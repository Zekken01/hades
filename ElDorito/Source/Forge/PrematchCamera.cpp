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
		_extern long _sub_10956360(short);
		long FindCameraObjectForTeamDesignator(short team_designator) // 0x10956360
		{
			mangled_x86(MANGLED_TODO, "?FindCameraObjectForTeamDesignator@PrematchCamera@Forge@@YAJF@Z");
			// static ...; // 0x10956488
			// static ...; // 0x1095647C
			// static ...; // 0x10956474
			// short team_designator;
			// c_data_array<s_object_header> *object_headers;
			// s_forge_globals_definition *forge_globals;
			{
				// c_data_iterator<s_object_header> it;
				{
					// s_multiplayer_object_properties *multiplayer;
				}
			}
			// function call : s_multiplayer_object_properties *(*const)(unsigned long)
			todo("implement");
			long __result = _sub_10956360(team_designator);
			return __result;
		}

		_extern void _sub_10956500(short);
		void PlaceCameraObject(short team) // 0x10956500
		{
			mangled_x86(MANGLED_TODO, "?PlaceCameraObject@PrematchCamera@Forge@@YAXF@Z");
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
			{
				// s_map_variant_placement_properties properties;
				// long prematch_camera_tag_index;
				{
					// s_variant_datum &placement;
					// s_object_data *camera_object;
				}
			}
			// function call : unsigned long (*const)(long)
			// function call : s_map_variant *(*const)()
			// function call : real_matrix4x3 *(*const)(long, real_matrix4x3 *)
			// function call : unsigned __int32 (*const)(s_map_variant *, long, long, long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, long, s_map_variant_placement_properties const *, unsigned short)
			// function call : void (*const)(long, long, s_map_variant_placement_properties const *)
			// function call : void (*const)(bool, long, real_point3d const *, real_vector3d const *, real_vector3d const *)
			todo("implement");
			_sub_10956500(team);
		}

		_extern bool _sub_109564E0();
		bool IsForgePrematchCameraDisabled() // 0x109564E0
		{
			mangled_x86(MANGLED_TODO, "?IsForgePrematchCameraDisabled@PrematchCamera@Forge@@YA_NXZ");
			// procedure flags: nofpo
			todo("implement");
			bool __result = _sub_109564E0();
			return __result;
		}

		_extern void _sub_10956820(bool);
		void SetForgePrematchCameraDisabled(bool disabled) // 0x10956820
		{
			mangled_x86(MANGLED_TODO, "?SetForgePrematchCameraDisabled@PrematchCamera@Forge@@YAX_N@Z");
			// bool disabled;
			todo("implement");
			_sub_10956820(disabled);
		}
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_flags<enum e_multiplayer_team_designator,short>::operator==(short const &) const;
