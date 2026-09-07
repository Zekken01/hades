/* ---------- headers */

#include "Blam/sounds/platform_sound.hpp"
#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern bool platform_sound_source_is_playing(long source_index);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern bool _sub_10F1AA30(long);
bool platform_sound_source_is_playing(long source_index) // 0x10F1AA30
{
	mangled_x86(MANGLED_TODO, "?platform_sound_source_is_playing@@YA_NJ@Z");
	// long source_index;
	// function call : short (*const)(long)
	todo("implement");
	bool __result = _sub_10F1AA30(source_index);
	return __result;
}

/* ---------- private code */
