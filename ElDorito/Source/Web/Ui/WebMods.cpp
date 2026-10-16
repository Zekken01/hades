/* ---------- headers */

#include "Web/Ui/WebMods.hpp"
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
#include "Download/IDownload.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Patches/Input.hpp"  // hades: added for 0x10CAD540
#include "mods/mod_system.hpp"  // hades: added for 0x10CAD540
#include "mods/new/ModListenerSet.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patch.hpp"
#include "Patches/CustomPackets.hpp"
#include "Pointer.hpp"
#include "Server/Connect/ServerConnectDefintiions.hpp"
#include "Server/Connect/ServerConnectModDownloadUI.hpp"
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
#include "Utils/EventSink.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/Ui/ScreenLayer.hpp"
#include "Modules/ModuleSettings.hpp"
#include "Modules/ModuleVoting.hpp"

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

class IMod;
class IModListener;
class IServerConnectModDownloadUI;
class c_mod_package;
struct SServerConnectState;
struct lambda_1;
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}
namespace Web
{
	namespace Ui
	{
		namespace WebMods
		{
			class CWebModDownloadScreen;
		}
	}
}
namespace hades_file_local
{
	namespace hades_file_local_WebMods { struct DownloadStatusInfo; } using namespace hades_file_local_WebMods;
	class ModChangeListener;
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
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

namespace Web
{
	namespace Ui
	{
		namespace WebMods
		{
			// hades: moved from hades/recovered_types.h onto its real base (was hades::polymorphic_bytes)
			struct CWebModDownloadScreen :
				public Web::Ui::WebScreen,
				public IServerConnectModDownloadUI
			{
				virtual void OnCreate(Web::Browser::Bridge::WebRendererQueryHandler &);
				virtual void OnDestroy();
				virtual void OnShow();
				virtual void OnHide();
				virtual void OnUpdate();
				std::function<void ()> m_confirmCallback; // 0x8
				std::function<void ()> m_retryCallback; // 0x30
				std::function<void ()> m_cancelCallback; // 0x58
				std::function<void ()> m_joinServerCallback; // 0x80
			public:
				virtual void Hide();
				virtual void SetConfirmCallback(std::function<void __cdecl(void)>);
				virtual void SetRetryCallback(std::function<void __cdecl(void)>);
				virtual void SetCancelCallback(std::function<void __cdecl(void)>);
				virtual void SetJoinServerCallback(std::function<void __cdecl(void)>);
				virtual void OnDownloadStart();
				virtual void OnDownloadFailed(std::string const &);
				virtual void OnDownloadFinalizing();
				virtual void OnDownloadFinished(SServerConnectState const &);
				virtual void OnDownloadProgress(SServerConnectState::SRequiredMod const &, __int32, long long, long long, __int32);
				virtual void ShowConfirmation(std::vector<SServerConnectState::SRequiredMod *> const &);
				CWebModDownloadScreen() = default;  // hades: not user-provided, so make_shared value-initializes
				// mangled_x86(MANGLED_KNOWN_GOOD, "??1CWebModDownloadScreen@WebMods@Ui@Web@@UAE@XZ"); defaulted on its declaration
				virtual ~CWebModDownloadScreen() = default; // 0x10caca50
			};
			static_assert32(sizeof(CWebModDownloadScreen) == 168, "Invalid CWebModDownloadScreen size");
		}
	}
}

namespace hades_file_local
{
	namespace hades_file_local_WebMods { struct DownloadStatusInfo
	{
		SServerConnectState::SRequiredMod package; // 0x0
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
	}; }  // hades_file_local_WebMods: DownloadStatusInfo is a different type in each translation unit
	static_assert(sizeof(DownloadStatusInfo) == 288, "Invalid DownloadStatusInfo size");

	class ModChangeListener :
		public IModListener
	{
	private:
		virtual void OnModChanged(EModIndex, IMod *);
	public:
		// hades: the other special members are implicit, so `new ModChangeListener()` zeroes the object and calls a noexcept constructor
		virtual ~ModChangeListener() = default; /* compiler_generated() */
	};
	static_assert(sizeof(ModChangeListener) == 4, "Invalid ModChangeListener size");
}
using namespace hades_file_local;
// Web::Ui::WebMods::CWebModDownloadScreen is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

//class Web::Ui::WebMods::CWebModDownloadScreen::OnCreate::__l2::<lambda_1>
//{
//public:
//	Web::Browser::Bridge::QueryError operator()(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::string *) const;
//	<lambda_1>(Web::Ui::WebMods::CWebModDownloadScreen::OnCreate::__l2::<lambda_1> &);
//	<lambda_1>(Web::Ui::WebMods::CWebModDownloadScreen *);
//private:
//	Web::Ui::WebMods::CWebModDownloadScreen *__this; // 0x0
//public:
//	Web::Ui::WebMods::CWebModDownloadScreen::OnCreate::__l2::<lambda_1> &operator=(Web::Ui::WebMods::CWebModDownloadScreen::OnCreate::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(Web::Ui::WebMods::CWebModDownloadScreen::OnCreate::__l2::<lambda_1>) == 4, "Invalid Web::Ui::WebMods::CWebModDownloadScreen::OnCreate::__l2::<lambda_1> size");

//class Web::Ui::WebMods::Init::__l2::<lambda_1>
//{
//public:
//	void operator()() const;
//};
//static_assert(sizeof(Web::Ui::WebMods::Init::__l2::<lambda_1>) == 1, "Invalid Web::Ui::WebMods::Init::__l2::<lambda_1> size");

/* ---------- prototypes */

namespace Web
{
	namespace Ui
	{
		namespace WebMods
		{
			extern std::shared_ptr<IServerConnectModDownloadUI> GetDownloadUI();
			extern void OnGameInputUpdated();
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
		namespace WebMods
		{
			std::shared_ptr<Web::Ui::WebMods::CWebModDownloadScreen> screen; // 0x1247EDD0
		}
	}
}

/* ---------- private variables */

namespace hades_file_local
{
	namespace hades_file_local_WebMods { extern bool screenVisible; } using namespace hades_file_local_WebMods; // 0x1247EDCC
}
using namespace hades_file_local;
/* ---------- public code */


namespace Web
{
	namespace Ui
	{
		namespace WebMods
		{
			std::shared_ptr<IServerConnectModDownloadUI> GetDownloadUI() // 0x10CAD340
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?GetDownloadUI@WebMods@Ui@Web@@YA?AV?$shared_ptr@VIServerConnectModDownloadUI@@@std@@XZ");
				// procedure flags: nofpo

				return screen;
			}

			void CWebModDownloadScreen::SetConfirmCallback(std::function<void __cdecl(void)> callback) // 0x10CAEDF0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?SetConfirmCallback@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXV?$function@$$A6AXXZ@std@@@Z");
				// __shifted(Web::Ui::WebMods::CWebModDownloadScreen, 4);
				// std::function<void __cdecl(void)> callback;

				m_confirmCallback = callback;
			}

			void CWebModDownloadScreen::SetRetryCallback(std::function<void __cdecl(void)> callback) // 0x10CAEF50
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?SetRetryCallback@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXV?$function@$$A6AXXZ@std@@@Z");
				// __shifted(Web::Ui::WebMods::CWebModDownloadScreen, 4);
				// std::function<void __cdecl(void)> callback;

				m_retryCallback = callback;
			}

			void CWebModDownloadScreen::SetCancelCallback(std::function<void __cdecl(void)> callback) // 0x10CAED40
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?SetCancelCallback@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXV?$function@$$A6AXXZ@std@@@Z");
				// __shifted(Web::Ui::WebMods::CWebModDownloadScreen, 4);
				// std::function<void __cdecl(void)> callback;

				m_cancelCallback = callback;
			}

			void CWebModDownloadScreen::SetJoinServerCallback(std::function<void __cdecl(void)> callback) // 0x10CAEEA0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?SetJoinServerCallback@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXV?$function@$$A6AXXZ@std@@@Z");
				// __shifted(Web::Ui::WebMods::CWebModDownloadScreen, 4);
				// std::function<void __cdecl(void)> callback;

				m_joinServerCallback = callback;
			}

			void CWebModDownloadScreen::OnDownloadStart() // 0x10CAE620
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnDownloadStart@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXXZ");
				// __shifted(Web::Ui::WebMods::CWebModDownloadScreen, 4);
				// Web::Ui::WebMods::CWebModDownloadScreen *const this;

				NotifyDownloadStateChanged("downloading", "downloading");
			}

			void CWebModDownloadScreen::OnDownloadFailed(std::string const &message) // 0x10CAE020
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnDownloadFailed@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
				// __shifted(Web::Ui::WebMods::CWebModDownloadScreen, 4);
				// std::string const &message;

				NotifyDownloadStateChanged("download_failed", "download_failed");
				NotifyDownloadError(message);
			}

			void CWebModDownloadScreen::OnDownloadFinalizing() // 0x10CAE140
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnDownloadFinalizing@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXXZ");
				// __shifted(Web::Ui::WebMods::CWebModDownloadScreen, 4);
				// Web::Ui::WebMods::CWebModDownloadScreen *const this;

				NotifyDownloadStateChanged("downloading", "download_finalizing");
			}

			void CWebModDownloadScreen::OnDownloadFinished(SServerConnectState const &state) // 0x10CAE240
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnDownloadFinished@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXABUSServerConnectState@@@Z");
				// __shifted(Web::Ui::WebMods::CWebModDownloadScreen, 4);
				// static ...; // 0x10CAE438
				// static ...; // 0x10CAE420
				// static ...; // 0x10CAE418
				// Web::Ui::WebMods::CWebModDownloadScreen *const this;
				// SServerConnectState const &state;
				// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buff;
				// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;

				rapidjson::StringBuffer buff;
				rapidjson::Writer<rapidjson::StringBuffer> writer(buff);
				writer.StartObject();
				writer.Key("serverName");
				writer.String(state.serverName.c_str());
				writer.Key("serverHost");
				writer.String(state.serverHost.c_str());
				writer.EndObject();
				Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::ModDownload, "modDownloadFinished", buff.GetString());
				NotifyDownloadStateChanged("download_finalizing", "download_finished");
			}

			void CWebModDownloadScreen::Hide() // 0x10CAD3B0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Hide@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXXZ");
				// __shifted(Web::Ui::WebMods::CWebModDownloadScreen, 4);
				// Web::Ui::WebMods::CWebModDownloadScreen *const this;

				NotifyDownloadStateChanged("awaiting_confirmation", "awaiting_confirmation");
				Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::ModDownload, "hide_moddownloader", "{}");
				screenVisible = false;
			}

			void CWebModDownloadScreen::OnDestroy() // 0x10CAE000
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnDestroy@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXXZ");
				// Web::Ui::WebMods::CWebModDownloadScreen *const this;
			}

			void CWebModDownloadScreen::OnShow() // 0x10CAED00
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnShow@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXXZ");
				// Web::Ui::WebMods::CWebModDownloadScreen *const this;
			}

			void CWebModDownloadScreen::OnHide() // 0x10CAE9E0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnHide@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXXZ");
				// Web::Ui::WebMods::CWebModDownloadScreen *const this;
			}

			void CWebModDownloadScreen::OnUpdate() // 0x10CAED20
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnUpdate@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXXZ");
				// Web::Ui::WebMods::CWebModDownloadScreen *const this;
			}

			void OnGameInputUpdated() // 0x10CAE720
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnGameInputUpdated@WebMods@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
					// Blam::Network::Session *session;
				// function call : bool (*const)()

				if (Utils::Singleton<Modules::ModuleSettings>::Instance().VarGamepadEnabled->ValueInt == 1)
				{
					if (Blam::Input::GetActionState(Blam::Input::eGameActionUiY)->Ticks == 1 && !Blam::Input::GetKeyTicks(Blam::Input::eKeyCodeEscape, Blam::Input::eInputTypeUi))
						ScreenLayer::NotifyScreen(ScreenLayer::ModDownload, "menuMaximizedByController", "{}");
					Blam::Network::Session *session = Blam::Network::GetActiveSession();
					if (((bool (*const)())0x531E90)() && Blam::Input::GetActionState(Blam::Input::eGameActionUiY)->Ticks == 1 && !Blam::Input::GetKeyTicks(Blam::Input::eKeyCodeEscape, Blam::Input::eInputTypeUi))
					{
						if (session && session->IsEstablished() && !session->IsHost())
							return;
						else if (session && session->IsEstablished() && session->IsHost() && Blam::Network::GetNetworkMode() == 3 && Utils::Singleton<Modules::ModuleVoting>::Instance().VarServerVotingType->ValueInt >= 0)
							return;
						if (!screenVisible)
							ScreenLayer::Show("mod_browse", "{}");
					}
				}
			}

			void Init() // 0x10CAD540
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Init@WebMods@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				// function call : void (IModListener *)

				screen = std::make_shared<CWebModDownloadScreen>();
				ScreenLayer::RegisterScreen("mod_download", screen);
				Patches::Input::RegisterDefaultInputHandler(OnGameInputUpdated);
				c_mod_system::get_package_manager().enumerated.Subscribe([]()
				{
					ScreenLayer::Notify("modsEnumerated", "{}", true);
				});
				c_mod_system::GetModManager().AddListener(new ModChangeListener());
			}

			// mangled_x86(MANGLED_DEFAULT, "??0CWebModDownloadScreen@WebMods@Ui@Web@@QAE@XZ"); no body to assert in
			// _inline CWebModDownloadScreen::CWebModDownloadScreen() = default; // 0x10CAC810  // hades: defaulted on its declaration
		}
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0IServerConnectModDownloadUI@@QAE@XZ"); no body to assert in

namespace Web
{
	namespace Ui
	{
		namespace WebMods
		{
		}
	}
}

// mangled_x86(MANGLED_DEFAULT, "??4SRequiredMod@SServerConnectState@@QAEAAU01@ABU01@@Z"); no body to assert in
_inline SServerConnectState::SRequiredMod &SServerConnectState::SRequiredMod::operator=(SServerConnectState::SRequiredMod const &__that) = default; // 0x10CACC30

/* ---------- private code */

_inline void ModChangeListener::OnModChanged(EModIndex index, IMod *mod) // 0x10CAEA00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnModChanged@ModChangeListener@hades_file_local@@EAEXW4EModIndex@@PAVIMod@@@Z");
	// `anonymous-namespace'::ModChangeListener::OnModChanged
	// static ...; // 0x10CAEC50
	// static ...; // 0x10CAEC2C
	// static ...; // 0x10CAEC24
	// ModChangeListener *const this;
	// EModIndex index;
	// IMod *mod;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buff;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
		// std::string hash_str;
		// c_mod_package *pak;
	// function call : c_mod_package *(bool) const

	rapidjson::StringBuffer buff;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buff);
	writer.StartObject();
	writer.Key("kind");
	writer.String(index == kMainMenu ? "mainmenu" : "game");
	if (mod)
	{
		writer.Key("hash");
		c_mod_package *pak = mod->GetPak(true);
		if (!pak)
			return;
		std::string hash_str;
		Utils::String::BytesToHexString(pak->get_header()->sha1, sizeof(pak->get_header()->sha1), hash_str);
		writer.String(hash_str.c_str());
	}
	writer.EndObject();
	Web::Ui::ScreenLayer::Notify("mod_changed", buff.GetString(), true);
}

static void NotifyDownloadStateChanged(std::string const &fromState, std::string const &toState) // 0x10CAD960
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?NotifyDownloadStateChanged@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
	// `anonymous-namespace'::NotifyDownloadStateChanged
	// static ...; // 0x10CADAF0
	// static ...; // 0x10CADAD8
	// static ...; // 0x10CADAD0
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

static void NotifyDownloadStatus(DownloadStatusInfo const &info) // 0x10CADB70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?NotifyDownloadStatus@@YAXABUDownloadStatusInfo@hades_file_local@@@Z");
	// `anonymous-namespace'::NotifyDownloadStatus
	// static ...; // 0x10CADE27
	// static ...; // 0x10CADE20
	// static ...; // 0x10CADE08
	// static ...; // 0x10CADE00
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

static void NotifyDownloadError(std::string const &reason) // 0x10CAD780
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?NotifyDownloadError@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::NotifyDownloadError
	// static ...; // 0x10CAD8FB
	// static ...; // 0x10CAD8F4
	// static ...; // 0x10CAD8DC
	// static ...; // 0x10CAD8D4
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
_inline DownloadStatusInfo::DownloadStatusInfo() = default; // 0x10CAC8C0

// mangled_x86(MANGLED_DEFAULT, "??0ModChangeListener@hades_file_local@@QAE@XZ"); no body to assert in
// ModChangeListener::ModChangeListener() is implicit; 0x10CAC940

// mangled_x86(MANGLED_DEFAULT, "??1DownloadStatusInfo@hades_file_local@@QAE@XZ"); no body to assert in
_inline DownloadStatusInfo::~DownloadStatusInfo() = default; // 0x10CACAE0


namespace Web
{
	namespace Ui
	{
		namespace WebMods
		{
			void CWebModDownloadScreen::OnDownloadProgress(SServerConnectState::SRequiredMod const &package, __int32 packageIndex, long long current, long long total, __int32 downloadSpeed) // 0x10CAE4D0
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
		namespace WebMods
		{
			void CWebModDownloadScreen::OnCreate(Web::Browser::Bridge::WebRendererQueryHandler &queryHandler) // 0x10CADEE0
			{

							queryHandler.AddMethod("modDownloadAction", [this](rapidjson::Value const &args, std::string *result) -> Web::Browser::Bridge::QueryError
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
								else if (action == "joinServer" && m_joinServerCallback)
									m_joinServerCallback();
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
		namespace WebMods
		{
			void CWebModDownloadScreen::ShowConfirmation(std::vector<SServerConnectState::SRequiredMod *> const &mods) // 0x10CAF000
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?ShowConfirmation@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXABV?$vector@PAUSRequiredMod@SServerConnectState@@V?$allocator@PAUSRequiredMod@SServerConnectState@@@std@@@std@@@Z");

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
				NotifyDownloadStateChanged("awaiting_confirmation", "awaiting_confirmation");
				screenVisible = true;
			}
		}
	}
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { namespace hades_file_local_WebMods { bool screenVisible; } }
