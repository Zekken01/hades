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
		bool ParseUriComponents(std::string_view uri, Utils::Uri::UriComponents &components) // 0x10C60260
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ParseUriComponents@Uri@Utils@@YA_NV?$basic_string_view@DU?$char_traits@D@std@@@std@@AAUUriComponents@12@@Z");

			auto it = uri.begin();
			auto endit = uri.end();
			auto startit = it;
			while (it != endit)
			{
				char c = *it;
				if (c == ':' || c == '/' || c == '?' || c == '#')
					break;
				++it;
			}
			if (it == endit || *it++ != ':')
				return false;
			components.scheme = std::string_view(startit, it - 1);
			if (it == endit || *it++ != '/' || it == endit || *it++ != '/')
				return false;
			startit = it;
			while (it != endit)
			{
				char c = *it;
				if (c == '/' || c == '?' || c == '#')
					break;
				++it;
			}
			components.authority = std::string_view(startit, it);
			startit = it;
			while (it != endit)
			{
				char c = *it;
				if (c == '?' || c == '#')
					break;
				++it;
			}
			components.path = std::string_view(startit, it);
			if (it != endit && *it == '?')
			{
				startit = ++it;
				while (it != endit)
				{
					char c = *it;
					if (c == '#')
						break;
					++it;
				}
				components.query = std::string_view(startit, it);
			}
			if (it != endit && *it == '#')
				components.fragment = std::string_view(it + 1, endit);
			return true;
		}

		bool ResolveUrl(std::string const &baseUri, std::string const &relativeUri, std::string &result) // 0x10C608B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ResolveUrl@Uri@Utils@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0AAV34@@Z");

			Utils::Uri::UriComponents baseComponents;
			if (!ParseUriComponents(baseUri, baseComponents))
				return false;
			Utils::Uri::UriComponents relativeComponents;
			if (!ParseUriComponents(relativeUri, relativeComponents) || relativeComponents.scheme.empty())
			{
				std::stringstream ss;
				if (relativeUri.starts_with("/"))
				{
					std::string path = relativeUri;
					if (path.starts_with("/"))
						path.erase(0, 1);
					ss << baseComponents.scheme << "://" << baseComponents.authority << "/" << path;
				}
				else
				{
					std::string path = relativeUri;
					unsigned __int32 filenamePos = path.find_last_of('/');
					if (filenamePos != -1)
						path.erase(filenamePos);
					ss << baseComponents.scheme << "://" << baseComponents.authority << "/" << path << "/" << relativeUri;
				}
				result = ss.str();
			}
			else
			{
				result = relativeUri;
			}
			return true;
		}
	}
}

/* ---------- private code */
