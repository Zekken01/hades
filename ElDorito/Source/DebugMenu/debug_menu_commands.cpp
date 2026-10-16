#include "DebugMenu/debug_menu.hpp"

#include "hades/hades.h"

#include "Blam/Cache/StringIdCache.hpp"
#include "Blam/game/players.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/units/units.hpp"
#include "CommandMap.hpp"
#include "Console/Console.hpp"
#include "Objects/ObjectMessaging.hpp"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

// What the menu's items do. The release eldorado.exe has no script compiler, and most
// of the debug commands and globals that debug_menu_init.txt names were stripped from
// it, so each command is resolved here in this order:
//   1. a command implemented below (drop, drop_variant, game_start, ...),
//   2. a script function the release build still has, called directly,
//   3. an ElDewrito console command or variable with the same short name,
// and anything else reports that it is not available in this build.

long tag_find_by_name(unsigned long group_tag, char const *name);
extern void (*const object_placement_data_new)(s_object_placement_data *, long, unsigned long, s_damage_owner *);

namespace DebugMenu
{
	namespace
	{
		/* ---------- globals */

		struct s_game_global
		{
			char const *name;
			e_debug_menu_value_type type;
			unsigned long address;
		};

		s_game_global const k_game_globals[] =
		{
#include "DebugMenu/debug_menu_game_globals.inl"
		};

		// Globals that ElDewrito implements under its own name.
		struct s_global_alias
		{
			char const *name;
			char const *eldewrito_name;
		};

		s_global_alias const k_global_aliases[] =
		{
			{ "cheat_deathless_player", "debug_player_damage_disabled" },
		};

		Modules::Command *find_eldewrito_command(char const *name)
		{
			return Modules::CommandMap::Instance().FindCommand(name);
		}

		/* ---------- commands */

		using t_arguments = std::vector<std::string>;

		// Splits a command into words, keeping "quoted strings" together and folding
		// arithmetic like (/ 1.0 30.0) into its value.
		bool evaluate_arithmetic(char const *&cursor, double *result);

		void skip_spaces(char const *&cursor)
		{
			while (*cursor == ' ' || *cursor == '\t')
				cursor++;
		}

		bool read_word(char const *&cursor, std::string *word)
		{
			skip_spaces(cursor);
			if (!*cursor || *cursor == ')')
				return false;

			if (*cursor == '"')
			{
				char const *end = strchr(++cursor, '"');
				*word = end ? std::string(cursor, end) : std::string(cursor);
				cursor = end ? end + 1 : cursor + strlen(cursor);
				return true;
			}

			if (*cursor == '(')
			{
				double value;
				if (!evaluate_arithmetic(cursor, &value))
					return false;
				char buffer[64];
				sprintf_s(buffer, "%g", value);
				*word = buffer;
				return true;
			}

			char const *start = cursor;
			while (*cursor && *cursor != ' ' && *cursor != '\t' && *cursor != ')')
				cursor++;
			*word = std::string(start, cursor);
			return true;
		}

		bool evaluate_arithmetic(char const *&cursor, double *result)
		{
			cursor++; // (
			std::string op;
			if (!read_word(cursor, &op))
				return false;

			std::vector<double> values;
			std::string word;
			while (read_word(cursor, &word))
				values.push_back(atof(word.c_str()));
			if (*cursor == ')')
				cursor++;
			if (values.empty())
				return false;

			double value = values[0];
			for (size_t i = 1; i < values.size(); i++)
			{
				if (op == "+") value += values[i];
				else if (op == "-") value -= values[i];
				else if (op == "*") value *= values[i];
				else if (op == "/") value = values[i] != 0.0 ? value / values[i] : 0.0;
				else return false;
			}
			*result = value;
			return true;
		}

		t_arguments split_command(char const *command)
		{
			t_arguments words;
			std::string word;
			char const *cursor = command;
			while (read_word(cursor, &word))
				words.push_back(word);
			return words;
		}

		bool parse_bool(std::string const &text)
		{
			return text == "1" || !_stricmp(text.c_str(), "true") || !_stricmp(text.c_str(), "on");
		}

		// drop / drop_variant: places a tag in front of the local player, as
		// Cheat.Spawn does, with an optional model variant.
		void drop_tag(std::string const &tag_path, std::string const &variant)
		{
			struct s_group
			{
				unsigned long tag;
				char const *name;
			};
			static s_group const groups[] =
			{
				{ 'obje', "object" }, { 'bipd', "biped" }, { 'vehi', "vehicle" }, { 'weap', "weapon" }, { 'eqip', "equipment" },
				{ 'argd', "alternate_reality_device" }, { 'term', "terminal" }, { 'proj', "projectile" }, { 'scen', "scenery" },
				{ 'mach', "machine" }, { 'ctrl', "control" }, { 'ssce', "sound_scenery" }, { 'bloc', "crate" }, { 'crea', "creature" },
				{ 'gint', "giant" }, { 'efsc', "effect_scenery" },
			};

			size_t dot = tag_path.find_last_of('.');
			if (dot == std::string::npos)
			{
				debug_menu_print("drop: '%s' has no tag group", tag_path.c_str());
				return;
			}
			std::string name = tag_path.substr(0, dot);
			std::string group_name = tag_path.substr(dot + 1);

			unsigned long group_tag = 0;
			for (s_group const &group : groups)
			{
				if (group_name == group.name)
					group_tag = group.tag;
			}
			if (!group_tag)
			{
				debug_menu_print("drop: can't drop tags of group '%s'", group_name.c_str());
				return;
			}

			long tag_index = tag_find_by_name(group_tag, name.c_str());
			if (tag_index == -1)
			{
				debug_menu_print("drop: '%s' is not in this map", tag_path.c_str());
				return;
			}

			unsigned long variant_name = 0xFFFFFFFF;
			if (!variant.empty())
			{
				auto strings = Blam::Cache::StringIDCache::GetCurrent();
				variant_name = strings ? strings->GetStringId(variant) : 0xFFFFFFFF;
			}

			Objects::CObjectMessaging::EnqueueAction([tag_index, variant_name]()
			{
				long player_index = reinterpret_cast<unsigned long (*)(long)>(0x00589C30)(0);
				if (player_index == -1)
					return;
				s_player_datum *player = player_get(player_index);
				if (player->unit_index == -1)
					return;
				s_unit_data *unit = reinterpret_cast<s_unit_data *>(object_get(player->unit_index));

				real_point3d camera_position;
				reinterpret_cast<void (*)(long, real_point3d *)>(0x00B439D0)(player->unit_index, &camera_position);

				s_object_placement_data placement;
				object_placement_data_new(&placement, tag_index, -1, nullptr);
				if (variant_name != 0xFFFFFFFF)
					placement.variant_name = variant_name;
				placement.forward = unit->aiming_vector;
				placement.up = global_up3d;
				placement.relative_position.x = 0.5f * unit->aiming_vector.i + camera_position.x;
				placement.relative_position.y = 0.5f * unit->aiming_vector.j + camera_position.y;
				placement.relative_position.z = 0.5f * unit->aiming_vector.k + camera_position.z;

				long object_index = reinterpret_cast<long (*)(s_object_placement_data *)>(0x00B30440)(&placement);
				if (object_index != -1)
				{
					reinterpret_cast<void (*)(long)>(0x004B2CD0)(object_index); // simulation_action_object_create
					reinterpret_cast<void (*)(long)>(0x0058FFB0)(object_index);
				}
			});
		}

		// game_start loads a map with the game type game_multiplayer chose, or as a
		// campaign mission when none was chosen, through Game.ForceLoad.
		std::string g_next_game_type;

		void game_start(std::string const &map_path)
		{
			size_t slash = map_path.find_last_of("\\/");
			std::string map_name = slash == std::string::npos ? map_path : map_path.substr(slash + 1);

			t_arguments arguments = { "Game.ForceLoad", map_name };
			if (g_next_game_type.empty())
			{
				arguments.push_back("none");
				arguments.push_back("campaign");
			}
			else
			{
				arguments.push_back(g_next_game_type);
				arguments.push_back("multiplayer");
			}
			std::string result = Modules::CommandMap::Instance().ExecuteCommand(arguments, false);
			if (!result.empty())
				Console::WriteLine(result);
		}

		struct s_builtin_command
		{
			char const *name;
			long minimum_arguments;
			void (*handler)(t_arguments const &arguments);
		};

		s_builtin_command const k_builtin_commands[] =
		{
			{ "drop", 1, [](t_arguments const &a) { drop_tag(a[1], ""); } },
			{ "drop_variant", 2, [](t_arguments const &a) { drop_tag(a[1], a[2]); } },
			{ "game_start", 1, [](t_arguments const &a) { game_start(a[1]); } },
			{ "game_multiplayer", 1, [](t_arguments const &a) { g_next_game_type = a[1]; debug_menu_print("game_start will load %s", a[1].c_str()); } },
			{ "debug_menu_rebuild", 0, [](t_arguments const &) { debug_menu_rebuild(); } },
		};

		// Script functions the release build still implements, called directly with
		// the arguments the script would have passed.
		enum e_call_signature
		{
			_call_void,
			_call_bool,
			_call_long_long,
			_call_long_real_real,
			_call_real_real_real_real,
		};

		struct s_game_function
		{
			char const *name;
			unsigned long address;
			e_call_signature signature;
		};

		s_game_function const k_game_functions[] =
		{
			{ "debug_scripting", 0x0096D860, _call_bool }, // hs_enable_debug_scripting
			{ "ai_enable", 0x01432160, _call_bool }, // ai_globals_set_ai_active
			{ "campaign_metagame_time_pause", 0x0060A460, _call_bool },
			{ "camera_control", 0x00592320, _call_bool }, // director_script_camera
			{ "game_won", 0x00533E40, _call_void },
			{ "game_lost", 0x005321B0, _call_bool }, // game_lost_for_scripting
			{ "game_revert", 0x00506CA0, _call_void }, // main_revert_map_scripting
			{ "core_load", 0x00505980, _call_void }, // main_load_core
			{ "core_save", 0x00506D20, _call_void }, // main_save_core
			{ "game_save_immediate", 0x006824B0, _call_void },
			{ "render_atmosphere_fog", 0x00A20190, _call_bool }, // rasterizer_game_state_set_atmosphere_fog_enable
			{ "atmosphere_fog_override_fade", 0x00672060, _call_long_real_real },
			{ "render_depth_of_field_enable", 0x00A3EEB0, _call_bool }, // render_enable_depth_of_field
			{ "render_depth_of_field", 0x00A3ED50, _call_real_real_real_real }, // render_animate_depth_of_field
			{ "camera_set_mode", 0x005929B0, _call_long_long }, // hs_director_set_camera_mode
		};

		long argument_count(e_call_signature signature)
		{
			switch (signature)
			{
			case _call_bool: return 1;
			case _call_long_long: return 2;
			case _call_long_real_real: return 3;
			case _call_real_real_real_real: return 4;
			}
			return 0;
		}

		void call_game_function(s_game_function const &function, t_arguments const &a)
		{
			if (long(a.size()) - 1 < argument_count(function.signature))
			{
				debug_menu_print("%s: expected %ld arguments", function.name, argument_count(function.signature));
				return;
			}

			switch (function.signature)
			{
			case _call_void:
				reinterpret_cast<void (*)()>(function.address)();
				break;
			case _call_bool:
				reinterpret_cast<void (*)(bool)>(function.address)(parse_bool(a[1]));
				break;
			case _call_long_long:
				reinterpret_cast<void (*)(long, long)>(function.address)(atol(a[1].c_str()), atol(a[2].c_str()));
				break;
			case _call_long_real_real:
				reinterpret_cast<void (*)(long, float, float)>(function.address)(atol(a[1].c_str()), float(atof(a[2].c_str())), float(atof(a[3].c_str())));
				break;
			case _call_real_real_real_real:
				reinterpret_cast<void (*)(float, float, float, float)>(function.address)(float(atof(a[1].c_str())), float(atof(a[2].c_str())), float(atof(a[3].c_str())), float(atof(a[4].c_str())));
				break;
			}
		}
	}

	void debug_menu_print(char const *format, ...)
	{
		char buffer[1024];
		va_list arguments;
		va_start(arguments, format);
		vsprintf_s(buffer, format, arguments);
		va_end(arguments);
		Console::WriteLine(buffer);
	}

	void debug_menu_execute_command(char const *command)
	{
		t_arguments arguments = split_command(command);
		if (arguments.empty())
			return;
		std::string const &verb = arguments[0];

		for (s_builtin_command const &builtin : k_builtin_commands)
		{
			if (verb == builtin.name)
			{
				if (long(arguments.size()) - 1 < builtin.minimum_arguments)
					debug_menu_print("%s: expected %ld arguments", builtin.name, builtin.minimum_arguments);
				else
					builtin.handler(arguments);
				return;
			}
		}

		for (s_game_function const &function : k_game_functions)
		{
			if (verb == function.name)
			{
				call_game_function(function, arguments);
				return;
			}
		}

		if (find_eldewrito_command(verb.c_str()))
		{
			std::string result = Modules::CommandMap::Instance().ExecuteCommand(arguments, false);
			if (!result.empty())
				Console::WriteLine(result);
			return;
		}

		debug_menu_print("debug menu: '%s' is not available in this build", verb.c_str());
	}

	/* ---------- c_debug_menu_value */

	c_debug_menu_value::c_debug_menu_value(char const *name) :
		m_type(k_debug_menu_value_none),
		m_address(nullptr),
		m_command(nullptr)
	{
		for (s_game_global const &global : k_game_globals)
		{
			if (!_stricmp(global.name, name))
			{
				m_type = global.type;
				m_address = reinterpret_cast<void *>(global.address);
				return;
			}
		}

		for (s_global_alias const &alias : k_global_aliases)
		{
			if (!_stricmp(alias.name, name))
				name = alias.eldewrito_name;
		}

		Modules::Command *command = find_eldewrito_command(name);
		if (!command)
			return;

		switch (command->Type)
		{
		case Modules::eCommandTypeVariableInt:
			m_type = command->ValueIntMax <= 1 && command->DefaultValueInt <= 1 ? k_debug_menu_value_bool : k_debug_menu_value_long;
			m_command = command;
			break;
		case Modules::eCommandTypeVariableFloat:
			m_type = k_debug_menu_value_real;
			m_command = command;
			break;
		}
	}

	e_debug_menu_value_type c_debug_menu_value::get_type() const
	{
		return m_type;
	}

	double c_debug_menu_value::get() const
	{
		if (m_address)
		{
			switch (m_type)
			{
			case k_debug_menu_value_bool: return *static_cast<bool *>(m_address) ? 1.0 : 0.0;
			case k_debug_menu_value_real: return *static_cast<float *>(m_address);
			case k_debug_menu_value_short: return *static_cast<short *>(m_address);
			case k_debug_menu_value_long: return *static_cast<long *>(m_address);
			}
		}
		else if (Modules::Command *command = static_cast<Modules::Command *>(m_command))
		{
			return m_type == k_debug_menu_value_real ? double(command->ValueFloat) : double(long(command->ValueInt));
		}
		return 0.0;
	}

	void c_debug_menu_value::set(double value)
	{
		if (m_address)
		{
			switch (m_type)
			{
			case k_debug_menu_value_bool: *static_cast<bool *>(m_address) = value != 0.0; break;
			case k_debug_menu_value_real: *static_cast<float *>(m_address) = float(value); break;
			case k_debug_menu_value_short: *static_cast<short *>(m_address) = short(value); break;
			case k_debug_menu_value_long: *static_cast<long *>(m_address) = long(value); break;
			}
		}
		else if (Modules::Command *command = static_cast<Modules::Command *>(m_command))
		{
			// Through the console, so the variable's update handler runs.
			char buffer[64];
			if (m_type == k_debug_menu_value_real)
				sprintf_s(buffer, "%g", value);
			else
				sprintf_s(buffer, "%ld", long(value));
			Modules::CommandMap::Instance().ExecuteCommand(t_arguments { command->Name, buffer }, false);
		}
	}
}
