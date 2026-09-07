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
	std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > Subnets; // 0x0
	std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > Names; // 0x10
	std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > Uids; // 0x20
	std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > Ips; // 0x30
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
unsigned long BanListSyncThreadProc(void *lpParam);
void OnShutdown();
bool TryParseSubnet(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &cidr, unsigned long *outNetwork, unsigned long *outMask);

/* ---------- globals */

/* ---------- private variables */

namespace Server
{
	namespace hades_file_local_Server
	{
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > DefaultBanListPath; // 0x12467688
	}
	using namespace hades_file_local_Server;
}
namespace hades_file_local
{
	extern long long lastSyncTime; // 0x124676A8
	extern std::mutex mutex; // 0x12467620
	extern std::condition_variable syncSignal; // 0x12467660
	extern bool shouldExit; // 0x124676A4
	extern bool banlistDirty; // 0x124676A5
	extern std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > banlistUrls; // 0x12467650
}
using namespace hades_file_local;
/* ---------- public code */

namespace Server
{
	namespace BanListSync
	{
		_extern void _sub_10B18E20();
		void Init() // 0x10B18E20
		{
			mangled_x86(MANGLED_TODO, "?Init@BanListSync@Server@@YAXXZ");
			// procedure flags: nofpo
			// function call : void *(_SECURITY_ATTRIBUTES *, unsigned long, unsigned long (*)(void *), void *, unsigned long, unsigned long *)
			todo("implement");
			_sub_10B18E20();
		}

		_extern void _sub_10B199C0();
		void Tick() // 0x10B199C0
		{
			mangled_x86(MANGLED_TODO, "?Tick@BanListSync@Server@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10B19DBD
			// static ...; // 0x10B19DB5
			// static ...; // 0x10B19DB0
			// static ...; // 0x10B19DAC
			// static ...; // 0x10B19D7C
			// static ...; // 0x10B19D74
			// unsigned long syncInternval;
			// Blam::Network::Session *session;
			// long long now;
			{
				// std::unique_lock<std::mutex> lock;
				{
					// Server::StatsServersBanList &statsserverBanList;
					{
						// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &<range>$L0;
						// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<begin>$L0;
						// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<end>$L0;
						{
							// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &ip;
						}
					}
					{
						// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<end>$L1;
						// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<begin>$L1;
						// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &<range>$L1;
						{
							// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &uid;
						}
					}
					{
						// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<end>$L2;
						// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &<range>$L2;
						// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<begin>$L2;
						{
							// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name;
						}
					}
					{
						// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &<range>$L3;
						// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<begin>$L3;
						// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<end>$L3;
						{
							// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &subnet;
							{
								// unsigned long mask;
								// unsigned long network;
							}
						}
					}
				}
			}
			todo("implement");
			_sub_10B199C0();
		}
	}
}

/* ---------- private code */

_extern bool _sub_10B18BA0();
bool GetEndpoints() // 0x10B18BA0
{
	// `anonymous-namespace'::GetEndpoints
	// procedure flags: nofpo
	// static ...; // 0x10B18D94
	// static ...; // 0x10B18D88
	// static ...; // 0x10B18D80
	// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
	{
		// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &urls;
		{
			// unsigned __int32 i;
		}
	}
	todo("implement");
	bool __result = _sub_10B18BA0();
	return __result;
}

extern s_sharedState* _sub_10B17D40(s_sharedState *const);
_inline s_sharedState::s_sharedState() // 0x10B17D40
{
	// `anonymous-namespace'::<unnamed-type-sharedState>::<unnamed-type-sharedState>
	// s_sharedState *const this;
	compiler_generated();
	todo("implement");
	_sub_10B17D40(this);
}

_extern void _sub_10B17E80(s_sharedState *const);
_inline s_sharedState::~s_sharedState() // 0x10B17E80
{
	// `anonymous-namespace'::<unnamed-type-sharedState>::~<unnamed-type-sharedState>
	// s_sharedState *const this;
	compiler_generated();
	todo("implement");
	_sub_10B17E80(this);
}

_extern void _sub_10B183A0();
void CheckToBootPlayers() // 0x10B183A0
{
	// `anonymous-namespace'::CheckToBootPlayers
	// procedure flags: nofpo
	// static ...; // 0x10B188CF
	// static ...; // 0x10B188C8
	// static ...; // 0x10B188C1
	// static ...; // 0x10B188BC
	// static ...; // 0x10B1888C
	// static ...; // 0x10B18884
	// Blam::Network::Session *session;
	// __int32 peerIdx;
	{
		// __int32 playerIdx;
		{
			// Blam::Network::PlayerSession *player;
			// unsigned long long uid;
			// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > stream;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &ipString;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > name;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > hexUID;
		}
	}
	todo("implement");
	_sub_10B183A0();
}

_extern bool _sub_10B18F00();
bool SyncBanList() // 0x10B18F00
{
	// `anonymous-namespace'::SyncBanList
	// procedure flags: nofpo
	// static ...; // 0x10B1978B
	// static ...; // 0x10B19782
	// static ...; // 0x10B1977D
	// static ...; // 0x10B19778
	// static ...; // 0x10B19748
	// static ...; // 0x10B19740
	{
		// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &<range>$L0;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<begin>$L0;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<end>$L0;
		{
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &endpoint;
			{
				// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
				// std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > expected;
				// HttpRequest req;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > resp;
				{
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &IPs;
					{
						// unsigned __int32 i;
					}
				}
				{
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &UIDs;
					{
					}
				}
				{
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &Names;
					{
					}
				}
				{
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &Subnets;
					{
					}
				}
			}
		}
	}
	todo("implement");
	bool __result = _sub_10B18F00();
	return __result;
}

_extern unsigned long _sub_10B18260(void *);
unsigned long BanListSyncThreadProc(void *lpParam) // 0x10B18260
{
	// `anonymous-namespace'::BanListSyncThreadProc
	// static ...; // 0x10B18354
	// static ...; // 0x10B18348
	// static ...; // 0x10B18340
	// void *lpParam;
	{
		// std::unique_lock<std::mutex> lk;
	}
	todo("implement");
	unsigned long __result = _sub_10B18260(lpParam);
	return __result;
}

_extern void _sub_10B18EB0();
void OnShutdown() // 0x10B18EB0
{
	// `anonymous-namespace'::OnShutdown
	// procedure flags: nofpo
	todo("implement");
	_sub_10B18EB0();
}

_extern bool _sub_10B19ED0(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, unsigned long *, unsigned long *);
bool TryParseSubnet(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &cidr, unsigned long *outNetwork, unsigned long *outMask) // 0x10B19ED0
{
	// `anonymous-namespace'::TryParseSubnet
	// static ...; // 0x10B1A040
	// static ...; // 0x10B1A038
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &cidr;
	// unsigned long *outNetwork;
	// unsigned long *outMask;
	// __int32 bits;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > snetwork;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > sbits;
	// unsigned __int32 pos;
	todo("implement");
	bool __result = _sub_10B19ED0(cidr, outNetwork, outMask);
	return __result;
}
