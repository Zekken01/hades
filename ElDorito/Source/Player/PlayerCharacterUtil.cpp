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

_extern long _sub_106BE4A0(s_game_globals_player_character_type const &);
long get_player_character_representation_index(s_game_globals_player_character_type const &character_type) // 0x106BE4A0
{
	mangled_x86(MANGLED_TODO, "?get_player_character_representation_index@@YAJABUs_game_globals_player_character_type@@@Z");
	// s_game_globals_player_character_type const &character_type;
	// function call : bool (*)()
	todo("implement");
	long __result = _sub_106BE4A0(character_type);
	return __result;
}

_extern long _sub_106BE5C0(unsigned long);
long player_find_character_type_by_name(unsigned long name) // 0x106BE5C0
{
	mangled_x86(MANGLED_TODO, "?player_find_character_type_by_name@@YAJK@Z");
	// unsigned long name;
	// s_game_globals *game_globals;
	{
		// __int32 i;
	}
	todo("implement");
	long __result = _sub_106BE5C0(name);
	return __result;
}

_extern long _sub_106BE530(long);
long get_player_character_representation_index(long character_type_index) // 0x106BE530
{
	mangled_x86(MANGLED_TODO, "?get_player_character_representation_index@@YAJJ@Z");
	// long character_type_index;
	// s_game_globals_player_character_type *character_type;
	todo("implement");
	long __result = _sub_106BE530(character_type_index);
	return __result;
}

_extern long _sub_106BE970(long);
long unit_get_player_character_type_block_index(long unit_index) // 0x106BE970
{
	mangled_x86(MANGLED_TODO, "?unit_get_player_character_type_block_index@@YAJJ@Z");
	// static ...; // 0x106BEB78
	// static ...; // 0x106BEB6C
	// static ...; // 0x106BEB64
	// long unit_index;
	// s_unit_data *unit;
	{
		// s_game_globals *game_globals;
		// long first_default_character_index;
		{
			// s_player_datum *player;
		}
		{
			// long i;
			{
				// long representation_index;
				// s_game_globals_player_representation *player_representation;
				{
					// unsigned long const variant_name;
				}
			}
		}
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	long __result = _sub_106BE970(unit_index);
	return __result;
}

_extern bool _sub_106BEC20(long, s_game_globals_player_character_type **);
bool unit_try_get_global_player_character_type(long unit_index, s_game_globals_player_character_type **out_player_character) // 0x106BEC20
{
	mangled_x86(MANGLED_TODO, "?unit_try_get_global_player_character_type@@YA_NJPAPAUs_game_globals_player_character_type@@@Z");
	// s_game_globals_player_character_type **out_player_character;
	// long index;
	todo("implement");
	bool __result = _sub_106BEC20(unit_index, out_player_character);
	return __result;
}

_extern long _sub_106BE8B0(long);
long unit_get_global_player_representation_block_index(long unit_index) // 0x106BE8B0
{
	mangled_x86(MANGLED_TODO, "?unit_get_global_player_representation_block_index@@YAJJ@Z");
	// static ...; // 0x106BE934
	// static ...; // 0x106BE928
	// static ...; // 0x106BE920
	// long unit_index;
	// s_game_globals_player_character_type *player_character;
	{
		// long representation_index;
	}
	todo("implement");
	long __result = _sub_106BE8B0(unit_index);
	return __result;
}

_extern long _sub_106BE7F0(long);
long unit_get_global_player_information_block_index(long unit_index) // 0x106BE7F0
{
	mangled_x86(MANGLED_TODO, "?unit_get_global_player_information_block_index@@YAJJ@Z");
	// static ...; // 0x106BE870
	// static ...; // 0x106BE864
	// static ...; // 0x106BE85C
	// long unit_index;
	// s_game_globals_player_character_type *player_character;
	todo("implement");
	long __result = _sub_106BE7F0(unit_index);
	return __result;
}

_extern long _sub_106BE730(long);
long unit_get_global_player_control_block_index(long unit_index) // 0x106BE730
{
	mangled_x86(MANGLED_TODO, "?unit_get_global_player_control_block_index@@YAJJ@Z");
	// static ...; // 0x106BE7B0
	// static ...; // 0x106BE7A4
	// static ...; // 0x106BE79C
	// long unit_index;
	// s_game_globals_player_character_type *player_character;
	todo("implement");
	long __result = _sub_106BE730(unit_index);
	return __result;
}

/* ---------- private code */
