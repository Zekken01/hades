/* ---------- headers */

#include "Player/PlayerInfo.hpp"
#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Forge/Magnets.hpp"
#include "Patches/Network.hpp"
#include "Player/PlayerServiceRecord.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Singleton.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <ios>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_network_session;
struct s_network_session_player;
struct s_player_emblem_configuration;
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}
namespace Player
{
	struct CPlayersInfo;
}
namespace Player
{
	namespace ServiceRecord
	{
		struct ServiceRecord;
	}
}
namespace hades_file_local
{
	struct SPlayerInfo;
	struct SPlayerEmblemInfo;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace ServiceRecord {}
	using namespace Player::ServiceRecord;
	namespace Emblems {}
	using namespace Player::Emblems;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace PlayerUid {}
	using namespace Patches::PlayerUid;
}

namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct SPlayerInfo
	{
		__int32 rank = -1; // 0x0
		__int32 skill = -1; // 0x4
		std::string emblemUrl; // 0x8
		bool rankup = false; // 0x24
		bool set = false; // 0x25
		// hades: special members left implicit; the original move-assigns value-initialized temporaries
	};
	static_assert(sizeof(SPlayerInfo) == 40, "Invalid SPlayerInfo size");

	struct SPlayerEmblemInfo
	{
		std::string emblemUrl; // 0x0
		unsigned long long uid; // 0x20
		// hades: special members left implicit; the original move-assigns value-initialized temporaries
	};
	static_assert(sizeof(SPlayerEmblemInfo) == 40, "Invalid SPlayerEmblemInfo size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const game_is_ui_shell = reinterpret_cast<bool (*)()>(0x531E90);
}

extern bool (*const network_session_interface_get_squad_session)(c_network_session **out_session);  // hades: added for 0x107EF4E0, 0x107EE0C0  // hades: added for 0x107EE0C0
extern void player_format_uid(char *string, unsigned long long id);  // hades: added for 0x107EE0C0  // hades: added for 0x107EE0C0

extern bool (*const network_session_interface_get_squad_session)(c_network_session **out_session);  // hades: added for 0x107EF4E0, 0x107EE0C0  // hades: added for 0x107EF4E0
namespace Player { namespace Emblems { extern std::string BuildUrl(s_player_emblem_configuration config); } }  // hades: added for 0x107EF4E0  // hades: added for 0x107EF4E0

namespace Player
{
	extern bool GetRankedUpRecently();
	extern void ClearRankUp();
	extern std::string getLocalEmblem(__int32 networkPlayerIndex);
	extern void LifeCycleStateChanged(Blam::Network::LifeCycleState newState);
}

bool ValidNetworkPlayerIndex(__int32 networkPlayerIndex);
void ClearCache();
void ClearEmblemCache();

/* ---------- globals */

namespace Player { namespace ServiceRecord { void clearCache(); } }  // hades: added for 0X107EE690

/* ---------- private variables */

namespace hades_file_local
{
	SPlayerInfo infoCache[16]; // 0x1138EDC8
	SPlayerEmblemInfo localEmblemCache[16]; // 0x1138F048
	extern bool isAvailable; // 0x1138F2C8
	extern bool rankCheckGameStarted; // 0x1138F2C9
	extern bool rankCheckGameEnded; // 0x1138F2CA
	extern long long checkRankTime; // 0x1138F2D0
}
using namespace hades_file_local;
/* ---------- public code */

namespace Player
{
	bool CPlayersInfo::IsAvailable() // 0x107EE670
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?IsAvailable@CPlayersInfo@Player@@SA_NXZ");

		return isAvailable;
	}

	bool GetRankedUpRecently() // 0x107EE500
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetRankedUpRecently@Player@@YA_NXZ");

		__int32 localPeer = Blam::Network::GetActiveSession()->MembershipInfo.LocalPeerIndex;
		__int32 localPlayerIdx = Blam::Network::GetActiveSession()->MembershipInfo.GetPeerPlayer(localPeer);

		if (localPlayerIdx != -1)
			return infoCache[localPlayerIdx].rankup;

		return false;
	}
}


namespace Player
{
	std::string CPlayersInfo::GeneratePlayerInfo() // 0x107EE0C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GeneratePlayerInfo@CPlayersInfo@Player@@SA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");

		rapidjson::StringBuffer jsonBuffer;
		rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
		jsonWriter.StartObject();
		for (__int32 i = 0; i < 16; i++)
		{
			c_network_session *session;
			if (!network_session_interface_get_squad_session(&session) || !session->established())
				continue;
			bool validIndex = i >= 0 && i < 16;
			if (!validIndex || i >= session->get_player_count())
				continue;
			if (!session->get_session_membership()->is_player_valid(i))
				continue;
			s_network_session_player *networkPlayer = session->get_player(i);
			if (!networkPlayer)
				continue;
			jsonWriter.Key(std::to_string(i).c_str());
			jsonWriter.StartObject();
			jsonWriter.Key("e");
			jsonWriter.String(localEmblemCache[i].emblemUrl.c_str());
			jsonWriter.Key("u");
			char uid[17];
			player_format_uid(uid, networkPlayer->configuration.host.player_uid);
			jsonWriter.String(uid);
			jsonWriter.EndObject();
		}
		jsonWriter.EndObject();
		return jsonBuffer.GetString();
	}

	void ClearRankUp() // 0x107EDE50
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ClearRankUp@Player@@YAXXZ");

		for (__int32 i = 0; i < 16; i++)
		{
			infoCache[i].rankup = false;
		}
	}

	__int32 CPlayersInfo::GetRank(__int32 networkPlayerIndex) // 0x107EE480
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetRank@CPlayersInfo@Player@@SAHH@Z");

		if (!ValidNetworkPlayerIndex(networkPlayerIndex))
		{
			return 0;
		}

		if (!isAvailable)
		{
			return 0;
		}

		return infoCache[networkPlayerIndex].rank;
	}

	__int32 CPlayersInfo::GetSkill(__int32 networkPlayerIndex) // 0x107EE590
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetSkill@CPlayersInfo@Player@@SAHH@Z");

		if (!ValidNetworkPlayerIndex(networkPlayerIndex))
		{
			return 0;
		}

		if (!isAvailable)
		{
			return 0;
		}

		return infoCache[networkPlayerIndex].skill;
	}
}


namespace Player
{
	std::string getLocalEmblem(__int32 networkPlayerIndex) // 0x107EF4E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?getLocalEmblem@Player@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z");

		c_network_session *session;
		if (!network_session_interface_get_squad_session(&session) || !session->established())
			return "";
		s_network_session_player *networkPlayer = session->get_player(networkPlayerIndex);
		if (!networkPlayer)
			return "";
		if (localEmblemCache[networkPlayerIndex].uid == networkPlayer->configuration.host.player_uid)
			return localEmblemCache[networkPlayerIndex].emblemUrl;
		s_player_emblem_configuration emblem_cfg = networkPlayer->configuration.host.appearance.emblem_config;
		localEmblemCache[networkPlayerIndex].uid = networkPlayer->configuration.host.player_uid;
		localEmblemCache[networkPlayerIndex].emblemUrl = Player::Emblems::BuildUrl(emblem_cfg);
		return localEmblemCache[networkPlayerIndex].emblemUrl;
	}
}


namespace Player
{
	std::string CPlayersInfo::GeEmblemUrl(__int32 networkPlayerIndex) // 0x107EDEA0
	{
		mangled_x86(MANGLED_TODO, "?GeEmblemUrl@CPlayersInfo@Player@@SA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z");
		if (!ValidNetworkPlayerIndex(networkPlayerIndex))
			return "";
		SPlayerInfo cached = infoCache[networkPlayerIndex];
		if (isAvailable && !cached.set)
			return getLocalEmblem(networkPlayerIndex);
		if (!isAvailable || cached.emblemUrl.size() == 0)
			return getLocalEmblem(networkPlayerIndex);
		return cached.emblemUrl; // hades: written in place (no symbol-map entry); keeps SPlayerInfo's copy ctor emitted
	}

	void CPlayersInfo::Update(std::string const &payload) // 0x107EE980
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Update@CPlayersInfo@Player@@SAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

		ClearCache();
		rapidjson::Document json;
		if (json.Parse<0>(payload.c_str()).HasParseError() || !json.IsObject() || payload == "{}")
		{
			isAvailable = false;
			return;
		}
		for (__int32 i = 0; i < 16; i++)
		{
			std::string key = std::to_string(i);
			if (json.HasMember(key.c_str()))
			{
				rapidjson::Value &info = json[key.c_str()];
				if (json[key.c_str()].HasMember("ru") && json[key.c_str()]["ru"].IsBool())
				{
					bool rankUp = info["ru"].GetBool();
					if (rankUp == true)
						infoCache[i].rankup = true;
					else
						infoCache[i].rankup = false;
				}
				else
					infoCache[i].rankup = false;
				if (json[key.c_str()].HasMember("r") && json[key.c_str()]["r"].IsInt())
				{
					__int32 rank = info["r"].GetInt();
					if (rank <= -1)
						rank = -1;
					else if (rank > 42)
						rank = 0;
					infoCache[i].rank = rank;
				}
				else
					infoCache[i].rank = -1;
				if (json[key.c_str()].HasMember("s") && json[key.c_str()]["s"].IsInt())
				{
					__int32 skill = info["s"].GetInt();
					if (skill <= -1)
						skill = -1;
					else if (skill > 50)
						skill = 0;
					infoCache[i].skill = skill;
				}
				else
					infoCache[i].skill = -1;
				if (json[key.c_str()].HasMember("e") && json[key.c_str()]["e"].IsString())
					infoCache[i].emblemUrl = info["e"].GetString();
				infoCache[i].set = true;
			}
			else
				infoCache[i] = SPlayerInfo{};
		}
		isAvailable = true;
	}

	void LifeCycleStateChanged(Blam::Network::LifeCycleState newState) // 0x107EE690
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?LifeCycleStateChanged@Player@@YAXW4LifeCycleState@Network@Blam@@@Z");

		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (!session || !session->IsEstablished())
			return;

		switch (newState)
		{
		case Blam::Network::eLifeCycleStatePreGame:
			if (rankCheckGameStarted)
				rankCheckGameEnded = true;
			Player::ServiceRecord::clearCache();
			ClearEmblemCache();
			break;
		case Blam::Network::eLifeCycleStateStartGame:
			rankCheckGameStarted = true;
			Player::ServiceRecord::clearCache();
			break;
		}
	}

	void CPlayersInfo::Init() // 0x107EE610
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Init@CPlayersInfo@Player@@SAXXZ");

		Patches::Network::OnLifeCycleStateChanged(Player::LifeCycleStateChanged);
	}

	void CPlayersInfo::Tick() // 0x107EE750
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@CPlayersInfo@Player@@SAXXZ");

		static bool (*IsMapLoading)() = (bool (*)())0x5670E0;
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		long long curTime1;
		if (!session || !session->IsEstablished())
			return;
		time(&curTime1);
		if (!checkRankTime && rankCheckGameStarted == true && rankCheckGameEnded == true && !IsMapLoading())
		{
			time(&checkRankTime);
			rankCheckGameStarted = false;
			rankCheckGameEnded = false;
		}
		if (checkRankTime && Blam::Network::GetLobbyType() == 2 && eldorado::game_is_ui_shell())
		{
			long long elapsed = curTime1 - checkRankTime;
			if (elapsed > 5)
			{
				if (GetRankedUpRecently())
				{
					ClearRankUp();
					Modules::CommandMap::Instance().ExecuteCommand("Game.ShowUI spartan_rank_dialog");
				}
				checkRankTime = 0;
			}
		}
	}
}

/* ---------- private code */

bool ValidNetworkPlayerIndex(__int32 networkPlayerIndex) // 0x107EEF90
{

	return networkPlayerIndex >= 0 && networkPlayerIndex < 16;
}

void ClearCache() // 0x107EDCB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ClearCache@@YAXXZ");

	for (__int32 i = 0; i < 16; i++)
		infoCache[i] = {};
}

void ClearEmblemCache() // 0x107EDD90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ClearEmblemCache@@YAXXZ");

	for (__int32 i = 0; i < 16; i++)
		localEmblemCache[i] = {};
}

// SPlayerInfo / SPlayerEmblemInfo special members (0x107ED930..0x107EDC10) are implicit.

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { bool isAvailable; }
namespace hades_file_local { bool rankCheckGameStarted; }
namespace hades_file_local { bool rankCheckGameEnded; }
namespace hades_file_local { long long checkRankTime; }
