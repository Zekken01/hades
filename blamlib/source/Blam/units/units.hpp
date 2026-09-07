#ifndef __BLAM_UNITS_UNITS_HPP__
#define __BLAM_UNITS_UNITS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/aim_target.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/motor/motor.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/objects/target_tracking.hpp"
#include "Blam/units/unit_definitions.hpp"

/* ---------- forward declarations */

struct c_target_tracking_system;
struct real_vector3d;
struct s_aim_assist_targeting_result;
struct s_damage_reporting_info;
struct s_motor_data;
struct s_object_header_block_reference;
struct s_unit_attacker;
struct s_unit_data;
struct s_unit_predicted_weapon_state;
struct s_unit_seat_definition;
struct s_unit_seat_source;
struct s_unit_weapon_set;

/* ---------- constants */

enum e_unit_messages
{
	_unit_message_idle = 0,
	_unit_message_fire_1,
	_unit_message_fire_2,
	_unit_message_misfire_1,
	_unit_message_misfire_2,
	_unit_message_light_on,
	_unit_message_light_off,
	_unit_message_reload_empty,
	_unit_message_reload_full,
	_unit_message_reload_enter,
	_unit_message_reload_continue_empty,
	_unit_message_reload_continue_full,
	_unit_message_reload_exit,
	_unit_message_overcharged,
	_unit_message_overheating,
	_unit_message_o_h_exit,
	_unit_message_unknown16,
	_unit_message_melee,
	_unit_message_put_away_1,
	_unit_message_put_away_2,
	_unit_message_ready_1,
	_unit_message_ready_2,
	_unit_message_ready_overheated_1,
	_unit_message_ready_overheated_2,
	_unit_message_unknown24,
	_unit_message_unknown25,
	_unit_message_throw_grenade,
	_unit_message_throw_overheated,
	_unit_message_throw_equipment,
	_unit_message_melee_1sthit,
	_unit_message_melee_1sthit2idle,
	_unit_message_melee_2ndhit,
	_unit_message_melee_2ndhit2idle,
	_unit_message_melee_3rdhit,
	_unit_message_melee_strike_1,
	_unit_message_melee_strike_2,
	_unit_message_melee_strike_3,
	_unit_message_melee_strike_4,
	_unit_message_melee_dash,
	_unit_message_melee_lunge,
	_unit_message_melee_dash_airborne,
	_unit_message_melee_lunge_airborne,
	_unit_message_melee_lunge_unaimed,
	_unit_message_melee_lunge_unaimed_airborne,
	_unit_message_jump,
	_unit_message_fall,
	_unit_message_land_soft,
	_unit_message_land_hard,
	_unit_message_sprint_enter,
	_unit_message_sprint_loop,
	_unit_message_sprint_loop_airborne,
	_unit_message_sprint_exit,
};

/* ---------- definitions */

struct s_unit_weapon_set
{
	short identifier; // 0x0
	s_static_array<char,2> indices; // 0x2
};
static_assert(sizeof(s_unit_weapon_set) == 4, "Invalid s_unit_weapon_set size");

struct s_unit_predicted_weapon_state
{
	short rounds_loaded; // 0x0
	short rounds_left; // 0x2
	unsigned char __pad0[4]; // 0x4
};
static_assert(sizeof(s_unit_predicted_weapon_state) == 8, "Invalid s_unit_predicted_weapon_state size");

struct s_unit_attacker
{
	long game_time; // 0x0
	float score; // 0x4
	long team_index; // 0x8
	long player_index; // 0xC
};
static_assert(sizeof(s_unit_attacker) == 16, "Invalid s_unit_attacker size");

struct s_unit_data :
	public s_motor_data
{
	long awake_tick_count; // 0x184
	long actor_index; // 0x188
	long simulation_actor_index; // 0x18C
	c_flags<enum e_unit_flags,unsigned long> unit_flags; // 0x190
	long team; // 0x194
	long player_index; // 0x198
	long last_weak_player_index; // 0x19C
	long game_time_at_last_unit_effect; // 0x1A0
	long unit_control_flags; // 0x1A4
	long desired_animation_seat; // 0x1A8
	real_vector3d desired_facing_vector; // 0x1AC
	real_vector3d desired_aiming_vector; // 0x1B8
	real_vector3d aiming_vector; // 0x1C4
	real_vector3d aiming_velocity; // 0x1D0
	real_vector3d desired_looking_vector; // 0x1DC
	real_vector3d looking_vector; // 0x1E8
	real_vector3d looking_velocty; // 0x1F4
	real_point3d gaze_position; // 0x200
	real_vector3d throttle; // 0x20C
	real_vector3d control_throttle; // 0x218
	unsigned char control_context_identifier; // 0x224
	char aiming_speed; // 0x225
	s_damage_reporting_info special_death_damage_reporting_info; // 0x226
	char special_death_type; // 0x22A
	unsigned char __pad0[1]; // 0x22B
	short special_death_node_index; // 0x22C
	unsigned char __pad1[2]; // 0x22E
	real_vector3d special_death_node_acceleration; // 0x230
	float primary_trigger; // 0x23C
	float secondary_trigger; // 0x240
	s_aim_assist_targeting_result aim_assist_data; // 0x244
	c_target_tracking_system target_tracking; // 0x26C
	c_flags<enum e_unit_control_flags,unsigned long> persistent_control_flags; // 0x2AC
	char weapon_drop_delay_ticks; // 0x2B0
	char left_eye_node; // 0x2B1
	char right_eye_node; // 0x2B2
	unsigned char horizontal_aiming_change; // 0x2B3
	unsigned char primary_fire_timer; // 0x2B4
	unsigned char secondary_fire_timer; // 0x2B5
	short seat_index; // 0x2B6
	float ambient_illumination; // 0x2B8
	float self_illumination; // 0x2BC
	float mouth_aperture; // 0x2C0
	float mouth_time; // 0x2C4
	s_unit_weapon_set current_weapon_set; // 0x2C8
	s_unit_weapon_set desired_weapon_set; // 0x2CC
	s_static_array<long,4> weapon_object_indices; // 0x2D0
	s_static_array<long,4> weapon_last_used_at_game_time; // 0x2E0
	s_static_array<long,4> equipment_object_indices; // 0x2F0
	long active_equipment_object_indices[4]; // 0x300
	long equipment_pickup_time; // 0x310
	long consumable_energy_level; // 0x314
	long consumable_energy_restored_game_time; // 0x318
	short weapon_firing_time; // 0x31C
	char current_grenade_index; // 0x31E
	char desired_grenade_index; // 0x31F
	s_static_array<unsigned char,4> grenade_counts; // 0x320
	char current_zoom_level; // 0x324
	char desired_zoom_level; // 0x325
	unsigned char __pad2[1]; // 0x326
	char aiming_change; // 0x327
	long weapon_control_last_active_time; // 0x328
	long motion_control_unit_index; // 0x32C
	long weapon_control_unit_index; // 0x330
	long last_vehicle_index; // 0x334
	long last_vehicle_exit_game_time; // 0x338
	short fake_squad_index; // 0x33C
	char impulse_vehicle_from_seat_ticks; // 0x33E
	char seat_power_valid_flags; // 0x33F
	float seat_power; // 0x340
	float integrated_light_power; // 0x344
	float integrated_light_battery; // 0x348
	float integrated_night_vision_power; // 0x34C
	float open_state; // 0x350
	unsigned char seat_acceleration_state[108]; // 0x354
	long predicted_player_index; // 0x3C0
	long predicted_simulation_actor_index; // 0x3C4
	long predicted_simulation_actor_squad_index; // 0x3C8
	long predicted_simulation_actor_cell_index; // 0x3CC
	long predicted_simulation_actor_spawn_point_index; // 0x3D0
	s_static_array<s_unit_predicted_weapon_state,4> predicted_weapon_state; // 0x3D4
	float active_camouflage; // 0x3F4
	float active_camouflage_maximum; // 0x3F8
	float active_camouflage_regrowth; // 0x3FC
	long active_camouflage_end_time; // 0x400
	float health_pack_end_time; // 0x404
	float health_pack_body_vitality_maximum; // 0x408
	float health_pack_shield_vitality_maximum; // 0x40C
	unsigned char map_editor_helper_flags; // 0x410
	unsigned char __pad3[1]; // 0x411
	short emp_timer; // 0x412
	short emp_campaign_metagame_timer; // 0x414
	unsigned char __pad4[2]; // 0x416
	float crouch_fraction; // 0x418
	short delayed_damage_category; // 0x41C
	short delayed_damage_timer; // 0x41E
	float delayed_damage_peak; // 0x420
	long delayed_damage_owner_weak_object_index; // 0x424
	long flaming_death_attacker_object_index; // 0x428
	float run_blindly_angle; // 0x42C
	float run_blindly_angular_velocity; // 0x430
	long hologram_creator_weak_unit_index; // 0x434
	long hologram_creation_time; // 0x438
	long hologram_ticks_left; // 0x43C
	long hologram_definition_index; // 0x440
	float hologram_shimmer_value; // 0x444
	real_point3d hologram_destination; // 0x448
	long sync_action_type; // 0x454
	real_point3d sync_action_origin; // 0x458
	real_vector3d sync_action_forward; // 0x464
	real_vector3d sync_action_up; // 0x470
	bool sync_action_critical_participant; // 0x47C
	unsigned char field_480[40]; // 0x47D
	unsigned char __pad5[3]; // 0x4A5
	long time_of_death; // 0x4A8
	float movement_stun; // 0x4AC
	short movement_stun_ticks; // 0x4B0
	short unknown_4B2_ticks; // 0x4B2
	unsigned char __pad6[4]; // 0x4B4
	short melee_inhibit_time; // 0x4B8
	c_flags<enum e_assassination_event_flags,unsigned char> assassination_event_flags; // 0x4BA
	unsigned char assassination_event_ticks; // 0x4BB
	s_static_array<s_unit_attacker,4> attackers; // 0x4BC
	s_static_array<long,4> attacker_weapon_unit_indices; // 0x4FC
	float boost_power_meter; // 0x50C
	float boost_recharge_delay; // 0x510
	long last_enemies_moving_nearby_tick; // 0x514
	long last_damaged_tick; // 0x518
	long last_in_soft_kill_volume_time; // 0x51C
	long last_in_phantom_volume_time; // 0x520
	long unknown_tick; // 0x524
	long unknown_team_index; // 0x528
	long unknown_object_index; // 0x52C
	s_object_header_block_reference animation_storage; // 0x530
	s_object_header_block_reference speech_storage; // 0x534
	unsigned long unit_ai_flags; // 0x538
	s_unit_data(s_unit_data &); /* compiler_generated() */
	s_unit_data(s_unit_data const &); /* compiler_generated() */
	s_unit_data(); /* compiler_generated() */
	s_unit_data &operator=(s_unit_data &); /* compiler_generated() */
	s_unit_data &operator=(s_unit_data const &); /* compiler_generated() */
	unsigned char __pad7[84]; // 0x53C
};
static_assert(sizeof(s_unit_data) == 1424, "Invalid s_unit_data size");

struct s_unit_seat_source
{
	long parent_unit_index; // 0x0
	short seat_index; // 0x4
	unsigned char __pad0[2]; // 0x6
	s_unit_seat_definition *seat; // 0x8
};
static_assert(sizeof(s_unit_seat_source) == 12, "Invalid s_unit_seat_source size");

/* ---------- prototypes */

extern long unit_get_ultimate_motion_control_unit_index(long unit_index);
extern long unit_get_current_or_last_weak_player_index(long unit_index);
extern long unit_get_player_index(long unit_index);
extern void unit_drop_grenades(long unit_index);
extern void unit_drop_equipment(long unit_index, long slot_index);
extern bool unit_is_holding_objective(long unit_index);
extern bool unit_has_vision(long unit_index);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_UNITS_UNITS_HPP__
