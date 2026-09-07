#ifndef __BLAM_CACHE_CACHE_FILE_TAG_RESOURCES_HPP__
#define __BLAM_CACHE_CACHE_FILE_TAG_RESOURCES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/memory/data.hpp"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_resource_internals.hpp"

/* ---------- forward declarations */

class c_cache_file_tag_resource_runtime_control_allocation;
struct c_cache_file_tag_resource_page_handler;
struct c_indirect_cache_file_location_atlas;
struct s_cache_file_resource_shared_file;
struct s_cache_file_tag_resource_cache_file_header;
struct s_cache_file_tag_resource_table;
struct s_cache_file_tag_resource_table_runtime;
struct s_data_array;
struct s_file_time;
struct s_indirect_cache_file_page;
struct s_tag_resource;

/* ---------- constants */

enum e_cache_file_tag_resource_location
{
	_cache_file_tag_resource_location_invalid = -1, // 0xFF
	_cache_file_tag_resource_location_resources = 0, // 0x0000
	_cache_file_tag_resource_location_textures = 1, // 0x0001
	_cache_file_tag_resource_location_textures_b = 2, // 0x0002
	_cache_file_tag_resource_location_audio = 3, // 0x0003
	_cache_file_tag_resource_location_resources_b = 4, // 0x0004
	_cache_file_tag_resource_location_mods = 5, // 0x0005
	k_number_of_cache_file_tag_resource_locations_old = 5, // 0x0005
	k_number_of_cache_file_tag_resource_locations_new = 6, // 0x0006
};

/* ---------- definitions */

struct s_cache_file_tag_resource_cache_file_header
{
	long field_0; // 0x0
	unsigned long table_offset; // 0x4
	long resource_count; // 0x8
	__int32 field_C; // 0xC
	s_file_time last_modification_date; // 0x10
	__int32 field_18; // 0x18
	long field_1C; // 0x1C
};
static_assert(sizeof(s_cache_file_tag_resource_cache_file_header) == 32, "Invalid s_cache_file_tag_resource_cache_file_header size");

struct s_cache_file_tag_resource_table
{
	long count; // 0x0
	unsigned long *file_offsets; // 0x4
};
static_assert(sizeof(s_cache_file_tag_resource_table) == 8, "Invalid s_cache_file_tag_resource_table size");

struct s_cache_file_tag_resource_table_runtime
{
	long count; // 0x0
	s_tag_resource **resources; // 0x4
};
static_assert(sizeof(s_cache_file_tag_resource_table_runtime) == 8, "Invalid s_cache_file_tag_resource_table_runtime size");

class c_cache_file_tag_resource_runtime_control_allocation
{
private:
	void *vftable; // 0x0
	__int32 field_4; // 0x4
	__int32 field_8; // 0x8
	__int32 field_C; // 0xC
	__int32 field_10; // 0x10
};
static_assert(sizeof(c_cache_file_tag_resource_runtime_control_allocation) == 20, "Invalid c_cache_file_tag_resource_runtime_control_allocation size");

struct s_cache_file_resource_shared_file
{
	unsigned short salt; // 0x0
	unsigned short flags; // 0x2
	void *file_handle; // 0x4
	void *file_handle2; // 0x8
	unsigned long indirect_file_handle; // 0xC
	__int32 field_10; // 0x10
	unsigned long base_offset; // 0x14
	unsigned char __pad0[4]; // 0x18
};
static_assert(sizeof(s_cache_file_resource_shared_file) == 28, "Invalid s_cache_file_resource_shared_file size");

struct s_indirect_cache_file_page
{
	unsigned long indirect_file_handle; // 0x0
	unsigned long offset; // 0x4
	unsigned long size; // 0x8
};
static_assert(sizeof(s_indirect_cache_file_page) == 12, "Invalid s_indirect_cache_file_page size");

struct c_indirect_cache_file_location_atlas
{
	void **vftable; // 0x0
	void **v_physical_memory_contigous_region_listener; // 0x4
	void **v_tag_resource_prediction_atom_generator; // 0x8
	void **v_cache_file_resource_stoler; // 0xC
	__int32 field_10; // 0x10
	__int32 field_14; // 0x14
	__int32 field_18; // 0x18
	__int32 field_1C; // 0x1C
	__int32 field_20; // 0x20
	__int32 field_24; // 0x24
	__int32 field_28; // 0x28
	__int32 field_2C; // 0x2C
	__int32 field_30; // 0x30
	__int32 field_34; // 0x34
	__int32 unknown_shared_file_handle; // 0x38
	__int32 field_3C; // 0x3C
	__int32 field_40; // 0x40
	unsigned char gap44[204]; // 0x44
	unsigned char field_110[256]; // 0x110
	unsigned char gap210[172256]; // 0x210
	c_cache_file_tag_resource_page_handler *page_handler; // 0x2A2F0
	unsigned char gap2A2F4[1020]; // 0x2A2F4
	__int32 field_2A6F0; // 0x2A6F0
	__int32 field_2A6F4; // 0x2A6F4
	__int32 field_2A6F8; // 0x2A6F8
	__int32 field_2A6FC; // 0x2A6FC
	__int32 field_2A700; // 0x2A700
	__int32 field_2A704; // 0x2A704
	__int32 field_2A708; // 0x2A708
	__int32 field_2A70C; // 0x2A70C
	__int32 field_2A710; // 0x2A710
	__int32 field_2A714; // 0x2A714
	__int32 field_2A718; // 0x2A718
	__int32 field_2A71C; // 0x2A71C
	__int32 field_2A720; // 0x2A720
	__int32 field_2A724; // 0x2A724
	__int32 field_2A728; // 0x2A728
	c_cache_file_tag_resource_runtime_control_allocation runtime_control_allocation; // 0x2A72C
	__int32 field_2A740; // 0x2A740
	__int32 field_2A744; // 0x2A744
	__int32 cache_file_shared_file_handle_handles[8]; // 0x2A748
	s_data_array *shared_file_handles; // 0x2A768
	__int32 field_2A76C; // 0x2A76C
	__int32 field_2A770; // 0x2A770
	__int32 field_2A774; // 0x2A774
	__int32 field_2A778; // 0x2A778
	__int32 field_2A77C; // 0x2A77C
	__int32 field_2A780; // 0x2A780
	__int32 field_2A784; // 0x2A784
	__int32 field_2A788; // 0x2A788
	__int32 field_2A78C; // 0x2A78C
};
static_assert(sizeof(c_indirect_cache_file_location_atlas) == 173968, "Invalid c_indirect_cache_file_location_atlas size");

/* ---------- prototypes */

extern e_cache_file_tag_resource_location tag_resource_get_location(s_tag_resource *resource);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_CACHE_CACHE_FILE_TAG_RESOURCES_HPP__
