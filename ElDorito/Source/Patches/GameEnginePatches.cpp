/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_events.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_engine_candy_monitor.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/multiplayer_definitions.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/simulation/simulation_entity_definition.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Modules/ModuleVoIP.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
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

class Patch;
struct lambda_1;
struct s_damage_reporting_info;
struct s_game_engine_event_data;
struct s_multiplayer_weapon;
namespace Modules
{
	class ModuleVoIP;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace PlayerPodium {}
	using namespace Player::PlayerPodium;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace GameEngine {}
	using namespace Patches::GameEngine;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

//class game_engine_weapon_item_definition_index_from_absolute_weapons_selection_block_index_hook::__l11::<lambda_1>
//{
//public:
//	float operator()(s_multiplayer_weapon const &) const;
//};
//static_assert(sizeof(game_engine_weapon_item_definition_index_from_absolute_weapons_selection_block_index_hook::__l11::<lambda_1>) == 1, "Invalid game_engine_weapon_item_definition_index_from_absolute_weapons_selection_block_index_hook::__l11::<lambda_1> size");

/* ---------- prototypes */

namespace Patches
{
	namespace GameEngine
	{
		extern void ApplyAll();
	}
}

/* ---------- globals */

namespace Utils
{
	Modules::ModuleVoIP *Utils::Singleton<Modules::ModuleVoIP>::m_instance; // 0x1138DD74
}

/* ---------- private variables */

/* ---------- public code */

extern s_game_engine_event_data* _sub_107A91F0(s_game_engine_event_data *const);
_inline s_game_engine_event_data::s_game_engine_event_data() // 0x107A91F0
{
	mangled_x86(MANGLED_TODO, "??0s_game_engine_event_data@@QAE@XZ");
	// s_game_engine_event_data *const this;
	compiler_generated();
	todo("implement");
	_sub_107A91F0(this);
}

_extern void _sub_107A9240(Patch *const);
_inline Patch::~Patch() // 0x107A9240
{
	mangled_x86(MANGLED_TODO, "??1Patch@@QAE@XZ");
	// Patch *const this;
	compiler_generated();
	todo("implement");
	_sub_107A9240(this);
}

extern s_damage_reporting_info &_sub_107A92D0(s_damage_reporting_info *const, s_damage_reporting_info const &);
_inline s_damage_reporting_info &s_damage_reporting_info::operator=(s_damage_reporting_info const &__that) // 0x107A92D0
{
	mangled_x86(MANGLED_TODO, "??4s_damage_reporting_info@@QAEAAU0@ABU0@@Z");
	// s_damage_reporting_info const &__that;
	compiler_generated();
	todo("implement");
	s_damage_reporting_info & __result = _sub_107A92D0(this, __that);
	return __result;
}

namespace Patches
{
	namespace GameEngine
	{
		_extern void _sub_107A96D0();
		void ApplyAll() // 0x107A96D0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@GameEngine@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_107A96D0();
		}
	}
}

/* ---------- private code */
