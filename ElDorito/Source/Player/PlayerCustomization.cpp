/* ---------- headers */

#include "Player/PlayerCustomization.hpp"
#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Player/PlayerCharacterSystem.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

class c_network_session;
struct s_game_globals;
struct s_network_session_player;
struct s_player_appearance;
struct s_player_datum;
struct s_player_identifier;
struct s_player_model_customization;
struct s_scenario;
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}
namespace Player
{
	struct CPlayerCustomization;
}

namespace Utils {}
using namespace ::Utils;
namespace Player {}
using namespace ::Player;
namespace Mods {}
using namespace ::Mods;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Player
{
	extern __int32 FindPlayerInGameWithIdentifier(s_player_identifier const &identifier);
	extern s_player_model_customization const *GetDefaultCharacterCustomization(__int32 playerIndex, __int32 characterIndex);
}

/* ---------- globals */

namespace Player
{
	extern s_player_model_customization nullCustomization; // 0x1240923C
}

static_warning("TODO: fix Player::inGamePlayerCustomizationDefaultsCache declaration");

/* ---------- private variables */

/* ---------- public code */

namespace Player
{
	_extern __int32 _sub_10904010(s_player_identifier const &);
	__int32 FindPlayerInGameWithIdentifier(s_player_identifier const &identifier) // 0x10904010
	{
		mangled_x86(MANGLED_TODO, "?FindPlayerInGameWithIdentifier@Player@@YAHABUs_player_identifier@@@Z");
		// static ...; // 0x109040CC
		// static ...; // 0x109040C0
		// static ...; // 0x109040B8
		// s_player_identifier const &identifier;
		// c_data_array<s_player_datum> *players;
		{
			// c_data_iterator<s_player_datum> it;
		}
		todo("implement");
		__int32 __result = _sub_10904010(identifier);
		return __result;
	}
}

extern s_player_model_customization const *_sub_10904100(__int32, __int32);
namespace Player
{
	s_player_model_customization const *GetDefaultCharacterCustomization(__int32 playerIndex, __int32 characterIndex) // 0x10904100
	{
		mangled_x86(MANGLED_TODO, "?GetDefaultCharacterCustomization@Player@@YAPBUs_player_model_customization@@HH@Z");
		// __int32 characterIndex;
		// __int32 absoluteIndex;
		todo("implement");
		s_player_model_customization const * __result = _sub_10904100(playerIndex, characterIndex);
		return __result;
	}
}

extern s_player_model_customization const *_sub_10904250(__int32);
namespace Player
{
	s_player_model_customization const *CPlayerCustomization::GetInGamePlayerCustomization(__int32 playerIndex) // 0x10904250
	{
		mangled_x86(MANGLED_TODO, "?GetInGamePlayerCustomization@CPlayerCustomization@Player@@SAPBUs_player_model_customization@@H@Z");
		// __int32 playerIndex;
		// s_player_datum *player;
		// s_game_globals *matg;
		// short characterTypeIndex;
		{
			// s_scenario *scnr;
			// Blam::Network::Session *session;
			{
				// __int32 player_session_index;
				{
					// unsigned long name;
					{
						// __int32 i;
					}
				}
			}
		}
		{
			// unsigned long character_name;
			// s_player_model_customization const *defaultCharacterCustomizaation;
			// s_player_appearance &appearance;
			{
				// __int32 i;
			}
		}
		// function call : bool (*)()
		todo("implement");
		s_player_model_customization const * __result = _sub_10904250(playerIndex);
		return __result;
	}

	_extern unsigned __int32 _sub_109044E0(char);
	unsigned __int32 CPlayerCustomization::GetPlayerPrimaryColor(signed char networkPlayerIndex) // 0x109044E0
	{
		mangled_x86(MANGLED_TODO, "?GetPlayerPrimaryColor@CPlayerCustomization@Player@@SAIC@Z");
		// static ...; // 0x109045EC
		// static ...; // 0x109045E0
		// static ...; // 0x109045D8
		// char networkPlayerIndex;
		// s_network_session_player *networkPlayer;
		// c_network_session *session;
		{
			// __int32 playerIndex;
		}
		// function call : bool (*const)(c_network_session **)
		// function call : bool (*const)()
		// function call : bool (*const)()
		todo("implement");
		unsigned __int32 __result = _sub_109044E0(networkPlayerIndex);
		return __result;
	}
}

/* ---------- private code */
