/* ---------- headers */

#include "Blam/mods/player_action_set.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <tuple>
#include <type_traits>
#include <utility>

/* ---------- forward declarations */

struct s_mod_player_actions_set_definition;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x10F07F20

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

s_mod_player_actions_set_definition *s_mod_player_actions_set_definition::get(long definition_index) // 0x10F07F20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get@s_mod_player_actions_set_definition@@SAPAU1@J@Z");

	return (s_mod_player_actions_set_definition *)tag_get(0x70616374, definition_index);
}

/* ---------- private code */
