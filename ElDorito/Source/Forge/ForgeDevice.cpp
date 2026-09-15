/* ---------- headers */

#include "Forge/ForgeDevice.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/devices/device_definitions.hpp"
#include "Blam/devices/devices.hpp"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/Reforge.hpp"
#include "Patches/GamePatches.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <type_traits>

/* ---------- forward declarations */

class CForgeDeviceManager;
struct CForgeDeviceObjectProperties;
struct c_game_engine;
struct s_device_data;
struct s_device_group_datum;
struct s_machine_definition;
struct s_multiplayer_object_properties;
struct s_object_header;
namespace hades_file_local
{
	struct SDeviceChannel;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Game {}
	using namespace Patches::Game;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct SDeviceChannel
	{
		unsigned long powerGroupIndex; // 0x0
		unsigned long positionGroupIndex; // 0x4
	};
	static_assert(sizeof(SDeviceChannel) == 8, "Invalid SDeviceChannel size");

}
using namespace hades_file_local;
/* ---------- prototypes */

extern s_multiplayer_object_properties *(*const object_get_multiplayer)(unsigned long);  // hades: added for 0x108610C0

void UpdateDevice(unsigned long objectIndex);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern std::array<SDeviceChannel,32> channels; // 0x123AC6C8
	extern bool shouldReset; // 0x123AC7C8
}
using namespace hades_file_local;
/* ---------- public code */

_extern void _sub_10860FE0(CForgeDeviceManager *const);
void CForgeDeviceManager::InitializeForNewMap() // 0x10860FE0
{
	mangled_x86(MANGLED_TODO, "?InitializeForNewMap@CForgeDeviceManager@@EAEXXZ");
	// CForgeDeviceManager *const this;
	{
		// __int32 i;
		{
			// SDeviceChannel &channel;
		}
	}
	// function call : c_game_engine *(*const)()
	todo("implement");
	_sub_10860FE0(this);
}

_extern void _sub_10861180(CForgeDeviceManager *const);
void CForgeDeviceManager::Update() // 0x10861180
{
	mangled_x86(MANGLED_TODO, "?Update@CForgeDeviceManager@@EAEXXZ");
	// static ...; // 0x108612C4
	// static ...; // 0x108612B8
	// static ...; // 0x108612B0
	// CForgeDeviceManager *const this;
	// bool (*const game_engine_in_round)();
	{
		// c_data_array<s_object_header> *objectHeaders;
		{
			// c_data_iterator<s_object_header> it;
		}
	}
	// function call : c_game_engine *(*const)()
	// function call : bool (*const)()
	todo("implement");
	_sub_10861180(this);
}

_extern void _sub_10860F50(CForgeDeviceManager *const, long);
void CForgeDeviceManager::InitializeDeviceObject(long objectIndex) // 0x10860F50
{
	mangled_x86(MANGLED_TODO, "?InitializeDeviceObject@CForgeDeviceManager@@QAEXJ@Z");
	// long objectIndex;
	// s_device_data *device;
	todo("implement");
	_sub_10860F50(this, objectIndex);
}

bool CForgeDeviceManager::IsForgeDevice(long objectIndex) // 0x108610C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?IsForgeDevice@CForgeDeviceManager@@QAE_NJ@Z");
	// long objectIndex;
	// s_device_data *device;
	// s_multiplayer_object_properties *multiplayerProperties;
	// unsigned char channelIndex;
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)

	s_object_data *object = object_get(objectIndex);

	if (!object)
	{
		return false;
	}

	s_multiplayer_object_properties *multiplayerProperties = object_get_multiplayer(objectIndex);

	if (!multiplayerProperties)
	{
		return false;
	}

	unsigned char channel = multiplayerProperties->teleporter_channel;

	return channel < 0x20;
}

extern EForgeDeviceType _sub_10860DD0(CForgeDeviceManager *const, long);
EForgeDeviceType CForgeDeviceManager::GetDeviceType(long objectIndex) // 0x10860DD0
{
	mangled_x86(MANGLED_TODO, "?GetDeviceType@CForgeDeviceManager@@QAE?AW4EForgeDeviceType@@J@Z");
	// long objectIndex;
	// s_device_data *device;
	{
		// s_machine_definition *machineDef;
	}
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	EForgeDeviceType __result = _sub_10860DD0(this, objectIndex);
	return __result;
}

/* ---------- private code */

_extern void _sub_10861320(unsigned long);
void UpdateDevice(unsigned long objectIndex) // 0x10861320
{
	// `anonymous-namespace'::UpdateDevice
	// static ...; // 0x1086165B
	// static ...; // 0x1086164C
	// static ...; // 0x10861634
	// static ...; // 0x1086162C
	// unsigned long objectIndex;
	// void (*const simulation_action_object_update)(long, unsigned long long *);
	// s_device_data *device;
	// s_multiplayer_object_properties *multiplayerProperties;
	// unsigned char channelIndex;
	// SDeviceChannel *channel;
	{
		// s_device_group_datum *powerGroup;
		// s_device_group_datum *positionGroup;
	}
	{
		// CForgeDeviceObjectProperties *deviceProperties;
		// unsigned long *machine_flags;
	}
	{
		// unsigned long long component_mask;
	}
	{
	}
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : bool (*const)(long, unsigned long)
	// function call : bool (*const)(long, unsigned long)
	// function call : void (*const)(long, unsigned long long *)
	// function call : void (*const)(long, unsigned long long *)
	todo("implement");
	_sub_10861320(objectIndex);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_enum<enum e_machine_type,short>::operator short() const;
template s_device_group_datum * c_data_array<s_device_group_datum>::try_and_get(unsigned long);
