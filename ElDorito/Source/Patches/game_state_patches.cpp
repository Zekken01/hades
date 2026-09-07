/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Patch.hpp"
#include "Pointer.hpp"
#include "Utils/String.hpp"

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
#include <utility>
#include <vector>

namespace Utils {}
using namespace ::Utils;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

//struct ai_initialize_for_saved_game_hook::__l2::s_ai_mission_critical_actor
//{
//	long unit_index; // 0x0
//	long field_04; // 0x4
//	long field_08; // 0x8
//	long field_0C; // 0xC
//};
//static_assert(sizeof(ai_initialize_for_saved_game_hook::__l2::s_ai_mission_critical_actor) == 16, "Invalid ai_initialize_for_saved_game_hook::__l2::s_ai_mission_critical_actor size");

/* ---------- prototypes */

extern void game_state_patches_apply();

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern wchar_t const *k_game_state_path; // 0x113533A0
	extern wchar_t const *k_game_state_filename; // 0x113533A4
	extern wchar_t const *k_game_state_header_filename; // 0x113533A8
	extern void **const global_game_state_data; // 0x11197A30
}
/* ---------- public code */

_extern void _sub_10919BE0();
void game_state_patches_apply() // 0x10919BE0
{
	mangled_x86(MANGLED_TODO, "?game_state_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_10919BE0();
}

/* ---------- private code */
