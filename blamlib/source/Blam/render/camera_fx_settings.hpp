#ifndef __BLAM_RENDER_CAMERA_FX_SETTINGS_HPP__
#define __BLAM_RENDER_CAMERA_FX_SETTINGS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/function_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class c_function_definition;
struct c_camera_fx_settings;
struct c_camera_fx_values;
struct c_exposure;
struct real_rgb_color;
struct s_camera_fx_bling_angle_struct;
struct s_camera_fx_bling_count_struct;
struct s_camera_fx_bling_intensity_struct;
struct s_camera_fx_bling_size_struct;
struct s_camera_fx_bloom_inherent_struct;
struct s_camera_fx_bloom_intensity_struct;
struct s_camera_fx_bloom_large_color_struct;
struct s_camera_fx_bloom_medium_color_struct;
struct s_camera_fx_bloom_point_struct;
struct s_camera_fx_bloom_small_color_struct;
struct s_camera_fx_color_grading_struct;
struct s_camera_fx_exposure_anti_bloom_struct;
struct s_camera_fx_exposure_sensitivity_struct;
struct s_camera_fx_exposure_struct;
struct s_camera_fx_lightshafts_struct;
struct s_camera_fx_self_illum_preferred_struct;
struct s_camera_fx_self_illum_scale_struct;
struct s_camera_fx_ssao_struct;
struct s_color_grading_brightness_contrast_block;
struct s_color_grading_cmy_struct;
struct s_color_grading_cmyb_struct;
struct s_color_grading_color_balance_block;
struct s_color_grading_colorize_effect_block;
struct s_color_grading_curves_editor_block;
struct s_color_grading_hslv_block;
struct s_color_grading_selective_color_block;
struct s_hue_saturation_control;
struct s_scripted_exposure_globals;

/* ---------- constants */

/* ---------- definitions */

struct s_camera_fx_exposure_struct
{
	unsigned short flags; // 0x0
	float exposure; // 0x4
	float maximum_change; // 0x8
	float blend_speed; // 0xC
	float minimum; // 0x10
	float maximum; // 0x14
	float autoexposure_screen_brightness; // 0x18
	float autoexposure_delay; // 0x1C
};
static_assert(sizeof(s_camera_fx_exposure_struct) == 32, "Invalid s_camera_fx_exposure_struct size");
static_assert(offsetof(s_camera_fx_exposure_struct, exposure) == 0x4, "s_camera_fx_exposure_struct::exposure moved when its reconstructed padding was removed");

struct s_camera_fx_exposure_sensitivity_struct
{
	unsigned short flags; // 0x0
	float sensitivity_01; // 0x4
};
static_assert(sizeof(s_camera_fx_exposure_sensitivity_struct) == 8, "Invalid s_camera_fx_exposure_sensitivity_struct size");
static_assert(offsetof(s_camera_fx_exposure_sensitivity_struct, sensitivity_01) == 0x4, "s_camera_fx_exposure_sensitivity_struct::sensitivity_01 moved when its reconstructed padding was removed");

struct s_camera_fx_exposure_anti_bloom_struct
{
	unsigned short flags; // 0x0
	float antibloom_01; // 0x4
};
static_assert(sizeof(s_camera_fx_exposure_anti_bloom_struct) == 8, "Invalid s_camera_fx_exposure_anti_bloom_struct size");
static_assert(offsetof(s_camera_fx_exposure_anti_bloom_struct, antibloom_01) == 0x4, "s_camera_fx_exposure_anti_bloom_struct::antibloom_01 moved when its reconstructed padding was removed");

struct s_camera_fx_bloom_point_struct
{
	unsigned short flags; // 0x0
	float bloom_point; // 0x4
	float maximum_change; // 0x8
	float blend_speed; // 0xC
};
static_assert(sizeof(s_camera_fx_bloom_point_struct) == 16, "Invalid s_camera_fx_bloom_point_struct size");
static_assert(offsetof(s_camera_fx_bloom_point_struct, bloom_point) == 0x4, "s_camera_fx_bloom_point_struct::bloom_point moved when its reconstructed padding was removed");

struct s_camera_fx_bloom_inherent_struct
{
	unsigned short flags; // 0x0
	float inherent_bloom; // 0x4
	float maximum_change; // 0x8
	float blend_speed; // 0xC
};
static_assert(sizeof(s_camera_fx_bloom_inherent_struct) == 16, "Invalid s_camera_fx_bloom_inherent_struct size");
static_assert(offsetof(s_camera_fx_bloom_inherent_struct, inherent_bloom) == 0x4, "s_camera_fx_bloom_inherent_struct::inherent_bloom moved when its reconstructed padding was removed");

struct s_camera_fx_bloom_intensity_struct
{
	unsigned short flags; // 0x0
	float bloom_intensity; // 0x4
	float maximum_change; // 0x8
	float blend_speed; // 0xC
};
static_assert(sizeof(s_camera_fx_bloom_intensity_struct) == 16, "Invalid s_camera_fx_bloom_intensity_struct size");
static_assert(offsetof(s_camera_fx_bloom_intensity_struct, bloom_intensity) == 0x4, "s_camera_fx_bloom_intensity_struct::bloom_intensity moved when its reconstructed padding was removed");

struct s_camera_fx_bloom_large_color_struct
{
	unsigned short flags; // 0x0
	real_rgb_color large_color; // 0x4
};
static_assert(sizeof(s_camera_fx_bloom_large_color_struct) == 16, "Invalid s_camera_fx_bloom_large_color_struct size");
static_assert(offsetof(s_camera_fx_bloom_large_color_struct, large_color) == 0x4, "s_camera_fx_bloom_large_color_struct::large_color moved when its reconstructed padding was removed");

struct s_camera_fx_bloom_medium_color_struct
{
	unsigned short flags; // 0x0
	real_rgb_color medium_color; // 0x4
};
static_assert(sizeof(s_camera_fx_bloom_medium_color_struct) == 16, "Invalid s_camera_fx_bloom_medium_color_struct size");
static_assert(offsetof(s_camera_fx_bloom_medium_color_struct, medium_color) == 0x4, "s_camera_fx_bloom_medium_color_struct::medium_color moved when its reconstructed padding was removed");

struct s_camera_fx_bloom_small_color_struct
{
	unsigned short flags; // 0x0
	real_rgb_color small_color; // 0x4
};
static_assert(sizeof(s_camera_fx_bloom_small_color_struct) == 16, "Invalid s_camera_fx_bloom_small_color_struct size");
static_assert(offsetof(s_camera_fx_bloom_small_color_struct, small_color) == 0x4, "s_camera_fx_bloom_small_color_struct::small_color moved when its reconstructed padding was removed");

struct s_camera_fx_bling_intensity_struct
{
	unsigned short flags; // 0x0
	float bling_intensity; // 0x4
	float maximum_change; // 0x8
	float blend_speed; // 0xC
};
static_assert(sizeof(s_camera_fx_bling_intensity_struct) == 16, "Invalid s_camera_fx_bling_intensity_struct size");
static_assert(offsetof(s_camera_fx_bling_intensity_struct, bling_intensity) == 0x4, "s_camera_fx_bling_intensity_struct::bling_intensity moved when its reconstructed padding was removed");

struct s_camera_fx_bling_size_struct
{
	unsigned short flags; // 0x0
	float bling_length; // 0x4
	float maximum_change; // 0x8
	float blend_speed; // 0xC
};
static_assert(sizeof(s_camera_fx_bling_size_struct) == 16, "Invalid s_camera_fx_bling_size_struct size");
static_assert(offsetof(s_camera_fx_bling_size_struct, bling_length) == 0x4, "s_camera_fx_bling_size_struct::bling_length moved when its reconstructed padding was removed");

struct s_camera_fx_bling_angle_struct
{
	unsigned short flags; // 0x0
	float bling_angle; // 0x4
	float maximum_change; // 0x8
	float blend_speed; // 0xC
};
static_assert(sizeof(s_camera_fx_bling_angle_struct) == 16, "Invalid s_camera_fx_bling_angle_struct size");
static_assert(offsetof(s_camera_fx_bling_angle_struct, bling_angle) == 0x4, "s_camera_fx_bling_angle_struct::bling_angle moved when its reconstructed padding was removed");

struct s_camera_fx_bling_count_struct
{
	unsigned short flags; // 0x0
	short bling_spikes; // 0x2
};
static_assert(sizeof(s_camera_fx_bling_count_struct) == 4, "Invalid s_camera_fx_bling_count_struct size");

struct s_camera_fx_self_illum_preferred_struct
{
	unsigned short flags; // 0x0
	float preferred_exposure; // 0x4
	float maximum_change; // 0x8
	float blend_speed; // 0xC
};
static_assert(sizeof(s_camera_fx_self_illum_preferred_struct) == 16, "Invalid s_camera_fx_self_illum_preferred_struct size");
static_assert(offsetof(s_camera_fx_self_illum_preferred_struct, preferred_exposure) == 0x4, "s_camera_fx_self_illum_preferred_struct::preferred_exposure moved when its reconstructed padding was removed");

struct s_camera_fx_self_illum_scale_struct
{
	unsigned short flags; // 0x0
	float exposure_change; // 0x4
	float maximum_change; // 0x8
	float blend_speed; // 0xC
};
static_assert(sizeof(s_camera_fx_self_illum_scale_struct) == 16, "Invalid s_camera_fx_self_illum_scale_struct size");
static_assert(offsetof(s_camera_fx_self_illum_scale_struct, exposure_change) == 0x4, "s_camera_fx_self_illum_scale_struct::exposure_change moved when its reconstructed padding was removed");

struct s_camera_fx_ssao_struct
{
	unsigned long flags; // 0x0
	float intensity; // 0x4
	float radius; // 0x8
	float sample_z_threshold; // 0xC
};
static_assert(sizeof(s_camera_fx_ssao_struct) == 16, "Invalid s_camera_fx_ssao_struct size");

struct s_color_grading_curves_editor_block
{
	unsigned long flags; // 0x0
	long mode; // 0x4
	c_function_definition brightness_curve; // 0x8
	c_function_definition red_curve; // 0x1C
	c_function_definition green_curve; // 0x30
	c_function_definition blue_curve; // 0x44
	s_color_grading_curves_editor_block(s_color_grading_curves_editor_block &); /* compiler_generated() */
	s_color_grading_curves_editor_block(s_color_grading_curves_editor_block const &); /* compiler_generated() */
	s_color_grading_curves_editor_block(); /* compiler_generated() */
	s_color_grading_curves_editor_block &operator=(s_color_grading_curves_editor_block &); /* compiler_generated() */
	s_color_grading_curves_editor_block &operator=(s_color_grading_curves_editor_block const &); /* compiler_generated() */
};
static_assert(sizeof(s_color_grading_curves_editor_block) == 88, "Invalid s_color_grading_curves_editor_block size");

struct s_color_grading_brightness_contrast_block
{
	unsigned long flags; // 0x0
	float brightness; // 0x4
	float contrast; // 0x8
};
static_assert(sizeof(s_color_grading_brightness_contrast_block) == 12, "Invalid s_color_grading_brightness_contrast_block size");

struct s_color_grading_hslv_block
{
	unsigned long flags; // 0x0
	float hue; // 0x4
	float saturation; // 0x8
	float lightness; // 0xC
	float vibrance; // 0x10
};
static_assert(sizeof(s_color_grading_hslv_block) == 20, "Invalid s_color_grading_hslv_block size");

struct s_color_grading_colorize_effect_block
{
	unsigned long flags; // 0x0
	float blendfactor; // 0x4
	float hue; // 0x8
	float saturation; // 0xC
	float lightness; // 0x10
};
static_assert(sizeof(s_color_grading_colorize_effect_block) == 20, "Invalid s_color_grading_colorize_effect_block size");

struct s_color_grading_cmyb_struct
{
	float cyan; // 0x0
	float magenta; // 0x4
	float yellow; // 0x8
	float black; // 0xC
};
static_assert(sizeof(s_color_grading_cmyb_struct) == 16, "Invalid s_color_grading_cmyb_struct size");

#pragma pack(push, 4)
struct s_color_grading_selective_color_block
{
	unsigned long flags; // 0x0
	s_color_grading_cmyb_struct reds; // 0x4
	s_color_grading_cmyb_struct yellows; // 0x14
	s_color_grading_cmyb_struct greens; // 0x24
	s_color_grading_cmyb_struct cyans; // 0x34
	s_color_grading_cmyb_struct blues; // 0x44
	s_color_grading_cmyb_struct magentas; // 0x54
	s_color_grading_cmyb_struct whites; // 0x64
	s_color_grading_cmyb_struct neutrals; // 0x74
	s_color_grading_cmyb_struct blacks; // 0x84
};
#pragma pack(pop)
static_assert(sizeof(s_color_grading_selective_color_block) == 148, "Invalid s_color_grading_selective_color_block size");

struct s_color_grading_cmy_struct
{
	float cyan_red; // 0x0
	float magenta_green; // 0x4
	float yellow_blue; // 0x8
};
static_assert(sizeof(s_color_grading_cmy_struct) == 12, "Invalid s_color_grading_cmy_struct size");

struct s_color_grading_color_balance_block
{
	unsigned long flags; // 0x0
	s_color_grading_cmy_struct shadows; // 0x4
	s_color_grading_cmy_struct midtones; // 0x10
	s_color_grading_cmy_struct highlights; // 0x1C
};
static_assert(sizeof(s_color_grading_color_balance_block) == 40, "Invalid s_color_grading_color_balance_block size");

struct s_camera_fx_color_grading_struct
{
	unsigned long flags; // 0x0
	float blend_time; // 0x4
	c_tag_block<s_color_grading_curves_editor_block> curves_editor; // 0x8
	c_tag_block<s_color_grading_brightness_contrast_block> brightness_contrast; // 0x14
	c_tag_block<s_color_grading_hslv_block> hue_saturation_lightness_vibrance; // 0x20
	c_tag_block<s_color_grading_colorize_effect_block> colorize_effect; // 0x2C
	c_tag_block<s_color_grading_selective_color_block> selective_color; // 0x38
	c_tag_block<s_color_grading_color_balance_block> color_balance; // 0x44
};
static_assert(sizeof(s_camera_fx_color_grading_struct) == 80, "Invalid s_camera_fx_color_grading_struct size");

#pragma pack(push, 4)
struct s_camera_fx_lightshafts_struct
{
	unsigned long flags; // 0x0
	float pitch; // 0x4
	float heading; // 0x8
	real_rgb_color tint; // 0xC
	float depth_clamp; // 0x18
	float intensity_clamp; // 0x1C
	float falloff_radius; // 0x20
	float intensity; // 0x24
	float blur_radius; // 0x28
};
#pragma pack(pop)
static_assert(sizeof(s_camera_fx_lightshafts_struct) == 44, "Invalid s_camera_fx_lightshafts_struct size");

struct c_camera_fx_settings
{
	s_camera_fx_exposure_struct exposure; // 0x0
	s_camera_fx_exposure_sensitivity_struct auto_exposure_sensitivity; // 0x20
	s_camera_fx_exposure_anti_bloom_struct auto_exposure_anti_bloom; // 0x28
	s_camera_fx_bloom_point_struct bloom_point; // 0x30
	s_camera_fx_bloom_inherent_struct bloom_inherent; // 0x40
	s_camera_fx_bloom_intensity_struct bloom_intensity; // 0x50
	s_camera_fx_bloom_large_color_struct bloom_large_color; // 0x60
	s_camera_fx_bloom_medium_color_struct bloom_medium_color; // 0x70
	s_camera_fx_bloom_small_color_struct bloom_small_color; // 0x80
	s_camera_fx_bling_intensity_struct bling_intensity; // 0x90
	s_camera_fx_bling_size_struct bling_size; // 0xA0
	s_camera_fx_bling_angle_struct bling_angle; // 0xB0
	s_camera_fx_bling_count_struct bling_count; // 0xC0
	s_camera_fx_self_illum_preferred_struct self_illum_preferred; // 0xC4
	s_camera_fx_self_illum_scale_struct self_illum_scale; // 0xD4
	s_camera_fx_ssao_struct ssao; // 0xE4
	s_camera_fx_color_grading_struct color_grading; // 0xF4
	s_camera_fx_lightshafts_struct lightshafts; // 0x144
	static _inline c_camera_fx_settings *get(long index);
};
static_assert(sizeof(c_camera_fx_settings) == 368, "Invalid c_camera_fx_settings size");

struct c_camera_fx_values
{
	long occlusion_type; // 0x0
	long occlusion_query_index; // 0x4
	float brightness; // 0x8
	float field_C; // 0xC
	float exposure; // 0x10
	float field_14; // 0x14
	float exposure_samples[60]; // 0x18
	long exposure_sample_count; // 0x108
	float exposure_boost; // 0x10C
	long auto_exposure_sensitivity; // 0x110
	float exposure_scale; // 0x114
	float highlight_bloom; // 0x118
	float inherent_bloom; // 0x11C
	float bloom_intensity; // 0x120
	float bling_intensity; // 0x124
	__int32 bling_size; // 0x128
	__int32 bling_angle; // 0x12C
	short bling_spikes; // 0x130
	short padd16; // 0x132
	real_rgb_color highlight_bloom_tint; // 0x134
	real_rgb_color inherent_bloom_tint; // 0x140
	real_rgb_color lighting_bloom_tint; // 0x14C
	float self_illum_preferred; // 0x158
	__int32 self_illum_scale; // 0x15C
	float exposure_exponent; // 0x160
	s_camera_fx_ssao_struct ssao; // 0x164
	s_camera_fx_color_grading_struct color_grading; // 0x174
	s_camera_fx_lightshafts_struct light_shafts; // 0x1C4
	static float const &g_exposure_stops;
};
static_assert(sizeof(c_camera_fx_values) == 496, "Invalid c_camera_fx_values size");

struct s_hue_saturation_control
{
	float hue_base; // 0x0
	float saturation_base; // 0x4
	float red_scale; // 0x8
	float green_scale; // 0xC
	float blue_scale; // 0x10
	static void (*const set_hue_saturaton_and_color_filters)(s_hue_saturation_control *, float, float, float, real_rgb_color const *, real_rgb_color const *);
};
static_assert(sizeof(s_hue_saturation_control) == 20, "Invalid s_hue_saturation_control size");

struct c_exposure
{
	__int32 flags; // 0x0
	float field_4; // 0x4
	float field_8; // 0x8
	float field_C; // 0xC
	float field_10; // 0x10
	static inline float (__thiscall *const &set_exposure)(c_exposure *, float) = reinterpret_cast<float (__thiscall *)(c_exposure *, float)>(0xA2AE30);  // hades: an inline reference bound to a temporary, as the original's `$S` shows
};
static_assert(sizeof(c_exposure) == 20, "Invalid c_exposure size");

#pragma pack(push, 4)
struct s_scripted_exposure_globals
{
	c_exposure exposure; // 0x0
	long field_14; // 0x14
	long field_18; // 0x18
	long field_1C; // 0x1C
	long field_20; // 0x20
	long field_24; // 0x24
	long field_28; // 0x28
	long field_2C; // 0x2C
	long field_30; // 0x30
};
#pragma pack(pop)
static_assert(sizeof(s_scripted_exposure_globals) == 52, "Invalid s_scripted_exposure_globals size");

/* ---------- prototypes */

extern void *(__cdecl *const tag_get)(unsigned long group, long index);  // hades: added for 0X108EEF00

/* ---------- globals */

/* ---------- public code */

inline c_camera_fx_settings *c_camera_fx_settings::get(long index) // 0x108EEF00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get@c_camera_fx_settings@@SAPAU1@J@Z");

	return (c_camera_fx_settings *)tag_get(0x63667873, index);
}

/* ---------- private code */

#endif // __BLAM_RENDER_CAMERA_FX_SETTINGS_HPP__
