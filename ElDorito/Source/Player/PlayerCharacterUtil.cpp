/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Modules/ModuleCampaign.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
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
#include <limits>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

struct s_game_globals;
struct s_game_globals_player_character_type;
struct s_game_globals_player_representation;
struct s_object_data;
struct s_player_datum;
struct s_unit_data;
namespace Modules
{
	class ModuleCampaign;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0x106BE970
unsigned long object_get_variant_name(long object_index);  // hades: added for 0x106BE970

extern bool (*game_is_campaign)();  // hades: added for 0x106BE4A0

s_game_globals *game_globals_get();  // hades: added for 0X106BEC20

extern long get_player_character_representation_index(s_game_globals_player_character_type const &character_type);
extern long player_find_character_type_by_name(unsigned long name);
extern long get_player_character_representation_index(long character_type_index);
extern long unit_get_player_character_type_block_index(long unit_index);
extern bool unit_try_get_global_player_character_type(long unit_index, s_game_globals_player_character_type **out_player_character);
extern long unit_get_global_player_representation_block_index(long unit_index);
extern long unit_get_global_player_information_block_index(long unit_index);
extern long unit_get_global_player_control_block_index(long unit_index);

/* ---------- globals */

namespace Utils
{
	Modules::ModuleCampaign *Utils::Singleton<Modules::ModuleCampaign>::m_instance; // 0x113861C0
}

/* ---------- private variables */

/* ---------- public code */

long get_player_character_representation_index(s_game_globals_player_character_type const &character_type) // 0x106BE4A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_player_character_representation_index@@YAJABUs_game_globals_player_character_type@@@Z");

	if (game_is_campaign() && Modules::ModuleCampaign::Instance().VarPlayerRepresentationEnabledClient->ValueInt)
	{
		return character_type.campaign_player_representation_block_index;
	}
	else
	{
		return character_type.multiplayer_player_representation_block_index;
	}
}

long player_find_character_type_by_name(unsigned long name) // 0x106BE5C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_find_character_type_by_name@@YAJK@Z");

	s_game_globals *globals = game_globals_get();

	for (long i = 0; i < globals->player_character_types.count; i++)
	{
		if (globals->player_character_types[i].name == name)
			return i;
	}

	return -1;
}

long get_player_character_representation_index(long character_type_index) // 0x106BE530
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_player_character_representation_index@@YAJJ@Z");

	s_game_globals_player_character_type *character_type = game_globals_get()->player_character_types.get_element(character_type_index);

	if (!character_type)
		return -1;

	return get_player_character_representation_index(*character_type);
}

long unit_get_player_character_type_block_index(long unit_index) // 0x106BE970
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_get_player_character_type_block_index@@YAJJ@Z");

	s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003);
	if (!unit)
		return -1;
	if (unit->unit_flags & 0x40000000)
	{
		unit_index = unit->hologram_creator_weak_unit_index;
		unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003);
	}
	if (unit)
	{
		if (unit->player_index != -1)
		{
			s_player_datum *player = player_get(unit->player_index);
			if (player && player->character_type_index != -1)
				return player->character_type_index;
		}
		s_game_globals *game_globals = game_globals_get();
		long first_default_character_index = -1;
		for (long i = 0; i < game_globals->player_character_types.count; i++)
		{
			s_game_globals_player_representation *player_representation;
			long representation_index = get_player_character_representation_index(i);
			if (game_globals->PlayerRepresentation.try_get_element(representation_index, &player_representation))
			{
				unsigned long const variant_name = object_get_variant_name(unit_index);
				if (unit->definition_index == player_representation->ThirdPersonUnit.index)
				{
					if (variant_name == player_representation->ThirdPersonVariant)
						return i;
					if (player_representation->ThirdPersonVariant == 0)
						first_default_character_index = i;
				}
			}
		}
		if (first_default_character_index != -1)
			return first_default_character_index;
	}
	return 0;
}

bool unit_try_get_global_player_character_type(long unit_index, s_game_globals_player_character_type **out_player_character) // 0x106BEC20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_try_get_global_player_character_type@@YA_NJPAPAUs_game_globals_player_character_type@@@Z");

	long index = unit_get_player_character_type_block_index(unit_index);
	if (index == -1)
		return false;
	return game_globals_get()->player_character_types.try_get_element(index, out_player_character);
}

long unit_get_global_player_representation_block_index(long unit_index) // 0x106BE8B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_get_global_player_representation_block_index@@YAJJ@Z");

	s_game_globals_player_character_type *player_character;

	if (unit_try_get_global_player_character_type(unit_index, &player_character))
	{
		long representation_index = get_player_character_representation_index(*player_character);

		return representation_index;
	}

	return 0;
}

long unit_get_global_player_information_block_index(long unit_index) // 0x106BE7F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_get_global_player_information_block_index@@YAJJ@Z");

	s_game_globals_player_character_type *player_character;

	if (unit_try_get_global_player_character_type(unit_index, &player_character))
	{
		return player_character->player_information_block_index;
	}

	return 0;
}

long unit_get_global_player_control_block_index(long unit_index) // 0x106BE730
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_get_global_player_control_block_index@@YAJJ@Z");

	s_game_globals_player_character_type *player_character;

	if (unit_try_get_global_player_character_type(unit_index, &player_character))
		return player_character->player_control_block_index;

	return 0;
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Modules::ModuleCampaign & Utils::Singleton<Modules::ModuleCampaign>::Instance();
template bool c_tag_block<s_game_globals_player_character_type>::try_get_element(__int32, s_game_globals_player_character_type **) const;
template bool c_tag_block<s_game_globals_player_representation>::try_get_element(__int32, s_game_globals_player_representation **) const;
template c_flags<enum e_unit_flags,unsigned long> c_flags<enum e_unit_flags,unsigned long>::operator&(__int32 const) const;
template c_flags<enum e_unit_flags,unsigned long>::c_flags(unsigned long const &);
template c_flags<enum e_unit_flags,unsigned long>::operator bool() const;
template c_tag_block_index<s_game_globals_player_information,char>::operator char() const;
template c_tag_block_index<s_game_globals_player_representation,char>::operator char() const;
template s_game_globals_player_character_type & c_tag_block<s_game_globals_player_character_type>::operator[](__int32);
template s_game_globals_player_character_type * c_tag_block<s_game_globals_player_character_type>::get_element(__int32) const;
