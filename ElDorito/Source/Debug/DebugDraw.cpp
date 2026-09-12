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
		static EMessageType const MessageType;
		real_rectangle2d bounds; // 0x0
		long color; // 0x10
	};
	#pragma pack(pop)
	static_assert(sizeof(SDrawBox2dMessage) == 20, "Invalid SDrawBox2dMessage size");

	#pragma pack(push, 4)
	struct SDrawBoxMessage
	{
		static EMessageType const MessageType;
		real_rectangle3d bounds; // 0x0
		long color; // 0x18
	};
	#pragma pack(pop)
	static_assert(sizeof(SDrawBoxMessage) == 28, "Invalid SDrawBoxMessage size");

	struct SDrawBoxOrientedMessage
	{
		static EMessageType const MessageType;
		real_rectangle3d bounds; // 0x0
		real_matrix4x3 matrix; // 0x18
		long color; // 0x4C
	};
	static_assert(sizeof(SDrawBoxOrientedMessage) == 80, "Invalid SDrawBoxOrientedMessage size");

	#pragma pack(push, 4)
	struct SDrawSphereMessage
	{
		static EMessageType const MessageType;
		real_point3d center; // 0x0
		float radius; // 0xC
		long color; // 0x10
	};
	#pragma pack(pop)
	static_assert(sizeof(SDrawSphereMessage) == 20, "Invalid SDrawSphereMessage size");

	struct SDrawPillMessage
	{
		static EMessageType const MessageType;
		real_point3d base; // 0x0
		real_vector3d height; // 0xC
		float radius; // 0x18
		long color; // 0x1C
	};
	static_assert(sizeof(SDrawPillMessage) == 32, "Invalid SDrawPillMessage size");

	#pragma pack(push, 4)
	struct SDrawConeMessage
	{
		static EMessageType const MessageType;
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
		static EMessageType const MessageType;
		real_point3d p1; // 0x0
		real_point3d p2; // 0xC
		real_point3d p3; // 0x18
		long color; // 0x24
	};
	static_assert(sizeof(SDrawTriangleMessage) == 40, "Invalid SDrawTriangleMessage size");

	#pragma pack(push, 4)
	struct SDrawLineMessage
	{
		static EMessageType const MessageType;
		real_point3d p1; // 0x0
		real_point3d p2; // 0xC
		long color; // 0x18
	};
	#pragma pack(pop)
	static_assert(sizeof(SDrawLineMessage) == 28, "Invalid SDrawLineMessage size");

	#pragma pack(push, 4)
	struct SDrawPointMessage
	{
		static EMessageType const MessageType;
		real_point3d point; // 0x0
		float size; // 0xC
		long color; // 0x10
	};
	#pragma pack(pop)
	static_assert(sizeof(SDrawPointMessage) == 20, "Invalid SDrawPointMessage size");

	#pragma pack(push, 4)
	struct SDrawVectorMessage
	{
		static EMessageType const MessageType;
		real_point3d point; // 0x0
		real_vector3d vector; // 0xC
		long color; // 0x18
	};
	#pragma pack(pop)
	static_assert(sizeof(SDrawVectorMessage) == 28, "Invalid SDrawVectorMessage size");

	#pragma pack(push, 4)
	struct SDrawText2dMessage
	{
		static EMessageType const MessageType;
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
		static EMessageType const MessageType;
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
		static EMessageType const MessageType;
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
		static EMessageType const MessageType;
		char const *group; // 0x0
		DebugDrawKey cacheKey; // 0x4
		SClearMessage(); /* compiler_generated() */
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
		t_arg0 GetPayload();
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

extern __int32 AllocateCacheEntry();
extern __int32 FindCacheEntry(char const *group, DebugDrawKey cacheKey);
extern void EvictCacheEntry(char const *group, DebugDrawKey cacheKey);

extern "C" void PreRenderCommand(SRenderThreadMessage &command);
extern "C" void PostRenderCommand(SRenderThreadMessage &command);
extern "C" void HandleRenderThreadMessage(SRenderThreadMessage *message);
void DrawString2dInternal(real_point2d const &point, long color, char const *text, __int32 fontId, float scale);
void DrawString3dInternal(real_point3d const &point, long color, char const *text, __int32 fontId, float scale);

/* ---------- globals */

static_warning("TODO: fix threadLocalAttributes declaration");

static_warning("TODO: fix threadLocalAttributes declaration");

/* ---------- private variables */

namespace hades_file_local
{
	extern CSimpleMessageQueue<SRenderThreadMessage,4096> renderThreadQueue; // 0x1138F548
	extern SCacehEntry persistentCache[4096]; // 0x114C7560
}
using namespace hades_file_local;
/* ---------- public code */

_extern __int32 _sub_10818DD0();
__int32 AllocateCacheEntry() // 0x10818DD0
{
	mangled_x86(MANGLED_TODO, "?AllocateCacheEntry@@YAHXZ");
	// procedure flags: nofpo
	{
		// __int32 i;
	}
	todo("implement");
	__int32 __result = _sub_10818DD0();
	return __result;
}

_extern __int32 _sub_1081C0D0(char const *, DebugDrawKey);
__int32 FindCacheEntry(char const *group, DebugDrawKey cacheKey) // 0x1081C0D0
{
	mangled_x86(MANGLED_TODO, "?FindCacheEntry@@YAHPBDUDebugDrawKey@@@Z");
	// DebugDrawKey cacheKey;
	{
		// __int32 i;
	}
	todo("implement");
	__int32 __result = _sub_1081C0D0(group, cacheKey);
	return __result;
}

void EvictCacheEntry(char const *group, DebugDrawKey cacheKey) // 0x1081C060
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?EvictCacheEntry@@YAXPBDUDebugDrawKey@@@Z");
	// DebugDrawKey cacheKey;
	// long index;

	int index = FindCacheEntry(group, cacheKey);
	if (index != -1)
		persistentCache[index].valid = false;
}

_extern void _sub_1081AB70(real_point3d const &, float, long);
void CDebugDrawBackend::DrawPoint(real_point3d const &point, float size, long color) // 0x1081AB70
{
	mangled_x86(MANGLED_TODO, "?DrawPoint@CDebugDrawBackend@@SAXABUreal_point3d@@MJ@Z");
	// static ...; // 0x1081ACAC
	// real_point3d const &point;
	// float size;
	// long color;
	{
		// SRenderThreadMessage *message;
		{
			// SDrawPointMessage &payload;
		}
	}
	{
		// real_argb_color realColor;
	}
	// function call : bool (*const)()
	// function call : real_argb_color *(*const)(unsigned long, real_argb_color *)
	todo("implement");
	_sub_1081AB70(point, size, color);
}

_extern void _sub_1081A160(real_point3d const &, real_point3d const &, long);
void CDebugDrawBackend::DrawLine(real_point3d const &p1, real_point3d const &p2, long color) // 0x1081A160
{
	mangled_x86(MANGLED_TODO, "?DrawLine@CDebugDrawBackend@@SAXABUreal_point3d@@0J@Z");
	// static ...; // 0x1081A2A0
	// real_point3d const &p1;
	// real_point3d const &p2;
	// long color;
	{
		// SRenderThreadMessage *message;
		{
			// SDrawLineMessage &payload;
		}
	}
	{
		// real_argb_color realColor;
	}
	// function call : bool (*const)()
	// function call : real_argb_color *(*const)(unsigned long, real_argb_color *)
	todo("implement");
	_sub_1081A160(p1, p2, color);
}

_extern void _sub_1081BEA0(real_point3d const &, real_vector3d const &, long);
void CDebugDrawBackend::DrawVector(real_point3d const &point, real_vector3d const &vector, long color) // 0x1081BEA0
{
	mangled_x86(MANGLED_TODO, "?DrawVector@CDebugDrawBackend@@SAXABUreal_point3d@@ABUreal_vector3d@@J@Z");
	// static ...; // 0x1081BFE0
	// real_point3d const &point;
	// real_vector3d const &vector;
	// long color;
	{
		// SRenderThreadMessage *message;
		{
			// SDrawVectorMessage &payload;
		}
	}
	{
		// real_argb_color realColor;
	}
	// function call : bool (*const)()
	// function call : real_argb_color *(*const)(unsigned long, real_argb_color *)
	todo("implement");
	_sub_1081BEA0(point, vector, color);
}

_extern void _sub_1081BBB0(real_point3d const &, real_point3d const &, real_point3d const &, long);
void CDebugDrawBackend::DrawTriangle(real_point3d const &p1, real_point3d const &p2, real_point3d const &p3, long color) // 0x1081BBB0
{
	mangled_x86(MANGLED_TODO, "?DrawTriangle@CDebugDrawBackend@@SAXABUreal_point3d@@00J@Z");
	// real_point3d const &p1;
	// real_point3d const &p2;
	// real_point3d const &p3;
	// long color;
	{
		// SRenderThreadMessage *message;
		{
			// SDrawTriangleMessage &payload;
		}
	}
	{
		// real_argb_color realColor;
	}
	// function call : bool (*const)()
	// function call : real_argb_color *(*const)(unsigned long, real_argb_color *)
	todo("implement");
	_sub_1081BBB0(p1, p2, p3, color);
}

_extern void _sub_108195A0(real_rectangle3d const &, long);
void CDebugDrawBackend::DrawBox(real_rectangle3d const &bounds, long color) // 0x108195A0
{
	mangled_x86(MANGLED_TODO, "?DrawBox@CDebugDrawBackend@@SAXABUreal_rectangle3d@@J@Z");
	// static ...; // 0x108196DC
	// static ...; // 0x108196D4
	// real_rectangle3d const &bounds;
	// long color;
	{
		// SRenderThreadMessage *message;
		{
			// SDrawBoxMessage &payload;
		}
	}
	{
		// real_argb_color realColor;
	}
	// function call : bool (*const)()
	// function call : real_argb_color *(*const)(unsigned long, real_argb_color *)
	todo("implement");
	_sub_108195A0(bounds, color);
}

_extern void _sub_10819860(real_rectangle3d const &, real_matrix4x3 const &, long);
void CDebugDrawBackend::DrawBoxOriented(real_rectangle3d const &bounds, real_matrix4x3 const &matrix, long color) // 0x10819860
{
	mangled_x86(MANGLED_TODO, "?DrawBoxOriented@CDebugDrawBackend@@SAXABUreal_rectangle3d@@ABUreal_matrix4x3@@J@Z");
	// static ...; // 0x108199A8
	// real_rectangle3d const &bounds;
	// real_matrix4x3 const &matrix;
	// long color;
	{
		// SRenderThreadMessage *message;
		{
			// SDrawBoxOrientedMessage &payload;
		}
	}
	{
		// real_argb_color realColor;
	}
	// function call : bool (*const)()
	// function call : real_argb_color *(*const)(unsigned long, real_argb_color *)
	todo("implement");
	_sub_10819860(bounds, matrix, color);
}

_extern void _sub_108191E0(real_rectangle2d const &, long);
void CDebugDrawBackend::DrawBox2dOutline(real_rectangle2d const &bounds, long color) // 0x108191E0
{
	mangled_x86(MANGLED_TODO, "?DrawBox2dOutline@CDebugDrawBackend@@SAXABUreal_rectangle2d@@J@Z");
	// static ...; // 0x108193F4
	// static ...; // 0x108193EC
	// real_rectangle2d const &bounds;
	// long color;
	{
		// SRenderThreadMessage *message;
		{
			// SDrawBox2dMessage &payload;
		}
	}
	{
		// short_point_2d vertices[5];
	}
	// function call : bool (*const)()
	// function call : void (*const)(short_point_2d const *, long, unsigned long)
	todo("implement");
	_sub_108191E0(bounds, color);
}

_extern void _sub_1081AE30(real_point3d const &, float, long);
void CDebugDrawBackend::DrawSphereOutline(real_point3d const &center, float radius, long color) // 0x1081AE30
{
	mangled_x86(MANGLED_TODO, "?DrawSphereOutline@CDebugDrawBackend@@SAXABUreal_point3d@@MJ@Z");
	// static ...; // 0x1081AF6C
	// real_point3d const &center;
	// float radius;
	// long color;
	{
		// SRenderThreadMessage *message;
		{
			// SDrawSphereMessage &payload;
		}
	}
	{
		// real_argb_color realColor;
	}
	// function call : bool (*const)()
	// function call : real_argb_color *(*const)(unsigned long, real_argb_color *)
	todo("implement");
	_sub_1081AE30(center, radius, color);
}

void CDebugDrawBackend::DrawString2d(real_point2d const &point, long color, long fontId, float scale, char const *format, ...) // 0x1081B200
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawString2d@CDebugDrawBackend@@SAXABUreal_point2d@@JJMPBDZZ");
	// char *va;

	va_list va;
	va_start(va, format);
	CDebugDrawBackend::DrawString2d(point, color, fontId, scale, format, va);
	va_end(va);
}

_extern void _sub_1081B110(real_point2d const &, long, long, float, char const *, char *);
void CDebugDrawBackend::DrawString2d(real_point2d const &point, long color, long fontId, float scale, char const *format, char *va) // 0x1081B110
{
	mangled_x86(MANGLED_TODO, "?DrawString2d@CDebugDrawBackend@@SAXABUreal_point2d@@JJMPBDPAD@Z");
	// long fontId;
	// float scale;
	// char const *format;
	// char *va;
	// char buffer[256];
	todo("implement");
	_sub_1081B110(point, color, fontId, scale, format, va);
}

void CDebugDrawBackend::DrawString3d(real_point3d const &point, long color, long fontId, float scale, char const *format, ...) // 0x1081B840
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawString3d@CDebugDrawBackend@@SAXABUreal_point3d@@JJMPBDZZ");
	// char *va;

	va_list va;
	va_start(va, format);
	CDebugDrawBackend::DrawString3d(point, color, fontId, scale, format, va);
	va_end(va);
}

void CDebugDrawBackend::DrawString3d(real_point3d const &point, long color, long fontId, float scale, char const *format, char *va) // 0x1081B750
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DrawString3d@CDebugDrawBackend@@SAXABUreal_point3d@@JJMPBDPAD@Z");
	// long fontId;
	// float scale;
	// char const *format;
	// char *va;
	// char buffer[256];

	char buffer[256];

	vsnprintf(buffer, 256, format, va);
	DrawString3dInternal(point, color, buffer, fontId, scale);
}

_extern void _sub_1081A880(real_point3d const &, real_vector3d const &, float, long);
void CDebugDrawBackend::DrawPill(real_point3d const &base, real_vector3d const &height, float radius, long color) // 0x1081A880
{
	mangled_x86(MANGLED_TODO, "?DrawPill@CDebugDrawBackend@@SAXABUreal_point3d@@ABUreal_vector3d@@MJ@Z");
	// real_point3d const &base;
	// real_vector3d const &height;
	// float radius;
	// long color;
	{
		// SRenderThreadMessage *message;
		{
			// SDrawPillMessage &payload;
		}
	}
	{
		// real_argb_color realColor;
	}
	// function call : bool (*const)()
	// function call : real_argb_color *(*const)(unsigned long, real_argb_color *)
	todo("implement");
	_sub_1081A880(base, height, radius, color);
}

_extern void _sub_10819E70(real_point3d const &, real_vector3d const &, float, long);
void CDebugDrawBackend::DrawCylinder(real_point3d const &base, real_vector3d const &height, float radius, long color) // 0x10819E70
{
	mangled_x86(MANGLED_TODO, "?DrawCylinder@CDebugDrawBackend@@SAXABUreal_point3d@@ABUreal_vector3d@@MJ@Z");
	// real_point3d const &base;
	// real_vector3d const &height;
	// float radius;
	// long color;
	{
		// SRenderThreadMessage *message;
		{
			// SDrawCylinderMessage &payload;
		}
	}
	{
		// real_argb_color realColor;
	}
	// function call : bool (*const)()
	// function call : real_argb_color *(*const)(unsigned long, real_argb_color *)
	todo("implement");
	_sub_10819E70(base, height, radius, color);
}

_extern void _sub_10819B50(real_point3d const &, real_vector3d const &, float, float, long);
void CDebugDrawBackend::DrawCone(real_point3d const &base, real_vector3d const &up, float theta, float height, long color) // 0x10819B50
{
	mangled_x86(MANGLED_TODO, "?DrawCone@CDebugDrawBackend@@SAXABUreal_point3d@@ABUreal_vector3d@@MMJ@Z");
	// real_vector3d const &up;
	// float theta;
	// float height;
	// long color;
	{
		// SRenderThreadMessage *message;
		{
			// SDrawConeMessage &payload;
		}
	}
	{
		// real_argb_color realColor;
	}
	// function call : bool (*const)()
	// function call : real_argb_color *(*const)(unsigned long, real_argb_color *)
	todo("implement");
	_sub_10819B50(base, up, theta, height, color);
}

_extern void _sub_1081A440(real_point3d const &, real_point3d const &, float, real_matrix4x3 const &, long);
void CDebugDrawBackend::DrawPhysicsShapeCapsule(real_point3d const &vertex_a, real_point3d const &vertex_b, float radius, real_matrix4x3 const &matrix, long color) // 0x1081A440
{
	mangled_x86(MANGLED_TODO, "?DrawPhysicsShapeCapsule@CDebugDrawBackend@@SAXABUreal_point3d@@0MABUreal_matrix4x3@@J@Z");
	// real_point3d const &vertex_a;
	// real_point3d const &vertex_b;
	// float radius;
	// real_matrix4x3 const &matrix;
	// long color;
	{
		// SRenderThreadMessage *message;
		{
			// SDrawPhysicsShapeCapsuleMessage &payload;
		}
	}
	{
		// hkpCapsuleShape shape;
		// real_argb_color realColor;
	}
	// function call : bool (*const)()
	// function call : real_argb_color *(*const)(unsigned long, real_argb_color *)
	todo("implement");
	_sub_1081A440(vertex_a, vertex_b, radius, matrix, color);
}

_extern void _sub_1081C610();
void CDebugDrawBackend::Render() // 0x1081C610
{
	mangled_x86(MANGLED_TODO, "?Render@CDebugDrawBackend@@SAXXZ");
	// procedure flags: nofpo
	{
		// __int32 i;
	}
	// function call : bool (*const)()
	todo("implement");
	_sub_1081C610();
}

_extern void _sub_10818E90(char const *, DebugDrawKey);
void CDebugDrawBackend::Clear(char const *group, DebugDrawKey key) // 0x10818E90
{
	mangled_x86(MANGLED_TODO, "?Clear@CDebugDrawBackend@@SAXPBDUDebugDrawKey@@@Z");
	// DebugDrawKey key;
	{
		// SRenderThreadMessage *message;
		{
			// SClearMessage &payload;
		}
	}
	{
		// unsigned __int32 i;
	}
	// function call : bool (*const)()
	todo("implement");
	_sub_10818E90(group, key);
}

extern CDebugDrawBackend::AttributeScope* _sub_10817C00(CDebugDrawBackend::AttributeScope *const);
CDebugDrawBackend::AttributeScope::AttributeScope() // 0x10817C00
{
	mangled_x86(MANGLED_TODO, "??0AttributeScope@CDebugDrawBackend@@QAE@XZ");
	// CDebugDrawBackend::AttributeScope *const this;
	todo("implement");
	_sub_10817C00(this);
}

_inline CDebugDrawBackend::Attributes::Attributes() : cacheKey(todo_result<DebugDrawKey>()) // 0x10817CA0
{
	mangled_x86(MANGLED_TODO, "??0Attributes@CDebugDrawBackend@@QAE@XZ");
	compiler_generated();
	// Cannot be `= default` while `cacheKey` is initialised from `todo_result`:
	// the generator writes that because DebugDrawKey has no default constructor
	// to reconstruct, and a defaulted constructor would be implicitly deleted.
	todo("implement");
}

_extern void _sub_108181F0(CDebugDrawBackend::AttributeScope *const);
CDebugDrawBackend::AttributeScope::~AttributeScope() // 0x108181F0
{
	mangled_x86(MANGLED_TODO, "??1AttributeScope@CDebugDrawBackend@@QAE@XZ");
	// CDebugDrawBackend::AttributeScope *const this;
	todo("implement");
	_sub_108181F0(this);
}

// mangled_x86(MANGLED_DEFAULT, "??4AttributeScope@CDebugDrawBackend@@QAEAAU01@ABU01@@Z"); no body to assert in
_inline CDebugDrawBackend::AttributeScope &CDebugDrawBackend::AttributeScope::operator=(CDebugDrawBackend::AttributeScope const &__that) = default; // 0x10818430

// mangled_x86(MANGLED_DEFAULT, "??4CDebugDraw@@QAEAAV0@ABV0@@Z"); no body to assert in
_inline CDebugDraw &CDebugDraw::operator=(CDebugDraw const &__that) = default; // 0x10818470

// mangled_x86(MANGLED_DEFAULT, "??4CDebugDrawBackend@@QAEAAU0@$$QAU0@@Z"); no body to assert in
_inline CDebugDrawBackend &CDebugDrawBackend::operator=(CDebugDrawBackend &&__that) = default; // 0x108184C0

// mangled_x86(MANGLED_DEFAULT, "??4CDebugDrawBackend@@QAEAAU0@ABU0@@Z"); no body to assert in
_inline CDebugDrawBackend &CDebugDrawBackend::operator=(CDebugDrawBackend const &__that) = default; // 0x108184F0

_extern void _sub_1081CB70(CDebugDrawBackend::AttributeScope *const, float);
void CDebugDrawBackend::AttributeScope::SetLifetime(float lifetime) // 0x1081CB70
{
	mangled_x86(MANGLED_TODO, "?SetLifetime@AttributeScope@CDebugDrawBackend@@QAEXM@Z");
	// float lifetime;
	todo("implement");
	_sub_1081CB70(this, lifetime);
}

_extern void _sub_1081C8C0(CDebugDrawBackend::AttributeScope *const, char const *, DebugDrawKey);
void CDebugDrawBackend::AttributeScope::SetCacheKey(char const *group, DebugDrawKey key) // 0x1081C8C0
{
	mangled_x86(MANGLED_TODO, "?SetCacheKey@AttributeScope@CDebugDrawBackend@@QAEXPBDUDebugDrawKey@@@Z");
	// DebugDrawKey key;
	todo("implement");
	_sub_1081C8C0(this, group, key);
}

_extern void _sub_1081CAA0(CDebugDrawBackend::AttributeScope *const, __int32);
void CDebugDrawBackend::AttributeScope::SetFont(__int32 fontId) // 0x1081CAA0
{
	mangled_x86(MANGLED_TODO, "?SetFont@AttributeScope@CDebugDrawBackend@@QAEXH@Z");
	// __int32 fontId;
	todo("implement");
	_sub_1081CAA0(this, fontId);
}

_extern void _sub_1081CC50(CDebugDrawBackend::AttributeScope *const, float);
void CDebugDrawBackend::AttributeScope::SetTextScale(float scale) // 0x1081CC50
{
	mangled_x86(MANGLED_TODO, "?SetTextScale@AttributeScope@CDebugDrawBackend@@QAEXM@Z");
	// float scale;
	todo("implement");
	_sub_1081CC50(this, scale);
}

_extern void _sub_1081C9D0(CDebugDrawBackend::AttributeScope *const, bool);
void CDebugDrawBackend::AttributeScope::SetDepthTest(bool enable) // 0x1081C9D0
{
	mangled_x86(MANGLED_TODO, "?SetDepthTest@AttributeScope@CDebugDrawBackend@@QAEX_N@Z");
	// bool enable;
	todo("implement");
	_sub_1081C9D0(this, enable);
}

float CDebugDraw::GetLineHeight(__int32 fontId) const // 0x1081C220
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetLineHeight@CDebugDraw@@QBEMH@Z");
	// __int32 fontId;
	// s_font_header *(*const font_get_header)(long);
	// long (*const font_get_line_height)(s_font_header *);
	// s_font_header *header;
	// float height;
	// function call : s_font_header *(*const)(long)
	// function call : long (*const)(s_font_header *)

	void *(__cdecl *const GetFontHeader)(__int32) = (void *(__cdecl *const)(__int32))0x5092f0;
	__int32 (__cdecl *const GetFontHeaderLineHeight)(void *) = (__int32(__cdecl *const)(void *))0x65b5e0;

	void *header = GetFontHeader(fontId);
	float lineHeight = (float)GetFontHeaderLineHeight(header);
	return lineHeight;
}

/* ---------- private code */

template<typename t_arg0>
_inline t_arg0 SRenderThreadMessage::GetPayload()
{
	todo("implement");
	return todo_result<t_arg0>();
}

_extern void _sub_10818640(SPayloadVisitor *const, SDrawBox2dMessage const &);
_inline void SPayloadVisitor::operator()(SDrawBox2dMessage const &payload) // 0x10818640
{
	// SPayloadVisitor::operator()
	// SDrawBox2dMessage const &payload;
	todo("implement");
	_sub_10818640(this, payload);
}

_extern void _sub_108186A0(SPayloadVisitor *const, SDrawBoxMessage const &);
_inline void SPayloadVisitor::operator()(SDrawBoxMessage const &payload) // 0x108186A0
{
	// SPayloadVisitor::operator()
	// SDrawBoxMessage const &payload;
	todo("implement");
	_sub_108186A0(this, payload);
}

_extern void _sub_10818700(SPayloadVisitor *const, SDrawBoxOrientedMessage const &);
_inline void SPayloadVisitor::operator()(SDrawBoxOrientedMessage const &payload) // 0x10818700
{
	// SPayloadVisitor::operator()
	// SDrawBoxOrientedMessage const &payload;
	todo("implement");
	_sub_10818700(this, payload);
}

_extern void _sub_10818A60(SPayloadVisitor *const, SDrawSphereMessage const &);
_inline void SPayloadVisitor::operator()(SDrawSphereMessage const &payload) // 0x10818A60
{
	// SPayloadVisitor::operator()
	// SDrawSphereMessage const &payload;
	todo("implement");
	_sub_10818A60(this, payload);
}

_extern void _sub_10818970(SPayloadVisitor *const, SDrawPillMessage const &);
_inline void SPayloadVisitor::operator()(SDrawPillMessage const &payload) // 0x10818970
{
	// SPayloadVisitor::operator()
	// SDrawPillMessage const &payload;
	todo("implement");
	_sub_10818970(this, payload);
}

_extern void _sub_10818800(SPayloadVisitor *const, SDrawCylinderMessage const &);
_inline void SPayloadVisitor::operator()(SDrawCylinderMessage const &payload) // 0x10818800
{
	// SPayloadVisitor::operator()
	// SDrawCylinderMessage const &payload;
	todo("implement");
	_sub_10818800(this, payload);
}

_extern void _sub_10818770(SPayloadVisitor *const, SDrawConeMessage const &);
_inline void SPayloadVisitor::operator()(SDrawConeMessage const &payload) // 0x10818770
{
	// SPayloadVisitor::operator()
	// SDrawConeMessage const &payload;
	todo("implement");
	_sub_10818770(this, payload);
}

_extern void _sub_10818880(SPayloadVisitor *const, SDrawLineMessage const &);
_inline void SPayloadVisitor::operator()(SDrawLineMessage const &payload) // 0x10818880
{
	// SPayloadVisitor::operator()
	// SDrawLineMessage const &payload;
	todo("implement");
	_sub_10818880(this, payload);
}

_extern void _sub_10818C40(SPayloadVisitor *const, SDrawVectorMessage const &);
_inline void SPayloadVisitor::operator()(SDrawVectorMessage const &payload) // 0x10818C40
{
	// SPayloadVisitor::operator()
	// SDrawVectorMessage const &payload;
	todo("implement");
	_sub_10818C40(this, payload);
}

_extern void _sub_108189F0(SPayloadVisitor *const, SDrawPointMessage const &);
_inline void SPayloadVisitor::operator()(SDrawPointMessage const &payload) // 0x108189F0
{
	// SPayloadVisitor::operator()
	// SDrawPointMessage const &payload;
	todo("implement");
	_sub_108189F0(this, payload);
}

_extern void _sub_10818BD0(SPayloadVisitor *const, SDrawTriangleMessage const &);
_inline void SPayloadVisitor::operator()(SDrawTriangleMessage const &payload) // 0x10818BD0
{
	// SPayloadVisitor::operator()
	// SDrawTriangleMessage const &payload;
	todo("implement");
	_sub_10818BD0(this, payload);
}

_extern void _sub_10818AD0(SPayloadVisitor *const, SDrawText2dMessage const &);
_inline void SPayloadVisitor::operator()(SDrawText2dMessage const &payload) // 0x10818AD0
{
	// SPayloadVisitor::operator()
	// SDrawText2dMessage const &payload;
	todo("implement");
	_sub_10818AD0(this, payload);
}

_extern void _sub_10818B50(SPayloadVisitor *const, SDrawText3dMessage const &);
_inline void SPayloadVisitor::operator()(SDrawText3dMessage const &payload) // 0x10818B50
{
	// SPayloadVisitor::operator()
	// SDrawText3dMessage const &payload;
	todo("implement");
	_sub_10818B50(this, payload);
}

_extern void _sub_108188F0(SPayloadVisitor *const, SDrawPhysicsShapeCapsuleMessage const &);
_inline void SPayloadVisitor::operator()(SDrawPhysicsShapeCapsuleMessage const &payload) // 0x108188F0
{
	// SPayloadVisitor::operator()
	// SDrawPhysicsShapeCapsuleMessage const &payload;
	todo("implement");
	_sub_108188F0(this, payload);
}

_inline void SPayloadVisitor::operator()(SClearMessage const &payload) // 0x108185D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??RSPayloadVisitor@hades_file_local@@QAEXABUSClearMessage@1@@Z");
	// SPayloadVisitor::operator()
	// SClearMessage const &payload;

	CDebugDrawBackend::Clear(payload.group, payload.cacheKey);
}

_extern void _sub_1081C5C0(SRenderThreadMessage &);
extern "C" void PreRenderCommand(SRenderThreadMessage &command) // 0x1081C5C0
{
	// PreRenderCommand
	// SRenderThreadMessage &command;
	todo("implement");
	_sub_1081C5C0(command);
}

_extern void _sub_1081C570(SRenderThreadMessage &);
extern "C" void PostRenderCommand(SRenderThreadMessage &command) // 0x1081C570
{
	// PostRenderCommand
	// SRenderThreadMessage &command;
	todo("implement");
	_sub_1081C570(command);
}

_extern void _sub_1081C2D0(SRenderThreadMessage *);
extern "C" void HandleRenderThreadMessage(SRenderThreadMessage *message) // 0x1081C2D0
{
	// HandleRenderThreadMessage
	// SRenderThreadMessage *message;
	{
		// __int32 cacheEntryIndex;
	}
	todo("implement");
	_sub_1081C2D0(message);
}

_extern void _sub_1081B280(real_point2d const &, long, char const *, __int32, float);
void DrawString2dInternal(real_point2d const &point, long color, char const *text, __int32 fontId, float scale) // 0x1081B280
{
	// `anonymous-namespace'::DrawString2dInternal
	// static ...; // 0x1081B510
	// static ...; // 0x1081B508
	// real_point2d const &point;
	// long color;
	// char const *text;
	// __int32 fontId;
	// float scale;
	{
		// SRenderThreadMessage *message;
		{
			// SDrawText2dMessage &payload;
		}
	}
	{
		// real_argb_color colorf;
		// short_rectangle2d bounds;
		// c_rasterizer_draw_string m_drawString;
		// c_font_cache_mt_safe m_fontCache;
	}
	// function call : bool (*const)()
	// function call : void (*const)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *)
	// function call : real_argb_color *(*const)(unsigned long, real_argb_color *)
	todo("implement");
	_sub_1081B280(point, color, text, fontId, scale);
}

_extern void _sub_1081B8C0(real_point3d const &, long, char const *, __int32, float);
void DrawString3dInternal(real_point3d const &point, long color, char const *text, __int32 fontId, float scale) // 0x1081B8C0
{
	// `anonymous-namespace'::DrawString3dInternal
	// long color;
	// char const *text;
	// __int32 fontId;
	// float scale;
	{
		// SRenderThreadMessage *message;
		{
			// SDrawText3dMessage &payload;
		}
	}
	{
		// real_argb_color colorf;
	}
	// function call : bool (*const)()
	// function call : real_argb_color *(*const)(unsigned long, real_argb_color *)
	todo("implement");
	_sub_1081B8C0(point, color, text, fontId, scale);
}

_inline SCacehEntry::SCacehEntry() : cacheKey(todo_result<DebugDrawKey>()) // 0x10817E60
{
	mangled_x86(MANGLED_TODO, "??0SCacehEntry@hades_file_local@@QAE@XZ");
	compiler_generated();
	// Cannot be `= default` while `cacheKey` is initialised from `todo_result`:
	// DebugDrawKey has no default constructor to reconstruct, so a defaulted
	// constructor would be implicitly deleted.
	todo("implement");
}

_inline SRenderThreadMessage::SRenderThreadMessage() : cacheKey(todo_result<DebugDrawKey>()) // 0x10817F40
{
	mangled_x86(MANGLED_TODO, "??0SRenderThreadMessage@hades_file_local@@QAE@XZ");
	compiler_generated();
	// Cannot be `= default` while `cacheKey` is initialised from `todo_result`:
	// DebugDrawKey has no default constructor to reconstruct, so a defaulted
	// constructor would be implicitly deleted.
	todo("implement");
}
