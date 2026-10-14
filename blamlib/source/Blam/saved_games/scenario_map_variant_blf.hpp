#ifndef __BLAM_SAVED_GAMES_SCENARIO_MAP_VARIANT_BLF_HPP__
#define __BLAM_SAVED_GAMES_SCENARIO_MAP_VARIANT_BLF_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/saved_games/blf.hpp"

/* ---------- forward declarations */

struct s_blf_chunk_header;
struct s_blf_chunk_mapv_tag_names;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_blf_chunk_mapv_tag_names :
	public s_blf_chunk_header
{
	char names[256][256]; // 0xC
	_inline s_blf_chunk_mapv_tag_names();
};
#pragma pack(pop)
static_assert(sizeof(s_blf_chunk_mapv_tag_names) == 65548, "Invalid s_blf_chunk_mapv_tag_names size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

inline s_blf_chunk_mapv_tag_names::s_blf_chunk_mapv_tag_names() // 0x10AC85E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_blf_chunk_mapv_tag_names@@QAE@XZ");
	// s_blf_chunk_mapv_tag_names *const this;

	setup(0x7461676E, 0x1000C, 1, 0);
}

/* ---------- private code */

#endif // __BLAM_SAVED_GAMES_SCENARIO_MAP_VARIANT_BLF_HPP__
