#include "DebugMenu/DebugMenu.hpp"
#include "DebugMenu/debug_menu.hpp"

#include "Blam/BlamInput.hpp"
#include "Blam/rasterizer/draw_string.hpp"
#include "Patches/Input.hpp"

#include <Windows.h>
#include <memory>
#include <string.h>
#include <string>

namespace Utils { namespace Version { std::string GetVersionString(); } }

namespace DebugMenu
{
	namespace
	{
		// Game functions the menu draws and switches with.
		auto const rasterizer_quad_screenspace = reinterpret_cast<void (*)(short_point_2d const (&)[4], unsigned long, void const *, short, bool)>(0x00A46DA0);
		auto const real_argb_color_to_pixel32 = reinterpret_cast<unsigned long (*)(real_argb_color const *)>(0x00521810);
		auto const interface_get_current_display_settings = reinterpret_cast<long (*)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *)>(0x00A9FAA0);
		auto const draw_string_get_glyph_scaling_for_display_settings = reinterpret_cast<float (*)()>(0x006582E0);
		auto const main_set_single_thread_request_flag = reinterpret_cast<void (*)(long, bool)>(0x00506EB0);
		auto const current_map_name = reinterpret_cast<char const *>(0x02391824);

		long const k_single_thread_for_user_request = 0;

		real_argb_color const instance_debug_real_argb_black = { 1.0f, 0.0f, 0.0f, 0.0f };
		real_argb_color const instance_debug_real_argb_grey = { 1.0f, 0.3f, 0.42f, 0.33f };
		real_argb_color const instance_debug_real_argb_white = { 1.0f, 0.9f, 0.9f, 0.8f };
		real_argb_color const instance_debug_real_argb_tv_white = { 1.0f, 0.8f, 0.8f, 0.75f };
		real_argb_color const instance_debug_real_argb_tv_blue = { 1.0f, 0.2f, 0.2f, 0.45f };
		real_argb_color const instance_debug_real_argb_tv_magenta = { 1.0f, 0.7f, 0.05f, 0.7f };
		real_argb_color const instance_debug_real_argb_tv_orange = { 1.0f, 1.0f, 0.5f, 0.0f };
		real_argb_color const instance_debug_real_argb_tv_green = { 1.0f, 0.05f, 0.65f, 0.05f };

		class c_main_menu :
			public c_debug_menu_scroll
		{
		public:
			c_main_menu(char const *name) :
				c_debug_menu_scroll(nullptr, k_debug_menu_visible_items, name)
			{
			}
		};

		struct s_debug_menu_globals
		{
			c_debug_menu *main_menu;
			c_debug_menu *active_menu;
			char captions[k_debug_menu_num_global_captions][128];
			bool rebuild_request;
			char built_for_map[64];

			// Input for the current frame.
			unsigned char button_ticks[k_debug_menu_button_count];
			short shortcut;
		};
		s_debug_menu_globals g_debug_menu_globals = {};

		// The menu allocator: one block, handed out in order and reset on rebuild.
		long g_debug_menu_stack[k_debug_menu_stack_size];
		long g_debug_menu_stack_count = 0;

		class c_debug_menu_input_context :
			public Patches::Input::InputContext
		{
		public:
			void Activated() override
			{
			}

			void Deactivated() override
			{
			}

			bool GameInputTick() override;

			bool UiInputTick() override
			{
				return debug_menu_get_active();
			}
		};

		unsigned char key_ticks(Blam::Input::KeyCode key)
		{
			return Blam::Input::GetKeyTicks(key, Blam::Input::eInputTypeUi);
		}

		// Ticks a controller UI action has been held, 0 when it is up or already handled.
		unsigned char action_ticks(Blam::Input::GameAction action)
		{
			Blam::Input::ActionState const *state = Blam::Input::GetActionState(action);
			return (state->Flags & Blam::Input::eActionStateFlagsHandled) ? 0 : state->Ticks;
		}

		unsigned char max_ticks(unsigned char a, unsigned char b)
		{
			return a > b ? a : b;
		}

		void debug_menu_sample_input()
		{
			using namespace Blam::Input;

			g_debug_menu_globals.button_ticks[_debug_menu_button_up] = max_ticks(key_ticks(eKeyCodeUp), action_ticks(eGameActionUiUp));
			g_debug_menu_globals.button_ticks[_debug_menu_button_down] = max_ticks(key_ticks(eKeyCodeDown), action_ticks(eGameActionUiDown));
			g_debug_menu_globals.button_ticks[_debug_menu_button_left] = max_ticks(key_ticks(eKeyCodeLeft), action_ticks(eGameActionUiLeft));
			g_debug_menu_globals.button_ticks[_debug_menu_button_right] = max_ticks(key_ticks(eKeyCodeRight), action_ticks(eGameActionUiRight));
			g_debug_menu_globals.button_ticks[_debug_menu_button_select] = max_ticks(max_ticks(key_ticks(eKeyCodeEnter), key_ticks(eKeyCodeNumpadEnter)), action_ticks(eGameActionUiA));
			g_debug_menu_globals.button_ticks[_debug_menu_button_back] = max_ticks(max_ticks(key_ticks(eKeyCodeEnd), key_ticks(eKeyCodeBack)), action_ticks(eGameActionUiB));

			// 1-9 and 0 pick the first ten items, a-z the next 26.
			static KeyCode const number_keys[] = { eKeyCode1, eKeyCode2, eKeyCode3, eKeyCode4, eKeyCode5, eKeyCode6, eKeyCode7, eKeyCode8, eKeyCode9, eKeyCode0 };
			static KeyCode const numpad_keys[] = { eKeyCodeNumpad1, eKeyCodeNumpad2, eKeyCodeNumpad3, eKeyCodeNumpad4, eKeyCodeNumpad5, eKeyCodeNumpad6, eKeyCodeNumpad7, eKeyCodeNumpad8, eKeyCodeNumpad9, eKeyCodeNumpad0 };
			static KeyCode const letter_keys[] =
			{
				eKeyCodeA, eKeyCodeB, eKeyCodeC, eKeyCodeD, eKeyCodeE, eKeyCodeF, eKeyCodeG, eKeyCodeH, eKeyCodeI, eKeyCodeJ, eKeyCodeK, eKeyCodeL, eKeyCodeM,
				eKeyCodeN, eKeyCodeO, eKeyCodeP, eKeyCodeQ, eKeyCodeR, eKeyCodeS, eKeyCodeT, eKeyCodeU, eKeyCodeV, eKeyCodeW, eKeyCodeX, eKeyCodeY, eKeyCodeZ,
			};
			g_debug_menu_globals.shortcut = -1;
			for (short i = 0; i < 10 && g_debug_menu_globals.shortcut == -1; i++)
			{
				if (key_ticks(number_keys[i]) == 1 || key_ticks(numpad_keys[i]) == 1)
					g_debug_menu_globals.shortcut = i;
			}
			for (short i = 0; i < 26 && g_debug_menu_globals.shortcut == -1; i++)
			{
				if (key_ticks(letter_keys[i]) == 1)
					g_debug_menu_globals.shortcut = 10 + i;
			}
		}

		// Insert, or Back+Start on a controller.
		bool debug_menu_toggle_pressed()
		{
			using namespace Blam::Input;

			if (key_ticks(eKeyCodeInsert) == 1)
				return true;

			unsigned char back = action_ticks(eGameActionUiSelect);
			unsigned char start = action_ticks(eGameActionUiStart);
			return (back == 1 && start > 0) || (start == 1 && back > 0);
		}

		void debug_menu_build()
		{
			debug_menu_free_all();
			memset(g_debug_menu_globals.captions, 0, sizeof(g_debug_menu_globals.captions));

			static std::string title;
			title = "ElDewrito " + Utils::Version::GetVersionString();
			g_debug_menu_globals.main_menu = DEBUG_MENU_MALLOC(c_main_menu, title.c_str());
			g_debug_menu_globals.active_menu = nullptr;

			debug_menu_parse(g_debug_menu_globals.main_menu, "debug_menu_init.txt");
			debug_menu_parse(g_debug_menu_globals.main_menu, "debug_menu_user_init.txt");

			strcpy_s(g_debug_menu_globals.built_for_map, current_map_name);
			if (g_debug_menu_globals.main_menu->get_num_items() == 0)
				debug_menu_print("debug menu: debug_menu_init.txt is missing or empty; put it next to eldorado.exe");
		}

		bool c_debug_menu_input_context::GameInputTick()
		{
			if (!debug_menu_get_active())
				return false;

			debug_menu_sample_input();

			if (debug_menu_toggle_pressed())
			{
				debug_menu_set_active_menu(nullptr, false);
				return false;
			}

			if (g_debug_menu_globals.rebuild_request)
			{
				g_debug_menu_globals.rebuild_request = false;
				debug_menu_set_active_menu(nullptr, false);
				debug_menu_build();
				debug_menu_open();
			}

			debug_menu_get_active_menu()->update();
			return debug_menu_get_active();
		}

		void OnGameInputUpdated()
		{
			if (!debug_menu_get_active() && debug_menu_toggle_pressed())
			{
				debug_menu_open();
				if (debug_menu_get_active())
					Patches::Input::PushContext(std::make_shared<c_debug_menu_input_context>());
			}
		}
	}

	real_argb_color const *const debug_real_argb_black = &instance_debug_real_argb_black;
	real_argb_color const *const debug_real_argb_grey = &instance_debug_real_argb_grey;
	real_argb_color const *const debug_real_argb_white = &instance_debug_real_argb_white;
	real_argb_color const *const debug_real_argb_tv_white = &instance_debug_real_argb_tv_white;
	real_argb_color const *const debug_real_argb_tv_blue = &instance_debug_real_argb_tv_blue;
	real_argb_color const *const debug_real_argb_tv_magenta = &instance_debug_real_argb_tv_magenta;
	real_argb_color const *const debug_real_argb_tv_orange = &instance_debug_real_argb_tv_orange;
	real_argb_color const *const debug_real_argb_tv_green = &instance_debug_real_argb_tv_green;

	void Initialize()
	{
		Patches::Input::RegisterDefaultInputHandler(OnGameInputUpdated);
	}

	void Render()
	{
		if (!debug_menu_get_active())
			return;

		c_font_cache_mt_safe font_cache;
		short_point_2d position = { 180, 60 };
		debug_menu_get_active_menu()->render(&font_cache, position);
	}

	void *debug_menu_malloc(long size)
	{
		long size_in_count = (size + 3) >> 2;
		if (g_debug_menu_stack_count + size_in_count > k_debug_menu_stack_size)
		{
			// Out of menu memory: a bigger debug_menu_init.txt than the original's budget.
			static long overflow[64];
			return overflow;
		}
		void *result = &g_debug_menu_stack[g_debug_menu_stack_count];
		g_debug_menu_stack_count += size_in_count;
		memset(result, 0, size_in_count * sizeof(long));
		return result;
	}

	void debug_menu_free_all()
	{
		g_debug_menu_stack_count = 0;
		g_debug_menu_globals.main_menu = nullptr;
		g_debug_menu_globals.active_menu = nullptr;
	}

	bool debug_menu_button_pressed(e_debug_menu_button button)
	{
		return g_debug_menu_globals.button_ticks[button] == 1;
	}

	bool debug_menu_button_held(e_debug_menu_button button)
	{
		return g_debug_menu_globals.button_ticks[button] > 0;
	}

	short debug_menu_shortcut_pressed()
	{
		return g_debug_menu_globals.shortcut;
	}

	void debug_menu_draw_rect(short x0, short y0, short x1, short y1, float alpha, real_argb_color const *color)
	{
		short_point_2d points[4] = { { x0, y1 }, { x1, y1 }, { x1, y0 }, { x0, y0 } };
		real_argb_color faded = *color;
		faded.alpha = alpha;
		rasterizer_quad_screenspace(points, real_argb_color_to_pixel32(&faded), nullptr, 0, false);
	}

	void debug_menu_draw_string(c_font_cache_base *font_cache, short x0, short y0, short x1, short y1, real_argb_color const *color, char const *text)
	{
		c_rasterizer_draw_string draw_string;
		short_rectangle2d bounds;
		bounds.x0 = x0;
		bounds.y0 = y0;
		bounds.x1 = x1;
		bounds.y1 = y1;
		draw_string.set_bounds(bounds);
		draw_string.set_color(*color);
		draw_string.draw(font_cache, text);
	}

	short_rectangle2d debug_menu_get_screen_bounds()
	{
		short_rectangle2d bounds = {};
		interface_get_current_display_settings(nullptr, nullptr, nullptr, &bounds);
		return bounds;
	}

	bool debug_menu_get_active()
	{
		return g_debug_menu_globals.active_menu != nullptr;
	}

	c_debug_menu *debug_menu_get_root()
	{
		return g_debug_menu_globals.main_menu;
	}

	c_debug_menu *debug_menu_get_active_menu()
	{
		return g_debug_menu_globals.active_menu;
	}

	void debug_menu_set_active_menu(c_debug_menu *active_menu, bool dont_open)
	{
		c_debug_menu *current_active_menu = g_debug_menu_globals.active_menu;

		bool menu_is_parent = current_active_menu && active_menu && current_active_menu->get_parent() == active_menu;
		g_debug_menu_globals.active_menu = active_menu;

		if (active_menu)
		{
			if (!menu_is_parent && !dont_open)
				active_menu->open();
			active_menu->notify_activated();
		}
		else if (current_active_menu)
		{
			current_active_menu->notify_closed();
		}

		// Rendering and the game's update share the menu state, so the game runs single
		// threaded while the menu is open, as in ManagedDonkey.
		main_set_single_thread_request_flag(k_single_thread_for_user_request, active_menu != nullptr);

		for (short caption_index = 0; caption_index < k_debug_menu_num_global_captions; caption_index++)
			debug_menu_set_caption(caption_index, "");
	}

	void debug_menu_open()
	{
		// The zone-set menu lists the loaded scenario, so the menu is rebuilt for each map.
		if (!debug_menu_get_root() || strcmp(g_debug_menu_globals.built_for_map, current_map_name) != 0)
			debug_menu_build();

		if (debug_menu_get_root() && !debug_menu_get_active())
			debug_menu_set_active_menu(debug_menu_get_root(), false);
	}

	void debug_menu_close()
	{
		if (debug_menu_get_active())
			debug_menu_set_active_menu(nullptr, false);
	}

	void debug_menu_rebuild()
	{
		g_debug_menu_globals.rebuild_request = true;
	}

	void debug_menu_set_caption(short caption_index, char const *caption)
	{
		if (caption_index >= 0 && caption_index < k_debug_menu_num_global_captions)
			strncpy_s(g_debug_menu_globals.captions[caption_index], caption, _TRUNCATE);
	}

	char const *debug_menu_get_caption(short caption_index)
	{
		return caption_index >= 0 && caption_index < k_debug_menu_num_global_captions ? g_debug_menu_globals.captions[caption_index] : "";
	}

	long debug_menu_get_time()
	{
		// 30 ticks a second, as in the original.
		return long(((GetTickCount64() * 30.0) / 1000.0) + 0.5);
	}

	float debug_menu_get_item_margin()
	{
		return draw_string_get_glyph_scaling_for_display_settings() * 10.0f;
	}

	float debug_menu_get_item_width()
	{
		return draw_string_get_glyph_scaling_for_display_settings() * 650.0f;
	}

	float debug_menu_get_item_height()
	{
		return draw_string_get_glyph_scaling_for_display_settings() * 20.0f;
	}

	float debug_menu_get_title_height()
	{
		return draw_string_get_glyph_scaling_for_display_settings() * 20.0f;
	}

	float debug_menu_get_item_indent_x()
	{
		return draw_string_get_glyph_scaling_for_display_settings() * 40.0f;
	}

	float debug_menu_get_item_indent_y()
	{
		return draw_string_get_glyph_scaling_for_display_settings() * 2.0f;
	}
}
