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
	struct DownloadStatusInfo;
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

namespace hades_file_local
{
	struct DownloadStatusInfo
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
	};
	static_assert(sizeof(DownloadStatusInfo) == 288, "Invalid DownloadStatusInfo size");
}
using namespace hades_file_local;
// Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

//class Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen::OnCreate::__l2::<lambda_1>
//{
//public:
//	Web::Browser::Bridge::QueryError operator()(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > *) const;
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
//	Web::Browser::Bridge::QueryError operator()(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > *) const;
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

void NotifyDownloadStateChanged(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &fromState, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &toState);
void NotifyDownloadStatus(DownloadStatusInfo const &info);
void NotifyDownloadError(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &reason);

/* ---------- globals */

namespace Web
{
	namespace Ui
	{
		namespace WebServerModBrowser
		{
			extern std::shared_ptr<Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen> screen_single; // 0x1247EC94
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

extern std::shared_ptr<IModBrowserModDownloadUI> _sub_10C7CC90();
namespace Web
{
	namespace Ui
	{
		namespace WebServerModBrowser
		{
			std::shared_ptr<IModBrowserModDownloadUI> GetDownloadUISingle() // 0x10C7CC90
			{
				mangled_x86(MANGLED_TODO, "?GetDownloadUISingle@WebServerModBrowser@Ui@Web@@YA?AV?$shared_ptr@VIModBrowserModDownloadUI@@@std@@XZ");
				// procedure flags: nofpo
				todo("implement");
				std::shared_ptr<IModBrowserModDownloadUI> __result = _sub_10C7CC90();
				return __result;
			}

			_extern void _sub_10C7E100(IModBrowserModDownloadUI * const, std::function<void __cdecl(void)>);
			void CWebModDownloadSingleScreen::SetConfirmCallback(std::function<void __cdecl(void)> callback) // 0x10C7E100
			{
				mangled_x86(MANGLED_TODO, "?SetConfirmCallback@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXV?$function@$$A6AXXZ@std@@@Z");
				// __shifted(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen, 4);
				// std::function<void __cdecl(void)> callback;
				todo("implement");
				_sub_10C7E100((IModBrowserModDownloadUI *)this, callback);
			}

			_extern void _sub_10C7E260(IModBrowserModDownloadUI * const, std::function<void __cdecl(void)>);
			void CWebModDownloadSingleScreen::SetRetryCallback(std::function<void __cdecl(void)> callback) // 0x10C7E260
			{
				mangled_x86(MANGLED_TODO, "?SetRetryCallback@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXV?$function@$$A6AXXZ@std@@@Z");
				// __shifted(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen, 4);
				// std::function<void __cdecl(void)> callback;
				todo("implement");
				_sub_10C7E260((IModBrowserModDownloadUI *)this, callback);
			}

			_extern void _sub_10C7E050(IModBrowserModDownloadUI * const, std::function<void __cdecl(void)>);
			void CWebModDownloadSingleScreen::SetCancelCallback(std::function<void __cdecl(void)> callback) // 0x10C7E050
			{
				mangled_x86(MANGLED_TODO, "?SetCancelCallback@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXV?$function@$$A6AXXZ@std@@@Z");
				// __shifted(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen, 4);
				// std::function<void __cdecl(void)> callback;
				todo("implement");
				_sub_10C7E050((IModBrowserModDownloadUI *)this, callback);
			}

			_extern void _sub_10C7E1B0(IModBrowserModDownloadUI * const, std::function<void __cdecl(void)>);
			void CWebModDownloadSingleScreen::SetDownloadSingleFinishedCallback(std::function<void __cdecl(void)> callback) // 0x10C7E1B0
			{
				mangled_x86(MANGLED_TODO, "?SetDownloadSingleFinishedCallback@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXV?$function@$$A6AXXZ@std@@@Z");
				// __shifted(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen, 4);
				// std::function<void __cdecl(void)> callback;
				todo("implement");
				_sub_10C7E1B0((IModBrowserModDownloadUI *)this, callback);
			}

			_extern void _sub_10C7DE90(IModBrowserModDownloadUI * const);
			void CWebModDownloadSingleScreen::OnDownloadStart() // 0x10C7DE90
			{
				mangled_x86(MANGLED_TODO, "?OnDownloadStart@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXXZ");
				// __shifted(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen, 4);
				// Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const this;
				todo("implement");
				_sub_10C7DE90((IModBrowserModDownloadUI *)this);
			}

			_extern void _sub_10C7D990(IModBrowserModDownloadUI * const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
			void CWebModDownloadSingleScreen::OnDownloadFailed(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &message) // 0x10C7D990
			{
				mangled_x86(MANGLED_TODO, "?OnDownloadFailed@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
				// __shifted(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen, 4);
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &message;
				todo("implement");
				_sub_10C7D990((IModBrowserModDownloadUI *)this, message);
			}

			_extern void _sub_10C7DAB0(IModBrowserModDownloadUI * const);
			void CWebModDownloadSingleScreen::OnDownloadFinalizing() // 0x10C7DAB0
			{
				mangled_x86(MANGLED_TODO, "?OnDownloadFinalizing@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXXZ");
				// __shifted(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen, 4);
				// Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const this;
				todo("implement");
				_sub_10C7DAB0((IModBrowserModDownloadUI *)this);
			}

			_extern void _sub_10C7DBB0(IModBrowserModDownloadUI * const, SModBrowserState const &);
			void CWebModDownloadSingleScreen::OnDownloadFinished(SModBrowserState const &state) // 0x10C7DBB0
			{
				mangled_x86(MANGLED_TODO, "?OnDownloadFinished@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXABUSModBrowserState@@@Z");
				// __shifted(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen, 4);
				// SModBrowserState const &state;
				todo("implement");
				_sub_10C7DBB0((IModBrowserModDownloadUI *)this, state);
			}

			_extern void _sub_10C7CD00(IModBrowserModDownloadUI * const);
			void CWebModDownloadSingleScreen::Hide() // 0x10C7CD00
			{
				mangled_x86(MANGLED_TODO, "?Hide@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXXZ");
				// __shifted(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen, 4);
				// Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const this;
				todo("implement");
				_sub_10C7CD00((IModBrowserModDownloadUI *)this);
			}

			_extern void _sub_10C7D950(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const);
			void CWebModDownloadSingleScreen::OnDestroy() // 0x10C7D950
			{
				mangled_x86(MANGLED_TODO, "?OnDestroy@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXXZ");
				// Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const this;
				todo("implement");
				_sub_10C7D950(this);
			}

			_extern void _sub_10C7DFD0(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const);
			void CWebModDownloadSingleScreen::OnShow() // 0x10C7DFD0
			{
				mangled_x86(MANGLED_TODO, "?OnShow@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXXZ");
				// Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const this;
				todo("implement");
				_sub_10C7DFD0(this);
			}

			_extern void _sub_10C7DF90(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const);
			void CWebModDownloadSingleScreen::OnHide() // 0x10C7DF90
			{
				mangled_x86(MANGLED_TODO, "?OnHide@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXXZ");
				// Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const this;
				todo("implement");
				_sub_10C7DF90(this);
			}

			_extern void _sub_10C7E010(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const);
			void CWebModDownloadSingleScreen::OnUpdate() // 0x10C7E010
			{
				mangled_x86(MANGLED_TODO, "?OnUpdate@CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAEXXZ");
				// Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const this;
				todo("implement");
				_sub_10C7E010(this);
			}

			_extern void _sub_10C7CE90();
			void Init() // 0x10C7CE90
			{
				mangled_x86(MANGLED_TODO, "?Init@WebServerModBrowser@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				todo("implement");
				_sub_10C7CE90();
			}

			extern CWebModDownloadSingleScreen* _sub_10C7B4E0(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const);
			_inline CWebModDownloadSingleScreen::CWebModDownloadSingleScreen() // 0x10C7B4E0
			{
				mangled_x86(MANGLED_TODO, "??0CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@QAE@XZ");
				// Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const this;
				compiler_generated();
				todo("implement");
				_sub_10C7B4E0(this);
			}
		}
	}
}

extern IModBrowserModDownloadUI* _sub_10C7B5E0(IModBrowserModDownloadUI *const);
_inline IModBrowserModDownloadUI::IModBrowserModDownloadUI() // 0x10C7B5E0
{
	mangled_x86(MANGLED_TODO, "??0IModBrowserModDownloadUI@@QAE@XZ");
	// IModBrowserModDownloadUI *const this;
	compiler_generated();
	todo("implement");
	_sub_10C7B5E0(this);
}

extern SModBrowserState* _sub_10C7B610(SModBrowserState *const);
_inline SModBrowserState::SModBrowserState() // 0x10C7B610
{
	mangled_x86(MANGLED_TODO, "??0SModBrowserState@@QAE@XZ");
	// SModBrowserState *const this;
	compiler_generated();
	todo("implement");
	_sub_10C7B610(this);
}

extern SModBrowserState::SRequestedMod* _sub_10C7B6A0(SModBrowserState::SRequestedMod *const);
_inline SModBrowserState::SRequestedMod::SRequestedMod() // 0x10C7B6A0
{
	mangled_x86(MANGLED_TODO, "??0SRequestedMod@SModBrowserState@@QAE@XZ");
	// SModBrowserState::SRequestedMod *const this;
	compiler_generated();
	todo("implement");
	_sub_10C7B6A0(this);
}

namespace Web
{
	namespace Ui
	{
		extern WebScreen* _sub_10C7B770(Web::Ui::WebScreen *const);
		_inline WebScreen::WebScreen() // 0x10C7B770
		{
			mangled_x86(MANGLED_TODO, "??0WebScreen@Ui@Web@@QAE@XZ");
			// Web::Ui::WebScreen *const this;
			compiler_generated();
			todo("implement");
			_sub_10C7B770(this);
		}
	}
}

namespace Web
{
	namespace Ui
	{
		namespace WebServerModBrowser
		{
			_extern void _sub_10C7B8A0(Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const);
			_inline CWebModDownloadSingleScreen::~CWebModDownloadSingleScreen() // 0x10C7B8A0
			{
				mangled_x86(MANGLED_TODO, "??1CWebModDownloadSingleScreen@WebServerModBrowser@Ui@Web@@UAE@XZ");
				// Web::Ui::WebServerModBrowser::CWebModDownloadSingleScreen *const this;
				compiler_generated();
				todo("implement");
				_sub_10C7B8A0(this);
			}
		}
	}
}

/* ---------- private code */

_extern void _sub_10C7D210(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
void NotifyDownloadStateChanged(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &fromState, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &toState) // 0x10C7D210
{
	// `anonymous-namespace'::NotifyDownloadStateChanged
	// static ...; // 0x10C7D3A0
	// static ...; // 0x10C7D388
	// static ...; // 0x10C7D380
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &fromState;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &toState;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buff;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	todo("implement");
	_sub_10C7D210(fromState, toState);
}

_extern void _sub_10C7D420(DownloadStatusInfo const &);
void NotifyDownloadStatus(DownloadStatusInfo const &info) // 0x10C7D420
{
	// `anonymous-namespace'::NotifyDownloadStatus
	// static ...; // 0x10C7D6D7
	// static ...; // 0x10C7D6D0
	// static ...; // 0x10C7D6B8
	// static ...; // 0x10C7D6B0
	// DownloadStatusInfo const &info;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buff;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	todo("implement");
	_sub_10C7D420(info);
}

_extern void _sub_10C7D030(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
void NotifyDownloadError(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &reason) // 0x10C7D030
{
	// `anonymous-namespace'::NotifyDownloadError
	// static ...; // 0x10C7D1AB
	// static ...; // 0x10C7D1A4
	// static ...; // 0x10C7D18C
	// static ...; // 0x10C7D184
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &reason;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buff;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	todo("implement");
	_sub_10C7D030(reason);
}

extern DownloadStatusInfo* _sub_10C7B590(DownloadStatusInfo *const);
_inline DownloadStatusInfo::DownloadStatusInfo() // 0x10C7B590
{
	// `anonymous-namespace'::DownloadStatusInfo::DownloadStatusInfo
	// DownloadStatusInfo *const this;
	compiler_generated();
	todo("implement");
	_sub_10C7B590(this);
}

_extern void _sub_10C7B930(DownloadStatusInfo *const);
_inline DownloadStatusInfo::~DownloadStatusInfo() // 0x10C7B930
{
	// `anonymous-namespace'::DownloadStatusInfo::~DownloadStatusInfo
	// DownloadStatusInfo *const this;
	compiler_generated();
	todo("implement");
	_sub_10C7B930(this);
}
