/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/interface/gui/gui_screen_manager.hpp"
#include "Blam/interface/gui/gui_screen_widget.hpp"
#include "Blam/interface/gui/gui_widget.hpp"
#include "Blam/interface/user_interface_sound.hpp"
#include "Blam/main/game_preferences.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/D3D/D3DAdapters.hpp"
#include "ElDorito.hpp"
#include "Forge/Geoemetry.hpp"
#include "mods/font_package.hpp"
#include "Modules/ModuleCamera.hpp"
#include "Modules/ModuleInput.hpp"
#include "Modules/ModuleSettings.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/Network.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
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
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
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
#include <memory>
#include <ostream>
#include <span>  // hades: added for 0x10A72BB0
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <variant>
#include <vector>

/* ---------- forward declarations */

class c_gui_screen_manager;
class c_gui_screen_widget;
struct c_game_engine;
struct c_game_variant;
struct real_euler_angles3d;
struct real_matrix4x3;
struct real_point3d;
struct s_game_options;
struct s_global_preferences;
struct s_global_preferences_settings;
struct s_object_data;
struct s_player_datum;
struct s_scenario;
namespace Blam
{
	namespace Input
	{
		struct ActionState;
	}
}
namespace Blam
{
	namespace Network
	{
		struct NetworkAddress;
		struct Session;
	}
}
namespace Common
{
	namespace D3DAdapters
	{
		struct DisplayMode;
	}
}
namespace Modules
{
	class ModuleCamera;
	class ModuleInput;
	class ModuleSettings;
}
namespace hades_file_local
{
	struct s_session_player_ping;
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
namespace Player
{
	namespace PlayerPodium {}
	using namespace Player::PlayerPodium;
}

namespace Forge {}
using namespace ::Forge;
namespace Scripting {}
using namespace ::Scripting;
namespace Scripting
{
	namespace HS {}
	using namespace Scripting::HS;
}

namespace Common {}
using namespace ::Common;
namespace Common
{
	namespace D3DAdapters {}
	using namespace Common::D3DAdapters;
}

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
	namespace Hf2pExperimental {}
	using namespace Patches::Hf2pExperimental;
}

namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
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
	#pragma pack(push, 4)
	struct s_session_player_ping
	{
		std::string ip; // 0x0
		unsigned short port; // 0x1C
		unsigned char __pad0[2]; // 0x1E
		long ping; // 0x20
		s_session_player_ping(s_session_player_ping &); /* compiler_generated() */
		s_session_player_ping(s_session_player_ping const &); /* compiler_generated() */
		s_session_player_ping(); /* compiler_generated() */
		~s_session_player_ping(); /* compiler_generated() */
		s_session_player_ping &operator=(s_session_player_ping &); /* compiler_generated() */
		s_session_player_ping &operator=(s_session_player_ping const &); /* compiler_generated() */
	};
	#pragma pack(pop)
	static_assert(sizeof(s_session_player_ping) == 36, "Invalid s_session_player_ping size");
}
using namespace hades_file_local;
/* ---------- prototypes */

extern __int32 game_engine_get_player_score(unsigned long player_index);  // hades: added for 0x10A73AE0

#include "Modules/ModuleServer.hpp"  // hades: added for 0x10A73A60

namespace Patches
{
	namespace Hf2pExperimental
	{
		extern void ApplyAll();
	}
}

void Hf2pInitHook();
void Hf2pShutdownHook();
void SystemMenu();
__int32 GetSecondsRemainingUntilPlayerSpawn();
bool PingPlayer(std::string ip, unsigned short port);
static void PongReceived(Blam::Network::NetworkAddress const &from, unsigned __int32 timestamp, unsigned short id, unsigned __int32 latency);
void BuildPlayerPing();
namespace Forge { namespace PrematchCamera { long FindCameraObjectForTeamDesignator(short team_designator); bool IsForgePrematchCameraDisabled(); } }  // hades: added for 0x10A72BB0
extern c_game_variant *(*const game_engine_get_variant)();  // hades: added for 0x10A72BB0
extern float (*const game_ticks_to_seconds)(float);  // hades: added for 0x10A72BB0
extern float (*const game_seconds_to_ticks_real)(float);  // hades: added for 0x10A72BB0
extern void matrix4x3_rotation_to_angles(real_matrix4x3 const *matrix, real_euler_angles3d *angles);  // hades: added for 0x10A72BB0
extern void UpdateUiPlayerModelArmor();  // hades: added for 0x10A72BB0
extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0x10A72BB0
namespace Player { namespace PlayerPodium { void PodiumTick(); } }  // hades: added for 0x10A72BB0
namespace Scripting { namespace HS { extern void ExecuteScript(std::string_view name, std::span<hs_value const> arguments); } }  // hades: added for 0x10A72BB0
void Hf2pTickHook();
s_global_preferences_settings::e_level LevelStringToSetting(std::string const &value);
void Hf2pLoadPreferencesHook();
void __fastcall c_game_engine_object_runtime_manager__update_hook(void *thisptr, void *unused);
void ApplyDefaultScreenFx();
void game_initialize_for_new_map_call_hook(s_game_options *game_options);
bool game_finish_should_mute_sounds();
void game_finished_wait_time_add_hook(float seconds);
bool game_engine_should_start_music_hook();
long scenario_multiplayer_globals_try_and_get_runtime_data_hook();
bool game_engine_in_round_hook();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	s_session_player_ping players_ping[16]; // 0x12458580
	extern unsigned short PingId; // 0x124587C0
	extern long long game_end_time; // 0x124587C8
	extern long long last_ping_time; // 0x124587D0
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Hf2pExperimental
	{
		void ApplyAll() // 0x10A708B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Hf2pExperimental@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x200630, Hf2pInitHook).Apply();
			Patch(0x24F6B0, { 0xC3 }).Apply();
			Patch(0x24EF50, { 0xC3 }).Apply();
			Patch(0x10F1121, { 0xE9 }).Apply();
			Patch(0x2006F0, { 0xC3 }).Apply();
			Patch(0x622920, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0xC3 }).Apply();
			Hook(0x200790, Hf2pShutdownHook).Apply();
			Hook(0x105F0D, Hf2pTickHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x10CB01, Hf2pLoadPreferencesHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x152783, c_game_engine_object_runtime_manager__update_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x167E9D, game_initialize_for_new_map_call_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x1391B5, { 0xEB }).Apply();
			Hook(0x1D85D0, game_finish_should_mute_sounds, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x347822, game_finished_wait_time_add_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x2E4590, game_engine_should_start_music_hook).Apply();
			Hook(0x2E4213, game_engine_in_round_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x2E43D2, scenario_multiplayer_globals_try_and_get_runtime_data_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
		}
	}
}

/* ---------- private code */

// mangled_x86(MANGLED_DEFAULT, "??0s_session_player_ping@hades_file_local@@QAE@XZ"); no body to assert in
_inline s_session_player_ping::s_session_player_ping() = default; // 0x10A70810

// mangled_x86(MANGLED_DEFAULT, "??1s_session_player_ping@hades_file_local@@QAE@XZ"); no body to assert in
_inline s_session_player_ping::~s_session_player_ping() = default; // 0x10A70860

void Hf2pInitHook() // 0x10A723E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Hf2pInitHook@@YAXXZ");
	// `anonymous-namespace'::Hf2pInitHook
	// procedure flags: nofpo
	// function call : void (*)()
	// InitSoundSystem
	// InitSoundSystem

	*(unsigned __int32 *)0x50CCB3C = 0;
	*(unsigned __int32 *)0x244ED28 = 0;

	// InitSoundSystem
	((void(__cdecl *const)())0x64e190)();

	PingId = Patches::Network::OnPong(PongReceived);
}

void Hf2pShutdownHook() // 0x10A72B60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Hf2pShutdownHook@@YAXXZ");
	// `anonymous-namespace'::Hf2pShutdownHook
	// procedure flags: nofpo
	// function call : void (*)()

	((void(__cdecl *const)())0x652ee0)();
}

void SystemMenu() // 0x10A73850
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SystemMenu@@YAXXZ");
	// `anonymous-namespace'::SystemMenu
	// procedure flags: nofpo
	// Blam::Input::ActionState *uiStartAction;
		// bool isUsingController;
		// c_gui_screen_manager *screenManager;
			// c_gui_screen_widget *screenWidget;
	// function call : bool (*const)()
	// function call : long (*const)(e_user_interface_sound, long)
	// function call : void (*const)(void *, __int32)

	static bool (*const game_in_progress)() = reinterpret_cast<bool (*)()>(0x531E90);
	static long (*const user_interface_play_sound)(e_user_interface_sound, long) = reinterpret_cast<long (*)(e_user_interface_sound, long)>(0xAA5CD0);
	static void (__thiscall *const screen_transition_out)(void *, __int32) = reinterpret_cast<void (__thiscall *)(void *, __int32)>(0xAB2830);
	if (game_in_progress())
		return;
	Blam::Input::ActionState *uiStartAction = Blam::Input::GetActionState(Blam::Input::eGameActionUiStart);
	if (!(uiStartAction->Flags & 1) && uiStartAction->Ticks == 1)
	{
		bool isUsingController = *reinterpret_cast<bool *>(0x244DE98);
		c_gui_screen_manager *screenManager = c_gui_screen_manager::get();
		if (!screenManager->any_active_screens(0) && !screenManager->find_screen(4, 0x100BE))
		{
			uiStartAction->Flags |= 1;
			user_interface_play_sound((e_user_interface_sound)7, -1);
			Patches::Ui::ShowDialog(0x10084, 0, 4, 0x1000C);
		}
		else if (isUsingController)
		{
			c_gui_screen_widget *screenWidget = screenManager->find_screen(4, 0x10084);
			if (screenWidget)
			{
				uiStartAction->Flags |= 1;
				screen_transition_out(screenWidget, 1);
			}
		}
	}
}

__int32 GetSecondsRemainingUntilPlayerSpawn() // 0x10A721B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetSecondsRemainingUntilPlayerSpawn@@YAHXZ");
	// `anonymous-namespace'::GetSecondsRemainingUntilPlayerSpawn
	// procedure flags: nofpo
	// s_player_datum *const player;
	// unsigned long playerIndex;
	// function call : unsigned long (*const)(long)
	// function call : unsigned long (*const)(long)

	unsigned long playerIndex = ((unsigned long (__cdecl *)(long))0x589C30)(0);
	s_player_datum *const player = players_get()->try_and_get(((unsigned long (__cdecl *)(long))0x589C30)(0));
	return player ? Pointer(player)(0x2CBC, 1).Read<__int32>() : 0;
}

bool PingPlayer(std::string ip, unsigned short port) // 0x10A734F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PingPlayer@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@G@Z");
	// `anonymous-namespace'::PingPlayer
	// static ...; // 0x10A73648
	// static ...; // 0x10A73640
	// std::string ip;
	// unsigned short port;
	// Blam::Network::Session *session;
		// Blam::Network::NetworkAddress blamAddress;

	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (session)
	{
		Blam::Network::NetworkAddress blamAddress;
		if (!Blam::Network::NetworkAddress::Parse(ip, port, &blamAddress))
			return false;
		if (!session->Gateway->Ping(blamAddress, PingId))
			return false;
		return true;
	}
	return false;
}

static void PongReceived(Blam::Network::NetworkAddress const &from, unsigned __int32 timestamp, unsigned short id, unsigned __int32 latency) // 0x10A736C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PongReceived@@YAXABUNetworkAddress@Network@Blam@@IGI@Z");
	// `anonymous-namespace'::PongReceived
	// unsigned __int32 latency;
		// __int32 i;

	if (id != PingId)
		return;
	for (__int32 i = 0; i < 16; i++)
	{
		if (players_ping[i].ip == from.ToString() && from.Port == players_ping[i].port)
		{
			players_ping[i].ping = latency;
			return;
		}
	}
}

void BuildPlayerPing() // 0x10A71CF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BuildPlayerPing@@YAXXZ");
	// `anonymous-namespace'::BuildPlayerPing
	// procedure flags: nofpo
	// static ...; // 0x10A720B0
	// static ...; // 0x10A720AD
	// static ...; // 0x10A720AB
	// static ...; // 0x10A720A4
	// static ...; // 0x10A72074
	// static ...; // 0x10A7206C
	// static bool (*`BuildPlayerPing'::`2'::IsMapLoading)(); // 0x113543F0
	// Blam::Network::Session *session;
		// long long elapsed;
		// long long curTime1;
			// __int32 playerIdx;
			// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> s;
			// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
				// Blam::Network::NetworkAddress ip;
				// __int32 i;
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : bool (*)()

	static bool (*IsMapLoading)() = reinterpret_cast<bool (*)()>(0x5670E0);
	if (((bool (*)())0x531E90)() || !((bool (*)())0x5319C0)() || IsMapLoading())
		return;
	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (session && session->IsEstablished())
	{
		if (Utils::Singleton<Modules::ModuleServer>::Instance().VarServerShowPlayerPing->ValueInt == 1)
		{
			long long curTime1;
			time(&curTime1);
			long long elapsed = curTime1 - last_ping_time;
			if (!last_ping_time || elapsed >= 10)
			{
				time(&last_ping_time);
				__int32 playerIdx = session->MembershipInfo.FindFirstPlayer();
				while (playerIdx != -1)
				{
					Blam::Network::NetworkAddress ip = session->GetPeerAddress(session->MembershipInfo.GetPlayerPeer(playerIdx));
					players_ping[playerIdx].ip = ip.ToString();
					players_ping[playerIdx].port = ip.Port;
					PingPlayer(ip.ToString(), ip.Port);
					playerIdx = session->MembershipInfo.FindNextPlayer(playerIdx);
				}
				rapidjson::StringBuffer s;
				rapidjson::Writer<rapidjson::StringBuffer> writer(s);
				writer.StartObject();
				writer.Key("players");
				writer.StartArray();
				for (__int32 i = 0; i < 16; i++)
				{
					writer.StartObject();
					writer.Key("ping");
					writer.Int(players_ping[i].ping);
					writer.EndObject();
				}
				writer.EndArray();
				writer.EndObject();
				Utils::Singleton<Modules::ModuleServer>::Instance().VarPlayersPingInfo->ValueString = s.GetString();
			}
		}
		else if (Utils::Singleton<Modules::ModuleServer>::Instance().VarPlayersPingInfo->ValueString != "{}")
		{
			Utils::Singleton<Modules::ModuleServer>::Instance().VarPlayersPingInfo->ValueString = "{}";
		}
	}
}

void Hf2pTickHook() // 0x10A72BB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Hf2pTickHook@@YAXXZ");
	// `anonymous-namespace'::Hf2pTickHook
	// procedure flags: nofpo
	// static ...; // 0x10A7325C
	// static ...; // 0x10A73244
	// static ...; // 0x10A7322C
	// static ...; // 0x10A73224
	// static void (*`Hf2pTickHook'::`2'::InitMpDirector)(); // 0x113543FC
	// static bool (*`Hf2pTickHook'::`2'::IsMapLoading)(); // 0x11354400
	// __int32 secondsUntilPlayerSpawn;
	// void (*const camera_control)(__int32);
	// static bool `Hf2pTickHook'::`2'::s_MatchStarted; // 0x124587C2
	// static __int32 `Hf2pTickHook'::`2'::s_CameraObjectIndex; // 0x11354408
	// static bool (*`Hf2pTickHook'::`2'::IsMainMenu)(); // 0x11354404
	// static bool (*`Hf2pTickHook'::`2'::UpdatePreMatchCamera)(); // 0x113543F8
	// void (*const scripted_camera_set_internal)(__int32, real_point3d const *, real_euler_angles3d const *, float, short, long);
	// unsigned long roundTimer;
	// static bool `Hf2pTickHook'::`2'::prematch_script_called; // 0x124587C3
	// static bool (*`Hf2pTickHook'::`2'::InPrematchState)(char); // 0x113543F4
		// s_object_data *scenObject;
			// s_player_datum *player;
			// unsigned long playerIndex;
				// long team_designator;
					// unsigned long foundCameraObjectIndex;
			// real_euler_angles3d cameraObjectOrientation;
			// real_matrix4x3 cameraObjectTransform;
		// unsigned long time;
		// float game_engine_finish_wait_seconds;
		// long game_finished_wait_time_ticks;
	// function call : bool (*const)()
	// function call : c_game_engine *(*const)()
	// function call : bool (*)(char)
	// function call : bool (*const)()
	// function call : c_game_variant *(*const)()
	// function call : unsigned long (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : real_matrix4x3 *(*const)(long, real_matrix4x3 *)
	// function call : void (*const)(__int32)
	// function call : void (*const)(__int32, real_point3d const *, real_euler_angles3d const *, float, short, long)
	// function call : bool (*)()
	// function call : void (*)()
	// function call : bool (*const)()
	// function call : float (*const)(float)
	// function call : c_game_engine *(*const)()
	// function call : float (*const)(float)
	// function call : void (*const)(char const *, float, short)
	// function call : float (*const)(float)
	// function call : void (*const)(char const *, float, short)
	// function call : float (*const)(float)
	// function call : void (*const)(char const *, float, short)
	// function call : float (*const)(float)
	// function call : void (*const)(char const *, float, short)
	// function call : bool (*)()
	// function call : bool (*)()

	static bool (*InPrematchState)(char) = reinterpret_cast<bool (*)(char)>(0x5523A0);
	static bool (*UpdatePreMatchCamera)() = reinterpret_cast<bool (*)()>(0x72D580);
	static void (*InitMpDirector)() = reinterpret_cast<void (*)()>(0x72D560);
	static bool (*IsMapLoading)() = reinterpret_cast<bool (*)()>(0x5670E0);
	static bool (*IsMainMenu)() = reinterpret_cast<bool (*)()>(0x531E90);
	static __int32 s_CameraObjectIndex = -1;
	static bool s_MatchStarted = false;
	static bool prematch_script_called = false;
	void (*const scripted_camera_set_internal)(__int32, real_point3d const *, real_euler_angles3d const *, float, short, long) = (void (*)(__int32, real_point3d const *, real_euler_angles3d const *, float, short, long))0x72DD70;
	void (*const camera_control)(__int32) = (void (*)(__int32))0x592320;
	__int32 secondsUntilPlayerSpawn = GetSecondsRemainingUntilPlayerSpawn();
	unsigned long roundTimer = Modules::ModuleServer::Instance().VarServerCountdownClient->ValueInt;
	if (((bool (*const)())0x5314B0)() && ((c_game_engine *(*const)())0x5CE150)() && InPrematchState(4))
	{
		if (roundTimer > 0)
		{
			if (!Forge::PrematchCamera::IsForgePrematchCameraDisabled())
			{
				if (((bool (*const)())0x5565E0)() || game_engine_get_variant()->game_engine_type == _game_engine_type_infection)
				{
					s_player_datum *player = nullptr;
					unsigned long playerIndex = ((unsigned long (*const)(long))0x589C30)(0);
					if (playerIndex != -1)
					{
						player = players_get()->try_and_get(playerIndex);
						if (player)
						{
							long team_designator = game_engine_get_team_designator(playerIndex);
							if (team_designator != -1)
							{
								unsigned long foundCameraObjectIndex = Forge::PrematchCamera::FindCameraObjectForTeamDesignator(team_designator);
								if (foundCameraObjectIndex != -1 && (s_CameraObjectIndex == -1 || s_CameraObjectIndex != foundCameraObjectIndex))
									s_CameraObjectIndex = foundCameraObjectIndex;
							}
						}
					}
				}
				if (s_CameraObjectIndex == -1)
					s_CameraObjectIndex = Forge::PrematchCamera::FindCameraObjectForTeamDesignator(8);
				s_object_data *scenObject = object_try_and_get_and_verify_type(s_CameraObjectIndex, 0x80);
				if (s_CameraObjectIndex != -1 && scenObject)
				{
					real_matrix4x3 cameraObjectTransform;
					real_euler_angles3d cameraObjectOrientation;
					((real_matrix4x3 *(*const)(long, real_matrix4x3 *))0xB2EC60)(s_CameraObjectIndex, &cameraObjectTransform);
					matrix4x3_rotation_to_angles(&cameraObjectTransform, &cameraObjectOrientation);
					camera_control(1);
					scripted_camera_set_internal(0, &cameraObjectTransform.position, &cameraObjectOrientation, 0.0f, 0, -1);
				}
				else
				{
					UpdatePreMatchCamera();
				}
			}
			if (!prematch_script_called)
			{
				Scripting::HS::ExecuteScript("prematch_camera", {});
				prematch_script_called = true;
			}
		}
		s_MatchStarted = true;
	}
	else if (s_MatchStarted)
	{
		InitMpDirector();
		s_MatchStarted = false;
		s_CameraObjectIndex = -1;
		prematch_script_called = false;
		unsigned long time = Modules::ModuleServer::Instance().VarPostGameFadeStartDelay->ValueInt;
		Pointer(0x553750).Write<unsigned char>(time);
	}
	if (((bool (*const)())0x531B20)() && !game_end_time)
		::time(&game_end_time);
	if (game_end_time)
	{
		long game_finished_wait_time_ticks = *(long *)offset_pointer(tls_getd().game_globals, 0x24BE8);
		float game_engine_finish_wait_seconds = game_ticks_to_seconds((float)game_finished_wait_time_ticks);
		if (game_engine_finish_wait_seconds <= 3.0f)
		{
			if (((c_game_engine *(*const)())0x5CE150)() && !Modules::ModuleServer::Instance().VarServerMuteSoundsDuringPostGameClient->ValueInt)
			{
				((void (*const)(char const *, float, short))0x660B50)("", 0.0f, (short)game_seconds_to_ticks_real(3.0f));
				((void (*const)(char const *, float, short))0x660B50)("ambient_nature", 0.2f, (short)game_seconds_to_ticks_real(3.0f));
				((void (*const)(char const *, float, short))0x660B50)("ambient_machinery", 0.2f, (short)game_seconds_to_ticks_real(3.0f));
				((void (*const)(char const *, float, short))0x660B50)("ambient_computers", 0.2f, (short)game_seconds_to_ticks_real(3.0f));
			}
			game_end_time = 0;
		}
	}
	if (!IsMapLoading())
	{
		if (IsMainMenu())
			UpdateUiPlayerModelArmor();
		else
			SystemMenu();
	}
	Player::PlayerPodium::PodiumTick();
	BuildPlayerPing();
}

s_global_preferences_settings::e_level LevelStringToSetting(std::string const &value) // 0x10A73430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LevelStringToSetting@@YA?AW4e_level@s_global_preferences_settings@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::LevelStringToSetting
	// std::string const &value;

	return value == "low" ? (s_global_preferences_settings::e_level)0 : value == "medium" ? (s_global_preferences_settings::e_level)1 : (s_global_preferences_settings::e_level)2;
}

void Hf2pLoadPreferencesHook() // 0x10A72490
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Hf2pLoadPreferencesHook@@YAXXZ");
	// `anonymous-namespace'::Hf2pLoadPreferencesHook
	// procedure flags: nofpo
	// static ...; // 0x10A729E3
	// static ...; // 0x10A729CC
	// static ...; // 0x10A729C0
	// static ...; // 0x10A7299C
	// static ...; // 0x10A72994
	// Modules::ModuleSettings const &moduleSettings;
	// Common::D3DAdapters::DisplayMode displayMode;
	// Modules::ModuleInput const &moduleInput;
	// void (*const global_preferences_create_default)();
	// __int32 screenResolutionWidth;
	// long (*const create_default_input_settings)(s_global_preferences_settings::s_input_settings *);
	// Modules::ModuleCamera const &moduleCamera;
	// s_global_preferences *prefs;
	// __int32 screenResolutionHeight;
	// function call : long (*const)(s_global_preferences_settings::s_input_settings *)

	Modules::ModuleSettings const &moduleSettings = Utils::Singleton<Modules::ModuleSettings>::Instance();
	Modules::ModuleCamera const &moduleCamera = Utils::Singleton<Modules::ModuleCamera>::Instance();
	Modules::ModuleInput const &moduleInput = Utils::Singleton<Modules::ModuleInput>::Instance();
	long (*const create_default_input_settings)(s_global_preferences_settings::s_input_settings *) = reinterpret_cast<long (*)(s_global_preferences_settings::s_input_settings *)>(0x50AC70);
	void (*const global_preferences_create_default)() = reinterpret_cast<void (*)()>(0x50A520);
	__int32 screenResolutionWidth, screenResolutionHeight;
	moduleSettings.GetScreenResolution(&screenResolutionWidth, &screenResolutionHeight);
	Common::D3DAdapters::EnumerateDisplayModes();
	Common::D3DAdapters::DisplayMode displayMode = Common::D3DAdapters::GetClosestSupportedDisplayMode(screenResolutionWidth, screenResolutionHeight);
	s_global_preferences *prefs = tls_getd().preferences;
	memset(&prefs->current, 0, sizeof(s_global_preferences_data));
	prefs->current.settings.version = 51;
	prefs->current.settings.lanquage = -1;
	prefs->current.settings.last_font_lanquage = -1;
	prefs->current.settings.build_number = 0;
	prefs->current.settings.privacy_mode = 1;
	prefs->current.settings.display_adapter = displayMode.adapterIndex;
	prefs->current.settings.video_settings.field_0 = 4;
	prefs->current.settings.display_type = s_global_preferences_settings::_display_mode_default;
	prefs->current.settings.field_41C4A = 1;
	create_default_input_settings(&prefs->current.settings.input_settings);
	prefs->current.settings.display_fullscreen = moduleSettings.VarFullscreen->ValueInt != 0;
	prefs->current.settings.display_contrast = moduleSettings.VarContrast->ValueInt;
	prefs->current.settings.display_brightness = moduleSettings.VarBrightness->ValueInt;
	prefs->current.settings.video_settings.resolution_width_wide = displayMode.width;
	prefs->current.settings.video_settings.resolution_height_wide = displayMode.height;
	prefs->current.settings.video_settings.texture_resolution = LevelStringToSetting(moduleSettings.VarTextureResolution->ValueString);
	prefs->current.settings.video_settings.shadow_quality = LevelStringToSetting(moduleSettings.VarShadowQuality->ValueString);
	prefs->current.settings.video_settings.texture_filtering_quality = LevelStringToSetting(moduleSettings.VarTextureFilteringQuality->ValueString);
	prefs->current.settings.video_settings.lighting_quality = LevelStringToSetting(moduleSettings.VarLightingQuality->ValueString);
	prefs->current.settings.video_settings.effects_quality = LevelStringToSetting(moduleSettings.VarEffectsQuality->ValueString);
	prefs->current.settings.video_settings.details_quality = LevelStringToSetting(moduleSettings.VarDetailsQuality->ValueString);
	prefs->current.settings.video_settings.postprocessing_quality = LevelStringToSetting(moduleSettings.VarPostprocessingQuality->ValueString);
	prefs->current.settings.video_settings.motion_blur = moduleSettings.VarMotionBlur->ValueInt != 0;
	prefs->current.settings.video_settings.vsync = moduleSettings.VarVSync->ValueInt != 0;
	prefs->current.settings.video_settings.anti_aliasing = moduleSettings.VarAntialiasing->ValueInt != 0;
	prefs->current.settings.hide_watermark = true;
	prefs->current.settings.master_volume = moduleSettings.VarMasterVolume->ValueInt;
	prefs->current.settings.sfx_volume = moduleSettings.VarSfxVolume->ValueInt;
	prefs->current.settings.music_volume = moduleSettings.VarMusicVolume->ValueInt * 2;
	prefs->current.settings.toggle_crouch = moduleSettings.VarToggleCrouch->ValueInt != 0;
	prefs->current.settings.voice_volume = 100;
	prefs->current.settings.hud_shake = moduleSettings.VarHUDShake->ValueInt != 0;
	prefs->current.settings.team_markers = moduleSettings.VarPlayerMarkerColors->ValueInt;
	prefs->current.settings.camera_fov = moduleCamera.VarCameraFov->ValueFloat;
	prefs->current.settings.input_settings.type = (s_global_preferences_settings::e_input_type)moduleSettings.VarGamepadEnabled->ValueInt;
	prefs->current.settings.input_settings.mouse_sensitivity_horizontal = moduleSettings.VarMouseSensitivityHorizontal->ValueInt;
	prefs->current.settings.input_settings.mouse_sensitivity_vertical = moduleSettings.VarMouseSensitivityVertical->ValueInt;
	prefs->current.settings.input_settings.mouse_sensitivity_vehicle_horizontal = moduleSettings.VarMouseSensitivityVehicleHorizontal->ValueInt;
	prefs->current.settings.input_settings.mouse_sensitivity_vehicle_vertical = moduleSettings.VarMouseSensitivityVehicleVertical->ValueInt;
	prefs->current.settings.input_settings.mouse_acceleration = moduleSettings.VarMouseAcceleration->ValueInt;
	prefs->current.settings.input_settings.mouse_filter = false;
	prefs->current.settings.input_settings.invert_mouse = moduleSettings.VarInvertMouse->ValueInt != 0;
	prefs->current.settings.display_subtitles = (s_global_preferences_settings::e_display_subtitles)moduleSettings.VarSubtitles->ValueInt;
	prefs->initialized = true;
}

void __fastcall c_game_engine_object_runtime_manager__update_hook(void *thisptr, void *unused) // 0x10A739D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_game_engine_object_runtime_manager__update_hook@@YIXPAX0@Z");
	// `anonymous-namespace'::c_game_engine_object_runtime_manager__update_hook
	// void *unused;
	// void (*const c_game_engine_object_runtime_manager__update)(void *);
	// function call : bool (*const)(char)
	// function call : void (*const)(void *)

	void (__thiscall *const c_game_engine_object_runtime_manager__update)(void *) = (void(__thiscall *const)(void *))0x5913e0;

	if (!((bool(__cdecl *const)(int))0x5523a0)(4))
		c_game_engine_object_runtime_manager__update(thisptr);
}

void ApplyDefaultScreenFx() // 0x10A71BC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyDefaultScreenFx@@YAXXZ");
	// `anonymous-namespace'::ApplyDefaultScreenFx
	// procedure flags: nofpo
	// static ...; // 0x10A71CA4
	// static ...; // 0x10A71C98
	// static ...; // 0x10A71C90
	// s_scenario *scnrDefinition;
	// constexpr void (*const `ApplyDefaultScreenFx'::`2'::SpawnScreenEffect)(unsigned __int32, unsigned __int32, __int32, void *, void *); // constant == 6828128
	// unsigned char unk[60];
	// s_scenario **scnrDefinitionPtr;
	// unsigned __int32 unitObjectIndex;
	// constexpr unsigned __int32 (*const `ApplyDefaultScreenFx'::`2'::GetLocalPlayerUnitObjectIndex)(__int32); // constant == 5807296
	// function call : unsigned __int32 (*const)(__int32)
	// function call : void (*const)(unsigned __int32, unsigned __int32, __int32, void *, void *)

	s_scenario **scnrDefinitionPtr = (s_scenario **)0x22AAEB4;

	if (!scnrDefinitionPtr)
		return;

	s_scenario *scnrDefinition = *scnrDefinitionPtr;

	if (scnrDefinition->default_screen_fx.index == -1)
		return;

	unsigned __int32 unitObjectIndex = ((unsigned __int32(__cdecl *)(__int32))0x589cc0)(*(__int32 *)0x18BF52C);

	unsigned char unk[60];
	memset(unk, 0, sizeof(unk));

	((void(__cdecl *)(unsigned __int32, unsigned __int32, __int32, void *, void *))0x683060)(scnrDefinition->default_screen_fx.index, unitObjectIndex, 0, unk, unk);
}

void game_initialize_for_new_map_call_hook(s_game_options *game_options) // 0x10A73F90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_initialize_for_new_map_call_hook@@YAXPAUs_game_options@@@Z");
	// `anonymous-namespace'::game_initialize_for_new_map_call_hook
	// s_game_options *game_options;
	// constexpr void (*const `game_initialize_for_new_map_call_hook'::`2'::game_initialize_for_new_map)(s_game_options *); // constant == 5445120
	// function call : void (*const)(s_game_options *)

	((void(__cdecl *)(s_game_options *))0x531600)(game_options);

	ApplyDefaultScreenFx();
}

bool game_finish_should_mute_sounds() // 0x10A73D90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_finish_should_mute_sounds@@YA_NXZ");
	// `anonymous-namespace'::game_finish_should_mute_sounds
	// procedure flags: nofpo
	// char (*const sound_set_class_volume)(char *, __int32, __int32, __int32);
	// bool (*const game_engine_running)();
	// function call : bool (*const)()

	const auto game_engine_running = (bool(*)())0x552410;
	const auto sound_set_class_volume = (char(*)(char *, __int32, __int32, __int32))0x660F40;

	if (Utils::Singleton<Modules::ModuleServer>::Instance().VarServerMuteSoundsDuringPostGameClient->ValueInt == 1)
	{
		return game_engine_running();
	}
	else
	{
		return false;
	}
}

void game_finished_wait_time_add_hook(float seconds) // 0x10A73E10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_finished_wait_time_add_hook@@YAXM@Z");
	// `anonymous-namespace'::game_finished_wait_time_add_hook
	// float seconds;
	// void (*const game_finished_wait_time_add)(float);
	// unsigned char fade_time;
	// function call : void (*const)(float)

	void (*const game_finished_wait_time_add)(float) = reinterpret_cast<void (*)(float)>(0x530FF0);
	unsigned char fade_time = Pointer(0x553750).Read<unsigned char>();
	Pointer(0x553750).Write<unsigned char>(fade_time + seconds);
	game_finished_wait_time_add(seconds);
}

bool game_engine_should_start_music_hook() // 0x10A73AE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_should_start_music_hook@@YA_NXZ");
	// `anonymous-namespace'::game_engine_should_start_music_hook
	// procedure flags: nofpo
	// static ...; // 0x10A73D04
	// static ...; // 0x10A73CF8
	// static ...; // 0x10A73CF0
	// long (*const game_engine_get_team_score)(unsigned __int32);
	// unsigned long near_victory_muisc_enabled;
	// long (*const game_engine_variant_get_score_to_win)();
	// unsigned long score_to_start_music_percentage;
		// unsigned long const score_needed;
		// long const score_to_win;
		// __int32 highest_score;
			// __int32 i;
				// long team_score;
			// c_data_array<s_player_datum> *players;
				// c_data_iterator<s_player_datum> it;
					// __int32 cur_player_score;
	// function call : long (*const)()
	// function call : bool (*const)()
	// function call : long (*const)(unsigned __int32)

	long (*const game_engine_variant_get_score_to_win)() = reinterpret_cast<long (*)()>(0x550B50);
	long (*const game_engine_get_team_score)(unsigned __int32) = reinterpret_cast<long (*)(unsigned __int32)>(0x550C90);
	unsigned long score_to_start_music_percentage = Utils::Singleton<Modules::ModuleServer>::Instance().VarServerNearVictoryMusicPercentClient->ValueInt;
	unsigned long near_victory_muisc_enabled = Utils::Singleton<Modules::ModuleServer>::Instance().VarServerNearVictoryMusicEnabledClient->ValueInt;
	if (near_victory_muisc_enabled != 1)
		return false;
	if (score_to_start_music_percentage == 0)
		return true;
	if (score_to_start_music_percentage > 0 && score_to_start_music_percentage <= 100)
	{
		long const score_to_win = game_engine_variant_get_score_to_win();
		if (score_to_win <= 0)
			return false;
		unsigned long const score_needed = score_to_win * score_to_start_music_percentage / 100;
		__int32 highest_score = 0;
		if (((bool (*)())0x5565E0)())
		{
			for (__int32 i = 0; i < 8; i++)
			{
				long team_score = game_engine_get_team_score(i);
				if (team_score > highest_score)
					highest_score = team_score;
			}
			return highest_score >= score_needed;
		}
		else
		{
			c_data_array<s_player_datum> *players = players_get();
			for (c_data_iterator<s_player_datum> it = players->begin(); it != players->end(); ++it)
			{
				if (!(it->flags & 2))
				{
					__int32 cur_player_score = game_engine_get_player_score(it.current_datum_index);
					if (cur_player_score > highest_score)
						highest_score = cur_player_score;
				}
			}
			return highest_score >= score_needed;
		}
	}
	return false;
}

long scenario_multiplayer_globals_try_and_get_runtime_data_hook() // 0x10A73FF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?scenario_multiplayer_globals_try_and_get_runtime_data_hook@@YAJXZ");
	// `anonymous-namespace'::scenario_multiplayer_globals_try_and_get_runtime_data_hook
	// procedure flags: nofpo
	// long result;
	// long (*const scenario_multiplayer_globals_try_and_get_runtime_data)();
	// function call : long (*const)()
	// function call : bool (*const)()

	const auto scenario_multiplayer_globals_try_and_get_runtime_data = (long(*)())0x69D310;

	long result = scenario_multiplayer_globals_try_and_get_runtime_data();

	if (((bool(__cdecl *const)())0x531B20)() && Utils::Singleton<Modules::ModuleServer>::Instance().VarServerPostMatchMusicEnabledClient->ValueInt == 1)
	{
		return result;
	}

	return 0;
}

bool game_engine_in_round_hook() // 0x10A73A60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_in_round_hook@@YA_NXZ");
	// `anonymous-namespace'::game_engine_in_round_hook
	// procedure flags: nofpo
	// bool roundInProgress;
	// bool (*const game_engine_round_in_progress)();
	// function call : bool (*const)()

	const auto game_engine_in_round = (bool(*)())0x550F90;

	bool roundInProgress = game_engine_in_round();

	if (Utils::Singleton<Modules::ModuleServer>::Instance().VarServerNearVictoryMusicEnabledClient->ValueInt == 1)
	{
		return roundInProgress;
	}

	return false;
}

/* ---------- explicit instantiations */
template unsigned char & Pointer::Read<unsigned char>() const;
