/* ---------- headers */

#include "Modules/ModuleScript.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/tag_files/tag_groups.hpp"
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
		extern ScriptMethodMap* _sub_106D3B40(Scripting::HS::ScriptMethodMap *const);
		_inline ScriptMethodMap::ScriptMethodMap() // 0x106D3B40
		{
			mangled_x86(MANGLED_TODO, "??0ScriptMethodMap@HS@Scripting@@QAE@XZ");
			// Scripting::HS::ScriptMethodMap *const this;
			compiler_generated();
			todo("implement");
			_sub_106D3B40(this);
		}
	}
}

namespace Modules
{
	_extern void _sub_106D3ED0(Modules::ModuleBase *const);
	_inline ModuleBase::~ModuleBase() // 0x106D3ED0
	{
		mangled_x86(MANGLED_TODO, "??1ModuleBase@Modules@@QAE@XZ");
		// Modules::ModuleBase *const this;
		compiler_generated();
		todo("implement");
		_sub_106D3ED0(this);
	}
}

namespace Scripting
{
	namespace HS
	{
		_extern void _sub_106D3F20(Scripting::HS::ScriptMethod *const);
		_inline ScriptMethod::~ScriptMethod() // 0x106D3F20
		{
			mangled_x86(MANGLED_TODO, "??1ScriptMethod@HS@Scripting@@QAE@XZ");
			// Scripting::HS::ScriptMethod *const this;
			compiler_generated();
			todo("implement");
			_sub_106D3F20(this);
		}
	}
}

/* ---------- private code */
