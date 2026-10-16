#include "DebugMenu/debug_menu.hpp"

#include <math.h>
#include <stdio.h>
#include <string.h>

namespace DebugMenu
{
	/* ---------- c_debug_menu_item */

	c_debug_menu_item::c_debug_menu_item(c_debug_menu *menu, char const *name, c_debug_menu *child, bool active) :
		m_name(nullptr),
		m_menu_ref(menu),
		m_child_ref(child),
		m_active(active)
	{
		set_name(name ? name : "Item???");
	}

	c_debug_menu_item::~c_debug_menu_item()
	{
		if (m_child_ref)
			m_child_ref->~c_debug_menu();
		m_child_ref = nullptr;
	}

	void c_debug_menu_item::update()
	{
	}

	void c_debug_menu_item::render(c_font_cache_base *font_cache, short_point_2d const &position)
	{
		real_argb_color const *color = debug_real_argb_black;
		if (get_active() && get_menu()->get_enabled())
			color = get_enabled_color();

		short_rectangle2d screen = debug_menu_get_screen_bounds();
		debug_menu_draw_string(font_cache, position.x, position.y, screen.x1, screen.y1, color, get_name());
	}

	void c_debug_menu_item::notify_selected()
	{
		if (get_child())
			debug_menu_set_active_menu(get_child(), false);
	}

	void c_debug_menu_item::open()
	{
		set_active(true);
	}

	void c_debug_menu_item::notify_left()
	{
	}

	void c_debug_menu_item::notify_right()
	{
	}

	real_argb_color const *c_debug_menu_item::get_enabled_color()
	{
		return get_child() ? debug_real_argb_tv_green : debug_real_argb_grey;
	}

	real_argb_color const *c_debug_menu_item::get_background_color()
	{
		if (!get_is_selection())
			return debug_real_argb_tv_white;

		// The selected item pulses between dark and the white of the other items.
		float phase = (debug_menu_get_time() % 80) / 79.0f;
		float wave = phase < 0.5f ? phase + phase : 1.0f - ((phase - 0.5f) + (phase - 0.5f));
		float weight = (wave * 0.4f) + 0.05f;

		static real_argb_color background_color;
		background_color.alpha = 1.0f;
		background_color.red = debug_real_argb_tv_white->red * weight;
		background_color.green = debug_real_argb_tv_white->green * weight;
		background_color.blue = debug_real_argb_tv_white->blue * weight;
		return &background_color;
	}

	char const *c_debug_menu_item::get_name()
	{
		return m_name ? m_name : "";
	}

	void c_debug_menu_item::set_name(char const *name)
	{
		long name_size = long(strlen(name)) + 1;
		m_name = static_cast<char *>(debug_menu_malloc(name_size));
		strcpy_s(m_name, name_size, name);
	}

	c_debug_menu *c_debug_menu_item::get_menu()
	{
		return m_menu_ref;
	}

	c_debug_menu *c_debug_menu_item::get_child()
	{
		return m_child_ref;
	}

	bool c_debug_menu_item::get_active()
	{
		return m_active;
	}

	void c_debug_menu_item::set_active(bool active)
	{
		m_active = active;
	}

	short c_debug_menu_item::get_index()
	{
		for (short item_index = 0; item_index < get_menu()->get_num_items(); item_index++)
		{
			if (get_menu()->get_item(item_index) == this)
				return item_index;
		}
		return 0;
	}

	bool c_debug_menu_item::get_is_selection()
	{
		return get_index() == get_menu()->get_selection();
	}

	/* ---------- c_debug_menu_item_numbered */

	void c_debug_menu_item_numbered::render(c_font_cache_base *font_cache, short_point_2d const &position)
	{
		render_number(font_cache, position);

		short_point_2d name_position = { short(position.x + get_indent()), position.y };
		c_debug_menu_item::render(font_cache, name_position);
	}

	c_debug_menu_item_numbered::c_debug_menu_item_numbered(c_debug_menu *menu, char const *name, c_debug_menu *child) :
		c_debug_menu_item(menu, name, child, true)
	{
	}

	void c_debug_menu_item_numbered::render_number(c_font_cache_base *font_cache, short_point_2d const &position)
	{
		// Items 1-10 are picked with the number keys, the next 26 with a-z.
		char buffer[64];
		short index = get_index();
		if (index < 10)
			sprintf_s(buffer, "   %s%d", index < 9 ? " " : "", index + 1);
		else if (index < 36)
			sprintf_s(buffer, "(%c)%d", index + 87, index + 1);
		else
			sprintf_s(buffer, "   %d", index + 1);

		real_argb_color const *color = get_active() ? get_enabled_color() : debug_real_argb_black;
		short_rectangle2d screen = debug_menu_get_screen_bounds();
		debug_menu_draw_string(font_cache, position.x - 3, position.y, screen.x1, screen.y1, color, buffer);
	}

	short c_debug_menu_item_numbered::get_indent()
	{
		return 45;
	}

	/* ---------- c_debug_menu_item_hs_command */

	void c_debug_menu_item_hs_command::notify_selected()
	{
		if (m_command)
			debug_menu_execute_command(m_command);
	}

	real_argb_color const *c_debug_menu_item_hs_command::get_enabled_color()
	{
		return debug_real_argb_tv_orange;
	}

	c_debug_menu_item_hs_command::c_debug_menu_item_hs_command(c_debug_menu *menu, char const *name, char const *command) :
		c_debug_menu_item_numbered(menu, name, nullptr),
		m_command(nullptr)
	{
		long command_length = long(strlen(command)) + 1;
		m_command = static_cast<char *>(debug_menu_malloc(command_length));
		strcpy_s(m_command, command_length, command);
	}

	/* ---------- c_debug_menu_item_type */

	c_debug_menu_item_type::c_debug_menu_item_type(c_debug_menu *menu, char const *name, char const *variable, float min, float max, float inc) :
		c_debug_menu_item_numbered(menu, name, nullptr),
		m_value(variable),
		m_min(min),
		m_max(max),
		m_inc(inc)
	{
	}

	void c_debug_menu_item_type::render(c_font_cache_base *font_cache, short_point_2d const &position)
	{
		short_point_2d value_point = { short(position.x - 66), position.y };
		render_value(font_cache, value_point);
		render_number(font_cache, position);

		short_point_2d name_point = { short(position.x + get_indent()), position.y };
		c_debug_menu_item::render(font_cache, name_point);
	}

	void c_debug_menu_item_type::notify_left()
	{
		step(-1.0f);
	}

	void c_debug_menu_item_type::notify_right()
	{
		step(1.0f);
	}

	void c_debug_menu_item_type::step(float direction)
	{
		switch (m_value.get_type())
		{
		case k_debug_menu_value_bool:
			m_value.set(m_value.get() != 0.0 ? 0.0 : 1.0);
			break;
		case k_debug_menu_value_real:
		case k_debug_menu_value_short:
		case k_debug_menu_value_long:
		{
			double value = m_value.get() + direction * m_inc;
			value = value < m_min ? m_min : value > m_max ? m_max : value;
			m_value.set(value);
		}
		break;
		}
	}

	void c_debug_menu_item_type::to_string(char *buffer, long buffer_size)
	{
		switch (m_value.get_type())
		{
		case k_debug_menu_value_bool:
			sprintf_s(buffer, buffer_size, "%s", m_value.get() != 0.0 ? "True" : "False");
			break;
		case k_debug_menu_value_real:
			sprintf_s(buffer, buffer_size, "%f", m_value.get());
			break;
		case k_debug_menu_value_short:
		case k_debug_menu_value_long:
			sprintf_s(buffer, buffer_size, "%ld", long(m_value.get()));
			break;
		default:
			sprintf_s(buffer, buffer_size, "n/a");
			break;
		}
	}

	void c_debug_menu_item_type::render_value(c_font_cache_base *font_cache, short_point_2d const &position)
	{
		char buffer[64];
		to_string(buffer, sizeof(buffer));

		if (get_active())
		{
			short x0 = position.x;
			short y0 = short(position.y + debug_menu_get_item_indent_y());
			short x1 = short(position.x + 60);
			short y1 = short((position.y + get_menu()->get_item_height()) - (2.0f * debug_menu_get_item_indent_y()));
			debug_menu_draw_rect(x0, y0, x1, y1, get_menu()->get_enabled() ? 0.7f : 0.1f, get_background_color());
		}

		real_argb_color const *color = get_active() ? debug_real_argb_grey : debug_real_argb_black;
		debug_menu_draw_string(font_cache, position.x + 2, position.y, position.x + 60, position.y + get_menu()->get_item_height(), color, buffer);
	}
}
