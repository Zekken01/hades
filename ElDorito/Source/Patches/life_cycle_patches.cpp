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

void life_cycle_patches_apply() // 0x1091F4B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?life_cycle_patches_apply@@YAXXZ");
	// procedure flags: nofpo

	Hook(0x91F77, begin_load_map_game_options_verify_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
}

/* ---------- private code */

bool begin_load_map_game_options_verify_hook(s_game_options *options) // 0x1091F420
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?begin_load_map_game_options_verify_hook@@YA_NPAUs_game_options@@@Z");
	// `anonymous-namespace'::begin_load_map_game_options_verify_hook
	// s_game_options *options;
	// Modules::ModuleCampaign *moduleCampaign;
	// Modules::ModuleGame *moduleGame;

	Modules::ModuleCampaign *moduleCampaign = &Modules::ModuleCampaign::Instance();
	Modules::ModuleGame *moduleGame = &Modules::ModuleGame::Instance();

	options->tick_rate = (short)moduleGame->VarTickRateClient->ValueInt;

	if (options->tick_rate < 1)
		options->tick_rate = 1;

	return true;
}
