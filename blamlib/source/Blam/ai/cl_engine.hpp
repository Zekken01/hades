#ifndef __BLAM_AI_CL_ENGINE_HPP__
#define __BLAM_AI_CL_ENGINE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct real_euler_angles2d;
struct s_cs_point;
struct s_cs_point_set;
struct s_scenario_editor_folder;
struct s_scenario_structure_bsp_reference;
struct s_zone_definition;
union tag_string;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_cs_point
{
	tag_string name; // 0x0
	real_point3d position; // 0x20
	short reference_frame; // 0x2C
	c_tag_block_index<s_scenario_structure_bsp_reference,short> bsp; // 0x2E
	c_tag_block_index<s_zone_definition,short> zone; // 0x30
	short surface_index; // 0x32
	real_euler_angles2d facing; // 0x34
	s_cs_point(s_cs_point &); /* compiler_generated() */
	s_cs_point(s_cs_point const &); /* compiler_generated() */
	s_cs_point(); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_cs_point) == 60, "Invalid s_cs_point size");

struct s_cs_point_set
{
	tag_string name; // 0x0
	c_tag_block<s_cs_point> points; // 0x20
	c_tag_block_index<s_scenario_structure_bsp_reference,short> bsp; // 0x2C
	short manual_reference_frame; // 0x2E
	c_flags<enum e_cs_point_set_flags,long> flags; // 0x30
	c_tag_block_index<s_scenario_editor_folder,short> editor_folder; // 0x34
	s_cs_point_set(s_cs_point_set &); /* compiler_generated() */
	s_cs_point_set(s_cs_point_set const &); /* compiler_generated() */
	s_cs_point_set(); /* compiler_generated() */
	s_cs_point_set &operator=(s_cs_point_set &); /* compiler_generated() */
	s_cs_point_set &operator=(s_cs_point_set const &); /* compiler_generated() */
	unsigned char __pad0[2]; // 0x36
};
static_assert(sizeof(s_cs_point_set) == 56, "Invalid s_cs_point_set size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_AI_CL_ENGINE_HPP__
