/* ---------- headers */

#include "hades/hades.h"

#include "Blam/main/levels.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Console/Console.hpp"
#include "ElDorito.hpp"
#include "Forge/Magnets.hpp"
#include "Modules/ModuleServer.hpp"
#include "Patches/Core.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/Network.hpp"
#include "Pointer.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Utils/Uri.hpp"
#include "Utils/WebSocket.hpp"

#include "Utils/Logger.hpp"  // hades: added for 0x10BB4850

#include "Modules/ModuleGame.hpp"  // hades: added for 0x10BB3E50

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
namespace Modules
{
	class ModuleServer;
	struct Command;
}
namespace hades_file_local
{
	class RconConsoleOutputHandler;
}
using namespace hades_file_local;

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

namespace hades_file_local
{
	class RconConsoleOutputHandler :
		public Console::ConsoleOutputHandler
	{
	private:
		virtual void WriteLine(std::string const &);
	public:
		RconConsoleOutputHandler(RconConsoleOutputHandler &); /* compiler_generated() */
		RconConsoleOutputHandler(RconConsoleOutputHandler const &); /* compiler_generated() */
		RconConsoleOutputHandler() = default; /* compiler_generated() */  // hades: not user-provided, so make_shared value-initializes
		virtual ~RconConsoleOutputHandler() = default; /* compiler_generated() */
		RconConsoleOutputHandler &operator=(RconConsoleOutputHandler &); /* compiler_generated() */
		RconConsoleOutputHandler &operator=(RconConsoleOutputHandler const &); /* compiler_generated() */
	};
	static_assert(sizeof(RconConsoleOutputHandler) == 4, "Invalid RconConsoleOutputHandler size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Server { namespace Rcon { extern void SendMessageToClients(std::string message); } }  // hades: added for 0x10BB5A60

namespace Server
{
	namespace Rcon
	{
		extern void Initialize();
		extern void SendMessageToClients(std::string message);
		extern void Tick();
	}
}

static void ForceStopServer();
void InitServer();
static bool OnValidate(websocketpp::server<Utils::WebSocket::Config> *rconServer, std::weak_ptr<void> hdl);
static void OnMessage(websocketpp::server<Utils::WebSocket::Config> *rconServer, std::weak_ptr<void> hdl, std::shared_ptr<websocketpp::message_buffer::message<websocketpp::message_buffer::alloc::con_msg_manager> > msg);
void ProcessCommand(websocketpp::server<Utils::WebSocket::Config> *rconServer, std::weak_ptr<void> hdl, std::shared_ptr<websocketpp::message_buffer::message<websocketpp::message_buffer::alloc::con_msg_manager> > msg);
void ProcessPassword(websocketpp::server<Utils::WebSocket::Config> *rconServer, std::weak_ptr<void> hdl, std::shared_ptr<websocketpp::message_buffer::message<websocketpp::message_buffer::alloc::con_msg_manager> > msg);
static void OnClose(websocketpp::server<Utils::WebSocket::Config> *rconServer, std::weak_ptr<void> hdl);
void LogMessage(websocketpp::server<Utils::WebSocket::Config> *rconServer, std::weak_ptr<void> hdl, std::string message);
std::string GetLogString(websocketpp::server<Utils::WebSocket::Config> *rconServer, std::weak_ptr<void> hdl, std::string message);

namespace Utils { namespace Cryptography { extern bool RandomPassword(__int32 length, std::string &out); } }  // hades: added for 0x10BB4150

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern websocketpp::server<Utils::WebSocket::Config> rconServer; // 0x12467AA8
	extern std::set<std::weak_ptr<void>,std::owner_less<std::weak_ptr<void> > > authenticatedConnections; // 0x12467A94
	extern char const *ProtocolName; // 0x11354EA8
	extern char const *AcceptMessage; // 0x11354EAC
	extern char const *DenyMessage; // 0x11354EB0
}
using namespace hades_file_local;
/* ---------- public code */

namespace Server
{
	namespace Rcon
	{
		void Initialize() // 0x10BB4150
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Initialize@Rcon@Server@@YAXXZ");
			// procedure flags: nofpo

			if (Modules::ModuleServer::Instance().VarRconPassword->ValueString == "")
			{
				Utils::Cryptography::RandomPassword(32, Modules::ModuleServer::Instance().VarRconPassword->ValueString);
				Modules::CommandMap::Instance().ExecuteCommand("WriteConfig");
			}
			if (!ElDorito::Instance().IsDedicated())
				return;
			Patches::Core::OnShutdown(ForceStopServer);
			Console::RegisterHandler(std::make_shared<RconConsoleOutputHandler>());
			InitServer();
		}

		void SendMessageToClients(std::string message) // 0x10BB57C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SendMessageToClients@Rcon@Server@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10BB5987
			// static ...; // 0x10BB597E
			// static ...; // 0x10BB597C
			// static ...; // 0x10BB5958
			// static ...; // 0x10BB5950
		// $LN14:
			// std::string message;
				// std::set<std::weak_ptr<void>,std::owner_less<std::weak_ptr<void> > > &<range>$L0;
				// std::_Tree_unchecked_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::weak_ptr<void> > >,std::_Iterator_base0> <begin>$L0;
				// std::_Default_sentinel <end>$L0;
					// std::weak_ptr<void> const &it;
						// websocketpp::exception const &e;
			// function call : char const *() const

			if (!rconServer.is_listening())
				return;
			for (std::weak_ptr<void> const &it : authenticatedConnections)
			{
				try
				{
					rconServer.send(it, message, websocketpp::frame::opcode::text);
				}
				catch (websocketpp::exception const &e)
				{
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "websocketpp: %s", e.what());
				}
			}
		}

		void Tick() // 0x10BB5A10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@Rcon@Server@@YAXXZ");
			// procedure flags: nofpo

			rconServer.poll();
		}
	}
}

/* ---------- private code */

_inline void RconConsoleOutputHandler::WriteLine(std::string const &line) // 0x10BB5A60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?WriteLine@RconConsoleOutputHandler@hades_file_local@@EAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::RconConsoleOutputHandler::WriteLine
	// std::string const &line;

	if (Utils::Singleton<Modules::ModuleServer>::Instance().VarRconConsoleOutputEnabled->ValueInt == 1)
	{
		Server::Rcon::SendMessageToClients(line);
	}
}

static void ForceStopServer() // 0x10BB3A60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ForceStopServer@@YAXXZ");
	// `anonymous-namespace'::ForceStopServer
	// procedure flags: nofpo

	if (rconServer.is_listening())
	{
		rconServer.stop();
	}
}

void InitServer() // 0x10BB3E50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?InitServer@@YAXXZ");
	// `anonymous-namespace'::InitServer
	// procedure flags: nofpo
	// static ...; // 0x10BB40A8
	// static ...; // 0x10BB409C
	// static ...; // 0x10BB4094
// $LN11:
		// unsigned long port;
		// std::exception const &e;
	// function call : char const *() const

	try
	{
		rconServer.set_access_channels(websocketpp::log::alevel::all);
		rconServer.set_error_channels(websocketpp::log::elevel::all);
		rconServer.init_asio();
		rconServer.set_validate_handler(websocketpp::lib::bind(OnValidate, &rconServer, websocketpp::lib::placeholders::_1));
		rconServer.set_message_handler(websocketpp::lib::bind(OnMessage, &rconServer, websocketpp::lib::placeholders::_1, websocketpp::lib::placeholders::_2));
		rconServer.set_close_handler(websocketpp::lib::bind(OnClose, &rconServer, websocketpp::lib::placeholders::_1));
		unsigned long port = Utils::Singleton<Modules::ModuleGame>::Instance().VarRconPort->ValueInt;
		rconServer.listen(static_cast<uint16_t>(port));
		rconServer.start_accept();
	}
	catch (websocketpp::exception const &e)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "websocketpp: %s", e.what());
	}
}

static bool OnValidate(websocketpp::server<Utils::WebSocket::Config> *rconServer, std::weak_ptr<void> hdl) // 0x10BB4B10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnValidate@@YA_NPAV?$server@UConfig@WebSocket@Utils@@@websocketpp@@V?$weak_ptr@X@std@@@Z");
	// `anonymous-namespace'::OnValidate
	// static ...; // 0x10BB4D94
	// static ...; // 0x10BB4D7C
	// static ...; // 0x10BB4D74
	// websocketpp::server<Utils::WebSocket::Config> *rconServer;
	// std::weak_ptr<void> hdl;
	// std::vector<std::string> subprotocols;
	// std::shared_ptr<websocketpp::connection<Utils::WebSocket::Config> > connection;

	auto connection = rconServer->get_con_from_hdl(hdl);
	std::vector<std::string> subprotocols = connection->get_requested_subprotocols();
	if (std::find(subprotocols.begin(), subprotocols.end(), ProtocolName) == subprotocols.end())
		return false;
	connection->select_subprotocol(ProtocolName);
	LogMessage(rconServer, hdl, "Client Connected");
	return true;
}

static void OnMessage(websocketpp::server<Utils::WebSocket::Config> *rconServer, std::weak_ptr<void> hdl, std::shared_ptr<websocketpp::message_buffer::message<websocketpp::message_buffer::alloc::con_msg_manager> > msg) // 0x10BB4850
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnMessage@@YAXPAV?$server@UConfig@WebSocket@Utils@@@websocketpp@@V?$weak_ptr@X@std@@V?$shared_ptr@V?$message@Vcon_msg_manager@alloc@message_buffer@websocketpp@@@message_buffer@websocketpp@@@4@@Z");
	// `anonymous-namespace'::OnMessage
	// static ...; // 0x10BB4A68
// $LN20:
	// websocketpp::server<Utils::WebSocket::Config> *rconServer;
	// std::weak_ptr<void> hdl;
	// std::shared_ptr<websocketpp::message_buffer::message<websocketpp::message_buffer::alloc::con_msg_manager> > msg;
		// websocketpp::exception const &e;
	// function call : char const *() const

	try
	{
		if (authenticatedConnections.find(hdl) != authenticatedConnections.end())
			ProcessCommand(rconServer, hdl, msg);
		else
			ProcessPassword(rconServer, hdl, msg);
	}
	catch (websocketpp::exception const &e)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "websocketpp: %s", e.what());
	}
}

void ProcessCommand(websocketpp::server<Utils::WebSocket::Config> *rconServer, std::weak_ptr<void> hdl, std::shared_ptr<websocketpp::message_buffer::message<websocketpp::message_buffer::alloc::con_msg_manager> > msg) // 0x10BB4E60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ProcessCommand@@YAXPAV?$server@UConfig@WebSocket@Utils@@@websocketpp@@V?$weak_ptr@X@std@@V?$shared_ptr@V?$message@Vcon_msg_manager@alloc@message_buffer@websocketpp@@@message_buffer@websocketpp@@@4@@Z");
	// `anonymous-namespace'::ProcessCommand
	// static ...; // 0x10BB51D8
	// websocketpp::server<Utils::WebSocket::Config> *rconServer;
	// std::weak_ptr<void> hdl;
	// std::shared_ptr<websocketpp::message_buffer::message<websocketpp::message_buffer::alloc::con_msg_manager> > msg;
	// Modules::Command *cmd;
		// std::string output;

	Modules::Command *cmd = Utils::Singleton<Modules::CommandMap>::Instance().FindCommand(msg->get_payload().c_str());
	if (cmd && (cmd->Flags & eCommandFlagsNoRcon))
		rconServer->send(hdl, "Command cannot be executed through rcon", websocketpp::frame::opcode::text);
	else
	{
		std::string output = Utils::Singleton<Modules::CommandMap>::Instance().ExecuteCommand(msg->get_payload(), true);
		rconServer->send(hdl, output, websocketpp::frame::opcode::text);
	}
	LogMessage(rconServer, hdl, "Client Sent: " + msg->get_payload() + " [" + rconServer->get_con_from_hdl(hdl)->get_remote_endpoint() + "]");
}

void ProcessPassword(websocketpp::server<Utils::WebSocket::Config> *rconServer, std::weak_ptr<void> hdl, std::shared_ptr<websocketpp::message_buffer::message<websocketpp::message_buffer::alloc::con_msg_manager> > msg) // 0x10BB52E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ProcessPassword@@YAXPAV?$server@UConfig@WebSocket@Utils@@@websocketpp@@V?$weak_ptr@X@std@@V?$shared_ptr@V?$message@Vcon_msg_manager@alloc@message_buffer@websocketpp@@@message_buffer@websocketpp@@@4@@Z");
	// `anonymous-namespace'::ProcessPassword
	// static ...; // 0x10BB5690
	// static ...; // 0x10BB5688
	// websocketpp::server<Utils::WebSocket::Config> *rconServer;
	// std::weak_ptr<void> hdl;
	// std::shared_ptr<websocketpp::message_buffer::message<websocketpp::message_buffer::alloc::con_msg_manager> > msg;
	// std::string actualPassword;
	// std::string inPassword;

	std::string inPassword = msg->get_payload();
	std::string actualPassword = Utils::Singleton<Modules::ModuleServer>::Instance().VarRconPassword->ValueString;
	if (inPassword == actualPassword)
	{
		authenticatedConnections.insert(hdl);
		rconServer->send(hdl, AcceptMessage, websocketpp::frame::opcode::text);
		LogMessage(rconServer, hdl, "Rcon Password Authenticated: " + rconServer->get_con_from_hdl(hdl)->get_remote_endpoint());
	}
	else
	{
		rconServer->send(hdl, DenyMessage, websocketpp::frame::opcode::text);
		rconServer->close(hdl, websocketpp::close::status::policy_violation, DenyMessage);
		LogMessage(rconServer, hdl, "Failed Password Attempt: " + rconServer->get_con_from_hdl(hdl)->get_remote_endpoint());
	}
}

static void OnClose(websocketpp::server<Utils::WebSocket::Config> *rconServer, std::weak_ptr<void> hdl) // 0x10BB4770
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnClose@@YAXPAV?$server@UConfig@WebSocket@Utils@@@websocketpp@@V?$weak_ptr@X@std@@@Z");
	// `anonymous-namespace'::OnClose
	// std::weak_ptr<void> hdl;

	authenticatedConnections.erase(hdl);
	LogMessage(rconServer, hdl, "Client Connection Closed");
}

void LogMessage(websocketpp::server<Utils::WebSocket::Config> *rconServer, std::weak_ptr<void> hdl, std::string message) // 0x10BB4330
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LogMessage@@YAXPAV?$server@UConfig@WebSocket@Utils@@@websocketpp@@V?$weak_ptr@X@std@@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@4@@Z");
	// `anonymous-namespace'::LogMessage
	// static ...; // 0x10BB4640
	// static ...; // 0x10BB4638
	// static ...; // 0x10BB4608
	// static ...; // 0x10BB4600
	// websocketpp::server<Utils::WebSocket::Config> *rconServer;
	// std::weak_ptr<void> hdl;
	// std::string message;
	// std::filesystem::path parentDirectory;
	// std::ofstream logFile;
	// std::filesystem::path logFilePath;
	// std::string rconLogFile;
	// Modules::ModuleServer &serverModule;

	Modules::ModuleServer &serverModule = Utils::Singleton<Modules::ModuleServer>::Instance();
	if (!serverModule.VarRconLogEnabled->ValueInt)
		return;
	std::string rconLogFile = Utils::Singleton<Modules::ModuleServer>::Instance().VarRconLogFile->ValueString;
	std::filesystem::path logFilePath(rconLogFile);
	std::filesystem::path parentDirectory = logFilePath.parent_path();
	if (parentDirectory != "")
		std::filesystem::create_directories(parentDirectory);
	std::ofstream logFile(rconLogFile, std::ios::app);
	if (!logFile)
		return;
	logFile << GetLogString(rconServer, hdl, message) << "\n";
}

std::string GetLogString(websocketpp::server<Utils::WebSocket::Config> *rconServer, std::weak_ptr<void> hdl, std::string message) // 0x10BB3AC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetLogString@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAV?$server@UConfig@WebSocket@Utils@@@websocketpp@@V?$weak_ptr@X@2@V12@@Z");
	// `anonymous-namespace'::GetLogString
	// static ...; // 0x10BB3D7E
	// static ...; // 0x10BB3D73
	// static ...; // 0x10BB3D6C
	// static ...; // 0x10BB3D63
	// static ...; // 0x10BB3D60
	// static ...; // 0x10BB3D0C
	// static ...; // 0x10BB3D04
	// websocketpp::server<Utils::WebSocket::Config> *rconServer;
	// std::weak_ptr<void> hdl;
	// std::string message;
	// std::string client;
	// std::ostringstream ss;
	// long long time;
	// std::shared_ptr<websocketpp::connection<Utils::WebSocket::Config> > connection;
	// std::string trimedIP;
	// tm gmTime;
	// std::chrono::time_point<std::chrono::system_clock,std::chrono::duration<__int64,std::ratio<1,10000000> > > now;

	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	long long time = std::chrono::system_clock::to_time_t(now);
	tm gmTime;
	gmtime_s(&gmTime, &time);
	websocketpp::server<Utils::WebSocket::Config>::connection_ptr connection = rconServer->get_con_from_hdl(hdl);
	std::string client = connection->get_remote_endpoint();
	std::string trimedIP = client.replace(1, 7, "");
	std::ostringstream ss;
	ss << "[" << std::put_time(&gmTime, "%m/%d/%y %H:%M:%S") << "] ";
	ss << trimedIP << " - ";
	ss << message;
	return ss.str();
}

// mangled_x86(MANGLED_DEFAULT, "??0RconConsoleOutputHandler@hades_file_local@@QAE@XZ"); no body to assert in
// _inline RconConsoleOutputHandler::RconConsoleOutputHandler() = default; // 0x10B95270  // hades: defaulted on its declaration

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { websocketpp::server<Utils::WebSocket::Config> rconServer; }
namespace hades_file_local { std::set<std::weak_ptr<void>,std::owner_less<std::weak_ptr<void> > > authenticatedConnections; }
namespace hades_file_local { char const *ProtocolName = "dew-rcon"; }
namespace hades_file_local { char const *AcceptMessage = "accept"; }
namespace hades_file_local { char const *DenyMessage = "deny"; }
