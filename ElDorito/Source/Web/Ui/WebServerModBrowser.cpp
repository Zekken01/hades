/* ---------- headers */

#include "Web/Ui/WebServerModBrowser.hpp"
#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/input/input.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/new/ModListenerSet.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patch.hpp"
#include "Patches/CustomPackets.hpp"
#include "Pointer.hpp"
#include "Server/ModBrowser/ModBrowser.hpp"
#include "Server/ModBrowser/ModBrowserDefinitions.hpp"
#include "Server/ModBrowser/ModBrowserModDownloadUI.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/Ui/ScreenLayer.hpp"

#include <base/cef_atomic_ref_count.h>
#include <base/cef_lock.h>
#include <base/cef_logging.h>
#include <base/cef_platform_thread.h>
#include <base/cef_ref_counted.h>
#include <base/cef_scoped_refptr.h>
#include <base/cef_thread_checker.h>
#include <base/internal/cef_lock_impl.h>
#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>
#include <cef_base.h>
#include <cef_devtools_message_observer.h>
#include <cef_extension_handler.h>
#include <internal/cef_string_wrappers.h>
#include <internal/cef_types_wrappers.h>
#include <internal/cef_win.h>
#include <wrapper/cef_message_router.h>

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
#include <cmath>
#include <condition_variable>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <ostream>
#include <ratio>
#include <shared_mutex>
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
#include <vector>

/* ---------- forward declarations */

class IModBrowserModDownloadUI;
struct SModBrowserState;
struct lambda_1;
struct lambda_2;
namespace Web
{
	namespace Ui
	{
		class WebScreen;
	}
}
namespace Web
{
	namespace Ui
	{
		namespace WebServerModBrowser
		{
			class CWebModDownloadSingleScreen;
		}
	}
}
namespace hades_file_local
{
	namespace hades_file_local_WebServerModBrowser { struct DownloadStatusInfo; } using namespace hades_file_local_WebServerModBrowser;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace base {}
using namespace ::base;
namespace base
{
	namespace cef_subtle {}
	using namespace base::cef_subtle;
	namespace cef_internal {}
	using namespace base::cef_internal;
	namespace internal {}
	using namespace base::internal;
}

namespace Modules {}
using namespace ::Modules;
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

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Input {}
	using namespace Patches::Input;
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

namespace Web
{
	namespace Ui
	{
		namespace WebServerModBrowser
		{
			// hades: moved from hades/recovered_types.h onto its real base (was hades::polymorphic_bytes)
			struct CWebModDownloadSingleScreen :
				public Web::Ui::WebScreen,
				public IModBrowserModDownloadUI
			{
				virtual void OnCreate(Web::Browser::Bridge::WebRendererQueryHandler &);
				virtual void OnDestroy();
				virtual void OnShow();
				virtual void OnHide();
				virtual void OnUpdate();
				std::function<void ()> m_confirmCallback; // 0x8
				std::function<void ()> m_retryCallback; // 0x30
				std::function<void ()> m_cancelCallback; // 0x58
				std::function<void ()> m_downloadSingleCallback; // 0x80
			public:
				virtual void Hide();
				virtual void SetConfirmCallback(std::function<void __cdecl(void)>);
				virtual void SetRetryCallback(std::function<void __cdecl(void)>);
				virtual void SetCancelCallback(std::function<void __cdecl(void)>);
				virtual void OnDownloadStart();
				virtual void OnDownloadFailed(std::string const &);
				virtual void OnDownloadFinalizing();
				virtual void OnDownloadFinished(SModBrowserState const &);
				virtual void OnDownloadProgress(SModBrowserState::SRequestedMod const &, __int32, long long, long long, __int32);
				virtual void ShowConfirmation(std::vector<SModBrowserState::SRequestedMod *> const &);
				virtual void SetDownloadSingleFinishedCallback(std::function<void __cdecl(void)>);
				CWebModDownloadSingleScreen() = default;  // hades: not user-provided, so make_shared value-initializes
				// mangled_x86(MANGLED_KNOWN_GOOD, "??1CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAE@XZ"); defaulted on its declaration
				virtual ~CWebModDownloadSingleScreen() = default; // 0x10c7b8a0
			};
			static_assert32(sizeof(CWebModDownloadSingleScreen) == 168, "Invalid CWebModDownloadSingleScreen size");
		}
	}
}

namespace hades_file_local
{
	namespace hades_file_local_WebServerModBrowser { struct DownloadStatusInfo
	{
		SModBrowserState::SRequestedMod package; // 0x0
		__int32 packageIndex; // 0x104
		long long current; // 0x108
		long long total; // 0x110
		__int32 downloadSpeed; // 0x118
		DownloadStatusInfo(DownloadStatusInfo &); /* compiler_generated() */
		DownloadStatusInfo(DownloadStatusInfo const &); /* compiler_generated() */
		DownloadStatusInfo(); /* compiler_generated() */
		~DownloadStatusInfo(); /* compiler_generated() */
		DownloadStatusInfo &operator=(DownloadStatusInfo &); /* compiler_generated() */
		DownloadStatusInfo &operator=(DownloadStatusInfo const &); /* compiler_generated() */
		unsigned char __pad0[4]; // 0x11C
	}; }  // hades_file_local_WebServerModBrowser: DownloadStatusInfo is a different type in each translation unit
	static_assert(sizeof(DownloadStatusInfo) == 288, "Invalid DownloadStatusInfo size");
}
using namespace hades_file_local;
// Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

//class Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen::OnCreate::__l2::<lambda_1>
//{
//public:
//	Web::Browser::Bridge::QueryError operator()(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *) const;
//	<lambda_1>(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen::OnCreate::__l2::<lambda_1> &);
//	<lambda_1>(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *);
//private:
//	Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *__this; // 0x0
//public:
//	Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen::OnCreate::__l2::<lambda_1> &operator=(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen::OnCreate::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen::OnCreate::__l2::<lambda_1>) == 4, "Invalid Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen::OnCreate::__l2::<lambda_1> size");

//class Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen::OnCreate::__l2::<lambda_2>
//{
//public:
//	Web::Browser::Bridge::QueryError operator()(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *) const;
//};
//static_assert(sizeof(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen::OnCreate::__l2::<lambda_2>) == 1, "Invalid Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen::OnCreate::__l2::<lambda_2> size");

/* ---------- prototypes */

namespace Web
{
	namespace Ui
	{
		namespace WebServerModBrowser
		{
			extern std::shared_ptr<IModBrowserModDownloadUI> GetDownloadUISingle();
			extern void Init();
		}
	}
}

static void NotifyDownloadStateChanged(std::string const &fromState, std::string const &toState);
static void NotifyDownloadStatus(DownloadStatusInfo const &info);
static void NotifyDownloadError(std::string const &reason);

/* ---------- globals */

namespace Web
{
	namespace Ui
	{
		namespace WebServerModBrowser
		{
			std::shared_ptr<Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen> screen_single; // 0x1247EC94
		}
	}
}

/* ---------- private variables */

namespace hades_file_local
{
	extern bool screenVisible; // 0x1247EC90
}
using namespace hades_file_local;
/* ---------- public code */


namespace Web
{
	namespace Ui
	{
		namespace WebServerModBrowser
		{
			std::shared_ptr<IModBrowserModDownloadUI> GetDownloadUISingle() // 0x10C7CC90
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?GetDownloadUISingle@WebServerModBrowser@Ui@Web@@YA?AV?$shared_ptr@VIModBrowserModDownloadUI@@@std@@XZ");
				// procedure flags: nofpo

				return screen_single;
			}

			void CWebModDownloadSingleScreen::SetConfirmCallback(std::function<void __cdecl(void)> callback) // 0x10C7E100
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?SetConfirmCallback@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXV?$function@$$A6AXXZ@std@@@Z");
				// __shifted(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen, 4);
				// std::function<void __cdecl(void)> callback;

				m_confirmCallback = callback;
			}

			void CWebModDownloadSingleScreen::SetRetryCallback(std::function<void __cdecl(void)> callback) // 0x10C7E260
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?SetRetryCallback@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXV?$function@$$A6AXXZ@std@@@Z");
				// __shifted(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen, 4);
				// std::function<void __cdecl(void)> callback;

				m_retryCallback = callback;
			}

			void CWebModDownloadSingleScreen::SetCancelCallback(std::function<void __cdecl(void)> callback) // 0x10C7E050
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?SetCancelCallback@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXV?$function@$$A6AXXZ@std@@@Z");
				// __shifted(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen, 4);
				// std::function<void __cdecl(void)> callback;

				m_cancelCallback = callback;
			}

			void CWebModDownloadSingleScreen::SetDownloadSingleFinishedCallback(std::function<void __cdecl(void)> callback) // 0x10C7E1B0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?SetDownloadSingleFinishedCallback@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXV?$function@$$A6AXXZ@std@@@Z");
				// __shifted(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen, 4);
				// std::function<void __cdecl(void)> callback;

				m_downloadSingleCallback = callback;
			}

			void CWebModDownloadSingleScreen::OnDownloadStart() // 0x10C7DE90
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnDownloadStart@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXXZ");
				// __shifted(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen, 4);
				// Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const this;

				NotifyDownloadStateChanged("downloading", "downloading");
			}

			void CWebModDownloadSingleScreen::OnDownloadFailed(std::string const &message) // 0x10C7D990
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnDownloadFailed@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
				// __shifted(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen, 4);
				// std::string const &message;

				NotifyDownloadStateChanged("download_failed", "download_failed");
				NotifyDownloadError(message);
			}

			void CWebModDownloadSingleScreen::OnDownloadFinalizing() // 0x10C7DAB0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnDownloadFinalizing@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXXZ");
				// __shifted(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen, 4);
				// Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const this;

				NotifyDownloadStateChanged("downloading", "download_finalizing");
			}

			void CWebModDownloadSingleScreen::OnDownloadFinished(SModBrowserState const &state) // 0x10C7DBB0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnDownloadFinished@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXABUSModBrowserState@@@Z");
				// __shifted(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen, 4);
				// SModBrowserState const &state;

				Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::ModDownload, "modDownloadSingleFinished", "{}");
				NotifyDownloadStateChanged("download_finalizing", "download_single_finished");
			}

			void CWebModDownloadSingleScreen::Hide() // 0x10C7CD00
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Hide@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXXZ");
				// __shifted(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen, 4);
				// Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const this;

				NotifyDownloadStateChanged("awaiting_confirmation_single", "awaiting_confirmation_single");
				Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::ModDownload, "hide_moddownloader", "{}");
				screenVisible = false;
			}

			void CWebModDownloadSingleScreen::OnDestroy() // 0x10C7D950
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnDestroy@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXXZ");
				// Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const this;
			}

			void CWebModDownloadSingleScreen::OnShow() // 0x10C7DFD0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnShow@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXXZ");
				// Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const this;
			}

			void CWebModDownloadSingleScreen::OnHide() // 0x10C7DF90
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnHide@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXXZ");
				// Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const this;
			}

			void CWebModDownloadSingleScreen::OnUpdate() // 0x10C7E010
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnUpdate@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXXZ");
				// Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const this;
			}

			void Init() // 0x10C7CE90
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Init@WebServerModBrowser@Ui@Web@@YAXXZ");
				// procedure flags: nofpo

				screen_single = std::make_shared<CWebModDownloadSingleScreen>();
				Web::Ui::ScreenLayer::RegisterScreen("mod_download_single", screen_single);
			}

			// mangled_x86(MANGLED_DEFAULT, "??0CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@QAE@XZ"); no body to assert in
			// _inline CWebModDownloadSingleScreen::CWebModDownloadSingleScreen() = default; // 0x10C7B4E0  // hades: defaulted on its declaration
		}
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0IModBrowserModDownloadUI@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0SModBrowserState@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0SRequestedMod@SModBrowserState@@QAE@XZ"); no body to assert in

namespace Web
{
	namespace Ui
	{
		// mangled_x86(MANGLED_DEFAULT, "??0WebScreen@Ui@Web@@QAE@XZ"); no body to assert in
	}
}

namespace Web
{
	namespace Ui
	{
		namespace WebServerModBrowser
		{
		}
	}
}

/* ---------- private code */

static void NotifyDownloadStateChanged(std::string const &fromState, std::string const &toState) // 0x10C7D210
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?NotifyDownloadStateChanged@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
	// `anonymous-namespace'::NotifyDownloadStateChanged
	// static ...; // 0x10C7D3A0
	// static ...; // 0x10C7D388
	// static ...; // 0x10C7D380
	// std::string const &fromState;
	// std::string const &toState;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buff;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;

	rapidjson::StringBuffer buff;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buff);
	writer.StartObject();
	writer.Key("fromState");
	writer.String(fromState.c_str());
	writer.Key("toState");
	writer.String(toState.c_str());
	writer.EndObject();
	Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::ModDownload, "modDownloadStateChange", buff.GetString());
}

static void NotifyDownloadStatus(DownloadStatusInfo const &info) // 0x10C7D420
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?NotifyDownloadStatus@@YAXABUDownloadStatusInfo@hades_file_local@@@Z");
	// `anonymous-namespace'::NotifyDownloadStatus
	// static ...; // 0x10C7D6D7
	// static ...; // 0x10C7D6D0
	// static ...; // 0x10C7D6B8
	// static ...; // 0x10C7D6B0
	// DownloadStatusInfo const &info;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buff;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;

	rapidjson::StringBuffer buff;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buff);
	writer.StartObject();
	writer.Key("index");
	writer.Int(info.packageIndex);
	writer.Key("name");
	writer.String(info.package.name.c_str());
	writer.Key("desc");
	writer.String(info.package.description.c_str());
	writer.Key("website");
	writer.String(info.package.website.c_str());
	writer.Key("version");
	writer.String(info.package.version.c_str());
	writer.Key("package_url");
	writer.String(info.package.packageUrl.c_str());
	writer.Key("hash");
	writer.Key(info.package.hash.c_str());
	writer.Key("current");
	writer.Int64(info.current);
	writer.Key("total");
	writer.Int64(info.total);
	writer.Key("speed");
	writer.Int64(info.downloadSpeed);
	writer.EndObject();
	Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::ModDownload, "modDownloadStatus", buff.GetString());
}

static void NotifyDownloadError(std::string const &reason) // 0x10C7D030
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?NotifyDownloadError@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::NotifyDownloadError
	// static ...; // 0x10C7D1AB
	// static ...; // 0x10C7D1A4
	// static ...; // 0x10C7D18C
	// static ...; // 0x10C7D184
	// std::string const &reason;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buff;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;

	rapidjson::StringBuffer buff;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buff);
	writer.StartObject();
	writer.Key("reason");
	writer.String(reason.c_str());
	writer.EndObject();
	Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::ModDownload, "modDownloadFailed", buff.GetString());
}

// mangled_x86(MANGLED_DEFAULT, "??0DownloadStatusInfo@hades_file_local@@QAE@XZ"); no body to assert in
_inline DownloadStatusInfo::DownloadStatusInfo() = default; // 0x10C7B590

// mangled_x86(MANGLED_DEFAULT, "??1DownloadStatusInfo@hades_file_local@@QAE@XZ"); no body to assert in
_inline DownloadStatusInfo::~DownloadStatusInfo() = default; // 0x10C7B930

namespace Web
{
	namespace Ui
	{
		namespace WebServerModBrowser
		{
			void CWebModDownloadSingleScreen::OnDownloadProgress(SModBrowserState::SRequestedMod const &package, __int32 packageIndex, long long current, long long total, __int32 downloadSpeed) // 0x10C7DD40
			{

							DownloadStatusInfo info;
							info.packageIndex = packageIndex;
							info.package = package;
							info.current = current;
							info.total = total;
							info.downloadSpeed = downloadSpeed;
							NotifyDownloadStatus(info);
			}
		}
	}
}

namespace Web
{
	namespace Ui
	{
		namespace WebServerModBrowser
		{
			void CWebModDownloadSingleScreen::OnCreate(Web::Browser::Bridge::WebRendererQueryHandler &queryHandler) // 0x10C7D790
			{

							queryHandler.AddMethod("modDownloadActionSingle", [this](rapidjson::Value const &args, std::string *result) -> Web::Browser::Bridge::QueryError
							{
								auto actionMember = args.FindMember("action");
								if (actionMember == args.MemberEnd() || !actionMember->value.IsString())
								{
									*result = "Bad query : A \"action\" argument is required and must be a string";
									return Web::Browser::Bridge::QueryError_BadQuery;
								}
								std::string action = actionMember->value.GetString();
								if (action == "confirm" && m_confirmCallback)
									m_confirmCallback();
								else if (action == "reject" && m_cancelCallback)
									m_cancelCallback();
								else if (action == "retry" && m_retryCallback)
									m_retryCallback();
								else if (action == "confirmFinished" && m_downloadSingleCallback)
									m_downloadSingleCallback();
								return Web::Browser::Bridge::QueryError_Ok;
							});
							queryHandler.AddMethod("modDownloadOption", [](rapidjson::Value const &args, std::string *result) -> Web::Browser::Bridge::QueryError
							{
								auto modMember = args.FindMember("mod");
								if (modMember == args.MemberEnd() || !modMember->value.IsObject())
								{
									*result = "Bad query : A \"mod\" argument is required and must be a object";
									return Web::Browser::Bridge::QueryError_BadQuery;
								}
								const char *requiredMembers[] = { "hash", "name", "host_player", "package_url", "source", "version", "source_ip" };
								for (auto memberName : requiredMembers)
								{
									auto member = modMember->value.FindMember(memberName);
									if (member == modMember->value.MemberEnd() || !member->value.IsString() || member->value.GetStringLength() == 0)
									{
										*result = std::string("Bad query: \"") + memberName + "\" must be a non-empty string";
										return Web::Browser::Bridge::QueryError_BadQuery;
									}
								}
								const char *optionalMembers[] = { "author", "description", "website" };
								for (auto memberName : optionalMembers)
								{
									auto member = modMember->value.FindMember(memberName);
									if (member == modMember->value.MemberEnd() || !member->value.IsString())
									{
										*result = std::string("Bad query: \"") + memberName + "\" must be a string";
										return Web::Browser::Bridge::QueryError_BadQuery;
									}
								}
								auto authorMember = modMember->value.FindMember("author");
								auto descriptionMember = modMember->value.FindMember("description");
								auto filesizeMember = modMember->value.FindMember("filesize");
								auto hashMember = modMember->value.FindMember("hash");
								auto nameMember = modMember->value.FindMember("name");
								auto urlMember = modMember->value.FindMember("package_url");
								auto sourceNameMember = modMember->value.FindMember("source");
								auto versionMember = modMember->value.FindMember("version");
								auto websiteMember = modMember->value.FindMember("website");
								auto sourceIPMember = modMember->value.FindMember("source_ip");
								auto hostPlayerMember = modMember->value.FindMember("host_player");
								if (!filesizeMember->value.IsUint64())
								{
									*result = "Bad query: \"filesize\" must be a number";
									return Web::Browser::Bridge::QueryError_BadQuery;
								}
								auto author = authorMember->value.GetString();
								auto description = descriptionMember->value.GetString();
								auto filesize = filesizeMember->value.GetUint64();
								auto hash = hashMember->value.GetString();
								auto name = nameMember->value.GetString();
								auto url = urlMember->value.GetString();
								auto sourceName = sourceNameMember->value.GetString();
								auto version = versionMember->value.GetString();
								auto website = websiteMember->value.GetString();
								auto sourceIP = sourceIPMember->value.GetString();
								auto hostPlayer = hostPlayerMember->value.GetString();
								SModBrowserState options;
								options = {};
								options.requestedMod.author = author;
								options.requestedMod.description = description;
								options.requestedMod.fileSize = filesize;
								options.requestedMod.hash = hash;
								options.requestedMod.name = name;
								options.requestedMod.packageUrl = url;
								options.requestedMod.version = version;
								options.requestedMod.website = website;
								options.hostname = sourceIP;
								options.serverName = sourceName;
								options.serverHost = hostPlayer;
								Utils::Singleton<CModBrowserManager>::Instance().DownloadMod(options);
								return Web::Browser::Bridge::QueryError_Ok;
							});
			}
		}
	}
}

// hades: ShowConfirmation was dropped from the tree (an orphaned member); it sits at the
// end of the file so the functions above keep their line numbers.
namespace Web
{
	namespace Ui
	{
		namespace WebServerModBrowser
		{
			void CWebModDownloadSingleScreen::ShowConfirmation(std::vector<SModBrowserState::SRequestedMod *> const &mods) // 0x10C7E310
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?ShowConfirmation@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXABV?$vector@PAUSRequestedMod@SModBrowserState@@V?$allocator@PAUSRequestedMod@SModBrowserState@@@std@@@std@@@Z");

				rapidjson::StringBuffer buff;
				rapidjson::Writer<rapidjson::StringBuffer> writer(buff);
				writer.StartObject();
				for (auto mod : mods)
				{
					writer.Key(mod->localName.c_str());
					writer.StartObject();
					writer.Key("hash");
					writer.String(mod->hash.c_str());
					writer.Key("mod_author");
					writer.String(mod->author.c_str());
					writer.Key("mod_description");
					writer.String(mod->description.c_str());
					writer.Key("mod_name");
					writer.String(mod->name.c_str());
					writer.Key("mod_version");
					writer.String(mod->version.c_str());
					writer.Key("mod_website");
					writer.String(mod->website.c_str());
					writer.Key("package_size");
					writer.Int64(mod->fileSize);
					writer.Key("package_url");
					writer.String(mod->packageUrl.c_str());
					writer.EndObject();
				}
				writer.EndObject();
				auto json = buff.GetString();
				Web::Ui::ScreenLayer::Show(Web::Ui::ScreenLayer::ModDownload, buff.GetString());
				NotifyDownloadStateChanged("awaiting_confirmation_single", "awaiting_confirmation_single");
				screenVisible = true;
			}
		}
	}
}
