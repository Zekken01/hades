#ifndef __BLAM_INTERFACE_GUI_GUI_BITMAP_WIDGET_HPP__
#define __BLAM_INTERFACE_GUI_GUI_BITMAP_WIDGET_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/async/async.hpp"
#include "Blam/interface/gui/gui_widget.hpp"
#include "Blam/multithreading/synchronization/synchronized_int.hpp"
#include "Blam/tag_files/files.hpp"

/* ---------- forward declarations */

class c_gui_bitmap_widget;
class c_gui_widget;
class c_synchronized_int32;
struct c_async_completion_flag;
struct c_gui_custom_bitmap_widget;
struct s_file_reference;
struct s_runtime_bitmap_widget_definition;
struct s_runtime_core_widget_definition;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_runtime_bitmap_widget_definition
{
	s_runtime_core_widget_definition core; // 0x0
	long bitmap_definition_index; // 0x34
	long explicit_shader_index; // 0x38
	long blend_mode; // 0x3C
	short field_40; // 0x40
	short field_42; // 0x42
	unsigned long data_source_name; // 0x44
	unsigned long sprite_data_source_name; // 0x48
};
#pragma pack(pop)
static_assert(sizeof(s_runtime_bitmap_widget_definition) == 76, "Invalid s_runtime_bitmap_widget_definition size");

class c_gui_bitmap_widget :
	public c_gui_widget
{
public:
	short get_sprite_frame_count();
	void set_sprite_frame_index(long frame_index);
	long field_DC; // 0xDC
	long bitmap_definition_index; // 0xE0
	long bitmap_index; // 0xE4
	long bitmap_sequence_index; // 0xE8
	s_runtime_bitmap_widget_definition runtime_definition; // 0xEC
	c_gui_bitmap_widget(c_gui_bitmap_widget &); /* compiler_generated() */
	c_gui_bitmap_widget(c_gui_bitmap_widget const &); /* compiler_generated() */
	c_gui_bitmap_widget(); /* compiler_generated() */
	virtual ~c_gui_bitmap_widget() = default; /* compiler_generated() */
	c_gui_bitmap_widget &operator=(c_gui_bitmap_widget &); /* compiler_generated() */
	c_gui_bitmap_widget &operator=(c_gui_bitmap_widget const &); /* compiler_generated() */
};
static_assert(sizeof(c_gui_bitmap_widget) == 312, "Invalid c_gui_bitmap_widget size");

#pragma pack(push, 4)
struct c_gui_custom_bitmap_widget :
	public c_gui_bitmap_widget
{
	long m_storage_item_index; // 0x138
	void *m_async_load_buffer; // 0x13C
	long m_async_load_status; // 0x140
	long m_async_load_task_id; // 0x144
	c_async_completion_flag m_async_load_completion_flag; // 0x148
	c_synchronized_int32 m_length; // 0x150
	s_file_reference file_reference; // 0x154
	bool unknown_flag; // 0x264
	long bitmap_format; // 0x268
	char m_requested_filename[256]; // 0x26C
	char m_filename[256]; // 0x36C
	c_gui_custom_bitmap_widget(c_gui_custom_bitmap_widget &); /* compiler_generated() */
	c_gui_custom_bitmap_widget(c_gui_custom_bitmap_widget const &); /* compiler_generated() */
	c_gui_custom_bitmap_widget(); /* compiler_generated() */
	virtual ~c_gui_custom_bitmap_widget() = default; /* compiler_generated() */
	c_gui_custom_bitmap_widget &operator=(c_gui_custom_bitmap_widget &); /* compiler_generated() */
	c_gui_custom_bitmap_widget &operator=(c_gui_custom_bitmap_widget const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(c_gui_custom_bitmap_widget) == 1132, "Invalid c_gui_custom_bitmap_widget size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_INTERFACE_GUI_GUI_BITMAP_WIDGET_HPP__
