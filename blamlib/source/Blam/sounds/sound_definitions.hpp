#ifndef __BLAM_SOUNDS_SOUND_DEFINITIONS_HPP__
#define __BLAM_SOUNDS_SOUND_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct real_bounds;
struct s_sound_custom_playback;
struct s_sound_definition;
struct s_sound_dialogue_info;
struct s_sound_dialogue_unknown;
struct s_sound_dialogue_unknown_2;
struct s_sound_dialogue_unknown_2_1;
struct s_sound_dialogue_unknown_2_2;
struct s_sound_encoded_permutation;
struct s_sound_extra_info;
struct s_sound_filter;
struct s_sound_filter_settings;
struct s_sound_language;
struct s_sound_language_permutation;
struct s_sound_permutation;
struct s_sound_permutation_chunk;
struct s_sound_permutation_duration;
struct s_sound_pitch_range;
struct s_sound_pitch_range_duration;
struct s_sound_platform_codec;
struct s_sound_playback_parameters;
struct s_sound_promotion;
struct s_sound_promotion_rule;
struct s_sound_raw_info;
struct s_sound_runtime_timer;
struct s_sound_scale;
struct s_sound_unknown;
struct s_tag_data;
struct short_bounds;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_sound_playback_parameters
{
	c_flags<enum e_sound_playback_distance_override_flags,long> distance_override_flags; // 0x0
	float distance_a; // 0x4
	float distance_b; // 0x8
	float distance_c; // 0xC
	float distance_d; // 0x10
	float skip_fraction; // 0x14
	float naximum_bend_per_second; // 0x18
	float gain_base; // 0x1C
	float gain_variance; // 0x20
	short_bounds random_pitch; // 0x24
	real_bounds cone_angle; // 0x28
	float outer_cone_gain; // 0x30
	c_flags<enum e_sound_playback_gain_override_flags,long> gain_override_flags; // 0x34
	float azimuth; // 0x38
	float positional_gain; // 0x3C
	float first_person_gain; // 0x40
	s_sound_playback_parameters(s_sound_playback_parameters &); /* compiler_generated() */
	s_sound_playback_parameters(s_sound_playback_parameters const &); /* compiler_generated() */
	s_sound_playback_parameters(); /* compiler_generated() */
	s_sound_playback_parameters &operator=(s_sound_playback_parameters &); /* compiler_generated() */
	s_sound_playback_parameters &operator=(s_sound_playback_parameters const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_sound_playback_parameters) == 68, "Invalid s_sound_playback_parameters size");

#pragma pack(push, 4)
struct s_sound_scale
{
	real_bounds gain_modifier; // 0x0
	short_bounds pitch_modifier; // 0x8
	real_bounds skip_fraction_modifier; // 0xC
};
#pragma pack(pop)
static_assert(sizeof(s_sound_scale) == 20, "Invalid s_sound_scale size");

struct s_sound_platform_codec
{
	unsigned char unknown; // 0x0
	c_enum<enum e_sound_load_mode,unsigned char> load_mode; // 0x1
	c_enum<enum e_sound_encoding,unsigned char> encoding; // 0x2
	c_enum<enum e_sound_compression,unsigned char> compression; // 0x3
	s_sound_platform_codec(s_sound_platform_codec &); /* compiler_generated() */
	s_sound_platform_codec(s_sound_platform_codec const &); /* compiler_generated() */
	s_sound_platform_codec(); /* compiler_generated() */
	s_sound_platform_codec &operator=(s_sound_platform_codec &); /* compiler_generated() */
	s_sound_platform_codec &operator=(s_sound_platform_codec const &); /* compiler_generated() */
};
static_assert(sizeof(s_sound_platform_codec) == 4, "Invalid s_sound_platform_codec size");

struct s_sound_promotion_rule
{
	short pitch_range_index; // 0x0
	short maximum_playing_count; // 0x2
	float suppression_time; // 0x4
	__int32 unknown_1; // 0x8
	__int32 unknown_2; // 0xC
};
static_assert(sizeof(s_sound_promotion_rule) == 16, "Invalid s_sound_promotion_rule size");

struct s_sound_runtime_timer
{
	__int32 unknown; // 0x0
};
static_assert(sizeof(s_sound_runtime_timer) == 4, "Invalid s_sound_runtime_timer size");

struct s_sound_promotion
{
	c_tag_block<s_sound_promotion_rule> promotion_rule; // 0x0
	c_tag_block<s_sound_runtime_timer> runtime_timer; // 0xC
};
static_assert(sizeof(s_sound_promotion) == 24, "Invalid s_sound_promotion size");

struct s_sound_permutation_chunk
{
	__int32 offset; // 0x0
	__int32 encoded_size; // 0x4
	__int32 runtime_index; // 0x8
	__int32 unknown_1; // 0xC
	s_sound_permutation_chunk *next; // 0x10
};
static_assert(sizeof(s_sound_permutation_chunk) == 20, "Invalid s_sound_permutation_chunk size");

#pragma pack(push, 4)
struct s_sound_permutation
{
	unsigned long name; // 0x0
	real_bounds skip_fraction; // 0x4
	unsigned long samples; // 0xC
	__int32 permutation_index; // 0x10
	__int32 is_not_first_permutation; // 0x14
	c_tag_block<s_sound_permutation_chunk> permutation_chunks; // 0x18
	__int32 unknown_1; // 0x24
	__int32 unknown_2; // 0x28
};
#pragma pack(pop)
static_assert(sizeof(s_sound_permutation) == 44, "Invalid s_sound_permutation size");

struct s_sound_pitch_range
{
	unsigned long name; // 0x0
	short natural_pitch; // 0x4
	short unknown_1; // 0x6
	short_bounds bend; // 0x8
	short_bounds max_gain_pitch; // 0xC
	short_bounds unknown_2; // 0x10
	__int32 unknown_3; // 0x14
	__int32 unknown_4; // 0x18
	__int32 unknown_5; // 0x1C
	__int32 unknown_6; // 0x20
	short unknown_7; // 0x24
	short unknown_8; // 0x26
	unsigned char permutation_count; // 0x28
	unsigned char unknown_9; // 0x29
	short unknown_10; // 0x2A
	c_tag_block<s_sound_permutation> permutations; // 0x2C
};
static_assert(sizeof(s_sound_pitch_range) == 56, "Invalid s_sound_pitch_range size");

struct s_sound_filter_settings
{
	real_bounds scale; // 0x0
	float random_base; // 0x8
	float random_variance; // 0xC
};
static_assert(sizeof(s_sound_filter_settings) == 16, "Invalid s_sound_filter_settings size");

struct s_sound_filter
{
	__int32 filter_type; // 0x0
	__int32 filter_width; // 0x4
	s_sound_filter_settings settings_1; // 0x8
	s_sound_filter_settings settings_2; // 0x18
	s_sound_filter_settings settings_3; // 0x28
	s_sound_filter_settings settings_4; // 0x38
};
static_assert(sizeof(s_sound_filter) == 72, "Invalid s_sound_filter size");

#pragma pack(push, 4)
struct s_sound_custom_playback
{
	__int32 unknown_1; // 0x0
	__int32 unknown_2; // 0x4
	__int32 unknown_3; // 0x8
	c_flags<enum e_sound_filter_flags,int> flags; // 0xC
	__int32 unknown_4; // 0x10
	__int32 unknown_5; // 0x14
	c_tag_block<s_sound_filter> filters; // 0x18
	__int32 unknown_6; // 0x24
	__int32 unknown_7; // 0x28
	__int32 unknown_8; // 0x2C
	__int32 unknown_9; // 0x30
	__int32 unknown_10; // 0x34
	__int32 unknown_11; // 0x38
	__int32 unknown_12; // 0x3C
	__int32 unknown_13; // 0x40
	__int32 unknown_14; // 0x44
	__int32 unknown_15; // 0x48
	__int32 unknown_16; // 0x4C
	__int32 unknown_17; // 0x50
	s_sound_custom_playback(s_sound_custom_playback &); /* compiler_generated() */
	s_sound_custom_playback(s_sound_custom_playback const &); /* compiler_generated() */
	s_sound_custom_playback(); /* compiler_generated() */
	s_sound_custom_playback &operator=(s_sound_custom_playback &); /* compiler_generated() */
	s_sound_custom_playback &operator=(s_sound_custom_playback const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_sound_custom_playback) == 84, "Invalid s_sound_custom_playback size");

struct s_sound_unknown
{
	__int32 unknown_1; // 0x0
	__int32 unknown_2; // 0x4
	__int32 unknown_3; // 0x8
	__int32 unknown_4; // 0xC
	__int32 unknown_5; // 0x10
	__int32 unknown_6; // 0x14
};
static_assert(sizeof(s_sound_unknown) == 24, "Invalid s_sound_unknown size");

#pragma pack(push, 4)
struct s_sound_raw_info
{
	unsigned long skip_fraction_name; // 0x0
	__int32 unknown_1; // 0x4
	__int32 unknown_2; // 0x8
	__int32 unknown_3; // 0xC
	__int32 unknown_4; // 0x10
	__int32 unknown_5; // 0x14
	__int32 unknown_6; // 0x18
	__int32 unknown_7; // 0x1C
	__int32 unknown_8; // 0x20
	__int32 unknown_9; // 0x24
	__int32 unknown_10; // 0x28
	__int32 unknown_11; // 0x2C
	__int32 unknown_12; // 0x30
	__int32 unknown_13; // 0x34
	__int32 unknown_14; // 0x38
	__int32 unknown_15; // 0x3C
	__int32 unknown_16; // 0x40
	__int32 unknown_17; // 0x44
	__int32 unknown_18; // 0x48
	c_tag_block<s_sound_unknown> unknown_list; // 0x4C
	c_enum<enum e_sound_compression,short> compression; // 0x58
	c_enum<enum e_sound_game_language,char> language; // 0x5A
	unsigned char unknown_19; // 0x5B
	unsigned long samples; // 0x5C
	unsigned long resource_sample_offset; // 0x60
	unsigned long resource_sample_size; // 0x64
	__int32 unknown_20; // 0x68
	__int32 unknown_21; // 0x6C
	__int32 unknown_22; // 0x70
	__int32 unknown_23; // 0x74
	__int32 unknown_24; // 0x78
	s_sound_raw_info(s_sound_raw_info &); /* compiler_generated() */
	s_sound_raw_info(s_sound_raw_info const &); /* compiler_generated() */
	s_sound_raw_info(); /* compiler_generated() */
	s_sound_raw_info &operator=(s_sound_raw_info &); /* compiler_generated() */
	s_sound_raw_info &operator=(s_sound_raw_info const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_sound_raw_info) == 124, "Invalid s_sound_raw_info size");

#pragma pack(push, 4)
struct s_sound_language_permutation
{
	c_tag_block<s_sound_raw_info> permutation_raw_info; // 0x0
};
#pragma pack(pop)
static_assert(sizeof(s_sound_language_permutation) == 12, "Invalid s_sound_language_permutation size");

struct s_sound_dialogue_info
{
	unsigned long mouth_data_offset; // 0x0
	unsigned long mouth_data_length; // 0x4
	unsigned long lipsync_data_offset; // 0x8
	unsigned long lipsync_data_length; // 0xC
};
static_assert(sizeof(s_sound_dialogue_info) == 16, "Invalid s_sound_dialogue_info size");

struct s_sound_dialogue_unknown_2_1
{
	__int32 unknown_1; // 0x0
	__int32 unknown_2; // 0x4
};
static_assert(sizeof(s_sound_dialogue_unknown_2_1) == 8, "Invalid s_sound_dialogue_unknown_2_1 size");

struct s_sound_dialogue_unknown_2_2
{
	short unknown_1; // 0x0
	unsigned char unknown_2; // 0x2
	unsigned char unknown_3; // 0x3
	unsigned char unknown_4; // 0x4
	unsigned char unknown_5; // 0x5
	unsigned char unknown_6; // 0x6
	unsigned char unknown_7; // 0x7
};
static_assert(sizeof(s_sound_dialogue_unknown_2_2) == 8, "Invalid s_sound_dialogue_unknown_2_2 size");

struct s_sound_dialogue_unknown_2
{
	float unknown_1; // 0x0
	float unknown_2; // 0x4
	float unknown_3; // 0x8
	float unknown_4; // 0xC
	c_tag_block<s_sound_dialogue_unknown_2_1> unknown_5; // 0x10
	c_tag_block<s_sound_dialogue_unknown_2_2> unknown_6; // 0x1C
};
static_assert(sizeof(s_sound_dialogue_unknown_2) == 40, "Invalid s_sound_dialogue_unknown_2 size");

#pragma pack(push, 4)
struct s_sound_dialogue_unknown
{
	c_tag_block<s_sound_dialogue_unknown_2> unknown; // 0x0
};
#pragma pack(pop)
static_assert(sizeof(s_sound_dialogue_unknown) == 12, "Invalid s_sound_dialogue_unknown size");

#pragma pack(push, 4)
struct s_sound_encoded_permutation
{
	s_tag_data data; // 0x0
	c_tag_block<s_sound_dialogue_info> dialogue_info; // 0x14
	c_tag_block<s_sound_dialogue_unknown> unknown; // 0x20
	s_sound_encoded_permutation(s_sound_encoded_permutation &); /* compiler_generated() */
	s_sound_encoded_permutation(s_sound_encoded_permutation const &); /* compiler_generated() */
	s_sound_encoded_permutation(); /* compiler_generated() */
	s_sound_encoded_permutation &operator=(s_sound_encoded_permutation &); /* compiler_generated() */
	s_sound_encoded_permutation &operator=(s_sound_encoded_permutation const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_sound_encoded_permutation) == 44, "Invalid s_sound_encoded_permutation size");

struct s_sound_extra_info
{
	c_tag_block<s_sound_language_permutation> language_permutations; // 0x0
	c_tag_block<s_sound_encoded_permutation> encoded_permutations; // 0xC
	__int32 unknown_1; // 0x18
	__int32 unknown_2; // 0x1C
	__int32 unknown_3; // 0x20
	__int32 unknown_4; // 0x24
};
static_assert(sizeof(s_sound_extra_info) == 40, "Invalid s_sound_extra_info size");

struct s_sound_permutation_duration
{
	__int32 frame_count; // 0x0
};
static_assert(sizeof(s_sound_permutation_duration) == 4, "Invalid s_sound_permutation_duration size");

struct s_sound_pitch_range_duration
{
	short permutation_start_index; // 0x0
	short permutation_count; // 0x2
};
static_assert(sizeof(s_sound_pitch_range_duration) == 4, "Invalid s_sound_pitch_range_duration size");

#pragma pack(push, 4)
struct s_sound_language
{
	c_enum<enum e_sound_game_language,int> game_languages; // 0x0
	c_tag_block<s_sound_permutation_duration> permutation_durations; // 0x4
	c_tag_block<s_sound_pitch_range_duration> pitch_range_durations; // 0x10
	s_sound_language(s_sound_language &); /* compiler_generated() */
	s_sound_language(s_sound_language const &); /* compiler_generated() */
	s_sound_language(); /* compiler_generated() */
	s_sound_language &operator=(s_sound_language &); /* compiler_generated() */
	s_sound_language &operator=(s_sound_language const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_sound_language) == 28, "Invalid s_sound_language size");

#pragma pack(push, 4)
struct s_sound_definition
{
	c_flags<enum e_sound_flags,short> flags; // 0x0
	short unknown_1; // 0x2
	long unknown_2; // 0x4
	long unknown_3; // 0x8
	c_enum<enum e_sound_class,unsigned char> sound_class; // 0xC
	c_enum<enum e_sound_sample_rate,unsigned char> sample_rate; // 0xD
	unsigned char unknown_4; // 0xE
	c_enum<enum e_sound_import_type,unsigned char> import_type; // 0xF
	s_sound_playback_parameters playback_parameters; // 0x10
	s_sound_scale scale; // 0x54
	s_sound_platform_codec platform_codec; // 0x68
	s_sound_promotion promotion; // 0x6C
	long unknown_5; // 0x84
	long unknown_6; // 0x88
	long unknown_7; // 0x8C
	long longest_permutation_duration; // 0x90
	unsigned long total_sample_size; // 0x94
	long unknown_8; // 0x98
	c_tag_block<s_sound_pitch_range> pitch_ranges; // 0x9C
	c_tag_block<s_sound_custom_playback> custom_playbacks; // 0xA8
	c_tag_block<s_sound_extra_info> extra_info; // 0xB4
	c_tag_block<s_sound_language> languages; // 0xC0
	unsigned long resource; // 0xCC
	unsigned long padding; // 0xD0
	s_sound_definition(s_sound_definition &); /* compiler_generated() */
	s_sound_definition(s_sound_definition const &); /* compiler_generated() */
	s_sound_definition(); /* compiler_generated() */
	s_sound_definition &operator=(s_sound_definition &); /* compiler_generated() */
	s_sound_definition &operator=(s_sound_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_sound_definition) == 212, "Invalid s_sound_definition size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_SOUNDS_SOUND_DEFINITIONS_HPP__
