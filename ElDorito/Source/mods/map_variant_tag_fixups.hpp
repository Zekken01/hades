#ifndef __MODS_MAP_VARIANT_TAG_FIXUPS_HPP__
#define __MODS_MAP_VARIANT_TAG_FIXUPS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/tag_files/files.hpp"
#include "mods/map_variant_loader.hpp"

/* ---------- forward declarations */

class c_map_variant_tag_fixups;
struct s_file_reference;
struct s_map_variant;

/* ---------- constants */

/* ---------- definitions */

class c_map_variant_tag_fixups
{
public:
	static bool fixup_map_variant_in_memory(unsigned char *buffer, unsigned long buffer_size, s_map_variant *map_variant);
	static bool fixup_map_variant_from_file(s_file_reference *file, s_map_variant *map_variant);
	static void initialize();
};
static_assert(sizeof(c_map_variant_tag_fixups) == 1, "Invalid c_map_variant_tag_fixups size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODS_MAP_VARIANT_TAG_FIXUPS_HPP__
