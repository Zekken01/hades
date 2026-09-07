#ifndef __BLAM_MATH_FUNCTION_DEFINITIONS_HPP__
#define __BLAM_MATH_FUNCTION_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/color_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class c_function_definition;
struct c_periodic_function_compact;
struct real_rgb_color;
struct s_function_definition_internal;
struct s_tag_data;

/* ---------- constants */

enum e_periodic_function
{
	_periodic_function_one = 0,
	_periodic_function_zero,
	_periodic_function_cosine,
	_periodic_function_consine_variable_period,
	_periodic_function_diagonal_wave,
	_periodic_function_diagnal_wave_variable_period,
	_periodic_function_slide,
	_periodic_function_slide_variable_period,
	_periodic_function_noise,
	_periodic_function_jitter,
	_periodic_function_wander,
	_periodic_function_spark,
};

enum e_function_flags
{
	_function_flags_ranged_bit = 0, // 0x0000
	_function_flags_clamped_bit = 2, // 0x0002
	_function_flags_exclusion_bit = 3, // 0x0003
};

/* ---------- definitions */

struct s_function_definition_internal
{
	char type; // 0x0
	unsigned char flags; // 0x1
	char color_graph_type; // 0x2
	unsigned char __pad0[1]; // 0x3
	union
	{
		struct
		{
			float clamp_range_min; // 0x4
			float clamp_range_max; // 0x8
		};
		unsigned long colors[4]; // 0x4
	};
	float exclusion_min; // 0x14
	float exclusion_max; // 0x18
	long data_size; // 0x1C
};
static_assert(sizeof(s_function_definition_internal) == 32, "Invalid s_function_definition_internal size");

struct c_periodic_function_compact
{
	long function; // 0x0
	float frequency; // 0x4
	float phase; // 0x8
	float amplitude_min; // 0xC
	float amplitude_max; // 0x10
};
static_assert(sizeof(c_periodic_function_compact) == 20, "Invalid c_periodic_function_compact size");

#pragma pack(push, 4)
class c_function_definition
{
public:
	public:
	enum e_function_type
	{
		_function_type_identity = 0,
		_function_type_constant,
		_function_type_transition,
		_function_type_periodic,
		_function_type_linear,
		_function_type_linearKey,
		_function_type_multi_linear_key,
		_function_type_spline,
		_function_type_multi_spline,
		_function_type_exponent,
		_function_type_spline2,
		k_number_of_function_types,
	};
	public:
	e_function_type get_type() const;
	float evaluate_scalar(float x, float t) const;
	void evaluate_color(float x, float t, real_rgb_color *out_color) const;
	static float (*const evaluate_legacy)(s_tag_data *, float, float);
	static char (*const get_function_type)(s_tag_data *);
	s_tag_data m_data; // 0x0
	c_function_definition(c_function_definition &); /* compiler_generated() */
	c_function_definition(c_function_definition const &); /* compiler_generated() */
	_inline c_function_definition(); /* compiler_generated() */
	c_function_definition &operator=(c_function_definition &); /* compiler_generated() */
	c_function_definition &operator=(c_function_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(c_function_definition) == 20, "Invalid c_function_definition size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_MATH_FUNCTION_DEFINITIONS_HPP__
