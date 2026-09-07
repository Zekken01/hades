#ifndef __BLAM_INTERFACE_PLAYER_PROFILE_HPP__
#define __BLAM_INTERFACE_PLAYER_PROFILE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

class c_player_profile_interface;

/* ---------- constants */

/* ---------- definitions */

class c_player_profile_interface
{
public:
	void set_last_campaign_played_time(long campaign_game_mode, unsigned long long time, bool unused);
};
static_assert(sizeof(c_player_profile_interface) == 1, "Invalid c_player_profile_interface size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_INTERFACE_PLAYER_PROFILE_HPP__
