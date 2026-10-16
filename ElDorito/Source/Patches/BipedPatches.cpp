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

extern float (*const game_tick_length)();  // hades: added for 0x1079BA00
extern float dot_product3d(real_vector3d const *v1, real_vector3d const *v2);  // hades: added for 0x1079BA00
extern float magnitude3d(real_vector3d const *v);  // hades: added for 0x1079BA00
extern s_object_data *object_get(unsigned long object_index);  // hades: added for 0x1079BA00
#include "Modules/ModuleDebug.hpp"  // hades: added for 0x1079BA00

#include "Modules/ModuleServer.hpp"  // hades: added for 0x1079C070
extern bool (*game_is_campaign)();  // hades: the original calls through the pointer global, ?game_is_campaign@@3P6A_NXZA
extern bool (*const game_is_multiplayer)();  // hades: the original calls through the pointer global, ?game_is_multiplayer@@3Q6A_NXZA

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

namespace hades_file_local
{
	namespace hades_file_local_BipedPatches { extern real_vector3d global_zero3d; } using namespace hades_file_local_BipedPatches; // 0x11182860
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Biped
	{
		void biped_update_boots_off_the_ground(long biped_index) // 0x1079BA00
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?biped_update_boots_off_the_ground@Biped@Patches@@YAXJ@Z");
			// static ...; // 0x1079BEBC
			// static ...; // 0x1079BEB4
			// static ...; // 0x1079BE9C
			// static ...; // 0x1079BE94
			// long biped_index;
			// s_unit_data *biped;
			// real_vector3d velocity;
			// float gravity;
				// float d;
				// bool boosting;
				// float s;
				// float directional_speed;
				// float maxVelocity;
				// float v;
				// c_motor_request request;
			// function call : void (*const)(long, real_vector3d *, real_vector3d *)
			// function call : e_motor_result (*const)(long, c_motor_request *)
			// function call : float (*const)()
			// function call : float (*const)()
			// function call : void (*const)(long, real_vector3d const *, real_vector3d const *)

			s_unit_data *biped = (s_unit_data *)object_get(biped_index);
			if (!biped || biped->player_index == -1)
				return;
			if (!(biped->unit_control_flags & 0x8000))
				return;
			if (!Modules::ModuleDebug::Instance().VarAcrophobiaClient->ValueInt)
				return;
			real_vector3d velocity;
			((void (*const)(long, real_vector3d *, real_vector3d *))0xB2EB30)(biped_index, &velocity, nullptr);
			if (!(biped->unit_control_flags & 1))
			{
				c_motor_request request;
				request.action_type = 1;
				request.task_id = 7;
				request.animation_name1 = -1;
				((e_motor_result (*const)(long, c_motor_request *))0xB749C0)(biped_index, &request);
				bool boosting = biped->unit_control_flags & 0x800;
				float directional_speed = dot_product3d(&biped->desired_aiming_vector, &velocity);
				float d = fminf(1.0f, fmaxf(directional_speed * 0.02f, 0.0f));
				float s = (d * 9.0f - d * d * 18.0f + 9.0f) * game_tick_length();
				velocity = velocity - 0.2f * (-directional_speed * biped->desired_aiming_vector + velocity) + s * biped->desired_aiming_vector;
				float maxVelocity = boosting ? 16.0f : 8.0f;
				float v = magnitude3d(&velocity);
				if (v > maxVelocity)
					velocity = maxVelocity / v * velocity;
			}
			else
				velocity = global_zero3d;
			float gravity = *reinterpret_cast<float *>(tls_getd().physics_constants);
			velocity.k += game_tick_length() * gravity;
			((void (*const)(long, real_vector3d const *, real_vector3d const *))0xB34040)(biped_index, &velocity, nullptr);
		}

		void biped_update_sub1_hook(long biped_index) // 0x1079C000
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?biped_update_sub1_hook@Biped@Patches@@YAXJ@Z");
			// long biped_index;
			// void (*const biped_update_sub1)(long);
			// function call : void (*const)(long)

			void (__cdecl *const biped_update_sub1)(long) = (void(__cdecl *const)(long))0xb72280;

			biped_update_sub1(biped_index);
			Patches::Biped::biped_update_boots_off_the_ground(biped_index);
		}

		bool biped_falling_damage_campaign_only() // 0x1079B990
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?biped_falling_damage_campaign_only@Biped@Patches@@YA_NXZ");
			// procedure flags: nofpo
			// function call : bool (*const)()

			if (Utils::Singleton<Modules::ModuleServer>::Instance().VarServerFallDamageMPEnabledClient->ValueInt < 2)
			{
				return game_is_multiplayer();
			}
			else
			{
				return false;
			}
		}

		bool fall_collision_damage_is_multiplayer() // 0x1079C0E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?fall_collision_damage_is_multiplayer@Biped@Patches@@YA_NXZ");
			// procedure flags: nofpo
			// function call : bool (*const)()

			if (Utils::Singleton<Modules::ModuleServer>::Instance().VarServerFallDamageMPEnabledClient->ValueInt != 1)
			{
				return game_is_multiplayer();
			}
			else
			{
				return false;
			}
		}

		bool fall_collision_damage_is_campaign() // 0x1079C070
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?fall_collision_damage_is_campaign@Biped@Patches@@YA_NXZ");
			// procedure flags: nofpo
			// function call : bool (*)()

			if (Utils::Singleton<Modules::ModuleServer>::Instance().VarServerFallDamageMPEnabledClient->ValueInt != 1)
			{
				return game_is_campaign();
			}
			else
			{
				return true;
			}
		}

		void ApplyAll() // 0x1079B490
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Biped@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x771790, biped_update_sub1_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7AE4AE, biped_falling_damage_campaign_only, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7AE5BF, biped_falling_damage_campaign_only, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x3633CB, fall_collision_damage_is_multiplayer, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x362BEF, fall_collision_damage_is_campaign, static_cast<__int32>(HookFlags::IsCall)).Apply();
		}
	}
}

/* ---------- private code */

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { namespace hades_file_local_BipedPatches { real_vector3d global_zero3d; } }
