/* ---------- headers */

#include "hades/hades.h"

#include "Utils/SemanticVersion.hpp"

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
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

namespace Utils
{
	struct SemanticVersion;
}

namespace Utils {}
using namespace ::Utils;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Utils
{
	namespace Version
	{
		extern unsigned __int32 GetVersionInt();
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetVersionString();
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetCompatibleVersionString();
		extern bool IsVersionCompatible(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &versionString);
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Utils
{
	namespace Version
	{
		_extern unsigned __int32 _sub_10C60D90();
		unsigned __int32 GetVersionInt() // 0x10C60D90
		{
			mangled_x86(MANGLED_TODO, "?GetVersionInt@Version@Utils@@YAIXZ");
			// procedure flags: nofpo
			todo("implement");
			unsigned __int32 __result = _sub_10C60D90();
			return __result;
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10C60DB0();
namespace Utils
{
	namespace Version
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetVersionString() // 0x10C60DB0
		{
			mangled_x86(MANGLED_TODO, "?GetVersionString@Version@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
			// procedure flags: nofpo
			todo("implement");
			std::string __result = _sub_10C60DB0();
			return __result;
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10C60D20();
namespace Utils
{
	namespace Version
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetCompatibleVersionString() // 0x10C60D20
		{
			mangled_x86(MANGLED_TODO, "?GetCompatibleVersionString@Version@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
			// procedure flags: nofpo
			todo("implement");
			std::string __result = _sub_10C60D20();
			return __result;
		}

		_extern bool _sub_10C60E20(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
		bool IsVersionCompatible(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &versionString) // 0x10C60E20
		{
			mangled_x86(MANGLED_TODO, "?IsVersionCompatible@Version@Utils@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10C61086
			// static ...; // 0x10C6107B
			// static ...; // 0x10C61070
			// static ...; // 0x10C6104C
			// static ...; // 0x10C61044
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &versionString;
			// Utils::SemanticVersion version;
			// Utils::SemanticVersion minVersion;
			// Utils::SemanticVersion maxVersion;
			todo("implement");
			bool __result = _sub_10C60E20(versionString);
			return __result;
		}
	}
}

/* ---------- private code */
