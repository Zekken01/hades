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
			WebRendererQueryHandler::WebRendererQueryHandler() : m_Queries(1024) /* hades-mem-init:  */ // 0x10C6F220
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "??0WebRendererQueryHandler@Bridge@Browser@Web@@QAE@XZ");
				// Web::Browser::Bridge::WebRendererQueryHandler *const this;
			}

			bool WebRendererQueryHandler::OnQuery(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, long long queryId, CefStringBase<CefStringTraitsUTF16> const &request, bool persistent, scoped_refptr<CefMessageRouterBrowserSide::Callback> callback) // 0x10C71290
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnQuery@WebRendererQueryHandler@Bridge@Browser@Web@@UAE_NV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@_JABV?$CefStringBase@UCefStringTraitsUTF16@@@@_NV?$scoped_refptr@VCallback@CefMessageRouterBrowserSide@@@@@Z");
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
				// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<std::string const ,std::function<enum Web::Browser::Bridge::QueryError __cdecl(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &,std::string *)> > > > > methodIt;
				// rapidjson::GenericMemberIterator<0,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > s_MethodMember;
				// rapidjson::GenericMemberIterator<0,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > argsMember;
				// std::string s_RequestStr;
				// function call : void (__int32, CefStringBase<CefStringTraitsUTF16> const &)
				// function call : void (__int32, CefStringBase<CefStringTraitsUTF16> const &)
				// function call : void (__int32, CefStringBase<CefStringTraitsUTF16> const &)
				// function call : void (__int32, CefStringBase<CefStringTraitsUTF16> const &)
				// function call : void (__int32, CefStringBase<CefStringTraitsUTF16> const &)
				// function call : void (__int32, CefStringBase<CefStringTraitsUTF16> const &)

				PendingQuery *query = new PendingQuery();
				auto &json = query->m_Json;
				auto s_RequestStr = request.ToString();
				json.Parse(s_RequestStr.c_str());
				if (json.HasParseError())
				{
					callback->Failure(QueryError_BadQuery, "Bad query: Failed to parse JSON");
					delete query;
					return true;
				}
				auto s_MethodMember = json.FindMember("method");
				if (s_MethodMember == json.MemberEnd())
				{
					callback->Failure(QueryError_BadQuery, "Bad query: A \"method\" value is required");
					delete query;
					return true;
				}
				if (!s_MethodMember->value.IsString())
				{
					callback->Failure(QueryError_BadQuery, "Bad query: \"method\" must be a string");
					delete query;
					return true;
				}
				auto method = s_MethodMember->value.GetString();
				auto methodIt = m_Methods.find(method);
				if (methodIt == m_Methods.end())
				{
					callback->Failure(QueryError_UnsupportedMethod, "Unsupported method: \"" + std::string(method) + "\"");
					delete query;
					return true;
				}
				query->m_Method = methodIt->second;
				auto argsMember = json.FindMember("args");
				if (argsMember == json.MemberEnd())
				{
					callback->Failure(QueryError_BadQuery, "Bad query: An \"args\" value is required");
					delete query;
					return true;
				}
				if (!argsMember->value.IsObject())
				{
					callback->Failure(QueryError_BadQuery, "Bad query: \"args\" must be an object");
					delete query;
					return true;
				}
				query->m_Args = &argsMember->value;
				query->m_Callback = callback;
				m_Queries.push(query);
				return true;
			}

			// mangled_x86(MANGLED_DEFAULT, "??1PendingQuery@WebRendererQueryHandler@Bridge@Browser@Web@@QAE@XZ"); no body to assert in
			_inline WebRendererQueryHandler::PendingQuery::~PendingQuery() = default; // 0x10C70100

			void WebRendererQueryHandler::OnQueryCanceled(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, long long queryId) // 0x10C71F40
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnQueryCanceled@WebRendererQueryHandler@Bridge@Browser@Web@@UAEXV?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@_J@Z");
				// long long queryId;
			}

			void WebRendererQueryHandler::AddMethod(std::string const &name, std::function<enum Web::Browser::Bridge::QueryError __cdecl(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &,std::string *)> const &method) // 0x10C70ED0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?AddMethod@WebRendererQueryHandler@Bridge@Browser@Web@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV?$function@$$A6A?AW4QueryError@Bridge@Browser@Web@@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z@6@@Z");
				// std::function<enum Web::Browser::Bridge::QueryError __cdecl(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &,std::string *)> const &method;

				m_Methods[name] = method;
			}

			void WebRendererQueryHandler::Update() // 0x10C721A0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Update@WebRendererQueryHandler@Bridge@Browser@Web@@QAEXXZ");
				// static ...; // 0x10C723D5
				// static ...; // 0x10C723CF
				// static ...; // 0x10C723C8
				// static ...; // 0x10C723A4
				// static ...; // 0x10C7239C
				// Web::Browser::Bridge::WebRendererQueryHandler *const this;
				// Web::Browser::Bridge::WebRendererQueryHandler::PendingQuery *pendingQuery;
					// std::unique_ptr<Web::Browser::Bridge::WebRendererQueryHandler::PendingQuery> query;
					// Web::Browser::Bridge::QueryError errorCode;
					// std::string result;
				// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
				// function call : void (__int32, CefStringBase<CefStringTraitsUTF16> const &)

				PendingQuery *pendingQuery;
				while (m_Queries.pop(pendingQuery))
				{
					std::unique_ptr<PendingQuery> query(pendingQuery);
					std::string result;
					QueryError errorCode = query->m_Method(*query->m_Args, &result);
					if (errorCode == QueryError_Ok)
						query->m_Callback->Success(result);
					else
						query->m_Callback->Failure(errorCode, result);
				}
			}

			// mangled_x86(MANGLED_DEFAULT, "??0PendingQuery@WebRendererQueryHandler@Bridge@Browser@Web@@QAE@XZ"); no body to assert in
		}
	}
}

/* ---------- private code */
