#ifndef __BLAM_MOTOR_MOTOR_SYSTEM_HPP__
#define __BLAM_MOTOR_MOTOR_SYSTEM_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

class c_motor_task;
struct c_motor_request;

/* ---------- constants */

enum e_motor_task
{
	_motor_task_none = 0,
	_motor_task_default,
	_motor_task_jump,
	_motor_task_accelerate,
	_motor_task_throw_object,
	_motor_task_notify_physics_built,
	_motor_task_handle_simulation_warp,
	_motor_task_force_airborne,
	_motor_task_force_relaxation_state,
	_motor_task_force_heavy,
	_motor_task_board,
	_motor_task_ejection,
	_motor_task_takeoff,
	_motor_task_perch,
	_motor_task_land,
	_motor_task_attach,
	_motor_task_detach,
	_motor_task_bunker_open,
	_motor_task_bunker_close,
	_motor_task_melee,
	_motor_task_resurrect,
	_motor_task_get_infected,
	_motor_task_infect,
	_motor_task_open,
	_motor_task_close,
	_motor_task_flip,
	_motor_task_unit_enter,
	_motor_task_weapon_animation,
	_motor_task_weapon_stow,
	_motor_task_weapon_draw,
	_motor_task_grenade,
	_motor_task_equipment,
	_motor_task_exit,
	_motor_task_ping,
	_motor_task_die,
	_motor_task_animation,
	_motor_task_posture,
	_motor_task_transient_posture,
	_motor_task_hoist,
};

enum e_motor_program
{
	_motor_program_biped_ground = 0,
	_motor_program_biped_airborne,
	_motor_program_biped_dead,
	_motor_program_biped_vehicle,
	_motor_program_biped_flying,
	_motor_program_biped_perch,
	_motor_program_biped_bunker,
	_motor_program_biped_climb,
	_motor_program_biped_posture,
	_motor_program_vehicle,
	_motor_program_unit_custom_animation,
	_motor_program_unit_phase,
	_motor_program_creature_ground,
	_motor_program_creature_flying,
	_motor_program_giant_scarab,
};

/* ---------- definitions */

struct c_motor_request
{
	short unknown0; // 0x0
	__int32 task_id; // 0x4
	__int32 action_type; // 0x8
	unsigned long animation_name1; // 0xC
	unsigned long animation_name2; // 0x10
	float interpolation_time; // 0x14
	short unknown18; // 0x18
};
static_assert(sizeof(c_motor_request) == 28, "Invalid c_motor_request size");
static_assert(offsetof(c_motor_request, task_id) == 0x4, "c_motor_request::task_id moved when its reconstructed padding was removed");

#pragma pack(push, 4)
class c_motor_task
{
public:
	long type; // 0x0
	long action_type; // 0x4
	long program_type; // 0x8
	unsigned char __pad0[4]; // 0xC
	long motor_index; // 0x10
	bool valid() const;
	bool program_default() const;
unsigned char __pad1[8]; // 0x14
};
#pragma pack(pop)
static_assert(sizeof(c_motor_task) == 28, "Invalid c_motor_task size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_MOTOR_MOTOR_SYSTEM_HPP__
