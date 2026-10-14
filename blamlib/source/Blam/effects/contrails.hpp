#ifndef __BLAM_EFFECTS_CONTRAILS_HPP__
#define __BLAM_EFFECTS_CONTRAILS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/shaders/render_methods_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

class c_render_method;
class s_contrail_function_definition;
struct s_contrail_gpu_datum;
struct s_contrail_gpu_row;
struct s_contrail_instance;
struct s_contrail_location;
struct s_contrail_profile;
struct s_contrail_states;
struct s_contrail_system;
struct s_contrail_system_definition;
struct s_datum;
struct s_tag_block;
struct s_tag_data;

/* ---------- constants */

/* ---------- definitions */

class s_contrail_function_definition
{
public:
	c_enum<enum e_control_function_variable_type,char> input_variable; // 0x0
	c_enum<enum e_control_function_variable_type,char> range_variable; // 0x1
	c_enum<enum e_control_function_output_modifier,char> output_modifier; // 0x2
	c_enum<enum e_control_function_variable_type,char> output_modifier_input; // 0x3
	s_tag_data data; // 0x4
	float runtime_m_constant_value; // 0x18
	c_flags<enum e_control_function_runtime_m_flags,unsigned char> runtime_m_flags; // 0x1C
	s_contrail_function_definition(s_contrail_function_definition &); /* compiler_generated() */
	s_contrail_function_definition(s_contrail_function_definition const &); /* compiler_generated() */
	s_contrail_function_definition(); /* compiler_generated() */
	s_contrail_function_definition &operator=(s_contrail_function_definition &); /* compiler_generated() */
	s_contrail_function_definition &operator=(s_contrail_function_definition const &); /* compiler_generated() */
};
static_assert(sizeof(s_contrail_function_definition) == 32, "Invalid s_contrail_function_definition size");

#pragma pack(push, 4)
struct s_contrail_system_definition
{
	unsigned long name; // 0x0
	float origin_fade_range; // 0x4
	float origin_fade_cutoff; // 0x8
	float edge_fade_range; // 0xC
	float edge_fade_cutoff; // 0x10
	unsigned char __pad0[16]; // 0x14
	s_contrail_function_definition function1; // 0x24
	s_contrail_function_definition function2; // 0x44
	s_contrail_function_definition function3; // 0x64
	s_contrail_function_definition function4; // 0x84
	unsigned char __pad1[24]; // 0xA4
	s_contrail_function_definition function5; // 0xBC
	s_contrail_function_definition function6; // 0xDC
	unsigned char __pad2[16]; // 0xFC
	s_contrail_function_definition function7; // 0x10C
	unsigned char render_flags; // 0x12C
	unsigned char field_12D; // 0x12D
	unsigned char field_12E; // 0x12E
	unsigned char field_12F; // 0x12F
	c_render_method render_method; // 0x130
	float tile_y; // 0x170
	float tIle_x; // 0x174
	float scroll_speed_x; // 0x178
	float scroll_speed_y; // 0x17C
	s_contrail_function_definition function8; // 0x180
	s_contrail_function_definition function9; // 0x1A0
	s_contrail_function_definition function10; // 0x1C0
	s_contrail_function_definition function11; // 0x1E0
	s_contrail_function_definition function12; // 0x200
	unsigned char __pad3[40]; // 0x220
	s_tag_block field_248; // 0x248
	s_tag_block shader_constants; // 0x254
	s_tag_block compiled_color_functions; // 0x260
	s_contrail_system_definition(s_contrail_system_definition &); /* compiler_generated() */
	s_contrail_system_definition(s_contrail_system_definition const &); /* compiler_generated() */
	s_contrail_system_definition(); /* compiler_generated() */
	s_contrail_system_definition &operator=(s_contrail_system_definition &); /* compiler_generated() */
	s_contrail_system_definition &operator=(s_contrail_system_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_contrail_system_definition) == 620, "Invalid s_contrail_system_definition size");

#pragma pack(push, 4)
struct s_contrail_instance :
	public s_datum
{
	long next_instance_datum_index; // 0x4
	long contrail_gpu_datum_index; // 0x8
	long first_profile_datum_index; // 0xC
	long system_absolute_index; // 0x10
	long location_datum_index; // 0x14
	unsigned long unknown_flags; // 0x18
	long random_seed; // 0x1C
	float random_uv_offset_x; // 0x20
	float random_uv_offset_y; // 0x24
	unsigned char __pad1[4]; // 0x28
	real_point3d position; // 0x2C
	float field_38; // 0x38
	float shader_function1_result; // 0x3C
	unsigned char __pad2[4]; // 0x40
	float uv_offset_x; // 0x44
	float uv_offset_y; // 0x48
};
#pragma pack(pop)
static_assert(sizeof(s_contrail_instance) == 76, "Invalid s_contrail_instance size");

struct s_contrail_system :
	public s_datum
{
	unsigned char __pad0[2]; // 0x2
	long effect_index; // 0x4
	char event_index; // 0x8
	char event_absolute_index; // 0x9
	unsigned char __pad1[2]; // 0xA
	long part_absolute_index; // 0xC
	long definition_index; // 0x10
	unsigned char __pad2[4]; // 0x14
	long first_location_index; // 0x18
	unsigned short unknown_flags; // 0x1C
	unsigned char camera_mode; // 0x1E
	unsigned char output_user_mask; // 0x1F
	float age; // 0x20
	float effect_scale_A; // 0x24
	float effect_scale_B; // 0x28
	float lod; // 0x2C
};
static_assert(sizeof(s_contrail_system) == 48, "Invalid s_contrail_system size");

struct s_contrail_states
{
	s_contrail_system *system; // 0x0
	s_contrail_location *location; // 0x4
	s_contrail_instance *contrail; // 0x8
	s_contrail_profile *profile; // 0xC
	float unknown_values[6]; // 0x10
	float game_tick_offset_seconds; // 0x28
	float system_age; // 0x2C
	unsigned char __pad0[4]; // 0x30
	long random_seed; // 0x34
	float length; // 0x38
	float speed; // 0x3C
	float system_lod; // 0x40
	long effect_scale_A; // 0x44
	long effect_scale_B; // 0x48
	long field_4C; // 0x4C
	unsigned long used_states; // 0x50
	unsigned long unknown_states; // 0x54
};
static_assert(sizeof(s_contrail_states) == 88, "Invalid s_contrail_states size");

struct s_contrail_gpu_row :
	public s_datum
{
	long previous_row_datum_index; // 0x4
	long next_row_datum_index; // 0x8
	short index; // 0xC
	float time; // 0x10
};
static_assert(sizeof(s_contrail_gpu_row) == 20, "Invalid s_contrail_gpu_row size");
static_assert(offsetof(s_contrail_gpu_row, previous_row_datum_index) == 0x4, "s_contrail_gpu_row::previous_row_datum_index moved when its reconstructed padding was removed");
static_assert(offsetof(s_contrail_gpu_row, time) == 0x10, "s_contrail_gpu_row::time moved when its reconstructed padding was removed");

struct s_contrail_gpu_datum :
	public s_datum
{
	long parent_contrail_index; // 0x4
	long gpu_row_datum_index; // 0x8
	short field_C; // 0xC
	unsigned short flags; // 0xE
};
static_assert(sizeof(s_contrail_gpu_datum) == 16, "Invalid s_contrail_gpu_datum size");
static_assert(offsetof(s_contrail_gpu_datum, parent_contrail_index) == 0x4, "s_contrail_gpu_datum::parent_contrail_index moved when its reconstructed padding was removed");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_EFFECTS_CONTRAILS_HPP__
