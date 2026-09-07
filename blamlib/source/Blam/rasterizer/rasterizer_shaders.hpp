#ifndef __BLAM_RASTERIZER_RASTERIZER_SHADERS_HPP__
#define __BLAM_RASTERIZER_RASTERIZER_SHADERS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"

/* ---------- forward declarations */

struct c_rasterizer_shaders;
struct real_vector4d;

/* ---------- constants */

/* ---------- definitions */

struct c_rasterizer_shaders
{
	static void (*const set_alpha_test)(bool);
	static bool (*const set_explicit_shaders)(long, long, long, long);
	static bool (*const set_vertex_shader_direct)(IDirect3DVertexShader9 *);
	static bool (*const set_pixel_shader_direct)(IDirect3DPixelShader9 *);
	static void (*const set_pixel_shader_constant)(long, long, real_vector4d const *);
	static void (*const set_pixel_shader_constant_bool)(long, long, __int32 const *);
	static void (*const set_pixel_shader_constant_int)(long, long, __int32 const *);
	static void (*const set_single_pixel_shader_constant)(long, real_vector4d const *);
	static void (*const set_vertex_shader_constant)(long, long, real_vector4d const *);
	static void (*const set_vertex_shader_constant_bool)(long, long, __int32 const *);
	static HRESULT (*const submit_vector_constants)();
	static IDirect3DVertexShader9 *&cached_vertex_shader;
	static IDirect3DPixelShader9 *&cached_pixel_shader;
	static IDirect3DVertexDeclaration9 *&cached_vertex_declaration;
	static void set_single_pixel_shader_constant_int(long, long);
	static void set_single_pixel_shader_constant_bool(long, bool);
	static void get_pixel_shader_constant_int(long, __int32 *);
	static void get_pixel_shader_constant(long, real_vector4d *);
	static void get_vertex_shader_constant(long, real_vector4d *);
};
static_assert(sizeof(c_rasterizer_shaders) == 1, "Invalid c_rasterizer_shaders size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_RASTERIZER_RASTERIZER_SHADERS_HPP__
