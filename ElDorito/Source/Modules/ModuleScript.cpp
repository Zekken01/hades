/* ---------- headers */

#include "Modules/ModuleScript.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Scripting/HaloScript/HsMethodMap.hpp"
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
#include <exception>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <limits>
#include <list>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Modules
{
	class ModuleBase;
	class ModuleScript;
}
namespace Scripting
{
	namespace HS
	{
		class ScriptMethodMap;
		struct ScriptMethod;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Scripting {}
using namespace ::Scripting;
namespace Scripting
{
	namespace HS {}
	using namespace Scripting::HS;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

bool CommandGenerateMethodDecl(std::vector<std::string> const &args, std::string &retValue);
bool CommandScriptHelp(std::vector<std::string> const &args, std::string &retValue);
bool CommandGenerateDoc(std::vector<std::string> const &args, std::string &retValue);

/* ---------- globals */

namespace Utils
{
	Scripting::HS::ScriptMethodMap *Utils::Singleton<Scripting::HS::ScriptMethodMap>::m_instance; // 0x11387E80
}

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	extern ModuleScript* _sub_106D3590(Modules::ModuleScript *const);
	ModuleScript::ModuleScript() : ModuleBase(todo_result<std::string>()) // 0x106D3590
	{
		mangled_x86(MANGLED_TODO, "??0ModuleScript@Modules@@QAE@XZ");
		// Modules::ModuleScript *const this;
		todo("implement");
		_sub_106D3590(this);
	}
}

namespace Scripting
{
	namespace HS
	{
		// mangled_x86(MANGLED_DEFAULT, "??0ScriptMethodMap@HS@Scripting@@QAE@XZ"); no body to assert in
	}
}

namespace Modules
{
	// mangled_x86(MANGLED_DEFAULT, "??1ModuleBase@Modules@@QAE@XZ"); no body to assert in
	_inline ModuleBase::~ModuleBase() = default; // 0x106D3ED0
}

namespace Scripting
{
	namespace HS
	{
		// mangled_x86(MANGLED_DEFAULT, "??1ScriptMethod@HS@Scripting@@QAE@XZ"); no body to assert in
		_inline ScriptMethod::~ScriptMethod() = default; // 0x106D3F20
	}
}

/* ---------- private code */

bool CommandGenerateMethodDecl(std::vector<std::string> const &args, std::string &retValue) // 0x106D4200
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGenerateMethodDecl@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandGenerateMethodDecl
	// std::string &retValue;
	// Scripting::HS::ScriptMethod const *method;
	// Scripting::HS::ScriptMethodMap &methods;

	if (args.size() < 1)
	{
		retValue = "Invalid arguments";
		return false;
	}

	auto &methodMap = Utils::Singleton<Scripting::HS::ScriptMethodMap>::Instance();

	auto *method = methodMap.FindMethod(args[0]);
	if (!method)
	{
		retValue = "Method not found.";
		return false;
	}

	retValue = methodMap.GenerateMethodDeclaration(method);
	return true;
}

bool CommandScriptHelp(std::vector<std::string> const &args, std::string &retValue) // 0x106D4330
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandScriptHelp@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandScriptHelp
	// std::string &retValue;
	// Scripting::HS::ScriptMethod const *method;
	// Scripting::HS::ScriptMethodMap &methods;

	if (args.size() < 1)
	{
		retValue = "Invalid arguments";
		return false;
	}

	auto &methodMap = Utils::Singleton<Scripting::HS::ScriptMethodMap>::Instance();

	auto *method = methodMap.FindMethod(args[0]);
	if (!method)
	{
		retValue = "Method not found.";
		return false;
	}

	retValue = methodMap.GenerateHelp(method);
	return true;
}

_extern bool _sub_106D3FE0(std::vector<std::string> const &, std::string &);
bool CommandGenerateDoc(std::vector<std::string> const &args, std::string &retValue) // 0x106D3FE0
{
	// `anonymous-namespace'::CommandGenerateDoc
	// static ...; // 0x106D4174
	// static ...; // 0x106D415C
	// static ...; // 0x106D4154
	// std::vector<std::string> const &args;
	// std::string &retValue;
	// std::string documentation;
	// std::ofstream outFile;
	// Scripting::HS::ScriptMethodMap &methods;
	todo("implement");
	bool __result = _sub_106D3FE0(args, retValue);
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Scripting::HS::ScriptMethodMap & Utils::Singleton<Scripting::HS::ScriptMethodMap>::Instance();
