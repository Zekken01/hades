#ifndef __BLAM_CAMERA_DIRECTOR_HPP__
#define __BLAM_CAMERA_DIRECTOR_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/camera/camera.hpp"
#include "Blam/camera/observer.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/objects/damage_definitions.hpp"

/* ---------- forward declarations */

class c_camera;
class c_director;
struct s_director_globals;
struct s_director_info;
struct s_observer_command;

/* ---------- constants */

/* ---------- definitions */

struct s_director_info
{
	c_enum<enum e_director_mode,long> director_mode; // 0x0
	c_enum<enum e_director_perspective,long> perspective; // 0x4
	long camera_mode; // 0x8
	s_director_info(s_director_info &); /* compiler_generated() */
	s_director_info(s_director_info const &); /* compiler_generated() */
	s_director_info(); /* compiler_generated() */
	s_director_info &operator=(s_director_info &); /* compiler_generated() */
	s_director_info &operator=(s_director_info const &); /* compiler_generated() */
};
static_assert(sizeof(s_director_info) == 12, "Invalid s_director_info size");

#pragma pack(push, 4)
class c_director
{
public:
	virtual long get_type() const = 0;
	virtual void update(float) = 0;
	virtual bool should_draw_hud_normal() const = 0;
	virtual bool should_draw_hud_saved_film() const = 0;
	virtual bool inhibits_facing() const = 0;
	virtual bool inhibits_input() const = 0;
	virtual void handle_deleted_player(long) = 0;
	virtual void handle_deleted_object(long) = 0;
	virtual bool can_use_camera_mode(long) const = 0;
	_inline c_camera *get_camera();
	unsigned char camera_storage[76]; // 0x4
	s_observer_command last_command; // 0x50
	long field_13C; // 0x13C
	long user_index; // 0x140
	long watched_player_index; // 0x144
	bool m_player_switch_gui_shown; // 0x148
	c_director(c_director &); /* compiler_generated() */
	c_director(c_director const &); /* compiler_generated() */
	c_director(); /* compiler_generated() */
	c_director &operator=(c_director &); /* compiler_generated() */
	c_director &operator=(c_director const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(c_director) == 332, "Invalid c_director size");

struct s_director_globals
{
	s_static_array<unsigned char [352],4> directors; // 0x0
	s_director_info director_info[4]; // 0x580
	s_director_globals(s_director_globals &); /* compiler_generated() */
	s_director_globals(s_director_globals const &); /* compiler_generated() */
	s_director_globals(); /* compiler_generated() */
	s_director_globals &operator=(s_director_globals &); /* compiler_generated() */
	s_director_globals &operator=(s_director_globals const &); /* compiler_generated() */
	unsigned char __pad0[16]; // 0x5B0
};
static_assert(sizeof(s_director_globals) == 1472, "Invalid s_director_globals size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

inline c_camera *c_director::get_camera() // 0x1095B280
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_camera@c_director@@QAEPAVc_camera@@XZ");
	// c_director *const this;

	return (c_camera *)camera_storage;
}

/* ---------- private code */

#endif // __BLAM_CAMERA_DIRECTOR_HPP__
