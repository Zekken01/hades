/* ---------- headers */

#include "mods/map_load_crash_recovery_helper.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "ElDorito.hpp"
#include "mods/font_package.hpp"
#include "Pointer.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

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
#include <deque>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <fstream>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
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
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_map_load_crash_recovery_helper;
struct s_game_options;

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern char const *const kMapLoadTempFile; // 0x11181B88
}
using namespace hades_file_local;
/* ---------- public code */

_extern void _sub_107876B0(c_map_load_crash_recovery_helper *const);
void c_map_load_crash_recovery_helper::map_load_start() // 0x107876B0
{
	mangled_x86(MANGLED_TODO, "?map_load_start@c_map_load_crash_recovery_helper@@QAEXXZ");
	// c_map_load_crash_recovery_helper *const this;
	// s_game_options *const intermediate_game_options;
	// function call : __int32 ()
	todo("implement");
	_sub_107876B0(this);
}

_extern void _sub_10787660(c_map_load_crash_recovery_helper *const);
void c_map_load_crash_recovery_helper::map_load_end() // 0x10787660
{
	mangled_x86(MANGLED_TODO, "?map_load_end@c_map_load_crash_recovery_helper@@QAEXXZ");
	// c_map_load_crash_recovery_helper *const this;
	todo("implement");
	_sub_10787660(this);
}

_extern void _sub_10787D00(c_map_load_crash_recovery_helper *const);
void c_map_load_crash_recovery_helper::tick() // 0x10787D00
{
	mangled_x86(MANGLED_TODO, "?tick@c_map_load_crash_recovery_helper@@QAEXXZ");
	// c_map_load_crash_recovery_helper *const this;
	todo("implement");
	_sub_10787D00(this);
}

_extern void _sub_10787BF0(c_map_load_crash_recovery_helper *const);
void c_map_load_crash_recovery_helper::shutdown() // 0x10787BF0
{
	mangled_x86(MANGLED_TODO, "?shutdown@c_map_load_crash_recovery_helper@@QAEXXZ");
	// c_map_load_crash_recovery_helper *const this;
	todo("implement");
	_sub_10787BF0(this);
}

_extern void _sub_107875B0(c_map_load_crash_recovery_helper *const);
void c_map_load_crash_recovery_helper::dirty_disk() // 0x107875B0
{
	mangled_x86(MANGLED_TODO, "?dirty_disk@c_map_load_crash_recovery_helper@@QAEXXZ");
	// c_map_load_crash_recovery_helper *const this;
	todo("implement");
	_sub_107875B0(this);
}

/* ---------- private code */
