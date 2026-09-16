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

	_extern void _sub_10680230(long, Forge::ForgeMapModifierProperties &);
	void CForgeWeather::Update(long mapModifierIndex, Forge::ForgeMapModifierProperties &mapModifierProperties) // 0x10680230
	{
		mangled_x86(MANGLED_TODO, "?Update@CForgeWeather@Forge@@SAXJAAUForgeMapModifierProperties@2@@Z");
		// Forge::ForgeMapModifierProperties &mapModifierProperties;
		// long newWeatherIndex;
		// s_rasterizer_game_states *rasterizerGameStates;
		// __int32 desiredWeatherIndex;
		// s_forge_globals_definition *forge_globals;
		// function call : void (*const)(unsigned long)
		todo("implement");
		_sub_10680230(mapModifierIndex, mapModifierProperties);
	}

	_extern bool _sub_10680350();
	bool CForgeWeather::UpdateWeatherEffects() // 0x10680350
	{
		mangled_x86(MANGLED_TODO, "?UpdateWeatherEffects@CForgeWeather@Forge@@SA_NXZ");
		// procedure flags: nofpo
		// static ...; // 0x10680478
		// static ...; // 0x1068046C
		// static ...; // 0x10680464
		// s_rasterizer_game_states *rasterizerGameStates;
		// s_forge_globals_definition *forge_globals;
		// long effectTagIndex;
		{
			// s_cluster_reference scenarioLocation;
		}
		// function call : long (*const)(long)
		// function call : void (*const)(unsigned long, s_cluster_reference *)
		todo("implement");
		bool __result = _sub_10680350();
		return __result;
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
