#ifndef __BLAM_SOUNDS_PLATFORM_SOUND_HPP__
#define __BLAM_SOUNDS_PLATFORM_SOUND_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"

/* ---------- forward declarations */

struct real_vector3d;
struct s_platform_sound_effect_properties;
struct s_platform_sound_environemnt;
struct s_platform_sound_listener_properties;
struct s_platform_sound_source_properties;
struct s_platform_sound_status;
struct s_platform_sound_voice_update_definition;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_platform_sound_source_properties
{
	long field_0; // 0x0
	long sample_rate; // 0x4
	float pitch; // 0x8
	float gain_db; // 0xC
	short sound_class; // 0x10
	float direct_path_gain_db; // 0x14
	float reverb_gain_db; // 0x18
	float override_speaker_gain; // 0x1C
	unsigned char __pad1[36]; // 0x20
	float cone_attenuation; // 0x44
	float transmission_envelope[4]; // 0x48
	unsigned char __pad2[8]; // 0x58
	long playback_controller_index; // 0x60
	long flags; // 0x64
	unsigned char __pad3[20]; // 0x68
};
#pragma pack(pop)
static_assert(sizeof(s_platform_sound_source_properties) == 124, "Invalid s_platform_sound_source_properties size");

#pragma pack(push, 4)
struct s_platform_sound_effect_properties
{
	char unknown[1084]; // 0x0
};
#pragma pack(pop)
static_assert(sizeof(s_platform_sound_effect_properties) == 1084, "Invalid s_platform_sound_effect_properties size");

struct s_platform_sound_environemnt
{
	void *sound_environemnt_definition; // 0x0
	float unknown1; // 0x4
	float unknown2; // 0x8
	float unknown3; // 0xC
	float unknown4; // 0x10
	float weight; // 0x14
};
static_assert(sizeof(s_platform_sound_environemnt) == 24, "Invalid s_platform_sound_environemnt size");

struct s_platform_sound_listener_properties
{
	real_point3d position; // 0x0
	real_vector3d forward; // 0xC
	real_vector3d up; // 0x18
	real_vector3d velocity; // 0x24
	long reverbs_count; // 0x30
	s_platform_sound_environemnt *reverbs; // 0x34
};
static_assert(sizeof(s_platform_sound_listener_properties) == 56, "Invalid s_platform_sound_listener_properties size");

#pragma pack(push, 4)
struct s_platform_sound_voice_update_definition
{
	long listener_index; // 0x0
	long flags; // 0x4
	real_vector3d position; // 0x8
	real_vector3d velocity; // 0x14
	real_vector3d forward; // 0x20
	real_vector3d up; // 0x2C
	float occlusion; // 0x38
	float obstruction; // 0x3C
	float reverb_gain_db; // 0x40
	float occlusion_bend; // 0x44
	float obstruction_bend; // 0x48
};
#pragma pack(pop)
static_assert(sizeof(s_platform_sound_voice_update_definition) == 76, "Invalid s_platform_sound_voice_update_definition size");

struct s_platform_sound_status
{
	unsigned long available_sources[7]; // 0x0
	long source_counts[5]; // 0x1C
	long source_max_counts[5]; // 0x30
	unsigned long available_voices[7]; // 0x44
};
static_assert(sizeof(s_platform_sound_status) == 96, "Invalid s_platform_sound_status size");

/* ---------- prototypes */

extern bool platform_sound_source_is_playing(long source_index);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_SOUNDS_PLATFORM_SOUND_HPP__
