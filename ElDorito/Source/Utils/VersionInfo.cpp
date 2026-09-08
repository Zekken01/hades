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
		extern std::string GetVersionString();
		extern std::string GetCompatibleVersionString();
		extern bool IsVersionCompatible(std::string const &versionString);
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Utils
{
	namespace Version
	{
		unsigned __int32 GetVersionInt() // 0x10C60D90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetVersionInt@Version@Utils@@YAIXZ");
			// procedure flags: nofpo

			return 0x70000;
		}
	}
}

extern std::string _sub_10C60DB0();
namespace Utils
{
	namespace Version
	{
		std::string GetVersionString() // 0x10C60DB0
		{
			mangled_x86(MANGLED_TODO, "?GetVersionString@Version@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
			// procedure flags: nofpo
			todo("implement");
			std::string __result = _sub_10C60DB0();
			return __result;
		}
	}
}

extern std::string _sub_10C60D20();
namespace Utils
{
	namespace Version
	{
		std::string GetCompatibleVersionString() // 0x10C60D20
		{
			mangled_x86(MANGLED_TODO, "?GetCompatibleVersionString@Version@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
			// procedure flags: nofpo
			todo("implement");
			std::string __result = _sub_10C60D20();
			return __result;
		}

		_extern bool _sub_10C60E20(std::string const &);
		bool IsVersionCompatible(std::string const &versionString) // 0x10C60E20
		{
			mangled_x86(MANGLED_TODO, "?IsVersionCompatible@Version@Utils@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10C61086
			// static ...; // 0x10C6107B
			// static ...; // 0x10C61070
			// static ...; // 0x10C6104C
			// static ...; // 0x10C61044
			// std::string const &versionString;
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
