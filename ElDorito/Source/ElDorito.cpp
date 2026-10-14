/* ---------- headers */

#include "ElDorito.hpp"
#include "hades/hades.h"

#include "Audio/AudioDeviceManager.hpp"
#include "Blam/BlamInput.hpp"
#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandLineArgs.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Console/Console.hpp"
#include "Debug/CrashReporting/CrashReporter.hpp"
#include "Download/IDownload.hpp"
#include "ElModules.hpp"
#include "Player/PlayerInfo.hpp"  // hades: added for 0x10965070
#include "mods/map_variant_loader.hpp"  // hades: added for 0x10965070
#include "Player/PlayerCharacterSystem.hpp"  // hades: added for 0x10965070
#include "Objects/ObjectMessaging.hpp"  // hades: added for 0x10965070
#include "mods/mod_system.hpp"  // hades: added for 0x10965070
#include "Modules/ModuleInput.hpp"  // hades: added for 0x10965070
#include "Forge/Magnets.hpp"
#include "Job/JobDefinitions.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Modules/ModuleTime.hpp"
#include "Patch.hpp"
#include "Patches/Network.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Player/PlayerEmblemDownload.hpp"
#include "Pointer.hpp"
#include "Server/BanList.hpp"
#include "Server/ClientDataTracker.hpp"
#include "Server/Connect/ServerConnect.hpp"
#include "Server/ModBrowser/ModBrowser.hpp"
#include "Server/ServerChat.hpp"
#include "Server/StatsServerBanList.hpp"
#include "Server/Voting/VotingPackets.hpp"
#include "Server/Voting/VotingTypes.hpp"
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
#include "Utils/EventSink.hpp"
#include "Utils/Macros.hpp"
#include "Utils/ProcessUtils.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>
#include <d3dx9core.h>
#include <d3dx9math.h>
#include <d3dx9math.inl>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <commctrl.h>
#include <dpa_dsa.h>
#include <propkeydef.h>
#include <propsys.h>
#include <shlobj_core.h>
#include <shobjidl.h>
#include <shobjidl_core.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <ostream>
#include <ratio>
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
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

/* ---------- forward declarations */

class CommandLineArgs;
class ElDorito;
class c_network_session;
struct CModBrowserManager;
struct CServerConnectManager;
namespace Audio
{
	class CAudioDeviceManager;
	struct IAudioDeviceListener;
}
namespace Blam
{
	namespace Input
	{
		class VirtualKeyboard;
	}
}
namespace Debug
{
	namespace CrashReporting
	{
		struct s_crash_info;
	}
}
namespace Modules
{
	class ElModules;
	class ModuleTime;
}
namespace Server
{
	class BanList;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace ChatCommands {}
using namespace ::ChatCommands;
namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace ClientDataTracker {}
	using namespace Server::ClientDataTracker;
	namespace VariableSynchronization {}
	using namespace Server::VariableSynchronization;
	namespace DedicatedServer {}
	using namespace Server::DedicatedServer;
	namespace Signaling {}
	using namespace Server::Signaling;
	namespace ReportHandler {}
	using namespace Server::ReportHandler;
	namespace InfoServer {}
	using namespace Server::InfoServer;
	namespace Stats {}
	using namespace Server::Stats;
	namespace HsGlobalSync {}
	using namespace Server::HsGlobalSync;
	namespace Rcon {}
	using namespace Server::Rcon;
	namespace Chat {}
	using namespace Server::Chat;
	namespace Voting {}
	using namespace Server::Voting;
	namespace BanListSync {}
	using namespace Server::BanListSync;
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

namespace Objects {}
using namespace ::Objects;
namespace Scripting {}
using namespace ::Scripting;
namespace Scripting
{
	namespace HS {}
	using namespace Scripting::HS;
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
		namespace WebDialog {}
		using namespace Web::Ui::WebDialog;
		namespace WebScoreboard {}
		using namespace Web::Ui::WebScoreboard;
		namespace WebSettings {}
		using namespace Web::Ui::WebSettings;
		namespace MpEventDispatcher {}
		using namespace Web::Ui::MpEventDispatcher;
		namespace WebChat {}
		using namespace Web::Ui::WebChat;
		namespace WebEmote {}
		using namespace Web::Ui::WebEmote;
		namespace WebLoadingScreen {}
		using namespace Web::Ui::WebLoadingScreen;
		namespace WebServerModBrowser {}
		using namespace Web::Ui::WebServerModBrowser;
		namespace WebMods {}
		using namespace Web::Ui::WebMods;
		namespace WebConsole {}
		using namespace Web::Ui::WebConsole;
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

namespace Debug {}
using namespace ::Debug;
namespace Debug
{
	namespace CrashReporting {}
	using namespace Debug::CrashReporting;
}

namespace Download {}
using namespace ::Download;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Camera {}
	using namespace Patches::Camera;
	namespace VirtualKeyboard {}
	using namespace Patches::VirtualKeyboard;
}

namespace Audio {}
using namespace ::Audio;
namespace Console {}
using namespace ::Console;
namespace Http {}
using namespace ::Http;
namespace PersistentMemory {}
using namespace ::PersistentMemory;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

typedef unsigned long SECURITY_INFORMATION;

/* ---------- prototypes */

namespace Patches { void ApplyRequired(); }  // hades: added for 0x10964D10

#include "Utils/Logger.hpp"  // hades: added for 0x10966E80
namespace hades_file_local { static bool handling = false; } // 0x1240F695  // hades: added for 0x10966E80

#include "Discord/DiscordRPC.h"  // hades: added for 0x10966BD0
#include "Modules/ModuleVoIP.hpp"  // hades: added for 0x10966BD0
#include "mods/map_variant_loader.hpp"  // hades: added for 0x10966BD0
#include "mods/mod_system.hpp"  // hades: added for 0x10966BD0
#include "Player/PlayerInfo.hpp"  // hades: added for 0x10966BD0
#include "Player/PlayerCharacterSystem.hpp"  // hades: added for 0x10966BD0
#include "Scripting/HaloScript/HaloScript.hpp"  // hades: added for 0x10966BD0
#include "Server/HsGlobalSync.hpp"  // hades: added for 0x10966BD0
#include "Web/Ui/ScreenLayer.hpp"  // hades: added for 0x10966BD0
namespace Server { namespace VariableSynchronization { extern void Tick(); } namespace Rcon { extern void Tick(); } namespace Signaling { extern void Tick(); } namespace DedicatedServer { extern void Tick(); } namespace InfoServer { extern void Tick(); } namespace Stats { extern void Tick(); } namespace Voting { extern void Tick(); } namespace BanListSync { extern void Tick(); } namespace ReportHandler { extern void Tick(); } }  // hades: added for 0x10966BD0
namespace Web { namespace Ui { namespace WebScoreboard { extern void Tick(); } namespace WebEmote { extern void Tick(); } } }  // hades: added for 0x10966BD0
namespace ChatCommands { extern void Tick(); }  // hades: added for 0x10966BD0
namespace Patches { extern void Tick(); }  // hades: added for 0x10966BD0
namespace Download { extern void Tick(); }  // hades: added for 0x10966BD0
namespace Utils { namespace AntiCheat { extern void OnTickCheck(); } }  // hades: added for 0x10966BD0
extern void game_time_set_speed(float speed);  // hades: added for 0x10966BD0
extern bool (*const network_session_interface_get_squad_session)(c_network_session **);  // hades: added for 0x10966BD0

namespace Download { extern void Shutdown(); }  // hades: added for 0x10966B70

namespace Utils { namespace Version { extern unsigned __int32 GetVersionInt(); } }  // hades: added for 0x109649F0

namespace Patches { void ApplyAfterInit(); }  // hades: added for 0X109671A0

extern bool CanAccessFolder(char const *folderName, unsigned long genericAccessRights);
extern bool EnsureChildProcessTermination();
extern std::string GetExceptionMessage(_EXCEPTION_RECORD const &exceptionRecord);
extern long __stdcall TopLevelExceptionFilter(_EXCEPTION_POINTERS *ExceptionInfo);
extern __int32 __stdcall WinMainHook(HINSTANCE__ *hInstance, HINSTANCE__ *hPrevInstance, char *lpCmdLine, __int32 nCmdShow);
extern __int32 InitInstance(HINSTANCE__ *hModule);
extern __int32 ExitInstance();
extern __int32 GetEDVersion();
extern "C" __int32 __stdcall DllMain(HINSTANCE__ *hModule, unsigned long Reason, void *Misc) noexcept(false);

void HandleFinder();

/* ---------- globals */

namespace Server { namespace DedicatedServer { extern void Init(); } }  // hades: added for 0x10966AA0

unsigned __int32 ElDorito::MainThreadID; // 0x1240F690
extern bool relaunch; // 0x1240F694
extern bool firstShow; // 0x11353C44
namespace Utils
{
	::Audio::CAudioDeviceManager *Utils::Singleton< ::Audio::CAudioDeviceManager>::m_instance; // 0x1240FB44
	CServerConnectManager *Utils::Singleton<CServerConnectManager>::m_instance; // 0x1240FB48
	CModBrowserManager *Utils::Singleton<CModBrowserManager>::m_instance; // 0x1240FB4C
	Modules::ElModules *Utils::Singleton<Modules::ElModules>::m_instance; // 0x1240FB40
}

/* ---------- private variables */

namespace Server
{
	namespace Voting
	{
		namespace hades_file_local_Server_Voting
		{
			// extern std::string const DefaultTypes[8]; // 0x1240F698  // hades: defined in VotingTypes.hpp, one copy per file
			// extern std::string const DefaultTypeNames[8]; // 0x1240F778  // hades: defined in VotingTypes.hpp, one copy per file
		}
		using namespace hades_file_local_Server_Voting;
	}
}
namespace Server
{
	namespace hades_file_local_Server
	{
		// extern std::string DefaultBanListPath; // 0x1240F858  // hades: defined (with its initialiser) elsewhere now
	}
	using namespace hades_file_local_Server;
}
/* ---------- public code */

ElDorito::ElDorito() : GameHasMenuShown(false), executeCommandQueue(false), isDedicated(false), isBotClient(false), isHighPriority(false), webDebugging(false), webDebugLogging(false), webdebugPort(8884), connectToServer(false), serverAddress(""), serverPassword(""), instanceName("") /* hades-mem-init:  */ // 0x109638F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0ElDorito@@QAE@XZ");
	// ElDorito *const this;
}

namespace Audio
{
	// mangled_x86(MANGLED_DEFAULT, "??0IAudioDeviceListener@Audio@@QAE@XZ"); no body to assert in
}

namespace Debug
{
	namespace CrashReporting
	{
		// mangled_x86(MANGLED_DEFAULT, "??0s_crash_info@CrashReporting@Debug@@QAE@XZ"); no body to assert in
	}
}

namespace Job { void Initialize(); }  // hades: added for 0x10965070
namespace Web::Ui { namespace ScreenLayer { void Init(); } namespace MpEventDispatcher { void Init(); } namespace WebChat { void Init(); } namespace WebScoreboard { void Init(); } namespace WebConsole { void Init(); } namespace WebLoadingScreen { void Init(); } namespace Voting { void Init(); } namespace WebSettings { void Init(); } namespace WebMods { void Init(); } namespace WebServerModBrowser { void Init(); } namespace WebDialog { void Init(); } namespace WebEmote { void Init(); } }  // hades: added for 0x10965070
namespace Patches::VirtualKeyboard { void Init(); }  // hades: added for 0x10965070
namespace Server { namespace Chat { void Initialize(); } namespace Stats { void Init(); } namespace Voting { void Init(); } namespace VariableSynchronization { void Initialize(); } namespace Rcon { void Initialize(); } namespace Signaling { void Initialize(); } namespace ReportHandler { void Init(); } namespace BanListSync { void Init(); } namespace HsGlobalSync { void Init(); } namespace ClientDataTracker { void Initialize(); } }  // hades: added for 0x10965070
namespace ChatCommands { void Init(); }  // hades: added for 0x10965070
namespace Download { void Init(); }  // hades: added for 0x10965070
namespace Scripting::HS { void Init(); }  // hades: added for 0x10965070
namespace Player::PlayerPodium { void Init(); }  // hades: added for 0x10965070
namespace PersistentMemory { void Init(); }  // hades: added for 0x10965070
namespace Utils { void LogEthernetAdapterInfo(); namespace Version { std::string GetVersionString(); } }  // hades: added for 0x10965070
void ElDorito::Initialize() // 0x10965070
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Initialize@ElDorito@@QAEXXZ");
	// static ...; // 0x1096622A
	// static ...; // 0x10966226
	// static ...; // 0x10966219
	// static ...; // 0x10966209
	// static ...; // 0x109661FE
	// static ...; // 0x109661F4
	// static ...; // 0x109661F1
	// static ...; // 0x109661EE
	// static ...; // 0x109661E4
	// static ...; // 0x109661E0
	// static ...; // 0x109661D8
	// static ...; // 0x109661CF
	// static ...; // 0x109661C7
	// static ...; // 0x109661BE
	// static ...; // 0x109661B0
	// static ...; // 0x109660FC
	// static ...; // 0x109660F4
	// ElDorito *const this;
	// std::wstring wide_ed_appdata;
	// __int32 numArgs;
	// CommandLineArgs cmdArgs;
	// wchar_t *localAppdata;
	// std::string ed_appdata;
		// __int32 i;
			// std::string arg;
		// std::stringstream ss;
		// std::stringstream keystream;
			// std::string argvalue;
			// unsigned __int32 pos;
			// std::string argname;
				// __int32 proc;
				// std::string command;
				// std::string filePath;
		// std::stringstream connectString;
	// function call : HRESULT (void *)
	// function call : unsigned long ()
	// function call : __int32 (char const *, _SECURITY_ATTRIBUTES *)
	// function call : wchar_t *()
	// function call : __int32 (char const *, _SECURITY_ATTRIBUTES *)

	if (FAILED(CoInitialize(NULL)))
		return;
	SetMainThreadID(GetCurrentThreadId());
	CreateDirectoryA(GetDirectory().c_str(), NULL);
	CommandLineArgs cmdArgs(Utils::String::ThinString(GetCommandLineW()));
	__int32 numArgs = cmdArgs.GetArgCount();
	if (numArgs > 1)
	{
		for (__int32 i = 1; i < numArgs; i++)
		{
			std::string arg = cmdArgs[i];
			if (arg.compare("-instance") == 0 && i < numArgs - 1)
				instanceName = cmdArgs[i + 1];
		}
	}
	Job::Initialize();
	::Audio::CAudioDeviceManager::Instance().Initialize();
	Console::Init();
	Modules::ElModules::Instance();
	Server::TempBanList::Instance();
	wchar_t *localAppdata;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppdata);
	std::wstring wide_ed_appdata(localAppdata);
	std::string ed_appdata = Utils::String::ThinString(wide_ed_appdata);
	ed_appdata += "\\ElDewrito";
	CreateDirectoryA(ed_appdata.c_str(), NULL);
	if (instanceName != "")
	{
		std::stringstream keystream;
		keystream << "Execute data\\dewrito_prefs_" << instanceName << ".cfg 1";
		Modules::CommandMap::Instance().ExecuteCommand(keystream.str());
		std::stringstream ss;
		ss << "Execute \"" << ed_appdata << "\\keys_" << instanceName << ".cfg\"";
		Modules::CommandMap::Instance().ExecuteCommand(ss.str());
	}
	else
	{
		std::stringstream ss;
		ss << "Execute data\\dewrito_prefs.cfg 1";
		Modules::CommandMap::Instance().ExecuteCommand(ss.str());
		std::stringstream keystream;
		keystream << "Execute \"" << ed_appdata << "\\keys.cfg\"";
		Modules::CommandMap::Instance().ExecuteCommand(keystream.str());
	}
	Modules::CommandMap::Instance().ExecuteCommand("Execute autoexec.cfg 1");
	if (!Modules::ModuleInput::Instance().IsCommandBound("game.takescreenshot"))
		Modules::CommandMap::Instance().ExecuteCommand("Bind PrintScreen Game.TakeScreenshot");
	if (!Modules::ModuleInput::Instance().IsCommandBound("game.showscreen browser"))
		Modules::CommandMap::Instance().ExecuteCommand("Bind F11 game.showscreen browser");
	if (!Modules::ModuleInput::Instance().IsCommandBound("Game.ShowLocalServersUI"))
		Modules::CommandMap::Instance().ExecuteCommand("Bind F10 Game.ShowLocalServersUI");
	if (!Modules::ModuleInput::Instance().IsCommandBound("Game.ShowModBrowser"))
		Modules::CommandMap::Instance().ExecuteCommand("Bind F9 Game.ShowModBrowser");
	if (!Modules::ModuleInput::Instance().IsCommandBound("Game.ShowModInfo"))
		Modules::CommandMap::Instance().ExecuteCommand("Bind F2 Game.ShowModInfo");
	Modules::CommandMap::Instance().CommitDirtyVariables();
	mapsFolder = "maps\\";
	if (numArgs > 1)
	{
		for (__int32 i = 1; i < numArgs; i++)
		{
			std::string arg = cmdArgs[i];
			if (arg.compare(0, 1, "-") != 0)
				continue;
			if (arg.compare("-highpriority") == 0)
				isHighPriority = true;
			if (arg.compare("-dedicated") == 0 || arg.compare("-headless") == 0)
			{
				isDedicated = true;
				Modules::CommandMap::Instance().ExecuteCommand("Server.Dedicated 1");
			}
			if (arg.compare("-bot") == 0)
				isBotClient = true;
			if (arg.compare("-maps") == 0 && i < numArgs - 1)
			{
				mapsFolder = cmdArgs[i + 1];
				if (mapsFolder.length() > 0 && mapsFolder.back() != '\\' && mapsFolder.back() != '/')
					mapsFolder += "\\";
			}
			if (arg.compare("-webdebug") == 0)
				webDebugging = true;
			if (arg.compare("-webdebug-port") == 0)
				webdebugPort = atoi(cmdArgs[i + 1]);
			if (arg.compare("-webdebug-log") == 0)
				webDebugLogging = true;
			if (arg.compare("-connect") == 0 && i < numArgs - 1)
			{
				serverAddress = cmdArgs[i + 1];
				connectToServer = true;
			}
			if (arg.compare("-password") == 0 && i < numArgs - 1)
				serverPassword = cmdArgs[i + 1];
			if (arg.compare("-debugger") == 0)
			{
				__int32 proc = _getpid();
				std::string command = "vsjitdebugger.exe -p " + std::to_string(proc);
				system(command.c_str());
			}
			if (arg.compare("-exec") == 0)
			{
				std::string filePath = cmdArgs[i + 1];
				Modules::CommandMap::Instance().ExecuteCommand(std::format("Execute \"{}\"", filePath));
			}
			unsigned __int32 pos = arg.find('=');
			if (pos == std::string::npos || arg.length() <= pos + 1)
				continue;
			std::string argname = arg.substr(1, pos - 1);
			std::string argvalue = arg.substr(pos + 1);
			Modules::CommandMap::Instance().ExecuteCommand(argname + " \"" + argvalue + "\"", true);
		}
	}
	webDebugging = true;
	if (!isDedicated)
	{
		Web::Ui::ScreenLayer::Init();
		Web::Ui::MpEventDispatcher::Init();
		Web::Ui::WebChat::Init();
		Web::Ui::WebScoreboard::Init();
		Web::Ui::WebConsole::Init();
		Web::Ui::WebLoadingScreen::Init();
		Web::Ui::Voting::Init();
		Web::Ui::WebSettings::Init();
		Web::Ui::WebMods::Init();
		Web::Ui::WebServerModBrowser::Init();
		Web::Ui::WebDialog::Init();
		Web::Ui::WebEmote::Init();
		Patches::VirtualKeyboard::Init();
		if (connectToServer)
		{
			std::stringstream connectString;
			connectString << "connect " << serverAddress << " " << serverPassword;
			Modules::CommandMap::Instance().ExecuteCommand(connectString.str());
		}
	}
	Modules::CommandMap::Instance().ExecuteCommand("register");
	setWatermarkText("ElDewrito | Version: " + Utils::Version::GetVersionString() + " | Build Date: Oct  3 2025");
	Server::SaveDefaultBanList(Server::LoadDefaultBanList());
	Server::Chat::Initialize();
	ChatCommands::Init();
	Server::Stats::Init();
	Player::CPlayersInfo::Init();
	Server::Voting::Init();
	Server::VariableSynchronization::Initialize();
	Server::Rcon::Initialize();
	Server::Signaling::Initialize();
	Server::ReportHandler::Init();
	Server::BanListSync::Init();
	Server::HsGlobalSync::Init();
	Server::ClientDataTracker::Initialize();
	Server::HsGlobalSync::Init();
	c_mod_system::initialize(IsDedicated());
	CServerConnectManager::Instance().Initialize();
	CModBrowserManager::Instance().Initialize();
	c_map_variant_loader::initialzie();
	Download::Init();
	Player::CPlayerCharacterSystem::Init();
	Scripting::HS::Init();
	Player::PlayerPodium::Init();
	PersistentMemory::Init();
	Objects::CObjectMessaging::Init();
	Utils::LogEthernetAdapterInfo();
}

namespace Server
{
	// mangled_x86(MANGLED_DEFAULT, "??1BanList@Server@@QAE@XZ"); no body to assert in
	_inline BanList::~BanList() = default; // 0x10963FE0
}

namespace Debug
{
	namespace CrashReporting
	{
		// mangled_x86(MANGLED_DEFAULT, "??1s_crash_info@CrashReporting@Debug@@QAE@XZ"); no body to assert in
		// hades: s_crash_info::~s_crash_info() is implicit (0x10964050)
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0CModBrowserManager@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0CServerConnectManager@@QAE@XZ"); no body to assert in

void ElDorito::Shutdown() // 0x10966B70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Shutdown@ElDorito@@QAEXXZ");
	// ElDorito *const this;

	Utils::Singleton<Utils::Logger>::Instance().Flush();
	Download::Shutdown();
}

void ElDorito::SetMapsFolder(std::string const &path) // 0x10966B50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetMapsFolder@ElDorito@@AAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// std::string const &path;
}

void ElDorito::Tick() // 0x10966BD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@ElDorito@@QAEXXZ");
	// static ...; // 0x10966DEC
	// static ...; // 0x10966DE0
	// static ...; // 0x10966DD8
	// ElDorito *const this;
		// float speed;
		// c_network_session *session;
		// Modules::ModuleTime const &moduleTime;
	// function call : bool (*const)()
	// function call : bool (*const)(c_network_session **)

	Server::VariableSynchronization::Tick();
	if (IsDedicated())
		Server::Rcon::Tick();
	Server::Signaling::Tick();
	Server::Chat::Tick();
	Patches::Tick();
	if (!isDedicated)
	{
		Web::Ui::ScreenLayer::Tick();
		Web::Ui::WebScoreboard::Tick();
		Web::Ui::WebEmote::Tick();
		Player::PlayerEmblemDownload::Instance().Tick();
	}
	else if (GameHasMenuShown)
		Server::DedicatedServer::Tick();
	Server::InfoServer::Tick();
	Server::Stats::Tick();
	Player::CPlayersInfo::Tick();
	Server::Voting::Tick();
	Server::BanListSync::Tick();
	Server::HsGlobalSync::Tick();
	ChatCommands::Tick();
	Server::ReportHandler::Tick();
	Discord::DiscordRPC::Instance().Update();
	Server::HsGlobalSync::Tick();
	Modules::ModuleVoIP::Instance().Tick();
	::Audio::CAudioDeviceManager::Instance().Update();
	CServerConnectManager::Instance().Update();
	CModBrowserManager::Instance().Update();
	c_map_variant_loader::update();
	Download::Tick();
	Player::CPlayerCharacterSystem::Tick();
	Scripting::HS::Tick();
	c_mod_system::update();
	Utils::AntiCheat::OnTickCheck();
	Modules::CommandMap::Instance().Update();
	if (executeCommandQueue)
	{
		Modules::CommandMap::Instance().ExecuteQueue();
		executeCommandQueue = false;
	}
	if (((bool(__cdecl *)())0x5314B0)())
	{
		Modules::ModuleTime const &moduleTime = Modules::ModuleTime::Instance();
		c_network_session *session;
		float speed = moduleTime.VarSpeedClient->ValueFloat;
		if (!network_session_interface_get_squad_session(&session))
			speed = moduleTime.VarSpeed->ValueFloat;
		game_time_set_speed(speed);
	}
}

std::string ElDorito::GetDirectory() // 0x10964690
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetDirectory@ElDorito@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// static ...; // 0x1096493D
	// static ...; // 0x10964938
	// static ...; // 0x10964934
	// static ...; // 0x10964910
	// static ...; // 0x10964908
	// ElDorito *const this;
	// HINSTANCE__ *hMod;
	// char Path[260];
	// std::string Dir;
		// __int32 Error;
	// function call : __int32 (unsigned long, char const *, HINSTANCE__ **)
	// function call : unsigned long ()
	// function call : void (char const *)
	// function call : unsigned long (HINSTANCE__ *, char *, unsigned long)

	char Path[260];
	HINSTANCE__ *hMod;
	if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (char const *)HandleFinder, &hMod))
	{
		__int32 Error = GetLastError();
		OutputDebugStringA(std::string("Unable to resolve current directory, error code: ").append(std::to_string(Error)).c_str());
	}
	GetModuleFileNameA(hMod, Path, sizeof(Path));
	std::string Dir(Path);
	Dir = Dir.substr(0, std::string(Dir).find_last_of('\\') + 1);
	return Dir;
}

void ElDorito::OnMainMenuShown() // 0x10966AA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnMainMenuShown@ElDorito@@QAEXXZ");
	// ElDorito *const this;

	if (GameHasMenuShown)
		return;

	GameHasMenuShown = true;
	executeCommandQueue = true;
	if (isDedicated)
		Server::DedicatedServer::Init();
}

void ElDorito::setWatermarkText(std::string const &Message) // 0x10967AF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?setWatermarkText@ElDorito@@AAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// static ...; // 0x10967D3C
	// static ...; // 0x10967D34
	// ElDorito *const this;
	// std::string const &Message;
	// static wchar_t msgBuf[256]; // 0x1240F878
	// std::wstring msgUnicode;

	static wchar_t msgBuf[256];
	wmemset(msgBuf, 0, 256);
	std::wstring msgUnicode = Utils::String::WidenString(Message);
	wcscpy_s(msgBuf, 256, msgUnicode.c_str());
	Pointer::Base(0x2E5338).Write<uint8_t>(0x68);
	Pointer::Base(0x2E5339).Write(&msgBuf);
	Pointer::Base(0x2E533D).Write<uint8_t>(0x90);
	Pointer::Base(0x2E533E).Write<uint8_t>(0x90);
}

bool CanAccessFolder(char const *folderName, unsigned long genericAccessRights) // 0x10964160
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CanAccessFolder@@YA_NPBDK@Z");
	// static ...; // 0x1096445C
	// static ...; // 0x10964449
	// static ...; // 0x10964441
	// static ...; // 0x10964436
	// static ...; // 0x10964428
	// static ...; // 0x10964417
	// static ...; // 0x10964410
	// static ...; // 0x109643B0
	// static ...; // 0x109643A8
	// char const *folderName;
	// unsigned long genericAccessRights;
	// bool bRet;
	// unsigned long length;
		// void *security;
			// void *hToken;
				// void *hImpersonatedToken;
					// unsigned long privilegesLength;
					// unsigned long grantedAccess;
					// _GENERIC_MAPPING mapping;
					// __int32 result;
					// _PRIVILEGE_SET privileges;
	// function call : __int32 (char const *, unsigned long, void *, unsigned long, unsigned long *)
	// function call : unsigned long ()
	// function call : __int32 (char const *, unsigned long, void *, unsigned long, unsigned long *)
	// function call : void *()
	// function call : __int32 (void *, unsigned long, void **)
	// function call : __int32 (void *, _SECURITY_IMPERSONATION_LEVEL, void **)
	// function call : void (unsigned long *, _GENERIC_MAPPING *)
	// function call : __int32 (void *, void *, unsigned long, _GENERIC_MAPPING *, _PRIVILEGE_SET *, unsigned long *, unsigned long *, __int32 *)
	// function call : __int32 (void *)
	// function call : __int32 (void *)

	bool bRet = false;
	DWORD length = 0;
	if (!::GetFileSecurity(folderName, OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION
		| DACL_SECURITY_INFORMATION, NULL, NULL, &length) &&
		ERROR_INSUFFICIENT_BUFFER == ::GetLastError()) {
		PSECURITY_DESCRIPTOR security = static_cast< PSECURITY_DESCRIPTOR >(::malloc(length));
		if (security && ::GetFileSecurity(folderName, OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION
			| DACL_SECURITY_INFORMATION, security, length, &length)) {
			HANDLE hToken = NULL;
			if (::OpenProcessToken(::GetCurrentProcess(), TOKEN_IMPERSONATE | TOKEN_QUERY |
				TOKEN_DUPLICATE | STANDARD_RIGHTS_READ, &hToken)) {
				HANDLE hImpersonatedToken = NULL;
				if (::DuplicateToken(hToken, SecurityImpersonation, &hImpersonatedToken)) {
					GENERIC_MAPPING mapping = { 0xFFFFFFFF };
					PRIVILEGE_SET privileges = { 0 };
					DWORD grantedAccess = 0, privilegesLength = sizeof(privileges);
					BOOL result = FALSE;
					mapping.GenericRead = FILE_GENERIC_READ;
					mapping.GenericWrite = FILE_GENERIC_WRITE;
					mapping.GenericExecute = FILE_GENERIC_EXECUTE;
					mapping.GenericAll = FILE_ALL_ACCESS;
					::MapGenericMask(&genericAccessRights, &mapping);
					if (::AccessCheck(security, hImpersonatedToken, genericAccessRights,
						&mapping, &privileges, &privilegesLength, &grantedAccess, &result)) {
						bRet = (result == TRUE);
					}
					::CloseHandle(hImpersonatedToken);
				}
				::CloseHandle(hToken);
			}
			::free(security);
		}
	}
	return bRet;
}

bool EnsureChildProcessTermination() // 0x10964530
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?EnsureChildProcessTermination@@YA_NXZ");
	// procedure flags: nofpo
	// static ...; // 0x10964624
	// static ...; // 0x10964618
	// static ...; // 0x10964610
	// void *hJob;
		// _JOBOBJECT_EXTENDED_LIMIT_INFORMATION jobLimits;
	// function call : void *(_SECURITY_ATTRIBUTES *, char const *)
	// function call : __int32 (void *, _JOBOBJECTINFOCLASS, void *, unsigned long)
	// function call : void *()
	// function call : __int32 (void *, void *)

	void *hJob = ::CreateJobObjectA(nullptr, nullptr);
	if (hJob)
	{
		JOBOBJECT_EXTENDED_LIMIT_INFORMATION jobLimits;
		::memset(&jobLimits, 0, sizeof(jobLimits));
		jobLimits.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE | JOB_OBJECT_LIMIT_BREAKAWAY_OK;
		if (!::SetInformationJobObject(hJob, JobObjectExtendedLimitInformation, &jobLimits, sizeof(jobLimits)))
			return false;

		if (!::AssignProcessToJobObject(hJob, ::GetCurrentProcess()))
			return false;
	}

	return true;
}

std::string GetExceptionMessage(_EXCEPTION_RECORD const &exceptionRecord) // 0x10964A30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetExceptionMessage@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABU_EXCEPTION_RECORD@@@Z");
	// static ...; // 0x10964C5C
	// static ...; // 0x10964C50
	// static ...; // 0x10964C48
	// _EXCEPTION_RECORD const &exceptionRecord;
	// char const *(*const exception_get_name)(unsigned long);
	// char const *name;
	// function call : char const *(*const)(unsigned long)

	char const *(*const exception_get_name)(unsigned long) = reinterpret_cast<char const *(*)(unsigned long)>(0x51BE40);
	char const *name = exception_get_name(exceptionRecord.ExceptionCode);
	if (!name)
		name = "UNKNOWN_EXCEPTION";
	if (exceptionRecord.ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
	{
		if (exceptionRecord.ExceptionInformation[1] == 0)
			return std::format("{} - tried to read address {:08x}", name, exceptionRecord.ExceptionInformation[0]);
		else if (exceptionRecord.ExceptionInformation[1] == 1)
			return std::format("{} - tried to write to address {:08x}", name, exceptionRecord.ExceptionInformation[0]);
		else if (exceptionRecord.ExceptionInformation[1] == 8)
			return std::format("{} - tried to execute address {:08x}", name, exceptionRecord.ExceptionInformation[0]);
	}
	return std::format("{} - code: {:08x}", name, exceptionRecord.ExceptionCode);
}

long __stdcall TopLevelExceptionFilter(_EXCEPTION_POINTERS *ExceptionInfo) // 0x10966E80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?TopLevelExceptionFilter@@YGJPAU_EXCEPTION_POINTERS@@@Z");
	// static ...; // 0x109670EF
	// static ...; // 0x109670EB
	// static ...; // 0x109670E6
	// static ...; // 0x109670DC
	// static ...; // 0x109670AC
	// static ...; // 0x109670A4
	// _EXCEPTION_POINTERS *ExceptionInfo;
	// HINSTANCE__ *hMod;
	// std::string moduleName;
	// static bool handling; // 0x1240F695
	// char info[1024];
	// Debug::CrashReporting::s_crash_info crashInfo;
	// std::string msg;

	if (handling)
		return EXCEPTION_EXECUTE_HANDLER;
	handling = true;
	Utils::Singleton<Utils::Logger>::Instance().Flush();
	HINSTANCE__ *hMod = Utils::ProcessUtils::GetModuleFromAddress(ExceptionInfo->ExceptionRecord->ExceptionAddress);
	std::string moduleName = Utils::ProcessUtils::GetModuleNameForDisplay(hMod);
	std::string msg = GetExceptionMessage(*ExceptionInfo->ExceptionRecord);
	char info[1024];
	sprintf_s(info, "%s - %s+%0X", msg.c_str(), moduleName.c_str(), (unsigned long)ExceptionInfo->ExceptionRecord->ExceptionAddress - (unsigned long)hMod);
	Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Debug, Utils::LogLevel::Error, info);
	Debug::CrashReporting::s_crash_info crashInfo;
	crashInfo.ctx = ExceptionInfo->ContextRecord;
	crashInfo.info = info;
	crashInfo.exception.address = (unsigned __int32)ExceptionInfo->ExceptionRecord->ExceptionAddress;
	crashInfo.exception.code = ExceptionInfo->ExceptionRecord->ExceptionCode;
	crashInfo.exception.flags = ExceptionInfo->ExceptionRecord->ExceptionFlags;
	crashInfo.exception.msg = msg;
	Debug::CrashReporting::ReportCrash(crashInfo);
	return EXCEPTION_EXECUTE_HANDLER;
}

__int32 __stdcall WinMainHook(HINSTANCE__ *hInstance, HINSTANCE__ *hPrevInstance, char *lpCmdLine, __int32 nCmdShow) // 0x109671A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?WinMainHook@@YGHPAUHINSTANCE__@@0PADH@Z");
	// __int32 nCmdShow;
	// __int32 (*const WinMain)(HINSTANCE__ *, HINSTANCE__ *, char *, __int32);
	// function call : long (*(long (*)(_EXCEPTION_POINTERS *)))(_EXCEPTION_POINTERS *)
	// function call : __int32 (*const)(HINSTANCE__ *, HINSTANCE__ *, char *, __int32)

	__int32 (__stdcall *const WinMainPtr)(HINSTANCE__ *, HINSTANCE__ *, char *, __int32) = (__int32(__stdcall *const)(HINSTANCE__ *, HINSTANCE__ *, char *, __int32))0x42eb10;

	SetUnhandledExceptionFilter(TopLevelExceptionFilter);
	Utils::Singleton<ElDorito>::Instance().Initialize();
	Patches::ApplyAfterInit();
	return WinMainPtr(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}

__int32 InitInstance(HINSTANCE__ *hModule) // 0x10964D10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?InitInstance@@YAHPAUHINSTANCE__@@@Z");
	// static ...; // 0x10964FB3
	// static ...; // 0x10964FAC
	// static ...; // 0x10964F94
	// static ...; // 0x10964F8C
	// HINSTANCE__ *hModule;
	// std::string EDPath;
	// char appPath[260];
	// function call : __int32 (HINSTANCE__ *)
	// function call : __int32 ()
	// function call : unsigned long (HINSTANCE__ *, char *, unsigned long)
	// function call : __int32 (char const *)
	// function call : __int32 (HWND__ *, char const *, char const *, unsigned __int32)

	DisableThreadLibraryCalls(hModule);
	SetProcessDPIAware();
	EnsureChildProcessTermination();
	char appPath[MAX_PATH];
	GetModuleFileNameA(hModule, appPath, MAX_PATH);
	std::string EDPath = appPath;
	EDPath = EDPath.substr(0, EDPath.find_last_of("\\"));
	SetCurrentDirectoryA(EDPath.c_str());
	if (!CanAccessFolder(".", GENERIC_READ | GENERIC_WRITE))
	{
		MessageBoxA(NULL, "Invalid permissions for the current directory, your game will be relaunched as Administrator.\nPlease set eldorado.exe to run as administrator or move your game to a different directory to avoid this message in the future.", "Invalid Directory Permissions", MB_ICONERROR);
		relaunch = true;
		return true;
	}
	Patches::ApplyRequired();
	Hook(0x7ED7C3, WinMainHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	return true;
}

__int32 ExitInstance() // 0x10964670
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ExitInstance@@YAHXZ");
	// procedure flags: nofpo

	return 1;
}

__int32 GetEDVersion() // 0x109649F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetEDVersion@@YAHXZ");
	// procedure flags: nofpo

	return Utils::Version::GetVersionInt();
}

extern "C" __int32 __stdcall DllMain(HINSTANCE__ *hModule, unsigned long Reason, void *Misc) noexcept(false) // 0x10967E50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_DllMain@12");
	// static ...; // 0x1096806C
	// static ...; // 0x10968064
// $LN11:
// $LN10:
// $LN9:
// $LN8:
	// HINSTANCE__ *hModule;
	// unsigned long Reason;
	// void *Misc;
		// std::string str;
		// __int32 offset;
		// char *cmd;
	// function call : char *()
	// function call : char *()
	// function call : HINSTANCE__ *(HWND__ *, char const *, char const *, char const *, char const *, __int32)

	switch (Reason)
	{
	case DLL_PROCESS_ATTACH:
		return InitInstance(hModule);
	case DLL_PROCESS_DETACH:
		return ExitInstance();
	case DLL_THREAD_ATTACH:
		return true;
	case DLL_THREAD_DETACH:
		if (relaunch)
		{
			char *cmd = GetCommandLineA();
			__int32 offset = 0;
			if (cmd[offset] == '"')
				while (cmd[++offset] != '"');
			while (cmd[++offset] != ' ');
			std::string str = static_cast<std::string>(GetCommandLineA());
			ShellExecuteA(nullptr, "runas", str.substr(0, offset).c_str(), str.substr(offset).c_str(), nullptr, SW_SHOWNORMAL);
			std::exit(0);
		}
		return true;
	}
	return false;
}

/* ---------- private code */

namespace Debug
{
	namespace CrashReporting
	{

	}
}

void HandleFinder() // 0x10964CF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleFinder@@YAXXZ");
	// the original is empty
	// `anonymous-namespace'::HandleFinder
	// procedure flags: nofpo
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template CModBrowserManager & Utils::Singleton<CModBrowserManager>::Instance();
template CServerConnectManager & Utils::Singleton<CServerConnectManager>::Instance();
template Modules::ElModules & Utils::Singleton<Modules::ElModules>::Instance();
