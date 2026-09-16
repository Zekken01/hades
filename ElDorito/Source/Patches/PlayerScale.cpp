/* ---------- headers */

#include "hades/hades.h"

#include "Blam/ai/actor.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/effects/effects.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_engine_teleporters.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/items/weapon_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/biped_definitions.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "ElDorito.hpp"
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

struct c_teleporter_area;
struct lambda_1;
struct real_matrix4x3;
struct real_point3d;
struct real_vector3d;
struct s_biped_definition;
struct s_datum;
struct s_effect_datum;
struct s_object_data;
struct s_physics_model_pill;
struct s_player_datum;
struct s_scenario_location;
struct s_state;
struct s_weapon_definition;
namespace hades_file_local
{
	struct hkVector4;
	struct hkCapsuleShape;
	struct PlayerState;
	struct s_biped_physics;
	struct s_biped_physics_data1;
	struct ZoneShape;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace PlayerScale {}
	using namespace Patches::PlayerScale;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct hkVector4
	{
		float x; // 0x0
		float y; // 0x4
		float z; // 0x8
		float w; // 0xC
	};
	static_assert(sizeof(hkVector4) == 16, "Invalid hkVector4 size");

	struct hkCapsuleShape
	{
		void **vftable; // 0x0
		unsigned short m_memSizeAndFlags; // 0x4
		unsigned short m_referenceCount; // 0x6
		unsigned __int32 m_userData; // 0x8
		unsigned __int32 m_type; // 0xC
		float m_radius; // 0x10
		__int32 field_14; // 0x14
		__int32 field_18; // 0x18
		__int32 field_1C; // 0x1C
		hkVector4 m_bottom; // 0x20
		hkVector4 m_top; // 0x30
	};
	static_assert(sizeof(hkCapsuleShape) == 64, "Invalid hkCapsuleShape size");

	struct PlayerState
	{
		bool IsValid; // 0x0
		bool IsTransitioning; // 0x1
		unsigned char __pad0[2]; // 0x2
		float DesiredScale; // 0x4
		unsigned __int32 UnitObjectIndex; // 0x8
		unsigned __int32 PhysicsUpdateDeltaTime; // 0xC
		hkCapsuleShape PhysicsCapsules[2]; // 0x10
	};
	static_assert(sizeof(PlayerState) == 144, "Invalid PlayerState size");
}
using namespace hades_file_local;
struct s_state
{
	bool IsValid; // 0x0
	bool IsLandingDamage; // 0x1
	PlayerState Players[16]; // 0x4
};
// static_assert(sizeof(s_state) == 2308, "Invalid s_state size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

namespace hades_file_local
{

	//@@anonymous-namespace@@
	#pragma pack(push, 4)
	struct s_biped_physics
	{
		__int32 Flags; // 0x0
		float HeightStanding; // 0x4
		float HeightCrouching; // 0x8
		float Radius; // 0xC
		float Mass; // 0x10
		unsigned __int32 LivingMaterialName; // 0x14
		unsigned __int32 DeadMaterialName; // 0x18
		unsigned short LivingMaterialGlobalIndex; // 0x1C
		unsigned short DeadMaterialIndex; // 0x1E
		c_tag_block<unsigned char> DeadSphereShapes; // 0x20
		c_tag_block<s_havok_shape_data<hkCapsuleShape> > PillShapes; // 0x2C
		c_tag_block<unsigned char> SphereShapes; // 0x38
	};
	#pragma pack(pop)
}
using namespace hades_file_local;
// static_assert(sizeof(s_biped_physics) == 68, "Invalid s_biped_physics size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

namespace hades_file_local
{

	//@@anonymous-namespace@@
	#pragma pack(push, 4)
	struct s_biped_physics_data1
	{
		unsigned char field_0[24]; // 0x0
		unsigned __int32 HavokComponentIndex; // 0x18
		unsigned char field_1C[308]; // 0x1C
		float Boost; // 0x150
		real_vector3d Velocity; // 0x154
		float GroundAcceleration; // 0x160
		float AirborneAcceleration; // 0x164
		void *Shape; // 0x168
	};
	#pragma pack(pop)
}
using namespace hades_file_local;
// static_assert(sizeof(s_biped_physics_data1) == 364, "Invalid s_biped_physics_data1 size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

namespace hades_file_local
{
	struct ZoneShape
	{
		__int32 Shape; // 0x0
		__int32 ShapeShader; // 0x4
		float RadiusWidth; // 0x8
		float Length; // 0xC
		float Top; // 0x10
		float Bottom; // 0x14
		real_matrix4x3 Transform; // 0x18
		float BoundingRadius; // 0x4C
	};
}
using namespace hades_file_local;
// static_assert(sizeof(ZoneShape) == 80, "Invalid ZoneShape size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

//struct ObjectDeleteAttachedEffects::__l2::s_object_attachment
//{
//	unsigned char type; // 0x0
//	unsigned char field_01; // 0x1
//	unsigned char field_02; // 0x2
//	unsigned char field_03; // 0x3
//	unsigned __int32 handle; // 0x4
//};
//static_assert(sizeof(ObjectDeleteAttachedEffects::__l2::s_object_attachment) == 8, "Invalid ObjectDeleteAttachedEffects::__l2::s_object_attachment size");

//class BipedPhysicsHook2::__l5::<lambda_1>
//{
//public:
//	void operator()() const;
//	<lambda_1>(BipedPhysicsHook2::__l5::<lambda_1> &);
//	<lambda_1>(unsigned __int32 const &, __int32 const &, void *const &);
//private:
//	unsigned __int32 objectIndex; // 0x0
//	__int32 a2; // 0x4
//	void *a3; // 0x8
//public:
//	BipedPhysicsHook2::__l5::<lambda_1> &operator=(BipedPhysicsHook2::__l5::<lambda_1> const &);
//};
//static_assert(sizeof(BipedPhysicsHook2::__l5::<lambda_1>) == 12, "Invalid BipedPhysicsHook2::__l5::<lambda_1> size");

//class BipedPhysicsHook1::__l5::<lambda_1>
//{
//public:
//	void operator()() const;
//	<lambda_1>(BipedPhysicsHook1::__l5::<lambda_1> &);
//	<lambda_1>(void (*const &)(unsigned __int32), __int32 const &);
//private:
//	void (*const sub_B73C00)(unsigned __int32); // 0x0
//	__int32 objectIndex; // 0x4
//public:
//	BipedPhysicsHook1::__l5::<lambda_1> &operator=(BipedPhysicsHook1::__l5::<lambda_1> const &);
//};
//static_assert(sizeof(BipedPhysicsHook1::__l5::<lambda_1>) == 8, "Invalid BipedPhysicsHook1::__l5::<lambda_1> size");

/* ---------- prototypes */

struct s_object_data *object_get(unsigned long objectIndex);  // hades: added for 0X10AB1CD0

namespace Patches
{
	namespace PlayerScale
	{
		extern void ApplyAll();
		extern void Tick();
		extern void UpdatePlayerScale(__int32 playerIndex);
	}
}

float SmoothStep(float from, float to, float t, float max);
void ObjectDeleteAttachedEffects(unsigned __int32 objectIndex);
void ObjectDeleteEffectAttachmentsRecursive(unsigned __int32 unitObjectIndex);
void UpdatePlayerSize(unsigned __int32 playerIndex);
bool biped_can_ragdoll(long biped_index);
bool biped_start_relaxation_hook(long biped_index, bool a1);
bool SprintCameraShakeHook(unsigned __int32 playerIndex, float *outValue);
void *GetScaledShape(unsigned __int32 bipedObjectIndex, s_biped_physics *bipedPhysicsData, __int32 shapeIndex);
void *GetBipedPhysicsShape(unsigned __int32 bipedObjectIndex, s_biped_physics *bipedPhysics, __int32 shapeIndex);
void BipedPhysicsHook_4B10E0();
void BipedPhysicsHook_5E23BC();
void BipedPhysicsHook_B7156F();
void BipedPhysicsHook_BAF4CF();
bool biped_can_spawn_at_location_unobstructed(long biped_index, real_point3d *position, bool validate_location);
bool teleporter_is_blocked_for_object_hook(c_teleporter_area *source_teleporter, c_teleporter_area *destination_teleporter, long teleported_object_index);
void PlayerSpawnLocationHook(unsigned __int32 playerIndex, real_vector3d *position, real_vector3d *orientation, __int32 *pStartingLocationIndex);
bool PlayerZoneTestHook(unsigned __int32 playerIndex, ZoneShape *zone);
void BipedShapeHook(unsigned __int32 objectIndex, real_vector3d *outPosition, float *outHeight, float *outRadius);
void MeleeRangeHook(unsigned __int32 unitObjectIndex, unsigned __int32 name, __int32 a3, void *damageData);
void ScaleCollisionDamage(unsigned __int32 objectIndex, unsigned char *damageData);
void CollisionDamageHook();
void BipedMovementPhysics(s_biped_physics_data1 *data, __int32 a2, char a3, char a4, char a5, char a6, __int32 a7, float sneak);
bool __fastcall WalkAnimationHook(void *thisptr, void *unused, unsigned __int32 unitObjectIndex, real_vector3d *a3, bool a4);
void JumpVelocityScaleHook(unsigned __int32 bipedObjectIndex);
float __fastcall PlayerPersonalGravity(void *traits, unsigned __int32 unitObjectIndex);
void PlayerPersonalGravityHook();
void *__fastcall BipedCreateRigidBodyHook(void *thisptr, void *unused, s_biped_physics *bipedPhysics, __int32 a4, __int32 a5, unsigned __int32 collisionFilter_, __int32 shapeIndex, bool hasFriction, char a9);
bool PlayerCollisionDamageHook(unsigned __int32 bipedObjectIndex, unsigned __int32 otherBipedObjectIndex);
void LandingDamageResponseHook(unsigned __int32 unitObjectIndex, unsigned __int32 a2, unsigned __int32 damageEffectTagIndex, real_vector3d *a4, real_vector3d *a5, float a6, float responseScale, __int32 a8);
void DamageResponsePlayerEffectsHook(unsigned __int32 uintObjectIndex, __int32 localPlayerIndex, unsigned __int32 damageResponseTagIndex, __int32 a4, real_vector3d *a5, float a6, float scale, bool a8);
bool ModelTargetTestHook(__int32 a1, unsigned __int32 objectIndex, __int32 a3, char a4, char a5, char a6, __int32 a7, unsigned char *target, __int32 a9, __int32 a10, real_vector3d *a11, __int32 a12, void *data);
void ShieldDownParticleEffectHook(unsigned __int32 effectDatumIndex, unsigned short eventIndex);
void BipedPhysicsHook2(unsigned __int32 objectIndex, __int32 a2, void *a3);
void BipedPhysicsHook1(__int32 objectIndex);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern float const kPlayerScales[17]; // 0x111B1140
	extern float kSpeedExp; // 0x113548A4
	extern float kMeleeRangeExp; // 0x113548A8
	extern float kMassExp; // 0x113548AC
	extern float kGravityExp; // 0x113548B0
	extern float kJumpVelocityExp; // 0x113548B4
	extern float kAirborneAccelerationScale; // 0x113548B8
	extern float kGroundAccelerationScale; // 0x113548BC
	extern float const kMaxPlayerScale; // 0x12466758
	extern s_state state; // 0x12466760
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace PlayerScale
	{
		_extern void _sub_10AAE0C0();
		void ApplyAll() // 0x10AAE0C0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@PlayerScale@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10AAE0C0();
		}

		void Tick() // 0x10AB2060
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@PlayerScale@Patches@@YAXXZ");
			// procedure flags: nofpo
			// bool (*const game_options_is_valid)();
				// __int32 i;
					// PlayerState &playerState;
			// function call : bool (*const)()

			const auto game_options_is_valid = (bool(*)())(0x00532650);
			if (!game_options_is_valid())
			{
				state.IsValid = false;
			}
			else
			{
				if (!state.IsValid)
				{
					memset(&state, 0, sizeof(state));
					for (auto i = 0; i < 16; i++)
					{
						auto &playerState = state.Players[i];
						playerState.UnitObjectIndex = -1;
						playerState.IsValid = false;
					}
					state.IsValid = true;
				}
			}
		}

		void UpdatePlayerScale(__int32 playerIndex) // 0x10AB2150
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?UpdatePlayerScale@PlayerScale@Patches@@YAXH@Z");
			// __int32 playerIndex;

			UpdatePlayerSize(playerIndex);
		}
	}
}

/* ---------- private code */

float SmoothStep(float from, float to, float t, float max) // 0x10AB1E60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SmoothStep@@YAMMMMM@Z");
	// `anonymous-namespace'::SmoothStep
	// float max;

	if (t > 1.0f)
		t = 1.0f;
	if (t < 0.0f)
		t = 0.0f;
	t = -2.0f * t * t * t + 3.0f * t * t;
	if (t > max)
		t = max;
	return to * t + (1.0f - t) * from;
}

_extern void _sub_10AB10D0(unsigned __int32);
void ObjectDeleteAttachedEffects(unsigned __int32 objectIndex) // 0x10AB10D0
{
	// `anonymous-namespace'::ObjectDeleteAttachedEffects
	// unsigned __int32 objectIndex;
	// s_object_data *unitObject;
	// unsigned __int32 attachmentBlock;
	// void (*const effect_delete)(unsigned __int32);
	// ObjectDeleteAttachedEffects::__l2::s_object_attachment *attachments;
	// unsigned __int32 attachmentsOffset;
	// unsigned __int32 attachmentsCount;
	{
		// unsigned char i;
		{
			// ObjectDeleteAttachedEffects::__l2::s_object_attachment &attachment;
		}
	}
	// function call : void (*const)(unsigned __int32)
	todo("implement");
	_sub_10AB10D0(objectIndex);
}

void ObjectDeleteEffectAttachmentsRecursive(unsigned __int32 unitObjectIndex) // 0x10AB1210
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ObjectDeleteEffectAttachmentsRecursive@@YAXI@Z");
	// `anonymous-namespace'::ObjectDeleteEffectAttachmentsRecursive
	// unsigned __int32 unitObjectIndex;
	// s_object_data *unitObject;
	// long objectIndex;
		// s_object_data *childObject;

	s_object_data *object = object_get(unitObjectIndex);
	if (!object)
		return;

	long childObjectIndex = object->first_child_object_index;
	do
	{
		ObjectDeleteEffectAttachmentsRecursive(childObjectIndex);

		s_object_data *childObject = object_get(childObjectIndex);
		if (!childObject)
			continue;

		ObjectDeleteAttachedEffects(childObjectIndex);
		childObjectIndex = childObject->next_object_index;
	} while (childObjectIndex != -1);
}

_extern void _sub_10AB21A0(unsigned __int32);
void UpdatePlayerSize(unsigned __int32 playerIndex) // 0x10AB21A0
{
	// `anonymous-namespace'::UpdatePlayerSize
	// unsigned __int32 playerIndex;
	// PlayerState &playerState;
	// s_player_datum *player;
	// s_object_data *unitObject;
	// __int32 playerScaleIndex;
	// float desiredScale;
	// float currentScale;
	// function call : void (*const)(unsigned __int32, float, float)
	// function call : __int32 (*const)(unsigned __int32, unsigned __int32)
	// function call : void (*const)(unsigned __int32, float, float)
	// function call : __int32 (*const)(unsigned __int32, unsigned __int32)
	// function call : void (*const)(unsigned __int32, float, float)
	// function call : float (*const)()
	// function call : void (*const)(unsigned __int32, float, float)
	// function call : float (*const)(float)
	// function call : __int32 (*const)(unsigned __int32, unsigned __int32)
	todo("implement");
	_sub_10AB21A0(playerIndex);
}

bool biped_can_ragdoll(long biped_index) // 0x10AB2780
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?biped_can_ragdoll@@YA_NJ@Z");
	// `anonymous-namespace'::biped_can_ragdoll
	// long biped_index;
	// s_object_data *biped;

	s_object_data *biped = object_get(biped_index);
	if (!biped)
		return false;
	return biped->scale >= 1.0f && biped->scale < 3.0f;
}

bool biped_start_relaxation_hook(long biped_index, bool a1) // 0x10AB2B60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?biped_start_relaxation_hook@@YA_NJ_N@Z");
	// `anonymous-namespace'::biped_start_relaxation_hook
	// bool a1;
	// char (*const biped_start_relaxation)(long, bool);
	// function call : char (*const)(long, bool)

	char (__cdecl *const biped_start_relaxation)(long, bool) = (char(__cdecl *const)(long, bool))0xbd80d0;

	if (!biped_can_ragdoll(biped_index))
	{
		return false;
	}

	return (bool)biped_start_relaxation(biped_index, a1);
}

bool SprintCameraShakeHook(unsigned __int32 playerIndex, float *outValue) // 0x10AB1F50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SprintCameraShakeHook@@YA_NIPAM@Z");
	// `anonymous-namespace'::SprintCameraShakeHook
	// float *outValue;
	// s_player_datum *player;
	// s_object_data *unitObject;
	// bool (*const player_get_sprinting)(unsigned __int32, float *);
	// function call : bool (*const)(unsigned __int32, float *)

	bool (__cdecl *const player_get_sprinting)(unsigned __int32, float *) = (bool(__cdecl *const)(unsigned __int32, float *))0x53b590;

	s_player_datum *player = players_get()->try_and_get(playerIndex);
	if (!player || player->unit_index == -1)
		return false;

	s_object_data *unitObject = object_get(player->unit_index);
	if (!unitObject)
		return false;

	return player_get_sprinting(playerIndex, outValue) && unitObject->scale >= 0.9f;
}

_extern void *_sub_10AB09A0(unsigned __int32, s_biped_physics *, __int32);
void *GetScaledShape(unsigned __int32 bipedObjectIndex, s_biped_physics *bipedPhysicsData, __int32 shapeIndex) // 0x10AB09A0
{
	// `anonymous-namespace'::GetScaledShape
	// __int32 shapeIndex;
	// s_player_datum *player;
	// PlayerState &playerState;
	// s_object_data *bipedObject;
	// hkCapsuleShape &stateCapsule;
	// float s;
	// unsigned __int32 playerIndex;
	// s_havok_shape_data<hkCapsuleShape> &pillShape;
	todo("implement");
	void * __result = _sub_10AB09A0(bipedObjectIndex, bipedPhysicsData, shapeIndex);
	return __result;
}

_extern void *_sub_10AB0880(unsigned __int32, s_biped_physics *, __int32);
void *GetBipedPhysicsShape(unsigned __int32 bipedObjectIndex, s_biped_physics *bipedPhysics, __int32 shapeIndex) // 0x10AB0880
{
	// `anonymous-namespace'::GetBipedPhysicsShape
	// __int32 shapeIndex;
	{
		// s_object_data *bipedObject;
		{
			// unsigned __int32 playerIndex;
			{
				// PlayerState &playerState;
				// void *shape;
			}
		}
	}
	{
		// unsigned char *data;
	}
	todo("implement");
	void * __result = _sub_10AB0880(bipedObjectIndex, bipedPhysics, shapeIndex);
	return __result;
}

__declspec(naked) void BipedPhysicsHook_4B10E0() // 0x10AB0460
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BipedPhysicsHook_4B10E0@@YAXXZ");
	// `anonymous-namespace'::BipedPhysicsHook_4B10E0
	// procedure flags: nofpo

	__asm
	{
		mov eax, [ebx + 8]
		push eax
		call GetBipedPhysicsShape
		push 04B10E5h
		ret 4
	}
}

__declspec(naked) void BipedPhysicsHook_5E23BC() // 0x10AB0480
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BipedPhysicsHook_5E23BC@@YAXXZ");
	// `anonymous-namespace'::BipedPhysicsHook_5E23BC
	// procedure flags: nofpo

	__asm
	{
		mov eax, [edx + 8]
		push eax
		call GetBipedPhysicsShape
		push 05E23C1h
		ret 4
	}
}

__declspec(naked) void BipedPhysicsHook_B7156F() // 0x10AB04A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BipedPhysicsHook_B7156F@@YAXXZ");
	// `anonymous-namespace'::BipedPhysicsHook_B7156F
	// procedure flags: nofpo

	__asm
	{
		mov eax, [ebx + 8]
		push eax
		call GetBipedPhysicsShape
		push 0B71574h
		ret 4
	}
}

__declspec(naked) void BipedPhysicsHook_BAF4CF() // 0x10AB04C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BipedPhysicsHook_BAF4CF@@YAXXZ");
	// `anonymous-namespace'::BipedPhysicsHook_BAF4CF
	// procedure flags: nofpo

	__asm
	{
		mov eax, [ebp + 8]
		push eax
		call GetBipedPhysicsShape
		push 0BAF4D4h
		ret 4
	}
}

_extern bool _sub_10AB2830(long, real_point3d *, bool);
bool biped_can_spawn_at_location_unobstructed(long biped_index, real_point3d *position, bool validate_location) // 0x10AB2830
{
	// `anonymous-namespace'::biped_can_spawn_at_location_unobstructed
	// static ...; // 0x10AB2A9C
	// static ...; // 0x10AB2A78
	// static ...; // 0x10AB2A70
	// long biped_index;
	// real_point3d *position;
	// bool validate_location;
	// bool (*const collision_test_point)(unsigned long, unsigned long, real_point3d *, long, long);
	// s_object_data *biped;
	// real_point3d adjusted_postion;
	// bool (*const havok_world_shape_collides)(void *, long, real_matrix4x3 *, long);
	// void *shape;
	// s_scenario_location location;
	// s_biped_definition *biped_definiton;
	// void (*const scenario_location_from_point)(s_scenario_location *, real_point3d *);
	// real_matrix4x3 matrix;
	// float height;
	// function call : bool (*)()
	// function call : bool (*const)()
	// function call : void (*const)(s_scenario_location *, real_point3d *)
	// function call : void *(*const)(unsigned long, long)
	// function call : bool (*const)(void *, long, real_matrix4x3 *, long)
	// function call : bool (*const)(unsigned long, unsigned long, real_point3d *, long, long)
	todo("implement");
	bool __result = _sub_10AB2830(biped_index, position, validate_location);
	return __result;
}

_extern bool _sub_10AB2D70(c_teleporter_area *, c_teleporter_area *, long);
bool teleporter_is_blocked_for_object_hook(c_teleporter_area *source_teleporter, c_teleporter_area *destination_teleporter, long teleported_object_index) // 0x10AB2D70
{
	// `anonymous-namespace'::teleporter_is_blocked_for_object_hook
	// static ...; // 0x10AB301D
	// static ...; // 0x10AB3014
	// static ...; // 0x10AB2FE4
	// static ...; // 0x10AB2FDC
	// c_teleporter_area *source_teleporter;
	// c_teleporter_area *destination_teleporter;
	// long teleported_object_index;
	// real_point3d destination_position;
	// bool (*const teleporter_has_object_inside_boundary_area)(c_teleporter_area *, long *);
	// bool (*const game_engine_vehicle_can_spawn_at_location_unobstructed)(long, real_point3d *, bool);
	// bool valid;
	// real_point3d *(*const teleporter_get_teleport_destination_position)(c_teleporter_area *, c_teleporter_area *, long, real_point3d *);
	// real_point3d *(*const object_get_origin)(long, real_point3d *);
	// s_object_data *teleported_object;
	// void (*const object_get_center_of_mass)(long, real_point3d *);
	{
		// real_point3d origin_position;
		// s_scenario_location location;
		// real_point3d center_point;
	}
	// function call : bool (*const)(c_teleporter_area *, long *)
	// function call : real_point3d *(*const)(c_teleporter_area *, c_teleporter_area *, long, real_point3d *)
	// function call : bool (*const)(long, real_point3d *, bool)
	// function call : void (*const)(long, real_point3d *)
	// function call : real_point3d *(*const)(long, real_point3d *)
	// function call : void (*const)(s_scenario_location *, real_point3d *)
	todo("implement");
	bool __result = _sub_10AB2D70(source_teleporter, destination_teleporter, teleported_object_index);
	return __result;
}

_extern void _sub_10AB1620(unsigned __int32, real_vector3d *, real_vector3d *, __int32 *);
void PlayerSpawnLocationHook(unsigned __int32 playerIndex, real_vector3d *position, real_vector3d *orientation, __int32 *pStartingLocationIndex) // 0x10AB1620
{
	// `anonymous-namespace'::PlayerSpawnLocationHook
	// unsigned __int32 playerIndex;
	// real_vector3d *position;
	// real_vector3d *orientation;
	// __int32 *pStartingLocationIndex;
	// void (*const player_get_spawn_location)(unsigned __int32, real_vector3d *, real_vector3d *, __int32 *);
	// unsigned __int32 (*const player_get_third_person_representation)(unsigned __int32, unsigned __int32 *, unsigned __int32 *);
	// unsigned __int32 thirdPersonUnitTagIndex;
	{
		// s_biped_definition *bipedDefinition;
		{
			// PlayerState &playerState;
			{
				// void *oldPointer;
				// static s_physics_model_pill `PlayerSpawnLocationHook'::`11'::shapes[2]; // 0x12467068
				// float s;
				{
					// __int32 i;
				}
			}
		}
	}
	// function call : unsigned __int32 (*const)(unsigned __int32, unsigned __int32 *, unsigned __int32 *)
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(unsigned __int32, real_vector3d *, real_vector3d *, __int32 *)
	// function call : void (*const)(unsigned __int32, real_vector3d *, real_vector3d *, __int32 *)
	todo("implement");
	_sub_10AB1620(playerIndex, position, orientation, pStartingLocationIndex);
}

_extern bool _sub_10AB1920(unsigned __int32, ZoneShape *);
bool PlayerZoneTestHook(unsigned __int32 playerIndex, ZoneShape *zone) // 0x10AB1920
{
	// `anonymous-namespace'::PlayerZoneTestHook
	// static ...; // 0x10AB1C03
	// static ...; // 0x10AB1BFC
	// static ...; // 0x10AB1BF5
	// static ...; // 0x10AB1BE8
	// static ...; // 0x10AB1BAC
	// static ...; // 0x10AB1BA4
	// unsigned __int32 playerIndex;
	// ZoneShape *zone;
	// s_player_datum *player;
	// s_object_data *bipedObject;
	// bool (*const zone_test_point)(real_vector3d *, ZoneShape *);
	// void (*const object_get_center_of_mass)(unsigned __int32, real_vector3d *);
	{
		// real_vector3d points[2];
		// real_vector3d position;
		// float cameraHeight;
		// float headOffset;
		// float height;
		// float radius;
	}
	{
		// real_vector3d centerOfMass;
	}
	// function call : bool (*const)(real_vector3d *, ZoneShape *)
	// function call : bool (*const)(real_vector3d *, ZoneShape *)
	// function call : void (*const)(unsigned __int32, real_vector3d *)
	// function call : bool (*const)(real_vector3d *, ZoneShape *)
	todo("implement");
	bool __result = _sub_10AB1920(playerIndex, zone);
	return __result;
}

_extern void _sub_10AB04E0(unsigned __int32, real_vector3d *, float *, float *);
void BipedShapeHook(unsigned __int32 objectIndex, real_vector3d *outPosition, float *outHeight, float *outRadius) // 0x10AB04E0
{
	// `anonymous-namespace'::BipedShapeHook
	// float *outRadius;
	// float heightStanding;
	// s_object_data *bipedObject;
	// s_biped_physics *bipedPhysics;
	// char *bipedDefinition;
	// float heightCrouching;
	// float radius;
	{
		// unsigned __int32 unitFlags;
		// float v6;
		// float v7;
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(unsigned __int32, real_vector3d *)
	todo("implement");
	_sub_10AB04E0(objectIndex, outPosition, outHeight, outRadius);
}

_extern void _sub_10AB0DB0(unsigned __int32, unsigned __int32, __int32, void *);
void MeleeRangeHook(unsigned __int32 unitObjectIndex, unsigned __int32 name, __int32 a3, void *damageData) // 0x10AB0DB0
{
	// `anonymous-namespace'::MeleeRangeHook
	// void *damageData;
	// s_object_data *unitObject;
	// unsigned char *equippedWeapons;
	// void (*const sub_B3C360)(__int32, unsigned __int32, __int32, void *);
	{
		// unsigned __int32 *weapons;
		// s_object_data *weaponObject;
		// unsigned __int32 weaponObjectIndex;
		{
			// s_weapon_definition *weaponDefinition;
			// float scale;
			// float oldDepth;
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(__int32, unsigned __int32, __int32, void *)
	// function call : void (*const)(__int32, unsigned __int32, __int32, void *)
	todo("implement");
	_sub_10AB0DB0(unitObjectIndex, name, a3, damageData);
}

void ScaleCollisionDamage(unsigned __int32 objectIndex, unsigned char *damageData) // 0x10AB1CD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ScaleCollisionDamage@@YAXIPAE@Z");
	// `anonymous-namespace'::ScaleCollisionDamage
	// unsigned char *damageData;
	// s_object_data *bipedObject;

	s_object_data *bipedObject = object_get(objectIndex);
	if (bipedObject)
	{
		*(float *)damageData = *(float *)damageData * bipedObject->scale;
		*(float *)(damageData + 4) = *(float *)(damageData + 4) * bipedObject->scale;
	}
}

__declspec(naked) void CollisionDamageHook() // 0x10AB0710
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CollisionDamageHook@@YAXXZ");
	// `anonymous-namespace'::CollisionDamageHook
	// procedure flags: nofpo

	__asm
	{
		push dword ptr [ebp + 0Ch]
		push dword ptr [ebp + 8]
		call ScaleCollisionDamage
		add esp, 8
		push 07636F6h
		ret
	}
}

_extern void _sub_10AAFEA0(s_biped_physics_data1 *, __int32, char, char, char, char, __int32, float);
void BipedMovementPhysics(s_biped_physics_data1 *data, __int32 a2, char a3, char a4, char a5, char a6, __int32 a7, float sneak) // 0x10AAFEA0
{
	// `anonymous-namespace'::BipedMovementPhysics
	// float sneak;
	// void (*const sub_7209E0)(void *, __int32, char, char, char, char, __int32, float);
	// float s;
	// c_data_array<s_datum> *havokComponents;
	// float scale;
	// unsigned char *havokComponent;
	{
		// unsigned __int32 objectIndex;
		{
			// s_object_data *object;
		}
	}
	// function call : void (*const)(void *, __int32, char, char, char, char, __int32, float)
	todo("implement");
	_sub_10AAFEA0(data, a2, a3, a4, a5, a6, a7, sneak);
}

bool __fastcall WalkAnimationHook(void *thisptr, void *unused, unsigned __int32 unitObjectIndex, real_vector3d *a3, bool a4) // 0x10AB2680
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?WalkAnimationHook@@YI_NPAX0IPAUreal_vector3d@@_N@Z");
	// `anonymous-namespace'::WalkAnimationHook
	// bool a4;
	// bool (*const sub_6DEFF0)(void *, unsigned __int32, real_vector3d *, bool);
	// s_object_data *object;
		// float scale;
	// function call : bool (*const)(void *, unsigned __int32, real_vector3d *, bool)

	bool (__thiscall *const sub_6DEFF0)(void *, unsigned __int32, real_vector3d *, bool) = (bool(__thiscall *const)(void *, unsigned __int32, real_vector3d *, bool))0x6deff0;

	s_object_data *object = object_get(unitObjectIndex);
	if (object)
	{
		float scale = object->scale;
		a3->i = a3->i / scale;
		a3->j = a3->j / scale;
		a3->k = a3->k / scale;
	}

	return sub_6DEFF0(thisptr, unitObjectIndex, a3, a4);
}

void JumpVelocityScaleHook(unsigned __int32 bipedObjectIndex) // 0x10AB0BB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?JumpVelocityScaleHook@@YAXI@Z");
	// `anonymous-namespace'::JumpVelocityScaleHook
	// unsigned __int32 bipedObjectIndex;
	// s_object_data *bipedObject;
	// float oldJumpVelocity;
	// s_biped_definition *bipedDefinition;
	// char (*const sub_BE1B30)(unsigned __int32);
	// function call : void *(*const)(unsigned long, long)
	// function call : char (*const)(unsigned __int32)

	char (__cdecl *const sub_BE1B30)(unsigned __int32) = (char (__cdecl *const)(unsigned __int32))0xbe1b30;

	s_object_data *bipedObject = object_get(bipedObjectIndex);
	if (!bipedObject)
		return;

	s_biped_definition *bipedDefinition = (s_biped_definition *)tag_get(0x62697064, bipedObject->definition_index);
	float oldJumpVelocity = bipedDefinition->jump_velocity;
	bipedDefinition->jump_velocity *= pow(bipedObject->scale, kJumpVelocityExp);
	sub_BE1B30(bipedObjectIndex);
	bipedDefinition->jump_velocity = oldJumpVelocity;
}

float __fastcall PlayerPersonalGravity(void *traits, unsigned __int32 unitObjectIndex) // 0x10AB1510
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PlayerPersonalGravity@@YIMPAXI@Z");
	// `anonymous-namespace'::PlayerPersonalGravity
	// unsigned __int32 unitObjectIndex;
	// s_object_data *unitObject;
	// float s;
	// float (*const c_player_movement_traits__get_personal_gravity)(void *);
	// function call : float (*const)(void *)

	float (__thiscall *const c_player_movement_traits__get_personal_gravity)(void *) = (float(__thiscall *const)(void *))0x5cc200;

	float s = 1.0f;
	s_object_data *unitObject = object_get(unitObjectIndex);
	if (unitObject)
		s = pow(unitObject->scale, kGravityExp);

	return c_player_movement_traits__get_personal_gravity(traits) * s;
}

__declspec(naked) void PlayerPersonalGravityHook() // 0x10AB1600
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PlayerPersonalGravityHook@@YAXXZ");
	// procedure flags: nofpo

	__asm
	{
		mov edx, [ebp + 8]
		call PlayerPersonalGravity
		push 0xBAF505
		ret
	}
}

void *__fastcall BipedCreateRigidBodyHook(void *thisptr, void *unused, s_biped_physics *bipedPhysics, __int32 a4, __int32 a5, unsigned __int32 collisionFilter_, __int32 shapeIndex, bool hasFriction, char a9) // 0x10AAFD10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BipedCreateRigidBodyHook@@YIPAXPAX0PAUs_biped_physics@hades_file_local@@HHIH_ND@Z");
	// `anonymous-namespace'::BipedCreateRigidBodyHook
	// char a9;
	// s_object_data *object;
	// void *(*const BipedCreateRigidBody)(void *, s_biped_physics *, __int32, __int32, unsigned __int32, __int32, bool, char);
		// void *ret;
		// float oldMass;
	// function call : void *(*const)(void *, s_biped_physics *, __int32, __int32, unsigned __int32, __int32, bool, char)
	// function call : void *(*const)(void *, s_biped_physics *, __int32, __int32, unsigned __int32, __int32, bool, char)

	void *(__thiscall *const BipedCreateRigidBody)(void *, s_biped_physics *, __int32, __int32, unsigned __int32, __int32, bool, char) = (void *(__thiscall *const)(void *, s_biped_physics *, __int32, __int32, unsigned __int32, __int32, bool, char))0x5e22c0;

	s_object_data *object = object_get(*(unsigned long *)((unsigned char *)thisptr + 0x8));
	if (object)
	{
		float oldMass = bipedPhysics->Mass;
		bipedPhysics->Mass *= pow(object->scale, kMassExp);
		void *ret = BipedCreateRigidBody(thisptr, bipedPhysics, a4, a5, collisionFilter_, shapeIndex, hasFriction, a9);
		bipedPhysics->Mass = oldMass;
		return ret;
	}

	return BipedCreateRigidBody(thisptr, bipedPhysics, a4, a5, collisionFilter_, shapeIndex, hasFriction, a9);
}

_extern bool _sub_10AB12C0(unsigned __int32, unsigned __int32);
bool PlayerCollisionDamageHook(unsigned __int32 bipedObjectIndex, unsigned __int32 otherBipedObjectIndex) // 0x10AB12C0
{
	// `anonymous-namespace'::PlayerCollisionDamageHook
	// unsigned __int32 otherBipedObjectIndex;
	// bool *const game_is_multiplayer;
	// bool (*const multiplayer_object_should_cause_collision_damage)(unsigned __int32, unsigned __int32);
	{
		// s_object_data *objectB;
		// s_object_data *objectA;
		{
			// float d;
			// float maxScale;
			// float minScale;
		}
	}
	// function call : bool (*const)(unsigned __int32, unsigned __int32)
	todo("implement");
	bool __result = _sub_10AB12C0(bipedObjectIndex, otherBipedObjectIndex);
	return __result;
}

void LandingDamageResponseHook(unsigned __int32 unitObjectIndex, unsigned __int32 a2, unsigned __int32 damageEffectTagIndex, real_vector3d *a4, real_vector3d *a5, float a6, float responseScale, __int32 a8) // 0x10AB0D00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LandingDamageResponseHook@@YAXIIIPAUreal_vector3d@@0MMH@Z");
	// `anonymous-namespace'::LandingDamageResponseHook
	// __int32 a8;
	// void (*const LandingDamageResponse)(unsigned __int32, unsigned __int32, unsigned __int32, real_vector3d *, real_vector3d *, float, float, __int32);
	// function call : void (*const)(unsigned __int32, unsigned __int32, unsigned __int32, real_vector3d *, real_vector3d *, float, float, __int32)

	void (__cdecl *const LandingDamageResponse)(unsigned __int32, unsigned __int32, unsigned __int32, real_vector3d *, real_vector3d *, float, float, __int32) = (void(__cdecl *const)(unsigned __int32, unsigned __int32, unsigned __int32, real_vector3d *, real_vector3d *, float, float, __int32))0x684df0;

	state.IsLandingDamage = true;
	LandingDamageResponse(unitObjectIndex, a2, damageEffectTagIndex, a4, a5, a6, responseScale, a8);
	state.IsLandingDamage = false;
}

void DamageResponsePlayerEffectsHook(unsigned __int32 uintObjectIndex, __int32 localPlayerIndex, unsigned __int32 damageResponseTagIndex, __int32 a4, real_vector3d *a5, float a6, float scale, bool a8) // 0x10AB0730
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DamageResponsePlayerEffectsHook@@YAXIHIHPAUreal_vector3d@@MM_N@Z");
	// `anonymous-namespace'::DamageResponsePlayerEffectsHook
	// bool a8;
	// s_object_data *unitObject;
	// void (*const sub_684F30)(unsigned __int32, __int32, unsigned __int32, __int32, real_vector3d *, float, float, bool);
	// function call : void (*const)(unsigned __int32, __int32, unsigned __int32, __int32, real_vector3d *, float, float, bool)

	void (__cdecl *const sub_684F30)(unsigned __int32, __int32, unsigned __int32, __int32, real_vector3d *, float, float, bool) = (void (__cdecl *const)(unsigned __int32, __int32, unsigned __int32, __int32, real_vector3d *, float, float, bool))0x684f30;

	s_object_data *unitObject = object_get(uintObjectIndex);
	if (unitObject)
	{
		if (state.IsLandingDamage)
		{
			scale = scale * unitObject->scale;
		}
		else if (unitObject->scale < 1.0f)
		{
			scale = pow(unitObject->scale, 0.4f) * scale;
		}
	}

	sub_684F30(uintObjectIndex, localPlayerIndex, damageResponseTagIndex, a4, a5, a6, scale, a8);
}

bool ModelTargetTestHook(__int32 a1, unsigned __int32 objectIndex, __int32 a3, char a4, char a5, char a6, __int32 a7, unsigned char *target, __int32 a9, __int32 a10, real_vector3d *a11, __int32 a12, void *data) // 0x10AB0FA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ModelTargetTestHook@@YA_NHIHDDDHPAEHHPAUreal_vector3d@@HPAX@Z");
	// `anonymous-namespace'::ModelTargetTestHook
	// void *data;
	// bool (*const model_target_test)(__int32, unsigned __int32, __int32, char, char, char, __int32, unsigned char *, __int32, __int32, real_vector3d *, __int32, void *);
	// s_object_data *object;
	// float oldRadius;
	// bool result;
	// float &targetRadius;
	// function call : bool (*const)(__int32, unsigned __int32, __int32, char, char, char, __int32, unsigned char *, __int32, __int32, real_vector3d *, __int32, void *)

	bool (__cdecl *const model_target_test)(__int32, unsigned __int32, __int32, char, char, char, __int32, unsigned char *, __int32, __int32, real_vector3d *, __int32, void *) = (bool (__cdecl *const)(__int32, unsigned __int32, __int32, char, char, char, __int32, unsigned char *, __int32, __int32, real_vector3d *, __int32, void *))0x58af40;

	s_object_data *object = object_get(objectIndex);
	if (!object)
		return false;

	if (!target)
		return false;

	float &targetRadius = *(float *)(target + 8);
	float oldRadius = targetRadius;
	targetRadius = targetRadius * object->scale;

	bool result = model_target_test(a1, objectIndex, a3, a4, a5, a6, a7, target, a9, a10, a11, a12, data);
	targetRadius = oldRadius;
	return result;
}

void ShieldDownParticleEffectHook(unsigned __int32 effectDatumIndex, unsigned short eventIndex) // 0x10AB1D70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ShieldDownParticleEffectHook@@YAXIG@Z");
	// `anonymous-namespace'::ShieldDownParticleEffectHook
	// unsigned short eventIndex;
	// s_effect_datum *effect;
	// void (*const ShieldDownParticleEffect)(unsigned __int32, unsigned short);
		// s_object_data *object;
	// function call : void (*const)(unsigned __int32, unsigned short)

	void (__cdecl *const ShieldDownParticleEffect)(unsigned __int32, unsigned short) = (void(__cdecl *const)(unsigned __int32, unsigned short))0x5bdf40;

	s_effect_datum *effect = tls_getd().effect->try_and_get(effectDatumIndex);
	if (effect && effect->primary_scale == 7388.0f)
	{
		s_object_data *object = object_get(effect->object_index);
		if (object->scale < 0.75f)
			return;
	}

	ShieldDownParticleEffect(effectDatumIndex, eventIndex);
}

_extern void _sub_10AB02F0(unsigned __int32, __int32, void *);
void BipedPhysicsHook2(unsigned __int32 objectIndex, __int32 a2, void *a3) // 0x10AB02F0
{
	// `anonymous-namespace'::BipedPhysicsHook2
	// void *a3;
	// s_object_data *object;
	// constexpr void (*const `BipedPhysicsHook2'::`2'::sub_BB01B0)(unsigned __int32, __int32, void *); // constant == 12255664
	{
	}
	// function call : void (*const)(unsigned __int32, __int32, void *)
	todo("implement");
	_sub_10AB02F0(objectIndex, a2, a3);
}

_extern void _sub_10AB0130(__int32);
void BipedPhysicsHook1(__int32 objectIndex) // 0x10AB0130
{
	// `anonymous-namespace'::BipedPhysicsHook1
	// static ...; // 0x10AB0280
	// static ...; // 0x10AB0274
	// static ...; // 0x10AB026C
	// __int32 objectIndex;
	// void (*const sub_B73C00)(unsigned __int32);
	// s_object_data *object;
	{
	}
	// function call : void (*const)(unsigned __int32)
	todo("implement");
	_sub_10AB0130(objectIndex);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_physics_model_pill>::try_get_element(__int32, s_physics_model_pill **) const;
template s_datum * c_data_array<s_datum>::try_and_get(unsigned long);
template s_physics_model_pill & c_tag_block<s_physics_model_pill>::operator[](__int32);
template s_physics_model_pill * c_tag_block<s_physics_model_pill>::get_element(__int32) const;

/* ---------- explicit instantiations */
template bool c_tag_block<s_havok_shape_data<hkCapsuleShape> >::try_get_element(__int32, s_havok_shape_data<hkCapsuleShape> **) const;
