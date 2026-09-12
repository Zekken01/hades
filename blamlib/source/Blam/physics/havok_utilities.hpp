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

extern hkpShape *_sub_10AAB350(hkpShape *);
_inline hkpShape *__fastcall havok_transform_wrapper_shape_get_child_shape(hkpShape *shape) // 0x10AAB350
{
	mangled_x86(MANGLED_TODO, "?havok_transform_wrapper_shape_get_child_shape@@YIPAUhkpShape@@PAU1@@Z");
	// hkpShape *shape;
	todo("implement");
	hkpShape * __result = _sub_10AAB350(shape);
	return __result;
}

_inline hkpShape *havok_shape_from_container(hkShapeContainer *container) // 0x10AAB330
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?havok_shape_from_container@@YAPAUhkpShape@@PAUhkShapeContainer@@@Z");
	// hkShapeContainer *container;

	return (hkpShape *)((char *)container - 0x10);
}

_extern bool _sub_10AAB650(hkpShape *);
_inline bool is_havok_convex_shape(hkpShape *shape) // 0x10AAB650
{
	mangled_x86(MANGLED_TODO, "?is_havok_convex_shape@@YA_NPAUhkpShape@@@Z");
	// static ...; // 0x10AAB6AC
	// static ...; // 0x10AAB6A4
// $LN12:
// $LN2:
	// hkpShape *shape;
	todo("implement");
	bool __result = _sub_10AAB650(shape);
	return __result;
}

_extern void _sub_10F1AE00(hkTransform const &, hkVector4 const &, hkVector4 const &, float, hkAabb &);
_inline void hkAabbUtil::calcAaab(hkTransform const &BvToWorld, hkVector4 const &halfExtents, hkVector4 const &center, float extraRadius, hkAabb &aabbOut) // 0x10F1AE00
{
	mangled_x86(MANGLED_TODO, "?calcAaab@hkAabbUtil@@SAXABUhkTransform@@ABUhkVector4@@1MAAUhkAabb@@@Z");
	// hkAabb &aabbOut;
	// float const cz;
	// float const cx;
	// float const hw;
	// float const hz;
	// float const cy;
	// float const hx;
	// float const hy;
	todo("implement");
	_sub_10F1AE00(BvToWorld, halfExtents, center, extraRadius, aabbOut);
}

/* ---------- private code */

#endif // __BLAM_PHYSICS_HAVOK_UTILITIES_HPP__
