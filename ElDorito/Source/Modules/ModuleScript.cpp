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

bool CommandGenerateMethodDecl(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &args, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &retValue);
bool CommandScriptHelp(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &args, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &retValue);
bool CommandGenerateDoc(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &args, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &retValue);

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
	ModuleScript::ModuleScript() : ModuleBase(todo_result<std::basic_string<char,std::char_traits<char>,std::allocator<char> >>()) // 0x106D3590
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
		_inline ScriptMethodMap::ScriptMethodMap() // 0x106D3B40
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0ScriptMethodMap@HS@Scripting@@QAE@XZ");
			// Scripting::HS::ScriptMethodMap *const this;

			compiler_generated();
		}
	}
}

namespace Modules
{
	_inline ModuleBase::~ModuleBase() // 0x106D3ED0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??1ModuleBase@Modules@@QAE@XZ");
		// Modules::ModuleBase *const this;

		compiler_generated();
	}
}

namespace Scripting
{
	namespace HS
	{
		_inline ScriptMethod::~ScriptMethod() // 0x106D3F20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1ScriptMethod@HS@Scripting@@QAE@XZ");
			// Scripting::HS::ScriptMethod *const this;

			compiler_generated();
		}
	}
}

/* ---------- private code */

_extern bool _sub_106D4200(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGenerateMethodDecl(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &args, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &retValue) // 0x106D4200
{
	// `anonymous-namespace'::CommandGenerateMethodDecl
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &retValue;
	// Scripting::HS::ScriptMethod const *method;
	// Scripting::HS::ScriptMethodMap &methods;
	todo("implement");
	bool __result = _sub_106D4200(args, retValue);
	return __result;
}

_extern bool _sub_106D4330(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandScriptHelp(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &args, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &retValue) // 0x106D4330
{
	// `anonymous-namespace'::CommandScriptHelp
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &retValue;
	// Scripting::HS::ScriptMethod const *method;
	// Scripting::HS::ScriptMethodMap &methods;
	todo("implement");
	bool __result = _sub_106D4330(args, retValue);
	return __result;
}

_extern bool _sub_106D3FE0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandGenerateDoc(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &args, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &retValue) // 0x106D3FE0
{
	// `anonymous-namespace'::CommandGenerateDoc
	// static ...; // 0x106D4174
	// static ...; // 0x106D415C
	// static ...; // 0x106D4154
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &args;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &retValue;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > documentation;
	// std::basic_ofstream<char,std::char_traits<char> > outFile;
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
