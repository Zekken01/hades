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

namespace Player
{
	extern void BuildChangeColors(unsigned long *changeColors, std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > const &colors);
}

unsigned __int32 ParseColor(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &value);

/* ---------- globals */

namespace Utils
{
	Player::CPlayerCustomizationDB *Utils::Singleton<Player::CPlayerCustomizationDB>::m_instance; // 0x1138E3C8
}

/* ---------- private variables */

/* ---------- public code */

namespace Player
{
	_extern void _sub_107CA700(unsigned long *, std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > const &);
	void BuildChangeColors(unsigned long *changeColors, std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > const &colors) // 0x107CA700
	{
		mangled_x86(MANGLED_TODO, "?BuildChangeColors@Player@@YAXPAKABV?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@U?$less@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@std@@@2@@std@@@Z");
		// static ...; // 0x107CA961
		// static ...; // 0x107CA95C
		// static ...; // 0x107CA938
		// static ...; // 0x107CA930
		// unsigned long *changeColors;
		// std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > const &colors;
		{
			// std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > const &<range>$L0;
			// std::_Tree_unchecked_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > >,std::_Iterator_base0> <begin>$L0;
			// std::_Default_sentinel <end>$L0;
			{
				// std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > $S10;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &changeColorAscii;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &colorValue;
			}
		}
		todo("implement");
		_sub_107CA700(changeColors, colors);
	}

	_extern bool _sub_107CB040(Player::CPlayerCharacterCustomizationBuilder *const, __int32, s_player_character_customiztion *);
	bool CPlayerCharacterCustomizationBuilder::BuildCustomizationFromPlayerModel(__int32 playerModelIndex, s_player_character_customiztion *data) // 0x107CB040
	{
		mangled_x86(MANGLED_TODO, "?BuildCustomizationFromPlayerModel@CPlayerCharacterCustomizationBuilder@Player@@QAE_NHPAUs_player_character_customiztion@@@Z");
		// static ...; // 0x107CB476
		// static ...; // 0x107CB471
		// static ...; // 0x107CB46C
		// static ...; // 0x107CB430
		// static ...; // 0x107CB428
		// Player::CPlayerCharacterCustomizationBuilder *const this;
		// __int32 playerModelIndex;
		// s_player_character_customiztion *data;
		// Player::SPersistentCharacterCustomization storedCustomization;
		// char *characterName;
		// s_model_customization_selection &playerModel;
		{
			// __int32 i;
			{
				// __int32 j;
				{
					// s_mod_globals_player_character_customization *const modgCustomization;
				}
			}
		}
		{
			// std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > &<range>$L0;
			// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > > <begin>$L0;
			// std::_Default_sentinel <end>$L0;
			{
				// std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > $S11;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &regionName;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &permutationName;
				{
					// std::pair<int,int> $S12;
					// __int32 &region_index;
					// __int32 &permutation_index;
				}
			}
		}
		todo("implement");
		bool __result = _sub_107CB040(this, playerModelIndex, data);
		return __result;
	}

	_inline CPlayerCustomizationDB::CPlayerCustomizationDB() // 0x107C95F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0CPlayerCustomizationDB@Player@@QAE@XZ");
		// Player::CPlayerCustomizationDB *const this;

		compiler_generated();
	}

	_inline SPersistentCharacterCustomization::SPersistentCharacterCustomization() // 0x107C96B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0SPersistentCharacterCustomization@Player@@QAE@XZ");
		// Player::SPersistentCharacterCustomization *const this;

		compiler_generated();
	}

	_inline SPersistentCharacterCustomization::~SPersistentCharacterCustomization() // 0x107C9ED0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??1SPersistentCharacterCustomization@Player@@QAE@XZ");
		// Player::SPersistentCharacterCustomization *const this;

		compiler_generated();
	}

	_extern bool _sub_107CAA20(Player::CPlayerCharacterCustomizationBuilder *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, s_player_appearance *);
	bool CPlayerCharacterCustomizationBuilder::BuildCharacterCustomizations(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &preferredCharacterName, s_player_appearance *data) // 0x107CAA20
	{
		mangled_x86(MANGLED_TODO, "?BuildCharacterCustomizations@CPlayerCharacterCustomizationBuilder@Player@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAUs_player_appearance@@@Z");
		// static ...; // 0x107CAECC
		// static ...; // 0x107CAEC4
		// Player::CPlayerCharacterCustomizationBuilder *const this;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &preferredCharacterName;
		// s_player_appearance *data;
		// bool preferredCharacterCustomized;
		{
			// __int32 i;
			{
				// s_player_character_customiztion customization;
				// s_model_customization_selection const &playerModel;
			}
		}
		{
			// Player::SPersistentCharacterCustomization defaultCustomization;
			{
				// char *characterName;
				// s_model_customization_selection &playerModel;
				{
					// __int32 i;
					{
						// __int32 j;
						{
							// s_mod_globals_player_character_customization *const modgCustomization;
						}
					}
				}
			}
		}
		todo("implement");
		bool __result = _sub_107CAA20(this, preferredCharacterName, data);
		return __result;
	}

	_extern bool _sub_107CB5C0(Player::CPlayerCharacterCustomizationBuilder *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, s_player_character_customiztion *);
	bool CPlayerCharacterCustomizationBuilder::BuildSingleCharacterCustomization(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &characterName, s_player_character_customiztion *data) // 0x107CB5C0
	{
		mangled_x86(MANGLED_TODO, "?BuildSingleCharacterCustomization@CPlayerCharacterCustomizationBuilder@Player@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAUs_player_character_customiztion@@@Z");
		// s_player_character_customiztion *data;
		// __int32 playerModelIndex;
		todo("implement");
		bool __result = _sub_107CB5C0(this, characterName, data);
		return __result;
	}

	_extern bool _sub_107CBA30(Player::CPlayerCharacterCustomizationBuilder *const);
	bool CPlayerCharacterCustomizationBuilder::Initialize() // 0x107CBA30
	{
		mangled_x86(MANGLED_TODO, "?Initialize@CPlayerCharacterCustomizationBuilder@Player@@AAE_NXZ");
		// Player::CPlayerCharacterCustomizationBuilder *const this;
		{
			// __int32 mulgIndex;
		}
		{
			// __int32 modgIndex;
		}
		// function call : bool (*const)()
		// function call : void *(*const)(unsigned long, long)
		// function call : void *(*const)(unsigned long, long)
		todo("implement");
		bool __result = _sub_107CBA30(this);
		return __result;
	}
}

extern std::pair<int,int> _sub_107CB790(Player::CPlayerCharacterCustomizationBuilder *const, s_model_customization_selection const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
namespace Player
{
	std::pair<int,int> CPlayerCharacterCustomizationBuilder::FindPlayerModelPermutation(s_model_customization_selection const &selection, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &regionName, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &permutationName) // 0x107CB790
	{
		mangled_x86(MANGLED_TODO, "?FindPlayerModelPermutation@CPlayerCharacterCustomizationBuilder@Player@@AAE?AU?$pair@HH@std@@ABUs_model_customization_selection@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@4@1@Z");
		// static ...; // 0x107CB97C
		// Player::CPlayerCharacterCustomizationBuilder *const this;
		// s_model_customization_selection const &selection;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &regionName;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &permutationName;
		{
			// __int32 i;
			{
				// char const *currentRegionName;
				// s_model_customization_player_region const &region;
				{
					// __int32 j;
					{
						// s_model_customization_player_region_permutation const &permutation;
						// char const *const currentPermutationName;
					}
				}
			}
		}
		todo("implement");
		std::pair<int,int> __result = _sub_107CB790(this, selection, regionName, permutationName);
		return __result;
	}

	_extern __int32 _sub_107CB680(Player::CPlayerCharacterCustomizationBuilder *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
	__int32 CPlayerCharacterCustomizationBuilder::FindPlayerModel(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &characterName) // 0x107CB680
	{
		mangled_x86(MANGLED_TODO, "?FindPlayerModel@CPlayerCharacterCustomizationBuilder@Player@@AAEHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &characterName;
		{
			// __int32 i;
			{
				// char *name;
			}
		}
		todo("implement");
		__int32 __result = _sub_107CB680(this, characterName);
		return __result;
	}
}

/* ---------- private code */

_extern unsigned __int32 _sub_107CBD20(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
unsigned __int32 ParseColor(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &value) // 0x107CBD20
{
	// `anonymous-namespace'::ParseColor
	// static ...; // 0x107CBED7
	// static ...; // 0x107CBECC
	// static ...; // 0x107CBEB4
	// static ...; // 0x107CBEAC
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &value;
	// std::basic_regex<char,std::regex_traits<char> > expression;
	// std::match_results<char const *,std::allocator<std::sub_match<char const *> > > what;
	todo("implement");
	unsigned __int32 __result = _sub_107CBD20(value);
	return __result;
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
