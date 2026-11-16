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

s_mod_package_id::s_mod_package_id(unsigned char const (&hash)[20]) : hash() /* hades-mem-init:  */ // 0x108539C0
{
	memcpy(this->hash, hash, sizeof(this->hash));
}

std::string const s_mod_package_id::to_string() const // 0x10853BF0
{
	std::string result;
	Utils::String::BytesToHexString(hash, sizeof(hash), result);
	return result;
}

s_mod_package_id s_mod_package_id::from_string(std::string const &str) // 0x10853B10
{
	s_mod_package_id result;
	Utils::String::HexStringToBytes(str, result.hash, sizeof(result.hash));
	return result;
}

bool s_mod_package_id::operator==(s_mod_package_id const &rhs) const // 0x10853A80
{
	return memcmp(this, &rhs, 20) == 0;
}

/* ---------- private code */
