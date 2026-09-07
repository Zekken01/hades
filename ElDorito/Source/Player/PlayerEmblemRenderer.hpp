#ifndef __PLAYER_PLAYEREMBLEMRENDERER_HPP__
#define __PLAYER_PLAYEREMBLEMRENDERER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/game/player_appearance.hpp"
#include "Patches/CustomPackets.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

struct s_player_emblem_configuration;
namespace Player
{
	namespace Emblems
	{
		class IPlayerEmblemRenderCallbacks;
		class IPlayerEmblemStream;
		class PlayerEmblemRenderer;
		struct PlayerEmblemRenderMetadata;
		struct PlayerEmblemRenderTask;
	}
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Player
{
	namespace Emblems
	{
		struct PlayerEmblemRenderMetadata
		{
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > mimeType; // 0x0
			PlayerEmblemRenderMetadata(Player::Emblems::PlayerEmblemRenderMetadata &); /* compiler_generated() */
			PlayerEmblemRenderMetadata(Player::Emblems::PlayerEmblemRenderMetadata const &); /* compiler_generated() */
			_inline PlayerEmblemRenderMetadata(); /* compiler_generated() */
			_inline ~PlayerEmblemRenderMetadata(); /* compiler_generated() */
			Player::Emblems::PlayerEmblemRenderMetadata &operator=(Player::Emblems::PlayerEmblemRenderMetadata &); /* compiler_generated() */
			_inline Player::Emblems::PlayerEmblemRenderMetadata &operator=(Player::Emblems::PlayerEmblemRenderMetadata const &__that); /* compiler_generated() */
		};
	}
}

#pragma pack(pop)
static_assert(sizeof(Player::Emblems::PlayerEmblemRenderMetadata) == 28, "Invalid Player::Emblems::PlayerEmblemRenderMetadata size");

namespace Player
{
	namespace Emblems
	{
		class IPlayerEmblemStream
		{
		public:
			virtual _inline ~IPlayerEmblemStream();
			virtual bool Read(void *, __int32, __int32 *) = 0;
			IPlayerEmblemStream(Player::Emblems::IPlayerEmblemStream const &); /* compiler_generated() */
			_inline IPlayerEmblemStream(); /* compiler_generated() */
			Player::Emblems::IPlayerEmblemStream &operator=(Player::Emblems::IPlayerEmblemStream const &); /* compiler_generated() */
		};
		static_assert(sizeof(Player::Emblems::IPlayerEmblemStream) == 4, "Invalid Player::Emblems::IPlayerEmblemStream size");

		class IPlayerEmblemRenderCallbacks
		{
		public:
			virtual _inline ~IPlayerEmblemRenderCallbacks();
			virtual void OnRenderStart(Player::Emblems::PlayerEmblemRenderMetadata const &, std::shared_ptr<Player::Emblems::IPlayerEmblemStream>) = 0;
			virtual void OnRenderComplete() = 0;
			virtual void OnRenderDataAvailable() = 0;
			IPlayerEmblemRenderCallbacks(Player::Emblems::IPlayerEmblemRenderCallbacks const &); /* compiler_generated() */
			_inline IPlayerEmblemRenderCallbacks(); /* compiler_generated() */
			Player::Emblems::IPlayerEmblemRenderCallbacks &operator=(Player::Emblems::IPlayerEmblemRenderCallbacks const &); /* compiler_generated() */
		};
		static_assert(sizeof(Player::Emblems::IPlayerEmblemRenderCallbacks) == 4, "Invalid Player::Emblems::IPlayerEmblemRenderCallbacks size");

		class PlayerEmblemRenderer
		{
		public:
			static bool StartRender(s_player_emblem_configuration const &config, std::shared_ptr<Player::Emblems::IPlayerEmblemRenderCallbacks> handler);
			static void DoRender();
		};
		static_assert(sizeof(Player::Emblems::PlayerEmblemRenderer) == 1, "Invalid Player::Emblems::PlayerEmblemRenderer size");
	}
}

/* ---------- prototypes */

namespace Player
{
	namespace Emblems
	{
		extern void ProcessRenderTask(Player::Emblems::PlayerEmblemRenderTask const &task);
	}
}

/* ---------- globals */

/* ---------- public code */

namespace Player
{
	namespace Emblems
	{
		_extern void _sub_107E7530(Player::Emblems::IPlayerEmblemStream *const);
		_inline IPlayerEmblemStream::~IPlayerEmblemStream() // 0x107E7530
		{
			mangled_x86(MANGLED_TODO, "??1IPlayerEmblemStream@Emblems@Player@@UAE@XZ");
			// Player::Emblems::IPlayerEmblemStream *const this;
			todo("implement");
			_sub_107E7530(this);
		}

		_extern void _sub_10C83000(Player::Emblems::IPlayerEmblemRenderCallbacks *const);
		_inline IPlayerEmblemRenderCallbacks::~IPlayerEmblemRenderCallbacks() // 0x10C83000
		{
			mangled_x86(MANGLED_TODO, "??1IPlayerEmblemRenderCallbacks@Emblems@Player@@UAE@XZ");
			// Player::Emblems::IPlayerEmblemRenderCallbacks *const this;
			todo("implement");
			_sub_10C83000(this);
		}
	}
}

/* ---------- private code */

#endif // __PLAYER_PLAYEREMBLEMRENDERER_HPP__
