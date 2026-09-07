/* ---------- headers */

#include "Modules/ModuleWeapon.hpp"
#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"
#include "ElDorito.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patches/Weapon.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <locale>
#include <memory>
#include <ostream>
#include <regex>
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
	class ModuleWeapon;
}
namespace Patches
{
	namespace Weapon
	{
		struct WeaponInfo;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Weapon {}
	using namespace Patches::Weapon;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern bool (*IsMainMenu)(); // 0x1135416C
}
/* ---------- public code */

namespace Modules
{
	extern ModuleWeapon* _sub_10A25BA0(Modules::ModuleWeapon *const);
	ModuleWeapon::ModuleWeapon() : ModuleBase(todo_result<std::basic_string<char,std::char_traits<char>,std::allocator<char> >>()) // 0x10A25BA0
	{
		mangled_x86(MANGLED_TODO, "??0ModuleWeapon@Modules@@QAE@XZ");
		// Modules::ModuleWeapon *const this;
		todo("implement");
		_sub_10A25BA0(this);
	}
}

namespace Patches
{
	namespace Weapon
	{
		extern WeaponInfo* _sub_10A26530(Patches::Weapon::WeaponInfo *const);
		_inline WeaponInfo::WeaponInfo() // 0x10A26530
		{
			mangled_x86(MANGLED_TODO, "??0WeaponInfo@Weapon@Patches@@QAE@XZ");
			// Patches::Weapon::WeaponInfo *const this;
			compiler_generated();
			todo("implement");
			_sub_10A26530(this);
		}

		_extern void _sub_10A26580(Patches::Weapon::WeaponInfo *const);
		_inline WeaponInfo::~WeaponInfo() // 0x10A26580
		{
			mangled_x86(MANGLED_TODO, "??1WeaponInfo@Weapon@Patches@@QAE@XZ");
			// Patches::Weapon::WeaponInfo *const this;
			compiler_generated();
			todo("implement");
			_sub_10A26580(this);
		}

		extern WeaponInfo &_sub_10A265D0(Patches::Weapon::WeaponInfo *const, Patches::Weapon::WeaponInfo &);
		_inline Patches::Weapon::WeaponInfo &WeaponInfo::operator=(Patches::Weapon::WeaponInfo &&__that) // 0x10A265D0
		{
			mangled_x86(MANGLED_TODO, "??4WeaponInfo@Weapon@Patches@@QAEAAU012@$$QAU012@@Z");
			// Patches::Weapon::WeaponInfo &__that;
			compiler_generated();
			todo("implement");
			Patches::Weapon::WeaponInfo & __result = _sub_10A265D0(this, __that);
			return __result;
		}
	}
}

/* ---------- private code */
