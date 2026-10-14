/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/game/engine/game_engine_events.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/engine/game_engine_player_traits.hpp"
#include "Blam/game/game_engine_candy_monitor.hpp"
#include "Blam/game/game_engine_globals.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/multiplayer_definitions.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/interface/chud/chud.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/simulation/game_interface/simulation_game_engine_player.hpp"
#include "Blam/simulation/simulation_entity_definition.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Modules/ModuleVoIP.hpp"
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

class Patch;
class c_bitstream;
struct c_entity_update_encode_helper;
struct c_game_engine;
struct c_player_traits;
struct lambda_1;
struct real_argb_color;
struct real_point3d;
struct real_vector3d;
struct s_chud_navpoint;
struct s_damage_reporting_info;
struct s_data_array;
struct s_game_engine_event_data;
struct s_game_engine_globals;
struct s_game_engine_status_response;
struct s_game_globals;
struct s_local_game_engine_globals;
struct s_multiplayer_globals_definition;
struct s_multiplayer_object_boundary_geometry_data;
struct s_multiplayer_weapon;
struct s_object_data;
struct s_object_definition;
struct s_object_placement_data;
struct s_player_datum;
struct s_scenario;
struct s_scenario_object;
struct s_simulation_game_engine_player_state_data;
struct s_simulation_player_netdebug_data;
struct s_unit_data;
struct tls_data;
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}
namespace Modules
{
	class ModuleVoIP;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace PlayerPodium {}
	using namespace Player::PlayerPodium;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace GameEngine {}
	using namespace Patches::GameEngine;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

//class game_engine_weapon_item_definition_index_from_absolute_weapons_selection_block_index_hook::__l11::<lambda_1>
//{
//public:
//	float operator()(s_multiplayer_weapon const &) const;
//};
//static_assert(sizeof(game_engine_weapon_item_definition_index_from_absolute_weapons_selection_block_index_hook::__l11::<lambda_1>) == 1, "Invalid game_engine_weapon_item_definition_index_from_absolute_weapons_selection_block_index_hook::__l11::<lambda_1> size");

/* ---------- prototypes */

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0x107AF6F0

float real_random_range(float min, float max); template<typename t_entry, typename t_weight_function> long compute_weighted_random_index(t_entry entries, long count, t_weight_function get_weight) { if (!count) return -1; float total_weight = 0.0f; for (long i = 0; i < count; i++) total_weight += get_weight(entries[i]); float random = real_random_range(0.0f, total_weight); for (long i = 0; i < count; i++) { float weight = get_weight(entries[i]); if (weight != 0.0f && weight > random) return i; random -= weight; } return -1; }  // hades: added for 0x107B0160
s_game_globals *game_globals_get();  // hades: added for 0x107B0160

template<typename t_arg0> static t_arg0 *object_get(unsigned long object_index) { return (t_arg0 *)object_get(object_index); }  // hades: a file-local template in the original (undecorated `object_get<T>`), defined so it is emitted;  // hades: added for 0x107AE860

extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x107AE540

extern void *offset_pointer(void *pointer, long offset);  // hades: added for 0x107AEC40
extern long (*const game_time_get)();  // hades: added for 0x107AEC40

#include "Modules/ModuleServer.hpp"  // hades: added for 0x107AFB40
extern long(__cdecl *const game_seconds_to_ticks_round)(float);  // hades: added for 0x107AFB40

namespace Patches
{
	namespace GameEngine
	{
		extern void ApplyAll();
	}
}

void game_engine_tick_hook();
__int32 GetPreRoundTicks();
__int32 game_engine_get_delta_ticks_hook();
__int32 game_engine_get_player_state_hook(__int32 player_index);
bool game_engine_hud_get_state_message_hook(__int32 hudIndex, wchar_t *buff, __int32 len, bool a4);
long game_engine_post_game_time_hook(float seconds);
void game_engine_assemble_player_traits_hook(long player_index);
bool __fastcall c_game_engine__build_player_navpoint_hook(c_game_engine *thisptr, void *__formal, long output_user_index, long player_index, long unknown_player_index, bool a5, s_chud_navpoint *navpoint);
void __fastcall c_game_engine__build_player_update_hook(void *thisptr, void *__formal, short absolute_player_index, unsigned long long *in_out_flags, long state_data_size, s_simulation_game_engine_player_state_data *data);
bool __fastcall c_game_engine__apply_player_update_hook(void *thisptr, void *__formal, short absolute_player_index, unsigned long long *component_mask, long state_data_size, s_simulation_game_engine_player_state_data *data);
bool __fastcall c_simulation_game_engine_player_entity_definition__entity_update_decode_hook(void *thisptr, void *__formal, bool a1, unsigned long long *out_update_mask, long state_data_size, s_simulation_game_engine_player_state_data *state_data, c_bitstream *stream, bool a6);
bool __fastcall c_simulation_game_engine_player_entity_definition__entity_update_encode_hook(void *thisptr, void *__formal, unsigned long a1, unsigned long long *update_mask, unsigned long long *out_update_mask, long state_data_size, s_simulation_game_engine_player_state_data *data, __int32 a6, c_bitstream *bitstream, long parent_component_count, bool a9);
void __fastcall c_game_engine__build_player_baseline_hook(void *thisptr, void *__formal, short absolute_player_index, long state_data_size, s_simulation_game_engine_player_state_data *state_data);
void game_engine_update_player_spawn_timer_hook(long player_index);
void game_engine_reset_stats_for_round_switch_hook();
bool game_engine_player_is_out_of_lives_hook(long player_index);
bool game_engine_team_is_out_of_lives_hook(long teamIndex);
void game_engine_add_starting_equipment_hook(long unit_index);
static void multiplayer_object_submit_boundary_hook(s_multiplayer_object_boundary_geometry_data *zoneShape, real_argb_color *color, long object_index);
long game_engine_weapon_item_definition_index_from_absolute_weapons_selection_block_index_hook(short selection_index, long weapon_set);
bool game_engine_object_is_dead(long object_index);
bool game_engine_object_has_been_abandoned_hook(long object_index);
long candy_spawner_object_new_hook(s_object_placement_data *placement_data);

/* ---------- globals */

namespace Player { namespace PlayerPodium { extern bool PodiumStarted(); } }  // hades: added for 0x107AEB40
extern long(__cdecl *const game_seconds_integer_to_ticks)(long);  // hades: added for 0x107AB1D0

namespace Utils
{
	Modules::ModuleVoIP *Utils::Singleton<Modules::ModuleVoIP>::m_instance; // 0x1138DD74
}

/* ---------- private variables */

/* ---------- public code */

// mangled_x86(MANGLED_DEFAULT, "??0s_game_engine_event_data@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??1Patch@@QAE@XZ"); no body to assert in
_inline Patch::~Patch() = default; // 0x107A9240

// mangled_x86(MANGLED_DEFAULT, "??4s_damage_reporting_info@@QAEAAU0@ABU0@@Z"); no body to assert in
_inline s_damage_reporting_info &s_damage_reporting_info::operator=(s_damage_reporting_info const &__that) = default; // 0x107A92D0

namespace Patches
{
	namespace GameEngine
	{
		void ApplyAll() // 0x107A96D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@GameEngine@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x34A1B5, reinterpret_cast<void *>(0x53A290), static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x155621, game_engine_player_is_out_of_lives_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x155630, game_engine_player_is_out_of_lives_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x15583E, game_engine_team_is_out_of_lives_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x15584B, game_engine_team_is_out_of_lives_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x2E4AA0, game_engine_hud_get_state_message_hook).Apply();
			Hook(0x150830, game_engine_get_player_state_hook).Apply();
			Hook(0x349280, c_game_engine__build_player_navpoint_hook).Apply();
			Hook(0x1527F7, game_engine_tick_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x5DD4BE, game_engine_get_delta_ticks_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x5DAD4A, game_engine_get_delta_ticks_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x130FAE, game_engine_post_game_time_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x13D3D7, { 0xEB }).Apply();
			Hook(0x1A4330, game_engine_update_player_spawn_timer_hook).Apply();
			Hook(0x349580, c_game_engine__build_player_update_hook).Apply();
			Hook(0x348AF0, c_game_engine__apply_player_update_hook).Apply();
			Hook(0x349200, c_game_engine__build_player_baseline_hook).Apply();
			Hook(0xBA3E0, c_simulation_game_engine_player_entity_definition__entity_update_decode_hook).Apply();
			Hook(0xBA780, c_simulation_game_engine_player_entity_definition__entity_update_encode_hook).Apply();
			Pointer(0x4BBE21).Write(static_cast<e_simulation_game_engine_player_components>(0x15));
			Pointer(0x5A148A).Write<unsigned int>(0x1FFFFF);
			Pointer(0x5A2609).Write<unsigned int>(0x1FFFFF);
			Hook(0x152FEB, game_engine_assemble_player_traits_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1516B8, game_engine_reset_stats_for_round_switch_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x1A31C1, { 0x75 }).Apply();
			Hook(0x1A30F0, game_engine_add_starting_equipment_hook).Apply();
			Hook(0x365D56, multiplayer_object_submit_boundary_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1CECD0, game_engine_weapon_item_definition_index_from_absolute_weapons_selection_block_index_hook).Apply();
			Hook(0x18F9E0, game_engine_object_has_been_abandoned_hook).Apply();
			Hook(0x190F30, candy_spawner_object_new_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
		}
	}
}

/* ---------- private code */

void game_engine_tick_hook() // 0x107AFD30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_tick_hook@@YAXXZ");
	// `anonymous-namespace'::game_engine_tick_hook
	// procedure flags: nofpo
	// void *engine;
	// void *(*const game_get_current_engine)();
	// function call : void *(*const)()
	// function call : bool (*const)(char)
	// function call : void (*)(void *)

	void *(*const get_game_engine)() = (void *(*const)())0x5ce150;

	void *engine = get_game_engine();
	if (!engine)
		return;
	if (!((bool (*)(int))0x5523a0)(4))
	{
		(*(void (__thiscall **)(void *))(*(int *)engine + 104))(engine);
	}
}

__int32 GetPreRoundTicks() // 0x107AB1D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetPreRoundTicks@@YAHXZ");
	// `anonymous-namespace'::GetPreRoundTicks
	// procedure flags: nofpo
	// __int32 offset;
	// long gameType;
	// function call : long (*const)(long)

	long gameType = *(long *)offset_pointer(tls_getd().game_engine_globals, 81328);
	__int32 offset = 0;
	if (gameType == 8)
		offset--;

	return game_seconds_integer_to_ticks(Utils::Singleton<Modules::ModuleServer>::Instance().VarServerCountdownClient->ValueInt + offset + 5);
}

__int32 game_engine_get_delta_ticks_hook() // 0x107AEC40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_get_delta_ticks_hook@@YAHXZ");
	// `anonymous-namespace'::game_engine_get_delta_ticks_hook
	// procedure flags: nofpo
	// long delta;
	// long round_start_time;
	// function call : long (*const)()

	long round_start_time = *(long *)offset_pointer(tls_getd().game_engine_globals, 0xE10C);
	long delta = game_time_get() - round_start_time - GetPreRoundTicks();
	if (delta < 0)
	{
		delta = 0;
	}

	return delta;
}

__int32 game_engine_get_player_state_hook(__int32 player_index) // 0x107AECE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_get_player_state_hook@@YAHH@Z");
	// `anonymous-namespace'::game_engine_get_player_state_hook
	// static ...; // 0x107AF0BC
	// static ...; // 0x107AF0A8
	// static ...; // 0x107AF09C
	// static ...; // 0x107AF094
// $LN11:
// $LN10:
// $LN9:
// $LN8:
	// __int32 player_index;
	// s_player_datum *player;
	// long (*const game_engine_get_winning_status)(long);
	// short seconds_remaining;
	// long round_delta_time;
	// long state_index;
	// long (*const game_engine_variant_get_score_to_win)();
	// bool (*const game_engine_player_is_out_of_lives)(long);
	// c_game_engine *engine;
	// long round_start_time;
	// bool state_index_valid;
	// bool (*const game_engine_round_condition_test)(char);
	// bool unlimited;
	// function call : c_game_engine *(*const)()
	// function call : __int32 (*)(c_game_engine *, __int32, bool *)
	// function call : bool (*const)()
	// function call : long (*const)(long)
	// function call : bool (*const)(long)
	// function call : bool (*const)(char)
	// function call : long (*const)(long)
	// function call : long (*const)()
	// function call : long (*const)(long)
	// function call : long (*const)()
	// function call : long (*const)(long)

	long (*const game_engine_get_winning_status)(long) = reinterpret_cast<long (*)(long)>(0x554EB0);
	bool (*const game_engine_player_is_out_of_lives)(long) = reinterpret_cast<bool (*)(long)>(0x552020);
	long (*const game_engine_variant_get_score_to_win)() = reinterpret_cast<long (*)()>(0x550B50);
	bool (*const game_engine_round_condition_test)(char) = reinterpret_cast<bool (*)(char)>(0x5523A0);
	bool state_index_valid = false;
	c_game_engine *engine = ((c_game_engine *(*)())0x5CE150)();
	long state_index = reinterpret_cast<long (__thiscall *)(c_game_engine *, long, bool *)>((*reinterpret_cast<void ***>(engine))[0x39])(engine, player_index, &state_index_valid);
	if (!state_index_valid && state_index != -1)
		return state_index;
	if (((bool (*)())0x531B20)())
	{
		switch (game_engine_get_winning_status(player_index))
		{
		case 0:
			return 8;
		case 1:
			return 10;
		case 2:
			return 11;
		case 3:
			return 9;
		}
		return state_index;
	}
	s_player_datum *player = player_get(player_index);
	if (!player)
		return state_index;
	short seconds_remaining = *(short *)offset_pointer(tls_getd().game_engine_globals, 0xF990);
	if (player->unit_index == -1)
	{
		if (game_engine_player_is_out_of_lives(player_index))
			return 4;
		if (player->flags & 0x1000)
			return 3;
		if (game_engine_round_condition_test(4))
			return 0x1D;
		if (player->respawn_timer_countdown_seconds >= 0)
			return 2;
		return state_index;
	}
	long round_start_time = *(long *)offset_pointer(tls_getd().game_engine_globals, 0xE10C);
	long round_delta_time = game_time_get() - round_start_time - game_seconds_integer_to_ticks(Utils::Singleton<Modules::ModuleServer>::Instance().VarServerCountdownClient->ValueInt + 4);
	if (round_delta_time < game_seconds_integer_to_ticks(3))
		return 0x13;
	if (seconds_remaining != -1 && seconds_remaining != 0 && seconds_remaining < 5)
		return 0x12;
	if (state_index != -1)
		return state_index;
	bool unlimited = game_engine_variant_get_score_to_win() <= 0;
	switch (game_engine_get_winning_status(player_index))
	{
	case 0:
		return unlimited ? 0x1A : 5;
	case 1:
		return unlimited ? 0x1C : 7;
	case 3:
		return unlimited ? 0x1B : 6;
	}
	return state_index;
}

bool game_engine_hud_get_state_message_hook(__int32 hudIndex, wchar_t *buff, __int32 len, bool a4) // 0x107AF1D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_hud_get_state_message_hook@@YA_NHPA_WH_N@Z");
	// `anonymous-namespace'::game_engine_hud_get_state_message_hook
	// static ...; // 0x107AF5CC
	// static ...; // 0x107AF59C
	// static ...; // 0x107AF594
	// __int32 hudIndex;
	// wchar_t *buff;
	// __int32 len;
	// bool a4;
	// long player_index;
	// void (*const build_multiplayer_string)(long, wchar_t *, void *, long, wchar_t *);
	// short round_state;
	// void (*const game_engine_get_universal_string)(unsigned long, wchar_t (&)[256]);
	// bool (*const string_list_get_normal_string)(long, unsigned long, wchar_t *);
		// e_game_engine_status state;
		// s_local_game_engine_globals::s_player_state &local_player_state;
			// s_game_engine_status_response const &state_response;
			// s_multiplayer_globals_definition *const mulg;
			// bool should_display;
			// unsigned long message;
				// long local_state;
				// wchar_t format[256];
		// wchar_t format[256];
	// function call : c_game_engine *(*const)()
	// function call : unsigned long (*const)(long)
	// function call : e_game_engine_status (*const)(long)
	// function call : void *(*const)(unsigned long, long)
	// function call : bool (*const)()
	// function call : bool (*const)(long, unsigned long, wchar_t *)
	// function call : void (*const)(long, wchar_t *, void *, long, wchar_t *)
	// function call : bool (*const)()
	// function call : void (*const)(unsigned long, wchar_t (&)[256])
	// function call : void (*const)(long, wchar_t *, void *, long, wchar_t *)
	// function call : void (*const)(unsigned long, wchar_t (&)[256])
	// function call : void (*const)(long, wchar_t *, void *, long, wchar_t *)
	// function call : void (*const)(unsigned long, wchar_t (&)[256])
	// function call : void (*const)(long, wchar_t *, void *, long, wchar_t *)

	bool (*const string_list_get_normal_string)(long, unsigned long, wchar_t *) = reinterpret_cast<bool (*)(long, unsigned long, wchar_t *)>(0x51E120);
	void (*const build_multiplayer_string)(long, wchar_t *, void *, long, wchar_t *) = reinterpret_cast<void (*)(long, wchar_t *, void *, long, wchar_t *)>(0x5CE070);
	void (*const game_engine_get_universal_string)(unsigned long, wchar_t (&)[256]) = reinterpret_cast<void (*)(unsigned long, wchar_t (&)[256])>(0x550EA0);
	if (!((c_game_engine *(*)())0x5CE150)())
		return false;
	long player_index = ((long (*)(long))0x589C60)(hudIndex);
	short round_state = *(short *)offset_pointer(tls_getd().game_engine_globals, 0xE108);
	if (round_state == 1)
	{
		e_game_engine_status state = ((e_game_engine_status (*)(long))0x550830)(player_index);
		s_local_game_engine_globals::s_player_state &local_player_state = tls_getd().local_game_engine_globals->player_states[hudIndex];
		if (local_player_state.state == -1 || local_player_state.field_8 == -1 || local_player_state.state != state)
		{
			*buff = 0;
			return false;
		}
		else
		{
			s_multiplayer_globals_definition *const mulg = (s_multiplayer_globals_definition *)tag_get('mulg', game_globals_get()->MultiplayerGlobals.index);
			s_game_engine_status_response const &state_response = mulg->runtime->state_responses[local_player_state.field_8];
			unsigned long message = ((bool (*)())0x5565E0)() ? state_response.team_message : state_response.ffa_message;
			bool should_display = true;
			if (a4)
			{
				long local_state = local_player_state.state;
				if (local_state == 0x19 || local_state == 5 || local_state == 0x1A || local_state == 6 || local_state == 0x1B || local_state == 7 || local_state == 0x1C)
					should_display = false;
			}
			if (should_display && message != -1 && message != 0)
			{
				wchar_t format[256];
				string_list_get_normal_string(mulg->runtime->in_game_strings.index, message, format);
				build_multiplayer_string(player_index, format, nullptr, len, buff);
				return true;
			}
			else
			{
				*buff = 0;
			}
		}
	}
	else if (((bool (*)())0x531B20)())
	{
		wchar_t format[256];
		game_engine_get_universal_string(0xEC, format);
		build_multiplayer_string(player_index, format, nullptr, len, buff);
		return true;
	}
	else if (round_state == 2)
	{
		wchar_t format[256];
		game_engine_get_universal_string(0xED, format);
		build_multiplayer_string(player_index, format, nullptr, len, buff);
		return true;
	}
	else if (round_state == 3)
	{
		wchar_t format[256];
		game_engine_get_universal_string(0xEE, format);
		build_multiplayer_string(player_index, format, nullptr, len, buff);
		return true;
	}
	return false;
}

long game_engine_post_game_time_hook(float seconds) // 0x107AFB40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_post_game_time_hook@@YAJM@Z");
	// `anonymous-namespace'::game_engine_post_game_time_hook
	// float seconds;
	// function call : long (*const)(float)

	return game_seconds_to_ticks_round((float)Utils::Singleton<Modules::ModuleServer>::Instance().VarPostGameTimeSeconds->ValueInt + 0.1f);
}

void game_engine_assemble_player_traits_hook(long player_index) // 0x107AEB40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_assemble_player_traits_hook@@YAXJ@Z");
	// `anonymous-namespace'::game_engine_assemble_player_traits_hook
	// static ...; // 0x107AEC00
	// static ...; // 0x107AEBF4
	// static ...; // 0x107AEBEC
	// long player_index;
	// void (*const game_engine_apply_player_traits)(long, c_player_traits *);
	// void (*const game_engine_assemble_player_traits)(long);
		// c_player_traits traits;
	// function call : void (*const)(long, c_player_traits *)
	// function call : void (*const)(long)

	void (*const game_engine_assemble_player_traits)(long) = (void (*const)(long))0x5cbf90;
	void (*const game_engine_apply_player_traits)(long, c_player_traits *) = (void (*const)(long, c_player_traits *))0x5cb7c0;

	if (::Player::PlayerPodium::PodiumStarted())
	{
		c_player_traits traits;
		traits.initialize();
		game_engine_apply_player_traits(player_index, &traits);
	}
	else
	{
		game_engine_assemble_player_traits(player_index);
	}
}

bool __fastcall c_game_engine__build_player_navpoint_hook(c_game_engine *thisptr, void *__formal, long output_user_index, long player_index, long unknown_player_index, bool a5, s_chud_navpoint *navpoint) // 0x107AC1D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_game_engine__build_player_navpoint_hook@@YI_NPAUc_game_engine@@PAXJJJ_NPAUs_chud_navpoint@@@Z");
	// `anonymous-namespace'::c_game_engine__build_player_navpoint_hook
	// s_chud_navpoint *navpoint;
	// s_player_datum *player;
	// bool is_enemy;
	// s_player_datum *our_player;
	// unsigned long (*const chud_get_team_marker_color)(bool, long, long);
	// bool (*const game_engine_team_is_enemy)(c_game_engine *, long, long);
	// wchar_t *(*const ustrnzcpy)(wchar_t *, wchar_t *, __int32);
	// bool result;
	// s_game_engine_globals::s_unknown_waypoint *const waypoint_data;
	// bool use_h3_style;
		// long unit_index;
		// Blam::Network::Session *session;
			// __int32 player_index;
		// s_unit_data *dead_unit;
		// long dead_unit_index;
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(c_game_engine *, long, long)
	// function call : unsigned long (*const)(bool, long, long)
	// function call : wchar_t *(*const)(wchar_t *, wchar_t *, __int32)
	// function call : void (*const)(long, real_point3d *)
	// function call : long (*const)(long)
	// function call : long (*const)()
	// function call : void (*const)(long, real_point3d *)

	extern long (*const game_seconds_integer_to_ticks)(long);
	extern long (*const game_time_get)();
	wchar_t *(*const ustrnzcpy)(wchar_t *, wchar_t *, __int32) = reinterpret_cast<wchar_t *(*)(wchar_t *, wchar_t *, __int32)>(0x4ECCD0);
	unsigned long (*const chud_get_team_marker_color)(bool, long, long) = reinterpret_cast<unsigned long (*)(bool, long, long)>(0xAAF040);
	bool (__thiscall *const game_engine_team_is_enemy)(c_game_engine *, long, long) = *(bool (__thiscall **)(c_game_engine *, long, long))offset_pointer(*(void **)thisptr, 0xB8);
	s_player_datum *player = player_get(player_index);
	s_player_datum *our_player = player_get(((unsigned long (*)(long))0x589C60)(output_user_index));
	bool is_enemy = game_engine_team_is_enemy(thisptr, our_player->configuration.host.team, player->configuration.host.team);
	s_game_engine_globals::s_unknown_waypoint *const waypoint_data = &tls_getd().game_engine_globals->unknown_waypoints[player_index & 0xF];
	bool result = false;
	bool use_h3_style = Modules::ModuleServer::Instance().VarHUDWaypointStyleClient->ValueInt == 1;
	navpoint->flags = 0;
	navpoint->objective_icon = -1;
	navpoint->arrow_icon = is_enemy ? 1 : 0;
	navpoint->marker_color = chud_get_team_marker_color(is_enemy, player->configuration.host.team, -1);
	navpoint->opacity = 1.0f;
	if (unknown_player_index != -1 && a5)
	{
		long unit_index = player_get(unknown_player_index)->unit_index;
		if (unit_index != -1 && object_get<s_unit_data>(unit_index)->active_camouflage > 0.75)
			navpoint->opacity = 0.0f;
	}
	navpoint->player_index = player_index;
	if (player_index == unknown_player_index)
		navpoint->flags |= 0x20;
	else
		navpoint->flags &= ~0x20;
	if (use_h3_style && is_enemy)
		navpoint->service_tag[0] = 0;
	else
		ustrnzcpy(navpoint->service_tag, player->configuration.host.appearance.service_tag, 5);
	if (player->unit_index != -1)
	{
		((void (*)(long, real_point3d *))0xB441B0)(player->unit_index, &navpoint->position);
		navpoint->position.x += global_up3d.i * 0.05f;
		navpoint->position.y += global_up3d.j * 0.05f;
		navpoint->position.z += global_up3d.k * 0.05f;
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (session && player)
		{
			__int32 player_index = session->MembershipInfo.GetPeerPlayer(player->machine_index);
			if (player_index != -1 && (Modules::ModuleVoIP::Instance().playersSpeaking & (1 << player_index)))
			{
				if (!is_enemy)
					navpoint->flags |= 0x10;
				else
					navpoint->objective_icon = 0;
			}
		}
		if (!is_enemy && waypoint_data->waypoint_action != 2)
		{
			result = true;
			if (waypoint_data->waypoint_action == 1)
				navpoint->flags |= 0x4;
			else if (waypoint_data->waypoint_action == 3)
				navpoint->flags |= 0x8;
			if (navpoint->objective_icon == -1)
			{
				if (use_h3_style)
				{
					if (player->traits.appearance.waypoint == 2 || player->traits.appearance.waypoint == 3)
						navpoint->arrow_icon = 0;
					else
						navpoint->arrow_icon = -1;
				}
				else
				{
					navpoint->arrow_icon = 3;
				}
			}
			return result;
		}
		{
			result = true;
			if (navpoint->objective_icon == -1 || navpoint->objective_icon == 0)
			{
				if (use_h3_style)
				{
					if (player->traits.appearance.waypoint == 3)
						navpoint->arrow_icon = 1;
					else
						navpoint->arrow_icon = -1;
				}
				else
				{
					navpoint->arrow_icon = 3;
				}
			}
			return result;
		}
	}
	{
		if (waypoint_data->death_acknowledged && waypoint_data->respawn_timer1 > 0)
		{
			navpoint->position = waypoint_data->death_position;
			result = true;
		}
		else
		{
			long dead_unit_index = player->dead_unit_index;
			if (player->dead_unit_index == -1)
				return false;
			s_unit_data *dead_unit = (s_unit_data *)object_get(dead_unit_index);
			if (!dead_unit)
				return false;
			if (game_time_get() - dead_unit->time_of_death >= game_seconds_integer_to_ticks(3))
				return false;
			((void (*)(long, real_point3d *))0xB441B0)(player->dead_unit_index, &navpoint->position);
			navpoint->position.x += global_up3d.i * 0.05f;
			navpoint->position.y += global_up3d.j * 0.05f;
			navpoint->position.z += global_up3d.k * 0.05f;
		}
		if (!is_enemy)
		{
			navpoint->objective_icon = 1;
			navpoint->marker_color = 3;
			if (use_h3_style)
				navpoint->arrow_icon = 0;
			else
				navpoint->arrow_icon = 3;
		}
		if (navpoint->objective_icon == -1 || navpoint->objective_icon == 0)
		{
			if (use_h3_style)
				navpoint->arrow_icon = -1;
			else
				navpoint->arrow_icon = 3;
		}
		return result;
	}
}

void __fastcall c_game_engine__build_player_update_hook(void *thisptr, void *__formal, short absolute_player_index, unsigned long long *in_out_flags, long state_data_size, s_simulation_game_engine_player_state_data *data) // 0x107AC990
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_game_engine__build_player_update_hook@@YIXPAX0FPA_KJPAUs_simulation_game_engine_player_state_data@@@Z");
	// `anonymous-namespace'::c_game_engine__build_player_update_hook
	// s_simulation_game_engine_player_state_data *data;
	// s_player_datum *player;
	// unsigned long long updated_flags;
	// bool (*const simulation_update_player_netdebug_data)(long, s_simulation_player_netdebug_data *);
	// tls_data *tls;
		// char waypoint_action;
		// bool blocking_teleporter;
		// long last_betrayer_player_index;
		// long revenge_player_index;
	// function call : void *(*const)(s_data_array const *, unsigned long)

	extern float normalize3d(real_vector3d *);
	extern void *(*const datum_try_and_get_absolute)(s_data_array const *, unsigned long);
	bool (*const simulation_update_player_netdebug_data)(long, s_simulation_player_netdebug_data *) = reinterpret_cast<bool (*)(long, s_simulation_player_netdebug_data *)>(0x4424F0);
	tls_data *tls = &tls_getd();
	s_player_datum *player = (s_player_datum *)datum_try_and_get_absolute((s_data_array *)tls->players, absolute_player_index);
	if (!player)
	{
		*in_out_flags = 0;
		return;
	}
	unsigned long long updated_flags = 0;
	if ((*in_out_flags & 0x1) != 0 && (data->initial_spawn != ((player->flags & 0x8) != 0) || data->respawn_timer != player->respawn_timer_countdown_seconds))
	{
		updated_flags |= 0x1;
		data->initial_spawn = (player->flags & 0x8) != 0;
		data->respawn_timer = (short)player->respawn_timer_countdown_seconds;
	}
	if ((*in_out_flags & 0x2) != 0 && data->early_respawn_requested != player->early_respawn_requested)
	{
		updated_flags |= 0x2;
		data->early_respawn_requested = player->early_respawn_requested;
	}
	if ((*in_out_flags & 0x4) != 0 && !data->player_traits.vitality.equivalent(&player->traits.vitality))
	{
		updated_flags |= 0x4;
		data->player_traits.vitality.set(&player->traits.vitality, false);
	}
	if ((*in_out_flags & 0x100000) != 0 && !data->player_traits.extended.equivalent(&player->traits.extended))
	{
		updated_flags |= 0x100000;
		data->player_traits.extended.set(&player->traits.extended, false);
	}
	if ((*in_out_flags & 0x8) != 0 && !data->player_traits.weapons.equivalent(&player->traits.weapons))
	{
		updated_flags |= 0x8;
		data->player_traits.weapons.set(&player->traits.weapons, false);
	}
	if ((*in_out_flags & 0x10) != 0 && !data->player_traits.movement.equivalent(&player->traits.movement))
	{
		updated_flags |= 0x10;
		data->player_traits.movement.set(&player->traits.movement, false);
	}
	if ((*in_out_flags & 0x20) != 0 && !data->player_traits.appearance.equivalent(&player->traits.appearance))
	{
		updated_flags |= 0x20;
		data->player_traits.appearance.set(&player->traits.appearance, false);
	}
	if ((*in_out_flags & 0x40) != 0 && !data->player_traits.sensors.equivalent(&player->traits.sensors))
	{
		updated_flags |= 0x40;
		data->player_traits.sensors.set(&player->traits.sensors, false);
	}
	if ((*in_out_flags & 0x80) != 0)
	{
		char waypoint_action = tls->game_engine_globals->unknown_waypoints[absolute_player_index].waypoint_action;
		if (data->waypoint_action != waypoint_action)
		{
			updated_flags |= 0x80;
			data->waypoint_action = waypoint_action;
		}
	}
	if ((*in_out_flags & 0x100) != 0)
	{
		bool blocking_teleporter = player->blocking_teleporter > 0;
		if (data->blocking_teleporter != blocking_teleporter)
		{
			updated_flags |= 0x100;
			data->blocking_teleporter = blocking_teleporter;
		}
	}
	if ((*in_out_flags & 0x400) != 0 && data->lives_remaining != player->lives)
	{
		updated_flags |= 0x400;
		data->lives_remaining = player->lives;
	}
	if ((*in_out_flags & 0x800) != 0)
	{
		long last_betrayer_player_index = player->game_grief_player_index;
		if (last_betrayer_player_index != -1)
			last_betrayer_player_index = (unsigned short)player->game_grief_player_index;
		if (data->last_betrayer_player_index != last_betrayer_player_index)
		{
			updated_flags |= 0x800;
			data->last_betrayer_player_index = last_betrayer_player_index;
		}
	}
	if ((*in_out_flags & 0x80000) != 0)
	{
		long revenge_player_index = player->revenge_player_Index;
		if (revenge_player_index != -1)
			revenge_player_index = (unsigned short)revenge_player_index;
		if (revenge_player_index != data->revenge_last_killer_player_index)
		{
			updated_flags |= 0x80000;
			data->revenge_last_killer_player_index = revenge_player_index;
			data->revenge_damage_report = static_cast<s_damage_reporting_info const &>(player->revenge_event_type);
		}
	}
	if ((*in_out_flags & 0x1000) != 0 && data->vehicle_entrance_ban != ((player->flags & 0x400) != 0))
	{
		updated_flags |= 0x1000;
		data->vehicle_entrance_ban = (player->flags & 0x400) != 0;
	}
	if ((*in_out_flags & 0x2000) != 0 && data->active_in_game != (player->flags & 0x1))
	{
		updated_flags |= 0x2000;
		data->active_in_game = player->flags & 0x1;
	}
	if ((*in_out_flags & 0x4000) != 0 && data->sitting_out != ((player->flags & 0x1000) != 0))
	{
		updated_flags |= 0x4000;
		data->sitting_out = (player->flags & 0x1000) != 0;
	}
	if ((*in_out_flags & 0x8000) != 0 && data->desired_respawn_player_index != (unsigned short)player->spectating_player_index)
	{
		updated_flags |= 0x8000;
		data->desired_respawn_player_index = (short)player->spectating_player_index;
	}
	if ((*in_out_flags & 0x10000) != 0 && player->unit_index != -1)
	{
		data->player_control_aiming = object_get<s_unit_data>(player->unit_index)->desired_aiming_vector;
		normalize3d(&data->player_control_aiming);
		updated_flags |= 0x10000;
	}
	if ((*in_out_flags & 0x20000) != 0 && data->player_character_type_index != player->character_type_index)
	{
		updated_flags |= 0x20000;
		data->player_character_type_index = player->character_type_index;
	}
	*in_out_flags = updated_flags;
}

bool __fastcall c_game_engine__apply_player_update_hook(void *thisptr, void *__formal, short absolute_player_index, unsigned long long *component_mask, long state_data_size, s_simulation_game_engine_player_state_data *data) // 0x107AB520
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_game_engine__apply_player_update_hook@@YI_NPAX0FPA_KJPAUs_simulation_game_engine_player_state_data@@@Z");
	// `anonymous-namespace'::c_game_engine__apply_player_update_hook
	// s_simulation_game_engine_player_state_data *data;
	// s_player_datum *player;
	// long (*const game_engine_sandbox_get_player_chief_biped_unit_index)(long);
	// tls_data *tls;
	// void (*const unit_set_aiming_vectors)(long, real_vector3d *, real_vector3d *);
	// void (*const player_control_set_facing)(long, real_vector3d *);
		// long respawn_timer_ticks;
		// long game_grief_player_index;
		// long revenge_player_index;
		// long player_index;
		// long unit_index;
		// long input_user_index;
	// function call : void *(*const)(s_data_array const *, unsigned long)
	// function call : long (*const)(float)
	// function call : void (*const)(long, real_point3d *)
	// function call : void *(*const)(s_data_array const *, unsigned long)
	// function call : long (*const)(long)
	// function call : void *(*const)(s_data_array const *, unsigned long)
	// function call : long (*const)(long)
	// function call : long (*const)(long)
	// function call : long (*const)(long)
	// function call : long (*const)(long)
	// function call : bool (*const)(long, long *, long *)
	// function call : long (*const)(long)
	// function call : void (*const)(long, real_vector3d *, real_vector3d *)
	// function call : void (*const)(long, real_vector3d *)
	// function call : long (*const)(long)
	// function call : bool (*const)(long)

	extern void *(*const datum_try_and_get_absolute)(s_data_array const *, unsigned long);
	extern long (*const game_seconds_to_ticks_round)(float);
	long (*const game_engine_sandbox_get_player_chief_biped_unit_index)(long) = reinterpret_cast<long (*)(long)>(0x59A980);
	void (*const unit_set_aiming_vectors)(long, real_vector3d *, real_vector3d *) = reinterpret_cast<void (*)(long, real_vector3d *, real_vector3d *)>(0xB48590);
	void (*const player_control_set_facing)(long, real_vector3d *) = reinterpret_cast<void (*)(long, real_vector3d *)>(0x5D4700);
	tls_data *tls = &tls_getd();
	s_player_datum *player = (s_player_datum *)datum_try_and_get_absolute((s_data_array *)tls->players, absolute_player_index);
	if (!player)
		return false;
	if ((*component_mask & 0x1) != 0)
	{
		if (data->initial_spawn)
			player->flags |= 0x8;
		else
			player->flags &= ~0x8;
		player->respawn_timer_countdown_seconds = data->respawn_timer;
		long respawn_timer_ticks = game_seconds_to_ticks_round((float)data->respawn_timer);
		if (respawn_timer_ticks > 0 && player->dead_unit_index != -1)
		{
			if (player->dead_unit_index == tls->game_engine_globals->unknown_waypoints[absolute_player_index].dead_unit_index)
			{
				tls->game_engine_globals->unknown_waypoints[absolute_player_index].respawn_timer1 = (short)respawn_timer_ticks;
				tls->game_engine_globals->unknown_waypoints[absolute_player_index].respawn_timer2 = (short)respawn_timer_ticks;
			}
			else
			{
				tls->game_engine_globals->unknown_waypoints[absolute_player_index].death_acknowledged = true;
				tls->game_engine_globals->unknown_waypoints[absolute_player_index].dead_unit_index = player->dead_unit_index;
				tls->game_engine_globals->unknown_waypoints[absolute_player_index].respawn_timer1 = (short)respawn_timer_ticks;
				tls->game_engine_globals->unknown_waypoints[absolute_player_index].respawn_timer2 = (short)respawn_timer_ticks;
				((void (*)(long, real_point3d *))0xB441B0)(player->dead_unit_index, &tls->game_engine_globals->unknown_waypoints[absolute_player_index].death_position);
			}
		}
	}
	if ((*component_mask & 0x2) != 0)
		player->early_respawn_requested = data->early_respawn_requested;
	if ((*component_mask & 0x4) != 0)
		player->traits.vitality.set(&data->player_traits.vitality, false);
	if ((*component_mask & 0x100000) != 0)
		player->traits.extended.set(&data->player_traits.extended, false);
	if ((*component_mask & 0x8) != 0)
		player->traits.weapons.set(&data->player_traits.weapons, false);
	if ((*component_mask & 0x10) != 0)
		player->traits.movement.set(&data->player_traits.movement, false);
	if ((*component_mask & 0x20) != 0)
		player->traits.appearance.set(&data->player_traits.appearance, false);
	if ((*component_mask & 0x40) != 0)
		player->traits.sensors.set(&data->player_traits.sensors, false);
	if ((*component_mask & 0x80) != 0)
		tls->game_engine_globals->unknown_waypoints[absolute_player_index].waypoint_action = data->waypoint_action;
	if ((*component_mask & 0x100) != 0)
	{
		if (data->blocking_teleporter)
			player->flags |= 0x4;
		else
			player->flags &= ~0x4;
	}
	if ((*component_mask & 0x200) != 0)
		tls->game_engine_globals->player_netdebug[absolute_player_index] = data->netdebug_data;
	if ((*component_mask & 0x400) != 0)
		player->lives = data->lives_remaining;
	if ((*component_mask & 0x800) != 0)
	{
		long game_grief_player_index;
		if (datum_try_and_get_absolute((s_data_array *)tls->players, data->last_betrayer_player_index))
			game_grief_player_index = ((long (*)(long))0x53B1A0)(data->last_betrayer_player_index);
		else
			game_grief_player_index = -1;
		player->game_grief_player_index = game_grief_player_index;
	}
	if ((*component_mask & 0x80000) != 0)
	{
		long revenge_player_index;
		if (datum_try_and_get_absolute((s_data_array *)tls->players, data->revenge_last_killer_player_index))
			revenge_player_index = ((long (*)(long))0x53B1A0)(data->revenge_last_killer_player_index);
		else
			revenge_player_index = -1;
		player->revenge_player_Index = revenge_player_index;
		player->revenge_event_type = static_cast<s_damage_reporting_info const &>(data->revenge_damage_report);
	}
	if ((*component_mask & 0x1000) != 0)
	{
		if (data->vehicle_entrance_ban)
			player->flags |= 0x400;
		else
			player->flags &= ~0x400;
	}
	if ((*component_mask & 0x2000) != 0)
	{
		if (data->active_in_game)
			player->flags |= 0x1;
		else
			player->flags &= ~0x1;
	}
	if ((*component_mask & 0x4000) != 0)
	{
		if (data->sitting_out)
			player->flags |= 0x1000;
		else
			player->flags &= ~0x1000;
	}
	if ((*component_mask & 0x8000) != 0)
		player->spectating_player_index = ((long (*)(long))0x53B1A0)(data->desired_respawn_player_index);
	if ((*component_mask & 0x10000) != 0)
	{
		long player_index = ((long (*)(long))0x53B1A0)(absolute_player_index);
		long input_user_index = ((long (*)(long))0x589B00)(player_index);
		long unit_index = player->unit_index;
		if (unit_index != -1)
		{
			if (((bool (*)(long, long, long))0x59A6F0)(player_index, 0, 0))
			{
				unit_index = game_engine_sandbox_get_player_chief_biped_unit_index(player_index);
				if (unit_index == -1)
					unit_index = player->unit_index;
			}
			unit_set_aiming_vectors(unit_index, &data->player_control_aiming, &data->player_control_aiming);
		}
		if (input_user_index != -1)
			player_control_set_facing(input_user_index, &data->player_control_aiming);
	}
	if ((*component_mask & 0x20000) != 0)
	{
		long player_index = ((long (*)(long))0x53B1A0)(absolute_player_index);
		player->character_type_index = (short)data->player_character_type_index;
		if (((bool (*)(long))0x53B4E0)(player_index))
			Player::CPlayerCharacterSystem::UpdateLocalPlayerHudGlobals();
	}
	return true;
}

bool __fastcall c_simulation_game_engine_player_entity_definition__entity_update_decode_hook(void *thisptr, void *__formal, bool a1, unsigned long long *out_update_mask, long state_data_size, s_simulation_game_engine_player_state_data *state_data, c_bitstream *stream, bool a6) // 0x107AD5E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_simulation_game_engine_player_entity_definition__entity_update_decode_hook@@YI_NPAX0_NPA_KJPAUs_simulation_game_engine_player_state_data@@PAVc_bitstream@@1@Z");
	// `anonymous-namespace'::c_simulation_game_engine_player_entity_definition__entity_update_decode_hook
	// bool a6;
	// unsigned long long update_mask;
	// long (*const player_try_and_get_player_index_from_absolute_player_index)(long);
	// void (*const damage_reporting_info_decode)(c_bitstream *, s_damage_reporting_info *);
		// long desired_respawn_player_index;
	// function call : void (*const)(c_bitstream *, s_damage_reporting_info *)
	// function call : long (*const)(long)

	long (*const player_try_and_get_player_index_from_absolute_player_index)(long) = reinterpret_cast<long (*)(long)>(0x53FF70);
	void (*const damage_reporting_info_decode)(c_bitstream *, s_damage_reporting_info *) = reinterpret_cast<void (*)(c_bitstream *, s_damage_reporting_info *)>(0xB7FE50);
	unsigned long long update_mask = 0;
	if (stream->read_bool("respawn-exists"))
	{
		state_data->initial_spawn = stream->read_bool("initial-spawn");
		state_data->respawn_timer = stream->read_integer("respawn-timer", 10);
		update_mask |= 0x1;
	}
	if (stream->read_bool("early-respawn-requested-exists"))
	{
		state_data->early_respawn_requested = stream->read_bool("early-respawn-requested");
		update_mask |= 0x2;
	}
	if (stream->read_bool("shield-traits-exist"))
	{
		state_data->player_traits.vitality.decode(stream);
		update_mask |= 0x4;
	}
	if (stream->read_bool("extended-traits-exist"))
	{
		state_data->player_traits.extended.decode(stream);
		update_mask |= 0x100000;
	}
	if (stream->read_bool("weapon-traits-exist"))
	{
		state_data->player_traits.weapons.decode(stream);
		update_mask |= 0x8;
	}
	if (stream->read_bool("movement-traits-exist"))
	{
		state_data->player_traits.movement.decode(stream);
		update_mask |= 0x10;
	}
	if (stream->read_bool("appearance-traits-exist"))
	{
		state_data->player_traits.appearance.decode(stream);
		update_mask |= 0x20;
	}
	if (stream->read_bool("snesor-traits-exist"))
	{
		state_data->player_traits.sensors.decode(stream);
		update_mask |= 0x40;
	}
	if (stream->read_bool("waypoint-action-exists"))
	{
		update_mask |= 0x80;
		state_data->waypoint_action = stream->read_integer("waypoint-action", 3);
	}
	if (stream->read_bool("blocking-telporter-exists"))
	{
		update_mask |= 0x100;
		state_data->blocking_teleporter = stream->read_bool("blocking-teleporter");
	}
	if (stream->read_bool("netdebug-exists"))
	{
		*(unsigned long long *)&state_data->netdebug_data.is_host = 0;
		*(unsigned long long *)&state_data->netdebug_data.rtt_average = 0;
		state_data->netdebug_data.is_host = stream->read_bool("is-host");
		if (state_data->netdebug_data.is_host)
		{
			state_data->netdebug_data.host_estimated_bps = stream->read_integer("host-estimated-bps", 16);
			state_data->netdebug_data.host_transmission_rate = stream->read_integer("host-transmission-rate", 16);
			state_data->netdebug_data.host_transmission_bps = stream->read_integer("host-transmission-bps", 16);
		}
		state_data->netdebug_data.rtt_average = stream->read_integer("client-rtt-msec", 16);
		state_data->netdebug_data.packet_rate_average = stream->read_integer("client-packet-rate", 16);
		state_data->netdebug_data.bandwidth_average = stream->read_integer("client-bandwidth-bps", 16);
		state_data->netdebug_data.packet_loss_average = stream->read_integer("client-packet-loss", 7);
		update_mask |= 0x200;
	}
	if (stream->read_bool("lives-remaining-exists"))
	{
		state_data->lives_remaining = stream->read_integer("lives-remaining", 7) - 1;
		update_mask |= 0x400;
	}
	if (stream->read_bool("last-betrayer-exists"))
	{
		state_data->last_betrayer_player_index = stream->read_integer("last-betrayer", 5) - 1;
		update_mask |= 0x800;
	}
	if (stream->read_bool("last-killer-exists"))
	{
		state_data->revenge_last_killer_player_index = stream->read_integer("last-killer-player-index", 5) - 1;
		damage_reporting_info_decode(stream, &state_data->revenge_damage_report);
		update_mask |= 0x80000;
	}
	if (stream->read_bool("vehicle-entrance-ban-exists"))
	{
		update_mask |= 0x1000;
		state_data->vehicle_entrance_ban = stream->read_bool("vehicle-entrance-ban");
	}
	if (stream->read_bool("active-exists"))
	{
		update_mask |= 0x2000;
		state_data->active_in_game = stream->read_bool("active");
	}
	if (stream->read_bool("sitting-out-exists"))
	{
		update_mask |= 0x4000;
		state_data->sitting_out = stream->read_bool("sitting-out");
	}
	if (stream->read_bool("desired-respawn-player-exists"))
	{
		long desired_respawn_player_index = stream->read_integer("desired-respawn-player", 16);
		state_data->desired_respawn_player_index = desired_respawn_player_index - 1;
		if (desired_respawn_player_index)
			state_data->desired_respawn_player_index = player_try_and_get_player_index_from_absolute_player_index((short)(desired_respawn_player_index - 1));
		update_mask |= 0x8000;
	}
	if (stream->read_bool("player-control-aiming-exists"))
	{
		stream->read_unit_vector("player-control-aiming", &state_data->player_control_aiming, 19);
		update_mask |= 0x10000;
	}
	if (stream->read_bool("player-character-type-exists"))
	{
		state_data->player_character_type_index = stream->read_integer("player-character-type", 7) - 1;
		update_mask |= 0x20000;
	}
	*out_update_mask = update_mask;
	return update_mask != 0;
}

bool __fastcall c_simulation_game_engine_player_entity_definition__entity_update_encode_hook(void *thisptr, void *__formal, unsigned long a1, unsigned long long *update_mask, unsigned long long *out_update_mask, long state_data_size, s_simulation_game_engine_player_state_data *data, __int32 a6, c_bitstream *bitstream, long parent_component_count, bool a9) // 0x107ADDC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_simulation_game_engine_player_entity_definition__entity_update_encode_hook@@YI_NPAX0KPA_K1JPAUs_simulation_game_engine_player_state_data@@HPAVc_bitstream@@J_N@Z");
	// `anonymous-namespace'::c_simulation_game_engine_player_entity_definition__entity_update_encode_hook
	// __int32 a6;
	// c_bitstream *bitstream;
	// long parent_component_count;
	// bool a9;
	// c_entity_update_encode_helper encode_helper;
	// void (*const damage_reporting_info_encode)(c_bitstream *, s_damage_reporting_info *);
		// long desired_respawn_player_index;
	// function call : void (*const)(c_bitstream *, s_damage_reporting_info *)

	void (*const damage_reporting_info_encode)(c_bitstream *, s_damage_reporting_info *) = reinterpret_cast<void (*)(c_bitstream *, s_damage_reporting_info *)>(0xB7FE90);
	c_entity_update_encode_helper encode_helper;
	memset(&encode_helper, 0, sizeof(encode_helper));
	if (!encode_helper.start_encoding_update(bitstream, parent_component_count, 0, 21, update_mask))
		return false;
	if (encode_helper.start_component(0, "respawn-exists"))
	{
		bitstream->write_bool("initial-spawn", data->initial_spawn);
		bitstream->write_integer("respawn-timer", data->respawn_timer, 10);
	}
	encode_helper.finish_component();
	if (encode_helper.start_component(1, "early-respawn-requested-exists"))
		bitstream->write_bool("early-respawn-requested", data->early_respawn_requested);
	encode_helper.finish_component();
	if (encode_helper.start_component(2, "shield-traits-exist"))
		data->player_traits.vitality.encode(bitstream);
	encode_helper.finish_component();
	if (encode_helper.start_component(20, "extended-traits-exist"))
		data->player_traits.extended.encode(bitstream);
	encode_helper.finish_component();
	if (encode_helper.start_component(3, "weapon-traits-exist"))
		data->player_traits.weapons.encode(bitstream);
	encode_helper.finish_component();
	if (encode_helper.start_component(4, "movement-traits-exist"))
		data->player_traits.movement.encode(bitstream);
	encode_helper.finish_component();
	if (encode_helper.start_component(5, "appearance-traits-exist"))
		data->player_traits.appearance.encode(bitstream);
	encode_helper.finish_component();
	if (encode_helper.start_component(6, "sensor-traits-exist"))
		data->player_traits.sensors.encode(bitstream);
	encode_helper.finish_component();
	if (encode_helper.start_component(7, "waypoint-action-exists"))
		bitstream->write_integer("waypoint-action", (unsigned char)data->waypoint_action, 3);
	encode_helper.finish_component();
	if (encode_helper.start_component(8, "blocking-teleporter-exists"))
		bitstream->write_bool("blocking-teleporter", data->blocking_teleporter);
	encode_helper.finish_component();
	if (encode_helper.start_component(9, "netdebug-exists"))
	{
		bitstream->write_bool("is-host", data->netdebug_data.is_host);
		if (data->netdebug_data.is_host)
		{
			bitstream->write_integer("host-estimated-bps", (unsigned short)data->netdebug_data.host_estimated_bps, 16);
			bitstream->write_integer("host-transmission-rate", (unsigned short)data->netdebug_data.host_transmission_rate, 16);
			bitstream->write_integer("host-transmission-bps", (unsigned short)data->netdebug_data.host_transmission_bps, 16);
		}
		bitstream->write_integer("client-rtt-msec", (unsigned short)data->netdebug_data.rtt_average, 16);
		bitstream->write_integer("client-packet-rate", (unsigned short)data->netdebug_data.packet_rate_average, 16);
		bitstream->write_integer("client-bandiwdth-bps", (unsigned short)data->netdebug_data.bandwidth_average, 16);
		bitstream->write_integer("client-packet-loss", (unsigned short)data->netdebug_data.packet_loss_average, 7);
	}
	encode_helper.finish_component();
	if (encode_helper.start_component(10, "lives-remaining-exists"))
		bitstream->write_integer("lives-remaining", data->lives_remaining + 1, 7);
	encode_helper.finish_component();
	if (encode_helper.start_component(11, "last-betrayer-exists"))
		bitstream->write_integer("last-betrayer", data->last_betrayer_player_index + 1, 5);
	encode_helper.finish_component();
	if (encode_helper.start_component(19, "last-killer-exists"))
	{
		bitstream->write_integer("last-killer-player-index", data->revenge_last_killer_player_index + 1, 5);
		damage_reporting_info_encode(bitstream, &data->revenge_damage_report);
	}
	encode_helper.finish_component();
	if (encode_helper.start_component(12, "vehicle-entrance-ban-exists"))
		bitstream->write_bool("vehicle-entrance-ban", data->vehicle_entrance_ban);
	encode_helper.finish_component();
	if (encode_helper.start_component(13, "active-in-game-exists"))
		bitstream->write_bool("active-in-game", data->active_in_game);
	encode_helper.finish_component();
	if (encode_helper.start_component(14, "sitting-out-exists"))
		bitstream->write_bool("sitting-out", data->sitting_out);
	encode_helper.finish_component();
	if (encode_helper.start_component(15, "desired-respawn-player-exists"))
	{
		long desired_respawn_player_index = (unsigned short)data->desired_respawn_player_index;
		if ((unsigned short)desired_respawn_player_index == 0xFFFF)
			desired_respawn_player_index = -1;
		bitstream->write_integer("desired-respawn-player", desired_respawn_player_index + 1, 16);
	}
	encode_helper.finish_component();
	if (encode_helper.start_component(16, "player-control-aiming-exists"))
		bitstream->write_unit_vector("player-control-aiming", &data->player_control_aiming, 19);
	encode_helper.finish_component();
	if (encode_helper.start_component(17, "player-character-type-exists"))
		bitstream->write_integer("player-character-type", data->player_character_type_index + 1, 7);
	encode_helper.finish_component();
	encode_helper.finish_encoding_update(out_update_mask);
	return true;
}

void __fastcall c_game_engine__build_player_baseline_hook(void *thisptr, void *__formal, short absolute_player_index, long state_data_size, s_simulation_game_engine_player_state_data *state_data) // 0x107AC100
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_game_engine__build_player_baseline_hook@@YIXPAX0FJPAUs_simulation_game_engine_player_state_data@@@Z");
	// `anonymous-namespace'::c_game_engine__build_player_baseline_hook
	// s_simulation_game_engine_player_state_data *state_data;

	memset(state_data, 0, sizeof(s_simulation_game_engine_player_state_data));
	state_data->initial_spawn = true;
	state_data->player_traits.initialize();
	state_data->last_betrayer_player_index = -1;
	state_data->desired_respawn_player_index = -1;
	state_data->player_control_aiming = global_forward3d;
	state_data->revenge_last_killer_player_index = -1;
	state_data->player_character_type_index = -1;
}

void game_engine_update_player_spawn_timer_hook(long player_index) // 0x107AFDE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_update_player_spawn_timer_hook@@YAXJ@Z");
	// `anonymous-namespace'::game_engine_update_player_spawn_timer_hook
	// static ...; // 0x107B0097
	// static ...; // 0x107B008C
	// static ...; // 0x107B0074
	// static ...; // 0x107B006C
	// long player_index;
	// s_player_datum *player;
	// unsigned long roundTimer;
		// s_game_engine_event_data event_data;
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : bool (*const)(long)
	// function call : void (*const)(long, long)
	// function call : long (*const)(long)
	// function call : long (*const)(long)
	// function call : long (*const)()
	// function call : long (*const)(long)
	// function call : long (*const)(long)
	// function call : long (*const)(long)
	// function call : void (*const)(e_game_engine_event_type, unsigned long, s_game_engine_event_data *)
	// function call : void (*const)(s_game_engine_event_data *)
	// function call : void (*const)(e_game_engine_event_type, unsigned long, s_game_engine_event_data *)
	// function call : void (*const)(s_game_engine_event_data *)
	// function call : void (*const)(long, long)

	unsigned long roundTimer = Utils::Singleton<Modules::ModuleServer>::Instance().VarServerCountdownClient->ValueInt;
	if (!((bool (*)())0x5319C0)())
		return;
	if (!((bool (*)())0x550F90)())
		return;
	if (!((bool (*)(long))0x552090)(player_index))
		return;
	s_player_datum *player = player_get(player_index);
	if (player->respawn_timer <= 0)
	{
		((void (*)(long, long))0x552100)(player_index, 0);
		return;
	}
	if (((long (*)())0x5523D0)() - game_seconds_integer_to_ticks(roundTimer + 4) >= game_seconds_integer_to_ticks(3) || roundTimer)
	{
		if (player->respawn_timer == game_seconds_integer_to_ticks(3) || player->respawn_timer == game_seconds_integer_to_ticks(2) || player->respawn_timer == game_seconds_integer_to_ticks(1))
		{
			s_game_engine_event_data event_data;
			((void (*)(long, long, s_game_engine_event_data *))0x5CEA30)(0, 0x4004E, &event_data);
			event_data.cause_player_index = event_data.effect_player_index = player_index;
			((void (*)(s_game_engine_event_data *))0x5CEAF0)(&event_data);
		}
		else if (player->respawn_timer == 1)
		{
			s_game_engine_event_data event_data;
			((void (*)(long, long, s_game_engine_event_data *))0x5CEA30)(0, 0x4004F, &event_data);
			event_data.cause_player_index = event_data.effect_player_index = player_index;
			((void (*)(s_game_engine_event_data *))0x5CEAF0)(&event_data);
		}
	}
	((void (*)(long, long))0x552100)(player_index, player->respawn_timer - 1);
}

void game_engine_reset_stats_for_round_switch_hook() // 0x107AFC00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_reset_stats_for_round_switch_hook@@YAXXZ");
	// `anonymous-namespace'::game_engine_reset_stats_for_round_switch_hook
	// procedure flags: nofpo
	// void (*const game_engine_reset_stats_for_round_switch)();
	// bool (*const game_results_get_game_recording)();
	// void (*const game_results_set_recording_pause)(bool);
	// function call : bool (*const)()
	// function call : void (*const)(bool)
	// function call : void (*const)()

	void (*const sub_5522B0)() = (void(*const)())0x5522b0;
	bool (*const sub_56E590)() = (bool(*const)())0x56e590;
	void (*const sub_570220)(int) = (void(*const)(int))0x570220;

	if (sub_56E590())
	{
		sub_570220(0);
	}

	sub_5522B0();
}

bool game_engine_player_is_out_of_lives_hook(long player_index) // 0x107AFAB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_player_is_out_of_lives_hook@@YA_NJ@Z");
	// `anonymous-namespace'::game_engine_player_is_out_of_lives_hook
	// long player_index;
	// bool (*const game_engine_player_is_out_of_lives)(long);
	// function call : bool (*const)()
	// function call : bool (*const)(long)

	bool (__cdecl *const game_engine_player_is_out_of_lives)(long) = (bool(__cdecl *const)(long))0x552020;

	if (((bool(__cdecl *)())0x531b20)())
		return false;

	return game_engine_player_is_out_of_lives(player_index);
}

bool game_engine_team_is_out_of_lives_hook(long teamIndex) // 0x107AFCA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_team_is_out_of_lives_hook@@YA_NJ@Z");
	// `anonymous-namespace'::game_engine_team_is_out_of_lives_hook
	// long teamIndex;
	// bool (*const game_engine_team_is_out_of_lives)(long);
	// function call : bool (*const)()
	// function call : bool (*const)(long)

	const auto game_engine_team_is_out_of_lives = (bool(*)(long))0x556A10;

	if (((bool(*)())0x531B20)())
	{
		return false;
	}

	return game_engine_team_is_out_of_lives(teamIndex);
}

void game_engine_add_starting_equipment_hook(long unit_index) // 0x107AE860
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_add_starting_equipment_hook@@YAXJ@Z");
	// `anonymous-namespace'::game_engine_add_starting_equipment_hook
	// static ...; // 0x107AEA9C
	// static ...; // 0x107AEA90
	// static ...; // 0x107AEA88
	// long unit_index;
	// s_unit_data *unit;
	// s_player_datum *player;
	// unsigned long long flags;
	// void (*const game_engine_add_starting_weapon_to_player)(long, long, long);
	// long secondary_weapon_definition_index;
	// long primary_weapon_definition_index;
	// long grenade_count;
	// long (*const get_weapon_definition_index)(short, long);
	// s_scenario *scenario;
		// long i;
	// function call : long (*const)(short, long)
	// function call : long (*const)(short, long)
	// function call : void (*const)(long, long, long)
	// function call : void (*const)(long, long, long)
	// function call : void (*const)(long, unsigned long long *)

	long (*const get_weapon_definition_index)(short, long) = reinterpret_cast<long (*)(short, long)>(0x5CECD0);
	void (*const game_engine_add_starting_weapon_to_player)(long, long, long) = reinterpret_cast<void (*)(long, long, long)>(0x5CE210);
	s_unit_data *unit = object_get<s_unit_data>(unit_index);
	s_player_datum *player = player_get(unit->player_index);
	long primary_weapon_definition_index = get_weapon_definition_index(player->traits.weapons.initial_primary_weapon, 0);
	long secondary_weapon_definition_index = get_weapon_definition_index(player->traits.weapons.initial_secondary_weapon, 1);
	game_engine_add_starting_weapon_to_player(unit_index, primary_weapon_definition_index, 1);
	game_engine_add_starting_weapon_to_player(unit_index, secondary_weapon_definition_index, 1);
	s_scenario *scenario = global_scenario_get();
	long grenade_count = player->traits.weapons.initial_grenade_count;
	for (long i = 0; i < 4; i++)
	{
		if (grenade_count == 2 || !scenario->player_starting_profile.count)
			unit->grenade_counts[i] = 0;
		else
			unit->grenade_counts[i] = scenario->player_starting_profile->starting_grenades[i];
	}
	for (long i = 0; i < 4; i++)
	{
		if (unit->grenade_counts[i] > 0)
		{
			unit->current_grenade_index = (char)i;
			unit->desired_grenade_index = (char)i;
			break;
		}
	}
	unsigned long long flags = 0x4000000;
	((void (*)(long, unsigned long long *))0x4B3010)(unit_index, &flags);
}

static void multiplayer_object_submit_boundary_hook(s_multiplayer_object_boundary_geometry_data *zoneShape, real_argb_color *color, long object_index) // 0x107B0620
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?multiplayer_object_submit_boundary_hook@@YAXPAUs_multiplayer_object_boundary_geometry_data@@PAUreal_argb_color@@J@Z");
	// `anonymous-namespace'::multiplayer_object_submit_boundary_hook
	// long object_index;
	// void (*const multiplayer_object_submit_boundary)(s_multiplayer_object_boundary_geometry_data *, real_argb_color *, long);
	// double l;
	// function call : void (*const)(s_multiplayer_object_boundary_geometry_data *, real_argb_color *, long)

	void (*const multiplayer_object_submit_boundary)(s_multiplayer_object_boundary_geometry_data *, real_argb_color *, long) = reinterpret_cast<void (*)(s_multiplayer_object_boundary_geometry_data *, real_argb_color *, long)>(0xBA0FC0);
	double l = 0.2126f * color->red + color->green * 0.7152 + color->blue * 0.0722;
	if (l < 0.0)
	{
		color->alpha = 1.0f;
		color->red = 1.0f;
		color->green = 1.0f;
		color->blue = 1.0f;
	}
	else if (l < 0.1f)
	{
		color->red += 0.1f;
		color->green += 0.1f;
		color->blue += 0.1f;
	}
	multiplayer_object_submit_boundary(zoneShape, color, object_index);
}

long game_engine_weapon_item_definition_index_from_absolute_weapons_selection_block_index_hook(short selection_index, long weapon_set) // 0x107B0160
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_weapon_item_definition_index_from_absolute_weapons_selection_block_index_hook@@YAJFJ@Z");
	// `anonymous-namespace'::game_engine_weapon_item_definition_index_from_absolute_weapons_selection_block_index_hook
	// long weapon_set;
	// long (*const game_engine_weapon_item_definition_index_from_absolute_weapons_selection_block_index)(short, long);
	// s_multiplayer_globals_definition *multiplayer_globals;
	// s_game_globals *globals;
		// long start_profile_weapon_definition_index;
		// s_scenario *scenario;
			// long j;
	// function call : void *(*const)(unsigned long, long)

	long (*const game_engine_weapon_item_definition_index_from_absolute_weapons_selection_block_index)(short, long) = reinterpret_cast<long (*)(short, long)>(0x5CECD0);
	s_game_globals *globals = game_globals_get();
	if (!globals)
		return -1;
	if (globals->MultiplayerGlobals.index == -1)
		return -1;
	s_multiplayer_globals_definition *multiplayer_globals = (s_multiplayer_globals_definition *)tag_get('mulg', globals->MultiplayerGlobals.index);
	if (!multiplayer_globals || !multiplayer_globals->universal.count)
		return -1;
	if (selection_index == -3)
	{
		selection_index = (short)compute_weighted_random_index(&multiplayer_globals->universal->weapons[0], multiplayer_globals->universal->weapons.count, [](s_multiplayer_weapon const &weapon) { return weapon.random_chance; });
	}
	else if (selection_index == -1)
	{
		s_scenario *scenario = global_scenario_get();
		if (!scenario->player_starting_profile.count)
			return -1;
		long start_profile_weapon_definition_index = scenario->player_starting_profile->starting_weapons[weapon_set].weapon.index;
		if (!multiplayer_globals->universal->weapons.count)
			return -1;
		for (long j = 0; j < multiplayer_globals->universal->weapons.count; j++)
		{
			if (multiplayer_globals->universal->weapons[j].object.index == start_profile_weapon_definition_index)
			{
				selection_index = (short)j;
				break;
			}
		}
	}
	if (selection_index >= 0 && selection_index < multiplayer_globals->universal->weapons.count)
		return multiplayer_globals->universal->weapons[selection_index].object.index;
	return -1;
}

bool game_engine_object_is_dead(long object_index) // 0x107AFA30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_object_is_dead@@YA_NJ@Z");
	// `anonymous-namespace'::game_engine_object_is_dead
	// long object_index;

	return (object_get(object_index)->damage_flags & 0x4) != 0;
}

bool game_engine_object_has_been_abandoned_hook(long object_index) // 0x107AF6F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_object_has_been_abandoned_hook@@YA_NJ@Z");
	// `anonymous-namespace'::game_engine_object_has_been_abandoned_hook
	// static ...; // 0x107AF97C
	// static ...; // 0x107AF968
// $LN18:
// $LN15:
// $LN12:
// $LN9:
// $LN6:
	// long object_index;
	// bool (*const game_engine_is_object_being_edited)(long, long *);
	// bool (*const object_is_at_rest)(long);
	// s_object_data *object;
	// bool (*const object_is_hidden)(long);
	// bool (*const game_engine_player_is_nearby)(real_point3d const *, float);
	// bool is_hidden;
	// bool abandoned;
	// bool (*const game_engine_unit_has_passengers)(long);
	// bool is_at_rest;
	// bool is_dead;
	// bool (*const game_engine_any_player_nearby_and_looking_at_sphere)(real_point3d const *, float, float);
	// bool player_prevented;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : bool (*const)(long)
	// function call : bool (*const)(long)
	// function call : bool (*const)(real_point3d const *, float)
	// function call : bool (*const)(real_point3d const *, float, float)
	// function call : bool (*const)(long)
	// function call : bool (*const)(long, long *)

	bool (*const object_is_hidden)(long) = reinterpret_cast<bool (*)(long)>(0xB2F1D0);
	bool (*const object_is_at_rest)(long) = reinterpret_cast<bool (*)(long)>(0xB2F120);
	bool (*const game_engine_player_is_nearby)(real_point3d const *, float) = reinterpret_cast<bool (*)(real_point3d const *, float)>(0x58FEE0);
	bool (*const game_engine_any_player_nearby_and_looking_at_sphere)(real_point3d const *, float, float) = reinterpret_cast<bool (*)(real_point3d const *, float, float)>(0x58F860);
	bool (*const game_engine_unit_has_passengers)(long) = reinterpret_cast<bool (*)(long)>(0x5901C0);
	bool (*const game_engine_is_object_being_edited)(long, long *) = reinterpret_cast<bool (*)(long, long *)>(0x59A6A0);
	s_object_data *object = object_try_and_get_and_verify_type(object_index, -1);
	if (!object)
		return false;
	if (object->parent_object_index != -1)
		return false;
	bool is_dead = game_engine_object_is_dead(object_index);
	bool is_hidden = object_is_hidden(object_index);
	bool is_at_rest = object_is_at_rest(object_index);
	bool player_prevented = game_engine_player_is_nearby(&object->bounding_sphere_center, 3.0f) || game_engine_any_player_nearby_and_looking_at_sphere(&object->bounding_sphere_center, object->bounding_sphere_radius, 8.0f);
	bool abandoned = false;
	switch (object_get_type(object_index))
	{
	case _object_type_biped:
		if (is_dead || reinterpret_cast<s_unit_data *>(object)->player_index == -1)
			abandoned = true;
		break;
	case _object_type_vehicle:
	case _object_type_giant:
		if (is_at_rest && !game_engine_unit_has_passengers(object_index) && !player_prevented)
			abandoned = true;
		break;
	case _object_type_weapon:
	case _object_type_equipment:
		if (!is_hidden && !player_prevented)
			abandoned = true;
		break;
	case _object_type_scenery:
	case _object_type_creature:
		if (!player_prevented)
			abandoned = true;
		break;
	}
	return abandoned && !game_engine_is_object_being_edited(object_index, nullptr);
}

long candy_spawner_object_new_hook(s_object_placement_data *placement_data) // 0x107AE540
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?candy_spawner_object_new_hook@@YAJPAUs_object_placement_data@@@Z");
	// `anonymous-namespace'::candy_spawner_object_new_hook
	// s_object_placement_data *placement_data;
	// long (*const object_new)(s_object_placement_data *);
	// s_scenario_object *(*const scenario_object_get)(s_scenario const *, long, long);
	// long object_index;
	// void (*const object_type_place)(long, s_scenario_object const *);
	// s_scenario_object const *scenario_object;
	// s_scenario const *scenario;
		// s_object_definition *object_definition;
		// s_object_data *object;
	// function call : void *(*const)(unsigned long, long)
	// function call : s_scenario_object *(*const)(s_scenario const *, long, long)
	// function call : long (*const)(s_object_placement_data *)
	// function call : void (*const)(long, s_scenario_object const *)

	long (*const object_new)(s_object_placement_data *) = reinterpret_cast<long (*)(s_object_placement_data *)>(0xB30440);
	s_scenario_object *(*const scenario_object_get)(s_scenario const *, long, long) = reinterpret_cast<s_scenario_object *(*)(s_scenario const *, long, long)>(0xB5A9E0);
	void (*const object_type_place)(long, s_scenario_object const *) = reinterpret_cast<void (*)(long, s_scenario_object const *)>(0xB73DC0);
	s_scenario const *scenario = global_scenario_get();
	s_scenario_object const *scenario_object = nullptr;
	if (placement_data->scenario_datum_index != -1)
	{
		s_object_definition *object_definition = (s_object_definition *)tag_get('obje', placement_data->definition_index);
		scenario_object = scenario_object_get(scenario, (short)object_definition->object_type, placement_data->scenario_datum_index);
		if ((short)scenario_object->name != -1 && tls_getd().object_name_list[(short)scenario_object->name] != -1)
			return -1;
	}
	long object_index = object_new(placement_data);
	if (object_index != -1 && scenario_object)
	{
		if ((short)scenario_object->name != -1)
		{
			s_object_data *object = object_get(object_index);
			tls_getd().object_name_list[(short)scenario_object->name] = object_index;
			object->name_index = (short)scenario_object->name;
		}
		object_type_place(object_index, scenario_object);
	}
	return object_index;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Modules::ModuleVoIP & Utils::Singleton<Modules::ModuleVoIP>::Instance();
template bool c_tag_block<s_game_engine_status_response>::try_get_element(__int32, s_game_engine_status_response **) const;
template bool c_tag_block<s_multiplayer_runtime_globals_definition>::try_get_element(__int32, s_multiplayer_runtime_globals_definition **) const;
template bool c_tag_block<s_scenario_profile>::try_get_element(__int32, s_scenario_profile **) const;
template bool s_static_array<unsigned char,4>::valid(__int32);
template c_enum<enum e_damage_reporting_type,short> & c_enum<enum e_damage_reporting_type,short>::operator=(c_enum<enum e_damage_reporting_type,short> const &);
template c_enum<enum e_game_engine_event_type,char>::c_enum();
template c_enum<enum e_object_type,short>::operator short() const;
template s_game_engine_status_response & c_tag_block<s_game_engine_status_response>::operator[](__int32);
template s_game_engine_status_response * c_tag_block<s_game_engine_status_response>::get_element(__int32) const;
template s_multiplayer_runtime_globals_definition * c_tag_block<s_multiplayer_runtime_globals_definition>::get_element(__int32) const;
template s_multiplayer_runtime_globals_definition * c_tag_block<s_multiplayer_runtime_globals_definition>::operator->();
template s_scenario_profile * c_tag_block<s_scenario_profile>::get_element(__int32) const;
template s_scenario_profile * c_tag_block<s_scenario_profile>::operator->();
template unsigned char & s_static_array<unsigned char,4>::operator[](long);
template void Pointer::Write<enum e_simulation_game_engine_player_components>(e_simulation_game_engine_player_components const) const;
