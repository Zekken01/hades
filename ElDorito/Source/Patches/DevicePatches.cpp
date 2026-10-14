/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/devices/device_definitions.hpp"
#include "Blam/devices/devices.hpp"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeDevice.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/GamePatches.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Pointer.hpp"
#include "Utils/Singleton.hpp"

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

class CForgeDeviceManager;
struct CForgeDeviceObjectProperties;
struct IGameSystem;
struct c_game_engine;
struct s_control_definition;
struct s_device_data;
struct s_device_definition;
struct s_device_group_datum;
struct s_machine_definition;
struct s_multiplayer_object_properties;
struct s_object_data;
struct s_player_action_context;

namespace Utils {}
using namespace ::Utils;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Devices {}
	using namespace Patches::Devices;
	namespace Game {}
	using namespace Patches::Game;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern bool (*game_is_campaign)();  // hades: added for 0x108CEF50

extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x108CF450
extern s_multiplayer_object_properties *(*const object_get_multiplayer)(unsigned long);  // hades: added for 0x108CF450

extern long unit_get_ultimate_motion_control_unit_index(long unit_index);  // hades: added for 0x108CEE80
extern long unit_get_current_or_last_weak_player_index(long unit_index);  // hades: added for 0x108CEE80
extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long object_index, c_enum<e_object_type, long> object_type_mask);  // hades: added for 0x108CEE80

namespace Patches
{
	namespace Devices
	{
		extern void ApplyAll();
		extern bool PlayerConsiderDeviceInteraction(long player_index, long device_index, s_player_action_context *out_action_context);
	}
}

void machine_update_hook(long machine_index);
bool device_block_interaction_odst_hook(long object_index);
bool device_allows_player_interaction(long device_index, long player_index);
bool device_allows_object_interaction(long device_index, long object_index);
void device_touched_hook(long device_index, long unit_index, bool a3);
bool machine_door_test_object_hook(long machine_index, long const *object_indices, short object_indices_count);
void control_touched_hook(long device_index, long unit_index);

/* ---------- globals */

namespace Utils
{
	CForgeDeviceManager *Utils::Singleton<CForgeDeviceManager>::m_instance; // 0x1240833C
}

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Devices
	{
		void ApplyAll() // 0x108CE320
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Devices@Patches@@YAXXZ");
			// procedure flags: nofpo

			Pointer(0x1948C2C).Write<unsigned long>(reinterpret_cast<unsigned long>(machine_update_hook));
			Hook(0x7925D1, device_block_interaction_odst_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x139CE6, PlayerConsiderDeviceInteraction, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0xCE415, device_touched_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x13AA88, device_touched_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x13AEA1, device_touched_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7B580F, machine_door_test_object_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x10CA7BD, machine_door_test_object_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x10CA7BD, machine_door_test_object_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7BFD50, control_touched_hook).Apply();
		}

		bool PlayerConsiderDeviceInteraction(long player_index, long device_index, s_player_action_context *out_action_context) // 0x108CED20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PlayerConsiderDeviceInteraction@Devices@Patches@@YA_NJJPAUs_player_action_context@@@Z");
			// s_player_action_context *out_action_context;
			// bool (*const player_consider_device_interaction)(long, long, s_player_action_context *);
			// function call : bool (*const)(long, long, s_player_action_context *)

			bool (__cdecl *const player_consider_device_interaction)(long, long, s_player_action_context *) = (bool(__cdecl *const)(long, long, s_player_action_context *))0x5388d0;

			if (!device_allows_player_interaction(device_index, player_index))
			{
				return false;
			}

			return player_consider_device_interaction(player_index, device_index, out_action_context);
		}
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0CForgeDeviceManager@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0IGameSystem@@QAE@XZ"); no body to assert in

/* ---------- private code */

void machine_update_hook(long machine_index) // 0x108CF450
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?machine_update_hook@@YAXJ@Z");
	// `anonymous-namespace'::machine_update_hook
	// long machine_index;
	// float old_proximity_radius;
	// s_object_data *machine;
	// float old_position_time;
	// void (*const machine_update)(long);
	// EForgeDeviceType device_type;
	// CForgeDeviceManager &deviceManager;
	// s_machine_definition *machine_def;
	// CForgeDeviceObjectProperties *device_properties;
	// s_multiplayer_object_properties *properties;
	// float old_door_open_time;
		// float radius;
		// float delayTime;
	// function call : void (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void *(*const)(unsigned long, long)
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : void (*const)(long)

	void (*const machine_update)(long) = reinterpret_cast<void (*)(long)>(0xBB5500);
	CForgeDeviceManager &deviceManager = Utils::Singleton<CForgeDeviceManager>::Instance();
	if (!deviceManager.IsForgeDevice(machine_index))
	{
		machine_update(machine_index);
		return;
	}
	s_object_data *machine = object_try_and_get_and_verify_type(machine_index, 0x100);
	s_machine_definition *machine_def = (s_machine_definition *)tag_get('mach', machine->definition_index);
	s_multiplayer_object_properties *properties = object_get_multiplayer(machine_index);
	CForgeDeviceObjectProperties *device_properties = (CForgeDeviceObjectProperties *)((unsigned char *)properties + 0x14);
	float old_position_time = machine_def->position_time;
	float old_door_open_time = machine_def->door_open_time;
	float old_proximity_radius = machine_def->proximity_radius;
	EForgeDeviceType device_type = deviceManager.GetDeviceType(machine_index);
	if (device_type == 2)
		machine_def->position_time = device_properties->GetGearTurnRate();
	else if (device_type == 1)
		machine_def->door_open_time = device_properties->GetDoorOpenTime();
	{
		float radius = device_properties->GetTriggerRadius();
		if (radius != 0.0f)
			machine_def->proximity_radius = radius;
	}
	{
		float delayTime = device_properties->GetDelayTime();
		if (delayTime != 0.0f)
			machine_def->delay_time = delayTime;
	}
	machine_update(machine_index);
	machine_def->position_time = old_position_time;
	machine_def->door_open_time = old_door_open_time;
	machine_def->proximity_radius = old_proximity_radius;
}

bool device_block_interaction_odst_hook(long object_index) // 0x108CF0C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?device_block_interaction_odst_hook@@YA_NJ@Z");
	// `anonymous-namespace'::device_block_interaction_odst_hook
	// long object_index;
	// s_device_data *device;
	// s_device_group_datum *device_group;
	// s_device_data *parent_device;
	// s_device_definition *parent_device_definition;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void *(*const)(unsigned long, long)

	s_device_data *device = (s_device_data *)object_get(object_index);
	if (!device || device->parent_object_index == -1)
		return false;

	s_device_data *parent_device = (s_device_data *)object_try_and_get_and_verify_type(device->parent_object_index, 0x310);
	if (!parent_device)
		return false;

	if (parent_device->position_group_index == -1 || parent_device->position_group_index != device->position_group_index)
		return false;

	s_device_definition *parent_device_definition = (s_device_definition *)tag_get(0x64657669, parent_device->definition_index);
	if (!(parent_device_definition->device_flags & 0x80000000))
		return false;

	s_device_group_datum *device_group = device_groups_get()->try_and_get(parent_device->position_group_index);
	if (device_group->value == 0.0f)
		return false;
	return true;
}

bool device_allows_player_interaction(long device_index, long player_index) // 0x108CEF50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?device_allows_player_interaction@@YA_NJJ@Z");
	// `anonymous-namespace'::device_allows_player_interaction
	// long player_index;
		// c_game_engine *game_engine;
			// s_multiplayer_object_properties *multiplayer_properties;
				// short player_team;
				// bool is_neutral;
				// long (*const get_player_team_desginator)(c_game_engine *, __int32);
				// short device_team;
	// function call : bool (*)()
	// function call : c_game_engine *(*const)()
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : long (*const)(c_game_engine *, __int32)

	if (game_is_campaign())
		return true;
	c_game_engine *game_engine = ((c_game_engine *(*)())0x5CE150)();
	if (game_engine && player_index != -1)
	{
		s_multiplayer_object_properties *multiplayer_properties = object_get_multiplayer(device_index);
		if (multiplayer_properties)
		{
			long (__thiscall *const get_player_team_desginator)(c_game_engine *, __int32) = reinterpret_cast<long (__thiscall *)(c_game_engine *, __int32)>(*(void **)(*(unsigned char **)game_engine + 0xB4));
			short player_team = get_player_team_desginator(game_engine, player_index);
			short device_team = static_cast<short>(multiplayer_properties->team_designator);
			bool is_neutral = device_team == 8;
			if (!is_neutral && player_team != device_team)
				return false;
		}
	}
	return true;
}

bool device_allows_object_interaction(long device_index, long object_index) // 0x108CEE80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?device_allows_object_interaction@@YA_NJJ@Z");
	// `anonymous-namespace'::device_allows_object_interaction
	// long object_index;
		// long player_index;
		// long unit_index;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)

	if (object_try_and_get_and_verify_type(object_index, 0x2003))
	{
		long unit_index = unit_get_ultimate_motion_control_unit_index(object_index);
		long player_index = unit_get_current_or_last_weak_player_index(unit_index);
		if (!device_allows_player_interaction(device_index, player_index))
		{
			return false;
		}
	}

	return true;
}

void device_touched_hook(long device_index, long unit_index, bool a3) // 0x108CF270
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?device_touched_hook@@YAXJJ_N@Z");
	// `anonymous-namespace'::device_touched_hook
	// bool a3;
	// void (*const device_touched)(long, long, bool);
	// function call : void (*const)(long, long, bool)

	void (__cdecl *const device_touched)(long, long, bool) = (void(__cdecl *const)(long, long, bool))0xb94500;

	if (!device_allows_object_interaction(device_index, unit_index))
	{
		return;
	}

	device_touched(device_index, unit_index, a3);
}

bool machine_door_test_object_hook(long machine_index, long const *object_indices, short object_indices_count) // 0x108CF300
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?machine_door_test_object_hook@@YA_NJPBJF@Z");
	// `anonymous-namespace'::machine_door_test_object_hook
	// static ...; // 0x108CF3DC
	// long machine_index;
	// long const *object_indices;
	// short object_indices_count;
	// bool (*const machine_door_test_object)(long, long const *, short);
	// long new_object_indices[16];
	// short new_object_indices_count;
		// long i;
			// long object_index;
	// function call : bool (*const)(long, long const *, short)

	bool (*const machine_door_test_object)(long, long const *, short) = reinterpret_cast<bool (*)(long, long const *, short)>(0xBB4FF0);
	long new_object_indices[16];
	short new_object_indices_count = 0;
	for (long i = 0; i < object_indices_count; i++)
	{
		long object_index = object_indices[i];
		if (!device_allows_object_interaction(machine_index, object_index))
			continue;
		new_object_indices[new_object_indices_count++] = object_index;
	}
	return machine_door_test_object(machine_index, new_object_indices, new_object_indices_count);
}

void control_touched_hook(long device_index, long unit_index) // 0x108CEDB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?control_touched_hook@@YAXJJ@Z");
	// `anonymous-namespace'::control_touched_hook
	// long unit_index;
	// s_object_data *control;
	// s_control_definition *control_definition;
	// void (*const control_toggle)(long);
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(long)

	void (*const device_touched)(long) = reinterpret_cast<void (*)(long)>(0xBBFC30);
	s_object_data *control = object_get(device_index);
	s_control_definition *control_definition = (s_control_definition *)tag_get(0x6374726C, control->definition_index);
	if (control_definition->control_type == 4)
	{
		return;
	}

	if (!control_definition->triggers_when)
	{
		device_touched(device_index);
	}
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template CForgeDeviceManager & Utils::Singleton<CForgeDeviceManager>::Instance();
