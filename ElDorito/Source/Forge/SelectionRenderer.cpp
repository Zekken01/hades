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
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeVisionRenderer.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/ObjectSet.hpp"
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
struct s_object_header;
namespace Forge
{
	class ObjectSet;
}
namespace
{
	struct SelectionItem;
}

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

namespace
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

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern __int32 s_RendererType; // 0x1244FBA8
	extern bool s_Enabled; // 0x1244FBAC
	extern __int32 volatile s_NumActiveItems; // 0x1244FBB0
	extern float s_SelectionColorCounter; // 0x1244FBB4
	extern long volatile s_VisionMaskBitmap; // 0x11353E4C
}
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
