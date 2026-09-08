/* ---------- headers */

#include "hades/hades.h"

#include "Blam/bitmaps/bitmap_definition.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/camera/observer.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/geometry/geometry_definitions.hpp"
#include "Blam/geometry/geometry_sampler.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/breakable_surfaces.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_globals.hpp"
#include "Blam/rasterizer/rasterizer_primitives.hpp"
#include "Blam/rasterizer/rasterizer_render_targets.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_shaders.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizer_vertex_types.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/camera_fx_settings.hpp"
#include "Blam/render/cubemap_sample.hpp"
#include "Blam/render/render_globals.hpp"
#include "Blam/render/render_model.hpp"
#include "Blam/render/render_object.hpp"
#include "Blam/render/render_object_globals.hpp"
#include "Blam/render/render_structure.hpp"
#include "Blam/render/screen_postprocess.hpp"
#include "Blam/render/view.hpp"
#include "Blam/render/views/render_camera.hpp"
#include "Blam/render/views/render_first_person_view.hpp"
#include "Blam/render/views/render_lights_view.hpp"
#include "Blam/render/views/render_player_view.hpp"
#include "Blam/render/views/render_texture_camera_view.hpp"
#include "Blam/render/views/render_view.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/shaders/render_method_extern.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/shaders/render_method_template_definitions.hpp"
#include "Blam/shaders/render_methods_definitions.hpp"
#include "Blam/sky_atm/atmosphere.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/structures/structure_bsp_definitions.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "Blam/visibility/visibility.hpp"
#include "Blam/visibility/visibility_items.hpp"
#include "Blam/visibility/visibility_object_render_info.hpp"
#include "Blam/widgets/muffin.hpp"
#include "Blam/widgets/muffin_definitions.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/ForgeVisionRenderer.hpp"
#include "Forge/Geoemetry.hpp"
#include "Modules/ModuleSettings.hpp"
#include "Patch.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/document.h"
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
#include <memory>
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

class c_rasterizer_globals;
class c_rasterizer_index_buffer;
class c_rasterizer_vertex_buffer;
class c_render_method;
class s_tag_block_index;
struct _D3DSURFACE_DESC;
struct c_camera_fx_settings;
struct c_camera_fx_values;
struct c_dynamic_cubemap_sample;
struct c_first_person_view;
struct c_lights_view;
struct c_player_view;
struct c_rasterizer;
struct c_rasterizer_texture_ref;
struct c_render_method_data;
struct c_render_method_template;
struct c_render_surface;
struct c_screen_postprocess;
struct c_surface_group;
struct c_texture_camera_view;
struct c_view;
struct c_visibility_collection;
struct real_matrix4x3;
struct real_plane3d;
struct real_point3d;
struct real_rectangle2d;
struct real_rgb_color;
struct real_vector3d;
struct real_vector4d;
struct s_bitmap_definition;
struct s_breakable_surface_set;
struct s_camera_fx_color_grading_struct;
struct s_cluster_reference;
struct s_compression_info;
struct s_cubemap_reference_point;
struct s_decorator_grid;
struct s_decorator_set;
struct s_destination_info;
struct s_extern_description;
struct s_geometry_material;
struct s_hue_saturation_control;
struct s_lod_alphas;
struct s_mesh;
struct s_muffin;
struct s_muffin_datum;
struct s_muffin_definition;
struct s_object_cached_render_state_datum;
struct s_object_data;
struct s_observer_depth_of_field;
struct s_observer_result;
struct s_part;
struct s_rasterizer_globals;
struct s_render_camera;
struct s_render_cluster_part;
struct s_render_geometry;
struct s_render_instance_part;
struct s_render_lighting;
struct s_render_method_animated_parameter;
struct s_render_method_routing_info;
struct s_render_method_template_pass;
struct s_render_method_template_routing_info;
struct s_render_model;
struct s_render_model_instance_placement;
struct s_render_object;
struct s_render_object_globals;
struct s_render_object_info;
struct s_render_object_mesh_part;
struct s_render_projection;
struct s_render_shield_parts;
struct s_scenario;
struct s_scenario_lightmap_bsp_data;
struct s_scenario_structure_bsp;
struct s_screen_effect_settings;
struct s_screen_effect_shader_sample_result;
struct s_screen_vertex;
struct s_shader_extern_info;
struct s_simple_light;
struct s_sorting_position;
struct s_structure_bsp_cache_file_resources;
struct s_structure_cluster;
struct s_structure_cluster_cubemap_info;
struct s_structure_instanced_geometry_definition;
struct s_structure_instanced_geometry_instance;
struct s_structure_plane;
struct s_structure_surface_plane;
struct s_subpart;
struct s_tag_data;
struct s_unit_data;
struct s_visibility_region;
struct s_visible_cluster;
struct s_visible_instance;
struct s_visible_instance_group;
struct s_visible_items;
struct s_visible_object;
struct s_weighted_atmosphere_parameters;
struct s_wind_definition;
struct s_wind_values;
struct shield_impact_definition;
struct short_rectangle2d;
struct tls_data;
namespace Modules
{
	class ModuleSettings;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace Forge {}
using namespace ::Forge;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Debug {}
	using namespace Patches::Debug;
	namespace RenderObject {}
	using namespace Patches::RenderObject;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

typedef float order_2_sh[9];
typedef float order_1_sh[4];
typedef float order_5_sh[36];
typedef __int32 S32;
typedef unsigned __int32 U32;

/* ---------- prototypes */

extern void render_patches_apply();
extern void render_patches_set_customization_biped(std::vector<int> characterBipeds);
extern void render_patches_tick();

void get_extern_constant_hook(long render_method_extern, real_vector4d *out_constant);
_inline long const render_get_extern_volatility_level_hook(long render_method_extern);
void submit_extern_texture_hook(void *device, long a2, long render_method_extern, long sampler);
void render_method_submit_externs_hook(c_render_method const *render_method, c_enum<enum e_entry_point,long> entry_point, long volatility, bool ignore_real_volatility);
void render_method_submit_single_extern_hook(long render_method_extern, bool a2);
void render_method_submit_set_bsp_call_hook(long lightmap_bsp_data_handle);
float evaluate_function_hook(long rm_index, s_render_method_animated_parameter *function);
void update_constants_hook(long render_method_index, real_vector4d *source, s_destination_info *destination_info, long *destination_count, s_tag_block_index *routing_index, c_tag_block<s_render_method_routing_info> *routing_block, c_tag_block<s_render_method_animated_parameter> *functions_block);
bool z_buffer_fix_enabled();
void rasterizer_get_z_planes_hook(float *near_clip, float *far_clip);
bool depth_stencil_format_is_float(_D3DFORMAT format);
void c_surface__set_depth_stencil(e_surface surface);
void c_surface__set_depth_stencil_surface(IDirect3DSurface9 *surface);
void c_first_person_view__override_projection(c_first_person_view *thisptr, void *unused, bool a2);
s_observer_result *observer_get_camera__call_hook(long output_user_index);
void post_render_player_view_hook();
void render_underwater_fog_hook();
void sub_14E3A00_vision_call_hook(s_render_projection *render_proj, float *proj_matrix, s_render_projection *out_render_proj, float *out_proj_matrix);
void render_mesh_part_default_hook(s_render_geometry *geometry, s_mesh *mesh, s_part *part, e_entry_point entry_point, unsigned long *subpart_visibility, s_geometry_material *materials);
void c_structure_renderer__render_cluster_mesh_part_hook(long cluster_visibility_index, e_entry_point entry_point, long flags);
void c_structure_renderer__render_instance_mesh_part_hook(long render_instance_index, e_entry_point entry_point, long flags);
void c_structure_renderer__submit_cluster_visibility(bool include_transparent);
void c_structure_renderer__submit_instance_visibility(bool include_transparent);
void c_structure_renderer__submit_visibility_hook(bool include_transparent);
void c_structure_renderer__render_decorators_hook();
void c_object_renderer__submit_object_mesh_parts_for_active_camo_hook(s_render_object *render_object, s_visible_object *visible_object, bool a3, __int32 is_first_person);
void c_water_renderer__render_water_part_hook(s_render_geometry *geometry, __int32 mesh_index, __int32 part_index, e_entry_point entry_point, s_geometry_material *materials);
void c_water_renderer__update_water_structure_part_list_hook(long *water_part_indices, long *out_count);
void s_render_shield_parts__render_hook(s_render_shield_parts *thisptr, void *unused, s_visible_object *visible_object, char flags);
void c_object_renderer__render_object_context_instances_hook(s_render_object_mesh_part *render_part, e_entry_point entry_point, unsigned long *subpart_visibility, s_lod_alphas alphas);
void c_object_renderer__render_object_context_mesh_part_hook(s_render_object_mesh_part *mesh_part, e_entry_point entry_point, long mesh_part_mask, bool a4);
void render_mesh_part_no_material(s_render_geometry *geometry, __int32 mesh_index, __int32 part_index);
long c_geometry_sampler__find_render_method_index_from_collision_hook(long structure_bsp_index, long a2, long instance_index, long surface_index);
bool part_is_renderable_hook(s_part const *part, s_geometry_material const *materials);
void muffins_render_opaque(short datum_index, e_entry_point entry_point);
bool mesh_get_data_hook(s_render_geometry *render_geometry, long mesh_index, void const **out_vertex_data, void const **out_index_data, unsigned char *out_vertex_stride, long *out_vertex_count, long *out_index_count);
bool render_method_submit_particle_gpu_emitter_render_hook(long tag_index, c_render_method const *render_method, e_vertex_type vertex_type, e_prt_vertex_type prt_type, e_entry_point entry_point, bool a6);
bool sub_610230__ssao_call_hook();
void c_render_shield__render_object_internal_hook(s_render_object_info *info, s_render_object_mesh_part *data, shield_impact_definition *shield_impact, float recent_shield_damage, float current_shield_damage, float unknown_amount, float overshield_amount, float t);
void c_dynamic_cubemap_sample__search_for_cubemap_sample_in_cluster_hook(c_dynamic_cubemap_sample *thisptr, void *__formal, s_cluster_reference test_location, real_point3d *test_point, float tolerance);
float render_projection_sphere_diameter_in_pixels_hook(s_render_projection const *render_projection, real_point3d const *center, float radius);
void bink_playback_allocate_framebuffers_hook();
void c_player_view__render_hook(c_player_view *view);
void c_player_view__render_lightmap_shadows_hook(c_player_view *_this, void *__savedreg);
void c_texture_camera_view__render_hook(c_texture_camera_view *thisptr);
void c_player_view__render_static_lighting(c_player_view *_this, void *_savedreg);
void c_lightmap_shadows_view__render_shadow_apply_call_hook(void *_this, void *_savedreg, float shadow_alpha, float quality_scale);
void c_lightmap_shadows_view__submit_visibility_and_render_call_hook(void *_this, void *_savedreg, float shadow_alpha, float quality_scale, long object_index, long model_tag_index);
void rasterizer_wait_for_device_query_hook(long index);
void c_rasterizer__draw_primitive_up_hook(e_primitive_type primitive_type, unsigned long primitive_count, void const *vertex_data, unsigned long stride);
void c_rasterizer__end_frame_set_surface_as_texture_call_hook(long sampler, e_surface surface);
void c_rasterizer__end_frame_set_sampler_texture_call_hook(long sampler, c_rasterizer_texture_ref ref);
bool c_rasterizer__initialize_after_device_creation_or_reset_call_hook();

/* ---------- globals */

float c_player_view::render_debug_depth_render_alpha; // 0x11352F68
void (*s_wind_definition::update)(s_wind_definition *, s_wind_values *); // 0x11352F74
s_wind_definition *(*s_wind_definition::get_wind_definition)(real_point3d *); // 0x11352F78
s_decorator_set *(*s_decorator_set::get)(long); // 0x11352F7C
long (*s_decorator_set::get_explicit_shader_index)(s_decorator_set *); // 0x11352F80
unsigned long *c_render_method_data::m_change_colors; // 0x11352F34
void (*c_rasterizer_globals::get_default_texture_rasterizer_texture_ref)(s_rasterizer_globals *, c_rasterizer_texture_ref *, c_enum<enum e_rasterizer_default_bitmap,long>); // 0x11352F3C
long *c_rasterizer::g_color_surfaces; // 0x11352F48
s_muffin_definition *(*s_muffin_definition::get)(long); // 0x11352F6C

/* ---------- private variables */

namespace hades_file_local
{
	extern float &k_camera_field_of_view_default; // 0x11352ED4
	extern s_extern_description const g_new_extern_descriptions[55]; // 0x11195C80
	extern s_wind_values &g_wind_values; // 0x11352EDC
	extern bool &g_invalidate_render_cache; // 0x11352ED8
	extern __int32 *g_bink_frame_width; // 0x11352EE0
	extern __int32 *g_bink_frame_height; // 0x11352EE4
	extern std::vector<int> customization_biped_index_array; // 0x124083B0
	extern float g_lod_distance_scale; // 0x11352EE8
	extern float g_decorator_distance_scale; // 0x11352EEC
	extern bool &render_static_lighting_enabled; // 0x11352EF0
	extern bool &byte_191C922; // 0x11352EF4
	extern float &c_camera_fx_values__g_HDR_target_stops; // 0x11352EF8
	extern c_screen_postprocess::s_settings &c_screen_postprocess__x_settings; // 0x11352EFC
	extern long &c_surface__g_current_splitscreen_res; // 0x11352F00
	extern s_weighted_atmosphere_parameters &g_atmosphere_parameters; // 0x11352F04
	extern float &g_particle_hack_near_fade_scale; // 0x11352F08
	extern long &render_debug_depth_render; // 0x11352F0C
	extern bool &render_dynamic_shadow_enabled; // 0x11352F10
	extern bool &render_water_interaction_enabled; // 0x11352F14
	extern bool &render_water_wireframe_enabled; // 0x11352F18
}
using namespace hades_file_local;
/* ---------- public code */

_extern void _sub_108F1E10();
void render_patches_apply() // 0x108F1E10
{
	mangled_x86(MANGLED_TODO, "?render_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_108F1E10();
}

_extern void _sub_108F5A80(std::vector<int>);
void render_patches_set_customization_biped(std::vector<int> characterBipeds) // 0x108F5A80
{
	mangled_x86(MANGLED_TODO, "?render_patches_set_customization_biped@@YAXV?$vector@HV?$allocator@H@std@@@std@@@Z");
	// std::vector<int> characterBipeds;
	todo("implement");
	_sub_108F5A80(characterBipeds);
}

_extern void _sub_108F5B20();
void render_patches_tick() // 0x108F5B20
{
	mangled_x86(MANGLED_TODO, "?render_patches_tick@@YAXXZ");
	// procedure flags: nofpo
	// Modules::ModuleSettings const &settingsModule;
	todo("implement");
	_sub_108F5B20();
}

/* ---------- private code */

_extern void _sub_108EFA30(long, real_vector4d *);
void get_extern_constant_hook(long render_method_extern, real_vector4d *out_constant) // 0x108EFA30
{
	// `anonymous-namespace'::get_extern_constant_hook
	// real_vector4d *out_constant;
	{
		// float z_near;
		// float z_far;
		// c_view *view;
	}
	{
	}
	{
		// long width;
		// long height;
	}
	// function call : c_view *(*const)()
	// function call : c_view *(*const)()
	// function call : long (*const)(long)
	// function call : long (*const)(long)
	// function call : void (*const)(c_enum<enum e_render_method_extern,long>, real_vector4d *)
	todo("implement");
	_sub_108EFA30(render_method_extern, out_constant);
}

extern long const _sub_108F09F0(long);
_inline long const render_get_extern_volatility_level_hook(long render_method_extern) // 0x108F09F0
{
	// `anonymous-namespace'::render_get_extern_volatility_level_hook
	// long render_method_extern;
	todo("implement");
	long const __result = _sub_108F09F0(render_method_extern);
	return __result;
}

_extern void _sub_108F6D50(void *, long, long, long);
void submit_extern_texture_hook(void *device, long a2, long render_method_extern, long sampler) // 0x108F6D50
{
	// `anonymous-namespace'::submit_extern_texture_hook
	// static ...; // 0x108F7104
	// static ...; // 0x108F70FC
	// void *device;
	// long a2;
	// long render_method_extern;
	// long sampler;
	// bool (*const game_is_ui_shell)();
	{
		// s_rasterizer_globals *rasg;
		// c_rasterizer_texture_ref texture_ref;
	}
	{
		// unsigned __int32 i;
	}
	{
		// s_unit_data *unit_data;
		{
			// s_unit_data *unit;
			// short player_index;
		}
	}
	{
		// long index;
	}
	// function call : void (*)(s_rasterizer_globals *, c_rasterizer_texture_ref *, c_enum<enum e_rasterizer_default_bitmap,long>)
	// function call : void (*const)(long, c_rasterizer_texture_ref)
	// function call : bool (*const)()
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*)(s_rasterizer_globals *, c_rasterizer_texture_ref *, c_enum<enum e_rasterizer_default_bitmap,long>)
	// function call : void (*const)(long, c_rasterizer_texture_ref)
	// function call : void (*const)(void *, long, c_enum<enum e_render_method_extern,long>, long)
	todo("implement");
	_sub_108F6D50(device, a2, render_method_extern, sampler);
}

_extern void _sub_108F1310(c_render_method const *, c_enum<enum e_entry_point,long>, long, bool);
void render_method_submit_externs_hook(c_render_method const *render_method, c_enum<enum e_entry_point,long> entry_point, long volatility, bool ignore_real_volatility) // 0x108F1310
{
	// `anonymous-namespace'::render_method_submit_externs_hook
	// static ...; // 0x108F15E0
	// c_render_method const *render_method;
	// c_enum<enum e_entry_point,long> entry_point;
	// long volatility;
	// bool ignore_real_volatility;
	// s_render_method_template_pass const *pass;
	// c_render_method_template const *rmt2;
	{
		// __int32 i;
		{
			// s_render_method_template_routing_info const *routing_info;
		}
	}
	{
		{
			{
				// real_vector4d extern_constant;
			}
		}
	}
	{
		{
			{
			}
		}
	}
	// function call : void (*const)(long)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	todo("implement");
	_sub_108F1310(render_method, entry_point, volatility, ignore_real_volatility);
}

_extern void _sub_108F1CE0(long, bool);
void render_method_submit_single_extern_hook(long render_method_extern, bool a2) // 0x108F1CE0
{
	// `anonymous-namespace'::render_method_submit_single_extern_hook
	// static ...; // 0x108F1DB8
	// static ...; // 0x108F1DB0
	// long render_method_extern;
	// bool a2;
	// s_extern_description const *const extern_desc;
	{
		// real_vector4d constant;
	}
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	todo("implement");
	_sub_108F1CE0(render_method_extern, a2);
}

_extern void _sub_108F1B70(long);
void render_method_submit_set_bsp_call_hook(long lightmap_bsp_data_handle) // 0x108F1B70
{
	// `anonymous-namespace'::render_method_submit_set_bsp_call_hook
	// static ...; // 0x108F1C84
	// static ...; // 0x108F1C78
	// static ...; // 0x108F1C70
	// long lightmap_bsp_data_handle;
	// long *g_lightmap_bsp_data_handle;
	{
		// __int32 i;
		{
			// s_extern_description const *const extern_desc;
			{
				// real_vector4d constant;
			}
		}
	}
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	todo("implement");
	_sub_108F1B70(lightmap_bsp_data_handle);
}

_extern float _sub_108EEA20(long, s_render_method_animated_parameter *);
float evaluate_function_hook(long rm_index, s_render_method_animated_parameter *function) // 0x108EEA20
{
	// `anonymous-namespace'::evaluate_function_hook
	// s_render_method_animated_parameter *function;
	// void *(*const scenario_interpolator_get)(unsigned long);
	// bool (*const sub_687DE0)(void *);
	// float (*const sub_687B50)(void *, long);
	// float (*const m_context_interface)(long, long, long);
	// float scalar;
	// bool is_scnr_interpolator;
	// bool is_unique_id;
	// float range_output;
	// float (*const sub_687D80)(void *, long);
	// float scalar_output;
	{
		// float scalar;
		// float sec_elapsed;
		{
			// float unique_id;
		}
		{
			// void *interpolator_block;
		}
	}
	// function call : float (*const)()
	// function call : char (*const)(s_tag_data *)
	// function call : float (*const)(s_tag_data *, float, float)
	// function call : void *(*const)(unsigned long)
	// function call : bool (*const)(void *)
	// function call : float (*const)(void *, long)
	// function call : float (*const)(void *, long)
	// function call : float (*const)(s_tag_data *, float, float)
	// function call : char (*const)(s_tag_data *)
	// function call : float (*const)(s_tag_data *, float, float)
	// function call : float (*const)(long, long, long)
	// function call : float (*const)(long, long, long)
	// function call : float (*const)(s_tag_data *, float, float)
	todo("implement");
	float __result = _sub_108EEA20(rm_index, function);
	return __result;
}

_extern void _sub_108F77F0(long, real_vector4d *, s_destination_info *, long *, s_tag_block_index *, c_tag_block<s_render_method_routing_info> *, c_tag_block<s_render_method_animated_parameter> *);
void update_constants_hook(long render_method_index, real_vector4d *source, s_destination_info *destination_info, long *destination_count, s_tag_block_index *routing_index, c_tag_block<s_render_method_routing_info> *routing_block, c_tag_block<s_render_method_animated_parameter> *functions_block) // 0x108F77F0
{
	// `anonymous-namespace'::update_constants_hook
// $LN16:
// $LN15:
// $LN13:
	// long render_method_index;
	// real_vector4d *source;
	// s_destination_info *destination_info;
	// long *destination_count;
	// s_tag_block_index *routing_index;
	// c_tag_block<s_render_method_routing_info> *routing_block;
	// c_tag_block<s_render_method_animated_parameter> *functions_block;
	// float (*const c_function_definition__map_to_output_range_legacy)(s_tag_data const *, float);
	// real_rgb_color out_colour;
	// s_render_method_animated_parameter const *functions;
	// s_render_method_routing_info const *routing_info;
	// float (*const evaluate_function)(long, s_render_method_animated_parameter const *);
	// __int32 const offset;
	// void (*const c_function_definition__map_to_color_range_legacy)(s_tag_data const *, float, real_rgb_color *);
	{
		// __int32 i;
		{
			// s_render_method_animated_parameter const *function;
			// long count;
			// s_render_method_routing_info const *route;
			{
				// long cc_index;
			}
			{
				// float function_result;
				{
					// float mapped_result;
				}
			}
			{
				// __int32 in;
			}
		}
	}
	// function call : real_rgb_color *(*const)(unsigned long, real_rgb_color *)
	// function call : float (*const)(long, s_render_method_animated_parameter const *)
	// function call : void (*const)(s_tag_data const *, float, real_rgb_color *)
	// function call : float (*const)(s_tag_data const *, float)
	todo("implement");
	_sub_108F77F0(render_method_index, source, destination_info, destination_count, routing_index, routing_block, functions_block);
}

_extern bool _sub_108F7F10();
bool z_buffer_fix_enabled() // 0x108F7F10
{
	// `anonymous-namespace'::z_buffer_fix_enabled
	// procedure flags: nofpo
	todo("implement");
	bool __result = _sub_108F7F10();
	return __result;
}

_extern void _sub_108F0830(float *, float *);
void rasterizer_get_z_planes_hook(float *near_clip, float *far_clip) // 0x108F0830
{
	// `anonymous-namespace'::rasterizer_get_z_planes_hook
	// float *far_clip;
	todo("implement");
	_sub_108F0830(near_clip, far_clip);
}

_extern bool _sub_108EE9A0(_D3DFORMAT);
bool depth_stencil_format_is_float(_D3DFORMAT format) // 0x108EE9A0
{
	// `anonymous-namespace'::depth_stencil_format_is_float
	// _D3DFORMAT format;
	todo("implement");
	bool __result = _sub_108EE9A0(format);
	return __result;
}

_extern void _sub_108EB8D0(e_surface);
void c_surface__set_depth_stencil(e_surface surface) // 0x108EB8D0
{
	// `anonymous-namespace'::c_surface__set_depth_stencil
	// e_surface surface;
	// IDirect3D9Ex *d3d9ex;
	// IDirect3DDevice9Ex *device;
	// c_render_surface *render_surface;
	{
		// c_render_surface *color_render_surface;
	}
	// function call : HRESULT (IDirect3DSurface9 *)
	// function call : HRESULT (unsigned __int32, _D3DDEVTYPE, _D3DFORMAT, _D3DFORMAT)
	// function call : HRESULT (IDirect3DSurface9 *)
	todo("implement");
	_sub_108EB8D0(surface);
}

_extern void _sub_108EBA70(IDirect3DSurface9 *);
void c_surface__set_depth_stencil_surface(IDirect3DSurface9 *surface) // 0x108EBA70
{
	// `anonymous-namespace'::c_surface__set_depth_stencil_surface
	// static ...; // 0x108EBB44
	// static ...; // 0x108EBB38
	// static ...; // 0x108EBB30
	// IDirect3DSurface9 *surface;
	// IDirect3DDevice9Ex *device;
	// _D3DSURFACE_DESC surface_desc;
	// function call : HRESULT (_D3DSURFACE_DESC *)
	// function call : HRESULT (IDirect3DSurface9 *)
	todo("implement");
	_sub_108EBA70(surface);
}

_extern void _sub_108E4F90(c_first_person_view *, void *, bool);
void c_first_person_view__override_projection(c_first_person_view *thisptr, void *unused, bool a2) // 0x108E4F90
{
	// `anonymous-namespace'::c_first_person_view__override_projection
	// static ...; // 0x108E53E8
	// c_first_person_view *thisptr;
	// void *unused;
	// bool a2;
	// float aspect_ratio;
	// float c_first_person_view__m_z_far_scale;
	// real_rectangle2d frustum_bounds;
	// float (*const cortana_effect_get_fov_scale)();
	// float (*const sub_A8E700)();
	// bool use_view_offset_scaling;
	// __int32 width;
	// float c_first_person_view__m_fov_scale;
	// __int32 height;
	{
		// float const k_magic_halo3_shipped_ratio;
		// float const fov_scale;
	}
	{
		// float z_near_scale;
	}
	// function call : float (*const)()
	// function call : float (*const)()
	// function call : bool (*const)(s_render_camera *, real_rectangle2d *)
	// function call : void (*const)(s_render_camera *, real_rectangle2d *, s_render_projection *, float)
	// function call : void (*const)(s_render_camera *, s_render_projection *)
	todo("implement");
	_sub_108E4F90(thisptr, unused, a2);
}

extern s_observer_result *_sub_108F0600(long);
s_observer_result *observer_get_camera__call_hook(long output_user_index) // 0x108F0600
{
	// `anonymous-namespace'::observer_get_camera__call_hook
	// long output_user_index;
	// float fov_rad;
	// s_observer_result *observer_camera;
	// float horizontal_fov;
	// function call : s_observer_result *(*const)(long)
	todo("implement");
	s_observer_result * __result = _sub_108F0600(output_user_index);
	return __result;
}

_extern void _sub_108F07D0();
void post_render_player_view_hook() // 0x108F07D0
{
	// `anonymous-namespace'::post_render_player_view_hook
	// procedure flags: nofpo
	// void (*const c_view__end)();
	// function call : void (*const)()
	todo("implement");
	_sub_108F07D0();
}

_extern void _sub_108F5D40();
void render_underwater_fog_hook() // 0x108F5D40
{
	// `anonymous-namespace'::render_underwater_fog_hook
	// procedure flags: nofpo
	// static ...; // 0x108F647D
	// static ...; // 0x108F6476
	// static ...; // 0x108F6470
	// static ...; // 0x108F6451
	// static ...; // 0x108F6448
	// static ...; // 0x108F640C
	// static ...; // 0x108F6404
	// unsigned long *g_game_resolution;
	// long &g_render_underwater_fog;
	{
		// s_screen_vertex vertices[4];
		// real_vector4d ps_screen_constants;
		// real_vector4d k_ps_water_view_depth_constant;
		// float z_near;
		// float z_far;
	}
	// function call : long (*const)(long)
	// function call : void (*const)(long)
	// function call : void (*const)(long, long)
	// function call : bool (*const)(long, long, long, long)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, e_surface)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*const)(long, e_surface)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : bool (*const)(IDirect3DIndexBuffer9 *)
	// function call : void (*const)(long, long, void *, long)
	todo("implement");
	_sub_108F5D40();
}

_extern void _sub_108F6A00(s_render_projection *, float *, s_render_projection *, float *);
void sub_14E3A00_vision_call_hook(s_render_projection *render_proj, float *proj_matrix, s_render_projection *out_render_proj, float *out_proj_matrix) // 0x108F6A00
{
	// `anonymous-namespace'::sub_14E3A00_vision_call_hook
	// static ...; // 0x108F6BF8
	// static ...; // 0x108F6BF0
	// s_render_projection *render_proj;
	// float *proj_matrix;
	// s_render_projection *out_render_proj;
	// float *out_proj_matrix;
	// bool cached_use_fp_z;
	// real_rectangle2d bounds;
	// s_render_projection new_render_proj;
	// c_player_view *x_current_player_view;
	// real_vector4d zbuf_params;
	// void (*const sub_14E3A00)(s_render_projection *, float *, s_render_projection *, float *);
	// function call : bool (*const)(s_render_camera *, real_rectangle2d *)
	// function call : void (*const)(s_render_camera *, real_rectangle2d *, s_render_projection *, float)
	// function call : void (*const)(s_render_projection *, float *, s_render_projection *, float *)
	// function call : long (*const)(long)
	// function call : long (*const)(long)
	// function call : void (*const)(long, long, real_vector4d const *)
	todo("implement");
	_sub_108F6A00(render_proj, proj_matrix, out_render_proj, out_proj_matrix);
}

_extern void _sub_108F0A20(s_render_geometry *, s_mesh *, s_part *, e_entry_point, unsigned long *, s_geometry_material *);
void render_mesh_part_default_hook(s_render_geometry *geometry, s_mesh *mesh, s_part *part, e_entry_point entry_point, unsigned long *subpart_visibility, s_geometry_material *materials) // 0x108F0A20
{
	// `anonymous-namespace'::render_mesh_part_default_hook
	// s_geometry_material *materials;
	// c_rasterizer_vertex_buffer *vertex_buffer;
	// bool alpha_test_enabled;
	// bool (*const player_reading_terminal)();
	// c_rasterizer_index_buffer *index_buffer;
	// c_rasterizer_vertex_buffer *lighting_buffer;
	// long (*const global_preferenced_get_lighting_quality)();
	// bool prevent_backface_culling;
	// c_rasterizer_index_buffer *(*const render_geometry_get_index_buffer)(s_render_geometry *, long);
	// bool (*const render_method_submit)(long, c_render_method *, e_vertex_type, e_prt_vertex_type, e_entry_point, bool);
	// c_render_method *render_method;
	// long render_method_index;
	// long cached_cull_mode;
	{
		// c_rasterizer_vertex_buffer *ambient_ptr_buffer;
	}
	{
		// long *g_prt_type_to_entry_point;
	}
	{
		// long index_start;
		// long index_end;
		{
			// long i;
			{
				// s_subpart *subpart;
			}
		}
	}
	// function call : c_rasterizer_index_buffer *(*const)(s_render_geometry *, long)
	// function call : c_rasterizer_vertex_buffer *(*const)(s_render_geometry *, s_mesh *, e_vertex_buffer_usage)
	// function call : bool (*const)(c_rasterizer_vertex_buffer const *)
	// function call : c_rasterizer_vertex_buffer *(*const)(s_render_geometry *, s_mesh *, e_vertex_buffer_usage)
	// function call : c_rasterizer_vertex_buffer *(*const)(s_render_geometry *, s_mesh *, e_vertex_buffer_usage)
	// function call : bool (*const)(c_rasterizer_vertex_buffer const *)
	// function call : c_rasterizer_vertex_buffer *(*const)(s_render_geometry *, s_mesh *, e_vertex_buffer_usage)
	// function call : bool (*const)(c_rasterizer_vertex_buffer const *)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : long (*const)()
	// function call : bool (*const)(long, c_render_method *, e_vertex_type, e_prt_vertex_type, e_entry_point, bool)
	// function call : long (*const)()
	// function call : void (*const)(long)
	// function call : void (*const)(bool)
	// function call : void (*const)(c_rasterizer_index_buffer const *, long, long, long, long)
	// function call : void (*const)(c_rasterizer_index_buffer const *, long, long, long, long)
	// function call : void (*const)(c_rasterizer_index_buffer const *, long, long, long, long)
	// function call : void (*const)(bool)
	// function call : void (*const)(long)
	todo("implement");
	_sub_108F0A20(geometry, mesh, part, entry_point, subpart_visibility, materials);
}

_extern void _sub_108E8D60(long, e_entry_point, long);
void c_structure_renderer__render_cluster_mesh_part_hook(long cluster_visibility_index, e_entry_point entry_point, long flags) // 0x108E8D60
{
	// `anonymous-namespace'::c_structure_renderer__render_cluster_mesh_part_hook
	// long flags;
	// s_render_cluster_part *cluster;
	// e_entry_point (*const update_cluster_stream_and_determine_lighting_attributes)(e_entry_point, long, s_render_geometry *, s_mesh *, s_part *, s_geometry_material *, s_cluster_reference);
	{
		// s_geometry_material *materials;
		// long bsp_index;
		// s_scenario_structure_bsp *structure_bsp;
		{
			// s_render_geometry *geometry;
			// s_part *part;
			// long cubemap_index;
			// s_mesh *mesh;
			{
				// long breakable_surface_set_index;
				// unsigned long *subpart_visibility;
				// long context;
				{
					// s_breakable_surface_set *breakable_surface_set;
				}
			}
		}
	}
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : long (*const)(s_cluster_reference)
	// function call : s_render_geometry *(*const)(long)
	// function call : s_breakable_surface_set *(*const)(long, long, long)
	// function call : e_entry_point (*const)(e_entry_point, long, s_render_geometry *, s_mesh *, s_part *, s_geometry_material *, s_cluster_reference)
	// function call : s_cluster_reference (*const)(bool, long, s_cluster_reference, long, s_cluster_reference, long, s_cluster_reference, long, float, unsigned long *, long, long, long, void *)
	// function call : void (*const)(long long, s_render_geometry *, s_mesh *, s_part *, e_entry_point, unsigned long *, s_geometry_material *)
	// function call : void (*const)(long, long, long)
	// function call : void (*const)(bool)
	todo("implement");
	_sub_108E8D60(cluster_visibility_index, entry_point, flags);
}

_extern void _sub_108EA030(long, e_entry_point, long);
void c_structure_renderer__render_instance_mesh_part_hook(long render_instance_index, e_entry_point entry_point, long flags) // 0x108EA030
{
	// `anonymous-namespace'::c_structure_renderer__render_instance_mesh_part_hook
	// static ...; // 0x108EA588
	// long render_instance_index;
	// e_entry_point entry_point;
	// long flags;
	// e_entry_point (*const update_cluster_instance_stream_and_determine_lighting_attributes)(e_entry_point, long, s_scenario_lightmap_bsp_data *, s_render_geometry *, s_mesh *, s_part *, s_geometry_material *, long, s_structure_instanced_geometry_instance *);
	// s_render_instance_part *render_instance_part;
	{
		// long bsp_index;
		// s_scenario_structure_bsp *structure_bsp;
		{
			// s_scenario_lightmap_bsp_data *lightmap_data;
			// s_structure_instanced_geometry_instance *instance;
			// s_geometry_material *materials;
			// s_render_geometry *geometry;
			{
				// long current_definition_index;
				// s_compression_info *compression_info;
				// long breakable_surface_set_index;
				// s_part *part;
				// long definition_index;
				// s_structure_instanced_geometry_definition *instance_geometry_definition;
				// s_cluster_reference cluster_reference;
				// unsigned long *subpart_visibility;
				// long instance_index;
				// s_mesh *mesh;
				{
					// s_breakable_surface_set *breakable_surface_set;
				}
			}
		}
	}
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : s_scenario_lightmap_bsp_data *(*const)(long)
	// function call : s_render_geometry *(*const)(long)
	// function call : s_structure_instanced_geometry_definition *(*const)(long, long)
	// function call : void (*const)(s_compression_info const *)
	// function call : void (*const)(real_matrix4x3 const *)
	// function call : s_cluster_reference (*const)(bool, long, s_cluster_reference, long, s_cluster_reference, long, s_cluster_reference, long, float, unsigned long *, long, long, long, void *)
	// function call : e_entry_point (*const)(e_entry_point, long, s_scenario_lightmap_bsp_data *, s_render_geometry *, s_mesh *, s_part *, s_geometry_material *, long, s_structure_instanced_geometry_instance *)
	// function call : void (*const)(long, long, long, long)
	// function call : s_breakable_surface_set *(*const)(long, long, long)
	// function call : void (*const)(long)
	// function call : void (*const)(long long, s_render_geometry *, s_mesh *, s_part *, e_entry_point, unsigned long *, s_geometry_material *)
	// function call : void (*const)()
	// function call : void (*const)(long, long, long)
	// function call : void (*const)(bool)
	todo("implement");
	_sub_108EA030(render_instance_index, entry_point, flags);
}

_extern void _sub_108EA710(bool);
void c_structure_renderer__submit_cluster_visibility(bool include_transparent) // 0x108EA710
{
	// `anonymous-namespace'::c_structure_renderer__submit_cluster_visibility
	// static ...; // 0x108EAD0B
	// static ...; // 0x108EAD05
	// static ...; // 0x108EACFC
	// static ...; // 0x108EACD8
	// static ...; // 0x108EACD0
	// bool include_transparent;
	// long iterator;
	// long cluster_starting_index;
	// s_visible_items &visible_items;
	{
		// s_visible_cluster *cluster;
		{
			// s_render_geometry *geometry;
			// s_scenario_structure_bsp *structure_bsp;
			// s_mesh *mesh;
			// long structure_bsp_index;
			{
				// long part_index;
				{
					// unsigned long flags;
					// s_render_cluster_part *render_part;
					// bool is_decal;
					// s_part *part;
					// c_render_method *render_method;
					// long render_method_index;
					// bool is_transparent;
					// bool use_z_prepass;
					{
						// real_point3d position;
						// real_plane3d plane;
						// float radius;
						{
							// short sorting_index;
							// s_sorting_position *sorting_position;
						}
					}
				}
			}
		}
	}
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : s_render_geometry *(*const)(long)
	// function call : bool (*const)(s_part *, s_geometry_material *)
	// function call : bool (*const)(long)
	// function call : long (*const)(void *, void *, long)
	// function call : long (*const)(real_point3d const *, real_plane3d const *, float, e_sorting_layer, void (*)(void const *, long), void *, long, float)
	todo("implement");
	_sub_108EA710(include_transparent);
}

_extern void _sub_108EAEA0(bool);
void c_structure_renderer__submit_instance_visibility(bool include_transparent) // 0x108EAEA0
{
	// `anonymous-namespace'::c_structure_renderer__submit_instance_visibility
	// static ...; // 0x108EB66B
	// static ...; // 0x108EB665
	// static ...; // 0x108EB65C
	// static ...; // 0x108EB638
	// static ...; // 0x108EB630
	// bool include_transparent;
	// long count;
	// bool (*const instance_list_sort_proc)(unsigned short, unsigned short, void const *);
	// s_sorter<s_visible_instance_group,4096> sorter;
	// long instance_group_start_index;
	// s_visible_items &visible_items;
	{
		// unsigned short i;
	}
	{
		// long i;
		{
			// long instance_end_index;
			// s_render_geometry *geometry;
			// long instance_start_index;
			// s_visible_instance_group *instance_list;
			// s_scenario_structure_bsp *structure_bsp;
			// s_mesh *mesh;
			// long structure_bsp_index;
			{
				// long part_index;
				{
					// s_part *part;
					// long render_method_index;
					{
						// long k;
						{
							// unsigned long flags;
							// s_visible_instance *instance;
							// s_render_instance_part *render_part;
							// bool is_decal;
							// c_render_method *render_method;
							// long render_method_index;
							// bool is_transparent;
							// bool use_z_prepass;
							{
								// real_point3d position;
								// real_plane3d plane;
								// real_matrix4x3 *matrix;
								// float radius;
								{
									// short sorting_index;
									// s_sorting_position *sorting_position;
								}
							}
						}
					}
				}
			}
		}
	}
	// function call : void (*const)(void *, long, bool (*)(unsigned short, unsigned short, void const *), void const *)
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : s_render_geometry *(*const)(long)
	// function call : bool (*const)(s_part *, s_geometry_material *)
	// function call : bool (*const)(long)
	// function call : long (*const)(real_point3d const *, real_plane3d const *, float, e_sorting_layer, void (*)(void const *, long), void *, long, float)
	todo("implement");
	_sub_108EAEA0(include_transparent);
}

_extern void _sub_108EB870(bool);
void c_structure_renderer__submit_visibility_hook(bool include_transparent) // 0x108EB870
{
	// `anonymous-namespace'::c_structure_renderer__submit_visibility_hook
	// bool include_transparent;
	todo("implement");
	_sub_108EB870(include_transparent);
}

_extern void _sub_108E9110();
void c_structure_renderer__render_decorators_hook() // 0x108E9110
{
	// `anonymous-namespace'::c_structure_renderer__render_decorators_hook
	// procedure flags: nofpo
	// static ...; // 0x108E9D22
	// static ...; // 0x108E9D12
	// static ...; // 0x108E9D04
	// static ...; // 0x108E9CF0
	// static ...; // 0x108E9CC0
	// static ...; // 0x108E9CB8
	// long (*const preferences_get_detail_quality)();
	// void (*const sub_A28480)(__int32);
	// void (*const rasterizer_set_vertex_buffer_stream)(c_rasterizer_vertex_buffer *, long);
	// float cull_modifier;
	// bool (*const visibility_region_test_sphere)(void *, long, real_point3d *, float, bool *);
	// long (*const scenario_zone_set_structure_bsp_cluster_visible_sky_index_get)(s_scenario *, long, long, long);
	// bool &g_render_decorators;
	// long (*const scenario_zone_set_index_get)();
	// float (*const rasterizer_camera_get_fov_pixel_linear_scale)();
	// bool &byte_50E8931;
	// void (*const sub_A301E0)(long);
	// void (*const clear_cached_sun_constants)();
	{
		// IDirect3DDevice9Ex *const g_device;
		// s_wind_definition *const wind;
		// c_player_view *player_view;
		// real_point3d &camera_position;
		{
			// c_visibility_collection *collection;
			// float fov_scale;
			// s_visibility_region *region;
			{
				// __int32 i;
				{
					// s_scenario_structure_bsp *const global_sbsp;
					// s_structure_cluster *const cluster;
					// long cluster_index;
					// long structure_bsp_index;
					{
						// long zone_set_index;
						// long visible_sky_index;
					}
					{
						// __int32 j;
						{
							// long dctr_index;
							// s_decorator_set *const decorator_set;
							// s_decorator_grid *const decorator_grid;
							{
								// float cull_end;
								// float cull_start;
								// real_vector3d pos;
								// float position_magnitude;
								{
									// bool fully_contained;
									{
										// c_rasterizer_vertex_buffer *vertex_buffer;
										// real_vector4d LOD_constants;
										// s_render_geometry *const render_geometry;
										// c_rasterizer_index_buffer *const index_buffer;
										// c_rasterizer_vertex_buffer *sbsp_vertex_buffer;
										// real_vector4d variant_index_count;
										// s_mesh *const mesh;
										// long instance_index_count;
										// s_render_model *const render_model;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	// function call : s_wind_definition *(*)(real_point3d *)
	// function call : void (*)(s_wind_definition *, s_wind_values *)
	// function call : long (*const)(long)
	// function call : void (*const)(long, long)
	// function call : void (*const)(s_wind_definition *, s_wind_values *)
	// function call : long (*const)(long)
	// function call : void (*const)()
	// function call : c_visibility_collection *(*const)()
	// function call : float (*const)()
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : long (*const)()
	// function call : long (*const)(s_scenario *, long, long, long)
	// function call : void (*const)(long)
	// function call : void (*const)(bool)
	// function call : s_decorator_set *(*)(long)
	// function call : bool (*const)(void *, long, real_point3d *, float, bool *)
	// function call : long (*)(s_decorator_set *)
	// function call : bool (*const)(long, long, long, long)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long)
	// function call : void *(*const)(unsigned long, long)
	// function call : c_rasterizer_vertex_buffer *(*const)(s_render_geometry const *, long)
	// function call : bool (*const)(c_rasterizer_vertex_buffer const *)
	// function call : void (*const)(s_compression_info const *, float)
	// function call : void (*const)(long, long, long)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : c_rasterizer_vertex_buffer *(*const)(s_render_geometry const *, long)
	// function call : void (*const)(c_rasterizer_vertex_buffer *, long)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(c_rasterizer_vertex_buffer *, long)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : HRESULT (unsigned __int32, unsigned __int32)
	// function call : HRESULT (unsigned __int32, unsigned __int32)
	// function call : void (*const)(__int32)
	// function call : c_rasterizer_index_buffer *(*const)(s_render_geometry const *, long)
	// function call : void (*const)(c_rasterizer_index_buffer const *, long, long, long, long)
	// function call : HRESULT (unsigned __int32, unsigned __int32)
	// function call : HRESULT (unsigned __int32, unsigned __int32)
	// function call : void (*const)(__int32)
	// function call : void (*const)(bool)
	// function call : void (*const)(bool)
	// function call : long (*const)(long)
	todo("implement");
	_sub_108E9110();
}

_extern void _sub_108E6520(s_render_object *, s_visible_object *, bool, __int32);
void c_object_renderer__submit_object_mesh_parts_for_active_camo_hook(s_render_object *render_object, s_visible_object *visible_object, bool a3, __int32 is_first_person) // 0x108E6520
{
	// `anonymous-namespace'::c_object_renderer__submit_object_mesh_parts_for_active_camo_hook
	// static ...; // 0x108E6A8C
	// static ...; // 0x108E6A84
	// s_render_object *render_object;
	// s_visible_object *visible_object;
	// bool a3;
	// __int32 is_first_person;
	// void (*const s_model_skinning_matrix_to_real_matrix4x3)(real_matrix4x3 *, void *);
	// void (*const sub_A73840)();
	// void *(*const model_skinning_get_rigid_region_matrix)(void *, long);
	// void *(*const object_get_active_shield_render_parameters)(s_object_data *, long);
	// void (*const sub_A731A0)(long, long);
	// long (*const render_objects_add_element)(s_render_object *, s_render_object_info *, unsigned long *, short, short, short, short, __int32);
	// void *(*const sub_A6DAA0)(long);
	// s_render_model *const mode;
	{
		// void *shield_impact;
		{
			// __int32 region_index;
			{
				// unsigned char region_mesh_index;
				// short transparent_sort_index;
				{
					// s_mesh const *mesh;
					{
						// __int32 part_index;
						{
							// s_part const *part;
							// long render_object_mesh_part_index;
							// c_render_method *const render_method;
							// unsigned long render_method_index;
							{
								// s_render_object_globals *render_object_globals;
								// real_point3d sorting_position;
								{
									// real_point3d position;
									// real_matrix4x3 skinning_matrix;
									// void *model_skinning;
									// void *model_skinning_matrix;
									// long element;
								}
							}
						}
					}
				}
			}
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void *(*const)(s_object_data *, long)
	// function call : long (*const)(s_render_object *, s_render_object_info *, unsigned long *, short, short, short, short, __int32)
	// function call : void (*const)()
	// function call : void *(*const)(long)
	// function call : void *(*const)(void *, long)
	// function call : void (*const)(real_matrix4x3 *, void *)
	// function call : long (*const)(real_point3d const *, real_plane3d const *, float, e_sorting_layer, void (*)(void const *, long), void *, long, float)
	// function call : void (*const)(long, long)
	todo("implement");
	_sub_108E6520(render_object, visible_object, a3, is_first_person);
}

_extern void _sub_108EDE80(s_render_geometry *, __int32, __int32, e_entry_point, s_geometry_material *);
void c_water_renderer__render_water_part_hook(s_render_geometry *geometry, __int32 mesh_index, __int32 part_index, e_entry_point entry_point, s_geometry_material *materials) // 0x108EDE80
{
	// `anonymous-namespace'::c_water_renderer__render_water_part_hook
	// static ...; // 0x108EE48C
	// s_render_geometry *geometry;
	// __int32 mesh_index;
	// __int32 part_index;
	// e_entry_point entry_point;
	// s_geometry_material *materials;
	// c_rasterizer_index_buffer *g_water_geometry_index_buffer;
	// c_rasterizer_vertex_buffer *(*const mesh_get_vertex_buffer)(s_render_geometry *, s_mesh *, long);
	// s_part *const mesh_part;
	// bool (*const c_water_renderer__is_active_ripple_exist)();
	// float &k_ripple_buffer_radius;
	// void (*const c_rasterizer__set_vertex_stream_with_offset)(long, void *, long, unsigned __int32);
	// bool &g_render_water_tesselation;
	// c_rasterizer_vertex_buffer *g_water_memexport_vertex_buffer;
	// s_mesh *const mesh;
	{
		// unsigned long rm_index;
		{
			// c_render_method *const render_method;
			{
				// real_vector4d unknown_water_instance_constant;
				{
					// __int32 k_is_water_tesselated;
					// __int32 active_water_interaction;
					{
						// long vertex_count;
						// IDirect3DDevice9Ex *g_device;
						// c_rasterizer_vertex_buffer *water_vertex_buffer_2;
						// c_rasterizer_vertex_buffer *water_vertex_buffer_1;
					}
				}
			}
		}
	}
	// function call : bool (*const)(long, c_render_method const *, e_vertex_type, e_prt_vertex_type, e_entry_point, bool)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : bool (*const)()
	// function call : void (*const)(long, long, __int32 const *)
	// function call : void (*const)(long, long, __int32 const *)
	// function call : void (*const)(long, e_surface)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*const)(long, e_surface)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*const)(long, long, __int32 const *)
	// function call : c_rasterizer_vertex_buffer *(*const)(s_render_geometry *, s_mesh *, long)
	// function call : c_rasterizer_vertex_buffer *(*const)(s_render_geometry *, s_mesh *, long)
	// function call : void (*const)(long, void *, long, unsigned __int32)
	// function call : void (*const)(long, void *, long, unsigned __int32)
	// function call : void (*const)(long, void *, long, unsigned __int32)
	// function call : HRESULT (unsigned __int32, unsigned __int32)
	// function call : HRESULT (unsigned __int32, unsigned __int32)
	// function call : HRESULT (unsigned __int32, unsigned __int32)
	// function call : HRESULT (unsigned __int32, unsigned __int32)
	// function call : void (*const)(c_rasterizer_index_buffer const *, long, long, long, long)
	// function call : HRESULT (unsigned __int32, unsigned __int32)
	// function call : HRESULT (unsigned __int32, unsigned __int32)
	// function call : HRESULT (unsigned __int32, unsigned __int32)
	// function call : HRESULT (unsigned __int32, unsigned __int32)
	todo("implement");
	_sub_108EDE80(geometry, mesh_index, part_index, entry_point, materials);
}

_extern void _sub_108EE6B0(long *, long *);
void c_water_renderer__update_water_structure_part_list_hook(long *water_part_indices, long *out_count) // 0x108EE6B0
{
	// `anonymous-namespace'::c_water_renderer__update_water_structure_part_list_hook
	// long *out_count;
	// long count;
	// long start_index;
	// bool (*const cluster_sort_proc)(unsigned short, unsigned short, void const *);
	{
		// __int32 i;
		{
			// s_render_cluster_part *mesh_part;
			// s_render_geometry *geometry;
			// long structure_bsp_index;
		}
	}
	// function call : void (*const)(void *, long, bool (*)(unsigned short, unsigned short, void const *), void const *)
	// function call : s_render_geometry *(*const)(long)
	todo("implement");
	_sub_108EE6B0(water_part_indices, out_count);
}

_extern void _sub_108F6670(s_render_shield_parts *, void *, s_visible_object *, char);
void s_render_shield_parts__render_hook(s_render_shield_parts *thisptr, void *unused, s_visible_object *visible_object, char flags) // 0x108F6670
{
	// `anonymous-namespace'::s_render_shield_parts__render_hook
	// s_render_shield_parts *thisptr;
	// void *unused;
	// s_visible_object *visible_object;
	// char flags;
	// void (*const sub_A79260)(s_render_object_mesh_part *);
	// void (*const render_mesh_part_no_material)(s_render_geometry *, long, long);
	{
		// s_render_object_mesh_part render_object_mesh_part;
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : bool (*const)(long, long, long, long)
	// function call : void (*const)(s_render_object_mesh_part *)
	// function call : void (*const)(s_render_geometry *, long, long)
	todo("implement");
	_sub_108F6670(thisptr, unused, visible_object, flags);
}

_extern void _sub_108E5BE0(s_render_object_mesh_part *, e_entry_point, unsigned long *, s_lod_alphas);
void c_object_renderer__render_object_context_instances_hook(s_render_object_mesh_part *render_part, e_entry_point entry_point, unsigned long *subpart_visibility, s_lod_alphas alphas) // 0x108E5BE0
{
	// `anonymous-namespace'::c_object_renderer__render_object_context_instances_hook
	// static ...; // 0x108E60F4
	// static ...; // 0x108E60EC
	// s_render_object_mesh_part *render_part;
	// e_entry_point entry_point;
	// unsigned long *subpart_visibility;
	// s_lod_alphas alphas;
	// s_render_model *render_model;
	{
		// s_compression_info *compression_info;
		// long active_bsp_index;
		// long count;
		// s_mesh *mesh;
		{
			// long i;
			{
				// s_render_model_instance_placement *placement;
				// s_part *part;
				// float skinning_matrix[12];
				// real_matrix4x3 matrix;
				// real_matrix4x3 *skinning;
				// unsigned long local_subpart_visibility[2];
			}
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(s_compression_info const *)
	// function call : long (*const)()
	// function call : void (*const)(long, s_shader_extern_info const *)
	// function call : bool (*const)(s_part *, s_geometry_material *)
	// function call : void *(*const)(long)
	// function call : float *(*const)(void const *, long, real_matrix4x3 *)
	// function call : void (*const)(float *, __int32)
	// function call : void (*const)(long)
	// function call : void (*const)(long long, s_render_geometry *, s_mesh *, s_part *, e_entry_point, unsigned long *, s_geometry_material *)
	// function call : void (*const)(long)
	// function call : void (*const)(bool)
	todo("implement");
	_sub_108E5BE0(render_part, entry_point, subpart_visibility, alphas);
}

_extern void _sub_108E62B0(s_render_object_mesh_part *, e_entry_point, long, bool);
void c_object_renderer__render_object_context_mesh_part_hook(s_render_object_mesh_part *mesh_part, e_entry_point entry_point, long mesh_part_mask, bool a4) // 0x108E62B0
{
	// `anonymous-namespace'::c_object_renderer__render_object_context_mesh_part_hook
	// bool a4;
	// s_mesh *mesh;
	// s_render_model *render_model;
	{
		// long next_clip_plane_index;
		// long active_clip_plane_mask;
		// real_plane3d *g_cinematic_clip_planes;
		{
			// long i;
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(s_render_object_mesh_part const *)
	// function call : long (*const)(long, float const *)
	// function call : long (*const)(long)
	// function call : void (*const)(long long, s_render_geometry *, s_mesh *, s_part *, e_entry_point, unsigned long *, s_geometry_material *)
	// function call : long (*const)(long)
	// function call : void (*const)(bool)
	todo("implement");
	_sub_108E62B0(mesh_part, entry_point, mesh_part_mask, a4);
}

_extern void _sub_108F1190(s_render_geometry *, __int32, __int32);
void render_mesh_part_no_material(s_render_geometry *geometry, __int32 mesh_index, __int32 part_index) // 0x108F1190
{
	// `anonymous-namespace'::render_mesh_part_no_material
	// __int32 part_index;
	// c_rasterizer_vertex_buffer *vertex_buffer;
	// c_rasterizer_vertex_buffer *(*const mesh_get_vertex_buffer)(s_render_geometry *, s_mesh *, long);
	// s_part *const mesh_part;
	// c_rasterizer_index_buffer *index_buffer;
	// s_mesh *const mesh;
	// function call : c_rasterizer_index_buffer *(*const)(s_render_geometry const *, long)
	// function call : c_rasterizer_vertex_buffer *(*const)(s_render_geometry *, s_mesh *, long)
	// function call : bool (*const)(c_rasterizer_vertex_buffer const *)
	// function call : void (*const)(c_rasterizer_index_buffer const *, long, long, long, long)
	todo("implement");
	_sub_108F1190(geometry, mesh_index, part_index);
}

_extern long _sub_108E5530(long, long, long, long);
long c_geometry_sampler__find_render_method_index_from_collision_hook(long structure_bsp_index, long a2, long instance_index, long surface_index) // 0x108E5530
{
	// `anonymous-namespace'::c_geometry_sampler__find_render_method_index_from_collision_hook
	// long surface_index;
	// s_render_geometry *geometry;
	// s_scenario_structure_bsp *structure_bsp;
	{
		// s_structure_surface_plane *leaf;
		// s_structure_bsp_cache_file_resources *cache_file_tag_resources;
		{
			// long i;
			{
				// s_structure_plane *surface;
				// s_structure_cluster *cluster;
				// s_mesh *mesh;
				{
					// long part_index;
					{
						// s_part *part;
					}
				}
			}
		}
	}
	{
		// s_structure_instanced_geometry_definition *definition;
		{
			{
				{
					{
					}
				}
			}
		}
	}
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : s_render_geometry *(*const)(long)
	// function call : void *(*const)(void *)
	// function call : s_structure_instanced_geometry_definition *(*const)(long, long)
	todo("implement");
	long __result = _sub_108E5530(structure_bsp_index, a2, instance_index, surface_index);
	return __result;
}

_extern bool _sub_108F06E0(s_part const *, s_geometry_material const *);
bool part_is_renderable_hook(s_part const *part, s_geometry_material const *materials) // 0x108F06E0
{
	// `anonymous-namespace'::part_is_renderable_hook
	// s_geometry_material const *materials;
	todo("implement");
	bool __result = _sub_108F06E0(part, materials);
	return __result;
}

_extern void _sub_108F0190(short, e_entry_point);
void muffins_render_opaque(short datum_index, e_entry_point entry_point) // 0x108F0190
{
	// `anonymous-namespace'::muffins_render_opaque
	// e_entry_point entry_point;
	// char *muffin_array;
	// long cached_render_state_index;
	// void (*const set_render_object_shader_extern_info)(__int32, s_shader_extern_info *);
	// void (*const sub_A528C0)(s_render_lighting *, e_entry_point);
	// bool (*const sub_A47430)(s_part *, s_geometry_material *);
	// tls_data *tls;
	// s_muffin_datum *muffin;
	// void (*const render_mesh_submit_matrices)(real_matrix4x3 *, long);
	// s_muffin_definition *const muffin_definition;
	{
		// s_object_cached_render_state_datum *cached_object_render_state;
		// s_render_model *const render_model;
		{
			// __int32 i;
			{
				// s_muffin *muffin_part;
				{
					// s_mesh *const mesh;
					{
						// __int32 j;
						{
							// s_part *const mesh_part;
							{
								// long long identifier;
							}
						}
					}
				}
			}
		}
	}
	// function call : s_muffin_definition *(*)(long)
	// function call : long (*const)(long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(s_compression_info const *)
	// function call : long (*const)()
	// function call : void (*const)(__int32, s_shader_extern_info *)
	// function call : void (*const)(s_render_lighting *, e_entry_point)
	// function call : void (*const)(real_matrix4x3 *, long)
	// function call : bool (*const)(s_part *, s_geometry_material *)
	// function call : void (*const)(long long, s_render_geometry *, s_mesh *, s_part *, e_entry_point, unsigned long *, s_geometry_material *)
	todo("implement");
	_sub_108F0190(datum_index, entry_point);
}

_extern bool _sub_108F0070(s_render_geometry *, long, void const **, void const **, unsigned char *, long *, long *);
bool mesh_get_data_hook(s_render_geometry *render_geometry, long mesh_index, void const **out_vertex_data, void const **out_index_data, unsigned char *out_vertex_stride, long *out_vertex_count, long *out_index_count) // 0x108F0070
{
	// `anonymous-namespace'::mesh_get_data_hook
	// long *out_index_count;
	// c_rasterizer_vertex_buffer *vertex_buffer;
	// c_rasterizer_index_buffer *index_buffer;
	// s_mesh *mesh;
	// function call : c_rasterizer_vertex_buffer *(*const)(s_render_geometry const *, long)
	// function call : c_rasterizer_index_buffer *(*const)(s_render_geometry const *, long)
	todo("implement");
	bool __result = _sub_108F0070(render_geometry, mesh_index, out_vertex_data, out_index_data, out_vertex_stride, out_vertex_count, out_index_count);
	return __result;
}

_extern bool _sub_108F16F0(long, c_render_method const *, e_vertex_type, e_prt_vertex_type, e_entry_point, bool);
bool render_method_submit_particle_gpu_emitter_render_hook(long tag_index, c_render_method const *render_method, e_vertex_type vertex_type, e_prt_vertex_type prt_type, e_entry_point entry_point, bool a6) // 0x108F16F0
{
	// `anonymous-namespace'::render_method_submit_particle_gpu_emitter_render_hook
	// e_vertex_type vertex_type;
	// e_prt_vertex_type prt_type;
	// e_entry_point entry_point;
	// bool a6;
	// __int32 is_normal_basemap;
	// c_render_method_template *rmt2;
	{
		// __int32 i;
		{
			// s_bitmap_definition *bitmap;
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(long, long, __int32 const *)
	// function call : bool (*const)(long, c_render_method const *, e_vertex_type, e_prt_vertex_type, e_entry_point, bool)
	todo("implement");
	bool __result = _sub_108F16F0(tag_index, render_method, vertex_type, prt_type, entry_point, a6);
	return __result;
}

_extern bool _sub_108F6CD0();
bool sub_610230__ssao_call_hook() // 0x108F6CD0
{
	// `anonymous-namespace'::sub_610230__ssao_call_hook
	// procedure flags: nofpo
	// bool (*const sub_610230)();
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_108F6CD0();
	return __result;
}

_extern void _sub_108E8BE0(s_render_object_info *, s_render_object_mesh_part *, shield_impact_definition *, float, float, float, float, float);
void c_render_shield__render_object_internal_hook(s_render_object_info *info, s_render_object_mesh_part *data, shield_impact_definition *shield_impact, float recent_shield_damage, float current_shield_damage, float unknown_amount, float overshield_amount, float t) // 0x108E8BE0
{
	// `anonymous-namespace'::c_render_shield__render_object_internal_hook
	// float t;
	// void (*const c_render_shield__render_object_internal)(s_render_object_info *, s_render_object_mesh_part *, shield_impact_definition *, float, float, float, float, float);
	// s_part const *part;
	// s_mesh const *mesh;
	// s_render_model *render_model;
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(s_render_object_info *, s_render_object_mesh_part *, shield_impact_definition *, float, float, float, float, float)
	todo("implement");
	_sub_108E8BE0(info, data, shield_impact, recent_shield_damage, current_shield_damage, unknown_amount, overshield_amount, t);
}

_extern void _sub_108E4A80(c_dynamic_cubemap_sample *, void *, s_cluster_reference, real_point3d *, float);
void c_dynamic_cubemap_sample__search_for_cubemap_sample_in_cluster_hook(c_dynamic_cubemap_sample *thisptr, void *__formal, s_cluster_reference test_location, real_point3d *test_point, float tolerance) // 0x108E4A80
{
	// `anonymous-namespace'::c_dynamic_cubemap_sample__search_for_cubemap_sample_in_cluster_hook
	// float tolerance;
	// s_scenario_structure_bsp *old_structure_bsp;
	// bool is_better;
	// s_structure_cluster *test_cluster;
	// s_structure_cluster_cubemap_info *old_cubemap_info;
	// s_structure_cluster_cubemap_info *best_cubemap_info;
	// s_scenario_structure_bsp *test_structure_bsp;
	// long best_reference_index;
	// long best_index;
	// float best_distance;
	// float distance;
	// float old_distance;
	// s_structure_cluster *old_cluster;
	{
		// long i;
		{
			// s_structure_cluster_cubemap_info *cubemap_info;
			{
				// long j;
				{
					// s_cubemap_reference_point *reference;
				}
			}
		}
	}
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : s_scenario_structure_bsp *(*const)(long)
	todo("implement");
	_sub_108E4A80(thisptr, __formal, test_location, test_point, tolerance);
}

_extern float _sub_108F5BB0(s_render_projection const *, real_point3d const *, float);
float render_projection_sphere_diameter_in_pixels_hook(s_render_projection const *render_projection, real_point3d const *center, float radius) // 0x108F5BB0
{
	// `anonymous-namespace'::render_projection_sphere_diameter_in_pixels_hook
	// float radius;
	// float scale;
	// float distance;
	// function call : bool (*const)()
	// function call : bool (*const)()
	todo("implement");
	float __result = _sub_108F5BB0(render_projection, center, radius);
	return __result;
}

_extern void _sub_108E49D0();
void bink_playback_allocate_framebuffers_hook() // 0x108E49D0
{
	// `anonymous-namespace'::bink_playback_allocate_framebuffers_hook
	// procedure flags: nofpo
	// void (*const bink_playback_allocate_framebuffers)();
	// function call : void (*const)()
	todo("implement");
	_sub_108E49D0();
}

_extern void _sub_108E6C50(c_player_view *);
void c_player_view__render_hook(c_player_view *view) // 0x108E6C50
{
	// `anonymous-namespace'::c_player_view__render_hook
	// static ...; // 0x108E7CB7
	// static ...; // 0x108E7C9B
	// static ...; // 0x108E7C85
	// static ...; // 0x108E7C73
	// static ...; // 0x108E7C65
	// static ...; // 0x108E7C62
	// static ...; // 0x108E7C4C
	// static ...; // 0x108E7BF8
	// static ...; // 0x108E7BF0
	// c_player_view *view;
	// s_weighted_atmosphere_parameters atmosphere_parameters;
	// s_screen_effect_settings screen_effect;
	// s_screen_effect_shader_sample_result screen_effect_shader_sample;
	// s_cluster_reference cluster_reference;
	// short_rectangle2d window_bounds;
	{
		// float fov_rad;
		// bool should_render_render;
		// unsigned char a2;
		// float horizontal_fov;
		// bool render_albedo;
		{
			// bool v10;
			{
				// c_render_surface *v5;
				// c_render_surface *v4;
				// c_render_surface *v6;
				// real_vector4d shadow_map_pixel_size;
				// float sm_ps;
			}
		}
	}
	// function call : char (*const)(long)
	// function call : void (*const)()
	// function call : s_cluster_reference (*const)(c_player_view *, s_cluster_reference *)
	// function call : void (*const)(s_cluster_reference, real_point3d *)
	// function call : void (*const)(long)
	// function call : void (*const)(long)
	// function call : void (*const)(long, unsigned char *)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : void (*const)()
	// function call : void (*const)()
	// function call : void (*const)(long)
	// function call : void (*const)(c_player_view *, float)
	// function call : void (*const)()
	// function call : long (*const)(c_lights_view *, long)
	// function call : void (*const)(c_lights_view *, long)
	// function call : void (*const)(s_cluster_reference, s_weighted_atmosphere_parameters *)
	// function call : void (*const)(s_weighted_atmosphere_parameters *, bool, bool)
	// function call : void (*const)(s_weighted_atmosphere_parameters *, bool, bool)
	// function call : void (*const)()
	// function call : void (*const)()
	// function call : bool (*const)(c_player_view *)
	// function call : bool (*const)()
	// function call : void (*const)(bool)
	// function call : bool (*const)()
	// function call : unsigned long (*const)()
	// function call : void (*const)(long, long)
	// function call : void (*const)()
	// function call : void (*const)(c_player_view *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : char (*const)(c_player_view *)
	// function call : void (*const)(float, float, bool, float, bool, char, bool)
	// function call : c_render_surface *(*const)(c_surface_group *, e_surface)
	// function call : c_render_surface *(*const)(c_surface_group *, e_surface)
	// function call : c_render_surface *(*const)(c_surface_group *, e_surface)
	// function call : void (*const)(c_lights_view *, long, long, IDirect3DSurface9 *, IDirect3DSurface9 *, IDirect3DSurface9 *)
	// function call : void (*const)(float, float, bool, float, bool, char, bool)
	// function call : void (*const)(c_player_view *, char)
	// function call : char (*const)()
	// function call : void (*const)(long, short_rectangle2d *)
	// function call : bool (*const)()
	// function call : void (*const)(s_render_projection *, s_render_camera *, e_surface, e_surface, e_surface, e_surface, e_surface, e_surface, e_surface, e_surface, e_surface, e_surface, e_surface, e_surface)
	// function call : void (*const)(float, float, bool, float, bool, char, bool)
	// function call : void (*const)()
	// function call : void (*const)(c_player_view *)
	// function call : void (*const)(c_player_view *)
	// function call : void (*const)(c_player_view *)
	// function call : bool (*const)()
	// function call : char (*const)(char)
	// function call : void (*const)(long)
	// function call : void (*const)(bool)
	// function call : void (*const)(c_player_view *, char)
	// function call : void (*const)(bool)
	// function call : void (*const)(c_player_view *)
	// function call : bool (*const)()
	// function call : unsigned long (*const)()
	// function call : void (*const)(long, long)
	// function call : bool (*const)(unsigned long)
	// function call : void (*const)(bool)
	// function call : void (*const)(float, float, float)
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : void (*const)(unsigned long)
	// function call : void (*const)(s_render_camera *, s_render_projection *)
	// function call : void (*const)(float, float, bool, float, bool, char, bool)
	// function call : void (*const)(c_player_view *)
	// function call : bool (*const)()
	// function call : void (*const)(c_camera_fx_values *, s_render_projection *, s_render_camera *, s_screen_effect_settings *, long, s_observer_depth_of_field *, long)
	// function call : void (*const)()
	// function call : bool (*const)()
	// function call : void (*const)()
	// function call : void (*const)()
	// function call : void (*const)(float, float, float)
	// function call : void (*const)(long, c_player_view *)
	// function call : void (*const)(long, c_player_view *, float, float, float, long, long)
	// function call : e_surface (*const)()
	// function call : void (*const)(s_screen_effect_shader_sample_result *, char, e_surface, e_surface, real_rectangle2d *)
	// function call : void (*const)(unsigned long)
	// function call : void (*const)(unsigned long)
	// function call : void (*const)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *)
	// function call : e_surface (*const)()
	// function call : void (*const)(long, long, unsigned long, short_rectangle2d *, e_surface, long)
	// function call : void (*const)()
	// function call : void (*const)(unsigned long)
	// function call : e_surface (*const)()
	// function call : void (*const)(s_screen_effect_shader_sample_result *, char, e_surface, e_surface, real_rectangle2d *)
	// function call : void (*const)(long)
	// function call : void (*const)(long)
	// function call : bool (*const)()
	// function call : long (*const)(long)
	// function call : void (*const)()
	todo("implement");
	_sub_108E6C50(view);
}

_extern void _sub_108E80F0(c_player_view *, void *);
void c_player_view__render_lightmap_shadows_hook(c_player_view *_this, void *__savedreg) // 0x108E80F0
{
	// `anonymous-namespace'::c_player_view__render_lightmap_shadows_hook
	// static ...; // 0x108E81FC
	// static ...; // 0x108E81F4
	// c_player_view *_this;
	// void *__savedreg;
	// void (*const c_player_view__render_lightmap_shadows)(c_player_view *);
	// real_vector4d shadow_map_pixel_size;
	// float sm_ps;
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(c_player_view *)
	todo("implement");
	_sub_108E80F0(_this, __savedreg);
}

_extern void _sub_108EBB90(c_texture_camera_view *);
void c_texture_camera_view__render_hook(c_texture_camera_view *thisptr) // 0x108EBB90
{
	// `anonymous-namespace'::c_texture_camera_view__render_hook
	// static ...; // 0x108ED776
	// static ...; // 0x108ED76F
	// static ...; // 0x108ED766
	// static ...; // 0x108ED760
	// static ...; // 0x108ED759
	// static ...; // 0x108ED74B
	// static ...; // 0x108ED736
	// static ...; // 0x108ED71F
	// static ...; // 0x108ED712
	// static ...; // 0x108ED707
	// static ...; // 0x108ED6FD
	// static ...; // 0x108ED6E8
	// static ...; // 0x108ED6D4
	// static ...; // 0x108ED6C4
	// static ...; // 0x108ED6AF
	// static ...; // 0x108ED69D
	// static ...; // 0x108ED683
	// static ...; // 0x108ED677
	// static ...; // 0x108ED66A
	// static ...; // 0x108ED657
	// static ...; // 0x108ED645
	// static ...; // 0x108ED638
	// static ...; // 0x108ED530
	// static ...; // 0x108ED528
	// c_texture_camera_view *thisptr;
	// bool byte_19186F4;
	// s_screen_effect_shader_sample_result shader_sample_result;
	// void (*const c_texture_camera_view__copy_texture)(c_texture_camera_view *, c_enum<long,enum e_rasterizer_default_shader>, c_rasterizer_texture_ref, c_rasterizer_texture_ref, float, float, bool);
	// float contrast;
	// bool (*const bitmap_group_try_get_texture)(long, long, c_rasterizer_texture_ref *);
	// float dword_19186EC;
	// s_screen_effect_settings screen_effect;
	// float dword_19186F0;
	// void (*const s_color_grading_parameter__update)(s_camera_fx_color_grading_struct *, bool, char);
	// float dword_19186F8;
	// long width;
	// real_vector4d p_postprocess_contrast;
	// float *g_texture_camera_exposure;
	// long height;
	// c_camera_fx_settings *camera_fx;
	{
		// short_rectangle2d viewport;
		// long width;
		// long height;
	}
	{
		// c_render_surface *depth_surface;
		// IDirect3DSurface9 *accum_surface;
	}
	{
		// real_vector4d cg_blend_factor;
		// unsigned long *random_seed_address;
		// real_vector4d pixel_space_xform;
		// long noise_height;
		// float noise_random2;
		// c_rasterizer_texture_ref default_noise_texture_ref;
		// real_vector4d bloom_sampler_xform;
		// _D3DSURFACE_DESC accum_surface_desc;
		// unsigned long random_seed;
		// c_rasterizer_texture_ref dark_surface;
		// s_rasterizer_globals *const rasg;
		// real_vector4d tone_curve_constants;
		// float noise_random1;
		// long frame_index;
		// real_vector4d noise_params;
		// real_vector4d pixel_size;
		// real_vector4d intensity;
		// real_vector4d gamma_power_constant;
		// long noise_width;
		// real_vector4d noise_space_xform;
	}
	// function call : void (*const)(c_view *)
	// function call : void (*const)()
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : long (*const)(c_lights_view *, long)
	// function call : void (*const)(c_lights_view *, long)
	// function call : void (*const)()
	// function call : long (*const)(long, c_rasterizer_texture_ref, long, long)
	// function call : long (*const)(long, c_rasterizer_texture_ref, long, long)
	// function call : void (*const)(bool)
	// function call : e_surface (*const)(e_surface)
	// function call : bool (*const)(c_rasterizer_texture_ref *, long, long *, long *)
	// function call : void (*const)(short_rectangle2d *, float, float)
	// function call : void (*const)(long, __int32, float, unsigned char)
	// function call : void (*const)(unsigned long)
	// function call : void (*const)()
	// function call : void (*const)(long, long)
	// function call : void (*const)(long, long)
	// function call : void (*const)()
	// function call : long (*const)(long, c_rasterizer_texture_ref, long, long)
	// function call : void (*const)(c_enum<enum e_render_method_extern,long>, bool)
	// function call : void (*const)(c_enum<enum e_render_method_extern,long>, bool)
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : void (*const)(long, __int32, float, unsigned char)
	// function call : void (*const)(float, float, float)
	// function call : void (*const)()
	// function call : void (*const)(bool)
	// function call : void (*const)(s_simple_light *, long)
	// function call : void (*const)(bool)
	// function call : void (*const)(unsigned long)
	// function call : void (*const)()
	// function call : void (*const)(long, long)
	// function call : void (*const)()
	// function call : long (*const)(long, c_rasterizer_texture_ref, long, long)
	// function call : e_surface (*const)(e_surface)
	// function call : void (*const)(long, __int32, float, unsigned char)
	// function call : long (*const)(long)
	// function call : void (*const)(long, long)
	// function call : c_render_surface *(*const)(e_surface)
	// function call : IDirect3DSurface9 *(*const)(c_rasterizer_texture_ref *, long, long)
	// function call : void (*const)(c_lights_view *, long, long, IDirect3DSurface9 *, IDirect3DSurface9 *, IDirect3DSurface9 *)
	// function call : void (*const)(c_enum<enum e_render_method_extern,long>, bool)
	// function call : void (*const)(c_enum<enum e_render_method_extern,long>, bool)
	// function call : void (*const)(c_enum<enum e_render_method_extern,long>, bool)
	// function call : void (*const)(s_simple_light *, long)
	// function call : void (*const)(bool)
	// function call : void (*const)(long, long)
	// function call : void (*const)()
	// function call : void (*const)(bool)
	// function call : void (*const)(bool)
	// function call : void (*)(void *)
	// function call : bool (*const)(c_rasterizer_texture_ref *, long, long *, long *)
	// function call : void (*const)(long)
	// function call : void (*const)(long)
	// function call : void (*const)(short_rectangle2d *)
	// function call : long (*const)(long)
	// function call : void (*const)(long, long)
	// function call : void (*const)(c_texture_camera_view *, c_enum<long,enum e_rasterizer_default_shader>, c_rasterizer_texture_ref, c_rasterizer_texture_ref, float, float, bool)
	// function call : void (*const)(long)
	// function call : void (*const)(long, long)
	// function call : long (*const)(long, c_rasterizer_texture_ref, long, long)
	// function call : void (*const)(long, __int32, float, unsigned char)
	// function call : void (*const)(s_hue_saturation_control *, float, float, float, real_rgb_color const *, real_rgb_color const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(s_camera_fx_color_grading_struct *, bool, char)
	// function call : bool (*const)(long, long, long, long)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*const)(long, c_rasterizer_texture_ref)
	// function call : void (*)(s_rasterizer_globals *, c_rasterizer_texture_ref *, c_enum<enum e_rasterizer_default_bitmap,long>)
	// function call : void (*const)(long, c_rasterizer_texture_ref)
	// function call : void (*const)(long, c_rasterizer_texture_ref)
	// function call : void (*const)(long, c_rasterizer_texture_ref)
	// function call : HRESULT (unsigned long, IDirect3DBaseTexture9 *)
	// function call : void (*const)(long, long)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : HRESULT (unsigned long, IDirect3DBaseTexture9 *)
	// function call : void (*const)(long, long)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*)(s_rasterizer_globals *, c_rasterizer_texture_ref *, c_enum<enum e_rasterizer_default_bitmap,long>)
	// function call : void (*const)(long, c_rasterizer_texture_ref)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : bool (*const)(c_rasterizer_texture_ref *, long, long *, long *)
	// function call : IDirect3DSurface9 *(*const)(c_rasterizer_texture_ref *, long, long)
	// function call : HRESULT (_D3DSURFACE_DESC *)
	// function call : unsigned long *(*)()
	// function call : unsigned long *(*)()
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long)
	// function call : void (*const)(long, c_rasterizer_texture_ref)
	// function call : void (*const)(long, c_rasterizer_texture_ref)
	// function call : void (*const)(long, c_rasterizer_texture_ref)
	// function call : void (*const)(long, c_rasterizer_texture_ref)
	// function call : void (*const)(long, c_rasterizer_texture_ref)
	// function call : void (*const)(long, c_rasterizer_texture_ref)
	// function call : void (*const)(long, c_rasterizer_texture_ref)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*const)(c_texture_camera_view *, c_enum<long,enum e_rasterizer_default_shader>, c_rasterizer_texture_ref, c_rasterizer_texture_ref, float, float, bool)
	// function call : void (*const)(long, c_rasterizer_texture_ref)
	// function call : void (*const)()
	// function call : void (*const)()
	todo("implement");
	_sub_108EBB90(thisptr);
}

_extern void _sub_108E8270(c_player_view *, void *);
void c_player_view__render_static_lighting(c_player_view *_this, void *_savedreg) // 0x108E8270
{
	// `anonymous-namespace'::c_player_view__render_static_lighting
	// static ...; // 0x108E8704
	// static ...; // 0x108E86EC
	// static ...; // 0x108E86E4
	// c_player_view *_this;
	// void *_savedreg;
	// bool (*const sub_A84D50)();
	{
		// __int32 surface_width;
		// __int32 surface_height;
		// real_vector4d scale;
		// real_vector4d pixel_size;
	}
	// function call : void (*const)(c_player_view *)
	// function call : void (*const)(s_simple_light *, long)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : void (*const)(long, long)
	// function call : void (*const)(long)
	// function call : void (*const)(unsigned long)
	// function call : void (*const)()
	// function call : void (*const)(long, long)
	// function call : void (*const)(long)
	// function call : void (*const)(bool)
	// function call : void (*const)(long)
	// function call : bool (*const)(long, long, long, long)
	// function call : void (*const)(long, e_surface)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : long (*const)(long)
	// function call : long (*const)(long)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long)
	// function call : void (*const)(long)
	// function call : void (*const)(long)
	todo("implement");
	_sub_108E8270(_this, _savedreg);
}

_extern void _sub_108E5A10(void *, void *, float, float);
void c_lightmap_shadows_view__render_shadow_apply_call_hook(void *_this, void *_savedreg, float shadow_alpha, float quality_scale) // 0x108E5A10
{
	// `anonymous-namespace'::c_lightmap_shadows_view__render_shadow_apply_call_hook
	// float quality_scale;
	// void (*const c_lightmap_shadows_view__render_shadow_apply)(void *, float, float);
	// function call : void (*const)(void *, float, float)
	// function call : void (*const)(void *, float, float)
	todo("implement");
	_sub_108E5A10(_this, _savedreg, shadow_alpha, quality_scale);
}

_extern void _sub_108E5AF0(void *, void *, float, float, long, long);
void c_lightmap_shadows_view__submit_visibility_and_render_call_hook(void *_this, void *_savedreg, float shadow_alpha, float quality_scale, long object_index, long model_tag_index) // 0x108E5AF0
{
	// `anonymous-namespace'::c_lightmap_shadows_view__submit_visibility_and_render_call_hook
	// long model_tag_index;
	// void (*const c_lightmap_shadows_view__submit_visibility_and_render)(void *, float, float, __int32, long);
	// function call : void (*const)(void *, float, float, __int32, long)
	// function call : void (*const)(void *, float, float, __int32, long)
	todo("implement");
	_sub_108E5AF0(_this, _savedreg, shadow_alpha, quality_scale, object_index, model_tag_index);
}

_extern void _sub_108F08C0(long);
void rasterizer_wait_for_device_query_hook(long index) // 0x108F08C0
{
	// `anonymous-namespace'::rasterizer_wait_for_device_query_hook
	// long index;
	// bool *g_device_queries_issued;
	// IDirect3DQuery9 **g_device_queries;
	// unsigned long start_time;
	// long cycles;
	// function call : HRESULT (void *, unsigned long, unsigned long)
	todo("implement");
	_sub_108F08C0(index);
}

_extern void _sub_108E8840(e_primitive_type, unsigned long, void const *, unsigned long);
void c_rasterizer__draw_primitive_up_hook(e_primitive_type primitive_type, unsigned long primitive_count, void const *vertex_data, unsigned long stride) // 0x108E8840
{
	// `anonymous-namespace'::c_rasterizer__draw_primitive_up_hook
	// unsigned long stride;
	// void (*const c_rasterizer_shaders__clear_cached_vertex_stream)(long);
	// void (*const c_rasterizer_shaders__submit_cached_shader_constants)();
	// function call : void (*const)()
	// function call : void (*const)(long)
	// function call : HRESULT (_D3DPRIMITIVETYPE, unsigned __int32, unsigned __int32, unsigned __int32, void const *, _D3DFORMAT, void const *, unsigned __int32)
	// function call : HRESULT (_D3DPRIMITIVETYPE, unsigned __int32, void const *, unsigned __int32)
	todo("implement");
	_sub_108E8840(primitive_type, primitive_count, vertex_data, stride);
}

_extern void _sub_108E8A40(long, e_surface);
void c_rasterizer__end_frame_set_surface_as_texture_call_hook(long sampler, e_surface surface) // 0x108E8A40
{
	// `anonymous-namespace'::c_rasterizer__end_frame_set_surface_as_texture_call_hook
	// e_surface surface;
	// function call : void (*const)(long, e_surface)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	todo("implement");
	_sub_108E8A40(sampler, surface);
}

_extern void _sub_108E89C0(long, c_rasterizer_texture_ref);
void c_rasterizer__end_frame_set_sampler_texture_call_hook(long sampler, c_rasterizer_texture_ref ref) // 0x108E89C0
{
	// `anonymous-namespace'::c_rasterizer__end_frame_set_sampler_texture_call_hook
	// c_rasterizer_texture_ref ref;
	// function call : void (*const)(long, c_rasterizer_texture_ref)
	// function call : void (*const)(long, c_rasterizer_texture_ref)
	todo("implement");
	_sub_108E89C0(sampler, ref);
}

_extern bool _sub_108E8B60();
bool c_rasterizer__initialize_after_device_creation_or_reset_call_hook() // 0x108E8B60
{
	// `anonymous-namespace'::c_rasterizer__initialize_after_device_creation_or_reset_call_hook
	// procedure flags: nofpo
	// bool (*const initialize_after_device_creation_or_reset)();
	// bool result;
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_108E8B60();
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_enum<enum e_alpha_blend_mode,int>::operator!=(e_alpha_blend_mode const &) const;
template bool c_enum<enum e_alpha_blend_mode,int>::operator==(e_alpha_blend_mode const &) const;
template bool c_enum<enum e_bitmap_format,unsigned char>::operator!=(e_bitmap_format const &) const;
template bool c_enum<enum e_bitmap_format,unsigned char>::operator==(e_bitmap_format const &) const;
template bool c_enum<enum e_render_method_animated_parameter_type,long>::operator<=(e_render_method_animated_parameter_type const &) const;
template bool c_enum<enum e_render_method_animated_parameter_type,long>::operator==(e_render_method_animated_parameter_type const &) const;
template bool c_enum<enum e_render_method_animated_parameter_type,long>::operator>=(e_render_method_animated_parameter_type const &) const;
template bool c_enum<enum e_render_method_extern_mode,char>::operator!=(e_render_method_extern_mode const &) const;
template bool c_enum<enum e_render_method_extern_mode,char>::operator==(e_render_method_extern_mode const &) const;
template bool c_flags<enum e_part_flags,unsigned char>::test(e_part_flags) const;
template bool c_flags<enum e_render_method_postprocess_flags,long>::test(e_render_method_postprocess_flags) const;
template bool c_tag_block<s_bitmap_image>::try_get_element(__int32, s_bitmap_image **) const;
template bool c_tag_block<s_cubemap_reference_point>::try_get_element(__int32, s_cubemap_reference_point **) const;
template bool c_tag_block<s_decorator_grid>::try_get_element(__int32, s_decorator_grid **) const;
template bool c_tag_block<s_instance_water>::try_get_element(__int32, s_instance_water **) const;
template bool c_tag_block<s_render_method_template_constant_table>::try_get_element(__int32, s_render_method_template_constant_table **) const;
template bool c_tag_block<s_render_method_template_pass>::try_get_element(__int32, s_render_method_template_pass **) const;
template bool c_tag_block<s_render_method_template_routing_info>::try_get_element(__int32, s_render_method_template_routing_info **) const;
template bool c_tag_block<s_render_method_texture_constant>::try_get_element(__int32, s_render_method_texture_constant **) const;
template bool c_tag_block<s_render_model_instance_placement>::try_get_element(__int32, s_render_model_instance_placement **) const;
template bool c_tag_block<s_structure_cluster_cubemap_info>::try_get_element(__int32, s_structure_cluster_cubemap_info **) const;
template bool c_tag_block<s_structure_plane>::try_get_element(__int32, s_structure_plane **) const;
template bool c_tag_block<s_structure_surface_plane>::try_get_element(__int32, s_structure_surface_plane **) const;
template bool c_tag_block<s_subpart>::try_get_element(__int32, s_subpart **) const;
template bool c_tag_block<s_tag_block_index>::try_get_element(__int32, s_tag_block_index **) const;
template bool s_static_array<unsigned short,2048>::valid(__int32);
template bool s_static_array<unsigned short,4096>::valid(__int32);
template c_enum<enum e_entry_point,long>::operator long() const;
template c_enum<enum e_prt_vertex_type,char>::operator char() const;
template c_enum<enum e_prt_vertex_type,char>::operator enum e_prt_vertex_type() const;
template c_enum<enum e_rasterizer_default_bitmap,long>::c_enum(e_rasterizer_default_bitmap const &);
template c_enum<enum e_rasterizer_default_bitmap,long>::c_enum(long const &);
template c_enum<enum e_render_method_animated_parameter_type,long> c_enum<enum e_render_method_animated_parameter_type,long>::operator-(e_render_method_animated_parameter_type const &) const;
template c_enum<enum e_render_method_animated_parameter_type,long>::c_enum(long const &);
template c_enum<enum e_render_method_animated_parameter_type,long>::operator long() const;
template c_enum<enum e_render_method_extern,long>::c_enum(e_render_method_extern const &);
template c_enum<enum e_render_method_extern,long>::c_enum(long const &);
template c_enum<enum e_sorting_layer,char>::operator enum e_sorting_layer() const;
template c_enum<enum e_surface,long>::operator enum e_surface() const;
template c_enum<enum e_vertex_type,char>::operator char() const;
template c_enum<enum e_vertex_type,char>::operator enum e_vertex_type() const;
template c_enum<long,enum e_rasterizer_default_shader>::c_enum(e_rasterizer_default_shader const &);
template c_flags<enum e_instanced_geometry_flags,unsigned short> c_flags<enum e_instanced_geometry_flags,unsigned short>::operator&(__int32 const) const;
template c_flags<enum e_instanced_geometry_flags,unsigned short>::c_flags(unsigned short const &);
template c_flags<enum e_instanced_geometry_flags,unsigned short>::operator bool() const;
template c_flags<enum e_part_flags,unsigned char>::operator unsigned char() const;
template s_bitmap_image & c_tag_block<s_bitmap_image>::operator[](__int32);
template s_bitmap_image * c_tag_block<s_bitmap_image>::get_element(__int32) const;
template s_cubemap_reference_point & c_tag_block<s_cubemap_reference_point>::operator[](__int32);
template s_cubemap_reference_point * c_tag_block<s_cubemap_reference_point>::get_element(__int32) const;
template s_decorator_grid & c_tag_block<s_decorator_grid>::operator[](__int32);
template s_decorator_grid * c_tag_block<s_decorator_grid>::get_element(__int32) const;
template s_instance_water & c_tag_block<s_instance_water>::operator[](__int32);
template s_instance_water * c_tag_block<s_instance_water>::get_element(__int32) const;
template s_part const & c_tag_block<s_part>::operator[](__int32) const;
template s_render_method_postprocess_definition const & c_tag_block<s_render_method_postprocess_definition>::operator[](__int32) const;
template s_render_method_template_constant_table & c_tag_block<s_render_method_template_constant_table>::operator[](__int32);
template s_render_method_template_constant_table * c_tag_block<s_render_method_template_constant_table>::get_element(__int32) const;
template s_render_method_template_pass * c_tag_block<s_render_method_template_pass>::get_element(__int32) const;
template s_render_method_template_pass const & c_tag_block<s_render_method_template_pass>::operator[](__int32) const;
template s_render_method_template_routing_info * c_tag_block<s_render_method_template_routing_info>::get_element(__int32) const;
template s_render_method_template_routing_info const & c_tag_block<s_render_method_template_routing_info>::operator[](__int32) const;
template s_render_method_texture_constant * c_tag_block<s_render_method_texture_constant>::get_element(__int32) const;
template s_render_method_texture_constant const & c_tag_block<s_render_method_texture_constant>::operator[](__int32) const;
template s_render_model_instance_placement & c_tag_block<s_render_model_instance_placement>::operator[](__int32);
template s_render_model_instance_placement * c_tag_block<s_render_model_instance_placement>::get_element(__int32) const;
template s_structure_cluster_cubemap_info & c_tag_block<s_structure_cluster_cubemap_info>::operator[](__int32);
template s_structure_cluster_cubemap_info * c_tag_block<s_structure_cluster_cubemap_info>::get_element(__int32) const;
template s_structure_plane & c_tag_block<s_structure_plane>::operator[](__int32);
template s_structure_plane * c_tag_block<s_structure_plane>::get_element(__int32) const;
template s_structure_surface_plane & c_tag_block<s_structure_surface_plane>::operator[](__int32);
template s_structure_surface_plane * c_tag_block<s_structure_surface_plane>::get_element(__int32) const;
template s_subpart & c_tag_block<s_subpart>::operator[](__int32);
template s_subpart * c_tag_block<s_subpart>::get_element(__int32) const;
template s_tag_block_index * c_tag_block<s_tag_block_index>::get_element(__int32) const;
template s_tag_block_index const & c_tag_block<s_tag_block_index>::operator[](__int32) const;
template s_visible_cluster * s_simple_list<s_visible_cluster,1392>::list_iterator_new(long *, long);
template s_visible_cluster * s_simple_list<s_visible_cluster,1392>::list_iterator_next(long *);
template unsigned short & s_static_array<unsigned short,2048>::operator[](long);
template unsigned short & s_static_array<unsigned short,4096>::operator[](long);
