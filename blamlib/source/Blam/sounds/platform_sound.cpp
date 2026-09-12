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

bool platform_sound_source_is_playing(long source_index) // 0x10F1AA30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?platform_sound_source_is_playing@@YA_NJ@Z");
	// long source_index;
	// function call : short (*const)(long)

	return ((short(__cdecl *)(long))0x667850)(source_index) > 0;
}

/* ---------- private code */
