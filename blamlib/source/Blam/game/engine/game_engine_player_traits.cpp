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

void c_player_trait_shield_vitality::initialize() // 0x10F051E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize@c_player_trait_shield_vitality@@QAEXXZ");
	// c_player_trait_shield_vitality *const this;

	damage_resistance = 4;
	shield_recharge_rate = 7;
	shield_vampirism = 1;
	headshot_immunity = 2;
	shield_multiplier = 2;
}

void c_player_trait_shield_vitality::set(c_player_trait_shield_vitality const *traits, bool can_inherit) // 0x10F05670
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set@c_player_trait_shield_vitality@@QAEXPBU1@_N@Z");
	// bool can_inherit;

	set_damage_resistance_setting((e_damage_resistance_setting)traits->damage_resistance, can_inherit);
	set_shield_recharge_rate_setting((e_shield_recharge_rate_setting)traits->shield_recharge_rate, can_inherit);
	set_shield_vampirism_setting((e_shield_vampirism_setting)traits->shield_vampirism, can_inherit);
	set_headshot_immunity_setting((e_headshot_immunity_setting)traits->headshot_immunity, can_inherit);
	set_shield_multiplier_setting((e_shield_multiplier_setting)traits->shield_multiplier, can_inherit);
}

float c_player_trait_shield_vitality::get_damage_resistance_percentage() const // 0x10F04C20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_damage_resistance_percentage@c_player_trait_shield_vitality@@QBEMXZ");
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

	switch (damage_resistance)
	{
	case _damage_resistance_10:
		return 0.1f;
	case _damage_resistance_50:
		return 0.5f;
	case _damage_resistance_90:
		return 0.9f;
	case _damage_resistance_normal:
		return 1.0f;
	case _damage_resistance_110:
		return 1.1f;
	case _damage_resistance_150:
		return 1.5f;
	case _damage_resistance_200:
		return 2.0f;
	case _damage_resistance_300:
		return 3.0f;
	case _damage_resistance_500:
		return 5.0f;
	case _damage_resistance_1000:
		return 10.0f;
	case _damage_resistance_2000:
		return 20.0f;
	case _damage_resistance_invulnerable:
	case _damage_resistance_invincible:
		return 1000.0f;
	case _damage_resistance_1500:
		return 15.0f;
	case _damage_resistance_3000:
		return 30.0f;
	}

	return 1.0f;
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

void c_player_trait_shield_vitality::encode(c_bitstream *packet) const // 0x10F04230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?encode@c_player_trait_shield_vitality@@QBEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;

	packet->write_integer("player-trait-damage-resistance", damage_resistance, 4);
	packet->write_integer("player-trait-shield-recharge-rate", shield_recharge_rate, 4);
	packet->write_integer("player-trait-vampirism", shield_vampirism, 3);
	packet->write_integer("player-traits-headshot-immunity", headshot_immunity, 2);
	packet->write_integer("player-trait-shield-multiplier", shield_multiplier, 3);
}

void c_player_trait_shield_vitality::decode(c_bitstream *packet) // 0x10F03BD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?decode@c_player_trait_shield_vitality@@QAEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;

	set_damage_resistance_setting((e_damage_resistance_setting)packet->read_integer("player-trait-damage-resistance", 4), true);
	set_shield_recharge_rate_setting((e_shield_recharge_rate_setting)packet->read_integer("player-trait-shield-recharge-rate", 4), true);
	set_shield_vampirism_setting((e_shield_vampirism_setting)packet->read_integer("player-trait-vampirism", 3), true);
	set_headshot_immunity_setting((e_headshot_immunity_setting)packet->read_integer("player-traits-headshot-immunity", 2), true);
	set_shield_multiplier_setting((e_shield_multiplier_setting)packet->read_integer("player-trait-shield-multiplier", 3), true);
}

bool c_player_trait_shield_vitality::equivalent(c_player_trait_shield_vitality const *traits) const // 0x10F04890
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?equivalent@c_player_trait_shield_vitality@@QBE_NPBU1@@Z");
	// c_player_trait_shield_vitality const *traits;

	return damage_resistance == traits->damage_resistance && shield_recharge_rate == traits->shield_recharge_rate && shield_vampirism == traits->shield_vampirism && headshot_immunity == traits->headshot_immunity && shield_multiplier == traits->shield_multiplier;
}

void c_player_trait_weapons::initialize() // 0x10F05260
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize@c_player_trait_weapons@@QAEXXZ");
	// c_player_trait_weapons *const this;

	initial_grenade_count = 1;
	initial_primary_weapon = -1;
	initial_secondary_weapon = -1;
	damage_modifier = 6;
	recharging_grenades = 2;
	infinite_ammo = 1;
	weapon_pickup = 1;
}

void c_player_trait_weapons::set(c_player_trait_weapons const *traits, bool can_inherit) // 0x10F05750
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set@c_player_trait_weapons@@QAEXPBU1@_N@Z");
	// bool can_inherit;

	set_initial_grenade_count_setting((e_grenade_count_setting)traits->initial_grenade_count, can_inherit);
	set_initial_primary_weapon_absolute_index(traits->initial_primary_weapon, can_inherit);
	set_initial_secondary_weapon_absolute_index(traits->initial_secondary_weapon, can_inherit);
	set_damage_modifier_setting((e_damage_modifier_setting)traits->damage_modifier, can_inherit);
	set_recharging_grenades_setting((e_recharging_grenades_setting)traits->recharging_grenades, can_inherit);
	set_infinite_ammo_setting((e_infinite_ammo_setting)traits->infinite_ammo, can_inherit);
	set_weapon_pickup_setting((e_weapon_pickup_setting)traits->weapon_pickup, can_inherit);
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

void c_player_trait_weapons::set_initial_primary_weapon_absolute_index(char index, bool can_inherit) // 0x10F05DC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_initial_primary_weapon_absolute_index@c_player_trait_weapons@@QAEXD_N@Z");
	// bool can_inherit;

	if (index == -1 || index == -2 || index == -3 || index >= 0)
	{
		if (index != -2 || can_inherit)
		{
			initial_primary_weapon = index;
		}
	}
	else if (can_inherit)
	{
		initial_primary_weapon = -2;
	}
}

void c_player_trait_weapons::set_initial_secondary_weapon_absolute_index(char index, bool can_inherit) // 0x10F05E80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_initial_secondary_weapon_absolute_index@c_player_trait_weapons@@QAEXD_N@Z");
	// bool can_inherit;

	if (index == -1 || index == -2 || index == -3 || index >= 0)
	{
		if (index != -2 || can_inherit)
			initial_secondary_weapon = index;
	}
	else if (can_inherit)
	{
		initial_secondary_weapon = -2;
	}
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

void c_player_trait_weapons::encode(c_bitstream *packet) const // 0x10F04310
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?encode@c_player_trait_weapons@@QBEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;

	packet->write_integer("player-trait-damage-modifier", damage_modifier, 4);
	packet->write_signed_integer("player-trait-initial-primary-weapon", initial_primary_weapon, 8);
	packet->write_signed_integer("player-trait-initial-secondary-weapon", initial_secondary_weapon, 8);
	packet->write_integer("player-trait-initial-grenade-count", initial_grenade_count, 2);
	packet->write_integer("player-traits-infinite-ammo-setting", infinite_ammo, 2);
	packet->write_integer("player-traits-recharging-grenades", recharging_grenades, 2);
	packet->write_integer("player-traits-weapon-pickup-allowed", weapon_pickup, 2);
}

void c_player_trait_weapons::decode(c_bitstream *packet) // 0x10F03CD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?decode@c_player_trait_weapons@@QAEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;

	set_damage_modifier_setting((e_damage_modifier_setting)packet->read_integer("player-trait-damage-modifier", 4), true);
	set_initial_primary_weapon_absolute_index((char)packet->read_signed_integer("player-trait-initial-primary-weapon", 8), true);
	set_initial_secondary_weapon_absolute_index((char)packet->read_signed_integer("player-trait-initial-secondary-weapon", 8), true);
	set_initial_grenade_count_setting((e_grenade_count_setting)packet->read_integer("player-trait-initial-grenade-count", 2), true);
	set_infinite_ammo_setting((e_infinite_ammo_setting)packet->read_integer("player-traits-infinite-ammo-setting", 2), true);
	set_recharging_grenades_setting((e_recharging_grenades_setting)packet->read_integer("player-traits-recharging-grenades", 2), true);
	set_weapon_pickup_setting((e_weapon_pickup_setting)packet->read_integer("player-traits-weapon-pickup-allowed", 2), true);
}

bool c_player_trait_weapons::equivalent(c_player_trait_weapons const *traits) const // 0x10F04980
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?equivalent@c_player_trait_weapons@@QBE_NPBU1@@Z");
	// c_player_trait_weapons const *traits;

	return initial_grenade_count == traits->initial_grenade_count && initial_primary_weapon == traits->initial_primary_weapon && initial_secondary_weapon == traits->initial_secondary_weapon && damage_modifier == traits->damage_modifier && recharging_grenades == traits->recharging_grenades && infinite_ammo == traits->infinite_ammo && weapon_pickup == traits->weapon_pickup;
}

void c_player_trait_movement::initialize() // 0x10F05100
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize@c_player_trait_movement@@QAEXXZ");
	// c_player_trait_movement *const this;

	player_speed = 5;
	player_gravity = 3;
	vehicle_usage = 3;
	unused = 0;
}

void c_player_trait_movement::set(c_player_trait_movement const *traits, bool can_inherit) // 0x10F05530
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set@c_player_trait_movement@@QAEXPBU1@_N@Z");
	// bool can_inherit;

	set_speed_setting((e_speed_setting)traits->player_speed, can_inherit);
	set_gravity_setting((e_gravity_setting)traits->player_gravity, can_inherit);
	set_vehicle_usage_setting((e_vehicle_usage_setting)traits->vehicle_usage, can_inherit);
	unused = 0;
}

float c_player_trait_movement::get_speed() const // 0x10F04EB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_speed@c_player_trait_movement@@QBEMXZ");
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

	switch (player_speed)
	{
	case _speed_25:
		return 0.25f;
	case _speed_50:
		return 0.5f;
	case _speed_75:
		return 0.75f;
	case _speed_90:
		return 0.9f;
	case _speed_100:
		return 1.0f;
	case _speed_110:
		return 1.1f;
	case _speed_125:
		return 1.25f;
	case _speed_150:
		return 1.5f;
	case _speed_200:
		return 2.0f;
	case _speed_300:
		return 3.0f;
	default:
		return 1.0f;
	}
}

float c_player_trait_movement::get_gravity() const // 0x10F04D90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_gravity@c_player_trait_movement@@QBEMXZ");
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

	switch (player_gravity)
	{
	case _gravity_50:
		return 0.5f;
	case _gravity_75:
		return 0.75f;
	case _gravity_150:
		return 1.5f;
	case _gravity_200:
		return 2.0f;
	case _gravity_0:
		return 0.0f;
	case _gravity_15:
		return 0.15f;
	case _gravity_25:
		return 0.25f;
	case _gravity_35:
		return 0.35f;
	case _gravity_125:
		return 1.25f;
	}

	return 1.0f;
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

void c_player_trait_movement::encode(c_bitstream *packet) const // 0x10F040F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?encode@c_player_trait_movement@@QBEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;

	packet->write_integer("player-traits-movement-speed", player_speed, 4);
	packet->write_integer("player-traits-movement-gravity", player_gravity, 4);
	packet->write_integer("player-traits-movement-vehicle-usage", vehicle_usage, 2);
}

void c_player_trait_movement::decode(c_bitstream *packet) // 0x10F03A70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?decode@c_player_trait_movement@@QAEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;

	set_speed_setting((e_speed_setting)packet->read_integer("player-traits-movement-speed", 4), true);
	set_gravity_setting((e_gravity_setting)packet->read_integer("player-traits-movement-gravity", 4), true);
	set_vehicle_usage_setting((e_vehicle_usage_setting)packet->read_integer("player-traits-movement-vehicle-usage", 2), true);
}

bool c_player_trait_movement::equivalent(c_player_trait_movement const *traits) const // 0x10F04730
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?equivalent@c_player_trait_movement@@QBE_NPBU1@@Z");
	// c_player_trait_movement const *traits;

	return player_speed == traits->player_speed
		&& player_gravity == traits->player_gravity
		&& vehicle_usage == traits->vehicle_usage;
}

void c_player_trait_appearance::initialize() // 0x10F04FE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize@c_player_trait_appearance@@QAEXXZ");
	// c_player_trait_appearance *const this;

	active_camo = 1;
	waypoint = 2;
	aura = 1;
	forced_color = 1;
}

void c_player_trait_appearance::set(c_player_trait_appearance const *traits, bool can_inherit) // 0x10F05390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set@c_player_trait_appearance@@QAEXPBU1@_N@Z");
	// bool can_inherit;

	set_active_camo_setting((e_active_camo_setting)traits->active_camo, can_inherit);
	set_waypoint_setting((e_waypoint_setting)traits->waypoint, can_inherit);
	set_player_size_setting((e_player_size_setting)traits->aura, can_inherit);
	set_forced_change_color_setting((e_forced_change_color_setting)traits->forced_color, can_inherit);
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

void c_player_trait_appearance::encode(c_bitstream *packet) const // 0x10F03F30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?encode@c_player_trait_appearance@@QBEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;

	packet->write_integer("player-traits-appearance-active-camo", active_camo, 3);
	packet->write_integer("player-traits-appearance-waypoint", waypoint, 3);
	packet->write_integer("player-traits-appearance-aura", aura, 5);
	packet->write_integer("player-traits-appearance-forced-change-color", forced_color, 4);
}

void c_player_trait_appearance::decode(c_bitstream *packet) // 0x10F038B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?decode@c_player_trait_appearance@@QAEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;

	set_active_camo_setting((e_active_camo_setting)packet->read_integer("player-traits-appearance-active-camo", 3), true);
	set_waypoint_setting((e_waypoint_setting)packet->read_integer("player-traits-appearance-waypoint", 3), true);
	set_player_size_setting((e_player_size_setting)packet->read_integer("player-traits-player-size", 5), true);
	set_forced_change_color_setting((e_forced_change_color_setting)packet->read_integer("player-traits-appearance-forced-change-color", 4), true);
}

bool c_player_trait_appearance::equivalent(c_player_trait_appearance const *traits) const // 0x10F04550
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?equivalent@c_player_trait_appearance@@QBE_NPBU1@@Z");
	// c_player_trait_appearance const *traits;

	return active_camo == traits->active_camo
		&& waypoint == traits->waypoint
		&& aura == traits->aura
		&& forced_color == traits->forced_color;
}

void c_player_trait_sensors::initialize() // 0x10F05170
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize@c_player_trait_sensors@@QAEXXZ");
	// c_player_trait_sensors *const this;

	motion_tracker_mode = 3;
	motion_tracker_range = 3;
}

void c_player_trait_sensors::set(c_player_trait_sensors const *traits, bool can_inherit) // 0x10F055E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set@c_player_trait_sensors@@QAEXPBU1@_N@Z");
	// bool can_inherit;

	set_motion_tracker_setting((e_motion_tracker_setting)traits->motion_tracker_mode, can_inherit);
	set_motion_tracker_range_setting((e_motion_tracker_range_setting)traits->motion_tracker_range, can_inherit);
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

void c_player_trait_sensors::encode(c_bitstream *packet) const // 0x10F041A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?encode@c_player_trait_sensors@@QBEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;

	packet->write_integer("player-traits-sensors-motion-tracker", motion_tracker_mode, 3);
	packet->write_integer("player-traits-sensors-motion-tracker-range", motion_tracker_range, 3);
}

void c_player_trait_sensors::decode(c_bitstream *packet) // 0x10F03B30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?decode@c_player_trait_sensors@@QAEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;

	set_motion_tracker_setting((e_motion_tracker_setting)packet->read_integer("player-traits-sensors-motion-tracker", 3), true);
	set_motion_tracker_range_setting((e_motion_tracker_range_setting)packet->read_integer("player-traits-sensors-motion-tracker-range", 3), true);
}

bool c_player_trait_sensors::equivalent(c_player_trait_sensors const *traits) const // 0x10F047F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?equivalent@c_player_trait_sensors@@QBE_NPBU1@@Z");
	// c_player_trait_sensors const *traits;

	return motion_tracker_mode == traits->motion_tracker_mode && motion_tracker_range == traits->motion_tracker_range;
}

void c_player_trait_extended::initialize() // 0x10F05050
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize@c_player_trait_extended@@QAEXXZ");
	// c_player_trait_extended *const this;

	player_model = 1;
	player_model_set = 1;
	sprint_allowed = 2;
	use_third_person_camera = 2;
}

void c_player_trait_extended::set(c_player_trait_extended const *traits, bool can_inherit) // 0x10F05450
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set@c_player_trait_extended@@QAEXPBU1@_N@Z");
	// bool can_inherit;

	set_player_model_absolute_index(traits->player_model, can_inherit);
	set_player_model_set_absolute_index(traits->player_model_set, can_inherit);
	set_sprint_setting((e_sprint_setting)traits->sprint_allowed, can_inherit);
	set_third_person_camera_setting((e_third_person_camera)traits->use_third_person_camera, can_inherit);
}

void c_player_trait_extended::set_player_model_absolute_index(unsigned char index, bool can_inherit) // 0x10F06060
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_player_model_absolute_index@c_player_trait_extended@@QAEXE_N@Z");
	// bool can_inherit;

	if (index >= 16)
	{
		return;
	}
	else if (index != 0 || can_inherit)
	{
		player_model = index;
	}
}

void c_player_trait_extended::set_player_model_set_absolute_index(unsigned char index, bool can_inherit) // 0x10F060F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_player_model_set_absolute_index@c_player_trait_extended@@QAEXE_N@Z");
	// bool can_inherit;

	if (index >= 8)
	{
		return;
	}
	else if (index != 0 || can_inherit)
	{
		player_model_set = index;
	}
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

void c_player_trait_extended::encode(c_bitstream *packet) const // 0x10F04000
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?encode@c_player_trait_extended@@QBEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;

	packet->write_integer("player-traits-extended-player-model", player_model, 4);
	packet->write_integer("player-traits-extended-player-model-set", player_model_set, 3);
	packet->write_integer("player-traits-extended-sprint", sprint_allowed, 2);
	packet->write_integer("player-traits-extended-third-person-camera", use_third_person_camera, 2);
}

void c_player_trait_extended::decode(c_bitstream *packet) // 0x10F03990
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?decode@c_player_trait_extended@@QAEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;

	set_player_model_absolute_index(packet->read_integer("player-traits-extended-player-model", 4), true);
	set_player_model_set_absolute_index(packet->read_integer("player-traits-extended-player-model-set", 3), true);
	set_sprint_setting((e_sprint_setting)packet->read_integer("player-traits-extended-sprint", 2), true);
	set_third_person_camera_setting((e_third_person_camera)packet->read_integer("player-traits-extended-third-person-camera", 2), true);
}

bool c_player_trait_extended::equivalent(c_player_trait_extended const *traits) const // 0x10F04620
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?equivalent@c_player_trait_extended@@QBE_NPBU1@@Z");
	// c_player_trait_extended const *traits;

	return player_model == traits->player_model && player_model_set == traits->player_model_set && sprint_allowed == traits->sprint_allowed && use_third_person_camera == traits->use_third_person_camera;
}

void c_player_traits::initialize() // 0x10F052F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize@c_player_traits@@QAEXXZ");
	// c_player_traits *const this;

	vitality.initialize();
	extended.initialize();
	weapons.initialize();
	movement.initialize();
	appearance.initialize();
	sensors.initialize();
}

void c_player_traits::set(c_player_traits const *traits, bool can_inherit) // 0x10F05860
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set@c_player_traits@@QAEXPBU1@_N@Z");
	// bool can_inherit;

	vitality.set(&traits->vitality, can_inherit);
	extended.set(&traits->extended, can_inherit);
	weapons.set(&traits->weapons, can_inherit);
	movement.set(&traits->movement, can_inherit);
	appearance.set(&traits->appearance, can_inherit);
	sensors.set(&traits->sensors, can_inherit);
}

void c_player_traits::encode(c_bitstream *packet) const // 0x10F04430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?encode@c_player_traits@@QBEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;

	vitality.encode(packet);
	extended.encode(packet);
	weapons.encode(packet);
	movement.encode(packet);
	appearance.encode(packet);
	sensors.encode(packet);
}

void c_player_traits::decode(c_bitstream *packet) // 0x10F03E10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?decode@c_player_traits@@QAEXPAVc_bitstream@@@Z");
	// c_bitstream *packet;

	vitality.decode(packet);
	extended.decode(packet);
	weapons.decode(packet);
	movement.decode(packet);
	appearance.decode(packet);
	sensors.decode(packet);
}

bool c_player_traits::equivalent(c_player_traits const *traits) const // 0x10F04A90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?equivalent@c_player_traits@@QBE_NPBU1@@Z");
	// c_player_traits const *traits;

	return vitality.equivalent(&traits->vitality)
		&& extended.equivalent(&traits->extended)
		&& weapons.equivalent(&traits->weapons)
		&& movement.equivalent(&traits->movement)
		&& appearance.equivalent(&traits->appearance)
		&& sensors.equivalent(&traits->sensors);
}

/* ---------- private code */
