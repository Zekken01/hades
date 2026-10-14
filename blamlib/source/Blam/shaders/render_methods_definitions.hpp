#ifndef __BLAM_SHADERS_RENDER_METHODS_DEFINITIONS_HPP__
#define __BLAM_SHADERS_RENDER_METHODS_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeUndo.hpp"

/* ---------- forward declarations */

class s_tag_block_index;
struct real_vector4d;
struct s_render_method_animated_parameter;
struct s_render_method_import_data;
struct s_render_method_pass;
struct s_render_method_postprocess_definition;
struct s_render_method_routing_info;
struct s_render_method_texture_constant;
struct s_tag_block;
struct s_tag_data;
struct s_tag_reference;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_render_method_import_data
{
	unsigned long name; // 0x0
	long type; // 0x4
	s_tag_reference bitmap; // 0x8
	float default_real; // 0x18
	long default_int_bool; // 0x1C
	short sampler_flags; // 0x20
	short sampler_filter_mode; // 0x22
	short default_address_mode; // 0x24
	short address_u; // 0x26
	short address_v; // 0x28
	short field_1E; // 0x2A
	long field_20; // 0x2C
	s_tag_block animated_parameters; // 0x30
};
#pragma pack(pop)
static_assert(sizeof(s_render_method_import_data) == 60, "Invalid s_render_method_import_data size");

struct s_render_method_texture_constant
{
	s_tag_reference bitmap; // 0x0
	short bitmap_index; // 0x10
	unsigned char sampler_address_mode_u : 4; // 0x12
	unsigned char sampler_address_mode_v : 4; // 0x12
	c_enum<enum e_sampler_filter_mode,char> filter_mode; // 0x13
	c_enum<enum e_render_method_extern_mode,char> extern_mode; // 0x14
	char xform_argument_index; // 0x15
	s_tag_block_index animated_parameters; // 0x16
	s_render_method_texture_constant(s_render_method_texture_constant &); /* compiler_generated() */
	s_render_method_texture_constant(s_render_method_texture_constant const &); /* compiler_generated() */
	s_render_method_texture_constant(); /* compiler_generated() */
	s_render_method_texture_constant &operator=(s_render_method_texture_constant &); /* compiler_generated() */
	s_render_method_texture_constant &operator=(s_render_method_texture_constant const &); /* compiler_generated() */
};
// static_assert(sizeof(s_render_method_texture_constant) == 24, "Invalid s_render_method_texture_constant size");
// The layout above is the PDB's member list without its padding, so the
// size assertion is withheld: it would fail on alignment alone.

struct s_render_method_pass
{
	s_tag_block_index texture; // 0x0
	s_tag_block_index real_vertex; // 0x2
	s_tag_block_index real_pixel; // 0x4
};
static_assert(sizeof(s_render_method_pass) == 6, "Invalid s_render_method_pass size");

struct s_render_method_routing_info
{
	short destination_index; // 0x0
	char animated_parameter_index; // 0x2
	char source_index; // 0x3
};
static_assert(sizeof(s_render_method_routing_info) == 4, "Invalid s_render_method_routing_info size");

#pragma pack(push, 4)
struct s_render_method_animated_parameter
{
	c_enum<enum e_render_method_animated_parameter_type,long> type; // 0x0
	unsigned long input_name; // 0x4
	unsigned long range_name; // 0x8
	float time_period; // 0xC
	s_tag_data function; // 0x10
	s_render_method_animated_parameter(s_render_method_animated_parameter &); /* compiler_generated() */
	s_render_method_animated_parameter(s_render_method_animated_parameter const &); /* compiler_generated() */
	s_render_method_animated_parameter(); /* compiler_generated() */
	s_render_method_animated_parameter &operator=(s_render_method_animated_parameter &); /* compiler_generated() */
	s_render_method_animated_parameter &operator=(s_render_method_animated_parameter const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_render_method_animated_parameter) == 36, "Invalid s_render_method_animated_parameter size");

#pragma pack(push, 4)
struct s_render_method_postprocess_definition
{
	s_tag_reference render_method_template; // 0x0
	c_tag_block<s_render_method_texture_constant> texture_constants; // 0x10
	c_tag_block<real_vector4d> real_constants; // 0x1C
	c_tag_block<long> integer_constants; // 0x28
	unsigned long boolean_constants; // 0x34
	c_tag_block<s_tag_block_index> entry_points; // 0x38
	c_tag_block<s_render_method_pass> routing_table; // 0x44
	c_tag_block<s_render_method_routing_info> routings; // 0x50
	c_tag_block<s_render_method_animated_parameter> animated_parameters; // 0x5C
	c_enum<enum e_alpha_blend_mode,int> alpha_blend_mode; // 0x68
	c_flags<enum e_render_method_postprocess_flags,long> flags; // 0x6C
	__int32 unknown70; // 0x70
	short queryable_properties[8]; // 0x74
	s_render_method_postprocess_definition(s_render_method_postprocess_definition &); /* compiler_generated() */
	s_render_method_postprocess_definition(s_render_method_postprocess_definition const &); /* compiler_generated() */
	s_render_method_postprocess_definition(); /* compiler_generated() */
	s_render_method_postprocess_definition &operator=(s_render_method_postprocess_definition &); /* compiler_generated() */
	s_render_method_postprocess_definition &operator=(s_render_method_postprocess_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_render_method_postprocess_definition) == 132, "Invalid s_render_method_postprocess_definition size");

// c_render_method is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

unsigned long tag_get_group_tag(long index);  // hades: added for 0X108EFD00

extern void *(__cdecl *const tag_get)(unsigned long, long);  // hades: added for 0X108DED70

/* ---------- globals */

/* ---------- public code */

_inline c_render_method *c_render_method::get(long index) // 0x108DED70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get@c_render_method@@SAPAV1@J@Z");
	// long index;
	// function call : void *(*const)(unsigned long, long)

	return (c_render_method *)tag_get(0x726D2020, index);
}

_inline bool c_render_method::get_is_transparent(long index) // 0x108EFD80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_is_transparent@c_render_method@@SA_NJ@Z");
	// long index;

	return index != -1 && (*reinterpret_cast<c_tag_block<s_render_method_postprocess_definition> *>(get(index)->postprocess))->alpha_blend_mode != static_cast<e_alpha_blend_mode>(0);
}

_inline bool c_render_method::get_is_decal(long index) // 0x108EFD00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_is_decal@c_render_method@@SA_NJ@Z");
	// long index;

	return index != -1 && tag_get_group_tag(index) == 0x726D6420;
}

/* ---------- private code */

#endif // __BLAM_SHADERS_RENDER_METHODS_DEFINITIONS_HPP__
