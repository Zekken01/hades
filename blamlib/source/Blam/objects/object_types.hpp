#ifndef __BLAM_OBJECTS_OBJECT_TYPES_HPP__
#define __BLAM_OBJECTS_OBJECT_TYPES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/scenario/scenario_definitions.hpp"

/* ---------- forward declarations */

struct c_mover_definition_data;
struct real_matrix4x3;
struct real_vector3d;
struct s_object_placement_data;
struct s_object_type_definition;
struct s_scenario_object;

/* ---------- constants */

// e_object_type is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

enum
{
	_object_mask_biped = 1, // 0x0001
	_object_mask_vehicle = 2, // 0x0002
	_object_mask_weapon = 4, // 0x0004
	_object_mask_equipment = 8, // 0x0008
	_object_mask_arg_device = 16, // 0x0010
	_object_mask_terminal = 32, // 0x0020 ' '
	_object_mask_projectile = 64, // 0x0040 '@'
	_object_mask_scenery = 128, // 0x0080
	_object_mask_machine = 256, // 0x0100
	_object_mask_control = 512, // 0x0200
	_object_mask_sound_scenery = 1024, // 0x0400
	_object_mask_crate = 2048, // 0x0800
	_object_mask_creature = 4096, // 0x1000
	_object_mask_giant = 8192, // 0x2000
	_object_mask_effect_scenery = 16384, // 0x4000
	_object_mask_unit = 8195, // 0x2003
	_object_mask_device = 784, // 0x0310
	_object_mask_item = 12, // 0x000C
};

/* ---------- definitions */

#pragma pack(push, 4)
struct s_object_type_definition
{
	char const *name; // 0x0
	unsigned long group_tag; // 0x4
	short datum_size; // 0x8
	short placement_tag_block_offset; // 0xA
	short palette_tag_block_offset; // 0xC
	short placement_tag_block_element_size; // 0xE
	long maximum_placement_count; // 0x10
	long mixing_board_index; // 0x14
	c_mover_definition_data *mover_definition; // 0x18
	void (*initialize)(s_object_type_definition *, long); // 0x1C
	void (*dispose)(); // 0x20
	void (*initialize_for_new_map)(); // 0x24
	void (*dispose_from_old_map)(); // 0x28
	void (*initialize_for_new_structure_bsp)(long); // 0x2C
	void (*disconnect_from_structure_bsp)(long); // 0x30
	void (*adjust_placement)(s_object_placement_data *); // 0x34
	bool (*new_)(long, s_object_placement_data *, bool *); // 0x38
	void (*place)(long, s_scenario_object *); // 0x3C
	void (*unplace)(long); // 0x40
	void (*create_children)(long); // 0x44
	void (*delete_)(long); // 0x48
	long (*export_function_values_A)(long); // 0x4C
	long (*export_function_values_B)(long); // 0x50
	void (*move)(long); // 0x54
	bool (*compute_activation)(long, long, long); // 0x58
	bool (*compute_function_value)(long, unsigned long, long, float *, bool *, long); // 0x5C
	void (*attach_simulation_object_glue)(long); // 0x60
	void (*detach_simulation_object_glue)(long); // 0x64
	void (*attach_to_marker)(long, long, long); // 0x68
	void (*attach_to_node)(long, long, long); // 0x6C
	void (*detach_from_parent)(long); // 0x70
	void (*handle_deleted_object)(long, long); // 0x74
	unsigned long handle_deleted_object_flags; // 0x78
	void (*handle_deleted_player)(long, long); // 0x7C
	void (*unused)(long, long, long); // 0x80
	bool (*handle_parent_destroyed)(long); // 0x84
	void (*fix_transform)(long, real_vector3d *, real_vector3d *, real_vector3d *); // 0x88
	void (*fix_transform_to_physics)(long, real_matrix4x3 *); // 0x8C
	void (*fix_transform_from_physics)(long, real_matrix4x3 *); // 0x90
	void (*preprocess_node_orientations)(long, long, long, long); // 0x94
	void (*preprocess_root_node_matrix)(long, real_matrix4x3 *); // 0x98
	void (*postprocess_node_matrices)(long, long, real_matrix4x3 *); // 0x9C
	void (*reset)(long); // 0xA0
	void (*notify_impulse_sound)(long, long, long); // 0xA4
	void (*render_debug)(long); // 0xA8
	s_object_type_definition *child_types[16]; // 0xAC
	s_object_type_definition *next_type; // 0xEC
	unsigned long deleted_object_handler_mask; // 0xF0
};
#pragma pack(pop)
static_assert(sizeof(s_object_type_definition) == 244, "Invalid s_object_type_definition size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_OBJECTS_OBJECT_TYPES_HPP__
