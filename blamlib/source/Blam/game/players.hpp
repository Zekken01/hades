#ifndef __BLAM_GAME_PLAYERS_HPP__
#define __BLAM_GAME_PLAYERS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/aim_target.hpp"
#include "Blam/game/engine/game_engine_player_traits.hpp"
#include "Blam/game/player_configuration.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeUndo.hpp"

/* ---------- forward declarations */

class c_player_output_user_iterator;
struct c_aim_target_object;
struct c_player_traits;
struct real_vector3d;
struct s_aim_assist_targeting_result;
struct s_damage_history;
struct s_damage_reporting_info;
struct s_datum;
struct s_player_action;
struct s_player_action_context;
struct s_player_configuration;
struct s_player_datum;
struct s_player_identifier;
struct s_player_interaction;
struct s_player_motion;
struct s_players_globals;
struct s_scenario_location;
struct s_unit_weapon_set;

/* ---------- constants */

/* ---------- definitions */

struct s_player_datum :
	public s_datum
{
	public:
	struct s_tracking_objects
	{
		char mask; // 0x0
		long object_index; // 0x4
		long field_8; // 0x8
	};
	// static_assert(sizeof(s_tracking_objects) == 12, "Invalid s_tracking_objects size");
	// Withheld: the type inventory does not describe this type, so its
	// padding could not be reconstructed.
	struct s_tank_mode_state
	{
		long LastUsedTick; // 0x0
		float Duration; // 0x4
		float DamageAccelerationScale; // 0x8
		float field_C; // 0xC
		float field_10; // 0x10
		float field_14; // 0x14
	};
	// static_assert(sizeof(s_tank_mode_state) == 24, "Invalid s_tank_mode_state size");
	// Withheld: the type inventory does not describe this type, so its
	// padding could not be reconstructed.
	struct s_reactive_armor_state
	{
		long last_used_game_time; // 0x0
		float duration; // 0x4
		float damage_acceleration_scale; // 0x8
		long field_C; // 0xC
	};
	// static_assert(sizeof(s_reactive_armor_state) == 16, "Invalid s_reactive_armor_state size");
	// Withheld: the type inventory does not describe this type, so its
	// padding could not be reconstructed.
	struct s_damage_history
	{
		unsigned short field_0; // 0x0
		s_damage_reporting_info damage_reporting_info; // 0x2
		unsigned long time; // 0x8
		s_damage_history(s_damage_history &); /* compiler_generated() */
		s_damage_history(s_damage_history const &); /* compiler_generated() */
		s_damage_history(); /* compiler_generated() */
		s_damage_history &operator=(s_damage_history &); /* compiler_generated() */
		s_damage_history &operator=(s_damage_history const &); /* compiler_generated() */
	};
	// static_assert(sizeof(s_damage_history) == 12, "Invalid s_damage_history size");
	// Withheld: the type inventory does not describe this type, so its
	// padding could not be reconstructed.
	public:
	unsigned long flags; // 0x4
	s_player_identifier player_identifier; // 0x8
	unsigned long left_game_time; // 0x10
	s_machine_identifier machine_identifier; // 0x14
	short machine_index; // 0x24
	short machine_input_user_index; // 0x26
	long machine_controller_index; // 0x28
	s_scenario_location location; // 0x2C
	unsigned long unit_index; // 0x30
	unsigned long dead_unit_index; // 0x34
	unsigned long previous_unit_index; // 0x38
	unsigned long unknown_flags2; // 0x3C
	unsigned short unknown_simulation_ticks2; // 0x40
	unsigned short unknown_simulation_ticks3; // 0x42
	unsigned short unknown_simulation_ticks4; // 0x44
	unsigned short unknown_flags3; // 0x46
	unsigned char unknown_simulation_ticks; // 0x48
	unsigned char field_4A; // 0x49
	short hsc_forced_character_type_index; // 0x4A
	short character_type_index; // 0x4C
	short previous_character_type_index; // 0x4E
	unsigned long consumable_index; // 0x50
	unsigned char melee_recovery_timer; // 0x54
	unsigned char melee_soft_recovery_timer; // 0x55
	unsigned char grenade_suppression_timer; // 0x56
	bool is_sprinting; // 0x57
	bool is_crouching; // 0x58
	bool is_firing_left; // 0x59
	bool is_firing_right; // 0x5A
	unsigned char field_5B; // 0x5B
	unsigned short magnification_level; // 0x5C
	bool sprint_interrupted_firing; // 0x5E
	bool sprint_interrupted_zoom; // 0x5F
	short sprint_cooldown; // 0x60
	short sprint_cooldown2; // 0x62
	real_vector3d position; // 0x64
	s_player_configuration configuration; // 0x70
	s_player_configuration desired_configuration; // 0x1690
	long single_player_respawn_timer; // 0x2CB0
	bool early_respawn_requested; // 0x2CB4
	bool respawn_in_progress; // 0x2CB5
	bool respawn_forced; // 0x2CB6
	long respawn_timer; // 0x2CB8
	long respawn_timer_countdown_seconds; // 0x2CBC
	unsigned long respawn_time_penalty; // 0x2CC0
	char blocking_teleporter; // 0x2CC4
	long dead_timer; // 0x2CC8
	long in_game_timer; // 0x2CCC
	long alive_timer; // 0x2CD0
	long unknown_input_global_ticks; // 0x2CD4
	long grenade_regeneration_timer; // 0x2CD8
	long unknown_object_index; // 0x2CDC
	long last_aim_target_time; // 0x2CE0
	unsigned short ticks_sprinting; // 0x2CE4
	unsigned short field_2CE6; // 0x2CE6
	unsigned short sprint_restoration_timer; // 0x2CE8
	unsigned short sprint_depleted_timer; // 0x2CEA
	bool sprint_disabled; // 0x2CEC
	unsigned short unknown_ticks_4; // 0x2CEE
	c_aim_target_object aim_target_object; // 0x2CF0
	long field_2CFC; // 0x2CFC
	s_tracking_objects tracking_objects[8]; // 0x2D00
	unsigned short respawn_duration_seconds; // 0x2D60
	bool first_spawn; // 0x2D62
	unsigned char respawn_failed_reason; // 0x2D63
	struct
	{
		long LastUsedTick; // 0x0
		float Duration; // 0x4
		float DamageAccelerationScale; // 0x8
		float field_C; // 0xC
		float field_10; // 0x10
		float field_14; // 0x14
	} tank_mode_state; // 0x2D64
	struct
	{
		long last_used_game_time; // 0x0
		float duration; // 0x4
		float damage_acceleration_scale; // 0x8
		long field_C; // 0xC
	} reactive_armor_state; // 0x2D7C
	long stamina_restore_near_death_timer; // 0x2D8C
	bool grenade_scavenger_ability_used; // 0x2D90
	long last_aim_assist_target_player_index; // 0x2D94
	short unused; // 0x2D98
	char game_engine_vehicle_use_timer; // 0x2D9A
	char game_engine_simulation_update_timer; // 0x2D9B
	char game_engine_simulation_update_timer2; // 0x2D9C
	bool was_sneaking; // 0x2D9D
	bool is_sneaking; // 0x2D9E
	unsigned short aim_assist_update_timer; // 0x2DA0
	unsigned short lives; // 0x2DA2
	long game_grief_player_index; // 0x2DA4
	unsigned long last_killed_game_time; // 0x2DA8
	c_player_traits traits; // 0x2DAC
	long powerup_pickup_times[3]; // 0x2DC8
	long spectating_player_index; // 0x2DD4
	bool sandbox_rotating; // 0x2DD8
	float sandbox_extend_distance; // 0x2DDC
	real_vector3d sandbox_rotation_throttle; // 0x2DE0
	unsigned short time_in_hill; // 0x2DEC
	unsigned short time_outside_Hill; // 0x2DEE
	unsigned short time_hill_Left; // 0x2DF0
	short nemesis_totals[16]; // 0x2DF4
	char field_2E14; // 0x2E14
	unsigned long last_hit_marker_game_time; // 0x2E18
	long revenge_player_Index; // 0x2E1C
	s_damage_reporting_info revenge_event_type; // 0x2E20
	bool revenge_taken; // 0x2E24
	unsigned char unknown_damage_reporting_timer; // 0x2E28
	char unknown_damage_reporting_timer2; // 0x2E29
	s_damage_reporting_info unknown_damagereportinginfo; // 0x2E2A
	s_damage_reporting_info unknown_damagereportinginfo2; // 0x2E2E
	s_damage_reporting_info unknown_damagereportinginfo3; // 0x2E32
	char field_2E38; // 0x2E36
	char field_2E39; // 0x2E37
	short field_2E3A; // 0x2E38
	short field_2E3C; // 0x2E3A
	short field_2E3E; // 0x2E3C
	long last_ejected_from_vehicle_index; // 0x2E40
	unsigned long last_ejected_from_vehicle_game_time; // 0x2E44
	long assassination_victim_unit_index; // 0x2E48
	bool is_assassination_victim; // 0x2E4C
	real_point3d assasination_authorative_position; // 0x2E50
	real_vector3d assasination_authorative_forward; // 0x2E5C
	unsigned char assassination_state[60]; // 0x2E68
	s_damage_history damage_history[8]; // 0x2EA4
	long field_2F04; // 0x2F04
	s_player_datum(s_player_datum &); /* compiler_generated() */
	s_player_datum(s_player_datum const &); /* compiler_generated() */
	s_player_datum(); /* compiler_generated() */
	s_player_datum &operator=(s_player_datum &); /* compiler_generated() */
	s_player_datum &operator=(s_player_datum const &); /* compiler_generated() */
};
// static_assert(sizeof(s_player_datum) == 12040, "Invalid s_player_datum size");
// The layout above is the PDB's member list without its padding, so the
// size assertion is withheld: it would fail on alignment alone.

struct s_player_interaction
{
	unsigned short type; // 0x0
	unsigned short seat_index_or_pickup_flags; // 0x2
	long object_index; // 0x4
};
// static_assert(sizeof(s_player_interaction) == 8, "Invalid s_player_interaction size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

#pragma pack(push, 4)
struct s_player_action_context
{
	s_player_interaction interaction; // 0x0
	long melee_target_object_index; // 0x8
};
#pragma pack(pop)
// static_assert(sizeof(s_player_action_context) == 12, "Invalid s_player_action_context size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

struct s_player_action
{
	unsigned char __pad0[4]; // 0x0
	unsigned char control_context_identifier; // 0x4
	unsigned char __pad1[3]; // 0x5
	c_flags<enum e_unit_control_flags,unsigned long> control_flags; // 0x8
	float yaw; // 0xC
	float pitch; // 0x10
	float throttle_x; // 0x14
	float throttle_y; // 0x18
	bool map_editor_rotation_valid; // 0x1C
	unsigned char __pad2[3]; // 0x1D
	float map_editor_rotation_yaw; // 0x20
	float map_editor_rotation_pitch; // 0x24
	short map_editor_flags; // 0x28
	unsigned char __pad3[2]; // 0x2A
	float primary_trigger; // 0x2C
	float secondary_trigger; // 0x30
	unsigned short action_flags; // 0x34
	s_unit_weapon_set desired_weapon_set; // 0x36
	short desired_grenade; // 0x3A
	short zoom_level; // 0x3C
	unsigned char __pad4[2]; // 0x3E
	s_player_action_context action_context; // 0x40
	s_aim_assist_targeting_result aim_assist_targeting_result; // 0x4C
	long field_74; // 0x74
	unsigned long long action_test_flags; // 0x78
	s_player_action(s_player_action &); /* compiler_generated() */
	s_player_action(s_player_action const &); /* compiler_generated() */
	s_player_action(); /* compiler_generated() */
	s_player_action &operator=(s_player_action &); /* compiler_generated() */
	s_player_action &operator=(s_player_action const &); /* compiler_generated() */
};
// static_assert(sizeof(s_player_action) == 128, "Invalid s_player_action size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

struct s_player_motion
{
	unsigned char __pad0[4]; // 0x0
	unsigned char control_context_identifier; // 0x4
	unsigned char __pad1[3]; // 0x5
	float yaw; // 0x8
	float pitch; // 0xC
	float throttle_x; // 0x10
	float throttle_y; // 0x14
	unsigned short action_flags; // 0x18
	s_unit_weapon_set desired_weapon_set; // 0x1A
	short ZoomLevel; // 0x1E
	unsigned char __pad2[8]; // 0x20
	s_aim_assist_targeting_result aim_assist_targeting_result; // 0x28
};
// static_assert(sizeof(s_player_motion) == 80, "Invalid s_player_motion size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

#pragma pack(push, 4)
struct s_players_globals
{
	long players_in_game_count; // 0x0
	bool player_input_disabled; // 0x4
	bool mostly_input_inhibit; // 0x5
	bool field_6; // 0x6
	bool sprint_disabled; // 0x7
	bool consumables_disabled; // 0x8
	unsigned char __pad0[3]; // 0x9
	unsigned long machine_valid_mask; // 0xC
	s_machine_identifier machine_identifiers[17]; // 0x10
	bool local_machine_valid; // 0x120
	char local_machine_identifier[16]; // 0x121
	unsigned char __pad1[3]; // 0x131
	long local_machine_index; // 0x134
	bool safe_to_respawn; // 0x138
	unsigned char __pad2[1]; // 0x139
	short respawn_failure; // 0x13A
	char field_13C; // 0x13C
	char field_13D; // 0x13D
	char field_13E; // 0x13E
	char field_13F; // 0x13F
	real_point3d zone_set_switch_teleport_position; // 0x140
	real_vector3d zone_set_switch_teleport_forward; // 0x14C
	long zone_set_switch_trigger_unknown1; // 0x158
	long zone_set_switch_trigger_index; // 0x15C
	short field_160; // 0x160
	short field_162; // 0x162
	long local_player_index; // 0x164
	long zone_set_index; // 0x168
	unsigned long zone_set_switch_flags[32]; // 0x16C
	unsigned short terminals_completed_mask; // 0x1EC
	unsigned short terminals_accessed_mask; // 0x1EE
	bool player_reading_terminal; // 0x1F0
	unsigned char __pad3[3]; // 0x1F1
	long unknown[16]; // 0x1F4
};
#pragma pack(pop)
static_assert(sizeof(s_players_globals) == 564, "Invalid s_players_globals size");

class c_player_output_user_iterator
{
public:
	_inline void begin(long player_index);
	void begin_unit(long);
	_inline bool next();
	_inline long get_output_user_index() const;
private:
	long m_player_index; // 0x0
	long m_output_user_index; // 0x4
};
static_assert(sizeof(c_player_output_user_iterator) == 8, "Invalid c_player_output_user_iterator size");

/* ---------- prototypes */

extern c_data_array<s_player_datum> *players_get();
extern s_player_datum *player_get(unsigned long player_index);

/* ---------- globals */

/* ---------- public code */

_inline void c_player_output_user_iterator::begin(long player_index) // 0x10A550D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?begin@c_player_output_user_iterator@@QAEXJ@Z");
	// long player_index;

	m_player_index = player_index;
	m_output_user_index = 0xFFFFFFFF;
}

_inline bool c_player_output_user_iterator::next() // 0x10A55640
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?next@c_player_output_user_iterator@@QAE_NXZ");
	// c_player_output_user_iterator *const this;
	// function call : long (*const)(long, long)

	if (m_player_index != -1)
		m_output_user_index = ((long(__cdecl *)(long, long))0x589b90)(m_player_index, m_output_user_index);

	return m_output_user_index != -1;
}

_inline long c_player_output_user_iterator::get_output_user_index() const // 0x10A55610
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_output_user_index@c_player_output_user_iterator@@QBEJXZ");
	// c_player_output_user_iterator const *const this;

	return m_output_user_index;
}

/* ---------- private code */

#endif // __BLAM_GAME_PLAYERS_HPP__
