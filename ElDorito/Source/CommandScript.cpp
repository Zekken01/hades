/* ---------- headers */

#include "CommandScript.hpp"
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
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "CommandLineArgs.hpp"
#include "CommandMap.hpp"
#include "Console/Console.hpp"
#include "Forge/Magnets.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/mod_system.hpp"
#include "mods/new/IModManager.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Scripting/HaloScript/HaloScript.hpp"
#include "Utils/Singleton.hpp"

#include <Windows.h>
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
#include <deque>
#include <exception>
#include <forward_list>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <memory>
#include <mutex>
#include <optional>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stack>
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

class CommandLineArgs;
struct lambda_1;
struct lambda_2;
struct lambda_3;
struct lambda_4;
struct lambda_5;
struct lambda_6;
struct lambda_7;
namespace Modules
{
	class CommandMap;
	class CommandScript;
	class CommandScriptStack;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Debug {}
using namespace ::Debug;
namespace Console {}
using namespace ::Console;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

//class Modules::CommandScript::ExecuteWaitFor::__l8::<lambda_1>
//{
//public:
//	bool operator()() const;
//};
//static_assert(sizeof(Modules::CommandScript::ExecuteWaitFor::__l8::<lambda_1>) == 1, "Invalid Modules::CommandScript::ExecuteWaitFor::__l8::<lambda_1> size");

//class Modules::CommandScript::ExecuteWaitFor::__l12::<lambda_2>
//{
//public:
//	bool operator()() const;
//};
//static_assert(sizeof(Modules::CommandScript::ExecuteWaitFor::__l12::<lambda_2>) == 1, "Invalid Modules::CommandScript::ExecuteWaitFor::__l12::<lambda_2> size");

//class Modules::CommandScript::ExecuteWaitFor::__l16::<lambda_3>
//{
//public:
//	bool operator()() const;
//};
//static_assert(sizeof(Modules::CommandScript::ExecuteWaitFor::__l16::<lambda_3>) == 1, "Invalid Modules::CommandScript::ExecuteWaitFor::__l16::<lambda_3> size");

//class Modules::CommandScript::ExecuteWaitFor::__l20::<lambda_4>
//{
//public:
//	bool operator()() const;
//	<lambda_4>(Modules::CommandScript::ExecuteWaitFor::__l20::<lambda_4> &);
//	<lambda_4>(unsigned long &);
//private:
//	unsigned long &establishTime; // 0x0
//public:
//	Modules::CommandScript::ExecuteWaitFor::__l20::<lambda_4> &operator=(Modules::CommandScript::ExecuteWaitFor::__l20::<lambda_4> const &);
//};
//static_assert(sizeof(Modules::CommandScript::ExecuteWaitFor::__l20::<lambda_4>) == 4, "Invalid Modules::CommandScript::ExecuteWaitFor::__l20::<lambda_4> size");

//class Modules::CommandScript::ExecuteWaitFor::__l24::<lambda_5>
//{
//public:
//	bool operator()() const;
//	<lambda_5>(Modules::CommandScript::ExecuteWaitFor::__l24::<lambda_5> &);
//	<lambda_5>(__int32 const &);
//private:
//	__int32 lobbyType; // 0x0
//public:
//	Modules::CommandScript::ExecuteWaitFor::__l24::<lambda_5> &operator=(Modules::CommandScript::ExecuteWaitFor::__l24::<lambda_5> const &);
//};
//static_assert(sizeof(Modules::CommandScript::ExecuteWaitFor::__l24::<lambda_5>) == 4, "Invalid Modules::CommandScript::ExecuteWaitFor::__l24::<lambda_5> size");

//class Modules::CommandScript::ExecuteWaitFor::__l34::<lambda_6>
//{
//public:
//	bool operator()() const;
//	<lambda_6>(Modules::CommandScript::ExecuteWaitFor::__l34::<lambda_6> &);
//	<lambda_6>(__int32 const &);
//private:
//	__int32 playerCount; // 0x0
//public:
//	Modules::CommandScript::ExecuteWaitFor::__l34::<lambda_6> &operator=(Modules::CommandScript::ExecuteWaitFor::__l34::<lambda_6> const &);
//};
//static_assert(sizeof(Modules::CommandScript::ExecuteWaitFor::__l34::<lambda_6>) == 4, "Invalid Modules::CommandScript::ExecuteWaitFor::__l34::<lambda_6> size");

//class Modules::CommandScript::ExecuteWaitFor::__l44::<lambda_7>
//{
//public:
//	bool operator()() const;
//};
//static_assert(sizeof(Modules::CommandScript::ExecuteWaitFor::__l44::<lambda_7>) == 1, "Invalid Modules::CommandScript::ExecuteWaitFor::__l44::<lambda_7> size");

//class Modules::CommandScript::ExecuteSleep::__l2::<lambda_1>
//{
//public:
//	bool operator()() const;
//	<lambda_1>(Modules::CommandScript::ExecuteSleep::__l2::<lambda_1> &);
//	<lambda_1>(std::chrono::time_point<std::chrono::system_clock,std::chrono::duration<__int64,std::ratio<1,10000000> > > const &);
//private:
//	std::chrono::time_point<std::chrono::system_clock,std::chrono::duration<__int64,std::ratio<1,10000000> > > wakeTime; // 0x0
//public:
//	Modules::CommandScript::ExecuteSleep::__l2::<lambda_1> &operator=(Modules::CommandScript::ExecuteSleep::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(Modules::CommandScript::ExecuteSleep::__l2::<lambda_1>) == 8, "Invalid Modules::CommandScript::ExecuteSleep::__l2::<lambda_1> size");

/* ---------- prototypes */

extern bool (*const network_session_interface_get_squad_session)(c_network_session **out_session);  // hades: added for 0x10666F10

namespace Modules
{
	bool ParseInt(std::string s, __int32 &delay);
}

/* ---------- globals */

namespace Utils
{
	Modules::CommandMap *Utils::Singleton<Modules::CommandMap>::m_instance; // 0x1137180C
}

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	void CommandScript::Execute() // 0x10666950
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Execute@CommandScript@Modules@@QAEXXZ");

		if (m_wakeCond && !m_wakeCond())
			return;
		m_wakeCond = nullptr;
		while (!m_finished)
		{
			if (!ReadNextLine())
			{
				Complete();
			}
			else
			{
				CommandLineArgs args(m_line);
				std::string commandName = args.GetArg(0);
				if (commandName == "sleep")
				{
					ExecuteSleep(args);
					return;
				}
				else if (commandName == "waitfor")
				{
					ExecuteWaitFor(args);
					return;
				}
				else
				{
					std::string output;
					if (!Modules::CommandMap::Instance().ExecuteCommandWithStatus(m_line, m_isUserInput, &output))
						HandleError(output);
				}
			}
		}
	}

	void CommandScript::ExecuteWaitFor(CommandLineArgs const &args) // 0x10666F10
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ExecuteWaitFor@CommandScript@Modules@@AAEXABVCommandLineArgs@@@Z");

		if (args.GetArgCount() < 2)
		{
			HandleError(std::format("Invalid arguments"));
			return;
		}
		std::string condition = args.GetArg(1);
		if (condition == "mainmenu")
		{
			m_wakeCond = []() { return ((bool (*)())0x5314B0)() && ((bool (*)())0x531E90)(); };
		}
		else if (condition == "in_game")
		{
			m_wakeCond = []() { return !((bool (*)())0x5314B0)() && !((bool (*)())0x531E90)(); };
		}
		else if (condition == "mod_load")
		{
			m_wakeCond = []()
			{
				IMod *mod = c_mod_system::GetModManager().GetMod(kGame);
				if (!mod)
					return true;
				return !mod->GetCacheIsLoading() && !((bool (*)())0x54B3A0)();
			};
		}
		else if (condition == "in_session")
		{
			unsigned long establishTime = 0;
			m_wakeCond = [&establishTime]()
			{
				c_network_session *session;
				if (network_session_interface_get_squad_session(&session) && session->established())
				{
					unsigned long now = system_milliseconds();
					if (establishTime == 0)
						establishTime = now;
					return now - establishTime >= 1000;
				}
				return false;
			};
		}
		else if (condition == "lobbytype")
		{
			if (args.GetArgCount() < 3)
			{
				HandleError(std::format("Expected lobby type"));
				return;
			}
			__int32 lobbyType;
			if (!ParseInt(args[2], lobbyType))
			{
				HandleError(std::format("Invalid lobby type"));
				return;
			}
			m_wakeCond = [lobbyType]() { return ((long (*)())0x435640)() == lobbyType; };
		}
		else if (condition == "player_count")
		{
			if (args.GetArgCount() < 3)
			{
				HandleError(std::format("Expected player count"));
				return;
			}
			__int32 playerCount;
			if (!ParseInt(args[2], playerCount))
			{
				HandleError(std::format("Invalid player count"));
				return;
			}
			m_wakeCond = [playerCount]()
			{
				c_network_session *session;
				if (network_session_interface_get_squad_session(&session) && session->established())
					return session->get_player_count() >= playerCount;
				else
					return false;
			};
		}
		else if (condition == "spawn")
		{
			m_wakeCond = []() { return ((bool (*)())0x5314B0)() && ((long (*)(long))0x589CC0)(0) != -1; };
		}
		else
		{
			HandleError("Unknown wait condition");
		}
	}

	void CommandScript::ExecuteSleep(CommandLineArgs const &args) // 0x10666C80
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ExecuteSleep@CommandScript@Modules@@AAEXABVCommandLineArgs@@@Z");

		if (args.GetArgCount() < 2)
		{
			HandleError(std::format("Invalid arguments"));
			return;
		}
		__int32 delay;
		if (!ParseInt(args.GetArg(1), delay))
		{
			HandleError("Invalid delay");
			return;
		}
		auto wakeTime = std::chrono::system_clock::now() + std::chrono::milliseconds(delay);
		m_wakeCond = [wakeTime]() { return std::chrono::system_clock::now() >= wakeTime; };
	}

	bool CommandScript::ReadNextLine() // 0x10667C10
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ReadNextLine@CommandScript@Modules@@AAE_NXZ");

		while (std::getline(*m_stream, m_line))
		{
			++m_lineNum;
			m_line.erase(m_line.find_last_not_of("\r") + 1);
			if (m_line.empty())
				continue;
			return true;
		}
		return false;
	}

	void CommandScript::Complete() // 0x10666920
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Complete@CommandScript@Modules@@QAEXXZ");

		m_finished = true;
	}

	void CommandScript::HandleError(std::string const &message) // 0x106677A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?HandleError@CommandScript@Modules@@AAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

		m_error << "Error at line " << m_lineNum << ": " << message << std::endl;
		m_hasError = true;
		if (m_stopOnFirstError)
			Complete();
	}

	bool CommandScript::HasError() const // 0x10667890
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?HasError@CommandScript@Modules@@QBE_NXZ");

		return m_hasError;
	}
}


namespace Modules
{
	std::string CommandScript::GetErrorMessage() const // 0x10667710
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetErrorMessage@CommandScript@Modules@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");

		return m_error.str();
	}

	bool CommandScript::IsFinished() const // 0x10667A00
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?IsFinished@CommandScript@Modules@@QBE_NXZ");

		return m_finished;
	}

	void CommandScriptStack::PushScript(std::shared_ptr<Modules::CommandScript> script) // 0x10667B50
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?PushScript@CommandScriptStack@Modules@@QAEXV?$shared_ptr@VCommandScript@Modules@@@std@@@Z");

		m_stack.emplace(std::move(script));
	}

	void CommandScriptStack::Update() // 0x10667D30
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Update@CommandScriptStack@Modules@@QAEXXZ");

		if (m_stack.empty())
			return;

		std::shared_ptr<Modules::CommandScript> &script = m_stack.top();
		script->Execute();
		if (script->IsFinished())
		{
			if (script->HasError())
			{
				script->Execute();
				Console::WriteLine(script->GetErrorMessage());
			}
			m_stack.pop();
		}
	}

	// mangled_x86(MANGLED_DEFAULT, "??0CommandMap@Modules@@QAE@XZ"); no body to assert in
}

/* ---------- private code */

namespace Modules
{
	bool ParseInt(std::string s, __int32 &delay) // 0x10667A30
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ParseInt@Modules@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAH@Z");

		char const *start = s.data();
		char const *end = s.data() + s.size();
		auto [ptr, ec] = std::from_chars(start, end, delay);
		return ec == std::errc();
	}
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Modules::CommandMap & Utils::Singleton<Modules::CommandMap>::Instance();
