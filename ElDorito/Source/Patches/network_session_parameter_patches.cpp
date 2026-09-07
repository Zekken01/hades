/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
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
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameter_mod.hpp"
#include "Blam/networking/session/network_session_parameter_types.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/networking/session/network_session_parameters_custom.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patch.hpp"
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

class c_network_session_parameter_base;
class c_network_session_parameter_mod;
class c_network_session_parameter_type_collection;

namespace Utils {}
using namespace ::Utils;
namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void network__session_parameter_types_register_hook(c_network_session_parameter_type_collection *collection);
extern void network_session_parameter_patches_apply();

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern char const *g_session_mod_parameter_name; // 0x113547E0
	extern s_static_array<c_network_session_parameter_mod,4> g_session_mod_parameters; // 0x12466598
}
/* ---------- public code */

extern c_network_session_parameter_base* _sub_10AA88D0(c_network_session_parameter_base *const);
_inline c_network_session_parameter_base::c_network_session_parameter_base() // 0x10AA88D0
{
	mangled_x86(MANGLED_TODO, "??0c_network_session_parameter_base@@QAE@XZ");
	// c_network_session_parameter_base *const this;
	compiler_generated();
	todo("implement");
	_sub_10AA88D0(this);
}

_extern void _sub_10AA8F20(c_network_session_parameter_type_collection *);
void network__session_parameter_types_register_hook(c_network_session_parameter_type_collection *collection) // 0x10AA8F20
{
	mangled_x86(MANGLED_TODO, "?network__session_parameter_types_register_hook@@YAXPAVc_network_session_parameter_type_collection@@@Z");
	// c_network_session_parameter_type_collection *collection;
	// constexpr void (*const `network__session_parameter_types_register_hook'::`2'::network_session_parameter_types_register)(c_network_session_parameter_type_collection *); // constant == 5092848
	// function call : void (*const)(c_network_session_parameter_type_collection *)
	todo("implement");
	_sub_10AA8F20(collection);
}

extern c_network_session_parameter_mod* _sub_10AA8940(c_network_session_parameter_mod *const);
_inline c_network_session_parameter_mod::c_network_session_parameter_mod() // 0x10AA8940
{
	mangled_x86(MANGLED_TODO, "??0c_network_session_parameter_mod@@QAE@XZ");
	// c_network_session_parameter_mod *const this;
	compiler_generated();
	todo("implement");
	_sub_10AA8940(this);
}

_extern void _sub_10AA90D0();
void network_session_parameter_patches_apply() // 0x10AA90D0
{
	mangled_x86(MANGLED_TODO, "?network_session_parameter_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_10AA90D0();
}

/* ---------- private code */
