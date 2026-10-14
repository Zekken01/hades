/* ---------- headers */

#include "Server/Connect/ServerConnectStateHandler_QueryServer.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "Console/Console.hpp"
#include "Job/JobDefinitions.hpp"
#include "Server/Connect/ServerConnectDefintiions.hpp"
#include "Server/Connect/ServerConnectStateManager.hpp"
#include "ThirdParty/HttpRequest.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/encodings.h"
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
#include "Utils/NetworkUtil.hpp"
#include "Utils/String.hpp"
#include "Utils/WebSocket.hpp"

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
#include <variant>
#include <vector>

/* ---------- forward declarations */

class CServerConnectStateHandler_QueryServer;
class HttpRequest;
struct SQueryInfoServerArgs;
struct SQueryInfoServerData;
struct SServerConnectState;
struct lambda_1;
struct lambda_2;
struct lambda_3;

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace Network {}
	using namespace Utils::Network;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Console {}
using namespace ::Console;

/* ---------- constants */

namespace hades_file_local
{
	enum class EQueryModsResult
	{
		Success = 0,
		RequestError,
		BadStatusCode,
		InvalidJson,
	};

	enum class EQueryInfoServerResult
	{
		Success = 0,
		RequestError,
		BadStatusCode,
		InvalidJson,
		IncorrectPassword,
		XNetInfoInvalid,
		IncompatibleVersion,
	};
}
using namespace hades_file_local;
/* ---------- definitions */

//class CServerConnectStateHandler_QueryServer::OnEnter::__l2::<lambda_1>
//{
//public:
//	EJobResult operator()() const;
//	<lambda_1>(CServerConnectStateHandler_QueryServer::OnEnter::__l2::<lambda_1> &);
//	<lambda_1>(CServerConnectStateHandler_QueryServer::OnEnter::__l2::<lambda_1> const &);
//	<lambda_1>(CServerConnectStateHandler_QueryServer *, SQueryInfoServerArgs const &);
//private:
//	CServerConnectStateHandler_QueryServer *__this; // 0x0
//	SQueryInfoServerArgs args; // 0x4
//public:
//	CServerConnectStateHandler_QueryServer::OnEnter::__l2::<lambda_1> &operator=(CServerConnectStateHandler_QueryServer::OnEnter::__l2::<lambda_1> const &);
//	~<lambda_1>(); /* compiler_generated() */
//};
//static_assert(sizeof(CServerConnectStateHandler_QueryServer::OnEnter::__l2::<lambda_1>) == 64, "Invalid CServerConnectStateHandler_QueryServer::OnEnter::__l2::<lambda_1> size");

//class CServerConnectStateHandler_QueryServer::OnEnter::__l2::<lambda_2>
//{
//public:
//	EJobResult operator()() const;
//	<lambda_2>(CServerConnectStateHandler_QueryServer::OnEnter::__l2::<lambda_2> &);
//	<lambda_2>(CServerConnectStateHandler_QueryServer::OnEnter::__l2::<lambda_2> const &);
//	<lambda_2>(CServerConnectStateHandler_QueryServer *, SQueryInfoServerArgs const &);
//private:
//	CServerConnectStateHandler_QueryServer *__this; // 0x0
//	SQueryInfoServerArgs args; // 0x4
//public:
//	CServerConnectStateHandler_QueryServer::OnEnter::__l2::<lambda_2> &operator=(CServerConnectStateHandler_QueryServer::OnEnter::__l2::<lambda_2> const &);
//	~<lambda_2>(); /* compiler_generated() */
//};
//static_assert(sizeof(CServerConnectStateHandler_QueryServer::OnEnter::__l2::<lambda_2>) == 64, "Invalid CServerConnectStateHandler_QueryServer::OnEnter::__l2::<lambda_2> size");

//class CServerConnectStateHandler_QueryServer::OnEnter::__l2::<lambda_3>
//{
//public:
//	EJobResult operator()() const;
//	<lambda_3>(CServerConnectStateHandler_QueryServer::OnEnter::__l2::<lambda_3> &);
//	<lambda_3>(CServerConnectStateHandler_QueryServer::OnEnter::__l2::<lambda_3> const &);
//	<lambda_3>(CServerConnectStateHandler_QueryServer *, SQueryInfoServerArgs const &);
//private:
//	CServerConnectStateHandler_QueryServer *__this; // 0x0
//	SQueryInfoServerArgs args; // 0x4
//public:
//	CServerConnectStateHandler_QueryServer::OnEnter::__l2::<lambda_3> &operator=(CServerConnectStateHandler_QueryServer::OnEnter::__l2::<lambda_3> const &);
//	~<lambda_3>(); /* compiler_generated() */
//};
//static_assert(sizeof(CServerConnectStateHandler_QueryServer::OnEnter::__l2::<lambda_3>) == 64, "Invalid CServerConnectStateHandler_QueryServer::OnEnter::__l2::<lambda_3> size");

/* ---------- prototypes */

namespace Job { extern void RunJob(std::function<EJobResult __cdecl(void)> function, SJobCounter *counter, __int32 priority); }  // hades: added for 0x10B12D20

EQueryModsResult QueryModsBlocking(SQueryInfoServerArgs const &args, std::vector<SServerConnectState::SRequiredMod> *outPackages);
namespace Utils::Version { std::string GetVersionString(); bool IsVersionCompatible(std::string const &version); }  // hades: added for 0x10B14B30, 0x10B13380
EQueryInfoServerResult QueryInfoServerBlocking(SQueryInfoServerArgs const &args, SQueryInfoServerData *result);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

void CServerConnectStateHandler_QueryServer::OnEnter() // 0x10B12D20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnEnter@CServerConnectStateHandler_QueryServer@@EAEXXZ");
	// static ...; // 0x10B12F68
	// static ...; // 0x10B12F5C
	// static ...; // 0x10B12F54
	// CServerConnectStateHandler_QueryServer *const this;
	// SQueryInfoServerArgs args;
	// SServerConnectState const &state;

	Console::WriteLine("Server Connect :: Querying info server...");
	SServerConnectState const &state = GetManager()->GetState();
	m_addressLookupAddress = 0;
	m_addressLookupResult = 0;
	m_queryInfoServerResult = 0;
	m_queryModsResult = 0;
	m_requiredMods.clear();
	SQueryInfoServerArgs args;
	args.port = state.port;
	args.hostname = state.hostname;
	args.password = state.password;
	Job::RunJob([this, args]() { return ResolveAddressJobCallback(args.hostname); }, &m_jobCounter, 0);
	Job::RunJob([this, args]() { return QueryInfoServerJobCallback(args); }, &m_jobCounter, 0);
	Job::RunJob([this, args]() { return QueryModsJobCallback(args); }, &m_jobCounter, 0);
}

void CServerConnectStateHandler_QueryServer::OnExit() // 0x10B13000
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnExit@CServerConnectStateHandler_QueryServer@@EAEXXZ");
	// CServerConnectStateHandler_QueryServer *const this;
}

void CServerConnectStateHandler_QueryServer::OnUpdate() // 0x10B13020
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnUpdate@CServerConnectStateHandler_QueryServer@@EAEXXZ");
	// static ...; // 0x10B132C4
	// static ...; // 0x10B132B8
	// static ...; // 0x10B132B0
	// CServerConnectStateHandler_QueryServer *const this;
		// std::unique_lock<std::mutex> lock;
		// SServerConnectState &state;

	if (m_jobCounter.GetValue() == 0)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		if (m_addressLookupResult)
		{
			Abort((EServerConnectAbortReason)3);
			return;
		}
		if (m_queryInfoServerResult)
		{
			switch (m_queryInfoServerResult)
			{
			case 4:
				Abort((EServerConnectAbortReason)1);
				return;
			case 6:
				Abort((EServerConnectAbortReason)2);
				return;
			default:
				Abort(InfoServerQueryFailed);
				return;
			}
		}
		if (m_queryModsResult)
		{
			switch (m_queryModsResult)
			{
			case 3:
				Abort(InvalidModListJson);
				return;
			default:
				Abort(ModsQueryFailed);
				return;
			}
		}
		SServerConnectState &state = GetManager()->GetStateMutable();
		state.address = m_addressLookupAddress;
		state.gamePort = m_infoServerData.gamePort;
		state.fileServerPort = m_infoServerData.fileServerPort;
		state.serverName = m_infoServerData.serverName;
		state.serverHost = m_infoServerData.serverHost;
		state.requiredMods = std::move(m_requiredMods);
		m_requiredMods.clear();
		memcpy(state.xnaddr, m_infoServerData.xnaddr, sizeof(state.xnaddr));
		memcpy(state.xnkid, m_infoServerData.xnkid, sizeof(state.xnkid));
		RequestStateChange(AcquireMods);
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0SQueryInfoServerArgs@@QAE@$$QAU0@@Z"); no body to assert in
_inline SQueryInfoServerArgs::SQueryInfoServerArgs(SQueryInfoServerArgs &&__that) = default; // 0x10B11D10

// mangled_x86(MANGLED_DEFAULT, "??0SQueryInfoServerArgs@@QAE@ABU0@@Z"); no body to assert in
_inline SQueryInfoServerArgs::SQueryInfoServerArgs(SQueryInfoServerArgs const &__that) = default; // 0x10B11DB0

// mangled_x86(MANGLED_DEFAULT, "??0SQueryInfoServerArgs@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0SRequiredMod@SServerConnectState@@QAE@$$QAU01@@Z"); no body to assert in
_inline SServerConnectState::SRequiredMod::SRequiredMod(SServerConnectState::SRequiredMod &&__that) = default; // 0x10B11EF0

// mangled_x86(MANGLED_DEFAULT, "??0SRequiredMod@SServerConnectState@@QAE@ABU01@@Z"); no body to assert in
_inline SServerConnectState::SRequiredMod::SRequiredMod(SServerConnectState::SRequiredMod const &__that) = default; // 0x10B120D0

// mangled_x86(MANGLED_DEFAULT, "??0SRequiredMod@SServerConnectState@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??1SQueryInfoServerArgs@@QAE@XZ"); no body to assert in
_inline SQueryInfoServerArgs::~SQueryInfoServerArgs() = default; // 0x10B12630

// mangled_x86(MANGLED_DEFAULT, "??4SQueryInfoServerData@@QAEAAU0@$$QAU0@@Z"); no body to assert in
_inline SQueryInfoServerData &SQueryInfoServerData::operator=(SQueryInfoServerData &&__that) noexcept = default; // 0x10B128D0

EJobResult CServerConnectStateHandler_QueryServer::QueryInfoServerJobCallback(SQueryInfoServerArgs const &args) // 0x10B14990
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?QueryInfoServerJobCallback@CServerConnectStateHandler_QueryServer@@AAE?AW4EJobResult@@ABUSQueryInfoServerArgs@@@Z");
	// static ...; // 0x10B14AC8
	// static ...; // 0x10B14AB0
	// static ...; // 0x10B14AA8
	// CServerConnectStateHandler_QueryServer *const this;
	// SQueryInfoServerArgs const &args;
	// std::scoped_lock<std::mutex> lock;
	// SQueryInfoServerData data;
	// EQueryInfoServerResult result;

	SQueryInfoServerData data;
	EQueryInfoServerResult result = QueryInfoServerBlocking(args, &data);
	std::scoped_lock<std::mutex> lock(m_mutex);
	m_infoServerData = std::move(data);
	m_queryInfoServerResult = (__int32)result;
	return Done;
}

EJobResult CServerConnectStateHandler_QueryServer::ResolveAddressJobCallback(std::string const &hostname) // 0x10B15DD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ResolveAddressJobCallback@CServerConnectStateHandler_QueryServer@@AAE?AW4EJobResult@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// static ...; // 0x10B15E90
	// static ...; // 0x10B15E78
	// static ...; // 0x10B15E70
	// CServerConnectStateHandler_QueryServer *const this;
	// std::string const &hostname;
	// std::scoped_lock<std::mutex> lock;
	// Utils::Network::EResolveAddressResult result;
	// unsigned __int32 address;

	unsigned __int32 address;
	Utils::Network::EResolveAddressResult result = Utils::Network::ResolveAddress(hostname, &address);
	std::scoped_lock<std::mutex> lock(m_mutex);
	m_addressLookupResult = result;
	if (result == Utils::Network::Success)
		m_addressLookupAddress = address;
	return Done;
}

EJobResult CServerConnectStateHandler_QueryServer::QueryModsJobCallback(SQueryInfoServerArgs const &args) // 0x10B15C50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?QueryModsJobCallback@CServerConnectStateHandler_QueryServer@@AAE?AW4EJobResult@@ABUSQueryInfoServerArgs@@@Z");
	// static ...; // 0x10B15D68
	// static ...; // 0x10B15D50
	// static ...; // 0x10B15D48
	// CServerConnectStateHandler_QueryServer *const this;
	// SQueryInfoServerArgs const &args;
	// std::scoped_lock<std::mutex> lock;
	// std::vector<SServerConnectState::SRequiredMod> requiredMods;
	// EQueryModsResult result;

	std::vector<SServerConnectState::SRequiredMod> requiredMods;
	EQueryModsResult result = QueryModsBlocking(args, &requiredMods);
	std::scoped_lock<std::mutex> lock(m_mutex);
	m_requiredMods = std::move(requiredMods);
	m_queryModsResult = (__int32)result;
	requiredMods.clear();
	return Done;
}

/* ---------- private code */

EQueryModsResult QueryModsBlocking(SQueryInfoServerArgs const &args, std::vector<SServerConnectState::SRequiredMod> *outPackages) // 0x10B14B30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?QueryModsBlocking@@YA?AW4EQueryModsResult@hades_file_local@@ABUSQueryInfoServerArgs@@PAV?$vector@USRequiredMod@SServerConnectState@@V?$allocator@USRequiredMod@SServerConnectState@@@std@@@std@@@Z");
	// `anonymous-namespace'::QueryModsBlocking
	// static ...; // 0x10B158CD
	// static ...; // 0x10B158C2
	// static ...; // 0x10B158B9
	// static ...; // 0x10B158B1
	// static ...; // 0x10B158AC
	// static ...; // 0x10B158A7
	// static ...; // 0x10B158A4
	// static ...; // 0x10B15898
	// static ...; // 0x10B1582C
	// static ...; // 0x10B15824
	// SQueryInfoServerArgs const &args;
	// std::vector<SServerConnectState::SRequiredMod> *outPackages;
	// std::wstring respHdr;
	// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
	// std::wstring expected;
	// HttpRequest req;
	// std::string endpoint;
	// std::string resp;
	// std::string authString;
		// rapidjson::GenericMemberIterator<0,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > it;
			// SServerConnectState::SRequiredMod description;
			// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &mod;

	HttpRequest req(L"ElDewrito/" + Utils::String::WidenString(Utils::Version::GetVersionString()), L"", L"");
	std::string endpoint = "http://" + std::string(args.hostname) + ":" + std::to_string(args.port) + "/mods";
	std::string authString = "dorito:" + args.password;
	authString = "Authorization: Basic " + Utils::String::Base64Encode((unsigned char const *)authString.c_str(), authString.length()) + "\r\n";
	if (!req.SendRequest(Utils::String::WidenString(endpoint), L"GET", L"", L"", Utils::String::WidenString(authString), nullptr, 0))
		return (EQueryModsResult)1;
	std::wstring expected = L"HTTP/1.1 200 OK";
	if (req.responseHeader.length() < expected.length())
		return (EQueryModsResult)2;
	std::wstring respHdr = req.responseHeader.substr(0, expected.length());
	if (respHdr.compare(expected) != 0)
		return (EQueryModsResult)2;
	std::string resp(req.responseBody.begin(), req.responseBody.end());
	rapidjson::Document json;
	if (json.Parse<0>(resp.c_str()).HasParseError() || !json.IsObject())
		return (EQueryModsResult)3;
	for (auto it = json.MemberBegin(); it != json.MemberEnd(); ++it)
	{
		rapidjson::Value &mod = it->value;
		if (!mod.IsObject() || !mod.HasMember("hash") || !mod.HasMember("package_url") || !mod.HasMember("package_size"))
			return (EQueryModsResult)3;
		SServerConnectState::SRequiredMod description;
		description.localName = std::string(it->name.GetString());
		description.hash = std::string(mod["hash"].GetString());
		description.packageUrl = std::string(mod["package_url"].GetString());
		if (description.packageUrl.length() < 2)
			continue;
		description.fileSize = mod["package_size"].GetUint64();
		if (mod.HasMember("mod_author"))
			description.author = std::string(mod["mod_author"].GetString());
		if (mod.HasMember("mod_description"))
			description.description = std::string(mod["mod_description"].GetString());
		if (mod.HasMember("mod_version"))
			description.version = std::string(mod["mod_version"].GetString());
		if (mod.HasMember("mod_website"))
			description.website = std::string(mod["mod_website"].GetString());
		if (mod.HasMember("mod_name"))
			description.name = std::string(mod["mod_name"].GetString());
		else
			description.name = it->name.GetString();
		outPackages->push_back(description);
	}
	return (EQueryModsResult)0;
}

EQueryInfoServerResult QueryInfoServerBlocking(SQueryInfoServerArgs const &args, SQueryInfoServerData *result) // 0x10B13380
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?QueryInfoServerBlocking@@YA?AW4EQueryInfoServerResult@hades_file_local@@ABUSQueryInfoServerArgs@@PAUSQueryInfoServerData@@@Z");
	// `anonymous-namespace'::QueryInfoServerBlocking
	// static ...; // 0x10B14517
	// static ...; // 0x10B1450B
	// static ...; // 0x10B14502
	// static ...; // 0x10B144FA
	// static ...; // 0x10B144F5
	// static ...; // 0x10B144F0
	// static ...; // 0x10B144E8
	// static ...; // 0x10B144E2
	// static ...; // 0x10B144D9
	// static ...; // 0x10B144CD
	// static ...; // 0x10B144C7
	// static ...; // 0x10B144C0
	// static ...; // 0x10B14424
	// static ...; // 0x10B1441C
	// SQueryInfoServerArgs const &args;
	// SQueryInfoServerData *result;
	// std::string xnkid;
	// std::wstring respHdr;
	// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
	// std::string gameVer;
	// std::wstring usernameStr;
	// std::string ourEdVer;
	// std::wstring passwordStr;
	// std::wstring expected;
	// HttpRequest req;
	// std::string xnaddr;
	// std::string resp;
	// std::string edVer;
	// std::string gameVersion;
	// function call : unsigned long ()

	HttpRequest req(L"ElDewrito/" + Utils::String::WidenString(Utils::Version::GetVersionString()), L"", L"");
	std::wstring usernameStr = L"";
	std::wstring passwordStr = L"";
	if (args.password.length() != 0)
	{
		usernameStr = L"dorito";
		passwordStr = Utils::String::WidenString(args.password);
	}
	if (!req.SendRequest(Utils::String::WidenString("http://" + args.hostname + ":" + std::to_string(args.port) + "/"), L"GET", usernameStr, passwordStr, L"", nullptr, 0))
	{
		result->message = "Unable to connect to server. (error: " + std::to_string(req.lastError) + "/" + std::to_string(GetLastError()) + ")";
		return (EQueryInfoServerResult)1;
	}
	std::wstring expected = L"HTTP/1.1 200 OK";
	if (req.responseHeader.length() < expected.length())
	{
		result->message = "Invalid server query response.";
		return (EQueryInfoServerResult)2;
	}
	std::wstring respHdr = req.responseHeader.substr(0, expected.length());
	if (respHdr.compare(expected) != 0)
	{
		result->message = "Invalid server query header response.";
		return (EQueryInfoServerResult)2;
	}
	std::string resp(req.responseBody.begin(), req.responseBody.end());
	rapidjson::Document json;
	if (json.Parse<0>(resp.c_str()).HasParseError() || !json.IsObject())
	{
		result->message = "Invalid server query JSON response.";
		return (EQueryInfoServerResult)3;
	}
	if (!json.HasMember("gameVersion") || !json["gameVersion"].IsString() || !json.HasMember("eldewritoVersion") || !json["eldewritoVersion"].IsString() || !json.HasMember("port") || !json["port"].IsNumber())
	{
		result->message = "Server query JSON response is missing data.";
		return (EQueryInfoServerResult)3;
	}
	if (json.HasMember("name") && json.HasMember("hostPlayer"))
	{
		result->serverName = json["name"].GetString();
		result->serverHost = json["hostPlayer"].GetString();
	}
	result->fileServerPort = 0;
	if (json.HasMember("fileServerPort") && json["fileServerPort"].IsInt())
		result->fileServerPort = json["fileServerPort"].GetInt();
	if (!json.HasMember("xnkid") || !json["xnkid"].IsString() || !json.HasMember("xnaddr") || !json["xnaddr"].IsString())
	{
		result->message = "Incorrect password specified.";
		return (EQueryInfoServerResult)4;
	}
	std::string gameVer = json["gameVersion"].GetString();
	std::string edVer = json["eldewritoVersion"].GetString();
	std::string ourEdVer = Utils::Version::GetVersionString();
	std::string gameVersion((char const *)0x199C0F0);
	if (gameVersion.compare(gameVer) != 0)
	{
		result->message = "Server is running a different game version.";
		return (EQueryInfoServerResult)6;
	}
	if (!Utils::Version::IsVersionCompatible(edVer))
	{
		result->message = "Server is running a different ElDewrito version.";
		return (EQueryInfoServerResult)6;
	}
	std::string xnkid = json["xnkid"].GetString();
	std::string xnaddr = json["xnaddr"].GetString();
	if (xnkid.length() != 32 || xnaddr.length() != 32)
	{
		result->message = "Server query XNet info is invalid.";
		return (EQueryInfoServerResult)5;
	}
	result->gamePort = json["port"].GetInt();
	Utils::String::HexStringToBytes(xnkid, result->xnkid, 16);
	Utils::String::HexStringToBytes(xnaddr, result->xnaddr, 16);
	return (EQueryInfoServerResult)0;
}
