/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/simulation/simulation_entity_definition.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Pointer.hpp"

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
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

namespace Player {}
using namespace ::Player;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Simulation {}
	using namespace Patches::Simulation;
}

/* ---------- constants */

/* ---------- definitions */

namespace
{
	// s_simulation_view_telemetry_data is defined in hades/recovered_types.h, which the synthesised
}
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

namespace Patches
{
	namespace Simulation
	{
		extern void apply_unit_entity_patches();
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Simulation
	{
		_extern void _sub_106D6F20();
		void apply_unit_entity_patches() // 0x106D6F20
		{
			mangled_x86(MANGLED_TODO, "?apply_unit_entity_patches@Simulation@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_106D6F20();
		}
	}
}

/* ---------- private code */
