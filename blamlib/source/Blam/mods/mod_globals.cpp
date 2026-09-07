/* ---------- headers */

#include "Blam/mods/mod_globals.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

struct s_mod_globals_definition;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern s_mod_globals_definition *mod_globals_get_definition();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern s_mod_globals_definition *_sub_10F02990();
s_mod_globals_definition *mod_globals_get_definition() // 0x10F02990
{
	mangled_x86(MANGLED_TODO, "?mod_globals_get_definition@@YAPAUs_mod_globals_definition@@XZ");
	// procedure flags: nofpo
	// function call : long (*const)(unsigned long)
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	s_mod_globals_definition * __result = _sub_10F02990();
	return __result;
}

/* ---------- private code */
