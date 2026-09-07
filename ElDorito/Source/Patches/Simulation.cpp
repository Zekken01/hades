/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
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
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/saved_games/scenario_map_variant.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/simulation/simulation_entity_definition.hpp"
#include "Blam/simulation/simulation_game_objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Forge/ForgeDevice.hpp"
#include "Forge/Geoemetry.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/GamePatches.hpp"
#include "Player/PlayerEmotes.hpp"
#include "Pointer.hpp"
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
#include <initializer_list>
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
#include <vector>

/* ---------- forward declarations */

struct real_rectangle3d;
struct real_vector3d;
struct s_map_variant_placement_properties;
struct s_simulation_generic_creation_data;
struct s_simulation_object_state_data;
namespace
{
	struct s_simulation_reforge_object_creation_datum;
	struct s_simulation_generic_creation_data_v2;
	struct s_simulation_device_state_data;
}

namespace Utils {}
using namespace ::Utils;
namespace Player {}
using namespace ::Player;
namespace Forge {}
using namespace ::Forge;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Simulation {}
	using namespace Patches::Simulation;
	namespace Game {}
	using namespace Patches::Game;
	namespace HaloScript {}
	using namespace Patches::HaloScript;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

namespace
{
	struct s_simulation_reforge_object_creation_datum
	{
		bool valid; // 0x0
		unsigned char __pad0[3]; // 0x1
		real_point3d position; // 0x4
		real_vector3d forward; // 0x10
		real_vector3d up; // 0x1C
		s_map_variant_placement_properties properties; // 0x28
		s_simulation_reforge_object_creation_datum(s_simulation_reforge_object_creation_datum &); /* compiler_generated() */
		s_simulation_reforge_object_creation_datum(s_simulation_reforge_object_creation_datum const &); /* compiler_generated() */
		s_simulation_reforge_object_creation_datum(); /* compiler_generated() */
		s_simulation_reforge_object_creation_datum &operator=(s_simulation_reforge_object_creation_datum &); /* compiler_generated() */
		s_simulation_reforge_object_creation_datum &operator=(s_simulation_reforge_object_creation_datum const &); /* compiler_generated() */
	};
	static_assert(sizeof(s_simulation_reforge_object_creation_datum) == 64, "Invalid s_simulation_reforge_object_creation_datum size");

	#pragma pack(push, 4)
	struct s_simulation_generic_creation_data_v2 :
		public s_simulation_generic_creation_data
	{
		s_simulation_reforge_object_creation_datum reforge; // 0x14
		s_simulation_generic_creation_data_v2(s_simulation_generic_creation_data_v2 &); /* compiler_generated() */
		s_simulation_generic_creation_data_v2(s_simulation_generic_creation_data_v2 const &); /* compiler_generated() */
		s_simulation_generic_creation_data_v2(); /* compiler_generated() */
		s_simulation_generic_creation_data_v2 &operator=(s_simulation_generic_creation_data_v2 &); /* compiler_generated() */
		s_simulation_generic_creation_data_v2 &operator=(s_simulation_generic_creation_data_v2 const &); /* compiler_generated() */
	};
	#pragma pack(pop)
	static_assert(sizeof(s_simulation_generic_creation_data_v2) == 84, "Invalid s_simulation_generic_creation_data_v2 size");

	struct s_simulation_device_state_data :
		public s_simulation_object_state_data
	{
		float device_position; // 0xA0
		float device_group_position; // 0xA4
		float device_power; // 0xA8
		float device_group_power; // 0xAC
	};
	static_assert(sizeof(s_simulation_device_state_data) == 176, "Invalid s_simulation_device_state_data size");
}
/* ---------- prototypes */

namespace Patches
{
	namespace Simulation
	{
		extern void ApplyAll();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern real_rectangle3d global_null_rectangle3d; // 0x111B22E0
}
/* ---------- public code */

namespace Patches
{
	namespace Simulation
	{
		_extern void _sub_10ACCE60();
		void ApplyAll() // 0x10ACCE60
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Simulation@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10ACCE60();
		}
	}
}

/* ---------- private code */
