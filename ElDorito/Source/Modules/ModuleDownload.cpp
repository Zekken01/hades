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

bool CommandDownloadHttp(std::vector<std::string> const &args, std::string &retValue);
namespace Download { std::shared_ptr<CHttpFileDownload> CreateHttpFileDownload(); }  // hades: added for 0x10856F10

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	ModuleDownload::ModuleDownload() : ModuleBase("Download") /* hades-mem-init: : ModuleBase(todo_result<std::string>()) */ // 0x108563E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ModuleDownload@Modules@@QAE@XZ");
		// Modules::ModuleDownload *const this;

		AddCommand("DownloadHttp", "download_http", "", eCommandFlagsInternal, CommandDownloadHttp);
		VarDebugTrace = AddVariableInt("DebugTrace", "download_debug_trace", "", eCommandFlagsNone, 0);
		VarMaxHttpConnections = AddVariableInt("MaxHttpConnections", "download_max_http_connections", "Controls the maximum number of http connections per download", eCommandFlagsArchived, 6);
		VarMinHttpSegmentSize = AddVariableInt("MinHttpSegmentSize", "download_min_http_segment_size", "Controls the minimum size that a segment can be split", eCommandFlagsNone, 0x200000);
		VarMaxHttpSegmentRetry = AddVariableInt("MaxHttpSegmentRetry", "download_max_http_segment_retry", "Controls the maximum number of times a segment is retried before the download is aborted", eCommandFlagsNone, 5);
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0SCallbackEntry@?$CEventSink@$$V@@QAE@$$QAU01@@Z"); no body to assert in
// _inline CEventSink<>::SCallbackEntry::SCallbackEntry(CEventSink<>::SCallbackEntry &&__that) = default; // 0x10856850  // hades: implicit (SCallbackEntry is an aggregate)

/* ---------- private code */

bool CommandDownloadHttp(std::vector<std::string> const &args, std::string &retValue) // 0x10856F10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandDownloadHttp@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandDownloadHttp
	// static ...; // 0x10857144
	// static ...; // 0x1085712C
	// static ...; // 0x10857124
	// std::vector<std::string> const &args;
	// std::string &retValue;
	// std::shared_ptr<Download::CHttpFileDownload> download;
	// std::shared_ptr<`CommandDownloadHttp'::`2'::ScopedDebugTrace> debugTrace;
	// function call : void ()

	struct ScopedDebugTrace
	{
		__int32 m_oldValue;
		ScopedDebugTrace()
		{
			m_oldValue = Modules::ModuleDownload::Instance().VarDebugTrace->ValueInt;
			Modules::ModuleDownload::Instance().VarDebugTrace->ValueInt = 1;
		}
		~ScopedDebugTrace()
		{
			Modules::ModuleDownload::Instance().VarDebugTrace->ValueInt = m_oldValue;
		}
	};
	auto debugTrace = std::make_shared<ScopedDebugTrace>();
	if (args.size() < 2)
	{
		retValue = "USAGE: <URL> <DestinationFile>";
		return false;
	}
	std::shared_ptr<Download::CHttpFileDownload> download = Download::CreateHttpFileDownload();
	download->SetUrl(args[0]);
	download->SetDestinationFile(args[1]);
	download->SetReceiveBufferSize(0x4000);
	download->Completed.Subscribe([download, trace = std::move(debugTrace)]()
	{
		char buff[8192];
		sprintf_s(buff, "Download finished. Status: %s. Error: %s. Time Taken: %d (sec). Requests made: %d", Download::DownloadStatusToString(download->GetStatus()), Download::DownloadErrorToString(download->GetError()), download->GetElapsedSeconds(), download->GetTotalRequests());
		Console::WriteLine(buff);
	});
	download->Start();
	return true;
}
