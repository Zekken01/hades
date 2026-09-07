#ifndef __BLAM_UNITS_VEHICLES_HPP__
#define __BLAM_UNITS_VEHICLES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"

/* ---------- forward declarations */

struct c_vehicle_auto_turret;
struct c_vehicle_type_component;
struct c_vehicle_type_guardian;
struct c_vehicle_type_turret;
struct s_damage_owner;
struct t_arg0;

/* ---------- constants */

enum e_vehicle_type
{
	_vehicle_type_human_tank = 0,
	_vehicle_type_human_jeep,
	_vehicle_type_human_plane,
	_vehicle_type_human_alien_scout,
	_vehicle_type_human_alien_fighter,
	_vehicle_type_turret,
	_vehicle_type_unknown,
	_vehicle_type_vtol,
	_vehicle_type_chopper,
	_vehicle_type_guardian,
	k_vehicle_type_count,
};

/* ---------- definitions */

#pragma pack(push, 4)
struct c_vehicle_type_component
{
	char data[96]; // 0x0
	c_enum<enum e_vehicle_type,char> type; // 0x60
	c_vehicle_type_component(c_vehicle_type_component &); /* compiler_generated() */
	c_vehicle_type_component(c_vehicle_type_component const &); /* compiler_generated() */
	c_vehicle_type_component(); /* compiler_generated() */
	c_vehicle_type_component &operator=(c_vehicle_type_component &); /* compiler_generated() */
	c_vehicle_type_component &operator=(c_vehicle_type_component const &); /* compiler_generated() */
public:
	template<typename t_arg0>
	t_arg0 get() const;
	unsigned char __pad0[3]; // 0x61
};
#pragma pack(pop)
static_assert(sizeof(c_vehicle_type_component) == 100, "Invalid c_vehicle_type_component size");

#pragma pack(push, 4)
struct c_vehicle_auto_turret
{
	long target_unit_index; // 0x0
	long target_set_time; // 0x4
	long dword8; // 0x8
	long target_lost_time; // 0xC
	s_damage_owner damage_onwer; // 0x10
	char field_1C; // 0x1C
	char field_1D; // 0x1D
	char field_1E; // 0x1E
	char field_1F; // 0x1F
	long trigger_volume_index; // 0x20
	static void (*const handle_deleted_object)(c_vehicle_auto_turret *, long, long);
};
#pragma pack(pop)
static_assert(sizeof(c_vehicle_auto_turret) == 36, "Invalid c_vehicle_auto_turret size");

#pragma pack(push, 4)
struct c_vehicle_type_turret
{
	c_vehicle_auto_turret auto_turret; // 0x0
};
#pragma pack(pop)
static_assert(sizeof(c_vehicle_type_turret) == 36, "Invalid c_vehicle_type_turret size");

#pragma pack(push, 4)
struct c_vehicle_type_guardian
{
	long field_0; // 0x0
	long field_4; // 0x4
	c_vehicle_auto_turret auto_turret; // 0x8
};
#pragma pack(pop)
static_assert(sizeof(c_vehicle_type_guardian) == 44, "Invalid c_vehicle_type_guardian size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

template<typename t_arg0>
_inline t_arg0 c_vehicle_type_component::get() const
{
	mangled_prefix_assert("??$get@");
	todo("implement");
	return todo_result<t_arg0>();
}

/* ---------- private code */

#endif // __BLAM_UNITS_VEHICLES_HPP__
