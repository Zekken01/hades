#ifndef __BLAM_MOTOR_MOTOR_HPP__
#define __BLAM_MOTOR_MOTOR_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/objects/objects.hpp"

/* ---------- forward declarations */

struct s_motor_data;
struct s_object_data;
struct s_object_header_block_reference;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_motor_data :
	public s_object_data
{
	s_object_header_block_reference motor_tasks; // 0x178
	s_object_header_block_reference motor_state; // 0x17C
	s_object_header_block_reference action_state_storage; // 0x180
	s_motor_data(s_motor_data &); /* compiler_generated() */
	s_motor_data(s_motor_data const &); /* compiler_generated() */
	s_motor_data(); /* compiler_generated() */
	s_motor_data &operator=(s_motor_data &); /* compiler_generated() */
	s_motor_data &operator=(s_motor_data const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_motor_data) == 388, "Invalid s_motor_data size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_MOTOR_MOTOR_HPP__
