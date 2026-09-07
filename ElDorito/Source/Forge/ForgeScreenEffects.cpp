/* ---------- headers */

#include "Forge/ForgeScreenEffects.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeObjectProperties.hpp"
#include "Forge/Geoemetry.hpp"

/* ---------- forward declarations */

struct s_multiplayer_object_properties;
struct s_object_data;
struct s_player_datum;
struct s_screen_effect_datum;
struct s_single_screen_effect_definition;
namespace Forge
{
	struct CForgeScreenEffects;
	struct ForgeScreenFxProperties;
}

namespace Forge {}
using namespace ::Forge;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Forge
{
	_extern void _sub_106D1C10(long, long, s_single_screen_effect_definition *);
	void CForgeScreenEffects::ApplyScreenEffectOverride(long output_user_index, long datum_index, s_single_screen_effect_definition *definition) // 0x106D1C10
	{
		mangled_x86(MANGLED_TODO, "?ApplyScreenEffectOverride@CForgeScreenEffects@Forge@@SAXJJPAUs_single_screen_effect_definition@@@Z");
		// s_single_screen_effect_definition *definition;
		// s_player_datum *player;
		// s_object_data *object;
		// s_screen_effect_datum *screenEffectDatum;
		// long playerIndex;
		// s_multiplayer_object_properties *props;
		// Forge::ForgeScreenFxProperties *properties;
		// function call : s_multiplayer_object_properties *(*const)(unsigned long)
		// function call : unsigned long (*const)(long)
		todo("implement");
		_sub_106D1C10(output_user_index, datum_index, definition);
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template s_player_datum * c_data_array<s_player_datum>::try_and_get(unsigned long);
template s_screen_effect_datum * c_data_array<s_screen_effect_datum>::try_and_get(unsigned long);
