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
namespace
{
	struct DownloadStatusInfo;
	class ModChangeListener;
}

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

namespace
{
	struct DownloadStatusInfo
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
	};
	static_assert(sizeof(DownloadStatusInfo) == 288, "Invalid DownloadStatusInfo size");

	class ModChangeListener :
		public IModListener
	{
	private:
		virtual void OnModChanged(EModIndex, IMod *);
	public:
		ModChangeListener(ModChangeListener &); /* compiler_generated() */
		ModChangeListener(ModChangeListener const &); /* compiler_generated() */
		ModChangeListener(); /* compiler_generated() */
		virtual ~ModChangeListener(); /* compiler_generated() */
		ModChangeListener &operator=(ModChangeListener &); /* compiler_generated() */
		ModChangeListener &operator=(ModChangeListener const &); /* compiler_generated() */
	};
	static_assert(sizeof(ModChangeListener) == 4, "Invalid ModChangeListener size");
}
// Web::Ui::WebMods::CWebModDownloadScreen is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

//class Web::Ui::WebMods::CWebModDownloadScreen::OnCreate::__l2::<lambda_1>
//{
//public:
//	Web::Browser::Bridge::QueryError operator()(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > *) const;
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

/* ---------- globals */

namespace Web
{
	namespace Ui
	{
		namespace WebMods
		{
			extern std::shared_ptr<Web::Ui::WebMods::CWebModDownloadScreen> screen; // 0x1247EDD0
		}
	}
}

/* ---------- private variables */

namespace
{
	extern bool screenVisible; // 0x1247EDCC
}
/* ---------- public code */

extern std::shared_ptr<IServerConnectModDownloadUI> _sub_10CAD340();
namespace Web
{
	namespace Ui
	{
		namespace WebMods
		{
			std::shared_ptr<IServerConnectModDownloadUI> GetDownloadUI() // 0x10CAD340
			{
				mangled_x86(MANGLED_TODO, "?GetDownloadUI@WebMods@Ui@Web@@YA?AV?$shared_ptr@VIServerConnectModDownloadUI@@@std@@XZ");
				// procedure flags: nofpo
				todo("implement");
				std::shared_ptr<IServerConnectModDownloadUI> __result = _sub_10CAD340();
				return __result;
			}

			_extern void _sub_10CAEDF0(IServerConnectModDownloadUI * const, std::function<void __cdecl(void)>);
			void CWebModDownloadScreen::SetConfirmCallback(std::function<void __cdecl(void)> callback) // 0x10CAEDF0
			{
				mangled_x86(MANGLED_TODO, "?SetConfirmCallback@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXV?$function@$$A6AXXZ@std@@@Z");
				// __shifted(Web::Ui::WebMods::CWebModDownloadScreen, 4);
				// std::function<void __cdecl(void)> callback;
				todo("implement");
				_sub_10CAEDF0((IServerConnectModDownloadUI *)this, callback);
			}

			_extern void _sub_10CAEF50(IServerConnectModDownloadUI * const, std::function<void __cdecl(void)>);
			void CWebModDownloadScreen::SetRetryCallback(std::function<void __cdecl(void)> callback) // 0x10CAEF50
			{
				mangled_x86(MANGLED_TODO, "?SetRetryCallback@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXV?$function@$$A6AXXZ@std@@@Z");
				// __shifted(Web::Ui::WebMods::CWebModDownloadScreen, 4);
				// std::function<void __cdecl(void)> callback;
				todo("implement");
				_sub_10CAEF50((IServerConnectModDownloadUI *)this, callback);
			}

			_extern void _sub_10CAED40(IServerConnectModDownloadUI * const, std::function<void __cdecl(void)>);
			void CWebModDownloadScreen::SetCancelCallback(std::function<void __cdecl(void)> callback) // 0x10CAED40
			{
				mangled_x86(MANGLED_TODO, "?SetCancelCallback@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXV?$function@$$A6AXXZ@std@@@Z");
				// __shifted(Web::Ui::WebMods::CWebModDownloadScreen, 4);
				// std::function<void __cdecl(void)> callback;
				todo("implement");
				_sub_10CAED40((IServerConnectModDownloadUI *)this, callback);
			}

			_extern void _sub_10CAEEA0(IServerConnectModDownloadUI * const, std::function<void __cdecl(void)>);
			void CWebModDownloadScreen::SetJoinServerCallback(std::function<void __cdecl(void)> callback) // 0x10CAEEA0
			{
				mangled_x86(MANGLED_TODO, "?SetJoinServerCallback@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXV?$function@$$A6AXXZ@std@@@Z");
				// __shifted(Web::Ui::WebMods::CWebModDownloadScreen, 4);
				// std::function<void __cdecl(void)> callback;
				todo("implement");
				_sub_10CAEEA0((IServerConnectModDownloadUI *)this, callback);
			}

			_extern void _sub_10CAE620(IServerConnectModDownloadUI * const);
			void CWebModDownloadScreen::OnDownloadStart() // 0x10CAE620
			{
				mangled_x86(MANGLED_TODO, "?OnDownloadStart@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXXZ");
				// __shifted(Web::Ui::WebMods::CWebModDownloadScreen, 4);
				// Web::Ui::WebMods::CWebModDownloadScreen *const this;
				todo("implement");
				_sub_10CAE620((IServerConnectModDownloadUI *)this);
			}

			_extern void _sub_10CAE020(IServerConnectModDownloadUI * const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
			void CWebModDownloadScreen::OnDownloadFailed(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &message) // 0x10CAE020
			{
				mangled_x86(MANGLED_TODO, "?OnDownloadFailed@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
				// __shifted(Web::Ui::WebMods::CWebModDownloadScreen, 4);
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &message;
				todo("implement");
				_sub_10CAE020((IServerConnectModDownloadUI *)this, message);
			}

			_extern void _sub_10CAE140(IServerConnectModDownloadUI * const);
			void CWebModDownloadScreen::OnDownloadFinalizing() // 0x10CAE140
			{
				mangled_x86(MANGLED_TODO, "?OnDownloadFinalizing@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXXZ");
				// __shifted(Web::Ui::WebMods::CWebModDownloadScreen, 4);
				// Web::Ui::WebMods::CWebModDownloadScreen *const this;
				todo("implement");
				_sub_10CAE140((IServerConnectModDownloadUI *)this);
			}

			_extern void _sub_10CAE240(IServerConnectModDownloadUI * const, SServerConnectState const &);
			void CWebModDownloadScreen::OnDownloadFinished(SServerConnectState const &state) // 0x10CAE240
			{
				mangled_x86(MANGLED_TODO, "?OnDownloadFinished@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXABUSServerConnectState@@@Z");
				// __shifted(Web::Ui::WebMods::CWebModDownloadScreen, 4);
				// static ...; // 0x10CAE438
				// static ...; // 0x10CAE420
				// static ...; // 0x10CAE418
				// Web::Ui::WebMods::CWebModDownloadScreen *const this;
				// SServerConnectState const &state;
				// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buff;
				// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
				todo("implement");
				_sub_10CAE240((IServerConnectModDownloadUI *)this, state);
			}

			_extern void _sub_10CAD3B0(IServerConnectModDownloadUI * const);
			void CWebModDownloadScreen::Hide() // 0x10CAD3B0
			{
				mangled_x86(MANGLED_TODO, "?Hide@CWebModDownloadScreen@WebMods@Ui@Web@@UAEXXZ");
				// __shifted(Web::Ui::WebMods::CWebModDownloadScreen, 4);
				// Web::Ui::WebMods::CWebModDownloadScreen *const this;
				todo("implement");
				_sub_10CAD3B0((IServerConnectModDownloadUI *)this);
			}

			_extern void _sub_10CAE720();
			void OnGameInputUpdated() // 0x10CAE720
			{
				mangled_x86(MANGLED_TODO, "?OnGameInputUpdated@WebMods@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				{
					// Blam::Network::Session *session;
				}
				// function call : bool (*const)()
				todo("implement");
				_sub_10CAE720();
			}

			_extern void _sub_10CAD540();
			void Init() // 0x10CAD540
			{
				mangled_x86(MANGLED_TODO, "?Init@WebMods@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				// function call : void (IModListener *)
				todo("implement");
				_sub_10CAD540();
			}

			extern CWebModDownloadScreen* _sub_10CAC810(Web::Ui::WebMods::CWebModDownloadScreen *const);
			_inline CWebModDownloadScreen::CWebModDownloadScreen() // 0x10CAC810
			{
				mangled_x86(MANGLED_TODO, "??0CWebModDownloadScreen@WebMods@Ui@Web@@QAE@XZ");
				// Web::Ui::WebMods::CWebModDownloadScreen *const this;
				compiler_generated();
				todo("implement");
				_sub_10CAC810(this);
			}
		}
	}
}

extern IServerConnectModDownloadUI* _sub_10CAC910(IServerConnectModDownloadUI *const);
_inline IServerConnectModDownloadUI::IServerConnectModDownloadUI() // 0x10CAC910
{
	mangled_x86(MANGLED_TODO, "??0IServerConnectModDownloadUI@@QAE@XZ");
	// IServerConnectModDownloadUI *const this;
	compiler_generated();
	todo("implement");
	_sub_10CAC910(this);
}

namespace Web
{
	namespace Ui
	{
		namespace WebMods
		{
			_extern void _sub_10CACA50(Web::Ui::WebMods::CWebModDownloadScreen *const);
			_inline CWebModDownloadScreen::~CWebModDownloadScreen() // 0x10CACA50
			{
				mangled_x86(MANGLED_TODO, "??1CWebModDownloadScreen@WebMods@Ui@Web@@UAE@XZ");
				// Web::Ui::WebMods::CWebModDownloadScreen *const this;
				compiler_generated();
				todo("implement");
				_sub_10CACA50(this);
			}
		}
	}
}

extern SServerConnectState::SRequiredMod &_sub_10CACC30(SServerConnectState::SRequiredMod *const, SServerConnectState::SRequiredMod const &);
_inline SServerConnectState::SRequiredMod &SServerConnectState::SRequiredMod::operator=(SServerConnectState::SRequiredMod const &__that) // 0x10CACC30
{
	mangled_x86(MANGLED_TODO, "??4SRequiredMod@SServerConnectState@@QAEAAU01@ABU01@@Z");
	// SServerConnectState::SRequiredMod const &__that;
	compiler_generated();
	todo("implement");
	SServerConnectState::SRequiredMod & __result = _sub_10CACC30(this, __that);
	return __result;
}

/* ---------- private code */
