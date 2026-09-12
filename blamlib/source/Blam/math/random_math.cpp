/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- constants */

/* ---------- definitions */

typedef bool (*__acrt_initialize_pft)();
typedef bool (*__acrt_uninitialize_pft)(bool);

/* ---------- prototypes */

extern unsigned long *(__cdecl *get_random_seed_address)();  // hades: added for 0X10F036C0

extern float real_random_range(float minimum, float maximum);
extern float real_random_range(long *random_seed_address, float minimum, float maximum);
extern float real_random_local();

/* ---------- globals */

extern unsigned long *(*get_local_random_seed_address)(); // 0x11359AF8
extern unsigned long *(*get_random_seed_address)(); // 0x11359AFC

/* ---------- private variables */

/* ---------- public code */

float real_random_range(float minimum, float maximum) // 0x10F036C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?real_random_range@@YAMMM@Z");
	// float maximum;
	// unsigned long *random_seed_address;
	// unsigned long next_value;
	// function call : unsigned long *(*)()

	unsigned long *random_seed_address = get_random_seed_address();
	unsigned int next_value = 1664525 * *random_seed_address + 1013904223;
	*random_seed_address = next_value;
	next_value >>= 16;
	return (float)next_value / 65535.0f * (maximum - minimum) + minimum;
}

float real_random_range(long *random_seed_address, float minimum, float maximum) // 0x10F037C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?real_random_range@@YAMPAJMM@Z");
	// float maximum;
	// unsigned long next_value;

	unsigned int next_value = 1664525 * *random_seed_address + 1013904223;
	*random_seed_address = next_value;
	next_value >>= 16;
	return (float)next_value / 65535.0f * (maximum - minimum) + minimum;
}

float real_random_local() // 0x10F035D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?real_random_local@@YAMXZ");
	// procedure flags: nofpo
	// unsigned long *random_seed_address;
	// unsigned long next_value;
	// function call : unsigned long *(*)()

	unsigned long *random_seed_address = get_local_random_seed_address();
	unsigned long next_value = 0x19660D * *random_seed_address + 0x3C6EF35F;
	*random_seed_address = next_value;
	next_value = next_value >> 16;
	return (float)next_value / 65535.0f;
}

/* ---------- private code */
