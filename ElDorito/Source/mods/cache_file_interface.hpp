#ifndef __MODS_CACHE_FILE_INTERFACE_HPP__
#define __MODS_CACHE_FILE_INTERFACE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/Cache/StringIdCache.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "Patches/CustomPackets.hpp"

#include <memory>

/* ---------- forward declarations */

class c_cache_file_tag_cache;
struct c_cache_file_interface;
namespace Blam
{
	namespace Cache
	{
		struct StringIDCache;
	}
}

/* ---------- constants */

/* ---------- definitions */

struct c_cache_file_interface
{
	virtual _inline ~c_cache_file_interface() = default; // 0x1078BEB0
	virtual std::shared_ptr<Blam::Cache::StringIDCache> get_string_cache() const = 0;
	virtual std::shared_ptr<c_cache_file_tag_cache> get_tag_cache() const = 0;
	c_cache_file_interface(c_cache_file_interface const &); /* compiler_generated() */
	_inline c_cache_file_interface(); /* compiler_generated() */
	c_cache_file_interface &operator=(c_cache_file_interface const &); /* compiler_generated() */
};
static_assert(sizeof(c_cache_file_interface) == 4, "Invalid c_cache_file_interface size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODS_CACHE_FILE_INTERFACE_HPP__
