/* ---------- headers */

#include "Server/ModBrowser/ModBrowser.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Console/Console.hpp"
#include "Download/IDownload.hpp"
#include "Forge/Magnets.hpp"
#include "Job/JobDefinitions.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patches/CustomPackets.hpp"
#include "Server/ModBrowser/ModBrowserDefinitions.hpp"
#include "Server/ModBrowser/ModBrowserStateHandler_AcquireMod.hpp"
#include "Server/ModBrowser/ModBrowserStateManager.hpp"
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
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/Ui/ScreenLayer.hpp"

#include "mods/mod_system.hpp"  // hades: added for 0x1070C940

#include "Web/Ui/WebServerModBrowser.hpp"  // hades: added for 0x1070C4E0

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
#include <ios>
#include <iosfwd>
#include <limits>
#include <list>
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
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

/* ---------- forward declarations */

class CModBrowserStateHandler_AcquireMod;
class CModBrowserStateManager;
class c_mod_package;
class c_mod_package_manager;
struct CModBrowserManager;
struct SModBrowserState;
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
		namespace WebServerModBrowser {}
		using namespace Web::Ui::WebServerModBrowser;
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

//class CModBrowserManager::Initialize::__l2::<lambda_1>
//{
//public:
//	void operator()(EModBrowserAbortReason) const;
//	<lambda_1>(CModBrowserManager::Initialize::__l2::<lambda_1> &);
//	<lambda_1>(CModBrowserManager *);
//private:
//	CModBrowserManager *__this; // 0x0
//public:
//	CModBrowserManager::Initialize::__l2::<lambda_1> &operator=(CModBrowserManager::Initialize::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(CModBrowserManager::Initialize::__l2::<lambda_1>) == 4, "Invalid CModBrowserManager::Initialize::__l2::<lambda_1> size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

void CModBrowserManager::Initialize() // 0x1070C4E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Initialize@CModBrowserManager@@QAEXXZ");

	auto acquireModsHandler = std::make_shared<CModBrowserStateHandler_AcquireMod>();
	acquireModsHandler->SetUI(Web::Ui::WebServerModBrowser::GetDownloadUISingle());
	m_stateManager = std::make_shared<CModBrowserStateManager>();
	m_stateManager->RegisterStateHandler(EModBrowserState::DownloadMod, acquireModsHandler);
	m_stateManager->AbortEvent.Subscribe([this](EModBrowserAbortReason reason) { OnDownloadAborted(reason); });
}

bool CModBrowserManager::ShouldDownloadPackage(SModBrowserState::SRequestedMod const &package) // 0x1070C940
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ShouldDownloadPackage@CModBrowserManager@@AAE_NABUSRequestedMod@SModBrowserState@@@Z");

	unsigned char remote_hash[20];
	Utils::String::HexStringToBytes(package.hash, remote_hash, sizeof(remote_hash));
	c_mod_package_manager &package_manager = c_mod_system::get_package_manager();
	c_mod_package_manager::s_entry package_entry;
	if (!package_manager.find_package_by_hash(remote_hash, &package_entry))
	{
		return true;
	}

	c_mod_package cache(package_entry.file.filename);
	if (!cache.initialize(nullptr))
	{
		return true;
	}

	cache.dispose();
	return false;
}

bool CModBrowserManager::DownloadMod(SModBrowserState const &options) // 0x1070C070
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DownloadMod@CModBrowserManager@@QAE_NABUSModBrowserState@@@Z");

	if (m_stateManager->InProgress())
		return false;
	if (!ShouldDownloadPackage(options.requestedMod))
	{
		Web::Ui::ScreenLayer::SDialogShowParams dialogParams;
		dialogParams.templateName = "mod_already_installed";
		dialogParams.callback = [](auto &result) {};
		Web::Ui::ScreenLayer::ShowDialog(dialogParams);
		return false;
	}
	SModBrowserState &state = m_stateManager->GetStateMutable();
	state = {};
	state.hostname = options.hostname;
	state.password = options.password;
	state.serverHost = options.serverHost;
	state.port = options.port;
	state.requestedMod = options.requestedMod;
	m_stateManager->RequestStateChange(EModBrowserState::DownloadMod);
	return true;
}

void CModBrowserManager::Update() // 0x1070CCA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Update@CModBrowserManager@@QAEXXZ");

	m_stateManager->Update();
}

void CModBrowserManager::OnDownloadAborted(EModBrowserAbortReason reason) // 0x1070C750
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnDownloadAborted@CModBrowserManager@@AAEXW4EModBrowserAbortReason@@@Z");

	std::string message;
	switch (reason)
	{
	case AddressResolutionFailed:
		message = "Failed to resolve hostname.";
		break;
	case ModSignatureVerificationFailed:
		message = "Failed to verify one or more mod package signatures. See dorito.log for details";
		break;
	default:
		return;
	}

	Web::Ui::ScreenLayer::SDialogShowParams dialogParams;
	dialogParams.templateName = "mod_download_error";
	dialogParams.customBody = message;
	dialogParams.callback = [](std::string const &) {};
	Web::Ui::ScreenLayer::ShowDialog(dialogParams);
}

// mangled_x86(MANGLED_DEFAULT, "??0CModBrowserStateManager@@QAE@XZ"); no body to assert in
// _inline CModBrowserStateManager::CModBrowserStateManager() = default; // 0x1070A870  // hades: defaulted on its declaration

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer
		{
			// mangled_x86(MANGLED_DEFAULT, "??0SDialogShowParams@ScreenLayer@Ui@Web@@QAE@XZ"); no body to assert in
		}
	}
}

// mangled_x86(MANGLED_DEFAULT, "??1CModBrowserStateManager@@QAE@XZ"); no body to assert in
_inline CModBrowserStateManager::~CModBrowserStateManager() = default; // 0x1070B500

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer
		{
			// mangled_x86(MANGLED_DEFAULT, "??1SDialogShowParams@ScreenLayer@Ui@Web@@QAE@XZ"); no body to assert in
			_inline SDialogShowParams::~SDialogShowParams() = default; // 0x1070B5E0
		}
	}
}

// mangled_x86(MANGLED_DEFAULT, "??1SModBrowserState@@QAE@XZ"); no body to assert in
_inline SModBrowserState::~SModBrowserState() = default; // 0x1070B670

// mangled_x86(MANGLED_DEFAULT, "??1SRequestedMod@SModBrowserState@@QAE@XZ"); no body to assert in
_inline SModBrowserState::SRequestedMod::~SRequestedMod() = default; // 0x1070B700

// mangled_x86(MANGLED_DEFAULT, "??4SModBrowserState@@QAEAAU0@$$QAU0@@Z"); no body to assert in
_inline SModBrowserState &SModBrowserState::operator=(SModBrowserState &&__that) noexcept = default; // 0x1070B930

// mangled_x86(MANGLED_DEFAULT, "??4SRequestedMod@SModBrowserState@@QAEAAU01@$$QAU01@@Z"); no body to assert in
_inline SModBrowserState::SRequestedMod &SModBrowserState::SRequestedMod::operator=(SModBrowserState::SRequestedMod &&__that) noexcept = default; // 0x1070BAC0

// mangled_x86(MANGLED_DEFAULT, "??4SRequestedMod@SModBrowserState@@QAEAAU01@ABU01@@Z"); no body to assert in
_inline SModBrowserState::SRequestedMod &SModBrowserState::SRequestedMod::operator=(SModBrowserState::SRequestedMod const &__that) = default; // 0x1070BC10

/* ---------- private code */

/* ---------- explicit instantiations */
template CEventSink<enum EModBrowserAbortReason>::CEventSink();
template CEventSink<enum EModBrowserAbortReason>::~CEventSink();
// template CEventSink<enum EModBrowserAbortReason>::SCallbackEntry::~SCallbackEntry();  // hades: implicit now; the sink's destructor emits it
