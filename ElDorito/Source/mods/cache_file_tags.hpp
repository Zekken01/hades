#ifndef __MODS_CACHE_FILE_TAGS_HPP__
#define __MODS_CACHE_FILE_TAGS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/Cache/StringIdCache.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "Patches/CustomPackets.hpp"

#include <memory>

/* ---------- forward declarations */

class c_cache_file_tag_cache;
struct c_cache_file_tags;
namespace Blam
{
	namespace Cache
	{
		struct StringIDCache;
	}
}

/* ---------- constants */

/* ---------- definitions */

struct c_cache_file_tags
{
	static std::shared_ptr<c_cache_file_tag_cache> get_open_cache();
	static std::shared_ptr<Blam::Cache::StringIDCache> get_open_string_id_cache();
	static bool open_tag_cache();
	static void close_tag_cache();
};
static_assert(sizeof(c_cache_file_tags) == 1, "Invalid c_cache_file_tags size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODS_CACHE_FILE_TAGS_HPP__
