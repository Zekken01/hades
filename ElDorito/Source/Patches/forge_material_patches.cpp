/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_component.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Forge/Geoemetry.hpp"
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

namespace
{
	struct c_global_material_type;
}

namespace Forge {}
using namespace ::Forge;
namespace Forge
{
	namespace Reforge {}
	using namespace Forge::Reforge;
}

/* ---------- constants */

/* ---------- definitions */

namespace
{
	struct c_global_material_type
	{
		short material_index; // 0x0
	};
	static_assert(sizeof(c_global_material_type) == 2, "Invalid c_global_material_type size");
}
/* ---------- prototypes */

extern void forge_material_patches_apply();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_109186F0();
void forge_material_patches_apply() // 0x109186F0
{
	mangled_x86(MANGLED_TODO, "?forge_material_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_109186F0();
}

/* ---------- private code */
