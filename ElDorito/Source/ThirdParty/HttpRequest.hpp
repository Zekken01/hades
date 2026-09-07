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
	std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > _userAgent; // 0x0
public:
	__int32 lastError; // 0x1C
	std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > responseHeader; // 0x20
	std::vector<unsigned char,std::allocator<unsigned char> > responseBody; // 0x3C
	HttpRequest(HttpRequest &); /* compiler_generated() */
	HttpRequest(HttpRequest const &); /* compiler_generated() */
	HttpRequest(std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > const &userAgent, std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > const &proxyIp, std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > const &proxyPort);
	__int32 SendRequest(std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > const &uri, std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > const &method, std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > const &username, std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > const &password, std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > const &headers, void *body, unsigned long bodySize);
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
