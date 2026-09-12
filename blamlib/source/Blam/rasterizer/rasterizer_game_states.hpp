#ifndef __BLAM_RASTERIZER_RASTERIZER_GAME_STATES_HPP__
#define __BLAM_RASTERIZER_RASTERIZER_GAME_STATES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct s_rasterizer_game_states;

/* ---------- constants */

/* ---------- definitions */

struct s_rasterizer_game_states
{
	bool motion_blur_enabled; // 0x0
	bool render_atmosphere_fog_enabled; // 0x1
	bool render_patchy_fog_enabled; // 0x2
	bool render_weather_enabled; // 0x3
	bool render_cinematic_motion_blur_enabled; // 0x4
	long weather_effects[64]; // 0x8
	static void (*motion_blur)(bool);
	static void (*render_atmosphere_fog)(bool);
	static void (*render_patchy_fog)(bool);
	static void (*render_weather)(bool);
	static void (*render_cinematic_motion_blur)(bool);
	static bool get_motion_blur();
	static bool get_render_atmosphere_fog();
	static bool get_render_patchy_fog();
	static bool get_render_weather();
	static bool get_render_cinematic_motion_blur();
};
static_assert(sizeof(s_rasterizer_game_states) == 264, "Invalid s_rasterizer_game_states size");
static_assert(offsetof(s_rasterizer_game_states, weather_effects) == 0x8, "s_rasterizer_game_states::weather_effects moved when its reconstructed padding was removed");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_RASTERIZER_RASTERIZER_GAME_STATES_HPP__
