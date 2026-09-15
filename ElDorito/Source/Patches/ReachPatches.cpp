/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/geometry/geometry_definitions.hpp"
#include "Blam/geometry/geometry_sampler.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/physics/collision_bsp.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/render_structure.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/shaders/render_methods_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/structures/structure_bsp_definitions.hpp"
#include "Blam/structures/structure_seams.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/visibility/visibility.hpp"
#include "Blam/visibility/visibility_items.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Modules/ModuleGraphics.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
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

class c_rasterizer_vertex_buffer;
struct c_collision_bsp_reference;
struct c_render_method_data;
struct real_matrix4x3;
struct real_point3d;
struct s_cluster_reference;
struct s_geometry_material;
struct s_instance_part;
struct s_mesh;
struct s_part;
struct s_render_geometry;
struct s_render_method_postprocess_definition;
struct s_scenario;
struct s_scenario_lightmap_bsp_data;
struct s_scenario_structure_bsp;
struct s_structure_bsp_path_finding;
struct s_structure_bsp_resources;
struct s_structure_cluster;
struct s_structure_instanced_geometry_definition;
struct s_structure_instanced_geometry_instance;
namespace Modules
{
	class ModuleGraphics;
}
namespace hades_file_local
{
	struct s_decal_cylinder;
	struct c_instanced_geometry_iterator;
	struct s_instance_collision_test_arguements;
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
	namespace Reach {}
	using namespace Patches::Reach;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	#pragma pack(push, 4)
	struct s_decal_cylinder
	{
		real_matrix4x3 matrix; // 0x0
		float radius; // 0x34
		float height; // 0x38
	};
	#pragma pack(pop)
	static_assert(sizeof(s_decal_cylinder) == 60, "Invalid s_decal_cylinder size");

	struct c_instanced_geometry_iterator
	{
		static long const k_max_instances;
		c_instanced_geometry_iterator(s_cluster_reference *, s_decal_cylinder *, long);
		bool next_instance();
		bool next_cluster();
		bool next_instance_bucket();
		void next();
	private:
		s_decal_cylinder *m_cylinder; // 0x0
		s_cluster_reference *m_cluster_references; // 0x4
		long m_structure_bsp_index; // 0x8
		long m_cluster_reference_index; // 0xC
		s_scenario_structure_bsp *m_structure_bsp; // 0x10
		s_structure_cluster *m_cluster; // 0x14
		s_mesh *m_mesh; // 0x18
		long m_instance_bucket_count; // 0x1C
		long m_instance_bucket_index; // 0x20
		s_instance_part *m_instance_buckets; // 0x24
		unsigned long *m_visited_instance_bit_vector; // 0x28
		long _pad[127]; // 0x2C
		long m_instance_bucket_instance_count; // 0x228
		long m_instance_bucket_instance_index; // 0x22C
		long m_instance_index; // 0x230
		s_structure_instanced_geometry_instance *m_instance; // 0x234
	};
	static_assert(sizeof(c_instanced_geometry_iterator) == 568, "Invalid c_instanced_geometry_iterator size");

	struct s_instance_collision_test_arguements
	{
		__int32 bsp_index; // 0x0
		s_scenario_structure_bsp *structure_bsp; // 0x4
		s_structure_bsp_resources *collision_bsp_resource; // 0x8
		c_collision_bsp_reference collision_bsp_reference; // 0xC
		s_structure_bsp_path_finding *path_finding; // 0x14
	};
	static_assert(sizeof(s_instance_collision_test_arguements) == 24, "Invalid s_instance_collision_test_arguements size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Patches
{
	namespace Reach
	{
		extern void ApplyAfterInit();
	}
}

bool scenario_structure_bsp_has_valid_lightmap_for_bsp_type_hook(long definition_index, long bspIndex, long bsp_type);
bool __fastcall s_render_method_postprocess_definition__query_texture_transform_hook(s_render_method_postprocess_definition *thisptr, void *unused, long bitmap_reference_index, unsigned long *out_color, long *out_bitmap_group_index, long *out_bitmap_index);
bool rasterizer_force_default_lighting_hook();
long update_cluster_stream_and_determine_lighting_attributes_hook(e_entry_point entry_point, __int32 bsp_index, s_render_geometry *geometry, s_mesh *mesh, s_part *part, s_geometry_material *materials, s_cluster_reference cluster);
void __fastcall c_instanced_geometry_iterator__next_hook(c_instanced_geometry_iterator *thisptr);
void __fastcall c_instanced_geometry_iterator__ctor_hook(c_instanced_geometry_iterator *thisptr, void *__formal, s_cluster_reference *cluster_references, s_decal_cylinder *cylinder, long ignore_instance_index);
bool test_instanced_geometry_hook(s_instance_collision_test_arguements *test_arguments, long instance_index, s_structure_instanced_geometry_instance *instance, s_structure_instanced_geometry_definition *definition, unsigned long flags);

/* ---------- globals */

extern s_scenario_structure_bsp *(*const global_structure_bsp_get)(long); // 0x11248AD4
extern long (*const global_structure_bsp_first_active_index_get)(); // 0x11248ACC

float (*c_render_method_data::m_context_interface)(long, long, long); // 0x1138DEE0
namespace Utils
{
	Modules::ModuleGraphics *Utils::Singleton<Modules::ModuleGraphics>::m_instance; // 0x1138DEDC
}

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Reach
	{
		_extern void _sub_107BEB80();
		void ApplyAfterInit() // 0x107BEB80
		{
			mangled_x86(MANGLED_TODO, "?ApplyAfterInit@Reach@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_107BEB80();
		}
	}
}

/* ---------- private code */

_extern bool _sub_107C0330(long, long, long);
bool scenario_structure_bsp_has_valid_lightmap_for_bsp_type_hook(long definition_index, long bspIndex, long bsp_type) // 0x107C0330
{
	// `anonymous-namespace'::scenario_structure_bsp_has_valid_lightmap_for_bsp_type_hook
	// long bsp_type;
	// long lightmap_definition_index;
	// s_scenario_lightmap_bsp_data *lightmap_bsp_data;
	// s_scenario_structure_bsp *structure_bsp;
	// s_scenario *scenario;
	// s_scenario_lightmap_bsp_data *(*const scenario_lightmap_find_bsp)(long, long, long);
	// s_scenario_structure_bsp *(*const scenario_structure_bsp_get)(s_scenario const *, long);
	{
		// long total_mesh_part_count;
		// bool valid;
		{
			// long cluster_index;
			{
				// long mesh_index;
			}
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : s_scenario_lightmap_bsp_data *(*const)(long, long, long)
	// function call : s_scenario_structure_bsp *(*const)(s_scenario const *, long)
	todo("implement");
	bool __result = _sub_107C0330(definition_index, bspIndex, bsp_type);
	return __result;
}

bool __fastcall s_render_method_postprocess_definition__query_texture_transform_hook(s_render_method_postprocess_definition *thisptr, void *unused, long bitmap_reference_index, unsigned long *out_color, long *out_bitmap_group_index, long *out_bitmap_index) // 0x107C0280
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?s_render_method_postprocess_definition__query_texture_transform_hook@@YI_NPAUs_render_method_postprocess_definition@@PAXJPAKPAJ3@Z");
	// `anonymous-namespace'::s_render_method_postprocess_definition__query_texture_transform_hook
	// long *out_bitmap_index;
	// bool (*const query_texture_transform)(s_render_method_postprocess_definition *, long, unsigned long *, long *, long *);
	// long texture_constant_index;
	// function call : bool (*const)(s_render_method_postprocess_definition *, long, unsigned long *, long *, long *)

	bool (__thiscall *const query_texture_transform)(s_render_method_postprocess_definition *, long, unsigned long *, long *, long *) = (bool(__thiscall *const)(s_render_method_postprocess_definition *, long, unsigned long *, long *, long *))0xa20df0;

	int texture_constant_index = thisptr->queryable_properties[bitmap_reference_index];
	if (texture_constant_index < 0 || texture_constant_index >= thisptr->texture_constants.count)
	{
		return false;
	}
	return query_texture_transform(thisptr, bitmap_reference_index, out_color, out_bitmap_group_index, out_bitmap_index);
}

bool rasterizer_force_default_lighting_hook() // 0x107C01E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?rasterizer_force_default_lighting_hook@@YA_NXZ");
	// `anonymous-namespace'::rasterizer_force_default_lighting_hook
	// procedure flags: nofpo
	// long sbsp_index;
		// s_scenario_structure_bsp *sbsp;
	// function call : long (*const)()
	// function call : s_scenario_structure_bsp *(*const)(long)

	long sbsp_index = global_structure_bsp_first_active_index_get();
	if (sbsp_index != NONE)
	{
		s_scenario_structure_bsp *sbsp = global_structure_bsp_get(sbsp_index);

		if (Utils::Singleton<Modules::ModuleGraphics>::Instance().VarForceDefaultLighting->ValueInt)
		{
			return true;
		}
	}

	return false;
}

_extern long _sub_107C09F0(e_entry_point, __int32, s_render_geometry *, s_mesh *, s_part *, s_geometry_material *, s_cluster_reference);
long update_cluster_stream_and_determine_lighting_attributes_hook(e_entry_point entry_point, __int32 bsp_index, s_render_geometry *geometry, s_mesh *mesh, s_part *part, s_geometry_material *materials, s_cluster_reference cluster) // 0x107C09F0
{
	// `anonymous-namespace'::update_cluster_stream_and_determine_lighting_attributes_hook
	// s_cluster_reference cluster;
	// bool (*const rasterizer_force_default_lighting)();
	// long result;
	{
		// c_rasterizer_vertex_buffer *vertex_buffer;
		// s_scenario_lightmap_bsp_data *lbsp;
		// long static_per_vertex_index;
		// long vertex_buffer_index;
	}
	// function call : bool (*const)()
	// function call : void (*const)()
	// function call : c_rasterizer_vertex_buffer *(*const)(s_scenario_lightmap_bsp_data *, long)
	// function call : bool (*const)(c_rasterizer_vertex_buffer const *)
	todo("implement");
	long __result = _sub_107C09F0(entry_point, bsp_index, geometry, mesh, part, materials, cluster);
	return __result;
}

_inline c_instanced_geometry_iterator::c_instanced_geometry_iterator(s_cluster_reference *cluster_references, s_decal_cylinder *cylinder, long ignore_instance_index) // 0x107BE6E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_instanced_geometry_iterator@hades_file_local@@QAE@PAUs_cluster_reference@@PAUs_decal_cylinder@1@J@Z");
	// `anonymous-namespace'::c_instanced_geometry_iterator::c_instanced_geometry_iterator
	// long ignore_instance_index;
	// static unsigned long `c_instanced_geometry_iterator::c_instanced_geometry_iterator'::`2'::static_visited_instance_bit_vector[256]; // 0x1138DEE8

	m_cylinder = cylinder;
	m_cluster_references = cluster_references;
	m_structure_bsp_index = NONE;
	m_cluster_reference_index = 0;
	m_instance_bucket_count = 0;
	m_instance_bucket_index = 0;
	m_instance_bucket_instance_count = 0;
	m_instance_bucket_instance_index = 0;
	m_instance_index = NONE;
	m_instance = nullptr;

	static unsigned long static_visited_instance_bit_vector[256];
	m_visited_instance_bit_vector = static_visited_instance_bit_vector;
	memset(m_visited_instance_bit_vector, 0, sizeof(static_visited_instance_bit_vector));

	if (ignore_instance_index != NONE)
	{
		m_visited_instance_bit_vector[ignore_instance_index >> 5] |= 1 << (ignore_instance_index & 31);
	}

	next();
}

_extern bool _sub_107BFE40(c_instanced_geometry_iterator *const);
_inline bool c_instanced_geometry_iterator::next_instance() // 0x107BFE40
{
	// `anonymous-namespace'::c_instanced_geometry_iterator::next_instance
	// c_instanced_geometry_iterator *const this;
	todo("implement");
	bool __result = _sub_107BFE40(this);
	return __result;
}

_inline bool c_instanced_geometry_iterator::next_cluster() // 0x107BFCD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?next_cluster@c_instanced_geometry_iterator@hades_file_local@@QAE_NXZ");
	// `anonymous-namespace'::c_instanced_geometry_iterator::next_cluster
	// c_instanced_geometry_iterator *const this;
	// s_cluster_reference &cluster_ref;
	// function call : s_scenario_structure_bsp *(*const)(long)

	if (m_cluster_reference_index >= 4)
	{
		return false;
	}

	s_cluster_reference &cluster_ref = m_cluster_references[m_cluster_reference_index];
	if (cluster_ref.bsp_index == NONE)
	{
		return false;
	}

	m_structure_bsp_index = cluster_ref.bsp_index;
	m_structure_bsp = global_structure_bsp_get(cluster_ref.bsp_index);
	m_cluster = &m_structure_bsp->clusters[cluster_ref.cluster_index];
	m_mesh = &m_structure_bsp->geometry.meshes[m_cluster->mesh_index];
	m_instance_bucket_count = m_mesh->instance_parts.count;
	++m_cluster_reference_index;

	return next_instance_bucket();
}

_inline bool c_instanced_geometry_iterator::next_instance_bucket() // 0x107C0100
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?next_instance_bucket@c_instanced_geometry_iterator@hades_file_local@@QAE_NXZ");
	// `anonymous-namespace'::c_instanced_geometry_iterator::next_instance_bucket
	// c_instanced_geometry_iterator *const this;

	if (m_instance_bucket_index >= m_instance_bucket_count)
	{
		m_instance_bucket_index = 0;
		return next_cluster();
	}
	else
	{
		m_instance_buckets = &m_mesh->instance_parts[m_instance_bucket_index];
		m_instance_bucket_instance_count = m_instance_buckets->contents.count;
		++m_instance_bucket_index;
		return next_instance();
	}
}

_inline void c_instanced_geometry_iterator::next() // 0x107BFBD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?next@c_instanced_geometry_iterator@hades_file_local@@QAEXXZ");
	// `anonymous-namespace'::c_instanced_geometry_iterator::next
	// c_instanced_geometry_iterator *const this;
	// bool (*const collision_point_in_cylinder)(real_point3d const *, real_matrix4x3 const *, float, float, float *);
	// function call : bool (*const)(real_point3d const *, real_matrix4x3 const *, float, float, float *)

	bool (*const collision_point_in_cylinder)(real_point3d const *, real_matrix4x3 const *, float, float, float *) = (bool (*const)(real_point3d const *, real_matrix4x3 const *, float, float, float *))0x97a530;

	while (next_instance())
	{
		if (collision_point_in_cylinder(&m_instance->bounding_sphere_offset, &m_cylinder->matrix, m_cylinder->radius + m_instance->bounding_sphere_radius_minimum, m_instance->bounding_sphere_radius_minimum * 2.0f + m_cylinder->height, nullptr))
			break;
	}
}

void __fastcall c_instanced_geometry_iterator__next_hook(c_instanced_geometry_iterator *thisptr) // 0x107BF730
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_instanced_geometry_iterator__next_hook@@YIXPAUc_instanced_geometry_iterator@hades_file_local@@@Z");
	// `anonymous-namespace'::c_instanced_geometry_iterator__next_hook
	// c_instanced_geometry_iterator *thisptr;

	thisptr->next();
}

void __fastcall c_instanced_geometry_iterator__ctor_hook(c_instanced_geometry_iterator *thisptr, void *__formal, s_cluster_reference *cluster_references, s_decal_cylinder *cylinder, long ignore_instance_index) // 0x107BF6B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_instanced_geometry_iterator__ctor_hook@@YIXPAUc_instanced_geometry_iterator@hades_file_local@@PAXPAUs_cluster_reference@@PAUs_decal_cylinder@2@J@Z");
	// `anonymous-namespace'::c_instanced_geometry_iterator__ctor_hook
	// long ignore_instance_index;

	new (thisptr) c_instanced_geometry_iterator(cluster_references, cylinder, ignore_instance_index);
}

bool test_instanced_geometry_hook(s_instance_collision_test_arguements *test_arguments, long instance_index, s_structure_instanced_geometry_instance *instance, s_structure_instanced_geometry_definition *definition, unsigned long flags) // 0x107C06E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?test_instanced_geometry_hook@@YA_NPAUs_instance_collision_test_arguements@hades_file_local@@JPAUs_structure_instanced_geometry_instance@@PAUs_structure_instanced_geometry_definition@@K@Z");
	// `anonymous-namespace'::test_instanced_geometry_hook
	// unsigned long flags;
	// bool (*const test_instanced_geometry)(s_instance_collision_test_arguements *, long, s_structure_instanced_geometry_instance *, s_structure_instanced_geometry_definition *, unsigned long);
	// function call : bool (*const)(s_instance_collision_test_arguements *, long, s_structure_instanced_geometry_instance *, s_structure_instanced_geometry_definition *, unsigned long)

	bool (__cdecl *const test_instanced_geometry)(s_instance_collision_test_arguements *, long, s_structure_instanced_geometry_instance *, s_structure_instanced_geometry_definition *, unsigned long) = (bool(__cdecl *const)(s_instance_collision_test_arguements *, long, s_structure_instanced_geometry_instance *, s_structure_instanced_geometry_definition *, unsigned long))0x6d9230;

	if (instance->flags.test(_instanced_geometry_miscolored_bsp_bit) || instance->flags.test(_instanced_geometry_no_physics_bit))
	{
		return false;
	}

	return test_instanced_geometry(test_arguments, instance_index, instance, definition, flags);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Modules::ModuleGraphics & Utils::Singleton<Modules::ModuleGraphics>::Instance();
template bool c_flags<enum e_instanced_geometry_flags,unsigned short>::test(e_instanced_geometry_flags) const;
template bool c_flags<enum e_scenario_structure_bsp_compatibility_flags,unsigned short>::test(e_scenario_structure_bsp_compatibility_flags) const;
template bool c_tag_block<s_instance_part>::try_get_element(__int32, s_instance_part **) const;
template bool c_tag_block<s_instance_part_contents>::try_get_element(__int32, s_instance_part_contents **) const;
template bool c_tag_block<s_mesh>::try_get_element(__int32, s_mesh **) const;
template bool c_tag_block<s_structure_cluster>::try_get_element(__int32, s_structure_cluster **) const;
template c_flags<enum e_part_flags,unsigned char> c_flags<enum e_part_flags,unsigned char>::operator&(__int32 const) const;
template c_flags<enum e_part_flags,unsigned char>::c_flags(unsigned char const &);
template c_flags<enum e_part_flags,unsigned char>::operator bool() const;
template s_instance_part & c_tag_block<s_instance_part>::operator[](__int32);
template s_instance_part * c_tag_block<s_instance_part>::get_element(__int32) const;
template s_instance_part_contents & c_tag_block<s_instance_part_contents>::operator[](__int32);
template s_instance_part_contents * c_tag_block<s_instance_part_contents>::get_element(__int32) const;
template s_mesh & c_tag_block<s_mesh>::operator[](__int32);
template s_mesh * c_tag_block<s_mesh>::get_element(__int32) const;
template s_structure_cluster & c_tag_block<s_structure_cluster>::operator[](__int32);
template s_structure_cluster * c_tag_block<s_structure_cluster>::get_element(__int32) const;
template s_structure_instanced_geometry_instance & c_tag_block<s_structure_instanced_geometry_instance>::operator[](__int32);
