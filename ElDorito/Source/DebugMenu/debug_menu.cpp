#include "DebugMenu/debug_menu.hpp"

#include "Blam/Cache/StringIdCache.hpp"

#include <stdio.h>
#include <string.h>

namespace DebugMenu
{
	namespace
	{
		// The zone sets of the loaded scenario, read straight from the tag: the scenario
		// keeps them as a tag block at +0x54, 0x24 bytes per element (name string_id at
		// +0x0, BSP zone flags at +0xC).
		auto const global_scenario = reinterpret_cast<char **>(0x022AAEB4);
		auto const main_switch_zone_set = reinterpret_cast<void (*)(long)>(0x00507210);

		long zone_set_count()
		{
			char *scenario = *global_scenario;
			return scenario ? *reinterpret_cast<long *>(scenario + 0x54) : 0;
		}

		char *zone_set_get(long index)
		{
			return *reinterpret_cast<char **>(*global_scenario + 0x58) + index * 0x24;
		}
	}

	/* ---------- c_debug_menu */

	c_debug_menu::~c_debug_menu()
	{
		clear();
	}

	void c_debug_menu::update()
	{
		if (get_selection() >= 0 && get_selection() < get_num_items() && !get_item(get_selection())->get_active())
		{
			short selection = get_selection();
			short num_items = get_num_items();
			for (short i = 1; i < get_num_items(); i++)
			{
				short item_index = (selection + i) % num_items;
				if (get_item(item_index)->get_active())
				{
					set_selection(item_index);
					break;
				}
			}
		}

		for (short item_index = 0; item_index < get_num_items(); item_index++)
			get_item(item_index)->update();

		if (get_enabled())
		{
			if (debug_menu_button_held(_debug_menu_button_up))
				notify_up();
			else if (debug_menu_button_held(_debug_menu_button_down))
				notify_down();
			else if (debug_menu_button_held(_debug_menu_button_left))
				try_left();
			else if (debug_menu_button_held(_debug_menu_button_right))
				try_right();
			else
			{
				m_last_up = 0;
				m_last_down = 0;
				m_last_left = 0;
				m_last_right = 0;
			}
		}

		if (get_enabled() && get_num_items() > 0 && get_item(get_selection())->get_active() && debug_menu_button_pressed(_debug_menu_button_select))
		{
			get_item(get_selection())->notify_selected();
			notify_selected(get_selection());
		}
		else if (debug_menu_button_pressed(_debug_menu_button_back))
		{
			close(false);
		}
		else
		{
			short selection = debug_menu_shortcut_pressed();
			if (selection != -1 && selection < get_num_items())
			{
				set_selection(selection);
				get_item(get_selection())->notify_selected();
				notify_selected(get_selection());
			}
		}
	}

	void c_debug_menu::render(c_font_cache_base *font_cache, short_point_2d const &point)
	{
		render_background(font_cache, point);
		render_title(font_cache, point);
		render_caption(font_cache, point);
		render_global_caption(font_cache, point);
		render_items(font_cache, point, 0, get_num_items() - 1);
	}

	void c_debug_menu::notify_selected(short selected_value)
	{
	}

	void c_debug_menu::open()
	{
		for (short item_index = 0; item_index < get_num_items(); item_index++)
			get_item(item_index)->open();

		set_selection(0);
		set_enabled(true);
	}

	char const *c_debug_menu::get_caption()
	{
		return m_caption ? m_caption : "";
	}

	void c_debug_menu::notify_closed()
	{
	}

	void c_debug_menu::notify_activated()
	{
	}

	long c_debug_menu::get_num_items_to_render()
	{
		return get_num_items();
	}

	void c_debug_menu::close(bool closed)
	{
		debug_menu_set_active_menu(get_parent(), false);
		notify_closed();

		if (get_parent())
		{
			if (closed)
				get_parent()->notify_selection_closed();
			else
				get_parent()->notify_selection_exited();
		}
	}

	short c_debug_menu::get_value_width()
	{
		return 0;
	}

	void c_debug_menu::notify_selection_closed()
	{
	}

	void c_debug_menu::notify_selection_exited()
	{
	}

	void c_debug_menu::notify_up()
	{
		if (!is_active_menu() || debug_menu_get_time() - m_last_up < get_menu_rate() || !get_num_items())
			return;

		short selection = get_selection();
		m_last_up = debug_menu_get_time();

		c_debug_menu_item *item = nullptr;
		do
		{
			short current_selection = get_selection();
			if (get_selection() <= 0)
				current_selection = get_num_items();
			set_selection(current_selection - 1);

			item = get_item(get_selection());
		} while (!item->get_active());

		if (!get_item(get_selection())->get_active())
			set_selection(selection);
	}

	void c_debug_menu::notify_down()
	{
		if (!is_active_menu() || debug_menu_get_time() - m_last_down < get_menu_rate() || !get_num_items())
			return;

		short selection = get_selection();
		m_last_down = debug_menu_get_time();

		c_debug_menu_item *item = nullptr;
		do
		{
			if (get_selection() >= get_num_items() - 1)
				set_selection(0);
			else
				set_selection(get_selection() + 1);

			item = get_item(get_selection());
		} while (!item->get_active());

		if (!get_item(get_selection())->get_active())
			set_selection(selection);
	}

	void c_debug_menu::notify_left()
	{
	}

	void c_debug_menu::notify_right()
	{
	}

	bool c_debug_menu::is_active_menu()
	{
		for (short item_index = 0; item_index < get_num_items(); item_index++)
		{
			if (get_item(item_index)->get_active())
				return true;
		}
		return false;
	}

	short c_debug_menu::get_menu_rate()
	{
		return 5;
	}

	short c_debug_menu::get_max_active_captions()
	{
		short max_active_captions = *get_caption() != 0;
		for (short caption_index = 0; caption_index < k_debug_menu_num_global_captions; caption_index++)
		{
			if (*debug_menu_get_caption(caption_index))
				max_active_captions = caption_index + 2;
		}
		return max_active_captions;
	}

	void c_debug_menu::render_background(c_font_cache_base *font_cache, short_point_2d const &point)
	{
		float item_margin = get_value_width() ? debug_menu_get_item_margin() : 0.0f;

		short x0 = short((((point.x - debug_menu_get_item_margin()) - get_num_items_to_render()) - item_margin) - 60.0f);
		short y0 = point.y;
		short x1 = short((point.x + debug_menu_get_item_width()) + debug_menu_get_item_margin());
		short y1 = short((point.y + get_title_height()) + (get_num_items_to_render() + get_max_active_captions()) * get_item_height());

		debug_menu_draw_rect(x0, y0, x1, y1, get_enabled() ? 0.7f : 0.1f, debug_real_argb_tv_blue);
	}

	void c_debug_menu::render_title(c_font_cache_base *font_cache, short_point_2d const &point)
	{
		short x0 = point.x;
		short y0 = short(point.y + debug_menu_get_item_indent_y());
		short x1 = short(point.x + debug_menu_get_item_width());
		short y1 = short((point.y + get_item_height()) - (2.0f * debug_menu_get_item_indent_y()));

		debug_menu_draw_rect(x0, y0, x1, y1, get_enabled() ? 0.7f : 0.1f, debug_real_argb_grey);
		debug_menu_draw_string(font_cache, point.x, point.y, x1, debug_menu_get_screen_bounds().y1, debug_real_argb_tv_magenta, m_name);
	}

	void c_debug_menu::render_caption(c_font_cache_base *font_cache, short_point_2d const &point)
	{
		if (!*get_caption())
			return;

		short x0 = point.x;
		short y0 = short(((point.y + get_title_height()) + get_num_items_to_render() * get_item_height()) + debug_menu_get_item_indent_y());
		short x1 = short(point.x + debug_menu_get_item_width());
		short y1 = short(((point.y + get_title_height()) + (get_num_items_to_render() + 1) * get_item_height()) - (2.0f * debug_menu_get_item_indent_y()));

		debug_menu_draw_rect(x0, y0, x1, y1, get_enabled() ? 0.7f : 0.1f, debug_real_argb_grey);
		debug_menu_draw_string(font_cache, point.x, short((point.y + get_title_height()) + get_num_items_to_render() * get_item_height()), x1, debug_menu_get_screen_bounds().y1, debug_real_argb_white, get_caption());
	}

	void c_debug_menu::render_global_caption(c_font_cache_base *font_cache, short_point_2d const &point)
	{
		short y = short((point.y + get_title_height()) + (get_num_items_to_render() + 1) * get_item_height());

		for (short caption_index = 0; caption_index < k_debug_menu_num_global_captions; caption_index++)
		{
			if (*debug_menu_get_caption(caption_index))
			{
				short x0 = point.x;
				short y0 = short(((point.y + get_title_height()) + ((caption_index + 1) + get_num_items_to_render()) * get_item_height()) + debug_menu_get_item_indent_y());
				short x1 = short(point.x + debug_menu_get_item_width());
				short y1 = short(((point.y + get_title_height()) + ((caption_index + 2) + get_num_items_to_render()) * get_item_height()) - (2.0f * debug_menu_get_item_indent_y()));

				debug_menu_draw_rect(x0, y0, x1, y1, get_enabled() ? 0.7f : 0.1f, debug_real_argb_grey);
				debug_menu_draw_string(font_cache, point.x, y, x1, debug_menu_get_screen_bounds().y1, debug_real_argb_tv_magenta, debug_menu_get_caption(caption_index));
			}

			debug_menu_set_caption(caption_index, "");
			y += get_item_height();
		}
	}

	void c_debug_menu::render_items(c_font_cache_base *font_cache, short_point_2d const &point, short start_index, short end_index)
	{
		for (short item_index = start_index; item_index <= end_index && item_index < get_num_items(); item_index++)
		{
			c_debug_menu_item *item = get_item(item_index);
			if (item->get_active())
			{
				short x0 = point.x;
				short y0 = short(((point.y + get_title_height()) + (item_index - start_index) * get_item_height()) + debug_menu_get_item_indent_y());
				short x1 = short(point.x + debug_menu_get_item_width());
				short y1 = short(((point.y + get_title_height()) + (item_index - start_index + 1) * get_item_height()) - (2.0f * debug_menu_get_item_indent_y()));

				debug_menu_draw_rect(x0, y0, x1, y1, get_enabled() ? 0.7f : 0.1f, item->get_background_color());
			}

			short_point_2d item_point = { point.x, short(point.y + (get_title_height() + (item_index - start_index) * get_item_height())) };
			item->render(font_cache, item_point);
		}
	}

	void c_debug_menu::try_left()
	{
		if (debug_menu_get_time() - m_last_left < get_menu_rate() || !get_num_items())
			return;

		m_last_left = debug_menu_get_time();
		notify_left();

		if (get_selection() < get_num_items())
			get_item(get_selection())->notify_left();
	}

	void c_debug_menu::try_right()
	{
		if (debug_menu_get_time() - m_last_right < get_menu_rate() || !get_num_items())
			return;

		m_last_right = debug_menu_get_time();
		notify_right();

		if (get_selection() < get_num_items())
			get_item(get_selection())->notify_right();
	}

	c_debug_menu::c_debug_menu(c_debug_menu *parent, char const *name) :
		m_num_items(0),
		m_selection(0),
		m_last_up(0),
		m_last_down(0),
		m_last_left(0),
		m_last_right(0),
		m_items(),
		m_name(nullptr),
		m_caption(nullptr),
		m_parent_ref(parent),
		m_enabled(true)
	{
		set_name(name ? name : "Menu???");
	}

	void c_debug_menu::clear()
	{
		// The items live in the menu allocator, so only their destructors run here.
		for (short item_index = 0; item_index < get_num_items(); item_index++)
		{
			if (c_debug_menu_item *item = m_items[item_index])
				item->~c_debug_menu_item();
			m_items[item_index] = nullptr;
		}
		set_num_items(0);
	}

	short c_debug_menu::get_num_items()
	{
		return m_num_items;
	}

	void c_debug_menu::set_num_items(short num_items)
	{
		m_num_items = num_items;
	}

	short c_debug_menu::get_selection()
	{
		return m_selection;
	}

	void c_debug_menu::set_selection(short selection)
	{
		m_selection = selection;
	}

	c_debug_menu_item *c_debug_menu::get_item(short item_index)
	{
		return m_items[item_index];
	}

	void c_debug_menu::add_item(c_debug_menu_item *item)
	{
		if (get_num_items() >= k_debug_menu_max_items)
		{
			debug_menu_print("debug menu: '%s' has more than %d items; '%s' was left out", get_name(), k_debug_menu_max_items, item->get_name());
			return;
		}
		m_items[get_num_items()] = item;
		set_num_items(get_num_items() + 1);
	}

	char const *c_debug_menu::get_name()
	{
		return m_name;
	}

	void c_debug_menu::set_name(char const *name)
	{
		long name_size = long(strlen(name)) + 1;
		m_name = static_cast<char *>(debug_menu_malloc(name_size));
		strcpy_s(m_name, name_size, name);
	}

	void c_debug_menu::set_caption(char const *caption)
	{
		long caption_size = long(strlen(caption)) + 1;
		m_caption = static_cast<char *>(debug_menu_malloc(caption_size));
		strcpy_s(m_caption, caption_size, caption);
	}

	c_debug_menu *c_debug_menu::get_parent()
	{
		return m_parent_ref;
	}

	bool c_debug_menu::get_enabled()
	{
		return m_enabled;
	}

	void c_debug_menu::set_enabled(bool enable)
	{
		m_enabled = enable;
	}

	short c_debug_menu::get_title_height()
	{
		return short(debug_menu_get_title_height());
	}

	short c_debug_menu::get_item_indent()
	{
		return short(debug_menu_get_item_indent_x());
	}

	short c_debug_menu::get_item_height()
	{
		return short(debug_menu_get_item_height());
	}

	/* ---------- c_debug_menu_scroll */

	void c_debug_menu_scroll::update()
	{
		c_debug_menu::update();

		short total = get_num_items() > get_num_visible() ? get_num_items() : get_num_visible();
		if (get_selection() + 1 >= get_first() + get_num_visible())
		{
			if (get_first() + 1 >= total - get_num_visible())
				set_first(total - get_num_visible());
			else
				set_first(get_first() + 1);
		}

		if (get_selection() - 1 < get_first())
			set_first(get_first() - 1 <= 0 ? 0 : get_first() - 1);
	}

	void c_debug_menu_scroll::render(c_font_cache_base *font_cache, short_point_2d const &position)
	{
		render_background(font_cache, position);
		render_title(font_cache, position);
		render_caption(font_cache, position);
		render_global_caption(font_cache, position);
		if (get_num_visible() > 0)
			render_items(font_cache, position, get_first(), get_first() + get_num_visible() - 1);

		short_rectangle2d screen = debug_menu_get_screen_bounds();
		if (get_first() > 0)
		{
			short y = position.y + get_title_height();
			debug_menu_draw_string(font_cache, position.x, y, screen.x1, screen.y1, debug_real_argb_tv_magenta, "^");
			debug_menu_draw_string(font_cache, position.x, y + get_item_height(), screen.x1, screen.y1, debug_real_argb_tv_magenta, "|");
		}

		if (get_num_items() - get_first() > get_num_visible())
		{
			short y = (position.y + get_title_height()) + (get_num_visible() - 2) * get_item_height();
			debug_menu_draw_string(font_cache, position.x, y, screen.x1, screen.y1, debug_real_argb_tv_magenta, "|");
			debug_menu_draw_string(font_cache, position.x, y + get_item_height(), screen.x1, screen.y1, debug_real_argb_tv_magenta, "v");
		}
	}

	void c_debug_menu_scroll::open()
	{
		c_debug_menu::open();
		set_first(0);
	}

	long c_debug_menu_scroll::get_num_items_to_render()
	{
		return get_num_items() <= get_num_visible() ? get_num_items() : get_num_visible();
	}

	c_debug_menu_scroll::c_debug_menu_scroll(c_debug_menu *parent, short num_visible, char const *name) :
		c_debug_menu(parent, name),
		m_num_visible(num_visible),
		m_first(0)
	{
	}

	short c_debug_menu_scroll::get_num_visible()
	{
		return m_num_visible;
	}

	short c_debug_menu_scroll::get_first()
	{
		return m_first;
	}

	void c_debug_menu_scroll::set_num_visible(short num_visible)
	{
		m_num_visible = num_visible;
	}

	void c_debug_menu_scroll::set_first(short first)
	{
		m_first = first < 0 ? 0 : first;
	}

	/* ---------- c_debug_menu_zone_sets */

	void c_debug_menu_zone_sets::notify_selected(short selected_value)
	{
		if (selected_value >= 0 && selected_value < zone_set_count())
			main_switch_zone_set(selected_value);
	}

	void c_debug_menu_zone_sets::open()
	{
		c_debug_menu_scroll::open();
		update_caption();
	}

	void c_debug_menu_zone_sets::notify_up()
	{
		c_debug_menu::notify_up();
		update_caption();
	}

	void c_debug_menu_zone_sets::notify_down()
	{
		c_debug_menu::notify_down();
		update_caption();
	}

	c_debug_menu_zone_sets::c_debug_menu_zone_sets(c_debug_menu *parent, short num_visible, char const *name) :
		c_debug_menu_scroll(parent, num_visible, name)
	{
		auto strings = Blam::Cache::StringIDCache::GetCurrent();
		for (long index = 0; index < zone_set_count(); index++)
		{
			char const *zone_set_name = strings ? strings->GetString(*reinterpret_cast<unsigned long *>(zone_set_get(index))) : nullptr;
			add_item(DEBUG_MENU_MALLOC(c_debug_menu_item_numbered, this, zone_set_name ? zone_set_name : "zone set", nullptr));
		}
	}

	void c_debug_menu_zone_sets::update_caption()
	{
		char caption[64] = "";
		if (get_selection() >= 0 && get_selection() < zone_set_count())
			sprintf_s(caption, "bsp zone flags 0x%08lX", *reinterpret_cast<unsigned long *>(zone_set_get(get_selection()) + 0xC));
		set_caption(caption);
	}
}
