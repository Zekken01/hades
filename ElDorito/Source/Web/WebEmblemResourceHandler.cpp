/* ---------- headers */

#include "Web/WebEmblemResourceHandler.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/game/player_appearance.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Player/PlayerEmblemRenderer.hpp"
#include "Utils/NameValueTable.hpp"

#include <base/cef_atomic_ref_count.h>
#include <base/cef_lock.h>
#include <base/cef_logging.h>
#include <base/cef_platform_thread.h>
#include <base/cef_ref_counted.h>
#include <base/cef_scoped_refptr.h>
#include <base/cef_thread_checker.h>
#include <base/internal/cef_lock_impl.h>
#include <cef_base.h>
#include <cef_devtools_message_observer.h>
#include <cef_extension_handler.h>
#include <cef_resource_handler.h>
#include <internal/cef_string_wrappers.h>
#include <internal/cef_types_wrappers.h>
#include <internal/cef_win.h>
#include <wrapper/cef_stream_resource_handler.h>

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
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

class CefCallback;
struct CefStringTraitsUTF16;
struct s_player_emblem_configuration;
namespace Player
{
	namespace Emblems
	{
		class IPlayerEmblemRenderCallbacks;
		class IPlayerEmblemStream;
		struct PlayerEmblemRenderMetadata;
	}
}
namespace Web
{
	namespace Browser
	{
		class WebEmblemRenderHandler;
		class WebEmblemResourceHandler;
	}
}

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

namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace Emblems {}
	using namespace Player::Emblems;
}

namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Browser {}
	using namespace Web::Browser;
}

/* ---------- constants */

/* ---------- definitions */

// Web::Browser::WebEmblemRenderHandler is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		extern WebEmblemRenderHandler* _sub_10C826F0(Web::Browser::WebEmblemRenderHandler *const, scoped_refptr<CefCallback>);
		_inline WebEmblemRenderHandler::WebEmblemRenderHandler(scoped_refptr<CefCallback> callback) // 0x10C826F0
		{
			mangled_x86(MANGLED_TODO, "??0WebEmblemRenderHandler@Browser@Web@@QAE@V?$scoped_refptr@VCefCallback@@@@@Z");
			// scoped_refptr<CefCallback> callback;
			todo("implement");
			_sub_10C826F0(this, callback);
		}

		_extern void _sub_10C83020(Web::Browser::WebEmblemRenderHandler *const);
		_inline WebEmblemRenderHandler::~WebEmblemRenderHandler() // 0x10C83020
		{
			mangled_x86(MANGLED_TODO, "??1WebEmblemRenderHandler@Browser@Web@@UAE@XZ");
			// Web::Browser::WebEmblemRenderHandler *const this;
			compiler_generated();
			todo("implement");
			_sub_10C83020(this);
		}
	}
}

namespace Player
{
	namespace Emblems
	{
		extern PlayerEmblemRenderMetadata &_sub_10C832C0(Player::Emblems::PlayerEmblemRenderMetadata *const, Player::Emblems::PlayerEmblemRenderMetadata const &);
		_inline Player::Emblems::PlayerEmblemRenderMetadata &PlayerEmblemRenderMetadata::operator=(Player::Emblems::PlayerEmblemRenderMetadata const &__that) // 0x10C832C0
		{
			mangled_x86(MANGLED_TODO, "??4PlayerEmblemRenderMetadata@Emblems@Player@@QAEAAU012@ABU012@@Z");
			// Player::Emblems::PlayerEmblemRenderMetadata const &__that;
			compiler_generated();
			todo("implement");
			Player::Emblems::PlayerEmblemRenderMetadata & __result = _sub_10C832C0(this, __that);
			return __result;
		}
	}
}

namespace Web
{
	namespace Browser
	{
		_inline void WebEmblemRenderHandler::OnRenderComplete() // 0x10C842D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnRenderComplete@WebEmblemRenderHandler@Browser@Web@@UAEXXZ");
			// Web::Browser::WebEmblemRenderHandler *const this;
		}

		_extern void _sub_10C842F0(Web::Browser::WebEmblemRenderHandler *const);
		_inline void WebEmblemRenderHandler::OnRenderDataAvailable() // 0x10C842F0
		{
			mangled_x86(MANGLED_TODO, "?OnRenderDataAvailable@WebEmblemRenderHandler@Browser@Web@@UAEXXZ");
			// Web::Browser::WebEmblemRenderHandler *const this;
			// function call : void ()
			todo("implement");
			_sub_10C842F0(this);
		}

		_extern void _sub_10C84DD0(Web::Browser::WebEmblemRenderHandler *const, scoped_refptr<CefCallback>);
		_inline void WebEmblemRenderHandler::SetCefContinuation(scoped_refptr<CefCallback> callback) // 0x10C84DD0
		{
			mangled_x86(MANGLED_TODO, "?SetCefContinuation@WebEmblemRenderHandler@Browser@Web@@QAEXV?$scoped_refptr@VCefCallback@@@@@Z");
			// scoped_refptr<CefCallback> callback;
			todo("implement");
			_sub_10C84DD0(this, callback);
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const _sub_10C83F20(Web::Browser::WebEmblemRenderHandler const *const);
namespace Web
{
	namespace Browser
	{
		_inline std::basic_string<char,std::char_traits<char>,std::allocator<char> > const WebEmblemRenderHandler::GetMimeType() const // 0x10C83F20
		{
			mangled_x86(MANGLED_TODO, "?GetMimeType@WebEmblemRenderHandler@Browser@Web@@QBE?BV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
			// Web::Browser::WebEmblemRenderHandler const *const this;
			todo("implement");
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > const __result = _sub_10C83F20((Web::Browser::WebEmblemRenderHandler const *)this);
			return __result;
		}

		_extern long long _sub_10C83EF0(Web::Browser::WebEmblemRenderHandler const *const);
		_inline long long WebEmblemRenderHandler::GetLength() const // 0x10C83EF0
		{
			mangled_x86(MANGLED_TODO, "?GetLength@WebEmblemRenderHandler@Browser@Web@@QBE_JXZ");
			// Web::Browser::WebEmblemRenderHandler const *const this;
			todo("implement");
			long long __result = _sub_10C83EF0((Web::Browser::WebEmblemRenderHandler const *)this);
			return __result;
		}
	}
}

namespace Player
{
	namespace Emblems
	{
		extern IPlayerEmblemRenderCallbacks* _sub_10C826C0(Player::Emblems::IPlayerEmblemRenderCallbacks *const);
		_inline IPlayerEmblemRenderCallbacks::IPlayerEmblemRenderCallbacks() // 0x10C826C0
		{
			mangled_x86(MANGLED_TODO, "??0IPlayerEmblemRenderCallbacks@Emblems@Player@@QAE@XZ");
			// Player::Emblems::IPlayerEmblemRenderCallbacks *const this;
			compiler_generated();
			todo("implement");
			_sub_10C826C0(this);
		}
	}
}

namespace Web
{
	namespace Browser
	{
		_extern bool _sub_10C84460(Web::Browser::WebEmblemResourceHandler *const, scoped_refptr<CefRequest>, scoped_refptr<CefCallback>);
		bool WebEmblemResourceHandler::ProcessRequest(scoped_refptr<CefRequest> request, scoped_refptr<CefCallback> callback) // 0x10C84460
		{
			mangled_x86(MANGLED_TODO, "?ProcessRequest@WebEmblemResourceHandler@Browser@Web@@UAE_NV?$scoped_refptr@VCefRequest@@@@V?$scoped_refptr@VCefCallback@@@@@Z");
			// static ...; // 0x10C84933
			// static ...; // 0x10C8492F
			// static ...; // 0x10C84928
			// static ...; // 0x10C848EC
			// static ...; // 0x10C848E4
			// Web::Browser::WebEmblemResourceHandler *const this;
			// scoped_refptr<CefRequest> request;
			// scoped_refptr<CefCallback> callback;
			// std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<CefStringBase<CefStringTraitsUTF16> const ,CefStringBase<CefStringTraitsUTF16> > > > > it;
			// s_player_emblem_configuration config;
			// std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16>,std::less<CefStringBase<CefStringTraitsUTF16> >,std::allocator<std::pair<CefStringBase<CefStringTraitsUTF16> const ,CefStringBase<CefStringTraitsUTF16> > > > requestHeaders;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > url;
			// CefStringBase<CefStringTraitsUTF16> origin;
			// function call : void (std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16>,std::less<CefStringBase<CefStringTraitsUTF16> >,std::allocator<std::pair<CefStringBase<CefStringTraitsUTF16> const ,CefStringBase<CefStringTraitsUTF16> > > > &)
			// function call : CefStringBase<CefStringTraitsUTF16> ()
			// function call : void ()
			todo("implement");
			bool __result = _sub_10C84460(this, request, callback);
			return __result;
		}

		_extern void _sub_10C83FA0(Web::Browser::WebEmblemResourceHandler *const, scoped_refptr<CefResponse>, long long &, CefStringBase<CefStringTraitsUTF16> &);
		void WebEmblemResourceHandler::GetResponseHeaders(scoped_refptr<CefResponse> response, long long &response_length, CefStringBase<CefStringTraitsUTF16> &redirectUrl) // 0x10C83FA0
		{
			mangled_x86(MANGLED_TODO, "?GetResponseHeaders@WebEmblemResourceHandler@Browser@Web@@UAEXV?$scoped_refptr@VCefResponse@@@@AA_JAAV?$CefStringBase@UCefStringTraitsUTF16@@@@@Z");
			// CefStringBase<CefStringTraitsUTF16> &redirectUrl;
			// function call : void (std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16>,std::less<CefStringBase<CefStringTraitsUTF16> >,std::allocator<std::pair<CefStringBase<CefStringTraitsUTF16> const ,CefStringBase<CefStringTraitsUTF16> > > > const &)
			// function call : void (__int32)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (__int32)
			todo("implement");
			_sub_10C83FA0(this, response, response_length, redirectUrl);
		}

		_extern bool _sub_10C84A90(Web::Browser::WebEmblemResourceHandler *const, void *, __int32, __int32 &, scoped_refptr<CefCallback>);
		bool WebEmblemResourceHandler::ReadResponse(void *data_out, __int32 bytes_to_read, __int32 &bytes_read, scoped_refptr<CefCallback> callback) // 0x10C84A90
		{
			mangled_x86(MANGLED_TODO, "?ReadResponse@WebEmblemResourceHandler@Browser@Web@@UAE_NPAXHAAHV?$scoped_refptr@VCefCallback@@@@@Z");
			// scoped_refptr<CefCallback> callback;
			// Player::Emblems::IPlayerEmblemStream *stream;
			// function call : bool (void *, __int32, __int32 *)
			// function call : void ()
			todo("implement");
			bool __result = _sub_10C84A90(this, data_out, bytes_to_read, bytes_read, callback);
			return __result;
		}

		void WebEmblemResourceHandler::Cancel() // 0x10C83E20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Cancel@WebEmblemResourceHandler@Browser@Web@@UAEXXZ");
			// Web::Browser::WebEmblemResourceHandler *const this;
		}
	}
}

/* ---------- private code */
