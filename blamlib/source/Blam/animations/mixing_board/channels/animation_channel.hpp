#ifndef __BLAM_ANIMATIONS_MIXING_BOARD_CHANNELS_ANIMATION_CHANNEL_HPP__
#define __BLAM_ANIMATIONS_MIXING_BOARD_CHANNELS_ANIMATION_CHANNEL_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

class c_animation_channel_base;
class c_animation_id;
struct c_animation_channel;
struct c_base_channel_settings;

/* ---------- constants */

/* ---------- definitions */

class c_animation_id
{
public:
	short graph_index; // 0x0
	short animation_index; // 0x2
};
static_assert(sizeof(c_animation_id) == 4, "Invalid c_animation_id size");

struct c_base_channel_settings
{
	long graph_definition_index; // 0x0
	long animation_name; // 0x4
	c_animation_id animation_id; // 0x8
	unsigned short playback_flags; // 0xC
	char type; // 0xE
	char field_F; // 0xF
};
static_assert(sizeof(c_base_channel_settings) == 16, "Invalid c_base_channel_settings size");

#pragma pack(push, 4)
class c_animation_channel_base
{
public:
	c_base_channel_settings settings; // 0x0
	char frame_count; // 0x10
	bool initialized; // 0x11
};
#pragma pack(pop)
static_assert(sizeof(c_animation_channel_base) == 20, "Invalid c_animation_channel_base size");

#pragma pack(push, 4)
struct c_animation_channel :
	public c_animation_channel_base
{
	float playback_speed; // 0x14
	float frame_position; // 0x18
	float playback_ratio_remaining; // 0x1C
	short vector2; // 0x20
	short field_22; // 0x22
	short field_24; // 0x24
	short field_26; // 0x26
	short vector1; // 0x28
	short field_2A; // 0x2A
	long field_2C; // 0x2C
	long field_30; // 0x30
	long field_34; // 0x34
	unsigned char state_flags; // 0x38
	static float (*const get_playback_time_remaining)(c_animation_channel *);
	static void (*const set_frame_position)(c_animation_channel *, float);
};
#pragma pack(pop)
static_assert(sizeof(c_animation_channel) == 60, "Invalid c_animation_channel size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_ANIMATIONS_MIXING_BOARD_CHANNELS_ANIMATION_CHANNEL_HPP__
