/* ---------- headers */

#include "hades/hades.h"

#include "Blam/animations/mixing_board/channels/animation_channel.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/motor/action_system.hpp"
#include "Blam/motor/motor_system.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Player/PlayerEmotes.hpp"
#include "Pointer.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_motor_task;
struct c_animation_channel;
struct s_action_definition;
struct s_action_request;
struct s_action_usage;
struct s_object_data;
struct s_unit_data;

namespace Player {}
using namespace ::Player;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace MotorSystem {}
	using namespace Patches::MotorSystem;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0x107BAE20

namespace Patches
{
	namespace MotorSystem
	{
		extern void ApplyAll();
	}
}

bool action_allow_interruption_hook(e_action current_action, e_action desired_action, unsigned short *context);
bool motor_animation_task_busy_hook(long object_index, c_motor_task *task, long resource_type, bool a4, bool a5);
s_action_definition *action_get_definition_hook(e_action action_type);
bool action_submit_hook(long motor_index, s_action_request *request);
void action_finished_hook(long motor_index, e_action action_type);
bool action_update_hook(long motor_index);
bool unit_movement_inhibited_hook(long unit_index);
bool custom_animation_submit_motor_task_allow_hook(long motor_index, e_action action, long mask);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern s_action_usage g_action_usage_definitions[88]; // 0x11351E28
	s_action_definition *g_action_definitions[88] = { (s_action_definition *)0x19496BC, (s_action_definition *)0x194966C, (s_action_definition *)0x1949680, (s_action_definition *)0x194A4D0, (s_action_definition *)0x1949770, (s_action_definition *)0x19496A8, (s_action_definition *)0x1949568, (s_action_definition *)0x194952C, (s_action_definition *)0x19496BC, (s_action_definition *)0x19496BC, (s_action_definition *)0x1949568, (s_action_definition *)0x194957C, (s_action_definition *)0x1949694, (s_action_definition *)0x1949644, (s_action_definition *)0x1949658, (s_action_definition *)0x194970C, (s_action_definition *)0x194941C, (s_action_definition *)0x1949798, (s_action_definition *)0x1949784, (s_action_definition *)0x19496D0, (s_action_definition *)0x19494B4, (s_action_definition *)0x19494C8, (s_action_definition *)0x1949720, (s_action_definition *)0x19494DC, (s_action_definition *)0x1949478, (s_action_definition *)0x194948C, (s_action_definition *)0x1949504, (s_action_definition *)0x1949518, nullptr, (s_action_definition *)0x1949430, (s_action_definition *)0x1949448, (s_action_definition *)0x19494A0, (s_action_definition *)0x1949464, (s_action_definition *)0x1949590, (s_action_definition *)0x19495A4, (s_action_definition *)0x19495B8, (s_action_definition *)0x19495CC, (s_action_definition *)0x19494F0, (s_action_definition *)0x194975C, (s_action_definition *)0x1949408, (s_action_definition *)0x19493F4, (s_action_definition *)0x19496E4, (s_action_definition *)0x1949734, (s_action_definition *)0x1949748, (s_action_definition *)0x19496F8, (s_action_definition *)0x1949540, (s_action_definition *)0x194A370, (s_action_definition *)0x194A384, (s_action_definition *)0x194A348, (s_action_definition *)0x194A348, (s_action_definition *)0x194961C, (s_action_definition *)0x1949630, (s_action_definition *)0x194A398, (s_action_definition *)0x194A3AC, (s_action_definition *)0x1949554, (s_action_definition *)0x194A334, (s_action_definition *)0x194A3E8, (s_action_definition *)0x194A3E8, (s_action_definition *)0x194A3C0, (s_action_definition *)0x194A3D4, (s_action_definition *)0x194A314, (s_action_definition *)0x19495E0, (s_action_definition *)0x19495F4, (s_action_definition *)0x1949608, (s_action_definition *)0x194A35C, (s_action_definition *)0x194A35C, (s_action_definition *)0x194A35C, (s_action_definition *)0x194A35C, (s_action_definition *)0x19496BC, (s_action_definition *)0x194A300, (s_action_definition *)0x194A300, (s_action_definition *)0x194A300, (s_action_definition *)0x194A300, (s_action_definition *)0x194A300, (s_action_definition *)0x194A300, (s_action_definition *)0x194A300, (s_action_definition *)0x194A300, (s_action_definition *)0x194A300, (s_action_definition *)0x194A300, (s_action_definition *)0x194A300, (s_action_definition *)0x194A300, (s_action_definition *)0x194A300, (s_action_definition *)0x194A300, (s_action_definition *)0x194A300, (s_action_definition *)0x194A300, (s_action_definition *)0x194A300, (s_action_definition *)0x194A300, Player::CPlayerEmotes::m_emote_action_definition }; // 0x113520E8
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace MotorSystem
	{
		void ApplyAll() // 0x107BA430
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@MotorSystem@Patches@@YAXXZ");

			Hook(0x7901D0, motor_animation_task_busy_hook).Apply();
			Hook(0x769B20, action_allow_interruption_hook).Apply();
			Hook(0x769D20, action_update_hook).Apply();
			Hook(0x769BF0, action_finished_hook).Apply();
			Hook(0x769C50, action_submit_hook).Apply();
			Hook(0x769C10, action_get_definition_hook).Apply();
			Hook(0x744F90, unit_movement_inhibited_hook).Apply();
			Hook(0x7828E4, custom_animation_submit_motor_task_allow_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0xBA6970).Write<unsigned int>(0x9C);
		}
	}
}

/* ---------- private code */

bool action_allow_interruption_hook(e_action current_action, e_action desired_action, unsigned short *context) // 0x107BAC40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?action_allow_interruption_hook@@YA_NW4e_action@@0PAG@Z");

	bool result = true;
	if (desired_action != -1)
	{
		if (current_action == -1)
			result = false;
		else if (current_action >= 0 && current_action < 88 && desired_action >= 0 && desired_action < 88)
		{
			unsigned short desired_flags = g_action_usage_definitions[desired_action].flags;
			result = true;
			if (!(desired_flags & 4) || !((*(unsigned char *)context >> 1) & 1))
			{
				short current_prioruty = g_action_usage_definitions[desired_action].priority;
				short desired_priority = g_action_usage_definitions[current_action].priority;
				if (current_prioruty > desired_priority || current_prioruty >= desired_priority && (!(g_action_usage_definitions[current_action].flags & 1) || (desired_flags & 2) && (*(unsigned char *)context & 1)))
					result = false;
			}
		}
	}
	return result;
}

bool motor_animation_task_busy_hook(long object_index, c_motor_task *task, long resource_type, bool a4, bool a5) // 0x107BB150
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?motor_animation_task_busy_hook@@YA_NJPAVc_motor_task@@J_N1@Z");

	bool v5 = false;
	if (task->valid() && !task->program_default())
	{
		long action_type = task->action_type;
		v5 = true;
		if (action_type >= 0 && action_type < 88)
		{
			unsigned short flags = g_action_usage_definitions[action_type].flags;
			if (!(flags & 8))
				return false;
			if ((!(flags & 0x10) || (v5 = !a4, !a4)) && a5 && a4 && (*(long *)((char *)((void *(*)(long, long))0xB8FED0)(object_index, resource_type) + 0x34) >> 5) & 1)
				v5 = false;
		}
	}
	return v5;
}

s_action_definition *action_get_definition_hook(e_action action_type) // 0x107BADF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?action_get_definition_hook@@YAPAUs_action_definition@@W4e_action@@@Z");

	return g_action_definitions[action_type];
}

bool action_submit_hook(long motor_index, s_action_request *request) // 0x107BAE20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?action_submit_hook@@YA_NJPAUs_action_request@@@Z");

	static void (*const motor_task_reset)(long) = reinterpret_cast<void (*)(long)>(0xB34D00);
	void (*const player_training_unit_submitted_action)(long, long, e_action, bool) = reinterpret_cast<void (*)(long, long, e_action, bool)>(0x68A0B0);
	bool result = false;
	s_action_definition *definition = g_action_definitions[request->action_type];
	if (definition && definition->submit)
	{
		motor_task_reset(motor_index);
		result = definition->submit(motor_index, request);
		{
			s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(motor_index, 0x2003);
			if (unit && unit->player_index != -1)
				player_training_unit_submitted_action(unit->player_index, motor_index, (e_action)request->action_type, result);
		}
	}
	else
		result = true;
	return result;
}

void action_finished_hook(long motor_index, e_action action_type) // 0x107BAD60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?action_finished_hook@@YAXJW4e_action@@@Z");

	if (g_action_definitions[action_type]->finished)
	{
		g_action_definitions[action_type]->finished(motor_index, action_type);
	}
}

bool action_update_hook(long motor_index) // 0x107BAF80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?action_update_hook@@YA_NJ@Z");

	static c_motor_task *(*const motor_task_get)(long, long) = reinterpret_cast<c_motor_task *(*)(long, long)>(0xB91510);
	bool result = false;
	for (__int32 i = 0; i < 4; i++)
	{
		c_motor_task *task = motor_task_get(motor_index, i);
		if (!task || !task->valid() || task->action_type == -1)
			continue;
		s_action_definition *definition = g_action_definitions[task->action_type];
		if (definition->update)
		{
			if (definition->update(motor_index, (e_action)task->action_type))
				result = true;
			else
				task->action_type = -1;
		}
	}
	return result;
}

bool unit_movement_inhibited_hook(long unit_index) // 0x107BB2A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_movement_inhibited_hook@@YA_NJ@Z");

	bool (*const unit_has_armor_lock)(long) = reinterpret_cast<bool (*)(long)>(0xB44EF0);
	bool (*const biped_is_animation_controlled_by_equipment)(long) = reinterpret_cast<bool (*)(long)>(0xB6FA00);

	if (unit_has_armor_lock(unit_index))
	{
		return true;
	}

	if (biped_is_animation_controlled_by_equipment(unit_index))
	{
		return true;
	}

	if (Player::CPlayerEmotes::UnitMovementInhibited(unit_index))
	{
		return true;
	}

	return false;
}

bool custom_animation_submit_motor_task_allow_hook(long motor_index, e_action action, long mask) // 0x107BB0B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?custom_animation_submit_motor_task_allow_hook@@YA_NJW4e_action@@J@Z");

	bool (__cdecl *const custom_animation_submit_motor_task_allow)(long, e_action, long) = (bool(__cdecl *const)(long, e_action, long))0xb90c80;

	if (((bool(__cdecl *)(long, int))0xb69ba0)(motor_index, 87))
	{
		return false;
	}

	return custom_animation_submit_motor_task_allow(motor_index, action, mask);
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { s_action_usage g_action_usage_definitions[88] = { { "_action_death_ping", 25, 9 }, { "_action_custom_animation", 20, 9 }, { "_action_stop_custom_animation", 20, 0 }, { "_action_sync_container", 20, 8 }, { "_action_assassinate", 20, 9 }, { "_action_get_infected", 19, 8 }, { "_action_hostile_morph", 19, 8 }, { "_action_resurrect", 19, 8 }, { "_action_hard_ping", 18, 9 }, { "_action_ping", 18, 1 }, { "_action_morph", 17, 8 }, { "_action_morph_arrival", 17, 8 }, { "_action_infect", 15, 8 }, { "_action_posture", 12, 8 }, { "_action_posture_exit", 12, 8 }, { "_action_vehicle_exit", 10, 8 }, { "_action_vehicle_exit_and_detach", 10, 8 }, { "_action_vehicle_ejection", 10, 8 }, { "_action_vehicle_board", 10, 8 }, { "_action_vehicle_enter", 8, 8 }, { "_action_open", 6, 9 }, { "_action_close", 6, 9 }, { "_action_vehicle_exit_immediate", 6, 8 }, { "_action_vehicle_flip", 6, 8 }, { "_action_climb_attach", 6, 8 }, { "_action_climb_detach", 6, 8 }, { "_action_wall_lean", 6, 8 }, { "_action_wall_lean_open", 6, 8 }, { "action_token", 6, 8 }, { "_action_takeoff", 6, 8 }, { "_action_perch", 6, 8 }, { "_action_perch_jump", 6, 8 }, { "_action_land", 6, 8 }, { "_action_jump", 6, 8 }, { "_action_leap_anticipation", 6, 8 }, { "_action_leap", 6, 8 }, { "_action_leap_recovery", 6, 8 }, { "_action_emit_ai", 6, 8 }, { "_action_berserk", 6, 8 }, { "_action_flurry", 6, 8 }, { "_action_deploy_turret", 6, 8 }, { "_action_smash", 6, 8 }, { "_action_vault", 6, 8 }, { "_action_hoist", 6, 8 }, { "_action_ai_impulse", 6, 8 }, { "_action_melee_ai", 6, 8 }, { "_action_weapon_pickup", 6, 8 }, { "_action_weapon_trade", 6, 8 }, { "_action_primary_weapon_drop", 6, 0 }, { "_action_secondary_weapon_drop", 6, 0 }, { "_action_surge", 6, 8 }, { "_action_phase", 6, 8 }, { "_action_stow", 6, 8 }, { "_action_draw", 6, 8 }, { "_action_infection_spew", 6, 8 }, { "_action_kamikaze", 5, 12 }, { "_action_primary_weapon_switch", 5, 8 }, { "_action_secondary_weapon_switch", 5, 8 }, { "_action_grenade", 4, 12 }, { "_action_equipment", 4, 12 }, { "_action_equipment_animation", 7, 8 }, { "_action_equipment_pickup", 4, 8 }, { "_action_equipment_drop", 4, 8 }, { "_action_melee_player", 3, 31 }, { "_action_primary_weapon_primary_reload", 3, 29 }, { "_action_primary_weapon_secondary_reload", 3, 29 }, { "_action_secondary_weapon_primary_reload", 3, 29 }, { "_action_secondary_weapon_secondary_reload", 3, 29 }, { "_action_soft_ping", 2, 1 }, { "_action_primary_weapon_primary_recoil", 2, 0 }, { "_action_primary_weapon_secondary_recoil", 2, 0 }, { "_action_primary_weapon_primary_chamber", 2, 0 }, { "_action_primary_weapon_secondary_chamber", 2, 0 }, { "_action_primary_weapon_primary_charged", 2, 0 }, { "_action_primary_weapon_secondary_charged", 2, 0 }, { "_action_secondary_weapon_primary_recoil", 2, 0 }, { "_action_secondary_weapon_secondary_recoil", 2, 0 }, { "_action_secondary_weapon_primary_chamber", 2, 0 }, { "_action_secondary_weapon_secondary_chamber", 2, 0 }, { "_action_secondary_weapon_primary_charged", 2, 0 }, { "_action_secondary_weapon_secondary_charged", 2, 0 }, { "_action_primary_weapon_overheat_enter", 2, 0 }, { "_action_primary_weapon_overheat_loop", 2, 0 }, { "_action_primary_weapon_overheat_exit", 2, 0 }, { "_action_secondary_weapon_overheat_enter", 2, 0 }, { "_action_secondary_weapon_overheat_loop", 2, 0 }, { "_action_secondary_weapon_overheat_exit", 2, 0 }, { "_action_player_emote", 4, 12 } }; }
