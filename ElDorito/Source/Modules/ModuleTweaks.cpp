/* ---------- headers */

#include "Modules/ModuleTweaks.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patch.hpp"
#include "Pointer.hpp"

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
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Modules
{
	class ModuleBase;
	class ModuleTweaks;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Ui {}
	using namespace Patches::Ui;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	extern ModuleTweaks* _sub_10A223E0(Modules::ModuleTweaks *const);
	ModuleTweaks::ModuleTweaks() : ModuleBase(todo_result<std::string>()) // 0x10A223E0
	{
		mangled_x86(MANGLED_TODO, "??0ModuleTweaks@Modules@@QAE@XZ");
		// Modules::ModuleTweaks *const this;
		todo("implement");
		_sub_10A223E0(this);
	}
}

/* ---------- private code */
