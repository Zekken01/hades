#ifndef __SERVER_MODBROWSER_MODBROWSERDEFINITIONS_HPP__
#define __SERVER_MODBROWSER_MODBROWSERDEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Utils/StlUtil.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

struct SModBrowserState;

/* ---------- constants */

/* ---------- definitions */

struct SModBrowserState
{
	public:
#pragma pack(push, 4)
	struct SRequestedMod
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
		SRequestedMod(SRequestedMod &); /* compiler_generated() */
		SRequestedMod(SRequestedMod const &); /* compiler_generated() */
		_inline SRequestedMod(); /* compiler_generated() */
		_inline ~SRequestedMod(); /* compiler_generated() */
		_inline SRequestedMod &operator=(SRequestedMod &&__that); /* compiler_generated() */
		_inline SRequestedMod &operator=(SRequestedMod const &__that); /* compiler_generated() */
	};
#pragma pack(pop)
	static_assert(sizeof(SRequestedMod) == 260, "Invalid SRequestedMod size");
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
	SRequestedMod requestedMod; // 0xA0
	bool modDownloadConfirmed; // 0x1A4
	SModBrowserState(SModBrowserState &); /* compiler_generated() */
	SModBrowserState(SModBrowserState const &); /* compiler_generated() */
	_inline SModBrowserState(); /* compiler_generated() */
	_inline ~SModBrowserState(); /* compiler_generated() */
	_inline SModBrowserState &operator=(SModBrowserState &&__that); /* compiler_generated() */
	SModBrowserState &operator=(SModBrowserState const &); /* compiler_generated() */
	unsigned char __pad0[3]; // 0x1A5
};
static_assert(sizeof(SModBrowserState) == 424, "Invalid SModBrowserState size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __SERVER_MODBROWSER_MODBROWSERDEFINITIONS_HPP__
