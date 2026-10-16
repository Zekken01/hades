#include "SavedFilms/saved_film.hpp"

#include "hades/hades.h"

#include "CommandMap.hpp"
#include "Console/Console.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patch.hpp"
#include "Patches/Core.hpp"

#include <Windows.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <algorithm>
#include <string>
#include <vector>

// ElDewrito's determinism trace hooks simulation_record_update too
// (DeterminismDebugPatches.cpp); the film hook replaces it and calls it first.
struct s_simulation_update;
void simulation_record_update_hook(s_simulation_update *update);

// Recording and playing back saved films, after ManagedDonkey's saved_film_manager and
// simulation film code. The release eldorado.exe kept the simulation's playback world
// and the update encoders, but its film manager was stripped and the hooks that fed it
// are stubs:
//   simulation_record_update (game_tick hands it every update)  -> write to the film
//   simulation_must_close_saved_film (leaving a game)            -> close the film
//   simulation_update's playback branch no longer reads a film   -> read it here, after
//                                                                   simulation_update
// Films are written to <game directory>\films and started with Film.Play.

namespace SavedFilms
{
	namespace
	{
		long const k_game_options_size = 0x24B48;

		// Game functions and data.
		auto const game_options_get = reinterpret_cast<unsigned char *(*)()>(0x005322D0);
		auto const game_in_progress = reinterpret_cast<bool (*)()>(0x005314B0);
		auto const game_playback_get = reinterpret_cast<long (*)()>(0x00532A80);
		auto const simulation_update = reinterpret_cast<void (*)()>(0x004421B0);
		auto const simulation_notify_saved_film_ended = reinterpret_cast<void (*)()>(0x00441DF0);
		auto const handle_playback_update = reinterpret_cast<bool(__thiscall *)(void *, void const *, void *)>(0x00469610);
		auto const time_get_available = reinterpret_cast<long(__thiscall *)(void *, bool *, long *)>(0x0046A8F0);
		auto const game_time_get_speed = reinterpret_cast<float (*)()>(0x00564EB0);
		auto const game_seconds_to_ticks_round = reinterpret_cast<long (*)(float)>(0x00564BB0);
		auto const simulation_globals = reinterpret_cast<unsigned char *>(0x019A9FA0);

		auto const network_life_cycle_end = reinterpret_cast<void (*)()>(0x00454B40);
		auto const simulation_end = reinterpret_cast<void (*)(long)>(0x004412B0);
		auto const game_options_validate = reinterpret_cast<void (*)(unsigned char *)>(0x00532680);
		auto const main_game_change = reinterpret_cast<void (*)(unsigned char const *)>(0x00566E70);

		long const k_simulation_abort_reason_preparing_to_play_film = 3;

		// game_options fields.
		long const k_game_options_game_mode = 0x0;
		long const k_game_options_scenario_path = 0x24;
		long const k_game_options_game_playback = 0x130;
		long const k_game_options_record_saved_film = 0x132;
		long const k_game_options_playback_start_tick = 0x134;
		long const k_game_options_playback_length_in_ticks = 0x138;

		long const k_game_mode_campaign = 1;
		long const k_game_mode_multiplayer = 2;
		long const k_game_playback_film = 1;

		// c_simulation_world fields.
		long const k_world_state = 0x24;
		long const k_world_time_running = 0x30;
		long const k_world_out_of_sync = 0x3C;
		long const k_world_state_active = 4;

		long const k_simulation_update_metadata_from_saved_film = 1 << 2;

		c_saved_film g_recording;
		long g_last_recorded_update = -1;

		c_saved_film g_playback;
		bool g_playback_pending = false; // Film.Play was issued; the film's game is loading
		bool g_playback_ended = false;

		Modules::Command *g_record_variable = nullptr;

		void print(char const *format, ...)
		{
			char buffer[1024];
			va_list arguments;
			va_start(arguments, format);
			vsprintf_s(buffer, format, arguments);
			va_end(arguments);
			Console::WriteLine(buffer);
		}

		std::string films_directory()
		{
			char path[MAX_PATH];
			GetCurrentDirectoryA(sizeof(path), path);
			return std::string(path) + "\\films";
		}

		std::string film_path(std::string const &name)
		{
			std::string file = name;
			if (file.size() < 5 || _stricmp(file.c_str() + file.size() - 5, ".film") != 0)
				file += ".film";
			if (file.find_first_of("\\/:") == std::string::npos)
				file = films_directory() + "\\" + file;
			return file;
		}

		std::string new_film_name(unsigned char const *options)
		{
			char const *scenario = reinterpret_cast<char const *>(options + k_game_options_scenario_path);
			char const *map = strrchr(scenario, '\\');
			map = map ? map + 1 : scenario;

			time_t now = time(nullptr);
			tm local;
			localtime_s(&local, &now);
			char name[128];
			sprintf_s(name, "%04d-%02d-%02d_%02d-%02d-%02d_%s", local.tm_year + 1900, local.tm_mon + 1, local.tm_mday, local.tm_hour, local.tm_min, local.tm_sec, *map ? map : "film");
			return name;
		}

		void stop_recording()
		{
			if (!g_recording.is_writing())
				return;
			long ticks = g_recording.get_current_tick();
			std::string path = g_recording.get_path();
			g_recording.close();
			g_last_recorded_update = -1;
			print("Film saved: %s (%ld ticks)", path.c_str(), ticks);
		}

		/* ---------- hooks */

		void film_record_update_hook(void const *update)
		{
			::simulation_record_update_hook(static_cast<s_simulation_update *>(const_cast<void *>(update)));

			unsigned char *options = game_options_get();
			if (!options || *reinterpret_cast<unsigned short *>(options + k_game_options_game_playback) != 0)
				return; // never record a film that is being played back

			bool enabled = g_record_variable && g_record_variable->ValueInt != 0;
			long game_mode = *reinterpret_cast<long *>(options + k_game_options_game_mode);
			if (!enabled || (game_mode != k_game_mode_campaign && game_mode != k_game_mode_multiplayer))
			{
				stop_recording();
				return;
			}

			long update_number = *static_cast<long const *>(update);
			if (g_recording.is_writing() && update_number == g_last_recorded_update)
				return; // game_tick and game_update can both pass the same update

			// A lower update number than the last one written means a new game started.
			if (!g_recording.is_writing() || update_number < g_last_recorded_update)
			{
				stop_recording();
				CreateDirectoryA(films_directory().c_str(), nullptr);
				std::string path = film_path(new_film_name(options));
				if (!g_recording.open_for_write(path.c_str(), reinterpret_cast<s_game_options const *>(options)))
				{
					print("Film: could not create %s", path.c_str());
					return;
				}
			}

			if (g_recording.write_simulation_update(update))
				g_last_recorded_update = update_number;
			else
				stop_recording();
		}

		void simulation_must_close_saved_film_hook()
		{
			stop_recording();
			if (g_playback.is_open())
			{
				g_playback.close();
				g_playback_pending = false;
			}
		}

		// Feeds the playback world updates from the film, as ManagedDonkey's
		// simulation_film_retrieve_updates does: enough for a quarter second ahead.
		void retrieve_film_updates()
		{
			unsigned char *world = *reinterpret_cast<unsigned char **>(simulation_globals + 0x14);
			if (!world || world[k_world_time_running] == 0 || *reinterpret_cast<long *>(world + k_world_state) != k_world_state_active || world[k_world_out_of_sync])
				return;

			long target_updates = game_seconds_to_ticks_round(game_time_get_speed() * 0.25f);
			if (target_updates < 1)
				target_updates = 1;

			for (;;)
			{
				long updates_available = 0;
				time_get_available(world, nullptr, &updates_available);
				if (updates_available >= target_updates)
					return;

				if (g_playback.at_end())
				{
					if (!g_playback_ended)
					{
						g_playback_ended = true;
						simulation_notify_saved_film_ended();
						print("Film ended");
					}
					return;
				}

				long position_tick = g_playback.get_current_tick();
				static unsigned char update[k_simulation_update_size];
				if (!g_playback.read_simulation_update(update))
				{
					print("Film: could not read update %ld; stopping playback", position_tick);
					g_playback.close();
					return;
				}

				struct
				{
					unsigned short flags;
					long saved_film_position;
					long saved_film_tick;
				} metadata = { k_simulation_update_metadata_from_saved_film, 0, position_tick };

				if (!handle_playback_update(world, update, &metadata))
				{
					print("Film: update %ld was rejected by the simulation; stopping playback", *reinterpret_cast<long *>(update));
					g_playback.close();
					return;
				}
			}
		}

		void simulation_update_hook()
		{
			simulation_update();

			if (!g_playback.is_open() || !game_in_progress() || game_playback_get() != k_game_playback_film)
				return;
			g_playback_pending = false;
			retrieve_film_updates();
		}

		/* ---------- commands */

		bool command_play(std::vector<std::string> const &arguments, std::string &result)
		{
			if (arguments.empty())
			{
				result = "Usage: Film.Play <name or path>";
				return false;
			}

			stop_recording();
			std::string path = film_path(arguments[0]);
			if (!g_playback.open_for_read(path.c_str()))
			{
				result = "Could not open film " + path;
				return false;
			}

			// As ManagedDonkey's saved_film_manager_play: leave any session, end the
			// simulation, then change to the film's game with playback from the film.
			network_life_cycle_end();
			simulation_end(k_simulation_abort_reason_preparing_to_play_film);

			static unsigned char options[k_game_options_size];
			memcpy(options, g_playback.get_game_options(), k_game_options_size);
			*reinterpret_cast<unsigned short *>(options + k_game_options_game_playback) = k_game_playback_film;
			options[k_game_options_record_saved_film] = 0;
			*reinterpret_cast<long *>(options + k_game_options_playback_start_tick) = 0;
			*reinterpret_cast<long *>(options + k_game_options_playback_length_in_ticks) = g_playback.get_length_in_ticks();
			game_options_validate(options);
			main_game_change(options);

			g_playback_pending = true;
			g_playback_ended = false;
			result = "Playing " + path + " (" + std::to_string(g_playback.get_length_in_ticks()) + " ticks)";
			return true;
		}

		bool command_stop(std::vector<std::string> const &, std::string &result)
		{
			bool was_recording = g_recording.is_writing();
			stop_recording();
			if (g_playback.is_open())
			{
				g_playback.close();
				g_playback_pending = false;
				result = "Playback stopped";
			}
			else
			{
				result = was_recording ? "Recording stopped" : "No film is recording or playing";
			}
			return true;
		}

		bool command_list(std::vector<std::string> const &, std::string &result)
		{
			std::vector<std::string> names;
			WIN32_FIND_DATAA data;
			HANDLE find = FindFirstFileA((films_directory() + "\\*.film").c_str(), &data);
			if (find != INVALID_HANDLE_VALUE)
			{
				do
					names.push_back(data.cFileName);
				while (FindNextFileA(find, &data));
				FindClose(find);
			}
			std::sort(names.begin(), names.end());

			result = names.empty() ? "No films in " + films_directory() : "Films in " + films_directory() + ":";
			for (std::string const &name : names)
				result += "\n\t" + name.substr(0, name.size() - 5);
			return true;
		}

		class ModuleSavedFilm :
			public Modules::ModuleBase
		{
		public:
			ModuleSavedFilm() :
				ModuleBase("Film")
			{
				g_record_variable = AddVariableInt("Record", "film_record", "Record a saved film of every campaign and multiplayer game into the films folder", eCommandFlagsArchived, 1);
				g_record_variable->ValueIntMin = 0;
				g_record_variable->ValueIntMax = 1;
				AddCommand("Play", "film_play", "Plays a saved film from the films folder", eCommandFlagsNone, command_play, { "name(string) The film's name, as Film.List shows it, or a path" });
				AddCommand("Stop", "film_stop", "Stops recording or playing the current film", eCommandFlagsNone, command_stop);
				AddCommand("List", "film_list", "Lists the saved films", eCommandFlagsNone, command_list);
			}
		};
	}

	void ApplyAll()
	{
		Hook(0x00441F90 - 0x00400000, reinterpret_cast<void *>(film_record_update_hook)).Apply();
		Hook(0x00441CD0 - 0x00400000, reinterpret_cast<void *>(simulation_must_close_saved_film_hook)).Apply();
		Hook(0x00505DD7 - 0x00400000, reinterpret_cast<void *>(simulation_update_hook), static_cast<__int32>(HookFlags::IsCall)).Apply();
		Patches::Core::OnShutdown([]()
		{
			stop_recording();
			g_playback.close();
		});
	}
}

// Called from the ElModules constructor with the other modules.
void RegisterSavedFilmModule()
{
	static SavedFilms::ModuleSavedFilm module;
}
