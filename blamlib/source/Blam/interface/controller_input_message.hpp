#ifndef __BLAM_INTERFACE_CONTROLLER_INPUT_MESSAGE_HPP__
#define __BLAM_INTERFACE_CONTROLLER_INPUT_MESSAGE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct c_controller_input_message;
struct c_message;

/* ---------- constants */

/* ---------- definitions */

struct c_message
{
	virtual ~c_message() = 0;
	long timestamp; // 0x4
	long message_type; // 0x8
	c_message(c_message const &); /* compiler_generated() */
	c_message(); /* compiler_generated() */
	c_message &operator=(c_message const &); /* compiler_generated() */
};
static_assert(sizeof(c_message) == 12, "Invalid c_message size");

struct c_controller_input_message :
	public c_message
{
	long screen_name; // 0xC
	long controller_index; // 0x10
	long input_user_index; // 0x14
	long event_type; // 0x18
	long button; // 0x1C
	c_controller_input_message(c_controller_input_message &); /* compiler_generated() */
	c_controller_input_message(c_controller_input_message const &); /* compiler_generated() */
	c_controller_input_message(); /* compiler_generated() */
	virtual ~c_controller_input_message() = default; /* compiler_generated() */
	c_controller_input_message &operator=(c_controller_input_message &); /* compiler_generated() */
	c_controller_input_message &operator=(c_controller_input_message const &); /* compiler_generated() */
	unsigned char __pad0[8]; // 0x20
};
static_assert(sizeof(c_controller_input_message) == 40, "Invalid c_controller_input_message size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_INTERFACE_CONTROLLER_INPUT_MESSAGE_HPP__
