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

#include "Blam/interface/gui/gui_screen_manager.hpp"  // hades: added for 0x108D5630

#include "Modules/ModuleSettings.hpp"  // hades: added for 0x108D3FD0

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
		// SMouseSupportContext(); /* compiler_generated() */ - implicit: the static in MouseSupportUpdate has no init guard
		unsigned char __pad2[3]; // 0x31
	};
	#pragma pack(pop)
	static_assert(sizeof(SMouseSupportContext) == 52, "Invalid SMouseSupportContext size");
}
using namespace hades_file_local;
/* ---------- prototypes */

#include "Modules/ModuleDebug.hpp"  // hades: added for 0x108D50B0
#include "Blam/camera/camera.hpp"  // hades: added for 0x108D50B0
namespace Patches { namespace Camera { extern e_camera_mode GetForcedCameraMode(); } }  // hades: added for 0x108D50B0

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
		void ApplyAll() // 0x108D3B60
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@MouseSupport@Patches@@YAXXZ");

			Hook(0x684F49, MouseSupportUpdate, static_cast<__int32>(HookFlags::IsCall)).Apply();
		}

		void NotifyMouseMove(__int32 x, __int32 y) // 0x108D5390
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?NotifyMouseMove@MouseSupport@Patches@@YAXHH@Z");

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

void SetMouseContext(EMouseContext ctx) // 0x108D5630
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetMouseContext@@YAXW4EMouseContext@hades_file_local@@@Z");

	static EMouseContext lastCtx = Game;
	if (ctx != lastCtx)
	{
		bool tagUiOpen = false;
		c_gui_screen_widget *activeScreen = c_gui_screen_manager::get()->get_topmost_screen();
		if (activeScreen)
		{
			c_gui_widget *focusedWidget = activeScreen->get_focused_widget();
			if (focusedWidget)
				tagUiOpen = true;
		}
		lastCtx = ctx;
		Blam::Input::BlockInput(Blam::Input::eInputTypeGame, ctx != Game);
		Web::Ui::ScreenLayer::Notify("mouseCapture", "{\"blocked\":" + std::string(ctx == TagUI ? "true" : "false") + ",\"tagMenuOpen\":" + (tagUiOpen ? "true" : "false") + "}", true);
	}
}

void MouseSupportUpdate() // 0x108D50B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?MouseSupportUpdate@@YAXXZ");

	static SMouseSupportContext ctx;
	bool isDebug = Utils::Singleton<Modules::ModuleDebug>::Instance().VarMouseSupport->ValueInt != 0;
	if (*(HWND *)0x199C014 != GetForegroundWindow())
		return;
	if (Patches::Camera::GetForcedCameraMode() == _camera_mode_flying)
		return;
	if (Blam::Input::InputIsBlocked(Blam::Input::eInputTypeUi))
	{
		SetMouseContext(Cef);
		return;
	}
	UpdateMouseState(ctx);
	if (isDebug)
	{
	#line 133 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\MouseSupport.cpp"
			CDebugDraw dd(std::source_location::
	#line 133 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\MouseSupport.cpp"
	             current());
	#line 312 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\MouseSupport.cpp"
		dd.SetLifetime(1.0f);
		dd.DrawString2d("mouse-window-coords", { 100.0f, 84.0f }, -1, "mouse window coords: %f, %f", ctx.windowMouseCoords.x, ctx.windowMouseCoords.y);
	}
	c_gui_screen_widget *activeScreen = c_gui_screen_manager::get()->get_topmost_screen();
	if (activeScreen)
	{
		c_gui_widget *focusedWidget = activeScreen->get_focused_widget();
		// The saved film control pad leaves the film's camera to the sticks, as the
		// game's camera_input_inhibited does: with a controller, game input stays on.
		bool const k_controller_in_use = *(bool *)0x244DE98;
		unsigned long const k_saved_film_control_pad = 0x100D2;
		if (focusedWidget && k_controller_in_use && activeScreen->get_name_string_id() == k_saved_film_control_pad)
		{
			SetMouseContext(Game);
			return;
		}
		if (focusedWidget)
		{
			SetMouseContext(TagUI);
			if (!HandleScreen(activeScreen, ctx))
				ctx.lastFocusedWidget = nullptr;
			return;
		}
	}
	SetMouseContext(Game);
}

void ScrollListWidget(c_gui_screen_widget *screenWidget, c_gui_list_widget *listWidget, __int32 amount) // 0x108D54F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ScrollListWidget@@YAXPAVc_gui_screen_widget@@PAVc_gui_list_widget@@H@Z");

	if (!amount)
		return;

	c_gui_data *data = screenWidget->get_datasource(listWidget->get_item_datasource_name());
	long dataItemCount = data->get_current_item_count();
	if (!dataItemCount)
		return;

	long &visibleItemCount = *(long *)offset_pointer(listWidget, 0x120);
	long &pageOffset = *(long *)offset_pointer(listWidget, 0x148);
	if (pageOffset == -1)
		return;

	long newIndex = pageOffset + amount;
	if (newIndex > dataItemCount - visibleItemCount)
		newIndex = dataItemCount - visibleItemCount;
	if (newIndex < 0)
		newIndex = 0;
	if (pageOffset != newIndex)
		*(long *)offset_pointer(listWidget, 0x140) = -1;
	pageOffset = newIndex;
}

bool HandleScreen(c_gui_screen_widget *screenWidget, SMouseSupportContext &ctx) // 0x108D48A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleScreen@@YA_NPAVc_gui_screen_widget@@AAUSMouseSupportContext@hades_file_local@@@Z");

	if (ctx.rightButtonDownTicks == 1)
	{
		Blam::Input::PostUiAction(ctx.userIndex, Blam::Input::eGameActionUiB);
		return true;
	}
	c_gui_widget *focusedWidget = screenWidget->get_focused_widget();
	if (focusedWidget && focusedWidget->get_type() == _gui_widget_listItem)
	{
		c_gui_list_widget *listWidget = (c_gui_list_widget *)focusedWidget->get_parent();
		if (listWidget && listWidget->get_type() == _gui_widget_list && HandleSpinnerListWidgetFocus(screenWidget, listWidget, ctx))
		{
			ctx.listItemSelectedDirty = true;
			return true;
		}
	}
	static long lastScreenWidgetName = -1;
	if (screenWidget->get_name_string_id() != lastScreenWidgetName)
	{
		lastScreenWidgetName = screenWidget->get_name_string_id();
		ctx.listItemSelectedDirty = true;
	}
	if (focusedWidget && focusedWidget->get_type() == _gui_widget_listItem)
	{
		c_gui_list_widget *listWidget = (c_gui_list_widget *)focusedWidget->get_parent();
		if (listWidget && listWidget->get_type() == _gui_widget_list)
		{
			long index = listWidget->get_selected_index();
			__int32 amount = ctx.mouseWheelDelta / 120;
			ScrollListWidget(screenWidget, listWidget, -amount);
		}
	}
	if (HandleListWidgets(screenWidget, ctx, nullptr))
		return true;
	return false;
}

bool HandleListWidgets(c_gui_screen_widget *screenWidget, SMouseSupportContext &ctx, c_gui_widget *parentWidget) // 0x108D47A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleListWidgets@@YA_NPAVc_gui_screen_widget@@AAUSMouseSupportContext@hades_file_local@@PAVc_gui_widget@@@Z");

	bool handled = false;

	if (!parentWidget)
		parentWidget = screenWidget;

	for (c_gui_list_widget *widget = (c_gui_list_widget *)parentWidget->get_first_child(); widget && !handled; widget = (c_gui_list_widget *)widget->get_next_sibling())
	{
		if (!widget->is_visible())
			continue;

		if (widget->get_type() == _gui_widget_list)
		{
			handled = HandleListWidget(screenWidget, widget, ctx);
		}
		else if (widget->get_type() == _gui_widget_listItem)
		{
		}
		else
		{
			handled = HandleListWidgets(screenWidget, ctx, widget);
		}
	}

	return handled;
}

bool HandleListWidget(c_gui_screen_widget *screenWidget, c_gui_list_widget *listWidget, SMouseSupportContext &ctx) // 0x108D3FD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleListWidget@@YA_NPAVc_gui_screen_widget@@PAVc_gui_list_widget@@AAUSMouseSupportContext@hades_file_local@@@Z");

	bool isDebug = Utils::Singleton<Modules::ModuleDebug>::Instance().VarMouseSupport->ValueInt != 0;
	bool handled = false;
	c_gui_list_item_widget *listItem;
	for (listItem = (c_gui_list_item_widget *)listWidget->find_first_child(_gui_widget_listItem); listItem; listItem = listItem->find_next_item())
	{
		if (!listItem->is_visible() || listItem->get_data_item_index() == -1)
			continue;
		real_rectangle2d bounds = {};
		ComputeListItemBounds(listItem, bounds);
		MapWidgetBoundsToWindowCoords(ctx.windowBounds, bounds);
	#line 296 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\MouseSupport.cpp"
			CDebugDraw dd(std::source_location::
	#line 296 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\MouseSupport.cpp"
	             current());
	#line 479 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\MouseSupport.cpp"
		dd.SetLifetime(1.0f);
		if (isDebug)
			dd.DrawBox2dOutline({ "bounds", (unsigned __int32)listItem }, bounds, 0xFFFFFF00);
		if (Utils::Singleton<Modules::ModuleSettings>::Instance().VarGamepadEnabled->ValueInt == 1 && !ctx.leftButtonDownTicks && !ctx.mouseMoveTicks)
		{
			handled = true;
			return false;
		}
		if (RectangleContainsPoint(bounds, ctx.windowMouseCoords))
		{
			c_gui_widget *focused_widget = screenWidget->get_focused_widget();
			if (isDebug)
			{
				dd.DrawBox2dOutline({ "bounds", (unsigned __int32)listItem }, bounds, 0xFF00FF00);
				dd.DrawString2d("bounds-coords", { bounds.x0, bounds.y0 }, -1, "bounds: %f, %f %f, %f", bounds.x0, bounds.y0, bounds.x1, bounds.y1);
				dd.DrawString2d("item-index", { 100.0f, 100.0f }, -1, "item index: %d", listItem->get_item_index());
				dd.DrawString2d("data-item-index", { 100.0f, 116.0f }, -1, "data item index: %d", listItem->get_data_item_index());
				dd.DrawString2d("list-item-index", { 100.0f, 132.0f }, -1, "list item index: %d", listWidget->get_selected_index());
				dd.DrawString2d("list-data-item-index", { 100.0f, 148.0f }, -1, "list data item index: %d", listWidget->get_selected_data_item_index());
				dd.DrawString2d("scroll-offset", { 100.0f, 164.0f }, -1, "scroll offset: %d", *(long *)offset_pointer(listWidget, 0x148));
				dd.DrawString2d("focused", { 100.0f, 180.0f }, -1, "focused: %d", ((c_gui_list_item_widget *)focused_widget)->get_data_item_index());
			}
			if ((ctx.mouseMoveTicks > 0 && ctx.lastFocusedWidget != listItem) || ctx.listItemSelectedDirty)
			{
				ctx.listItemSelectedDirty = false;
				if (focused_widget && focused_widget->get_parent() != listWidget)
				{
					ctx.lastFocusedWidget = nullptr;
					screenWidget->select_list_item(listWidget, listItem->get_data_item_index(), true, false);
				}
				else if (focused_widget != listItem)
				{
					ctx.lastFocusedWidget = nullptr;
					screenWidget->select_list_item(listWidget, listItem->get_data_item_index(), true, true);
				}
			}
			long transitionStateFlags = *(long *)offset_pointer(screenWidget, 0x68);
			bool isTransitioning = transitionStateFlags >> 3 || transitionStateFlags >> 5;
			if (ctx.leftButtonDownTicks == 1 && listItem == focused_widget && !isTransitioning)
			{
				ctx.lastFocusedWidget = listItem;
				Blam::Input::PostUiAction(ctx.userIndex, Blam::Input::eGameActionUiA);
			}
			handled = true;
			if (!isDebug)
				break;
		}
		else if (ctx.lastFocusedWidget == listItem)
		{
			ctx.lastFocusedWidget = nullptr;
		}
	}
	return false;
}

bool HandleSpinnerListWidgetFocus(c_gui_screen_widget *screenWidget, c_gui_list_widget *listWidget, SMouseSupportContext &ctx) // 0x108D4A60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleSpinnerListWidgetFocus@@YA_NPAVc_gui_screen_widget@@PAVc_gui_list_widget@@AAUSMouseSupportContext@hades_file_local@@@Z");

	void (*const animateArrowButton)(c_gui_list_widget *, c_gui_widget *, __int32) = reinterpret_cast<void (*)(c_gui_list_widget *, c_gui_widget *, __int32)>(0xB157F0);
	c_gui_widget *focused = screenWidget->get_focused_widget();
	c_gui_widget *focusedParent = focused->get_parent();
	if (listWidget != focusedParent)
		return false;
	if (listWidget->get_parent() && listWidget->get_parent()->get_type() == 5)
	{
		if (ctx.leftButtonDownTicks == 1)
			Blam::Input::PostUiAction(ctx.userIndex, Blam::Input::eGameActionUiA);
		c_gui_data *data = screenWidget->get_datasource(listWidget->get_item_datasource_name());
		long dataItemCount = data->get_current_item_count();
		if (!dataItemCount)
			return true;
		long index = listWidget->get_selected_index();
		__int32 amount = ctx.mouseWheelDelta / 120;
		if ((index -= amount) < 0)
			index += dataItemCount;
		if (index >= dataItemCount)
			index -= dataItemCount;
		listWidget->select_item(index);
		return true;
	}
	return false;
}

void ComputeListItemBounds(c_gui_list_item_widget *itemWidget, real_rectangle2d &bounds) // 0x108D3CC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ComputeListItemBounds@@YAXPAVc_gui_list_item_widget@@AAUreal_rectangle2d@@@Z");

	ComputeWidgetBounds(itemWidget, &bounds, [](auto const &widget)
	{
		return widget.is_visible() && widget.get_type() == _gui_widget_bitmap;
	});
	real_point2d anchorPos = itemWidget->get_anchor_position();
	bounds.x0 += anchorPos.x;
	bounds.x1 += anchorPos.x;
	bounds.y0 += anchorPos.y;
	bounds.y1 += anchorPos.y;
}

void UpdateMouseMovementTracking(SMouseSupportContext &state) // 0x108D5970
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateMouseMovementTracking@@YAXAAUSMouseSupportContext@hades_file_local@@@Z");

	if (globalMouseMoveDelta > 0.00001f)
	{
		globalMouseMoveDelta *= 0.4f;
	}
	else
	{
		globalMouseMoveDelta = 0.0f;
	}

	if (globalMouseMoveDelta >= 0.01f)
	{
		if (state.mouseMoveTicks < 255)
		{
			state.mouseMoveTicks++;
		}
	}
	else
	{
		state.mouseMoveTicks = 0;
	}
}

void UpdateMouseState(SMouseSupportContext &state) // 0x108D5A20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateMouseState@@YAXAAUSMouseSupportContext@hades_file_local@@@Z");

	unsigned long *clientResolution = (unsigned long *)0x19106D0;
	unsigned long *renderBoundaries = (unsigned long *)0x19106E4;
	UpdateMouseMovementTracking(state);
	state.userIndex = 0;
	state.windowBounds = { (float)clientResolution[0], (float)renderBoundaries[0] - (float)clientResolution[0], (float)clientResolution[1], (float)renderBoundaries[1] - (float)clientResolution[1] };
	state.lastWindowMouseCoords = state.windowMouseCoords;
	state.windowMouseCoords = { (float)globalMouseX, (float)globalMouseY };
	state.leftButtonDownTicks = Blam::Input::GetMouseButtonTicks(Blam::Input::eMouseButtonLeft, Blam::Input::eInputTypeUi);
	state.rightButtonDownTicks = Blam::Input::GetMouseButtonTicks(Blam::Input::eMouseButtonRight, Blam::Input::eInputTypeUi);
	state.mouseWheelDelta = *(short *)0x238E6C8;
}

void ComputeWidgetBounds(c_gui_widget *widget, real_rectangle2d *accumulatedBounds, bool (*childFilter)(c_gui_widget const &)) // 0x108D3DD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ComputeWidgetBounds@@YAXPAVc_gui_widget@@PAUreal_rectangle2d@@P6A_NABV1@@Z@Z");

	c_gui_widget *child;

	for (child = widget->get_first_child(); child; child = child->get_next_sibling())
	{
		if (!childFilter(*child))
		{
			continue;
		}

		real_rectangle2d bounds = {};
		child->get_render_bounds(&bounds);

		if (accumulatedBounds->x0 > bounds.x0 || accumulatedBounds->x0 == 0.0f)
		{
			accumulatedBounds->x0 = bounds.x0;
		}

		if (bounds.x1 > accumulatedBounds->x1 || accumulatedBounds->x1 == 0.0f)
		{
			accumulatedBounds->x1 = bounds.x1;
		}

		if (accumulatedBounds->y0 > bounds.y0 || accumulatedBounds->y0 == 0.0f)
		{
			accumulatedBounds->y0 = bounds.y0;
		}

		if (bounds.y1 > accumulatedBounds->y1 || accumulatedBounds->y1 == 0.0f)
		{
			accumulatedBounds->y1 = bounds.y1;
		}
	}
}

void MapWidgetBoundsToWindowCoords(real_rectangle2d const &windowBounds, real_rectangle2d &widgetBounds) // 0x108D4BE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?MapWidgetBoundsToWindowCoords@@YAXABUreal_rectangle2d@@AAU1@@Z");

	long (*const interface_get_closest_authored_ui_aspect_ratio)() = reinterpret_cast<long (*)()>(0xA9F980);
	long display_mode = interface_get_closest_authored_ui_aspect_ratio();
	long *ui_resolution = reinterpret_cast<long *>(0x19106C8);
	float ui_aspect_ratio = (float)ui_resolution[0] / (float)ui_resolution[1];
	float ui_tag_resolutions[2][2] = { { 1512.0f, 840.0f }, { 840.0f, 630.0f } };
	float widescreen_factor = ui_aspect_ratio / (display_mode == 1 ? 1.3333333f : 1.7777778f);
	real_point2d ui_scale;
	ui_scale.x = ui_resolution[0] / ui_tag_resolutions[display_mode][0] / widescreen_factor;
	ui_scale.y = ui_resolution[1] / ui_tag_resolutions[display_mode][1];
	widgetBounds.x0 *= ui_scale.x;
	widgetBounds.x1 *= ui_scale.x;
	widgetBounds.y0 *= ui_scale.y;
	widgetBounds.y1 *= ui_scale.y;
	widgetBounds.x0 += ui_resolution[0] / 2.0f;
	widgetBounds.x1 += ui_resolution[0] / 2.0f;
	widgetBounds.y0 += ui_resolution[1] / 2.0f;
	widgetBounds.y1 += ui_resolution[1] / 2.0f;
	float window_width = windowBounds.x1 - windowBounds.x0;
	float window_height = windowBounds.y1 - windowBounds.y0;
	real_point2d window_scale;
	window_scale.x = window_width / ui_resolution[0];
	window_scale.y = window_height / ui_resolution[1];
	widgetBounds.x0 *= window_scale.x;
	widgetBounds.x1 *= window_scale.x;
	widgetBounds.y0 *= window_scale.y;
	widgetBounds.y1 *= window_scale.y;
	widgetBounds.x0 += windowBounds.x0;
	widgetBounds.x1 += windowBounds.x0;
	widgetBounds.y0 += windowBounds.y0;
	widgetBounds.y1 += windowBounds.y0;
}

bool RectangleContainsPoint(real_rectangle2d const &rect, real_point2d const &point) // 0x108D5460
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RectangleContainsPoint@@YA_NABUreal_rectangle2d@@ABUreal_point2d@@@Z");

	return point.x >= rect.x0 && rect.x1 >= point.x && point.y >= rect.y0 && rect.y1 >= point.y;
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { __int32 globalMouseX; }
namespace hades_file_local { __int32 globalMouseY; }
namespace hades_file_local { float globalMouseMoveDelta; }
