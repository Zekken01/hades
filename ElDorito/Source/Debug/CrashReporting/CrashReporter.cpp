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

namespace Debug
{
	namespace CrashReporting
	{
		extern char const *GetGameModeName(s_game_options *options);
		extern char const *FormatRegister(unsigned long value);
		extern void BuildStackTraceJSON(_CONTEXT const &ctx, rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer);
		extern void AddSystemInfo(rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer);
		extern void WriteDumpForCrashReporter(rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> &buffer, ::Debug::CrashReporting::s_crash_info const &crash);
		extern bool LaunchExternalCrashReporter(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &LaunchCommand);
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
		namespace
		{
			extern char const *kLifeCycleStateNames[18]; // 0x1134D270
		}
	}
}
/* ---------- public code */

extern char const *_sub_1068F380(s_game_options *);
namespace Debug
{
	namespace CrashReporting
	{
		char const *GetGameModeName(s_game_options *options) // 0x1068F380
		{
			mangled_x86(MANGLED_TODO, "?GetGameModeName@CrashReporting@Debug@@YAPBDPAUs_game_options@@@Z");
			// static ...; // 0x1068F420
		// $LN8:
		// $LN7:
		// $LN6:
		// $LN5:
		// $LN4:
			// s_game_options *options;
			todo("implement");
			char const * __result = _sub_1068F380(options);
			return __result;
		}
	}
}

extern char const *_sub_1068F1A0(unsigned long);
namespace Debug
{
	namespace CrashReporting
	{
		char const *FormatRegister(unsigned long value) // 0x1068F1A0
		{
			mangled_x86(MANGLED_TODO, "?FormatRegister@CrashReporting@Debug@@YAPBDK@Z");
			// unsigned long value;
			// static s_static_string<16> buff; // 0x11371970
			todo("implement");
			char const * __result = _sub_1068F1A0(value);
			return __result;
		}

		_extern void _sub_1068EA10(_CONTEXT const &, rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &);
		void BuildStackTraceJSON(_CONTEXT const &ctx, rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer) // 0x1068EA10
		{
			mangled_x86(MANGLED_TODO, "?BuildStackTraceJSON@CrashReporting@Debug@@YAXABU_CONTEXT@@AAV?$PrettyWriter@V?$GenericStringBuffer@U?$UTF8@D@rapidjson@@VCrtAllocator@2@@rapidjson@@U?$UTF8@D@2@U32@VCrtAllocator@2@$0A@@rapidjson@@@Z");
			// static ...; // 0x1068ECD1
			// static ...; // 0x1068ECC4
			// static ...; // 0x1068ECA0
			// static ...; // 0x1068EC98
			// _CONTEXT const &ctx;
			// rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer;
			// Debug::CrashReporting::StackWalker stackWalker;
			{
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > moduleName;
				// s_static_string<256> address_line;
				// HINSTANCE__ *hModule;
				{
					// char const *ed_relative_path;
					// char const *filename;
					// static s_static_string<4096> address_line; // 0x11371980
				}
			}
			todo("implement");
			_sub_1068EA10(ctx, writer);
		}

		_extern void _sub_1068E610(rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &);
		void AddSystemInfo(rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer) // 0x1068E610
		{
			mangled_x86(MANGLED_TODO, "?AddSystemInfo@CrashReporting@Debug@@YAXAAV?$PrettyWriter@V?$GenericStringBuffer@U?$UTF8@D@rapidjson@@VCrtAllocator@2@@rapidjson@@U?$UTF8@D@2@U32@VCrtAllocator@2@$0A@@rapidjson@@@Z");
			// static ...; // 0x1068E8C5
			// static ...; // 0x1068E8B4
			// static ...; // 0x1068E8AC
			// static ...; // 0x1068E888
			// static ...; // 0x1068E880
			// rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > gpuDriverVersion;
			// _MEMORYSTATUSEX memInfo;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > gpuName;
			// function call : __int32 (_MEMORYSTATUSEX *)
			todo("implement");
			_sub_1068E610(writer);
		}

		_extern void _sub_106913E0(rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> &, ::Debug::CrashReporting::s_crash_info const &);
		void WriteDumpForCrashReporter(rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> &buffer, ::Debug::CrashReporting::s_crash_info const &crash) // 0x106913E0
		{
			mangled_x86(MANGLED_TODO, "?WriteDumpForCrashReporter@CrashReporting@Debug@@YAXAAV?$GenericStringBuffer@U?$UTF8@D@rapidjson@@VCrtAllocator@2@@rapidjson@@ABUs_crash_info@12@@Z");
			// static ...; // 0x10691CC7
			// static ...; // 0x10691CB6
			// static ...; // 0x10691CA4
			// static ...; // 0x10691CA0
			// static ...; // 0x10691C9C
			// static ...; // 0x10691C94
			// static ...; // 0x10691C40
			// static ...; // 0x10691C38
			// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> &buffer;
			// Debug::CrashReporting::s_crash_info const &crash;
			// char uid[17];
			// rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
			// c_network_session *session;
			{
				// s_game_options *game_options;
				// bool (*const game_time_initialized)();
				{
					// s_static_string<16> game_variant_name;
					// s_static_string<16> map_variant_name;
				}
			}
			{
				// Ref<IMod> mod;
			}
			{
			}
			{
				// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &<range>$L0;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const *<begin>$L0;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const *<end>$L0;
				{
					// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &tag_name;
				}
			}
			// function call : bool (*const)()
			// function call : long (*const)()
			// function call : Ref<IMod> (EModIndex) const
			// function call : char const *() const
			// function call : Ref<IMod> (EModIndex) const
			// function call : char const *() const
			// function call : bool (*const)(c_network_session **)
			todo("implement");
			_sub_106913E0(buffer, crash);
		}

		_extern bool _sub_1068FF20(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
		bool LaunchExternalCrashReporter(std::basic_string<char,std::char_traits<char>,std::allocator<char> > &LaunchCommand) // 0x1068FF20
		{
			mangled_x86(MANGLED_TODO, "?LaunchExternalCrashReporter@CrashReporting@Debug@@YA_NAAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10690060
			// static ...; // 0x10690054
			// static ...; // 0x1069003C
			// static ...; // 0x10690034
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &LaunchCommand;
			// _PROCESS_INFORMATION processInfo;
			// _STARTUPINFOA info;
			// function call : __int32 (char const *, char *, _SECURITY_ATTRIBUTES *, _SECURITY_ATTRIBUTES *, __int32, unsigned long, void *, char const *, _STARTUPINFOA *, _PROCESS_INFORMATION *)
			// function call : unsigned long ()
			// function call : __int32 (void *)
			// function call : __int32 (void *)
			todo("implement");
			bool __result = _sub_1068FF20(LaunchCommand);
			return __result;
		}

		_extern void _sub_10690840(::Debug::CrashReporting::s_crash_info const &);
		void ReportCrash(::Debug::CrashReporting::s_crash_info const &crash) // 0x10690840
		{
			mangled_x86(MANGLED_TODO, "?ReportCrash@CrashReporting@Debug@@YAXABUs_crash_info@12@@Z");
			// static ...; // 0x10690C66
			// static ...; // 0x10690C58
			// static ...; // 0x10690C4A
			// static ...; // 0x10690C43
			// static ...; // 0x10690C38
			// static ...; // 0x10690BFC
			// static ...; // 0x10690BF4
			// Debug::CrashReporting::s_crash_info const &crash;
			// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > ReporterPath;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > LaunchCommand;
			// std::basic_ofstream<char,std::char_traits<char> > crash_dump;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > CrashDumpPath;
			todo("implement");
			_sub_10690840(crash);
		}
	}
}

/* ---------- private code */
