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
		unsigned __int32 PlayerPropertiesExtender::GetTotalSize() // 0x10AAD630
		{
			unsigned __int32 result = 0;
			for (auto it = extensions.begin(); it != extensions.end(); ++it)
				result += (*it)->GetDataSize();
			return result;
		}

		void PlayerPropertiesExtender::BuildData(__int32 playerIndex, void *out) // 0x10AAD1D0
		{
			unsigned char *ptr = static_cast<unsigned char *>(out);
			for (auto it = extensions.begin(); it != extensions.end(); ++it)
			{
				(*it)->BuildData(playerIndex, ptr);
				ptr += (*it)->GetDataSize();
			}
		}

		void PlayerPropertiesExtender::ApplyData(__int32 playerIndex, s_player_configuration *properties, void const *data) // 0x10AACFA0
		{
			unsigned char const *ptr = static_cast<unsigned char const *>(data);
			for (auto it = extensions.begin(); it != extensions.end(); ++it)
			{
				(*it)->ApplyData(playerIndex, properties, ptr);
				ptr += (*it)->GetDataSize();
			}
		}

		void PlayerPropertiesExtender::SerializeData(Blam::BitStream *stream, void const *data) // 0x10AAD800
		{
			unsigned char const *ptr = static_cast<unsigned char const *>(data);
			for (auto it = extensions.begin(); it != extensions.end(); ++it)
			{
				(*it)->Serialize(stream, ptr);
				ptr += (*it)->GetDataSize();
			}
		}

		void PlayerPropertiesExtender::DeserializeData(Blam::BitStream *stream, void *out) // 0x10AAD400
		{
			unsigned char *ptr = static_cast<unsigned char *>(out);
			for (auto it = extensions.begin(); it != extensions.end(); ++it)
			{
				(*it)->Deserialize(stream, ptr);
				ptr += (*it)->GetDataSize();
			}
		}
	}
}

/* ---------- private code */
