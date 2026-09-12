/* ---------- headers */

#include "Patches/GamePatches.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
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
#include <initializer_list>
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
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct IGameSystem;
struct begin;
struct end;

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Game {}
	using namespace Patches::Game;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace Game
	{
		extern void ApplyAll();
		extern void RegisterGameSystem(IGameSystem *system);
	}
}

void unused_initialize_hook();
void unused_dispose_hook();
void unused_intialize_for_new_map_hook();
void unused_dispose_from_old_map_hook();
void unused_update_hook();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern std::vector<IGameSystem *> eldewritoGameSystems; // 0x12408340
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Game
	{
		_extern void _sub_108D0640();
		void ApplyAll() // 0x108D0640
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Game@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_108D0640();
		}

		void RegisterGameSystem(IGameSystem *system) // 0x108D0950
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterGameSystem@Game@Patches@@YAXPAUIGameSystem@@@Z");
			// IGameSystem *system;

			eldewritoGameSystems.push_back(system);
		}
	}
}

/* ---------- private code */

_extern void _sub_108D1590();
void unused_initialize_hook() // 0x108D1590
{
	// `anonymous-namespace'::unused_initialize_hook
	// procedure flags: nofpo
	{
		// std::vector<IGameSystem *> &<range>$L0;
		// IGameSystem **<begin>$L0;
		// IGameSystem **<end>$L0;
		{
			// IGameSystem *system;
		}
	}
	// function call : void ()
	todo("implement");
	_sub_108D1590();
}

_extern void _sub_108D14F0();
void unused_dispose_hook() // 0x108D14F0
{
	// `anonymous-namespace'::unused_dispose_hook
	// procedure flags: nofpo
	{
		// std::vector<IGameSystem *> &<range>$L0;
		// IGameSystem **<begin>$L0;
		// IGameSystem **<end>$L0;
		{
			// IGameSystem *system;
		}
	}
	// function call : void ()
	todo("implement");
	_sub_108D14F0();
}

_extern void _sub_108D1630();
void unused_intialize_for_new_map_hook() // 0x108D1630
{
	// `anonymous-namespace'::unused_intialize_for_new_map_hook
	// procedure flags: nofpo
	{
		// std::vector<IGameSystem *> &<range>$L0;
		// IGameSystem **<begin>$L0;
		// IGameSystem **<end>$L0;
		{
			// IGameSystem *system;
		}
	}
	// function call : void ()
	todo("implement");
	_sub_108D1630();
}

_extern void _sub_108D1450();
void unused_dispose_from_old_map_hook() // 0x108D1450
{
	// `anonymous-namespace'::unused_dispose_from_old_map_hook
	// procedure flags: nofpo
	{
		// std::vector<IGameSystem *> &<range>$L0;
		// IGameSystem **<begin>$L0;
		// IGameSystem **<end>$L0;
		{
			// IGameSystem *system;
		}
	}
	// function call : void ()
	todo("implement");
	_sub_108D1450();
}

_extern void _sub_108D16D0();
void unused_update_hook() // 0x108D16D0
{
	// `anonymous-namespace'::unused_update_hook
	// procedure flags: nofpo
	{
		// std::vector<IGameSystem *> &<range>$L0;
		// IGameSystem **<begin>$L0;
		// IGameSystem **<end>$L0;
		{
			// IGameSystem *system;
		}
	}
	// function call : void ()
	todo("implement");
	_sub_108D16D0();
}
