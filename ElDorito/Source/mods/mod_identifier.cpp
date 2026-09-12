/* ---------- headers */

#include "mods/mod_identifier.hpp"
#include "hades/hades.h"

#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"

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
#include <ios>
#include <iosfwd>
#include <limits>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

struct s_mod_package_id;

namespace Utils {}
using namespace ::Utils;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern s_mod_package_id* _sub_108539C0(s_mod_package_id *const, unsigned char const (&)[20]);
s_mod_package_id::s_mod_package_id(unsigned char const (&hash)[20]) // 0x108539C0
{
	mangled_x86(MANGLED_TODO, "??0s_mod_package_id@@QAE@AAY0BE@$$CBE@Z");
	// unsigned char const (&hash)[20];
	todo("implement");
	_sub_108539C0(this, hash);
}

extern std::string const _sub_10853BF0(s_mod_package_id const *const);
std::string const s_mod_package_id::to_string() const // 0x10853BF0
{
	mangled_x86(MANGLED_TODO, "?to_string@s_mod_package_id@@QBE?BV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// static ...; // 0x10853CDC
	// static ...; // 0x10853CD0
	// static ...; // 0x10853CC8
	// s_mod_package_id const *const this;
	// std::string result;
	todo("implement");
	std::string const __result = _sub_10853BF0((s_mod_package_id const *)this);
	return __result;
}

extern s_mod_package_id _sub_10853B10(std::string const &);
s_mod_package_id s_mod_package_id::from_string(std::string const &str) // 0x10853B10
{
	mangled_x86(MANGLED_TODO, "?from_string@s_mod_package_id@@SA?AU1@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// static ...; // 0x10853BB8
	// static ...; // 0x10853BAC
	// static ...; // 0x10853BA4
	// std::string const &str;
	// s_mod_package_id result;
	todo("implement");
	s_mod_package_id __result = _sub_10853B10(str);
	return __result;
}

bool s_mod_package_id::operator==(s_mod_package_id const &rhs) const // 0x10853A80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??8s_mod_package_id@@QBE_NABU0@@Z");
	// s_mod_package_id const &rhs;

	return memcmp(this, &rhs, 20) == 0;
}

/* ---------- private code */
