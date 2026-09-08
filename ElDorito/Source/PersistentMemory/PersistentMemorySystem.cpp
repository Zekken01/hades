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
	extern bool Load(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &filename);
	extern void Save();
	extern void Init();
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetLastAnnoucementViewedDate();
	extern void SetLastAnnoucementViewedDate(std::basic_string<char,std::char_traits<char>,std::allocator<char> > annoucementViewedDate);
	extern __int32 GetLastMapID();
	extern void SetLastMapID(__int32 mapID);
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetLastMapName();
	extern void SetLastMapName(std::basic_string<char,std::char_traits<char>,std::allocator<char> > mapName);
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetLastGameType();
	extern void SetLastGameType(std::basic_string<char,std::char_traits<char>,std::allocator<char> > gameType);
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetLastMultiplayerMod();
	extern void SetLastMultiplayerMod(std::basic_string<char,std::char_traits<char>,std::allocator<char> > multiplayerMod);
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetLastCampaignMod();
	extern void SetLastCampaignMod(std::basic_string<char,std::char_traits<char>,std::allocator<char> > campaignMod);
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetLastFirefightMod();
	extern void SetLastFirefightMod(std::basic_string<char,std::char_traits<char>,std::allocator<char> > firefightMod);
	extern void AddMutedVoipPlayer(std::basic_string<char,std::char_traits<char>,std::allocator<char> > name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > uid);
	extern bool RemoveMutedVoipPlayer(std::basic_string<char,std::char_traits<char>,std::allocator<char> > uid);
	extern bool PlayerIsVoipMuted(std::basic_string<char,std::char_traits<char>,std::allocator<char> > uid);
}

/* ---------- globals */

namespace PersistentMemory
{
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > persistentMemoryPath; // 0x11386164
	extern PersistentMemory::SPersistentMemoryDB persistentMemoryDB; // 0x113860A8
}

/* ---------- private variables */

/* ---------- public code */

namespace PersistentMemory
{
	extern SPersistentMemoryDB _sub_106B58F0(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &);
	PersistentMemory::SPersistentMemoryDB LoadPersistentMemory(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &value) // 0x106B58F0
	{
		mangled_x86(MANGLED_TODO, "?LoadPersistentMemory@PersistentMemory@@YA?AUSPersistentMemoryDB@1@AAV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@@Z");
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
		{
			// char const *const &lastAnnoucementViewedDate;
		}
		{
			// __int32 const &lastMapID;
		}
		{
			// char const *const &lastMapName;
		}
		{
			// char const *const &lastGameType;
		}
		{
			// char const *const &lastMultiplayerMod;
		}
		{
			// char const *const &lastCampaignMod;
		}
		{
			// char const *const &lastFirefightMod;
		}
		{
			// rapidjson::GenericArray<0,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > const &mutedVoipPlayers;
			{
				// rapidjson::GenericArray<0,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > const &<range>$L0;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > *<begin>$L0;
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > *<end>$L0;
				{
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &player;
					{
						// char const *const &uid;
						// PersistentMemory::SPersistentMemoryDB::SPersistantMute new_player;
						// char const *const &name;
					}
				}
			}
		}
		todo("implement");
		PersistentMemory::SPersistentMemoryDB __result = _sub_106B58F0(value);
		return __result;
	}

	_inline SPersistentMemoryDB::SPersistantMute::SPersistantMute(PersistentMemory::SPersistentMemoryDB::SPersistantMute &&__that) // 0x106AF9A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0SPersistantMute@SPersistentMemoryDB@PersistentMemory@@QAE@$$QAU012@@Z");
		// PersistentMemory::SPersistentMemoryDB::SPersistantMute &__that;

		compiler_generated();
	}

	_inline SPersistentMemoryDB::SPersistantMute::SPersistantMute(PersistentMemory::SPersistentMemoryDB::SPersistantMute const &__that) // 0x106AFA30
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0SPersistantMute@SPersistentMemoryDB@PersistentMemory@@QAE@ABU012@@Z");
		// PersistentMemory::SPersistentMemoryDB::SPersistantMute const &__that;

		compiler_generated();
	}

	_inline SPersistentMemoryDB::SPersistentMemoryDB(PersistentMemory::SPersistentMemoryDB &&__that) // 0x106AFB00
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0SPersistentMemoryDB@PersistentMemory@@QAE@$$QAU01@@Z");
		// PersistentMemory::SPersistentMemoryDB &__that;

		compiler_generated();
	}

	_inline SPersistentMemoryDB::SPersistentMemoryDB() // 0x106AFC70
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0SPersistentMemoryDB@PersistentMemory@@QAE@XZ");
		// PersistentMemory::SPersistentMemoryDB *const this;

		compiler_generated();
	}

	_extern bool _sub_106B5600(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
	bool Load(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &filename) // 0x106B5600
	{
		mangled_x86(MANGLED_TODO, "?Load@PersistentMemory@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x106B5850
		// static ...; // 0x106B584C
		// static ...; // 0x106B5848
		// static ...; // 0x106B5824
		// static ...; // 0x106B581C
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &filename;
		// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> doc;
		// std::basic_ifstream<char,std::char_traits<char> > stream;
		// rapidjson::BasicIStreamWrapper<std::basic_istream<char,std::char_traits<char> > > isw;
		todo("implement");
		bool __result = _sub_106B5600(filename);
		return __result;
	}

	_inline SPersistentMemoryDB::SPersistantMute::~SPersistantMute() // 0x106B0E30
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??1SPersistantMute@SPersistentMemoryDB@PersistentMemory@@QAE@XZ");
		// PersistentMemory::SPersistentMemoryDB::SPersistantMute *const this;

		compiler_generated();
	}

	_inline SPersistentMemoryDB::~SPersistentMemoryDB() // 0x106B0E90
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??1SPersistentMemoryDB@PersistentMemory@@QAE@XZ");
		// PersistentMemory::SPersistentMemoryDB *const this;

		compiler_generated();
	}

	extern SPersistentMemoryDB::SPersistantMute &_sub_106B1300(PersistentMemory::SPersistentMemoryDB::SPersistantMute *const, PersistentMemory::SPersistentMemoryDB::SPersistantMute &);
	_inline PersistentMemory::SPersistentMemoryDB::SPersistantMute &SPersistentMemoryDB::SPersistantMute::operator=(PersistentMemory::SPersistentMemoryDB::SPersistantMute &&__that) // 0x106B1300
	{
		mangled_x86(MANGLED_TODO, "??4SPersistantMute@SPersistentMemoryDB@PersistentMemory@@QAEAAU012@$$QAU012@@Z");
		// PersistentMemory::SPersistentMemoryDB::SPersistantMute &__that;
		compiler_generated();
		todo("implement");
		PersistentMemory::SPersistentMemoryDB::SPersistantMute & __result = _sub_106B1300(this, __that);
		return __result;
	}

	extern SPersistentMemoryDB &_sub_106B1370(PersistentMemory::SPersistentMemoryDB *const, PersistentMemory::SPersistentMemoryDB &);
	_inline PersistentMemory::SPersistentMemoryDB &SPersistentMemoryDB::operator=(PersistentMemory::SPersistentMemoryDB &&__that) // 0x106B1370
	{
		mangled_x86(MANGLED_TODO, "??4SPersistentMemoryDB@PersistentMemory@@QAEAAU01@$$QAU01@@Z");
		// PersistentMemory::SPersistentMemoryDB &__that;
		compiler_generated();
		todo("implement");
		PersistentMemory::SPersistentMemoryDB & __result = _sub_106B1370(this, __that);
		return __result;
	}

	_extern void _sub_106B75E0();
	void Save() // 0x106B75E0
	{
		mangled_x86(MANGLED_TODO, "?Save@PersistentMemory@@YAXXZ");
		// procedure flags: nofpo
		// static ...; // 0x106B7963
		// static ...; // 0x106B795F
		// static ...; // 0x106B7958
		// static ...; // 0x106B7934
		// static ...; // 0x106B792C
		// rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::basic_ostream<char,std::char_traits<char> > >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
		// std::basic_ofstream<char,std::char_traits<char> > stream;
		// rapidjson::BasicOStreamWrapper<std::basic_ostream<char,std::char_traits<char> > > isw;
		{
			// std::vector<PersistentMemory::SPersistentMemoryDB::SPersistantMute,std::allocator<PersistentMemory::SPersistentMemoryDB::SPersistantMute> > &<range>$L0;
			// PersistentMemory::SPersistentMemoryDB::SPersistantMute *<begin>$L0;
			// PersistentMemory::SPersistentMemoryDB::SPersistantMute *<end>$L0;
			{
				// PersistentMemory::SPersistentMemoryDB::SPersistantMute const &player;
			}
		}
		todo("implement");
		_sub_106B75E0();
	}

	_extern void _sub_106B4BC0();
	void Init() // 0x106B4BC0
	{
		mangled_x86(MANGLED_TODO, "?Init@PersistentMemory@@YAXXZ");
		// procedure flags: nofpo
		// static ...; // 0x106B4E53
		// static ...; // 0x106B4E50
		// static ...; // 0x106B4E38
		// static ...; // 0x106B4E30
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > prefsName;
		{
			// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
		}
		todo("implement");
		_sub_106B4BC0();
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_106B4570();
namespace PersistentMemory
{
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetLastAnnoucementViewedDate() // 0x106B4570
	{
		mangled_x86(MANGLED_TODO, "?GetLastAnnoucementViewedDate@PersistentMemory@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// procedure flags: nofpo
		todo("implement");
		std::string __result = _sub_106B4570();
		return __result;
	}

	_extern void _sub_106B7C00(std::string);
	void SetLastAnnoucementViewedDate(std::basic_string<char,std::char_traits<char>,std::allocator<char> > annoucementViewedDate) // 0x106B7C00
	{
		mangled_x86(MANGLED_TODO, "?SetLastAnnoucementViewedDate@PersistentMemory@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > annoucementViewedDate;
		todo("implement");
		_sub_106B7C00(annoucementViewedDate);
	}

	_extern __int32 _sub_106B4730();
	__int32 GetLastMapID() // 0x106B4730
	{
		mangled_x86(MANGLED_TODO, "?GetLastMapID@PersistentMemory@@YAHXZ");
		// procedure flags: nofpo
		todo("implement");
		__int32 __result = _sub_106B4730();
		return __result;
	}

	_extern void _sub_106B7E80(__int32);
	void SetLastMapID(__int32 mapID) // 0x106B7E80
	{
		mangled_x86(MANGLED_TODO, "?SetLastMapID@PersistentMemory@@YAXH@Z");
		// __int32 mapID;
		todo("implement");
		_sub_106B7E80(mapID);
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_106B4750();
namespace PersistentMemory
{
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetLastMapName() // 0x106B4750
	{
		mangled_x86(MANGLED_TODO, "?GetLastMapName@PersistentMemory@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// procedure flags: nofpo
		todo("implement");
		std::string __result = _sub_106B4750();
		return __result;
	}

	_extern void _sub_106B7EB0(std::string);
	void SetLastMapName(std::basic_string<char,std::char_traits<char>,std::allocator<char> > mapName) // 0x106B7EB0
	{
		mangled_x86(MANGLED_TODO, "?SetLastMapName@PersistentMemory@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > mapName;
		todo("implement");
		_sub_106B7EB0(mapName);
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_106B46C0();
namespace PersistentMemory
{
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetLastGameType() // 0x106B46C0
	{
		mangled_x86(MANGLED_TODO, "?GetLastGameType@PersistentMemory@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// procedure flags: nofpo
		todo("implement");
		std::string __result = _sub_106B46C0();
		return __result;
	}

	_extern void _sub_106B7DE0(std::string);
	void SetLastGameType(std::basic_string<char,std::char_traits<char>,std::allocator<char> > gameType) // 0x106B7DE0
	{
		mangled_x86(MANGLED_TODO, "?SetLastGameType@PersistentMemory@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > gameType;
		todo("implement");
		_sub_106B7DE0(gameType);
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_106B47C0();
namespace PersistentMemory
{
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetLastMultiplayerMod() // 0x106B47C0
	{
		mangled_x86(MANGLED_TODO, "?GetLastMultiplayerMod@PersistentMemory@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// procedure flags: nofpo
		todo("implement");
		std::string __result = _sub_106B47C0();
		return __result;
	}

	_extern void _sub_106B7F50(std::string);
	void SetLastMultiplayerMod(std::basic_string<char,std::char_traits<char>,std::allocator<char> > multiplayerMod) // 0x106B7F50
	{
		mangled_x86(MANGLED_TODO, "?SetLastMultiplayerMod@PersistentMemory@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > multiplayerMod;
		todo("implement");
		_sub_106B7F50(multiplayerMod);
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_106B45E0();
namespace PersistentMemory
{
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetLastCampaignMod() // 0x106B45E0
	{
		mangled_x86(MANGLED_TODO, "?GetLastCampaignMod@PersistentMemory@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// procedure flags: nofpo
		todo("implement");
		std::string __result = _sub_106B45E0();
		return __result;
	}

	_extern void _sub_106B7CA0(std::string);
	void SetLastCampaignMod(std::basic_string<char,std::char_traits<char>,std::allocator<char> > campaignMod) // 0x106B7CA0
	{
		mangled_x86(MANGLED_TODO, "?SetLastCampaignMod@PersistentMemory@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > campaignMod;
		todo("implement");
		_sub_106B7CA0(campaignMod);
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_106B4650();
namespace PersistentMemory
{
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetLastFirefightMod() // 0x106B4650
	{
		mangled_x86(MANGLED_TODO, "?GetLastFirefightMod@PersistentMemory@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// procedure flags: nofpo
		todo("implement");
		std::string __result = _sub_106B4650();
		return __result;
	}

	_extern void _sub_106B7D40(std::string);
	void SetLastFirefightMod(std::basic_string<char,std::char_traits<char>,std::allocator<char> > firefightMod) // 0x106B7D40
	{
		mangled_x86(MANGLED_TODO, "?SetLastFirefightMod@PersistentMemory@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > firefightMod;
		todo("implement");
		_sub_106B7D40(firefightMod);
	}

	_extern void _sub_106B2B50(std::string, std::string);
	void AddMutedVoipPlayer(std::basic_string<char,std::char_traits<char>,std::allocator<char> > name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > uid) // 0x106B2B50
	{
		mangled_x86(MANGLED_TODO, "?AddMutedVoipPlayer@PersistentMemory@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
		// static ...; // 0x106B2C2C
		// static ...; // 0x106B2C24
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > name;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > uid;
		// PersistentMemory::SPersistentMemoryDB::SPersistantMute muted;
		todo("implement");
		_sub_106B2B50(name, uid);
	}

	_extern bool _sub_106B7410(std::string);
	bool RemoveMutedVoipPlayer(std::basic_string<char,std::char_traits<char>,std::allocator<char> > uid) // 0x106B7410
	{
		mangled_x86(MANGLED_TODO, "?RemoveMutedVoipPlayer@PersistentMemory@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x106B7578
		// static ...; // 0x106B756C
		// static ...; // 0x106B7564
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > uid;
		{
			// std::_Vector_iterator<std::_Vector_val<std::_Simple_types<PersistentMemory::SPersistentMemoryDB::SPersistantMute> > > it;
		}
		todo("implement");
		bool __result = _sub_106B7410(uid);
		return __result;
	}

	_extern bool _sub_106B6A70(std::string);
	bool PlayerIsVoipMuted(std::basic_string<char,std::char_traits<char>,std::allocator<char> > uid) // 0x106B6A70
	{
		mangled_x86(MANGLED_TODO, "?PlayerIsVoipMuted@PersistentMemory@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x106B6BA4
		// static ...; // 0x106B6B98
		// static ...; // 0x106B6B90
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > uid;
		{
			// std::_Vector_iterator<std::_Vector_val<std::_Simple_types<PersistentMemory::SPersistentMemoryDB::SPersistantMute> > > it;
		}
		todo("implement");
		bool __result = _sub_106B6A70(uid);
		return __result;
	}
}

/* ---------- private code */
