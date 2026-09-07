/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/effects/particle_emitter.hpp"
#include "Blam/effects/particle_emitter_definitions.hpp"
#include "Blam/effects/particle_states.hpp"
#include "Blam/effects/particle_system.hpp"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_shaders.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/shaders/render_methods_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Modules/ModuleGraphics.hpp"
#include "Patch.hpp"
#include "Pointer.hpp"
#include "Utils/Singleton.hpp"

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
namespace Modules
{
	class ModuleGraphics;
}
namespace
{
	struct s_gpu_vertex_stream;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;

/* ---------- constants */

/* ---------- definitions */

namespace
{
	struct s_gpu_vertex_stream
	{
		void *vertex_data; // 0x0
		unsigned char __pad0[4]; // 0x4
		long offset; // 0x8
		long previous_offset; // 0xC
		long vertex_count; // 0x10
	};
	static_assert(sizeof(s_gpu_vertex_stream) == 20, "Invalid s_gpu_vertex_stream size");
}
//struct render_visible_decals_hook::__l2::c_decal
//{
//	short identifier; // 0x0
//	long parent_system_block_index; // 0x4
//	long parent_system_index; // 0x8
//	long next_index; // 0xC
//};
//static_assert(sizeof(render_visible_decals_hook::__l2::c_decal) == 16, "Invalid render_visible_decals_hook::__l2::c_decal size");

//struct render_visible_decals_hook::__l2::s_render_decal_unknown
//{
//	render_visible_decals_hook::__l2::c_decal *decals[600]; // 0x0
//	long decal_count; // 0x960
//};
//static_assert(sizeof(render_visible_decals_hook::__l2::s_render_decal_unknown) == 2420, "Invalid render_visible_decals_hook::__l2::s_render_decal_unknown size");

/* ---------- prototypes */

extern void effect_system_patches_apply();
extern void effect_system_patches_tick();

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern c_flags<enum e_effect_message_type,unsigned long> g_effect_message_filter; // 0x1240936C
	extern real_vector3d global_zero3d; // 0x111978AC
}
/* ---------- public code */

_extern void _sub_10911EE0();
void effect_system_patches_apply() // 0x10911EE0
{
	mangled_x86(MANGLED_TODO, "?effect_system_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_10911EE0();
}

_extern void _sub_10912BB0();
void effect_system_patches_tick() // 0x10912BB0
{
	mangled_x86(MANGLED_TODO, "?effect_system_patches_tick@@YAXXZ");
	// procedure flags: nofpo
	// Modules::ModuleGraphics &graphics_module;
	todo("implement");
	_sub_10912BB0();
}

/* ---------- private code */
