#ifndef __BLAM_FORGE_FORGE_GLOBALS_HPP__
#define __BLAM_FORGE_FORGE_GLOBALS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct real_euler_angles3d;
struct s_forge_description_text_entry;
struct s_forge_globals_definition;
struct s_forge_material;
struct s_forge_material_type;
struct s_forge_object_property_setter;
struct s_forge_palette_category;
struct s_forge_palette_item;
struct s_forge_sky_definition;
struct s_forge_weather_definition;
struct s_tag_reference;
union long_string;
union tag_string;

/* ---------- constants */

enum e_forge_object_property_setter_type
{
	_forge_object_property_setter_type_integer = 0,
	_forge_object_property_setter_type_real,
};

enum e_forge_object_property_setter_flags
{
	_forge_object_property_setter_flags_hidden_bit = 0,
};

/* ---------- definitions */

#pragma pack(push, 4)
struct s_forge_material_type
{
	tag_string name; // 0x0
	short collision_global_material_type; // 0x20
	short physics_global_material_type; // 0x22
};
#pragma pack(pop)
static_assert(sizeof(s_forge_material_type) == 36, "Invalid s_forge_material_type size");

#pragma pack(push, 2)
struct s_forge_material
{
	tag_string name; // 0x0
	c_tag_block_index<s_forge_material_type,short> material_type; // 0x20
	s_forge_material(s_forge_material &); /* compiler_generated() */
	s_forge_material(s_forge_material const &); /* compiler_generated() */
	s_forge_material(); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_forge_material) == 34, "Invalid s_forge_material size");

struct s_forge_object_property_setter
{
	unsigned short target; // 0x0
	c_enum<enum e_forge_object_property_setter_type,unsigned char> type; // 0x2
	c_flags<enum e_forge_object_property_setter_flags,unsigned char> flags; // 0x3
	long integer_value; // 0x4
	float real_value; // 0x8
	s_forge_object_property_setter(s_forge_object_property_setter &); /* compiler_generated() */
	s_forge_object_property_setter(s_forge_object_property_setter const &); /* compiler_generated() */
	s_forge_object_property_setter(); /* compiler_generated() */
	s_forge_object_property_setter &operator=(s_forge_object_property_setter &); /* compiler_generated() */
	s_forge_object_property_setter &operator=(s_forge_object_property_setter const &); /* compiler_generated() */
};
static_assert(sizeof(s_forge_object_property_setter) == 12, "Invalid s_forge_object_property_setter size");

struct s_forge_description_text_entry
{
	long_string text; // 0x0
};
static_assert(sizeof(s_forge_description_text_entry) == 256, "Invalid s_forge_description_text_entry size");

#pragma pack(push, 4)
struct s_forge_palette_category
{
	tag_string name; // 0x0
	short description_index; // 0x20
	short parent_category_index; // 0x22
};
#pragma pack(pop)
static_assert(sizeof(s_forge_palette_category) == 36, "Invalid s_forge_palette_category size");

#pragma pack(push, 4)
struct s_forge_palette_item
{
	tag_string name; // 0x0
	unsigned short type; // 0x20
	c_tag_block_index<s_forge_palette_category,short> category_index; // 0x22
	c_tag_block_index<s_forge_description_text_entry,short> description_index; // 0x24
	unsigned short max_allowed; // 0x26
	s_tag_reference object; // 0x28
	c_tag_block<s_forge_object_property_setter> setters; // 0x38
	s_forge_palette_item(s_forge_palette_item &); /* compiler_generated() */
	s_forge_palette_item(s_forge_palette_item const &); /* compiler_generated() */
	s_forge_palette_item(); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_forge_palette_item) == 68, "Invalid s_forge_palette_item size");

#pragma pack(push, 4)
struct s_forge_sky_definition
{
	tag_string name; // 0x0
	unsigned long flags; // 0x20
	real_point3d translation; // 0x24
	real_euler_angles3d orientation; // 0x30
	s_tag_reference object; // 0x3C
	s_tag_reference parameters; // 0x4C
	s_tag_reference wind; // 0x5C
	s_tag_reference camera_fx; // 0x6C
	s_tag_reference screen_fx; // 0x7C
	s_tag_reference global_lighting; // 0x8C
	s_tag_reference background_sound; // 0x9C
};
#pragma pack(pop)
static_assert(sizeof(s_forge_sky_definition) == 172, "Invalid s_forge_sky_definition size");

struct s_forge_weather_definition
{
	tag_string name; // 0x0
	s_tag_reference effect; // 0x20
};
static_assert(sizeof(s_forge_weather_definition) == 48, "Invalid s_forge_weather_definition size");

#pragma pack(push, 4)
struct s_forge_globals_definition
{
	__int32 version; // 0x0
	s_tag_reference default_boundary_method; // 0x4
	s_tag_reference invisible_render_method; // 0x14
	s_tag_reference default_render_method; // 0x24
	c_tag_block<s_forge_material> materials; // 0x34
	c_tag_block<s_forge_material_type> material_types; // 0x40
	c_tag_block<s_tag_reference> reforge_objects; // 0x4C
	s_tag_reference prematch_camera_object; // 0x58
	s_tag_reference podium_placement_object; // 0x68
	s_tag_reference map_modifier_object; // 0x78
	s_tag_reference kill_volume_object; // 0x88
	s_tag_reference garbage_volume_object; // 0x98
	c_tag_block<s_forge_description_text_entry> descriptions; // 0xA8
	c_tag_block<s_forge_palette_category> palette_categories; // 0xB4
	c_tag_block<s_forge_palette_item> palette; // 0xC0
	c_tag_block<s_forge_weather_definition> weather_effects; // 0xCC
	c_tag_block<s_forge_sky_definition> skies; // 0xD8
	s_tag_reference fx_object; // 0xE4
	s_tag_reference fx_light; // 0xF4
};
#pragma pack(pop)
static_assert(sizeof(s_forge_globals_definition) == 260, "Invalid s_forge_globals_definition size");

/* ---------- prototypes */

extern s_forge_globals_definition *forge_globals_get_definition();

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_FORGE_FORGE_GLOBALS_HPP__
