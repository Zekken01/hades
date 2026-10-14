/* ---------- headers */

#include "hades/hades.h"

#include "Blam/ai/actor.hpp"
#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
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
#include "Blam/interface/chud/chud_globals.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/items/weapon_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/models/model_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/biped_definitions.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patch.hpp"
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
struct s_biped_definition;
struct s_chud_globals_definition;
struct s_chud_per_character_globals;
struct s_chud_sound;
struct s_game_globals;
struct s_game_globals_player_character_type;
struct s_game_globals_player_control;
struct s_game_globals_player_information;
struct s_game_globals_player_representation;
struct s_model_definition;
struct s_model_variant;
struct s_player_datum;
struct s_scenario;
struct s_weapon_definition;
struct s_weapon_first_person_block;
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern bool (*const game_engine_is_sandbox)();  // hades: added for 0x10ABE530

extern bool (*const game_is_multiplayer)();  // hades: added for 0x10ABE860
long player_find_character_type_by_name(unsigned long name);  // hades: added for 0x10ABE860

long get_player_character_representation_index(s_game_globals_player_character_type const &character_type);  // hades: added for 0x10ABEE10

extern long get_player_character_representation_index(long character_type_index);  // hades: added for 0x10ABE740

long unit_get_global_player_representation_block_index(long unit_index);  // hades: added for 0X10ABC220

bool unit_try_get_global_player_character_type(long unit_index, s_game_globals_player_character_type **out_player_character);  // hades: added for 0X10ABBF00

long unit_get_global_player_control_block_index(long unit_index);  // hades: added for 0X10ABEBE0
long unit_get_global_player_information_block_index(long unit_index);  // hades: added for 0X10ABEBE0

extern void player_character_type_patches_apply();

void player_find_player_character_unit_and_variant_info(long player_index, long character_type_index, long *out_unit_definition_index, unsigned long *out_variant_name);
bool find_best_starting_location_index__game_is_survival_hook();
bool player_find_best_spawn_location_hook(long player_index, real_point3d *position, float *facing, float *pitch, bool a5, bool a6);
long chud_character_globals_index_from_output_user_hook(long output_user_index);
void player_find_player_character_unit_and_variant_info_hook(long player_index, long *out_unit_definition_index, unsigned long *out_variant_name);
s_weapon_first_person_block *weapon_definition_get_first_person_interface_by_character_hook(s_weapon_definition *weapon_definition, long representation_index);
void player_submit_actions_53E2B2();
void player_submit_actions_53E4F6();
void player_submit_actions_53EA06();
bool player_submit_actions_53D580_hook(long unit_index);
long game_globals_player_representation_index_from_player_index_hook(long player_index);
s_game_globals_player_representation *game_globals_player_representation_from_player_index_hook(long player_index);
void chud_sounds_fix_hook(long player_index);
s_model_variant *player_get_model_variant_hook(long player_index);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern s_game_globals_player_control *g_temp_global_player_control; // 0x12467358
	extern s_game_globals_player_information *g_temp_global_player_information; // 0x1246735C
}
using namespace hades_file_local;
/* ---------- public code */

void player_character_type_patches_apply() // 0x10ABC410
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_character_type_patches_apply@@YAXXZ");
	// procedure flags: nofpo

	Hook(0x139F70, player_find_player_character_unit_and_variant_info_hook).Apply();
	Hook(0x137430, player_get_model_variant_hook).Apply();
	Hook(0x7E1BF0, unit_get_global_player_information_block_index, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x7B0F28, unit_get_global_player_information_block_index, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x7A445C, unit_get_global_player_information_block_index, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x7861C4, unit_get_global_player_information_block_index, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x75C4B6, unit_get_global_player_information_block_index, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x73F44D, unit_get_global_player_information_block_index, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x73F336, unit_get_global_player_information_block_index, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x738459, unit_get_global_player_information_block_index, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x6D7189, unit_get_global_player_information_block_index, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x69DFA2, unit_get_global_player_information_block_index, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x284E68, unit_get_global_player_information_block_index, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x13A401, unit_get_global_player_control_block_index, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x13B5C3, unit_get_global_player_control_block_index, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x13C5A3, unit_get_global_player_control_block_index, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x1D118C, unit_get_global_player_control_block_index, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x1D3C66, unit_get_global_player_control_block_index, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x25FA26, unit_get_global_player_control_block_index, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x32987F, unit_get_global_player_control_block_index, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x7AE92F, unit_get_global_player_control_block_index, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x13CF37, player_find_best_spawn_location_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x1376B1, find_best_starting_location_index__game_is_survival_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x13D580, player_submit_actions_53D580_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x13E2B2, player_submit_actions_53E2B2).Apply();
	Hook(0x13E4F6, player_submit_actions_53E4F6).Apply();
	Hook(0x13EA06, player_submit_actions_53EA06).Apply();
	Patch(0x143781, { 0xE9, 0x85, 0x00, 0x00, 0x00 }).Apply();
	Hook(0x13A770, game_globals_player_representation_index_from_player_index_hook).Apply();
	Hook(0x13A6F0, game_globals_player_representation_from_player_index_hook).Apply();
	Hook(0x140350, unit_get_global_player_representation_block_index).Apply();
	Hook(0x7BF830, weapon_definition_get_first_person_interface_by_character_hook).Apply();
	Hook(0x6895C0, chud_character_globals_index_from_output_user_hook).Apply();
	Patch(0x770379, { 0xEB }).Apply();
	Hook(0x13CADE, chud_sounds_fix_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
}

/* ---------- private code */

void player_find_player_character_unit_and_variant_info(long player_index, long character_type_index, long *out_unit_definition_index, unsigned long *out_variant_name) // 0x10ABE740
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_find_player_character_unit_and_variant_info@@YAXJJPAJPAK@Z");
	// `anonymous-namespace'::player_find_player_character_unit_and_variant_info
	// long player_index;
	// long character_type_index;
	// long *out_unit_definition_index;
	// unsigned long *out_variant_name;
	// long representation_index;
	// s_game_globals_player_representation *player_representation;
	// long third_person_unit_index;
	// long thid_person_variant_name;

	long third_person_unit_index = -1;
	long thid_person_variant_name = 0;
	s_game_globals_player_representation *player_representation;
	long representation_index = get_player_character_representation_index(character_type_index);
	if (game_globals_get()->PlayerRepresentation.try_get_element(representation_index, &player_representation))
	{
		third_person_unit_index = player_representation->ThirdPersonUnit.index;
		thid_person_variant_name = player_representation->ThirdPersonVariant;
	}

	if (out_unit_definition_index)
		*out_unit_definition_index = third_person_unit_index;
	if (out_variant_name)
		*out_variant_name = thid_person_variant_name;
}

bool find_best_starting_location_index__game_is_survival_hook() // 0x10ABC180
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?find_best_starting_location_index__game_is_survival_hook@@YA_NXZ");
	// `anonymous-namespace'::find_best_starting_location_index__game_is_survival_hook
	// procedure flags: nofpo

	return false;
}

bool player_find_best_spawn_location_hook(long player_index, real_point3d *position, float *facing, float *pitch, bool a5, bool a6) // 0x10ABE530
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_find_best_spawn_location_hook@@YA_NJPAUreal_point3d@@PAM1_N2@Z");
	// `anonymous-namespace'::player_find_best_spawn_location_hook
	// bool a6;
	// constexpr bool (*const `player_find_best_spawn_location_hook'::`2'::player_find_best_spawn_location)(long, real_point3d *, float *, float *, bool, bool); // constant == 5479984
	// long (*const scenario_find_best_starting_location_index)(long, bool, bool);
	// bool found;
		// long starting_location_index;
			// s_scenario *scnr;
			// char *sandbox_globals;
	// function call : bool (*const)(long, real_point3d *, float *, float *, bool, bool)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : long (*const)(long, bool, bool)

	long (*const scenario_find_best_starting_location_index)(long, bool, bool) = reinterpret_cast<long (*)(long, bool, bool)>(0x5375B0);
	bool found = ((bool (*)(long, real_point3d *, float *, float *, bool, bool))0x539E30)(player_index, position, facing, pitch, a5, a6);
	if (found)
		return true;
	if (game_engine_is_sandbox() && ((bool (*)())0x5319C0)())
	{
		long starting_location_index = scenario_find_best_starting_location_index(player_index, a5, a6);
		if (starting_location_index != -1)
		{
			s_scenario *scnr = global_scenario_get();
			*position = scnr->player_starting_locations[starting_location_index].position;
			*facing = 0.0f;
			*pitch = 0.0f;
		}
		else
		{
			char *sandbox_globals = *(char **)tls_get(0x48) + 0xE190;
			*(unsigned long *)offset_pointer(sandbox_globals, 8) |= 1 << (player_index & 0xF);
			*position = global_origin3d;
			*facing = 0.0f;
			*pitch = 0.0f;
		}
		found = true;
	}
	return found;
}

long chud_character_globals_index_from_output_user_hook(long output_user_index) // 0x10ABBF00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?chud_character_globals_index_from_output_user_hook@@YAJJ@Z");
	// `anonymous-namespace'::chud_character_globals_index_from_output_user_hook
	// static ...; // 0x10ABBF98
	// static ...; // 0x10ABBF8C
	// static ...; // 0x10ABBF84
	// long output_user_index;
	// long unit_index;
	// s_game_globals_player_character_type *player_character;
	// function call : unsigned long (*const)(long)

	long unit_index = ((long (*)(long))0x589CC0)(output_user_index);
	s_game_globals_player_character_type *player_character;
	if (unit_try_get_global_player_character_type(unit_index, &player_character))
		return player_character->chud_character_globals_block_index;
	return 0;
}

void player_find_player_character_unit_and_variant_info_hook(long player_index, long *out_unit_definition_index, unsigned long *out_variant_name) // 0x10ABE860
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_find_player_character_unit_and_variant_info_hook@@YAXJPAJPAK@Z");
	// `anonymous-namespace'::player_find_player_character_unit_and_variant_info_hook
	// unsigned long *out_variant_name;
	// s_player_datum *player;
	// short index;
		// s_scenario *scnr;
		// Blam::Network::Session *session;
			// short i;
				// __int32 player_session_index;
				// unsigned long name;
	// function call : bool (*const)()

	s_player_datum *player = player_get(player_index);
	short index = -1;
	if (game_is_multiplayer())
	{
		index = player->character_type_index;
	}
	else
	{
		s_scenario *scnr = global_scenario_get();
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (session && scnr->campaign_players.count > 0)
		{
			for (short i = 0; i < scnr->campaign_players.count; i++)
			{
				unsigned long name = scnr->campaign_players[i].player_representation;
				__int32 player_session_index = session->MembershipInfo.GetPeerPlayer(player->machine_index);
				if (player_session_index == i)
				{
					index = player_find_character_type_by_name(name);
					break;
				}
			}
		}
		if (index == -1)
			index = player_find_character_type_by_name(0xCB);
	}
	if (index == -1)
		index = 0;
	player_find_player_character_unit_and_variant_info(player_index, index, out_unit_definition_index, out_variant_name);
}

s_weapon_first_person_block *weapon_definition_get_first_person_interface_by_character_hook(s_weapon_definition *weapon_definition, long representation_index) // 0x10ABEE10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?weapon_definition_get_first_person_interface_by_character_hook@@YAPAUs_weapon_first_person_block@@PAUs_weapon_definition@@J@Z");
	// `anonymous-namespace'::weapon_definition_get_first_person_interface_by_character_hook
	// static ...; // 0x10ABEEF8
	// static ...; // 0x10ABEEF0
	// s_weapon_definition *weapon_definition;
	// long representation_index;
	// s_game_globals *game_globals;
		// long i;
			// s_game_globals_player_character_type *const character_type;
			// long expected_representation_index;
				// s_weapon_first_person_block *fp_interface;

	s_game_globals *game_globals = game_globals_get();
	for (long i = 0; i < game_globals->player_character_types.count; i++)
	{
		s_game_globals_player_character_type *const character_type = &game_globals->player_character_types[i];
		long expected_representation_index = get_player_character_representation_index(*character_type);
		if (representation_index == expected_representation_index)
		{
			s_weapon_first_person_block *fp_interface;
			if (weapon_definition->first_person.try_get_element(character_type->first_person_weapon_interface_block_index, &fp_interface))
				return fp_interface;
		}
	}
	return nullptr;
}

__declspec(naked) void player_submit_actions_53E2B2() // 0x10ABECC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_submit_actions_53E2B2@@YAXXZ");
	// procedure flags: nofpo

	__asm
	{
		mov ecx, g_temp_global_player_control
		push 0x53E2B8
		ret
	}
}

__declspec(naked) void player_submit_actions_53E4F6() // 0x10ABECD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_submit_actions_53E4F6@@YAXXZ");
	// procedure flags: nofpo

	__asm
	{
		mov ecx, g_temp_global_player_control
		push 0x53E4FC
		ret
	}
}

__declspec(naked) void player_submit_actions_53EA06() // 0x10ABECE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_submit_actions_53EA06@@YAXXZ");
	// procedure flags: nofpo

	__asm
	{
		mov ecx, g_temp_global_player_information
		push 0x53EA0C
		ret
	}
}

bool player_submit_actions_53D580_hook(long unit_index) // 0x10ABEBE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_submit_actions_53D580_hook@@YA_NJ@Z");
	// `anonymous-namespace'::player_submit_actions_53D580_hook
	// long unit_index;
	// long player_info_block_index;
	// bool (*const unit_movement_inhibited_by_equipment)(long);
	// long player_control_block_index;
	// function call : bool (*const)(long)

	bool (__cdecl *const player_submit_actions_53D580)(long) = (bool(__cdecl *const)(long))0xb44f90;
	long player_control_block_index = unit_get_global_player_control_block_index(unit_index);
	long player_information_block_index = unit_get_global_player_information_block_index(unit_index);
	g_temp_global_player_control = &game_globals_get()->PlayerControl[player_control_block_index];
	g_temp_global_player_information = &game_globals_get()->PlayerInformation[player_control_block_index];
	return player_submit_actions_53D580(unit_index);
}

long game_globals_player_representation_index_from_player_index_hook(long player_index) // 0x10ABC220
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_globals_player_representation_index_from_player_index_hook@@YAJJ@Z");
	// `anonymous-namespace'::game_globals_player_representation_index_from_player_index_hook
	// long player_index;
	// s_player_datum *player;
	// long unit;
	// function call : unsigned long (*const)(long)

	s_player_datum *player = player_get(player_index);
	void *player_representation = ((void *(__cdecl *)(long))0x589cc0)(0);

	if (*(long *)((unsigned char *)player + 0x30) != -1)
		return unit_get_global_player_representation_block_index(*(long *)((unsigned char *)player + 0x30));
	return 0;
}

s_game_globals_player_representation *game_globals_player_representation_from_player_index_hook(long player_index) // 0x10ABC1A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_globals_player_representation_from_player_index_hook@@YAPAUs_game_globals_player_representation@@J@Z");
	// `anonymous-namespace'::game_globals_player_representation_from_player_index_hook
	// long player_index;
	// long index;

	long index = game_globals_player_representation_index_from_player_index_hook(player_index);

	return &game_globals_get()->PlayerRepresentation[index];
}

void chud_sounds_fix_hook(long player_index) // 0x10ABBFE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?chud_sounds_fix_hook@@YAXJ@Z");
	// `anonymous-namespace'::chud_sounds_fix_hook
	// static ...; // 0x10ABC114
	// static ...; // 0x10ABC108
	// static ...; // 0x10ABC100
	// long player_index;
	// s_player_datum *player;
	// constexpr void (*const `chud_sounds_fix_hook'::`2'::chud_update_sounds)(long, unsigned __int32, c_tag_block<s_chud_sound> *, long *, unsigned short *); // constant == 11049584
	// long output_unit_index;
		// s_chud_per_character_globals *character_hud_globals;
		// s_chud_globals_definition *hud_globals;
		// long character_hud_globals_index;
			// char *persistent_chud_data;
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, unsigned __int32, c_tag_block<s_chud_sound> *, long *, unsigned short *)
	// function call : void (*)(long, long)

	long output_unit_index = ((long (*)(long))0x589CC0)(0);
	s_player_datum *player = player_get(player_index);
	if (player && output_unit_index != -1 && output_unit_index == player->unit_index)
	{
		s_chud_globals_definition *hud_globals = *(s_chud_globals_definition **)0x5257C40;
		long character_hud_globals_index = chud_character_globals_index_from_output_user_hook(0);
		s_chud_per_character_globals *character_hud_globals;
		if (hud_globals->character_globals.try_get_element(character_hud_globals_index, &character_hud_globals))
		{
			char *persistent_chud_data = *(char **)tls_get(0x420);
			((void (*)(long, unsigned __int32, c_tag_block<s_chud_sound> *, long *, unsigned short *))0xA89A70)(0, 0, &character_hud_globals->sounds, (long *)(persistent_chud_data + 0x3E0C), (unsigned short *)(persistent_chud_data + 0x3E8C));
		}
	}
	((void (*)(long, long))0x58A2B0)(player_index, -1);
}

s_model_variant *player_get_model_variant_hook(long player_index) // 0x10ABEA10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_get_model_variant_hook@@YAPAUs_model_variant@@J@Z");
	// `anonymous-namespace'::player_get_model_variant_hook
	// static ...; // 0x10ABEB61
	// static ...; // 0x10ABEB54
	// static ...; // 0x10ABEB3C
	// static ...; // 0x10ABEB34
	// long player_index;
	// long biped_definition_index;
	// s_biped_definition *biped;
	// unsigned long variant_name;
	// s_game_globals_player_representation *representation;
	// long model_variant_index;
	// s_model_definition *model;
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)

	s_game_globals_player_representation *representation = game_globals_player_representation_from_player_index_hook(player_index);
	if (!representation || representation->ThirdPersonUnit.index == -1)
		return nullptr;

	long biped_definition_index = -1;
	unsigned long variant_name = 0;
	player_find_player_character_unit_and_variant_info_hook(player_index, &biped_definition_index, &variant_name);
	if (biped_definition_index == -1)
		return nullptr;

	s_biped_definition *biped = (s_biped_definition *)tag_get(0x62697064, biped_definition_index);
	long model_variant_index = object_lookup_variant_index_from_name(biped->model.index, variant_name);
	if (model_variant_index == -1)
		return nullptr;

	s_model_definition *model = (s_model_definition *)tag_get(0x686C6D74, biped->model.index);
	return &model->variants[model_variant_index];
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_game_globals_player_control>::try_get_element(__int32, s_game_globals_player_control **) const;
template bool c_tag_block<s_scenario_player>::try_get_element(__int32, s_scenario_player **) const;
template bool c_tag_block<s_weapon_first_person_block>::try_get_element(__int32, s_weapon_first_person_block **) const;
template c_tag_block_index<s_chud_per_character_globals,char>::operator char() const;
template c_tag_block_index<s_weapon_first_person_interface_definition,char>::operator char() const;
template s_game_globals_player_control & c_tag_block<s_game_globals_player_control>::operator[](__int32);
template s_game_globals_player_control * c_tag_block<s_game_globals_player_control>::get_element(__int32) const;
template s_scenario_player & c_tag_block<s_scenario_player>::operator[](__int32);
template s_scenario_player * c_tag_block<s_scenario_player>::get_element(__int32) const;

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { s_game_globals_player_control *g_temp_global_player_control; }
namespace hades_file_local { s_game_globals_player_information *g_temp_global_player_information; }
