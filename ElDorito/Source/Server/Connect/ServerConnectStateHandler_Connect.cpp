/* ---------- headers */

#include "Server/Connect/ServerConnectStateHandler_Connect.hpp"
#include "hades/hades.h"

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
#include "Blam/networking/logic/network_join.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/networking/transport/transport.hpp"
#include "Blam/networking/transport/transport_shim.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Console/Console.hpp"
#include "Discord/DiscordRPC.h"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Pointer.hpp"
#include "Server/Connect/ServerConnectDefintiions.hpp"
#include "Server/Connect/ServerConnectStateManager.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "Utils/Singleton.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/Ui/ScreenLayer.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
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
#include <variant>

/* ---------- forward declarations */

class CServerConnectStateHandler_Connect;
struct SServerConnectState;
struct lambda_1;
struct s_network_session_remote_join_data;
struct s_transport_address;
struct s_xnet_shim_table_row;
namespace Discord
{
	class DiscordRPC;
}
namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer
		{
			struct SDialogShowParams;
		}
	}
}

namespace Utils {}
using namespace ::Utils;
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

namespace Console {}
using namespace ::Console;

/* ---------- constants */

/* ---------- definitions */

//class CServerConnectStateHandler_Connect::OnEnter::__l2::<lambda_1>
//{
//public:
//	void operator()(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &) const;
//};
//static_assert(sizeof(CServerConnectStateHandler_Connect::OnEnter::__l2::<lambda_1>) == 1, "Invalid CServerConnectStateHandler_Connect::OnEnter::__l2::<lambda_1> size");

/* ---------- prototypes */

/* ---------- globals */

extern s_xnet_shim_table_row *g_xnet_shim_table; // 0x113530CC
namespace Utils
{
	Discord::DiscordRPC *Utils::Singleton<Discord::DiscordRPC>::m_instance; // 0x12409268
}

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_1090BE70(CServerConnectStateHandler_Connect *const);
void CServerConnectStateHandler_Connect::OnEnter() // 0x1090BE70
{
	mangled_x86(MANGLED_TODO, "?OnEnter@CServerConnectStateHandler_Connect@@EAEXXZ");
	// static ...; // 0x1090C203
	// static ...; // 0x1090C1EF
	// static ...; // 0x1090C1E8
	// static ...; // 0x1090C1C4
	// static ...; // 0x1090C1BC
	// CServerConnectStateHandler_Connect *const this;
	// Web::Ui::ScreenLayer::SDialogShowParams params;
	// s_transport_address inaddr;
	// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > discordStringStream;
	// SServerConnectState const &state;
	// s_network_session_remote_join_data *join_data;
	// function call : void (*const)()
	// function call : void (*const)(s_transport_address const *, void const *, void const *)
	// function call : unsigned long long (*const)()
	todo("implement");
	_sub_1090BE70(this);
}

_extern void _sub_1090C2F0(CServerConnectStateHandler_Connect *const);
void CServerConnectStateHandler_Connect::OnExit() // 0x1090C2F0
{
	mangled_x86(MANGLED_TODO, "?OnExit@CServerConnectStateHandler_Connect@@EAEXXZ");
	// CServerConnectStateHandler_Connect *const this;
	todo("implement");
	_sub_1090C2F0(this);
}

_extern void _sub_1090C310(CServerConnectStateHandler_Connect *const);
void CServerConnectStateHandler_Connect::OnUpdate() // 0x1090C310
{
	mangled_x86(MANGLED_TODO, "?OnUpdate@CServerConnectStateHandler_Connect@@EAEXXZ");
	// CServerConnectStateHandler_Connect *const this;
	todo("implement");
	_sub_1090C310(this);
}

/* ---------- private code */
