#ifndef __BLAM_SKY_ATM_ATMOSPHERE_HPP__
#define __BLAM_SKY_ATM_ATMOSPHERE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/sky_atm/sky_atm_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"

/* ---------- forward declarations */

struct c_atmosphere_fog_interface;
struct c_atmosphere_setting;
struct real_point3d;
struct real_rgb_color;
struct real_vector3d;
struct s_cluster_reference;
struct s_weighted_atmosphere_parameters;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_weighted_atmosphere_parameters
{
	bool valid; // 0x0
	real_rgb_color sun_color; // 0x4
	real_vector3d sun_direction; // 0x10
	float distance_bias; // 0x1C
	float max_fog_thickness; // 0x20
	real_vector3d beta_m; // 0x24
	real_vector3d beta_p; // 0x30
	real_vector3d beta_m_theta_prefix; // 0x3C
	real_vector3d beta_p_theta_prefix; // 0x48
	float sun_phase_function; // 0x54
	float sea_level; // 0x58
	float mie_height_scale; // 0x5C
	float rayleign_height_scale; // 0x60
	float sheet_density; // 0x64
	float full_intensity_height; // 0x68
	float half_intensity_height; // 0x6C
	real_vector3d wind_direction; // 0x70
};
#pragma pack(pop)
static_assert(sizeof(s_weighted_atmosphere_parameters) == 124, "Invalid s_weighted_atmosphere_parameters size");

struct c_atmosphere_fog_interface
{
	static void (*const compute_cluster_weights)(s_cluster_reference, real_point3d *);
	static void (*const sample_atmosphere)(s_cluster_reference, s_weighted_atmosphere_parameters *);
	static void (*const set_constant)(s_weighted_atmosphere_parameters *, bool, bool);
	static void (*const accumulate_atmosphere_settings)(s_cluster_reference, c_atmosphere_setting *, s_weighted_atmosphere_parameters *, float);
	static long &g_custom_setting_index;
};
static_assert(sizeof(c_atmosphere_fog_interface) == 1, "Invalid c_atmosphere_fog_interface size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_SKY_ATM_ATMOSPHERE_HPP__
