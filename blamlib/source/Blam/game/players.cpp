/* ---------- headers */

#include "Blam/game/players.hpp"
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
#include "Blam/memory/data.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

struct s_data_array;
struct s_player_datum;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern c_data_array<s_player_datum> *players_get();
extern s_player_datum *player_get(unsigned long player_index);

/* ---------- globals */

extern void (*const player_refresh_object_appearance_full)(long, long); // 0x11248E14

/* ---------- private variables */

/* ---------- public code */

extern c_data_array<s_player_datum> *_sub_10F00570();
c_data_array<s_player_datum> *players_get() // 0x10F00570
{
	mangled_x86(MANGLED_TODO, "?players_get@@YAPAV?$c_data_array@Us_player_datum@@@@XZ");
	// procedure flags: nofpo
	todo("implement");
	c_data_array<s_player_datum> * __result = _sub_10F00570();
	return __result;
}

extern s_player_datum *_sub_10F004E0(unsigned long);
s_player_datum *player_get(unsigned long player_index) // 0x10F004E0
{
	mangled_x86(MANGLED_TODO, "?player_get@@YAPAUs_player_datum@@K@Z");
	// unsigned long player_index;
	// function call : void *(*const)(s_data_array const *, unsigned long)
	todo("implement");
	s_player_datum * __result = _sub_10F004E0(player_index);
	return __result;
}

/* ---------- private code */
