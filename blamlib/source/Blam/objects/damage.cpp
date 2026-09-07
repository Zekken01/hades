/* ---------- headers */

#include "Blam/objects/damage.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

#include <functional>

/* ---------- constants */

/* ---------- definitions */

namespace Patches
{
	namespace Core
	{
		typedef std::function<void __cdecl(void)> GameStartCallback;
	}
}

/* ---------- prototypes */

/* ---------- globals */

extern char const *g_damage_reporting_type_names[64]; // 0x1135A4A0

/* ---------- private variables */

/* ---------- public code */

/* ---------- private code */
