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
	extern bool ParseSize(std::basic_string_view<char,std::char_traits<char> > s, long long &value);
	extern bool ParseContentRangeHeader(std::basic_string_view<char,std::char_traits<char> > header, Http::SContentRangeHeader &parsedHeader);
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Http
{
	_extern bool _sub_10802510(std::basic_string_view<char,std::char_traits<char> >, long long &);
	bool ParseSize(std::basic_string_view<char,std::char_traits<char> > s, long long &value) // 0x10802510
	{
		mangled_x86(MANGLED_TODO, "?ParseSize@Http@@YA_NV?$basic_string_view@DU?$char_traits@D@std@@@std@@AA_J@Z");
		// static ...; // 0x10802620
		// static ...; // 0x10802618
		// std::basic_string_view<char,std::char_traits<char> > s;
		// long long &value;
		// std::errc ec;
		// char const *_;
		// std::from_chars_result $S1;
		todo("implement");
		bool __result = _sub_10802510(s, value);
		return __result;
	}

	_extern bool _sub_10801F40(std::basic_string_view<char,std::char_traits<char> >, Http::SContentRangeHeader &);
	bool ParseContentRangeHeader(std::basic_string_view<char,std::char_traits<char> > header, Http::SContentRangeHeader &parsedHeader) // 0x10801F40
	{
		mangled_x86(MANGLED_TODO, "?ParseContentRangeHeader@Http@@YA_NV?$basic_string_view@DU?$char_traits@D@std@@@std@@AAUSContentRangeHeader@1@@Z");
		// static ...; // 0x108023DF
		// static ...; // 0x108023D9
		// static ...; // 0x108023CF
		// static ...; // 0x108023C6
		// static ...; // 0x108023C3
		// static ...; // 0x108023C0
		// static ...; // 0x1080236C
		// static ...; // 0x10802364
		// std::basic_string_view<char,std::char_traits<char> > header;
		// Http::SContentRangeHeader &parsedHeader;
		// std::_String_view_iterator<std::char_traits<char> > it;
		// std::basic_string_view<char,std::char_traits<char> > sizePart;
		// std::_String_view_iterator<std::char_traits<char> > start;
		// std::_String_view_iterator<std::char_traits<char> > end;
		// std::basic_string_view<char,std::char_traits<char> > rangePart;
		{
			// std::basic_string_view<char,std::char_traits<char> > v1;
			// std::basic_string_view<char,std::char_traits<char> > v2;
		}
		todo("implement");
		bool __result = _sub_10801F40(header, parsedHeader);
		return __result;
	}
}

/* ---------- private code */
