/* ---------- headers */

#include "Blam/game/engine/game_engine_player_traits.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"

/* ---------- forward declarations */

class c_bitstream;
struct c_player_trait_appearance;
struct c_player_trait_extended;
struct c_player_trait_movement;
struct c_player_trait_sensors;
struct c_player_trait_shield_vitality;
struct c_player_trait_weapons;
struct c_player_traits;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_10F051E0(c_player_trait_shield_vitality *const);
void c_player_trait_shield_vitality::initialize() // 0x10F051E0
{
	mangled_x86(MANGLED_TODO, "?initialize@c_player_trait_shield_vitality@@QAEXXZ");
	// c_player_trait_shield_vitality *const this;
	todo("implement");
	_sub_10F051E0(this);
}

_extern void _sub_10F05670(c_player_trait_shield_vitality *const, c_player_trait_shield_vitality const *, bool);
void c_player_trait_shield_vitality::set(c_player_trait_shield_vitality const *traits, bool can_inherit) // 0x10F05670
{
	mangled_x86(MANGLED_TODO, "?set@c_player_trait_shield_vitality@@QAEXPBU1@_N@Z");
	// bool can_inherit;
	todo("implement");
	_sub_10F05670(this, traits, can_inherit);
}

_extern float _sub_10F04C20(c_player_trait_shield_vitality const *const);
float c_player_trait_shield_vitality::get_damage_resistance_percentage() const // 0x10F04C20
{
	mangled_x86(MANGLED_TODO, "?get_damage_resistance_percentage@c_player_trait_shield_vitality@@QBEMXZ");
	// static ...; // 0x10F04D00
// $LN18:
// $LN17:
// $LN15:
// $LN14:
// $LN13:
// $LN12:
// $LN11:
// $LN10:
// $LN9:
// $LN8:
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// c_player_trait_shield_vitality const *const this;
	todo("implement");
	float __result = _sub_10F04C20((c_player_trait_shield_vitality const *)this);
	return __result;
}

void c_player_trait_shield_vitality::set_damage_resistance_setting(c_player_trait_shield_vitality::e_damage_resistance_setting value, bool can_inherit) // 0x10F05AB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_damage_resistance_setting@c_player_trait_shield_vitality@@QAEXW4e_damage_resistance_setting@1@_N@Z");
	// bool can_inherit;

	if (value < _damage_resistance_unchanged || value >= k_damage_resistance_setting_count)
	{
		return;
	}
	else if (value != _damage_resistance_unchanged || can_inherit)
	{
		damage_resistance = (unsigned char)value;
	}
}

void c_player_trait_shield_vitality::set_shield_recharge_rate_setting(c_player_trait_shield_vitality::e_shield_recharge_rate_setting value, bool can_inherit) // 0x10F06310
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_shield_recharge_rate_setting@c_player_trait_shield_vitality@@QAEXW4e_shield_recharge_rate_setting@1@_N@Z");
	// bool can_inherit;

	if (value < _shield_recharge_rate_unchanged || value >= k_shield_recharge_rate_setting_count)
	{
		return;
	}
	else if (value != _shield_recharge_rate_unchanged || can_inherit)
	{
		shield_recharge_rate = (unsigned char)value;
	}
}

void c_player_trait_shield_vitality::set_shield_vampirism_setting(c_player_trait_shield_vitality::e_shield_vampirism_setting value, bool can_inherit) // 0x10F06390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_shield_vampirism_setting@c_player_trait_shield_vitality@@QAEXW4e_shield_vampirism_setting@1@_N@Z");
	// bool can_inherit;

	if (value < _shield_vampirism_unchanged || value >= k_shield_vampirism_setting_count)
	{
		return;
	}
	else if (value != _shield_vampirism_unchanged || can_inherit)
	{
		shield_vampirism = (unsigned char)value;
	}
}

void c_player_trait_shield_vitality::set_headshot_immunity_setting(c_player_trait_shield_vitality::e_headshot_immunity_setting value, bool can_inherit) // 0x10F05C30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_headshot_immunity_setting@c_player_trait_shield_vitality@@QAEXW4e_headshot_immunity_setting@1@_N@Z");
	// bool can_inherit;

	if (value < _headshot_immunity_unchanged || value >= k_headshot_immunity_setting_count)
	{
		return;
	}
	else if (value != _headshot_immunity_unchanged || can_inherit)
	{
		headshot_immunity = (unsigned char)value;
	}
}

void c_player_trait_shield_vitality::set_shield_multiplier_setting(c_player_trait_shield_vitality::e_shield_multiplier_setting value, bool can_inherit) // 0x10F06290
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_shield_multiplier_setting@c_player_trait_shield_vitality@@QAEXW4e_shield_multiplier_setting@1@_N@Z");
	// bool can_inherit;

	if (value < _shield_multiplier_unchanged || value >= k_shield_multiplier_setting_count)
	{
		return;
	}
	else if (value != _shield_multiplier_unchanged || can_inherit)
	{
		shield_multiplier = (unsigned char)value;
	}
}

_extern void _sub_10F04230(c_player_trait_shield_vitality const *const, c_bitstream *);
void c_player_trait_shield_vitality::encode(c_bitstream *packet) const // 0x10F04230
{
	mangled_x86(MANGLED_TODO, "?encode@c_player_trait_shield_vitality@@QBEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;
	todo("implement");
	_sub_10F04230((c_player_trait_shield_vitality const *)this, packet);
}

_extern void _sub_10F03BD0(c_player_trait_shield_vitality *const, c_bitstream *);
void c_player_trait_shield_vitality::decode(c_bitstream *packet) // 0x10F03BD0
{
	mangled_x86(MANGLED_TODO, "?decode@c_player_trait_shield_vitality@@QAEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;
	todo("implement");
	_sub_10F03BD0(this, packet);
}

_extern bool _sub_10F04890(c_player_trait_shield_vitality const *const, c_player_trait_shield_vitality const *);
bool c_player_trait_shield_vitality::equivalent(c_player_trait_shield_vitality const *traits) const // 0x10F04890
{
	mangled_x86(MANGLED_TODO, "?equivalent@c_player_trait_shield_vitality@@QBE_NPBU1@@Z");
	// c_player_trait_shield_vitality const *traits;
	todo("implement");
	bool __result = _sub_10F04890((c_player_trait_shield_vitality const *)this, traits);
	return __result;
}

_extern void _sub_10F05260(c_player_trait_weapons *const);
void c_player_trait_weapons::initialize() // 0x10F05260
{
	mangled_x86(MANGLED_TODO, "?initialize@c_player_trait_weapons@@QAEXXZ");
	// c_player_trait_weapons *const this;
	todo("implement");
	_sub_10F05260(this);
}

_extern void _sub_10F05750(c_player_trait_weapons *const, c_player_trait_weapons const *, bool);
void c_player_trait_weapons::set(c_player_trait_weapons const *traits, bool can_inherit) // 0x10F05750
{
	mangled_x86(MANGLED_TODO, "?set@c_player_trait_weapons@@QAEXPBU1@_N@Z");
	// bool can_inherit;
	todo("implement");
	_sub_10F05750(this, traits, can_inherit);
}

void c_player_trait_weapons::set_initial_grenade_count_setting(c_player_trait_weapons::e_grenade_count_setting value, bool can_inherit) // 0x10F05D30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_initial_grenade_count_setting@c_player_trait_weapons@@QAEXW4e_grenade_count_setting@1@_N@Z");
	// bool can_inherit;

	if (value < _grenade_count_unchanged || value >= k_grenade_count_setting_count)
	{
		return;
	}
	else if (value != _grenade_count_unchanged || can_inherit)
	{
		initial_grenade_count = (unsigned short)value;
	}
}

_extern void _sub_10F05DC0(c_player_trait_weapons *const, char, bool);
void c_player_trait_weapons::set_initial_primary_weapon_absolute_index(char index, bool can_inherit) // 0x10F05DC0
{
	mangled_x86(MANGLED_TODO, "?set_initial_primary_weapon_absolute_index@c_player_trait_weapons@@QAEXD_N@Z");
	// bool can_inherit;
	todo("implement");
	_sub_10F05DC0(this, index, can_inherit);
}

_extern void _sub_10F05E80(c_player_trait_weapons *const, char, bool);
void c_player_trait_weapons::set_initial_secondary_weapon_absolute_index(char index, bool can_inherit) // 0x10F05E80
{
	mangled_x86(MANGLED_TODO, "?set_initial_secondary_weapon_absolute_index@c_player_trait_weapons@@QAEXD_N@Z");
	// bool can_inherit;
	todo("implement");
	_sub_10F05E80(this, index, can_inherit);
}

void c_player_trait_weapons::set_damage_modifier_setting(c_player_trait_weapons::e_damage_modifier_setting value, bool can_inherit) // 0x10F05A30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_damage_modifier_setting@c_player_trait_weapons@@QAEXW4e_damage_modifier_setting@1@_N@Z");
	// bool can_inherit;

	if (value < _damage_modifier_unchanged || value >= k_damage_modifier_setting_count)
	{
		return;
	}
	else if (value != _damage_modifier_unchanged || can_inherit)
	{
		damage_modifier = (unsigned char)value;
	}
}

void c_player_trait_weapons::set_recharging_grenades_setting(c_player_trait_weapons::e_recharging_grenades_setting value, bool can_inherit) // 0x10F06210
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_recharging_grenades_setting@c_player_trait_weapons@@QAEXW4e_recharging_grenades_setting@1@_N@Z");
	// bool can_inherit;

	if (value < _recharging_grenades_unchanged || value >= k_recharging_grenades_setting_count)
	{
		return;
	}
	else if (value != _recharging_grenades_unchanged || can_inherit)
	{
		recharging_grenades = (unsigned char)value;
	}
}

void c_player_trait_weapons::set_infinite_ammo_setting(c_player_trait_weapons::e_infinite_ammo_setting value, bool can_inherit) // 0x10F05CB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_infinite_ammo_setting@c_player_trait_weapons@@QAEXW4e_infinite_ammo_setting@1@_N@Z");
	// bool can_inherit;

	if (value < _infinite_ammo_unchanged || value >= k_infinite_ammo_setting_setting_count)
	{
		return;
	}
	else if (value != _infinite_ammo_unchanged || can_inherit)
	{
		infinite_ammo = (unsigned char)value;
	}
}

void c_player_trait_weapons::set_weapon_pickup_setting(c_player_trait_weapons::e_weapon_pickup_setting value, bool can_inherit) // 0x10F066D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_weapon_pickup_setting@c_player_trait_weapons@@QAEXW4e_weapon_pickup_setting@1@_N@Z");
	// bool can_inherit;

	if (value < _weapon_pickup_unchanged || value >= k_weapon_pickup_setting_count)
	{
		return;
	}
	else if (value != _weapon_pickup_unchanged || can_inherit)
	{
		weapon_pickup = (unsigned char)value;
	}
}

_extern void _sub_10F04310(c_player_trait_weapons const *const, c_bitstream *);
void c_player_trait_weapons::encode(c_bitstream *packet) const // 0x10F04310
{
	mangled_x86(MANGLED_TODO, "?encode@c_player_trait_weapons@@QBEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;
	todo("implement");
	_sub_10F04310((c_player_trait_weapons const *)this, packet);
}

_extern void _sub_10F03CD0(c_player_trait_weapons *const, c_bitstream *);
void c_player_trait_weapons::decode(c_bitstream *packet) // 0x10F03CD0
{
	mangled_x86(MANGLED_TODO, "?decode@c_player_trait_weapons@@QAEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;
	todo("implement");
	_sub_10F03CD0(this, packet);
}

_extern bool _sub_10F04980(c_player_trait_weapons const *const, c_player_trait_weapons const *);
bool c_player_trait_weapons::equivalent(c_player_trait_weapons const *traits) const // 0x10F04980
{
	mangled_x86(MANGLED_TODO, "?equivalent@c_player_trait_weapons@@QBE_NPBU1@@Z");
	// c_player_trait_weapons const *traits;
	todo("implement");
	bool __result = _sub_10F04980((c_player_trait_weapons const *)this, traits);
	return __result;
}

_extern void _sub_10F05100(c_player_trait_movement *const);
void c_player_trait_movement::initialize() // 0x10F05100
{
	mangled_x86(MANGLED_TODO, "?initialize@c_player_trait_movement@@QAEXXZ");
	// c_player_trait_movement *const this;
	todo("implement");
	_sub_10F05100(this);
}

_extern void _sub_10F05530(c_player_trait_movement *const, c_player_trait_movement const *, bool);
void c_player_trait_movement::set(c_player_trait_movement const *traits, bool can_inherit) // 0x10F05530
{
	mangled_x86(MANGLED_TODO, "?set@c_player_trait_movement@@QAEXPBU1@_N@Z");
	// bool can_inherit;
	todo("implement");
	_sub_10F05530(this, traits, can_inherit);
}

_extern float _sub_10F04EB0(c_player_trait_movement const *const);
float c_player_trait_movement::get_speed() const // 0x10F04EB0
{
	mangled_x86(MANGLED_TODO, "?get_speed@c_player_trait_movement@@QBEMXZ");
	// static ...; // 0x10F04F70
// $LN13:
// $LN12:
// $LN11:
// $LN10:
// $LN9:
// $LN8:
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// c_player_trait_movement const *const this;
	todo("implement");
	float __result = _sub_10F04EB0((c_player_trait_movement const *)this);
	return __result;
}

_extern float _sub_10F04D90(c_player_trait_movement const *const);
float c_player_trait_movement::get_gravity() const // 0x10F04D90
{
	mangled_x86(MANGLED_TODO, "?get_gravity@c_player_trait_movement@@QBEMXZ");
	// static ...; // 0x10F04E48
// $LN12:
// $LN11:
// $LN10:
// $LN9:
// $LN8:
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// c_player_trait_movement const *const this;
	todo("implement");
	float __result = _sub_10F04D90((c_player_trait_movement const *)this);
	return __result;
}

void c_player_trait_movement::set_speed_setting(c_player_trait_movement::e_speed_setting value, bool can_inherit) // 0x10F06410
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_speed_setting@c_player_trait_movement@@QAEXW4e_speed_setting@1@_N@Z");
	// bool can_inherit;

	if (value < _speed_unchanged || value >= k_player_speed_setting_count)
	{
		return;
	}
	else if (value != _speed_unchanged || can_inherit)
	{
		player_speed = (unsigned char)value;
	}
}

void c_player_trait_movement::set_gravity_setting(c_player_trait_movement::e_gravity_setting value, bool can_inherit) // 0x10F05BB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_gravity_setting@c_player_trait_movement@@QAEXW4e_gravity_setting@1@_N@Z");
	// bool can_inherit;

	if (value < _gravity_unchanged || value >= k_player_gravity_setting_count)
	{
		return;
	}
	else if (value != _gravity_unchanged || can_inherit)
	{
		player_gravity = (unsigned char)value;
	}
}

void c_player_trait_movement::set_vehicle_usage_setting(c_player_trait_movement::e_vehicle_usage_setting value, bool can_inherit) // 0x10F065D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_vehicle_usage_setting@c_player_trait_movement@@QAEXW4e_vehicle_usage_setting@1@_N@Z");
	// bool can_inherit;

	if (value < _vehicle_usage_unchanged || value >= k_vehicle_usage_setting_count)
	{
		return;
	}
	else if (value != _vehicle_usage_unchanged || can_inherit)
	{
		vehicle_usage = (unsigned char)value;
	}
}

_extern void _sub_10F040F0(c_player_trait_movement const *const, c_bitstream *);
void c_player_trait_movement::encode(c_bitstream *packet) const // 0x10F040F0
{
	mangled_x86(MANGLED_TODO, "?encode@c_player_trait_movement@@QBEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;
	todo("implement");
	_sub_10F040F0((c_player_trait_movement const *)this, packet);
}

_extern void _sub_10F03A70(c_player_trait_movement *const, c_bitstream *);
void c_player_trait_movement::decode(c_bitstream *packet) // 0x10F03A70
{
	mangled_x86(MANGLED_TODO, "?decode@c_player_trait_movement@@QAEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;
	todo("implement");
	_sub_10F03A70(this, packet);
}

_extern bool _sub_10F04730(c_player_trait_movement const *const, c_player_trait_movement const *);
bool c_player_trait_movement::equivalent(c_player_trait_movement const *traits) const // 0x10F04730
{
	mangled_x86(MANGLED_TODO, "?equivalent@c_player_trait_movement@@QBE_NPBU1@@Z");
	// c_player_trait_movement const *traits;
	todo("implement");
	bool __result = _sub_10F04730((c_player_trait_movement const *)this, traits);
	return __result;
}

_extern void _sub_10F04FE0(c_player_trait_appearance *const);
void c_player_trait_appearance::initialize() // 0x10F04FE0
{
	mangled_x86(MANGLED_TODO, "?initialize@c_player_trait_appearance@@QAEXXZ");
	// c_player_trait_appearance *const this;
	todo("implement");
	_sub_10F04FE0(this);
}

_extern void _sub_10F05390(c_player_trait_appearance *const, c_player_trait_appearance const *, bool);
void c_player_trait_appearance::set(c_player_trait_appearance const *traits, bool can_inherit) // 0x10F05390
{
	mangled_x86(MANGLED_TODO, "?set@c_player_trait_appearance@@QAEXPBU1@_N@Z");
	// bool can_inherit;
	todo("implement");
	_sub_10F05390(this, traits, can_inherit);
}

void c_player_trait_appearance::set_active_camo_setting(c_player_trait_appearance::e_active_camo_setting value, bool can_inherit) // 0x10F059B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_active_camo_setting@c_player_trait_appearance@@QAEXW4e_active_camo_setting@1@_N@Z");
	// bool can_inherit;

	if (value < _active_camo_unchanged || value >= k_active_camo_setting_count)
	{
		return;
	}
	else if (value != _active_camo_unchanged || can_inherit)
	{
		active_camo = (unsigned char)value;
	}
}

void c_player_trait_appearance::set_waypoint_setting(c_player_trait_appearance::e_waypoint_setting value, bool can_inherit) // 0x10F06650
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_waypoint_setting@c_player_trait_appearance@@QAEXW4e_waypoint_setting@1@_N@Z");
	// bool can_inherit;

	if (value < _waypoint_unchanged || value >= k_waypoint_setting_count)
	{
		return;
	}
	else if (value != _waypoint_unchanged || can_inherit)
	{
		waypoint = (unsigned char)value;
	}
}

void c_player_trait_appearance::set_player_size_setting(c_player_trait_appearance::e_player_size_setting value, bool can_inherit) // 0x10F06190
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_player_size_setting@c_player_trait_appearance@@QAEXW4e_player_size_setting@1@_N@Z");
	// bool can_inherit;

	if (value < _player_size_unchanged || value >= k_player_size_setting_count)
	{
		return;
	}
	else if (value != _player_size_unchanged || can_inherit)
	{
		aura = (unsigned char)value;
	}
}

void c_player_trait_appearance::set_forced_change_color_setting(c_player_trait_appearance::e_forced_change_color_setting value, bool can_inherit) // 0x10F05B30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_forced_change_color_setting@c_player_trait_appearance@@QAEXW4e_forced_change_color_setting@1@_N@Z");
	// bool can_inherit;

	if (value < _forced_change_color_unchanged || value >= k_forced_change_color_setting_count)
	{
		return;
	}
	else if (value != _forced_change_color_unchanged || can_inherit)
	{
		forced_color = (unsigned char)value;
	}
}

_extern void _sub_10F03F30(c_player_trait_appearance const *const, c_bitstream *);
void c_player_trait_appearance::encode(c_bitstream *packet) const // 0x10F03F30
{
	mangled_x86(MANGLED_TODO, "?encode@c_player_trait_appearance@@QBEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;
	todo("implement");
	_sub_10F03F30((c_player_trait_appearance const *)this, packet);
}

_extern void _sub_10F038B0(c_player_trait_appearance *const, c_bitstream *);
void c_player_trait_appearance::decode(c_bitstream *packet) // 0x10F038B0
{
	mangled_x86(MANGLED_TODO, "?decode@c_player_trait_appearance@@QAEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;
	todo("implement");
	_sub_10F038B0(this, packet);
}

_extern bool _sub_10F04550(c_player_trait_appearance const *const, c_player_trait_appearance const *);
bool c_player_trait_appearance::equivalent(c_player_trait_appearance const *traits) const // 0x10F04550
{
	mangled_x86(MANGLED_TODO, "?equivalent@c_player_trait_appearance@@QBE_NPBU1@@Z");
	// c_player_trait_appearance const *traits;
	todo("implement");
	bool __result = _sub_10F04550((c_player_trait_appearance const *)this, traits);
	return __result;
}

_extern void _sub_10F05170(c_player_trait_sensors *const);
void c_player_trait_sensors::initialize() // 0x10F05170
{
	mangled_x86(MANGLED_TODO, "?initialize@c_player_trait_sensors@@QAEXXZ");
	// c_player_trait_sensors *const this;
	todo("implement");
	_sub_10F05170(this);
}

_extern void _sub_10F055E0(c_player_trait_sensors *const, c_player_trait_sensors const *, bool);
void c_player_trait_sensors::set(c_player_trait_sensors const *traits, bool can_inherit) // 0x10F055E0
{
	mangled_x86(MANGLED_TODO, "?set@c_player_trait_sensors@@QAEXPBU1@_N@Z");
	// bool can_inherit;
	todo("implement");
	_sub_10F055E0(this, traits, can_inherit);
}

void c_player_trait_sensors::set_motion_tracker_setting(c_player_trait_sensors::e_motion_tracker_setting value, bool can_inherit) // 0x10F05FD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_motion_tracker_setting@c_player_trait_sensors@@QAEXW4e_motion_tracker_setting@1@_N@Z");
	// bool can_inherit;

	if (value < _motion_tracker_unchanged || value >= k_motion_tracker_setting_count)
	{
		return;
	}
	else if (value != _motion_tracker_unchanged || can_inherit)
	{
		motion_tracker_mode = (unsigned short)value;
	}
}

void c_player_trait_sensors::set_motion_tracker_range_setting(c_player_trait_sensors::e_motion_tracker_range_setting value, bool can_inherit) // 0x10F05F40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_motion_tracker_range_setting@c_player_trait_sensors@@QAEXW4e_motion_tracker_range_setting@1@_N@Z");
	// bool can_inherit;

	if (value < _motion_tracker_range_unchanged || value >= k_motion_tracker_range_setting_count)
	{
		return;
	}
	else if (value != _motion_tracker_range_unchanged || can_inherit)
	{
		motion_tracker_range = (unsigned short)value;
	}
}

_extern void _sub_10F041A0(c_player_trait_sensors const *const, c_bitstream *);
void c_player_trait_sensors::encode(c_bitstream *packet) const // 0x10F041A0
{
	mangled_x86(MANGLED_TODO, "?encode@c_player_trait_sensors@@QBEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;
	todo("implement");
	_sub_10F041A0((c_player_trait_sensors const *)this, packet);
}

_extern void _sub_10F03B30(c_player_trait_sensors *const, c_bitstream *);
void c_player_trait_sensors::decode(c_bitstream *packet) // 0x10F03B30
{
	mangled_x86(MANGLED_TODO, "?decode@c_player_trait_sensors@@QAEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;
	todo("implement");
	_sub_10F03B30(this, packet);
}

_extern bool _sub_10F047F0(c_player_trait_sensors const *const, c_player_trait_sensors const *);
bool c_player_trait_sensors::equivalent(c_player_trait_sensors const *traits) const // 0x10F047F0
{
	mangled_x86(MANGLED_TODO, "?equivalent@c_player_trait_sensors@@QBE_NPBU1@@Z");
	// c_player_trait_sensors const *traits;
	todo("implement");
	bool __result = _sub_10F047F0((c_player_trait_sensors const *)this, traits);
	return __result;
}

_extern void _sub_10F05050(c_player_trait_extended *const);
void c_player_trait_extended::initialize() // 0x10F05050
{
	mangled_x86(MANGLED_TODO, "?initialize@c_player_trait_extended@@QAEXXZ");
	// c_player_trait_extended *const this;
	todo("implement");
	_sub_10F05050(this);
}

_extern void _sub_10F05450(c_player_trait_extended *const, c_player_trait_extended const *, bool);
void c_player_trait_extended::set(c_player_trait_extended const *traits, bool can_inherit) // 0x10F05450
{
	mangled_x86(MANGLED_TODO, "?set@c_player_trait_extended@@QAEXPBU1@_N@Z");
	// bool can_inherit;
	todo("implement");
	_sub_10F05450(this, traits, can_inherit);
}

_extern void _sub_10F06060(c_player_trait_extended *const, unsigned char, bool);
void c_player_trait_extended::set_player_model_absolute_index(unsigned char index, bool can_inherit) // 0x10F06060
{
	mangled_x86(MANGLED_TODO, "?set_player_model_absolute_index@c_player_trait_extended@@QAEXE_N@Z");
	// bool can_inherit;
	todo("implement");
	_sub_10F06060(this, index, can_inherit);
}

_extern void _sub_10F060F0(c_player_trait_extended *const, unsigned char, bool);
void c_player_trait_extended::set_player_model_set_absolute_index(unsigned char index, bool can_inherit) // 0x10F060F0
{
	mangled_x86(MANGLED_TODO, "?set_player_model_set_absolute_index@c_player_trait_extended@@QAEXE_N@Z");
	// bool can_inherit;
	todo("implement");
	_sub_10F060F0(this, index, can_inherit);
}

void c_player_trait_extended::set_sprint_setting(c_player_trait_extended::e_sprint_setting value, bool can_inherit) // 0x10F06490
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_sprint_setting@c_player_trait_extended@@QAEXW4e_sprint_setting@1@_N@Z");
	// bool can_inherit;

	if (value < _sprint_unchanged || value >= k_sprint_setting_count)
	{
		return;
	}
	else if (value != _sprint_unchanged || can_inherit)
	{
		sprint_allowed = (unsigned char)value;
	}
}

void c_player_trait_extended::set_third_person_camera_setting(c_player_trait_extended::e_third_person_camera value, bool can_inherit) // 0x10F06530
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_third_person_camera_setting@c_player_trait_extended@@QAEXW4e_third_person_camera@1@_N@Z");
	// bool can_inherit;

	if (value < _third_person_camera_unchanged || value >= k_third_person_camera_setting_count)
	{
		return;
	}
	else if (value != _third_person_camera_unchanged || can_inherit)
	{
		use_third_person_camera = (unsigned char)value;
	}
}

_extern void _sub_10F04000(c_player_trait_extended const *const, c_bitstream *);
void c_player_trait_extended::encode(c_bitstream *packet) const // 0x10F04000
{
	mangled_x86(MANGLED_TODO, "?encode@c_player_trait_extended@@QBEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;
	todo("implement");
	_sub_10F04000((c_player_trait_extended const *)this, packet);
}

_extern void _sub_10F03990(c_player_trait_extended *const, c_bitstream *);
void c_player_trait_extended::decode(c_bitstream *packet) // 0x10F03990
{
	mangled_x86(MANGLED_TODO, "?decode@c_player_trait_extended@@QAEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;
	todo("implement");
	_sub_10F03990(this, packet);
}

_extern bool _sub_10F04620(c_player_trait_extended const *const, c_player_trait_extended const *);
bool c_player_trait_extended::equivalent(c_player_trait_extended const *traits) const // 0x10F04620
{
	mangled_x86(MANGLED_TODO, "?equivalent@c_player_trait_extended@@QBE_NPBU1@@Z");
	// c_player_trait_extended const *traits;
	todo("implement");
	bool __result = _sub_10F04620((c_player_trait_extended const *)this, traits);
	return __result;
}

_extern void _sub_10F052F0(c_player_traits *const);
void c_player_traits::initialize() // 0x10F052F0
{
	mangled_x86(MANGLED_TODO, "?initialize@c_player_traits@@QAEXXZ");
	// c_player_traits *const this;
	todo("implement");
	_sub_10F052F0(this);
}

_extern void _sub_10F05860(c_player_traits *const, c_player_traits const *, bool);
void c_player_traits::set(c_player_traits const *traits, bool can_inherit) // 0x10F05860
{
	mangled_x86(MANGLED_TODO, "?set@c_player_traits@@QAEXPBU1@_N@Z");
	// bool can_inherit;
	todo("implement");
	_sub_10F05860(this, traits, can_inherit);
}

_extern void _sub_10F04430(c_player_traits const *const, c_bitstream *);
void c_player_traits::encode(c_bitstream *packet) const // 0x10F04430
{
	mangled_x86(MANGLED_TODO, "?encode@c_player_traits@@QBEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;
	todo("implement");
	_sub_10F04430((c_player_traits const *)this, packet);
}

_extern void _sub_10F03E10(c_player_traits *const, c_bitstream *);
void c_player_traits::decode(c_bitstream *packet) // 0x10F03E10
{
	mangled_x86(MANGLED_TODO, "?decode@c_player_traits@@QAEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;
	todo("implement");
	_sub_10F03E10(this, packet);
}

_extern bool _sub_10F04A90(c_player_traits const *const, c_player_traits const *);
bool c_player_traits::equivalent(c_player_traits const *traits) const // 0x10F04A90
{
	mangled_x86(MANGLED_TODO, "?equivalent@c_player_traits@@QBE_NPBU1@@Z");
	// c_player_traits const *traits;
	todo("implement");
	bool __result = _sub_10F04A90((c_player_traits const *)this, traits);
	return __result;
}

/* ---------- private code */
