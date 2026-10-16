/* ---------- headers */

#include "Utils/SemanticVersion.hpp"
#include "hades/hades.h"

#include <format>  // hades: added for 0x10768300  // hades: added for 0x10768300

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <iterator>
#include <limits>
#include <locale>
#include <memory>
#include <mutex>
#include <ratio>
#include <regex>
#include <stdexcept>
#include <stop_token>
#include <string>
#include <string_view>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

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

/* ---------- globals */

/* ---------- private variables */

namespace Utils
{
	namespace hades_file_local_Utils
	{
		std::regex kPattern("(\\d+)\\.(\\d+)\\.(\\d+)(?:-([0-9A-Za-z-.]+))?(?:\\+([0-9A-Za-z-.]+))?"); // 0x1138CE6C
	}
	using namespace hades_file_local_Utils;
}
/* ---------- public code */

namespace Utils
{
	SemanticVersion::SemanticVersion(__int32 major, __int32 minor, __int32 patch, std::string prerelease, std::string build) : major(major), minor(minor), patch(patch), prerelease(prerelease), build(build) /* hades-mem-init:  */ // 0x107627C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0SemanticVersion@Utils@@QAE@HHHV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");

		if (major < 0 || minor < 0 || patch < 0)
			throw std::invalid_argument("Version components cannot be negative.");
	}
}


namespace Utils
{
	std::string SemanticVersion::ToString() const // 0x10768300
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ToString@SemanticVersion@Utils@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");

		std::string result = std::format("{}.{}.{}", major, minor, patch);
		if (!prerelease.empty())
			result += "-" + prerelease;
		if (!build.empty())
			result += "+" + build;
		return result;
	}

	bool SemanticVersion::TryParse(std::string const &input, Utils::SemanticVersion &outVersion) // 0x10768560
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?TryParse@SemanticVersion@Utils@@SA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAU12@@Z");

		try
		{
			outVersion = Parse(input);
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	Utils::SemanticVersion SemanticVersion::Parse(std::string const &input) // 0x10767DF0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Parse@SemanticVersion@Utils@@SA?AU12@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

		std::smatch matches;
		if (!std::regex_match(input, matches, kPattern))
			throw std::invalid_argument("Invalid semantic version: " + input);
		return SemanticVersion(std::stoi(matches[1].str()), std::stoi(matches[2].str()), std::stoi(matches[3].str()), matches[4].str(), matches[5].str());
	}

	__int32 SemanticVersion::Compare(Utils::SemanticVersion const &a, Utils::SemanticVersion const &b) // 0x107678E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Compare@SemanticVersion@Utils@@CAHABU12@0@Z");

		if (a.major != b.major)
			return a.major < b.major ? -1 : 1;
		if (a.minor != b.minor)
			return a.minor < b.minor ? -1 : 1;
		if (a.patch != b.patch)
			return a.patch < b.patch ? -1 : 1;
		return ComparePrerelease(a.prerelease, b.prerelease);
	}

	__int32 SemanticVersion::ComparePrerelease(std::string_view const &a, std::string_view const &b) // 0x10767BF0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ComparePrerelease@SemanticVersion@Utils@@CAHABV?$basic_string_view@DU?$char_traits@D@std@@@std@@0@Z");

		if (a.empty() && b.empty())
			return 0;
		if (a.empty())
			return 1;
		if (b.empty())
			return -1;
		unsigned __int32 pos1 = 0;
		unsigned __int32 pos2 = 0;
		while (true)
		{
			unsigned __int32 next_pos1 = a.find('.', pos1);
			unsigned __int32 next_pos2 = b.find('.', pos2);
			std::string_view identifier1 = a.substr(pos1, next_pos1 - pos1);
			std::string_view identifier2 = b.substr(pos2, next_pos2 - pos2);
			__int32 cmp = CompareIdentifier(identifier1, identifier2);
			if (cmp != 0)
				return cmp;
			if (next_pos1 == std::string_view::npos && next_pos2 == std::string_view::npos)
				return 0;
			if (next_pos1 == std::string_view::npos)
				return -1;
			if (next_pos2 == std::string_view::npos)
				return 1;
			pos1 = next_pos1 + 1;
			pos2 = next_pos2 + 1;
		}
	}

	__int32 SemanticVersion::CompareIdentifier(std::string_view const &a, std::string_view const &b) // 0x10767A60
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?CompareIdentifier@SemanticVersion@Utils@@CAHABV?$basic_string_view@DU?$char_traits@D@std@@@std@@0@Z");

		__int32 num1, num2;
		bool a_num = ParseNumericIdentifier(a, num1);
		bool b_num = ParseNumericIdentifier(b, num2);
		if (a_num != b_num)
			return a_num ? -1 : 1;
		if (a_num)
		{
			if (num1 != num2)
				return num1 < num2 ? -1 : 1;
		}
		else
		{
			__int32 const cmp = a.compare(b);
			if (cmp != 0)
				return cmp < 0 ? -1 : 1;
		}
		return 0;
	}

	bool SemanticVersion::ParseNumericIdentifier(std::string_view const &input, __int32 &value) // 0x107681C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ParseNumericIdentifier@SemanticVersion@Utils@@CA_NABV?$basic_string_view@DU?$char_traits@D@std@@@std@@AAH@Z");

		value = 0;
		__int32 count = 0;
		for (std::string_view::const_iterator it = input.cbegin(); it != input.cend(); ++it)
		{
			if (!isdigit(*it))
				return false;
			value = value * 10 + (*it - '0');
			count++;
		}
		return count > 0;
	}
}

/* ---------- private code */
