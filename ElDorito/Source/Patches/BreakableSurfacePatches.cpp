/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/physics/breakable_surfaces.hpp"
#include "Blam/physics/collision_bsp.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/structures/structure_bsp_definitions.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"

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
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct c_collision_bsp_reference;
struct c_collision_surface_reference;
struct c_simulation_entity_definition;
struct real_point3d;
struct real_vector3d;
struct s_breakable_surface_globals;
struct s_breakable_surface_set;
struct s_data_array;
struct s_data_iterator;
struct s_datum;
struct s_scenario_location;
struct s_scenario_structure_bsp;
struct s_structure_breakable_surface;
namespace hades_file_local
{
	struct s_simulation_breakable_surface_group_state_data;
	struct s_simulation_breakable_surface_break_event_data;
	struct c_breakable_surface_group_handle;
}
using namespace hades_file_local;

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace BreakableSurface {}
	using namespace Patches::BreakableSurface;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct s_simulation_breakable_surface_group_state_data
	{
		unsigned long surface_bits; // 0x0
	};
	static_assert(sizeof(s_simulation_breakable_surface_group_state_data) == 4, "Invalid s_simulation_breakable_surface_group_state_data size");

	struct s_simulation_breakable_surface_break_event_data
	{
		long instanced_geometry_instance_index; // 0x0
		long surface_index; // 0x4
		s_scenario_location location; // 0x8
		unsigned char __pad0[2]; // 0xA
		real_point3d position; // 0xC
	};
	static_assert(sizeof(s_simulation_breakable_surface_break_event_data) == 24, "Invalid s_simulation_breakable_surface_break_event_data size");

	struct c_breakable_surface_group_handle
	{
		static long create(long, long);
		static long get_bsp_index(long);
		static long get_group_index(long);
	};
	static_assert(sizeof(c_breakable_surface_group_handle) == 1, "Invalid c_breakable_surface_group_handle size");
}
using namespace hades_file_local;
/* ---------- prototypes */

extern void *(*const datum_try_and_get)(s_data_array const *, unsigned long);  // hades: added for 0x1069CA20
extern void (*const data_iterator_new)(s_data_iterator *, s_data_array const *);  // hades: added for 0x1069CA20
extern s_datum *(*const data_iterator_next)(s_data_iterator *);  // hades: added for 0x1069CA20

static constexpr long k_maximum_structure_bsps_per_scenario = 16;  // hades: added for 0x1069D2E0
static constexpr long k_maximum_breakable_surface_groups = 1024;  // hades: added for 0x1069D2E0

extern long (*const global_structure_bsp_first_active_index_get)();  // hades: added for 0x1069DA60
extern long (*const global_structure_bsp_next_active_index_get)(long);  // hades: added for 0x1069DA60

extern bool (*const game_is_server)();  // hades: added for 0x1069D8B0
extern bool (*const game_is_distributed)();  // hades: added for 0x1069D8B0

extern s_scenario_structure_bsp *(*const global_structure_bsp_get)(long);  // hades: added for 0x1069C540

namespace Patches
{
	namespace BreakableSurface
	{
		extern void ApplyAll();
	}
}

long breakable_surface_group_get_gamestate_index(long bsp_index, long group_index);
void breakable_surface_group_set_gamestate_index(long bsp_index, long group_index, long gamestate_index);
bool breakable_surface_get_surface_information(long bsp_index, long surface_index, long *instanced_geometry_instance_index_out, long *breakable_surface_set_index_out, long *breakable_surface_index_out);
long breakable_surface_get_surface_count(long bsp_index);
long breakable_surface_get_group_index(long bsp_index, long instanced_geometry_instance, long breakable_surface_set_index, long breakable_surface_index);
long breakable_surface_get_surface_index_from_group_index_and_offset(long bsp_index, long group_index, long offset);
void simulation_action_breakable_surface_update(long bsp_index, long group_index);
void breakable_surface_break_sub_hook(real_point3d const *position, real_vector3d const *direction, s_scenario_location const *location, long bsp_index, long instance_index, long breakable_surface_set_index, long breakable_surface_index, long surface_index);
void simulation_action_breakable_surfaces_create_hook();
void __fastcall c_simulation_breakable_surface_break_event_definition__apply_game_event_hook(void *thisptr, void *__formal, long const *entitiy_references, long entity_reference_count, long payload_size, s_simulation_breakable_surface_break_event_data const *payload);
bool __fastcall c_simulation_breakable_surface_group_entity_definition__build_updated_state_data_hook(void *thisptr, void *__formal, void *entity, unsigned long *update_mask, long update_state_data_size, s_simulation_breakable_surface_group_state_data *update_state_data);
bool __fastcall c_simulation_breakable_surface_group_entity_definition__update_game_entity_hook(c_simulation_entity_definition *thisptr, void *__formal, long gamestate_index, unsigned long *update_mask, long update_state_data_size, s_simulation_breakable_surface_group_state_data *update_state_data);
void breakable_surfaces_initialize_for_new_map_hook();
void breakable_surfaces_reset_hook();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	namespace hades_file_local_BreakableSurfacePatches { extern real_vector3d global_zero3d; } using namespace hades_file_local_BreakableSurfacePatches; // 0x1117520C
	extern long g_breakable_surface_group_gamestate_mapping[16][1024]; // 0x11372CD8
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace BreakableSurface
	{
		void ApplyAll() // 0x1069BA50
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@BreakableSurface@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x16B960, breakable_surfaces_reset_hook).Apply();
			Hook(0x1689E6, breakable_surface_break_sub_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x169E30, breakable_surface_group_get_gamestate_index).Apply();
			Hook(0xC6CFA, breakable_surface_get_surface_information, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0xB21A0, simulation_action_breakable_surfaces_create_hook).Apply();
			Hook(0xC67B0, c_simulation_breakable_surface_break_event_definition__apply_game_event_hook).Apply();
			Hook(0xC6C70, c_simulation_breakable_surface_group_entity_definition__build_updated_state_data_hook).Apply();
			Hook(0xC7E10, c_simulation_breakable_surface_group_entity_definition__update_game_entity_hook).Apply();
			Pointer(0x1656258).Write(breakable_surfaces_initialize_for_new_map_hook);
		}
	}
}

/* ---------- private code */

_inline long c_breakable_surface_group_handle::create(long bsp_index, long group_index) // 0x1069D5E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?create@c_breakable_surface_group_handle@hades_file_local@@SAJJJ@Z");
	// `anonymous-namespace'::c_breakable_surface_group_handle::create
	// long group_index;

	(void)((!!(bsp_index >= 0 && bsp_index < 16)) || (_wassert(L"bsp_index >= 0 && bsp_index < k_maximum_structure_bsps_per_scenario", L"C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\BreakableSurfacePatches.cpp", 50), 0));
	(void)((!!(group_index >= 0 && group_index < 1024)) || (_wassert(L"group_index >= 0 && group_index < k_maximum_breakable_surface_groups", L"C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\BreakableSurfacePatches.cpp", 51), 0));
	return bsp_index << 10 | group_index;
}

_inline long c_breakable_surface_group_handle::get_bsp_index(long handle) // 0x1069D680
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_bsp_index@c_breakable_surface_group_handle@hades_file_local@@SAJJ@Z");
	// `anonymous-namespace'::c_breakable_surface_group_handle::get_bsp_index
	// long handle;

	return handle >> 10;
}

_inline long c_breakable_surface_group_handle::get_group_index(long handle) // 0x1069D800
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_group_index@c_breakable_surface_group_handle@hades_file_local@@SAJJ@Z");
	// `anonymous-namespace'::c_breakable_surface_group_handle::get_group_index
	// long handle;

	return handle & 0x3FF;
}

long breakable_surface_group_get_gamestate_index(long bsp_index, long group_index) // 0x1069C800
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?breakable_surface_group_get_gamestate_index@@YAJJJ@Z");
	// `anonymous-namespace'::breakable_surface_group_get_gamestate_index
	// long group_index;
	// long group_count;
	// function call : long (*const)(long)

	#line 227 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\BreakableSurfacePatches.cpp"
		(void)((!!(bsp_index >= 0 && bsp_index < 16)) || (_wassert(L"bsp_index >= 0 && bsp_index < k_maximum_structure_bsps_per_scenario", _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0));
		(void)((!!(group_index >= 0 && group_index < 1024)) || (_wassert(L"group_index >= 0 && group_index < k_maximum_breakable_surface_groups", _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0));
		#line 237 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\BreakableSurfacePatches.cpp"
	long group_count = ((long (*const)(long))0x569D30)(bsp_index);
	if (group_index < 0 || group_index >= group_count)
	{
		return -1;
	}

	return g_breakable_surface_group_gamestate_mapping[bsp_index][group_index];
}

void breakable_surface_group_set_gamestate_index(long bsp_index, long group_index, long gamestate_index) // 0x1069C8F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?breakable_surface_group_set_gamestate_index@@YAXJJJ@Z");
	// `anonymous-namespace'::breakable_surface_group_set_gamestate_index
	// long gamestate_index;

	#line 248 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\BreakableSurfacePatches.cpp"
		(void)((!!(bsp_index >= 0 && bsp_index < 16)) || (_wassert(L"bsp_index >= 0 && bsp_index < k_maximum_structure_bsps_per_scenario", _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0));
		(void)((!!(group_index >= 0 && group_index < 1024)) || (_wassert(L"group_index >= 0 && group_index < k_maximum_breakable_surface_groups", _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0));
		#line 256 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\BreakableSurfacePatches.cpp"
	g_breakable_surface_group_gamestate_mapping[bsp_index][group_index] = gamestate_index;
}

bool breakable_surface_get_surface_information(long bsp_index, long surface_index, long *instanced_geometry_instance_index_out, long *breakable_surface_set_index_out, long *breakable_surface_index_out) // 0x1069C680
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?breakable_surface_get_surface_information@@YA_NJJPAJ00@Z");
	// `anonymous-namespace'::breakable_surface_get_surface_information
	// long *breakable_surface_index_out;
	// s_scenario_structure_bsp const *structure_bsp;
		// s_structure_breakable_surface const *entry;
	// function call : s_scenario_structure_bsp *(*const)(long)

	#line 261 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\BreakableSurfacePatches.cpp"
		assert(instanced_geometry_instance_index_out);
		assert(breakable_surface_set_index_out);
		assert(breakable_surface_index_out);
		#line 273 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\BreakableSurfacePatches.cpp"
	*instanced_geometry_instance_index_out = -1;
	*breakable_surface_set_index_out = -1;
	*breakable_surface_index_out = -1;
	s_scenario_structure_bsp const *structure_bsp = global_structure_bsp_get(bsp_index);
	if (surface_index >= 0 && surface_index < structure_bsp->breakable_surface_key_table.count)
	{
		s_structure_breakable_surface const *entry = &structure_bsp->breakable_surface_key_table[surface_index];
		*instanced_geometry_instance_index_out = entry->instanced_geometry_index;
		*breakable_surface_set_index_out = entry->breakable_surface_set_index;
		*breakable_surface_index_out = entry->breakable_surface_index;
		return true;
	}

	return false;
}

long breakable_surface_get_surface_count(long bsp_index) // 0x1069C540
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?breakable_surface_get_surface_count@@YAJJ@Z");
	// `anonymous-namespace'::breakable_surface_get_surface_count
	// long bsp_index;
	// function call : s_scenario_structure_bsp *(*const)(long)

	#line 291 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\BreakableSurfacePatches.cpp"
		(void)((!!(bsp_index >= 0 && bsp_index < 16)) || (_wassert(L"bsp_index >= 0 && bsp_index < k_maximum_structure_bsps_per_scenario", _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0));
		#line 299 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\BreakableSurfacePatches.cpp"
	return global_structure_bsp_get(bsp_index)->breakable_surface_key_table.count;
}

long breakable_surface_get_group_index(long bsp_index, long instanced_geometry_instance, long breakable_surface_set_index, long breakable_surface_index) // 0x1069C380
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?breakable_surface_get_group_index@@YAJJJJJ@Z");
	// `anonymous-namespace'::breakable_surface_get_group_index
	// static ...; // 0x1069C458
	// static ...; // 0x1069C450
	// long bsp_index;
	// long instanced_geometry_instance;
	// long breakable_surface_set_index;
	// long breakable_surface_index;
	// long surface_count;
		// long i;
			// long instanced_geometry_instance_index_out;
			// long breakable_surface_set_index_out;
			// bool valid;
			// long breakable_surface_index_out;

	long surface_count = breakable_surface_get_surface_count(bsp_index);
	for (long i = 0; i < surface_count; i++)
	{
		long instanced_geometry_instance_index_out = -1;
		long breakable_surface_set_index_out = -1;
		long breakable_surface_index_out = -1;
		bool valid = breakable_surface_get_surface_information(bsp_index, i, &instanced_geometry_instance_index_out, &breakable_surface_set_index_out, &breakable_surface_index_out);
		if (valid && instanced_geometry_instance_index_out == instanced_geometry_instance && breakable_surface_set_index_out == breakable_surface_set_index && breakable_surface_index_out == breakable_surface_index)
		{
			return i / 32;
		}
	}

	return -1;
}

long breakable_surface_get_surface_index_from_group_index_and_offset(long bsp_index, long group_index, long offset) // 0x1069C5E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?breakable_surface_get_surface_index_from_group_index_and_offset@@YAJJJJ@Z");
	// `anonymous-namespace'::breakable_surface_get_surface_index_from_group_index_and_offset
	// long offset;
	// long group_count;
	// function call : long (*const)(long)

	long group_count = ((long(__cdecl *)(long))0x569d30)(bsp_index);

	if (group_index < 0 || group_index >= group_count)
	{
		return -1;
	}

	if (offset < 0 || offset >= 32)
	{
		return -1;
	}

	return group_index * 32 + offset;
}

void simulation_action_breakable_surface_update(long bsp_index, long group_index) // 0x1069D8B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?simulation_action_breakable_surface_update@@YAXJJ@Z");
	// `anonymous-namespace'::simulation_action_breakable_surface_update
	// static ...; // 0x1069D9F4
	// static ...; // 0x1069D9EC
	// long bsp_index;
	// long group_index;
	// long gamestate_index;
		// long entity_indx;
			// unsigned long long flags;
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : long (*const)(long)
	// function call : void (*const)(long, long, unsigned long long *)

	#line 360 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\BreakableSurfacePatches.cpp"
		(void)((!!(bsp_index >= 0 && bsp_index < 16)) || (_wassert(L"bsp_index >= 0 && bsp_index < k_maximum_structure_bsps_per_scenario", _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0));
		(void)((!!(group_index >= 0 && group_index < 1024)) || (_wassert(L"group_index >= 0 && group_index < k_maximum_breakable_surface_groups", _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0));
		#line 379 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\BreakableSurfacePatches.cpp"
	if (!game_is_distributed() || !game_is_server() || ((bool (*const)())0x531D10)())
		return;
	long gamestate_index = breakable_surface_group_get_gamestate_index(bsp_index, group_index);
	if (gamestate_index != -1)
	{
		long entity_indx = ((long (*const)(long))0x471FC0)(gamestate_index);
		if (entity_indx != -1)
		{
			unsigned long long flags = 1;
			((void (*const)(long, long, unsigned long long *))0x4AFC20)(entity_indx, group_index, &flags);
		}
	}
}

void breakable_surface_break_sub_hook(real_point3d const *position, real_vector3d const *direction, s_scenario_location const *location, long bsp_index, long instance_index, long breakable_surface_set_index, long breakable_surface_index, long surface_index) // 0x1069C280
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?breakable_surface_break_sub_hook@@YAXPBUreal_point3d@@PBUreal_vector3d@@PBUs_scenario_location@@JJJJJ@Z");
	// `anonymous-namespace'::breakable_surface_break_sub_hook
	// long surface_index;
	// void (*const breakable_surface_break_sub)(real_point3d const *, real_vector3d const *, s_scenario_location const *, long, long, long, long, long);
		// long group_index;
	// function call : void (*const)(real_point3d const *, real_vector3d const *, s_scenario_location const *, long, long, long, long, long)
	// function call : void (*const)(long, long, long, real_point3d const *, s_scenario_location const *)

	void (*const breakable_surface_break_sub)(real_point3d const *position, real_vector3d const *direction, s_scenario_location const *location, long bsp_index, long instance_index, long breakable_surface_set_index, long breakable_surface_index, long surface_index) = (void (*const)(real_point3d const *, real_vector3d const *, s_scenario_location const *, long, long, long, long, long))0x569820;

	breakable_surface_break_sub(position, &global_zero3d, location, bsp_index, instance_index, breakable_surface_set_index, breakable_surface_index, surface_index);
	if (*(char const *)location != -1)
	{
		((void (*)(long, long, long, real_point3d const *, s_scenario_location const *))0x4b20b0)(instance_index, 0, surface_index, position, location);

		long group_index = breakable_surface_get_group_index(bsp_index, instance_index, breakable_surface_set_index, breakable_surface_index);
		if (group_index != -1)
			simulation_action_breakable_surface_update(bsp_index, group_index);
	}
}

void simulation_action_breakable_surfaces_create_hook() // 0x1069DA60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?simulation_action_breakable_surfaces_create_hook@@YAXXZ");
	// `anonymous-namespace'::simulation_action_breakable_surfaces_create_hook
	// procedure flags: nofpo
		// long bsp_index;
			// long group_count;
				// long group_index;
					// long gamestate_index;
					// long handle;
						// long entity_index;
							// void *entity_manager;
							// void *entity_database;
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : long (*const)()
	// function call : long (*const)(long)
	// function call : long (*const)(long)
	// function call : long (*const)()
	// function call : long (*const)(long, long)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : long (*const)(long, long, long)
	// function call : c_simulation_world *(*const)()
	// function call : void (*const)(void *, short)

	if (!game_is_server() || !game_is_distributed())
		return;
	for (long bsp_index = global_structure_bsp_first_active_index_get(); bsp_index != -1; bsp_index = global_structure_bsp_next_active_index_get(bsp_index))
	{
		long group_count = ((long (*)(long))0x569D30)(bsp_index);
		for (long group_index = 0; group_index < group_count; group_index++)
		{
			long gamestate_index = ((long (*)())0x471E10)();
			breakable_surface_group_set_gamestate_index(bsp_index, group_index, gamestate_index);
			long handle = c_breakable_surface_group_handle::create(bsp_index, group_index);
			((void (*)(long, long))0x471FF0)(gamestate_index, handle);
			if (game_is_distributed() && !((bool (*)())0x531D10)())
			{
				long entity_index = ((long (*)(long, long, long))0x4AF8A0)(12, handle, gamestate_index);
				if (entity_index != -1)
				{
					void *entity_manager = *(void **)offset_pointer(((void *(*)())0x441940)(), 4);
					void *entity_database = offset_pointer(entity_manager, 0x10A0);
					((void (__thiscall *)(void *, unsigned short))0x4A6110)(entity_database, (unsigned short)entity_index);
				}
			}
		}
	}
}

void __fastcall c_simulation_breakable_surface_break_event_definition__apply_game_event_hook(void *thisptr, void *__formal, long const *entitiy_references, long entity_reference_count, long payload_size, s_simulation_breakable_surface_break_event_data const *payload) // 0x1069CD70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_simulation_breakable_surface_break_event_definition__apply_game_event_hook@@YIXPAX0PBJJJPBUs_simulation_breakable_surface_break_event_data@hades_file_local@@@Z");
	// `anonymous-namespace'::c_simulation_breakable_surface_break_event_definition__apply_game_event_hook
	// void *__formal;
	// long const *entitiy_references;
	// long entity_reference_count;
	// long payload_size;
	// s_simulation_breakable_surface_break_event_data const *payload;
	// c_collision_surface_reference surface_reference;
	// long breakable_surface_set_index;
	// long surface_index;
	// long bsp_index;
	// s_scenario_structure_bsp const *structure_bsp;
	// long breakable_surface_index;
	// c_collision_bsp_reference bsp_reference;
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : void (*const)(c_collision_bsp_reference *, s_scenario_structure_bsp const *)
	// function call : void (*const)(c_collision_bsp_reference *, s_scenario_structure_bsp const *, long, bool)
	// function call : void (*const)(c_collision_surface_reference *, c_collision_bsp_reference, long)
	// function call : unsigned char (*const)(c_collision_surface_reference *)
	// function call : long (*const)(c_collision_surface_reference *)
	// function call : long (*const)(c_collision_surface_reference *)
	// function call : void (*const)(long, long, long, long, long, real_point3d const *, s_scenario_location const *, real_vector3d const *)

	long bsp_index = payload->location.cluster_reference.bsp_index;
	long surface_index = payload->surface_index;
	s_scenario_structure_bsp const *structure_bsp = global_structure_bsp_get(bsp_index);
	c_collision_bsp_reference bsp_reference;
	if (payload->instanced_geometry_instance_index == -1)
		((void (__thiscall *)(c_collision_bsp_reference *, s_scenario_structure_bsp const *))0x5F0B50)(&bsp_reference, structure_bsp);
	else
		((void (__thiscall *)(c_collision_bsp_reference *, s_scenario_structure_bsp const *, long, bool))0x5F0BB0)(&bsp_reference, structure_bsp, structure_bsp->instanced_geometry_instances[payload->instanced_geometry_instance_index].mesh_index, false);
	c_collision_surface_reference surface_reference;
	((void (__thiscall *)(c_collision_surface_reference *, c_collision_bsp_reference, long))0x7182D0)(&surface_reference, bsp_reference, surface_index);
	if (!(((unsigned char (__thiscall *)(c_collision_surface_reference *))0x7185D0)(&surface_reference) & 8))
		return;
	long breakable_surface_set_index = ((long (__thiscall *)(c_collision_surface_reference *))0x718470)(&surface_reference);
	long breakable_surface_index = ((long (__thiscall *)(c_collision_surface_reference *))0x7184B0)(&surface_reference);
	if (breakable_surface_set_index == -1 || breakable_surface_index == -1)
		return;
	((void (*)(long, long, long, long, long, real_point3d const *, s_scenario_location const *, real_vector3d const *))0x568810)(payload->location.cluster_reference.bsp_index, payload->instanced_geometry_instance_index, breakable_surface_index, breakable_surface_set_index, payload->surface_index, &payload->position, &payload->location, &global_zero3d);
}

bool __fastcall c_simulation_breakable_surface_group_entity_definition__build_updated_state_data_hook(void *thisptr, void *__formal, void *entity, unsigned long *update_mask, long update_state_data_size, s_simulation_breakable_surface_group_state_data *update_state_data) // 0x1069CFC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_simulation_breakable_surface_group_entity_definition__build_updated_state_data_hook@@YI_NPAX00PAKJPAUs_simulation_breakable_surface_group_state_data@hades_file_local@@@Z");
	// `anonymous-namespace'::c_simulation_breakable_surface_group_entity_definition__build_updated_state_data_hook
	// void *thisptr;
	// void *__formal;
	// void *entity;
	// unsigned long *update_mask;
	// long update_state_data_size;
	// s_simulation_breakable_surface_group_state_data *update_state_data;
	// long gamestate_index;
	// unsigned long new_surface_bits;
	// long bsp_index;
	// long group_index;
	// long handle;
		// long i;
			// long breakable_surface_set_index;
			// long surface_index;
			// long breakable_surface_index;
			// long instanced_geometry_instance_index;
	// function call : long (*const)(long)
	// function call : bool (*const)(long, long, long, long)

	if (!(*update_mask & 1))
		return true;
	long gamestate_index = *(long *)offset_pointer(entity, 0xC);
	long handle = ((long (*)(long))0x471F10)(gamestate_index);
	long bsp_index = c_breakable_surface_group_handle::get_bsp_index(handle);
	long group_index = c_breakable_surface_group_handle::get_group_index(handle);
	#line 522 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\BreakableSurfacePatches.cpp"
		assert(bsp_index >= 0 && bsp_index < k_maximum_structure_bsps_per_scenario);
		#line 543 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\BreakableSurfacePatches.cpp"
	#line 523 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\BreakableSurfacePatches.cpp"
		assert(group_index >= 0 && group_index < k_maximum_breakable_surface_groups);
		#line 546 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\BreakableSurfacePatches.cpp"
	unsigned long new_surface_bits = update_state_data->surface_bits;
	for (long i = 0; i < 32; i++)
	{
		long surface_index = breakable_surface_get_surface_index_from_group_index_and_offset(bsp_index, group_index, i);
		if (surface_index == -1)
			continue;
		long instanced_geometry_instance_index = -1;
		long breakable_surface_set_index = -1;
		long breakable_surface_index = -1;
		if (breakable_surface_get_surface_information(bsp_index, surface_index, &instanced_geometry_instance_index, &breakable_surface_set_index, &breakable_surface_index))
		{
			if (!((bool (*)(long, long, long, long))0x569AB0)(bsp_index, instanced_geometry_instance_index, breakable_surface_set_index, breakable_surface_index))
				new_surface_bits |= (1 << i);
			else
				new_surface_bits &= ~(1 << i);
		}
	}
	if (new_surface_bits != update_state_data->surface_bits)
	{
		update_state_data->surface_bits = new_surface_bits;
		*update_mask |= 1;
	}
	return true;
}

bool __fastcall c_simulation_breakable_surface_group_entity_definition__update_game_entity_hook(c_simulation_entity_definition *thisptr, void *__formal, long gamestate_index, unsigned long *update_mask, long update_state_data_size, s_simulation_breakable_surface_group_state_data *update_state_data) // 0x1069D2E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_simulation_breakable_surface_group_entity_definition__update_game_entity_hook@@YI_NPAUc_simulation_entity_definition@@PAXJPAKJPAUs_simulation_breakable_surface_group_state_data@hades_file_local@@@Z");
	// `anonymous-namespace'::c_simulation_breakable_surface_group_entity_definition__update_game_entity_hook
	// c_simulation_entity_definition *thisptr;
	// void *__formal;
	// long gamestate_index;
	// unsigned long *update_mask;
	// long update_state_data_size;
	// s_simulation_breakable_surface_group_state_data *update_state_data;
	// bool (*const gameworld_attachment_valid)(void *, long);
	// long bsp_index;
	// long group_index;
	// long handle;
		// long i;
			// long breakable_surface_set_index;
			// long surface_index;
			// long breakable_surface_index;
			// long instance_index;
	// function call : bool (*const)(void *, long)
	// function call : long (*const)(long)
	// function call : bool (*const)(long, long, long, long)
	// function call : void (*const)(long, long, long, long, bool)

	bool (__thiscall *const gameworld_attachment_valid)(void *, long) = *(bool (__thiscall **)(void *, long))offset_pointer(*(void **)thisptr, 0x20);
	if (!gameworld_attachment_valid(thisptr, gamestate_index))
		return true;
	long handle = ((long (*)(long))0x471F10)(gamestate_index);
	long bsp_index = c_breakable_surface_group_handle::get_bsp_index(handle);
	long group_index = c_breakable_surface_group_handle::get_group_index(handle);
	#line 582 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\BreakableSurfacePatches.cpp"
		assert(bsp_index >= 0 && bsp_index < k_maximum_structure_bsps_per_scenario);
		#line 604 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\BreakableSurfacePatches.cpp"
	#line 583 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\BreakableSurfacePatches.cpp"
		assert(group_index >= 0 && group_index < k_maximum_breakable_surface_groups);
		#line 607 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\BreakableSurfacePatches.cpp"
	for (long i = 0; i < 32; i++)
	{
		if (!(update_state_data->surface_bits & (1 << i)))
			continue;
		long surface_index = breakable_surface_get_surface_index_from_group_index_and_offset(bsp_index, group_index, i);
		if (surface_index == -1)
			continue;
		long instance_index = -1;
		long breakable_surface_set_index = -1;
		long breakable_surface_index = -1;
		if (breakable_surface_get_surface_information(bsp_index, surface_index, &instance_index, &breakable_surface_set_index, &breakable_surface_index) && ((bool (*)(long, long, long, long))0x569AB0)(bsp_index, instance_index, breakable_surface_set_index, breakable_surface_index))
			((void (*)(long, long, long, long, bool))0x569BA0)(bsp_index, instance_index, breakable_surface_set_index, breakable_surface_index, false);
	}
	return true;
}

void breakable_surfaces_initialize_for_new_map_hook() // 0x1069C9B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?breakable_surfaces_initialize_for_new_map_hook@@YAXXZ");
	// `anonymous-namespace'::breakable_surfaces_initialize_for_new_map_hook
	// procedure flags: nofpo
	// void (*const breakable_surfaces_initialize_for_new_map)();
	// function call : void (*const)()

	void (*const breakable_surfaces_initialize_for_new_map)() = (void (*const)())0x56B770;
	breakable_surfaces_initialize_for_new_map();
	memset(g_breakable_surface_group_gamestate_mapping, -1, 0x10000);
}

void breakable_surfaces_reset_hook() // 0x1069CA20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?breakable_surfaces_reset_hook@@YAXXZ");
	// `anonymous-namespace'::breakable_surfaces_reset_hook
	// procedure flags: nofpo
	// static ...; // 0x1069CCC1
	// static ...; // 0x1069CCBC
	// static ...; // 0x1069CCA4
	// static ...; // 0x1069CC9C
	// s_breakable_surface_set set;
	// s_breakable_surface_globals *breakable_surface_globals;
	// s_data_array *broken_events;
	// void (*const havok_notify_static_geometry_modfied)();
	// s_data_iterator iter;
		// long i;
		// long bsp_index;
			// long group_count;
				// long i;
	// function call : void (*const)()
	// function call : void (*const)(s_data_iterator *, s_data_array const *)
	// function call : s_datum *(*const)(s_data_iterator *)
	// function call : void *(*const)(s_data_array const *, unsigned long)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : long (*const)()
	// function call : long (*const)(long)
	// function call : long (*const)(long)

	void (*const havok_notify_static_geometry_modfied)() = reinterpret_cast<void (*)()>(0x5C6AF0);
	s_breakable_surface_globals *breakable_surface_globals = tls_getd().breakable_surface_globals;
	s_breakable_surface_set set;
	memset(&set, 0, sizeof(set));
	memset(set.subpart_visibility, -1, sizeof(set.subpart_visibility));
	memset(set.impct_decal_indices, -1, sizeof(set.impct_decal_indices));
	set.first_broken_event_index = -1;
	set.is_broken = false;
	for (long i = 0; i < 2048; i++)
		memcpy(&breakable_surface_globals->breakable_surface_sets[i], &set, sizeof(set));
	breakable_surface_globals->field_10 = -1;
	breakable_surface_globals->impact_decal_next_index = 0;
	havok_notify_static_geometry_modfied();
	s_data_array *broken_events = tls_getd().breakable_surface_set_broken_event;
	s_data_iterator iter;
	data_iterator_new(&iter, broken_events);
	while (data_iterator_next(&iter))
		*(bool *)offset_pointer(datum_try_and_get(broken_events, iter.current_datum_index), 0x463) = false;
	if (game_is_server() && game_is_distributed())
	{
		for (long bsp_index = global_structure_bsp_first_active_index_get(); bsp_index != -1; bsp_index = global_structure_bsp_next_active_index_get(bsp_index))
		{
			long group_count = ((long (*)(long))0x569D30)(bsp_index);
			for (long i = 0; i < group_count; i++)
				simulation_action_breakable_surface_update(bsp_index, i);
		}
	}
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_structure_breakable_surface>::try_get_element(__int32, s_structure_breakable_surface **) const;
template bool c_tag_block<s_structure_instanced_geometry_instance>::try_get_element(__int32, s_structure_instanced_geometry_instance **) const;
template s_structure_breakable_surface * c_tag_block<s_structure_breakable_surface>::get_element(__int32) const;
template s_structure_breakable_surface const & c_tag_block<s_structure_breakable_surface>::operator[](__int32) const;
template s_structure_instanced_geometry_instance * c_tag_block<s_structure_instanced_geometry_instance>::get_element(__int32) const;
template s_structure_instanced_geometry_instance const & c_tag_block<s_structure_instanced_geometry_instance>::operator[](__int32) const;
template void Pointer::Write<void (__cdecl*)(void)>(void (*const value)()) const;

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { long g_breakable_surface_group_gamestate_mapping[16][1024]; }
namespace hades_file_local { namespace hades_file_local_BreakableSurfacePatches { real_vector3d global_zero3d; } }
