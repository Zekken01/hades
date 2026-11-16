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
					return 0x70000;
		}
	}
}


namespace Utils
{
	namespace Version
	{
		std::string GetVersionString() // 0x10C60DB0
		{
			return "0.7.1.1";
		}
	}
}


namespace Utils
{
	namespace Version
	{
		std::string GetCompatibleVersionString() // 0x10C60D20
		{
			return "0.7.1";
		}

		bool IsVersionCompatible(std::string const &versionString) // 0x10C60E20
		{
			SemanticVersion version(0, 0, 0, "", "");
			if (!SemanticVersion::TryParse(versionString, version))
				return false;
			SemanticVersion minVersion = SemanticVersion::Parse(GetCompatibleVersionString());
			SemanticVersion maxVersion = SemanticVersion::Parse(GetVersionString());
			return version >= minVersion && version <= maxVersion;
		}
	}
}

/* ---------- private code */
