#ifndef __BLAM_GAME_GAME_TIME_HPP__
#define __BLAM_GAME_GAME_TIME_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct s_game_tick_time_samples;
struct s_game_time_globals;

/* ---------- constants */

/* ---------- definitions */

struct s_game_time_globals
{
	bool initialized : 8; // 0x0
	unsigned short flags; // 0x2
	unsigned short tick_rate; // 0x4
	float tick_length; // 0x8
	long game_tick; // 0xC
	float game_speed; // 0x10
};
static_assert(sizeof(s_game_time_globals) == 20, "Invalid s_game_time_globals size");
static_assert(offsetof(s_game_time_globals, flags) == 0x2, "s_game_time_globals::flags moved when its reconstructed padding was removed");
static_assert(offsetof(s_game_time_globals, tick_length) == 0x8, "s_game_time_globals::tick_length moved when its reconstructed padding was removed");

struct s_game_tick_time_samples
{
	unsigned long publishing_flags; // 0x0
	float delta; // 0x4
	float game_delta; // 0x8
	float frame_delta; // 0xC
	long update_steps; // 0x10
	long field_14; // 0x14
};
static_assert(sizeof(s_game_tick_time_samples) == 24, "Invalid s_game_tick_time_samples size");

/* ---------- prototypes */

extern s_game_time_globals *game_time_get_globals();
extern void game_time_set_speed(float speed);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_GAME_GAME_TIME_HPP__
