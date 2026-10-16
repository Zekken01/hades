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

HttpRequest::HttpRequest(std::wstring const &userAgent, std::wstring const &proxyIp, std::wstring const &proxyPort) : _userAgent(userAgent) /* hades-mem-init:  */ // 0x10C52A20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0HttpRequest@@QAE@ABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@00@Z");
}

__int32 HttpRequest::SendRequest(std::wstring const &uri, std::wstring const &method, std::wstring const &username, std::wstring const &password, std::wstring const &headers, void *body, unsigned long bodySize) // 0x10C52B70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SendRequest@HttpRequest@@QAEHABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@0000PAXK@Z");

	unsigned long dwSize;
	unsigned long dwDownloaded;
	unsigned long headerSize = 0;
	__int32 bResults = FALSE;
	void *hSession;
	void *hConnect;
	void *hRequest;
	responseHeader.resize(0);
	responseBody.resize(0);
	_WINHTTP_URL_COMPONENTS urlComp;
	memset(&urlComp, 0, sizeof(urlComp));
	urlComp.dwStructSize = sizeof(urlComp);
	urlComp.dwSchemeLength = (unsigned long)-1;
	urlComp.dwHostNameLength = (unsigned long)-1;
	urlComp.dwUrlPathLength = (unsigned long)-1;
	if (!WinHttpCrackUrl(uri.c_str(), uri.length(), 0, &urlComp))
		return 0;
	std::wstring scheme;
	std::wstring hostname;
	std::wstring path;
	scheme.resize(urlComp.dwSchemeLength);
	hostname.resize(urlComp.dwHostNameLength);
	path.resize(urlComp.dwUrlPathLength);
	if (urlComp.lpszScheme == nullptr)
		scheme = L"http";
	else
		memcpy(scheme.data(), urlComp.lpszScheme, urlComp.dwSchemeLength * sizeof(wchar_t));
	if (urlComp.lpszHostName == nullptr)
		hostname = L"localhost";
	else
		memcpy(hostname.data(), urlComp.lpszHostName, urlComp.dwHostNameLength * sizeof(wchar_t));
	if (urlComp.lpszUrlPath == nullptr)
		path = L"/";
	else
		memcpy(path.data(), urlComp.lpszUrlPath, urlComp.dwUrlPathLength * sizeof(wchar_t));
	unsigned long dwAccessType = WINHTTP_ACCESS_TYPE_DEFAULT_PROXY;
	wchar_t const *pszProxyW = WINHTTP_NO_PROXY_NAME;
	wchar_t const *pszProxyBypassW = WINHTTP_NO_PROXY_BYPASS;
	hSession = WinHttpOpen(_userAgent.c_str(), dwAccessType, pszProxyW, pszProxyBypassW, 0);
	if (!hSession)
	{
		lastError = 80002;
		return 0;
	}
	WinHttpSetTimeouts(hSession, 5000, 5000, 5000, 5000);
	hConnect = WinHttpConnect(hSession, hostname.c_str(), urlComp.nPort, 0);
	if (!hConnect)
	{
		lastError = 80003;
		return 0;
	}
	hRequest = WinHttpOpenRequest(hConnect, method.c_str(), path.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
	if (!username.empty() || !password.empty())
	{
		if (!WinHttpSetCredentials(hRequest, WINHTTP_AUTH_TARGET_SERVER, WINHTTP_AUTH_SCHEME_BASIC, username.c_str(), password.c_str(), NULL))
		{
			lastError = 80004;
			return 0;
		}
	}
	if (!hRequest)
	{
		lastError = 80005;
		return 0;
	}
	wchar_t const *addtHdrs = WINHTTP_NO_ADDITIONAL_HEADERS;
	unsigned long length = 0;
	if (headers.length() > 0)
	{
		addtHdrs = headers.c_str();
		length = (unsigned long)-1;
	}
	bResults = WinHttpSendRequest(hRequest, addtHdrs, length, body, bodySize, bodySize, 0);
	if (bResults)
		bResults = WinHttpReceiveResponse(hRequest, NULL);
	if (bResults)
	{
		bResults = WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, NULL, &headerSize, WINHTTP_NO_HEADER_INDEX);
		if (!bResults && GetLastError() == ERROR_INSUFFICIENT_BUFFER)
		{
			responseHeader.resize(headerSize / sizeof(wchar_t));
			if (responseHeader.empty())
				bResults = TRUE;
			else
			{
				bResults = WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, &responseHeader[0], &headerSize, WINHTTP_NO_HEADER_INDEX);
				if (!bResults)
					headerSize = 0;
				responseHeader.resize(headerSize / sizeof(wchar_t));
			}
		}
	}
	if (bResults)
	{
		do
		{
			dwSize = 0;
			bResults = WinHttpQueryDataAvailable(hRequest, &dwSize);
			if (!bResults)
			{
				std::stringstream ss;
				ss << "Error " << GetLastError() << "in WinHttpQueryDataAvailable.";
				OutputDebugStringA(ss.str().c_str());
				break;
			}
			if (dwSize == 0)
				break;
			do
			{
				unsigned long dwOffset = responseBody.size();
				responseBody.resize(dwOffset + dwSize);
				bResults = WinHttpReadData(hRequest, &responseBody[dwOffset], dwSize, &dwDownloaded);
				if (!bResults)
				{
					std::stringstream ss;
					ss << "Error " << GetLastError() << " in WinHttpReadData.";
					OutputDebugStringA(ss.str().c_str());
					dwDownloaded = 0;
				}
				responseBody.resize(dwOffset + dwDownloaded);
				if (dwDownloaded == 0)
					break;
			} while ((dwSize -= dwDownloaded) != 0);
		} while (true);
	}
	if (!bResults)
		lastError = GetLastError();
	if (hRequest)
		WinHttpCloseHandle(hRequest);
	if (hConnect)
		WinHttpCloseHandle(hConnect);
	if (hSession)
		WinHttpCloseHandle(hSession);
	return bResults;
}

/* ---------- private code */
