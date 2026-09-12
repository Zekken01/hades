#ifndef __BLAM_GAME_GAME_VARIANT_HPP__
#define __BLAM_GAME_GAME_VARIANT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/game/engine/game_engine.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/engine/game_engine_player_traits.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/saved_games/content.hpp"

/* ---------- forward declarations */

struct c_game_engine_assault_variant;
struct c_game_engine_base_variant;
struct c_game_engine_ctf_variant;
struct c_game_engine_infection_variant;
struct c_game_engine_juggernaut_variant;
struct c_game_engine_king_variant;
struct c_game_engine_map_override_options;
struct c_game_engine_miscellaneous_options;
struct c_game_engine_oddball_variant;
struct c_game_engine_respawn_options;
struct c_game_engine_sandbox_variant;
struct c_game_engine_slayer_variant;
struct c_game_engine_team_options;
struct c_game_engine_territories_variant;
struct c_game_engine_vip_variant;
struct c_game_variant;
struct c_player_traits;
struct s_content_item_metadata;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct c_game_variant
{
	c_enum<enum e_game_engine_type,long> game_engine_type; // 0x0
	unsigned char storage[608]; // 0x4
	_inline c_game_engine_base_variant *get_base_variant();
	c_game_variant(c_game_variant &); /* compiler_generated() */
	c_game_variant(c_game_variant const &); /* compiler_generated() */
	_inline c_game_variant(); /* compiler_generated() */
	c_game_variant &operator=(c_game_variant &); /* compiler_generated() */
	c_game_variant &operator=(c_game_variant const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(c_game_variant) == 612, "Invalid c_game_variant size");

struct c_game_engine_base_variant
{
	void **vftable; // 0x0
	unsigned char __pad0[4]; // 0x4
	char backend_name[32]; // 0x8
	s_content_item_metadata metadata; // 0x28
	c_game_engine_miscellaneous_options miscellaneous_options; // 0x120
	c_game_engine_respawn_options respawn_options; // 0x124
	c_game_engine_social_options social_options; // 0x14C
	c_game_engine_map_override_options map_override_options; // 0x150
	c_game_engine_team_options team_options; // 0x1CC
	c_game_engine_base_variant(c_game_engine_base_variant &); /* compiler_generated() */
	c_game_engine_base_variant(c_game_engine_base_variant const &); /* compiler_generated() */
	c_game_engine_base_variant(); /* compiler_generated() */
	c_game_engine_base_variant &operator=(c_game_engine_base_variant &); /* compiler_generated() */
	c_game_engine_base_variant &operator=(c_game_engine_base_variant const &); /* compiler_generated() */
	unsigned char __pad1[2]; // 0x1CE
};
static_assert(sizeof(c_game_engine_base_variant) == 464, "Invalid c_game_engine_base_variant size");

struct c_game_engine_ctf_variant :
	public c_game_engine_base_variant
{
	unsigned char flags; // 0x1D0
	unsigned char home_flag_waypoint; // 0x1D1
	unsigned char game_mode; // 0x1D2
	unsigned char respawn_on_capture; // 0x1D3
	short flag_return_time; // 0x1D4
	short sudden_death_time; // 0x1D6
	short score_to_win; // 0x1D8
	unsigned char __pad0[2]; // 0x1DA
	short flag_reset_time; // 0x1DC
	c_player_traits flag_carrier_traits; // 0x1DE
	c_game_engine_ctf_variant(c_game_engine_ctf_variant &); /* compiler_generated() */
	c_game_engine_ctf_variant(c_game_engine_ctf_variant const &); /* compiler_generated() */
	c_game_engine_ctf_variant(); /* compiler_generated() */
	c_game_engine_ctf_variant &operator=(c_game_engine_ctf_variant &); /* compiler_generated() */
	c_game_engine_ctf_variant &operator=(c_game_engine_ctf_variant const &); /* compiler_generated() */
	unsigned char __pad1[6]; // 0x1FA
};
static_assert(sizeof(c_game_engine_ctf_variant) == 512, "Invalid c_game_engine_ctf_variant size");

struct c_game_engine_slayer_variant :
	public c_game_engine_base_variant
{
	short points_to_win; // 0x1D0
	short rules_symmetric; // 0x1D2
	short kill_points; // 0x1D4
	char assist_points; // 0x1D6
	char death_points; // 0x1D7
	char suicide_points; // 0x1D8
	char betrayal_points; // 0x1D9
	char leader_kill_bonus_points; // 0x1DA
	char elimination_bonus_points; // 0x1DB
	char assasination_bonus_points; // 0x1DC
	char headshot_bonus_points; // 0x1DD
	char beatdown_bonus_points; // 0x1DE
	char sticky_bonus_points; // 0x1DF
	char splatter_bonus_points; // 0x1E0
	char spree_bonus_points; // 0x1E1
	c_player_traits leader_traits; // 0x1E2
	c_game_engine_slayer_variant(c_game_engine_slayer_variant &); /* compiler_generated() */
	c_game_engine_slayer_variant(c_game_engine_slayer_variant const &); /* compiler_generated() */
	c_game_engine_slayer_variant(); /* compiler_generated() */
	c_game_engine_slayer_variant &operator=(c_game_engine_slayer_variant &); /* compiler_generated() */
	c_game_engine_slayer_variant &operator=(c_game_engine_slayer_variant const &); /* compiler_generated() */
};
static_assert(sizeof(c_game_engine_slayer_variant) == 512, "Invalid c_game_engine_slayer_variant size");

struct c_game_engine_king_variant :
	public c_game_engine_base_variant
{
	unsigned long flags; // 0x1D0
	unsigned short score_to_win; // 0x1D4
	unsigned short field_1D6; // 0x1D6
	unsigned char hill_movement; // 0x1D8
	unsigned char hill_movement_order; // 0x1D9
	unsigned char hill_points; // 0x1DA
	unsigned char uncontested_control_points; // 0x1DB
	unsigned char off_hill_points; // 0x1DC
	unsigned char kill_points; // 0x1DD
	c_player_traits hill_traits; // 0x1DE
	c_game_engine_king_variant(c_game_engine_king_variant &); /* compiler_generated() */
	c_game_engine_king_variant(c_game_engine_king_variant const &); /* compiler_generated() */
	c_game_engine_king_variant(); /* compiler_generated() */
	c_game_engine_king_variant &operator=(c_game_engine_king_variant &); /* compiler_generated() */
	c_game_engine_king_variant &operator=(c_game_engine_king_variant const &); /* compiler_generated() */
};
static_assert(sizeof(c_game_engine_king_variant) == 512, "Invalid c_game_engine_king_variant size");

struct c_game_engine_oddball_variant :
	public c_game_engine_base_variant
{
	unsigned long Flags; // 0x1D0
	short points_to_win; // 0x1D4
	short unknown_time; // 0x1D6
	short carrying_points; // 0x1D8
	char kill_points; // 0x1DA
	char ball_kill_points; // 0x1DB
	char ball_carrier_kill_points; // 0x1DC
	char ball_count; // 0x1DD
	short ball_initial_delay; // 0x1DE
	short ball_respawn_delay; // 0x1E0
	c_player_traits ball_carrier_traits; // 0x1E2
	c_game_engine_oddball_variant(c_game_engine_oddball_variant &); /* compiler_generated() */
	c_game_engine_oddball_variant(c_game_engine_oddball_variant const &); /* compiler_generated() */
	c_game_engine_oddball_variant(); /* compiler_generated() */
	c_game_engine_oddball_variant &operator=(c_game_engine_oddball_variant &); /* compiler_generated() */
	c_game_engine_oddball_variant &operator=(c_game_engine_oddball_variant const &); /* compiler_generated() */
};
static_assert(sizeof(c_game_engine_oddball_variant) == 512, "Invalid c_game_engine_oddball_variant size");

struct c_game_engine_sandbox_variant :
	public c_game_engine_base_variant
{
	unsigned char flags; // 0x1D0
	unsigned char edit_mode; // 0x1D1
	unsigned short editor_respawn_time; // 0x1D2
	c_player_traits editor_traits; // 0x1D4
	c_game_engine_sandbox_variant(c_game_engine_sandbox_variant &); /* compiler_generated() */
	c_game_engine_sandbox_variant(c_game_engine_sandbox_variant const &); /* compiler_generated() */
	c_game_engine_sandbox_variant(); /* compiler_generated() */
	c_game_engine_sandbox_variant &operator=(c_game_engine_sandbox_variant &); /* compiler_generated() */
	c_game_engine_sandbox_variant &operator=(c_game_engine_sandbox_variant const &); /* compiler_generated() */
};
static_assert(sizeof(c_game_engine_sandbox_variant) == 496, "Invalid c_game_engine_sandbox_variant size");

struct c_game_engine_vip_variant :
	public c_game_engine_base_variant
{
	short score_to_win; // 0x1D0
	unsigned char __pad0[2]; // 0x1D2
	unsigned short flags; // 0x1D4
	char kill_points; // 0x1D6
	char vip_takedown_points; // 0x1D7
	char kill_as_vip_points; // 0x1D8
	char vip_death_points; // 0x1D9
	char goal_arrival_points; // 0x1DA
	char suicide_points; // 0x1DB
	char betrayal_points; // 0x1DC
	char vip_betrayal_points; // 0x1DD
	char next_vip; // 0x1DE
	char goal_zone_movement; // 0x1DF
	char goal_zone_movement_order; // 0x1E0
	unsigned char __pad1[1]; // 0x1E1
	short vip_proximity_radius; // 0x1E2
	c_player_traits vip_team_traits; // 0x1E4
	c_player_traits vip_proximity_traits; // 0x200
	c_player_traits vip_traits; // 0x21C
	c_game_engine_vip_variant(c_game_engine_vip_variant &); /* compiler_generated() */
	c_game_engine_vip_variant(c_game_engine_vip_variant const &); /* compiler_generated() */
	c_game_engine_vip_variant(); /* compiler_generated() */
	c_game_engine_vip_variant &operator=(c_game_engine_vip_variant &); /* compiler_generated() */
	c_game_engine_vip_variant &operator=(c_game_engine_vip_variant const &); /* compiler_generated() */
};
static_assert(sizeof(c_game_engine_vip_variant) == 568, "Invalid c_game_engine_vip_variant size");

struct c_game_engine_territories_variant :
	public c_game_engine_base_variant
{
	unsigned short flags; // 0x1D0
	short respawn_on_capture; // 0x1D2
	short territory_capture_time; // 0x1D4
	short sudden_death_time; // 0x1D6
	c_player_traits defender_traits; // 0x1D8
	c_player_traits attacker_traits; // 0x1F4
	c_game_engine_territories_variant(c_game_engine_territories_variant &); /* compiler_generated() */
	c_game_engine_territories_variant(c_game_engine_territories_variant const &); /* compiler_generated() */
	c_game_engine_territories_variant(); /* compiler_generated() */
	c_game_engine_territories_variant &operator=(c_game_engine_territories_variant &); /* compiler_generated() */
	c_game_engine_territories_variant &operator=(c_game_engine_territories_variant const &); /* compiler_generated() */
};
static_assert(sizeof(c_game_engine_territories_variant) == 528, "Invalid c_game_engine_territories_variant size");

struct c_game_engine_juggernaut_variant :
	public c_game_engine_base_variant
{
	short ScoreToWin; // 0x1D0
	unsigned char __pad0[2]; // 0x1D2
	char field_1D4; // 0x1D4
	char field_1D5; // 0x1D5
	unsigned char first_juggernaut; // 0x1D6
	unsigned char next_juggernaut; // 0x1D7
	unsigned char flags; // 0x1D8
	unsigned char goal_movement_type; // 0x1D9
	unsigned char goal_movement_order; // 0x1DA
	char kill_points; // 0x1DB
	char takedown_points; // 0x1DC
	char kill_as_juggernaut_points; // 0x1DD
	char goal_arrival_points; // 0x1DE
	char suicide_points; // 0x1DF
	char betrayal_points; // 0x1E0
	char next_juggernaut_delay; // 0x1E1
	c_player_traits juggernaut_traits; // 0x1E2
	c_game_engine_juggernaut_variant(c_game_engine_juggernaut_variant &); /* compiler_generated() */
	c_game_engine_juggernaut_variant(c_game_engine_juggernaut_variant const &); /* compiler_generated() */
	c_game_engine_juggernaut_variant(); /* compiler_generated() */
	c_game_engine_juggernaut_variant &operator=(c_game_engine_juggernaut_variant &); /* compiler_generated() */
	c_game_engine_juggernaut_variant &operator=(c_game_engine_juggernaut_variant const &); /* compiler_generated() */
	unsigned char __pad1[2]; // 0x1FE
};
static_assert(sizeof(c_game_engine_juggernaut_variant) == 512, "Invalid c_game_engine_juggernaut_variant size");

struct c_game_engine_assault_variant :
	public c_game_engine_base_variant
{
	short flags; // 0x1D0
	short respawn_on_capture; // 0x1D2
	short game_mode; // 0x1D4
	short enemy_bomb_waypoint; // 0x1D6
	short detonations_to_win; // 0x1D8
	unsigned char __pad0[2]; // 0x1DA
	short unknown_points; // 0x1DC
	unsigned char __pad1[4]; // 0x1DE
	short sudden_death_time; // 0x1E2
	short bomb_reset_time; // 0x1E4
	short bomb_arming_time; // 0x1E6
	short bomb_disarming_time; // 0x1E8
	short bomb_fuse_time; // 0x1EA
	c_player_traits bomb_carrier_traits; // 0x1EC
	c_player_traits field_208; // 0x208
	c_game_engine_assault_variant(c_game_engine_assault_variant &); /* compiler_generated() */
	c_game_engine_assault_variant(c_game_engine_assault_variant const &); /* compiler_generated() */
	c_game_engine_assault_variant(); /* compiler_generated() */
	c_game_engine_assault_variant &operator=(c_game_engine_assault_variant &); /* compiler_generated() */
	c_game_engine_assault_variant &operator=(c_game_engine_assault_variant const &); /* compiler_generated() */
	unsigned char __pad2[4]; // 0x224
};
static_assert(sizeof(c_game_engine_assault_variant) == 552, "Invalid c_game_engine_assault_variant size");

struct c_game_engine_infection_variant :
	public c_game_engine_base_variant
{
	char field_1D0; // 0x1D0
	unsigned char haven_movement; // 0x1D1
	unsigned char field_1D2; // 0x1D2
	unsigned char initial_zombie_count; // 0x1D3
	unsigned short haven_move_time; // 0x1D4
	unsigned char zombie_kill_points; // 0x1D6
	unsigned char infection_points; // 0x1D7
	unsigned char haven_arrived_points; // 0x1D8
	unsigned char field_1D9; // 0x1D9
	unsigned char field_1DA; // 0x1DA
	unsigned char last_man_standing_bonus_points; // 0x1DB
	c_player_traits infected_traits; // 0x1DC
	c_player_traits alpha_traits; // 0x1F8
	c_player_traits haven_traits; // 0x214
	c_player_traits last_man_standing_traits; // 0x230
	c_game_engine_infection_variant(c_game_engine_infection_variant &); /* compiler_generated() */
	c_game_engine_infection_variant(c_game_engine_infection_variant const &); /* compiler_generated() */
	c_game_engine_infection_variant(); /* compiler_generated() */
	c_game_engine_infection_variant &operator=(c_game_engine_infection_variant &); /* compiler_generated() */
	c_game_engine_infection_variant &operator=(c_game_engine_infection_variant const &); /* compiler_generated() */
};
static_assert(sizeof(c_game_engine_infection_variant) == 592, "Invalid c_game_engine_infection_variant size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline c_game_engine_base_variant *c_game_variant::get_base_variant() // 0x1092CFD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_base_variant@c_game_variant@@QAEPAUc_game_engine_base_variant@@XZ");
	// c_game_variant *const this;

	return (c_game_engine_base_variant *)storage;
}

/* ---------- private code */

#endif // __BLAM_GAME_GAME_VARIANT_HPP__
