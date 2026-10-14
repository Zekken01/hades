#ifndef __BLAM_RASTERIZER_RASTERIZER_GEOMETRY_HPP__
#define __BLAM_RASTERIZER_RASTERIZER_GEOMETRY_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include <d3d9.h>

/* ---------- forward declarations */

class c_rasterizer_index_buffer;
class c_rasterizer_vertex_buffer;

/* ---------- constants */

/* ---------- definitions */

class c_rasterizer_vertex_buffer
{
public:
	unsigned char get_declaration() const;
	_inline unsigned char get_vertex_stride() const;
	_inline short get_vertex_count() const;
	_inline IDirect3DVertexBuffer9 *get_d3d_buffer();
	_inline void const *get_data() const;
private:
	unsigned char declaration; // 0x0
	unsigned char vertex_stride; // 0x1
	unsigned short vertex_count; // 0x2
	IDirect3DVertexBuffer9 *d3d_buffer; // 0x4
	void *data; // 0x8
public:
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
unsigned char __pad0[4]; // 0xC
};
static_assert(sizeof(c_rasterizer_vertex_buffer) == 16, "Invalid c_rasterizer_vertex_buffer size");

class c_rasterizer_index_buffer
{
public:
	unsigned char get_primtive_type();
	IDirect3DIndexBuffer9 *get_d3d_buffer();
	_inline void const *get_data() const;
	_inline unsigned long const get_index_count() const;
private:
	unsigned char primitive_type; // 0x0
	unsigned char stride; // 0x1
	unsigned char __pad0[2]; // 0x2
	unsigned long index_count; // 0x4
	IDirect3DIndexBuffer9 *d3d_buffer; // 0x8
	void *data; // 0xC
public:
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_rasterizer_index_buffer) == 16, "Invalid c_rasterizer_index_buffer size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

inline unsigned char c_rasterizer_vertex_buffer::get_vertex_stride() const // 0x108EFEC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_vertex_stride@c_rasterizer_vertex_buffer@@QBEEXZ");
	// c_rasterizer_vertex_buffer const *const this;

	return vertex_stride;
}

inline short c_rasterizer_vertex_buffer::get_vertex_count() const // 0x108EFE90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_vertex_count@c_rasterizer_vertex_buffer@@QBEFXZ");
	// c_rasterizer_vertex_buffer const *const this;

	return vertex_count;
}

inline IDirect3DVertexBuffer9 *c_rasterizer_vertex_buffer::get_d3d_buffer() // 0x107BF780
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_d3d_buffer@c_rasterizer_vertex_buffer@@QAEPAUIDirect3DVertexBuffer9@@XZ");
	// c_rasterizer_vertex_buffer *const this;

	return d3d_buffer;
}

inline void const *c_rasterizer_vertex_buffer::get_data() const // 0x108EF040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_data@c_rasterizer_vertex_buffer@@QBEPBXXZ");
	// c_rasterizer_vertex_buffer const *const this;

	return data;
}

inline void const *c_rasterizer_index_buffer::get_data() const // 0x108EF010
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_data@c_rasterizer_index_buffer@@QBEPBXXZ");
	// c_rasterizer_index_buffer const *const this;

	return data;
}

inline unsigned long const c_rasterizer_index_buffer::get_index_count() const // 0x108EFCD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_index_count@c_rasterizer_index_buffer@@QBE?BKXZ");
	// c_rasterizer_index_buffer const *const this;

	return index_count;
}

/* ---------- private code */

#endif // __BLAM_RASTERIZER_RASTERIZER_GEOMETRY_HPP__
