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

#include "Blam/Cache/StringIdCache.hpp"  // hades: added for 0x10AB63E0

#include "mods/mod_system.hpp"  // hades: added for 0x10AB6C90  // hades: added for 0x10AB6C90

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

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const current_game_engine = reinterpret_cast<c_game_engine *(*)()>(0x5CE150);
	static auto const game_engine_has_teams = reinterpret_cast<bool (*)()>(0x5565E0);
	static auto const game_in_progress = reinterpret_cast<bool (*)()>(0x5314B0);
}
#line 183

extern float angle_between_vectors3d(real_vector3d const *v1, real_vector3d const *v2);  // hades: added for 0x10AB7470
extern float (*const game_ticks_to_seconds)(float);  // hades: added for 0x10AB7470

extern void (*const object_choose_initial_permutation)(long, unsigned long, s_model_customization_region_permutation const *, long);  // hades: added for 0x10ABAA80

extern void (*const object_set_position)(unsigned long, real_point3d *, real_vector3d *, real_vector3d *, s_scenario_location *);  // hades: added for 0x10ABB920

extern void render_patches_set_customization_biped(std::vector<int> characterBipeds);  // hades: added for 0x10ABADC0

template<typename t_arg0> static t_arg0 *object_get(unsigned long object_index) { return (t_arg0 *)object_get(object_index); }  // hades: a file-local template in the original (undecorated `object_get<T>`), defined so it is emitted;  // hades: added for 0x10ABB830

extern bool (*game_is_campaign)();  // hades: added for 0x10AB8070
extern bool (*const game_is_multiplayer)();  // hades: added for 0x10AB8070
#include "Modules/ModuleCampaign.hpp"  // hades: added for 0x10AB8070

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0x10AB8400

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

static s_game_globals *try_and_get_game_globals() // 0x10ABB040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?try_and_get_game_globals@@YAPAUs_game_globals@@XZ");

	return (s_game_globals *)tag_get(0x6D617467, tag_get_first_in_group(0x6D617467));
}

long get_multiplayer_player_model_customization_block_index(long unit_index) // 0x10AB8400
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_multiplayer_player_model_customization_block_index@@YAJJ@Z");

	s_game_globals *game_globals = game_globals_get();
	s_unit_data *unit_object = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003);
	if (!unit_object)
		return -1;
	for (s_game_globals_player_character_type &character_type : game_globals->player_character_types)
	{
		long player_representation_index = character_type.multiplayer_player_representation_block_index;
		s_game_globals_player_representation *player_representation;
		if (game_globals->PlayerRepresentation.try_get_element(player_representation_index, &player_representation) && player_representation->ThirdPersonUnit.index == unit_object->definition_index)
			return character_type.multiplayer_armor_customization_block_index;
	}
	return 0;
}

s_player_model_customization const *player_get_model_customization(s_player_datum *player) // 0x10AB8E10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_get_model_customization@@YAPBUs_player_model_customization@@PAUs_player_datum@@@Z");

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

void player_refresh_object_appearance_full_hook(long player_index, long object_index) // 0x10ABA680
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_refresh_object_appearance_full_hook@@YAXJJ@Z");

	long (*const game_engine_get_change_colors)(long, s_player_model_customization const *, long, real_rgb_color *, bool *) = reinterpret_cast<long (*)(long, s_player_model_customization const *, long, real_rgb_color *, bool *)>(0x54F250);
	void (*const object_apply_change_colors)(long) = reinterpret_cast<void (*)(long)>(0x5A2FA0);
	void (*const object_set_initial_change_colors)(long, __int32, real_rgb_color const *) = reinterpret_cast<void (*)(long, __int32, real_rgb_color const *)>(0xB32F20);
	char (*const set_object_base_change_color_by_index)(long, long, real_rgb_color const *) = reinterpret_cast<char (*)(long, long, real_rgb_color const *)>(0xB328F0);
	s_player_datum *player = player_get(player_index);
	s_object_data *object = object_get(object_index);
	if ((1 << (char)object->object_identifier.type) & 0x2003)
	{
		s_unit_data *unit = (s_unit_data *)object;
		unit->team = player->configuration.host.team;
	}
	long team_index = 0;
	if (game_is_multiplayer())
	{
		if (((bool (*)())0x5565E0)())
			team_index = player->configuration.host.team;
		else
			team_index = -1;
	}
	s_player_model_customization const *customization = player_get_model_customization(player);
	real_rgb_color colors[5];
	bool custom_colors = false;
	game_engine_get_change_colors(player_index, customization, team_index, colors, &custom_colors);
	if (custom_colors)
	{
		for (long i = 0; i < 5; i++)
			set_object_base_change_color_by_index(object_index, i, &colors[i]);
	}
	else
	{
		object_set_initial_change_colors(object_index, 0, nullptr);
	}
	if (object->object_identifier.type == _object_type_biped)
		object_apply_change_colors(object_index);
	{
		long child_index = object->first_child_object_index;
		while (child_index != -1)
		{
			s_object_data *child_object = object_try_and_get_and_verify_type(child_index, -1);
			if (!child_object)
				break;
			if (child_object->child_variant_index != -1)
				player_refresh_object_appearance_full_hook(player_index, child_index);
			child_index = child_object->next_object_index;
		}
	}
}

void recreate_child_objects_for_customization(long object_index, long region_discard_mask, s_model_customization_region_permutation *region_permutations, long region_permutations_count) // 0x10ABAA80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?recreate_child_objects_for_customization@@YAXJJPAUs_model_customization_region_permutation@@J@Z");

	void (*const object_delete_immediately)(long) = reinterpret_cast<void (*)(long)>(0xB2CF40);
	void (*const object_create_children)(long) = reinterpret_cast<void (*)(long)>(0xB2C980);
	void (*const object_detach)(long) = reinterpret_cast<void (*)(long)>(0xB2D180);
	s_unit_data *object = (s_unit_data *)object_try_and_get_and_verify_type(object_index, -1);
	if (!object)
		return;
	long child_index = object->first_child_object_index;
	while (child_index != -1)
	{
		s_object_data *child_object = object_try_and_get_and_verify_type(child_index, -1);
		if (!child_object)
			break;
		long next_index = child_object->next_object_index;
		if (child_object->child_variant_index != -1)
			object_delete_immediately(child_index);
		child_index = next_index;
	}
	object_create_children(object_index);
	{
		long child_index = object->first_child_object_index;
		while (child_index != -1)
		{
			s_object_data *child_object = object_try_and_get_and_verify_type(child_index, -1);
			if (!child_object)
				break;
			if (child_object->child_variant_index != -1)
				object_choose_initial_permutation(child_index, region_discard_mask, region_permutations, region_permutations_count);
			child_index = child_object->next_object_index;
		}
	}
}

#line 456
void player_model_customize(s_player_model_customization const *customization_data, long unit_index) // 0x10AB8F00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_model_customize@@YAXPBUs_player_model_customization@@J@Z");
#line 483

	if (game_is_campaign() && Modules::ModuleCampaign::Instance().VarPlayerRepresentationEnabledClient->ValueInt)
		return;
	s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003);
	if (!unit)
		return;
	long customize_from_unit_index = unit_index;
	if (unit->hologram_creator_weak_unit_index != -1)
	{
		customize_from_unit_index = unit->hologram_creator_weak_unit_index;
		if (!object_try_and_get_and_verify_type(customize_from_unit_index, 0x2003))
			return;
	}
	long player_model_index = get_multiplayer_player_model_customization_block_index(customize_from_unit_index);
	s_game_globals *globals_definition = try_and_get_game_globals();
	#line 477 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
		assert(globals_definition);
		#line 501 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
	s_multiplayer_globals_definition *multiplayer_globals_definition = (s_multiplayer_globals_definition *)tag_get('mulg', globals_definition->MultiplayerGlobals.index);
	s_multiplayer_universal_globals_definition *universal_globals = &multiplayer_globals_definition->universal[0];
	if (player_model_index < 0 || player_model_index >= universal_globals->player_model.count)
		return;
	s_model_customization_selection *selected_model = &universal_globals->player_model[player_model_index];
	s_static_array<s_model_customization_region_permutation, 16> region_permutations;
	region_permutations.set_memory(0);
	long region_permutation_count = 0;
	unsigned long region_discard_mask = 0;
	for (__int32 region_index = 0; region_index < 16; region_index++)
	{
		if (region_index >= selected_model->regions.count)
			continue;
		s_model_customization_player_region *region = &selected_model->regions[region_index];
		char permutation_index = customization_data->armor_section_indices[region_index];
		if (permutation_index == -1)
			continue;
		s_model_customization_player_region_permutation *permutation = &region->permutations[permutation_index];
		if (permutation_index >= region->permutations.count)
			continue;
		for (__int32 variant_index = 0; variant_index < permutation->variants.count; variant_index++)
			region_permutations[region_permutation_count++] = permutation->variants[variant_index];
	}
	object_choose_initial_permutation(unit_index, region_discard_mask, region_permutations.get_elements(), region_permutation_count);
	recreate_child_objects_for_customization(unit_index, region_discard_mask, region_permutations.get_elements(), region_permutation_count);
}

void model_permutation_possibility_set(long permutation_index, s_model_permutation_possibility *possibility) // 0x10AB8690
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?model_permutation_possibility_set@@YAXJPAUs_model_permutation_possibility@@@Z");

	possibility->runtime_permutation_index = permutation_index;
	possibility->variant_permutation_index = -1;
	possibility->state = 0;
	possibility->property_flags = 0;
	possibility->looping_effect_index = -1;
	possibility->looping_effect_marker = 0;
	possibility->probability = 1.0f;
}

void model_select_initial_permutation(long model_definition_index, long variant_index, unsigned char *region_permutation_indices, s_object_region_information *region_info, unsigned long discard_mask, s_model_customization_region_permutation *region_permutations, long region_permutation_count) // 0x10AB8700
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?model_select_initial_permutation@@YAXJJPAEPAUs_object_region_information@@KPAUs_model_customization_region_permutation@@J@Z");

	void (*const model_find_permutation_possibilities)(s_model_variant_region *, long, long, long, bool, long *, long, s_model_permutation_possibility *) = (void (*)(s_model_variant_region *, long, long, long, bool, long *, long, s_model_permutation_possibility *))0x6D9640;
	long (*const model_select_permutation_possibility)(long, s_model_permutation_possibility *) = (long (*)(long, s_model_permutation_possibility *))0x6DA070;
	s_model_definition *model = (s_model_definition *)tag_get('hlmt', model_definition_index);
	for (__int32 i = 0; i < model->runtime_regions.count; i++)
	{
		region_permutation_indices[i] = 0xFF;
		region_info[i].variant_permutation_index = -1;
		region_info[i].state = 0;
		region_info[i].property_flags = 0;
		region_info->unknown_index = -1;
	}
	s_model_permutation_possibility possibilities[128];
	for (long region_index = 0; region_index < model->runtime_regions.count; region_index++)
	{
		long possibility_count = 0;
		s_model_region &region = model->runtime_regions[region_index];
		if (variant_index != -1)
		{
			s_model_variant &variant = model->variants[variant_index];
			long variant_region_index = variant.region_indices[region_index];
			if (variant_region_index != -1)
			{
				s_model_variant_region &variant_region = variant.regions[variant_region_index];
				model_find_permutation_possibilities(&variant_region, -1, 0, 0, true, &possibility_count, 128, possibilities);
			}
		}
		if (possibility_count == 0)
		{
			for (__int32 k = 0; k < region.permutations.count; k++)
			{
				s_model_permutation &permutation = region.permutations[k];
				if (!(permutation.flags & 1))
					model_permutation_possibility_set(k, &possibilities[possibility_count++]);
			}
			if (possibility_count == 0 && region.permutations.count > 0)
				model_permutation_possibility_set(0, &possibilities[possibility_count++]);
		}
		if (!((1 << region_index) & discard_mask))
		{
			long chosen_possibility_index = -1;
			for (long j = 0; j < region_permutation_count; j++)
			{
				if (region.name == region_permutations[j].region_name)
				{
					for (long k = 0; k < possibility_count; k++)
					{
						long permutation_index = possibilities[k].runtime_permutation_index;
						if (permutation_index != -1)
						{
							s_model_permutation &permutation = region.permutations[permutation_index];
							if (permutation.name == region_permutations[j].permutation_name)
							{
								chosen_possibility_index = k;
								break;
							}
						}
					}
					break;
				}
			}
			if (chosen_possibility_index == -1)
				chosen_possibility_index = model_select_permutation_possibility(possibility_count, possibilities);
			s_model_permutation_possibility &chosen_possibility = possibilities[chosen_possibility_index];
			region_permutation_indices[region_index] = (unsigned char)chosen_possibility.runtime_permutation_index;
			region_info[region_index].variant_permutation_index = (char)chosen_possibility.variant_permutation_index;
			region_info[region_index].property_flags = (unsigned char)chosen_possibility.property_flags;
			region_info[region_index].state = chosen_possibility.state;
		}
	}
}

long find_player_character_by_name(char const *name) // 0x10AB7CD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?find_player_character_by_name@@YAJPBD@Z");

	s_game_globals *game_globals = game_globals_get();
	for (long i = 0; i < game_globals->player_character_types.count; i++)
	{
		if (strcmp(Blam::Cache::StringIDCache::GetCurrent()->GetString(game_globals->player_character_types[i].name), name) == 0)
			return i;
	}
	return -1;
}

std::string GetCurrentPreferredCharacter() // 0x10AB6C90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetCurrentPreferredCharacter@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");

	if (!eldorado::game_in_progress())
		return "";
	std::string loadedMod = c_mod_system::get_current_package_filename(kMainMenu);
	std::string modHash = c_mod_system::get_current_mainmenu_package_hash();
	s_game_globals const *game_globals = game_globals_get();
	s_mod_globals_definition const *mod_globals = mod_globals_get_definition();
	bool modIsCharacterType = false;
	unsigned char hash[20];
	Utils::String::HexStringToBytes(modHash, hash, sizeof(hash));
	c_mod_package_manager::s_entry entry;
	if (c_mod_system::get_package_manager().find_package_by_hash(hash, &entry))
		modIsCharacterType = entry.modtype.character;
	if (loadedMod.empty() || (!loadedMod.empty() && !modIsCharacterType))
		loadedMod = "default";
	std::string character = Utils::Singleton<Player::CPlayerCustomizationDB>::Instance().GetPreferredCharacter(loadedMod);
	for (__int32 i = 0; i < game_globals->player_character_types.count; i++)
	{
		char *currentName = Blam::Cache::StringIDCache::GetCurrent()->GetString(game_globals->player_character_types[i].name);
		if ((char)game_globals->player_character_types[i].multiplayer_armor_customization_block_index == -1)
			continue;
		if (strcmp(currentName, character.c_str()) == 0)
		{
			for (__int32 j = 0; j < mod_globals->player_character_customizations.count; j++)
			{
				if (mod_globals->player_character_customizations[j].global_player_character_type_index == i)
					return character;
			}
		}
	}
	return Blam::Cache::StringIDCache::GetCurrent()->GetString(game_globals->player_character_types[mod_globals->player_character_customizations[0].global_player_character_type_index].name);
}

void clearCachedCharacter() // 0x10AB7C70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?clearCachedCharacter@@YAXXZ");

	customization_biped_index = -1;
	customization_char_platform_index = -1;
}

s_mod_globals_player_character_customization *try_get_customization_character(std::string const &name) // 0x10ABB0E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?try_get_customization_character@@YAPAUs_mod_globals_player_character_customization@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

	if (!name.empty())
	{
		long character_type_index = find_player_character_by_name(name.c_str());
		if (character_type_index != -1)
			return Mods::CModGlobals::GetCustomizationCharacter(character_type_index);
	}
	return nullptr;
}

long scenario_find_named_object(long name_index) // 0x10ABACB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?scenario_find_named_object@@YAJJ@Z");

	if (name_index != -1)
	{
		c_data_array<s_object_header> *object_headers = object_headers_get();
		for (c_data_iterator<s_object_header> it = object_headers->begin(); it != object_headers->end(); ++it)
		{
			if (name_index == it->data->name_index)
				return it.current_datum_index;
		}
	}
	return -1;
}

long user_interface_find_model_customization_biped() // 0x10ABBC50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?user_interface_find_model_customization_biped@@YAJXZ");

	s_mod_globals_player_character_customization *const character = try_get_customization_character(GetCurrentPreferredCharacter());
	if (character && character->character_position_data.biped_name_index != -1)
	{
		long object_index = scenario_find_named_object(character->character_position_data.biped_name_index);
		if (object_index != -1)
		{
			customization_biped_flags = character->character_position_data.flags;
			return object_index;
		}
	}
	customization_biped_flags = 0;
	return -1;
}

long user_interface_find_char_platform() // 0x10ABBB40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?user_interface_find_char_platform@@YAJXZ");

	s_mod_globals_player_character_customization *const character = try_get_customization_character(GetCurrentPreferredCharacter());

	if (character && character->character_position_data.platform_name_index != NONE)
	{
		return scenario_find_named_object(character->character_position_data.platform_name_index);
	}

	return NONE;
}

void unit_refresh_hologram_appearance_hook(long creator_unit_index, long hologram_unit_index) // 0x10ABB830
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_refresh_hologram_appearance_hook@@YAXJJ@Z");

	if (creator_unit_index != -1 && hologram_unit_index != -1)
	{
		s_unit_data *creator_unit = object_get<s_unit_data>(creator_unit_index);
		s_object_data *hologram_unit = object_get(hologram_unit_index);
		if (hologram_unit && creator_unit && creator_unit->player_index != -1)
		{
			hologram_unit->variant_index = creator_unit->variant_index;
			s_player_datum *creator_player = player_get(creator_unit->player_index);
			s_player_model_customization const *customization = player_get_model_customization(creator_player);
			player_model_customize(customization, hologram_unit_index);
		}
	}
}

static real_rgb_color *network_get_team_color(real_rgb_color *color, long team) // 0x10AB8D00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?network_get_team_color@@YAPAUreal_rgb_color@@PAU1@J@Z");

	*color = **reinterpret_cast<real_rgb_color **>(0x189CDBC);
	s_game_globals *matg = try_and_get_game_globals();
	if (matg)
	{
		s_multiplayer_globals_definition *mulg = (s_multiplayer_globals_definition *)tag_get('mulg', matg->MultiplayerGlobals.index);
		if (mulg && team >= 0 && team < mulg->universal->team_colors.count)
		{
			*color = mulg->universal->team_colors[team].color;
		}
	}

	return color;
}

unsigned char get_character_team_color_override_flags(long character_type_index) // 0x10AB8300
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_character_team_color_override_flags@@YAEJ@Z");

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

void game_engine_get_player_colors_hook(long player_index, s_player_model_customization const *customization, long team_index, real_rgb_color *out_colors, bool *custom_colors) // 0x10AB8070
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_get_player_colors_hook@@YAXJPBUs_player_model_customization@@JPAUreal_rgb_color@@PA_N@Z");

	if (game_is_campaign() && !Modules::ModuleCampaign::Instance().VarPlayerRepresentationEnabledClient->ValueInt && player_index != -1)
	{
		*custom_colors = true;
		game_engine_get_player_colors(player_index, customization, out_colors);
		return;
	}
	if (!eldorado::current_game_engine() || !game_is_multiplayer() || player_index == -1)
	{
		*custom_colors = false;
		return;
	}
	s_player_datum *player = player_get(player_index);
	s_game_globals *globals = game_globals_get();
	if (globals && player && player->character_type_index != -1 && globals->player_character_types.count > player->character_type_index && (char)globals->player_character_types[player->character_type_index].multiplayer_armor_customization_block_index == -1)
	{
		*custom_colors = false;
		return;
	}
	*custom_colors = true;
	game_engine_get_player_colors(player_index, customization, out_colors);
	unsigned char team_override_flags = get_player_team_color_override_flags(player_index);
	if (eldorado::game_engine_has_teams())
	{
		for (long i = 0; i < 5; i++)
		{
			if ((team_override_flags >> i) & 1)
				network_get_team_color(&out_colors[i], team_index);
		}
	}
	unsigned char forced_color_team = player->traits.appearance.forced_color - 2;
	if (forced_color_team <= 11)
	{
		for (long i = 0; i < 5; i++)
		{
			if ((team_override_flags >> i) & 1)
				network_get_team_color(&out_colors[i], forced_color_team);
		}
	}
}

#line 991
long ui_get_player_model_id_hook() // 0x10ABB170
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ui_get_player_model_id_hook@@YAJXZ");
#line 1006

	std::string preferredCharacterName = GetCurrentPreferredCharacter();
	s_game_globals *matg = try_and_get_game_globals();
	#line 996 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
		assert(matg);
		#line 1012 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
	s_mod_globals_definition *modg = (s_mod_globals_definition *)tag_get('modg', tag_get_first_in_group('modg'));
	#line 999 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
		assert(modg);
		#line 1016 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
	#line 1001 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
		assert(matg->player_character_types.count > 0);
		#line 1019 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
	if (preferredCharacterName.c_str())
	{
		for (__int32 i = 0; i < modg->player_character_customizations.count; i++)
		{
			__int32 rep_index = modg->player_character_customizations[i].global_player_character_type_index;
			if (rep_index < 0 || rep_index >= matg->player_character_types.count)
				continue;
			s_game_globals_player_character_type &player_representation_block = matg->player_character_types[rep_index];
			if (!strcmp(preferredCharacterName.c_str(), Blam::Cache::StringIDCache::GetCurrent()->GetString(player_representation_block.name)))
				return i;
		}
	}
	return -1;
}

void player_model_patches_apply() // 0x10AB9BC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_model_patches_apply@@YAXXZ");

	Hook(0x1A4430, player_model_customize).Apply();
	Hook(0x73E470, unit_refresh_hologram_appearance_hook).Apply();
	Hook(0x7B5BD0, user_interface_find_model_customization_biped).Apply();
	Hook(0x7B5F00, update_customization_biped).Apply();
	Hook(0x2EF10, network_get_team_color).Apply();
	Hook(0x14F250, game_engine_get_player_colors_hook).Apply();
	Hook(0x136000, player_get_model_customization).Apply();
	Hook(0x136020, player_get_model_customization).Apply();
	Hook(0x2351E0, ui_get_player_model_id_hook).Apply();
	Hook(0x2D9DE0, model_select_initial_permutation).Apply();
	Hook(0x138ED0, player_refresh_object_appearance_full_hook).Apply();
	Modules::ModulePlayer &playerModule = Modules::ModulePlayer::Instance();
	Modules::ModuleGame &gameModule = Modules::ModuleGame::Instance();
	Modules::CommandMap::Instance().OnVariableUpdate([&gameModule](Modules::Command const *command)
	{
		if (command == gameModule.VarMainMenuMod)
			clearCachedCharacter();
	});
}

void RefreshUiPlayer() // 0x10AB7390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RefreshUiPlayer@@YAXXZ");

	updateUiPlayerArmor = true;
}

__declspec(naked) void PoseWithWeapon(unsigned __int32 unit, unsigned __int32 weaponTag) // 0x10AB7370
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PoseWithWeapon@@YAXII@Z");

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

#line 1089
__int32 player_model_get_region_permutation(__int32 player_model_index, char const *region_name, char const *permutation_name) // 0x10AB96A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_model_get_region_permutation@@YAHHPBD0@Z");
#line 1111

	s_game_globals_player_character_type *character = nullptr;
	s_model_customization_selection *customization = nullptr;
	s_game_globals *matg = try_and_get_game_globals();
	#line 1095 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
		assert(matg);
		#line 1118 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
	s_multiplayer_globals_definition *mulg = (s_multiplayer_globals_definition *)tag_get('mulg', matg->MultiplayerGlobals.index);
	if (!mulg)
		return 0;
	if (!matg->player_character_types.try_get_element(player_model_index, &character) || !character)
		return 0;
	if (!mulg->universal->player_model.try_get_element(character->multiplayer_armor_customization_block_index, &customization) || !customization)
		return 0;
	bool is_default = !strcmp(permutation_name, "default");
	for (__int32 i = 0; i < customization->regions.count; i++)
	{
		s_model_customization_player_region *region = nullptr;
		if (!customization->regions.try_get_element(i, &region) || !region)
			continue;
		bool region_found = !strcmp(region_name, Blam::Cache::StringIDCache::GetCurrent()->GetString(region->name));
		if (!region_found)
			continue;
		for (__int32 perm_index = 0; perm_index < region->permutations.count; perm_index++)
		{
			s_model_customization_player_region_permutation *permutation = nullptr;
			if (!region->permutations.try_get_element(perm_index, &permutation) || !permutation)
				continue;
			if (!permutation->variants.count)
			{
				if (!is_default)
					continue;
				return perm_index;
			}
			char *perm_name = Blam::Cache::StringIDCache::GetCurrent()->GetString(permutation->variants->permutation_name);
			if (!strcmp(permutation_name, perm_name))
				return perm_index;
		}
		if (region_found)
			break;
	}
	return 0;
}

void unit_copy_player_appearance(long source_player_unit_index, long target_unit_index) // 0x10ABB530
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_copy_player_appearance@@YAXJJ@Z");

	long (*const game_engine_get_change_colors)(long, s_player_model_customization const *, long, real_rgb_color *, bool *) = reinterpret_cast<long (*)(long, s_player_model_customization const *, long, real_rgb_color *, bool *)>(0x54F250);
	void (*const object_apply_change_colors)(long) = reinterpret_cast<void (*)(long)>(0x5A2FA0);
	void (*const object_set_initial_change_colors)(long, __int32, real_rgb_color const *) = reinterpret_cast<void (*)(long, __int32, real_rgb_color const *)>(0xB32F20);
	char (*const set_object_base_change_color_by_index)(long, long, real_rgb_color const *) = reinterpret_cast<char (*)(long, long, real_rgb_color const *)>(0xB328F0);
	if (target_unit_index != -1)
	{
	if (s_unit_data *player_unit_object = (s_unit_data *)object_try_and_get_and_verify_type(source_player_unit_index, 0x2003))
	{
		if (s_unit_data *target_unit = (s_unit_data *)object_try_and_get_and_verify_type(target_unit_index, 0x2003))
		{
			if (player_unit_object && player_unit_object->player_index != -1)
			{
				target_unit->variant_index = player_unit_object->variant_index;
				s_player_datum *source_player = player_get(player_unit_object->player_index);
				s_player_model_customization const *customization = player_get_model_customization(source_player);
				player_model_customize(customization, target_unit_index);
				target_unit->hologram_creator_weak_unit_index = source_player_unit_index;
				real_rgb_color colors[5];
				bool custom_colors = false;
				game_engine_get_change_colors(player_unit_object->player_index, customization, -1, colors, &custom_colors);
				if (custom_colors)
				{
					for (long i = 0; i < 5; i++)
						set_object_base_change_color_by_index(target_unit_index, i, &colors[i]);
				}
				else
				{
					object_set_initial_change_colors(target_unit_index, 0, nullptr);
				}
				object_apply_change_colors(target_unit_index);
			}
		}
	}
	}
}

#line 1217
unsigned char player_model_get_index(char const *name) // 0x10AB93E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_model_get_index@@YAEPBD@Z");
#line 1230

	s_game_globals *matg = try_and_get_game_globals();
	#line 1220 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
		assert(matg);
		#line 1235 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
	s_mod_globals_definition *modg = (s_mod_globals_definition *)tag_get('modg', tag_get_first_in_group('modg'));
	#line 1223 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
		assert(modg);
		#line 1239 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
	#line 1225 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
		assert(matg->player_character_types.count > 0);
		#line 1242 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
	if (name)
	{
		for (__int32 i = 0; i < modg->player_character_customizations.count; i++)
		{
			s_mod_globals_player_character_customization &character_customization_block = modg->player_character_customizations[i];
			__int32 &rep_index = character_customization_block.global_player_character_type_index;
			if (rep_index < 0 || rep_index >= matg->player_character_types.count)
				continue;
			s_game_globals_player_character_type &player_representation_block = matg->player_character_types[rep_index];
			char *character_name = Blam::Cache::StringIDCache::GetCurrent()->GetString(player_representation_block.name);
			if (!strcmp(name, character_name))
				return (unsigned char)character_customization_block.global_player_character_type_index;
		}
	}
	return 0;
}

void CustomizeObjectColors(long objectIndex, s_player_model_customization const *customization) // 0x10AB68E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CustomizeObjectColors@@YAXJPBUs_player_model_customization@@@Z");

	static void (*const UpdateArmorColors)(unsigned __int32) = reinterpret_cast<void (*)(unsigned __int32)>(0x5A2FA0);
	s_object_data *object = object_try_and_get_and_verify_type(objectIndex, -1);
	static void (*const ApplyArmor)(s_player_model_customization *, unsigned __int32) = reinterpret_cast<void (*)(s_player_model_customization *, unsigned __int32)>(0x5A4430);
	static void (*const ApplyArmorColor)(unsigned __int32, __int32, float *) = reinterpret_cast<void (*)(unsigned __int32, __int32, float *)>(0xB328F0);
	if (!object)
		return;
	for (__int32 i = 0; i < 5; i++)
	{
		float colorData[3];
		for (__int32 j = 0; j < 3; j++)
			colorData[2 - j] = (unsigned char)(customization->colors[i] >> (j * 8)) / 255.0f;
		ApplyArmorColor(objectIndex, i, colorData);
	}
	if (object->object_identifier.type == _object_type_biped)
		UpdateArmorColors(objectIndex);
	for (long child_index = object->first_child_object_index; child_index != -1; )
	{
		s_object_data *child_object = object_try_and_get_and_verify_type(child_index, -1);
		if (!child_object)
			break;
		if (child_object->child_variant_index != -1)
			CustomizeObjectColors(child_index, customization);
		child_index = child_object->next_object_index;
	}
}

#line 1306
void CustomizeBipeds() // 0x10AB63E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CustomizeBipeds@@YAXXZ");
#line 1332

	s_game_globals *matg = try_and_get_game_globals();
	#line 1312 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
		assert(matg);
		#line 1337 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
	s_mod_globals_definition *modg = (s_mod_globals_definition *)tag_get('modg', tag_get_first_in_group('modg'));
	#line 1314 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
		assert(modg);
		#line 1341 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
	#line 1315 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
		assert(matg->player_character_types.count > 0);
		#line 1344 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\player_model_patches.cpp"
	for (__int32 i = 0; i < modg->player_character_customizations.count; i++)
	{
		__int32 rep_index = modg->player_character_customizations[i].global_player_character_type_index;
		if (rep_index < 0 || rep_index >= matg->player_character_types.count)
			continue;
		s_mod_globals_player_character_customization *character = nullptr;
		if (!modg->player_character_customizations.try_get_element(i, &character))
			continue;
		char *character_name = Blam::Cache::StringIDCache::GetCurrent()->GetString(matg->player_character_types[rep_index].name);
		__int32 character_index = character->character_position_data.biped_name_index;
		s_player_model_customization customization = {};
		if (!Player::CPlayerCharacterSystem::BuildCharacterCustomization(character_name, customization))
			continue;
		unsigned __int32 bipedObject = -1;
		c_data_array<s_object_header> *object_headers = object_headers_get();
		for (c_data_iterator<s_object_header> it = object_headers->begin(); it != object_headers->end(); ++it)
		{
			if (character_index == it->data->name_index)
			{
				bipedObject = it.current_datum_index;
				break;
			}
		}
		if (bipedObject != -1)
		{
			((void (*)(s_player_model_customization *, unsigned __int32))0x5A4430)(&customization, bipedObject);
			CustomizeObjectColors(bipedObject, &customization);
		}
	}
}

void update_customization_biped() // 0x10ABB920
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update_customization_biped@@YAXXZ");

	void (*const object_get_orientation)(long, real_vector3d *, real_vector3d *) = reinterpret_cast<void (*)(long, real_vector3d *, real_vector3d *)>(0xB2E490);
	void (*const object_queue_render_thread_message)(long, short, long) = reinterpret_cast<void (*)(long, short, long)>(0xB31B80);
	if (customization_biped_index == -1)
		return;
	if (customization_biped_angle_dirty)
	{
		real_vector3d forward;
		real_vector3d up;
		object_get_orientation(customization_biped_index, &forward, &up);
		float angle_radians = customzation_biped_angle_degrees / 180.0f * 3.14159265f;
		forward.i = cos(angle_radians);
		forward.j = sin(angle_radians);
		object_set_position(customization_biped_index, nullptr, &forward, &up, nullptr);
		if (customization_char_platform_index != -1 && CharacterHasFlag(2))
			object_set_position(customization_char_platform_index, nullptr, &forward, &up, nullptr);
		object_queue_render_thread_message(customization_biped_index, 1, 1);
		customization_biped_angle_dirty = false;
	}
}

void set_customization_bipeds() // 0x10ABADC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_customization_bipeds@@YAXXZ");

	std::vector<int> characterBipeds;
	s_mod_globals_definition *modg = nullptr;
	modg = mod_globals_get_definition();
	if (modg)
	{
		for (__int32 i = 0; i < modg->player_character_customizations.count; i++)
		{
			s_mod_globals_player_character_customization *character = modg->player_character_customizations.get_element(i);
			if (character && character->character_position_data.biped_name_index != -1)
			{
				long object_index = scenario_find_named_object(character->character_position_data.biped_name_index);
				if (!object_try_and_get_and_verify_type(object_index, 1))
					continue;
				characterBipeds.push_back(object_index);
			}
		}
	}
	if (characterBipeds.size() > 0)
		render_patches_set_customization_biped(characterBipeds);
}

void UpdateUiPlayerModelArmor() // 0x10AB7470
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateUiPlayerModelArmor@@YAXXZ");

	void (*const Object_SetTransform)(__int32, real_vector3d *, real_vector3d *, real_vector3d *, __int32) = reinterpret_cast<void (*)(__int32, real_vector3d *, real_vector3d *, real_vector3d *, __int32)>(0xB33530);
	void (*const object_get_orientation)(long, real_vector3d *, real_vector3d *) = reinterpret_cast<void (*)(long, real_vector3d *, real_vector3d *)>(0xB2E490);
	if (!object_try_and_get_and_verify_type(customization_biped_index, 1))
	{
		customization_biped_index = user_interface_find_model_customization_biped();
		if (customization_biped_index != -1)
		{
			real_vector3d forward;
			real_vector3d up;
			object_get_orientation(customization_biped_index, &forward, &up);
			customzation_biped_angle_degrees = angle_between_vectors3d(&forward, &global_forward3d) / 3.1415927f * -180.0f;
		}
	}
	set_customization_bipeds();
	if (!object_try_and_get_and_verify_type(customization_char_platform_index, 0x80) && CharacterHasFlag(2))
		customization_char_platform_index = user_interface_find_char_platform();
	if (customization_biped_index == -1)
		return;
	if (s_UiPlayerModelState.Flags & 1)
	{
		float t = game_ticks_to_seconds((float)s_UiPlayerModelState.RotationTicks++);
		float d = s_UiPlayerModelState.RotationDuration;
		if (d != 0.0f)
		{
			if (t > d)
			{
				t = d;
				s_UiPlayerModelState.Flags &= ~1;
			}
			float c = Utils::Math::DeltaAngle(s_UiPlayerModelState.StartRotationAngle, s_UiPlayerModelState.EndRotationAngle);
			float b = s_UiPlayerModelState.StartRotationAngle;
			customzation_biped_angle_degrees = std::lerp(b, b - c, Utils::Math::EaseOutCubic(t / d));
		}
		else
		{
			customzation_biped_angle_degrees = s_UiPlayerModelState.EndRotationAngle;
			s_UiPlayerModelState.Flags &= ~1;
		}
		customization_biped_angle_dirty = true;
	}
	if (s_UiPlayerModelState.Flags & 2)
	{
		real_vector3d forward;
		real_vector3d up;
		object_get_orientation(customization_biped_index, &forward, &up);
		float angle_radians = customzation_biped_angle_degrees / 180.0f * 3.1415927f;
		forward.i = cos(angle_radians);
		forward.j = sin(angle_radians);
		Object_SetTransform(customization_biped_index, (real_vector3d *)s_UiPlayerModelState.Position, &forward, &up, 0);
		s_UiPlayerModelState.Flags &= ~2;
	}
	if (!updateUiPlayerArmor)
		return;
	if (customization_biped_index != -1)
		CustomizeBipeds();
	updateUiPlayerArmor = false;
}

bool CharacterHasFlag(__int32 flag) // 0x10AB63A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CharacterHasFlag@@YA_NH@Z");

	if ((1 << flag) & customization_biped_flags)
	{
		return true;
	}

	return false;
}

void SetUiPlayerModelPosition(real_vector3d const *newPosition) // 0x10AB73B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetUiPlayerModelPosition@@YAXPBUreal_vector3d@@@Z");

	*(real_vector3d *)s_UiPlayerModelState.Position = *newPosition;
	s_UiPlayerModelState.Flags |= 2;
}

void SetUiPlayerModelRotation(float angleDegrees, float seconds) // 0x10AB7400
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetUiPlayerModelRotation@@YAXMM@Z");

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

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
bool updateUiPlayerArmor;
long customization_biped_index = -1;
long customization_char_platform_index = -1;
float &customzation_biped_angle_degrees = *reinterpret_cast<float *>(0x194A66C);
bool customization_biped_angle_dirty;
__int32 customization_biped_flags = -1;
UiPlayerModelState s_UiPlayerModelState;
