/* ---------- headers */

#include "hades/hades.h"

#include "Blam/ai/actor.hpp"
#include "Blam/BitStream.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/aim_target.hpp"
#include "Blam/game/engine/game_engine_events.hpp"
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
#include "Blam/models/model_definitions.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/saved_games/scenario_map_variant.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/simulation/simulation_entity_definition.hpp"
#include "Blam/simulation/simulation_game_objects.hpp"
#include "Blam/simulation/simulation_type_collection.hpp"
#include "Blam/simulation/simulation_types.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/structures/structure_bsp_definitions.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeDevice.hpp"
#include "Forge/Geoemetry.hpp"
#include "mods/map_variant_loader.hpp"
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

class c_simulation_type_collection;
struct c_simulation_game_engine_event_definition;
struct real_rectangle3d;
struct real_vector3d;
struct s_aim_assist_targeting_result;
struct s_game_engine_event_data;
struct s_map_variant;
struct s_map_variant_placement_properties;
struct s_model_definition;
struct s_object_data;
struct s_object_definition;
struct s_object_header;
struct s_object_placement_data;
struct s_player_action;
struct s_player_motion;
struct s_scenario;
struct s_scenario_structure_bsp;
struct s_simulation_generic_creation_data;
struct s_simulation_object_creation_data;
struct s_simulation_object_state_data;
struct s_variant_datum;
namespace Blam
{
	class BitStream;
}
namespace hades_file_local
{
	struct s_simulation_reforge_object_creation_datum;
	struct s_simulation_generic_creation_data_v2;
	struct s_simulation_device_state_data;
}
using namespace hades_file_local;

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

namespace hades_file_local
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
using namespace hades_file_local;
/* ---------- prototypes */

extern s_object_header *object_header_get(unsigned long object_index);  // hades: added for 0x10ACF190

extern bool (*const game_is_server)();  // hades: added for 0x10ACF3D0
extern bool (*const game_is_distributed)();  // hades: added for 0x10ACF3D0

extern s_scenario_structure_bsp *(*const global_structure_bsp_get)(long);  // hades: added for 0x10ACF880

namespace Patches { namespace Simulation { extern void apply_unit_entity_patches(); } }  // hades: added for 0x10ACCE60

namespace Patches
{
	namespace HaloScript
	{
		extern void RegisterSimulationTypes(c_simulation_type_collection *collection, __int32 *entity_count, __int32 *event_count);
	}
}

namespace Patches
{
	namespace Simulation
	{
		extern void ApplyAll();
	}
}

void __fastcall c_simulation_generic_entity_definition__entity_creation_encode_hook(void *thisptr, void *unused, __int32 a1, s_simulation_generic_creation_data_v2 *creation_data, unsigned long long *mask, Blam::BitStream *stream, __int32 creation_data_size);
bool __fastcall c_simulation_generic_entity_definition__entity_creation_decode_hook(void *thisptr, void *unused, __int32 creation_data_size, s_simulation_generic_creation_data_v2 *creation_data, Blam::BitStream *bitstream, long a5);
long __fastcall c_simulation_generic_entity_definition__create_object_hook(void *thisptr, void *unused, s_simulation_generic_creation_data_v2 *creation_data, s_simulation_generic_creation_data *object_state_data, long a4, s_object_placement_data *placement_data);
long __fastcall c_simulation_device_entity_definition__create_object_hook(void *thisptr, void *unused, s_simulation_generic_creation_data_v2 *creation_data, s_simulation_device_state_data *state_data, long a4, s_object_placement_data *placement_data);
void __fastcall c_simulation_generic_entity_definition__build_object_creation_data_hook(void *thisptr, void *unused, long object_index, long creation_data_size, s_simulation_generic_creation_data_v2 *creation_data);
bool object_physics_has_powered_chains(long object_definition_index);
bool should_attach_projectile_to_object(long object_index, long projectile_index);
void projectile_attach_to_object_hook();
void simulation_game_build_action_from_motion_data_hook(s_player_motion *motion_data, s_player_action *action);
void simulation_game_build_motion_data_from_action_hook(s_player_action *action, long unit_index, s_player_motion *motion_data);
void simulation_damage_aftermath_hook(long event_type, long a2, long a3, long player_index, long data_size, void *data);
void ragdoll_object_damage_aftermath_hook(long object_index, void *damage_data);
void __fastcall c_simulation_game_engine_event_definition__event_payload_encode_hook(c_simulation_game_engine_event_definition *thisptr, void *unused, long a2, s_game_engine_event_data const *event_data, Blam::BitStream *bitstream, bool a5);
long simulation_entity_type_from_object_creation_ex(long object_definition_index, long parent_object_index, bool is_garbage);
void simulation_action_object_create_build_entity_types(long object_index, long parent_object_index, long max_entity_count, long *out_entity_count, long *out_entity_types, long *out_object_indices);
void simulation_action_object_recapture_creation_data_hook(long object_index);
void simulation_game_register_types_hook(c_simulation_type_collection *type_collection, __int32 *entity_type_count, __int32 *event_type_count);
void __fastcall c_simulation_event_handler__send_event_hook(void *thisptr, void *unused, e_simulation_event_type event_type, long num_entity_references, long *entity_references, long recipient_peer_mask, long payload_size, void const *payload, long grief_time);
bool player_action_decode_validate_hook(s_player_action *action);
real_rectangle3d *simulation_encoding_get_world_bounds_hook(real_rectangle3d *out_world_bounds);
void simulation_encoding_get_world_bounds__object_handle_update_hook(real_rectangle3d *out_world_bounds);

/* ---------- globals */

extern s_map_variant *(*const game_engine_get_runtime_map_variant)();  // hades: added for 0X10ACEA10
namespace Forge { extern bool ObjectIsForgeScenery(long objectIndex); }  // hades: added for 0X10ACEA10
namespace Forge { extern void ScaleForgeSceneryObject(long objectIndex, float scale); }  // hades: added for 0X10ACEA10

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>); // 0x11248848

/* ---------- private variables */

namespace hades_file_local
{
	extern real_rectangle3d global_null_rectangle3d; // 0x111B22E0
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Simulation
	{
		void ApplyAll() // 0x10ACCE60
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Simulation@Patches@@YAXXZ");

			Pointer(0x163FE48).Write<unsigned int>(reinterpret_cast<unsigned int>(c_simulation_game_engine_event_definition__event_payload_encode_hook));
			Pointer(0x1642F58).Write(c_simulation_generic_entity_definition__entity_creation_encode_hook);
			Pointer(0x1643150).Write(c_simulation_generic_entity_definition__entity_creation_encode_hook);
			Pointer(0x1642F5C).Write(c_simulation_generic_entity_definition__entity_creation_decode_hook);
			Pointer(0x1643154).Write(c_simulation_generic_entity_definition__entity_creation_decode_hook);
			Pointer(0x1642F98).Write(c_simulation_generic_entity_definition__build_object_creation_data_hook);
			Pointer(0x1643190).Write(c_simulation_generic_entity_definition__build_object_creation_data_hook);
			Hook(0xC8E91, c_simulation_generic_entity_definition__create_object_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0xCE772, c_simulation_device_entity_definition__create_object_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0xC9B37, c_simulation_generic_entity_definition__create_object_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0x4C8F01).Write<unsigned int>(0x54);
			Pointer(0x4C9B91).Write<unsigned int>(0x54);
			Hook(0x77862A, projectile_attach_to_object_hook).Apply();
			Hook(0xA7880, simulation_game_build_action_from_motion_data_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0xA7A17, simulation_game_build_motion_data_from_action_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0xA77BF, simulation_game_build_motion_data_from_action_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch::NopFill(Pointer::Base(0x74C4E7), 6);
			Hook(0xB22C4, simulation_damage_aftermath_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x754226, 0x90, 12).Apply();
			Hook(0x7543DF, ragdoll_object_damage_aftermath_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0xC8E37, tag_get, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0xB2CD0, simulation_action_object_recapture_creation_data_hook).Apply();
			Hook(0xAFA90, simulation_entity_type_from_object_creation_ex).Apply();
			Hook(0x419FF, simulation_game_register_types_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0xE5A15, c_simulation_event_handler__send_event_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0xE5B1B, c_simulation_event_handler__send_event_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0xE5723, c_simulation_event_handler__send_event_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0x4A87E2).Write<signed char>(0x40);
			Hook(0x6E217, player_action_decode_validate_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x6EE60, simulation_encoding_get_world_bounds_hook).Apply();
			Hook(0xAD910, simulation_encoding_get_world_bounds__object_handle_update_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patches::Simulation::apply_unit_entity_patches();
		}
	}
}

/* ---------- private code */

void __fastcall c_simulation_generic_entity_definition__entity_creation_encode_hook(void *thisptr, void *unused, __int32 a1, s_simulation_generic_creation_data_v2 *creation_data, unsigned long long *mask, Blam::BitStream *stream, __int32 creation_data_size) // 0x10ACECE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_simulation_generic_entity_definition__entity_creation_encode_hook@@YIXPAX0HPAUs_simulation_generic_creation_data_v2@hades_file_local@@PA_KPAVBitStream@Blam@@H@Z");

	((void (__thiscall *)(void *, __int32, s_simulation_object_creation_data *, unsigned long long *, Blam::BitStream *, __int32))0x4c8fa0)(thisptr, a1, creation_data, mask, stream, creation_data_size);

	if (creation_data->map_variant_index != -1)
	{
		s_simulation_reforge_object_creation_datum *datum = &creation_data->reforge;

		stream->WriteBool(datum->valid);

		if (datum->valid)
		{
			stream->WriteBlock(0x200, (unsigned char const *)datum);
		}
	}
}

bool __fastcall c_simulation_generic_entity_definition__entity_creation_decode_hook(void *thisptr, void *unused, __int32 creation_data_size, s_simulation_generic_creation_data_v2 *creation_data, Blam::BitStream *bitstream, long a5) // 0x10ACEBC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_simulation_generic_entity_definition__entity_creation_decode_hook@@YI_NPAX0HPAUs_simulation_generic_creation_data_v2@hades_file_local@@PAVBitStream@Blam@@J@Z");

	bool ret = ((bool (__thiscall *)(void *, __int32, s_simulation_generic_creation_data_v2 *, Blam::BitStream *, long))0x4C8F50)(thisptr, creation_data_size, creation_data, bitstream, a5);
	s_simulation_reforge_object_creation_datum *datum = &creation_data->reforge;
	if (creation_data->map_variant_index != -1)
	{
		bool valid = bitstream->ReadBool();
		if (valid)
		{
			bitstream->ReadBlock(0x200, (unsigned char *)datum);
			datum->valid = true;
		}
	}
	return ret && bitstream->StreamBitPosition() <= bitstream->SizeBytes() * 8;
}

long __fastcall c_simulation_generic_entity_definition__create_object_hook(void *thisptr, void *unused, s_simulation_generic_creation_data_v2 *creation_data, s_simulation_generic_creation_data *object_state_data, long a4, s_object_placement_data *placement_data) // 0x10ACEA10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_simulation_generic_entity_definition__create_object_hook@@YIJPAX0PAUs_simulation_generic_creation_data_v2@hades_file_local@@PAUs_simulation_generic_creation_data@@JPAUs_object_placement_data@@@Z");

	void (__thiscall *const c_map_variant__apply_variant_properties_to_object)(s_map_variant *, s_map_variant_placement_properties *, long) = (void(__thiscall *const)(s_map_variant *, s_map_variant_placement_properties *, long))0x580e80;

	if (creation_data->map_variant_index != -1 && creation_data->reforge.valid)
	{
		s_simulation_reforge_object_creation_datum *datum = &creation_data->reforge;

		placement_data->relative_position = datum->position;
		placement_data->forward = datum->forward;
		placement_data->up = datum->up;
	}

	long object_index = ((long (__thiscall *)(void *, s_simulation_generic_creation_data_v2 *, s_simulation_generic_creation_data *, long, s_object_placement_data *))0x4ad3e0)(thisptr, creation_data, object_state_data, a4, placement_data);

	if (object_index != -1 && creation_data->map_variant_index != -1 && creation_data->reforge.valid)
	{
		c_map_variant__apply_variant_properties_to_object(game_engine_get_runtime_map_variant(), &creation_data->reforge.properties, object_index);

		if (Forge::ObjectIsForgeScenery(object_index))
		{
			Forge::ScaleForgeSceneryObject(object_index, creation_data->reforge.properties.boundry_width);
		}
	}

	return object_index;
}

long __fastcall c_simulation_device_entity_definition__create_object_hook(void *thisptr, void *unused, s_simulation_generic_creation_data_v2 *creation_data, s_simulation_device_state_data *state_data, long a4, s_object_placement_data *placement_data) // 0x10ACE620
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_simulation_device_entity_definition__create_object_hook@@YIJPAX0PAUs_simulation_generic_creation_data_v2@hades_file_local@@PAUs_simulation_device_state_data@2@JPAUs_object_placement_data@@@Z");

	// The original folds `create_object' to an immediate and gives it no stack slot, so it
	// cannot be a `const' local here -- that would allocate one.
	long object_index = ((long (__thiscall *)(void *, s_simulation_generic_creation_data_v2 *, s_simulation_device_state_data *, long, s_object_placement_data *))0x4ad3e0)(thisptr, creation_data, state_data, a4, placement_data);

	if (creation_data->map_variant_index != -1 && creation_data->scenario_datum_index == -1)
	{
		Utils::Singleton<CForgeDeviceManager>::Instance().InitializeDeviceObject(object_index);
	}

	return object_index;
}

void __fastcall c_simulation_generic_entity_definition__build_object_creation_data_hook(void *thisptr, void *unused, long object_index, long creation_data_size, s_simulation_generic_creation_data_v2 *creation_data) // 0x10ACE850
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_simulation_generic_entity_definition__build_object_creation_data_hook@@YIXPAX0JJPAUs_simulation_generic_creation_data_v2@hades_file_local@@@Z");

	static void (__thiscall *const build_object_creation_data)(void *, long, long, s_simulation_generic_creation_data_v2 *) = reinterpret_cast<void (__thiscall *)(void *, long, long, s_simulation_generic_creation_data_v2 *)>(0x4C8D70);
	build_object_creation_data(thisptr, object_index, creation_data_size, creation_data);
	s_simulation_reforge_object_creation_datum *datum = &creation_data->reforge;
	datum->valid = false;
	if (creation_data->map_variant_index == -1)
		return;
	s_object_data *object = object_try_and_get_and_verify_type(object_index, -1);
	if (object && object->map_variant_index != -1)
	{
		s_map_variant *map_variant = game_engine_get_runtime_map_variant();
		s_variant_datum *placement = &map_variant->objects[object->map_variant_index];
		datum->position = placement->position;
		datum->forward = placement->forward;
		datum->up = placement->up;
		datum->properties = static_cast<s_map_variant_placement_properties const &>(placement->properties);
		datum->valid = true;
	}
}

bool object_physics_has_powered_chains(long object_definition_index) // 0x10ACEDE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_physics_has_powered_chains@@YA_NJ@Z");

	s_object_definition *object_definition = (s_object_definition *)tag_get(0x6F626A65, object_definition_index);

	if (object_definition->model.index == -1)
	{
		return false;
	}

	s_model_definition *model = (s_model_definition *)tag_get(0x686C6D74, object_definition->model.index);

	if (model->physics_model.index == -1)
	{
		return false;
	}

	char *physics_model = (char *)tag_get(0x70686D6F, model->physics_model.index);
	unsigned long flags = *(unsigned long *)physics_model;

	return (flags & 2) != 0 && *(long *)(physics_model + 0x40) > 0;
}

bool should_attach_projectile_to_object(long object_index, long projectile_index) // 0x10ACF0A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?should_attach_projectile_to_object@@YA_NJJ@Z");

	s_object_data *object = object_try_and_get_and_verify_type(object_index, -1);

	if (!object)
	{
		return false;
	}

	return object->multiplayer.offset == -1 || !((bool (*)(long))0x59a7b0)(object_index);
}

__declspec(naked) void projectile_attach_to_object_hook() // 0x10ACEFF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?projectile_attach_to_object_hook@@YAXXZ");

	__asm
	{
		pushad
		push dword ptr [ebp + 8]
		push dword ptr [ebp + 0Ch]
		call should_attach_projectile_to_object
		add esp, 8
		test al, al
		popad
		jne LATTACH
		mov eax, 0B786C8h
		jmp eax
		LATTACH:
		mov eax, 0B78630h
		jmp eax
	}
}

void simulation_game_build_action_from_motion_data_hook(s_player_motion *motion_data, s_player_action *action) // 0x10ACFE00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?simulation_game_build_action_from_motion_data_hook@@YAXPAUs_player_motion@@PAUs_player_action@@@Z");

	((void (*)(s_player_motion *, s_player_action *))0x4712d0)(motion_data, action);

	if (motion_data->action_flags & 0x20)
	{
		action->control_flags |= 4;
	}
	else
	{
		action->control_flags &= ~4;
	}
}

void simulation_game_build_motion_data_from_action_hook(s_player_action *action, long unit_index, s_player_motion *motion_data) // 0x10ACFE90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?simulation_game_build_motion_data_from_action_hook@@YAXPAUs_player_action@@JPAUs_player_motion@@@Z");

	((void (*)(s_player_action *, long, s_player_motion *))0x4708f0)(action, unit_index, motion_data);

	if (action->control_flags & 4)
	{
		motion_data->action_flags |= 0x20;
	}
	else
	{
		motion_data->action_flags &= ~0x20;
	}
}

void simulation_damage_aftermath_hook(long event_type, long a2, long a3, long player_index, long data_size, void *data) // 0x10ACF770
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?simulation_damage_aftermath_hook@@YAXJJJJJPAX@Z");

	*(bool *)((unsigned char *)data + 0xa) = true;
	((void(__cdecl *const)(long, long, long, long, long, void *))0x4e5a30)(event_type, a2, a3, player_index, data_size, data);
}

void ragdoll_object_damage_aftermath_hook(long object_index, void *damage_data) // 0x10ACF020
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ragdoll_object_damage_aftermath_hook@@YAXJPAX@Z");

	void (__cdecl *const object_deal_damage)(__int32, void *) = (void(__cdecl *const)(__int32, void *))0xb52c50;

	*(long *)((unsigned char *)damage_data + 0x54) = 1;
	object_deal_damage(object_index, damage_data);
}

void __fastcall c_simulation_game_engine_event_definition__event_payload_encode_hook(c_simulation_game_engine_event_definition *thisptr, void *unused, long a2, s_game_engine_event_data const *event_data, Blam::BitStream *bitstream, bool a5) // 0x10ACE780
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_simulation_game_engine_event_definition__event_payload_encode_hook@@YIXPAUc_simulation_game_engine_event_definition@@PAXJPBUs_game_engine_event_data@@PAVBitStream@Blam@@_N@Z");

	((void (__thiscall *)(c_simulation_game_engine_event_definition *, long, s_game_engine_event_data const *, Blam::BitStream *, bool))0x4b6310)(thisptr, a2, event_data, bitstream, a5);

	if (event_data->type == _game_engine_event_type_territories)
	{
		bitstream->WriteUnsigned<unsigned char>(event_data->territory_index + 1, 4);
	}
}

long simulation_entity_type_from_object_creation_ex(long object_definition_index, long parent_object_index, bool is_garbage) // 0x10ACFA00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?simulation_entity_type_from_object_creation_ex@@YAJJJ_N@Z");

	s_object_definition *definition = (s_object_definition *)tag_get('obje', object_definition_index);
	if (definition->object_type == _object_type_biped || definition->object_type == _object_type_giant)
		return 14;
	else if (definition->object_type == _object_type_weapon)
		return parent_object_index != -1 ? -1 : 20;
	else if (definition->object_type == _object_type_vehicle)
		return 18;
	else if (definition->object_type == _object_type_equipment)
		return 15;
	else if (definition->object_type == _object_type_crate)
	{
		if (definition->model.index == -1 || object_physics_has_powered_chains(object_definition_index))
			return -1;
		return is_garbage ? 17 : 16;
	}
	else if (definition->object_type == _object_type_projectile)
		return 19;
	else if (definition->object_type == _object_type_terminal || definition->object_type == _object_type_machine || definition->object_type == _object_type_control)
		return 21;
	else if (definition->object_type == _object_type_scenery)
		return parent_object_index != -1 ? -1 : 16;
	return -1;
}

void simulation_action_object_create_build_entity_types(long object_index, long parent_object_index, long max_entity_count, long *out_entity_count, long *out_entity_types, long *out_object_indices) // 0x10ACF190
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?simulation_action_object_create_build_entity_types@@YAXJJJPAJ00@Z");

	s_object_header *object_header = object_header_get(object_index);
	s_object_data *object = object_header->data;
	bool object_sync_disabled = reinterpret_cast<bool (*)(long)>(0xB2F300)(object_index);
	long root_parent_object_index = reinterpret_cast<long (*)(long)>(0xB2EAB0)(object_index);
	bool root_parent_sync_disbaled = reinterpret_cast<bool (*)(long)>(0xB2F300)(root_parent_object_index);
	if (!(object_header->flags & 0x10) && object->simulation_object_glue_index == -1 && !object_sync_disabled && !root_parent_sync_disbaled)
	{
		long entity_type = simulation_entity_type_from_object_creation_ex(object->definition_index, parent_object_index, (object->recycling_flags & 2) != 0);
		if (entity_type != -1 && *out_entity_count < max_entity_count)
		{
			out_entity_types[*out_entity_count] = entity_type;
			out_object_indices[(*out_entity_count)++] = object_index;
			for (long child_object_index = object->first_child_object_index; child_object_index != -1; child_object_index = object->next_object_index)
			{
				object = object_get(child_object_index);
				if ((long)object->object_flags & 0x4000000)
					simulation_action_object_create_build_entity_types(child_object_index, object_index, max_entity_count, out_entity_count, out_entity_types, out_object_indices);
			}
		}
	}
}

void simulation_action_object_recapture_creation_data_hook(long object_index) // 0x10ACF3D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?simulation_action_object_recapture_creation_data_hook@@YAXJ@Z");

	struct s_simulation_entity;
	struct c_simulation_world { unsigned char __pad0[4]; void *replication_manager; };
	static s_simulation_entity * (__thiscall *const c_simulation_entity_database__entity_get)(void *, long) = (s_simulation_entity * (__thiscall *)(void *, long))0x4A63D0;
	static long (*const object_attach_simulation_object_glue)(long, long) = (long (*)(long, long))0xB29F20;
	static void (*const simulation_object_glue_set_object_index)(long, long) = (void (*)(long, long))0x471FF0;
	static void (__thiscall *const c_simulation_entity_database__entity_capture_creation_data)(void *, long) = (void (__thiscall *)(void *, long))0x4A6110;
	static c_simulation_world * (*const simulation_get_world)() = (c_simulation_world * (*)())0x441940;
	static bool (*const game_is_playback)() = (bool (*)())0x531D10;
	static long (*const simulation_object_glue_create)() = (long (*)())0x471E10;
	static long (*const simulation_entity_create)(long, long, long) = (long (*)(long, long, long))0x4AF8A0;
	if (!game_is_server() || !game_is_distributed())
		return;
	s_static_array<long,32> entity_types;
	s_static_array<long,32> object_indices;
	long entity_type_count = 0;
	simulation_action_object_create_build_entity_types(object_index, -1, entity_types.get_count(), &entity_type_count, &entity_types[0], &object_indices[0]);
	for (long i = 0; i < entity_type_count; i++)
	{
		long object_index = object_indices[i];
		long object_glue_index = simulation_object_glue_create();
		object_attach_simulation_object_glue(object_index, object_glue_index);
		simulation_object_glue_set_object_index(object_glue_index, object_index);
		if (!game_is_playback())
		{
			long entity_index = simulation_entity_create(entity_types[i], object_indices[i], object_glue_index);
			if (entity_index != -1)
			{
				void *replication_manager = simulation_get_world()->replication_manager;
				void *entity_database = (char *)replication_manager + 0x10A0;
				c_simulation_entity_database__entity_get(entity_database, entity_index);
				c_simulation_entity_database__entity_capture_creation_data(entity_database, entity_index);
			}
		}
	}
}

void simulation_game_register_types_hook(c_simulation_type_collection *type_collection, __int32 *entity_type_count, __int32 *event_type_count) // 0x10ACFF60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?simulation_game_register_types_hook@@YAXPAVc_simulation_type_collection@@PAH1@Z");

	void (*const simulation_game_register_types)(c_simulation_type_collection *, __int32 *, __int32 *) = (void (*const)(c_simulation_type_collection *, __int32 *, __int32 *))0x4715d0;

	simulation_game_register_types(type_collection, entity_type_count, event_type_count);

	__int32 additional_entity_types = 0;
	__int32 additional_event_types = 0;

	Player::CPlayerEmotes::RegisterSimulationTypes(type_collection, &additional_entity_types, &additional_event_types);
	Patches::HaloScript::RegisterSimulationTypes(type_collection, &additional_entity_types, &additional_event_types);

	*entity_type_count += additional_entity_types;
	*event_type_count += additional_event_types;
}

void __fastcall c_simulation_event_handler__send_event_hook(void *thisptr, void *unused, e_simulation_event_type event_type, long num_entity_references, long *entity_references, long recipient_peer_mask, long payload_size, void const *payload, long grief_time) // 0x10ACE6E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_simulation_event_handler__send_event_hook@@YIXPAX0W4e_simulation_event_type@@JPAJJJPBXJ@Z");

	void (__thiscall *const c_simulation_event_handler__send_event)(void *, e_simulation_event_type, long, long *, long, long, void const *, long) = (void(__thiscall *const)(void *, e_simulation_event_type, long, long *, long, long, void const *, long))0x4a7500;

	if (event_type >= _simulation_event_type_hs_wake_script)
	{
		grief_time = 5000;
	}

	c_simulation_event_handler__send_event(thisptr, event_type, num_entity_references, entity_references, recipient_peer_mask, payload_size, payload, grief_time);
}

bool player_action_decode_validate_hook(s_player_action *action) // 0x10ACEF30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_action_decode_validate_hook@@YA_NPAUs_player_action@@@Z");

	bool (__cdecl *const player_action_decode_validate)(s_player_action *) = (bool(__cdecl *const)(s_player_action *))0x537ab0;
	bool (__cdecl *const aim_assist_targeting_result_valid)(void *) = (bool(__cdecl *const)(void *))0x58cf40;
	void (__cdecl *const aim_assist_targeting_result_build_default)(void *) = (void(__cdecl *const)(void *))0x58cc50;

	if (!aim_assist_targeting_result_valid(&action->aim_assist_targeting_result))
	{
		aim_assist_targeting_result_build_default(&action->aim_assist_targeting_result);
	}

	return player_action_decode_validate(action);
}

real_rectangle3d *simulation_encoding_get_world_bounds_hook(real_rectangle3d *out_world_bounds) // 0x10ACF880
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?simulation_encoding_get_world_bounds_hook@@YAPAUreal_rectangle3d@@PAU1@@Z");

	void (*const real_rectangle3d_enclose_rectangle)(real_rectangle3d *, real_rectangle3d *) = reinterpret_cast<void (*)(real_rectangle3d *, real_rectangle3d *)>(0x4FBF30);
	s_scenario *scenario = global_scenario_get();
	*out_world_bounds = global_null_rectangle3d;
	for (long i = 0; i < 16; i++)
	{
		if (!((1 << i) & *(unsigned long *)0x22AAEBC))
			continue;
		if (scenario->structure_bsps[i].flags.test(s_scenario_structure_bsp_reference::_not_multiplayer_playable_space_bit))
			continue;
		s_scenario_structure_bsp *sbsp = global_structure_bsp_get(i);
		real_rectangle3d_enclose_rectangle(out_world_bounds, &sbsp->world_bounds);
	}
	return out_world_bounds;
}

void simulation_encoding_get_world_bounds__object_handle_update_hook(real_rectangle3d *out_world_bounds) // 0x10ACF7F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?simulation_encoding_get_world_bounds__object_handle_update_hook@@YAXPAUreal_rectangle3d@@@Z");

	out_world_bounds->x0 = -FLT_MAX;
	out_world_bounds->x1 = FLT_MAX;
	out_world_bounds->y0 = -FLT_MAX;
	out_world_bounds->y1 = FLT_MAX;
	out_world_bounds->z0 = -FLT_MAX;
	out_world_bounds->z1 = FLT_MAX;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_enum<enum e_game_engine_event_type,char>::operator==(e_game_engine_event_type const &) const;
template bool c_enum<enum e_object_type,short>::operator==(e_object_type const &) const;
template bool c_flags<enum s_scenario_structure_bsp_reference::e_flags,unsigned short>::test(s_scenario_structure_bsp_reference::e_flags) const;
template bool s_static_array<long,32>::valid(__int32);
template c_flags<enum e_object_datum_flags,unsigned char> c_flags<enum e_object_datum_flags,unsigned char>::operator&(__int32 const) const;
template c_flags<enum e_object_datum_flags,unsigned char>::c_flags(unsigned char const &);
template c_flags<enum e_object_datum_flags,unsigned char>::operator bool() const;
template c_flags<enum e_object_flags,long>::operator long() const;
template c_flags<enum e_unit_control_flags,unsigned long> & c_flags<enum e_unit_control_flags,unsigned long>::operator&=(__int32 const);
template c_flags<enum e_unit_control_flags,unsigned long> & c_flags<enum e_unit_control_flags,unsigned long>::operator|=(__int32 const);
template c_flags<enum e_unit_control_flags,unsigned long> c_flags<enum e_unit_control_flags,unsigned long>::operator&(__int32 const) const;
template c_flags<enum e_unit_control_flags,unsigned long>::c_flags(unsigned long const &);
template c_flags<enum e_unit_control_flags,unsigned long>::operator bool() const;
template long & s_static_array<long,32>::operator[](long);
template long s_static_array<long,32>::get_count();
template void Blam::BitStream::WriteUnsigned<unsigned char>(unsigned char, __int32);

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { real_rectangle3d global_null_rectangle3d; }
