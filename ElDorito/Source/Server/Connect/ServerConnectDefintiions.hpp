#ifndef __SERVER_CONNECT_SERVERCONNECTDEFINTIIONS_HPP__
#define __SERVER_CONNECT_SERVERCONNECTDEFINTIIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Utils/StlUtil.hpp"

#include <memory>
#include <string>
#include <vector>

/* ---------- forward declarations */

struct SServerConnectOptions;
struct SServerConnectState;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct SServerConnectOptions
{
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > hostname; // 0x0
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > password; // 0x1C
	__int32 port; // 0x38
	SServerConnectOptions(SServerConnectOptions &); /* compiler_generated() */
	SServerConnectOptions(SServerConnectOptions const &); /* compiler_generated() */
	_inline SServerConnectOptions(); /* compiler_generated() */
	_inline ~SServerConnectOptions(); /* compiler_generated() */
	SServerConnectOptions &operator=(SServerConnectOptions &); /* compiler_generated() */
	SServerConnectOptions &operator=(SServerConnectOptions const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(SServerConnectOptions) == 60, "Invalid SServerConnectOptions size");

#pragma pack(push, 4)
struct SServerConnectState
{
	public:
#pragma pack(push, 4)
	struct SRequiredMod
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > localName; // 0x0
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > name; // 0x1C
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > author; // 0x38
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > description; // 0x54
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > hash; // 0x70
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > packageUrl; // 0x8C
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > version; // 0xA8
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > website; // 0xC4
		unsigned __int32 fileSize; // 0xE0
		bool verificationFailed; // 0xE4
		unsigned char __pad0[3]; // 0xE5
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > downloadPath; // 0xE8
		_inline SRequiredMod(SRequiredMod &&__that); /* compiler_generated() */
		_inline SRequiredMod(SRequiredMod const &__that); /* compiler_generated() */
		_inline SRequiredMod(); /* compiler_generated() */
		_inline ~SRequiredMod(); /* compiler_generated() */
		SRequiredMod &operator=(SRequiredMod &); /* compiler_generated() */
		_inline SRequiredMod &operator=(SRequiredMod const &__that); /* compiler_generated() */
	};
#pragma pack(pop)
	static_assert(sizeof(SRequiredMod) == 260, "Invalid SRequiredMod size");
	public:
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > serverName; // 0x0
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > serverHost; // 0x1C
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > hostname; // 0x38
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > password; // 0x54
	__int32 port; // 0x70
	__int32 gamePort; // 0x74
	__int32 fileServerPort; // 0x78
	unsigned __int32 address; // 0x7C
	unsigned char xnkid[16]; // 0x80
	unsigned char xnaddr[16]; // 0x90
	std::vector<SRequiredMod,std::allocator<SRequiredMod> > requiredMods; // 0xA0
	bool modDownloadConfirmed; // 0xB0
	SServerConnectState(SServerConnectState &); /* compiler_generated() */
	SServerConnectState(SServerConnectState const &); /* compiler_generated() */
	SServerConnectState(); /* compiler_generated() */
	_inline ~SServerConnectState(); /* compiler_generated() */
	_inline SServerConnectState &operator=(SServerConnectState &&__that); /* compiler_generated() */
	SServerConnectState &operator=(SServerConnectState const &); /* compiler_generated() */
	unsigned char __pad0[3]; // 0xB1
};
#pragma pack(pop)
static_assert(sizeof(SServerConnectState) == 180, "Invalid SServerConnectState size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __SERVER_CONNECT_SERVERCONNECTDEFINTIIONS_HPP__
