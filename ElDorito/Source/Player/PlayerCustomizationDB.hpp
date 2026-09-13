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
		std::map<std::string,std::string> colors; // 0x0
		std::map<std::string,std::string> permutations; // 0xC
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
		bool Load(std::string const &filename);
		void Save();
		void Save(std::string const &filename);
		void Reload();
		void Reset();
		std::vector<std::string> GetCharacters();
		std::string GetPreferredCharacter(std::string const &target) const;
		bool SetPreferredCharacter(std::string const &target, std::string const &characterName);
		bool GetCharacterCustomization(std::string const &characterName, Player::SPersistentCharacterCustomization &customization) const;
		bool SetCharacterCustomization(std::string const &characterName, Player::SPersistentCharacterCustomization const &customization);
		bool SetCharacterPermutation(std::string const &characterName, std::string const &regionName, std::string const &permutationName);
		bool SetCharacterColor(std::string const &characterName, std::string const &colorName, std::string const &colorValue);
	private:
		std::string m_fileName; // 0x0
		std::map<std::string,Player::SPersistentCharacterCustomization> m_customizations; // 0x1C
		std::map<std::string,std::string> m_preferredCharacters; // 0x28
	public:
		_inline CPlayerCustomizationDB() = default; /* compiler_generated() - defaulted on its
		    first declaration, so it is NOT user-provided and `new CPlayerCustomizationDB()`
		    zero-initializes before constructing, as the original does. */
		~CPlayerCustomizationDB() = default; /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Player::CPlayerCustomizationDB) == 52, "Invalid Player::CPlayerCustomizationDB size");

/* ---------- prototypes */

namespace Player
{
	extern Player::SPersistentCharacterCustomization LoadCustomization(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &value);
	extern std::map<std::string,Player::SPersistentCharacterCustomization> LoadCustomizations(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &value);
	extern void SaveCustomization(rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, Player::SPersistentCharacterCustomization const &customization);
	extern void SaveCustomizations(rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, std::map<std::string,Player::SPersistentCharacterCustomization> const &customizations);
	extern std::map<std::string,std::string> LoadPreferredCharacters(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &value);
	extern void SavePreferredCharacters(rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, std::map<std::string,std::string> const &preferredCharacters);
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __PLAYER_PLAYERCUSTOMIZATIONDB_HPP__
