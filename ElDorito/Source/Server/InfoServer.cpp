/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_results.hpp"
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
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "ElDorito.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/font_package.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/mod_system.hpp"
#include "mods/new/IModManager.hpp"
#include "Pointer.hpp"
#include "Server/Voting/VotingPackets.hpp"
#include "Server/Voting/VotingTypes.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Utils/UPnP.hpp"
#include "Modules/ModuleVoting.hpp"  // hades: added for 0x10B1B3F0
#include "Player/PlayerCustomization.hpp"  // hades: added for 0x10B1B3F0
#include "Blam/game/engine/game_engine.hpp"  // hades: added for 0x10B1B3F0
#include "Blam/game/game_state.hpp"  // hades: added for 0x10B1B3F0

#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
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

class c_mod_package_manager;
struct s_game_options;
struct s_game_results_player_statistics;
struct s_mod_server_package_entry;
struct s_player_emblem_configuration;
namespace Blam
{
	namespace Network
	{
		struct PlayerSession;
		struct Session;
	}
}
namespace hades_file_local
{
	struct HttpRequestLine;
}
using namespace hades_file_local;

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
	namespace InfoServer {}
	using namespace Server::InfoServer;
	namespace Voting {}
	using namespace Server::Voting;
}

namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace Emblems {}
	using namespace Player::Emblems;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

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

//enum ParseHttpRequestLine::__l2::s_state
//{
//	STATE_METHOD_TOKEN = 0,
//	STATE_REQUEST_URI,
//	STATE_PROTOCOL_VERSION,
//	STATE_END,
//};

/* ---------- definitions */

namespace hades_file_local
{
	#pragma pack(push, 4)
	struct HttpRequestLine
	{
		std::string method; // 0x0
		std::string requestUri; // 0x1C
		std::string protocolVersion; // 0x38
		HttpRequestLine(HttpRequestLine &); /* compiler_generated() */
		HttpRequestLine(HttpRequestLine const &); /* compiler_generated() */
		HttpRequestLine(); /* compiler_generated() */
		~HttpRequestLine(); /* compiler_generated() */
		HttpRequestLine &operator=(HttpRequestLine &); /* compiler_generated() */
		HttpRequestLine &operator=(HttpRequestLine const &); /* compiler_generated() */
	};
	#pragma pack(pop)
	static_assert(sizeof(HttpRequestLine) == 84, "Invalid HttpRequestLine size");
}
using namespace hades_file_local;
/* ---------- prototypes */

#include "Modules/ModuleUPnP.hpp"  // hades: added for 0x10B1E850
#include "Modules/ModulePlayer.hpp"  // hades: added for 0x10B1E850
#include "Modules/ModuleServer.hpp"  // hades: added for 0x10B1E850
namespace Server { namespace Voting { extern void StartNewVote(); } }  // hades: added for 0x10B1E850

namespace Utils::Version { std::string GetVersionString(); }  // hades: added for 0x10B1AF30

namespace Server
{
	namespace InfoServer
	{
		extern bool IsInfoSocketOpen();
		extern bool StartInfoServer();
		extern bool StopInfoServer();
		extern __int32 __stdcall networkWndProc(HWND__ *hWnd, unsigned __int32 msg, unsigned __int32 wParam, long lParam, bool *outHandled);
		extern void Tick();
	}
}

std::string BuildInfoServerPayload(std::string const &inDataBuffer);
extern s_game_options *(*game_options_get)();  // hades: added for 0x10B1B3F0
namespace Player::Emblems { std::string BuildUrl(s_player_emblem_configuration config); }  // hades: added for 0x10B1B3F0
std::string GenerateModList();
bool ParseHttpRequestLine(std::string const &rawline, HttpRequestLine *outRequestLine);
std::string BuildHttpResponse(std::string const &status, std::string const &contentType, std::string const &content, std::string const &additionalHeaders);
std::string BuildInfoServerResponse(std::string const &rawRequest);
std::string BuildModsServerResponse(std::string const &rawRequest);
std::string BuildNotFoundResponse(std::string const &rawRequest);
std::string BuildBadRequestResponse(std::string const &rawRequest);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern unsigned __int32 infoSocket; // 0x124678D8
	extern bool infoSocketOpen; // 0x124678DC
	extern long long lastAnnounce; // 0x124678E0
	std::string httpServerCache; // 0x124678A0
	std::string modListJson; // 0x124678BC
	extern long long timeSinceLastPoll; // 0x124678E8
	extern __int32 modCount; // 0x124678F0
}
using namespace hades_file_local;
namespace Server
{
	namespace Voting
	{
		namespace hades_file_local_Server_Voting
		{
			// extern std::string const DefaultTypes[8]; // 0x124676E0  // hades: defined in VotingTypes.hpp, one copy per file
			// extern std::string const DefaultTypeNames[8]; // 0x124677C0  // hades: defined in VotingTypes.hpp, one copy per file
		}
		using namespace hades_file_local_Server_Voting;
	}
}
/* ---------- public code */

namespace Server
{
	namespace InfoServer
	{
		bool IsInfoSocketOpen() // 0x10B1E450
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?IsInfoSocketOpen@InfoServer@Server@@YA_NXZ");

			return infoSocketOpen;
		}

		bool StartInfoServer() // 0x10B1E850
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?StartInfoServer@InfoServer@Server@@YA_NXZ");

			if (infoSocketOpen)
				return true;
			modListJson = GenerateModList();
			Server::Voting::StartNewVote();
			HWND__ *hwnd = Pointer::Base(0x159C014).Read<HWND__ *>();
			if (hwnd == 0)
				return false;
			infoSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			sockaddr_in bindAddr;
			bindAddr.sin_family = AF_INET;
			bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);
			unsigned long port = Modules::ModuleServer::Instance().VarServerPort->ValueInt;
			if (port == Pointer(0x1860454).Read<unsigned int>())
				port++;
			bindAddr.sin_port = htons((unsigned short)port);
			while (bind(infoSocket, (sockaddr *)&bindAddr, sizeof(bindAddr)) != 0)
			{
				port++;
				if (port == Pointer(0x1860454).Read<unsigned int>())
					port++;
				bindAddr.sin_port = htons((unsigned short)port);
				if (port > Modules::ModuleServer::Instance().VarServerPort->ValueInt + 10)
					return false;
			}
			Modules::CommandMap::Instance().SetVariable(Modules::ModuleServer::Instance().VarServerPort, std::to_string(port), false);
			Modules::ModuleServer::Instance().VarServerHost->ValueString = Modules::ModulePlayer::Instance().VarPlayerName->ValueString;
			if (Modules::ModuleUPnP::Instance().VarUPnPEnabled->ValueInt)
			{
				Modules::ModuleUPnP::Instance().UPnPForwardPort(true, port, port, "ElDewrito InfoServer");
				Modules::ModuleUPnP::Instance().UPnPForwardPort(false, Pointer(0x1860454).Read<unsigned int>(), Pointer(0x1860454).Read<unsigned int>(), "ElDewrito Game");
			}
			WSAAsyncSelect(infoSocket, hwnd, 0x939, FD_ACCEPT | FD_CLOSE);
			listen(infoSocket, 5);
			infoSocketOpen = true;
			return true;
		}

		bool StopInfoServer() // 0x10B1EEE0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?StopInfoServer@InfoServer@Server@@YA_NXZ");

			if (!infoSocketOpen)
				return true;
			closesocket(infoSocket);
			int istrue = 1;
			setsockopt(infoSocket, SOL_SOCKET, SO_REUSEADDR, (char const *)&istrue, sizeof(istrue));
			Modules::CommandMap::Instance().ExecuteCommand("Server.Unannounce");
			infoSocketOpen = false;
			lastAnnounce = 0;
			return true;
		}

		__int32 __stdcall networkWndProc(HWND__ *hWnd, unsigned __int32 msg, unsigned __int32 wParam, long lParam, bool *outHandled) // 0x10B1F560
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?networkWndProc@InfoServer@Server@@YGHPAUHWND__@@IIJPA_N@Z");

			if (msg != 0x939)
				return 0;
			*outHandled = true;
			if (WSAGETSELECTERROR(lParam))
			{
				closesocket(wParam);
				return 0;
			}
			unsigned __int32 clientSocket;
			__int32 inDataLength;
			char inDataBuffer[4096];
			switch (WSAGETSELECTEVENT(lParam))
			{
			case FD_ACCEPT:
				clientSocket = accept(wParam, nullptr, nullptr);
				WSAAsyncSelect(clientSocket, hWnd, msg, FD_READ | FD_WRITE | FD_CLOSE);
				break;
			case FD_READ:
				if (msg == 0x939)
				{
					memset(inDataBuffer, 0, sizeof(inDataBuffer));
					inDataLength = recv(wParam, inDataBuffer, sizeof(inDataBuffer), 0);
					std::string rawRequest(inDataBuffer, sizeof(inDataBuffer) - 1);
					HttpRequestLine requestLine;
					ParseHttpRequestLine(rawRequest, &requestLine);
					std::string reply = "";
					if (requestLine.method == "GET")
					{
						if (requestLine.requestUri == "/")
							reply = BuildInfoServerResponse(rawRequest);
						else if (requestLine.requestUri == "/mods")
							reply = BuildModsServerResponse(rawRequest);
						else
							reply = BuildNotFoundResponse(rawRequest);
					}
					else
						reply = BuildBadRequestResponse(rawRequest);
					send(wParam, reply.c_str(), reply.length(), 0);
				}
				break;
			case FD_CLOSE:
				closesocket(wParam);
				break;
			}
			return 0;
		}

		void Tick() // 0x10B1F050
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@InfoServer@Server@@YAXXZ");

			time_t curTime;
			time(&curTime);
			if (infoSocketOpen && Utils::Singleton<Modules::ModuleServer>::Instance().VarServerShouldAnnounce->ValueInt)
			{
				if (curTime - lastAnnounce > 150)
				{
					lastAnnounce = curTime;
					Modules::CommandMap::Instance().ExecuteCommand("Server.Announce");
				}
			}
		}
	}
}

/* ---------- private code */

std::string BuildInfoServerPayload(std::string const &inDataBuffer) // 0x10B1B3F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BuildInfoServerPayload@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV12@@Z");

	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session)
		return "{}";
	std::string mapName((char *)Pointer(0x22AB018)(0x1A4, 1));
	std::wstring mapVariantName((wchar_t *)Pointer(0x1863ACA));
	std::wstring variantName((wchar_t *)Pointer(0x23DAF4C));
	std::string xnkid;
	std::string xnaddr;
	std::string gameVersion((char *)Pointer(0x199C0F0));
	std::string status = "InGame";
	Utils::String::BytesToHexString((char *)Pointer(0x2247B80), 0x10, xnkid);
	Utils::String::BytesToHexString((char *)Pointer(0x2247B90), 0x10, xnaddr);
	e_game_mode gameMode = game_options_get()->game_mode;
	e_game_engine_type variantType = Pointer(0x23DAF18).Read<e_game_engine_type>();
	if (gameMode == _game_mode_mainmenu)
	{
		if (mapName == "mainmenu")
		{
			status = "InLobby";
			mapName = std::string((char *)Pointer(0x19A5E49));
			variantName = L"none";
			variantType = _game_engine_type_none;
		}
		else
			status = "Loading";
	}
	rapidjson::StringBuffer s;
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	writer.StartObject();
	writer.Key("name");
	writer.String(Modules::ModuleServer::Instance().VarServerName->ValueString.c_str());
	writer.Key("port");
	writer.Int(Pointer(0x1860454).Read<unsigned int>());
	writer.Key("fileServerPort");
	writer.Int(Modules::ModuleServer::Instance().VarFileServerPort->ValueInt);
	writer.Key("hostPlayer");
	writer.String(Modules::ModulePlayer::Instance().VarPlayerName->ValueString.c_str());
	writer.Key("sprintState");
	writer.String(Modules::ModuleServer::Instance().VarServerSprintState->ValueString.c_str());
	writer.Key("sprintUnlimitedEnabled");
	writer.String(Modules::ModuleServer::Instance().VarServerSprintUnlimited->ValueString.c_str());
	writer.Key("dualWielding");
	writer.String(Modules::ModuleServer::Instance().VarServerDualWieldEnabled->ValueString.c_str());
	writer.Key("assassinationEnabled");
	writer.String(Modules::ModuleServer::Instance().VarServerAssassinationEnabled->ValueString.c_str());
	writer.Key("voteSystemType");
	writer.Int(Modules::ModuleVoting::Instance().VarServerVotingType->ValueInt);
	if (session && session->IsEstablished())
	{
		writer.Key("teams");
		writer.Bool(session->HasTeams());
	}
	writer.Key("map");
	writer.String(Utils::String::ThinString(mapVariantName).c_str());
	writer.Key("mapFile");
	writer.String(mapName.c_str());
	writer.Key("variant");
	writer.String(Utils::String::ThinString(variantName).c_str());
	if (variantType >= 0 && variantType < 11)
	{
		writer.Key("variantType");
		writer.String(game_engine_type_get_string(variantType));
	}
	writer.Key("status");
	writer.String(status.c_str());
	writer.Key("numPlayers");
	writer.Int(Blam::Network::GetNumPlayers());
	writer.Key("maxPlayers");
	writer.Int(Modules::ModuleServer::Instance().VarServerMaxPlayers->ValueInt);
	bool authenticated = true;
	if (!Modules::ModuleServer::Instance().VarServerPassword->ValueString.empty())
	{
		std::string authString = "dorito:" + Modules::ModuleServer::Instance().VarServerPassword->ValueString;
		authString = "Authorization: Basic " + Utils::String::Base64Encode((unsigned char const *)authString.c_str(), authString.length()) + "\r\n";
		authenticated = inDataBuffer.find(authString) != std::string::npos;
	}
	if (authenticated)
	{
		writer.Key("modCount");
		writer.Int(modCount);
		c_mod_package_manager::s_entry packageEntry;
		std::string modHash = c_mod_system::get_current_package_hash();
		c_mod_system::get_mod_info_by_identifier(modHash.c_str(), &packageEntry);
		writer.Key("modPackageName");
		writer.String(!modHash.empty() ? Utils::String::ThinString(packageEntry.name).c_str() : "");
		writer.Key("modPackageAuthor");
		writer.String(!modHash.empty() ? packageEntry.author : "");
		writer.Key("modPackageHash");
		writer.String(modHash.c_str());
		writer.Key("modPackageVersion");
		writer.String(!modHash.empty() ? (std::to_string(packageEntry.version_major) + "." + std::to_string(packageEntry.version_minor)).c_str() : "");
		writer.Key("xnkid");
		writer.String(xnkid.c_str());
		writer.Key("xnaddr");
		writer.String(xnaddr.c_str());
		if (session->HasTeams())
		{
			writer.Key("teamScores");
			writer.StartArray();
			unsigned __int32 *scores = &Pointer(0x1879DA8).Read<unsigned __int32>();
			for (__int32 t = 0; t < 8; t++)
				writer.Int(scores[t]);
			writer.EndArray();
		}
		writer.Key("players");
		writer.StartArray();
		unsigned __int32 playerInfoBase = 0x2162E08;
		unsigned __int32 playerStatusBase = 0x2161808;
		__int32 peerIdx = session->MembershipInfo.FindFirstPeer();
		while (peerIdx != -1)
		{
			__int32 playerIdx = session->MembershipInfo.GetPeerPlayer(peerIdx);
			if (playerIdx != -1)
			{
				s_game_results_player_statistics *player_stats = game_results_get_player_stats(playerIdx);
				Blam::Network::PlayerSession *player = &session->MembershipInfo.PlayerSessions[playerIdx];
				std::string name = Utils::String::ThinString(player->Properties.host.player_name);
				unsigned short team = Pointer(playerInfoBase + 5696 * playerIdx + 0x20).Read<unsigned short>();
				unsigned char alive = Pointer(playerStatusBase + 176 * playerIdx).Read<unsigned char>();
				writer.StartObject();
				writer.Key("name");
				writer.String(name.c_str());
				writer.Key("serviceTag");
				writer.String(Utils::String::ThinString(player->Properties.host.appearance.service_tag).c_str());
				writer.Key("emblem");
				s_player_emblem_configuration config = player->Properties.host.appearance.emblem_config;
				std::string emblem = Player::Emblems::BuildUrl(config);
				writer.String(emblem.substr(16, emblem.size() - 1).c_str());
				writer.Key("team");
				writer.Int(team);
				char uid[17];
				player_format_uid(uid, player->Properties.host.player_uid);
				writer.Key("uid");
				writer.String(uid);
				std::stringstream color;
				color << "#" << std::setw(6) << std::setfill('0') << std::hex << Player::CPlayerCustomization::GetPlayerPrimaryColor(playerIdx);
				writer.Key("primaryColor");
				writer.String(color.str().c_str());
				writer.Key("isAlive");
				writer.Bool(alive == 1);
				writer.Key("roundScore");
				writer.Int(player_stats->in_round_score);
				writer.Key("score");
				writer.Int(player_stats->in_game_total_score);
				writer.Key("kills");
				writer.Int(player_stats->kills);
				writer.Key("assists");
				writer.Int(player_stats->assists);
				writer.Key("deaths");
				writer.Int(player_stats->deaths);
				writer.Key("betrayals");
				writer.Int(player_stats->betrayals);
				writer.Key("timeSpentAlive");
				writer.Int(player_stats->seconds_alive);
				writer.Key("suicides");
				writer.Int(player_stats->suicides);
				writer.Key("bestStreak");
				writer.Int(player_stats->best_streak);
				writer.EndObject();
			}
			peerIdx = session->MembershipInfo.FindNextPeer(peerIdx);
		}
		writer.EndArray();
	}
	else
	{
		writer.Key("passworded");
		writer.Bool(true);
	}
	writer.Key("isDedicated");
	writer.Bool(ElDorito::Instance().IsDedicated());
	writer.Key("gameVersion");
	writer.String(gameVersion.c_str());
	writer.Key("eldewritoVersion");
	std::string eldewritoVersion = Utils::Version::GetVersionString();
	writer.String(eldewritoVersion.c_str());
	writer.EndObject();
	std::string response = s.GetString();
	return response;
}

std::string GenerateModList() // 0x10B1DAF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GenerateModList@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");

	c_mod_package_manager &package_manager = c_mod_system::get_package_manager();
	c_mod_package_manager::c_threadsafe_iterator it = package_manager.lock_for_iteration();
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	modCount = 0;
	bool has_server_package_list = c_mod_system::has_server_package_list();
	bool file_server_enabled = Utils::Singleton<Modules::ModuleServer>::Instance().VarFileServerEnabled->ValueInt != 0;
	writer.StartObject();
	while (it.next())
	{
		std::string hash_encoded;
		Utils::String::BytesToHexString(it->hash, sizeof(it->hash), hash_encoded);
		std::string key;
		std::string package_url;
		s_mod_server_package_entry server_package;
		if (c_mod_system::find_server_package_by_hash(hash_encoded, &server_package))
		{
			package_url = server_package.package_url;
			key = server_package.local_name;
		}
		else
		{
			if (!file_server_enabled || has_server_package_list)
				continue;
			std::filesystem::path path(it->file.filename);
			std::string filename = key = path.filename().string();
			package_url = std::string("./") + filename;
		}
		writer.Key(key.c_str());
		writer.StartObject();
		writer.Key("hash");
		writer.String(hash_encoded.c_str());
		writer.Key("package_url");
		writer.String(package_url.c_str());
		writer.Key("package_size");
		writer.Uint64(it->file_size);
		writer.Key("mod_name");
		writer.String(Utils::String::ThinString(it->name).c_str());
		writer.Key("mod_author");
		writer.String(it->author);
		writer.Key("mod_description");
		writer.String(it->description);
		writer.Key("mod_version");
		writer.String((std::to_string(it->version_major) + "." + std::to_string(it->version_minor)).c_str());
		writer.Key("mod_website");
		writer.String(it->website);
		writer.EndObject();
		modCount++;
	}
	writer.EndObject();
	return buffer.GetString();
}

bool ParseHttpRequestLine(std::string const &rawline, HttpRequestLine *outRequestLine) // 0x10B1E470
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ParseHttpRequestLine@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAUHttpRequestLine@hades_file_local@@@Z");

	enum s_state
	{
		STATE_METHOD_TOKEN,
		STATE_REQUEST_URI,
		STATE_PROTOCOL_VERSION,
		STATE_END,
	};
	s_state state = STATE_METHOD_TOKEN;
	std::stringstream buff;
	for (__int32 i = 0; i <= rawline.size(); i++)
	{
		char c = rawline[i];
		switch (state)
		{
		case STATE_METHOD_TOKEN:
			if (c == ' ')
			{
				outRequestLine->method = buff.str();
				buff.str("");
				state = STATE_REQUEST_URI;
				continue;
			}
			break;
		case STATE_REQUEST_URI:
			if (c == ' ')
			{
				outRequestLine->requestUri = buff.str();
				buff.str("");
				state = STATE_PROTOCOL_VERSION;
				continue;
			}
			break;
		case STATE_PROTOCOL_VERSION:
			if (c == '\r' || c == '\0')
			{
				outRequestLine->protocolVersion = buff.str();
				buff.str("");
				state = STATE_END;
				continue;
			}
			break;
		}
		buff << c;
	}
	return state == STATE_END;
}

std::string BuildHttpResponse(std::string const &status, std::string const &contentType, std::string const &content, std::string const &additionalHeaders) // 0x10B1AF30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BuildHttpResponse@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV12@000@Z");

	return "HTTP/1.1 " + status + "\r\nContent-Type: " + contentType + "\r\nAccess-Control-Allow-Origin: *\r\nServer: ElDewrito/" + Utils::Version::GetVersionString() + "\r\nContent-Length: " + std::to_string(content.length()) + "\r\nConnection: close\r\n" + additionalHeaders + "\r\n" + content;
}

std::string BuildInfoServerResponse(std::string const &rawRequest) // 0x10B1D250
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BuildInfoServerResponse@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV12@@Z");

	long long curTime;
	time(&curTime);
	if (!Modules::ModuleServer::Instance().VarServerPassword->ValueString.empty() || curTime - timeSinceLastPoll > Modules::ModuleServer::Instance().VarHttpServerCacheTime->ValueInt)
	{
		timeSinceLastPoll = curTime;
		httpServerCache = BuildInfoServerPayload(rawRequest);
	}
	std::string const &replyData = httpServerCache;
	return BuildHttpResponse("200 OK", "application/json", replyData, "");
}

// mangled_x86(MANGLED_DEFAULT, "??0HttpRequestLine@hades_file_local@@QAE@XZ"); no body to assert in
_inline HttpRequestLine::HttpRequestLine() = default; // 0x10B1ACC0

// mangled_x86(MANGLED_DEFAULT, "??1HttpRequestLine@hades_file_local@@QAE@XZ"); no body to assert in
_inline HttpRequestLine::~HttpRequestLine() = default; // 0x10B1AD30

std::string BuildModsServerResponse(std::string const &rawRequest) // 0x10B1D4F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BuildModsServerResponse@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV12@@Z");

	bool authenticated = true;
	if (!Modules::ModuleServer::Instance().VarServerPassword->ValueString.empty())
	{
		std::string authString = "dorito:" + Modules::ModuleServer::Instance().VarServerPassword->ValueString;
		authString = "Authorization: Basic " + Utils::String::Base64Encode((unsigned char const *)authString.c_str(), authString.length()) + "\r\n";
		authenticated = rawRequest.find(authString) != std::string::npos;
	}
	if (authenticated)
		return BuildHttpResponse("200 OK", "application/json", modListJson, "");
	return BuildHttpResponse("200 OK", "application/json", "{}", "");
}

std::string BuildNotFoundResponse(std::string const &rawRequest) // 0x10B1D960
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BuildNotFoundResponse@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV12@@Z");

	return BuildHttpResponse("404 Not Found", "text/html", "", "");
}

std::string BuildBadRequestResponse(std::string const &rawRequest) // 0x10B1ADA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BuildBadRequestResponse@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV12@@Z");

	return BuildHttpResponse("400 Bad Request", "text/html", "", "");
}

/* ---------- explicit instantiations */
template HWND__ * & Pointer::Read<HWND__ *>() const;
template e_game_engine_type & Pointer::Read<enum e_game_engine_type>() const;

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { unsigned __int32 infoSocket; }
namespace hades_file_local { bool infoSocketOpen; }
namespace hades_file_local { long long lastAnnounce; }
namespace hades_file_local { long long timeSinceLastPoll; }
namespace hades_file_local { __int32 modCount; }
