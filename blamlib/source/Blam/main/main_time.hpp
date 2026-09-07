#ifndef __BLAM_MAIN_MAIN_TIME_HPP__
#define __BLAM_MAIN_MAIN_TIME_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct s_main_time_globals;

/* ---------- constants */

/* ---------- definitions */

struct s_main_time_globals
{
	bool unknown1; // 0x0
	bool unknown2; // 0x1
	unsigned char __pad0[2]; // 0x2
	long last_game_time; // 0x4
	long long last_milliseconds; // 0x8
	long long last_cpu_ticks; // 0x10
	long long unknown_blank_index; // 0x18
	long long target_display_blank_index; // 0x20
	long long input_collection_time; // 0x28
	long long publishing_start_time; // 0x30
	long long publishing_end_time; // 0x38
};
static_assert(sizeof(s_main_time_globals) == 64, "Invalid s_main_time_globals size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_MAIN_MAIN_TIME_HPP__
