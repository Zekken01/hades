#ifndef __BLAM_WIDGETS_MUFFIN_DEFINITIONS_HPP__
#define __BLAM_WIDGETS_MUFFIN_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/function_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

class c_function_definition;
struct s_muffin_definition;
struct s_muffin_location;
struct s_muffin_type;
struct s_tag_reference;

/* ---------- constants */

/* ---------- definitions */

struct s_muffin_location
{
	unsigned long location_name; // 0x0
	short muffinage_chance; // 0x4
	short allowed_muffin_types; // 0x6
};
static_assert(sizeof(s_muffin_location) == 8, "Invalid s_muffin_location size");

struct s_muffin_type
{
	short mesh_index; // 0x0
	c_enum<enum e_muffin_type_flags,short> flags; // 0x2
	float spawn_delay_min; // 0x4
	float spawn_delay_max; // 0x8
	float initial_scale_min; // 0xC
	float initial_scale_max; // 0x10
	c_function_definition initial_growth; // 0x14
	float growth_time; // 0x28
	c_function_definition periodic_noise; // 0x2C
	float jiggle; // 0x40
	float jiggle_spring_length; // 0x44
	float jiggle_spring_strength; // 0x48
	float jiggle_velocity_dampening; // 0x4C
	float jiggle_max_velocity; // 0x50
	float lifetime_min; // 0x54
	float lifetime_max; // 0x58
	float immortality_chance; // 0x5C
	s_tag_reference effect; // 0x60
	s_muffin_type(s_muffin_type &); /* compiler_generated() */
	s_muffin_type(s_muffin_type const &); /* compiler_generated() */
	s_muffin_type(); /* compiler_generated() */
	s_muffin_type &operator=(s_muffin_type &); /* compiler_generated() */
	s_muffin_type &operator=(s_muffin_type const &); /* compiler_generated() */
};
static_assert(sizeof(s_muffin_type) == 112, "Invalid s_muffin_type size");

struct s_muffin_definition
{
	s_tag_reference render_model; // 0x0
	c_tag_block<unsigned long> render_model_permutation_names; // 0x10
	long render_model_permutation_name_valid_count; // 0x1C
	c_tag_block<s_muffin_location> locations; // 0x20
	c_tag_block<s_muffin_type> muffin_types; // 0x2C
	static s_muffin_definition *(*get)(long);
};
static_assert(sizeof(s_muffin_definition) == 56, "Invalid s_muffin_definition size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_WIDGETS_MUFFIN_DEFINITIONS_HPP__
