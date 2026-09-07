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
	_inline DebugDrawKey(char const *name_, unsigned __int32 id_);
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
		unsigned char __pad0[3]; // 0x19
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

class CDebugDraw
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
	_inline CDebugDraw(std::source_location loc);
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
	void __dflt_ctor_closure(); /* compiler_generated() */
	public:
	CDebugDraw & operator=(CDebugDraw const &__that);
unsigned char __pad0[3]; // 0x11
};
static_assert(sizeof(CDebugDraw) == 20, "Invalid CDebugDraw size");

/* ---------- prototypes */

extern __int32 AllocateCacheEntry();
extern __int32 FindCacheEntry(char const *group, DebugDrawKey cacheKey);
extern void EvictCacheEntry(char const *group, DebugDrawKey cacheKey);

extern _inline bool operator==(DebugDrawKey const &a, DebugDrawKey const &b);

/* ---------- globals */

/* ---------- public code */

extern DebugDrawKey* _sub_10817E20(DebugDrawKey *const, char const *, unsigned __int32);
_inline DebugDrawKey::DebugDrawKey(char const *name_, unsigned __int32 id_) // 0x10817E20
{
	mangled_x86(MANGLED_TODO, "??0DebugDrawKey@@QAE@PBDI@Z");
	// unsigned __int32 id_;
	todo("implement");
	_sub_10817E20(this, name_, id_);
}

_extern bool _sub_10818580(DebugDrawKey *const);
_inline DebugDrawKey::operator bool() // 0x10818580
{
	mangled_x86(MANGLED_TODO, "??BDebugDrawKey@@QAE_NXZ");
	// DebugDrawKey *const this;
	todo("implement");
	bool __result = _sub_10818580(this);
	return __result;
}

_extern bool _sub_10818520(DebugDrawKey const &, DebugDrawKey const &);
_inline bool operator==(DebugDrawKey const &a, DebugDrawKey const &b) // 0x10818520
{
	mangled_x86(MANGLED_TODO, "??8@YA_NABUDebugDrawKey@@0@Z");
	// DebugDrawKey const &b;
	todo("implement");
	bool __result = _sub_10818520(a, b);
	return __result;
}

extern CDebugDraw* _sub_10817D20(CDebugDraw *const, char const *);
_inline CDebugDraw::CDebugDraw(char const *name) // 0x10817D20
{
	mangled_x86(MANGLED_TODO, "??0CDebugDraw@@QAE@PBD@Z");
	// char const *name;
	todo("implement");
	_sub_10817D20(this, name);
}

extern CDebugDraw* _sub_10817D90(CDebugDraw *const, std::source_location);
_inline CDebugDraw::CDebugDraw(std::source_location loc) // 0x10817D90
{
	mangled_x86(MANGLED_TODO, "??0CDebugDraw@@QAE@Usource_location@std@@@Z");
	// std::source_location loc;
	todo("implement");
	_sub_10817D90(this, loc);
}

_extern void _sub_1081CC20(CDebugDraw *const, float);
_inline void CDebugDraw::SetLifetime(float seconds) // 0x1081CC20
{
	mangled_x86(MANGLED_TODO, "?SetLifetime@CDebugDraw@@QAEXM@Z");
	// float seconds;
	todo("implement");
	_sub_1081CC20(this, seconds);
}

_extern void _sub_1081CB40(CDebugDraw *const, long);
_inline void CDebugDraw::SetFont(long id) // 0x1081CB40
{
	mangled_x86(MANGLED_TODO, "?SetFont@CDebugDraw@@QAEXJ@Z");
	// long id;
	todo("implement");
	_sub_1081CB40(this, id);
}

_extern void _sub_1081CD00(CDebugDraw *const, float);
_inline void CDebugDraw::SetTextScale(float scale) // 0x1081CD00
{
	mangled_x86(MANGLED_TODO, "?SetTextScale@CDebugDraw@@QAEXM@Z");
	// float scale;
	todo("implement");
	_sub_1081CD00(this, scale);
}

_extern void _sub_1081CA70(CDebugDraw *const, bool);
_inline void CDebugDraw::SetDepthTest(bool enable) // 0x1081CA70
{
	mangled_x86(MANGLED_TODO, "?SetDepthTest@CDebugDraw@@QAEX_N@Z");
	// bool enable;
	todo("implement");
	_sub_1081CA70(this, enable);
}

_extern void _sub_10818E30(CDebugDraw *const, DebugDrawKey);
_inline void CDebugDraw::Clear(DebugDrawKey key) // 0x10818E30
{
	mangled_x86(MANGLED_TODO, "?Clear@CDebugDraw@@QAEXUDebugDrawKey@@@Z");
	// DebugDrawKey key;
	todo("implement");
	_sub_10818E30(this, key);
}

_extern void _sub_1081AA60(CDebugDraw *const, DebugDrawKey, real_point3d const &, float, long);
_inline void CDebugDraw::DrawPoint(DebugDrawKey key, real_point3d const &point, float size, long color) // 0x1081AA60
{
	mangled_x86(MANGLED_TODO, "?DrawPoint@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_point3d@@MJ@Z");
	// DebugDrawKey key;
	// real_point3d const &point;
	// float size;
	// long color;
	// CDebugDrawBackend::AttributeScope attr;
	todo("implement");
	_sub_1081AA60(this, key, point, size, color);
}

_extern void _sub_1081A050(CDebugDraw *const, DebugDrawKey, real_point3d const &, real_point3d const &, long);
_inline void CDebugDraw::DrawLine(DebugDrawKey key, real_point3d const &p1, real_point3d const &p2, long color) // 0x1081A050
{
	mangled_x86(MANGLED_TODO, "?DrawLine@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_point3d@@1J@Z");
	// DebugDrawKey key;
	// real_point3d const &p1;
	// real_point3d const &p2;
	// long color;
	// CDebugDrawBackend::AttributeScope attr;
	todo("implement");
	_sub_1081A050(this, key, p1, p2, color);
}

_extern void _sub_1081BD90(CDebugDraw *const, DebugDrawKey, real_point3d const &, real_vector3d const &, long);
_inline void CDebugDraw::DrawVector(DebugDrawKey key, real_point3d const &point, real_vector3d const &vector, long color) // 0x1081BD90
{
	mangled_x86(MANGLED_TODO, "?DrawVector@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_point3d@@ABUreal_vector3d@@J@Z");
	// DebugDrawKey key;
	// real_point3d const &point;
	// real_vector3d const &vector;
	// long color;
	// CDebugDrawBackend::AttributeScope attr;
	todo("implement");
	_sub_1081BD90(this, key, point, vector, color);
}

_extern void _sub_1081BAA0(CDebugDraw *const, DebugDrawKey, real_point3d const &, real_point3d const &, real_point3d const &, long);
_inline void CDebugDraw::DrawTriangle(DebugDrawKey key, real_point3d const &p1, real_point3d const &p2, real_point3d const &p3, long color) // 0x1081BAA0
{
	mangled_x86(MANGLED_TODO, "?DrawTriangle@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_point3d@@11J@Z");
	// real_point3d const &p1;
	// real_point3d const &p2;
	// real_point3d const &p3;
	// long color;
	// CDebugDrawBackend::AttributeScope attr;
	todo("implement");
	_sub_1081BAA0(this, key, p1, p2, p3, color);
}

_extern void _sub_108190E0(CDebugDraw *const, DebugDrawKey, real_rectangle2d const &, long);
_inline void CDebugDraw::DrawBox2dOutline(DebugDrawKey key, real_rectangle2d const &bounds, long color) // 0x108190E0
{
	mangled_x86(MANGLED_TODO, "?DrawBox2dOutline@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_rectangle2d@@J@Z");
	// CDebugDraw *const this;
	// DebugDrawKey key;
	// real_rectangle2d const &bounds;
	// long color;
	// CDebugDrawBackend::AttributeScope attr;
	todo("implement");
	_sub_108190E0(this, key, bounds, color);
}

_extern void _sub_108194A0(CDebugDraw *const, DebugDrawKey, real_rectangle3d const &, long);
_inline void CDebugDraw::DrawBox(DebugDrawKey key, real_rectangle3d const &bounds, long color) // 0x108194A0
{
	mangled_x86(MANGLED_TODO, "?DrawBox@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_rectangle3d@@J@Z");
	// CDebugDraw *const this;
	// DebugDrawKey key;
	// real_rectangle3d const &bounds;
	// long color;
	// CDebugDrawBackend::AttributeScope attr;
	todo("implement");
	_sub_108194A0(this, key, bounds, color);
}

_extern void _sub_10819750(CDebugDraw *const, DebugDrawKey, real_rectangle3d const &, real_matrix4x3 const &, long);
_inline void CDebugDraw::DrawBoxOriented(DebugDrawKey key, real_rectangle3d const &bounds, real_matrix4x3 const &matrix, long color) // 0x10819750
{
	mangled_x86(MANGLED_TODO, "?DrawBoxOriented@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_rectangle3d@@ABUreal_matrix4x3@@J@Z");
	// DebugDrawKey key;
	// real_rectangle3d const &bounds;
	// real_matrix4x3 const &matrix;
	// long color;
	// CDebugDrawBackend::AttributeScope attr;
	todo("implement");
	_sub_10819750(this, key, bounds, matrix, color);
}

_extern void _sub_1081AD20(CDebugDraw *const, DebugDrawKey, real_point3d const &, float, long);
_inline void CDebugDraw::DrawSphereOutline(DebugDrawKey key, real_point3d const &center, float radius, long color) // 0x1081AD20
{
	mangled_x86(MANGLED_TODO, "?DrawSphereOutline@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_point3d@@MJ@Z");
	// DebugDrawKey key;
	// real_point3d const &center;
	// float radius;
	// long color;
	// CDebugDrawBackend::AttributeScope attr;
	todo("implement");
	_sub_1081AD20(this, key, center, radius, color);
}

_extern void _sub_1081AFE0(CDebugDraw *const, DebugDrawKey, real_point2d const &, long, char const *, ...);
_inline void __cdecl CDebugDraw::DrawString2d(DebugDrawKey key, real_point2d const &point, long color, char const *format, ...) // 0x1081AFE0
{
	mangled_x86(MANGLED_TODO, "?DrawString2d@CDebugDraw@@QAAXUDebugDrawKey@@ABUreal_point2d@@JPBDZZ");
	// real_point2d const &point;
	// long color;
	// char const *format;
	// char *va;
	// CDebugDrawBackend::AttributeScope attr;
	todo("implement");
	_sub_1081AFE0(this, key, point, color, format);
}

_extern void _sub_1081B620(CDebugDraw *const, DebugDrawKey, real_point3d const &, long, char const *, ...);
_inline void __cdecl CDebugDraw::DrawString3d(DebugDrawKey key, real_point3d const &point, long color, char const *format, ...) // 0x1081B620
{
	mangled_x86(MANGLED_TODO, "?DrawString3d@CDebugDraw@@QAAXUDebugDrawKey@@ABUreal_point3d@@JPBDZZ");
	// real_point3d const &point;
	// long color;
	// char const *format;
	// char *va;
	// CDebugDrawBackend::AttributeScope attr;
	todo("implement");
	_sub_1081B620(this, key, point, color, format);
}

_extern void _sub_1081A760(CDebugDraw *const, DebugDrawKey, real_point3d const &, real_vector3d const &, float, long);
_inline void CDebugDraw::DrawPill(DebugDrawKey key, real_point3d const &base, real_vector3d const &height, float radius, long color) // 0x1081A760
{
	mangled_x86(MANGLED_TODO, "?DrawPill@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_point3d@@ABUreal_vector3d@@MJ@Z");
	// real_point3d const &base;
	// real_vector3d const &height;
	// float radius;
	// long color;
	// CDebugDrawBackend::AttributeScope attr;
	todo("implement");
	_sub_1081A760(this, key, base, height, radius, color);
}

_extern void _sub_10819D50(CDebugDraw *const, DebugDrawKey, real_point3d const &, real_vector3d const &, float, long);
_inline void CDebugDraw::DrawCylinder(DebugDrawKey key, real_point3d const &base, real_vector3d const &height, float radius, long color) // 0x10819D50
{
	mangled_x86(MANGLED_TODO, "?DrawCylinder@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_point3d@@ABUreal_vector3d@@MJ@Z");
	// real_point3d const &base;
	// real_vector3d const &height;
	// float radius;
	// long color;
	// CDebugDrawBackend::AttributeScope attr;
	todo("implement");
	_sub_10819D50(this, key, base, height, radius, color);
}

_extern void _sub_10819A20(CDebugDraw *const, DebugDrawKey, real_point3d const &, real_vector3d const &, float, float, long);
_inline void CDebugDraw::DrawCone(DebugDrawKey key, real_point3d const &base, real_vector3d const &up, float theta, float height, long color) // 0x10819A20
{
	mangled_x86(MANGLED_TODO, "?DrawCone@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_point3d@@ABUreal_vector3d@@MMJ@Z");
	// real_vector3d const &up;
	// float theta;
	// float height;
	// long color;
	// CDebugDrawBackend::AttributeScope attr;
	todo("implement");
	_sub_10819A20(this, key, base, up, theta, height, color);
}

_extern void _sub_1081A320(CDebugDraw *const, DebugDrawKey, real_point3d const &, real_point3d const &, float, real_matrix4x3 const &, long);
_inline void CDebugDraw::DrawPhysicsShapeCapsule(DebugDrawKey key, real_point3d const &vertex_a, real_point3d const &vertex_b, float radius, real_matrix4x3 const &matrix, long color) // 0x1081A320
{
	mangled_x86(MANGLED_TODO, "?DrawPhysicsShapeCapsule@CDebugDraw@@QAEXUDebugDrawKey@@ABUreal_point3d@@1MABUreal_matrix4x3@@J@Z");
	// real_point3d const &vertex_b;
	// float radius;
	// real_matrix4x3 const &matrix;
	// long color;
	// CDebugDrawBackend::AttributeScope attr;
	todo("implement");
	_sub_1081A320(this, key, vertex_a, vertex_b, radius, matrix, color);
}

_extern void _sub_1081C800(CDebugDraw *const, CDebugDrawBackend::AttributeScope &, DebugDrawKey);
_inline void CDebugDraw::SetAttributes(CDebugDrawBackend::AttributeScope &attr, DebugDrawKey key) // 0x1081C800
{
	mangled_x86(MANGLED_TODO, "?SetAttributes@CDebugDraw@@AAEXAAUAttributeScope@CDebugDrawBackend@@UDebugDrawKey@@@Z");
	// DebugDrawKey key;
	todo("implement");
	_sub_1081C800(this, attr, key);
}

/* ---------- private code */

#endif // __DEBUG_DEBUGDRAW_HPP__
