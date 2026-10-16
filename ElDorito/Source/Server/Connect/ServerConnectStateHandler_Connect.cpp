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
//	void operator()(std::string const &) const;
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

void CServerConnectStateHandler_Connect::OnEnter() // 0x1090BE70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnEnter@CServerConnectStateHandler_Connect@@EAEXXZ");

	Console::WriteLine("Server Connect :: Connecting to game server...");
	SServerConnectState const &state = GetManager()->GetState();
	((void(__cdecl *)())0x1596610)();
	s_transport_address inaddr = {};
	inaddr.address.ipv4 = state.address;
	inaddr.address_size = 4;
	inaddr.port = state.gamePort;
	((void(__cdecl *)(s_transport_address *, unsigned char const *, unsigned char const *))0x430CD0)(&inaddr, state.xnaddr, state.xnkid);
	s_network_session_remote_join_data *join_data = (s_network_session_remote_join_data *)0x2240B98;
	join_data->session_class = 1;
	memcpy(&join_data->session_id, state.xnkid, 16);
	memcpy(&join_data->host_secure_address, state.xnaddr, 16);
	join_data->session_key = {};
	join_data->join_nonce = ((unsigned long long(__cdecl *)())0x431010)();
	join_data->platform = 1;
	std::stringstream discordStringStream;
	discordStringStream << state.hostname << ":" << state.port << " " << state.password;
	Utils::Singleton<Discord::DiscordRPC>::Instance().joinString = discordStringStream.str();
	Web::Ui::ScreenLayer::Hide("console");
	Web::Ui::ScreenLayer::SDialogShowParams params;
	params.templateName = "attempting_join";
	params.callback = [](std::string const &) { int unused = 1; };
	Web::Ui::ScreenLayer::ShowDialog(params);
	Complete();
}

void CServerConnectStateHandler_Connect::OnExit() // 0x1090C2F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnExit@CServerConnectStateHandler_Connect@@EAEXXZ");
}

void CServerConnectStateHandler_Connect::OnUpdate() // 0x1090C310
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnUpdate@CServerConnectStateHandler_Connect@@EAEXXZ");
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Discord::DiscordRPC & Utils::Singleton<Discord::DiscordRPC>::Instance();
