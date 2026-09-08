/* ---------- headers */

#include "mods/mod_package_updater.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/cseries/static_string.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "Download/DownloadStatCounter.hpp"
#include "Download/HttpFileDownload.hpp"
#include "Download/IDownload.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patches/CustomPackets.hpp"
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
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <conio.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <ostream>
#include <queue>
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

class c_file_reference;
class c_mod_package;
class c_mod_package_manager;
class c_mod_package_updater_blocking;
struct lambda_1;
struct lambda_2;
struct s_file_reference;
struct s_mod_package_header;
namespace Download
{
	class CHttpFileDownload;
}
namespace Http
{
	class CHttpHeaders;
	class IHttpRequest;
	class IHttpResponse;
}

namespace Utils {}
using namespace ::Utils;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Download {}
using namespace ::Download;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Core {}
	using namespace Patches::Core;
}

namespace Http {}
using namespace ::Http;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

enum
{
	k_retry_interval_in_seconds = 5, // 0x0005
};

/* ---------- definitions */

//class download_mod_package_header::__l2::<lambda_1>
//{
//public:
//	void operator()(std::shared_ptr<Http::IHttpRequest>, bool) const;
//	<lambda_1>(download_mod_package_header::__l2::<lambda_1> &);
//	<lambda_1>(std::atomic<bool> &);
//private:
//	std::atomic<bool> &completion_flag; // 0x0
//public:
//	download_mod_package_header::__l2::<lambda_1> &operator=(download_mod_package_header::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(download_mod_package_header::__l2::<lambda_1>) == 4, "Invalid download_mod_package_header::__l2::<lambda_1> size");

//class download_mod_package_header::__l2::<lambda_2>
//{
//public:
//	bool operator()(char const *, unsigned __int32);
//	<lambda_2>(download_mod_package_header::__l2::<lambda_2> &);
//	<lambda_2>(char *&, char *&);
//private:
//	char *&end; // 0x0
//	char *&ptr; // 0x4
//public:
//	download_mod_package_header::__l2::<lambda_2> &operator=(download_mod_package_header::__l2::<lambda_2> const &);
//};
//static_assert(sizeof(download_mod_package_header::__l2::<lambda_2>) == 8, "Invalid download_mod_package_header::__l2::<lambda_2> size");

/* ---------- prototypes */

extern bool download_mod_package_header(char const *url, s_mod_package_header *out_header, bool use_range);

void shell_allocate_console();
void shell_free_console(bool dedicated);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_inline c_mod_package_updater_blocking::s_mod_package_description::s_mod_package_description(c_mod_package_updater_blocking::s_mod_package_description &&__that) // 0x108ADB90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_mod_package_description@c_mod_package_updater_blocking@@QAE@$$QAU01@@Z");
	// c_mod_package_updater_blocking::s_mod_package_description &__that;

	compiler_generated();
}

_inline c_mod_package_updater_blocking::s_mod_package_description::s_mod_package_description(c_mod_package_updater_blocking::s_mod_package_description const &__that) // 0x108ADCD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_mod_package_description@c_mod_package_updater_blocking@@QAE@ABU01@@Z");
	// c_mod_package_updater_blocking::s_mod_package_description const &__that;

	compiler_generated();
}

_inline c_mod_package_updater_blocking::s_mod_package_description::s_mod_package_description() // 0x108ADE70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_mod_package_description@c_mod_package_updater_blocking@@QAE@XZ");
	// c_mod_package_updater_blocking::s_mod_package_description *const this;

	compiler_generated();
}

_inline c_mod_package_updater_blocking::s_mod_package_description::~s_mod_package_description() // 0x108ADFE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1s_mod_package_description@c_mod_package_updater_blocking@@QAE@XZ");
	// c_mod_package_updater_blocking::s_mod_package_description *const this;

	compiler_generated();
}

_extern void _sub_108B1070(c_mod_package_updater_blocking *const, bool, char const *, char const *);
void c_mod_package_updater_blocking::initialize(bool dedicated, char const *package_list_filename, char const *package_directory) // 0x108B1070
{
	mangled_x86(MANGLED_TODO, "?initialize@c_mod_package_updater_blocking@@QAEX_NPBD1@Z");
	// char const *package_directory;
	todo("implement");
	_sub_108B1070(this, dedicated, package_list_filename, package_directory);
}

_extern bool _sub_108B1190(c_mod_package_updater_blocking *const);
bool c_mod_package_updater_blocking::locate_packages() // 0x108B1190
{
	mangled_x86(MANGLED_TODO, "?locate_packages@c_mod_package_updater_blocking@@AAE_NXZ");
	// static ...; // 0x108B169B
	// static ...; // 0x108B1697
	// static ...; // 0x108B1693
	// static ...; // 0x108B168F
	// static ...; // 0x108B168C
	// static ...; // 0x108B1680
	// static ...; // 0x108B1638
	// static ...; // 0x108B1630
	// c_mod_package_updater_blocking *const this;
	// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> doc;
	// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > src;
	// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &mods;
	// std::basic_ifstream<char,std::char_traits<char> > ifs;
	{
		// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > it;
		{
			// c_mod_package_updater_blocking::s_mod_package_description description;
			// char const *package_url;
			// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &mod;
		}
	}
	todo("implement");
	bool __result = _sub_108B1190(this);
	return __result;
}

_extern bool _sub_108B08C0(c_mod_package_updater_blocking *const, char const *, char const *);
bool c_mod_package_updater_blocking::download_package(char const *package_url, char const *filename) // 0x108B08C0
{
	mangled_x86(MANGLED_TODO, "?download_package@c_mod_package_updater_blocking@@AAE_NPBD0@Z");
	// static ...; // 0x108B0D00
	// c_mod_package_updater_blocking *const this;
	// char const *package_url;
	// char const *filename;
	// std::shared_ptr<Download::CHttpFileDownload> download;
	{
		// __int32 speed;
		// long long position;
		// long long length;
		{
			// float complete_fraction;
		}
	}
	{
		// __int32 x;
	}
	// function call : void ()
	// function call : long long () const
	// function call : long long () const
	// function call : __int32 () const
	// function call : bool () const
	// function call : void (unsigned long)
	// function call : Download::EDownloadStatus () const
	// function call : Download::EDownloadError () const
	// function call : Download::EDownloadError () const
	// function call : Download::EDownloadError () const
	todo("implement");
	bool __result = _sub_108B08C0(this, package_url, filename);
	return __result;
}

_extern void _sub_108B0040(c_mod_package_updater_blocking *const, c_mod_package &, c_mod_package_updater_blocking::s_mod_package_description *);
void c_mod_package_updater_blocking::build_mod_package_description(c_mod_package &package, c_mod_package_updater_blocking::s_mod_package_description *description) // 0x108B0040
{
	mangled_x86(MANGLED_TODO, "?build_mod_package_description@c_mod_package_updater_blocking@@AAEXAAVc_mod_package@@PAUs_mod_package_description@1@@Z");
	// static ...; // 0x108B0160
	// c_mod_package_updater_blocking *const this;
	// c_mod_package &package;
	// c_mod_package_updater_blocking::s_mod_package_description *description;
	// s_static_string<32> metadata_name;
	todo("implement");
	_sub_108B0040(this, package, description);
}

_extern bool _sub_108B02E0(char const *, s_mod_package_header *, bool);
bool download_mod_package_header(char const *url, s_mod_package_header *out_header, bool use_range) // 0x108B02E0
{
	mangled_x86(MANGLED_TODO, "?download_mod_package_header@@YA_NPBDPAUs_mod_package_header@@_N@Z");
	// static ...; // 0x108B0771
	// static ...; // 0x108B0769
	// static ...; // 0x108B0761
	// static ...; // 0x108B0758
	// static ...; // 0x108B0710
	// static ...; // 0x108B0708
	// char const *url;
	// s_mod_package_header *out_header;
	// bool use_range;
	// Http::CHttpHeaders headers;
	// char *ptr;
	// std::atomic<bool> completion_flag;
	// char *end;
	// std::shared_ptr<Http::IHttpResponse> response;
	// std::shared_ptr<Http::IHttpRequest> request;
	// function call : void (Http::CHttpHeaders)
	// function call : void (std::string)
	// function call : bool ()
	// function call : void (std::function<void __cdecl(std::shared_ptr<Http::IHttpRequest>,bool)> &)
	// function call : void (std::function<bool __cdecl(char const *,unsigned int)> &)
	// function call : std::shared_ptr<Http::IHttpResponse> ()
	// function call : __int32 () const
	todo("implement");
	bool __result = _sub_108B02E0(url, out_header, use_range);
	return __result;
}

_extern bool _sub_108B23B0(c_mod_package_updater_blocking *const, c_mod_package_updater_blocking::s_mod_package_description *);
bool c_mod_package_updater_blocking::update_package(c_mod_package_updater_blocking::s_mod_package_description *description) // 0x108B23B0
{
	mangled_x86(MANGLED_TODO, "?update_package@c_mod_package_updater_blocking@@AAE_NPAUs_mod_package_description@1@@Z");
	// static ...; // 0x108B2C90
	// static ...; // 0x108B2C87
	// static ...; // 0x108B2C79
	// static ...; // 0x108B2C65
	// static ...; // 0x108B2C5D
	// static ...; // 0x108B2C59
	// static ...; // 0x108B2C56
	// static ...; // 0x108B2C4D
	// static ...; // 0x108B2C41
	// static ...; // 0x108B2C38
	// static ...; // 0x108B2BB4
	// static ...; // 0x108B2BAC
	// c_mod_package_updater_blocking *const this;
	// c_mod_package_updater_blocking::s_mod_package_description *description;
	// c_mod_package_manager::s_entry package_entry;
	// char const *package_url;
	// bool needs_downloading;
	// static s_mod_package_header remote_header; // 0x12407980
	// c_mod_package_manager &package_manager;
	// static __int32 $TSS0; // 0x12407DD8
	{
		// c_file_reference const &local_file;
		{
			// c_mod_package local_package;
		}
	}
	{
		// s_static_string<256> temp_filename;
		// c_mod_package::e_error err;
		// c_mod_package package;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > hash_str;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > mod_version;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > mod_name;
		// std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > ws;
		// s_static_string<256> new_name;
		// s_file_reference temp_file_reference;
	}
	// function call : s_file_reference *(*const)(s_file_reference *, char const *, bool)
	// function call : bool (*const)(s_file_reference *)
	// function call : bool (*const)(s_file_reference *)
	// function call : bool (*const)(s_file_reference *, char const *)
	todo("implement");
	bool __result = _sub_108B23B0(this, description);
	return __result;
}

_extern bool _sub_108B1BF0(c_mod_package_updater_blocking *const);
bool c_mod_package_updater_blocking::process_queue() // 0x108B1BF0
{
	mangled_x86(MANGLED_TODO, "?process_queue@c_mod_package_updater_blocking@@AAE_NXZ");
	// c_mod_package_updater_blocking *const this;
	// c_mod_package_manager &package_manager;
	{
		// c_mod_package_updater_blocking::s_mod_package_description &package_description;
	}
	// function call : void (unsigned long)
	todo("implement");
	bool __result = _sub_108B1BF0(this);
	return __result;
}

_extern bool _sub_108B2EF0(c_mod_package_updater_blocking *const);
bool c_mod_package_updater_blocking::update_packages_blocking() // 0x108B2EF0
{
	mangled_x86(MANGLED_TODO, "?update_packages_blocking@c_mod_package_updater_blocking@@QAE_NXZ");
	// c_mod_package_updater_blocking *const this;
	// bool result;
	todo("implement");
	bool __result = _sub_108B2EF0(this);
	return __result;
}

/* ---------- private code */

_extern void _sub_108B1F00();
void shell_allocate_console() // 0x108B1F00
{
	// `anonymous-namespace'::shell_allocate_console
	// procedure flags: nofpo
	// static ...; // 0x108B2089
	// static ...; // 0x108B2080
	// static ...; // 0x108B2078
	// static ...; // 0x108B2054
	// static ...; // 0x108B204C
	// _iobuf *fpStdIn;
	// long style;
	// HWND__ *consoleWindow;
	// _iobuf *fpStdOut;
	// _iobuf *fpStdErr;
	// function call : __int32 ()
	// function call : HWND__ *()
	// function call : long (HWND__ *, __int32)
	// function call : long (HWND__ *, __int32, long)
	// function call : HMENU__ *(HWND__ *, __int32)
	// function call : __int32 (HMENU__ *, unsigned __int32, unsigned __int32)
	// function call : __int32 (HWND__ *, HWND__ *, __int32, __int32, __int32, __int32, unsigned __int32)
	todo("implement");
	_sub_108B1F00();
}

_extern void _sub_108B2100(bool);
void shell_free_console(bool dedicated) // 0x108B2100
{
	// `anonymous-namespace'::shell_free_console
	// static ...; // 0x108B229D
	// static ...; // 0x108B2294
	// static ...; // 0x108B228C
	// static ...; // 0x108B2268
	// static ...; // 0x108B2260
	// bool dedicated;
	// HWND__ *consoleWindow;
	{
		// _iobuf *fpStdIn;
		// _iobuf *fpStdOut;
		// _iobuf *fpStdErr;
	}
	// function call : HWND__ *()
	// function call : HMENU__ *(HWND__ *, __int32)
	// function call : __int32 (HMENU__ *, unsigned __int32, unsigned __int32)
	// function call : __int32 ()
	todo("implement");
	_sub_108B2100(dedicated);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template char const * s_static_string<32>::get_string() const;
template s_static_string<256>::operator char const *() const;
template s_static_string<32>::operator char const *() const;
template void s_static_string<32>::set_wchar(wchar_t const *);
