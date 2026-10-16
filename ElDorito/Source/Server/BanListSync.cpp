/* ---------- headers */

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
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "Patches/Core.hpp"
#include "Server/BanList.hpp"
#include "Server/StatsServerBanList.hpp"
#include "ThirdParty/HttpRequest.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "Utils/DewritoReader.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Utils/WebSocket.hpp"

#include "Utils/Logger.hpp"  // hades: added for 0x10B18BA0
namespace Utils::Version { std::string GetVersionString(); }  // hades: added for 0x10B18F00

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <condition_variable>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_set>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class HttpRequest;
struct begin;
struct end;
struct s_sharedState;
namespace Blam
{
	namespace Network
	{
		struct PlayerSession;
		struct Session;
	}
}
namespace Server
{
	class StatsServersBanList;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace BanListSync {}
	using namespace Server::BanListSync;
}

namespace Modules {}
using namespace ::Modules;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Core {}
	using namespace Patches::Core;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

struct s_sharedState
{
	std::vector<std::string> Subnets; // 0x0
	std::vector<std::string> Names; // 0x10
	std::vector<std::string> Uids; // 0x20
	std::vector<std::string> Ips; // 0x30
	s_sharedState(s_sharedState &); /* compiler_generated() */
	s_sharedState(s_sharedState const &); /* compiler_generated() */
	s_sharedState(); /* compiler_generated() */
	~s_sharedState(); /* compiler_generated() */
	s_sharedState &operator=(s_sharedState &); /* compiler_generated() */
	s_sharedState &operator=(s_sharedState const &); /* compiler_generated() */
};
// static_assert(sizeof(s_sharedState) == 64, "Invalid s_sharedState size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

/* ---------- prototypes */

extern "C" unsigned long __stdcall inet_addr(char const *cp);  // hades: added for 0x10B19ED0
extern "C" unsigned long __stdcall htonl(unsigned long hostlong);  // hades: added for 0x10B19ED0

namespace Server
{
	namespace BanListSync
	{
		extern void Init();
		extern void Tick();
	}
}

bool GetEndpoints();
void CheckToBootPlayers();
bool SyncBanList();
unsigned long __stdcall BanListSyncThreadProc(void *lpParam);
static void OnShutdown();
bool TryParseSubnet(std::string const &cidr, unsigned long *outNetwork, unsigned long *outMask);

/* ---------- globals */

/* ---------- private variables */

namespace Server
{
	namespace hades_file_local_Server
	{
		// extern std::string DefaultBanListPath; // 0x12467688  // hades: defined (with its initialiser) elsewhere now
	}
	using namespace hades_file_local_Server;
}
namespace hades_file_local
{
	extern long long lastSyncTime; // 0x124676A8
	namespace hades_file_local_BanListSync { extern std::mutex mutex; } using namespace hades_file_local_BanListSync; // 0x12467620
	extern std::condition_variable syncSignal; // 0x12467660
	namespace hades_file_local_BanListSync { extern bool shouldExit; } using namespace hades_file_local_BanListSync; // 0x124676A4
	extern bool banlistDirty; // 0x124676A5
	extern std::vector<std::string> banlistUrls; // 0x12467650
	extern s_sharedState sharedState; // 0x124675E0
}
using namespace hades_file_local;
/* ---------- public code */

namespace Server
{
	namespace BanListSync
	{
		void Init() // 0x10B18E20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Init@BanListSync@Server@@YAXXZ");

			CreateThread(nullptr, 0, BanListSyncThreadProc, nullptr, 0, nullptr);
			Patches::Core::OnShutdown(::OnShutdown);
		}

		void Tick() // 0x10B199C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@BanListSync@Server@@YAXXZ");

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (!session || !session->IsEstablished() || !session->IsHost())
				return;
			if (banlistDirty)
			{
				std::unique_lock<std::mutex> lock(mutex, std::try_to_lock);
				if (lock.owns_lock())
				{
					banlistDirty = false;
					Server::StatsServersBanList &statsserverBanList = Utils::Singleton<Server::StatsServersBanList>::Instance();
					statsserverBanList.ClearList();
					for (std::string const &ip : sharedState.Ips)
						Utils::Singleton<Server::StatsServersBanList>::Instance().AddIp(ip);
					for (std::string const &uid : sharedState.Uids)
						Utils::Singleton<Server::StatsServersBanList>::Instance().AddUID(uid);
					for (std::string const &name : sharedState.Names)
						Utils::Singleton<Server::StatsServersBanList>::Instance().AddName(name);
					for (std::string const &subnet : sharedState.Subnets)
					{
						unsigned long network;
						unsigned long mask;
						if (TryParseSubnet(subnet, &network, &mask))
							Utils::Singleton<Server::StatsServersBanList>::Instance().AddSubnet(network, mask);
					}
					CheckToBootPlayers();
				}
			}
			unsigned long syncInternval = Modules::ModuleServer::Instance().VarBanListSyncIntervalSeconds->ValueInt;
			time_t now;
			time(&now);
			if (now - lastSyncTime > syncInternval)
			{
				lastSyncTime = now;
				syncSignal.notify_one();
			}
		}
	}
}

/* ---------- private code */

bool GetEndpoints() // 0x10B18BA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetEndpoints@@YA_NXZ");

	if (!Utils::Singleton<Utils::DewritoReader>::Instance().IsValid())
		return false;
	auto json = Utils::Singleton<Utils::DewritoReader>::Instance().GetDewritoJson();
	if (json.IsObject() && json.HasMember("banlistUrls"))
	{
		banlistUrls.clear();
		auto &urls = json["banlistUrls"];
		if (!urls.IsArray())
		{
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "Server::BanListSync::GetEndpoints(): \"banlistUrls\" must be an array");
			return false;
		}
		for (unsigned __int32 i = 0; i < urls.Size(); i++)
			banlistUrls.push_back(urls[i].GetString());
	}
	return true;
}

_inline s_sharedState::s_sharedState() = default; // 0x10B17D40

_inline s_sharedState::~s_sharedState() = default; // 0x10B17E80

void CheckToBootPlayers() // 0x10B183A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CheckToBootPlayers@@YAXXZ");

	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session || !session->IsEstablished() || !session->IsHost())
		return;
	__int32 peerIdx = session->MembershipInfo.FindFirstPeer();
	while (peerIdx != -1)
	{
		__int32 playerIdx = session->MembershipInfo.GetPeerPlayer(peerIdx);
		if (playerIdx != -1)
		{
			Blam::Network::PlayerSession *player = &session->MembershipInfo.PlayerSessions[playerIdx];
			std::string name = Utils::String::ThinString(player->Properties.host.player_name);
			unsigned long long uid = player->Properties.host.player_uid;
			std::stringstream stream;
			stream << std::hex << uid;
			std::string hexUID = stream.str();
			std::string const &ipString = session->GetPeerAddress(peerIdx).ToString();
			if (Utils::Singleton<Server::StatsServersBanList>::Instance().ContainsIp(ipString) || Utils::Singleton<Server::StatsServersBanList>::Instance().ContainsSubnet(ipString))
			{
				if (!Blam::Network::BootPlayer(playerIdx, 13))
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Failed to Kick Banned IP: " + ipString);
				else
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Successfully Kicked Banned IP: " + ipString);
			}
			if (Utils::Singleton<Server::StatsServersBanList>::Instance().ContainsUID(hexUID))
			{
				if (!Blam::Network::BootPlayer(playerIdx, 13))
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Failed to Kick Banned UID: " + hexUID);
				else
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Successfully Kicked Banned UID: " + hexUID);
			}
			if (Utils::Singleton<Server::StatsServersBanList>::Instance().ContainsName(name))
			{
				if (!Blam::Network::BootPlayer(playerIdx, 13))
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Failed to Kick Banned Name: " + name);
				else
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Successfully Kicked Banned Name: " + name);
			}
		}
		peerIdx = session->MembershipInfo.FindNextPeer(peerIdx);
	}
}

bool SyncBanList() // 0x10B18F00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SyncBanList@@YA_NXZ");

	if (!GetEndpoints())
		return false;
	sharedState.Ips.clear();
	sharedState.Subnets.clear();
	sharedState.Names.clear();
	sharedState.Uids.clear();
	for (auto &endpoint : banlistUrls)
	{
		HttpRequest req(L"ElDewrito/" + Utils::String::WidenString(Utils::Version::GetVersionString()), L"", L"");
		if (!req.SendRequest(Utils::String::WidenString(endpoint), L"GET", L"", L"", L"", nullptr, 0))
		{
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Unable to connect to banlist endpoint. \"%s\"", endpoint.c_str());
			continue;
		}
		std::wstring expected = L"HTTP/1.1 200 OK";
		if (req.responseHeader.length() < expected.length())
		{
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Invalid server query response. \"%s\"", endpoint.c_str());
			continue;
		}
		std::string resp(req.responseBody.begin(), req.responseBody.end());
		rapidjson::Document json;
		if (json.Parse<0>(resp.c_str()).HasParseError() || !json.IsObject())
		{
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Invalid json returned from banlist endpoint. \"%s\"", endpoint.c_str());
			continue;
		}
		if (json.HasMember("ips"))
		{
			rapidjson::Value const &IPs = json["ips"];
			for (unsigned __int32 i = 0; i < IPs.Size(); i++)
				sharedState.Ips.push_back(IPs[i].GetString());
		}
		if (json.HasMember("uids"))
		{
			rapidjson::Value const &UIDs = json["uids"];
			for (unsigned __int32 i = 0; i < UIDs.Size(); i++)
				sharedState.Uids.push_back(UIDs[i].GetString());
		}
		if (json.HasMember("names"))
		{
			rapidjson::Value const &Names = json["names"];
			for (unsigned __int32 i = 0; i < Names.Size(); i++)
				sharedState.Names.emplace_back(Names[i].GetString());
		}
		if (json.HasMember("subnets"))
		{
			rapidjson::Value const &Subnets = json["subnets"];
			for (unsigned __int32 i = 0; i < Subnets.Size(); i++)
				sharedState.Subnets.emplace_back(Subnets[i].GetString());
		}
	}
	return true;
}

unsigned long __stdcall BanListSyncThreadProc(void *lpParam) // 0x10B18260
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BanListSyncThreadProc@@YGKPAX@Z");

	for (;;)
	{
		std::unique_lock<std::mutex> lk(hades_file_local::mutex);
		syncSignal.wait(lk);
		if (shouldExit)
			return 0;
		if (SyncBanList())
			banlistDirty = true;
	}
}

static void OnShutdown() // 0x10B18EB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnShutdown@@YAXXZ");

	shouldExit = true;
	syncSignal.notify_one();
}

bool TryParseSubnet(std::string const &cidr, unsigned long *outNetwork, unsigned long *outMask) // 0x10B19ED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?TryParseSubnet@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAK1@Z");

	auto pos = cidr.find_first_of('/');
	if (pos == std::string::npos || pos + 1 >= cidr.length())
		return false;
	auto snetwork = cidr.substr(0, pos);
	auto sbits = cidr.substr(pos + 1);
	auto bits = atoi(sbits.c_str());
	if (bits == 0)
		return false;
	*outNetwork = inet_addr(snetwork.c_str());
	*outMask = htonl(0xFFFFFFFF << (32 - bits));
	return true;
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { long long lastSyncTime; }
namespace hades_file_local { std::condition_variable syncSignal; }
namespace hades_file_local { bool banlistDirty; }
namespace hades_file_local { std::vector<std::string> banlistUrls; }
namespace hades_file_local { s_sharedState sharedState; }
namespace hades_file_local { namespace hades_file_local_BanListSync { std::mutex mutex; } }
namespace hades_file_local { namespace hades_file_local_BanListSync { bool shouldExit; } }
