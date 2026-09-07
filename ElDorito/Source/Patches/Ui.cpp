/* ---------- headers */

#include "Patches/Ui.hpp"
#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/multiplayer_definitions.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/input/input.hpp"
#include "Blam/interface/chud/chud_globals.hpp"
#include "Blam/interface/gui/gui_list_item_widget.hpp"
#include "Blam/interface/gui/gui_list_widget.hpp"
#include "Blam/interface/gui/gui_screen_manager.hpp"
#include "Blam/interface/gui/gui_screen_widget.hpp"
#include "Blam/interface/gui/gui_widget.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/networking/session/network_session_parameters_custom.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/draw_string.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "ElDorito.hpp"
#include "Interface/CustomBitmapManager.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Player/PlayerServiceRecord.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/rapidjson.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/DewritoReader.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/Ui/ScreenLayer.hpp"

#include <Windows.h>
#include <intsafe.h>
#include <roapi.h>
#include <roerrorapi.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <weakreference.h>
#include <wrl/client.h>
#include <wrl/event.h>
#include <wrl/implements.h>
#include <wrl/internal.h>
#include <wrl/module.h>
#include <wrl/wrappers/corewrappers.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <memory>
#include <mutex>
#include <optional>
#include <ostream>
#include <ratio>
#include <regex>
#include <shared_mutex>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class _Closure_wrapper_569e7c00_1;
class _Closure_wrapper_569e7c00_2;
class _Closure_wrapper_569e7c00_3;
class c_gui_data;
class c_gui_list_item_widget;
class c_gui_list_widget;
class c_gui_screen_manager;
class c_gui_screen_widget;
struct lambda_1;
struct lambda_2;
struct lambda_3;
struct lambda_invoker_cdecl;
struct lambda_typedef_cdecl;
struct lambda_typedef_fastcall;
struct lambda_typedef_stdcall;
struct lambda_typedef_vectorcall;
struct s_multiplayer_globals_definition;
struct s_scenario;
namespace Player
{
	namespace ServiceRecord
	{
		struct ServiceRecord;
	}
}

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
namespace Player
{
	namespace PlayerPodium {}
	using namespace Player::PlayerPodium;
	namespace ServiceRecord {}
	using namespace Player::ServiceRecord;
}

namespace Windows {}
using namespace ::Windows;
namespace Windows
{
	namespace Foundation {}
	using namespace Windows::Foundation;
}

namespace Windows
{
	namespace Foundation
	{
		namespace Diagnostics {}
		using namespace Windows::Foundation::Diagnostics;
	}
}

namespace ABI {}
using namespace ::ABI;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Web {}
using namespace ::Web;
namespace Patches
{
	namespace Ui {}
	using namespace Patches::Ui;
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
	namespace Camera {}
	using namespace Patches::Camera;
	namespace MenuBlur {}
	using namespace Patches::MenuBlur;
	namespace Input {}
	using namespace Patches::Input;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

namespace
{

}
//class c_gui_player_select_screen_widget__show_service_record_hook::__l11::<lambda_1>
//{
//public:
//	void operator()(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &) const;
//	<lambda_1>(c_gui_player_select_screen_widget__show_service_record_hook::__l11::<lambda_1> &);
//	<lambda_1>(c_gui_player_select_screen_widget__show_service_record_hook::__l11::<lambda_1> const &);
//	<lambda_1>(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
//private:
//	std::basic_string<char,std::char_traits<char>,std::allocator<char> > profileUrl; // 0x0
//public:
//	c_gui_player_select_screen_widget__show_service_record_hook::__l11::<lambda_1> &operator=(c_gui_player_select_screen_widget__show_service_record_hook::__l11::<lambda_1> const &);
//	~<lambda_1>(); /* compiler_generated() */
//};
//static_assert(sizeof(c_gui_player_select_screen_widget__show_service_record_hook::__l11::<lambda_1>) == 28, "Invalid c_gui_player_select_screen_widget__show_service_record_hook::__l11::<lambda_1> size");

//class c_main_menu_screen_widget_handle_list_item_chosen_hook::__l25::<lambda_1>
//{
//public:
//	void operator()(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &) const;
//};
//static_assert(sizeof(c_main_menu_screen_widget_handle_list_item_chosen_hook::__l25::<lambda_1>) == 1, "Invalid c_main_menu_screen_widget_handle_list_item_chosen_hook::__l25::<lambda_1> size");

namespace
{
	// c_player_select_actions_datasource is defined in hades/recovered_types.h, which the synthesised
}
// templates in hades/recovered_templates.h inherit from.

//class OnUiInputUpdated::__l19::<lambda_1>
//{
//public:
//	void operator()(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &) const;
//};
//static_assert(sizeof(OnUiInputUpdated::__l19::<lambda_1>) == 1, "Invalid OnUiInputUpdated::__l19::<lambda_1> size");

//struct UpdateH3HUDImpl::__l2::ControlGlobalsAction
//{
//	unsigned short Type; // 0x0
//	unsigned short Flags; // 0x2
//	unsigned __int32 ObjectIndex; // 0x4
//};
//static_assert(sizeof(UpdateH3HUDImpl::__l2::ControlGlobalsAction) == 8, "Invalid UpdateH3HUDImpl::__l2::ControlGlobalsAction size");

//class _Closure_wrapper_569e7c00_1 :
//	public user_interface_text_parser_initialize_hook::__l2::<lambda_1>
//{
//private:
//	typedef bool (*<lambda_typedef_cdecl>)(void *, wchar_t *, long);
//public:
//	bool (*operator bool (__cdecl *)(void *,wchar_t *,long)() const)(void *, wchar_t *, long);
//private:
//	typedef bool (*<lambda_typedef_stdcall>)(void *, wchar_t *, long);
//public:
//	bool (*operator bool (__stdcall *)(void *,wchar_t *,long)() const)(void *, wchar_t *, long);
//private:
//	typedef bool (*<lambda_typedef_fastcall>)(void *, wchar_t *, long);
//public:
//	bool (*operator bool (__fastcall *)(void *,wchar_t *,long)() const)(void *, wchar_t *, long);
//private:
//	typedef bool (*<lambda_typedef_vectorcall>)(void *, wchar_t *, long);
//public:
//	bool (*operator bool (__vectorcall *)(void *,wchar_t *,long)() const)(void *, wchar_t *, long);
//};
//static_assert(sizeof(_Closure_wrapper_569e7c00_1) == 1, "Invalid _Closure_wrapper_569e7c00_1 size");

//class user_interface_text_parser_initialize_hook::__l2::<lambda_1>
//{
//public:
//	bool operator()(void *, wchar_t *, long) const;
//};
//static_assert(sizeof(user_interface_text_parser_initialize_hook::__l2::<lambda_1>) == 1, "Invalid user_interface_text_parser_initialize_hook::__l2::<lambda_1> size");

//class _Closure_wrapper_569e7c00_2 :
//	public user_interface_text_parser_initialize_hook::__l2::<lambda_2>
//{
//private:
//	typedef bool (*<lambda_typedef_cdecl>)(void *, wchar_t *, long);
//public:
//	bool (*operator bool (__cdecl *)(void *,wchar_t *,long)() const)(void *, wchar_t *, long);
//private:
//	typedef bool (*<lambda_typedef_stdcall>)(void *, wchar_t *, long);
//public:
//	bool (*operator bool (__stdcall *)(void *,wchar_t *,long)() const)(void *, wchar_t *, long);
//private:
//	typedef bool (*<lambda_typedef_fastcall>)(void *, wchar_t *, long);
//public:
//	bool (*operator bool (__fastcall *)(void *,wchar_t *,long)() const)(void *, wchar_t *, long);
//private:
//	typedef bool (*<lambda_typedef_vectorcall>)(void *, wchar_t *, long);
//public:
//	bool (*operator bool (__vectorcall *)(void *,wchar_t *,long)() const)(void *, wchar_t *, long);
//};
//static_assert(sizeof(_Closure_wrapper_569e7c00_2) == 1, "Invalid _Closure_wrapper_569e7c00_2 size");

//class user_interface_text_parser_initialize_hook::__l2::<lambda_2>
//{
//public:
//	bool operator()(void *, wchar_t *, long) const;
//};
//static_assert(sizeof(user_interface_text_parser_initialize_hook::__l2::<lambda_2>) == 1, "Invalid user_interface_text_parser_initialize_hook::__l2::<lambda_2> size");

//class _Closure_wrapper_569e7c00_3 :
//	public user_interface_text_parser_initialize_hook::__l2::<lambda_3>
//{
//private:
//	typedef bool (*<lambda_typedef_cdecl>)(void *, wchar_t *, long);
//public:
//	bool (*operator bool (__cdecl *)(void *,wchar_t *,long)() const)(void *, wchar_t *, long);
//private:
//	typedef bool (*<lambda_typedef_stdcall>)(void *, wchar_t *, long);
//public:
//	bool (*operator bool (__stdcall *)(void *,wchar_t *,long)() const)(void *, wchar_t *, long);
//private:
//	typedef bool (*<lambda_typedef_fastcall>)(void *, wchar_t *, long);
//public:
//	bool (*operator bool (__fastcall *)(void *,wchar_t *,long)() const)(void *, wchar_t *, long);
//private:
//	typedef bool (*<lambda_typedef_vectorcall>)(void *, wchar_t *, long);
//public:
//	bool (*operator bool (__vectorcall *)(void *,wchar_t *,long)() const)(void *, wchar_t *, long);
//};
//static_assert(sizeof(_Closure_wrapper_569e7c00_3) == 1, "Invalid _Closure_wrapper_569e7c00_3 size");

//class user_interface_text_parser_initialize_hook::__l2::<lambda_3>
//{
//public:
//	bool operator()(void *, wchar_t *, long) const;
//};
//static_assert(sizeof(user_interface_text_parser_initialize_hook::__l2::<lambda_3>) == 1, "Invalid user_interface_text_parser_initialize_hook::__l2::<lambda_3> size");

//class c_gui_screen_campaign_select_skulls__handle_controller_input_message_hook::__l2::<lambda_1>
//{
//public:
//	__int32 operator()(c_gui_list_widget *, long) const;
//};
//static_assert(sizeof(c_gui_screen_campaign_select_skulls__handle_controller_input_message_hook::__l2::<lambda_1>) == 1, "Invalid c_gui_screen_campaign_select_skulls__handle_controller_input_message_hook::__l2::<lambda_1> size");

/* ---------- prototypes */

namespace Patches
{
	namespace Ui
	{
		extern void ApplyAfterTagsLoaded();
		extern void ApplyAll();
		extern void *ShowDialog(unsigned long const p_DialogID, __int32 const p_Arg1, __int32 const p_Flags, unsigned long const p_ParentID);
		extern void OnCreateWindow(std::function<void __cdecl(HWND__ *)> callback);
		extern void TogglePTTSound(bool enabled);
		extern void ToggleSpeakingPlayerName(std::basic_string<char,std::char_traits<char>,std::allocator<char> > name, bool speaking);
		extern void ApplyUIResolution();
		extern void ShowLanBrowser();
	}
}

/* ---------- globals */

namespace Patches
{
	namespace Ui
	{
		extern bool HasAttractBinks; // 0x12467422
		extern bool isPttSoundPlaying; // 0x12467423
		extern std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > speakingPlayers; // 0x12467478
		extern char16_t chud_talking_player_name[32]; // 0x12467428
		extern bool enableCustomHUDColors; // 0x12467420
		extern bool enableAllyBlueWaypointsFix; // 0x12467421
		extern __int32 customPrimaryHUDColor; // 0x11354C4C
		extern __int32 customSecondaryHUDColor; // 0x12467424
	}
}

/* ---------- private variables */

namespace
{
	extern bool (*c_gui_screen_pregame_lobby_handle_item_chosen)(void *, void *, unsigned long, c_gui_list_item_widget *, c_gui_data *); // 0x12467488
	extern bool (*IsMapLoading)(); // 0x11354C84
	extern bool tagsInitiallyLoaded; // 0x1246748C
	extern __int32 localDesiredTeam; // 0x11354C88
	extern std::vector<std::function<void __cdecl(HWND__ *)>,std::allocator<std::function<void __cdecl(HWND__ *)> > > createWindowCallbacks; // 0x12467468
}
/* ---------- public code */

namespace Patches
{
	namespace Ui
	{
		_extern void _sub_10AD7260();
		void ApplyAfterTagsLoaded() // 0x10AD7260
		{
			mangled_x86(MANGLED_TODO, "?ApplyAfterTagsLoaded@Ui@Patches@@YAXXZ");
			// procedure flags: nofpo
			// __int32 (*SSL_SetMusicVolume)(__int32, bool);
			// s_scenario *scnr;
			// unsigned __int32 SoundSystemInitialized;
			// function call : __int32 (*)(__int32, bool)
			// function call : __int32 (*)(__int32, bool)
			todo("implement");
			_sub_10AD7260();
		}

		_extern void _sub_10AD7390();
		void ApplyAll() // 0x10AD7390
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Ui@Patches@@YAXXZ");
			// procedure flags: nofpo
			// __int32 achievementstringidaddress;
			{
				// __int32 i;
			}
			todo("implement");
			_sub_10AD7390();
		}

		_extern void *_sub_10ADD220(unsigned long const, __int32 const, __int32 const, unsigned long const);
		void *ShowDialog(unsigned long const p_DialogID, __int32 const p_Arg1, __int32 const p_Flags, unsigned long const p_ParentID) // 0x10ADD220
		{
			mangled_x86(MANGLED_TODO, "?ShowDialog@Ui@Patches@@YAPAXKHHK@Z");
			// unsigned long const p_ParentID;
			// void *s_UIData;
			// function call : void *(*const)(__int32)
			// function call : void *(*const)(void *, unsigned long, __int32, __int32, unsigned long)
			// function call : __int32 (*const)(void *)
			todo("implement");
			void * __result = _sub_10ADD220(p_DialogID, p_Arg1, p_Flags, p_ParentID);
			return __result;
		}

		_extern void _sub_10ADCCD0(std::function<void __cdecl(HWND__ *)>);
		void OnCreateWindow(std::function<void __cdecl(HWND__ *)> callback) // 0x10ADCCD0
		{
			mangled_x86(MANGLED_TODO, "?OnCreateWindow@Ui@Patches@@YAXV?$function@$$A6AXPAUHWND__@@@Z@std@@@Z");
			// std::function<void __cdecl(HWND__ *)> callback;
			todo("implement");
			_sub_10ADCCD0(callback);
		}

		_extern void _sub_10ADD3E0(bool);
		void TogglePTTSound(bool enabled) // 0x10ADD3E0
		{
			mangled_x86(MANGLED_TODO, "?TogglePTTSound@Ui@Patches@@YAX_N@Z");
			// bool enabled;
			// static void (*Sound_LoopingSound_Stop)(unsigned __int32, __int32); // 0x11354C8C
			// static void (*Sound_LoopingSound_Start)(unsigned __int32, __int32, __int32, __int32, char); // 0x11354C90
			// s_multiplayer_globals_definition *mulg;
			// long pttLsndIndex;
			// function call : bool (*)()
			// function call : void *(*const)(unsigned long, long)
			// function call : void (*)(unsigned __int32, __int32, __int32, __int32, char)
			// function call : void (*)(unsigned __int32, __int32)
			todo("implement");
			_sub_10ADD3E0(enabled);
		}

		_extern void _sub_10ADD620(std::string, bool);
		void ToggleSpeakingPlayerName(std::basic_string<char,std::char_traits<char>,std::allocator<char> > name, bool speaking) // 0x10ADD620
		{
			mangled_x86(MANGLED_TODO, "?ToggleSpeakingPlayerName@Ui@Patches@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
			// static ...; // 0x10ADD884
			// static ...; // 0x10ADD87C
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > name;
			// bool speaking;
			{
				// unsigned __int32 i;
			}
			{
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > hud_name;
				{
					// unsigned __int32 i;
				}
			}
			todo("implement");
			_sub_10ADD620(name, speaking);
		}

		_extern void _sub_10ADB800();
		void ApplyUIResolution() // 0x10ADB800
		{
			mangled_x86(MANGLED_TODO, "?ApplyUIResolution@Ui@Patches@@YAXXZ");
			// procedure flags: nofpo
			// long *game_resolution;
			// long *ui_resolution;
			// c_gui_screen_manager *screen_manager;
			// c_gui_screen_widget *active_screen;
			{
				// c_gui_screen_widget *screen_below;
			}
			// function call : void ()
			// function call : void ()
			todo("implement");
			_sub_10ADB800();
		}

		_extern void _sub_10ADD2E0();
		void ShowLanBrowser() // 0x10ADD2E0
		{
			mangled_x86(MANGLED_TODO, "?ShowLanBrowser@Ui@Patches@@YAXXZ");
			// procedure flags: nofpo
			// void *dialog;
			// void *(*UI_Alloc)(__int32);
			// void *(*c_load_game_browser_screen_message)(void *, __int32, __int32, __int32, __int32, __int32, __int32, __int32);
			// void (*UI_Dialog_QueueLoad)(void *);
			// function call : void *(*)(__int32)
			// function call : void *(*)(void *, __int32, __int32, __int32, __int32, __int32, __int32, __int32)
			// function call : void (*)(void *)
			todo("implement");
			_sub_10ADD2E0();
		}
	}
}

/* ---------- private code */

//_extern bool _sub_10AD2960(void *, wchar_t *, long);
//_inline bool _Closure_wrapper_569e7c00_1::<lambda_invoker_cdecl>(void *__p1, wchar_t *__p2, long __p3) // 0x10AD2960
//{
//	// _Closure_wrapper_569e7c00_1::<lambda_invoker_cdecl>
//	// long __p3;
//	todo("implement");
//	bool __result = _sub_10AD2960(__p1, __p2, __p3);
//	return __result;
//}

//extern bool (*_sub_10AD63B0(_Closure_wrapper_569e7c00_1 const *const) const)(void *, wchar_t *, long);
//{
//	// _Closure_wrapper_569e7c00_1 const *const this;
//	todo("implement");
//	auto __result = _sub_10AD63B0(this);
//	return __result;
//}

//_extern bool _sub_10AD29B0(void *, wchar_t *, long);
//_inline bool _Closure_wrapper_569e7c00_2::<lambda_invoker_cdecl>(void *__p1, wchar_t *__p2, long __p3) // 0x10AD29B0
//{
//	// _Closure_wrapper_569e7c00_2::<lambda_invoker_cdecl>
//	// long __p3;
//	todo("implement");
//	bool __result = _sub_10AD29B0(__p1, __p2, __p3);
//	return __result;
//}

//extern bool (*_sub_10AD63E0(_Closure_wrapper_569e7c00_2 const *const) const)(void *, wchar_t *, long);
//{
//	// _Closure_wrapper_569e7c00_2 const *const this;
//	todo("implement");
//	auto __result = _sub_10AD63E0(this);
//	return __result;
//}

//_extern bool _sub_10AD2A00(void *, wchar_t *, long);
//_inline bool _Closure_wrapper_569e7c00_3::<lambda_invoker_cdecl>(void *__p1, wchar_t *__p2, long __p3) // 0x10AD2A00
//{
//	// _Closure_wrapper_569e7c00_3::<lambda_invoker_cdecl>
//	// long __p3;
//	todo("implement");
//	bool __result = _sub_10AD2A00(__p1, __p2, __p3);
//	return __result;
//}

//extern bool (*_sub_10AD6410(_Closure_wrapper_569e7c00_3 const *const) const)(void *, wchar_t *, long);
//{
//	// _Closure_wrapper_569e7c00_3 const *const this;
//	todo("implement");
//	auto __result = _sub_10AD6410(this);
//	return __result;
//}
