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

#include "Modules/ModuleDebug.hpp"  // hades: added for 0x10960490

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

extern float (*const game_seconds_to_ticks_real)(float);  // hades: added for 0x10960550

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long object_index, c_enum<e_object_type, long> object_type_mask);  // hades: added for 0x109603C0

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
		void ApplyAll() // 0x1095F330
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@DamageSystem@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x73D10A, MeleeDamageHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x56D05D, object_cause_damage_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x56D2EB, object_cause_damage_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x750535, object_cause_damage_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7527DF, object_cause_damage_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7542B2, object_cause_damage_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x756D80, object_cause_damage_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x757F49, object_cause_damage_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x779645, object_cause_damage_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7B3EC6, object_cause_damage_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7B4994, object_cause_damage_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x755F89, object_damage_update_overshield_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0xC1C27, unit_resolve_melee_attack_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0xC189D, { 0xEB }).Apply();
			Hook(0x1B868B, effect_new_from_object__effect_new_from_creation_data_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1BF0AE, event_generate_part_object_new_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
		}
	}
}

/* ---------- private code */

long event_generate_part_object_new_hook(s_object_placement_data *placement_data) // 0x109603C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_generate_part_object_new_hook@@YAJPAUs_object_placement_data@@@Z");
	// `anonymous-namespace'::event_generate_part_object_new_hook
	// s_object_placement_data *placement_data;
	// long new_object_index;
		// s_equipment_data *equipment;
	// function call : long (*const)(s_object_placement_data *)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)

	long new_object_index = ((long (*const)(s_object_placement_data *))0xB30440)(placement_data);
	s_equipment_data *equipment = (s_equipment_data *)object_try_and_get_and_verify_type(new_object_index, 8);
	if (equipment)
	{
		equipment->equipment_damage_owner = equipment->damage_owner;
	}

	return new_object_index;
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

	damageData->acceleration_scale = 1.0f;
	((void(__cdecl *const)(s_damage_data *, long, long))0xb542a0)(damageData, unitObjectIndex, predictability);
}

void object_cause_damage_hook(s_damage_data *damage_data, long object_index, short node_index, short region_index, short material_index, long predictability) // 0x10960490
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_cause_damage_hook@@YAXPAUs_damage_data@@JFFFJ@Z");
	// `anonymous-namespace'::object_cause_damage_hook
	// long predictability;
	// long (*const get_ultimate_parent_player_index)(long);
	// void (*const object_cause_damage)(s_damage_data *, long, short, short, short, long);
	// function call : long (*const)(long)
	// function call : void (*const)(s_damage_data *, long, short, short, short, long)

	long (*const get_ultimate_parent_player_index)(long) = reinterpret_cast<long (*)(long)>(0x554360);
	void (*const object_cause_damage)(s_damage_data *, long, short, short, short, long) = reinterpret_cast<void (*)(s_damage_data *, long, short, short, short, long)>(0xB532F0);
	if (get_ultimate_parent_player_index(object_index) != -1 && Utils::Singleton<Modules::ModuleDebug>::Instance().VarPlayerDamageDisabledClient->ValueInt)
	{
		return;
	}

	object_cause_damage(damage_data, object_index, node_index, region_index, material_index, predictability);
}

bool object_damage_update_overshield_hook(s_player_datum *player) // 0x10960550
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_damage_update_overshield_hook@@YA_NPAUs_player_datum@@@Z");
	// `anonymous-namespace'::object_damage_update_overshield_hook
	// static ...; // 0x109606D0
	// static ...; // 0x109606C4
	// static ...; // 0x109606BC
	// s_player_datum *player;
	// bool (*const sub_53AF10)(s_player_datum *);
	// long (*const get_shield_multiplier)(c_player_trait_shield_vitality *);
		// s_object_data *unit;
			// float max_shield_vitality;
				// float step;
				// unsigned long long update_flags;
	// function call : long (*const)(c_player_trait_shield_vitality *)
	// function call : float (*const)(float)
	// function call : void (*const)(long, unsigned long long *)
	// function call : bool (*const)(s_player_datum *)

	bool (*const sub_53AF10)(s_player_datum *) = reinterpret_cast<bool (*)(s_player_datum *)>(0x53AF10);
	long (__thiscall *const get_shield_multiplier)(c_player_trait_shield_vitality *) = reinterpret_cast<long (__thiscall *)(c_player_trait_shield_vitality *)>(0x5CC380);
	s_object_data *unit = object_get(player->unit_index);
	if (unit)
	{
		float max_shield_vitality = (float)get_shield_multiplier(&player->traits.vitality);
		if (unit->shield_vitality > max_shield_vitality)
		{
			float step = max_shield_vitality / game_seconds_to_ticks_real(45.0f);
			if (unit->shield_vitality - 1.0f >= step)
				unit->shield_vitality -= step;
			else
				unit->shield_vitality = max_shield_vitality;
			unsigned long long update_flags = 0x80;
			((void (*)(long, unsigned long long *))0x4B3010)(player->unit_index, &update_flags);
		}
	}
	return sub_53AF10(player);
}

void unit_resolve_melee_attack_hook(long unit_index, long definition_index, long secondary_definition_index, s_damage_owner *damage_owner, s_unit_player_melee_damage_target *target, bool a6, bool a7) // 0x10960740
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_resolve_melee_attack_hook@@YAXJJJPAUs_damage_owner@@PAUs_unit_player_melee_damage_target@hades_file_local@@_N2@Z");
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

	void (*const unit_resolve_melee_attack)(long, long, long, s_damage_owner *, s_unit_player_melee_damage_target *, bool, bool) = reinterpret_cast<void (*)(long, long, long, s_damage_owner *, s_unit_player_melee_damage_target *, bool, bool)>(0xB470F0);
	s_scenario_location location;
	((void (__cdecl *)(s_scenario_location *, real_point3d *))0x4EA940)(&location, &target->position);
	if (location.cluster_reference.bsp_index != -1)
		target->bsp_index = location.cluster_reference.bsp_index;

	if (target->breakable_surface_index != -1 && !((bool (__cdecl *)(long, long, long, long, long))0x56ACE0)(target->bsp_index, target->instanced_geometry_index, target->breakable_surface_set_index, target->breakable_surface_index, target->surface_index))
	{
		target->bsp_index = -1;
		target->instanced_geometry_index = -1;
		target->breakable_surface_set_index = -1;
		target->breakable_surface_index = -1;
		target->surface_index = -1;
	}

	unit_resolve_melee_attack(unit_index, definition_index, secondary_definition_index, damage_owner, target, a6, a7);
}
