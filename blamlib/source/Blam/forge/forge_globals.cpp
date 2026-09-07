/* ---------- headers */

#include "Blam/forge/forge_globals.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

struct s_forge_globals_definition;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern s_forge_globals_definition *forge_globals_get_definition();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern s_forge_globals_definition *_sub_10EF8A30();
s_forge_globals_definition *forge_globals_get_definition() // 0x10EF8A30
{
	mangled_x86(MANGLED_TODO, "?forge_globals_get_definition@@YAPAUs_forge_globals_definition@@XZ");
	// procedure flags: nofpo
	// long definition_index;
	// function call : long (*const)(unsigned long)
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	s_forge_globals_definition * __result = _sub_10EF8A30();
	return __result;
}

/* ---------- private code */
