#ifndef __PLAYER_PLAYERCUSTOMIZATIONEXTENSION_HPP__
#define __PLAYER_PLAYERCUSTOMIZATIONEXTENSION_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BitStream.hpp"
#include "Blam/game/player_configuration.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Player/PlayerCharacterSystem.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

struct s_player_appearance;
struct s_player_configuration;
struct s_player_model_customization;
namespace Blam
{
	class BitStream;
}
namespace Player
{
	class PlayerCustomizationExtensions;
}

/* ---------- constants */

/* ---------- definitions */

namespace Player
{
	class PlayerCustomizationExtensions :
		public Patches::Network::PlayerPropertiesExtension<s_player_appearance>
	{
	protected:
		virtual void BuildData(__int32 playerIndex, s_player_appearance *out);
		virtual void ApplyData(__int32 playerIndex, s_player_configuration *properties, s_player_appearance const &data);
		virtual void Serialize(Blam::BitStream *stream, s_player_appearance const &data);
		virtual void Deserialize(Blam::BitStream *stream, s_player_appearance *out);
	public:
		PlayerCustomizationExtensions(Player::PlayerCustomizationExtensions &); /* compiler_generated() */
		PlayerCustomizationExtensions(Player::PlayerCustomizationExtensions const &); /* compiler_generated() */
		_inline PlayerCustomizationExtensions(); /* compiler_generated() */
		virtual _inline ~PlayerCustomizationExtensions(); /* compiler_generated() */
		Player::PlayerCustomizationExtensions &operator=(Player::PlayerCustomizationExtensions &); /* compiler_generated() */
		Player::PlayerCustomizationExtensions &operator=(Player::PlayerCustomizationExtensions const &); /* compiler_generated() */
	};
	static_assert(sizeof(Player::PlayerCustomizationExtensions) == 4, "Invalid Player::PlayerCustomizationExtensions size");
}

/* ---------- prototypes */

namespace Player
{
	extern bool ValidServiceTag(wchar_t (&tag)[5]);
	extern unsigned __int32 ParseColor(std::string const &value);
	extern void SanitizeModelCustomization(s_player_model_customization *customization);
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __PLAYER_PLAYERCUSTOMIZATIONEXTENSION_HPP__
