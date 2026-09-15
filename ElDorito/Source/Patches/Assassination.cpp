/* ---------- headers */

#include "hades/hades.h"

#include "Blam/animations/animation_definitions.hpp"
#include "Blam/animations/animation_manager.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
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

struct c_animation_manager;
struct s_animation_sync_action;
struct s_animation_sync_action_participant;
struct s_object_data;
struct s_player_datum;
struct s_unit_data;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Assassination {}
	using namespace Patches::Assassination;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

#include "Modules/ModuleServer.hpp"  // hades: added for 0x10A29F10

namespace Patches
{
	namespace Assassination
	{
		extern void ApplyAll();
	}
}

bool object_has_invincibility(long object_index);
bool player_can_assassinate_object_hook(long player_index, long object_index);
bool object_can_be_melee_instant_killed_hook(long object_index);
bool motor_system_biped_physics_preupdate_moving_hook(long biped_index, void *physics_input, void *physics_output, bool a4, bool a5, float a6, bool a7, bool a8);
bool sync_action_compatible_with_participant_current_states_hook(long initiator_index, long target_index, unsigned long sync_action_name);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Assassination
	{
		_extern void _sub_10A297C0();
		void ApplyAll() // 0x10A297C0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Assassination@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A297C0();
		}
	}
}

/* ---------- private code */

_extern bool _sub_10A29E40(long);
bool object_has_invincibility(long object_index) // 0x10A29E40
{
	// `anonymous-namespace'::object_has_invincibility
	// long object_index;
	// s_unit_data *unit;
	{
		// s_player_datum *player;
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	bool __result = _sub_10A29E40(object_index);
	return __result;
}

bool player_can_assassinate_object_hook(long player_index, long object_index) // 0x10A29F10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_can_assassinate_object_hook@@YA_NJJ@Z");
	// `anonymous-namespace'::player_can_assassinate_object_hook
	// long object_index;
	// bool (*const player_can_assassinate_object)(long, long);
	// function call : bool (*const)(long, long)

	if (!Utils::Singleton<Modules::ModuleServer>::Instance().VarServerAssassinationEnabledClient->ValueInt)
	{
		return false;
	}

	if (((bool(*)(long, long))0x538510)(player_index, object_index))
	{
		return !object_has_invincibility(object_index);
	}

	return false;
}

bool object_can_be_melee_instant_killed_hook(long object_index) // 0x10A29D90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_can_be_melee_instant_killed_hook@@YA_NJ@Z");
	// `anonymous-namespace'::object_can_be_melee_instant_killed_hook
	// long object_index;
	// bool (*const object_can_be_melee_instant_killed)(long);
	// function call : bool (*const)(long)

	bool (__cdecl *const object_can_be_melee_instant_killed)(long) = (bool(__cdecl *const)(long))0xb2a780;

	if (!object_can_be_melee_instant_killed(object_index))
	{
		return false;
	}

	return !object_has_invincibility(object_index);
}

_extern bool _sub_10A29CA0(long, void *, void *, bool, bool, float, bool, bool);
bool motor_system_biped_physics_preupdate_moving_hook(long biped_index, void *physics_input, void *physics_output, bool a4, bool a5, float a6, bool a7, bool a8) // 0x10A29CA0
{
	// `anonymous-namespace'::motor_system_biped_physics_preupdate_moving_hook
	// bool a8;
	// bool (*const motor_system_biped_physics_preupdate_moving)(long, void *, void *, bool, bool, float, bool, bool);
	// bool ret;
	// bool (*const object_is_running_sync_action)(long);
	// function call : bool (*const)(long, void *, void *, bool, bool, float, bool, bool)
	// function call : bool (*const)(long)
	todo("implement");
	bool __result = _sub_10A29CA0(biped_index, physics_input, physics_output, a4, a5, a6, a7, a8);
	return __result;
}

_extern bool _sub_10A29FE0(long, long, unsigned long);
bool sync_action_compatible_with_participant_current_states_hook(long initiator_index, long target_index, unsigned long sync_action_name) // 0x10A29FE0
{
	// `anonymous-namespace'::sync_action_compatible_with_participant_current_states_hook
	// unsigned long sync_action_name;
	// bool (*const initiator_satisfies_airborne_state)(long, long, bool);
	// c_animation_manager *initiator_manager;
	// s_object_data *target;
	// bool (*const target_satisfies_airborne_state)(long, long, bool);
	// s_object_data *initiator;
	// s_animation_sync_action_participant *target_participant;
	// bool initiator_valid;
	// s_animation_sync_action *target_sync_action;
	// s_animation_sync_action_participant *initiator_participant;
	// bool target_valid;
	// c_animation_manager *target_manager;
	// s_animation_sync_action *initiator_sync_action;
	{
		// long i;
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_animation_sync_action *(*const)(c_animation_manager const *, unsigned long, unsigned long, unsigned long)
	// function call : s_animation_sync_action *(*const)(c_animation_manager const *, unsigned long, unsigned long, unsigned long)
	// function call : bool (*const)(long, long, bool)
	// function call : bool (*const)(long, long, bool)
	todo("implement");
	bool __result = _sub_10A29FE0(initiator_index, target_index, sync_action_name);
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_animation_sync_action_participant>::try_get_element(__int32, s_animation_sync_action_participant **) const;
template s_animation_sync_action_participant & c_tag_block<s_animation_sync_action_participant>::operator[](__int32);
template s_animation_sync_action_participant * c_tag_block<s_animation_sync_action_participant>::get_element(__int32) const;
