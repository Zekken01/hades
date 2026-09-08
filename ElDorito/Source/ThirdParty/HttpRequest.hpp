#ifndef __THIRDPARTY_HTTPREQUEST_HPP__
#define __THIRDPARTY_HTTPREQUEST_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"

#include <memory>
#include <string>
#include <vector>

/* ---------- forward declarations */

class HttpRequest;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
class HttpRequest
{
private:
	std::wstring _userAgent; // 0x0
public:
	__int32 lastError; // 0x1C
	std::wstring responseHeader; // 0x20
	std::vector<unsigned char,std::allocator<unsigned char> > responseBody; // 0x3C
	HttpRequest(HttpRequest &); /* compiler_generated() */
	HttpRequest(HttpRequest const &); /* compiler_generated() */
	HttpRequest(std::wstring const &userAgent, std::wstring const &proxyIp, std::wstring const &proxyPort);
	__int32 SendRequest(std::wstring const &uri, std::wstring const &method, std::wstring const &username, std::wstring const &password, std::wstring const &headers, void *body, unsigned long bodySize);
	_inline ~HttpRequest(); /* compiler_generated() */
	HttpRequest &operator=(HttpRequest &); /* compiler_generated() */
	HttpRequest &operator=(HttpRequest const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(HttpRequest) == 76, "Invalid HttpRequest size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __THIRDPARTY_HTTPREQUEST_HPP__
