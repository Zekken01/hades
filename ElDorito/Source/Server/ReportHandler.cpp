/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "Patches/Core.hpp"
#include "ThirdParty/HttpRequest.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "Utils/DewritoReader.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Utils/WebSocket.hpp"

#include "Utils/Logger.hpp"  // hades: added for 0x10B23680

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
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <functional>
#include <ios>
#include <iosfwd>
#include <limits>
#include <memory>
#include <mutex>
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

class HttpRequest;
struct begin;
struct end;
namespace hades_file_local
{
	struct ReportRequest;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace ReportHandler {}
	using namespace Server::ReportHandler;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Core {}
	using namespace Patches::Core;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct ReportRequest
	{
		long long CreationTime; // 0x0
		std::string Token; // 0x8
		// ReportRequest(ReportRequest &&);  // hades: implicit /* compiler_generated() */
		// ReportRequest(ReportRequest const &);  // hades: implicit /* compiler_generated() */
		// ReportRequest();  // hades: implicit /* compiler_generated() */
		// ~ReportRequest() = default;  // hades: implicit
		// ReportRequest &operator=(ReportRequest &&);  // hades: implicit /* compiler_generated() */  // hades: the PDB's `T &` is the move assignment (it moves the strings)
		// ReportRequest &operator=(ReportRequest const &);  // hades: implicit /* compiler_generated() */
	};
	static_assert(sizeof(ReportRequest) == 40, "Invalid ReportRequest size");

}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Utils::Version { std::string GetVersionString(); }  // hades: added for 0x10B22BE0

namespace Server
{
	namespace ReportHandler
	{
		extern void Handle(std::string const &token);
		extern void Tick();
		extern void Init();
	}
}

void GetEndpoints();
bool ForwardReportToEndpoint(std::string const &endpoint, std::string const &report);
void ForwardReportToEndpoints(std::string const &report);
bool HandleReport(std::string const &token);
void HandleReports();
unsigned long __stdcall HandledReportsThreadProc(void *lpParam);
static void OnShutdown();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern std::mutex mutex; // 0x12467960
	extern std::condition_variable signal; // 0x12467990
	extern std::vector<std::string> playerReportUrls; // 0x124679B8
	std::vector<ReportRequest> pending; // 0x124679C8
	extern bool shouldExit; // 0x124679D8
}
using namespace hades_file_local;
/* ---------- public code */

namespace Server
{
	namespace ReportHandler
	{
		void Handle(std::string const &token) // 0x10B22A80
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Handle@ReportHandler@Server@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10B22B8C
			// static ...; // 0x10B22B84
			// static ...; // 0x10B22B6C
			// static ...; // 0x10B22B64
			// std::string const &token;
				// std::lock_guard<std::mutex> guard;
				// ReportRequest request;

			{
				std::lock_guard<std::mutex> guard(hades_file_local::mutex);
				ReportRequest request;
				time(&request.CreationTime);
				request.Token = token;
				pending.emplace_back(request);
			}
			hades_file_local::signal.notify_one();
		}

		void Tick() // 0x10B23BF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@ReportHandler@Server@@YAXXZ");
			// procedure flags: nofpo
		}

		void Init() // 0x10B23B10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Init@ReportHandler@Server@@YAXXZ");
			// procedure flags: nofpo
			// function call : void *(_SECURITY_ATTRIBUTES *, unsigned long, unsigned long (*)(void *), void *, unsigned long, unsigned long *)

			Patches::Core::OnShutdown(::OnShutdown);
			CreateThread(nullptr, 0, HandledReportsThreadProc, nullptr, 0, nullptr);
		}
	}
}

/* ---------- private code */

void GetEndpoints() // 0x10B22890
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetEndpoints@@YAXXZ");
	// `anonymous-namespace'::GetEndpoints
	// procedure flags: nofpo
	// static ...; // 0x10B22A0C
	// static ...; // 0x10B22A00
	// static ...; // 0x10B229F8
	// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
		// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &urls;
			// unsigned __int32 i;

	if (!Utils::Singleton<Utils::DewritoReader>::Instance().IsValid())
		return;
	auto json = Utils::Singleton<Utils::DewritoReader>::Instance().GetDewritoJson();
	if (json.IsObject() && json.HasMember("playerReportUrls"))
	{
		playerReportUrls.clear();
		auto &urls = json["playerReportUrls"];
		for (rapidjson::SizeType i = 0; i < urls.Size(); i++)
			playerReportUrls.push_back(urls[i].GetString());
	}
}

bool ForwardReportToEndpoint(std::string const &endpoint, std::string const &report) // 0x10B21ED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ForwardReportToEndpoint@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
	// `anonymous-namespace'::ForwardReportToEndpoint
	// static ...; // 0x10B22604
	// static ...; // 0x10B225F9
	// static ...; // 0x10B225F4
	// static ...; // 0x10B225EC
	// static ...; // 0x10B225B0
	// static ...; // 0x10B225A8
// $LN43:
// $LN44:
	// std::string const &endpoint;
	// std::string const &report;
	// std::wstring expected;
	// HttpRequest req;
	// std::wstring statusCode;
	// std::string resp;
	// std::ofstream logfile;

	HttpRequest req(L"ElDewrito/" + Utils::String::WidenString(Utils::Version::GetVersionString()), L"", L"");
	try
	{
		if (!req.SendRequest(Utils::String::WidenString(endpoint), L"POST", L"", L"", L"", (void *)report.c_str(), report.size()))
		{
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "Server::ReportHandler::ForwardReportToEndpoint(): Unable to forward player report to \"%s\". LastError: %d", endpoint.c_str(), req.lastError);
			return false;
		}
	}
	catch (...)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "Server::ReportHandler::ForwardReportToEndpoint(): Exception while forwarding report player to \"%s\"", endpoint.c_str());
		return false;
	}
	std::wstring expected = L"HTTP/1.1 200 OK";
	if (req.responseHeader.length() < expected.length())
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "Server::ReportHandler::ForwardReportToEndpoint(): Invalid server query response from \"%s\". LastError %d", endpoint.c_str(), req.lastError);
		return false;
	}
	std::wstring statusCode = req.responseHeader.substr(0, expected.length());
	if (statusCode != expected)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "Server::ReportHandler::ForwardReportToEndpoint(): Server returned response status code: %d", statusCode);
		return false;
	}
	std::string resp = std::string(req.responseBody.begin(), req.responseBody.end());
	std::ofstream logfile("logs\\player_reports.log", std::ios::app);
	logfile << resp << "\n\n";
	logfile.flush();
	return true;
}

// mangled_x86(MANGLED_DEFAULT, "??0ReportRequest@hades_file_local@@QAE@AAU01@@Z"); no body to assert in
// _inline ReportRequest::ReportRequest(ReportRequest &&__that) = default; // 0x10B21560  // hades: implicit

// mangled_x86(MANGLED_DEFAULT, "??0ReportRequest@hades_file_local@@QAE@ABU01@@Z"); no body to assert in
// _inline ReportRequest::ReportRequest(ReportRequest const &__that) = default; // 0x10B215E0  // hades: implicit

// mangled_x86(MANGLED_DEFAULT, "??0ReportRequest@hades_file_local@@QAE@XZ"); no body to assert in
// _inline ReportRequest::ReportRequest() = default; // 0x10B21660  // hades: implicit


// _inline ReportRequest &ReportRequest::operator=(ReportRequest &&__that) = default; // 0x10B219D0  // hades: implicit

void ForwardReportToEndpoints(std::string const &report) // 0x10B227F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ForwardReportToEndpoints@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::ForwardReportToEndpoints
	// std::string const &report;
		// std::vector<std::string> &<range>$L0;
		// std::string *<begin>$L0;
		// std::string *<end>$L0;
			// std::string &endpoint;

	for (auto &url : playerReportUrls)
		ForwardReportToEndpoint(url, report);
}

bool HandleReport(std::string const &token) // 0x10B22BE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleReport@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::HandleReport
	// static ...; // 0x10B23459
	// static ...; // 0x10B23451
	// static ...; // 0x10B23448
	// static ...; // 0x10B2343D
	// static ...; // 0x10B23438
	// static ...; // 0x10B23430
	// static ...; // 0x10B233E8
	// static ...; // 0x10B233E0
// $LN39:
// $LN10:
	// std::string const &token;
	// std::wstring expected;
	// HttpRequest req;
	// std::wstring statusCode;
	// std::string resp;
	// std::ofstream logfile;
		// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> dewrito;

	HttpRequest req(L"ElDewrito/" + Utils::String::WidenString(Utils::Version::GetVersionString()), L"", L"");
	try
	{
		rapidjson::Document dewrito = Utils::Singleton<Utils::DewritoReader>::Instance().GetDewritoJson();
		if (!dewrito.HasMember("verifyReport"))
		{
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "Server::ReportHandler Missing verifyReport api URL from dewrito.json");
			return false;
		}
		if (!req.SendRequest(Utils::String::WidenString(dewrito["verifyReport"].GetString()) + L"?t=" + Utils::String::WidenString(token), L"GET", L"", L"", L"", NULL, 0))
		{
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "Server::ReportHandler Unable to connect to report verification endpoint. LastError: %d", req.lastError);
		}
	}
	catch (...)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "Server::ReportHandler Exception while verifying player report token");
		return false;
	}
	std::wstring expected = L"HTTP/1.1 200 OK";
	if (req.responseHeader.length() < expected.length())
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "Server::ReportHandler: Invalid server query response. LastError %d", req.lastError);
		return false;
	}
	std::wstring statusCode = req.responseHeader.substr(0, expected.length());
	if (statusCode != expected)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "Server::ReportHandler: Server returned response status code: %s", statusCode.c_str());
		return false;
	}
	std::string resp = std::string(req.responseBody.begin(), req.responseBody.end());
	std::ofstream logfile("logs\\player_reports.log", std::ios::app);
	logfile << resp << "\n\n";
	logfile.flush();
	ForwardReportToEndpoints(resp);
	return true;
}

void HandleReports() // 0x10B23680
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleReports@@YAXXZ");
	// `anonymous-namespace'::HandleReports
	// procedure flags: nofpo
	// static ...; // 0x10B238F4
	// static ...; // 0x10B238E8
	// static ...; // 0x10B238E0
		// std::_Vector_iterator<std::_Vector_val<std::_Simple_types<ReportRequest> > > it;
			// long long deltaTime;
			// ReportRequest &request;

	if (pending.size() == 0)
		return;
	GetEndpoints();
	for (auto it = pending.begin(); it != pending.end();)
	{
		auto &request = *it;
		long long deltaTime = time(nullptr) - request.CreationTime;
		if (HandleReport(request.Token))
			it = pending.erase(it);
		else if (deltaTime > 60)
		{
			it = pending.erase(it);
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "Server::ReportHandler: Failed to handle report after %d seconds", 60);
		}
		else
			it++;
	}
}

unsigned long __stdcall HandledReportsThreadProc(void *lpParam) // 0x10B239A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandledReportsThreadProc@@YGKPAX@Z");
	// `anonymous-namespace'::HandledReportsThreadProc
	// static ...; // 0x10B23AC4
	// static ...; // 0x10B23AC0
	// static ...; // 0x10B23AA8
	// static ...; // 0x10B23AA0
	// void *lpParam;
		// std::unique_lock<std::mutex> lk;
		// std::chrono::time_point<std::chrono::system_clock,std::chrono::duration<__int64,std::ratio<1,10000000> > > now;

	for (;;)
	{
		std::unique_lock<std::mutex> lk(hades_file_local::mutex);
		auto now = std::chrono::system_clock::now();
		hades_file_local::signal.wait_for(lk, std::chrono::seconds(5));
		if (shouldExit)
			return 0;
		HandleReports();
	}
	return 0;
}

static void OnShutdown() // 0x10B23BA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnShutdown@@YAXXZ");
	// `anonymous-namespace'::OnShutdown
	// procedure flags: nofpo

	shouldExit = true;
	hades_file_local::signal.notify_one();
}

/* ---------- explicit instantiations */
template class std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<ReportRequest> > >;
template class std::_Vector_iterator<std::_Vector_val<std::_Simple_types<ReportRequest> > >;
template std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<ReportRequest> > >::~_Vector_const_iterator();
template std::_Vector_iterator<std::_Vector_val<std::_Simple_types<ReportRequest> > >::~_Vector_iterator();
