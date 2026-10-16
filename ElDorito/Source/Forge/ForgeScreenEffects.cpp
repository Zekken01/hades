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

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const player_mapping_get_player_by_input_user = reinterpret_cast<unsigned long (*)(long)>(0x589C30);
}

extern s_multiplayer_object_properties *(*const object_get_multiplayer)(unsigned long);  // hades: added for 0x106D1C10
extern s_object_data *object_get(unsigned long object_index);  // hades: added for 0x106D1C10

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Forge
{
	void CForgeScreenEffects::ApplyScreenEffectOverride(long output_user_index, long datum_index, s_single_screen_effect_definition *definition) // 0x106D1C10
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyScreenEffectOverride@CForgeScreenEffects@Forge@@SAXJJPAUs_single_screen_effect_definition@@@Z");

		s_screen_effect_datum *screenEffectDatum = tls_getd().screen_effects->try_and_get(datum_index);
		s_object_data *object = object_get(screenEffectDatum->attach_object_index);
		if (!object || object->map_variant_index == -1)
			return;
		s_multiplayer_object_properties *props = object_get_multiplayer(screenEffectDatum->attach_object_index);
		Forge::ForgeScreenFxProperties *properties = (Forge::ForgeScreenFxProperties *)&props->boundry_width;
		if (!properties)
			return;
		long playerIndex = eldorado::player_mapping_get_player_by_input_user(output_user_index);
		if (playerIndex == -1)
			return;
		s_player_datum *player = players_get()->try_and_get(playerIndex);
		if (!player)
			return;
		if (player->configuration.host.team != (short)props->team_designator && (short)props->team_designator != 8)
		{
			definition->maximum_distance = 0.0f;
			return;
		}
		definition->maximum_distance = properties->MaximumDistance / 255.0f * 255.0f;
		definition->settings.exposure_boost = properties->LightIntensity / 255.0f * 5.0f;
		definition->settings.saturation = properties->Saturation / 255.0f;
		definition->settings.desaturation = properties->Desaturation / 255.0f;
		definition->settings.hue_left = properties->Hue / 255.0f * 360.0f;
		definition->settings.contrast_enhance = properties->GammaIncrease / 255.0f;
		definition->settings.gamma_enhance = properties->GammaDecrease / 255.0f;
		definition->settings.color_filter.red = properties->ColorFilterR / 255.0f;
		definition->settings.color_filter.green = properties->ColorFilterG / 255.0f;
		definition->settings.color_filter.blue = properties->ColorFilterB / 255.0f;
		definition->settings.color_floor.red = properties->ColorFloorR / 255.0f;
		definition->settings.color_floor.green = properties->ColorFloorG / 255.0f;
		definition->settings.color_floor.blue = properties->ColorFloorB / 255.0f;
		definition->settings.vision_mode = properties->Tracing / 100.0f;
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template s_player_datum * c_data_array<s_player_datum>::try_and_get(unsigned long);
template s_screen_effect_datum * c_data_array<s_screen_effect_datum>::try_and_get(unsigned long);
