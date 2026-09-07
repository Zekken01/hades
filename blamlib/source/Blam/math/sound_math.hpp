#ifndef __BLAM_MATH_SOUND_MATH_HPP__
#define __BLAM_MATH_SOUND_MATH_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct real_decibel;

/* ---------- constants */

/* ---------- definitions */

struct real_decibel
{
	float value; // 0x0
	static real_decibel from_real(float);
	float to_real() const;
	real_decibel &operator+=(real_decibel const &);
	real_decibel &operator-=(real_decibel const &);
	operator float() const;
};
static_assert(sizeof(real_decibel) == 4, "Invalid real_decibel size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_MATH_SOUND_MATH_HPP__
