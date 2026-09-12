#ifndef __BLAM_SAVED_GAMES_CONTENT_HPP__
#define __BLAM_SAVED_GAMES_CONTENT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct s_content_item_metadata;

/* ---------- constants */

/* ---------- definitions */

struct s_content_item_metadata
{
	unsigned long long id; // 0x0
	wchar_t name[16]; // 0x8
	char description[128]; // 0x28
	char author[16]; // 0xA8
	unsigned long content_type; // 0xB8
	bool user_is_online; // 0xBC
	unsigned long long user_id; // 0xC0
	unsigned long long content_size; // 0xC8
	unsigned long long timestamp; // 0xD0
	long unknown; // 0xD8
	long campaign_id; // 0xDC
	long map_id; // 0xE0
	long game_engine_type; // 0xE4
	unsigned long campaign_difficulty; // 0xE8
	unsigned char campaign_insertion_point; // 0xEC
	bool is_survival; // 0xED
	unsigned long long map_checksum; // 0xF0
};
static_assert(sizeof(s_content_item_metadata) == 248, "Invalid s_content_item_metadata size");
static_assert(offsetof(s_content_item_metadata, user_id) == 0xC0, "s_content_item_metadata::user_id moved when its reconstructed padding was removed");
static_assert(offsetof(s_content_item_metadata, map_checksum) == 0xF0, "s_content_item_metadata::map_checksum moved when its reconstructed padding was removed");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_SAVED_GAMES_CONTENT_HPP__
