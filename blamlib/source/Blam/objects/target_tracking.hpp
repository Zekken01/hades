#ifndef __BLAM_OBJECTS_TARGET_TRACKING_HPP__
#define __BLAM_OBJECTS_TARGET_TRACKING_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/game/aim_target.hpp"

/* ---------- forward declarations */

struct c_aim_target_object;
struct c_target_tracking_system;
struct c_tracked_target;

/* ---------- constants */

enum
{
	k_tracked_targets = 2, // 0x0002
};

/* ---------- definitions */

#pragma pack(push, 4)
struct c_tracked_target
{
	public:
	enum e_state
	{
		_none = 0,
		_tracking,
		_locked,
		_target_lost,
	};
	public:
	c_aim_target_object aim_target; // 0x0
	long state; // 0xC
	float acquire_time; // 0x10
	short acquire_timer; // 0x14
	short hold_timer; // 0x16
	bool locked; // 0x18
	static long (*const initialize)(c_tracked_target *);
	static bool (*const target_matches)(c_tracked_target *, c_aim_target_object *);
};
#pragma pack(pop)
static_assert(sizeof(c_tracked_target) == 28, "Invalid c_tracked_target size");

struct c_target_tracking_system
{
	c_tracked_target tracked_targets[2]; // 0x0
	long best_target_index; // 0x38
	static c_aim_target_object *(*const get_target)(c_target_tracking_system *);
	static bool (*const is_locked)(c_target_tracking_system *);
	unsigned char __pad0[4]; // 0x3C
};
static_assert(sizeof(c_target_tracking_system) == 64, "Invalid c_target_tracking_system size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_OBJECTS_TARGET_TRACKING_HPP__
