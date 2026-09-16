/* ---------- headers */

#include "Patches/Ui.hpp"
#include "hades/hades.h"
#include "Patches/Input.hpp"
#include <detours.h>

#include "Blam/ai/actor.hpp"
#include "Blam/bitmaps/bitmap_definition.hpp"
#include "Blam/BlamInput.hpp"
#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/Cache/StringIdCache.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/multiplayer_definitions.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/input/input.hpp"
#include "Blam/interface/chud/chud.hpp"
#include "Blam/interface/chud/chud_globals.hpp"
#include "Blam/interface/controller_input_message.hpp"
#include "Blam/interface/gui/gui_bitmap_widget.hpp"
#include "Blam/interface/gui/gui_list_item_widget.hpp"
#include "Blam/interface/gui/gui_list_widget.hpp"
#include "Blam/interface/gui/gui_location_manager.hpp"
#include "Blam/interface/gui/gui_screen_manager.hpp"
#include "Blam/interface/gui/gui_screen_widget.hpp"
#include "Blam/interface/gui/gui_widget.hpp"
#include "Blam/interface/gui_selected_items_map.hpp"
#include "Blam/interface/user_interface.hpp"
#include "Blam/interface/user_interface_definitions.hpp"
#include "Blam/interface/user_interface_sound.hpp"
#include "Blam/items/equipment.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/items/weapon_definitions.hpp"
#include "Blam/main/levels.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameters.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/networking/session/network_session_parameters_custom.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
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
#include "Blam/text/text_group.hpp"
#include "Blam/units/units.hpp"
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
#include "Modules/ModuleInput.hpp"
#include "Modules/ModuleSettings.hpp"
#include "Modules/ModuleTweaks.hpp"
#include "Modules/ModuleVoIP.hpp"
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

class CustomBitmapManager;
class _Closure_wrapper_569e7c00_1;
class _Closure_wrapper_569e7c00_2;
class _Closure_wrapper_569e7c00_3;
class c_gui_bitmap_widget;
class c_gui_data;
class c_gui_list_item_widget;
class c_gui_list_widget;
class c_gui_map_category_datasource;
class c_gui_screen_manager;
class c_gui_screen_widget;
class c_gui_widget;
class c_network_session;
class c_network_session_parameter_base;
class c_network_session_parameters;
struct begin;
struct c_chud_global_scripting;
struct c_chud_update_user_data;
struct c_controller_input_message;
struct c_draw_string;
struct c_gui_custom_bitmap_widget;
struct c_gui_location_manager;
struct c_rasterizer_texture_ref;
struct c_user_interface_main_menu_music;
struct end;
struct gui_real_rectangle2d;
struct lambda_1;
struct lambda_2;
struct lambda_3;
struct lambda_invoker_cdecl;
struct lambda_typedef_cdecl;
struct lambda_typedef_fastcall;
struct lambda_typedef_stdcall;
struct lambda_typedef_vectorcall;
struct real_argb_color;
struct real_point2d;
struct real_rectangle2d;
struct s_bitmap_definition;
struct s_chud_globals_definition;
struct s_chud_managed_navpoint;
struct s_chud_navpoint;
struct s_equipment_data;
struct s_equipment_definition;
struct s_game_globals;
struct s_game_globals_player_character_type;
struct s_game_globals_player_representation;
struct s_gui_alert_description;
struct s_gui_widget_render_data;
struct s_level_datum;
struct s_multilingual_unicode_string_list_group_header;
struct s_multiplayer_globals_definition;
struct s_network_session_player;
struct s_object_data;
struct s_player_configuration;
struct s_player_datum;
struct s_scenario;
struct s_unit_data;
struct s_user_interface_shared_globals;
struct s_weapon_definition;
struct short_rectangle2d;
namespace Blam
{
	namespace Input
	{
		enum GameAction : unsigned char;
		struct BindingsTable;
	}
}
namespace Blam
{
	namespace Network
	{
		struct PlayerSession;
		struct Session;
		struct SessionMembership;
	}
}
namespace Modules
{
	class ModuleSettings;
	class ModuleTweaks;
	class ModuleVoIP;
}
namespace Player
{
	namespace ServiceRecord
	{
		struct ServiceRecord;
	}
}
namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer
		{
			struct SDialogShowParams;
		}
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
}

namespace Blam
{
	namespace Input {}
	using namespace Blam::Input;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{

}
using namespace hades_file_local;
//class c_gui_player_select_screen_widget__show_service_record_hook::__l11::<lambda_1>
//{
//public:
//	void operator()(std::string const &) const;
//	<lambda_1>(c_gui_player_select_screen_widget__show_service_record_hook::__l11::<lambda_1> &);
//	<lambda_1>(c_gui_player_select_screen_widget__show_service_record_hook::__l11::<lambda_1> const &);
//	<lambda_1>(std::string const &);
//private:
//	std::string profileUrl; // 0x0
//public:
//	c_gui_player_select_screen_widget__show_service_record_hook::__l11::<lambda_1> &operator=(c_gui_player_select_screen_widget__show_service_record_hook::__l11::<lambda_1> const &);
//	~<lambda_1>(); /* compiler_generated() */
//};
//static_assert(sizeof(c_gui_player_select_screen_widget__show_service_record_hook::__l11::<lambda_1>) == 28, "Invalid c_gui_player_select_screen_widget__show_service_record_hook::__l11::<lambda_1> size");

//class c_main_menu_screen_widget_handle_list_item_chosen_hook::__l25::<lambda_1>
//{
//public:
//	void operator()(std::string const &) const;
//};
//static_assert(sizeof(c_main_menu_screen_widget_handle_list_item_chosen_hook::__l25::<lambda_1>) == 1, "Invalid c_main_menu_screen_widget_handle_list_item_chosen_hook::__l25::<lambda_1> size");

namespace hades_file_local
{
	// c_player_select_actions_datasource is defined in hades/recovered_types.h, which the synthesised
}
using namespace hades_file_local;
// templates in hades/recovered_templates.h inherit from.

//class OnUiInputUpdated::__l19::<lambda_1>
//{
//public:
//	void operator()(std::string const &) const;
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

#include "Modules/ModuleCamera.hpp"  // hades: added for 0x10AE8F50

#include "Modules/ModuleGame.hpp"  // hades: added for 0x10AE8270
namespace Patches { namespace MenuBlur { extern void RenderUIPostProcess(); } }  // hades: added for 0x10AE8270

#include "Player/PlayerInfo.hpp"  // hades: added for 0x10ADC1D0

namespace Player::PlayerNetworkUtil { long get_session_player_index_from_player_datum_index(long player_datum_index); }  // hades: added for 0X10AE7C40

namespace Patches
{
	namespace Ui
	{
		extern void ApplyAfterTagsLoaded();
		extern void ApplyAll();
		extern void *ShowDialog(unsigned long const p_DialogID, __int32 const p_Arg1, __int32 const p_Flags, unsigned long const p_ParentID);
		extern void OnCreateWindow(std::function<void __cdecl(HWND__ *)> callback);
		extern void TogglePTTSound(bool enabled);
		extern void ToggleSpeakingPlayerName(std::string name, bool speaking);
		extern void ApplyUIResolution();
		extern void ShowLanBrowser();
	}
}

void __fastcall c_gui_map_category_datasource__ctor_hook(c_gui_map_category_datasource *thisptr, void *__formal, wchar_t const *recent_maps_item_title, wchar_t const *recent_maps_item_description, wchar_t const *file_share_item_title, wchar_t const *file_share_item_description);
void __fastcall c_gui_player_select_screen_widget__set_mute_hook(void *thisPtr, void *unused, bool muted);
bool isValidUrl(std::string const &url);
void __fastcall c_gui_player_select_screen_widget__show_service_record_hook(void *thisPtr, void *unused, bool muted);
bool UserInterfaceSquadSetMap_hook(__int32 a1, __int32 a2, char a3, __int32 a4, __int32 a5, __int32 a6);
bool AttractShouldStartHook();
__int32 GetPlayerRankIndex(__int32 networkPlayerIndex);
__int32 GetPlayerSkillIndex(__int32 networkPlayerIndex);
std::wstring GetRankName(__int32 rankIndex);
std::wstring GetRankGradeName(__int32 rankIndex);
void __fastcall c_gui_location_manager__change_location_hook(c_gui_location_manager *thisptr, void *__formal, unsigned long screen_name);
bool __fastcall c_gui_screen_pregame_lobby__handle_controller_input_message_fallback_hook(c_gui_screen_widget *thisptr, void *__formal, c_controller_input_message *message);
bool __fastcall c_start_menu_settings_handle_list_item_chosen_hook(void *thisptr, void *unused, void *message, unsigned long list_name, c_gui_list_item_widget const *list_item, c_gui_data *data);
bool __fastcall c_main_menu_screen_widget_handle_list_item_chosen_hook(void *thisptr, void *unused, void *message, unsigned long list_name, c_gui_list_item_widget const *list_item, c_gui_data *data);
void ui_background_set_hook(__int32 index);
void user_interface_networking_notify_booted_from_session_hook(__int32 a1, e_network_session_boot_reason reason);
void __fastcall c_start_menu_screen_widget__update_render_state_hook(c_gui_screen_widget *thisptr, void *__formal, unsigned long milliseconds);
void __fastcall c_start_menu_screen_widget__post_initialize_hook(c_gui_screen_widget *thisptr, void *unused);
void c_gui_spartan_rank_widget__update_sub_hook(c_gui_widget *widget, long in_rank, long in_grade);
void __fastcall c_spartan_rank_widget__update_render_state_hook(c_gui_screen_widget *thisptr, void *unused, unsigned long milliseconds);
void c_player_select_actions_datasource__add_action(c_player_select_actions_datasource *result, __int32 stringid, bool enabled);
bool c_gui_screen_pregame_lobby__squad_party_leader_hook(void *thisptr, wchar_t *buffer, unsigned __int32 length);
void __fastcall c_player_select_actions_datasource__initialize_hook(c_player_select_actions_datasource *thisptr);
void __fastcall c_player_select_screen_widget__update_render_state_hook(c_gui_screen_widget *thisptr, void *unused, unsigned long milliseconds);
void gui_widget_set_visible_safe(c_gui_widget *item, bool visibility);
void __fastcall c_player_select_screen_widget__update_hook(c_gui_screen_widget *thisptr, void *unused, unsigned long milliseconds);
void __fastcall c_gui_roster_list_widget_update_hook(c_gui_screen_widget *thisptr, void *unused, unsigned long milliseconds);
void __fastcall c_gui_custom_bitmap_widget__set_map_image_hook(c_gui_custom_bitmap_widget *thisptr, long unused, e_image_content_type map_image, __int32 map_id, bool a4);
void __fastcall c_gui_custom_bitmap_widget__update_hook(c_gui_custom_bitmap_widget *thisptr, void *__formal, unsigned long time);
void __fastcall c_gui_custom_bitmap_widget__reset_hook(c_gui_custom_bitmap_widget *thisptr);
void ResolutionChangeHook();
__int32 UI_ListItem_GetIndex(void *item);
bool UI_OrderedDataSource_Get(void *data, __int32 index, __int32 key, void *result);
__int32 __fastcall c_gui_roster_list_widget__start_team_change_hook(void *thisPtr, __int32 unused, __int32 a2, __int32 teamIndex, __int32 a4);
void OnUiInputUpdated();
void __fastcall c_gui_roster_list_widget__update_render_state(c_gui_screen_widget *thisPtr, void *__formal, unsigned long milliseconds);
HWND__ *CreateGameWindowHook();
bool UpdateH3HUDImpl(__int32 playerMappingIndex);
void UI_UpdateH3HUDHook(__int32 playerMappingIndex);
bool GetBoundMouseButtonName(__int32 code, wchar_t *buff);
void GetActionButtonNameHook();
void __fastcall c_ui_view_draw_hook(void *thisptr, void *unused);
__int32 GetPlayerTypeFlagsValues();
__int32 GetMultiplayerFlagsValues();
__int32 GetMultiplayerEventsFlagsValues();
__int32 GetUnitGeneralFlagsValues();
__int32 GameStateFlagsValues();
unsigned long __fastcall GetGlobalDynamicColorHook(s_chud_globals_definition *thisptr, void *unused, long character_type, long color_index);
void GetWeaponOutlineColorHook(long index, real_argb_color *out_color);
bool __fastcall c_gui_game_variant_category_datasource_init(c_gui_generic_category_datasource<11> *thisptr, void *unused, __int32 datasource);
void __stdcall OnLobbySwitchNetworkMode();
void c_gui_screen_pregame_lobby_switch_network_hook();
void __fastcall c_gui_alert_manager__show(void *thisptr, void *unused, unsigned __int32 name, __int32 a3, wchar_t *customMessage, __int32 profileIndex, bool a6, __int32 a7);
void __fastcall c_hud_camera_view__render_outlines_hook(void *thisptr, void *unused, __int32 localProfileIndex, __int32 playerMappingIndex, void *a3);
wchar_t *chud_talking_player_name_hook(wchar_t *buffer);
bool PlayerMarkerIsDisabled(unsigned __int32 playerIndex);
void __fastcall chud_add_player_marker_hook(void *thisptr, void *unused, unsigned char *data_);
void __fastcall c_start_menu_pane_screen_widget__handle_spinner_chosen_hook(void *thisptr, void *unused, unsigned char *widget);
void __fastcall UI_GameVariantSavePromptFix(void *thisptr, void *unused, __int32 a2);
float get_player_vertical_crosshair_location();
void observer_validate_camera_command__first_person_hook(unsigned char *c_observer_command);
void observer_validate_camera_command__third_person_hook(unsigned char *c_observer_command);
__int32 user_interface_squad_get_countdown_timer_hook();
void __fastcall c_chud_update_user_data__ctor_hook(c_chud_update_user_data *thisptr, void *__formal, long user_index, long unit_index, bool a4);
void __fastcall c_user_interface_main_menu_music_update_desired_state(c_user_interface_main_menu_music *thisptr, void *unused);
void user_interface_text_parser_initialize_hook();
bool __fastcall c_gui_screen_pregame_lobby_handle_item_chosen_hook(void *thisptr, void *unused, void *message, unsigned long source_name, c_gui_list_item_widget *list_widget, c_gui_data *data);
bool __fastcall c_gui_screen_campaign_select_skulls__handle_controller_input_message_hook(c_gui_screen_widget *thisptr, void *unused, c_controller_input_message *message);
void __fastcall c_gui_screen_game_options__update_hook(c_gui_screen_widget *thisptr, void *__formal, unsigned long milliseconds);
void __fastcall c_gui_widget__get_unprojected_bounds_hook(c_gui_widget *thisptr, void *unused, gui_real_rectangle2d *unprojected_bounds, bool offset, bool scale, bool rotate);
void c_rasterizer__get_display_pixel_bounds_hook(short_rectangle2d *display_pixel_bounds);
long interface_get_closest_authored_ui_aspect_ratio_hook();
real_point2d interface_get_authoring_to_target_dimensions_scaling_hook();
void __fastcall c_gui_custom_bitmap_widget__assemble_render_data_hook(c_gui_custom_bitmap_widget *thisptr, void *unused, s_gui_widget_render_data *render_data, real_rectangle2d *bounds, long controller_index, bool offset, bool scale, bool rotate);
bool __fastcall c_draw_string__draw_internal_hook(c_draw_string *thisptr, void *unused, void *cache, char const *utf32_text);
void __fastcall c_draw_string__set_bounds_hook(c_draw_string *thisptr, void *unused, real_rectangle2d *upper_x, real_rectangle2d *upper_y);
bool user_interface_set_campaign_options_hook(long campaign_id, long map_id, short insertion_point_index, long a4, long a5, long a7);

/* ---------- globals */

extern bool (*const network_session_interface_get_squad_session)(c_network_session **); // 0x11248780

namespace Patches
{
	namespace Ui
	{
		extern bool HasAttractBinks; // 0x12467422
		extern bool isPttSoundPlaying; // 0x12467423
		extern std::vector<std::string> speakingPlayers; // 0x12467478
		extern char16_t chud_talking_player_name[32]; // 0x12467428
		extern bool enableCustomHUDColors; // 0x12467420
		extern bool enableAllyBlueWaypointsFix; // 0x12467421
		extern __int32 customPrimaryHUDColor; // 0x11354C4C
		extern __int32 customSecondaryHUDColor; // 0x12467424
	}
}

/* ---------- private variables */

namespace hades_file_local
{
	extern "C" bool (__thiscall *c_gui_screen_pregame_lobby_handle_item_chosen)(void *, void *, unsigned long, c_gui_list_item_widget *, c_gui_data *);  // 0x12467488
	extern bool (*IsMapLoading)(); // 0x11354C84
	extern bool tagsInitiallyLoaded; // 0x1246748C
	extern __int32 localDesiredTeam; // 0x11354C88
	extern std::vector<std::function<void __cdecl(HWND__ *)> > createWindowCallbacks; // 0x12467468
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Ui
	{
		void ApplyAfterTagsLoaded() // 0x10AD7260
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAfterTagsLoaded@Ui@Patches@@YAXXZ");
			// procedure flags: nofpo
			// __int32 (*SSL_SetMusicVolume)(__int32, bool);
			// s_scenario *scnr;
			// unsigned __int32 SoundSystemInitialized;
			// function call : __int32 (*)(__int32, bool)
			// function call : __int32 (*)(__int32, bool)

			if (!tagsInitiallyLoaded)
			{
				tagsInitiallyLoaded = true;
			}

			void *sound_globals = *(void **)0x69AD06C;
			void (__stdcall *set_music_volume)(long, long) = (void (__stdcall *)(long, long))0x79B940;
			s_scenario *scenario = global_scenario_get();
			if (scenario && sound_globals)
			{
				if (scenario->type == _scenario_type_main_menu)
				{
					set_music_volume(*(long *)((unsigned char *)Modules::ModuleSettings::Instance().VarMainMenuMusicVolume + 0x7C) * 2, 1);
				}
				else
				{
					set_music_volume(*(long *)((unsigned char *)Modules::ModuleSettings::Instance().VarMusicVolume + 0x7C) * 2, 1);
				}
			}
		}

		_extern void _sub_10AD7390();
		void ApplyAll() // 0x10AD7390
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Ui@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x6A7547, user_interface_set_campaign_options_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch::NopFill(Pointer::Base(0x6E05F3), 2);
			Patch(0x6C34B0, { 0xB6 }).Apply();
			Patch(0x705B21, { 0xB6 }).Apply();
			Patch::NopFill(Pointer::Base(0x20D7F2), 2);
			Hook(0x6DFB73, c_gui_location_manager__change_location_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x6DFA37, { 0xEB }).Apply();
			Hook(0x721DCF, c_gui_screen_pregame_lobby__handle_controller_input_message_fallback_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch::NopFill(Pointer::Base(0x723D85), 23);
			Pointer::Base(0x723DA1).Write<unsigned char>(0x0);
			Pointer::Base(0x723DB8).Write<unsigned char>(0x1);
			Patch::NopFill(Pointer::Base(0x723DFF), 3);
			Pointer::Base(0x723E07).Write<unsigned char>(0x0);
			Pointer::Base(0x723E1C).Write<unsigned char>(0x0);
			Hook(0x621303, ResolutionChangeHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x6B735D, c_gui_widget__get_unprojected_bounds_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x6B95E4, c_gui_widget__get_unprojected_bounds_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x718C98, c_gui_widget__get_unprojected_bounds_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x61FAA0, c_rasterizer__get_display_pixel_bounds_hook).Apply();
			Hook(0x69F980, interface_get_closest_authored_ui_aspect_ratio_hook).Apply();
			Hook(0x69F960, interface_get_authoring_to_target_dimensions_scaling_hook).Apply();
			Hook(0x6C37B0, c_gui_custom_bitmap_widget__assemble_render_data_hook).Apply();
			Hook(0x25788A, c_draw_string__draw_internal_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x6BD6F3, c_draw_string__set_bounds_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x726100, c_gui_roster_list_widget__update_render_state).Apply();
			Hook(0x622057, CreateGameWindowHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x6866F2, { 0xEB }).Apply();
			Patch(0x29CBD0, { 0x31, 0xC0, 0xC3 }).Apply();
			Hook(0x6970BB, UI_UpdateH3HUDHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0xABD324).Write<unsigned int>(0xABD2F7);
			Pointer(0xABD388).Write<unsigned int>(0xABD300);
			Hook(0x6BC83F, GetActionButtonNameHook, static_cast<__int32>(HookFlags::IsJmpIfEqual)).Apply();
			Patch(0x6BC5D7, { 0x98, 0xDE, 0x44, 0x02, 0x01 }).Apply();
			Pointer(0x169FCE0).Write<unsigned int>(reinterpret_cast<unsigned int>(c_main_menu_screen_widget_handle_list_item_chosen_hook));
			Pointer(0x16A1C20).Write<unsigned int>(reinterpret_cast<unsigned int>(c_start_menu_settings_handle_list_item_chosen_hook));
			Pointer(0x16A0158).Write<unsigned int>(reinterpret_cast<unsigned int>(c_start_menu_pane_screen_widget__handle_spinner_chosen_hook));
			Pointer(0x169FFE8).Write<unsigned int>(reinterpret_cast<unsigned int>(c_start_menu_pane_screen_widget__handle_spinner_chosen_hook));
			Hook(0x2047BF, c_ui_view_draw_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x721D38, c_gui_roster_list_widget__start_team_change_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			::Patches::Input::RegisterDefaultInputHandler(OnUiInputUpdated);
			Hook(0x68F554, c_chud_update_user_data__ctor_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x6D5B20, GetGlobalDynamicColorHook).Apply();
			Hook(0x6C9FD0, GetWeaponOutlineColorHook).Apply();
			Hook(0x6CA981, chud_talking_player_name_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x68AA21, chud_add_player_marker_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x6C3DE0, c_gui_custom_bitmap_widget__set_map_image_hook).Apply();
			Hook(0x6C3D50, c_gui_custom_bitmap_widget__reset_hook).Apply();
			Pointer(0x169D394).Write<unsigned int>(reinterpret_cast<unsigned int>(c_gui_custom_bitmap_widget__update_hook));
			Pointer(0x16A7874).Write<unsigned int>(reinterpret_cast<unsigned int>(c_gui_roster_list_widget_update_hook));
			Pointer(0x16A48E4).Write<unsigned int>(reinterpret_cast<unsigned int>(c_player_select_screen_widget__update_hook));
			Pointer(0x16A48E8).Write<unsigned int>(reinterpret_cast<unsigned int>(c_player_select_screen_widget__update_render_state_hook));
			Pointer(0x169EC50).Write<unsigned int>(reinterpret_cast<unsigned int>(c_start_menu_screen_widget__post_initialize_hook));
			Pointer(0x169ECA8).Write<unsigned int>(reinterpret_cast<unsigned int>(c_start_menu_screen_widget__update_render_state_hook));
			Pointer(0x16A2FF0).Write<unsigned int>(reinterpret_cast<unsigned int>(c_spartan_rank_widget__update_render_state_hook));
			Hook(0x6FC130, c_gui_spartan_rank_widget__update_sub_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x6FC149, c_gui_spartan_rank_widget__update_sub_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0x169E510).Write<unsigned int>(reinterpret_cast<unsigned int>(c_gui_game_variant_category_datasource_init));
			Hook(0x721F03, c_gui_screen_pregame_lobby_switch_network_hook).Apply();
			Hook(0x6A8706, UI_GameVariantSavePromptFix, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x691FD0, c_gui_alert_manager__show).Apply();
			Hook(0x62D58D, c_hud_camera_view__render_outlines_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x1CE52D, { 0xEB }).Apply();
			unsigned int destination = 0x1769410;
			for (int i = 0; i < 0x2F; i++)
				Pointer(destination + i * 4).Write<int>(i + 0x600E7);
			Hook(0x25FC1B, observer_validate_camera_command__first_person_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x329E4C, observer_validate_camera_command__third_person_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x6D5884, c_user_interface_main_menu_music_update_desired_state, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x682AE0, user_interface_squad_get_countdown_timer_hook).Apply();
			Hook(0x684585, user_interface_text_parser_initialize_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch::NopFill(Pointer::Base(0x6FF00C), 13);
			Pointer(0x16A3668).Write(c_gui_screen_campaign_select_skulls__handle_controller_input_message_hook);
			Pointer(0x16A507C).Write(c_gui_screen_game_options__update_hook);
			HasAttractBinks = std::filesystem::exists("bink\\attract_1.bik")
				&& std::filesystem::exists("bink\\attract_2.bik")
				&& std::filesystem::exists("bink\\attract_3.bik");
			Hook(0x684FA1, AttractShouldStartHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x6A7570, UserInterfaceSquadSetMap_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x709BB0, c_gui_player_select_screen_widget__set_mute_hook).Apply();
			Hook(0x70A060, c_gui_player_select_screen_widget__show_service_record_hook).Apply();
			Hook(0x70A440, c_player_select_actions_datasource__initialize_hook).Apply();
			Hook(0x722930, c_gui_screen_pregame_lobby__squad_party_leader_hook).Apply();
			Hook(0x5ECB70, ui_background_set_hook).Apply();
			Hook(0x67F580, user_interface_networking_notify_booted_from_session_hook).Apply();
			Patch(0x70DA94, { 0x90, 0xE9 }).Apply();
			Patch(0x71681C, { 0x90, 0x90 }).Apply();
			Hook(0x704694, c_gui_map_category_datasource__ctor_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0xB04658).Write<unsigned int>(0xF800);
			DetourTransactionBegin();
			c_gui_screen_pregame_lobby_handle_item_chosen = reinterpret_cast<decltype(c_gui_screen_pregame_lobby_handle_item_chosen)>(0xB21EA0);
			DetourAttach(&reinterpret_cast<PVOID &>(c_gui_screen_pregame_lobby_handle_item_chosen), reinterpret_cast<PVOID>(c_gui_screen_pregame_lobby_handle_item_chosen_hook));
			DetourTransactionCommit();
		}

		void *ShowDialog(unsigned long const p_DialogID, __int32 const p_Arg1, __int32 const p_Flags, unsigned long const p_ParentID) // 0x10ADD220
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ShowDialog@Ui@Patches@@YAPAXKHHK@Z");
			// unsigned long const p_ParentID;
			// void *s_UIData;
			// function call : void *(*const)(__int32)
			// function call : void *(*const)(void *, unsigned long, __int32, __int32, unsigned long)
			// function call : __int32 (*const)(void *)

			void *s_UIData = ((void *(__cdecl *)(int))0xab4ed0)(64);
			if (!s_UIData)
			{
				return nullptr;
			}
			((void (__thiscall *)(void *, unsigned long, __int32, __int32, unsigned long))0xa92780)(s_UIData, p_DialogID, p_Arg1, p_Flags, p_ParentID);
			((void (__cdecl *)(void *))0xa93450)(s_UIData);
			return s_UIData;
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
		void ToggleSpeakingPlayerName(std::string name, bool speaking) // 0x10ADD620
		{
			mangled_x86(MANGLED_TODO, "?ToggleSpeakingPlayerName@Ui@Patches@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
			// static ...; // 0x10ADD884
			// static ...; // 0x10ADD87C
			// std::string name;
			// bool speaking;
			{
				// unsigned __int32 i;
			}
			{
				// std::string hud_name;
				{
					// unsigned __int32 i;
				}
			}
			todo("implement");
			_sub_10ADD620(name, speaking);
		}

		void ApplyUIResolution() // 0x10ADB800
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyUIResolution@Ui@Patches@@YAXXZ");
			// procedure flags: nofpo
			// long *game_resolution;
			// long *ui_resolution;
			// c_gui_screen_manager *screen_manager;
			// c_gui_screen_widget *active_screen;
				// c_gui_screen_widget *screen_below;
			// function call : void ()
			// function call : void ()

			long *game_resolution = (long *)0x19106C0;
			long *ui_resolution = (long *)0x19106C8;

			ui_resolution[0] = game_resolution[0];
			ui_resolution[1] = game_resolution[1];

			auto screen_manager = c_gui_screen_manager::get();
			auto active_screen = screen_manager->get_topmost_screen();
			if (active_screen)
			{
				auto screen_below = screen_manager->get_screen_below(active_screen);
				while (screen_below)
				{
					screen_below->reload_next_frame();
					screen_below = screen_manager->get_screen_below(screen_below);
				}

				active_screen->reload_next_frame();
			}
		}

		void ShowLanBrowser() // 0x10ADD2E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ShowLanBrowser@Ui@Patches@@YAXXZ");
			// procedure flags: nofpo
			// void *dialog;
			// void *(*UI_Alloc)(__int32);
			// void *(*c_load_game_browser_screen_message)(void *, __int32, __int32, __int32, __int32, __int32, __int32, __int32);
			// void (*UI_Dialog_QueueLoad)(void *);
			// function call : void *(*)(__int32)
			// function call : void *(*)(void *, __int32, __int32, __int32, __int32, __int32, __int32, __int32)
			// function call : void (*)(void *)

			typedef void*(__cdecl * UI_AllocPtr)(int size);
			auto UI_Alloc = reinterpret_cast<UI_AllocPtr>(0xAB4ED0);
			typedef void*(__fastcall* c_load_game_browser_screen_messagePtr)(void *thisPtr, int unused, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
			auto c_load_game_browser_screen_message = reinterpret_cast<c_load_game_browser_screen_messagePtr>(0xADE0B0);
			typedef void(*UI_Dialog_QueueLoadPtr)(void *dialog);
			auto UI_Dialog_QueueLoad = reinterpret_cast<UI_Dialog_QueueLoadPtr>(0xA93450);

			auto dialog = UI_Alloc(0x44);
			if (!dialog)
				return;
			dialog = c_load_game_browser_screen_message(dialog, 0, 0x10355, 0, 4, 0x1000C, 0, 0);
			if (dialog)
				UI_Dialog_QueueLoad(dialog);
		}
	}
}

/* ---------- private code */

void __fastcall c_gui_map_category_datasource__ctor_hook(c_gui_map_category_datasource *thisptr, void *__formal, wchar_t const *recent_maps_item_title, wchar_t const *recent_maps_item_description, wchar_t const *file_share_item_title, wchar_t const *file_share_item_description) // 0x10AE1030
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_map_category_datasource__ctor_hook@@YIXPAVc_gui_map_category_datasource@@PAXPB_W222@Z");
	// `anonymous-namespace'::c_gui_map_category_datasource__ctor_hook
	// wchar_t const *file_share_item_description;

	new (thisptr) c_gui_map_category_datasource(recent_maps_item_title, recent_maps_item_description, file_share_item_title, file_share_item_description);
}

_extern void _sub_10AE10C0(void *, void *, bool);
void __fastcall c_gui_player_select_screen_widget__set_mute_hook(void *thisPtr, void *unused, bool muted) // 0x10AE10C0
{
	// `anonymous-namespace'::c_gui_player_select_screen_widget__set_mute_hook
	// static ...; // 0x10AE13C8
	// static ...; // 0x10AE13A4
	// static ...; // 0x10AE139C
	// void *thisPtr;
	// void *unused;
	// bool muted;
	// __int32 destination_player_index;
	// char *player_identifier_selected;
	// char (*const user_interface_session_get_player_index)(char *);
	// __int32 source_player_index;
	// char *player_identifier_local;
	{
		// Blam::Network::Session *session;
		{
			// Blam::Network::PlayerSession *player;
			// char uid[17];
			// Blam::Network::SessionMembership *membership;
			// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
			// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
		}
	}
	// function call : char (*const)(char *)
	// function call : char (*const)(char *)
	todo("implement");
	_sub_10AE10C0(thisPtr, unused, muted);
}

bool isValidUrl(std::string const &url) // 0x10AE8D10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?isValidUrl@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::isValidUrl
	// static ...; // 0x10AE8DE0
	// static ...; // 0x10AE8DD4
	// static ...; // 0x10AE8DCC
	// std::string const &url;
	// std::regex url_regex;

	std::regex url_regex("^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\\?([^#]*))?(#(.*))?", std::regex_constants::extended);

	return std::regex_match(url, url_regex);
}

_extern void _sub_10AE14B0(void *, void *, bool);
void __fastcall c_gui_player_select_screen_widget__show_service_record_hook(void *thisPtr, void *unused, bool muted) // 0x10AE14B0
{
	// `anonymous-namespace'::c_gui_player_select_screen_widget__show_service_record_hook
	// static ...; // 0x10AE1990
	// static ...; // 0x10AE198B
	// static ...; // 0x10AE1984
	// static ...; // 0x10AE1948
	// static ...; // 0x10AE1940
	// void *thisPtr;
	// void *unused;
	// bool muted;
	// s_network_session_player *player;
	// __int32 local_player_index;
	// __int32 player_index;
	// char *player_identifier_selected;
	// char (*const user_interface_session_get_player_index)(char *);
	// c_network_session *session;
	// char *player_identifier_local;
	// Player::ServiceRecord::ServiceRecord service_record;
	{
		// Web::Ui::ScreenLayer::SDialogShowParams params;
		// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
		// __int32 statsPlayerID;
		// std::string profileUrl;
		{
			// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &statsObject;
		}
	}
	// function call : char (*const)(char *)
	// function call : char (*const)(char *)
	// function call : bool (*const)(c_network_session **)
	todo("implement");
	_sub_10AE14B0(thisPtr, unused, muted);
}

bool UserInterfaceSquadSetMap_hook(__int32 a1, __int32 a2, char a3, __int32 a4, __int32 a5, __int32 a6) // 0x10ADDDE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UserInterfaceSquadSetMap_hook@@YA_NHHDHHH@Z");
	// `anonymous-namespace'::UserInterfaceSquadSetMap_hook
	// __int32 a2;
	// char a3;
	// __int32 a4;
	// __int32 a5;
	// __int32 a6;
	// long c;
	// bool (*const user_interface_squad_set_map)(__int32, __int32, char, __int32, __int32, __int32);
	// long m;
	// function call : bool (*const)(long *, long *)
	// function call : bool (*const)(__int32, __int32, char, __int32, __int32, __int32)

	long c;
	long m[2];

	if (((bool(*)(long *, long *))0xA817B0)(&c, m))
	{
		return false;
	}

	const auto user_interface_squad_set_map = (bool(*)(__int32, __int32, char, __int32, __int32, __int32))0xA83690;

	return user_interface_squad_set_map(a1, 3005, a3, a4, a5, a6);
}

bool AttractShouldStartHook() // 0x10ADB920
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?AttractShouldStartHook@@YA_NXZ");
	// `anonymous-namespace'::AttractShouldStartHook
	// procedure flags: nofpo
	// bool (*const Attract_Mode_should_Start)();
	// function call : bool (*const)()

	bool (*const AttractShouldStart)() = (bool (*const)())0xa992a0;

	if (HasAttractBinks)
	{
		return AttractShouldStart();
	}
	else
	{
		return false;
	}
}

__int32 GetPlayerRankIndex(__int32 networkPlayerIndex) // 0x10ADC160
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetPlayerRankIndex@@YAHH@Z");
	// `anonymous-namespace'::GetPlayerRankIndex
	// __int32 networkPlayerIndex;
	// __int32 rank;

	long rank;

	if (!::Player::CPlayersInfo::IsAvailable())
	{
		return 0;
	}

	rank = ::Player::CPlayersInfo::GetRank(networkPlayerIndex) + 1;
	return rank;
}

__int32 GetPlayerSkillIndex(__int32 networkPlayerIndex) // 0x10ADC1D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetPlayerSkillIndex@@YAHH@Z");
	// `anonymous-namespace'::GetPlayerSkillIndex
	// __int32 networkPlayerIndex;
	// __int32 skill;

	long skill;

	if (!::Player::CPlayersInfo::IsAvailable())
	{
		return 0;
	}

	skill = ::Player::CPlayersInfo::GetSkill(networkPlayerIndex);
	return skill;
}

std::wstring GetRankName(__int32 rankIndex) // 0x10ADC830
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetRankName@@YA?AV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@H@Z");
	// `anonymous-namespace'::GetRankName
	// static ...; // 0x10ADCA1F
	// static ...; // 0x10ADCA18
	// static ...; // 0x10ADCA00
	// static ...; // 0x10ADC9F8
	// __int32 rankIndex;
	// wchar_t buffer[1024];
	// unsigned long rankName;
	// bool (*const user_interface_global_string_get)(unsigned long, wchar_t (&)[1024]);
	// c_gui_data *(*const interface_get_global_datasource)(unsigned long);
	// c_gui_data *datasource;
	// function call : c_gui_data *(*const)(unsigned long)
	// function call : long ()
	// function call : bool (long, unsigned long, unsigned long *)
	// function call : bool (*const)(unsigned long, wchar_t (&)[1024])

	bool (*const user_interface_global_string_get)(unsigned long, wchar_t (&)[1024]) = (bool (*const)(unsigned long, wchar_t (&)[1024]))0xaa5970;
	c_gui_data *(*const interface_get_global_datasource)(unsigned long) = (c_gui_data *(*const)(unsigned long))0xa84200;
	c_gui_data *datasource = interface_get_global_datasource(66510);
	unsigned long rankName;
	wchar_t buffer[1024];

	if (!datasource || rankIndex < 0 || rankIndex >= datasource->get_current_item_count())
	{
		return L"";
	}

	if (!datasource->get_string_id_value(rankIndex, 682, &rankName))
	{
		return L"";
	}

	buffer[0] = 0;
	if (!user_interface_global_string_get(rankName, buffer))
	{
		return L"";
	}

	return buffer;
}

std::wstring GetRankGradeName(__int32 rankIndex) // 0x10ADC5B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetRankGradeName@@YA?AV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@H@Z");
	// `anonymous-namespace'::GetRankGradeName
	// static ...; // 0x10ADC79F
	// static ...; // 0x10ADC798
	// static ...; // 0x10ADC780
	// static ...; // 0x10ADC778
	// __int32 rankIndex;
	// unsigned long rankGradeName;
	// wchar_t buffer[1024];
	// bool (*const user_interface_global_string_get)(unsigned long, wchar_t (&)[1024]);
	// c_gui_data *(*const interface_get_global_datasource)(unsigned long);
	// c_gui_data *datasource;
	// function call : c_gui_data *(*const)(unsigned long)
	// function call : long ()
	// function call : bool (long, unsigned long, unsigned long *)
	// function call : bool (*const)(unsigned long, wchar_t (&)[1024])

	bool (*const user_interface_global_string_get)(unsigned long, wchar_t (&)[1024]) = (bool (*const)(unsigned long, wchar_t (&)[1024]))0xaa5970;
	c_gui_data *(*const interface_get_global_datasource)(unsigned long) = (c_gui_data *(*const)(unsigned long))0xa84200;
	c_gui_data *datasource = interface_get_global_datasource(66510);
	unsigned long rankGradeName;
	wchar_t buffer[1024];

	if (!datasource || rankIndex < 0 || rankIndex >= datasource->get_current_item_count())
	{
		return L"";
	}

	if (!datasource->get_string_id_value(rankIndex, 66511, &rankGradeName))
	{
		return L"";
	}

	buffer[0] = 0;
	if (!user_interface_global_string_get(rankGradeName, buffer))
	{
		return L"";
	}

	return buffer;
}

_extern void _sub_10AE0B90(c_gui_location_manager *, void *, unsigned long);
void __fastcall c_gui_location_manager__change_location_hook(c_gui_location_manager *thisptr, void *__formal, unsigned long screen_name) // 0x10AE0B90
{
	// `anonymous-namespace'::c_gui_location_manager__change_location_hook
	// static ...; // 0x10AE0F24
	// c_gui_location_manager *thisptr;
	// void *__formal;
	// unsigned long screen_name;
	// void (*const user_interface_messaging_post)(void *);
	// void (*const close_screens)(c_gui_screen_manager *, c_gui_screen_widget **, long);
	// long transition_type;
	// void *load_screen_message;
	// c_gui_screen_widget *screens[7];
	// c_gui_screen_manager *window_manager;
	// void (*const c_load_screen_message_ctor)(void *, unsigned long, long, long, unsigned long);
	// void *(*const user_interface_malloc)(unsigned __int32);
	// c_gui_screen_widget *screen_widget;
	// function call : c_gui_screen_widget *(*)()
	// function call : void (long, long)
	// function call : void (*const)(c_gui_screen_manager *, c_gui_screen_widget **, long)
	// function call : void (*const)(c_gui_screen_manager *, c_gui_screen_widget **, long)
	// function call : void *(*const)(unsigned __int32)
	// function call : void (*const)(void *, unsigned long, long, long, unsigned long)
	// function call : void (*const)(void *)
	todo("implement");
	_sub_10AE0B90(thisptr, __formal, screen_name);
}

bool __fastcall c_gui_screen_pregame_lobby__handle_controller_input_message_fallback_hook(c_gui_screen_widget *thisptr, void *__formal, c_controller_input_message *message) // 0x10AE3EA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_screen_pregame_lobby__handle_controller_input_message_fallback_hook@@YI_NPAVc_gui_screen_widget@@PAXPAUc_controller_input_message@@@Z");
	// `anonymous-namespace'::c_gui_screen_pregame_lobby__handle_controller_input_message_fallback_hook
	// c_controller_input_message *message;
	// void (*const c_gui_screen_pregame_lobby__show_game_options)(void *, long);
	// bool (*const c_gui_screen_widget__handle_controller_input_message)(c_gui_screen_widget *, c_controller_input_message *);
	// function call : void (*const)(void *, long)
	// function call : bool (*const)(c_gui_screen_widget *, c_controller_input_message *)

	bool (__thiscall *const sub_AB1270)(c_gui_screen_widget *, c_controller_input_message *) = (bool(__thiscall *const)(c_gui_screen_widget *, c_controller_input_message *))0xab1270;
	void (__thiscall *const sub_B225B0)(c_gui_screen_widget *, int) = (void(__thiscall *const)(c_gui_screen_widget *, int))0xb225b0;

	if (message->event_type == 13 && message->button == 2)
	{
		sub_B225B0(thisptr, message->controller_index);
		return true;
	}

	return sub_AB1270(thisptr, message);
}

_extern bool _sub_10AE8020(void *, void *, void *, unsigned long, c_gui_list_item_widget const *, c_gui_data *);
bool __fastcall c_start_menu_settings_handle_list_item_chosen_hook(void *thisptr, void *unused, void *message, unsigned long list_name, c_gui_list_item_widget const *list_item, c_gui_data *data) // 0x10AE8020
{
	// `anonymous-namespace'::c_start_menu_settings_handle_list_item_chosen_hook
	// void *message;
	// unsigned long list_name;
	// c_gui_list_item_widget const *list_item;
	// c_gui_data *data;
	// unsigned long id;
	// bool (*const handle_list_item_chosen)(void *, void *, unsigned long, c_gui_list_item_widget const *, c_gui_data const *);
	{
		// char *menuOptionString;
	}
	// function call : bool (long, unsigned long, unsigned long *)
	// function call : bool (*const)(void *, void *, unsigned long, c_gui_list_item_widget const *, c_gui_data const *)
	todo("implement");
	bool __result = _sub_10AE8020(thisptr, unused, message, list_name, list_item, data);
	return __result;
}

_extern bool _sub_10AE4BC0(void *, void *, void *, unsigned long, c_gui_list_item_widget const *, c_gui_data *);
bool __fastcall c_main_menu_screen_widget_handle_list_item_chosen_hook(void *thisptr, void *unused, void *message, unsigned long list_name, c_gui_list_item_widget const *list_item, c_gui_data *data) // 0x10AE4BC0
{
	// `anonymous-namespace'::c_main_menu_screen_widget_handle_list_item_chosen_hook
	// void *message;
	// unsigned long list_name;
	// c_gui_list_item_widget const *list_item;
	// c_gui_data *data;
	// bool (*const handle_list_item_chosen)(void *, void *, unsigned long, c_gui_list_item_widget const *, c_gui_data const *);
	{
		// unsigned long id;
		{
			// char *menuOptionString;
			{
			}
		}
	}
	// function call : bool (long, unsigned long, unsigned long *)
	// function call : bool (*const)(void *, void *, unsigned long, c_gui_list_item_widget const *, c_gui_data const *)
	todo("implement");
	bool __result = _sub_10AE4BC0(thisptr, unused, message, list_name, list_item, data);
	return __result;
}

_extern void _sub_10AE9250(__int32);
void ui_background_set_hook(__int32 index) // 0x10AE9250
{
	// `anonymous-namespace'::ui_background_set_hook
	// static ...; // 0x10AE96AD
	// static ...; // 0x10AE96A0
	// static ...; // 0x10AE9694
	// static ...; // 0x10AE9688
	// static ...; // 0x10AE967C
	// static ...; // 0x10AE9640
	// static ...; // 0x10AE9638
	// __int32 index;
	// Modules::ModuleSettings const &moduleSettings;
	// bool (*const bitmap_group_try_get_texture)(long, long, c_rasterizer_texture_ref *);
	// void (*const ui_set_mainmenu_bitmap_texture)(__int32);
	// __int32 screenHeight;
	// long (*const rasterizer_bitmap_get_texture)(void *);
	// s_scenario *scnr;
	// __int32 screenWidth;
	// double screenRatio;
	{
		// unsigned long bitmapTagIndex;
		// s_bitmap_definition *bitmap;
		{
			// double closestAspect;
			// __int32 closestIndex;
			{
				// __int32 x;
				{
					// double diff;
					// double imageAspectRatio;
					{
						// c_rasterizer_texture_ref texture_ref;
						{
							// __int32 texture;
						}
					}
				}
			}
			{
				// c_rasterizer_texture_ref texture_ref;
				{
					// __int32 texture;
				}
			}
			{
				{
				}
			}
		}
	}
	// function call : void (*const)(__int32)
	// function call : void *(*const)(unsigned long, long)
	// function call : bool (*const)(long, long, c_rasterizer_texture_ref *)
	// function call : long (*const)(void *)
	// function call : void (*const)(__int32)
	// function call : bool (*const)(long, long, c_rasterizer_texture_ref *)
	// function call : long (*const)(void *)
	// function call : void (*const)(__int32)
	// function call : bool (*const)(long, long, c_rasterizer_texture_ref *)
	// function call : long (*const)(void *)
	// function call : void (*const)(__int32)
	// function call : void (*const)(__int32)
	todo("implement");
	_sub_10AE9250(index);
}

_extern void _sub_10AE97E0(__int32, e_network_session_boot_reason);
void user_interface_networking_notify_booted_from_session_hook(__int32 a1, e_network_session_boot_reason reason) // 0x10AE97E0
{
	// `anonymous-namespace'::user_interface_networking_notify_booted_from_session_hook
	// static ...; // 0x10AE9A30
// $LN9:
// $LN8:
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// __int32 a1;
	// e_network_session_boot_reason reason;
	// __int32 (*const c_gui_error_manager__post_error)(void *, unsigned long, __int32, bool);
	// unsigned long reasonStringID;
	// __int32 (*const sub_A81280)(__int32);
	// char (*const sub_A92540)();
	// char (*v3)();
	// function call : __int32 (*const)(__int32)
	// function call : __int32 (*const)(__int32)
	// function call : __int32 (*const)(__int32)
	// function call : __int32 (*const)(void *, unsigned long, __int32, bool)
	// function call : __int32 (*const)(__int32)
	todo("implement");
	_sub_10AE97E0(a1, reason);
}

_extern void _sub_10AE7D10(c_gui_screen_widget *, void *, unsigned long);
void __fastcall c_start_menu_screen_widget__update_render_state_hook(c_gui_screen_widget *thisptr, void *__formal, unsigned long milliseconds) // 0x10AE7D10
{
	// `anonymous-namespace'::c_start_menu_screen_widget__update_render_state_hook
	// static ...; // 0x10AE7F58
	// c_gui_screen_widget *thisptr;
	// void *__formal;
	// unsigned long milliseconds;
	// void (*UI_ColorWidgetWithPlayerColor)(void *, __int32, bool);
	// static float `c_start_menu_screen_widget__update_render_state_hook'::`2'::color[4]; // 0x11354C94
	// void (*const c_start_menu_screen_widget__update_render_state)(void *, unsigned long);
	// static __int32 `c_start_menu_screen_widget__update_render_state_hook'::`2'::team_index; // 0x11354CA4
	// void (*RgbToFloatColor)(unsigned long, float *);
	// __int32 localPlayerIndex;
	// static bool `c_start_menu_screen_widget__update_render_state_hook'::`2'::teamsEnabled; // 0x1246748D
	// c_gui_bitmap_widget *base_color;
	// Blam::Network::Session *session;
	// void (*UI_Widget_MultiplyColor)(void *, float *);
	{
		// c_network_session *squad_session;
		{
			// s_network_session_player *player;
			// unsigned long nameplate_color;
		}
	}
	// function call : void (*const)(void *, unsigned long)
	// function call : bool (*const)(c_network_session **)
	// function call : bool (*const)()
	// function call : void (*)(unsigned long, float *)
	// function call : void (*)(void *, float *)
	// function call : void (*)(void *, __int32, bool)
	todo("implement");
	_sub_10AE7D10(thisptr, __formal, milliseconds);
}

void __fastcall c_start_menu_screen_widget__post_initialize_hook(c_gui_screen_widget *thisptr, void *unused) // 0x10AE7C40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_start_menu_screen_widget__post_initialize_hook@@YIXPAVc_gui_screen_widget@@PAX@Z");
	// `anonymous-namespace'::c_start_menu_screen_widget__post_initialize_hook
	// void *unused;
	// long session_index;
	// c_gui_bitmap_widget *emblem_widget;
	// __int32 (*const c_start_menu_screen_widget__post_initialize)(void *);
	// unsigned long playerIndex;
	// function call : __int32 (*const)(void *)
	// function call : unsigned long (*const)(long)

	void (__thiscall *const post_initialize)(c_gui_screen_widget *) = (void(__thiscall *const)(c_gui_screen_widget *))0xae0f00;

	post_initialize(thisptr);

	long playerIndex = ((long(__cdecl *)(int))0x589c30)(0);
	long session_index = Player::PlayerNetworkUtil::get_session_player_index_from_player_datum_index(playerIndex);
	c_gui_bitmap_widget *emblem_widget = thisptr->get_child_bitmap_widget(0x3F9E);
	if (emblem_widget)
	{
		if (session_index != -1)
		{
			emblem_widget->set_sprite_frame_index(session_index | 0x8000);
		}
	}
}

_extern void _sub_10AE44C0(c_gui_widget *, long, long);
void c_gui_spartan_rank_widget__update_sub_hook(c_gui_widget *widget, long in_rank, long in_grade) // 0x10AE44C0
{
	// `anonymous-namespace'::c_gui_spartan_rank_widget__update_sub_hook
	// static ...; // 0x10AE46AC
	// static ...; // 0x10AE46A4
	// c_gui_widget *widget;
	// long in_rank;
	// long in_grade;
	// void (*UI_ColorWidgetWithPlayerColor)(void *, __int32, bool);
	// __int32 rank;
	// void (*RgbToFloatColor)(unsigned long, float *);
	// __int32 localPlayerIndex;
	// __int32 (*const user_interface_session_get_player_index)(char *);
	// Blam::Network::Session *session;
	// void (*const c_gui_spartan_rank_widget_update_sub)(c_gui_widget *, long, long);
	// c_gui_bitmap_widget *rank_image;
	// void (*UI_Widget_MultiplyColor)(void *, __int32, float *);
	{
		// std::wstring rank_name;
	}
	{
	}
	// function call : void (*const)(c_gui_widget *, long, long)
	todo("implement");
	_sub_10AE44C0(widget, in_rank, in_grade);
}

_extern void _sub_10AE75D0(c_gui_screen_widget *, void *, unsigned long);
void __fastcall c_spartan_rank_widget__update_render_state_hook(c_gui_screen_widget *thisptr, void *unused, unsigned long milliseconds) // 0x10AE75D0
{
	// `anonymous-namespace'::c_spartan_rank_widget__update_render_state_hook
	// static ...; // 0x10AE7928
	// static ...; // 0x10AE7920
	// c_gui_screen_widget *thisptr;
	// void *unused;
	// unsigned long milliseconds;
	// void (*UI_ColorWidgetWithPlayerColor)(void *, __int32, bool);
	// static __int32 `c_spartan_rank_widget__update_render_state_hook'::`2'::team_index; // 0x11354CB8
	// c_network_session *squad_session;
	// void (*RgbToFloatColor)(unsigned long, float *);
	// __int32 localPlayerIndex;
	// void (*const c_gui_spartan_rank__update_render_state)(void *, unsigned long);
	// static bool `c_spartan_rank_widget__update_render_state_hook'::`2'::teamsEnabled; // 0x1246748E
	// static float `c_spartan_rank_widget__update_render_state_hook'::`2'::rank_nameplate_color[4]; // 0x11354CA8
	// __int32 (*const user_interface_session_get_player_index)(char *);
	// c_gui_bitmap_widget *base_color;
	// Blam::Network::Session *session;
	// void (*UI_Widget_MultiplyColor)(void *, __int32, float *);
	{
		// c_network_session *squad_session;
		{
			// s_network_session_player *player;
			// unsigned long nameplate_color;
		}
	}
	{
		// c_gui_list_item_widget *service_tag_widget;
		// c_gui_list_item_widget *player_name_widget;
		{
		}
		{
		}
	}
	// function call : void (*const)(void *, unsigned long)
	// function call : bool (*const)(c_network_session **)
	// function call : void (*)(unsigned long, float *)
	// function call : void (*)(void *, __int32, float *)
	// function call : void (*)(void *, __int32, bool)
	// function call : bool (*const)(c_network_session **)
	todo("implement");
	_sub_10AE75D0(thisptr, unused, milliseconds);
}

_extern void _sub_10AE4FB0(c_player_select_actions_datasource *, __int32, bool);
void c_player_select_actions_datasource__add_action(c_player_select_actions_datasource *result, __int32 stringid, bool enabled) // 0x10AE4FB0
{
	// `anonymous-namespace'::c_player_select_actions_datasource__add_action
	// bool enabled;
	// __int32 button_index;
	todo("implement");
	_sub_10AE4FB0(result, stringid, enabled);
}

_extern bool _sub_10AE3F60(void *, wchar_t *, unsigned __int32);
bool c_gui_screen_pregame_lobby__squad_party_leader_hook(void *thisptr, wchar_t *buffer, unsigned __int32 length) // 0x10AE3F60
{
	// `anonymous-namespace'::c_gui_screen_pregame_lobby__squad_party_leader_hook
	// static ...; // 0x10AE417C
	// void *thisptr;
	// wchar_t *buffer;
	// unsigned __int32 length;
	// bool (*const user_interface_squad_exists)();
	// __int32 (*const user_interface_squad_leader_get_player_index)();
	// wchar_t *(*const ustrnzcpy)(wchar_t *, wchar_t const *, long);
	// s_player_configuration *(*const user_interface_squad_get_player_data)(__int32);
	// std::wstring host_name;
	{
		// s_player_configuration *player;
		// __int32 host_index;
	}
	// function call : __int32 (*const)()
	// function call : s_player_configuration *(*const)(__int32)
	// function call : bool (*const)()
	// function call : wchar_t *(*const)(wchar_t *, wchar_t const *, long)
	todo("implement");
	bool __result = _sub_10AE3F60(thisptr, buffer, length);
	return __result;
}

_extern void _sub_10AE5010(c_player_select_actions_datasource *);
void __fastcall c_player_select_actions_datasource__initialize_hook(c_player_select_actions_datasource *thisptr) // 0x10AE5010
{
	// `anonymous-namespace'::c_player_select_actions_datasource__initialize_hook
	// c_player_select_actions_datasource *thisptr;
	// bool (*const game_options_is_valid)();
	// __int32 (*const user_interface_squad_get_player_index)(void *);
	// bool (*const user_interface_interactive_session_is_group)();
	// bool (*const user_interface_squad_local_peer_is_leader)();
	// bool (*const user_interface_squad_is_booting_allowed)();
	// __int32 (*const user_interface_session_get_player_index)(void *);
	// bool (*const user_interface_group_is_local_player)(__int32);
	// bool (*const game_is_theater)();
	// bool (*const user_interface_group_is_player_valid)(__int32);
	{
		// bool player2_is_local;
		// bool player3_is_valid;
		// __int32 destination_player_index;
		// __int32 local_player_squad_index;
		// bool selected_self;
		// __int32 source_player_index;
		// bool is_host_player;
		{
			// bool player_is_muted;
		}
	}
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : __int32 (*const)(void *)
	// function call : __int32 (*const)(void *)
	// function call : __int32 (*const)(void *)
	// function call : bool (*const)(__int32)
	// function call : bool (*const)(__int32)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : bool (*const)()
	todo("implement");
	_sub_10AE5010(thisptr);
}

_extern void _sub_10AE7140(c_gui_screen_widget *, void *, unsigned long);
void __fastcall c_player_select_screen_widget__update_render_state_hook(c_gui_screen_widget *thisptr, void *unused, unsigned long milliseconds) // 0x10AE7140
{
	// `anonymous-namespace'::c_player_select_screen_widget__update_render_state_hook
	// static ...; // 0x10AE7408
	// static ...; // 0x10AE7400
	// c_gui_screen_widget *thisptr;
	// void *unused;
	// unsigned long milliseconds;
	// void (*const c_player_select_screen_widget__update_render_state)(void *, unsigned long);
	// void (*UI_ColorWidgetWithPlayerColor)(void *, __int32, bool);
	// __int32 local_player_index;
	// __int32 player_index;
	// void (*RgbToFloatColor)(unsigned long, float *);
	// char *player_identifier_selected;
	// bool teamsEnabled;
	// __int32 (*const user_interface_session_get_player_index)(char *);
	// c_gui_bitmap_widget *base_color;
	// Blam::Network::Session *session;
	// char *player_identifier_local;
	// void (*UI_Widget_MultiplyColor)(void *, __int32, float *);
	{
		// c_network_session *squad_session;
		{
			// s_network_session_player *player;
			// unsigned long nameplate_color;
			// float color[4];
		}
	}
	// function call : void (*const)(void *, unsigned long)
	// function call : __int32 (*const)(char *)
	// function call : __int32 (*const)(char *)
	// function call : bool (*const)(c_network_session **)
	// function call : void (*)(unsigned long, float *)
	// function call : void (*)(void *, __int32, float *)
	// function call : void (*)(void *, __int32, bool)
	todo("implement");
	_sub_10AE7140(thisptr, unused, milliseconds);
}

void gui_widget_set_visible_safe(c_gui_widget *item, bool visibility) // 0x10AE8BE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?gui_widget_set_visible_safe@@YAXPAVc_gui_widget@@_N@Z");
	// `anonymous-namespace'::gui_widget_set_visible_safe
	// bool visibility;

	if (item)
	{
		item->set_visible(visibility);
	}
}

_extern void _sub_10AE5440(c_gui_screen_widget *, void *, unsigned long);
void __fastcall c_player_select_screen_widget__update_hook(c_gui_screen_widget *thisptr, void *unused, unsigned long milliseconds) // 0x10AE5440
{
	// `anonymous-namespace'::c_player_select_screen_widget__update_hook
	// static ...; // 0x10AE6B48
	// static ...; // 0x10AE6B39
	// static ...; // 0x10AE6B35
	// static ...; // 0x10AE6B2F
	// static ...; // 0x10AE6B29
	// static ...; // 0x10AE6B24
	// static ...; // 0x10AE6B1E
	// static ...; // 0x10AE6B17
	// static ...; // 0x10AE6B10
	// static ...; // 0x10AE6B09
	// static ...; // 0x10AE6AFC
	// static ...; // 0x10AE6AF6
	// static ...; // 0x10AE6AF0
	// static ...; // 0x10AE6AEA
	// static ...; // 0x10AE6AE4
	// static ...; // 0x10AE6ADE
	// static ...; // 0x10AE6AD8
	// static ...; // 0x10AE6AD2
	// static ...; // 0x10AE6ACC
	// static ...; // 0x10AE69D0
	// static ...; // 0x10AE69C8
	// c_gui_screen_widget *thisptr;
	// void *unused;
	// unsigned long milliseconds;
	// s_network_session_player *player;
	// c_gui_list_item_widget *service_record_skill;
	// __int32 local_player_index;
	// __int32 rank;
	// c_gui_bitmap_widget *medal_5;
	// __int32 player_index;
	// c_gui_list_item_widget *service_record_medals;
	// c_gui_list_item_widget *medal_1_count;
	// std::wstring rank_grade_name;
	// c_gui_list_item_widget *service_record_wins;
	// c_gui_list_item_widget *service_record_deaths;
	// c_gui_bitmap_widget *medal_1;
	// c_gui_bitmap_widget *medal_6;
	// c_gui_bitmap_widget *emblem_widget;
	// std::wstring rank_name;
	// c_gui_list_item_widget *service_record_streak;
	// c_gui_bitmap_widget *medal_2;
	// c_gui_list_item_widget *medal_2_count;
	// c_gui_bitmap_widget *medal_8;
	// char *player_identifier_selected;
	// c_gui_bitmap_widget *medal_7;
	// c_gui_list_item_widget *medal_7_count;
	// c_gui_bitmap_widget *difficulty_widget;
	// c_gui_list_item_widget *service_record_games;
	// c_gui_list_item_widget *medal_6_count;
	// c_gui_list_item_widget *medal_5_count;
	// c_gui_list_item_widget *medal_8_count;
	// c_gui_bitmap_widget *loading_ring_1;
	// c_gui_bitmap_widget *rank_widget;
	// char (*const c_player_select_screen_widget__update)(void *, unsigned long);
	// __int32 (*const user_interface_session_get_player_index)(char *);
	// c_gui_list_item_widget *medal_3_count;
	// c_gui_bitmap_widget *medal_4;
	// c_gui_list_item_widget *medal_4_count;
	// c_network_session *session;
	// char *player_identifier_local;
	// c_gui_list_item_widget *service_record_exp;
	// c_gui_list_item_widget *service_record_kills;
	// c_gui_list_item_widget *service_record_value_column;
	// c_gui_bitmap_widget *medal_3;
	// c_gui_bitmap_widget *loading_ring_3;
	// c_gui_bitmap_widget *loading_ring_2;
	// Player::ServiceRecord::ServiceRecord service_record;
	{
		// std::wstring exp;
	}
	{
		// std::wstring skill;
	}
	{
		// std::wstring games;
	}
	{
		// std::wstring wins;
	}
	{
		// std::wstring kills;
	}
	{
		// std::wstring deaths;
	}
	{
		// std::wstring medals;
	}
	{
		// std::wstring streak;
	}
	{
		// std::wstring value_column;
	}
	{
		// std::wstring count;
	}
	{
	}
	{
	}
	{
	}
	{
	}
	{
	}
	{
	}
	{
	}
	// function call : __int32 (*const)(char *)
	// function call : __int32 (*const)(char *)
	// function call : char (*const)(void *, unsigned long)
	// function call : bool (*const)(c_network_session **)
	todo("implement");
	_sub_10AE5440(thisptr, unused, milliseconds);
}

_extern void _sub_10AE2460(c_gui_screen_widget *, void *, unsigned long);
void __fastcall c_gui_roster_list_widget_update_hook(c_gui_screen_widget *thisptr, void *unused, unsigned long milliseconds) // 0x10AE2460
{
	// `anonymous-namespace'::c_gui_roster_list_widget_update_hook
	// static ...; // 0x10AE3387
	// static ...; // 0x10AE337C
	// static ...; // 0x10AE3370
	// static ...; // 0x10AE3366
	// static ...; // 0x10AE3358
	// static ...; // 0x10AE3350
	// static ...; // 0x10AE3348
	// static ...; // 0x10AE32DC
	// static ...; // 0x10AE32D4
	// c_gui_screen_widget *thisptr;
	// void *unused;
	// unsigned long milliseconds;
	// __int32 (*const ui_get_prefered_lanquage)();
	// c_gui_widget *item;
	// void *data;
	// char *(*const ui_resolve_string)(unsigned __int32, unsigned __int32, __int32);
	// long (*const c_gui_list_item_widget__get_element_handle)(void *);
	// static void (*`c_gui_roster_list_widget_update_hook'::`2'::c_gui_roster_list_widget_update)(void *, unsigned long); // 0x11354CBC
	// char (*const c_gui_roster_data__get_integer_value)(void *, long, unsigned long, long *);
	// void *(*const c_gui_list_widget__get_data)(void *);
	// __int32 (*const sub_B25B30)(void *, __int32);
	{
		// c_gui_bitmap_widget *player_joining_widget;
		// c_gui_list_item_widget *player_joining_text_widget;
		// c_gui_bitmap_widget *rank_hilite_widget;
		// c_gui_list_item_widget *player_service_tag_widget;
		// __int32 changingTeam;
		// long player_index;
		// c_gui_bitmap_widget *skill_level_hilite_widget;
		// c_gui_bitmap_widget *nameplateWidget;
		// c_gui_bitmap_widget *nameplateWidget_hilite;
		// c_gui_bitmap_widget *base_color_hilite_widget;
		// c_gui_bitmap_widget *rank_tray_hilite_widget;
		// long element_handle;
		// c_gui_bitmap_widget *voice_widget;
		// c_gui_bitmap_widget *rank_widget;
		// c_gui_bitmap_widget *base_color_widget;
		// c_gui_bitmap_widget *player_joining_hilite_widget;
		// c_gui_list_item_widget *player_name_widget;
		// c_network_session *session;
		// c_gui_bitmap_widget *player_emblem_widget;
		// c_gui_bitmap_widget *skill_level_widget;
		// c_gui_bitmap_widget *rank_tray_widget;
		// c_gui_bitmap_widget *player_emblem_hilite_widget;
		// c_gui_list_item_widget *player_name_hilite_widget;
		{
			// s_network_session_player *player;
			// __int32 ringStatus;
			// __int32 rank;
			// c_network_session *squad_session;
			// __int32 localPlayerIndex;
			// __int32 skill;
			// Blam::Network::Session *session;
			{
				// __int32 nameplate_index;
			}
			{
			}
		}
		{
			// long const team_names_tag_index;
			{
				// s_multilingual_unicode_string_list_group_header *team_names_unic;
				{
					// wchar_t rightBumper[8];
					// std::string s;
					// std::wstring wTeamName;
					// char *teamName;
					// wchar_t leftBumper[8];
					// std::wstring newPlayerName;
					// unsigned long stringid;
				}
			}
		}
		{
			{
				// std::wstring joining;
			}
		}
	}
	// function call : void (*)(void *, unsigned long)
	// function call : void *(*const)(void *)
	// function call : long (*const)(void *)
	// function call : char (*const)(void *, long, unsigned long, long *)
	// function call : bool (*const)(c_network_session **)
	// function call : __int32 (*const)(void *, __int32)
	// function call : void *(*const)(unsigned long, long)
	// function call : __int32 (*const)()
	// function call : char *(*const)(unsigned __int32, unsigned __int32, __int32)
	// function call : bool (*const)(c_network_session **)
	// function call : bool (bool)
	// function call : bool (bool)
	// function call : bool (bool)
	// function call : bool (bool)
	// function call : bool (bool)
	// function call : bool (bool)
	todo("implement");
	_sub_10AE2460(thisptr, unused, milliseconds);
}

_extern void _sub_10AE04A0(c_gui_custom_bitmap_widget *, long, e_image_content_type, __int32, bool);
void __fastcall c_gui_custom_bitmap_widget__set_map_image_hook(c_gui_custom_bitmap_widget *thisptr, long unused, e_image_content_type map_image, __int32 map_id, bool a4) // 0x10AE04A0
{
	// `anonymous-namespace'::c_gui_custom_bitmap_widget__set_map_image_hook
	// c_gui_custom_bitmap_widget *thisptr;
	// long unused;
	// e_image_content_type map_image;
	// __int32 map_id;
	// bool a4;
	// s_level_datum level;
	{
		// std::string fpath;
	}
	// function call : bool (*const)(long, s_level_datum *)
	// function call : bool (*const)(long, s_level_datum *)
	todo("implement");
	_sub_10AE04A0(thisptr, unused, map_image, map_id, a4);
}

_extern void _sub_10AE07F0(c_gui_custom_bitmap_widget *, void *, unsigned long);
void __fastcall c_gui_custom_bitmap_widget__update_hook(c_gui_custom_bitmap_widget *thisptr, void *__formal, unsigned long time) // 0x10AE07F0
{
	// `anonymous-namespace'::c_gui_custom_bitmap_widget__update_hook
	// unsigned long time;
	// void (*const c_gui_widget__update)(void *, unsigned long);
	// void (*const c_gui_custom_bitmap_widget__reset)(c_gui_custom_bitmap_widget *);
	{
		// CustomBitmapManager *customBitmapManager;
	}
	// function call : void (*const)(void *, unsigned long)
	// function call : void (*const)(c_gui_custom_bitmap_widget *)
	todo("implement");
	_sub_10AE07F0(thisptr, __formal, time);
}

void __fastcall c_gui_custom_bitmap_widget__reset_hook(c_gui_custom_bitmap_widget *thisptr) // 0x10AE0400
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_custom_bitmap_widget__reset_hook@@YIXPAUc_gui_custom_bitmap_widget@@@Z");
	// `anonymous-namespace'::c_gui_custom_bitmap_widget__reset_hook
	// c_gui_custom_bitmap_widget *thisptr;

	if (thisptr->m_storage_item_index != -1)
	{
		CustomBitmapManager::Get()->BitmapRelease(thisptr->m_storage_item_index);
		thisptr->m_storage_item_index = -1;
	}
}

void ResolutionChangeHook() // 0x10ADD1C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ResolutionChangeHook@@YAXXZ");
	// `anonymous-namespace'::ResolutionChangeHook
	// procedure flags: nofpo
	// void (*ApplyResolutionChange)();
	// function call : void (*)()

	typedef void(__thiscall *ApplyResolutionChangeFunc)();
	ApplyResolutionChangeFunc ApplyResolutionChange = reinterpret_cast<ApplyResolutionChangeFunc>(0xA226D0);
	ApplyResolutionChange();

	// Update the ingame UI's resolution
	Patches::Ui::ApplyUIResolution();
	Web::Ui::ScreenLayer::Resize();
}

__int32 UI_ListItem_GetIndex(void *item) // 0x10ADD9D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UI_ListItem_GetIndex@@YAHPAX@Z");
	// `anonymous-namespace'::UI_ListItem_GetIndex
	// void *item;
	// __int32 (*GetIndex)(void *, __int32);
	// void **vtable;
	// function call : __int32 (*)(void *, __int32)

	typedef int(__fastcall* UI_ListItem_GetIndexPtr)(void *thisPtr, int unused);
	auto vtable = *reinterpret_cast<void***>(item);
	auto GetIndex = reinterpret_cast<UI_ListItem_GetIndexPtr>(vtable[6]);
	return GetIndex(item, 0);
}

bool UI_OrderedDataSource_Get(void *data, __int32 index, __int32 key, void *result) // 0x10ADDA50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UI_OrderedDataSource_Get@@YA_NPAXHH0@Z");
	// `anonymous-namespace'::UI_OrderedDataSource_Get
	// void *result;
	// bool (*Get)(void *, __int32, __int32, __int32, void *);
	// void **vtable;
	// function call : bool (*)(void *, __int32, __int32, __int32, void *)

	typedef bool(__fastcall* UI_OrderedDataSource_GetPtr)(void *thisPtr, int unused, int index, int key, void *result);
	auto vtable = *reinterpret_cast<void***>(data);
	auto Get = reinterpret_cast<UI_OrderedDataSource_GetPtr>(vtable[11]);
	return Get(data, 0, index, key, result);
}

__int32 __fastcall c_gui_roster_list_widget__start_team_change_hook(void *thisPtr, __int32 unused, __int32 a2, __int32 teamIndex, __int32 a4) // 0x10AE1B00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_roster_list_widget__start_team_change_hook@@YIHPAXHHHH@Z");
	// `anonymous-namespace'::c_gui_roster_list_widget__start_team_change_hook
	// __int32 a4;
	// __int32 (*c_gui_roster_list_widget__start_team_change)(void *, __int32, __int32, __int32);
	// function call : __int32 (*)(void *, __int32, __int32, __int32)

	localDesiredTeam = teamIndex;
	__int32 (__thiscall *F)(void *, __int32, __int32, __int32) = (__int32(__thiscall *)(void *, __int32, __int32, __int32))0xb25c30;
	return F(thisPtr, a2, teamIndex, a4);
}

_extern void _sub_10ADCE40();
void OnUiInputUpdated() // 0x10ADCE40
{
	// `anonymous-namespace'::OnUiInputUpdated
	// procedure flags: nofpo
	// bool isUsingController;
	{
	}
	// function call : long (*const)(e_user_interface_sound, long)
	todo("implement");
	_sub_10ADCE40();
}

_extern void _sub_10AE1B90(c_gui_screen_widget *, void *, unsigned long);
void __fastcall c_gui_roster_list_widget__update_render_state(c_gui_screen_widget *thisPtr, void *__formal, unsigned long milliseconds) // 0x10AE1B90
{
	// `anonymous-namespace'::c_gui_roster_list_widget__update_render_state
	// static ...; // 0x10AE2274
	// static ...; // 0x10AE2268
	// static ...; // 0x10AE225E
	// static ...; // 0x10AE2250
	// static ...; // 0x10AE2208
	// static ...; // 0x10AE2200
	// c_gui_screen_widget *thisPtr;
	// void *__formal;
	// unsigned long milliseconds;
	// void (*const UI_ColorWidgetWithPlayerColor)(void *, __int32, bool);
	// void (*const RgbToFloatColor)(unsigned __int32, float *);
	// void *(*const UI_GetOrderedDataSource)(void *);
	// c_gui_widget *item;
	// void *data;
	// static bool `c_gui_roster_list_widget__update_render_state'::`2'::teamsEnabled; // 0x1246748F
	// long (*const c_gui_list_item_widget__get_element_handle)(void *);
	// void (*const UI_BaseUpdateListColors)(void *, unsigned long);
	// Blam::Network::Session *session;
	// char (*const c_gui_roster_data__get_integer_value)(void *, long, unsigned long, long *);
	// void (*const UI_Widget_MultiplyColor)(void *, float *);
	{
		// long player_index;
		// __int32 playerRowType;
		// c_gui_bitmap_widget *nameplateWidget;
		// c_gui_bitmap_widget *nameplateWidget_hilite;
		// c_gui_bitmap_widget *baseColorHiliteWidget;
		// __int32 itemIndex;
		// c_gui_bitmap_widget *baseColorWidget;
		// long element_handle;
		{
			// c_network_session *squad_session;
			// __int32 teamIndex;
			{
				// s_network_session_player *player;
				{
					// float joiningGrey[4];
				}
			}
			{
				// __int32 playerWidgetIndex;
				// char (*const c_gui_roster_list_widget__get_current_team_change_is_active)(void *, long);
				// static bool `c_gui_roster_list_widget__update_render_state'::`26'::wasChangingTeam; // 0x12467490
				{
					// char isChangingTeam;
				}
			}
			{
				// unsigned __int32 primaryColor;
				// float primaryColorF[4];
			}
		}
	}
	// function call : void (*const)(void *, unsigned long)
	// function call : void *(*const)(void *)
	// function call : long (*const)(void *)
	// function call : char (*const)(void *, long, unsigned long, long *)
	// function call : bool (*const)(c_network_session **)
	// function call : void (*const)(void *, float *)
	// function call : void (*const)(void *, float *)
	// function call : char (*const)(void *, long)
	// function call : void (*const)(void *, __int32, bool)
	// function call : void (*const)(void *, __int32, bool)
	// function call : void (*const)(void *, __int32, bool)
	// function call : void (*const)(void *, __int32, bool)
	// function call : void (*const)(unsigned __int32, float *)
	// function call : void (*const)(void *, float *)
	// function call : void (*const)(void *, float *)
	// function call : void (*const)(void *, float *)
	// function call : void (*const)(void *, float *)
	todo("implement");
	_sub_10AE1B90(thisPtr, __formal, milliseconds);
}

extern HWND__ *_sub_10ADB990();
HWND__ *CreateGameWindowHook() // 0x10ADB990
{
	// `anonymous-namespace'::CreateGameWindowHook
	// procedure flags: nofpo
	// static ...; // 0x10ADBB18
	// static ...; // 0x10ADBB0C
	// static ...; // 0x10ADBB04
	{
		// tagWNDCLASSEXW wc;
		// HWND__ *hWnd;
	}
	{
		// HWND__ *(*const CreateGameWindow)();
		{
			// std::vector<std::function<void __cdecl(HWND__ *)> > &<range>$L0;
			// std::function<void __cdecl(HWND__ *)> *<begin>$L0;
			// std::function<void __cdecl(HWND__ *)> *<end>$L0;
			{
				// std::function<void __cdecl(HWND__ *)> &callback;
			}
		}
	}
	// function call : HICON__ *(HINSTANCE__ *, char const *)
	// function call : HICON__ *(HINSTANCE__ *, char const *)
	// function call : unsigned short (tagWNDCLASSEXW const *)
	// function call : HWND__ *(unsigned long, wchar_t const *, wchar_t const *, unsigned long, __int32, __int32, __int32, __int32, HWND__ *, HMENU__ *, HINSTANCE__ *, void *)
	// function call : HWND__ *(*const)()
	todo("implement");
	HWND__ * __result = _sub_10ADB990();
	return __result;
}

_extern bool _sub_10ADDB60(__int32);
bool UpdateH3HUDImpl(__int32 playerMappingIndex) // 0x10ADDB60
{
	// `anonymous-namespace'::UpdateH3HUDImpl
	// __int32 playerMappingIndex;
	// UpdateH3HUDImpl::__l2::ControlGlobalsAction *action;
	// s_weapon_definition *actionWeapDef;
	// static void (*`UpdateH3HUDImpl'::`2'::HUD_DisplayHUDMessage)(unsigned __int32, __int32, __int32, __int32); // 0x11354CC4
	// s_object_data *actionWeapObject;
	// static UpdateH3HUDImpl::__l2::ControlGlobalsAction *(*`UpdateH3HUDImpl'::`2'::GetPlayerControlsAction)(__int32); // 0x11354CC0
	// function call : UpdateH3HUDImpl::__l2::ControlGlobalsAction *(*)(__int32)
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*)(unsigned __int32, __int32, __int32, __int32)
	// function call : void (*)(unsigned __int32, __int32, __int32, __int32)
	// function call : void (*)(unsigned __int32, __int32, __int32, __int32)
	// function call : void (*)(unsigned __int32, __int32, __int32, __int32)
	// function call : void (*)(unsigned __int32, __int32, __int32, __int32)
	// function call : void (*)(unsigned __int32, __int32, __int32, __int32)
	todo("implement");
	bool __result = _sub_10ADDB60(playerMappingIndex);
	return __result;
}

void UI_UpdateH3HUDHook(__int32 playerMappingIndex) // 0x10ADDAE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UI_UpdateH3HUDHook@@YAXH@Z");
	// `anonymous-namespace'::UI_UpdateH3HUDHook
	// __int32 playerMappingIndex;
	// static void (*`UI_UpdateH3HUDHook'::`2'::UI_UpdateHUD)(__int32); // 0x11354CC8
	// function call : void (*)(__int32)

	static auto UI_UpdateHUD = (void(__cdecl*)(int playerMappingIndex))(0xA95D10);

	if (!UpdateH3HUDImpl(playerMappingIndex))
		UI_UpdateHUD(playerMappingIndex);
}

bool GetBoundMouseButtonName(__int32 code, wchar_t *buff) // 0x10ADBCA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetBoundMouseButtonName@@YA_NHPA_W@Z");
	// `anonymous-namespace'::GetBoundMouseButtonName
// $LN8:
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// __int32 code;
	// wchar_t *buff;
	// Blam::Input::GameAction action;
	// Blam::Input::BindingsTable *bindings;
	// static Blam::Input::GameAction (*`GetBoundMouseButtonName'::`2'::GameActionFromUnicodeCode)(__int32); // 0x11354CCC
	// Blam::Input::MouseButton mouseButton;
	// function call : Blam::Input::GameAction (*)(__int32)

	using namespace Blam::Input;

	static auto GameActionFromUnicodeCode = (GameAction(__cdecl *)(int code))(0xABD240);

	auto bindings = Modules::ModuleInput::Instance().GetBindings();

	auto action = GameActionFromUnicodeCode(code);
	auto mouseButton = bindings->PrimaryMouseButtons[action];
	switch (mouseButton)
	{
	case eMouseButtonWheelDown:
		swprintf(buff, L"<WHEEL DOWN>");
		return true;
	case eMouseButtonWheelUp:
		swprintf(buff, L"<WHEEL UP>");
		return true;
	case eMouseButtonLeft:
		swprintf(buff, L"<LMB>");
		return true;
	case eMouseButtonRight:
		swprintf(buff, L"<RMB>");
		return true;
	case eMouseButtonMiddle:
		swprintf(buff, L"<MMB>");
		return true;
	}

	return false;
}

__declspec(naked) void GetActionButtonNameHook() // 0x10ADBC70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetActionButtonNameHook@@YAXXZ");
	// `anonymous-namespace'::GetActionButtonNameHook
	// procedure flags: nofpo
	// DEFAULT:

	__asm
	{
		push dword ptr [ebp + 14h]
		push dword ptr [ebp + 10h]
		call GetBoundMouseButtonName
		add esp, 8
		test al, al
		je Lpatched
		pop ebx
		mov esp, ebp
		pop ebp
		ret
		Lpatched:
		mov eax, 0ABCA79h
		jmp eax
	}
}

void __fastcall c_ui_view_draw_hook(void *thisptr, void *unused) // 0x10AE8270
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_ui_view_draw_hook@@YIXPAX0@Z");
	// `anonymous-namespace'::c_ui_view_draw_hook
	// void *unused;
	// function call : void (*)(void *)

	if (!Utils::Singleton<Modules::ModuleGame>::Instance().VarHideH3UI->ValueInt)
	{
		((void(__thiscall *)(void *))0xA290A0)(thisptr);
	}

	Patches::MenuBlur::RenderUIPostProcess();
}

_extern __int32 _sub_10ADC240();
__int32 GetPlayerTypeFlagsValues() // 0x10ADC240
{
	// `anonymous-namespace'::GetPlayerTypeFlagsValues
	// procedure flags: nofpo
	// static ...; // 0x10ADC4E8
	// static ...; // 0x10ADC4DC
	// static ...; // 0x10ADC4D4
	// s_unit_data *unit;
	// s_player_datum *playerDatum;
	{
		// s_game_globals *game_globals;
		{
			// long i;
			{
				// s_game_globals_player_character_type *character_type;
				// s_game_globals_player_representation *player_representation;
				{
					// char *name;
				}
			}
		}
	}
	// function call : unsigned long (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	__int32 __result = _sub_10ADC240();
	return __result;
}

_extern __int32 _sub_10ADC040();
__int32 GetMultiplayerFlagsValues() // 0x10ADC040
{
	// `anonymous-namespace'::GetMultiplayerFlagsValues
	// procedure flags: nofpo
	// __int32 flags;
	// Modules::ModuleVoIP &voipModule;
	todo("implement");
	__int32 __result = _sub_10ADC040();
	return __result;
}

__int32 GetMultiplayerEventsFlagsValues() // 0x10ADBFD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetMultiplayerEventsFlagsValues@@YAHXZ");
	// `anonymous-namespace'::GetMultiplayerEventsFlagsValues
	// procedure flags: nofpo
	// __int32 flags;

	__int32 flags = 0;

	if (Patches::Ui::speakingPlayers.size() > 0)
	{
		flags |= 8;
	}

	return flags;
}

_extern __int32 _sub_10ADCAB0();
__int32 GetUnitGeneralFlagsValues() // 0x10ADCAB0
{
	// `anonymous-namespace'::GetUnitGeneralFlagsValues
	// procedure flags: nofpo
	// __int32 flags;
	// Modules::ModuleVoIP &voipModule;
	todo("implement");
	__int32 __result = _sub_10ADCAB0();
	return __result;
}

__int32 GameStateFlagsValues() // 0x10ADBB80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GameStateFlagsValues@@YAHXZ");
	// `anonymous-namespace'::GameStateFlagsValues
	// procedure flags: nofpo
	// s_player_datum *player;
	// __int32 flags;
	// Blam::Network::Session *session;
	// function call : unsigned long (*const)(long)

	s_player_datum *player = players_get()->try_and_get(((unsigned long(__cdecl *const)(long))0x589c30)(0));

	if (!player)
	{
		return 0;
	}

	__int32 flags = 0;

	Blam::Network::Session *session = Blam::Network::GetActiveSession();

	if (session && session->IsEstablished())
	{
		if (session->HasTeams())
		{
			flags |= 16;
		}
		else
		{
			flags |= 8;
		}
	}

	return flags;
}

_extern unsigned long _sub_10ADBE10(s_chud_globals_definition *, void *, long, long);
unsigned long __fastcall GetGlobalDynamicColorHook(s_chud_globals_definition *thisptr, void *unused, long character_type, long color_index) // 0x10ADBE10
{
	// `anonymous-namespace'::GetGlobalDynamicColorHook
// $LN11:
// $LN9:
	// s_chud_globals_definition *thisptr;
	// void *unused;
	// long character_type;
	// long color_index;
	// s_chud_globals_definition *chud_definition;
	todo("implement");
	unsigned long __result = _sub_10ADBE10(thisptr, unused, character_type, color_index);
	return __result;
}

void GetWeaponOutlineColorHook(long index, real_argb_color *out_color) // 0x10ADCBA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetWeaponOutlineColorHook@@YAXJPAUreal_argb_color@@@Z");
	// `anonymous-namespace'::GetWeaponOutlineColorHook
	// real_argb_color *out_color;
	// unsigned long (*const hud_color_to_real_argb_color)(unsigned __int32, real_argb_color *);
	// s_chud_globals_definition *chud_definition;
		// long character_type;
	// function call : real_argb_color *(*const)(unsigned long, real_argb_color *)
	// function call : unsigned long (*const)(unsigned __int32, real_argb_color *)

	const auto hud_color_to_real_argb_color = (unsigned long(*)(unsigned __int32, real_argb_color *))0xAC9AA0;

	if (Patches::Ui::enableCustomHUDColors && index == 0)
	{
		out_color = ((real_argb_color *(*)(unsigned long, real_argb_color *))0x5211C0)(Patches::Ui::customSecondaryHUDColor, out_color);
		return;
	}

	auto chud_definition = *(s_chud_globals_definition **)0x5257C40;
	if (chud_definition)
	{
		auto character_type = *(long *)0x526A074;
		if (character_type < chud_definition->character_globals.count)
		{
			hud_color_to_real_argb_color(chud_definition->character_globals[character_type].colors[index + 30], out_color);
		}
		else
		{
			out_color = nullptr;
		}
	}
	else
	{
		out_color = nullptr;
	}
}

bool __fastcall c_gui_game_variant_category_datasource_init(c_gui_generic_category_datasource<11> *thisptr, void *unused, __int32 datasource) // 0x10AE0A30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_game_variant_category_datasource_init@@YI_NPAV?$c_gui_generic_category_datasource@$0L@@@PAXH@Z");
	// `anonymous-namespace'::c_gui_game_variant_category_datasource_init
	// __int32 datasource;
	// static bool (*`c_gui_game_variant_category_datasource_init'::`2'::c_gui_data_init)(void *, __int32); // 0x11354CD0
	// static void *(*`c_gui_game_variant_category_datasource_init'::`2'::sub_A84200)(__int32); // 0x11354CD4
	// __int32 index;
	// static void *(*`c_gui_game_variant_category_datasource_init'::`2'::sub_ADB130)(c_gui_generic_category_datasource<11> *, void *, __int32); // 0x11354CD8
	// void *tagsource;
	// function call : bool (*)(void *, __int32)
	// function call : void *(*)(__int32)
	// function call : void *(*)(c_gui_generic_category_datasource<11> *, void *, __int32)

	static auto c_gui_data_init = (bool(__thiscall *)(void *, int))0x00AD52F0;
	static auto sub_A84200 = (void *(*)(int))0xA84200;
	static auto sub_ADB130 = (void *(__thiscall *)(c_gui_generic_category_datasource<11> *, void *, int))0xADB130;

	if (!c_gui_data_init(thisptr, datasource))
		return false;

	auto tagsource = sub_A84200(0x201); // game_variant
	if (!tagsource)
		return false;

	thisptr->ItemCount = 0;
	auto index = 0;
	do
	{
		if (index)
		{
			if (index != 5)
				sub_ADB130(thisptr, tagsource, index);
		}
		++index;
	} while (index < 11);

	std::qsort(thisptr->items, thisptr->ItemCount, 0x26c, (int(*)(const void *, const void *))0xADB280);
	return true;
}

void __stdcall OnLobbySwitchNetworkMode() // 0x10ADCD70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnLobbySwitchNetworkMode@@YGXXZ");
	// `anonymous-namespace'::OnLobbySwitchNetworkMode
	// procedure flags: nofpo

	std::string data("{}");

	Web::Ui::ScreenLayer::Show(Web::Ui::ScreenLayer::ServerSettings, data);
}

__declspec(naked) void c_gui_screen_pregame_lobby_switch_network_hook() // 0x10AE44B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_screen_pregame_lobby_switch_network_hook@@YAXXZ");
	// `anonymous-namespace'::c_gui_screen_pregame_lobby_switch_network_hook
	// procedure flags: nofpo

	__asm
	{
		call OnLobbySwitchNetworkMode
		mov eax, 0B21F5Bh
		jmp eax
	}
}

_extern void _sub_10ADFDE0(void *, void *, unsigned __int32, __int32, wchar_t *, __int32, bool, __int32);
void __fastcall c_gui_alert_manager__show(void *thisptr, void *unused, unsigned __int32 name, __int32 a3, wchar_t *customMessage, __int32 profileIndex, bool a6, __int32 a7) // 0x10ADFDE0
{
	// `anonymous-namespace'::c_gui_alert_manager__show
	// wchar_t *customMessage;
	// __int32 profileIndex;
	// bool a6;
	// __int32 a7;
	// s_user_interface_shared_globals *wigl;
	// __int32 (*const ui_get_prefered_lanquage)();
	// char *(*const ui_resolve_string)(unsigned __int32, unsigned __int32, __int32);
	// long const alertStrings;
	{
		// c_tag_block<s_gui_alert_description> &<range>$L0;
		// s_gui_alert_description *<begin>$L0;
		// s_gui_alert_description *<end>$L0;
		{
			// s_gui_alert_description &alert;
			{
				// char const *body;
				// char const *title;
				{
					// std::string customMessageStr;
				}
			}
		}
	}
	// function call : s_user_interface_shared_globals *(*const)()
	// function call : __int32 (*const)()
	// function call : char *(*const)(unsigned __int32, unsigned __int32, __int32)
	// function call : __int32 (*const)()
	// function call : char *(*const)(unsigned __int32, unsigned __int32, __int32)
	todo("implement");
	_sub_10ADFDE0(thisptr, unused, name, a3, customMessage, profileIndex, a6, a7);
}

void __fastcall c_hud_camera_view__render_outlines_hook(void *thisptr, void *unused, __int32 localProfileIndex, __int32 playerMappingIndex, void *a3) // 0x10AE4AC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_hud_camera_view__render_outlines_hook@@YIXPAX0HH0@Z");
	// `anonymous-namespace'::c_hud_camera_view__render_outlines_hook
	// void *a3;
	// s_player_datum *player;
	// unsigned long const playerIndex;
	// void (*const c_hud_camera_view__render_outlines_hook)(void *, __int32, __int32, void *);
	// Modules::ModuleTweaks const &moduleTweaks;
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(void *, __int32, __int32, void *)

	void (__thiscall *const c_hud_camera_view__render_outlines_hook)(void *, __int32, __int32, void *) = (void (__thiscall *const)(void *, __int32, __int32, void *))0xa2e620;
	Modules::ModuleTweaks const &moduleTweaks = Utils::Singleton<Modules::ModuleTweaks>::Instance();

	unsigned long const playerIndex = ((unsigned long(*)(long))0x589C30)(0);
	s_player_datum *player;

	if (playerIndex != -1)
	{
		player = players_get()->try_and_get(playerIndex);
		if (player)
		{
			if (player->unit_index != -1)
			{
				if (object_get(player->unit_index))
				{
					c_hud_camera_view__render_outlines_hook(thisptr, localProfileIndex, playerMappingIndex, a3);
				}
			}
		}
	}
}

wchar_t *chud_talking_player_name_hook(wchar_t *buffer) // 0x10AE87F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?chud_talking_player_name_hook@@YAPA_WPA_W@Z");
	// `anonymous-namespace'::chud_talking_player_name_hook
	// wchar_t *buffer;
	// wchar_t *(*const ustrnzcpy)(wchar_t *, wchar_t *, long);
	// function call : wchar_t *(*const)(wchar_t *, wchar_t *, long)

	const auto csmemcpy = (void(*)(void *, void const *, unsigned long))0x4ECCD0;

	csmemcpy(buffer, &Patches::Ui::chud_talking_player_name, 16);
	return buffer;
}

_extern bool _sub_10ADD020(unsigned __int32);
bool PlayerMarkerIsDisabled(unsigned __int32 playerIndex) // 0x10ADD020
{
	// `anonymous-namespace'::PlayerMarkerIsDisabled
	// unsigned __int32 playerIndex;
	// s_player_datum *player;
	// s_player_datum *localPlayer;
	// unsigned long localPlayerDatumIndex;
	// c_data_array<s_player_datum> *players;
	// unsigned char waypointTrait;
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_10ADD020(playerIndex);
	return __result;
}

_extern void _sub_10AE8510(void *, void *, unsigned char *);
void __fastcall chud_add_player_marker_hook(void *thisptr, void *unused, unsigned char *data_) // 0x10AE8510
{
	// `anonymous-namespace'::chud_add_player_marker_hook
	// unsigned char *data_;
	// s_chud_navpoint *data;
	// __int32 index;
	// __int32 (*const sub_AAF560)(void *);
	// s_chud_managed_navpoint *state;
	{
		// s_chud_managed_navpoint *newState;
	}
	{
		// s_chud_managed_navpoint *existingState;
		{
			// s_chud_managed_navpoint *newState;
		}
		{
			// s_player_datum *player;
			{
				// s_object_data *unitObject;
			}
		}
	}
	// function call : __int32 (*const)(void *)
	// function call : __int32 (*const)(void *)
	// function call : long (*const)()
	// function call : long (*const)()
	todo("implement");
	_sub_10AE8510(thisptr, unused, data_);
}

void __fastcall c_start_menu_pane_screen_widget__handle_spinner_chosen_hook(void *thisptr, void *unused, unsigned char *widget) // 0x10AE7A40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_start_menu_pane_screen_widget__handle_spinner_chosen_hook@@YIXPAX0PAE@Z");
	// `anonymous-namespace'::c_start_menu_pane_screen_widget__handle_spinner_chosen_hook
// $LN17:
// $LN16:
// $LN15:
// $LN14:
// $LN13:
// $LN12:
// $LN11:
// $LN10:
// $LN9:
	// void *thisptr;
	// void *unused;
	// unsigned char *widget;
	// __int32 const _string_id_value;
	// unsigned char *(*const game_engine_get_map_variant)();
	// void (*const c_gui_list_widget__set_selected)(void *, __int32, __int32, char);
		// __int32 selectedGametype;
		// __int32 contentType;
			// __int32 teamIndex;
	// function call : void (*const)(void *, __int32, __int32, char)
	// function call : unsigned char *(*const)()
	// function call : void (*const)(void *, __int32, __int32, char)

	const auto c_gui_list_widget__set_selected = (void(__thiscall *)(void *thisptr, int target, int value, char a5))(0xB16170);
	const auto game_engine_get_map_variant = (uint8_t*(*)())(0x00583230);
	const auto _string_id_value = 0x111;

	switch (*(uint32_t*)(widget + 0x40))
	{
	case 0x10E: //  change_teams
	{
		auto teamIndex = *(int*)((uint8_t*)0x019A03D8 + 0x167C);
		if (teamIndex < 0)
			teamIndex = 0;
		c_gui_list_widget__set_selected(widget, 0x111, teamIndex, 0);
	}
	break;
	case 0x105B9: // change_gametype
		auto selectedGametype = 0;
		auto contentType = *(int*)(game_engine_get_map_variant() + 0x11c);
		switch (contentType)
		{
		case 0:
			selectedGametype = 1;
			break;
		case 1:
			selectedGametype = 2;
			break;
		case 2:
			selectedGametype = 3;
			break;
		case 3:
			selectedGametype = 4;
			break;
		case 4:
			selectedGametype = 7;
			break;
		case 5:
			selectedGametype = 8;
			break;
		case 6:
			selectedGametype = 9;
			break;
		case 7:
			selectedGametype = 6;
			break;
		case 8:
			selectedGametype = 10;
			break;
		case 10:
			selectedGametype = 0;
			break;
		}
		c_gui_list_widget__set_selected(widget, 0x111, selectedGametype, 0);
		break;
	}
}

void __fastcall UI_GameVariantSavePromptFix(void *thisptr, void *unused, __int32 a2) // 0x10ADD940
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UI_GameVariantSavePromptFix@@YIXPAX0H@Z");
	// `anonymous-namespace'::UI_GameVariantSavePromptFix
	// __int32 a2;
	// void (*const c_gui_screen_widget__transition_out)(void *, __int32);
	// unsigned __int32 name;
	// function call : void (*const)(void *, __int32)

	const auto c_gui_screen_widget__transition_out = (void(__thiscall*)(void *thisptr, int a2))(0x00AB2830);

	auto name = *(uint32_t*)((uint8_t*)thisptr + 0x40);
	if (name != 0x103A9) // game_options
		c_gui_screen_widget__transition_out(thisptr, a2);
}

float get_player_vertical_crosshair_location() // 0x10AE8B30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_player_vertical_crosshair_location@@YAMXZ");
	// `anonymous-namespace'::get_player_vertical_crosshair_location
	// procedure flags: nofpo
	// constexpr unsigned char *(*const `get_player_vertical_crosshair_location'::`2'::c_player_profile__get)(__int32); // constant == 10997072
	// s_game_globals *game_globals;
	// unsigned char *c_player_profile;
	// __int32 representationIndex;
	// function call : unsigned char *(*const)(__int32)

	s_game_globals *game_globals;
	long representationIndex;

	representationIndex = *(long *)(((long(*)(long))0xA7CD50)(0) + 4);
	game_globals = game_globals_get();
	if (game_globals->PlayerControl.count <= representationIndex)
	{
		return 0.0f;
	}

	return game_globals->PlayerControl[representationIndex].CrosshairLocation.y;
}

void observer_validate_camera_command__first_person_hook(unsigned char *c_observer_command) // 0x10AE8ED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?observer_validate_camera_command__first_person_hook@@YAXPAE@Z");
	// `anonymous-namespace'::observer_validate_camera_command__first_person_hook
	// unsigned char *c_observer_command;
	// constexpr void (*const `observer_validate_camera_command__first_person_hook'::`2'::observer_validate_camera_command)(void *); // constant == 6376800
	// function call : void (*const)(void *)

	*(float *)(c_observer_command + 8) = get_player_vertical_crosshair_location();
	if (Utils::Singleton<Modules::ModuleCamera>::Instance().VarCameraCenteredCrosshairFirst->ValueInt == 1)
	{
		*(float *)(c_observer_command + 8) = 0.0f;
	}

	((void(*)(unsigned char *))0x614D60)(c_observer_command);
}

void observer_validate_camera_command__third_person_hook(unsigned char *c_observer_command) // 0x10AE8F50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?observer_validate_camera_command__third_person_hook@@YAXPAE@Z");
	// `anonymous-namespace'::observer_validate_camera_command__third_person_hook
	// unsigned char *c_observer_command;
	// constexpr void (*const `observer_validate_camera_command__third_person_hook'::`2'::observer_validate_camera_command)(void *); // constant == 6376800
	// function call : void (*const)(void *)

	*(float *)(c_observer_command + 8) = get_player_vertical_crosshair_location();
	if (Utils::Singleton<Modules::ModuleCamera>::Instance().VarCameraCenteredCrosshairThird->ValueInt == 1)
	{
		*(float *)(c_observer_command + 8) = 0.0f;
	}

	((void(*)(unsigned char *))0x614D60)(c_observer_command);
}

__int32 user_interface_squad_get_countdown_timer_hook() // 0x10AE9C40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?user_interface_squad_get_countdown_timer_hook@@YAHXZ");
	// `anonymous-namespace'::user_interface_squad_get_countdown_timer_hook
	// procedure flags: nofpo
	// static ...; // 0x10AE9CF4
	// static ...; // 0x10AE9CE8
	// static ...; // 0x10AE9CE0
	// c_network_session_parameters *session_parameters;
	// c_network_session *session;
	// c_network_session_parameter_base *session_parameter;
	// function call : bool (*const)(c_network_session **)

	c_network_session *session;
	c_network_session_parameters *session_parameters;
	c_network_session_parameter_base *session_parameter;

	if (!network_session_interface_get_squad_session(&session))
	{
		return -1;
	}

	session_parameters = session->get_session_parameters();
	if (!session_parameters)
	{
		return -1;
	}

	session_parameter = session_parameters->parameters[25];
	return *(__int32 *)((unsigned char *)session_parameter + 0x34);
}

_extern void _sub_10ADF560(c_chud_update_user_data *, void *, long, long, bool);
void __fastcall c_chud_update_user_data__ctor_hook(c_chud_update_user_data *thisptr, void *__formal, long user_index, long unit_index, bool a4) // 0x10ADF560
{
	// `anonymous-namespace'::c_chud_update_user_data__ctor_hook
	// bool a4;
	// constexpr void (*const `c_chud_update_user_data__ctor_hook'::`2'::ctor)(c_chud_update_user_data *, long, long, bool); // constant == 11031104
	// s_unit_data *unit;
	// c_chud_global_scripting *scripting;
	{
		// s_equipment_data *equipment;
		{
			// s_equipment_definition *equipment_definition;
			{
				// float remaining_time;
				// float max_use_duration;
				// float remaining_fraction;
				// float time_since_use;
			}
		}
	}
	// function call : void (*const)(c_chud_update_user_data *, long, long, bool)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void *(*const)(unsigned long, long)
	// function call : bool (*const)(long)
	// function call : long (*const)()
	// function call : float (*const)(float)
	// function call : float (*const)(long)
	todo("implement");
	_sub_10ADF560(thisptr, __formal, user_index, unit_index, a4);
}

_extern void _sub_10AE82F0(c_user_interface_main_menu_music *, void *);
void __fastcall c_user_interface_main_menu_music_update_desired_state(c_user_interface_main_menu_music *thisptr, void *unused) // 0x10AE82F0
{
	// `anonymous-namespace'::c_user_interface_main_menu_music_update_desired_state
// $LN16:
// $LN9:
// $LN7:
	// c_user_interface_main_menu_music *thisptr;
	// void *unused;
	// s_scenario *scenario;
	// c_gui_screen_widget *screen;
	{
		// long location;
	}
	// function call : c_gui_screen_widget *(*)()
	// function call : long ()
	// function call : long ()
	// function call : bool (*const)()
	// function call : bool (*const)()
	todo("implement");
	_sub_10AE82F0(thisptr, unused);
}

_extern void _sub_10AE9D30();
void user_interface_text_parser_initialize_hook() // 0x10AE9D30
{
	// `anonymous-namespace'::user_interface_text_parser_initialize_hook
	// procedure flags: nofpo
	// static char `user_interface_text_parser_initialize_hook'::`2'::selected_mod_parser[20]; // 0x12467494
	// static char `user_interface_text_parser_initialize_hook'::`2'::mission_tag_parser[20]; // 0x124674BC
	// void (*const user_interface_text_parser_initialize)();
	// void (*const c_magic_string_game_tag_parser_ctor)(void *, wchar_t const *, void *, bool (*)(void *, wchar_t *, long));
	// static char `user_interface_text_parser_initialize_hook'::`2'::version_tag_parser[20]; // 0x124674A8
	// void (*const user_interface_text_parser_register)(void *, __int32);
	// function call : void (*const)()
	// function call : void (*const)(void *, wchar_t const *, void *, bool (*)(void *, wchar_t *, long))
	// function call : void (*const)(void *, __int32)
	// function call : void (*const)(void *, wchar_t const *, void *, bool (*)(void *, wchar_t *, long))
	// function call : void (*const)(void *, __int32)
	// function call : void (*const)(void *, wchar_t const *, void *, bool (*)(void *, wchar_t *, long))
	// function call : void (*const)(void *, __int32)
	todo("implement");
	_sub_10AE9D30();
}

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

_extern bool _sub_10AE4230(void *, void *, void *, unsigned long, c_gui_list_item_widget *, c_gui_data *);
bool __fastcall c_gui_screen_pregame_lobby_handle_item_chosen_hook(void *thisptr, void *unused, void *message, unsigned long source_name, c_gui_list_item_widget *list_widget, c_gui_data *data) // 0x10AE4230
{
	// `anonymous-namespace'::c_gui_screen_pregame_lobby_handle_item_chosen_hook
	// void *message;
	// unsigned long source_name;
	// c_gui_list_item_widget *list_widget;
	// c_gui_data *data;
	// long index;
	// unsigned long item_name_id;
	{
		// char *name;
	}
	// function call : bool (long, unsigned long, unsigned long *)
	// function call : bool (*)(void *, void *, unsigned long, c_gui_list_item_widget *, c_gui_data *)
	todo("implement");
	bool __result = _sub_10AE4230(thisptr, unused, message, source_name, list_widget, data);
	return __result;
}

_extern bool _sub_10AE3780(c_gui_screen_widget *, void *, c_controller_input_message *);
bool __fastcall c_gui_screen_campaign_select_skulls__handle_controller_input_message_hook(c_gui_screen_widget *thisptr, void *unused, c_controller_input_message *message) // 0x10AE3780
{
	// `anonymous-namespace'::c_gui_screen_campaign_select_skulls__handle_controller_input_message_hook
	// static ...; // 0x10AE3C0C
	// c_gui_screen_widget *thisptr;
	// void *unused;
	// c_controller_input_message *message;
	// void (*const select_skull)(c_gui_screen_widget *, __int32, long);
	// bool (*const handle_controller_input_message)(c_gui_screen_widget *, c_controller_input_message *);
	// c_gui_screen_campaign_select_skulls__handle_controller_input_message_hook::__l2::<lambda_1> clamp_list_item_index;
	// __int32 const row_size;
	{
		// c_gui_list_widget *secondary_list;
		// c_gui_list_widget *primary_list;
		{
			// long new_index;
			// long row_index;
			// long item_count;
			// long column_index;
			// long item_index;
			// long row_count;
			// long target_list_index;
		}
		{
			// __int32 target_list_index;
		}
	}
	// function call : bool ()
	// function call : void (*const)(c_gui_screen_widget *, __int32, long)
	// function call : bool ()
	// function call : void (*const)(c_gui_screen_widget *, __int32, long)
	// function call : bool (*const)(c_gui_screen_widget *, c_controller_input_message *)
	todo("implement");
	bool __result = _sub_10AE3780(thisptr, unused, message);
	return __result;
}

void __fastcall c_gui_screen_game_options__update_hook(c_gui_screen_widget *thisptr, void *__formal, unsigned long milliseconds) // 0x10AE3D70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_screen_game_options__update_hook@@YIXPAVc_gui_screen_widget@@PAXK@Z");
	// `anonymous-namespace'::c_gui_screen_game_options__update_hook
	// unsigned long milliseconds;
	// unsigned long (*const user_interface_milliseconds)();
	// unsigned long &progress_start_time_ms;
	// c_gui_screen_widget *progress_screen;
	// long task_id;
	// function call : bool ()
	// function call : unsigned long (*const)()
	// function call : void (*)(c_gui_screen_widget *, unsigned long)

	unsigned long (*const user_interface_milliseconds)() = (unsigned long (*const)())0xa848e0;
	long task_id = *(long *)offset_pointer(thisptr, 71492);
	unsigned long &progress_start_time_ms = *(unsigned long *)offset_pointer(thisptr, 71508);
	c_gui_screen_widget *progress_screen = (c_gui_screen_widget *)thisptr->get_child_widget(_gui_widget_screen, 0x100BE);

	if (progress_screen
		&& !progress_screen->transitioning_out()
		&& progress_start_time_ms
		&& user_interface_milliseconds() - progress_start_time_ms >= 0x7D0
		&& task_id == -1)
	{
		progress_screen->transition_out(0);
		progress_start_time_ms = 0;
	}

	((void (__thiscall *)(c_gui_screen_widget *, unsigned long))0xb0d410)(thisptr, milliseconds);
}

_extern void _sub_10AE4760(c_gui_widget *, void *, gui_real_rectangle2d *, bool, bool, bool);
void __fastcall c_gui_widget__get_unprojected_bounds_hook(c_gui_widget *thisptr, void *unused, gui_real_rectangle2d *unprojected_bounds, bool offset, bool scale, bool rotate) // 0x10AE4760
{
	// `anonymous-namespace'::c_gui_widget__get_unprojected_bounds_hook
	// void *unused;
	// gui_real_rectangle2d *unprojected_bounds;
	// bool offset;
	// bool scale;
	// bool rotate;
	// short_rectangle2d display_pixel_bounds;
	// float ui_aspect_ratio;
	// void (*const get_unprojected_bounds)(c_gui_widget *, gui_real_rectangle2d *, bool, bool, bool);
	// float ui_tag_resolutions[2][2];
	// long *ui_resolution;
	// float width_scale;
	// float height_scale;
	// float widescreen_factor;
	// long display_mode;
	// function call : void (*const)(c_gui_widget *, gui_real_rectangle2d *, bool, bool, bool)
	// function call : void (*const)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *)
	todo("implement");
	_sub_10AE4760(thisptr, unused, unprojected_bounds, offset, scale, rotate);
}

void c_rasterizer__get_display_pixel_bounds_hook(short_rectangle2d *display_pixel_bounds) // 0x10AE7500
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_rasterizer__get_display_pixel_bounds_hook@@YAXPAUshort_rectangle2d@@@Z");
	// `anonymous-namespace'::c_rasterizer__get_display_pixel_bounds_hook
	// short_rectangle2d *display_pixel_bounds;
	// long *ui_resolution;

	long *ui_resolution = (long *)0x19106C8;

	display_pixel_bounds->x0 = 0;
	display_pixel_bounds->x1 = 0;
	display_pixel_bounds->y0 = 0;
	display_pixel_bounds->y1 = 0;

	if (ui_resolution[0] <= 8)
	{
		display_pixel_bounds->x1 = 8;
	}
	else
	{
		display_pixel_bounds->x1 = (short)ui_resolution[0];
	}

	if (ui_resolution[1] <= 8)
	{
		display_pixel_bounds->y1 = 8;
	}
	else
	{
		display_pixel_bounds->y1 = (short)ui_resolution[1];
	}
}

long interface_get_closest_authored_ui_aspect_ratio_hook() // 0x10AE8C90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?interface_get_closest_authored_ui_aspect_ratio_hook@@YAJXZ");
	// `anonymous-namespace'::interface_get_closest_authored_ui_aspect_ratio_hook
	// procedure flags: nofpo
	// float ui_aspect_ratio;
	// long *ui_resolution;

	long *resolution = (long *)0x19106C8;
	float aspect = (float)resolution[0] / (float)resolution[1];

	if (aspect < 1.6f)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

extern real_point2d _sub_10AE8C30();
real_point2d interface_get_authoring_to_target_dimensions_scaling_hook() // 0x10AE8C30
{
	// `anonymous-namespace'::interface_get_authoring_to_target_dimensions_scaling_hook
	// procedure flags: nofpo
	// real_point2d *target_dimensions;
	todo("implement");
	real_point2d __result = _sub_10AE8C30();
	return __result;
}

void __fastcall c_gui_custom_bitmap_widget__assemble_render_data_hook(c_gui_custom_bitmap_widget *thisptr, void *unused, s_gui_widget_render_data *render_data, real_rectangle2d *bounds, long controller_index, bool offset, bool scale, bool rotate) // 0x10AE01E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_custom_bitmap_widget__assemble_render_data_hook@@YIXPAUc_gui_custom_bitmap_widget@@PAXPAUs_gui_widget_render_data@@PAUreal_rectangle2d@@J_N44@Z");
	// `anonymous-namespace'::c_gui_custom_bitmap_widget__assemble_render_data_hook
	// long controller_index;
	// bool offset;
	// bool scale;
	// bool rotate;
	// long (*const interface_get_closest_authored_ui_aspect_ratio)();
	// void (*const c_gui_bitmap_widget__assemble_render_data)(c_gui_custom_bitmap_widget *, s_gui_widget_render_data *, real_rectangle2d *, long, bool, bool, bool);
	// real_point2d (*const interface_get_authoring_aspect_conversion_scaling)(long);
	// float width;
	// long display_mode;
	// real_point2d bitmap_scale;
	// float height;
	// function call : void (*const)(c_gui_custom_bitmap_widget *, s_gui_widget_render_data *, real_rectangle2d *, long, bool, bool, bool)
	// function call : long (*const)()
	// function call : real_point2d (*const)(long)

	void (__thiscall *const c_gui_bitmap_widget__assemble_render_data)(c_gui_custom_bitmap_widget *, s_gui_widget_render_data *, real_rectangle2d *, long, bool, bool, bool) = (void (__thiscall *const)(c_gui_custom_bitmap_widget *, s_gui_widget_render_data *, real_rectangle2d *, long, bool, bool, bool))0xb167b0;
	long (*const interface_get_closest_authored_ui_aspect_ratio)() = (long (*const)())0xa9f980;
	real_point2d (*const interface_get_authoring_aspect_conversion_scaling)(long) = (real_point2d (*const)(long))0xa9f920;

	c_gui_bitmap_widget__assemble_render_data(thisptr, render_data, bounds, controller_index, offset, scale, rotate);

	*(unsigned long *)&render_data->scaled_anchoring |= 1;
	*(unsigned long *)((unsigned char *)render_data + 0x30) = thisptr->m_storage_item_index;

	long display_mode = interface_get_closest_authored_ui_aspect_ratio();
	real_point2d bitmap_scale = interface_get_authoring_aspect_conversion_scaling(display_mode);
	float width = render_data->vertices.top_right.x - render_data->vertices.top_left.x;
	float height = render_data->vertices.bottom_left.y - render_data->vertices.top_left.y;

	width *= bitmap_scale.x;
	height *= bitmap_scale.y;

	render_data->vertices.top_right.x = render_data->vertices.top_left.x + width;
	render_data->vertices.bottom_right.x = render_data->vertices.top_left.x + width;
	render_data->vertices.bottom_left.y = render_data->vertices.top_left.y + height;
	render_data->vertices.bottom_right.y = render_data->vertices.top_left.y + height;
}

bool __fastcall c_draw_string__draw_internal_hook(c_draw_string *thisptr, void *unused, void *cache, char const *utf32_text) // 0x10ADFB40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_draw_string__draw_internal_hook@@YI_NPAUc_draw_string@@PAX1PBD@Z");
	// `anonymous-namespace'::c_draw_string__draw_internal_hook
	// char const *utf32_text;
	// bool (*const c_draw_string__draw_internal)(c_draw_string *, void *, char const *);
	// float font_scale;
	// function call : bool (*const)(c_draw_string *, void *, char const *)

	float font_scale = 1.0f;

	thisptr->scale = thisptr->scale * font_scale;

	const auto c_draw_string__draw_internal = (bool(__thiscall *)(c_draw_string *, void *, char const *))0x657950;

	return c_draw_string__draw_internal(thisptr, cache, utf32_text);
}

void __fastcall c_draw_string__set_bounds_hook(c_draw_string *thisptr, void *unused, real_rectangle2d *upper_x, real_rectangle2d *upper_y) // 0x10ADFBE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_draw_string__set_bounds_hook@@YIXPAUc_draw_string@@PAXPAUreal_rectangle2d@@2@Z");
	// `anonymous-namespace'::c_draw_string__set_bounds_hook
	// static ...; // 0x10ADFD38
	// c_draw_string *thisptr;
	// void *unused;
	// real_rectangle2d *upper_x;
	// real_rectangle2d *upper_y;
	// long (*const interface_get_closest_authored_ui_aspect_ratio)();
	// void (*const c_draw_string__set_bounds)(c_draw_string *, real_rectangle2d *, real_rectangle2d *);
	// float ui_tag_resolutions[2][2];
	// float scale_factor;
	// long *ui_resolution;
	// real_point2d (*const interface_get_authoring_aspect_conversion_scaling)(long);
	// long display_mode;
	// real_point2d bitmap_scale;
	// function call : long (*const)()
	// function call : real_point2d (*const)(long)
	// function call : void (*const)(c_draw_string *, real_rectangle2d *, real_rectangle2d *)

	void (__thiscall *const c_draw_string__set_bounds)(c_draw_string *, real_rectangle2d *, real_rectangle2d *) = (void (__thiscall *const)(c_draw_string *, real_rectangle2d *, real_rectangle2d *))0x658b10;
	long (*const interface_get_closest_authored_ui_aspect_ratio)() = (long (*const)())0xa9f980;
	real_point2d (*const interface_get_authoring_aspect_conversion_scaling)(long) = (real_point2d (*const)(long))0xa9f920;
	long *ui_resolution = (long *)0x19106C8;
	float ui_tag_resolutions[2][2] = { { 1512.0f, 840.0f }, { 840.0f, 630.0f } };

	long display_mode = interface_get_closest_authored_ui_aspect_ratio();
	real_point2d bitmap_scale = interface_get_authoring_aspect_conversion_scaling(display_mode);
	float scale_factor = (float)ui_resolution[1] / ui_tag_resolutions[display_mode][1];

	thisptr->scale = thisptr->scale * scale_factor;

	c_draw_string__set_bounds(thisptr, upper_x, upper_y);
}

bool user_interface_set_campaign_options_hook(long campaign_id, long map_id, short insertion_point_index, long a4, long a5, long a7) // 0x10AE9B00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?user_interface_set_campaign_options_hook@@YA_NJJFJJJ@Z");
	// `anonymous-namespace'::user_interface_set_campaign_options_hook
	// long map_id;
	// short insertion_point_index;
	// long a4;
	// long a5;
	// long a7;
	// long current_campaign_id;
	// long current_map_id;
	// char (*const user_interface_set_campaign_options)(long, long, short, long, long, long);
	// function call : bool (*const)(long *, long *)
	// function call : char (*const)(long, long, short, long, long, long)

	long current_campaign_id;
	long current_map_id[2];

	if (((bool(*)(long *, long *))0xA817B0)(&current_campaign_id, current_map_id) && current_campaign_id != -1)
	{
		return true;
	}

	const auto user_interface_set_campaign_options = (char(*)(long, long, short, long, long, long))0xA83690;

	return user_interface_set_campaign_options(campaign_id, map_id, insertion_point_index, a4, a5, a7);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_enum<enum e_scenario_type,char>::operator!=(e_scenario_type const &) const;
template bool c_enum<enum e_scenario_type,char>::operator==(e_scenario_type const &) const;
template bool c_tag_block<s_multilingual_unicode_string_reference>::try_get_element(__int32, s_multilingual_unicode_string_reference **) const;
template bool c_tag_block<s_multiplayer_runtime_sound>::try_get_element(__int32, s_multiplayer_runtime_sound **) const;
template bool c_tag_block<s_scenario_background_textures>::try_get_element(__int32, s_scenario_background_textures **) const;
template bool s_static_array<unsigned long,37>::valid(__int32);
template c_enum<enum e_gui_error_icon,char>::operator char() const;
template long s_static_array<unsigned long,37>::get_count();
template s_gui_alert_description * c_tag_block<s_gui_alert_description>::begin();
template s_gui_alert_description * c_tag_block<s_gui_alert_description>::end();
template s_multilingual_unicode_string_reference & c_tag_block<s_multilingual_unicode_string_reference>::operator[](__int32);
template s_multilingual_unicode_string_reference * c_tag_block<s_multilingual_unicode_string_reference>::get_element(__int32) const;
template s_multiplayer_runtime_sound & c_tag_block<s_multiplayer_runtime_sound>::operator[](__int32);
template s_multiplayer_runtime_sound * c_tag_block<s_multiplayer_runtime_sound>::get_element(__int32) const;
template s_scenario_background_textures & c_tag_block<s_scenario_background_textures>::operator[](__int32);
template s_scenario_background_textures * c_tag_block<s_scenario_background_textures>::get_element(__int32) const;
template unsigned long & s_static_array<unsigned long,37>::operator[](long);
