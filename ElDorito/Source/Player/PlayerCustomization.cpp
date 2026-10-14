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
#include "mods/ModGlobals.hpp"  // hades: added for 0x10904100
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

extern bool (*game_is_campaign)();  // hades: added for 0x10904250

extern bool (*const network_session_interface_get_squad_session)(c_network_session **);  // hades: added for 0x109044E0
extern bool (*const game_is_multiplayer)();  // hades: added for 0x109044E0

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
	__int32 FindPlayerInGameWithIdentifier(s_player_identifier const &identifier) // 0x10904010
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?FindPlayerInGameWithIdentifier@Player@@YAHABUs_player_identifier@@@Z");
		// static ...; // 0x109040CC
		// static ...; // 0x109040C0
		// static ...; // 0x109040B8
		// s_player_identifier const &identifier;
		// c_data_array<s_player_datum> *players;
			// c_data_iterator<s_player_datum> it;

		c_data_array<s_player_datum> *players = players_get();
		for (c_data_iterator<s_player_datum> it = players->begin(); it != players->end(); ++it)
		{
			if (!memcmp(&it->player_identifier, &identifier, sizeof(s_player_identifier)))
				return it.current_datum_index;
		}
		return -1;
	}
}


namespace Player
{
	s_player_model_customization const *GetDefaultCharacterCustomization(__int32 playerIndex, __int32 characterIndex) // 0x10904100
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetDefaultCharacterCustomization@Player@@YAPBUs_player_model_customization@@HH@Z");
		// __int32 characterIndex;
		// __int32 absoluteIndex;

		if (playerIndex == -1)
			return &nullCustomization;
		__int32 absoluteIndex = playerIndex & 0xF;
		thread_local s_player_model_customization customizations[16];
		customizations[absoluteIndex] = s_player_model_customization{};
		if (!Mods::CModGlobals::GetCharacterDefaultColors(characterIndex, customizations[absoluteIndex].colors))
			return nullptr;
		return &customizations[absoluteIndex];
	}
}


namespace Player
{
	s_player_model_customization const *CPlayerCustomization::GetInGamePlayerCustomization(__int32 playerIndex) // 0x10904250
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetInGamePlayerCustomization@CPlayerCustomization@Player@@SAPBUs_player_model_customization@@H@Z");
		// __int32 playerIndex;
		// s_player_datum *player;
		// s_game_globals *matg;
		// short characterTypeIndex;
			// s_scenario *scnr;
			// Blam::Network::Session *session;
				// __int32 player_session_index;
					// unsigned long name;
						// __int32 i;
			// unsigned long character_name;
			// s_player_model_customization const *defaultCharacterCustomizaation;
			// s_player_appearance &appearance;
				// __int32 i;
		// function call : bool (*)()

		s_player_datum *player = player_get(playerIndex);
		if (!player)
			return &nullCustomization;
		s_game_globals *matg = game_globals_get();
		short characterTypeIndex = player->character_type_index;
		if (game_is_campaign())
		{
			s_scenario *scnr = global_scenario_get();
			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (session && scnr)
			{
				__int32 player_session_index = session->MembershipInfo.GetPeerPlayer(player->machine_index);
				if (scnr->campaign_players.count > 0 && player_session_index < scnr->campaign_players.count)
				{
					unsigned long name = scnr->campaign_players[player_session_index].player_representation;
					for (__int32 i = 0; i < matg->player_character_types.count; i++)
					{
						if (matg->player_character_types[i].name == name)
						{
							characterTypeIndex = i;
							break;
						}
					}
				}
			}
		}
		if (characterTypeIndex >= 0 && characterTypeIndex < matg->player_character_types.count)
		{
			unsigned long character_name = matg->player_character_types[characterTypeIndex].name;
			s_player_appearance &appearance = player->configuration.host.appearance;
			for (__int32 i = 0; i < appearance.characters_count; i++)
			{
				if (appearance.characters[i].character_name == character_name)
					return (s_player_model_customization const *)appearance.characters[i].customization;
			}
			s_player_model_customization const *defaultCharacterCustomizaation = GetDefaultCharacterCustomization(playerIndex, characterTypeIndex);
			if (defaultCharacterCustomizaation)
				return defaultCharacterCustomizaation;
		}
		return &player->configuration.host.appearance.model_customization;
	}

	unsigned __int32 CPlayerCustomization::GetPlayerPrimaryColor(signed char networkPlayerIndex) // 0x109044E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetPlayerPrimaryColor@CPlayerCustomization@Player@@SAIC@Z");
		// static ...; // 0x109045EC
		// static ...; // 0x109045E0
		// static ...; // 0x109045D8
		// char networkPlayerIndex;
		// s_network_session_player *networkPlayer;
		// c_network_session *session;
			// __int32 playerIndex;
		// function call : bool (*const)(c_network_session **)
		// function call : bool (*const)()
		// function call : bool (*const)()

		c_network_session *session;
		if (!network_session_interface_get_squad_session(&session) || !session->established())
			return 0;
		s_network_session_player *networkPlayer = session->get_player(networkPlayerIndex);
		if (!networkPlayer)
			return 0;
		if (((bool(*)())0x5314B0)() && game_is_multiplayer())
		{
			__int32 playerIndex = FindPlayerInGameWithIdentifier(networkPlayer->player_identifier);
			return GetInGamePlayerCustomization(playerIndex)->colors[0];
		}
		return networkPlayer->configuration.host.appearance.nameplate_color;
	}
}

/* ---------- private code */
