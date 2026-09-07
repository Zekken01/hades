/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/game/aim_target.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/items/weapon_definitions.hpp"
#include "Blam/items/weapons.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/objects/target_tracking.hpp"
#include "Blam/simulation/simulation_types.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
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

struct c_aim_target_object;
struct c_aim_target_predicted;
struct c_aim_target_simulation_entity;
struct c_target_tracking_system;
struct real_matrix4x3;
struct real_point3d;
struct real_vector3d;
struct s_aim_assist_targeting_result;
struct s_unit_data;
struct s_unit_target_tracking_block;
struct s_weapon_data;
struct s_weapon_definition;
namespace hades_file_local
{
	struct s_simulation_action_projectile_fire_result;
	struct s_player_predicted_aim_assist;
	struct s_weapon_fire_event_sending_data;
	struct s_predicted_weapon_fire_projectile_data;
	struct s_predicted_weapon_fire_data;
}
using namespace hades_file_local;

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

namespace hades_file_local
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
using namespace hades_file_local;
/* ---------- prototypes */

namespace Patches
{
	namespace SimulationWeapon
	{
		extern void ApplyAll();
	}
}

void simulation_action_weapon_fire_hook(long weapon_index, long barrel_index, bool barrel_should_recover, long tracked_gamestate_index, float projectile_error, short unit_zoom_level, s_simulation_action_projectile_fire_result *projectile_results, long projectile_result_count, bool generated_from_host_live_fire);
void c_simulation_weapon_fire_event_definition__apply_game_event_hook(void *thisptr, void *__formal, long a1, long const *object_references, long object_reference_count, s_weapon_fire_event_sending_data *payload);

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

_extern void _sub_1069FE20(long, long, bool, long, float, short, s_simulation_action_projectile_fire_result *, long, bool);
void simulation_action_weapon_fire_hook(long weapon_index, long barrel_index, bool barrel_should_recover, long tracked_gamestate_index, float projectile_error, short unit_zoom_level, s_simulation_action_projectile_fire_result *projectile_results, long projectile_result_count, bool generated_from_host_live_fire) // 0x1069FE20
{
	// `anonymous-namespace'::simulation_action_weapon_fire_hook
	// long tracked_gamestate_index;
	// float projectile_error;
	// short unit_zoom_level;
	// s_simulation_action_projectile_fire_result *projectile_results;
	// long projectile_result_count;
	// bool generated_from_host_live_fire;
	// long player_index;
	// long object_index;
	// long object_references[1];
	// s_weapon_fire_event_sending_data event_data;
	// long aim_assist_unit_index;
	// s_weapon_definition *weapon_definiton;
	// long weapon_owner_unit_index;
	// long unit_inventory_index;
	// s_weapon_data *weapon;
	{
		// s_unit_data *unit;
		// long weapon_control_unit_index;
	}
	{
		// s_aim_assist_targeting_result *aim_assist_targeting_result;
	}
	{
		// long i;
		{
			// long index;
			// s_simulation_action_projectile_fire_result const *current_fire_result;
			{
				// long entity_index;
				{
					// long target_index;
					{
						// long j;
					}
				}
			}
		}
	}
	{
		// c_aim_target_object *aim_target;
	}
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : void *(*const)(unsigned long, long)
	// function call : long (*const)(long)
	// function call : long (*const)(long)
	// function call : long (*const)(long)
	// function call : long (*const)(long)
	// function call : bool (*const)(long, long, long *)
	// function call : void (*const)(c_aim_target_predicted *)
	// function call : void (*const)(long, real_vector3d *)
	// function call : void (*const)(s_aim_assist_targeting_result *, s_player_predicted_aim_assist *)
	// function call : bool (*const)()
	// function call : long (*const)(long)
	// function call : long (*const)(long)
	// function call : unsigned long (*const)(unsigned short)
	// function call : bool (*const)(long)
	// function call : bool (*const)(c_target_tracking_system *)
	// function call : c_aim_target_object *(*const)(c_target_tracking_system *)
	// function call : bool (*const)(c_aim_target_object *, c_aim_target_simulation_entity *)
	// function call : void (*const)(long, long, long *, long, void const *)
	// function call : void (*const)(e_simulation_event_type, long, long *, long, long, void const *)
	todo("implement");
	_sub_1069FE20(weapon_index, barrel_index, barrel_should_recover, tracked_gamestate_index, projectile_error, unit_zoom_level, projectile_results, projectile_result_count, generated_from_host_live_fire);
}

_extern void _sub_1069EF80(void *, void *, long, long const *, long, s_weapon_fire_event_sending_data *);
void c_simulation_weapon_fire_event_definition__apply_game_event_hook(void *thisptr, void *__formal, long a1, long const *object_references, long object_reference_count, s_weapon_fire_event_sending_data *payload) // 0x1069EF80
{
	// `anonymous-namespace'::c_simulation_weapon_fire_event_definition__apply_game_event_hook
	// static ...; // 0x1069F984
	// static ...; // 0x1069F980
	// static ...; // 0x1069F97C
	// static ...; // 0x1069F91C
	// static ...; // 0x1069F914
	// void *thisptr;
	// void *__formal;
	// long a1;
	// long const *object_references;
	// long object_reference_count;
	// s_weapon_fire_event_sending_data *payload;
	// long weapon_index;
	// long object_index;
	// s_predicted_weapon_fire_data fire_data;
	// long weapon_control_unit_index;
	// s_weapon_data *weapon;
	// long delay;
	// short reloading_time;
	// long object_type;
	// s_weapon_definition *weapon_def;
	// long barrel_index;
	{
		// s_unit_data *unit;
		// long weapon_set_index;
		// long unit_inventory_index;
	}
	{
		// real_point3d position;
		// real_vector3d *event_data_aiming_vector;
		// real_vector3d aiming_vector;
		{
			// long i;
			{
				// long index;
				// s_weapon_fire_event_sending_data::s_predicted_projectile_fire_data *projectile_element;
				// bool valid;
				{
					// long target_index;
					{
						// long gamestate_index;
						{
							// long predicted_object_index;
							{
								// real_matrix4x3 *node_matrices;
								// long node_index;
								// long node_matrix_count;
							}
						}
					}
				}
			}
		}
		{
		}
	}
	{
		// long v67;
		// long v57;
		// long v64;
	}
	// function call : long (*const)(long)
	// function call : long (*const)(long)
	// function call : void *(*const)(unsigned long, long)
	// function call : long (*const)(long)
	// function call : real_matrix4x3 *(*const)(long, long *)
	// function call : char (*const)(long, real_point3d *)
	// function call : void (*const)(long, real_vector3d const *, real_vector3d const *)
	// function call : bool (*const)(c_aim_target_object *)
	// function call : bool (*const)(long)
	// function call : char (*const)(c_aim_target_simulation_entity *)
	// function call : bool (*const)(c_target_tracking_system *, c_aim_target_simulation_entity *, s_unit_target_tracking_block *)
	// function call : long (*const)(float)
	// function call : bool (*const)(long, long, short *)
	// function call : void (*const)(long, bool)
	// function call : char (*const)(long, long, long *, long *, long *)
	// function call : bool (*const)()
	// function call : bool (*const)(long, short)
	// function call : char (*const)(long, short, bool)
	// function call : long (*const)(long, short)
	// function call : long (*const)(long, short, float)
	// function call : void (*const)(long, s_predicted_weapon_fire_data *, bool, long)
	todo("implement");
	_sub_1069EF80(thisptr, __formal, a1, object_references, object_reference_count, payload);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_enum<enum e_weapon_barrel_prediction_type,short>::operator==(e_weapon_barrel_prediction_type const &) const;
template bool c_tag_block<s_unit_target_tracking_block>::try_get_element(__int32, s_unit_target_tracking_block **) const;
template bool c_tag_block<s_weapon_barrel_definition>::try_get_element(__int32, s_weapon_barrel_definition **) const;
template bool s_static_array<char,2>::valid(__int32);
template bool s_static_array<long,4>::valid(__int32);
template char & s_static_array<char,2>::operator[](long);
template long & s_static_array<long,4>::operator[](long);
template s_unit_target_tracking_block & c_tag_block<s_unit_target_tracking_block>::operator[](__int32);
template s_unit_target_tracking_block * c_tag_block<s_unit_target_tracking_block>::get_element(__int32) const;
template s_weapon_barrel_definition & c_tag_block<s_weapon_barrel_definition>::operator[](__int32);
template s_weapon_barrel_definition * c_tag_block<s_weapon_barrel_definition>::get_element(__int32) const;
