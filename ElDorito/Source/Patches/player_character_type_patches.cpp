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

_extern void _sub_10ABC410();
void player_character_type_patches_apply() // 0x10ABC410
{
	mangled_x86(MANGLED_TODO, "?player_character_type_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_10ABC410();
}

/* ---------- private code */

_extern void _sub_10ABE740(long, long, long *, unsigned long *);
void player_find_player_character_unit_and_variant_info(long player_index, long character_type_index, long *out_unit_definition_index, unsigned long *out_variant_name) // 0x10ABE740
{
	// `anonymous-namespace'::player_find_player_character_unit_and_variant_info
	// long player_index;
	// long character_type_index;
	// long *out_unit_definition_index;
	// unsigned long *out_variant_name;
	// long representation_index;
	// s_game_globals_player_representation *player_representation;
	// long third_person_unit_index;
	// long thid_person_variant_name;
	todo("implement");
	_sub_10ABE740(player_index, character_type_index, out_unit_definition_index, out_variant_name);
}

bool find_best_starting_location_index__game_is_survival_hook() // 0x10ABC180
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?find_best_starting_location_index__game_is_survival_hook@@YA_NXZ");
	// `anonymous-namespace'::find_best_starting_location_index__game_is_survival_hook
	// procedure flags: nofpo

	return false;
}

_extern bool _sub_10ABE530(long, real_point3d *, float *, float *, bool, bool);
bool player_find_best_spawn_location_hook(long player_index, real_point3d *position, float *facing, float *pitch, bool a5, bool a6) // 0x10ABE530
{
	// `anonymous-namespace'::player_find_best_spawn_location_hook
	// bool a6;
	// constexpr bool (*const `player_find_best_spawn_location_hook'::`2'::player_find_best_spawn_location)(long, real_point3d *, float *, float *, bool, bool); // constant == 5479984
	// long (*const scenario_find_best_starting_location_index)(long, bool, bool);
	// bool found;
	{
		// long starting_location_index;
		{
			// s_scenario *scnr;
		}
		{
			// char *sandbox_globals;
		}
	}
	// function call : bool (*const)(long, real_point3d *, float *, float *, bool, bool)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : long (*const)(long, bool, bool)
	todo("implement");
	bool __result = _sub_10ABE530(player_index, position, facing, pitch, a5, a6);
	return __result;
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

_extern void _sub_10ABE860(long, long *, unsigned long *);
void player_find_player_character_unit_and_variant_info_hook(long player_index, long *out_unit_definition_index, unsigned long *out_variant_name) // 0x10ABE860
{
	// `anonymous-namespace'::player_find_player_character_unit_and_variant_info_hook
	// unsigned long *out_variant_name;
	// s_player_datum *player;
	// short index;
	{
		// s_scenario *scnr;
		// Blam::Network::Session *session;
		{
			// short i;
			{
				// __int32 player_session_index;
				// unsigned long name;
			}
		}
	}
	// function call : bool (*const)()
	todo("implement");
	_sub_10ABE860(player_index, out_unit_definition_index, out_variant_name);
}

extern s_weapon_first_person_block *_sub_10ABEE10(s_weapon_definition *, long);
s_weapon_first_person_block *weapon_definition_get_first_person_interface_by_character_hook(s_weapon_definition *weapon_definition, long representation_index) // 0x10ABEE10
{
	// `anonymous-namespace'::weapon_definition_get_first_person_interface_by_character_hook
	// static ...; // 0x10ABEEF8
	// static ...; // 0x10ABEEF0
	// s_weapon_definition *weapon_definition;
	// long representation_index;
	// s_game_globals *game_globals;
	{
		// long i;
		{
			// s_game_globals_player_character_type *const character_type;
			// long expected_representation_index;
			{
				// s_weapon_first_person_block *fp_interface;
			}
		}
	}
	todo("implement");
	s_weapon_first_person_block * __result = _sub_10ABEE10(weapon_definition, representation_index);
	return __result;
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

_extern void _sub_10ABBFE0(long);
void chud_sounds_fix_hook(long player_index) // 0x10ABBFE0
{
	// `anonymous-namespace'::chud_sounds_fix_hook
	// static ...; // 0x10ABC114
	// static ...; // 0x10ABC108
	// static ...; // 0x10ABC100
	// long player_index;
	// s_player_datum *player;
	// constexpr void (*const `chud_sounds_fix_hook'::`2'::chud_update_sounds)(long, unsigned __int32, c_tag_block<s_chud_sound> *, long *, unsigned short *); // constant == 11049584
	// long output_unit_index;
	{
		// s_chud_per_character_globals *character_hud_globals;
		// s_chud_globals_definition *hud_globals;
		// long character_hud_globals_index;
		{
			// char *persistent_chud_data;
		}
	}
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, unsigned __int32, c_tag_block<s_chud_sound> *, long *, unsigned short *)
	// function call : void (*)(long, long)
	todo("implement");
	_sub_10ABBFE0(player_index);
}

extern s_model_variant *_sub_10ABEA10(long);
s_model_variant *player_get_model_variant_hook(long player_index) // 0x10ABEA10
{
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
	todo("implement");
	s_model_variant * __result = _sub_10ABEA10(player_index);
	return __result;
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
