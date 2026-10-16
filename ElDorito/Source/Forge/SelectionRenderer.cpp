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

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const object_get_world_matrix = reinterpret_cast<real_matrix4x3 *(*)(long, real_matrix4x3 *)>(0xB2EC60);
}

extern float (*const game_tick_length)();  // hades: added for 0x10977300
extern c_data_array<s_object_header> *object_headers_get();  // hades: added for 0x10977300

#include "Modules/ModuleTweaks.hpp"  // hades: added for 0x10976FD0
#include "Forge/ForgeUtil.hpp"  // hades: added for 0x10976FD0
namespace Forge { namespace Selection { extern ::Forge::ObjectSet &GetSelection(); } }  // hades: added for 0x10976FD0

long tag_find_by_name(unsigned long group_tag, char const *name);  // hades: added for 0X10976940

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
	extern long volatile s_VisionMaskBitmap; // 0x11353E4C
	extern __int32 s_RendererType; // 0x1244FBA8
	extern bool s_Enabled; // 0x1244FBAC
	extern __int32 volatile s_NumActiveItems; // 0x1244FBB0
	extern float s_SelectionColorCounter; // 0x1244FBB4
	extern SelectionItem s_items[256]; // 0x1244FBB8
}
using namespace hades_file_local;
/* ---------- public code */

namespace Forge
{
	namespace SelectionRenderer
	{
		void ApplyPatches() // 0x109766D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyPatches@SelectionRenderer@Forge@@YAXXZ");

			Hook(0x62E760, SpecialWeaponHUDHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x63B409, RasterizeImplicitGeometryHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
		}

		void Update() // 0x10977300
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Update@SelectionRenderer@Forge@@YAXXZ");

			if (s_RendererType == eRendererImplicit)
			{
				s_NumActiveItems = 0;
				Forge::ObjectSet const &selection = Forge::Selection::GetSelection();
				c_data_array<s_object_header> *objects = object_headers_get();
				for (c_data_iterator<s_object_header> it = objects->begin(); it != objects->end() && s_NumActiveItems < 256; ++it)
				{
					if (!selection.Contains(it.current_datum_index))
						continue;
					SelectionItem &item = s_items[s_NumActiveItems++];
					real_rectangle3d const *boundingBox = Forge::GetObjectBoundingBox(it->data->definition_index);
					if (!boundingBox)
						continue;
					eldorado::object_get_world_matrix(it.current_datum_index, &item.Transform);
					item.Transform.forward *= (boundingBox->x1 - boundingBox->x0) * 1.02f;
					item.Transform.left *= (boundingBox->y1 - boundingBox->y0) * 1.02f;
					item.Transform.up *= (boundingBox->z1 - boundingBox->z0) * 1.02f;
					item.Transform.position = it->data->bounding_sphere_center;
					item.Width = boundingBox->x1 - boundingBox->x0;
					item.Depth = boundingBox->y1 - boundingBox->y0;
					item.Height = boundingBox->z1 - boundingBox->z0;
				}
				s_SelectionColorCounter += game_tick_length() / 1.0f;
				if (s_SelectionColorCounter > 6.2831855f)
					s_SelectionColorCounter -= 6.2831855f;
			}
			Forge::CForgeVisionRenderer::SetActive(s_Enabled && !s_RendererType);
			if (Forge::CForgeVisionRenderer::IsActive())
				Forge::CForgeVisionRenderer::Update();
		}

		void SetEnabled(bool enabled) // 0x10976F60
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetEnabled@SelectionRenderer@Forge@@YAX_N@Z");

			s_Enabled = enabled;

			if (!enabled)
			{
				s_NumActiveItems = 0;
			}
		}

		void SetRendererType(Forge::SelectionRenderer::RendererImplementationType type) // 0x10976FA0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetRendererType@SelectionRenderer@Forge@@YAXW4RendererImplementationType@12@@Z");

			s_RendererType = type;
		}

		void Initialize() // 0x10976940
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Initialize@SelectionRenderer@Forge@@YAXXZ");

			auto *forge_globals = forge_globals_get_definition();
			if (forge_globals)
				s_VisionMaskBitmap = tag_find_by_name(0x6269746D, "shaders\\default_bitmaps\\bitmaps\\alpha_white");
		}

		void Dispose() // 0x10976910
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Dispose@SelectionRenderer@Forge@@YAXXZ");

			s_NumActiveItems = 0;
		}
	}
}

/* ---------- private code */

void SpecialWeaponHUDHook(__int32 a1, unsigned __int32 unitObjectIndex, __int32 a3, unsigned __int32 *objectsInCluster, short objectcount, unsigned char *activeSpecialChudTypes) // 0x10976FD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SpecialWeaponHUDHook@@YAXHIHPAIFPAE@Z");

	static void (*sub_A2CAA0)(__int32, unsigned __int32, __int32, unsigned __int32 *, short, unsigned char *) = reinterpret_cast<void (*)(__int32, unsigned __int32, __int32, unsigned __int32 *, short, unsigned char *)>(0xA2CAA0);
	static void (*sub_686FD0)() = reinterpret_cast<void (*)()>(0x686FD0);
	static void (*sub_A78230)() = reinterpret_cast<void (*)()>(0xA78230);
	static void (*sub_A53160)(__int32, __int32, char, char) = reinterpret_cast<void (*)(__int32, __int32, char, char)>(0xA53160);
	static void (*sub_A7A510)(__int32) = reinterpret_cast<void (*)(__int32)>(0xA7A510);
	static unsigned char (*sub_A242E0)(__int32, __int32) = reinterpret_cast<unsigned char (*)(__int32, __int32)>(0xA242E0);
	static __int32 (*sub_A48E40)(__int32, __int32, __int32) = reinterpret_cast<__int32 (*)(__int32, __int32, __int32)>(0xA48E40);
	static __int32 (*sub_A78F00)(__int32, __int32) = reinterpret_cast<__int32 (*)(__int32, __int32)>(0xA78F00);
	static __int32 (*sub_A781F0)() = reinterpret_cast<__int32 (*)()>(0xA781F0);
	static __int32 (*sub_686DE0)() = reinterpret_cast<__int32 (*)()>(0x686DE0);
	if (!s_Enabled || s_RendererType)
	{
		if (!Utils::Singleton<Modules::ModuleTweaks>::Instance().VarDisableWeaponOutline->ValueInt)
			sub_A2CAA0(a1, unitObjectIndex, a3, objectsInCluster, objectcount, activeSpecialChudTypes);
		return;
	}
	s_map_variant *mapv = ::Forge::GetMapVariant();
	if (!mapv)
		return;
	::Forge::ObjectSet const &selection = ::Forge::Selection::GetSelection();
	if (!selection.Any())
		return;
	for (__int32 i = 0; i < mapv->variant_object_count; i++)
	{
		s_variant_datum &placement = mapv->objects[i];
		if (selection.Contains(placement.object_index))
		{
			__int32 const specialHudType = 6;
			activeSpecialChudTypes[specialHudType] = 1;
			sub_686FD0();
			sub_A78230();
			sub_A53160(placement.object_index, a1, 0, 1);
			sub_A7A510(0);
			sub_A242E0(18, (unsigned char)floor(191.25));
			sub_A48E40(2, 23, -1);
			sub_A78F00(0, 1);
			sub_A48E40(1, 0, 0);
			sub_A48E40(2, 0, 0);
			sub_A781F0();
			sub_686DE0();
		}
	}
}

void RenderImplicit() // 0x10976A10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RenderImplicit@@YAXXZ");

	Forge::Magnets::Render();
	if (s_RendererType != eRendererImplicit)
		return;
	__int32 s_ImplicitShader = -1;
	s_forge_globals_definition *forgeGlobals = forge_globals_get_definition();
	if (forgeGlobals)
		s_ImplicitShader = forgeGlobals->default_boundary_method.index;
	__int32 const PT_TRIANGLESTRIP = 5;
	if (!(s_Enabled && ((bool (*)(__int32, __int32, __int32, __int32))0xA23300)(64, 20, 0, 0)))
		return;
	void *shaderDef = tag_get('rm  ', s_ImplicitShader);
	((void (*)(unsigned __int32, void *, __int32, unsigned __int32, __int32, __int32))0xA3CA60)(s_ImplicitShader, shaderDef, 20, 0, PT_TRIANGLESTRIP, 1);
	for (__int32 i = 0; i < s_NumActiveItems; i++)
	{
		SelectionItem const &item = s_items[i];
		float m[12];
		m[0] = item.Transform.forward.i;
		m[1] = item.Transform.left.i;
		m[2] = item.Transform.up.i;
		m[3] = item.Transform.position.x;
		m[4] = item.Transform.forward.j;
		m[5] = item.Transform.left.j;
		m[6] = item.Transform.up.j;
		m[7] = item.Transform.position.y;
		m[8] = item.Transform.forward.k;
		m[9] = item.Transform.left.k;
		m[10] = item.Transform.up.k;
		m[11] = item.Transform.position.z;
		float color[4] =
		{
			sin(s_SelectionColorCounter + 2.0f) * 0.5f + 0.5f,
			sin(s_SelectionColorCounter + 0.0f) * 0.5f + 0.5f,
			sin(s_SelectionColorCounter + 4.0f) * 0.5f + 0.5f,
			1.0f,
		};
		((void (*)(__int32, __int32, void *))0xA66410)(24, 3, m);
		((void (*)(__int32, __int32, void *))0xA66410)(20, 1, color);
		__int32 v14 = ((__int32 (*)())0xA22BA0)();
		((__int32 (*)(__int32))0xA232D0)(1);
		((__int32 (*)(__int32, __int32, void *, __int32))0xA28330)(PT_TRIANGLESTRIP, 2, (void *)(Forge::hades_file_local_Forge::Geoemetry::BOX_VERTICES + 0), 20);
		((__int32 (*)(__int32, __int32, void *, __int32))0xA28330)(PT_TRIANGLESTRIP, 2, (void *)(Forge::hades_file_local_Forge::Geoemetry::BOX_VERTICES + 4), 20);
		((__int32 (*)(__int32, __int32, void *, __int32))0xA28330)(PT_TRIANGLESTRIP, 2, (void *)(Forge::hades_file_local_Forge::Geoemetry::BOX_VERTICES + 8), 20);
		((__int32 (*)(__int32, __int32, void *, __int32))0xA28330)(PT_TRIANGLESTRIP, 2, (void *)(Forge::hades_file_local_Forge::Geoemetry::BOX_VERTICES + 12), 20);
		((__int32 (*)(__int32, __int32, void *, __int32))0xA28330)(PT_TRIANGLESTRIP, 2, (void *)(Forge::hades_file_local_Forge::Geoemetry::BOX_VERTICES + 16), 20);
		((__int32 (*)(__int32, __int32, void *, __int32))0xA28330)(PT_TRIANGLESTRIP, 2, (void *)(Forge::hades_file_local_Forge::Geoemetry::BOX_VERTICES + 20), 20);
	}
}

void RasterizeImplicitGeometryHook() // 0x109769B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RasterizeImplicitGeometryHook@@YAXXZ");

	((void (*)())0xa743b0)();

	if (!s_Enabled)
	{
		return;
	}

	RenderImplicit();
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { long volatile s_VisionMaskBitmap = -1; }
namespace hades_file_local { __int32 s_RendererType; }
namespace hades_file_local { bool s_Enabled; }
namespace hades_file_local { __int32 volatile s_NumActiveItems; }
namespace hades_file_local { float s_SelectionColorCounter; }
namespace hades_file_local { SelectionItem s_items[256]; }
