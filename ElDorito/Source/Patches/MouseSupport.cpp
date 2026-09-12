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
#include "ChatCommands/ChatCommandMap.hpp"
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

class CDebugDraw;
class c_gui_data;
class c_gui_list_item_widget;
class c_gui_list_widget;
class c_gui_screen_widget;
class c_gui_widget;
struct real_point2d;
struct real_rectangle2d;
namespace hades_file_local
{
	struct SMouseSupportContext;
}
using namespace hades_file_local;

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

namespace hades_file_local
{
	enum EMouseContext
	{
		TagUI = 0,
		Cef,
		Game,
	};
}
using namespace hades_file_local;
/* ---------- definitions */

namespace hades_file_local
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
using namespace hades_file_local;
/* ---------- prototypes */

namespace Patches
{
	namespace MouseSupport
	{
		extern void ApplyAll();
		extern void NotifyMouseMove(__int32 x, __int32 y);
	}
}

void SetMouseContext(EMouseContext ctx);
void MouseSupportUpdate();
void ScrollListWidget(c_gui_screen_widget *screenWidget, c_gui_list_widget *listWidget, __int32 amount);
bool HandleScreen(c_gui_screen_widget *screenWidget, SMouseSupportContext &ctx);
bool HandleListWidgets(c_gui_screen_widget *screenWidget, SMouseSupportContext &ctx, c_gui_widget *parentWidget);
bool HandleListWidget(c_gui_screen_widget *screenWidget, c_gui_list_widget *listWidget, SMouseSupportContext &ctx);
bool HandleSpinnerListWidgetFocus(c_gui_screen_widget *screenWidget, c_gui_list_widget *listWidget, SMouseSupportContext &ctx);
void ComputeListItemBounds(c_gui_list_item_widget *itemWidget, real_rectangle2d &bounds);
void UpdateMouseMovementTracking(SMouseSupportContext &state);
void UpdateMouseState(SMouseSupportContext &state);
void ComputeWidgetBounds(c_gui_widget *widget, real_rectangle2d *accumulatedBounds, bool (*childFilter)(c_gui_widget const &));
void MapWidgetBoundsToWindowCoords(real_rectangle2d const &windowBounds, real_rectangle2d &widgetBounds);
bool RectangleContainsPoint(real_rectangle2d const &rect, real_point2d const &point);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern __int32 globalMouseX; // 0x12408358
	extern __int32 globalMouseY; // 0x1240835C
	extern float globalMouseMoveDelta; // 0x12408360
}
using namespace hades_file_local;
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

		void NotifyMouseMove(__int32 x, __int32 y) // 0x108D5390
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?NotifyMouseMove@MouseSupport@Patches@@YAXHH@Z");
			// __int32 y;
			// float deltaSquared;
			// __int32 deltaX;
			// __int32 deltaY;

			int deltaX = abs(x - globalMouseX);
			int deltaY = abs(y - globalMouseY);
			float distance = (float)(deltaX * deltaX + deltaY * deltaY);
			globalMouseMoveDelta += distance * 1.0f / 60.0f;
			globalMouseX = x;
			globalMouseY = y;
		}
	}
}

/* ---------- private code */

_extern void _sub_108D5630(EMouseContext);
void SetMouseContext(EMouseContext ctx) // 0x108D5630
{
	// `anonymous-namespace'::SetMouseContext
	// EMouseContext ctx;
	// static EMouseContext `SetMouseContext'::`2'::lastCtx; // 0x11352D84
	{
		// c_gui_screen_widget *activeScreen;
		// bool tagUiOpen;
		{
			// c_gui_widget *focusedWidget;
		}
	}
	todo("implement");
	_sub_108D5630(ctx);
}

_extern void _sub_108D50B0();
void MouseSupportUpdate() // 0x108D50B0
{
	// `anonymous-namespace'::MouseSupportUpdate
	// procedure flags: nofpo
	// static ...; // 0x108D52F0
	// static ...; // 0x108D52E4
	// static ...; // 0x108D52DC
	// static SMouseSupportContext `MouseSupportUpdate'::`2'::ctx; // 0x12408364
	// bool isDebug;
	// c_gui_screen_widget *activeScreen;
	{
		// CDebugDraw dd;
	}
	{
		// c_gui_widget *focusedWidget;
	}
	// function call : HWND__ *()
	todo("implement");
	_sub_108D50B0();
}

_extern void _sub_108D54F0(c_gui_screen_widget *, c_gui_list_widget *, __int32);
void ScrollListWidget(c_gui_screen_widget *screenWidget, c_gui_list_widget *listWidget, __int32 amount) // 0x108D54F0
{
	// `anonymous-namespace'::ScrollListWidget
	// __int32 amount;
	// long &visibleItemCount;
	// c_gui_data *data;
	// long &pageOffset;
	// long newIndex;
	// long dataItemCount;
	// function call : long ()
	todo("implement");
	_sub_108D54F0(screenWidget, listWidget, amount);
}

_extern bool _sub_108D48A0(c_gui_screen_widget *, SMouseSupportContext &);
bool HandleScreen(c_gui_screen_widget *screenWidget, SMouseSupportContext &ctx) // 0x108D48A0
{
	// `anonymous-namespace'::HandleScreen
	// SMouseSupportContext &ctx;
	// c_gui_widget *focusedWidget;
	// static long `HandleScreen'::`2'::lastScreenWidgetName; // 0x11352D88
	{
		// c_gui_list_widget *listWidget;
	}
	{
		{
			// __int32 amount;
			// long index;
		}
	}
	todo("implement");
	bool __result = _sub_108D48A0(screenWidget, ctx);
	return __result;
}

_extern bool _sub_108D47A0(c_gui_screen_widget *, SMouseSupportContext &, c_gui_widget *);
bool HandleListWidgets(c_gui_screen_widget *screenWidget, SMouseSupportContext &ctx, c_gui_widget *parentWidget) // 0x108D47A0
{
	// `anonymous-namespace'::HandleListWidgets
	// c_gui_widget *parentWidget;
	// bool handled;
	{
		// c_gui_widget *widget;
	}
	todo("implement");
	bool __result = _sub_108D47A0(screenWidget, ctx, parentWidget);
	return __result;
}

_extern bool _sub_108D3FD0(c_gui_screen_widget *, c_gui_list_widget *, SMouseSupportContext &);
bool HandleListWidget(c_gui_screen_widget *screenWidget, c_gui_list_widget *listWidget, SMouseSupportContext &ctx) // 0x108D3FD0
{
	// `anonymous-namespace'::HandleListWidget
	// static ...; // 0x108D45EC
	// static ...; // 0x108D45E4
	// c_gui_screen_widget *screenWidget;
	// c_gui_list_widget *listWidget;
	// SMouseSupportContext &ctx;
	// bool isDebug;
	// bool handled;
	// c_gui_list_item_widget *listItem;
	{
		// CDebugDraw dd;
		// real_rectangle2d bounds;
		{
			// bool isTransitioning;
			// long transitionStateFlags;
			// c_gui_widget *focused_widget;
		}
	}
	todo("implement");
	bool __result = _sub_108D3FD0(screenWidget, listWidget, ctx);
	return __result;
}

_extern bool _sub_108D4A60(c_gui_screen_widget *, c_gui_list_widget *, SMouseSupportContext &);
bool HandleSpinnerListWidgetFocus(c_gui_screen_widget *screenWidget, c_gui_list_widget *listWidget, SMouseSupportContext &ctx) // 0x108D4A60
{
	// `anonymous-namespace'::HandleSpinnerListWidgetFocus
	// SMouseSupportContext &ctx;
	// c_gui_widget *focusedParent;
	// void (*const animateArrowButton)(c_gui_list_widget *, c_gui_widget *, __int32);
	// c_gui_widget *focused;
	{
		// __int32 amount;
		// c_gui_data *data;
		// long index;
		// long dataItemCount;
	}
	// function call : long ()
	todo("implement");
	bool __result = _sub_108D4A60(screenWidget, listWidget, ctx);
	return __result;
}

_extern void _sub_108D3CC0(c_gui_list_item_widget *, real_rectangle2d &);
void ComputeListItemBounds(c_gui_list_item_widget *itemWidget, real_rectangle2d &bounds) // 0x108D3CC0
{
	// `anonymous-namespace'::ComputeListItemBounds
	// static ...; // 0x108D3D84
	// static ...; // 0x108D3D7C
	// c_gui_list_item_widget *itemWidget;
	// real_rectangle2d &bounds;
	// real_point2d anchorPos;
	todo("implement");
	_sub_108D3CC0(itemWidget, bounds);
}

_extern void _sub_108D5970(SMouseSupportContext &);
void UpdateMouseMovementTracking(SMouseSupportContext &state) // 0x108D5970
{
	// `anonymous-namespace'::UpdateMouseMovementTracking
	// SMouseSupportContext &state;
	todo("implement");
	_sub_108D5970(state);
}

_extern void _sub_108D5A20(SMouseSupportContext &);
void UpdateMouseState(SMouseSupportContext &state) // 0x108D5A20
{
	// `anonymous-namespace'::UpdateMouseState
	// SMouseSupportContext &state;
	// unsigned long *clientResolution;
	// unsigned long *renderBoundaries;
	todo("implement");
	_sub_108D5A20(state);
}

_extern void _sub_108D3DD0(c_gui_widget *, real_rectangle2d *, bool (*)(c_gui_widget const &));
void ComputeWidgetBounds(c_gui_widget *widget, real_rectangle2d *accumulatedBounds, bool (*childFilter)(c_gui_widget const &)) // 0x108D3DD0
{
	// `anonymous-namespace'::ComputeWidgetBounds
	// static ...; // 0x108D3F4C
	// c_gui_widget *widget;
	// real_rectangle2d *accumulatedBounds;
	// bool (*childFilter)(c_gui_widget const &);
	// c_gui_widget *child;
	{
		// real_rectangle2d bounds;
	}
	// function call : bool (*)(c_gui_widget const &)
	todo("implement");
	_sub_108D3DD0(widget, accumulatedBounds, childFilter);
}

_extern void _sub_108D4BE0(real_rectangle2d const &, real_rectangle2d &);
void MapWidgetBoundsToWindowCoords(real_rectangle2d const &windowBounds, real_rectangle2d &widgetBounds) // 0x108D4BE0
{
	// `anonymous-namespace'::MapWidgetBoundsToWindowCoords
	// static ...; // 0x108D4F95
	// static ...; // 0x108D4F88
	// static ...; // 0x108D4F64
	// static ...; // 0x108D4F5C
	// real_rectangle2d const &windowBounds;
	// real_rectangle2d &widgetBounds;
	// long (*const interface_get_closest_authored_ui_aspect_ratio)();
	// float ui_aspect_ratio;
	// float window_height;
	// float ui_tag_resolutions[2][2];
	// long *ui_resolution;
	// float widescreen_factor;
	// float window_width;
	// long display_mode;
	// real_point2d window_scale;
	// real_point2d ui_scale;
	// function call : long (*const)()
	todo("implement");
	_sub_108D4BE0(windowBounds, widgetBounds);
}

bool RectangleContainsPoint(real_rectangle2d const &rect, real_point2d const &point) // 0x108D5460
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RectangleContainsPoint@@YA_NABUreal_rectangle2d@@ABUreal_point2d@@@Z");
	// `anonymous-namespace'::RectangleContainsPoint
	// real_point2d const &point;

	return point.x >= rect.x0 && rect.x1 >= point.x && point.y >= rect.y0 && rect.y1 >= point.y;
}
