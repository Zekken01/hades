#ifndef __BLAM_SHADERS_RENDER_METHOD_TEMPLATE_DEFINITIONS_HPP__
#define __BLAM_SHADERS_RENDER_METHOD_TEMPLATE_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class s_tag_block_index;
struct c_render_method_template;
struct s_render_method_template_constant_table;
struct s_render_method_template_pass;
struct s_render_method_template_routing_info;
struct s_tag_reference;

/* ---------- constants */

/* ---------- definitions */

struct s_render_method_template_pass
{
	s_tag_block_index bitmaps; // 0x0
	s_tag_block_index vertex_real_constants; // 0x2
	s_tag_block_index vertex_int_constants; // 0x4
	s_tag_block_index vertex_bool_constants; // 0x6
	s_tag_block_index pixel_real_constants; // 0x8
	s_tag_block_index pixel_int_constants; // 0xA
	s_tag_block_index pixel_bool_constants; // 0xC
	s_tag_block_index extern_bitmaps; // 0xE
	s_tag_block_index extern_vertex_real_constants; // 0x10
	s_tag_block_index extern_vertex_int_constants; // 0x12
	s_tag_block_index extern_pixel_real_constants; // 0x14
	s_tag_block_index extern_pixel_int_constants; // 0x16
	unsigned char __pad0[4]; // 0x18
};
static_assert(sizeof(s_render_method_template_pass) == 28, "Invalid s_render_method_template_pass size");

struct s_render_method_template_routing_info
{
	short destination_index; // 0x0
	unsigned char source_index; // 0x2
	unsigned char bitmap_flags; // 0x3
};
static_assert(sizeof(s_render_method_template_routing_info) == 4, "Invalid s_render_method_template_routing_info size");

struct s_render_method_template_constant_table
{
	unsigned long parameter_name; // 0x0
};
static_assert(sizeof(s_render_method_template_constant_table) == 4, "Invalid s_render_method_template_constant_table size");

#pragma pack(push, 4)
struct c_render_method_template
{
	s_tag_reference vertex_shader; // 0x0
	s_tag_reference pixel_shader; // 0x10
	c_flags<enum e_entry_point,long> available_entry_points; // 0x20
	c_tag_block<s_tag_block_index> entry_points; // 0x24
	c_tag_block<s_render_method_template_pass> passes; // 0x30
	c_tag_block<s_render_method_template_routing_info> routing_info; // 0x3C
	c_tag_block<s_render_method_template_constant_table> float_constants; // 0x48
	c_tag_block<s_render_method_template_constant_table> int_constants; // 0x54
	c_tag_block<s_render_method_template_constant_table> bool_constants; // 0x60
	c_tag_block<s_render_method_template_constant_table> textures; // 0x6C
	static _inline c_render_method_template *get(long index);
	c_render_method_template(c_render_method_template &); /* compiler_generated() */
	c_render_method_template(c_render_method_template const &); /* compiler_generated() */
	c_render_method_template(); /* compiler_generated() */
	c_render_method_template &operator=(c_render_method_template &); /* compiler_generated() */
	c_render_method_template &operator=(c_render_method_template const &); /* compiler_generated() */
	unsigned char __pad0[12]; // 0x78
};
#pragma pack(pop)
static_assert(sizeof(c_render_method_template) == 132, "Invalid c_render_method_template size");

/* ---------- prototypes */

extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x108EEF70

/* ---------- globals */

/* ---------- public code */

_inline c_render_method_template *c_render_method_template::get(long index) // 0x108EEF70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get@c_render_method_template@@SAPAU1@J@Z");

	return (c_render_method_template *)tag_get(0x726D7432, index);
}

/* ---------- private code */

#endif // __BLAM_SHADERS_RENDER_METHOD_TEMPLATE_DEFINITIONS_HPP__
