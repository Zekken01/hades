/* ---------- headers */

#include "Blam/main/levels.hpp"
#include "hades/hades.h"

#include "Blam/async/async.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/cseries/static_string.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/multithreading/synchronization/critical_section.hpp"
#include "Blam/saved_games/blf.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "ThirdParty/rapidjson/document.h"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <limits>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

struct c_async_completion_flag;
struct s_blf_campaign;
struct s_blf_map_information;
struct s_data_array;
struct s_data_iterator;
struct s_datum;
struct s_file_reference;
struct s_level_datum;
struct s_levels_globals;

/* ---------- constants */

/* ---------- definitions */

// s_levels_globals is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

extern s_file_reference *(*const file_reference_create_from_path)(s_file_reference *, char const *, bool);  // hades: added for 0x10F07550
extern char *(*const file_reference_get_name)(s_file_reference *, c_flags<enum e_file_reference_flags,long>, char *, long);  // hades: added for 0x10F07550

const bool levels_find_map_by_name_internal(s_data_array *level_data_array, char const *name, s_level_datum *out_level);  // hades: added for 0X10F07490

extern void (*const critical_section_enter)(e_critical_section);  // hades: added for 0X10F06B60
extern void (*const critical_section_leave)(e_critical_section);  // hades: added for 0X10F06B60
extern void (*const data_delete_all)(s_data_array *);  // hades: added for 0X10F06B60

extern void levels_yield_until_enumerate_done();
extern bool const levels_find_map_by_name_internal(s_data_array *level_data, char const *name, s_level_datum *out_level);
extern bool levels_find_level_by_map_id_internal(s_data_array *level_array, long map_id, s_level_datum *out_level);
extern bool levels_find_level_by_map_id(long map_id, s_level_datum *out_level);
extern void levels_iterate_multiplayer_maps(std::function<void __cdecl(s_level_datum *)> func);
extern void levels_iterate_campaign_maps(std::function<void __cdecl(s_level_datum *)> func);
extern bool levels_find_by_path_internal(s_data_array *level_data, char const *path, s_level_datum *out_level);
extern bool levels_find_map_by_name(char const *name, s_level_datum *out_level);
extern bool levels_find_map_by_path(char const *path, s_level_datum *out_level);
extern void levels_close_all_multiplayer_in_directory(char const *directory);
extern void levels_close_map_internal(s_data_array *level_data, long map_id);
extern void levels_close_all_campaigns();
extern void levels_close_multiplayer_map(long map_id);
extern void levels_close_campaign_map(long map_id);
extern void levels_clear_and_enumerate_async();

/* ---------- globals */

extern void (*const data_iterator_new)(s_data_iterator *, s_data_array const *); // 0x11248884
extern void (*const data_iterator_new)(s_data_iterator *, s_data_array const *);  // hades: added for 0X10F06C30
extern void (*const datum_delete)(s_data_array *, long);  // hades: added for 0X10F06C30
extern void (*const data_iterator_new)(s_data_iterator *, s_data_array const *);  // hades: added for 0X10F06EB0
extern void (*const datum_delete)(s_data_array *, long);  // hades: added for 0X10F06EB0
extern void (*const data_iterator_new)(s_data_iterator *, s_data_array const *);  // hades: added for 0X10F070A0

extern bool (*const levels_try_and_get_multiplayer_map)(long, s_level_datum *); // 0x11249EA0
extern bool (*const levels_try_and_get_campaign_map)(long, s_level_datum *); // 0x11249EA4
extern void (*const levels_add_map_internal)(s_blf_map_information *, bool, char const *, bool); // 0x11249E8C
extern bool (*const levels_add_campaign)(s_file_reference *, wchar_t *, bool); // 0x11249E94
extern bool (*const levels_add_campaign_internal)(s_blf_campaign *, bool, char const *, bool); // 0x11249E98
extern void (*const levels_add_map)(s_file_reference *, char *); // 0x11249E9C
extern void (*const levels_get_map_name)(unsigned long, unsigned long, char *, __int32); // 0x11249E90

/* ---------- private variables */

namespace hades_file_local
{
	extern s_levels_globals *g_level_globals; // 0x11359B84
}
using namespace hades_file_local;
/* ---------- public code */

void levels_yield_until_enumerate_done() // 0x10F07D10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_yield_until_enumerate_done@@YAXXZ");

	if (g_level_globals->enumeration_async_task_id != -1)
	{
		((void(__cdecl *const)(c_async_completion_flag *, bool, bool))0x508a40)((c_async_completion_flag *)0x189ece4, false, false);
	}
}

bool const levels_find_map_by_name_internal(s_data_array *level_data, char const *name, s_level_datum *out_level) // 0x10F07550
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_find_map_by_name_internal@@YA?B_NPAUs_data_array@@PBDPAUs_level_datum@@@Z");

	*out_level = {};
	bool result = false;
	critical_section_enter(_critical_section_levels);
	s_data_iterator iterator;
	data_iterator_new(&iterator, level_data);
	while (s_level_datum *level = (s_level_datum *)data_iterator_next(&iterator))
	{
		s_file_reference file_reference;
		char filename[256];
		file_reference_create_from_path(&file_reference, level->file_path, false);
		file_reference_get_name(&file_reference, 4, filename, 256);
		if (!_stricmp(filename, name))
		{
			memcpy(out_level, level, sizeof(s_level_datum));
			result = true;
			break;
		}
	}
	critical_section_leave(_critical_section_levels);
	return result;
}

bool levels_find_level_by_map_id_internal(s_data_array *level_array, long map_id, s_level_datum *out_level) // 0x10F07350
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_find_level_by_map_id_internal@@YA_NPAUs_data_array@@JPAUs_level_datum@@@Z");

	s_data_iterator iterator;
	data_iterator_new(&iterator, level_array);
	while (s_level_datum *level = (s_level_datum *)data_iterator_next(&iterator))
	{
		if (level->map_id == map_id)
		{
			memcpy(out_level, level, sizeof(s_level_datum));
			return true;
		}
	}
	return false;
}

bool levels_find_level_by_map_id(long map_id, s_level_datum *out_level) // 0x10F071F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_find_level_by_map_id@@YA_NJPAUs_level_datum@@@Z");

	critical_section_enter(_critical_section_levels);

	bool found = levels_find_level_by_map_id_internal(g_level_globals->multiplayer_levels, map_id, out_level)
		|| levels_find_level_by_map_id_internal(g_level_globals->campaign_levels, map_id, out_level);
	if (!found && ((s_level_datum *)g_level_globals->mainmenu_level)->map_id == map_id)
	{
		memcpy(out_level, g_level_globals->mainmenu_level, sizeof(s_level_datum));
		found = true;
	}

	critical_section_leave(_critical_section_levels);
	return found;
}

void levels_iterate_multiplayer_maps(std::function<void __cdecl(s_level_datum *)> func) // 0x10F07B60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_iterate_multiplayer_maps@@YAXV?$function@$$A6AXPAUs_level_datum@@@Z@std@@@Z");

	critical_section_enter(_critical_section_levels);
	s_data_iterator iterator;
	data_iterator_new(&iterator, g_level_globals->multiplayer_levels);
	while (s_level_datum *level = (s_level_datum *)data_iterator_next(&iterator))
		func(level);
	critical_section_leave(_critical_section_levels);
}

void levels_iterate_campaign_maps(std::function<void __cdecl(s_level_datum *)> func) // 0x10F079B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_iterate_campaign_maps@@YAXV?$function@$$A6AXPAUs_level_datum@@@Z@std@@@Z");

	critical_section_enter(_critical_section_levels);
	s_data_iterator iterator;
	data_iterator_new(&iterator, g_level_globals->campaign_levels);
	while (s_level_datum *level = (s_level_datum *)data_iterator_next(&iterator))
		func(level);
	critical_section_leave(_critical_section_levels);
}

bool levels_find_by_path_internal(s_data_array *level_data, char const *path, s_level_datum *out_level) // 0x10F070A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_find_by_path_internal@@YA_NPAUs_data_array@@PBDPAUs_level_datum@@@Z");

	s_data_iterator iterator;
	data_iterator_new(&iterator, level_data);
	while (s_level_datum *level = (s_level_datum *)data_iterator_next(&iterator))
	{
		if (!strcmp(level->file_path, path))
		{
			memcpy(out_level, level, sizeof(s_level_datum));
			return true;
		}
	}
	return false;
}

bool levels_find_map_by_name(char const *name, s_level_datum *out_level) // 0x10F07490
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_find_map_by_name@@YA_NPBDPAUs_level_datum@@@Z");

	return levels_find_map_by_name_internal(g_level_globals->multiplayer_levels, name, out_level)
		|| levels_find_map_by_name_internal(g_level_globals->campaign_levels, name, out_level);
}

bool levels_find_map_by_path(char const *path, s_level_datum *out_level) // 0x10F07890
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_find_map_by_path@@YA_NPBDPAUs_level_datum@@@Z");

	critical_section_enter(_critical_section_levels);
	bool result = levels_find_by_path_internal(g_level_globals->multiplayer_levels, path, out_level)
		|| levels_find_by_path_internal(g_level_globals->campaign_levels, path, out_level);
	critical_section_leave(_critical_section_levels);
	return result;
}

void levels_close_all_multiplayer_in_directory(char const *directory) // 0x10F06C30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_close_all_multiplayer_in_directory@@YAXPBD@Z");

	critical_section_enter(_critical_section_levels);

	s_static_string<256> safe_directory;
	safe_directory.set(directory);

	s_data_iterator iterator;
	data_iterator_new(&iterator, g_level_globals->multiplayer_levels);
	while (s_level_datum *level = (s_level_datum *)data_iterator_next(&iterator))
	{
		if (strstr(level->file_path, safe_directory.get_string()) == level->file_path)
		{
			datum_delete(g_level_globals->multiplayer_levels, iterator.current_index);
		}
	}

	critical_section_leave(_critical_section_levels);
}

void levels_close_map_internal(s_data_array *level_data, long map_id) // 0x10F06EB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_close_map_internal@@YAXPAUs_data_array@@J@Z");

	critical_section_enter(_critical_section_levels);
	s_data_iterator iterator;
	data_iterator_new(&iterator, level_data);
	while (s_level_datum *level = (s_level_datum *)data_iterator_next(&iterator))
	{
		if (level->map_id == map_id)
			datum_delete(level_data, iterator.current_index);
	}
	critical_section_leave(_critical_section_levels);
}

void levels_close_all_campaigns() // 0x10F06B60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_close_all_campaigns@@YAXXZ");

	critical_section_enter(_critical_section_levels);
	data_delete_all(g_level_globals->campaigns);
	critical_section_leave(_critical_section_levels);
}

void levels_close_multiplayer_map(long map_id) // 0x10F07040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_close_multiplayer_map@@YAXJ@Z");

	levels_close_map_internal(g_level_globals->multiplayer_levels, map_id);
}

void levels_close_campaign_map(long map_id) // 0x10F06E50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_close_campaign_map@@YAXJ@Z");

	levels_close_map_internal(g_level_globals->campaign_levels, map_id);
}

void levels_clear_and_enumerate_async() // 0x10F069F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_clear_and_enumerate_async@@YAXXZ");

	critical_section_enter(_critical_section_levels);
	data_delete_all(g_level_globals->campaigns);
	data_delete_all(g_level_globals->campaign_levels);
	data_delete_all(g_level_globals->campaign_insertions);
	data_delete_all(g_level_globals->multiplayer_levels);
	((void(*)())0x54AD80)();
	critical_section_leave(_critical_section_levels);
}

/* ---------- private code */

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
bool (*const levels_try_and_get_multiplayer_map)(long, s_level_datum *) = reinterpret_cast<decltype(levels_try_and_get_multiplayer_map)>(0x54CB00);
void (*const levels_get_map_name)(unsigned long, unsigned long, char *, __int32) = reinterpret_cast<decltype(levels_get_map_name)>(0x54C040);
bool (*const levels_try_and_get_campaign_map)(long, s_level_datum *) = reinterpret_cast<decltype(levels_try_and_get_campaign_map)>(0x54CAB0);
void (*const levels_add_map_internal)(s_blf_map_information *, bool, char const *, bool) = reinterpret_cast<decltype(levels_add_map_internal)>(0x54A6C0);
bool (*const levels_add_campaign_internal)(s_blf_campaign *, bool, char const *, bool) = reinterpret_cast<decltype(levels_add_campaign_internal)>(0x54A2A0);
void (*const levels_add_map)(s_file_reference *, char *) = reinterpret_cast<decltype(levels_add_map)>(0x54C530);
bool (*const levels_add_campaign)(s_file_reference *, wchar_t *, bool) = reinterpret_cast<decltype(levels_add_campaign)>(0x54C3C0);
namespace hades_file_local { s_levels_globals *g_level_globals = reinterpret_cast<s_levels_globals *>(0x189E2D4); }
