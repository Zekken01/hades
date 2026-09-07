#ifndef __BLAM_GAME_ENGINE_GAME_ENGINE_PLAYER_TRAITS_HPP__
#define __BLAM_GAME_ENGINE_GAME_ENGINE_PLAYER_TRAITS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

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

enum
{
	k_player_traits_maximum_player_model_count = 16, // 0x0010
	k_player_traits_maximum_player_model_set_count = 8, // 0x0008
};

enum e_player_traits_tri_state_option
{
	_player_traits_tri_state_option_unchanged = 0,
	_player_traits_tri_state_option_enabled,
	_player_traits_tri_state_option_disabled,
	k_player_traits_tri_state_option_count,
};

/* ---------- definitions */

struct c_player_trait_shield_vitality
{
	public:
	enum e_damage_resistance_setting
	{
		_damage_resistance_unchanged = 0,
		_damage_resistance_10,
		_damage_resistance_50,
		_damage_resistance_90,
		_damage_resistance_normal,
		_damage_resistance_110,
		_damage_resistance_150,
		_damage_resistance_200,
		_damage_resistance_300,
		_damage_resistance_500,
		_damage_resistance_1000,
		_damage_resistance_2000,
		_damage_resistance_invulnerable,
		_damage_resistance_1500,
		_damage_resistance_3000,
		_damage_resistance_invincible,
		k_damage_resistance_setting_count,
	};
	enum e_shield_recharge_rate_setting
	{
		_shield_recharge_rate_unchanged = 0,
		_shield_recharge_decay_25,
		_shield_recharge_decay_10,
		_shield_recharge_decay_5,
		_shield_recharge_0,
		_shield_recharge_50,
		_shield_recharge_90,
		_shield_recharge_100,
		_shield_recharge_110,
		_shield_recharge_200,
		k_shield_recharge_rate_setting_count,
	};
	enum e_shield_multiplier_setting
	{
		_shield_multiplier_unchanged = 0,
		_shield_multiplier_0x,
		_shield_multiplier_1x,
		_shield_multiplier_2x,
		_shield_multiplier_3x,
		_shield_multiplier_4x,
		k_shield_multiplier_setting_count,
	};
	enum e_headshot_immunity_setting
	{
		_headshot_immunity_unchanged = 0,
		_headshot_immunity_enabled,
		_headshot_immunity_disabled,
		k_headshot_immunity_setting_count,
	};
	enum e_shield_vampirism_setting
	{
		_shield_vampirism_unchanged = 0,
		_shield_vampirism_disabled,
		_shield_vampirism_vampirism_10,
		_shield_vampirism_vampirism_25,
		_shield_vampirism_vampirism_50,
		_shield_vampirism_vampirism_100,
		k_shield_vampirism_setting_count,
	};
	public:
	void initialize();
	void set(c_player_trait_shield_vitality const *traits, bool can_inherit);
	float get_damage_resistance_percentage() const;
	void set_damage_resistance_setting(e_damage_resistance_setting value, bool can_inherit);
	void set_shield_recharge_rate_setting(e_shield_recharge_rate_setting value, bool can_inherit);
	void set_shield_vampirism_setting(e_shield_vampirism_setting value, bool can_inherit);
	void set_headshot_immunity_setting(e_headshot_immunity_setting value, bool can_inherit);
	void set_shield_multiplier_setting(e_shield_multiplier_setting value, bool can_inherit);
	void encode(c_bitstream *packet) const;
	void decode(c_bitstream *packet);
	bool equivalent(c_player_trait_shield_vitality const *traits) const;
	unsigned char damage_resistance; // 0x0
	unsigned char shield_recharge_rate; // 0x1
	unsigned char shield_vampirism; // 0x2
	unsigned char headshot_immunity; // 0x3
	unsigned char shield_multiplier; // 0x4
};
static_assert(sizeof(c_player_trait_shield_vitality) == 5, "Invalid c_player_trait_shield_vitality size");

struct c_player_trait_weapons
{
	public:
	enum e_grenade_count_setting
	{
		_grenade_count_unchanged = 0,
		_grenade_count_map_default,
		_grenade_count_more,
		k_grenade_count_setting_count,
	};
	enum e_damage_modifier_setting
	{
		_damage_modifier_unchanged = 0,
		_damage_modifier_0,
		_damage_modifier_25,
		_damage_modifier_50,
		_damage_modifier_75,
		_damage_modifier_90,
		_damage_modifier_100,
		_damage_modifier_110,
		_damage_modifier_125,
		_damage_modifier_150,
		_damage_modifier_200,
		_damage_modifier_300,
		_damage_modifier_fatal,
		k_damage_modifier_setting_count,
	};
	enum e_recharging_grenades_setting
	{
		_recharging_grenades_unchanged = 0,
		_recharging_grenades_enabled,
		_recharging_grenades_disabled,
		k_recharging_grenades_setting_count,
	};
	enum e_infinite_ammo_setting
	{
		_infinite_ammo_unchanged = 0,
		_infinite_ammo_disabled,
		_infinite_ammo_enabled,
		_infinite_ammo_bottomless_clip,
		k_infinite_ammo_setting_setting_count,
	};
	enum e_weapon_pickup_setting
	{
		_weapon_pickup_unchanged = 0,
		_weapon_pickup_enabled,
		_weapon_pickup_disabled,
		k_weapon_pickup_setting_count,
	};
	public:
	void initialize();
	void set(c_player_trait_weapons const *traits, bool can_inherit);
	void set_initial_grenade_count_setting(e_grenade_count_setting value, bool can_inherit);
	void set_initial_primary_weapon_absolute_index(char index, bool can_inherit);
	void set_initial_secondary_weapon_absolute_index(char index, bool can_inherit);
	void set_damage_modifier_setting(e_damage_modifier_setting value, bool can_inherit);
	void set_recharging_grenades_setting(e_recharging_grenades_setting value, bool can_inherit);
	void set_infinite_ammo_setting(e_infinite_ammo_setting value, bool can_inherit);
	void set_weapon_pickup_setting(e_weapon_pickup_setting value, bool can_inherit);
	void encode(c_bitstream *packet) const;
	void decode(c_bitstream *packet);
	bool equivalent(c_player_trait_weapons const *traits) const;
	unsigned short initial_grenade_count; // 0x0
	char initial_primary_weapon; // 0x2
	char initial_secondary_weapon; // 0x3
	unsigned char damage_modifier; // 0x4
	unsigned char recharging_grenades; // 0x5
	unsigned char infinite_ammo; // 0x6
	unsigned char weapon_pickup; // 0x7
};
static_assert(sizeof(c_player_trait_weapons) == 8, "Invalid c_player_trait_weapons size");

struct c_player_trait_movement
{
	public:
	enum e_speed_setting
	{
		_speed_unchanged = 0,
		_speed_25,
		_speed_50,
		_speed_75,
		_speed_90,
		_speed_100,
		_speed_110,
		_speed_125,
		_speed_150,
		_speed_200,
		_speed_300,
		k_player_speed_setting_count,
	};
	enum e_gravity_setting
	{
		_gravity_unchanged = 0,
		_gravity_50,
		_gravity_75,
		_gravity_100,
		_gravity_150,
		_gravity_200,
		_gravity_0,
		_gravity_15,
		_gravity_25,
		_gravity_35,
		_gravity_125,
		k_player_gravity_setting_count,
	};
	enum e_vehicle_usage_setting
	{
		_vehicle_usage_unchanged = 0,
		_vehicle_usage_none,
		_vehicle_usage_passenger,
		_vehicle_usage_full,
		k_vehicle_usage_setting_count,
	};
	public:
	void initialize();
	void set(c_player_trait_movement const *traits, bool can_inherit);
	float get_speed() const;
	float get_gravity() const;
	void set_speed_setting(e_speed_setting value, bool can_inherit);
	void set_gravity_setting(e_gravity_setting value, bool can_inherit);
	void set_vehicle_usage_setting(e_vehicle_usage_setting value, bool can_inherit);
	void encode(c_bitstream *packet) const;
	void decode(c_bitstream *packet);
	bool equivalent(c_player_trait_movement const *traits) const;
	unsigned char player_speed; // 0x0
	unsigned char player_gravity; // 0x1
	unsigned char vehicle_usage; // 0x2
	unsigned char unused; // 0x3
};
static_assert(sizeof(c_player_trait_movement) == 4, "Invalid c_player_trait_movement size");

struct c_player_trait_appearance
{
	public:
	enum e_active_camo_setting
	{
		_active_camo_unchanged = 0,
		_active_camo_off,
		_active_camo_bad,
		_active_camo_poor,
		_active_camo_good,
		k_active_camo_setting_count,
	};
	enum e_waypoint_setting
	{
		_waypoint_unchanged = 0,
		_waypoint_none,
		_waypoint_allies,
		_waypoint_all,
		_waypoint_nametag_none,
		_waypoint_nametag_allies,
		k_waypoint_setting_count,
	};
	enum e_player_size_setting
	{
		_player_size_unchanged = 0, // 0x0000
		_player_size_10 = 2, // 0x0002
		_player_size_15 = 3, // 0x0003
		_player_size_25 = 4, // 0x0004
		_player_size_35 = 5, // 0x0005
		_player_size_50 = 6, // 0x0006
		_player_size_75 = 7, // 0x0007
		_player_size_100 = 8, // 0x0008
		_player_size_125 = 9, // 0x0009
		_player_size_150 = 10, // 0x000A
		_player_size_200 = 11, // 0x000B
		_player_size_300 = 12, // 0x000C
		_player_size_500 = 13, // 0x000D
		_player_size_750 = 14, // 0x000E
		_player_size_1000 = 15, // 0x000F
		_player_size_1500 = 16, // 0x0010
		_player_size_2000 = 17, // 0x0011
		_player_size_3000 = 18, // 0x0012
		k_player_size_setting_count = 19, // 0x0013
	};
	enum e_forced_change_color_setting
	{
		_forced_change_color_unchanged = 0,
		_forced_change_color_off,
		_forced_change_color0,
		_forced_change_color1,
		_forced_change_color2,
		_forced_change_color3,
		_forced_change_color4,
		_forced_change_color5,
		_forced_change_color6,
		_forced_change_color7,
		_forced_change_color8,
		_forced_change_color9,
		_forced_change_color10,
		k_forced_change_color_setting_count,
	};
	public:
	void initialize();
	void set(c_player_trait_appearance const *traits, bool can_inherit);
	void set_active_camo_setting(e_active_camo_setting value, bool can_inherit);
	void set_waypoint_setting(e_waypoint_setting value, bool can_inherit);
	void set_player_size_setting(e_player_size_setting value, bool can_inherit);
	void set_forced_change_color_setting(e_forced_change_color_setting value, bool can_inherit);
	void encode(c_bitstream *packet) const;
	void decode(c_bitstream *packet);
	bool equivalent(c_player_trait_appearance const *traits) const;
	unsigned char active_camo; // 0x0
	unsigned char waypoint; // 0x1
	unsigned char aura; // 0x2
	unsigned char forced_color; // 0x3
};
static_assert(sizeof(c_player_trait_appearance) == 4, "Invalid c_player_trait_appearance size");

struct c_player_trait_sensors
{
	public:
	enum e_motion_tracker_setting
	{
		_motion_tracker_unchanged = 0,
		_motion_tracker_off,
		_motion_tracker_friends,
		_motion_tracker_normal,
		_motion_tracker_all,
		k_motion_tracker_setting_count,
	};
	enum e_motion_tracker_range_setting
	{
		_motion_tracker_range_unchanged = 0, // 0x0000
		_motion_tracker_range_10m = 1, // 0x0001
		_motion_tracker_range_25m = 3, // 0x0003
		_motion_tracker_range_75m = 5, // 0x0005
		_motion_tracker_range_150m = 7, // 0x0007
		k_motion_tracker_range_setting_count = 8, // 0x0008
	};
	public:
	void initialize();
	void set(c_player_trait_sensors const *traits, bool can_inherit);
	void set_motion_tracker_setting(e_motion_tracker_setting value, bool can_inherit);
	void set_motion_tracker_range_setting(e_motion_tracker_range_setting value, bool can_inherit);
	void encode(c_bitstream *packet) const;
	void decode(c_bitstream *packet);
	bool equivalent(c_player_trait_sensors const *traits) const;
	unsigned short motion_tracker_mode; // 0x0
	unsigned short motion_tracker_range; // 0x2
};
static_assert(sizeof(c_player_trait_sensors) == 4, "Invalid c_player_trait_sensors size");

struct c_player_trait_extended
{
	public:
	enum e_sprint_setting
	{
		_sprint_unchanged = 0,
		_sprint_enabled,
		_sprint_disabled,
		k_sprint_setting_count,
	};
	enum e_third_person_camera
	{
		_third_person_camera_unchanged = 0,
		_third_person_camera_enabled,
		_third_person_camera_disabled,
		k_third_person_camera_setting_count,
	};
	public:
	void initialize();
	void set(c_player_trait_extended const *traits, bool can_inherit);
	void set_player_model_absolute_index(unsigned char index, bool can_inherit);
	void set_player_model_set_absolute_index(unsigned char index, bool can_inherit);
	void set_sprint_setting(e_sprint_setting value, bool can_inherit);
	void set_third_person_camera_setting(e_third_person_camera value, bool can_inherit);
	void encode(c_bitstream *packet) const;
	void decode(c_bitstream *packet);
	bool equivalent(c_player_trait_extended const *traits) const;
	unsigned char player_model : 4; // 0x0
	unsigned char player_model_set : 3; // 0x0
	unsigned char sprint_allowed : 2; // 0x1
	unsigned char use_third_person_camera : 2; // 0x1
	unsigned char unused1 : 4; // 0x1
	unsigned char unused2 : 8; // 0x2
};
static_assert(sizeof(c_player_trait_extended) == 3, "Invalid c_player_trait_extended size");

#pragma pack(push, 4)
struct c_player_traits
{
	c_player_trait_shield_vitality vitality; // 0x0
	c_player_trait_extended extended; // 0x5
	c_player_trait_weapons weapons; // 0x8
	c_player_trait_movement movement; // 0x10
	c_player_trait_appearance appearance; // 0x14
	c_player_trait_sensors sensors; // 0x18
	void initialize();
	void set(c_player_traits const *traits, bool can_inherit);
	void encode(c_bitstream *packet) const;
	void decode(c_bitstream *packet);
	bool equivalent(c_player_traits const *traits) const;
};
#pragma pack(pop)
static_assert(sizeof(c_player_traits) == 28, "Invalid c_player_traits size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_GAME_ENGINE_GAME_ENGINE_PLAYER_TRAITS_HPP__
