/* ---------- headers */

#include "Player/PlayerServiceRecord.hpp"
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
#include "Common/Http/HttpRequest.hpp"
#include "ElDorito.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
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
#include "Utils/Logger.hpp"  // hades: added for 0x106C73A0

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
class c_network_session;
struct s_network_session_player;
namespace Player
{
	namespace ServiceRecord
	{
		struct PlayerTopMedals;
		struct ServiceRecord;
		struct ServiceRecordPlayer;
	}
}
namespace Utils
{
	class DewritoReader;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace ServiceRecord {}
	using namespace Player::ServiceRecord;
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

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void GetServiceRecordEndpoint();
bool ValidNetworkPlayerIndex(__int32 networkPlayerIndex); extern bool (*const network_session_interface_get_squad_session)(c_network_session **);  // hades: added for 0x106CAB50
std::wstring processNumber(__int32 num);
extern void player_format_uid(char *string, unsigned long long id);  // hades: added for 0x106C73A0
namespace Utils::Version { std::string GetVersionString(); }  // hades: added for 0x106C73A0
void clearCachedServiceRecords();

/* ---------- globals */

namespace Utils
{
	Utils::DewritoReader *Utils::Singleton<Utils::DewritoReader>::m_instance; // 0x113861C4
}

/* ---------- private variables */

namespace hades_file_local
{
	::Player::ServiceRecord::ServiceRecord ServiceRecords[16]; // 0x113861C8  // hades: defined, so its dynamic initializer emits the constructor
	::Player::ServiceRecord::ServiceRecordPlayer currentDesiredRecord; // 0x11387948  // hades: defined, so its dynamic initializer emits the constructor
	extern bool threadActive; // 0x11387994
	extern std::string serviceRecordEndpoint; // 0x11387978
}
using namespace hades_file_local;
/* ---------- public code */

namespace Player
{
	namespace ServiceRecord
	{
		unsigned long __stdcall GetServiceRecord_Thread(void *lpParam) // 0x106C73A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetServiceRecord_Thread@ServiceRecord@Player@@YGKPAX@Z");
			// static ...; // 0x106C8AFF
			// static ...; // 0x106C8AFD
			// static ...; // 0x106C8AF6
			// static ...; // 0x106C8AF2
			// static ...; // 0x106C8AEE
			// static ...; // 0x106C8AE7
			// static ...; // 0x106C8ADC
			// static ...; // 0x106C8AD3
			// static ...; // 0x106C8ACE
			// static ...; // 0x106C8AC9
			// static ...; // 0x106C8AC5
			// static ...; // 0x106C8ABA
			// static ...; // 0x106C8AB4
			// static ...; // 0x106C8A18
			// static ...; // 0x106C8A10
		// $LN64:
			// void *lpParam;
			// char uid[17];
			// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> s;
			// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
			// Player::ServiceRecord::ServiceRecord record;
			// HttpRequest req;
			// Player::ServiceRecord::ServiceRecordPlayer playerRecord;
				// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
				// std::string sendObject;
				// std::wstring expected;
				// std::string resp;
					// __int32 id;
					// char const *name;
					// unsigned long long uid;
					// char const *uid_str;
					// __int32 exp;
					// __int32 skill;
					// __int32 total_games;
					// __int32 total_wins;
					// __int32 total_kills;
					// __int32 total_deaths;
					// __int32 total_medals;
					// __int32 best_streak;
					// __int32 ranked_matches;
					// __int32 social_matches;
					// __int32 custom_games;
					// rapidjson::GenericArray<0,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > top_medals;
						// __int32 x;
							// Player::ServiceRecord::PlayerTopMedals medal;

			ServiceRecordPlayer playerRecord = currentDesiredRecord;
			if (!ValidNetworkPlayerIndex(playerRecord.networkPlayerIndex))
				return 0;
			if (serviceRecordEndpoint.empty())
				GetServiceRecordEndpoint();
			if (serviceRecordEndpoint.empty())
			{
				threadActive = false;
				return 0;
			}
			rapidjson::StringBuffer s;
			rapidjson::Writer<rapidjson::StringBuffer> writer(s);
			writer.StartObject();
			writer.Key("name");
			writer.String(Utils::String::ThinString(playerRecord.name).c_str());
			writer.Key("uid");
			char uid[17];
			player_format_uid(uid, playerRecord.uid);
			writer.String(uid);
			writer.EndObject();
			HttpRequest req(L"ElDewrito/" + Utils::String::WidenString(Utils::Version::GetVersionString()), L"", L"");
			ServiceRecord record;
			try
			{
				std::string sendObject = s.GetString();
				if (!req.SendRequest(Utils::String::WidenString(serviceRecordEndpoint), L"POST", L"", L"", L"Content-Type: application/json\r\n", (void *)sendObject.c_str(), sendObject.length()))
				{
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Unable to connect to service record endpoint");
					record.uid = playerRecord.uid;
					record.Empty = true;
					ServiceRecords[playerRecord.networkPlayerIndex] = record;
					threadActive = false;
					return 0;
				}
				std::wstring expected = L"HTTP/1.1 200 OK";
				if (req.responseHeader.length() < expected.length())
				{
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Invalid server query response.");
					record.uid = playerRecord.uid;
					record.Empty = true;
					ServiceRecords[playerRecord.networkPlayerIndex] = record;
					threadActive = false;
					return 0;
				}
				std::string resp(req.responseBody.begin(), req.responseBody.end());
				rapidjson::Document json;
				if (json.Parse<0>(resp.c_str()).HasParseError() || !json.IsObject() || resp == "{}")
				{
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Invalid json returned from player info endpoint.");
					record.uid = playerRecord.uid;
					record.Empty = true;
					ServiceRecords[playerRecord.networkPlayerIndex] = record;
					threadActive = false;
					return 0;
				}
				if (json.HasMember("id") && json["id"].IsInt())
				{
					__int32 id = json["id"].GetInt();
					record.playerId = id;
				}
				if (json.HasMember("name") && json["name"].IsString())
				{
					char const *name = json["name"].GetString();
					record.name = name;
				}
				if (json.HasMember("uid") && json["uid"].IsString())
				{
					char const *uid_str = json["uid"].GetString();
					unsigned long long uid;
					Utils::String::HexStringToBytes(uid_str, &uid, 8);
					uid = _byteswap_uint64(uid);
					record.uid = uid;
				}
				if (json.HasMember("exp") && json["exp"].IsInt())
				{
					__int32 exp = json["exp"].GetInt();
					record.exp = exp;
				}
				if (json.HasMember("skill") && json["exp"].IsInt())
				{
					__int32 skill = json["skill"].GetInt();
					record.skill = skill;
				}
				if (json.HasMember("total_games") && json["total_games"].IsInt())
				{
					__int32 total_games = json["total_games"].GetInt();
					record.games = total_games;
				}
				if (json.HasMember("total_wins") && json["total_wins"].IsInt())
				{
					__int32 total_wins = json["total_wins"].GetInt();
					record.wins = total_wins;
				}
				if (json.HasMember("total_kills") && json["total_kills"].IsInt())
				{
					__int32 total_kills = json["total_kills"].GetInt();
					record.kills = total_kills;
				}
				if (json.HasMember("total_deaths") && json["total_deaths"].IsInt())
				{
					__int32 total_deaths = json["total_deaths"].GetInt();
					record.deaths = total_deaths;
				}
				if (json.HasMember("total_medals") && json["total_medals"].IsInt())
				{
					__int32 total_medals = json["total_medals"].GetInt();
					record.medals = total_medals;
				}
				if (json.HasMember("best_streak") && json["best_streak"].IsInt())
				{
					__int32 best_streak = json["best_streak"].GetInt();
					record.best_streak = best_streak;
				}
				if (json.HasMember("ranked_matches") && json["ranked_matches"].IsInt())
				{
					__int32 ranked_matches = json["ranked_matches"].GetInt();
					record.ranked_matches = ranked_matches;
				}
				if (json.HasMember("social_matches") && json["social_matches"].IsInt())
				{
					__int32 social_matches = json["social_matches"].GetInt();
					record.social_matches = social_matches;
				}
				if (json.HasMember("custom_games") && json["custom_games"].IsInt())
				{
					__int32 custom_games = json["custom_games"].GetInt();
					record.custom_games = custom_games;
				}
				if (json.HasMember("top_medals") && json["top_medals"].IsArray())
				{
					auto top_medals = json["top_medals"].GetArray();
					for (__int32 x = 0; x < top_medals.Size(); x++)
					{
						PlayerTopMedals medal = static_cast<PlayerTopMedals const &>(record.top_medals[x]);
						if (top_medals[x].HasMember("id") && top_medals[x]["id"].IsInt() && top_medals[x].HasMember("value") && top_medals[x]["value"].IsInt())
						{
							record.top_medals[x].id = top_medals[x]["id"].GetInt();
							record.top_medals[x].count = top_medals[x]["value"].GetInt();
							record.top_medals[x].countStr = processNumber(top_medals[x]["value"].GetInt());
						}
					}
				}
				threadActive = false;
				ServiceRecords[playerRecord.networkPlayerIndex] = record;
				return 1;
			}
			catch (...)
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Exception while getting player info");
			}
			record.uid = playerRecord.uid;
			record.Empty = true;
			ServiceRecords[playerRecord.networkPlayerIndex] = record;
			threadActive = false;
			return 0;
		}

		// mangled_x86(MANGLED_DEFAULT, "??0PlayerTopMedals@ServiceRecord@Player@@QAE@ABU012@@Z"); no body to assert in
		// PlayerTopMedals::PlayerTopMedals(::Player::ServiceRecord::PlayerTopMedals const &__that) = default; // 0x106C5D30  // hades: implicit (aggregate)

		// mangled_x86(MANGLED_DEFAULT, "??0PlayerTopMedals@ServiceRecord@Player@@QAE@XZ"); no body to assert in

		// mangled_x86(MANGLED_DEFAULT, "??0ServiceRecord@0Player@@QAE@ABU001@@Z"); no body to assert in
		// implicit copy constructor (aggregate); emitted through getCachedServiceRecord // 0x106C5E40

		// mangled_x86(MANGLED_DEFAULT, "??0ServiceRecord@0Player@@QAE@XZ"); no body to assert in

		// mangled_x86(MANGLED_DEFAULT, "??0ServiceRecordPlayer@ServiceRecord@Player@@QAE@XZ"); no body to assert in
		// _inline ServiceRecordPlayer::ServiceRecordPlayer() // 0x106C6170  // hades: implicit now; networkPlayerIndex's member initializer does this
		// {
		// 	networkPlayerIndex = -1;
		// }
	}
}

// mangled_x86(MANGLED_DEFAULT, "??1HttpRequest@@QAE@XZ"); no body to assert in
_inline HttpRequest::~HttpRequest() = default; // 0x106C63A0

namespace Player
{
	namespace ServiceRecord
	{
		// mangled_x86(MANGLED_DEFAULT, "??1PlayerTopMedals@ServiceRecord@Player@@QAE@XZ"); no body to assert in
		// PlayerTopMedals::~PlayerTopMedals() = default; // 0x106C6410  // hades: implicit (aggregate)

		// mangled_x86(MANGLED_DEFAULT, "??1ServiceRecord@0Player@@QAE@XZ"); no body to assert in
		// implicit destructor // 0x106C6460

		// mangled_x86(MANGLED_DEFAULT, "??4PlayerTopMedals@ServiceRecord@Player@@QAEAAU012@$$QAU012@@Z"); no body to assert in
		// ::Player::ServiceRecord::PlayerTopMedals &PlayerTopMedals::operator=(::Player::ServiceRecord::PlayerTopMedals &&__that) noexcept = default; // 0x106C6610  // hades: implicit (aggregate)

		// mangled_x86(MANGLED_DEFAULT, "??4PlayerTopMedals@ServiceRecord@Player@@QAEAAU012@ABU012@@Z"); no body to assert in
		// ::Player::ServiceRecord::PlayerTopMedals &PlayerTopMedals::operator=(::Player::ServiceRecord::PlayerTopMedals const &__that) = default; // 0x106C6690  // hades: implicit (aggregate)

		// mangled_x86(MANGLED_DEFAULT, "??4ServiceRecord@0Player@@QAEAAU001@$$QAU001@@Z"); no body to assert in
		// implicit move assignment // 0x106C6710

		// mangled_x86(MANGLED_DEFAULT, "??4ServiceRecord@0Player@@QAEAAU001@ABU001@@Z"); no body to assert in
		// implicit copy assignment // 0x106C6890

		::Player::ServiceRecord::ServiceRecord getCachedServiceRecord(__int32 networkPlayerIndex) // 0x106CA2C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?getCachedServiceRecord@ServiceRecord@Player@@YA?AU112@H@Z");
			// __int32 networkPlayerIndex;

			return hades_file_local::ServiceRecords[networkPlayerIndex];
		}

		void clearCache() // 0x106CA000
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?clearCache@ServiceRecord@Player@@YAXXZ");
			// procedure flags: nofpo

			clearCachedServiceRecords();
		}

		void requestPlayerServiceRecord(__int32 networkPlayerIndex) // 0x106CAB50
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?requestPlayerServiceRecord@ServiceRecord@Player@@YAXH@Z");
			// static ...; // 0x106CAD27
			// static ...; // 0x106CAD20
			// static ...; // 0x106CAD08
			// static ...; // 0x106CAD00
			// __int32 networkPlayerIndex;
			// s_network_session_player *networkPlayer;
			// c_network_session *session;
				// Player::ServiceRecord::ServiceRecordPlayer player;
				// void *thread;
			// function call : bool (*const)(c_network_session **)
			// function call : void *(_SECURITY_ATTRIBUTES *, unsigned long, unsigned long (*)(void *), void *, unsigned long, unsigned long *)

			if (!ValidNetworkPlayerIndex(networkPlayerIndex))
				return;
			if (threadActive)
				return;
			c_network_session *session;
			if (!network_session_interface_get_squad_session(&session) || !session->established())
				return;
			s_network_session_player *networkPlayer = session->get_player(networkPlayerIndex);
			if (!networkPlayer)
				return;
			if (ServiceRecords[networkPlayerIndex].uid == networkPlayer->configuration.host.player_uid)
				return;
			else
			{
				ServiceRecordPlayer player = {};
				memcpy(player.name, networkPlayer->configuration.host.player_name, sizeof(player.name));
				player.uid = networkPlayer->configuration.host.player_uid;
				player.networkPlayerIndex = networkPlayerIndex;
				currentDesiredRecord = player;
				threadActive = true;
				void *thread = CreateThread(nullptr, 0, GetServiceRecord_Thread, (void *)"", 0, nullptr);
			}
		}
	}
}

/* ---------- private code */

void GetServiceRecordEndpoint() // 0x106C7200
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetServiceRecordEndpoint@@YAXXZ");
	// `anonymous-namespace'::GetServiceRecordEndpoint
	// procedure flags: nofpo
	// static ...; // 0x106C733C
	// static ...; // 0x106C7330
	// static ...; // 0x106C7328
	// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
		// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &statsObject;

	if (!Utils::Singleton<Utils::DewritoReader>::Instance().IsValid())
		return;
	auto json = Utils::Singleton<Utils::DewritoReader>::Instance().GetDewritoJson();
	if (json.IsObject() && json.HasMember("stats"))
	{
		auto &statsObject = json["stats"];
		if (statsObject.HasMember("serviceRecord"))
			serviceRecordEndpoint = statsObject["serviceRecord"].GetString();
	}
}

static bool ValidNetworkPlayerIndex(__int32 networkPlayerIndex) // 0x106C9A30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ValidNetworkPlayerIndex@@YA_NH@Z");
	// `anonymous-namespace'::ValidNetworkPlayerIndex
	// __int32 networkPlayerIndex;

	return networkPlayerIndex >= 0 && networkPlayerIndex < 16;
}

std::wstring processNumber(__int32 num) // 0x106CA7E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?processNumber@@YA?AV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@H@Z");
	// `anonymous-namespace'::processNumber
	// static ...; // 0x106CAA18
	// static ...; // 0x106CAA0C
	// static ...; // 0x106CAA04
	// __int32 num;
	// std::ostringstream oss;
		// double numInK;
		// double numInM;

	std::ostringstream oss;
	if (num < 1000)
		oss << num << "x";
	else if (num >= 1000 && num < 1000000)
	{
		double numInK = floor(num / 100.0) / 10.0;
		oss << numInK << "k";
	}
	else
	{
		double numInM = floor(num / 100000.0) / 10.0;
		oss << numInM << "m";
	}
	return Utils::String::WidenString(oss.str().c_str());
}

void clearCachedServiceRecords() // 0x106CA040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?clearCachedServiceRecords@@YAXXZ");
	// `anonymous-namespace'::clearCachedServiceRecords
	// procedure flags: nofpo
		// __int32 i;

	for (__int32 i = 0; i < 16; i++)
		hades_file_local::ServiceRecords[i] = {};
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Utils::DewritoReader & Utils::Singleton<Utils::DewritoReader>::Instance();

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { bool threadActive; }
namespace hades_file_local { std::string serviceRecordEndpoint; }
