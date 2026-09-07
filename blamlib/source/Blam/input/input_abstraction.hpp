#ifndef __BLAM_INPUT_INPUT_ABSTRACTION_HPP__
#define __BLAM_INPUT_INPUT_ABSTRACTION_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/memory/ring_buffer.hpp"

/* ---------- forward declarations */

struct c_abstract_button;
struct c_ring_buffer;
struct s_game_input_preferences;
struct s_game_input_state;
struct s_input_abstraction_globals;

/* ---------- constants */

enum
{
	k_abstract_gamepad_button_count = 16, // 0x0010
	k_abstract_remappable_button_count = 59, // 0x003B ';'
	k_abstract_button_count = 63, // 0x003F '?'
};

/* ---------- definitions */

struct c_abstract_button
{
	public:
	enum e_flag_bits
	{
		_latched_bit = 0,
	};
	public:
	unsigned short down_msec; // 0x0
	unsigned char down_frames; // 0x2
	unsigned char flags; // 0x3
	float down_amount; // 0x4
	unsigned char accessor_index; // 0x8
	unsigned char lock_index; // 0x9
	_inline void update(unsigned short msec, unsigned char frames, unsigned char amount);
	bool access_valid() const;
	void set_accessor(long);
	void lock();
	void unlock();
	unsigned char get_down_frames() const;
	unsigned short get_down_msec() const;
	bool locked() const;
	bool latched() const;
	_inline void unlatch();
private:
	_inline void set_latched_bit(bool value);
	unsigned char __pad0[2]; // 0xA
};
static_assert(sizeof(c_abstract_button) == 12, "Invalid c_abstract_button size");

struct s_game_input_preferences
{
	float gamepad_sensitivty_x; // 0x0
	float gamepad_sensitivty_y; // 0x4
	unsigned char button_remap[59]; // 0x8
	bool hold_buttons[59]; // 0x43
	unsigned short primary_keys[63]; // 0x7E
	unsigned short secondary_keys[63]; // 0xFC
	unsigned char primary_mouuse[63]; // 0x17A
	unsigned char secondary_mouse[63]; // 0x1B9
	short stick_layout; // 0x1F8
	bool pitch_inverted; // 0x1FA
	bool vehicle_pitch_inverted; // 0x1FB
	short camera_panning; // 0x1FC
	unsigned char __pad0[2]; // 0x1FE
	float camera_speed; // 0x200
	float camera_thrust; // 0x204
};
static_assert(sizeof(s_game_input_preferences) == 520, "Invalid s_game_input_preferences size");

struct s_game_input_state
{
	c_abstract_button buttons[63]; // 0x0
	short left_thumb_x; // 0x2F4
	short left_thumb_y; // 0x2F6
	short right_thumb_x; // 0x2F8
	short right_thumb_y; // 0x2FA
	float forward; // 0x2FC
	float strafe; // 0x300
	float vehicle_forward; // 0x304
	float yaw; // 0x308
	float pitch; // 0x30C
	float vehicle_aircraft_pitch; // 0x310
	float vehicle_yaw; // 0x314
	float vehicle_ground_pitch; // 0x318
	float field_31C; // 0x31C
	float field_320; // 0x320
	float field_324; // 0x324
};
static_assert(sizeof(s_game_input_state) == 808, "Invalid s_game_input_state size");

#pragma pack(push, 4)
struct s_input_abstraction_globals
{
	s_game_input_preferences preferences[4]; // 0x0
	s_game_input_state input_states[4]; // 0x820
	unsigned long gamepad_detection_time; // 0x14C0
	bool active_gamepads[4]; // 0x14C4
	long control_method; // 0x14C8
	char field_14CC[4]; // 0x14CC
	void *game_input_globals; // 0x14D0
	float legacy_function[4]; // 0x14D4
	long legacy_flags; // 0x14E4
	c_ring_buffer mouse_filter_ring_buffer; // 0x14E8
	float mouse_filter_values[4]; // 0x14F4
	unsigned long mouse_filter_flags; // 0x1504
	unsigned long last_update_milliseconds; // 0x1508
	unsigned long update_flags; // 0x150C
	long field_1510; // 0x1510
};
#pragma pack(pop)
static_assert(sizeof(s_input_abstraction_globals) == 5396, "Invalid s_input_abstraction_globals size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_extern void _sub_10A818D0(c_abstract_button *const, unsigned short, unsigned char, unsigned char);
_inline void c_abstract_button::update(unsigned short msec, unsigned char frames, unsigned char amount) // 0x10A818D0
{
	mangled_x86(MANGLED_TODO, "?update@c_abstract_button@@QAEXGEE@Z");
	// unsigned char amount;
	todo("implement");
	_sub_10A818D0(this, msec, frames, amount);
}

_extern void _sub_10A81870(c_abstract_button *const);
_inline void c_abstract_button::unlatch() // 0x10A81870
{
	mangled_x86(MANGLED_TODO, "?unlatch@c_abstract_button@@QAEXXZ");
	// c_abstract_button *const this;
	todo("implement");
	_sub_10A81870(this);
}

_extern void _sub_10A81750(c_abstract_button *const, bool);
_inline void c_abstract_button::set_latched_bit(bool value) // 0x10A81750
{
	mangled_x86(MANGLED_TODO, "?set_latched_bit@c_abstract_button@@AAEX_N@Z");
	// bool value;
	todo("implement");
	_sub_10A81750(this, value);
}

/* ---------- private code */

#endif // __BLAM_INPUT_INPUT_ABSTRACTION_HPP__
