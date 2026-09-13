/* ---------- headers */

#include "Server/Connect/ServerConnect.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Console/Console.hpp"
#include "Download/IDownload.hpp"
#include "Forge/Magnets.hpp"
#include "Job/JobDefinitions.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Patches/CustomPackets.hpp"
#include "Server/Connect/ServerConnectDefintiions.hpp"
#include "Server/Connect/ServerConnectStateHandler.hpp"
#include "Server/Connect/ServerConnectStateHandler_AcquireMods.hpp"
#include "Server/Connect/ServerConnectStateHandler_Connect.hpp"
#include "Server/Connect/ServerConnectStateHandler_QueryServer.hpp"
#include "Server/Connect/ServerConnectStateManager.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "Utils/EventSink.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/Ui/ScreenLayer.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <limits>
#include <list>
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
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

/* ---------- forward declarations */

class CServerConnectStateHandler_AcquireMods;
class CServerConnectStateHandler_Connect;
class CServerConnectStateHandler_QueryServer;
class CServerConnectStateManager;
struct CServerConnectManager;
struct SQueryInfoServerData;
struct SServerConnectOptions;
struct SServerConnectState;
struct lambda_1;
namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer
		{
			struct SDialogShowParams;
		}
	}
}

namespace Utils {}
using namespace ::Utils;
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
		namespace WebMods {}
		using namespace Web::Ui::WebMods;
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

namespace Download {}
using namespace ::Download;
namespace Console {}
using namespace ::Console;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

//class CServerConnectManager::Initialize::__l2::<lambda_1>
//{
//public:
//	void operator()(EServerConnectAbortReason) const;
//	<lambda_1>(CServerConnectManager::Initialize::__l2::<lambda_1> &);
//	<lambda_1>(CServerConnectManager *);
//private:
//	CServerConnectManager *__this; // 0x0
//public:
//	CServerConnectManager::Initialize::__l2::<lambda_1> &operator=(CServerConnectManager::Initialize::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(CServerConnectManager::Initialize::__l2::<lambda_1>) == 4, "Invalid CServerConnectManager::Initialize::__l2::<lambda_1> size");

//class CServerConnectManager::OnConnectionAborted::__l2::<lambda_1>
//{
//public:
//	void operator()(std::string const &) const;
//	<lambda_1>(CServerConnectManager::OnConnectionAborted::__l2::<lambda_1> &);
//	<lambda_1>(CServerConnectManager *);
//private:
//	CServerConnectManager *__this; // 0x0
//public:
//	CServerConnectManager::OnConnectionAborted::__l2::<lambda_1> &operator=(CServerConnectManager::OnConnectionAborted::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(CServerConnectManager::OnConnectionAborted::__l2::<lambda_1>) == 4, "Invalid CServerConnectManager::OnConnectionAborted::__l2::<lambda_1> size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_10B079E0(CServerConnectManager *const);
void CServerConnectManager::Initialize() // 0x10B079E0
{
	mangled_x86(MANGLED_TODO, "?Initialize@CServerConnectManager@@QAEXXZ");
	// static ...; // 0x10B07CB0
	// static ...; // 0x10B07CA4
	// static ...; // 0x10B07C9C
	// CServerConnectManager *const this;
	// std::shared_ptr<CServerConnectStateHandler_AcquireMods> acquireModsHandler;
	todo("implement");
	_sub_10B079E0(this);
}

void CServerConnectManager::Update() // 0x10B08170
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Update@CServerConnectManager@@QAEXXZ");
	// CServerConnectManager *const this;

	m_stateManager->Update();
}

_extern bool _sub_10B07780(CServerConnectManager *const, SServerConnectOptions const &);
bool CServerConnectManager::ConnectToServer(SServerConnectOptions const &options) // 0x10B07780
{
	mangled_x86(MANGLED_TODO, "?ConnectToServer@CServerConnectManager@@QAE_NABUSServerConnectOptions@@@Z");
	// SServerConnectOptions const &options;
	// SServerConnectState &state;
	todo("implement");
	bool __result = _sub_10B07780(this, options);
	return __result;
}

_extern void _sub_10B07D80(CServerConnectManager *const, EServerConnectAbortReason);
void CServerConnectManager::OnConnectionAborted(EServerConnectAbortReason reason) // 0x10B07D80
{
	mangled_x86(MANGLED_TODO, "?OnConnectionAborted@CServerConnectManager@@AAEXW4EServerConnectAbortReason@@@Z");
	// static ...; // 0x10B07FA5
	// static ...; // 0x10B07F98
	// static ...; // 0x10B07F80
	// static ...; // 0x10B07F78
// $LN10:
// $LN9:
// $LN8:
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// CServerConnectManager *const this;
	// EServerConnectAbortReason reason;
	// Web::Ui::ScreenLayer::SDialogShowParams dialogParams;
	// bool allowRetry;
	// std::string message;
	todo("implement");
	_sub_10B07D80(this, reason);
}

// mangled_x86(MANGLED_DEFAULT, "??0CServerConnectStateHandler_Connect@@QAE@XZ"); no body to assert in
_inline CServerConnectStateHandler_Connect::CServerConnectStateHandler_Connect() = default; // 0x10B05F80

// mangled_x86(MANGLED_DEFAULT, "??0CServerConnectStateHandler_QueryServer@@QAE@XZ"); no body to assert in
_inline CServerConnectStateHandler_QueryServer::CServerConnectStateHandler_QueryServer() = default; // 0x10B05FE0

// mangled_x86(MANGLED_DEFAULT, "??0CServerConnectStateManager@@QAE@XZ"); no body to assert in
_inline CServerConnectStateManager::CServerConnectStateManager() = default; // 0x10B06080

// mangled_x86(MANGLED_DEFAULT, "??0SQueryInfoServerData@@QAE@XZ"); no body to assert in
_inline SQueryInfoServerData::SQueryInfoServerData() = default; // 0x10B062C0

// mangled_x86(MANGLED_DEFAULT, "??1CServerConnectStateHandler_QueryServer@@QAE@XZ"); no body to assert in
_inline CServerConnectStateHandler_QueryServer::~CServerConnectStateHandler_QueryServer() = default; // 0x10B06C60

// mangled_x86(MANGLED_DEFAULT, "??1CServerConnectStateManager@@QAE@XZ"); no body to assert in
_inline CServerConnectStateManager::~CServerConnectStateManager() = default; // 0x10B06CD0

// mangled_x86(MANGLED_DEFAULT, "??1SQueryInfoServerData@@QAE@XZ"); no body to assert in
_inline SQueryInfoServerData::~SQueryInfoServerData() = default; // 0x10B06DB0

// mangled_x86(MANGLED_DEFAULT, "??1SRequiredMod@SServerConnectState@@QAE@XZ"); no body to assert in
_inline SServerConnectState::SRequiredMod::~SRequiredMod() = default; // 0x10B06E20

// mangled_x86(MANGLED_DEFAULT, "??1SServerConnectState@@QAE@XZ"); no body to assert in
_inline SServerConnectState::~SServerConnectState() = default; // 0x10B06EF0

extern SServerConnectState &_sub_10B07090(SServerConnectState *const, SServerConnectState &);
_inline SServerConnectState &SServerConnectState::operator=(SServerConnectState &&__that) // 0x10B07090
{
	mangled_x86(MANGLED_TODO, "??4SServerConnectState@@QAEAAU0@$$QAU0@@Z");
	// SServerConnectState &__that;
	{
		// unsigned __int32 $S1;
	}
	{
		// unsigned __int32 $S2;
	}
	compiler_generated();
	todo("implement");
	SServerConnectState & __result = _sub_10B07090(this, __that);
	return __result;
}

/* ---------- private code */

/* ---------- explicit instantiations */
template CEventSink<enum EServerConnectAbortReason>::CEventSink();
