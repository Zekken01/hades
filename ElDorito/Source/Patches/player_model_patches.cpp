/* ---------- headers */

#include "hades/hades.h"

#include "Blam/ai/actor.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/multiplayer_definitions.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/player_model_customization.hpp"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/models/model_definitions.hpp"
#include "Blam/mods/mod_globals.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/ModGlobals.hpp"
#include "mods/new/IModManager.hpp"
#include "Modules/ModuleGame.hpp"
#include "Modules/ModulePlayer.hpp"
#include "Patch.hpp"
#include "Player/PlayerCharacterSystem.hpp"
#include "Player/PlayerCustomizationDB.hpp"
#include "Pointer.hpp"
#include "Utils/MathUtils.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
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
#include <deque>
#include <exception>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>
#include "Player/PlayerCustomization.hpp"  // hades: added for 0X10AB8E10

/* ---------- forward declarations */

class c_mod_package_manager;
struct UiPlayerModelState;
struct begin;
struct c_game_engine;
struct end;
struct lambda_1;
struct real_point3d;
struct real_rgb_color;
struct real_vector3d;
struct s_game_globals;
struct s_game_globals_player_character_type;
struct s_game_globals_player_representation;
struct s_mod_globals_definition;
struct s_mod_globals_player_character_customization;
struct s_model_customization_player_region;
struct s_model_customization_player_region_permutation;
struct s_model_customization_region_permutation;
struct s_model_customization_selection;
struct s_model_definition;
struct s_model_permutation;
struct s_model_permutation_possibility;
struct s_model_region;
struct s_model_variant;
struct s_model_variant_region;
struct s_multiplayer_globals_definition;
struct s_multiplayer_universal_globals_definition;
struct s_object_data;
struct s_object_header;
struct s_object_region_information;
struct s_player_appearance;
struct s_player_datum;
struct s_player_model_customization;
struct s_scenario_location;
struct s_unit_data;
namespace Modules
{
	class ModuleGame;
	class ModulePlayer;
	struct Command;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace Mods {}
using namespace ::Mods;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

// UiPlayerModelState is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

//class player_model_patches_apply::__l2::<lambda_1>
//{
//public:
//	void operator()(Modules::Command const *) const;
//	<lambda_1>(player_model_patches_apply::__l2::<lambda_1> &);
//	<lambda_1>(Modules::ModuleGame &);
//private:
//	Modules::ModuleGame &gameModule; // 0x0
//public:
//	player_model_patches_apply::__l2::<lambda_1> &operator=(player_model_patches_apply::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(player_model_patches_apply::__l2::<lambda_1>) == 4, "Invalid player_model_patches_apply::__l2::<lambda_1> size");

/* ---------- prototypes */

extern void *(__cdecl *const tag_get)(unsigned long, long);  // hades: added for 0X10ABB040
extern long (__cdecl *const tag_get_first_in_group)(unsigned long);  // hades: added for 0X10ABB040

extern s_game_globals *try_and_get_game_globals();
extern long get_multiplayer_player_model_customization_block_index(long unit_index);
extern s_player_model_customization const *player_get_model_customization(s_player_datum *player);
extern void player_refresh_object_appearance_full_hook(long player_index, long object_index);
extern void recreate_child_objects_for_customization(long object_index, long region_discard_mask, s_model_customization_region_permutation *region_permutations, long region_permutations_count);
extern void player_model_customize(s_player_model_customization const *customization_data, long unit_index);
extern void model_permutation_possibility_set(long permutation_index, s_model_permutation_possibility *possibility);
extern void model_select_initial_permutation(long model_definition_index, long variant_index, unsigned char *region_permutation_indices, s_object_region_information *region_info, unsigned long discard_mask, s_model_customization_region_permutation *region_permutations, long region_permutation_count);
extern long find_player_character_by_name(char const *name);
extern std::string GetCurrentPreferredCharacter();
extern void clearCachedCharacter();
extern s_mod_globals_player_character_customization *try_get_customization_character(std::string const &name);
extern long scenario_find_named_object(long name_index);
extern long user_interface_find_model_customization_biped();
extern long user_interface_find_char_platform();
extern void unit_refresh_hologram_appearance_hook(long creator_unit_index, long hologram_unit_index);
extern real_rgb_color *network_get_team_color(real_rgb_color *color, long team);
extern unsigned char get_character_team_color_override_flags(long character_type_index);
extern unsigned char get_player_team_color_override_flags(long player_index);
extern bool find_player_customized_character_by_name(long player_index, unsigned long character_name);
extern void game_engine_get_player_colors(long player_index, s_player_model_customization const *customization, real_rgb_color *out_colors);
extern void game_engine_get_player_colors_hook(long player_index, s_player_model_customization const *customization, long team_index, real_rgb_color *out_colors, bool *custom_colors);
extern long ui_get_player_model_id_hook();
extern void player_model_patches_apply();
extern void RefreshUiPlayer();
extern void PoseWithWeapon(unsigned __int32 unit, unsigned __int32 weaponTag);
extern __int32 player_model_get_region_permutation(__int32 player_model_index, char const *region_name, char const *permutation_name);
extern void unit_copy_player_appearance(long source_player_unit_index, long target_unit_index);
extern unsigned char player_model_get_index(char const *name);
extern void CustomizeObjectColors(long objectIndex, s_player_model_customization const *customization);
extern void CustomizeBipeds();
extern void update_customization_biped();
extern void set_customization_bipeds();
extern void UpdateUiPlayerModelArmor();
extern bool CharacterHasFlag(__int32 flag);
extern void SetUiPlayerModelPosition(real_vector3d const *newPosition);
extern void SetUiPlayerModelRotation(float angleDegrees, float seconds);

/* ---------- globals */

extern bool updateUiPlayerArmor; // 0x1246732C
extern long customization_biped_index; // 0x11354910
extern long customization_char_platform_index; // 0x11354914
extern float &customzation_biped_angle_degrees; // 0x11354918
extern bool customization_biped_angle_dirty; // 0x1246732D
extern __int32 customization_biped_flags; // 0x1135491C
extern UiPlayerModelState s_UiPlayerModelState; // 0x12467330

/* ---------- private variables */

/* ---------- public code */

s_game_globals *try_and_get_game_globals() // 0x10ABB040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?try_and_get_game_globals@@YAPAUs_game_globals@@XZ");
	// procedure flags: nofpo
	// function call : long (*const)(unsigned long)
	// function call : void *(*const)(unsigned long, long)

	return (s_game_globals *)tag_get(0x6D617467, tag_get_first_in_group(0x6D617467));
}

_extern long _sub_10AB8400(long);
long get_multiplayer_player_model_customization_block_index(long unit_index) // 0x10AB8400
{
	mangled_x86(MANGLED_TODO, "?get_multiplayer_player_model_customization_block_index@@YAJJ@Z");
	// static ...; // 0x10AB8534
	// static ...; // 0x10AB8528
	// static ...; // 0x10AB8520
	// long unit_index;
	// s_game_globals *game_globals;
	// s_unit_data *unit_object;
	{
		// c_tag_block<s_game_globals_player_character_type> &<range>$L0;
		// s_game_globals_player_character_type *<begin>$L0;
		// s_game_globals_player_character_type *<end>$L0;
		{
			// s_game_globals_player_character_type &character_type;
			{
				// long player_representation_index;
				// s_game_globals_player_representation *player_representation;
			}
		}
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	long __result = _sub_10AB8400(unit_index);
	return __result;
}

s_player_model_customization const *player_get_model_customization(s_player_datum *player) // 0x10AB8E10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_get_model_customization@@YAPBUs_player_model_customization@@PAUs_player_datum@@@Z");
	// s_player_datum *player;
	// __int32 player_index;
	// c_data_array<s_player_datum> *players;
	// __int32 offset;
	// __int32 absolute_index;
		// s_player_datum *datum;
		// s_player_datum *player;

	c_data_array<s_player_datum> *players = players_get();
	__int32 offset = (char *)player - (char *)players->address;
	__int32 absolute_index = offset / 12040u;
	__int32 player_index = NONE;

	if (absolute_index < 16)
	{
		s_player_datum *datum = players->get_absolute(absolute_index);
		player_index = (datum->salt << 16) | absolute_index;

		s_player_datum *player = player_get(player_index);
		if (!player || player->salt != datum->salt)
		{
			player_index = NONE;
		}
	}

	return Player::CPlayerCustomization::GetInGamePlayerCustomization(player_index);
}

_extern void _sub_10ABA680(long, long);
void player_refresh_object_appearance_full_hook(long player_index, long object_index) // 0x10ABA680
{
	mangled_x86(MANGLED_TODO, "?player_refresh_object_appearance_full_hook@@YAXJJ@Z");
	// static ...; // 0x10ABA94C
	// static ...; // 0x10ABA934
	// static ...; // 0x10ABA92C
	// long player_index;
	// long object_index;
	// s_player_datum *player;
	// real_rgb_color colors[5];
	// long team_index;
	// char (*const set_object_base_change_color_by_index)(long, long, real_rgb_color const *);
	// s_player_model_customization const *customization;
	// s_object_data *object;
	// void (*const object_set_initial_change_colors)(long, __int32, real_rgb_color const *);
	// long (*const game_engine_get_change_colors)(long, s_player_model_customization const *, long, real_rgb_color *, bool *);
	// bool custom_colors;
	// void (*const object_apply_change_colors)(long);
	{
		// s_unit_data *unit;
	}
	{
		// long i;
	}
	{
		// long child_index;
		{
			// s_object_data *child_object;
		}
	}
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : long (*const)(long, s_player_model_customization const *, long, real_rgb_color *, bool *)
	// function call : char (*const)(long, long, real_rgb_color const *)
	// function call : void (*const)(long, __int32, real_rgb_color const *)
	// function call : void (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	_sub_10ABA680(player_index, object_index);
}

_extern void _sub_10ABAA80(long, long, s_model_customization_region_permutation *, long);
void recreate_child_objects_for_customization(long object_index, long region_discard_mask, s_model_customization_region_permutation *region_permutations, long region_permutations_count) // 0x10ABAA80
{
	mangled_x86(MANGLED_TODO, "?recreate_child_objects_for_customization@@YAXJJPAUs_model_customization_region_permutation@@J@Z");
	// long region_permutations_count;
	// void (*const object_detach)(long);
	// void (*const object_create_children)(long);
	// s_unit_data *object;
	// void (*const object_delete_immediately)(long);
	{
		// long child_index;
		{
			// s_object_data *child_object;
			// long next_index;
		}
	}
	{
		{
		}
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long)
	// function call : void (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, unsigned long, s_model_customization_region_permutation const *, long)
	todo("implement");
	_sub_10ABAA80(object_index, region_discard_mask, region_permutations, region_permutations_count);
}

_extern void _sub_10AB8F00(s_player_model_customization const *, long);
void player_model_customize(s_player_model_customization const *customization_data, long unit_index) // 0x10AB8F00
{
	mangled_x86(MANGLED_TODO, "?player_model_customize@@YAXPBUs_player_model_customization@@J@Z");
	// static ...; // 0x10AB92C0
	// static ...; // 0x10AB92B8
	// s_player_model_customization const *customization_data;
	// long unit_index;
	// s_unit_data *unit;
	// s_multiplayer_globals_definition *multiplayer_globals_definition;
	// s_game_globals *globals_definition;
	// unsigned long region_discard_mask;
	// s_multiplayer_universal_globals_definition *universal_globals;
	// long region_permutation_count;
	// s_model_customization_selection *selected_model;
	// s_static_array<s_model_customization_region_permutation,16> region_permutations;
	// long player_model_index;
	// long customize_from_unit_index;
	{
		// __int32 region_index;
		{
			// s_model_customization_player_region_permutation *permutation;
			// char permutation_index;
			// s_model_customization_player_region *region;
			{
				// __int32 variant_index;
			}
		}
	}
	// function call : bool (*)()
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(long, unsigned long, s_model_customization_region_permutation const *, long)
	todo("implement");
	_sub_10AB8F00(customization_data, unit_index);
}

void model_permutation_possibility_set(long permutation_index, s_model_permutation_possibility *possibility) // 0x10AB8690
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?model_permutation_possibility_set@@YAXJPAUs_model_permutation_possibility@@@Z");
	// s_model_permutation_possibility *possibility;

	possibility->runtime_permutation_index = permutation_index;
	possibility->variant_permutation_index = -1;
	possibility->state = 0;
	possibility->property_flags = 0;
	possibility->looping_effect_index = -1;
	possibility->looping_effect_marker = 0;
	possibility->probability = 1.0f;
}

_extern void _sub_10AB8700(long, long, unsigned char *, s_object_region_information *, unsigned long, s_model_customization_region_permutation *, long);
void model_select_initial_permutation(long model_definition_index, long variant_index, unsigned char *region_permutation_indices, s_object_region_information *region_info, unsigned long discard_mask, s_model_customization_region_permutation *region_permutations, long region_permutation_count) // 0x10AB8700
{
	mangled_x86(MANGLED_TODO, "?model_select_initial_permutation@@YAXJJPAEPAUs_object_region_information@@KPAUs_model_customization_region_permutation@@J@Z");
	// unsigned char *region_permutation_indices;
	// s_object_region_information *region_info;
	// unsigned long discard_mask;
	// s_model_customization_region_permutation *region_permutations;
	// long region_permutation_count;
	// void (*const model_find_permutation_possibilities)(s_model_variant_region *, long, long, long, bool, long *, long, s_model_permutation_possibility *);
	// s_model_permutation_possibility possibilities[128];
	// long (*const model_select_permutation_possibility)(long, s_model_permutation_possibility *);
	// s_model_definition *model;
	{
		// __int32 i;
	}
	{
		{
			// long possibility_count;
			// s_model_region &region;
			{
				// s_model_variant &variant;
				// long variant_region_index;
				{
					// s_model_variant_region &variant_region;
				}
			}
			{
				// __int32 k;
				{
					// s_model_permutation &permutation;
				}
			}
			{
				// s_model_permutation_possibility &chosen_possibility;
				// long chosen_possibility_index;
				{
					// long j;
					{
						// long k;
						{
							// long permutation_index;
							{
								// s_model_permutation &permutation;
							}
						}
					}
				}
			}
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(s_model_variant_region *, long, long, long, bool, long *, long, s_model_permutation_possibility *)
	// function call : long (*const)(long, s_model_permutation_possibility *)
	todo("implement");
	_sub_10AB8700(model_definition_index, variant_index, region_permutation_indices, region_info, discard_mask, region_permutations, region_permutation_count);
}

_extern long _sub_10AB7CD0(char const *);
long find_player_character_by_name(char const *name) // 0x10AB7CD0
{
	mangled_x86(MANGLED_TODO, "?find_player_character_by_name@@YAJPBD@Z");
	// char const *name;
	// s_game_globals *game_globals;
	{
		// long i;
	}
	todo("implement");
	long __result = _sub_10AB7CD0(name);
	return __result;
}

extern std::string _sub_10AB6C90();
std::string GetCurrentPreferredCharacter() // 0x10AB6C90
{
	mangled_x86(MANGLED_TODO, "?GetCurrentPreferredCharacter@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// procedure flags: nofpo
	// static ...; // 0x10AB7155
	// static ...; // 0x10AB714D
	// static ...; // 0x10AB7148
	// static ...; // 0x10AB7142
	// static ...; // 0x10AB7138
	// static ...; // 0x10AB70FC
	// static ...; // 0x10AB70F4
	// std::string modHash;
	// s_game_globals const *game_globals;
	// bool modIsCharacterType;
	// s_mod_globals_definition const *mod_globals;
	// std::string loadedMod;
	// c_mod_package_manager::s_entry entry;
	// unsigned char hash[20];
	// std::string character;
	{
		// __int32 i;
		{
			// char *currentName;
			{
				// __int32 j;
			}
		}
	}
	// function call : bool (*const)()
	todo("implement");
	std::string __result = _sub_10AB6C90();
	return __result;
}

void clearCachedCharacter() // 0x10AB7C70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?clearCachedCharacter@@YAXXZ");
	// procedure flags: nofpo

	customization_biped_index = -1;
	customization_char_platform_index = -1;
}

extern s_mod_globals_player_character_customization *_sub_10ABB0E0(std::string const &);
s_mod_globals_player_character_customization *try_get_customization_character(std::string const &name) // 0x10ABB0E0
{
	mangled_x86(MANGLED_TODO, "?try_get_customization_character@@YAPAUs_mod_globals_player_character_customization@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// std::string const &name;
	{
		// long character_type_index;
	}
	todo("implement");
	s_mod_globals_player_character_customization * __result = _sub_10ABB0E0(name);
	return __result;
}

_extern long _sub_10ABACB0(long);
long scenario_find_named_object(long name_index) // 0x10ABACB0
{
	mangled_x86(MANGLED_TODO, "?scenario_find_named_object@@YAJJ@Z");
	// static ...; // 0x10ABAD68
	// static ...; // 0x10ABAD5C
	// static ...; // 0x10ABAD54
	// long name_index;
	{
		// c_data_array<s_object_header> *object_headers;
		{
			// c_data_iterator<s_object_header> it;
		}
	}
	todo("implement");
	long __result = _sub_10ABACB0(name_index);
	return __result;
}

_extern long _sub_10ABBC50();
long user_interface_find_model_customization_biped() // 0x10ABBC50
{
	mangled_x86(MANGLED_TODO, "?user_interface_find_model_customization_biped@@YAJXZ");
	// procedure flags: nofpo
	// s_mod_globals_player_character_customization *const character;
	{
		// long object_index;
	}
	todo("implement");
	long __result = _sub_10ABBC50();
	return __result;
}

long user_interface_find_char_platform() // 0x10ABBB40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?user_interface_find_char_platform@@YAJXZ");
	// procedure flags: nofpo
	// s_mod_globals_player_character_customization *const character;

	s_mod_globals_player_character_customization *const character = try_get_customization_character(GetCurrentPreferredCharacter());

	if (character && character->character_position_data.platform_name_index != NONE)
	{
		return scenario_find_named_object(character->character_position_data.platform_name_index);
	}

	return NONE;
}

_extern void _sub_10ABB830(long, long);
void unit_refresh_hologram_appearance_hook(long creator_unit_index, long hologram_unit_index) // 0x10ABB830
{
	mangled_x86(MANGLED_TODO, "?unit_refresh_hologram_appearance_hook@@YAXJJ@Z");
	// long hologram_unit_index;
	{
		// s_object_data *hologram_unit;
		// s_unit_data *creator_unit;
		{
			// s_player_model_customization const *customization;
			// s_player_datum *creator_player;
		}
	}
	todo("implement");
	_sub_10ABB830(creator_unit_index, hologram_unit_index);
}

extern real_rgb_color *_sub_10AB8D00(real_rgb_color *, long);
real_rgb_color *network_get_team_color(real_rgb_color *color, long team) // 0x10AB8D00
{
	mangled_x86(MANGLED_TODO, "?network_get_team_color@@YAPAUreal_rgb_color@@PAU1@J@Z");
	// long team;
	// s_game_globals *matg;
	{
		// s_multiplayer_globals_definition *mulg;
	}
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	real_rgb_color * __result = _sub_10AB8D00(color, team);
	return __result;
}

unsigned char get_character_team_color_override_flags(long character_type_index) // 0x10AB8300
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_character_team_color_override_flags@@YAEJ@Z");
	// long character_type_index;
	// s_mod_globals_definition *modg;
		// __int32 i;

	s_mod_globals_definition *mod_globals = NULL;

	if (character_type_index != -1)
	{
		mod_globals = mod_globals_get_definition();

		if (mod_globals)
		{
			for (long i = 0; i < mod_globals->player_character_customizations.count; i++)
			{
				if (mod_globals->player_character_customizations[i].global_player_character_type_index == character_type_index)
				{
					return *((unsigned char *)&mod_globals->player_character_customizations[i] + 0xd5);
				}
			}
		}
	}

	return 0;
}

unsigned char get_player_team_color_override_flags(long player_index) // 0x10AB85A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_player_team_color_override_flags@@YAEJ@Z");
	// long player_index;
	// unsigned char flags;
		// s_player_datum *player;

	unsigned char flags = 0;
	if (s_player_datum *player = player_get(player_index))
	{
		flags = get_character_team_color_override_flags(player->character_type_index);
	}
	return flags;
}

bool find_player_customized_character_by_name(long player_index, unsigned long character_name) // 0x10AB7E80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?find_player_customized_character_by_name@@YA_NJK@Z");
	// unsigned long character_name;
	// s_player_datum *player;
	// s_player_appearance const &appearance;
		// __int32 i;

	s_player_datum *player = player_get(player_index);
	s_player_appearance const &appearance = player->configuration.host.appearance;

	for (__int32 i = 0; i < appearance.characters_count; i++)
	{
		if (appearance.characters[i].character_name == character_name)
		{
			return true;
		}
	}

	return false;
}

void game_engine_get_player_colors(long player_index, s_player_model_customization const *customization, real_rgb_color *out_colors) // 0x10AB7F30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_get_player_colors@@YAXJPBUs_player_model_customization@@PAUreal_rgb_color@@@Z");
	// real_rgb_color *out_colors;
	// s_player_datum *player;
		// s_game_globals_player_character_type *character_type;
		// long i;
	// function call : real_rgb_color *(*const)(unsigned long, real_rgb_color *)

	s_player_datum *player = player_get(player_index);

	if (player->character_type_index != NONE)
	{
		s_game_globals_player_character_type *character_type = game_globals_get()->player_character_types.get_element(player->character_type_index);

		if (character_type
			&& !find_player_customized_character_by_name(player_index, character_type->name)
			&& Mods::CModGlobals::GetCharacterDefaultColors(player->character_type_index, out_colors))
		{
			return;
		}
	}

	for (long i = 0; i < 5; i++)
	{
		((real_rgb_color *(*)(unsigned long, real_rgb_color *))0x521300)(customization->colors[i], &out_colors[i]);
	}
}

_extern void _sub_10AB8070(long, s_player_model_customization const *, long, real_rgb_color *, bool *);
void game_engine_get_player_colors_hook(long player_index, s_player_model_customization const *customization, long team_index, real_rgb_color *out_colors, bool *custom_colors) // 0x10AB8070
{
	mangled_x86(MANGLED_TODO, "?game_engine_get_player_colors_hook@@YAXJPBUs_player_model_customization@@JPAUreal_rgb_color@@PA_N@Z");
	// bool *custom_colors;
	// s_player_datum *player;
	// unsigned char forced_color_team;
	// unsigned char team_override_flags;
	// s_game_globals *globals;
	{
		// long i;
	}
	{
	}
	// function call : bool (*)()
	// function call : c_game_engine *(*const)()
	// function call : bool (*const)()
	// function call : bool (*const)()
	todo("implement");
	_sub_10AB8070(player_index, customization, team_index, out_colors, custom_colors);
}

_extern long _sub_10ABB170();
long ui_get_player_model_id_hook() // 0x10ABB170
{
	mangled_x86(MANGLED_TODO, "?ui_get_player_model_id_hook@@YAJXZ");
	// procedure flags: nofpo
	// static ...; // 0x10ABB454
	// static ...; // 0x10ABB448
	// static ...; // 0x10ABB440
	// std::string preferredCharacterName;
	// s_game_globals *matg;
	// s_mod_globals_definition *modg;
	{
		// __int32 i;
		{
			// s_game_globals_player_character_type &player_representation_block;
			// __int32 rep_index;
		}
	}
	// function call : long (*const)(unsigned long)
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	long __result = _sub_10ABB170();
	return __result;
}

_extern void _sub_10AB9BC0();
void player_model_patches_apply() // 0x10AB9BC0
{
	mangled_x86(MANGLED_TODO, "?player_model_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	// Modules::ModuleGame &gameModule;
	// Modules::ModulePlayer &playerModule;
	todo("implement");
	_sub_10AB9BC0();
}

void RefreshUiPlayer() // 0x10AB7390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RefreshUiPlayer@@YAXXZ");
	// procedure flags: nofpo

	updateUiPlayerArmor = true;
}

__declspec(naked) void PoseWithWeapon(unsigned __int32 unit, unsigned __int32 weaponTag) // 0x10AB7370
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PoseWithWeapon@@YAXII@Z");
	// unsigned __int32 weaponTag;

	__asm
	{
		push ebp
		mov ebp, esp
		sub esp, 18Ch
		push esi
		push edi
		sub esp, 8
		mov esi, [ebp + 8]
		mov edi, [ebp + 0Ch]
		push 7B77DAh
		ret
	}
}

_extern __int32 _sub_10AB96A0(__int32, char const *, char const *);
__int32 player_model_get_region_permutation(__int32 player_model_index, char const *region_name, char const *permutation_name) // 0x10AB96A0
{
	mangled_x86(MANGLED_TODO, "?player_model_get_region_permutation@@YAHHPBD0@Z");
	// static ...; // 0x10AB9A94
	// static ...; // 0x10AB9A88
	// static ...; // 0x10AB9A58
	// static ...; // 0x10AB9A50
	// __int32 player_model_index;
	// char const *region_name;
	// char const *permutation_name;
	// bool is_default;
	// s_game_globals *matg;
	// s_model_customization_selection *customization;
	// s_multiplayer_globals_definition *mulg;
	// s_game_globals_player_character_type *character;
	{
		// __int32 i;
		{
			// bool region_found;
			// s_model_customization_player_region *region;
			{
				// __int32 perm_index;
				{
					// s_model_customization_player_region_permutation *permutation;
					// char *perm_name;
				}
			}
		}
	}
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	__int32 __result = _sub_10AB96A0(player_model_index, region_name, permutation_name);
	return __result;
}

_extern void _sub_10ABB530(long, long);
void unit_copy_player_appearance(long source_player_unit_index, long target_unit_index) // 0x10ABB530
{
	mangled_x86(MANGLED_TODO, "?unit_copy_player_appearance@@YAXJJ@Z");
	// static ...; // 0x10ABB780
	// static ...; // 0x10ABB768
	// static ...; // 0x10ABB760
	// long source_player_unit_index;
	// long target_unit_index;
	// char (*const set_object_base_change_color_by_index)(long, long, real_rgb_color const *);
	// void (*const object_set_initial_change_colors)(long, __int32, real_rgb_color const *);
	// long (*const game_engine_get_change_colors)(long, s_player_model_customization const *, long, real_rgb_color *, bool *);
	// void (*const object_apply_change_colors)(long);
	{
		// s_unit_data *player_unit_object;
		{
			// s_unit_data *target_unit;
			{
				// real_rgb_color colors[5];
				// s_player_model_customization const *customization;
				// bool custom_colors;
				// s_player_datum *source_player;
				{
					// long i;
				}
			}
		}
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : long (*const)(long, s_player_model_customization const *, long, real_rgb_color *, bool *)
	// function call : char (*const)(long, long, real_rgb_color const *)
	// function call : void (*const)(long, __int32, real_rgb_color const *)
	// function call : void (*const)(long)
	todo("implement");
	_sub_10ABB530(source_player_unit_index, target_unit_index);
}

_extern unsigned char _sub_10AB93E0(char const *);
unsigned char player_model_get_index(char const *name) // 0x10AB93E0
{
	mangled_x86(MANGLED_TODO, "?player_model_get_index@@YAEPBD@Z");
	// char const *name;
	// s_game_globals *matg;
	// s_mod_globals_definition *modg;
	{
		// __int32 i;
		{
			// char *character_name;
			// s_game_globals_player_character_type &player_representation_block;
			// __int32 &rep_index;
			// s_mod_globals_player_character_customization &character_customization_block;
		}
	}
	// function call : long (*const)(unsigned long)
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	unsigned char __result = _sub_10AB93E0(name);
	return __result;
}

_extern void _sub_10AB68E0(long, s_player_model_customization const *);
void CustomizeObjectColors(long objectIndex, s_player_model_customization const *customization) // 0x10AB68E0
{
	mangled_x86(MANGLED_TODO, "?CustomizeObjectColors@@YAXJPBUs_player_model_customization@@@Z");
	// static ...; // 0x10AB6ABC
	// static ...; // 0x10AB6AB4
	// long objectIndex;
	// s_player_model_customization const *customization;
	// constexpr void (*const `CustomizeObjectColors'::`2'::UpdateArmorColors)(unsigned __int32); // constant == 5910432
	// s_object_data *object;
	// constexpr void (*const `CustomizeObjectColors'::`2'::ApplyArmor)(s_player_model_customization *, unsigned __int32); // constant == 5915696
	// constexpr void (*const `CustomizeObjectColors'::`2'::ApplyArmorColor)(unsigned __int32, __int32, float *); // constant == 11741424
	{
		// __int32 i;
		{
			// float colorData[3];
			{
				// __int32 j;
			}
		}
	}
	{
		// long child_index;
		{
			// s_object_data *child_object;
		}
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(unsigned __int32, __int32, float *)
	// function call : void (*const)(unsigned __int32)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	_sub_10AB68E0(objectIndex, customization);
}

_extern void _sub_10AB63E0();
void CustomizeBipeds() // 0x10AB63E0
{
	mangled_x86(MANGLED_TODO, "?CustomizeBipeds@@YAXXZ");
	// procedure flags: nofpo
	// static ...; // 0x10AB67CD
	// static ...; // 0x10AB67BF
	// static ...; // 0x10AB67BC
	// static ...; // 0x10AB6798
	// static ...; // 0x10AB6790
	// constexpr void (*const `CustomizeBipeds'::`2'::UpdateArmorColors)(unsigned __int32); // constant == 5910432
	// s_game_globals *matg;
	// s_mod_globals_definition *modg;
	// constexpr void (*const `CustomizeBipeds'::`2'::ApplyArmor)(s_player_model_customization *, unsigned __int32); // constant == 5915696
	// constexpr void (*const `CustomizeBipeds'::`2'::ApplyArmorColor)(unsigned __int32, __int32, float *); // constant == 11741424
	{
		// __int32 i;
		{
			// char *character_name;
			// unsigned __int32 bipedObject;
			// c_data_array<s_object_header> *object_headers;
			// s_player_model_customization customization;
			// __int32 rep_index;
			// __int32 character_index;
			// s_mod_globals_player_character_customization *character;
			{
				// c_data_iterator<s_object_header> it;
			}
		}
	}
	// function call : long (*const)(unsigned long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(s_player_model_customization *, unsigned __int32)
	todo("implement");
	_sub_10AB63E0();
}

_extern void _sub_10ABB920();
void update_customization_biped() // 0x10ABB920
{
	mangled_x86(MANGLED_TODO, "?update_customization_biped@@YAXXZ");
	// procedure flags: nofpo
	// static ...; // 0x10ABBACB
	// static ...; // 0x10ABBAC8
	// static ...; // 0x10ABBAB0
	// static ...; // 0x10ABBAA8
	// void (*const object_get_orientation)(long, real_vector3d *, real_vector3d *);
	// void (*const object_queue_render_thread_message)(long, short, long);
	{
		// real_vector3d forward;
		// float angle_radians;
		// real_vector3d up;
	}
	// function call : void (*const)(long, real_vector3d *, real_vector3d *)
	// function call : void (*const)(unsigned long, real_point3d *, real_vector3d *, real_vector3d *, s_scenario_location *)
	// function call : void (*const)(unsigned long, real_point3d *, real_vector3d *, real_vector3d *, s_scenario_location *)
	// function call : void (*const)(long, short, long)
	todo("implement");
	_sub_10ABB920();
}

_extern void _sub_10ABADC0();
void set_customization_bipeds() // 0x10ABADC0
{
	mangled_x86(MANGLED_TODO, "?set_customization_bipeds@@YAXXZ");
	// procedure flags: nofpo
	// static ...; // 0x10ABAF60
	// static ...; // 0x10ABAF54
	// static ...; // 0x10ABAF4C
	// std::vector<int> characterBipeds;
	// s_mod_globals_definition *modg;
	{
		// __int32 i;
		{
			// s_mod_globals_player_character_customization *character;
			{
				// long object_index;
			}
		}
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	_sub_10ABADC0();
}

_extern void _sub_10AB7470();
void UpdateUiPlayerModelArmor() // 0x10AB7470
{
	mangled_x86(MANGLED_TODO, "?UpdateUiPlayerModelArmor@@YAXXZ");
	// procedure flags: nofpo
	// static ...; // 0x10AB7876
	// static ...; // 0x10AB7873
	// static ...; // 0x10AB786B
	// static ...; // 0x10AB7868
	// static ...; // 0x10AB7838
	// static ...; // 0x10AB7830
	// void (*const object_get_orientation)(long, real_vector3d *, real_vector3d *);
	// void (*const Object_SetTransform)(__int32, real_vector3d *, real_vector3d *, real_vector3d *, __int32);
	{
		// real_vector3d forward;
		// real_vector3d up;
	}
	{
		// float d;
		// float t;
		{
			// float c;
			// float b;
		}
	}
	{
		// float angle_radians;
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, real_vector3d *, real_vector3d *)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : float (*const)(float)
	// function call : void (*const)(long, real_vector3d *, real_vector3d *)
	// function call : void (*const)(__int32, real_vector3d *, real_vector3d *, real_vector3d *, __int32)
	todo("implement");
	_sub_10AB7470();
}

bool CharacterHasFlag(__int32 flag) // 0x10AB63A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CharacterHasFlag@@YA_NH@Z");
	// __int32 flag;

	if ((1 << flag) & customization_biped_flags)
	{
		return true;
	}

	return false;
}

void SetUiPlayerModelPosition(real_vector3d const *newPosition) // 0x10AB73B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetUiPlayerModelPosition@@YAXPBUreal_vector3d@@@Z");
	// real_vector3d const *newPosition;

	*(real_vector3d *)s_UiPlayerModelState.Position = *newPosition;
	s_UiPlayerModelState.Flags |= 2;
}

void SetUiPlayerModelRotation(float angleDegrees, float seconds) // 0x10AB7400
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetUiPlayerModelRotation@@YAXMM@Z");
	// float seconds;

	s_UiPlayerModelState.StartRotationAngle = customzation_biped_angle_degrees;
	s_UiPlayerModelState.EndRotationAngle = angleDegrees;
	s_UiPlayerModelState.RotationTicks = 0;
	s_UiPlayerModelState.RotationDuration = seconds;
	s_UiPlayerModelState.Flags |= 1;
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool s_static_array<s_model_customization_region_permutation,16>::valid(__int32);
template s_game_globals_player_character_type * c_tag_block<s_game_globals_player_character_type>::begin();
template s_game_globals_player_character_type * c_tag_block<s_game_globals_player_character_type>::end();
template s_model_customization_player_region & c_tag_block<s_model_customization_player_region>::operator[](__int32);
template s_model_customization_player_region_permutation & c_tag_block<s_model_customization_player_region_permutation>::operator[](__int32);
template s_model_customization_region_permutation & c_tag_block<s_model_customization_region_permutation>::operator[](__int32);
template s_model_customization_region_permutation & s_static_array<s_model_customization_region_permutation,16>::operator[](long);
template s_model_customization_region_permutation * s_static_array<s_model_customization_region_permutation,16>::get_elements();
template s_model_variant & c_tag_block<s_model_variant>::operator[](__int32);
template s_model_variant_region & c_tag_block<s_model_variant_region>::operator[](__int32);
template s_multiplayer_universal_globals_definition & c_tag_block<s_multiplayer_universal_globals_definition>::operator[](__int32);
template void s_static_array<s_model_customization_region_permutation,16>::set_memory(unsigned char);
