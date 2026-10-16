/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/game/engine/game_engine_events.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_results.hpp"
#include "Blam/game/game_statborg.hpp"
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
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "ElDorito.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/font_package.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Patches/Core.hpp"
#include "Patches/Events.hpp"
#include "Patches/Network.hpp"
#include "Pointer.hpp"
#include "ThirdParty/HttpRequest.hpp"
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
#include "Utils/DewritoReader.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <WinSock2.h>
#include <WS2tcpip.h>
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
#include <ws2ipdef.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
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

class HttpRequest;
class c_mod_package_manager;
struct begin;
struct c_game_engine;
struct c_game_results;
struct c_game_statborg;
struct end;
struct s_game_engine_event_data;
struct s_game_options;
struct s_game_results_events;
struct s_game_results_player_statistics;
struct s_multiplayer_event_response_definition;
struct s_player_emblem_configuration;
namespace Blam
{
	namespace Network
	{
		struct PlayerSession;
		struct Session;
		struct SessionMembership;
	}
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
	namespace Stats {}
	using namespace Server::Stats;
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

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace PlayerUid {}
	using namespace Patches::PlayerUid;
	namespace Events {}
	using namespace Patches::Events;
	namespace Core {}
	using namespace Patches::Core;
}

namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

#include "Modules/ModulePlayer.hpp"  // hades: added for 0x10B28970
namespace Utils { namespace Cryptography { extern std::string ReformatKey(bool isPrivateKey, std::string key); extern bool PublicEncrypt(std::string publicKey, void *data, unsigned __int32 dataSize, std::string &encrypted); extern bool CreateRSASignature(std::string privateKey, void *data, unsigned __int32 dataSize, std::string &signature); } } namespace Utils { namespace Version { std::string GetVersionString(); } } namespace Player { namespace Emblems { extern std::string HexToStrHex(int hex); } } extern void player_format_uid(char *string, unsigned long long id); extern char const *g_player_medal_names[58]; extern char const *g_damage_reporting_type_names[64];  // hades: added for 0x10B28970  // hades: added for 0x10B28970
#include "Player/PlayerCustomization.hpp"  // hades: added for 0x10B28970
namespace Patches { namespace PlayerUid { extern unsigned long long Get(); } } extern s_game_options *(*game_options_get)();  // hades: added for 0x10B28970  // hades: added for 0x10B28970
#include "mods/mod_system.hpp"  // hades: added for 0x10B28970

#include "Utils/Logger.hpp"  // hades: added for 0x10B27360
#include "Modules/ModuleServer.hpp"  // hades: added for 0x10B27360
#include "Blam/game/game_state.hpp"  // hades: added for 0x10B27360
#include "Player/PlayerCharacterSystem.hpp"  // hades: added for 0x10B27360
namespace Utils::Version { std::string GetVersionString(); }  // hades: added for 0x10B27360
namespace Player { namespace Emblems { std::string HexToStrHex(int); } }  // hades: added for 0x10B27360
extern "C" char const *__stdcall inet_ntop(int Family, void const *pAddr, char *pStringBuf, size_t StringBufSize);  // hades: added for 0x10B27360

namespace Blam::Network { Session *GetActiveSession(); __int32 GetNumPlayers(); }  // hades: added for 0X10B2C0B0

namespace Blam::Network { Session *GetActiveSession(); }  // hades: added for 0X10B2CBA0

namespace Server
{
	namespace Stats
	{
		extern void GetStatsEndpoints(std::vector<std::string> &destVect);
		extern void GetPlayersInfoEndpoint();
		extern void GetStatsPublicKey(std::string &dest);
		extern unsigned long __stdcall GetPlayersInfo_Thread(void *lpParam);
		extern bool AnnounceStats(std::string payload, std::vector<std::string> endpoints);
		extern std::string GetStatsPayload();
		extern void LifeCycleStateChanged(Blam::Network::LifeCycleState newState);
		extern void OnGameStart();
		extern unsigned __int32 GetPeerIp(Blam::Network::Session *session, __int32 peer);
		extern void LogListPlayers();
		extern void OnEvent(unsigned long player, s_game_engine_event_data const *event, s_multiplayer_event_response_definition const *definition);
		extern void Init();
		extern void UpdatePlayersInfo();
		extern void Tick();
		extern bool localPlayerIsPostMatch();
	}
}

/* ---------- globals */

namespace Server
{
	namespace Stats
	{
		extern long long matchStartTime; // 0x124679F8
		extern long long matchEndTime; // 0x12467A00
		extern long long sendStatsTime; // 0x12467A08
		extern long long listPlayersTime; // 0x12467A10
		extern bool postMatch; // 0x12467A18
		extern std::string playersInfoEndpoint; // 0x12467A1C
		extern __int32 numberOfRounds; // 0x11354E40
	}
}

/* ---------- private variables */

/* ---------- public code */

namespace Server
{
	namespace Stats
	{
		void GetStatsEndpoints(std::vector<std::string> &destVect) // 0x10B28760
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetStatsEndpoints@Stats@Server@@YAXAAV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@@Z");

			if (!Utils::Singleton<Utils::DewritoReader>::Instance().IsValid())
				return;
			rapidjson::Document json = Utils::Singleton<Utils::DewritoReader>::Instance().GetDewritoJson();
			if (json.IsObject() && json.HasMember("stats"))
			{
				rapidjson::Value &statsObject = json["stats"];
				if (statsObject.HasMember("submitUrls"))
				{
					rapidjson::Value &submitUrls = statsObject["submitUrls"];
					for (rapidjson::SizeType i = 0; i < submitUrls.Size(); i++)
						destVect.push_back(submitUrls[i].GetString());
				}
			}
		}

		void GetPlayersInfoEndpoint() // 0x10B271C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPlayersInfoEndpoint@Stats@Server@@YAXXZ");

			if (!Utils::Singleton<Utils::DewritoReader>::Instance().IsValid())
				return;
			rapidjson::Document json = Utils::Singleton<Utils::DewritoReader>::Instance().GetDewritoJson();
			if (json.IsObject() && json.HasMember("stats"))
			{
				auto &statsObject = json["stats"];
				if (statsObject.HasMember("playerInfo"))
					playersInfoEndpoint = statsObject["playerInfo"].GetString();
			}
		}

		void GetStatsPublicKey(std::string &dest) // 0x10B2BE60
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetStatsPublicKey@Stats@Server@@YAXAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

			if (!Utils::Singleton<Utils::DewritoReader>::Instance().IsValid())
				return;
			rapidjson::Document json = Utils::Singleton<Utils::DewritoReader>::Instance().GetDewritoJson();
			if (json.IsObject() && json.HasMember("stats"))
			{
				rapidjson::Value &statsObject = json["stats"];
				if (statsObject.HasMember("publicKey"))
					dest = statsObject["publicKey"].GetString();
			}
		}

		unsigned long __stdcall GetPlayersInfo_Thread(void *lpParam) // 0x10B27360
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPlayersInfo_Thread@Stats@Server@@YGKPAX@Z");

			if (playersInfoEndpoint.empty())
				return false;
			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			rapidjson::StringBuffer s;
			rapidjson::Writer<rapidjson::StringBuffer> writer(s);
			writer.StartObject();
			writer.Key("players");
			writer.StartArray();
			__int32 player_index = session->MembershipInfo.FindFirstPlayer();
			while (player_index != -1)
			{
				Blam::Network::PlayerSession *player = &session->MembershipInfo.PlayerSessions[player_index];
				unsigned short team = Pointer(0x2162E28 + 5696 * player_index).Read<unsigned short>();
				in_addr inAddr;
				inAddr.S_un.S_addr = session->GetPeerAddress(session->MembershipInfo.GetPlayerPeer(player_index)).ToInAddr();
				char ipStr[22];
				inet_ntop(AF_INET, &inAddr, ipStr, sizeof(ipStr));
				char uid[17];
				player_format_uid(uid, player->Properties.host.player_uid);
				writer.StartObject();
				writer.Key("name");
				writer.String(Utils::String::ThinString(player->Properties.client.player_name).c_str());
				writer.Key("filteredName");
				writer.String(Utils::String::ThinString(player->Properties.host.player_name).c_str());
				writer.Key("serviceTag");
				writer.String(Utils::String::ThinString(player->Properties.host.appearance.service_tag).c_str());
				writer.Key("playerIndex");
				writer.Int(player_index);
				writer.Key("uid");
				writer.String(uid);
				writer.Key("ip");
				writer.String(ipStr);
				s_player_emblem_configuration emblemConfig = player->Properties.host.appearance.emblem_config;
				writer.Key("emblem");
				writer.StartObject();
				writer.Key("one");
				writer.String((emblemConfig.backgroundHex ? Player::Emblems::HexToStrHex(emblemConfig.backgroundColor) : std::to_string(emblemConfig.backgroundColor)).c_str());
				writer.Key("two");
				writer.String((emblemConfig.secondaryHex ? Player::Emblems::HexToStrHex(emblemConfig.secondaryColor) : std::to_string(emblemConfig.secondaryColor)).c_str());
				writer.Key("three");
				writer.String((emblemConfig.primaryHex ? Player::Emblems::HexToStrHex(emblemConfig.primaryColor) : std::to_string(emblemConfig.primaryColor)).c_str());
				writer.Key("fi");
				writer.Int(emblemConfig.foregroundIndex);
				writer.Key("bi");
				writer.Int(emblemConfig.backgroundIndex);
				writer.Key("fl");
				writer.Int(emblemConfig.iconEnabled ? 1 : 0);
				writer.EndObject();
				writer.EndObject();
				player_index = session->MembershipInfo.FindNextPlayer(player_index);
			}
			writer.EndArray();
			writer.EndObject();
			HttpRequest req(L"ElDewrito/" + Utils::String::WidenString(Utils::Version::GetVersionString()), L"", L"");
			try
			{
				std::string sendObject = s.GetString();
				if (!req.SendRequest(Utils::String::WidenString(playersInfoEndpoint), L"POST", L"", L"", L"Content-Type: application/json\r\n", (void *)sendObject.c_str(), sendObject.length()))
				{
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Unable to connect to player info endpoint");
					Utils::Singleton<Modules::ModuleServer>::Instance().VarPlayersInfo->ValueString = "{}";
					return false;
				}
				std::wstring expected = L"HTTP/1.1 200 OK";
				if (req.responseHeader.length() < expected.length())
				{
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Invalid server query response.");
					Utils::Singleton<Modules::ModuleServer>::Instance().VarPlayersInfo->ValueString = "{}";
					return false;
				}
				std::string resp = std::string(req.responseBody.begin(), req.responseBody.end());
				rapidjson::Document json;
				if (json.Parse<0>(resp.c_str()).HasParseError() || !json.IsObject())
				{
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Invalid json returned from player info endpoint.");
					Utils::Singleton<Modules::ModuleServer>::Instance().VarPlayersInfo->ValueString = "{}";
					return false;
				}
				Utils::Singleton<Modules::ModuleServer>::Instance().VarPlayersInfo->ValueString = resp;
			}
			catch (...)
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Exception while getting player info");
				Utils::Singleton<Modules::ModuleServer>::Instance().VarPlayersInfo->ValueString = "{}";
			}
			return true;
		}

		bool AnnounceStats(std::string payload, std::vector<std::string> endpoints) // 0x10B26B90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?AnnounceStats@Stats@Server@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@4@@Z");

			for (auto server : endpoints)
			{
				HttpRequest req(L"ElDewrito/" + Utils::String::WidenString(Utils::Version::GetVersionString()), L"", L"");
				try
				{
					if (!req.SendRequest(Utils::String::WidenString(server), L"POST", L"", L"", L"Content-Type: application/json\r\n", (void *)payload.c_str(), payload.length()))
						Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Unable to connect to stats server");
				}
				catch (...)
				{
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Exception while sending stats to server");
				}
			}
			return true;
		}
	}
}


namespace Server
{
	namespace Stats
	{
		std::string GetStatsPayload() // 0x10B28970
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetStatsPayload@Stats@Server@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (Blam::Network::GetLobbyType() != 2 || Blam::Network::GetNetworkMode() != 3)
				return "";
			std::string encryptedString;
			c_game_statborg *scoreboard = ((c_game_statborg *(__cdecl *)())0x550B80)();
			if (!scoreboard)
				return "";
			long long now = time(nullptr);
			tm *now_tm = gmtime(&now);
			char buf[42];
			strftime(buf, sizeof(buf), "%Y%m%d %X", now_tm);
			std::string pubKey;
			GetStatsPublicKey(pubKey);
			Utils::Cryptography::PublicEncrypt(Utils::Cryptography::ReformatKey(false, pubKey), buf, strlen(buf), encryptedString);
			std::string signature;
			char const *const sig = "signature";
			Utils::Cryptography::CreateRSASignature(Utils::Cryptography::ReformatKey(true, Modules::ModulePlayer::Instance().VarPlayerPrivKey->ValueString), (void *)sig, strlen(sig), signature);
			rapidjson::StringBuffer s;
			rapidjson::Writer<rapidjson::StringBuffer> writer(s);
			writer.StartObject();
			writer.Key("timestamp");
			writer.String(encryptedString.c_str());
			writer.Key("signature");
			writer.String(signature.c_str());
			writer.Key("pubkey");
			writer.String(Modules::ModulePlayer::Instance().VarPlayerPubKey->ValueString.c_str());
			writer.Key("gameVersion");
			writer.String(Utils::Version::GetVersionString().c_str());
			writer.Key("serverName");
			writer.String(Modules::ModuleServer::Instance().VarServerName->ValueString.c_str());
			writer.Key("serverPort");
			writer.Int(Modules::ModuleServer::Instance().VarServerPort->ValueInt);
			writer.Key("port");
			writer.Int(Pointer(0x1860454).Read<unsigned int>());
			writer.Key("hostPlayer");
			writer.String(Modules::ModulePlayer::Instance().VarPlayerName->ValueString.c_str());
			writer.Key("isPrivate");
			writer.Bool(Modules::ModuleServer::Instance().VarServerPassword->ValueString.size() > 0);
			writer.Key("isAnnounced");
			writer.Bool(Modules::ModuleServer::Instance().VarServerShouldAnnounce->ValueInt == 1);
			writer.Key("uid");
			char uid[17];
			player_format_uid(uid, Patches::PlayerUid::Get());
			writer.String(uid);
			writer.Key("game");
			writer.StartObject();
			writer.Key("matchLength");
			__int32 matchLengthSeconds = 0;
			if (matchStartTime < matchEndTime)
				matchLengthSeconds = (__int32)(matchEndTime - matchStartTime);
			writer.Int(matchLengthSeconds);
			writer.Key("roundCount");
			__int32 roundCount = ((int(__cdecl *)())0x5504C0)();
			writer.Int(roundCount);
			writer.Key("sprintEnabled");
			writer.Bool(Modules::ModuleServer::Instance().VarServerSprintState->ValueInt != 0);
			writer.Key("sprintState");
			writer.Int(Modules::ModuleServer::Instance().VarServerSprintState->ValueInt);
			writer.Key("sprintUnlimitedEnabled");
			writer.Bool(Modules::ModuleServer::Instance().VarServerSprintUnlimited->ValueInt != 0);
			writer.Key("maxPlayers");
			writer.Int(Modules::ModuleServer::Instance().VarServerMaxPlayers->ValueInt);
			std::string mapName((char *)Pointer(0x22AB018)(0x1A4, 1));
			std::wstring mapVariantName((wchar_t *)Pointer(0x1863ACA));
			std::wstring variantName((wchar_t *)Pointer(0x23DAF4C));
			e_game_mode gameMode = game_options_get()->game_mode;
			e_game_engine_type variantType = Pointer(0x23DAF18).Read<e_game_engine_type>();
			if (gameMode == _game_mode_mainmenu && mapName == "mainmenu")
			{
				mapName = std::string((char *)Pointer(0x19A5E49));
				variantName = std::wstring((wchar_t *)Pointer(0x179254));
				variantType = Pointer(0x179250).Read<e_game_engine_type>();
			}
			writer.Key("mapName");
			writer.String(Utils::String::ThinString(mapVariantName).c_str());
			writer.Key("mapFile");
			writer.String(mapName.c_str());
			writer.Key("variant");
			writer.String(Utils::String::ThinString(variantName).c_str());
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
			if (variantType >= _game_engine_type_none && variantType < k_number_of_game_engine_types)
			{
				writer.Key("variantType");
				writer.String(game_engine_type_get_string(variantType));
			}
			unsigned __int32 TeamMode = Pointer(0x19A6210).Read<unsigned int>();
			writer.Key("teamGame");
			writer.Bool(TeamMode != 0);
			if (TeamMode == 1)
			{
				writer.Key("teamScores");
				writer.StartArray();
				if (((int(__cdecl *)())0x5CE150)())
				{
					c_game_statborg *statborg = ((c_game_statborg *(__cdecl *)())0x550B80)();
					for (__int32 t = 0; t < 8; t++)
					{
						c_game_statborg::s_team_row &teamScore = statborg->teams[t];
						if (numberOfRounds > 1)
							writer.Int(teamScore.total_score);
						else
							writer.Int(teamScore.score);
					}
				}
				writer.EndArray();
			}
			writer.EndObject();
			writer.Key("players");
			writer.StartArray();
			for (__int32 peerIdx = session->MembershipInfo.FindFirstPeer(); peerIdx != -1; peerIdx = session->MembershipInfo.FindNextPeer(peerIdx))
			{
				__int32 playerIdx = session->MembershipInfo.GetPeerPlayer(peerIdx);
				if (playerIdx == -1)
					continue;
				s_game_results_player_statistics *player_stats = game_results_get_player_stats(playerIdx);
				Blam::Network::PlayerSession *player = &session->MembershipInfo.PlayerSessions[playerIdx];
				std::stringstream color;
				color << "#" << std::setw(6) << std::setfill('0') << std::hex << Player::CPlayerCustomization::GetPlayerPrimaryColor(playerIdx);
				in_addr inAddr;
				inAddr.s_addr = session->GetPeerAddress(peerIdx).ToInAddr();
				char ipStr[22];
				inet_ntop(AF_INET, &inAddr, ipStr, sizeof(ipStr));
				unsigned short team = Pointer(0x2162E28 + playerIdx * 0x1640).Read<unsigned short>();
				char uid[17];
				player_format_uid(uid, player->Properties.host.player_uid);
				Pointer pvpBase(0x23F5A98);
				writer.StartObject();
				writer.Key("name");
				writer.String(Utils::String::ThinString(player->Properties.host.player_name).c_str());
				writer.Key("clientName");
				writer.String(Utils::String::ThinString(player->Properties.client.player_name).c_str());
				writer.Key("serviceTag");
				writer.String(Utils::String::ThinString(player->Properties.host.appearance.service_tag).c_str());
				writer.Key("ip");
				writer.String(ipStr);
				writer.Key("team");
				writer.Int(team);
				writer.Key("playerIndex");
				writer.Int(playerIdx);
				writer.Key("uid");
				writer.String(uid);
				writer.Key("primaryColor");
				writer.String(color.str().c_str());
				s_player_emblem_configuration emblemConfig = player->Properties.host.appearance.emblem_config;
				writer.Key("emblem");
				writer.StartObject();
				writer.Key("one");
				writer.String((emblemConfig.backgroundHex ? Player::Emblems::HexToStrHex(emblemConfig.backgroundColor) : std::to_string(emblemConfig.backgroundColor)).c_str());
				writer.Key("two");
				writer.String((emblemConfig.secondaryHex ? Player::Emblems::HexToStrHex(emblemConfig.secondaryColor) : std::to_string(emblemConfig.secondaryColor)).c_str());
				writer.Key("three");
				writer.String((emblemConfig.primaryHex ? Player::Emblems::HexToStrHex(emblemConfig.primaryColor) : std::to_string(emblemConfig.primaryColor)).c_str());
				writer.Key("fi");
				writer.Int(emblemConfig.foregroundIndex);
				writer.Key("bi");
				writer.Int(emblemConfig.backgroundIndex);
				writer.Key("fl");
				writer.Int(emblemConfig.iconEnabled ? 1 : 0);
				writer.EndObject();
				writer.Key("playerGameStats");
				writer.StartObject();
				writer.Key("round_score");
				writer.Int(player_stats->in_round_score);
				writer.Key("score");
				c_game_results *current_results = game_results_get_current_results();
				writer.Int(current_results->players[playerIdx].score);
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
				writer.Key("playerMedals");
				writer.StartArray();
				for (__int32 i = 0; i < 58; i++)
				{
					if (player_stats->medals[i].earned > 0)
					{
						writer.StartObject();
						writer.Key("medalName");
						writer.String(g_player_medal_names[i]);
						writer.Key("count");
						writer.Int(player_stats->medals[i].earned);
						writer.EndObject();
					}
				}
				writer.EndArray();
				writer.Key("playerWeapons");
				writer.StartArray();
				for (__int32 i = 0; i < 64; i++)
				{
					if (player_stats->weapon_stats[i].initialized == 1)
					{
						writer.StartObject();
						writer.Key("weaponName");
						writer.String(g_damage_reporting_type_names[i]);
						writer.Key("weaponIndex");
						writer.Int(i + 1);
						writer.Key("kills");
						writer.Int(player_stats->weapon_stats[i].kills);
						writer.Key("killedBy");
						writer.Int(player_stats->weapon_stats[i].killed_by);
						writer.Key("betrayalsWith");
						writer.Int(player_stats->weapon_stats[i].betrayals_with);
						writer.Key("suicidesWith");
						writer.Int(player_stats->weapon_stats[i].suicides_with);
						writer.Key("headshotsWith");
						writer.Int(player_stats->weapon_stats[i].headshots_with);
						writer.EndObject();
					}
				}
				writer.EndArray();
				writer.Key("otherStats");
				writer.StartObject();
				__int32 nemesisIdx = 0;
				for (__int32 i = 0, nemesisKills = 0; i < 16; i++)
				{
					unsigned short currKills = pvpBase(playerIdx * 64 + i * 4 + 2, 1).Read<unsigned short>();
					if (currKills <= nemesisKills)
						continue;
					nemesisKills = currKills;
					nemesisIdx = i;
				}
				writer.Key("nemesisIndex");
				writer.Int(nemesisIdx);
				writer.Key("roundsFinished");
				writer.Int(player_stats->rounds_completed);
				writer.Key("roundsWon");
				writer.Int(player_stats->rounds_won);
				writer.Key("flagsCaptured");
				writer.Int(player_stats->ctf_flag_scores);
				writer.Key("flagsCarried");
				writer.Int(player_stats->ctf_flag_grabs);
				writer.Key("carriersKilled");
				writer.Int(player_stats->carriers_killed);
				writer.Key("bombsArmed");
				writer.Int(player_stats->assault_bomb_arms);
				writer.Key("bombsCarried");
				writer.Int(player_stats->assault_bomb_grabs);
				writer.Key("bombsDisarmed");
				writer.Int(player_stats->assault_bomb_disarms);
				writer.Key("bombsDetonated");
				writer.Int(player_stats->assault_bomb_detonations);
				writer.Key("ballHeldTime");
				writer.Int(player_stats->oddball_time_with_ball);
				writer.Key("oddballKillsAsCarrier");
				writer.Int(player_stats->oddball_kills_as_carrier);
				writer.Key("oddballCarrierKills");
				writer.Int(player_stats->oddball_ball_carrier_kills);
				writer.Key("vipsKilled");
				writer.Int(player_stats->vip_takedowns);
				writer.Key("killsAsVip");
				writer.Int(player_stats->vip_kills_as_vip);
				writer.Key("timeAsVip");
				writer.Int(player_stats->vip_time_as_vip);
				writer.Key("vipLives");
				writer.Int(player_stats->vip_lives_as_vip);
				writer.Key("juggernautKills");
				writer.Int(player_stats->juggernaut_kills);
				writer.Key("killsAsJuggernaut");
				writer.Int(player_stats->kills_as_juggernaut);
				writer.Key("timeAsJuggernaut");
				writer.Int(player_stats->time_as_juggernaut);
				writer.Key("territoriesCaptured");
				writer.Int(player_stats->territories_captured);
				writer.Key("territoriesDefended");
				writer.Int(player_stats->territories_ousts);
				writer.Key("timeInTerritory");
				writer.Int(player_stats->time_in_territory);
				writer.Key("kingsKilled");
				writer.Int(player_stats->kings_killed);
				writer.Key("humansInfected");
				writer.Int(player_stats->infection_infections);
				writer.Key("zombiesKilled");
				writer.Int(player_stats->infection_zombie_kills);
				writer.Key("timeInHill");
				writer.Int(player_stats->time_in_hill);
				writer.Key("timeControllingHill");
				writer.Int(player_stats->time_controlling_hill);
				writer.EndObject();
				writer.Key("playerVersusPlayerKills");
				writer.StartArray();
				for (__int32 i = 0; i < 16; i++)
					writer.Int(pvpBase(playerIdx * 64 + i * 4, 1).Read<unsigned short>());
				writer.EndArray();
				writer.EndObject();
			}
			writer.EndArray();
			writer.Key("events");
			writer.StartArray();
			for (__int32 e = 0; e < 1000; e++)
			{
				s_game_results_events *resultsEvent = game_results_get_event(e);
				if (resultsEvent->type == _game_results_event_type_none)
					continue;
				writer.StartObject();
				writer.Key("type");
				writer.Int((char)resultsEvent->type);
				writer.Key("eventTime");
				writer.Int(resultsEvent->time);
				if (resultsEvent->type == _game_results_event_type_kill)
				{
					writer.Key("killerIdx");
					writer.Int(resultsEvent->kill.killing_player_index);
					writer.Key("deadIdx");
					writer.Int(resultsEvent->kill.dead_player_index);
					writer.Key("killer_pos");
					writer.StartArray();
					writer.Double(resultsEvent->kill.killing_player_position.x);
					writer.Double(resultsEvent->kill.killing_player_position.y);
					writer.Double(resultsEvent->kill.killing_player_position.z);
					writer.EndArray();
					writer.Key("dead_pos");
					writer.StartArray();
					writer.Double(resultsEvent->kill.dead_player_position.x);
					writer.Double(resultsEvent->kill.dead_player_position.y);
					writer.Double(resultsEvent->kill.dead_player_position.z);
					writer.EndArray();
					writer.Key("damageType");
					writer.Int64((long)resultsEvent->kill.tracked_damage_type);
				}
				if (resultsEvent->type == _game_results_event_type_carry)
				{
					writer.Key("carry_playerIdx");
					writer.Int(resultsEvent->carry.player_index);
					writer.Key("carry_pos");
					writer.StartArray();
					writer.Double(resultsEvent->carry.player_position.x);
					writer.Double(resultsEvent->carry.player_position.y);
					writer.Double(resultsEvent->carry.player_position.z);
					writer.EndArray();
					writer.Key("carry");
					writer.Int64(resultsEvent->carry.carry);
					writer.Key("carryType");
					writer.Int64(resultsEvent->carry.carry_type);
				}
				if (resultsEvent->type == _game_results_event_type_score)
				{
					writer.Key("score_playerIdx");
					writer.Int(resultsEvent->score.player_index);
					writer.Key("score_pos");
					writer.StartArray();
					writer.Double(resultsEvent->score.player_position.x);
					writer.Double(resultsEvent->score.player_position.y);
					writer.Double(resultsEvent->score.player_position.z);
					writer.EndArray();
					writer.Key("score");
					writer.Int(resultsEvent->score.score);
					writer.Key("scoreType");
					writer.Int(resultsEvent->score.score_type);
				}
				writer.EndObject();
			}
			writer.EndArray();
			writer.EndObject();
			return s.GetString();
		}

		void LifeCycleStateChanged(Blam::Network::LifeCycleState newState) // 0x10B2C0B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?LifeCycleStateChanged@Stats@Server@@YAXW4LifeCycleState@Network@Blam@@@Z");

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (!session || !session->IsEstablished() || !session->IsHost())
			{
			}
			else
			{
				switch (newState)
				{
				case Blam::Network::eLifeCycleStatePreGame:
					if (Blam::Network::GetNumPlayers())
						Server::Stats::UpdatePlayersInfo();
					break;
				case Blam::Network::eLifeCycleStateStartGame:
					Server::Stats::UpdatePlayersInfo();
					break;
				}
			}
		}

		void OnGameStart() // 0x10B2CBA0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnGameStart@Stats@Server@@YAXXZ");

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (!session || !session->IsEstablished() || !session->IsHost())
				return;
			numberOfRounds = ((int(__cdecl *)())0x5504c0)();
		}

		unsigned __int32 GetPeerIp(Blam::Network::Session *session, __int32 peer) // 0x10B27140
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPeerIp@Stats@Server@@YAIPAUSession@Network@Blam@@H@Z");

			Blam::Network::SessionMembership *membership = &session->MembershipInfo;
			__int32 channelIndex = membership->PeerChannels[peer].ChannelIndex;
			return channelIndex >= 0 ? session->Observer->Channels[channelIndex].Address.Address.IPv4 : 0x7F000001;
		}

		void LogListPlayers() // 0x10B2C170
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?LogListPlayers@Stats@Server@@YAXXZ");

			if (Modules::ModuleServer::Instance().VarListPlayersLogEnabled->ValueInt != 1)
				return;
			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			std::stringstream ss;
			std::string listPlayersLogFile = Modules::ModuleServer::Instance().VarListPlayersLogFile->ValueString;
			std::filesystem::path logFilePath(listPlayersLogFile);
			std::filesystem::path parentDirectory = logFilePath.parent_path();
			if (parentDirectory != "")
				std::filesystem::create_directories(parentDirectory);
			std::ofstream logFile(listPlayersLogFile, std::ios::app);
			if (!logFile)
				return;
			auto now = std::chrono::system_clock::now();
			long long time = std::chrono::system_clock::to_time_t(now);
			tm gmTime;
			gmtime_s(&gmTime, &time);
			__int32 peerIdx = session->MembershipInfo.FindFirstPeer();
			while (peerIdx != -1)
			{
				__int32 playerIdx = session->MembershipInfo.GetPeerPlayer(peerIdx);
				if (playerIdx != -1)
				{
					Blam::Network::PlayerSession *player = &session->MembershipInfo.PlayerSessions[playerIdx];
					std::string name = Utils::String::ThinString(player->Properties.host.player_name);
					unsigned __int32 ip = GetPeerIp(session, peerIdx);
					unsigned long long uid = session->MembershipInfo.PlayerSessions[playerIdx].Properties.host.player_uid;
					std::stringstream stream;
					stream << std::hex << uid;
					std::string hexUID = stream.str();
					logFile << "[" << std::put_time(&gmTime, "%m/%d/%y %H:%M:%S") << "] ";
					logFile << "<" << name << "/";
					logFile << hexUID << "/";
					logFile << (ip >> 24) << "." << ((ip >> 16) & 0xFF) << "." << ((ip >> 8) & 0xFF) << "." << (ip & 0xFF) << "> ";
					logFile << std::endl;
				}
				peerIdx = session->MembershipInfo.FindNextPeer(peerIdx);
			}
		}

		void OnEvent(unsigned long player, s_game_engine_event_data const *event, s_multiplayer_event_response_definition const *definition) // 0x10B2C980
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnEvent@Stats@Server@@YAXKPBUs_game_engine_event_data@@PBUs_multiplayer_event_response_definition@@@Z");

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			if (!session || !session->IsEstablished())
				return;
			switch (event->name)
			{
			case 0x4004D:
				time(&sendStatsTime);
				time(&matchEndTime);
				postMatch = true;
				break;
			case 0x400AE:
			case 0x400B0:
			case 0x400BF:
			case 0x400C8:
			case 0x400CF:
			case 0x400D6:
			case 0x400DA:
			case 0x400DF:
			case 0x400F2:
				if (((long (*const)())0x5504C0)() > 1 && ((__int32 (*const)())0x550AD0)())
				{
				}
				else
				{
					time(&matchStartTime);
					matchEndTime = 0;
				}
				break;
			}
		}

		void Init() // 0x10B2BFF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Init@Stats@Server@@YAXXZ");

			Patches::Network::OnLifeCycleStateChanged(LifeCycleStateChanged);
			Patches::Events::OnEvent(OnEvent);
			Patches::Core::OnGameStart(OnGameStart);
			GetPlayersInfoEndpoint();
			time(&listPlayersTime);
		}

		void UpdatePlayersInfo() // 0x10B2CF80
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?UpdatePlayersInfo@Stats@Server@@YAXXZ");

			HANDLE thread = CreateThread(nullptr, 0, Server::Stats::GetPlayersInfo_Thread, (LPVOID)"", 0, nullptr);
		}

		void Tick() // 0x10B2CC30
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@Stats@Server@@YAXXZ");

			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			long long curTime1;
			if (!session || !session->IsEstablished())
				postMatch = false;
			if (!session || !session->IsEstablished() || !session->IsHost())
				return;
			time(&curTime1);
			if (sendStatsTime)
			{
				long long elapsed = curTime1 - sendStatsTime;
				if (elapsed > 1)
				{
					if (Modules::ModuleServer::Instance().VarShouldSubmitStats->ValueInt == 1)
					{
						std::vector<std::string> statsEndpoints;
						GetStatsEndpoints(statsEndpoints);
						if (statsEndpoints.size() > 0)
						{
							std::string statsPayload = GetStatsPayload();
							if (statsPayload != "" && statsPayload.size() > 0)
							{
								std::thread SendStats(AnnounceStats, statsPayload, statsEndpoints);
								SendStats.detach();
							}
						}
					}
					sendStatsTime = 0;
				}
			}
			if (listPlayersTime && Blam::Network::GetNetworkMode() == 3)
			{
				long long elapsed = curTime1 - listPlayersTime;
				if (elapsed > 45)
				{
					LogListPlayers();
					time(&listPlayersTime);
				}
			}
		}

		bool localPlayerIsPostMatch() // 0x10B2D5E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?localPlayerIsPostMatch@Stats@Server@@YA_NXZ");

			return postMatch;
		}
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_enum<enum e_game_results_event_type,char>::operator==(e_game_results_event_type const &) const;
template c_enum<enum e_damage_reporting_type,long>::operator long() const;
template c_enum<enum e_game_results_event_type,char>::operator char() const;

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace Server { namespace Stats { long long matchStartTime; } }
namespace Server { namespace Stats { long long matchEndTime; } }
namespace Server { namespace Stats { long long sendStatsTime; } }
namespace Server { namespace Stats { long long listPlayersTime; } }
namespace Server { namespace Stats { bool postMatch; } }
namespace Server { namespace Stats { std::string playersInfoEndpoint; } }
namespace Server { namespace Stats { __int32 numberOfRounds = 1; } }
