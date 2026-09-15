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
void multiplayer_object_submit_boundary_hook(s_multiplayer_object_boundary_geometry_data *zoneShape, real_argb_color *color, long object_index);
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
_inline s_game_engine_event_data::s_game_engine_event_data() = default; // 0x107A91F0

// mangled_x86(MANGLED_DEFAULT, "??1Patch@@QAE@XZ"); no body to assert in
_inline Patch::~Patch() = default; // 0x107A9240

// mangled_x86(MANGLED_DEFAULT, "??4s_damage_reporting_info@@QAEAAU0@ABU0@@Z"); no body to assert in
_inline s_damage_reporting_info &s_damage_reporting_info::operator=(s_damage_reporting_info const &__that) = default; // 0x107A92D0

namespace Patches
{
	namespace GameEngine
	{
		_extern void _sub_107A96D0();
		void ApplyAll() // 0x107A96D0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@GameEngine@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_107A96D0();
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

_extern __int32 _sub_107AEC40();
__int32 game_engine_get_delta_ticks_hook() // 0x107AEC40
{
	// `anonymous-namespace'::game_engine_get_delta_ticks_hook
	// procedure flags: nofpo
	// long delta;
	// long round_start_time;
	// function call : long (*const)()
	todo("implement");
	__int32 __result = _sub_107AEC40();
	return __result;
}

_extern __int32 _sub_107AECE0(__int32);
__int32 game_engine_get_player_state_hook(__int32 player_index) // 0x107AECE0
{
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
	todo("implement");
	__int32 __result = _sub_107AECE0(player_index);
	return __result;
}

_extern bool _sub_107AF1D0(__int32, wchar_t *, __int32, bool);
bool game_engine_hud_get_state_message_hook(__int32 hudIndex, wchar_t *buff, __int32 len, bool a4) // 0x107AF1D0
{
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
	{
		// e_game_engine_status state;
		// s_local_game_engine_globals::s_player_state &local_player_state;
		{
			// s_game_engine_status_response const &state_response;
			// s_multiplayer_globals_definition *const mulg;
			// bool should_display;
			// unsigned long message;
			{
				// long local_state;
			}
			{
				// wchar_t format[256];
			}
		}
	}
	{
		// wchar_t format[256];
	}
	{
	}
	{
	}
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
	todo("implement");
	bool __result = _sub_107AF1D0(hudIndex, buff, len, a4);
	return __result;
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

_extern bool _sub_107AC1D0(c_game_engine *, void *, long, long, long, bool, s_chud_navpoint *);
bool __fastcall c_game_engine__build_player_navpoint_hook(c_game_engine *thisptr, void *__formal, long output_user_index, long player_index, long unknown_player_index, bool a5, s_chud_navpoint *navpoint) // 0x107AC1D0
{
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
	{
		// long unit_index;
	}
	{
		// Blam::Network::Session *session;
		{
			// __int32 player_index;
		}
	}
	{
		// s_unit_data *dead_unit;
		// long dead_unit_index;
	}
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(c_game_engine *, long, long)
	// function call : unsigned long (*const)(bool, long, long)
	// function call : wchar_t *(*const)(wchar_t *, wchar_t *, __int32)
	// function call : void (*const)(long, real_point3d *)
	// function call : long (*const)(long)
	// function call : long (*const)()
	// function call : void (*const)(long, real_point3d *)
	todo("implement");
	bool __result = _sub_107AC1D0(thisptr, __formal, output_user_index, player_index, unknown_player_index, a5, navpoint);
	return __result;
}

_extern void _sub_107AC990(void *, void *, short, unsigned long long *, long, s_simulation_game_engine_player_state_data *);
void __fastcall c_game_engine__build_player_update_hook(void *thisptr, void *__formal, short absolute_player_index, unsigned long long *in_out_flags, long state_data_size, s_simulation_game_engine_player_state_data *data) // 0x107AC990
{
	// `anonymous-namespace'::c_game_engine__build_player_update_hook
	// s_simulation_game_engine_player_state_data *data;
	// s_player_datum *player;
	// unsigned long long updated_flags;
	// bool (*const simulation_update_player_netdebug_data)(long, s_simulation_player_netdebug_data *);
	// tls_data *tls;
	{
		// char waypoint_action;
	}
	{
		// bool blocking_teleporter;
	}
	{
		// long last_betrayer_player_index;
	}
	{
		// long revenge_player_index;
	}
	// function call : void *(*const)(s_data_array const *, unsigned long)
	todo("implement");
	_sub_107AC990(thisptr, __formal, absolute_player_index, in_out_flags, state_data_size, data);
}

_extern bool _sub_107AB520(void *, void *, short, unsigned long long *, long, s_simulation_game_engine_player_state_data *);
bool __fastcall c_game_engine__apply_player_update_hook(void *thisptr, void *__formal, short absolute_player_index, unsigned long long *component_mask, long state_data_size, s_simulation_game_engine_player_state_data *data) // 0x107AB520
{
	// `anonymous-namespace'::c_game_engine__apply_player_update_hook
	// s_simulation_game_engine_player_state_data *data;
	// s_player_datum *player;
	// long (*const game_engine_sandbox_get_player_chief_biped_unit_index)(long);
	// tls_data *tls;
	// void (*const unit_set_aiming_vectors)(long, real_vector3d *, real_vector3d *);
	// void (*const player_control_set_facing)(long, real_vector3d *);
	{
		// long respawn_timer_ticks;
	}
	{
		// long game_grief_player_index;
	}
	{
		// long revenge_player_index;
	}
	{
		// long player_index;
		// long unit_index;
		// long input_user_index;
	}
	{
	}
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
	todo("implement");
	bool __result = _sub_107AB520(thisptr, __formal, absolute_player_index, component_mask, state_data_size, data);
	return __result;
}

_extern bool _sub_107AD5E0(void *, void *, bool, unsigned long long *, long, s_simulation_game_engine_player_state_data *, c_bitstream *, bool);
bool __fastcall c_simulation_game_engine_player_entity_definition__entity_update_decode_hook(void *thisptr, void *__formal, bool a1, unsigned long long *out_update_mask, long state_data_size, s_simulation_game_engine_player_state_data *state_data, c_bitstream *stream, bool a6) // 0x107AD5E0
{
	// `anonymous-namespace'::c_simulation_game_engine_player_entity_definition__entity_update_decode_hook
	// bool a6;
	// unsigned long long update_mask;
	// long (*const player_try_and_get_player_index_from_absolute_player_index)(long);
	// void (*const damage_reporting_info_decode)(c_bitstream *, s_damage_reporting_info *);
	{
		// long desired_respawn_player_index;
	}
	// function call : void (*const)(c_bitstream *, s_damage_reporting_info *)
	// function call : long (*const)(long)
	todo("implement");
	bool __result = _sub_107AD5E0(thisptr, __formal, a1, out_update_mask, state_data_size, state_data, stream, a6);
	return __result;
}

_extern bool _sub_107ADDC0(void *, void *, unsigned long, unsigned long long *, unsigned long long *, long, s_simulation_game_engine_player_state_data *, __int32, c_bitstream *, long, bool);
bool __fastcall c_simulation_game_engine_player_entity_definition__entity_update_encode_hook(void *thisptr, void *__formal, unsigned long a1, unsigned long long *update_mask, unsigned long long *out_update_mask, long state_data_size, s_simulation_game_engine_player_state_data *data, __int32 a6, c_bitstream *bitstream, long parent_component_count, bool a9) // 0x107ADDC0
{
	// `anonymous-namespace'::c_simulation_game_engine_player_entity_definition__entity_update_encode_hook
	// __int32 a6;
	// c_bitstream *bitstream;
	// long parent_component_count;
	// bool a9;
	// c_entity_update_encode_helper encode_helper;
	// void (*const damage_reporting_info_encode)(c_bitstream *, s_damage_reporting_info *);
	{
		// long desired_respawn_player_index;
	}
	// function call : void (*const)(c_bitstream *, s_damage_reporting_info *)
	todo("implement");
	bool __result = _sub_107ADDC0(thisptr, __formal, a1, update_mask, out_update_mask, state_data_size, data, a6, bitstream, parent_component_count, a9);
	return __result;
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

_extern void _sub_107AFDE0(long);
void game_engine_update_player_spawn_timer_hook(long player_index) // 0x107AFDE0
{
	// `anonymous-namespace'::game_engine_update_player_spawn_timer_hook
	// static ...; // 0x107B0097
	// static ...; // 0x107B008C
	// static ...; // 0x107B0074
	// static ...; // 0x107B006C
	// long player_index;
	// s_player_datum *player;
	// unsigned long roundTimer;
	{
		// s_game_engine_event_data event_data;
	}
	{
	}
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
	todo("implement");
	_sub_107AFDE0(player_index);
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

_extern void _sub_107AE860(long);
void game_engine_add_starting_equipment_hook(long unit_index) // 0x107AE860
{
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
	{
		// long i;
	}
	{
	}
	// function call : long (*const)(short, long)
	// function call : long (*const)(short, long)
	// function call : void (*const)(long, long, long)
	// function call : void (*const)(long, long, long)
	// function call : void (*const)(long, unsigned long long *)
	todo("implement");
	_sub_107AE860(unit_index);
}

_extern void _sub_107B0620(s_multiplayer_object_boundary_geometry_data *, real_argb_color *, long);
void multiplayer_object_submit_boundary_hook(s_multiplayer_object_boundary_geometry_data *zoneShape, real_argb_color *color, long object_index) // 0x107B0620
{
	// `anonymous-namespace'::multiplayer_object_submit_boundary_hook
	// long object_index;
	// void (*const multiplayer_object_submit_boundary)(s_multiplayer_object_boundary_geometry_data *, real_argb_color *, long);
	// double l;
	// function call : void (*const)(s_multiplayer_object_boundary_geometry_data *, real_argb_color *, long)
	todo("implement");
	_sub_107B0620(zoneShape, color, object_index);
}

_extern long _sub_107B0160(short, long);
long game_engine_weapon_item_definition_index_from_absolute_weapons_selection_block_index_hook(short selection_index, long weapon_set) // 0x107B0160
{
	// `anonymous-namespace'::game_engine_weapon_item_definition_index_from_absolute_weapons_selection_block_index_hook
	// long weapon_set;
	// long (*const game_engine_weapon_item_definition_index_from_absolute_weapons_selection_block_index)(short, long);
	// s_multiplayer_globals_definition *multiplayer_globals;
	// s_game_globals *globals;
	{
	}
	{
		// long start_profile_weapon_definition_index;
		// s_scenario *scenario;
		{
			// long j;
		}
	}
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	long __result = _sub_107B0160(selection_index, weapon_set);
	return __result;
}

bool game_engine_object_is_dead(long object_index) // 0x107AFA30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_object_is_dead@@YA_NJ@Z");
	// `anonymous-namespace'::game_engine_object_is_dead
	// long object_index;

	return (object_get(object_index)->damage_flags & 0x4) != 0;
}

_extern bool _sub_107AF6F0(long);
bool game_engine_object_has_been_abandoned_hook(long object_index) // 0x107AF6F0
{
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
	todo("implement");
	bool __result = _sub_107AF6F0(object_index);
	return __result;
}

_extern long _sub_107AE540(s_object_placement_data *);
long candy_spawner_object_new_hook(s_object_placement_data *placement_data) // 0x107AE540
{
	// `anonymous-namespace'::candy_spawner_object_new_hook
	// s_object_placement_data *placement_data;
	// long (*const object_new)(s_object_placement_data *);
	// s_scenario_object *(*const scenario_object_get)(s_scenario const *, long, long);
	// long object_index;
	// void (*const object_type_place)(long, s_scenario_object const *);
	// s_scenario_object const *scenario_object;
	// s_scenario const *scenario;
	{
		// s_object_definition *object_definition;
	}
	{
		// s_object_data *object;
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : s_scenario_object *(*const)(s_scenario const *, long, long)
	// function call : long (*const)(s_object_placement_data *)
	// function call : void (*const)(long, s_scenario_object const *)
	todo("implement");
	long __result = _sub_107AE540(placement_data);
	return __result;
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
