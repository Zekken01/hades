/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/forge/forge_globals.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Forge/Geoemetry.hpp"

/* ---------- forward declarations */

struct s_forge_globals_definition;
struct s_object_header;

namespace Forge {}
using namespace ::Forge;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Forge
{
	namespace PodiumPoint
	{
		extern long FindPodiumObject();
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Forge
{
	namespace PodiumPoint
	{
		_extern long _sub_10698120();
		long FindPodiumObject() // 0x10698120
		{
			mangled_x86(MANGLED_TODO, "?FindPodiumObject@PodiumPoint@Forge@@YAJXZ");
			// procedure flags: nofpo
			// static ...; // 0x106981F4
			// static ...; // 0x106981E8
			// static ...; // 0x106981E0
			// c_data_array<s_object_header> *object_headers;
			// s_forge_globals_definition const *forge_globals;
			{
				// c_data_iterator<s_object_header> it;
			}
			todo("implement");
			long __result = _sub_10698120();
			return __result;
		}
	}
}

/* ---------- private code */
