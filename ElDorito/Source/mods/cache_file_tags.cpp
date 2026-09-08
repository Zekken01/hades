/* ---------- headers */

#include "mods/cache_file_tags.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/Cache/StringIdCache.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/tag_name_csv_reader.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patches/CustomPackets.hpp"

#include <Windows.h>
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
#include <exception>
#include <filesystem>
#include <forward_list>
#include <fstream>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <optional>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_cache_file_tag_cache;
class c_file_open_scope;
class c_file_reference;
class c_tag_name_dictionary;
class c_tag_names_csv_file_reader;
struct c_cache_file_tags;
struct s_tag_name_entry;
namespace Blam
{
	namespace Cache
	{
		struct StringIDCache;
	}
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

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern std::shared_ptr<c_cache_file_tag_cache> tag_cache; // 0x123AEF10
	extern std::shared_ptr<Blam::Cache::StringIDCache> string_id_cache; // 0x123AEF18
	extern std::chrono::time_point<std::filesystem::_File_time_clock,std::chrono::duration<__int64,std::ratio<1,10000000> > > previous_last_write_time; // 0x123AEF20
}
using namespace hades_file_local;
/* ---------- public code */

extern std::shared_ptr<c_cache_file_tag_cache> _sub_10879AA0();
std::shared_ptr<c_cache_file_tag_cache> c_cache_file_tags::get_open_cache() // 0x10879AA0
{
	mangled_x86(MANGLED_TODO, "?get_open_cache@c_cache_file_tags@@SA?AV?$shared_ptr@Vc_cache_file_tag_cache@@@std@@XZ");
	// procedure flags: nofpo
	todo("implement");
	std::shared_ptr<c_cache_file_tag_cache> __result = _sub_10879AA0();
	return __result;
}

extern std::shared_ptr<Blam::Cache::StringIDCache> _sub_10879B10();
std::shared_ptr<Blam::Cache::StringIDCache> c_cache_file_tags::get_open_string_id_cache() // 0x10879B10
{
	mangled_x86(MANGLED_TODO, "?get_open_string_id_cache@c_cache_file_tags@@SA?AV?$shared_ptr@UStringIDCache@Cache@Blam@@@std@@XZ");
	// procedure flags: nofpo
	todo("implement");
	std::shared_ptr<Blam::Cache::StringIDCache> __result = _sub_10879B10();
	return __result;
}

_extern bool _sub_10879F70();
bool c_cache_file_tags::open_tag_cache() // 0x10879F70
{
	mangled_x86(MANGLED_TODO, "?open_tag_cache@c_cache_file_tags@@SA_NXZ");
	// procedure flags: nofpo
	// static ...; // 0x1087A435
	// static ...; // 0x1087A425
	// static ...; // 0x1087A411
	// static ...; // 0x1087A40C
	// static ...; // 0x1087A406
	// static ...; // 0x1087A3FC
	// static ...; // 0x1087A3EC
	// static ...; // 0x1087A3E6
	// static ...; // 0x1087A3D8
	// static ...; // 0x1087A36C
	// static ...; // 0x1087A364
	// std::shared_ptr<c_cache_file_tag_cache> tmp_tag_cache;
	// char const *tags_names_path;
	// c_tag_names_csv_file_reader tag_name_reader;
	// std::shared_ptr<Blam::Cache::StringIDCache> tmp_string_id_cache;
	// char const *tags_path;
	// std::chrono::time_point<std::filesystem::_File_time_clock,std::chrono::duration<__int64,std::ratio<1,10000000> > > last_write_time;
	// char const *string_ids_path;
	// c_file_reference file;
	// c_tag_name_dictionary tag_names;
	// c_file_open_scope scope;
	{
		// s_tag_name_entry entry;
	}
	todo("implement");
	bool __result = _sub_10879F70();
	return __result;
}

_inline c_tag_names_csv_file_reader::~c_tag_names_csv_file_reader() // 0x10877FB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1c_tag_names_csv_file_reader@@QAE@XZ");
	// c_tag_names_csv_file_reader *const this;

	compiler_generated();
}

_extern void _sub_108799C0();
void c_cache_file_tags::close_tag_cache() // 0x108799C0
{
	mangled_x86(MANGLED_TODO, "?close_tag_cache@c_cache_file_tags@@SAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_108799C0();
}

/* ---------- private code */
