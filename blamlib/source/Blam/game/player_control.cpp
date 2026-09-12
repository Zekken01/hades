/* ---------- headers */

#include "Blam/game/player_control.hpp"
#include "hades/hades.h"

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
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct s_player_control_input_state;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern s_player_control_input_state *player_control_input_get(long user_index);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

s_player_control_input_state *player_control_input_get(long user_index) // 0x10F19200
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_control_input_get@@YAPAUs_player_control_input_state@@J@Z");
	// long user_index;

	return &tls_getd().player_control_globals->player_input[user_index];
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool s_static_array<s_player_control_input_state,4>::valid(__int32);
template s_player_control_input_state & s_static_array<s_player_control_input_state,4>::operator[](long);
