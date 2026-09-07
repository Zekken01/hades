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

extern bool CanAccessFolder(char const *folderName, unsigned long genericAccessRights);
extern bool EnsureChildProcessTermination();
extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetExceptionMessage(_EXCEPTION_RECORD const &exceptionRecord);
extern long __stdcall TopLevelExceptionFilter(_EXCEPTION_POINTERS *ExceptionInfo);
extern __int32 __stdcall WinMainHook(HINSTANCE__ *hInstance, HINSTANCE__ *hPrevInstance, char *lpCmdLine, __int32 nCmdShow);
extern __int32 InitInstance(HINSTANCE__ *hModule);
extern __int32 ExitInstance();
extern __int32 GetEDVersion();
extern "C" __int32 __stdcall DllMain(HINSTANCE__ *hModule, unsigned long Reason, void *Misc);

void HandleFinder();

/* ---------- globals */

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
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const DefaultTypes[8]; // 0x1240F698
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const DefaultTypeNames[8]; // 0x1240F778
		}
		using namespace hades_file_local_Server_Voting;
	}
}
namespace Server
{
	namespace hades_file_local_Server
	{
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > DefaultBanListPath; // 0x1240F858
	}
	using namespace hades_file_local_Server;
}
/* ---------- public code */

extern ElDorito* _sub_109638F0(ElDorito *const);
ElDorito::ElDorito() // 0x109638F0
{
	mangled_x86(MANGLED_TODO, "??0ElDorito@@QAE@XZ");
	// ElDorito *const this;
	todo("implement");
	_sub_109638F0(this);
}

namespace Audio
{
	extern IAudioDeviceListener* _sub_10963A50(::Audio::IAudioDeviceListener *const);
	_inline IAudioDeviceListener::IAudioDeviceListener() // 0x10963A50
	{
		mangled_x86(MANGLED_TODO, "??0IAudioDeviceListener@Audio@@QAE@XZ");
		// Audio::IAudioDeviceListener *const this;
		compiler_generated();
		todo("implement");
		_sub_10963A50(this);
	}
}

namespace Debug
{
	namespace CrashReporting
	{
		extern s_crash_info* _sub_10963A80(::Debug::CrashReporting::s_crash_info *const);
		_inline s_crash_info::s_crash_info() // 0x10963A80
		{
			mangled_x86(MANGLED_TODO, "??0s_crash_info@CrashReporting@Debug@@QAE@XZ");
			// Debug::CrashReporting::s_crash_info *const this;
			compiler_generated();
			todo("implement");
			_sub_10963A80(this);
		}
	}
}

_extern void _sub_10965070(ElDorito *const);
void ElDorito::Initialize() // 0x10965070
{
	mangled_x86(MANGLED_TODO, "?Initialize@ElDorito@@QAEXXZ");
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
	// std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > wide_ed_appdata;
	// __int32 numArgs;
	// CommandLineArgs cmdArgs;
	// wchar_t *localAppdata;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > ed_appdata;
	{
		// __int32 i;
		{
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > arg;
		}
	}
	{
		// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
		// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > keystream;
	}
	{
	}
	{
		{
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > argvalue;
			// unsigned __int32 pos;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > argname;
			{
				// __int32 proc;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > command;
			}
			{
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > filePath;
			}
		}
	}
	{
		// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > connectString;
	}
	// function call : HRESULT (void *)
	// function call : unsigned long ()
	// function call : __int32 (char const *, _SECURITY_ATTRIBUTES *)
	// function call : wchar_t *()
	// function call : __int32 (char const *, _SECURITY_ATTRIBUTES *)
	todo("implement");
	_sub_10965070(this);
}

namespace Server
{
	_extern void _sub_10963FE0(Server::BanList *const);
	_inline BanList::~BanList() // 0x10963FE0
	{
		mangled_x86(MANGLED_TODO, "??1BanList@Server@@QAE@XZ");
		// Server::BanList *const this;
		compiler_generated();
		todo("implement");
		_sub_10963FE0(this);
	}
}

namespace Debug
{
	namespace CrashReporting
	{
		_extern void _sub_10964050(::Debug::CrashReporting::s_crash_info *const);
		_inline s_crash_info::~s_crash_info() // 0x10964050
		{
			mangled_x86(MANGLED_TODO, "??1s_crash_info@CrashReporting@Debug@@QAE@XZ");
			// Debug::CrashReporting::s_crash_info *const this;
			compiler_generated();
			todo("implement");
			_sub_10964050(this);
		}
	}
}

extern CModBrowserManager* _sub_10963850(CModBrowserManager *const);
_inline CModBrowserManager::CModBrowserManager() // 0x10963850
{
	mangled_x86(MANGLED_TODO, "??0CModBrowserManager@@QAE@XZ");
	// CModBrowserManager *const this;
	compiler_generated();
	todo("implement");
	_sub_10963850(this);
}

extern CServerConnectManager* _sub_109638A0(CServerConnectManager *const);
_inline CServerConnectManager::CServerConnectManager() // 0x109638A0
{
	mangled_x86(MANGLED_TODO, "??0CServerConnectManager@@QAE@XZ");
	// CServerConnectManager *const this;
	compiler_generated();
	todo("implement");
	_sub_109638A0(this);
}

_extern void _sub_10966B70(ElDorito *const);
void ElDorito::Shutdown() // 0x10966B70
{
	mangled_x86(MANGLED_TODO, "?Shutdown@ElDorito@@QAEXXZ");
	// ElDorito *const this;
	todo("implement");
	_sub_10966B70(this);
}

_extern void _sub_10966B50(ElDorito *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
void ElDorito::SetMapsFolder(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path) // 0x10966B50
{
	mangled_x86(MANGLED_TODO, "?SetMapsFolder@ElDorito@@AAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path;
	todo("implement");
	_sub_10966B50(this, path);
}

_extern void _sub_10966BD0(ElDorito *const);
void ElDorito::Tick() // 0x10966BD0
{
	mangled_x86(MANGLED_TODO, "?Tick@ElDorito@@QAEXXZ");
	// static ...; // 0x10966DEC
	// static ...; // 0x10966DE0
	// static ...; // 0x10966DD8
	// ElDorito *const this;
	{
		// float speed;
		// c_network_session *session;
		// Modules::ModuleTime const &moduleTime;
	}
	// function call : bool (*const)()
	// function call : bool (*const)(c_network_session **)
	todo("implement");
	_sub_10966BD0(this);
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10964690(ElDorito *const);
std::basic_string<char,std::char_traits<char>,std::allocator<char> > ElDorito::GetDirectory() // 0x10964690
{
	mangled_x86(MANGLED_TODO, "?GetDirectory@ElDorito@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// static ...; // 0x1096493D
	// static ...; // 0x10964938
	// static ...; // 0x10964934
	// static ...; // 0x10964910
	// static ...; // 0x10964908
	// ElDorito *const this;
	// HINSTANCE__ *hMod;
	// char Path[260];
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > Dir;
	{
		// __int32 Error;
	}
	// function call : __int32 (unsigned long, char const *, HINSTANCE__ **)
	// function call : unsigned long ()
	// function call : void (char const *)
	// function call : unsigned long (HINSTANCE__ *, char *, unsigned long)
	todo("implement");
	std::string __result = _sub_10964690(this);
	return __result;
}

_extern void _sub_10966AA0(ElDorito *const);
void ElDorito::OnMainMenuShown() // 0x10966AA0
{
	mangled_x86(MANGLED_TODO, "?OnMainMenuShown@ElDorito@@QAEXXZ");
	// ElDorito *const this;
	todo("implement");
	_sub_10966AA0(this);
}

_extern void _sub_10967AF0(ElDorito *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
void ElDorito::setWatermarkText(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &Message) // 0x10967AF0
{
	mangled_x86(MANGLED_TODO, "?setWatermarkText@ElDorito@@AAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// static ...; // 0x10967D3C
	// static ...; // 0x10967D34
	// ElDorito *const this;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &Message;
	// static wchar_t msgBuf[256]; // 0x1240F878
	// std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > msgUnicode;
	todo("implement");
	_sub_10967AF0(this, Message);
}

_extern bool _sub_10964160(char const *, unsigned long);
bool CanAccessFolder(char const *folderName, unsigned long genericAccessRights) // 0x10964160
{
	mangled_x86(MANGLED_TODO, "?CanAccessFolder@@YA_NPBDK@Z");
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
	{
		// void *security;
		{
			// void *hToken;
			{
				// void *hImpersonatedToken;
				{
					// unsigned long privilegesLength;
					// unsigned long grantedAccess;
					// _GENERIC_MAPPING mapping;
					// __int32 result;
					// _PRIVILEGE_SET privileges;
				}
			}
		}
	}
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
	todo("implement");
	bool __result = _sub_10964160(folderName, genericAccessRights);
	return __result;
}

_extern bool _sub_10964530();
bool EnsureChildProcessTermination() // 0x10964530
{
	mangled_x86(MANGLED_TODO, "?EnsureChildProcessTermination@@YA_NXZ");
	// procedure flags: nofpo
	// static ...; // 0x10964624
	// static ...; // 0x10964618
	// static ...; // 0x10964610
	// void *hJob;
	{
		// _JOBOBJECT_EXTENDED_LIMIT_INFORMATION jobLimits;
	}
	// function call : void *(_SECURITY_ATTRIBUTES *, char const *)
	// function call : __int32 (void *, _JOBOBJECTINFOCLASS, void *, unsigned long)
	// function call : void *()
	// function call : __int32 (void *, void *)
	todo("implement");
	bool __result = _sub_10964530();
	return __result;
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10964A30(_EXCEPTION_RECORD const &);
std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetExceptionMessage(_EXCEPTION_RECORD const &exceptionRecord) // 0x10964A30
{
	mangled_x86(MANGLED_TODO, "?GetExceptionMessage@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABU_EXCEPTION_RECORD@@@Z");
	// static ...; // 0x10964C5C
	// static ...; // 0x10964C50
	// static ...; // 0x10964C48
	// _EXCEPTION_RECORD const &exceptionRecord;
	// char const *(*const exception_get_name)(unsigned long);
	// char const *name;
	// function call : char const *(*const)(unsigned long)
	todo("implement");
	std::string __result = _sub_10964A30(exceptionRecord);
	return __result;
}

_extern long _sub_10966E80(_EXCEPTION_POINTERS *);
long __stdcall TopLevelExceptionFilter(_EXCEPTION_POINTERS *ExceptionInfo) // 0x10966E80
{
	mangled_x86(MANGLED_TODO, "?TopLevelExceptionFilter@@YGJPAU_EXCEPTION_POINTERS@@@Z");
	// static ...; // 0x109670EF
	// static ...; // 0x109670EB
	// static ...; // 0x109670E6
	// static ...; // 0x109670DC
	// static ...; // 0x109670AC
	// static ...; // 0x109670A4
	// _EXCEPTION_POINTERS *ExceptionInfo;
	// HINSTANCE__ *hMod;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > moduleName;
	// static bool handling; // 0x1240F695
	// char info[1024];
	// Debug::CrashReporting::s_crash_info crashInfo;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > msg;
	todo("implement");
	long __result = _sub_10966E80(ExceptionInfo);
	return __result;
}

_extern __int32 _sub_109671A0(HINSTANCE__ *, HINSTANCE__ *, char *, __int32);
__int32 __stdcall WinMainHook(HINSTANCE__ *hInstance, HINSTANCE__ *hPrevInstance, char *lpCmdLine, __int32 nCmdShow) // 0x109671A0
{
	mangled_x86(MANGLED_TODO, "?WinMainHook@@YGHPAUHINSTANCE__@@0PADH@Z");
	// __int32 nCmdShow;
	// __int32 (*const WinMain)(HINSTANCE__ *, HINSTANCE__ *, char *, __int32);
	// function call : long (*(long (*)(_EXCEPTION_POINTERS *)))(_EXCEPTION_POINTERS *)
	// function call : __int32 (*const)(HINSTANCE__ *, HINSTANCE__ *, char *, __int32)
	todo("implement");
	__int32 __result = _sub_109671A0(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	return __result;
}

_extern __int32 _sub_10964D10(HINSTANCE__ *);
__int32 InitInstance(HINSTANCE__ *hModule) // 0x10964D10
{
	mangled_x86(MANGLED_TODO, "?InitInstance@@YAHPAUHINSTANCE__@@@Z");
	// static ...; // 0x10964FB3
	// static ...; // 0x10964FAC
	// static ...; // 0x10964F94
	// static ...; // 0x10964F8C
	// HINSTANCE__ *hModule;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > EDPath;
	// char appPath[260];
	// function call : __int32 (HINSTANCE__ *)
	// function call : __int32 ()
	// function call : unsigned long (HINSTANCE__ *, char *, unsigned long)
	// function call : __int32 (char const *)
	// function call : __int32 (HWND__ *, char const *, char const *, unsigned __int32)
	todo("implement");
	__int32 __result = _sub_10964D10(hModule);
	return __result;
}

_extern __int32 _sub_10964670();
__int32 ExitInstance() // 0x10964670
{
	mangled_x86(MANGLED_TODO, "?ExitInstance@@YAHXZ");
	// procedure flags: nofpo
	todo("implement");
	__int32 __result = _sub_10964670();
	return __result;
}

_extern __int32 _sub_109649F0();
__int32 GetEDVersion() // 0x109649F0
{
	mangled_x86(MANGLED_TODO, "?GetEDVersion@@YAHXZ");
	// procedure flags: nofpo
	todo("implement");
	__int32 __result = _sub_109649F0();
	return __result;
}

_extern __int32 _sub_10967E50(HINSTANCE__ *, unsigned long, void *);
extern "C" __int32 __stdcall DllMain(HINSTANCE__ *hModule, unsigned long Reason, void *Misc) // 0x10967E50
{
	mangled_x86(MANGLED_TODO, "_DllMain@12");
	// static ...; // 0x1096806C
	// static ...; // 0x10968064
// $LN11:
// $LN10:
// $LN9:
// $LN8:
	// HINSTANCE__ *hModule;
	// unsigned long Reason;
	// void *Misc;
	{
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > str;
		// __int32 offset;
		// char *cmd;
	}
	// function call : char *()
	// function call : char *()
	// function call : HINSTANCE__ *(HWND__ *, char const *, char const *, char const *, char const *, __int32)
	todo("implement");
	__int32 __result = _sub_10967E50(hModule, Reason, Misc);
	return __result;
}

/* ---------- private code */

namespace Debug
{
	namespace CrashReporting
	{
		_extern void _sub_10963AF0(::Debug::CrashReporting::s_crash_info::s_exception *const);
		_inline s_crash_info::s_exception::~s_exception() // 0x10963AF0
		{
			// Debug::CrashReporting::s_crash_info::<unnamed-type-exception>::~<unnamed-type-exception>
			// Debug::CrashReporting::s_crash_info::s_exception *const this;
			compiler_generated();
			todo("implement");
			_sub_10963AF0(this);
		}

		extern s_crash_info::s_exception* _sub_10963390(::Debug::CrashReporting::s_crash_info::s_exception *const);
		_inline s_crash_info::s_exception::s_exception() // 0x10963390
		{
			// Debug::CrashReporting::s_crash_info::<unnamed-type-exception>::<unnamed-type-exception>
			// Debug::CrashReporting::s_crash_info::s_exception *const this;
			compiler_generated();
			todo("implement");
			_sub_10963390(this);
		}
	}
}

_extern void _sub_10964CF0();
void HandleFinder() // 0x10964CF0
{
	// `anonymous-namespace'::HandleFinder
	// procedure flags: nofpo
	todo("implement");
	_sub_10964CF0();
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template CModBrowserManager & Utils::Singleton<CModBrowserManager>::Instance();
template CServerConnectManager & Utils::Singleton<CServerConnectManager>::Instance();
template Modules::ElModules & Utils::Singleton<Modules::ElModules>::Instance();
