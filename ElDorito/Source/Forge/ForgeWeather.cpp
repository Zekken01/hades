/* ---------- headers */

#include "Forge/ForgeWeather.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/forge/forge_globals.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/rasterizer/rasterizer_game_states.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeObjectProperties.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/Reforge.hpp"

/* ---------- forward declarations */

struct s_cluster_reference;
struct s_forge_globals_definition;
struct s_rasterizer_game_states;
namespace Forge
{
	class CForgeWeather;
	struct ForgeMapModifierProperties;
}

namespace Forge {}
using namespace ::Forge;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern long currentWeatherIndex; // 0x1134D1A4
}
using namespace hades_file_local;
/* ---------- public code */

namespace Forge
{
	void CForgeWeather::InitializeForNewMap() // 0x10680200
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?InitializeForNewMap@CForgeWeather@Forge@@SAXXZ");
		// procedure flags: nofpo

		currentWeatherIndex = -1;
	}

	void CForgeWeather::HandleMapModifierDeleted() // 0x10680140
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?HandleMapModifierDeleted@CForgeWeather@Forge@@SAXXZ");
		// procedure flags: nofpo
			// s_rasterizer_game_states *rasterizer_game_states;
		// function call : void (*const)(unsigned long)

		if (currentWeatherIndex != -1)
		{
			s_rasterizer_game_states *rasterizerGameStates = tls_getd().rasterizer_game_states;
			if (rasterizerGameStates->weather_effects[0] != -1)
			{
				((void (__cdecl *)(long))0x5B6FC0)(rasterizerGameStates->weather_effects[0]);
				rasterizerGameStates->weather_effects[0] = -1;
			}
		}
	}

	void CForgeWeather::Update(long mapModifierIndex, Forge::ForgeMapModifierProperties &mapModifierProperties) // 0x10680230
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Update@CForgeWeather@Forge@@SAXJAAUForgeMapModifierProperties@2@@Z");
		// Forge::ForgeMapModifierProperties &mapModifierProperties;
		// long newWeatherIndex;
		// s_rasterizer_game_states *rasterizerGameStates;
		// __int32 desiredWeatherIndex;
		// s_forge_globals_definition *forge_globals;
		// function call : void (*const)(unsigned long)

		s_forge_globals_definition *forge_globals = forge_globals_get_definition();
		s_rasterizer_game_states *rasterizerGameStates = tls_getd().rasterizer_game_states;
		long newWeatherIndex = -1;
		__int32 desiredWeatherIndex;
		if ((desiredWeatherIndex = mapModifierProperties.AtmosphereProperties.Weather - 1) >= 0 && desiredWeatherIndex < forge_globals->weather_effects.count)
			newWeatherIndex = desiredWeatherIndex;

		if (currentWeatherIndex != newWeatherIndex && rasterizerGameStates->weather_effects[0] != -1)
		{
			currentWeatherIndex = -1;
			((void (__cdecl *)(long))0x5B6FC0)(rasterizerGameStates->weather_effects[0]);
			rasterizerGameStates->weather_effects[0] = -1;
		}
		else
		{
			currentWeatherIndex = newWeatherIndex;
			UpdateWeatherEffects();
		}
	}

	bool CForgeWeather::UpdateWeatherEffects() // 0x10680350
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateWeatherEffects@CForgeWeather@Forge@@SA_NXZ");
		// procedure flags: nofpo
		// static ...; // 0x10680478
		// static ...; // 0x1068046C
		// static ...; // 0x10680464
		// s_rasterizer_game_states *rasterizerGameStates;
		// s_forge_globals_definition *forge_globals;
		// long effectTagIndex;
			// s_cluster_reference scenarioLocation;
		// function call : long (*const)(long)
		// function call : void (*const)(unsigned long, s_cluster_reference *)

		if (currentWeatherIndex == -1)
			return false;
		s_rasterizer_game_states *rasterizerGameStates = tls_getd().rasterizer_game_states;
		if (rasterizerGameStates->weather_effects[0] != -1)
			return false;
		s_forge_globals_definition *forge_globals = forge_globals_get_definition();
		long effectTagIndex = forge_globals->weather_effects[currentWeatherIndex].effect.index;
		if (effectTagIndex != -1)
			rasterizerGameStates->weather_effects[0] = ((long(*)(long))0x5B8BD0)(effectTagIndex);
		if (rasterizerGameStates->weather_effects[0] != -1)
		{
			s_cluster_reference scenarioLocation = {};
			((void(*)(long, s_cluster_reference *))0x5B9720)(rasterizerGameStates->weather_effects[0], &scenarioLocation);
		}
		return true;
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_forge_weather_definition>::try_get_element(__int32, s_forge_weather_definition **) const;
template s_forge_weather_definition & c_tag_block<s_forge_weather_definition>::operator[](__int32);
template s_forge_weather_definition * c_tag_block<s_forge_weather_definition>::get_element(__int32) const;

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { long currentWeatherIndex = -1; }
