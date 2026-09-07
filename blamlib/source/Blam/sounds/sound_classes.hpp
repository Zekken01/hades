#ifndef __BLAM_SOUNDS_SOUND_CLASSES_HPP__
#define __BLAM_SOUNDS_SOUND_CLASSES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"

/* ---------- forward declarations */

struct real_bounds;
struct s_sound_class_definition;
struct s_sound_class_ducking;
struct s_sound_propagation;

/* ---------- constants */

/* ---------- definitions */

struct s_sound_propagation
{
	float reverb_gain; // 0x0
	float direct_path_gain; // 0x4
	float base_obstruction; // 0x8
	float base_occlusion; // 0xC
};
static_assert(sizeof(s_sound_propagation) == 16, "Invalid s_sound_propagation size");

struct s_sound_class_ducking
{
	float ducking_db; // 0x0
	float fade_in_time; // 0x4
	float sustain_time; // 0x8
	float fade_out_time; // 0xC
};
static_assert(sizeof(s_sound_class_ducking) == 16, "Invalid s_sound_class_ducking size");

struct s_sound_class_definition
{
	short max_sounds_per_tag; // 0x0
	short max_sounds_per_object; // 0x2
	long preemption_time; // 0x4
	c_flags<enum e_sound_class_internal_flags,unsigned short> internal_flags; // 0x8
	c_flags<enum e_sound_class_flags,unsigned short> flags; // 0xA
	short priority; // 0xC
	c_enum<enum e_sound_cache_miss_mode,char> cache_miss_mode; // 0xE
	c_flags<enum e_sound_accoustics_flags,char> bind_to_accoustics; // 0xF
	c_flags<enum e_sound_spatial_suppression_flags,char> suppress_spatialization; // 0x10
	unsigned char __pad0[3]; // 0x11
	s_sound_propagation air_propogation; // 0x14
	s_sound_propagation underwater_propogation; // 0x24
	float override_speaker_gain; // 0x34
	real_bounds distance_bounds1; // 0x38
	real_bounds distance_bounds2; // 0x40
	real_bounds scale_gain_bounds; // 0x48
	s_sound_class_ducking cutscene_ducking; // 0x50
	s_sound_class_ducking scripted_dialog_ducking; // 0x60
	s_sound_class_ducking cortana_effect_ducking; // 0x70
	float cortana_effect_unknown; // 0x80
	float doppler_factor; // 0x84
	char stero_playback_type; // 0x88
	unsigned char __pad1[3]; // 0x89
	float transmission_multiplier; // 0x8C
	float obstruction_max_bend; // 0x90
	float occlusion_max_bend; // 0x94
	s_sound_class_definition(s_sound_class_definition &); /* compiler_generated() */
	s_sound_class_definition(s_sound_class_definition const &); /* compiler_generated() */
	s_sound_class_definition(); /* compiler_generated() */
	s_sound_class_definition &operator=(s_sound_class_definition &); /* compiler_generated() */
	s_sound_class_definition &operator=(s_sound_class_definition const &); /* compiler_generated() */
	unsigned char __pad2[8]; // 0x98
};
static_assert(sizeof(s_sound_class_definition) == 160, "Invalid s_sound_class_definition size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_SOUNDS_SOUND_CLASSES_HPP__
