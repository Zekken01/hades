#ifndef __BLAM_RENDER_VIEWS_RENDER_FIRST_PERSON_VIEW_HPP__
#define __BLAM_RENDER_VIEWS_RENDER_FIRST_PERSON_VIEW_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/render/views/render_camera.hpp"
#include "Blam/render/views/render_view.hpp"

/* ---------- forward declarations */

struct c_first_person_view;
struct c_view;
struct s_render_camera;

/* ---------- constants */

/* ---------- definitions */

struct c_first_person_view :
	public c_view
{
	s_render_camera *camera; // 0x294
};
static_assert(sizeof(c_first_person_view) == 664, "Invalid c_first_person_view size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_RENDER_VIEWS_RENDER_FIRST_PERSON_VIEW_HPP__
