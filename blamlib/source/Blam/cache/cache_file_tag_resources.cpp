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

extern e_cache_file_tag_resource_location _sub_10F0C2E0(s_tag_resource *);
e_cache_file_tag_resource_location tag_resource_get_location(s_tag_resource *resource) // 0x10F0C2E0
{
	mangled_x86(MANGLED_TODO, "?tag_resource_get_location@@YA?AW4e_cache_file_tag_resource_location@@PAUs_tag_resource@@@Z");
	// s_tag_resource *resource;
	todo("implement");
	e_cache_file_tag_resource_location __result = _sub_10F0C2E0(resource);
	return __result;
}

/* ---------- private code */
