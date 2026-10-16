#ifndef __MODS_MOD_PACKAGE_BLF_HPP__
#define __MODS_MOD_PACKAGE_BLF_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/saved_games/blf.hpp"
#include "mods/mod_package_cache.hpp"

/* ---------- forward declarations */

struct s_blf_chunk_header;
struct s_blf_chunk_mod_package_reference;
struct s_mod_package_metadata;
struct s_mod_package_reference;
struct s_mod_package_reference_v1;

/* ---------- constants */

enum
{
	_mod_package_reference_v1 = 1, // 0x0001
	_mod_package_reference_v2 = 2, // 0x0002
};

/* ---------- definitions */

#pragma pack(push, 4)
struct s_mod_package_reference_v1
{
	wchar_t name[16]; // 0x0
	char author[16]; // 0x20
	unsigned char sha1[20]; // 0x30
};
#pragma pack(pop)
static_assert(sizeof(s_mod_package_reference_v1) == 68, "Invalid s_mod_package_reference_v1 size");

#pragma pack(push, 4)
struct s_mod_package_reference
{
	unsigned char sha1[20]; // 0x0
	s_mod_package_metadata metadata; // 0x14
};
#pragma pack(pop)
static_assert(sizeof(s_mod_package_reference) == 1156, "Invalid s_mod_package_reference size");

struct s_blf_chunk_mod_package_reference :
	public s_blf_chunk_header,
	public s_mod_package_reference
{
	_inline s_blf_chunk_mod_package_reference();
};
static_assert(sizeof(s_blf_chunk_mod_package_reference) == 1168, "Invalid s_blf_chunk_mod_package_reference size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline s_blf_chunk_mod_package_reference::s_blf_chunk_mod_package_reference() // 0x10AC8640
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_blf_chunk_mod_package_reference@@QAE@XZ");

	setup(0x6D6F6470, 0x490, 2, 0);
}

/* ---------- private code */

#endif // __MODS_MOD_PACKAGE_BLF_HPP__
