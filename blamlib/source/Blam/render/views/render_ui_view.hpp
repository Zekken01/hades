#ifndef __BLAM_RENDER_VIEWS_RENDER_UI_VIEW_HPP__
#define __BLAM_RENDER_VIEWS_RENDER_UI_VIEW_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/render/views/render_view.hpp"

/* ---------- forward declarations */

struct c_ui_view;
struct c_view;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct c_ui_view :
	public c_view
{
	unsigned char __pad0[4]; // 0x294
	__int32 render_surface; // 0x298
};
#pragma pack(pop)
static_assert(sizeof(c_ui_view) == 668, "Invalid c_ui_view size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_RENDER_VIEWS_RENDER_UI_VIEW_HPP__
