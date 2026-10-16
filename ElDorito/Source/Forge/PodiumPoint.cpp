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
		long FindPodiumObject() // 0x10698120
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?FindPodiumObject@PodiumPoint@Forge@@YAJXZ");

			s_forge_globals_definition const *forge_globals = forge_globals_get_definition();
			if (!forge_globals)
				return -1;
			if (forge_globals->podium_placement_object.index == -1)
				return -1;
			c_data_array<s_object_header> *object_headers = object_headers_get();
			for (c_data_iterator<s_object_header> it = object_headers->begin(); it != object_headers->end(); ++it)
			{
				if (it->data->definition_index == forge_globals->podium_placement_object.index)
					return it.current_datum_index;
			}
			return -1;
		}
	}
}

/* ---------- private code */
