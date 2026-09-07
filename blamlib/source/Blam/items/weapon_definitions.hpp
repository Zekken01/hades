#ifndef __BLAM_ITEMS_WEAPON_DEFINITIONS_HPP__
#define __BLAM_ITEMS_WEAPON_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/items/item_definitions.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct real_bounds;
struct real_vector2d;
struct real_vector3d;
struct s_game_object_predicted_resource;
struct s_item_definition;
struct s_tag_field_definition;
struct s_tag_reference;
struct s_tag_reference_short;
struct s_unit_target_tracking_block;
struct s_weapon_barrel_definition;
struct s_weapon_barrel_firing_effect;
struct s_weapon_definition;
struct s_weapon_first_person_block;
struct s_weapon_magazine_definition;
struct s_weapon_magazine_magazine_equipment_block;
struct s_weapon_trigger_definition;
struct short_bounds;

/* ---------- constants */

/* ---------- definitions */

struct s_game_object_predicted_resource
{
	short type; // 0x0
	short resource_index; // 0x2
	s_tag_reference_short tag_index; // 0x4
};
static_assert(sizeof(s_game_object_predicted_resource) == 8, "Invalid s_game_object_predicted_resource size");

struct s_unit_target_tracking_block
{
	c_tag_block<unsigned long> tracking_types; // 0x0
	float acquire_time; // 0xC
	float grace_time; // 0x10
	float decay_time; // 0x14
	s_tag_reference tracking_sound; // 0x18
	s_tag_reference locked_sound; // 0x28
};
static_assert(sizeof(s_unit_target_tracking_block) == 56, "Invalid s_unit_target_tracking_block size");

#pragma pack(push, 4)
struct s_weapon_barrel_firing_effect
{
	short shot_count_lower_bound; // 0x0
	short shot_count_upper_bound; // 0x2
	s_tag_reference effects[12]; // 0x4
};
#pragma pack(pop)
static_assert(sizeof(s_weapon_barrel_firing_effect) == 196, "Invalid s_weapon_barrel_firing_effect size");

#pragma pack(push, 4)
struct s_weapon_barrel_definition
{
	c_flags<enum e_barrel_flags,long> barrel_flags; // 0x0
	real_bounds rounds_per_second; // 0x4
	float acceleration_time; // 0xC
	float deceleration_time; // 0x10
	float barrel_spin_scale; // 0x14
	float blurred_rate_of_fire; // 0x18
	short_bounds shots_per_fire; // 0x1C
	float fire_recovery_time; // 0x20
	float soft_recovery_fraction; // 0x24
	short magazine_index; // 0x28
	short rounds_per_shot; // 0x2A
	short minimum_rounds_loaded; // 0x2C
	short rounds_between_tracers; // 0x2E
	unsigned long optional_barrel_marker_name; // 0x30
	c_enum<enum e_weapon_barrel_prediction_type,short> prediction_type; // 0x34
	c_enum<enum e_weapon_barrel_firing_noise,short> firing_noise; // 0x36
	float error_acceleration_time; // 0x38
	float error_deceleration_time; // 0x3C
	real_bounds damage_error; // 0x40
	float base_turning_speed; // 0x48
	real_bounds dynamic_turning_speed; // 0x4C
	float dual_wield_error_acceleration_time; // 0x54
	float dual_wield_error_deceleration_time; // 0x58
	float unknown; // 0x5C
	float unknown2; // 0x60
	float dual_wield_minimum_error; // 0x64
	real_bounds dual_wield_error_angle; // 0x68
	float dual_wield_damage_scale; // 0x70
	c_enum<enum e_weapon_barrel_distribution_function,short> projectile_distribution_function; // 0x74
	short projectiles_per_shot; // 0x76
	float projectile_distribution_angle; // 0x78
	float projectile_minimum_error; // 0x7C
	real_bounds projectile_error_angle; // 0x80
	float reload_penalty; // 0x88
	float switch_penalty; // 0x8C
	float zoom_penalty; // 0x90
	float jump_penalty; // 0x94
	c_tag_block<s_tag_field_definition> firing_penalty_function; // 0x98
	c_tag_block<s_tag_field_definition> firing_crouched_penalty_function; // 0xA4
	c_tag_block<s_tag_field_definition> moving_penalty_function; // 0xB0
	c_tag_block<s_tag_field_definition> turning_penalty_function; // 0xBC
	float error_angle_maximum_rotation; // 0xC8
	c_tag_block<s_tag_field_definition> dual_firing_penalty_function; // 0xCC
	c_tag_block<s_tag_field_definition> dual_firing_crouched_penalty_function; // 0xD8
	c_tag_block<s_tag_field_definition> dual_moving_penalty_function; // 0xE4
	c_tag_block<s_tag_field_definition> dual_turning_penalty_function; // 0xF0
	float dual_error_angle_maximum_rotation; // 0xFC
	c_tag_block<real_vector3d> first_person_offsets; // 0x100
	c_enum<enum e_damage_reporting_type,char> damage_reporting_type; // 0x10C
	char unknown3; // 0x10D
	short unknown4; // 0x10E
	s_tag_reference initial_projectile; // 0x110
	s_tag_reference trailing_projectile; // 0x120
	s_tag_reference damage_effect; // 0x130
	s_tag_reference crate_projectile; // 0x140
	float crate_projectile_speed; // 0x150
	float ejection_port_recovery_time; // 0x154
	float illumination_recovery_time; // 0x158
	float heat_generated_per_round; // 0x15C
	float age_generated_per_round_mp; // 0x160
	float age_generated_per_round_sp; // 0x164
	float overload_time; // 0x168
	real_bounds angle_change_per_shot; // 0x16C
	float angle_change_acceleration_time; // 0x174
	float angle_change_deceleration_time; // 0x178
	c_enum<enum e_weapon_barrel_angle_change_function,short> angle_change_function; // 0x17C
	short unknown5; // 0x17E
	float unknown6; // 0x180
	float unknown7; // 0x184
	float firing_effect_deceleration_time; // 0x188
	unsigned long unknown8; // 0x18C
	float rate_of_fire_acceleration_time; // 0x190
	float rate_of_fire_deceleration_time; // 0x194
	unsigned long unknown9; // 0x198
	float bloom_rate_of_decay; // 0x19C
	c_tag_block<s_weapon_barrel_firing_effect> firing_effects; // 0x1A0
	s_weapon_barrel_definition(s_weapon_barrel_definition &); /* compiler_generated() */
	s_weapon_barrel_definition(s_weapon_barrel_definition const &); /* compiler_generated() */
	s_weapon_barrel_definition(); /* compiler_generated() */
	s_weapon_barrel_definition &operator=(s_weapon_barrel_definition &); /* compiler_generated() */
	s_weapon_barrel_definition &operator=(s_weapon_barrel_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_weapon_barrel_definition) == 428, "Invalid s_weapon_barrel_definition size");

struct s_weapon_first_person_block
{
	s_tag_reference first_person_model; // 0x0
	s_tag_reference first_person_animations; // 0x10
};
static_assert(sizeof(s_weapon_first_person_block) == 32, "Invalid s_weapon_first_person_block size");

#pragma pack(push, 4)
struct s_weapon_magazine_magazine_equipment_block
{
	short rounds0_for_max; // 0x0
	short unknown; // 0x2
	s_tag_reference equipment; // 0x4
};
#pragma pack(pop)
static_assert(sizeof(s_weapon_magazine_magazine_equipment_block) == 20, "Invalid s_weapon_magazine_magazine_equipment_block size");

struct s_weapon_magazine_definition
{
	unsigned long flags; // 0x0
	short rounds_recharged; // 0x4
	short rounds_total_initial; // 0x6
	short rounds_total_maximum; // 0x8
	short rounds_total_loaded_maximum; // 0xA
	short maximum_rounds_held; // 0xC
	short unknown; // 0xE
	float reload_time; // 0x10
	short rounds_reloaded; // 0x14
	short unknown2; // 0x16
	float chamber_time; // 0x18
	unsigned long unknown3; // 0x1C
	unsigned long unknown4; // 0x20
	unsigned long unknown5; // 0x24
	unsigned long unknown6; // 0x28
	unsigned long unknown7; // 0x2C
	unsigned long unknown8; // 0x30
	s_tag_reference reloading_effect; // 0x34
	s_tag_reference reloading_damage_effect; // 0x44
	s_tag_reference chambering_effect; // 0x54
	s_tag_reference chambering_damage_effect; // 0x64
	c_tag_block<s_weapon_magazine_magazine_equipment_block> magazine_equipment; // 0x74
};
static_assert(sizeof(s_weapon_magazine_definition) == 128, "Invalid s_weapon_magazine_definition size");

struct s_weapon_trigger_definition
{
	unsigned long flags; // 0x0
	c_enum<enum e_weapon_trigger_button_used,short> button_used; // 0x4
	c_enum<enum e_weapon_trigger_behavior,short> behavior; // 0x6
	short primary_barrel; // 0x8
	short secondary_barrel; // 0xA
	c_enum<enum e_weapon_trigger_prediction,short> prediction; // 0xC
	short unknown; // 0xE
	float autofire_time; // 0x10
	float autofire_throw; // 0x14
	c_enum<enum e_weapon_trigger_secondary_action,short> secondary_action; // 0x18
	c_enum<enum e_weapon_trigger_primary_action,short> primary_action; // 0x1A
	float charging_time; // 0x1C
	float charged_time; // 0x20
	c_enum<enum e_weapon_trigger_overcharge_action,short> overcharge_action; // 0x24
	unsigned short charge_flags; // 0x26
	float charged_illumination; // 0x28
	float spew_time; // 0x2C
	s_tag_reference charging_effect; // 0x30
	s_tag_reference charging_damage_effect; // 0x40
	s_tag_reference charging_response; // 0x50
	float charging_age_degeneration; // 0x60
	s_tag_reference unknown2; // 0x64
	s_tag_reference unknown3; // 0x74
	unsigned long unknown4; // 0x84
	unsigned long unknown5; // 0x88
	unsigned long unknown6; // 0x8C
	s_weapon_trigger_definition(s_weapon_trigger_definition &); /* compiler_generated() */
	s_weapon_trigger_definition(s_weapon_trigger_definition const &); /* compiler_generated() */
	s_weapon_trigger_definition(); /* compiler_generated() */
	s_weapon_trigger_definition &operator=(s_weapon_trigger_definition &); /* compiler_generated() */
	s_weapon_trigger_definition &operator=(s_weapon_trigger_definition const &); /* compiler_generated() */
};
static_assert(sizeof(s_weapon_trigger_definition) == 144, "Invalid s_weapon_trigger_definition size");

struct s_weapon_definition :
	public s_item_definition
{
	c_flags<enum e_weapon_definition_flags,unsigned long> weapon_flags; // 0x1D4
	unsigned long more_flags; // 0x1D8
	unsigned long unknown8; // 0x1DC
	c_enum<enum e_weapon_secondary_trigger_mode,short> secondary_trigger_mode; // 0x1E0
	short maximum_alternate_shots_loaded; // 0x1E2
	float turn_on_time; // 0x1E4
	float ready_time; // 0x1E8
	s_tag_reference ready_effect; // 0x1EC
	s_tag_reference ready_damage_effect; // 0x1FC
	float heat_recovery_threshold; // 0x20C
	float overheated_threshold; // 0x210
	float heat_detonation_threshold; // 0x214
	float heat_detonation_fraction; // 0x218
	float heat_loss_per_second; // 0x21C
	float heat_illumination; // 0x220
	float overheated_heat_loss_per_second; // 0x224
	s_tag_reference overheated; // 0x228
	s_tag_reference overheated_damage_effect; // 0x238
	s_tag_reference detonation; // 0x248
	s_tag_reference detonation_damage_effect2; // 0x258
	s_tag_reference player_melee_damage; // 0x268
	s_tag_reference player_melee_response; // 0x278
	float damage_pyramid_angles_y; // 0x288
	float damage_pyramid_angles_p; // 0x28C
	float damage_pyramid_depth; // 0x290
	s_tag_reference first_hit_damage; // 0x294
	s_tag_reference first_hit_response; // 0x2A4
	s_tag_reference second_hit_damage; // 0x2B4
	s_tag_reference second_hit_response; // 0x2C4
	s_tag_reference third_hit_damage; // 0x2D4
	s_tag_reference third_hit_response; // 0x2E4
	s_tag_reference lunge_melee_damage; // 0x2F4
	s_tag_reference lunge_melee_response; // 0x304
	s_tag_reference gun_gun_clang_damage; // 0x314
	s_tag_reference gun_gun_clang_response; // 0x324
	s_tag_reference gun_sword_clang_damage; // 0x334
	s_tag_reference gun_sword_clang_response; // 0x344
	s_tag_reference clash_effect; // 0x354
	c_enum<enum e_damage_reporting_type,char> melee_damage_reporting_type; // 0x364
	char unknown9; // 0x365
	short magnification_levels; // 0x366
	real_bounds magnification_bounds; // 0x368
	unsigned long magnification_flags; // 0x370
	float weapon_switch_ready_speed0_default; // 0x374
	float autoaim_angle; // 0x378
	float autoaim_range_long; // 0x37C
	float autoaim_range_short; // 0x380
	float autoaim_safe_radius; // 0x384
	float magnetism_angle; // 0x388
	float magnetism_range_long; // 0x38C
	float magnetism_range_short; // 0x390
	float magnetism_safe_radius; // 0x394
	float deviation_angle; // 0x398
	unsigned long unknown10; // 0x39C
	unsigned long unknown11; // 0x3A0
	unsigned long unknown12; // 0x3A4
	unsigned long unknown13; // 0x3A8
	unsigned long unknown14; // 0x3AC
	unsigned long unknown15; // 0x3B0
	c_tag_block<s_unit_target_tracking_block> target_tracking; // 0x3B4
	unsigned long unknown16; // 0x3C0
	unsigned long unknown17; // 0x3C4
	unsigned long unknown18; // 0x3C8
	unsigned long unknown19; // 0x3CC
	c_enum<enum e_weapon_movement_penalized,short> movement_penalized; // 0x3D0
	short unknown20; // 0x3D2
	float forwards_movement_penalty; // 0x3D4
	float sideways_movement_penalty; // 0x3D8
	float ai_scariness; // 0x3DC
	float weapon_power_on_time; // 0x3E0
	float weapon_power_off_time; // 0x3E4
	s_tag_reference weapon_power_on_effect; // 0x3E8
	s_tag_reference weapon_power_off_effect; // 0x3F8
	float age_heat_recovery_penalty; // 0x408
	float age_rate_of_fire_penalty; // 0x40C
	float age_misfire_start; // 0x410
	float age_misfire_chance; // 0x414
	s_tag_reference pickup_sound; // 0x418
	s_tag_reference zoom_in_sound; // 0x428
	s_tag_reference zoom_out_sound; // 0x438
	float active_camo_ding; // 0x448
	float camo_regrowth_rate; // 0x44C
	unsigned long unknown22; // 0x450
	unsigned long unknown23; // 0x454
	unsigned long weapon_class; // 0x458
	unsigned long weapon_name; // 0x45C
	c_enum<enum e_weapon_multiplayer_weapon_type,short> multiplayer_weapon_type; // 0x460
	c_enum<enum e_weapon_weapon_type,short> weapon_type; // 0x462
	c_enum<enum e_weapon_tracking_type,short> tracking; // 0x464
	short unknown_enum; // 0x466
	c_enum<enum e_weapon_special_hud_version_value,long> special_hud_version; // 0x468
	long special_hud_icon; // 0x46C
	c_tag_block<s_weapon_first_person_block> first_person; // 0x470
	s_tag_reference hud_interface; // 0x47C
	c_tag_block<s_game_object_predicted_resource> predicted_weapon_resources; // 0x48C
	c_tag_block<s_weapon_magazine_definition> magazines; // 0x498
	c_tag_block<s_weapon_trigger_definition> triggers; // 0x4A4
	c_tag_block<s_weapon_barrel_definition> barrels; // 0x4B0
	float unknown25; // 0x4BC
	float unknown26; // 0x4C0
	float maximum_movement_acceleration; // 0x4C4
	float maximum_movement_velocity; // 0x4C8
	float maximum_turning_acceleration; // 0x4CC
	float maximum_turning_velocity; // 0x4D0
	s_tag_reference deployed_vehicle; // 0x4D4
	s_tag_reference deployed_weapon; // 0x4E4
	s_tag_reference age_model; // 0x4F4
	s_tag_reference age_weapon; // 0x504
	s_tag_reference aged_material_effects; // 0x514
	float hammer_age_per_use; // 0x524
	unsigned long unknown_sword_age_per_use; // 0x528
	real_vector3d first_person_weapon_offset; // 0x52C
	real_vector2d first_person_scope_size; // 0x538
	real_bounds third_person_pitch_bounds; // 0x540
	float zoom_transition_time; // 0x548
	float melee_weapon_delay; // 0x54C
	float ready_animation_duration; // 0x550
	unsigned long weapon_holster_marker; // 0x554
	real_vector3d centered_first_person_weapon_offset; // 0x558
	unsigned long weapon_type_name; // 0x564
	s_weapon_definition(s_weapon_definition &); /* compiler_generated() */
	s_weapon_definition(s_weapon_definition const &); /* compiler_generated() */
	s_weapon_definition(); /* compiler_generated() */
	s_weapon_definition &operator=(s_weapon_definition &); /* compiler_generated() */
	s_weapon_definition &operator=(s_weapon_definition const &); /* compiler_generated() */
};
static_assert(sizeof(s_weapon_definition) == 1384, "Invalid s_weapon_definition size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_ITEMS_WEAPON_DEFINITIONS_HPP__
