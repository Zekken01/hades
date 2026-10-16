#ifndef __DEBUG_DEBUGDRAW_HPP__
#define __DEBUG_DEBUGDRAW_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Magnets.hpp"

#include <source_location>

/* ---------- forward declarations */

class CDebugDraw;
struct CDebugDrawBackend;
struct DebugDrawKey;
struct real_matrix4x3;
struct real_point2d;
struct real_point3d;
struct real_rectangle2d;
struct real_rectangle3d;
struct real_vector3d;

/* ---------- constants */

/* ---------- definitions */

struct DebugDrawKey
{
	void const *name; // 0x0
	unsigned __int32 id; // 0x4
	_inline DebugDrawKey(char const *name_, unsigned __int32 id_ = 0xFFFFFFFF);
	_inline operator bool();
	void __dflt_ctor_closure(); /* compiler_generated() */
};
static_assert(sizeof(DebugDrawKey) == 8, "Invalid DebugDrawKey size");

struct CDebugDrawBackend
{
	public:
#pragma pack(push, 4)
	struct Attributes
	{
		float lifetime; // 0x0
		char const *group; // 0x4
		DebugDrawKey cacheKey; // 0x8
		__int32 fontId; // 0x10
		float textScale; // 0x14
		bool depthTest; // 0x18
		_inline Attributes(); /* compiler_generated() */
	};
#pragma pack(pop)
	static_assert(sizeof(Attributes) == 28, "Invalid Attributes size");
#pragma pack(push, 4)
	struct AttributeScope
	{
		AttributeScope();
		~AttributeScope();
		void SetLifetime(float lifetime);
		void SetCacheKey(char const *group, DebugDrawKey key);
		void SetFont(__int32 fontId);
		void SetTextScale(float scale);
		void SetDepthTest(bool enable);
	private:
		Attributes m_prevAttributes; // 0x0
		public:
		AttributeScope & operator=(AttributeScope const &__that);
	};
#pragma pack(pop)
	static_assert(sizeof(AttributeScope) == 28, "Invalid AttributeScope size");
	public:
	static void Render();
	static void DrawPoint(real_point3d const &point, float size, long color);
	static void DrawLine(real_point3d const &p1, real_point3d const &p2, long color);
	static void DrawVector(real_point3d const &point, real_vector3d const &vector, long color);
	static void DrawTriangle(real_point3d const &p1, real_point3d const &p2, real_point3d const &p3, long color);
	static void DrawBox2dOutline(real_rectangle2d const &bounds, long color);
	static void DrawBox(real_rectangle3d const &bounds, long color);
	static void DrawBoxOriented(real_rectangle3d const &bounds, real_matrix4x3 const &matrix, long color);
	static void DrawSphereOutline(real_point3d const &center, float radius, long color);
	static void DrawString2d(real_point2d const &point, long color, long fontId, float scale, char const *format, char *va);
	static void DrawString2d(real_point2d const &point, long color, long fontId, float scale, char const *format, ...);
	static void DrawString3d(real_point3d const &point, long color, long fontId, float scale, char const *format, char *va);
	static void DrawString3d(real_point3d const &point, long color, long fontId, float scale, char const *format, ...);
	static void DrawPill(real_point3d const &base, real_vector3d const &height, float radius, long color);
	static void DrawCylinder(real_point3d const &base, real_vector3d const &height, float radius, long color);
	static void DrawCone(real_point3d const &base, real_vector3d const &up, float theta, float height, long color);
	static void DrawPhysicsShapeCapsule(real_point3d const &vertex_a, real_point3d const &vertex_b, float radius, real_matrix4x3 const &matrix, long color);
	static void Clear(char const *group, DebugDrawKey key);
	public:
	CDebugDrawBackend & operator=(CDebugDrawBackend &&__that);
	CDebugDrawBackend & operator=(CDebugDrawBackend const &__that);
};
static_assert(sizeof(CDebugDrawBackend) == 1, "Invalid CDebugDrawBackend size");

#line 75
class HADES_EXPORT CDebugDraw
#line 100
{
public:
	static long const COLOR_WHITE;
	static long const COLOR_BLACK;
	static long const COLOR_RED;
	static long const COLOR_BLUE;
	static long const COLOR_GREEN;
	static long const COLOR_YELLOW;
	static long const COLOR_PINK;
	static long const COLOR_CYAN;
	static long const COLOR_ORANGE;
	CDebugDraw(CDebugDraw const &);
	inline CDebugDraw(std::source_location loc = std::source_location::current());
	_inline CDebugDraw(char const *name);
	_inline void SetLifetime(float seconds);
	_inline void SetFont(long id);
	_inline void SetTextScale(float scale);
	_inline void SetDepthTest(bool enable);
	_inline void Clear(DebugDrawKey key);
	_inline void DrawPoint(DebugDrawKey key, real_point3d const &point, float size, long color);
	_inline void DrawLine(DebugDrawKey key, real_point3d const &p1, real_point3d const &p2, long color);
	_inline void DrawVector(DebugDrawKey key, real_point3d const &point, real_vector3d const &vector, long color);
	_inline void DrawTriangle(DebugDrawKey key, real_point3d const &p1, real_point3d const &p2, real_point3d const &p3, long color);
	_inline void DrawBox2dOutline(DebugDrawKey key, real_rectangle2d const &bounds, long color);
	_inline void DrawBox(DebugDrawKey key, real_rectangle3d const &bounds, long color);
	_inline void DrawBoxOriented(DebugDrawKey key, real_rectangle3d const &bounds, real_matrix4x3 const &matrix, long color);
	_inline void DrawSphereOutline(DebugDrawKey key, real_point3d const &center, float radius, long color);
	_inline void __cdecl DrawString2d(DebugDrawKey key, real_point2d const &point, long color, char const *format, ...);
	_inline void __cdecl DrawString3d(DebugDrawKey key, real_point3d const &point, long color, char const *format, ...);
	_inline void DrawPill(DebugDrawKey key, real_point3d const &base, real_vector3d const &height, float radius, long color);
	_inline void DrawCylinder(DebugDrawKey key, real_point3d const &base, real_vector3d const &height, float radius, long color);
	_inline void DrawCone(DebugDrawKey key, real_point3d const &base, real_vector3d const &up, float theta, float height, long color);
	_inline void DrawPhysicsShapeCapsule(DebugDrawKey key, real_point3d const &vertex_a, real_point3d const &vertex_b, float radius, real_matrix4x3 const &matrix, long color);
	float GetLineHeight(__int32 fontId) const;
private:
	_inline void SetAttributes(CDebugDrawBackend::AttributeScope &attr, DebugDrawKey key);
	char const *m_name; // 0x0
	float m_lifetime; // 0x4
	__int32 m_fontId; // 0x8
	float m_textScale; // 0xC
	bool m_depthTest; // 0x10
public:
	// void __dflt_ctor_closure(); /* compiler_generated(): emitted by the dllexport default argument */
	public:
	CDebugDraw & operator=(CDebugDraw const &__that) = default;  // hades: implicit (trivial: one block copy)
};
static_assert(sizeof(CDebugDraw) == 20, "Invalid CDebugDraw size");

/* ---------- prototypes */

extern __int32 AllocateCacheEntry();
extern __int32 FindCacheEntry(char const *group, DebugDrawKey cacheKey);
extern void EvictCacheEntry(char const *group, DebugDrawKey cacheKey);

extern _inline bool operator==(DebugDrawKey const &a, DebugDrawKey const &b);

/* ---------- globals */

/* ---------- public code */

inline DebugDrawKey::DebugDrawKey(char const *name_, unsigned __int32 id_) // 0x10817E20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0DebugDrawKey@@QAE@PBDI@Z");

	name = (void const *)name_;
	id = id_;
}

inline DebugDrawKey::operator bool() // 0x10818580
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??BDebugDrawKey@@QAE_NXZ");

	return name != nullptr;
}

inline bool operator==(DebugDrawKey const &a, DebugDrawKey const &b) // 0x10818520
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??8@YA_NABUDebugDrawKey@@0@Z");

	return a.name == b.name && a.id == b.id;
}

inline CDebugDraw::CDebugDraw(char const *name) // 0x10817D20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0CDebugDraw@@QAE@PBD@Z");

	m_name = name;
	m_lifetime = 0.0f;
	m_fontId = 0;
	m_textScale = 1.0f;
	m_depthTest = true;
}

inline CDebugDraw::CDebugDraw(std::source_location loc) // 0x10817D90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0CDebugDraw@@QAE@Usource_location@std@@@Z");

	m_name = loc.function_name();
	m_lifetime = 0.0f;
	m_fontId = 0;
	m_textScale = 1.0f;
	m_depthTest = true;
}

inline void CDebugDraw::SetLifetime(float seconds) // 0x1081CC20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetLifetime@CDebugDraw@@QAEXM@Z");

	m_lifetime = seconds;
}

inline void CDebugDraw::SetFont(long id) // 0x1081CB40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetFont@CDebugDraw@@QAEXJ@Z");

	m_fontId = id;
}

inline void CDebugDraw::SetTextScale(float scale) // 0x1081CD00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetTextScale@CDebugDraw@@QAEXM@Z");

	m_textScale = scale;
}

inline void CDebugDraw::SetDepthTest(bool enable) // 0x1081CA70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetDepthTest@CDebugDraw@@QAEX_N@Z");

	m_depthTest = enable;
}

inline void CDebugDraw::Clear(DebugDrawKey key) // 0x10818E30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Clear@CDebugDraw@@QAEXUDebugDrawKey@@@Z");

	CDebugDrawBackend::Clear(m_name, key);
}

inline void CDebugDraw::DrawPoint(DebugDrawKey key, real_point3d const &point, float size, long color) // 0x1081AA60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawPoint@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_point3d@@MJ@Z");

	CDebugDrawBackend::AttributeScope attr;
	SetAttributes(attr, key);
	CDebugDrawBackend::DrawPoint(point, size, color);
}

inline void CDebugDraw::DrawLine(DebugDrawKey key, real_point3d const &p1, real_point3d const &p2, long color) // 0x1081A050
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawLine@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_point3d@@1J@Z");

	CDebugDrawBackend::AttributeScope attr;
	SetAttributes(attr, key);
	CDebugDrawBackend::DrawLine(p1, p2, color);
}

inline void CDebugDraw::DrawVector(DebugDrawKey key, real_point3d const &point, real_vector3d const &vector, long color) // 0x1081BD90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawVector@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_point3d@@ABUreal_vector3d@@J@Z");

	CDebugDrawBackend::AttributeScope attr;
	SetAttributes(attr, key);
	CDebugDrawBackend::DrawVector(point, vector, color);
}

inline void CDebugDraw::DrawTriangle(DebugDrawKey key, real_point3d const &p1, real_point3d const &p2, real_point3d const &p3, long color) // 0x1081BAA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawTriangle@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_point3d@@11J@Z");

	CDebugDrawBackend::AttributeScope attr;
	SetAttributes(attr, key);
	CDebugDrawBackend::DrawTriangle(p1, p2, p3, color);
}

inline void CDebugDraw::DrawBox2dOutline(DebugDrawKey key, real_rectangle2d const &bounds, long color) // 0x108190E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawBox2dOutline@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_rectangle2d@@J@Z");

	CDebugDrawBackend::AttributeScope attr;
	SetAttributes(attr, key);
	CDebugDrawBackend::DrawBox2dOutline(bounds, color);
}

inline void CDebugDraw::DrawBox(DebugDrawKey key, real_rectangle3d const &bounds, long color) // 0x108194A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawBox@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_rectangle3d@@J@Z");

	CDebugDrawBackend::AttributeScope attr;
	SetAttributes(attr, key);
	CDebugDrawBackend::DrawBox(bounds, color);
}

inline void CDebugDraw::DrawBoxOriented(DebugDrawKey key, real_rectangle3d const &bounds, real_matrix4x3 const &matrix, long color) // 0x10819750
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawBoxOriented@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_rectangle3d@@ABUreal_matrix4x3@@J@Z");

	CDebugDrawBackend::AttributeScope attr;
	SetAttributes(attr, key);
	CDebugDrawBackend::DrawBoxOriented(bounds, matrix, color);
}

inline void CDebugDraw::DrawSphereOutline(DebugDrawKey key, real_point3d const &center, float radius, long color) // 0x1081AD20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawSphereOutline@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_point3d@@MJ@Z");

	CDebugDrawBackend::AttributeScope attr;
	SetAttributes(attr, key);
	CDebugDrawBackend::DrawSphereOutline(center, radius, color);
}

inline void __cdecl CDebugDraw::DrawString2d(DebugDrawKey key, real_point2d const &point, long color, char const *format, ...) // 0x1081AFE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawString2d@CDebugDraw@@QAAXUDebugDrawKey@@ABUreal_point2d@@JPBDZZ");

	CDebugDrawBackend::AttributeScope attr;
	SetAttributes(attr, key);

	va_list args;
	va_start(args, format);
	CDebugDrawBackend::DrawString2d(point, color, m_fontId, m_textScale, format, args);
	va_end(args);
}

inline void __cdecl CDebugDraw::DrawString3d(DebugDrawKey key, real_point3d const &point, long color, char const *format, ...) // 0x1081B620
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawString3d@CDebugDraw@@QAAXUDebugDrawKey@@ABUreal_point3d@@JPBDZZ");

	CDebugDrawBackend::AttributeScope attr;
	SetAttributes(attr, key);

	va_list args;
	va_start(args, format);
	CDebugDrawBackend::DrawString3d(point, color, m_fontId, m_textScale, format);
	va_end(args);
}

inline void CDebugDraw::DrawPill(DebugDrawKey key, real_point3d const &base, real_vector3d const &height, float radius, long color) // 0x1081A760
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawPill@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_point3d@@ABUreal_vector3d@@MJ@Z");

	CDebugDrawBackend::AttributeScope attr;
	SetAttributes(attr, key);
	CDebugDrawBackend::DrawPill(base, height, radius, color);
}

inline void CDebugDraw::DrawCylinder(DebugDrawKey key, real_point3d const &base, real_vector3d const &height, float radius, long color) // 0x10819D50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawCylinder@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_point3d@@ABUreal_vector3d@@MJ@Z");

	CDebugDrawBackend::AttributeScope attr;
	SetAttributes(attr, key);
	CDebugDrawBackend::DrawCylinder(base, height, radius, color);
}

inline void CDebugDraw::DrawCone(DebugDrawKey key, real_point3d const &base, real_vector3d const &up, float theta, float height, long color) // 0x10819A20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawCone@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_point3d@@ABUreal_vector3d@@MMJ@Z");

	CDebugDrawBackend::AttributeScope attr;
	SetAttributes(attr, key);
	CDebugDrawBackend::DrawCone(base, up, theta, height, color);
}

inline void CDebugDraw::DrawPhysicsShapeCapsule(DebugDrawKey key, real_point3d const &vertex_a, real_point3d const &vertex_b, float radius, real_matrix4x3 const &matrix, long color) // 0x1081A320
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawPhysicsShapeCapsule@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_point3d@@1MABUreal_matrix4x3@@J@Z");

	CDebugDrawBackend::AttributeScope attr;
	SetAttributes(attr, key);
	CDebugDrawBackend::DrawPhysicsShapeCapsule(vertex_a, vertex_b, radius, matrix, color);
}

inline void CDebugDraw::SetAttributes(CDebugDrawBackend::AttributeScope &attr, DebugDrawKey key) // 0x1081C800
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetAttributes@CDebugDraw@@AAEXAAUAttributeScope@CDebugDrawBackend@@UDebugDrawKey@@@Z");

	attr.SetCacheKey(m_name, key);
	attr.SetLifetime(m_lifetime);
	attr.SetFont(m_fontId);
	attr.SetTextScale(m_textScale);
	attr.SetDepthTest(m_depthTest);
}

/* ---------- private code */

#endif // __DEBUG_DEBUGDRAW_HPP__
