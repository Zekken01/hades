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
		_extern void _sub_10AD2060();
		void ApplyAfterTagsLoaded() // 0x10AD2060
		{
			mangled_x86(MANGLED_TODO, "?ApplyAfterTagsLoaded@Tweaks@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10AD2060();
		}

		_extern void _sub_10AD22B0(bool);
		void EnableHitmarkers(bool enabled) // 0x10AD22B0
		{
			mangled_x86(MANGLED_TODO, "?EnableHitmarkers@Tweaks@Patches@@YAX_N@Z");
			// bool enabled;
			todo("implement");
			_sub_10AD22B0(enabled);
		}
	}
}

/* ---------- private code */

_extern void _sub_10AD2100();
void DisableReactorFog() // 0x10AD2100
{
	// `anonymous-namespace'::DisableReactorFog
	// procedure flags: nofpo
	// static ...; // 0x10AD224C
	// static ...; // 0x10AD2240
	// static ...; // 0x10AD2238
	// s_tag_iterator iterator;
	{
		// long tag_index;
		{
			// s_scenario *scnrDefinition;
		}
	}
	// function call : void (*const)(s_tag_iterator *, long)
	// function call : long (*const)(s_tag_iterator *)
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	_sub_10AD2100();
}

_extern void _sub_10AD2300(bool);
void EnableHitmarkersInternal(bool enabled) // 0x10AD2300
{
	// `anonymous-namespace'::EnableHitmarkersInternal
	// bool enabled;
	// bool forceDisabled;
	// s_game_globals *matgDefinition;
	{
		// c_tag_block<s_game_globals_player_representation> &<range>$L0;
		// s_game_globals_player_representation *<begin>$L0;
		// s_game_globals_player_representation *<end>$L0;
		{
			// s_game_globals_player_representation &representation;
			{
				// s_chud_definition *chudDefinition;
				// s_biped_definition *bipdDefinition;
				{
					// s_chud_widget_collection *<end>$L1;
					// s_chud_widget_collection *<begin>$L1;
					// c_tag_block<s_chud_widget_collection> &<range>$L1;
					{
						// s_chud_widget_collection &hudWidget;
					}
				}
			}
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	_sub_10AD2300(enabled);
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
