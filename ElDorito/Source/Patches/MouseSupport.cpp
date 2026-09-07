/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/input/input.hpp"
#include "Blam/interface/gui/gui_list_item_widget.hpp"
#include "Blam/interface/gui/gui_list_widget.hpp"
#include "Blam/interface/gui/gui_screen_widget.hpp"
#include "Blam/interface/gui/gui_widget.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Debug/DebugDraw.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "Utils/Singleton.hpp"
#include "Web/Ui/Screen.hpp"

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

struct real_point2d;
struct real_rectangle2d;
namespace
{
	struct SMouseSupportContext;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Ui {}
	using namespace Web::Ui;
}

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer {}
		using namespace Web::Ui::ScreenLayer;
	}
}

namespace Web
{
	namespace Browser {}
	using namespace Web::Browser;
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge {}
		using namespace Web::Browser::Bridge;
	}
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace MouseSupport {}
	using namespace Patches::MouseSupport;
	namespace Camera {}
	using namespace Patches::Camera;
	namespace Input {}
	using namespace Patches::Input;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

namespace
{
	enum EMouseContext
	{
		TagUI = 0,
		Cef,
		Game,
	};
}
/* ---------- definitions */

namespace
{
	#pragma pack(push, 4)
	struct SMouseSupportContext
	{
		__int32 userIndex; // 0x0
		real_rectangle2d windowBounds; // 0x4
		real_point2d windowMouseCoords; // 0x14
		real_point2d lastWindowMouseCoords; // 0x1C
		unsigned char mouseMoveTicks; // 0x24
		unsigned char leftButtonDownTicks; // 0x25
		unsigned char rightButtonDownTicks; // 0x26
		unsigned char __pad0[1]; // 0x27
		short mouseWheelDelta; // 0x28
		unsigned char __pad1[2]; // 0x2A
		void *lastFocusedWidget; // 0x2C
		bool listItemSelectedDirty; // 0x30
		SMouseSupportContext(); /* compiler_generated() */
		unsigned char __pad2[3]; // 0x31
	};
	#pragma pack(pop)
	static_assert(sizeof(SMouseSupportContext) == 52, "Invalid SMouseSupportContext size");
}
/* ---------- prototypes */

namespace Patches
{
	namespace MouseSupport
	{
		extern void ApplyAll();
		extern void NotifyMouseMove(__int32 x, __int32 y);
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern __int32 globalMouseX; // 0x12408358
	extern __int32 globalMouseY; // 0x1240835C
	extern float globalMouseMoveDelta; // 0x12408360
}
/* ---------- public code */

namespace Patches
{
	namespace MouseSupport
	{
		_extern void _sub_108D3B60();
		void ApplyAll() // 0x108D3B60
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@MouseSupport@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_108D3B60();
		}

		_extern void _sub_108D5390(__int32, __int32);
		void NotifyMouseMove(__int32 x, __int32 y) // 0x108D5390
		{
			mangled_x86(MANGLED_TODO, "?NotifyMouseMove@MouseSupport@Patches@@YAXHH@Z");
			// __int32 y;
			// float deltaSquared;
			// __int32 deltaX;
			// __int32 deltaY;
			todo("implement");
			_sub_108D5390(x, y);
		}
	}
}

/* ---------- private code */
