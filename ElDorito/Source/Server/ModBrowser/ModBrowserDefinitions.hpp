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
		std::string localName; // 0x0
		std::string name; // 0x1C
		std::string author; // 0x38
		std::string description; // 0x54
		std::string hash; // 0x70
		std::string packageUrl; // 0x8C
		std::string version; // 0xA8
		std::string website; // 0xC4
		unsigned __int32 fileSize; // 0xE0
		bool verificationFailed; // 0xE4
		std::string downloadPath; // 0xE8
		// SRequestedMod(SRequestedMod &); hades: implicit, the original aggregate-initializes it
		// SRequestedMod(SRequestedMod const &); hades: implicit, the original aggregate-initializes it
		// _inline SRequestedMod() = default; hades: implicit, the original aggregate-initializes it
		_inline ~SRequestedMod(); /* compiler_generated() */
		_inline SRequestedMod &operator=(SRequestedMod &&__that) noexcept; /* compiler_generated() */
		_inline SRequestedMod &operator=(SRequestedMod const &__that); /* compiler_generated() */
	};
#pragma pack(pop)
	static_assert(sizeof(SRequestedMod) == 260, "Invalid SRequestedMod size");
	public:
	std::string serverName; // 0x0
	std::string serverHost; // 0x1C
	std::string hostname; // 0x38
	std::string password; // 0x54
	__int32 port; // 0x70
	__int32 gamePort; // 0x74
	__int32 fileServerPort; // 0x78
	unsigned __int32 address; // 0x7C
	unsigned char xnkid[16]; // 0x80
	unsigned char xnaddr[16]; // 0x90
	SRequestedMod requestedMod; // 0xA0
	bool modDownloadConfirmed; // 0x1A4
	// SModBrowserState(SModBrowserState &); hades: implicit, the original aggregate-initializes it
	// SModBrowserState(SModBrowserState const &); hades: implicit, the original aggregate-initializes it
	// _inline SModBrowserState() = default; hades: implicit, the original aggregate-initializes it
	_inline ~SModBrowserState(); /* compiler_generated() */
	_inline SModBrowserState &operator=(SModBrowserState &&__that) noexcept; /* compiler_generated() */
	SModBrowserState &operator=(SModBrowserState const &); /* compiler_generated() */
};
static_assert(sizeof(SModBrowserState) == 424, "Invalid SModBrowserState size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __SERVER_MODBROWSER_MODBROWSERDEFINITIONS_HPP__
