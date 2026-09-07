#ifndef __BLAM_INTERFACE_GUI_GUI_SELECTED_ITEMS_HPP__
#define __BLAM_INTERFACE_GUI_GUI_SELECTED_ITEMS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/files.hpp"

/* ---------- forward declarations */

struct c_gui_game_variant_selected_item;
struct c_gui_level_selected_item;
struct c_gui_map_selected_item;
class c_gui_selected_item;
struct s_file_reference;

/* ---------- constants */

enum e_gui_selected_item_type
{
	_gui_selected_item_level = 0,
	_gui_selected_item_difficulty,
	_gui_selected_item_map,
	_gui_selected_item_game_variant,
	_gui_selected_item_hopper,
	_gui_selected_item_saved_film,
	_gui_selected_item_screenshot,
	_gui_selected_item_network_mode,
};

/* ---------- definitions */

class c_gui_selected_item
{
	public:
	struct s_content_header
	{
		unsigned long long checksum; // 0x0
		wchar_t name[16]; // 0x8
		wchar_t description[128]; // 0x28
		char author[16]; // 0x128
		__int32 content_type; // 0x138
		__int32 user_flags; // 0x13C
		unsigned long long user_xuid; // 0x140
		unsigned long long size; // 0x148
		unsigned long long Timestamp; // 0x150
		long film_length; // 0x158
		long campaign_id; // 0x15C
		long map_id; // 0x160
		long game_engine_type; // 0x164
		long camapign_difficulty; // 0x168
		long campaign_insertion_point; // 0x16C
		unsigned long long game_id; // 0x170
	};
	static_assert(sizeof(s_content_header) == 376, "Invalid s_content_header size");
	public:
	void *ftable; // 0x0
	long unknown; // 0x4
	c_enum<long,enum e_gui_selected_item_type> item_type; // 0x8
	long map_id; // 0xC
	long location; // 0x10
	bool enabled; // 0x14
	bool corrupted; // 0x15
	unsigned char __pad0[2]; // 0x16
	s_content_header content_header; // 0x18
	c_gui_selected_item(c_gui_selected_item &); /* compiler_generated() */
	c_gui_selected_item(c_gui_selected_item const &); /* compiler_generated() */
	c_gui_selected_item(); /* compiler_generated() */
	c_gui_selected_item &operator=(c_gui_selected_item &); /* compiler_generated() */
	c_gui_selected_item &operator=(c_gui_selected_item const &); /* compiler_generated() */
};
static_assert(sizeof(c_gui_selected_item) == 400, "Invalid c_gui_selected_item size");

struct c_gui_map_selected_item :
	public c_gui_selected_item
{
	long controller_index; // 0x190
	s_file_reference file; // 0x194
	long unknown2; // 0x2A4
	c_gui_map_selected_item(c_gui_map_selected_item &); /* compiler_generated() */
	c_gui_map_selected_item(c_gui_map_selected_item const &); /* compiler_generated() */
	c_gui_map_selected_item(); /* compiler_generated() */
	c_gui_map_selected_item &operator=(c_gui_map_selected_item &); /* compiler_generated() */
	c_gui_map_selected_item &operator=(c_gui_map_selected_item const &); /* compiler_generated() */
};
static_assert(sizeof(c_gui_map_selected_item) == 680, "Invalid c_gui_map_selected_item size");

struct c_gui_level_selected_item :
	public c_gui_selected_item
{
	long campaign_id; // 0x190
	long map_id; // 0x194
	short unknown198; // 0x198
	short insertion_point; // 0x19A
	c_gui_level_selected_item(c_gui_level_selected_item &); /* compiler_generated() */
	c_gui_level_selected_item(c_gui_level_selected_item const &); /* compiler_generated() */
	c_gui_level_selected_item(); /* compiler_generated() */
	c_gui_level_selected_item &operator=(c_gui_level_selected_item &); /* compiler_generated() */
	c_gui_level_selected_item &operator=(c_gui_level_selected_item const &); /* compiler_generated() */
	unsigned char __pad0[4]; // 0x19C
};
static_assert(sizeof(c_gui_level_selected_item) == 416, "Invalid c_gui_level_selected_item size");

struct c_gui_game_variant_selected_item :
	public c_gui_selected_item
{
	long controller_index; // 0x190
	long built_in_variant_index; // 0x194
	s_file_reference file; // 0x198
	long unknown2A8; // 0x2A8
	long unknown2AC; // 0x2AC
	c_gui_game_variant_selected_item(c_gui_game_variant_selected_item &); /* compiler_generated() */
	c_gui_game_variant_selected_item(c_gui_game_variant_selected_item const &); /* compiler_generated() */
	c_gui_game_variant_selected_item(); /* compiler_generated() */
	c_gui_game_variant_selected_item &operator=(c_gui_game_variant_selected_item &); /* compiler_generated() */
	c_gui_game_variant_selected_item &operator=(c_gui_game_variant_selected_item const &); /* compiler_generated() */
};
static_assert(sizeof(c_gui_game_variant_selected_item) == 688, "Invalid c_gui_game_variant_selected_item size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_INTERFACE_GUI_GUI_SELECTED_ITEMS_HPP__
