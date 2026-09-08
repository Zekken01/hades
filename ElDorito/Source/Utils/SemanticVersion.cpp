/* ---------- headers */

#include "Utils/SemanticVersion.hpp"
#include "hades/hades.h"

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
		extern std::basic_regex<char,std::regex_traits<char> > kPattern; // 0x1138CE6C
	}
	using namespace hades_file_local_Utils;
}
/* ---------- public code */

namespace Utils
{
	extern SemanticVersion* _sub_107627C0(Utils::SemanticVersion *const, __int32, __int32, __int32, std::string, std::string);
	SemanticVersion::SemanticVersion(__int32 major, __int32 minor, __int32 patch, std::string prerelease, std::string build) // 0x107627C0
	{
		mangled_x86(MANGLED_TODO, "??0SemanticVersion@Utils@@QAE@HHHV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
		// std::string build;
		todo("implement");
		_sub_107627C0(this, major, minor, patch, prerelease, build);
	}
}

extern std::string _sub_10768300(Utils::SemanticVersion const *const);
namespace Utils
{
	std::string SemanticVersion::ToString() const // 0x10768300
	{
		mangled_x86(MANGLED_TODO, "?ToString@SemanticVersion@Utils@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// static ...; // 0x107684D8
		// static ...; // 0x107684CC
		// static ...; // 0x107684C4
		// Utils::SemanticVersion const *const this;
		// std::string result;
		todo("implement");
		std::string __result = _sub_10768300((Utils::SemanticVersion const *)this);
		return __result;
	}

	_extern bool _sub_10768560(std::string const &, Utils::SemanticVersion &);
	bool SemanticVersion::TryParse(std::string const &input, Utils::SemanticVersion &outVersion) // 0x10768560
	{
		mangled_x86(MANGLED_TODO, "?TryParse@SemanticVersion@Utils@@SA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAU12@@Z");
		// std::string const &input;
		// Utils::SemanticVersion &outVersion;
		todo("implement");
		bool __result = _sub_10768560(input, outVersion);
		return __result;
	}

	extern SemanticVersion _sub_10767DF0(std::string const &);
	Utils::SemanticVersion SemanticVersion::Parse(std::string const &input) // 0x10767DF0
	{
		mangled_x86(MANGLED_TODO, "?Parse@SemanticVersion@Utils@@SA?AU12@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x107680F0
		// static ...; // 0x107680E4
		// static ...; // 0x107680DC
		// std::string const &input;
		// std::match_results<std::_String_const_iterator<std::_String_val<std::_Simple_types<char> > >,std::allocator<std::sub_match<std::_String_const_iterator<std::_String_val<std::_Simple_types<char> > > > > > matches;
		todo("implement");
		Utils::SemanticVersion __result = _sub_10767DF0(input);
		return __result;
	}

	_extern __int32 _sub_107678E0(Utils::SemanticVersion const &, Utils::SemanticVersion const &);
	__int32 SemanticVersion::Compare(Utils::SemanticVersion const &a, Utils::SemanticVersion const &b) // 0x107678E0
	{
		mangled_x86(MANGLED_TODO, "?Compare@SemanticVersion@Utils@@CAHABU12@0@Z");
		// Utils::SemanticVersion const &b;
		todo("implement");
		__int32 __result = _sub_107678E0(a, b);
		return __result;
	}

	_extern __int32 _sub_10767BF0(std::string_view const &, std::string_view const &);
	__int32 SemanticVersion::ComparePrerelease(std::string_view const &a, std::string_view const &b) // 0x10767BF0
	{
		mangled_x86(MANGLED_TODO, "?ComparePrerelease@SemanticVersion@Utils@@CAHABV?$basic_string_view@DU?$char_traits@D@std@@@std@@0@Z");
		// static ...; // 0x10767D70
		// static ...; // 0x10767D58
		// static ...; // 0x10767D50
		// std::string_view const &a;
		// std::string_view const &b;
		// unsigned __int32 pos1;
		// unsigned __int32 pos2;
		{
			// unsigned __int32 next_pos1;
			// std::string_view identifier1;
			// unsigned __int32 next_pos2;
			// __int32 cmp;
			// std::string_view identifier2;
		}
		todo("implement");
		__int32 __result = _sub_10767BF0(a, b);
		return __result;
	}

	_extern __int32 _sub_10767A60(std::string_view const &, std::string_view const &);
	__int32 SemanticVersion::CompareIdentifier(std::string_view const &a, std::string_view const &b) // 0x10767A60
	{
		mangled_x86(MANGLED_TODO, "?CompareIdentifier@SemanticVersion@Utils@@CAHABV?$basic_string_view@DU?$char_traits@D@std@@@std@@0@Z");
		// static ...; // 0x10767B94
		// static ...; // 0x10767B7C
		// static ...; // 0x10767B74
		// std::string_view const &a;
		// std::string_view const &b;
		// bool a_num;
		// __int32 num2;
		// __int32 num1;
		// bool b_num;
		{
			// __int32 const cmp;
		}
		todo("implement");
		__int32 __result = _sub_10767A60(a, b);
		return __result;
	}

	_extern bool _sub_107681C0(std::string_view const &, __int32 &);
	bool SemanticVersion::ParseNumericIdentifier(std::string_view const &input, __int32 &value) // 0x107681C0
	{
		mangled_x86(MANGLED_TODO, "?ParseNumericIdentifier@SemanticVersion@Utils@@CA_NABV?$basic_string_view@DU?$char_traits@D@std@@@std@@AAH@Z");
		// static ...; // 0x107682B0
		// static ...; // 0x107682A8
		// std::string_view const &input;
		// __int32 &value;
		// __int32 count;
		{
			// std::_String_view_iterator<std::char_traits<char> > it;
		}
		todo("implement");
		bool __result = _sub_107681C0(input, value);
		return __result;
	}
}

/* ---------- private code */
