/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/BlamNetwork.hpp"
#include "Blam/camera/director.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_engine_candy_monitor.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/interface/gui/gui_bitmap_widget.hpp"
#include "Blam/interface/gui/gui_list_item_widget.hpp"
#include "Blam/interface/gui/gui_list_widget.hpp"
#include "Blam/interface/gui/gui_screen_widget.hpp"
#include "Blam/interface/gui/gui_widget.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "ElDorito.hpp"
#include "Modules/ModuleInput.hpp"
#include "Modules/ModuleSettings.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"

#include "Player/PlayerCustomization.hpp"  // hades: added for 0x10AD0F40

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

class c_director;
class c_gui_bitmap_widget;
class c_gui_data;
class c_gui_list_item_widget;
class c_gui_screen_widget;
class c_gui_widget;
struct real_argb_color;
struct s_player_datum;
struct s_tag_data;
namespace Blam
{
	namespace Input
	{
		struct BindingsTable;
	}
}
namespace Modules
{
	class ModuleInput;
	class ModuleSettings;
}
namespace hades_file_local
{
	struct c_observer_camera_list_screen;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
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
	namespace Spectate {}
	using namespace Patches::Spectate;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Input {}
	using namespace Blam::Input;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct c_observer_camera_list_screen :
		public c_gui_screen_widget
	{
		s_tag_data *data_source; // 0x1AA0
		long user_index; // 0x1AA4
		c_observer_camera_list_screen(c_observer_camera_list_screen &); /* compiler_generated() */
		c_observer_camera_list_screen(c_observer_camera_list_screen const &); /* compiler_generated() */
		c_observer_camera_list_screen(); /* compiler_generated() */
		virtual ~c_observer_camera_list_screen() = default; /* compiler_generated() */
		c_observer_camera_list_screen &operator=(c_observer_camera_list_screen &); /* compiler_generated() */
		c_observer_camera_list_screen &operator=(c_observer_camera_list_screen const &); /* compiler_generated() */
	};
	static_assert(sizeof(c_observer_camera_list_screen) == 6824, "Invalid c_observer_camera_list_screen size");
}
using namespace hades_file_local;
//struct get_player_index_from_list_item::__l2::s_player_info
//{
//	long player_index; // 0x0
//	long type; // 0x4
//};
//static_assert(sizeof(get_player_index_from_list_item::__l2::s_player_info) == 8, "Invalid get_player_index_from_list_item::__l2::s_player_info size");

/* ---------- prototypes */

extern bool (*const game_is_multiplayer)();  // hades: added for 0x10AD0AC0

namespace Player { namespace PlayerNetworkUtil { long get_session_player_index_from_player_datum_index(long player_datum_index); } }  // hades: added for 0X10AD0E10

namespace Patches
{
	namespace Spectate
	{
		extern void ApplyAll();
	}
}

void GetObserverCameraSensitivityHook(__int32 localPlayerIndex, float *sensitivity);
long c_director__player_switch_update__object_get_ultimate_parent_hook(long object_index);
void __fastcall c_director__player_switch_gui_create_or_update_hook(c_director *thisptr);
long c_game_director__update_watched_player_when_unit_deleted_fix(long avoid_player_index, long starting_player_index, long a2, long direction, bool same_team, bool a6, bool a7, long *out_unit_index);
long get_player_index_from_list_item(c_observer_camera_list_screen *screen, c_gui_list_item_widget *item);
void __fastcall c_observer_camera_list_screen__update_hook(c_observer_camera_list_screen *thisptr, void *__formal, unsigned long milliseconds);
void __fastcall c_observer_camera_list_screen__update_render_state_hook(c_observer_camera_list_screen *thisptr, void *__formal, unsigned long milliseconds);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Spectate
	{
		void ApplyAll() // 0x10AD0360
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Spectate@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x32A8D6, GetObserverCameraSensitivityHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1930FB, c_director__player_switch_update__object_get_ultimate_parent_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x192D80, c_director__player_switch_gui_create_or_update_hook).Apply();
			Hook(0x6BBCC0, c_observer_camera_list_screen__update_render_state_hook).Apply();
			Pointer(0x169B714).Write(c_observer_camera_list_screen__update_hook);
			Hook(0x321A38, c_game_director__update_watched_player_when_unit_deleted_fix, static_cast<__int32>(HookFlags::IsCall)).Apply();
		}
	}
}

/* ---------- private code */

void GetObserverCameraSensitivityHook(__int32 localPlayerIndex, float *sensitivity) // 0x10AD08C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetObserverCameraSensitivityHook@@YAXHPAM@Z");
	// `anonymous-namespace'::GetObserverCameraSensitivityHook
	// float *sensitivity;
	// Modules::ModuleSettings &moduleSettings;
	// bool const isUsingController;
	// Blam::Input::BindingsTable *bindings;
	// Modules::ModuleInput &moduleInput;
	// float sens;

	auto& moduleInput = Modules::ModuleInput::Instance();
	auto& moduleSettings = Modules::ModuleSettings::Instance();
	auto bindings = moduleInput.GetBindings();

	float sens = moduleInput.VarSpectateSensitivity->ValueFloat;

	// the controller defaults are unreasonably sensitive
	const auto isUsingController = *(bool*)0x0244DE98;
	if (isUsingController)
	{
		sens *= 0.015f;
		sensitivity[0] = bindings->ControllerSensitivityX * 0.017453292f * sens;
		sensitivity[1] = bindings->ControllerSensitivityY * 0.017453292f * sens;
	}
	else
	{
		sensitivity[0] = (moduleSettings.VarMouseSensitivityHorizontal->ValueInt / 100.0f * 360.0f) * 0.017453294f * sens;
		sensitivity[1] = (moduleSettings.VarMouseSensitivityVertical->ValueInt / 100.0f * 360.0f) * 0.017453294f * sens;
	}
}

long c_director__player_switch_update__object_get_ultimate_parent_hook(long object_index) // 0x10AD0CF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_director__player_switch_update__object_get_ultimate_parent_hook@@YAJJ@Z");
	// `anonymous-namespace'::c_director__player_switch_update__object_get_ultimate_parent_hook
	// long object_index;

	return object_index;
}

void __fastcall c_director__player_switch_gui_create_or_update_hook(c_director *thisptr) // 0x10AD0AC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_director__player_switch_gui_create_or_update_hook@@YIXPAVc_director@@@Z");
	// `anonymous-namespace'::c_director__player_switch_gui_create_or_update_hook
	// c_director *thisptr;
	// c_observer_camera_list_screen *camera_list_screen;
	// long controller_index;
	// long window_index;
		// bool is_playback;
	// function call : bool (*const)(char)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : char (*const)(c_director *)
	// function call : unsigned long (*const)(long)
	// function call : long (*const)(long)
	// function call : c_observer_camera_list_screen *(*const)(long)
	// function call : bool (*const)(long)
	// function call : c_observer_camera_list_screen *(*const)(long)
	// function call : void (*const)(c_director *)
	// function call : bool (*const)()
	// function call : void (*const)(c_gui_widget *, bool)
	// function call : void (*const)(c_gui_widget *, long, bool)

	if (((bool (*)(long))0x5523A0)(4))
		return;
	if (!((bool (*)())0x550F90)())
		return;
	if (!game_is_multiplayer() || ((bool (*)())0x531BE0)())
	{
		((void (__thiscall *)(c_director *))0x592D90)(thisptr);
		return;
	}
	long controller_index = ((long (*)(long))0xA7CF00)(thisptr->user_index);
	if (controller_index == -1)
		return;
	long window_index = ((long (*)(long))0xA7CE80)(controller_index);
	if (!((void *(*)(long))0xABBAF0)(window_index))
		((void (*)(long))0x592CC0)(thisptr->user_index);
	c_observer_camera_list_screen *camera_list_screen = (c_observer_camera_list_screen *)((void *(*)(long))0xABBAF0)(window_index);
	if (camera_list_screen)
	{
		((void (__thiscall *)(c_director *))0x592E30)(thisptr);
		if (!camera_list_screen->is_visible())
		{
			camera_list_screen->set_visible(true);
			bool is_playback = ((bool (*)())0x531D10)();
			((void (__thiscall *)(c_observer_camera_list_screen *, bool))0xABA760)(camera_list_screen, true);
			((void (__thiscall *)(c_observer_camera_list_screen *, long, bool))0xABA890)(camera_list_screen, 30, true);
		}
	}
}

long c_game_director__update_watched_player_when_unit_deleted_fix(long avoid_player_index, long starting_player_index, long a2, long direction, bool same_team, bool a6, bool a7, long *out_unit_index) // 0x10AD0D10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_game_director__update_watched_player_when_unit_deleted_fix@@YAJJJJJ_N00PAJ@Z");
	// `anonymous-namespace'::c_game_director__update_watched_player_when_unit_deleted_fix
	// long *out_unit_index;
	// void (*const c_director__set_watched_player)(c_director *, long);
	// long (*const c_director__player_get_next_player_with_a_unit)(long, long, long, long, bool, bool, bool, long *);
	// long next_player_index;
		// long output_user_index;
	// function call : long (*const)(long, long, long, long, bool, bool, bool, long *)
	// function call : long (*const)(long)
	// function call : c_director *(*const)(long)
	// function call : void (*const)(c_director *, long)

	void (__thiscall *const c_player_view__set_watched_player_index)(void *player_view, long player_index) = (void (__thiscall *)(void *, long))0x5934D0;
	long (*const c_game_director__update_watched_player_when_unit_deleted)(long, long, long, long, bool, bool, bool, long *) = (long (*)(long, long, long, long, bool, bool, bool, long *))0x592A80;

	long next_player_index = c_game_director__update_watched_player_when_unit_deleted(avoid_player_index, starting_player_index, a2, direction, same_team, a6, a7, out_unit_index);

	if (avoid_player_index != -1)
	{
		long output_user_index = ((long (*)(long))0x589A70)(avoid_player_index);

		c_player_view__set_watched_player_index(((void *(*)(long))0x591990)(output_user_index), next_player_index);
	}

	return next_player_index;
}

long get_player_index_from_list_item(c_observer_camera_list_screen *screen, c_gui_list_item_widget *item) // 0x10AD1160
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_player_index_from_list_item@@YAJPAUc_observer_camera_list_screen@hades_file_local@@PAVc_gui_list_item_widget@@@Z");
	// `anonymous-namespace'::get_player_index_from_list_item
	// static ...; // 0x10AD1220
	// static ...; // 0x10AD1218
	// c_observer_camera_list_screen *screen;
	// c_gui_list_item_widget *item;
	// c_gui_data *data;
	// long element_handle;
	// get_player_index_from_list_item::__l2::s_player_info player_info;
	// function call : long ()
	// function call : bool (long, void *, long)

	struct s_player_info
	{
		long player_index;
		long unknown4;
	};

	c_gui_data *data = screen->get_datasource(0x100E1);
	if (!data)
		return -1;

	long element_handle = item->get_element_handle();
	if (element_handle == -1)
		return -1;

	s_player_info player_info;
	if (!data->get_element(element_handle, &player_info, sizeof(player_info)))
		return -1;

	return player_info.player_index;
}

void __fastcall c_observer_camera_list_screen__update_hook(c_observer_camera_list_screen *thisptr, void *__formal, unsigned long milliseconds) // 0x10AD0E10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_observer_camera_list_screen__update_hook@@YIXPAUc_observer_camera_list_screen@hades_file_local@@PAXK@Z");
	// `anonymous-namespace'::c_observer_camera_list_screen__update_hook
	// unsigned long milliseconds;
	// long player_index;
	// long player_idx;
	// void (*const c_observer_camera_list_screen__update)(c_observer_camera_list_screen *, unsigned long);
	// c_gui_bitmap_widget *player_emblem_widget;
	// function call : void (*const)(c_observer_camera_list_screen *, unsigned long)

	void (__thiscall *const c_observer_camera_list_screen__update)(c_observer_camera_list_screen *, unsigned long) = (void (__thiscall *)(c_observer_camera_list_screen *, unsigned long))0xABBB30;

	if (*(bool *)((unsigned char *)thisptr + 0x111))
	{
		thisptr->set_visible(false);
	}

	c_observer_camera_list_screen__update(thisptr, milliseconds);

	if (!*(c_gui_list_item_widget **)((unsigned char *)thisptr + 0xF0))
		return;

	c_gui_bitmap_widget *bitmap_widget = (*(c_gui_list_item_widget **)((unsigned char *)thisptr + 0xF0))->get_child_bitmap_widget(0x103DB);
	if (!bitmap_widget)
		return;

	long player_index = get_player_index_from_list_item(thisptr, *(c_gui_list_item_widget **)((unsigned char *)thisptr + 0xF0));
	if (player_index == -1)
		return;

	long session_player_index = Player::PlayerNetworkUtil::get_session_player_index_from_player_datum_index(player_index);
	if (session_player_index == -1)
		return;

	bitmap_widget->set_sprite_frame_index(session_player_index | 0x8000);
}

void __fastcall c_observer_camera_list_screen__update_render_state_hook(c_observer_camera_list_screen *thisptr, void *__formal, unsigned long milliseconds) // 0x10AD0F40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_observer_camera_list_screen__update_render_state_hook@@YIXPAUc_observer_camera_list_screen@hades_file_local@@PAXK@Z");
	// `anonymous-namespace'::c_observer_camera_list_screen__update_render_state_hook
	// static ...; // 0x10AD10D4
	// c_observer_camera_list_screen *thisptr;
	// void *__formal;
	// unsigned long milliseconds;
	// void (*const update_render_state)(c_gui_widget *, unsigned long);
	// long player_index;
	// c_gui_bitmap_widget *base_color_widget;
		// s_player_datum *player;
		// long player_idx;
		// real_argb_color base_color;
	// function call : void (*const)(c_gui_widget *, unsigned long)
	// function call : bool (*const)()
	// function call : void (*const)(c_gui_widget *, long, bool)
	// function call : real_argb_color *(*const)(unsigned long, real_argb_color *)
	// function call : void (*const)(c_gui_widget *, real_argb_color const *)

	void (__thiscall *const update_render_state)(c_gui_widget *, unsigned long) = reinterpret_cast<void (__thiscall *)(c_gui_widget *, unsigned long)>(0xABB1A0);
	update_render_state(thisptr, milliseconds);
	if (!thisptr->focused_widget)
		return;
	long player_index = get_player_index_from_list_item(thisptr, (c_gui_list_item_widget *)thisptr->focused_widget);
	if (player_index == -1)
		return;
	c_gui_bitmap_widget *base_color_widget = thisptr->focused_widget->get_child_bitmap_widget(0x10144);
	if (!base_color_widget)
		return;
	if (((bool (*)())0x5565E0)())
	{
		s_player_datum *player = player_get(player_index);
		if (!player)
			return;
		((void (*)(c_gui_bitmap_widget *, long, bool))0xAA4C80)(base_color_widget, player->configuration.host.team, true);
	}
	else
	{
		long player_idx = Player::PlayerNetworkUtil::get_session_player_index_from_player_datum_index(player_index);
		if (player_idx == -1)
			return;
		real_argb_color base_color;
		((void (*)(unsigned long, real_argb_color *))0x5211C0)(Player::CPlayerCustomization::GetPlayerPrimaryColor((signed char)player_idx), &base_color);
		base_color.alpha = 1.0f;
		((void (__thiscall *)(c_gui_bitmap_widget *, real_argb_color const *))0xAB9D70)(base_color_widget, &base_color);
	}
}
