#ifndef __BLAM_EFFECTS_PARTICLE_STATES_HPP__
#define __BLAM_EFFECTS_PARTICLE_STATES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/particle.hpp"
#include "Blam/effects/particle_system.hpp"

/* ---------- forward declarations */

class c_particle_state_list;
struct c_particle;
struct c_particle_system;
struct s_particle_system_definition;

/* ---------- constants */

enum e_particle_states
{
	_particle_state_age = 0, // 0x0000
	_particle_state_system_age = 1, // 0x0001
	_particle_state_random_seed = 2, // 0x0002
	_particle_state_system_random_seed = 3, // 0x0003
	_particle_state_random_1 = 4, // 0x0004
	_particle_state_random_2 = 5, // 0x0005
	_particle_state_random_3 = 6, // 0x0006
	_particle_state_random_4 = 7, // 0x0007
	_particle_state_system_random_1 = 8, // 0x0008
	_particle_state_system_random_2 = 9, // 0x0009
	_particle_state_system_time = 10, // 0x000A
	_particle_state_system_lod = 11, // 0x000B
	_particle_state_game_time = 12, // 0x000C
	_particle_state_effect_a_scale = 13, // 0x000D
	_particle_state_effect_b_scale = 14, // 0x000E
	_particle_state_physics_rotation = 15, // 0x000F
	_particle_state_location_random = 16, // 0x0010
	_particle_state_distance_from_emitter = 17, // 0x0011
	_particle_state_simulation_a = 18, // 0x0012
	_particle_state_simulation_b = 19, // 0x0013
	_particle_state_velocity = 20, // 0x0014
	_particle_state_random_5 = 21, // 0x0015
	_particle_state_random_6 = 22, // 0x0016
	_particle_state_random_7 = 23, // 0x0017
	_particle_state_random_8 = 24, // 0x0018
	_particle_state_system_random_3 = 25, // 0x0019
	_particle_state_system_random_4 = 26, // 0x001A
	k_number_of_particle_states = 27, // 0x001B
	_particle_state_invalid = 255, // 0x00FF
};

/* ---------- definitions */

#pragma pack(push, 4)
class c_particle_state_list
{
public:
	float m_states[27]; // 0x0
	long m_used_states; // 0x6C
	long m_updated_states; // 0x70
	c_particle_system *m_particle_system; // 0x74
	s_particle_system_definition *m_particle_system_definition; // 0x78
	void *m_particle_location; // 0x7C
	c_particle *m_particle; // 0x80
	static long &x_force_used_states;
	c_particle_state_list();
	static void (*set_null_particle)(c_particle_state_list *);
	static void (*set_particle_location)(c_particle_state_list *, void *);
	static void (*set_particle_system)(c_particle_state_list *, c_particle_system *);
	static void (*update_states)(c_particle_state_list *, long);
	static void (*update_states_internal)(c_particle_state_list *, long);
};
#pragma pack(pop)
static_assert(sizeof(c_particle_state_list) == 132, "Invalid c_particle_state_list size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_EFFECTS_PARTICLE_STATES_HPP__
