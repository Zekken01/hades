#ifndef __BLAM_INTERFACE_GUI_GUI_SCREEN_WIDGET_HPP__
#define __BLAM_INTERFACE_GUI_GUI_SCREEN_WIDGET_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/interface/controller_input_message.hpp"
#include "Blam/interface/gui/gui_list_item_widget.hpp"
#include "Blam/interface/gui/gui_list_widget.hpp"
#include "Blam/interface/gui/gui_selected_items.hpp"
#include "Blam/interface/gui/gui_widget.hpp"
#include "Player/PlayerCharacterSystem.hpp"

/* ---------- forward declarations */

class c_gui_data;
class c_gui_list_item_widget;
class c_gui_list_widget;
class c_gui_screen_widget;
class c_gui_widget;
struct c_controller_input_message;
struct c_dialog_result_message;
class c_gui_selected_item;
struct c_message;
struct s_gui_data;
struct s_player_appearance;

/* ---------- constants */

/* ---------- definitions */

class c_gui_data
{
public:
	c_gui_data(c_gui_data const &); /* compiler_generated() */
	_inline c_gui_data();
	virtual ~c_gui_data();
	virtual bool initialize(unsigned long name);
	virtual void dispose();
	virtual void update();
	virtual bool nullsub1();
	virtual long get_current_item_count() = 0;
	virtual long get_first_element_handle() = 0;
	virtual long get_next_element_handle(long) = 0;
	virtual long get_previous_element_handle(long) = 0;
	virtual void get_column_names(unsigned long *, long *) = 0;
	virtual bool get_element(long element_handle, void *element, long element_size);
	virtual bool get_integer_value(long element_handle, unsigned long name, long *value);
	virtual bool get_text_value(long element_handle, unsigned long name, wchar_t (&value)[1024]);
	virtual bool get_string_id_value(long element_handle, unsigned long name, unsigned long *value);
	virtual bool get_qword_value(long element_handle, unsigned long name, unsigned long long *value);
	virtual bool get_real_value(long element_handle, unsigned long name, float *value);
	virtual bool get_player_appearance(long element_handle, s_player_appearance *__formal);
	virtual c_gui_selected_item const *get_gui_selected_item() const;
	virtual long get_maximum_item_count();
	virtual long add_element();
	virtual void delete_element(long element_handle);
	virtual void set_element(long element_handle, void const *element, long element_size);
	virtual bool get_invoked_control(long __formal, long *name);
	virtual void clear_disabled_elements();
	virtual void set_disabled_element(long element_index, unsigned long name);
	virtual void disable_all_elements(unsigned long name);
	virtual void enable_element(long element_index, unsigned long name);
	void set_name(unsigned long name);
private:
	unsigned long m_name; // 0x4
public:
	c_gui_data &operator=(c_gui_data const &); /* compiler_generated() */
};
static_assert(sizeof(c_gui_data) == 8, "Invalid c_gui_data size");

class c_gui_screen_widget :
	public c_gui_widget
{
public:
	virtual void sub_AB99E0() = 0;
	virtual void sub_B122B0() = 0;
	virtual bool get_string_by_string_id(unsigned long, char (&)[1024]) = 0;
	virtual long get_render_data_size() = 0;
	virtual long get_gui_location() = 0;
	virtual void reconstruct() = 0;
	virtual void initialize_datasurce() = 0;
	virtual void reload_assets() = 0;
	virtual void reload_next_frame() = 0;
	virtual void sub_AB1AE0() = 0;
	virtual void sub_AB1B80() = 0;
	virtual void sub_AB0840() = 0;
	virtual void sub_AB29A0() = 0;
	virtual bool progress_message(c_message const *) = 0;
	virtual bool handle_focused_widget_selected(c_controller_input_message const *, c_gui_widget *) = 0;
	virtual bool handle_list_item_chosen(c_controller_input_message const *, unsigned long, c_gui_list_item_widget *, c_gui_data *) = 0;
	virtual bool handle_dialog_result(c_dialog_result_message const *) = 0;
	virtual void submenu_invoked(c_gui_list_widget *) = 0;
	virtual void transition_out_internal(long, long) = 0;
	virtual void sub_AB1760() = 0;
	virtual void sub_AB2930() = 0;
	c_gui_widget *get_focused_widget() const;
	long get_index() const;
	void select_list_item(c_gui_list_widget *list_widget, long item_index, bool flag1, bool flag2);
	c_gui_data *get_datasource(unsigned long name) const;
	void transition_out(__int32 type);
	long field_DC; // 0xDC
	long datum_index; // 0xE0
	long field_E4; // 0xE4
	long field_E8; // 0xE8
	long field_EC; // 0xEC
	c_gui_widget *focused_widget; // 0xF0
	bool screen_disabled; // 0xF4
	long field_F8; // 0xF8
	long field_FC; // 0xFC
	long field_100; // 0x100
	long field_104; // 0x104
	long field_108; // 0x108
	long field_10C; // 0x10C
	bool m_reload_next_frame; // 0x110
	bool unknown_flag; // 0x111
	unsigned long screen_name; // 0x114
	unsigned long initial_focus_list_widget_name; // 0x118
	long initial_focus_unknown; // 0x11C
	long initial_focus_element_handle; // 0x120
	char runtime_definition[136]; // 0x124
	s_gui_data *m_datasource[32]; // 0x1AC
	long m_datasource_count; // 0x22C
	void *text_parsers[20]; // 0x230
	long text_parser_count; // 0x280
	char render_data[6172]; // 0x284
	c_gui_screen_widget(c_gui_screen_widget &); /* compiler_generated() */
	c_gui_screen_widget(c_gui_screen_widget const &); /* compiler_generated() */
	c_gui_screen_widget(); /* compiler_generated() */
	virtual ~c_gui_screen_widget() = default; /* compiler_generated() */
	c_gui_screen_widget &operator=(c_gui_screen_widget &); /* compiler_generated() */
	c_gui_screen_widget &operator=(c_gui_screen_widget const &); /* compiler_generated() */
	void __autoclassinit2(unsigned __int32); /* compiler_generated() */
};
static_assert(sizeof(c_gui_screen_widget) == 6816, "Invalid c_gui_screen_widget size");
static_assert(offsetof(c_gui_screen_widget, field_F8) == 0xF8, "c_gui_screen_widget::field_F8 moved when its reconstructed padding was removed");
static_assert(offsetof(c_gui_screen_widget, screen_name) == 0x114, "c_gui_screen_widget::screen_name moved when its reconstructed padding was removed");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_INTERFACE_GUI_GUI_SCREEN_WIDGET_HPP__
