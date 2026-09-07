#ifndef __BLAM_INTERFACE_CONTROLLER_HPP__
#define __BLAM_INTERFACE_CONTROLLER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/interface/player_profile.hpp"

/* ---------- forward declarations */

class c_controller_interface;
class c_player_profile_interface;

/* ---------- constants */

/* ---------- definitions */

class c_controller_interface
{
public:
	c_player_profile_interface *get_player_profile_interface();
};
static_assert(sizeof(c_controller_interface) == 1, "Invalid c_controller_interface size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_INTERFACE_CONTROLLER_HPP__
