/* ---------- headers */

#include "Web/Bridge/WebRendererQueryHandler.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Magnets.hpp"
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
#include "Utils/NameValueTable.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/WebRenderHandlerGpu.hpp"

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
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <ios>
#include <iosfwd>
#include <iterator>
#include <limits>
#include <list>
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
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct CefStringTraitsUTF16;
namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			class WebRendererQueryHandler;
		}
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

namespace Web {}
using namespace ::Web;
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

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			extern WebRendererQueryHandler* _sub_10C6F220(Web::Browser::Bridge::WebRendererQueryHandler *const);
			WebRendererQueryHandler::WebRendererQueryHandler() // 0x10C6F220
			{
				mangled_x86(MANGLED_TODO, "??0WebRendererQueryHandler@Bridge@Browser@Web@@QAE@XZ");
				// Web::Browser::Bridge::WebRendererQueryHandler *const this;
				todo("implement");
				_sub_10C6F220(this);
			}

			_extern bool _sub_10C71290(Web::Browser::Bridge::WebRendererQueryHandler *const, scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, long long, CefStringBase<CefStringTraitsUTF16> const &, bool, scoped_refptr<CefMessageRouterBrowserSide::Callback>);
			bool WebRendererQueryHandler::OnQuery(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, long long queryId, CefStringBase<CefStringTraitsUTF16> const &request, bool persistent, scoped_refptr<CefMessageRouterBrowserSide::Callback> callback) // 0x10C71290
			{
				mangled_x86(MANGLED_TODO, "?OnQuery@WebRendererQueryHandler@Bridge@Browser@Web@@UAE_NV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@_JABV?$CefStringBase@UCefStringTraitsUTF16@@@@_NV?$scoped_refptr@VCallback@CefMessageRouterBrowserSide@@@@@Z");
				// static ...; // 0x10C71BE4
				// Web::Browser::Bridge::WebRendererQueryHandler *const this;
				// scoped_refptr<CefBrowser> browser;
				// scoped_refptr<CefFrame> frame;
				// long long queryId;
				// CefStringBase<CefStringTraitsUTF16> const &request;
				// bool persistent;
				// scoped_refptr<CefMessageRouterBrowserSide::Callback> callback;
				// Web::Browser::Bridge::WebRendererQueryHandler::PendingQuery *query;
				// char const *method;
				// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> &json;
				// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::function<enum Web::Browser::Bridge::QueryError __cdecl(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &,std::basic_string<char,std::char_traits<char>,std::allocator<char> > *)> > > > > methodIt;
				// rapidjson::GenericMemberIterator<0,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > s_MethodMember;
				// rapidjson::GenericMemberIterator<0,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > argsMember;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > s_RequestStr;
				// function call : void (__int32, CefStringBase<CefStringTraitsUTF16> const &)
				// function call : void (__int32, CefStringBase<CefStringTraitsUTF16> const &)
				// function call : void (__int32, CefStringBase<CefStringTraitsUTF16> const &)
				// function call : void (__int32, CefStringBase<CefStringTraitsUTF16> const &)
				// function call : void (__int32, CefStringBase<CefStringTraitsUTF16> const &)
				// function call : void (__int32, CefStringBase<CefStringTraitsUTF16> const &)
				todo("implement");
				bool __result = _sub_10C71290(this, browser, frame, queryId, request, persistent, callback);
				return __result;
			}

			_extern void _sub_10C70100(Web::Browser::Bridge::WebRendererQueryHandler::PendingQuery *const);
			_inline WebRendererQueryHandler::PendingQuery::~PendingQuery() // 0x10C70100
			{
				mangled_x86(MANGLED_TODO, "??1PendingQuery@WebRendererQueryHandler@Bridge@Browser@Web@@QAE@XZ");
				// Web::Browser::Bridge::WebRendererQueryHandler::PendingQuery *const this;
				compiler_generated();
				todo("implement");
				_sub_10C70100(this);
			}

			_extern void _sub_10C70170(Web::Browser::Bridge::WebRendererQueryHandler *const);
			_inline WebRendererQueryHandler::~WebRendererQueryHandler() // 0x10C70170
			{
				mangled_x86(MANGLED_TODO, "??1WebRendererQueryHandler@Bridge@Browser@Web@@UAE@XZ");
				// Web::Browser::Bridge::WebRendererQueryHandler *const this;
				compiler_generated();
				todo("implement");
				_sub_10C70170(this);
			}

			_extern void _sub_10C71F40(Web::Browser::Bridge::WebRendererQueryHandler *const, scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, long long);
			void WebRendererQueryHandler::OnQueryCanceled(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, long long queryId) // 0x10C71F40
			{
				mangled_x86(MANGLED_TODO, "?OnQueryCanceled@WebRendererQueryHandler@Bridge@Browser@Web@@UAEXV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@_J@Z");
				// long long queryId;
				todo("implement");
				_sub_10C71F40(this, browser, frame, queryId);
			}

			_extern void _sub_10C70ED0(Web::Browser::Bridge::WebRendererQueryHandler *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::function<enum Web::Browser::Bridge::QueryError __cdecl(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &,std::basic_string<char,std::char_traits<char>,std::allocator<char> > *)> const &);
			void WebRendererQueryHandler::AddMethod(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, std::function<enum Web::Browser::Bridge::QueryError __cdecl(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &,std::basic_string<char,std::char_traits<char>,std::allocator<char> > *)> const &method) // 0x10C70ED0
			{
				mangled_x86(MANGLED_TODO, "?AddMethod@WebRendererQueryHandler@Bridge@Browser@Web@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV?$function@$$A6A?AW4QueryError@Bridge@Browser@Web@@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z@6@@Z");
				// std::function<enum Web::Browser::Bridge::QueryError __cdecl(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &,std::basic_string<char,std::char_traits<char>,std::allocator<char> > *)> const &method;
				todo("implement");
				_sub_10C70ED0(this, name, method);
			}

			_extern void _sub_10C721A0(Web::Browser::Bridge::WebRendererQueryHandler *const);
			void WebRendererQueryHandler::Update() // 0x10C721A0
			{
				mangled_x86(MANGLED_TODO, "?Update@WebRendererQueryHandler@Bridge@Browser@Web@@QAEXXZ");
				// static ...; // 0x10C723D5
				// static ...; // 0x10C723CF
				// static ...; // 0x10C723C8
				// static ...; // 0x10C723A4
				// static ...; // 0x10C7239C
				// Web::Browser::Bridge::WebRendererQueryHandler *const this;
				// Web::Browser::Bridge::WebRendererQueryHandler::PendingQuery *pendingQuery;
				{
					// std::unique_ptr<Web::Browser::Bridge::WebRendererQueryHandler::PendingQuery,std::default_delete<Web::Browser::Bridge::WebRendererQueryHandler::PendingQuery> > query;
					// Web::Browser::Bridge::QueryError errorCode;
					// std::basic_string<char,std::char_traits<char>,std::allocator<char> > result;
				}
				// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
				// function call : void (__int32, CefStringBase<CefStringTraitsUTF16> const &)
				todo("implement");
				_sub_10C721A0(this);
			}

			extern WebRendererQueryHandler::PendingQuery* _sub_10C6F190(Web::Browser::Bridge::WebRendererQueryHandler::PendingQuery *const);
			_inline WebRendererQueryHandler::PendingQuery::PendingQuery() // 0x10C6F190
			{
				mangled_x86(MANGLED_TODO, "??0PendingQuery@WebRendererQueryHandler@Bridge@Browser@Web@@QAE@XZ");
				// Web::Browser::Bridge::WebRendererQueryHandler::PendingQuery *const this;
				compiler_generated();
				todo("implement");
				_sub_10C6F190(this);
			}
		}
	}
}

/* ---------- private code */
