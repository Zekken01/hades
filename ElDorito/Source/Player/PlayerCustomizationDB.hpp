#ifndef __PLAYER_PLAYERCUSTOMIZATIONDB_HPP__
#define __PLAYER_PLAYERCUSTOMIZATIONDB_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Prefab.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/ostreamwrapper.h"
#include "ThirdParty/rapidjson/prettywriter.h"
#include "ThirdParty/rapidjson/stream.h"
#include "Utils/NameValueTable.hpp"

#include <functional>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Player
{
	class CPlayerCustomizationDB;
	struct SPersistentCharacterCustomization;
}

/* ---------- constants */

/* ---------- definitions */

namespace Player
{
	struct SPersistentCharacterCustomization
	{
		std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > colors; // 0x0
		std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > permutations; // 0xC
		_inline SPersistentCharacterCustomization(Player::SPersistentCharacterCustomization &&__that); /* compiler_generated() */
		SPersistentCharacterCustomization(Player::SPersistentCharacterCustomization const &); /* compiler_generated() */
		_inline SPersistentCharacterCustomization(); /* compiler_generated() */
		_inline ~SPersistentCharacterCustomization(); /* compiler_generated() */
		Player::SPersistentCharacterCustomization &operator=(Player::SPersistentCharacterCustomization &); /* compiler_generated() */
		_inline Player::SPersistentCharacterCustomization &operator=(Player::SPersistentCharacterCustomization const &__that); /* compiler_generated() */
	};
	static_assert(sizeof(Player::SPersistentCharacterCustomization) == 24, "Invalid Player::SPersistentCharacterCustomization size");
}

#pragma pack(push, 4)
namespace Player
{
	class CPlayerCustomizationDB :
		public Utils::Singleton<Player::CPlayerCustomizationDB>
	{
	public:
		bool Load(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &filename);
		void Save();
		void Save(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &filename);
		void Reload();
		void Reset();
		std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > GetCharacters();
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetPreferredCharacter(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &target) const;
		bool SetPreferredCharacter(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &target, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &characterName);
		bool GetCharacterCustomization(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &characterName, Player::SPersistentCharacterCustomization &customization) const;
		bool SetCharacterCustomization(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &characterName, Player::SPersistentCharacterCustomization const &customization);
		bool SetCharacterPermutation(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &characterName, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &regionName, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &permutationName);
		bool SetCharacterColor(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &characterName, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &colorName, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &colorValue);
	private:
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > m_fileName; // 0x0
		std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,Player::SPersistentCharacterCustomization,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,Player::SPersistentCharacterCustomization> > > m_customizations; // 0x1C
		std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > m_preferredCharacters; // 0x28
	public:
		_inline CPlayerCustomizationDB(); /* compiler_generated() */
		~CPlayerCustomizationDB(); /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Player::CPlayerCustomizationDB) == 52, "Invalid Player::CPlayerCustomizationDB size");

/* ---------- prototypes */

namespace Player
{
	extern Player::SPersistentCharacterCustomization LoadCustomization(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &value);
	extern std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,Player::SPersistentCharacterCustomization,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,Player::SPersistentCharacterCustomization> > > LoadCustomizations(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &value);
	extern void SaveCustomization(rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::basic_ostream<char,std::char_traits<char> > >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, Player::SPersistentCharacterCustomization const &customization);
	extern void SaveCustomizations(rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::basic_ostream<char,std::char_traits<char> > >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,Player::SPersistentCharacterCustomization,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,Player::SPersistentCharacterCustomization> > > const &customizations);
	extern std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > LoadPreferredCharacters(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &value);
	extern void SavePreferredCharacters(rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::basic_ostream<char,std::char_traits<char> > >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > const &preferredCharacters);
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __PLAYER_PLAYERCUSTOMIZATIONDB_HPP__
