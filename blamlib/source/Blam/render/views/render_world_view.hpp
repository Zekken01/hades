#ifndef __BLAM_RENDER_VIEWS_RENDER_WORLD_VIEW_HPP__
#define __BLAM_RENDER_VIEWS_RENDER_WORLD_VIEW_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/render/views/render_view.hpp"

/* ---------- forward declarations */

struct c_view;
struct c_world_view;

/* ---------- constants */

/* ---------- definitions */

struct c_world_view :
	public c_view
{
	unsigned char __pad0[4]; // 0x294
};
static_assert(sizeof(c_world_view) == 664, "Invalid c_world_view size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_RENDER_VIEWS_RENDER_WORLD_VIEW_HPP__
