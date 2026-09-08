/* ---------- headers */

#include "Web/WebRendererSchemeHandlerFactory.hpp"
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
#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/FileSystem/ModPackageFileSystemViewManager.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patches/CustomPackets.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/Uri.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"
#include "Web/WebFileReadHandler.hpp"

#include <base/cef_atomic_ref_count.h>
#include <base/cef_lock.h>
#include <base/cef_logging.h>
#include <base/cef_platform_thread.h>
#include <base/cef_ref_counted.h>
#include <base/cef_scoped_refptr.h>
#include <base/cef_thread_checker.h>
#include <base/internal/cef_lock_impl.h>
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/core/demangle.hpp>
#include <boost/exception/all.hpp>
#include <boost/function/function_base.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/range/as_literal.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_index/stl_type_index.hpp>
#include <cef_base.h>
#include <cef_devtools_message_observer.h>
#include <cef_extension_handler.h>
#include <cef_resource_handler.h>
#include <cef_scheme.h>
#include <internal/cef_string_wrappers.h>
#include <internal/cef_types_wrappers.h>
#include <internal/cef_win.h>
#include <wrapper/cef_stream_resource_handler.h>

#include <WinSock2.h>
#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <boost/range/detail/implementation_help.hpp>
#include <boost/type_index.hpp>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
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
#include <vector>

/* ---------- forward declarations */

class CModPackageFileSystemView;
class CefStreamResourceHandler;
struct CefStringTraitsUTF16;
struct lambda_1;
namespace Utils
{
	namespace Uri
	{
		struct UriComponents;
	}
}
namespace Web
{
	namespace Browser
	{
		class WebRendererSchemeHandlerFactory;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace Uri {}
	using namespace Utils::Uri;
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

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

//class Web::Browser::WebRendererSchemeHandlerFactory::Create::__l2::<lambda_1>
//{
//public:
//	bool operator()(char) const;
//};
//static_assert(sizeof(Web::Browser::WebRendererSchemeHandlerFactory::Create::__l2::<lambda_1>) == 1, "Invalid Web::Browser::WebRendererSchemeHandlerFactory::Create::__l2::<lambda_1> size");

/* ---------- prototypes */

std::string GetMimeType(std::string extension);
scoped_refptr<CefResourceHandler> CreateError(scoped_refptr<CefRequest> request, __int32 statusCode, std::string const &statusText);
bool HandleContentRange(std::string const &range_query, scoped_refptr<CefStreamReader> stream, std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > &header_map, long long &content_length);
bool ParseRequestUri(scoped_refptr<CefRequest> const &request, std::string &scheme, std::string &host, std::string &path);
void BuildResponseHeaders(scoped_refptr<CefRequest> const &request, std::string const &contentType, scoped_refptr<CefStreamReader> const &stream, std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > &headers);
bool ParseRequestRange(scoped_refptr<CefRequest> request, std::string &range);
scoped_refptr<CefStreamResourceHandler> GetStreamResourceHandler(scoped_refptr<CefRequest> request, std::string const &mimeType, std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > &headers, scoped_refptr<CefStreamReader> stream);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern char const *const kDefaultMimetype; // 0x111C0F5C
	extern std::unordered_map<std::string,std::string> kExtensionMimeTypeMap; // 0x1247EE30
}
using namespace hades_file_local;
/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		extern WebRendererSchemeHandlerFactory* _sub_10CDD890(Web::Browser::WebRendererSchemeHandlerFactory *const, std::string const &, std::string const &);
		WebRendererSchemeHandlerFactory::WebRendererSchemeHandlerFactory(std::string const &scheme, std::string const &directory) : m_Directory(todo_result<std::string>()), m_Scheme(todo_result<std::string>()) // 0x10CDD890
		{
			mangled_x86(MANGLED_TODO, "??0WebRendererSchemeHandlerFactory@Browser@Web@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
			// std::string const &directory;
			todo("implement");
			_sub_10CDD890(this, scheme, directory);
		}
	}
}

extern scoped_refptr<CefResourceHandler> _sub_10CE0480(Web::Browser::WebRendererSchemeHandlerFactory *const, scoped_refptr<CefBrowser>, scoped_refptr<CefFrame>, CefStringBase<CefStringTraitsUTF16> const &, scoped_refptr<CefRequest>);
namespace Web
{
	namespace Browser
	{
		scoped_refptr<CefResourceHandler> WebRendererSchemeHandlerFactory::Create(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, CefStringBase<CefStringTraitsUTF16> const &schemeName, scoped_refptr<CefRequest> request) // 0x10CE0480
		{
			mangled_x86(MANGLED_TODO, "?Create@WebRendererSchemeHandlerFactory@Browser@Web@@MAE?AV?$scoped_refptr@VCefResourceHandler@@@@V?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@ABV?$CefStringBase@UCefStringTraitsUTF16@@@@V?$scoped_refptr@VCefRequest@@@@@Z");
			// static ...; // 0x10CE13D1
			// static ...; // 0x10CE13C7
			// static ...; // 0x10CE13C0
			// static ...; // 0x10CE13BC
			// static ...; // 0x10CE13B3
			// static ...; // 0x10CE13AE
			// static ...; // 0x10CE13A4
			// static ...; // 0x10CE1398
			// static ...; // 0x10CE1390
			// static ...; // 0x10CE12F4
			// static ...; // 0x10CE12EC
			// Web::Browser::WebRendererSchemeHandlerFactory *const this;
			// scoped_refptr<CefBrowser> browser;
			// scoped_refptr<CefFrame> frame;
			// CefStringBase<CefStringTraitsUTF16> const &schemeName;
			// scoped_refptr<CefRequest> request;
			// std::filesystem::path fpath;
			// std::string extension;
			// std::string host;
			// std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > headers;
			// std::string path;
			// scoped_refptr<CefStreamReader> stream;
			// std::string contentType;
			// std::string scheme;
			{
				// CModPackageFileSystemView::SFileEntry fileEntry;
				// std::shared_ptr<CModPackageFileSystemView> fsView;
			}
			{
				// std::filesystem::_Path_iterator<std::_String_const_iterator<std::_String_val<std::_Simple_types<wchar_t> > > > &it;
				// std::filesystem::_Path_iterator<std::_String_const_iterator<std::_String_val<std::_Simple_types<wchar_t> > > > &_;
				// std::pair<std::filesystem::_Path_iterator<std::_String_const_iterator<std::_String_val<std::_Simple_types<wchar_t> > > >,std::filesystem::_Path_iterator<std::_String_const_iterator<std::_String_val<std::_Simple_types<wchar_t> > > > > $S11;
				// std::filesystem::path dir;
				// std::filesystem::path filePath;
			}
			// function call : CefStringBase<CefStringTraitsUTF16> ()
			// function call : bool ()
			todo("implement");
			scoped_refptr<CefResourceHandler> __result = _sub_10CE0480(this, browser, frame, schemeName, request);
			return __result;
		}

		_inline WebRendererSchemeHandlerFactory::~WebRendererSchemeHandlerFactory() // 0x10CDE710
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1WebRendererSchemeHandlerFactory@Browser@Web@@UAE@XZ");
			// __shifted(Web::Browser::WebRendererSchemeHandlerFactory, 72);
			// Web::Browser::WebRendererSchemeHandlerFactory *const this;

			compiler_generated();
		}
	}
}

/* ---------- private code */

extern std::string _sub_10CE1B50(std::string);
std::string GetMimeType(std::string extension) // 0x10CE1B50
{
	// `anonymous-namespace'::GetMimeType
	// static ...; // 0x10CE1CF8
	// static ...; // 0x10CE1CEC
	// static ...; // 0x10CE1CE4
	// std::string extension;
	// std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<std::string const ,std::string> > > > it;
	todo("implement");
	std::string __result = _sub_10CE1B50(extension);
	return __result;
}

extern scoped_refptr<CefResourceHandler> _sub_10CE17D0(scoped_refptr<CefRequest>, __int32, std::string const &);
scoped_refptr<CefResourceHandler> CreateError(scoped_refptr<CefRequest> request, __int32 statusCode, std::string const &statusText) // 0x10CE17D0
{
	// `anonymous-namespace'::CreateError
	// static ...; // 0x10CE1A6C
	// static ...; // 0x10CE1A64
	// scoped_refptr<CefRequest> request;
	// __int32 statusCode;
	// std::string const &statusText;
	// std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > headers;
	// scoped_refptr<CefStreamReader> stream;
	todo("implement");
	scoped_refptr<CefResourceHandler> __result = _sub_10CE17D0(request, statusCode, statusText);
	return __result;
}

_extern bool _sub_10CE2680(std::string const &, scoped_refptr<CefStreamReader>, std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > &, long long &);
bool HandleContentRange(std::string const &range_query, scoped_refptr<CefStreamReader> stream, std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > &header_map, long long &content_length) // 0x10CE2680
{
	// `anonymous-namespace'::HandleContentRange
	// static ...; // 0x10CE2C20
	// std::string const &range_query;
	// scoped_refptr<CefStreamReader> stream;
	// std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > &header_map;
	// long long &content_length;
	// long long range_begin;
	// long long total_bytes;
	// long long range_end;
	// std::stringstream content_length_ss;
	// std::stringstream content_range_ss;
	{
		// unsigned __int32 hyphen_pos;
	}
	// function call : __int32 (long long, __int32)
	// function call : long long ()
	// function call : __int32 (long long, __int32)
	todo("implement");
	bool __result = _sub_10CE2680(range_query, stream, header_map, content_length);
	return __result;
}

_extern bool _sub_10CE3180(scoped_refptr<CefRequest> const &, std::string &, std::string &, std::string &);
bool ParseRequestUri(scoped_refptr<CefRequest> const &request, std::string &scheme, std::string &host, std::string &path) // 0x10CE3180
{
	// `anonymous-namespace'::ParseRequestUri
	// static ...; // 0x10CE344C
	// scoped_refptr<CefRequest> const &request;
	// std::string &scheme;
	// std::string &host;
	// std::string &path;
	// std::string url;
	// Utils::Uri::UriComponents components;
	// function call : CefStringBase<CefStringTraitsUTF16> ()
	todo("implement");
	bool __result = _sub_10CE3180(request, scheme, host, path);
	return __result;
}

_extern void _sub_10CE0160(scoped_refptr<CefRequest> const &, std::string const &, scoped_refptr<CefStreamReader> const &, std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > &);
void BuildResponseHeaders(scoped_refptr<CefRequest> const &request, std::string const &contentType, scoped_refptr<CefStreamReader> const &stream, std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > &headers) // 0x10CE0160
{
	// `anonymous-namespace'::BuildResponseHeaders
	// static ...; // 0x10CE0398
	// static ...; // 0x10CE0390
	// scoped_refptr<CefRequest> const &request;
	// std::string const &contentType;
	// scoped_refptr<CefStreamReader> const &stream;
	// std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > &headers;
	// std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<CefStringBase<CefStringTraitsUTF16> const ,CefStringBase<CefStringTraitsUTF16> > > > > it;
	// std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > requestHeaders;
	// CefStringBase<CefStringTraitsUTF16> origin;
	// function call : void (std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > &)
	todo("implement");
	_sub_10CE0160(request, contentType, stream, headers);
}

_extern bool _sub_10CE2EA0(scoped_refptr<CefRequest>, std::string &);
bool ParseRequestRange(scoped_refptr<CefRequest> request, std::string &range) // 0x10CE2EA0
{
	// `anonymous-namespace'::ParseRequestRange
	// static ...; // 0x10CE30D0
	// static ...; // 0x10CE30B8
	// static ...; // 0x10CE30B0
	// scoped_refptr<CefRequest> request;
	// std::string &range;
	// std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > headers;
	// std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<CefStringBase<CefStringTraitsUTF16> const ,CefStringBase<CefStringTraitsUTF16> > > > > findRange;
	// function call : void (std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > &)
	todo("implement");
	bool __result = _sub_10CE2EA0(request, range);
	return __result;
}

extern scoped_refptr<CefStreamResourceHandler> _sub_10CE1D70(scoped_refptr<CefRequest>, std::string const &, std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > &, scoped_refptr<CefStreamReader>);
scoped_refptr<CefStreamResourceHandler> GetStreamResourceHandler(scoped_refptr<CefRequest> request, std::string const &mimeType, std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > &headers, scoped_refptr<CefStreamReader> stream) // 0x10CE1D70
{
	// `anonymous-namespace'::GetStreamResourceHandler
	// static ...; // 0x10CE246C
	// static ...; // 0x10CE2464
	// scoped_refptr<CefRequest> request;
	// std::string const &mimeType;
	// std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > &headers;
	// scoped_refptr<CefStreamReader> stream;
	// scoped_refptr<CefStreamResourceHandler> handler;
	// std::string range;
	{
		// long long content_length;
	}
	todo("implement");
	scoped_refptr<CefStreamResourceHandler> __result = _sub_10CE1D70(request, mimeType, headers, stream);
	return __result;
}
