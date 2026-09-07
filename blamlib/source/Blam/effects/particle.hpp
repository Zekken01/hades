#ifndef __BLAM_EFFECTS_PARTICLE_HPP__
#define __BLAM_EFFECTS_PARTICLE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"

/* ---------- forward declarations */

struct c_particle;
struct real_argb_color;
struct real_vector3d;
struct s_datum;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct c_particle :
	public s_datum
{
	short field_02; // 0x2
	long field_04; // 0x4
	long particle_emitter_datum; // 0x8
	long m_start_vertex; // 0xC
	float m_age; // 0x10
	float m_inverse_lifespan; // 0x14
	float m_system_age; // 0x18
	short m_state_random_seeds[8]; // 0x1C
	real_point3d m_position; // 0x2C
	real_vector3d m_velocity; // 0x38
	float m_mass; // 0x44
	long field_48; // 0x48
	real_argb_color m_tint; // 0x4C
	real_vector3d direction; // 0x5C
	long field_68; // 0x68
	float animation_rate; // 0x6C
	long field_70; // 0x70
	long field_74; // 0x74
	long field_78; // 0x78
	static c_particle *(*get)(unsigned long);
};
#pragma pack(pop)
static_assert(sizeof(c_particle) == 124, "Invalid c_particle size");

/* ---------- prototypes */

extern c_data_array<c_particle> *particles_get();

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_EFFECTS_PARTICLE_HPP__
