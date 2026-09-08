/* ---------- headers */

#include "Web/WebEmblemSchemeHandler.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/game/player_appearance.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Web/WebEmblemResourceHandler.hpp"

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
#include <ios>
#include <iosfwd>
#include <iterator>
#include <limits>
#include <map>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

struct CefStringTraitsUTF16;
namespace Web
{
	namespace Browser
	{
		class WebEmblemResourceHandler;
		class WebEmblemSchemeHandlerFactory;
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

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern scoped_refptr<CefResourceHandler> _sub_10CB67C0(Web::Browser::WebEmblemSchemeHandlerFactory *const, scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, CefStringBase<CefStringTraitsUTF16> const &, scoped_refptr<CefRequest>);
namespace Web
{
	namespace Browser
	{
		scoped_refptr<CefResourceHandler> WebEmblemSchemeHandlerFactory::Create(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, CefStringBase<CefStringTraitsUTF16> const &scheme, scoped_refptr<CefRequest> request) // 0x10CB67C0
		{
			mangled_x86(MANGLED_TODO, "?Create@WebEmblemSchemeHandlerFactory@Browser@Web@@MAE?AV?$scoped_refptr@VCefResourceHandler@@@@V?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@ABV?$CefStringBase@UCefStringTraitsUTF16@@@@V?$scoped_refptr@VCefRequest@@@@@Z");
			// scoped_refptr<CefRequest> request;
			todo("implement");
			scoped_refptr<CefResourceHandler> __result = _sub_10CB67C0(this, browser, frame, scheme, request);
			return __result;
		}

		// mangled_x86(MANGLED_DEFAULT, "??0WebEmblemResourceHandler@Browser@Web@@QAE@XZ"); no body to assert in
		_inline WebEmblemResourceHandler::WebEmblemResourceHandler() = default; // 0x10CB61A0

		_inline WebEmblemResourceHandler::~WebEmblemResourceHandler() // 0x10CB6470
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1WebEmblemResourceHandler@Browser@Web@@UAE@XZ");
			// __shifted(Web::Browser::WebEmblemResourceHandler, 32);
			// Web::Browser::WebEmblemResourceHandler *const this;

			compiler_generated();
		}
	}
}

/* ---------- private code */
