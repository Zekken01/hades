#ifndef __BLAM_AI_ZONE_HPP__
#define __BLAM_AI_ZONE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"

/* ---------- forward declarations */

struct s_zone_area_definition;
union tag_string;

/* ---------- constants */

/* ---------- definitions */

struct s_zone_area_definition
{
	tag_string name; // 0x0
};
static_assert(sizeof(s_zone_area_definition) == 32, "Invalid s_zone_area_definition size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_AI_ZONE_HPP__
