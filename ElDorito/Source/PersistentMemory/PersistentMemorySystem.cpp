/* ---------- headers */

#include "PersistentMemory/PersistentMemorySystem.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "ElDorito.hpp"
#include "Forge/Prefab.hpp"
#include "Pointer.hpp"
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
#include "ThirdParty/rapidjson/istreamwrapper.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/ostreamwrapper.h"
#include "ThirdParty/rapidjson/prettywriter.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include "Utils/Logger.hpp"  // hades: added for 0x106B5600

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

struct begin;
struct end;
namespace PersistentMemory
{
	struct SPersistentMemoryDB;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace PersistentMemory {}
using namespace ::PersistentMemory;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace PersistentMemory
{
	extern PersistentMemory::SPersistentMemoryDB LoadPersistentMemory(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &value);
	extern bool Load(std::string const &filename);
	extern void Save();
	extern void Init();
	extern std::string GetLastAnnoucementViewedDate();
	extern void SetLastAnnoucementViewedDate(std::string annoucementViewedDate);
	extern __int32 GetLastMapID();
	extern void SetLastMapID(__int32 mapID);
	extern std::string GetLastMapName();
	extern void SetLastMapName(std::string mapName);
	extern std::string GetLastGameType();
	extern void SetLastGameType(std::string gameType);
	extern std::string GetLastMultiplayerMod();
	extern void SetLastMultiplayerMod(std::string multiplayerMod);
	extern std::string GetLastCampaignMod();
	extern void SetLastCampaignMod(std::string campaignMod);
	extern std::string GetLastFirefightMod();
	extern void SetLastFirefightMod(std::string firefightMod);
	extern void AddMutedVoipPlayer(std::string name, std::string uid);
	extern bool RemoveMutedVoipPlayer(std::string uid);
	extern bool PlayerIsVoipMuted(std::string uid);
}

/* ---------- globals */

namespace PersistentMemory
{
	extern std::string persistentMemoryPath; // 0x11386164
	PersistentMemory::SPersistentMemoryDB persistentMemoryDB; // 0x113860A8  // hades: defined, so its dynamic initializer emits the constructor
}

/* ---------- private variables */

/* ---------- public code */

namespace PersistentMemory
{
	PersistentMemory::SPersistentMemoryDB LoadPersistentMemory(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &value) // 0x106B58F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?LoadPersistentMemory@PersistentMemory@@YA?AUSPersistentMemoryDB@1@AAV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@@Z");
		// static ...; // 0x106B5E6B
		// static ...; // 0x106B5E67
		// static ...; // 0x106B5E63
		// static ...; // 0x106B5E5E
		// static ...; // 0x106B5E59
		// static ...; // 0x106B5E54
		// static ...; // 0x106B5E4F
		// static ...; // 0x106B5E4A
		// static ...; // 0x106B5E45
		// static ...; // 0x106B5E40
		// static ...; // 0x106B5E3B
		// static ...; // 0x106B5E30
		// static ...; // 0x106B5DA0
		// static ...; // 0x106B5D98
		// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &value;
		// PersistentMemory::SPersistentMemoryDB persistentMemory;
			// char const *const &lastAnnoucementViewedDate;
			// __int32 const &lastMapID;
			// char const *const &lastMapName;
			// char const *const &lastGameType;
			// char const *const &lastMultiplayerMod;
			// char const *const &lastCampaignMod;
			// char const *const &lastFirefightMod;
			// rapidjson::GenericArray<0,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > const &mutedVoipPlayers;
				// rapidjson::GenericArray<0,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > const &<range>$L0;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > *<begin>$L0;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > *<end>$L0;
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &player;
						// char const *const &uid;
						// PersistentMemory::SPersistentMemoryDB::SPersistantMute new_player;
						// char const *const &name;

		PersistentMemory::SPersistentMemoryDB persistentMemory;
		if (value.HasMember("lastAnnoucementViewedDate"))
		{
			char const *const &lastAnnoucementViewedDate = value["lastAnnoucementViewedDate"].GetString();
			persistentMemory.lastAnnoucementViewedDate = lastAnnoucementViewedDate;
		}
		if (value.HasMember("lastMapID"))
		{
			__int32 const &lastMapID = value["lastMapID"].GetInt();
			persistentMemory.lastMapID = lastMapID;
		}
		if (value.HasMember("lastMapName"))
		{
			char const *const &lastMapName = value["lastMapName"].GetString();
			persistentMemory.lastMapName = lastMapName;
		}
		if (value.HasMember("lastGameType"))
		{
			char const *const &lastGameType = value["lastGameType"].GetString();
			persistentMemory.lastGameType = lastGameType;
		}
		if (value.HasMember("lastMultiplayerMod"))
		{
			char const *const &lastMultiplayerMod = value["lastMultiplayerMod"].GetString();
			persistentMemory.lastMultiplayerMod = lastMultiplayerMod;
		}
		if (value.HasMember("lastCampaignMod"))
		{
			char const *const &lastCampaignMod = value["lastCampaignMod"].GetString();
			persistentMemory.lastCampaignMod = lastCampaignMod;
		}
		if (value.HasMember("lastFirefightMod"))
		{
			char const *const &lastFirefightMod = value["lastFirefightMod"].GetString();
			persistentMemory.lastFirefightMod = lastFirefightMod;
		}
		if (value.HasMember("mutedVoipPlayers") && value["mutedVoipPlayers"].IsArray())
		{
			auto const &mutedVoipPlayers = value["mutedVoipPlayers"].GetArray();
			for (rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &player : mutedVoipPlayers)
			{
				if (player.IsObject() && player.HasMember("name") && player.HasMember("uid"))
				{
					char const *const &name = player["name"].GetString();
					char const *const &uid = player["uid"].GetString();
					PersistentMemory::SPersistentMemoryDB::SPersistantMute new_player = { name, uid };
					persistentMemory.mutedVoipPlayers.push_back(new_player);
				}
			}
		}
		return persistentMemory;
	}

	// mangled_x86(MANGLED_DEFAULT, "??0SPersistantMute@SPersistentMemoryDB@PersistentMemory@@QAE@$$QAU012@@Z"); no body to assert in
	// _inline SPersistentMemoryDB::SPersistantMute::SPersistantMute(PersistentMemory::SPersistentMemoryDB::SPersistantMute &&__that) = default; // 0x106AF9A0  // hades: left implicit

	// mangled_x86(MANGLED_DEFAULT, "??0SPersistantMute@SPersistentMemoryDB@PersistentMemory@@QAE@ABU012@@Z"); no body to assert in
	// _inline SPersistentMemoryDB::SPersistantMute::SPersistantMute(PersistentMemory::SPersistentMemoryDB::SPersistantMute const &__that) = default; // 0x106AFA30  // hades: left implicit

	// mangled_x86(MANGLED_DEFAULT, "??0SPersistentMemoryDB@PersistentMemory@@QAE@$$QAU01@@Z"); no body to assert in
	// _inline SPersistentMemoryDB::SPersistentMemoryDB(PersistentMemory::SPersistentMemoryDB &&__that) = default; // 0x106AFB00  // hades: left implicit

	// mangled_x86(MANGLED_DEFAULT, "??0SPersistentMemoryDB@PersistentMemory@@QAE@XZ"); no body to assert in

	bool Load(std::string const &filename) // 0x106B5600
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Load@PersistentMemory@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x106B5850
		// static ...; // 0x106B584C
		// static ...; // 0x106B5848
		// static ...; // 0x106B5824
		// static ...; // 0x106B581C
		// std::string const &filename;
		// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> doc;
		// std::ifstream stream;
		// rapidjson::BasicIStreamWrapper<std::istream > isw;

		persistentMemoryPath = filename;
		std::ifstream stream(std::filesystem::absolute(filename));
		rapidjson::IStreamWrapper isw(stream);
		rapidjson::Document doc;
		doc.ParseStream(isw);
		if (doc.HasParseError())
		{
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, "Invalid json in persistent_memory.json. Persistent Memory will not be applied!");
			return false;
		}
		persistentMemoryDB = LoadPersistentMemory(doc);
		return true;
	}

	// mangled_x86(MANGLED_DEFAULT, "??1SPersistantMute@SPersistentMemoryDB@PersistentMemory@@QAE@XZ"); no body to assert in
	// _inline SPersistentMemoryDB::SPersistantMute::~SPersistantMute() = default; // 0x106B0E30  // hades: left implicit

	// mangled_x86(MANGLED_DEFAULT, "??1SPersistentMemoryDB@PersistentMemory@@QAE@XZ"); no body to assert in
	// _inline SPersistentMemoryDB::~SPersistentMemoryDB() = default; // 0x106B0E90  // hades: left implicit

	// mangled_x86(MANGLED_DEFAULT, "??4SPersistantMute@SPersistentMemoryDB@PersistentMemory@@QAEAAU012@$$QAU012@@Z"); no body to assert in
	// _inline PersistentMemory::SPersistentMemoryDB::SPersistantMute &SPersistentMemoryDB::SPersistantMute::operator=(PersistentMemory::SPersistentMemoryDB::SPersistantMute &&__that) = default; // 0x106B1300  // hades: left implicit

	// mangled_x86(MANGLED_DEFAULT, "??4SPersistentMemoryDB@PersistentMemory@@QAEAAU01@$$QAU01@@Z"); no body to assert in
	// _inline PersistentMemory::SPersistentMemoryDB &SPersistentMemoryDB::operator=(PersistentMemory::SPersistentMemoryDB &&__that) = default; // 0x106B1370  // hades: left implicit

	void Save() // 0x106B75E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Save@PersistentMemory@@YAXXZ");
		// procedure flags: nofpo
		// static ...; // 0x106B7963
		// static ...; // 0x106B795F
		// static ...; // 0x106B7958
		// static ...; // 0x106B7934
		// static ...; // 0x106B792C
		// rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
		// std::ofstream stream;
		// rapidjson::BasicOStreamWrapper<std::ostream > isw;
			// std::vector<PersistentMemory::SPersistentMemoryDB::SPersistantMute> &<range>$L0;
			// PersistentMemory::SPersistentMemoryDB::SPersistantMute *<begin>$L0;
			// PersistentMemory::SPersistentMemoryDB::SPersistantMute *<end>$L0;
				// PersistentMemory::SPersistentMemoryDB::SPersistantMute const &player;

		std::ofstream stream(std::filesystem::absolute(persistentMemoryPath), std::ios::out);
		rapidjson::OStreamWrapper isw(stream);
		rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(isw);
		writer.StartObject();
		writer.Key("lastAnnoucementViewedDate");
		writer.String(persistentMemoryDB.lastAnnoucementViewedDate.c_str());
		writer.Key("lastMapID");
		writer.Int(persistentMemoryDB.lastMapID);
		writer.Key("lastMapName");
		writer.String(persistentMemoryDB.lastMapName.c_str());
		writer.Key("lastGameType");
		writer.String(persistentMemoryDB.lastGameType.c_str());
		writer.Key("lastMultiplayerMod");
		writer.String(persistentMemoryDB.lastMultiplayerMod.c_str());
		writer.Key("lastCampaignMod");
		writer.String(persistentMemoryDB.lastCampaignMod.c_str());
		writer.Key("lastFirefightMod");
		writer.String(persistentMemoryDB.lastFirefightMod.c_str());
		writer.Key("mutedVoipPlayers");
		writer.StartArray();
		for (auto const &player : persistentMemoryDB.mutedVoipPlayers)
		{
			writer.StartObject();
			writer.Key("name");
			writer.String(player.player_name.c_str());
			writer.Key("uid");
			writer.String(player.player_uid.c_str());
			writer.EndObject();
		}
		writer.EndArray();
		writer.EndObject();
	}

	void Init() // 0x106B4BC0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Init@PersistentMemory@@YAXXZ");
		// procedure flags: nofpo
		// static ...; // 0x106B4E53
		// static ...; // 0x106B4E50
		// static ...; // 0x106B4E38
		// static ...; // 0x106B4E30
		// std::string prefsName;
			// std::stringstream ss;

		if (Utils::Singleton<ElDorito>::Instance().IsDedicated())
			return;
		std::string prefsName = "persistent_memory.json";
		if (!(Utils::Singleton<ElDorito>::Instance().GetInstanceName() == ""))
		{
			std::stringstream ss;
			ss << "persistent_memory_" << Utils::Singleton<ElDorito>::Instance().GetInstanceName() << ".json";
			prefsName = ss.str();
		}
		Load("data\\cache\\" + prefsName);
	}
}


namespace PersistentMemory
{
	std::string GetLastAnnoucementViewedDate() // 0x106B4570
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetLastAnnoucementViewedDate@PersistentMemory@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// procedure flags: nofpo

		return persistentMemoryDB.lastAnnoucementViewedDate;
	}

	void SetLastAnnoucementViewedDate(std::string annoucementViewedDate) // 0x106B7C00
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetLastAnnoucementViewedDate@PersistentMemory@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string annoucementViewedDate;

		persistentMemoryDB.lastAnnoucementViewedDate = annoucementViewedDate;
	}

	__int32 GetLastMapID() // 0x106B4730
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetLastMapID@PersistentMemory@@YAHXZ");
		// procedure flags: nofpo

			return persistentMemoryDB.lastMapID;
	}

	void SetLastMapID(__int32 mapID) // 0x106B7E80
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetLastMapID@PersistentMemory@@YAXH@Z");
		// __int32 mapID;

		persistentMemoryDB.lastMapID = mapID;
	}
}


namespace PersistentMemory
{
	std::string GetLastMapName() // 0x106B4750
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetLastMapName@PersistentMemory@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// procedure flags: nofpo

		return persistentMemoryDB.lastMapName;
	}

	void SetLastMapName(std::string mapName) // 0x106B7EB0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetLastMapName@PersistentMemory@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string mapName;

		persistentMemoryDB.lastMapName = mapName;
	}
}


namespace PersistentMemory
{
	std::string GetLastGameType() // 0x106B46C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetLastGameType@PersistentMemory@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// procedure flags: nofpo

		return persistentMemoryDB.lastGameType;
	}

	void SetLastGameType(std::string gameType) // 0x106B7DE0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetLastGameType@PersistentMemory@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string gameType;

		persistentMemoryDB.lastGameType = gameType;
	}
}


namespace PersistentMemory
{
	std::string GetLastMultiplayerMod() // 0x106B47C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetLastMultiplayerMod@PersistentMemory@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// procedure flags: nofpo

		return persistentMemoryDB.lastMultiplayerMod;
	}

	void SetLastMultiplayerMod(std::string multiplayerMod) // 0x106B7F50
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetLastMultiplayerMod@PersistentMemory@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string multiplayerMod;

		persistentMemoryDB.lastMultiplayerMod = multiplayerMod;
	}
}


namespace PersistentMemory
{
	std::string GetLastCampaignMod() // 0x106B45E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetLastCampaignMod@PersistentMemory@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// procedure flags: nofpo

		return persistentMemoryDB.lastCampaignMod;
	}

	void SetLastCampaignMod(std::string campaignMod) // 0x106B7CA0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetLastCampaignMod@PersistentMemory@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string campaignMod;

		persistentMemoryDB.lastCampaignMod = campaignMod;
	}
}


namespace PersistentMemory
{
	std::string GetLastFirefightMod() // 0x106B4650
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetLastFirefightMod@PersistentMemory@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// procedure flags: nofpo

		return persistentMemoryDB.lastFirefightMod;
	}

	void SetLastFirefightMod(std::string firefightMod) // 0x106B7D40
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetLastFirefightMod@PersistentMemory@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string firefightMod;

		persistentMemoryDB.lastFirefightMod = firefightMod;
	}

	void AddMutedVoipPlayer(std::string name, std::string uid) // 0x106B2B50
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?AddMutedVoipPlayer@PersistentMemory@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
		// static ...; // 0x106B2C2C
		// static ...; // 0x106B2C24
		// std::string name;
		// std::string uid;
		// PersistentMemory::SPersistentMemoryDB::SPersistantMute muted;

		PersistentMemory::SPersistentMemoryDB::SPersistantMute muted = { name, uid };
		persistentMemoryDB.mutedVoipPlayers.push_back(muted);
	}

	bool RemoveMutedVoipPlayer(std::string uid) // 0x106B7410
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?RemoveMutedVoipPlayer@PersistentMemory@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x106B7578
		// static ...; // 0x106B756C
		// static ...; // 0x106B7564
		// std::string uid;
			// std::_Vector_iterator<std::_Vector_val<std::_Simple_types<PersistentMemory::SPersistentMemoryDB::SPersistantMute> > > it;

		for (auto it = persistentMemoryDB.mutedVoipPlayers.begin(); it != persistentMemoryDB.mutedVoipPlayers.end(); ++it)
		{
			if (it->player_uid == uid)
			{
				persistentMemoryDB.mutedVoipPlayers.erase(it);
				return true;
			}
		}
		return false;
	}

	bool PlayerIsVoipMuted(std::string uid) // 0x106B6A70
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?PlayerIsVoipMuted@PersistentMemory@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x106B6BA4
		// static ...; // 0x106B6B98
		// static ...; // 0x106B6B90
		// std::string uid;
			// std::_Vector_iterator<std::_Vector_val<std::_Simple_types<PersistentMemory::SPersistentMemoryDB::SPersistantMute> > > it;

		for (std::vector<PersistentMemory::SPersistentMemoryDB::SPersistantMute>::iterator it = persistentMemoryDB.mutedVoipPlayers.begin(); it != persistentMemoryDB.mutedVoipPlayers.end(); ++it)
		{
			if (it->player_uid == uid)
				return true;
		}
		return false;
	}
}

/* ---------- private code */

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace PersistentMemory { std::string persistentMemoryPath; }
