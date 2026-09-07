#ifndef __BLAM_MAIN_MAIN_RENDER_HPP__
#define __BLAM_MAIN_MAIN_RENDER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/camera/observer.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class c_wait_for_render_thread;
struct c_player_render_camera_iterator;
struct s_observer_result;

/* ---------- constants */

/* ---------- definitions */

class c_wait_for_render_thread
{
public:
	_inline c_wait_for_render_thread();
	_inline ~c_wait_for_render_thread();
private:
	long m_lock_handle; // 0x0
};
static_assert(sizeof(c_wait_for_render_thread) == 4, "Invalid c_wait_for_render_thread size");

struct c_player_render_camera_iterator
{
	__int32 m_window_count; // 0x0
	__int32 m_window_arrangement; // 0x4
	__int32 m_current_iteration; // 0x8
	__int32 m_output_user_index; // 0xC
	s_observer_result *m_observer_result; // 0x10
	c_player_render_camera_iterator();
	static short *(*const get_cluster_reference)(c_player_render_camera_iterator *, short *);
	static s_observer_result *(*const get_observer_result)(c_player_render_camera_iterator *);
	static long (*const get_output_user_index)(c_player_render_camera_iterator *);
	static long (*const get_window_arrangement)(c_player_render_camera_iterator *);
	static long (*const get_window_count)(c_player_render_camera_iterator *);
};
static_assert(sizeof(c_player_render_camera_iterator) == 20, "Invalid c_player_render_camera_iterator size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

extern c_wait_for_render_thread* _sub_10900E20(c_wait_for_render_thread *const);
_inline c_wait_for_render_thread::c_wait_for_render_thread() // 0x10900E20
{
	mangled_x86(MANGLED_TODO, "??0c_wait_for_render_thread@@QAE@XZ");
	// c_wait_for_render_thread *const this;
	// long (*const _internal_halt_render_thread_and_lock_resources)();
	// function call : long (*const)()
	todo("implement");
	_sub_10900E20(this);
}

_extern void _sub_109010B0(c_wait_for_render_thread *const);
_inline c_wait_for_render_thread::~c_wait_for_render_thread() // 0x109010B0
{
	mangled_x86(MANGLED_TODO, "??1c_wait_for_render_thread@@QAE@XZ");
	// c_wait_for_render_thread *const this;
	// void (*const unlock_resources_and_resume_render_thread)(long);
	// function call : void (*const)(long)
	todo("implement");
	_sub_109010B0(this);
}

/* ---------- private code */

#endif // __BLAM_MAIN_MAIN_RENDER_HPP__
