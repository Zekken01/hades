/* ---------- headers */

#include "Blam/cseries/errors.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/objects/damage_definitions.hpp"

#include <stdio.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void error(c_enum<enum e_error_message_priority,int> priority, char const *message, ...);

/* ---------- globals */

extern bool g_errors_write_to_console; // 0x1135A72E

/* ---------- private variables */

/* ---------- public code */

void error(c_enum<enum e_error_message_priority,int> priority, char const *message, ...) // 0x10F1D3B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?error@@YAXV?$c_enum@W4e_error_message_priority@@H@@PBDZZ");
	// char *va;

	va_list va;
	va_start(va, message);
	vprintf(message, va);
	va_end(va);
}

/* ---------- private code */
