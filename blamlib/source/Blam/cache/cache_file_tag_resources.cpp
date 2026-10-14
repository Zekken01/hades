/* ---------- headers */

#include "Blam/cache/cache_file_tag_resources.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/tag_files/tag_resource_internals.hpp"

/* ---------- forward declarations */

struct s_tag_resource;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern e_cache_file_tag_resource_location tag_resource_get_location(s_tag_resource *resource);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

e_cache_file_tag_resource_location tag_resource_get_location(s_tag_resource *resource) // 0x10F0C2E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?tag_resource_get_location@@YA?AW4e_cache_file_tag_resource_location@@PAUs_tag_resource@@@Z");
	// s_tag_resource *resource;

	if (resource->page_flags & 0x2)
		return _cache_file_tag_resource_location_resources;
	else if (resource->page_flags & 0x4)
		return _cache_file_tag_resource_location_textures;
	else if (resource->page_flags & 0x8)
		return _cache_file_tag_resource_location_textures_b;
	else if (resource->page_flags & 0x10)
		return _cache_file_tag_resource_location_audio;
	else if (resource->page_flags & 0x20)
		return _cache_file_tag_resource_location_resources_b;
	else if (resource->page_flags & 0x40)
		return _cache_file_tag_resource_location_mods;
	return _cache_file_tag_resource_location_invalid;
}

/* ---------- private code */
