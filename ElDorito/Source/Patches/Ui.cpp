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
#include "mods/mod_system.hpp"  // hades: added for 0x10AE9D30
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

#include "Modules/ModuleServer.hpp"  // hades: added for 0x10AE3F60

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

namespace eldorado
{
	// Functions in eldorado.exe, named from the game's own symbols.
	static auto const equipment_get_use_duration = reinterpret_cast<float (*)(long)>(0xB889F0);
	static auto const equipment_has_remaining_use_duration = reinterpret_cast<bool (*)(long)>(0xB88C80);
}

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const controller_get = reinterpret_cast<unsigned char *(*)(__int32)>(0xA7CD50);
	static auto const levels_try_and_get_campaign_insertion = reinterpret_cast<bool (*)(long, void *)>(0x54C9E0);
	static auto const network_life_cycle_session_get_map = reinterpret_cast<bool (*)(long *, long *)>(0x4354D0);
	static auto const network_squad_session_get_campaign_insertion_point = reinterpret_cast<short (*)()>(0x435080);
	static auto const player_mapping_get_player_by_input_user = reinterpret_cast<unsigned long(__cdecl *)(long)>(0x589C30);
}

extern void *(__cdecl *const tag_get)(unsigned long, long);  // hades: added for 0x10ADD3E0
extern void *tag_try_and_get_and_verify_group(unsigned long group_tag, long tag_index);  // hades: added for 0x10ADD3E0

long tag_find_by_name(unsigned long group_tag, char const *name);  // hades: added for 0x10ADFDE0

void player_format_uid(char *string, unsigned long long id);  // hades: added for 0x10AE10C0

#include <format>  // hades: added for 0x10AE04A0
extern bool (*const levels_try_and_get_multiplayer_map)(long, s_level_datum *);  // hades: added for 0x10AE04A0
extern bool (*const levels_try_and_get_campaign_map)(long, s_level_datum *);  // hades: added for 0x10AE04A0
extern s_session_mod_options const *network_squad_session_get_mod();  // hades: added for 0x10AE9D30
namespace Utils::Version { std::string GetVersionString(); }  // hades: added for 0x10AE9D30

extern long (*const game_time_get)(); extern float (*const game_ticks_to_seconds)(float);  // hades: added for 0x10AE8510, 0x10ADF560

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0x10ADC240

#include "Blam/camera/camera.hpp"  // hades: added for 0x10ADD020
namespace Patches { namespace Camera { extern e_camera_mode GetForcedCameraMode(); } }  // hades: added for 0x10ADD020
namespace Player { namespace PlayerPodium { extern bool PodiumEnabled(); } }  // hades: added for 0x10ADD020

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
namespace Player::ServiceRecord { ServiceRecord getCachedServiceRecord(__int32 networkPlayerIndex); }  // hades: added for 0x10AE14B0
namespace Player::ServiceRecord { void requestPlayerServiceRecord(__int32 networkPlayerIndex); }  // hades: added for 0x10AE5440
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
static HWND__ *CreateGameWindowHook();
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
		std::vector<std::string> speakingPlayers; // 0x12467478
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
	namespace hades_file_local_Ui { extern bool (*IsMapLoading)(); } using namespace hades_file_local_Ui; // 0x11354C84
	extern bool tagsInitiallyLoaded; // 0x1246748C
	extern __int32 localDesiredTeam; // 0x11354C88
	std::vector<std::function<void __cdecl(HWND__ *)> > createWindowCallbacks; // 0x12467468
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


		void ApplyAll() // 0x10AD7390
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Ui@Patches@@YAXXZ");

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

			void *s_UIData = ((void *(__cdecl *)(int))0xab4ed0)(64);
			if (!s_UIData)
			{
				return nullptr;
			}
			((void (__thiscall *)(void *, unsigned long, __int32, __int32, unsigned long))0xa92780)(s_UIData, p_DialogID, p_Arg1, p_Flags, p_ParentID);
			((void (__cdecl *)(void *))0xa93450)(s_UIData);
			return s_UIData;
		}

		void OnCreateWindow(std::function<void __cdecl(HWND__ *)> callback) // 0x10ADCCD0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnCreateWindow@Ui@Patches@@YAXV?$function@$$A6AXPAUHWND__@@@Z@std@@@Z");

			createWindowCallbacks.push_back(callback);
		}

		void TogglePTTSound(bool enabled) // 0x10ADD3E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?TogglePTTSound@Ui@Patches@@YAX_N@Z");

			static void (*Sound_LoopingSound_Stop)(unsigned __int32, __int32) = (void (*)(unsigned __int32, __int32))0x5DC6B0;
			static void (*Sound_LoopingSound_Start)(unsigned __int32, __int32, __int32, __int32, char) = (void (*)(unsigned __int32, __int32, __int32, __int32, char))0x5DC530;
			if (IsMapLoading())
				return;
			if (!Modules::ModuleVoIP::Instance().VarPTTSoundEnabled->ValueInt)
				return;
			if (isPttSoundPlaying == enabled)
				return;
			s_multiplayer_globals_definition *mulg = (s_multiplayer_globals_definition *)tag_get('mulg', (*(s_game_globals **)0x22AAEB8)->MultiplayerGlobals.index);
			if (!mulg)
				return;
			if (mulg->runtime.count < 1 || mulg->runtime[0].looping_sounds.count < 1 || mulg->runtime[0].looping_sounds[0].sound.index == -1)
				return;
			long pttLsndIndex = mulg->runtime[0].looping_sounds[0].sound.index;
			if (tag_try_and_get_and_verify_group('lsnd', pttLsndIndex))
			{
				if (enabled)
					Sound_LoopingSound_Start(pttLsndIndex, -1, 0x3F800000, 0, 0);
				else
					Sound_LoopingSound_Stop(pttLsndIndex, -1);
				isPttSoundPlaying = enabled;
			}
		}

		void ToggleSpeakingPlayerName(std::string name, bool speaking) // 0x10ADD620
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ToggleSpeakingPlayerName@Ui@Patches@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");

			for (unsigned __int32 i = 0; i < speakingPlayers.size(); i++)
			{
				if (speakingPlayers.at(i) == name)
					speakingPlayers.erase(speakingPlayers.begin() + i);
			}
			if (speaking)
				speakingPlayers.push_back(name);
			memset(chud_talking_player_name, 0, sizeof(chud_talking_player_name));
			if (speakingPlayers.size() < 1)
			{
				return;
			}
			else
			{
				if (speakingPlayers[speakingPlayers.size() - 1].length() < 15)
				{
					std::string hud_name = speakingPlayers[speakingPlayers.size() - 1];
					for (unsigned __int32 i = 0; i < hud_name.length(); i++)
						chud_talking_player_name[i] = hud_name[i];
				}
				else
				{
					return;
				}
			}
		}

		void ApplyUIResolution() // 0x10ADB800
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyUIResolution@Ui@Patches@@YAXXZ");

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

	new (thisptr) c_gui_map_category_datasource(recent_maps_item_title, recent_maps_item_description, file_share_item_title, file_share_item_description);
}

void __fastcall c_gui_player_select_screen_widget__set_mute_hook(void *thisPtr, void *unused, bool muted) // 0x10AE10C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_player_select_screen_widget__set_mute_hook@@YIXPAX0_N@Z");

	char (*const user_interface_session_get_player_index)(char *) = reinterpret_cast<char (*)(char *)>(0xA819E0);
	char *player_identifier_local = (char *)thisPtr + 0x1AA0;
	char *player_identifier_selected = (char *)thisPtr + 0x1AA8;
	__int32 source_player_index = user_interface_session_get_player_index(player_identifier_local);
	__int32 destination_player_index = user_interface_session_get_player_index(player_identifier_selected);
	if (source_player_index != -1 && destination_player_index != -1)
	{
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (session && session->IsEstablished())
		{
			Blam::Network::SessionMembership *membership = &session->MembershipInfo;
			Blam::Network::PlayerSession *player = &membership->PlayerSessions[destination_player_index];
			char uid[17];
			player_format_uid(uid, player->Properties.host.player_uid);
			rapidjson::StringBuffer jsonBuffer;
			rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
			jsonWriter.StartObject();
			jsonWriter.Key("name");
			jsonWriter.String(Utils::String::ThinString(player->Properties.host.player_name).c_str());
			jsonWriter.Key("uid");
			jsonWriter.String(uid);
			jsonWriter.Key("muted");
			jsonWriter.Bool(muted);
			jsonWriter.EndObject();
			Web::Ui::ScreenLayer::Notify("mute-voip-player", jsonBuffer.GetString(), true);
		}
	}
}

bool isValidUrl(std::string const &url) // 0x10AE8D10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?isValidUrl@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

	std::regex url_regex("^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\\?([^#]*))?(#(.*))?", std::regex_constants::extended);

	return std::regex_match(url, url_regex);
}

void __fastcall c_gui_player_select_screen_widget__show_service_record_hook(void *thisPtr, void *unused, bool muted) // 0x10AE14B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_player_select_screen_widget__show_service_record_hook@@YIXPAX0_N@Z");

	char (*const user_interface_session_get_player_index)(char *) = reinterpret_cast<char (*)(char *)>(0xA819E0);
	char *player_identifier_local = (char *)thisPtr + 0x1AA0;
	char *player_identifier_selected = (char *)thisPtr + 0x1AA8;
	__int32 local_player_index = user_interface_session_get_player_index(player_identifier_local);
	__int32 player_index = user_interface_session_get_player_index(player_identifier_selected);
	if (player_index == -1)
		return;
	c_network_session *session;
	if (!network_session_interface_get_squad_session(&session))
		return;
	if (!session->get_session_membership()->is_player_valid(player_index))
		return;
	s_network_session_player *player = session->get_session_membership()->get_player(player_index);
	Player::ServiceRecord::ServiceRecord service_record = Player::ServiceRecord::getCachedServiceRecord(player_index);
	if (player && player->configuration.host.player_uid == service_record.uid && !service_record.Empty)
	{
		__int32 statsPlayerID = service_record.playerId;
		if (statsPlayerID <= -1)
			return;
		if (!Utils::DewritoReader::Instance().IsValid())
			return;
		std::string profileUrl = "";
		rapidjson::Document json = Utils::DewritoReader::Instance().GetDewritoJson();
		if (json.IsObject() && json.HasMember("stats"))
		{
			rapidjson::Value &statsObject = json["stats"];
			if (statsObject.HasMember("playerProfile"))
				profileUrl = statsObject["playerProfile"].GetString();
		}
		if (profileUrl != "")
			profileUrl = profileUrl + std::to_string(statsPlayerID);
		Web::Ui::ScreenLayer::SDialogShowParams params;
		params.templateName = "confirm_link";
		params.customBody = "This link goes to " + profileUrl + "|r|nAre you sure you want to open this?";
		params.callback = [profileUrl](std::string const &boxTag)
		{
			if (boxTag == "yes" && profileUrl != "" && isValidUrl(profileUrl))
				ShellExecuteA(NULL, "open", profileUrl.c_str(), "", NULL, SW_SHOWNORMAL);
		};
		Web::Ui::ScreenLayer::ShowDialog(params);
	}
}

bool UserInterfaceSquadSetMap_hook(__int32 a1, __int32 a2, char a3, __int32 a4, __int32 a5, __int32 a6) // 0x10ADDDE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UserInterfaceSquadSetMap_hook@@YA_NHHDHHH@Z");

	long c;
	long m;
	if (((bool(*)(long *, long *))0xA817B0)(&c, &m))
	{
		return false;
	}
	const auto user_interface_squad_set_map = (bool(*)(__int32, __int32, char, __int32, __int32, __int32))0xA83690;
	return user_interface_squad_set_map(a1, 3005, a3, a4, a5, a6);
}

bool AttractShouldStartHook() // 0x10ADB920
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?AttractShouldStartHook@@YA_NXZ");

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

void __fastcall c_gui_location_manager__change_location_hook(c_gui_location_manager *thisptr, void *__formal, unsigned long screen_name) // 0x10AE0B90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_location_manager__change_location_hook@@YIXPAUc_gui_location_manager@@PAXK@Z");

	void (__thiscall *const c_load_screen_message_ctor)(void *, unsigned long, long, long, unsigned long) = reinterpret_cast<void (__thiscall *)(void *, unsigned long, long, long, unsigned long)>(0xA92780);
	void (*const user_interface_messaging_post)(void *) = reinterpret_cast<void (*)(void *)>(0xA93450);
	void *(*const user_interface_malloc)(unsigned __int32) = reinterpret_cast<void *(*)(unsigned __int32)>(0xAB4ED0);
	void (__thiscall *const close_screens)(c_gui_screen_manager *, c_gui_screen_widget **, long) = reinterpret_cast<void (__thiscall *)(c_gui_screen_manager *, c_gui_screen_widget **, long)>(0xAAA870);
	if (system_milliseconds() - thisptr->last_change_location_milliseconds < 500)
		return;
	thisptr->last_change_location_milliseconds = system_milliseconds();
	c_gui_screen_manager *window_manager = c_gui_screen_manager::get();
	c_gui_screen_widget *screen_widget = c_gui_location_manager::get_location_gui_screen();
	long transition_type = 1;
	if (screen_widget)
	{
		if (screen_name == 0x100CF)
		{
			if (screen_widget->m_name == 0x100B2)
				transition_type = 5;
		}
		else if (screen_name == 0x100B2 && screen_widget->m_name == 0x100CF)
		{
			transition_type = 5;
		}
		screen_widget->transition_out_internal(0, transition_type);
	}
	c_gui_screen_widget *screens[7];
	if (screen_name == 0x100CF)
	{
		screens[0] = window_manager->find_screen(4, 0x100C7);
		screens[1] = window_manager->find_screen(4, 0x1006D);
		screens[2] = window_manager->find_screen(4, 0x1006F);
		screens[3] = window_manager->find_screen(4, 0x100A0);
		screens[4] = window_manager->find_screen(4, 0x1009F);
		screens[5] = window_manager->find_screen(4, 0x100A1);
		screens[6] = window_manager->find_screen(4, 0x100A2);
		close_screens(window_manager, screens, 7);
	}
	else
	{
		screens[1] = window_manager->find_screen(4, 0x1006D);
		screens[2] = window_manager->find_screen(4, 0x1006F);
		screens[3] = window_manager->find_screen(4, 0x100A0);
		screens[4] = window_manager->find_screen(4, 0x1009F);
		screens[5] = window_manager->find_screen(4, 0x100A1);
		screens[6] = window_manager->find_screen(4, 0x100A2);
		close_screens(window_manager, &screens[1], 6);
	}
	if (screen_name == -1)
		return;
	void *load_screen_message = user_interface_malloc(60);
	c_load_screen_message_ctor(load_screen_message, screen_name, 255, 4, 0x1000D);
	user_interface_messaging_post(load_screen_message);
	*(long *)offset_pointer(load_screen_message, 24) = transition_type;
	if (screen_name == 0x10083)
		Utils::Singleton<ElDorito>::Instance().OnMainMenuShown();
}

bool __fastcall c_gui_screen_pregame_lobby__handle_controller_input_message_fallback_hook(c_gui_screen_widget *thisptr, void *__formal, c_controller_input_message *message) // 0x10AE3EA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_screen_pregame_lobby__handle_controller_input_message_fallback_hook@@YI_NPAVc_gui_screen_widget@@PAXPAUc_controller_input_message@@@Z");

	bool (__thiscall *const sub_AB1270)(c_gui_screen_widget *, c_controller_input_message *) = (bool(__thiscall *const)(c_gui_screen_widget *, c_controller_input_message *))0xab1270;
	void (__thiscall *const sub_B225B0)(c_gui_screen_widget *, int) = (void(__thiscall *const)(c_gui_screen_widget *, int))0xb225b0;

	if (message->event_type == 13 && message->button == 2)
	{
		sub_B225B0(thisptr, message->controller_index);
		return true;
	}

	return sub_AB1270(thisptr, message);
}

bool __fastcall c_start_menu_settings_handle_list_item_chosen_hook(void *thisptr, void *unused, void *message, unsigned long list_name, c_gui_list_item_widget const *list_item, c_gui_data *data) // 0x10AE8020
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_start_menu_settings_handle_list_item_chosen_hook@@YI_NPAX00KPBVc_gui_list_item_widget@@PAVc_gui_data@@@Z");

	bool (__thiscall *const handle_list_item_chosen)(void *, void *, unsigned long, c_gui_list_item_widget const *, c_gui_data const *) = reinterpret_cast<bool (__thiscall *)(void *, void *, unsigned long, c_gui_list_item_widget const *, c_gui_data const *)>(0xAF73B0);
	unsigned long id;
	if (list_name == 0x10127)
	{
		if (data->get_string_id_value(list_item->get_data_item_index(), 0x2AA, &id))
		{
			char *menuOptionString = Blam::Cache::StringIDCache::GetCurrent()->GetString(id);
			if (!strcmp(menuOptionString, "controls_settings"))
			{
				Web::Ui::ScreenLayer::Show(Web::Ui::ScreenLayer::Settings, "{}");
				return true;
			}
		}
	}
	return handle_list_item_chosen(thisptr, message, list_name, list_item, data);
}

bool __fastcall c_main_menu_screen_widget_handle_list_item_chosen_hook(void *thisptr, void *unused, void *message, unsigned long list_name, c_gui_list_item_widget const *list_item, c_gui_data *data) // 0x10AE4BC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_main_menu_screen_widget_handle_list_item_chosen_hook@@YI_NPAX00KPBVc_gui_list_item_widget@@PAVc_gui_data@@@Z");

	bool (__thiscall *const handle_list_item_chosen)(void *, void *, unsigned long, c_gui_list_item_widget const *, c_gui_data const *) = reinterpret_cast<bool (__thiscall *)(void *, void *, unsigned long, c_gui_list_item_widget const *, c_gui_data const *)>(0xAE77D0);
	if (list_name == 0x10083)
	{
		unsigned long id;
		if (data->get_string_id_value(list_item->get_data_item_index(), 0x2AA, &id))
		{
			char *menuOptionString = Blam::Cache::StringIDCache::GetCurrent()->GetString(id);
			if (!menuOptionString)
				return false;
			if (!strcmp(menuOptionString, "server_browser"))
			{
				Web::Ui::ScreenLayer::Show(Web::Ui::ScreenLayer::Browser, "{}");
				return true;
			}
			if (!strcmp(menuOptionString, "game_browser"))
			{
				Patches::Ui::ShowLanBrowser();
				return true;
			}
			if (!strcmp(menuOptionString, "customization"))
			{
				Web::Ui::ScreenLayer::Show(Web::Ui::ScreenLayer::ProfileSettings, "{}");
				return true;
			}
			if (!strcmp(menuOptionString, "eldewrito_settings"))
			{
				Web::Ui::ScreenLayer::Show(Web::Ui::ScreenLayer::Settings, "{}");
				return true;
			}
			if (!strcmp(menuOptionString, "exit"))
			{
				Web::Ui::ScreenLayer::ShowDialog("exit", [](std::string const &result)
				{
					if (result == "exit")
						Utils::Singleton<Modules::CommandMap>::Instance().ExecuteCommand("Game.Exit", false);
				});
				return true;
			}
		}
	}
	return handle_list_item_chosen(thisptr, message, list_name, list_item, data);
}

void ui_background_set_hook(__int32 index) // 0x10AE9250
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ui_background_set_hook@@YAXH@Z");

	void (*const ui_set_mainmenu_bitmap_texture)(__int32) = reinterpret_cast<void (*)(__int32)>(0xA20310);
	bool (*const bitmap_group_try_get_texture)(long, long, c_rasterizer_texture_ref *) = reinterpret_cast<bool (*)(long, long, c_rasterizer_texture_ref *)>(0x718D10);
	long (__thiscall *const rasterizer_bitmap_get_texture)(void *) = reinterpret_cast<long (__thiscall *)(void *)>(0xA6E8E0);
	Modules::ModuleSettings const &moduleSettings = Utils::Singleton<Modules::ModuleSettings>::Instance();
	s_scenario *scnr = *g_scenario_definition;
	__int32 screenWidth;
	__int32 screenHeight;
	moduleSettings.GetScreenResolution(&screenWidth, &screenHeight);
	double screenRatio = (double)screenHeight / (double)screenWidth;
	if (index == 0xFFFF)
	{
		ui_set_mainmenu_bitmap_texture(0);
		return;
	}
	if (scnr && index >= 0 && index < scnr->background_textures.count)
	{
		unsigned long bitmapTagIndex = ((s_tag_reference *)scnr->background_textures[index].bitmap)->index;
		s_bitmap_definition *bitmap = (s_bitmap_definition *)tag_get('bitm', bitmapTagIndex);
		if (bitmap)
		{
			__int32 closestIndex = 0;
			double closestAspect = 1.0;
			for (__int32 x = 0; x < bitmap->images.count; x++)
			{
				double imageAspectRatio = (double)bitmap->images[x].height / bitmap->images[x].width;
				double diff = abs(screenRatio - imageAspectRatio);
				if (closestAspect > diff)
				{
					closestAspect = diff;
					closestIndex = x;
				}
				if (imageAspectRatio == screenRatio)
				{
					c_rasterizer_texture_ref texture_ref(-1);
					if (bitmap_group_try_get_texture(bitmapTagIndex, x, &texture_ref))
					{
						__int32 texture = rasterizer_bitmap_get_texture(&texture_ref);
						if (texture)
						{
							ui_set_mainmenu_bitmap_texture(texture);
							return;
						}
					}
				}
			}
			if (closestAspect <= 0.15)
			{
				c_rasterizer_texture_ref texture_ref(-1);
				if (bitmap_group_try_get_texture(bitmapTagIndex, closestIndex, &texture_ref))
				{
					__int32 texture = rasterizer_bitmap_get_texture(&texture_ref);
					if (texture)
					{
						ui_set_mainmenu_bitmap_texture(texture);
						return;
					}
				}
			}
			else
			{
				c_rasterizer_texture_ref texture_ref(-1);
				if (bitmap_group_try_get_texture(bitmapTagIndex, 0, &texture_ref))
				{
					__int32 texture = rasterizer_bitmap_get_texture(&texture_ref);
					if (texture)
					{
						ui_set_mainmenu_bitmap_texture(texture);
						return;
					}
				}
				else
				{
					ui_set_mainmenu_bitmap_texture(0);
				}
			}
		}
	}
}

void user_interface_networking_notify_booted_from_session_hook(__int32 a1, e_network_session_boot_reason reason) // 0x10AE97E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?user_interface_networking_notify_booted_from_session_hook@@YAXHW4e_network_session_boot_reason@@@Z");

	__int32 (__thiscall *const c_gui_error_manager__post_error)(void *, unsigned long, __int32, bool) = reinterpret_cast<__int32 (__thiscall *)(void *, unsigned long, __int32, bool)>(0xA91FB0);
	__int32 (*const sub_A81280)(__int32) = reinterpret_cast<__int32 (*)(__int32)>(0xA81280);
	char (*const sub_A92540)() = reinterpret_cast<char (*)()>(0xA92540);
	unsigned long reasonStringID;
	switch (reason)
	{
	case 0:
		reasonStringID = 0x2000A;
		break;
	case 4:
		reasonStringID = 0x2000B;
		break;
	case 13:
		Web::Ui::ScreenLayer::ShowAlert("Banned", "You are Banned.", (Web::Ui::ScreenLayer::AlertIcon)0, 0.0f);
		sub_A81280(0);
		return;
	case 14:
		Web::Ui::ScreenLayer::ShowAlert("Temporarily Banned", "You are temporarily Banned.", (Web::Ui::ScreenLayer::AlertIcon)0, 0.0f);
		sub_A81280(0);
		return;
	case 15:
		Web::Ui::ScreenLayer::ShowAlert("DUPLICATE USER ID", "Another user's ID conflicts with yours.", (Web::Ui::ScreenLayer::AlertIcon)0, 0.0f);
		sub_A81280(0);
		return;
	default:
		return;
	}
	char (*v3)() = sub_A92540;
	c_gui_error_manager__post_error(v3, reasonStringID, 0xFF, false);
	sub_A81280(0);
}

void __fastcall c_start_menu_screen_widget__update_render_state_hook(c_gui_screen_widget *thisptr, void *__formal, unsigned long milliseconds) // 0x10AE7D10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_start_menu_screen_widget__update_render_state_hook@@YIXPAVc_gui_screen_widget@@PAXK@Z");

	void (__thiscall *const c_start_menu_screen_widget__update_render_state)(void *, unsigned long) = reinterpret_cast<void (__thiscall *)(void *, unsigned long)>(0xAE1660);
	void (__thiscall *UI_Widget_MultiplyColor)(void *, float *) = reinterpret_cast<void (__thiscall *)(void *, float *)>(0xAB9D70);
	void (*UI_ColorWidgetWithPlayerColor)(void *, __int32, bool) = reinterpret_cast<void (*)(void *, __int32, bool)>(0xAA4C80);
	void (*RgbToFloatColor)(unsigned long, float *) = reinterpret_cast<void (*)(unsigned long, float *)>(0x521300);
	static bool teamsEnabled = false;
	static float color[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
	static __int32 team_index = -1;
	c_start_menu_screen_widget__update_render_state(thisptr, milliseconds);
	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session)
		return;
	if (session->IsEstablished())
		teamsEnabled = session->HasTeams();
	__int32 localPlayerIndex = session->MembershipInfo.GetPeerPlayer(session->MembershipInfo.LocalPeerIndex);
	c_gui_bitmap_widget *base_color = thisptr->get_child_bitmap_widget(0x10144);
	if (base_color)
	{
		c_network_session *squad_session;
		if (localPlayerIndex != -1 && network_session_interface_get_squad_session(&squad_session) && squad_session->get_session_membership()->is_player_valid(localPlayerIndex))
		{
			s_network_session_player *player = squad_session->get_session_membership()->get_player(localPlayerIndex);
			unsigned long nameplate_color = player->configuration.host.appearance.nameplate_color;
			if (!((bool (*)())0x531E90)())
				nameplate_color = player->configuration.host.appearance.model_customization.colors[0];
			RgbToFloatColor(nameplate_color, &color[1]);
			if (teamsEnabled)
				team_index = player->configuration.host.team;
		}
		if (!teamsEnabled)
			UI_Widget_MultiplyColor(base_color, color);
		else
			UI_ColorWidgetWithPlayerColor(base_color, team_index, true);
	}
}

void __fastcall c_start_menu_screen_widget__post_initialize_hook(c_gui_screen_widget *thisptr, void *unused) // 0x10AE7C40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_start_menu_screen_widget__post_initialize_hook@@YIXPAVc_gui_screen_widget@@PAX@Z");

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

void c_gui_spartan_rank_widget__update_sub_hook(c_gui_widget *widget, long in_rank, long in_grade) // 0x10AE44C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_spartan_rank_widget__update_sub_hook@@YAXPAVc_gui_widget@@JJ@Z");

	void (*const c_gui_spartan_rank_widget_update_sub)(c_gui_widget *, long, long) = reinterpret_cast<void (*)(c_gui_widget *, long, long)>(0xAFC170);
	__int32 (*const user_interface_session_get_player_index)(char *) = reinterpret_cast<__int32 (*)(char *)>(0xA819E0);
	void (*UI_Widget_MultiplyColor)(void *, __int32, float *) = reinterpret_cast<void (*)(void *, __int32, float *)>(0xAB9D70);
	void (*UI_ColorWidgetWithPlayerColor)(void *, __int32, bool) = reinterpret_cast<void (*)(void *, __int32, bool)>(0xAA4C80);
	void (*RgbToFloatColor)(unsigned long, float *) = reinterpret_cast<void (*)(unsigned long, float *)>(0x521300);
	c_gui_spartan_rank_widget_update_sub(widget, in_rank, in_grade);
	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session)
		return;
	__int32 localPlayerIndex = session->MembershipInfo.GetPeerPlayer(session->MembershipInfo.LocalPeerIndex);
	__int32 rank = GetPlayerRankIndex(localPlayerIndex);
	c_gui_bitmap_widget *rank_image = widget->get_child_bitmap_widget(0x408);
	if (widget->get_name_string_id() == 0x10072)
	{
		std::wstring rank_name = GetRankName(rank - 1);
		widget->set_text_widget_text(0x2AB, rank_name.c_str());
		if (rank_image)
			rank_image->set_sprite_frame_index(rank - 1);
	}
	if (widget->get_name_string_id() == 0x10073)
	{
		std::wstring rank_name = GetRankName(rank);
		widget->set_text_widget_text(0x2AB, rank_name.c_str());
		if (rank_image)
			rank_image->set_sprite_frame_index(rank);
	}
}

void __fastcall c_spartan_rank_widget__update_render_state_hook(c_gui_screen_widget *thisptr, void *unused, unsigned long milliseconds) // 0x10AE75D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_spartan_rank_widget__update_render_state_hook@@YIXPAVc_gui_screen_widget@@PAXK@Z");

	static bool teamsEnabled = false;
	static __int32 team_index = -1;
	static float rank_nameplate_color[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
	void (__thiscall *const c_gui_spartan_rank__update_render_state)(void *, unsigned long) = reinterpret_cast<void (__thiscall *)(void *, unsigned long)>(0xAFC270);
	__int32 (*const user_interface_session_get_player_index)(char *) = reinterpret_cast<__int32 (*)(char *)>(0xA819E0);
	void (__fastcall *UI_Widget_MultiplyColor)(void *, __int32, float *) = reinterpret_cast<void (__fastcall *)(void *, __int32, float *)>(0xAB9D70);
	void (*UI_ColorWidgetWithPlayerColor)(void *, __int32, bool) = reinterpret_cast<void (*)(void *, __int32, bool)>(0xAA4C80);
	void (*RgbToFloatColor)(unsigned long, float *) = reinterpret_cast<void (*)(unsigned long, float *)>(0x521300);
	c_gui_spartan_rank__update_render_state(thisptr, milliseconds);
	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	thisptr->focused_widget = thisptr;
	if (!session)
		return;
	if (session->IsEstablished())
		teamsEnabled = session->HasTeams();
	__int32 localPlayerIndex = session->MembershipInfo.GetPeerPlayer(session->MembershipInfo.LocalPeerIndex);
	c_gui_bitmap_widget *base_color = thisptr->get_child_bitmap_widget(0x10144);
	if (base_color)
	{
		{
			c_network_session *squad_session;
			if (localPlayerIndex != -1 && network_session_interface_get_squad_session(&squad_session) && squad_session->get_session_membership()->is_player_valid(localPlayerIndex))
			{
				s_network_session_player *player = squad_session->get_session_membership()->get_player(localPlayerIndex);
				unsigned long nameplate_color = player->configuration.host.appearance.nameplate_color;
				RgbToFloatColor(nameplate_color, &rank_nameplate_color[1]);
				if (teamsEnabled)
					team_index = player->configuration.host.team;
			}
		}
		if (!teamsEnabled)
			UI_Widget_MultiplyColor(base_color, 0, rank_nameplate_color);
		else
			UI_ColorWidgetWithPlayerColor(base_color, team_index, true);
	}
	c_network_session *squad_session;
	if (localPlayerIndex != -1 && network_session_interface_get_squad_session(&squad_session) && squad_session->get_session_membership()->is_player_valid(localPlayerIndex))
	{
		c_gui_list_item_widget *player_name_widget = thisptr->get_child_text_widget(0x2BC);
		if (player_name_widget)
		{
			s_network_session_player *player = squad_session->get_session_membership()->get_player(localPlayerIndex);
			thisptr->set_text_widget_text(0x2BC, player->configuration.host.player_name);
		}
		c_gui_list_item_widget *service_tag_widget = thisptr->get_child_text_widget(0x103F2);
		if (service_tag_widget)
		{
			s_network_session_player *player = squad_session->get_session_membership()->get_player(localPlayerIndex);
			thisptr->set_text_widget_text(0x103F2, player->configuration.host.appearance.service_tag);
		}
	}
}

void c_player_select_actions_datasource__add_action(c_player_select_actions_datasource *result, __int32 stringid, bool enabled) // 0x10AE4FB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_select_actions_datasource__add_action@@YAXPAUc_player_select_actions_datasource@@H_N@Z");

	__int32 button_index = result->button_count;
	if (button_index < 8)
		result->buttons[button_index] = stringid;
	result->button_count++;
}

bool c_gui_screen_pregame_lobby__squad_party_leader_hook(void *thisptr, wchar_t *buffer, unsigned __int32 length) // 0x10AE3F60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_screen_pregame_lobby__squad_party_leader_hook@@YA_NPAXPA_WI@Z");

	bool (*const user_interface_squad_exists)() = reinterpret_cast<bool (*)()>(0xA82980);
	__int32 (*const user_interface_squad_leader_get_player_index)() = reinterpret_cast<__int32 (*)()>(0xA82BE0);
	s_player_configuration *(*const user_interface_squad_get_player_data)(__int32) = reinterpret_cast<s_player_configuration *(*)(__int32)>(0xA82EC0);
	wchar_t *(*const ustrnzcpy)(wchar_t *, wchar_t const *, long) = reinterpret_cast<wchar_t *(*)(wchar_t *, wchar_t const *, long)>(0x4ECCD0);
	std::wstring host_name;
	if (Utils::Singleton<Modules::ModuleServer>::Instance().VarServerDedicatedClient->ValueInt == 1)
	{
		host_name = Utils::String::WidenString(Utils::Singleton<Modules::ModuleServer>::Instance().VarServerHostClient->ValueString);
		if (!host_name.size())
			return false;
	}
	else
	{
		__int32 host_index = user_interface_squad_leader_get_player_index();
		s_player_configuration *player = user_interface_squad_get_player_data(host_index);
		if (!user_interface_squad_exists() || host_index == -1)
			return false;
		host_name = player->host.player_name;
	}
	ustrnzcpy(buffer, host_name.c_str(), length > 32 ? 32 : length);
	return true;
}

void __fastcall c_player_select_actions_datasource__initialize_hook(c_player_select_actions_datasource *thisptr) // 0x10AE5010
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_select_actions_datasource__initialize_hook@@YIXPAUc_player_select_actions_datasource@@@Z");

	__int32 (*const user_interface_session_get_player_index)(void *) = reinterpret_cast<__int32 (*)(void *)>(0xA819E0);
	__int32 (*const user_interface_squad_get_player_index)(void *) = reinterpret_cast<__int32 (*)(void *)>(0xA82F90);
	bool (*const user_interface_interactive_session_is_group)() = reinterpret_cast<bool (*)()>(0xA811F0);
	bool (*const user_interface_squad_local_peer_is_leader)() = reinterpret_cast<bool (*)()>(0xA83520);
	bool (*const user_interface_group_is_local_player)(__int32) = reinterpret_cast<bool (*)(__int32)>(0xA81DF0);
	bool (*const user_interface_group_is_player_valid)(__int32) = reinterpret_cast<bool (*)(__int32)>(0xA81E80);
	bool (*const game_options_is_valid)() = reinterpret_cast<bool (*)()>(0x532650);
	bool (*const game_is_theater)() = reinterpret_cast<bool (*)()>(0x531D10);
	bool (*const user_interface_squad_is_booting_allowed)() = reinterpret_cast<bool (*)()>(0xA83300);
	thisptr->button_count = 0;
	if (reinterpret_cast<bool (*const)()>(0x5314B0)() && reinterpret_cast<bool (*const)()>(0x531E90)())
	{
		__int32 source_player_index = user_interface_session_get_player_index(&thisptr->player_identifer1);
		__int32 destination_player_index = user_interface_session_get_player_index(&thisptr->player_identifer2);
		__int32 local_player_squad_index = user_interface_squad_get_player_index(&thisptr->player_identifer2);
		bool player2_is_local = destination_player_index != -1 ? user_interface_group_is_local_player(destination_player_index) : false;
		bool player3_is_valid = local_player_squad_index != -1 ? user_interface_group_is_player_valid(local_player_squad_index) : false;
		bool selected_self = memcmp(&thisptr->player_identifer1, &thisptr->player_identifer2, 8) == 0;
		bool is_host_player = !user_interface_interactive_session_is_group() && user_interface_squad_local_peer_is_leader();
		c_player_select_actions_datasource__add_action(thisptr, 0x1001C, true);
		if (is_host_player && player3_is_valid && !player2_is_local && user_interface_squad_is_booting_allowed())
			c_player_select_actions_datasource__add_action(thisptr, 0x125, true);
		if (game_options_is_valid() && !game_is_theater() && source_player_index != -1 && destination_player_index != -1 && !selected_self && !player2_is_local)
		{
			bool player_is_muted = (Utils::Singleton<Modules::ModuleVoIP>::Instance().playersMuted & (1 << destination_player_index)) ? true : false;
			c_player_select_actions_datasource__add_action(thisptr, player_is_muted ? 0x124 : 0x123, true);
		}
	}
}

void __fastcall c_player_select_screen_widget__update_render_state_hook(c_gui_screen_widget *thisptr, void *unused, unsigned long milliseconds) // 0x10AE7140
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_select_screen_widget__update_render_state_hook@@YIXPAVc_gui_screen_widget@@PAXK@Z");

	void (__thiscall *const c_player_select_screen_widget__update_render_state)(void *, unsigned long) = reinterpret_cast<void (__thiscall *)(void *, unsigned long)>(0xB0A670);
	__int32 (*const user_interface_session_get_player_index)(char *) = reinterpret_cast<__int32 (*)(char *)>(0xA819E0);
	void (__fastcall *UI_Widget_MultiplyColor)(void *, __int32, float *) = reinterpret_cast<void (__fastcall *)(void *, __int32, float *)>(0xAB9D70);
	void (*UI_ColorWidgetWithPlayerColor)(void *, __int32, bool) = reinterpret_cast<void (*)(void *, __int32, bool)>(0xAA4C80);
	void (*RgbToFloatColor)(unsigned long, float *) = reinterpret_cast<void (*)(unsigned long, float *)>(0x521300);
	c_player_select_screen_widget__update_render_state(thisptr, milliseconds);
	char *player_identifier_local = (char *)thisptr + 0x1AA0;
	char *player_identifier_selected = (char *)thisptr + 0x1AA8;
	__int32 local_player_index = user_interface_session_get_player_index(player_identifier_local);
	__int32 player_index = user_interface_session_get_player_index(player_identifier_selected);
	if (player_index == -1)
		return;
	bool teamsEnabled = false;
	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (session && session->IsEstablished())
		teamsEnabled = session->HasTeams();
	c_gui_bitmap_widget *base_color = thisptr->get_child_bitmap_widget(0x10144);
	if (base_color && player_index != -1)
	{
		c_network_session *squad_session;
		if (network_session_interface_get_squad_session(&squad_session) && squad_session->get_session_membership()->is_player_valid(player_index))
		{
			s_network_session_player *player = squad_session->get_session_membership()->get_player(player_index);
			unsigned long nameplate_color = player->configuration.host.appearance.nameplate_color;
			float color[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
			RgbToFloatColor(nameplate_color, &color[1]);
			if (!teamsEnabled)
				UI_Widget_MultiplyColor(base_color, 0, color);
			else
				UI_ColorWidgetWithPlayerColor(base_color, player->configuration.host.team, true);
		}
	}
}

void gui_widget_set_visible_safe(c_gui_widget *item, bool visibility) // 0x10AE8BE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?gui_widget_set_visible_safe@@YAXPAVc_gui_widget@@_N@Z");

	if (item)
	{
		item->set_visible(visibility);
	}
}

void __fastcall c_player_select_screen_widget__update_hook(c_gui_screen_widget *thisptr, void *unused, unsigned long milliseconds) // 0x10AE5440
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_select_screen_widget__update_hook@@YIXPAVc_gui_screen_widget@@PAXK@Z");

	char (__thiscall *const c_player_select_screen_widget__update)(void *, unsigned long) = (char (__thiscall *)(void *, unsigned long))0xB0A1D0;
	__int32 (*const user_interface_session_get_player_index)(char *) = (__int32 (*)(char *))0xA819E0;
	char *player_identifier_local = (char *)thisptr + 0x1AA0;
	char *player_identifier_selected = (char *)thisptr + 0x1AA8;
	__int32 local_player_index = user_interface_session_get_player_index(player_identifier_local);
	__int32 player_index = user_interface_session_get_player_index(player_identifier_selected);
	c_player_select_screen_widget__update(thisptr, milliseconds);
	if (player_index == -1)
		return;
	c_gui_bitmap_widget *emblem_widget = thisptr->get_child_bitmap_widget(0x3F9E);
	if (emblem_widget)
		emblem_widget->set_sprite_frame_index(player_index | 0x8000);
	__int32 rank = GetPlayerRankIndex(player_index);
	c_gui_bitmap_widget *rank_widget = thisptr->get_child_bitmap_widget(0x103E1);
	if (rank_widget)
		rank_widget->set_sprite_frame_index(rank);
	c_gui_bitmap_widget *difficulty_widget = thisptr->get_child_bitmap_widget(0x285);
	if (difficulty_widget)
		difficulty_widget->set_sprite_frame_index(3);
	std::wstring rank_name = GetRankName(rank);
	thisptr->set_text_widget_text(0x103CE, rank_name.c_str());
	std::wstring rank_grade_name = GetRankGradeName(rank);
	thisptr->set_text_widget_text(0x103CF, rank_grade_name.c_str());
	c_network_session *session;
	if (!network_session_interface_get_squad_session(&session))
		return;
	if (!session->get_session_membership()->is_player_valid(player_index))
		return;
	s_network_session_player *player = session->get_session_membership()->get_player(player_index);
	if (!player)
		return;
	thisptr->set_text_widget_text(0x103F2, player->configuration.host.appearance.service_tag);
	c_gui_list_item_widget *service_record_exp = thisptr->get_child_text_widget(0x9C0F);
	c_gui_list_item_widget *service_record_skill = thisptr->get_child_text_widget(0x9C10);
	c_gui_list_item_widget *service_record_games = thisptr->get_child_text_widget(0x9C11);
	c_gui_list_item_widget *service_record_wins = thisptr->get_child_text_widget(0x9C12);
	c_gui_list_item_widget *service_record_kills = thisptr->get_child_text_widget(0x9C13);
	c_gui_list_item_widget *service_record_deaths = thisptr->get_child_text_widget(0x9C14);
	c_gui_list_item_widget *service_record_medals = thisptr->get_child_text_widget(0x9C15);
	c_gui_list_item_widget *service_record_streak = thisptr->get_child_text_widget(0x9C16);
	c_gui_list_item_widget *service_record_value_column = thisptr->get_child_text_widget(0x9C17);
	c_gui_bitmap_widget *medal_1 = thisptr->get_child_bitmap_widget(0x9C18);
	c_gui_list_item_widget *medal_1_count = thisptr->get_child_text_widget(0x9C20);
	c_gui_bitmap_widget *medal_2 = thisptr->get_child_bitmap_widget(0x9C19);
	c_gui_list_item_widget *medal_2_count = thisptr->get_child_text_widget(0x9C21);
	c_gui_bitmap_widget *medal_3 = thisptr->get_child_bitmap_widget(0x9C1A);
	c_gui_list_item_widget *medal_3_count = thisptr->get_child_text_widget(0x9C22);
	c_gui_bitmap_widget *medal_4 = thisptr->get_child_bitmap_widget(0x9C1B);
	c_gui_list_item_widget *medal_4_count = thisptr->get_child_text_widget(0x9C23);
	c_gui_bitmap_widget *medal_5 = thisptr->get_child_bitmap_widget(0x9C1C);
	c_gui_list_item_widget *medal_5_count = thisptr->get_child_text_widget(0x9C24);
	c_gui_bitmap_widget *medal_6 = thisptr->get_child_bitmap_widget(0x9C1D);
	c_gui_list_item_widget *medal_6_count = thisptr->get_child_text_widget(0x9C25);
	c_gui_bitmap_widget *medal_7 = thisptr->get_child_bitmap_widget(0x9C1E);
	c_gui_list_item_widget *medal_7_count = thisptr->get_child_text_widget(0x9C26);
	c_gui_bitmap_widget *medal_8 = thisptr->get_child_bitmap_widget(0x9C1F);
	c_gui_list_item_widget *medal_8_count = thisptr->get_child_text_widget(0x9C27);
	c_gui_bitmap_widget *loading_ring_1 = thisptr->get_child_bitmap_widget(0x9C28);
	c_gui_bitmap_widget *loading_ring_2 = thisptr->get_child_bitmap_widget(0x9C29);
	c_gui_bitmap_widget *loading_ring_3 = thisptr->get_child_bitmap_widget(0x9C2A);
	Player::ServiceRecord::ServiceRecord service_record = Player::ServiceRecord::getCachedServiceRecord(player_index);
	if (player->configuration.host.player_uid == service_record.uid && !service_record.Empty)
	{
		if (loading_ring_1)
			loading_ring_1->set_visible(false);
		if (loading_ring_2)
			loading_ring_2->set_visible(false);
		if (loading_ring_3)
			loading_ring_3->set_visible(false);
		if (service_record_exp)
		{
			std::wstring exp = L"<color argb=#ff76a1d3>TOTAL EXP:</color> " + std::to_wstring(service_record.exp);
			service_record_exp->set_text_widget_text(0x9C0F, exp.c_str());
			service_record_exp->set_visible(true);
		}
		if (service_record_skill)
		{
			std::wstring skill = L"<color argb=#ff76a1d3>HIGHEST SKILL:</color> " + std::to_wstring(service_record.skill);
			service_record_skill->set_text_widget_text(0x9C10, skill.c_str());
			service_record_skill->set_visible(true);
		}
		if (service_record_games)
		{
			std::wstring games = L"<color argb=#ff76a1d3>TOTAL GAMES:</color> " + std::to_wstring(service_record.games);
			service_record_games->set_text_widget_text(0x9C11, games.c_str());
			service_record_games->set_visible(true);
		}
		if (service_record_wins)
		{
			std::wstring wins = L"<color argb=#ff76a1d3>TOTAL WINS:</color> " + std::to_wstring(service_record.wins);
			service_record_wins->set_text_widget_text(0x9C12, wins.c_str());
			service_record_wins->set_visible(true);
		}
		if (service_record_kills)
		{
			std::wstring kills = L"<color argb=#ff76a1d3>TOTAL KILLS:</color> " + std::to_wstring(service_record.kills);
			service_record_kills->set_text_widget_text(0x9C13, kills.c_str());
			service_record_kills->set_visible(true);
		}
		if (service_record_deaths)
		{
			std::wstring deaths = L"<color argb=#ff76a1d3>TOTAL DEATHS:</color> " + std::to_wstring(service_record.deaths);
			service_record_deaths->set_text_widget_text(0x9C14, deaths.c_str());
			service_record_deaths->set_visible(true);
		}
		if (service_record_medals)
		{
			std::wstring medals = L"<color argb=#ff76a1d3>TOTAL MEDALS:</color> " + std::to_wstring(service_record.medals);
			service_record_medals->set_text_widget_text(0x9C15, medals.c_str());
			service_record_medals->set_visible(true);
		}
		if (service_record_streak)
		{
			std::wstring streak = L"<color argb=#ff76a1d3>BEST STREAK:</color> " + std::to_wstring(service_record.best_streak);
			service_record_streak->set_text_widget_text(0x9C16, streak.c_str());
			service_record_streak->set_visible(true);
		}
		if (service_record_value_column)
		{
			std::wstring value_column = std::to_wstring(service_record.ranked_matches) + L"|n" + std::to_wstring(service_record.social_matches) + L"|n" + std::to_wstring(service_record.custom_games);
			service_record_value_column->set_text_widget_text(0x9C17, value_column.c_str());
			service_record_value_column->set_visible(true);
		}
		if (medal_1 && medal_1_count && service_record.top_medals[0].count > 0)
		{
			medal_1->set_sprite_frame_index(service_record.top_medals[0].id);
			medal_1->set_visible(true);
			std::wstring count = service_record.top_medals[0].countStr;
			medal_1_count->set_text_widget_text(0x9C20, count.c_str());
			medal_1_count->set_visible(true);
		}
		else
		{
			gui_widget_set_visible_safe(medal_1, false);
			gui_widget_set_visible_safe(medal_1_count, false);
		}
		if (medal_2 && medal_2_count && service_record.top_medals[1].count > 0)
		{
			medal_2->set_sprite_frame_index(service_record.top_medals[1].id);
			medal_2->set_visible(true);
			std::wstring count = service_record.top_medals[1].countStr;
			medal_2_count->set_text_widget_text(0x9C21, count.c_str());
			medal_2_count->set_visible(true);
		}
		else
		{
			gui_widget_set_visible_safe(medal_2, false);
			gui_widget_set_visible_safe(medal_2_count, false);
		}
		if (medal_3 && medal_3_count && service_record.top_medals[2].count > 0)
		{
			medal_3->set_sprite_frame_index(service_record.top_medals[2].id);
			medal_3->set_visible(true);
			std::wstring count = service_record.top_medals[2].countStr;
			medal_3_count->set_text_widget_text(0x9C22, count.c_str());
			medal_3_count->set_visible(true);
		}
		else
		{
			gui_widget_set_visible_safe(medal_3, false);
			gui_widget_set_visible_safe(medal_3_count, false);
		}
		if (medal_4 && medal_4_count && service_record.top_medals[3].count > 0)
		{
			medal_4->set_sprite_frame_index(service_record.top_medals[3].id);
			medal_4->set_visible(true);
			std::wstring count = service_record.top_medals[3].countStr;
			medal_4_count->set_text_widget_text(0x9C23, count.c_str());
			medal_4_count->set_visible(true);
		}
		else
		{
			gui_widget_set_visible_safe(medal_4, false);
			gui_widget_set_visible_safe(medal_4_count, false);
		}
		if (medal_5 && medal_5_count && service_record.top_medals[4].count > 0)
		{
			medal_5->set_sprite_frame_index(service_record.top_medals[4].id);
			medal_5->set_visible(true);
			std::wstring count = service_record.top_medals[4].countStr;
			medal_5_count->set_text_widget_text(0x9C24, count.c_str());
			medal_5_count->set_visible(true);
		}
		else
		{
			gui_widget_set_visible_safe(medal_5, false);
			gui_widget_set_visible_safe(medal_5_count, false);
		}
		if (medal_6 && medal_6_count && service_record.top_medals[5].count > 0)
		{
			medal_6->set_sprite_frame_index(service_record.top_medals[5].id);
			medal_6->set_visible(true);
			std::wstring count = service_record.top_medals[5].countStr;
			medal_6_count->set_text_widget_text(0x9C25, count.c_str());
			medal_6_count->set_visible(true);
		}
		else
		{
			gui_widget_set_visible_safe(medal_6, false);
			gui_widget_set_visible_safe(medal_6_count, false);
		}
		if (medal_7 && medal_7_count && service_record.top_medals[6].count > 0)
		{
			medal_7->set_sprite_frame_index(service_record.top_medals[6].id);
			medal_7->set_visible(true);
			std::wstring count = service_record.top_medals[6].countStr;
			medal_7_count->set_text_widget_text(0x9C26, count.c_str());
			medal_7_count->set_visible(true);
		}
		else
		{
			gui_widget_set_visible_safe(medal_7, false);
			gui_widget_set_visible_safe(medal_7_count, false);
		}
		if (medal_8 && medal_8_count && service_record.top_medals[7].count > 0)
		{
			medal_8->set_sprite_frame_index(service_record.top_medals[7].id);
			medal_8->set_visible(true);
			std::wstring count = service_record.top_medals[7].countStr;
			medal_8_count->set_text_widget_text(0x9C27, count.c_str());
			medal_8_count->set_visible(true);
		}
		else
		{
			gui_widget_set_visible_safe(medal_8, false);
			gui_widget_set_visible_safe(medal_8_count, false);
		}
	}
	else
	{
		if (loading_ring_1)
			loading_ring_1->set_visible(true);
		if (loading_ring_2)
			loading_ring_2->set_visible(true);
		if (loading_ring_3)
			loading_ring_3->set_visible(true);
		gui_widget_set_visible_safe(service_record_exp, false);
		gui_widget_set_visible_safe(service_record_skill, false);
		gui_widget_set_visible_safe(service_record_games, false);
		gui_widget_set_visible_safe(service_record_wins, false);
		gui_widget_set_visible_safe(service_record_kills, false);
		gui_widget_set_visible_safe(service_record_deaths, false);
		gui_widget_set_visible_safe(service_record_medals, false);
		gui_widget_set_visible_safe(service_record_streak, false);
		gui_widget_set_visible_safe(service_record_value_column, false);
		gui_widget_set_visible_safe(medal_1, false);
		gui_widget_set_visible_safe(medal_1_count, false);
		gui_widget_set_visible_safe(medal_2, false);
		gui_widget_set_visible_safe(medal_2_count, false);
		gui_widget_set_visible_safe(medal_3, false);
		gui_widget_set_visible_safe(medal_3_count, false);
		gui_widget_set_visible_safe(medal_4, false);
		gui_widget_set_visible_safe(medal_4_count, false);
		gui_widget_set_visible_safe(medal_5, false);
		gui_widget_set_visible_safe(medal_5_count, false);
		gui_widget_set_visible_safe(medal_6, false);
		gui_widget_set_visible_safe(medal_6_count, false);
		gui_widget_set_visible_safe(medal_7, false);
		gui_widget_set_visible_safe(medal_7_count, false);
		gui_widget_set_visible_safe(medal_8, false);
		gui_widget_set_visible_safe(medal_8_count, false);
		if (player->configuration.host.player_uid != service_record.uid || !service_record.Empty)
			Player::ServiceRecord::requestPlayerServiceRecord(player_index);
	}
}

void __fastcall c_gui_roster_list_widget_update_hook(c_gui_screen_widget *thisptr, void *unused, unsigned long milliseconds) // 0x10AE2460
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_roster_list_widget_update_hook@@YIXPAVc_gui_screen_widget@@PAXK@Z");

	long (__thiscall *const c_gui_list_item_widget__get_element_handle)(void *) = (long (__thiscall *)(void *))0xB184A0;
	char (__thiscall *const c_gui_roster_data__get_integer_value)(void *, long, unsigned long, long *) = (char (__thiscall *)(void *, long, unsigned long, long *))0xB24CA0;
	void *(__thiscall *const c_gui_list_widget__get_data)(void *) = (void *(__thiscall *)(void *))0xB14FE0;
	__int32 (__thiscall *const sub_B25B30)(void *, __int32) = (__int32 (__thiscall *)(void *, __int32))0xB25B30;
	char *(*const ui_resolve_string)(unsigned __int32, unsigned __int32, __int32) = (char *(*)(unsigned __int32, unsigned __int32, __int32))0x51E290;
	__int32 (*const ui_get_prefered_lanquage)() = (__int32 (*)())0x52FC40;
	static void (__thiscall *c_gui_roster_list_widget_update)(void *, unsigned long) = (void (__thiscall *)(void *, unsigned long))0xB25C60;
	c_gui_roster_list_widget_update(thisptr, milliseconds);
	void *data = c_gui_list_widget__get_data(thisptr);
	if (!data)
		return;
	c_gui_widget *item = thisptr->find_first_child((e_gui_widget)5);
	while (item)
	{
		c_gui_bitmap_widget *rank_widget = item->get_child_bitmap_widget(0x103E1);
		c_gui_bitmap_widget *rank_hilite_widget = item->get_child_bitmap_widget(0x103E2);
		c_gui_bitmap_widget *skill_level_widget = item->get_child_bitmap_widget(0x103DF);
		c_gui_bitmap_widget *skill_level_hilite_widget = item->get_child_bitmap_widget(0x103E0);
		c_gui_bitmap_widget *voice_widget = item->get_child_bitmap_widget(0x1000B);
		c_gui_bitmap_widget *base_color_widget = item->get_child_bitmap_widget(0x10144);
		c_gui_bitmap_widget *base_color_hilite_widget = item->get_child_bitmap_widget(0x103DD);
		c_gui_bitmap_widget *nameplateWidget = item->get_child_bitmap_widget(0x9BF8);
		c_gui_bitmap_widget *nameplateWidget_hilite = item->get_child_bitmap_widget(0x9BF9);
		c_gui_bitmap_widget *player_emblem_widget = item->get_child_bitmap_widget(0x103DB);
		c_gui_bitmap_widget *player_emblem_hilite_widget = item->get_child_bitmap_widget(0x103DC);
		c_gui_bitmap_widget *player_joining_widget = item->get_child_bitmap_widget(0x103EA);
		c_gui_bitmap_widget *player_joining_hilite_widget = item->get_child_bitmap_widget(0x9BAB);
		c_gui_bitmap_widget *rank_tray_widget = item->get_child_bitmap_widget(0x103EB);
		c_gui_bitmap_widget *rank_tray_hilite_widget = item->get_child_bitmap_widget(0x103EC);
		c_gui_list_item_widget *player_name_widget = item->get_child_text_widget(0x2AA);
		c_gui_list_item_widget *player_name_hilite_widget = item->get_child_text_widget(0x103DA);
		c_gui_list_item_widget *player_service_tag_widget = item->get_child_text_widget(0x103F2);
		c_gui_list_item_widget *player_joining_text_widget = item->get_child_text_widget(0x103EA);
		gui_widget_set_visible_safe(player_joining_widget, false);
		gui_widget_set_visible_safe(player_joining_text_widget, false);
		gui_widget_set_visible_safe(player_joining_hilite_widget, false);
		gui_widget_set_visible_safe(rank_widget, true);
		gui_widget_set_visible_safe(rank_hilite_widget, true);
		gui_widget_set_visible_safe(skill_level_widget, true);
		gui_widget_set_visible_safe(skill_level_hilite_widget, true);
		gui_widget_set_visible_safe(voice_widget, true);
		gui_widget_set_visible_safe(nameplateWidget, true);
		gui_widget_set_visible_safe(nameplateWidget_hilite, true);
		long element_handle = c_gui_list_item_widget__get_element_handle(item);
		long player_index;
		c_gui_roster_data__get_integer_value(data, element_handle, 0x10014, &player_index);
		if (player_index != -1)
		{
			if (player_emblem_widget)
				player_emblem_widget->set_sprite_frame_index(player_index | 0x8000);
			if (player_emblem_hilite_widget)
				player_emblem_hilite_widget->set_sprite_frame_index(player_index | 0x8000);
			__int32 rank = GetPlayerRankIndex(player_index);
			if (rank_widget)
				rank_widget->set_sprite_frame_index(rank);
			if (rank_hilite_widget)
				rank_hilite_widget->set_sprite_frame_index(rank);
			__int32 skill = GetPlayerSkillIndex(player_index);
			if (skill_level_widget)
				skill_level_widget->set_sprite_frame_index(skill);
			if (skill_level_hilite_widget)
				skill_level_hilite_widget->set_sprite_frame_index(skill);
			c_network_session *squad_session;
			if (!network_session_interface_get_squad_session(&squad_session))
				return;
			if (!squad_session->get_session_membership()->is_player_valid(player_index))
				return;
			s_network_session_player *player = squad_session->get_session_membership()->get_player(player_index);
			if (nameplateWidget)
			{
				__int32 nameplate_index = 0;
				if (player->configuration.host.appearance.nameplate_index >= 0 && player->configuration.host.appearance.nameplate_index < nameplateWidget->get_sprite_frame_count())
					nameplate_index = player->configuration.host.appearance.nameplate_index;
				nameplateWidget->set_sprite_frame_index(nameplate_index);
			}
			if (nameplateWidget_hilite)
			{
				__int32 nameplate_index = 0;
				if (player->configuration.host.appearance.nameplate_index >= 0 && player->configuration.host.appearance.nameplate_index < nameplateWidget_hilite->get_sprite_frame_count())
					nameplate_index = player->configuration.host.appearance.nameplate_index;
				nameplateWidget_hilite->set_sprite_frame_index(nameplate_index);
			}
			if (player_service_tag_widget)
				item->set_text_widget_text(0x103F2, player->configuration.host.appearance.service_tag);
			__int32 ringStatus = 0;
			Blam::Network::Session *session = Blam::Network::GetActiveSession();
			__int32 localPlayerIndex = session->MembershipInfo.GetPeerPlayer(session->MembershipInfo.LocalPeerIndex);
			if (Modules::ModuleVoIP::Instance().playersMuted & (1 << player_index))
				ringStatus = 7;
			else if (Modules::ModuleVoIP::Instance().playersSpeaking & (1 << player_index))
				ringStatus = 5;
			else if (player_index == localPlayerIndex)
				ringStatus = 0;
			else if (Modules::ModuleVoIP::Instance().playersSpoke & (1 << player_index))
				ringStatus = 4;
			else
				gui_widget_set_visible_safe(voice_widget, false);
			if (voice_widget)
				voice_widget->set_sprite_frame_index(ringStatus);
		}
		__int32 changingTeam = sub_B25B30(thisptr, player_index);
		if (changingTeam)
		{
			long const team_names_tag_index = tag_find_by_name('unic', "multiplayer\\team_names");
			if (team_names_tag_index != -1)
			{
				s_multilingual_unicode_string_list_group_header *team_names_unic = (s_multilingual_unicode_string_list_group_header *)tag_get('unic', team_names_tag_index);
				if (team_names_unic && localDesiredTeam >= 0 && localDesiredTeam < team_names_unic->string_references.count)
				{
					unsigned long stringid = team_names_unic->string_references[localDesiredTeam].string_id;
					char *teamName = ui_resolve_string(team_names_tag_index, stringid, ui_get_prefered_lanquage());
					std::string s(teamName);
					wchar_t leftBumper[8];
					leftBumper[0] = 0xE104;
					leftBumper[1] = 0;
					wchar_t rightBumper[8];
					rightBumper[0] = 0xE105;
					rightBumper[1] = 0;
					std::wstring wTeamName(s.begin(), s.end());
					std::wstring newPlayerName;
					newPlayerName.append(leftBumper);
					newPlayerName.append(L" ");
					newPlayerName.append(wTeamName);
					newPlayerName.append(L" ");
					newPlayerName.append(rightBumper);
					if (player_name_widget)
						item->set_text_widget_text(0x2AA, newPlayerName.c_str());
					if (player_name_hilite_widget)
						item->set_text_widget_text(0x103DA, newPlayerName.c_str());
				}
			}
		}
		c_network_session *session;
		if (network_session_interface_get_squad_session(&session) && session->get_session_membership()->is_player_valid(player_index))
		{
			s_network_session_player *player = session->get_session_membership()->get_player(player_index);
			if (!wcslen(player->configuration.host.player_name) || !player->configuration.host.player_uid)
			{
				item->set_enabled(false);
				if (player_name_widget)
					player_name_widget->set_enabled(true);
				if (player_joining_text_widget)
					player_joining_text_widget->set_enabled(true);
				if (player_name_hilite_widget)
					player_name_hilite_widget->set_enabled(true);
				if (player_service_tag_widget)
					player_service_tag_widget->set_enabled(true);
				gui_widget_set_visible_safe(player_joining_widget, true);
				gui_widget_set_visible_safe(player_joining_text_widget, true);
				gui_widget_set_visible_safe(player_joining_hilite_widget, true);
				gui_widget_set_visible_safe(base_color_hilite_widget, false);
				gui_widget_set_visible_safe(player_emblem_widget, false);
				gui_widget_set_visible_safe(player_emblem_hilite_widget, false);
				gui_widget_set_visible_safe(player_name_widget, false);
				gui_widget_set_visible_safe(rank_tray_widget, false);
				gui_widget_set_visible_safe(rank_tray_hilite_widget, false);
				gui_widget_set_visible_safe(rank_widget, false);
				gui_widget_set_visible_safe(rank_hilite_widget, false);
				gui_widget_set_visible_safe(skill_level_widget, false);
				gui_widget_set_visible_safe(skill_level_hilite_widget, false);
				gui_widget_set_visible_safe(nameplateWidget, false);
				gui_widget_set_visible_safe(nameplateWidget_hilite, false);
				std::wstring joining = L"Player Joining";
				if (player_name_hilite_widget && player_joining_text_widget && player_service_tag_widget)
				{
					item->set_text_widget_text(0x103DA, joining.c_str());
					item->set_text_widget_text(0x103EA, joining.c_str());
					item->set_text_widget_text(0x103F2, L"Loading");
				}
			}
			else
			{
				gui_widget_set_visible_safe(player_joining_widget, false);
				gui_widget_set_visible_safe(player_joining_text_widget, false);
				gui_widget_set_visible_safe(player_joining_hilite_widget, false);
				item->set_enabled(true);
				gui_widget_set_visible_safe(base_color_hilite_widget, true);
				gui_widget_set_visible_safe(player_emblem_widget, true);
				gui_widget_set_visible_safe(player_emblem_hilite_widget, true);
				gui_widget_set_visible_safe(player_name_widget, true);
				gui_widget_set_visible_safe(rank_tray_widget, true);
				gui_widget_set_visible_safe(rank_tray_hilite_widget, true);
				gui_widget_set_visible_safe(rank_widget, true);
				gui_widget_set_visible_safe(rank_hilite_widget, true);
				gui_widget_set_visible_safe(skill_level_widget, true);
				gui_widget_set_visible_safe(skill_level_hilite_widget, true);
				gui_widget_set_visible_safe(nameplateWidget, true);
				gui_widget_set_visible_safe(nameplateWidget_hilite, true);
			}
		}
		item = item->get_next_sibling();
	}
}

void __fastcall c_gui_custom_bitmap_widget__set_map_image_hook(c_gui_custom_bitmap_widget *thisptr, long unused, e_image_content_type map_image, __int32 map_id, bool a4) // 0x10AE04A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_custom_bitmap_widget__set_map_image_hook@@YIXPAUc_gui_custom_bitmap_widget@@JW4e_image_content_type@@H_N@Z");

	s_level_datum level;
	if (levels_try_and_get_multiplayer_map(map_id, &level) || levels_try_and_get_campaign_map(map_id, &level))
	{
		std::string fpath = std::format("assets/maps/small/{}", std::filesystem::path(level.file_path).filename().string());
		csstrnzcpy(thisptr->m_requested_filename, fpath.c_str(), 256);
		thisptr->unknown_flag = false;
		thisptr->bitmap_format = 0;
	}
	else
	{
		csstrnzcpy(thisptr->m_requested_filename, "assets/maps/small/placeholder", 256);
	}
}

void __fastcall c_gui_custom_bitmap_widget__update_hook(c_gui_custom_bitmap_widget *thisptr, void *__formal, unsigned long time) // 0x10AE07F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_custom_bitmap_widget__update_hook@@YIXPAUc_gui_custom_bitmap_widget@@PAXK@Z");

	void (__thiscall *const c_gui_custom_bitmap_widget__reset)(c_gui_custom_bitmap_widget *) = reinterpret_cast<void (__thiscall *)(c_gui_custom_bitmap_widget *)>(0xAC3D50);
	void (__thiscall *const c_gui_widget__update)(void *, unsigned long) = reinterpret_cast<void (__thiscall *)(void *, unsigned long)>(0xABB070);
	c_gui_widget__update(thisptr, time);
	if (strncmp(thisptr->m_requested_filename, thisptr->m_filename, 255))
	{
		c_gui_custom_bitmap_widget__reset(thisptr);
		strncpy_s(thisptr->m_filename, thisptr->m_requested_filename, 255);
		if (thisptr->m_filename[0])
		{
			CustomBitmapManager *customBitmapManager = CustomBitmapManager::Get();
			thisptr->m_storage_item_index = customBitmapManager->FindOrAllocateBitmap(thisptr->m_filename);
			if (thisptr->m_storage_item_index != -1)
				customBitmapManager->BitmapLoadFromFileAsync(thisptr->m_storage_item_index, thisptr->m_filename, "assets/maps/small/placeholder");
		}
	}
}

void __fastcall c_gui_custom_bitmap_widget__reset_hook(c_gui_custom_bitmap_widget *thisptr) // 0x10AE0400
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_custom_bitmap_widget__reset_hook@@YIXPAUc_gui_custom_bitmap_widget@@@Z");

	if (thisptr->m_storage_item_index != -1)
	{
		CustomBitmapManager::Get()->BitmapRelease(thisptr->m_storage_item_index);
		thisptr->m_storage_item_index = -1;
	}
}

void ResolutionChangeHook() // 0x10ADD1C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ResolutionChangeHook@@YAXXZ");

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

	typedef int(__fastcall* UI_ListItem_GetIndexPtr)(void *thisPtr, int unused);
	auto vtable = *reinterpret_cast<void***>(item);
	auto GetIndex = reinterpret_cast<UI_ListItem_GetIndexPtr>(vtable[6]);
	return GetIndex(item, 0);
}

bool UI_OrderedDataSource_Get(void *data, __int32 index, __int32 key, void *result) // 0x10ADDA50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UI_OrderedDataSource_Get@@YA_NPAXHH0@Z");

	typedef bool(__fastcall* UI_OrderedDataSource_GetPtr)(void *thisPtr, int unused, int index, int key, void *result);
	auto vtable = *reinterpret_cast<void***>(data);
	auto Get = reinterpret_cast<UI_OrderedDataSource_GetPtr>(vtable[11]);
	return Get(data, 0, index, key, result);
}

__int32 __fastcall c_gui_roster_list_widget__start_team_change_hook(void *thisPtr, __int32 unused, __int32 a2, __int32 teamIndex, __int32 a4) // 0x10AE1B00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_roster_list_widget__start_team_change_hook@@YIHPAXHHHH@Z");

	localDesiredTeam = teamIndex;
	__int32 (__thiscall *F)(void *, __int32, __int32, __int32) = (__int32(__thiscall *)(void *, __int32, __int32, __int32))0xb25c30;
	return F(thisPtr, a2, teamIndex, a4);
}

void OnUiInputUpdated() // 0x10ADCE40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnUiInputUpdated@@YAXXZ");

	bool isUsingController = *(bool *)0x244DE98;
	if (isUsingController && Blam::Input::GetActionState(Blam::Input::eGameActionUiB)->Ticks == 1)
	{
		localDesiredTeam = -1;
	}
	else if (Blam::Input::GetKeyTicks(Blam::Input::eKeyCodeB, Blam::Input::eInputTypeGame) == 1)
	{
		localDesiredTeam = -1;
	}
	else if (Blam::Input::GetKeyTicks(Blam::Input::eKeyCodeEscape, Blam::Input::eInputTypeUi) == 1)
	{
		localDesiredTeam = -1;
	}
	else if (Blam::Input::GetMouseButtonTicks(Blam::Input::eMouseButtonRight, Blam::Input::eInputTypeUi) == 1)
		localDesiredTeam = -1;
	if (Blam::Input::GetKeyTicks(Blam::Input::eKeyCodeEscape, Blam::Input::eInputTypeUi) == 1 && Blam::Network::GetLobbyType() == -1)
	{
		reinterpret_cast<void (*)(long, long)>(0xAA5CD0)(3, -1);
		Web::Ui::ScreenLayer::ShowDialog("exit", [](std::string const &boxTag)
		{
			if (boxTag == "exit")
				Utils::Singleton<Modules::CommandMap>::Instance().ExecuteCommand("Game.Exit", false);
		});
	}
}

void __fastcall c_gui_roster_list_widget__update_render_state(c_gui_screen_widget *thisPtr, void *__formal, unsigned long milliseconds) // 0x10AE1B90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_roster_list_widget__update_render_state@@YIXPAVc_gui_screen_widget@@PAXK@Z");

	void *(__thiscall *const UI_GetOrderedDataSource)(void *) = (void *(__thiscall *)(void *))0xB14FE0;
	void (__thiscall *const UI_BaseUpdateListColors)(void *, unsigned long) = (void (__thiscall *)(void *, unsigned long))0xB16650;
	void (*const UI_ColorWidgetWithPlayerColor)(void *, __int32, bool) = (void (*)(void *, __int32, bool))0xAA4C80;
	void (__thiscall *const UI_Widget_MultiplyColor)(void *, float *) = (void (__thiscall *)(void *, float *))0xAB9D70;
	void (*const RgbToFloatColor)(unsigned __int32, float *) = (void (*)(unsigned __int32, float *))0x521300;
	long (__thiscall *const c_gui_list_item_widget__get_element_handle)(void *) = (long (__thiscall *)(void *))0xB184A0;
	char (__thiscall *const c_gui_roster_data__get_integer_value)(void *, long, unsigned long, long *) = (char (__thiscall *)(void *, long, unsigned long, long *))0xB24CA0;
	UI_BaseUpdateListColors(thisPtr, milliseconds);
	void *data = UI_GetOrderedDataSource(thisPtr);
	if (!data)
		return;
	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session)
		return;
	static bool teamsEnabled;
	if (session->IsEstablished())
		teamsEnabled = session->HasTeams();
	c_gui_widget *item = thisPtr->find_first_child((e_gui_widget)5);
	while (item)
	{
		c_gui_bitmap_widget *nameplateWidget = item->get_child_bitmap_widget(0x10144);
		c_gui_bitmap_widget *nameplateWidget_hilite = item->get_child_bitmap_widget(0x103DD);
		c_gui_bitmap_widget *baseColorWidget = item->get_child_bitmap_widget(0x9BF8);
		c_gui_bitmap_widget *baseColorHiliteWidget = item->get_child_bitmap_widget(0x9BF9);
		long element_handle = c_gui_list_item_widget__get_element_handle(item);
		long player_index;
		c_gui_roster_data__get_integer_value(data, element_handle, 0x10014, &player_index);
		__int32 itemIndex = UI_ListItem_GetIndex(item);
		__int32 playerRowType = 0;
		if (UI_OrderedDataSource_Get(data, itemIndex, 0x103CD, &playerRowType) && playerRowType == 0)
		{
			c_network_session *squad_session;
			if (player_index != -1 && network_session_interface_get_squad_session(&squad_session) && squad_session->get_session_membership()->is_player_valid(player_index))
			{
				s_network_session_player *player = squad_session->get_session_membership()->get_player(player_index);
				if (!wcslen(player->configuration.host.player_name) || !player->configuration.host.player_uid)
				{
					float joiningGrey[4] = { 1.0f, 0.3f, 0.3f, 0.3f };
					if (nameplateWidget)
						UI_Widget_MultiplyColor(nameplateWidget, joiningGrey);
					if (nameplateWidget_hilite)
						UI_Widget_MultiplyColor(nameplateWidget_hilite, joiningGrey);
					item = item->get_next_sibling();
					continue;
				}
			}
			__int32 teamIndex = 0;
			if (teamsEnabled && UI_OrderedDataSource_Get(data, itemIndex, 0x11D, &teamIndex) && teamIndex >= 0)
			{
				char (__thiscall *const c_gui_roster_list_widget__get_current_team_change_is_active)(void *, long) = (char (__thiscall *)(void *, long))0xB25B30;
				__int32 playerWidgetIndex = *(__int32 *)((char *)data + itemIndex * 0x1678 + 0x11C);
				static bool wasChangingTeam;
				if (playerWidgetIndex == session->MembershipInfo.GetPeerPlayer(session->MembershipInfo.LocalPeerIndex))
				{
					char isChangingTeam = c_gui_roster_list_widget__get_current_team_change_is_active(thisPtr, playerWidgetIndex);
					if (isChangingTeam)
					{
						wasChangingTeam = true;
						teamIndex = localDesiredTeam;
					}
					else if (wasChangingTeam)
					{
						teamIndex = localDesiredTeam;
						wasChangingTeam = false;
					}
				}
				if (nameplateWidget)
					UI_ColorWidgetWithPlayerColor(nameplateWidget, teamIndex, true);
				if (nameplateWidget_hilite)
					UI_ColorWidgetWithPlayerColor(nameplateWidget_hilite, teamIndex, true);
				if (baseColorWidget)
					UI_ColorWidgetWithPlayerColor(baseColorWidget, teamIndex, true);
				if (baseColorHiliteWidget)
					UI_ColorWidgetWithPlayerColor(baseColorHiliteWidget, teamIndex, true);
			}
			else
			{
				unsigned __int32 primaryColor = *(unsigned __int32 *)((char *)data + itemIndex * 0x1678 + 0x81C);
				float primaryColorF[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
				RgbToFloatColor(primaryColor, &primaryColorF[1]);
				if (nameplateWidget)
					UI_Widget_MultiplyColor(nameplateWidget, primaryColorF);
				if (nameplateWidget_hilite)
					UI_Widget_MultiplyColor(nameplateWidget_hilite, primaryColorF);
				if (baseColorWidget)
					UI_Widget_MultiplyColor(baseColorWidget, primaryColorF);
				if (baseColorHiliteWidget)
					UI_Widget_MultiplyColor(baseColorHiliteWidget, primaryColorF);
			}
		}
		item = item->get_next_sibling();
	}
}

static HWND__ *CreateGameWindowHook() // 0x10ADB990
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CreateGameWindowHook@@YAPAUHWND__@@XZ");

	if (Utils::Singleton<ElDorito>::Instance().IsHeadless())
	{
		WNDCLASSEXW wc;
		memset(&wc, 0, sizeof(wc));
		wc.cbSize = sizeof(WNDCLASSEXW);
		wc.lpszClassName = L"ElDorito - Dedicated Server";
		wc.hCursor = LoadCursorA(nullptr, MAKEINTRESOURCEA(32512));
		wc.hIcon = LoadIconA(nullptr, MAKEINTRESOURCEA(32512));
		wc.lpfnWndProc = *(WNDPROC *)0x199C020;
		RegisterClassExW(&wc);
		HWND__ *hWnd = CreateWindowExW(0, wc.lpszClassName, wc.lpszClassName, 0, 0, 0, 0, 0, nullptr, nullptr, nullptr, nullptr);
		*(HWND__ **)0x199C014 = hWnd;
		return hWnd;
	}
	else
	{
		HWND__ *(*const CreateGameWindow)() = reinterpret_cast<HWND__ *(*)()>(0xA223F0);
		HWND__ *hWnd = CreateGameWindow();
		if (!hWnd)
			return nullptr;
		for (auto &callback : createWindowCallbacks)
			callback(hWnd);
		return hWnd;
	}
}

bool UpdateH3HUDImpl(__int32 playerMappingIndex) // 0x10ADDB60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateH3HUDImpl@@YA_NH@Z");

	struct ControlGlobalsAction
	{
		unsigned short Type;
		unsigned short Flags;
		unsigned __int32 ObjectIndex;
	};
	static ControlGlobalsAction *(*GetPlayerControlsAction)(__int32) = (ControlGlobalsAction *(*)(__int32))0x5D0BD0;
	static void (*HUD_DisplayHUDMessage)(unsigned __int32, __int32, __int32, __int32) = (void (*)(unsigned __int32, __int32, __int32, __int32))0xA964E0;
	ControlGlobalsAction *action = GetPlayerControlsAction(playerMappingIndex);
	if (action->Type != 9 && action->Type != 1)
		return false;
	s_object_data *actionWeapObject = object_get(action->ObjectIndex);
	if (!actionWeapObject)
		return false;
	s_weapon_definition *actionWeapDef = (s_weapon_definition *)tag_get('weap', actionWeapObject->definition_index);
	if (action->Flags & 1)
		HUD_DisplayHUDMessage(playerMappingIndex, actionWeapDef->pickup_message, -1, 0);
	else if (action->Flags & 2)
		HUD_DisplayHUDMessage(playerMappingIndex, actionWeapDef->swap_message, -1, 0);
	else
		HUD_DisplayHUDMessage(playerMappingIndex, -1, -1, 0);
	if (action->Flags & 4)
		HUD_DisplayHUDMessage(playerMappingIndex, actionWeapDef->pickup_or_dual_wield_message, -1, 1);
	else if (action->Flags & 8)
		HUD_DisplayHUDMessage(playerMappingIndex, actionWeapDef->swap_or_dual_wield_message, -1, 1);
	else
		HUD_DisplayHUDMessage(playerMappingIndex, -1, -1, 1);
	return true;
}

void UI_UpdateH3HUDHook(__int32 playerMappingIndex) // 0x10ADDAE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UI_UpdateH3HUDHook@@YAXH@Z");

	static auto UI_UpdateHUD = (void(__cdecl*)(int playerMappingIndex))(0xA95D10);

	if (!UpdateH3HUDImpl(playerMappingIndex))
		UI_UpdateHUD(playerMappingIndex);
}

bool GetBoundMouseButtonName(__int32 code, wchar_t *buff) // 0x10ADBCA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetBoundMouseButtonName@@YA_NHPA_W@Z");

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

	if (!Utils::Singleton<Modules::ModuleGame>::Instance().VarHideH3UI->ValueInt)
	{
		((void(__thiscall *)(void *))0xA290A0)(thisptr);
	}

	Patches::MenuBlur::RenderUIPostProcess();
}

__int32 GetPlayerTypeFlagsValues() // 0x10ADC240
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetPlayerTypeFlagsValues@@YAHXZ");

	s_player_datum *playerDatum = players_get()->try_and_get(((long (*)(long))0x589C30)(0));
	if (!playerDatum)
		return 1;
	s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(playerDatum->unit_index, 0x2003);
	if (!unit)
		return 1;
	if (unit)
	{
		s_game_globals *game_globals = game_globals_get();
		for (long i = 0; i < game_globals->player_character_types.count; i++)
		{
			s_game_globals_player_character_type *character_type = &game_globals->player_character_types[i];
			s_game_globals_player_representation *player_representation;
			if (game_globals->PlayerRepresentation.try_get_element(character_type->multiplayer_player_representation_block_index, &player_representation) && unit->definition_index == player_representation->ThirdPersonUnit.index)
			{
				char *name = Blam::Cache::StringIDCache::GetCurrent()->GetString(player_representation->Name);
				if (!strcmp(name, "monitor"))
					return 4;
				else if (!strcmp(name, "mp_elite") || !strcmp(name, "dervish") || !strcmp(name, "sp_elite"))
					return 2;
				else
					return 1;
			}
		}
	}
	return 1;
}

__int32 GetMultiplayerFlagsValues() // 0x10ADC040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetMultiplayerFlagsValues@@YAHXZ");

	__int32 flags = 0;
	Modules::ModuleVoIP &voipModule = Modules::ModuleVoIP::Instance();
	if (!voipModule.VarVoipEnabled->ValueInt == 0)
	{
		if (voipModule.voipConnected)
		{
			if (voipModule.VarPTTEnabled->ValueInt == 0)
			{
				if (voipModule.voiceDetected)
				{
					flags |= 0x400;
				}
				else
				{
					flags |= 0x200;
				}
			}
			else
			{
				if (voipModule.IsChatting())
				{
					flags |= 0x400;
				}
				else
				{
					flags |= 0x80;
					flags |= 0x200;
				}
			}
		}
		else
		{
			flags |= 0x40;
		}
	}

	return flags;
}

__int32 GetMultiplayerEventsFlagsValues() // 0x10ADBFD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetMultiplayerEventsFlagsValues@@YAHXZ");

	__int32 flags = 0;

	if (Patches::Ui::speakingPlayers.size() > 0)
	{
		flags |= 8;
	}

	return flags;
}

__int32 GetUnitGeneralFlagsValues() // 0x10ADCAB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetUnitGeneralFlagsValues@@YAHXZ");

	__int32 flags = 0;
	Modules::ModuleVoIP &voipModule = Modules::ModuleVoIP::Instance();
	if (!voipModule.VarVoipEnabled->ValueInt == 0 && voipModule.voipConnected)
	{
		if (voipModule.VarPTTEnabled->ValueInt == 0)
		{
			if (voipModule.voiceDetected)
			{
				flags |= 0x400;
			}
		}
		else
		{
			if (Modules::ModuleVoIP::Instance().IsChatting())
			{
				flags |= 0x400;
			}
		}
	}

	return flags;
}

__int32 GameStateFlagsValues() // 0x10ADBB80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GameStateFlagsValues@@YAHXZ");

	s_player_datum *player = players_get()->try_and_get(eldorado::player_mapping_get_player_by_input_user(0));

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

unsigned long __fastcall GetGlobalDynamicColorHook(s_chud_globals_definition *thisptr, void *unused, long character_type, long color_index) // 0x10ADBE10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetGlobalDynamicColorHook@@YIKPAUs_chud_globals_definition@@PAXJJ@Z");

	s_chud_globals_definition *chud_definition = *(s_chud_globals_definition **)0x5257C40;
	if (character_type < 0 || character_type >= chud_definition->character_globals.count)
		return 0;
	if (color_index < 0 || color_index >= chud_definition->character_globals[character_type].colors.get_count())
		return 0;

	if (Patches::Ui::enableAllyBlueWaypointsFix && color_index == 15)
		return thisptr->character_globals[character_type].colors[19];

	if (Patches::Ui::enableCustomHUDColors)
	{
		switch (color_index)
		{
		case 0:
		case 1:
			return Patches::Ui::customSecondaryHUDColor;
		case 2:
		case 4:
		case 8:
		case 10:
		case 11:
		case 15:
			return Patches::Ui::customPrimaryHUDColor;
		}
	}

	return thisptr->character_globals[character_type].colors[color_index];
}

void GetWeaponOutlineColorHook(long index, real_argb_color *out_color) // 0x10ADCBA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetWeaponOutlineColorHook@@YAXJPAUreal_argb_color@@@Z");

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

	Web::Ui::ScreenLayer::Show(Web::Ui::ScreenLayer::ServerSettings, "{}");
}

__declspec(naked) void c_gui_screen_pregame_lobby_switch_network_hook() // 0x10AE44B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_screen_pregame_lobby_switch_network_hook@@YAXXZ");

	__asm
	{
		call OnLobbySwitchNetworkMode
		mov eax, 0B21F5Bh
		jmp eax
	}
}

void __fastcall c_gui_alert_manager__show(void *thisptr, void *unused, unsigned __int32 name, __int32 a3, wchar_t *customMessage, __int32 profileIndex, bool a6, __int32 a7) // 0x10ADFDE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_alert_manager__show@@YIXPAX0IHPA_WH_NH@Z");

	char *(*const ui_resolve_string)(unsigned __int32, unsigned __int32, __int32) = reinterpret_cast<char *(*)(unsigned __int32, unsigned __int32, __int32)>(0x51E290);
	__int32 (*const ui_get_prefered_lanquage)() = reinterpret_cast<__int32 (*)()>(0x52FC40);
	s_user_interface_shared_globals *wigl = ((s_user_interface_shared_globals *(*)())0xA84D20)();
	if (!wigl)
		return;
	long const alertStrings = tag_find_by_name('unic', "ui\\halox\\alert\\strings");
	if (alertStrings == -1)
		return;
	for (s_gui_alert_description &alert : wigl->alerts)
	{
		if (alert.error_name == name)
		{
			char const *title = ui_resolve_string(alertStrings, alert.title, ui_get_prefered_lanquage());
			char const *body = ui_resolve_string(alertStrings, alert.message, ui_get_prefered_lanquage());
			if (customMessage)
			{
				std::string customMessageStr = Utils::String::ThinString(customMessage);
				Web::Ui::ScreenLayer::ShowAlert(title, customMessageStr.c_str(), (Web::Ui::ScreenLayer::AlertIcon)(char)alert.error_icon, 0.0f);
			}
			else
			{
				Web::Ui::ScreenLayer::ShowAlert(title, body, (Web::Ui::ScreenLayer::AlertIcon)(char)alert.error_icon, 0.0f);
			}
			return;
		}
	}
}

void __fastcall c_hud_camera_view__render_outlines_hook(void *thisptr, void *unused, __int32 localProfileIndex, __int32 playerMappingIndex, void *a3) // 0x10AE4AC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_hud_camera_view__render_outlines_hook@@YIXPAX0HH0@Z");

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

	const auto csmemcpy = (void(*)(void *, void const *, unsigned long))0x4ECCD0;

	csmemcpy(buffer, &Patches::Ui::chud_talking_player_name, 16);
	return buffer;
}

bool PlayerMarkerIsDisabled(unsigned __int32 playerIndex) // 0x10ADD020
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PlayerMarkerIsDisabled@@YA_NI@Z");

	if (Patches::Camera::GetForcedCameraMode() == _camera_mode_flying)
		return true;

	c_data_array<s_player_datum> *players = players_get();
	if (playerIndex == -1)
		return false;

	s_player_datum *player = players_get()->try_and_get(playerIndex);
	if (!player)
		return false;

	unsigned long localPlayerDatumIndex = ((unsigned long (__cdecl *)(long))0x589C30)(0);
	if (localPlayerDatumIndex == -1)
		return false;

	s_player_datum *localPlayer = players->try_and_get(localPlayerDatumIndex);
	if (!localPlayer)
		return false;

	if (((bool (__cdecl *)())0x531B20)() && Player::PlayerPodium::PodiumEnabled())
		return true;

	unsigned char waypointTrait = player->traits.appearance.waypoint;
	switch (waypointTrait)
	{
	case 4:
		return player->configuration.host.team != localPlayer->configuration.host.team;
	case 5:
		return true;
	}
	return false;
}

void __fastcall chud_add_player_marker_hook(void *thisptr, void *unused, unsigned char *data_) // 0x10AE8510
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?chud_add_player_marker_hook@@YIXPAX0PAE@Z");

	__int32 (__thiscall *const sub_AAF560)(void *) = reinterpret_cast<__int32 (__thiscall *)(void *)>(0xAAF560);
	s_chud_navpoint *data = (s_chud_navpoint *)data_;
	__int32 index = 0;
	s_chud_managed_navpoint *state = (s_chud_managed_navpoint *)thisptr;
	while (!state->visible || state->navpoint.player_index != data->player_index)
	{
		index++;
		state++;
		if (index >= 20)
		{
			index = -1;
			break;
		}
	}
	if (PlayerMarkerIsDisabled(data->player_index))
	{
		if (index != -1)
		{
			s_chud_managed_navpoint *newState = &((s_chud_managed_navpoint *)thisptr)[sub_AAF560(thisptr)];
			newState->visible = false;
			newState->navpoint.player_index = -1;
		}
	}
	else
	{
		if (index == -1)
		{
			s_chud_managed_navpoint *newState = &((s_chud_managed_navpoint *)thisptr)[sub_AAF560(thisptr)];
			memcpy(newState, data, sizeof(s_chud_navpoint));
			newState->visible = true;
			newState->state = -1;
			newState->field_6C = 0;
			newState->submit_time = game_time_get();
			return;
		}
		if (data->player_index != -1)
		{
			s_player_datum *player = players_get()->try_and_get(data->player_index);
			if (player && player->unit_index != -1)
			{
				s_object_data *unitObject = object_get(player->unit_index);
				if (unitObject)
					data->position.x = data->position.x - 0.05f + pow(unitObject->scale, 1.0f) * 0.05f;
			}
		}
		s_chud_managed_navpoint *existingState = &((s_chud_managed_navpoint *)thisptr)[index];
		memcpy(existingState, data, sizeof(s_chud_navpoint));
		existingState->submit_time = game_time_get();
	}
}

void __fastcall c_start_menu_pane_screen_widget__handle_spinner_chosen_hook(void *thisptr, void *unused, unsigned char *widget) // 0x10AE7A40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_start_menu_pane_screen_widget__handle_spinner_chosen_hook@@YIXPAX0PAE@Z");

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

	const auto c_gui_screen_widget__transition_out = (void(__thiscall*)(void *thisptr, int a2))(0x00AB2830);

	auto name = *(uint32_t*)((uint8_t*)thisptr + 0x40);
	if (name != 0x103A9) // game_options
		c_gui_screen_widget__transition_out(thisptr, a2);
}

float get_player_vertical_crosshair_location() // 0x10AE8B30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_player_vertical_crosshair_location@@YAMXZ");

	unsigned char *c_player_profile = eldorado::controller_get(0);
	__int32 representationIndex = *(__int32 *)(c_player_profile + 4);
	s_game_globals *game_globals = game_globals_get();
	if (game_globals->PlayerControl.count > representationIndex)
	{
		return game_globals->PlayerControl[representationIndex].CrosshairLocation.y;
	}

	return 0.0f;
}

void observer_validate_camera_command__first_person_hook(unsigned char *c_observer_command) // 0x10AE8ED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?observer_validate_camera_command__first_person_hook@@YAXPAE@Z");

	*(float *)(c_observer_command + 0x20) = get_player_vertical_crosshair_location();
	if (Utils::Singleton<Modules::ModuleCamera>::Instance().VarCameraCenteredCrosshairFirst->ValueInt == 1)
	{
		*(float *)(c_observer_command + 0x20) = 0.0f;
	}
	((void(*)(unsigned char *))0x614D60)(c_observer_command);
}

void observer_validate_camera_command__third_person_hook(unsigned char *c_observer_command) // 0x10AE8F50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?observer_validate_camera_command__third_person_hook@@YAXPAE@Z");

	*(float *)(c_observer_command + 0x20) = get_player_vertical_crosshair_location();
	if (Utils::Singleton<Modules::ModuleCamera>::Instance().VarCameraCenteredCrosshairThird->ValueInt == 1)
	{
		*(float *)(c_observer_command + 0x20) = 0.0f;
	}
	((void(*)(unsigned char *))0x614D60)(c_observer_command);
}

__int32 user_interface_squad_get_countdown_timer_hook() // 0x10AE9C40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?user_interface_squad_get_countdown_timer_hook@@YAHXZ");

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

void __fastcall c_chud_update_user_data__ctor_hook(c_chud_update_user_data *thisptr, void *__formal, long user_index, long unit_index, bool a4) // 0x10ADF560
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_chud_update_user_data__ctor_hook@@YIXPAUc_chud_update_user_data@@PAXJJ_N@Z");

	static void (__thiscall *const ctor)(c_chud_update_user_data *, long, long, bool) = (void (__thiscall *)(c_chud_update_user_data *, long, long, bool))0xA85240;
	ctor(thisptr, user_index, unit_index, a4);
	c_chud_global_scripting *scripting = &tls_getd().chud_persistent_global_data->m_scripting;
	if ((!scripting->show || !scripting->widget_show[user_index][7]) && thisptr->grenade_counts[2] > 0)
		scripting->widget_show[user_index][7] = true;
	if ((!scripting->show || !scripting->widget_show[user_index][8]) && thisptr->grenade_counts[3] > 0)
		scripting->widget_show[user_index][8] = true;
	thisptr->player_type_flags = GetPlayerTypeFlagsValues();
	thisptr->game_engine_flags |= GameStateFlagsValues();
	thisptr->multiplayer_flags &= ~0x6C0;
	thisptr->multiplayer_flags |= GetMultiplayerFlagsValues();
	thisptr->multiplayer_events_flags |= GetMultiplayerEventsFlagsValues();
	thisptr->unit_general_flags |= GetUnitGeneralFlagsValues();
	thisptr->consumable_flags = 0;
	s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003);
	if (unit && unit->equipment_object_indices[0] != -1)
	{
		s_equipment_data *equipment = (s_equipment_data *)object_try_and_get_and_verify_type(unit->equipment_object_indices[0], 8);
		if (equipment)
		{
			s_equipment_definition *equipment_definition = (s_equipment_definition *)tag_get('eqip', equipment->definition_index);
			thisptr->interfaces[4].object_index = unit->equipment_object_indices[0];
			thisptr->interfaces[4].chud_definition_index = equipment_definition->hud_interface.index;
			thisptr->consumable_flags |= 0x100;
			if (eldorado::equipment_has_remaining_use_duration(unit->equipment_object_indices[0]))
			{
				float time_since_use = game_ticks_to_seconds((float)(game_time_get() - equipment->last_use_time));
				float max_use_duration = eldorado::equipment_get_use_duration(unit->equipment_object_indices[0]);
				float remaining_time = max_use_duration - time_since_use;
				float remaining_fraction = 1.0f - time_since_use / max_use_duration;
				thisptr->consumables[0].time_remaining = remaining_time;
				thisptr->consumables[0].remaining_fraction = remaining_fraction;
				thisptr->consumable_meter_visible = true;
				thisptr->consumable_flags |= 0x100000;
				thisptr->consumable_remaining_time = remaining_time;
				thisptr->consumable_remaining_fraction = remaining_fraction;
			}
		}
	}
}

void __fastcall c_user_interface_main_menu_music_update_desired_state(c_user_interface_main_menu_music *thisptr, void *unused) // 0x10AE82F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_user_interface_main_menu_music_update_desired_state@@YIXPAUc_user_interface_main_menu_music@@PAX@Z");

	s_scenario *scenario = global_scenario_get();
	if (!scenario || scenario->type != _scenario_type_main_menu)
	{
		thisptr->m_desired_state = 0;
		return;
	}
	c_gui_screen_widget *screen = c_gui_location_manager::get_location_gui_screen();
	if (screen)
	{
		long location = screen->get_gui_location();
		switch (screen->get_gui_location())
		{
		case 0:
			if (!((bool (*)())0xA84850)())
				thisptr->m_desired_state = 1;
			break;
		case 1:
			if (((bool (*)())0xA83250)())
				thisptr->m_desired_state = 0;
			else if (Utils::Singleton<Modules::ModuleSettings>::Instance().VarMusicInLobby->ValueInt)
				thisptr->m_desired_state = 1;
			break;
		case 2:
		case 3:
		case 4:
		case 5:
			thisptr->m_desired_state = 0;
			break;
		}
	}
}

void user_interface_text_parser_initialize_hook() // 0x10AE9D30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?user_interface_text_parser_initialize_hook@@YAXXZ");

	void (__thiscall *const c_magic_string_game_tag_parser_ctor)(void *, wchar_t const *, void *, bool (*)(void *, wchar_t *, long)) = reinterpret_cast<void (__thiscall *)(void *, wchar_t const *, void *, bool (*)(void *, wchar_t *, long))>(0xAA64C0);
	void (*const user_interface_text_parser_initialize)() = reinterpret_cast<void (*)()>(0xAA6AF0);
	void (*const user_interface_text_parser_register)(void *, __int32) = reinterpret_cast<void (*)(void *, __int32)>(0xAA6B10);
	user_interface_text_parser_initialize();
	static char selected_mod_parser[20];
	c_magic_string_game_tag_parser_ctor(selected_mod_parser, L"<eldewrito-mod", nullptr, [](void *data, wchar_t *buffer, long length) -> bool
	{
		s_session_mod_options const *mod = network_squad_session_get_mod();
		if (mod && mod->valid)
		{
			c_mod_package_manager::s_entry entry;
			if (c_mod_system::get_package_manager().find_package_by_hash(mod->hash, &entry))
			{
				_snwprintf(buffer, length, entry.name);
				return true;
			}
		}
		_snwprintf(buffer, length, L"NONE");
		return true;
	});
	user_interface_text_parser_register(selected_mod_parser, -1);
	static char version_tag_parser[20];
	c_magic_string_game_tag_parser_ctor(version_tag_parser, L"<eldewrito-version", nullptr, [](void *data, wchar_t *buffer, long length) -> bool
	{
		std::string version = Utils::Version::GetVersionString();
		std::transform(version.begin(), version.end(), version.begin(), toupper);
		std::wstring unicodeVersion(version.begin(), version.end());
		_snwprintf(buffer, length, unicodeVersion.c_str());
		return true;
	});
	user_interface_text_parser_register(version_tag_parser, -1);
	static char mission_tag_parser[20];
	c_magic_string_game_tag_parser_ctor(mission_tag_parser, L"<lobby-campaign-level", nullptr, [](void *data, wchar_t *buffer, long length) -> bool
	{
		std::string mission_name = "";
		long campaignId;
		long mapId;
		if (eldorado::network_life_cycle_session_get_map(&campaignId, &mapId))
		{
			char insertion[0xBA8];
			if (eldorado::levels_try_and_get_campaign_insertion(mapId, insertion))
			{
				short insertion_point = eldorado::network_squad_session_get_campaign_insertion_point();
				if (Blam::Network::GetLobbyType() == 5)
					mission_name = Utils::String::ThinString((wchar_t const *)(insertion + 8 + 64 * insertion_point));
				else
				{
					s_level_datum level;
					if (levels_try_and_get_campaign_map(mapId, &level))
						mission_name = Utils::String::ThinString(level.name);
				}
			}
		}
		std::transform(mission_name.begin(), mission_name.end(), mission_name.begin(), toupper);
		std::wstring unicodeVersion(mission_name.begin(), mission_name.end());
		_snwprintf(buffer, length, unicodeVersion.c_str());
		return true;
	});
	user_interface_text_parser_register(mission_tag_parser, -1);
}

// The three _Closure_wrapper_569e7c00 lambda invokers and conversion operators are emitted by the compiler from the lambdas above.





















































bool __fastcall c_gui_screen_pregame_lobby_handle_item_chosen_hook(void *thisptr, void *unused, void *message, unsigned long source_name, c_gui_list_item_widget *list_widget, c_gui_data *data) // 0x10AE4230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_screen_pregame_lobby_handle_item_chosen_hook@@YI_NPAX00KPAVc_gui_list_item_widget@@PAVc_gui_data@@@Z");

	long index = list_widget->get_data_item_index();
	unsigned long item_name_id;
	if (data->get_string_id_value(index, 0x2AA, &item_name_id))
	{
		char *name = Blam::Cache::StringIDCache::GetCurrent()->GetString(item_name_id);
		if (!_stricmp(name, "switch_selected_mod"))
		{
			Web::Ui::ScreenLayer::Show("mod_browse", "{}");
			return true;
		}
	}
	return c_gui_screen_pregame_lobby_handle_item_chosen(thisptr, message, source_name, list_widget, data);
}

bool __fastcall c_gui_screen_campaign_select_skulls__handle_controller_input_message_hook(c_gui_screen_widget *thisptr, void *unused, c_controller_input_message *message) // 0x10AE3780
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_screen_campaign_select_skulls__handle_controller_input_message_hook@@YI_NPAVc_gui_screen_widget@@PAXPAUc_controller_input_message@@@Z");

	bool (__thiscall *const handle_controller_input_message)(c_gui_screen_widget *, c_controller_input_message *) = reinterpret_cast<bool (__thiscall *)(c_gui_screen_widget *, c_controller_input_message *)>(0xAB1270);
	void (__thiscall *const select_skull)(c_gui_screen_widget *, __int32, long) = reinterpret_cast<void (__thiscall *)(c_gui_screen_widget *, __int32, long)>(0xAFF0D0);
	__int32 const row_size = 5;
	auto clamp_list_item_index = [](c_gui_list_widget *list, long index)
	{
		long item_count = list->get_item_count(false);
		return std::min<__int32>(std::max<__int32>(0, index), item_count - 1);
	};
	if (message->event_type >= 1 && message->event_type <= 4)
	{
		c_gui_list_widget *primary_list = thisptr->get_child_list_widget(0x104B7);
		c_gui_list_widget *secondary_list = thisptr->get_child_list_widget(0x104BA);
		if (primary_list && primary_list->within_focus())
		{
			long item_count = primary_list->get_item_count(false);
			long item_index = primary_list->get_selected_index();
			long row_count = (long)ceil(item_count / 5.0f);
			long row_index = item_index / row_size;
			long column_index = item_index % row_size;
			long target_list_index = 1;
			if (message->event_type == 1 || message->event_type == 3)
			{
				if (message->event_type == 1 && row_index > 0)
					row_index--;
				else if (message->event_type == 3)
					row_index++;
				if (row_index >= row_count)
				{
					row_index = 0;
					target_list_index = 2;
				}
			}
			else if (message->event_type == 2 || message->event_type == 4)
			{
				column_index += message->event_type == 2 ? -1 : 1;
			}
			long new_index = row_index * row_size + column_index;
			new_index = clamp_list_item_index(target_list_index == 1 ? primary_list : secondary_list, new_index);
			select_skull(thisptr, target_list_index, new_index);
			return true;
		}
		else if (secondary_list->within_focus())
		{
			long item_count = secondary_list->get_item_count(false);
			long item_index = secondary_list->get_selected_index();
			long row_count = (long)ceil(item_count / 5.0f);
			long row_index = item_index / row_size;
			long column_index = item_index % row_size;
			__int32 target_list_index = 2;
			if (primary_list && (message->event_type == 1 || message->event_type == 3))
			{
				if (message->event_type == 1)
					row_index--;
				else if (message->event_type == 3 && row_index < row_count - 1)
					row_index++;
				if (row_index < 0)
				{
					row_index = (long)ceil(primary_list->get_item_count(false) / 5.0f) - 1;
					target_list_index = 1;
				}
			}
			else if (message->event_type == 2 || message->event_type == 4)
			{
				column_index += message->event_type == 2 ? -1 : 1;
			}
			long new_index = row_index * row_size + column_index;
			new_index = clamp_list_item_index(target_list_index == 1 ? primary_list : secondary_list, new_index);
			select_skull(thisptr, target_list_index, new_index);
			return true;
		}
	}
	return handle_controller_input_message(thisptr, message);
}

void __fastcall c_gui_screen_game_options__update_hook(c_gui_screen_widget *thisptr, void *__formal, unsigned long milliseconds) // 0x10AE3D70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_screen_game_options__update_hook@@YIXPAVc_gui_screen_widget@@PAXK@Z");

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

void __fastcall c_gui_widget__get_unprojected_bounds_hook(c_gui_widget *thisptr, void *unused, gui_real_rectangle2d *unprojected_bounds, bool offset, bool scale, bool rotate) // 0x10AE4760
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_widget__get_unprojected_bounds_hook@@YIXPAVc_gui_widget@@PAXPAUgui_real_rectangle2d@@_N33@Z");

	void (__thiscall *const get_unprojected_bounds)(c_gui_widget *, gui_real_rectangle2d *, bool, bool, bool) = reinterpret_cast<void (__thiscall *)(c_gui_widget *, gui_real_rectangle2d *, bool, bool, bool)>(0xAB97C0);
	get_unprojected_bounds(thisptr, unprojected_bounds, offset, scale, rotate);
	short_rectangle2d display_pixel_bounds;
	long *ui_resolution = reinterpret_cast<long *>(0x19106C8);
	float ui_aspect_ratio = (float)ui_resolution[0] / (float)ui_resolution[1];
	((void (*)(long, long, short_rectangle2d *, long))0xA9FAA0)(0, 0, &display_pixel_bounds, 0);
	long display_mode = interface_get_closest_authored_ui_aspect_ratio_hook();
	float ui_tag_resolutions[2][2] = { { 1512.0f, 840.0f }, { 840.0f, 630.0f } };
	float widescreen_factor = ui_aspect_ratio / (display_mode == 1 ? 1.3333333f : 1.7777778f);
	float width_scale = (display_pixel_bounds.x1 - display_pixel_bounds.x0) / ui_tag_resolutions[display_mode][0] / widescreen_factor;
	float height_scale = (display_pixel_bounds.y1 - display_pixel_bounds.y0) / ui_tag_resolutions[display_mode][1];
	unprojected_bounds->top_left.x *= width_scale;
	unprojected_bounds->bottom_left.x *= width_scale;
	unprojected_bounds->top_right.x *= width_scale;
	unprojected_bounds->bottom_right.x *= width_scale;
	unprojected_bounds->top_left.y *= height_scale;
	unprojected_bounds->bottom_left.y *= height_scale;
	unprojected_bounds->top_right.y *= height_scale;
	unprojected_bounds->bottom_right.y *= height_scale;
}

void c_rasterizer__get_display_pixel_bounds_hook(short_rectangle2d *display_pixel_bounds) // 0x10AE7500
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_rasterizer__get_display_pixel_bounds_hook@@YAXPAUshort_rectangle2d@@@Z");

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

real_point2d interface_get_authoring_to_target_dimensions_scaling_hook() // 0x10AE8C30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?interface_get_authoring_to_target_dimensions_scaling_hook@@YA?AUreal_point2d@@XZ");

	real_point2d *scaling = reinterpret_cast<real_point2d *>(0x191D4B4);
	scaling->x = 1.3125f;
	scaling->y = 1.3125f;
	return *scaling;
}

void __fastcall c_gui_custom_bitmap_widget__assemble_render_data_hook(c_gui_custom_bitmap_widget *thisptr, void *unused, s_gui_widget_render_data *render_data, real_rectangle2d *bounds, long controller_index, bool offset, bool scale, bool rotate) // 0x10AE01E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_custom_bitmap_widget__assemble_render_data_hook@@YIXPAUc_gui_custom_bitmap_widget@@PAXPAUs_gui_widget_render_data@@PAUreal_rectangle2d@@J_N44@Z");

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

	float font_scale = 1.0f;

	thisptr->scale = thisptr->scale * font_scale;

	const auto c_draw_string__draw_internal = (bool(__thiscall *)(c_draw_string *, void *, char const *))0x657950;

	return c_draw_string__draw_internal(thisptr, cache, utf32_text);
}

void __fastcall c_draw_string__set_bounds_hook(c_draw_string *thisptr, void *unused, real_rectangle2d *upper_x, real_rectangle2d *upper_y) // 0x10ADFBE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_draw_string__set_bounds_hook@@YIXPAUc_draw_string@@PAXPAUreal_rectangle2d@@2@Z");

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

	long current_campaign_id;
	long current_map_id;
	if (((bool(*)(long *, long *))0xA817B0)(&current_campaign_id, &current_map_id) && current_campaign_id != -1)
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

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace Patches { namespace Ui { __int32 customPrimaryHUDColor = -1; } }
namespace Patches { namespace Ui { __int32 customSecondaryHUDColor; } }
namespace Patches { namespace Ui { bool enableCustomHUDColors; } }
namespace Patches { namespace Ui { bool enableAllyBlueWaypointsFix; } }
namespace Patches { namespace Ui { bool HasAttractBinks; } }
namespace Patches { namespace Ui { bool isPttSoundPlaying; } }
namespace Patches { namespace Ui { char16_t chud_talking_player_name[32]; } }
namespace hades_file_local { bool tagsInitiallyLoaded; }
namespace hades_file_local { __int32 localDesiredTeam = -1; }
namespace hades_file_local { namespace hades_file_local_Ui { bool (*IsMapLoading)() = reinterpret_cast<decltype(IsMapLoading)>(0x5670E0); } }

namespace hades_file_local { extern "C" { bool (__thiscall *c_gui_screen_pregame_lobby_handle_item_chosen)(void *, void *, unsigned long, c_gui_list_item_widget *, c_gui_data *); } }
