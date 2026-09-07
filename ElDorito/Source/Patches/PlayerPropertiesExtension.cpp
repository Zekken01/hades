/* ---------- headers */

#include "Patches/PlayerPropertiesExtension.hpp"
#include "hades/hades.h"

#include "Blam/BitStream.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patches/CustomPackets.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <memory>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
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
		class PlayerPropertiesExtensionBase;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Network {}
	using namespace Patches::Network;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Network
	{
		_extern unsigned __int32 _sub_10AAD630(Patches::Network::PlayerPropertiesExtender *const);
		unsigned __int32 PlayerPropertiesExtender::GetTotalSize() // 0x10AAD630
		{
			mangled_x86(MANGLED_TODO, "?GetTotalSize@PlayerPropertiesExtender@Network@Patches@@QAEIXZ");
			// static ...; // 0x10AAD7A0
			// static ...; // 0x10AAD794
			// static ...; // 0x10AAD78C
			// Patches::Network::PlayerPropertiesExtender *const this;
			// unsigned __int32 result;
			{
				// std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<Patches::Network::PlayerPropertiesExtensionBase> > > > it;
			}
			// function call : unsigned __int32 () const
			todo("implement");
			unsigned __int32 __result = _sub_10AAD630(this);
			return __result;
		}

		_extern void _sub_10AAD1D0(Patches::Network::PlayerPropertiesExtender *const, __int32, void *);
		void PlayerPropertiesExtender::BuildData(__int32 playerIndex, void *out) // 0x10AAD1D0
		{
			mangled_x86(MANGLED_TODO, "?BuildData@PlayerPropertiesExtender@Network@Patches@@QAEXHPAX@Z");
			// static ...; // 0x10AAD370
			// Patches::Network::PlayerPropertiesExtender *const this;
			// __int32 playerIndex;
			// void *out;
			// unsigned char *ptr;
			{
				// std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<Patches::Network::PlayerPropertiesExtensionBase> > > > it;
			}
			// function call : void (__int32, void *)
			// function call : unsigned __int32 () const
			todo("implement");
			_sub_10AAD1D0(this, playerIndex, out);
		}

		_extern void _sub_10AACFA0(Patches::Network::PlayerPropertiesExtender *const, __int32, s_player_configuration *, void const *);
		void PlayerPropertiesExtender::ApplyData(__int32 playerIndex, s_player_configuration *properties, void const *data) // 0x10AACFA0
		{
			mangled_x86(MANGLED_TODO, "?ApplyData@PlayerPropertiesExtender@Network@Patches@@QAEXHPAUs_player_configuration@@PBX@Z");
			// Patches::Network::PlayerPropertiesExtender *const this;
			// __int32 playerIndex;
			// s_player_configuration *properties;
			// void const *data;
			// unsigned char const *ptr;
			{
				// std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<Patches::Network::PlayerPropertiesExtensionBase> > > > it;
			}
			// function call : void (__int32, s_player_configuration *, void const *)
			// function call : unsigned __int32 () const
			todo("implement");
			_sub_10AACFA0(this, playerIndex, properties, data);
		}

		_extern void _sub_10AAD800(Patches::Network::PlayerPropertiesExtender *const, Blam::BitStream *, void const *);
		void PlayerPropertiesExtender::SerializeData(Blam::BitStream *stream, void const *data) // 0x10AAD800
		{
			mangled_x86(MANGLED_TODO, "?SerializeData@PlayerPropertiesExtender@Network@Patches@@QAEXPAVBitStream@Blam@@PBX@Z");
			// static ...; // 0x10AAD9A0
			// Patches::Network::PlayerPropertiesExtender *const this;
			// Blam::BitStream *stream;
			// void const *data;
			// unsigned char const *ptr;
			{
				// std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<Patches::Network::PlayerPropertiesExtensionBase> > > > it;
			}
			// function call : void (Blam::BitStream *, void const *)
			// function call : unsigned __int32 () const
			todo("implement");
			_sub_10AAD800(this, stream, data);
		}

		_extern void _sub_10AAD400(Patches::Network::PlayerPropertiesExtender *const, Blam::BitStream *, void *);
		void PlayerPropertiesExtender::DeserializeData(Blam::BitStream *stream, void *out) // 0x10AAD400
		{
			mangled_x86(MANGLED_TODO, "?DeserializeData@PlayerPropertiesExtender@Network@Patches@@QAEXPAVBitStream@Blam@@PAX@Z");
			// static ...; // 0x10AAD5A0
			// Patches::Network::PlayerPropertiesExtender *const this;
			// Blam::BitStream *stream;
			// void *out;
			// unsigned char *ptr;
			{
				// std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<Patches::Network::PlayerPropertiesExtensionBase> > > > it;
			}
			// function call : void (Blam::BitStream *, void *)
			// function call : unsigned __int32 () const
			todo("implement");
			_sub_10AAD400(this, stream, out);
		}
	}
}

/* ---------- private code */
