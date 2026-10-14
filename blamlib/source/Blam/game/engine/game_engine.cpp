/* ---------- headers */

#include "Blam/game/engine/game_engine.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/multiplayer_definitions.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

struct c_game_engine;
struct c_game_variant;
struct real_rgb_color;
struct s_game_globals;
struct s_multiplayer_globals_definition;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void *(__cdecl *const tag_get)(unsigned long, long);  // hades: added for 0x10EFFD80

extern __int32 game_engine_get_player_assists(unsigned long player_index);
extern __int32 game_engine_get_player_deaths(unsigned long player_index);
extern __int32 game_engine_get_player_kills(unsigned long player_index);
extern __int32 game_engine_get_player_score(unsigned long player_index);
extern long game_engine_get_team_designator(long player_index);
extern void game_engine_get_team_color(real_rgb_color *color, long team);
extern char const *game_engine_type_get_string(e_game_engine_type type);

/* ---------- globals */

extern c_game_variant *(*const game_engine_get_variant)(); // 0x11248CB0
extern bool (*const game_engine_is_sandbox)(); // 0x11248CAC

/* ---------- private variables */

namespace hades_file_local
{
	extern char const *k_game_engine_type_names[11]; // 0x1135965C
}
using namespace hades_file_local;
/* ---------- public code */

__int32 game_engine_get_player_assists(unsigned long player_index) // 0x10EFFC00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_get_player_assists@@YAHK@Z");
	// unsigned long player_index;
	// function call : __int32 (*)(unsigned long)

	return ((__int32(__cdecl *)(unsigned long))0x5504e0)(player_index);
}

__int32 game_engine_get_player_deaths(unsigned long player_index) // 0x10EFFC60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_get_player_deaths@@YAHK@Z");
	// unsigned long player_index;
	// function call : __int32 (*)(unsigned long)

	return ((__int32(__cdecl *const)(unsigned long))0x550580)(player_index);
}

__int32 game_engine_get_player_kills(unsigned long player_index) // 0x10EFFCC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_get_player_kills@@YAHK@Z");
	// unsigned long player_index;
	// function call : __int32 (*)(unsigned long)

	return ((__int32(__cdecl *)(unsigned long))0x550620)(player_index);
}

__int32 game_engine_get_player_score(unsigned long player_index) // 0x10EFFD20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_get_player_score@@YAHK@Z");
	// unsigned long player_index;
	// function call : __int32 (*)(unsigned long)

	return ((__int32(__cdecl *)(unsigned long))0x550720)(player_index);
}

long game_engine_get_team_designator(long player_index) // 0x10EFFEA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_get_team_designator@@YAJJ@Z");
	// long player_index;
	// long (*get_player_team_designator)(c_game_engine *, __int32);
	// c_game_engine *game_engine;
	// function call : c_game_engine *(*const)()
	// function call : long (*)(c_game_engine *, __int32)

	void *game_engine = ((void *(__cdecl *)())0x5ce150)();
	long (__thiscall *const get_team_designator)(void *, long) = *(long (__thiscall **)(void *, long))(*(unsigned char **)game_engine + 0xb4);

	if (game_engine)
		return get_team_designator(game_engine, player_index);
	else
		return -1;
}

void game_engine_get_team_color(real_rgb_color *color, long team) // 0x10EFFD80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_get_team_color@@YAXPAUreal_rgb_color@@J@Z");
	// long team;
	// s_game_globals *globals;
		// s_multiplayer_globals_definition *multiplayer_globals;
	// function call : void *(*const)(unsigned long, long)

	*color = **reinterpret_cast<real_rgb_color **>(0x189CDBC);
	s_game_globals *matg = game_globals_get();
	if (matg)
	{
		s_multiplayer_globals_definition *mulg = (s_multiplayer_globals_definition *)tag_get('mulg', matg->MultiplayerGlobals.index);
		if (mulg && team >= 0 && team < mulg->universal->team_colors.count)
		{
			*color = mulg->universal->team_colors[team].color;
		}
	}
}

char const *game_engine_type_get_string(e_game_engine_type type) // 0x10EFFF50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_type_get_string@@YAPBDW4e_game_engine_type@@@Z");
	// e_game_engine_type type;

	if (type < 0 || type >= 11)
	{
		return "unknown";
	}

	return k_game_engine_type_names[type];
}

/* ---------- private code */
