/* ---------- headers */

#include "hades/hades.h"

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

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Mouse {}
	using namespace Patches::Mouse;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace Mouse
	{
		extern void ApplyAll();
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Mouse
	{
		_extern void _sub_10A8BE00();
		void ApplyAll() // 0x10A8BE00
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Mouse@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A8BE00();
		}
	}
}

/* ---------- private code */
