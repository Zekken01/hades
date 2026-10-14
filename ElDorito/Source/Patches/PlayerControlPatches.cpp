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

extern float distance_squared3d(real_point3d const *p1, real_point3d const *p2);  // hades: added for 0x108DD9A0

namespace Patches::Devices { bool PlayerConsiderDeviceInteraction(long playerIndex, long objectIndex, s_player_action_context *context); }  // hades: added for 0x108DD0C0
namespace Patches::Equipment { void PlayerConsiderEquipmentInteraction(long playerIndex, long objectIndex, s_player_action_context *context); }  // hades: added for 0x108DD0C0

extern float distance_squared3d(real_point3d const &a, real_point3d const &b);  // hades: added for 0x108DD9A0

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
		void ApplyAll() // 0x108DC8C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@PlayerControl@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x139B20, player_find_nearby_interactions_hook).Apply();
			Hook(0x139900, player_find_nearby_items_hook).Apply();
			Hook(0x1D49DF, player_control_update_player_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1D5102, player_control_zoom_hold_timer_fix1_hook).Apply();
			Hook(0x1D511D, player_control_zoom_hold_timer_fix2_hook).Apply();
			Hook(0x1D1C60, player_control_crouch_hold_timer_fix1_hook).Apply();
			Hook(0x1D1C24, player_control_crouch_hold_timer_fix2_hook).Apply();
		}
	}
}

/* ---------- private code */

bool sphere_intersects_sphere(real_point3d const &c0, float r0, real_point3d const &c1, float r1) // 0x108DD9A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sphere_intersects_sphere@@YA_NABUreal_point3d@@M0M@Z");
	// `anonymous-namespace'::sphere_intersects_sphere
	// float r1;

	return distance_squared3d(&c0, &c1) <= (r0 + r1) * (r0 + r1);
}

void player_find_nearby_items_hook(long player_index) // 0x108DD6D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_find_nearby_items_hook@@YAXJ@Z");
	// `anonymous-namespace'::player_find_nearby_items_hook
	// static ...; // 0x108DD8FC
	// static ...; // 0x108DD8F0
	// static ...; // 0x108DD8E8
	// long player_index;
	// long unit_index;
	// void (*const player_examine_nearby_item)(long, long);
		// long num_objects;
		// long nearby_objects[256];
		// long root_object_index;
		// s_unit_data *unit_object;
			// long i;
				// long object_index;
				// s_object_data *nearby_object;
				// long object_type;
					// long child_object_index;
	// function call : long (*const)(long)
	// function call : short (*const)(long, long, s_cluster_reference const *, real_point3d const *, float, long *, short)
	// function call : void (*const)(long, long)

	void (*const player_examine_nearby_item)(long, long) = reinterpret_cast<void (*)(long, long)>(0x5394A0);
	long unit_index = player_get(player_index)->unit_index;
	if (unit_index != -1)
	{
		long root_object_index = ((long (*)(long))0xB2EAB0)(unit_index);
		s_unit_data *unit_object = (s_unit_data *)object_get(root_object_index);
		long nearby_objects[256];
		long num_objects = ((short (*)(long, long, s_scenario_location const *, real_point3d const *, float, long *, long))0xB35B60)(0, 0x298E, &unit_object->location, &unit_object->bounding_sphere_center, unit_object->bounding_sphere_radius + 0.4f, nearby_objects, 256);
		for (long i = 0; i < num_objects; i++)
		{
			long object_index = nearby_objects[i];
			s_object_data *nearby_object = object_get(nearby_objects[i]);
			long object_type = (char)nearby_object->object_identifier.type;
			if ((unsigned long)(object_type - 2) <= 1)
				player_examine_nearby_item(player_index, object_index);
			if ((1 << object_type) & 0x2982)
			{
				for (long child_object_index = nearby_object->first_child_object_index; child_object_index != -1; child_object_index = object_get(child_object_index)->next_object_index)
				{
					if (num_objects >= sizeof(nearby_objects) / sizeof(nearby_objects[0]))
						break;
					nearby_objects[num_objects++] = child_object_index;
				}
			}
		}
	}
}

void player_find_nearby_interactions_hook(long player_index, s_player_action_context *out_action_context) // 0x108DD0C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_find_nearby_interactions_hook@@YAXJPAUs_player_action_context@@@Z");
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
		// long i;
			// long object_index;
			// s_object_data *object;
				// long child_filter;
					// s_object_data *child_object;
						// long child_object_index;
	// function call : void (*const)(long, s_cluster_reference *)
	// function call : short (*const)(long, long, s_cluster_reference const *, real_point3d const *, float, long *, short)
	// function call : bool (*const)(long, long, s_player_action_context *)
	// function call : bool (*const)(long, long, s_player_action_context *)
	// function call : bool (*const)(long, long, s_player_action_context *)
	// function call : bool (*const)(long, long, s_player_action_context *)

	long k_base_object_filter = 0x2BBF;
	out_action_context->interaction.object_index = -1;
	out_action_context->melee_target_object_index = -1;
	out_action_context->interaction.seat_index_or_pickup_flags = 0;
	out_action_context->interaction.type = 0;
	s_player_datum *player = player_get(player_index);
	if (player->unit_index == -1)
		return;
	s_object_data *unit = object_get(player->unit_index);
	if (unit->parent_object_index != -1 && !(player->flags & 0x4000))
		return;
	float radius = unit->bounding_sphere_radius + 0.4f + 0.1f;
	long results[256];
	s_cluster_reference location;
	((void (*)(long, s_cluster_reference *))0xB2E2F0)(player->unit_index, &location);
	long num_objects = ((short (*)(long, long, s_cluster_reference *, real_point3d *, float, long *, long))0xB35B60)(0, k_base_object_filter, &location, &unit->bounding_sphere_center, radius, results, 256);
	long k_ignore_distance_filter = 0x304;
	for (long i = 0; i < num_objects; i++)
	{
		long object_index = results[i];
		s_object_data *object = object_get(object_index);
		if ((1 << (char)object->object_identifier.type) & 0x1440)
			continue;
		if (!((1 << (char)object->object_identifier.type) & k_ignore_distance_filter) || sphere_intersects_sphere(object->bounding_sphere_center, object->bounding_sphere_radius, unit->bounding_sphere_center, radius))
		{
			long child_filter = 0x1440;
			switch ((char)object->object_identifier.type)
			{
			case 2:
				((void (*)(long, long, s_player_action_context *))0x538D00)(player_index, object_index, out_action_context);
				break;
			case 4:
			case 5:
			case 9:
				PlayerConsiderDeviceInteraction(player_index, object_index, out_action_context);
				break;
			case 1:
				((void (*)(long, long, s_player_action_context *))0x538B10)(player_index, object_index, out_action_context);
				child_filter = 0x1442;
			default:
			{
				s_object_data *child_object = nullptr;
				for (long child_object_index = object->first_child_object_index; child_object_index != -1; child_object_index = child_object->next_object_index)
				{
					if (num_objects >= _countof(results))
						break;
					child_object = object_get(child_object_index);
					if (!((1 << (char)child_object->object_identifier.type) & child_filter) && (!((1 << (char)object->object_identifier.type) & k_ignore_distance_filter) || sphere_intersects_sphere(child_object->bounding_sphere_center, child_object->bounding_sphere_radius, unit->bounding_sphere_center, radius)))
						results[num_objects++] = child_object_index;
				}
				break;
			}
			case 3:
				PlayerConsiderEquipmentInteraction(player_index, object_index, out_action_context);
				break;
			case 0:
				((void (*)(long, long, s_player_action_context *))0x5387F0)(player_index, object_index, out_action_context);
				break;
			}
			if ((1 << (char)object->object_identifier.type) & 0x2003)
				((void (*)(long, long, s_player_action_context *))0x5389E0)(player_index, results[i], out_action_context);
		}
	}
}

void player_control_update_player_hook(long player_index, long input_user_index, long controller_index, float world_delta, float game_delta) // 0x108DCFD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_control_update_player_hook@@YAXJJJMM@Z");
	// `anonymous-namespace'::player_control_update_player_hook
	// float game_delta;
	// void (*const player_control_update_player)(long, long, long, float, float);
	// function call : void (*const)(long, long, long, float, float)

	g_player_control_delta_msec = (long)(world_delta * 1000.0f);

	const auto player_control_update_player = (void(*)(long, long, long, float, float))0x5D4BF0;

	player_control_update_player(player_index, input_user_index, controller_index, world_delta, game_delta);
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

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { long g_player_control_delta_msec; }
