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
#include "Blam/memory/tls.hpp"
#include "Blam/motor/motor_system.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
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

struct c_motor_request;
struct real_vector3d;
struct s_unit_data;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Biped {}
	using namespace Patches::Biped;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace Biped
	{
		extern void biped_update_boots_off_the_ground(long biped_index);
		extern void biped_update_sub1_hook(long biped_index);
		extern bool biped_falling_damage_campaign_only();
		extern bool fall_collision_damage_is_multiplayer();
		extern bool fall_collision_damage_is_campaign();
		extern void ApplyAll();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern real_vector3d global_zero3d; // 0x11182860
}
/* ---------- public code */

namespace Patches
{
	namespace Biped
	{
		_extern void _sub_1079BA00(long);
		void biped_update_boots_off_the_ground(long biped_index) // 0x1079BA00
		{
			mangled_x86(MANGLED_TODO, "?biped_update_boots_off_the_ground@Biped@Patches@@YAXJ@Z");
			// static ...; // 0x1079BEBC
			// static ...; // 0x1079BEB4
			// static ...; // 0x1079BE9C
			// static ...; // 0x1079BE94
			// long biped_index;
			// s_unit_data *biped;
			// real_vector3d velocity;
			// float gravity;
			{
				// float d;
				// bool boosting;
				// float s;
				// float directional_speed;
				// float maxVelocity;
				// float v;
				// c_motor_request request;
			}
			// function call : void (*const)(long, real_vector3d *, real_vector3d *)
			// function call : e_motor_result (*const)(long, c_motor_request *)
			// function call : float (*const)()
			// function call : float (*const)()
			// function call : void (*const)(long, real_vector3d const *, real_vector3d const *)
			todo("implement");
			_sub_1079BA00(biped_index);
		}

		_extern void _sub_1079C000(long);
		void biped_update_sub1_hook(long biped_index) // 0x1079C000
		{
			mangled_x86(MANGLED_TODO, "?biped_update_sub1_hook@Biped@Patches@@YAXJ@Z");
			// long biped_index;
			// void (*const biped_update_sub1)(long);
			// function call : void (*const)(long)
			todo("implement");
			_sub_1079C000(biped_index);
		}

		_extern bool _sub_1079B990();
		bool biped_falling_damage_campaign_only() // 0x1079B990
		{
			mangled_x86(MANGLED_TODO, "?biped_falling_damage_campaign_only@Biped@Patches@@YA_NXZ");
			// procedure flags: nofpo
			// function call : bool (*const)()
			todo("implement");
			bool __result = _sub_1079B990();
			return __result;
		}

		_extern bool _sub_1079C0E0();
		bool fall_collision_damage_is_multiplayer() // 0x1079C0E0
		{
			mangled_x86(MANGLED_TODO, "?fall_collision_damage_is_multiplayer@Biped@Patches@@YA_NXZ");
			// procedure flags: nofpo
			// function call : bool (*const)()
			todo("implement");
			bool __result = _sub_1079C0E0();
			return __result;
		}

		_extern bool _sub_1079C070();
		bool fall_collision_damage_is_campaign() // 0x1079C070
		{
			mangled_x86(MANGLED_TODO, "?fall_collision_damage_is_campaign@Biped@Patches@@YA_NXZ");
			// procedure flags: nofpo
			// function call : bool (*)()
			todo("implement");
			bool __result = _sub_1079C070();
			return __result;
		}

		_extern void _sub_1079B490();
		void ApplyAll() // 0x1079B490
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Biped@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_1079B490();
		}
	}
}

/* ---------- private code */
