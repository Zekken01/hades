/* ---------- headers */

#include "hades/hades.h"

#include "Modules/ModuleDebug.hpp"

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
#include "Forge/ForgeAtmosphere.hpp"
#include "Forge/ForgeCameraFx.hpp"
#include "Forge/ForgeVisionRenderer.hpp"
#include "Forge/Geoemetry.hpp"
#include "Modules/ModuleGraphics.hpp"  // hades: added for 0x108EBB90
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
#include "Modules/ModuleCamera.hpp"

#include "Blam/Cache/StringIdCache.hpp"  // hades: added for 0x108F16F0

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

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const c_atmosphere_fog_interface_compute_cluster_weights = reinterpret_cast<void (*)(s_cluster_reference, real_point3d *)>(0x6724B0);
	static auto const c_atmosphere_fog_interface_populate_atmosphere_parameters = reinterpret_cast<void (*)(s_cluster_reference, s_weighted_atmosphere_parameters *)>(0x6739A0);
	static auto const c_cpu_gpu_synchronizer_wait_for_gpu_to_catch_up = reinterpret_cast<void (*)()>(0xA60020);
	static auto const c_decal_system_submit_all = reinterpret_cast<void (*)()>(0x6951B0);
	static auto const c_object_renderer_render_albedo = reinterpret_cast<void (*)(unsigned long)>(0xA78410);
	static auto const c_object_renderer_submit_and_render_sky = reinterpret_cast<void (*)(long, long)>(0xA79300);
	static auto const c_player_view_render_albedo_decals = reinterpret_cast<void (*)(long, long)>(0xA3A310);
	static auto const c_player_view_render_water = reinterpret_cast<void (*)()>(0xA3B470);
	static auto const c_player_view_setup_cinematic_clip_planes = reinterpret_cast<void (*)()>(0xA3BBA0);
	static auto const c_rasterizer_begin_high_quality_blend = reinterpret_cast<void (*)()>(0xA21350);
	static auto const c_rasterizer_clear = reinterpret_cast<void (*)(long, __int32, float, unsigned char)>(0xA213F0);
	static auto const c_rasterizer_draw_fullscreen_quad = reinterpret_cast<void (*)(long, long)>(0xA45EE0);
	static auto const c_rasterizer_draw_indexed_primitive = reinterpret_cast<void (*)(c_rasterizer_index_buffer const *, long, long, long, long)>(0xA28270);
	static auto const c_rasterizer_draw_indexed_primitive_2 = reinterpret_cast<void (*)(c_rasterizer_index_buffer *, long, long, long, long)>(0xA28270);
	static auto const c_rasterizer_draw_primitive_up = reinterpret_cast<void (*)(long, long, void *, long)>(0xA28330);
	static auto const c_rasterizer_end = reinterpret_cast<void (*)()>(0xA1F9B0);
	static auto const c_rasterizer_end_high_quality_blend = reinterpret_cast<void (*)()>(0xA21880);
	static auto const c_rasterizer_get_cull_mode = reinterpret_cast<long (*)()>(0xA22BA0);
	static auto const c_rasterizer_get_display_surface = reinterpret_cast<long (*)()>(0xA48770);
	static auto const c_rasterizer_get_is_tiling_enabled = reinterpret_cast<char (*)()>(0xA218D0);
	static auto const c_rasterizer_restore_last_scissor_rect = reinterpret_cast<void (*)()>(0xA202E0);
	static auto const c_rasterizer_restore_last_viewport = reinterpret_cast<void (*)()>(0xA202F0);
	static auto const c_rasterizer_set_alpha_blend_mode = reinterpret_cast<void (*)(long)>(0xA22D10);
	static auto const c_rasterizer_set_color_write_enable = reinterpret_cast<void (*)(long, long)>(0xA231E0);
	static auto const c_rasterizer_set_cull_mode = reinterpret_cast<void (*)(long)>(0xA232D0);
	static auto const c_rasterizer_set_depth_stencil_surface = reinterpret_cast<e_surface (*)(e_surface)>(0xA48CB0);
	static auto const c_rasterizer_set_explicit_shaders = reinterpret_cast<bool (*)(long, long, long, long)>(0xA23300);
	static auto const c_rasterizer_set_indices = reinterpret_cast<void (*)(long)>(0xA233C0);
	static auto const c_rasterizer_set_pixel_shader_constant = reinterpret_cast<void (*)(long, long, real_vector4d const *)>(0xA66270);
	static auto const c_rasterizer_set_pixel_shader_constant_bool = reinterpret_cast<void (*)(long, long, __int32 const *)>(0xA66370);
	static auto const c_rasterizer_set_render_target = reinterpret_cast<e_surface (*)(long, e_surface, long)>(0xA48E40);
	static auto const c_rasterizer_set_sampler_address_mode = reinterpret_cast<void (*)(long, c_enum<e_sampler_address_mode, long>, c_enum<e_sampler_address_mode, long>, c_enum<e_sampler_address_mode, long>)>(0xA23570);
	static auto const c_rasterizer_set_sampler_address_mode_2 = reinterpret_cast<void (*)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)>(0xA23570);
	static auto const c_rasterizer_set_sampler_filter_mode = reinterpret_cast<void (*)(long, c_enum<e_sampler_filter_mode, long>)>(0xA23660);
	static auto const c_rasterizer_set_sampler_filter_mode_2 = reinterpret_cast<void (*)(long, c_enum<enum e_sampler_filter_mode,long>)>(0xA23660);
	static auto const c_rasterizer_set_sampler_texture = reinterpret_cast<void (*)(long, c_rasterizer_texture_ref)>(0xA23810);
	static auto const c_rasterizer_set_sampler_texture_direct = reinterpret_cast<void (*)(long, long)>(0xA23530);
	static auto const c_rasterizer_set_scissor_rect = reinterpret_cast<void (*)(short_rectangle2d *)>(0xA239B0);
	static auto const c_rasterizer_set_stencil_mode = reinterpret_cast<void (*)(long)>(0xA23BA0);
	static auto const c_rasterizer_set_surface_as_texture = reinterpret_cast<void (*)(long, e_surface)>(0xA48F20);
	static auto const c_rasterizer_set_using_albedo_sampler = reinterpret_cast<void (*)(bool)>(0xA48FE0);
	static auto const c_rasterizer_set_vertex_shader_constant = reinterpret_cast<void (*)(long, long, real_vector4d const *)>(0xA66410);
	static auto const c_rasterizer_set_vertex_shader_constant_bool = reinterpret_cast<void (*)(long, long, __int32 const *)>(0xA66620);
	static auto const c_rasterizer_set_viewport = reinterpret_cast<void (*)(short_rectangle2d *, float, float)>(0xA49010);
	static auto const c_rasterizer_set_z_buffer_mode = reinterpret_cast<long (*)(long)>(0xA247E0);
	static auto const c_rasterizer_setup_occlusion_state = reinterpret_cast<void (*)()>(0xA24B30);
	static auto const c_rasterizer_setup_render_target_globals_with_exposure = reinterpret_cast<void (*)(float, float, float)>(0xA24B90);
	static auto const c_rasterizer_setup_targets_static_lighting = reinterpret_cast<void (*)(float, float, bool, float, bool, bool, bool)>(0xA252C0);
	static auto const c_rasterizer_setup_targets_static_lighting_alpha_blend = reinterpret_cast<void (*)(bool)>(0xA25400);
	static auto const c_render_globals_set_distortion_history = reinterpret_cast<void (*)(bool)>(0xA2A310);
	static auto const c_render_surfaces_interface_get_render_surface = reinterpret_cast<c_render_surface *(*)(e_surface)>(0x60F8B0);
	static auto const c_screen_postprocess_postprocess_player_view = reinterpret_cast<void (*)(c_camera_fx_values *, s_render_projection *, s_render_camera *, s_screen_effect_settings *, long, s_observer_depth_of_field *, long)>(0xA61770);
	static auto const c_screen_postprocess_postprocess_ssr = reinterpret_cast<void (*)(s_render_projection *, s_render_camera *, long, long, long, long, long, long, long, long, long, long, long, long)>(0xA61CD0);
	static auto const c_structure_renderer_render_albedo = reinterpret_cast<void (*)()>(0xA2F050);
	static auto const c_transparency_renderer_render = reinterpret_cast<void (*)(bool)>(0xA73640);
	static auto const c_transparency_renderer_sort = reinterpret_cast<void (*)()>(0xA73880);
	static auto const c_tron_effect_resolve_and_process_z_camera = reinterpret_cast<void (*)(long, short_rectangle2d *)>(0xA7B5F0);
	static auto const c_view_begin = reinterpret_cast<void (*)(c_view *)>(0xA289D0);
	static auto const c_view_end = reinterpret_cast<void (*)()>(0xA28B10);
	static auto const c_water_renderer_is_active_ripple_exist = reinterpret_cast<bool (*)()>(0xA362B0);
	static auto const c_water_renderer_ripple_apply = reinterpret_cast<void (*)()>(0xA37000);
	static auto const c_water_renderer_ripple_slope = reinterpret_cast<void (*)()>(0xA372B0);
	static auto const c_water_renderer_update_water_part_list = reinterpret_cast<bool (*)()>(0xA373F0);
	static auto const chud_draw_screen = reinterpret_cast<void (*)(long)>(0xA88DA0);
	static auto const chud_draw_screen_LDR = reinterpret_cast<void (*)(long)>(0xA88FE0);
	static auto const chud_draw_screen_saved_film = reinterpret_cast<void (*)(long)>(0xA89100);
	static auto const chud_draw_turbulence = reinterpret_cast<void (*)(long)>(0xA89250);
	static auto const chud_generate_damage_flash_texture = reinterpret_cast<bool (*)(long)>(0xA89440);
	static auto const cinematic_in_progress = reinterpret_cast<bool (*)()>(0x67D270);
	static auto const game_engine_render = reinterpret_cast<void (*)(long)>(0x6E4E50);
	static auto const game_engine_render_debug = reinterpret_cast<void (*)(long)>(0x6E4FE0);
	static auto const game_engine_render_fade_to_black = reinterpret_cast<void (*)(long)>(0x6E5040);
	static auto const game_engine_render_watermarks = reinterpret_cast<void (*)()>(0x6E5160);
	static auto const game_engine_suppress_render_scene = reinterpret_cast<char (*)(long)>(0x6E5510);
	static auto const get_distortion_visible = reinterpret_cast<bool (*)()>(0xA29580);
	static auto const get_global_camera_collection = reinterpret_cast<c_visibility_collection *(*)()>(0x686B90);
	static auto const interface_get_current_window_settings = reinterpret_cast<void (*)(long, long, short_rectangle2d *, long)>(0xA9FAF0);
	static auto const lens_flares_submit_occlusions = reinterpret_cast<void (*)(long, bool)>(0xA5AB30);
	static auto const pixel32_to_real_rgb_color = reinterpret_cast<real_rgb_color *(*)(unsigned long, real_rgb_color *)>(0x521300);
	static auto const player_effect_render = reinterpret_cast<void (*)(long)>(0x684B20);
	static auto const rasterizer_set_vertex_stream = reinterpret_cast<bool (*)(c_rasterizer_vertex_buffer const *)>(0xA5DB60);
	static auto const rasterizer_set_vertex_stream_2 = reinterpret_cast<bool (*)(c_rasterizer_vertex_buffer *)>(0xA5DB60);
	static auto const rasterizer_stipple_initialize = reinterpret_cast<void (*)()>(0xA7A930);
	static auto const rasterizer_stipple_set_fade_byte = reinterpret_cast<void (*)(long, long, long, long)>(0xA7AC20);
	static auto const render_debug_window_render = reinterpret_cast<void (*)(long)>(0xA29230);
	static auto const render_method_clear_externs = reinterpret_cast<void (*)()>(0xA3CA50);
	static auto const render_method_submit = reinterpret_cast<bool (*)(long, c_render_method const *, e_vertex_type, e_prt_vertex_type, e_entry_point, bool)>(0xA3CA60);
	static auto const render_method_submit_data = reinterpret_cast<void (*)(long, s_shader_extern_info const *)>(0xA3CC20);
	static auto const render_method_submit_single_extern = reinterpret_cast<void (*)(c_enum<enum e_render_method_extern,long>, bool)>(0xA3D200);
	static auto const render_method_submit_valid = reinterpret_cast<void (*)(bool)>(0xA3D260);
	static auto const render_screen_shaders = reinterpret_cast<void (*)(s_screen_effect_shader_sample_result *, bool, long, long, long)>(0x14E6F60);
	static auto const render_setup_window = reinterpret_cast<void (*)(s_render_camera *, s_render_projection *)>(0xA2A080);
	static auto const screenshot_allow_postprocess = reinterpret_cast<bool (*)()>(0x6101A0);
	static auto const screenshot_allow_ui_render = reinterpret_cast<bool (*)()>(0x6101C0);
	static auto const screenshot_in_progress = reinterpret_cast<bool (*)()>(0x610310);
	static auto const screenshot_sub_610260 = reinterpret_cast<bool (*)()>(0x610260);
	static auto const sub_14E56A0 = reinterpret_cast<void (*)(long, c_player_view *)>(0x14E56A0);
	static auto const user_interface_render = reinterpret_cast<void (*)(long, long, long, short_rectangle2d *, long, long)>(0xA849B0);
	static auto const vision_mode_render = reinterpret_cast<void (*)(long, c_player_view *, float, float, float, long, long)>(0x14E3EE0);
}

namespace Player { namespace PlayerEmblem { extern void set_emblem_customization_biped(long sampler, bool use_generic, bool screen_emblem); extern void set_emblem_texture(long sampler, long player_index, bool use_generic, bool screen_emblem); } }  // hades: added for 0x108F6D50
extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0x108F6D50

float distance_squared3d(real_point3d const *a, real_point3d const *b);  // hades: added for 0x108E4A80

extern long (*const global_structure_bsp_first_active_index_get)();  // hades: added for 0x108F0190

extern s_scenario_structure_bsp *(*const global_structure_bsp_get)(long);  // hades: added for 0x108E8D60
extern real_point3d *matrix4x3_transform_point(real_matrix4x3 const *matrix, real_point3d const *point, real_point3d *result);  // hades: added for 0x108E6520

static s_sorter<s_render_cluster_part, 2048> *const render_structure_cluster_sorter = reinterpret_cast<s_sorter<s_render_cluster_part, 2048> *>(0x19136D0);  // hades: added for 0x108EE6B0

namespace Patches { namespace Debug { extern void RenderPlayerView(); } }  // hades: added for 0x108F07D0
extern void screen_effect_sample(real_point3d const *position, real_vector3d const *forward, s_screen_effect_settings *settings, s_screen_effect_shader_sample_result *shader_sample, long user_index);  // hades: added for 0x108E6C50
extern unsigned long *(*get_local_random_seed_address)();  // hades: added for 0x108EBB90
extern void screen_effect_set_hud_alpha_scale(float scale);  // hades: added for 0x108E6C50

class c_rasterizer_LUT_control { public: static bool initialized(); static bool initialize_LUT_textures(); static void set_LUT_texture(long sampler); };  // hades: added for 0x108E8B60

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
namespace Patches { namespace RenderObject { bool GetPRTDisabled(); } }  // hades: added for 0x108F0A20
void matrix4x3_multiply(real_matrix4x3 const *a, real_matrix4x3 const *b, real_matrix4x3 *result);  // hades: added for 0x108E5BE0
bool depth_stencil_format_is_float(_D3DFORMAT format);
void c_surface__set_depth_stencil(e_surface surface);
void c_surface__set_depth_stencil_surface(IDirect3DSurface9 *surface);
void __fastcall c_first_person_view__override_projection(c_first_person_view *thisptr, void *unused, bool a2);
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
void __fastcall s_render_shield_parts__render_hook(s_render_shield_parts *thisptr, void *unused, s_visible_object *visible_object, char flags);
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
void __fastcall c_dynamic_cubemap_sample__search_for_cubemap_sample_in_cluster_hook(c_dynamic_cubemap_sample *thisptr, void *__formal, s_cluster_reference test_location, real_point3d *test_point, float tolerance);
float render_projection_sphere_diameter_in_pixels_hook(s_render_projection const *render_projection, real_point3d const *center, float radius);
void bink_playback_allocate_framebuffers_hook();
void __fastcall c_player_view__render_hook(c_player_view *view);
void __fastcall c_player_view__render_lightmap_shadows_hook(c_player_view *_this, void *__savedreg);
void __fastcall c_texture_camera_view__render_hook(c_texture_camera_view *thisptr);
void __fastcall c_player_view__render_static_lighting(c_player_view *_this, void *_savedreg);
void __fastcall c_lightmap_shadows_view__render_shadow_apply_call_hook(void *_this, void *_savedreg, float shadow_alpha, float quality_scale);
void __fastcall c_lightmap_shadows_view__submit_visibility_and_render_call_hook(void *_this, void *_savedreg, float shadow_alpha, float quality_scale, long object_index, long model_tag_index);
void rasterizer_wait_for_device_query_hook(long index);
void c_rasterizer__draw_primitive_up_hook(e_primitive_type primitive_type, unsigned long primitive_count, void const *vertex_data, unsigned long stride);
void c_rasterizer__end_frame_set_surface_as_texture_call_hook(long sampler, e_surface surface);
void c_rasterizer__end_frame_set_sampler_texture_call_hook(long sampler, c_rasterizer_texture_ref ref);
bool c_rasterizer__initialize_after_device_creation_or_reset_call_hook();

/* ---------- globals */

float c_player_view::render_debug_depth_render_alpha; // 0x11352F68
void (__thiscall *s_wind_definition::update)(s_wind_definition *, s_wind_values *); // 0x11352F74
s_wind_definition *(*s_wind_definition::get_wind_definition)(real_point3d *); // 0x11352F78
s_decorator_set *(*s_decorator_set::get)(long); // 0x11352F7C
long (__thiscall *s_decorator_set::get_explicit_shader_index)(s_decorator_set *); // 0x11352F80
unsigned long *c_render_method_data::m_change_colors; // 0x11352F34
void (__thiscall *c_rasterizer_globals::get_default_texture_rasterizer_texture_ref)(s_rasterizer_globals *, c_rasterizer_texture_ref *, c_enum<enum e_rasterizer_default_bitmap,long>); // 0x11352F3C
long *c_rasterizer::g_color_surfaces; // 0x11352F48
s_muffin_definition *(*s_muffin_definition::get)(long); // 0x11352F6C

/* ---------- private variables */

extern "C" { static __int32 *g_bink_frame_width; } // 0x11352EE0
extern "C" { static __int32 *g_bink_frame_height; } // 0x11352EE4

namespace hades_file_local
{
	namespace hades_file_local_render_patches { extern float &k_camera_field_of_view_default; } using namespace hades_file_local_render_patches; // 0x11352ED4
	extern s_extern_description const g_new_extern_descriptions[55]; // 0x11195C80
	extern s_wind_values &g_wind_values; // 0x11352EDC
	extern bool &g_invalidate_render_cache; // 0x11352ED8
	std::vector<int> customization_biped_index_array; // 0x124083B0
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

void render_patches_apply() // 0x108F1E10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_patches_apply@@YAXXZ");

	Hook(0x639960, c_player_view__render_hook).Apply();
	Hook(0x670950, c_texture_camera_view__render_hook).Apply();
	Hook(0x63CFFD, get_extern_constant_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x63D060, get_extern_constant_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x63D0F8, get_extern_constant_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x63D222, get_extern_constant_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x63C9A0, render_get_extern_volatility_level_hook).Apply();
	Hook(0x63CF00, render_method_submit_externs_hook).Apply();
	Hook(0x63D200, render_method_submit_single_extern_hook).Apply();
	Hook(0x63CDE1, render_method_submit_set_bsp_call_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x63E430, update_constants_hook).Apply();
	Hook(0x625AA0, rasterizer_get_z_planes_hook).Apply();
	Hook(0x628DA0, c_first_person_view__override_projection).Apply();
	Hook(0x648C70, c_surface__set_depth_stencil_surface).Apply();
	Hook(0x648CB0, c_surface__set_depth_stencil).Apply();
	Patch::NopFill(0xA399F4, 8);
	Hook(0x6399CB, observer_get_camera__call_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x636580, render_underwater_fog_hook).Apply();
	Hook(0x10E4169, sub_14E3A00_vision_call_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x10E583F, sub_14E3A00_vision_call_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x63C040, evaluate_function_hook).Apply();
	Hook(0x64DE9C, render_method_submit_particle_gpu_emitter_render_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x63A151, sub_610230__ssao_call_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x20473B, post_render_player_view_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x670CC0, c_player_view__render_lightmap_shadows_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x639BC3, c_player_view__render_lightmap_shadows_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x668E6D, c_lightmap_shadows_view__render_shadow_apply_call_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x668E32, c_lightmap_shadows_view__submit_visibility_and_render_call_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x6475E0, render_mesh_part_default_hook).Apply();
	Hook(0x62F0D0, c_structure_renderer__render_cluster_mesh_part_hook).Apply();
	Hook(0x62F8C0, c_structure_renderer__render_instance_mesh_part_hook).Apply();
	Hook(0x630290, c_structure_renderer__submit_visibility_hook).Apply();
	Hook(0x62F340, c_structure_renderer__render_decorators_hook).Apply();
	Hook(0x67A280, c_object_renderer__submit_object_mesh_parts_for_active_camo_hook).Apply();
	Hook(0x636660, c_water_renderer__render_water_part_hook).Apply();
	Hook(0x630990, c_water_renderer__update_water_structure_part_list_hook).Apply();
	Hook(0x653880, s_render_shield_parts__render_hook).Apply();
	Hook(0x6786B0, c_object_renderer__render_object_context_instances_hook).Apply();
	Hook(0x678940, c_object_renderer__render_object_context_mesh_part_hook).Apply();
	Hook(0x647820, render_mesh_part_no_material).Apply();
	Hook(0x350810, c_geometry_sampler__find_render_method_index_from_collision_hook).Apply();
	Hook(0x647430, part_is_renderable_hook).Apply();
	Hook(0x7C7320, muffins_render_opaque).Apply();
	Hook(0x1F3070, mesh_get_data_hook).Apply();
	Hook(0x679051, c_render_shield__render_object_internal_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Patch(0x654620, { 0x10 }).Apply();
	Hook(0x67A670, c_dynamic_cubemap_sample__search_for_cubemap_sample_in_cluster_hook).Apply();
	Hook(0x665E30, render_projection_sphere_diameter_in_pixels_hook).Apply();
	Hook(0x216250, bink_display_frame).Apply();
	Hook(0x216B62, bink_playback_allocate_framebuffers_hook).Apply();
	Patch(0x1292D88, { 0x9A, 0x99, 0x19, 0x3E }).Apply();
	Patch(0x1292D8C, { 0x9A, 0x99, 0x99, 0x3E }).Apply();
	Patch(0x1292D90, { 0x33, 0x33, 0xB3, 0x3E }).Apply();
	Hook(0x63A8C0, c_player_view__render_static_lighting).Apply();
	c_player_view::render_debug_depth_render_scale_r = 7.0f;
	c_player_view::render_debug_depth_render_scale_g = 7.0f;
	c_player_view::render_debug_depth_render_scale_b = 8.0f;
	Patch(0x62508C, { 0x90, 0x90, 0x8A, 0x45, 0x08, 0x84, 0xC0, 0x75, 0x09 }).Apply();
	Patch(0x6250A9, { 0xCC, 0x94, 0x6C, 0x00 }).Apply();
	Hook(0x660040, rasterizer_wait_for_device_query_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x628330, c_rasterizer__draw_primitive_up_hook).Apply();
	Hook(0x62165E, c_rasterizer__end_frame_set_surface_as_texture_call_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x621748, c_rasterizer__end_frame_set_sampler_texture_call_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x6203B9, c_rasterizer__initialize_after_device_creation_or_reset_call_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x6226B1, c_rasterizer__initialize_after_device_creation_or_reset_call_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x6227EE, c_rasterizer__initialize_after_device_creation_or_reset_call_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
}

void render_patches_set_customization_biped(std::vector<int> characterBipeds) // 0x108F5A80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_patches_set_customization_biped@@YAXV?$vector@HV?$allocator@H@std@@@std@@@Z");

	customization_biped_index_array = characterBipeds;
}

void render_patches_tick() // 0x108F5B20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_patches_tick@@YAXXZ");

	auto *settingsModule = &Utils::Singleton<Modules::ModuleSettings>::Instance();
	g_decorator_distance_scale = settingsModule->VarDecoratorDistance->ValueFloat;
	g_lod_distance_scale = settingsModule->VarLODDistance->ValueFloat;
}

/* ---------- private code */

void get_extern_constant_hook(long render_method_extern, real_vector4d *out_constant) // 0x108EFA30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_extern_constant_hook@@YAXJPAUreal_vector4d@@@Z");

	if (render_method_extern == 0x33)
	{
		c_view *view = ((c_view *(*)())0xA293B0)();
		if (!view)
			view = c_view_stack::get_player_view();
		float z_near = view->render_camera.z_near;
		float z_far = view->render_camera.z_far;
		out_constant->i = 1.0f / z_near;
		out_constant->j = -((z_far - z_near) / (z_near * z_far));
		out_constant->k = out_constant->i + out_constant->j;
		out_constant->w = 0.0f;
	}
	else if (render_method_extern == 0x34)
	{
		c_view *view = ((c_view *(*)())0xA293B0)();
		if (!view)
			view = c_view_stack::get_player_view();
		out_constant->i = view->rasterizer_camera.forward.i;
		out_constant->j = view->rasterizer_camera.forward.j;
		out_constant->k = view->rasterizer_camera.forward.k;
		out_constant->w = 0.0f;
	}
	else if (render_method_extern == 0x35)
	{
		long width = ((long (*)(long))0xA48810)(57);
		long height = ((long (*)(long))0xA487A0)(57);
		out_constant->i = 1.0f / width;
		out_constant->j = 1.0f / height;
		out_constant->k = 0.0f;
		out_constant->w = 0.0f;
	}
	else
	{
		((void (*)(c_enum<e_render_method_extern,long>, real_vector4d *))0xA3C3D0)(render_method_extern, out_constant);
	}
}

_inline long const render_get_extern_volatility_level_hook(long render_method_extern) // 0x108F09F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_get_extern_volatility_level_hook@@YA?BJJ@Z");

	return g_new_extern_descriptions[render_method_extern].m_volatility_level;
}

void submit_extern_texture_hook(void *device, long a2, long render_method_extern, long sampler) // 0x108F6D50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?submit_extern_texture_hook@@YAXPAXJJJ@Z");

	bool (*const game_is_ui_shell)() = reinterpret_cast<bool (*)()>(0x531E90);
	if (render_method_extern == 49)
	{
		if (c_render_method_data::m_context == -1)
		{
			s_rasterizer_globals *rasg = c_rasterizer_globals::get();
			c_rasterizer_texture_ref texture_ref(-1);
			c_rasterizer_globals::get_default_texture_rasterizer_texture_ref(rasg, &texture_ref, _default_bitmap_color_black_transparent);
			((void (*)(long, c_rasterizer_texture_ref))0xA23810)(sampler, texture_ref);
			return;
		}
		if (game_is_ui_shell())
		{
			for (unsigned __int32 i = 0; i < customization_biped_index_array.size(); i++)
			{
				if (c_render_method_data::m_context == customization_biped_index_array[i])
					::Player::PlayerEmblem::set_emblem_customization_biped(sampler, false, false);
			}
		}
		else
		{
			s_unit_data *unit_data = (s_unit_data *)object_try_and_get_and_verify_type(c_render_method_data::m_context, 0x2003);
			if (unit_data)
			{
				short player_index = -1;
				player_index = unit_data->player_index;
				if (player_index != -1 && player_index < 16)
				{
					::Player::PlayerEmblem::set_emblem_texture(sampler, player_index, false, false);
					return;
				}
				player_index = unit_data->last_weak_player_index;
				if (player_index != -1 && player_index < 16)
				{
					::Player::PlayerEmblem::set_emblem_texture(sampler, player_index, false, false);
					return;
				}
				s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_data->hologram_creator_weak_unit_index, 0x2003);
				if (unit)
				{
					player_index = unit->player_index;
					if (player_index != -1 && player_index < 16)
					{
						::Player::PlayerEmblem::set_emblem_texture(sampler, player_index, false, false);
						return;
					}
				}
			}
			::Player::PlayerEmblem::set_emblem_texture(sampler, -1, true, false);
		}
	}
	else if (render_method_extern == 54)
	{
		s_rasterizer_globals *rasg = c_rasterizer_globals::get();
		long index = 7;
		if (rasg->default_bitmaps.count > 14)
		{
			index = 14;
			((void (*)(long, c_enum<e_sampler_filter_mode, long>))0xA23660)(sampler, _filter_trilinear);
			((void (*)(long, c_enum<e_sampler_address_mode, long>, c_enum<e_sampler_address_mode, long>, c_enum<e_sampler_address_mode, long>))0xA23570)(sampler, _address_mode_clamp, _address_mode_clamp, _address_mode_clamp);
		}
		c_rasterizer_texture_ref texture_ref(-1);
		c_rasterizer_globals::get_default_texture_rasterizer_texture_ref(rasg, &texture_ref, index);
		((void (*)(long, c_rasterizer_texture_ref))0xA23810)(sampler, texture_ref);
	}
	else
	{
		((void (*)(void *, long, c_enum<e_render_method_extern, long>, long))0xA3DC90)(device, a2, render_method_extern, sampler);
	}
}

void render_method_submit_externs_hook(c_render_method const *render_method, c_enum<enum e_entry_point,long> entry_point, long volatility, bool ignore_real_volatility) // 0x108F1310
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_method_submit_externs_hook@@YAXPBVc_render_method@@V?$c_enum@W4e_entry_point@@J@@J_N@Z");

	c_render_method_template const *rmt2 = c_render_method_template::get((*reinterpret_cast<c_tag_block<s_render_method_postprocess_definition> const *>(reinterpret_cast<char const *>(render_method) + 0x28))[0].render_method_template.index);
	s_render_method_template_pass const *pass = &rmt2->passes[rmt2->entry_points[(long)entry_point].get_offset()];
	for (__int32 i = 0; i < pass->extern_bitmaps.get_count(); i++)
	{
		s_render_method_template_routing_info const *routing_info = &rmt2->routing_info[pass->extern_bitmaps.get_offset() + i];
		if (volatility == render_get_extern_volatility_level_hook(routing_info->source_index))
		{
			if (g_invalidate_render_cache)
				((void (*)(long))0xA22A90)(routing_info->destination_index);
			submit_extern_texture_hook(nullptr, 0, routing_info->source_index, routing_info->destination_index);
		}
	}
	for (__int32 i = 0; i < pass->extern_pixel_real_constants.get_count(); i++)
	{
		s_render_method_template_routing_info const *routing_info = &rmt2->routing_info[pass->extern_pixel_real_constants.get_offset() + i];
		if (ignore_real_volatility || volatility == render_get_extern_volatility_level_hook(routing_info->source_index))
		{
			real_vector4d extern_constant;
			get_extern_constant_hook(routing_info->source_index, &extern_constant);
			((void (*)(long, long, real_vector4d const *))0xA66270)(routing_info->destination_index, 1, &extern_constant);
		}
	}
	for (__int32 i = 0; i < pass->extern_vertex_real_constants.get_count(); i++)
	{
		s_render_method_template_routing_info const *routing_info = &rmt2->routing_info[pass->extern_vertex_real_constants.get_offset() + i];
		if (ignore_real_volatility || volatility == render_get_extern_volatility_level_hook(routing_info->source_index))
		{
			real_vector4d extern_constant;
			get_extern_constant_hook(routing_info->source_index, &extern_constant);
			((void (*)(long, long, real_vector4d const *))0xA66410)(routing_info->destination_index, 1, &extern_constant);
		}
	}
}

void render_method_submit_single_extern_hook(long render_method_extern, bool a2) // 0x108F1CE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_method_submit_single_extern_hook@@YAXJ_N@Z");

	s_extern_description const *const extern_desc = get_extern_description(render_method_extern);
	if (!a2 && extern_desc->unknown_0C)
	{
		real_vector4d constant;

		get_extern_constant_hook(render_method_extern, &constant);

		if (extern_desc->m_vertex_shader)
		{
			((void(__cdecl *)(long, long, real_vector4d const *))0xa66270)(extern_desc->m_register, 1, &constant);
		}

		((void(__cdecl *)(long, long, real_vector4d const *))0xa66410)(extern_desc->m_register, 1, &constant);
	}
}

void render_method_submit_set_bsp_call_hook(long lightmap_bsp_data_handle) // 0x108F1B70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_method_submit_set_bsp_call_hook@@YAXJ@Z");

	for (__int32 i = 0; i < 55; i++)
	{
		s_extern_description const *const extern_desc = get_extern_description(i);

		if (extern_desc->m_volatility_level == 2 && extern_desc->unknown_0C)
		{
			real_vector4d constant;

			get_extern_constant_hook(i, &constant);

			if (extern_desc->m_vertex_shader)
			{
				((void(__cdecl *)(long, long, real_vector4d const *))0xa66270)(extern_desc->m_register, 1, &constant);
			}

			((void(__cdecl *)(long, long, real_vector4d const *))0xa66410)(extern_desc->m_register, 1, &constant);
		}
	}

	long *g_lightmap_bsp_data_handle = (long *)0x191489c;

	*g_lightmap_bsp_data_handle = lightmap_bsp_data_handle;
}

float evaluate_function_hook(long rm_index, s_render_method_animated_parameter *function) // 0x108EEA20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?evaluate_function_hook@@YAMJPAUs_render_method_animated_parameter@@@Z");

	void *(*const scenario_interpolator_get)(unsigned long) = reinterpret_cast<void *(*)(unsigned long)>(0x688850);
	bool (*const sub_687DE0)(void *) = reinterpret_cast<bool (*)(void *)>(0x687DE0);
	float (*const sub_687B50)(void *, long) = reinterpret_cast<float (*)(void *, long)>(0x687B50);
	float (*const sub_687D80)(void *, long) = reinterpret_cast<float (*)(void *, long)>(0x687D80);
	float (*const m_context_interface)(long, long, long) = *reinterpret_cast<float (**)(long, long, long)>(0x50FB610);
	bool is_unique_id = function->input_name == 0x2C2;
	bool is_scnr_interpolator = function->input_name > 0x2C2 && function->input_name < 0x2C7;
	float scalar = 0.0f;
	if (!m_context_interface || !function->input_name && !function->range_name || is_unique_id || is_scnr_interpolator)
	{
		float sec_elapsed = ((float (*)())0x564E60)();
		float scalar = sec_elapsed / function->time_period;
		if (is_unique_id)
		{
			float unique_id = (c_render_method_data::m_context & 0xFFF) * 1.37317f;
			if (((char (__thiscall *)(void *))0x949FC0)(&function->function) == 3)
				scalar = (sec_elapsed + unique_id) / function->time_period;
			else
				scalar = fmod(unique_id, 1.0f);
			return ((float (__thiscall *)(void *, float, float))0x949940)(&function->function, scalar, 0.0f);
		}
		else if (is_scnr_interpolator)
		{
			void *interpolator_block = scenario_interpolator_get(function->input_name - 0x2C3);
			if (sub_687DE0(interpolator_block))
				scalar = sub_687B50(interpolator_block, 1);
			else
				scalar = sub_687D80(interpolator_block, 1);
			return ((float (__thiscall *)(void *, float, float))0x949940)(&function->function, scalar, 0.0f);
		}
		if (((char (__thiscall *)(void *))0x949FC0)(&function->function) != 3)
			scalar = fmod(scalar, 1.0f);
		return ((float (__thiscall *)(void *, float, float))0x949940)(&function->function, scalar, 0.0f);
	}
	float scalar_output = m_context_interface(c_render_method_data::m_context, function->input_name, rm_index);
	float range_output = m_context_interface(c_render_method_data::m_context, function->range_name, rm_index);
	return ((float (__thiscall *)(void *, float, float))0x949940)(&function->function, scalar_output, range_output);
}

void update_constants_hook(long render_method_index, real_vector4d *source, s_destination_info *destination_info, long *destination_count, s_tag_block_index *routing_index, c_tag_block<s_render_method_routing_info> *routing_block, c_tag_block<s_render_method_animated_parameter> *functions_block) // 0x108F77F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update_constants_hook@@YAXJPAUreal_vector4d@@PAUs_destination_info@@PAJPAVs_tag_block_index@@PAV?$c_tag_block@Us_render_method_routing_info@@@@PAV?$c_tag_block@Us_render_method_animated_parameter@@@@@Z");

	float (*const evaluate_function)(long, s_render_method_animated_parameter const *) = reinterpret_cast<float (*)(long, s_render_method_animated_parameter const *)>(0xA3C040);
	void (__thiscall *const c_function_definition__map_to_color_range_legacy)(s_tag_data const *, float, real_rgb_color *) = reinterpret_cast<void (__thiscall *)(s_tag_data const *, float, real_rgb_color *)>(0x94A530);
	float (__thiscall *const c_function_definition__map_to_output_range_legacy)(s_tag_data const *, float) = reinterpret_cast<float (__thiscall *)(s_tag_data const *, float)>(0x94A580);
	s_render_method_routing_info const *routing_info = (s_render_method_routing_info const *)routing_block->address;
	s_render_method_animated_parameter const *functions = (s_render_method_animated_parameter const *)functions_block->address;
	*destination_count = 0;
	real_rgb_color out_colour = {};
	__int32 const offset = routing_index->get_offset();
	for (__int32 i = offset; i < offset + routing_index->get_count(); i++)
	{
		s_render_method_routing_info const *route = &routing_info[i];
		s_render_method_animated_parameter const *function = &functions[route->animated_parameter_index];
		if (function->type >= _animated_parameter_type_change_color_primary && function->type <= _animated_parameter_type_change_color_quinary)
		{
			long cc_index = function->type - _animated_parameter_type_change_color_primary;
			eldorado::pixel32_to_real_rgb_color(c_render_method_data::m_change_colors[cc_index], &out_colour);
			source[routing_info[i].source_index].i = out_colour.red;
			source[routing_info[i].source_index].j = out_colour.green;
			source[routing_info[i].source_index].k = out_colour.blue;
		}
		else
		{
			float function_result = evaluate_function(render_method_index, function);
			if (function->type == _animated_parameter_type_color)
			{
				c_function_definition__map_to_color_range_legacy(&function->function, function_result, &out_colour);
				source[routing_info[i].source_index].i = out_colour.red;
				source[routing_info[i].source_index].j = out_colour.green;
				source[routing_info[i].source_index].k = out_colour.blue;
			}
			else
			{
				float mapped_result = c_function_definition__map_to_output_range_legacy(&function->function, function_result);
				switch ((long)function->type)
				{
				case 0:
				case 3:
					source[routing_info[i].source_index].i = mapped_result;
					break;
				case 2:
					source[routing_info[i].source_index].j = mapped_result;
					source[routing_info[i].source_index].i = mapped_result;
					break;
				case 4:
					source[routing_info[i].source_index].j = mapped_result;
					break;
				case 5:
					source[routing_info[i].source_index].k = mapped_result;
					break;
				case 6:
				case 8:
					source[routing_info[i].source_index].w = mapped_result;
					break;
				}
			}
		}
		long count = *destination_count;
		if (count <= 0)
		{
			destination_info[count].destination_index = routing_info[i].destination_index;
			destination_info[count].source_index = routing_info[i].source_index;
			(*destination_count)++;
		}
		else
		{
			__int32 in = 0;
			while (destination_info[in].source_index != routing_info[i].source_index || destination_info[in].destination_index != routing_info[i].destination_index)
			{
				if (++in >= count)
				{
					destination_info[count].destination_index = routing_info[i].destination_index;
					destination_info[count].source_index = routing_info[i].source_index;
					(*destination_count)++;
					break;
				}
			}
		}
	}
}

bool z_buffer_fix_enabled() // 0x108F7F10
{

	return Modules::ModuleDebug::Instance().VarZBuffTest->ValueInt != 0;
}

void rasterizer_get_z_planes_hook(float *near_clip, float *far_clip) // 0x108F0830
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?rasterizer_get_z_planes_hook@@YAXPAM0@Z");

	if (z_buffer_fix_enabled())
	{
		*near_clip = *(float *)0x191068c;
		*far_clip = *(float *)0x1910690;
	}
	else
	{
		*near_clip = *(float *)0x191068c * 10.0f;
		*far_clip = *(float *)0x1910690;
	}
}

bool depth_stencil_format_is_float(_D3DFORMAT format) // 0x108EE9A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?depth_stencil_format_is_float@@YA_NW4_D3DFORMAT@@@Z");

	switch (format)
	{
	case 0x52:
	case 0x53:
		return true;
	case 0x4B:
		return z_buffer_fix_enabled();
	default:
		return false;
	}
}

void c_surface__set_depth_stencil(e_surface surface) // 0x108EB8D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_surface__set_depth_stencil@@YAXW4e_surface@@@Z");

	IDirect3DDevice9Ex *device = c_rasterizer::get_device();
	IDirect3D9Ex *d3d9ex = c_rasterizer::get_direct3d();
	c_rasterizer::g_depth_stencil_surface = surface;
	c_render_surface *render_surface = &((c_surface_group *)0x510D8D0)[surface].surfaces[0];
	if (surface == 0)
	{
		c_rasterizer::m_use_floating_point_z_buffer = false;
		device->SetDepthStencilSurface(render_surface->m_surface);
	}
	if (c_rasterizer::g_color_surfaces[0] && surface != 3)
	{
		c_render_surface *color_render_surface = &((c_surface_group *)0x510D8D0)[c_rasterizer::g_color_surfaces[0]].surfaces[0];
		d3d9ex->CheckDeviceFormatConversion(0, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, color_render_surface->m_desc.depth_stencil_format);
	}
	c_rasterizer::m_use_floating_point_z_buffer = depth_stencil_format_is_float(render_surface->m_desc.depth_stencil_format);
	device->SetDepthStencilSurface(render_surface->m_surface);
}

void c_surface__set_depth_stencil_surface(IDirect3DSurface9 *surface) // 0x108EBA70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_surface__set_depth_stencil_surface@@YAXPAUIDirect3DSurface9@@@Z");

	IDirect3DDevice9Ex *device = c_rasterizer::get_device();
	_D3DSURFACE_DESC surface_desc;
	surface->GetDesc(&surface_desc);
	c_rasterizer::m_use_floating_point_z_buffer = depth_stencil_format_is_float(surface_desc.Format);
	device->SetDepthStencilSurface(surface);
}

void __fastcall c_first_person_view__override_projection(c_first_person_view *thisptr, void *unused, bool a2) // 0x108E4F90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_first_person_view__override_projection@@YIXPAUc_first_person_view@@PAX_N@Z");

	float (*const cortana_effect_get_fov_scale)() = reinterpret_cast<float (*)()>(0xABEA20);
	float (*const sub_A8E700)() = reinterpret_cast<float (*)()>(0xA8E700);
	float c_first_person_view__m_fov_scale = *reinterpret_cast<float *>(0x1913434);
	float c_first_person_view__m_z_far_scale = *reinterpret_cast<float *>(0x1913470);
	memcpy(&thisptr->rasterizer_camera, thisptr->camera, sizeof(thisptr->rasterizer_camera));
	__int32 width = thisptr->rasterizer_camera.window_pixel_bounds.x1 - thisptr->rasterizer_camera.window_pixel_bounds.x0;
	__int32 height = thisptr->rasterizer_camera.window_pixel_bounds.y1 - thisptr->rasterizer_camera.window_pixel_bounds.y0;
	float aspect_ratio = (float)width / (float)height;
	bool use_view_offset_scaling = Utils::Singleton<Modules::ModuleCamera>::Instance().VarOldViewOffsetScale->ValueInt == 0;
	if (use_view_offset_scaling)
	{
		float const k_magic_halo3_shipped_ratio = 0.6908f;
		float const fov_scale = k_camera_field_of_view_default / 1.2217305f * k_magic_halo3_shipped_ratio;
		thisptr->rasterizer_camera.vertical_field_of_view *= fov_scale / fmaxf(thisptr->rasterizer_camera.horizontal_field_of_view, 0.0001f);
	}
	else if ((float)thisptr->rasterizer_camera.window_pixel_bounds.y1 - (float)thisptr->rasterizer_camera.window_pixel_bounds.y0 <= 0.0001f || aspect_ratio <= 1.8f)
	{
		thisptr->rasterizer_camera.vertical_field_of_view *= c_first_person_view__m_fov_scale;
	}
	else if (thisptr->rasterizer_camera.window_pixel_bounds.x0 <= 0)
	{
		thisptr->rasterizer_camera.vertical_field_of_view *= 0.73f;
	}
	else
	{
		thisptr->rasterizer_camera.vertical_field_of_view *= 0.7f;
	}
	thisptr->render_camera.vertical_field_of_view /= fmaxf(cortana_effect_get_fov_scale() * sub_A8E700(), 0.0001f);
	if (a2)
	{
		if (z_buffer_fix_enabled())
		{
			float z_near_scale = 1.0f;
			if (!use_view_offset_scaling)
				z_near_scale = (thisptr->rasterizer_camera.horizontal_field_of_view - 0.68687505f) * 2.038216f * -0.39999998f + 1.0f;
			if (aspect_ratio <= 1.8f)
				z_near_scale *= 3.2f;
			else
				z_near_scale *= 2.4f;
			if (!use_view_offset_scaling)
				z_near_scale = fmaxf(z_near_scale, 1.0f);
			thisptr->rasterizer_camera.z_near *= z_near_scale;
		}
		thisptr->rasterizer_camera.z_far *= c_first_person_view__m_z_far_scale;
	}
	real_rectangle2d frustum_bounds;
	((void (*)(s_render_camera *, real_rectangle2d *))0xA64A50)(&thisptr->rasterizer_camera, &frustum_bounds);
	((void (*)(s_render_camera *, real_rectangle2d *, s_render_projection *, float))0xA64140)(&thisptr->rasterizer_camera, &frustum_bounds, &thisptr->render_projection, 0.0f);
	((void (*)(s_render_camera *, s_render_projection *))0xA2A080)(&thisptr->rasterizer_camera, &thisptr->render_projection);
}

s_observer_result *observer_get_camera__call_hook(long output_user_index) // 0x108F0600
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?observer_get_camera__call_hook@@YAPAUs_observer_result@@J@Z");

	s_observer_result *observer_camera = ((s_observer_result *(__cdecl *)(long))0x6127c0)(output_user_index);
	float fov_rad = Modules::ModuleCamera::Instance().VarCameraFov->ValueFloat * 0.017453292f;
	float horizontal_fov = fmax(fov_rad / 1.3962634f, 0.000099999997f);

	g_particle_hack_near_fade_scale = 1.0f / horizontal_fov;

	return observer_camera;
}

void post_render_player_view_hook() // 0x108F07D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?post_render_player_view_hook@@YAXXZ");

	void (*const c_view__end)() = reinterpret_cast<void (*)()>(0xA28B10);
	c_view__end();
	Patches::Debug::RenderPlayerView();
}

void render_underwater_fog_hook() // 0x108F5D40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_underwater_fog_hook@@YAXXZ");

	unsigned long *g_game_resolution = (unsigned long *)0x19106C0;
	long &g_render_underwater_fog = *(long *)0x50FAAEC;
	if (g_render_underwater_fog)
	{
		eldorado::c_rasterizer_set_z_buffer_mode(2);
		eldorado::c_rasterizer_set_cull_mode(1);
		eldorado::c_rasterizer_set_color_write_enable(0, 15);
		if (eldorado::c_rasterizer_set_explicit_shaders(0x3A, 7, 0, 13))
		{
			eldorado::c_rasterizer_set_pixel_shader_constant(0xD5, 4, (real_vector4d const *)0x50FB328);
			eldorado::c_rasterizer_set_pixel_shader_constant(0xDA, 1, (real_vector4d const *)0x2446520);
			eldorado::c_rasterizer_set_pixel_shader_constant(0xDB, 1, (real_vector4d const *)0x50FB3C8);
			eldorado::c_rasterizer_set_pixel_shader_constant(0xDC, 1, (real_vector4d const *)0x50FB324);
			eldorado::c_rasterizer_set_pixel_shader_constant(0xDD, 1, (real_vector4d const *)0x50FB3A8);
			real_vector4d ps_screen_constants = {};
			ps_screen_constants.i = 1.0f / g_game_resolution[0];
			ps_screen_constants.j = 1.0f / g_game_resolution[1];
			ps_screen_constants.k = ps_screen_constants.i / 2.0f;
			ps_screen_constants.w = ps_screen_constants.j / 2.0f;
			eldorado::c_rasterizer_set_pixel_shader_constant(0xDE, 1, &ps_screen_constants);
			float z_near;
			float z_far;
			rasterizer_get_z_planes_hook(&z_near, &z_far);
			real_vector4d k_ps_water_view_depth_constant = {};
			k_ps_water_view_depth_constant.i = -(z_far / (z_far - z_near) * z_near);
			k_ps_water_view_depth_constant.j = z_far / (z_far - z_near);
			k_ps_water_view_depth_constant.k = 0.0f;
			k_ps_water_view_depth_constant.w = 0.0f;
			eldorado::c_rasterizer_set_pixel_shader_constant(0xD9, 1, &k_ps_water_view_depth_constant);
			eldorado::c_rasterizer_set_surface_as_texture(0, (e_surface)13);
			eldorado::c_rasterizer_set_sampler_address_mode(0, _address_mode_mirror, _address_mode_mirror, _address_mode_mirror);
			eldorado::c_rasterizer_set_sampler_filter_mode(0, _filter_bilinear);
			eldorado::c_rasterizer_set_surface_as_texture(1, (e_surface)23);
			eldorado::c_rasterizer_set_sampler_address_mode(1, _address_mode_mirror, _address_mode_mirror, _address_mode_mirror);
			eldorado::c_rasterizer_set_sampler_filter_mode(1, _filter_bilinear);
			s_screen_vertex vertices[4] = {};
			vertices[0].position = { -1.0f, 1.0f };
			vertices[1].position = { 1.0f, 1.0f };
			vertices[2].position = { -1.0f, -1.0f };
			vertices[3].position = { 1.0f, -1.0f };
			vertices[0].texcoord = { 0.0f + ps_screen_constants.k, 0.0f + ps_screen_constants.w };
			vertices[1].texcoord = { 1.0f + ps_screen_constants.k, 0.0f + ps_screen_constants.w };
			vertices[2].texcoord = { 0.0f + ps_screen_constants.k, 1.0f + ps_screen_constants.w };
			vertices[3].texcoord = { 1.0f + ps_screen_constants.k, 1.0f + ps_screen_constants.w };
			vertices[0].color = 0;
			vertices[1].color = 0;
			vertices[2].color = 0;
			vertices[3].color = 0;
			eldorado::c_rasterizer_set_indices(0);
			eldorado::c_rasterizer_draw_primitive_up(5, 2, vertices, sizeof(s_screen_vertex));
		}
	}
}

void sub_14E3A00_vision_call_hook(s_render_projection *render_proj, float *proj_matrix, s_render_projection *out_render_proj, float *out_proj_matrix) // 0x108F6A00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sub_14E3A00_vision_call_hook@@YAXPAUs_render_projection@@PAM01@Z");

	static bool (*const render_camera_build_viewport_frustum_bounds)(s_render_camera *, real_rectangle2d *) = reinterpret_cast<bool (*)(s_render_camera *, real_rectangle2d *)>(0xA64A50);
	static void (*const render_camera_build_projection)(s_render_camera *, real_rectangle2d *, s_render_projection *, float) = reinterpret_cast<void (*)(s_render_camera *, real_rectangle2d *, s_render_projection *, float)>(0xA64140);
	static long (*const rasterizer_get_surface_width)(long) = reinterpret_cast<long (*)(long)>(0xA48810);
	static long (*const rasterizer_get_surface_height)(long) = reinterpret_cast<long (*)(long)>(0xA487A0);
	static void (*const rasterizer_set_pixel_shader_constant)(long, long, real_vector4d const *) = reinterpret_cast<void (*)(long, long, real_vector4d const *)>(0xA66270);
	void (*const sub_14E3A00)(s_render_projection *, float *, s_render_projection *, float *) = reinterpret_cast<void (*)(s_render_projection *, float *, s_render_projection *, float *)>(0x14E3A00);
	bool cached_use_fp_z = c_rasterizer::m_use_floating_point_z_buffer;
	c_rasterizer::m_use_floating_point_z_buffer = false;
	c_player_view *x_current_player_view = c_player_view::get_current();
	real_rectangle2d bounds;
	render_camera_build_viewport_frustum_bounds(&x_current_player_view->render_camera, &bounds);
	s_render_projection new_render_proj;
	render_camera_build_projection(&x_current_player_view->render_camera, &bounds, &new_render_proj, 0.0f);
	sub_14E3A00(&new_render_proj, &new_render_proj.projection_matrix[0][0], out_render_proj, out_proj_matrix);
	real_vector4d zbuf_params = {};
	zbuf_params.i = new_render_proj.projection_matrix[3][2];
	zbuf_params.j = -new_render_proj.projection_matrix[2][2];
	zbuf_params.k = 1.0f / rasterizer_get_surface_width(23);
	zbuf_params.w = 1.0f / rasterizer_get_surface_height(23);
	rasterizer_set_pixel_shader_constant(121, 1, &zbuf_params);
	c_rasterizer::m_use_floating_point_z_buffer = cached_use_fp_z;
}

void render_mesh_part_default_hook(s_render_geometry *geometry, s_mesh *mesh, s_part *part, e_entry_point entry_point, unsigned long *subpart_visibility, s_geometry_material *materials) // 0x108F0A20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_mesh_part_default_hook@@YAXPAUs_render_geometry@@PAUs_mesh@@PAUs_part@@W4e_entry_point@@PAKPAUs_geometry_material@@@Z");

	bool (*const player_reading_terminal)() = (bool (*)())0x53B570;
	c_rasterizer_index_buffer *(*const render_geometry_get_index_buffer)(s_render_geometry *, long) = (c_rasterizer_index_buffer *(*)(s_render_geometry *, long))0x78C870;
	bool (*const render_method_submit)(long, c_render_method *, e_vertex_type, e_prt_vertex_type, e_entry_point, bool) = (bool (*)(long, c_render_method *, e_vertex_type, e_prt_vertex_type, e_entry_point, bool))0xA3CA60;
	long (*const global_preferenced_get_lighting_quality)() = (long (*)())0x50B890;
	c_rasterizer_index_buffer *index_buffer = render_geometry_get_index_buffer(geometry, mesh->index_buffer_indices[0]);
	c_rasterizer_vertex_buffer *vertex_buffer = ((c_rasterizer_vertex_buffer *(*const)(s_render_geometry *, s_mesh *, e_vertex_buffer_usage))0x78C750)(geometry, mesh, (e_vertex_buffer_usage)0);
	eldorado::rasterizer_set_vertex_stream(vertex_buffer);
	c_rasterizer_vertex_buffer *lighting_buffer = nullptr;
	if (mesh->vertex_buffer_indices[2] != -1)
		lighting_buffer = ((c_rasterizer_vertex_buffer *(*const)(s_render_geometry *, s_mesh *, e_vertex_buffer_usage))0x78C750)(geometry, mesh, (e_vertex_buffer_usage)2);
	else if ((entry_point == _entry_static_per_pixel || entry_point == _entry_lightmap_debug_mode) && mesh->vertex_buffer_indices[1] != -1)
		lighting_buffer = ((c_rasterizer_vertex_buffer *(*const)(s_render_geometry *, s_mesh *, e_vertex_buffer_usage))0x78C750)(geometry, mesh, (e_vertex_buffer_usage)1);
	if (lighting_buffer)
		eldorado::rasterizer_set_vertex_stream(lighting_buffer);
	if (mesh->vertex_buffer_indices[3] != -1)
	{
		c_rasterizer_vertex_buffer *ambient_ptr_buffer = ((c_rasterizer_vertex_buffer *(*const)(s_render_geometry *, s_mesh *, e_vertex_buffer_usage))0x78C750)(geometry, mesh, (e_vertex_buffer_usage)3);
		if (ambient_ptr_buffer)
			eldorado::rasterizer_set_vertex_stream(ambient_ptr_buffer);
	}
	if (entry_point == _entry_static_prt_quadratic)
	{
		if (mesh->flags.test((e_mesh_flags)0))
		{
			entry_point = _entry_static_per_vertex_color;
		}
		else if (eldorado::cinematic_in_progress() || player_reading_terminal() || (entry_point = _entry_static_sh, global_preferenced_get_lighting_quality()))
		{
			if ((char)mesh->prt_vertex_type >= 0 && (char)mesh->prt_vertex_type < 4 && !Patches::RenderObject::GetPRTDisabled())
			{
				long *g_prt_type_to_entry_point = (long *)0x16940C8;
				entry_point = (e_entry_point)g_prt_type_to_entry_point[(char)mesh->prt_vertex_type];
			}
		}
	}
	long render_method_index = materials[part->material_index].render_method.index;
	c_render_method *render_method = c_render_method::get(render_method_index);
	if (!render_method_submit(render_method_index, render_method, mesh->vertex_type, mesh->prt_vertex_type, entry_point, false))
		return;
	bool prevent_backface_culling = part->flags.test((e_part_flags)6);
	long cached_cull_mode = 2;
	if (prevent_backface_culling)
	{
		cached_cull_mode = eldorado::c_rasterizer_get_cull_mode();
		eldorado::c_rasterizer_set_cull_mode(0);
	}
	bool alpha_test_enabled = false;
	if ((*(c_tag_block<s_render_method_postprocess_definition> *)((char *)render_method + 0x28))->flags.test((e_render_method_postprocess_flags)1))
	{
		alpha_test_enabled = true;
		((void (*const)(bool))0xA230E0)(true);
	}
	if (!subpart_visibility)
	{
		eldorado::c_rasterizer_draw_indexed_primitive(index_buffer, 0, vertex_buffer->get_vertex_count(), part->first_index, part->index_count);
	}
	else if (part->subpart_count > 0)
	{
		long index_start = -1;
		long index_end = -1;
		for (long i = 0; i < part->subpart_count; i++)
		{
			if (!((1 << (i & 31)) & subpart_visibility[i >> 5]))
				continue;
			s_subpart *subpart = &mesh->subparts[part->first_subpart_index + i];
			if (index_start == -1)
			{
				index_start = subpart->first_index;
				index_end = subpart->first_index + subpart->index_count - 1;
			}
			else if (subpart->first_index == index_end + 1)
			{
				index_end = subpart->first_index + subpart->index_count - 1;
			}
			else
			{
				eldorado::c_rasterizer_draw_indexed_primitive(index_buffer, 0, vertex_buffer->get_vertex_count(), index_start, index_end - index_start + 1);
				index_start = subpart->first_index;
				index_end = subpart->first_index + subpart->index_count - 1;
			}
		}
		if (index_start != -1)
			eldorado::c_rasterizer_draw_indexed_primitive(index_buffer, 0, vertex_buffer->get_vertex_count(), index_start, index_end - index_start + 1);
	}
	if (alpha_test_enabled)
		((void (*const)(bool))0xA230E0)(false);
	if (prevent_backface_culling)
		eldorado::c_rasterizer_set_cull_mode(cached_cull_mode);
}

void c_structure_renderer__render_cluster_mesh_part_hook(long cluster_visibility_index, e_entry_point entry_point, long flags) // 0x108E8D60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_structure_renderer__render_cluster_mesh_part_hook@@YAXJW4e_entry_point@@J@Z");

	static long (*const render_cubemap_index_get)(s_cluster_reference) = reinterpret_cast<long (*)(s_cluster_reference)>(0xA7A5D0);
	static s_render_geometry *(*const render_structure_get_geometry)(long) = reinterpret_cast<s_render_geometry *(*)(long)>(0xA2EF00);
	static s_breakable_surface_set *(*const breakable_surface_set_get)(long, long, long) = reinterpret_cast<s_breakable_surface_set *(*)(long, long, long)>(0x569D70);
	static s_cluster_reference (*const render_setup_lighting)(bool, long, s_cluster_reference, long, s_cluster_reference, long, s_cluster_reference, long, float, unsigned long *, long, long, long, void *) = reinterpret_cast<s_cluster_reference (*)(bool, long, s_cluster_reference, long, s_cluster_reference, long, s_cluster_reference, long, float, unsigned long *, long, long, long, void *)>(0xA3CD20);
	static void (*const render_mesh_part)(long long, s_render_geometry *, s_mesh *, s_part *, e_entry_point, unsigned long *, s_geometry_material *) = reinterpret_cast<void (*)(long long, s_render_geometry *, s_mesh *, s_part *, e_entry_point, unsigned long *, s_geometry_material *)>(0xA475A0);
	static void (*const breakable_surface_set_release)(long, long, long) = reinterpret_cast<void (*)(long, long, long)>(0x56A360);
	static void (*const render_object_mesh_part_end)(bool) = reinterpret_cast<void (*)(bool)>(0xA3D260);
	e_entry_point (*const update_cluster_stream_and_determine_lighting_attributes)(e_entry_point, long, s_render_geometry *, s_mesh *, s_part *, s_geometry_material *, s_cluster_reference) = reinterpret_cast<e_entry_point (*)(e_entry_point, long, s_render_geometry *, s_mesh *, s_part *, s_geometry_material *, s_cluster_reference)>(0xA2FED0);
	s_render_cluster_part *cluster = &((s_render_structure_globals *)0x50E8938)->cluster_parts[render_structure_cluster_sorter->order_table[cluster_visibility_index]];
	if (flags & cluster->flags)
	{
		long bsp_index = cluster->cluster_reference.bsp_index;
		s_scenario_structure_bsp *structure_bsp = global_structure_bsp_get(bsp_index);
		s_geometry_material *materials = (s_geometry_material *)structure_bsp->materials.address;
		if (structure_bsp->materials.count > 0)
		{
			long cubemap_index = render_cubemap_index_get(cluster->cluster_reference);
			s_render_geometry *geometry = render_structure_get_geometry(bsp_index);
			s_mesh *mesh = &geometry->meshes[cluster->mesh_index];
			s_part *part = &mesh->parts[cluster->part_index];
			if (!(part->flags & 8))
			{
				unsigned long *subpart_visibility = nullptr;
				long breakable_surface_set_index = materials[part->material_index].breakable_surface_set_index;
				if (breakable_surface_set_index != -1)
				{
					s_breakable_surface_set *breakable_surface_set = breakable_surface_set_get(bsp_index, -1, breakable_surface_set_index);
					if (breakable_surface_set)
						subpart_visibility = breakable_surface_set->subpart_visibility;
					else
						subpart_visibility = nullptr;
				}
				entry_point = update_cluster_stream_and_determine_lighting_attributes(entry_point, bsp_index, geometry, mesh, part, materials, cluster->cluster_reference);
				long context = cluster->part_index * 255 + ((cluster->cluster_reference.cluster_index * 16 + bsp_index) * 16);
				render_setup_lighting(true, bsp_index, cluster->cluster_reference, -1, cluster->cluster_reference, cubemap_index, cluster->cluster_reference, cubemap_index, 1.0f, nullptr, -1, -1, context, nullptr);
				render_mesh_part(0, geometry, mesh, part, entry_point, subpart_visibility, materials);
				if (breakable_surface_set_index != -1)
					breakable_surface_set_release(bsp_index, -1, breakable_surface_set_index);
			}
		}
	}
	render_object_mesh_part_end(false);
}

void c_structure_renderer__render_instance_mesh_part_hook(long render_instance_index, e_entry_point entry_point, long flags) // 0x108EA030
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_structure_renderer__render_instance_mesh_part_hook@@YAXJW4e_entry_point@@J@Z");

	e_entry_point (*const update_cluster_instance_stream_and_determine_lighting_attributes)(e_entry_point, long, s_scenario_lightmap_bsp_data *, s_render_geometry *, s_mesh *, s_part *, s_geometry_material *, long, s_structure_instanced_geometry_instance *) = reinterpret_cast<e_entry_point (*)(e_entry_point, long, s_scenario_lightmap_bsp_data *, s_render_geometry *, s_mesh *, s_part *, s_geometry_material *, long, s_structure_instanced_geometry_instance *)>(0xA2FF80);
	s_render_instance_part *render_instance_part = &((s_render_structure_globals *)0x50E8938)->instance_parts[render_instance_index];
	if (render_instance_part->lod && (flags & render_instance_part->flags))
	{
		long bsp_index = render_instance_part->structure_bsp_index;
		s_scenario_structure_bsp *structure_bsp = global_structure_bsp_get(bsp_index);
		if (structure_bsp->materials.count > 0)
		{
			s_scenario_lightmap_bsp_data *lightmap_data = ((s_scenario_lightmap_bsp_data *(*const)(long))0xA2EEC0)(bsp_index);
			s_render_geometry *geometry = ((s_render_geometry *(*const)(long))0xA2EF00)(bsp_index);
			s_structure_instanced_geometry_instance *instance = &structure_bsp->instanced_geometry_instances[render_instance_part->instance_index];
			s_geometry_material *materials = (s_geometry_material *)structure_bsp->materials.address;
			if (!(instance->flags & 0x40))
			{
				long instance_index = render_instance_part->instance_index;
				long definition_index = instance->mesh_index;
				s_structure_instanced_geometry_definition *instance_geometry_definition = ((s_structure_instanced_geometry_definition *(*const)(long, long))0x4E9640)(bsp_index, definition_index);
				s_compression_info *compression_info = &geometry->compression[instance_geometry_definition->compression_info_index];
				long current_definition_index = -1;
				if (bsp_index == ((s_render_structure_globals *)0x50E8938)->current_bsp_index)
				{
					current_definition_index = ((s_render_structure_globals *)0x50E8938)->current_instance_definition_index;
				}
				else
				{
					((s_render_structure_globals *)0x50E8938)->current_bsp_index = bsp_index;
					((s_render_structure_globals *)0x50E8938)->current_instance_definition_index = -1;
					((s_render_structure_globals *)0x50E8938)->current_instance_index = -1;
					current_definition_index = -1;
				}
				if (definition_index != current_definition_index)
				{
					((void (*const)(s_compression_info const *))0xA47890)(compression_info);
					((s_render_structure_globals *)0x50E8938)->current_instance_definition_index = definition_index;
				}
				if (instance_index != ((s_render_structure_globals *)0x50E8938)->current_instance_index)
				{
					((void (*const)(real_matrix4x3 const *))0xA47B00)(&instance->rigid_matrix);
					((s_render_structure_globals *)0x50E8938)->current_instance_index = instance_index;
				}
				s_cluster_reference cluster_reference = { (char)bsp_index, 0xFF };
				((s_cluster_reference (*const)(bool, long, s_cluster_reference, long, s_cluster_reference, long, s_cluster_reference, long, float, unsigned long *, long, long, long, void *))0xA3CD20)(true, bsp_index, s_cluster_reference{ -1, 0xFF }, render_instance_part->instance_index, cluster_reference, instance->cubemap_index, cluster_reference, instance->cubemap_index, 1.0f, nullptr, -1, -1, render_instance_part->instance_index, nullptr);
				s_mesh *mesh = &geometry->meshes[instance_geometry_definition->mesh_index];
				s_part *part = &mesh->parts[render_instance_part->mesh_part_index];
				entry_point = update_cluster_instance_stream_and_determine_lighting_attributes(entry_point, bsp_index, lightmap_data, geometry, mesh, part, materials, instance_index, instance);
				unsigned long *subpart_visibility = nullptr;
				eldorado::rasterizer_stipple_set_fade_byte(render_instance_part->lod, 0, 0, 0);
				long breakable_surface_set_index = materials[part->material_index].breakable_surface_set_index;
				if (breakable_surface_set_index != -1 && !(instance->flags & 2))
				{
					s_breakable_surface_set *breakable_surface_set = ((s_breakable_surface_set *(*const)(long, long, long))0x569D70)(render_instance_part->structure_bsp_index, render_instance_part->instance_index, breakable_surface_set_index);
					if (breakable_surface_set)
						subpart_visibility = breakable_surface_set->subpart_visibility;
					else
						subpart_visibility = nullptr;
				((void (*const)(long))0x56A900)(c_render_globals::get_frame_index());
				}
				((void (*const)(long long, s_render_geometry *, s_mesh *, s_part *, e_entry_point, unsigned long *, s_geometry_material *))0xA475A0)(0, geometry, mesh, part, entry_point, subpart_visibility, materials);
				if (materials[part->material_index].breakable_surface_set_index != -1 && !(instance->flags & 2))
				{
					((void (*const)())0x56A8E0)();
					((void (*const)(long, long, long))0x56A360)(render_instance_part->structure_bsp_index, render_instance_part->instance_index, materials[part->material_index].breakable_surface_set_index);
				}
			}
		}
	}
	eldorado::render_method_submit_valid(false);
}

void c_structure_renderer__submit_cluster_visibility(bool include_transparent) // 0x108EA710
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_structure_renderer__submit_cluster_visibility@@YAX_N@Z");

	s_visible_items &visible_items = c_visible_items::get_global_items();
	long cluster_starting_index = c_visible_items::get_current_markers().clusters_marker;
	long iterator;
	for (s_visible_cluster *cluster = visible_items.clusters.list_iterator_new(&iterator, cluster_starting_index); cluster; cluster = visible_items.clusters.list_iterator_next(&iterator))
	{
		long structure_bsp_index = cluster->cluster_reference.bsp_index;
		s_scenario_structure_bsp *structure_bsp = global_structure_bsp_get(structure_bsp_index);
		if (!structure_bsp->materials.count)
			continue;
		if (!(cluster->flags & 0x8))
			continue;
		s_render_geometry *geometry = ((s_render_geometry *(*)(long))0xA2EF00)(structure_bsp_index);
		s_mesh *mesh = &geometry->meshes[cluster->mesh_index];
		for (long part_index = 0; part_index < mesh->parts.count; part_index++)
		{
			if (((s_render_structure_globals *)0x50E8938)->cluster_part_count >= sizeof(((s_render_structure_globals *)0)->cluster_parts) / sizeof(s_render_cluster_part))
				continue;
			if (cluster->mesh_part_visibility && !(cluster->mesh_part_visibility[part_index >> 5] & (1 << (part_index & 0x1F))))
				continue;
			s_part *part = &mesh->parts[part_index];
			if (!((bool (*)(s_part *, s_geometry_material *))0xA47430)(part, &structure_bsp->materials[0]))
				continue;
			long render_method_index = structure_bsp->materials[part->material_index].render_method.index;
			c_render_method *render_method = c_render_method::get(render_method_index);
			bool is_transparent = c_render_method::get_is_transparent(render_method_index);
			bool use_z_prepass = ((bool (*)(long))0xA77D20)(render_method_index);
			bool is_decal = c_render_method::get_is_decal(render_method_index);
			unsigned long flags;
			if (use_z_prepass)
				flags = 0x10;
			else if (is_transparent)
				flags = 0x4;
			else
				flags = cluster->flags & 0x3;
			if (is_decal)
				flags |= 0x8;
			s_render_cluster_part *render_part = &((s_render_structure_globals *)0x50E8938)->cluster_parts[((s_render_structure_globals *)0x50E8938)->cluster_part_count];
			render_part->flags = flags;
			render_part->cluster_reference = cluster->cluster_reference;
			render_part->mesh_index = cluster->mesh_index;
			render_part->part_index = (unsigned short)part_index;
			if (use_z_prepass)
			{
				is_transparent = false;
				((void (*)(void *, long, long))0xA7AC90)((void *)0xA2FD80, 0, ((s_render_structure_globals *)0x50E8938)->cluster_part_count);
			}
			if (include_transparent && is_transparent)
			{
				real_plane3d plane = { global_forward3d.i, global_forward3d.j, global_forward3d.k, 0.0f };
				real_point3d position = global_origin3d;
				float radius = 0.0f;
				if (part->transparent_sorting_index != -1)
				{
					short sorting_index = part->transparent_sorting_index;
					if (sorting_index & 0x8000)
						sorting_index += 0x8000;
					s_sorting_position *sorting_position = &geometry->sorting[sorting_index];
					plane = sorting_position->plane;
					position = sorting_position->position;
					radius = sorting_position->radius;
				}
				((void (*)(real_point3d const *, real_plane3d const *, float, e_sorting_layer, void *, long, long, float))0xA72BF0)(&position, &plane, 0.0f, *(c_enum<e_sorting_layer, char> *)((char *)render_method + 0x36), (void *)0xA2FCF0, 0, ((s_render_structure_globals *)0x50E8938)->cluster_part_count, radius);
			}
			render_structure_cluster_sorter->order_table[((s_render_structure_globals *)0x50E8938)->cluster_part_count] = (unsigned short)((s_render_structure_globals *)0x50E8938)->cluster_part_count;
			if (render_structure_cluster_sorter->count <= ((s_render_structure_globals *)0x50E8938)->cluster_part_count + 1)
				render_structure_cluster_sorter->count = ((s_render_structure_globals *)0x50E8938)->cluster_part_count + 1;
			((s_render_structure_globals *)0x50E8938)->cluster_part_count++;
		}
	}
}

void c_structure_renderer__submit_instance_visibility(bool include_transparent) // 0x108EAEA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_structure_renderer__submit_instance_visibility@@YAX_N@Z");

	extern real_point3d *matrix4x3_transform_point(real_matrix4x3 const *, real_point3d const *, real_point3d *);
	extern real_plane3d *matrix4x3_transform_plane(real_matrix4x3 const *, real_plane3d const *, real_plane3d *);
	bool (*const instance_list_sort_proc)(unsigned short, unsigned short, void const *) = reinterpret_cast<bool (*)(unsigned short, unsigned short, void const *)>(0xA2EF80);
	s_visible_items &visible_items = c_visible_items::get_global_items();
	long instance_group_start_index = c_visible_items::get_current_markers().instance_groups_marker;
	long count = visible_items.instance_groups.count - instance_group_start_index;
	if (!count)
		return;
	if (count > 4096)
		count = 4096;
	s_sorter<s_visible_instance_group, 4096> sorter;
	sorter.count = (unsigned short)count;
	sorter.elements = nullptr;
	for (unsigned short i = 0; i < count; i++)
		sorter.order_table[i] = instance_group_start_index + i;
	((void (*)(unsigned short *, long, bool (*)(unsigned short, unsigned short, void const *), void const *))0x65B070)(&sorter.order_table[0], count, instance_list_sort_proc, nullptr);
	for (long i = 0; i < count; i++)
	{
		s_visible_instance_group *instance_list = &visible_items.instance_groups.elements[sorter.order_table[i]];
		long structure_bsp_index = instance_list->cluster_reference.bsp_index;
		s_scenario_structure_bsp *structure_bsp = global_structure_bsp_get(structure_bsp_index);
		if (!structure_bsp->materials.count)
			continue;
		s_render_geometry *geometry = ((s_render_geometry *(*)(long))0xA2EF00)(structure_bsp_index);
		long instance_start_index = instance_list->first_index;
		long instance_end_index = instance_list->count + instance_start_index;
		s_mesh *mesh = &geometry->meshes[instance_list->mesh_index];
		for (long part_index = 0; part_index < mesh->parts.count; part_index++)
		{
			s_part *part = &mesh->parts[part_index];
			if (!((bool (*)(s_part *, s_geometry_material *))0xA47430)(part, &structure_bsp->materials[0]))
				continue;
			long render_method_index = structure_bsp->materials[part->material_index].render_method.index;
			for (long k = instance_start_index; k < instance_end_index; k++)
			{
				if (((s_render_structure_globals *)0x50E8938)->instance_part_count >= sizeof(((s_render_structure_globals *)0)->instance_parts) / sizeof(s_render_instance_part))
					break;
				s_visible_instance *instance = &visible_items.instances.elements[k];
				if (instance->mesh_part_visibility && !(instance->mesh_part_visibility[part_index >> 5] & (1 << (part_index & 0x1F))))
					continue;
				if (!(instance->flags & 0xC))
					continue;
				long render_method_index = structure_bsp->materials[part->material_index].render_method.index;
				c_render_method *render_method = c_render_method::get(render_method_index);
				bool is_transparent = c_render_method::get_is_transparent(render_method_index);
				bool use_z_prepass = ((bool (*)(long))0xA77D20)(render_method_index);
				bool is_decal = c_render_method::get_is_decal(render_method_index);
				unsigned long flags;
				if (use_z_prepass)
					flags = 0x10;
				else if (is_transparent)
					flags = 0x4;
				else
					flags = instance->flags & 0x3;
				if (is_decal)
					flags |= 0x8;
				s_render_instance_part *render_part = &((s_render_structure_globals *)0x50E8938)->instance_parts[((s_render_structure_globals *)0x50E8938)->instance_part_count];
				render_part->flags = flags;
				render_part->structure_bsp_index = instance->structure_bsp_index;
				render_part->instance_index = instance->instance_index;
				render_part->mesh_index = instance_list->mesh_index;
				render_part->mesh_part_index = (short)part_index;
				render_part->lod = (unsigned char)instance->alpha;
				if (include_transparent && is_transparent)
				{
					real_plane3d plane = { global_forward3d.i, global_forward3d.j, global_forward3d.k, 0.0f };
					real_point3d position = global_origin3d;
					float radius = 0.0f;
					s_structure_instanced_geometry_instance *matrix = &structure_bsp->instanced_geometry_instances[instance->instance_index];
					if (part->transparent_sorting_index != -1)
					{
						short transparent_sorting_index = part->transparent_sorting_index;
						if (transparent_sorting_index & 0x8000)
							transparent_sorting_index += 0x8000;
						s_sorting_position *sorting_position = &geometry->sorting[transparent_sorting_index];
						plane = sorting_position->plane;
						position = sorting_position->position;
						radius = sorting_position->radius;
						matrix4x3_transform_point(&matrix->rigid_matrix, &position, &position);
						matrix4x3_transform_plane(&matrix->rigid_matrix, &plane, &plane);
					}
					else
					{
						position = matrix->rigid_matrix.position;
					}
					((void (*)(real_point3d const *, real_plane3d const *, float, e_sorting_layer, void *, long, long, float))0xA72BF0)(&position, &plane, 0.0f, *(c_enum<e_sorting_layer, char> *)((char *)render_method + 0x36), (void *)0xA2FD10, 0, ((s_render_structure_globals *)0x50E8938)->instance_part_count, radius);
				}
				((s_render_structure_globals *)0x50E8938)->instance_part_count++;
			}
		}
	}
}

void c_structure_renderer__submit_visibility_hook(bool include_transparent) // 0x108EB870
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_structure_renderer__submit_visibility_hook@@YAX_N@Z");

	c_structure_renderer__submit_cluster_visibility(include_transparent);
	c_structure_renderer__submit_instance_visibility(include_transparent);
}

void c_structure_renderer__render_decorators_hook() // 0x108E9110
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_structure_renderer__render_decorators_hook@@YAXXZ");

	long (*const preferences_get_detail_quality)() = reinterpret_cast<long (*)()>(0x50AF50);
	void (*const sub_A28480)(__int32) = reinterpret_cast<void (*)(__int32)>(0xA28480);
	void (*const clear_cached_sun_constants)() = reinterpret_cast<void (*)()>(0xA2ECE0);
	long (*const scenario_zone_set_index_get)() = reinterpret_cast<long (*)()>(0x4EBA20);
	long (*const scenario_zone_set_structure_bsp_cluster_visible_sky_index_get)(s_scenario *, long, long, long) = reinterpret_cast<long (*)(s_scenario *, long, long, long)>(0x766380);
	void (*const sub_A301E0)(long) = reinterpret_cast<void (*)(long)>(0xA301E0);
	float (*const rasterizer_camera_get_fov_pixel_linear_scale)() = reinterpret_cast<float (*)()>(0xA28EC0);
	bool (*const visibility_region_test_sphere)(void *, long, real_point3d *, float, bool *) = reinterpret_cast<bool (*)(void *, long, real_point3d *, float, bool *)>(0x971C60);
	void (*const rasterizer_set_vertex_buffer_stream)(c_rasterizer_vertex_buffer *, long) = reinterpret_cast<void (*)(c_rasterizer_vertex_buffer *, long)>(0xA5DB90);
	bool &g_render_decorators = *(bool *)0x191367C;
	bool &byte_50E8931 = *(bool *)0x50E8931;
	float cull_modifier = g_decorator_distance_scale;
	if (g_render_decorators && cull_modifier != 0.0f)
	{
		c_player_view *player_view = c_player_view::get_current();
		real_point3d &camera_position = player_view->render_camera.position;
		s_wind_definition *const wind = s_wind_definition::get_wind_definition(&camera_position);
		if (wind)
			s_wind_definition::update(wind, &g_wind_values);
		eldorado::c_rasterizer_set_z_buffer_mode(0);
		eldorado::c_rasterizer_set_color_write_enable(0, 15);
		IDirect3DDevice9Ex *const g_device = c_rasterizer::get_device();
		if (!byte_50E8931)
		{
			((void (*const)(s_wind_definition *, s_wind_values *))0x14E6E90)(wind, &g_wind_values);
			eldorado::c_rasterizer_set_stencil_mode(9);
			clear_cached_sun_constants();
			c_visibility_collection *collection = eldorado::get_global_camera_collection();
			s_visibility_region *region = collection->visbility_region;
			float fov_scale = rasterizer_camera_get_fov_pixel_linear_scale();
			for (__int32 i = 0; i < collection->visbility_region->cluster_count; i++)
			{
				long structure_bsp_index = region->clusters[i].cluster_reference.bsp_index;
				long cluster_index = region->clusters[i].cluster_reference.cluster_index;
				s_scenario_structure_bsp *const global_sbsp = global_structure_bsp_get(structure_bsp_index);
				s_structure_cluster *const cluster = &global_sbsp->clusters[cluster_index];
				if (cluster->decorator_grids.count > 0)
				{
					long zone_set_index = scenario_zone_set_index_get();
					long visible_sky_index = scenario_zone_set_structure_bsp_cluster_visible_sky_index_get(global_scenario_get(), zone_set_index, structure_bsp_index, cluster_index);
					if (visible_sky_index != -1)
						sub_A301E0(visible_sky_index);
				}
				for (__int32 j = 0; j < cluster->decorator_grids.count; j++)
				{
					((void (*const)(long))0xA230E0)(1);
					s_decorator_grid *const decorator_grid = &cluster->decorator_grids[j];
					if (!decorator_grid->amount)
						continue;
					long dctr_index = global_sbsp->decorators[decorator_grid->palette_index].index;
					if (dctr_index == -1)
						continue;
					s_decorator_set *const decorator_set = s_decorator_set::get(dctr_index);
					if (decorator_set->model.index != -1)
					{
						float cull_start = cull_modifier / fov_scale * decorator_set->cull_start;
						float cull_end = cull_modifier / fov_scale * decorator_set->cull_end;
						real_vector3d pos;
						pos = decorator_grid->bounding_sphere_offset - camera_position;
						float position_magnitude = sqrt(pos.i * pos.i + pos.j * pos.j + pos.k * pos.k);
						if ((1.0f - decorator_set->scale) * (decorator_grid->radius + cull_end) >= position_magnitude)
						{
							bool fully_contained;
							if (visibility_region_test_sphere(region, i, &decorator_grid->bounding_sphere_offset, decorator_grid->radius, &fully_contained))
							{
								eldorado::c_rasterizer_set_explicit_shaders(s_decorator_set::get_explicit_shader_index(decorator_set), 15, 0, 0);
								real_vector4d LOD_constants;
								LOD_constants.i = 0.7f / (cull_start - cull_end);
								LOD_constants.j = 1.0f - 0.7f / (cull_start - cull_end) * cull_start;
								LOD_constants.k = 0.0f;
								LOD_constants.w = 0.0f;
								eldorado::c_rasterizer_set_vertex_shader_constant(245, 1, &LOD_constants);
								eldorado::c_rasterizer_set_vertex_shader_constant(246, 1, (real_vector4d const *)&decorator_set->translucency_abc);
								eldorado::c_rasterizer_set_vertex_shader_constant(249, 1, (real_vector4d const *)&decorator_set->wavelength_xy);
								eldorado::c_rasterizer_set_pixel_shader_constant(13, 1, (real_vector4d const *)&decorator_set->darkness);
								eldorado::c_rasterizer_set_cull_mode(2 - ((decorator_set->render_flags & 1) != 0));
								s_render_model *const render_model = (s_render_model *)tag_get('mode', decorator_set->model.index);
								s_render_geometry *const render_geometry = &render_model->render_geometry;
								c_rasterizer_vertex_buffer *vertex_buffer = ((c_rasterizer_vertex_buffer *(*const)(s_render_geometry *, long))0x78C930)(render_geometry, 0);
								eldorado::rasterizer_set_vertex_stream_2(vertex_buffer);
								((void (*const)(s_compression_info *, float))0xA47940)(&render_geometry->compression[0], 2.0f);
								((void (*const)(long, long, long))0xA3D130)(0, decorator_set->texture.index, 0);
								eldorado::c_rasterizer_set_sampler_address_mode_2(0, _address_mode_wrap, _address_mode_wrap, _address_mode_wrap);
								eldorado::c_rasterizer_set_sampler_filter_mode_2(0, _filter_bilinear);
								c_rasterizer_vertex_buffer *sbsp_vertex_buffer = ((c_rasterizer_vertex_buffer *(*const)(s_render_geometry *, long))0x78C930)(&global_sbsp->decorator_geometry, decorator_grid->vertex_buffer_index);
								rasterizer_set_vertex_buffer_stream(sbsp_vertex_buffer, decorator_grid->vertex_buffer_offset);
								eldorado::c_rasterizer_set_vertex_shader_constant(240, 2, (real_vector4d const *)&decorator_grid->position);
								s_mesh *const mesh = &render_geometry->meshes[render_model->instance_mesh_index];
								long instance_index_count = mesh->subparts[decorator_grid->variant].index_count;
								rasterizer_set_vertex_buffer_stream(sbsp_vertex_buffer, decorator_grid->vertex_buffer_offset);
								real_vector4d variant_index_count;
								variant_index_count.i = (float)instance_index_count;
								variant_index_count.j = 0.0f;
								variant_index_count.k = 0.0f;
								variant_index_count.w = 0.0f;
								eldorado::c_rasterizer_set_vertex_shader_constant(242, 1, &variant_index_count);
								g_device->SetStreamSourceFreq(0, decorator_grid->amount | D3DSTREAMSOURCE_INDEXEDDATA);
								g_device->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
								sub_A28480(decorator_grid->amount);
								c_rasterizer_index_buffer *const index_buffer = ((c_rasterizer_index_buffer *(*const)(s_render_geometry *, long))0x78C870)(render_geometry, mesh->index_buffer_indices[0]);
								eldorado::c_rasterizer_draw_indexed_primitive_2(index_buffer, mesh->subparts[decorator_grid->variant].first_index, instance_index_count, 0, instance_index_count);
							}
						}
					}
				}
			}
		}
		g_device->SetStreamSourceFreq(0, 1);
		g_device->SetStreamSourceFreq(1, 1);
		sub_A28480(1);
		eldorado::render_method_submit_valid(false);
		((void (*const)(long))0xA230E0)(0);
		eldorado::c_rasterizer_set_stencil_mode(0);
	}
}

void c_object_renderer__submit_object_mesh_parts_for_active_camo_hook(s_render_object *render_object, s_visible_object *visible_object, bool a3, __int32 is_first_person) // 0x108E6520
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_object_renderer__submit_object_mesh_parts_for_active_camo_hook@@YAXPAUs_render_object@@PAUs_visible_object@@_NH@Z");

	void * (*const object_get_active_shield_render_parameters)(s_object_data *, long) = reinterpret_cast<void * (*)(s_object_data *, long)>(0xA78030);
	long (*const render_objects_add_element)(s_render_object *, s_render_object_info *, unsigned long *, short, short, short, short, __int32) = reinterpret_cast<long (*)(s_render_object *, s_render_object_info *, unsigned long *, short, short, short, short, __int32)>(0xA77AC0);
	void (*const sub_A73840)() = reinterpret_cast<void (*)()>(0xA73840);
	void * (*const sub_A6DAA0)(long) = reinterpret_cast<void * (*)(long)>(0xA6DAA0);
	void * (*const model_skinning_get_rigid_region_matrix)(void *, long) = reinterpret_cast<void * (*)(void *, long)>(0xA1EE00);
	void (*const s_model_skinning_matrix_to_real_matrix4x3)(real_matrix4x3 *, void *) = reinterpret_cast<void (*)(real_matrix4x3 *, void *)>(0xA47BE0);
	void (*const sub_A731A0)(long, long) = reinterpret_cast<void (*)(long, long)>(0xA731A0);
	s_render_model *const mode = (s_render_model *)tag_get('mode', visible_object->info.render_model_index);
	if (mode->materials.count > 0)
	{
		void *shield_impact = nullptr;
		if (a3)
			shield_impact = object_get_active_shield_render_parameters(object_try_and_get_and_verify_type(visible_object->object_index, -1), is_first_person);
		for (__int32 region_index = 0; region_index < visible_object->info.region_count; region_index++)
		{
			short transparent_sort_index = visible_object->info.region_transparent_sort_indices[region_index];
			unsigned char region_mesh_index = visible_object->info.region_mesh_indices[region_index];
			if (region_mesh_index != 0xFF)
			{
				s_mesh const *mesh = &mode->render_geometry.meshes[region_mesh_index];
				for (__int32 part_index = 0; part_index < mesh->parts.count; part_index++)
				{
					s_part const *part = &mesh->parts[part_index];
					if (part->material_index == -1)
						continue;
					unsigned long render_method_index = mode->materials[part->material_index].render_method.index;
					if (render_method_index == -1)
						continue;
					c_render_method *const render_method = c_render_method::get(render_method_index);
					*(long *)0x524B6DC |= ((c_flags<enum e_render_method_flags,short> *)((char *)render_method + 0x34))->test((e_render_method_flags)2);
					long render_object_mesh_part_index = render_objects_add_element(render_object, (s_render_object_info *)visible_object, visible_object->subpart_visibility, region_mesh_index, part_index, region_index, part->material_index, 6);
					sub_A73840();
					if (a3)
					{
						real_point3d sorting_position = global_origin3d;
						if (part->transparent_sorting_index != -1 && !part->flags.test((e_part_flags)1))
							sorting_position = mode->render_geometry.sorting[part->transparent_sorting_index].position;
						if (mesh->vertex_type == (e_vertex_type)1 || mesh->vertex_type == (e_vertex_type)2 || mesh->vertex_type == (e_vertex_type)22)
						{
							void *model_skinning = sub_A6DAA0(visible_object->info.skinning_memory_designator);
							void *model_skinning_matrix = model_skinning_get_rigid_region_matrix(model_skinning, region_index);
							real_matrix4x3 skinning_matrix;
							s_model_skinning_matrix_to_real_matrix4x3(&skinning_matrix, model_skinning_matrix);
							real_point3d position;
							matrix4x3_transform_point(&skinning_matrix, &sorting_position, &position);
							long element = ((long (*)(real_point3d const *, real_plane3d const *, float, e_sorting_layer, void *, long, long, float))0xA72BF0)(&position, nullptr, region_index * 0.1f, (e_sorting_layer)3, (void *)0xA78F50, (long)visible_object, render_object_mesh_part_index, 0.0f);
							if (element != -1 && transparent_sort_index != -1)
								sub_A731A0(transparent_sort_index, element);
						}
						s_render_object_globals *render_object_globals = render_object_globals_get();
						render_object_globals->parts[render_object_mesh_part_index].shield_definition = shield_impact;
					}
				}
			}
		}
	}
}

void c_water_renderer__render_water_part_hook(s_render_geometry *geometry, __int32 mesh_index, __int32 part_index, e_entry_point entry_point, s_geometry_material *materials) // 0x108EDE80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_water_renderer__render_water_part_hook@@YAXPAUs_render_geometry@@HHW4e_entry_point@@PAUs_geometry_material@@@Z");

	bool (*const c_water_renderer__is_active_ripple_exist)() = (bool (*)())0xA362B0;
	c_rasterizer_vertex_buffer *(*const mesh_get_vertex_buffer)(s_render_geometry *, s_mesh *, long) = (c_rasterizer_vertex_buffer *(*)(s_render_geometry *, s_mesh *, long))0x78C750;
	void (*const c_rasterizer__set_vertex_stream_with_offset)(long, void *, long, unsigned __int32) = (void (*)(long, void *, long, unsigned __int32))0xA245C0;
	float &k_ripple_buffer_radius = *(float *)0x19146E0;
	bool &g_render_water_tesselation = *(bool *)0x19146F1;
	c_rasterizer_vertex_buffer *g_water_memexport_vertex_buffer = (c_rasterizer_vertex_buffer *)0x50FAAD0;
	c_rasterizer_index_buffer *g_water_geometry_index_buffer = (c_rasterizer_index_buffer *)0x50FAAC0;
	s_mesh *const mesh = &geometry->meshes[mesh_index];
	s_part *const mesh_part = &mesh->parts[part_index];
	if (mesh_part->flags.test((e_part_flags)3))
	{
		unsigned long rm_index = materials[mesh_part->material_index].render_method.index;
		if (rm_index != -1)
		{
			c_render_method *const render_method = c_render_method::get(rm_index);
			if (eldorado::render_method_submit(rm_index, render_method, (e_vertex_type)18, mesh->prt_vertex_type, entry_point, false))
			{
				real_vector4d unknown_water_instance_constant = { (float)(mesh->instance_water[part_index].value / 3), 0.0f, 0.0f, 0.0f };
				eldorado::c_rasterizer_set_vertex_shader_constant(0x83, 1, &unknown_water_instance_constant);
				if (entry_point == _entry_static_per_pixel || entry_point == _entry_static_per_vertex)
				{
					eldorado::c_rasterizer_set_vertex_shader_constant(0x85, 1, (real_vector4d const *)&k_ripple_buffer_radius);
					__int32 active_water_interaction = *(bool *)0x19146F2 && c_water_renderer__is_active_ripple_exist();
					eldorado::c_rasterizer_set_vertex_shader_constant_bool(1, 1, &active_water_interaction);
					eldorado::c_rasterizer_set_pixel_shader_constant_bool(1, 1, &active_water_interaction);
					if (active_water_interaction)
					{
						eldorado::c_rasterizer_set_surface_as_texture(1, (e_surface)0x36);
						eldorado::c_rasterizer_set_sampler_filter_mode(1, _filter_bilinear);
						((void (*const)(long, e_surface))0xA48F80)(1, (e_surface)0x36);
						((void (*const)(long, c_enum<e_sampler_filter_mode, long>))0xA246A0)(1, _filter_bilinear);
					}
					__int32 k_is_water_tesselated = g_render_water_tesselation;
					eldorado::c_rasterizer_set_vertex_shader_constant_bool(2, 1, &k_is_water_tesselated);
					if (entry_point != _entry_static_per_pixel && entry_point == _entry_static_per_vertex)
					{
						c_rasterizer_vertex_buffer *water_vertex_buffer_1 = mesh_get_vertex_buffer(geometry, mesh, 6);
						c_rasterizer_vertex_buffer *water_vertex_buffer_2 = mesh_get_vertex_buffer(geometry, mesh, 7);
						c_rasterizer__set_vertex_stream_with_offset(1, water_vertex_buffer_1->get_d3d_buffer(), mesh_part->first_index * 156 / 3, 156);
						c_rasterizer__set_vertex_stream_with_offset(3, water_vertex_buffer_2->get_d3d_buffer(), mesh_part->first_index * 72 / 3, 72);
						c_rasterizer__set_vertex_stream_with_offset(2, g_water_memexport_vertex_buffer->get_d3d_buffer(), 0, 12);
						IDirect3DDevice9Ex *g_device = c_rasterizer::get_device();
						g_device->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
						g_device->SetStreamSourceFreq(3, D3DSTREAMSOURCE_INSTANCEDATA | 1);
						g_device->SetStreamSourceFreq(0, (mesh_part->index_count / 3) | D3DSTREAMSOURCE_INDEXEDDATA);
						g_device->SetStreamSourceFreq(2, (mesh_part->index_count / 3) | D3DSTREAMSOURCE_INDEXEDDATA);
						long vertex_count = 0;
						eldorado::c_rasterizer_draw_indexed_primitive(g_water_geometry_index_buffer, 0, vertex_count, 0, 0x2A3);
						g_device->SetStreamSourceFreq(0, 1);
						g_device->SetStreamSourceFreq(1, 1);
						g_device->SetStreamSourceFreq(2, 1);
						g_device->SetStreamSourceFreq(3, 1);
					}
				}
			}
		}
	}
}

void c_water_renderer__update_water_structure_part_list_hook(long *water_part_indices, long *out_count) // 0x108EE6B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_water_renderer__update_water_structure_part_list_hook@@YAXPAJ0@Z");

	bool (*const cluster_sort_proc)(unsigned short, unsigned short, void const *) = reinterpret_cast<bool (*)(unsigned short, unsigned short, void const *)>(0xA2ED40);
	*out_count = 0;
	long start_index = ((s_render_structure_globals *)0x50E8938)->cluster_markers[((s_render_structure_globals *)0x50E8938)->marker_index];
	long count;
	if ((count = (*render_structure_cluster_sorter).count - start_index) == 0)
		return;
	((void (*)(unsigned short *, long, bool (*)(unsigned short, unsigned short, void const *), void const *))0x65B070)(&(*render_structure_cluster_sorter).order_table[start_index], count, cluster_sort_proc, (*render_structure_cluster_sorter).elements);
	for (__int32 i = 0; i < count; i++)
	{
		s_render_cluster_part *mesh_part = &((s_render_structure_globals *)0x50E8938)->cluster_parts[(*render_structure_cluster_sorter).order_table[i]];
		long structure_bsp_index = mesh_part->cluster_reference.bsp_index;
		s_render_geometry *geometry = ((s_render_geometry *(*)(long))0xA2EF00)(structure_bsp_index);
		if (geometry->meshes[mesh_part->mesh_index].parts[mesh_part->part_index].flags & 8)
			water_part_indices[(*out_count)++] = i;
	}
}

void __fastcall s_render_shield_parts__render_hook(s_render_shield_parts *thisptr, void *unused, s_visible_object *visible_object, char flags) // 0x108F6670
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?s_render_shield_parts__render_hook@@YIXPAUs_render_shield_parts@@PAXPAUs_visible_object@@D@Z");

	void (*const sub_A79260)(s_render_object_mesh_part *) = reinterpret_cast<void (*)(s_render_object_mesh_part *)>(0xA79260);
	void (*const render_mesh_part_no_material)(s_render_geometry *, long, long) = reinterpret_cast<void (*)(s_render_geometry *, long, long)>(0xA47820);
	thisptr->visible_object = visible_object;
	thisptr->render_model = (s_render_model *)tag_get('mode', visible_object->info.render_model_index);
	thisptr->geometry = &thisptr->render_model->render_geometry;
	thisptr->materials = (s_geometry_material *)thisptr->render_model->materials.address;
	for (thisptr->current_region_index = 0; thisptr->current_region_index < visible_object->info.region_count; thisptr->current_region_index++)
	{
		thisptr->current_mesh_index = visible_object->info.region_mesh_indices[thisptr->current_region_index];
		if (thisptr->current_mesh_index != 0xFF)
		{
			thisptr->current_mesh = &thisptr->geometry->meshes[thisptr->current_mesh_index];
			((void (*)(long, long, long, long))0xA23300)(61, (char)thisptr->current_mesh->vertex_type, 0, 0);
			for (thisptr->current_part_index = 0; thisptr->current_part_index < thisptr->current_mesh->parts.count; thisptr->current_part_index++)
			{
				thisptr->current_part = &thisptr->current_mesh->parts[thisptr->current_part_index];
				if (!(flags & (unsigned char)thisptr->current_part->flags))
				{
					s_render_object_mesh_part render_object_mesh_part;
					render_object_mesh_part.info = thisptr->visible_object;
					render_object_mesh_part.flags = 0;
					render_object_mesh_part.subpart_visibility = render_object_mesh_part.info->subpart_visibility;
					render_object_mesh_part.part_index = (short)thisptr->current_part_index;
					render_object_mesh_part.mesh_index = (short)thisptr->current_mesh_index;
					render_object_mesh_part.skinning_node_index = (short)thisptr->current_region_index;
					render_object_mesh_part.material_index = thisptr->current_part->material_index;
					render_object_mesh_part.shield_definition = nullptr;
					sub_A79260(&render_object_mesh_part);
					render_mesh_part_no_material(thisptr->geometry, thisptr->current_mesh_index, thisptr->current_part_index);
				}
			}
		}
	}
}

void c_object_renderer__render_object_context_instances_hook(s_render_object_mesh_part *render_part, e_entry_point entry_point, unsigned long *subpart_visibility, s_lod_alphas alphas) // 0x108E5BE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_object_renderer__render_object_context_instances_hook@@YAXPAUs_render_object_mesh_part@@W4e_entry_point@@PAKUs_lod_alphas@@@Z");

	s_render_model *render_model = (s_render_model *)tag_get('mode', render_part->info->info.render_model_index);
	if (render_model->instance_mesh_index != -1 && render_model->materials.count > 0)
	{
		if (entry_point == _entry_static_prt_quadratic)
			entry_point = _entry_static_sh;
		s_mesh *mesh = &render_model->render_geometry.meshes[render_model->instance_mesh_index];
		s_compression_info *compression_info = &render_model->render_geometry.compression[0];
		((void (*const)(s_compression_info const *))0xA47890)(compression_info);
		long active_bsp_index = global_structure_bsp_first_active_index_get();
		eldorado::render_method_submit_data(active_bsp_index, render_part->info->info.render_info);
		long count = render_model->instance_placements.count;
		if (mesh->subparts.count < count)
			count = mesh->subparts.count;
		for (long i = 0; i < count; i++)
		{
			if (!(subpart_visibility[i >> 5] & (1 << (i & 31))))
				continue;
			s_render_model_instance_placement *placement = &render_model->instance_placements[i];
			s_part *part = &mesh->parts[mesh->subparts[i].part_index];
			if (!((bool (*const)(s_part *, s_geometry_material *))0xA47430)(part, &render_model->materials[0]))
				continue;
			real_matrix4x3 *skinning = (real_matrix4x3 *)((void *(*const)(long))0xA6DAA0)(render_part->info->info.skinning_memory_designator);
			real_matrix4x3 matrix;
			((float *(*const)(void const *, long, real_matrix4x3 *))0xA1ED50)(skinning, placement->node_index, &matrix);
			matrix4x3_multiply(&matrix, &placement->matrix, &matrix);
			float skinning_matrix[12];
			skinning_matrix[0] = matrix.forward.i * matrix.scale;
			skinning_matrix[1] = matrix.left.i * matrix.scale;
			skinning_matrix[2] = matrix.up.i * matrix.scale;
			skinning_matrix[3] = matrix.position.x;
			skinning_matrix[4] = matrix.forward.j * matrix.scale;
			skinning_matrix[5] = matrix.left.j * matrix.scale;
			skinning_matrix[6] = matrix.up.j * matrix.scale;
			skinning_matrix[7] = matrix.position.y;
			skinning_matrix[8] = matrix.forward.k * matrix.scale;
			skinning_matrix[9] = matrix.left.k * matrix.scale;
			skinning_matrix[10] = matrix.up.k * matrix.scale;
			skinning_matrix[11] = matrix.position.z;
			((void (*const)(float *, __int32))0xA47BC0)(skinning_matrix, 1);
			unsigned long local_subpart_visibility[2] = {};
			local_subpart_visibility[(i - part->first_subpart_index) >> 5] |= 1 << ((i - part->first_subpart_index) & 31);
			if (matrix.scale < 0.0)
				eldorado::c_rasterizer_set_cull_mode(3);
			((void (*const)(long long, s_render_geometry *, s_mesh *, s_part *, e_entry_point, unsigned long *, s_geometry_material *))0xA475A0)(0, &render_model->render_geometry, mesh, part, entry_point, local_subpart_visibility, &render_model->materials[0]);
			if (matrix.scale < 0.0)
				eldorado::c_rasterizer_set_cull_mode(2);
		}
	}
	eldorado::render_method_submit_valid(false);
}

void c_object_renderer__render_object_context_mesh_part_hook(s_render_object_mesh_part *mesh_part, e_entry_point entry_point, long mesh_part_mask, bool a4) // 0x108E62B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_object_renderer__render_object_context_mesh_part_hook@@YAXPAUs_render_object_mesh_part@@W4e_entry_point@@J_N@Z");

	static void (*const render_object_mesh_part_begin)(s_render_object_mesh_part const *) = reinterpret_cast<void (*)(s_render_object_mesh_part const *)>(0xA79260);
	static long (*const rasterizer_set_clip_plane)(long, float const *) = reinterpret_cast<long (*)(long, float const *)>(0xA231C0);
	static long (*const rasterizer_set_clip_plane_mask)(long) = reinterpret_cast<long (*)(long)>(0xA22B50);
	static void (*const render_mesh_part)(long long, s_render_geometry *, s_mesh *, s_part *, e_entry_point, unsigned long *, s_geometry_material *) = reinterpret_cast<void (*)(long long, s_render_geometry *, s_mesh *, s_part *, e_entry_point, unsigned long *, s_geometry_material *)>(0xA475A0);
	static void (*const render_object_mesh_part_end)(bool) = reinterpret_cast<void (*)(bool)>(0xA3D260);
	s_render_model *render_model = (s_render_model *)tag_get('mode', mesh_part->info->info.render_model_index);
	if (!render_model->materials.count)
		return;
	render_object_mesh_part_begin(mesh_part);
	s_mesh *mesh = &render_model->render_geometry.meshes[mesh_part->mesh_index];
	if (mesh_part->info->info.clipping_mask)
	{
		real_plane3d *g_cinematic_clip_planes = (real_plane3d *)0x50FB400;
		long active_clip_plane_mask = 0;
		long next_clip_plane_index = 0;
		for (long i = 0; i < 32; i++)
		{
			if (mesh_part->info->info.clipping_mask & (1 << i))
			{
				rasterizer_set_clip_plane(next_clip_plane_index, (float const *)&g_cinematic_clip_planes[i]);
				next_clip_plane_index++;
				active_clip_plane_mask = (active_clip_plane_mask << 1) | 1;
			}
		}
		rasterizer_set_clip_plane_mask(active_clip_plane_mask);
	}
	render_mesh_part(0, &render_model->render_geometry, mesh, &mesh->parts[mesh_part->part_index], entry_point, nullptr, &render_model->materials[0]);
	if (mesh_part->info->info.clipping_mask)
		rasterizer_set_clip_plane_mask(0);
	render_object_mesh_part_end(false);
}

void render_mesh_part_no_material(s_render_geometry *geometry, __int32 mesh_index, __int32 part_index) // 0x108F1190
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_mesh_part_no_material@@YAXPAUs_render_geometry@@HH@Z");

	c_rasterizer_vertex_buffer *(__cdecl *const mesh_get_vertex_buffer)(s_render_geometry *, s_mesh *, long) = (c_rasterizer_vertex_buffer *(__cdecl *const)(s_render_geometry *, s_mesh *, long))0x78c750;
	s_mesh *const mesh = &geometry->meshes[mesh_index];
	s_part *const mesh_part = &mesh->parts[part_index];
	c_rasterizer_index_buffer *index_buffer = ((c_rasterizer_index_buffer *(__cdecl *)(s_render_geometry const *, long))0x78c870)(geometry, mesh->index_buffer_indices[0]);
	c_rasterizer_vertex_buffer *vertex_buffer = mesh_get_vertex_buffer(geometry, mesh, 0);

	if (((bool(__cdecl *)(c_rasterizer_vertex_buffer const *))0xa5db60)(vertex_buffer))
	{
		((void(__cdecl *)(c_rasterizer_index_buffer const *, long, long, long, long))0xa28270)(index_buffer, 0, vertex_buffer->get_vertex_count(), mesh_part->first_index, mesh_part->index_count);
	}
}

long c_geometry_sampler__find_render_method_index_from_collision_hook(long structure_bsp_index, long a2, long instance_index, long surface_index) // 0x108E5530
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_geometry_sampler__find_render_method_index_from_collision_hook@@YAJJJJJ@Z");

	if (a2 != -1)
		return -1;
	s_scenario_structure_bsp *structure_bsp = global_structure_bsp_get(structure_bsp_index);
	s_render_geometry *geometry = ((s_render_geometry *(*)(long))0xA2EF00)(structure_bsp_index);
	if (instance_index == -1)
	{
		s_structure_bsp_cache_file_resources *cache_file_tag_resources = ((s_structure_bsp_cache_file_resources *(*)(s_tag_resource **))0x563E10)(&structure_bsp->pathfinding_resource);
		if (!cache_file_tag_resources->surface_planes.count)
			return -1;
		if (surface_index < 0 || surface_index >= cache_file_tag_resources->surface_planes.count)
			return -1;
		s_structure_surface_plane *leaf = &cache_file_tag_resources->surface_planes[surface_index];
		for (long i = 0; i < leaf->plane_count; i++)
		{
			if (leaf->plane_index < 0 || leaf->plane_index >= cache_file_tag_resources->planes.count)
				continue;
			s_structure_plane *surface = &cache_file_tag_resources->planes[i + leaf->plane_index];
			if (surface->cluster_index < 0 || surface->cluster_index >= structure_bsp->clusters.count)
				continue;
			s_structure_cluster *cluster = &structure_bsp->clusters[surface->cluster_index];
			s_mesh *mesh = &geometry->meshes[cluster->mesh_index];
			for (long part_index = 0; part_index < mesh->parts.count; part_index++)
			{
				s_part *part = &mesh->parts[part_index];
				if (surface->index_offset >= part->first_index && surface->index_offset < part->first_index + part->index_count)
					return part->material_index;
			}
		}
	}
	else
	{
		s_structure_instanced_geometry_definition *definition = ((s_structure_instanced_geometry_definition *(*)(long, long))0x4E9640)(structure_bsp_index, structure_bsp->instanced_geometry_instances[instance_index].mesh_index);
		if (surface_index < 0 || surface_index >= definition->surface_planes.count)
			return -1;
		s_structure_surface_plane *leaf = &definition->surface_planes[surface_index];
		if (!definition->surface_planes.count)
			return -1;
		for (long i = 0; i < leaf->plane_count; i++)
		{
			s_structure_plane *surface = &definition->planes[i];
			s_mesh *mesh = &geometry->meshes[definition->mesh_index];
			for (long part_index = 0; part_index < mesh->parts.count; part_index++)
			{
				s_part *part = &mesh->parts[part_index];
				if (surface->index_offset >= part->first_index && surface->index_offset < part->first_index + part->index_count)
					return part->material_index;
			}
		}
	}
	return -1;
}

bool part_is_renderable_hook(s_part const *part, s_geometry_material const *materials) // 0x108F06E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?part_is_renderable_hook@@YA_NPBUs_part@@PBUs_geometry_material@@@Z");

	if (part->material_index == -1 || materials[part->material_index].render_method.index == -1)
	{
		return false;
	}

	if (part->type == _part_type_lightmap_only || part->type == _part_type_unknown6)
	{
		return false;
	}

	return true;
}

void muffins_render_opaque(short datum_index, e_entry_point entry_point) // 0x108F0190
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?muffins_render_opaque@@YAXFW4e_entry_point@@@Z");

	void (*const set_render_object_shader_extern_info)(__int32, s_shader_extern_info *) = reinterpret_cast<void (*)(__int32, s_shader_extern_info *)>(0xA3CC20);
	void (*const sub_A528C0)(s_render_lighting *, e_entry_point) = reinterpret_cast<void (*)(s_render_lighting *, e_entry_point)>(0xA528C0);
	void (*const render_mesh_submit_matrices)(real_matrix4x3 *, long) = reinterpret_cast<void (*)(real_matrix4x3 *, long)>(0xA47A10);
	bool (*const sub_A47430)(s_part *, s_geometry_material *) = reinterpret_cast<bool (*)(s_part *, s_geometry_material *)>(0xA47430);
	tls_data *tls = (tls_data *)tls_get(0);
	char *muffin_array = (char *)tls->muffin->address;
	s_muffin_datum *muffin = (s_muffin_datum *)(muffin_array + datum_index * 0x1890);
	s_muffin_definition *const muffin_definition = s_muffin_definition::get(muffin->tag_index);
	long cached_render_state_index = ((long (*)(long))0xA43AC0)(muffin->object_index);
	if (cached_render_state_index != -1 && muffin_definition->render_model.index != -1)
	{
		s_render_model *const render_model = (s_render_model *)tag_get('mode', muffin_definition->render_model.index);
		((void (*)(s_compression_info const *))0xA47890)(&render_model->render_geometry.compression[0]);
		s_object_cached_render_state_datum *cached_object_render_state = tls->cached_object_render_states->try_and_get(cached_render_state_index);
		set_render_object_shader_extern_info(global_structure_bsp_first_active_index_get(), &cached_object_render_state->shader_extern_info);
		sub_A528C0(&cached_object_render_state->render_lighting, entry_point);
		for (__int32 i = 0; i < muffin->muffin_count; i++)
		{
			s_muffin *muffin_part = &muffin->muffins[i];
			if (muffin_part->flags & 2)
			{
				render_mesh_submit_matrices(&muffin_part->render_matrix, 2);
				s_mesh *const mesh = &render_model->render_geometry.meshes[muffin_part->mesh_index];
				for (__int32 j = 0; j < mesh->parts.count; j++)
				{
					s_part *const mesh_part = &mesh->parts[j];
					if (sub_A47430(mesh_part, &render_model->materials[0]))
					{
						long long identifier = (long long)((long)&render_model->render_geometry >> 31) + muffin_part->mesh_index + ((long long)j << 16);
						identifier += (long)&render_model->render_geometry;
						((void (*)(long long, s_render_geometry *, s_mesh *, s_part *, e_entry_point, long, s_geometry_material *))0xA475A0)(identifier, &render_model->render_geometry, mesh, mesh_part, entry_point, 0, &render_model->materials[0]);
					}
				}
			}
		}
	}
}

bool mesh_get_data_hook(s_render_geometry *render_geometry, long mesh_index, void const **out_vertex_data, void const **out_index_data, unsigned char *out_vertex_stride, long *out_vertex_count, long *out_index_count) // 0x108F0070
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?mesh_get_data_hook@@YA_NPAUs_render_geometry@@JPAPBX1PAEPAJ3@Z");

	s_mesh *mesh = &render_geometry->meshes[mesh_index];
	c_rasterizer_vertex_buffer *vertex_buffer = ((c_rasterizer_vertex_buffer *(__cdecl *)(s_render_geometry *, long))0x78c930)(render_geometry, mesh->vertex_buffer_indices[0]);
	c_rasterizer_index_buffer *index_buffer = ((c_rasterizer_index_buffer *(__cdecl *)(s_render_geometry *, long))0x78c870)(render_geometry, mesh->index_buffer_indices[0]);
	*out_vertex_data = vertex_buffer->get_data();
	*out_vertex_stride = vertex_buffer->get_vertex_stride();
	*out_vertex_count = vertex_buffer->get_vertex_count();
	*out_index_data = index_buffer->get_data();
	*out_index_count = index_buffer->get_index_count();
	return false;
}

bool render_method_submit_particle_gpu_emitter_render_hook(long tag_index, c_render_method const *render_method, e_vertex_type vertex_type, e_prt_vertex_type prt_type, e_entry_point entry_point, bool a6) // 0x108F16F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_method_submit_particle_gpu_emitter_render_hook@@YA_NJPBVc_render_method@@W4e_vertex_type@@W4e_prt_vertex_type@@W4e_entry_point@@_N@Z");

	c_render_method_template *rmt2 = c_render_method_template::get((*reinterpret_cast<c_tag_block<s_render_method_postprocess_definition> const *>(reinterpret_cast<char const *>(render_method) + 0x28))[0].render_method_template.index);
	__int32 is_normal_basemap = 1;
	for (__int32 i = 0; i < rmt2->textures.count; i++)
	{
		if (strncmp(Blam::Cache::StringIDCache::GetCurrent()->GetString(rmt2->textures[i].parameter_name), "base_map", 8) == 0)
		{
			if ((*reinterpret_cast<c_tag_block<s_render_method_postprocess_definition> const *>(reinterpret_cast<char const *>(render_method) + 0x28))[0].texture_constants[i].extern_mode != _extern_mode_none)
			{
				is_normal_basemap = 0;
			}
			else if ((*reinterpret_cast<c_tag_block<s_render_method_postprocess_definition> const *>(reinterpret_cast<char const *>(render_method) + 0x28))[0].texture_constants[i].bitmap.index != 0xFFFF)
			{
				s_bitmap_definition *bitmap = (s_bitmap_definition *)tag_get('bitm', (*reinterpret_cast<c_tag_block<s_render_method_postprocess_definition> const *>(reinterpret_cast<char const *>(render_method) + 0x28))[0].texture_constants[i].bitmap.index);
				if (!bitmap->images.count || bitmap->images[0].format != _bitmap_format_dxn && bitmap->images[0].format != _bitmap_format_dxt5nm)
					is_normal_basemap = 0;
			}
			break;
		}
	}
	((void (*)(long, long, __int32 *))0xA66370)(14, 1, &is_normal_basemap);
	return ((bool (*)(long, c_render_method const *, e_vertex_type, e_prt_vertex_type, e_entry_point, bool))0xA3CA60)(tag_index, render_method, vertex_type, prt_type, entry_point, a6);
}

bool sub_610230__ssao_call_hook() // 0x108F6CD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sub_610230__ssao_call_hook@@YA_NXZ");

	bool (__cdecl *const sub_610230)() = (bool(__cdecl *const)())0x610230;

	if (!Modules::ModuleSettings::Instance().VarSsao->ValueInt)
	{
		return true;
	}
	else
	{
		return sub_610230();
	}
}

void c_render_shield__render_object_internal_hook(s_render_object_info *info, s_render_object_mesh_part *data, shield_impact_definition *shield_impact, float recent_shield_damage, float current_shield_damage, float unknown_amount, float overshield_amount, float t) // 0x108E8BE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_render_shield__render_object_internal_hook@@YAXPAUs_render_object_info@@PAUs_render_object_mesh_part@@PAUshield_impact_definition@@MMMMM@Z");

	void (*const c_render_shield__render_object_internal)(s_render_object_info *, s_render_object_mesh_part *, shield_impact_definition *, float, float, float, float, float) = reinterpret_cast<void (*)(s_render_object_info *, s_render_object_mesh_part *, shield_impact_definition *, float, float, float, float, float)>(0xA53AC0);
	s_render_model *render_model = (s_render_model *)tag_get(0x6D6F6465, data->info->info.render_model_index);
	s_mesh const *mesh = &render_model->render_geometry.meshes[data->mesh_index];
	s_part const *part = &mesh->parts[data->part_index];
	if (part->flags & 0x10)
		return;
	c_render_shield__render_object_internal(info, data, shield_impact, recent_shield_damage, current_shield_damage, unknown_amount, overshield_amount, t);
}

void __fastcall c_dynamic_cubemap_sample__search_for_cubemap_sample_in_cluster_hook(c_dynamic_cubemap_sample *thisptr, void *__formal, s_cluster_reference test_location, real_point3d *test_point, float tolerance) // 0x108E4A80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_dynamic_cubemap_sample__search_for_cubemap_sample_in_cluster_hook@@YIXPAUc_dynamic_cubemap_sample@@PAXUs_cluster_reference@@PAUreal_point3d@@M@Z");

	s_structure_cluster *test_cluster;
	s_structure_cluster *old_cluster;
	s_structure_cluster_cubemap_info *best_cubemap_info;
	s_structure_cluster_cubemap_info *old_cubemap_info;
	s_scenario_structure_bsp *test_structure_bsp;
	s_scenario_structure_bsp *old_structure_bsp;
	float distance;
	float old_distance;
	float best_distance;
	long best_index;
	long best_reference_index;
	bool is_better;
	if (test_location.bsp_index == -1)
		return;
	test_structure_bsp = global_structure_bsp_get(test_location.bsp_index);
	test_cluster = &test_structure_bsp->clusters[test_location.cluster_index];
	old_cubemap_info = nullptr;
	if (thisptr->cubemap0_location.bsp_index != -1 && thisptr->cubemap0_index != -1)
	{
		old_structure_bsp = global_structure_bsp_get(thisptr->cubemap0_location.bsp_index);
		if (old_structure_bsp && thisptr->cubemap0_location.cluster_index < old_structure_bsp->clusters.count)
		{
			old_cluster = &old_structure_bsp->clusters[thisptr->cubemap0_location.cluster_index];
			if (thisptr->cubemap0_index < old_cluster->cubemaps.count)
				old_cubemap_info = &old_cluster->cubemaps[thisptr->cubemap0_index];
		}
	}
	best_distance = 3.40282347e+38f;
	best_cubemap_info = nullptr;
	best_index = -1;
	best_reference_index = -1;
	for (long i = 0; i < test_cluster->cubemaps.count; i++)
	{
		s_structure_cluster_cubemap_info *cubemap_info = &test_cluster->cubemaps[i];
		for (long j = 0; j < cubemap_info->reference_points.count; j++)
		{
			s_cubemap_reference_point *reference = &cubemap_info->reference_points[j];
			distance = distance_squared3d(&reference->point, test_point);
			if (best_distance > distance)
			{
				best_distance = distance;
				best_cubemap_info = cubemap_info;
				best_index = i;
				best_reference_index = j;
			}
		}
	}
	if (best_cubemap_info)
	{
		if (old_cubemap_info && thisptr->cubemap0_location == test_location)
		{
			old_distance = distance_squared3d(&old_cubemap_info->reference_points[thisptr->cubemap0_reference_index].point, test_point);
			is_better = (1.0f - tolerance) * (1.0f - tolerance) * old_distance > best_distance;
		}
		else
		{
			is_better = true;
		}
	}
	else
	{
		is_better = false;
	}
	if (is_better && best_cubemap_info)
	{
		thisptr->cubemap1_location = thisptr->cubemap0_location;
		thisptr->cubemap1_index = thisptr->cubemap0_index;
		thisptr->cubemap1_reference_index = thisptr->cubemap0_reference_index;
		thisptr->cubemap1_bitmap_index = thisptr->cubemap0_bitmap_index;
		thisptr->cubemap0_location = test_location;
		thisptr->cubemap0_index = (char)best_index;
		thisptr->cubemap0_reference_index = (char)best_reference_index;
		thisptr->cubemap0_bitmap_index = best_cubemap_info->cubemap_bitmap_index;
		thisptr->blend = 0.0f;
		if (thisptr->cubemap1_index == -1 || !old_cubemap_info)
		{
			thisptr->cubemap1_location = thisptr->cubemap0_location;
			thisptr->cubemap1_index = thisptr->cubemap0_index;
			thisptr->cubemap1_bitmap_index = thisptr->cubemap0_bitmap_index;
			thisptr->cubemap1_reference_index = thisptr->cubemap0_reference_index;
			thisptr->blend = 1.0f;
		}
	}
}

float render_projection_sphere_diameter_in_pixels_hook(s_render_projection const *render_projection, real_point3d const *center, float radius) // 0x108F5BB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_projection_sphere_diameter_in_pixels_hook@@YAMPBUs_render_projection@@PBUreal_point3d@@M@Z");

	float distance = fabsf(render_projection->world_to_view.left.k * center->y + render_projection->world_to_view.forward.k * center->x + render_projection->world_to_view.up.k * center->z + render_projection->world_to_view.position.z);

	if (distance <= 0.1)
		distance = 0.1f;

	float scale = render_projection->scale_height;

	if (((bool(__cdecl *)())0x67d270)() && !((bool(__cdecl *)())0xa1fc90)())
		scale = scale * 1.3329999;

	scale = scale * g_lod_distance_scale;

	return radius * 2.0 * scale / distance;
}

void bink_playback_allocate_framebuffers_hook() // 0x108E49D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?bink_playback_allocate_framebuffers_hook@@YAXXZ");

	void (*const bink_playback_allocate_framebuffers)() = reinterpret_cast<void (*)()>(0x6165A0);
	Utils::Singleton<Modules::ModuleSettings>::Instance().GetScreenResolution(g_bink_frame_width, g_bink_frame_height);
	bink_playback_allocate_framebuffers();
}

void __fastcall c_player_view__render_hook(c_player_view *view) // 0x108E6C50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_view__render_hook@@YIXPAUc_player_view@@@Z");

	s_screen_effect_settings screen_effect;
	s_screen_effect_shader_sample_result screen_effect_shader_sample;
	s_weighted_atmosphere_parameters atmosphere_parameters;
	s_cluster_reference cluster_reference;
	short_rectangle2d window_bounds;
	screen_effect_sample(&view->rasterizer_camera.position, &view->rasterizer_camera.forward, &screen_effect, &screen_effect_shader_sample, view->out_user_index);
	c_surface__g_current_splitscreen_res = view->splitscreen_res;
	if (!eldorado::game_engine_suppress_render_scene(view->out_user_index))
	{
		eldorado::render_method_clear_externs();
		((s_cluster_reference (__thiscall *)(c_player_view *, s_cluster_reference *))0xA28B50)(view, &cluster_reference);
		eldorado::c_atmosphere_fog_interface_compute_cluster_weights(cluster_reference, &view->rasterizer_camera.position);
		float fov_rad = Modules::ModuleCamera::Instance().VarCameraFov->ValueFloat * 0.017453292f;
		float horizontal_fov = fmax(fov_rad / 1.3962634f, 0.000099999997f);
		g_particle_hack_near_fade_scale = 1.0f / horizontal_fov;
		((void (*const)(long))0xA793E0)(view->out_user_index);
		((void (*const)(long))0xA67B30)(view->out_user_index);
		unsigned char a2 = 2;
		((void (*const)(long, unsigned char *))0x5BD0D0)(view->out_user_index, &a2);
		bool should_render_render = eldorado::c_water_renderer_update_water_part_list();
		if (should_render_render && render_water_interaction_enabled && eldorado::c_water_renderer_is_active_ripple_exist())
		{
			eldorado::c_water_renderer_ripple_apply();
			eldorado::c_water_renderer_ripple_slope();
		}
		eldorado::chud_draw_turbulence(view->out_user_index);
		screen_effect_set_hud_alpha_scale(1.0 - fminf(fmaxf(screen_effect.hud_fade, 0.0f), 1.0f));
		if (screen_effect.tron <= 0.0f)
		{
			render_debug_depth_render = 0;
			c_player_view::render_debug_depth_render_alpha = 1.0f;
		}
		else
		{
			render_debug_depth_render = -2;
			c_player_view::render_debug_depth_render_alpha = screen_effect.tron;
		}
		((void (__thiscall *)(c_player_view *, float))0xA3B990)(view, screen_effect.exposure_boost - screen_effect.exposure_deboost);
		Forge::CForgeCameraFx::OverrideCameraFxSettings(view, screen_effect.exposure_boost - screen_effect.exposure_deboost);
		eldorado::c_player_view_setup_cinematic_clip_planes();
		((long (__thiscall *)(c_lights_view *, long))0xA66A20)(&view->lights_view, view->out_user_index);
		((void (__thiscall *)(c_lights_view *, long))0xA669E0)(&view->lights_view, view->window_index);
		c_atmosphere_fog_interface::g_custom_setting_index = -1;
		memset(&atmosphere_parameters, 0, sizeof(atmosphere_parameters));
		if (!Forge::CForgeAtmosphere::OverrideSkyAtmosphereSettings(cluster_reference, &atmosphere_parameters))
			eldorado::c_atmosphere_fog_interface_populate_atmosphere_parameters(cluster_reference, &atmosphere_parameters);
		memcpy(&g_atmosphere_parameters, &atmosphere_parameters, sizeof(atmosphere_parameters));
		c_atmosphere_fog_interface::g_custom_setting_index = -2;
		((void (*const)(s_weighted_atmosphere_parameters *, bool, bool))0x674170)(&g_atmosphere_parameters, true, true);
		if (c_atmosphere_fog_interface::g_custom_setting_index != -2)
		{
			c_atmosphere_fog_interface::g_custom_setting_index = -2;
			((void (*const)(s_weighted_atmosphere_parameters *, bool, bool))0x674170)(&g_atmosphere_parameters, true, true);
		}
		eldorado::rasterizer_stipple_initialize();
		eldorado::c_decal_system_submit_all();
		bool render_albedo = ((bool (__thiscall *)(c_player_view *))0xA3A0E0)(view);
		if (render_albedo)
		{
			bool v10 = c_screen_postprocess__x_settings.field_0 || eldorado::screenshot_in_progress();
			eldorado::c_rasterizer_set_using_albedo_sampler(true);
			if (!eldorado::screenshot_in_progress())
			{
				eldorado::c_rasterizer_setup_occlusion_state();
				eldorado::lens_flares_submit_occlusions(view->out_user_index, true);
			}
			if (view->flush_device_queries)
			{
				eldorado::c_cpu_gpu_synchronizer_wait_for_gpu_to_catch_up();
				view->flush_device_queries = false;
			}
			if (render_static_lighting_enabled)
				((void (__thiscall *)(c_player_view *))0xA3A8C0)(view);
			if (render_dynamic_shadow_enabled)
			{
				float sm_ps = 1.0f / Modules::ModuleSettings::Instance().VarShadowResolution->ValueInt;
				real_vector4d shadow_map_pixel_size;
				shadow_map_pixel_size.i = sm_ps;
				shadow_map_pixel_size.j = sm_ps;
				shadow_map_pixel_size.k = 0.0f;
				shadow_map_pixel_size.w = 0.0f;
				eldorado::c_rasterizer_set_pixel_shader_constant(214, 1, &shadow_map_pixel_size);
				((void (__thiscall *)(c_player_view *))0xA3A700)(view);
				eldorado::c_rasterizer_setup_targets_static_lighting(view->exposure, view->bloom_intensity, true, c_camera_fx_values__g_HDR_target_stops, false, false, false);
				c_render_surface *v4 = ((c_render_surface *(__thiscall *)(c_surface_group *, e_surface))0xA48740)(&((c_surface_group *)0x510D8D0)[7], (e_surface)7);
				c_render_surface *v5 = ((c_render_surface *(__thiscall *)(c_surface_group *, e_surface))0xA48740)(&((c_surface_group *)0x510D8D0)[8], (e_surface)8);
				c_render_surface *v6 = ((c_render_surface *(__thiscall *)(c_surface_group *, e_surface))0xA48740)(&((c_surface_group *)0x510D8D0)[4], (e_surface)4);
				((void (__thiscall *)(c_lights_view *, long, long, IDirect3DSurface9 *, IDirect3DSurface9 *, IDirect3DSurface9 *))0xA67060)(&view->lights_view, view->out_user_index, view->window_index, v4->m_surface, v5->m_surface, v6->m_surface);
			}
			if (byte_191C922)
			{
				eldorado::c_rasterizer_setup_targets_static_lighting(view->exposure, view->bloom_intensity, v10, c_camera_fx_values__g_HDR_target_stops, false, false, true);
				if (render_debug_depth_render == 0)
					((void (__thiscall *)(c_player_view *, bool))0xA3A420)(view, false);
				if (eldorado::c_rasterizer_get_is_tiling_enabled())
					eldorado::c_tron_effect_resolve_and_process_z_camera(view->window_index, &view->rasterizer_camera.window_pixel_bounds);
				if (eldorado::screenshot_allow_postprocess())
					eldorado::c_screen_postprocess_postprocess_ssr(&view->rasterizer_projection, &view->rasterizer_camera, 7, 8, 12, 23, 11, 13, 14, 18, 19, 20, 17, 15);
				eldorado::c_rasterizer_setup_targets_static_lighting(view->exposure, view->bloom_intensity, v10, c_camera_fx_values__g_HDR_target_stops, false, false, false);
				if (should_render_render || render_water_wireframe_enabled)
					eldorado::c_player_view_render_water();
				if (*(bool *)offset_pointer(tls_getd().rasterizer_game_states, 2))
					((void (__thiscall *)(c_player_view *))0xA39860)(view);
				((void (__thiscall *)(c_player_view *))0xA3B380)(view);
				((void (__thiscall *)(c_player_view *))0xA3BDF0)(view);
				eldorado::c_render_globals_set_distortion_history(eldorado::get_distortion_visible() || should_render_render || render_water_wireframe_enabled);
				eldorado::game_engine_render(view->out_user_index);
				c_player_view::apply_distortions_new(view, &screen_effect.motion_suck_direction, Modules::ModuleSettings::Instance().VarMotionBlurAlways->ValueInt > 0);
				if (render_debug_depth_render == 0)
				{
					eldorado::c_rasterizer_setup_targets_static_lighting_alpha_blend(v10);
					((void (__thiscall *)(c_player_view *, bool))0xA3A420)(view, true);
				}
				eldorado::c_rasterizer_setup_targets_static_lighting_alpha_blend(v10);
				((void (__thiscall *)(c_player_view *))0xA3A6C0)(view);
				if (!eldorado::screenshot_in_progress())
				{
					eldorado::c_rasterizer_setup_occlusion_state();
					eldorado::lens_flares_submit_occlusions(view->out_user_index, false);
				}
				if (eldorado::chud_generate_damage_flash_texture(view->out_user_index))
				{
					eldorado::c_rasterizer_setup_targets_static_lighting_alpha_blend(false);
					eldorado::c_rasterizer_setup_render_target_globals_with_exposure(1.0f, 1.0f, 1.0f);
					eldorado::c_rasterizer_set_render_target(1, (e_surface)0, -1);
					eldorado::chud_draw_screen_LDR(view->out_user_index);
				}
				eldorado::render_setup_window(&view->rasterizer_camera, &view->rasterizer_projection);
				eldorado::c_rasterizer_setup_targets_static_lighting(view->exposure, view->bloom_intensity, true, c_camera_fx_values__g_HDR_target_stops, false, false, false);
				((void (__thiscall *)(c_player_view *))0xA3B500)(view);
			}
			if (eldorado::screenshot_allow_postprocess())
				eldorado::c_screen_postprocess_postprocess_player_view(&view->player_window_game_state->camera_fx_values, &view->rasterizer_projection, &view->rasterizer_camera, &screen_effect, view->splitscreen_res, &view->observer_depth_of_field, view->out_user_index);
		}
		else if (view->flush_device_queries)
		{
			eldorado::c_cpu_gpu_synchronizer_wait_for_gpu_to_catch_up();
			view->flush_device_queries = false;
		}
	}
	if (eldorado::screenshot_allow_ui_render())
	{
		eldorado::c_rasterizer_restore_last_viewport();
		eldorado::c_rasterizer_restore_last_scissor_rect();
		eldorado::c_rasterizer_setup_render_target_globals_with_exposure(1.0f, 1.0f, 1.0f);
		if (Forge::CForgeVisionRenderer::IsActive())
			Forge::CForgeVisionRenderer::Render(view->window_index, view);
		if (screen_effect.vision_mode <= 0.0f)
			eldorado::sub_14E56A0(view->window_index, view);
		else
			eldorado::vision_mode_render(view->window_index, view, screen_effect.vision_mode, *(float *)offset_pointer(tls_getd().main_render_timing, 12), screen_effect.vision_noise, 0, 0);
		eldorado::render_screen_shaders(&screen_effect_shader_sample, true, eldorado::c_rasterizer_get_display_surface(), 0, 0);
		eldorado::chud_draw_screen(view->out_user_index);
		eldorado::game_engine_render_fade_to_black(view->out_user_index);
		eldorado::interface_get_current_window_settings(0, 0, &window_bounds, 0);
		eldorado::user_interface_render(view->controller_index, view->out_user_index, view->window_index, &window_bounds, eldorado::c_rasterizer_get_display_surface(), 0);
		c_screen_postprocess::render_screen_effect_blur(screen_effect.horizontal_blur, screen_effect.vertical_blur);
		eldorado::game_engine_render_watermarks();
		eldorado::chud_draw_screen_saved_film(view->out_user_index);
		eldorado::render_screen_shaders(&screen_effect_shader_sample, false, eldorado::c_rasterizer_get_display_surface(), 0, 0);
		eldorado::player_effect_render(view->out_user_index);
	}
	eldorado::game_engine_render_debug(view->out_user_index);
	Patches::Debug::RenderPlayerView();
	if (!eldorado::screenshot_sub_610260())
		eldorado::render_debug_window_render(view->out_user_index);
	eldorado::c_rasterizer_end();
}

void __fastcall c_player_view__render_lightmap_shadows_hook(c_player_view *_this, void *__savedreg) // 0x108E80F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_view__render_lightmap_shadows_hook@@YIXPAUc_player_view@@PAX@Z");

	void (__thiscall *const c_player_view__render_lightmap_shadows)(c_player_view *) = (void(__thiscall *const)(c_player_view *))0xa3a700;
	float sm_ps = 1.0f / Utils::Singleton<Modules::ModuleSettings>::Instance().VarShadowResolution->ValueInt;
	real_vector4d shadow_map_pixel_size;

	shadow_map_pixel_size.i = sm_ps;
	shadow_map_pixel_size.j = sm_ps;
	shadow_map_pixel_size.k = 0.0f;
	shadow_map_pixel_size.w = 0.0f;

	((void(__cdecl *)(long, long, real_vector4d const *))0xa66270)(214, 1, &shadow_map_pixel_size);

	c_player_view__render_lightmap_shadows(_this);
}

void __fastcall c_texture_camera_view__render_hook(c_texture_camera_view *thisptr) // 0x108EBB90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_texture_camera_view__render_hook@@YIXPAUc_texture_camera_view@@@Z");

	bool (*const bitmap_group_try_get_texture)(long, long, c_rasterizer_texture_ref *) = reinterpret_cast<bool (*)(long, long, c_rasterizer_texture_ref *)>(0x718D10);
	void (*const s_color_grading_parameter__update)(s_camera_fx_color_grading_struct *, bool, char) = reinterpret_cast<void (*)(s_camera_fx_color_grading_struct *, bool, char)>(0xA6FDD0);
	void (__thiscall *const c_texture_camera_view__copy_texture)(c_texture_camera_view *, c_enum<long,enum e_rasterizer_default_shader>, c_rasterizer_texture_ref, c_rasterizer_texture_ref, float, float, bool) = reinterpret_cast<void (__thiscall *)(c_texture_camera_view *, c_enum<long,enum e_rasterizer_default_shader>, c_rasterizer_texture_ref, c_rasterizer_texture_ref, float, float, bool)>(0xA707B0);
	bool byte_19186F4 = *(bool *)0x19186F4;
	float *g_texture_camera_exposure = (float *)0x19186E4;
	float dword_19186F8 = *(float *)0x19186F8;
	float dword_19186EC = *(float *)0x19186EC;
	float dword_19186F0 = *(float *)0x19186F0;
	eldorado::c_view_begin(thisptr);
	eldorado::render_method_clear_externs();
	eldorado::c_rasterizer_set_render_target(2, (e_surface)0, -1);
	eldorado::c_rasterizer_set_render_target(3, (e_surface)0, -1);
	if (thisptr->flags & 0x20)
	{
		((long (__thiscall *)(c_lights_view *, long))0xA66A20)(&thisptr->lights_view, 0);
		thisptr->lights_view.global_light_intensity = tls_getd().scripted_exposure_globals->exposure.field_4 * c_lights_view::g_render_light_intensity;
		if (thisptr->flags & 0x200)
			((void (__thiscall *)(c_lights_view *, long))0xA669E0)(&thisptr->lights_view, 0);
		eldorado::c_rasterizer_end_high_quality_blend();
		((long (*const)(long, c_rasterizer_texture_ref, long, long))0xA48DD0)(0, thisptr->albedo_texture, 0, 0);
		((long (*const)(long, c_rasterizer_texture_ref, long, long))0xA48DD0)(1, thisptr->normal_texture, 0, 0);
		((void (*const)(bool))0xA48EB0)(false);
		eldorado::c_rasterizer_set_depth_stencil_surface(thisptr->depth_stencil_surface);
		{
			long width = 0;
			long height = 0;
			((bool (__thiscall *)(c_rasterizer_texture_ref *, long, long *, long *))0xA6E950)(&thisptr->accum_texture, 0, &width, &height);
			short_rectangle2d viewport = { 0, 0, (short)height, (short)width };
			eldorado::c_rasterizer_set_viewport(&viewport, 0.0f, 1.0f);
		}
		eldorado::c_rasterizer_clear(thisptr->flags & 1 | 2, 0, 1.0f, 0);
		if (thisptr->flags & 8)
			eldorado::c_object_renderer_render_albedo(1);
		if (thisptr->flags & 4)
			eldorado::c_structure_renderer_render_albedo();
		if (thisptr->flags & 8)
			eldorado::c_object_renderer_submit_and_render_sky(0, thisptr->window_index);
		eldorado::c_player_view_render_albedo_decals((thisptr->flags & 8) != 0, 0);
		eldorado::c_rasterizer_begin_high_quality_blend();
		((long (*const)(long, c_rasterizer_texture_ref, long, long))0xA48DD0)(0, thisptr->accum_texture, thisptr->cubemap_face, 0);
		c_rasterizer::m_albedo_texture = thisptr->albedo_texture;
		c_rasterizer::m_normal_texture = thisptr->normal_texture;
		eldorado::render_method_submit_single_extern((e_render_method_extern)1, false);
		eldorado::render_method_submit_single_extern((e_render_method_extern)2, false);
		eldorado::c_rasterizer_set_render_target(1, (e_surface)0, -1);
		if (thisptr->unknown_object_index != -1 || thisptr->flags & 2)
			eldorado::c_rasterizer_clear(1, 0, 1.0f, 0);
		eldorado::c_rasterizer_setup_render_target_globals_with_exposure(g_texture_camera_exposure[0], g_texture_camera_exposure[1], 7.0f);
		eldorado::c_rasterizer_end_high_quality_blend();
		((void (*const)(bool))0xA48EB0)(true);
		((void (*const)(s_simple_light *, long))0xA67B90)(thisptr->lights_view.m_simple_lights, thisptr->lights_view.m_simple_light_count);
		eldorado::c_rasterizer_set_using_albedo_sampler(true);
		if (thisptr->flags & 8)
			((void (*const)(unsigned long))0xA79060)(1);
		if (thisptr->flags & 4)
			((void (*const)())0xA2FC90)();
		if (thisptr->flags & 8)
			eldorado::c_object_renderer_submit_and_render_sky(1, thisptr->window_index);
		eldorado::c_rasterizer_begin_high_quality_blend();
	}
	else if (thisptr->flags & 0x40)
	{
		((long (*const)(long, c_rasterizer_texture_ref, long, long))0xA48DD0)(0, thisptr->accum_texture, thisptr->cubemap_face, 0);
		eldorado::c_rasterizer_set_depth_stencil_surface(thisptr->depth_stencil_surface);
		eldorado::c_rasterizer_clear(3, -1, 1.0f, 0);
		if (thisptr->flags & 4)
			((long (*const)(long))0xA2FC30)(3);
		if (thisptr->flags & 8)
			((void (*const)(long, long))0xA78F00)(3, 2);
	}
	if (thisptr->flags & 0x200)
	{
		c_render_surface *depth_surface = eldorado::c_render_surfaces_interface_get_render_surface(thisptr->depth_stencil_surface);
		IDirect3DSurface9 *accum_surface = ((IDirect3DSurface9 *(__thiscall *)(c_rasterizer_texture_ref *, long, long))0xA6E860)(&thisptr->accum_texture, 0, thisptr->cubemap_face);
		((void (__thiscall *)(c_lights_view *, long, long, IDirect3DSurface9 *, IDirect3DSurface9 *, IDirect3DSurface9 *))0xA67060)(&thisptr->lights_view, thisptr->out_user_index, thisptr->window_index, accum_surface, nullptr, depth_surface->m_surface);
	}
	if (thisptr->flags & 0x100)
		c_player_view__render_lightmap_shadows_hook(thisptr, nullptr);
	if (thisptr->flags & 0x20 && thisptr->flags & 0x80)
	{
		eldorado::render_method_submit_single_extern((e_render_method_extern)3, false);
		eldorado::render_method_submit_single_extern((e_render_method_extern)1, true);
		eldorado::render_method_submit_single_extern((e_render_method_extern)2, true);
		((void (*const)(s_simple_light *, long))0xA67B90)(thisptr->lights_view.m_simple_lights, thisptr->lights_view.m_simple_light_count);
		eldorado::c_rasterizer_set_using_albedo_sampler(false);
		eldorado::c_object_renderer_submit_and_render_sky(2, thisptr->window_index);
		eldorado::c_transparency_renderer_sort();
		eldorado::c_transparency_renderer_render(true);
		eldorado::c_rasterizer_set_using_albedo_sampler(true);
	}
	if (thisptr->flags & 0x800 && thisptr->unknown_callback)
		thisptr->unknown_callback(thisptr->unknown_callback_context);
	long width;
	long height;
	((bool (__thiscall *)(c_rasterizer_texture_ref *, long, long *, long *))0xA6E950)(&thisptr->accum_texture, 0, &width, &height);
	eldorado::c_rasterizer_set_alpha_blend_mode(0);
	eldorado::c_rasterizer_set_cull_mode(1);
	eldorado::c_rasterizer_set_scissor_rect(nullptr);
	eldorado::c_rasterizer_set_z_buffer_mode(2);
	eldorado::c_rasterizer_set_color_write_enable(0, 15);
	c_texture_camera_view__copy_texture(thisptr, (e_rasterizer_default_shader)51, thisptr->normal_texture, thisptr->accum_texture, (float)width, (float)height, true);
	eldorado::c_rasterizer_set_alpha_blend_mode(0);
	eldorado::c_rasterizer_set_color_write_enable(0, 15);
	((long (*const)(long, c_rasterizer_texture_ref, long, long))0xA48DD0)(0, thisptr->albedo_texture, 0, 0);
	eldorado::c_rasterizer_clear(1, 0, 1.0f, 0);
	s_screen_effect_settings screen_effect;
	s_screen_effect_shader_sample_result shader_sample_result;
	screen_effect_sample(&thisptr->rasterizer_camera.position, &thisptr->rasterizer_camera.forward, &screen_effect, &shader_sample_result, -1);
	((void (__thiscall *)(s_hue_saturation_control *, float, float, float, real_rgb_color const *, real_rgb_color const *))0xA411A0)(tls_getd().hue_saturation_control, screen_effect.hue_right - screen_effect.hue_left, screen_effect.saturation - screen_effect.desaturation, screen_effect.contrast_enhance, &screen_effect.color_filter, &screen_effect.color_floor);
	float contrast = fminf(fmaxf(screen_effect.gamma_enhance + 1.0f - screen_effect.gamma_reduce, 0.01f), 10.0f);
	real_vector4d p_postprocess_contrast;
	p_postprocess_contrast.i = contrast;
	p_postprocess_contrast.j = contrast;
	p_postprocess_contrast.k = contrast;
	p_postprocess_contrast.w = contrast;
	eldorado::c_rasterizer_set_pixel_shader_constant(222, 1, &p_postprocess_contrast);
	c_camera_fx_settings *camera_fx = c_camera_fx_settings::get(game_globals_get()->DefaultCameraEffect.index);
	s_color_grading_parameter__update(&camera_fx->color_grading, false, 1);
	if (eldorado::c_rasterizer_set_explicit_shaders(18, 7, 0, 0))
	{
		eldorado::c_rasterizer_set_sampler_filter_mode_2(0, (e_sampler_filter_mode)1);
		eldorado::c_rasterizer_set_sampler_filter_mode_2(1, (e_sampler_filter_mode)1);
		eldorado::c_rasterizer_set_sampler_texture(0, thisptr->accum_texture);
		c_rasterizer_texture_ref dark_surface(-1);
		s_rasterizer_globals *const rasg = c_rasterizer_globals::get();
		c_rasterizer_globals::get_default_texture_rasterizer_texture_ref(rasg, &dark_surface, _default_bitmap_color_black_transparent);
		eldorado::c_rasterizer_set_sampler_texture(1, dark_surface);
		eldorado::c_rasterizer_set_sampler_texture(2, -1);
		eldorado::c_rasterizer_set_sampler_texture(3, -1);
		c_rasterizer::get_device()->SetTexture(4, *(IDirect3DBaseTexture9 **)0x5215C34);
		eldorado::c_rasterizer_set_sampler_texture_direct(4, 0);
		eldorado::c_rasterizer_set_sampler_address_mode_2(4, (e_sampler_address_mode)1, (e_sampler_address_mode)1, (e_sampler_address_mode)1);
		eldorado::c_rasterizer_set_sampler_filter_mode_2(4, (e_sampler_filter_mode)2);
		c_rasterizer::get_device()->SetTexture(5, *(IDirect3DBaseTexture9 **)0x5215C34);
		eldorado::c_rasterizer_set_sampler_texture_direct(5, 0);
		eldorado::c_rasterizer_set_sampler_address_mode_2(5, (e_sampler_address_mode)1, (e_sampler_address_mode)1, (e_sampler_address_mode)1);
		eldorado::c_rasterizer_set_sampler_filter_mode_2(5, (e_sampler_filter_mode)2);
		real_vector4d pixel_size;
		pixel_size.i = 1.0f / width;
		pixel_size.j = 1.0f / height;
		pixel_size.k = 0.0f;
		pixel_size.w = 0.0f;
		eldorado::c_rasterizer_set_pixel_shader_constant(1, 1, &pixel_size);
		real_vector4d intensity;
		intensity[0] = dword_19186EC;
		intensity[1] = camera_fx->bloom_intensity.bloom_intensity;
		intensity[2] = camera_fx->bling_intensity.bling_intensity;
		intensity[3] = dword_19186F0;
		eldorado::c_rasterizer_set_pixel_shader_constant(2, 1, &intensity);
		real_vector4d tone_curve_constants;
		if (byte_19186F4)
		{
			tone_curve_constants[0] = 1.4938016f / (1.4938016f / dword_19186F8);
			tone_curve_constants[1] = 1.4938016f / dword_19186F8 * 1.0041494f;
			tone_curve_constants[2] = 1.4938016f / dword_19186F8 * 0.0f * (1.4938016f / dword_19186F8);
			tone_curve_constants[3] = 1.4938016f / dword_19186F8 * -0.15f * (1.493801f / dword_19186F8) * (1.493801f / dword_19186F8);
		}
		else
		{
			tone_curve_constants[0] = 65535.0f;
			tone_curve_constants[1] = 1.4938016f / dword_19186F8;
			tone_curve_constants[2] = 0.0f;
			tone_curve_constants[3] = 0.0f;
		}
		eldorado::c_rasterizer_set_pixel_shader_constant(3, 1, &tone_curve_constants);
		real_vector4d bloom_sampler_xform;
		bloom_sampler_xform.i = 1.0f;
		bloom_sampler_xform.j = 1.0f;
		bloom_sampler_xform.k = 0.0f;
		bloom_sampler_xform.w = 0.0f;
		eldorado::c_rasterizer_set_pixel_shader_constant(5, 1, &bloom_sampler_xform);
		real_vector4d cg_blend_factor;
		cg_blend_factor.i = 1.0f;
		cg_blend_factor.j = 0.0f;
		cg_blend_factor.k = 0.0f;
		cg_blend_factor.w = 0.0f;
		eldorado::c_rasterizer_set_pixel_shader_constant(6, 1, &cg_blend_factor);
		real_vector4d gamma_power_constant;
		gamma_power_constant.i = Modules::ModuleGraphics::Instance().VarGammaPower->ValueFloatMax - Modules::ModuleGraphics::Instance().VarGammaPower->ValueFloat + 1.0f;
		gamma_power_constant.j = 0.0f;
		gamma_power_constant.k = 0.0f;
		gamma_power_constant.w = 0.0f;
		eldorado::c_rasterizer_set_pixel_shader_constant(8, 1, &gamma_power_constant);
		real_vector4d pixel_space_xform;
		pixel_space_xform[0] = 1.0f;
		pixel_space_xform[1] = 1.0f;
		pixel_space_xform[2] = 0.0f;
		pixel_space_xform[3] = 0.0f;
		eldorado::c_rasterizer_set_vertex_shader_constant(9, 1, &pixel_space_xform);
		c_rasterizer_texture_ref default_noise_texture_ref(-1);
		c_rasterizer_globals::get_default_texture_rasterizer_texture_ref(rasg, &default_noise_texture_ref, _default_bitmap_noise);
		eldorado::c_rasterizer_set_sampler_texture(9, default_noise_texture_ref);
		eldorado::c_rasterizer_set_sampler_address_mode_2(9, 0, 0, 0);
		eldorado::c_rasterizer_set_sampler_filter_mode_2(9, 1);
		long noise_width;
		long noise_height;
		((bool (__thiscall *)(c_rasterizer_texture_ref *, long, long *, long *))0xA6E950)(&default_noise_texture_ref, 0, &noise_width, &noise_height);
		_D3DSURFACE_DESC accum_surface_desc;
		((IDirect3DSurface9 *(__thiscall *)(c_rasterizer_texture_ref *, long, long))0xA6E860)(&thisptr->accum_texture, 0, 0)->GetDesc(&accum_surface_desc);
		unsigned long *random_seed_address = get_local_random_seed_address();
		unsigned long random_seed = 1664525 * *random_seed_address + 1013904223;
		*random_seed_address = random_seed;
		float noise_random1 = HIWORD(random_seed) / 65535.0f;
		random_seed_address = get_local_random_seed_address();
		random_seed = 1664525 * *random_seed_address + 1013904223;
		*random_seed_address = random_seed;
		float noise_random2 = HIWORD(random_seed) / 65535.0f;
		long frame_index = c_render_globals::get_frame_index();
		real_vector4d noise_space_xform;
		noise_space_xform[0] = (float)accum_surface_desc.Width / (float)noise_width;
		noise_space_xform[1] = (float)accum_surface_desc.Height / (float)noise_height;
		noise_space_xform[2] = ((frame_index & 2) * 0.5f + noise_random1) * 0.5f;
		noise_space_xform[3] = (((frame_index + 1) & 2) * 0.5f + noise_random2) * 0.5f;
		eldorado::c_rasterizer_set_vertex_shader_constant(10, 1, &noise_space_xform);
		real_vector4d noise_params;
		noise_params[0] = screen_effect.dark_noise + screen_effect.dark_noise;
		noise_params[1] = screen_effect.bright_noise;
		noise_params[2] = 1.0 - screen_effect.dark_noise;
		noise_params[3] = 0.0f;
		eldorado::c_rasterizer_set_pixel_shader_constant(11, 1, &noise_params);
		eldorado::c_rasterizer_draw_fullscreen_quad(width, height);
		eldorado::c_rasterizer_set_sampler_texture(0, -1);
		eldorado::c_rasterizer_set_sampler_texture(1, -1);
		eldorado::c_rasterizer_set_sampler_texture(2, -1);
		eldorado::c_rasterizer_set_sampler_texture(3, -1);
		eldorado::c_rasterizer_set_sampler_texture(4, -1);
		eldorado::c_rasterizer_set_sampler_texture(5, -1);
	}
	eldorado::c_rasterizer_set_sampler_texture(1, thisptr->normal_texture);
	eldorado::c_rasterizer_set_sampler_address_mode_2(1, (e_sampler_address_mode)1, (e_sampler_address_mode)1, (e_sampler_address_mode)1);
	eldorado::c_rasterizer_set_sampler_filter_mode_2(1, (e_sampler_filter_mode)2);
	c_texture_camera_view__copy_texture(thisptr, (e_rasterizer_default_shader)94, thisptr->accum_texture, thisptr->albedo_texture, (float)width, (float)height, true);
	eldorado::c_rasterizer_set_sampler_texture(1, -1);
	c_rasterizer::m_albedo_texture = -1;
	c_rasterizer::m_normal_texture = -1;
	eldorado::render_method_clear_externs();
	eldorado::c_view_end();
}

void __fastcall c_player_view__render_static_lighting(c_player_view *_this, void *_savedreg) // 0x108E8270
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_view__render_static_lighting@@YIXPAUc_player_view@@PAX@Z");

	bool (*const sub_A84D50)() = reinterpret_cast<bool (*)()>(0xA84D50);
	((void (__thiscall *)(c_player_view *))0xA3BD10)(_this);
	((void (*)(s_simple_light *, long))0xA67B90)(_this->lights_view.m_simple_lights, _this->lights_view.m_simple_light_count);
	if (!((bool (*)())0x531E90)() || sub_A84D50())
		((void (*)(long, long))0x5BCF60)(_this->out_user_index, 0);
	if (render_debug_depth_render <= 0)
	{
		if (c_rasterizer_states::initialized)
		{
			((void (*)(long))0xA22D10)(11);
			c_rasterizer_states::set_separate_alpha_blend_enabled(true);
		}
		((void (*)(long))0xA79060)(1);
		((void (*)())0xA2FC90)();
		((void (*)(long, long))0xA79300)(1, _this->window_index);
		if (c_rasterizer_states::initialized)
		{
			c_rasterizer_states::set_separate_alpha_blend_enabled(false);
			((void (*)(long))0xA22D10)(0);
		}
	}
	if (render_debug_depth_render)
	{
		((void (*)(long))0xA63510)(0);
		if (render_debug_depth_render < 0)
			((void (*)(long))0xA22D10)(5);
		if (((bool (*)(long, long, long, long))0xA23300)(abs(render_debug_depth_render) != 1 ? 59 : 54, 7, 0, 0))
		{
			((void (*)(long, long))0xA48F20)(0, 23);
			((void (*)(long, c_enum<e_sampler_address_mode, long>, c_enum<e_sampler_address_mode, long>, c_enum<e_sampler_address_mode, long>))0xA23570)(0, _address_mode_mirror, _address_mode_mirror, _address_mode_mirror);
			((void (*)(long, c_enum<e_sampler_filter_mode, long>))0xA23660)(0, 1);
			real_vector4d scale = { powf(2.0f, c_player_view::render_debug_depth_render_scale_r) * c_player_view::render_debug_depth_render_alpha, powf(2.0f, c_player_view::render_debug_depth_render_scale_g) * c_player_view::render_debug_depth_render_alpha, powf(2.0f, c_player_view::render_debug_depth_render_scale_b) * c_player_view::render_debug_depth_render_alpha, c_player_view::render_debug_depth_render_alpha };
			((void (*)(long, long, real_vector4d const *))0xA66270)(2, 1, &scale);
			__int32 surface_width = ((long (*)(long))0xA48810)(23);
			__int32 surface_height = ((long (*)(long))0xA487A0)(23);
			real_vector4d pixel_size = { 1.0f / surface_width, 1.0f / surface_height, 0.0f, 0.0f };
			((void (*)(long, long, real_vector4d const *))0xA66270)(1, 1, &pixel_size);
			((void (*)(long, long))0xA45EE0)(surface_width, surface_height);
		}
		((void (*)(long))0xA22D10)(0);
	}
	((void (*)(long))0x694810)(1);
}

void __fastcall c_lightmap_shadows_view__render_shadow_apply_call_hook(void *_this, void *_savedreg, float shadow_alpha, float quality_scale) // 0x108E5A10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_lightmap_shadows_view__render_shadow_apply_call_hook@@YIXPAX0MM@Z");

	void (__thiscall *const render_shadow_apply)(void *, float, float) = (void(__thiscall *const)(void *, float, float))0xa6b4b0;

	if (Modules::ModuleSettings::Instance().VarShadowResolution->ValueInt > 0x200)
		render_shadow_apply(_this, shadow_alpha, 1.0f);
	else
		render_shadow_apply(_this, shadow_alpha, quality_scale);
}

void __fastcall c_lightmap_shadows_view__submit_visibility_and_render_call_hook(void *_this, void *_savedreg, float shadow_alpha, float quality_scale, long object_index, long model_tag_index) // 0x108E5AF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_lightmap_shadows_view__submit_visibility_and_render_call_hook@@YIXPAX0MMJJ@Z");

	const auto c_lightmap_shadows_view__submit_visibility_and_render = (void(__thiscall *)(void *, float, float, __int32, long))0xA68F30;

	if (Utils::Singleton<Modules::ModuleSettings>::Instance().VarShadowResolution->ValueInt > 0x200)
	{
		c_lightmap_shadows_view__submit_visibility_and_render(_this, shadow_alpha, 1.0f, object_index, model_tag_index);
	}
	else
	{
		c_lightmap_shadows_view__submit_visibility_and_render(_this, shadow_alpha, quality_scale, object_index, model_tag_index);
	}
}

void rasterizer_wait_for_device_query_hook(long index) // 0x108F08C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?rasterizer_wait_for_device_query_hook@@YAXJ@Z");

	IDirect3DQuery9 **queries = (IDirect3DQuery9 **)0x50DADE4;
	bool *pending = (bool *)0x50DADE0;
	long count = 0;
	unsigned long start_time = system_milliseconds();
	while (queries[index]->GetData(nullptr, 0, D3DGETDATA_FLUSH) == S_FALSE)
	{
		if (count++ >= 10000)
		{
			count = 0;
			if (system_milliseconds() - start_time >= 100)
			{
				break;
			}
		}
	}

	*(pending + index) = false;
}

void c_rasterizer__draw_primitive_up_hook(e_primitive_type primitive_type, unsigned long primitive_count, void const *vertex_data, unsigned long stride) // 0x108E8840
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_rasterizer__draw_primitive_up_hook@@YAXW4e_primitive_type@@KPBXK@Z");

	void (*const c_rasterizer_shaders__submit_cached_shader_constants)() = reinterpret_cast<void (*)()>(0xA66670);
	void (*const c_rasterizer_shaders__clear_cached_vertex_stream)(long) = reinterpret_cast<void (*)(long)>(0xA22CB0);
	++*(long *)0x50DEDE0;
	c_rasterizer_shaders__submit_cached_shader_constants();
	c_rasterizer_shaders__clear_cached_vertex_stream(0);
	*(long *)0x50DAE2C = 0;
	if (primitive_type == 6)
		c_rasterizer::get_device()->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, primitive_count * 4, primitive_count * 2, (void const *)0x50DB218, D3DFMT_INDEX16, vertex_data, stride);
	else
		c_rasterizer::get_device()->DrawPrimitiveUP(((_D3DPRIMITIVETYPE const *)0x19133C0)[primitive_type], primitive_count, vertex_data, stride);
}

void c_rasterizer__end_frame_set_surface_as_texture_call_hook(long sampler, e_surface surface) // 0x108E8A40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_rasterizer__end_frame_set_surface_as_texture_call_hook@@YAXJW4e_surface@@@Z");

	((void (*)(long, e_surface))0xA48F20)(sampler, surface);
	if (c_rasterizer_LUT_control::initialized())
	{
		c_rasterizer::set_DAC_LUT_curve();
		c_rasterizer_LUT_control::set_LUT_texture(1);
		((void (*)(long, c_enum<e_sampler_address_mode, long>, c_enum<e_sampler_address_mode, long>, c_enum<e_sampler_address_mode, long>))0xA23570)(1, _address_mode_clamp, _address_mode_clamp, _address_mode_clamp);
		((void (*)(long, c_enum<e_sampler_filter_mode, long>))0xA23660)(1, _filter_bilinear);
	}
}

void c_rasterizer__end_frame_set_sampler_texture_call_hook(long sampler, c_rasterizer_texture_ref ref) // 0x108E89C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_rasterizer__end_frame_set_sampler_texture_call_hook@@YAXJUc_rasterizer_texture_ref@@@Z");

	((void(__cdecl *)(long, c_rasterizer_texture_ref))0xa23810)(sampler, ref);
	((void(__cdecl *)(long, c_rasterizer_texture_ref))0xa23810)(1, -1);
}

bool c_rasterizer__initialize_after_device_creation_or_reset_call_hook() // 0x108E8B60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_rasterizer__initialize_after_device_creation_or_reset_call_hook@@YA_NXZ");

	const auto c_rasterizer__initialize_after_device_creation_or_reset = (bool(*)())0xA1FD80;

	bool result = c_rasterizer__initialize_after_device_creation_or_reset();

	if (!c_rasterizer_LUT_control::initialize_LUT_textures())
	{
		throw;
	}

	return result;
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

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { s_wind_values &g_wind_values = *reinterpret_cast<s_wind_values *>(0x50FAA6C); }
namespace hades_file_local { bool &g_invalidate_render_cache = *reinterpret_cast<bool *>(0x5106FAF); }
namespace hades_file_local { float g_lod_distance_scale = 1.0f; }
namespace hades_file_local { float g_decorator_distance_scale = 1.0f; }
namespace hades_file_local { bool &render_static_lighting_enabled = *reinterpret_cast<bool *>(0x191C920); }
namespace hades_file_local { bool &byte_191C922 = *reinterpret_cast<bool *>(0x191C922); }
namespace hades_file_local { float &c_camera_fx_values__g_HDR_target_stops = *reinterpret_cast<float *>(0x19134C0); }
namespace hades_file_local { c_screen_postprocess::s_settings &c_screen_postprocess__x_settings = *reinterpret_cast<c_screen_postprocess::s_settings *>(0x1917D18); }
namespace hades_file_local { long &c_surface__g_current_splitscreen_res = *reinterpret_cast<long *>(0x50DCA30); }
namespace hades_file_local { s_weighted_atmosphere_parameters &g_atmosphere_parameters = *reinterpret_cast<s_weighted_atmosphere_parameters *>(0x2497E08); }
namespace hades_file_local { float &g_particle_hack_near_fade_scale = *reinterpret_cast<float *>(0x19147B8); }
namespace hades_file_local { long &render_debug_depth_render = *reinterpret_cast<long *>(0x50FB3FC); }
namespace hades_file_local { bool &render_dynamic_shadow_enabled = *reinterpret_cast<bool *>(0x191C921); }
namespace hades_file_local { bool &render_water_interaction_enabled = *reinterpret_cast<bool *>(0x19146F2); }
namespace hades_file_local { bool &render_water_wireframe_enabled = *reinterpret_cast<bool *>(0x50FAAEC); }
float const &c_lights_view::g_render_light_intensity = *reinterpret_cast<float const *>(0x19180BC);
bool &c_rasterizer_states::initialized = *reinterpret_cast<bool *>(0x1914B84);
long &c_render_method_data::m_context = *reinterpret_cast<long *>(0x19148B0);
bool &c_rasterizer::m_use_floating_point_z_buffer = *reinterpret_cast<bool *>(0x50DAE03);
long &c_rasterizer::g_depth_stencil_surface = *reinterpret_cast<long *>(0x50DB1EC);
c_rasterizer_texture_ref &c_rasterizer::m_albedo_texture = *reinterpret_cast<c_rasterizer_texture_ref *>(0x1910104);
c_rasterizer_texture_ref &c_rasterizer::m_normal_texture = *reinterpret_cast<c_rasterizer_texture_ref *>(0x1910108);
float &c_player_view::render_debug_depth_render_scale_r = *reinterpret_cast<float *>(0x19147BC);
float &c_player_view::render_debug_depth_render_scale_g = *reinterpret_cast<float *>(0x19147C0);
float &c_player_view::render_debug_depth_render_scale_b = *reinterpret_cast<float *>(0x19147C4);
long &c_atmosphere_fog_interface::g_custom_setting_index = *reinterpret_cast<long *>(0x18BE9DC);
namespace hades_file_local { namespace hades_file_local_render_patches { float &k_camera_field_of_view_default = *reinterpret_cast<float *>(0x18BB1C8); } }
namespace hades_file_local { s_extern_description const g_new_extern_descriptions[55] = { { 0, -1, 6, false, false, "_render_method_extern_none" }, { 1, -1, 0, false, false, "_render_method_extern_texture_global_target_texaccum" }, { 1, -1, 0, false, false, "_render_method_extern_texture_global_target_normal" }, { 1, -1, 0, false, false, "_render_method_extern_texture_global_target_z" }, { 1, -1, 6, false, false, "_render_method_extern_texture_global_target_shadow_buffer1" }, { 1, -1, 6, false, false, "_render_method_extern_texture_global_target_shadow_buffer2" }, { 1, -1, 6, false, false, "_render_method_extern_texture_global_target_shadow_buffer3" }, { 1, -1, 6, false, false, "_render_method_extern_texture_global_target_shadow_buffer4" }, { 1, -1, 6, false, false, "_render_method_extern_texture_global_target_texture_camera" }, { 1, -1, 6, false, false, "_render_method_extern_texture_global_target_reflection" }, { 1, -1, 6, false, false, "_render_method_extern_texture_global_target_refraction" }, { 0, -1, 0, false, false, "_render_method_extern_texture_lightprobe_texture" }, { 0, -1, 0, false, false, "_render_method_extern_texture_dominant_light_intensity_map" }, { 0, -1, 6, false, false, "_render_method_extern_texture_unused1" }, { 0, -1, 6, false, false, "_render_method_extern_texture_unused2" }, { 0, -1, 6, false, false, "_render_method_extern_object_change_color_primary" }, { 0, -1, 6, false, false, "_render_method_extern_object_change_color_secondary" }, { 0, -1, 6, false, false, "_render_method_extern_object_change_color_tertiary" }, { 0, -1, 6, false, false, "_render_method_extern_object_change_color_quaternary" }, { 0, -1, 6, false, false, "_render_method_extern_object_change_color_quinary" }, { 0, -1, 6, false, false, "_render_method_extern_object_change_color_primary_anim" }, { 0, -1, 6, false, false, "_render_method_extern_object_change_color_secondary_anim" }, { 0, -1, 6, false, false, "_render_method_extern_texture_dynamic_environment_map_0" }, { 0, -1, 6, false, false, "_render_method_extern_texture_dynamic_environment_map_1" }, { 1, -1, 6, false, true, "_render_method_extern_texture_cook_torrance_cc0236" }, { 1, -1, 6, false, true, "_render_method_extern_texture_cook_torrance_dd0236" }, { 1, -1, 6, false, true, "_render_method_extern_texture_cook_torrance_c78d78" }, { 0, -1, 6, false, false, "_render_method_extern_light_dir_0" }, { 0, -1, 6, false, false, "_render_method_extern_light_color_0" }, { 0, -1, 6, false, false, "_render_method_extern_light_dir_1" }, { 0, -1, 6, false, false, "_render_method_extern_light_color_1" }, { 0, -1, 6, false, false, "_render_method_extern_light_dir_2" }, { 0, -1, 6, false, false, "_render_method_extern_light_color_2" }, { 0, -1, 6, false, false, "_render_method_extern_light_dir_3" }, { 0, -1, 6, false, false, "_render_method_extern_light_color_3" }, { 0, -1, 6, false, false, "_render_method_extern_texture_unused_3" }, { 0, -1, 6, false, false, "_render_method_extern_texture_unused_4" }, { 0, -1, 6, false, false, "_render_method_extern_texture_unused_5" }, { 0, -1, 6, false, false, "_render_method_extern_texture_dynamic_light_gel_0" }, { 0, -1, 6, false, false, "_render_method_extern_flat_envmap_matrix_x" }, { 0, -1, 6, false, false, "_render_method_extern_flat_envmap_matrix_y" }, { 0, -1, 6, false, false, "_render_method_extern_flat_envmap_matrix_z" }, { 0, -1, 6, false, false, "_render_method_extern_debug_tint" }, { 0, -1, 6, false, false, "_render_method_extern_screen_constants" }, { 0, -1, 6, false, false, "_render_method_extern_active_camo_distortion_texture" }, { 1, -1, 0, false, false, "_render_method_extern_scene_ldr_texture" }, { 1, -1, 0, false, false, "_render_method_extern_scene_hdr_texture" }, { 1, -1, 6, false, false, "_render_method_extern_water_memory_export_address" }, { 1, -1, 6, false, false, "_render_method_extern_tree_animation_timer" }, { 1, -1, 0, false, false, "_render_method_extern_emblem_player_shoulder_texture" }, { 1, -1, 0, false, false, "_render_method_extern_emblem_clan_chest_texture" }, { 0, -1, 6, false, false, "_render_method_extern_global_depth_constants" }, { 0, -1, 6, false, false, "_render_method_extern_global_camera_forward" }, { 0, 0, 0, false, false, nullptr }, { 0, 0, 0, false, false, nullptr } }; }
// get_extern_description (render_method_extern.hpp) names this table with C linkage, as the
// original did; both names are the one object.
#pragma comment(linker, "/alternatename:_g_new_extern_descriptions=?g_new_extern_descriptions@hades_file_local@@3QBUs_extern_description@@B")
