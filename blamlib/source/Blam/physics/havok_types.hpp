#ifndef __BLAM_PHYSICS_HAVOK_TYPES_HPP__
#define __BLAM_PHYSICS_HAVOK_TYPES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

struct hkAabb;
struct hkArrayBase;
struct hkMatrix3;
struct hkMatrix4;
struct hkQuaternion;
struct hkRotation;
struct hkShapeContainer;
struct hkSweptTransform;
struct hkTransform;
struct hkVector4;
struct hkWorld;
struct hkpBoxShape;
struct hkpBroadPhaseHandle;
struct hkpBvShape;
struct hkpCapsuleShape;
struct hkpCdBody;
struct hkpCollidable;
struct hkpConvexShape;
struct hkpConvexTransformShape;
struct hkpConvexTranslateShape;
struct hkpConvexVerticesConnectivity;
struct hkpConvexVerticesShape;
struct hkpEntity;
struct hkpListShape;
struct hkpMaterial;
struct hkpMoppBvTreeShape;
struct hkpMoppCode;
struct hkpMotion;
struct hkpMotionState;
struct hkpReferencedObject;
struct hkpRigidBody;
struct hkpShape;
struct hkpShapeCollection;
struct hkpSingleShapeContainer;
struct hkpTransformShape;
struct hkpTriangleShape;
struct hkpTypedBroadPhaseHandle;
struct hkpWorldCinfo;
struct hkpWorldObject;

/* ---------- constants */

enum hkpShapeType
{
	HK_SHAPE_INVALID = 0,
	HK_SHAPE_CONVEX,
	HK_SHAPE_COLLECTION,
	HK_SHAPE_SPHERE,
	HK_SHAPE_CYLINDER,
	HK_SHAPE_TRIANGLE,
	HK_SHAPE_BOX,
	HK_SHAPE_CAPSULE,
	HK_SHAPE_CONVEX_VERTICES,
	HK_SHAPE_UNKNOWN9,
	HK_SHAPE_LIST,
	HK_SHAPE_MOPP_EMBEDDED,
	HK_SHAPE_CONVEX_TRANSLATE,
	HK_SHAPE_CONVEX_TRANSFORM,
	HK_SHAPE_UNKNOWN14,
	HK_SHAPE_UNKNOWN15,
	HK_SHAPE_MULTI_SPHERE,
	HK_SHAPE_UNKNOWN17,
	HK_SHAPE_UNKNOWN18,
	HK_SHAPE_BV_TREE,
	HK_SHAPE_UNKNOWN20,
	HK_SHAPE_UNKNOWN21,
	HK_SHAPE_UNKNOWN22,
	HK_SHAPE_UNKNOWN23,
	HK_SHAPE_UNKNOWN24,
	HK_SHAPE_BV,
	HK_SHAPE_UNKNOWN26,
	HK_SHAPE_MOPP,
	HK_SHAPE_TRANSFORM,
	HK_SHAPE_PHANTOM_CALLBACK,
	HK_SHAPE_USER0,
	HK_SHAPE_USER1,
	HK_SHAPE_USER2,
	HK_SHAPE_MAX_ID,
};

/* ---------- definitions */

struct alignas(16) hkVector4  // hades: Havok's 16-byte SIMD alignment; temporaries land on 16-byte slots
{
	float x; // 0x0
	float y; // 0x4
	float z; // 0x8
	float w; // 0xC
	float &operator()(__int32);
	float const &operator()(__int32) const;
};
static_assert(sizeof(hkVector4) == 16, "Invalid hkVector4 size");

struct hkQuaternion
{
	hkVector4 m_vec; // 0x0
};
static_assert(sizeof(hkQuaternion) == 16, "Invalid hkQuaternion size");

struct hkMatrix3
{
	hkVector4 m_col0; // 0x0
	hkVector4 m_col1; // 0x10
	hkVector4 m_col2; // 0x20
};
static_assert(sizeof(hkMatrix3) == 48, "Invalid hkMatrix3 size");

struct hkMatrix4
{
	hkVector4 m_col0; // 0x0
	hkVector4 m_col1; // 0x10
	hkVector4 m_col2; // 0x20
	hkVector4 m_col3; // 0x30
};
static_assert(sizeof(hkMatrix4) == 64, "Invalid hkMatrix4 size");

struct hkSweptTransform
{
	hkVector4 m_centerOfMass0; // 0x0
	hkVector4 m_centerOfMass1; // 0x10
	hkQuaternion m_rotation0; // 0x20
	hkQuaternion m_rotation1; // 0x30
	hkVector4 m_centerOfMassLocal; // 0x40
};
static_assert(sizeof(hkSweptTransform) == 80, "Invalid hkSweptTransform size");

struct hkAabb
{
	hkVector4 m_min; // 0x0
	hkVector4 m_max; // 0x10
};
static_assert(sizeof(hkAabb) == 32, "Invalid hkAabb size");

struct hkRotation :
	public hkMatrix3
{
};
static_assert(sizeof(hkRotation) == 48, "Invalid hkRotation size");

struct hkTransform
{
	hkRotation m_rotation; // 0x0
	hkVector4 m_translation; // 0x30
};
static_assert(sizeof(hkTransform) == 64, "Invalid hkTransform size");

struct hkpReferencedObject
{
	unsigned short m_memSizeAndFlags; // 0x0
	unsigned short m_referenceCount; // 0x2
};
static_assert(sizeof(hkpReferencedObject) == 4, "Invalid hkpReferencedObject size");

struct hkArrayBase
{
	void *m_data; // 0x0
	__int32 m_size; // 0x4
	__int32 m_capacityAndFlags; // 0x8
};
static_assert(sizeof(hkArrayBase) == 12, "Invalid hkArrayBase size");

struct hkpMoppCode
{
	void *vftable; // 0x0
	hkpReferencedObject m_referenceObject; // 0x4
};
static_assert(sizeof(hkpMoppCode) == 8, "Invalid hkpMoppCode size");

struct hkpShape
{
	void **vftable; // 0x0
	hkpReferencedObject m_referenceObject; // 0x4
	unsigned long m_userData; // 0x8
	unsigned __int32 m_type; // 0xC
	_inline hkShapeContainer const *getContainer() const;
};
static_assert(sizeof(hkpShape) == 16, "Invalid hkpShape size");

struct hkShapeContainer
{
	typedef char ShapeBuffer[512];
	void **vftable; // 0x0
	__int32 getNumChildShapes() const;
	_inline unsigned __int32 getFirstKey() const;
	_inline unsigned __int32 getNextKey(unsigned __int32 oldKey) const;
	unsigned __int32 getCollisionFilterInfo(unsigned __int32) const;
	_inline hkpShape *getChildShape(unsigned __int32 key, void *buffer) const;
};
static_assert(sizeof(hkShapeContainer) == 4, "Invalid hkShapeContainer size");

struct hkpSingleShapeContainer :
	public hkShapeContainer
{
	hkpShape *m_childShape; // 0x4
};
static_assert(sizeof(hkpSingleShapeContainer) == 8, "Invalid hkpSingleShapeContainer size");

#pragma pack(push, 4)
struct hkpConvexShape :
	public hkpShape
{
	float m_radius; // 0x10
};
#pragma pack(pop)
static_assert(sizeof(hkpConvexShape) == 20, "Invalid hkpConvexShape size");

struct hkpConvexTransformShape :
	public hkpConvexShape
{
	hkpSingleShapeContainer m_childShape; // 0x14
	unsigned __int32 m_childShapeSize; // 0x1C
	hkTransform m_transform; // 0x20
};
static_assert(sizeof(hkpConvexTransformShape) == 96, "Invalid hkpConvexTransformShape size");

struct hkpConvexTranslateShape :
	public hkpConvexShape
{
	hkpSingleShapeContainer m_childShape; // 0x14
	unsigned __int32 m_childShapeSize; // 0x1C
	hkVector4 m_translation; // 0x20
};
static_assert(sizeof(hkpConvexTranslateShape) == 48, "Invalid hkpConvexTranslateShape size");

struct hkpConvexVerticesShape :
	public hkpConvexShape
{
	public:
	struct FourVectors
	{
		hkVector4 m_x; // 0x0
		hkVector4 m_y; // 0x10
		hkVector4 m_z; // 0x20
	};
	static_assert(sizeof(FourVectors) == 48, "Invalid FourVectors size");
	public:
	unsigned char __pad0[12]; // 0x14
	hkVector4 m_aabbHalfExtents; // 0x20
	hkVector4 m_aabbCenter; // 0x30
	hkArrayBase m_rotatedVertices; // 0x40
	__int32 m_numVertices; // 0x4C
	hkArrayBase m_planeEquation; // 0x50
	hkpConvexVerticesConnectivity *m_connectivity; // 0x5C
};
static_assert(sizeof(hkpConvexVerticesShape) == 96, "Invalid hkpConvexVerticesShape size");

#pragma pack(push, 4)
struct hkpBvShape :
	public hkpShape
{
	hkpShape *m_boundingVolumeShape; // 0x10
	hkpSingleShapeContainer m_child_shape; // 0x14
};
#pragma pack(pop)
static_assert(sizeof(hkpBvShape) == 28, "Invalid hkpBvShape size");

struct hkpShapeCollection :
	public hkpShape,
	public hkShapeContainer
{
	char m_disableWelding; // 0x14
};
static_assert(sizeof(hkpShapeCollection) == 24, "Invalid hkpShapeCollection size");

struct hkpListShape :
	public hkpShapeCollection
{
	hkArrayBase m_childInfo; // 0x18
	unsigned char __pad0[12]; // 0x24
	hkVector4 m_aabbHalfExtents; // 0x30
	hkVector4 m_aabbCenter; // 0x40
};
static_assert(sizeof(hkpListShape) == 80, "Invalid hkpListShape size");

struct hkpBoxShape :
	public hkpConvexShape
{
	unsigned char __pad0[12]; // 0x14
	hkVector4 m_halfExtents; // 0x20
};
static_assert(sizeof(hkpBoxShape) == 48, "Invalid hkpBoxShape size");

struct hkpCapsuleShape :
	public hkpConvexShape
{
	long unknown[3]; // 0x14
	hkVector4 m_vertexA; // 0x20
	hkVector4 m_vertexB; // 0x30
};
static_assert(sizeof(hkpCapsuleShape) == 64, "Invalid hkpCapsuleShape size");

struct hkpTriangleShape :
	public hkpConvexShape
{
	unsigned short m_weldingInfo; // 0x14
	unsigned char m_weldingType; // 0x16
	unsigned char m_isExtruded; // 0x17
	unsigned char __pad0[8]; // 0x18
	hkVector4 m_vertexA; // 0x20
	hkVector4 m_vertexB; // 0x30
	hkVector4 m_vertexC; // 0x40
	hkVector4 m_extrusion; // 0x50
};
static_assert(sizeof(hkpTriangleShape) == 96, "Invalid hkpTriangleShape size");

#pragma pack(push, 4)
struct hkpMoppBvTreeShape :
	public hkpShape,
	public hkpSingleShapeContainer
{
	hkpMoppCode *m_code; // 0x18
};
#pragma pack(pop)
static_assert(sizeof(hkpMoppBvTreeShape) == 28, "Invalid hkpMoppBvTreeShape size");

struct hkpTransformShape :
	public hkpShape
{
	hkpSingleShapeContainer m_childShape; // 0x10
	unsigned char __pad0[8]; // 0x18
	hkRotation m_rotation; // 0x20
	hkVector4 m_translation; // 0x50
};
static_assert(sizeof(hkpTransformShape) == 96, "Invalid hkpTransformShape size");

struct hkpWorldObject
{
	void *vftable; // 0x0
	hkpReferencedObject m_ref; // 0x4
	hkWorld *m_world; // 0x8
	void *field_C; // 0xC
	__int32 m_userData; // 0x10
	__int32 field_14; // 0x14
	__int32 m_motionState; // 0x18
	__int32 field_1C; // 0x1C
	char field_20; // 0x20
	char field_21; // 0x21
	char field_22; // 0x22
	char field_23; // 0x23
	__int32 field_24; // 0x24
	short field_28; // 0x28
	short m_qualityType; // 0x2A
	__int32 m_collisionFilterInfo; // 0x2C
	float m_allowedPenetrationDepth; // 0x30
	__int32 field_34; // 0x34
	__int32 field_38; // 0x38
	__int32 field_3C; // 0x3C
	__int32 field_40; // 0x40
	__int32 field_44; // 0x44
	char field_48; // 0x48
	char field_49; // 0x49
	char DoesNotInteractWithEnvironemnt; // 0x4A
	char field_4B; // 0x4B
	hkArrayBase m_properties; // 0x4C
};
static_assert(sizeof(hkpWorldObject) == 88, "Invalid hkpWorldObject size");

struct hkpMaterial
{
	char m_responseType; // 0x0
	float m_friction; // 0x4
	float m_restitution; // 0x8
};
static_assert(sizeof(hkpMaterial) == 12, "Invalid hkpMaterial size");
static_assert(offsetof(hkpMaterial, m_friction) == 0x4, "hkpMaterial::m_friction moved when its reconstructed padding was removed");

struct hkpMotionState
{
	hkMatrix4 m_transform; // 0x0
	hkSweptTransform m_sweptTransform; // 0x40
	hkVector4 m_deltaAngle; // 0x90
	float m_objectRadius; // 0xA0
	float m_linearDamping; // 0xA4
	float m_angularDamping; // 0xA8
	float m_maxLinearVelocity; // 0xAC
};
static_assert(sizeof(hkpMotionState) == 176, "Invalid hkpMotionState size");

struct hkpMotion
{
	void **vftable; // 0x0
	hkpReferencedObject m_ref; // 0x4
	unsigned char m_type; // 0x8
	unsigned char m_deactivationIntegrateCounter; // 0x9
	unsigned short m_deactivationNumInactiveFrames[2]; // 0xA
	hkpMotionState m_motionState; // 0x10
	float m_maxAngularVelocity; // 0xC0
	unsigned __int32 m_rigidBodyDeactivatorType; // 0xC4
	__int32 field_C8; // 0xC8
	__int32 field_CC; // 0xCC
	__int32 field_D0; // 0xD0
	__int32 field_D4; // 0xD4
	__int32 field_D8; // 0xD8
	float m_mass; // 0xDC
	hkVector4 m_linearVelocity; // 0xE0
	hkVector4 m_angularVelocity; // 0xF0
	hkVector4 field_100; // 0x100
	hkVector4 field_110; // 0x110
	__int32 field_120; // 0x120
	__int32 field_124; // 0x124
	__int32 field_128; // 0x128
	__int32 field_12C; // 0x12C
};
static_assert(sizeof(hkpMotion) == 304, "Invalid hkpMotion size");
static_assert(offsetof(hkpMotion, m_motionState) == 0x10, "hkpMotion::m_motionState moved when its reconstructed padding was removed");

struct hkpEntity :
	public hkpWorldObject
{
	hkpMaterial m_material; // 0x58
	__int32 field_64; // 0x64
	unsigned short m_islandEntityIndex; // 0x68
	unsigned short field_6A; // 0x6A
	__int32 field_6C; // 0x6C
	unsigned short m_storageIndex; // 0x70
	unsigned short m_processContactCallbackDelay; // 0x72
	hkArrayBase m_constraintsMaster; // 0x74
	hkArrayBase m_constraintsSlave; // 0x80
	hkArrayBase m_constraintRuntime; // 0x8C
	unsigned __int32 m_simulationIsland; // 0x98
	unsigned char m_autoRemoveLevel; // 0x9C
	unsigned char m_numUserDatasInContactPointProperties; // 0x9D
	unsigned char m_uid; // 0x9E
	char field_9F; // 0x9F
	hkpMotion m_motion; // 0xA0
	void *m_collisionListeners; // 0x1D0
	unsigned __int32 m_collisionListeneCount; // 0x1D4
	void *m_actionListeners; // 0x1D8
	unsigned __int32 m_actionListenerCount; // 0x1DC
	hkArrayBase field_1E0; // 0x1E0
	__int32 field_1EC; // 0x1EC
};
static_assert(sizeof(hkpEntity) == 496, "Invalid hkpEntity size");

struct hkpCdBody
{
	hkpShape *m_shape; // 0x0
	__int32 m_shapeKey; // 0x4
	__int32 m_motion; // 0x8
	hkpCdBody *m_parent; // 0xC
};
static_assert(sizeof(hkpCdBody) == 16, "Invalid hkpCdBody size");

struct hkpBroadPhaseHandle
{
	unsigned __int32 m_id; // 0x0
};
static_assert(sizeof(hkpBroadPhaseHandle) == 4, "Invalid hkpBroadPhaseHandle size");

struct hkpTypedBroadPhaseHandle :
	public hkpBroadPhaseHandle
{
	unsigned char m_type; // 0x4
	unsigned char m_ownerOffset; // 0x5
	unsigned short m_objectQualityType; // 0x6
	unsigned __int32 m_collisionFilterInfo; // 0x8
};
static_assert(sizeof(hkpTypedBroadPhaseHandle) == 12, "Invalid hkpTypedBroadPhaseHandle size");

struct hkpCollidable :
	public hkpCdBody
{
	char m_ownerOffset; // 0x10
	unsigned char m_forceCollideOntoPpu; // 0x11
	unsigned short m_shapeSizeOnSpu; // 0x12
	hkpTypedBroadPhaseHandle m_broadPhaseHandle; // 0x14
};
static_assert(sizeof(hkpCollidable) == 32, "Invalid hkpCollidable size");

struct hkpWorldCinfo
{
	void *vtable; // 0x0
	hkpReferencedObject m_referenceObject; // 0x4
	float m_gravity[4]; // 0x8
	float field_18; // 0x18
	float m_contactRestingVelocity; // 0x1C
	__int32 m_broadPhaseQuerySize; // 0x20
	float float24; // 0x24
	char byte28; // 0x28
	char field_29; // 0x29
	char field_2A; // 0x2A
	char field_2B; // 0x2B
	unsigned char __pad0[4]; // 0x2C
	hkAabb m_broadPhaseWorldAabb; // 0x30
	float m_collisionTolerance; // 0x50
	__int32 m_collisionFilter; // 0x54
	__int32 m_convexListFilter; // 0x58
	float m_expectedMaxLinearVelocity; // 0x5C
	__int32 m_sizeOfToiEventQueue; // 0x60
	float m_expectedMinPsiDeltaTime; // 0x64
	__int32 field_68; // 0x68
	__int32 field_6C; // 0x6C
	char m_contactPointGeneration; // 0x70
	unsigned char __pad1[3]; // 0x71
	float m_solverDamp; // 0x74
	float float78; // 0x78
	__int32 m_solverIterations; // 0x7C
	__int32 m_solverMicrosteps; // 0x80
	char byte84; // 0x84
	unsigned char __pad2[3]; // 0x85
	float m_snapCollisionToConvexEdgeThreshold; // 0x88
	float m_snapCollisionToConcaveEdgeThreshold; // 0x8C
	char byte90; // 0x90
	char byte91; // 0x91
	unsigned char __pad3[2]; // 0x92
	float m_iterativeLinearCastEarlyOutDistance; // 0x94
	__int32 m_iterativeLinearCastMaxIterations; // 0x98
	float float9C; // 0x9C
	float floatA0; // 0xA0
	char byteA4; // 0xA4
	char byteA5; // 0xA5
	char byteA6; // 0xA6
	char byteA7; // 0xA7
	char byteA8; // 0xA8
	unsigned char __pad4[3]; // 0xA9
	float m_deactivationReferenceDistance; // 0xAC
	float m_toiCollisionResponseRotateNormal; // 0xB0
	char field_B4; // 0xB4
	char field_B5; // 0xB5
	char field_B6; // 0xB6
	unsigned char __pad5[1]; // 0xB7
	__int32 m_minDesiredIslandSize; // 0xB8
	char m_processActionsInSingleThread; // 0xBC
	unsigned char __pad6[3]; // 0xBD
	float m_frameMarkerPsiSnap; // 0xC0
	unsigned char __pad7[12]; // 0xC4
};
static_assert(sizeof(hkpWorldCinfo) == 208, "Invalid hkpWorldCinfo size");

struct hkpRigidBody :
	public hkpEntity
{
};
static_assert(sizeof(hkpRigidBody) == 496, "Invalid hkpRigidBody size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

inline float &hkVector4::operator()(__int32 i) // 0x10F07FA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??RhkVector4@@QAEAAMH@Z");
	// __int32 i;

	return ((float *)this)[i];
}

inline hkShapeContainer const *hkpShape::getContainer() const // 0x10F08110
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?getContainer@hkpShape@@QBEPBUhkShapeContainer@@XZ");
	// hkpShape const *const this;
	// function call : hkShapeContainer const *(*)(hkpShape const *)

	return ((hkShapeContainer const *(__thiscall **)(hkpShape const *))vftable)[4](this);
}

inline unsigned __int32 hkShapeContainer::getFirstKey() const // 0x10F08190
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?getFirstKey@hkShapeContainer@@QBEIXZ");
	// hkShapeContainer const *const this;
	// function call : unsigned __int32 (*)(hkShapeContainer const *)

	return ((unsigned __int32(__thiscall **)(hkShapeContainer const *))vftable)[2](this);
}

inline unsigned __int32 hkShapeContainer::getNextKey(unsigned __int32 oldKey) const // 0x10F08210
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?getNextKey@hkShapeContainer@@QBEII@Z");
	// unsigned __int32 oldKey;
	// function call : unsigned __int32 (*)(hkShapeContainer const *, unsigned __int32)

	return ((unsigned __int32(__thiscall **)(hkShapeContainer const *, unsigned __int32))vftable)[3](this, oldKey);
}

inline hkpShape *hkShapeContainer::getChildShape(unsigned __int32 key, void *buffer) const // 0x10AAAAF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?getChildShape@hkShapeContainer@@QBEPAUhkpShape@@IPAX@Z");
	// void *buffer;
	// function call : hkpShape *(*)(hkShapeContainer const *, unsigned __int32, void *)

	return ((hkpShape *(__thiscall **)(hkShapeContainer const *, unsigned __int32, void *))vftable)[5](this, key, buffer);
}

/* ---------- private code */

#endif // __BLAM_PHYSICS_HAVOK_TYPES_HPP__
