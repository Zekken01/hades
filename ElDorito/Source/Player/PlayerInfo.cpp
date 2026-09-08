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
		__int32 rank; // 0x0
		__int32 skill; // 0x4
		std::string emblemUrl; // 0x8
		bool rankup; // 0x24
		bool set; // 0x25
		SPlayerInfo(SPlayerInfo &); /* compiler_generated() */
		SPlayerInfo(SPlayerInfo const &); /* compiler_generated() */
		SPlayerInfo(); /* compiler_generated() */
		~SPlayerInfo(); /* compiler_generated() */
		SPlayerInfo &operator=(SPlayerInfo &); /* compiler_generated() */
		SPlayerInfo &operator=(SPlayerInfo const &); /* compiler_generated() */
		unsigned char __pad0[2]; // 0x26
	};
	static_assert(sizeof(SPlayerInfo) == 40, "Invalid SPlayerInfo size");

	struct SPlayerEmblemInfo
	{
		std::string emblemUrl; // 0x0
		unsigned char __pad0[4]; // 0x1C
		unsigned long long uid; // 0x20
		SPlayerEmblemInfo(SPlayerEmblemInfo &); /* compiler_generated() */
		SPlayerEmblemInfo(SPlayerEmblemInfo const &); /* compiler_generated() */
		SPlayerEmblemInfo(); /* compiler_generated() */
		~SPlayerEmblemInfo(); /* compiler_generated() */
		SPlayerEmblemInfo &operator=(SPlayerEmblemInfo &); /* compiler_generated() */
		SPlayerEmblemInfo &operator=(SPlayerEmblemInfo const &); /* compiler_generated() */
	};
	static_assert(sizeof(SPlayerEmblemInfo) == 40, "Invalid SPlayerEmblemInfo size");
}
using namespace hades_file_local;
/* ---------- prototypes */

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

/* ---------- private variables */

namespace hades_file_local
{
	extern bool isAvailable; // 0x1138F2C8
	extern long long checkRankTime; // 0x1138F2D0
	extern bool rankCheckGameStarted; // 0x1138F2C9
	extern bool rankCheckGameEnded; // 0x1138F2CA
}
using namespace hades_file_local;
/* ---------- public code */

namespace Player
{
	_extern bool _sub_107EE670();
	bool CPlayersInfo::IsAvailable() // 0x107EE670
	{
		mangled_x86(MANGLED_TODO, "?IsAvailable@CPlayersInfo@Player@@SA_NXZ");
		// procedure flags: nofpo
		todo("implement");
		bool __result = _sub_107EE670();
		return __result;
	}

	_extern bool _sub_107EE500();
	bool GetRankedUpRecently() // 0x107EE500
	{
		mangled_x86(MANGLED_TODO, "?GetRankedUpRecently@Player@@YA_NXZ");
		// procedure flags: nofpo
		// __int32 localPeer;
		// __int32 localPlayerIdx;
		todo("implement");
		bool __result = _sub_107EE500();
		return __result;
	}
}

extern std::string _sub_107EE0C0();
namespace Player
{
	std::string CPlayersInfo::GeneratePlayerInfo() // 0x107EE0C0
	{
		mangled_x86(MANGLED_TODO, "?GeneratePlayerInfo@CPlayersInfo@Player@@SA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// procedure flags: nofpo
		// static ...; // 0x107EE3B3
		// static ...; // 0x107EE3A8
		// static ...; // 0x107EE3A0
		// static ...; // 0x107EE39C
		// static ...; // 0x107EE36C
		// static ...; // 0x107EE364
		// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
		// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
		{
			// __int32 i;
			{
				// char uid[17];
				// s_network_session_player *networkPlayer;
				// c_network_session *session;
				// bool validIndex;
			}
		}
		// function call : bool (*const)(c_network_session **)
		todo("implement");
		std::string __result = _sub_107EE0C0();
		return __result;
	}

	_extern void _sub_107EDE50();
	void ClearRankUp() // 0x107EDE50
	{
		mangled_x86(MANGLED_TODO, "?ClearRankUp@Player@@YAXXZ");
		// procedure flags: nofpo
		{
			// __int32 i;
		}
		todo("implement");
		_sub_107EDE50();
	}

	_extern __int32 _sub_107EE480(__int32);
	__int32 CPlayersInfo::GetRank(__int32 networkPlayerIndex) // 0x107EE480
	{
		mangled_x86(MANGLED_TODO, "?GetRank@CPlayersInfo@Player@@SAHH@Z");
		// __int32 networkPlayerIndex;
		todo("implement");
		__int32 __result = _sub_107EE480(networkPlayerIndex);
		return __result;
	}

	_extern __int32 _sub_107EE590(__int32);
	__int32 CPlayersInfo::GetSkill(__int32 networkPlayerIndex) // 0x107EE590
	{
		mangled_x86(MANGLED_TODO, "?GetSkill@CPlayersInfo@Player@@SAHH@Z");
		// __int32 networkPlayerIndex;
		todo("implement");
		__int32 __result = _sub_107EE590(networkPlayerIndex);
		return __result;
	}
}

extern std::string _sub_107EF4E0(__int32);
namespace Player
{
	std::string getLocalEmblem(__int32 networkPlayerIndex) // 0x107EF4E0
	{
		mangled_x86(MANGLED_TODO, "?getLocalEmblem@Player@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z");
		// static ...; // 0x107EF723
		// static ...; // 0x107EF718
		// static ...; // 0x107EF700
		// static ...; // 0x107EF6F8
		// __int32 networkPlayerIndex;
		// s_player_emblem_configuration emblem_cfg;
		// s_network_session_player *networkPlayer;
		// c_network_session *session;
		// function call : bool (*const)(c_network_session **)
		todo("implement");
		std::string __result = _sub_107EF4E0(networkPlayerIndex);
		return __result;
	}
}

extern std::string _sub_107EDEA0(__int32);
namespace Player
{
	std::string CPlayersInfo::GeEmblemUrl(__int32 networkPlayerIndex) // 0x107EDEA0
	{
		mangled_x86(MANGLED_TODO, "?GeEmblemUrl@CPlayersInfo@Player@@SA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z");
		// static ...; // 0x107EE044
		// static ...; // 0x107EE038
		// static ...; // 0x107EE030
		// __int32 networkPlayerIndex;
		// SPlayerInfo cached;
		todo("implement");
		std::string __result = _sub_107EDEA0(networkPlayerIndex);
		return __result;
	}

	_extern void _sub_107EE980(std::string const &);
	void CPlayersInfo::Update(std::string const &payload) // 0x107EE980
	{
		mangled_x86(MANGLED_TODO, "?Update@CPlayersInfo@Player@@SAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x107EEE54
		// static ...; // 0x107EEE50
		// static ...; // 0x107EEE38
		// static ...; // 0x107EEE30
		// std::string const &payload;
		// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
		{
			// __int32 i;
			{
				// std::string key;
				{
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &info;
					{
						// bool rankUp;
					}
					{
						// __int32 rank;
					}
					{
						// __int32 skill;
					}
				}
			}
		}
		todo("implement");
		_sub_107EE980(payload);
	}

	_extern void _sub_107EE690(Blam::Network::LifeCycleState);
	void LifeCycleStateChanged(Blam::Network::LifeCycleState newState) // 0x107EE690
	{
		mangled_x86(MANGLED_TODO, "?LifeCycleStateChanged@Player@@YAXW4LifeCycleState@Network@Blam@@@Z");
		// Blam::Network::LifeCycleState newState;
		// Blam::Network::Session *session;
		todo("implement");
		_sub_107EE690(newState);
	}

	_extern void _sub_107EE610();
	void CPlayersInfo::Init() // 0x107EE610
	{
		mangled_x86(MANGLED_TODO, "?Init@CPlayersInfo@Player@@SAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_107EE610();
	}

	_extern void _sub_107EE750();
	void CPlayersInfo::Tick() // 0x107EE750
	{
		mangled_x86(MANGLED_TODO, "?Tick@CPlayersInfo@Player@@SAXXZ");
		// procedure flags: nofpo
		// static ...; // 0x107EE900
		// static ...; // 0x107EE8F4
		// static ...; // 0x107EE8EC
		// static bool (*IsMapLoading)(); // 0x113525C8
		// long long curTime1;
		// Blam::Network::Session *session;
		{
			// long long elapsed;
		}
		// function call : bool (*)()
		// function call : bool (*const)()
		todo("implement");
		_sub_107EE750();
	}
}

/* ---------- private code */

_extern bool _sub_107EEF90(__int32);
bool ValidNetworkPlayerIndex(__int32 networkPlayerIndex) // 0x107EEF90
{
	// `anonymous-namespace'::ValidNetworkPlayerIndex
	// __int32 networkPlayerIndex;
	todo("implement");
	bool __result = _sub_107EEF90(networkPlayerIndex);
	return __result;
}

_extern void _sub_107EDCB0();
void ClearCache() // 0x107EDCB0
{
	// `anonymous-namespace'::ClearCache
	// procedure flags: nofpo
	{
		// __int32 i;
	}
	todo("implement");
	_sub_107EDCB0();
}

_extern void _sub_107EDD90();
void ClearEmblemCache() // 0x107EDD90
{
	// `anonymous-namespace'::ClearEmblemCache
	// procedure flags: nofpo
	{
		// __int32 i;
	}
	todo("implement");
	_sub_107EDD90();
}

_inline SPlayerEmblemInfo::SPlayerEmblemInfo() // 0x107ED930
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SPlayerEmblemInfo@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::SPlayerEmblemInfo::SPlayerEmblemInfo
	// SPlayerEmblemInfo *const this;

	compiler_generated();
}

_inline SPlayerInfo::SPlayerInfo(SPlayerInfo const &__that) // 0x107ED980
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SPlayerInfo@hades_file_local@@QAE@ABU01@@Z");
	// `anonymous-namespace'::SPlayerInfo::SPlayerInfo
	// SPlayerInfo const &__that;

	compiler_generated();
}

_inline SPlayerInfo::SPlayerInfo() // 0x107EDA30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SPlayerInfo@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::SPlayerInfo::SPlayerInfo
	// SPlayerInfo *const this;

	compiler_generated();
}

_inline SPlayerEmblemInfo::~SPlayerEmblemInfo() // 0x107EDB00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1SPlayerEmblemInfo@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::SPlayerEmblemInfo::~SPlayerEmblemInfo
	// SPlayerEmblemInfo *const this;

	compiler_generated();
}

_inline SPlayerInfo::~SPlayerInfo() // 0x107EDB50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1SPlayerInfo@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::SPlayerInfo::~SPlayerInfo
	// SPlayerInfo *const this;

	compiler_generated();
}

extern SPlayerEmblemInfo &_sub_107EDBA0(SPlayerEmblemInfo *const, SPlayerEmblemInfo &);
_inline SPlayerEmblemInfo &SPlayerEmblemInfo::operator=(SPlayerEmblemInfo &__that) // 0x107EDBA0
{
	// `anonymous-namespace'::SPlayerEmblemInfo::operator=
	// SPlayerEmblemInfo &__that;
	compiler_generated();
	todo("implement");
	SPlayerEmblemInfo & __result = _sub_107EDBA0(this, __that);
	return __result;
}

extern SPlayerInfo &_sub_107EDC10(SPlayerInfo *const, SPlayerInfo &);
_inline SPlayerInfo &SPlayerInfo::operator=(SPlayerInfo &__that) // 0x107EDC10
{
	// `anonymous-namespace'::SPlayerInfo::operator=
	// SPlayerInfo &__that;
	compiler_generated();
	todo("implement");
	SPlayerInfo & __result = _sub_107EDC10(this, __that);
	return __result;
}
