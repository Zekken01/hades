#ifndef __BLAM_RENDER_VIEW_HPP__
#define __BLAM_RENDER_VIEW_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/render/views/render_player_view.hpp"
#include "Blam/render/views/render_view.hpp"

/* ---------- forward declarations */

struct c_player_view;
struct c_view;
struct c_view_stack;

/* ---------- constants */

/* ---------- definitions */

struct c_view_stack
{
	static c_view *(*const get_top)();
	static _inline c_player_view *get_player_view();
};
static_assert(sizeof(c_view_stack) == 1, "Invalid c_view_stack size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline c_player_view *c_view_stack::get_player_view() // 0x108EFE70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_player_view@c_view_stack@@SAPAUc_player_view@@XZ");

	return *(c_player_view * *)0x50dedf0;
}

/* ---------- private code */

#endif // __BLAM_RENDER_VIEW_HPP__
