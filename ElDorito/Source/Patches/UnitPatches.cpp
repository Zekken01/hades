/* ---------- headers */

#include "hades/hades.h"

#include "Blam/animations/animation_definitions.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/aim_target.hpp"
#include "Blam/game/game_time.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/items/weapon_definitions.hpp"
#include "Blam/items/weapons.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/objects/target_tracking.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/unit_definitions.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Modules/ModuleSettings.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
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
#include <functional>
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

struct c_aim_target_object;
struct c_aim_target_simulation_entity;
struct c_tracked_target;
struct real_point3d;
struct real_vector3d;
struct s_aim_assist_targeting_result;
struct s_game_time_globals;
struct s_multiplayer_object_properties;
struct s_object_data;
struct s_object_marker;
struct s_unit_data;
struct s_unit_definition;
struct s_unit_target_tracking_block;
struct s_weapon_data;
struct s_weapon_definition;
namespace Modules
{
	class ModuleSettings;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Unit {}
	using namespace Patches::Unit;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern long (*const game_seconds_to_ticks_round)(float);  // hades: added for 0x106A2030

extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x106A34B0

extern s_multiplayer_object_properties *(*const object_get_multiplayer)(unsigned long object_index);  // hades: added for 0x106A3C70

extern bool (*const game_is_distributed)();  // hades: added for 0X106A2680

extern bool unit_compute_function_value_hook(long unit_index, unsigned long function_name, long definition_index, float *out_value, bool *out_value_valid, bool *a6);
extern void unit_action_assassinate_event_hook(long mover_index, e_action action_type, c_flags<enum e_animation_frame_event_types,unsigned long> frame_events);
extern void unit_action_assassinate_finished_hook(__int32 mover_index, e_action action_type);
extern void unit_action_assassinate_interrupted_hook(long mover_index, e_action action_type);
extern void unit_update_assassination_events(long unit_index);
extern void unit_update_vision_mode_hook(long unit_index);
extern void unit_update_target_tracking_hook(long unit_index);
namespace Patches
{
	namespace Unit
	{
		extern void ApplyAll();
	}
}

extern "C" void unit_send_message_to_first_person_ho_hook(long unit_index, e_unit_messages message);
extern "C" void unit_update_target_pivot_aiming(long unit_index, long ultimate_weapon_control_unit_index);
extern "C" void unit_update_target_aiming(long unit_index);
extern "C" void __fastcall c_tracked_target__update_internal_hook(c_tracked_target *thisptr, void *__formal, c_aim_target_object *target_object, s_unit_target_tracking_block *tracking_parameters, long behavior);
extern "C" void unit_update_team_index_hook(long unit_index);
extern "C" long unit_get_last_associated_weak_player_index_for_appearance(long unit_index);
extern "C" bool __fastcall c_tracked_target__set_from_weapon_fire_event_hook(c_tracked_target *thisptr, void *__formal, c_aim_target_simulation_entity *aim_target, s_unit_target_tracking_block *tracking_parameters);
extern "C" void giant_object_early_mover_delete_early_mover_childern_hook(long object_index);
extern "C" void object_detach_predicted_objects_hook(__int32 object_index);

/* ---------- globals */

template<typename t_arg0> static t_arg0 *object_get(unsigned long object_index) { return (t_arg0 *)object_get(object_index); }  // hades: a file-local template in the original (undecorated `object_get<T>`), defined so it is emitted;  // hades: added for 0X106A31B0
extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0X106A2D50
extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0X106A2C30

namespace Utils
{
	Modules::ModuleSettings *Utils::Singleton<Modules::ModuleSettings>::m_instance; // 0x11386010
}

/* ---------- private variables */

/* ---------- public code */

bool unit_compute_function_value_hook(long unit_index, unsigned long function_name, long definition_index, float *out_value, bool *out_value_valid, bool *a6) // 0x106A2E70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_compute_function_value_hook@@YA_NJKJPAMPA_N1@Z");
	// bool *a6;
	// bool (*const unit_compute_function_value)(long, unsigned long, long, float *, bool *, bool *);
		// s_unit_data *unit;
			// s_game_time_globals *time_globals;
			// float function_value;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : bool (*const)(long, unsigned long, long, float *, bool *, bool *)

	bool (*const unit_compute_function_value)(long, unsigned long, long, float *, bool *, bool *) = reinterpret_cast<bool (*)(long, unsigned long, long, float *, bool *, bool *)>(0xB3DA70);
	if (function_name == 0x9C65 || function_name == 0x9C66)
	{
		s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003);
		if (unit->assassination_event_flags.test(function_name == 0x9C65 ? (e_assassination_event_flags)0 : (e_assassination_event_flags)1))
		{
			s_game_time_globals *time_globals = game_time_get_globals();
			float function_value = unit->assassination_event_ticks * time_globals->tick_length / 0.5f;
			if (function_value > 1.0f)
				function_value = 1.0f;
			*out_value = function_value;
			*out_value_valid = true;
		}
		else
		{
			*out_value = 0.0f;
			*out_value_valid = false;
		}
		return *out_value_valid;
	}
	return unit_compute_function_value(unit_index, function_name, definition_index, out_value, out_value_valid, a6);
}

void unit_action_assassinate_event_hook(long mover_index, e_action action_type, c_flags<enum e_animation_frame_event_types,unsigned long> frame_events) // 0x106A28A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_action_assassinate_event_hook@@YAXJW4e_action@@V?$c_flags@W4e_animation_frame_event_types@@K@@@Z");
	// c_flags<enum e_animation_frame_event_types,unsigned long> frame_events;
		// s_unit_data *unit;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, long, bool)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : bool (*const)()
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long)

	if (frame_events.test(_animation_frame_event_drop_weapon_key))
	{
		s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(mover_index, 0x2003);
		((void (*)(long, long, bool))0xB856C0)(mover_index, action_type, *(bool *)offset_pointer(unit, unit->action_state_storage.offset + 0x65));
	}
	if (frame_events.test(_animation_frame_event_assassination_a))
	{
		s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(mover_index, 0x2003);
		true ? (unit->assassination_event_flags |= 1) : (unit->assassination_event_flags &= ~1);
	}
	if (frame_events.test(_animation_frame_event_assassination_b))
	{
		s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(mover_index, 0x2003);
		true ? (unit->assassination_event_flags |= 2) : (unit->assassination_event_flags &= ~2);
	}
	if (((bool (*)())0x5319C0)())
	{
		if (frame_events.test(_animation_frame_event_primary_key))
		{
			s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(mover_index, 0x2003);
			if (unit && mover_index != *(long *)offset_pointer(unit, unit->action_state_storage.offset + 0x5C))
				((void (*)(long))0xB85A10)(mover_index);
		}
		if (frame_events.test(_animation_frame_event_ragdoll_key))
		{
			s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(mover_index, 0x2003);
			if (unit && mover_index != *(long *)offset_pointer(unit, unit->action_state_storage.offset + 0x5C))
				((void (*)(long))0xB85AB0)(mover_index);
		}
	}
}

void unit_action_assassinate_finished_hook(__int32 mover_index, e_action action_type) // 0x106A2C30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_action_assassinate_finished_hook@@YAXHW4e_action@@@Z");
	// e_action action_type;
	// void (*const unit_action_assassinate_finished)(long, e_action);
	// s_unit_data *unit;
	// s_game_time_globals *time_globals;
	// function call : void (*const)(long, e_action)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)

	void (*const unit_action_assassinate_finished)(long, e_action) = (void (*const)(long, e_action))0xb841b0;
	s_game_time_globals *time_globals = game_time_get_globals();

	unit_action_assassinate_finished(mover_index, action_type);

	s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(mover_index, 0x2003);

	true ? unit->assassination_event_flags |= 4 : unit->assassination_event_flags &= ~4;

	unit->assassination_event_ticks = 0.5f / time_globals->tick_length;
}

void unit_action_assassinate_interrupted_hook(long mover_index, e_action action_type) // 0x106A2D50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_action_assassinate_interrupted_hook@@YAXJW4e_action@@@Z");
	// e_action action_type;
	// void (*const unit_action_assassinate_interrupted)(long, e_action);
	// s_unit_data *unit;
	// s_game_time_globals *time_globals;
	// function call : void (*const)(long, e_action)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)

	void (*const unit_action_assassinate_interrupted)(long, e_action) = (void (*const)(long, e_action))0xb84300;
	s_game_time_globals *time_globals = game_time_get_globals();

	unit_action_assassinate_interrupted(mover_index, action_type);

	s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(mover_index, 0x2003);

	true ? unit->assassination_event_flags |= 4 : unit->assassination_event_flags &= ~4;

	unit->assassination_event_ticks = 0.5f / time_globals->tick_length;
}

void unit_update_assassination_events(long unit_index) // 0x106A32F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_update_assassination_events@@YAXJ@Z");
	// long unit_index;
	// s_unit_data *unit;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)

	s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003);
	if (unit->assassination_event_flags.test((e_assassination_event_flags)2))
	{
		if (unit->assassination_event_ticks)
			unit->assassination_event_ticks--;
		else if (unit->assassination_event_flags != 0)
			unit->assassination_event_flags = 0;
	}
	else if (unit->assassination_event_flags.test((e_assassination_event_flags)0) || unit->assassination_event_flags.test((e_assassination_event_flags)1))
	{
		if (unit->assassination_event_ticks != 0xFF)
			unit->assassination_event_ticks++;
	}
}

void unit_update_vision_mode_hook(long unit_index) // 0x106A3D40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_update_vision_mode_hook@@YAXJ@Z");
	// long unit_index;
	// void (*const unit_update_vision_mode)(long);
	// function call : void (*const)(long)

	void (__cdecl *const unit_update_vision_mode)(long) = (void(__cdecl *const)(long))0xb4c4a0;

	unit_update_vision_mode(unit_index);
	unit_update_assassination_events(unit_index);
}

void unit_update_target_tracking_hook(long unit_index) // 0x106A3C00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_update_target_tracking_hook@@YAXJ@Z");
	// long unit_index;
	// void (*const unit_update_target_tracking)(long);
	// function call : void (*const)(long)

	void (__cdecl *const unit_update_target_tracking)(long) = (void(__cdecl *const)(long))0xb4c260;

	unit_update_target_aiming(unit_index);
	unit_update_target_tracking(unit_index);
}

namespace Patches
{
	namespace Unit
	{
		void ApplyAll() // 0x106A11F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Unit@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x7BC67A, giant_object_early_mover_delete_early_mover_childern_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x72D4E0, object_detach_predicted_objects_hook).Apply();
			Pointer(0x194809C).Write(unit_compute_function_value_hook);
			Hook(0x644A16, unit_compute_function_value_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x761AA5, unit_compute_function_value_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7840B0, unit_action_assassinate_event_hook).Apply();
			Pointer(0x194977C).Write(unit_action_assassinate_finished_hook);
			Pointer(0x1949780).Write(unit_action_assassinate_interrupted_hook);
			Hook(0x749FC0, unit_update_vision_mode_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x748440, unit_send_message_to_first_person_ho_hook).Apply();
			Hook(0x74A30A, unit_update_target_tracking_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7751C0, c_tracked_target__update_internal_hook).Apply();
			Hook(0x749FAE, unit_update_team_index_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x774EB0, c_tracked_target__set_from_weapon_fire_event_hook).Apply();
			Hook(0x744340, unit_get_last_associated_weak_player_index_for_appearance).Apply();
		}
	}
}

/* ---------- private code */

extern "C" void unit_send_message_to_first_person_ho_hook(long unit_index, e_unit_messages message) // 0x106A31B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_unit_send_message_to_first_person_ho_hook");
	// unit_send_message_to_first_person_ho_hook
	// e_unit_messages message;
	// s_unit_data *unit;
		// long i;
			// long weapon_index;
	// function call : void (*const)(long, long, e_unit_messages, long)

	if (Utils::Singleton<Modules::ModuleSettings>::Instance().VarFpJumpLandAnimationsDisabled->ValueInt != 1)
	{
		return;
	}

	s_unit_data *unit = object_get<s_unit_data>(unit_index);

	for (long i = 0; i < 2; i++)
	{
		if (unit->current_weapon_set.indices[i] != -1)
		{
			long weapon_index = unit->weapon_object_indices[unit->current_weapon_set.indices[i]];

			((void (*)(long, long, e_unit_messages, long))0xa9c010)(unit_index, weapon_index, message, i);
		}
	}
}

extern "C" void unit_update_target_pivot_aiming(long unit_index, long ultimate_weapon_control_unit_index) // 0x106A3630
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_unit_update_target_pivot_aiming");
	// unit_update_target_pivot_aiming
	// static ...; // 0x106A3AB5
	// static ...; // 0x106A3AAD
	// static ...; // 0x106A3AA4
	// static ...; // 0x106A3A74
	// static ...; // 0x106A3A6C
	// long unit_index;
	// long ultimate_weapon_control_unit_index;
	// s_unit_data *unit;
	// s_unit_data *ultimate_weapon_control_unit;
	// s_object_marker pivot_marker;
	// long (*const weapon_get_effect_object_index)(long);
	// real_vector3d forward;
	// real_point3d position;
	// long (*const weapon_barrel_get_marker_name)(long, long);
	// s_unit_definition *unit_definiton;
	// s_object_marker barrel_marker;
	// unsigned long barrel_marker_name;
	// s_unit_data *weapon_control_unit;
	// long effect_object_index;
	// long primary_weapon_index;
	// s_weapon_definition *weapon_definition;
	// s_weapon_data *weapon;
	// long ultimate_primary_weapon_index;
	// bool (*const player_aim_projectile)(long, s_aim_assist_targeting_result *, long, long, bool, real_point3d *, real_point3d *, real_vector3d *);
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void *(*const)(unsigned long, long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : long (*const)(long, short)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void *(*const)(unsigned long, long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : long (*const)(long, short)
	// function call : long (*const)(long)
	// function call : long (*const)(long, long)
	// function call : short (*const)(long, unsigned long, s_object_marker *, short)
	// function call : short (*const)(long, unsigned long, s_object_marker *, short)
	// function call : bool (*const)(long, s_aim_assist_targeting_result *, long, long, bool, real_point3d *, real_point3d *, real_vector3d *)

	bool (*const player_aim_projectile)(long, s_aim_assist_targeting_result *, long, long, bool, real_point3d *, real_point3d *, real_vector3d *) = (bool (*)(long, s_aim_assist_targeting_result *, long, long, bool, real_point3d *, real_point3d *, real_vector3d *))0x58EA50;
	long (*const weapon_get_effect_object_index)(long) = (long (*)(long))0xB62B20;
	long (*const weapon_barrel_get_marker_name)(long, long) = (long (*)(long, long))0xB606D0;
	s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003);
	s_unit_definition *unit_definiton = (s_unit_definition *)tag_get('unit', unit->definition_index);
	s_unit_data *ultimate_weapon_control_unit = (s_unit_data *)object_try_and_get_and_verify_type(ultimate_weapon_control_unit_index, 0x2003);
	if (ultimate_weapon_control_unit->player_index == -1)
		return;
	if (!unit_definiton->target_aiming_pivot_marker_name)
		return;
	long primary_weapon_index = ((long (*const)(long, short))0xB454D0)(unit_index, unit->current_weapon_set.indices[0]);
	if (primary_weapon_index == -1)
		return;
	s_weapon_data *weapon = (s_weapon_data *)object_try_and_get_and_verify_type(primary_weapon_index, 4);
	s_weapon_definition *weapon_definition = (s_weapon_definition *)tag_get('weap', weapon->definition_index);
	if (!weapon_definition->barrels.count || weapon_definition->barrels->initial_projectile.index == -1)
		return;
	s_unit_data *weapon_control_unit = (s_unit_data *)object_try_and_get_and_verify_type(unit->weapon_control_unit_index, 0x2003);
	long ultimate_primary_weapon_index = ((long (*const)(long, short))0xB454D0)(ultimate_weapon_control_unit_index, weapon_control_unit->current_weapon_set.indices[0]);
	long effect_object_index = weapon_get_effect_object_index(primary_weapon_index);
	s_object_marker barrel_marker;
	s_object_marker pivot_marker;
	unsigned long barrel_marker_name = weapon_barrel_get_marker_name(primary_weapon_index, 0);
	if (!((short (*const)(long, unsigned long, s_object_marker *, short))0xB2E3C0)(effect_object_index, barrel_marker_name, &barrel_marker, 1))
		return;
	if (!((short (*const)(long, unsigned long, s_object_marker *, short))0xB2E3C0)(effect_object_index, unit_definiton->target_aiming_pivot_marker_name, &pivot_marker, 1))
		return;
	real_vector3d forward = barrel_marker.world_matrix.forward;
	real_point3d position = pivot_marker.world_matrix.position;
	player_aim_projectile(ultimate_weapon_control_unit->player_index, &ultimate_weapon_control_unit->aim_assist_data, weapon_definition->barrels->initial_projectile.index, 1, primary_weapon_index == ultimate_primary_weapon_index, &position, &position, &forward);
	unit->desired_aiming_vector = forward;
	unit->desired_looking_vector = forward;
}

extern "C" void unit_update_target_aiming(long unit_index) // 0x106A34B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_unit_update_target_aiming");
	// unit_update_target_aiming
	// long unit_index;
	// s_unit_data *unit;
	// s_unit_definition *unit_definiton;
		// long ultimate_weapon_control_unit_index;
		// s_unit_data *ultimate_weapon_control_unit;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void *(*const)(unsigned long, long)
	// function call : long (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)

	static long (*const unit_get_ultimate_weapon_control_unit_index)(long) = reinterpret_cast<long (*)(long)>(0xB44600);
	s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003);
	s_unit_definition *unit_definiton = (s_unit_definition *)tag_get('unit', unit->definition_index);
	if (unit->weapon_control_unit_index != -1 && unit->weapon_control_unit_index != unit_index)
	{
		long ultimate_weapon_control_unit_index = unit_get_ultimate_weapon_control_unit_index(unit_index);
		s_unit_data *ultimate_weapon_control_unit = (s_unit_data *)object_try_and_get_and_verify_type(ultimate_weapon_control_unit_index, 0x2003);
		if (ultimate_weapon_control_unit)
		{
			memcpy(&unit->aim_assist_data, &ultimate_weapon_control_unit->aim_assist_data, sizeof(s_aim_assist_targeting_result));
			unit_update_target_pivot_aiming(unit_index, ultimate_weapon_control_unit_index);
		}
	}
}

extern "C" void __fastcall c_tracked_target__update_internal_hook(c_tracked_target *thisptr, void *__formal, c_aim_target_object *target_object, s_unit_target_tracking_block *tracking_parameters, long behavior) // 0x106A2030
{
	mangled_x86(MANGLED_KNOWN_GOOD, "@c_tracked_target__update_internal_hook@20");
	// c_tracked_target__update_internal_hook
// $LN5:
	// c_tracked_target *thisptr;
	// void *__formal;
	// c_aim_target_object *target_object;
	// s_unit_target_tracking_block *tracking_parameters;
	// long behavior;
		// short decay_ticks;
	// function call : bool (*const)(c_aim_target_object *)
	// function call : bool (*const)(c_tracked_target *, c_aim_target_object *)
	// function call : long (*const)(float)
	// function call : long (*const)(float)
	// function call : bool (*const)(c_aim_target_object *)
	// function call : long (*const)(float)
	// function call : long (*const)(float)
	// function call : bool (*const)(c_tracked_target *, c_aim_target_object *)
	// function call : long (*const)(float)
	// function call : long (*const)(c_tracked_target *)
	// function call : bool (*const)(c_tracked_target *, c_aim_target_object *)
	// function call : long (*const)(float)
	// function call : long (*const)(float)
	// function call : bool (*const)(c_tracked_target *, c_aim_target_object *)
	// function call : long (*const)(c_tracked_target *)
	// function call : long (*const)(float)
	// function call : long (*const)(float)

	if (behavior == 2 && ((bool (__thiscall *)(c_aim_target_object *))0x589020)(target_object) && !((bool (__thiscall *)(c_tracked_target *, c_aim_target_object *))0xB74F30)(thisptr, target_object))
	{
		thisptr->state = 1;
		thisptr->aim_target = *target_object;
		thisptr->acquire_timer = game_seconds_to_ticks_round(tracking_parameters->acquire_time);
		thisptr->hold_timer = game_seconds_to_ticks_round(tracking_parameters->grace_time);
		thisptr->acquire_time = (float)thisptr->acquire_timer;
	}
	else
	{
		switch (thisptr->state)
		{
		case 0:
			if (behavior != 1 && ((bool (__thiscall *)(c_aim_target_object *))0x589020)(target_object))
			{
				thisptr->state = 1;
				thisptr->aim_target = *target_object;
				thisptr->acquire_timer = game_seconds_to_ticks_round(tracking_parameters->acquire_time);
				thisptr->hold_timer = game_seconds_to_ticks_round(tracking_parameters->grace_time);
				thisptr->acquire_time = (float)thisptr->acquire_timer;
			}
			break;
		case 1:
			if (((bool (__thiscall *)(c_tracked_target *, c_aim_target_object *))0xB74F30)(thisptr, target_object))
			{
				thisptr->hold_timer = game_seconds_to_ticks_round(tracking_parameters->grace_time);
				thisptr->aim_target = *target_object;
				if (thisptr->acquire_timer > 0)
					thisptr->acquire_timer--;
				if (thisptr->acquire_timer == 0)
				{
					thisptr->state = 2;
					thisptr->locked = true;
				}
			}
			else
			{
				if (thisptr->hold_timer > 0)
					thisptr->hold_timer--;
				if (thisptr->hold_timer == 0)
					((void (__thiscall *)(c_tracked_target *))0xB74D70)(thisptr);
			}
			break;
		case 2:
			if (((bool (__thiscall *)(c_tracked_target *, c_aim_target_object *))0xB74F30)(thisptr, target_object))
			{
				thisptr->hold_timer = game_seconds_to_ticks_round(tracking_parameters->grace_time);
				thisptr->aim_target = *target_object;
			}
			else
			{
				if (thisptr->hold_timer > 0)
					thisptr->hold_timer--;
				if (thisptr->hold_timer == 0)
				{
					thisptr->state = 3;
					thisptr->acquire_timer = game_seconds_to_ticks_round(tracking_parameters->decay_time);
					thisptr->acquire_time = (float)thisptr->acquire_timer;
				}
			}
			break;
		case 3:
			if (!((bool (__thiscall *)(c_tracked_target *, c_aim_target_object *))0xB74F30)(thisptr, target_object))
			{
				if (thisptr->hold_timer > 0)
					thisptr->hold_timer--;
				else if (thisptr->acquire_timer > 0)
					thisptr->acquire_timer--;
				if (thisptr->acquire_timer == 0 && thisptr->hold_timer == 0)
					((void (__thiscall *)(c_tracked_target *))0xB74D70)(thisptr);
			}
			else
			{
				thisptr->hold_timer = game_seconds_to_ticks_round(tracking_parameters->grace_time);
				short decay_ticks = game_seconds_to_ticks_round(tracking_parameters->decay_time);
				if (thisptr->acquire_timer < decay_ticks)
					thisptr->acquire_timer++;
				if (thisptr->acquire_timer == decay_ticks)
					thisptr->state = 2;
			}
			break;
		}
	}
}

extern "C" void unit_update_team_index_hook(long unit_index) // 0x106A3C70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_unit_update_team_index_hook");
	// unit_update_team_index_hook
	// long unit_index;
	// s_unit_data *unit;
	// long (*const game_engine_team_designator_to_team_index)(long);
	// void (*const unit_update_team_index)(long);
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : void (*const)(long)

	long (*const game_engine_team_designator_to_team_index)(long) = reinterpret_cast<long (*)(long)>(0x556950);
	s_unit_data *unit = object_get<s_unit_data>(unit_index);
	if (unit->map_variant_index != -1)
	{
		unit->team = (short)object_get_multiplayer(unit_index)->team_designator;
	}

	void (*const unit_update_team_index)(long) = reinterpret_cast<void (*)(long)>(0xB4C300);
	unit_update_team_index(unit_index);
}

extern "C" long unit_get_last_associated_weak_player_index_for_appearance(long unit_index) // 0x106A3030
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_unit_get_last_associated_weak_player_index_for_appearance");
	// unit_get_last_associated_weak_player_index_for_appearance
	// long unit_index;
	// s_unit_data *unit;
		// s_unit_data *hologram_creator_unit;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)

	s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003);
	if (!unit)
		return -1;
	if (unit->player_index != -1)
		return unit->player_index;
	if (unit->last_weak_player_index != -1)
		return unit->last_weak_player_index;
	if (unit->hologram_creator_weak_unit_index != -1)
	{
		s_unit_data *hologram_creator_unit = (s_unit_data *)object_try_and_get_and_verify_type(unit->hologram_creator_weak_unit_index, 0x2003);
		if (hologram_creator_unit)
		{
			if (hologram_creator_unit->player_index != -1)
				return hologram_creator_unit->player_index;
			if (hologram_creator_unit->last_weak_player_index != -1)
				return hologram_creator_unit->last_weak_player_index;
		}
	}
	return -1;
}

extern "C" bool __fastcall c_tracked_target__set_from_weapon_fire_event_hook(c_tracked_target *thisptr, void *__formal, c_aim_target_simulation_entity *aim_target, s_unit_target_tracking_block *tracking_parameters) // 0x106A1FB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "@c_tracked_target__set_from_weapon_fire_event_hook@16");
	// c_tracked_target__set_from_weapon_fire_event_hook
	// s_unit_target_tracking_block *tracking_parameters;
	// function call : bool (*const)(c_aim_target_simulation_entity *, c_aim_target_object *)

	if (((bool (__thiscall *const)(c_aim_target_simulation_entity *, c_aim_target_object *))0x589520)(aim_target, &thisptr->aim_target))
	{
		return true;
	}
	else
	{
		return false;
	}
}

extern "C" void giant_object_early_mover_delete_early_mover_childern_hook(long object_index) // 0x106A2680
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_giant_object_early_mover_delete_early_mover_childern_hook");
	// giant_object_early_mover_delete_early_mover_childern_hook
	// long object_index;
	// void (*const object_early_mover_delete_early_mover_childern)(long);
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : void (*const)(long)

	if (game_is_distributed() && ((bool (*)())0x531d70)())
	{
	}
	else
	{
		void (*const delete_early_mover_childern)(long) = (void (*const)(long))0xb97f90;

		delete_early_mover_childern(object_index);
	}
}

extern "C" void object_detach_predicted_objects_hook(__int32 object_index) // 0x106A2720
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_object_detach_predicted_objects_hook");
	// object_detach_predicted_objects_hook
	// __int32 object_index;
	// void (*const object_detach_immediate)(long);
	// long predicted_object_index;
	// long (*const find_first_predicted_object_recursive)(long);
	// void (*const object_type_detach_from_parent)(long);
		// s_object_data *predicted_object;
	// function call : long (*const)(long)
	// function call : void (*const)(long)
	// function call : void (*const)(long)
	// function call : long (*const)(long)

	long (*const find_first_predicted_object_recursive)(long) = reinterpret_cast<long (*)(long)>(0xB286C0);
	void (*const object_type_detach_from_parent)(long) = reinterpret_cast<void (*)(long)>(0xB735A0);
	void (*const object_detach_immediate)(long) = reinterpret_cast<void (*)(long)>(0xB2D2C0);
	long predicted_object_index = find_first_predicted_object_recursive(object_index);
	if (predicted_object_index == object_index)
		return;
	while (predicted_object_index != -1)
	{
		s_object_data *predicted_object = object_get(predicted_object_index);
		if (!predicted_object)
			return;
		if (predicted_object->parent_object_index != -1)
		{
			object_type_detach_from_parent(predicted_object_index);
			if (predicted_object->parent_object_index != -1)
				object_detach_immediate(predicted_object_index);
		}
		predicted_object_index = find_first_predicted_object_recursive(object_index);
	}
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Modules::ModuleSettings & Utils::Singleton<Modules::ModuleSettings>::Instance();
template bool c_flags<enum e_animation_frame_event_types,unsigned long>::test(e_animation_frame_event_types) const;
template bool c_flags<enum e_assassination_event_flags,unsigned char>::operator!=(unsigned char const &) const;
template bool c_flags<enum e_assassination_event_flags,unsigned char>::operator==(unsigned char const &) const;
template bool c_flags<enum e_assassination_event_flags,unsigned char>::test(e_assassination_event_flags) const;
template c_flags<enum e_assassination_event_flags,unsigned char> & c_flags<enum e_assassination_event_flags,unsigned char>::operator&=(__int32 const);
template c_flags<enum e_assassination_event_flags,unsigned char> & c_flags<enum e_assassination_event_flags,unsigned char>::operator=(unsigned char const &);
template c_flags<enum e_assassination_event_flags,unsigned char> & c_flags<enum e_assassination_event_flags,unsigned char>::operator|=(__int32 const);
template c_flags<enum e_multiplayer_team_designator,short>::operator short() const;
template s_weapon_barrel_definition * c_tag_block<s_weapon_barrel_definition>::operator->();
template void Pointer::Write<bool (__cdecl*)(long,unsigned long,long,float *,bool *,bool *)>(bool (*const value)(long, unsigned long, long, float *, bool *, bool *)) const;
template void Pointer::Write<void (__cdecl*)(int,enum e_action)>(void (*const value)(__int32, e_action)) const;
template void Pointer::Write<void (__cdecl*)(long,enum e_action)>(void (*const value)(long, e_action)) const;
