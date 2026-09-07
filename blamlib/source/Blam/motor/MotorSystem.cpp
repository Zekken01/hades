/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/motor/motor_system.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class c_motor_task;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern bool _sub_10F06870(c_motor_task const *const);
bool c_motor_task::valid() const // 0x10F06870
{
	mangled_x86(MANGLED_TODO, "?valid@c_motor_task@@QBE_NXZ");
	// c_motor_task const *const this;
	// function call : bool (*)(c_motor_task const *)
	todo("implement");
	bool __result = _sub_10F06870((c_motor_task const *)this);
	return __result;
}

_extern bool _sub_10F06800(c_motor_task const *const);
bool c_motor_task::program_default() const // 0x10F06800
{
	mangled_x86(MANGLED_TODO, "?program_default@c_motor_task@@QBE_NXZ");
	// c_motor_task const *const this;
	// function call : bool (*)(c_motor_task const *)
	todo("implement");
	bool __result = _sub_10F06800((c_motor_task const *)this);
	return __result;
}

/* ---------- private code */
