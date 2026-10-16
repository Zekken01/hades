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

#include "Utils/Logger.hpp"  // hades: added for 0x10CE0480

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

CefString CefURIDecode(const CefString &text, bool convert_to_utf8, cef_uri_unescape_rule_t unescape_rule);  // hades: added for 0x10CE3180

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
	std::unordered_map<std::string,std::string> kExtensionMimeTypeMap = { { ".html", "text/html" }, { ".htm", "text/html" }, { ".png", "image/png" }, { ".jpg", "image/jpeg" }, { ".jpeg", "image/jpeg" }, { ".jpe", "image/jpeg" }, { ".gif", "image/gif" }, { ".bmp", "image/bmp" }, { ".ico", "image/x-icon" }, { ".css", "text/css" }, { ".scss", "text/css" }, { ".sass", "text/css" }, { ".less", "text/css" }, { ".js", "application/javascript" }, { ".txt", "text/plain" }, { ".obj", "text/plain" }, { ".svg", "image/svg+xml" }, { ".ttf", "application/font-sfnt" }, { ".otf", "application/font-sfnt" }, { ".woff", "application/x-font-wof" }, { ".ogv", "video/ogg" }, { ".webm", "video/webm" }, { ".ogg", "audio/ogg" }, { ".json", "application/json" } }; // 0x1247EE30
}
using namespace hades_file_local;
/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		WebRendererSchemeHandlerFactory::WebRendererSchemeHandlerFactory(std::string const &scheme, std::string const &directory) : m_Directory(directory), m_Scheme(scheme) /* hades-mem-init: : m_Directory(todo_result<std::string>()), m_Scheme(todo_result<std::string>()) */ // 0x10CDD890
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0WebRendererSchemeHandlerFactory@Browser@Web@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
		}
	}
}


namespace Web
{
	namespace Browser
	{
		scoped_refptr<CefResourceHandler> WebRendererSchemeHandlerFactory::Create(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, CefStringBase<CefStringTraitsUTF16> const &schemeName, scoped_refptr<CefRequest> request) // 0x10CE0480
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Create@WebRendererSchemeHandlerFactory@Browser@Web@@MAE?AV?$scoped_refptr@VCefResourceHandler@@@@V?$scoped_refptr@VCefBrowser@@@@V?$scoped_refptr@VCefFrame@@@@ABV?$CefStringBase@UCefStringTraitsUTF16@@@@V?$scoped_refptr@VCefRequest@@@@@Z");

			std::string scheme;
			std::string host;
			std::string path;
			if (!ParseRequestUri(request, scheme, host, path) || scheme != m_Scheme)
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::All, Utils::LogLevel::Error, "Cef scheme handler failed to parse uri \"" + request->GetURL().ToString() + "\"");
				return CreateError(request, 400, "Bad Request");
			}
			if (!frame->IsMain() && m_Scheme == "dew" && host == "ui")
				return CreateError(request, 401, "Not Authorized");
			boost::algorithm::trim_left_if(path, [](char c) { return c == '/' || c == '\\'; });
			std::filesystem::path fpath(path);
			CefRefPtr<CefStreamReader> stream;
			if (scheme == "pak")
			{
				CModPackageFileSystemView::SFileEntry fileEntry = {};
				auto fsView = Utils::Singleton<CModPackageFileSystemViewManager>::Instance().GetView(host);
				if (!fsView || !fsView->GetFileEntry(fpath.string(), &fileEntry))
					return CreateError(request, 404, "File Not Found");
				stream = new CWebFileReadHandler(fsView->GetFilePath(), fsView->GetBaseOffset() + fileEntry.offset, fileEntry.size);
			}
			else
			{
				std::filesystem::path dir = std::filesystem::canonical(m_Directory);
				std::filesystem::path filePath = (dir / host / fpath).lexically_normal();
				auto [it, _] = std::mismatch(dir.begin(), dir.end(), filePath.begin());
				if (it != dir.end() || !std::filesystem::exists(filePath))
					return CreateError(request, 404, "File Not Found");
				stream = CefStreamReader::CreateForFile(filePath.string());
			}
			std::string extension = fpath.has_extension() ? fpath.extension().string() : "";
			boost::algorithm::to_lower(extension);
			std::string contentType = GetMimeType(extension);
			std::multimap<CefString,CefString> headers;
			BuildResponseHeaders(request, contentType, stream, headers);
			return GetStreamResourceHandler(request, contentType, headers, stream);
		}

	}
}

/* ---------- private code */

std::string GetMimeType(std::string extension) // 0x10CE1B50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetMimeType@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@Z");

	if (extension.empty())
		return kDefaultMimetype;
	auto it = static_cast<std::unordered_map<std::string, std::string> const &>(kExtensionMimeTypeMap).find(extension);
	if (it == static_cast<std::unordered_map<std::string, std::string> const &>(kExtensionMimeTypeMap).end())
		return kDefaultMimetype;
	return it->second;
}

scoped_refptr<CefResourceHandler> CreateError(scoped_refptr<CefRequest> request, __int32 statusCode, std::string const &statusText) // 0x10CE17D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CreateError@@YA?AV?$scoped_refptr@VCefResourceHandler@@@@V?$scoped_refptr@VCefRequest@@@@HABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

	scoped_refptr<CefStreamReader> stream = CefStreamReader::CreateForData((void *)statusText.c_str(), statusText.length());
	std::multimap<CefStringBase<CefStringTraitsUTF16>, CefStringBase<CefStringTraitsUTF16> > headers;
	BuildResponseHeaders(request, "text/html", stream, headers);
	return new CefStreamResourceHandler(statusCode, statusText, "text/html", headers, stream);
}

bool HandleContentRange(std::string const &range_query, scoped_refptr<CefStreamReader> stream, std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > &header_map, long long &content_length) // 0x10CE2680
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleContentRange@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$scoped_refptr@VCefStreamReader@@@@AAV?$multimap@V?$CefStringBase@UCefStringTraitsUTF16@@@@V1@U?$less@V?$CefStringBase@UCefStringTraitsUTF16@@@@@std@@V?$allocator@U?$pair@$$CBV?$CefStringBase@UCefStringTraitsUTF16@@@@V1@@std@@@3@@2@AA_J@Z");

	int64 total_bytes = 0;
	std::stringstream content_range_ss;
	std::stringstream content_length_ss;
	int64 range_begin = 0;
	int64 range_end = 0;

	if (range_query.find("bytes=") != 0 ||
		range_query.find(",") != std::string::npos) {
		// Multiple range headers are not supported.
		return false;
	}
	else {
		// Further parse |range_query| and find hyphen.
		std::size_t hyphen_pos = range_query.find("-");
		if (hyphen_pos != std::string::npos) {
			// Skip "bytes=" prefix (offset = 6).
			range_begin = atoll(range_query.substr(6, hyphen_pos - 6).c_str());
			range_end = atoll(range_query.substr(hyphen_pos + 1).c_str());
		}
		else {
			return false;
		}
	}

	if (stream->Seek(0, SEEK_END) == 0) {
		total_bytes = stream->Tell();
		if (total_bytes > 0) {
			if (range_end == 0) {
				range_end = (total_bytes - 1);
			}
			if (range_begin > range_end) {
				return false;
			}
			else
			{
				content_range_ss << "bytes "
					<< range_begin << "-" << range_end << "/"
					<< total_bytes;
				content_length = total_bytes - range_begin;
				content_length_ss << content_length;
				header_map.insert(std::pair<CefString, CefString>(
					"Content-Range", content_range_ss.str()));
				header_map.insert(std::pair<CefString, CefString>(
					"Content-Length", content_length_ss.str()));
			}
		}

		// Set stream cursor to range begin.
		stream->Seek(range_begin, SEEK_SET);
	}

	return true;
}

bool ParseRequestUri(scoped_refptr<CefRequest> const &request, std::string &scheme, std::string &host, std::string &path) // 0x10CE3180
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ParseRequestUri@@YA_NABV?$scoped_refptr@VCefRequest@@@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@11@Z");

	std::string url = request->GetURL().ToString();
	boost::replace_all(url, " ", "%20");
	Utils::Uri::UriComponents components;
	if (!Utils::Uri::ParseUriComponents(url, components))
		return false;
	scheme = components.scheme;
	host = components.authority;
	path = components.path;
	path = CefURIDecode(path, true, UU_NORMAL).ToString();
	if (path.size() == 0)
		path = "/";
	if (path.substr(path.size() - 1) == "/")
		path += "index.html";
	return true;
}

void BuildResponseHeaders(scoped_refptr<CefRequest> const &request, std::string const &contentType, scoped_refptr<CefStreamReader> const &stream, std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > &headers) // 0x10CE0160
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BuildResponseHeaders@@YAXABV?$scoped_refptr@VCefRequest@@@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV?$scoped_refptr@VCefStreamReader@@@@AAV?$multimap@V?$CefStringBase@UCefStringTraitsUTF16@@@@V1@U?$less@V?$CefStringBase@UCefStringTraitsUTF16@@@@@std@@V?$allocator@U?$pair@$$CBV?$CefStringBase@UCefStringTraitsUTF16@@@@V1@@std@@@3@@3@@Z");

	CefResponse::HeaderMap requestHeaders;
	request->GetHeaderMap(requestHeaders);

	CefString origin = "";
	auto it = requestHeaders.find("Origin");
	if (it != requestHeaders.end())
		origin = it->second;

	headers.insert(std::make_pair("Access-Control-Allow-Origin", origin));
	headers.insert(std::make_pair("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept"));
}

bool ParseRequestRange(scoped_refptr<CefRequest> request, std::string &range) // 0x10CE2EA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ParseRequestRange@@YA_NV?$scoped_refptr@VCefRequest@@@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

	CefRequest::HeaderMap headers;
	request->GetHeaderMap(headers);

	auto findRange = headers.find("Range");
	if (findRange != headers.end()) {
		range = findRange->second.ToString();
		return true;
	}

	return false;
}

#line 501
scoped_refptr<CefStreamResourceHandler> GetStreamResourceHandler(scoped_refptr<CefRequest> request, std::string const &mimeType, std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > &headers, scoped_refptr<CefStreamReader> stream) // 0x10CE1D70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetStreamResourceHandler@@YA?AV?$scoped_refptr@VCefStreamResourceHandler@@@@V?$scoped_refptr@VCefRequest@@@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV?$multimap@V?$CefStringBase@UCefStringTraitsUTF16@@@@V1@U?$less@V?$CefStringBase@UCefStringTraitsUTF16@@@@@std@@V?$allocator@U?$pair@$$CBV?$CefStringBase@UCefStringTraitsUTF16@@@@V1@@std@@@3@@4@V?$scoped_refptr@VCefStreamReader@@@@@Z");
#line 514

	#line 503 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Web\\WebRendererSchemeHandlerFactory.cpp"
	DCHECK(request);
	DCHECK(stream);
	#line 519 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Web\\WebRendererSchemeHandlerFactory.cpp"
	CefRefPtr<CefStreamResourceHandler> handler;
	std::string range;
	if (ParseRequestRange(request, range)) {
		int64 content_length = -1;
		if (HandleContentRange(range, stream, headers, content_length)) {
			handler = new CefStreamResourceHandler(
				206,
				"Partial Content",
				mimeType,
				headers,
				stream);
		}
		else {
			handler = new CefStreamResourceHandler(
				416,
				"Requested Range Not Satisfiable",
				mimeType,
				headers,
				stream);
		}
	}
	else {
		handler = new CefStreamResourceHandler(200, "OK", mimeType, headers, stream);
	}
	return handler;
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { char const *const kDefaultMimetype = "application/octet-stream"; }
