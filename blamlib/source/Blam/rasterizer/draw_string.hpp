#ifndef __BLAM_RASTERIZER_DRAW_STRING_HPP__
#define __BLAM_RASTERIZER_DRAW_STRING_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/color_definitions.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

struct c_draw_string;
struct c_font_cache_base;
struct c_font_cache_mt_safe;
struct c_rasterizer_draw_string;
struct real_argb_color;
struct real_point2d;
struct real_rectangle2d;
struct s_font_header;
struct short_rectangle2d;

/* ---------- constants */

/* ---------- definitions */

struct c_font_cache_mt_safe :
	public c_font_cache_base
{
private:
	char data[8]; // 0x0
public:
	_inline c_font_cache_mt_safe();
	_inline ~c_font_cache_mt_safe();
};
static_assert(sizeof(c_font_cache_mt_safe) == 8, "Invalid c_font_cache_mt_safe size");

#pragma pack(push, 4)
struct c_draw_string
{
	void *vftable; // 0x0
	long flags; // 0x4
	long font; // 0x8
	s_font_header *font_header; // 0xC
	long style; // 0x10
	long justification; // 0x14
	long drop_shadow_style; // 0x18
	real_argb_color color; // 0x1C
	real_argb_color shadow_color; // 0x2C
	float scale; // 0x3C
	float scale_internal; // 0x40
	unsigned char unknown4[2]; // 0x44
	short tab_stop_count; // 0x46
	short tab_stops[16]; // 0x48
	real_rectangle2d x_bounds; // 0x68
	unsigned char unknown5[16]; // 0x78
	real_rectangle2d y_bounds; // 0x88
	unsigned char unknown7[136]; // 0x98
	real_point2d rotation_origin; // 0x120
	float angle_radians; // 0x128
	real_point2d rotation; // 0x12C
	_inline void set_font(long font);
	_inline short get_line_height();
	_inline void set_color(real_argb_color const &color);
	_inline void set_shadow_color(real_argb_color const &color);
	_inline void set_bounds(short_rectangle2d const &bounds);
	_inline void set_style(long style);
	_inline void set_justification(long justification);
	_inline void draw(c_font_cache_base *cache, char const *text);
	_inline void set_scale(float scale);
	_inline void set_drop_shadow_style(long style);
};
#pragma pack(pop)
static_assert(sizeof(c_draw_string) == 308, "Invalid c_draw_string size");

struct c_rasterizer_draw_string :
	public c_draw_string
{
protected:
	char data[1780]; // 0x134
public:
	_inline c_rasterizer_draw_string();
	_inline ~c_rasterizer_draw_string();
};
static_assert(sizeof(c_rasterizer_draw_string) == 2088, "Invalid c_rasterizer_draw_string size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

inline c_font_cache_mt_safe::c_font_cache_mt_safe() // 0x108180A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_font_cache_mt_safe@@QAE@XZ");
	// c_font_cache_mt_safe *const this;
	// function call : void (*)(c_font_cache_mt_safe *)

	((void(__thiscall *const)(c_font_cache_mt_safe *))0x659650)(this);
}

inline c_font_cache_mt_safe::~c_font_cache_mt_safe() // 0x108182F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1c_font_cache_mt_safe@@QAE@XZ");
	// c_font_cache_mt_safe *const this;
	// function call : void (*)(c_font_cache_mt_safe *)

	((void(__thiscall *)(c_font_cache_mt_safe *))0x659720)(this);
}

inline void c_draw_string::set_font(long font) // 0x1081D2F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_font@c_draw_string@@QAEXJ@Z");
	// long font;
	// function call : void (*)(c_draw_string *, long)

	((void(__thiscall *)(c_draw_string *, long))0x659070)(this, font);
}

inline short c_draw_string::get_line_height() // 0x1085FAC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_line_height@c_draw_string@@QAEFXZ");
	// c_draw_string *const this;
	// function call : short (*)(c_draw_string *)

	return ((short(__thiscall *const)(c_draw_string *))0x658440)(this);
}

inline void c_draw_string::set_color(real_argb_color const &color) // 0x1081D260
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_color@c_draw_string@@QAEXABUreal_argb_color@@@Z");
	// real_argb_color const &color;
	// function call : void (*)(c_draw_string *, real_argb_color const &)

	((void(__thiscall *const)(c_draw_string *, real_argb_color const *))0x658df0)(this, &color);
}

inline void c_draw_string::set_shadow_color(real_argb_color const &color) // 0x1081D380
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_shadow_color@c_draw_string@@QAEXABUreal_argb_color@@@Z");
	// real_argb_color const &color;
	// function call : void (*)(c_draw_string *, real_argb_color const &)

	((void(__thiscall *const)(c_draw_string *, real_argb_color const &))0x659190)(this, color);
}

inline void c_draw_string::set_bounds(short_rectangle2d const &bounds) // 0x1081D200
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_bounds@c_draw_string@@QAEXABUshort_rectangle2d@@@Z");
	// short_rectangle2d const &bounds;
	// function call : void (*)(c_draw_string *, short_rectangle2d const &)

	((void(__thiscall *)(c_draw_string *, short_rectangle2d const *))0x658d20)(this, &bounds);
}

inline void c_draw_string::set_style(long style) // 0x1095E770
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_style@c_draw_string@@QAEXJ@Z");
	// long style;
	// function call : void (*)(c_draw_string *, long)

	((void(__thiscall *)(c_draw_string *, long))0x659280)(this, style);
}

inline void c_draw_string::set_justification(long justification) // 0x1085FE70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_justification@c_draw_string@@QAEXJ@Z");
	// long justification;
	// function call : void (*)(c_draw_string *, long)

	((void(__thiscall *)(c_draw_string *, long))0x6590f0)(this, justification);
}

inline void c_draw_string::draw(c_font_cache_base *cache, char const *text) // 0x1081D110
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?draw@c_draw_string@@QAEXPAUc_font_cache_base@@PBD@Z");
	// char const *text;
	// function call : void (*)(c_draw_string *, c_font_cache_base *, char const *)

	((void(__thiscall *const)(c_draw_string *, c_font_cache_base *, char const *))0x657640)(this, cache, text);
}

inline void c_draw_string::set_scale(float scale) // 0x1081D350
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_scale@c_draw_string@@QAEXM@Z");
	// float scale;

	this->scale = scale;
}

inline void c_draw_string::set_drop_shadow_style(long style) // 0x1081D2C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_drop_shadow_style@c_draw_string@@QAEXJ@Z");
	// long style;

	this->style = style;
}

inline c_rasterizer_draw_string::c_rasterizer_draw_string() // 0x10818100
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_rasterizer_draw_string@@QAE@XZ");
	// c_rasterizer_draw_string *const this;
	// function call : c_rasterizer_draw_string *(*)(c_rasterizer_draw_string *)

	((void(__thiscall *)(c_rasterizer_draw_string *))0xa25f00)(this);
}

inline c_rasterizer_draw_string::~c_rasterizer_draw_string() // 0x10818390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1c_rasterizer_draw_string@@QAE@XZ");
	// c_rasterizer_draw_string *const this;
	// function call : c_rasterizer_draw_string *(*)(c_rasterizer_draw_string *)

	((void(__thiscall *)(c_rasterizer_draw_string *))0x6571d0)(this);
}

/* ---------- private code */

#endif // __BLAM_RASTERIZER_DRAW_STRING_HPP__
