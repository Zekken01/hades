/* ---------- headers */

#include "Debug/DebugDraw.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/draw_string.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/render_globals.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Threading/SimpleMessageQueue.hpp"
#include "Forge/Magnets.hpp"
#include "Server/Connect/ServerConnectStateHandler_AcquireMods.hpp"

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
#include <limits>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <variant>

/* ---------- forward declarations */

class CDebugDraw;
struct CDebugDrawBackend;
struct DebugDrawKey;
struct c_font_cache_mt_safe;
struct c_rasterizer_draw_string;
struct hkpCapsuleShape;
struct real_argb_color;
struct real_matrix4x3;
struct real_point2d;
struct real_point3d;
struct real_rectangle2d;
struct real_rectangle3d;
struct real_vector3d;
struct s_font_header;
struct short_point_2d;
struct short_rectangle2d;
struct t_arg0;
namespace hades_file_local
{
	struct SDrawBox2dMessage;
	struct SDrawBoxMessage;
	struct SDrawBoxOrientedMessage;
	struct SDrawSphereMessage;
	struct SDrawPillMessage;
	struct SDrawConeMessage;
	struct SDrawTriangleMessage;
	struct SDrawLineMessage;
	struct SDrawPointMessage;
	struct SDrawVectorMessage;
	struct SDrawText2dMessage;
	struct SDrawText3dMessage;
	struct SDrawPhysicsShapeCapsuleMessage;
	struct SClearMessage;
	struct SRenderThreadMessage;
	struct SCacehEntry;
}
using namespace hades_file_local;

/* ---------- constants */

namespace hades_file_local
{
	enum EMessageType
	{
		DrawPoint = 0,
		DrawLine,
		DrawVector,
		DrawBox2dOutline,
		DrawBox,
		DrawBoxOriented,
		DrawSphere,
		DrawPill,
		DrawCylinder,
		DrawCone,
		DrawTriangle,
		DrawText2d,
		DrawText3d,
		DrawPhysicsShapeCapsule,
		Clear,
	};
}
using namespace hades_file_local;
/* ---------- definitions */

namespace hades_file_local
{
	#pragma pack(push, 4)
	struct SDrawBox2dMessage
	{
		static EMessageType const MessageType = static_cast<EMessageType>(3);
		real_rectangle2d bounds; // 0x0
		long color; // 0x10
	};
	#pragma pack(pop)
	static_assert(sizeof(SDrawBox2dMessage) == 20, "Invalid SDrawBox2dMessage size");

	#pragma pack(push, 4)
	struct SDrawBoxMessage
	{
		static EMessageType const MessageType = static_cast<EMessageType>(4);
		real_rectangle3d bounds; // 0x0
		long color; // 0x18
	};
	#pragma pack(pop)
	static_assert(sizeof(SDrawBoxMessage) == 28, "Invalid SDrawBoxMessage size");

	struct SDrawBoxOrientedMessage
	{
		static EMessageType const MessageType = static_cast<EMessageType>(5);
		real_rectangle3d bounds; // 0x0
		real_matrix4x3 matrix; // 0x18
		long color; // 0x4C
	};
	static_assert(sizeof(SDrawBoxOrientedMessage) == 80, "Invalid SDrawBoxOrientedMessage size");

	#pragma pack(push, 4)
	struct SDrawSphereMessage
	{
		static EMessageType const MessageType = static_cast<EMessageType>(6);
		real_point3d center; // 0x0
		float radius; // 0xC
		long color; // 0x10
	};
	#pragma pack(pop)
	static_assert(sizeof(SDrawSphereMessage) == 20, "Invalid SDrawSphereMessage size");

	struct SDrawPillMessage
	{
		static EMessageType const MessageType = static_cast<EMessageType>(7);
		real_point3d base; // 0x0
		real_vector3d height; // 0xC
		float radius; // 0x18
		long color; // 0x1C
	};
	static_assert(sizeof(SDrawPillMessage) == 32, "Invalid SDrawPillMessage size");

	#pragma pack(push, 4)
	struct SDrawConeMessage
	{
		static EMessageType const MessageType = static_cast<EMessageType>(9);
		real_point3d base; // 0x0
		real_vector3d up; // 0xC
		float height; // 0x18
		float theta; // 0x1C
		long color; // 0x20
	};
	#pragma pack(pop)
	static_assert(sizeof(SDrawConeMessage) == 36, "Invalid SDrawConeMessage size");

	struct SDrawTriangleMessage
	{
		static EMessageType const MessageType = static_cast<EMessageType>(10);
		real_point3d p1; // 0x0
		real_point3d p2; // 0xC
		real_point3d p3; // 0x18
		long color; // 0x24
	};
	static_assert(sizeof(SDrawTriangleMessage) == 40, "Invalid SDrawTriangleMessage size");

	#pragma pack(push, 4)
	struct SDrawLineMessage
	{
		static EMessageType const MessageType = static_cast<EMessageType>(1);
		real_point3d p1; // 0x0
		real_point3d p2; // 0xC
		long color; // 0x18
	};
	#pragma pack(pop)
	static_assert(sizeof(SDrawLineMessage) == 28, "Invalid SDrawLineMessage size");

	#pragma pack(push, 4)
	struct SDrawPointMessage
	{
		static EMessageType const MessageType = static_cast<EMessageType>(1);
		real_point3d point; // 0x0
		float size; // 0xC
		long color; // 0x10
	};
	#pragma pack(pop)
	static_assert(sizeof(SDrawPointMessage) == 20, "Invalid SDrawPointMessage size");

	#pragma pack(push, 4)
	struct SDrawVectorMessage
	{
		static EMessageType const MessageType = static_cast<EMessageType>(1);
		real_point3d point; // 0x0
		real_vector3d vector; // 0xC
		long color; // 0x18
	};
	#pragma pack(pop)
	static_assert(sizeof(SDrawVectorMessage) == 28, "Invalid SDrawVectorMessage size");

	#pragma pack(push, 4)
	struct SDrawText2dMessage
	{
		static EMessageType const MessageType = static_cast<EMessageType>(11);
		real_point2d point; // 0x0
		long color; // 0x8
		__int32 fontId; // 0xC
		float scale; // 0x10
		char text[256]; // 0x14
	};
	#pragma pack(pop)
	static_assert(sizeof(SDrawText2dMessage) == 276, "Invalid SDrawText2dMessage size");

	struct SDrawText3dMessage
	{
		static EMessageType const MessageType = static_cast<EMessageType>(12);
		real_point3d point; // 0x0
		long color; // 0xC
		__int32 fontId; // 0x10
		float scale; // 0x14
		char text[256]; // 0x18
	};
	static_assert(sizeof(SDrawText3dMessage) == 280, "Invalid SDrawText3dMessage size");

	#pragma pack(push, 4)
	struct SDrawPhysicsShapeCapsuleMessage
	{
		static EMessageType const MessageType = static_cast<EMessageType>(13);
		real_point3d vertex_a; // 0x0
		real_point3d vertex_b; // 0xC
		float radius; // 0x18
		real_matrix4x3 matrix; // 0x1C
		long color; // 0x50
	};
	#pragma pack(pop)
	static_assert(sizeof(SDrawPhysicsShapeCapsuleMessage) == 84, "Invalid SDrawPhysicsShapeCapsuleMessage size");

	#pragma pack(push, 4)
	struct SClearMessage
	{
		static EMessageType const MessageType = static_cast<EMessageType>(14);
		char const *group; // 0x0
		DebugDrawKey cacheKey = nullptr; // 0x4  // hades: an aggregate, as AllocateMessage's `SClearMessage{}` shows
	};
	#pragma pack(pop)
	static_assert(sizeof(SClearMessage) == 12, "Invalid SClearMessage size");

	//@@anonymous-namespace@@
	#pragma pack(push, 4)
	struct SRenderThreadMessage
	{
		EMessageType type : 7; // 0x0
		bool depthTest : 1; // 0x4
		unsigned char __pad0[3]; // 0x5
		float lifetime; // 0x8
		char const *group; // 0xC
		DebugDrawKey cacheKey; // 0x10
		std::variant<SDrawPointMessage,SDrawLineMessage,SDrawVectorMessage,SDrawTriangleMessage,SDrawSphereMessage,SDrawPillMessage,SDrawCylinderMessage,SDrawConeMessage,SDrawBox2dMessage,SDrawBoxMessage,SDrawBoxOrientedMessage,SDrawText2dMessage,SDrawText3dMessage,SDrawPhysicsShapeCapsuleMessage,SClearMessage> payload; // 0x18
		SRenderThreadMessage(); /* compiler_generated() */
	public:
		template<typename t_arg0>
		t_arg0 &GetPayload();
	};
	#pragma pack(pop)
	static_assert(sizeof(SRenderThreadMessage) == 308, "Invalid SRenderThreadMessage size");

	struct SCacehEntry
	{
		bool valid; // 0x0
		unsigned char __pad0[3]; // 0x1
		SRenderThreadMessage command; // 0x4
		char const *group; // 0x138
		DebugDrawKey cacheKey; // 0x13C
		float expireTime; // 0x144
		SCacehEntry(); /* compiler_generated() */
	};
	static_assert(sizeof(SCacehEntry) == 328, "Invalid SCacehEntry size");

	struct SPayloadVisitor
	{
		void operator()(SClearMessage const &);
		void operator()(SDrawPhysicsShapeCapsuleMessage const &);
		void operator()(SDrawText3dMessage const &);
		void operator()(SDrawText2dMessage const &);
		void operator()(SDrawTriangleMessage const &);
		void operator()(SDrawPointMessage const &);
		void operator()(SDrawVectorMessage const &);
		void operator()(SDrawLineMessage const &);
		void operator()(SDrawConeMessage const &);
		void operator()(SDrawCylinderMessage const &);
		void operator()(SDrawPillMessage const &);
		void operator()(SDrawSphereMessage const &);
		void operator()(SDrawBoxOrientedMessage const &);
		void operator()(SDrawBoxMessage const &);
		void operator()(SDrawBox2dMessage const &);
	};
	static_assert(sizeof(SPayloadVisitor) == 1, "Invalid SPayloadVisitor size");
}
using namespace hades_file_local;
typedef std::variant<SDrawPointMessage,SDrawLineMessage,SDrawVectorMessage,SDrawTriangleMessage,SDrawSphereMessage,SDrawPillMessage,SDrawCylinderMessage,SDrawConeMessage,SDrawBox2dMessage,SDrawBoxMessage,SDrawBoxOrientedMessage,SDrawText2dMessage,SDrawText3dMessage,SDrawPhysicsShapeCapsuleMessage,SClearMessage> TMessagePayload;

/* ---------- prototypes */

extern void render_debug_enable_depth_test(bool enable);  // hades: added for 0x1081C570
extern void render_debug_point(real_point3d const &point, float scale, real_argb_color const &color);  // hades: added for the DrawX backends
extern void render_debug_line(real_point3d const &p1, real_point3d const &p2, real_argb_color const &color);
extern void render_debug_vector(real_point3d const &point, real_vector3d const &vector, real_argb_color const &color);
extern void render_debug_triangle(real_point3d const &p1, real_point3d const &p2, real_point3d const &p3, real_argb_color const &color);
extern void render_debug_box_outline(real_rectangle3d const &bounds, real_argb_color const &color);
extern void render_debug_box_oriented(real_rectangle3d const &bounds, real_matrix4x3 const &matrix, real_argb_color const &color);
extern void render_debug_sphere(real_point3d const &center, float radius, real_argb_color const &color);
extern void render_debug_pill(real_point3d const &base, real_vector3d const &height, float radius, real_argb_color const &color);
extern void render_debug_cylinder(real_point3d const &base, real_vector3d const &height, float radius, real_argb_color const &color);
extern void render_debug_cone_outline(real_point3d const &base, real_vector3d const &up, float theta, float height, real_argb_color const &color);
extern void render_debug_string_at_point(real_point3d const &point, char const *text, real_argb_color const &color, long fontId, float scale);
extern void render_debug_physics_shape(hkpShape const *shape, real_matrix4x3 const *matrix, real_argb_color const *color);

extern __int32 AllocateCacheEntry();
extern __int32 FindCacheEntry(char const *group, DebugDrawKey cacheKey);
extern void EvictCacheEntry(char const *group, DebugDrawKey cacheKey);

extern "C" void PreRenderCommand(SRenderThreadMessage &command);
extern "C" void PostRenderCommand(SRenderThreadMessage &command);
extern "C" void HandleRenderThreadMessage(SRenderThreadMessage *message);
void DrawString2dInternal(real_point2d const &point, long color, char const *text, __int32 fontId, float scale);
void DrawString3dInternal(real_point3d const &point, long color, char const *text, __int32 fontId, float scale);

/* ---------- globals */

namespace hades_file_local
{
	// hades: `threadLocalAttributes` was never declared - the generator left two
	// placeholder warnings here. The type and name are recovered from its use:
	// every CDebugDrawBackend::DrawX reads `.lifetime` and every AttributeScope
	// setter writes a field of it.
	//
	// Its ADDRESS cannot be reproduced. The original sits at TLS offset 264 and
	// its dynamic-init guard at 2004, but this unit references no other
	// thread-local - those 264 bytes belong to other translation units, and TLS
	// offsets are assigned when the image is LINKED. Our side is a compiled
	// object, so the variable lands at offset 0 and every access differs by the
	// immediate. No source change fixes it; see the thread-local note in memory.
	thread_local CDebugDrawBackend::Attributes threadLocalAttributes;
}

/* ---------- private variables */

namespace hades_file_local
{
	CSimpleMessageQueue<SRenderThreadMessage,4096> renderThreadQueue; // 0x1138F548  // hades: defined, so its dynamic initializer emits the constructor
	SCacehEntry persistentCache[4096]; // 0x114C7560
}
using namespace hades_file_local;

// hades: one message off the render-thread queue, stamped with this thread's
// current attributes. Static, so the PDB spells it without a namespace.
template<typename t_message>
static SRenderThreadMessage *AllocateMessage()
{
	SRenderThreadMessage *message = renderThreadQueue.TryToAllocate();
	if (!message)
		return nullptr;
	message->type = static_cast<EMessageType>(t_message::MessageType);
	message->payload = t_message{};
	message->lifetime = threadLocalAttributes.lifetime;
	message->group = threadLocalAttributes.group;
	message->cacheKey = threadLocalAttributes.cacheKey;
	message->depthTest = threadLocalAttributes.depthTest;
	return message;
}
/* ---------- public code */

__int32 AllocateCacheEntry() // 0x10818DD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?AllocateCacheEntry@@YAHXZ");

	for (__int32 i = 0; i < sizeof(persistentCache) / sizeof(persistentCache[0]); i++)
	{
		if (!persistentCache[i].valid)
			return i;
	}
	return -1;
}

__int32 FindCacheEntry(char const *group, DebugDrawKey cacheKey) // 0x1081C0D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FindCacheEntry@@YAHPBDUDebugDrawKey@@@Z");

	for (unsigned __int32 i = 0; i < 4096; i++)
	{
		if (persistentCache[i].group == group && (!cacheKey || persistentCache[i].cacheKey == cacheKey))
			return i;
	}

	return -1;
}

void EvictCacheEntry(char const *group, DebugDrawKey cacheKey) // 0x1081C060
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?EvictCacheEntry@@YAXPBDUDebugDrawKey@@@Z");

	int index = FindCacheEntry(group, cacheKey);
	if (index != -1)
		persistentCache[index].valid = false;
}

void CDebugDrawBackend::DrawPoint(real_point3d const &point, float size, long color) // 0x1081AB70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawPoint@CDebugDrawBackend@@SAXABUreal_point3d@@MJ@Z");

	if (!((bool(*)())0xA22390)() || threadLocalAttributes.lifetime != 0.0f)
	{
		SRenderThreadMessage *message = AllocateMessage<SDrawPointMessage>();
		if (message)
		{
			SDrawPointMessage &payload = message->GetPayload<SDrawPointMessage>();
			payload.point = point;
			payload.size = size;
			payload.color = color;
			renderThreadQueue.Add(message);
		}
	}
	else
	{
		real_argb_color realColor;
		((void(*)(long, real_argb_color *))0x5211C0)(color, &realColor);
		render_debug_point(point, size, realColor);
	}
}

void CDebugDrawBackend::DrawLine(real_point3d const &p1, real_point3d const &p2, long color) // 0x1081A160
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawLine@CDebugDrawBackend@@SAXABUreal_point3d@@0J@Z");

	if (!((bool(*)())0xA22390)() || threadLocalAttributes.lifetime != 0.0f)
	{
		SRenderThreadMessage *message = AllocateMessage<SDrawLineMessage>();
		if (message)
		{
			SDrawLineMessage &payload = message->GetPayload<SDrawLineMessage>();
			payload.color = color;
			payload.p1 = p1;
			payload.p2 = p2;
			renderThreadQueue.Add(message);
		}
	}
	else
	{
		real_argb_color realColor;
		((void(*)(long, real_argb_color *))0x5211C0)(color, &realColor);
		render_debug_line(p1, p2, realColor);
	}
}

void CDebugDrawBackend::DrawVector(real_point3d const &point, real_vector3d const &vector, long color) // 0x1081BEA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawVector@CDebugDrawBackend@@SAXABUreal_point3d@@ABUreal_vector3d@@J@Z");

	if (!((bool(*)())0xA22390)() || threadLocalAttributes.lifetime != 0.0f)
	{
		SRenderThreadMessage *message = AllocateMessage<SDrawVectorMessage>();
		if (message)
		{
			SDrawVectorMessage &payload = message->GetPayload<SDrawVectorMessage>();
			payload.point = point;
			payload.vector = vector;
			payload.color = color;
			renderThreadQueue.Add(message);
		}
	}
	else
	{
		real_argb_color realColor;
		((void(*)(long, real_argb_color *))0x5211C0)(color, &realColor);
		render_debug_vector(point, vector, realColor);
	}
}

void CDebugDrawBackend::DrawTriangle(real_point3d const &p1, real_point3d const &p2, real_point3d const &p3, long color) // 0x1081BBB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawTriangle@CDebugDrawBackend@@SAXABUreal_point3d@@00J@Z");

	if (!((bool(*)())0xA22390)() || threadLocalAttributes.lifetime != 0.0f)
	{
		SRenderThreadMessage *message = AllocateMessage<SDrawTriangleMessage>();
		if (message)
		{
			SDrawTriangleMessage &payload = message->GetPayload<SDrawTriangleMessage>();
			payload.p1 = p1;
			payload.p2 = p2;
			payload.p3 = p3;
			payload.color = color;
			renderThreadQueue.Add(message);
		}
	}
	else
	{
		real_argb_color realColor;
		((void(*)(long, real_argb_color *))0x5211C0)(color, &realColor);
		render_debug_triangle(p1, p2, p3, realColor);
	}
}

void CDebugDrawBackend::DrawBox(real_rectangle3d const &bounds, long color) // 0x108195A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawBox@CDebugDrawBackend@@SAXABUreal_rectangle3d@@J@Z");

	if (!((bool(*)())0xA22390)() || threadLocalAttributes.lifetime != 0.0f)
	{
		SRenderThreadMessage *message = AllocateMessage<SDrawBoxMessage>();
		if (message)
		{
			SDrawBoxMessage &payload = message->GetPayload<SDrawBoxMessage>();
			payload.color = color;
			payload.bounds = bounds;
			renderThreadQueue.Add(message);
		}
	}
	else
	{
		real_argb_color realColor;
		((void(*)(long, real_argb_color *))0x5211C0)(color, &realColor);
		render_debug_box_outline(bounds, realColor);
	}
}

void CDebugDrawBackend::DrawBoxOriented(real_rectangle3d const &bounds, real_matrix4x3 const &matrix, long color) // 0x10819860
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawBoxOriented@CDebugDrawBackend@@SAXABUreal_rectangle3d@@ABUreal_matrix4x3@@J@Z");

	if (!((bool(*)())0xA22390)() || threadLocalAttributes.lifetime != 0.0f)
	{
		SRenderThreadMessage *message = AllocateMessage<SDrawBoxOrientedMessage>();
		if (message)
		{
			SDrawBoxOrientedMessage &payload = message->GetPayload<SDrawBoxOrientedMessage>();
			payload.bounds = bounds;
			payload.matrix = matrix;
			payload.color = color;
			renderThreadQueue.Add(message);
		}
	}
	else
	{
		real_argb_color realColor;
		((void(*)(long, real_argb_color *))0x5211C0)(color, &realColor);
		render_debug_box_oriented(bounds, matrix, realColor);
	}
}

void CDebugDrawBackend::DrawBox2dOutline(real_rectangle2d const &bounds, long color) // 0x108191E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawBox2dOutline@CDebugDrawBackend@@SAXABUreal_rectangle2d@@J@Z");

	if (!((bool(*)())0xA22390)() || threadLocalAttributes.lifetime != 0.0f)
	{
		SRenderThreadMessage *message = AllocateMessage<SDrawBox2dMessage>();
		if (message)
		{
			SDrawBox2dMessage &payload = message->GetPayload<SDrawBox2dMessage>();
			payload.color = color;
			payload.bounds = bounds;
			renderThreadQueue.Add(message);
		}
	}
	else
	{
		short_point_2d vertices[5];
		vertices[0] = short_point_2d{ static_cast<short>(bounds.x0), static_cast<short>(bounds.y1) };
		vertices[1] = short_point_2d{ static_cast<short>(bounds.x0), static_cast<short>(bounds.y0) };
		vertices[2] = short_point_2d{ static_cast<short>(bounds.x1), static_cast<short>(bounds.y0) };
		vertices[3] = short_point_2d{ static_cast<short>(bounds.x1), static_cast<short>(bounds.y1) };
		vertices[4] = short_point_2d{ static_cast<short>(bounds.x0), static_cast<short>(bounds.y1) };
		((void(*)(short_point_2d const *, long, unsigned long))0xA45970)(vertices, 5, color);
	}
}

void CDebugDrawBackend::DrawSphereOutline(real_point3d const &center, float radius, long color) // 0x1081AE30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawSphereOutline@CDebugDrawBackend@@SAXABUreal_point3d@@MJ@Z");

	if (!((bool(*)())0xA22390)() || threadLocalAttributes.lifetime != 0.0f)
	{
		SRenderThreadMessage *message = AllocateMessage<SDrawSphereMessage>();
		if (message)
		{
			SDrawSphereMessage &payload = message->GetPayload<SDrawSphereMessage>();
			payload.center = center;
			payload.radius = radius;
			payload.color = color;
			renderThreadQueue.Add(message);
		}
	}
	else
	{
		real_argb_color realColor;
		((void(*)(long, real_argb_color *))0x5211C0)(color, &realColor);
		render_debug_sphere(center, radius, realColor);
	}
}

void CDebugDrawBackend::DrawString2d(real_point2d const &point, long color, long fontId, float scale, char const *format, ...) // 0x1081B200
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawString2d@CDebugDrawBackend@@SAXABUreal_point2d@@JJMPBDZZ");

	va_list va;
	va_start(va, format);
	CDebugDrawBackend::DrawString2d(point, color, fontId, scale, format, va);
	va_end(va);
}

void CDebugDrawBackend::DrawString2d(real_point2d const &point, long color, long fontId, float scale, char const *format, char *va) // 0x1081B110
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawString2d@CDebugDrawBackend@@SAXABUreal_point2d@@JJMPBDPAD@Z");

	char buffer[256];
	vsnprintf(buffer, 256, format, va);
	DrawString2dInternal(point, color, buffer, fontId, scale);
}

void CDebugDrawBackend::DrawString3d(real_point3d const &point, long color, long fontId, float scale, char const *format, ...) // 0x1081B840
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawString3d@CDebugDrawBackend@@SAXABUreal_point3d@@JJMPBDZZ");

	va_list va;
	va_start(va, format);
	CDebugDrawBackend::DrawString3d(point, color, fontId, scale, format, va);
	va_end(va);
}

void CDebugDrawBackend::DrawString3d(real_point3d const &point, long color, long fontId, float scale, char const *format, char *va) // 0x1081B750
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawString3d@CDebugDrawBackend@@SAXABUreal_point3d@@JJMPBDPAD@Z");

	char buffer[256];

	vsnprintf(buffer, 256, format, va);
	DrawString3dInternal(point, color, buffer, fontId, scale);
}

void CDebugDrawBackend::DrawPill(real_point3d const &base, real_vector3d const &height, float radius, long color) // 0x1081A880
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawPill@CDebugDrawBackend@@SAXABUreal_point3d@@ABUreal_vector3d@@MJ@Z");

	if (!((bool(*)())0xA22390)() || threadLocalAttributes.lifetime != 0.0f)
	{
		SRenderThreadMessage *message = AllocateMessage<SDrawPillMessage>();
		if (message)
		{
			SDrawPillMessage &payload = message->GetPayload<SDrawPillMessage>();
			payload.base = base;
			payload.height = height;
			payload.radius = radius;
			payload.color = color;
			renderThreadQueue.Add(message);
		}
	}
	else
	{
		real_argb_color realColor;
		((void(*)(long, real_argb_color *))0x5211C0)(color, &realColor);
		render_debug_pill(base, height, radius, realColor);
	}
}

void CDebugDrawBackend::DrawCylinder(real_point3d const &base, real_vector3d const &height, float radius, long color) // 0x10819E70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawCylinder@CDebugDrawBackend@@SAXABUreal_point3d@@ABUreal_vector3d@@MJ@Z");

	if (!((bool(*)())0xA22390)() || threadLocalAttributes.lifetime != 0.0f)
	{
		SRenderThreadMessage *message = AllocateMessage<SDrawCylinderMessage>();
		if (message)
		{
			SDrawCylinderMessage &payload = message->GetPayload<SDrawCylinderMessage>();
			payload.base = base;
			*(real_vector3d *)payload.height = height;
			payload.radius = radius;
			payload.color = color;
			renderThreadQueue.Add(message);
		}
	}
	else
	{
		real_argb_color realColor;
		((void(*)(long, real_argb_color *))0x5211C0)(color, &realColor);
		render_debug_cylinder(base, height, radius, realColor);
	}
}

void CDebugDrawBackend::DrawCone(real_point3d const &base, real_vector3d const &up, float theta, float height, long color) // 0x10819B50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawCone@CDebugDrawBackend@@SAXABUreal_point3d@@ABUreal_vector3d@@MMJ@Z");

	if (!((bool(*)())0xA22390)() || threadLocalAttributes.lifetime != 0.0f)
	{
		SRenderThreadMessage *message = AllocateMessage<SDrawConeMessage>();
		if (message)
		{
			SDrawConeMessage &payload = message->GetPayload<SDrawConeMessage>();
			payload.base = base;
			payload.up = up;
			payload.theta = theta;
			payload.height = height;
			payload.color = color;
			renderThreadQueue.Add(message);
		}
	}
	else
	{
		real_argb_color realColor;
		((void(*)(long, real_argb_color *))0x5211C0)(color, &realColor);
		render_debug_cone_outline(base, up, theta, height, realColor);
	}
}

void CDebugDrawBackend::DrawPhysicsShapeCapsule(real_point3d const &vertex_a, real_point3d const &vertex_b, float radius, real_matrix4x3 const &matrix, long color) // 0x1081A440
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawPhysicsShapeCapsule@CDebugDrawBackend@@SAXABUreal_point3d@@0MABUreal_matrix4x3@@J@Z");

	if (!((bool(*)())0xA22390)() || threadLocalAttributes.lifetime != 0.0f)
	{
		SRenderThreadMessage *message = AllocateMessage<SDrawPhysicsShapeCapsuleMessage>();
		if (message)
		{
			SDrawPhysicsShapeCapsuleMessage &payload = message->GetPayload<SDrawPhysicsShapeCapsuleMessage>();
			payload.vertex_a = vertex_a;
			payload.vertex_b = vertex_b;
			payload.radius = radius;
			payload.matrix = matrix;
			payload.color = color;
			renderThreadQueue.Add(message);
		}
	}
	else
	{
		real_argb_color realColor;
		((void(*)(long, real_argb_color *))0x5211C0)(color, &realColor);
		alignas(16) hkpCapsuleShape shape;
		memset(&shape, 0, sizeof(shape));
		shape.m_type = 7;
		shape.m_radius = radius;
		shape.m_vertexA = hkVector4{ vertex_a.x, vertex_a.y, vertex_a.z, 0.0f };
		shape.m_vertexB = hkVector4{ vertex_b.x, vertex_b.y, vertex_b.z, 0.0f };
		render_debug_physics_shape(&shape, &matrix, &realColor);
	}
}

#line 887
void CDebugDrawBackend::Render() // 0x1081C610
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Render@CDebugDrawBackend@@SAXXZ");
	// procedure flags: nofpo
		// __int32 i;
	// function call : bool (*const)()

	#line 889 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Debug\\DebugDraw.cpp"
		assert(c_rasterizer::thread_owns_device());
		#line 897 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Debug\\DebugDraw.cpp"
	renderThreadQueue.ConsumeAll(HandleRenderThreadMessage);
	for (__int32 i = 0; i < sizeof(persistentCache) / sizeof(persistentCache[0]); i++)
	{
		if (!persistentCache[i].valid)
			continue;
		PreRenderCommand(persistentCache[i].command);
		std::visit(SPayloadVisitor{}, persistentCache[i].command.payload);
		PostRenderCommand(persistentCache[i].command);
		if (c_render_globals::get_frame_time() >= persistentCache[i].expireTime)
			persistentCache[i].valid = false;
	}
}

void CDebugDrawBackend::Clear(char const *group, DebugDrawKey key) // 0x10818E90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Clear@CDebugDrawBackend@@SAXPBDUDebugDrawKey@@@Z");

	if (!((bool(*)())0xA22390)() || threadLocalAttributes.lifetime != 0.0f)
	{
		SRenderThreadMessage *message = AllocateMessage<SClearMessage>();
		if (message)
		{
			SClearMessage &payload = message->GetPayload<SClearMessage>();
			payload.group = group;
			payload.cacheKey = key;
			renderThreadQueue.Add(message);
		}
	}
	else
	{
		for (unsigned __int32 i = 0; i < std::size(persistentCache); i++)
		{
			if (persistentCache[i].group == group && (!key || persistentCache[i].cacheKey == key))
				persistentCache[i].valid = false;
		}
	}
}

CDebugDrawBackend::AttributeScope::AttributeScope() : m_prevAttributes(threadLocalAttributes) /* hades-mem-init:  */ // 0x10817C00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0AttributeScope@CDebugDrawBackend@@QAE@XZ");
}

_inline CDebugDrawBackend::Attributes::Attributes() : lifetime(0.0f), cacheKey(nullptr, 0xFFFFFFFF), depthTest(true) /* hades-mem-init: : cacheKey(todo_result<DebugDrawKey>()) */ // 0x10817CA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0Attributes@CDebugDrawBackend@@QAE@XZ");
}

CDebugDrawBackend::AttributeScope::~AttributeScope() // 0x108181F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1AttributeScope@CDebugDrawBackend@@QAE@XZ");

	threadLocalAttributes = m_prevAttributes;
}

// mangled_x86(MANGLED_DEFAULT, "??4AttributeScope@CDebugDrawBackend@@QAEAAU01@ABU01@@Z"); no body to assert in
_inline CDebugDrawBackend::AttributeScope &CDebugDrawBackend::AttributeScope::operator=(CDebugDrawBackend::AttributeScope const &__that) = default; // 0x10818430

// mangled_x86(MANGLED_DEFAULT, "??4CDebugDraw@@QAEAAV0@ABV0@@Z"); no body to assert in
// hades: CDebugDraw::operator=(CDebugDraw const &) is defaulted in the class (0x10818470); it stays trivial, so its
// body is one block copy, and taking its address makes this object emit it as the original's does.
extern CDebugDraw &(CDebugDraw::*const hades_keep_cdebugdraw_assign)(CDebugDraw const &) = &CDebugDraw::operator=;

// mangled_x86(MANGLED_DEFAULT, "??4CDebugDrawBackend@@QAEAAU0@$$QAU0@@Z"); no body to assert in
_inline CDebugDrawBackend &CDebugDrawBackend::operator=(CDebugDrawBackend &&__that) = default; // 0x108184C0

// mangled_x86(MANGLED_DEFAULT, "??4CDebugDrawBackend@@QAEAAU0@ABU0@@Z"); no body to assert in
_inline CDebugDrawBackend &CDebugDrawBackend::operator=(CDebugDrawBackend const &__that) = default; // 0x108184F0

void CDebugDrawBackend::AttributeScope::SetLifetime(float lifetime) // 0x1081CB70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetLifetime@AttributeScope@CDebugDrawBackend@@QAEXM@Z");

	threadLocalAttributes.lifetime = lifetime;
}

void CDebugDrawBackend::AttributeScope::SetCacheKey(char const *group, DebugDrawKey key) // 0x1081C8C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetCacheKey@AttributeScope@CDebugDrawBackend@@QAEXPBDUDebugDrawKey@@@Z");

	threadLocalAttributes.group = group;
	threadLocalAttributes.cacheKey = key;
}

void CDebugDrawBackend::AttributeScope::SetFont(__int32 fontId) // 0x1081CAA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetFont@AttributeScope@CDebugDrawBackend@@QAEXH@Z");

	threadLocalAttributes.fontId = fontId;
}

void CDebugDrawBackend::AttributeScope::SetTextScale(float scale) // 0x1081CC50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetTextScale@AttributeScope@CDebugDrawBackend@@QAEXM@Z");

	threadLocalAttributes.textScale = scale;
}

void CDebugDrawBackend::AttributeScope::SetDepthTest(bool enable) // 0x1081C9D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetDepthTest@AttributeScope@CDebugDrawBackend@@QAEX_N@Z");

	threadLocalAttributes.depthTest = enable;
}

float CDebugDraw::GetLineHeight(__int32 fontId) const // 0x1081C220
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetLineHeight@CDebugDraw@@QBEMH@Z");

	void *(__cdecl *const GetFontHeader)(__int32) = (void *(__cdecl *const)(__int32))0x5092f0;
	__int32 (__cdecl *const GetFontHeaderLineHeight)(void *) = (__int32(__cdecl *const)(void *))0x65b5e0;

	void *header = GetFontHeader(fontId);
	float lineHeight = (float)GetFontHeaderLineHeight(header);
	return lineHeight;
}

/* ---------- private code */

template<typename t_arg0>
_inline t_arg0 &SRenderThreadMessage::GetPayload()
{
	return std::get<t_arg0>(payload);
}

_inline void SPayloadVisitor::operator()(SDrawBox2dMessage const &payload) // 0x10818640
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??RSPayloadVisitor@hades_file_local@@QAEXABUSDrawBox2dMessage@1@@Z");

	CDebugDrawBackend::DrawBox2dOutline(*(real_rectangle2d const *)&payload, *(long const *)((unsigned char const *)&payload + 0x10));
}

_inline void SPayloadVisitor::operator()(SDrawBoxMessage const &payload) // 0x108186A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??RSPayloadVisitor@hades_file_local@@QAEXABUSDrawBoxMessage@1@@Z");

	CDebugDrawBackend::DrawBox(*(real_rectangle3d const *)&payload, *(long const *)((unsigned char const *)&payload + 0x18));
}

_inline void SPayloadVisitor::operator()(SDrawBoxOrientedMessage const &payload) // 0x10818700
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??RSPayloadVisitor@hades_file_local@@QAEXABUSDrawBoxOrientedMessage@1@@Z");

	CDebugDrawBackend::DrawBoxOriented(*(real_rectangle3d const *)&payload, *(real_matrix4x3 const *)((unsigned char const *)&payload + 0x18), *(long const *)((unsigned char const *)&payload + 0x4c));
}

_inline void SPayloadVisitor::operator()(SDrawSphereMessage const &payload) // 0x10818A60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??RSPayloadVisitor@hades_file_local@@QAEXABUSDrawSphereMessage@1@@Z");

	CDebugDrawBackend::DrawSphereOutline(*(real_point3d const *)&payload, *(float const *)((unsigned char const *)&payload + 0xc), *(long const *)((unsigned char const *)&payload + 0x10));
}

_inline void SPayloadVisitor::operator()(SDrawPillMessage const &payload) // 0x10818970
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??RSPayloadVisitor@hades_file_local@@QAEXABUSDrawPillMessage@1@@Z");

	CDebugDrawBackend::DrawPill(*(real_point3d const *)&payload, *(real_vector3d const *)((unsigned char const *)&payload + 0xc), *(float const *)((unsigned char const *)&payload + 0x18), *(long const *)((unsigned char const *)&payload + 0x1c));
}

_inline void SPayloadVisitor::operator()(SDrawCylinderMessage const &payload) // 0x10818800
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??RSPayloadVisitor@hades_file_local@@QAEXABUSDrawCylinderMessage@@@Z");

	CDebugDrawBackend::DrawCylinder(*(real_point3d const *)&payload, *(real_vector3d const *)((unsigned char const *)&payload + 0xc), *(float const *)((unsigned char const *)&payload + 0x18), *(long const *)((unsigned char const *)&payload + 0x1c));
}

_inline void SPayloadVisitor::operator()(SDrawConeMessage const &payload) // 0x10818770
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??RSPayloadVisitor@hades_file_local@@QAEXABUSDrawConeMessage@1@@Z");

	CDebugDrawBackend::DrawCone(*(real_point3d const *)&payload, *(real_vector3d const *)((unsigned char const *)&payload + 0xc), *(float const *)((unsigned char const *)&payload + 0x1c), *(float const *)((unsigned char const *)&payload + 0x18), *(long const *)((unsigned char const *)&payload + 0x20));
}

_inline void SPayloadVisitor::operator()(SDrawLineMessage const &payload) // 0x10818880
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??RSPayloadVisitor@hades_file_local@@QAEXABUSDrawLineMessage@1@@Z");

	CDebugDrawBackend::DrawLine(*(real_point3d const *)&payload, *(real_point3d const *)((unsigned char const *)&payload + 0xc), *(long const *)((unsigned char const *)&payload + 0x18));
}

_inline void SPayloadVisitor::operator()(SDrawVectorMessage const &payload) // 0x10818C40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??RSPayloadVisitor@hades_file_local@@QAEXABUSDrawVectorMessage@1@@Z");

	CDebugDrawBackend::DrawVector(*(real_point3d const *)&payload, *(real_vector3d const *)((unsigned char const *)&payload + 0xc), *(long const *)((unsigned char const *)&payload + 0x18));
}

_inline void SPayloadVisitor::operator()(SDrawPointMessage const &payload) // 0x108189F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??RSPayloadVisitor@hades_file_local@@QAEXABUSDrawPointMessage@1@@Z");

	CDebugDrawBackend::DrawPoint(*(real_point3d const *)&payload, *(float const *)((unsigned char const *)&payload + 0xc), *(long const *)((unsigned char const *)&payload + 0x10));
}

_inline void SPayloadVisitor::operator()(SDrawTriangleMessage const &payload) // 0x10818BD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??RSPayloadVisitor@hades_file_local@@QAEXABUSDrawTriangleMessage@1@@Z");

	CDebugDrawBackend::DrawTriangle(*(real_point3d const *)&payload, *(real_point3d const *)((unsigned char const *)&payload + 0xc), *(real_point3d const *)((unsigned char const *)&payload + 0x18), *(long const *)((unsigned char const *)&payload + 0x24));
}

_inline void SPayloadVisitor::operator()(SDrawText2dMessage const &payload) // 0x10818AD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??RSPayloadVisitor@hades_file_local@@QAEXABUSDrawText2dMessage@1@@Z");

	DrawString2dInternal(*(real_point2d const *)&payload, *(long const *)((unsigned char const *)&payload + 0x8), (char const *)((unsigned char const *)&payload + 0x14), *(__int32 const *)((unsigned char const *)&payload + 0xc), *(float const *)((unsigned char const *)&payload + 0x10));
}

_inline void SPayloadVisitor::operator()(SDrawText3dMessage const &payload) // 0x10818B50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??RSPayloadVisitor@hades_file_local@@QAEXABUSDrawText3dMessage@1@@Z");

	DrawString3dInternal(*(real_point3d const *)&payload, *(long const *)((unsigned char const *)&payload + 0xc), (char const *)((unsigned char const *)&payload + 0x18), *(__int32 const *)((unsigned char const *)&payload + 0x10), *(float const *)((unsigned char const *)&payload + 0x14));
}

_inline void SPayloadVisitor::operator()(SDrawPhysicsShapeCapsuleMessage const &payload) // 0x108188F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??RSPayloadVisitor@hades_file_local@@QAEXABUSDrawPhysicsShapeCapsuleMessage@1@@Z");

	CDebugDrawBackend::DrawPhysicsShapeCapsule(*(real_point3d const *)&payload, *(real_point3d const *)((unsigned char const *)&payload + 0xc), *(float const *)((unsigned char const *)&payload + 0x18), *(real_matrix4x3 const *)((unsigned char const *)&payload + 0x1c), *(long const *)((unsigned char const *)&payload + 0x50));
}

_inline void SPayloadVisitor::operator()(SClearMessage const &payload) // 0x108185D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??RSPayloadVisitor@hades_file_local@@QAEXABUSClearMessage@1@@Z");

	CDebugDrawBackend::Clear(payload.group, payload.cacheKey);
}

extern "C" void PreRenderCommand(SRenderThreadMessage &command) // 0x1081C5C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_PreRenderCommand");

	render_debug_enable_depth_test(command.depthTest);
}

extern "C" void PostRenderCommand(SRenderThreadMessage &command) // 0x1081C570
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_PostRenderCommand");

	render_debug_enable_depth_test(true);
}

extern "C" void HandleRenderThreadMessage(SRenderThreadMessage *message) // 0x1081C2D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_HandleRenderThreadMessage");

	if (message->lifetime != 0.0f)
	{
		__int32 cacheEntryIndex = -1;
		if (message->cacheKey)
			cacheEntryIndex = FindCacheEntry(message->group, message->cacheKey);
		if (cacheEntryIndex == -1)
			cacheEntryIndex = AllocateCacheEntry();
		if (cacheEntryIndex == -1)
			return;
		persistentCache[cacheEntryIndex].valid = true;
		persistentCache[cacheEntryIndex].expireTime = c_render_globals::get_frame_time() + message->lifetime;
		persistentCache[cacheEntryIndex].cacheKey = message->cacheKey;
		persistentCache[cacheEntryIndex].group = message->group;
		memcpy(&persistentCache[cacheEntryIndex].command, message, sizeof(SRenderThreadMessage));
		return;
	}
	PreRenderCommand(*message);
	std::visit(SPayloadVisitor{}, message->payload);
	PostRenderCommand(*message);
}

void DrawString2dInternal(real_point2d const &point, long color, char const *text, __int32 fontId, float scale) // 0x1081B280
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawString2dInternal@@YAXABUreal_point2d@@JPBDHM@Z");

	if (!((bool(*)())0xA22390)() || threadLocalAttributes.lifetime != 0.0f)
	{
		SRenderThreadMessage *message = AllocateMessage<SDrawText2dMessage>();
		if (message)
		{
			SDrawText2dMessage &payload = message->GetPayload<SDrawText2dMessage>();
			payload.color = color;
			payload.point = point;
			payload.fontId = fontId;
			payload.scale = scale;
			strncpy_s(payload.text, text, _TRUNCATE);
			renderThreadQueue.Add(message);
		}
	}
	else
	{
		c_font_cache_mt_safe m_fontCache;
		c_rasterizer_draw_string m_drawString;
		short_rectangle2d bounds;
		((void(*)(long, long, long, short_rectangle2d *))0xA9FAA0)(0, 0, 0, &bounds);
		bounds.x0 = static_cast<short>(point.x);
		bounds.y0 = static_cast<short>(point.y);
		real_argb_color colorf;
		((void(*)(long, real_argb_color *))0x5211C0)(color, &colorf);
		m_drawString.set_scale(scale);
		m_drawString.set_font(fontId);
		m_drawString.set_color(colorf);
		m_drawString.set_shadow_color(real_argb_color{ 1.0f, 0.0f, 0.0f, 0.0f });
		m_drawString.set_drop_shadow_style(2);
		m_drawString.set_bounds(bounds);
		m_drawString.draw(&m_fontCache, text);
	}
}

void DrawString3dInternal(real_point3d const &point, long color, char const *text, __int32 fontId, float scale) // 0x1081B8C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawString3dInternal@@YAXABUreal_point3d@@JPBDHM@Z");

	if (!((bool(*)())0xA22390)() || threadLocalAttributes.lifetime != 0.0f)
	{
		SRenderThreadMessage *message = AllocateMessage<SDrawText3dMessage>();
		if (message)
		{
			SDrawText3dMessage &payload = message->GetPayload<SDrawText3dMessage>();
			payload.color = color;
			payload.point = point;
			payload.fontId = fontId;
			payload.scale = scale;
			strncpy_s(payload.text, text, _TRUNCATE);
			renderThreadQueue.Add(message);
		}
	}
	else
	{
		real_argb_color colorf;
		((void(*)(long, real_argb_color *))0x5211C0)(color, &colorf);
		render_debug_string_at_point(point, text, colorf, fontId, scale);
	}
}

_inline SCacehEntry::SCacehEntry() : cacheKey(nullptr, 0xFFFFFFFF) /* hades-mem-init: : cacheKey(todo_result<DebugDrawKey>()) */ // 0x10817E60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SCacehEntry@hades_file_local@@QAE@XZ");
}

_inline SRenderThreadMessage::SRenderThreadMessage() : lifetime(0.0f), cacheKey(nullptr, 0xFFFFFFFF) /* hades-mem-init: : cacheKey(todo_result<DebugDrawKey>()) */ // 0x10817F40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SRenderThreadMessage@hades_file_local@@QAE@XZ");
}

/* ---------- explicit instantiations */
template _SINGLE_LIST_ENTRY * CSimpleMessageQueue<SRenderThreadMessage,4096>::Reversed(_SINGLE_LIST_ENTRY *);
template CSimpleMessageQueue<SRenderThreadMessage,4096>::CSimpleMessageQueue();  // hades: emits SQueueEntry's implicit ctor, as the original's does

/* ---------- explicit instantiations (hades: the original object carries these) */
template SDrawPointMessage &SRenderThreadMessage::GetPayload<SDrawPointMessage>();
template SDrawLineMessage &SRenderThreadMessage::GetPayload<SDrawLineMessage>();
template SDrawVectorMessage &SRenderThreadMessage::GetPayload<SDrawVectorMessage>();
template SDrawTriangleMessage &SRenderThreadMessage::GetPayload<SDrawTriangleMessage>();
template SDrawSphereMessage &SRenderThreadMessage::GetPayload<SDrawSphereMessage>();
template SDrawPillMessage &SRenderThreadMessage::GetPayload<SDrawPillMessage>();
template SDrawCylinderMessage &SRenderThreadMessage::GetPayload<SDrawCylinderMessage>();
template SDrawConeMessage &SRenderThreadMessage::GetPayload<SDrawConeMessage>();
template SDrawBox2dMessage &SRenderThreadMessage::GetPayload<SDrawBox2dMessage>();
template SDrawBoxMessage &SRenderThreadMessage::GetPayload<SDrawBoxMessage>();
template SDrawBoxOrientedMessage &SRenderThreadMessage::GetPayload<SDrawBoxOrientedMessage>();
template SDrawText2dMessage &SRenderThreadMessage::GetPayload<SDrawText2dMessage>();
template SDrawText3dMessage &SRenderThreadMessage::GetPayload<SDrawText3dMessage>();
template SDrawPhysicsShapeCapsuleMessage &SRenderThreadMessage::GetPayload<SDrawPhysicsShapeCapsuleMessage>();
template SClearMessage &SRenderThreadMessage::GetPayload<SClearMessage>();

/* ---------- data definitions */
long const CDebugDraw::COLOR_WHITE = static_cast<long>(0xFFFFFFFF);
long const CDebugDraw::COLOR_BLACK = static_cast<long>(0xFF000000);
long const CDebugDraw::COLOR_RED = static_cast<long>(0xFFFF0000);
long const CDebugDraw::COLOR_BLUE = static_cast<long>(0xFF0000FF);
long const CDebugDraw::COLOR_GREEN = static_cast<long>(0xFF00FF00);
long const CDebugDraw::COLOR_YELLOW = static_cast<long>(0xFFFFFF00);
long const CDebugDraw::COLOR_PINK = static_cast<long>(0xFFFF00FF);
long const CDebugDraw::COLOR_CYAN = static_cast<long>(0xFF00FFFF);
long const CDebugDraw::COLOR_ORANGE = static_cast<long>(0xFFFF7F00);
