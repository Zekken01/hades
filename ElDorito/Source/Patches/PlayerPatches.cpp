/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/simulation/game_interface/simulation_game_engine_player.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Player/PlayerCustomizationExtension.hpp"
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
struct real_rgb_color;
struct s_damage_owner;
struct s_damage_reporting_info;
struct s_game_globals_player_information;
struct s_multiplayer_object_boundary_geometry_data;
struct s_player_datum;
struct s_simulation_game_engine_player_state_data;
namespace Patches
{
	namespace Network
	{
		class PlayerPropertiesExtender;
		class PlayerPropertiesExtensionBase;
	}
}
namespace Player
{
	class PlayerCustomizationExtensions;
}

namespace Utils {}
using namespace ::Utils;
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
	namespace Sprint {}
	using namespace Patches::Sprint;
	namespace PlayerScale {}
	using namespace Patches::PlayerScale;
	namespace Network {}
	using namespace Patches::Network;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

long unit_get_global_player_information_block_index(long unit_index);  // hades: added for 0x108DC110
s_game_globals *game_globals_get();  // hades: added for 0x108DC110

namespace Blam { class BitStream; }  // hades: added for 0x108D9400
namespace Player { extern bool player_configuration_host_decode(Blam::BitStream *stream, s_player_configuration_from_host *configuration, e_player_configuration_encoding_type encoding_type); }  // hades: added for 0x108D9400
namespace Player { extern void player_configuration_host_encode(Blam::BitStream *stream, s_player_configuration_from_host *configuration, e_player_configuration_encoding_type encoding_type); }  // hades: added for 0x108D9400

namespace Patches { namespace PlayerScale { extern void UpdatePlayerScale(int playerIndex); } }  // hades: added for 0x108DBEB0

namespace Patches { namespace Sprint { extern void UpdatePlayerSprint(long player_index); } }  // hades: added for 0x108DC6A0
namespace Player { namespace PlayerPodium { extern void UpdatePlayer(long player_datum_index); } }  // hades: added for 0x108DC6A0

s_player_datum *player_get(unsigned long player_index);  // hades: added for 0X108DC4C0

namespace Patches
{
	namespace Player
	{
		extern void ApplyAll();
	}
}

bool s3d_player_has_gameplay_modifier(s_player_datum *playerdatum, long index);
long s3d_player_get_gameplay_modifier_int(s_player_datum *playerDatum, long index, long default_value);
float s3d_player_get_gameplay_modifier_real(s_player_datum *playerDatum, long index, float default_value);
bool BeforePlayerSpawn(long playerIndex);
void AfterPlayerSpawn(long playerIndex);
bool player_spawn_hook(long player_index);
void player_reset_hook(long player_index, bool a2, bool a3, void *data);
void player_set_unit_index_hook(long player_index, long unit_index);
bool player_in_multiplayer_object_boundary(long player_index, s_multiplayer_object_boundary_geometry_data const *geometry_data);
void game_engine_player_died_hook(long player_index);
void game_engine_player_update_sub_hook(long player_index, long unit_index);
void __fastcall c_game_engine__build_player_baseline(void *thisptr, void *unused, __int32 a1, __int32 a2, s_simulation_game_engine_player_state_data *state_data);
void player_handle_coop_respawn(long player_index);
void player_update_after_game_hook(long player_index);

/* ---------- globals */

namespace Utils
{
	Patches::Network::PlayerPropertiesExtender *Utils::Singleton<Patches::Network::PlayerPropertiesExtender>::m_instance; // 0x124083A4
}

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Player
	{
		void ApplyAll() // 0x108D9400
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Player@Patches@@YAXXZ");
			// procedure flags: nofpo

			Patch(0x1360E0, { 0xC3 }).Apply();
			Patch(0x136750, { 0xC3 }).Apply();
			Patch(0x136260, { 0xC3 }).Apply();
			Patch(0x1368D0, { 0xC3 }).Apply();
			Hook(0x29CAE0, s3d_player_has_gameplay_modifier).Apply();
			Hook(0x29C160, s3d_player_get_gameplay_modifier_real).Apply();
			Hook(0x29C110, s3d_player_get_gameplay_modifier_int).Apply();
			Hook(0xB4DFA, player_spawn_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x141816, player_spawn_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x143EF8, player_spawn_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x143F3E, player_spawn_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x143FEB, player_spawn_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x13B8B7, player_reset_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x13C030, player_reset_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x141AA1, player_reset_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7A10B0, player_in_multiplayer_object_boundary).Apply();
			Hook(0x1390FA, game_engine_player_died_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x13B6C2, game_engine_player_died_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x436E0, ::Player::player_configuration_host_decode).Apply();
			Hook(0x437C0, ::Player::player_configuration_host_encode).Apply();
			Hook(0x349200, c_game_engine__build_player_baseline).Apply();
			Hook(0x13CC98, player_set_unit_index_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x34A41F, game_engine_player_update_sub_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x143AE8, player_update_after_game_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0x4BAD4E).Write<unsigned char>(0x4);
			Pointer(0x4BAD54).Write<unsigned char>(0x4);
			Pointer(0x4BAD57).Write<unsigned char>(0x4);
			Pointer(0x4BAD64).Write<unsigned char>(0x4);
			Pointer(0x4BAD67).Write<unsigned char>(0x4);
			Pointer(0x4BAD73).Write<unsigned char>(0x4);
			Pointer(0x4BA6E4).Write<unsigned char>(0x4);
			Patches::Network::PlayerPropertiesExtender::Instance().Add(std::make_unique<::Player::PlayerCustomizationExtensions>());
		}
	}
}

namespace Player
{
	// mangled_x86(MANGLED_DEFAULT, "??0PlayerCustomizationExtensions@Player@@QAE@XZ"); no body to assert in
}

namespace Patches
{
	namespace Network
	{
		// mangled_x86(MANGLED_DEFAULT, "??0PlayerPropertiesExtender@Network@Patches@@QAE@XZ"); no body to assert in

		// mangled_x86(MANGLED_DEFAULT, "??0PlayerPropertiesExtensionBase@Network@Patches@@QAE@XZ"); no body to assert in
		// _inline PlayerPropertiesExtensionBase::PlayerPropertiesExtensionBase() = default; // 0x108D8CC0  // hades: defaulted on its declaration
	}
}

namespace Player
{
}

/* ---------- private code */

bool s3d_player_has_gameplay_modifier(s_player_datum *playerdatum, long index) // 0x108DC840
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?s3d_player_has_gameplay_modifier@@YA_NPAUs_player_datum@@J@Z");
	// `anonymous-namespace'::s3d_player_has_gameplay_modifier
	// long index;

	return false;
}

long s3d_player_get_gameplay_modifier_int(s_player_datum *playerDatum, long index, long default_value) // 0x108DC800
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?s3d_player_get_gameplay_modifier_int@@YAJPAUs_player_datum@@JJ@Z");
	// `anonymous-namespace'::s3d_player_get_gameplay_modifier_int
	// long default_value;

	return default_value;
}

float s3d_player_get_gameplay_modifier_real(s_player_datum *playerDatum, long index, float default_value) // 0x108DC820
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?s3d_player_get_gameplay_modifier_real@@YAMPAUs_player_datum@@JM@Z");
	// `anonymous-namespace'::s3d_player_get_gameplay_modifier_real
	// float default_value;

	return default_value;
}

bool BeforePlayerSpawn(long playerIndex) // 0x108DB000
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BeforePlayerSpawn@@YA_NJ@Z");
	// `anonymous-namespace'::BeforePlayerSpawn
	// long playerIndex;

	::Player::CPlayerCharacterSystem::AssignPlayerCharacter(playerIndex);
	return true;
}

void AfterPlayerSpawn(long playerIndex) // 0x108D93E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?AfterPlayerSpawn@@YAXJ@Z");
	// the original is empty
	// `anonymous-namespace'::AfterPlayerSpawn
	// long playerIndex;
}

bool player_spawn_hook(long player_index) // 0x108DC5F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_spawn_hook@@YA_NJ@Z");
	// `anonymous-namespace'::player_spawn_hook
	// long player_index;
	// bool (*const player_spawn)(long, real_point3d *, float *);
	// bool did_spawn;
	// function call : bool (*const)(long, real_point3d *, float *)

	bool (__cdecl *const player_spawn)(long, int, int) = (bool(__cdecl *const)(long, int, int))0x53ce60;

	if (!BeforePlayerSpawn(player_index))
	{
		return false;
	}
	bool did_spawn = player_spawn(player_index, 0, 0);
	if (did_spawn)
	{
		AfterPlayerSpawn(player_index);
	}
	return did_spawn;
}

void player_reset_hook(long player_index, bool a2, bool a3, void *data) // 0x108DC4C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_reset_hook@@YAXJ_N0PAX@Z");
	// `anonymous-namespace'::player_reset_hook
	// void *data;
	// s_player_datum *player;
	// constexpr void (*const `player_reset_hook'::`2'::player_reset)(long, bool, bool, void *); // constant == 5488752
	// function call : void (*const)(long, bool, bool, void *)

	((void(__cdecl *)(long, bool, bool, void *))0x53c070)(player_index, a2, a3, data);
	s_player_datum *player = player_get(player_index);
	player->hsc_forced_character_type_index = -1;
	player->character_type_index = -1;
	player->previous_character_type_index = -1;
}

void player_set_unit_index_hook(long player_index, long unit_index) // 0x108DC570
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_set_unit_index_hook@@YAXJJ@Z");
	// `anonymous-namespace'::player_set_unit_index_hook
	// long unit_index;
	// void (*const player_mapping_set_player_unit)(long, long);
	// function call : void (*const)(long, long)

	void (__cdecl *const player_mapping_set_player_unit)(long, long) = (void(__cdecl *const)(long, long))0x58a2b0;

	player_mapping_set_player_unit(player_index, unit_index);
	::Player::CPlayerCharacterSystem::PlayerCharacterEditor(player_index);
}

bool player_in_multiplayer_object_boundary(long player_index, s_multiplayer_object_boundary_geometry_data const *geometry_data) // 0x108DC300
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_in_multiplayer_object_boundary@@YA_NJPBUs_multiplayer_object_boundary_geometry_data@@@Z");
	// `anonymous-namespace'::player_in_multiplayer_object_boundary
	// static ...; // 0x108DC450
	// static ...; // 0x108DC448
	// long player_index;
	// s_multiplayer_object_boundary_geometry_data const *geometry_data;
	// s_player_datum *player;
	// bool (*const point_in_multiplayer_object_boundary)(real_point3d const *, s_multiplayer_object_boundary_geometry_data const *);
	// bool (*const unit_get_body_position)(long, real_point3d *);
		// real_point3d points[2];
		// long point_count;
			// __int32 i;
	// function call : void (*const)(long, real_point3d *)
	// function call : bool (*const)(long, real_point3d *)
	// function call : bool (*const)(real_point3d const *, s_multiplayer_object_boundary_geometry_data const *)

	bool (*const unit_get_body_position)(long, real_point3d *) = reinterpret_cast<bool (*)(long, real_point3d *)>(0xB43630);
	bool (*const point_in_multiplayer_object_boundary)(real_point3d const *, s_multiplayer_object_boundary_geometry_data const *) = reinterpret_cast<bool (*)(real_point3d const *, s_multiplayer_object_boundary_geometry_data const *)>(0xBA11F0);
	s_player_datum *player = player_get(player_index);
	if (player && player->unit_index != -1)
	{
		real_point3d points[2];
		long point_count = 0;
		((bool (*)(long, real_point3d *))0xB2E5A0)(player->unit_index, &points[point_count++]);
		unit_get_body_position(player->unit_index, &points[point_count++]);
		for (__int32 i = 0; i < point_count; i++)
		{
			if (point_in_multiplayer_object_boundary(&points[i], geometry_data))
				return true;
		}
	}
	return false;
}

void game_engine_player_died_hook(long player_index) // 0x108DBE50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_player_died_hook@@YAXJ@Z");
	// `anonymous-namespace'::game_engine_player_died_hook
	// long player_index;
	// constexpr void (*const `game_engine_player_died_hook'::`2'::game_engine_player_died)(long); // constant == 5481264
	// function call : void (*const)(long)

	((void(*)(long))0x53A330)(player_index);
}

void game_engine_player_update_sub_hook(long player_index, long unit_index) // 0x108DBEB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_player_update_sub_hook@@YAXJJ@Z");
	// `anonymous-namespace'::game_engine_player_update_sub_hook
	// long unit_index;
	// void (*const player_refresh_object_appearance_full)(long, long);
	// function call : void (*const)(long, long)

	void (*const player_refresh_object_appearance_full)(long, long) = reinterpret_cast<void (*)(long, long)>(0x538ED0);
	player_refresh_object_appearance_full(player_index, unit_index);
	Patches::PlayerScale::UpdatePlayerScale(player_index);
}

void __fastcall c_game_engine__build_player_baseline(void *thisptr, void *unused, __int32 a1, __int32 a2, s_simulation_game_engine_player_state_data *state_data) // 0x108DBCE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_game_engine__build_player_baseline@@YIXPAX0HHPAUs_simulation_game_engine_player_state_data@@@Z");
	// `anonymous-namespace'::c_game_engine__build_player_baseline
	// s_simulation_game_engine_player_state_data *state_data;

	memset(state_data, 0, 0x74);
	state_data->initial_spawn = true;
	state_data->last_betrayer_player_index = -1;
	state_data->desired_respawn_player_index = -1;
	state_data->revenge_last_killer_player_index = -1;
	state_data->player_control_aiming = global_forward3d;
	state_data->player_traits.initialize();
	state_data->player_character_type_index = -1;
}

void player_handle_coop_respawn(long player_index) // 0x108DC110
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_handle_coop_respawn@@YAXJ@Z");
	// `anonymous-namespace'::player_handle_coop_respawn
	// static ...; // 0x108DC284
	// static ...; // 0x108DC278
	// static ...; // 0x108DC270
	// long player_index;
	// s_player_datum *player;
	// long (*const effect_new_from_object)(long, s_damage_owner const *, s_damage_reporting_info *, long, float, float, real_rgb_color const *, player_handle_coop_respawn::__l2::effect_vector_field *, long);
		// s_game_globals_player_information *player_info;
		// long info_block_index;
			// s_damage_reporting_info reporting_info;
	// function call : long (*const)(long, s_damage_owner const *, s_damage_reporting_info *, long, float, float, real_rgb_color const *, player_handle_coop_respawn::__l2::effect_vector_field *, long)

	struct effect_vector_field;
	long (*const effect_new_from_object)(long, s_damage_owner const *, s_damage_reporting_info *, long, float, float, real_rgb_color const *, effect_vector_field *, long) = reinterpret_cast<long (*)(long, s_damage_owner const *, s_damage_reporting_info *, long, float, float, real_rgb_color const *, effect_vector_field *, long)>(0x5B8550);
	s_player_datum *player = player_get(player_index);
	if (player->flags & 0x800)
	{
		if (player->unit_index != -1)
		{
			long info_block_index = unit_get_global_player_information_block_index(player->unit_index);
			s_game_globals_player_information *player_info = &game_globals_get()->PlayerInformation[info_block_index];
			if (player_info->coop_respawn_effect.index != -1)
			{
				struct { c_enum<e_damage_reporting_type,short> type; char variant; char modifier; } reporting_info = {};
				effect_new_from_object(player_info->coop_respawn_effect.index, nullptr, (s_damage_reporting_info *)&reporting_info, player->unit_index, 0.0f, 0.0f, nullptr, nullptr, 1);
			}
		}
		false ? player->flags |= 0x800 : player->flags &= ~0x800;
	}
}

void player_update_after_game_hook(long player_index) // 0x108DC6A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_update_after_game_hook@@YAXJ@Z");
	// `anonymous-namespace'::player_update_after_game_hook
	// long player_index;
	// void (*const player_after_game)(long);
	// function call : void (*const)(long)

	const auto player_update_after_game = (void(*)(long))0x68A100;

	player_update_after_game(player_index);
	::Patches::Sprint::UpdatePlayerSprint(player_index);
	::Player::PlayerPodium::UpdatePlayer(player_index);
	player_handle_coop_respawn(player_index);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Patches::Network::PlayerPropertiesExtender & Utils::Singleton<Patches::Network::PlayerPropertiesExtender>::Instance();
template bool c_tag_block<s_game_globals_player_information>::try_get_element(__int32, s_game_globals_player_information **) const;
template s_game_globals_player_information & c_tag_block<s_game_globals_player_information>::operator[](__int32);
template s_game_globals_player_information * c_tag_block<s_game_globals_player_information>::get_element(__int32) const;
template unsigned __int32 Patches::Network::PlayerPropertiesExtension<s_player_appearance>::GetDataSize() const;
template void Patches::Network::PlayerPropertiesExtension<s_player_appearance>::ApplyData(__int32, s_player_configuration *, void const *);
template void Patches::Network::PlayerPropertiesExtension<s_player_appearance>::BuildData(__int32, void *);
template void Patches::Network::PlayerPropertiesExtension<s_player_appearance>::Deserialize(Blam::BitStream *, void *);
template void Patches::Network::PlayerPropertiesExtension<s_player_appearance>::Serialize(Blam::BitStream *, void const *);
template void Pointer::Write<unsigned char>(unsigned char const) const;

/* ---------- explicit instantiations */
template Patches::Network::PlayerPropertiesExtension<s_player_appearance>::PlayerPropertiesExtension();
