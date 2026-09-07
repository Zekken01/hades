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
struct CefStringTraitsUTF16;
struct lambda_1;
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

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern char const *const kDefaultMimetype; // 0x111C0F5C
	extern std::unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > kExtensionMimeTypeMap; // 0x1247EE30
}
/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		extern WebRendererSchemeHandlerFactory* _sub_10CDD890(Web::Browser::WebRendererSchemeHandlerFactory *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
		WebRendererSchemeHandlerFactory::WebRendererSchemeHandlerFactory(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &scheme, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &directory) : m_Directory(todo_result<std::basic_string<char,std::char_traits<char>,std::allocator<char> >>()), m_Scheme(todo_result<std::basic_string<char,std::char_traits<char>,std::allocator<char> >>()) // 0x10CDD890
		{
			mangled_x86(MANGLED_TODO, "??0WebRendererSchemeHandlerFactory@Browser@Web@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &directory;
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
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > extension;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > host;
			// std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16>,std::less<CefStringBase<CefStringTraitsUTF16> >,std::allocator<std::pair<CefStringBase<CefStringTraitsUTF16> const ,CefStringBase<CefStringTraitsUTF16> > > > headers;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > path;
			// scoped_refptr<CefStreamReader> stream;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > contentType;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > scheme;
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

		_extern void _sub_10CDE710(Web::Browser::WebRendererSchemeHandlerFactory * const);
		_inline WebRendererSchemeHandlerFactory::~WebRendererSchemeHandlerFactory() // 0x10CDE710
		{
			mangled_x86(MANGLED_TODO, "??1WebRendererSchemeHandlerFactory@Browser@Web@@UAE@XZ");
			// __shifted(Web::Browser::WebRendererSchemeHandlerFactory, 72);
			// Web::Browser::WebRendererSchemeHandlerFactory *const this;
			compiler_generated();
			todo("implement");
			_sub_10CDE710(this);
		}
	}
}

/* ---------- private code */
