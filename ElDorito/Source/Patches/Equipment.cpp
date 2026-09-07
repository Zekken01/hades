/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/items/equipment.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/motor/action_system.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "ElDorito.hpp"
#include "Forge/Geoemetry.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "Utils/Macros.hpp"
#include "Utils/String.hpp"

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

struct s_action_request;
struct s_equipment_data;
struct s_object_data;
struct s_player_action_context;
struct s_player_datum;
struct s_player_interaction;
struct s_unit_data;

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Forge {}
using namespace ::Forge;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Sprint {}
	using namespace Patches::Sprint;
	namespace Equipment {}
	using namespace Patches::Equipment;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

//struct player_examine_nearby_item_hook::__l2::s_unit_weapon_pickup_result
//{
//	char indices1[2]; // 0x0
//	char indices2[2]; // 0x2
//};
//static_assert(sizeof(player_examine_nearby_item_hook::__l2::s_unit_weapon_pickup_result) == 4, "Invalid player_examine_nearby_item_hook::__l2::s_unit_weapon_pickup_result size");

//struct player_examine_nearby_item_hook::__l2::s_unit_weapon_pickup_action_request :
//	public s_action_request
//{
//	long item_index; // 0x4
//	long pickup_type; // 0x8
//};
//static_assert(sizeof(player_examine_nearby_item_hook::__l2::s_unit_weapon_pickup_action_request) == 12, "Invalid player_examine_nearby_item_hook::__l2::s_unit_weapon_pickup_action_request size");

/* ---------- prototypes */

namespace Patches
{
	namespace Equipment
	{
		extern void ApplyAll();
		extern void PlayerConsiderEquipmentInteraction(long playerIndex, long equipmentIndex, s_player_action_context *outActionContext);
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Equipment
	{
		_extern void _sub_10A53110();
		void ApplyAll() // 0x10A53110
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Equipment@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A53110();
		}

		_extern void _sub_10A54CF0(long, long, s_player_action_context *);
		void PlayerConsiderEquipmentInteraction(long playerIndex, long equipmentIndex, s_player_action_context *outActionContext) // 0x10A54CF0
		{
			mangled_x86(MANGLED_TODO, "?PlayerConsiderEquipmentInteraction@Equipment@Patches@@YAXJJPAUs_player_action_context@@@Z");
			// static ...; // 0x10A54F00
			// long playerIndex;
			// long equipmentIndex;
			// s_player_action_context *outActionContext;
			// s_player_datum const *player;
			// s_unit_data const *unit;
			// long active_primary_weapon_index;
			// s_equipment_data const *equipment;
			// bool (*const player_evaluate_interaction)(long, s_player_interaction *, s_player_interaction *);
			// s_player_interaction interaction;
			// float const radius;
			// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
			// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
			// function call : long (*const)(long, long *)
			// function call : bool (*const)(long)
			// function call : bool (*const)(long, long)
			// function call : bool (*const)(long, s_player_interaction *, s_player_interaction *)
			todo("implement");
			_sub_10A54CF0(playerIndex, equipmentIndex, outActionContext);
		}
	}
}

/* ---------- private code */
