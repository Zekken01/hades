/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/game/aim_target.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
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

struct c_aim_target_predicted;
struct c_aim_target_simulation_entity;
struct real_vector3d;
struct s_aim_assist_targeting_result;
namespace
{
	struct s_simulation_action_projectile_fire_result;
	struct s_player_predicted_aim_assist;
	struct s_weapon_fire_event_sending_data;
	struct s_predicted_weapon_fire_projectile_data;
	struct s_predicted_weapon_fire_data;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace SimulationWeapon {}
	using namespace Patches::SimulationWeapon;
}

/* ---------- constants */

/* ---------- definitions */

namespace
{
	struct s_simulation_action_projectile_fire_result
	{
		long projectile_creation_id; // 0x0
		bool impact_valid; // 0x4
		unsigned char __pad0[3]; // 0x5
		long impact_object_index; // 0x8
		long impact_node_index; // 0xC
		real_point3d position; // 0x10
		bool conical_valid; // 0x1C
		unsigned char __pad1[1]; // 0x1D
		unsigned short conical_random_seed; // 0x1E
	};
	static_assert(sizeof(s_simulation_action_projectile_fire_result) == 32, "Invalid s_simulation_action_projectile_fire_result size");

	#pragma pack(push, 4)
	struct s_player_predicted_aim_assist
	{
		c_aim_target_predicted aim_target; // 0x0
		float primary_auto_aim_level; // 0xC
		float secondary_auto_aim_level; // 0x10
		real_vector3d lead_vector; // 0x14
		unsigned char flags; // 0x20
		unsigned char __pad0[3]; // 0x21
		s_aim_assist_targeting_result aim_assist_data; // 0x24
	};
	#pragma pack(pop)
	static_assert(sizeof(s_player_predicted_aim_assist) == 76, "Invalid s_player_predicted_aim_assist size");

	#pragma pack(push, 4)
	struct s_weapon_fire_event_sending_data
	{
		public:
		struct s_predicted_impact_target
		{
			long encoding_type; // 0x0
			long weapon_fire_impact_entitiy_index; // 0x4
			long predicted_object_glue_index; // 0x8
		};
		static_assert(sizeof(s_predicted_impact_target) == 12, "Invalid s_predicted_impact_target size");
		struct s_predicted_projectile_fire_data
		{
			long projectile_creation_id; // 0x0
			bool impact_valid; // 0x4
			unsigned char __pad0[3]; // 0x5
			real_point3d position; // 0x8
			long object_node_index; // 0x14
			long target_index; // 0x18
			bool conical_valid; // 0x1C
			unsigned char __pad1[1]; // 0x1D
			unsigned short conical_random_seed; // 0x1E
		};
		static_assert(sizeof(s_predicted_projectile_fire_data) == 32, "Invalid s_predicted_projectile_fire_data size");
		public:
		long unit_inventory_index; // 0x0
		long weapon_definition_index; // 0x4
		long barrel_index; // 0x8
		bool barrel_should_recover; // 0xC
		bool aiming_vector_valid; // 0xD
		unsigned char __pad0[2]; // 0xE
		real_vector3d aiming_vector; // 0x10
		long predicted_impact_target_count; // 0x1C
		s_predicted_impact_target predicted_impact_targets[16]; // 0x20
		long predicted_projectile_fire_data_count; // 0xE0
		s_predicted_projectile_fire_data predicted_projectile_fire_data[16]; // 0xE4
		s_player_predicted_aim_assist aim_target_predicted; // 0x2E4
		c_aim_target_simulation_entity aim_target_simulation_entity; // 0x330
		float projectile_error; // 0x344
		short unit_zoom_level; // 0x348
		unsigned char __pad1[2]; // 0x34A
		long tracked_gamestate_index; // 0x34C
		bool generated_from_host_live_fire; // 0x350
		unsigned char __pad2[3]; // 0x351
	};
	#pragma pack(pop)
	static_assert(sizeof(s_weapon_fire_event_sending_data) == 852, "Invalid s_weapon_fire_event_sending_data size");

	#pragma pack(push, 4)
	struct s_predicted_weapon_fire_projectile_data
	{
		long projectile_id; // 0x0
		bool impact_valid; // 0x4
		unsigned char __pad0[3]; // 0x5
		real_point3d position; // 0x8
		long object_index; // 0x14
		bool conical_valid; // 0x18
		unsigned char __pad1[1]; // 0x19
		unsigned short conical_random_seed; // 0x1A
	};
	#pragma pack(pop)
	static_assert(sizeof(s_predicted_weapon_fire_projectile_data) == 28, "Invalid s_predicted_weapon_fire_projectile_data size");

	struct s_predicted_weapon_fire_data
	{
		short unit_zoom_level; // 0x0
		unsigned char __pad0[2]; // 0x2
		long tracked_gamestate_index; // 0x4
		s_predicted_weapon_fire_projectile_data predicted_projectile_fire_data[4]; // 0x8
		long predicted_projectile_fire_data_count; // 0x78
		bool field_7C; // 0x7C
		unsigned char __pad1[3]; // 0x7D
	};
	static_assert(sizeof(s_predicted_weapon_fire_data) == 128, "Invalid s_predicted_weapon_fire_data size");
}
/* ---------- prototypes */

namespace Patches
{
	namespace SimulationWeapon
	{
		extern void ApplyAll();
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace SimulationWeapon
	{
		_extern void _sub_1069EDB0();
		void ApplyAll() // 0x1069EDB0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@SimulationWeapon@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_1069EDB0();
		}
	}
}

/* ---------- private code */
