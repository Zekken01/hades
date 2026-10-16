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
	std::shared_ptr<c_cache_file_tag_cache> tag_cache; // 0x123AEF10
	std::shared_ptr<Blam::Cache::StringIDCache> string_id_cache; // 0x123AEF18
	extern std::chrono::time_point<std::filesystem::_File_time_clock,std::chrono::duration<__int64,std::ratio<1,10000000> > > previous_last_write_time; // 0x123AEF20
}
using namespace hades_file_local;
/* ---------- public code */

std::shared_ptr<c_cache_file_tag_cache> c_cache_file_tags::get_open_cache() // 0x10879AA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_open_cache@c_cache_file_tags@@SA?AV?$shared_ptr@Vc_cache_file_tag_cache@@@std@@XZ");

	return tag_cache;
}

std::shared_ptr<Blam::Cache::StringIDCache> c_cache_file_tags::get_open_string_id_cache() // 0x10879B10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_open_string_id_cache@c_cache_file_tags@@SA?AV?$shared_ptr@UStringIDCache@Cache@Blam@@@std@@XZ");

	return string_id_cache;
}

bool c_cache_file_tags::open_tag_cache() // 0x10879F70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?open_tag_cache@c_cache_file_tags@@SA_NXZ");

	char const *tags_path = "maps\\tags.dat";
	char const *tags_names_path = "maps\\tag_list.csv";
	char const *string_ids_path = "maps\\string_ids.dat";
	auto last_write_time = std::filesystem::last_write_time(tags_path);
	if (tag_cache && last_write_time == previous_last_write_time)
		return true;
	close_tag_cache();
	previous_last_write_time = last_write_time;
	std::shared_ptr<Blam::Cache::StringIDCache> tmp_string_id_cache = std::make_shared<Blam::Cache::StringIDCache>();
	if (!tmp_string_id_cache->Load(string_ids_path, 0))
		return false;
	c_file_reference file(tags_path);
	c_file_open_scope scope(file, 1);
	if (!file_is_open(&file))
		return false;
	c_tag_name_dictionary tag_names;
	c_tag_names_csv_file_reader tag_name_reader(tags_names_path);
	{
		s_tag_name_entry entry;
		while (tag_name_reader.read_next(&entry))
			tag_names.add(entry.index, entry.name);
	}
	std::shared_ptr<c_cache_file_tag_cache> tmp_tag_cache = std::make_shared<c_cache_file_tag_cache>(&file, 0, std::move(tag_names));
	if (!tmp_tag_cache->initialize())
		return false;
	tag_cache = tmp_tag_cache;
	string_id_cache = tmp_string_id_cache;
	return true;
}

// mangled_x86(MANGLED_DEFAULT, "??1c_tag_names_csv_file_reader@@QAE@XZ"); no body to assert in
_inline c_tag_names_csv_file_reader::~c_tag_names_csv_file_reader() = default; // 0x10877FB0

void c_cache_file_tags::close_tag_cache() // 0x108799C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?close_tag_cache@c_cache_file_tags@@SAXXZ");

	tag_cache = nullptr;
	string_id_cache = nullptr;
	previous_last_write_time = {};
}

/* ---------- private code */

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { std::chrono::time_point<std::filesystem::_File_time_clock,std::chrono::duration<__int64,std::ratio<1,10000000> > > previous_last_write_time; }
