#include "SavedFilms/saved_film.hpp"
#include "SavedFilms/saved_film_manager.hpp"

#include "Patch.hpp"
#include "Patches/Core.hpp"
#include "Pointer.hpp"

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

// The theater lobby, reached from the main menu.
//
// c_main_menu_screen_widget::handle_list_item_chosen still sends gui::theater to the
// theater pregame lobby, and the menu's string list still has its text, but Halo
// Online's main menu datasource (ui\halox\main_menu\main_menu_list) dropped the
// element. It is put back after the tags load, after Forge (gui::mapeditor) as in
// Halo 3.
//
// The lobby's film browser (c_gui_saved_film_category_datasource for the categories,
// c_gui_saved_film_subitem_datasource for the films in one) listed films from the
// console's content catalogue and autosave queue, neither of which Halo Online has,
// and s_blf_saved_film::copy_to_and_validate, which reads a chosen film's
// game_options, was compiled out. As in ManagedDonkey's gui_selected_items_saved_film.cpp,
// the categories are Halo 3's, the films come from the films folder, and a chosen
// film's details are read from its file.

namespace SavedFilms
{
	namespace
	{
		auto const tag_iterator_new = reinterpret_cast<void (*)(void *, unsigned long)>(0x005033E0);
		auto const tag_iterator_next = reinterpret_cast<long (*)(void *)>(0x00503400);
		auto const tag_get = reinterpret_cast<void *(*)(unsigned long, long)>(0x00503370);

		long const k_global_name = 0x2AA;
		long const k_gui_main_menu = 0x10083;
		long const k_gui_mapeditor = 0x1007B;
		long const k_gui_theater = 0x1007C;

		struct s_tag_block
		{
			long count;
			void *address;
			long definition;
		};
		static_assert(sizeof(s_tag_block) == 0xC, "Invalid s_tag_block size");

		struct s_string_id_data_nugget
		{
			long name;
			long value;
		};

		// 'dsrc' (ManagedDonkey's s_datasource_definition): name, then the elements.
		struct s_datasource_element
		{
			s_tag_block integer_nuggets;
			s_tag_block text_nuggets;
			s_tag_block string_id_nuggets;
			long submenu_control_name;
		};
		static_assert(sizeof(s_datasource_element) == 0x28, "Invalid s_datasource_element size");

		long const k_datasource_name = 0x0;
		long const k_datasource_elements = 0x10;

		long const k_datasource_elements_max = 32;
		s_datasource_element g_main_menu_elements[k_datasource_elements_max];
		s_string_id_data_nugget g_theater_nuggets[] = { { k_global_name, k_gui_theater } };

		// The pregame lobbies' Switch Lobby list (ui\halox\pregame_lobby\switch_lobby\lobbies)
		// dropped Theater too, though c_gui_screen_pregame_switch_lobby still handles it
		// and its strings still have its name and description; from the theater lobby
		// the list opened focused on the missing element, which froze the game.
		long const k_gui_switch_lobby = 0x102BE;
		long const k_global_description = 0x2AC;
		long const k_switch_lobby_theater_description = 0x428E;
		s_datasource_element g_switch_lobby_elements[k_datasource_elements_max];
		s_string_id_data_nugget g_switch_lobby_theater_nuggets[] = { { k_global_name, k_gui_theater }, { k_global_description, k_switch_lobby_theater_description } };

		long element_name(s_datasource_element const &element)
		{
			auto const *nuggets = static_cast<s_string_id_data_nugget const *>(element.string_id_nuggets.address);
			for (long index = 0; index < element.string_id_nuggets.count; index++)
			{
				if (nuggets[index].name == k_global_name)
					return nuggets[index].value;
			}
			return -1;
		}

		// Adds a Theater element (its string id nuggets as given) after Forge's; returns
		// whether it did.
		bool add_theater_element(unsigned char *datasource, s_datasource_element *storage, s_string_id_data_nugget *nuggets, long nugget_count)
		{
			s_tag_block &elements = *reinterpret_cast<s_tag_block *>(datasource + k_datasource_elements);
			if (elements.count <= 0 || elements.count >= k_datasource_elements_max || elements.address == storage)
				return false;

			auto const *old_elements = static_cast<s_datasource_element const *>(elements.address);
			long insert_at = elements.count;
			for (long index = 0; index < elements.count; index++)
			{
				long name = element_name(old_elements[index]);
				if (name == k_gui_theater)
					return false;
				if (name == k_gui_mapeditor)
					insert_at = index + 1;
			}

			s_datasource_element theater = {};
			theater.integer_nuggets.definition = old_elements[0].integer_nuggets.definition;
			theater.text_nuggets.definition = old_elements[0].text_nuggets.definition;
			theater.string_id_nuggets = { nugget_count, nuggets, old_elements[0].string_id_nuggets.definition };

			memcpy(storage, old_elements, insert_at * sizeof(s_datasource_element));
			storage[insert_at] = theater;
			memcpy(storage + insert_at + 1, old_elements + insert_at, (elements.count - insert_at) * sizeof(s_datasource_element));

			elements.address = storage;
			elements.count++;
			return true;
		}

		// A list's background is sized to the rows it had: a bitmap in the list's screen
		// whose bottom edge is the bottom of the list's last row grows by a row, for the
		// Theater row added to it. (s_screen_widget_definition: group blocks +0x5C;
		// s_group_widget_block: list blocks +0x3C, bitmap blocks +0x54; s_list_widget_block:
		// bounds +0x1C, datasource name +0x3C, list items +0x54 (0x30 each, bounds +0xC);
		// s_bitmap_widget_block: bounds +0x1C, both 0x6C; bounds are top, left, bottom, right.)
		long const k_screen_group_blocks = 0x5C;
		long const k_group_block_size = 0x6C;
		long const k_group_list_blocks = 0x3C;
		long const k_group_bitmap_blocks = 0x54;
		long const k_list_block_size = 0x80;
		long const k_list_bounds = 0x1C;
		long const k_list_datasource_name = 0x3C;
		long const k_list_items = 0x54;
		long const k_list_item_size = 0x30;
		long const k_list_item_bounds = 0xC;
		long const k_bitmap_block_size = 0x6C;
		long const k_bitmap_bounds = 0x1C;

		void grow_list_backgrounds(long datasource_name, long old_rows)
		{
			unsigned char iterator[20];
			tag_iterator_new(iterator, 'scn3');
			for (long tag_index; (tag_index = tag_iterator_next(iterator)) != -1; )
			{
				auto *screen = static_cast<unsigned char *>(tag_get('scn3', tag_index));
				if (!screen)
					continue;
				s_tag_block const &groups = *reinterpret_cast<s_tag_block *>(screen + k_screen_group_blocks);
				for (long group = 0; groups.address && group < groups.count; group++)
				{
					auto *group_block = static_cast<unsigned char *>(groups.address) + group * k_group_block_size;
					s_tag_block const &lists = *reinterpret_cast<s_tag_block *>(group_block + k_group_list_blocks);
					for (long list = 0; lists.address && list < lists.count; list++)
					{
						auto *list_block = static_cast<unsigned char *>(lists.address) + list * k_list_block_size;
						s_tag_block const &items = *reinterpret_cast<s_tag_block *>(list_block + k_list_items);
						if (*reinterpret_cast<long *>(list_block + k_list_datasource_name) != datasource_name || !items.address || items.count < 2)
							continue;
						auto const *item_tops = static_cast<unsigned char const *>(items.address) + k_list_item_bounds;
						short row_height = *reinterpret_cast<short const *>(item_tops + k_list_item_size) - *reinterpret_cast<short const *>(item_tops);
						short last_row_bottom = short(*reinterpret_cast<short *>(list_block + k_list_bounds) + old_rows * row_height - 1);
						if (row_height <= 0)
							continue;

						for (long other_group = 0; other_group < groups.count; other_group++)
						{
							auto *other = static_cast<unsigned char *>(groups.address) + other_group * k_group_block_size;
							s_tag_block const &bitmaps = *reinterpret_cast<s_tag_block *>(other + k_group_bitmap_blocks);
							for (long bitmap = 0; bitmaps.address && bitmap < bitmaps.count; bitmap++)
							{
								short *bounds = reinterpret_cast<short *>(static_cast<unsigned char *>(bitmaps.address) + bitmap * k_bitmap_block_size + k_bitmap_bounds);
								if (bounds[2] == last_row_bottom)
									bounds[2] += row_height;
							}
						}
					}
				}
			}
		}

		void main_menu_add_theater(char const *)
		{
			unsigned char iterator[20];
			tag_iterator_new(iterator, 'dsrc');
			for (long tag_index; (tag_index = tag_iterator_next(iterator)) != -1; )
			{
				auto *datasource = static_cast<unsigned char *>(tag_get('dsrc', tag_index));
				if (!datasource)
					continue;
				long name = *reinterpret_cast<long *>(datasource + k_datasource_name);
				long old_rows = reinterpret_cast<s_tag_block *>(datasource + k_datasource_elements)->count;
				if (name == k_gui_main_menu)
					add_theater_element(datasource, g_main_menu_elements, g_theater_nuggets, _countof(g_theater_nuggets));
				else if (name == k_gui_switch_lobby && add_theater_element(datasource, g_switch_lobby_elements, g_switch_lobby_theater_nuggets, _countof(g_switch_lobby_theater_nuggets)))
					grow_list_backgrounds(k_gui_switch_lobby, old_rows);
			}
		}
	}

	namespace
	{
		/* ---------- film browser */

		long const k_gui_recent_films = 0x10306;
		long const k_gui_recent_films_description = 0x10307;
		long const k_gui_film_clip = 0x10226;
		long const k_gui_film_clip_description = 0x10227;
		long const k_gui_multiplayer_film = 0x1022C;
		long const k_gui_multiplayer_film_description = 0x1022D;
		long const k_gui_editor_film = 0x1022E;
		long const k_gui_editor_film_description = 0x1022F;

		enum
		{
			_saved_film_category_recent_films = 1,
			_saved_film_category_film_clips = 2,
			_saved_film_category_multiplayer = 4,
			_saved_film_category_editor = 5,

			_special_item_type_recent = 0,
			_special_item_type_category = 2,

			_saved_game_film = 0xB,
			_saved_game_film_clip = 0xC,

			_gui_stored_item_location_saved_game_file = 1,
		};

		// c_gui_saved_film_category_datasource
		unsigned long const k_category_datasource_initialize_slot = 0x0169E6D8; // vtable 0x169E6D4 +4
		auto const category_datasource_initialize = reinterpret_cast<bool(__thiscall *)(void *, long)>(0x00ADD210);
		auto const category_datasource_add_category = reinterpret_cast<void(__thiscall *)(void *, long, long, long, long)>(0x00ADC7D0);
		long const k_category_datasource_count = 0x144C;

		// c_gui_saved_film_subitem_datasource
		unsigned long const k_subitem_update_autosave_enumeration = 0x00ADD3E0;
		unsigned long const k_subitem_update_content_enumeration = 0x00ADD560;
		auto const subitem_film_matches_category = reinterpret_cast<bool(__thiscall *)(void *, void const *)>(0x00ADC8F0);
		auto const saved_film_sort_proc = reinterpret_cast<int(__cdecl *)(void const *, void const *)>(0x00ADD2E0);
		long const k_subitem_saved_films = 0x110;
		long const k_subitem_saved_film_count = 0x19B98;
		long const k_subitem_category = 0x19B9C;
		long const k_subitem_controller_index = 0x19BA0;
		long const k_subitem_enumeration_complete = 0x19BA4;
		long const k_saved_films_shown_max = 151;

		// c_gui_saved_film_selected_item
		auto const saved_film_selected_item_constructor = reinterpret_cast<void *(__thiscall *)(void *, void const *, long, long, long, void const *, long, bool, bool)>(0x00ADC2F0);
		auto const saved_film_selected_item_assign = reinterpret_cast<void *(__thiscall *)(void *, void const *)>(0x00ADC640);
		unsigned long const k_saved_film_selected_item_get_film_details = 0x00ADCB00;
		long const k_saved_film_selected_item_size = 0x2B8;
		long const k_saved_film_selected_item_file_path = 0x194 + 0x8; // m_file_reference.path

		// s_file_reference
		auto const file_reference_create = reinterpret_cast<void(__cdecl *)(void *, unsigned short)>(0x0052A9A0);
		long const k_file_reference_size = 0x110;
		long const k_file_reference_flags = 0x4;
		long const k_file_reference_path = 0x8;
		long const k_file_reference_path_size = 256;
		unsigned short const k_file_reference_flag_has_name = 1;

		// game_options
		long const k_game_options_size = 0x24B48;
		long const k_game_options_tick_rate = 0x6;
		long const k_game_options_map_id = 0x20;
		long const k_game_options_scenario_path = 0x24;
		long const k_game_options_game_engine_index = 0x32C;
		long const k_game_engine_type_none = 0;

		struct s_saved_game_item_metadata
		{
			unsigned long long unique_id;
			wchar_t display_name[16];
			char description[128];
			char author[16];
			long file_type;
			bool author_is_xuid_online;
			unsigned char pad0[3];
			unsigned long long author_id;
			unsigned long long size_in_bytes;
			unsigned long long date;
			long length_seconds;
			long campaign_id;
			long map_id;
			long game_engine_index;
			long campaign_difficulty;
			unsigned char campaign_insertion_point;
			bool campaign_survival_enabled;
			unsigned short pad;
			unsigned long long game_id;
		};
		static_assert(sizeof(s_saved_game_item_metadata) == 0xF8, "Invalid s_saved_game_item_metadata size");

		bool __fastcall category_datasource_initialize_hook(unsigned char *datasource, void *, long name)
		{
			if (!category_datasource_initialize(datasource, name))
				return false;

			// The release build's own categories are campaign and survival films.
			*reinterpret_cast<long *>(datasource + k_category_datasource_count) = 0;
			category_datasource_add_category(datasource, k_gui_recent_films, k_gui_recent_films_description, _saved_film_category_recent_films, _special_item_type_recent);
			category_datasource_add_category(datasource, k_gui_film_clip, k_gui_film_clip_description, _saved_film_category_film_clips, _special_item_type_category);
			category_datasource_add_category(datasource, k_gui_multiplayer_film, k_gui_multiplayer_film_description, _saved_film_category_multiplayer, _special_item_type_category);
			category_datasource_add_category(datasource, k_gui_editor_film, k_gui_editor_film_description, _saved_film_category_editor, _special_item_type_category);
			return true;
		}

		unsigned long long hash_name(char const *name)
		{
			unsigned long long hash = 14695981039346656037ull;
			for (; *name; name++)
				hash = (hash ^ (unsigned char)*name) * 1099511628211ull;
			return hash;
		}

		bool film_metadata(std::string const &path, char const *file_name, s_saved_game_item_metadata *metadata)
		{
			c_saved_film film;
			if (!film.open_for_read(path.c_str()))
				return false;
			auto const *options = reinterpret_cast<unsigned char const *>(film.get_game_options());

			memset(metadata, 0, sizeof(*metadata));
			metadata->unique_id = hash_name(file_name);
			metadata->file_type = film.is_snippet() ? _saved_game_film_clip : _saved_game_film;
			metadata->date = film.get_recorded_time();
			metadata->campaign_id = -1;
			metadata->map_id = *reinterpret_cast<long const *>(options + k_game_options_map_id);
			metadata->game_engine_index = *reinterpret_cast<long const *>(options + k_game_options_game_engine_index);
			if (metadata->game_engine_index < 0)
				metadata->game_engine_index = k_game_engine_type_none;
			short tick_rate = *reinterpret_cast<short const *>(options + k_game_options_tick_rate);
			metadata->length_seconds = (film.get_length_in_ticks() - film.get_snippet_start_tick()) / (tick_rate > 0 ? tick_rate : 60);

			WIN32_FILE_ATTRIBUTE_DATA attributes;
			if (GetFileAttributesExA(path.c_str(), GetFileExInfoStandard, &attributes))
				metadata->size_in_bytes = ((unsigned long long)attributes.nFileSizeHigh << 32) | attributes.nFileSizeLow;

			// The title holds 15 characters: the map and the time it was recorded.
			char const *scenario = reinterpret_cast<char const *>(options + k_game_options_scenario_path);
			char const *map = strrchr(scenario, '\\');
			map = map ? map + 1 : scenario;
			char title[64];
			time_t recorded = time_t(metadata->date);
			tm local = {};
			if (recorded && localtime_s(&local, &recorded) == 0)
				sprintf_s(title, "%.9s %02d:%02d", map, local.tm_hour, local.tm_min);
			else
				sprintf_s(title, "%.15s", map);
			for (long index = 0; index < 15 && title[index]; index++)
				metadata->display_name[index] = wchar_t((unsigned char)title[index]);

			strncpy_s(metadata->description, file_name, _TRUNCATE);
			return true;
		}

		void __fastcall subitem_update_enumeration_hook(unsigned char *datasource, void *)
		{
			bool &enumeration_complete = *reinterpret_cast<bool *>(datasource + k_subitem_enumeration_complete);
			if (enumeration_complete)
				return;
			enumeration_complete = true;

			long &count = *reinterpret_cast<long *>(datasource + k_subitem_saved_film_count);
			long category = *reinterpret_cast<long *>(datasource + k_subitem_category);
			long controller_index = *reinterpret_cast<long *>(datasource + k_subitem_controller_index);
			unsigned char *films = datasource + k_subitem_saved_films;

			std::string directory = get_films_directory();
			WIN32_FIND_DATAA data;
			HANDLE find = FindFirstFileA((directory + "\\*.film").c_str(), &data);
			if (find == INVALID_HANDLE_VALUE)
				return;
			do
			{
				if (count >= k_saved_films_shown_max)
					break;
				if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					continue;

				std::string path = directory + "\\" + data.cFileName;
				if (path.size() >= size_t(k_file_reference_path_size))
					continue;
				s_saved_game_item_metadata metadata;
				if (!film_metadata(path, data.cFileName, &metadata) || !subitem_film_matches_category(datasource, &metadata))
					continue;

				unsigned char file[k_file_reference_size];
				file_reference_create(file, 0xFFFF);
				strcpy_s(reinterpret_cast<char *>(file + k_file_reference_path), k_file_reference_path_size, path.c_str());
				*reinterpret_cast<unsigned short *>(file + k_file_reference_flags) |= k_file_reference_flag_has_name;

				unsigned char item[k_saved_film_selected_item_size];
				bool is_new = metadata.date + 7 * 24 * 60 * 60 > (unsigned long long)time(nullptr);
				saved_film_selected_item_constructor(item, &metadata, category, _gui_stored_item_location_saved_game_file, controller_index, file, 0, false, is_new);
				saved_film_selected_item_assign(films + count * k_saved_film_selected_item_size, item);
				count++;
			} while (FindNextFileA(find, &data));
			FindClose(find);

			qsort(films, count, k_saved_film_selected_item_size, saved_film_sort_proc);
		}

		bool __fastcall saved_film_selected_item_get_film_details_hook(unsigned char const *item, void *, void *options, long *out_length_in_ticks, long *out_start_tick)
		{
			char const *path = reinterpret_cast<char const *>(item + k_saved_film_selected_item_file_path);
			c_saved_film film;
			if (!film.open_for_read(path))
				return false;
			memcpy(options, film.get_game_options(), k_game_options_size);
			if (out_length_in_ticks)
				*out_length_in_ticks = film.get_length_in_ticks();
			if (out_start_tick)
				*out_start_tick = film.get_snippet_start_tick();
			return true;
		}

		/* ---------- choosing and starting a film */

		// c_gui_pregame_setup_manager::set_selected_item reads a chosen film's details,
		// then - its film case cut down in the release build - always gives the squad an
		// invalid film and posts gui_alert::pregame_selected_film_invalid. The theater
		// lobby's two calls (choosing a film, and the lobby picking the most recent one)
		// handle films here, as ManagedDonkey's set_selected_item_type_film does.
		auto const set_selected_item = reinterpret_cast<void(__thiscall *)(void *, long, void const *, bool, long)>(0x00AA7DB0);
		unsigned long const k_set_selected_item_calls[] = { 0x00B02DD1, 0x00B040A6 };
		auto const user_interface_squad_set_film = reinterpret_cast<bool (*)(void const *)>(0x00A836F0);
		auto const user_interface_squad_set_saved_film_game_options = reinterpret_cast<bool (*)(long, long, void const *)>(0x00A83C90);
		auto const user_interface_squad_set_map_variant = reinterpret_cast<bool (*)(void const *)>(0x00A83AB0);
		auto const user_interface_squad_exists = reinterpret_cast<bool (*)()>(0x00A82980);
		auto const user_interface_squad_local_peer_is_leader = reinterpret_cast<bool (*)()>(0x00A83520);
		auto const user_interface_squad_get_ui_game_mode = reinterpret_cast<long (*)()>(0x00A83180);
		auto const user_interface_get_session_game_mode = reinterpret_cast<long (*)()>(0x00A80970);
		long const k_gui_game_setup_mode_theater = 4;
		long const k_session_game_mode_pregame = 2;
		long const k_game_options_map_variant = 0x590;
		auto const window_manager_get = reinterpret_cast<void *(*)()>(0x00AAD930);
		auto const window_manager_get_screen_by_screen_index = reinterpret_cast<void *(__thiscall *)(void *, long)>(0x00AAB5B0);
		auto const screen_widget_transition_out = reinterpret_cast<void(__thiscall *)(void *, long)>(0x00AB2830);

		long const k_gui_selection_type_film = 5;
		long const k_transition_out_normal = 0;
		long const k_saved_film_category_invalid = 7;

		// c_gui_selected_item / c_gui_saved_film_selected_item
		long const k_selected_item_selection_type = 0x8;
		long const k_selected_item_metadata_display_name = 0x18 + 0x8; // s_ui_saved_game_item_metadata
		long const k_selected_item_metadata_length_seconds = 0x18 + 0x158;
		long const k_selected_item_metadata_map_id = 0x18 + 0x160;
		long const k_saved_film_selected_item_category = 0x2B0;

		struct s_saved_film_description
		{
			long category;
			long campaign_id;
			long map_id;
			short campaign_insertion_point;
			bool campaign_survival_enabled;
			unsigned char pad;
			long difficulty;
			wchar_t film_path[256];
			wchar_t film_name[128];
			long controller_index;
			long length_seconds;
		};
		static_assert(sizeof(s_saved_film_description) == 0x31C, "Invalid s_saved_film_description size");

		auto const network_life_cycle_session_get_film = reinterpret_cast<s_saved_film_description const *(*)()>(0x00435250);

		std::string g_selected_film_path; // the last film chosen, should the session's not say

		void dispose_screen(long screen_index)
		{
			if (screen_index == -1)
				return;
			if (void *screen = window_manager_get_screen_by_screen_index(window_manager_get(), screen_index))
				screen_widget_transition_out(screen, k_transition_out_normal);
		}

		long const k_saved_film_category_film_clips = 2;
		long const k_saved_film_category_multiplayer = 4;
		long const k_saved_film_category_editor = 5;
		long const k_game_engine_type_sandbox = 5;

		std::string g_applied_mod_hash; // the mod loaded when the squad was last given the film
		bool g_applied_with_mod_ready = false;

		// Gives the squad the film, its game options and its map: the theater lobby can
		// start once it has all three (user_interface_session_parameters_are_valid_for_ui_game_mode).
		bool set_squad_film(char const *path)
		{
			static unsigned char options[k_game_options_size];
			char const *name = strrchr(path, '\\');
			name = name ? name + 1 : path;

			s_saved_game_item_metadata metadata;
			c_saved_film film;
			if (!film_metadata(path, name, &metadata) || !film.open_for_read(path))
				return false;
			memcpy(options, film.get_game_options(), k_game_options_size);

			s_saved_film_description description = {};
			description.category = metadata.file_type == _saved_game_film_clip ? k_saved_film_category_film_clips
				: metadata.game_engine_index == k_game_engine_type_sandbox ? k_saved_film_category_editor
				: k_saved_film_category_multiplayer;
			description.campaign_id = -1;
			description.map_id = metadata.map_id;
			// The squad takes only a film with no controller (user_interface_squad_set_film_internal).
			description.controller_index = -1;
			description.length_seconds = metadata.length_seconds;
			MultiByteToWideChar(CP_ACP, 0, path, -1, description.film_path, _countof(description.film_path) - 1);
			wcsncpy_s(description.film_name, metadata.display_name, 15);

			if (!user_interface_squad_set_film(&description))
				return false;
			user_interface_squad_set_saved_film_game_options(film.get_length_in_ticks(), film.get_snippet_start_tick(), options);
			user_interface_squad_set_map_variant(options + k_game_options_map_variant);
			g_applied_mod_hash = get_loaded_mod_hash();
			return true;
		}

		void select_film(unsigned char const *item, long source_screen_index_to_dispose)
		{
			char const *path = reinterpret_cast<char const *>(item + k_saved_film_selected_item_file_path);
			g_selected_film_path = path;

			// A film from a mod package needs that mod, which loading passes on to the
			// squad; update_theater gives the squad the film again once it has loaded.
			g_applied_with_mod_ready = prepare_film_mod(path);
			if (set_squad_film(path))
			{
				dispose_screen(source_screen_index_to_dispose);
				return;
			}

			s_saved_film_description invalid_film = {};
			invalid_film.category = k_saved_film_category_invalid;
			user_interface_squad_set_film(&invalid_film);
			g_selected_film_path.clear();
		}

		bool squad_has_film(char const *path)
		{
			s_saved_film_description const *film = network_life_cycle_session_get_film();
			if (!film || film->category == 0 || film->category == k_saved_film_category_invalid)
				return false;
			wchar_t wide_path[MAX_PATH] = {};
			MultiByteToWideChar(CP_ACP, 0, path, -1, wide_path, _countof(wide_path) - 1);
			return _wcsicmp(film->film_path, wide_path) == 0;
		}

		void __fastcall set_selected_item_hook(void *manager, void *, long controller_index, unsigned char const *item, bool selected_from_recent_list, long source_screen_index_to_dispose)
		{
			if (item && *reinterpret_cast<long const *>(item + k_selected_item_selection_type) == k_gui_selection_type_film)
			{
				select_film(item, source_screen_index_to_dispose);
				return;
			}
			set_selected_item(manager, controller_index, item, selected_from_recent_list, source_screen_index_to_dispose);
		}

		// Starting the lobby's game: c_life_cycle_state_handler_in_game::begin_load_map
		// builds a theater game from the session's saved_film_game_options. The host
		// opened the film there through the saved film manager, which the release build
		// stripped - leaving "host failed to open saved film" and no game - so the host
		// takes the clients' path (jz -> jmp at 0x491C52), and its main_game_change call
		// opens the session's film and sets the options up as Film.Play does.
		unsigned long const k_begin_load_map_host_film_check = 0x00491C52;
		unsigned long const k_host_update_countdown_film_case = 0x0048F7C8 + 3 * 4; // jpt_48F67F[_network_game_start_mode_film]
		unsigned long const k_host_update_countdown_start_game = 0x0048F7B8; // push _network_session_mode_setup; session_mode.set
		unsigned long const k_begin_load_map_main_game_change_call = 0x00491F96;
		auto const main_game_change = reinterpret_cast<void (*)(void const *)>(0x00566E70);
		long const k_game_options_game_playback = 0x130;

		void __cdecl begin_load_map_main_game_change_hook(unsigned char *options)
		{
			if (*reinterpret_cast<unsigned short const *>(options + k_game_options_game_playback) != 0)
			{
				std::string path = g_selected_film_path;
				if (s_saved_film_description const *film = network_life_cycle_session_get_film())
				{
					char film_path[MAX_PATH] = {};
					if (WideCharToMultiByte(CP_ACP, 0, film->film_path, -1, film_path, sizeof(film_path) - 1, nullptr, nullptr) > 1)
						path = film_path;
				}
				begin_session_film(options, path.c_str());
			}
			main_game_change(options);
		}
	}

	// In the theater lobby, keeps the squad's film the one chosen: once the film's mod
	// has loaded (ElDewrito restores the lobby's last setup when the mod changes), or
	// if the squad's film is otherwise reset.
	void update_theater()
	{
		if (g_selected_film_path.empty())
			return;
		static DWORD last_update = 0;
		DWORD now = GetTickCount();
		if (now - last_update < 250)
			return;
		last_update = now;

		if (!user_interface_squad_exists() || user_interface_get_session_game_mode() != k_session_game_mode_pregame
			|| user_interface_squad_get_ui_game_mode() != k_gui_game_setup_mode_theater || !user_interface_squad_local_peer_is_leader())
			return;

		char const *path = g_selected_film_path.c_str();
		bool has_film = squad_has_film(path);
		bool same_mod = g_applied_mod_hash == get_loaded_mod_hash();
		if (has_film && same_mod && g_applied_with_mod_ready)
			return;

		bool mod_ready = prepare_film_mod(path);
		if ((!has_film || !same_mod || (mod_ready && !g_applied_with_mod_ready)) && set_squad_film(path))
			g_applied_with_mod_ready = mod_ready;
	}

	void ApplyTheater()
	{
		Patches::Core::OnMapLoaded(main_menu_add_theater);

		Pointer(k_category_datasource_initialize_slot).Write(reinterpret_cast<unsigned long>(&category_datasource_initialize_hook));
		Hook(k_subitem_update_autosave_enumeration - 0x00400000, reinterpret_cast<void *>(&subitem_update_enumeration_hook)).Apply();
		Hook(k_subitem_update_content_enumeration - 0x00400000, reinterpret_cast<void *>(&subitem_update_enumeration_hook)).Apply();
		Hook(k_saved_film_selected_item_get_film_details - 0x00400000, reinterpret_cast<void *>(&saved_film_selected_item_get_film_details_hook)).Apply();
		for (unsigned long call : k_set_selected_item_calls)
			Hook(call - 0x00400000, reinterpret_cast<void *>(&set_selected_item_hook), static_cast<__int32>(HookFlags::IsCall)).Apply();
		// c_life_cycle_state_handler_pre_game::host_update_countdown's film case, where the
		// host checked the film with the stripped saved film manager, became "film
		// invalid, clearing and stopping countdown". Its jump table entry goes to the
		// custom game case's end instead, which starts the game (session mode setup).
		Pointer(k_host_update_countdown_film_case).Write<unsigned long>(k_host_update_countdown_start_game);
		Patch(k_begin_load_map_host_film_check - 0x00400000, { 0xEB }).Apply();
		Hook(k_begin_load_map_main_game_change_call - 0x00400000, reinterpret_cast<void *>(&begin_load_map_main_game_change_hook), static_cast<__int32>(HookFlags::IsCall)).Apply();
	}
}
