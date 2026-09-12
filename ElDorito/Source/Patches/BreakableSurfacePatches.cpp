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
	extern real_vector3d global_zero3d; // 0x1117520C
	extern long g_breakable_surface_group_gamestate_mapping[16][1024]; // 0x11372CD8
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace BreakableSurface
	{
		_extern void _sub_1069BA50();
		void ApplyAll() // 0x1069BA50
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@BreakableSurface@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_1069BA50();
		}
	}
}

/* ---------- private code */

_extern long _sub_1069D5E0(long, long);
_inline long c_breakable_surface_group_handle::create(long bsp_index, long group_index) // 0x1069D5E0
{
	// `anonymous-namespace'::c_breakable_surface_group_handle::create
	// long group_index;
	todo("implement");
	long __result = _sub_1069D5E0(bsp_index, group_index);
	return __result;
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

_extern long _sub_1069C800(long, long);
long breakable_surface_group_get_gamestate_index(long bsp_index, long group_index) // 0x1069C800
{
	// `anonymous-namespace'::breakable_surface_group_get_gamestate_index
	// long group_index;
	// long group_count;
	// function call : long (*const)(long)
	todo("implement");
	long __result = _sub_1069C800(bsp_index, group_index);
	return __result;
}

_extern void _sub_1069C8F0(long, long, long);
void breakable_surface_group_set_gamestate_index(long bsp_index, long group_index, long gamestate_index) // 0x1069C8F0
{
	// `anonymous-namespace'::breakable_surface_group_set_gamestate_index
	// long gamestate_index;
	todo("implement");
	_sub_1069C8F0(bsp_index, group_index, gamestate_index);
}

_extern bool _sub_1069C680(long, long, long *, long *, long *);
bool breakable_surface_get_surface_information(long bsp_index, long surface_index, long *instanced_geometry_instance_index_out, long *breakable_surface_set_index_out, long *breakable_surface_index_out) // 0x1069C680
{
	// `anonymous-namespace'::breakable_surface_get_surface_information
	// long *breakable_surface_index_out;
	// s_scenario_structure_bsp const *structure_bsp;
	{
		// s_structure_breakable_surface const *entry;
	}
	// function call : s_scenario_structure_bsp *(*const)(long)
	todo("implement");
	bool __result = _sub_1069C680(bsp_index, surface_index, instanced_geometry_instance_index_out, breakable_surface_set_index_out, breakable_surface_index_out);
	return __result;
}

_extern long _sub_1069C540(long);
long breakable_surface_get_surface_count(long bsp_index) // 0x1069C540
{
	// `anonymous-namespace'::breakable_surface_get_surface_count
	// long bsp_index;
	// function call : s_scenario_structure_bsp *(*const)(long)
	todo("implement");
	long __result = _sub_1069C540(bsp_index);
	return __result;
}

_extern long _sub_1069C380(long, long, long, long);
long breakable_surface_get_group_index(long bsp_index, long instanced_geometry_instance, long breakable_surface_set_index, long breakable_surface_index) // 0x1069C380
{
	// `anonymous-namespace'::breakable_surface_get_group_index
	// static ...; // 0x1069C458
	// static ...; // 0x1069C450
	// long bsp_index;
	// long instanced_geometry_instance;
	// long breakable_surface_set_index;
	// long breakable_surface_index;
	// long surface_count;
	{
		// long i;
		{
			// long instanced_geometry_instance_index_out;
			// long breakable_surface_set_index_out;
			// bool valid;
			// long breakable_surface_index_out;
		}
	}
	todo("implement");
	long __result = _sub_1069C380(bsp_index, instanced_geometry_instance, breakable_surface_set_index, breakable_surface_index);
	return __result;
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

_extern void _sub_1069D8B0(long, long);
void simulation_action_breakable_surface_update(long bsp_index, long group_index) // 0x1069D8B0
{
	// `anonymous-namespace'::simulation_action_breakable_surface_update
	// static ...; // 0x1069D9F4
	// static ...; // 0x1069D9EC
	// long bsp_index;
	// long group_index;
	// long gamestate_index;
	{
		// long entity_indx;
		{
			// unsigned long long flags;
		}
	}
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : long (*const)(long)
	// function call : void (*const)(long, long, unsigned long long *)
	todo("implement");
	_sub_1069D8B0(bsp_index, group_index);
}

_extern void _sub_1069C280(real_point3d const *, real_vector3d const *, s_scenario_location const *, long, long, long, long, long);
void breakable_surface_break_sub_hook(real_point3d const *position, real_vector3d const *direction, s_scenario_location const *location, long bsp_index, long instance_index, long breakable_surface_set_index, long breakable_surface_index, long surface_index) // 0x1069C280
{
	// `anonymous-namespace'::breakable_surface_break_sub_hook
	// long surface_index;
	// void (*const breakable_surface_break_sub)(real_point3d const *, real_vector3d const *, s_scenario_location const *, long, long, long, long, long);
	{
		// long group_index;
	}
	// function call : void (*const)(real_point3d const *, real_vector3d const *, s_scenario_location const *, long, long, long, long, long)
	// function call : void (*const)(long, long, long, real_point3d const *, s_scenario_location const *)
	todo("implement");
	_sub_1069C280(position, direction, location, bsp_index, instance_index, breakable_surface_set_index, breakable_surface_index, surface_index);
}

_extern void _sub_1069DA60();
void simulation_action_breakable_surfaces_create_hook() // 0x1069DA60
{
	// `anonymous-namespace'::simulation_action_breakable_surfaces_create_hook
	// procedure flags: nofpo
	{
		// long bsp_index;
		{
			// long group_count;
			{
				// long group_index;
				{
					// long gamestate_index;
					// long handle;
					{
						// long entity_index;
						{
							// void *entity_manager;
							// void *entity_database;
						}
					}
				}
			}
		}
	}
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
	todo("implement");
	_sub_1069DA60();
}

_extern void _sub_1069CD70(void *, void *, long const *, long, long, s_simulation_breakable_surface_break_event_data const *);
void __fastcall c_simulation_breakable_surface_break_event_definition__apply_game_event_hook(void *thisptr, void *__formal, long const *entitiy_references, long entity_reference_count, long payload_size, s_simulation_breakable_surface_break_event_data const *payload) // 0x1069CD70
{
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
	todo("implement");
	_sub_1069CD70(thisptr, __formal, entitiy_references, entity_reference_count, payload_size, payload);
}

_extern bool _sub_1069CFC0(void *, void *, void *, unsigned long *, long, s_simulation_breakable_surface_group_state_data *);
bool __fastcall c_simulation_breakable_surface_group_entity_definition__build_updated_state_data_hook(void *thisptr, void *__formal, void *entity, unsigned long *update_mask, long update_state_data_size, s_simulation_breakable_surface_group_state_data *update_state_data) // 0x1069CFC0
{
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
	{
		// long i;
		{
			// long breakable_surface_set_index;
			// long surface_index;
			// long breakable_surface_index;
			// long instanced_geometry_instance_index;
		}
	}
	// function call : long (*const)(long)
	// function call : bool (*const)(long, long, long, long)
	todo("implement");
	bool __result = _sub_1069CFC0(thisptr, __formal, entity, update_mask, update_state_data_size, update_state_data);
	return __result;
}

_extern bool _sub_1069D2E0(c_simulation_entity_definition *, void *, long, unsigned long *, long, s_simulation_breakable_surface_group_state_data *);
bool __fastcall c_simulation_breakable_surface_group_entity_definition__update_game_entity_hook(c_simulation_entity_definition *thisptr, void *__formal, long gamestate_index, unsigned long *update_mask, long update_state_data_size, s_simulation_breakable_surface_group_state_data *update_state_data) // 0x1069D2E0
{
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
	{
		// long i;
		{
			// long breakable_surface_set_index;
			// long surface_index;
			// long breakable_surface_index;
			// long instance_index;
		}
	}
	// function call : bool (*const)(void *, long)
	// function call : long (*const)(long)
	// function call : bool (*const)(long, long, long, long)
	// function call : void (*const)(long, long, long, long, bool)
	todo("implement");
	bool __result = _sub_1069D2E0(thisptr, __formal, gamestate_index, update_mask, update_state_data_size, update_state_data);
	return __result;
}

_extern void _sub_1069C9B0();
void breakable_surfaces_initialize_for_new_map_hook() // 0x1069C9B0
{
	// `anonymous-namespace'::breakable_surfaces_initialize_for_new_map_hook
	// procedure flags: nofpo
	// void (*const breakable_surfaces_initialize_for_new_map)();
	// function call : void (*const)()
	todo("implement");
	_sub_1069C9B0();
}

_extern void _sub_1069CA20();
void breakable_surfaces_reset_hook() // 0x1069CA20
{
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
	{
		// long i;
	}
	{
		// long bsp_index;
		{
			// long group_count;
			{
				// long i;
			}
		}
	}
	// function call : void (*const)()
	// function call : void (*const)(s_data_iterator *, s_data_array const *)
	// function call : s_datum *(*const)(s_data_iterator *)
	// function call : void *(*const)(s_data_array const *, unsigned long)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : long (*const)()
	// function call : long (*const)(long)
	// function call : long (*const)(long)
	todo("implement");
	_sub_1069CA20();
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
