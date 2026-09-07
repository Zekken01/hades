/* ---------- headers */

#include "hades/hades.h"

#include "Blam/main/levels.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Console/Console.hpp"
#include "ElDorito.hpp"
#include "Forge/Magnets.hpp"
#include "Patches/Network.hpp"
#include "Pointer.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Utils/Uri.hpp"
#include "Utils/WebSocket.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/bind/bind.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/numeric/conversion/converter_policies.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/regex/v5/match_flags.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/system/errc.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/throw_exception.hpp>
#include <boost/winapi/error_handling.hpp>
#include <websocketpp/base64/base64.hpp>
#include <websocketpp/close.hpp>
#include <websocketpp/common/asio.hpp>
#include <websocketpp/common/md5.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/connection.hpp>
#include <websocketpp/extensions/extension.hpp>
#include <websocketpp/extensions/permessage_deflate/disabled.hpp>
#include <websocketpp/frame.hpp>
#include <websocketpp/http/constants.hpp>
#include <websocketpp/http/parser.hpp>
#include <websocketpp/http/request.hpp>
#include <websocketpp/http/response.hpp>
#include <websocketpp/message_buffer/alloc.hpp>
#include <websocketpp/message_buffer/message.hpp>
#include <websocketpp/processors/base.hpp>
#include <websocketpp/processors/hybi00.hpp>
#include <websocketpp/processors/hybi07.hpp>
#include <websocketpp/processors/hybi08.hpp>
#include <websocketpp/processors/hybi13.hpp>
#include <websocketpp/processors/processor.hpp>
#include <websocketpp/random/none.hpp>
#include <websocketpp/roles/server_endpoint.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/sha1/sha1.hpp>
#include <websocketpp/utf8_validator.hpp>
#include <websocketpp/utilities.hpp>

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <boost/system/detail/throws.hpp>
#include <mswsockdef.h>
#include <pplcancellation_token.h>
#include <pplinterface.h>
#include <ppltasks.h>
#include <ppltaskscheduler.h>
#include <pplwin.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <ws2ipdef.h>
#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <ostream>
#include <queue>
#include <ratio>
#include <set>
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
namespace Console
{
	class ConsoleOutputHandler;
}
namespace
{
	class RconConsoleOutputHandler;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
	namespace WebSocket {}
	using namespace Utils::WebSocket;
}

namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace Rcon {}
	using namespace Server::Rcon;
}

namespace asio_require_fn {}
using namespace ::asio_require_fn;
namespace Modules {}
using namespace ::Modules;
namespace asio_query_fn {}
using namespace ::asio_query_fn;
namespace asio_require_concept_fn {}
using namespace ::asio_require_concept_fn;
namespace asio_execution_bulk_execute_fn {}
using namespace ::asio_execution_bulk_execute_fn;
namespace asio_execution_submit_fn {}
using namespace ::asio_execution_submit_fn;
namespace asio_execution_set_value_fn {}
using namespace ::asio_execution_set_value_fn;
namespace asio_prefer_fn {}
using namespace ::asio_prefer_fn;
namespace asio_execution_set_error_fn {}
using namespace ::asio_execution_set_error_fn;
namespace asio_execution_start_fn {}
using namespace ::asio_execution_start_fn;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Core {}
	using namespace Patches::Core;
}

namespace asio_execution_execute_fn {}
using namespace ::asio_execution_execute_fn;
namespace asio_execution_set_done_fn {}
using namespace ::asio_execution_set_done_fn;
namespace asio_execution_schedule_fn {}
using namespace ::asio_execution_schedule_fn;
namespace asio_execution_connect_fn {}
using namespace ::asio_execution_connect_fn;
namespace Console {}
using namespace ::Console;

/* ---------- constants */

/* ---------- definitions */

namespace
{
	class RconConsoleOutputHandler :
		public Console::ConsoleOutputHandler
	{
	private:
		virtual void WriteLine(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
	public:
		RconConsoleOutputHandler(RconConsoleOutputHandler &); /* compiler_generated() */
		RconConsoleOutputHandler(RconConsoleOutputHandler const &); /* compiler_generated() */
		RconConsoleOutputHandler(); /* compiler_generated() */
		virtual ~RconConsoleOutputHandler(); /* compiler_generated() */
		RconConsoleOutputHandler &operator=(RconConsoleOutputHandler &); /* compiler_generated() */
		RconConsoleOutputHandler &operator=(RconConsoleOutputHandler const &); /* compiler_generated() */
	};
	static_assert(sizeof(RconConsoleOutputHandler) == 4, "Invalid RconConsoleOutputHandler size");
}
/* ---------- prototypes */

namespace Server
{
	namespace Rcon
	{
		extern void Initialize();
		extern void SendMessageToClients(std::basic_string<char,std::char_traits<char>,std::allocator<char> > message);
		extern void Tick();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern websocketpp::server<Utils::WebSocket::Config> rconServer; // 0x12467AA8
	extern std::set<std::weak_ptr<void>,std::owner_less<std::weak_ptr<void> >,std::allocator<std::weak_ptr<void> > > authenticatedConnections; // 0x12467A94
	extern char const *ProtocolName; // 0x11354EA8
	extern char const *AcceptMessage; // 0x11354EAC
	extern char const *DenyMessage; // 0x11354EB0
}
/* ---------- public code */

namespace Server
{
	namespace Rcon
	{
		_extern void _sub_10BB4150();
		void Initialize() // 0x10BB4150
		{
			mangled_x86(MANGLED_TODO, "?Initialize@Rcon@Server@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10BB4150();
		}

		_extern void _sub_10BB57C0(std::string);
		void SendMessageToClients(std::basic_string<char,std::char_traits<char>,std::allocator<char> > message) // 0x10BB57C0
		{
			mangled_x86(MANGLED_TODO, "?SendMessageToClients@Rcon@Server@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10BB5987
			// static ...; // 0x10BB597E
			// static ...; // 0x10BB597C
			// static ...; // 0x10BB5958
			// static ...; // 0x10BB5950
		// $LN14:
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > message;
			{
				// std::set<std::weak_ptr<void>,std::owner_less<std::weak_ptr<void> >,std::allocator<std::weak_ptr<void> > > &<range>$L0;
				// std::_Tree_unchecked_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::weak_ptr<void> > >,std::_Iterator_base0> <begin>$L0;
				// std::_Default_sentinel <end>$L0;
				{
					// std::weak_ptr<void> const &it;
					{
						// websocketpp::exception const &e;
					}
				}
			}
			// function call : char const *() const
			todo("implement");
			_sub_10BB57C0(message);
		}

		_extern void _sub_10BB5A10();
		void Tick() // 0x10BB5A10
		{
			mangled_x86(MANGLED_TODO, "?Tick@Rcon@Server@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10BB5A10();
		}
	}
}

/* ---------- private code */
