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

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern s_mod_player_actions_set_definition *_sub_10F07F20(long);
s_mod_player_actions_set_definition *s_mod_player_actions_set_definition::get(long definition_index) // 0x10F07F20
{
	mangled_x86(MANGLED_TODO, "?get@s_mod_player_actions_set_definition@@SAPAU1@J@Z");
	// long definition_index;
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	s_mod_player_actions_set_definition * __result = _sub_10F07F20(definition_index);
	return __result;
}

/* ---------- private code */
