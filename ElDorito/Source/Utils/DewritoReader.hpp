#ifndef __UTILS_DEWRITOREADER_HPP__
#define __UTILS_DEWRITOREADER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Patches/PlayerPropertiesExtension.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/stream.h"

#include <memory>
#include <string>

/* ---------- forward declarations */

namespace Utils
{
	class DewritoReader;
}

/* ---------- constants */

/* ---------- definitions */

namespace Utils
{
	class DewritoReader :
		public Utils::Singleton<Utils::DewritoReader>
	{
	public:
		DewritoReader();
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetDewritoString();
		rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> GetDewritoJson();
		_inline bool IsValid();
	private:
		bool ReadFile(char const *path);
		bool m_isValid; // 0x0
		unsigned char __pad0[3]; // 0x1
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > m_dewrito_string; // 0x4
		rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> m_dewrito_json; // 0x20
		char const *dewrito_json_filepath; // 0x58
		char const *dewrito_json_user_filepath; // 0x5C
	public:
		~DewritoReader(); /* compiler_generated() */
	};
	static_assert(sizeof(Utils::DewritoReader) == 96, "Invalid Utils::DewritoReader size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Utils
{
	_extern bool _sub_106C9270(Utils::DewritoReader *const);
	_inline bool DewritoReader::IsValid() // 0x106C9270
	{
		mangled_x86(MANGLED_TODO, "?IsValid@DewritoReader@Utils@@QAE_NXZ");
		// Utils::DewritoReader *const this;
		todo("implement");
		bool __result = _sub_106C9270(this);
		return __result;
	}
}

/* ---------- private code */

#endif // __UTILS_DEWRITOREADER_HPP__
