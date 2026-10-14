/* ---------- headers */

#include "Discord/DiscordRPC.h"
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
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "Forge/Magnets.hpp"
#include "mods/map_variant_loader.hpp"
#include "Patches/Core.hpp"
#include "Pointer.hpp"
#include "ThirdParty/HttpRequest.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

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
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
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
#include <utility>
#include <vector>

/* ---------- forward declarations */

class HttpRequest;
struct c_game_variant;
struct s_map_variant;
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}
namespace Discord
{
	class DiscordRPC;
}

namespace Utils {}
using namespace ::Utils; namespace Utils { namespace Version { std::string GetVersionString(); } }
namespace Modules {}
using namespace ::Modules;
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

/* ---------- prototypes */

#include <discord_register.h>  // hades: added for 0x109520A0
#include "Modules/ModuleServer.hpp"  // hades: added for 0x10952610
namespace Utils { namespace Cryptography { extern bool RandomPassword(__int32 length, std::string &out); } }  // hades: added for 0x109520A0

#include "Modules/ModuleGame.hpp"  // hades: added for 0x10954380

void handleDiscordDisconnected(__int32 errorCode, char const *message);
void handleDiscordError(__int32 errorCode, char const *message);
void handleDiscordJoin(char const *joinSecret);
void handleDiscordSpectate(char const *spectateSecret);
void handleDiscordJoinRequest(DiscordJoinRequest const *joinRequest);
void UpdateRichPresence();
void handleDiscordReady();
unsigned long __stdcall DiscordRetrieveExternalIP_Thread(void *lpParam);
static void OnShutdown();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern char const *APPLICATION_ID; // 0x11353AE0
	std::pair<std::wstring,bool> const ipGetter[3] = { std::make_pair(L"http://checkip.amazonaws.com/", true), std::make_pair(L"http://ipecho.net/plain", false), std::make_pair(L"http://myexternalip.com/raw", true) }; // 0x1240DA40
}
using namespace hades_file_local;
/* ---------- public code */

namespace Discord
{
	void DiscordRPC::SetJoinString(std::string join) // 0x10953000
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetJoinString@DiscordRPC@Discord@@QAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string join;

		joinMtx.lock();
		joinString.assign(join);
		joinMtx.unlock();
	}

	void DiscordRPC::UpdatePresence() // 0x10953270
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?UpdatePresence@DiscordRPC@Discord@@QAEXXZ");
		// static ...; // 0x10953370
		// static ...; // 0x10953364
		// static ...; // 0x1095335C
		// Discord::DiscordRPC *const this;
		// long long curTime;

		long long curTime;
		time(&curTime);
		if (curTime - lastUpdate > discordUpdateTime)
		{
			if (!Modules::ModuleGame::Instance().VarDiscordEnable->ValueInt)
			{
				Discord_ClearPresence();
				lastUpdate = curTime;
				return;
			}

			lastUpdate = curTime;
			UpdateRichPresence();
		}
	}

	void DiscordRPC::UpdatePresence(__int32 networkMode) // 0x10953190
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?UpdatePresence@DiscordRPC@Discord@@QAEXH@Z");
		// __int32 networkMode;
		// Blam::Network::Session *session;
			// void *thread;
		// function call : void *(_SECURITY_ATTRIBUTES *, unsigned long, unsigned long (*)(void *), void *, unsigned long, unsigned long *)

		if (!Modules::ModuleGame::Instance().VarDiscordEnable->ValueInt)
		{
			Discord_ClearPresence();
			return;
		}

		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (networkMode == 3 && session->IsHost())
		{
			HANDLE thread = CreateThread(0, 0, DiscordRetrieveExternalIP_Thread, 0, 0, 0);
		}
		else
		{
			joinString = "";
		}

		UpdatePresence();
	}

	DiscordRPC::DiscordRPC() : lastUpdate(0), discordUpdateTime(20) /* hades-mem-init: : discordUpdateTime(todo_result<long long>()) */ // 0x109520A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0DiscordRPC@Discord@@QAE@XZ");
		// static ...; // 0x10952325
		// static ...; // 0x1095231C
		// static ...; // 0x10952304
		// static ...; // 0x109522FC
		// Discord::DiscordRPC *const this;
		// DiscordEventHandlers handlers;
		// HINSTANCE__ *hModule;
		// wchar_t appPath[260];
		// function call : HINSTANCE__ *(wchar_t const *)
		// function call : unsigned long (HINSTANCE__ *, wchar_t *, unsigned long)

		joinString = "";
		detailString = "";
		Utils::Cryptography::RandomPassword(32, matchSecret);
		HINSTANCE__ *hModule = GetModuleHandleW(NULL);
		wchar_t appPath[260];
		GetModuleFileNameW(hModule, appPath, MAX_PATH);
		Discord_Register("ElDewrito", Utils::String::ThinString(appPath).c_str());
		DiscordEventHandlers handlers;
		memset(&handlers, 0, sizeof(handlers));
		handlers.ready = handleDiscordReady;
		handlers.disconnected = handleDiscordDisconnected;
		handlers.errored = handleDiscordError;
		handlers.joinGame = handleDiscordJoin;
		handlers.spectateGame = handleDiscordSpectate;
		handlers.joinRequest = handleDiscordJoinRequest;
		Discord_Initialize(APPLICATION_ID, &handlers, 1, nullptr);
		Patches::Core::OnShutdown(static_cast<void (*)()>(OnShutdown));
	}

	void DiscordRPC::ReplyToJoinRequest(char const *userId, __int32 reply) // 0x10952FA0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ReplyToJoinRequest@DiscordRPC@Discord@@QAEXPBDH@Z");
		// __int32 reply;

		Discord_Respond(userId, reply);
	}

	void DiscordRPC::Shutdown() // 0x109530E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Shutdown@DiscordRPC@Discord@@QAEXXZ");
		// Discord::DiscordRPC *const this;

		Discord_Shutdown();
	}

	void DiscordRPC::Update() // 0x10953130
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Update@DiscordRPC@Discord@@QAEXXZ");
		// Discord::DiscordRPC *const this;

		UpdatePresence();
		Discord_RunCallbacks();
	}
}

/* ---------- private code */

void handleDiscordDisconnected(__int32 errorCode, char const *message) // 0x10954210
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?handleDiscordDisconnected@@YAXHPBD@Z");
	// the original is empty
	// `anonymous-namespace'::handleDiscordDisconnected
	// char const *message;
}

void handleDiscordError(__int32 errorCode, char const *message) // 0x10954230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?handleDiscordError@@YAXHPBD@Z");
	// the original is empty
	// `anonymous-namespace'::handleDiscordError
	// char const *message;
}

void handleDiscordJoin(char const *joinSecret) // 0x10954250
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?handleDiscordJoin@@YAXPBD@Z");
	// `anonymous-namespace'::handleDiscordJoin
	// char const *joinSecret;

	Modules::CommandMap::Instance().ExecuteCommand("connect " + std::string(joinSecret));
}

void handleDiscordSpectate(char const *spectateSecret) // 0x10954430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?handleDiscordSpectate@@YAXPBD@Z");
	// the original is empty
	// `anonymous-namespace'::handleDiscordSpectate
	// char const *spectateSecret;
}

void handleDiscordJoinRequest(DiscordJoinRequest const *joinRequest) // 0x10954380
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?handleDiscordJoinRequest@@YAXPBUDiscordJoinRequest@@@Z");
	// `anonymous-namespace'::handleDiscordJoinRequest
	// DiscordJoinRequest const *joinRequest;

	if (Utils::Singleton<Modules::ModuleGame>::Instance().VarDiscordAutoAccept->ValueInt == 1)
	{
		Discord_Respond(joinRequest->userId, 1);
	}
}

void UpdateRichPresence() // 0x109533C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateRichPresence@@YAXXZ");
	// `anonymous-namespace'::UpdateRichPresence
	// procedure flags: nofpo
	// static ...; // 0x10953C14
	// static ...; // 0x10953C08
	// static ...; // 0x10953C00
	// Blam::Network::Session *session;
		// c_game_variant *game;
		// __int32 plyIndex;
		// __int32 players;
		// s_map_variant *map;
			// std::stringstream ss;

	Discord::DiscordRPC::Instance().detailString.clear();
	memset(&Discord::DiscordRPC::Instance().discordPresence, 0, sizeof(Discord::DiscordRPC::discordPresence));
	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (session && session->IsEstablished())
	{
		c_game_variant *game = session->Parameters.GameVariant.Get();
		s_map_variant *map = session->Parameters.MapVariant.Get();
		if (strcmp((char *)Pointer(0x22AB018)(0x1A4, 1), "mainmenu") == 0)
		{
			Discord::DiscordRPC::Instance().discordPresence.largeImageKey = "default";
			Discord::DiscordRPC::Instance().discordPresence.largeImageText = "Mainmenu";
			if (Blam::Network::GetNetworkMode() == 3)
				Discord::DiscordRPC::Instance().discordPresence.details = "In an Online Lobby";
			else
				Discord::DiscordRPC::Instance().discordPresence.details = "In an Offline Lobby";
		}
		else
		{
			Discord::DiscordRPC::Instance().mapString = std::string((char *)Pointer(0x22AB018)(0x1A4, 1));
			Discord::DiscordRPC::Instance().mapString[0] = toupper(Discord::DiscordRPC::Instance().mapString[0]);
			Discord::DiscordRPC::Instance().discordPresence.largeImageText = Discord::DiscordRPC::Instance().mapString.c_str();
			Discord::DiscordRPC::Instance().discordPresence.largeImageKey = (char *)Pointer(0x22AB018)(0x1A4, 1);
			if (game && map)
			{
				std::stringstream ss;
				ss << "On " << Utils::String::ThinString(map->metadata.name);
				Discord::DiscordRPC::Instance().detailString = ss.str();
				Discord::DiscordRPC::Instance().discordPresence.details = Discord::DiscordRPC::Instance().detailString.c_str();
				Discord::DiscordRPC::Instance().gameTypeString = game_engine_type_get_string(game->game_engine_type);
				Discord::DiscordRPC::Instance().gameTypeString[0] = toupper(Discord::DiscordRPC::Instance().gameTypeString[0]);
				Discord::DiscordRPC::Instance().discordPresence.smallImageText = Discord::DiscordRPC::Instance().gameTypeString.c_str();
				Discord::DiscordRPC::Instance().discordPresence.smallImageKey = game_engine_type_get_string(game->game_engine_type);
			}
		}
		__int32 players = 0;
		__int32 plyIndex = session->MembershipInfo.FindFirstPlayer();
		while (plyIndex != -1)
		{
			players++;
			plyIndex = session->MembershipInfo.FindNextPlayer(plyIndex);
		}
		Discord::DiscordRPC::Instance().discordPresence.partyId = Modules::ModuleServer::Instance().VarServerNameClient->ValueString.c_str();
		Discord::DiscordRPC::Instance().discordPresence.matchSecret = Discord::DiscordRPC::Instance().matchSecret.c_str();
		Discord::DiscordRPC::Instance().discordPresence.partySize = players;
		Discord::DiscordRPC::Instance().discordPresence.partyMax = session->MembershipInfo.SessionMaxPlayers;
		if (game)
		{
			Discord::DiscordRPC::Instance().gameTypeString = game_engine_type_get_string(game->game_engine_type);
			Discord::DiscordRPC::Instance().gameTypeString[0] = toupper(Discord::DiscordRPC::Instance().gameTypeString[0]);
			Discord::DiscordRPC::Instance().discordPresence.state = Discord::DiscordRPC::Instance().gameTypeString.c_str();
		}
	}
	else
	{
		Discord::DiscordRPC::Instance().discordPresence.state = "At the Mainmenu";
		Discord::DiscordRPC::Instance().discordPresence.largeImageKey = "default";
		Discord::DiscordRPC::Instance().discordPresence.largeImageText = "Mainmenu";
		Discord::DiscordRPC::Instance().discordPresence.details = "Alone";
		Discord::DiscordRPC::Instance().discordPresence.partySize = 1;
		Discord::DiscordRPC::Instance().discordPresence.partyMax = 1;
		Discord::DiscordRPC::Instance().SetJoinString("");
	}
	Discord::DiscordRPC::Instance().joinMtx.lock();
	Discord::DiscordRPC::Instance().discordPresence.joinSecret = Discord::DiscordRPC::Instance().joinString.c_str();
	Discord::DiscordRPC::Instance().joinMtx.unlock();
	Discord_UpdatePresence(&Discord::DiscordRPC::Instance().discordPresence);
}

void handleDiscordReady() // 0x109543E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?handleDiscordReady@@YAXXZ");
	// `anonymous-namespace'::handleDiscordReady
	// procedure flags: nofpo

	Discord::DiscordRPC::Instance().Update();
}

unsigned long __stdcall DiscordRetrieveExternalIP_Thread(void *lpParam) // 0x10952610
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DiscordRetrieveExternalIP_Thread@@YGKPAX@Z");
	// `anonymous-namespace'::DiscordRetrieveExternalIP_Thread
	// static ...; // 0x10952D73
	// static ...; // 0x10952D6A
	// static ...; // 0x10952D62
	// static ...; // 0x10952D5C
	// static ...; // 0x10952D2C
	// static ...; // 0x10952D24
	// void *lpParam;
	// HttpRequest req;
		// __int32 i;
			// std::wstring respHdr;
			// std::string extIp;
			// std::wstring expected;

	HttpRequest req(L"ElDewrito/" + Utils::String::WidenString(Utils::Version::GetVersionString()), L"", L"");
	for (__int32 i = 0; i < 3; i++)
	{
		if (!req.SendRequest(ipGetter[i].first, L"GET", L"", L"", L"", nullptr, 0))
		{
			Discord::DiscordRPC::Instance().SetJoinString("");
			continue;
		}
		std::wstring expected = L"HTTP/1.1 200 OK";
		if (req.responseHeader.length() < expected.length())
		{
			Discord::DiscordRPC::Instance().SetJoinString("");
			continue;
		}
		std::wstring respHdr = req.responseHeader.substr(0, expected.length());
		if (respHdr.compare(expected))
		{
			Discord::DiscordRPC::Instance().SetJoinString("");
			continue;
		}
		std::string extIp;
		if (ipGetter[i].second)
			extIp = std::string(req.responseBody.begin(), req.responseBody.end() - 1);
		else
			extIp = std::string(req.responseBody.begin(), req.responseBody.end());
		Discord::DiscordRPC::Instance().SetJoinString(extIp + ":" + Modules::ModuleServer::Instance().VarServerPort->ValueString + " " + Modules::ModuleServer::Instance().VarServerPassword->ValueString);
		return true;
	}
	Discord::DiscordRPC::Instance().SetJoinString("");
	return true;
}

static void OnShutdown() // 0x10952F50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnShutdown@@YAXXZ");
	// `anonymous-namespace'::OnShutdown
	// procedure flags: nofpo

	Discord::DiscordRPC::Instance().Shutdown();
}

/* ---------- explicit instantiations */
template Pointer::operator char *() const;
