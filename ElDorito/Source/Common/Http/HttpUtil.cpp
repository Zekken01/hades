/* ---------- headers */

#include "Common/Http/HttpUtil.hpp"
#include "hades/hades.h"

#include "Common/Http/WinHttp/WinHttpCommon.hpp"
#include "Web/WebRenderHandlerGpu.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <charconv>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <memory>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>

/* ---------- forward declarations */

namespace Http
{
	struct SContentRangeHeader;
	struct WinHttpHandlerDeleter;
}

namespace Http {}
using namespace ::Http;

/* ---------- constants */

/* ---------- definitions */

namespace Http
{
	typedef std::unique_ptr<void *,Http::WinHttpHandlerDeleter> WinHttpHandle;
}

/* ---------- prototypes */

namespace Http
{
	extern bool ParseSize(std::string_view s, long long &value);
	extern bool ParseContentRangeHeader(std::string_view header, Http::SContentRangeHeader &parsedHeader);
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Http
{
	bool ParseSize(std::string_view s, long long &value) // 0x10802510
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ParseSize@Http@@YA_NV?$basic_string_view@DU?$char_traits@D@std@@@std@@AA_J@Z");
		// static ...; // 0x10802620
		// static ...; // 0x10802618
		// std::string_view s;
		// long long &value;
		// std::errc ec;
		// char const *_;
		// std::from_chars_result $S1;

		if (s.empty())
			return false;
		auto [_, ec] = std::from_chars(&*s.begin(), &*(s.end() - 1) + 1, value, 10);
		return ec == std::errc();
	}

	bool ParseContentRangeHeader(std::string_view header, Http::SContentRangeHeader &parsedHeader) // 0x10801F40
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ParseContentRangeHeader@Http@@YA_NV?$basic_string_view@DU?$char_traits@D@std@@@std@@AAUSContentRangeHeader@1@@Z");
		// static ...; // 0x108023DF
		// static ...; // 0x108023D9
		// static ...; // 0x108023CF
		// static ...; // 0x108023C6
		// static ...; // 0x108023C3
		// static ...; // 0x108023C0
		// static ...; // 0x1080236C
		// static ...; // 0x10802364
		// std::string_view header;
		// Http::SContentRangeHeader &parsedHeader;
		// std::_String_view_iterator<std::char_traits<char> > it;
		// std::string_view sizePart;
		// std::_String_view_iterator<std::char_traits<char> > start;
		// std::_String_view_iterator<std::char_traits<char> > end;
		// std::string_view rangePart;
			// std::string_view v1;
			// std::string_view v2;

		auto it = header.begin();
		auto end = header.end();
		auto start = it;
		while (it != end && *it != ' ')
			++it;
		if (it == end || *it != ' ')
			return false;
		parsedHeader.unit = std::string_view(start, it);
		start = ++it;
		while (it != end && *it != '/')
			++it;
		if (it == end || *it != '/')
			return false;
		std::string_view rangePart(start, it);
		++it;
		std::string_view sizePart(it, end);
		if (rangePart == "*")
		{
			parsedHeader.rangeStart = -1;
			parsedHeader.rangeEnd = -1;
		}
		else
		{
			it = rangePart.begin();
			end = rangePart.end();
			start = it;
			while (it != end && *it != '-')
				++it;
			if (it == end || *it != '-')
				return false;
			std::string_view v1(start, it);
			++it;
			std::string_view v2(it, end);
			if (!ParseSize(v1, parsedHeader.rangeStart))
				return false;
			if (!ParseSize(v2, parsedHeader.rangeEnd))
				return false;
		}
		if (sizePart == "*")
			parsedHeader.totalSize = -1;
		else if (!ParseSize(sizePart, parsedHeader.totalSize))
			return false;
		return true;
	}
}

/* ---------- private code */
