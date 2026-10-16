/* ---------- headers */

#include "Blam/game/game_time.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage_definitions.hpp"

/* ---------- forward declarations */

struct s_game_time_globals;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern s_game_time_globals *game_time_get_globals();
extern void game_time_set_speed(float speed);

/* ---------- globals */

extern float (*const game_ticks_to_seconds)(float); // 0x11248DA4
extern long (*const game_time_get)(); // 0x11248DA8
extern float (*const game_tick_length)(); // 0x11248D9C
extern float (*const game_seconds_to_ticks_real)(float); // 0x11248D94
extern long (*const game_seconds_to_ticks_round)(float); // 0x11248D98
extern long (*const game_tick_rate)(); // 0x11248DA0
extern bool (*const game_time_get_paused)(); // 0x11248DAC
extern long (*const game_seconds_integer_to_ticks)(long); // 0x11248D90
extern float (*const game_time_get_speed)(); // 0x11248DB0
extern void (*const game_time_set_paused)(bool, c_enum<enum e_game_time_pause_reason,unsigned short>); // 0x11248DB4

/* ---------- private variables */

/* ---------- public code */

s_game_time_globals *game_time_get_globals() // 0x10F003C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_time_get_globals@@YAPAUs_game_time_globals@@XZ");

	return tls_getd().game_time;
}

void game_time_set_speed(float speed) // 0x10F00410
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_time_set_speed@@YAXM@Z");

	game_time_get_globals()->game_speed = speed;
}

/* ---------- private code */

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
long (*const game_time_get)() = reinterpret_cast<decltype(game_time_get)>(0x564D50);
float (*const game_tick_length)() = reinterpret_cast<decltype(game_tick_length)>(0x564C20);
float (*const game_ticks_to_seconds)(float) = reinterpret_cast<decltype(game_ticks_to_seconds)>(0x564C60);
float (*const game_seconds_to_ticks_real)(float) = reinterpret_cast<decltype(game_seconds_to_ticks_real)>(0x564B70);
long (*const game_tick_rate)() = reinterpret_cast<decltype(game_tick_rate)>(0x564C40);
bool (*const game_time_get_paused)() = reinterpret_cast<decltype(game_time_get_paused)>(0x564D70);
long (*const game_seconds_to_ticks_round)(float) = reinterpret_cast<decltype(game_seconds_to_ticks_round)>(0x564BB0);
long (*const game_seconds_integer_to_ticks)(long) = reinterpret_cast<decltype(game_seconds_integer_to_ticks)>(0x564B40);
