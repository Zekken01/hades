#ifndef __BLAM_PHYSICS_HAVOK_UTILITIES_HPP__
#define __BLAM_PHYSICS_HAVOK_UTILITIES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/physics/havok_types.hpp"

/* ---------- forward declarations */

struct c_runtime_node_to_physics_model_rigid_body_index_mapping;
struct hkAabb;
struct hkAabbUtil;
struct hkShapeContainer;
struct hkTransform;
struct hkVector4;
struct hkpShape;

/* ---------- constants */

/* ---------- definitions */

struct c_runtime_node_to_physics_model_rigid_body_index_mapping
{
	public:
#pragma pack(push, 4)
	struct s_mapping
	{
		char rigid_body_indices[64]; // 0x0
		long rigid_body_count; // 0x40
	};
#pragma pack(pop)
	static_assert(sizeof(s_mapping) == 68, "Invalid s_mapping size");
	public:
	long m_node_count; // 0x0
	s_mapping m_node_to_rigid_body_mapping[256]; // 0x4
	s_mapping m_root_rigid_body_mapping; // 0x4404
};
static_assert(sizeof(c_runtime_node_to_physics_model_rigid_body_index_mapping) == 17480, "Invalid c_runtime_node_to_physics_model_rigid_body_index_mapping size");

struct hkAabbUtil
{
	static _inline void calcAaab(hkTransform const &BvToWorld, hkVector4 const &halfExtents, hkVector4 const &center, float extraRadius, hkAabb &aabbOut);
};
static_assert(sizeof(hkAabbUtil) == 1, "Invalid hkAabbUtil size");

/* ---------- prototypes */

extern _inline hkpShape *__fastcall havok_transform_wrapper_shape_get_child_shape(hkpShape *shape);
extern _inline hkpShape *havok_shape_from_container(hkShapeContainer *container);
extern _inline bool is_havok_convex_shape(hkpShape *shape);

/* ---------- globals */

/* ---------- public code */

inline hkpShape *__fastcall havok_transform_wrapper_shape_get_child_shape(hkpShape *shape) // 0x10AAB350
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?havok_transform_wrapper_shape_get_child_shape@@YIPAUhkpShape@@PAU1@@Z");

	switch (shape->m_type)
	{
	case 12:
		shape = *(hkpShape **)((unsigned char *)shape + 0x18);
		break;
	case 13:
		shape = *(hkpShape **)((unsigned char *)shape + 0x18);
		break;
	case 0x1C:
		shape = *(hkpShape **)((unsigned char *)shape + 0x14);
		break;
	}

	if (shape->m_userData == 0xFFFF00AB)
		shape = *(hkpShape **)((unsigned char *)shape + 0x14);

	return shape;
}

inline hkpShape *havok_shape_from_container(hkShapeContainer *container) // 0x10AAB330
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?havok_shape_from_container@@YAPAUhkpShape@@PAUhkShapeContainer@@@Z");

	return (hkpShape *)((char *)container - 0x10);
}

inline bool is_havok_convex_shape(hkpShape *shape) // 0x10AAB650
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?is_havok_convex_shape@@YA_NPAUhkpShape@@@Z");

	switch (shape->m_type)
	{
	case 1:
	case 3:
	case 5:
	case 6:
	case 7:
	case 8:
	case 12:
	case 13:
	case 30:
		return true;
	}

	return false;
}

inline void hkAabbUtil::calcAaab(hkTransform const &BvToWorld, hkVector4 const &halfExtents, hkVector4 const &center, float extraRadius, hkAabb &aabbOut) // 0x10F1AE00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?calcAaab@hkAabbUtil@@SAXABUhkTransform@@ABUhkVector4@@1MAAUhkAabb@@@Z");

	float const hx = fabs(BvToWorld.m_rotation.m_col1.x * halfExtents.y) + fabs(BvToWorld.m_rotation.m_col0.x * halfExtents.x) + fabs(BvToWorld.m_rotation.m_col2.x * halfExtents.z) + extraRadius;
	float const hy = fabs(BvToWorld.m_rotation.m_col1.y * halfExtents.y) + fabs(BvToWorld.m_rotation.m_col0.y * halfExtents.x) + fabs(BvToWorld.m_rotation.m_col2.y * halfExtents.z) + extraRadius;
	float const hz = fabs(BvToWorld.m_rotation.m_col1.z * halfExtents.y) + fabs(BvToWorld.m_rotation.m_col0.z * halfExtents.x) + fabs(BvToWorld.m_rotation.m_col2.z * halfExtents.z) + extraRadius;
	float const hw = fabs(BvToWorld.m_rotation.m_col1.w * halfExtents.y) + fabs(BvToWorld.m_rotation.m_col0.w * halfExtents.x) + fabs(BvToWorld.m_rotation.m_col2.w * halfExtents.z) + extraRadius;
	float const cx = BvToWorld.m_rotation.m_col0.x * center.x + BvToWorld.m_rotation.m_col1.x * center.y + BvToWorld.m_rotation.m_col2.x * center.z + BvToWorld.m_translation.x;
	float const cy = BvToWorld.m_rotation.m_col1.y * center.y + BvToWorld.m_rotation.m_col0.y * center.x + BvToWorld.m_rotation.m_col2.y * center.z + BvToWorld.m_translation.y;
	float const cz = BvToWorld.m_rotation.m_col1.z * center.y + BvToWorld.m_rotation.m_col0.z * center.x + BvToWorld.m_rotation.m_col2.z * center.z + BvToWorld.m_translation.z;
	aabbOut.m_min.x = cx - hx;
	aabbOut.m_max.x = cx + hx;
	aabbOut.m_min.z = cz - hz;
	aabbOut.m_max.z = cz + hz;
	aabbOut.m_min.y = cy - hy;
	aabbOut.m_max.y = cy + hy;
	aabbOut.m_min.w = -hw;
	aabbOut.m_max.w = hw;
}

/* ---------- private code */

#endif // __BLAM_PHYSICS_HAVOK_UTILITIES_HPP__
