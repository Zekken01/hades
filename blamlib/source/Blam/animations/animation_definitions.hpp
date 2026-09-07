#ifndef __BLAM_ANIMATIONS_ANIMATION_DEFINITIONS_HPP__
#define __BLAM_ANIMATIONS_ANIMATION_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct real_vector3d;
struct s_animation_sync_action;
struct s_animation_sync_action_participant;
struct s_tag_block;

/* ---------- constants */

enum e_animation_frame_event_types
{
	_animation_frame_event_primary_key = 0,
	_animation_frame_event_secondary_key,
	_animation_frame_event_tertiary_key,
	_animation_frame_event_left_foot,
	_animation_frame_event_right_foot,
	_animation_frame_event_allow_interruption,
	_animation_frame_event_transition_a,
	_animation_frame_event_transition_b,
	_animation_frame_event_transition_c,
	_animation_frame_event_transition_d,
	_animation_frame_event_both_feet_shuffle,
	_animation_frame_event_body_impact,
	_animation_frame_event_left_back_foot,
	_animation_frame_event_right_back_foot,
	_animation_frame_event_ragdoll_key,
	_animation_frame_event_drop_weapon_key,
	_animation_frame_event_assassination_a,
	_animation_frame_event_assassination_b,
	k_total_animation_frame_event_types,
};

/* ---------- definitions */

struct s_animation_sync_action_participant
{
	unsigned long flags; // 0x0
	short graph_index; // 0x4
	short animation_index; // 0x6
	real_point3d start_offset; // 0x8
	real_vector3d start_facing; // 0x14
	real_vector3d end_offset; // 0x20
	float time_unit_hurt; // 0x2C
};
static_assert(sizeof(s_animation_sync_action_participant) == 48, "Invalid s_animation_sync_action_participant size");

#pragma pack(push, 4)
struct s_animation_sync_action
{
	unsigned long name; // 0x0
	c_tag_block<s_animation_sync_action_participant> same_type_participants; // 0x4
	s_tag_block other_participants; // 0x10
};
#pragma pack(pop)
static_assert(sizeof(s_animation_sync_action) == 28, "Invalid s_animation_sync_action size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_ANIMATIONS_ANIMATION_DEFINITIONS_HPP__
