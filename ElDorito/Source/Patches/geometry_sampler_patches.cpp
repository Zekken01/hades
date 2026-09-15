/* ---------- headers */

#include "hades/hades.h"

#include "Blam/ai/actor.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/geometry/geometry_definitions.hpp"
#include "Blam/geometry/geometry_sampler.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/collision_bsp.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/render_structure.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/shaders/render_methods_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/structures/structure_bsp_definitions.hpp"
#include "Blam/structures/structure_surfaces.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/visibility/visibility.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
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

class c_rasterizer_index_buffer;
class c_rasterizer_vertex_buffer;
struct c_collision_bsp_reference;
struct c_structure_surface;
struct collision_bsp;
struct collision_surface;
struct real_plane3d;
struct real_point3d;
struct real_vector3d;
struct s_compression_info;
struct s_geometry_sample;
struct s_geometry_test_result;
struct s_large_collision_surface;
struct s_mesh;
struct s_rasterizer_vertex_rigid;
struct s_rasterizer_vertex_world;
struct s_render_geometry;
struct s_scenario_lightmap_bsp_data;
struct s_scenario_structure_bsp;
struct s_structure_cluster;
struct s_structure_instanced_geometry_instance;
struct s_structure_plane;
struct s_uncompressed_triangle;
namespace hades_file_local
{
	struct s_structure_lighting_data;
}
using namespace hades_file_local;

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

namespace hades_file_local
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
using namespace hades_file_local;
/* ---------- prototypes */

class c_geometry_sampler { public: static long (*interpolate_geometry_samples)(s_geometry_sample *, s_geometry_sample *, float, char); };  // hades: added for 0x1091EE50

namespace Patches
{
	namespace geometry_sampler_patches
	{
		extern void ApplyAll();
	}
}

long interpoloate_lighting_sample_hook(s_geometry_sample *current_sample, s_geometry_sample *next_sample, float interpolation_parameter, char a4);
_inline void extract_world_vertex(s_render_geometry const *render_geometry, long mesh_index, long triangle_index, s_uncompressed_triangle *triangle);
_inline void extract_rigid_vertex(s_render_geometry const *render_geometry, long mesh_index, long triangle_index, long compression_index, s_uncompressed_triangle *triangle);
bool get_structure_lighting(long bsp_index, long section_index, long instance_index, s_structure_lighting_data *lighting);
_inline void barycentric_coordinates(real_point3d const &p, real_point3d const &a, real_point3d const &b, real_point3d const &c, float &u, float &v, float &w);
void closest_point_on_triangle(real_point3d const &p, real_point3d const &a, real_point3d const &b, real_point3d const &c, real_point3d &closest_point);
void get_surface_plane(real_plane3d *plane, c_structure_surface const &structure_surface);
long find_best_triangle_closest(c_structure_surface const &structure_surface, s_render_geometry const *render_geometry, real_point3d const &point, s_uncompressed_triangle &triangle, float &s, float &t);
long find_best_triangle_h3(c_structure_surface const &structure_surface, s_render_geometry const *render_geometry, real_point3d const &point, s_uncompressed_triangle &triangle, float &s, float &t);
bool geometry_test_collision_result_impl(long bsp_index, long object_index, long instance_index, long surface_index, real_point3d const *test_point, bool unknown_flag, bool find_material_flag, bool *out_test_result_valid, s_geometry_test_result *test_result);
_inline bool geometry_test_collision_result_hook(long bsp_index, long object_index, long instance_index, long surface_index, real_point3d const *test_point, bool unknown_flag, bool find_material_flag, bool *out_test_result_valid, s_geometry_test_result *test_result);
void sample_airprobes_hook();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern real_vector3d global_down3d; // 0x11197B50
}
using namespace hades_file_local;
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

_inline void s_structure_lighting_data::set_per_vertex_buffer(c_rasterizer_vertex_buffer *buffer) // 0x1091F100
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_per_vertex_buffer@s_structure_lighting_data@hades_file_local@@QAEXPAVc_rasterizer_vertex_buffer@@@Z");
	// `anonymous-namespace'::s_structure_lighting_data::set_per_vertex_buffer
	// c_rasterizer_vertex_buffer *buffer;

	per_vertex_count = buffer->get_vertex_count();
	per_vertex_stride = buffer->get_vertex_stride();
	per_vertex_data = buffer->get_data();
}

_inline void s_structure_lighting_data::set_per_pixel_buffer(c_rasterizer_vertex_buffer *buffer) // 0x1091F0A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_per_pixel_buffer@s_structure_lighting_data@hades_file_local@@QAEXPAVc_rasterizer_vertex_buffer@@@Z");
	// `anonymous-namespace'::s_structure_lighting_data::set_per_pixel_buffer
	// c_rasterizer_vertex_buffer *buffer;

	per_pixel_data = buffer->get_data();
}

_inline void s_structure_lighting_data::set_lightprobe_index(long index) // 0x1091F070
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_lightprobe_index@s_structure_lighting_data@hades_file_local@@QAEXJ@Z");
	// `anonymous-namespace'::s_structure_lighting_data::set_lightprobe_index
	// long index;

	lightprobe_index = index;
}

// mangled_x86(MANGLED_DEFAULT, "??0s_structure_lighting_data@hades_file_local@@QAE@XZ"); no body to assert in
_inline s_structure_lighting_data::s_structure_lighting_data() // 0x1091BB60
{
	lightprobe_index = -1;
	per_vertex_count = 0;
	per_vertex_stride = 0;
	per_pixel_data = nullptr;
	per_vertex_data = nullptr;
}

long interpoloate_lighting_sample_hook(s_geometry_sample *current_sample, s_geometry_sample *next_sample, float interpolation_parameter, char a4) // 0x1091EE50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?interpoloate_lighting_sample_hook@@YAJPAUs_geometry_sample@@0MD@Z");
	// `anonymous-namespace'::interpoloate_lighting_sample_hook
	// char a4;
	// function call : long (*)(s_geometry_sample *, s_geometry_sample *, float, char)

	return c_geometry_sampler::interpolate_geometry_samples(current_sample, next_sample, interpolation_parameter / 2.0f, 1);
}

_inline void extract_world_vertex(s_render_geometry const *render_geometry, long mesh_index, long triangle_index, s_uncompressed_triangle *triangle) // 0x1091CD70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?extract_world_vertex@@YAXPBUs_render_geometry@@JJPAUs_uncompressed_triangle@@@Z");
	// `anonymous-namespace'::extract_world_vertex
	// s_uncompressed_triangle *triangle;
	// c_rasterizer_index_buffer const *index_buffer;
	// s_rasterizer_vertex_world *const world_vertices;
	// c_rasterizer_vertex_buffer const *world_vertex_buffer;
	// s_mesh const *mesh;
	// unsigned short *const indices;
	// function call : c_rasterizer_vertex_buffer *(*const)(s_render_geometry const *, long)
	// function call : c_rasterizer_index_buffer *(*const)(s_render_geometry const *, long)
	// function call : void (*const)(s_rasterizer_vertex_world *, long, unsigned short const *, unsigned long, s_uncompressed_triangle *)

	s_mesh const *mesh = &render_geometry->meshes[mesh_index];
	c_rasterizer_vertex_buffer *world_vertex_buffer = ((c_rasterizer_vertex_buffer *(__cdecl *)(s_render_geometry const *, long))0x78C930)(render_geometry, mesh->vertex_buffer_indices[0]);
	c_rasterizer_index_buffer *index_buffer = ((c_rasterizer_index_buffer *(__cdecl *)(s_render_geometry const *, long))0x78C870)(render_geometry, mesh->index_buffer_indices[0]);
	unsigned short const *indices = (unsigned short const *)index_buffer->get_data();
	void const *world_vertices = world_vertex_buffer->get_data();
	((void(__cdecl *)(void const *, long, unsigned short const *, long, s_uncompressed_triangle *))0x7520D0)(world_vertices, triangle_index, indices, world_vertex_buffer->get_vertex_count(), triangle);
}

_extern void _sub_1091CC20(s_render_geometry const *, long, long, long, s_uncompressed_triangle *);
_inline void extract_rigid_vertex(s_render_geometry const *render_geometry, long mesh_index, long triangle_index, long compression_index, s_uncompressed_triangle *triangle) // 0x1091CC20
{
	// `anonymous-namespace'::extract_rigid_vertex
	// s_uncompressed_triangle *triangle;
	// s_compression_info const *compression_info;
	// c_rasterizer_vertex_buffer *const rigid_vertex_buffer;
	// c_rasterizer_index_buffer *const index_buffer;
	// s_rasterizer_vertex_rigid *const rigid_vertex;
	// s_mesh const *mesh;
	// unsigned short *const indices;
	// function call : c_rasterizer_vertex_buffer *(*const)(s_render_geometry const *, long)
	// function call : c_rasterizer_index_buffer *(*const)(s_render_geometry const *, long)
	// function call : void (*const)(s_rasterizer_vertex_rigid const *, s_compression_info const *, long, unsigned short const *, unsigned long, s_uncompressed_triangle *)
	todo("implement");
	_sub_1091CC20(render_geometry, mesh_index, triangle_index, compression_index, triangle);
}

_extern bool _sub_1091E630(long, long, long, s_structure_lighting_data *);
bool get_structure_lighting(long bsp_index, long section_index, long instance_index, s_structure_lighting_data *lighting) // 0x1091E630
{
	// `anonymous-namespace'::get_structure_lighting
// $LN7:
	// long bsp_index;
	// long section_index;
	// long instance_index;
	// s_structure_lighting_data *lighting;
	// s_scenario_lightmap_bsp_data *bsp_lightmap_data;
	// s_render_geometry *render_geometry;
	// s_scenario_structure_bsp *bsp;
	{
		// s_structure_instanced_geometry_instance *instance;
		{
			// long lod_index;
			{
				// long vertex_buffer_index;
			}
		}
		{
			// long mesh_index;
		}
	}
	{
		// long lightmap_bsp_type;
		{
			// long instance_data_index;
			{
				// long per_vertex_buffer_index;
			}
		}
		{
			// s_structure_cluster *const cluster;
			{
				// s_mesh const *mesh;
			}
		}
	}
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : s_scenario_lightmap_bsp_data *(*const)(long)
	// function call : s_render_geometry *(*const)(long)
	// function call : c_rasterizer_vertex_buffer *(*const)(s_render_geometry const *, long)
	// function call : c_rasterizer_vertex_buffer *(*const)(s_scenario_lightmap_bsp_data *, long)
	// function call : long (*const)(long)
	// function call : c_rasterizer_vertex_buffer *(*const)(s_render_geometry const *, long)
	// function call : c_rasterizer_vertex_buffer *(*const)(s_render_geometry const *, long)
	todo("implement");
	bool __result = _sub_1091E630(bsp_index, section_index, instance_index, lighting);
	return __result;
}

_extern void _sub_1091C250(real_point3d const &, real_point3d const &, real_point3d const &, real_point3d const &, float &, float &, float &);
_inline void barycentric_coordinates(real_point3d const &p, real_point3d const &a, real_point3d const &b, real_point3d const &c, float &u, float &v, float &w) // 0x1091C250
{
	// `anonymous-namespace'::barycentric_coordinates
	// real_point3d const &a;
	// real_point3d const &b;
	// real_point3d const &c;
	// float &u;
	// float &v;
	// float &w;
	// real_vector3d ac;
	// real_vector3d ap;
	// float const d01;
	// float const denom;
	// float const d00;
	// real_vector3d ab;
	// float const d21;
	// float const d11;
	// float const d20;
	todo("implement");
	_sub_1091C250(p, a, b, c, u, v, w);
}

_extern void _sub_1091C560(real_point3d const &, real_point3d const &, real_point3d const &, real_point3d const &, real_point3d &);
void closest_point_on_triangle(real_point3d const &p, real_point3d const &a, real_point3d const &b, real_point3d const &c, real_point3d &closest_point) // 0x1091C560
{
	// `anonymous-namespace'::closest_point_on_triangle
	// static ...; // 0x1091CAB6
	// static ...; // 0x1091CAB3
	// static ...; // 0x1091CAB0
	// static ...; // 0x1091CA5C
	// static ...; // 0x1091CA54
	// real_point3d const &p;
	// real_point3d const &a;
	// real_point3d const &b;
	// real_point3d const &c;
	// real_point3d &closest_point;
	// float u;
	// float w;
	// float v;
	{
		// bool const sw;
		// bool const su;
		// bool const sv;
		{
			// real_point3d r;
			// real_vector3d qr;
			// float const length;
			// real_point3d q;
			// real_vector3d pq;
			{
				// float const t;
			}
		}
	}
	todo("implement");
	_sub_1091C560(p, a, b, c, closest_point);
}

_extern void _sub_1091EA70(real_plane3d *, c_structure_surface const &);
void get_surface_plane(real_plane3d *plane, c_structure_surface const &structure_surface) // 0x1091EA70
{
	// `anonymous-namespace'::get_surface_plane
	// static ...; // 0x1091EC04
	// static ...; // 0x1091EBFC
	// real_plane3d *plane;
	// c_structure_surface const &structure_surface;
	// bool negated;
	// c_collision_bsp_reference collision_bsp;
	{
		// s_large_collision_surface *const surface;
	}
	{
		// collision_surface *const surface;
	}
	todo("implement");
	_sub_1091EA70(plane, structure_surface);
}

_extern long _sub_1091CEA0(c_structure_surface const &, s_render_geometry const *, real_point3d const &, s_uncompressed_triangle &, float &, float &);
long find_best_triangle_closest(c_structure_surface const &structure_surface, s_render_geometry const *render_geometry, real_point3d const &point, s_uncompressed_triangle &triangle, float &s, float &t) // 0x1091CEA0
{
	// `anonymous-namespace'::find_best_triangle_closest
	// static ...; // 0x1091D282
	// static ...; // 0x1091D280
	// static ...; // 0x1091D27E
	// static ...; // 0x1091D27C
	// static ...; // 0x1091D210
	// static ...; // 0x1091D208
	// c_structure_surface const &structure_surface;
	// s_render_geometry const *render_geometry;
	// real_point3d const &point;
	// s_uncompressed_triangle &triangle;
	// float &s;
	// float &t;
	// long end_index;
	// long best_triangle_index;
	// long first_index;
	// float min_point_distance;
	// real_plane3d surface_plane;
	// real_point3d min_point;
	{
		// long i;
		{
			// long const vertex_index;
			// real_vector3d v1;
			// s_structure_plane const *triangle_mapping;
			// real_vector3d triangle_normal;
			// real_point3d closest_point;
			// long const mesh_index;
			// real_vector3d v2;
			// float const distance;
		}
	}
	{
		// float u;
		// long const vertex_index;
		// float w;
		// long const mesh_index;
		// float v;
	}
	todo("implement");
	long __result = _sub_1091CEA0(structure_surface, render_geometry, point, triangle, s, t);
	return __result;
}

_extern long _sub_1091D3D0(c_structure_surface const &, s_render_geometry const *, real_point3d const &, s_uncompressed_triangle &, float &, float &);
long find_best_triangle_h3(c_structure_surface const &structure_surface, s_render_geometry const *render_geometry, real_point3d const &point, s_uncompressed_triangle &triangle, float &s, float &t) // 0x1091D3D0
{
	// `anonymous-namespace'::find_best_triangle_h3
	// static ...; // 0x1091D654
	// c_structure_surface const &structure_surface;
	// s_render_geometry const *render_geometry;
	// real_point3d const &point;
	// s_uncompressed_triangle &triangle;
	// float &s;
	// float &t;
	// float min_area;
	// long const end_index;
	// long best_triangle_index;
	// long const first_index;
	// float min_s;
	// float min_t;
	{
		// long i;
		{
			// long const vertex_index;
			// float t;
			// float s;
			// s_structure_plane const *triangle_mapping;
			// long const mesh_index;
			// float const a;
		}
	}
	{
		// long const vertex_index;
		// long const mesh_index;
	}
	// function call : float (*const)(real_point3d const *, real_point3d const *, real_point3d const *, real_point3d const *, float *, float *)
	todo("implement");
	long __result = _sub_1091D3D0(structure_surface, render_geometry, point, triangle, s, t);
	return __result;
}

_extern bool _sub_1091D7B0(long, long, long, long, real_point3d const *, bool, bool, bool *, s_geometry_test_result *);
bool geometry_test_collision_result_impl(long bsp_index, long object_index, long instance_index, long surface_index, real_point3d const *test_point, bool unknown_flag, bool find_material_flag, bool *out_test_result_valid, s_geometry_test_result *test_result) // 0x1091D7B0
{
	// `anonymous-namespace'::geometry_test_collision_result_impl
	// long bsp_index;
	// long object_index;
	// long instance_index;
	// long surface_index;
	// real_point3d const *test_point;
	// bool unknown_flag;
	// bool find_material_flag;
	// bool *out_test_result_valid;
	// s_geometry_test_result *test_result;
	{
		// long (*const object_has_unknown_lighting)(long);
		// long (*const object_has_light_volume_samples)(long);
	}
	{
		// s_scenario_lightmap_bsp_data *const bsp_lightmap_data;
		// float t;
		// __int32 const quality;
		// long section_index;
		// float s;
		// s_render_geometry *const render_geometry;
		// s_uncompressed_triangle triangle;
		// s_scenario_structure_bsp *structure_bsp;
		// long triangle_index;
		// s_structure_lighting_data lighting;
		// real_point3d point;
		// long triangle_vertex_index;
		// c_structure_surface structure_surface;
	}
	// function call : long (*const)(long)
	// function call : long (*const)(long)
	// function call : s_scenario_lightmap_bsp_data *(*const)(long)
	// function call : s_render_geometry *(*const)(long)
	// function call : long (*const)(long, long, long, long)
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : bool (*const)(real_point3d const *, s_uncompressed_triangle const *, float, float, __int32, void const *, void const *, long, unsigned long, long, s_structure_instanced_geometry_instance const *, s_geometry_test_result *, long, s_scenario_lightmap_bsp_data const *)
	todo("implement");
	bool __result = _sub_1091D7B0(bsp_index, object_index, instance_index, surface_index, test_point, unknown_flag, find_material_flag, out_test_result_valid, test_result);
	return __result;
}

_inline bool geometry_test_collision_result_hook(long bsp_index, long object_index, long instance_index, long surface_index, real_point3d const *test_point, bool unknown_flag, bool find_material_flag, bool *out_test_result_valid, s_geometry_test_result *test_result) // 0x1091D740
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?geometry_test_collision_result_hook@@YA_NJJJJPBUreal_point3d@@_N1PA_NPAUs_geometry_test_result@@@Z");
	// `anonymous-namespace'::geometry_test_collision_result_hook
	// s_geometry_test_result *test_result;

	return geometry_test_collision_result_impl(bsp_index, object_index, instance_index, surface_index, test_point, unknown_flag, find_material_flag, out_test_result_valid, test_result);
}

__declspec(naked) void sample_airprobes_hook() // 0x1091EF10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sample_airprobes_hook@@YAXXZ");
	// `anonymous-namespace'::sample_airprobes_hook
	// procedure flags: nofpo
// bad_probe:
// good_probe:

	__asm
	{
		cmp word ptr [ecx + 14h], 0
		jne Lbad_probe
		cmp word ptr [ecx + 16h], 0
		jne Lbad_probe
		cmp word ptr [ecx + 18h], 0
		je Lgood_probe
		Lbad_probe:
		mov eax, 0BF0E20h
		call eax
		push 075388Bh
		ret
		Lgood_probe:
		push 07539A1h
		ret
	}
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<collision_bsp>::try_get_element(__int32, collision_bsp **) const;
template bool c_tag_block<collision_surface>::try_get_element(__int32, collision_surface **) const;
template bool c_tag_block<real_plane3d>::try_get_element(__int32, real_plane3d **) const;
template bool c_tag_block<s_large_collision_bsp>::try_get_element(__int32, s_large_collision_bsp **) const;
template bool c_tag_block<s_large_collision_surface>::try_get_element(__int32, s_large_collision_surface **) const;
template bool c_tag_block<s_per_mesh_lod_data>::try_get_element(__int32, s_per_mesh_lod_data **) const;
template collision_bsp & c_tag_block<collision_bsp>::operator[](__int32);
template collision_bsp * c_tag_block<collision_bsp>::get_element(__int32) const;
template collision_surface & c_tag_block<collision_surface>::operator[](__int32);
template collision_surface * c_tag_block<collision_surface>::get_element(__int32) const;
template real_plane3d & c_tag_block<real_plane3d>::operator[](__int32);
template real_plane3d * c_tag_block<real_plane3d>::get_element(__int32) const;
template s_compression_info const & c_tag_block<s_compression_info>::operator[](__int32) const;
template s_large_collision_bsp & c_tag_block<s_large_collision_bsp>::operator[](__int32);
template s_large_collision_bsp * c_tag_block<s_large_collision_bsp>::get_element(__int32) const;
template s_large_collision_surface & c_tag_block<s_large_collision_surface>::operator[](__int32);
template s_large_collision_surface * c_tag_block<s_large_collision_surface>::get_element(__int32) const;
template s_mesh const & c_tag_block<s_mesh>::operator[](__int32) const;
template s_per_mesh_lod_data & c_tag_block<s_per_mesh_lod_data>::operator[](__int32);
template s_per_mesh_lod_data * c_tag_block<s_per_mesh_lod_data>::get_element(__int32) const;
