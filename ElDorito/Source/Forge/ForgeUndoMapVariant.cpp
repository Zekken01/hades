/* ---------- headers */

#include "Forge/ForgeUndoMapVariant.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_engine_candy_monitor.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/saved_games/scenario_map_variant.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeUndo.hpp"
#include "Forge/Geoemetry.hpp"
#include "mods/map_variant_loader.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Utils/EventSink.hpp"
#include "Utils/Singleton.hpp"

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
#include <functional>
#include <limits>
#include <list>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class CForgeUndoManager;
struct CForgeUndoMapVariant;
struct IForgeUndo;
struct c_candy_monitor_manager;
struct s_map_variant;
struct s_object_header;
struct s_unit_data;
struct s_variant_datum;

namespace Utils {}
using namespace ::Utils;
namespace Forge {}
using namespace ::Forge;
namespace Forge
{
	namespace Selection {}
	using namespace Forge::Selection;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

namespace Utils
{
	CForgeUndoManager *Utils::Singleton<CForgeUndoManager>::m_instance; // 0x123AC7FC
}

/* ---------- private variables */

/* ---------- public code */

extern CForgeUndoMapVariant* _sub_10864890(CForgeUndoMapVariant *const, std::string const &, s_map_variant const &);
CForgeUndoMapVariant::CForgeUndoMapVariant(std::string const &summary, s_map_variant const &mapVariant) // 0x10864890
{
	mangled_x86(MANGLED_TODO, "??0CForgeUndoMapVariant@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABUs_map_variant@@@Z");
	// s_map_variant const &mapVariant;
	todo("implement");
	_sub_10864890(this, summary, mapVariant);
}

// mangled_x86(MANGLED_DEFAULT, "??0IForgeUndo@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0s_map_variant@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0s_variant_datum@@QAE@XZ"); no body to assert in

_extern void _sub_10864F40(CForgeUndoMapVariant *const);
void CForgeUndoMapVariant::Undo() // 0x10864F40
{
	mangled_x86(MANGLED_TODO, "?Undo@CForgeUndoMapVariant@@EAEXXZ");
	// static ...; // 0x10865324
	// static ...; // 0x10865318
	// static ...; // 0x10865310
	// CForgeUndoMapVariant *const this;
	// void (*const breakable_surfaces_reset)();
	// void (*const effects_reset)();
	// c_candy_monitor_manager *candyMonitorManager;
	// long lock_flags;
	// void (*const hs_runtime_reset)();
	// s_map_variant *mapVariant;
	// void (*const game_create_objects)(long);
	// c_data_array<s_object_header> *objects;
	// void (*const lights_delete_all)();
	// void (*const device_groups_reset)();
	// bool &g_havok_garbage_collection_locked;
	// void (*const game_sound_reset_at_round_finish)();
	// void (*const object_delete_immediately)(long);
	// void (*const object_placement_create_active_zone_set_objects)(long);
	{
		// c_data_iterator<s_object_header> it;
		{
			// s_unit_data *unit;
		}
	}
	{
		// __int32 i;
	}
	// function call : long (*const)()
	// function call : s_map_variant *(*const)()
	// function call : void (*const)(long)
	// function call : void (*const)()
	// function call : void (*const)()
	// function call : void (*const)()
	// function call : void (*const)()
	// function call : void (*const)()
	// function call : void (*const)()
	// function call : void (*const)(long)
	// function call : void (*const)(long)
	// function call : void (*const)(s_map_variant *)
	// function call : long (*const)(long)
	todo("implement");
	_sub_10864F40(this);
}

// mangled_x86(MANGLED_DEFAULT, "??0CForgeUndoManager@@QAE@XZ"); no body to assert in

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template CForgeUndoManager & Utils::Singleton<CForgeUndoManager>::Instance();
template c_flags<enum e_variant_object_placement_flags,unsigned short>::c_flags();
