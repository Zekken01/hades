/* ---------- headers */

#include "Patches/GamePatches.hpp"
#include "hades/hades.h"

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

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern std::vector<IGameSystem *,std::allocator<IGameSystem *> > eldewritoGameSystems; // 0x12408340
}
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

		_extern void _sub_108D0950(IGameSystem *);
		void RegisterGameSystem(IGameSystem *system) // 0x108D0950
		{
			mangled_x86(MANGLED_TODO, "?RegisterGameSystem@Game@Patches@@YAXPAUIGameSystem@@@Z");
			// IGameSystem *system;
			todo("implement");
			_sub_108D0950(system);
		}
	}
}

/* ---------- private code */
