#ifndef __BLAM_TAG_FILES_FILES_HPP__
#define __BLAM_TAG_FILES_FILES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/objects/damage_definitions.hpp"

/* ---------- forward declarations */

struct s_file_handle;
struct s_file_reference;
struct s_file_time;

/* ---------- constants */

enum
{
	k_maximum_filename_length = 256, // 0x0100
};

enum e_file_reference_location
{
	_file_reference_location_none = -1,
	_file_reference_location_application_relative = 0,
	_file_reference_location_tags,
	_file_reference_location_absolute,
	k_number_of_file_reference_locations,
};

/* ---------- definitions */

struct s_file_handle
{
	unsigned long handle; // 0x0
};
static_assert(sizeof(s_file_handle) == 4, "Invalid s_file_handle size");

struct s_file_time
{
	unsigned long low_date_time; // 0x0
	unsigned long high_date_time; // 0x4
};
static_assert(sizeof(s_file_time) == 8, "Invalid s_file_time size");

struct s_file_reference
{
	unsigned long signature; // 0x0
	c_flags<enum e_file_reference_flags,unsigned short> flags; // 0x4
	c_enum<enum e_file_reference_location,short> location; // 0x6
	char filename[256]; // 0x8
	unsigned long handle; // 0x108
	unsigned long position; // 0x10C
	s_file_reference(s_file_reference &); /* compiler_generated() */
	_inline s_file_reference(s_file_reference const &__that); /* compiler_generated() */
	_inline s_file_reference() = default; /* compiler_generated() */
	s_file_reference &operator=(s_file_reference &); /* compiler_generated() */
	_inline s_file_reference &operator=(s_file_reference const &__that); /* compiler_generated() */
};
static_assert(sizeof(s_file_reference) == 272, "Invalid s_file_reference size");

/* ---------- prototypes */

extern void invalidate_file_handle(s_file_handle *handle);
extern bool file_is_open(s_file_reference const *reference);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_TAG_FILES_FILES_HPP__
