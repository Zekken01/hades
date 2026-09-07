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
		_extern void _sub_10AD1270();
		void ApplyAll() // 0x10AD1270
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Sprint@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10AD1270();
		}

		_extern void _sub_10AD15D0(__int32);
		void SetState(__int32 state) // 0x10AD15D0
		{
			mangled_x86(MANGLED_TODO, "?SetState@Sprint@Patches@@YAXH@Z");
			// __int32 state;
			todo("implement");
			_sub_10AD15D0(state);
		}

		_extern __int32 _sub_10AD14B0();
		__int32 GetState() // 0x10AD14B0
		{
			mangled_x86(MANGLED_TODO, "?GetState@Sprint@Patches@@YAHXZ");
			// procedure flags: nofpo
			todo("implement");
			__int32 __result = _sub_10AD14B0();
			return __result;
		}

		_extern void _sub_10AD1600(bool);
		void SetUnlimited(bool unlimited) // 0x10AD1600
		{
			mangled_x86(MANGLED_TODO, "?SetUnlimited@Sprint@Patches@@YAX_N@Z");
			// bool unlimited;
			todo("implement");
			_sub_10AD1600(unlimited);
		}

		_extern bool _sub_10AD1580(long);
		bool PlayerHasSprintTrait(long player_index) // 0x10AD1580
		{
			mangled_x86(MANGLED_TODO, "?PlayerHasSprintTrait@Sprint@Patches@@YA_NJ@Z");
			// long player_index;
			todo("implement");
			bool __result = _sub_10AD1580(player_index);
			return __result;
		}

		_extern void _sub_10AD1630();
		void Tick() // 0x10AD1630
		{
			mangled_x86(MANGLED_TODO, "?Tick@Sprint@Patches@@YAXXZ");
			// procedure flags: nofpo
			{
				// long player_index;
			}
			// function call : bool (*const)()
			// function call : unsigned long (*const)(long)
			todo("implement");
			_sub_10AD1630();
		}

		_extern void _sub_10AD1700(long);
		void UpdatePlayerSprint(long player_index) // 0x10AD1700
		{
			mangled_x86(MANGLED_TODO, "?UpdatePlayerSprint@Sprint@Patches@@YAXJ@Z");
			// long player_index;
			// s_player_datum *player;
			{
				// s_unit_data *unitObject;
				// s_unit_data *eqipObject;
				{
					// e_equipment_type equipment_type;
					{
						// float activeFraction;
					}
				}
			}
			// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
			// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
			// function call : e_equipment_type (*const)(long, long)
			// function call : float (*const)(long)
			// function call : long (*const)(long)
			todo("implement");
			_sub_10AD1700(player_index);
		}
	}
}

/* ---------- private code */

_extern bool _sub_10AD14D0(long);
bool HasSprintPlayerTrait(long player_index) // 0x10AD14D0
{
	// `anonymous-namespace'::HasSprintPlayerTrait
	// long player_index;
	// s_player_datum *player;
	todo("implement");
	bool __result = _sub_10AD14D0(player_index);
	return __result;
}

_extern bool _sub_10AD1B90(long);
bool player_is_using_adrenaline(long player_index) // 0x10AD1B90
{
	// `anonymous-namespace'::player_is_using_adrenaline
	// long player_index;
	// s_player_datum *player;
	{
		// s_unit_data *unitObject;
		// e_equipment_type equipment_type;
		// s_unit_data *eqipObject;
		{
			// float activeFraction;
		}
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : e_equipment_type (*const)(long, long)
	// function call : float (*const)(long)
	// function call : long (*const)(long)
	todo("implement");
	bool __result = _sub_10AD1B90(player_index);
	return __result;
}

_extern bool _sub_10AD1980(long);
bool player_can_sprint(long player_index) // 0x10AD1980
{
	// `anonymous-namespace'::player_can_sprint
	// long player_index;
	// s_player_datum *player;
	// bool (*const game_is_cooperative)();
	// function call : bool (*const)(unsigned long)
	// function call : bool (*)()
	// function call : bool (*const)()
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_10AD1980(player_index);
	return __result;
}

_extern void _sub_10AD1B00(long, long, s_player_action *);
void player_examine_action_hook(long player_index, long unit_index, s_player_action *action) // 0x10AD1B00
{
	// `anonymous-namespace'::player_examine_action_hook
	// s_player_action *action;
	// constexpr void (*const `player_examine_action_hook'::`2'::player_examine_action)(long, long, s_player_action *); // constant == 5494048
	// function call : void (*const)(long, long, s_player_action *)
	todo("implement");
	_sub_10AD1B00(player_index, unit_index, action);
}

_extern void _sub_10AD1E10(long, e_unit_messages);
void player_sprint_enter_hook(long unit_index, e_unit_messages message) // 0x10AD1E10
{
	// `anonymous-namespace'::player_sprint_enter_hook
	// e_unit_messages message;
	// void (*const unit_send_message_to_first_person)(long, e_unit_messages);
	// void (*const weapon_stop_reload)(long, bool);
	// bool (*const weapon_reloading)(long, long, short *);
	{
		// s_unit_data *unit;
		{
			// long i;
			{
				// long weapon_index;
			}
		}
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : long (*const)(long, short)
	// function call : bool (*const)(long, long, short *)
	// function call : void (*const)(long, bool)
	// function call : void (*const)(long, e_unit_messages)
	todo("implement");
	_sub_10AD1E10(unit_index, message);
}
