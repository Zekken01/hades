#ifndef __BLAM_INTERFACE_GUI_SELECTED_ITEMS_MAP_HPP__
#define __BLAM_INTERFACE_GUI_SELECTED_ITEMS_MAP_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/interface/gui/gui_data.hpp"
#include "Blam/networking/session/network_session_membership.hpp"

/* ---------- forward declarations */

class c_gui_map_category_datasource;
class c_gui_ordered_data;

/* ---------- constants */

/* ---------- definitions */

class c_gui_map_category_datasource :
	public c_gui_ordered_data
{
public:
	public:
#pragma pack(push, 4)
	class s_map_category_item
	{
	public:
		long special_status; // 0x0
		long map_id; // 0x4
		wchar_t name[48]; // 0x8
		wchar_t description[256]; // 0x68
		long type; // 0x268
	};
#pragma pack(pop)
	static_assert(sizeof(s_map_category_item) == 620, "Invalid s_map_category_item size");
	public:
	c_gui_map_category_datasource(c_gui_map_category_datasource &); /* compiler_generated() */
	c_gui_map_category_datasource(c_gui_map_category_datasource const &); /* compiler_generated() */
	c_gui_map_category_datasource(wchar_t const *recent_maps_item_name, wchar_t const *recent_maps_item_description, wchar_t const *file_share_item_name, wchar_t const *file_share_item_description);
	virtual bool initialize(unsigned long name);
	virtual void get_column_names(unsigned long *names, long *out_name_count);
	virtual bool get_integer_value(long element_handle, unsigned long name, long *value);
	virtual bool get_text_value(long element_handle, unsigned long name, wchar_t (&value)[1024]);
	virtual _inline bool get_string_id_value(long element_handle, unsigned long name, unsigned long *value);
protected:
	virtual _inline long get_current_item_count_internal();
private:
	wchar_t m_recent_item_name[48]; // 0x10C
	wchar_t m_recent_item_description[256]; // 0x16C
	wchar_t m_file_share_item_name[48]; // 0x36C
	wchar_t m_file_share_item_description[256]; // 0x3CC
	s_static_array<s_map_category_item,100> m_items; // 0x5CC
	long m_item_count; // 0xF7FC
public:
	virtual _inline ~c_gui_map_category_datasource(); /* compiler_generated() */
	c_gui_map_category_datasource &operator=(c_gui_map_category_datasource &); /* compiler_generated() */
	c_gui_map_category_datasource &operator=(c_gui_map_category_datasource const &); /* compiler_generated() */
};
static_assert(sizeof(c_gui_map_category_datasource) == 63488, "Invalid c_gui_map_category_datasource size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_INTERFACE_GUI_SELECTED_ITEMS_MAP_HPP__
