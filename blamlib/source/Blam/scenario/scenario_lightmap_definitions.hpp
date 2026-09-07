#ifndef __BLAM_SCENARIO_SCENARIO_LIGHTMAP_DEFINITIONS_HPP__
#define __BLAM_SCENARIO_SCENARIO_LIGHTMAP_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/items/equipment_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct s_half_rgb_lightprobe;
struct s_scenario_lightmap_air_lightprobe;
struct s_scenario_lightmap_cluster_static_per_vertex_lighting;
struct s_scenario_lightmap_instanced_geometry_lighting;
struct s_scenario_lightmap_luminance_scale;
struct s_scenario_lightmap_machine_lightprobe;
struct s_scenario_lightmap_machine_lightprobes;
struct s_scenario_lightmap_scenery_lightprobe;
struct s_scenario_lightmap_static_per_vertex_lighting;
struct s_tag_block;

/* ---------- constants */

/* ---------- definitions */

struct s_scenario_lightmap_cluster_static_per_vertex_lighting
{
	short lightmap_bitmaps_image_index; // 0x0
	short instance_index; // 0x2
};
static_assert(sizeof(s_scenario_lightmap_cluster_static_per_vertex_lighting) == 4, "Invalid s_scenario_lightmap_cluster_static_per_vertex_lighting size");

struct s_scenario_lightmap_instanced_geometry_lighting
{
	short lightmap_bitmaps_image_index; // 0x0
	short instanced_mesh_index; // 0x2
	short unknown_probe_index; // 0x4
	unsigned char __pad0[2]; // 0x6
};
static_assert(sizeof(s_scenario_lightmap_instanced_geometry_lighting) == 8, "Invalid s_scenario_lightmap_instanced_geometry_lighting size");

struct s_scenario_lightmap_static_per_vertex_lighting
{
	s_tag_block unused_tag_vertex_buffer; // 0x0
	long vertex_buffer_index; // 0xC
};
static_assert(sizeof(s_scenario_lightmap_static_per_vertex_lighting) == 16, "Invalid s_scenario_lightmap_static_per_vertex_lighting size");

struct s_half_rgb_lightprobe
{
	unsigned short dominant_direction_i; // 0x0
	unsigned short dominant_direction_j; // 0x2
	unsigned short dominant_direction_k; // 0x4
	unsigned char __pad0[2]; // 0x6
	unsigned short dominant_intensity_i; // 0x8
	unsigned short dominant_intensity_j; // 0xA
	unsigned short dominant_intensity_k; // 0xC
	unsigned char __pad1[2]; // 0xE
	unsigned short coefficents_r[9]; // 0x10
	unsigned short coefficents_g[9]; // 0x22
	unsigned short coefficents_b[9]; // 0x34
	unsigned char __pad2[2]; // 0x46
};
static_assert(sizeof(s_half_rgb_lightprobe) == 72, "Invalid s_half_rgb_lightprobe size");

struct s_scenario_lightmap_scenery_lightprobe
{
	long unknown1; // 0x0
	short unknown2; // 0x4
	unsigned char unknown3; // 0x6
	unsigned char unknown4; // 0x7
	s_half_rgb_lightprobe lightprobe; // 0x8
};
static_assert(sizeof(s_scenario_lightmap_scenery_lightprobe) == 80, "Invalid s_scenario_lightmap_scenery_lightprobe size");

#pragma pack(push, 4)
struct s_scenario_lightmap_machine_lightprobe
{
	real_point3d position; // 0x0
	s_half_rgb_lightprobe lightprobe; // 0xC
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_lightmap_machine_lightprobe) == 84, "Invalid s_scenario_lightmap_machine_lightprobe size");

#pragma pack(push, 4)
struct s_scenario_lightmap_machine_lightprobes
{
	long unknown1; // 0x0
	short unknown2; // 0x4
	short unknown3; // 0x6
	real_point3d unknown4; // 0x8
	real_point3d unknown5; // 0x14
	c_tag_block<s_scenario_lightmap_machine_lightprobe> lightprobes; // 0x20
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_lightmap_machine_lightprobes) == 44, "Invalid s_scenario_lightmap_machine_lightprobes size");

#pragma pack(push, 4)
struct s_scenario_lightmap_air_lightprobe
{
	real_point3d position; // 0x0
	unsigned long name; // 0xC
	long flags; // 0x10
	s_half_rgb_lightprobe lightprobe; // 0x14
};
#pragma pack(pop)
static_assert(sizeof(s_scenario_lightmap_air_lightprobe) == 92, "Invalid s_scenario_lightmap_air_lightprobe size");

struct s_scenario_lightmap_luminance_scale
{
	float scale; // 0x0
	float unused1; // 0x4
	float unused2; // 0x8
	float unused3; // 0xC
	float unused4; // 0x10
	float unused5; // 0x14
};
static_assert(sizeof(s_scenario_lightmap_luminance_scale) == 24, "Invalid s_scenario_lightmap_luminance_scale size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_SCENARIO_SCENARIO_LIGHTMAP_DEFINITIONS_HPP__
