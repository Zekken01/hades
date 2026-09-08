#ifndef __BLAM_CACHE_TAGCACHEFILEREADER_HPP__
#define __BLAM_CACHE_TAGCACHEFILEREADER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Magnets.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <fstream>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Blam
{
	namespace Cache
	{
		class CTagCacheFileReader;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Blam
{
	namespace Cache
	{
		class CTagCacheFileReader
		{
		public:
			_inline bool ValidTagIndex(__int32 index) const;
			__int32 GetTagCount() const;
			bool Open(std::string const &filename, long long baseOffset, std::unordered_map<int,std::string,std::hash<int>,std::equal_to<int>,std::allocator<std::pair<int const ,std::string> > > &&tagNames);
			void Close();
			__int32 FindTagByName(__int32 group, std::string_view name);
			bool ReadTag(__int32 index, std::vector<char,std::allocator<char> > &buffer);
			bool ReadAndFixupTag(__int32 index, std::vector<char,std::allocator<char> > &buffer);
			bool ReadTagData(__int32 index, void *buffer, unsigned __int32 offset, __int32 size);
		private:
			bool Initialize();
			std::basic_ifstream<char,std::char_traits<char> > m_stream; // 0x0
			long long m_baseOffset; // 0xB8
			unsigned __int32 m_tagTableOffset; // 0xC0
			__int32 m_tagCount; // 0xC4
			std::unordered_map<int,std::string,std::hash<int>,std::equal_to<int>,std::allocator<std::pair<int const ,std::string> > > m_tagNames; // 0xC8
		public:
			CTagCacheFileReader(Blam::Cache::CTagCacheFileReader &); /* compiler_generated() */
			CTagCacheFileReader(); /* compiler_generated() */
			~CTagCacheFileReader(); /* compiler_generated() */
			Blam::Cache::CTagCacheFileReader &operator=(Blam::Cache::CTagCacheFileReader &); /* compiler_generated() */
		};
		static_assert(sizeof(Blam::Cache::CTagCacheFileReader) == 240, "Invalid Blam::Cache::CTagCacheFileReader size");
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Blam
{
	namespace Cache
	{
		_extern bool _sub_107F5490(Blam::Cache::CTagCacheFileReader const *const, __int32);
		_inline bool CTagCacheFileReader::ValidTagIndex(__int32 index) const // 0x107F5490
		{
			mangled_x86(MANGLED_TODO, "?ValidTagIndex@CTagCacheFileReader@Cache@Blam@@QBE_NH@Z");
			// __int32 index;
			todo("implement");
			bool __result = _sub_107F5490((Blam::Cache::CTagCacheFileReader const *)this, index);
			return __result;
		}
	}
}

/* ---------- private code */

#endif // __BLAM_CACHE_TAGCACHEFILEREADER_HPP__
