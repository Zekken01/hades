#include "DebugMenu/debug_menu.hpp"

#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The parser for debug_menu_init.txt, ported from ManagedDonkey's
// debug_menu_parse.cpp. The file is a loose tag format:
//   <menu name = "Cheats">
//       <item type = command name = "Ghost" variable = "drop objects\\vehicles\\ghost\\ghost.vehicle">
//       <item type = global name = "deathless player" variable = "cheat_deathless_player">
//   </menu>
// Strings take backslash escapes; numbers set min, max and inc on global items.

namespace DebugMenu
{
	namespace
	{
		enum e_parse_state
		{
			_parse_state_none = 0,
			_parse_state_reading_tag,
			_parse_state_reading_open_tag,
			_parse_state_reading_close_tag,
			_parse_state_reading_property,
			_parse_state_reading_property_found_equals,
			_parse_state_reading_menu_items,
			_parse_state_reading_string,
			_parse_state_reading_escape_character,
			_parse_state_reading_number,

			k_parse_state_count
		};

		struct s_parse_stack
		{
			e_parse_state states[k_parse_state_count];
			long count = 0;

			void push_back(e_parse_state state)
			{
				if (count < k_parse_state_count)
					states[count++] = state;
			}
			void pop()
			{
				if (count > 0)
					count--;
			}
			e_parse_state top() const
			{
				return count > 0 ? states[count - 1] : _parse_state_none;
			}
		};

		enum e_advance_type
		{
			_advance_type_process_token = 0,
			_advance_type_process_distance,
			_advance_type_process_nothing,
		};

		enum e_tokens
		{
			_token_none = 0,
			_token_min,
			_token_max,
			_token_inc,
			_token_menu,
			_token_zone_set_menu,
			_token_create_zone_set_menu, // Halo 3: ODST; built as a plain menu here
			_token_error_geometry_settings_menu, // Halo 3: ODST; built as a plain menu here
			_token_item,
			_token_caption,
			_token_name,
			_token_variable,
			_token_color,
			_token_type,
			_token_global,
			_token_command,
			_token_eol_0, // CR LF
			_token_eol_1, // LF CR
			_token_eol_2, // CR
			_token_eol_3, // LF

			k_token_count
		};

		char const *const g_token_names[k_token_count] =
		{
			"none", "min", "max", "inc", "menu", "zone_set_menu", "create_zone_set_menu", "error_geometry_settings_menu",
			"item", "caption", "name", "variable", "color", "type", "global", "command", "\r\n", "\n\r", "\r", "\n",
		};

		enum e_property
		{
			_property_none = 0,
			_property_type,
			_property_color,
			_property_caption,
			_property_name,
			_property_variable,
			_property_min,
			_property_max,
			_property_inc,
		};

		enum e_property_owners
		{
			_property_owner_none = 0,
			_property_owner_item,
			_property_owner_menu,
			_property_owner_zone_set_menu,
			_property_owner_create_zone_set_menu,
			_property_owner_error_geometry_settings_menu,
		};

		enum e_item_types
		{
			_item_type_none = 0,
			_item_type_hs_variable_global,
			_item_type_command,
		};

		struct s_parser_state
		{
			enum
			{
				k_string_length = 2048
			};

			e_property m_current_property_type;
			e_property_owners m_current_property_owner;

			char m_string_buffer[k_string_length];
			short m_string_buffer_index;

			char m_number_buffer[k_string_length];
			short m_number_buffer_index;

			bool m_has_name;
			char m_name[k_string_length];

			bool m_has_color;
			char m_color[k_string_length];

			bool m_has_variable;
			char m_variable[k_string_length];

			bool m_has_caption;
			char m_caption[k_string_length];

			bool m_has_min;
			float m_min;

			bool m_has_max;
			float m_max;

			bool m_has_inc;
			float m_inc;

			bool m_has_item_type;
			e_item_types m_item_type;

			void reset()
			{
				m_has_name = false;
				m_has_color = false;
				m_has_variable = false;
				m_has_caption = false;
				m_has_min = false;
				m_has_max = false;
				m_has_inc = false;
				m_has_item_type = false;
				m_item_type = _item_type_none;
				m_current_property_type = _property_none;
				m_current_property_owner = _property_owner_none;
			}
		};

		s_parser_state g_parser_state;

		void debug_menu_display_error(char const *error_text)
		{
			debug_menu_print("debug menu: debug_menu_init.txt %s", error_text);
		}

		void debug_menu_look_ahead_read_token(FILE *file, long file_char, char *token_buffer, long token_buffer_count)
		{
			long position = ftell(file);
			*token_buffer = char(file_char);
			long characters_read = long(fread(token_buffer + 1, sizeof(char), token_buffer_count - 1, file));
			fseek(file, position, SEEK_SET);

			long token_buffer_end = characters_read + 1;
			if (token_buffer_end > token_buffer_count - 1)
				token_buffer_end = token_buffer_count - 1;
			token_buffer[token_buffer_end] = 0;
		}

		// Whether source starts with find, ignoring case.
		bool string_starts_with_case_insensitive(char const *source, char const *find)
		{
			for (; *find; source++, find++)
			{
				if (!*source || tolower(*source) != tolower(*find))
					return false;
			}
			return true;
		}

		void debug_menu_store_number_property(s_parse_stack *parse_stack)
		{
			parse_stack->pop(); // reading number
			parse_stack->pop(); // found equals
			parse_stack->pop(); // reading property

			g_parser_state.m_number_buffer[g_parser_state.m_number_buffer_index] = 0;
			float value = float(atof(g_parser_state.m_number_buffer));
			switch (g_parser_state.m_current_property_type)
			{
			case _property_min:
				g_parser_state.m_has_min = true;
				g_parser_state.m_min = value;
				break;
			case _property_max:
				g_parser_state.m_has_max = true;
				g_parser_state.m_max = value;
				break;
			case _property_inc:
				g_parser_state.m_has_inc = true;
				g_parser_state.m_inc = value;
				break;
			}
			g_parser_state.m_current_property_type = _property_none;
		}

		void debug_menu_store_string_property(s_parse_stack *parse_stack)
		{
			parse_stack->pop(); // reading string
			parse_stack->pop(); // found equals
			parse_stack->pop(); // reading property

			g_parser_state.m_string_buffer[g_parser_state.m_string_buffer_index] = 0;
			char *destination = nullptr;
			switch (g_parser_state.m_current_property_type)
			{
			case _property_color:
				g_parser_state.m_has_color = true;
				destination = g_parser_state.m_color;
				break;
			case _property_caption:
				g_parser_state.m_has_caption = true;
				destination = g_parser_state.m_caption;
				break;
			case _property_name:
				g_parser_state.m_has_name = true;
				destination = g_parser_state.m_name;
				break;
			case _property_variable:
				g_parser_state.m_has_variable = true;
				destination = g_parser_state.m_variable;
				break;
			}
			if (destination)
				strcpy_s(destination, s_parser_state::k_string_length, g_parser_state.m_string_buffer);
			g_parser_state.m_current_property_type = _property_none;
		}

		char const *debug_menu_build_item_hs_variable_global(c_debug_menu *menu, char *error_buffer, long error_buffer_size)
		{
			if (!g_parser_state.m_has_variable)
			{
				sprintf_s(error_buffer, error_buffer_size, "global variable debug menu items must define a variable");
				return error_buffer;
			}

			char const *name = g_parser_state.m_has_name ? g_parser_state.m_name : g_parser_state.m_variable;

			c_debug_menu_item *item = nullptr;
			switch (c_debug_menu_value(g_parser_state.m_variable).get_type())
			{
			case k_debug_menu_value_bool:
				item = DEBUG_MENU_MALLOC(c_debug_menu_item_type, menu, name, g_parser_state.m_variable, 0.0f, 1.0f, 1.0f);
				break;
			case k_debug_menu_value_real:
				item = DEBUG_MENU_MALLOC(c_debug_menu_item_type, menu, name, g_parser_state.m_variable,
					g_parser_state.m_has_min ? g_parser_state.m_min : -FLT_MAX,
					g_parser_state.m_has_max ? g_parser_state.m_max : FLT_MAX,
					g_parser_state.m_has_inc ? g_parser_state.m_inc : 0.1f);
				break;
			case k_debug_menu_value_short:
				item = DEBUG_MENU_MALLOC(c_debug_menu_item_type, menu, name, g_parser_state.m_variable,
					g_parser_state.m_has_min ? g_parser_state.m_min : float(SHRT_MIN + 1),
					g_parser_state.m_has_max ? g_parser_state.m_max : float(SHRT_MAX - 1),
					g_parser_state.m_has_inc ? g_parser_state.m_inc : 1.0f);
				break;
			case k_debug_menu_value_long:
				item = DEBUG_MENU_MALLOC(c_debug_menu_item_type, menu, name, g_parser_state.m_variable,
					g_parser_state.m_has_min ? g_parser_state.m_min : float(LONG_MIN + 1),
					g_parser_state.m_has_max ? g_parser_state.m_max : float(LONG_MAX - 1),
					g_parser_state.m_has_inc ? g_parser_state.m_inc : 1.0f);
				break;
			}

			if (!item)
			{
				// Not a global this build can reach: shown greyed out, as in ManagedDonkey.
				char undefined_name[1024];
				sprintf_s(undefined_name, "UNDEFINED: %s", g_parser_state.m_variable);
				item = DEBUG_MENU_MALLOC(c_debug_menu_item, menu, undefined_name, nullptr, false);
			}

			menu->add_item(item);
			return nullptr;
		}

		char const *debug_menu_build_item_command(c_debug_menu *menu, char *error_buffer, long error_buffer_size)
		{
			if (!g_parser_state.m_has_variable)
			{
				sprintf_s(error_buffer, error_buffer_size, "command menu items must define a variable");
				return error_buffer;
			}

			char const *name = g_parser_state.m_has_name ? g_parser_state.m_name : g_parser_state.m_variable;
			menu->add_item(DEBUG_MENU_MALLOC(c_debug_menu_item_hs_command, menu, name, g_parser_state.m_variable));
			return nullptr;
		}

		char const *debug_menu_build_item(c_debug_menu *menu, char *error_buffer, long error_buffer_size)
		{
			if (!g_parser_state.m_has_item_type)
			{
				sprintf_s(error_buffer, error_buffer_size, "menu items must supply a type");
				return error_buffer;
			}

			switch (g_parser_state.m_item_type)
			{
			case _item_type_hs_variable_global:
				return debug_menu_build_item_hs_variable_global(menu, error_buffer, error_buffer_size);
			case _item_type_command:
				return debug_menu_build_item_command(menu, error_buffer, error_buffer_size);
			}
			return nullptr;
		}

		c_debug_menu *debug_menu_build_menu(e_property_owners property_owner, c_debug_menu *menu)
		{
			char const *name = g_parser_state.m_has_name ? g_parser_state.m_name : "untitled menu";
			char const *caption = g_parser_state.m_has_caption ? g_parser_state.m_caption : "";

			for (long i = 0; i < s_parser_state::k_string_length && g_parser_state.m_name[i]; i++)
			{
				if (g_parser_state.m_name[i] == '\t')
					g_parser_state.m_name[i] = ',';
			}

			c_debug_menu *child = nullptr;
			if (property_owner == _property_owner_zone_set_menu)
				child = DEBUG_MENU_MALLOC(c_debug_menu_zone_sets, menu, k_debug_menu_visible_items, name);
			else
				child = DEBUG_MENU_MALLOC(c_debug_menu_scroll, menu, k_debug_menu_visible_items, name);

			child->set_caption(caption);
			menu->add_item(DEBUG_MENU_MALLOC(c_debug_menu_item_numbered, menu, name, child));
			return child;
		}

#define PARSER_ASSERT_WITH_MESSAGE(STATEMENT, MESSAGE) \
	if (!(STATEMENT)) \
	{ \
		sprintf_s(error_buffer, error_buffer_length, "line %ld: %s", *line_count, MESSAGE); \
		parse_error = error_buffer; \
		debug_menu_display_error(error_buffer); \
		continue; \
	} else
#define PARSER_ASSERT(STATEMENT) PARSER_ASSERT_WITH_MESSAGE(STATEMENT, #STATEMENT)

		char const *debug_menu_build_recursive(FILE *menu_file, long &file_char, c_debug_menu *menu, long *line_count, char *error_buffer, long error_buffer_length)
		{
			char const *parse_error = nullptr;

			s_parse_stack parse_stack;
			parse_stack.push_back(_parse_state_none);
			g_parser_state.reset();

			while (file_char && file_char != EOF && !parse_error)
			{
				long advance_distance = 0;
				e_advance_type advance_process_type = _advance_type_process_token;

				if (parse_stack.top() == _parse_state_reading_number)
				{
					if ((file_char >= '0' && file_char <= '9') || file_char == '.')
					{
						if (g_parser_state.m_number_buffer_index < s_parser_state::k_string_length - 1)
						{
							g_parser_state.m_number_buffer[g_parser_state.m_number_buffer_index++] = char(file_char);
							g_parser_state.m_number_buffer[g_parser_state.m_number_buffer_index] = 0;
						}
						advance_distance = 1;
						advance_process_type = _advance_type_process_distance;
					}
					else
					{
						// The character after the number is read again in the next state.
						debug_menu_store_number_property(&parse_stack);
						continue;
					}
				}
				else if (parse_stack.top() == _parse_state_reading_escape_character)
				{
					parse_stack.pop();
					PARSER_ASSERT(parse_stack.top() == _parse_state_reading_string)
					{
						if (g_parser_state.m_string_buffer_index < s_parser_state::k_string_length - 1)
						{
							g_parser_state.m_string_buffer[g_parser_state.m_string_buffer_index++] = char(file_char);
							g_parser_state.m_string_buffer[g_parser_state.m_string_buffer_index] = 0;
						}
						advance_distance = 1;
						advance_process_type = _advance_type_process_distance;
					}
				}
				else if (parse_stack.top() == _parse_state_reading_string && file_char != '"')
				{
					if (file_char == '\\')
					{
						parse_stack.push_back(_parse_state_reading_escape_character);
					}
					else if (g_parser_state.m_string_buffer_index < s_parser_state::k_string_length - 1)
					{
						if (file_char == '\n')
							++*line_count;
						g_parser_state.m_string_buffer[g_parser_state.m_string_buffer_index++] = char(file_char);
						g_parser_state.m_string_buffer[g_parser_state.m_string_buffer_index] = 0;
					}
					advance_distance = 1;
					advance_process_type = _advance_type_process_distance;
				}
				else if ((file_char >= '0' && file_char <= '9') || file_char == '-' || file_char == '.')
				{
					PARSER_ASSERT_WITH_MESSAGE(parse_stack.top() == _parse_state_reading_property_found_equals, "loose number not assigned to a property")
					{
						parse_stack.push_back(_parse_state_reading_number);
						g_parser_state.m_number_buffer_index = 0;
						g_parser_state.m_number_buffer[g_parser_state.m_number_buffer_index++] = char(file_char);
						g_parser_state.m_number_buffer[g_parser_state.m_number_buffer_index] = 0;
						advance_distance = 1;
						advance_process_type = _advance_type_process_distance;
					}
				}
				else
				{
					switch (file_char)
					{
					case ' ':
					case '\t':
					case 0xCD:
						advance_distance = 1;
						advance_process_type = _advance_type_process_distance;
						break;

					case '"':
					{
						e_parse_state state = parse_stack.top();
						if (state == _parse_state_reading_property_found_equals)
						{
							g_parser_state.m_string_buffer_index = 0;
							g_parser_state.m_string_buffer[0] = 0;
							parse_stack.push_back(_parse_state_reading_string);
						}
						else
						{
							PARSER_ASSERT_WITH_MESSAGE(state == _parse_state_reading_string, "unexpected symbol \"")
							{
								debug_menu_store_string_property(&parse_stack);
							}
						}
						advance_distance = 1;
						advance_process_type = _advance_type_process_distance;
					}
					break;

					case '/':
						advance_distance = 1;
						advance_process_type = _advance_type_process_distance;
						PARSER_ASSERT_WITH_MESSAGE(parse_stack.top() == _parse_state_reading_tag, "unexpected symbol /")
						{
							parse_stack.push_back(_parse_state_reading_close_tag);
						}
						break;

					case '<':
						advance_distance = 1;
						advance_process_type = _advance_type_process_distance;
						PARSER_ASSERT_WITH_MESSAGE(parse_stack.top() == _parse_state_none, "unexpected symbol <")
						{
							parse_stack.push_back(_parse_state_reading_tag);
							g_parser_state.reset();
						}
						break;

					case '=':
						advance_distance = 1;
						advance_process_type = _advance_type_process_distance;
						PARSER_ASSERT_WITH_MESSAGE(parse_stack.top() == _parse_state_reading_property, "= sign expected")
						{
							parse_stack.push_back(_parse_state_reading_property_found_equals);
						}
						break;

					case '>':
						advance_distance = 1;
						advance_process_type = _advance_type_process_distance;

						if (parse_stack.top() == _parse_state_reading_open_tag)
						{
							parse_stack.pop();
							PARSER_ASSERT(parse_stack.top() == _parse_state_reading_tag)
							{
								parse_stack.pop();
								if (g_parser_state.m_current_property_owner == _property_owner_item)
								{
									char build_error[1024];
									char const *error = debug_menu_build_item(menu, build_error, sizeof(build_error));
									if (error)
										debug_menu_display_error(error);
								}
								else
								{
									c_debug_menu *built_menu = debug_menu_build_menu(g_parser_state.m_current_property_owner, menu);
									advance_process_type = _advance_type_process_nothing;
									file_char = fgetc(menu_file);
									char const *recursive_error = debug_menu_build_recursive(menu_file, file_char, built_menu, line_count, error_buffer, error_buffer_length);
									PARSER_ASSERT_WITH_MESSAGE(!recursive_error, recursive_error);
								}
							}
							break;
						}

						PARSER_ASSERT_WITH_MESSAGE(parse_stack.top() == _parse_state_reading_close_tag, "unexpected symbol >")
						{
							parse_stack.pop();
							file_char = fgetc(menu_file);
							return nullptr;
						}
						break;
					}
				}

				if (advance_process_type == _advance_type_process_token)
				{
					char token_buffer[64];
					debug_menu_look_ahead_read_token(menu_file, file_char, token_buffer, sizeof(token_buffer));

					// The longest name that fits wins, so "zone_set_menu" is not read as "z...".
					e_tokens token = _token_none;
					for (long i = 1; i < k_token_count; i++)
					{
						if (string_starts_with_case_insensitive(token_buffer, g_token_names[i])
							&& (token == _token_none || strlen(g_token_names[i]) > strlen(g_token_names[token])))
						{
							token = e_tokens(i);
						}
					}
					if (token != _token_none)
					{
						advance_distance = long(strlen(g_token_names[token]));
						advance_process_type = _advance_type_process_distance;
					}

					switch (token)
					{
					case _token_min:
					case _token_max:
					case _token_inc:
					case _token_caption:
					case _token_name:
					case _token_variable:
					case _token_color:
					case _token_type:
					{
						switch (token)
						{
						case _token_min: g_parser_state.m_current_property_type = _property_min; break;
						case _token_max: g_parser_state.m_current_property_type = _property_max; break;
						case _token_inc: g_parser_state.m_current_property_type = _property_inc; break;
						case _token_caption: g_parser_state.m_current_property_type = _property_caption; break;
						case _token_name: g_parser_state.m_current_property_type = _property_name; break;
						case _token_variable: g_parser_state.m_current_property_type = _property_variable; break;
						case _token_color: g_parser_state.m_current_property_type = _property_color; break;
						case _token_type: g_parser_state.m_current_property_type = _property_type; break;
						}
						PARSER_ASSERT(parse_stack.top() == _parse_state_reading_open_tag)
						{
							parse_stack.push_back(_parse_state_reading_property);
						}
					}
					break;

					case _token_menu:
					case _token_zone_set_menu:
					case _token_create_zone_set_menu:
					case _token_error_geometry_settings_menu:
					case _token_item:
					{
						if (token != _token_item && parse_stack.top() == _parse_state_reading_close_tag)
							break;

						switch (token)
						{
						case _token_menu: g_parser_state.m_current_property_owner = _property_owner_menu; break;
						case _token_zone_set_menu: g_parser_state.m_current_property_owner = _property_owner_zone_set_menu; break;
						case _token_create_zone_set_menu: g_parser_state.m_current_property_owner = _property_owner_create_zone_set_menu; break;
						case _token_error_geometry_settings_menu: g_parser_state.m_current_property_owner = _property_owner_error_geometry_settings_menu; break;
						case _token_item: g_parser_state.m_current_property_owner = _property_owner_item; break;
						}
						PARSER_ASSERT(parse_stack.top() == _parse_state_reading_tag)
						{
							parse_stack.push_back(_parse_state_reading_open_tag);
						}
					}
					break;

					case _token_global:
					case _token_command:
					{
						PARSER_ASSERT_WITH_MESSAGE(parse_stack.top() == _parse_state_reading_property_found_equals, "unexpected item type")
						{
							g_parser_state.m_has_item_type = true;
							g_parser_state.m_item_type = token == _token_global ? _item_type_hs_variable_global : _item_type_command;
							parse_stack.pop(); // found equals
							parse_stack.pop(); // reading property
						}
					}
					break;

					case _token_eol_0:
					case _token_eol_1:
					case _token_eol_2:
					case _token_eol_3:
						++*line_count;
						break;
					}
				}

				PARSER_ASSERT_WITH_MESSAGE(advance_process_type != _advance_type_process_token, "unexpected token")
				{
					if (advance_process_type == _advance_type_process_distance)
					{
						while (advance_distance-- > 0)
							file_char = fgetc(menu_file);
					}
				}
			}

			return parse_error;
		}

#undef PARSER_ASSERT
#undef PARSER_ASSERT_WITH_MESSAGE
	}

	void debug_menu_parse(c_debug_menu *root_menu, char const *file_name)
	{
		FILE *file = nullptr;
		if (fopen_s(&file, file_name, "rb") != 0 || !file)
			return;

		char error_buffer[1024];
		long line_count = 1;
		long file_char = fgetc(file);
		debug_menu_build_recursive(file, file_char, root_menu, &line_count, error_buffer, sizeof(error_buffer));
		fclose(file);
	}
}
