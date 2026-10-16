/* ---------- headers */

#include "Blam/game/game_state.hpp"
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

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <iomanip>  // hades: added for 0x10F00140
#include <sstream>  // hades: added for 0x10F00140
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

struct s_game_options;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void player_format_uid(char *string, unsigned long long id);

/* ---------- globals */

extern s_game_options *(*game_options_get)(); // 0x1135969C

/* ---------- private variables */

/* ---------- public code */

void player_format_uid(char *string, unsigned long long id) // 0x10F00140
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_format_uid@@YAXPAD_K@Z");

	if (!string)
		return;
	std::stringstream ss;
	ss << std::setw(16) << std::setfill('0') << std::hex << id << std::dec << std::setw(0);
	strncpy(string, ss.str().c_str(), 16);
	string[16] = 0;
}

/* ---------- private code */

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
s_game_options *(*game_options_get)() = reinterpret_cast<decltype(game_options_get)>(0x5322D0);
