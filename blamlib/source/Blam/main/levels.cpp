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
	// procedure flags: nofpo
	// function call : void (*const)(c_async_completion_flag *, bool, bool)

	if (g_level_globals->enumeration_async_task_id != -1)
	{
		((void(__cdecl *const)(c_async_completion_flag *, bool, bool))0x508a40)((c_async_completion_flag *)0x189ece4, false, false);
	}
}

extern bool const _sub_10F07550(s_data_array *, char const *, s_level_datum *);
bool const levels_find_map_by_name_internal(s_data_array *level_data, char const *name, s_level_datum *out_level) // 0x10F07550
{
	mangled_x86(MANGLED_TODO, "?levels_find_map_by_name_internal@@YA?B_NPAUs_data_array@@PBDPAUs_level_datum@@@Z");
	// static ...; // 0x10F077C4
	// static ...; // 0x10F077A0
	// static ...; // 0x10F07798
	// s_data_array *level_data;
	// char const *name;
	// s_level_datum *out_level;
	// s_data_iterator iterator;
	// bool result;
	{
		// s_level_datum *level;
		{
			// char filename[256];
			// s_file_reference file_reference;
		}
	}
	// function call : void (*const)(e_critical_section)
	// function call : void (*const)(s_data_iterator *, s_data_array const *)
	// function call : s_datum *(*const)(s_data_iterator *)
	// function call : s_file_reference *(*const)(s_file_reference *, char const *, bool)
	// function call : char *(*const)(s_file_reference *, c_flags<enum e_file_reference_flags,long>, char *, long)
	// function call : void (*const)(e_critical_section)
	todo("implement");
	bool const __result = _sub_10F07550(level_data, name, out_level);
	return __result;
}

_extern bool _sub_10F07350(s_data_array *, long, s_level_datum *);
bool levels_find_level_by_map_id_internal(s_data_array *level_array, long map_id, s_level_datum *out_level) // 0x10F07350
{
	mangled_x86(MANGLED_TODO, "?levels_find_level_by_map_id_internal@@YA_NPAUs_data_array@@JPAUs_level_datum@@@Z");
	// static ...; // 0x10F07428
	// s_data_array *level_array;
	// long map_id;
	// s_level_datum *out_level;
	// s_data_iterator iterator;
	{
		// s_level_datum *level;
	}
	// function call : void (*const)(s_data_iterator *, s_data_array const *)
	// function call : s_datum *(*const)(s_data_iterator *)
	todo("implement");
	bool __result = _sub_10F07350(level_array, map_id, out_level);
	return __result;
}

_extern bool _sub_10F071F0(long, s_level_datum *);
bool levels_find_level_by_map_id(long map_id, s_level_datum *out_level) // 0x10F071F0
{
	mangled_x86(MANGLED_TODO, "?levels_find_level_by_map_id@@YA_NJPAUs_level_datum@@@Z");
	// s_level_datum *out_level;
	// bool found;
	// function call : void (*const)(e_critical_section)
	// function call : void (*const)(e_critical_section)
	todo("implement");
	bool __result = _sub_10F071F0(map_id, out_level);
	return __result;
}

_extern void _sub_10F07B60(std::function<void __cdecl(s_level_datum *)>);
void levels_iterate_multiplayer_maps(std::function<void __cdecl(s_level_datum *)> func) // 0x10F07B60
{
	mangled_x86(MANGLED_TODO, "?levels_iterate_multiplayer_maps@@YAXV?$function@$$A6AXPAUs_level_datum@@@Z@std@@@Z");
	// static ...; // 0x10F07CAC
	// static ...; // 0x10F07CA0
	// static ...; // 0x10F07C98
	// std::function<void __cdecl(s_level_datum *)> func;
	// s_data_iterator iterator;
	{
		// s_level_datum *level;
	}
	// function call : void (*const)(e_critical_section)
	// function call : void (*const)(s_data_iterator *, s_data_array const *)
	// function call : s_datum *(*const)(s_data_iterator *)
	// function call : void (*const)(e_critical_section)
	todo("implement");
	_sub_10F07B60(func);
}

_extern void _sub_10F079B0(std::function<void __cdecl(s_level_datum *)>);
void levels_iterate_campaign_maps(std::function<void __cdecl(s_level_datum *)> func) // 0x10F079B0
{
	mangled_x86(MANGLED_TODO, "?levels_iterate_campaign_maps@@YAXV?$function@$$A6AXPAUs_level_datum@@@Z@std@@@Z");
	// static ...; // 0x10F07AFC
	// static ...; // 0x10F07AF0
	// static ...; // 0x10F07AE8
	// std::function<void __cdecl(s_level_datum *)> func;
	// s_data_iterator iterator;
	{
		// s_level_datum *level;
	}
	// function call : void (*const)(e_critical_section)
	// function call : void (*const)(s_data_iterator *, s_data_array const *)
	// function call : s_datum *(*const)(s_data_iterator *)
	// function call : void (*const)(e_critical_section)
	todo("implement");
	_sub_10F079B0(func);
}

_extern bool _sub_10F070A0(s_data_array *, char const *, s_level_datum *);
bool levels_find_by_path_internal(s_data_array *level_data, char const *path, s_level_datum *out_level) // 0x10F070A0
{
	mangled_x86(MANGLED_TODO, "?levels_find_by_path_internal@@YA_NPAUs_data_array@@PBDPAUs_level_datum@@@Z");
	// static ...; // 0x10F07184
	// s_data_array *level_data;
	// char const *path;
	// s_level_datum *out_level;
	// s_data_iterator iterator;
	{
		// s_level_datum *level;
	}
	// function call : void (*const)(s_data_iterator *, s_data_array const *)
	// function call : s_datum *(*const)(s_data_iterator *)
	todo("implement");
	bool __result = _sub_10F070A0(level_data, path, out_level);
	return __result;
}

bool levels_find_map_by_name(char const *name, s_level_datum *out_level) // 0x10F07490
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_find_map_by_name@@YA_NPBDPAUs_level_datum@@@Z");
	// s_level_datum *out_level;

	return levels_find_map_by_name_internal(g_level_globals->multiplayer_levels, name, out_level)
		|| levels_find_map_by_name_internal(g_level_globals->campaign_levels, name, out_level);
}

bool levels_find_map_by_path(char const *path, s_level_datum *out_level) // 0x10F07890
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_find_map_by_path@@YA_NPBDPAUs_level_datum@@@Z");
	// s_level_datum *out_level;
	// bool found;
	// function call : void (*const)(e_critical_section)
	// function call : void (*const)(e_critical_section)

	critical_section_enter(_critical_section_levels);
	bool result = levels_find_by_path_internal(g_level_globals->multiplayer_levels, path, out_level)
		|| levels_find_by_path_internal(g_level_globals->campaign_levels, path, out_level);
	critical_section_leave(_critical_section_levels);
	return result;
}

_extern void _sub_10F06C30(char const *);
void levels_close_all_multiplayer_in_directory(char const *directory) // 0x10F06C30
{
	mangled_x86(MANGLED_TODO, "?levels_close_all_multiplayer_in_directory@@YAXPBD@Z");
	// static ...; // 0x10F06DCD
	// static ...; // 0x10F06DC4
	// static ...; // 0x10F06DAC
	// static ...; // 0x10F06DA4
	// char const *directory;
	// s_static_string<256> safe_directory;
	// s_data_iterator iterator;
	{
		// s_level_datum *level;
	}
	// function call : void (*const)(e_critical_section)
	// function call : void (*const)(s_data_iterator *, s_data_array const *)
	// function call : s_datum *(*const)(s_data_iterator *)
	// function call : void (*const)(s_data_array *, long)
	// function call : void (*const)(e_critical_section)
	todo("implement");
	_sub_10F06C30(directory);
}

_extern void _sub_10F06EB0(s_data_array *, long);
void levels_close_map_internal(s_data_array *level_data, long map_id) // 0x10F06EB0
{
	mangled_x86(MANGLED_TODO, "?levels_close_map_internal@@YAXPAUs_data_array@@J@Z");
	// static ...; // 0x10F06FD8
	// static ...; // 0x10F06FD0
	// s_data_array *level_data;
	// long map_id;
	// s_data_iterator iterator;
	{
		// s_level_datum *level;
	}
	// function call : void (*const)(e_critical_section)
	// function call : void (*const)(s_data_iterator *, s_data_array const *)
	// function call : s_datum *(*const)(s_data_iterator *)
	// function call : void (*const)(s_data_array *, long)
	// function call : void (*const)(e_critical_section)
	todo("implement");
	_sub_10F06EB0(level_data, map_id);
}

void levels_close_all_campaigns() // 0x10F06B60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_close_all_campaigns@@YAXXZ");
	// procedure flags: nofpo
	// function call : void (*const)(e_critical_section)
	// function call : void (*const)(s_data_array *)
	// function call : void (*const)(e_critical_section)

	critical_section_enter(_critical_section_levels);
	data_delete_all(g_level_globals->campaigns);
	critical_section_leave(_critical_section_levels);
}

_extern void _sub_10F07040(long);
void levels_close_multiplayer_map(long map_id) // 0x10F07040
{
	mangled_x86(MANGLED_TODO, "?levels_close_multiplayer_map@@YAXJ@Z");
	// long map_id;
	todo("implement");
	_sub_10F07040(map_id);
}

_extern void _sub_10F06E50(long);
void levels_close_campaign_map(long map_id) // 0x10F06E50
{
	mangled_x86(MANGLED_TODO, "?levels_close_campaign_map@@YAXJ@Z");
	// long map_id;
	todo("implement");
	_sub_10F06E50(map_id);
}

_extern void _sub_10F069F0();
void levels_clear_and_enumerate_async() // 0x10F069F0
{
	mangled_x86(MANGLED_TODO, "?levels_clear_and_enumerate_async@@YAXXZ");
	// procedure flags: nofpo
	// constexpr bool (*const `levels_clear_and_enumerate_async'::`2'::levels_enumerate_non_blocking)(); // constant == 5549440
	// function call : void (*const)(e_critical_section)
	// function call : void (*const)(s_data_array *)
	// function call : void (*const)(s_data_array *)
	// function call : void (*const)(s_data_array *)
	// function call : void (*const)(s_data_array *)
	// function call : bool (*const)()
	// function call : void (*const)(e_critical_section)
	todo("implement");
	_sub_10F069F0();
}

/* ---------- private code */
