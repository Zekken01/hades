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

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const object_get_origin = reinterpret_cast<void(__cdecl *)(long, real_point3d *)>(0xB2E5A0);
	static auto const object_get_velocities = reinterpret_cast<void (*)(long, real_vector3d *, real_vector3d *)>(0xB2EB30);
	static auto const object_get_world_matrix = reinterpret_cast<real_matrix4x3 *(*)(long, real_matrix4x3 *)>(0xB2EC60);
	static auto const object_set_at_rest = reinterpret_cast<void (*)(long, bool)>(0xB327F0);
	static auto const object_set_velocities = reinterpret_cast<void (*)(long, real_vector3d const *, real_vector3d const *)>(0xB34040);
	static auto const unit_get_camera_position = reinterpret_cast<void (*)(long, real_point3d *)>(0xB439D0);
}

extern float normalize3d(real_vector3d *v);  // hades: added for 0x1096A240
extern real_vector3d *vector_from_points3d(real_point3d const *p1, real_point3d const *p2, real_vector3d *result);  // hades: added for 0x1096A240

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<e_object_type, long>);  // hades: added for 0x10969FB0

extern s_object_data *object_get(unsigned long object_index);  // hades: added for 0x1096A0F0

extern void *(__cdecl *const tag_get)(unsigned long, long);  // hades: added for 0x10969CF0
extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<e_object_type, long>);  // hades: added for 0x10969CF0

extern s_multiplayer_object_properties *(*const object_get_multiplayer)(unsigned long);  // hades: added for 0x10969B90

extern s_map_variant *(*const game_engine_get_runtime_map_variant)();  // hades: added for 0x109699F0

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
	namespace hades_file_local_ForgeUtil { extern real_vector3d global_zero3d; } using namespace hades_file_local_ForgeUtil; // 0x1119A698
}
using namespace hades_file_local; extern real_vector3d *matrix4x3_inverse_transform_vector(real_matrix4x3 const *, real_vector3d const *, real_vector3d *);
/* ---------- public code */


namespace Forge
{
	s_map_variant *GetMapVariant() // 0x109699F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetMapVariant@Forge@@YAPAUs_map_variant@@XZ");

		return game_engine_get_runtime_map_variant();
	}

	void PrintKillFeedText(long user_index, wchar_t const *message, long unused) // 0x10969F50
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?PrintKillFeedText@Forge@@YAXJPB_WJ@Z");

		((void(__cdecl *const)(long, wchar_t const *, e_chud_message_context))0xa95920)(user_index, message, (e_chud_message_context)0);
	}
}


namespace Forge
{
	real_rectangle3d const *GetObjectBoundingBox(long tag_index) // 0x10969A40
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetObjectBoundingBox@Forge@@YAPBUreal_rectangle3d@@J@Z");

		s_object_definition *object_definition = (s_object_definition *)tag_get('obje', tag_index);
		if (!object_definition || object_definition->model.index == -1)
		{
			return nullptr;
		}

		s_model_definition *model = (s_model_definition *)tag_get('hlmt', object_definition->model.index);
		if (!model || model->render_model.index == -1)
		{
			return nullptr;
		}

		s_render_model *render_model = (s_render_model *)tag_get('mode', model->render_model.index);
		if (!render_model)
		{
			return nullptr;
		}

		if (!render_model->render_geometry.compression.count)
		{
			return nullptr;
		}

		return (real_rectangle3d const *)&render_model->render_geometry.compression[0].x;
	}

	void DeleteObject(long player_index, long map_variant_index) // 0x109695C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?DeleteObject@Forge@@YAXJJ@Z");

		void (__cdecl *const game_engine_sandbox_apply_delete_object)(long, long) = (void(__cdecl *const)(long, long))0x59cbe0;

		game_engine_sandbox_apply_delete_object(player_index, map_variant_index);
	}

	long CloneObject(long player_index, long object_index, float depth, real_vector3d const &normal) // 0x10968A20
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?CloneObject@Forge@@YAJJJMABUreal_vector3d@@@Z");

		s_map_variant *mapv = game_engine_get_runtime_map_variant();
		s_object_data *object = object_get(object_index);
		if (!mapv || player_index == -1 || object_index == -1 || !object)
			return -1;
		real_rectangle3d const *boundsPtr = GetObjectBoundingBox(object->definition_index);
		if (!boundsPtr)
			return -1;
		real_rectangle3d const &bounds = *boundsPtr;
		s_map_variant_placement_properties const &variantProperties = mapv->objects[object->map_variant_index].properties;
		real_matrix4x3 objectTransform;
		eldorado::object_get_world_matrix(object_index, &objectTransform);
		real_vector3d intersectNormal;
		matrix4x3_inverse_transform_vector(&objectTransform, &normal, &intersectNormal);
		real_vector3d displacement = global_zero3d;
		if (abs(intersectNormal.k) > abs(intersectNormal.j) && abs(intersectNormal.k) > abs(intersectNormal.i))
		{
			float dz = bounds.z1 - bounds.z0;
			displacement = intersectNormal.k > 0.0f ? objectTransform.up * dz : objectTransform.up * -dz;
		}
		else if (abs(intersectNormal.j) > abs(intersectNormal.k) && abs(intersectNormal.j) > abs(intersectNormal.i))
		{
			float dy = bounds.y1 - bounds.y0;
			displacement = intersectNormal.j > 0.0f ? objectTransform.left * dy : objectTransform.left * -dy;
		}
		else if (abs(intersectNormal.i) > abs(intersectNormal.j) && abs(intersectNormal.i) > abs(intersectNormal.k))
		{
			float dx = bounds.x1 - bounds.x0;
			displacement = intersectNormal.i > 0.0f ? objectTransform.forward * dx : objectTransform.forward * -dx;
		}
		if (ObjectIsForgeScenery(object_index))
		{
			float scale = object_get_multiplayer(object_index)->boundry_width;
			if (scale >= 0.00001f)
				depth *= scale;
		}
		real_point3d displacedPosition = objectTransform.position + displacement * depth;
		if (!(displacedPosition.x > mapv->world_bounds.x0 && mapv->world_bounds.x1 > displacedPosition.x && displacedPosition.y > mapv->world_bounds.y0 && mapv->world_bounds.y1 > displacedPosition.y && displacedPosition.z > mapv->world_bounds.z0 && mapv->world_bounds.z1 > displacedPosition.z))
		{
			PrintKillFeedText(0, L"Object out of World Bounds", 0);
			return -1;
		}
		return ((long (__thiscall *const)(s_map_variant *, long, long, long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, long, s_map_variant_placement_properties const *, short))0x582110)(GetMapVariant(), object->definition_index, 0, -1, &displacedPosition, &objectTransform.forward, &objectTransform.up, -1, -1, &variantProperties, 0);
	}

	void ThrowObject(long player_index, long object_index, float throwForce) // 0x1096A240
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ThrowObject@Forge@@YAXJJM@Z");

		void (*const simulation_action_generic_object_update)(long, unsigned long) = (void (*)(long, unsigned long))0x580AD0;
		void (*const start_tracking_object)(long) = (void (*)(long))0x59EA10;
		real_matrix4x3 objectTransform;
		eldorado::object_get_world_matrix(object_index, &objectTransform);
		s_player_datum *player = player_get(player_index);
		if (!player)
			return;
		eldorado::object_set_at_rest(object_index, false);
		if (throwForce >= 0.00001f)
		{
			s_object_data *unitObjectPtr = object_get(player->unit_index);
			if (!unitObjectPtr)
				return;
			real_point3d unitHeadPos;
			eldorado::unit_get_camera_position(player->unit_index, &unitHeadPos);
			real_vector3d vec;
			vector_from_points3d(&unitHeadPos, &objectTransform.position, &vec);
			normalize3d(&vec);
			vec.i = throwForce * 15.0f * vec.i;
			vec.j = throwForce * 15.0f * vec.j;
			vec.k = throwForce * 15.0f * vec.k;
			real_vector3d v2;
			real_vector3d v3;
			eldorado::object_get_velocities(object_index, &v2, &v3);
			eldorado::object_set_velocities(object_index, &v2, &v3);
			simulation_action_generic_object_update(object_index, 4);
		}
		start_tracking_object(object_index);
	}
}


namespace Forge
{
	real_vector3d GetClosestCardianalAxix(real_vector3d const &v) // 0x10969630
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetClosestCardianalAxix@Forge@@YA?AUreal_vector3d@@ABU2@@Z");

		float xn = abs(v.i);
		float yn = abs(v.j);
		float zn = abs(v.k);
		if (xn >= yn && xn >= zn)
			return v.i > 0.0f ? real_vector3d{ 1.0f, 0.0f, 0.0f } : real_vector3d{ -1.0f, 0.0f, 0.0f };
		else if (yn > xn && yn > zn)
			return v.j > 0.0f ? real_vector3d{ 0.0f, 1.0f, 0.0f } : real_vector3d{ 0.0f, -1.0f, 0.0f };
		else if (zn > xn && zn > yn)
			return v.k > 0.0f ? real_vector3d{ 0.0f, 0.0f, 1.0f } : real_vector3d{ 0.0f, 0.0f, -1.0f };
		return { 0.0f, 0.0f, 0.0f };
	}

	Forge::ForgeObjectQuota CalculateObjectQuota() // 0x10968910
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?CalculateObjectQuota@Forge@@YA?AUForgeObjectQuota@1@XZ");

		unsigned short totalAvailable = 0;
		unsigned short totalUsed = 0;
		s_map_variant *mapv = GetMapVariant();
		if (mapv)
		{
			for (unsigned short i = mapv->scenario_object_count; i < 640; i++)
			{
				s_variant_datum &placement = mapv->objects[i];
				totalAvailable++;
				if (placement.flags.test(_map_variant_occupied_slot_bit))
					totalUsed++;
			}
		}
		return { totalAvailable, totalUsed };
	}

	bool PointInWorldBounds(real_point3d const &point) // 0x10969E50
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?PointInWorldBounds@Forge@@YA_NABUreal_point3d@@@Z");

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

		real_point3d worldPos;

		eldorado::object_get_origin(objectIndex, &worldPos);

		return Forge::PointInWorldBounds(worldPos);
	}

	void SetObjectPhysicsMode(long objectIndex, Forge::EForgeObjectPhysics mode, bool atRest) // 0x1096A0F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetObjectPhysicsMode@Forge@@YAXJW4EForgeObjectPhysics@1@_N@Z");

		void (*const change_object_physics_mode)(long, bool) = reinterpret_cast<void (*)(long, bool)>(0x59A620);
		s_object_data *object = object_get(objectIndex);
		if (!object)
		{
			return;
		}

		switch (mode)
		{
		case Forge::Normal:
			object->physics_flags &= ~0x40;
			break;
		case Forge::Phased:
			object->physics_flags |= 0x40;
			break;
		}

		if (!atRest)
		{
			object->physics_flags &= ~0x200;
		}
		else
		{
			object->physics_flags |= 0x200;
		}

		object->physics_flags &= ~0x100000;
		change_object_physics_mode(objectIndex, true);
	}

	Forge::EForgeObjectPhysics GetObjectPhysicsMode(long objectIndex) // 0x10969B90
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetObjectPhysicsMode@Forge@@YA?AW4EForgeObjectPhysics@1@J@Z");

		s_multiplayer_object_properties *multiplayerProperties = object_get_multiplayer(objectIndex);

		if (multiplayerProperties && (char)multiplayerProperties->boundary_shape == 4)
		{
			return Forge::Phased;
		}
		else
		{
			return Forge::Normal;
		}
	}

	bool ObjectIsForgeScenery(long objectIndex) // 0x10969CF0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ObjectIsForgeScenery@Forge@@YA_NJ@Z");

		s_object_data *object = object_try_and_get_and_verify_type(objectIndex, 0x80);
		if (!object)
		{
			return false;
		}

		if (object->map_variant_index == -1)
		{
			return false;
		}

		s_object_definition *objectDef = (s_object_definition *)tag_get('scen', object->definition_index);
		if (objectDef->model.index == -1)
		{
			return false;
		}

		s_model_definition *modelDef = (s_model_definition *)tag_get('hlmt', objectDef->model.index);
		if (!modelDef)
		{
			return false;
		}

		return modelDef->physics_model.index == -1;
	}

	void ScaleForgeSceneryObject(long objectIndex, float scale) // 0x10969FB0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ScaleForgeSceneryObject@Forge@@YAXJM@Z");

		s_object_data *object = object_try_and_get_and_verify_type(objectIndex, 0x80);
		if (!object)
			return;
		if (scale >= 0.00001f)
		{
			if (abs(object->scale - scale) >= 0.00001f)
			{
				void (*const object_set_scale)(long, float, float) = (void(*const)(long, float, float))0xB33BC0;
				object_set_scale(objectIndex, scale, 0.0f);
				((void(*)(long))0x5C7360)(objectIndex);
			}
		}
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_flags<enum e_variant_object_placement_flags,unsigned short>::test(e_variant_object_placement_flags) const;

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { namespace hades_file_local_ForgeUtil { real_vector3d global_zero3d; } }
