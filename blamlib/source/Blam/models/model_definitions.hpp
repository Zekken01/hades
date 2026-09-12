#ifndef __BLAM_MODELS_MODEL_DEFINITIONS_HPP__
#define __BLAM_MODELS_MODEL_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct s_model_definition;
struct s_model_instance_group;
struct s_model_instance_member;
struct s_model_material;
struct s_model_object_data;
struct s_model_permutation;
struct s_model_permutation_possibility;
struct s_model_permutation_state;
struct s_model_region;
struct s_model_target;
struct s_model_unknown_block;
struct s_model_variant;
struct s_model_variant_object;
struct s_model_variant_permutation;
struct s_model_variant_region;
struct s_tag_block;
struct s_tag_reference;

/* ---------- constants */

enum
{
	k_model_group_tag = 'hlmt', // 0x686C6D74
	k_maximum_number_of_model_regions = 16, // 0x0010
	k_maximum_number_of_model_region_permutations = 12, // 0x000C
};

enum e_model_lod
{
	_model_lod_super_low = 0,
	_model_lod_low,
	_model_lod_medium,
	_model_lod_high,
	_model_lod_super_high,
	k_number_of_model_lods,
};

/* ---------- definitions */

struct s_model_permutation_state
{
	unsigned long name; // 0x0
	char model_permutation; // 0x4
	c_flags<enum e_model_permutation_state_flags,unsigned char> flags; // 0x5
	c_enum<enum e_model_damage_state,short> state; // 0x6
	s_tag_reference looping_effect; // 0x8
	unsigned long looping_effect_marker_name; // 0x18
	float initial_probability; // 0x1C
	s_model_permutation_state(s_model_permutation_state &); /* compiler_generated() */
	s_model_permutation_state(s_model_permutation_state const &); /* compiler_generated() */
	s_model_permutation_state(); /* compiler_generated() */
	s_model_permutation_state &operator=(s_model_permutation_state &); /* compiler_generated() */
	s_model_permutation_state &operator=(s_model_permutation_state const &); /* compiler_generated() */
};
static_assert(sizeof(s_model_permutation_state) == 32, "Invalid s_model_permutation_state size");

#pragma pack(push, 4)
struct s_model_variant_permutation
{
	unsigned long name; // 0x0
	char render_model_permutation; // 0x4
	c_flags<enum e_model_permutation_flags,unsigned char> flags; // 0x5
	unsigned char __pad0[2]; // 0x6
	float probability; // 0x8
	c_tag_block<s_model_permutation_state> states; // 0xC
	char runtime_state_permutation_indices[12]; // 0x18
	s_model_variant_permutation(s_model_variant_permutation &); /* compiler_generated() */
	s_model_variant_permutation(s_model_variant_permutation const &); /* compiler_generated() */
	s_model_variant_permutation(); /* compiler_generated() */
	s_model_variant_permutation &operator=(s_model_variant_permutation &); /* compiler_generated() */
	s_model_variant_permutation &operator=(s_model_variant_permutation const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_model_variant_permutation) == 36, "Invalid s_model_variant_permutation size");

struct s_model_variant_region
{
	unsigned long name; // 0x0
	char render_model_region; // 0x4
	short parent_variant; // 0x6
	c_tag_block<s_model_variant_permutation> permutations; // 0x8
	c_enum<enum e_model_region_sort_order,long> sort_order; // 0x14
	s_model_variant_region(s_model_variant_region &); /* compiler_generated() */
	s_model_variant_region(s_model_variant_region const &); /* compiler_generated() */
	s_model_variant_region(); /* compiler_generated() */
	s_model_variant_region &operator=(s_model_variant_region &); /* compiler_generated() */
	s_model_variant_region &operator=(s_model_variant_region const &); /* compiler_generated() */
};
static_assert(sizeof(s_model_variant_region) == 24, "Invalid s_model_variant_region size");
static_assert(offsetof(s_model_variant_region, parent_variant) == 0x6, "s_model_variant_region::parent_variant moved when its reconstructed padding was removed");

#pragma pack(push, 4)
struct s_model_variant_object
{
	unsigned long parent_marker; // 0x0
	unsigned long child_marker; // 0x4
	unsigned long child_variant; // 0x8
	s_tag_reference child_object; // 0xC
};
#pragma pack(pop)
static_assert(sizeof(s_model_variant_object) == 28, "Invalid s_model_variant_object size");

struct s_model_variant
{
	unsigned long name; // 0x0
	s_tag_reference variant_dialogue; // 0x4
	unsigned long default_dialog_effect; // 0x14
	unsigned char __pad0[4]; // 0x18
	char region_indices[16]; // 0x1C
	c_tag_block<s_model_variant_region> regions; // 0x2C
	c_tag_block<s_model_variant_object> objects; // 0x38
	long instance_group_index; // 0x44
	unsigned char __pad1[8]; // 0x48
};
static_assert(sizeof(s_model_variant) == 80, "Invalid s_model_variant size");

#pragma pack(push, 4)
struct s_model_instance_member
{
	long subgroup_index; // 0x0
	unsigned long instance_name; // 0x4
	float probability; // 0x8
	unsigned char __pad0[16]; // 0xC
};
#pragma pack(pop)
static_assert(sizeof(s_model_instance_member) == 28, "Invalid s_model_instance_member size");

struct s_model_instance_group
{
	unsigned long name; // 0x0
	c_enum<enum e_model_instance_group_choice,long> choice; // 0x4
	c_tag_block<s_model_instance_member> instance_members; // 0x8
	float probability; // 0x14
	s_model_instance_group(s_model_instance_group &); /* compiler_generated() */
	s_model_instance_group(s_model_instance_group const &); /* compiler_generated() */
	s_model_instance_group(); /* compiler_generated() */
	s_model_instance_group &operator=(s_model_instance_group &); /* compiler_generated() */
	s_model_instance_group &operator=(s_model_instance_group const &); /* compiler_generated() */
};
static_assert(sizeof(s_model_instance_group) == 24, "Invalid s_model_instance_group size");

struct s_model_material
{
	unsigned long name; // 0x0
	c_enum<enum e_model_material_type,short> material_type; // 0x4
	short damage_section; // 0x6
	short runtime_collision_material; // 0x8
	short runtime_damager_material; // 0xA
	unsigned long material_name; // 0xC
	short global_material; // 0x10
	s_model_material(s_model_material &); /* compiler_generated() */
	s_model_material(s_model_material const &); /* compiler_generated() */
	s_model_material(); /* compiler_generated() */
	s_model_material &operator=(s_model_material &); /* compiler_generated() */
	s_model_material &operator=(s_model_material const &); /* compiler_generated() */
};
static_assert(sizeof(s_model_material) == 20, "Invalid s_model_material size");

struct s_model_target
{
	public:
	enum e_model_target_flags
	{
		_model_target_aoe_top_level = 0,
		_model_target_aoe_test_obstruction,
		_model_target_shows_tracking_reticle,
	};
	struct s_model_lockon_data
	{
		public:
		enum e_model_lockon_flags
		{
			_model_lockon_headshot = 0,
			_model_lockon_vulnerable,
			_model_lockon_ignored_on_local_physics,
			_model_lockon_use_for_network_lead_vector_only,
		};
		public:
		c_flags<enum e_model_lockon_flags,long> flags; // 0x0
		float lockon_distance; // 0x4
		unsigned long tracking_type; // 0x8
		s_model_lockon_data(s_model_lockon_data &); /* compiler_generated() */
		s_model_lockon_data(s_model_lockon_data const &); /* compiler_generated() */
		s_model_lockon_data(); /* compiler_generated() */
		s_model_lockon_data &operator=(s_model_lockon_data &); /* compiler_generated() */
		s_model_lockon_data &operator=(s_model_lockon_data const &); /* compiler_generated() */
	};
	static_assert(sizeof(s_model_lockon_data) == 12, "Invalid s_model_lockon_data size");
	public:
	c_flags<enum e_model_target_flags,long> flags; // 0x0
	unsigned long marker_name; // 0x4
	float size; // 0x8
	float cone_angle; // 0xC
	short damage_section_index; // 0x10
	short variant_index; // 0x12
	float targeting_relevance; // 0x14
	float aoe_exclusion_radius; // 0x18
	s_model_lockon_data lockon_data; // 0x1C
	s_model_target(s_model_target &); /* compiler_generated() */
	s_model_target(s_model_target const &); /* compiler_generated() */
	s_model_target(); /* compiler_generated() */
	s_model_target &operator=(s_model_target &); /* compiler_generated() */
	s_model_target &operator=(s_model_target const &); /* compiler_generated() */
};
static_assert(sizeof(s_model_target) == 40, "Invalid s_model_target size");

struct s_model_permutation
{
	unsigned long name; // 0x0
	unsigned char flags; // 0x4
	char collision_permutation_index; // 0x5
	char physics_permutation_index; // 0x6
};
static_assert(sizeof(s_model_permutation) == 8, "Invalid s_model_permutation size");

#pragma pack(push, 4)
struct s_model_region
{
	unsigned long name; // 0x0
	char collision_region_index; // 0x4
	char physics_region_index; // 0x5
	unsigned char __pad0[2]; // 0x6
	c_tag_block<s_model_permutation> permutations; // 0x8
};
#pragma pack(pop)
static_assert(sizeof(s_model_region) == 20, "Invalid s_model_region size");

#pragma pack(push, 4)
struct s_model_object_data
{
	public:
	enum e_bounding_sphere_type
	{
		_bounding_sphere_type_not_set = 0,
		_bounding_sphere_type_user_defined,
		_bounding_sphere_type_auto_generated,
	};
	public:
	c_enum<enum e_bounding_sphere_type,short> type; // 0x0
	unsigned char __pad0[2]; // 0x2
	real_point3d offset; // 0x4
	float Radius; // 0x10
	s_model_object_data(s_model_object_data &); /* compiler_generated() */
	s_model_object_data(s_model_object_data const &); /* compiler_generated() */
	s_model_object_data(); /* compiler_generated() */
	s_model_object_data &operator=(s_model_object_data &); /* compiler_generated() */
	s_model_object_data &operator=(s_model_object_data const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_model_object_data) == 20, "Invalid s_model_object_data size");

#pragma pack(push, 4)
struct s_model_definition
{
	s_tag_reference render_model; // 0x0
	s_tag_reference collision_model; // 0x10
	s_tag_reference animation; // 0x20
	s_tag_reference physics_model; // 0x30
	float reduce_to_lod_distances[5]; // 0x40
	s_tag_reference lod_model; // 0x54
	c_tag_block<s_model_variant> variants; // 0x64
	c_tag_block<s_model_unknown_block> unknown; // 0x70
	c_tag_block<s_model_instance_group> instance_groups; // 0x7C
	c_tag_block<s_model_material> materials; // 0x88
	s_tag_block damage_info; // 0x94
	c_tag_block<s_model_target> targets; // 0xA0
	c_tag_block<s_model_region> runtime_regions; // 0xAC
	s_tag_block runtime_nodes; // 0xB8
	unsigned long runtime_nodes_checksum; // 0xC4
	c_tag_block<s_model_object_data> model_object_data; // 0xC8
	s_tag_reference primary_dialog; // 0xD4
	s_tag_reference secondary_dialog; // 0xE4
	unsigned long flags; // 0xF4
	unsigned long default_dialog_effect; // 0xF8
	unsigned long render_only_node_flags[8]; // 0xFC
	unsigned long render_section_flags[8]; // 0x11C
	unsigned long runtime_flags; // 0x13C
	s_tag_block scenario_load_parameters; // 0x140
	char shadow_detail; // 0x14C
	char shadow_bounces; // 0x14D
	unsigned char __pad0[2]; // 0x14E
	s_tag_block shadow_cast_overrides; // 0x150
	s_tag_block shadow_receive_overrides; // 0x15C
	s_tag_block occlusion_spheres; // 0x168
	s_tag_reference override_3p_shield_impact; // 0x174
	s_tag_reference override_fp_shield_impact; // 0x184
	s_tag_reference overshield_3p_shield_impact; // 0x194
	s_tag_reference overshield_fp_shield_impact; // 0x1A4
};
#pragma pack(pop)
static_assert(sizeof(s_model_definition) == 436, "Invalid s_model_definition size");

struct s_model_permutation_possibility
{
	long runtime_permutation_index; // 0x0
	long variant_permutation_index; // 0x4
	char state; // 0x8
	long property_flags; // 0xC
	long looping_effect_index; // 0x10
	unsigned long looping_effect_marker; // 0x14
	float probability; // 0x18
};
static_assert(sizeof(s_model_permutation_possibility) == 28, "Invalid s_model_permutation_possibility size");
static_assert(offsetof(s_model_permutation_possibility, property_flags) == 0xC, "s_model_permutation_possibility::property_flags moved when its reconstructed padding was removed");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_MODELS_MODEL_DEFINITIONS_HPP__
