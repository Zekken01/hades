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
struct c_game_engine;
struct s_device_data;
struct s_machine_definition;
struct s_multiplayer_object_properties;
struct s_object_header;
namespace
{
	struct SDeviceChannel;
}

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

namespace
{
	struct SDeviceChannel
	{
		unsigned long powerGroupIndex; // 0x0
		unsigned long positionGroupIndex; // 0x4
	};
	static_assert(sizeof(SDeviceChannel) == 8, "Invalid SDeviceChannel size");

}
/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern bool shouldReset; // 0x123AC7C8
}
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

_extern bool _sub_108610C0(CForgeDeviceManager *const, long);
bool CForgeDeviceManager::IsForgeDevice(long objectIndex) // 0x108610C0
{
	mangled_x86(MANGLED_TODO, "?IsForgeDevice@CForgeDeviceManager@@QAE_NJ@Z");
	// long objectIndex;
	// s_device_data *device;
	// s_multiplayer_object_properties *multiplayerProperties;
	// unsigned char channelIndex;
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	todo("implement");
	bool __result = _sub_108610C0(this, objectIndex);
	return __result;
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
