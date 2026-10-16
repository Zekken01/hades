/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cache/tag_iterator.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/interface/chud/chud.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/biped_definitions.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patches/Ui.hpp"
#include "ThirdParty/rapidjson/document.h"
#include "Utils/Singleton.hpp"

#include "Modules/ModuleTweaks.hpp"  // hades: added for 0x10AD2060
#include "Modules/ModuleServer.hpp"  // hades: added for 0x10AD2060

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <limits>
#include <mutex>
#include <ratio>
#include <stdexcept>
#include <stop_token>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

struct begin;
struct end;
struct s_biped_definition;
struct s_chud_definition;
struct s_chud_widget_collection;
struct s_game_globals;
struct s_game_globals_player_representation;
struct s_scenario;
struct s_tag_iterator;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Tweaks {}
	using namespace Patches::Tweaks;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern bool tags_loaded();  // hades: added for 0x10AD2300
#include "Utils/Logger.hpp"  // hades: added for 0x10AD2300

extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x10AD2100

namespace Patches
{
	namespace Tweaks
	{
		extern void ApplyAfterTagsLoaded();
		extern void EnableHitmarkers(bool enabled);
	}
}

void DisableReactorFog();
void EnableHitmarkersInternal(bool enabled);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern bool tagsloaded; // 0x12467418
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Tweaks
	{
		void ApplyAfterTagsLoaded() // 0x10AD2060
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAfterTagsLoaded@Tweaks@Patches@@YAXXZ");

			tagsloaded = true;
			if (Utils::Singleton<Modules::ModuleTweaks>::Instance().VarDisableReactorFog->ValueInt)
			{
				DisableReactorFog();
			}

			EnableHitmarkers(Utils::Singleton<Modules::ModuleServer>::Instance().VarHitMarkersEnabledClient->ValueInt);
		}

		void EnableHitmarkers(bool enabled) // 0x10AD22B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?EnableHitmarkers@Tweaks@Patches@@YAX_N@Z");

			EnableHitmarkersInternal(enabled);
		}
	}
}

/* ---------- private code */

void DisableReactorFog() // 0x10AD2100
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DisableReactorFog@@YAXXZ");

	static void (*const tag_iterator_new)(s_tag_iterator *, long) = reinterpret_cast<void (*)(s_tag_iterator *, long)>(0x5033E0);
	static long (*const tag_iterator_next)(s_tag_iterator *) = reinterpret_cast<long (*)(s_tag_iterator *)>(0x503400);
	s_tag_iterator iterator;
	tag_iterator_new(&iterator, 'scnr');
	for (long tag_index; (tag_index = tag_iterator_next(&iterator)) != -1; )
	{
		s_scenario *scnrDefinition = (s_scenario *)tag_get('scnr', tag_index);
		if (scnrDefinition && scnrDefinition->map_id == 700)
		{
			*(short *)&scnrDefinition->effect_scenery[1] = -1;
			*(short *)&scnrDefinition->effect_scenery[2] = -1;
			*(short *)&scnrDefinition->effect_scenery[61] = -1;
		}
	}
}

void EnableHitmarkersInternal(bool enabled) // 0x10AD2300
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?EnableHitmarkersInternal@@YAX_N@Z");

	bool forceDisabled = Utils::Singleton<Modules::ModuleTweaks>::Instance().VarDisableHitMarkers->ValueInt != 0;
	if (!tags_loaded())
		return;
	s_game_globals *matgDefinition = game_globals_get();
	if (!matgDefinition)
		return;
	if (matgDefinition->PlayerRepresentation.count < 1)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Debug, Utils::LogLevel::Warning, "no player representations defined in tag 'global\\globals'!");
		return;
	}
	for (s_game_globals_player_representation &representation : matgDefinition->PlayerRepresentation)
	{
		s_biped_definition *bipdDefinition = (s_biped_definition *)tag_get('bipd', representation.ThirdPersonUnit.index);
		if (!bipdDefinition)
			continue;
		if (bipdDefinition->hud_interfaces.count < 1 && bipdDefinition->hud_interfaces[0].unit_hud_interface.index != -1)
			continue;
		s_chud_definition *chudDefinition = (s_chud_definition *)tag_get('chdt', bipdDefinition->hud_interfaces[0].unit_hud_interface.index);
		if (!chudDefinition)
			continue;
		for (s_chud_widget_collection &hudWidget : chudDefinition->widgets)
		{
			if (hudWidget.name == 0x2AAD)
			{
				if (enabled && !forceDisabled)
				{
					hudWidget.placement[0].scale_x = 1.75f;
					hudWidget.placement[0].scale_y = 1.75f;
				}
				else
				{
					hudWidget.placement[0].scale_x = 0.0f;
					hudWidget.placement[0].scale_y = 0.0f;
				}
				break;
			}
		}
	}
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_scenario_effect_scenery>::try_get_element(__int32, s_scenario_effect_scenery **) const;
template bool c_tag_block<s_unit_hud_interface_definition>::try_get_element(__int32, s_unit_hud_interface_definition **) const;
template s_chud_widget_collection * c_tag_block<s_chud_widget_collection>::begin();
template s_chud_widget_collection * c_tag_block<s_chud_widget_collection>::end();
template s_game_globals_player_representation * c_tag_block<s_game_globals_player_representation>::begin();
template s_game_globals_player_representation * c_tag_block<s_game_globals_player_representation>::end();
template s_scenario_effect_scenery & c_tag_block<s_scenario_effect_scenery>::operator[](__int32);
template s_scenario_effect_scenery * c_tag_block<s_scenario_effect_scenery>::get_element(__int32) const;
template s_unit_hud_interface_definition & c_tag_block<s_unit_hud_interface_definition>::operator[](__int32);
template s_unit_hud_interface_definition * c_tag_block<s_unit_hud_interface_definition>::get_element(__int32) const;

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { bool tagsloaded; }
