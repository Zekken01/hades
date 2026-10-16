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
		StringIDCache::StringIDCache() :
			Header() // 0x1092D090
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0StringIDCache@Cache@Blam@@QAE@XZ");

			Data = nullptr;
			Strings = nullptr;
		}

		StringIDCache::~StringIDCache() // 0x1092D0E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1StringIDCache@Cache@Blam@@QAE@XZ");

			if (Strings)
			{
				delete[] Strings;
				Strings = nullptr;
			}
			if (Data)
			{
				delete[] Data;
				Data = nullptr;
			}
		}

		bool StringIDCache::Load(std::string const &path, long long baseOffset) // 0x1092D5E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Load@StringIDCache@Cache@Blam@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_J@Z");

			std::ifstream stream;
			stream.open(path, std::ios::binary);
			if (!stream.good())
				return false;
			stream.seekg(baseOffset);
			stream.read((char *)&Header, sizeof(Header));
			Data = new char[Header.StringDataSize + 1];
			Strings = new char *[Header.StringCount]();
			__int32 *stringOffsets = new __int32[Header.StringCount];
			stream.read((char *)stringOffsets, Header.StringCount * (std::streamsize)sizeof(__int32));
			long long dataOffset = stream.tellg().seekpos();
			stream.read(Data, Header.StringDataSize);
			Data[Header.StringDataSize] = 0;
			for (__int32 i = 0; i < Header.StringCount; i++)
			{
				if (stringOffsets[i] < 0 || stringOffsets[i] >= Header.StringDataSize)
				{
					Strings[i] = nullptr;
					continue;
				}
				Strings[i] = Data + stringOffsets[i];
			}
			stream.close();
			delete[] stringOffsets;
			return true;
		}

		_inline __int32 GetIndex(unsigned __int32 stringId) // 0x1092D210
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetIndex@Cache@Blam@@YAHI@Z");

			if (stringId >> 31 == 1)
			{
				return stringId & 0x7FFFFFFF;
			}
			else
			{
				return stringId & 0xFFFF;
			}
		}

		_inline __int32 GetSet(unsigned __int32 stringId) // 0x1092D250
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetSet@Cache@Blam@@YAHI@Z");

			if (stringId >> 31 == 1)
			{
				return 0;
			}
			else
			{
				return (stringId >> 16) & 0xFF;
			}
		}

		__int32 GetStringIndex(unsigned __int32 StringId) // 0x1092D3E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetStringIndex@Cache@Blam@@YAHI@Z");

			__int32 set = Blam::Cache::GetSet(StringId);
			__int32 index = Blam::Cache::GetIndex(StringId);
			if (set == 0 && (index < setMin || index > setMax))
			{
				return index;
			}
			if (set < 0 || set >= 9)
			{
				return -1;
			}
			if (set == 0)
			{
				index -= setMin;
			}
			return index + setOffsets[set];
		}

		char *StringIDCache::GetString(unsigned __int32 const StringID) const // 0x1092D290
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetString@StringIDCache@Cache@Blam@@QBEPADI@Z");

			int index = GetStringIndex(StringID);
			if (index < 0 || index >= Header.StringCount)
				return nullptr;
			return Strings[index];
		}

		unsigned __int32 StringIDCache::GetStringId(std::string_view str) const // 0x1092D310
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetStringId@StringIDCache@Cache@Blam@@QBEIV?$basic_string_view@DU?$char_traits@D@std@@@std@@@Z");

			for (__int32 i = 0; i < Header.StringCount; i++)
			{
				if (Strings[i] && str == Strings[i])
					return IndexToStringID(i);
			}
			return 0;
		}

#line 238
		unsigned __int32 MakeStringId(__int32 set, __int32 index) // 0x1092D9F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?MakeStringId@Cache@Blam@@YAIHH@Z");
#line 242

			if (index > 0xFFFF)
			{
				#line 242 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Blam\\Cache\\StringIdCache.cpp"
					assert(set == 0);
					assert(index >= 0 && index < (1 << 30));
					#line 249 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Blam\\Cache\\StringIdCache.cpp"
				return index | 0x80000000;
			}
			else
			{
				#line 248 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Blam\\Cache\\StringIdCache.cpp"
					assert(set >= 0 && set < 256);
					assert(index >= 0 && index < (1 << 30));
					#line 257 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Blam\\Cache\\StringIdCache.cpp"
				return set << 16 | index;
			}
		}

		unsigned __int32 StringIDCache::IndexToStringID(__int32 index) const // 0x1092D4B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?IndexToStringID@StringIDCache@Cache@Blam@@ABEIH@Z");

			if (index < setMin || index > setMax)
				return MakeStringId(0, index);
			__int32 set = 0;
			__int32 minDistance = std::numeric_limits<__int32>::max();
			for (__int32 i = 0; i < _countof(setOffsets); i++)
			{
				if (index < setOffsets[i])
					continue;
				__int32 distance = index - setOffsets[i];
				if (distance >= minDistance)
					continue;
				set = i;
				minDistance = distance;
			}
			__int32 setRelativeIndex = index - setOffsets[set];
			if (set == 0)
				setRelativeIndex += setMin;
			return MakeStringId(set, setRelativeIndex);
		}

		void StringIDCache::SetCurrent(std::shared_ptr<Blam::Cache::StringIDCache> cache) // 0x1092DB20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetCurrent@StringIDCache@Cache@Blam@@SAXV?$shared_ptr@UStringIDCache@Cache@Blam@@@std@@@Z");

			m_current = cache;
		}
	}
}


namespace Blam
{
	namespace Cache
	{
		std::shared_ptr<Blam::Cache::StringIDCache> StringIDCache::GetCurrent() // 0x1092D1A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetCurrent@StringIDCache@Cache@Blam@@SA?AV?$shared_ptr@UStringIDCache@Cache@Blam@@@std@@XZ");

			return m_current;
		}
	}
}

/* ---------- private code */

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace Blam { namespace Cache { __int32 setMin = 1; } }
namespace Blam { namespace Cache { __int32 setMax = 3870; } }
namespace Blam { namespace Cache { __int32 setOffsets[9] = { 2319, 1, 1669, 1824, 1988, 1912, 2000, 2282, 2306 }; } }
