/* ---------- headers */

#include "Modules/ModuleWeapon.hpp"
#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
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

struct begin;
struct end;
struct real_vector3d;
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

bool CommandWeaponOffset(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandWeaponOffsetReset(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandLoadWeaponsJSON(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandSaveWeaponsJSON(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandNewWeaponsJSON(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandDeleteWeaponsJSON(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandGetEquippedWeaponInfo(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandListWeaponConfigsJSON(std::vector<std::string> const &arguments, std::string &returnInfo);
real_vector3d ToOffset(std::string I, std::string J, std::string K);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern bool (*IsMainMenu)(); // 0x1135416C
}
using namespace hades_file_local;
/* ---------- public code */

namespace Modules
{
	extern ModuleWeapon* _sub_10A25BA0(Modules::ModuleWeapon *const);
	ModuleWeapon::ModuleWeapon() : ModuleBase(todo_result<std::string>()) // 0x10A25BA0
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
		_inline WeaponInfo::WeaponInfo() // 0x10A26530
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0WeaponInfo@Weapon@Patches@@QAE@XZ");
			// Patches::Weapon::WeaponInfo *const this;

			compiler_generated();
		}

		_inline WeaponInfo::~WeaponInfo() // 0x10A26580
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1WeaponInfo@Weapon@Patches@@QAE@XZ");
			// Patches::Weapon::WeaponInfo *const this;

			compiler_generated();
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

_extern bool _sub_10A27430(std::vector<std::string> const &, std::string &);
bool CommandWeaponOffset(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A27430
{
	// `anonymous-namespace'::CommandWeaponOffset
	// static ...; // 0x10A27A0C
	// static ...; // 0x10A27A01
	// static ...; // 0x10A279F6
	// static ...; // 0x10A279EF
	// static ...; // 0x10A279EC
	// static ...; // 0x10A279A4
	// static ...; // 0x10A2799C
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::stringstream ss;
	// real_vector3d offset;
	// Patches::Weapon::WeaponInfo weapon;
	{
		// std::string type;
	}
	{
		// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
		// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
	}
	todo("implement");
	bool __result = _sub_10A27430(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A27BA0(std::vector<std::string> const &, std::string &);
bool CommandWeaponOffsetReset(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A27BA0
{
	// `anonymous-namespace'::CommandWeaponOffsetReset
	// static ...; // 0x10A27E5F
	// static ...; // 0x10A27E5C
	// static ...; // 0x10A27E38
	// static ...; // 0x10A27E30
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::stringstream ss;
	// Patches::Weapon::WeaponInfo weapon;
	{
		// std::string type;
	}
	// function call : bool (*)()
	todo("implement");
	bool __result = _sub_10A27BA0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A26E70(std::vector<std::string> const &, std::string &);
bool CommandLoadWeaponsJSON(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A26E70
{
	// `anonymous-namespace'::CommandLoadWeaponsJSON
	// static ...; // 0x10A27048
	// static ...; // 0x10A27040
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// bool changeJson;
	// std::string file;
	{
		// std::vector<std::string> &<range>$L0;
		// std::string *<begin>$L0;
		// std::string *<end>$L0;
		{
			// std::string &name;
		}
	}
	todo("implement");
	bool __result = _sub_10A26E70(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A27390(std::vector<std::string> const &, std::string &);
bool CommandSaveWeaponsJSON(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A27390
{
	// `anonymous-namespace'::CommandSaveWeaponsJSON
	// std::string &returnInfo;
	// function call : bool (*)()
	todo("implement");
	bool __result = _sub_10A27390(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A270E0(std::vector<std::string> const &, std::string &);
bool CommandNewWeaponsJSON(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A270E0
{
	// `anonymous-namespace'::CommandNewWeaponsJSON
	// static ...; // 0x10A272F0
	// static ...; // 0x10A272D8
	// static ...; // 0x10A272D0
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::string newConfigName;
	{
		// std::regex pattern;
	}
	// function call : bool (*)()
	todo("implement");
	bool __result = _sub_10A270E0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A26650(std::vector<std::string> const &, std::string &);
bool CommandDeleteWeaponsJSON(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A26650
{
	// `anonymous-namespace'::CommandDeleteWeaponsJSON
	// static ...; // 0x10A268A4
	// static ...; // 0x10A2688C
	// static ...; // 0x10A26884
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::string newConfigName;
	{
		// std::regex pattern;
	}
	// function call : bool (*)()
	todo("implement");
	bool __result = _sub_10A26650(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A26960(std::vector<std::string> const &, std::string &);
bool CommandGetEquippedWeaponInfo(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A26960
{
	// `anonymous-namespace'::CommandGetEquippedWeaponInfo
	// static ...; // 0x10A26CAE
	// static ...; // 0x10A26CA3
	// static ...; // 0x10A26C98
	// static ...; // 0x10A26C68
	// static ...; // 0x10A26C60
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// Patches::Weapon::WeaponInfo equippedWeapon;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
	// real_vector3d equippedWeaponOffset;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
	// function call : bool (*)()
	todo("implement");
	bool __result = _sub_10A26960(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10A26DB0(std::vector<std::string> const &, std::string &);
bool CommandListWeaponConfigsJSON(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x10A26DB0
{
	// `anonymous-namespace'::CommandListWeaponConfigsJSON
	// std::string &returnInfo;
	{
		// std::vector<std::string> &<range>$L0;
		// std::string *<begin>$L0;
		// std::string *<end>$L0;
		{
			// std::string &name;
		}
	}
	todo("implement");
	bool __result = _sub_10A26DB0(arguments, returnInfo);
	return __result;
}

extern real_vector3d _sub_10A27F20(std::string, std::string, std::string);
real_vector3d ToOffset(std::string I, std::string J, std::string K) // 0x10A27F20
{
	// `anonymous-namespace'::ToOffset
	// std::string K;
	todo("implement");
	real_vector3d __result = _sub_10A27F20(I, J, K);
	return __result;
}
