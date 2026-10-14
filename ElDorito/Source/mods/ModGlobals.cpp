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
	__int32 CModGlobals::FindCharacterSet(std::string const &name) // 0x10788160
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?FindCharacterSet@CModGlobals@Mods@@SAHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x107882EC
		// static ...; // 0x107882E0
		// static ...; // 0x107882D8
		// std::string const &name;
		// s_mod_globals_definition *modg;
		// std::shared_ptr<Blam::Cache::StringIDCache> stringCache;
			// __int32 i;
				// char *currentName;

		std::shared_ptr<Blam::Cache::StringIDCache> stringCache = Blam::Cache::StringIDCache::GetCurrent();
		s_mod_globals_definition *modg = mod_globals_get_definition();
		if (!modg)
			return -1;
		for (__int32 i = 0; i < modg->player_character_sets.count; i++)
		{
			char *currentName = stringCache->GetString(modg->player_character_sets[i].name);
			if (currentName && name == currentName)
				return i;
		}
		return -1;
	}

	__int32 CModGlobals::FindCharacterInSet(__int32 characterSetIndex, std::string const &name) // 0x10787EF0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?FindCharacterInSet@CModGlobals@Mods@@SAHHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x107880C8
		// static ...; // 0x107880C0
		// __int32 characterSetIndex;
		// std::string const &name;
		// s_mod_globals_player_character_set const &set;
		// s_mod_globals_definition *modg;
		// std::shared_ptr<Blam::Cache::StringIDCache> stringCache;
			// __int32 i;
				// char *currentName;

		std::shared_ptr<Blam::Cache::StringIDCache> stringCache = Blam::Cache::StringIDCache::GetCurrent();
		s_mod_globals_definition *modg = mod_globals_get_definition();
		if (!modg)
			return -1;
		if (characterSetIndex < 0 || characterSetIndex >= modg->player_character_sets.count)
			return -1;
		s_mod_globals_player_character_set const &set = modg->player_character_sets[characterSetIndex];
		for (__int32 i = 0; i < set.characters.count; i++)
		{
			char *currentName = stringCache->GetString(set.characters[i].name);
			if (currentName && name == currentName)
				return i;
		}
		return -1;
	}

	__int32 CModGlobals::GetCharacterVisionModeGlobals(__int32 characterTypeIndex) // 0x10788710
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetCharacterVisionModeGlobals@CModGlobals@Mods@@SAHH@Z");
		// __int32 characterTypeIndex;
		// s_mod_globals_definition *modg;
			// __int32 i;

		s_mod_globals_definition *mod_globals = mod_globals_get_definition();
		if (mod_globals)
		{
			for (int i = 0; i < mod_globals->player_character_customizations.count; i++)
			{
				if (mod_globals->player_character_customizations[i].global_player_character_type_index == characterTypeIndex)
				{
					return mod_globals->player_character_customizations[i].vision_mode.index;
				}
			}
		}

		return -1;
	}

	__int32 CModGlobals::GetCharacterHudGlobals(__int32 characterTypeIndex) // 0x10788640
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetCharacterHudGlobals@CModGlobals@Mods@@SAHH@Z");
		// __int32 characterTypeIndex;
		// s_mod_globals_definition *modg;
			// __int32 i;

		s_mod_globals_definition *mod_globals = mod_globals_get_definition();
		if (mod_globals)
		{
			for (int i = 0; i < mod_globals->player_character_customizations.count; i++)
			{
				if (mod_globals->player_character_customizations[i].global_player_character_type_index == characterTypeIndex)
				{
					return mod_globals->player_character_customizations[i].hud_globals.index;
				}
			}
		}

		return -1;
	}

	bool CModGlobals::GetCharacterDefaultColors(__int32 characterTypeIndex, unsigned long *colors) // 0x10788360
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetCharacterDefaultColors@CModGlobals@Mods@@SA_NHPAK@Z");
		// unsigned long *colors;
		// s_mod_globals_definition *modg;
			// __int32 i;
				// s_mod_globals_player_character_customization const &customization;
					// long j;
			// long i;

		s_mod_globals_definition *modg = nullptr;
		if (characterTypeIndex != -1)
		{
			modg = mod_globals_get_definition();
			if (modg)
			{
				for (__int32 i = 0; i < modg->player_character_customizations.count; i++)
				{
					s_mod_globals_player_character_customization const &customization = modg->player_character_customizations[i];
					if (customization.global_player_character_type_index == characterTypeIndex)
					{
						for (long j = 0; j < 5; j++)
							colors[j] = reinterpret_cast<s_mod_globals_player_character_colors::s_change_color_block const *>(customization.character_colors.colors)[j].default_color;
						return true;
					}
				}
			}
		}
		for (long i = 0; i < 5; i++)
			colors[i] = 0;
		return false;
	}

	bool CModGlobals::GetCharacterDefaultColors(__int32 characterTypeIndex, real_rgb_color *colors) // 0x10788490
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetCharacterDefaultColors@CModGlobals@Mods@@SA_NHPAUreal_rgb_color@@@Z");
		// real_rgb_color *colors;
		// s_mod_globals_definition *modg;
			// __int32 i;
				// s_mod_globals_player_character_customization const &customization;
					// long j;
			// long i;
		// function call : real_rgb_color *(*const)(unsigned long, real_rgb_color *)

		s_mod_globals_definition *modg = nullptr;
		if (characterTypeIndex != -1)
		{
			modg = mod_globals_get_definition();
			if (modg)
			{
				for (__int32 i = 0; i < modg->player_character_customizations.count; i++)
				{
					s_mod_globals_player_character_customization const &customization = modg->player_character_customizations[i];
					if (customization.global_player_character_type_index == characterTypeIndex)
					{
						for (long j = 0; j < 5; j++)
							((void(*)(unsigned long, real_rgb_color *))0x521300)(reinterpret_cast<s_mod_globals_player_character_colors::s_change_color_block const *>(customization.character_colors.colors)[j].default_color, &colors[j]);
						return true;
					}
				}
			}
		}
		for (long i = 0; i < 5; i++)
			colors[i] = { 0.0f, 0.0f, 0.0f };
		return false;
	}
}


namespace Mods
{
	s_mod_globals_player_character_customization *CModGlobals::GetCustomizationCharacter(__int32 characterTypeIndex) // 0x107887E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetCustomizationCharacter@CModGlobals@Mods@@SAPAUs_mod_globals_player_character_customization@@H@Z");
		// __int32 characterTypeIndex;
		// s_mod_globals_definition *modg;
			// __int32 i;
				// s_mod_globals_player_character_customization *character;

		s_mod_globals_definition *globals = nullptr;
		if (characterTypeIndex != -1)
		{
			globals = mod_globals_get_definition();
			if (globals)
			{
				for (long i = 0; i < globals->player_character_customizations.count; i++)
				{
					s_mod_globals_player_character_customization *customization = globals->player_character_customizations.get_element(i);
					if (customization->global_player_character_type_index == characterTypeIndex)
						return customization;
				}
			}
		}

		return nullptr;
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
