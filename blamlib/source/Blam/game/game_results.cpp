/* ---------- headers */

#include "Blam/game/game_results.hpp"
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
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct s_game_results_events;
struct s_game_results_player_statistics;
struct s_game_results_player_vs_player_statistics;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern s_game_results_player_statistics *game_results_get_player_stats(__int32 player_index);
extern s_game_results_player_vs_player_statistics *game_results_get_player_vs_player_stats(__int32 player_index);
extern s_game_results_events *game_results_get_event(__int32 event_index);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern s_game_results_player_statistics *_sub_10F1D300(__int32);
s_game_results_player_statistics *game_results_get_player_stats(__int32 player_index) // 0x10F1D300
{
	mangled_x86(MANGLED_TODO, "?game_results_get_player_stats@@YAPAUs_game_results_player_statistics@@H@Z");
	// __int32 player_index;
	todo("implement");
	s_game_results_player_statistics * __result = _sub_10F1D300(player_index);
	return __result;
}

extern s_game_results_player_vs_player_statistics *_sub_10F1D360(__int32);
s_game_results_player_vs_player_statistics *game_results_get_player_vs_player_stats(__int32 player_index) // 0x10F1D360
{
	mangled_x86(MANGLED_TODO, "?game_results_get_player_vs_player_stats@@YAPAUs_game_results_player_vs_player_statistics@@H@Z");
	// __int32 player_index;
	todo("implement");
	s_game_results_player_vs_player_statistics * __result = _sub_10F1D360(player_index);
	return __result;
}

extern s_game_results_events *_sub_10F1D2B0(__int32);
s_game_results_events *game_results_get_event(__int32 event_index) // 0x10F1D2B0
{
	mangled_x86(MANGLED_TODO, "?game_results_get_event@@YAPAUs_game_results_events@@H@Z");
	// __int32 event_index;
	todo("implement");
	s_game_results_events * __result = _sub_10F1D2B0(event_index);
	return __result;
}

/* ---------- private code */
