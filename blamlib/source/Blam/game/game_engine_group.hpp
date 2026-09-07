#ifndef __BLAM_GAME_GAME_ENGINE_GROUP_HPP__
#define __BLAM_GAME_GAME_ENGINE_GROUP_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/items/equipment_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct s_game_engine_assault_variant_definition;
struct s_game_engine_base_variant_definition;
struct s_game_engine_ctf_variant_definition;
struct s_game_engine_infection_variant_definition;
struct s_game_engine_juggernaut_variant_definition;
struct s_game_engine_king_variant_definition;
struct s_game_engine_map_override_options_definition;
struct s_game_engine_miscellaneous_options_definition;
struct s_game_engine_oddball_variant_definition;
struct s_game_engine_player_traits;
struct s_game_engine_respawn_options_definition;
struct s_game_engine_sandbox_variant_definition;
struct s_game_engine_settings_definition;
struct s_game_engine_slayer_variant_definition;
struct s_game_engine_social_options_definition;
struct s_game_engine_territories_variant_definition;
struct s_game_engine_vip_variant_definition;
struct s_player_trait_appearance;
struct s_player_trait_movement;
struct s_player_trait_sensors;
struct s_player_trait_shield_vitality;
struct s_player_trait_weapons;

/* ---------- constants */

/* ---------- definitions */

struct s_player_trait_shield_vitality
{
	char damage_resistance; // 0x0
	char shield_multiplier; // 0x1
	char shield_recharge_rate; // 0x2
	char headshot_immunity; // 0x3
	char vampirism; // 0x4
	unsigned char elephant[3]; // 0x5
};
static_assert(sizeof(s_player_trait_shield_vitality) == 8, "Invalid s_player_trait_shield_vitality size");

struct s_player_trait_weapons
{
	char damage_modifier; // 0x0
	char recharging_grenades; // 0x1
	char weapon_pickup; // 0x2
	char infinite_ammo; // 0x3
	unsigned long initial_primary_weapon; // 0x4
	unsigned long initial_secondary_weapon; // 0x8
	short initial_grenade_count; // 0xC
	unsigned char blah[2]; // 0xE
};
static_assert(sizeof(s_player_trait_weapons) == 16, "Invalid s_player_trait_weapons size");

struct s_player_trait_movement
{
	char speed_multiplier; // 0x0
	char gravity_multiplier; // 0x1
	char vehicle_usage; // 0x2
	unsigned char shark[1]; // 0x3
};
static_assert(sizeof(s_player_trait_movement) == 4, "Invalid s_player_trait_movement size");

struct s_player_trait_appearance
{
	char active_camo_setting; // 0x0
	char waypoint_setting; // 0x1
	char player_size; // 0x2
	char forced_change_color_setting; // 0x3
};
static_assert(sizeof(s_player_trait_appearance) == 4, "Invalid s_player_trait_appearance size");

struct s_player_trait_sensors
{
	long motion_tracker_settings; // 0x0
	long motion_tracker_range; // 0x4
};
static_assert(sizeof(s_player_trait_sensors) == 8, "Invalid s_player_trait_sensors size");

struct s_game_engine_player_traits
{
	unsigned long name; // 0x0
	c_tag_block<s_player_trait_shield_vitality> shield_traits; // 0x4
	c_tag_block<s_player_trait_weapons> weapon_traits; // 0x10
	c_tag_block<s_player_trait_movement> movement_traits; // 0x1C
	c_tag_block<s_player_trait_appearance> appearance_traits; // 0x28
	c_tag_block<s_player_trait_sensors> sensor_traits; // 0x34
};
static_assert(sizeof(s_game_engine_player_traits) == 64, "Invalid s_game_engine_player_traits size");

struct s_game_engine_miscellaneous_options_definition
{
	unsigned long flags; // 0x0
	char round_time_limit; // 0x4
	char number_of_rounds; // 0x5
	char early_victory_win_count; // 0x6
	char round_reset; // 0x7
};
static_assert(sizeof(s_game_engine_miscellaneous_options_definition) == 8, "Invalid s_game_engine_miscellaneous_options_definition size");

struct s_game_engine_respawn_options_definition
{
	unsigned short flags; // 0x0
	char lives_per_round; // 0x2
	char team_lives_per_round; // 0x3
	char respawn_time; // 0x4
	char suicide_penalty; // 0x5
	char betrayal_penalty; // 0x6
	char respawn_growth; // 0x7
	unsigned long respawn_player_traits_name; // 0x8
	char respawn_player_traits_duration; // 0xC
	unsigned char pad[3]; // 0xD
};
static_assert(sizeof(s_game_engine_respawn_options_definition) == 16, "Invalid s_game_engine_respawn_options_definition size");

struct s_game_engine_social_options_definition
{
	unsigned long flags; // 0x0
};
static_assert(sizeof(s_game_engine_social_options_definition) == 4, "Invalid s_game_engine_social_options_definition size");

struct s_game_engine_map_override_options_definition
{
	unsigned long flags; // 0x0
	unsigned long player_traits_name; // 0x4
	unsigned long weapon_set_name; // 0x8
	unsigned long vehicle_set_name; // 0xC
	unsigned long red_powerup_traits_name; // 0x10
	unsigned long blue_powerup_traits_name; // 0x14
	unsigned long yellow_powerup_traits_name; // 0x18
	char red_powerup_duration; // 0x1C
	char blue_powerup_duration; // 0x1D
	char yellow_powerup_duration; // 0x1E
	unsigned char gonna_pack_her_bags_and_leave_this_house_of_pain[1]; // 0x1F
};
static_assert(sizeof(s_game_engine_map_override_options_definition) == 32, "Invalid s_game_engine_map_override_options_definition size");

struct s_game_engine_base_variant_definition
{
	char name_ascii[32]; // 0x0
	unsigned long localizable_name; // 0x20
	unsigned long localizable_description; // 0x24
	c_tag_block<s_game_engine_miscellaneous_options_definition> miscellaneous_options; // 0x28
	c_tag_block<s_game_engine_respawn_options_definition> respawn_options; // 0x34
	c_tag_block<s_game_engine_social_options_definition> social_options; // 0x40
	c_tag_block<s_game_engine_map_override_options_definition> map_override_options; // 0x4C
};
static_assert(sizeof(s_game_engine_base_variant_definition) == 88, "Invalid s_game_engine_base_variant_definition size");

struct s_game_engine_slayer_variant_definition :
	public s_game_engine_base_variant_definition
{
	short team_scoring; // 0x58
	short score_to_win; // 0x5A
	char kill_points; // 0x5C
	char assist_points; // 0x5D
	char death_points; // 0x5E
	char suicide_points; // 0x5F
	char betrayal_points; // 0x60
	char leader_kill_points; // 0x61
	char elimination_points; // 0x62
	char assassination_bonus_points; // 0x63
	char headshot_bonus_points; // 0x64
	char melee_bonus_points; // 0x65
	char sticky_bonus_points; // 0x66
	char splatter_bonus_points; // 0x67
	char killing_spree_bonus_points; // 0x68
	unsigned char slayer_padding[3]; // 0x69
	unsigned long leader_player_traits_name; // 0x6C
};
static_assert(sizeof(s_game_engine_slayer_variant_definition) == 112, "Invalid s_game_engine_slayer_variant_definition size");

struct s_game_engine_oddball_variant_definition :
	public s_game_engine_base_variant_definition
{
	unsigned long flags; // 0x58
	short team_scoring; // 0x5C
	short score_to_win; // 0x5E
	char carrying_points; // 0x60
	char kill_points; // 0x61
	char ball_kill_points; // 0x62
	char carrier_kill_points; // 0x63
	char ball_count; // 0x64
	unsigned char pad[3]; // 0x65
	short ball_spawn_delay; // 0x68
	short ball_inactive_respawn; // 0x6A
	unsigned long carrier_traits_name; // 0x6C
};
static_assert(sizeof(s_game_engine_oddball_variant_definition) == 112, "Invalid s_game_engine_oddball_variant_definition size");

struct s_game_engine_ctf_variant_definition :
	public s_game_engine_base_variant_definition
{
	unsigned long flags; // 0x58
	short home_flag_waypoint; // 0x5C
	short game_type; // 0x5E
	short capture_respawn; // 0x60
	short touch_return_time; // 0x62
	short sudden_death_time; // 0x64
	short score_to_win; // 0x66
	short flag_reset_time; // 0x68
	unsigned char pad[2]; // 0x6A
	unsigned long carrier_traits_name; // 0x6C
};
static_assert(sizeof(s_game_engine_ctf_variant_definition) == 112, "Invalid s_game_engine_ctf_variant_definition size");

struct s_game_engine_assault_variant_definition :
	public s_game_engine_base_variant_definition
{
	unsigned long flags; // 0x58
	short respawn_type; // 0x5C
	short game_type; // 0x5E
	short enemy_bomb_waypoint; // 0x60
	short sudden_death_time; // 0x62
	short score_to_win; // 0x64
	short unknown1; // 0x66
	short unknown2; // 0x68
	short unknown3; // 0x6A
	short unknown4; // 0x6C
	short bomb_reset_time; // 0x6E
	short bomb_arming_time; // 0x70
	short bomb_disarming_time; // 0x72
	short bomb_fuse_time; // 0x74
	unsigned char pad[2]; // 0x76
	unsigned long carrier_traits_name; // 0x78
	unsigned long arming_traits_name; // 0x7C
};
static_assert(sizeof(s_game_engine_assault_variant_definition) == 128, "Invalid s_game_engine_assault_variant_definition size");

#pragma pack(push, 4)
struct s_game_engine_infection_variant_definition :
	public s_game_engine_base_variant_definition
{
	unsigned long flags; // 0x58
	short safe_haven_settings; // 0x5C
	short next_zombie_settings; // 0x5E
	short initial_zombie_count; // 0x60
	short safe_haven_movement_time; // 0x62
	char zombie_kill_points; // 0x64
	char infection_points; // 0x65
	char safe_haven_arrival_points; // 0x66
	char suicide_points; // 0x67
	char betrayal_points; // 0x68
	char last_man_bonus_points; // 0x69
	unsigned char pad[2]; // 0x6A
	unsigned long zombie_traits_name; // 0x6C
	unsigned long first_zombie_traits_name; // 0x70
	unsigned long safe_haven_defender_traits_name; // 0x74
	unsigned long last_human_traits_name; // 0x78
};
#pragma pack(pop)
static_assert(sizeof(s_game_engine_infection_variant_definition) == 124, "Invalid s_game_engine_infection_variant_definition size");

struct s_game_engine_king_variant_definition :
	public s_game_engine_base_variant_definition
{
	unsigned long flags; // 0x58
	short score_to_win; // 0x5C
	unsigned short unknown; // 0x5E
	short team_scoring; // 0x60
	short moving_hill; // 0x62
	short moving_hill_order; // 0x64
	char inside_hill_points; // 0x66
	char outside_hill_points; // 0x67
	char uncontested_hill_bonus_points; // 0x68
	char points_per_kill; // 0x69
	unsigned char __pad0[2]; // 0x6A
	unsigned long inside_hill_traits_name; // 0x6C
};
static_assert(sizeof(s_game_engine_king_variant_definition) == 112, "Invalid s_game_engine_king_variant_definition size");

#pragma pack(push, 4)
struct s_game_engine_territories_variant_definition :
	public s_game_engine_base_variant_definition
{
	unsigned long flags; // 0x58
	short respawn_on_capture; // 0x5C
	short capture_time; // 0x5E
	short sudden_death_time; // 0x60
	unsigned char pad[2]; // 0x62
	unsigned long defender_traits; // 0x64
	unsigned long attacker_traits; // 0x68
};
#pragma pack(pop)
static_assert(sizeof(s_game_engine_territories_variant_definition) == 108, "Invalid s_game_engine_territories_variant_definition size");

#pragma pack(push, 4)
struct s_game_engine_juggernaut_variant_definition :
	public s_game_engine_base_variant_definition
{
	unsigned long flags; // 0x58
	short initial_juggernaut; // 0x5C
	short next_juggernaut; // 0x5E
	short zone_movement; // 0x60
	short zone_order; // 0x62
	short score_to_win_round; // 0x64
	char kill_points; // 0x66
	char juggeraut_kill_points; // 0x67
	char kill_as_juggernaut_points; // 0x68
	char destination_arrival_points; // 0x69
	char suicide_points; // 0x6A
	char betrayal_points; // 0x6B
	char juggernat_delay; // 0x6C
	unsigned char pad[3]; // 0x6D
	unsigned long juggernaut_traits; // 0x70
};
#pragma pack(pop)
static_assert(sizeof(s_game_engine_juggernaut_variant_definition) == 116, "Invalid s_game_engine_juggernaut_variant_definition size");

#pragma pack(push, 4)
struct s_game_engine_vip_variant_definition :
	public s_game_engine_base_variant_definition
{
	unsigned long flags; // 0x58
	short score_to_win_round; // 0x5C
	short vip_selection; // 0x5E
	short zone_movement; // 0x60
	short zone_order; // 0x62
	char kill_points; // 0x64
	char takedown_points; // 0x65
	char kill_as_vip_points; // 0x66
	char vip_death_points; // 0x67
	char destination_arrival_points; // 0x68
	char suicide_points; // 0x69
	char vip_friendly_death_points; // 0x6A
	char betrayal_points; // 0x6B
	char influence_radius; // 0x6C
	unsigned char pad[3]; // 0x6D
	unsigned long vip_team_traits; // 0x70
	unsigned long vip_influence_traits; // 0x74
	unsigned long vip_traits; // 0x78
};
#pragma pack(pop)
static_assert(sizeof(s_game_engine_vip_variant_definition) == 124, "Invalid s_game_engine_vip_variant_definition size");

#pragma pack(push, 4)
struct s_game_engine_sandbox_variant_definition :
	public s_game_engine_base_variant_definition
{
	unsigned long flags; // 0x58
	short edit_mode; // 0x5C
	short respawn_time; // 0x5E
	unsigned long all_players_traits; // 0x60
};
#pragma pack(pop)
static_assert(sizeof(s_game_engine_sandbox_variant_definition) == 100, "Invalid s_game_engine_sandbox_variant_definition size");

#pragma pack(push, 4)
struct s_game_engine_settings_definition
{
	unsigned long flags; // 0x0
	c_tag_block<s_game_engine_player_traits> player_traits; // 0x4
	c_tag_block<s_game_engine_slayer_variant_definition> slayer_variants; // 0x10
	c_tag_block<s_game_engine_oddball_variant_definition> oddball_variants; // 0x1C
	c_tag_block<s_game_engine_ctf_variant_definition> ctf_variants; // 0x28
	c_tag_block<s_game_engine_assault_variant_definition> assault_variants; // 0x34
	c_tag_block<s_game_engine_infection_variant_definition> infection_variants; // 0x40
	c_tag_block<s_game_engine_king_variant_definition> koth_variants; // 0x4C
	c_tag_block<s_game_engine_territories_variant_definition> territories_variants; // 0x58
	c_tag_block<s_game_engine_juggernaut_variant_definition> juggernaut_variants; // 0x64
	c_tag_block<s_game_engine_vip_variant_definition> vip_variants; // 0x70
	c_tag_block<s_game_engine_sandbox_variant_definition> sandbox_variants; // 0x7C
	unsigned long unknown; // 0x88
};
#pragma pack(pop)
static_assert(sizeof(s_game_engine_settings_definition) == 140, "Invalid s_game_engine_settings_definition size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_GAME_GAME_ENGINE_GROUP_HPP__
