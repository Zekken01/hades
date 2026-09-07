#ifndef __BLAM_OBJECTS_OBJECT_DEFINITIONS_HPP__
#define __BLAM_OBJECTS_OBJECT_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct real_bounds;
struct real_euler_angles3d;
struct real_rgb_color;
struct s_multiplayer_object_definition;
struct s_object_ai_properties_definition;
struct s_object_attachment_definition;
struct s_object_change_color_definition;
struct s_object_change_color_function_definition;
struct s_object_change_color_permutation_definition;
struct s_object_definition;
struct s_object_early_mover_obb_definition;
struct s_object_function_definition;
struct s_object_model_data_definition;
struct s_object_node_map_definition;
struct s_object_reviving_equipment_definition;
struct s_object_widget_definition;
struct s_tag_data;
struct s_tag_reference;

/* ---------- constants */

enum
{
	k_object_group_tag = 'obje', // 0x6F626A65
};

// e_object_change_color is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- definitions */

struct s_object_early_mover_obb_definition
{
	unsigned long name; // 0x0
	real_bounds x_bounds; // 0x4
	real_bounds y_bounds; // 0xC
	real_bounds z_bounds; // 0x14
	real_euler_angles3d angles; // 0x1C
};
static_assert(sizeof(s_object_early_mover_obb_definition) == 40, "Invalid s_object_early_mover_obb_definition size");

struct s_object_ai_properties_definition
{
	c_flags<enum e_object_ai_properties_flags,long> flags; // 0x0
	unsigned long ai_type_name; // 0x4
	c_enum<enum e_object_ai_size,short> size; // 0x8
	c_enum<enum e_object_ai_distance,short> leap_jump_speed; // 0xA
	s_object_ai_properties_definition(s_object_ai_properties_definition &); /* compiler_generated() */
	s_object_ai_properties_definition(s_object_ai_properties_definition const &); /* compiler_generated() */
	s_object_ai_properties_definition(); /* compiler_generated() */
	s_object_ai_properties_definition &operator=(s_object_ai_properties_definition &); /* compiler_generated() */
	s_object_ai_properties_definition &operator=(s_object_ai_properties_definition const &); /* compiler_generated() */
};
static_assert(sizeof(s_object_ai_properties_definition) == 12, "Invalid s_object_ai_properties_definition size");

#pragma pack(push, 4)
struct s_object_function_definition
{
	c_flags<enum e_object_function_flags,long> flags; // 0x0
	unsigned long import_name; // 0x4
	unsigned long export_name; // 0x8
	unsigned long turn_off_with; // 0xC
	float minimum_value; // 0x10
	s_tag_data default_function; // 0x14
	unsigned long scale_by; // 0x28
	s_object_function_definition(s_object_function_definition &); /* compiler_generated() */
	s_object_function_definition(s_object_function_definition const &); /* compiler_generated() */
	s_object_function_definition(); /* compiler_generated() */
	s_object_function_definition &operator=(s_object_function_definition &); /* compiler_generated() */
	s_object_function_definition &operator=(s_object_function_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_object_function_definition) == 44, "Invalid s_object_function_definition size");

#pragma pack(push, 4)
struct s_object_attachment_definition
{
	c_flags<enum e_object_attachment_atlas_flags,long> atlas_flags; // 0x0
	s_tag_reference type; // 0x4
	unsigned long marker; // 0x14
	c_enum<enum e_object_attachment_change_color,short> change_color; // 0x18
	c_flags<enum e_object_attachment_flags,unsigned short> flags; // 0x1A
	unsigned long primary_scale; // 0x1C
	unsigned long secondary_scale; // 0x20
	s_object_attachment_definition(s_object_attachment_definition &); /* compiler_generated() */
	s_object_attachment_definition(s_object_attachment_definition const &); /* compiler_generated() */
	s_object_attachment_definition(); /* compiler_generated() */
	s_object_attachment_definition &operator=(s_object_attachment_definition &); /* compiler_generated() */
	s_object_attachment_definition &operator=(s_object_attachment_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_object_attachment_definition) == 36, "Invalid s_object_attachment_definition size");

struct s_object_widget_definition
{
	s_tag_reference type; // 0x0
};
static_assert(sizeof(s_object_widget_definition) == 16, "Invalid s_object_widget_definition size");

struct s_object_change_color_permutation_definition
{
	float weight; // 0x0
	real_rgb_color color_lower_bound; // 0x4
	real_rgb_color color_upper_bound; // 0x10
	unsigned long variant_name; // 0x1C
};
static_assert(sizeof(s_object_change_color_permutation_definition) == 32, "Invalid s_object_change_color_permutation_definition size");

struct s_object_change_color_function_definition
{
	unsigned char __pad0[4]; // 0x0
	c_flags<enum e_object_change_color_function_flags,long> scale_flags; // 0x4
	real_rgb_color color_lower_bound; // 0x8
	real_rgb_color color_upper_bound; // 0x14
	unsigned long darken_by; // 0x20
	unsigned long scale_by; // 0x24
	s_object_change_color_function_definition(s_object_change_color_function_definition &); /* compiler_generated() */
	s_object_change_color_function_definition(s_object_change_color_function_definition const &); /* compiler_generated() */
	s_object_change_color_function_definition(); /* compiler_generated() */
	s_object_change_color_function_definition &operator=(s_object_change_color_function_definition &); /* compiler_generated() */
	s_object_change_color_function_definition &operator=(s_object_change_color_function_definition const &); /* compiler_generated() */
};
static_assert(sizeof(s_object_change_color_function_definition) == 40, "Invalid s_object_change_color_function_definition size");

struct s_object_change_color_definition
{
	c_tag_block<s_object_change_color_permutation_definition> initial_permutations; // 0x0
	c_tag_block<s_object_change_color_function_definition> functions; // 0xC
};
static_assert(sizeof(s_object_change_color_definition) == 24, "Invalid s_object_change_color_definition size");

struct s_object_node_map_definition
{
	char target_node; // 0x0
};
static_assert(sizeof(s_object_node_map_definition) == 1, "Invalid s_object_node_map_definition size");

struct s_object_reviving_equipment_definition
{
	s_tag_reference equipment; // 0x0
};
static_assert(sizeof(s_object_reviving_equipment_definition) == 16, "Invalid s_object_reviving_equipment_definition size");

#pragma pack(push, 4)
struct s_object_model_data_definition
{
	c_enum<enum e_object_model_data_type,short> type; // 0x0
	unsigned char __pad0[2]; // 0x2
	real_point3d offset; // 0x4
	float radius; // 0x10
	s_object_model_data_definition(s_object_model_data_definition &); /* compiler_generated() */
	s_object_model_data_definition(s_object_model_data_definition const &); /* compiler_generated() */
	s_object_model_data_definition(); /* compiler_generated() */
	s_object_model_data_definition &operator=(s_object_model_data_definition &); /* compiler_generated() */
	s_object_model_data_definition &operator=(s_object_model_data_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_object_model_data_definition) == 20, "Invalid s_object_model_data_definition size");

struct s_object_definition
{
	c_enum<enum e_object_type,short> object_type; // 0x0
	c_flags<enum e_object_definition_flags,unsigned short> object_flags; // 0x2
	float bounding_radius; // 0x4
	real_point3d bounding_offset; // 0x8
	float acceleration_scale; // 0x14
	c_enum<enum e_object_lightmap_shadow_mode,short> lightmap_shadow_mode; // 0x18
	c_enum<enum e_object_sweetener_size,char> sweetener_size; // 0x1A
	c_enum<enum e_object_water_density,char> water_density; // 0x1B
	c_enum<enum e_object_definition_runtime_flags,long> runtime_flags; // 0x1C
	float dynamic_light_sphere_radius; // 0x20
	real_point3d dynamic_light_sphere_offset; // 0x24
	unsigned long default_model_variant; // 0x30
	s_tag_reference model; // 0x34
	s_tag_reference crate_object; // 0x44
	s_tag_reference collision_damage; // 0x54
	c_tag_block<s_object_early_mover_obb_definition> early_mover_obb; // 0x64
	s_tag_reference creation_effect; // 0x70
	s_tag_reference material_effects; // 0x80
	s_tag_reference armor_sounds; // 0x90
	s_tag_reference melee_impact; // 0xA0
	c_tag_block<s_object_ai_properties_definition> ai_properties; // 0xB0
	c_tag_block<s_object_function_definition> functions; // 0xBC
	short hud_text_message_index; // 0xC8
	unsigned char __pad0[2]; // 0xCA
	c_tag_block<s_object_attachment_definition> attachments; // 0xCC
	c_tag_block<s_object_widget_definition> widgets; // 0xD8
	c_tag_block<s_object_change_color_definition> change_colors; // 0xE4
	c_tag_block<s_object_node_map_definition> node_maps; // 0xF0
	c_tag_block<s_multiplayer_object_definition> multiplayer_object; // 0xFC
	c_tag_block<s_object_reviving_equipment_definition> reviving_equipment; // 0x108
	c_tag_block<s_object_model_data_definition> model_data; // 0x114
	s_object_definition(s_object_definition &); /* compiler_generated() */
	s_object_definition(s_object_definition const &); /* compiler_generated() */
	s_object_definition(); /* compiler_generated() */
	s_object_definition &operator=(s_object_definition &); /* compiler_generated() */
	s_object_definition &operator=(s_object_definition const &); /* compiler_generated() */
};
static_assert(sizeof(s_object_definition) == 288, "Invalid s_object_definition size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_OBJECTS_OBJECT_DEFINITIONS_HPP__
