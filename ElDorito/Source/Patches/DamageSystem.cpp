/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/engine/game_engine_player_traits.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/items/equipment.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "Utils/Singleton.hpp"

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

struct c_player_trait_shield_vitality;
struct real_point3d;
struct real_vector3d;
struct s_damage_data;
struct s_damage_owner;
struct s_damage_reporting_info;
struct s_effect_creation_data;
struct s_equipment_data;
struct s_object_data;
struct s_object_placement_data;
struct s_player_datum;
struct s_scenario_location;
namespace hades_file_local
{
	struct s_unit_player_melee_damage_target;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace DamageSystem {}
	using namespace Patches::DamageSystem;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct s_unit_player_melee_damage_target
	{
		real_point3d position; // 0x0
		real_vector3d direction; // 0xC
		long bsp_index; // 0x18
		long object_index; // 0x1C
		short breakable_surface_set_index; // 0x20
		short breakable_surface_index; // 0x22
		long instanced_geometry_index; // 0x24
		long surface_index; // 0x28
		long object_material_index; // 0x2C
		short global_material_index; // 0x30
		unsigned char __pad0[2]; // 0x32
		float scale; // 0x34
		s_damage_reporting_info damage_reporting_info; // 0x38
		long byte3C; // 0x3C
		s_unit_player_melee_damage_target(s_unit_player_melee_damage_target &); /* compiler_generated() */
		s_unit_player_melee_damage_target(s_unit_player_melee_damage_target const &); /* compiler_generated() */
		s_unit_player_melee_damage_target(); /* compiler_generated() */
		s_unit_player_melee_damage_target &operator=(s_unit_player_melee_damage_target &); /* compiler_generated() */
		s_unit_player_melee_damage_target &operator=(s_unit_player_melee_damage_target const &); /* compiler_generated() */
	};
	static_assert(sizeof(s_unit_player_melee_damage_target) == 64, "Invalid s_unit_player_melee_damage_target size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Patches
{
	namespace DamageSystem
	{
		extern void ApplyAll();
	}
}

long event_generate_part_object_new_hook(s_object_placement_data *placement_data);
long effect_new_from_object__effect_new_from_creation_data_hook(s_effect_creation_data *creation_data);
void MeleeDamageHook(s_damage_data *damageData, unsigned __int32 unitObjectIndex, __int32 predictability);
void object_cause_damage_hook(s_damage_data *damage_data, long object_index, short node_index, short region_index, short material_index, long predictability);
bool object_damage_update_overshield_hook(s_player_datum *player);
void unit_resolve_melee_attack_hook(long unit_index, long definition_index, long secondary_definition_index, s_damage_owner *damage_owner, s_unit_player_melee_damage_target *target, bool a6, bool a7);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace DamageSystem
	{
		_extern void _sub_1095F330();
		void ApplyAll() // 0x1095F330
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@DamageSystem@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_1095F330();
		}
	}
}

/* ---------- private code */

_extern long _sub_109603C0(s_object_placement_data *);
long event_generate_part_object_new_hook(s_object_placement_data *placement_data) // 0x109603C0
{
	// `anonymous-namespace'::event_generate_part_object_new_hook
	// s_object_placement_data *placement_data;
	// long new_object_index;
	{
		// s_equipment_data *equipment;
	}
	// function call : long (*const)(s_object_placement_data *)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	long __result = _sub_109603C0(placement_data);
	return __result;
}

long effect_new_from_object__effect_new_from_creation_data_hook(s_effect_creation_data *creation_data) // 0x10960300
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?effect_new_from_object__effect_new_from_creation_data_hook@@YAJPAUs_effect_creation_data@@@Z");
	// `anonymous-namespace'::effect_new_from_object__effect_new_from_creation_data_hook
	// s_effect_creation_data *creation_data;
	// long object_index;
	// long (*const effect_new_from_creation_data)(s_effect_creation_data *);
	// s_damage_owner *damage_owner;
	// function call : void (*const)(long, s_damage_owner *)
	// function call : long (*const)(s_effect_creation_data *)

	long (__cdecl *const effect_new_from_creation_data)(s_effect_creation_data *) = (long(__cdecl *const)(s_effect_creation_data *))0x5b7fc0;

	long object_index = *(long *)offset_pointer(creation_data, 8);
	s_damage_owner *damage_owner = (s_damage_owner *)offset_pointer(creation_data, 12);
	if (damage_owner->object_index == -1)
	{
		((void(__cdecl *const)(long, s_damage_owner *))0xb770e0)(object_index, damage_owner);
	}

	return effect_new_from_creation_data(creation_data);
}

void MeleeDamageHook(s_damage_data *damageData, unsigned __int32 unitObjectIndex, __int32 predictability) // 0x10960290
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?MeleeDamageHook@@YAXPAUs_damage_data@@IH@Z");
	// `anonymous-namespace'::MeleeDamageHook
	// __int32 predictability;
	// function call : void (*const)(s_damage_data *, long, long)

	((void(__cdecl *const)(s_damage_data *, long, long))0xb542a0)(damageData, unitObjectIndex, predictability);
}

_extern void _sub_10960490(s_damage_data *, long, short, short, short, long);
void object_cause_damage_hook(s_damage_data *damage_data, long object_index, short node_index, short region_index, short material_index, long predictability) // 0x10960490
{
	// `anonymous-namespace'::object_cause_damage_hook
	// long predictability;
	// long (*const get_ultimate_parent_player_index)(long);
	// void (*const object_cause_damage)(s_damage_data *, long, short, short, short, long);
	// function call : long (*const)(long)
	// function call : void (*const)(s_damage_data *, long, short, short, short, long)
	todo("implement");
	_sub_10960490(damage_data, object_index, node_index, region_index, material_index, predictability);
}

_extern bool _sub_10960550(s_player_datum *);
bool object_damage_update_overshield_hook(s_player_datum *player) // 0x10960550
{
	// `anonymous-namespace'::object_damage_update_overshield_hook
	// static ...; // 0x109606D0
	// static ...; // 0x109606C4
	// static ...; // 0x109606BC
	// s_player_datum *player;
	// bool (*const sub_53AF10)(s_player_datum *);
	// long (*const get_shield_multiplier)(c_player_trait_shield_vitality *);
	{
		// s_object_data *unit;
		{
			// float max_shield_vitality;
			{
				// float step;
				// unsigned long long update_flags;
			}
		}
	}
	// function call : long (*const)(c_player_trait_shield_vitality *)
	// function call : float (*const)(float)
	// function call : void (*const)(long, unsigned long long *)
	// function call : bool (*const)(s_player_datum *)
	todo("implement");
	bool __result = _sub_10960550(player);
	return __result;
}

_extern void _sub_10960740(long, long, long, s_damage_owner *, s_unit_player_melee_damage_target *, bool, bool);
void unit_resolve_melee_attack_hook(long unit_index, long definition_index, long secondary_definition_index, s_damage_owner *damage_owner, s_unit_player_melee_damage_target *target, bool a6, bool a7) // 0x10960740
{
	// `anonymous-namespace'::unit_resolve_melee_attack_hook
	// s_damage_owner *damage_owner;
	// s_unit_player_melee_damage_target *target;
	// bool a6;
	// bool a7;
	// void (*const unit_resolve_melee_attack)(long, long, long, s_damage_owner *, s_unit_player_melee_damage_target *, bool, bool);
	// s_scenario_location location;
	// function call : void (*const)(s_scenario_location *, real_point3d *)
	// function call : bool (*const)(long, long, long, long, long)
	// function call : void (*const)(long, long, long, s_damage_owner *, s_unit_player_melee_damage_target *, bool, bool)
	todo("implement");
	_sub_10960740(unit_index, definition_index, secondary_definition_index, damage_owner, target, a6, a7);
}
