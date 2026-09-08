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

_extern void _sub_1070C4E0(CModBrowserManager *const);
void CModBrowserManager::Initialize() // 0x1070C4E0
{
	mangled_x86(MANGLED_TODO, "?Initialize@CModBrowserManager@@QAEXXZ");
	// static ...; // 0x1070C6B8
	// static ...; // 0x1070C6AC
	// static ...; // 0x1070C6A4
	// CModBrowserManager *const this;
	// std::shared_ptr<CModBrowserStateHandler_AcquireMod> acquireModsHandler;
	todo("implement");
	_sub_1070C4E0(this);
}

_extern bool _sub_1070C940(CModBrowserManager *const, SModBrowserState::SRequestedMod const &);
bool CModBrowserManager::ShouldDownloadPackage(SModBrowserState::SRequestedMod const &package) // 0x1070C940
{
	mangled_x86(MANGLED_TODO, "?ShouldDownloadPackage@CModBrowserManager@@AAE_NABUSRequestedMod@SModBrowserState@@@Z");
	// static ...; // 0x1070CAFA
	// static ...; // 0x1070CAF4
	// static ...; // 0x1070CAD0
	// static ...; // 0x1070CAC8
	// CModBrowserManager *const this;
	// SModBrowserState::SRequestedMod const &package;
	// c_mod_package_manager::s_entry package_entry;
	// unsigned char remote_hash[20];
	// c_mod_package cache;
	// c_mod_package_manager &package_manager;
	todo("implement");
	bool __result = _sub_1070C940(this, package);
	return __result;
}

_extern bool _sub_1070C070(CModBrowserManager *const, SModBrowserState const &);
bool CModBrowserManager::DownloadMod(SModBrowserState const &options) // 0x1070C070
{
	mangled_x86(MANGLED_TODO, "?DownloadMod@CModBrowserManager@@QAE_NABUSModBrowserState@@@Z");
	// static ...; // 0x1070C340
	// static ...; // 0x1070C338
	// CModBrowserManager *const this;
	// SModBrowserState const &options;
	// SModBrowserState &state;
	{
		// Web::Ui::ScreenLayer::SDialogShowParams dialogParams;
	}
	todo("implement");
	bool __result = _sub_1070C070(this, options);
	return __result;
}

_extern void _sub_1070CCA0(CModBrowserManager *const);
void CModBrowserManager::Update() // 0x1070CCA0
{
	mangled_x86(MANGLED_TODO, "?Update@CModBrowserManager@@QAEXXZ");
	// CModBrowserManager *const this;
	todo("implement");
	_sub_1070CCA0(this);
}

_extern void _sub_1070C750(CModBrowserManager *const, EModBrowserAbortReason);
void CModBrowserManager::OnDownloadAborted(EModBrowserAbortReason reason) // 0x1070C750
{
	mangled_x86(MANGLED_TODO, "?OnDownloadAborted@CModBrowserManager@@AAEXW4EModBrowserAbortReason@@@Z");
	// static ...; // 0x1070C8BC
	// static ...; // 0x1070C8A4
	// static ...; // 0x1070C89C
	// CModBrowserManager *const this;
	// EModBrowserAbortReason reason;
	// Web::Ui::ScreenLayer::SDialogShowParams dialogParams;
	// std::string message;
	todo("implement");
	_sub_1070C750(this, reason);
}

// mangled_x86(MANGLED_DEFAULT, "??0CModBrowserStateManager@@QAE@XZ"); no body to assert in
_inline CModBrowserStateManager::CModBrowserStateManager() = default; // 0x1070A870

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer
		{
			// mangled_x86(MANGLED_DEFAULT, "??0SDialogShowParams@ScreenLayer@Ui@Web@@QAE@XZ"); no body to assert in
			_inline SDialogShowParams::SDialogShowParams() = default; // 0x1070AB50
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

extern SModBrowserState &_sub_1070B930(SModBrowserState *const, SModBrowserState &);
_inline SModBrowserState &SModBrowserState::operator=(SModBrowserState &&__that) // 0x1070B930
{
	mangled_x86(MANGLED_TODO, "??4SModBrowserState@@QAEAAU0@$$QAU0@@Z");
	// SModBrowserState &__that;
	{
		// unsigned __int32 $S5;
	}
	{
		// unsigned __int32 $S6;
	}
	compiler_generated();
	todo("implement");
	SModBrowserState & __result = _sub_1070B930(this, __that);
	return __result;
}

// mangled_x86(MANGLED_DEFAULT, "??4SRequestedMod@SModBrowserState@@QAEAAU01@$$QAU01@@Z"); no body to assert in
_inline SModBrowserState::SRequestedMod &SModBrowserState::SRequestedMod::operator=(SModBrowserState::SRequestedMod &&__that) = default; // 0x1070BAC0

// mangled_x86(MANGLED_DEFAULT, "??4SRequestedMod@SModBrowserState@@QAEAAU01@ABU01@@Z"); no body to assert in
_inline SModBrowserState::SRequestedMod &SModBrowserState::SRequestedMod::operator=(SModBrowserState::SRequestedMod const &__that) = default; // 0x1070BC10

/* ---------- private code */
