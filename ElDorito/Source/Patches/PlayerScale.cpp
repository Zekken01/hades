/* ---------- headers */

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
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
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

struct lambda_1;
struct real_matrix4x3;
struct real_vector3d;
struct s_state;
namespace
{
	struct hkVector4;
	struct hkCapsuleShape;
	struct PlayerState;
	struct s_biped_physics;
	struct s_biped_physics_data1;
	struct ZoneShape;
}

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

namespace
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
struct s_state
{
	bool IsValid; // 0x0
	bool IsLandingDamage; // 0x1
	PlayerState Players[16]; // 0x4
};
// static_assert(sizeof(s_state) == 2308, "Invalid s_state size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

namespace
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
// static_assert(sizeof(s_biped_physics) == 68, "Invalid s_biped_physics size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

namespace
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
// static_assert(sizeof(s_biped_physics_data1) == 364, "Invalid s_biped_physics_data1 size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

namespace
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

namespace Patches
{
	namespace PlayerScale
	{
		extern void ApplyAll();
		extern void Tick();
		extern void UpdatePlayerScale(__int32 playerIndex);
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern float const kPlayerScales[17]; // 0x111B1140
	extern float const kMaxPlayerScale; // 0x12466758
	extern float kSpeedExp; // 0x113548A4
	extern float kMeleeRangeExp; // 0x113548A8
	extern float kMassExp; // 0x113548AC
	extern float kGravityExp; // 0x113548B0
	extern float kJumpVelocityExp; // 0x113548B4
	extern float kAirborneAccelerationScale; // 0x113548B8
	extern float kGroundAccelerationScale; // 0x113548BC
}
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

		_extern void _sub_10AB2060();
		void Tick() // 0x10AB2060
		{
			mangled_x86(MANGLED_TODO, "?Tick@PlayerScale@Patches@@YAXXZ");
			// procedure flags: nofpo
			// bool (*const game_options_is_valid)();
			{
				// __int32 i;
				{
					// PlayerState &playerState;
				}
			}
			// function call : bool (*const)()
			todo("implement");
			_sub_10AB2060();
		}

		_extern void _sub_10AB2150(__int32);
		void UpdatePlayerScale(__int32 playerIndex) // 0x10AB2150
		{
			mangled_x86(MANGLED_TODO, "?UpdatePlayerScale@PlayerScale@Patches@@YAXH@Z");
			// __int32 playerIndex;
			todo("implement");
			_sub_10AB2150(playerIndex);
		}
	}
}

/* ---------- private code */
