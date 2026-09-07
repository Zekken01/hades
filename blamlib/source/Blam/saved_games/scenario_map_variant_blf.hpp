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

extern s_blf_chunk_mapv_tag_names* _sub_10AC85E0(s_blf_chunk_mapv_tag_names *const);
_inline s_blf_chunk_mapv_tag_names::s_blf_chunk_mapv_tag_names() // 0x10AC85E0
{
	mangled_x86(MANGLED_TODO, "??0s_blf_chunk_mapv_tag_names@@QAE@XZ");
	// s_blf_chunk_mapv_tag_names *const this;
	todo("implement");
	_sub_10AC85E0(this);
}

/* ---------- private code */

#endif // __BLAM_SAVED_GAMES_SCENARIO_MAP_VARIANT_BLF_HPP__
