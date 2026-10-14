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
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/saved_games/scenario_map_variant.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Geoemetry.hpp"
#include "mods/map_variant_loader.hpp"

/* ---------- forward declarations */

struct real_matrix4x3;
struct real_point3d;
struct real_vector3d;
struct s_forge_globals_definition;
struct s_map_variant;
struct s_map_variant_placement_properties;
struct s_multiplayer_object_properties;
struct s_object_data;
struct s_object_header;
struct s_player_datum;
struct s_variant_datum;

namespace Forge {}
using namespace ::Forge;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Forge
{
	namespace PrematchCamera
	{
		extern long FindCameraObjectForTeamDesignator(short team_designator);
		extern void PlaceCameraObject(short team);
		extern bool IsForgePrematchCameraDisabled();
		extern void SetForgePrematchCameraDisabled(bool disabled);
	}
}

extern s_multiplayer_object_properties *(*const object_get_multiplayer)(unsigned long); extern s_map_variant *(*const game_engine_get_runtime_map_variant)();  // hades: added for 0x10956360, 0x10956500

/* ---------- globals */

namespace Forge
{
	namespace PrematchCamera
	{
		extern bool prematchCameraDisabled; // 0x1240F660
	}
}

/* ---------- private variables */

/* ---------- public code */

namespace Forge
{
	namespace PrematchCamera
	{
		long FindCameraObjectForTeamDesignator(short team_designator) // 0x10956360
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?FindCameraObjectForTeamDesignator@PrematchCamera@Forge@@YAJF@Z");
			// static ...; // 0x10956488
			// static ...; // 0x1095647C
			// static ...; // 0x10956474
			// short team_designator;
			// c_data_array<s_object_header> *object_headers;
			// s_forge_globals_definition *forge_globals;
				// c_data_iterator<s_object_header> it;
					// s_multiplayer_object_properties *multiplayer;
			// function call : s_multiplayer_object_properties *(*const)(unsigned long)

			s_forge_globals_definition *forge_globals = forge_globals_get_definition();
			if (!forge_globals)
				return -1;
			if (forge_globals->prematch_camera_object.index == -1)
				return -1;
			c_data_array<s_object_header> *object_headers = object_headers_get();
			for (c_data_iterator<s_object_header> it = object_headers->begin(); it != object_headers->end(); ++it)
			{
				if (it->data->definition_index == forge_globals->prematch_camera_object.index)
				{
					s_multiplayer_object_properties *multiplayer = object_get_multiplayer(it.current_datum_index);
					if (multiplayer && multiplayer->team_designator == team_designator)
						return it.current_datum_index;
				}
			}
			return -1;
		}

		void PlaceCameraObject(short team) // 0x10956500
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PlaceCameraObject@PrematchCamera@Forge@@YAXF@Z");
			// static ...; // 0x1095676B
			// static ...; // 0x10956760
			// static ...; // 0x10956748
			// static ...; // 0x10956740
			// short team;
			// s_player_datum *player;
			// long player_index;
			// real_matrix4x3 unit_world_matrix;
			// void (*const game_engine_sandbox_update_variant_object_properties)(long, long, s_map_variant_placement_properties const *);
			// unsigned __int32 (*const spawn_object)(s_map_variant *, long, long, long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, long, s_map_variant_placement_properties const *, unsigned short);
			// s_map_variant *map_variant;
			// long camera_object_index;
				// s_map_variant_placement_properties properties;
				// long prematch_camera_tag_index;
					// s_variant_datum &placement;
					// s_object_data *camera_object;
			// function call : unsigned long (*const)(long)
			// function call : s_map_variant *(*const)()
			// function call : real_matrix4x3 *(*const)(long, real_matrix4x3 *)
			// function call : unsigned __int32 (*const)(s_map_variant *, long, long, long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, long, s_map_variant_placement_properties const *, unsigned short)
			// function call : void (*const)(long, long, s_map_variant_placement_properties const *)
			// function call : void (*const)(bool, long, real_point3d const *, real_vector3d const *, real_vector3d const *)

			unsigned __int32 (__thiscall *const spawn_object)(s_map_variant *, long, long, long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, long, s_map_variant_placement_properties const *, unsigned short) = (unsigned __int32 (__thiscall *)(s_map_variant *, long, long, long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, long, s_map_variant_placement_properties const *, unsigned short))0x582110;
			void (*const game_engine_sandbox_update_variant_object_properties)(long, long, s_map_variant_placement_properties const *) = (void (*)(long, long, s_map_variant_placement_properties const *))0x59B720;
			long player_index = ((unsigned long (*const)(long))0x589C30)(0);
			if (player_index == -1)
				return;
			s_player_datum *player = player_get(player_index);
			if (!player || player->unit_index == -1)
				return;
			s_map_variant *map_variant = game_engine_get_runtime_map_variant();
			real_matrix4x3 unit_world_matrix;
			((real_matrix4x3 *(*const)(long, real_matrix4x3 *))0xB2EC60)(player->unit_index, &unit_world_matrix);
			long camera_object_index = FindCameraObjectForTeamDesignator(team);
			if (camera_object_index == -1)
			{
				s_map_variant_placement_properties properties = {};
				properties.team_affiliation = (char)team;
				long prematch_camera_tag_index = forge_globals_get_definition()->prematch_camera_object.index;
				camera_object_index = spawn_object(map_variant, prematch_camera_tag_index, -1, -1, &unit_world_matrix.position, &unit_world_matrix.forward, &unit_world_matrix.up, -1, -1, &properties, 0);
				if (camera_object_index != -1)
				{
					s_object_data *camera_object = object_get(camera_object_index);
					s_variant_datum &placement = map_variant->objects[camera_object->map_variant_index];
					placement.properties.boundry_shape = 4;
					game_engine_sandbox_update_variant_object_properties(player_index, camera_object->map_variant_index, &placement.properties);
				}
			}
			else
			{
				((void (*const)(bool, long, real_point3d const *, real_vector3d const *, real_vector3d const *))0x59E340)(false, camera_object_index, &unit_world_matrix.position, &unit_world_matrix.forward, &unit_world_matrix.up);
			}
		}

		bool IsForgePrematchCameraDisabled() // 0x109564E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?IsForgePrematchCameraDisabled@PrematchCamera@Forge@@YA_NXZ");
			// procedure flags: nofpo

			return prematchCameraDisabled;
		}

		void SetForgePrematchCameraDisabled(bool disabled) // 0x10956820
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetForgePrematchCameraDisabled@PrematchCamera@Forge@@YAX_N@Z");
			// bool disabled;

			prematchCameraDisabled = disabled;
		}
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_flags<enum e_multiplayer_team_designator,short>::operator==(short const &) const;
