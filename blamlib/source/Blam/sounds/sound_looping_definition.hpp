#ifndef __BLAM_SOUNDS_SOUND_LOOPING_DEFINITION_HPP__
#define __BLAM_SOUNDS_SOUND_LOOPING_DEFINITION_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct real_bounds;
struct s_sound_looping_definition;
struct s_sound_looping_detail;
struct s_sound_looping_track;
struct s_tag_reference;

/* ---------- constants */

/* ---------- definitions */

struct s_sound_looping_track
{
	unsigned long name; // 0x0
	c_flags<enum e_sound_looping_track_flags,long> flags; // 0x4
	float gain; // 0x8
	float fade_in_duration; // 0xC
	short unknown_1; // 0x10
	short unknown_2; // 0x12
	float fade_out_duration; // 0x14
	short unknown_3; // 0x18
	short unknown_4; // 0x1A
	s_tag_reference in; // 0x1C
	s_tag_reference loop; // 0x2C
	s_tag_reference out; // 0x3C
	s_tag_reference alternate_loop; // 0x4C
	s_tag_reference alternate_out; // 0x5C
	c_enum<enum e_sound_looping_output_effect,short> output_effect; // 0x6C
	short unknown_5; // 0x6E
	s_tag_reference alternate_transition_in; // 0x70
	s_tag_reference alternate_transition_out; // 0x80
	float alternate_cross_fade_duration; // 0x90
	short unknown_6; // 0x94
	short unknown_7; // 0x96
	float alternate_fade_out_duration; // 0x98
	float unknown_8; // 0x9C
	s_sound_looping_track(s_sound_looping_track &); /* compiler_generated() */
	s_sound_looping_track(s_sound_looping_track const &); /* compiler_generated() */
	s_sound_looping_track(); /* compiler_generated() */
	s_sound_looping_track &operator=(s_sound_looping_track &); /* compiler_generated() */
	s_sound_looping_track &operator=(s_sound_looping_track const &); /* compiler_generated() */
};
static_assert(sizeof(s_sound_looping_track) == 160, "Invalid s_sound_looping_track size");

#pragma pack(push, 4)
struct s_sound_looping_detail
{
	unsigned long name; // 0x0
	s_tag_reference sound; // 0x4
	real_bounds random_period; // 0x14
	float unknown; // 0x1C
	c_flags<enum e_sound_looping_detail_flags,long> flags; // 0x20
	angle_bounds yaw; // 0x24
	angle_bounds pitch; // 0x2C
	real_bounds distance; // 0x34
	s_sound_looping_detail(s_sound_looping_detail &); /* compiler_generated() */
	s_sound_looping_detail(s_sound_looping_detail const &); /* compiler_generated() */
	s_sound_looping_detail(); /* compiler_generated() */
	s_sound_looping_detail &operator=(s_sound_looping_detail &); /* compiler_generated() */
	s_sound_looping_detail &operator=(s_sound_looping_detail const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_sound_looping_detail) == 60, "Invalid s_sound_looping_detail size");

struct s_sound_looping_definition
{
	c_flags<enum e_sound_looping_flags,long> flags; // 0x0
	real_bounds martys_music_time; // 0x4
	real_bounds distance_bounds; // 0xC
	s_tag_reference unused; // 0x14
	c_enum<enum e_sound_class,short> sound_class; // 0x24
	short unknown_4; // 0x26
	c_tag_block<s_sound_looping_track> tracks; // 0x28
	c_tag_block<s_sound_looping_detail> details; // 0x34
	s_sound_looping_definition(s_sound_looping_definition &); /* compiler_generated() */
	s_sound_looping_definition(s_sound_looping_definition const &); /* compiler_generated() */
	s_sound_looping_definition(); /* compiler_generated() */
	s_sound_looping_definition &operator=(s_sound_looping_definition &); /* compiler_generated() */
	s_sound_looping_definition &operator=(s_sound_looping_definition const &); /* compiler_generated() */
};
static_assert(sizeof(s_sound_looping_definition) == 64, "Invalid s_sound_looping_definition size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_SOUNDS_SOUND_LOOPING_DEFINITION_HPP__
