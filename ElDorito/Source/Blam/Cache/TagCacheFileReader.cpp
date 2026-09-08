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
		_extern bool _sub_107F4F10(Blam::Cache::CTagCacheFileReader *const, std::string const &, long long, std::unordered_map<int,std::string> &);
		bool CTagCacheFileReader::Open(std::string const &filename, long long baseOffset, std::unordered_map<int,std::string> &&tagNames) // 0x107F4F10
		{
			mangled_x86(MANGLED_TODO, "?Open@CTagCacheFileReader@Cache@Blam@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_J$$QAV?$unordered_map@HV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$hash@H@2@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBHV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@@2@@5@@Z");
			// std::unordered_map<int,std::string> &tagNames;
			todo("implement");
			bool __result = _sub_107F4F10(this, filename, baseOffset, tagNames);
			return __result;
		}

		_extern void _sub_107F4A30(Blam::Cache::CTagCacheFileReader *const);
		void CTagCacheFileReader::Close() // 0x107F4A30
		{
			mangled_x86(MANGLED_TODO, "?Close@CTagCacheFileReader@Cache@Blam@@QAEXXZ");
			// Blam::Cache::CTagCacheFileReader *const this;
			todo("implement");
			_sub_107F4A30(this);
		}

		_extern __int32 _sub_107F4A80(Blam::Cache::CTagCacheFileReader *const, __int32, std::string_view);
		__int32 CTagCacheFileReader::FindTagByName(__int32 group, std::string_view name) // 0x107F4A80
		{
			mangled_x86(MANGLED_TODO, "?FindTagByName@CTagCacheFileReader@Cache@Blam@@QAEHHV?$basic_string_view@DU?$char_traits@D@std@@@std@@@Z");
			// static ...; // 0x107F4CE4
			// static ...; // 0x107F4CC0
			// static ...; // 0x107F4CB8
			// Blam::Cache::CTagCacheFileReader *const this;
			// __int32 group;
			// std::string_view name;
			{
				// __int32 i;
				{
					// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<int const ,std::string> > > > nameIt;
					// s_cache_tag_instance header;
				}
			}
			todo("implement");
			__int32 __result = _sub_107F4A80(this, group, name);
			return __result;
		}

		_extern bool _sub_107F5140(Blam::Cache::CTagCacheFileReader *const, __int32, std::vector<char> &);
		bool CTagCacheFileReader::ReadTag(__int32 index, std::vector<char> &buffer) // 0x107F5140
		{
			mangled_x86(MANGLED_TODO, "?ReadTag@CTagCacheFileReader@Cache@Blam@@QAE_NHAAV?$vector@DV?$allocator@D@std@@@std@@@Z");
			// static ...; // 0x107F51E4
			// Blam::Cache::CTagCacheFileReader *const this;
			// __int32 index;
			// std::vector<char> &buffer;
			// s_cache_tag_instance header;
			todo("implement");
			bool __result = _sub_107F5140(this, index, buffer);
			return __result;
		}

		_extern bool _sub_107F5040(Blam::Cache::CTagCacheFileReader *const, __int32, std::vector<char> &);
		bool CTagCacheFileReader::ReadAndFixupTag(__int32 index, std::vector<char> &buffer) // 0x107F5040
		{
			mangled_x86(MANGLED_TODO, "?ReadAndFixupTag@CTagCacheFileReader@Cache@Blam@@QAE_NHAAV?$vector@DV?$allocator@D@std@@@std@@@Z");
			// std::vector<char> &buffer;
			// s_cache_tag_instance *instance;
			// unsigned __int32 *fixups;
			{
				// long i;
			}
			todo("implement");
			bool __result = _sub_107F5040(this, index, buffer);
			return __result;
		}

		_extern bool _sub_107F5230(Blam::Cache::CTagCacheFileReader *const, __int32, void *, unsigned __int32, __int32);
		bool CTagCacheFileReader::ReadTagData(__int32 index, void *buffer, unsigned __int32 offset, __int32 size) // 0x107F5230
		{
			mangled_x86(MANGLED_TODO, "?ReadTagData@CTagCacheFileReader@Cache@Blam@@QAE_NHPAXIH@Z");
			// __int32 index;
			// void *buffer;
			// unsigned __int32 offset;
			// __int32 size;
			// unsigned __int32 tagOffset;
			todo("implement");
			bool __result = _sub_107F5230(this, index, buffer, offset, size);
			return __result;
		}

		_extern bool _sub_107F4DA0(Blam::Cache::CTagCacheFileReader *const);
		bool CTagCacheFileReader::Initialize() // 0x107F4DA0
		{
			mangled_x86(MANGLED_TODO, "?Initialize@CTagCacheFileReader@Cache@Blam@@AAE_NXZ");
			// static ...; // 0x107F4EBC
			// static ...; // 0x107F4EB0
			// static ...; // 0x107F4EA8
			// Blam::Cache::CTagCacheFileReader *const this;
			// s_cache_file_segment_header header;
			todo("implement");
			bool __result = _sub_107F4DA0(this);
			return __result;
		}
	}
}

/* ---------- private code */
