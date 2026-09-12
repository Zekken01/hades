#ifndef __BLAM_RASTERIZER_RASTERIZERS_TEXTURES_CACHE_HPP__
#define __BLAM_RASTERIZER_RASTERIZERS_TEXTURES_CACHE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/render/views/render_lights_view.hpp"

/* ---------- forward declarations */

struct c_rasterizer_texture_ref;

/* ---------- constants */

/* ---------- definitions */

struct c_rasterizer_texture_ref
{
	long index; // 0x0
	_inline c_rasterizer_texture_ref(long index);
	static void *(*const get_d3d_texture)(c_rasterizer_texture_ref *);
	static IDirect3DSurface9 *(*const get_d3d_surface)(c_rasterizer_texture_ref *, long, long);
	static bool (*const get_width_height)(c_rasterizer_texture_ref *, long, long *, long *);
	void __dflt_ctor_closure(); /* compiler_generated() */
};
static_assert(sizeof(c_rasterizer_texture_ref) == 4, "Invalid c_rasterizer_texture_ref size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline c_rasterizer_texture_ref::c_rasterizer_texture_ref(long index) // 0x108582D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_rasterizer_texture_ref@@QAE@J@Z");
	// long index;

	this->index = index;
}

/* ---------- private code */

#endif // __BLAM_RASTERIZER_RASTERIZERS_TEXTURES_CACHE_HPP__
