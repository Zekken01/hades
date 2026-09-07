#ifndef __BLAM_INTERFACE_FIRST_PERSON_WEAPONS_HPP__
#define __BLAM_INTERFACE_FIRST_PERSON_WEAPONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/animations/animation_manager.hpp"
#include "Blam/animations/mixing_board/channels/animation_channel.hpp"
#include "Blam/math/real_math_definitions.hpp"

/* ---------- forward declarations */

class c_animation_id;
struct c_animation_manager;
struct c_animation_channel;
struct real_matrix4x3;
struct s_first_person_weapon;
struct s_first_person_weapon_attachment;
struct s_first_person_weapon_data;

/* ---------- constants */

/* ---------- definitions */

struct s_first_person_weapon_attachment
{
	long unit_index; // 0x0
	long player_representation_index; // 0x4
	long weapon_index; // 0x8
	unsigned long weapon_class; // 0xC
	long first_person_render_model_index; // 0x10
	long first_person_model_animation_graph_index; // 0x14
	long first_person_hands_definition_index; // 0x18
	long arms_render_model_definition_index; // 0x1C
	long first_person_body_definition_index; // 0x20
	long legs_render_model_definition_index; // 0x24
	long fp_weapon_render_model_node_count; // 0x28
	long hands_node_count; // 0x2C
};
static_assert(sizeof(s_first_person_weapon_attachment) == 48, "Invalid s_first_person_weapon_attachment size");

struct s_first_person_weapon_data
{
	unsigned long flags; // 0x0
	s_first_person_weapon_attachment attachment; // 0x4
	c_animation_manager animation_manager; // 0x34
	char unknown[116]; // 0xF4
	c_animation_channel field_168; // 0x168
	unsigned char __pad0[4]; // 0x1A4
	c_animation_id animation_id; // 0x1A8
	c_animation_id animation_id2; // 0x1AC
	c_animation_id animation_id3; // 0x1B0
	unsigned char __pad1[16]; // 0x1B4
	long weapon_node_remapping_table_count; // 0x1C4
	long hands_node_remapping_table_count; // 0x1C8
	long weapon_node_remapping_table[150]; // 0x1CC
	long hands_node_remapping_table[150]; // 0x424
	long node_indices[150]; // 0x67C
	unsigned char __pad2[4]; // 0x8D4
	long node_orientations_count; // 0x8D8
	long node_matrices_count; // 0x8DC
	real_matrix4x3 node_matrices[150]; // 0x8E0
	unsigned char __pad3[4]; // 0x2758
	real_matrix4x3 unknown_matrix; // 0x275C
	unsigned char __pad4[4]; // 0x2790
	unsigned long animation_name_string_id; // 0x2794
	s_first_person_weapon_data(); /* compiler_generated() */
	~s_first_person_weapon_data(); /* compiler_generated() */
	unsigned char __pad5[8]; // 0x2798
};
static_assert(sizeof(s_first_person_weapon_data) == 10144, "Invalid s_first_person_weapon_data size");

struct s_first_person_weapon
{
	unsigned long flags; // 0x0
	long unit_index; // 0x4
	s_first_person_weapon_attachment attachment; // 0x8
	s_first_person_weapon_data weapon_slots[2]; // 0x38
	unsigned char __pad0[72]; // 0x4F78
	real_matrix4x3 root_transform; // 0x4FC0
	long unknown_animation_graph_index; // 0x4FF4
	s_first_person_weapon(); /* compiler_generated() */
	~s_first_person_weapon(); /* compiler_generated() */
	unsigned char __pad1[8]; // 0x4FF8
};
static_assert(sizeof(s_first_person_weapon) == 20480, "Invalid s_first_person_weapon size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_INTERFACE_FIRST_PERSON_WEAPONS_HPP__
