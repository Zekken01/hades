/* ---------- headers */

#include "Modules/ModuleTime.hpp"
#include "hades/hades.h"

#include "Modules/ModuleBase.hpp"

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
#include <limits>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

namespace Modules
{
	class ModuleBase;
	class ModuleTime;
}

namespace Utils {}
using namespace ::Utils;
namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace VariableSynchronization {}
	using namespace Server::VariableSynchronization;
}

namespace Modules {}
using namespace ::Modules;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Server { namespace VariableSynchronization { extern void Synchronize(Modules::Command *serverVariable, Modules::Command *clientVariable); } }  // hades: added for 0x10A22130

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	ModuleTime::ModuleTime() : ModuleBase("Time") /* hades-mem-init: : ModuleBase(todo_result<std::string>()) */ // 0x10A22130
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ModuleTime@Modules@@QAE@XZ");

		VarSpeed = AddVariableFloat("GameSpeed", "game_speed", "The game's speed", eCommandFlagsHostOnly, 1.0f);
		VarSpeed->ValueFloatMin = 0.0f;
		VarSpeed->ValueFloatMax = 10.0f;
		VarSpeedClient = AddVariableFloat("GameSpeedClient", "game_speed_client", "The game's speed", eCommandFlagsInternal, 1.0f);
		Server::VariableSynchronization::Synchronize(VarSpeed, VarSpeedClient);
	}
}

/* ---------- private code */
