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

namespace Objects
{
	// hades: moved from hades/recovered_types.h onto its real base (was hades::polymorphic_bytes)
	struct ObjectMessageSystem :
		public IGameSystem
	{
		// mangled_x86(MANGLED_KNOWN_GOOD, "??1ObjectMessageSystem@Objects@@UAE@XZ"); defaulted on its declaration, which skips the vfptr store
		virtual ~ObjectMessageSystem() = default; // 0x10799710
		virtual void Initialize();
		virtual void InitializeForNewMap();
		virtual void DisposeFromOldMap();
		virtual void Dispose();
		virtual void Update();
	};
	static_assert32(sizeof(ObjectMessageSystem) == 4, "Invalid ObjectMessageSystem size");
}

// Objects::ObjectMessageSystem is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

/* ---------- globals */

namespace Objects
{
	::Objects::ObjectMessageSystem system; // 0x1134DCDC
	std::queue<std::function<void __cdecl(void)> > queuedActions; // 0x1138DD58
}

/* ---------- private variables */

/* ---------- public code */

namespace Objects
{
	_inline void ObjectMessageSystem::DisposeFromOldMap() // 0x10798290
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?DisposeFromOldMap@ObjectMessageSystem@Objects@@UAEXXZ");
		// Objects::ObjectMessageSystem *const this;

		CObjectMessaging::Reset();
	}

	void CObjectMessaging::Init() // 0x107999B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Init@CObjectMessaging@Objects@@SAXXZ");
		// procedure flags: nofpo

		Patches::Game::RegisterGameSystem((IGameSystem *)&Objects::system);
	}

	void CObjectMessaging::EnqueueAction(std::function<void __cdecl(void)> &&action) // 0x10799950
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?EnqueueAction@CObjectMessaging@Objects@@SAX$$QAV?$function@$$A6AXXZ@std@@@Z");
		// std::function<void __cdecl(void)> &action;

		queuedActions.push(std::move(action));
	}

	void CObjectMessaging::RunActions() // 0x10799A60
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?RunActions@CObjectMessaging@Objects@@SAXXZ");
		// procedure flags: nofpo
		// static ...; // 0x10799B44
		// static ...; // 0x10799B38
		// static ...; // 0x10799B30
			// std::function<void __cdecl(void)> action;

		while (!queuedActions.empty())
		{
			std::function<void __cdecl(void)> action = std::move(queuedActions.front());
			queuedActions.pop();
			action();
		}
	}

	void CObjectMessaging::Reset() // 0x10799A00
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Reset@CObjectMessaging@Objects@@SAXXZ");
		// procedure flags: nofpo

		while (!Objects::queuedActions.empty())
		{
			Objects::queuedActions.pop();
		}
	}
}

/* ---------- private code */
