/* ---------- headers */

#include "hades/hades.h"

#include "Blam/ai/actor.hpp"
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
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
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

struct real_point3d;
struct s_cluster_reference;
struct s_object_data;
struct s_player_action_context;
struct s_player_datum;
struct s_unit_data;

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Devices {}
	using namespace Patches::Devices;
	namespace PlayerControl {}
	using namespace Patches::PlayerControl;
	namespace Equipment {}
	using namespace Patches::Equipment;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace PlayerControl
	{
		extern void ApplyAll();
	}
}

bool sphere_intersects_sphere(real_point3d const &c0, float r0, real_point3d const &c1, float r1);
void player_find_nearby_items_hook(long player_index);
void player_find_nearby_interactions_hook(long player_index, s_player_action_context *out_action_context);
void player_control_update_player_hook(long player_index, long input_user_index, long controller_index, float world_delta, float game_delta);
void player_control_zoom_hold_timer_fix1_hook();
void player_control_zoom_hold_timer_fix2_hook();
void player_control_crouch_hold_timer_fix1_hook();
void player_control_crouch_hold_timer_fix2_hook();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern long g_player_control_delta_msec; // 0x124083A8
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace PlayerControl
	{
		_extern void _sub_108DC8C0();
		void ApplyAll() // 0x108DC8C0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@PlayerControl@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_108DC8C0();
		}
	}
}

/* ---------- private code */

_extern bool _sub_108DD9A0(real_point3d const &, float, real_point3d const &, float);
bool sphere_intersects_sphere(real_point3d const &c0, float r0, real_point3d const &c1, float r1) // 0x108DD9A0
{
	// `anonymous-namespace'::sphere_intersects_sphere
	// float r1;
	todo("implement");
	bool __result = _sub_108DD9A0(c0, r0, c1, r1);
	return __result;
}

_extern void _sub_108DD6D0(long);
void player_find_nearby_items_hook(long player_index) // 0x108DD6D0
{
	// `anonymous-namespace'::player_find_nearby_items_hook
	// static ...; // 0x108DD8FC
	// static ...; // 0x108DD8F0
	// static ...; // 0x108DD8E8
	// long player_index;
	// long unit_index;
	// void (*const player_examine_nearby_item)(long, long);
	{
		// long num_objects;
		// long nearby_objects[256];
		// long root_object_index;
		// s_unit_data *unit_object;
		{
			// long i;
			{
				// long object_index;
				// s_object_data *nearby_object;
				// long object_type;
				{
					// long child_object_index;
				}
			}
		}
	}
	// function call : long (*const)(long)
	// function call : short (*const)(long, long, s_cluster_reference const *, real_point3d const *, float, long *, short)
	// function call : void (*const)(long, long)
	todo("implement");
	_sub_108DD6D0(player_index);
}

_extern void _sub_108DD0C0(long, s_player_action_context *);
void player_find_nearby_interactions_hook(long player_index, s_player_action_context *out_action_context) // 0x108DD0C0
{
	// `anonymous-namespace'::player_find_nearby_interactions_hook
	// static ...; // 0x108DD565
	// static ...; // 0x108DD55C
	// static ...; // 0x108DD544
	// static ...; // 0x108DD53C
// $LN26:
// $LN25:
// $LN19:
// $LN16:
// $LN15:
// EXPLICIT_DEFAULT:
	// long player_index;
	// s_player_action_context *out_action_context;
	// s_player_datum *player;
	// s_object_data *unit;
	// long k_ignore_distance_filter;
	// long num_objects;
	// s_cluster_reference location;
	// long results[256];
	// long k_base_object_filter;
	// float radius;
	{
		// long i;
		{
			// long object_index;
			// s_object_data *object;
			{
				// long child_filter;
				{
					// s_object_data *child_object;
					{
						// long child_object_index;
					}
				}
			}
		}
	}
	// function call : void (*const)(long, s_cluster_reference *)
	// function call : short (*const)(long, long, s_cluster_reference const *, real_point3d const *, float, long *, short)
	// function call : bool (*const)(long, long, s_player_action_context *)
	// function call : bool (*const)(long, long, s_player_action_context *)
	// function call : bool (*const)(long, long, s_player_action_context *)
	// function call : bool (*const)(long, long, s_player_action_context *)
	todo("implement");
	_sub_108DD0C0(player_index, out_action_context);
}

_extern void _sub_108DCFD0(long, long, long, float, float);
void player_control_update_player_hook(long player_index, long input_user_index, long controller_index, float world_delta, float game_delta) // 0x108DCFD0
{
	// `anonymous-namespace'::player_control_update_player_hook
	// float game_delta;
	// void (*const player_control_update_player)(long, long, long, float, float);
	// function call : void (*const)(long, long, long, float, float)
	todo("implement");
	_sub_108DCFD0(player_index, input_user_index, controller_index, world_delta, game_delta);
}

__declspec(naked) void player_control_zoom_hold_timer_fix1_hook() // 0x108DD080
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_control_zoom_hold_timer_fix1_hook@@YAXXZ");
	// `anonymous-namespace'::player_control_zoom_hold_timer_fix1_hook
	// procedure flags: nofpo
	// skip:

	__asm
	{
		cmp ax, 7FFFh
		jge Lcapped
		add eax, g_player_control_delta_msec
		push 05D5109h
		ret
		Lcapped:
		push 05D5145h
		ret
	}
}

__declspec(naked) void player_control_zoom_hold_timer_fix2_hook() // 0x108DD0A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_control_zoom_hold_timer_fix2_hook@@YAXXZ");
	// `anonymous-namespace'::player_control_zoom_hold_timer_fix2_hook
	// procedure flags: nofpo

	__asm
	{
		cmp word ptr [edi + esi + 3D4h], 0FAh
		push 05D5126h
		ret
	}
}

__declspec(naked) void player_control_crouch_hold_timer_fix1_hook() // 0x108DCF80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_control_crouch_hold_timer_fix1_hook@@YAXXZ");
	// `anonymous-namespace'::player_control_crouch_hold_timer_fix1_hook
	// procedure flags: nofpo
	// skip:

	__asm
	{
		movsx eax, word ptr [esi + edx + 3CEh]
		cmp ax, 7FFFh
		jge Lcapped
		add eax, g_player_control_delta_msec
		mov [esi + edx + 3CEh], ax
		Lcapped:
		push 05D1CD7h
		ret
	}
}

__declspec(naked) void player_control_crouch_hold_timer_fix2_hook() // 0x108DCFB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_control_crouch_hold_timer_fix2_hook@@YAXXZ");
	// `anonymous-namespace'::player_control_crouch_hold_timer_fix2_hook
	// procedure flags: nofpo

	__asm
	{
		cmp word ptr [esi + edx + 3CEh], 0FAh
		push 05D1C2Dh
		ret
	}
}
