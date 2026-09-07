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

extern s_player_control_input_state *_sub_10F19200(long);
s_player_control_input_state *player_control_input_get(long user_index) // 0x10F19200
{
	mangled_x86(MANGLED_TODO, "?player_control_input_get@@YAPAUs_player_control_input_state@@J@Z");
	// long user_index;
	todo("implement");
	s_player_control_input_state * __result = _sub_10F19200(user_index);
	return __result;
}

/* ---------- private code */
