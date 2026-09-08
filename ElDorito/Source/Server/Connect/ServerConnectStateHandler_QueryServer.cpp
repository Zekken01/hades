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

EQueryModsResult QueryModsBlocking(SQueryInfoServerArgs const &args, std::vector<SServerConnectState::SRequiredMod> *outPackages);
EQueryInfoServerResult QueryInfoServerBlocking(SQueryInfoServerArgs const &args, SQueryInfoServerData *result);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_10B12D20(CServerConnectStateHandler_QueryServer *const);
void CServerConnectStateHandler_QueryServer::OnEnter() // 0x10B12D20
{
	mangled_x86(MANGLED_TODO, "?OnEnter@CServerConnectStateHandler_QueryServer@@EAEXXZ");
	// static ...; // 0x10B12F68
	// static ...; // 0x10B12F5C
	// static ...; // 0x10B12F54
	// CServerConnectStateHandler_QueryServer *const this;
	// SQueryInfoServerArgs args;
	// SServerConnectState const &state;
	todo("implement");
	_sub_10B12D20(this);
}

void CServerConnectStateHandler_QueryServer::OnExit() // 0x10B13000
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnExit@CServerConnectStateHandler_QueryServer@@EAEXXZ");
	// CServerConnectStateHandler_QueryServer *const this;
}

_extern void _sub_10B13020(CServerConnectStateHandler_QueryServer *const);
void CServerConnectStateHandler_QueryServer::OnUpdate() // 0x10B13020
{
	mangled_x86(MANGLED_TODO, "?OnUpdate@CServerConnectStateHandler_QueryServer@@EAEXXZ");
	// static ...; // 0x10B132C4
	// static ...; // 0x10B132B8
	// static ...; // 0x10B132B0
	// CServerConnectStateHandler_QueryServer *const this;
	{
		// std::unique_lock<std::mutex> lock;
		// SServerConnectState &state;
	}
	todo("implement");
	_sub_10B13020(this);
}

_inline SQueryInfoServerArgs::SQueryInfoServerArgs(SQueryInfoServerArgs &&__that) // 0x10B11D10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SQueryInfoServerArgs@@QAE@$$QAU0@@Z");
	// SQueryInfoServerArgs &__that;

	compiler_generated();
}

_inline SQueryInfoServerArgs::SQueryInfoServerArgs(SQueryInfoServerArgs const &__that) // 0x10B11DB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SQueryInfoServerArgs@@QAE@ABU0@@Z");
	// SQueryInfoServerArgs const &__that;

	compiler_generated();
}

_inline SQueryInfoServerArgs::SQueryInfoServerArgs() // 0x10B11E90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SQueryInfoServerArgs@@QAE@XZ");
	// SQueryInfoServerArgs *const this;

	compiler_generated();
}

_inline SServerConnectState::SRequiredMod::SRequiredMod(SServerConnectState::SRequiredMod &&__that) // 0x10B11EF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SRequiredMod@SServerConnectState@@QAE@$$QAU01@@Z");
	// SServerConnectState::SRequiredMod &__that;

	compiler_generated();
}

_inline SServerConnectState::SRequiredMod::SRequiredMod(SServerConnectState::SRequiredMod const &__that) // 0x10B120D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SRequiredMod@SServerConnectState@@QAE@ABU01@@Z");
	// SServerConnectState::SRequiredMod const &__that;

	compiler_generated();
}

_inline SServerConnectState::SRequiredMod::SRequiredMod() // 0x10B12310
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SRequiredMod@SServerConnectState@@QAE@XZ");
	// SServerConnectState::SRequiredMod *const this;

	compiler_generated();
}

_inline SQueryInfoServerArgs::~SQueryInfoServerArgs() // 0x10B12630
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1SQueryInfoServerArgs@@QAE@XZ");
	// SQueryInfoServerArgs *const this;

	compiler_generated();
}

extern SQueryInfoServerData &_sub_10B128D0(SQueryInfoServerData *const, SQueryInfoServerData &);
_inline SQueryInfoServerData &SQueryInfoServerData::operator=(SQueryInfoServerData &&__that) // 0x10B128D0
{
	mangled_x86(MANGLED_TODO, "??4SQueryInfoServerData@@QAEAAU0@$$QAU0@@Z");
	// SQueryInfoServerData &__that;
	{
		// unsigned __int32 $S1;
	}
	{
		// unsigned __int32 $S2;
	}
	compiler_generated();
	todo("implement");
	SQueryInfoServerData & __result = _sub_10B128D0(this, __that);
	return __result;
}

extern EJobResult _sub_10B14990(CServerConnectStateHandler_QueryServer *const, SQueryInfoServerArgs const &);
EJobResult CServerConnectStateHandler_QueryServer::QueryInfoServerJobCallback(SQueryInfoServerArgs const &args) // 0x10B14990
{
	mangled_x86(MANGLED_TODO, "?QueryInfoServerJobCallback@CServerConnectStateHandler_QueryServer@@AAE?AW4EJobResult@@ABUSQueryInfoServerArgs@@@Z");
	// static ...; // 0x10B14AC8
	// static ...; // 0x10B14AB0
	// static ...; // 0x10B14AA8
	// CServerConnectStateHandler_QueryServer *const this;
	// SQueryInfoServerArgs const &args;
	// std::scoped_lock<std::mutex> lock;
	// SQueryInfoServerData data;
	// EQueryInfoServerResult result;
	todo("implement");
	EJobResult __result = _sub_10B14990(this, args);
	return __result;
}

extern EJobResult _sub_10B15DD0(CServerConnectStateHandler_QueryServer *const, std::string const &);
EJobResult CServerConnectStateHandler_QueryServer::ResolveAddressJobCallback(std::string const &hostname) // 0x10B15DD0
{
	mangled_x86(MANGLED_TODO, "?ResolveAddressJobCallback@CServerConnectStateHandler_QueryServer@@AAE?AW4EJobResult@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// static ...; // 0x10B15E90
	// static ...; // 0x10B15E78
	// static ...; // 0x10B15E70
	// CServerConnectStateHandler_QueryServer *const this;
	// std::string const &hostname;
	// std::scoped_lock<std::mutex> lock;
	// Utils::Network::EResolveAddressResult result;
	// unsigned __int32 address;
	todo("implement");
	EJobResult __result = _sub_10B15DD0(this, hostname);
	return __result;
}

extern EJobResult _sub_10B15C50(CServerConnectStateHandler_QueryServer *const, SQueryInfoServerArgs const &);
EJobResult CServerConnectStateHandler_QueryServer::QueryModsJobCallback(SQueryInfoServerArgs const &args) // 0x10B15C50
{
	mangled_x86(MANGLED_TODO, "?QueryModsJobCallback@CServerConnectStateHandler_QueryServer@@AAE?AW4EJobResult@@ABUSQueryInfoServerArgs@@@Z");
	// static ...; // 0x10B15D68
	// static ...; // 0x10B15D50
	// static ...; // 0x10B15D48
	// CServerConnectStateHandler_QueryServer *const this;
	// SQueryInfoServerArgs const &args;
	// std::scoped_lock<std::mutex> lock;
	// std::vector<SServerConnectState::SRequiredMod> requiredMods;
	// EQueryModsResult result;
	todo("implement");
	EJobResult __result = _sub_10B15C50(this, args);
	return __result;
}

/* ---------- private code */

extern EQueryModsResult _sub_10B14B30(SQueryInfoServerArgs const &, std::vector<SServerConnectState::SRequiredMod> *);
EQueryModsResult QueryModsBlocking(SQueryInfoServerArgs const &args, std::vector<SServerConnectState::SRequiredMod> *outPackages) // 0x10B14B30
{
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
	{
		// rapidjson::GenericMemberIterator<0,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > it;
		{
			// SServerConnectState::SRequiredMod description;
			// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &mod;
		}
	}
	todo("implement");
	EQueryModsResult __result = _sub_10B14B30(args, outPackages);
	return __result;
}

extern EQueryInfoServerResult _sub_10B13380(SQueryInfoServerArgs const &, SQueryInfoServerData *);
EQueryInfoServerResult QueryInfoServerBlocking(SQueryInfoServerArgs const &args, SQueryInfoServerData *result) // 0x10B13380
{
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
	todo("implement");
	EQueryInfoServerResult __result = _sub_10B13380(args, result);
	return __result;
}
