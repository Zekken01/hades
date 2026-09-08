/* ---------- headers */

#include "mods/ModGlobals.hpp"
#include "hades/hades.h"

#include "Blam/Cache/StringIdCache.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/mods/mod_globals.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patches/CustomPackets.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

struct real_rgb_color;
struct s_mod_globals_definition;
struct s_mod_globals_player_character_customization;
struct s_mod_globals_player_character_set;
namespace Blam
{
	namespace Cache
	{
		struct StringIDCache;
	}
}
namespace Mods
{
	struct CModGlobals;
}

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

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Mods
{
	_extern __int32 _sub_10788160(std::string const &);
	__int32 CModGlobals::FindCharacterSet(std::string const &name) // 0x10788160
	{
		mangled_x86(MANGLED_TODO, "?FindCharacterSet@CModGlobals@Mods@@SAHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x107882EC
		// static ...; // 0x107882E0
		// static ...; // 0x107882D8
		// std::string const &name;
		// s_mod_globals_definition *modg;
		// std::shared_ptr<Blam::Cache::StringIDCache> stringCache;
		{
			// __int32 i;
			{
				// char *currentName;
			}
		}
		todo("implement");
		__int32 __result = _sub_10788160(name);
		return __result;
	}

	_extern __int32 _sub_10787EF0(__int32, std::string const &);
	__int32 CModGlobals::FindCharacterInSet(__int32 characterSetIndex, std::string const &name) // 0x10787EF0
	{
		mangled_x86(MANGLED_TODO, "?FindCharacterInSet@CModGlobals@Mods@@SAHHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x107880C8
		// static ...; // 0x107880C0
		// __int32 characterSetIndex;
		// std::string const &name;
		// s_mod_globals_player_character_set const &set;
		// s_mod_globals_definition *modg;
		// std::shared_ptr<Blam::Cache::StringIDCache> stringCache;
		{
			// __int32 i;
			{
				// char *currentName;
			}
		}
		todo("implement");
		__int32 __result = _sub_10787EF0(characterSetIndex, name);
		return __result;
	}

	_extern __int32 _sub_10788710(__int32);
	__int32 CModGlobals::GetCharacterVisionModeGlobals(__int32 characterTypeIndex) // 0x10788710
	{
		mangled_x86(MANGLED_TODO, "?GetCharacterVisionModeGlobals@CModGlobals@Mods@@SAHH@Z");
		// __int32 characterTypeIndex;
		// s_mod_globals_definition *modg;
		{
			// __int32 i;
		}
		todo("implement");
		__int32 __result = _sub_10788710(characterTypeIndex);
		return __result;
	}

	_extern __int32 _sub_10788640(__int32);
	__int32 CModGlobals::GetCharacterHudGlobals(__int32 characterTypeIndex) // 0x10788640
	{
		mangled_x86(MANGLED_TODO, "?GetCharacterHudGlobals@CModGlobals@Mods@@SAHH@Z");
		// __int32 characterTypeIndex;
		// s_mod_globals_definition *modg;
		{
			// __int32 i;
		}
		todo("implement");
		__int32 __result = _sub_10788640(characterTypeIndex);
		return __result;
	}

	_extern bool _sub_10788360(__int32, unsigned long *);
	bool CModGlobals::GetCharacterDefaultColors(__int32 characterTypeIndex, unsigned long *colors) // 0x10788360
	{
		mangled_x86(MANGLED_TODO, "?GetCharacterDefaultColors@CModGlobals@Mods@@SA_NHPAK@Z");
		// unsigned long *colors;
		// s_mod_globals_definition *modg;
		{
			// __int32 i;
			{
				// s_mod_globals_player_character_customization const &customization;
				{
					// long j;
				}
			}
		}
		{
			// long i;
		}
		todo("implement");
		bool __result = _sub_10788360(characterTypeIndex, colors);
		return __result;
	}

	_extern bool _sub_10788490(__int32, real_rgb_color *);
	bool CModGlobals::GetCharacterDefaultColors(__int32 characterTypeIndex, real_rgb_color *colors) // 0x10788490
	{
		mangled_x86(MANGLED_TODO, "?GetCharacterDefaultColors@CModGlobals@Mods@@SA_NHPAUreal_rgb_color@@@Z");
		// real_rgb_color *colors;
		// s_mod_globals_definition *modg;
		{
			// __int32 i;
			{
				// s_mod_globals_player_character_customization const &customization;
				{
					// long j;
				}
			}
		}
		{
			// long i;
		}
		// function call : real_rgb_color *(*const)(unsigned long, real_rgb_color *)
		todo("implement");
		bool __result = _sub_10788490(characterTypeIndex, colors);
		return __result;
	}
}

extern s_mod_globals_player_character_customization *_sub_107887E0(__int32);
namespace Mods
{
	s_mod_globals_player_character_customization *CModGlobals::GetCustomizationCharacter(__int32 characterTypeIndex) // 0x107887E0
	{
		mangled_x86(MANGLED_TODO, "?GetCustomizationCharacter@CModGlobals@Mods@@SAPAUs_mod_globals_player_character_customization@@H@Z");
		// __int32 characterTypeIndex;
		// s_mod_globals_definition *modg;
		{
			// __int32 i;
			{
				// s_mod_globals_player_character_customization *character;
			}
		}
		todo("implement");
		s_mod_globals_player_character_customization * __result = _sub_107887E0(characterTypeIndex);
		return __result;
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_mod_globals_player_character>::try_get_element(__int32, s_mod_globals_player_character **) const;
template bool c_tag_block<s_mod_globals_player_character_set>::try_get_element(__int32, s_mod_globals_player_character_set **) const;
template s_mod_globals_player_character * c_tag_block<s_mod_globals_player_character>::get_element(__int32) const;
template s_mod_globals_player_character const & c_tag_block<s_mod_globals_player_character>::operator[](__int32) const;
template s_mod_globals_player_character_set & c_tag_block<s_mod_globals_player_character_set>::operator[](__int32);
template s_mod_globals_player_character_set * c_tag_block<s_mod_globals_player_character_set>::get_element(__int32) const;
