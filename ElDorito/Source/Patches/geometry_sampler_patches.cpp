/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/shaders/render_methods_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/structures/structure_surfaces.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Debug/DebugDraw.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "Utils/Singleton.hpp"

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
#include <exception>
#include <functional>
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

class c_rasterizer_vertex_buffer;
struct real_vector3d;
namespace
{
	struct s_structure_lighting_data;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace geometry_sampler_patches {}
	using namespace Patches::geometry_sampler_patches;
}

/* ---------- constants */

/* ---------- definitions */

namespace
{
	struct s_structure_lighting_data
	{
		long lightprobe_index; // 0x0
		long per_vertex_count; // 0x4
		long per_vertex_stride; // 0x8
		void const *per_pixel_data; // 0xC
		void const *per_vertex_data; // 0x10
		void set_per_vertex_buffer(c_rasterizer_vertex_buffer *);
		void set_per_pixel_buffer(c_rasterizer_vertex_buffer *);
		void set_lightprobe_index(long);
		s_structure_lighting_data(); /* compiler_generated() */
	};
	static_assert(sizeof(s_structure_lighting_data) == 20, "Invalid s_structure_lighting_data size");
}
/* ---------- prototypes */

namespace Patches
{
	namespace geometry_sampler_patches
	{
		extern void ApplyAll();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern real_vector3d global_down3d; // 0x11197B50
}
/* ---------- public code */

namespace Patches
{
	namespace geometry_sampler_patches
	{
		_extern void _sub_1091BF20();
		void ApplyAll() // 0x1091BF20
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@geometry_sampler_patches@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_1091BF20();
		}
	}
}

/* ---------- private code */
