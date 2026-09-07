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
#include "Server/BanList.hpp"
#include "Server/StatsServerBanList.hpp"
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

struct begin;
struct end;
struct s_sharedState;
namespace Blam
{
	namespace Network
	{
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

/* ---------- globals */

/* ---------- private variables */

namespace Server
{
	namespace
	{
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > DefaultBanListPath; // 0x12467688
	}
}
namespace
{
	extern long long lastSyncTime; // 0x124676A8
	extern std::mutex mutex; // 0x12467620
	extern std::condition_variable syncSignal; // 0x12467660
	extern bool shouldExit; // 0x124676A4
	extern bool banlistDirty; // 0x124676A5
	extern std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > banlistUrls; // 0x12467650
}
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
