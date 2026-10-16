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
#include "Modules/ModuleDebug.hpp"  // hades: added for 0x1091D7B0
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

extern s_scenario_structure_bsp *(*const global_structure_bsp_get)(long);  // hades: added for 0x1091E630
real_point3d *matrix4x3_inverse_transform_point(real_matrix4x3 const *matrix, real_point3d const *point, real_point3d *result);  // hades: added for 0x1091D7B0
#include "Blam/scenario/scenario_lightmap_definitions.hpp"  // hades: added for 0x1091E630

real_vector3d *vector_from_points3d(real_point3d const *a, real_point3d const *b, real_vector3d *result);  // hades: added for 0x1091CEA0
real_vector3d *cross_product3d(real_vector3d const *a, real_vector3d const *b, real_vector3d *result);  // hades: added for 0x1091CEA0
extern float normalize3d(real_vector3d *v);  // hades: added for 0x1091CEA0
extern float distance_squared3d(real_point3d const *p1, real_point3d const *p2);  // hades: added for 0x1091CEA0

float dot_product3d(real_vector3d const *a, real_vector3d const *b);  // hades: added for 0x1091C250

real_plane3d *plane3d_negate(real_plane3d const *plane, real_plane3d *out_plane);  // hades: added for 0x1091EA70

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
		void ApplyAll() // 0x1091BF20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@geometry_sampler_patches@Patches@@YAXXZ");

			Hook(0x6444B4, interpoloate_lighting_sample_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x350C60, geometry_test_collision_result_hook).Apply();
			Hook(0x353886, sample_airprobes_hook).Apply();
		}
	}
}

/* ---------- private code */

_inline void s_structure_lighting_data::set_per_vertex_buffer(c_rasterizer_vertex_buffer *buffer) // 0x1091F100
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_per_vertex_buffer@s_structure_lighting_data@hades_file_local@@QAEXPAVc_rasterizer_vertex_buffer@@@Z");

	per_vertex_count = buffer->get_vertex_count();
	per_vertex_stride = buffer->get_vertex_stride();
	per_vertex_data = buffer->get_data();
}

_inline void s_structure_lighting_data::set_per_pixel_buffer(c_rasterizer_vertex_buffer *buffer) // 0x1091F0A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_per_pixel_buffer@s_structure_lighting_data@hades_file_local@@QAEXPAVc_rasterizer_vertex_buffer@@@Z");

	per_pixel_data = buffer->get_data();
}

_inline void s_structure_lighting_data::set_lightprobe_index(long index) // 0x1091F070
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_lightprobe_index@s_structure_lighting_data@hades_file_local@@QAEXJ@Z");

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

	return c_geometry_sampler::interpolate_geometry_samples(current_sample, next_sample, interpolation_parameter / 2.0f, 1);
}

_inline void extract_world_vertex(s_render_geometry const *render_geometry, long mesh_index, long triangle_index, s_uncompressed_triangle *triangle) // 0x1091CD70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?extract_world_vertex@@YAXPBUs_render_geometry@@JJPAUs_uncompressed_triangle@@@Z");

	s_mesh const *mesh = &render_geometry->meshes[mesh_index];
	c_rasterizer_vertex_buffer *world_vertex_buffer = ((c_rasterizer_vertex_buffer *(__cdecl *)(s_render_geometry const *, long))0x78C930)(render_geometry, mesh->vertex_buffer_indices[0]);
	c_rasterizer_index_buffer *index_buffer = ((c_rasterizer_index_buffer *(__cdecl *)(s_render_geometry const *, long))0x78C870)(render_geometry, mesh->index_buffer_indices[0]);
	unsigned short const *indices = (unsigned short const *)index_buffer->get_data();
	void const *world_vertices = world_vertex_buffer->get_data();
	((void(__cdecl *)(void const *, long, unsigned short const *, long, s_uncompressed_triangle *))0x7520D0)(world_vertices, triangle_index, indices, world_vertex_buffer->get_vertex_count(), triangle);
}

_inline void extract_rigid_vertex(s_render_geometry const *render_geometry, long mesh_index, long triangle_index, long compression_index, s_uncompressed_triangle *triangle) // 0x1091CC20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?extract_rigid_vertex@@YAXPBUs_render_geometry@@JJJPAUs_uncompressed_triangle@@@Z");

	s_mesh const *mesh = &render_geometry->meshes[mesh_index];
	c_rasterizer_vertex_buffer *rigid_vertex_buffer = ((c_rasterizer_vertex_buffer *(__cdecl *)(s_render_geometry const *, long))0x78C930)(render_geometry, mesh->vertex_buffer_indices[0]);
	void const *rigid_vertices = rigid_vertex_buffer->get_data();
	c_rasterizer_index_buffer *index_buffer = ((c_rasterizer_index_buffer *(__cdecl *)(s_render_geometry const *, long))0x78C870)(render_geometry, mesh->index_buffer_indices[0]);
	unsigned short const *indices = (unsigned short const *)index_buffer->get_data();
	s_compression_info const *compression_info = &render_geometry->compression[compression_index];
	((void(__cdecl *)(void const *, s_compression_info const *, long, unsigned short const *, long, s_uncompressed_triangle *))0x752030)(rigid_vertices, compression_info, triangle_index, indices, rigid_vertex_buffer->get_vertex_count(), triangle);
}

bool get_structure_lighting(long bsp_index, long section_index, long instance_index, s_structure_lighting_data *lighting) // 0x1091E630
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_structure_lighting@@YA_NJJJPAUs_structure_lighting_data@hades_file_local@@@Z");

	s_scenario_structure_bsp *bsp = global_structure_bsp_get(bsp_index);
	s_scenario_lightmap_bsp_data *bsp_lightmap_data = ((s_scenario_lightmap_bsp_data *(*)(long))0xA2EEC0)(bsp_index);
	s_render_geometry *render_geometry = ((s_render_geometry *(*)(long))0xA2EF00)(bsp_index);
	if (instance_index != -1)
	{
		s_structure_instanced_geometry_instance *instance = &bsp->instanced_geometry_instances[instance_index];
		switch (instance->lightmapping_policy)
		{
		case 0:
		case 3:
		{
			long lod_index = instance->lod_data_index;
			if (lod_index >= 0 && lod_index < render_geometry->pvs_data.per_mesh_lod_data.count)
			{
				long vertex_buffer_index = render_geometry->pvs_data.per_mesh_lod_data[lod_index].vertex_buffer;
				if (vertex_buffer_index != -1)
					lighting->set_per_pixel_buffer(((c_rasterizer_vertex_buffer *(*)(s_render_geometry const *, long))0x78C930)(render_geometry, vertex_buffer_index));
			}
			break;
		}
		case 1:
		{
			long mesh_index = (*(c_tag_block<s_scenario_lightmap_instanced_geometry_lighting> *)bsp_lightmap_data->instanced_geometry)[instance_index].instanced_mesh_index;
			if (mesh_index != -1)
				lighting->set_per_vertex_buffer(((c_rasterizer_vertex_buffer *(*)(s_scenario_lightmap_bsp_data *, long))0x5F9980)(bsp_lightmap_data, (*(c_tag_block<s_scenario_lightmap_static_per_vertex_lighting> *)bsp_lightmap_data->per_vertex_lighting_buffers)[mesh_index].vertex_buffer_index));
			break;
		}
		case 2:
			lighting->set_lightprobe_index((*(c_tag_block<s_scenario_lightmap_instanced_geometry_lighting> *)bsp_lightmap_data->instanced_geometry)[instance_index].unknown_probe_index);
			break;
		}
	}
	else
	{
		long lightmap_bsp_type = ((long (*)(long))0xA2EED0)(bsp_index);
		if (lightmap_bsp_type == 1)
		{
			long instance_data_index = (*(c_tag_block<s_scenario_lightmap_cluster_static_per_vertex_lighting> *)bsp_lightmap_data->cluster_per_vertex_lighting_buffers)[section_index].instance_index;
			if (instance_data_index != -1)
			{
				long per_vertex_buffer_index = (*(c_tag_block<s_scenario_lightmap_static_per_vertex_lighting> *)bsp_lightmap_data->per_vertex_lighting_buffers)[instance_data_index].vertex_buffer_index;
				lighting->set_per_vertex_buffer(((c_rasterizer_vertex_buffer *(*)(s_render_geometry const *, long))0x78C930)(render_geometry, per_vertex_buffer_index));
			}
		}
		else if (lightmap_bsp_type == 0)
		{
			s_structure_cluster *const cluster = &bsp->clusters[section_index];
			if (cluster->mesh_index != -1)
			{
				s_mesh const *mesh = &render_geometry->meshes[cluster->mesh_index];
				if (mesh->vertex_buffer_indices[1] != -1)
					lighting->set_per_pixel_buffer(((c_rasterizer_vertex_buffer *(*)(s_render_geometry const *, long))0x78C930)(render_geometry, mesh->vertex_buffer_indices[1]));
			}
		}
	}
	return true;
}

_inline void barycentric_coordinates(real_point3d const &p, real_point3d const &a, real_point3d const &b, real_point3d const &c, float &u, float &v, float &w) // 0x1091C250
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?barycentric_coordinates@@YAXABUreal_point3d@@000AAM11@Z");

	real_vector3d ab = b - a;
	real_vector3d ac = c - a;
	real_vector3d ap = p - a;
	float const d00 = dot_product3d(&ab, &ab);
	float const d01 = dot_product3d(&ab, &ac);
	float const d11 = dot_product3d(&ac, &ac);
	float const d20 = dot_product3d(&ap, &ab);
	float const d21 = dot_product3d(&ap, &ac);
	float const denom = 1.0f / (d00 * d11 - d01 * d01);
	v = (d11 * d20 - d01 * d21) * denom;
	w = (d00 * d21 - d01 * d20) * denom;
	u = 1.0f - v - w;
}

void closest_point_on_triangle(real_point3d const &p, real_point3d const &a, real_point3d const &b, real_point3d const &c, real_point3d &closest_point) // 0x1091C560
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?closest_point_on_triangle@@YAXABUreal_point3d@@000AAU1@@Z");

	float u;
	float v;
	float w;
	barycentric_coordinates(p, a, b, c, u, v, w);
	if (u >= 0.0f && v >= 0.0f && w >= 0.0f)
	{
		closest_point.x = u * a.x + v * b.x + w * c.x;
		closest_point.y = u * a.y + v * b.y + w * c.y;
		closest_point.z = u * a.z + v * b.z + w * c.z;
	}
	else
	{
		bool const su = u < 0.0f;
		bool const sv = v < 0.0f;
		bool const sw = w < 0.0f;
		if (!su && sv && sw)
			closest_point = a;
		else if (su && !sv && sw)
			closest_point = b;
		else if (su && sv && !sw)
			closest_point = c;
		else
		{
			real_point3d q;
			real_point3d r;
			if (!su && !sv && sw)
			{
				q = a, r = b;
			}
			else if (!su && sv && !sw)
			{
				q = a, r = c;
			}
			else
			{
				q = b, r = c;
			}
			real_vector3d qr = r - q;
			real_vector3d pq = p - q;
			float const length = dot_product3d(&qr, &qr);
			if (length < 0.00001f)
				closest_point = q;
			else
			{
				float const t = std::clamp(dot_product3d(&pq, &qr) / length, 0.0f, 1.0f);
				closest_point = q + t * qr;
			}
		}
	}
}

void get_surface_plane(real_plane3d *plane, c_structure_surface const &structure_surface) // 0x1091EA70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_surface_plane@@YAXPAUreal_plane3d@@ABUc_structure_surface@@@Z");

	c_collision_bsp_reference collision_bsp;
	structure_surface.get_collision_bsp(&collision_bsp);
	bool negated;
	if (collision_bsp.large_bsp)
	{
		s_large_collision_surface *const surface = &collision_bsp.large_bsp->surfaces[structure_surface.get_surface_index()];
		*plane = collision_bsp.large_bsp->planes[surface->plane_index & 0x7FFFFFFF];
		negated = (surface->plane_index & 0x80000000) != 0;
	}
	else
	{
		collision_surface *const surface = &collision_bsp.bsp->surfaces[structure_surface.get_surface_index()];
		*plane = collision_bsp.bsp->planes[surface->plane_index & 0x7FFF];
		negated = (surface->plane_index & 0x8000) != 0;
	}
	if (negated)
		plane3d_negate(plane, plane);
}

long find_best_triangle_closest(c_structure_surface const &structure_surface, s_render_geometry const *render_geometry, real_point3d const &point, s_uncompressed_triangle &triangle, float &s, float &t) // 0x1091CEA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?find_best_triangle_closest@@YAJABUc_structure_surface@@PBUs_render_geometry@@ABUreal_point3d@@AAUs_uncompressed_triangle@@AAM4@Z");

	long first_index = structure_surface.get_first_triangle_index();
	long end_index = first_index + structure_surface.get_triangle_count() - 1;
	real_plane3d surface_plane;
	get_surface_plane(&surface_plane, structure_surface);
	long best_triangle_index = -1;
	float min_point_distance = FLT_MAX;
	real_point3d min_point;
	for (long i = first_index; i <= end_index; i++)
	{
		s_structure_plane const *triangle_mapping = structure_surface.get_triangle_mapping(i);
		long const mesh_index = structure_surface.get_mesh_index(i);
		long const vertex_index = structure_surface.get_triangle_vertex_index(i);
		if (structure_surface.get_instance_definition())
			extract_rigid_vertex(render_geometry, mesh_index, vertex_index, structure_surface.get_compression_info_index(), &triangle);
		else
			extract_world_vertex(render_geometry, mesh_index, vertex_index, &triangle);
		real_vector3d v1;
		vector_from_points3d(&triangle.positions[0], &triangle.positions[1], &v1);
		real_vector3d v2;
		vector_from_points3d(&triangle.positions[0], &triangle.positions[2], &v2);
		real_vector3d triangle_normal;
		cross_product3d(&v1, &v2, &triangle_normal);
		normalize3d(&triangle_normal);
		if (dot_product3d(&surface_plane.normal, &triangle_normal) < -0.00001f)
			continue;
		real_point3d closest_point;
		closest_point_on_triangle(point, triangle.positions[0], triangle.positions[1], triangle.positions[2], closest_point);
		float const distance = distance_squared3d(&closest_point, &point);
		if (min_point_distance > distance)
		{
			best_triangle_index = i;
			min_point_distance = distance;
			min_point = closest_point;
			if (distance < 0.001f)
				break;
		}
	}
	if (best_triangle_index != -1)
	{
		long const mesh_index = structure_surface.get_mesh_index(best_triangle_index);
		long const vertex_index = structure_surface.get_triangle_vertex_index(best_triangle_index);
		if (structure_surface.get_instance_definition())
			extract_rigid_vertex(render_geometry, mesh_index, vertex_index, structure_surface.get_compression_info_index(), &triangle);
		else
			extract_world_vertex(render_geometry, mesh_index, vertex_index, &triangle);
		float u;
		float v;
		float w;
		barycentric_coordinates(min_point, triangle.positions[0], triangle.positions[1], triangle.positions[2], u, v, w);
		s = v;
		t = w;
	}
	return best_triangle_index;
}

long find_best_triangle_h3(c_structure_surface const &structure_surface, s_render_geometry const *render_geometry, real_point3d const &point, s_uncompressed_triangle &triangle, float &s, float &t) // 0x1091D3D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?find_best_triangle_h3@@YAJABUc_structure_surface@@PBUs_render_geometry@@ABUreal_point3d@@AAUs_uncompressed_triangle@@AAM4@Z");

	long const first_index = structure_surface.get_first_triangle_index();
	long const end_index = first_index + structure_surface.get_triangle_count() - 1;
	long best_triangle_index = -1;
	float min_area = -FLT_MAX;
	float min_s;
	float min_t;
	for (long i = first_index; i <= end_index; i++)
	{
		s_structure_plane const *triangle_mapping = structure_surface.get_triangle_mapping(i);
		long const mesh_index = structure_surface.get_mesh_index(i);
		long const vertex_index = structure_surface.get_triangle_vertex_index(i);
		if (structure_surface.get_instance_definition())
			extract_rigid_vertex(render_geometry, mesh_index, vertex_index, structure_surface.get_compression_info_index(), &triangle);
		else
			extract_world_vertex(render_geometry, mesh_index, vertex_index, &triangle);
		float s;
		float t;
		float const a = ((float (__cdecl *)(real_point3d const *, real_point3d const *, real_point3d const *, real_point3d const *, float *, float *))0x750A20)(&point, &triangle.positions[0], &triangle.positions[1], &triangle.positions[2], &s, &t);
		if (a > min_area)
		{
			best_triangle_index = i;
			min_s = s;
			min_t = t;
			min_area = a;
			if (a > -0.00001f)
				break;
		}
	}
	if (best_triangle_index != -1)
	{
		long const mesh_index = structure_surface.get_mesh_index(best_triangle_index);
		long const vertex_index = structure_surface.get_triangle_vertex_index(best_triangle_index);
		if (structure_surface.get_instance_definition())
			extract_rigid_vertex(render_geometry, mesh_index, vertex_index, structure_surface.get_compression_info_index(), &triangle);
		else
			extract_world_vertex(render_geometry, mesh_index, vertex_index, &triangle);
		s = min_s;
		t = min_t;
	}
	return best_triangle_index;
}

bool geometry_test_collision_result_impl(long bsp_index, long object_index, long instance_index, long surface_index, real_point3d const *test_point, bool unknown_flag, bool find_material_flag, bool *out_test_result_valid, s_geometry_test_result *test_result) // 0x1091D7B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?geometry_test_collision_result_impl@@YA_NJJJJPBUreal_point3d@@_N1PA_NPAUs_geometry_test_result@@@Z");

	*out_test_result_valid = false;
	if (object_index != -1)
	{
		long (*const object_has_unknown_lighting)(long) = (long (*)(long))0x752600;
		long (*const object_has_light_volume_samples)(long) = (long (*)(long))0x752660;
		if (!object_has_unknown_lighting(object_index) && !object_has_light_volume_samples(object_index))
			return false;
		test_result->object_index = object_index;
		*out_test_result_valid = true;
	}
	else
	{
		if (bsp_index == -1)
			return false;
		s_scenario_lightmap_bsp_data *const bsp_lightmap_data = ((s_scenario_lightmap_bsp_data *(*const)(long))0xA2EEC0)(bsp_index);
		if (!unknown_flag && !bsp_lightmap_data)
			return false;
		s_render_geometry *const render_geometry = ((s_render_geometry *(*const)(long))0xA2EF00)(bsp_index);
		if (!render_geometry)
			return false;
		test_result->bsp_index = bsp_index;
		if (find_material_flag)
			test_result->material_index = ((long (*const)(long, long, long, long))0x750810)(bsp_index, -1, instance_index, surface_index);
		else
			test_result->material_index = -1;
		s_scenario_structure_bsp *structure_bsp = global_structure_bsp_get(bsp_index);
		real_point3d point = *test_point;
		if (instance_index != -1)
			matrix4x3_inverse_transform_point(&structure_bsp->instanced_geometry_instances[instance_index].rigid_matrix, &point, &point);
		float s;
		float t;
		long triangle_index = -1;
		long section_index = -1;
		long triangle_vertex_index = -1;
		s_uncompressed_triangle triangle;
		c_structure_surface structure_surface(structure_bsp, instance_index, surface_index);
		__int32 const quality = Modules::ModuleDebug::Instance().VarGeometrySamplerQuality->ValueInt;
		if (structure_surface.is_valid())
		{
			if (quality > 0)
			{
				if (instance_index != -1 || quality == 2)
					triangle_index = find_best_triangle_closest(structure_surface, render_geometry, point, triangle, s, t);
				else
					triangle_index = find_best_triangle_h3(structure_surface, render_geometry, point, triangle, s, t);
			}
			if (triangle_index != -1)
			{
				section_index = structure_surface.get_section_index(triangle_index);
				triangle_vertex_index = structure_surface.get_triangle_vertex_index(triangle_index);
			}
		}
		if (triangle_index == -1)
			return false;
		s_structure_lighting_data lighting;
		if (get_structure_lighting(bsp_index, section_index, instance_index, &lighting))
		{
			test_result->use_lightprobe = lighting.lightprobe_index != -1;
			test_result->use_per_vertex_lighting = lighting.per_vertex_data != nullptr;
			test_result->use_per_pixel_lighting = lighting.per_pixel_data != nullptr;
		}
		if (!((bool (*const)(real_point3d const *, s_uncompressed_triangle const *, float, float, long, void const *, void const *, long, long, long, bool, s_geometry_test_result *, long, s_scenario_lightmap_bsp_data *))0x751730)(&point, &triangle, s, t, (triangle_vertex_index - 2) / 3, lighting.per_pixel_data, lighting.per_vertex_data, lighting.per_vertex_count, lighting.per_vertex_stride, lighting.lightprobe_index, false, test_result, bsp_index, bsp_lightmap_data))
			return false;
		if (instance_index != -1)
			test_result->instanced_geometry_index = instance_index;
		else
			test_result->cluster_index = structure_surface.get_section_index(triangle_index);
	}
	*out_test_result_valid = true;
	return true;
}

_inline bool geometry_test_collision_result_hook(long bsp_index, long object_index, long instance_index, long surface_index, real_point3d const *test_point, bool unknown_flag, bool find_material_flag, bool *out_test_result_valid, s_geometry_test_result *test_result) // 0x1091D740
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?geometry_test_collision_result_hook@@YA_NJJJJPBUreal_point3d@@_N1PA_NPAUs_geometry_test_result@@@Z");

	return geometry_test_collision_result_impl(bsp_index, object_index, instance_index, surface_index, test_point, unknown_flag, find_material_flag, out_test_result_valid, test_result);
}

__declspec(naked) void sample_airprobes_hook() // 0x1091EF10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sample_airprobes_hook@@YAXXZ");

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
