/* ---------- headers */

#include "Objects/ObjectMessaging.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "mods/mod_package_updater.hpp"
#include "Patches/GamePatches.hpp"

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
#include <deque>
#include <exception>
#include <functional>
#include <limits>
#include <memory>
#include <queue>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

namespace Objects
{
	struct CObjectMessaging;
	struct ObjectMessageSystem;
}

namespace Objects {}
using namespace ::Objects;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Game {}
	using namespace Patches::Game;
}

/* ---------- constants */

/* ---------- definitions */

// Objects::ObjectMessageSystem is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

/* ---------- globals */

namespace Objects
{
	extern ::Objects::ObjectMessageSystem system; // 0x1134DCDC
	extern std::queue<std::function<void __cdecl(void)> > queuedActions; // 0x1138DD58
}

/* ---------- private variables */

/* ---------- public code */

namespace Objects
{
	_extern void _sub_10798290(::Objects::ObjectMessageSystem *const);
	_inline void ObjectMessageSystem::DisposeFromOldMap() // 0x10798290
	{
		mangled_x86(MANGLED_TODO, "?DisposeFromOldMap@ObjectMessageSystem@Objects@@UAEXXZ");
		// Objects::ObjectMessageSystem *const this;
		todo("implement");
		_sub_10798290(this);
	}

	_extern void _sub_107999B0();
	void CObjectMessaging::Init() // 0x107999B0
	{
		mangled_x86(MANGLED_TODO, "?Init@CObjectMessaging@Objects@@SAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_107999B0();
	}

	_extern void _sub_10799950(std::function<void __cdecl(void)> &);
	void CObjectMessaging::EnqueueAction(std::function<void __cdecl(void)> &&action) // 0x10799950
	{
		mangled_x86(MANGLED_TODO, "?EnqueueAction@CObjectMessaging@Objects@@SAX$$QAV?$function@$$A6AXXZ@std@@@Z");
		// std::function<void __cdecl(void)> &action;
		todo("implement");
		_sub_10799950(action);
	}

	_extern void _sub_10799A60();
	void CObjectMessaging::RunActions() // 0x10799A60
	{
		mangled_x86(MANGLED_TODO, "?RunActions@CObjectMessaging@Objects@@SAXXZ");
		// procedure flags: nofpo
		// static ...; // 0x10799B44
		// static ...; // 0x10799B38
		// static ...; // 0x10799B30
		{
			// std::function<void __cdecl(void)> action;
		}
		todo("implement");
		_sub_10799A60();
	}

	_extern void _sub_10799A00();
	void CObjectMessaging::Reset() // 0x10799A00
	{
		mangled_x86(MANGLED_TODO, "?Reset@CObjectMessaging@Objects@@SAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_10799A00();
	}

	_inline ObjectMessageSystem::~ObjectMessageSystem() // 0x10799710
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??1ObjectMessageSystem@Objects@@UAE@XZ");
		// Objects::ObjectMessageSystem *const this;

		compiler_generated();
	}
}

/* ---------- private code */
