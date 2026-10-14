/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
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
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "ElDorito.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

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
#include "Modules/ModuleCampaign.hpp"  // hades: added for 0X10AD1980

/* ---------- forward declarations */

struct s_object_data;
struct s_player_action;
struct s_player_datum;
struct s_unit_data;

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Sprint {}
	using namespace Patches::Sprint;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0x10AD1E10

namespace Patches
{
	namespace Sprint
	{
		extern void ApplyAll();
		extern void SetState(__int32 state);
		extern __int32 GetState();
		extern void SetUnlimited(bool unlimited);
		extern bool PlayerHasSprintTrait(long player_index);
		extern void Tick();
		extern void UpdatePlayerSprint(long player_index);
	}
}

bool HasSprintPlayerTrait(long player_index);
bool player_is_using_adrenaline(long player_index);
bool player_can_sprint(long player_index);
void player_examine_action_hook(long player_index, long unit_index, s_player_action *action);
void player_sprint_enter_hook(long unit_index, e_unit_messages message);

/* ---------- globals */

extern bool (__cdecl *const unit_is_dual_wielding)(unsigned long);  // hades: added for 0X10AD1980
extern bool (*game_is_campaign)();  // hades: added for 0X10AD1980

/* ---------- private variables */

namespace hades_file_local
{
	extern __int32 sprintState; // 0x11354BFC
	extern bool sprintUnlimited; // 0x12467417
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Sprint
	{
		void ApplyAll() // 0x10AD1270
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Sprint@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x1442F4, player_examine_action_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x13E7B0, player_sprint_enter_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
		}

		void SetState(__int32 state) // 0x10AD15D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetState@Sprint@Patches@@YAXH@Z");
			// __int32 state;

			sprintState = state;
		}

		__int32 GetState() // 0x10AD14B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetState@Sprint@Patches@@YAHXZ");
			// procedure flags: nofpo

			return sprintState;
		}

		void SetUnlimited(bool unlimited) // 0x10AD1600
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetUnlimited@Sprint@Patches@@YAX_N@Z");
			// bool unlimited;

			sprintUnlimited = unlimited;
		}

		bool PlayerHasSprintTrait(long player_index) // 0x10AD1580
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PlayerHasSprintTrait@Sprint@Patches@@YA_NJ@Z");
			// long player_index;

			return HasSprintPlayerTrait(player_index);
		}

		void Tick() // 0x10AD1630
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@Sprint@Patches@@YAXXZ");
			// procedure flags: nofpo
				// long player_index;
			// function call : bool (*const)()
			// function call : unsigned long (*const)(long)

			if (((bool(__cdecl *)())0x5314b0)())
			{
				long player_index = ((unsigned long(__cdecl *)(long))0x589c60)(0);

				if (player_index != NONE)
					tls_getd().chud_persistent_global_data->m_scripting.widget_show[0][10] = player_can_sprint(player_index);
			}
		}

		void UpdatePlayerSprint(long player_index) // 0x10AD1700
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?UpdatePlayerSprint@Sprint@Patches@@YAXJ@Z");
			// long player_index;
			// s_player_datum *player;
				// s_unit_data *unitObject;
				// s_unit_data *eqipObject;
					// e_equipment_type equipment_type;
						// float activeFraction;
			// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
			// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
			// function call : e_equipment_type (*const)(long, long)
			// function call : float (*const)(long)
			// function call : long (*const)(long)

			s_player_datum *player = player_get(player_index);
			if (player)
			{
				s_unit_data *unitObject = (s_unit_data *)object_try_and_get_and_verify_type(player->unit_index, -1);
				if (!unitObject)
					return;
				s_unit_data *eqipObject = (s_unit_data *)object_try_and_get_and_verify_type(unitObject->equipment_object_indices[0], -1);
				if (eqipObject)
				{
					e_equipment_type equipment_type = ((e_equipment_type (*const)(long, long))0xBA0260)(eqipObject->definition_index, 0);
					if (equipment_type == _equipment_type_adrenaline && sprintState == 2 && !HasSprintPlayerTrait(player_index))
					{
						float activeFraction = ((float (*const)(long))0xB87DA0)(unitObject->equipment_object_indices[0]);
						if (((long (*const)(long))0xB89190)(unitObject->equipment_object_indices[0]) <= 0 && activeFraction == 0.0f)
							player->sprint_cooldown2 = 5;
					}
				}
				if (sprintUnlimited && HasSprintPlayerTrait(player_index))
					player->sprint_depleted_timer = 0;
			}
		}
	}
}

/* ---------- private code */

bool HasSprintPlayerTrait(long player_index) // 0x10AD14D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HasSprintPlayerTrait@@YA_NJ@Z");
	// `anonymous-namespace'::HasSprintPlayerTrait
	// long player_index;
	// s_player_datum *player;

	s_player_datum *player = player_get(player_index);

	return sprintState == 1
		|| (sprintState == 2 && player && player->traits.extended.sprint_allowed == c_player_trait_extended::_sprint_enabled);
}

bool player_is_using_adrenaline(long player_index) // 0x10AD1B90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_is_using_adrenaline@@YA_NJ@Z");
	// `anonymous-namespace'::player_is_using_adrenaline
	// long player_index;
	// s_player_datum *player;
		// s_unit_data *unitObject;
		// e_equipment_type equipment_type;
		// s_unit_data *eqipObject;
			// float activeFraction;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : e_equipment_type (*const)(long, long)
	// function call : float (*const)(long)
	// function call : long (*const)(long)

	s_player_datum *player = player_get(player_index);
	if (player)
	{
		s_unit_data *unitObject = (s_unit_data *)object_try_and_get_and_verify_type(player->unit_index, -1);
		if (!unitObject)
			return false;
		s_unit_data *eqipObject = (s_unit_data *)object_try_and_get_and_verify_type(unitObject->equipment_object_indices[0], -1);
		if (!eqipObject)
			return false;
		e_equipment_type equipment_type = ((e_equipment_type (*)(long, long))0xBA0260)(eqipObject->definition_index, 0);
		if (equipment_type == (e_equipment_type)18 && sprintState == 2 && !HasSprintPlayerTrait(player_index))
		{
			float activeFraction = ((float (*)(long))0xB87DA0)(unitObject->equipment_object_indices[0]);
			if (((long (*)(long))0xB89190)(unitObject->equipment_object_indices[0]) <= 0 && activeFraction == 0.0f && player->sprint_depleted_timer < 270)
				return true;
			if (activeFraction == 1.0f)
				return true;
		}
	}
	return false;
}

bool player_can_sprint(long player_index) // 0x10AD1980
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_can_sprint@@YA_NJ@Z");
	// `anonymous-namespace'::player_can_sprint
	// long player_index;
	// s_player_datum *player;
	// bool (*const game_is_cooperative)();
	// function call : bool (*const)(unsigned long)
	// function call : bool (*)()
	// function call : bool (*const)()
	// function call : bool (*const)()

	bool (__cdecl *const game_is_cooperative)() = (bool(__cdecl *const)())0x531a80;

	s_player_datum *player = player_get(player_index);

	if (!player || player->unit_index == NONE)
		return false;

	if (unit_is_dual_wielding(player->unit_index))
		return false;

	if (game_is_campaign() || ((bool(__cdecl *)())0x531e20)())
	{
		if (game_is_cooperative())
			return false;

		if (Utils::Singleton<Modules::ModuleCampaign>::Instance().VarCampaignSprintEnabled->ValueInt == 1)
			return true;
		else
			return false;
	}

	if (player_is_using_adrenaline(player_index) && sprintState == 2 && !HasSprintPlayerTrait(player_index))
		return true;

	return HasSprintPlayerTrait(player_index);
}

void player_examine_action_hook(long player_index, long unit_index, s_player_action *action) // 0x10AD1B00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_examine_action_hook@@YAXJJPAUs_player_action@@@Z");
	// `anonymous-namespace'::player_examine_action_hook
	// s_player_action *action;
	// constexpr void (*const `player_examine_action_hook'::`2'::player_examine_action)(long, long, s_player_action *); // constant == 5494048
	// function call : void (*const)(long, long, s_player_action *)

	if (!player_can_sprint(player_index))
		action->control_flags &= -257;

	((void(__cdecl *)(long, long, s_player_action *))0x53d520)(player_index, unit_index, action);
}

void player_sprint_enter_hook(long unit_index, e_unit_messages message) // 0x10AD1E10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_sprint_enter_hook@@YAXJW4e_unit_messages@@@Z");
	// `anonymous-namespace'::player_sprint_enter_hook
	// e_unit_messages message;
	// void (*const unit_send_message_to_first_person)(long, e_unit_messages);
	// void (*const weapon_stop_reload)(long, bool);
	// bool (*const weapon_reloading)(long, long, short *);
		// s_unit_data *unit;
			// long i;
				// long weapon_index;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : long (*const)(long, short)
	// function call : bool (*const)(long, long, short *)
	// function call : void (*const)(long, bool)
	// function call : void (*const)(long, e_unit_messages)

	static long (*const unit_inventory_get_weapon)(long, short) = reinterpret_cast<long (*)(long, short)>(0xB454D0);
	void (*const unit_send_message_to_first_person)(long, e_unit_messages) = reinterpret_cast<void (*)(long, e_unit_messages)>(0xBA5750);
	bool (*const weapon_reloading)(long, long, short *) = reinterpret_cast<bool (*)(long, long, short *)>(0xB66220);
	void (*const weapon_stop_reload)(long, bool) = reinterpret_cast<void (*)(long, bool)>(0xB676D0);
	if (s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003))
	{
		for (long i = 0; i < 2; i++)
		{
			long weapon_index = unit_inventory_get_weapon(unit_index, unit->current_weapon_set.indices[i]);
			if (weapon_index != -1 && weapon_reloading(weapon_index, -1, nullptr))
				weapon_stop_reload(weapon_index, false);
		}
	}
	unit_send_message_to_first_person(unit_index, message);
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { __int32 sprintState = 1; }
namespace hades_file_local { bool sprintUnlimited; }
