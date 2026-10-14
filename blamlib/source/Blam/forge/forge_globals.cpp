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

extern long (*const tag_get_first_in_group)(unsigned long group_tag);  // hades: added for 0x10EF8A30
extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x10EF8A30

extern s_forge_globals_definition *forge_globals_get_definition();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

s_forge_globals_definition *forge_globals_get_definition() // 0x10EF8A30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?forge_globals_get_definition@@YAPAUs_forge_globals_definition@@XZ");
	// procedure flags: nofpo
	// long definition_index;
	// function call : long (*const)(unsigned long)
	// function call : void *(*const)(unsigned long, long)

	long definition_index = tag_get_first_in_group('forg');
	if (definition_index != -1)
	{
		return (s_forge_globals_definition *)tag_get('forg', definition_index);
	}

	return nullptr;
}

/* ---------- private code */
