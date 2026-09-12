/* ---------- headers */

#include "Forge/ForgeUtil.hpp"
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
#include "Blam/interface/chud/chud_messaging.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/models/model_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/render/render_model.hpp"
#include "Blam/saved_games/scenario_map_variant.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Geoemetry.hpp"
#include "mods/map_variant_loader.hpp"
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

/* ---------- forward declarations */

struct real_matrix4x3;
struct real_point3d;
struct real_rectangle3d;
struct real_vector3d;
struct s_map_variant;
struct s_map_variant_placement_properties;
struct s_model_definition;
struct s_multiplayer_object_properties;
struct s_object_data;
struct s_object_definition;
struct s_player_datum;
struct s_render_model;
struct s_variant_datum;
namespace Forge
{
	struct ForgeObjectQuota;
}

namespace Forge {}
using namespace ::Forge;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Forge
{
	extern s_map_variant *GetMapVariant();
	extern void PrintKillFeedText(long user_index, wchar_t const *message, long unused);
	extern real_rectangle3d const *GetObjectBoundingBox(long tag_index);
	extern void DeleteObject(long player_index, long map_variant_index);
	extern long CloneObject(long player_index, long object_index, float depth, real_vector3d const &normal);
	extern void ThrowObject(long player_index, long object_index, float throwForce);
	extern real_vector3d GetClosestCardianalAxix(real_vector3d const &v);
	extern Forge::ForgeObjectQuota CalculateObjectQuota();
	extern bool PointInWorldBounds(real_point3d const &point);
	extern bool ObjectInWorldBounds(long objectIndex);
	extern void SetObjectPhysicsMode(long objectIndex, Forge::EForgeObjectPhysics mode, bool atRest);
	extern Forge::EForgeObjectPhysics GetObjectPhysicsMode(long objectIndex);
	extern bool ObjectIsForgeScenery(long objectIndex);
	extern void ScaleForgeSceneryObject(long objectIndex, float scale);
}

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern real_vector3d global_zero3d; // 0x1119A698
}
using namespace hades_file_local;
/* ---------- public code */

extern s_map_variant *_sub_109699F0();
namespace Forge
{
	s_map_variant *GetMapVariant() // 0x109699F0
	{
		mangled_x86(MANGLED_TODO, "?GetMapVariant@Forge@@YAPAUs_map_variant@@XZ");
		// procedure flags: nofpo
		// function call : s_map_variant *(*const)()
		todo("implement");
		s_map_variant * __result = _sub_109699F0();
		return __result;
	}

	void PrintKillFeedText(long user_index, wchar_t const *message, long unused) // 0x10969F50
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?PrintKillFeedText@Forge@@YAXJPB_WJ@Z");
		// long unused;
		// function call : void (*const)(long, wchar_t const *, e_chud_message_context)

		((void(__cdecl *const)(long, wchar_t const *, e_chud_message_context))0xa95920)(user_index, message, (e_chud_message_context)0);
	}
}

extern real_rectangle3d const *_sub_10969A40(long);
namespace Forge
{
	real_rectangle3d const *GetObjectBoundingBox(long tag_index) // 0x10969A40
	{
		mangled_x86(MANGLED_TODO, "?GetObjectBoundingBox@Forge@@YAPBUreal_rectangle3d@@J@Z");
		// long tag_index;
		// s_object_definition *object_definition;
		// s_model_definition *model;
		// s_render_model *render_model;
		// function call : void *(*const)(unsigned long, long)
		// function call : void *(*const)(unsigned long, long)
		// function call : void *(*const)(unsigned long, long)
		todo("implement");
		real_rectangle3d const * __result = _sub_10969A40(tag_index);
		return __result;
	}

	void DeleteObject(long player_index, long map_variant_index) // 0x109695C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?DeleteObject@Forge@@YAXJJ@Z");
		// long map_variant_index;
		// void (*const game_engine_sandbox_apply_delete_object)(long, long);
		// function call : void (*const)(long, long)

		void (__cdecl *const game_engine_sandbox_apply_delete_object)(long, long) = (void(__cdecl *const)(long, long))0x59cbe0;

		game_engine_sandbox_apply_delete_object(player_index, map_variant_index);
	}

	_extern long _sub_10968A20(long, long, float, real_vector3d const &);
	long CloneObject(long player_index, long object_index, float depth, real_vector3d const &normal) // 0x10968A20
	{
		mangled_x86(MANGLED_TODO, "?CloneObject@Forge@@YAJJJMABUreal_vector3d@@@Z");
		// static ...; // 0x1096932C
		// static ...; // 0x109692FC
		// static ...; // 0x109692F4
		// long player_index;
		// long object_index;
		// float depth;
		// real_vector3d const &normal;
		// real_vector3d intersectNormal;
		// s_object_data *object;
		// real_rectangle3d const &bounds;
		// s_map_variant_placement_properties const &variantProperties;
		// real_matrix4x3 objectTransform;
		// real_point3d displacedPosition;
		// s_map_variant *mapv;
		// real_rectangle3d const *boundsPtr;
		// real_vector3d displacement;
		{
			// float dz;
		}
		{
			// float dy;
		}
		{
			// float dx;
		}
		{
			// float scale;
		}
		// function call : s_map_variant *(*const)()
		// function call : real_matrix4x3 *(*const)(long, real_matrix4x3 *)
		// function call : s_multiplayer_object_properties *(*const)(unsigned long)
		// function call : long (*const)(s_map_variant *, long, long, long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, long, s_map_variant_placement_properties const *, short)
		todo("implement");
		long __result = _sub_10968A20(player_index, object_index, depth, normal);
		return __result;
	}

	_extern void _sub_1096A240(long, long, float);
	void ThrowObject(long player_index, long object_index, float throwForce) // 0x1096A240
	{
		mangled_x86(MANGLED_TODO, "?ThrowObject@Forge@@YAXJJM@Z");
		// static ...; // 0x1096A486
		// static ...; // 0x1096A483
		// static ...; // 0x1096A480
		// static ...; // 0x1096A444
		// static ...; // 0x1096A43C
		// long player_index;
		// long object_index;
		// float throwForce;
		// s_player_datum *player;
		// void (*const simulation_action_generic_object_update)(long, unsigned long);
		// real_matrix4x3 objectTransform;
		// void (*const start_tracking_object)(long);
		{
			// real_point3d unitHeadPos;
			// real_vector3d vec;
			// real_vector3d v2;
			// s_object_data *unitObjectPtr;
			// real_vector3d v3;
		}
		// function call : real_matrix4x3 *(*const)(long, real_matrix4x3 *)
		// function call : void (*const)(long, bool)
		// function call : void (*const)(long, real_point3d *)
		// function call : void (*const)(long, real_vector3d *, real_vector3d *)
		// function call : void (*const)(long, real_vector3d const *, real_vector3d const *)
		// function call : void (*const)(long, unsigned long)
		// function call : void (*const)(long)
		todo("implement");
		_sub_1096A240(player_index, object_index, throwForce);
	}
}

extern real_vector3d _sub_10969630(real_vector3d const &);
namespace Forge
{
	real_vector3d GetClosestCardianalAxix(real_vector3d const &v) // 0x10969630
	{
		mangled_x86(MANGLED_TODO, "?GetClosestCardianalAxix@Forge@@YA?AUreal_vector3d@@ABU2@@Z");
		// real_vector3d const &v;
		// float xn;
		// float zn;
		// float yn;
		todo("implement");
		real_vector3d __result = _sub_10969630(v);
		return __result;
	}

	extern ForgeObjectQuota _sub_10968910();
	Forge::ForgeObjectQuota CalculateObjectQuota() // 0x10968910
	{
		mangled_x86(MANGLED_TODO, "?CalculateObjectQuota@Forge@@YA?AUForgeObjectQuota@1@XZ");
		// procedure flags: nofpo
		// unsigned short totalAvailable;
		// unsigned short totalUsed;
		// s_map_variant *mapv;
		{
			// unsigned short i;
			{
				// s_variant_datum &placement;
			}
		}
		todo("implement");
		Forge::ForgeObjectQuota __result = _sub_10968910();
		return __result;
	}

	bool PointInWorldBounds(real_point3d const &point) // 0x10969E50
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?PointInWorldBounds@Forge@@YA_NABUreal_point3d@@@Z");
		// real_point3d const &point;
		// s_map_variant *mapv;

		s_map_variant *mapv = Forge::GetMapVariant();
		return point.x >= mapv->world_bounds.x0
			&& mapv->world_bounds.x1 >= point.x
			&& point.y >= mapv->world_bounds.y0
			&& mapv->world_bounds.y1 >= point.y
			&& point.z >= mapv->world_bounds.z0
			&& mapv->world_bounds.z1 >= point.z;
	}

	bool ObjectInWorldBounds(long objectIndex) // 0x10969C30
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ObjectInWorldBounds@Forge@@YA_NJ@Z");
		// static ...; // 0x10969CC0
		// static ...; // 0x10969CB4
		// static ...; // 0x10969CAC
		// long objectIndex;
		// real_point3d worldPos;
		// function call : void (*const)(long, real_point3d *)

		real_point3d worldPos;

		((void(__cdecl *const)(long, real_point3d *))0xb2e5a0)(objectIndex, &worldPos);

		return Forge::PointInWorldBounds(worldPos);
	}

	_extern void _sub_1096A0F0(long, Forge::EForgeObjectPhysics, bool);
	void SetObjectPhysicsMode(long objectIndex, Forge::EForgeObjectPhysics mode, bool atRest) // 0x1096A0F0
	{
		mangled_x86(MANGLED_TODO, "?SetObjectPhysicsMode@Forge@@YAXJW4EForgeObjectPhysics@1@_N@Z");
		// bool atRest;
		// s_object_data *object;
		// void (*const change_object_physics_mode)(long, bool);
		// function call : void (*const)(long, bool)
		todo("implement");
		_sub_1096A0F0(objectIndex, mode, atRest);
	}

	extern EForgeObjectPhysics _sub_10969B90(long);
	Forge::EForgeObjectPhysics GetObjectPhysicsMode(long objectIndex) // 0x10969B90
	{
		mangled_x86(MANGLED_TODO, "?GetObjectPhysicsMode@Forge@@YA?AW4EForgeObjectPhysics@1@J@Z");
		// long objectIndex;
		// s_multiplayer_object_properties *multiplayerProperties;
		// function call : s_multiplayer_object_properties *(*const)(unsigned long)
		todo("implement");
		Forge::EForgeObjectPhysics __result = _sub_10969B90(objectIndex);
		return __result;
	}

	_extern bool _sub_10969CF0(long);
	bool ObjectIsForgeScenery(long objectIndex) // 0x10969CF0
	{
		mangled_x86(MANGLED_TODO, "?ObjectIsForgeScenery@Forge@@YA_NJ@Z");
		// long objectIndex;
		// s_object_data *object;
		// s_model_definition *modelDef;
		// s_object_definition *objectDef;
		// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
		// function call : void *(*const)(unsigned long, long)
		// function call : void *(*const)(unsigned long, long)
		todo("implement");
		bool __result = _sub_10969CF0(objectIndex);
		return __result;
	}

	_extern void _sub_10969FB0(long, float);
	void ScaleForgeSceneryObject(long objectIndex, float scale) // 0x10969FB0
	{
		mangled_x86(MANGLED_TODO, "?ScaleForgeSceneryObject@Forge@@YAXJM@Z");
		// float scale;
		// s_object_data *object;
		{
			// void (*const object_set_scale)(long, float, float);
			// constexpr void (*const `Forge::ScaleForgeSceneryObject'::`7'::havok_object_rebuild_immediate)(long); // constant == 6058848
		}
		// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
		// function call : void (*const)(long, float, float)
		// function call : void (*const)(long)
		todo("implement");
		_sub_10969FB0(objectIndex, scale);
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_flags<enum e_variant_object_placement_flags,unsigned short>::test(e_variant_object_placement_flags) const;
