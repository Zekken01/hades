/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/forge/forge_globals.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/multiplayer_definitions.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/geometry/geometry_definitions.hpp"
#include "Blam/geometry/geometry_sampler.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/models/model_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_globals.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/render_globals.hpp"
#include "Blam/render/render_model.hpp"
#include "Blam/render/render_object.hpp"
#include "Blam/render/render_object_globals.hpp"
#include "Blam/render/render_structure.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/shaders/render_methods_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/visibility/visibility_items.hpp"
#include "Blam/visibility/visibility_object_render_info.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeObjectProperties.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/Reforge.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
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

class c_render_method;
struct real_matrix4x3;
struct real_point3d;
struct real_rgb_color;
struct real_vector3d;
struct s_compression_info;
struct s_forge_globals_definition;
struct s_game_globals;
struct s_geometry_material;
struct s_geometry_sample;
struct s_mesh;
struct s_model_definition;
struct s_multiplayer_globals_definition;
struct s_multiplayer_object_properties;
struct s_object_cached_render_state_datum;
struct s_object_data;
struct s_object_definition;
struct s_object_region_information;
struct s_part;
struct s_render_first_person_model;
struct s_render_geometry;
struct s_render_lighting;
struct s_render_model;
struct s_render_model_permutation;
struct s_render_model_region;
struct s_render_object;
struct s_shield_parameters;
struct s_render_object_info;
struct s_render_object_mesh_part;
struct s_shader_extern_info;
struct s_visible_items;
struct s_visible_object;
struct s_visible_object_hierarchy;
namespace Forge
{
	struct ForgeKillVolumeProperties;
	struct ReforgeObjectProperties;
}
namespace Forge
{
	namespace Reforge
	{
		struct SRenderMaterialParameters;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Forge {}
using namespace ::Forge;
namespace Forge
{
	namespace Reforge {}
	using namespace Forge::Reforge;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace RenderObject {}
	using namespace Patches::RenderObject;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

#include "Modules/ModuleDebug.hpp"  // hades: added for 0x108DF6D0
#include "Modules/ModuleForge.hpp"  // hades: added for 0x108DF6D0
extern bool (*const game_engine_is_sandbox)();  // hades: added for 0x108DF6D0
s_forge_globals_definition *forge_globals_get_definition();  // hades: added for 0x108DF6D0

extern s_multiplayer_object_properties *(*const object_get_multiplayer)(unsigned long);  // hades: added for 0x108DF3C0

namespace Forge::Reforge { bool IsReforgeObject(long objectIndex); }  // hades: added for 0X108DF640
namespace Forge { bool ObjectIsForgeScenery(long objectIndex); }  // hades: added for 0X108DF640

extern void *(__cdecl *const tag_get)(unsigned long, long);  // hades: added for 0X108E1E10
extern long (__cdecl *const tag_get_first_in_group)(unsigned long);  // hades: added for 0X108E1E10
extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0x108E1010

namespace Patches
{
	namespace RenderObject
	{
		extern void ApplyAll();
		extern bool GetPRTDisabled();
	}
}

void render_object_set_shield_impact(long element_index, void *definition);
bool object_should_render(long object_index);
void render_object_add_mesh_parts_hook(s_render_object *render_object, s_visible_object *render_info, long object_entry_point_flags, bool a4, bool has_shield_impact, bool isFpShit, bool camo);
void render_reforge_object_mesh_part(s_render_object_mesh_part *element, long entry_point, long entry_point_flags, bool a4, long material_index, ::Forge::Reforge::SRenderMaterialParameters const &parameters);
long object_get_prt_disabled(long object_index);
void render_object_mesh_part_hook(s_render_object_mesh_part *element, long entry_point, long entry_point_flags, bool a4);
bool object_sh_lightmap_sampling_disabled(long object_index);
long object_lighting_geometry_sample_hook(real_point3d *origin, real_vector3d *direction, __int32 a3, long object_index, char a5, char a6, s_geometry_sample *sample);
static s_game_globals *try_and_get_game_globals();
static real_rgb_color *network_get_team_color(real_rgb_color *color, long team);
bool object_always_updates_change_colors(long object_index);
void render_object_update_change_colors_hook(long object_index, bool force);
void render_visibility_add_first_person_object_to_items_hook(long output_user_index, long object_index, bool a3, bool a4);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern bool g_prt_disabled; // 0x124083AC
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace RenderObject
	{
		void ApplyAll() // 0x108DE300
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@RenderObject@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x678B9E, render_object_mesh_part_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x679136, render_object_mesh_part_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x6791D6, render_object_mesh_part_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x678643, render_object_mesh_part_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x6784C5, render_object_mesh_part_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x679B03, render_object_add_mesh_parts_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x679CEF, render_object_add_mesh_parts_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7BEEEE, object_lighting_geometry_sample_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x645160, render_object_update_change_colors_hook).Apply();
			Hook(0x652C90, render_visibility_add_first_person_object_to_items_hook).Apply();
		}
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0s_compression_info@@QAE@ABU0@@Z"); no body to assert in
_inline s_compression_info::s_compression_info(s_compression_info const &__that) = default; // 0x108DDBA0

namespace Patches
{
	namespace RenderObject
	{
		bool GetPRTDisabled() // 0x108DEC70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPRTDisabled@RenderObject@Patches@@YA_NXZ");
			// procedure flags: nofpo

			return g_prt_disabled;
		}
	}
}

/* ---------- private code */

void render_object_set_shield_impact(long element_index, void *definition) // 0x108E06E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_object_set_shield_impact@@YAXJPAX@Z");
	// `anonymous-namespace'::render_object_set_shield_impact
	// void *definition;

	render_object_globals_get()->parts[element_index].shield_definition = definition;
}

bool object_should_render(long object_index) // 0x108DF6D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_should_render@@YA_NJ@Z");
	// `anonymous-namespace'::object_should_render
	// long object_index;
	// s_object_data *object;
	// bool is_invisible_material;
	// s_forge_globals_definition *forge_globals;
		// s_multiplayer_object_properties *multiplayer_properties;
		// Forge::ForgeKillVolumeProperties *kill_volume_properties;
		// long player_index;
		// bool show_invisibles;
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *, long *)

	s_object_data *object = object_get(object_index);
	if (!object)
		return false;
	s_forge_globals_definition *forge_globals = forge_globals_get_definition();
	if (forge_globals && (!game_engine_is_sandbox() || game_engine_is_sandbox() && Utils::Singleton<Modules::ModuleDebug>::Instance().VarHideForgeObjects->ValueInt == 1))
	{
		if (object->definition_index == forge_globals->garbage_volume_object.index || object->definition_index == forge_globals->prematch_camera_object.index)
			return false;
		if (object->definition_index == forge_globals->kill_volume_object.index)
		{
			s_multiplayer_object_properties *multiplayer_properties = object_get_multiplayer(object_index);
			Forge::ForgeKillVolumeProperties *kill_volume_properties = (Forge::ForgeKillVolumeProperties *)&multiplayer_properties->teleporter_channel;
			return kill_volume_properties->Flags & Forge::ForgeKillVolumeProperties::eKillVolumeFlags_AlwaysVisible;
		}
	}
	bool is_invisible_material = Forge::Reforge::GetRenderMaterialOverride(object_index, nullptr) == 0x79;
	if (is_invisible_material)
	{
		bool show_invisibles = Utils::Singleton<Modules::ModuleForge>::Instance().VarShowInvisiblesClient->ValueInt != 0;
		long player_index = ((long (*)(long))0x589C30)(0);
		return ((bool (*)(long, long *, long *))0x59A6F0)(player_index, nullptr, nullptr) || show_invisibles;
	}
	return true;
}

void render_object_add_mesh_parts_hook(s_render_object *render_object, s_visible_object *render_info, long object_entry_point_flags, bool a4, bool has_shield_impact, bool isFpShit, bool camo) // 0x108DF930
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_object_add_mesh_parts_hook@@YAXPAUs_render_object@@PAUs_visible_object@@J_N222@Z");
	// `anonymous-namespace'::render_object_add_mesh_parts_hook
	// long object_entry_point_flags;
	// bool a4;
	// bool has_shield_impact;
	// bool isFpShit;
	// bool camo;
	// bool uses_fixed_oreder_transparency;
	// s_geometry_material *materials;
	// s_object_data *object;
	// bool ridiculous_transparency_sort_bias_bit;
	// s_render_model *render_model;
		// __int32 region_index;
			// short sort_index;
			// unsigned char mesh_index;
			// s_mesh *mesh;
				// __int32 part_index;
					// long reforge_material_index;
					// bool uses_z_pre_pass;
					// bool is_decal;
					// bool unknown_transparency_flag;
					// long element_index;
					// s_part *part;
					// bool uses_alpha_blending;
					// c_render_method *render_method;
					// long entry_point_flags;
					// long render_method_index;
					// short material_index;
						// real_point3d sorting_position;
							// void *callback;
							// unsigned char sorting_layer;
							// bool uses_distortion;
							// void *shield_impact;
	// function call : void *(*const)(unsigned long, long)
	// function call : bool (*const)(long)
	// function call : bool (*const)(long)
	// function call : long (*const)(s_render_object *, s_render_object_info *, unsigned long *, short, short, short, short, __int32)
	// function call : long (*const)(void *, void *, long)
	// function call : bool (*const)(long)
	// function call : void (*const)(s_render_geometry *, s_mesh *, s_part *, long, long, void *, __int32, real_point3d *, char, long, long, void *)
	// function call : bool (*const)(long)
	// function call : void (*const)(s_render_geometry *, s_mesh *, s_part *, long, long, void *, __int32, real_point3d *, char, long, long, void *)
	// function call : void (*const)(bool)
	// function call : void (*const)(bool)
	// function call : void (*const)(s_render_geometry *, s_mesh *, s_part *, long, long, void *, __int32, real_point3d *, char, long, long, void *)
	// function call : s_shield_parameters *(*const)(s_object_data *, bool)
	// function call : void (*const)()

	bool uses_fixed_oreder_transparency = (object_entry_point_flags >> 6) & 1;
	s_render_model *render_model = (s_render_model *)tag_get('mode', render_info->info.render_model_index);
	bool ridiculous_transparency_sort_bias_bit = false;
	s_geometry_material *materials = (s_geometry_material *)render_model->materials.address;
	if (render_model->materials.count <= 0 || !render_info->info.region_count)
		return;
	s_object_data *object = object_get(render_info->object_index);
	if (!object)
		return;
	if (!object_should_render(render_info->object_index))
		return;
	for (__int32 region_index = 0; region_index < render_info->info.region_count; region_index++)
	{
		unsigned char mesh_index = render_info->info.region_mesh_indices[region_index];
		if (mesh_index == 0xFF)
			continue;
		s_mesh *mesh = &render_model->render_geometry.meshes[mesh_index];
		short sort_index = render_info->info.region_transparent_sort_indices[region_index];
		for (__int32 part_index = 0; part_index < mesh->parts.count; part_index++)
		{
			s_part *part = &mesh->parts[part_index];
			short material_index = part->material_index;
			long reforge_material_index = Forge::Reforge::GetRenderMaterialOverride(render_info->object_index, nullptr);
			if (reforge_material_index != -1)
				material_index = reforge_material_index;
			if (material_index < 0 || material_index >= render_model->materials.count)
				continue;
			if (part->type == (e_part_type)5 || part->type == (e_part_type)6)
				continue;
			long render_method_index = materials[material_index].render_method.index;
			if (render_method_index == -1)
				continue;
			c_render_method *render_method = c_render_method::get(render_method_index);
			if (!render_method)
				continue;
			if (((bool *)0x1699294)[static_cast<char>(object->object_identifier.type)])
				object_entry_point_flags |= 0x10;
			*(long *)0x524B6DC |= ((c_flags<enum e_render_method_flags,short> *)((char *)render_method + 0x34))->test((e_render_method_flags)2);
			bool uses_z_pre_pass = ((bool (*const)(long))0xA77D20)(render_method_index);
			bool is_decal = ((bool (*const)(long))0xA20D10)(render_method_index);
			bool uses_alpha_blending = ((c_tag_block<s_render_method_postprocess_definition> *)((char *)render_method + 0x28))->operator->()->alpha_blend_mode != 0;
			bool unknown_transparency_flag = uses_alpha_blending && !is_decal;
			long entry_point_flags = object_entry_point_flags;
			if (unknown_transparency_flag)
				entry_point_flags = 4;
			if (uses_z_pre_pass)
				entry_point_flags = 0x800;
			if (is_decal)
				entry_point_flags = object_entry_point_flags & ~1 | 0x20;
			long element_index = ((long (*const)(s_render_object *, s_render_object_info *, unsigned long *, short, short, short, short, __int32))0xA77AC0)(render_object, &render_info->info, render_info->subpart_visibility, mesh_index, part_index, region_index, material_index, entry_point_flags);
			if (uses_z_pre_pass)
			{
				if (mesh->vertex_type == (e_vertex_type)2 || mesh->vertex_type == (e_vertex_type)1 || mesh->vertex_type == (e_vertex_type)22)
					((long (*const)(void *, void *, long))0xA7AC90)((void *)0xA791A0, render_object, element_index);
				unknown_transparency_flag = false;
			}
			if (camo && ((bool (*const)(long))0xA20D40)(render_method_index))
			{
				real_point3d sorting_position = global_origin3d;
				if (part->transparent_sorting_index != -1 && !mesh->flags.test((e_mesh_flags)1))
					sorting_position = render_model->render_geometry.sorting[part->transparent_sorting_index].position;
				((void (*const)(s_render_geometry *, s_mesh *, s_part *, long, long, void *, __int32, real_point3d *, char, long, long, void *))0xA77B70)(&render_model->render_geometry, mesh, part, region_index, render_info->info.skinning_memory_designator, render_object, element_index, &sorting_position, uses_fixed_oreder_transparency, static_cast<char>(*(c_enum<enum e_sorting_layer,char> *)((char *)render_method + 0x36)), sort_index, (void *)0xA78480);
				ridiculous_transparency_sort_bias_bit |= sort_index != -1;
			}
			if (a4 && (object_entry_point_flags & 1) && (unknown_transparency_flag || has_shield_impact))
			{
				real_point3d sorting_position = global_origin3d;
				if (part->transparent_sorting_index != -1 && !mesh->flags.test((e_mesh_flags)1))
					sorting_position = render_model->render_geometry.sorting[part->transparent_sorting_index].position;
				if (unknown_transparency_flag)
				{
					unsigned char sorting_layer = *(unsigned char *)offset_pointer(render_method, 0x36);
					bool uses_distortion = ((bool (*const)(long))0xA20D40)(render_method_index);
					void *callback = (void *)0xA790E0;
					if (render_info->flags & 0x10)
						callback = (void *)0xA79160;
					((void (*const)(s_render_geometry *, s_mesh *, s_part *, long, long, void *, __int32, real_point3d *, char, long, long, void *))0xA77B70)(&render_model->render_geometry, mesh, part, region_index, render_info->info.skinning_memory_designator, render_object, element_index, &sorting_position, uses_fixed_oreder_transparency, sorting_layer, sort_index, callback);
					if (uses_distortion)
					{
						((void (*const)(bool))0xA2A300)(true);
						((void (*const)(bool))0xA2A320)(true);
					}
					ridiculous_transparency_sort_bias_bit |= sort_index != -1;
				}
				if (has_shield_impact)
				{
					((void (*const)(s_render_geometry *, s_mesh *, s_part *, long, long, void *, __int32, real_point3d *, char, long, long, void *))0xA77B70)(&render_model->render_geometry, mesh, part, region_index, render_info->info.skinning_memory_designator, render_info, element_index, &sorting_position, 0, 3, sort_index, (void *)0xA78F50);
					ridiculous_transparency_sort_bias_bit |= sort_index != -1;
					void *shield_impact = nullptr;
					if (has_shield_impact)
						shield_impact = ((s_shield_parameters *(*const)(s_object_data *, bool))0xA78030)(object, isFpShit);
					render_object_set_shield_impact(element_index, shield_impact);
				}
			}
		}
	}
	if (ridiculous_transparency_sort_bias_bit)
		((void (*const)())0xA73620)();
}

void render_reforge_object_mesh_part(s_render_object_mesh_part *element, long entry_point, long entry_point_flags, bool a4, long material_index, ::Forge::Reforge::SRenderMaterialParameters const &parameters) // 0x108E0D80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_reforge_object_mesh_part@@YAXPAUs_render_object_mesh_part@@JJ_NJABUSRenderMaterialParameters@Reforge@Forge@@@Z");
	// `anonymous-namespace'::render_reforge_object_mesh_part
	// long entry_point_flags;
	// bool a4;
	// long material_index;
	// Forge::Reforge::SRenderMaterialParameters const &parameters;
	// long old_material_index;
	// s_compression_info custom_compression_info;
	// s_part *part;
	// void *old_compression_info_adress;
	// s_mesh *mesh;
	// s_render_model *render_model;
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(s_render_object_mesh_part *, long, long, bool)

	s_render_model *render_model = (s_render_model *)tag_get('mode', element->info->info.render_model_index);
	s_mesh *mesh = &render_model->render_geometry.meshes[element->mesh_index];
	s_part *part = &mesh->parts[element->part_index];
	s_compression_info custom_compression_info(render_model->render_geometry.compression[0]);
	if (parameters.customTextureMode)
	{
		custom_compression_info.u = { custom_compression_info.u.lower * parameters.textureScale + parameters.textureOffsetU, custom_compression_info.u.upper * parameters.textureScale + parameters.textureOffsetU };
		custom_compression_info.v = { custom_compression_info.v.lower * parameters.textureScale + parameters.textureOffsetV, custom_compression_info.v.upper * parameters.textureScale + parameters.textureOffsetV };
	}
	long old_material_index = part->material_index;
	void *old_compression_info_adress = render_model->render_geometry.compression.address;
	render_model->render_geometry.compression.address = &custom_compression_info;
	part->material_index = material_index;
	((void (*)(s_render_object_mesh_part *, long, long, bool))0xA78940)(element, entry_point, entry_point_flags, a4);
	render_model->render_geometry.compression.address = old_compression_info_adress;
	part->material_index = old_material_index;
}

long object_get_prt_disabled(long object_index) // 0x108DF440
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_get_prt_disabled@@YAJJ@Z");
	// `anonymous-namespace'::object_get_prt_disabled
	// static ...; // 0x108DF520
	// static ...; // 0x108DF514
	// static ...; // 0x108DF50C
	// long object_index;
	// float const k_spartan_scale_threshold;
	// s_object_data *object;
		// c_enum<enum e_object_type,char> object_type;
	// function call : long (*const)(long)

	float const k_spartan_scale_threshold = 1.5f;
	object_index = ((long (*)(long))0xB2EAB0)(object_index);
	s_object_data *object = object_get(object_index);
	if (object)
	{
		c_enum<e_object_type, char> object_type = object->object_identifier.type;
		if (object_type == _object_type_biped && object->scale > k_spartan_scale_threshold)
			return 1;
	}
	return 0;
}

void render_object_mesh_part_hook(s_render_object_mesh_part *element, long entry_point, long entry_point_flags, bool a4) // 0x108E0540
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_object_mesh_part_hook@@YAXPAUs_render_object_mesh_part@@JJ_N@Z");
	// `anonymous-namespace'::render_object_mesh_part_hook
	// s_render_object_mesh_part *element;
	// long entry_point;
	// long entry_point_flags;
	// bool a4;
	// short reforge_material_index;
	// Forge::Reforge::SRenderMaterialParameters reforgeParameters;
	// function call : void (*const)(s_render_object_mesh_part *, long, long, bool)

	#line 519 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\RenderObjectPatches.cpp"
		assert(element->info);
		#line 532 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\RenderObjectPatches.cpp"

	Forge::Reforge::SRenderMaterialParameters reforgeParameters;
	short reforge_material_index = Forge::Reforge::GetRenderMaterialOverride(element->info->object_index, &reforgeParameters);
	if (reforge_material_index != -1)
	{
		render_reforge_object_mesh_part(element, entry_point, entry_point_flags, a4, reforge_material_index, reforgeParameters);
	}
	else
	{
		g_prt_disabled = object_get_prt_disabled(element->info->object_index) ? true : false;
		((void (__cdecl *)(s_render_object_mesh_part *, long, long, bool))0xA78940)(element, entry_point, entry_point_flags, a4);
		g_prt_disabled = false;
	}
}

bool object_sh_lightmap_sampling_disabled(long object_index) // 0x108DF640
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_sh_lightmap_sampling_disabled@@YA_NJ@Z");
	// `anonymous-namespace'::object_sh_lightmap_sampling_disabled
	// long object_index;

	return Forge::Reforge::IsReforgeObject(object_index) || Forge::ObjectIsForgeScenery(object_index);
}

long object_lighting_geometry_sample_hook(real_point3d *origin, real_vector3d *direction, __int32 a3, long object_index, char a5, char a6, s_geometry_sample *sample) // 0x108DF570
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_lighting_geometry_sample_hook@@YAJPAUreal_point3d@@PAUreal_vector3d@@HJDDPAUs_geometry_sample@@@Z");
	// `anonymous-namespace'::object_lighting_geometry_sample_hook
	// s_geometry_sample *sample;
	// static __int32 (*`object_lighting_geometry_sample_hook'::`2'::object_sh_lighting)(real_point3d *, real_vector3d *, __int32, long, char, char, void *); // 0x11352E8C
	// function call : __int32 (*)(real_point3d *, real_vector3d *, __int32, long, char, char, void *)

	if (object_sh_lightmap_sampling_disabled(object_index))
	{
		memcpy(sample, (void const *)0x18F3000, 0x1F8);
		sample->is_valid = false;
		return 1;
	}

	static long (*object_sh_lighting)(real_point3d *, real_vector3d *, __int32, long, char, char, s_geometry_sample *) = (long (*)(real_point3d *, real_vector3d *, __int32, long, char, char, s_geometry_sample *))0x00752B10;
	return object_sh_lighting(origin, direction, a3, object_index, a5, a6, sample);
}

static s_game_globals *try_and_get_game_globals() // 0x108E1E10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?try_and_get_game_globals@@YAPAUs_game_globals@@XZ");
	// `anonymous-namespace'::try_and_get_game_globals
	// procedure flags: nofpo
	// function call : long (*const)(unsigned long)
	// function call : void *(*const)(unsigned long, long)

	return (s_game_globals *)tag_get(0x6D617467, tag_get_first_in_group(0x6D617467));
}

static real_rgb_color *network_get_team_color(real_rgb_color *color, long team) // 0x108DF2B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?network_get_team_color@@YAPAUreal_rgb_color@@PAU1@J@Z");
	// `anonymous-namespace'::network_get_team_color
	// long team;
	// s_game_globals *matg;
		// s_multiplayer_globals_definition *mulg;
	// function call : void *(*const)(unsigned long, long)

	*color = **reinterpret_cast<real_rgb_color **>(0x189CDBC);
	s_game_globals *matg = try_and_get_game_globals();
	if (matg)
	{
		s_multiplayer_globals_definition *mulg = (s_multiplayer_globals_definition *)tag_get('mulg', matg->MultiplayerGlobals.index);
		if (mulg && team >= 0 && team < mulg->universal->team_colors.count)
		{
			*color = mulg->universal->team_colors[team].color;
		}
	}

	return color;
}

bool object_always_updates_change_colors(long object_index) // 0x108DF3C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_always_updates_change_colors@@YA_NJ@Z");
	// `anonymous-namespace'::object_always_updates_change_colors
	// long object_index;
	// s_multiplayer_object_properties *multiplayer;
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)

	s_multiplayer_object_properties *multiplayer = object_get_multiplayer(object_index);

	if (multiplayer)
	{
		return true;
	}

	return false;
}

void render_object_update_change_colors_hook(long object_index, bool force) // 0x108E0730
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_object_update_change_colors_hook@@YAXJ_N@Z");
	// `anonymous-namespace'::render_object_update_change_colors_hook
	// static ...; // 0x108E0C20
	// static ...; // 0x108E0C18
	// long object_index;
	// bool force;
	// s_object_data *object;
	// bool (*const restricted_region_locked_for_current_thread)(long);
	// void (*const object_queue_render_thread_message)(long, long, long);
	// void *(*const object_get_render_data)(long);
	// bool (*const object_get_change_color)(long, long, real_rgb_color *);
	// s_object_definition *object_def;
	// long cached_state_index;
		// c_data_array<s_object_cached_render_state_datum> *cached_states;
		// s_object_cached_render_state_datum *cached_state;
			// __int32 i;
				// real_rgb_color color;
					// s_multiplayer_object_properties *multiplayer;
					// long target_object_index;
						// bool isReforgeObject;
							// Forge::ReforgeObjectProperties *const reforge;
							// unsigned char *custom_change_colors;
	// function call : bool (*const)(long)
	// function call : void (*const)(long, long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(long)
	// function call : bool (*const)(long, long, real_rgb_color *)
	// function call : long (*const)(long)
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : unsigned long (*const)(real_rgb_color *)

	bool (*const restricted_region_locked_for_current_thread)(long) = (bool (*)(long))0x5A03E0;
	void (*const object_queue_render_thread_message)(long, long, long) = (void (*)(long, long, long))0xB31B80;
	void *(*const object_get_render_data)(long) = (void *(*)(long))0xB2E800;
	bool (*const object_get_change_color)(long, long, real_rgb_color *) = (bool (*)(long, long, real_rgb_color *))0xB2DE50;
	if (!restricted_region_locked_for_current_thread(2))
	{
		object_queue_render_thread_message(object_index, 2, force);
		return;
	}
	s_object_data *object = object_get(object_index);
	if (!object)
		return;
	s_object_definition *object_def = (s_object_definition *)tag_get('obje', object->definition_index);
	long cached_state_index = *(long *)object_get_render_data(object_index);
	if (cached_state_index != -1 && (force || (object_def->runtime_flags & 1) || object_always_updates_change_colors(object_index)))
	{
		c_data_array<s_object_cached_render_state_datum> *cached_states = ((tls_data *)tls_get(0))->cached_object_render_states;
		s_object_cached_render_state_datum *cached_state = cached_states->try_and_get(cached_state_index);
		cached_state->shader_extern_info.change_colors_count = 0;
		for (__int32 i = 0; i < 5; i++)
		{
			real_rgb_color color;
			if (object_get_change_color(object_index, i + 1, &color))
			{
				long target_object_index = ((long (*const)(long))0xB2EAB0)(object_index);
				s_multiplayer_object_properties *multiplayer = object_get_multiplayer(target_object_index);
				if (!multiplayer)
					multiplayer = object_get_multiplayer(target_object_index);
				if (multiplayer)
				{
					bool isReforgeObject = Forge::Reforge::IsReforgeObject(object_index);
					if (isReforgeObject)
					{
						Forge::ReforgeObjectProperties *const reforge = (Forge::ReforgeObjectProperties *)&multiplayer->boundry_width;
						color.red = reforge->ColorR / 255.0f;
						color.green = reforge->ColorG / 255.0f;
						color.blue = reforge->ColorB / 255.0f;
					}
					else if (multiplayer->multiplayer_object_type == (e_multiplayer_object_type)12 || Forge::Reforge::IsPrematchCameraObject(object_index))
					{
						if (multiplayer->team_designator >= (e_multiplayer_team_designator)0 && multiplayer->team_designator < (e_multiplayer_team_designator)8)
							network_get_team_color(&color, (short)multiplayer->team_designator);
					}
					else if (!((1 << (char)object->object_identifier.type) & 0xD))
					{
						unsigned char *custom_change_colors = (unsigned char *)&multiplayer->boundry_width;
						if (custom_change_colors[0] || custom_change_colors[1] || custom_change_colors[2])
						{
							color.red = custom_change_colors[0] / 255.0f;
							color.green = custom_change_colors[1] / 255.0f;
							color.blue = custom_change_colors[2] / 255.0f;
						}
					}
				}
				cached_state->shader_extern_info.change_colors[i] = ((unsigned long (*const)(real_rgb_color *))0x521D90)(&color);
				cached_state->shader_extern_info.change_colors_count++;
			}
		}
	}
}

void render_visibility_add_first_person_object_to_items_hook(long output_user_index, long object_index, bool a3, bool a4) // 0x108E1010
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_visibility_add_first_person_object_to_items_hook@@YAXJJ_N0@Z");
	// `anonymous-namespace'::render_visibility_add_first_person_object_to_items_hook
	// static ...; // 0x108E1A3C
	// long output_user_index;
	// long object_index;
	// bool a3;
	// bool a4;
	// bool (*const render_object_first_person_globals_valid)();
	// void *(*const c_render_frame_memory__get)(long);
	// long (*const render_model_get_skinning_matrix_count)(long, long, unsigned char const *);
	// long old_objects_count;
	// long old_hierarchy_count;
	// long new_hierarchy_index;
	// long (*const c_object_renderer_submit_object_attachments)(long, long);
	// s_render_lighting *(*const object_update_cached_render_lighting)(long, float);
	// void (*const render_object_get_object_values)(long, s_render_object_info *);
	// long (*const c_render_frame_memory__allocate)(long, __int32, long);
	// void (*const render_model_build_skinning)(long, long, real_matrix4x3 *, unsigned char *, long, char, __int32, void *);
	// s_render_lighting *lighting;
	// void (*const object_get_region_information)(long, long *, char **, char **, s_object_region_information **);
	// long (*const render_model_compute_skinning_size_in_bytes)(long);
	// bool added_successfully;
	// void (*const object_visibility_new)(s_visible_object *);
	// s_visible_items &visible_items;
		// s_visible_object_hierarchy &new_hierarchy;
		// __int32 count;
			// __int32 i;
				// s_object_data *object;
				// long new_render_visibility_index;
				// long unit_region_count;
				// s_render_first_person_model &first_person_model;
				// s_object_definition *object_def;
				// char *unit_region_permutation_indices;
				// bool v29;
				// s_render_model *render_model;
				// s_visible_object &new_render_visibility;
				// long skinning_size;
					// __int32 j;
						// s_render_model_region &region;
					// s_model_definition *tp_model;
					// s_object_data *tp_object;
					// s_render_model *tp_render_model;
					// s_object_definition *tp_object_def;
						// __int32 j;
							// s_render_model_permutation &permutation;
							// char permutation_index;
							// s_render_model_region &region;
								// __int32 k;
									// s_render_model_region &target_region;
										// __int32 l;
											// s_render_model_permutation &target_permutation;
					// void *skinning;
	// function call : bool (*const)()
	// function call : s_render_lighting *(*const)(long, float)
	// function call : void *(*const)(unsigned long, long)
	// function call : long (*const)(long, long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(s_visible_object *)
	// function call : void (*const)(long, long *, char **, char **, s_object_region_information **)
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : long (*const)(long, long, unsigned char const *)
	// function call : long (*const)(long)
	// function call : long (*const)(long, __int32, long)
	// function call : void *(*const)(long)
	// function call : void (*const)(long, long, real_matrix4x3 *, unsigned char *, long, char, __int32, void *)
	// function call : s_shader_extern_info *(*const)(long)
	// function call : void (*const)(long, s_render_object_info *)

	bool (*const render_object_first_person_globals_valid)() = reinterpret_cast<bool (*)()>(0xA44BE0);
	long (*const c_object_renderer_submit_object_attachments)(long, long) = reinterpret_cast<long (*)(long, long)>(0xA79470);
	void (*const object_visibility_new)(s_visible_object *) = reinterpret_cast<void (*)(s_visible_object *)>(0x973C80);
	long (*const render_model_get_skinning_matrix_count)(long, long, unsigned char const *) = reinterpret_cast<long (*)(long, long, unsigned char const *)>(0xA1F5D0);
	long (*const render_model_compute_skinning_size_in_bytes)(long) = reinterpret_cast<long (*)(long)>(0xA1F630);
	void (*const render_model_build_skinning)(long, long, real_matrix4x3 *, unsigned char *, long, char, __int32, void *) = reinterpret_cast<void (*)(long, long, real_matrix4x3 *, unsigned char *, long, char, __int32, void *)>(0xA1F120);
	long (*const c_render_frame_memory__allocate)(long, __int32, long) = reinterpret_cast<long (*)(long, __int32, long)>(0xA6D940);
	void * (*const c_render_frame_memory__get)(long) = reinterpret_cast<void * (*)(long)>(0xA6DAA0);
	s_render_lighting * (*const object_update_cached_render_lighting)(long, float) = reinterpret_cast<s_render_lighting * (*)(long, float)>(0xA445A0);
	void (*const render_object_get_object_values)(long, s_render_object_info *) = reinterpret_cast<void (*)(long, s_render_object_info *)>(0xA190A0);
	void (*const object_get_region_information)(long, long *, char **, char **, s_object_region_information **) = reinterpret_cast<void (*)(long, long *, char **, char **, s_object_region_information **)>(0xB2E770);
	if (!render_object_first_person_globals_valid())
		return;
	s_render_lighting *lighting = object_update_cached_render_lighting(object_index, 10000.0f);
	bool added_successfully = true;
	s_visible_items &visible_items = c_visible_items::get_global_items();
	long old_hierarchy_count = visible_items.object_hierarchies.count;
	long old_objects_count = visible_items.objects.count;
	long new_hierarchy_index = visible_items.object_hierarchies.add();
	if (new_hierarchy_index == -1)
	{
		added_successfully = false;
	}
	else
	{
		s_visible_object_hierarchy &new_hierarchy = visible_items.object_hierarchies.elements[new_hierarchy_index];
		new_hierarchy.group_index = -1;
		new_hierarchy.first_index = 0;
		new_hierarchy.flags |= 8;
		new_hierarchy.flags |= 4;
		if (a3)
			new_hierarchy.flags |= 1;
		else
			new_hierarchy.flags &= ~1;
		if (a4)
			new_hierarchy.flags |= 2;
		else
			new_hierarchy.flags &= ~2;
		__int32 count = 0;
		for (__int32 i = 0; i < reinterpret_cast<s_render_object_first_person_globals *>(0x50FB668)->first_person_model_count; i++)
		{
			s_render_first_person_model &first_person_model = reinterpret_cast<s_render_object_first_person_globals *>(0x50FB668)->first_person_models[i];
			s_render_model *render_model = (s_render_model *)tag_get('mode', first_person_model.render_model_index);
			if (i < reinterpret_cast<s_render_object_first_person_globals *>(0x50FB668)->first_person_model_count - 1)
				c_object_renderer_submit_object_attachments(output_user_index, first_person_model.object_index);
			if (!render_model->render_geometry.meshes.count)
				continue;
			long new_render_visibility_index = visible_items.objects.add();
			s_visible_object &new_render_visibility = visible_items.objects.elements[new_render_visibility_index];
			s_object_data *object = object_try_and_get_and_verify_type(first_person_model.object_index, -1);
			s_object_definition *object_def = (s_object_definition *)tag_get('obje', object->definition_index);
			bool v29 = false;
			if (object_def->model.index != -1)
				v29 = (((s_model_definition *)tag_get('hlmt', object_def->model.index))->flags & 2) != 0;
			object_visibility_new(&new_render_visibility);
			new_render_visibility.object_index = first_person_model.object_index;
			new_render_visibility.info.render_model_index = first_person_model.render_model_index;
			new_render_visibility.info.region_count = render_model->regions.count;
			new_render_visibility.flags |= 1;
			if (object->first_widget_index == -1)
				new_render_visibility.flags &= ~2;
			else
				new_render_visibility.flags |= 2;
			if (v29)
				new_render_visibility.flags |= 4;
			else
				new_render_visibility.flags &= ~4;
			new_render_visibility.flags |= 8;
			if (first_person_model.flags & 1)
				new_render_visibility.flags |= 0x10;
			else
				new_render_visibility.flags &= ~0x10;
			for (__int32 j = 0; j < render_model->regions.count; j++)
			{
				s_render_model_region &region = render_model->regions[j];
				new_render_visibility.info.region_mesh_indices[j] = region.permutations->mesh_index;
			}
			long unit_region_count = 0;
			char *unit_region_permutation_indices;
			object_get_region_information(first_person_model.object_index, &unit_region_count, &unit_region_permutation_indices, nullptr, nullptr);
			if (unit_region_count > 0)
			{
				s_object_data *tp_object = object_get(first_person_model.object_index);
				s_object_definition *tp_object_def = (s_object_definition *)tag_get('obje', tp_object->definition_index);
				s_model_definition *tp_model = (s_model_definition *)tag_get('hlmt', tp_object_def->model.index);
				s_render_model *tp_render_model = (s_render_model *)tag_get('mode', tp_model->render_model.index);
				for (__int32 j = 0; j < tp_render_model->regions.count; j++)
				{
					s_render_model_region &region = tp_render_model->regions[j];
					char permutation_index = unit_region_permutation_indices[j];
					if (permutation_index == -1)
						continue;
					s_render_model_permutation &permutation = region.permutations[permutation_index];
					for (__int32 k = 0; k < render_model->regions.count; k++)
					{
						s_render_model_region &target_region = render_model->regions[k];
						if (region.name != target_region.name)
							continue;
						for (__int32 l = 0; l < target_region.permutations.count; l++)
						{
							s_render_model_permutation &target_permutation = target_region.permutations[l];
							if (permutation.name != target_permutation.name)
								continue;
							new_render_visibility.info.region_mesh_indices[k] = target_permutation.mesh_index;
							break;
						}
					}
				}
			}
			new_render_visibility.info.skinning_matrix_count = render_model_get_skinning_matrix_count(first_person_model.render_model_index, new_render_visibility.info.lod_type, new_render_visibility.info.region_mesh_indices);
			long skinning_size = render_model_compute_skinning_size_in_bytes(new_render_visibility.info.skinning_matrix_count);
			new_render_visibility.info.skinning_memory_designator = c_render_frame_memory__allocate(0, 1, skinning_size);
			if (new_render_visibility.info.skinning_memory_designator == -1)
			{
				added_successfully = false;
			}
			else
			{
				void *skinning = c_render_frame_memory__get(new_render_visibility.info.skinning_memory_designator);
				render_model_build_skinning(first_person_model.object_index, first_person_model.render_model_index, first_person_model.node_matrices, new_render_visibility.info.region_mesh_indices, new_render_visibility.info.lod_type, 1, new_render_visibility.info.skinning_matrix_count, skinning);
			}
			new_render_visibility.info.render_info = ((s_shader_extern_info *(*const)(long))0xA44D30)(first_person_model.object_index);
			if (new_render_visibility.info.render_info)
				memcpy((char *)new_render_visibility.info.render_info + 0x10, lighting, 0x218);
			if (new_render_visibility.info.render_info)
				render_object_get_object_values(new_render_visibility.object_index, &new_render_visibility.info);
			count++;
		}
		new_hierarchy.first_index = c_visible_items::get_current_markers().objects_marker;
		new_hierarchy.count = count;
		new_hierarchy.lod_alphas.lod_fade = 0xFF;
		new_hierarchy.lod_alphas.field_1 = 0xFF;
		new_hierarchy.lod_alphas.shadow_alpha = 0xFF;
	}
	if (!added_successfully)
	{
		visible_items.object_hierarchies.count = old_hierarchy_count;
		visible_items.objects.count = old_objects_count;
	}
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_enum<enum e_alpha_blend_mode,int>::operator!=(__int32 const &) const;
template bool c_enum<enum e_alpha_blend_mode,int>::operator==(__int32 const &) const;
template bool c_enum<enum e_multiplayer_object_type,char>::operator==(e_multiplayer_object_type const &) const;
template bool c_enum<enum e_part_type,char>::operator==(e_part_type const &) const;
template bool c_enum<enum e_vertex_type,char>::operator==(e_vertex_type const &) const;
template bool c_flags<enum e_mesh_flags,unsigned char>::test(e_mesh_flags) const;
template bool c_flags<enum e_multiplayer_team_designator,short>::operator<(e_multiplayer_team_designator const &) const;
template bool c_flags<enum e_multiplayer_team_designator,short>::operator>=(e_multiplayer_team_designator const &) const;
template bool c_flags<enum e_render_method_flags,short>::test(e_render_method_flags) const;
template bool c_tag_block<s_compression_info>::try_get_element(__int32, s_compression_info **) const;
template bool c_tag_block<s_multiplayer_team_color>::try_get_element(__int32, s_multiplayer_team_color **) const;
template bool c_tag_block<s_part>::try_get_element(__int32, s_part **) const;
template bool c_tag_block<s_render_method_postprocess_definition>::try_get_element(__int32, s_render_method_postprocess_definition **) const;
template bool c_tag_block<s_render_model_permutation>::try_get_element(__int32, s_render_model_permutation **) const;
template bool c_tag_block<s_render_model_region>::try_get_element(__int32, s_render_model_region **) const;
template bool c_tag_block<s_sorting_position>::try_get_element(__int32, s_sorting_position **) const;
template c_enum<enum e_object_definition_runtime_flags,long> c_enum<enum e_object_definition_runtime_flags,long>::operator&(__int32 const) const;
template c_enum<enum e_object_definition_runtime_flags,long>::c_enum(long const &);
template c_enum<enum e_object_definition_runtime_flags,long>::operator bool() const;
template c_enum<enum e_object_type,char>::c_enum(c_enum<enum e_object_type,char> const &);
template c_enum<enum e_object_type,char>::c_enum(char const &);
template c_enum<enum e_sorting_layer,char>::operator char() const;
template c_flags<enum e_compression_info_flags,unsigned short>::c_flags(c_flags<enum e_compression_info_flags,unsigned short> const &);
template c_flags<enum e_compression_info_flags,unsigned short>::c_flags(unsigned short const &);
template long s_simple_list<s_visible_object,1792>::add();
template long s_simple_list<s_visible_object_hierarchy,1536>::add();
template s_compression_info & c_tag_block<s_compression_info>::operator[](__int32);
template s_compression_info * c_tag_block<s_compression_info>::get_element(__int32) const;
template s_multiplayer_team_color & c_tag_block<s_multiplayer_team_color>::operator[](__int32);
template s_multiplayer_team_color * c_tag_block<s_multiplayer_team_color>::get_element(__int32) const;
template s_object_cached_render_state_datum * c_data_array<s_object_cached_render_state_datum>::try_and_get(unsigned long);
template s_part & c_tag_block<s_part>::operator[](__int32);
template s_part * c_tag_block<s_part>::get_element(__int32) const;
template s_render_method_postprocess_definition * c_tag_block<s_render_method_postprocess_definition>::get_element(__int32) const;
template s_render_method_postprocess_definition * c_tag_block<s_render_method_postprocess_definition>::operator->();
template s_render_model_permutation & c_tag_block<s_render_model_permutation>::operator[](__int32);
template s_render_model_permutation * c_tag_block<s_render_model_permutation>::get_element(__int32) const;
template s_render_model_permutation * c_tag_block<s_render_model_permutation>::operator->();
template s_render_model_region & c_tag_block<s_render_model_region>::operator[](__int32);
template s_render_model_region * c_tag_block<s_render_model_region>::get_element(__int32) const;
template s_sorting_position & c_tag_block<s_sorting_position>::operator[](__int32);
template s_sorting_position * c_tag_block<s_sorting_position>::get_element(__int32) const;
