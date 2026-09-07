#ifndef __BLAM_CACHE_RESTRICTED_MEMORY_REGIONS_HPP__
#define __BLAM_CACHE_RESTRICTED_MEMORY_REGIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- constants */

enum e_restricted_memory_region
{
	_game_state_header_region = 0,
	_game_state_update_region,
	_game_state_render_region,
	_game_state_shared_region,
	_global_render_data_region,
};

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_CACHE_RESTRICTED_MEMORY_REGIONS_HPP__
