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

extern void *(__cdecl *const tag_get)(unsigned long, long);  // hades: added for 0X10F02990
extern long (__cdecl *const tag_get_first_in_group)(unsigned long);  // hades: added for 0X10F02990

extern s_mod_globals_definition *mod_globals_get_definition();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

s_mod_globals_definition *mod_globals_get_definition() // 0x10F02990
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?mod_globals_get_definition@@YAPAUs_mod_globals_definition@@XZ");
	// procedure flags: nofpo
	// function call : long (*const)(unsigned long)
	// function call : void *(*const)(unsigned long, long)

	return (s_mod_globals_definition *)tag_get(0x6D6F6467, tag_get_first_in_group(0x6D6F6467));
}

/* ---------- private code */
