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
extern "C" void c_tracked_target__update_internal_hook(c_tracked_target *thisptr, void *__formal, c_aim_target_object *target_object, s_unit_target_tracking_block *tracking_parameters, long behavior);
extern "C" void unit_update_team_index_hook(long unit_index);
extern "C" long unit_get_last_associated_weak_player_index_for_appearance(long unit_index);
extern "C" bool c_tracked_target__set_from_weapon_fire_event_hook(c_tracked_target *thisptr, void *__formal, c_aim_target_simulation_entity *aim_target, s_unit_target_tracking_block *tracking_parameters);
extern "C" void giant_object_early_mover_delete_early_mover_childern_hook(long object_index);
extern "C" void object_detach_predicted_objects_hook(__int32 object_index);

/* ---------- globals */

namespace Utils
{
	Modules::ModuleSettings *Utils::Singleton<Modules::ModuleSettings>::m_instance; // 0x11386010
}

/* ---------- private variables */

/* ---------- public code */

_extern bool _sub_106A2E70(long, unsigned long, long, float *, bool *, bool *);
bool unit_compute_function_value_hook(long unit_index, unsigned long function_name, long definition_index, float *out_value, bool *out_value_valid, bool *a6) // 0x106A2E70
{
	mangled_x86(MANGLED_TODO, "?unit_compute_function_value_hook@@YA_NJKJPAMPA_N1@Z");
	// bool *a6;
	// bool (*const unit_compute_function_value)(long, unsigned long, long, float *, bool *, bool *);
	{
		// s_unit_data *unit;
		{
			// s_game_time_globals *time_globals;
			// float function_value;
		}
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : bool (*const)(long, unsigned long, long, float *, bool *, bool *)
	todo("implement");
	bool __result = _sub_106A2E70(unit_index, function_name, definition_index, out_value, out_value_valid, a6);
	return __result;
}

_extern void _sub_106A28A0(long, e_action, c_flags<enum e_animation_frame_event_types,unsigned long>);
void unit_action_assassinate_event_hook(long mover_index, e_action action_type, c_flags<enum e_animation_frame_event_types,unsigned long> frame_events) // 0x106A28A0
{
	mangled_x86(MANGLED_TODO, "?unit_action_assassinate_event_hook@@YAXJW4e_action@@V?$c_flags@W4e_animation_frame_event_types@@K@@@Z");
	// c_flags<enum e_animation_frame_event_types,unsigned long> frame_events;
	{
		// s_unit_data *unit;
	}
	{
	}
	{
	}
	{
	}
	{
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, long, bool)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : bool (*const)()
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long)
	todo("implement");
	_sub_106A28A0(mover_index, action_type, frame_events);
}

_extern void _sub_106A2C30(__int32, e_action);
void unit_action_assassinate_finished_hook(__int32 mover_index, e_action action_type) // 0x106A2C30
{
	mangled_x86(MANGLED_TODO, "?unit_action_assassinate_finished_hook@@YAXHW4e_action@@@Z");
	// e_action action_type;
	// void (*const unit_action_assassinate_finished)(long, e_action);
	// s_unit_data *unit;
	// s_game_time_globals *time_globals;
	// function call : void (*const)(long, e_action)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	_sub_106A2C30(mover_index, action_type);
}

_extern void _sub_106A2D50(long, e_action);
void unit_action_assassinate_interrupted_hook(long mover_index, e_action action_type) // 0x106A2D50
{
	mangled_x86(MANGLED_TODO, "?unit_action_assassinate_interrupted_hook@@YAXJW4e_action@@@Z");
	// e_action action_type;
	// void (*const unit_action_assassinate_interrupted)(long, e_action);
	// s_unit_data *unit;
	// s_game_time_globals *time_globals;
	// function call : void (*const)(long, e_action)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	_sub_106A2D50(mover_index, action_type);
}

_extern void _sub_106A32F0(long);
void unit_update_assassination_events(long unit_index) // 0x106A32F0
{
	mangled_x86(MANGLED_TODO, "?unit_update_assassination_events@@YAXJ@Z");
	// long unit_index;
	// s_unit_data *unit;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	_sub_106A32F0(unit_index);
}

_extern void _sub_106A3D40(long);
void unit_update_vision_mode_hook(long unit_index) // 0x106A3D40
{
	mangled_x86(MANGLED_TODO, "?unit_update_vision_mode_hook@@YAXJ@Z");
	// long unit_index;
	// void (*const unit_update_vision_mode)(long);
	// function call : void (*const)(long)
	todo("implement");
	_sub_106A3D40(unit_index);
}

_extern void _sub_106A3C00(long);
void unit_update_target_tracking_hook(long unit_index) // 0x106A3C00
{
	mangled_x86(MANGLED_TODO, "?unit_update_target_tracking_hook@@YAXJ@Z");
	// long unit_index;
	// void (*const unit_update_target_tracking)(long);
	// function call : void (*const)(long)
	todo("implement");
	_sub_106A3C00(unit_index);
}

namespace Patches
{
	namespace Unit
	{
		_extern void _sub_106A11F0();
		void ApplyAll() // 0x106A11F0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Unit@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_106A11F0();
		}
	}
}

/* ---------- private code */

_extern void _sub_106A31B0(long, e_unit_messages);
extern "C" void unit_send_message_to_first_person_ho_hook(long unit_index, e_unit_messages message) // 0x106A31B0
{
	// unit_send_message_to_first_person_ho_hook
	// e_unit_messages message;
	// s_unit_data *unit;
	{
		// long i;
		{
			// long weapon_index;
		}
	}
	// function call : void (*const)(long, long, e_unit_messages, long)
	todo("implement");
	_sub_106A31B0(unit_index, message);
}

_extern void _sub_106A3630(long, long);
extern "C" void unit_update_target_pivot_aiming(long unit_index, long ultimate_weapon_control_unit_index) // 0x106A3630
{
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
	todo("implement");
	_sub_106A3630(unit_index, ultimate_weapon_control_unit_index);
}

_extern void _sub_106A34B0(long);
extern "C" void unit_update_target_aiming(long unit_index) // 0x106A34B0
{
	// unit_update_target_aiming
	// long unit_index;
	// s_unit_data *unit;
	// s_unit_definition *unit_definiton;
	{
		// long ultimate_weapon_control_unit_index;
		// s_unit_data *ultimate_weapon_control_unit;
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void *(*const)(unsigned long, long)
	// function call : long (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	_sub_106A34B0(unit_index);
}

_extern void _sub_106A2030(c_tracked_target *, void *, c_aim_target_object *, s_unit_target_tracking_block *, long);
extern "C" void c_tracked_target__update_internal_hook(c_tracked_target *thisptr, void *__formal, c_aim_target_object *target_object, s_unit_target_tracking_block *tracking_parameters, long behavior) // 0x106A2030
{
	// c_tracked_target__update_internal_hook
// $LN5:
	// c_tracked_target *thisptr;
	// void *__formal;
	// c_aim_target_object *target_object;
	// s_unit_target_tracking_block *tracking_parameters;
	// long behavior;
	{
		// short decay_ticks;
	}
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
	todo("implement");
	_sub_106A2030(thisptr, __formal, target_object, tracking_parameters, behavior);
}

_extern void _sub_106A3C70(long);
extern "C" void unit_update_team_index_hook(long unit_index) // 0x106A3C70
{
	// unit_update_team_index_hook
	// long unit_index;
	// s_unit_data *unit;
	// long (*const game_engine_team_designator_to_team_index)(long);
	// void (*const unit_update_team_index)(long);
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : void (*const)(long)
	todo("implement");
	_sub_106A3C70(unit_index);
}

_extern long _sub_106A3030(long);
extern "C" long unit_get_last_associated_weak_player_index_for_appearance(long unit_index) // 0x106A3030
{
	// unit_get_last_associated_weak_player_index_for_appearance
	// long unit_index;
	// s_unit_data *unit;
	{
		// s_unit_data *hologram_creator_unit;
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	long __result = _sub_106A3030(unit_index);
	return __result;
}

_extern bool _sub_106A1FB0(c_tracked_target *, void *, c_aim_target_simulation_entity *, s_unit_target_tracking_block *);
extern "C" bool c_tracked_target__set_from_weapon_fire_event_hook(c_tracked_target *thisptr, void *__formal, c_aim_target_simulation_entity *aim_target, s_unit_target_tracking_block *tracking_parameters) // 0x106A1FB0
{
	// c_tracked_target__set_from_weapon_fire_event_hook
	// s_unit_target_tracking_block *tracking_parameters;
	// function call : bool (*const)(c_aim_target_simulation_entity *, c_aim_target_object *)
	todo("implement");
	bool __result = _sub_106A1FB0(thisptr, __formal, aim_target, tracking_parameters);
	return __result;
}

_extern void _sub_106A2680(long);
extern "C" void giant_object_early_mover_delete_early_mover_childern_hook(long object_index) // 0x106A2680
{
	// giant_object_early_mover_delete_early_mover_childern_hook
	// long object_index;
	// void (*const object_early_mover_delete_early_mover_childern)(long);
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : void (*const)(long)
	todo("implement");
	_sub_106A2680(object_index);
}

_extern void _sub_106A2720(__int32);
extern "C" void object_detach_predicted_objects_hook(__int32 object_index) // 0x106A2720
{
	// object_detach_predicted_objects_hook
	// __int32 object_index;
	// void (*const object_detach_immediate)(long);
	// long predicted_object_index;
	// long (*const find_first_predicted_object_recursive)(long);
	// void (*const object_type_detach_from_parent)(long);
	{
		// s_object_data *predicted_object;
	}
	// function call : long (*const)(long)
	// function call : void (*const)(long)
	// function call : void (*const)(long)
	// function call : long (*const)(long)
	todo("implement");
	_sub_106A2720(object_index);
}
