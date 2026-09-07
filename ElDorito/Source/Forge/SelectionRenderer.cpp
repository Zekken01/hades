/* ---------- headers */

#include "Forge/SelectionRenderer.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/forge/forge_globals.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/saved_games/scenario_map_variant.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeVisionRenderer.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/ObjectSet.hpp"
#include "mods/map_variant_loader.hpp"
#include "Patch.hpp"
#include "Pointer.hpp"
#include "Utils/Singleton.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <bitset>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
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

struct real_matrix4x3;
struct real_rectangle3d;
struct s_forge_globals_definition;
struct s_map_variant;
struct s_object_header;
struct s_variant_datum;
namespace Forge
{
	class ObjectSet;
}
namespace hades_file_local
{
	struct SelectionItem;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Forge {}
using namespace ::Forge;
namespace Forge
{
	namespace Magnets {}
	using namespace Forge::Magnets;
	namespace Selection {}
	using namespace Forge::Selection;
	namespace Geoemetry {}
	using namespace Forge::Geoemetry;
	namespace SelectionRenderer {}
	using namespace Forge::SelectionRenderer;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	#pragma pack(push, 4)
	struct SelectionItem
	{
		real_matrix4x3 Transform; // 0x0
		float Radius; // 0x34
		float Width; // 0x38
		float Depth; // 0x3C
		float Height; // 0x40
	};
	#pragma pack(pop)
	static_assert(sizeof(SelectionItem) == 68, "Invalid SelectionItem size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Forge
{
	namespace SelectionRenderer
	{
		extern void ApplyPatches();
		extern void Update();
		extern void SetEnabled(bool enabled);
		extern void SetRendererType(Forge::SelectionRenderer::RendererImplementationType type);
		extern void Initialize();
		extern void Dispose();
	}
}

void SpecialWeaponHUDHook(__int32 a1, unsigned __int32 unitObjectIndex, __int32 a3, unsigned __int32 *objectsInCluster, short objectcount, unsigned char *activeSpecialChudTypes);
void RenderImplicit();
void RasterizeImplicitGeometryHook();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern __int32 s_RendererType; // 0x1244FBA8
	extern bool s_Enabled; // 0x1244FBAC
	extern __int32 volatile s_NumActiveItems; // 0x1244FBB0
	extern float s_SelectionColorCounter; // 0x1244FBB4
	extern long volatile s_VisionMaskBitmap; // 0x11353E4C
}
using namespace hades_file_local;
/* ---------- public code */

namespace Forge
{
	namespace SelectionRenderer
	{
		_extern void _sub_109766D0();
		void ApplyPatches() // 0x109766D0
		{
			mangled_x86(MANGLED_TODO, "?ApplyPatches@SelectionRenderer@Forge@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_109766D0();
		}

		_extern void _sub_10977300();
		void Update() // 0x10977300
		{
			mangled_x86(MANGLED_TODO, "?Update@SelectionRenderer@Forge@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x109775FC
			// static ...; // 0x109775F0
			// static ...; // 0x109775E8
			{
				// Forge::ObjectSet const &selection;
				// c_data_array<s_object_header> *objects;
				{
					// c_data_iterator<s_object_header> it;
					{
						// SelectionItem &item;
						// real_rectangle3d const *boundingBox;
					}
				}
			}
			// function call : real_matrix4x3 *(*const)(long, real_matrix4x3 *)
			// function call : float (*const)()
			todo("implement");
			_sub_10977300();
		}

		_extern void _sub_10976F60(bool);
		void SetEnabled(bool enabled) // 0x10976F60
		{
			mangled_x86(MANGLED_TODO, "?SetEnabled@SelectionRenderer@Forge@@YAX_N@Z");
			// bool enabled;
			todo("implement");
			_sub_10976F60(enabled);
		}

		_extern void _sub_10976FA0(Forge::SelectionRenderer::RendererImplementationType);
		void SetRendererType(Forge::SelectionRenderer::RendererImplementationType type) // 0x10976FA0
		{
			mangled_x86(MANGLED_TODO, "?SetRendererType@SelectionRenderer@Forge@@YAXW4RendererImplementationType@12@@Z");
			// Forge::SelectionRenderer::RendererImplementationType type;
			todo("implement");
			_sub_10976FA0(type);
		}

		_extern void _sub_10976940();
		void Initialize() // 0x10976940
		{
			mangled_x86(MANGLED_TODO, "?Initialize@SelectionRenderer@Forge@@YAXXZ");
			// procedure flags: nofpo
			// s_forge_globals_definition *forgeGlobals;
			todo("implement");
			_sub_10976940();
		}

		_extern void _sub_10976910();
		void Dispose() // 0x10976910
		{
			mangled_x86(MANGLED_TODO, "?Dispose@SelectionRenderer@Forge@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10976910();
		}
	}
}

/* ---------- private code */

_extern void _sub_10976FD0(__int32, unsigned __int32, __int32, unsigned __int32 *, short, unsigned char *);
void SpecialWeaponHUDHook(__int32 a1, unsigned __int32 unitObjectIndex, __int32 a3, unsigned __int32 *objectsInCluster, short objectcount, unsigned char *activeSpecialChudTypes) // 0x10976FD0
{
	// `anonymous-namespace'::SpecialWeaponHUDHook
	// unsigned char *activeSpecialChudTypes;
	// static void (*`SpecialWeaponHUDHook'::`2'::sub_A7A510)(__int32); // 0x11353E60
	// static __int32 (*`SpecialWeaponHUDHook'::`2'::sub_A781F0)(); // 0x11353E70
	// static void (*`SpecialWeaponHUDHook'::`2'::sub_A53160)(__int32, __int32, char, char); // 0x11353E5C
	// static void (*`SpecialWeaponHUDHook'::`2'::sub_686FD0)(); // 0x11353E54
	// Forge::ObjectSet const &selection;
	// static __int32 (*`SpecialWeaponHUDHook'::`2'::sub_A78F00)(__int32, __int32); // 0x11353E6C
	// static __int32 (*`SpecialWeaponHUDHook'::`2'::sub_A48E40)(__int32, __int32, __int32); // 0x11353E68
	// static void (*`SpecialWeaponHUDHook'::`2'::sub_A2CAA0)(__int32, unsigned __int32, __int32, unsigned __int32 *, short, unsigned char *); // 0x11353E50
	// static __int32 (*`SpecialWeaponHUDHook'::`2'::sub_686DE0)(); // 0x11353E74
	// static unsigned char (*`SpecialWeaponHUDHook'::`2'::sub_A242E0)(__int32, __int32); // 0x11353E64
	// s_map_variant *mapv;
	// static void (*`SpecialWeaponHUDHook'::`2'::sub_A78230)(); // 0x11353E58
	{
		// __int32 i;
		{
			// s_variant_datum &placement;
			{
				// __int32 const specialHudType;
			}
		}
	}
	// function call : void (*)(__int32, unsigned __int32, __int32, unsigned __int32 *, short, unsigned char *)
	// function call : void (*)()
	// function call : void (*)()
	// function call : void (*)(__int32, __int32, char, char)
	// function call : void (*)(__int32)
	// function call : unsigned char (*)(__int32, __int32)
	// function call : __int32 (*)(__int32, __int32, __int32)
	// function call : __int32 (*)(__int32, __int32)
	// function call : __int32 (*)(__int32, __int32, __int32)
	// function call : __int32 (*)(__int32, __int32, __int32)
	// function call : __int32 (*)()
	// function call : __int32 (*)()
	todo("implement");
	_sub_10976FD0(a1, unitObjectIndex, a3, objectsInCluster, objectcount, activeSpecialChudTypes);
}

_extern void _sub_10976A10();
void RenderImplicit() // 0x10976A10
{
	// `anonymous-namespace'::RenderImplicit
	// procedure flags: nofpo
	// static ...; // 0x10976E42
	// static ...; // 0x10976E3C
	// static ...; // 0x10976E24
	// static ...; // 0x10976E1C
	// constexpr __int32 (*const `RenderImplicit'::`2'::DrawPrimitive)(__int32, __int32, void *, __int32); // constant == 10650416
	// s_forge_globals_definition *forgeGlobals;
	// __int32 s_ImplicitShader;
	// constexpr __int32 (*const `RenderImplicit'::`2'::sub_A232D0)(__int32); // constant == 10629840
	// void *shaderDef;
	// constexpr bool (*const `RenderImplicit'::`2'::UseDefaultShader)(__int32, __int32, __int32, __int32); // constant == 10629888
	// constexpr void (*const `RenderImplicit'::`2'::sub_A3CA60)(unsigned __int32, void *, __int32, unsigned __int32, __int32, __int32); // constant == 10734176
	// constexpr __int32 (*const `RenderImplicit'::`2'::sub_A22BA0)(); // constant == 10628000
	// constexpr void (*const `RenderImplicit'::`2'::SetArgument)(__int32, __int32, void *); // constant == 10904592
	// __int32 const PT_TRIANGLESTRIP;
	{
		// __int32 i;
		{
			// float color[4];
			// __int32 v14;
			// SelectionItem const &item;
			// float m[12];
		}
	}
	// function call : bool (*const)(__int32, __int32, __int32, __int32)
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(unsigned __int32, void *, __int32, unsigned __int32, __int32, __int32)
	// function call : void (*const)(__int32, __int32, void *)
	// function call : void (*const)(__int32, __int32, void *)
	// function call : __int32 (*const)()
	// function call : __int32 (*const)(__int32)
	// function call : __int32 (*const)(__int32, __int32, void *, __int32)
	// function call : __int32 (*const)(__int32, __int32, void *, __int32)
	// function call : __int32 (*const)(__int32, __int32, void *, __int32)
	// function call : __int32 (*const)(__int32, __int32, void *, __int32)
	// function call : __int32 (*const)(__int32, __int32, void *, __int32)
	// function call : __int32 (*const)(__int32, __int32, void *, __int32)
	todo("implement");
	_sub_10976A10();
}

_extern void _sub_109769B0();
void RasterizeImplicitGeometryHook() // 0x109769B0
{
	// `anonymous-namespace'::RasterizeImplicitGeometryHook
	// procedure flags: nofpo
	// constexpr void (*const `RasterizeImplicitGeometryHook'::`2'::RasterizeImplicitGeometry)(); // constant == 10961840
	// function call : void (*const)()
	todo("implement");
	_sub_109769B0();
}
