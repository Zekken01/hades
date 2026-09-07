#ifndef __BLAM_RENDER_VIEWS_RENDER_VIEW_HPP__
#define __BLAM_RENDER_VIEWS_RENDER_VIEW_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/render/views/render_camera.hpp"

/* ---------- forward declarations */

struct c_view;
struct s_render_camera;
struct s_render_projection;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct c_view
{
	void **vftable; // 0x0
	s_render_camera rasterizer_camera; // 0x4
	s_render_projection rasterizer_projection; // 0x8C
	s_render_camera render_camera; // 0x14C
	s_render_projection render_projection; // 0x1D4
	static void (*const begin)(c_view *);
	static void (*const end)();
};
#pragma pack(pop)
static_assert(sizeof(c_view) == 660, "Invalid c_view size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_RENDER_VIEWS_RENDER_VIEW_HPP__
