/* ---------- headers */

#include "Blam/Cache/StringIdCache.hpp"
#include "hades/hades.h"

#include "Forge/Prefab.hpp"
#include "Patches/CustomPackets.hpp"

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
#include <ios>
#include <iosfwd>
#include <istream>
#include <limits>
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
#include <utility>

/* ---------- forward declarations */

namespace Blam
{
	namespace Cache
	{
		struct StringIDCache;
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

namespace Blam
{
	namespace Cache
	{
		std::shared_ptr<Blam::Cache::StringIDCache> StringIDCache::m_current; // 0x1240D6E4
		extern __int32 setMin; // 0x113539B4
		extern __int32 setMax; // 0x113539B8
		extern __int32 setOffsets[9]; // 0x113539BC
	}
}

/* ---------- private variables */

/* ---------- public code */

namespace Blam
{
	namespace Cache
	{
		extern StringIDCache* _sub_1092D090(Blam::Cache::StringIDCache *const);
		StringIDCache::StringIDCache() // 0x1092D090
		{
			mangled_x86(MANGLED_TODO, "??0StringIDCache@Cache@Blam@@QAE@XZ");
			// Blam::Cache::StringIDCache *const this;
			todo("implement");
			_sub_1092D090(this);
		}

		_extern void _sub_1092D0E0(Blam::Cache::StringIDCache *const);
		StringIDCache::~StringIDCache() // 0x1092D0E0
		{
			mangled_x86(MANGLED_TODO, "??1StringIDCache@Cache@Blam@@QAE@XZ");
			// Blam::Cache::StringIDCache *const this;
			todo("implement");
			_sub_1092D0E0(this);
		}

		_extern bool _sub_1092D5E0(Blam::Cache::StringIDCache *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, long long);
		bool StringIDCache::Load(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path, long long baseOffset) // 0x1092D5E0
		{
			mangled_x86(MANGLED_TODO, "?Load@StringIDCache@Cache@Blam@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_J@Z");
			// static ...; // 0x1092D900
			// Blam::Cache::StringIDCache *const this;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path;
			// long long baseOffset;
			// long long dataOffset;
			// __int32 *stringOffsets;
			// std::basic_ifstream<char,std::char_traits<char> > stream;
			{
				// __int32 i;
			}
			todo("implement");
			bool __result = _sub_1092D5E0(this, path, baseOffset);
			return __result;
		}

		_extern __int32 _sub_1092D210(unsigned __int32);
		_inline __int32 GetIndex(unsigned __int32 stringId) // 0x1092D210
		{
			mangled_x86(MANGLED_TODO, "?GetIndex@Cache@Blam@@YAHI@Z");
			// unsigned __int32 stringId;
			todo("implement");
			__int32 __result = _sub_1092D210(stringId);
			return __result;
		}

		_extern __int32 _sub_1092D250(unsigned __int32);
		_inline __int32 GetSet(unsigned __int32 stringId) // 0x1092D250
		{
			mangled_x86(MANGLED_TODO, "?GetSet@Cache@Blam@@YAHI@Z");
			// unsigned __int32 stringId;
			todo("implement");
			__int32 __result = _sub_1092D250(stringId);
			return __result;
		}

		_extern __int32 _sub_1092D3E0(unsigned __int32);
		__int32 GetStringIndex(unsigned __int32 StringId) // 0x1092D3E0
		{
			mangled_x86(MANGLED_TODO, "?GetStringIndex@Cache@Blam@@YAHI@Z");
			// unsigned __int32 StringId;
			// __int32 set;
			// __int32 index;
			todo("implement");
			__int32 __result = _sub_1092D3E0(StringId);
			return __result;
		}

		_extern char *_sub_1092D290(Blam::Cache::StringIDCache const *const, unsigned __int32 const);
		char *StringIDCache::GetString(unsigned __int32 const StringID) const // 0x1092D290
		{
			mangled_x86(MANGLED_TODO, "?GetString@StringIDCache@Cache@Blam@@QBEPADI@Z");
			// unsigned __int32 const StringID;
			// __int32 index;
			todo("implement");
			char * __result = _sub_1092D290((Blam::Cache::StringIDCache const *)this, StringID);
			return __result;
		}

		_extern unsigned __int32 _sub_1092D310(Blam::Cache::StringIDCache const *const, std::basic_string_view<char,std::char_traits<char> >);
		unsigned __int32 StringIDCache::GetStringId(std::basic_string_view<char,std::char_traits<char> > str) const // 0x1092D310
		{
			mangled_x86(MANGLED_TODO, "?GetStringId@StringIDCache@Cache@Blam@@QBEIV?$basic_string_view@DU?$char_traits@D@std@@@std@@@Z");
			// std::basic_string_view<char,std::char_traits<char> > str;
			{
				// __int32 i;
			}
			todo("implement");
			unsigned __int32 __result = _sub_1092D310((Blam::Cache::StringIDCache const *)this, str);
			return __result;
		}

		_extern unsigned __int32 _sub_1092D9F0(__int32, __int32);
		unsigned __int32 MakeStringId(__int32 set, __int32 index) // 0x1092D9F0
		{
			mangled_x86(MANGLED_TODO, "?MakeStringId@Cache@Blam@@YAIHH@Z");
			// __int32 index;
			todo("implement");
			unsigned __int32 __result = _sub_1092D9F0(set, index);
			return __result;
		}

		_extern unsigned __int32 _sub_1092D4B0(Blam::Cache::StringIDCache const *const, __int32);
		unsigned __int32 StringIDCache::IndexToStringID(__int32 index) const // 0x1092D4B0
		{
			mangled_x86(MANGLED_TODO, "?IndexToStringID@StringIDCache@Cache@Blam@@ABEIH@Z");
			// __int32 index;
			// __int32 set;
			// __int32 setRelativeIndex;
			// __int32 minDistance;
			{
				// __int32 i;
				{
					// __int32 distance;
				}
			}
			todo("implement");
			unsigned __int32 __result = _sub_1092D4B0((Blam::Cache::StringIDCache const *)this, index);
			return __result;
		}

		_extern void _sub_1092DB20(std::shared_ptr<Blam::Cache::StringIDCache>);
		void StringIDCache::SetCurrent(std::shared_ptr<Blam::Cache::StringIDCache> cache) // 0x1092DB20
		{
			mangled_x86(MANGLED_TODO, "?SetCurrent@StringIDCache@Cache@Blam@@SAXV?$shared_ptr@UStringIDCache@Cache@Blam@@@std@@@Z");
			// std::shared_ptr<Blam::Cache::StringIDCache> cache;
			todo("implement");
			_sub_1092DB20(cache);
		}
	}
}

extern std::shared_ptr<Blam::Cache::StringIDCache> _sub_1092D1A0();
namespace Blam
{
	namespace Cache
	{
		std::shared_ptr<Blam::Cache::StringIDCache> StringIDCache::GetCurrent() // 0x1092D1A0
		{
			mangled_x86(MANGLED_TODO, "?GetCurrent@StringIDCache@Cache@Blam@@SA?AV?$shared_ptr@UStringIDCache@Cache@Blam@@@std@@XZ");
			// procedure flags: nofpo
			todo("implement");
			std::shared_ptr<Blam::Cache::StringIDCache> __result = _sub_1092D1A0();
			return __result;
		}
	}
}

/* ---------- private code */
