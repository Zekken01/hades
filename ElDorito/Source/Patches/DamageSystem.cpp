/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
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
#include "Blam/memory/data_array.inl"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
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
#include <functional>
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

struct real_vector3d;
struct s_damage_reporting_info;
namespace
{
	struct s_unit_player_melee_damage_target;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace DamageSystem {}
	using namespace Patches::DamageSystem;
}

/* ---------- constants */

/* ---------- definitions */

namespace
{
	struct s_unit_player_melee_damage_target
	{
		real_point3d position; // 0x0
		real_vector3d direction; // 0xC
		long bsp_index; // 0x18
		long object_index; // 0x1C
		short breakable_surface_set_index; // 0x20
		short breakable_surface_index; // 0x22
		long instanced_geometry_index; // 0x24
		long surface_index; // 0x28
		long object_material_index; // 0x2C
		short global_material_index; // 0x30
		unsigned char __pad0[2]; // 0x32
		float scale; // 0x34
		s_damage_reporting_info damage_reporting_info; // 0x38
		long byte3C; // 0x3C
		s_unit_player_melee_damage_target(s_unit_player_melee_damage_target &); /* compiler_generated() */
		s_unit_player_melee_damage_target(s_unit_player_melee_damage_target const &); /* compiler_generated() */
		s_unit_player_melee_damage_target(); /* compiler_generated() */
		s_unit_player_melee_damage_target &operator=(s_unit_player_melee_damage_target &); /* compiler_generated() */
		s_unit_player_melee_damage_target &operator=(s_unit_player_melee_damage_target const &); /* compiler_generated() */
	};
	static_assert(sizeof(s_unit_player_melee_damage_target) == 64, "Invalid s_unit_player_melee_damage_target size");
}
/* ---------- prototypes */

namespace Patches
{
	namespace DamageSystem
	{
		extern void ApplyAll();
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace DamageSystem
	{
		_extern void _sub_1095F330();
		void ApplyAll() // 0x1095F330
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@DamageSystem@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_1095F330();
		}
	}
}

/* ---------- private code */
