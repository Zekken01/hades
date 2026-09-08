/* ---------- headers */

#include "hades/hades.h"

#include "Blam/camera/director.hpp"
#include "Blam/camera/observer.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/aim_target.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/interface/chud/chud.hpp"
#include "Blam/interface/chud/chud_globals.hpp"
#include "Blam/interface/chud/chud_render_definitions.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/models/model_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_shaders.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/camera_fx_settings.hpp"
#include "Blam/render/views/render_player_view.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/shaders/render_methods_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Debug/DebugDraw.hpp"
#include "Modules/ModuleGraphics.hpp"
#include "Modules/ModuleTweaks.hpp"
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

struct c_aim_target_object;
struct c_chud_navpoint_manager;
struct c_chud_point_tracker;
struct c_chud_update_user_data;
struct c_curved_hud_test;
struct c_player_view;
struct c_rasterizer_texture_ref;
struct real_argb_color;
struct real_matrix4x3;
struct real_point2d;
struct real_point3d;
struct real_rectangle2d;
struct real_vector4d;
struct s_aim_assist_targeting_result;
struct s_chud_bitmap_info;
struct s_chud_bitmap_widget;
struct s_chud_draw_widget_data;
struct s_chud_globals_attributes;
struct s_chud_globals_definition;
struct s_chud_managed_navpoint;
struct s_chud_per_character_globals;
struct s_chud_render_data;
struct s_chud_shared_persistent_user_data;
struct s_chud_widget_placement;
struct s_hud_shader_info;
struct s_model_target;
struct s_observer_result;
struct s_widget_geometry_properties;
struct s_widget_geometry_quad_simple;
struct short_rectangle2d;
namespace Modules
{
	class ModuleGraphics;
	class ModuleTweaks;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Chud {}
	using namespace Patches::Chud;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace Chud
	{
		extern void ApplyAll();
	}
}

void c_chud_persistent_user_data__update_from_update_data_hook(void *thisptr, void *__formal, long output_user_index, c_chud_update_user_data *hudData);
void c_chud_persistent_user_data__reset_hook(void *thisptr);
unsigned long c_chud_update_user_data__get_sound_flags_hook(c_chud_update_user_data *thisptr);
bool sub_AC59F0_hook(s_hud_shader_info *a1, bool fancy);
bool chud_draw_begin_hook(long output_user_index, float alpha, bool a3, bool curve_flag);
bool chud_bitmap_widget_compute_geometry_hook(s_chud_draw_widget_data *draw_data, s_chud_widget_geometry<s_widget_geometry_quad_simple> *geometry);
void c_chud_navpoint_manager__draw_hook(c_chud_navpoint_manager *thisptr, void *__formal, long output_user_index);
void c_chud_update_user_data__compute_weapon_update_hook(void *thisptr, void *unused, long weapon_index, long interface_index, s_aim_assist_targeting_result *targeting_result);
void chud_get_target_tracking_render_point_hook(c_aim_target_object *aim_target_object, real_point3d *point);

/* ---------- globals */

namespace Utils
{
	Modules::ModuleTweaks *Utils::Singleton<Modules::ModuleTweaks>::m_instance; // 0x1195B5CC
}

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Chud
	{
		_extern void _sub_10858520();
		void ApplyAll() // 0x10858520
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Chud@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10858520();
		}
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0s_widget_geometry_properties@@QAE@XZ"); no body to assert in
_inline s_widget_geometry_properties::s_widget_geometry_properties() = default; // 0x10858300

/* ---------- private code */

_extern void _sub_1085AAB0(void *, void *, long, c_chud_update_user_data *);
void c_chud_persistent_user_data__update_from_update_data_hook(void *thisptr, void *__formal, long output_user_index, c_chud_update_user_data *hudData) // 0x1085AAB0
{
	// `anonymous-namespace'::c_chud_persistent_user_data__update_from_update_data_hook
	// c_chud_update_user_data *hudData;
	// s_chud_shared_persistent_user_data *(*const chud_shared_persistent_user_data_get)(long);
	// long (*const c_chud_persistent_user_data__update_from_update_data)(void *, long, c_chud_update_user_data *);
	// float warp;
	// function call : long (*const)(void *, long, c_chud_update_user_data *)
	// function call : s_observer_result *(*const)(long)
	// function call : s_chud_shared_persistent_user_data *(*const)(long)
	todo("implement");
	_sub_1085AAB0(thisptr, __formal, output_user_index, hudData);
}

_extern void _sub_1085A9E0(void *);
void c_chud_persistent_user_data__reset_hook(void *thisptr) // 0x1085A9E0
{
	// `anonymous-namespace'::c_chud_persistent_user_data__reset_hook
	// void *thisptr;
	// long perspective;
	// void *(*const c_chud_persistent_user_data__reset)(void *);
	// function call : void *(*const)(void *)
	// function call : e_director_perspective (*const)(long)
	todo("implement");
	_sub_1085A9E0(thisptr);
}

_extern unsigned long _sub_1085ACC0(c_chud_update_user_data *);
unsigned long c_chud_update_user_data__get_sound_flags_hook(c_chud_update_user_data *thisptr) // 0x1085ACC0
{
	// `anonymous-namespace'::c_chud_update_user_data__get_sound_flags_hook
	// c_chud_update_user_data *thisptr;
	// bool (*const player_shields_recharge)(long);
	// unsigned long flags;
	// float persistent_shield;
	// s_chud_globals_definition *chud_globals;
	// long unit_index;
	// void *persistent_user_data;
	// bool (*const game_skull_active)(long);
	// unsigned long (*const get_sound_flags)(c_chud_update_user_data *);
	{
		// unsigned long damage_flags;
		// float shield;
	}
	// function call : unsigned long (*const)(c_chud_update_user_data *)
	// function call : bool (*const)()
	// function call : bool (*const)(long)
	// function call : bool (*const)(long)
	// function call : bool (*const)()
	todo("implement");
	unsigned long __result = _sub_1085ACC0(thisptr);
	return __result;
}

_extern bool _sub_1085DD50(s_hud_shader_info *, bool);
bool sub_AC59F0_hook(s_hud_shader_info *a1, bool fancy) // 0x1085DD50
{
	// `anonymous-namespace'::sub_AC59F0_hook
	// bool fancy;
	{
		// long vertex_type;
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : bool (*const)(void *, long, long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : bool (*const)(void *, long)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : void (*const)(short_rectangle2d *)
	// function call : void (*const)(short_rectangle2d *)
	todo("implement");
	bool __result = _sub_1085DD50(a1, fancy);
	return __result;
}

_extern bool _sub_1085BBC0(long, float, bool, bool);
bool chud_draw_begin_hook(long output_user_index, float alpha, bool a3, bool curve_flag) // 0x1085BBC0
{
	// `anonymous-namespace'::chud_draw_begin_hook
	// static ...; // 0x1085D3A0
	// static ...; // 0x1085D370
	// static ...; // 0x1085D368
	// long output_user_index;
	// float alpha;
	// bool a3;
	// bool curve_flag;
	// float &dword_526A030;
	// c_curved_hud_test curved_hud_test;
	// float v69;
	// float &g_chud_display_x0;
	// float &g_chud_draw_warp_modifier;
	// float &g_chud_draw_curved_screen_width;
	// float title_bounds_scale_y1;
	// float &dword_526A010;
	// float v99;
	// float v80;
	// long &g_chud_draw_resolution_setting;
	// float &g_chud_display_x1;
	// float &dword_5269FE8;
	// float &dword_526A00C;
	// float &dword_526A028;
	// bool (*const bitmap_group_try_get_texture)(long, long, c_rasterizer_texture_ref *);
	// short_rectangle2d &g_chud_bounds;
	// float &dword_5269FE0;
	// float &dword_526A01C;
	// real_point2d &g_chud_draw_curved_hud_point1;
	// __int32 cortana_vertex;
	// float &g_chud_draw_alpha;
	// c_curved_hud_test curved_hud_test2;
	// float v62;
	// float &g_chud_display_y0;
	// s_chud_per_character_globals *hud_globals;
	// float chud_bounds_height;
	// float v68;
	// float &dword_5269FE4;
	// float &dword_5269FF4;
	// float &dword_5269FEC;
	// real_point2d &g_chud_draw_curved_hud_point3;
	// float &g_chud_draw_curved_screen_height;
	// s_chud_shared_persistent_user_data *persistent_user_data;
	// long resolution_height;
	// float v20;
	// float title_render_ratio_x;
	// s_chud_globals_definition *&g_chud_globals;
	// long &g_chud_draw_globals_index;
	// s_chud_globals_attributes *&g_chud_draw_attributes;
	// real_point2d &g_chud_draw_sensor_origin;
	// float &dword_526A004;
	// float &dword_526A014;
	// float &g_chud_draw_screen_height;
	// s_chud_globals_attributes *(*const chud_get_global_attributes_from_output_user)(long, long);
	// float &dword_5269FDC;
	// float &g_chud_draw_curved_scale_x;
	// c_player_view *player_view;
	// float ding_offset_y;
	// float chud_bounds_width;
	// float &dword_5269FF8;
	// float v73;
	// float &dword_526A034;
	// float title_bounds_scale_y0;
	// float &dword_526A008;
	// float &g_chud_draw_curved_scale_y;
	// float ding_offset_x;
	// long resolution_width;
	// float base_height;
	// float base_aspect;
	// float v70;
	// float title_render_ratio_y;
	// float v100;
	// long (*const chud_globals_from_output_user)(long);
	// long &g_chud_draw_user_index;
	// float &g_chud_display_y1;
	// float &dword_526A018;
	// float &dword_526A02C;
	// real_rectangle2d &g_chud_draw_unknown_rectangle;
	// float &g_chud_draw_screen_width;
	// real_point2d &g_chud_draw_curved_hud_point2;
	// float v12;
	// float v64;
	// float &dword_5269FF0;
	// float &dword_5269FFC;
	// float &dword_526A020;
	// float v19;
	// float &dword_5269FD8;
	// float &dword_526A000;
	// float &dword_526A024;
	// float aspect;
	// float v21;
	// float v66;
	{
		// __int32 margin;
	}
	{
		// bool anchor_to_center;
		// Modules::ModuleGraphics &moduleGraphics;
		{
			// __int32 margin;
		}
	}
	{
		// float v84;
		// float v44;
		// float v46;
		// float v45;
		// float v41;
		// float v48;
		// float v49;
		// float v47;
		// float display_width;
		// float normal_scale_x;
		// float normal_scale_y;
		// float display_height;
	}
	{
		// float v58;
		// float v57;
	}
	{
		// c_rasterizer_texture_ref micro_texture_ref;
	}
	// function call : long (*const)(long)
	// function call : s_chud_shared_persistent_user_data *(*const)(long)
	// function call : long (*const)(long)
	// function call : s_chud_globals_attributes *(*const)(long, long)
	// function call : void (*const)(c_curved_hud_test *)
	// function call : void (*const)(c_curved_hud_test *, long)
	// function call : void (*const)(c_curved_hud_test *)
	// function call : void (*const)(c_curved_hud_test *, float, float, real_point2d *)
	// function call : void (*const)(c_curved_hud_test *, float, float, real_point2d *)
	// function call : void (*const)(c_curved_hud_test *, float, float, real_point2d *)
	// function call : bool (*const)(long, long, c_rasterizer_texture_ref *)
	// function call : void (*const)(long, c_rasterizer_texture_ref)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*const)(c_chud_point_tracker *, float)
	// function call : void (*const)(c_chud_point_tracker *, float)
	// function call : void (*const)(long)
	// function call : void (*const)(long, long, __int32 const *)
	// function call : void (*const)(long, long, __int32 const *)
	// function call : void (*const)(long, long, real_vector4d const *)
	// function call : long (*const)(long)
	// function call : void (*const)(long)
	todo("implement");
	bool __result = _sub_1085BBC0(output_user_index, alpha, a3, curve_flag);
	return __result;
}

_extern bool _sub_1085AFC0(s_chud_draw_widget_data *, s_chud_widget_geometry<s_widget_geometry_quad_simple> *);
bool chud_bitmap_widget_compute_geometry_hook(s_chud_draw_widget_data *draw_data, s_chud_widget_geometry<s_widget_geometry_quad_simple> *geometry) // 0x1085AFC0
{
	// `anonymous-namespace'::chud_bitmap_widget_compute_geometry_hook
	// static ...; // 0x1085B938
	// static ...; // 0x1085B935
	// static ...; // 0x1085B932
	// static ...; // 0x1085B92F
	// static ...; // 0x1085B92C
	// static ...; // 0x1085B924
	// static ...; // 0x1085B91C
	// static ...; // 0x1085B914
	// static ...; // 0x1085B8A8
	// static ...; // 0x1085B8A0
	// s_chud_draw_widget_data *draw_data;
	// s_chud_widget_geometry<s_widget_geometry_quad_simple> *geometry;
	// float bitmap_height;
	// bool (*const bitmap_group_try_get_texture)(long, long, c_rasterizer_texture_ref *);
	// float x0;
	// real_rectangle2d bounds1;
	// float &g_chud_draw_virtual_height;
	// s_chud_bitmap_info bitmap_info;
	// float chud_width;
	// s_chud_widget_placement *placement_data;
	// bool (*const chud_bitmap_widget_compute_bitmap_info)(long, long, long, s_chud_bitmap_info *);
	// void (*const chud_widget_build_quads_from_bounds)(real_rectangle2d const *, real_rectangle2d const *, real_rectangle2d const *, s_chud_widget_geometry<s_widget_geometry_quad_simple> *, float, float);
	// real_rectangle2d bounds3;
	// float y0;
	// float bitmap_scale_y;
	// float &g_chud_draw_virtual_width;
	// long &g_chud_player_character_type;
	// unsigned long bitmap_flags;
	// float bitmap_scale_x;
	// float bitmap_width;
	// float chud_height;
	// real_rectangle2d bounds2;
	// s_chud_bitmap_widget *bitmap_widget;
	// long shift_seq_index;
	// float border_thickness;
	// float x1;
	// float y1;
	// void (*const chud_compute_geometry_common)(s_chud_widget_placement const *, s_widget_geometry_properties *);
	// short (*const survival_get_number_of_waves)();
	{
		// c_curved_hud_test curved_hud_test;
		// real_point2d p2;
		// real_point2d p4;
		// real_point2d p1;
		// real_point2d p3;
		// float v20;
		// float v18;
		// float v19;
		// float v21;
	}
	{
		// float border_y;
		// float border_x;
	}
	// function call : short (*const)()
	// function call : bool (*const)(long, long, long, s_chud_bitmap_info *)
	// function call : bool (*const)(long, long, c_rasterizer_texture_ref *)
	// function call : void (*const)(c_curved_hud_test *)
	// function call : void (*const)(c_curved_hud_test *, real_point2d const *, float *, float *)
	// function call : void (*const)(c_curved_hud_test *, real_point2d const *, float *, float *)
	// function call : void (*const)(c_curved_hud_test *, real_point2d const *, float *, float *)
	// function call : void (*const)(c_curved_hud_test *, real_point2d const *, float *, float *)
	// function call : void (*const)(real_rectangle2d const *, real_rectangle2d const *, real_rectangle2d const *, s_chud_widget_geometry<s_widget_geometry_quad_simple> *, float, float)
	// function call : void (*const)(s_chud_widget_placement const *, s_widget_geometry_properties *)
	todo("implement");
	bool __result = _sub_1085AFC0(draw_data, geometry);
	return __result;
}

_extern void _sub_10859B30(c_chud_navpoint_manager *, void *, long);
void c_chud_navpoint_manager__draw_hook(c_chud_navpoint_manager *thisptr, void *__formal, long output_user_index) // 0x10859B30
{
	// `anonymous-namespace'::c_chud_navpoint_manager__draw_hook
	// static ...; // 0x1085A6CA
	// static ...; // 0x1085A6C3
	// static ...; // 0x1085A6BC
	// static ...; // 0x1085A680
	// static ...; // 0x1085A678
// H3_OBJECTIVE:
// H3_NAMETAG:
	// c_chud_navpoint_manager *thisptr;
	// void *__formal;
	// long output_user_index;
	// s_chud_render_data render_data;
	// void (*const chud_expand_pixel32)(unsigned long, real_argb_color *);
	// s_chud_per_character_globals *hud_skin;
	// unsigned long (*const c_chud_navpoint_manager__get_managed_navpoint_arrow_color)(s_chud_managed_navpoint *);
	// bool (*const chud_apply_render_data)(void *, bool);
	// s_chud_globals_definition *chud_globals;
	// s_chud_widget_geometry<s_widget_geometry_quad_simple> geometry;
	// wchar_t buff[128];
	// real_rectangle2d bounds;
	// bool (*const chud_build_text_geometry)(s_widget_geometry_properties *, wchar_t *, __int32, bool, float, real_rectangle2d *);
	// float position_y;
	// float offscreen_amount;
	// long (*const player_mapping_output_user_active_count)();
	// void (*const chud_draw_widget_geometry)(s_widget_geometry_properties *, real_matrix4x3 *, char, char);
	// wchar_t *v17;
	// real_matrix4x3 matrix;
	// void (*const chud_build_custom_render_data)(void *, long);
	// bool (*const chud_compute_anchor_basis_from_tracker)(c_chud_point_tracker *, real_matrix4x3 *, bool);
	// float scale;
	// bool distance_visible;
	// float bounds_x0;
	// long (*const chud_globals_from_output_user)(long);
	// float (*const chud_build_geometry_from_navpoint)(long, long, long, float, float, s_chud_widget_geometry<s_widget_geometry_quad_simple> *);
	// real_rectangle2d *v19;
	// bool name_visible;
	// bool const use_h3_style;
	{
		// long i;
		{
			// bool v5;
			// s_chud_managed_navpoint *managed_navpoint;
			{
				// float icon_scale;
			}
			{
				// float height;
			}
		}
	}
	// function call : long (*const)(long)
	// function call : long (*const)()
	// function call : void (*const)(c_chud_point_tracker *, float)
	// function call : void (*const)(c_chud_point_tracker *, float)
	// function call : void (*const)(void *, long)
	// function call : bool (*const)(c_chud_point_tracker *, real_matrix4x3 *, bool)
	// function call : float (*const)(long, long, long, float, float, s_chud_widget_geometry<s_widget_geometry_quad_simple> *)
	// function call : unsigned long (*const)(s_chud_managed_navpoint *)
	// function call : void (*const)(unsigned long, real_argb_color *)
	// function call : bool (*const)(void *, bool)
	// function call : void (*const)(s_widget_geometry_properties *, real_matrix4x3 *, char, char)
	// function call : bool (*const)(s_widget_geometry_properties *, wchar_t *, __int32, bool, float, real_rectangle2d *)
	// function call : unsigned long (*const)(s_chud_managed_navpoint *)
	// function call : void (*const)(unsigned long, real_argb_color *)
	// function call : bool (*const)(void *, bool)
	// function call : void (*const)(s_widget_geometry_properties *, real_matrix4x3 *, char, char)
	// function call : float (*const)(long, long, long, float, float, s_chud_widget_geometry<s_widget_geometry_quad_simple> *)
	// function call : unsigned long (*const)(s_chud_managed_navpoint *)
	// function call : void (*const)(unsigned long, real_argb_color *)
	// function call : bool (*const)(void *, bool)
	// function call : void (*const)(s_widget_geometry_properties *, real_matrix4x3 *, char, char)
	// function call : bool (*const)(s_widget_geometry_properties *, wchar_t *, __int32, bool, float, real_rectangle2d *)
	// function call : unsigned long (*const)(s_chud_managed_navpoint *)
	// function call : void (*const)(unsigned long, real_argb_color *)
	// function call : bool (*const)(void *, bool)
	// function call : void (*const)(s_widget_geometry_properties *, real_matrix4x3 *, char, char)
	todo("implement");
	_sub_10859B30(thisptr, __formal, output_user_index);
}

_extern void _sub_1085ABE0(void *, void *, long, long, s_aim_assist_targeting_result *);
void c_chud_update_user_data__compute_weapon_update_hook(void *thisptr, void *unused, long weapon_index, long interface_index, s_aim_assist_targeting_result *targeting_result) // 0x1085ABE0
{
	// `anonymous-namespace'::c_chud_update_user_data__compute_weapon_update_hook
	// s_aim_assist_targeting_result *targeting_result;
	// void (*const chud_build_weapon_hud_render_data)(void *, long, long, s_aim_assist_targeting_result *);
	{
		// long offset;
	}
	// function call : void (*const)(void *, long, long, s_aim_assist_targeting_result *)
	todo("implement");
	_sub_1085ABE0(thisptr, unused, weapon_index, interface_index, targeting_result);
}

_extern void _sub_1085D9F0(c_aim_target_object *, real_point3d *);
void chud_get_target_tracking_render_point_hook(c_aim_target_object *aim_target_object, real_point3d *point) // 0x1085D9F0
{
	// `anonymous-namespace'::chud_get_target_tracking_render_point_hook
	// real_point3d *point;
	// s_model_target *(*const get_targeted_model_targets_block)(c_aim_target_object *);
	// static c_aim_target_object `chud_get_target_tracking_render_point_hook'::`2'::last_render_state; // 0x1195B5D4
	// void (*const c_aim_target_object__get_target_point)(c_aim_target_object *, real_point3d *);
	// void (*const get_tracking_point_fallback)(long, real_point3d *);
	// s_model_target *target_block;
	// function call : bool (*const)(c_aim_target_object *)
	// function call : void (*const)(long, real_point3d *)
	// function call : s_model_target *(*const)(c_aim_target_object *)
	// function call : void (*const)(long, real_point3d *)
	// function call : void (*const)(c_aim_target_object *, real_point3d *)
	// function call : void (*const)(c_aim_target_object *, real_point3d *)
	// function call : void (*const)(long, real_point3d *)
	todo("implement");
	_sub_1085D9F0(aim_target_object, point);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Modules::ModuleTweaks & Utils::Singleton<Modules::ModuleTweaks>::Instance();
template bool c_tag_block<s_chud_per_character_globals>::try_get_element(__int32, s_chud_per_character_globals **) const;
template bool c_tag_block<s_chud_widget_placement>::try_get_element(__int32, s_chud_widget_placement **) const;
template c_enum<enum e_sampler_address_mode,long>::c_enum(e_sampler_address_mode const &);
template c_enum<enum e_sampler_address_mode,long>::c_enum(long const &);
template c_enum<enum e_sampler_filter_mode,long>::c_enum(e_sampler_filter_mode const &);
template c_enum<enum e_sampler_filter_mode,long>::c_enum(long const &);
template c_flags<enum e_chud_widget_bitmap_flags,unsigned long>::operator unsigned long() const;
template c_flags<enum s_model_target::e_model_target_flags,long> c_flags<enum s_model_target::e_model_target_flags,long>::operator&(__int32 const) const;
template c_flags<enum s_model_target::e_model_target_flags,long>::c_flags(long const &);
template c_flags<enum s_model_target::e_model_target_flags,long>::operator bool() const;
template s_chud_per_character_globals & c_tag_block<s_chud_per_character_globals>::operator[](__int32);
template s_chud_per_character_globals * c_tag_block<s_chud_per_character_globals>::get_element(__int32) const;
template s_chud_widget_placement & c_tag_block<s_chud_widget_placement>::operator[](__int32);
template s_chud_widget_placement * c_tag_block<s_chud_widget_placement>::get_element(__int32) const;
