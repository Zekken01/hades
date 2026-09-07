/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/saved_games/blf.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/RefCounting.hpp"
#include "mods/blf_reader.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"

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
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
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

class IMod;
class IModListener;
struct s_find_file_data;
namespace
{
	class ModListener;
	struct s_levels_enumerate_async_data;
}

namespace Utils {}
using namespace ::Utils;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Maps {}
	using namespace Patches::Maps;
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

namespace
{
	class ModListener :
		public IModListener
	{
	public:
		virtual void OnModChanged(EModIndex, IMod *);
		ModListener(ModListener &); /* compiler_generated() */
		ModListener(ModListener const &); /* compiler_generated() */
		ModListener(); /* compiler_generated() */
		virtual ~ModListener(); /* compiler_generated() */
		ModListener &operator=(ModListener &); /* compiler_generated() */
		ModListener &operator=(ModListener const &); /* compiler_generated() */
	};
	static_assert(sizeof(ModListener) == 4, "Invalid ModListener size");

	struct s_levels_enumerate_async_data
	{
		unsigned long state; // 0x0
		s_find_file_data *find_data; // 0x4
	};
	static_assert(sizeof(s_levels_enumerate_async_data) == 8, "Invalid s_levels_enumerate_async_data size");
}
/* ---------- prototypes */

namespace Patches
{
	namespace Maps
	{
		extern void ApplyAll();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern char const *const k_mods_mainmenu_virtual_path; // 0x111B0700
	extern char const *const k_mods_game_virtual_path; // 0x111B0704
	extern std::vector<unsigned char,std::allocator<unsigned char> > map_file_buffer; // 0x12458E90
}
/* ---------- public code */

namespace Patches
{
	namespace Maps
	{
		_extern void _sub_10A87700();
		void ApplyAll() // 0x10A87700
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Maps@Patches@@YAXXZ");
			// procedure flags: nofpo
			// function call : void (IModListener *)
			todo("implement");
			_sub_10A87700();
		}
	}
}

/* ---------- private code */
