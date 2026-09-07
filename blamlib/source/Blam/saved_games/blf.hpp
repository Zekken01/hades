#ifndef __BLAM_SAVED_GAMES_BLF_HPP__
#define __BLAM_SAVED_GAMES_BLF_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/objects/damage_definitions.hpp"

/* ---------- forward declarations */

struct s_blf_campaign;
struct s_blf_chunk_end_of_file;
struct s_blf_chunk_header;
struct s_blf_chunk_start_of_file;
struct s_blf_map_information;
struct s_blf_map_mission_information;
union long_string;
union tag_string;

/* ---------- constants */

enum
{
	k_blf_signature = 'flb_', // 0x666C625F
	k_number_of_campaign_map_ids = 64, // 0x0040 '@'
	k_campaign_name_length = 64, // 0x0040 '@'
	k_campaign_description_length = 128, // 0x0080
};

/* ---------- definitions */

struct s_blf_chunk_header
{
	unsigned long signature; // 0x0
	unsigned long size; // 0x4
	short version_major; // 0x8
	short version_minor; // 0xA
	void setup(unsigned long signature, unsigned long size, short version_major, short version_minor);
};
static_assert(sizeof(s_blf_chunk_header) == 12, "Invalid s_blf_chunk_header size");

struct s_blf_chunk_start_of_file :
	public s_blf_chunk_header
{
	short byte_order_marker; // 0xC
	unsigned char __pad0[2]; // 0xE
	tag_string internal_name; // 0x10
	s_blf_chunk_start_of_file();
};
static_assert(sizeof(s_blf_chunk_start_of_file) == 48, "Invalid s_blf_chunk_start_of_file size");

#pragma pack(push, 1)
struct s_blf_chunk_end_of_file :
	public s_blf_chunk_header
{
	unsigned long authentication_data_size; // 0xC
	c_enum<enum e_blf_authentication_type,char> authentication_type; // 0x10
	s_blf_chunk_end_of_file(s_blf_chunk_end_of_file &); /* compiler_generated() */
	s_blf_chunk_end_of_file(s_blf_chunk_end_of_file const &); /* compiler_generated() */
	s_blf_chunk_end_of_file();
	_inline s_blf_chunk_end_of_file &operator=(s_blf_chunk_end_of_file &&__that); /* compiler_generated() */
	s_blf_chunk_end_of_file &operator=(s_blf_chunk_end_of_file const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_blf_chunk_end_of_file) == 17, "Invalid s_blf_chunk_end_of_file size");

struct s_blf_map_mission_information
{
	bool visible; // 0x0
	bool used; // 0x1
	short zone_index; // 0x2
	unsigned char __pad0[12]; // 0x4
	wchar_t name[32][12]; // 0x10
	wchar_t description[128][12]; // 0x310
};
static_assert(sizeof(s_blf_map_mission_information) == 3856, "Invalid s_blf_map_mission_information size");

struct s_blf_map_information :
	public s_blf_chunk_header
{
	long map_id; // 0xC
	c_flags<enum e_blf_scenario_flags,long> scenario_flags; // 0x10
	wchar_t map_names[32][12]; // 0x14
	wchar_t map_descriptions[128][12]; // 0x314
	long_string map_image_path; // 0xF14
	long_string map_name_internal; // 0x1014
	long map_index; // 0x1114
	long gui_selectable_item_type; // 0x1118
	unsigned char unknown_teams1; // 0x111C
	unsigned char unknown_teams2; // 0x111D
	unsigned char team_counts[11]; // 0x111E
	unsigned char __pad0[7]; // 0x1129
	s_blf_map_mission_information insertions[9]; // 0x1130
	s_blf_map_information(s_blf_map_information &); /* compiler_generated() */
	s_blf_map_information(s_blf_map_information const &); /* compiler_generated() */
	_inline s_blf_map_information(); /* compiler_generated() */
	s_blf_map_information &operator=(s_blf_map_information &); /* compiler_generated() */
	s_blf_map_information &operator=(s_blf_map_information const &); /* compiler_generated() */
};
static_assert(sizeof(s_blf_map_information) == 39104, "Invalid s_blf_map_information size");

struct s_blf_campaign :
	public s_blf_chunk_header
{
	long campaign_id; // 0xC
	unsigned long type; // 0x10
	wchar_t names[64][12]; // 0x14
	wchar_t descriptions[128][12]; // 0x614
	long map_ids[64]; // 0x1214
	unsigned char __pad0[4]; // 0x1314
};
static_assert(sizeof(s_blf_campaign) == 4888, "Invalid s_blf_campaign size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_SAVED_GAMES_BLF_HPP__
