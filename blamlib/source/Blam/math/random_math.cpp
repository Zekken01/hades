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

extern float real_random_range(float minimum, float maximum);
extern float real_random_range(long *random_seed_address, float minimum, float maximum);
extern float real_random_local();

/* ---------- globals */

extern unsigned long *(*get_local_random_seed_address)(); // 0x11359AF8
extern unsigned long *(*get_random_seed_address)(); // 0x11359AFC

/* ---------- private variables */

/* ---------- public code */

_extern float _sub_10F036C0(float, float);
float real_random_range(float minimum, float maximum) // 0x10F036C0
{
	mangled_x86(MANGLED_TODO, "?real_random_range@@YAMMM@Z");
	// float maximum;
	// unsigned long *random_seed_address;
	// unsigned long next_value;
	// function call : unsigned long *(*)()
	todo("implement");
	float __result = _sub_10F036C0(minimum, maximum);
	return __result;
}

_extern float _sub_10F037C0(long *, float, float);
float real_random_range(long *random_seed_address, float minimum, float maximum) // 0x10F037C0
{
	mangled_x86(MANGLED_TODO, "?real_random_range@@YAMPAJMM@Z");
	// float maximum;
	// unsigned long next_value;
	todo("implement");
	float __result = _sub_10F037C0(random_seed_address, minimum, maximum);
	return __result;
}

_extern float _sub_10F035D0();
float real_random_local() // 0x10F035D0
{
	mangled_x86(MANGLED_TODO, "?real_random_local@@YAMXZ");
	// procedure flags: nofpo
	// unsigned long *random_seed_address;
	// unsigned long next_value;
	// function call : unsigned long *(*)()
	todo("implement");
	float __result = _sub_10F035D0();
	return __result;
}

/* ---------- private code */
