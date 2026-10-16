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

namespace eldorado
{
	// Functions in eldorado.exe, named from the game's own symbols.
	static auto const c_motor_task_valid = reinterpret_cast<bool(__thiscall *)(const c_motor_task *)>(0xB74BC0);
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

bool c_motor_task::valid() const // 0x10F06870
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?valid@c_motor_task@@QBE_NXZ");

	return eldorado::c_motor_task_valid(this);
}

bool c_motor_task::program_default() const // 0x10F06800
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?program_default@c_motor_task@@QBE_NXZ");

	return ((bool(__thiscall *)(const c_motor_task *))0xb74b40)(this);
}

/* ---------- private code */
