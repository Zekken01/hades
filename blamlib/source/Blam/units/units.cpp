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

_extern long _sub_10F0CF80(long);
long unit_get_ultimate_motion_control_unit_index(long unit_index) // 0x10F0CF80
{
	mangled_x86(MANGLED_TODO, "?unit_get_ultimate_motion_control_unit_index@@YAJJ@Z");
	// long unit_index;
	{
		// s_unit_data *unit;
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	long __result = _sub_10F0CF80(unit_index);
	return __result;
}

_extern long _sub_10F0CE10(long);
long unit_get_current_or_last_weak_player_index(long unit_index) // 0x10F0CE10
{
	mangled_x86(MANGLED_TODO, "?unit_get_current_or_last_weak_player_index@@YAJJ@Z");
	// long unit_index;
	// s_unit_data *unit;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	long __result = _sub_10F0CE10(unit_index);
	return __result;
}

_extern long _sub_10F0CED0(long);
long unit_get_player_index(long unit_index) // 0x10F0CED0
{
	mangled_x86(MANGLED_TODO, "?unit_get_player_index@@YAJJ@Z");
	// long unit_index;
	// s_unit_data *unit;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	long __result = _sub_10F0CED0(unit_index);
	return __result;
}

_extern void _sub_10F0CB70(long);
void unit_drop_grenades(long unit_index) // 0x10F0CB70
{
	mangled_x86(MANGLED_TODO, "?unit_drop_grenades@@YAXJ@Z");
	// static ...; // 0x10F0CD70
	// static ...; // 0x10F0CD64
	// static ...; // 0x10F0CD5C
	// long unit_index;
	// s_unit_data *unit;
	// s_game_globals *game_globals;
	{
		// long i;
		{
			// s_game_globals_grenade *grenade_type;
			{
				// __int32 j;
				{
					// long item_index;
					// s_object_placement_data placement_data;
				}
			}
		}
	}
	// function call : bool (*const)()
	// function call : void (*const)(s_object_placement_data *, long, unsigned long, s_damage_owner *)
	// function call : long (*const)(s_object_placement_data *)
	// function call : void (*const)(long, long)
	// function call : void (*const)(long, long, long)
	todo("implement");
	_sub_10F0CB70(unit_index);
}

_extern void _sub_10F0C8F0(long, long);
void unit_drop_equipment(long unit_index, long slot_index) // 0x10F0C8F0
{
	mangled_x86(MANGLED_TODO, "?unit_drop_equipment@@YAXJJ@Z");
	// static ...; // 0x10F0CACC
	// static ...; // 0x10F0CAC4
	// long unit_index;
	// long slot_index;
	// s_unit_data *unit;
	// long equipment_index;
	{
		// s_object_data *equipment;
		// unsigned long long component_flags;
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : bool (*const)()
	// function call : long (*const)(long)
	// function call : void (*const)(long, long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, long, long)
	// function call : void (*const)(long)
	// function call : void (*const)(long, unsigned long long *)
	todo("implement");
	_sub_10F0C8F0(unit_index, slot_index);
}

_extern bool _sub_10F0D1B0(long);
bool unit_is_holding_objective(long unit_index) // 0x10F0D1B0
{
	mangled_x86(MANGLED_TODO, "?unit_is_holding_objective@@YA_NJ@Z");
	// long unit_index;
	// s_unit_data *unit;
	{
		// s_static_array<char,2> &<range>$L0;
		// char *<begin>$L0;
		// char *<end>$L0;
		{
			// char inventory_index;
			{
				// long weapon_index;
				// s_object_data *weapon;
			}
		}
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : short (*const)(long)
	todo("implement");
	bool __result = _sub_10F0D1B0(unit_index);
	return __result;
}

_extern bool _sub_10F0D040(long);
bool unit_has_vision(long unit_index) // 0x10F0D040
{
	mangled_x86(MANGLED_TODO, "?unit_has_vision@@YA_NJ@Z");
	// long unit_index;
	// s_unit_data *unit;
	{
		// __int32 i;
		{
			// s_object_data *equipment;
			// long equipment_index;
		}
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : bool (*const)(long)
	// function call : bool (*const)(long, e_equipment_type)
	todo("implement");
	bool __result = _sub_10F0D040(unit_index);
	return __result;
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
