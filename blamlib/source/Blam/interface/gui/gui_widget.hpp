#ifndef __BLAM_INTERFACE_GUI_GUI_WIDGET_HPP__
#define __BLAM_INTERFACE_GUI_GUI_WIDGET_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/interface/controller_input_message.hpp"
#include "Blam/interface/gui/gui_widget_types.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"

/* ---------- forward declarations */

class c_gui_bitmap_widget;
class c_gui_list_item_widget;
class c_gui_list_widget;
class c_gui_widget;
struct c_controller_input_message;
struct c_font_cache;
struct c_gui_widget_reference;
struct gui_real_rectangle2d;
struct real_argb_color;
struct real_point2d;
struct real_rectangle2d;
struct s_animation_transform;
struct s_gui_widget_render_data;
struct s_runtime_core_widget_definition;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_runtime_core_widget_definition
{
	long flags; // 0x0
	unsigned long name; // 0x4
	long field_8; // 0x8
	short layer; // 0xC
	real_rectangle2d widescreen_bounds; // 0x10
	real_rectangle2d standard_bounds; // 0x20
	long animation_index; // 0x30
};
#pragma pack(pop)
static_assert(sizeof(s_runtime_core_widget_definition) == 52, "Invalid s_runtime_core_widget_definition size");

#pragma pack(push, 4)
struct c_gui_widget_reference
{
	c_gui_widget *widget; // 0x0
	unsigned char __pad0[8]; // 0x4
};
#pragma pack(pop)
static_assert(sizeof(c_gui_widget_reference) == 12, "Invalid c_gui_widget_reference size");

struct gui_real_rectangle2d
{
	real_point2d top_left; // 0x0
	real_point2d bottom_left; // 0x8
	real_point2d top_right; // 0x10
	real_point2d bottom_right; // 0x18
};
static_assert(sizeof(gui_real_rectangle2d) == 32, "Invalid gui_real_rectangle2d size");

#pragma pack(push, 4)
struct s_gui_widget_render_data
{
	unsigned long name; // 0x0
	short scaled_anchoring; // 0x4
	short render_depth_bias; // 0x6
	gui_real_rectangle2d vertices; // 0x8
	long animation_collection; // 0x28
};
#pragma pack(pop)
static_assert(sizeof(s_gui_widget_render_data) == 44, "Invalid s_gui_widget_render_data size");

#pragma pack(push, 4)
class c_gui_widget
{
public:
	virtual long get_ambient_state() = 0;
	virtual ~c_gui_widget() = 0;
	virtual void initialize() = 0;
	virtual void post_initialize() = 0;
	virtual void dispose() = 0;
	virtual long get_player_index() = 0;
	virtual long get_element_handle() = 0;
	virtual long get_datasource_index() = 0;
	virtual bool get_enabled() = 0;
	virtual bool set_enabled(bool) = 0;
	virtual void *get_core_definition() = 0;
	virtual real_rectangle2d *get_current_bounds(real_rectangle2d *) const = 0;
	virtual real_rectangle2d *get_container_current_bounds(real_rectangle2d *) const = 0;
	virtual bool should_render(bool *) = 0;
	virtual real_argb_color *get_cumulative_color_tint(real_argb_color *) = 0;
	virtual bool can_receive_focus() = 0;
	virtual bool within_focus() = 0;
	virtual c_gui_widget *create_text_widget(void *) = 0;
	virtual c_gui_widget *create_bitmap_widget(void *) = 0;
	virtual c_gui_widget *create_group_widget(void *) = 0;
	virtual c_gui_widget *create_button_key_widget(void *) = 0;
	virtual c_gui_widget *create_list_widget(void *) = 0;
	virtual c_gui_widget *create_list_item_widget(void *) = 0;
	virtual c_gui_widget *create_model_widget(void *) = 0;
	virtual void update() = 0;
	virtual void update_render_state(c_font_cache *, unsigned long) = 0;
	virtual void set_animated_state_baseline(s_animation_transform *) = 0;
	virtual void unknown6C() = 0;
	virtual bool transitioning_out() = 0;
	virtual void assemble_render_data(s_gui_widget_render_data *, real_rectangle2d const *, long, bool, bool, bool) = 0;
	virtual bool handle_widget_backout() = 0;
	virtual bool handle_widget_selected() = 0;
	virtual bool handle_tab(c_controller_input_message const *) = 0;
	virtual bool handle_alt_tab(c_controller_input_message const *) = 0;
	_inline c_gui_widget *get_parent() const;
	_inline c_gui_widget *get_first_child() const;
	_inline c_gui_widget *get_next_sibling() const;
	_inline unsigned long get_name_string_id() const;
	_inline e_gui_widget get_type() const;
	void set_visible(bool visible);
	_inline bool is_visible() const;
	bool is_enabled() const;
	c_gui_widget *find_first_child(e_gui_widget type) const;
	c_gui_widget *find_next_sibling(e_gui_widget type) const;
	void get_render_bounds(real_rectangle2d *bounds) const;
	c_gui_widget *find_ancestor(bool (*predicate)(c_gui_widget const &));
	c_gui_list_widget *get_child_list_widget(unsigned long name);
	c_gui_widget *get_child_widget(e_gui_widget type, unsigned long name) const;
	c_gui_bitmap_widget *get_child_bitmap_widget(unsigned long name);
	c_gui_list_item_widget *get_child_text_widget(unsigned long name);
	void set_text_widget_text(unsigned long name, wchar_t const *text);
	static void (*const tint_widget_to_change_color)(c_gui_widget *, long, bool);
	static void (*const modulate_tint_color)(c_gui_widget *, real_argb_color const *);
	static void (*const set_use_alternate_ambient_state)(c_gui_widget *, bool);
	static void (*const start_animation)(c_gui_widget *, long, bool);
	unsigned char __pad0[4]; // 0x4
	long m_type; // 0x8
	bool m_visible; // 0xC
	bool m_enabled; // 0xD
	bool field_e; // 0xE
	bool m_ambient_state; // 0xF
	c_gui_widget_reference m_parent; // 0x10
	c_gui_widget_reference m_first_child; // 0x1C
	c_gui_widget_reference m_next_sibling; // 0x28
	c_gui_widget_reference m_unknown2; // 0x34
	unsigned long m_name; // 0x40
	unsigned char __pad1[4]; // 0x44
	long m_unkown; // 0x48
	unsigned char __pad2[4]; // 0x4C
	unsigned char m_unknown3[136]; // 0x50
	c_gui_widget(c_gui_widget const &); /* compiler_generated() */
	c_gui_widget(); /* compiler_generated() */
	c_gui_widget &operator=(c_gui_widget const &); /* compiler_generated() */
unsigned char __pad3[4]; // 0xD8
};
#pragma pack(pop)
static_assert(sizeof(c_gui_widget) == 220, "Invalid c_gui_widget size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

inline c_gui_widget *c_gui_widget::get_parent() const // 0x108D5F20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_parent@c_gui_widget@@QBEPAV1@XZ");
	// c_gui_widget const *const this;

	return m_parent.widget;
}

inline c_gui_widget *c_gui_widget::get_first_child() const // 0x108D5E30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_first_child@c_gui_widget@@QBEPAV1@XZ");
	// c_gui_widget const *const this;

	return m_first_child.widget;
}

inline c_gui_widget *c_gui_widget::get_next_sibling() const // 0x108D5EF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_next_sibling@c_gui_widget@@QBEPAV1@XZ");
	// c_gui_widget const *const this;

	return m_next_sibling.widget;
}

inline unsigned long c_gui_widget::get_name_string_id() const // 0x108D5EC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_name_string_id@c_gui_widget@@QBEKXZ");
	// c_gui_widget const *const this;

	return m_name;
}

inline e_gui_widget c_gui_widget::get_type() const // 0x108D5F80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_type@c_gui_widget@@QBE?AW4e_gui_widget@@XZ");
	// c_gui_widget const *const this;

	return static_cast<e_gui_widget>(m_type);
}

inline bool c_gui_widget::is_visible() const // 0x108D5FB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?is_visible@c_gui_widget@@QBE_NXZ");
	// c_gui_widget const *const this;

	return m_visible;
}

/* ---------- private code */

#endif // __BLAM_INTERFACE_GUI_GUI_WIDGET_HPP__
