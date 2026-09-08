/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "ThirdParty/HttpRequest.hpp"

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
#include <iterator>
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
#include <vector>

/* ---------- forward declarations */

class HttpRequest;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern HttpRequest* _sub_10C52A20(HttpRequest *const, std::wstring const &, std::wstring const &, std::wstring const &);
HttpRequest::HttpRequest(std::wstring const &userAgent, std::wstring const &proxyIp, std::wstring const &proxyPort) // 0x10C52A20
{
	mangled_x86(MANGLED_TODO, "??0HttpRequest@@QAE@ABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@00@Z");
	// std::wstring const &proxyPort;
	todo("implement");
	_sub_10C52A20(this, userAgent, proxyIp, proxyPort);
}

_extern __int32 _sub_10C52B70(HttpRequest *const, std::wstring const &, std::wstring const &, std::wstring const &, std::wstring const &, std::wstring const &, void *, unsigned long);
__int32 HttpRequest::SendRequest(std::wstring const &uri, std::wstring const &method, std::wstring const &username, std::wstring const &password, std::wstring const &headers, void *body, unsigned long bodySize) // 0x10C52B70
{
	mangled_x86(MANGLED_TODO, "?SendRequest@HttpRequest@@QAEHABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@0000PAXK@Z");
	// static ...; // 0x10C5359F
	// static ...; // 0x10C5359C
	// static ...; // 0x10C53530
	// static ...; // 0x10C53528
	// HttpRequest *const this;
	// std::wstring const &uri;
	// std::wstring const &method;
	// std::wstring const &username;
	// std::wstring const &password;
	// std::wstring const &headers;
	// void *body;
	// unsigned long bodySize;
	// void *hConnect;
	// unsigned long dwSize;
	// unsigned long dwAccessType;
	// std::wstring path;
	// wchar_t const *pszProxyBypassW;
	// unsigned long length;
	// _WINHTTP_URL_COMPONENTS urlComp;
	// wchar_t const *addtHdrs;
	// wchar_t const *pszProxyW;
	// __int32 bResults;
	// void *hSession;
	// void *hRequest;
	// std::wstring hostname;
	// unsigned long dwDownloaded;
	// unsigned long headerSize;
	// std::wstring scheme;
	{
		// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
	}
	{
		// unsigned long dwOffset;
		{
			// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
		}
	}
	// function call : __int32 (wchar_t const *, unsigned long, unsigned long, _WINHTTP_URL_COMPONENTS *)
	// function call : void *(wchar_t const *, unsigned long, wchar_t const *, wchar_t const *, unsigned long)
	// function call : __int32 (void *, __int32, __int32, __int32, __int32)
	// function call : void *(void *, wchar_t const *, unsigned short, unsigned long)
	// function call : void *(void *, wchar_t const *, wchar_t const *, wchar_t const *, wchar_t const *, wchar_t const **, unsigned long)
	// function call : __int32 (void *, unsigned long, unsigned long, wchar_t const *, wchar_t const *, void *)
	// function call : __int32 (void *, wchar_t const *, unsigned long, void *, unsigned long, unsigned long, unsigned long)
	// function call : __int32 (void *, void *)
	// function call : __int32 (void *, unsigned long, wchar_t const *, void *, unsigned long *, unsigned long *)
	// function call : unsigned long ()
	// function call : __int32 (void *, unsigned long, wchar_t const *, void *, unsigned long *, unsigned long *)
	// function call : __int32 (void *, unsigned long *)
	// function call : unsigned long ()
	// function call : void (char const *)
	// function call : __int32 (void *, void *, unsigned long, unsigned long *)
	// function call : unsigned long ()
	// function call : void (char const *)
	// function call : unsigned long ()
	// function call : __int32 (void *)
	// function call : __int32 (void *)
	// function call : __int32 (void *)
	todo("implement");
	__int32 __result = _sub_10C52B70(this, uri, method, username, password, headers, body, bodySize);
	return __result;
}

/* ---------- private code */
