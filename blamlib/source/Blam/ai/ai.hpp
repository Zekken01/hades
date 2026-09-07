#ifndef __BLAM_AI_AI_HPP__
#define __BLAM_AI_AI_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/math/integer_math_definitions.hpp"

/* ---------- forward declarations */

struct s_ai_conditions;
struct short_bounds;

/* ---------- constants */

/* ---------- definitions */

struct s_ai_conditions
{
	c_flags<enum e_game_difficulty_level,unsigned short> difficulty_flags; // 0x0
	unsigned char __pad0[2]; // 0x2
	short_bounds round_range; // 0x4
	short_bounds set_range; // 0x8
	s_ai_conditions(s_ai_conditions &); /* compiler_generated() */
	s_ai_conditions(s_ai_conditions const &); /* compiler_generated() */
	s_ai_conditions(); /* compiler_generated() */
	s_ai_conditions &operator=(s_ai_conditions &); /* compiler_generated() */
	s_ai_conditions &operator=(s_ai_conditions const &); /* compiler_generated() */
};
static_assert(sizeof(s_ai_conditions) == 12, "Invalid s_ai_conditions size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_AI_AI_HPP__
