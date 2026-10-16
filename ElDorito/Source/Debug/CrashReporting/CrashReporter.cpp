/* ---------- headers */

#include "Debug/CrashReporting/CrashReporter.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/cseries/static_string.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/networking/session/network_session_parameters_custom.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/RefCounting.hpp"
#include "Debug/CrashReporting/StalkWalker.hpp"
#include "ElDorito.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/font_package.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Modules/ModuleDebug.hpp"
#include "Modules/ModulePlayer.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/prettywriter.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Macros.hpp"
#include "Utils/ProcessUtils.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Utils/WebSocket.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <DbgHelp.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <fstream>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
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
#include <utility>
#include <vector>

/* ---------- forward declarations */

class ElDorito;
class IMod;
class c_network_session;
struct begin;
struct end;
struct s_game_options;
namespace Debug
{
	namespace CrashReporting
	{
		class StackWalker;
		struct s_crash_info;
	}
}
namespace Modules
{
	class ModuleDebug;
	class ModulePlayer;
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
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Debug {}
using namespace ::Debug;
namespace Debug
{
	namespace CrashReporting {}
	using namespace Debug::CrashReporting;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace PlayerUid {}
	using namespace Patches::PlayerUid;
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

/* ---------- prototypes */

namespace Patches { namespace PlayerUid { extern unsigned long long Get(); } }  // hades: added for 0x106913E0  // hades: added for 0x106913E0
#include "mods/mod_system.hpp"  // hades: added for 0x106913E0  // hades: added for 0x106913E0
namespace Utils { namespace FileUtils { char const *GetName(char const *filename); } }  // hades: added for 0x106913E0  // hades: added for 0x106913E0
extern void player_format_uid(char *string, unsigned long long id); extern long (*const game_time_get)(); extern bool (*const network_session_interface_get_squad_session)(c_network_session **);  // hades: added for 0x106913E0  // hades: added for 0x106913E0
namespace Debug { namespace CrashReporting { extern std::string TakeScreenshot(); } }  // hades: added for 0x106913E0  // hades: added for 0x106913E0

namespace Debug { namespace CrashReporting { std::string GetFriendlyOSName(); std::string GetCPUName(); bool GetGPUInfo(std::string &description, std::string &driverVersion); } }  // hades: added for 0x1068E610  // hades: added for 0x1068E610

#include "Utils/Logger.hpp"  // hades: added for 0x1068FF20  // hades: added for 0x1068FF20
namespace Utils { char const *GetLastErrorToText(unsigned long lastError); }  // hades: added for 0x1068FF20  // hades: added for 0x1068FF20

namespace hades_file_local { extern "C" s_static_string<16> buff; }  // hades: added for 0x1068F1A0

namespace Debug
{
	namespace CrashReporting
	{
		extern char const *GetGameModeName(s_game_options *options);
		extern char const *FormatRegister(unsigned long value);
		extern void BuildStackTraceJSON(_CONTEXT const &ctx, rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer);
		extern void AddSystemInfo(rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer);
		extern void WriteDumpForCrashReporter(rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> &buffer, ::Debug::CrashReporting::s_crash_info const &crash);
		extern bool LaunchExternalCrashReporter(std::string &LaunchCommand);
		extern void ReportCrash(::Debug::CrashReporting::s_crash_info const &crash);
	}
}

/* ---------- globals */

namespace Utils
{
	Utils::Logger *Utils::Singleton<Utils::Logger>::m_instance; // 0x11371964
	Modules::ModulePlayer *Utils::Singleton<Modules::ModulePlayer>::m_instance; // 0x11371958
	ElDorito *Utils::Singleton<ElDorito>::m_instance; // 0x11371960
	Modules::ModuleDebug *Utils::Singleton<Modules::ModuleDebug>::m_instance; // 0x11371968
}

/* ---------- private variables */

namespace Debug
{
	namespace CrashReporting
	{
		namespace hades_file_local_Debug_CrashReporting
		{
			extern char const *kLifeCycleStateNames[18]; // 0x1134D270
		}
		using namespace hades_file_local_Debug_CrashReporting;
	}
}
/* ---------- public code */


namespace Debug
{
	namespace CrashReporting
	{
		char const *GetGameModeName(s_game_options *options) // 0x1068F380
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetGameModeName@CrashReporting@Debug@@YAPBDPAUs_game_options@@@Z");

			switch ((e_game_mode)options->game_mode)
			{
			case 0:
				return "none";
			case 1:
				return options->game_is_survival ? "firefight" : "campaign";
			case 2:
				return "multiplayer";
			case 3:
				return "mainmenu";
			case 4:
				return "theater";
			default:
				return "unknown";
			}
		}
	}
}


namespace Debug
{
	namespace CrashReporting
	{
		char const *FormatRegister(unsigned long value) // 0x1068F1A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?FormatRegister@CrashReporting@Debug@@YAPBDK@Z");

			buff.print("%08X", value);
			return buff.get_string();
		}

		void BuildStackTraceJSON(_CONTEXT const &ctx, rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer) // 0x1068EA10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?BuildStackTraceJSON@CrashReporting@Debug@@YAXABU_CONTEXT@@AAV?$PrettyWriter@V?$GenericStringBuffer@U?$UTF8@D@rapidjson@@VCrtAllocator@2@@rapidjson@@U?$UTF8@D@2@U32@VCrtAllocator@2@$0A@@rapidjson@@@Z");

			writer.StartArray();
			StackWalker stackWalker(ctx);
			while (stackWalker.Next())
			{
				writer.StartObject();
				HINSTANCE__ *hModule = Utils::ProcessUtils::GetModuleFromAddress((void *)stackWalker.GetPCAddress());
				std::string moduleName = Utils::ProcessUtils::GetModuleNameForDisplay(hModule);
				s_static_string<256> address_line;
				address_line.print("%s+%X", moduleName.c_str(), stackWalker.GetPCAddress() - (unsigned __int32)hModule);
				writer.Key("address");
				writer.String(address_line.get_string());
				if (stackWalker.HasLineInfo())
				{
					char const *filename = stackWalker.GetFileName();
					char const *ed_relative_path = strstr(filename, "\\eldorito\\");
					if (ed_relative_path)
						filename = &ed_relative_path[10];
					static s_static_string<4096> address_line;
					address_line.print("%s:%d", filename, stackWalker.GetLineNumber());
					writer.Key("name");
					writer.String(stackWalker.GetFunctionName());
					writer.Key("line");
					writer.String(address_line);
				}
				else if (stackWalker.HasSymbolInfo())
				{
					writer.Key("name");
					writer.String(stackWalker.GetFunctionName());
				}
				writer.EndObject();
			}
			writer.EndArray();
		}

		void AddSystemInfo(rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer) // 0x1068E610
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?AddSystemInfo@CrashReporting@Debug@@YAXAAV?$PrettyWriter@V?$GenericStringBuffer@U?$UTF8@D@rapidjson@@VCrtAllocator@2@@rapidjson@@U?$UTF8@D@2@U32@VCrtAllocator@2@$0A@@rapidjson@@@Z");

			writer.Key("os");
			writer.String(GetFriendlyOSName().c_str());
			writer.Key("cpu");
			writer.String(GetCPUName().c_str());
			std::string gpuName;
			std::string gpuDriverVersion;
			GetGPUInfo(gpuName, gpuDriverVersion);
			writer.Key("gpu");
			writer.String(gpuName.c_str());
			writer.Key("gpu_driver");
			writer.String(gpuDriverVersion.c_str());
			_MEMORYSTATUSEX memInfo = { sizeof(memInfo) };
			if (GlobalMemoryStatusEx(&memInfo))
			{
				writer.Key("mem_total_physical");
				writer.Uint64(memInfo.ullTotalPhys);
				writer.Key("mem_avail_physical");
				writer.Uint64(memInfo.ullAvailPhys);
				writer.Key("mem_total_virtual");
				writer.Uint64(memInfo.ullTotalVirtual);
				writer.Key("mem_avail_virtual");
				writer.Uint64(memInfo.ullAvailVirtual);
			}
		}

		void WriteDumpForCrashReporter(rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> &buffer, ::Debug::CrashReporting::s_crash_info const &crash) // 0x106913E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?WriteDumpForCrashReporter@CrashReporting@Debug@@YAXAAV?$GenericStringBuffer@U?$UTF8@D@rapidjson@@VCrtAllocator@2@@rapidjson@@ABUs_crash_info@12@@Z");

			rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
			writer.StartObject();
			writer.Key("timestamp");
			writer.Int64(_time64(nullptr));
			writer.Key("build");
			writer.String("0.7.2-1759537232.debug");
			writer.Key("build_date");
			writer.String("Oct 4 2025");
			char uid[17];
			player_format_uid(uid, Patches::PlayerUid::Get());
			writer.Key("player_uid");
			writer.String(uid);
			writer.Key("player_name");
			writer.String(Utils::Singleton<Modules::ModulePlayer>::Instance().VarPlayerName->ValueString.c_str());
			if (!*(bool *)0x23917F1)
			{
				s_game_options *game_options = (s_game_options *)0x2391800;
				writer.Key("scenario");
				writer.String(game_options->scenario_path);
				if (*(bool *)0x23917F0)
				{
					writer.Key("map_loading");
					writer.Bool(true);
				}
				writer.Key("game_mode");
				writer.String(GetGameModeName(game_options));
				writer.Key("random_seed");
				writer.Uint(game_options->random_seed);
				if (game_options->game_mode == _game_mode_multiplayer)
				{
					writer.Key("game_engine");
					writer.String(game_engine_type_get_string(game_options->game_variant.game_engine_type));
					s_static_string<16> map_variant_name;
					map_variant_name.set_wchar(game_options->map_variant.metadata.name);
					s_static_string<16> game_variant_name;
					game_variant_name.set_wchar(reinterpret_cast<wchar_t const *>(game_options->game_variant.storage + 0x30));
					writer.Key("game_variant");
					writer.String(game_variant_name.get_string());
					writer.Key("map_variant");
					writer.String(map_variant_name.get_string());
				}
				bool (*const game_time_initialized)() = (bool (*)())0x564FA0;
				if (game_time_initialized())
				{
					writer.Key("game_time");
					writer.Int(game_time_get());
				}
			}
			{
				Ref<IMod> mod = c_mod_system::GetModManager().GetModShared(kMainMenu);
				if (mod)
				{
					writer.Key("mainmenu_mod");
					writer.String(Utils::FileUtils::GetName(mod->GetFilename()));
				}
			}
			{
				Ref<IMod> mod = c_mod_system::GetModManager().GetModShared(kGame);
				if (mod)
				{
					writer.Key("game_mod");
					writer.String(Utils::FileUtils::GetName(mod->GetFilename()));
				}
			}
			c_network_session *session;
			if (network_session_interface_get_squad_session(&session) && session->established())
			{
				writer.Key("session");
				writer.StartObject();
				writer.Key("life_cycle_state");
				writer.String(kLifeCycleStateNames[*(long *)0x19AB7F8]);
				writer.Key("host");
				writer.Bool(session->is_host());
				writer.Key("player_count");
				writer.Int(session->get_session_membership()->get_player_count());
				writer.EndObject();
			}
			if (ElDorito::Instance().IsDedicated())
			{
				writer.Key("dedicated");
				writer.Bool(true);
			}
			writer.Key("tag_history");
			writer.StartArray();
			for (std::string const &tag_name : crash.tag_history)
				writer.String(tag_name.c_str());
			writer.EndArray();
			writer.Key("info");
			writer.String(crash.info.c_str());
			writer.Key("stack");
			BuildStackTraceJSON(*crash.ctx, writer);
			writer.Key("registers");
			writer.StartObject();
			writer.Key("EAX");
			writer.String(FormatRegister(crash.ctx->Eax));
			writer.Key("EBX");
			writer.String(FormatRegister(crash.ctx->Ebx));
			writer.Key("ECX");
			writer.String(FormatRegister(crash.ctx->Ecx));
			writer.Key("EDX");
			writer.String(FormatRegister(crash.ctx->Edx));
			writer.Key("ESI");
			writer.String(FormatRegister(crash.ctx->Esi));
			writer.Key("EDI");
			writer.String(FormatRegister(crash.ctx->Edi));
			writer.Key("EIP");
			writer.String(FormatRegister(crash.ctx->Eip));
			writer.Key("ESP");
			writer.String(FormatRegister(crash.ctx->Esp));
			writer.Key("EBP");
			writer.String(FormatRegister(crash.ctx->Ebp));
			writer.Key("EFL");
			writer.String(FormatRegister(crash.ctx->EFlags));
			writer.EndObject();
			writer.Key("additional_info");
			writer.StartObject();
			AddSystemInfo(writer);
			writer.EndObject();
			writer.Key("screenshot");
			writer.String(TakeScreenshot().c_str());
			writer.EndObject();
		}

		bool LaunchExternalCrashReporter(std::string &LaunchCommand) // 0x1068FF20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?LaunchExternalCrashReporter@CrashReporting@Debug@@YA_NAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

			_STARTUPINFOA info = { sizeof(info) };
			_PROCESS_INFORMATION processInfo;
			if (!CreateProcessA(nullptr, LaunchCommand.data(), nullptr, nullptr, FALSE, CREATE_BREAKAWAY_FROM_JOB | DETACHED_PROCESS, nullptr, nullptr, &info, &processInfo))
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Debug, Utils::LogLevel::Error, "Error Launching CrashReporter: %s", Utils::GetLastErrorToText(GetLastError()));
				return false;
			}
			CloseHandle(processInfo.hProcess);
			CloseHandle(processInfo.hThread);
			return true;
		}

		void ReportCrash(::Debug::CrashReporting::s_crash_info const &crash) // 0x10690840
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ReportCrash@CrashReporting@Debug@@YAXABUs_crash_info@12@@Z");

			std::string ReporterPath = "" + ElDorito::Instance().GetDirectory() + "crash_reporter.exe";
			std::string CrashDumpPath = "" + ElDorito::Instance().GetDirectory() + "crash_dump.json";
			std::string LaunchCommand = "\"" + ReporterPath + "\" \"" + CrashDumpPath + "\"";
			if (ElDorito::Instance().IsDedicated())
				LaunchCommand += " --silent";
			rapidjson::StringBuffer buffer;
			WriteDumpForCrashReporter(buffer, crash);
			std::ofstream crash_dump(CrashDumpPath);
			crash_dump << buffer.GetString();
			crash_dump.close();
			if (!Modules::ModuleDebug::Instance().VarCrashReporting->ValueInt)
				return;
			LaunchExternalCrashReporter(LaunchCommand);
		}
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template ElDorito & Utils::Singleton<ElDorito>::Instance();
template IMod * Ref<IMod>::operator->() const;
template Modules::ModuleDebug & Utils::Singleton<Modules::ModuleDebug>::Instance();
template Modules::ModulePlayer & Utils::Singleton<Modules::ModulePlayer>::Instance();
template Ref<IMod>::operator IMod *() const;
template Ref<IMod>::~Ref();
template Utils::Logger & Utils::Singleton<Utils::Logger>::Instance();
template bool c_enum<enum e_game_mode,long>::operator==(e_game_mode const &) const;
template c_enum<enum e_game_engine_type,long>::operator enum e_game_engine_type() const;
template c_enum<enum e_game_mode,long>::operator enum e_game_mode() const;
template char const * s_static_string<16>::get_string() const;
template char const * s_static_string<16>::print(char const *, ...);
template char const * s_static_string<256>::get_string() const;
template char const * s_static_string<256>::print(char const *, ...);
template char const * s_static_string<4096>::get_string() const;
template char const * s_static_string<4096>::print(char const *, ...);
template s_static_string<4096>::operator char const *() const;
template void const s_static_string<16>::print_va(char const *, char *);
template void const s_static_string<256>::print_va(char const *, char *);
template void const s_static_string<4096>::print_va(char const *, char *);
template void s_static_string<16>::set_wchar(wchar_t const *);

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace Debug { namespace CrashReporting { namespace hades_file_local_Debug_CrashReporting { char const *kLifeCycleStateNames[18] = { "none", "pre-game", "start-game", "in-game", "end-game-write-stats", "leaving", "joining", "matchmaking-start", "matchmaking-find-match-client", "matchmaking-find_match", "matchmaking-find-and-assemble-match", "matchmaking-assemble-match", "matchmaking-arbitration", "matchmaking-select-host", "matchmaking-prepare-map", "in-match", "end-match-write-stats", "post-match" }; } } }
namespace hades_file_local { extern "C" { s_static_string<16> buff; } }
