#ifndef __FORGE_PREFAB_HPP__
#define __FORGE_PREFAB_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/Geoemetry.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

namespace Forge
{
	namespace Prefabs
	{
		struct PrefabHeader;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Forge
{
	namespace Prefabs
	{
		struct PrefabHeader
		{
			unsigned __int32 Magic; // 0x0
			unsigned short Flags; // 0x4
			unsigned short Version; // 0x6
			unsigned long long DateCreated; // 0x8
			char Name[16]; // 0x10
			char Author[16]; // 0x20
			unsigned short ObjectCount; // 0x30
			unsigned short PaletteCount; // 0x32
			unsigned char __pad0[4]; // 0x34
		};
		static_assert(sizeof(Forge::Prefabs::PrefabHeader) == 56, "Invalid Forge::Prefabs::PrefabHeader size");
	}
}

/* ---------- prototypes */

namespace Forge
{
	namespace Prefabs
	{
		extern bool Save(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &author, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path);
		extern bool Load(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path);
		extern bool ReadHeader(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path, Forge::Prefabs::PrefabHeader &header);
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __FORGE_PREFAB_HPP__
