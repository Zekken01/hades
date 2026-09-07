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

_extern void _sub_10F00140(char *, unsigned long long);
void player_format_uid(char *string, unsigned long long id) // 0x10F00140
{
	mangled_x86(MANGLED_TODO, "?player_format_uid@@YAXPAD_K@Z");
	// static ...; // 0x10F0032C
	// static ...; // 0x10F00324
	// char *string;
	// unsigned long long id;
	// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
	todo("implement");
	_sub_10F00140(string, id);
}

/* ---------- private code */
