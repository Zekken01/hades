/* ---------- headers */

#include "Web/WebFileReadHandler.hpp"
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
#include "mods/cache_file_tag_cache.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/tag_name_dictionary.hpp"

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
#include <cef_stream.h>
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
#include <fstream>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
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

struct _Mbstatet;
namespace Web
{
	namespace Browser
	{
		class CWebFileReadHandler;
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

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

typedef unsigned long long qword;
typedef unsigned long dword;
typedef unsigned short word;
typedef unsigned long string_id;
typedef unsigned long datum_index;

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		extern CWebFileReadHandler* _sub_10CB7280(Web::Browser::CWebFileReadHandler *const, std::string const &, long long, long long);
		CWebFileReadHandler::CWebFileReadHandler(std::string const &filepath, long long offset, long long length) // 0x10CB7280
		{
			mangled_x86(MANGLED_TODO, "??0CWebFileReadHandler@Browser@Web@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_J1@Z");
			// Web::Browser::CWebFileReadHandler *const this;
			// std::string const &filepath;
			// long long offset;
			// long long length;
			{
				// std::fpos<_Mbstatet> begin;
			}
			todo("implement");
			_sub_10CB7280(this, filepath, offset, length);
		}

		CWebFileReadHandler::~CWebFileReadHandler() // 0x10CB7690
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1CWebFileReadHandler@Browser@Web@@UAE@XZ");
			// __shifted(Web::Browser::CWebFileReadHandler, 228);
			// Web::Browser::CWebFileReadHandler *const this;
		}

		unsigned __int32 CWebFileReadHandler::Read(void *ptr, unsigned __int32 size, unsigned __int32 n) // 0x10CB7B80
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Read@CWebFileReadHandler@Browser@Web@@UAEIPAXII@Z");
			// unsigned __int32 n;
			// long long chunkBytes;
			// long long remainingBytes;

			long long remaining = m_length - m_position;
			long long chunkBytes = size * n;
			if (chunkBytes > remaining)
				chunkBytes = remaining;
			m_stream.read((char *)ptr, chunkBytes);
			m_position += chunkBytes;
			return (unsigned __int32)chunkBytes;
		}

		_extern __int32 _sub_10CB7D80(Web::Browser::CWebFileReadHandler *const, long long, __int32);
		__int32 CWebFileReadHandler::Seek(long long offset, __int32 whence) // 0x10CB7D80
		{
			mangled_x86(MANGLED_TODO, "?Seek@CWebFileReadHandler@Browser@Web@@UAEH_JH@Z");
			// __int32 whence;
			todo("implement");
			__int32 __result = _sub_10CB7D80(this, offset, whence);
			return __result;
		}

		long long CWebFileReadHandler::Tell() // 0x10CB7EB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tell@CWebFileReadHandler@Browser@Web@@UAE_JXZ");
			// Web::Browser::CWebFileReadHandler *const this;

			return m_position;
		}

		__int32 CWebFileReadHandler::Eof() // 0x10CB79C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Eof@CWebFileReadHandler@Browser@Web@@UAEHXZ");
			// Web::Browser::CWebFileReadHandler *const this;

			return m_position >= m_length || m_stream.eof();
		}

		bool CWebFileReadHandler::MayBlock() // 0x10CB7B60
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?MayBlock@CWebFileReadHandler@Browser@Web@@UAE_NXZ");
			// Web::Browser::CWebFileReadHandler *const this;

			return true;
		}
	}
}

/* ---------- private code */
