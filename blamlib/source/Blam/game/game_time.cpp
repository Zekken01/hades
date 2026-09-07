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

extern s_game_time_globals *_sub_10F003C0();
s_game_time_globals *game_time_get_globals() // 0x10F003C0
{
	mangled_x86(MANGLED_TODO, "?game_time_get_globals@@YAPAUs_game_time_globals@@XZ");
	// procedure flags: nofpo
	todo("implement");
	s_game_time_globals * __result = _sub_10F003C0();
	return __result;
}

_extern void _sub_10F00410(float);
void game_time_set_speed(float speed) // 0x10F00410
{
	mangled_x86(MANGLED_TODO, "?game_time_set_speed@@YAXM@Z");
	// float speed;
	todo("implement");
	_sub_10F00410(speed);
}

/* ---------- private code */
