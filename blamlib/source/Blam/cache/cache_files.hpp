#ifndef __BLAM_CACHE_CACHE_FILES_HPP__
#define __BLAM_CACHE_CACHE_FILES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/tag_files/tag_resource_internals.hpp"
#include "Forge/ForgeUndo.hpp"
#include "Utils/StlUtil.hpp"

/* ---------- forward declarations */

class c_file_reference;
struct s_cache_file_header;
struct s_cache_file_secure_memory;
struct s_cache_file_segment_header;
struct s_cache_file_tag_globals;
struct s_cache_tag_instance;
struct s_cached_map_file;
struct s_file_handle;
struct s_file_time;
struct s_tag_group;
struct s_tag_resource;
struct s_tag_resource_data;

/* ---------- constants */

enum
{
	k_maximum_number_of_cache_tag_instances = 65535, // 0xFFFF
	k_cache_file_tag_memory_size = 78643200, // 0x04B00000
	k_number_of_cached_map_files = 15, // 0x000F
};

/* ---------- definitions */

struct s_cache_file_header
{
	__int32 header_signature; // 0x0
	__int32 version; // 0x4
	__int32 size; // 0x8
	__int32 field_C; // 0xC
	__int32 field_10; // 0x10
	__int32 field_14; // 0x14
	__int32 field_18; // 0x18
	char map_path[256]; // 0x1C
	char build_info[32]; // 0x11C
	short map_type; // 0x13C
	short field_13E; // 0x13E
	char field_140; // 0x140
	char is_tracked_build; // 0x141
	char field_142; // 0x142
	char field_143; // 0x143
	s_file_time last_modification_date; // 0x144
	__int32 field_14C; // 0x14C
	__int32 field_150; // 0x150
	__int32 field_154; // 0x154
	__int32 field_158; // 0x158
	__int32 field_15C; // 0x15C
	__int32 field_160; // 0x160
	__int32 field_164; // 0x164
	__int32 valid_cache_file_section_mask; // 0x168
	s_file_time resources_last_modification_date; // 0x16C
	s_file_time file_times[6]; // 0x174
	char map_name[32]; // 0x1A4
	__int32 field_1C4; // 0x1C4
	char scenario_path[256]; // 0x1C8
	__int32 minor_version; // 0x2C8
	__int32 tag_name_count; // 0x2CC
	__int32 tag_name_buffer_offset; // 0x2D0
	__int32 tag_name_buffer_size; // 0x2D4
	__int32 tag_name_indices_offset; // 0x2D8
	__int32 field_2DC; // 0x2DC
	__int32 field_2E0; // 0x2E0
	__int32 field_2E4; // 0x2E4
	char field_2E8[32]; // 0x2E8
	__int32 field_308; // 0x308
	__int32 field_30C; // 0x30C
	__int32 field_310; // 0x310
	__int32 field_314; // 0x314
	__int32 field_318; // 0x318
	__int32 field_31C; // 0x31C
	char hash[20]; // 0x320
	char rsa_signature[256]; // 0x334
	char cache_file_sections[48]; // 0x434
	__int32 field_464; // 0x464
	short field_468; // 0x468
	short field_46A; // 0x46A
	__int32 compression_guid; // 0x46C
	char field_470[8960]; // 0x470
	__int32 field_2770; // 0x2770
	__int32 field_2774; // 0x2774
	__int32 field_2778; // 0x2778
	__int32 field_277C; // 0x277C
	__int32 field_2780; // 0x2780
	__int32 field_2784; // 0x2784
	__int32 field_2788; // 0x2788
	__int32 field_278C; // 0x278C
	__int32 field_2790; // 0x2790
	char field_2794[360]; // 0x2794
	char field_28FC[1264]; // 0x28FC
	__int32 map_id; // 0x2DEC
	__int32 scenario_tag_index; // 0x2DF0
	char field_2DF4[1432]; // 0x2DF4
	__int32 footer_signature; // 0x338C
};
static_assert(sizeof(s_cache_file_header) == 13200, "Invalid s_cache_file_header size");

struct s_cached_map_file
{
	s_file_handle file_handle; // 0x0
	long field_4; // 0x4
	s_cache_file_header file_header; // 0x8
	s_file_handle indirect_file_handle; // 0x3398
	s_file_handle file_handle2; // 0x339C
};
static_assert(sizeof(s_cached_map_file) == 13216, "Invalid s_cached_map_file size");

#pragma pack(push, 4)
struct s_cache_tag_instance
{
	union
	{
		unsigned long checksum; // 0x0
		char const *name; // 0x0
	};
	unsigned long size; // 0x4
	unsigned short dependency_count; // 0x8
	unsigned short fixup_count; // 0xA
	unsigned short resource_fixup_count; // 0xC
	unsigned short tag_reference_fixup_count; // 0xE
	unsigned long definition_offset; // 0x10
	s_tag_group group; // 0x14
	_inline bool is_empty() const;
};
#pragma pack(pop)
static_assert(sizeof(s_cache_tag_instance) == 36, "Invalid s_cache_tag_instance size");

struct s_cache_file_segment_header
{
	unsigned char __pad0[4]; // 0x0
	unsigned long table_offset; // 0x4
	unsigned long table_count; // 0x8
	unsigned char __pad1[4]; // 0xC
	unsigned long long guid; // 0x10
	unsigned char __pad2[8]; // 0x18
};
static_assert(sizeof(s_cache_file_segment_header) == 32, "Invalid s_cache_file_segment_header size");

#pragma pack(push, 4)
struct s_tag_resource_data
{
	long resource_count; // 0x0
	s_tag_resource **resources; // 0x4
	long field_8; // 0x8
	unsigned long resource_memory_used; // 0xC
	long field_10; // 0x10
	char field_14[360]; // 0x14
};
#pragma pack(pop)
static_assert(sizeof(s_tag_resource_data) == 380, "Invalid s_tag_resource_data size");

struct s_cache_file_secure_memory
{
	s_cache_file_header header; // 0x0
	__int32 valid; // 0x3390
	unsigned long size; // 0x3394
	void *data; // 0x3398
	unsigned char input_hash[20]; // 0x339C
	unsigned char hash_buffer[1024]; // 0x33B0
	unsigned char result_hash[20]; // 0x37B0
	unsigned char rsa_signature[256]; // 0x37C4
	__int32 field_38C4; // 0x38C4
};
static_assert(sizeof(s_cache_file_secure_memory) == 14536, "Invalid s_cache_file_secure_memory size");

struct s_cache_file_tag_globals
{
	public:
	struct s_unknown_fixups
	{
		long count; // 0x0
		unsigned long *fixups; // 0x4
	};
	// static_assert(sizeof(s_unknown_fixups) == 8, "Invalid s_unknown_fixups size");
	// Withheld: the type inventory does not describe this type, so its
	// padding could not be reconstructed.
	public:
	bool initialized; // 0x0
	unsigned char tag_load_sequence_number; // 0x1
	unsigned long *file_offsets; // 0x4
	s_cache_tag_instance **instances; // 0x8
	long *index_to_absolute_index_map; // 0xC
	long *absolute_index_index_map; // 0x10
	long loaded_instance_count; // 0x14
	long total_instance_count; // 0x18
	void *memory; // 0x1C
	unsigned long memory_used; // 0x20
	unsigned long memory_size; // 0x24
	s_cache_file_header cache_file_header; // 0x28
	c_file_reference cache_file_reference; // 0x33B8
	s_tag_resource_data *tag_resource_data; // 0x34C8
	long tag_resource_counts_by_location[5]; // 0x34CC
	struct
	{
		long count; // 0x0
		unsigned long *fixups; // 0x4
	} unknown_fixups; // 0x34E0
	char const *resource_locations[5]; // 0x34E8
	s_cache_file_tag_globals(s_cache_file_tag_globals &); /* compiler_generated() */
	s_cache_file_tag_globals(s_cache_file_tag_globals const &); /* compiler_generated() */
	s_cache_file_tag_globals(); /* compiler_generated() */
	~s_cache_file_tag_globals(); /* compiler_generated() */
	s_cache_file_tag_globals &operator=(s_cache_file_tag_globals &); /* compiler_generated() */
	s_cache_file_tag_globals &operator=(s_cache_file_tag_globals const &); /* compiler_generated() */
};
// static_assert(sizeof(s_cache_file_tag_globals) == 13564, "Invalid s_cache_file_tag_globals size");
// The layout above is the PDB's member list without its padding, so the
// size assertion is withheld: it would fail on alignment alone.

/* ---------- prototypes */

extern void cache_file_tag_references_fixup();
extern void cache_file_tags_close();

/* ---------- globals */

/* ---------- public code */

_extern bool _sub_10927E40(s_cache_tag_instance const *const);
_inline bool s_cache_tag_instance::is_empty() const // 0x10927E40
{
	mangled_x86(MANGLED_TODO, "?is_empty@s_cache_tag_instance@@QBE_NXZ");
	// s_cache_tag_instance const *const this;
	todo("implement");
	bool __result = _sub_10927E40((s_cache_tag_instance const *)this);
	return __result;
}

/* ---------- private code */

#endif // __BLAM_CACHE_CACHE_FILES_HPP__
