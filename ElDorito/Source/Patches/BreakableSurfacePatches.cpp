/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
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

struct real_vector3d;
struct s_scenario_location;
namespace
{
	struct s_simulation_breakable_surface_group_state_data;
	struct s_simulation_breakable_surface_break_event_data;
	struct c_breakable_surface_group_handle;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace BreakableSurface {}
	using namespace Patches::BreakableSurface;
}

/* ---------- constants */

/* ---------- definitions */

namespace
{
	struct s_simulation_breakable_surface_group_state_data
	{
		unsigned long surface_bits; // 0x0
	};
	static_assert(sizeof(s_simulation_breakable_surface_group_state_data) == 4, "Invalid s_simulation_breakable_surface_group_state_data size");

	struct s_simulation_breakable_surface_break_event_data
	{
		long instanced_geometry_instance_index; // 0x0
		long surface_index; // 0x4
		s_scenario_location location; // 0x8
		unsigned char __pad0[2]; // 0xA
		real_point3d position; // 0xC
	};
	static_assert(sizeof(s_simulation_breakable_surface_break_event_data) == 24, "Invalid s_simulation_breakable_surface_break_event_data size");

	struct c_breakable_surface_group_handle
	{
		static long create(long, long);
		static long get_bsp_index(long);
		static long get_group_index(long);
	};
	static_assert(sizeof(c_breakable_surface_group_handle) == 1, "Invalid c_breakable_surface_group_handle size");
}
/* ---------- prototypes */

namespace Patches
{
	namespace BreakableSurface
	{
		extern void ApplyAll();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern real_vector3d global_zero3d; // 0x1117520C
	extern long g_breakable_surface_group_gamestate_mapping[16][1024]; // 0x11372CD8
}
/* ---------- public code */

namespace Patches
{
	namespace BreakableSurface
	{
		_extern void _sub_1069BA50();
		void ApplyAll() // 0x1069BA50
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@BreakableSurface@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_1069BA50();
		}
	}
}

/* ---------- private code */
