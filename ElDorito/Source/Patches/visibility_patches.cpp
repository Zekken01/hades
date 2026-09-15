/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/geometry/geometry_definitions.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/draw_string.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/render_object_globals.hpp"
#include "Blam/render/render_structure.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/structures/structure_bsp_definitions.hpp"
#include "Blam/structures/structure_seams.hpp"
#include "Blam/structures/structures.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_block_flags.inl"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/visibility/visibility.hpp"
#include "Blam/visibility/visibility_items.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Console/Console.hpp"
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

class CDebugTextPrinter;
struct begin;
struct c_seam_connected_cluster_references;
struct c_visibility_collection;
struct end;
struct real_point3d;
struct s_cluster_reference;
struct s_instance_part;
struct s_mesh;
struct s_render_geometry;
struct s_render_object_globals;
struct s_scenario;
struct s_scenario_structure_bsp;
struct s_scenario_zone_set;
struct s_scenario_zone_set_bsp_pvs;
struct s_scenario_zone_set_bsp_seam_cluster_mapping;
struct s_scenario_zone_set_pvs;
struct s_seam_mapping;
struct s_structure_cluster;
struct s_structure_globals;
struct s_structure_instanced_geometry_instance;
struct s_visibility_cluster;
struct s_visible_cluster;
struct s_visible_instance;
struct s_visible_instance_group;
struct s_visible_items;
struct short_rectangle2d;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;

/* ---------- constants */

/* ---------- definitions */

// CDebugTextPrinter is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

extern s_scenario_structure_bsp *(__cdecl *const global_structure_bsp_get)(long);  // hades: added for 0X10AC71B0

extern long __stdcall sub_6870A0_hook(short region_cluster_index);
extern void render_debug_visibility();
extern void __fastcall c_visibility_collection__generate_cluster_visible_parts(void *thisptr, void *unused, s_visible_cluster *visible_cluster);
extern s_structure_globals *get_structure_globals();
extern bool structure_seams_connected_cluster_references_get_reach(long scenario_index, s_cluster_reference cluster_reference, bool include_self, c_seam_connected_cluster_references *out_cluster_refs);
extern bool structure_seams_connected_cluster_references_get_h3(long scenario_index, s_cluster_reference cluster_reference, bool add_self, c_seam_connected_cluster_references *out_cluster_refs);
extern bool structure_seams_connected_cluster_references_get_hook(long scenario_index, s_cluster_reference cluster_reference, bool include_self, c_seam_connected_cluster_references *out_cluster_refs);
extern void visibility_patches_apply();

extern "C" void sub_687070_hook(__int32 region_index, __int32 cluster_index);
extern "C" unsigned long *sub_686BC0_hook(long part_count);
extern "C" void patch_visibility();
extern "C" void patch_render_object_globals();
extern "C" bool structure_instanced_geometry_mark(long structure_bsp_index, long instance_index);
extern "C" bool structure_instanced_geometry_mark_get_user_data(short structure_bsp_index, short instance_index, long *user_data);
extern "C" bool structure_instanced_geometry_mark_with_user_data(short structure_bsp_index, short instance_index, long user_data);
extern "C" void structure_instanced_geometry_marker_begin();
extern "C" void structure_instanced_geometry_marker_end();
extern "C" bool structure_instanced_geometry_unmarked(short structure_bsp_index, short instance_index);
extern "C" void __fastcall c_visibility_collection__collect_structure_elements_from_region_hook(c_visibility_collection *thisptr);
extern "C" unsigned char const *scenario_pvs_connected_clusters_get_hook(s_cluster_reference cluster_reference, long *out_count);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

long __stdcall sub_6870A0_hook(short region_cluster_index) // 0x10AC7640
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sub_6870A0_hook@@YGJF@Z");
	// short region_cluster_index;
	// long group_index;
	// s_visible_items &visible_items;
		// long group_offset;

	s_visible_items &visible_items = c_visible_items::get_global_items();
	long group_index = visible_items.cluster_group_count++;

	if (group_index >= 512)
	{
		group_index = -1;
	}
	else
	{
		long group_offset = 4 * group_index;

		visible_items.cluster_group_visibility[group_offset + 3] = 0;
		visible_items.cluster_group_visibility[group_offset + 2] = 0;
		visible_items.cluster_group_visibility[group_offset + 1] = 0;
		visible_items.cluster_group_visibility[group_offset] = 0;
		visible_items.cluster_group_visibility[group_offset + (region_cluster_index >> 5)] |= 1 << (region_cluster_index & 0x1F);
	}

	return group_index;
}

_extern void _sub_10AC3F90(CDebugTextPrinter *const, char const *, ...);
_inline void __cdecl CDebugTextPrinter::WriteLine(char const *format, ...) // 0x10AC3F90
{
	mangled_x86(MANGLED_TODO, "?WriteLine@CDebugTextPrinter@@QAAXPBDZZ");
	// static ...; // 0x10AC4178
	// static ...; // 0x10AC4170
	// CDebugTextPrinter *const this;
	// char const *format;
	// short_rectangle2d bounds;
	// char *va;
	// void (*const interface_get_current_display_settings)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *);
	// char line[8192];
	// function call : void (*const)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *)
	todo("implement");
	_sub_10AC3F90(this, format);
}

// mangled_x86(MANGLED_DEFAULT, "??0CDebugTextPrinter@@QAE@XZ"); no body to assert in
_inline CDebugTextPrinter::CDebugTextPrinter() = default; // 0x10AC39E0

// mangled_x86(MANGLED_DEFAULT, "??1CDebugTextPrinter@@QAE@XZ"); no body to assert in
_inline CDebugTextPrinter::~CDebugTextPrinter() = default; // 0x10AC3AD0

_extern void _sub_10AC61B0();
void render_debug_visibility() // 0x10AC61B0
{
	mangled_x86(MANGLED_TODO, "?render_debug_visibility@@YAXXZ");
	// procedure flags: nofpo
	// static ...; // 0x10AC6534
	// static ...; // 0x10AC6528
	// static ...; // 0x10AC6520
	// long visible_parts;
	// s_render_object_globals *render_object_globals;
	// s_visible_items const &visible_items;
	// CDebugTextPrinter debugTextPrinter;
	{
		// long i;
		{
			// unsigned long value;
			{
				// long j;
			}
		}
	}
	todo("implement");
	_sub_10AC61B0();
}

void __fastcall c_visibility_collection__generate_cluster_visible_parts(void *thisptr, void *unused, s_visible_cluster *visible_cluster) // 0x10AC4B00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_visibility_collection__generate_cluster_visible_parts@@YIXPAX0PAUs_visible_cluster@@@Z");
	// s_visible_cluster *visible_cluster;
	// unsigned __int32 *(*const reserve_cluster_mesh_part_visibility)(__int32);
	// s_render_geometry *render_geometry;
	// s_mesh &mesh;
	// unsigned __int32 *visibility;
	// function call : s_render_geometry *(*const)(long)
	// function call : unsigned __int32 *(*const)(__int32)

	unsigned __int32 *(*const reserve_cluster_mesh_part_visibility)(__int32) = (unsigned __int32 *(*const)(__int32))0x686bc0;
	s_render_geometry *render_geometry = ((s_render_geometry *(*)(long))0xa2ef00)(visible_cluster->cluster_reference.bsp_index);
	s_mesh &mesh = render_geometry->meshes[visible_cluster->mesh_index];
	unsigned __int32 *visibility = reserve_cluster_mesh_part_visibility(mesh.parts.count);

	memset(visibility, -1, 4 * ((mesh.parts.count + 31) >> 5));

	visible_cluster->flags |= 8;
	visible_cluster->flags &= ~4;
}

s_structure_globals *get_structure_globals() // 0x10AC50A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_structure_globals@@YAPAUs_structure_globals@@XZ");
	// procedure flags: nofpo
	// long current_thread_index;
	// s_structure_globals *per_thread_globals;

	s_structure_globals *per_thread_globals = (s_structure_globals *)0x2497e88;
	long current_thread_index = tls_getd().current_thread_index;

	#line 248 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
		assert(current_thread_index == 1 || current_thread_index == 2);
		#line 236 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\visibility_patches.cpp"

	return &per_thread_globals[current_thread_index - 1];
}

_extern bool _sub_10AC7240(long, s_cluster_reference, bool, c_seam_connected_cluster_references *);
bool structure_seams_connected_cluster_references_get_reach(long scenario_index, s_cluster_reference cluster_reference, bool include_self, c_seam_connected_cluster_references *out_cluster_refs) // 0x10AC7240
{
	mangled_x86(MANGLED_TODO, "?structure_seams_connected_cluster_references_get_reach@@YA_NJUs_cluster_reference@@_NPAUc_seam_connected_cluster_references@@@Z");
	// c_seam_connected_cluster_references *out_cluster_refs;
	// s_scenario_zone_set_pvs &zone_set_pvs;
	// s_scenario_zone_set_bsp_seam_cluster_mapping &cluster_mapping;
	// long bsp_pvs_index;
	// s_scenario *scenario;
	// s_scenario_zone_set &zone_set;
	// s_scenario_zone_set_bsp_pvs &bsp_pvs;
	{
		// long i;
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : long (*const)()
	todo("implement");
	bool __result = _sub_10AC7240(scenario_index, cluster_reference, include_self, out_cluster_refs);
	return __result;
}

_extern bool _sub_10AC6AE0(long, s_cluster_reference, bool, c_seam_connected_cluster_references *);
bool structure_seams_connected_cluster_references_get_h3(long scenario_index, s_cluster_reference cluster_reference, bool add_self, c_seam_connected_cluster_references *out_cluster_refs) // 0x10AC6AE0
{
	mangled_x86(MANGLED_TODO, "?structure_seams_connected_cluster_references_get_h3@@YA_NJUs_cluster_reference@@_NPAUc_seam_connected_cluster_references@@@Z");
	// static ...; // 0x10AC7010
	// long scenario_index;
	// s_cluster_reference cluster_reference;
	// bool add_self;
	// c_seam_connected_cluster_references *out_cluster_refs;
	// s_scenario_structure_bsp *structure;
	// s_scenario *scenario;
	// s_structure_cluster &structure_cluster;
	{
		// c_tag_block<char> &<range>$L0;
		// char *<begin>$L0;
		// char *<end>$L0;
		{
			// long seam_index;
			{
				// bool above;
				// bool bad_connection;
				// s_seam_mapping const &mapping;
				{
					// long cluster_mapping_index;
					{
						// s_seam_mapping::s_seam_cluster_mapping const &cluster_mapping;
						{
							// s_cluster_reference cluster_ref;
						}
					}
				}
				{
					{
						{
						}
					}
				}
			}
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : s_scenario_structure_bsp *(*const)(s_scenario *, long)
	todo("implement");
	bool __result = _sub_10AC6AE0(scenario_index, cluster_reference, add_self, out_cluster_refs);
	return __result;
}

bool structure_seams_connected_cluster_references_get_hook(long scenario_index, s_cluster_reference cluster_reference, bool include_self, c_seam_connected_cluster_references *out_cluster_refs) // 0x10AC71B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?structure_seams_connected_cluster_references_get_hook@@YA_NJUs_cluster_reference@@_NPAUc_seam_connected_cluster_references@@@Z");
	// c_seam_connected_cluster_references *out_cluster_refs;
	// s_scenario_structure_bsp *structure;
	// function call : s_scenario_structure_bsp *(*const)(long)

	s_scenario_structure_bsp *structure_bsp = global_structure_bsp_get(cluster_reference.bsp_index);

	return structure_seams_connected_cluster_references_get_h3(scenario_index, cluster_reference, include_self, out_cluster_refs);
}

_extern void _sub_10AC7A10();
void visibility_patches_apply() // 0x10AC7A10
{
	mangled_x86(MANGLED_TODO, "?visibility_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_10AC7A10();
}

/* ---------- private code */

extern "C" void sub_687070_hook(__int32 region_index, __int32 cluster_index) // 0x10AC75B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_sub_687070_hook");
	// sub_687070_hook
	// __int32 cluster_index;
	// long index;

	int index = 4 * region_index + (cluster_index >> 5);
	c_visible_items::get_global_items().cluster_group_visibility[index] |= 1 << (cluster_index & 0x1F);
}

extern "C" unsigned long *sub_686BC0_hook(long part_count) // 0x10AC74E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_sub_686BC0_hook");
	// sub_686BC0_hook
	// long part_count;
	// unsigned long *result;
	// s_visible_items &visible_items;
		// long allocation_size;

	s_visible_items &visible_items = c_visible_items::get_global_items();
	unsigned long *result;

	if (part_count <= 0)
	{
		result = nullptr;
	}
	else
	{
		long allocation_size = (part_count + 31) >> 5;

		if (allocation_size + visible_items.cluster_mesh_part_visibility_size >= 512)
		{
			result = visible_items.cluster_mesh_part_visibility;
		}
		else
		{
			result = &visible_items.cluster_mesh_part_visibility[visible_items.cluster_mesh_part_visibility_size];
			visible_items.cluster_mesh_part_visibility_size += allocation_size;
		}
	}

	return result;
}

_extern void _sub_10AC5500();
extern "C" void patch_visibility() // 0x10AC5500
{
	// patch_visibility
	// procedure flags: nofpo
	// long object_base;
	// long offset;
	todo("implement");
	_sub_10AC5500();
}

_extern void _sub_10AC5210();
extern "C" void patch_render_object_globals() // 0x10AC5210
{
	// patch_render_object_globals
	// procedure flags: nofpo
	// long offset;
	todo("implement");
	_sub_10AC5210();
}

extern "C" bool structure_instanced_geometry_mark(long structure_bsp_index, long instance_index) // 0x10AC66A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_structure_instanced_geometry_mark");
	// structure_instanced_geometry_mark
	// long instance_index;
	// bool is_marked;
	// unsigned long *bit_vector;
	// unsigned long bit_mask;
	// long dword_index;
	// s_structure_globals *structure_globals;

	s_structure_globals *structure_globals = get_structure_globals();

	#line 400 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
		assert(structure_globals->instanced_geometry_marker_initialized);
		#line 412 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\visibility_patches.cpp"

	unsigned long *bit_vector = structure_globals->instanced_geometry_marker_bit_vectors[structure_bsp_index];
	long dword_index = instance_index >> 5;
	unsigned long bit_mask = 1 << (instance_index & 0x1F);
	bool is_marked = (bit_vector[dword_index] & bit_mask) != 0;

	bit_vector[dword_index] |= bit_mask;

	return !is_marked;
}

extern "C" bool structure_instanced_geometry_mark_get_user_data(short structure_bsp_index, short instance_index, long *user_data) // 0x10AC67D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_structure_instanced_geometry_mark_get_user_data");
	// structure_instanced_geometry_mark_get_user_data
	// long *user_data;

	#line 426 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
		assert(!"should no longer be used");
		#line 432 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\visibility_patches.cpp"

	return false;
}

extern "C" bool structure_instanced_geometry_mark_with_user_data(short structure_bsp_index, short instance_index, long user_data) // 0x10AC6840
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_structure_instanced_geometry_mark_with_user_data");
	// structure_instanced_geometry_mark_with_user_data
	// long user_data;

	#line 438 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
		assert(!"should no longer be used");
		#line 444 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\visibility_patches.cpp"

	return false;
}

extern "C" void structure_instanced_geometry_marker_begin() // 0x10AC68B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_structure_instanced_geometry_marker_begin");
	// structure_instanced_geometry_marker_begin
	// procedure flags: nofpo
	// s_structure_globals *structure_globals;

	s_structure_globals *structure_globals = get_structure_globals();

	#line 446 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
		assert(!structure_globals->instanced_geometry_marker_initialized);
		#line 454 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\visibility_patches.cpp"

	structure_globals->instanced_geometry_marker_initialized = true;
	memset(structure_globals->instanced_geometry_marker_bit_vectors, 0, sizeof(structure_globals->instanced_geometry_marker_bit_vectors));
}

extern "C" void structure_instanced_geometry_marker_end() // 0x10AC6960
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_structure_instanced_geometry_marker_end");
	// structure_instanced_geometry_marker_end
	// procedure flags: nofpo
	// s_structure_globals *structure_globals;

	s_structure_globals *structure_globals = get_structure_globals();

	#line 468 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
		assert(structure_globals->instanced_geometry_marker_initialized);
		#line 476 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\visibility_patches.cpp"

	structure_globals->instanced_geometry_marker_initialized = false;
}

extern "C" bool structure_instanced_geometry_unmarked(short structure_bsp_index, short instance_index) // 0x10AC69F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_structure_instanced_geometry_unmarked");
	// structure_instanced_geometry_unmarked
	// short instance_index;
	// unsigned long *bit_vector;
	// unsigned long bit_mask;
	// long dword_index;
	// s_structure_globals *structure_globals;

	s_structure_globals *structure_globals = get_structure_globals();

	#line 472 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
		assert(structure_globals->instanced_geometry_marker_initialized);
		#line 483 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\visibility_patches.cpp"

	unsigned long *bit_vector = structure_globals->instanced_geometry_marker_bit_vectors[structure_bsp_index];
	long dword_index = instance_index >> 5;
	unsigned long bit_mask = 1 << (instance_index & 0x1F);

	return (bit_vector[dword_index] & bit_mask) == 0;
}

_extern void _sub_10AC43A0(c_visibility_collection *);
extern "C" void __fastcall c_visibility_collection__collect_structure_elements_from_region_hook(c_visibility_collection *thisptr) // 0x10AC43A0
{
	// c_visibility_collection__collect_structure_elements_from_region_hook
	// static ...; // 0x10AC4977
	// static ...; // 0x10AC4973
	// static ...; // 0x10AC4964
	// static ...; // 0x10AC4940
	// static ...; // 0x10AC4938
	// c_visibility_collection *thisptr;
	{
		// s_visible_items *visible_items;
		{
			// long region_cluster_index;
			{
				// long cluster_mesh_index;
				// s_visibility_cluster const *visible_cluster;
				// s_scenario_structure_bsp const *structure;
				// s_mesh const *cluster_mesh;
				// long dword_index;
				// s_visible_cluster *cluster;
				// long visibility_cluster_index;
				// long structure_index;
				// s_structure_cluster const *structure_cluster;
				// s_render_geometry const *structure_render_geometry;
				{
					// long instance_bucket_index;
					{
						// s_instance_part const *instance_bucket;
						// s_visible_instance_group *instance_list;
						// long instance_mesh_index;
						// long visibility_instance_list_index;
						{
							// long i;
							{
								// long structure_instance_index;
								// s_structure_instanced_geometry_instance const *structure_instance;
								{
									// bool shadow_casting;
									// bool fully_contained;
									// bool lit;
									{
										// long visibility_instance_index;
										// float instance_alpha;
										// s_visible_instance *instance;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : s_render_geometry *(*const)(long)
	// function call : char (*const)(c_visibility_collection *, real_point3d const *, float, short, bool, bool *, bool *, bool *)
	// function call : float (*const)(s_structure_instanced_geometry_instance const *, long)
	// function call : void (*const)(c_visibility_collection *)
	todo("implement");
	_sub_10AC43A0(thisptr);
}

extern "C" unsigned char const *scenario_pvs_connected_clusters_get_hook(s_cluster_reference cluster_reference, long *out_count) // 0x10AC6630
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_scenario_pvs_connected_clusters_get_hook");
	// scenario_pvs_connected_clusters_get_hook
	// long *out_count;
	// unsigned char const *(*const scenario_pvs_connected_clusters_get)(s_cluster_reference, long *);
	// function call : unsigned char const *(*const)(s_cluster_reference, long *)

	unsigned char const *(__cdecl *const scenario_pvs_connected_clusters_get)(s_cluster_reference, long *) = (unsigned char const *(__cdecl *const)(s_cluster_reference, long *))0x5f0e40;

	return scenario_pvs_connected_clusters_get(cluster_reference, out_count);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_cluster_reference>::try_get_element(__int32, s_cluster_reference **) const;
template bool c_tag_block<s_scenario_zone_set>::try_get_element(__int32, s_scenario_zone_set **) const;
template bool c_tag_block<s_scenario_zone_set_bsp_pvs>::try_get_element(__int32, s_scenario_zone_set_bsp_pvs **) const;
template bool c_tag_block<s_scenario_zone_set_bsp_seam_cluster_mapping>::try_get_element(__int32, s_scenario_zone_set_bsp_seam_cluster_mapping **) const;
template bool c_tag_block<s_scenario_zone_set_pvs>::try_get_element(__int32, s_scenario_zone_set_pvs **) const;
template bool s_static_array<s_cluster_reference,64>::valid(__int32);
template bool s_static_array<s_seam_mapping,128>::valid(__int32);
template c_tag_block_flags<s_scenario_structure_bsp_reference,long>::operator long() const;
template c_tag_block_index<s_scenario_zone_set_pvs,long>::operator long() const;
template char * c_tag_block<char>::begin();
template char * c_tag_block<char>::end();
template long s_simple_list<s_visible_cluster,1392>::add();
template long s_simple_list<s_visible_instance,4608>::add();
template long s_simple_list<s_visible_instance_group,4096>::add();
template long s_static_array<s_cluster_reference,64>::get_count();
template s_cluster_reference & c_tag_block<s_cluster_reference>::operator[](__int32);
template s_cluster_reference & s_static_array<s_cluster_reference,64>::operator[](long);
template s_cluster_reference * c_tag_block<s_cluster_reference>::get_element(__int32) const;
template s_instance_part const & c_tag_block<s_instance_part>::operator[](__int32) const;
template s_instance_part_contents const & c_tag_block<s_instance_part_contents>::operator[](__int32) const;
template s_scenario_zone_set & c_tag_block<s_scenario_zone_set>::operator[](__int32);
template s_scenario_zone_set * c_tag_block<s_scenario_zone_set>::get_element(__int32) const;
template s_scenario_zone_set_bsp_pvs & c_tag_block<s_scenario_zone_set_bsp_pvs>::operator[](__int32);
template s_scenario_zone_set_bsp_pvs * c_tag_block<s_scenario_zone_set_bsp_pvs>::get_element(__int32) const;
template s_scenario_zone_set_bsp_seam_cluster_mapping & c_tag_block<s_scenario_zone_set_bsp_seam_cluster_mapping>::operator[](__int32);
template s_scenario_zone_set_bsp_seam_cluster_mapping * c_tag_block<s_scenario_zone_set_bsp_seam_cluster_mapping>::get_element(__int32) const;
template s_scenario_zone_set_pvs & c_tag_block<s_scenario_zone_set_pvs>::operator[](__int32);
template s_scenario_zone_set_pvs * c_tag_block<s_scenario_zone_set_pvs>::get_element(__int32) const;
template s_seam_mapping & s_static_array<s_seam_mapping,128>::operator[](long);
template s_structure_cluster const & c_tag_block<s_structure_cluster>::operator[](__int32) const;
