#ifndef __BLAM_INTERFACE_GUI_GUI_WIDGET_RENDER_INFO_HPP__
#define __BLAM_INTERFACE_GUI_GUI_WIDGET_RENDER_INFO_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"

/* ---------- forward declarations */

struct real_point2d;
struct s_gui_bitmap_widget_render_info;
struct s_gui_widget_render_info;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_gui_widget_render_info
{
	char type; // 0x0
	unsigned __int32 flags; // 0x4
	real_point2d vertices[4]; // 0x8
	unsigned char __pad1[4]; // 0x28
};
#pragma pack(pop)
static_assert(sizeof(s_gui_widget_render_info) == 44, "Invalid s_gui_widget_render_info size");

#pragma pack(push, 4)
struct s_gui_bitmap_widget_render_info :
	public s_gui_widget_render_info
{
	long bitmap_group_index; // 0x2C
	union
	{
		struct
		{
			short bitmap_sequence_index; // 0x30
			short bitmap_index; // 0x32
		};
		long storage_item_index; // 0x30
	};
	unsigned char __pad0[12]; // 0x34
	unsigned long color; // 0x40
	float offset_u; // 0x44
	float offset_v; // 0x48
	long blend_mode; // 0x4C
	long explicit_shader_index; // 0x50
};
#pragma pack(pop)
static_assert(sizeof(s_gui_bitmap_widget_render_info) == 84, "Invalid s_gui_bitmap_widget_render_info size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_INTERFACE_GUI_GUI_WIDGET_RENDER_INFO_HPP__
