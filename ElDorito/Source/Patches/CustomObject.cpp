/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/object_types.hpp"
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

/* ---------- forward declarations */

struct s_object_type_definition;
namespace
{
	struct s_custom_object_data_definition;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace CustomObjects {}
	using namespace Patches::CustomObjects;
}

/* ---------- constants */

/* ---------- definitions */

namespace
{
	#pragma pack(push, 4)
	struct s_custom_object_data_definition :
		public s_object_type_definition
	{
	};
	#pragma pack(pop)
	static_assert(sizeof(s_custom_object_data_definition) == 244, "Invalid s_custom_object_data_definition size");
}
/* ---------- prototypes */

namespace Patches
{
	namespace CustomObjects
	{
		extern void ApplyAll();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern s_object_type_definition *g_object_type_definitions[16]; // 0x11353250
	extern s_object_type_definition const *g_first_object_type_definition; // 0x12409464
}
/* ---------- public code */

namespace Patches
{
	namespace CustomObjects
	{
		_extern void _sub_10914A40();
		void ApplyAll() // 0x10914A40
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@CustomObjects@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10914A40();
		}
	}
}

/* ---------- private code */
