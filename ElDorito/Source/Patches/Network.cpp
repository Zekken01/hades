/* ---------- headers */

#include "Patches/Network.hpp"
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
#include "Common/Http/HttpHeaders.hpp"
#include "mods/map_variant_loader.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Pointer.hpp"
#include "Server/BanList.hpp"
#include "Server/StatsServerBanList.hpp"
#include "Server/Voting/VotingPackets.hpp"
#include "Server/Voting/VotingTypes.hpp"
#include "ThirdParty/rapidjson/allocators.h"
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
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"

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
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <initializer_list>
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
#include <unordered_set>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct s_map_variant;
namespace Blam
{
	namespace Network
	{
		struct NetworkAddress;
		struct PeerInfo;
		struct PlayerSession;
		struct Session;
	}
}
namespace Patches
{
	namespace Network
	{
		class NetworkSessionListener;
	}
}
namespace Server
{
	class StatsServersBanList;
}
namespace
{
	struct struc_703;
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
	namespace Signaling {}
	using namespace Server::Signaling;
	namespace InfoServer {}
	using namespace Server::InfoServer;
	namespace Stats {}
	using namespace Server::Stats;
	namespace HsGlobalSync {}
	using namespace Server::HsGlobalSync;
	namespace Voting {}
	using namespace Server::Voting;
}

namespace Modules {}
using namespace ::Modules;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Ui {}
	using namespace Web::Ui;
}

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer {}
		using namespace Web::Ui::ScreenLayer;
	}
}

namespace Web
{
	namespace Browser {}
	using namespace Web::Browser;
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge {}
		using namespace Web::Browser::Bridge;
	}
}

namespace Patches {}
using namespace ::Patches;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

namespace
{
	struct struc_703
	{
		__int32 field_0; // 0x0
		__int32 field_4; // 0x4
		__int32 WindowMin; // 0x8
		__int32 WindowMax; // 0xC
		__int32 field_10; // 0x10
	};
	static_assert(sizeof(struc_703) == 20, "Invalid struc_703 size");
}
namespace Patches
{
	namespace Network
	{
		typedef std::function<void __cdecl(s_map_variant *)> MapVariantRequestChangeCallback;
		typedef std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)> PongCallback;
	}
}

/* ---------- prototypes */

namespace Patches
{
	namespace Network
	{
		extern void ApplyAll();
		extern void ForceDedicated();
		extern void ForceBotClient();
		extern unsigned short OnPong(std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)> callback);
		extern void OnLifeCycleStateChanged(std::function<void __cdecl(enum Blam::Network::LifeCycleState)> callback);
		extern void RegisterSessionListener(std::shared_ptr<Patches::Network::NetworkSessionListener> observer);
		extern void OnMapVariantRequestChange(std::function<void __cdecl(s_map_variant *)> callback);
		extern void Tick();
	}
}

/* ---------- globals */

namespace Utils
{
	Server::StatsServersBanList *Utils::Singleton<Server::StatsServersBanList>::m_instance; // 0x1246460C
}

/* ---------- private variables */

namespace Server
{
	namespace
	{
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > DefaultBanListPath; // 0x12464800
	}
}
namespace
{
	extern std::vector<std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)>,std::allocator<std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)> > > pongCallbacks; // 0x124647E0
	extern std::vector<std::function<void __cdecl(s_map_variant *)>,std::allocator<std::function<void __cdecl(s_map_variant *)> > > mapVariantRequestChangeCallbacks; // 0x124647F0
}
namespace Server
{
	namespace Voting
	{
		namespace
		{
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const DefaultTypes[8]; // 0x12464610
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const DefaultTypeNames[8]; // 0x124646F0
		}
	}
}
namespace
{
	extern std::vector<std::function<void __cdecl(enum Blam::Network::LifeCycleState)>,std::allocator<std::function<void __cdecl(enum Blam::Network::LifeCycleState)> > > lifeCycleStateChangedCallbacks; // 0x124647D0
	extern std::shared_ptr<Patches::Network::NetworkSessionListener> sessionObserver; // 0x1246481C
}
/* ---------- public code */

namespace Patches
{
	namespace Network
	{
		_extern void _sub_10A90670();
		void ApplyAll() // 0x10A90670
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Network@Patches@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10A92B66
			// static ...; // 0x10A92B60
			// static ...; // 0x10A92B56
			// static ...; // 0x10A92B53
			// static ...; // 0x10A92B50
			// static ...; // 0x10A92B14
			// static ...; // 0x10A92B0C
			// unsigned long temp;
			// Pointer writeAddr;
			// unsigned __int32 verNum;
			// unsigned long temp2;
			{
				// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
			}
			{
			}
			// function call : __int32 (void *, unsigned long, unsigned long, unsigned long *)
			// function call : void (char const *)
			// function call : __int32 (void *, unsigned long, unsigned long, unsigned long *)
			// function call : __int32 (void *, unsigned long, unsigned long, unsigned long *)
			// function call : void (char const *)
			// function call : __int32 (void *, unsigned long, unsigned long, unsigned long *)
			todo("implement");
			_sub_10A90670();
		}

		_extern void _sub_10A95310();
		void ForceDedicated() // 0x10A95310
		{
			mangled_x86(MANGLED_TODO, "?ForceDedicated@Network@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A95310();
		}

		_extern void _sub_10A94A20();
		void ForceBotClient() // 0x10A94A20
		{
			mangled_x86(MANGLED_TODO, "?ForceBotClient@Network@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A94A20();
		}

		_extern unsigned short _sub_10A9A490(std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)>);
		unsigned short OnPong(std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)> callback) // 0x10A9A490
		{
			mangled_x86(MANGLED_TODO, "?OnPong@Network@Patches@@YAGV?$function@$$A6AXABUNetworkAddress@Network@Blam@@IGI@Z@std@@@Z");
			// std::function<void __cdecl(Blam::Network::NetworkAddress const &,unsigned int,unsigned short,unsigned int)> callback;
			// static unsigned short id; // 0x12464824
			todo("implement");
			unsigned short __result = _sub_10A9A490(callback);
			return __result;
		}

		_extern void _sub_10A9A350(std::function<void __cdecl(enum Blam::Network::LifeCycleState)>);
		void OnLifeCycleStateChanged(std::function<void __cdecl(enum Blam::Network::LifeCycleState)> callback) // 0x10A9A350
		{
			mangled_x86(MANGLED_TODO, "?OnLifeCycleStateChanged@Network@Patches@@YAXV?$function@$$A6AXW4LifeCycleState@Network@Blam@@@Z@std@@@Z");
			// std::function<void __cdecl(enum Blam::Network::LifeCycleState)> callback;
			todo("implement");
			_sub_10A9A350(callback);
		}

		_extern void _sub_10A9AB60(std::shared_ptr<Patches::Network::NetworkSessionListener>);
		void RegisterSessionListener(std::shared_ptr<Patches::Network::NetworkSessionListener> observer) // 0x10A9AB60
		{
			mangled_x86(MANGLED_TODO, "?RegisterSessionListener@Network@Patches@@YAXV?$shared_ptr@VNetworkSessionListener@Network@Patches@@@std@@@Z");
			// std::shared_ptr<Patches::Network::NetworkSessionListener> observer;
			todo("implement");
			_sub_10A9AB60(observer);
		}

		_extern void _sub_10A9A3F0(std::function<void __cdecl(s_map_variant *)>);
		void OnMapVariantRequestChange(std::function<void __cdecl(s_map_variant *)> callback) // 0x10A9A3F0
		{
			mangled_x86(MANGLED_TODO, "?OnMapVariantRequestChange@Network@Patches@@YAXV?$function@$$A6AXPAUs_map_variant@@@Z@std@@@Z");
			// std::function<void __cdecl(s_map_variant *)> callback;
			todo("implement");
			_sub_10A9A3F0(callback);
		}

		_extern void _sub_10A9B020();
		void Tick() // 0x10A9B020
		{
			mangled_x86(MANGLED_TODO, "?Tick@Network@Patches@@YAXXZ");
			// procedure flags: nofpo
			// Blam::Network::Session *session;
			{
				// __int32 i;
				{
					// Blam::Network::PlayerSession *player;
					// Blam::Network::PeerInfo *peer;
					// __int32 peerIndex;
				}
			}
			todo("implement");
			_sub_10A9B020();
		}
	}
}

/* ---------- private code */
