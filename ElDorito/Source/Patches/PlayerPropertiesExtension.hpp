#ifndef __PATCHES_PLAYERPROPERTIESEXTENSION_HPP__
#define __PATCHES_PLAYERPROPERTIESEXTENSION_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BitStream.hpp"
#include "Blam/game/player_configuration.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Patches/CustomPackets.hpp"

#include <memory>
#include <vector>

/* ---------- forward declarations */

struct s_player_configuration;
namespace Blam
{
	class BitStream;
}
namespace Patches
{
	namespace Network
	{
		class PlayerPropertiesExtender;
	}
}

/* ---------- constants */

/* ---------- definitions */

// Patches::Network::PlayerPropertiesExtensionBase is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

namespace Patches
{
	namespace Network
	{
		class PlayerPropertiesExtender :
			public Utils::Singleton<Patches::Network::PlayerPropertiesExtender>
		{
		public:
			_inline void Add(std::shared_ptr<Patches::Network::PlayerPropertiesExtensionBase> extension);
			unsigned __int32 GetTotalSize();
			void BuildData(__int32 playerIndex, void *out);
			void ApplyData(__int32 playerIndex, s_player_configuration *properties, void const *data);
			void SerializeData(Blam::BitStream *stream, void const *data);
			void DeserializeData(Blam::BitStream *stream, void *out);
		private:
			std::vector<std::shared_ptr<Patches::Network::PlayerPropertiesExtensionBase> > extensions; // 0x0
		public:
			_inline PlayerPropertiesExtender(); /* compiler_generated() */
			~PlayerPropertiesExtender(); /* compiler_generated() */
		};
		static_assert(sizeof(Patches::Network::PlayerPropertiesExtender) == 16, "Invalid Patches::Network::PlayerPropertiesExtender size");
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Patches
{
	namespace Network
	{
		_extern void _sub_108D8F20(Patches::Network::PlayerPropertiesExtensionBase *const);
		_inline PlayerPropertiesExtensionBase::~PlayerPropertiesExtensionBase() // 0x108D8F20
		{
			mangled_x86(MANGLED_TODO, "??1PlayerPropertiesExtensionBase@Network@Patches@@UAE@XZ");
			// Patches::Network::PlayerPropertiesExtensionBase *const this;
			todo("implement");
			_sub_108D8F20(this);
		}

		_extern void _sub_108D9320(Patches::Network::PlayerPropertiesExtender *const, std::shared_ptr<Patches::Network::PlayerPropertiesExtensionBase>);
		_inline void PlayerPropertiesExtender::Add(std::shared_ptr<Patches::Network::PlayerPropertiesExtensionBase> extension) // 0x108D9320
		{
			mangled_x86(MANGLED_TODO, "?Add@PlayerPropertiesExtender@Network@Patches@@QAEXV?$shared_ptr@VPlayerPropertiesExtensionBase@Network@Patches@@@std@@@Z");
			// std::shared_ptr<Patches::Network::PlayerPropertiesExtensionBase> extension;
			todo("implement");
			_sub_108D9320(this, extension);
		}
	}
}

/* ---------- private code */

#endif // __PATCHES_PLAYERPROPERTIESEXTENSION_HPP__
