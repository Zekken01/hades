#ifndef __BLAM_MOTOR_ACTION_SYSTEM_HPP__
#define __BLAM_MOTOR_ACTION_SYSTEM_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct s_action_definition;
struct s_action_request;
struct s_action_usage;

/* ---------- constants */

/* ---------- definitions */

struct s_action_request
{
	long action_type; // 0x0
};
static_assert(sizeof(s_action_request) == 4, "Invalid s_action_request size");

struct s_action_definition
{
	bool (*submit)(long, s_action_request const *); // 0x0
	bool (*update)(long, e_action); // 0x4
	void (*animation_event)(long, e_action, unsigned long); // 0x8
	void (*finished)(long, e_action); // 0xC
	void (*interrupt)(long, e_action); // 0x10
};
static_assert(sizeof(s_action_definition) == 20, "Invalid s_action_definition size");

struct s_action_usage
{
	char const *name; // 0x0
	short priority; // 0x4
	unsigned short flags; // 0x6
};
static_assert(sizeof(s_action_usage) == 8, "Invalid s_action_usage size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_MOTOR_ACTION_SYSTEM_HPP__
