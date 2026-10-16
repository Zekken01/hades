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

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
char const *g_damage_reporting_type_names[64] = { "guardians_unknown", "guardians", "falling_damage", "generic_collision", "armor_lock_crush", "generic_melee", "generic_explosion", "magnum", "plasma_pistol", "needler", "mauler", "smg", "plasma_rifle", "battle_rifle", "carbine", "shotgun", "sniper_rifle", "beam_rifle", "assault_rifle", "spiker", "fuel_rod_cannon", "missile_pod", "rocket_launcher", "spartan_laser", "brute_shot", "flamethrower", "sentinel_gun", "energy_sword", "gravity_hammer", "frag_grenade", "plasma_grenade", "spike_grenade", "firebomb_grenade", "flag", "bomb", "bomb_explosion", "ball", "machinegun_turret", "plasma_cannon", "plasma_mortar", "plasma_turret", "shade_turret", "banshee", "ghost", "mongoose", "scorpion", "scorpion_gunner", "spectre", "spectre_gunner", "warthog", "warthog_gunner", "warthog_gauss_turret", "wraith", "wraith_gunner", "tank", "chopper", "hornet", "mantis", "prowler", "sentinel_beam", "sentinel_rpg", "teleporter", "tripmine", "dmr" };
