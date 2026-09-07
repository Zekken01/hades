#ifndef __BLAM_SAVED_GAMES_CONTENT_BLF_HPP__
#define __BLAM_SAVED_GAMES_CONTENT_BLF_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/saved_games/blf.hpp"
#include "Blam/saved_games/content.hpp"

/* ---------- forward declarations */

struct s_blf_chunk_content_header;
struct s_blf_chunk_header;
struct s_content_item_metadata;

/* ---------- constants */

/* ---------- definitions */

struct s_blf_chunk_content_header :
	public s_blf_chunk_header
{
	short build_version_major; // 0xC
	short build_version_minor; // 0xE
	s_content_item_metadata metadata; // 0x10
	s_blf_chunk_content_header();
};
static_assert(sizeof(s_blf_chunk_content_header) == 264, "Invalid s_blf_chunk_content_header size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_SAVED_GAMES_CONTENT_BLF_HPP__
