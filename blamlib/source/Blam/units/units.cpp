/* ---------- headers */

#include "Blam/units/units.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

struct begin;
struct end;
struct s_damage_owner;
struct s_game_globals;
struct s_game_globals_grenade;
struct s_object_data;
struct s_object_placement_data;
struct s_unit_data;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

template<typename t_arg0> static t_arg0 *object_get(unsigned long object_index) { return (t_arg0 *)object_get(object_index); }  // hades: a file-local template in the original (undecorated `object_get<T>`), defined so it is emitted;  // hades: added for 0x10F0D040

extern void (*const object_placement_data_new)(s_object_placement_data *, long, unsigned long, s_damage_owner *);  // hades: added for 0x10F0CB70

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long object_index, c_enum<e_object_type, long> object_type_mask);  // hades: added for 0X10F0CE10

extern long unit_get_ultimate_motion_control_unit_index(long unit_index);
extern long unit_get_current_or_last_weak_player_index(long unit_index);
extern long unit_get_player_index(long unit_index);
extern void unit_drop_grenades(long unit_index);
extern void unit_drop_equipment(long unit_index, long slot_index);
extern bool unit_is_holding_objective(long unit_index);
extern bool unit_has_vision(long unit_index);

/* ---------- globals */

extern bool (*const unit_is_dual_wielding)(unsigned long); // 0x11249FDC

/* ---------- private variables */

/* ---------- public code */

long unit_get_ultimate_motion_control_unit_index(long unit_index) // 0x10F0CF80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_get_ultimate_motion_control_unit_index@@YAJJ@Z");

	for (;;)
	{
		s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003);
		if (!unit || *(long *)((unsigned char *)unit + 0x32C) == -1)
			break;

		unit_index = *(long *)((unsigned char *)unit + 0x32C);
	}

	return unit_index;
}

long unit_get_current_or_last_weak_player_index(long unit_index) // 0x10F0CE10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_get_current_or_last_weak_player_index@@YAJJ@Z");

	s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003);
	if (!unit)
		return -1;

	if (unit->player_index == -1)
		return unit->last_weak_player_index;
	else
		return unit->player_index;
}

long unit_get_player_index(long unit_index) // 0x10F0CED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_get_player_index@@YAJJ@Z");

	s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003);
	if (!unit)
		return NONE;
	else
		return unit->player_index;
}

void unit_drop_grenades(long unit_index) // 0x10F0CB70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_drop_grenades@@YAXJ@Z");

	s_game_globals *game_globals = game_globals_get();
	s_unit_data *unit = (s_unit_data *)object_get(unit_index);
	for (long i = 0; i < 4 && i < game_globals->Grenades.count; i++)
	{
		s_game_globals_grenade *grenade_type = &game_globals->Grenades[i];
		for (__int32 j = 0; j < unit->grenade_counts[i]; j++)
		{
			if (((bool (*)())0x5319C0)())
			{
				s_object_placement_data placement_data;
				object_placement_data_new(&placement_data, grenade_type->Equipment.index, unit_index, nullptr);
				long item_index = ((long (*)(s_object_placement_data *))0xB30440)(&placement_data);
				if (item_index != -1)
				{
					((void (*)(long, long))0xB49190)(unit_index, item_index);
					((void (*)(long, long, long))0xB40A70)(unit_index, item_index, 0);
				}
			}
		}
		unit->grenade_counts[i] = 0;
	}
}

void unit_drop_equipment(long unit_index, long slot_index) // 0x10F0C8F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_drop_equipment@@YAXJJ@Z");

	s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003);
	long equipment_index = unit->equipment_object_indices[slot_index];
	if (equipment_index == -1 || !((bool (*)())0x5319C0)())
		return;
	if (!((long (*)(long))0xB89190)(equipment_index))
	{
		((void (*)(long, long))0xB3FC50)(unit_index, 0);
	}
	else
	{
		s_object_data *equipment = object_try_and_get_and_verify_type(equipment_index, 8);
		((void (*)(long, long, long))0xB40A70)(unit_index, equipment_index, 0);
		if (!(equipment->physics_flags & 0x80))
			((void (*)(long))0xB31E20)(equipment_index);
		unit->equipment_object_indices[slot_index] = -1;
		unsigned long long component_flags = 0x10000000;
		((void (*)(long, unsigned long long *))0x4B3010)(unit_index, &component_flags);
	}
}

bool unit_is_holding_objective(long unit_index) // 0x10F0D1B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_is_holding_objective@@YA_NJ@Z");

	s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003);
	if (!unit)
		return false;
	for (char inventory_index : unit->current_weapon_set.indices)
	{
		if (inventory_index < 0)
			continue;
		long weapon_index = unit->weapon_object_indices[inventory_index];
		s_object_data *weapon = object_try_and_get_and_verify_type(weapon_index, 4);
		if (!weapon)
			continue;
		if (((short (*)(long))0xB62DB0)(weapon_index))
			return true;
	}
	return false;
}

bool unit_has_vision(long unit_index) // 0x10F0D040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_has_vision@@YA_NJ@Z");

	s_unit_data *unit = object_get<s_unit_data>(unit_index);
	if (!unit)
		return false;
	for (__int32 i = 0; i < unit->equipment_object_indices.get_count(); i++)
	{
		long equipment_index = unit->equipment_object_indices[i];
		s_object_data *equipment = object_try_and_get_and_verify_type(equipment_index, 8);
		if (!equipment)
			continue;
		if (((bool (*)(long))0xB88C80)(equipment_index) && ((bool (*)(long, long))0xBA0360)(equipment->definition_index, 23))
			return true;
	}
	return false;
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_game_globals_grenade>::try_get_element(__int32, s_game_globals_grenade **) const;
template char * s_static_array<char,2>::begin() const;
template char * s_static_array<char,2>::end() const;
template s_game_globals_grenade & c_tag_block<s_game_globals_grenade>::operator[](__int32);
template s_game_globals_grenade * c_tag_block<s_game_globals_grenade>::get_element(__int32) const;

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
bool (*const unit_is_dual_wielding)(unsigned long) = reinterpret_cast<decltype(unit_is_dual_wielding)>(0xB45750);
