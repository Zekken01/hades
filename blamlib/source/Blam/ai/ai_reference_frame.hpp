#ifndef __BLAM_AI_AI_REFERENCE_FRAME_HPP__
#define __BLAM_AI_AI_REFERENCE_FRAME_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"


/* ---------- forward declarations */

class c_ai_point3d;
struct s_scenario_structure_bsp_reference;

/* ---------- constants */

/* ---------- definitions */

class c_ai_point3d
{
public:
	c_ai_point3d(c_ai_point3d &); /* compiler_generated() */
	c_ai_point3d(c_ai_point3d const &); /* compiler_generated() */
	c_ai_point3d();
private:
	real_point3d position; // 0x0
	c_tag_block_index<void,short> reference_frame; // 0xC
	c_tag_block_index<s_scenario_structure_bsp_reference,short> bsp; // 0xE
};
static_assert(sizeof(c_ai_point3d) == 16, "Invalid c_ai_point3d size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_AI_AI_REFERENCE_FRAME_HPP__
