/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Utils/String.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <ios>
#include <iosfwd>
#include <limits>
#include <memory>
#include <mutex>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

namespace Utils {}
using namespace ::Utils;
namespace Debug {}
using namespace ::Debug;
namespace Debug
{
	namespace CrashReporting {}
	using namespace Debug::CrashReporting;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Utils { namespace Jpeg { extern void CompressBuf(std::vector<unsigned char> &dest, __int32 quality, unsigned char const *srcBits, __int32 width, __int32 height); } }  // hades: added for 0x106978B0  // hades: added for 0x106978B0

namespace Debug
{
	namespace CrashReporting
	{
		extern std::string TakeScreenshot();
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */


namespace Debug
{
	namespace CrashReporting
	{
		std::string TakeScreenshot() // 0x106978B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?TakeScreenshot@CrashReporting@Debug@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
			// procedure flags: nofpo
			// static ...; // 0x10697CD8
			// static ...; // 0x10697CD4
			// static ...; // 0x10697CD0
			// static ...; // 0x10697CAC
			// static ...; // 0x10697CA4
		// $LN19:
				// HBITMAP__ *bmpDest;
				// HWND__ *hwndSrc;
				// unsigned char *bits;
				// tagRECT rc;
				// __int32 sx;
				// std::vector<unsigned char> buf;
				// __int32 sy;
				// HDC__ *dcSrc;
				// HDC__ *dcDst;
				// tagBITMAPINFO bmi;
			// function call : __int32 (HWND__ *, tagRECT *)
			// function call : HDC__ *(HWND__ *)
			// function call : HDC__ *(HDC__ *)
			// function call : HBITMAP__ *(HDC__ *, __int32, __int32)
			// function call : void *(HDC__ *, void *)
			// function call : __int32 (HDC__ *, __int32, __int32, __int32, __int32, HDC__ *, __int32, __int32, unsigned long)
			// function call : __int32 (HDC__ *, HBITMAP__ *, unsigned __int32, unsigned __int32, void *, tagBITMAPINFO *, unsigned __int32)
			// function call : __int32 (HDC__ *, HBITMAP__ *, unsigned __int32, unsigned __int32, void *, tagBITMAPINFO *, unsigned __int32)

			try
			{
				HWND__ *hwndSrc = *(HWND__ **)0x199C014;
				if (!hwndSrc)
					return {};
				tagRECT rc;
				if (!GetClientRect(hwndSrc, &rc))
					return {};
				__int32 sx = rc.right - rc.left;
				__int32 sy = rc.bottom - rc.top;
				HDC__ *dcSrc = GetDC(hwndSrc);
				if (!dcSrc)
					return {};
				HDC__ *dcDst = CreateCompatibleDC(dcSrc);
				if (!dcDst)
					return {};
				HBITMAP__ *bmpDest = CreateCompatibleBitmap(dcSrc, sx, sy);
				if (!bmpDest || !SelectObject(dcDst, bmpDest))
					return {};
				if (!BitBlt(dcDst, 0, 0, sx, sy, dcSrc, 0, 0, SRCCOPY))
					return {};
				tagBITMAPINFO bmi;
				memset(&bmi, 0, sizeof(bmi));
				bmi.bmiHeader.biSize = sizeof(tagBITMAPINFOHEADER);
				if (!GetDIBits(dcDst, bmpDest, 0, 0, nullptr, &bmi, DIB_RGB_COLORS))
					return {};
				bmi.bmiHeader.biBitCount = 32;
				bmi.bmiHeader.biCompression = BI_RGB;
				bmi.bmiHeader.biHeight = -bmi.bmiHeader.biHeight;
				unsigned char *bits = new unsigned char[bmi.bmiHeader.biSizeImage];
				if (!GetDIBits(dcDst, bmpDest, 0, bmi.bmiHeader.biHeight, bits, &bmi, DIB_RGB_COLORS))
					return {};
				std::vector<unsigned char> buf;
				Utils::Jpeg::CompressBuf(buf, 80, bits, sx, sy);
				return Utils::String::Base64Encode(buf.data(), buf.size());
			}
			catch (...)
			{
			}
			return {};
		}
	}
}

/* ---------- private code */
