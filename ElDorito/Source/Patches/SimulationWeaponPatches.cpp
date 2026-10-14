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
template<typename t_arg0> static t_arg0 *object_get(unsigned long object_index) { return (t_arg0 *)object_get(object_index); }  // hades: a file-local template in the original (undecorated `object_get<T>`), defined so it is emitted
extern bool (*const game_is_distributed)();  // hades: added for 0x1069FE20
extern void weapon_barrel_fire(long weapon_index, short barrel_index, bool a3);  // hades: added for 0x1069EF80
extern real_point3d *matrix4x3_transform_point(real_matrix4x3 const *matrix, real_point3d const *point, real_point3d *result);  // hades: added for 0x1069EF80
extern float normalize3d(real_vector3d *v);  // hades: added for 0x1069EF80
extern long (*const game_seconds_to_ticks_round)(float);  // hades: added for 0x1069EF80

namespace Patches
{
	namespace SimulationWeapon
	{
		extern void ApplyAll();
	}
}

void simulation_action_weapon_fire_hook(long weapon_index, long barrel_index, bool barrel_should_recover, long tracked_gamestate_index, float projectile_error, short unit_zoom_level, s_simulation_action_projectile_fire_result *projectile_results, long projectile_result_count, bool generated_from_host_live_fire);
void __fastcall c_simulation_weapon_fire_event_definition__apply_game_event_hook(void *thisptr, void *__formal, long a1, long const *object_references, long object_reference_count, s_weapon_fire_event_sending_data *payload);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace SimulationWeapon
	{
		void ApplyAll() // 0x1069EDB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@SimulationWeapon@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x75F2B9, simulation_action_weapon_fire_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0x1643450).Write(c_simulation_weapon_fire_event_definition__apply_game_event_hook);
		}
	}
}

/* ---------- private code */

void simulation_action_weapon_fire_hook(long weapon_index, long barrel_index, bool barrel_should_recover, long tracked_gamestate_index, float projectile_error, short unit_zoom_level, s_simulation_action_projectile_fire_result *projectile_results, long projectile_result_count, bool generated_from_host_live_fire) // 0x1069FE20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?simulation_action_weapon_fire_hook@@YAXJJ_NJMFPAUs_simulation_action_projectile_fire_result@hades_file_local@@J0@Z");
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
		// s_unit_data *unit;
		// long weapon_control_unit_index;
		// s_aim_assist_targeting_result *aim_assist_targeting_result;
		// long i;
			// long index;
			// s_simulation_action_projectile_fire_result const *current_fire_result;
				// long entity_index;
					// long target_index;
						// long j;
		// c_aim_target_object *aim_target;
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

	if (!game_is_distributed() || ((bool (*const)())0x531D10)())
		return;
	s_weapon_data *weapon = object_get<s_weapon_data>(weapon_index);
	s_weapon_definition *weapon_definiton = (s_weapon_definition *)tag_get('weap', weapon->definition_index);
	if (weapon_definiton->barrels[barrel_index].prediction_type == (e_weapon_barrel_prediction_type)1)
		return;
	long weapon_owner_unit_index = ((long (*const)(long))0xB62DF0)(weapon_index);
	long unit_inventory_index = ((long (*const)(long))0xB62E30)(weapon_index);
	long object_index = -1;
	long aim_assist_unit_index = -1;
	long player_index = -1;
	long object_references[1] = { -1 };
	if (weapon_owner_unit_index == -1)
	{
		if (unit_inventory_index == -1)
			object_index = weapon_index;
		object_references[0] = object_index;
	}
	else if (unit_inventory_index <= 3)
	{
		aim_assist_unit_index = ((long (*const)(long))0xB44600)(weapon_owner_unit_index);
		object_index = weapon_owner_unit_index;
		object_references[0] = weapon_owner_unit_index;
	}
	if (object_header_get(object_index)->type == (e_object_type)1)
	{
		s_unit_data *unit = object_get<s_unit_data>(object_index);
		long weapon_control_unit_index = unit->weapon_control_unit_index;
		if (weapon_control_unit_index == -1 || object_get<s_unit_data>(weapon_control_unit_index)->player_index == -1)
			object_index = ((long (*const)(long))0xB75F20)(object_index);
	}
	if (object_index == -1 || !((bool (*const)(long, long, long *))0x4B48E0)(object_index, 1, &player_index))
		return;
	s_weapon_fire_event_sending_data event_data;
	memset(&event_data, 0, sizeof(event_data));
	event_data.unit_inventory_index = unit_inventory_index;
	event_data.weapon_definition_index = weapon->definition_index;
	event_data.barrel_index = barrel_index;
	event_data.barrel_should_recover = barrel_should_recover;
	event_data.unit_zoom_level = unit_zoom_level;
	event_data.tracked_gamestate_index = tracked_gamestate_index;
	event_data.projectile_error = fmaxf(0.0f, fminf(1.0f, projectile_error));
	((void (__thiscall *const)(c_aim_target_predicted *))0x5890F0)(&event_data.aim_target_predicted.aim_target);
	event_data.aim_target_predicted.primary_auto_aim_level = 0.0f;
	event_data.aim_target_predicted.secondary_auto_aim_level = 0.0f;
	event_data.aiming_vector = global_forward3d;
	if (aim_assist_unit_index != -1)
	{
		s_aim_assist_targeting_result *aim_assist_targeting_result = &object_get<s_unit_data>(aim_assist_unit_index)->aim_assist_data;
		((void (*const)(long, real_vector3d *))0xB43300)(aim_assist_unit_index, &event_data.aiming_vector);
		((void (*const)(s_aim_assist_targeting_result *, s_player_predicted_aim_assist *))0x470CF0)(aim_assist_targeting_result, &event_data.aim_target_predicted);
	}
	event_data.aiming_vector_valid = true;
	event_data.predicted_projectile_fire_data_count = 0;
	event_data.predicted_impact_target_count = 0;
	for (long i = 0; i < projectile_result_count; i++)
	{
		s_simulation_action_projectile_fire_result const *current_fire_result = &projectile_results[i];
		long index = event_data.predicted_projectile_fire_data_count;
		if (current_fire_result->impact_valid)
		{
			long entity_index = ((bool (*const)())0x5319C0)() ? ((long (*const)(long))0x4AF3E0)(current_fire_result->impact_object_index) : ((long (*const)(long))0x4AF520)(current_fire_result->impact_object_index);
			if (entity_index != -1)
			{
				long target_index = 0;
				for (long j = 0; j < event_data.predicted_impact_target_count; j++)
				{
					if (event_data.predicted_impact_targets[j].weapon_fire_impact_entitiy_index == entity_index)
						break;
					target_index++;
				}
				if (target_index == event_data.predicted_impact_target_count)
				{
					event_data.predicted_impact_targets[event_data.predicted_impact_target_count].weapon_fire_impact_entitiy_index = entity_index;
					event_data.predicted_impact_targets[event_data.predicted_impact_target_count].encoding_type = ((unsigned long (*const)(unsigned short))0x46EF20)((unsigned short)current_fire_result->impact_object_index);
					target_index = event_data.predicted_impact_target_count++;
				}
				event_data.predicted_projectile_fire_data[index].object_node_index = current_fire_result->impact_node_index;
				event_data.predicted_projectile_fire_data[index].position = current_fire_result->position;
				event_data.predicted_projectile_fire_data[index].impact_valid = true;
				event_data.predicted_projectile_fire_data[index].target_index = target_index;
			}
		}
		if (current_fire_result->conical_valid)
		{
			event_data.predicted_projectile_fire_data[index].conical_random_seed = current_fire_result->conical_random_seed;
			event_data.predicted_projectile_fire_data[index].conical_valid = true;
		}
		if (event_data.predicted_projectile_fire_data[index].conical_valid || event_data.predicted_projectile_fire_data[index].impact_valid)
		{
			event_data.predicted_projectile_fire_data[index].projectile_creation_id = current_fire_result->projectile_creation_id;
			event_data.predicted_projectile_fire_data_count++;
		}
	}
	if (((bool (*const)(long))0xB617E0)(weapon_index) && ((bool (__thiscall *const)(c_target_tracking_system *))0xB74D90)(&weapon->target_tracking))
	{
		c_aim_target_object *aim_target = ((c_aim_target_object *(__thiscall *const)(c_target_tracking_system *))0xB74D00)(&weapon->target_tracking);
		((bool (__thiscall *const)(c_aim_target_object *, c_aim_target_simulation_entity *))0x589400)(aim_target, &event_data.aim_target_simulation_entity);
	}
	event_data.generated_from_host_live_fire = generated_from_host_live_fire;
	if (generated_from_host_live_fire)
		((void (*const)(long, long, long *, long, void const *))0x4E5B30)(17, 1, object_references, sizeof(event_data), &event_data);
	else
		((void (*const)(e_simulation_event_type, long, long *, long, long, void const *))0x4E5A40)((e_simulation_event_type)17, 1, object_references, player_index, sizeof(event_data), &event_data);
}

void __fastcall c_simulation_weapon_fire_event_definition__apply_game_event_hook(void *thisptr, void *__formal, long a1, long const *object_references, long object_reference_count, s_weapon_fire_event_sending_data *payload) // 0x1069EF80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_simulation_weapon_fire_event_definition__apply_game_event_hook@@YIXPAX0JPBJJPAUs_weapon_fire_event_sending_data@hades_file_local@@@Z");
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
		// s_unit_data *unit;
		// long weapon_set_index;
		// long unit_inventory_index;
		// real_point3d position;
		// real_vector3d *event_data_aiming_vector;
		// real_vector3d aiming_vector;
			// long i;
				// long index;
				// s_weapon_fire_event_sending_data::s_predicted_projectile_fire_data *projectile_element;
				// bool valid;
					// long target_index;
						// long gamestate_index;
							// long predicted_object_index;
								// real_matrix4x3 *node_matrices;
								// long node_index;
								// long node_matrix_count;
		// long v67;
		// long reloading_time;
		// long v57;
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

	if (object_references[0] == -1)
		return;
	long object_index = ((long (*const)(long))0x471F10)(*object_references);
	if (object_index == -1)
		return;
	long object_type = object_get_type(object_index);
	long weapon_control_unit_index = -1;
	long weapon_index = -1;
	if (object_type == 2)
	{
		weapon_index = object_index;
	}
	else
	{
		if (!((1 << object_type) & 0x2003))
			return;
		long unit_inventory_index = payload->unit_inventory_index;
		if (payload->unit_inventory_index < 0)
			return;
		if (unit_inventory_index >= 4)
			return;
		s_unit_data *unit = object_get<s_unit_data>(object_index);
		if (unit->damage_flags & 4)
			return;
		long weapon_set_index = 0;
		while (unit->current_weapon_set.indices[weapon_set_index] != unit_inventory_index)
		{
			weapon_set_index++;
			if (weapon_set_index >= 2)
				return;
		}
		weapon_control_unit_index = ((long (*const)(long))0xB44600)(object_index);
		weapon_index = unit->weapon_object_indices[unit_inventory_index];
	}
	if (weapon_index == -1)
		return;
	s_weapon_data *weapon = object_get<s_weapon_data>(weapon_index);
	s_weapon_definition *weapon_def = (s_weapon_definition *)tag_get('weap', weapon->definition_index);
	if (payload->weapon_definition_index != weapon->definition_index)
		return;
	long barrel_index = payload->barrel_index;
	if (barrel_index < 0 || barrel_index >= weapon_def->barrels.count)
		return;
	s_predicted_weapon_fire_data fire_data;
	memset(&fire_data, 0, sizeof(fire_data));
	fire_data.unit_zoom_level = payload->unit_zoom_level;
	fire_data.tracked_gamestate_index = payload->tracked_gamestate_index;
	fire_data.field_7C = false;
	if (weapon_control_unit_index != -1)
	{
		s_unit_data *unit = object_get<s_unit_data>(weapon_control_unit_index);
		for (long i = 0; i < payload->predicted_projectile_fire_data_count; i++)
		{
			s_weapon_fire_event_sending_data::s_predicted_projectile_fire_data *projectile_element = &payload->predicted_projectile_fire_data[i];
			if (fire_data.predicted_projectile_fire_data_count >= 4)
				continue;
			bool valid = projectile_element->conical_valid || projectile_element->impact_valid;
			if (projectile_element->projectile_creation_id < 0 || projectile_element->projectile_creation_id >= 4 || !valid)
				continue;
			long index = fire_data.predicted_projectile_fire_data_count;
			if (projectile_element->impact_valid)
			{
				long target_index = projectile_element->target_index;
				if (projectile_element->target_index >= 0 && target_index < payload->predicted_impact_target_count)
				{
					long gamestate_index = payload->predicted_impact_targets[target_index].predicted_object_glue_index;
					if (gamestate_index != -1)
					{
						long predicted_object_index = ((long (*const)(long))0x471F10)(gamestate_index);
						if (predicted_object_index != -1)
						{
							long node_matrix_count = 0;
							real_matrix4x3 *node_matrices = ((real_matrix4x3 *(*const)(long, long *))0xB2E400)(predicted_object_index, &node_matrix_count);
							long node_index = projectile_element->object_node_index;
							if (node_index >= 0 && node_index < node_matrix_count)
							{
								matrix4x3_transform_point(&node_matrices[node_index], &projectile_element->position, &fire_data.predicted_projectile_fire_data[index].position);
								fire_data.predicted_projectile_fire_data[index].object_index = predicted_object_index;
								fire_data.predicted_projectile_fire_data[index].impact_valid = true;
							}
						}
					}
				}
			}
			if (projectile_element->conical_valid)
			{
				fire_data.predicted_projectile_fire_data[index].conical_random_seed = projectile_element->conical_random_seed;
				fire_data.predicted_projectile_fire_data[index].conical_valid = true;
			}
			if (fire_data.predicted_projectile_fire_data[index].impact_valid || fire_data.predicted_projectile_fire_data[index].conical_valid)
			{
				fire_data.predicted_projectile_fire_data[index].projectile_id = projectile_element->projectile_creation_id;
				fire_data.predicted_projectile_fire_data_count++;
			}
		}
		real_point3d position;
		((char (*const)(long, real_point3d *))0xB43110)(weapon_control_unit_index, &position);
		real_vector3d *event_data_aiming_vector = nullptr;
		real_vector3d aiming_vector;
		for (long j = 0; j < fire_data.predicted_projectile_fire_data_count; j++)
		{
			if (fire_data.predicted_projectile_fire_data[j].impact_valid)
			{
				aiming_vector = fire_data.predicted_projectile_fire_data[j].position - position;
				normalize3d(&aiming_vector);
				event_data_aiming_vector = &aiming_vector;
				break;
			}
		}
		if (!event_data_aiming_vector && payload->aiming_vector_valid)
			event_data_aiming_vector = &payload->aiming_vector;
		((void (*const)(long, real_vector3d const *, real_vector3d const *))0xB48590)(weapon_control_unit_index, event_data_aiming_vector, event_data_aiming_vector);
		if (((bool (__thiscall *const)(c_aim_target_object *))0x589020)(&payload->aim_target_predicted.aim_assist_data.target_object))
			unit->aim_assist_data = payload->aim_target_predicted.aim_assist_data;
		if (((bool (*const)(long))0xB617E0)(weapon_index) && ((char (__thiscall *const)(c_aim_target_simulation_entity *))0x589050)(&payload->aim_target_simulation_entity))
			((bool (__thiscall *const)(c_target_tracking_system *, c_aim_target_simulation_entity *, s_unit_target_tracking_block *))0xB74E60)(&weapon->target_tracking, &payload->aim_target_simulation_entity, weapon_def->target_tracking.count > 0 ? &weapon_def->target_tracking[0] : nullptr);
	}
	long v67 = game_seconds_to_ticks_round(0.1f);
	short reloading_time;
	if (((bool (*const)(long, long, short *))0xB66220)(weapon_index, -1, &reloading_time))
		((void (*const)(long, bool))0xB676D0)(weapon_index, reloading_time >= 0 && reloading_time <= v67);
	if (weapon->weapon_disabled_by_reload_timer > 0 && weapon->weapon_disabled_by_reload_timer <= v67)
		weapon->weapon_disabled_by_reload_timer = 0;
	if (!payload->generated_from_host_live_fire)
	{
		long v57 = 0;
		long v64 = -1;
		long v67 = -1;
		if (!((char (*const)(long, long, long *, long *, long *))0xB5CE60)(weapon_index, payload->barrel_index, &v57, &v64, &v67))
			return;
		weapon_barrel_fire(weapon_index, (short)payload->barrel_index, ((bool (*const)())0x531D70)());
		if (payload->barrel_should_recover || ((bool (*const)(long, short))0xB608D0)(weapon_index, (short)payload->barrel_index))
			((char (*const)(long, short, bool))0xB60950)(weapon_index, (short)payload->barrel_index, false);
		else
			((long (*const)(long, short))0xB60AE0)(weapon_index, (short)payload->barrel_index);
	}
	((long (*const)(long, short, float))0xB66CB0)(weapon_index, (short)payload->barrel_index, payload->projectile_error);
	((void (*const)(long, s_predicted_weapon_fire_data *, bool, long))0xB62950)(weapon_index, &fire_data, true, payload->generated_from_host_live_fire ? payload->barrel_index : -1);
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
