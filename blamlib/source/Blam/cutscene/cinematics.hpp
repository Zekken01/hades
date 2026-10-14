#ifndef __BLAM_CUTSCENE_CINEMATICS_HPP__
#define __BLAM_CUTSCENE_CINEMATICS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"

/* ---------- forward declarations */

struct real_vector3d;
struct s_cinematic_globals;
struct s_cinematic_new_globals;

/* ---------- constants */

/* ---------- definitions */

struct s_cinematic_new_globals
{
	public:
#pragma pack(push, 4)
	struct s_cinematic_clip
	{
		real_point3d plane_center; // 0x0
		real_vector3d plane_direction; // 0xC
		long game_time_start; // 0x18
		long game_time_end; // 0x1C
		long objects_count; // 0x20
		unsigned long object_indices[24]; // 0x24
	};
#pragma pack(pop)
	static_assert(sizeof(s_cinematic_clip) == 132, "Invalid s_cinematic_clip size");
	public:
	long field_00; // 0x0
	long scene_tag_index; // 0x4
	long field_08[1503]; // 0x8
	long active_clip_count; // 0x1784
	s_cinematic_clip clips[32]; // 0x1788
};
static_assert(sizeof(s_cinematic_new_globals) == 10248, "Invalid s_cinematic_new_globals size");

#pragma pack(push, 4)
struct s_cinematic_globals
{
	public:
	struct s_delayed_titles
	{
		short index; // 0x0
		short current_up_time; // 0x2
		short field_4; // 0x4
	};
	// static_assert(sizeof(s_delayed_titles) == 6, "Invalid s_delayed_titles size");
	// Withheld: the type inventory does not describe this type, so its
	// padding could not be reconstructed.
	public:
	float letter_box_coverage; // 0x0
	bool letter_box_enabled; // 0x4
	bool in_progress; // 0x5
	bool skip_allowed; // 0x6
	bool supressing_bsp_object_creation; // 0x7
	s_delayed_titles delayed_titles[4]; // 0x8
	unsigned long subtitle_string_id; // 0x20
	float field_24; // 0x24
	float field_28; // 0x28
	short field_2C; // 0x2C
	bool outro_started; // 0x2E
	bool unknown; // 0x2F
	bool fade_active_for_user_skip; // 0x30
	long fade_start_time; // 0x34
	long cinematic_fade_for_user_skip_end_time; // 0x38
};
#pragma pack(pop)
// static_assert(sizeof(s_cinematic_globals) == 60, "Invalid s_cinematic_globals size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_CUTSCENE_CINEMATICS_HPP__
