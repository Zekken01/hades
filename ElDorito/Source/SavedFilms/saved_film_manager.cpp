#include "SavedFilms/saved_film.hpp"

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "CommandMap.hpp"
#include "Console/Console.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patch.hpp"
#include "Patches/Core.hpp"
#include "Modules/ModuleServer.hpp"
#include "Modules/ModuleTime.hpp"
#include "SavedFilms/saved_film_manager.hpp"
#include "Utils/String.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_system.hpp"
#include "mods/new/IModManager.hpp"

#include <Windows.h>
#include <share.h>
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

		auto const simulation_end = reinterpret_cast<void (*)(long)>(0x004412B0);
		auto const game_options_validate = reinterpret_cast<void (*)(unsigned char *)>(0x00532680);
		auto const main_game_change = reinterpret_cast<void (*)(unsigned char const *)>(0x00566E70);

		long const k_simulation_abort_reason_preparing_to_play_film = 3;

		// game_options fields.
		auto const main_menu_launch = reinterpret_cast<void (*)()>(0x005680E0);
		auto const game_time_get = reinterpret_cast<long (*)()>(0x00564D50);

		long const k_game_options_game_mode = 0x0;
		long const k_game_options_game_simulation = 0x4;
		long const k_game_options_game_network_type = 0x5;
		long const k_game_options_tick_rate = 0x6;
		unsigned char const k_game_simulation_local = 1;
		unsigned char const k_game_simulation_distributed_client = 4;
		long const k_game_options_game_instance = 0x8;

		// _game_simulation_synchronous_client and _game_simulation_distributed_client.
		bool simulation_is_client(unsigned char simulation)
		{
			return simulation == 2 || simulation == 4;
		}
		unsigned char const k_network_game_simulation_local = 1;
		long const k_game_options_game_engine = 0x32C; // the multiplayer variant's engine; Game.ForceLoad writes the same field
		long const k_game_options_scenario_path = 0x24;
		long const k_game_options_game_playback = 0x130;
		long const k_game_options_record_saved_film = 0x132;
		long const k_game_options_playback_start_tick = 0x134;
		long const k_game_options_playback_length_in_ticks = 0x138;

		long const k_game_mode_campaign = 1;
		long const k_game_mode_multiplayer = 2;
		long const k_game_playback_film = 1;

		// c_simulation_world fields.
		long const k_world_type = 0x8;
		long const k_world_next_update_number = 0x34;
		long const k_world_update_queue_next_update_number_to_dequeue = 0x14EC;
		long const k_world_update_queue_latest_received_type = 0x14F0;
		long const k_world_update_queue_latest_received_update_number = 0x14F4;
		long const k_world_state = 0x24;
		long const k_world_time_running = 0x30;
		long const k_world_out_of_sync = 0x3C;
		long const k_world_state_active = 4;

		long const k_simulation_update_metadata_from_saved_film = 1 << 2;

		std::string loaded_mod_hash();
		std::string g_loaded_mod_hash; // loaded_mod_hash() as of this frame, set on the main thread

		c_saved_film g_recording;

		// Replication packets a client receives before its film opens (the join, which
		// creates every entity), written at the start of the film.
		std::vector<std::vector<unsigned char>> g_pending_packets;
		long long g_pending_packet_bytes = 0;
		long long const k_pending_packet_bytes_max = 64 * 1024 * 1024;
		long g_last_recorded_update = -1;
		unsigned long long g_recording_game_instance = 0;
		std::string g_last_recorded_players_info;

		c_saved_film g_playback;
		long g_clip_start_tick = -1; // a clip being recorded from the film, from this tick
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
			apply_received_map_variant_placements(g_recording.get_game_options());
			g_recording.close();
			g_last_recorded_update = -1;
			print("Film saved: %s (%ld ticks)", path.c_str(), ticks);
		}

		/* ---------- hooks */

		void record_update_to_film(void const *update);

		// simulation_record_update, which game_tick and game_update call: ElDewrito's
		// determinism trace, then the film.
		void film_record_update_hook(void const *update)
		{
			::simulation_record_update_hook(static_cast<s_simulation_update *>(const_cast<void *>(update)));
			record_update_to_film(update);
		}

		// simulation_update_pregame builds and applies updates outside the game tick (a
		// client's join arrives in these, as entity creations in the update's simulation
		// queues); its simulation_record_update call was stripped from the release build,
		// so the updates are recorded here, before they are applied.
		auto const simulation_apply_before_game = reinterpret_cast<void (*)(void const *)>(0x00440E50);

		void simulation_update_pregame_apply_hook(void const *update)
		{
			record_update_to_film(update);
			simulation_apply_before_game(update);
		}

		void record_update_to_film(void const *update)
		{

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

			// A client of an online game is sent the other players and objects by the
			// host; its films also carry what it was sent (replication packets,
			// saved_film_replication.cpp) so the game can be rebuilt from them.

			// Updates reach here from simulation_update_pregame (before the game ticks,
			// e.g. a client's join) and from game_tick/game_update, which can pass one
			// that was already written; each is written once, in order.
			long update_number = *static_cast<long const *>(update);
			unsigned long long game_instance = *reinterpret_cast<unsigned long long *>(options + k_game_options_game_instance);
			bool new_game = !g_recording.is_writing() || game_instance != g_recording_game_instance;
			if (!new_game && update_number <= g_last_recorded_update)
				return;

			if (new_game)
			{
				g_recording_game_instance = game_instance;
				stop_recording();
				CreateDirectoryA(films_directory().c_str(), nullptr);
				std::string path = film_path(new_film_name(options));
				if (!g_recording.open_for_write(path.c_str(), reinterpret_cast<s_game_options const *>(options),
					g_loaded_mod_hash.c_str(), c_mod_system::get_current_package_filename(EModIndex(0)).c_str()))
				{
					print("Film: could not create %s", path.c_str());
					return;
				}
				print("Film recording: %s (from update #%ld)", path.c_str(), update_number);
				g_last_recorded_players_info.clear();
				for (std::vector<unsigned char> const &packet : g_pending_packets)
					g_recording.write_record(_saved_film_update_type_replication_packet, packet.data(), long(packet.size()));
				g_pending_packets.clear();
				g_pending_packet_bytes = 0;
			}

			if (g_recording.write_simulation_update(update))
				g_last_recorded_update = update_number;
			else
			{
				stop_recording();
				return;
			}

			// The players' ranks and emblems come from the server (Server.PlayersInfoClient),
			// which a film's playback has none of; they are recorded as they change.
			std::string const &players_info = Modules::ModuleServer::Instance().VarPlayersInfoClient->ValueString;
			if (players_info != g_last_recorded_players_info && !players_info.empty() && players_info != "{}"
				&& g_recording.write_record(_saved_film_update_type_players_info, players_info.data(), long(players_info.size())))
				g_last_recorded_players_info = players_info;
		}

		// Leaving a game closes a recording. Playback is closed by the main loop once a
		// game other than the film is running, since replaying a film leaves its game too.
		void simulation_must_close_saved_film_hook()
		{
			stop_recording();
		}

		// Feeds the playback world updates from the film, as ManagedDonkey's
		// simulation_film_retrieve_updates does: enough for a quarter second ahead.
		// films\film_playback.log: what playback saw, to diagnose a film that does not play.
		FILE *g_playback_log = nullptr;
		std::string g_last_logged_state;

		void playback_log(char const *format, ...)
		{
			if (!g_playback_log)
			{
				CreateDirectoryA(films_directory().c_str(), nullptr);
				// Shared, so the log can be read while the game runs.
				g_playback_log = _fsopen((films_directory() + "\\film_playback.log").c_str(), "w", _SH_DENYNO);
				if (!g_playback_log)
					return;
			}
			char buffer[1024];
			va_list arguments;
			va_start(arguments, format);
			vsprintf_s(buffer, format, arguments);
			va_end(arguments);
			fprintf(g_playback_log, "[%lu] %s\n", GetTickCount(), buffer);
			fflush(g_playback_log);
		}

		// Logs the playback state whenever it changes.
		void playback_log_state(char const *state)
		{
			if (g_last_logged_state != state)
			{
				g_last_logged_state = state;
				playback_log("%s", state);
			}
		}

		// The update number the playback world accepts next, as handle_playback_update
		// computes it; -1 accepts any.
		long world_expected_update_number(unsigned char const *world)
		{
			long received_type = *reinterpret_cast<long const *>(world + k_world_update_queue_latest_received_type);
			long latest = *reinterpret_cast<long const *>(world + k_world_update_queue_latest_received_update_number);
			if (received_type == 1)
				return latest;
			if (received_type != 0)
				return *reinterpret_cast<long const *>(world + k_world_update_queue_next_update_number_to_dequeue);
			return latest + 1;
		}

		void retrieve_film_updates()
		{
			unsigned char *world = *reinterpret_cast<unsigned char **>(simulation_globals + 0x14);
			{
				char state[256];
				sprintf_s(state, "world %p type %ld state %ld time_running %d out_of_sync %d expects %ld",
					world,
					world ? *reinterpret_cast<long *>(world + k_world_type) : -1,
					world ? *reinterpret_cast<long *>(world + k_world_state) : -1,
					world ? world[k_world_time_running] : -1,
					world ? world[k_world_out_of_sync] : -1,
					world ? world_expected_update_number(world) : -2);
				playback_log_state(state);
			}
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

				// The film's numbering is its own; the world only checks that the numbers
				// run on from its own count, so the update takes the number it expects.
				long &update_number = *reinterpret_cast<long *>(update);
				long expected = world_expected_update_number(world);
				if (position_tick < 3 || (expected != -1 && update_number != expected))
					playback_log("film tick %ld: update #%ld, world expects #%ld", position_tick, update_number, expected);
				if (expected != -1)
					update_number = expected;

				if (!handle_playback_update(world, update, &metadata))
				{
					playback_log("film tick %ld: update #%ld rejected", position_tick, update_number);
					print("Film: update %ld was rejected by the simulation; stopping playback", update_number);
					g_playback.close();
					return;
				}
			}
		}

		/* ---------- film HUD */

		// The chud's saved film timeline reads this; the release build's chud asked the
		// stripped film manager for it and so always drew 00:00.
		struct s_saved_film_hud_interface_state
		{
			float duration_in_seconds;
			float marker_position_in_seconds;
			long number_of_chapters_available;
			float buffered_theta;
			float current_position_theta;
			float recording_start_theta;
			bool recording;
			float chapter_mark_theta[10];
		};
		static_assert(sizeof(s_saved_film_hud_interface_state) == 0x44, "Invalid s_saved_film_hud_interface_state size");

		long film_tick_rate()
		{
			if (s_game_options const *options = g_playback.get_game_options())
			{
				short rate = *reinterpret_cast<short const *>(reinterpret_cast<unsigned char const *>(options) + k_game_options_tick_rate);
				if (rate > 0)
					return rate;
			}
			return 60;
		}

		// The film tick the game is showing (the film is read a little ahead of it).
		long film_playback_tick()
		{
			long tick = game_time_get();
			long length = g_playback.get_length_in_ticks();
			return tick < 0 ? 0 : tick > length ? length : tick;
		}

		void __cdecl saved_film_get_hud_interface_state(s_saved_film_hud_interface_state *state)
		{
			memset(state, 0, sizeof(*state));
			if (!g_playback.is_open() || game_playback_get() != k_game_playback_film)
				return;

			float rate = float(film_tick_rate());
			long length = g_playback.get_length_in_ticks();
			state->duration_in_seconds = length / rate;
			state->marker_position_in_seconds = film_playback_tick() / rate;
			if (length > 0)
			{
				state->current_position_theta = float(film_playback_tick()) / length;
				if (g_clip_start_tick >= 0)
				{
					state->recording = true;
					state->recording_start_theta = float(g_clip_start_tick) / length;
				}
				state->buffered_theta = state->current_position_theta;
				state->number_of_chapters_available = k_film_chapter_count - 1;
				for (long chapter = 1; chapter < k_film_chapter_count; chapter++)
					state->chapter_mark_theta[chapter - 1] = float(chapter) / k_film_chapter_count;
			}
		}

		// Replaces "call game_is_multiplayer; test al, al; jz 0xA86C64" at 0xA86C2F in the
		// chud's per-user update (edi is the user's chud data, the film state at +0x8BC),
		// as ManagedDonkey's saved_film_manager_get_hud_interface_state_inline does.
		__declspec(naked) void chud_saved_film_state_hook()
		{
			__asm
			{
				lea     eax, [edi + 0x8BC]
				push    eax
				call    saved_film_get_hud_interface_state
				add     esp, 4

				mov     eax, 0x00531C00 // game_is_multiplayer
				call    eax
				test    al, al
				jz      not_multiplayer
				push    0x00A86C38
				ret
			not_multiplayer:
				push    0x00A86C64
				ret
			}
		}

		/* ---------- out of sync */

		auto const get_random_seed = reinterpret_cast<unsigned long (*)()>(0x0051EFE0);
		auto const world_go_out_of_sync = reinterpret_cast<void(__thiscall *)(void *, bool)>(0x004695E0);

		long const k_simulation_update_verify_game_time = 0x15F0;
		long const k_simulation_update_verify_random_seed = 0x15F4;

		// simulation_build_update checks each update a playback world consumes against the
		// world - its number, game time and random seed - and takes the world out of sync
		// on a mismatch. An online client's updates come from the host, whose time and
		// random seed the client's own simulation never tracked (a distributed client skips
		// the check), so a client's film fails it straight away. During playback the
		// mismatch is logged and the film plays on.
		void __cdecl build_update_out_of_sync(void *world, unsigned char const *update, bool determinism_failure)
		{
			if (!g_playback.is_open() || game_playback_get() != k_game_playback_film)
			{
				world_go_out_of_sync(world, determinism_failure);
				return;
			}

			static long logged = 0;
			if (logged < 20)
			{
				logged++;
				playback_log("update #%ld fails the sync check: world expects #%ld, time %ld (local %ld), seed %08lX (local %08lX)",
					*reinterpret_cast<long const *>(update),
					*reinterpret_cast<long const *>(static_cast<unsigned char *>(world) + k_world_next_update_number),
					*reinterpret_cast<long const *>(update + k_simulation_update_verify_game_time), game_time_get(),
					*reinterpret_cast<unsigned long const *>(update + k_simulation_update_verify_random_seed), get_random_seed());
			}
		}

		// Replaces "call c_simulation_world::go_out_of_sync" at 0x4411B1 in
		// simulation_build_update (ecx is the world, esi the update, the argument pushed).
		__declspec(naked) void build_update_out_of_sync_hook()
		{
			__asm
			{
				push    dword ptr [esp + 4]
				push    esi
				push    ecx
				call    build_update_out_of_sync
				add     esp, 12
				ret     4
			}
		}

		/* ---------- starting a film */

		// Film.Play opens the film; the main loop then puts the film's mod in place and
		// changes to its game. ElDewrito keeps the active mod in step with the squad
		// session (ModSessionManager), so the session stays up and its mod is switched
		// to the film's, rather than leaving the session as ManagedDonkey does.
		enum e_play_state
		{
			_play_state_none,
			_play_state_requested,
			_play_state_waiting_for_mod,
		};
		e_play_state g_play_state = _play_state_none;
		DWORD g_play_wait_start = 0;

		std::string film_mod_description()
		{
			std::string file = g_playback.get_mod_file();
			size_t slash = file.find_last_of("\\/");
			return slash == std::string::npos ? file : file.substr(slash + 1);
		}

		void cancel_play(char const *reason)
		{
			print("Film: %s", reason);
			playback_log("cancelled: %s", reason);
			g_playback.close();
			g_play_state = _play_state_none;
		}

		// The film's game_options, as a film's game plays them.
		void set_film_playback_options(unsigned char *options)
		{
			// A film recorded in an online game carries that game's simulation. The
			// playback world is a local playback world either way (the world type comes
			// from game_playback alone), but a distributed client's film keeps its
			// simulation: the host's entity creations, updates and promotions reach the
			// client through the simulation queues in its updates, and the queue
			// handlers apply them only in a distributed game (with a playback path for
			// creations). A host's film, like a local one, plays as a local game.
			bool distributed_client = options[k_game_options_game_simulation] == k_game_simulation_distributed_client;
			playback_log("film simulation %d, network %d; playing as %s", options[k_game_options_game_simulation], options[k_game_options_game_network_type], distributed_client ? "a distributed client" : "local");
			if (!distributed_client)
				options[k_game_options_game_simulation] = k_game_simulation_local;
			options[k_game_options_game_network_type] = k_network_game_simulation_local;
			*reinterpret_cast<unsigned short *>(options + k_game_options_game_playback) = k_game_playback_film;
			options[k_game_options_record_saved_film] = 0;
			*reinterpret_cast<long *>(options + k_game_options_playback_start_tick) = 0;
			*reinterpret_cast<long *>(options + k_game_options_playback_length_in_ticks) = g_playback.get_length_in_ticks();
		}

		void start_film_game()
		{
			simulation_end(k_simulation_abort_reason_preparing_to_play_film);

			static unsigned char options[k_game_options_size];
			memcpy(options, g_playback.get_game_options(), k_game_options_size);
			set_film_playback_options(options);
			game_options_validate(options);
			main_game_change(options);

			g_play_state = _play_state_none;
			playback_log("starting the film's game: map %s", reinterpret_cast<char const *>(options + k_game_options_scenario_path));
		}

		// The hash of the mod package that is loaded, "" when none is. (The squad session's
		// mod, which c_mod_system::get_current_package_hash reports, is not set at the
		// main menu, so the loaded package is asked directly.)
		std::string loaded_mod_hash()
		{
			IMod *mod = c_mod_system::GetModManager().GetMod(EModIndex(0));
			if (!mod)
				return "";
			c_mod_package *package = mod->GetPak(true);
			if (!package)
				return "";
			std::string hash;
			Utils::String::BytesToHexString(package->get_header()->sha1, sizeof(package->get_header()->sha1), hash);
			return hash;
		}

		bool film_mod_ready(std::string const &hash)
		{
			IMod *mod = c_mod_system::GetModManager().GetMod(EModIndex(0));
			if (hash.empty())
				return mod == nullptr;
			return mod && !mod->GetPakIsLoading() && !mod->GetCacheIsLoading() && mod->GetError() == kSuccess
				&& _stricmp(loaded_mod_hash().c_str(), hash.c_str()) == 0;
		}

		void update_play_request()
		{
			if (g_play_state == _play_state_requested)
			{
				std::string hash = g_playback.get_mod_hash();
				// Films from before the mod was recorded keep whatever mod is active.
				if (!g_playback.has_mod_info() || film_mod_ready(hash))
				{
					start_film_game();
					return;
				}

				playback_log("switching mod from '%s' to '%s' (%s)", loaded_mod_hash().c_str(), hash.c_str(), film_mod_description().c_str());
				bool switched = hash.empty()
					? c_mod_system::unload_current_package()
					: c_mod_system::load_package_by_identifier(hash.c_str());
				if (!switched)
				{
					std::string reason = "this film needs the mod " + film_mod_description() + ", which is not installed";
					cancel_play(reason.c_str());
					return;
				}
				g_play_state = _play_state_waiting_for_mod;
				g_play_wait_start = GetTickCount();
				print("Film: loading the mod %s", hash.empty() ? "(none)" : film_mod_description().c_str());
			}

			if (g_play_state == _play_state_waiting_for_mod)
			{
				std::string hash = g_playback.get_mod_hash();
				if (film_mod_ready(hash))
				{
					start_film_game();
					return;
				}
				IMod *mod = c_mod_system::GetModManager().GetMod(EModIndex(0));
				EModResult error = mod ? mod->GetError() : kSuccess;
				{
					char state[256];
					sprintf_s(state, "waiting for mod: loaded '%s' pak_loading %d cache_loading %d error %d",
						loaded_mod_hash().c_str(), mod ? mod->GetPakIsLoading() : -1, mod ? mod->GetCacheIsLoading() : -1, int(error));
					playback_log_state(state);
				}
				if (mod && error != kSuccess && error != kPending)
					cancel_play(("the mod " + film_mod_description() + " failed to load").c_str());
				else if (GetTickCount() - g_play_wait_start > 30000)
					cancel_play("timed out waiting for the film's mod to load");
			}
		}

		/* ---------- speed and skipping */

		// Playback speed is the game speed ElDorito::Tick applies every tick
		// (Time.GameSpeed, or Time.GameSpeedClient in a session), so both are set.
		long g_skip_target = -1; // the film tick a skip runs to at full speed
		long g_pending_skip_target = -1; // a skip back, run once the restarted film plays

		// Replaying starts the film's game again with its own game options - the same
		// game instance, so a theater session keeps it as its game - by main_game_change
		// alone, as the session started it (c_life_cycle_state_handler_in_game::
		// begin_load_map): ending the simulation first aborts it, and the session's life
		// cycle ends a game whose simulation aborted. (A map reset leaves the simulation
		// world's entities behind, which a client's film cannot replay over.) No updates
		// are fed until the new game is in.
		auto const main_game_change_in_progress = reinterpret_cast<bool (*)()>(0x005670E0);
		bool g_reset_requested = false;
		bool g_reset_change_seen = false;

		// A theater session's film ends through the session (network_squad_session_end_game:
		// its life cycle finishes a playback game, and the squad goes back to its lobby).
		auto const network_squad_session_end_game = reinterpret_cast<bool (*)()>(0x00438780);
		bool g_session_film = false; // the film's game was started by a theater session
		DWORD g_end_request_tick = 0;
		DWORD g_reset_request_tick = 0;
		float g_speed_before_skip = 1.0f;
		float const k_skip_speed = 10.0f;

		float speed_get()
		{
			return Modules::ModuleTime::Instance().VarSpeed->ValueFloat;
		}

		void speed_set(float speed)
		{
			speed = speed < 0.0f ? 0.0f : speed > k_skip_speed ? k_skip_speed : speed;
			Modules::ModuleTime &time = Modules::ModuleTime::Instance();
			time.VarSpeed->ValueFloat = speed;
			time.VarSpeedClient->ValueFloat = speed;
		}

		bool film_game_running()
		{
			return g_playback.is_open() && game_in_progress() && game_playback_get() == k_game_playback_film;
		}

		void start_skip_to(long target)
		{
			if (g_skip_target < 0)
				g_speed_before_skip = speed_get() > 0.0f ? speed_get() : 1.0f;
			g_skip_target = target;
			speed_set(k_skip_speed);
		}

		void update_skip()
		{
			if (!film_game_running())
				return;
			if (g_pending_skip_target >= 0)
			{
				long target = g_pending_skip_target;
				g_pending_skip_target = -1;
				if (target > film_playback_tick())
					start_skip_to(target);
			}
			if (g_skip_target >= 0 && (film_playback_tick() >= g_skip_target || film_playback_tick() >= g_playback.get_length_in_ticks()))
			{
				speed_set(g_speed_before_skip);
				g_skip_target = -1;
			}
		}

		void reset_playback_state()
		{
			g_clip_start_tick = -1;
			g_skip_target = -1;
			g_pending_skip_target = -1;
			speed_set(1.0f);
		}

		// The right trigger plays the film faster the further it is pulled, as Halo 3's
		// c_saved_film_director::update does (its saved film manager call was stripped):
		// speed = (max + 1)^pull - 1, max from the camera globals' saved film director max
		// playback speed. Letting go returns to the speed before.
		auto const input_abstraction_get_input_state = reinterpret_cast<void (*)(long, unsigned char **)>(0x0060BFE0);
		long const k_abstract_button_size = 0xC;
		long const k_abstract_button_right_trigger = 1;
		long const k_abstract_button_flags = 0x3;
		long const k_abstract_button_down_amount = 0x4;
		long const k_abstract_button_accessor_index = 0x8;
		long const k_abstract_button_locked_index = 0x9;
		float const *const k_saved_film_director_max_playback_speed = reinterpret_cast<float const *>(0x018ECE00 + 0x80);

		void update_trigger_speed()
		{
			static bool trigger_controls_speed = false;
			static float speed_before_trigger = 1.0f;

			float pull = 0.0f;
			bool const controller_in_use = *reinterpret_cast<bool const *>(0x0244DE98);
			if (film_game_running() && g_skip_target < 0 && controller_in_use)
			{
				unsigned char *state = nullptr;
				input_abstraction_get_input_state(0, &state);
				unsigned char const *trigger = state ? state + k_abstract_button_right_trigger * k_abstract_button_size : nullptr;
				char locked = trigger ? char(trigger[k_abstract_button_locked_index]) : 0;
				if (trigger && !(trigger[k_abstract_button_flags] & 1) && (locked == -1 || locked == char(trigger[k_abstract_button_accessor_index])))
					pull = *reinterpret_cast<float const *>(trigger + k_abstract_button_down_amount);
			}

			if (pull > 0.0f)
			{
				if (!trigger_controls_speed)
				{
					speed_before_trigger = speed_get();
					trigger_controls_speed = true;
				}
				float max_speed = *k_saved_film_director_max_playback_speed > 0.0f ? *k_saved_film_director_max_playback_speed : 4.0f;
				speed_set(powf(max_speed + 1.0f, pull) - 1.0f);
			}
			else if (trigger_controls_speed)
			{
				trigger_controls_speed = false;
				if (film_game_running() && g_skip_target < 0)
					speed_set(speed_before_trigger);
			}
		}

		void simulation_update_hook()
		{
			if (g_end_request_tick && GetTickCount() - g_end_request_tick > 5000)
			{
				g_end_request_tick = 0;
				if (film_game_running())
				{
					playback_log("the session did not end the film's game; leaving it");
					g_playback.close();
					g_playback_pending = false;
					g_play_state = _play_state_none;
					reset_playback_state();
					main_menu_launch();
				}
			}

			if (g_reset_requested)
			{
				if (main_game_change_in_progress())
					g_reset_change_seen = true;
				else if (g_reset_change_seen && game_in_progress())
				{
					g_reset_requested = false;
					playback_log("the film's game restarted");
				}
				else if (GetTickCount() - g_reset_request_tick > 15000)
				{
					g_reset_requested = false;
					playback_log("the film's game did not restart");
				}
			}
			simulation_update();
			g_loaded_mod_hash = loaded_mod_hash();
			update_play_request();
			update_theater();
			update_trigger_speed();

			// A game other than the film is running: the film was left.
			if (g_playback.is_open() && g_play_state == _play_state_none && !g_playback_pending
				&& game_in_progress() && game_playback_get() != k_game_playback_film)
			{
				playback_log("left the film");
				g_playback.close();
				reset_playback_state();
			}
			if (!g_reset_requested)
				update_skip();
			if (g_clip_start_tick >= 0 && film_is_ended())
				clip_stop();

			if (g_playback.is_open())
			{
				char state[128];
				sprintf_s(state, "game_in_progress %d game_playback %ld", game_in_progress(), game_playback_get());
				playback_log_state(state);
			}

			if (!g_playback.is_open() || !game_in_progress() || game_playback_get() != k_game_playback_film || g_reset_requested)
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

			std::string path = film_path(arguments[0]);
			if (!play_film(path.c_str()))
			{
				result = "Could not open film " + path;
				return false;
			}
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

		bool command_delete(std::vector<std::string> const &arguments, std::string &result)
		{
			if (arguments.empty())
			{
				result = "Usage: Film.Delete <name>";
				return false;
			}
			std::string path = film_path(arguments[0]);
			if ((g_playback.is_open() && g_playback.get_path() == path) || (g_recording.is_writing() && g_recording.get_path() == path))
			{
				result = "That film is in use";
				return false;
			}
			if (!DeleteFileA(path.c_str()))
			{
				result = "Could not delete " + path;
				return false;
			}
			result = "Deleted " + path;
			return true;
		}

		bool command_speed(std::vector<std::string> const &arguments, std::string &result)
		{
			if (!film_is_playing())
			{
				result = "No film is playing";
				return false;
			}
			if (arguments.empty())
			{
				result = "Usage: Film.Speed <speed>";
				return false;
			}
			set_playback_speed(float(atof(arguments[0].c_str())));
			result = "Film speed " + arguments[0];
			return true;
		}

		bool command_pause(std::vector<std::string> const &, std::string &result)
		{
			if (!film_is_playing())
			{
				result = "No film is playing";
				return false;
			}
			bool paused = get_playback_speed() > 0.0f;
			set_playback_speed(paused ? 0.0f : 1.0f);
			result = paused ? "Paused" : "Resumed";
			return true;
		}

		bool command_skip(std::vector<std::string> const &arguments, std::string &result)
		{
			if (!film_is_playing())
			{
				result = "No film is playing";
				return false;
			}
			float seconds = arguments.empty() ? 30.0f : float(atof(arguments[0].c_str()));
			skip(seconds);
			result = "Skipping " + std::to_string(int(seconds)) + " seconds";
			return true;
		}

		bool command_end(std::vector<std::string> const &, std::string &result)
		{
			if (!g_playback.is_open())
			{
				result = "No film is playing";
				return false;
			}
			end_film();
			result = "Film ended";
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
				AddCommand("Delete", "film_delete", "Deletes a saved film", eCommandFlagsNone, command_delete, { "name(string) The film's name, as Film.List shows it" });
				AddCommand("Speed", "film_speed", "Sets the playback speed of the film that is playing", eCommandFlagsNone, command_speed, { "speed(float) 0 to 10; 1 is normal speed" });
				AddCommand("Pause", "film_pause", "Pauses or resumes the film that is playing", eCommandFlagsNone, command_pause);
				AddCommand("Skip", "film_skip", "Skips the film that is playing forward or back", eCommandFlagsNone, command_skip, { "seconds(float) Seconds to skip; negative skips back (default 30)" });
				AddCommand("End", "film_end", "Stops the film that is playing and returns to the main menu", eCommandFlagsNone, command_end);
			}
		};
	}

	bool play_film(char const *path)
	{
		g_session_film = false;
		stop_recording();
		if (!g_playback.open_for_read(path))
			return false;

		// The main loop starts it (update_play_request), with the film's mod; a clip
		// then runs at full speed to its start.
		g_play_state = _play_state_requested;
		g_clip_start_tick = -1;
		g_pending_skip_target = g_playback.is_snippet() ? g_playback.get_snippet_start_tick() : -1;
		g_playback_pending = true;
		g_playback_ended = false;
		g_last_logged_state.clear();
		playback_log("play %s: %ld ticks, mod '%s' (%s)", path, g_playback.get_length_in_ticks(),
			g_playback.has_mod_info() ? g_playback.get_mod_hash().c_str() : "not recorded", film_mod_description().c_str());
		return true;
	}

	bool begin_session_film(void *options, char const *path)
	{
		stop_recording();
		if (!g_playback.open_for_read(path))
		{
			playback_log("session film: could not open %s", path);
			return false;
		}

		g_play_state = _play_state_none;
		g_clip_start_tick = -1;
		g_pending_skip_target = g_playback.is_snippet() ? g_playback.get_snippet_start_tick() : -1;
		g_playback_pending = true;
		g_playback_ended = false;
		g_last_logged_state.clear();
		playback_log("session film %s: %ld ticks", path, g_playback.get_length_in_ticks());
		g_session_film = true;
		g_end_request_tick = 0;

		// The session's copy of the film's game_options, overridden as for Film.Play.
		set_film_playback_options(static_cast<unsigned char *>(options));
		game_options_validate(static_cast<unsigned char *>(options));
		playback_log("starting the film's game: map %s", static_cast<char const *>(options) + k_game_options_scenario_path);
		return true;
	}

	bool prepare_film_mod(char const *path)
	{
		static std::string requested_path;
		static std::string requested_hash;
		static DWORD requested_time = 0;

		c_saved_film film;
		if (!film.open_for_read(path))
			return false;
		// Films from before the mod was recorded keep whatever mod is active.
		if (!film.has_mod_info())
			return true;
		std::string hash = film.get_mod_hash();
		if (film_mod_ready(hash))
			return true;

		// Switch once per film (again only if it has not loaded after a while).
		if (requested_path == path && requested_hash == hash && GetTickCount() - requested_time < 30000)
			return false;
		requested_path = path;
		requested_hash = hash;
		requested_time = GetTickCount();

		std::string file = film.get_mod_file();
		size_t slash = file.find_last_of("\\/");
		std::string description = slash == std::string::npos ? file : file.substr(slash + 1);
		playback_log("theater: switching mod from '%s' to '%s' (%s) for %s", loaded_mod_hash().c_str(), hash.c_str(), description.c_str(), path);
		bool switched = hash.empty()
			? c_mod_system::unload_current_package()
			: c_mod_system::load_package_by_identifier(hash.c_str());
		if (!switched)
			print("Film: this film needs the mod %s, which is not installed", description.c_str());
		else
			print("Film: loading the mod %s", hash.empty() ? "(none)" : description.c_str());
		return false;
	}

	std::string get_loaded_mod_hash()
	{
		return g_loaded_mod_hash;
	}

	std::string get_film_players_info()
	{
		return film_game_running() ? g_playback.get_players_info() : std::string();
	}

	std::string get_films_directory()
	{
		return films_directory();
	}

	bool film_is_playing()
	{
		return film_game_running();
	}

	bool film_is_ended()
	{
		return film_game_running() && film_playback_tick() >= g_playback.get_length_in_ticks();
	}

	float get_playback_speed()
	{
		return g_skip_target >= 0 ? g_speed_before_skip : speed_get();
	}

	void set_playback_speed(float speed)
	{
		if (g_skip_target >= 0)
			g_speed_before_skip = speed; // applied when the skip finishes
		else
			speed_set(speed);
	}

	void skip(float seconds)
	{
		if (!film_game_running())
			return;
		long length = g_playback.get_length_in_ticks();
		long target = film_playback_tick() + long(seconds * film_tick_rate());
		target = target < 0 ? 0 : target > length ? length : target;
		if (target > film_playback_tick())
		{
			start_skip_to(target);
		}
		else
		{
			// There are no snapshots to rewind to: replay from the start and run to it.
			clip_stop();
			float speed = get_playback_speed();
			replay_film();
			g_speed_before_skip = speed > 0.0f ? speed : 1.0f;
			g_pending_skip_target = target;
		}
	}

	float film_position_theta()
	{
		long length = g_playback.get_length_in_ticks();
		return film_game_running() && length > 0 ? float(film_playback_tick()) / length : 0.0f;
	}

	void skip_chapter(long direction)
	{
		if (!film_game_running())
			return;
		long length = g_playback.get_length_in_ticks();
		long tick = film_playback_tick();
		long rate = film_tick_rate();
		long target = -1;
		if (direction > 0)
		{
			// The next mark at least half a second on; the end after the last.
			for (long chapter = 1; chapter <= k_film_chapter_count && target < 0; chapter++)
			{
				long mark = length * chapter / k_film_chapter_count;
				if (mark > tick + rate / 2)
					target = mark;
			}
		}
		else
		{
			// The last mark more than two seconds back, so a press just after a mark
			// goes on to the one before it.
			for (long chapter = k_film_chapter_count - 1; chapter >= 0 && target < 0; chapter--)
			{
				long mark = length * chapter / k_film_chapter_count;
				if (mark < tick - 2 * rate)
					target = mark;
			}
			if (target < 0)
				target = 0;
		}
		if (target >= 0 && target != tick)
			skip(float(target - tick) / rate);
	}

	bool is_skipping()
	{
		return g_skip_target >= 0 || g_pending_skip_target >= 0;
	}

	void replay_film()
	{
		if (!g_playback.is_open())
			return;
		std::string path = g_playback.get_path();
		clip_stop();
		g_skip_target = -1;
		g_pending_skip_target = -1;
		if (!g_playback.open_for_read(path.c_str()))
			return;
		g_playback_pending = true;
		g_playback_ended = false;
		if (game_in_progress() && game_playback_get() == k_game_playback_film)
		{
			static unsigned char options[k_game_options_size];
			memcpy(options, game_options_get(), k_game_options_size);
			g_reset_requested = true;
			g_reset_change_seen = false;
			g_reset_request_tick = GetTickCount();
			main_game_change(options);
			playback_log("restarting the film's game");
		}
		else
			g_play_state = _play_state_requested;
		if (g_playback.is_snippet())
			g_pending_skip_target = g_playback.get_snippet_start_tick();
		playback_log("replay %s", path.c_str());
	}

	void end_film()
	{
		if (!g_playback.is_open())
			return;
		clip_stop();
		if (g_session_film && film_game_running() && network_squad_session_end_game())
		{
			playback_log("ending the film's game through the session");
			g_end_request_tick = GetTickCount();
			return;
		}
		g_playback.close();
		g_playback_pending = false;
		g_play_state = _play_state_none;
		reset_playback_state();
		main_menu_launch();
	}

	void record_replication_packet(void const *data, long size)
	{
		unsigned char const *options = game_options_get();
		if (!options || !g_record_variable || g_record_variable->ValueInt == 0
			|| *reinterpret_cast<unsigned short const *>(options + k_game_options_game_playback) != 0
			|| options[k_game_options_game_simulation] != k_game_simulation_distributed_client)
		{
			return;
		}

		if (g_recording.is_writing())
		{
			g_recording.write_record(_saved_film_update_type_replication_packet, data, size);
		}
		else if (g_pending_packet_bytes + size <= k_pending_packet_bytes_max)
		{
			unsigned char const *bytes = static_cast<unsigned char const *>(data);
			g_pending_packets.emplace_back(bytes, bytes + size);
			g_pending_packet_bytes += size;
		}
	}

	void clear_pending_replication_packets()
	{
		g_pending_packets.clear();
		g_pending_packet_bytes = 0;
	}

	bool clip_is_recording()
	{
		return g_clip_start_tick >= 0;
	}

	bool clip_start()
	{
		if (!film_game_running() || film_is_ended() || is_skipping() || g_clip_start_tick >= 0)
			return false;
		g_clip_start_tick = film_playback_tick();
		print("Film: recording a clip from %ld:%02ld", g_clip_start_tick / film_tick_rate() / 60, g_clip_start_tick / film_tick_rate() % 60);
		return true;
	}

	bool clip_stop()
	{
		if (g_clip_start_tick < 0)
			return false;
		long start_tick = g_clip_start_tick;
		long stop_tick = film_game_running() ? film_playback_tick() : -1;
		g_clip_start_tick = -1;
		if (stop_tick <= start_tick)
			return false;

		// <film>_clip_<mm>-<ss>.film beside the film.
		std::string source = g_playback.get_path();
		std::string base = source.substr(0, source.size() - 5);
		char suffix[32];
		long seconds = start_tick / film_tick_rate();
		sprintf_s(suffix, "_clip_%02ld-%02ld", seconds / 60, seconds % 60);
		std::string clip = base + suffix + ".film";
		for (int n = 2; GetFileAttributesA(clip.c_str()) != INVALID_FILE_ATTRIBUTES; n++)
			clip = base + suffix + "_" + std::to_string(n) + ".film";

		if (!c_saved_film::write_clip(source.c_str(), clip.c_str(), start_tick, stop_tick))
		{
			print("Film: could not save the clip");
			return false;
		}
		print("Film: clip saved: %s (%ld seconds)", clip.c_str(), (stop_tick - start_tick) / film_tick_rate());
		return true;
	}

	void ApplyAll()
	{
		Hook(0x00441F90 - 0x00400000, reinterpret_cast<void *>(film_record_update_hook)).Apply();
		Hook(0x00441CD0 - 0x00400000, reinterpret_cast<void *>(simulation_must_close_saved_film_hook)).Apply();
		Hook(0x0044275C - 0x00400000, reinterpret_cast<void *>(simulation_update_pregame_apply_hook), static_cast<__int32>(HookFlags::IsCall)).Apply();
		Hook(0x00505DD7 - 0x00400000, reinterpret_cast<void *>(simulation_update_hook), static_cast<__int32>(HookFlags::IsCall)).Apply();
		// game_time_update sets the game speed to the film manager's playback speed during
		// playback; with the manager stripped that became a constant 0, so films never
		// ran. Skip it (jz -> jmp) and leave the speed to Time.GameSpeed / Film.Speed.
		Patch(0x00565277 - 0x00400000, { 0xEB }).Apply();
		Hook(0x00A86C2F - 0x00400000, reinterpret_cast<void *>(chud_saved_film_state_hook)).Apply();
		Hook(0x004411B1 - 0x00400000, reinterpret_cast<void *>(build_update_out_of_sync_hook), static_cast<__int32>(HookFlags::IsCall)).Apply();
		Patches::Core::OnShutdown([]()
		{
			stop_recording();
			g_playback.close();
		});
		ApplyControlPad();
		ApplyReplication();
		ApplyTheater();
	}
}

// Called from the ElModules constructor with the other modules.
void RegisterSavedFilmModule()
{
	static SavedFilms::ModuleSavedFilm module;
}
