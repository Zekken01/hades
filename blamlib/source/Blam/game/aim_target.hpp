#ifndef __BLAM_GAME_AIM_TARGET_HPP__
#define __BLAM_GAME_AIM_TARGET_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"

/* ---------- forward declarations */

struct c_aim_target_object;
struct c_aim_target_predicted;
struct c_aim_target_simulation_entity;
struct real_vector3d;
struct s_aim_assist_targeting_result;

/* ---------- constants */

/* ---------- definitions */

struct c_aim_target_object
{
	unsigned char type; // 0x0
	long model_target_index; // 0x4
	long object_index; // 0x8
	static bool (*const setup)(c_aim_target_object *, c_aim_target_simulation_entity *);
	static bool (*const is_valid)(c_aim_target_object *);
};
static_assert(sizeof(c_aim_target_object) == 12, "Invalid c_aim_target_object size");
static_assert(offsetof(c_aim_target_object, model_target_index) == 0x4, "c_aim_target_object::model_target_index moved when its reconstructed padding was removed");

struct s_aim_assist_targeting_result
{
	c_aim_target_object target_object; // 0x0
	long player_index; // 0xC
	float primary_auto_aim_level; // 0x10
	float secondary_auto_aim_level; // 0x14
	real_vector3d lead_vector; // 0x18
	unsigned long flags; // 0x24
};
static_assert(sizeof(s_aim_assist_targeting_result) == 40, "Invalid s_aim_assist_targeting_result size");

#pragma pack(push, 4)
struct c_aim_target_predicted :
	public c_aim_target_object
{
	static void (*const reset)(c_aim_target_predicted *);
};
#pragma pack(pop)
static_assert(sizeof(c_aim_target_predicted) == 12, "Invalid c_aim_target_predicted size");

struct c_aim_target_simulation_entity
{
	char type; // 0x0
	long target_model_index; // 0x4
	unsigned char flags; // 0x8
	long entity_index; // 0xC
	long gamestate_index; // 0x10
	static bool (*const setup)(c_aim_target_simulation_entity *, c_aim_target_object *);
	static char (*const is_valid)(c_aim_target_simulation_entity *);
};
static_assert(sizeof(c_aim_target_simulation_entity) == 20, "Invalid c_aim_target_simulation_entity size");
static_assert(offsetof(c_aim_target_simulation_entity, target_model_index) == 0x4, "c_aim_target_simulation_entity::target_model_index moved when its reconstructed padding was removed");
static_assert(offsetof(c_aim_target_simulation_entity, entity_index) == 0xC, "c_aim_target_simulation_entity::entity_index moved when its reconstructed padding was removed");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_GAME_AIM_TARGET_HPP__
