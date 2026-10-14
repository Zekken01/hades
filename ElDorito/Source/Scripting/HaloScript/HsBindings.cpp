/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Scripting/HaloScript/HsMethodMap.hpp"
#include "Utils/Singleton.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <list>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Scripting
{
	namespace HS
	{
		class ScriptMethodMap;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Scripting {}
using namespace ::Scripting;
namespace Scripting
{
	namespace HS {}
	using namespace Scripting::HS;
}

namespace Player
{
	namespace PlayerPodium {}
	using namespace Player::PlayerPodium;
}

namespace Player {}
using namespace ::Player;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Scripting { namespace HS { namespace Methods { namespace Player { extern void RegisterMethods(Scripting::HS::ScriptMethodMap &methods); } namespace PlayerPodium { extern void RegisterMethods(Scripting::HS::ScriptMethodMap &methods); } namespace Multiplayer { extern void RegisterMethods(Scripting::HS::ScriptMethodMap &methods); } namespace Object { extern void RegisterMethods(Scripting::HS::ScriptMethodMap &methods); } } } }  // hades: added for 0x106ECC30

namespace Scripting
{
	namespace HS
	{
		extern void RegisterBindings();
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Scripting
{
	namespace HS
	{
		void RegisterBindings() // 0x106ECC30
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterBindings@HS@Scripting@@YAXXZ");
			// procedure flags: nofpo
			// Scripting::HS::ScriptMethodMap &methods;

			Scripting::HS::ScriptMethodMap &methods = Utils::Singleton<Scripting::HS::ScriptMethodMap>::Instance();
			Methods::Player::RegisterMethods(methods);
			Methods::PlayerPodium::RegisterMethods(methods);
			Methods::Multiplayer::RegisterMethods(methods);
			Methods::Object::RegisterMethods(methods);
			methods.Finalize();
		}
	}
}

/* ---------- private code */
