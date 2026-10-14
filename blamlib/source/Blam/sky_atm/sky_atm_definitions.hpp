#ifndef __BLAM_SKY_ATM_SKY_ATM_DEFINITIONS_HPP__
#define __BLAM_SKY_ATM_SKY_ATM_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct c_atmosphere_setting;
struct c_sky_atm_parameters;
struct c_underwater_setting;
struct real_rgb_color;
struct real_vector3d;
struct s_tag_reference;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct c_atmosphere_setting
{
	c_flags<enum e_atmosphere_flags,unsigned short> flags; // 0x0
	unsigned char abcdefgh[2]; // 0x2
	unsigned long name; // 0x4
	float pitch; // 0x8
	float heading; // 0xC
	real_rgb_color color; // 0x10
	float intensity; // 0x1C
	float sea_level; // 0x20
	float rayleign_height_scale; // 0x24
	float mie_height_scale; // 0x28
	float rayleigh_multiplier; // 0x2C
	float mie_multiplier; // 0x30
	float sun_phase_function; // 0x34
	float de_saturation; // 0x38
	float distance_bias; // 0x3C
	float max_fog_thickness; // 0x40
	real_vector3d beta_m; // 0x44
	real_vector3d beta_p; // 0x50
	real_vector3d beta_m_theta_prefix; // 0x5C
	real_vector3d beta_p_theta_prefix; // 0x68
	float sheet_density; // 0x74
	float full_intensity_height; // 0x78
	float half_intensity_height; // 0x7C
	real_vector3d wind_direction; // 0x80
	s_tag_reference weather_effect; // 0x8C
	float runtime_weight; // 0x9C
	float runtime_effect_weight; // 0xA0
	// implicit: c_atmosphere_setting(c_atmosphere_setting const &), c_atmosphere_setting(), operator=(c_atmosphere_setting const &)
	// - declaring them makes the struct a non-aggregate, and `c_atmosphere_setting x = {}` then calls a constructor instead of
	//   default-constructing `flags` and zero-filling the rest
};
#pragma pack(pop)
static_assert(sizeof(c_atmosphere_setting) == 164, "Invalid c_atmosphere_setting size");

#pragma pack(push, 4)
struct c_underwater_setting
{
	unsigned long name; // 0x0
	float murkiness; // 0x4
	real_rgb_color fog_color; // 0x8
};
#pragma pack(pop)
static_assert(sizeof(c_underwater_setting) == 20, "Invalid c_underwater_setting size");

#pragma pack(push, 4)
struct c_sky_atm_parameters
{
	c_flags<enum e_sky_atm_flags,unsigned short> flags; // 0x0
	unsigned char gsoinbszid[2]; // 0x2
	s_tag_reference fog_bitmap; // 0x4
	float texture_repeat_rate; // 0x14
	float distance_between_sheets; // 0x18
	float depth_fade_factor; // 0x1C
	float cluster_search_radius; // 0x20
	float falloff_start_distance; // 0x24
	float distance_falloff_power; // 0x28
	float transparent_sort_distance; // 0x2C
	c_enum<enum e_transparent_sort_layer,char> transparent_sort_layer; // 0x30
	unsigned char undfdfdsed[3]; // 0x31
	c_tag_block<c_atmosphere_setting> atmosphere_settings; // 0x34
	c_tag_block<c_underwater_setting> underwater_settings; // 0x40
	c_sky_atm_parameters(c_sky_atm_parameters &); /* compiler_generated() */
	c_sky_atm_parameters(c_sky_atm_parameters const &); /* compiler_generated() */
	c_sky_atm_parameters(); /* compiler_generated() */
	c_sky_atm_parameters &operator=(c_sky_atm_parameters &); /* compiler_generated() */
	c_sky_atm_parameters &operator=(c_sky_atm_parameters const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(c_sky_atm_parameters) == 76, "Invalid c_sky_atm_parameters size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_SKY_ATM_SKY_ATM_DEFINITIONS_HPP__
