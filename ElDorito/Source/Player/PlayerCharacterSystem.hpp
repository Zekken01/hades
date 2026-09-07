#ifndef __PLAYER_PLAYERCHARACTERSYSTEM_HPP__
#define __PLAYER_PLAYERCHARACTERSYSTEM_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/game/player_appearance.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

class c_cache_file_tag_cache;
struct s_player_appearance;
struct s_player_character_customiztion;
struct s_player_emblem_configuration;
struct s_player_model_customization;
namespace Blam
{
	namespace Cache
	{
		struct StringIDCache;
	}
}
namespace Player
{
	struct CPlayerCharacterSystem;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_player_model_customization
{
	unsigned long colors[5]; // 0x0
	char armor_section_indices[16]; // 0x14
};
#pragma pack(pop)
static_assert(sizeof(s_player_model_customization) == 36, "Invalid s_player_model_customization size");

struct s_player_appearance
{
	unsigned char gender; // 0x0
	unsigned char player_model; // 0x1
	unsigned char unused1[1618]; // 0x2
	wchar_t service_tag[5]; // 0x654
	char _pad[2]; // 0x65E
	unsigned char __pad0[8]; // 0x660
	s_player_model_customization model_customization; // 0x668
	unsigned long nameplate_color; // 0x68C
	unsigned long preferred_character; // 0x690
	long characters_count; // 0x694
	s_player_character_customiztion characters[16]; // 0x698
	s_player_emblem_configuration emblem_config; // 0x918
	long nameplate_index; // 0x92C
	_inline s_player_appearance(); /* compiler_generated() */
};
static_assert(sizeof(s_player_appearance) == 2352, "Invalid s_player_appearance size");

namespace Player
{
	struct CPlayerCharacterSystem
	{
		static void Init();
		static void Tick();
		static void NotifyTagsLoaded(bool isMainMenuMod, std::shared_ptr<c_cache_file_tag_cache> baseCache, std::shared_ptr<Blam::Cache::StringIDCache> baseStringCache);
		static void AssignPlayerCharacter(__int32 playerIndex);
		static void PlayerCharacterEditor(__int32 playerIndex);
		static void UpdateLocalPlayerHudGlobals();
		static bool BuildCustomizations(s_player_appearance &appearance);
		static bool BuildCharacterCustomization(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &characterName, s_player_model_customization &customization);
		static void ReloadCustomizations();
	};
	static_assert(sizeof(Player::CPlayerCharacterSystem) == 1, "Invalid Player::CPlayerCharacterSystem size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __PLAYER_PLAYERCHARACTERSYSTEM_HPP__
