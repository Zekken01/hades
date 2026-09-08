#ifndef __PLAYER_PLAYERCUSTOMIZATIONBUILDER_HPP__
#define __PLAYER_PLAYERCUSTOMIZATIONBUILDER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/Cache/StringIdCache.hpp"
#include "Blam/game/multiplayer_definitions.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_model_customization.hpp"
#include "Blam/mods/mod_globals.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Magnets.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "Patches/CustomPackets.hpp"
#include "Player/PlayerCharacterSystem.hpp"
#include "Utils/NameValueTable.hpp"

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_cache_file_tag_cache;
struct s_mod_globals_definition;
struct s_model_customization_selection;
struct s_multiplayer_globals_definition;
struct s_player_appearance;
struct s_player_character_customiztion;
namespace Blam
{
	namespace Cache
	{
		struct StringIDCache;
	}
}
namespace Player
{
	class CPlayerCharacterCustomizationBuilder;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Player
{
	class CPlayerCharacterCustomizationBuilder
	{
	public:
		public:
		struct SBaseCacheReference
		{
			std::shared_ptr<c_cache_file_tag_cache> tagCache; // 0x0
			std::shared_ptr<Blam::Cache::StringIDCache> stringCache; // 0x8
			SBaseCacheReference(SBaseCacheReference &); /* compiler_generated() */
			SBaseCacheReference(SBaseCacheReference const &); /* compiler_generated() */
			_inline SBaseCacheReference(); /* compiler_generated() */
			_inline ~SBaseCacheReference(); /* compiler_generated() */
			SBaseCacheReference &operator=(SBaseCacheReference &); /* compiler_generated() */
			SBaseCacheReference &operator=(SBaseCacheReference const &); /* compiler_generated() */
		};
		static_assert(sizeof(SBaseCacheReference) == 16, "Invalid SBaseCacheReference size");
		public:
		void SetIgnoreSession(bool);
		bool BuildCustomizationFromPlayerModel(__int32 playerModelIndex, s_player_character_customiztion *data);
		bool BuildCharacterCustomizations(std::string const &preferredCharacterName, s_player_appearance *data);
		bool BuildSingleCharacterCustomization(std::string const &characterName, s_player_character_customiztion *data);
		void SetBaseCache(std::shared_ptr<c_cache_file_tag_cache>, std::shared_ptr<Blam::Cache::StringIDCache>);
	private:
		bool Initialize();
		std::pair<int,int> FindPlayerModelPermutation(s_model_customization_selection const &selection, std::string const &regionName, std::string const &permutationName);
		__int32 FindPlayerModel(std::string const &characterName);
		bool m_initialized; // 0x0
		bool m_ignoreSession; // 0x1
		unsigned char __pad0[2]; // 0x2
		std::shared_ptr<Blam::Cache::StringIDCache> m_stringCache; // 0x4
		s_multiplayer_globals_definition *m_mulg; // 0xC
		s_mod_globals_definition *m_modg; // 0x10
		std::vector<char,std::allocator<char> > m_mulgData; // 0x14
		std::vector<char,std::allocator<char> > m_modgData; // 0x24
		SBaseCacheReference m_actualBaseCache; // 0x34
	public:
		CPlayerCharacterCustomizationBuilder(Player::CPlayerCharacterCustomizationBuilder &); /* compiler_generated() */
		CPlayerCharacterCustomizationBuilder(Player::CPlayerCharacterCustomizationBuilder const &); /* compiler_generated() */
		_inline CPlayerCharacterCustomizationBuilder(); /* compiler_generated() */
		_inline ~CPlayerCharacterCustomizationBuilder(); /* compiler_generated() */
		Player::CPlayerCharacterCustomizationBuilder &operator=(Player::CPlayerCharacterCustomizationBuilder &); /* compiler_generated() */
		Player::CPlayerCharacterCustomizationBuilder &operator=(Player::CPlayerCharacterCustomizationBuilder const &); /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Player::CPlayerCharacterCustomizationBuilder) == 68, "Invalid Player::CPlayerCharacterCustomizationBuilder size");

/* ---------- prototypes */

namespace Player
{
	extern void BuildChangeColors(unsigned long *changeColors, std::map<std::string,std::string,std::less<std::string>,std::allocator<std::pair<std::string const ,std::string> > > const &colors);
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __PLAYER_PLAYERCUSTOMIZATIONBUILDER_HPP__
