#ifndef __BLAM_CACHE_STRINGIDCACHE_HPP__
#define __BLAM_CACHE_STRINGIDCACHE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/Prefab.hpp"
#include "Patches/CustomPackets.hpp"

#include <memory>
#include <string>
#include <string_view>

/* ---------- forward declarations */

namespace Blam
{
	namespace Cache
	{
		struct StringIDCache;
		struct StringIDCacheHeader;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Blam
{
	namespace Cache
	{
		struct StringIDCacheHeader
		{
			__int32 StringCount; // 0x0
			__int32 StringDataSize; // 0x4
		};
		static_assert(sizeof(Blam::Cache::StringIDCacheHeader) == 8, "Invalid Blam::Cache::StringIDCacheHeader size");

		struct StringIDCache
		{
			Blam::Cache::StringIDCacheHeader Header; // 0x0
			char *Data; // 0x8
			char **Strings; // 0xC
			StringIDCache(Blam::Cache::StringIDCache &);
			StringIDCache(Blam::Cache::StringIDCache const &);
			StringIDCache();
			~StringIDCache();
			bool Load(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path, long long baseOffset);
			char *GetString(unsigned __int32 const StringID) const;
			unsigned __int32 GetStringId(std::basic_string_view<char,std::char_traits<char> > str) const;
			static void SetCurrent(std::shared_ptr<Blam::Cache::StringIDCache> cache);
			static std::shared_ptr<Blam::Cache::StringIDCache> GetCurrent();
		private:
			unsigned __int32 IndexToStringID(__int32 index) const;
			static std::shared_ptr<Blam::Cache::StringIDCache> m_current;
		};
		static_assert(sizeof(Blam::Cache::StringIDCache) == 16, "Invalid Blam::Cache::StringIDCache size");
	}
}

/* ---------- prototypes */

namespace Blam
{
	namespace Cache
	{
		extern _inline __int32 GetIndex(unsigned __int32 stringId);
		extern _inline __int32 GetSet(unsigned __int32 stringId);
		extern __int32 GetStringIndex(unsigned __int32 StringId);
		extern unsigned __int32 MakeStringId(__int32 set, __int32 index);
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_CACHE_STRINGIDCACHE_HPP__
