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

namespace Forge::Selection { void Clear(); }  // hades: added for 0x10864F40
extern s_map_variant *(*const game_engine_get_runtime_map_variant)();  // hades: added for 0x10864F40
extern c_data_array<s_object_header> *object_headers_get();  // hades: added for 0x10864F40

/* ---------- globals */

namespace Utils
{
	CForgeUndoManager *Utils::Singleton<CForgeUndoManager>::m_instance; // 0x123AC7FC
}

/* ---------- private variables */

/* ---------- public code */

CForgeUndoMapVariant::CForgeUndoMapVariant(std::string const &summary, s_map_variant const &mapVariant) : m_summary(summary) /* hades-mem-init:  */ // 0x10864890
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0CForgeUndoMapVariant@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABUs_map_variant@@@Z");

	memcpy(&m_storedMapVariant, &mapVariant, sizeof(s_map_variant));
}

// mangled_x86(MANGLED_DEFAULT, "??0IForgeUndo@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0s_map_variant@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0s_variant_datum@@QAE@XZ"); no body to assert in

void CForgeUndoMapVariant::Undo() // 0x10864F40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Undo@CForgeUndoMapVariant@@EAEXXZ");

	void (*const breakable_surfaces_reset)() = reinterpret_cast<void (*)()>(0x56B960);
	void (*const effects_reset)() = reinterpret_cast<void (*)()>(0x5BD040);
	void (*const lights_delete_all)() = reinterpret_cast<void (*)()>(0xB933E0);
	void (*const device_groups_reset)() = reinterpret_cast<void (*)()>(0xB9E450);
	void (*const hs_runtime_reset)() = reinterpret_cast<void (*)()>(0x5D9770);
	void (*const game_sound_reset_at_round_finish)() = reinterpret_cast<void (*)()>(0x597EA0);
	void (*const object_placement_create_active_zone_set_objects)(long) = reinterpret_cast<void (*)(long)>(0x530B30);
	void (*const game_create_objects)(long) = reinterpret_cast<void (*)(long)>(0xB591C0);
	void (*const object_delete_immediately)(long) = reinterpret_cast<void (*)(long)>(0xB2CF40);
	bool &g_havok_garbage_collection_locked = *reinterpret_cast<bool *>(0x18A23C3);
	long lock_flags = ((long (*)())0x504D20)();
	g_havok_garbage_collection_locked = true;
	Forge::Selection::Clear();
	s_map_variant *mapVariant = game_engine_get_runtime_map_variant();
	Utils::Singleton<CForgeUndoManager>::Instance().AddUndo(m_summary, std::make_shared<CForgeUndoMapVariant>(m_summary, *mapVariant));
	c_candy_monitor_manager *candyMonitorManager = get_candy_monitor_manager();
	candyMonitorManager->reset();
	c_data_array<s_object_header> *objects = object_headers_get();
	for (c_data_iterator<s_object_header> it = objects->begin(); it != objects->end(); ++it)
	{
		if (it.current_datum_index == -1 || it->data->parent_object_index != -1)
			continue;
		if (it->type == _object_type_biped)
		{
			s_unit_data *unit = (s_unit_data *)it->data;
			if (*(long *)((unsigned char *)unit + 0x198) != -1 || *(long *)((unsigned char *)unit + 0x19C) != -1 || *(long *)((unsigned char *)unit + 0x4A8) != -1)
				continue;
		}
		object_delete_immediately(it.current_datum_index);
	}
	breakable_surfaces_reset();
	effects_reset();
	lights_delete_all();
	device_groups_reset();
	hs_runtime_reset();
	game_sound_reset_at_round_finish();
	memcpy(mapVariant, &m_storedMapVariant, sizeof(s_map_variant));
	for (__int32 i = 0; i < _countof(mapVariant->objects); i++)
	{
		mapVariant->objects[i].editor_object_index = -1;
		mapVariant->objects[i].object_index = -1;
	}
	object_placement_create_active_zone_set_objects(1);
	game_create_objects(0);
	((void (__thiscall *)(s_map_variant *))0x585EE0)(mapVariant);
	g_havok_garbage_collection_locked = false;
	((void (*)(long))0x507940)(lock_flags);
}

// mangled_x86(MANGLED_DEFAULT, "??0CForgeUndoManager@@QAE@XZ"); no body to assert in

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template CForgeUndoManager & Utils::Singleton<CForgeUndoManager>::Instance();
template c_flags<enum e_variant_object_placement_flags,unsigned short>::c_flags();
