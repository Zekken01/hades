/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_time.hpp"
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
#include "mods/font_package.hpp"
#include "Patch.hpp"
#include "Pointer.hpp"
#include "Utils/Singleton.hpp"

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
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct s_game_options;
struct s_game_time_globals;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void game_time_patches_apply();

void game_time_set_rate_scale_direct_hook(float scale);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_1091B3B0();
void game_time_patches_apply() // 0x1091B3B0
{
	mangled_x86(MANGLED_TODO, "?game_time_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_1091B3B0();
}

/* ---------- private code */

_extern void _sub_1091B510(float);
void game_time_set_rate_scale_direct_hook(float scale) // 0x1091B510
{
	// `anonymous-namespace'::game_time_set_rate_scale_direct_hook
	// float scale;
	// s_game_options *options;
	// float target_tick_rate;
	// long new_tick_rate;
	// s_game_time_globals *globals;
	// function call : s_game_options *(*)()
	// function call : bool (*)()
	// function call : bool (*const)()
	todo("implement");
	_sub_1091B510(scale);
}
