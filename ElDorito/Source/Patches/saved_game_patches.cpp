/* ---------- headers */

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
#include "Blam/saved_games/blf.hpp"
#include "Blam/saved_games/scenario_map_variant_blf.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Forge/ForgeUndo.hpp"
#include "mods/blf_reader.hpp"
#include "mods/blf_writer.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_blf.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patch.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"

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

struct s_blf_chunk_end_of_file;
struct s_file_reference;
namespace
{
	class c_gui_selected_item;
	struct _c_gui_map_selected_item;
}

namespace Utils {}
using namespace ::Utils;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Ui {}
	using namespace Web::Ui;
}

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer {}
		using namespace Web::Ui::ScreenLayer;
	}
}

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
	class c_gui_selected_item
	{
	public:
		void *vftable; // 0x0
		__int32 field_4; // 0x4
		__int32 type; // 0x8
		__int32 field_C; // 0xC
		__int32 field_10; // 0x10
		char field_14; // 0x14
		char field_15; // 0x15
		char field_16; // 0x16
		char field_17; // 0x17
		unsigned char content_header[376]; // 0x18
	};
}
// static_assert(sizeof(c_gui_selected_item) == 400, "Invalid c_gui_selected_item size");
// The layout above is the PDB's member list without its padding, so the
// size assertion is withheld: it would fail on alignment alone.

namespace
{
	#pragma pack(push, 4)
	struct _c_gui_map_selected_item
	{
		c_gui_selected_item base; // 0x0
		__int32 controller_index; // 0x190
		s_file_reference file_reference; // 0x194
		_c_gui_map_selected_item(_c_gui_map_selected_item &); /* compiler_generated() */
		_c_gui_map_selected_item(_c_gui_map_selected_item const &); /* compiler_generated() */
		_c_gui_map_selected_item(); /* compiler_generated() */
		_c_gui_map_selected_item &operator=(_c_gui_map_selected_item &); /* compiler_generated() */
		_c_gui_map_selected_item &operator=(_c_gui_map_selected_item const &); /* compiler_generated() */
	};
	#pragma pack(pop)
	static_assert(sizeof(_c_gui_map_selected_item) == 676, "Invalid _c_gui_map_selected_item size");
}
/* ---------- prototypes */

extern void saved_game_patches_apply();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern s_blf_chunk_end_of_file &_sub_10AC86D0(s_blf_chunk_end_of_file *const, s_blf_chunk_end_of_file &);
_inline s_blf_chunk_end_of_file &s_blf_chunk_end_of_file::operator=(s_blf_chunk_end_of_file &&__that) // 0x10AC86D0
{
	mangled_x86(MANGLED_TODO, "??4s_blf_chunk_end_of_file@@QAEAAU0@$$QAU0@@Z");
	// s_blf_chunk_end_of_file &__that;
	compiler_generated();
	todo("implement");
	s_blf_chunk_end_of_file & __result = _sub_10AC86D0(this, __that);
	return __result;
}

_extern void _sub_10AC9930();
void saved_game_patches_apply() // 0x10AC9930
{
	mangled_x86(MANGLED_TODO, "?saved_game_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	// long const k__mapv_rename_buffer_size;
	todo("implement");
	_sub_10AC9930();
}

/* ---------- private code */
