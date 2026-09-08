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
	_extern void _sub_10666950(Modules::CommandScript *const);
	void CommandScript::Execute() // 0x10666950
	{
		mangled_x86(MANGLED_TODO, "?Execute@CommandScript@Modules@@QAEXXZ");
		// static ...; // 0x10666BCF
		// static ...; // 0x10666BC3
		// static ...; // 0x10666BBC
		// static ...; // 0x10666B98
		// static ...; // 0x10666B90
		// Modules::CommandScript *const this;
		{
			// CommandLineArgs args;
			// std::string commandName;
			{
				// std::string output;
			}
		}
		todo("implement");
		_sub_10666950(this);
	}

	_extern void _sub_10666F10(Modules::CommandScript *const, CommandLineArgs const &);
	void CommandScript::ExecuteWaitFor(CommandLineArgs const &args) // 0x10666F10
	{
		mangled_x86(MANGLED_TODO, "?ExecuteWaitFor@CommandScript@Modules@@AAEXABVCommandLineArgs@@@Z");
		// static ...; // 0x106674AE
		// static ...; // 0x106674A4
		// static ...; // 0x10667498
		// static ...; // 0x10667468
		// static ...; // 0x10667460
		// Modules::CommandScript *const this;
		// CommandLineArgs const &args;
		// std::string condition;
		{
		}
		{
		}
		{
		}
		{
			// unsigned long establishTime;
		}
		{
			// __int32 lobbyType;
		}
		{
			// __int32 playerCount;
		}
		{
		}
		todo("implement");
		_sub_10666F10(this, args);
	}

	_extern void _sub_10666C80(Modules::CommandScript *const, CommandLineArgs const &);
	void CommandScript::ExecuteSleep(CommandLineArgs const &args) // 0x10666C80
	{
		mangled_x86(MANGLED_TODO, "?ExecuteSleep@CommandScript@Modules@@AAEXABVCommandLineArgs@@@Z");
		// static ...; // 0x10666E74
		// static ...; // 0x10666E5C
		// static ...; // 0x10666E54
		// Modules::CommandScript *const this;
		// CommandLineArgs const &args;
		// __int32 delay;
		// std::chrono::time_point<std::chrono::system_clock,std::chrono::duration<__int64,std::ratio<1,10000000> > > wakeTime;
		todo("implement");
		_sub_10666C80(this, args);
	}

	_extern bool _sub_10667C10(Modules::CommandScript *const);
	bool CommandScript::ReadNextLine() // 0x10667C10
	{
		mangled_x86(MANGLED_TODO, "?ReadNextLine@CommandScript@Modules@@AAE_NXZ");
		// Modules::CommandScript *const this;
		todo("implement");
		bool __result = _sub_10667C10(this);
		return __result;
	}

	_extern void _sub_10666920(Modules::CommandScript *const);
	void CommandScript::Complete() // 0x10666920
	{
		mangled_x86(MANGLED_TODO, "?Complete@CommandScript@Modules@@QAEXXZ");
		// Modules::CommandScript *const this;
		todo("implement");
		_sub_10666920(this);
	}

	_extern void _sub_106677A0(Modules::CommandScript *const, std::string const &);
	void CommandScript::HandleError(std::string const &message) // 0x106677A0
	{
		mangled_x86(MANGLED_TODO, "?HandleError@CommandScript@Modules@@AAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string const &message;
		todo("implement");
		_sub_106677A0(this, message);
	}

	bool CommandScript::HasError() const // 0x10667890
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?HasError@CommandScript@Modules@@QBE_NXZ");
		// Modules::CommandScript const *const this;

		return m_hasError;
	}
}

extern std::string _sub_10667710(Modules::CommandScript const *const);
namespace Modules
{
	std::string CommandScript::GetErrorMessage() const // 0x10667710
	{
		mangled_x86(MANGLED_TODO, "?GetErrorMessage@CommandScript@Modules@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// Modules::CommandScript const *const this;
		todo("implement");
		std::string __result = _sub_10667710((Modules::CommandScript const *)this);
		return __result;
	}

	bool CommandScript::IsFinished() const // 0x10667A00
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?IsFinished@CommandScript@Modules@@QBE_NXZ");
		// Modules::CommandScript const *const this;

		return m_finished;
	}

	_extern void _sub_10667B50(Modules::CommandScriptStack *const, std::shared_ptr<Modules::CommandScript>);
	void CommandScriptStack::PushScript(std::shared_ptr<Modules::CommandScript> script) // 0x10667B50
	{
		mangled_x86(MANGLED_TODO, "?PushScript@CommandScriptStack@Modules@@QAEXV?$shared_ptr@VCommandScript@Modules@@@std@@@Z");
		// std::shared_ptr<Modules::CommandScript> script;
		todo("implement");
		_sub_10667B50(this, script);
	}

	_extern void _sub_10667D30(Modules::CommandScriptStack *const);
	void CommandScriptStack::Update() // 0x10667D30
	{
		mangled_x86(MANGLED_TODO, "?Update@CommandScriptStack@Modules@@QAEXXZ");
		// Modules::CommandScriptStack *const this;
		// std::shared_ptr<Modules::CommandScript> &script;
		todo("implement");
		_sub_10667D30(this);
	}

	// mangled_x86(MANGLED_DEFAULT, "??0CommandMap@Modules@@QAE@XZ"); no body to assert in
	_inline CommandMap::CommandMap() = default; // 0x1065D950
}

/* ---------- private code */

namespace Modules
{
	_extern bool _sub_10667A30(std::string, __int32 &);
	bool ParseInt(std::string s, __int32 &delay) // 0x10667A30
	{
		// Modules::ParseInt
		// static ...; // 0x10667B04
		// static ...; // 0x10667AFC
		// std::string s;
		// __int32 &delay;
		// std::errc ec;
		// std::from_chars_result $S15;
		// char const *ptr;
		// char const *start;
		// char const *end;
		todo("implement");
		bool __result = _sub_10667A30(s, delay);
		return __result;
	}
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Modules::CommandMap & Utils::Singleton<Modules::CommandMap>::Instance();
