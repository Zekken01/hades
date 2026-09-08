/* ---------- headers */

#include "Modules/ModuleDownload.hpp"
#include "hades/hades.h"

#include "Audio/AudioDeviceManager.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Console/Console.hpp"
#include "Download/DownloadStatCounter.hpp"
#include "Download/HttpFileDownload.hpp"
#include "Download/IDownload.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patches/CustomPackets.hpp"
#include "Utils/EventSink.hpp"
#include "Utils/Singleton.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <initializer_list>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <ratio>
#include <stdexcept>
#include <stop_token>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct lambda_1;
namespace Download
{
	class CHttpFileDownload;
}
namespace Modules
{
	class ModuleBase;
	class ModuleDownload;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Download {}
using namespace ::Download;
namespace Console {}
using namespace ::Console;
namespace Http {}
using namespace ::Http;

/* ---------- constants */

/* ---------- definitions */

//struct CommandDownloadHttp::__l2::ScopedDebugTrace
//{
//	__int32 m_oldValue; // 0x0
//	ScopedDebugTrace();
//	~ScopedDebugTrace();
//};
//static_assert(sizeof(CommandDownloadHttp::__l2::ScopedDebugTrace) == 4, "Invalid CommandDownloadHttp::__l2::ScopedDebugTrace size");

//class CommandDownloadHttp::__l2::<lambda_1>
//{
//public:
//	void operator()() const;
//	<lambda_1>(CommandDownloadHttp::__l2::<lambda_1> &);
//	<lambda_1>(CommandDownloadHttp::__l2::<lambda_1> const &);
//	<lambda_1>(std::shared_ptr<Download::CHttpFileDownload> const &, std::shared_ptr<`CommandDownloadHttp'::`2'::ScopedDebugTrace> &);
//private:
//	std::shared_ptr<Download::CHttpFileDownload> download; // 0x0
//	std::shared_ptr<`CommandDownloadHttp'::`2'::ScopedDebugTrace> trace; // 0x8
//public:
//	CommandDownloadHttp::__l2::<lambda_1> &operator=(CommandDownloadHttp::__l2::<lambda_1> const &);
//	~<lambda_1>(); /* compiler_generated() */
//};
//static_assert(sizeof(CommandDownloadHttp::__l2::<lambda_1>) == 16, "Invalid CommandDownloadHttp::__l2::<lambda_1> size");

/* ---------- prototypes */

bool CommandDownloadHttp(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &args, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &retValue);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	extern ModuleDownload* _sub_108563E0(Modules::ModuleDownload *const);
	ModuleDownload::ModuleDownload() : ModuleBase(todo_result<std::basic_string<char,std::char_traits<char>,std::allocator<char> >>()) // 0x108563E0
	{
		mangled_x86(MANGLED_TODO, "??0ModuleDownload@Modules@@QAE@XZ");
		// Modules::ModuleDownload *const this;
		todo("implement");
		_sub_108563E0(this);
	}
}

_inline CEventSink<>::SCallbackEntry::SCallbackEntry(CEventSink<>::SCallbackEntry &&__that) // 0x10856850
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SCallbackEntry@?$CEventSink@$$V@@QAE@$$QAU01@@Z");
	// CEventSink<>::SCallbackEntry &__that;

	compiler_generated();
}

/* ---------- private code */

_extern bool _sub_10856F10(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandDownloadHttp(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &args, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &retValue) // 0x10856F10
{
	// `anonymous-namespace'::CommandDownloadHttp
	// static ...; // 0x10857144
	// static ...; // 0x1085712C
	// static ...; // 0x10857124
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &args;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &retValue;
	// std::shared_ptr<Download::CHttpFileDownload> download;
	// std::shared_ptr<`CommandDownloadHttp'::`2'::ScopedDebugTrace> debugTrace;
	// function call : void ()
	todo("implement");
	bool __result = _sub_10856F10(args, retValue);
	return __result;
}
