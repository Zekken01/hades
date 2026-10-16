#pragma once

// Ported from ManagedDonkey (game/source/interface/debug_menu). The classes keep their
// names and behaviour; input, drawing, values and commands go through the adapters in
// debug_menu_main.cpp and debug_menu_commands.cpp instead of the game's stripped
// debug code.

#include "Blam/math/color_definitions.hpp"
#include "Blam/math/integer_math_definitions.hpp"

#include <new>

struct c_font_cache_base;

namespace DebugMenu
{
	class c_debug_menu;
	class c_debug_menu_item;

	enum
	{
		k_debug_menu_stack_size = 262144,
		k_debug_menu_num_global_captions = 8,
		k_debug_menu_max_items = 128, // Reach's limit; Halo 3 used 64
		k_debug_menu_visible_items = 26,
	};

	// Everything the menu builds comes from one bump allocator, released as a whole when
	// the menu is rebuilt, as in the original.
	void *debug_menu_malloc(long size);
	void debug_menu_free_all();
#define DEBUG_MENU_MALLOC(CLASS, ...) new (::DebugMenu::debug_menu_malloc(sizeof(CLASS))) CLASS(__VA_ARGS__)

	extern real_argb_color const *const debug_real_argb_black;
	extern real_argb_color const *const debug_real_argb_grey;
	extern real_argb_color const *const debug_real_argb_white;
	extern real_argb_color const *const debug_real_argb_tv_white;
	extern real_argb_color const *const debug_real_argb_tv_blue;
	extern real_argb_color const *const debug_real_argb_tv_magenta;
	extern real_argb_color const *const debug_real_argb_tv_orange;
	extern real_argb_color const *const debug_real_argb_tv_green;

	// Input, sampled once per frame while the menu has the input context.
	enum e_debug_menu_button
	{
		_debug_menu_button_up,
		_debug_menu_button_down,
		_debug_menu_button_left,
		_debug_menu_button_right,
		_debug_menu_button_select,
		_debug_menu_button_back,

		k_debug_menu_button_count
	};
	bool debug_menu_button_pressed(e_debug_menu_button button); // first frame only
	bool debug_menu_button_held(e_debug_menu_button button); // any frame it is down
	short debug_menu_shortcut_pressed(); // 0-9 and a-z jump to an item; -1 when none

	// Drawing.
	void debug_menu_draw_rect(short x0, short y0, short x1, short y1, float alpha, real_argb_color const *color);
	void debug_menu_draw_string(c_font_cache_base *font_cache, short x0, short y0, short x1, short y1, real_argb_color const *color, char const *text);
	short_rectangle2d debug_menu_get_screen_bounds();

	// Menu state.
	bool debug_menu_get_active();
	c_debug_menu *debug_menu_get_root();
	c_debug_menu *debug_menu_get_active_menu();
	void debug_menu_set_active_menu(c_debug_menu *active_menu, bool dont_open);
	void debug_menu_open();
	void debug_menu_close();
	void debug_menu_rebuild();
	void debug_menu_set_caption(short caption_index, char const *caption);
	char const *debug_menu_get_caption(short caption_index);
	long debug_menu_get_time();
	float debug_menu_get_item_margin();
	float debug_menu_get_item_width();
	float debug_menu_get_item_height();
	float debug_menu_get_title_height();
	float debug_menu_get_item_indent_x();
	float debug_menu_get_item_indent_y();

	// Commands and values (debug_menu_commands.cpp).
	void debug_menu_execute_command(char const *command);
	void debug_menu_print(char const *format, ...);

	enum e_debug_menu_value_type
	{
		k_debug_menu_value_none,
		k_debug_menu_value_bool,
		k_debug_menu_value_real,
		k_debug_menu_value_short,
		k_debug_menu_value_long,
	};

	// A script global the menu can show and change: game memory the release build still
	// has, or an ElDewrito variable with the same short name.
	class c_debug_menu_value
	{
	public:
		explicit c_debug_menu_value(char const *name);

		e_debug_menu_value_type get_type() const;
		double get() const;
		void set(double value);

	private:
		e_debug_menu_value_type m_type;
		void *m_address;
		void *m_command; // Modules::Command *
	};

	void debug_menu_parse(c_debug_menu *root_menu, char const *file_name);

	class c_debug_menu
	{
	public:
		virtual ~c_debug_menu();
		virtual void update();
		virtual void render(c_font_cache_base *font_cache, short_point_2d const &point);
		virtual void notify_selected(short selected_value);
		virtual void open();
		virtual char const *get_caption();
		virtual void notify_closed();
		virtual void notify_activated();

	protected:
		virtual long get_num_items_to_render();
		virtual void close(bool closed);
		virtual short get_value_width();
		virtual void notify_selection_closed();
		virtual void notify_selection_exited();
		virtual void notify_up();
		virtual void notify_down();
		virtual void notify_left();
		virtual void notify_right();

		bool is_active_menu();
		short get_menu_rate();
		short get_max_active_captions();

		void render_background(c_font_cache_base *font_cache, short_point_2d const &point);
		void render_title(c_font_cache_base *font_cache, short_point_2d const &point);
		void render_caption(c_font_cache_base *font_cache, short_point_2d const &point);
		void render_global_caption(c_font_cache_base *font_cache, short_point_2d const &point);
		void render_items(c_font_cache_base *font_cache, short_point_2d const &point, short start_index, short end_index);

	private:
		void try_left();
		void try_right();

	public:
		c_debug_menu(c_debug_menu *parent, char const *name);

		void clear();

		short get_num_items();
		void set_num_items(short num_items);

		short get_selection();
		void set_selection(short selection);

		c_debug_menu_item *get_item(short item_index);
		void add_item(c_debug_menu_item *item);

		char const *get_name();
		void set_name(char const *name);

		void set_caption(char const *caption);

		c_debug_menu *get_parent();

		bool get_enabled();
		void set_enabled(bool enable);

		short get_title_height();
		short get_item_indent();
		short get_item_height();

	protected:
		short m_num_items;
		short m_selection;
		long m_last_up;
		long m_last_down;
		long m_last_left;
		long m_last_right;
		c_debug_menu_item *m_items[k_debug_menu_max_items];
		char *m_name;
		char *m_caption;
		c_debug_menu *m_parent_ref;
		bool m_enabled;
	};

	class c_debug_menu_scroll :
		public c_debug_menu
	{
	public:
		virtual void update() override;
		virtual void render(c_font_cache_base *font_cache, short_point_2d const &point) override;
		virtual void open() override;

	protected:
		virtual long get_num_items_to_render() override;

	public:
		c_debug_menu_scroll(c_debug_menu *parent, short num_visible, char const *name);

	protected:
		short get_num_visible();
		short get_first();

	private:
		void set_num_visible(short num_visible);
		void set_first(short first);

	protected:
		short m_num_visible;
		short m_first;
	};

	class c_debug_menu_zone_sets :
		public c_debug_menu_scroll
	{
	public:
		virtual void notify_selected(short selected_value) override;
		virtual void open() override;

	protected:
		virtual void notify_up() override;
		virtual void notify_down() override;

	public:
		c_debug_menu_zone_sets(c_debug_menu *parent, short num_visible, char const *name);

	private:
		void update_caption();
	};

	class c_debug_menu_item
	{
	public:
		virtual ~c_debug_menu_item();
		virtual void update();
		virtual void render(c_font_cache_base *font_cache, short_point_2d const &position);
		virtual void notify_selected();
		virtual void open();
		virtual void notify_left();
		virtual void notify_right();
		virtual real_argb_color const *get_enabled_color();
		virtual real_argb_color const *get_background_color();

		c_debug_menu_item(c_debug_menu *menu, char const *name, c_debug_menu *child, bool active);

		char const *get_name();
		void set_name(char const *name);

		c_debug_menu *get_menu();
		c_debug_menu *get_child();

		bool get_active();
		void set_active(bool active);

		short get_index();
		bool get_is_selection();

	protected:
		char *m_name;
		c_debug_menu *m_menu_ref;
		c_debug_menu *m_child_ref;
		bool m_active;
	};

	class c_debug_menu_item_numbered :
		public c_debug_menu_item
	{
	public:
		virtual void render(c_font_cache_base *font_cache, short_point_2d const &position) override;

		c_debug_menu_item_numbered(c_debug_menu *menu, char const *name, c_debug_menu *child);

	protected:
		void render_number(c_font_cache_base *font_cache, short_point_2d const &position);
		short get_indent();
	};

	class c_debug_menu_item_hs_command :
		public c_debug_menu_item_numbered
	{
	public:
		virtual void notify_selected() override;
		virtual real_argb_color const *get_enabled_color() override;

		c_debug_menu_item_hs_command(c_debug_menu *menu, char const *name, char const *command);

	protected:
		char *m_command;
	};

	// A global variable item: bool, real, short or long, changed with left/right.
	class c_debug_menu_item_type :
		public c_debug_menu_item_numbered
	{
	public:
		virtual void render(c_font_cache_base *font_cache, short_point_2d const &position) override;
		virtual void notify_left() override;
		virtual void notify_right() override;

		c_debug_menu_item_type(c_debug_menu *menu, char const *name, char const *variable, float min, float max, float inc);

	protected:
		void to_string(char *buffer, long buffer_size);
		void render_value(c_font_cache_base *font_cache, short_point_2d const &position);
		void step(float direction);

		c_debug_menu_value m_value;
		float m_min;
		float m_max;
		float m_inc;
	};
}
