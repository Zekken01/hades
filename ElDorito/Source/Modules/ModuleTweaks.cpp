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
	ModuleTweaks::ModuleTweaks() : ModuleBase("Tweaks") /* hades-mem-init: : ModuleBase(todo_result<std::string>()) */ // 0x10A223E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ModuleTweaks@Modules@@QAE@XZ");
		// Modules::ModuleTweaks *const this;

		VarDisableReactorFog = AddVariableInt("DisableReactorFog", "disablereactorfog", "Disable the fog effects around the moving platforms on the Reactor map to increase performance.", eCommandFlagsArchived, 0);
		VarDisableReactorFog->ValueIntMin = 0;
		VarDisableReactorFog->ValueIntMax = 1;
		VarDisableWeaponOutline = AddVariableInt("DisableWeaponOutline", "disableweaponoutline", "Disables the outline effect on weapons and equipment.", eCommandFlagsArchived, 0);
		VarDisableWeaponOutline->ValueIntMin = 0;
		VarDisableWeaponOutline->ValueIntMax = 1;
		VarDisableHitMarkers = AddVariableInt("DisableHitMarkers", "disablehitmarkers", "Disables weapon hitmarkers.", eCommandFlagsArchived, 0);
		VarDisableHitMarkers->ValueIntMin = 0;
		VarDisableHitMarkers->ValueIntMax = 1;
		VarFlatHUD = AddVariableInt("FlatHUD", "flathud", "Removes distortion from the HUD.", eCommandFlagsArchived, 0);
		VarFlatHUD->ValueIntMin = 0;
		VarFlatHUD->ValueIntMax = 1;
	}
}

/* ---------- private code */
