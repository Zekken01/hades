#ifndef __BLAM_ITEMS_EQUIPMENT_DEFINITIONS_HPP__
#define __BLAM_ITEMS_EQUIPMENT_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/item_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

struct real_bounds;
struct s_equipment_adrenaline_block;
struct s_equipment_ammo_pack_block;
struct s_equipment_ammo_pack_block_weapon;
struct s_equipment_armor_lock_block;
struct s_equipment_bomb_run_block;
struct s_equipment_concussive_blast_block;
struct s_equipment_definition;
struct s_equipment_forced_reload_block;
struct s_equipment_health_pack_block;
struct s_equipment_hologram_block;
struct s_equipment_invincibility_block;
struct s_equipment_invisibility_block;
struct s_equipment_lightning_strike_block;
struct s_equipment_mag_pulse_block;
struct s_equipment_motion_tracker_noise_block;
struct s_equipment_multiplayer_powerup_block;
struct s_equipment_optional_unit_camera_block;
struct s_equipment_optional_unit_camera_block_camera_acceleration_block;
struct s_equipment_optional_unit_camera_block_camera_track;
struct s_equipment_proximity_mine_block;
struct s_equipment_reactive_armor_block;
struct s_equipment_regenerator_block;
struct s_equipment_scrambler_block;
struct s_equipment_spawner_block;
struct s_equipment_super_shield_block;
struct s_equipment_tank_mode_block;
struct s_equipment_vision_block;
struct s_equipment_weapon_jammer_block;
struct s_item_definition;
struct s_tag_data;
struct s_tag_reference;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_equipment_adrenaline_block
{
	float unknown; // 0x0
	s_tag_reference activation_effect; // 0x4
	s_tag_reference unknown3; // 0x14
};
#pragma pack(pop)
static_assert(sizeof(s_equipment_adrenaline_block) == 36, "Invalid s_equipment_adrenaline_block size");

struct s_equipment_ammo_pack_block_weapon
{
	unsigned long name; // 0x0
	s_tag_reference weapon_object; // 0x4
	long unknown; // 0x14
};
static_assert(sizeof(s_equipment_ammo_pack_block_weapon) == 24, "Invalid s_equipment_ammo_pack_block_weapon size");

#pragma pack(push, 4)
struct s_equipment_ammo_pack_block
{
	unsigned long unknown; // 0x0
	long unknown2; // 0x4
	long unknown3; // 0x8
	unsigned long unknown4; // 0xC
	long unknown5; // 0x10
	long unknown6; // 0x14
	c_tag_block<s_equipment_ammo_pack_block_weapon> weapons; // 0x18
	s_tag_reference unknown7; // 0x24
};
#pragma pack(pop)
static_assert(sizeof(s_equipment_ammo_pack_block) == 52, "Invalid s_equipment_ammo_pack_block size");

struct s_equipment_armor_lock_block
{
	s_tag_reference collision_damage; // 0x0
	s_tag_reference unknown_collision_damage; // 0x10
};
static_assert(sizeof(s_equipment_armor_lock_block) == 32, "Invalid s_equipment_armor_lock_block size");

#pragma pack(push, 4)
struct s_equipment_bomb_run_block
{
	long unknown; // 0x0
	unsigned long unknown2; // 0x4
	unsigned long unknown3; // 0x8
	unsigned long unknown4; // 0xC
	unsigned long unknown5; // 0x10
	s_tag_reference projectile; // 0x14
	s_tag_reference throw_sound; // 0x24
};
#pragma pack(pop)
static_assert(sizeof(s_equipment_bomb_run_block) == 52, "Invalid s_equipment_bomb_run_block size");

struct s_equipment_concussive_blast_block
{
	s_tag_reference unknown; // 0x0
	s_tag_reference unknown2; // 0x10
};
static_assert(sizeof(s_equipment_concussive_blast_block) == 32, "Invalid s_equipment_concussive_blast_block size");

#pragma pack(push, 4)
struct s_equipment_forced_reload_block
{
	s_tag_reference effect; // 0x0
	unsigned long unknown; // 0x10
};
#pragma pack(pop)
static_assert(sizeof(s_equipment_forced_reload_block) == 20, "Invalid s_equipment_forced_reload_block size");

struct s_equipment_health_pack_block
{
	float health_amount; // 0x0
	float shield_amount; // 0x4
};
static_assert(sizeof(s_equipment_health_pack_block) == 8, "Invalid s_equipment_health_pack_block size");

#pragma pack(push, 4)
struct s_equipment_hologram_block
{
	unsigned long unknown; // 0x0
	s_tag_reference active_effect; // 0x4
	s_tag_reference unknown2; // 0x14
	unsigned long unknown3; // 0x24
	unsigned long unknown4; // 0x28
	unsigned long unknown5; // 0x2C
	s_tag_reference death_effect; // 0x30
	unsigned long unknown6; // 0x40
	unsigned long unknown7; // 0x44
	s_tag_data function; // 0x48
	s_tag_reference nav_point_hud; // 0x5C
	s_equipment_hologram_block(s_equipment_hologram_block &); /* compiler_generated() */
	s_equipment_hologram_block(s_equipment_hologram_block const &); /* compiler_generated() */
	s_equipment_hologram_block(); /* compiler_generated() */
	s_equipment_hologram_block &operator=(s_equipment_hologram_block &); /* compiler_generated() */
	s_equipment_hologram_block &operator=(s_equipment_hologram_block const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_equipment_hologram_block) == 108, "Invalid s_equipment_hologram_block size");

#pragma pack(push, 4)
struct s_equipment_invincibility_block
{
	unsigned long new_player_material; // 0x0
	short new_player_material_global_index; // 0x4
	short unknown; // 0x6
	float unknown2; // 0x8
	s_tag_reference activation_effect; // 0xC
	s_tag_reference active_effect; // 0x1C
};
#pragma pack(pop)
static_assert(sizeof(s_equipment_invincibility_block) == 44, "Invalid s_equipment_invincibility_block size");

struct s_equipment_invisibility_block
{
	float invisibility_duration; // 0x0
	float invisibility_fade_time; // 0x4
};
static_assert(sizeof(s_equipment_invisibility_block) == 8, "Invalid s_equipment_invisibility_block size");

#pragma pack(push, 4)
struct s_equipment_lightning_strike_block
{
	unsigned long melee_time_reduction; // 0x0
	s_tag_reference unknown_effect; // 0x4
};
#pragma pack(pop)
static_assert(sizeof(s_equipment_lightning_strike_block) == 20, "Invalid s_equipment_lightning_strike_block size");

#pragma pack(push, 4)
struct s_equipment_mag_pulse_block
{
	s_tag_reference unknown; // 0x0
	s_tag_reference unknown2; // 0x10
	s_tag_reference unknown3; // 0x20
	unsigned long unknown4; // 0x30
};
#pragma pack(pop)
static_assert(sizeof(s_equipment_mag_pulse_block) == 52, "Invalid s_equipment_mag_pulse_block size");

struct s_equipment_motion_tracker_noise_block
{
	float arm_time; // 0x0
	float noise_radius; // 0x4
	long noise_count; // 0x8
	float flash_radius; // 0xC
};
static_assert(sizeof(s_equipment_motion_tracker_noise_block) == 16, "Invalid s_equipment_motion_tracker_noise_block size");

struct s_equipment_multiplayer_powerup_block
{
	c_enum<enum e_equipment_multiplayer_powerup_block_flavor,long> flavor; // 0x0
	s_equipment_multiplayer_powerup_block(s_equipment_multiplayer_powerup_block &); /* compiler_generated() */
	s_equipment_multiplayer_powerup_block(s_equipment_multiplayer_powerup_block const &); /* compiler_generated() */
	s_equipment_multiplayer_powerup_block(); /* compiler_generated() */
	s_equipment_multiplayer_powerup_block &operator=(s_equipment_multiplayer_powerup_block &); /* compiler_generated() */
	s_equipment_multiplayer_powerup_block &operator=(s_equipment_multiplayer_powerup_block const &); /* compiler_generated() */
};
static_assert(sizeof(s_equipment_multiplayer_powerup_block) == 4, "Invalid s_equipment_multiplayer_powerup_block size");

struct s_equipment_optional_unit_camera_block_camera_acceleration_block
{
	unsigned long unknown; // 0x0
	unsigned long unknown2; // 0x4
	unsigned long unknown3; // 0x8
	unsigned long unknown4; // 0xC
	unsigned long unknown5; // 0x10
	unsigned long unknown6; // 0x14
	unsigned long unknown7; // 0x18
	unsigned long unknown8; // 0x1C
	unsigned long unknown9; // 0x20
	unsigned long unknown10; // 0x24
	unsigned long unknown11; // 0x28
	unsigned long unknown12; // 0x2C
	unsigned long unknown13; // 0x30
	unsigned long unknown14; // 0x34
	unsigned long unknown15; // 0x38
	unsigned long unknown16; // 0x3C
	unsigned long unknown17; // 0x40
	unsigned long unknown18; // 0x44
	unsigned long unknown19; // 0x48
};
static_assert(sizeof(s_equipment_optional_unit_camera_block_camera_acceleration_block) == 76, "Invalid s_equipment_optional_unit_camera_block_camera_acceleration_block size");

struct s_equipment_optional_unit_camera_block_camera_track
{
	s_tag_reference track; // 0x0
};
static_assert(sizeof(s_equipment_optional_unit_camera_block_camera_track) == 16, "Invalid s_equipment_optional_unit_camera_block_camera_track size");

#pragma pack(push, 4)
struct s_equipment_optional_unit_camera_block
{
	c_flags<enum e_equipment_optional_unit_camera_block_flag_bits,unsigned short> flags; // 0x0
	unsigned char unused[2]; // 0x2
	unsigned long camera_marker_name; // 0x4
	unsigned long camera_submerged_marker_name; // 0x8
	float pitch_auto_level; // 0xC
	real_bounds pitch_range; // 0x10
	c_tag_block<s_equipment_optional_unit_camera_block_camera_track> camera_tracks; // 0x18
	float unknown2; // 0x24
	float unknown3; // 0x28
	float unknown4; // 0x2C
	c_tag_block<s_equipment_optional_unit_camera_block_camera_acceleration_block> camera_acceleration; // 0x30
	s_equipment_optional_unit_camera_block(s_equipment_optional_unit_camera_block &); /* compiler_generated() */
	s_equipment_optional_unit_camera_block(s_equipment_optional_unit_camera_block const &); /* compiler_generated() */
	s_equipment_optional_unit_camera_block(); /* compiler_generated() */
	s_equipment_optional_unit_camera_block &operator=(s_equipment_optional_unit_camera_block &); /* compiler_generated() */
	s_equipment_optional_unit_camera_block &operator=(s_equipment_optional_unit_camera_block const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_equipment_optional_unit_camera_block) == 60, "Invalid s_equipment_optional_unit_camera_block size");

struct s_equipment_proximity_mine_block
{
	s_tag_reference explosion_effect; // 0x0
	s_tag_reference explosion_damage_effect; // 0x10
	float arm_time; // 0x20
	float self_destruct_time; // 0x24
	float trigger_time; // 0x28
	float trigger_velocity; // 0x2C
};
static_assert(sizeof(s_equipment_proximity_mine_block) == 48, "Invalid s_equipment_proximity_mine_block size");

#pragma pack(push, 4)
struct s_equipment_reactive_armor_block
{
	unsigned long unknown; // 0x0
	unsigned long unknown2; // 0x4
	unsigned long unknown3; // 0x8
	s_tag_reference unknown4; // 0xC
	s_tag_reference unknown5; // 0x1C
	s_tag_reference unknown6; // 0x2C
	s_tag_reference unknown7; // 0x3C
};
#pragma pack(pop)
static_assert(sizeof(s_equipment_reactive_armor_block) == 76, "Invalid s_equipment_reactive_armor_block size");

struct s_equipment_regenerator_block
{
	s_tag_reference regenerating_effect; // 0x0
};
static_assert(sizeof(s_equipment_regenerator_block) == 16, "Invalid s_equipment_regenerator_block size");

#pragma pack(push, 4)
struct s_equipment_spawner_block
{
	s_tag_reference spawned_object; // 0x0
	s_tag_reference spawned_effect; // 0x10
	float spawn_radius; // 0x20
	float spawn_z_offset; // 0x24
	float spawn_area_radius; // 0x28
	float spawn_velocity; // 0x2C
	c_enum<enum e_equipment_spawner_block_type,short> type; // 0x30
	unsigned char unused[2]; // 0x32
	s_equipment_spawner_block(s_equipment_spawner_block &); /* compiler_generated() */
	s_equipment_spawner_block(s_equipment_spawner_block const &); /* compiler_generated() */
	s_equipment_spawner_block(); /* compiler_generated() */
	s_equipment_spawner_block &operator=(s_equipment_spawner_block &); /* compiler_generated() */
	s_equipment_spawner_block &operator=(s_equipment_spawner_block const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_equipment_spawner_block) == 52, "Invalid s_equipment_spawner_block size");

#pragma pack(push, 4)
struct s_equipment_super_shield_block
{
	unsigned long unknown; // 0x0
	unsigned long unknown2; // 0x4
	float shields_given; // 0x8
	s_tag_reference unknown3; // 0xC
	s_tag_reference unknown4; // 0x1C
	s_tag_reference unknown5; // 0x2C
};
#pragma pack(pop)
static_assert(sizeof(s_equipment_super_shield_block) == 60, "Invalid s_equipment_super_shield_block size");

struct s_equipment_tank_mode_block
{
	unsigned long new_player_material; // 0x0
	unsigned long unknown; // 0x4
	unsigned long unknown2; // 0x8
	unsigned long unknown3; // 0xC
	unsigned long unknown4; // 0x10
	unsigned long unknown5; // 0x14
	s_tag_reference active_hud; // 0x18
};
static_assert(sizeof(s_equipment_tank_mode_block) == 40, "Invalid s_equipment_tank_mode_block size");

struct s_equipment_vision_block
{
	s_tag_reference screen_effect; // 0x0
	s_tag_reference damage_response; // 0x10
};
static_assert(sizeof(s_equipment_vision_block) == 32, "Invalid s_equipment_vision_block size");

#pragma pack(push, 4)
struct s_equipment_weapon_jammer_block
{
	unsigned long unknown; // 0x0
	s_tag_reference unknown2; // 0x4
	long unknown3; // 0x14
	long unknown4; // 0x18
	long unknown5; // 0x1C
	long unknown6; // 0x20
};
#pragma pack(pop)
static_assert(sizeof(s_equipment_weapon_jammer_block) == 36, "Invalid s_equipment_weapon_jammer_block size");

#pragma pack(push, 4)
struct s_equipment_definition :
	public s_item_definition
{
	float use_duration; // 0x1D4
	float activation_delay; // 0x1D8
	short number_of_uses; // 0x1DC
	c_flags<enum e_equipment_equipment_flag_bits,unsigned short> equipment_flags; // 0x1DE
	float unknown9; // 0x1E0
	float unknown10; // 0x1E4
	float unknown11; // 0x1E8
	c_tag_block<s_equipment_optional_unit_camera_block> override_camera; // 0x1EC
	c_tag_block<s_equipment_super_shield_block> super_shield; // 0x1F8
	c_tag_block<s_equipment_multiplayer_powerup_block> multiplayer_powerup; // 0x204
	c_tag_block<s_equipment_spawner_block> spawner; // 0x210
	c_tag_block<s_equipment_proximity_mine_block> proximity_mine; // 0x21C
	c_tag_block<s_equipment_motion_tracker_noise_block> motion_tracker_noise; // 0x228
	unsigned char unused[12]; // 0x234
	c_tag_block<s_equipment_invisibility_block> invisibility; // 0x240
	c_tag_block<s_equipment_invincibility_block> invincibility; // 0x24C
	c_tag_block<s_equipment_regenerator_block> regenerator; // 0x258
	c_tag_block<s_equipment_health_pack_block> health_pack; // 0x264
	c_tag_block<s_equipment_forced_reload_block> forced_reload; // 0x270
	c_tag_block<s_equipment_concussive_blast_block> concussive_blast; // 0x27C
	c_tag_block<s_equipment_tank_mode_block> tank_mode; // 0x288
	c_tag_block<s_equipment_mag_pulse_block> mag_pulse; // 0x294
	c_tag_block<s_equipment_hologram_block> hologram; // 0x2A0
	c_tag_block<s_equipment_reactive_armor_block> reactive_armor; // 0x2AC
	c_tag_block<s_equipment_bomb_run_block> bomb_run; // 0x2B8
	c_tag_block<s_equipment_armor_lock_block> armor_lock; // 0x2C4
	c_tag_block<s_equipment_adrenaline_block> adrenaline; // 0x2D0
	c_tag_block<s_equipment_lightning_strike_block> lightning_strike; // 0x2DC
	c_tag_block<s_equipment_scrambler_block> scrambler; // 0x2E8
	c_tag_block<s_equipment_weapon_jammer_block> weapon_jammer; // 0x2F4
	c_tag_block<s_equipment_ammo_pack_block> ammo_pack; // 0x300
	c_tag_block<s_equipment_vision_block> vision; // 0x30C
	s_tag_reference hud_interface; // 0x318
	s_tag_reference pickup_sound; // 0x328
	s_tag_reference empty_sound; // 0x338
	s_tag_reference activation_effect; // 0x348
	s_tag_reference active_effect; // 0x358
	s_tag_reference deactivation_effect; // 0x368
	unsigned long enter_animation; // 0x378
	unsigned long idle_animation; // 0x37C
	unsigned long exit_animation; // 0x380
	s_equipment_definition(s_equipment_definition &); /* compiler_generated() */
	s_equipment_definition(s_equipment_definition const &); /* compiler_generated() */
	s_equipment_definition(); /* compiler_generated() */
	s_equipment_definition &operator=(s_equipment_definition &); /* compiler_generated() */
	s_equipment_definition &operator=(s_equipment_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_equipment_definition) == 900, "Invalid s_equipment_definition size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_ITEMS_EQUIPMENT_DEFINITIONS_HPP__
