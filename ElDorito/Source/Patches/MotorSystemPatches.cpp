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
	extern s_action_definition *g_action_definitions[88]; // 0x113520E8
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace MotorSystem
	{
		_extern void _sub_107BA430();
		void ApplyAll() // 0x107BA430
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@MotorSystem@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_107BA430();
		}
	}
}

/* ---------- private code */

_extern bool _sub_107BAC40(e_action, e_action, unsigned short *);
bool action_allow_interruption_hook(e_action current_action, e_action desired_action, unsigned short *context) // 0x107BAC40
{
	// `anonymous-namespace'::action_allow_interruption_hook
	// unsigned short *context;
	// bool result;
	{
		// unsigned short desired_flags;
		{
			// short current_prioruty;
			// short desired_priority;
		}
	}
	todo("implement");
	bool __result = _sub_107BAC40(current_action, desired_action, context);
	return __result;
}

_extern bool _sub_107BB150(long, c_motor_task *, long, bool, bool);
bool motor_animation_task_busy_hook(long object_index, c_motor_task *task, long resource_type, bool a4, bool a5) // 0x107BB150
{
	// `anonymous-namespace'::motor_animation_task_busy_hook
	// bool a5;
	// bool v5;
	{
		// long action_type;
		{
			// unsigned short flags;
		}
	}
	// function call : c_animation_channel *(*const)(long, long)
	todo("implement");
	bool __result = _sub_107BB150(object_index, task, resource_type, a4, a5);
	return __result;
}

s_action_definition *action_get_definition_hook(e_action action_type) // 0x107BADF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?action_get_definition_hook@@YAPAUs_action_definition@@W4e_action@@@Z");
	// `anonymous-namespace'::action_get_definition_hook
	// e_action action_type;

	return g_action_definitions[action_type];
}

_extern bool _sub_107BAE20(long, s_action_request *);
bool action_submit_hook(long motor_index, s_action_request *request) // 0x107BAE20
{
	// `anonymous-namespace'::action_submit_hook
	// s_action_request *request;
	// void (*const player_training_unit_submitted_action)(long, long, e_action, bool);
	// bool result;
	// s_action_definition *definition;
	{
		// s_unit_data *unit;
	}
	// function call : void (*const)(long)
	// function call : bool (*)(long, s_action_request const *)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, long, e_action, bool)
	todo("implement");
	bool __result = _sub_107BAE20(motor_index, request);
	return __result;
}

void action_finished_hook(long motor_index, e_action action_type) // 0x107BAD60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?action_finished_hook@@YAXJW4e_action@@@Z");
	// `anonymous-namespace'::action_finished_hook
	// e_action action_type;
	// function call : void (*)(long, e_action)

	if (g_action_definitions[action_type]->finished)
	{
		g_action_definitions[action_type]->finished(motor_index, action_type);
	}
}

_extern bool _sub_107BAF80(long);
bool action_update_hook(long motor_index) // 0x107BAF80
{
	// `anonymous-namespace'::action_update_hook
	// long motor_index;
	// bool result;
	{
		// __int32 i;
		{
			// s_action_definition *definition;
			// c_motor_task *task;
		}
	}
	// function call : c_motor_task *(*const)(long, long)
	// function call : bool (*)(long, e_action)
	todo("implement");
	bool __result = _sub_107BAF80(motor_index);
	return __result;
}

_extern bool _sub_107BB2A0(long);
bool unit_movement_inhibited_hook(long unit_index) // 0x107BB2A0
{
	// `anonymous-namespace'::unit_movement_inhibited_hook
	// long unit_index;
	// bool (*const unit_has_armor_lock)(long);
	// bool (*const biped_is_animation_controlled_by_equipment)(long);
	// function call : bool (*const)(long)
	// function call : bool (*const)(long)
	todo("implement");
	bool __result = _sub_107BB2A0(unit_index);
	return __result;
}

bool custom_animation_submit_motor_task_allow_hook(long motor_index, e_action action, long mask) // 0x107BB0B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?custom_animation_submit_motor_task_allow_hook@@YA_NJW4e_action@@J@Z");
	// `anonymous-namespace'::custom_animation_submit_motor_task_allow_hook
	// long mask;
	// bool (*const motor_task_allow)(long, e_action, long);
	// function call : bool (*const)(long, e_action)
	// function call : bool (*const)(long, e_action, long)

	bool (__cdecl *const custom_animation_submit_motor_task_allow)(long, e_action, long) = (bool(__cdecl *const)(long, e_action, long))0xb90c80;

	if (((bool(__cdecl *)(long, int))0xb69ba0)(motor_index, 87))
	{
		return false;
	}

	return custom_animation_submit_motor_task_allow(motor_index, action, mask);
}
