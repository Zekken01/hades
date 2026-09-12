#ifndef __BLAM_EFFECTS_PARTICLE_SYSTEM_HPP__
#define __BLAM_EFFECTS_PARTICLE_SYSTEM_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/particle.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

struct c_particle;
struct c_particle_system;
struct real_vector3d;
struct s_datum;

/* ---------- constants */

/* ---------- definitions */

struct c_particle_system :
	public s_datum
{
	short field_02; // 0x2
	float state_emitter_age; // 0x4
	short flags; // 0x8
	short particle_system_index; // 0xA
	__int32 effect_tag_index; // 0xC
	char event_index; // 0x10
	char field_11; // 0x11
	short field_12; // 0x12
	__int32 effect_index; // 0x14
	__int32 effect_lightprobe_index; // 0x18
	__int32 field_1C; // 0x1C
	__int32 field_20; // 0x20
	float effect_scale_a; // 0x24
	float effect_scale_b; // 0x28
	long random_seed; // 0x2C
	float state_emitter_random1; // 0x30
	float state_emitter_random2; // 0x34
	float state_emitter_random3; // 0x38
	float state_emitter_random4; // 0x3C
	short particle_location_index; // 0x40
	short field_42; // 0x42
	__int32 field_44; // 0x44
	__int32 field_48; // 0x48
	__int32 field_4C; // 0x4C
	__int32 field_50; // 0x50
	__int32 field_54; // 0x54
	static c_particle_system *(*get)(unsigned long);
	_inline void *get_particle_definition();
	_inline float real_internal_random_range(float min, float max);
	_inline void internal_random_direction3d(real_vector3d *direction);
	_inline void initialize_particle(void *state_list, c_particle *particle);
};
static_assert(sizeof(c_particle_system) == 88, "Invalid c_particle_system size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline void *c_particle_system::get_particle_definition() // 0x10913010
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_particle_definition@c_particle_system@@QAEPAXXZ");
	// c_particle_system *const this;
	// void *(*const c_particle_system__get_particle_definition)(c_particle_system *);
	// function call : void *(*const)(c_particle_system *)

	void * (__thiscall *const c_particle_system__get_particle_definition)(c_particle_system *) = (void *(__thiscall *const)(c_particle_system *))0x74f290;

	return c_particle_system__get_particle_definition(this);
}

_inline float c_particle_system::real_internal_random_range(float min, float max) // 0x10913DE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?real_internal_random_range@c_particle_system@@QAEMMM@Z");
	// float max;
	// float (*const c_particle_system__real_internal_random_range)(c_particle_system *, float, float);
	// function call : float (*const)(c_particle_system *, float, float)

	float (__thiscall *const c_particle_system__real_internal_random_range)(c_particle_system *, float, float) = (float(__thiscall *const)(c_particle_system *, float, float))0x74f820;

	return c_particle_system__real_internal_random_range(this, min, max);
}

_inline void c_particle_system::internal_random_direction3d(real_vector3d *direction) // 0x10913C60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?internal_random_direction3d@c_particle_system@@QAEXPAUreal_vector3d@@@Z");
	// real_vector3d *direction;
	// void (*const c_particle_system__internal_random_direction3d)(c_particle_system *, real_vector3d *);
	// function call : void (*const)(c_particle_system *, real_vector3d *)

	void (__thiscall *const c_particle_system__internal_random_direction3d)(c_particle_system *, real_vector3d *) = (void(__thiscall *const)(c_particle_system *, real_vector3d *))0x9ee030;

	c_particle_system__internal_random_direction3d(this, direction);
}

_inline void c_particle_system::initialize_particle(void *state_list, c_particle *particle) // 0x109131A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize_particle@c_particle_system@@QAEXPAXPAUc_particle@@@Z");
	// c_particle *particle;
	// void (*const c_particle_system__initialize_particle)(c_particle_system *, void *, c_particle *);
	// function call : void (*const)(c_particle_system *, void *, c_particle *)

	void (__thiscall *const c_particle_system__initialize_particle)(c_particle_system *, void *, c_particle *) = (void(__thiscall *const)(c_particle_system *, void *, c_particle *))0x74f540;

	c_particle_system__initialize_particle(this, state_list, particle);
}

/* ---------- private code */

#endif // __BLAM_EFFECTS_PARTICLE_SYSTEM_HPP__
