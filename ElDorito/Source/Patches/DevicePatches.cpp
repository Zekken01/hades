/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/devices/device_definitions.hpp"
#include "Blam/devices/devices.hpp"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeDevice.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/GamePatches.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Pointer.hpp"
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
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class CForgeDeviceManager;
struct CForgeDeviceObjectProperties;
struct IGameSystem;
struct c_game_engine;
struct s_control_definition;
struct s_device_data;
struct s_device_definition;
struct s_device_group_datum;
struct s_machine_definition;
struct s_multiplayer_object_properties;
struct s_object_data;
struct s_player_action_context;

namespace Utils {}
using namespace ::Utils;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Devices {}
	using namespace Patches::Devices;
	namespace Game {}
	using namespace Patches::Game;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace Devices
	{
		extern void ApplyAll();
		extern bool PlayerConsiderDeviceInteraction(long player_index, long device_index, s_player_action_context *out_action_context);
	}
}

void machine_update_hook(long machine_index);
bool device_block_interaction_odst_hook(long object_index);
bool device_allows_player_interaction(long device_index, long player_index);
bool device_allows_object_interaction(long device_index, long object_index);
void device_touched_hook(long device_index, long unit_index, bool a3);
bool machine_door_test_object_hook(long machine_index, long const *object_indices, short object_indices_count);
void control_touched_hook(long device_index, long unit_index);

/* ---------- globals */

namespace Utils
{
	CForgeDeviceManager *Utils::Singleton<CForgeDeviceManager>::m_instance; // 0x1240833C
}

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Devices
	{
		_extern void _sub_108CE320();
		void ApplyAll() // 0x108CE320
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Devices@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_108CE320();
		}

		_extern bool _sub_108CED20(long, long, s_player_action_context *);
		bool PlayerConsiderDeviceInteraction(long player_index, long device_index, s_player_action_context *out_action_context) // 0x108CED20
		{
			mangled_x86(MANGLED_TODO, "?PlayerConsiderDeviceInteraction@Devices@Patches@@YA_NJJPAUs_player_action_context@@@Z");
			// s_player_action_context *out_action_context;
			// bool (*const player_consider_device_interaction)(long, long, s_player_action_context *);
			// function call : bool (*const)(long, long, s_player_action_context *)
			todo("implement");
			bool __result = _sub_108CED20(player_index, device_index, out_action_context);
			return __result;
		}
	}
}

_inline CForgeDeviceManager::CForgeDeviceManager() // 0x108CE160
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0CForgeDeviceManager@@QAE@XZ");
	// CForgeDeviceManager *const this;

	compiler_generated();
}

_inline IGameSystem::IGameSystem() // 0x108CE1C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0IGameSystem@@QAE@XZ");
	// IGameSystem *const this;

	compiler_generated();
}

_inline CForgeDeviceManager::~CForgeDeviceManager() // 0x108CE1F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1CForgeDeviceManager@@UAE@XZ");
	// CForgeDeviceManager *const this;

	compiler_generated();
}

/* ---------- private code */

_extern void _sub_108CF450(long);
void machine_update_hook(long machine_index) // 0x108CF450
{
	// `anonymous-namespace'::machine_update_hook
	// long machine_index;
	// float old_proximity_radius;
	// s_object_data *machine;
	// float old_position_time;
	// void (*const machine_update)(long);
	// EForgeDeviceType device_type;
	// CForgeDeviceManager &deviceManager;
	// s_machine_definition *machine_def;
	// CForgeDeviceObjectProperties *device_properties;
	// s_multiplayer_object_properties *properties;
	// float old_door_open_time;
	{
		// float radius;
	}
	{
		// float delayTime;
	}
	// function call : void (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void *(*const)(unsigned long, long)
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : void (*const)(long)
	todo("implement");
	_sub_108CF450(machine_index);
}

_extern bool _sub_108CF0C0(long);
bool device_block_interaction_odst_hook(long object_index) // 0x108CF0C0
{
	// `anonymous-namespace'::device_block_interaction_odst_hook
	// long object_index;
	// s_device_data *device;
	// s_device_group_datum *device_group;
	// s_device_data *parent_device;
	// s_device_definition *parent_device_definition;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	bool __result = _sub_108CF0C0(object_index);
	return __result;
}

_extern bool _sub_108CEF50(long, long);
bool device_allows_player_interaction(long device_index, long player_index) // 0x108CEF50
{
	// `anonymous-namespace'::device_allows_player_interaction
	// long player_index;
	{
		// c_game_engine *game_engine;
		{
			// s_multiplayer_object_properties *multiplayer_properties;
			{
				// short player_team;
				// bool is_neutral;
				// long (*const get_player_team_desginator)(c_game_engine *, __int32);
				// short device_team;
			}
		}
	}
	// function call : bool (*)()
	// function call : c_game_engine *(*const)()
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : long (*const)(c_game_engine *, __int32)
	todo("implement");
	bool __result = _sub_108CEF50(device_index, player_index);
	return __result;
}

_extern bool _sub_108CEE80(long, long);
bool device_allows_object_interaction(long device_index, long object_index) // 0x108CEE80
{
	// `anonymous-namespace'::device_allows_object_interaction
	// long object_index;
	{
		// long player_index;
		// long unit_index;
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	bool __result = _sub_108CEE80(device_index, object_index);
	return __result;
}

_extern void _sub_108CF270(long, long, bool);
void device_touched_hook(long device_index, long unit_index, bool a3) // 0x108CF270
{
	// `anonymous-namespace'::device_touched_hook
	// bool a3;
	// void (*const device_touched)(long, long, bool);
	// function call : void (*const)(long, long, bool)
	todo("implement");
	_sub_108CF270(device_index, unit_index, a3);
}

_extern bool _sub_108CF300(long, long const *, short);
bool machine_door_test_object_hook(long machine_index, long const *object_indices, short object_indices_count) // 0x108CF300
{
	// `anonymous-namespace'::machine_door_test_object_hook
	// static ...; // 0x108CF3DC
	// long machine_index;
	// long const *object_indices;
	// short object_indices_count;
	// bool (*const machine_door_test_object)(long, long const *, short);
	// long new_object_indices[16];
	// short new_object_indices_count;
	{
		// long i;
		{
			// long object_index;
		}
	}
	// function call : bool (*const)(long, long const *, short)
	todo("implement");
	bool __result = _sub_108CF300(machine_index, object_indices, object_indices_count);
	return __result;
}

_extern void _sub_108CEDB0(long, long);
void control_touched_hook(long device_index, long unit_index) // 0x108CEDB0
{
	// `anonymous-namespace'::control_touched_hook
	// long unit_index;
	// s_object_data *control;
	// s_control_definition *control_definition;
	// void (*const control_toggle)(long);
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(long)
	todo("implement");
	_sub_108CEDB0(device_index, unit_index);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template CForgeDeviceManager & Utils::Singleton<CForgeDeviceManager>::Instance();
