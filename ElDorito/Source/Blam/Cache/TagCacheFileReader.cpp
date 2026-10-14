/* ---------- headers */

#include "Blam/Cache/TagCacheFileReader.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Magnets.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <limits>
#include <list>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <string_view>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct s_cache_file_segment_header;
struct s_cache_tag_instance;
namespace Blam
{
	namespace Cache
	{
		class CTagCacheFileReader;
	}
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Blam
{
	namespace Cache
	{
		bool CTagCacheFileReader::Open(std::string const &filename, long long baseOffset, std::unordered_map<int,std::string> &&tagNames) // 0x107F4F10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Open@CTagCacheFileReader@Cache@Blam@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_J$$QAV?$unordered_map@HV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$hash@H@2@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBHV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@@2@@5@@Z");
			// std::unordered_map<int,std::string> &tagNames;

			m_baseOffset = baseOffset;
			m_stream = std::ifstream(filename, std::ios::binary);
			m_tagNames = std::move(tagNames);
			return Initialize();
		}

		void CTagCacheFileReader::Close() // 0x107F4A30
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Close@CTagCacheFileReader@Cache@Blam@@QAEXXZ");
			// Blam::Cache::CTagCacheFileReader *const this;

			m_stream.close();
		}

		__int32 CTagCacheFileReader::FindTagByName(__int32 group, std::string_view name) // 0x107F4A80
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?FindTagByName@CTagCacheFileReader@Cache@Blam@@QAEHHV?$basic_string_view@DU?$char_traits@D@std@@@std@@@Z");
			// static ...; // 0x107F4CE4
			// static ...; // 0x107F4CC0
			// static ...; // 0x107F4CB8
			// Blam::Cache::CTagCacheFileReader *const this;
			// __int32 group;
			// std::string_view name;
				// __int32 i;
					// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<int const ,std::string> > > > nameIt;
					// s_cache_tag_instance header;

			for (__int32 i = 0; i < m_tagCount; i++)
			{
				auto nameIt = m_tagNames.find(i);
				if (nameIt == m_tagNames.end() || nameIt->second != name)
					continue;
				s_cache_tag_instance header;
				if (!ReadTagData(i, &header, 0, sizeof(header)))
					continue;
				if (header.group.tags[0] == group)
					return i;
			}
			return -1;
		}

		bool CTagCacheFileReader::ReadTag(__int32 index, std::vector<char> &buffer) // 0x107F5140
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ReadTag@CTagCacheFileReader@Cache@Blam@@QAE_NHAAV?$vector@DV?$allocator@D@std@@@std@@@Z");
			// static ...; // 0x107F51E4
			// Blam::Cache::CTagCacheFileReader *const this;
			// __int32 index;
			// std::vector<char> &buffer;
			// s_cache_tag_instance header;

			s_cache_tag_instance header;
			if (!ReadTagData(index, &header, 0, sizeof(header)))
				return false;
			buffer.resize(header.size);
			return ReadTagData(index, buffer.data(), 0, header.size);
		}

		bool CTagCacheFileReader::ReadAndFixupTag(__int32 index, std::vector<char> &buffer) // 0x107F5040
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ReadAndFixupTag@CTagCacheFileReader@Cache@Blam@@QAE_NHAAV?$vector@DV?$allocator@D@std@@@std@@@Z");
			// std::vector<char> &buffer;
			// s_cache_tag_instance *instance;
			// unsigned __int32 *fixups;
				// long i;

			if (!ReadTag(index, buffer))
				return false;
			s_cache_tag_instance *instance = (s_cache_tag_instance *)buffer.data();
			unsigned __int32 *fixups = (unsigned __int32 *)&instance[1] + instance->dependency_count;
			for (long i = 0; i < instance->fixup_count; i++)
				*(unsigned __int32 *)((char *)instance + fixups[i] - 0x40000000) = (unsigned __int32)((char *)instance + *(unsigned __int32 *)((char *)instance + fixups[i] - 0x40000000) - 0x40000000);
			return true;
		}

		bool CTagCacheFileReader::ReadTagData(__int32 index, void *buffer, unsigned __int32 offset, __int32 size) // 0x107F5230
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ReadTagData@CTagCacheFileReader@Cache@Blam@@QAE_NHPAXIH@Z");
			// __int32 index;
			// void *buffer;
			// unsigned __int32 offset;
			// __int32 size;
			// unsigned __int32 tagOffset;

			if (!ValidTagIndex(index))
				return false;
			m_stream.seekg(m_tagTableOffset + m_baseOffset + index * 4LL);
			unsigned __int32 tagOffset;
			m_stream.read(reinterpret_cast<char *>(&tagOffset), 4);
			if (!m_stream.good() || !tagOffset)
				return false;
			m_stream.seekg(tagOffset + m_baseOffset + offset);
			m_stream.read(static_cast<char *>(buffer), size);
			return m_stream.good() && m_stream.gcount() == size;
		}

		bool CTagCacheFileReader::Initialize() // 0x107F4DA0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Initialize@CTagCacheFileReader@Cache@Blam@@AAE_NXZ");
			// static ...; // 0x107F4EBC
			// static ...; // 0x107F4EB0
			// static ...; // 0x107F4EA8
			// Blam::Cache::CTagCacheFileReader *const this;
			// s_cache_file_segment_header header;

			m_stream.seekg(m_baseOffset);
			s_cache_file_segment_header header;
			m_stream.read((char *)&header, sizeof(header));
			if (!m_stream.good())
				return false;
			m_tagCount = header.table_count;
			m_tagTableOffset = header.table_offset;
			return m_tagCount <= std::numeric_limits<unsigned short>::max();
		}
	}
}

/* ---------- private code */
