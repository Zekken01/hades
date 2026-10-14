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

#include "Modules/ModuleGame.hpp"  // hades: added for 0x1091B510
#include "Modules/ModuleCampaign.hpp"  // hades: added for 0x1091B510
extern s_game_options *(*game_options_get)();  // hades: added for 0x1091B510
extern bool (*game_is_campaign)();  // hades: added for 0x1091B510

extern void game_time_patches_apply();

void game_time_set_rate_scale_direct_hook(float scale);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

void game_time_patches_apply() // 0x1091B3B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_time_patches_apply@@YAXXZ");
	// procedure flags: nofpo

	Hook(0x165110, game_time_set_rate_scale_direct_hook).Apply();
}

/* ---------- private code */

void game_time_set_rate_scale_direct_hook(float scale) // 0x1091B510
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_time_set_rate_scale_direct_hook@@YAXM@Z");
	// `anonymous-namespace'::game_time_set_rate_scale_direct_hook
	// float scale;
	// s_game_options *options;
	// float target_tick_rate;
	// long new_tick_rate;
	// s_game_time_globals *globals;
	// function call : s_game_options *(*)()
	// function call : bool (*)()
	// function call : bool (*const)()

	s_game_options *options = game_options_get();
	if (scale < 0.00001f)
		scale = 0.00001f;

	s_game_time_globals *globals = game_time_get_globals();
	float target_tick_rate = (float)Modules::ModuleGame::Instance().VarTickRateClient->ValueInt;
	if (game_is_campaign() && ((bool (__cdecl *)())0x67D270)())
		target_tick_rate = (float)Modules::ModuleCampaign::Instance().VarCinematicFrameRateClient->ValueInt;

	long new_tick_rate = (long)floorf(target_tick_rate / scale + 0.5f);
	globals->tick_rate = new_tick_rate;
	globals->tick_length = 1.0 / (float)new_tick_rate;
	globals->game_speed = target_tick_rate / new_tick_rate;
}
