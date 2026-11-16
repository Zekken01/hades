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
	return ((short(__cdecl *)(long))0x667850)(source_index) > 0;
}

/* ---------- private code */
