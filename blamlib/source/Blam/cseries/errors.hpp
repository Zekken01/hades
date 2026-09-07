#ifndef __BLAM_CSERIES_ERRORS_HPP__
#define __BLAM_CSERIES_ERRORS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/objects/damage_definitions.hpp"

/* ---------- constants */

enum e_error_message_priority
{
	_error_message_priority_out_of_memory = 0,
	_error_message_priority_warning,
	_error_message_priority_assert,
	_error_message_priority_critical,
	k_number_of_error_message_priorities,
};

/* ---------- definitions */

/* ---------- prototypes */

extern void error(c_enum<enum e_error_message_priority,int> priority, char const *message, ...);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_CSERIES_ERRORS_HPP__
