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
#include "Modules/ModuleServer.hpp"  // hades: added for 0x10859B30
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

namespace eldorado
{
	// Functions in eldorado.exe, named from the game's own symbols.
	static auto const c_curved_hud_test_construct = reinterpret_cast<void (__thiscall *)(c_curved_hud_test *)>(0xAC5190);
}

namespace eldorado
{
	// Functions in eldorado.exe, named from the game's own symbols.
	static auto const c_chud_navpoint_manager_get_managed_navpoint_text_color = reinterpret_cast<unsigned long (*)(s_chud_managed_navpoint *)>(0xAD1680);
	static auto const c_chud_point_tracker_prepare_for_draw = reinterpret_cast<void (__thiscall *)(c_chud_point_tracker *, float)>(0xAD2360);
	static auto const c_curved_hud_test_set_constants = reinterpret_cast<void (__thiscall *)(c_curved_hud_test *, long)>(0xAD2B20);
	static auto const c_curved_hud_test_transform = reinterpret_cast<void (__thiscall *)(c_curved_hud_test *, float, float, real_point2d *)>(0xAD2D30);
}

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const c_rasterizer_set_alpha_blend_mode = reinterpret_cast<void (*)(long)>(0xA22D10);
	static auto const c_rasterizer_set_cull_mode = reinterpret_cast<void (*)(long)>(0xA232D0);
	static auto const c_rasterizer_set_pixel_shader_constant = reinterpret_cast<void (*)(long, long, real_vector4d const *)>(0xA66270);
	static auto const c_rasterizer_set_pixel_shader_constant_bool = reinterpret_cast<void (*)(long, long, __int32 const *)>(0xA66370);
	static auto const c_rasterizer_set_sampler_address_mode = reinterpret_cast<void (*)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)>(0xA23570);
	static auto const c_rasterizer_set_sampler_filter_mode = reinterpret_cast<void (*)(long, c_enum<enum e_sampler_filter_mode,long>)>(0xA23660);
	static auto const c_rasterizer_set_sampler_texture = reinterpret_cast<void (*)(long, c_rasterizer_texture_ref)>(0xA23810);
	static auto const c_rasterizer_set_vertex_shader_constant_bool = reinterpret_cast<void (*)(long, long, __int32 const *)>(0xA66620);
	static auto const c_rasterizer_set_z_buffer_mode = reinterpret_cast<long (*)(long)>(0xA247E0);
	static auto const chud_shared_persistent_user_data_get = reinterpret_cast<s_chud_shared_persistent_user_data *(*)(long)>(0xA8A570);
}

extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x1085DD50

extern bool (*const game_is_multiplayer)();  // hades: added for 0x1085ACC0

bool weapon_has_bottomless_clip(long weapon_index);  // hades: added for 0X1085ABE0

namespace Patches
{
	namespace Chud
	{
		extern void ApplyAll();
	}
}

void __fastcall c_chud_persistent_user_data__update_from_update_data_hook(void *thisptr, void *__formal, long output_user_index, c_chud_update_user_data *hudData);
void __fastcall c_chud_persistent_user_data__reset_hook(void *thisptr);
unsigned long __fastcall c_chud_update_user_data__get_sound_flags_hook(c_chud_update_user_data *thisptr);
bool sub_AC59F0_hook(s_hud_shader_info *a1, bool fancy);
bool chud_draw_begin_hook(long output_user_index, float alpha, bool a3, bool curve_flag);
bool chud_bitmap_widget_compute_geometry_hook(s_chud_draw_widget_data *draw_data, s_chud_widget_geometry<s_widget_geometry_quad_simple> *geometry);
void __fastcall c_chud_navpoint_manager__draw_hook(c_chud_navpoint_manager *thisptr, void *__formal, long output_user_index);
void __fastcall c_chud_update_user_data__compute_weapon_update_hook(void *thisptr, void *unused, long weapon_index, long interface_index, s_aim_assist_targeting_result *targeting_result);
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
		void ApplyAll() // 0x10858520
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Chud@Patches@@YAXXZ");

			Hook(0x68F598, c_chud_update_user_data__get_sound_flags_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x6C59F0, sub_AC59F0_hook).Apply();
			Hook(0x6C80F0, chud_draw_begin_hook).Apply();
			Hook(0x6C63F0, chud_bitmap_widget_compute_geometry_hook).Apply();
			Hook(0x6CED00, c_chud_navpoint_manager__draw_hook).Apply();
			Hook(0x68F57C, c_chud_persistent_user_data__update_from_update_data_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x690273, c_chud_persistent_user_data__reset_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x686239, c_chud_update_user_data__compute_weapon_update_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x6862A8, c_chud_update_user_data__compute_weapon_update_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x68B149, { 0x75 }).Apply();
			Patch(0x68B154, { 0x90, 0x90 }).Apply();
			Patch(0x686092, { 0x75 }).Apply();
			Patch(0x68609F, { 0x90, 0x90 }).Apply();
			Patch(0x686A1A, { 0x75 }).Apply();
			Patch(0x686A28, { 0x90, 0x90 }).Apply();
			Patch(0x6865AD, { 0x75 }).Apply();
			Patch(0x6865BB, { 0x90, 0x90 }).Apply();
			Hook(0x761474, chud_get_target_tracking_render_point_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
		}
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0s_widget_geometry_properties@@QAE@XZ"); no body to assert in
_inline s_widget_geometry_properties::s_widget_geometry_properties() // 0x10858300
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_widget_geometry_properties@@QAE@XZ");

	reinterpret_cast<c_rasterizer_texture_ref *>(texture_ref)->c_rasterizer_texture_ref::c_rasterizer_texture_ref(-1);
}

/* ---------- private code */

void __fastcall c_chud_persistent_user_data__update_from_update_data_hook(void *thisptr, void *__formal, long output_user_index, c_chud_update_user_data *hudData) // 0x1085AAB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_chud_persistent_user_data__update_from_update_data_hook@@YIXPAX0JPAUc_chud_update_user_data@@@Z");

	long (__thiscall *const c_chud_persistent_user_data__update_from_update_data)(void *, long, c_chud_update_user_data *) = reinterpret_cast<long (__thiscall *)(void *, long, c_chud_update_user_data *)>(0xA901E0);
	c_chud_persistent_user_data__update_from_update_data(thisptr, output_user_index, hudData);
	s_chud_shared_persistent_user_data *(*const chud_shared_persistent_user_data_get)(long) = reinterpret_cast<s_chud_shared_persistent_user_data *(*)(long)>(0xA8A570);
	float warp = ((s_observer_result *(__cdecl *)(long))0x6127C0)(output_user_index)->focus_offset.i;
	if (warp > 1.0f)
		warp = 1.0f;
	if (warp < 0.0f)
		warp = 0.0f;
	if (Utils::Singleton<Modules::ModuleTweaks>::Instance().VarFlatHUD->ValueInt == 1)
		warp = 0.0f;
	chud_shared_persistent_user_data_get(output_user_index)->warp_modifier = warp;
}

void __fastcall c_chud_persistent_user_data__reset_hook(void *thisptr) // 0x1085A9E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_chud_persistent_user_data__reset_hook@@YIXPAX@Z");

	void (__thiscall *const c_chud_persistent_user_data__reset)(void *) = (void (__thiscall *)(void *))0xA8DD60;
	c_chud_persistent_user_data__reset(thisptr);

	long user_index = ((long (__cdecl *)(long))0x591A40)(0);
	if (user_index)
		*(float *)offset_pointer(thisptr, 0x1C30) = 0.0f;
	else
		*(float *)offset_pointer(thisptr, 0x1C30) = 1.0f;
}

unsigned long __fastcall c_chud_update_user_data__get_sound_flags_hook(c_chud_update_user_data *thisptr) // 0x1085ACC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_chud_update_user_data__get_sound_flags_hook@@YIKPAUc_chud_update_user_data@@@Z");

	unsigned long (__thiscall *const get_sound_flags)(c_chud_update_user_data *) = reinterpret_cast<unsigned long (__thiscall *)(c_chud_update_user_data *)>(0xA8C810);
	bool (*const game_skull_active)(long) = reinterpret_cast<bool (*)(long)>(0x60AE20);
	bool (*const player_shields_recharge)(long) = reinterpret_cast<bool (*)(long)>(0x551EA0);
	unsigned long flags = get_sound_flags(thisptr);
	long unit_index = *(long *)offset_pointer(thisptr, 8);
	if (((bool (*)())0x67D270)() || unit_index == -1)
		return flags;
	flags &= ~0x3780;
	void *persistent_user_data = offset_pointer(*(void **)tls_get(0x420), 0x3E90 * *(long *)thisptr);
	float persistent_shield = *(float *)offset_pointer(persistent_user_data, 0x3DD8);
	s_chud_globals_definition *chud_globals = *(s_chud_globals_definition **)0x5257C40;
	if (persistent_shield != -1.0)
	{
		if (player_shields_recharge(*(long *)offset_pointer(thisptr, 4)))
		{
			float shield = *(float *)offset_pointer(thisptr, 0x5C4);
			unsigned long damage_flags = *(unsigned long *)offset_pointer(thisptr, 0x5F8);
			if ((damage_flags >> 10) & 1)
				flags |= 0x80;
			else
				flags &= ~0x80;
			if (persistent_shield > shield)
				flags |= 0x100;
			if (!game_skull_active(1))
			{
				if (chud_globals->shield_major_threshold > shield && shield > chud_globals->shield_critical_threshold)
					flags |= 0x1000;
				if (chud_globals->shield_critical_threshold >= shield)
					flags |= 0x2000;
			}
			if (game_is_multiplayer() && shield >= 1.0)
				flags &= ~0x700;
		}
	}
	if (flags & 0x8000)
		flags &= ~0x4000;
	return flags;
}

bool sub_AC59F0_hook(s_hud_shader_info *a1, bool fancy) // 0x1085DD50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sub_AC59F0_hook@@YA_NPAUs_hud_shader_info@@_N@Z");

	if (a1->pixel_shader != -1 && a1->vertex_shader != -1)
	{
		long vertex_type = fancy ? 14 : 13;
		reinterpret_cast<void (*)(void *, long, long, long)>(0xA246E0)(tag_get('vtsh', a1->vertex_shader), vertex_type, 0, 0);
		reinterpret_cast<void (*)(void *, long)>(0xA23460)(tag_get('pixl', a1->pixel_shader), 0);
		reinterpret_cast<void (*)(long, long, real_vector4d const *)>(0xA66410)(32, 1, &a1->chud_texture_transform);
		reinterpret_cast<void (*)(long, long, real_vector4d const *)>(0xA66270)(24, 1, &a1->chud_color_output_a);
		reinterpret_cast<void (*)(long, long, real_vector4d const *)>(0xA66270)(25, 1, &a1->chud_color_output_b);
		reinterpret_cast<void (*)(long, long, real_vector4d const *)>(0xA66270)(26, 1, &a1->chud_color_output_c);
		reinterpret_cast<void (*)(long, long, real_vector4d const *)>(0xA66270)(27, 1, &a1->chud_color_output_d);
		reinterpret_cast<void (*)(long, long, real_vector4d const *)>(0xA66270)(28, 1, &a1->chud_color_output_e);
		reinterpret_cast<void (*)(long, long, real_vector4d const *)>(0xA66270)(29, 1, &a1->chud_color_output_f);
		reinterpret_cast<void (*)(long, long, real_vector4d const *)>(0xA66270)(30, 1, &a1->chud_scalar_output_abcd);
		reinterpret_cast<void (*)(long, long, real_vector4d const *)>(0xA66270)(31, 1, &a1->chud_scalar_output_ef);
		if (a1->rect.x1 <= a1->rect.x0 || a1->rect.y1 <= a1->rect.y0)
			reinterpret_cast<void (*)(short_rectangle2d const *)>(0xA239B0)(nullptr);
		else
			reinterpret_cast<void (*)(short_rectangle2d const *)>(0xA239B0)(&a1->rect);
		return a1->chud_scalar_output_ef.w > 0.0f;
	}
	return false;
}

bool chud_draw_begin_hook(long output_user_index, float alpha, bool a3, bool curve_flag) // 0x1085BBC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?chud_draw_begin_hook@@YA_NJM_N0@Z");

	bool (*const bitmap_group_try_get_texture)(long, long, c_rasterizer_texture_ref *) = reinterpret_cast<bool (*)(long, long, c_rasterizer_texture_ref *)>(0x718D10);
	long (*const chud_globals_from_output_user)(long) = reinterpret_cast<long (*)(long)>(0xA895C0);
	s_chud_globals_attributes *(*const chud_get_global_attributes_from_output_user)(long, long) = reinterpret_cast<s_chud_globals_attributes *(*)(long, long)>(0xAC78D0);
	s_chud_globals_definition *&g_chud_globals = *(s_chud_globals_definition * *)0x5257C40;
	long &g_chud_draw_user_index = *(long *)0x526A070;
	long &g_chud_draw_globals_index = *(long *)0x526A074;
	long &g_chud_draw_resolution_setting = *(long *)0x526A064;
	s_chud_globals_attributes *&g_chud_draw_attributes = *(s_chud_globals_attributes * *)0x526A058;
	real_point2d &g_chud_draw_sensor_origin = *(real_point2d *)0x526A05C;
	short_rectangle2d &g_chud_bounds = *(short_rectangle2d *)0x526A048;
	float &g_chud_display_x0 = *(float *)0x5269FC8;
	float &g_chud_display_x1 = *(float *)0x5269FCC;
	float &g_chud_display_y0 = *(float *)0x5269FD0;
	float &g_chud_display_y1 = *(float *)0x5269FD4;
	float &dword_5269FDC = *(float *)0x5269FDC;
	float &dword_5269FE0 = *(float *)0x5269FE0;
	float &dword_5269FD8 = *(float *)0x5269FD8;
	float &dword_5269FE4 = *(float *)0x5269FE4;
	float &dword_5269FF4 = *(float *)0x5269FF4;
	float &dword_5269FEC = *(float *)0x5269FEC;
	float &dword_5269FE8 = *(float *)0x5269FE8;
	float &dword_5269FF0 = *(float *)0x5269FF0;
	float &dword_5269FFC = *(float *)0x5269FFC;
	float &dword_526A004 = *(float *)0x526A004;
	float &dword_5269FF8 = *(float *)0x5269FF8;
	float &dword_526A000 = *(float *)0x526A000;
	float &dword_526A010 = *(float *)0x526A010;
	float &dword_526A008 = *(float *)0x526A008;
	float &dword_526A00C = *(float *)0x526A00C;
	float &dword_526A014 = *(float *)0x526A014;
	float &dword_526A018 = *(float *)0x526A018;
	float &dword_526A01C = *(float *)0x526A01C;
	float &dword_526A020 = *(float *)0x526A020;
	float &dword_526A024 = *(float *)0x526A024;
	float &dword_526A028 = *(float *)0x526A028;
	float &dword_526A030 = *(float *)0x526A030;
	float &dword_526A034 = *(float *)0x526A034;
	float &dword_526A02C = *(float *)0x526A02C;
	real_rectangle2d &g_chud_draw_unknown_rectangle = *(real_rectangle2d *)0x526A038;
	float &g_chud_draw_screen_width = *(float *)0x526A050;
	float &g_chud_draw_screen_height = *(float *)0x526A054;
	float &g_chud_draw_alpha = *(float *)0x526A068;
	float &g_chud_draw_warp_modifier = *(float *)0x526A06C;
	real_point2d &g_chud_draw_curved_hud_point1 = *(real_point2d *)0x526A08C;
	real_point2d &g_chud_draw_curved_hud_point2 = *(real_point2d *)0x526A094;
	real_point2d &g_chud_draw_curved_hud_point3 = *(real_point2d *)0x526A09C;
	float &g_chud_draw_curved_scale_x = *(float *)0x526A0A4;
	float &g_chud_draw_curved_scale_y = *(float *)0x526A0A8;
	float &g_chud_draw_curved_screen_width = *(float *)0x526A07C;
	float &g_chud_draw_curved_screen_height = *(float *)0x526A080;
	c_curved_hud_test curved_hud_test;
	c_curved_hud_test curved_hud_test2;
	if (!g_chud_globals)
		return false;
	s_chud_per_character_globals *hud_globals = &g_chud_globals->character_globals[chud_globals_from_output_user(output_user_index)];
	if (hud_globals->attributes.count < 1)
		return false;
	s_chud_shared_persistent_user_data *persistent_user_data;
	c_player_view *player_view = c_player_view::get_current();
	persistent_user_data = eldorado::chud_shared_persistent_user_data_get(output_user_index);
	g_chud_draw_user_index = output_user_index;
	g_chud_draw_globals_index = chud_globals_from_output_user(output_user_index);
	g_chud_draw_resolution_setting = persistent_user_data->resolution_setting;
	g_chud_draw_attributes = chud_get_global_attributes_from_output_user(output_user_index, g_chud_draw_resolution_setting);
	g_chud_draw_sensor_origin = g_chud_draw_attributes->sensor_origin;
	g_chud_bounds = player_view->rasterizer_camera.fullscreen_pixel_bounds;
	g_chud_draw_screen_width = (float)g_chud_draw_attributes->virtual_width;
	g_chud_draw_screen_height = (float)g_chud_draw_attributes->virtual_height;
	g_chud_draw_alpha = alpha;
	float ding_offset_x = (float)(g_chud_bounds.x1 - g_chud_bounds.x0) * (g_chud_draw_attributes->safe_frame_horizontal_ding * 0.5f);
	float ding_offset_y = (float)(g_chud_bounds.y1 - g_chud_bounds.y0) * (g_chud_draw_attributes->safe_frame_vertical_ding * 0.5f);
	g_chud_bounds.x0 += (__int32)ding_offset_x;
	g_chud_bounds.y0 += (__int32)ding_offset_y;
	g_chud_bounds.x1 -= (__int32)ding_offset_x;
	g_chud_bounds.y1 -= (__int32)ding_offset_y;
	long resolution_width = *(long *)0x19106C0;
	long resolution_height = *(long *)0x19106C4;
	float base_height = 1080.0f;
	float base_aspect = 16.0f / 9.0f;
	float aspect = (float)resolution_width / (float)resolution_height;
	float chud_bounds_height = (float)(g_chud_bounds.y1 - g_chud_bounds.y0);
	float chud_bounds_width = (float)(g_chud_bounds.x1 - g_chud_bounds.x0);
	if (aspect <= base_aspect)
	{
		__int32 margin = (chud_bounds_height - chud_bounds_width / base_aspect) * 0.5f;
		g_chud_bounds.y0 += margin;
		g_chud_bounds.y1 -= margin;
	}
	else
	{
		Modules::ModuleGraphics &moduleGraphics = Modules::ModuleGraphics::Instance();
		bool anchor_to_center = moduleGraphics.VarCenteredHUD->ValueInt != 0;
		if (anchor_to_center)
		{
			__int32 margin = (chud_bounds_width - chud_bounds_height * base_aspect) * 0.5f;
			g_chud_bounds.x0 += margin;
			g_chud_bounds.x1 -= margin;
		}
		else
		{
			g_chud_draw_screen_width = base_height / chud_bounds_height * chud_bounds_width * moduleGraphics.VarHUDScaleX->ValueFloat;
		}
	}
	g_chud_display_x1 = (float)player_view->rasterizer_camera.display_pixel_bounds.x1;
	g_chud_display_y0 = (float)player_view->rasterizer_camera.display_pixel_bounds.y0;
	g_chud_display_x0 = (float)player_view->rasterizer_camera.display_pixel_bounds.x0;
	g_chud_display_y1 = (float)player_view->rasterizer_camera.display_pixel_bounds.y1;
	float title_bounds_scale_y0 = (float)player_view->rasterizer_camera.render_title_safe_pixel_bounds.y0 / (float)player_view->rasterizer_camera.render_pixel_bounds.y1;
	float title_bounds_scale_y1 = (float)player_view->rasterizer_camera.render_title_safe_pixel_bounds.y1 / (float)player_view->rasterizer_camera.render_pixel_bounds.y1;
	float v19 = (float)player_view->rasterizer_camera.unknown_chud_offset.x + (float)player_view->rasterizer_camera.window_pixel_bounds.x1;
	float v20 = ((float)player_view->rasterizer_camera.unknown_chud_offset.y + (float)player_view->rasterizer_camera.window_pixel_bounds.y0) / (float)player_view->rasterizer_camera.render_pixel_bounds.y1;
	float v12 = (float)player_view->rasterizer_camera.unknown_chud_offset.x + (float)player_view->rasterizer_camera.window_pixel_bounds.x0;
	float v21 = (float)player_view->rasterizer_camera.render_pixel_bounds.x1;
	dword_5269FDC = (float)player_view->rasterizer_camera.render_title_safe_pixel_bounds.x1 / (float)player_view->rasterizer_camera.render_pixel_bounds.x1 * g_chud_display_x1;
	dword_5269FE0 = title_bounds_scale_y0 * g_chud_display_y1;
	dword_5269FD8 = (float)player_view->rasterizer_camera.render_title_safe_pixel_bounds.x0 / (float)player_view->rasterizer_camera.render_pixel_bounds.x1 * g_chud_display_x1;
	dword_5269FE4 = title_bounds_scale_y1 * g_chud_display_y1;
	dword_5269FF4 = ((float)player_view->rasterizer_camera.unknown_chud_offset.y + (float)player_view->rasterizer_camera.window_pixel_bounds.y1) / (float)player_view->rasterizer_camera.render_pixel_bounds.y1 * g_chud_display_y1;
	dword_5269FEC = v19 / v21 * g_chud_display_x1;
	dword_5269FE8 = v12 / v21 * g_chud_display_x1;
	dword_5269FF0 = v20 * g_chud_display_y1;
	float v69 = v19 / v21 * g_chud_display_x1;
	float v64 = dword_5269FF4;
	float v70 = v12 / v21 * g_chud_display_x1;
	float v66 = v20 * g_chud_display_y1;
	dword_5269FFC = (float)g_chud_bounds.x1 / (float)player_view->rasterizer_camera.render_pixel_bounds.x1 * g_chud_display_x1;
	dword_526A004 = (float)g_chud_bounds.y1 / (float)player_view->rasterizer_camera.render_pixel_bounds.y1 * g_chud_display_y1;
	dword_5269FF8 = (float)g_chud_bounds.x0 / (float)player_view->rasterizer_camera.render_pixel_bounds.x1 * g_chud_display_x1;
	dword_526A000 = (float)g_chud_bounds.y0 / (float)player_view->rasterizer_camera.render_pixel_bounds.y1 * g_chud_display_y1;
	dword_526A010 = (float)player_view->rasterizer_camera.render_pixel_bounds.y0;
	dword_526A008 = (float)player_view->rasterizer_camera.render_pixel_bounds.x0;
	dword_526A00C = (float)player_view->rasterizer_camera.render_pixel_bounds.x1;
	dword_526A014 = (float)player_view->rasterizer_camera.render_pixel_bounds.y1;
	float title_render_ratio_x = (float)player_view->rasterizer_camera.render_title_safe_pixel_bounds.y0 / (float)player_view->rasterizer_camera.render_pixel_bounds.y1;
	float title_render_ratio_y = (float)player_view->rasterizer_camera.render_title_safe_pixel_bounds.y1 / (float)player_view->rasterizer_camera.render_pixel_bounds.y1;
	float v99 = ((float)player_view->rasterizer_camera.unknown_chud_offset.y + (float)player_view->rasterizer_camera.window_pixel_bounds.y0) / (float)player_view->rasterizer_camera.render_pixel_bounds.y1;
	float v100 = ((float)player_view->rasterizer_camera.unknown_chud_offset.y + (float)player_view->rasterizer_camera.window_pixel_bounds.y1) / (float)player_view->rasterizer_camera.render_pixel_bounds.y1;
	dword_526A018 = (float)player_view->rasterizer_camera.render_title_safe_pixel_bounds.x0 / (float)player_view->rasterizer_camera.render_pixel_bounds.x1 * dword_526A00C;
	dword_526A01C = (float)player_view->rasterizer_camera.render_title_safe_pixel_bounds.x1 / (float)player_view->rasterizer_camera.render_pixel_bounds.x1 * dword_526A00C;
	dword_526A020 = title_render_ratio_x * dword_526A014;
	dword_526A024 = title_render_ratio_y * dword_526A014;
	dword_526A028 = ((float)player_view->rasterizer_camera.unknown_chud_offset.x + (float)player_view->rasterizer_camera.window_pixel_bounds.x0) / (float)player_view->rasterizer_camera.render_pixel_bounds.x1 * dword_526A00C;
	dword_526A030 = v99 * dword_526A014;
	dword_526A034 = v100 * dword_526A014;
	dword_526A02C = ((float)player_view->rasterizer_camera.unknown_chud_offset.x + (float)player_view->rasterizer_camera.window_pixel_bounds.x1) / (float)player_view->rasterizer_camera.render_pixel_bounds.x1 * dword_526A00C;
	float v68 = ((float)player_view->rasterizer_camera.unknown_chud_offset.x + (float)player_view->rasterizer_camera.window_pixel_bounds.x1) / (float)player_view->rasterizer_camera.render_pixel_bounds.x1 * dword_526A00C;
	float v80 = dword_526A028;
	float v62 = v99 * dword_526A014;
	float v73 = v100 * dword_526A014;
	g_chud_draw_unknown_rectangle.x0 = (float)g_chud_bounds.x0 / (float)player_view->rasterizer_camera.render_pixel_bounds.x1 * dword_526A00C;
	g_chud_draw_unknown_rectangle.x1 = (float)g_chud_bounds.x1 / (float)player_view->rasterizer_camera.render_pixel_bounds.x1 * dword_526A00C;
	g_chud_draw_unknown_rectangle.y0 = (float)g_chud_bounds.y0 / (float)player_view->rasterizer_camera.render_pixel_bounds.y1 * dword_526A014;
	g_chud_draw_unknown_rectangle.y1 = (float)g_chud_bounds.y1 / (float)player_view->rasterizer_camera.render_pixel_bounds.y1 * dword_526A014;
	if (g_chud_draw_attributes->global_safe_frame_horiz != 0.0f && g_chud_draw_attributes->global_safe_frame_vert != 0.0f)
	{
		float display_width = g_chud_display_x1 - g_chud_display_x0;
		float display_height = g_chud_display_y1 - g_chud_display_y0;
		float normal_scale_x = (1.0f - g_chud_draw_attributes->global_safe_frame_horiz) * 0.5f;
		float normal_scale_y = (1.0f - g_chud_draw_attributes->global_safe_frame_vert) * 0.5f;
		float v84 = 1.0f - normal_scale_x;
		float v41 = 1.0f - normal_scale_y;
		float v44 = dword_526A00C - dword_526A008;
		float v46 = dword_526A014 - dword_526A010;
		float v45 = v84 * v44;
		float v48 = v41 * v46;
		float v47 = v44 * normal_scale_x;
		float v49 = v46 * normal_scale_y;
		dword_5269FD8 = display_width * normal_scale_x;
		dword_5269FE0 = display_height * normal_scale_y;
		dword_5269FDC = (1.0f - normal_scale_x) * display_width;
		dword_5269FE4 = (1.0f - normal_scale_y) * display_height;
		dword_5269FF8 = fmaxf(v70, display_width * normal_scale_x);
		dword_526A000 = fmaxf(v66, display_height * normal_scale_y);
		dword_5269FFC = fminf(v69, v84 * display_width);
		dword_526A004 = fminf(v64, v41 * display_height);
		dword_526A018 = v47;
		dword_526A01C = v45;
		dword_526A020 = v49;
		dword_526A024 = v48;
		g_chud_draw_unknown_rectangle.x0 = fmaxf(v47, v80);
		g_chud_draw_unknown_rectangle.y0 = fmaxf(v49, v62);
		g_chud_draw_unknown_rectangle.x1 = fminf(v68, v45);
		g_chud_draw_unknown_rectangle.y1 = fminf(v73, v48);
		g_chud_bounds.x0 = fmaxf(v47 - (float)player_view->rasterizer_camera.unknown_chud_offset.x, (float)g_chud_bounds.x0);
		g_chud_bounds.y0 = fmaxf(v49 - (float)player_view->rasterizer_camera.unknown_chud_offset.y, (float)g_chud_bounds.y0);
		g_chud_bounds.x1 = fminf(v45 - (float)player_view->rasterizer_camera.unknown_chud_offset.x, (float)g_chud_bounds.x1);
		g_chud_bounds.y1 = fminf(v48 - (float)player_view->rasterizer_camera.unknown_chud_offset.y, (float)g_chud_bounds.y1);
	}
	if (curve_flag)
		g_chud_draw_warp_modifier = 0.0f;
	else
		g_chud_draw_warp_modifier = persistent_user_data->warp_modifier;
	eldorado::c_curved_hud_test_construct(&curved_hud_test);
	eldorado::c_curved_hud_test_set_constants(&curved_hud_test, output_user_index);
	if (curve_flag)
	{
		g_chud_draw_warp_modifier = persistent_user_data->warp_modifier;
		eldorado::c_curved_hud_test_construct(&curved_hud_test2);
		eldorado::c_curved_hud_test_transform(&curved_hud_test2, 0.0f, 1.0f, &g_chud_draw_curved_hud_point1);
		eldorado::c_curved_hud_test_transform(&curved_hud_test2, 1.0f, 0.0f, &g_chud_draw_curved_hud_point2);
		eldorado::c_curved_hud_test_transform(&curved_hud_test2, 0.5f, 1.0f, &g_chud_draw_curved_hud_point3);
		float v57 = g_chud_draw_curved_hud_point2.x - g_chud_draw_curved_hud_point1.x;
		float v58 = g_chud_draw_curved_hud_point2.y - g_chud_draw_curved_hud_point1.y;
		if (fabsf(g_chud_draw_curved_hud_point2.x - g_chud_draw_curved_hud_point1.x) < 0.000099999997f)
			v57 = 0.000099999997f;
		if (fabsf(v58) < 0.000099999997f)
			v58 = 0.000099999997f;
		g_chud_draw_warp_modifier = 0.0f;
		g_chud_draw_curved_scale_x = (g_chud_draw_curved_hud_point3.x - g_chud_draw_curved_hud_point1.x) / v57;
		g_chud_draw_curved_scale_y = (g_chud_draw_curved_hud_point3.y - g_chud_draw_curved_hud_point1.y) / v58;
		g_chud_draw_curved_screen_width = g_chud_draw_curved_scale_x * g_chud_draw_screen_width;
		g_chud_draw_curved_screen_height = g_chud_draw_curved_scale_y * g_chud_draw_screen_height;
	}
	if (hud_globals->damage_microtexture.index != -1)
	{
		c_rasterizer_texture_ref micro_texture_ref(-1);
		bitmap_group_try_get_texture(hud_globals->damage_microtexture.index, 0, &micro_texture_ref);
		eldorado::c_rasterizer_set_sampler_texture(1, micro_texture_ref);
		eldorado::c_rasterizer_set_sampler_address_mode(1, _address_mode_wrap, _address_mode_wrap, _address_mode_wrap);
		eldorado::c_rasterizer_set_sampler_filter_mode(1, _filter_bilinear);
	}
	if (persistent_user_data->use_pointer_tracker1)
	{
		persistent_user_data->point_tracker.valid = true;
		persistent_user_data->point_tracker.world_point = persistent_user_data->unknown_pooint1;
		eldorado::c_chud_point_tracker_prepare_for_draw(&persistent_user_data->point_tracker, 1.0f);
	}
	if (persistent_user_data->use_pointer_tracker2)
	{
		persistent_user_data->pointer_tracker2.valid = true;
		persistent_user_data->pointer_tracker2.world_point = persistent_user_data->unknown_point2;
		eldorado::c_chud_point_tracker_prepare_for_draw(&persistent_user_data->pointer_tracker2, 1.0f);
		persistent_user_data->use_pointer_tracker2 = persistent_user_data->pointer_tracker2.offscreen_amount < 0.000099999997;
	}
	eldorado::c_rasterizer_set_alpha_blend_mode(3);
	__int32 cortana_vertex = 0;
	eldorado::c_rasterizer_set_vertex_shader_constant_bool(7, 1, &cortana_vertex);
	eldorado::c_rasterizer_set_pixel_shader_constant_bool(7, 1, &cortana_vertex);
	if (curve_flag)
		eldorado::c_rasterizer_set_pixel_shader_constant(33, 4, &persistent_user_data->local_to_world0);
	eldorado::c_rasterizer_set_z_buffer_mode(2);
	eldorado::c_rasterizer_set_cull_mode(1);
	return true;
}

bool chud_bitmap_widget_compute_geometry_hook(s_chud_draw_widget_data *draw_data, s_chud_widget_geometry<s_widget_geometry_quad_simple> *geometry) // 0x1085AFC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?chud_bitmap_widget_compute_geometry_hook@@YA_NPAUs_chud_draw_widget_data@@PAU?$s_chud_widget_geometry@Us_widget_geometry_quad_simple@@@@@Z");

	bool (*const chud_bitmap_widget_compute_bitmap_info)(long, long, long, s_chud_bitmap_info *) = reinterpret_cast<bool (*)(long, long, long, s_chud_bitmap_info *)>(0xAC6220);
	bool (*const bitmap_group_try_get_texture)(long, long, c_rasterizer_texture_ref *) = reinterpret_cast<bool (*)(long, long, c_rasterizer_texture_ref *)>(0x718D10);
	void (*const chud_widget_build_quads_from_bounds)(real_rectangle2d const *, real_rectangle2d const *, real_rectangle2d const *, s_chud_widget_geometry<s_widget_geometry_quad_simple> *, float, float) = reinterpret_cast<void (*)(real_rectangle2d const *, real_rectangle2d const *, real_rectangle2d const *, s_chud_widget_geometry<s_widget_geometry_quad_simple> *, float, float)>(0xACAD00);
	void (*const chud_compute_geometry_common)(s_chud_widget_placement const *, s_widget_geometry_properties *) = reinterpret_cast<void (*)(s_chud_widget_placement const *, s_widget_geometry_properties *)>(0xAC7940);
	short (*const survival_get_number_of_waves)() = reinterpret_cast<short (*)()>(0x689120);
	float &g_chud_draw_virtual_width = *(float *)0x526A050;
	float &g_chud_draw_virtual_height = *(float *)0x526A054;
	long &g_chud_player_character_type = *(long *)0x526A074;
	s_chud_bitmap_widget *bitmap_widget = (s_chud_bitmap_widget *)draw_data->widget;
	s_chud_widget_placement *placement_data = &bitmap_widget->placement[0];
	if (!placement_data)
		return false;
	long shift_seq_index = 0;
	unsigned long bitmap_flags = bitmap_widget->flags;
	if (bitmap_flags & 0x20)
		shift_seq_index = g_chud_player_character_type;
	else if (bitmap_flags & 0x40)
		shift_seq_index = survival_get_number_of_waves();
	else if (bitmap_flags & 0x80)
		shift_seq_index = (long)*(float *)offset_pointer(draw_data->runtime_data, 0x10);
	else if (bitmap_flags & 0x100)
		shift_seq_index = (long)*(float *)offset_pointer(draw_data->runtime_data, 0x14);
	else if (bitmap_flags & 0x4000)
		shift_seq_index = (long)(*(float *)offset_pointer(draw_data->runtime_data, 0x10) + 0.5f);
	else if (bitmap_flags & 0x8000)
		shift_seq_index = (long)*(float *)offset_pointer(draw_data->runtime_data, 0x10);
	s_chud_bitmap_info bitmap_info;
	if (!chud_bitmap_widget_compute_bitmap_info(bitmap_widget->bitmap.index, bitmap_widget->sprite_index + shift_seq_index, 0, &bitmap_info))
		return false;
	float bitmap_scale_x = 1.0f;
	float bitmap_scale_y = 1.0f;
	float bitmap_width = bitmap_info.unknown_width;
	float bitmap_height = bitmap_info.unknown_height;
	bitmap_group_try_get_texture(bitmap_info.group_definition_index, bitmap_info.bitmap_index, (c_rasterizer_texture_ref *)geometry->texture_ref);
	geometry->sampler_address_mode = 3;
	if (bitmap_flags & 0x10)
		geometry->sampler_address_mode = 0;
	float border_thickness = 0.0f;
	float chud_height = g_chud_draw_virtual_height;
	float chud_width = g_chud_draw_virtual_width;
	float x0;
	float x1;
	float y0;
	float y1;
	if (bitmap_flags & 0x10000)
	{
		bitmap_width = g_chud_draw_virtual_width / 1920.0f * bitmap_width;
		bitmap_height = g_chud_draw_virtual_height / 1080.0f * bitmap_height;
		x0 = bitmap_info.bounds.x0;
		x1 = bitmap_info.bounds.x1;
		y0 = bitmap_info.bounds.y0;
		y1 = bitmap_info.bounds.y1;
	}
	else if (bitmap_flags & 4)
	{
		c_curved_hud_test curved_hud_test;
		((void (__thiscall *)(c_curved_hud_test *))0xAC5190)(&curved_hud_test);
		real_point2d p1 = { 0.0f, chud_height };
		real_point2d p2 = { chud_width, chud_height };
		real_point2d p3 = { 0.0f, 0.0f };
		real_point2d p4 = { chud_width, 0.0f };
		((void (__thiscall *)(c_curved_hud_test *, real_point2d const *, float *, float *))0xAD1C30)(&curved_hud_test, &p1, &p1.x, &p1.y);
		((void (__thiscall *)(c_curved_hud_test *, real_point2d const *, float *, float *))0xAD1C30)(&curved_hud_test, &p2, &p2.x, &p2.y);
		((void (__thiscall *)(c_curved_hud_test *, real_point2d const *, float *, float *))0xAD1C30)(&curved_hud_test, &p3, &p3.x, &p3.y);
		((void (__thiscall *)(c_curved_hud_test *, real_point2d const *, float *, float *))0xAD1C30)(&curved_hud_test, &p4, &p4.x, &p4.y);
		float v20 = fmaxf(0.5f - p1.x, 0.5f - p3.x);
		float v18 = fmaxf(p2.x - 0.5f, p4.x - 0.5f);
		if (v18 >= v20)
			v20 = v18;
		float v19 = fmaxf(0.5f - p1.y, 0.5f - p2.y);
		float v21 = fmaxf(p3.y - 0.5f, p4.y - 0.5f);
		if (v21 >= v19)
			v19 = v21;
		bitmap_scale_x = (v20 + 0.5f) * g_chud_draw_virtual_width / fmaxf(0.01f, placement_data->scale_x) / bitmap_width;
		bitmap_scale_y = (v19 + 0.5f) * g_chud_draw_virtual_height / fmaxf(0.01f, placement_data->scale_y) / bitmap_height;
		x0 = bitmap_info.bounds.x0;
		x1 = bitmap_info.bounds.x1;
		y0 = bitmap_info.bounds.y0;
		y1 = bitmap_info.bounds.y1;
	}
	else
	{
		border_thickness = 2.0f;
		float border_x = border_thickness / bitmap_info.width;
		float border_y = border_thickness / bitmap_info.height;
		x0 = bitmap_info.bounds.x0 - border_x;
		x1 = bitmap_info.bounds.x1 + border_x;
		y0 = bitmap_info.bounds.y0 - border_y;
		y1 = bitmap_info.bounds.y1 + border_y;
	}
	real_rectangle2d bounds1 = { 0.0f, bitmap_width * bitmap_scale_x, 0.0f, bitmap_height * bitmap_scale_y };
	real_rectangle2d bounds2 = { 0.0f - border_thickness, bitmap_width * bitmap_scale_x + border_thickness, 0.0f - border_thickness, bitmap_height * bitmap_scale_y + border_thickness };
	real_rectangle2d bounds3 = { x0, x1 * bitmap_scale_x, y0, y1 * bitmap_scale_y };
	chud_widget_build_quads_from_bounds(&bounds1, &bounds2, &bounds3, geometry, placement_data->scale_x, placement_data->scale_y);
	chud_compute_geometry_common(placement_data, geometry);
	return true;
}

void __fastcall c_chud_navpoint_manager__draw_hook(c_chud_navpoint_manager *thisptr, void *__formal, long output_user_index) // 0x10859B30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_chud_navpoint_manager__draw_hook@@YIXPAUc_chud_navpoint_manager@@PAXJ@Z");

	float scale;
	wchar_t *v17;
	real_rectangle2d *v19;
	float bounds_x0;
	s_chud_widget_geometry<s_widget_geometry_quad_simple> geometry;
	wchar_t buff[128];
	s_chud_render_data render_data;
	real_matrix4x3 matrix;
	real_rectangle2d bounds;
	float position_y;
	float offscreen_amount;
	bool distance_visible;
	bool name_visible;
	s_chud_globals_definition *chud_globals = chud_globals_definition_get();
	long (*const chud_globals_from_output_user)(long) = reinterpret_cast<long (*)(long)>(0xA895C0);
	long (*const player_mapping_output_user_active_count)() = reinterpret_cast<long (*)()>(0x589F00);
	void (*const chud_build_custom_render_data)(void *, long) = reinterpret_cast<void (*)(void *, long)>(0xAC67C0);
	bool (*const chud_compute_anchor_basis_from_tracker)(c_chud_point_tracker *, real_matrix4x3 *, bool) = reinterpret_cast<bool (*)(c_chud_point_tracker *, real_matrix4x3 *, bool)>(0xAC76A0);
	float (*const chud_build_geometry_from_navpoint)(long, long, long, float, float, s_chud_widget_geometry<s_widget_geometry_quad_simple> *) = reinterpret_cast<float (*)(long, long, long, float, float, s_chud_widget_geometry<s_widget_geometry_quad_simple> *)>(0xAC69E0);
	unsigned long (*const c_chud_navpoint_manager__get_managed_navpoint_arrow_color)(s_chud_managed_navpoint *) = reinterpret_cast<unsigned long (*)(s_chud_managed_navpoint *)>(0xAD1510);
	void (*const chud_expand_pixel32)(unsigned long, real_argb_color *) = reinterpret_cast<void (*)(unsigned long, real_argb_color *)>(0xAC9AA0);
	bool (*const chud_apply_render_data)(void *, bool) = reinterpret_cast<bool (*)(void *, bool)>(0xAC59F0);
	void (*const chud_draw_widget_geometry)(s_widget_geometry_properties *, real_matrix4x3 *, char, char) = reinterpret_cast<void (*)(s_widget_geometry_properties *, real_matrix4x3 *, char, char)>(0xAC9620);
	bool (*const chud_build_text_geometry)(s_widget_geometry_properties *, wchar_t *, __int32, bool, float, real_rectangle2d *) = reinterpret_cast<bool (*)(s_widget_geometry_properties *, wchar_t *, __int32, bool, float, real_rectangle2d *)>(0xAC6B80);
	s_chud_per_character_globals *hud_skin = &chud_globals->character_globals[chud_globals_from_output_user(output_user_index)];
	if (hud_skin->waypoints.index == -1)
		return;
	bool const use_h3_style = Modules::ModuleServer::Instance().VarHUDWaypointStyleClient->ValueInt ? true : false;
	for (long i = 0; i < 20; i++)
	{
		s_chud_managed_navpoint *managed_navpoint = &thisptr->m_navpoints[i];
		if (!managed_navpoint->visible)
			continue;
		bool v5 = managed_navpoint->navpoint.flags & 1;
		if (managed_navpoint->state != -1 && player_mapping_output_user_active_count() == 1)
			v5 = true;
		managed_navpoint->point_tracker.valid = true;
		managed_navpoint->point_tracker.world_point = managed_navpoint->navpoint.position;
		if (v5)
			((void (__thiscall *)(c_chud_point_tracker *, float))0xAD2360)(&managed_navpoint->point_tracker, 0.8f);
		else
			((void (__thiscall *)(c_chud_point_tracker *, float))0xAD2360)(&managed_navpoint->point_tracker, 0.0f);
		chud_build_custom_render_data(&render_data, 10);
		chud_compute_anchor_basis_from_tracker(&managed_navpoint->point_tracker, &matrix, true);
		distance_visible = (float)i == thisptr->m_distance_navpoint_index;
		name_visible = i == thisptr->m_name_navpoint_index;
		position_y = managed_navpoint->point_tracker.offscreen_amount;
		scale = managed_navpoint->scale;
		offscreen_amount = 0.0f;
		*(long *)geometry.texture_ref = -1;
		if (managed_navpoint->navpoint.arrow_icon != -1 && (position_y == 0.0 || v5))
		{
			float icon_scale = 1.0f;
			if (use_h3_style && managed_navpoint->navpoint.arrow_icon < 3 && hud_skin->waypoint_arrrow_scale != 0.0f)
				icon_scale = hud_skin->waypoint_arrrow_scale + 0.6f;
			offscreen_amount = 0.0f - chud_build_geometry_from_navpoint(output_user_index, 1, managed_navpoint->navpoint.arrow_icon, 0.0f, scale * icon_scale, &geometry);
			chud_expand_pixel32(c_chud_navpoint_manager__get_managed_navpoint_arrow_color(managed_navpoint), render_data.colors);
			render_data.opacity = managed_navpoint->opacity * managed_navpoint->navpoint.opacity;
			if (chud_apply_render_data(&render_data, false))
				chud_draw_widget_geometry(&geometry, &matrix, 0, 0);
		}
		if (position_y != 0.0)
			continue;
		if (distance_visible)
		{
			_snwprintf_s(buff, -1, L"%s", thisptr->m_distance_text);
			bounds.x0 = 0.0f;
			bounds.x1 = (thisptr->m_distance_reveal_width + 1.0f) * thisptr->m_distance_reveal;
			bounds.y0 = 0.0f;
			bounds.y1 = 1000.0f;
			if (chud_build_text_geometry(&geometry, thisptr->m_distance_text, 6, false, 1.0f, &bounds))
			{
				(*(real_rectangle2d *)geometry.string_bounds).x1 = thisptr->m_distance_reveal * thisptr->m_distance_reveal_width;
				(*(real_point2d *)geometry.widget_offset).x = (*(real_rectangle2d *)geometry.string_bounds).x0;
				(*(real_point2d *)geometry.widget_offset).y = (*(real_rectangle2d *)geometry.string_bounds).y1 - (*(real_rectangle2d *)geometry.string_bounds).y0 + (*(real_rectangle2d *)geometry.string_bounds).y0;
				geometry.field_8 = 0;
				geometry.scale_x = scale * 0.75;
				geometry.scale_y = scale * 0.75;
				geometry.position.x = scale * 14.0;
				geometry.position.y = 0.0f;
				geometry.position.z = 0.0f;
				(*(real_vector3d *)geometry.angles).i = 0.0f;
				(*(real_vector3d *)geometry.angles).j = 0.0f;
				(*(real_vector3d *)geometry.angles).k = 0.0f;
				chud_expand_pixel32(eldorado::c_chud_navpoint_manager_get_managed_navpoint_text_color(managed_navpoint), render_data.colors);
				render_data.opacity = managed_navpoint->opacity * managed_navpoint->navpoint.opacity;
				if (chud_apply_render_data(&render_data, false))
					chud_draw_widget_geometry(&geometry, &matrix, 0, 0);
			}
		}
		if (use_h3_style)
			goto H3_NAMETAG;
	H3_OBJECTIVE:
			if (managed_navpoint->navpoint.objective_icon != -1)
			{
				float height = chud_build_geometry_from_navpoint(output_user_index, 0, managed_navpoint->navpoint.objective_icon, offscreen_amount, scale, &geometry);
				offscreen_amount -= height;
				chud_expand_pixel32(((unsigned long (*const)(s_chud_managed_navpoint *))0xAD15E0)(managed_navpoint), render_data.colors);
				render_data.opacity = managed_navpoint->opacity * managed_navpoint->navpoint.opacity;
				if (chud_apply_render_data(&render_data, false))
					chud_draw_widget_geometry(&geometry, &matrix, 0, 0);
			}
			if (use_h3_style)
				continue;
	H3_NAMETAG:
		if (wcsnlen(managed_navpoint->navpoint.service_tag, 5) || name_visible)
		{
			if (name_visible)
			{
				_snwprintf_s(buff, -1, L"%s%s", thisptr->m_player_name, managed_navpoint->navpoint.service_tag);
				bounds.x0 = (1.0 - thisptr->m_name_reveal) * thisptr->m_name_reveal_width;
				bounds.x1 = 1000.0f;
				bounds.y0 = 0.0f;
				bounds.y1 = 1000.0f;
				v17 = buff;
				v19 = &bounds;
			}
			else
			{
				v17 = managed_navpoint->navpoint.service_tag;
				v19 = nullptr;
			}
			if (chud_build_text_geometry(&geometry, v17, 6, false, 1.0f, v19))
			{
				if (name_visible)
					(*(real_rectangle2d *)geometry.string_bounds).x0 = bounds_x0 = (1.0f - thisptr->m_name_reveal) * thisptr->m_name_reveal_width;
				else
					bounds_x0 = (*(real_rectangle2d *)geometry.string_bounds).x0;
				(*(real_point2d *)geometry.widget_offset).x = ((*(real_rectangle2d *)geometry.string_bounds).x1 - bounds_x0) * 0.5f + bounds_x0;
				(*(real_point2d *)geometry.widget_offset).y = (*(real_rectangle2d *)geometry.string_bounds).y1 - (*(real_rectangle2d *)geometry.string_bounds).y0 + (*(real_rectangle2d *)geometry.string_bounds).y0;
				geometry.field_8 = 0;
				geometry.scale_x = scale;
				geometry.scale_y = scale;
				geometry.position.x = 0.0f;
				geometry.position.y = offscreen_amount;
				geometry.position.z = 0.0f;
				(*(real_vector3d *)geometry.angles).i = 0.0f;
				(*(real_vector3d *)geometry.angles).j = 0.0f;
				(*(real_vector3d *)geometry.angles).k = 0.0f;
				offscreen_amount -= ((*(real_rectangle2d *)geometry.string_bounds).y1 - (*(real_rectangle2d *)geometry.string_bounds).y0) * scale;
				chud_expand_pixel32(eldorado::c_chud_navpoint_manager_get_managed_navpoint_text_color(managed_navpoint), render_data.colors);
				render_data.opacity = managed_navpoint->opacity * managed_navpoint->navpoint.opacity;
				if (chud_apply_render_data(&render_data, false))
					chud_draw_widget_geometry(&geometry, &matrix, 0, 0);
			}
		}
		if (use_h3_style)
			goto H3_OBJECTIVE;
	}
}

void __fastcall c_chud_update_user_data__compute_weapon_update_hook(void *thisptr, void *unused, long weapon_index, long interface_index, s_aim_assist_targeting_result *targeting_result) // 0x1085ABE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_chud_update_user_data__compute_weapon_update_hook@@YIXPAX0JJPAUs_aim_assist_targeting_result@@@Z");

	void (__thiscall *const c_chud_update_user_data__compute_weapon_update)(void *, long, long, s_aim_assist_targeting_result *) = (void (__thiscall *)(void *, long, long, s_aim_assist_targeting_result *))0xA8AED0;
	c_chud_update_user_data__compute_weapon_update(thisptr, weapon_index, interface_index, targeting_result);
	if (weapon_has_bottomless_clip(weapon_index))
	{
		long offset = interface_index * 0x5C;
		*(float *)((unsigned char *)thisptr + offset + 0x34) = 3.4028235e38f;
		*(float *)((unsigned char *)thisptr + offset + 0x48) = 3.4028235e38f;
		*(float *)((unsigned char *)thisptr + offset + 0x50) = 3.4028235e38f;
	}
}

void chud_get_target_tracking_render_point_hook(c_aim_target_object *aim_target_object, real_point3d *point) // 0x1085D9F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?chud_get_target_tracking_render_point_hook@@YAXPAUc_aim_target_object@@PAUreal_point3d@@@Z");

	void (__thiscall *const c_aim_target_object__get_target_point)(c_aim_target_object *, real_point3d *) = reinterpret_cast<void (__thiscall *)(c_aim_target_object *, real_point3d *)>(0x588E60);
	s_model_target *(__thiscall *const get_targeted_model_targets_block)(c_aim_target_object *) = reinterpret_cast<s_model_target *(__thiscall *)(c_aim_target_object *)>(0x588DB0);
	void (*const get_tracking_point_fallback)(long, real_point3d *) = reinterpret_cast<void (*)(long, real_point3d *)>(0xB2E620);
	static c_aim_target_object last_render_state;

	if (!((bool (__thiscall *)(c_aim_target_object *))0x589020)(aim_target_object))
	{
		get_tracking_point_fallback(aim_target_object->object_index, point);
		return;
	}

	s_model_target *target_block = get_targeted_model_targets_block(aim_target_object);
	if (!target_block)
	{
		get_tracking_point_fallback(aim_target_object->object_index, point);
		return;
	}

	if (target_block->flags & 4)
	{
		c_aim_target_object__get_target_point(aim_target_object, point);
		last_render_state = *aim_target_object;
	}
	else if (aim_target_object->object_index == last_render_state.object_index)
	{
		c_aim_target_object__get_target_point(&last_render_state, point);
	}
	else
	{
		get_tracking_point_fallback(aim_target_object->object_index, point);
	}
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

/* ---------- explicit instantiations */
template s_chud_widget_geometry<s_widget_geometry_quad_simple>::s_chud_widget_geometry();
