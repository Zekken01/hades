#ifndef __BLAM_INTERFACE_CHUD_CHUD_GLOBALS_HPP__
#define __BLAM_INTERFACE_CHUD_CHUD_GLOBALS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct real_point2d;
struct real_vector2d;
struct s_chud_globals_attributes;
struct s_chud_globals_definition;
struct s_chud_per_character_globals;
struct s_chud_player_training_definition;
struct s_chud_shaders;
struct s_chud_sound;
struct s_tag_block;
struct s_tag_data;
struct s_tag_reference;

/* ---------- constants */

/* ---------- definitions */

struct s_chud_globals_attributes
{
	c_flags<enum e_chud_resolution_flags,unsigned char> resolution_flags; // 0x0
	float warp_angle; // 0x4
	float warp_amount; // 0x8
	float warp_direction; // 0xC
	__int32 virtual_width; // 0x10
	__int32 virtual_height; // 0x14
	real_point2d sensor_origin; // 0x18
	float sensor_radius; // 0x20
	float blip_radius; // 0x24
	float global_safe_frame_horiz; // 0x28
	float global_safe_frame_vert; // 0x2C
	float safe_frame_horizontal_ding; // 0x30
	float safe_frame_vertical_ding; // 0x34
	s_tag_reference first_person_unknown_reference; // 0x38
	s_tag_reference third_person_unknown_reference; // 0x48
	s_tag_reference first_person_damage_border; // 0x58
	s_tag_reference third_person_damage_border; // 0x68
	float field_78; // 0x78
	real_vector2d state_message_offset; // 0x7C
	float field_84; // 0x84
	float unknown_scale; // 0x88
	real_point2d unknown_offset; // 0x8C
	float bottom_state_v_offset; // 0x94
	float bottom_primary_v_offset; // 0x98
	float medal_scale; // 0x9C
	float medal_width; // 0xA0
	real_point2d survival_medals_offset; // 0xA4
	float medal_unknown; // 0xAC
	real_point2d multiplayer_medals_offset; // 0xB0
	float message_scale; // 0xB8
	float message_height; // 0xBC
	float field_C0; // 0xC0
	real_point2d message_offset; // 0xC4
	real_point2d unknown_message_offset; // 0xCC
	float field_D4; // 0xD4
	real_point2d unknown_achor_offset; // 0xD8
	real_point2d prompt_achor_offset; // 0xE0
	s_chud_globals_attributes(s_chud_globals_attributes &); /* compiler_generated() */
	s_chud_globals_attributes(s_chud_globals_attributes const &); /* compiler_generated() */
	s_chud_globals_attributes(); /* compiler_generated() */
	s_chud_globals_attributes &operator=(s_chud_globals_attributes &); /* compiler_generated() */
	s_chud_globals_attributes &operator=(s_chud_globals_attributes const &); /* compiler_generated() */
};
static_assert(sizeof(s_chud_globals_attributes) == 232, "Invalid s_chud_globals_attributes size");
static_assert(offsetof(s_chud_globals_attributes, warp_angle) == 0x4, "s_chud_globals_attributes::warp_angle moved when its reconstructed padding was removed");

#pragma pack(push, 4)
struct s_chud_sound
{
	c_flags<enum e_chud_sound_flags,unsigned long> sound_flags; // 0x0
	float scale; // 0x4
	s_tag_block unknown; // 0x8
	s_chud_sound(s_chud_sound &); /* compiler_generated() */
	s_chud_sound(s_chud_sound const &); /* compiler_generated() */
	s_chud_sound(); /* compiler_generated() */
	s_chud_sound &operator=(s_chud_sound &); /* compiler_generated() */
	s_chud_sound &operator=(s_chud_sound const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_chud_sound) == 20, "Invalid s_chud_sound size");

struct s_chud_shaders
{
	s_tag_reference vertex_shader; // 0x0
	s_tag_reference pixel_shader; // 0x10
};
static_assert(sizeof(s_chud_shaders) == 32, "Invalid s_chud_shaders size");

struct s_chud_per_character_globals
{
	c_enum<enum e_chud_character_type,unsigned char> character_type; // 0x0
	s_static_array<unsigned long,37> colors; // 0x4
	c_tag_block<s_chud_globals_attributes> attributes; // 0x98
	c_tag_block<s_chud_sound> sounds; // 0xA4
	s_tag_reference field_B0; // 0xB0
	s_tag_reference frag_grenade_swap_sound; // 0xC0
	s_tag_reference plasma_grenade_swap_sound; // 0xD0
	s_tag_reference spike_grenade_swap_sound; // 0xE0
	s_tag_reference fire_grenade_swap_sound; // 0xF0
	s_tag_reference damage_microtexture; // 0x100
	s_tag_reference damage_noise; // 0x110
	s_tag_reference directional_arrow; // 0x120
	s_tag_reference field_130; // 0x130
	s_tag_reference field_140; // 0x140
	float field_150; // 0x150
	long field_158; // 0x154
	long field_15C; // 0x158
	long field_160; // 0x15C
	long field_164; // 0x160
	long field_168; // 0x164
	s_tag_reference waypoints; // 0x168
	s_tag_reference field_188; // 0x178
	s_tag_reference scooreboard_hud; // 0x188
	s_tag_reference metagame_scoreboard_hud; // 0x198
	s_tag_reference survival_hud; // 0x1A8
	s_tag_reference field_1B8; // 0x1B8
	s_tag_reference theater_hud; // 0x1C8
	s_tag_reference forge_hud; // 0x1D8
	s_tag_reference hud_strings; // 0x1E8
	s_tag_reference medals_bitmap; // 0x1F8
	c_tag_block<unsigned long> multiplayer_medals; // 0x208
	s_tag_reference medal_hud_animation1; // 0x214
	s_tag_reference medal_hud_animation2; // 0x224
	s_tag_reference cortana_channel_bitmap; // 0x234
	s_tag_reference field_244; // 0x244
	s_tag_reference field_254; // 0x254
	s_tag_reference field_264; // 0x264
	s_tag_reference field_274; // 0x274
	long field_284; // 0x284
	long field_288; // 0x288
	float grenade_scematc_spacing; // 0x28C
	float equipment_scematic_offset_y; // 0x290
	float dual_equipment_scematic_offset; // 0x294
	float field_298; // 0x298
	float field_29C; // 0x29C
	float scoreboard_leader_offset_y; // 0x2A0
	float waypoint_minimum_distance_scale; // 0x2A4
	float waypoint_maximum_distance_scale; // 0x2A8
	float waypoint_arrrow_scale; // 0x2AC
	s_chud_per_character_globals(s_chud_per_character_globals &); /* compiler_generated() */
	s_chud_per_character_globals(s_chud_per_character_globals const &); /* compiler_generated() */
	s_chud_per_character_globals(); /* compiler_generated() */
	s_chud_per_character_globals &operator=(s_chud_per_character_globals &); /* compiler_generated() */
	s_chud_per_character_globals &operator=(s_chud_per_character_globals const &); /* compiler_generated() */
};
static_assert(sizeof(s_chud_per_character_globals) == 688, "Invalid s_chud_per_character_globals size");
static_assert(offsetof(s_chud_per_character_globals, colors) == 0x4, "s_chud_per_character_globals::colors moved when its reconstructed padding was removed");

struct s_chud_player_training_definition
{
	unsigned long display_string; // 0x0
	short max_display_time; // 0x4
	short display_count; // 0x6
	short disappear_delay; // 0x8
	short dedisplay_delay; // 0xA
	float display_delay; // 0xC
	c_flags<enum e_chud_player_training_flags,unsigned char> flags; // 0x10
	s_chud_player_training_definition(s_chud_player_training_definition &); /* compiler_generated() */
	s_chud_player_training_definition(s_chud_player_training_definition const &); /* compiler_generated() */
	s_chud_player_training_definition(); /* compiler_generated() */
	s_chud_player_training_definition &operator=(s_chud_player_training_definition &); /* compiler_generated() */
	s_chud_player_training_definition &operator=(s_chud_player_training_definition const &); /* compiler_generated() */
};
static_assert(sizeof(s_chud_player_training_definition) == 20, "Invalid s_chud_player_training_definition size");

struct s_chud_globals_definition
{
	c_tag_block<s_chud_per_character_globals> character_globals; // 0x0
	c_tag_block<s_chud_shaders> shaders; // 0xC
	s_tag_block field_18; // 0x18
	s_tag_block field_24; // 0x24
	c_tag_block<s_chud_player_training_definition> player_training; // 0x30
	s_tag_reference start_menu_emblems; // 0x3C
	s_tag_reference campaign_medals; // 0x4C
	s_tag_reference campaign_medal_hud_animation; // 0x5C
	unsigned char __pad0[4]; // 0x6C
	float campaign_medal_scale; // 0x70
	float campaign_medal_spacing; // 0x74
	float campaign_medal_offset_x; // 0x78
	float campaign_medal_offset_y; // 0x7C
	float metagame_scoreboard_top_y; // 0x80
	float metagame_scoreboard_spacing; // 0x84
	s_tag_reference unit_damage_grid; // 0x88
	float micro_texture_tile_amount; // 0x98
	float medium_sensor_blip_scale; // 0x9C
	float small_sensor_blip_scale; // 0xA0
	float large_sensor_blip_scale; // 0xA4
	float sensor_blip_glow_amount; // 0xA8
	float sensor_blip_glow_radius; // 0xAC
	float sensor_blip_glow_opacity; // 0xB0
	s_tag_reference motion_sensor_blip; // 0xB4
	s_tag_reference birthday_party_effect; // 0xC4
	s_tag_reference campaign_flood_mask; // 0xD4
	s_tag_reference campaign_flood_tile; // 0xE4
	float field_F4; // 0xF4
	float shield_minor_threshold; // 0xF8
	float shield_major_threshold; // 0xFC
	float shield_critical_threshold; // 0x100
	float health_minor_threshold; // 0x104
	float health_major_threshold; // 0x108
	float health_critical_threshold; // 0x10C
	unsigned char __pad1[64]; // 0x110
	s_tag_data field_150; // 0x150
	unsigned char __pad2[84]; // 0x164
	float sprint_fov_multiplier; // 0x1B8
	float sprint_fov_transition_in_time; // 0x1BC
	float sprint_fov_transition_out_time; // 0x1C0
	s_tag_reference parallax_data; // 0x1C4
	unsigned char __pad3[4]; // 0x1D4
	s_tag_data field_1D4; // 0x1D8
	s_tag_data field_1EC; // 0x1EC
	s_tag_data field_200; // 0x200
	s_tag_data field_214; // 0x214
	s_tag_data field_228; // 0x228
	long field_23C; // 0x23C
	s_tag_data field_240; // 0x240
	s_tag_data field_254; // 0x254
	s_tag_data field_268; // 0x268
	s_tag_data field_27C; // 0x27C
	s_tag_data field_290; // 0x290
	s_tag_reference field_2A4; // 0x2A4
	long field_2B4; // 0x2B4
	long field_2B8; // 0x2B8
	long field_2BC; // 0x2BC
	s_chud_globals_definition(s_chud_globals_definition &); /* compiler_generated() */
	s_chud_globals_definition(s_chud_globals_definition const &); /* compiler_generated() */
	s_chud_globals_definition(); /* compiler_generated() */
	s_chud_globals_definition &operator=(s_chud_globals_definition &); /* compiler_generated() */
	s_chud_globals_definition &operator=(s_chud_globals_definition const &); /* compiler_generated() */
};
static_assert(sizeof(s_chud_globals_definition) == 704, "Invalid s_chud_globals_definition size");

/* ---------- prototypes */

extern _inline s_chud_globals_definition *chud_globals_definition_get();

/* ---------- globals */

/* ---------- public code */

inline s_chud_globals_definition *chud_globals_definition_get() // 0x1085DBB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?chud_globals_definition_get@@YAPAUs_chud_globals_definition@@XZ");

	return *(s_chud_globals_definition * *)0x5257c40;
}

/* ---------- private code */

#endif // __BLAM_INTERFACE_CHUD_CHUD_GLOBALS_HPP__
