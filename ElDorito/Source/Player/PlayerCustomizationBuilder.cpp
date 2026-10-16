/* ---------- headers */

#include "Player/PlayerCustomizationBuilder.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/player_model_customization.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Magnets.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/ModGlobals.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Player/PlayerCharacterSystem.hpp"
#include "Player/PlayerCustomizationDB.hpp"
#include "Player/PlayerCustomizationExtension.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <regex>
#include <stdexcept>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
struct s_mod_globals_player_character_customization;
struct s_model_customization_player_region;
struct s_model_customization_player_region_permutation;
struct s_model_customization_selection;
struct s_player_appearance;
struct s_player_character_customiztion;
namespace Player
{
	class CPlayerCharacterCustomizationBuilder;
	class CPlayerCustomizationDB;
	struct SPersistentCharacterCustomization;
}

namespace Utils {}
using namespace ::Utils;
namespace Player {}
using namespace ::Player;
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

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const game_in_progress = reinterpret_cast<bool (*)()>(0x5314B0);
}

namespace Player
{
	extern void BuildChangeColors(unsigned long *changeColors, std::map<std::string,std::string> const &colors);
}

unsigned __int32 ParseColor(std::string const &value);

extern long tag_find_by_name(unsigned long group_tag, char const *name);  // hades: added for 0x107CBA30
extern void *(__cdecl *const tag_get)(unsigned long, long);  // hades: added for 0x107CBA30

/* ---------- globals */

namespace Utils
{
	Player::CPlayerCustomizationDB *Utils::Singleton<Player::CPlayerCustomizationDB>::m_instance; // 0x1138E3C8
}

/* ---------- private variables */

/* ---------- public code */

namespace Player
{
	void BuildChangeColors(unsigned long *changeColors, std::map<std::string,std::string> const &colors) // 0x107CA700
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?BuildChangeColors@Player@@YAXPAKABV?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@U?$less@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@std@@@2@@std@@@Z");

		for (const auto [changeColorAscii, colorValue] : colors)
		{
			if (changeColorAscii == "primary")
				changeColors[0] = ::ParseColor(colorValue);
			else if (changeColorAscii == "secondary")
				changeColors[1] = ::ParseColor(colorValue);
			else if (changeColorAscii == "tertiary")
				changeColors[2] = ::ParseColor(colorValue);
			else if (changeColorAscii == "quaternary")
				changeColors[3] = ::ParseColor(colorValue);
			else if (changeColorAscii == "quinary")
				changeColors[4] = ::ParseColor(colorValue);
		}
	}

	bool CPlayerCharacterCustomizationBuilder::BuildCustomizationFromPlayerModel(__int32 playerModelIndex, s_player_character_customiztion *data) // 0x107CB040
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?BuildCustomizationFromPlayerModel@CPlayerCharacterCustomizationBuilder@Player@@QAE_NHPAUs_player_character_customiztion@@@Z");

		if (!Initialize())
			return false;
		memset(data, 0, sizeof(s_player_character_customiztion));
		if (playerModelIndex < 0 || playerModelIndex >= m_mulg->universal->player_model.count)
			return false;
		s_model_customization_selection &playerModel = m_mulg->universal->player_model[playerModelIndex];
		char *characterName = m_stringCache->GetString(playerModel.character_name);
		if (!characterName)
			return false;
		SPersistentCharacterCustomization storedCustomization;
		if (!Utils::Singleton<CPlayerCustomizationDB>::Instance().GetCharacterCustomization(characterName, storedCustomization))
		{
			for (__int32 i = 0; i < m_modg->player_character_customizations.count; i++)
			{
				if (m_modg->player_character_customizations[i].global_player_character_type_index == 0)
				{
					for (__int32 j = 0; j < 5; j++)
					{
						s_mod_globals_player_character_customization *const modgCustomization = &m_modg->player_character_customizations[i];
						reinterpret_cast<s_player_model_customization *>(data->customization)->colors[j] = reinterpret_cast<s_mod_globals_player_character_colors::s_change_color_block const *>(modgCustomization->character_colors.colors)[j].default_color;
					}
					BuildChangeColors(reinterpret_cast<s_player_model_customization *>(data->customization)->colors, storedCustomization.colors);
					break;
				}
			}
		}
		data->character_name = playerModel.character_name;
		for (auto const [regionName, permutationName] : storedCustomization.permutations)
		{
			auto [region_index, permutation_index] = FindPlayerModelPermutation(playerModel, regionName, permutationName);
			if (region_index != -1 && permutation_index != -1)
				reinterpret_cast<s_player_model_customization *>(data->customization)->armor_section_indices[region_index] = permutation_index;
		}
		BuildChangeColors(reinterpret_cast<s_player_model_customization *>(data->customization)->colors, storedCustomization.colors);
		return true;
	}

	// mangled_x86(MANGLED_DEFAULT, "??0CPlayerCustomizationDB@Player@@QAE@XZ"); no body to assert in

	// mangled_x86(MANGLED_DEFAULT, "??0SPersistentCharacterCustomization@Player@@QAE@XZ"); no body to assert in

	// mangled_x86(MANGLED_DEFAULT, "??1SPersistentCharacterCustomization@Player@@QAE@XZ"); no body to assert in
	_inline SPersistentCharacterCustomization::~SPersistentCharacterCustomization() = default; // 0x107C9ED0

	bool CPlayerCharacterCustomizationBuilder::BuildCharacterCustomizations(std::string const &preferredCharacterName, s_player_appearance *data) // 0x107CAA20
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?BuildCharacterCustomizations@CPlayerCharacterCustomizationBuilder@Player@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAUs_player_appearance@@@Z");

		memset(&data->model_customization, 0, sizeof(data->model_customization));
		memset(data->characters, 0, sizeof(data->characters));
		data->characters_count = 0;
		if (!Initialize())
			return false;
		bool preferredCharacterCustomized = false;
		data->preferred_character = m_stringCache->GetStringId(preferredCharacterName);
		for (__int32 i = 0; i < m_mulg->universal->player_model.count; i++)
		{
			s_model_customization_selection const &playerModel = m_mulg->universal->player_model[i];
			s_player_character_customiztion customization = {};
			if (!BuildCustomizationFromPlayerModel(i, &customization))
				continue;
			memcpy(&data->characters[data->characters_count++], &customization, sizeof(customization));
			if (playerModel.character_name == data->preferred_character)
			{
				memcpy(&data->model_customization, customization.customization, sizeof(data->model_customization));
				preferredCharacterCustomized = true;
			}
		}
		if (!preferredCharacterCustomized)
		{
			Player::SPersistentCharacterCustomization defaultCustomization;
			if (Utils::Singleton<Player::CPlayerCustomizationDB>::Instance().GetCharacterCustomization(preferredCharacterName, defaultCustomization))
				BuildChangeColors(data->model_customization.colors, defaultCustomization.colors);
			else
			{
				s_model_customization_selection &playerModel = m_mulg->universal->player_model[0];
				char *characterName = m_stringCache->GetString(playerModel.character_name);
				if (characterName && Utils::Singleton<Player::CPlayerCustomizationDB>::Instance().GetCharacterCustomization(characterName, defaultCustomization))
					BuildChangeColors(data->model_customization.colors, defaultCustomization.colors);
				else
				{
					for (__int32 i = 0; i < m_modg->player_character_customizations.count; i++)
					{
						if (m_modg->player_character_customizations[i].global_player_character_type_index == 0)
						{
							for (__int32 j = 0; j < 5; j++)
							{
								s_mod_globals_player_character_customization *const modgCustomization = &m_modg->player_character_customizations[i];
								data->model_customization.colors[j] = ((s_mod_globals_player_character_colors::s_change_color_block *)modgCustomization->character_colors.colors)[j].default_color;
							}
							break;
						}
					}
				}
			}
		}
		return true;
	}

	bool CPlayerCharacterCustomizationBuilder::BuildSingleCharacterCustomization(std::string const &characterName, s_player_character_customiztion *data) // 0x107CB5C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?BuildSingleCharacterCustomization@CPlayerCharacterCustomizationBuilder@Player@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAUs_player_character_customiztion@@@Z");

		if (!Initialize())
			return false;
		__int32 playerModelIndex = FindPlayerModel(characterName);
		return playerModelIndex != -1 && BuildCustomizationFromPlayerModel(playerModelIndex, data);
	}

	bool CPlayerCharacterCustomizationBuilder::Initialize() // 0x107CBA30
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Initialize@CPlayerCharacterCustomizationBuilder@Player@@AAE_NXZ");

		if (!eldorado::game_in_progress())
			return false;
		if (!m_mulg)
		{
			m_stringCache = Blam::Cache::StringIDCache::GetCurrent();
			__int32 mulgIndex = tag_find_by_name('mulg', "multiplayer\\multiplayer_globals");
			if (mulgIndex == -1)
				return false;
			m_mulg = (s_multiplayer_globals_definition *)tag_get('mulg', mulgIndex);
			if (!m_mulg)
				return false;
		}
		if (!m_modg)
		{
			__int32 modgIndex = tag_find_by_name('modg', "multiplayer\\mod_globals");
			if (modgIndex == -1)
				return false;
			m_modg = (s_mod_globals_definition *)tag_get('modg', modgIndex);
			if (!m_modg)
				return false;
		}
		return true;
	}
}


namespace Player
{
	std::pair<int,int> CPlayerCharacterCustomizationBuilder::FindPlayerModelPermutation(s_model_customization_selection const &selection, std::string const &regionName, std::string const &permutationName) // 0x107CB790
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?FindPlayerModelPermutation@CPlayerCharacterCustomizationBuilder@Player@@AAE?AU?$pair@HH@std@@ABUs_model_customization_selection@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@4@1@Z");

		for (__int32 i = 0; i < selection.regions.count; i++)
		{
			s_model_customization_player_region const &region = selection.regions[i];
			char const *currentRegionName = m_stringCache->GetString(region.name);
			if (!currentRegionName || regionName != currentRegionName)
				continue;
			for (__int32 j = 0; j < region.permutations.count; j++)
			{
				s_model_customization_player_region_permutation const &permutation = region.permutations[j];
				char const *const currentPermutationName = permutation.variants.count > 0 ? m_stringCache->GetString(permutation.variants[0].permutation_name) : "default";
				if (currentPermutationName && permutationName == currentPermutationName)
					return { i, j };
			}
		}
		return { -1, -1 };
	}

	__int32 CPlayerCharacterCustomizationBuilder::FindPlayerModel(std::string const &characterName) // 0x107CB680
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?FindPlayerModel@CPlayerCharacterCustomizationBuilder@Player@@AAEHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

		for (__int32 i = 0; i < m_mulg->universal->player_model.count; i++)
		{
			char *name = m_stringCache->GetString(m_mulg->universal->player_model[i].character_name);
			if (name && characterName == name)
				return i;
		}
		return -1;
	}
}

/* ---------- private code */

unsigned __int32 ParseColor(std::string const &value) // 0x107CBD20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ParseColor@@YAIABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

	std::cmatch what;
	std::regex expression("#([A-Fa-f0-9]{6}|[A-Fa-f0-9]{3})");
	if (std::regex_match(value.c_str(), what, expression))
		return std::stoi(value.substr(1), nullptr, 16);
	else
		return 0;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Player::CPlayerCustomizationDB & Utils::Singleton<Player::CPlayerCustomizationDB>::Instance();
template bool c_tag_block<s_model_customization_player_region>::try_get_element(__int32, s_model_customization_player_region **) const;
template bool c_tag_block<s_model_customization_player_region_permutation>::try_get_element(__int32, s_model_customization_player_region_permutation **) const;
template bool c_tag_block<s_model_customization_region_permutation>::try_get_element(__int32, s_model_customization_region_permutation **) const;
template bool c_tag_block<s_model_customization_selection>::try_get_element(__int32, s_model_customization_selection **) const;
template s_model_customization_player_region * c_tag_block<s_model_customization_player_region>::get_element(__int32) const;
template s_model_customization_player_region const & c_tag_block<s_model_customization_player_region>::operator[](__int32) const;
template s_model_customization_player_region_permutation * c_tag_block<s_model_customization_player_region_permutation>::get_element(__int32) const;
template s_model_customization_player_region_permutation const & c_tag_block<s_model_customization_player_region_permutation>::operator[](__int32) const;
template s_model_customization_region_permutation * c_tag_block<s_model_customization_region_permutation>::get_element(__int32) const;
template s_model_customization_region_permutation const & c_tag_block<s_model_customization_region_permutation>::operator[](__int32) const;
template s_model_customization_selection & c_tag_block<s_model_customization_selection>::operator[](__int32);
template s_model_customization_selection * c_tag_block<s_model_customization_selection>::get_element(__int32) const;
