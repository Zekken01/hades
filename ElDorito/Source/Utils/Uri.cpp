/* ---------- headers */

#include "Utils/Uri.hpp"
#include "hades/hades.h"

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
#include <istream>
#include <limits>
#include <memory>
#include <ostream>
#include <sstream>
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

namespace Utils
{
	namespace Uri
	{
		struct UriComponents;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace Uri {}
	using namespace Utils::Uri;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Utils
{
	namespace Uri
	{
		extern bool ParseUriComponents(std::string_view uri, Utils::Uri::UriComponents &components);
		extern bool ResolveUrl(std::string const &baseUri, std::string const &relativeUri, std::string &result);
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Utils
{
	namespace Uri
	{
		_extern bool _sub_10C60260(std::string_view, Utils::Uri::UriComponents &);
		bool ParseUriComponents(std::string_view uri, Utils::Uri::UriComponents &components) // 0x10C60260
		{
			mangled_x86(MANGLED_TODO, "?ParseUriComponents@Uri@Utils@@YA_NV?$basic_string_view@DU?$char_traits@D@std@@@std@@AAUUriComponents@12@@Z");
			// static ...; // 0x10C60758
			// static ...; // 0x10C60750
			// static ...; // 0x10C6072C
			// static ...; // 0x10C60724
			// std::string_view uri;
			// Utils::Uri::UriComponents &components;
			// std::_String_view_iterator<std::char_traits<char> > it;
			// std::_String_view_iterator<std::char_traits<char> > endit;
			// std::_String_view_iterator<std::char_traits<char> > startit;
			{
				// char c;
			}
			{
			}
			{
			}
			{
			}
			todo("implement");
			bool __result = _sub_10C60260(uri, components);
			return __result;
		}

		_extern bool _sub_10C608B0(std::string const &, std::string const &, std::string &);
		bool ResolveUrl(std::string const &baseUri, std::string const &relativeUri, std::string &result) // 0x10C608B0
		{
			mangled_x86(MANGLED_TODO, "?ResolveUrl@Uri@Utils@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0AAV34@@Z");
			// static ...; // 0x10C60BD6
			// static ...; // 0x10C60BD1
			// static ...; // 0x10C60BCC
			// static ...; // 0x10C60B90
			// static ...; // 0x10C60B88
			// std::string const &baseUri;
			// std::string const &relativeUri;
			// std::string &result;
			// Utils::Uri::UriComponents relativeComponents;
			// Utils::Uri::UriComponents baseComponents;
			{
				// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
				{
					// std::string path;
				}
				{
					// unsigned __int32 filenamePos;
				}
			}
			todo("implement");
			bool __result = _sub_10C608B0(baseUri, relativeUri, result);
			return __result;
		}
	}
}

/* ---------- private code */
