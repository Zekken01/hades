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

namespace
{
	extern long currentWeatherIndex; // 0x1134D1A4
}
/* ---------- public code */

namespace Forge
{
	_extern void _sub_10680200();
	void CForgeWeather::InitializeForNewMap() // 0x10680200
	{
		mangled_x86(MANGLED_TODO, "?InitializeForNewMap@CForgeWeather@Forge@@SAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_10680200();
	}

	_extern void _sub_10680140();
	void CForgeWeather::HandleMapModifierDeleted() // 0x10680140
	{
		mangled_x86(MANGLED_TODO, "?HandleMapModifierDeleted@CForgeWeather@Forge@@SAXXZ");
		// procedure flags: nofpo
		{
			// s_rasterizer_game_states *rasterizer_game_states;
		}
		// function call : void (*const)(unsigned long)
		todo("implement");
		_sub_10680140();
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
