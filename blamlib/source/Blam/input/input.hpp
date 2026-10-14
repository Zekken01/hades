#ifndef __BLAM_INPUT_INPUT_HPP__
#define __BLAM_INPUT_INPUT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/integer_math_definitions.hpp"

/* ---------- forward declarations */

struct s_gamepad_state;
struct s_input_globals;
struct s_key_state;
struct s_key_stroke;
struct s_mouse_event;
struct s_mouse_state;
struct s_rumble_state;
struct short_point_2d;

/* ---------- constants */

enum
{
	k_number_of_buffered_key_strokes = 64, // 0x0040 '@'
	k_number_of_buffered_mouse_events = 64, // 0x0040 '@'
	k_number_of_key_states = 104, // 0x0068 'h'
};

/* ---------- definitions */

struct s_key_state
{
	unsigned short down_milliseconds; // 0x0
	unsigned char down_frames; // 0x2
	char unknown; // 0x3
};
static_assert(sizeof(s_key_state) == 4, "Invalid s_key_state size");

struct s_key_stroke
{
	unsigned char flags; // 0x0
	long type; // 0x4
	long field_8; // 0x8
	long field_C; // 0xC
};
static_assert(sizeof(s_key_stroke) == 16, "Invalid s_key_stroke size");
static_assert(offsetof(s_key_stroke, type) == 0x4, "s_key_stroke::type moved when its reconstructed padding was removed");

struct s_mouse_event
{
	__int32 type; // 0x0
	__int32 x; // 0x4
	__int32 y; // 0x8
	__int32 delta; // 0xC
	char button; // 0x10
	char _pad[3]; // 0x11
};
static_assert(sizeof(s_mouse_event) == 20, "Invalid s_mouse_event size");

#pragma pack(push, 4)
struct s_mouse_state
{
	long x; // 0x0
	long y; // 0x4
	long z; // 0x8
	unsigned char down_frames[5]; // 0xC
	unsigned char __pad0[1]; // 0x11
	unsigned short down_milliseconds[5]; // 0x12
	char button_mask; // 0x1C
	long raw_x; // 0x20
	long raw_y; // 0x24
	long raw_z; // 0x28
};
#pragma pack(pop)
static_assert(sizeof(s_mouse_state) == 44, "Invalid s_mouse_state size");

#pragma pack(push, 4)
struct s_gamepad_state
{
	unsigned char trigger_values[2]; // 0x0
	unsigned char trigger_thresholds[2]; // 0x2
	unsigned char button_frames[16]; // 0x4
	unsigned short button_milliseconds[16]; // 0x14
	short_point_2d left_thumb; // 0x34
	short_point_2d right_thumb; // 0x38
};
#pragma pack(pop)
static_assert(sizeof(s_gamepad_state) == 60, "Invalid s_gamepad_state size");

struct s_rumble_state
{
	short left_motor_speed; // 0x0
	short right_motor_speed; // 0x2
};
static_assert(sizeof(s_rumble_state) == 4, "Invalid s_rumble_state size");

#pragma pack(push, 4)
struct s_input_globals
{
	bool initialized; // 0x0
	bool field_1; // 0x1
	bool supressed; // 0x2
	bool blocked_inputs[3]; // 0x3
	bool feedback_supressed; // 0x6
	unsigned long last_update_milliseconds; // 0x8
	s_key_state key_states[104]; // 0xC
	short buffered_key_read_index; // 0x1AC
	short buffered_key_write_index; // 0x1AE
	s_key_stroke buffered_keys[64]; // 0x1B0
	short buffered_mouse_read_index; // 0x5B0
	short buffered_mouse_write_index; // 0x5B2
	s_mouse_event buffered_mouse[64]; // 0x5B4
	bool field_AB4; // 0xAB4
	bool nc_mouse_down; // 0xAB5
	bool field_AB6; // 0xAB6
	bool mouse_active; // 0xAB7
	s_mouse_state mouse; // 0xAB8
	s_mouse_state null_mouse; // 0xAE4
	long field_B10; // 0xB10
	long field_B14; // 0xB14
	long field_B18; // 0xB18
	long field_B1C; // 0xB1C
	long field_B20; // 0xB20
	long field_B24; // 0xB24
	unsigned long active_gamepads; // 0xB28
	s_gamepad_state gamepad_states[4]; // 0xB2C
	s_gamepad_state null_gamepad; // 0xC1C
	s_rumble_state rumble_states[4]; // 0xC58
	unsigned long field_C68; // 0xC68
};
#pragma pack(pop)
static_assert(sizeof(s_input_globals) == 3180, "Invalid s_input_globals size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_INPUT_INPUT_HPP__
