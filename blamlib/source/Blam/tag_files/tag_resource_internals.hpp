#ifndef __BLAM_TAG_FILES_TAG_RESOURCE_INTERNALS_HPP__
#define __BLAM_TAG_FILES_TAG_RESOURCE_INTERNALS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct s_tag_block;
struct s_tag_data;
struct s_tag_reference;
struct s_tag_resource;
struct s_tag_resource_interop_location;
struct s_tag_resource_page;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_tag_resource_page
{
	unsigned short identifier; // 0x0
	c_flags<enum e_tag_resource_page_flags,unsigned char> page_flags; // 0x2
	char compression_codec_index; // 0x3
	long index; // 0x4
	unsigned long compressed_block_size; // 0x8
	unsigned long uncompressed_block_size; // 0xC
	long crc_checksum; // 0x10
	short block_asset_count; // 0x14
	s_tag_resource_page(s_tag_resource_page &); /* compiler_generated() */
	s_tag_resource_page(s_tag_resource_page const &); /* compiler_generated() */
	s_tag_resource_page(); /* compiler_generated() */
	s_tag_resource_page &operator=(s_tag_resource_page &); /* compiler_generated() */
	s_tag_resource_page &operator=(s_tag_resource_page const &); /* compiler_generated() */
	unsigned char __pad0[14]; // 0x16
};
#pragma pack(pop)
static_assert(sizeof(s_tag_resource_page) == 36, "Invalid s_tag_resource_page size");

struct s_tag_resource_interop_location
{
	unsigned long address; // 0x0
	long type; // 0x4
};
static_assert(sizeof(s_tag_resource_interop_location) == 8, "Invalid s_tag_resource_interop_location size");

#pragma pack(push, 4)
struct s_tag_resource :
	public s_tag_resource_page
{
	s_tag_reference parent_tag; // 0x24
	unsigned short salt; // 0x34
	char resource_type_index; // 0x36
	c_flags<enum e_tag_resource_flags,unsigned char> flags; // 0x37
	s_tag_data definition_data; // 0x38
	unsigned long definition_address; // 0x4C
	s_tag_block resource_fixups; // 0x50
	c_tag_block<s_tag_resource_interop_location> interop_locations; // 0x5C
	s_tag_resource(s_tag_resource &); /* compiler_generated() */
	s_tag_resource(s_tag_resource const &); /* compiler_generated() */
	s_tag_resource(); /* compiler_generated() */
	s_tag_resource &operator=(s_tag_resource &); /* compiler_generated() */
	s_tag_resource &operator=(s_tag_resource const &); /* compiler_generated() */
	unsigned char __pad0[4]; // 0x68
};
#pragma pack(pop)
static_assert(sizeof(s_tag_resource) == 108, "Invalid s_tag_resource size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_TAG_FILES_TAG_RESOURCE_INTERNALS_HPP__
