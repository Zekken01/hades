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

#include "Modules/ModuleDebug.hpp"  // hades: added for 0x10AC61B0

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

// hades: moved from hades/recovered_types.h, where its member types were not visible
struct CDebugTextPrinter
{
	static real_argb_color const kDefaultColor;
	real_argb_color m_color = kDefaultColor; // 0x0
	c_rasterizer_draw_string m_drawString; // 0x10
	c_font_cache_mt_safe m_fontCache; // 0x838
	int m_yOffset = 0; // 0x840
public:
	void WriteLine(char const *, ...);
	CDebugTextPrinter();
	~CDebugTextPrinter();
};
static_assert32(sizeof(CDebugTextPrinter) == 2116, "Invalid CDebugTextPrinter size");

// CDebugTextPrinter is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const scenario_structure_bsp_get = reinterpret_cast<s_scenario_structure_bsp *(*)(s_scenario *, long)>(0x766280);
}
#line 131

#define NONE -1  // hades: added for 0x10AC6AE0

long scenario_pvs_bsp_pvs_index_get(unsigned long bsp_zone_flags, long bsp_index);  // hades: added for 0x10AC7240
extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x10AC7240

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
void patch_visibility();
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

_inline void __cdecl CDebugTextPrinter::WriteLine(char const *format, ...) // 0x10AC3F90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?WriteLine@CDebugTextPrinter@@QAAXPBDZZ");
	// static ...; // 0x10AC4178
	// static ...; // 0x10AC4170
	// CDebugTextPrinter *const this;
	// char const *format;
	// short_rectangle2d bounds;
	// char *va;
	// void (*const interface_get_current_display_settings)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *);
	// char line[8192];
	// function call : void (*const)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *)

	void (*const interface_get_current_display_settings)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *) = reinterpret_cast<void (*)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *)>(0xA9FAA0);
	char line[8192];
	va_list va;
	va_start(va, format);
	vsprintf_s(line, format, va);
	va_end(va);
	short_rectangle2d bounds;
	interface_get_current_display_settings(nullptr, nullptr, nullptr, &bounds);
	m_drawString.set_font(0);
	m_drawString.set_justification(0);
	m_drawString.set_color(m_color);
	m_drawString.set_shadow_color(real_argb_color{ 0.0f, 0.0f, 0.0f, 1.0f });
	bounds.y0 += m_yOffset;
	m_yOffset += m_drawString.get_line_height();
	m_drawString.set_bounds(bounds);
	m_drawString.draw(&m_fontCache, line);
}

// mangled_x86(MANGLED_DEFAULT, "??0CDebugTextPrinter@@QAE@XZ"); no body to assert in
_inline CDebugTextPrinter::CDebugTextPrinter() = default; // 0x10AC39E0

// mangled_x86(MANGLED_DEFAULT, "??1CDebugTextPrinter@@QAE@XZ"); no body to assert in
_inline CDebugTextPrinter::~CDebugTextPrinter() = default; // 0x10AC3AD0

void render_debug_visibility() // 0x10AC61B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_visibility@@YAXXZ");
	// procedure flags: nofpo
	// static ...; // 0x10AC6534
	// static ...; // 0x10AC6528
	// static ...; // 0x10AC6520
	// long visible_parts;
	// s_render_object_globals *render_object_globals;
	// s_visible_items const &visible_items;
	// CDebugTextPrinter debugTextPrinter;
		// long i;
			// unsigned long value;
				// long j;

	if (!Utils::Singleton<Modules::ModuleDebug>::Instance().VarVisibility->ValueInt)
		return;
	CDebugTextPrinter debugTextPrinter;
	s_visible_items const &visible_items = c_visible_items::get_global_items();
	long visible_parts = 0;
	for (long i = 0; i < visible_items.cluster_mesh_part_visibility_size; i++)
	{
		unsigned long value = visible_items.cluster_mesh_part_visibility[i];
		for (long j = 0; j < 32; j++)
		{
			if ((value >> j) & 1)
				visible_parts++;
		}
	}
	debugTextPrinter.WriteLine("visibility objects: %d/%d", visible_items.objects.count, visible_items.objects.max_count);
	debugTextPrinter.WriteLine("visibility object hierarchies: %d/%d", visible_items.object_hierarchies.count, visible_items.object_hierarchies.max_count);
	debugTextPrinter.WriteLine("visibility instance groups: %d/%d", visible_items.instance_groups.count, visible_items.instance_groups.max_count);
	debugTextPrinter.WriteLine("visibility instances: %d/%d", visible_items.instances.count, visible_items.instances.max_count);
	debugTextPrinter.WriteLine("visibility clusters: %d/%d", visible_items.clusters.count, visible_items.clusters.max_count);
	debugTextPrinter.WriteLine("visibility lights: %d/%d", visible_items.lights.count, visible_items.lights.max_count);
	debugTextPrinter.WriteLine("visibility skies: %d/%d", visible_items.skies.count, visible_items.skies.max_count);
	debugTextPrinter.WriteLine("visibility cluster mesh part alloc: %d/%d", visible_items.cluster_mesh_part_visibility_size, 512);
	debugTextPrinter.WriteLine("visibility cluster mesh part %d/%d", visible_parts, 4096);
	debugTextPrinter.WriteLine("visibility clusters groups: %d/%d", visible_items.cluster_group_count, 512);
	s_render_object_globals *render_object_globals = render_object_globals_get();
	debugTextPrinter.WriteLine("render objects: %d/%d", render_object_globals->object_count, 2048);
	debugTextPrinter.WriteLine("render object mesh parts: %d/%d", render_object_globals->part_count, 0x2000);
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

	#line 303 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
		assert(current_thread_index == 1 || current_thread_index == 2);
		#line 312 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\visibility_patches.cpp"

	return &per_thread_globals[current_thread_index - 1];
}

bool structure_seams_connected_cluster_references_get_reach(long scenario_index, s_cluster_reference cluster_reference, bool include_self, c_seam_connected_cluster_references *out_cluster_refs) // 0x10AC7240
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?structure_seams_connected_cluster_references_get_reach@@YA_NJUs_cluster_reference@@_NPAUc_seam_connected_cluster_references@@@Z");
	// c_seam_connected_cluster_references *out_cluster_refs;
	// s_scenario_zone_set_pvs &zone_set_pvs;
	// s_scenario_zone_set_bsp_seam_cluster_mapping &cluster_mapping;
	// long bsp_pvs_index;
	// s_scenario *scenario;
	// s_scenario_zone_set &zone_set;
	// s_scenario_zone_set_bsp_pvs &bsp_pvs;
		// long i;
	// function call : void *(*const)(unsigned long, long)
	// function call : long (*const)()

	out_cluster_refs->reference_count = 0;
	if (include_self)
		out_cluster_refs->references[out_cluster_refs->reference_count++] = cluster_reference;
	s_scenario *scenario = (s_scenario *)tag_get('scnr', scenario_index);
	s_scenario_zone_set &zone_set = scenario->zone_sets[((long (*)())0x4EBA20)()];
	s_scenario_zone_set_pvs &zone_set_pvs = scenario->zone_set_pvs[zone_set.pvs_index];
	long bsp_pvs_index = scenario_pvs_bsp_pvs_index_get(zone_set.bsp_zone_flags, cluster_reference.bsp_index);
	s_scenario_zone_set_bsp_pvs &bsp_pvs = zone_set_pvs.structure_bsp_pvs[bsp_pvs_index];
	s_scenario_zone_set_bsp_seam_cluster_mapping &cluster_mapping = bsp_pvs.cluster_mapping[cluster_reference.cluster_index];
	for (long i = 0; i < cluster_mapping.connected_clusters.count; i++)
	{
		if (out_cluster_refs->reference_count == out_cluster_refs->references.get_count())
		{
			#line 334 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
				assert(!"Connected cluster limit reached. Talk to unk");
				#line 346 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
			break;
		}
		out_cluster_refs->references[out_cluster_refs->reference_count++] = cluster_mapping.connected_clusters[i];
	}
	return true;
}

bool structure_seams_connected_cluster_references_get_h3(long scenario_index, s_cluster_reference cluster_reference, bool add_self, c_seam_connected_cluster_references *out_cluster_refs) // 0x10AC6AE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?structure_seams_connected_cluster_references_get_h3@@YA_NJUs_cluster_reference@@_NPAUc_seam_connected_cluster_references@@@Z");
	// static ...; // 0x10AC7010
	// long scenario_index;
	// s_cluster_reference cluster_reference;
	// bool add_self;
	// c_seam_connected_cluster_references *out_cluster_refs;
	// s_scenario_structure_bsp *structure;
	// s_scenario *scenario;
	// s_structure_cluster &structure_cluster;
		// c_tag_block<char> &<range>$L0;
		// char *<begin>$L0;
		// char *<end>$L0;
			// long seam_index;
				// bool above;
				// bool bad_connection;
				// s_seam_mapping const &mapping;
					// long cluster_mapping_index;
						// s_seam_mapping::s_seam_cluster_mapping const &cluster_mapping;
							// s_cluster_reference cluster_ref;
	// function call : void *(*const)(unsigned long, long)
	// function call : s_scenario_structure_bsp *(*const)(s_scenario *, long)

	s_scenario *scenario = (s_scenario *)tag_get('scnr', scenario_index);
	s_scenario_structure_bsp *structure = eldorado::scenario_structure_bsp_get(scenario, cluster_reference.bsp_index);
	s_structure_cluster &structure_cluster = structure->clusters[cluster_reference.cluster_index];
	if (add_self)
		out_cluster_refs->references[out_cluster_refs->reference_count++] = cluster_reference;
	for (long seam_index : structure_cluster.seam_indices)
	{
		s_seam_mapping const &mapping = tls_getd().structure_seam_globals->mappings[seam_index];
		bool above = mapping.bsp_indices[1] == cluster_reference.bsp_index;
		if (mapping.bsp_indices[above] != cluster_reference.bsp_index || mapping.bsp_indices[!above] == -1)
			continue;
		bool bad_connection = false;
		for (long cluster_mapping_index = 0; cluster_mapping_index < mapping.clusters_count; cluster_mapping_index++)
		{
			s_seam_mapping::s_seam_cluster_mapping const &cluster_mapping = mapping.clusters[cluster_mapping_index];
			#line 374 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
			assert((cluster_mapping.cluster_indices[above]==NONE)==(cluster_mapping.cluster_mapping_indices[above]==NONE));
			#line 395 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
			if (cluster_mapping.cluster_indices[above] == cluster_reference.cluster_index)
			{
				if (cluster_mapping.cluster_indices[!above] == -1)
					bad_connection = true;
				else
				{
					s_cluster_reference cluster_ref = { mapping.bsp_indices[!above], (unsigned char)cluster_mapping.cluster_indices[!above] };
					out_cluster_refs->insert(cluster_ref);
				}
			}
		}
		if (bad_connection)
		{
			for (long cluster_mapping_index = 0; cluster_mapping_index < mapping.clusters_count; cluster_mapping_index++)
			{
				s_seam_mapping::s_seam_cluster_mapping const &cluster_mapping = mapping.clusters[cluster_mapping_index];
				#line 397 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
				assert((cluster_mapping.cluster_indices[above] == NONE) == (cluster_mapping.cluster_mapping_indices[above] == NONE));
				#line 414 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
				if (cluster_mapping.cluster_indices[above] == -1)
				{
					s_cluster_reference cluster_ref = { mapping.bsp_indices[!above], (unsigned char)cluster_mapping.cluster_indices[!above] };
					out_cluster_refs->insert(cluster_ref);
				}
			}
		}
	}
	return out_cluster_refs->reference_count != 0;
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

void visibility_patches_apply() // 0x10AC7A10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?visibility_patches_apply@@YAXXZ");
	// procedure flags: nofpo

	patch_visibility();
	patch_render_object_globals();
	Hook(0x573E10, c_visibility_collection__collect_structure_elements_from_region_hook).Apply();
	Hook(0x278240, structure_instanced_geometry_mark).Apply();
	Hook(0x278290, structure_instanced_geometry_mark_get_user_data).Apply();
	Hook(0x2782E0, structure_instanced_geometry_mark_with_user_data).Apply();
	Hook(0x278310, structure_instanced_geometry_marker_begin).Apply();
	Hook(0x278350, structure_instanced_geometry_marker_end).Apply();
	Hook(0x278370, structure_instanced_geometry_unmarked).Apply();
	Hook(0x56FE77, scenario_pvs_connected_clusters_get_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x570DEF, scenario_pvs_connected_clusters_get_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x1F4350, structure_seams_connected_cluster_references_get_hook).Apply();
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

void patch_visibility() // 0x10AC5500
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_patch_visibility");
	// patch_visibility
	// procedure flags: nofpo
	// long object_base;
	// long offset;

	Hook(0x286FD0, c_visible_items::push_marker).Apply();
	Hook(0x286DE0, c_visible_items::pop_marker).Apply();
	Hook(0x286BA0, c_visible_items::get_global_items).Apply();
	Hook(0x286950, c_visible_items::clear_all).Apply();
	Hook(0x2870A0, sub_6870A0_hook).Apply();
	Hook(0x286BC0, sub_686BC0_hook).Apply();
	Hook(0x287070, sub_687070_hook).Apply();
	long offset;
	long object_base;
	offset = 0x6004;
	*(long *)0x686788 = offset;
	*(long *)0x9736A0 = offset;
	*(long *)0xA52D8B = offset;
	*(long *)0xA53465 = offset;
	*(long *)0xA534E9 = offset;
	*(long *)0xA68CE6 = offset;
	*(long *)0xA78C5C = offset;
	*(long *)0xA78CAD = offset;
	*(long *)0xA793FC = offset;
	*(long *)0xA79447 = offset;
	*(long *)0xA79761 = offset;
	*(long *)0x14E785C = offset;
	offset += 2;
	*(long *)0x973825 = offset;
	*(long *)0x973832 = offset;
	*(long *)0xA52CBD = offset;
	*(long *)0xA5303B = offset;
	*(long *)0xA79B4E = offset;
	*(long *)0xA79D2F = offset;
	offset += 2;
	object_base = offset;
	*(long *)0x97370F = offset;
	*(long *)0xA533EB = offset;
	*(long *)0x14E7A1D = offset;
	*(long *)0xA52DB2 = offset / 8;
	*(long *)0xA796FD = offset / 8;
	*(long *)0xA798CC = offset / 8;
	*(long *)0xA79BBF = offset / 8;
	offset = object_base + 104;
	*(long *)0x5BD3B3 = offset;
	offset = object_base + 108;
	*(long *)0x14E7A59 = offset;
	offset = object_base + 112;
	*(long *)0x973408 = offset;
	offset = 0x3A808;
	*(long *)0x973FC5 = offset;
	*(long *)0xA2EF8B = offset;
	*(long *)0xA2EF96 = offset;
	*(long *)0xA305EE = offset;
	offset += 2;
	*(long *)0x973FBB = offset;
	*(long *)0x973FD5 = offset;
	*(long *)0x974208 = offset;
	*(long *)0x974B83 = offset;
	*(long *)0x974C34 = offset;
	*(long *)0xA305E8 = offset;
	offset += 2;
	#line 575 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
		assert(offset % sizeof(s_visible_instance_group) == 0);
		#line 571 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
	*(long *)0x973FE7 = offset / sizeof(s_visible_instance_group);
	*(long *)0x974B90 = offset / sizeof(s_visible_instance_group);
	*(long *)0x974BAE = offset / sizeof(s_visible_instance_group);
	*(long *)0xA3066F = offset / sizeof(s_visible_instance_group);
	offset = 0x4680C;
	*(long *)0x9740E5 = offset;
	*(long *)0xA53079 = offset;
	*(long *)0x14E7935 = offset;
	*(long *)0x14E7975 = offset;
	offset += 2;
	*(long *)0x97400F = offset;
	*(long *)0x9740DE = offset;
	*(long *)0x9740F8 = offset;
	*(long *)0x14E7AE1 = offset;
	offset += 2;
	#line 596 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
		assert((offset % sizeof(s_visible_instance)) == 0);
		#line 589 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
	*(long *)0x97410A = offset / sizeof(s_visible_instance);
	*(long *)0x9741C3 = offset / sizeof(s_visible_instance);
	*(long *)0x974BD3 = offset / sizeof(s_visible_instance);
	*(long *)0xA3072E = offset / sizeof(s_visible_instance);
	*(long *)0xA530A9 = offset / sizeof(s_visible_instance);
	*(long *)0xA5310D = offset / sizeof(s_visible_instance);
	*(long *)0x14E7AF9 = offset / sizeof(s_visible_instance);
	offset += 2;
	*(long *)0x14E7B0E = offset;
	offset = 0x58810;
	*(long *)0x973F2A = offset;
	*(long *)0xA302B4 = offset;
	*(long *)0xA305B8 = offset;
	*(long *)0x14E78C6 = offset;
	*(long *)0x14E7905 = offset;
	offset += 2;
	*(long *)0x973F23 = offset;
	*(long *)0x973F36 = offset;
	*(long *)0x974B1D = offset;
	*(long *)0x974B5E = offset;
	offset += 2;
	*(long *)0x973F4A = offset;
	*(long *)0x974B2E = offset;
	*(long *)0x974B46 = offset;
	offset += 2;
	*(long *)0x973F5D = offset;
	offset += 2;
	*(long *)0x973F67 = offset;
	offset += 2;
	*(long *)0x973F6F = offset;
	offset += 2;
	*(long *)0x973F7E = offset;
	offset += 4;
	*(long *)0x973F85 = offset;
	offset += 2;
	offset = 0x5DF14;
	*(long *)0x9735B6 = offset;
	offset += 2;
	*(long *)0xA66B6B = offset;
	*(long *)0xA67B3A = offset;
	offset += 2;
	*(long *)0x9735D7 = offset;
	*(long *)0xA66BB0 = offset;
	*(long *)0xA67B5B = offset;
	offset = 0x5DFE0;
	*(long *)0x973142 = offset;
	*(long *)0xA51CFC = offset;
	offset += 2;
	*(long *)0x9732AC = offset;
	*(long *)0xA5246F = offset;
	*(long *)0xBBF5B8 = offset;
	offset += 2;
	*(long *)0x973164 = offset;
	*(long *)0x9732C4 = offset;
	*(long *)0xA52481 = offset;
	offset = 0x60800;
	*(long *)0x5BD2EB = offset;
	*(long *)0x5BD397 = offset;
	*(long *)0x973027 = offset;
	*(long *)0xA533AF = offset;
	*(long *)0x14E7ACF = (long)&c_visible_items::get_global_items() + 0x4680E;
	*(long *)0xA68C9A = (long)&c_visible_items::get_global_items() + 0x2;
	*(long *)0x14E79B7 = (long)&c_visible_items::get_global_items() + 0x2;
}

extern "C" void patch_render_object_globals() // 0x10AC5210
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_patch_render_object_globals");
	// patch_render_object_globals
	// procedure flags: nofpo
	// long offset;

	long offset;
	offset = 0x8000;
	*(long *)0xA77CC7 = offset;
	*(long *)0xA77CFF = offset;
	*(long *)0xA77D08 = offset;
	*(long *)0xA7821A = offset;
	*(long *)0xA78253 = offset;
	*(long *)0xA78A84 = offset;
	*(long *)0xA78C15 = offset;
	*(long *)0xA79237 = offset;
	*(long *)0xA79328 = offset;
	*(long *)0xA793BF = offset;
	*(long *)0xA7977F = offset;
	*(long *)0xA797C1 = offset;
	*(long *)0xA797CA = offset;
	offset = 0x8004;
	*(long *)0xA77B04 = offset;
	*(long *)0xA784B9 = offset;
	*(long *)0xA785DF = offset;
	*(long *)0xA78B36 = offset;
	*(long *)0xA78F77 = offset;
	*(long *)0xA7912C = offset;
	*(long *)0xA791D1 = offset;
	offset = 0x40004;
	*(long *)0xA77ADB = offset;
	*(long *)0xA77AEF = offset;
	*(long *)0xA77CDD = offset;
	*(long *)0xA78227 = offset;
	*(long *)0xA78266 = offset;
	*(long *)0xA79241 = offset;
	*(long *)0xA7933B = offset;
	*(long *)0xA793CC = offset;
	*(long *)0xA7979F = offset;
	offset = 0x40008;
	*(long *)0xA79B27 = offset;
	*(long *)0xA7989F = offset;
	*(long *)0xA7984D = offset;
	*(long *)0xA7978B = offset;
	*(long *)0xA79255 = offset;
	*(long *)0xA77DC7 = offset;
	*(long *)0xA77CCD = offset;
	offset = 0x4000C;
	*(long *)0xA78207 = offset;
	*(long *)0xA7820D = offset;
	*(long *)0xA78247 = offset;
	*(long *)0xA7824D = offset;
	*(long *)0xA78260 = offset;
	*(long *)0xA78A74 = offset;
	*(long *)0xA7924B = offset;
	*(long *)0xA7931C = offset;
	*(long *)0xA79322 = offset;
	*(long *)0xA79335 = offset;
	*(long *)0xA793AB = offset;
	*(long *)0xA793B1 = offset;
	offset = 0x40010;
	*(long *)0xA7825A = offset;
	*(long *)0xA78A7B = offset;
	*(long *)0xA7932F = offset;
	offset = 0x40014;
	*(long *)0xA78214 = offset;
	*(long *)0xA793B9 = offset;
	offset = 0x40028;
	*(long *)0xA7826D = offset;
	*(long *)0xA79342 = offset;
	offset = 0x4002C;
	*(long *)0xA78221 = offset;
	*(long *)0xA793C6 = offset;
	offset = 0x801C;
	*(long *)0xA781EA = offset;
	*(long *)0xA7A4A7 = offset;
	*(long *)0xA77AE1 = 0x2000;
	*(long *)0xA77CD4 = 0x800;
	*(long *)0xA79792 = 0x800;
	*(long *)0xA7814C = 0x40040;
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

	#line 740 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
		assert(structure_globals->instanced_geometry_marker_initialized);
		#line 753 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\visibility_patches.cpp"

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

	#line 766 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
		assert(!"should no longer be used");
		#line 773 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\visibility_patches.cpp"

	return false;
}

extern "C" bool structure_instanced_geometry_mark_with_user_data(short structure_bsp_index, short instance_index, long user_data) // 0x10AC6840
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_structure_instanced_geometry_mark_with_user_data");
	// structure_instanced_geometry_mark_with_user_data
	// long user_data;

	#line 779 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
		assert(!"should no longer be used");
		#line 786 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\visibility_patches.cpp"

	return false;
}

extern "C" void structure_instanced_geometry_marker_begin() // 0x10AC68B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_structure_instanced_geometry_marker_begin");
	// structure_instanced_geometry_marker_begin
	// procedure flags: nofpo
	// s_structure_globals *structure_globals;

	s_structure_globals *structure_globals = get_structure_globals();

	#line 793 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
		assert(!structure_globals->instanced_geometry_marker_initialized);
		#line 802 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\visibility_patches.cpp"

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

	#line 810 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
		assert(structure_globals->instanced_geometry_marker_initialized);
		#line 819 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\visibility_patches.cpp"

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

	#line 826 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\visibility_patches.cpp"
		assert(structure_globals->instanced_geometry_marker_initialized);
		#line 838 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\visibility_patches.cpp"

	unsigned long *bit_vector = structure_globals->instanced_geometry_marker_bit_vectors[structure_bsp_index];
	long dword_index = instance_index >> 5;
	unsigned long bit_mask = 1 << (instance_index & 0x1F);

	return (bit_vector[dword_index] & bit_mask) == 0;
}

extern "C" void __fastcall c_visibility_collection__collect_structure_elements_from_region_hook(c_visibility_collection *thisptr) // 0x10AC43A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "@c_visibility_collection__collect_structure_elements_from_region_hook@4");
	// c_visibility_collection__collect_structure_elements_from_region_hook
	// static ...; // 0x10AC4977
	// static ...; // 0x10AC4973
	// static ...; // 0x10AC4964
	// static ...; // 0x10AC4940
	// static ...; // 0x10AC4938
	// c_visibility_collection *thisptr;
		// s_visible_items *visible_items;
			// long region_cluster_index;
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
					// long instance_bucket_index;
						// s_instance_part const *instance_bucket;
						// s_visible_instance_group *instance_list;
						// long instance_mesh_index;
						// long visibility_instance_list_index;
							// long i;
								// long structure_instance_index;
								// s_structure_instanced_geometry_instance const *structure_instance;
									// bool shadow_casting;
									// bool fully_contained;
									// bool lit;
										// long visibility_instance_index;
										// float instance_alpha;
										// s_visible_instance *instance;
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : s_render_geometry *(*const)(long)
	// function call : char (*const)(c_visibility_collection *, real_point3d const *, float, short, bool, bool *, bool *, bool *)
	// function call : float (*const)(s_structure_instanced_geometry_instance const *, long)
	// function call : void (*const)(c_visibility_collection *)

	structure_instanced_geometry_marker_begin();
	if ((thisptr->visbility_region->flags & 0x10) == 0)
	{
		s_visible_items *visible_items = &c_visible_items::get_global_items();
		for (long region_cluster_index = 0; region_cluster_index < thisptr->visbility_region->cluster_count; region_cluster_index++)
		{
			s_visibility_cluster const *visible_cluster = &thisptr->visbility_region->clusters[region_cluster_index];
			long structure_index = visible_cluster->cluster_reference.bsp_index;
			s_scenario_structure_bsp const *structure = global_structure_bsp_get(structure_index);
			s_structure_cluster const *structure_cluster = &structure->clusters[visible_cluster->cluster_reference.cluster_index];
			s_render_geometry const *structure_render_geometry = ((s_render_geometry *(*const)(long))0xA2EF00)(structure_index);
			long cluster_mesh_index = structure_cluster->mesh_index;
			if (cluster_mesh_index < 0 || cluster_mesh_index >= structure_render_geometry->meshes.count)
				continue;
			long dword_index = (visible_cluster->cluster_reference.cluster_index >> 5) + 8 * visible_cluster->cluster_reference.bsp_index;
			thisptr->visbility_region->active_clusters_bit_vector[dword_index] |= 1 << (visible_cluster->cluster_reference.cluster_index & 0x1F);
			thisptr->visbility_region->region_cluster_mapping[visible_cluster->cluster_reference.bsp_index][visible_cluster->cluster_reference.cluster_index] = (char)region_cluster_index;
			long visibility_cluster_index = visible_items->clusters.add();
			if (visibility_cluster_index == -1)
				continue;
			s_visible_cluster *cluster = &visible_items->clusters.elements[visibility_cluster_index];
			cluster->flags = 3;
			cluster->cluster_reference = visible_cluster->cluster_reference;
			cluster->unknown = 0;
			cluster->region_cluster_index = (short)region_cluster_index;
			cluster->mesh_index = (short)cluster_mesh_index;
			cluster->mesh_part_visibility = nullptr;
			s_mesh const *cluster_mesh = &structure_render_geometry->meshes[cluster_mesh_index];
			for (long instance_bucket_index = 0; instance_bucket_index < cluster_mesh->instance_parts.count; instance_bucket_index++)
			{
				s_instance_part const *instance_bucket = &cluster_mesh->instance_parts[instance_bucket_index];
				long instance_mesh_index = instance_bucket->section1;
				long visibility_instance_list_index = visible_items->instance_groups.add();
				if (visibility_instance_list_index == -1)
					continue;
				s_visible_instance_group *instance_list = &visible_items->instance_groups.elements[visibility_instance_list_index];
				instance_list->cluster_reference = visible_cluster->cluster_reference;
				instance_list->instance_bucket_index = (short)instance_bucket_index;
				instance_list->first_index = visible_items->instances.count;
				instance_list->count = 0;
				instance_list->mesh_index = (short)instance_mesh_index;
				for (long i = 0; i < instance_bucket->contents.count; i++)
				{
					long structure_instance_index = instance_bucket->contents[i].value;
					s_structure_instanced_geometry_instance const *structure_instance = &structure->instanced_geometry_instances[structure_instance_index];
					if (structure_instanced_geometry_unmarked((short)structure_index, (short)structure_instance_index))
					{
						bool fully_contained;
						bool lit;
						bool shadow_casting;
						if (((char (__thiscall *const)(c_visibility_collection *, real_point3d const *, float, short, bool, bool *, bool *, bool *))0x6873A0)(thisptr, &structure_instance->bounding_sphere_offset, structure_instance->bounding_sphere_radius_minimum, (short)region_cluster_index, false, &fully_contained, &lit, &shadow_casting) || (thisptr->visbility_region->flags & 0x40) != 0)
						{
							float instance_alpha = ((float (*const)(s_structure_instanced_geometry_instance const *, long))0x974260)(structure_instance, structure_index);
							if (instance_alpha <= 0.0f)
								continue;
							long visibility_instance_index = visible_items->instances.add();
							if (visibility_instance_index == -1)
								continue;
							s_visible_instance *instance = &visible_items->instances.elements[visibility_instance_index];
							instance->flags = 3;
							instance->instance_index = (short)structure_instance_index;
							instance->structure_bsp_index = (short)structure_index;
							instance->group_index = -1;
							instance->mesh_part_visibility = nullptr;
							instance->alpha = (unsigned short)(instance_alpha * 255.0f);
							visible_items->instance_groups.elements[visibility_instance_list_index].count++;
							structure_instanced_geometry_mark(structure_index, structure_instance_index);
						}
					}
				}
				if (visible_items->instance_groups.elements[visibility_instance_list_index].count == 0)
					visible_items->instance_groups.count--;
			}
		}
	}
	((void (__thiscall *const)(c_visibility_collection *))0x974AF0)(thisptr);
	structure_instanced_geometry_marker_end();
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

/* ---------- data definitions */
real_argb_color const CDebugTextPrinter::kDefaultColor = { 1.0f, 1.0f, 1.0f, 1.0f };
