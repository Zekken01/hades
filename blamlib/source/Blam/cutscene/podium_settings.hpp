#ifndef __BLAM_CUTSCENE_PODIUM_SETTINGS_HPP__
#define __BLAM_CUTSCENE_PODIUM_SETTINGS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/items/equipment_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct s_podium_biped;
struct s_podium_settings;
struct s_tag_reference;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_podium_biped
{
	float offset_x; // 0x0
	float offset_y; // 0x4
	float offset_z; // 0x8
	float orientation_offset_y; // 0xC
	float orientation_offset_p; // 0x10
	float orientation_offset_r; // 0x14
	__int32 spawn_delay; // 0x18
	s_tag_reference spawn_effect; // 0x1C
};
#pragma pack(pop)
static_assert(sizeof(s_podium_biped) == 44, "Invalid s_podium_biped size");

#pragma pack(push, 4)
struct s_podium_settings
{
	float camera_offset_x; // 0x0
	float camera_offset_y; // 0x4
	float camera_offset_z; // 0x8
	float camera_orientation_offset_y; // 0xC
	float camera_orientation_offset_p; // 0x10
	float camera_orientation_offset_r; // 0x14
	float camera_fov; // 0x18
	__int32 tick_delay; // 0x1C
	s_tag_reference unknown; // 0x20
	c_tag_block<s_podium_biped> podium_bipeds; // 0x30
};
#pragma pack(pop)
static_assert(sizeof(s_podium_settings) == 60, "Invalid s_podium_settings size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_CUTSCENE_PODIUM_SETTINGS_HPP__
