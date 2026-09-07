/* ---------- headers */

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
#include "mods/font_package.hpp"
#include "Modules/ModuleCampaign.hpp"
#include "Modules/ModuleGame.hpp"
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
namespace Modules
{
	class ModuleCampaign;
	class ModuleGame;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void life_cycle_patches_apply();

bool begin_load_map_game_options_verify_hook(s_game_options *options);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_1091F4B0();
void life_cycle_patches_apply() // 0x1091F4B0
{
	mangled_x86(MANGLED_TODO, "?life_cycle_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_1091F4B0();
}

/* ---------- private code */

_extern bool _sub_1091F420(s_game_options *);
bool begin_load_map_game_options_verify_hook(s_game_options *options) // 0x1091F420
{
	// `anonymous-namespace'::begin_load_map_game_options_verify_hook
	// s_game_options *options;
	// Modules::ModuleCampaign *moduleCampaign;
	// Modules::ModuleGame *moduleGame;
	todo("implement");
	bool __result = _sub_1091F420(options);
	return __result;
}
