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

void CForgeDeviceManager::InitializeForNewMap() // 0x10860FE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?InitializeForNewMap@CForgeDeviceManager@@EAEXXZ");

	if (!((c_game_engine *(__cdecl *)())0x5CE150)())
		return;
	for (__int32 i = 0; i < 32; i++)
	{
		SDeviceChannel &channel = channels[i];
		channel.positionGroupIndex = device_group_new(-1, 0.0f, 0);
		channel.powerGroupIndex = device_group_new(-1, 1.0f, 0);
	}
}

void CForgeDeviceManager::Update() // 0x10861180
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Update@CForgeDeviceManager@@EAEXXZ");

	if (!((c_game_engine *(__cdecl *)())0x5CE150)())
		return;
	bool (*const game_engine_in_round)() = reinterpret_cast<bool (*)()>(0x550F90);
	if (!game_engine_in_round())
	{
		shouldReset = true;
		return;
	}
	c_data_array<s_object_header> *objectHeaders = object_headers_get();
	for (c_data_iterator<s_object_header> it = objectHeaders->begin(); it != objectHeaders->end(); ++it)
	{
		if (!((1 << (char)it->type) & 0x310))
			continue;
		if (it->data->scenario_datum_index != -1)
			continue;
		if (it->data->map_variant_index == -1)
			continue;
		UpdateDevice(it.current_datum_index);
	}
	shouldReset = false;
}

void CForgeDeviceManager::InitializeDeviceObject(long objectIndex) // 0x10860F50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?InitializeDeviceObject@CForgeDeviceManager@@QAEXJ@Z");

	UpdateDevice(objectIndex);

	s_object_data *object = object_get(objectIndex);

	if (!object)
	{
		return;
	}

	*(float *)((unsigned char *)object + 0x18c) = 0.7f;
}

bool CForgeDeviceManager::IsForgeDevice(long objectIndex) // 0x108610C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?IsForgeDevice@CForgeDeviceManager@@QAE_NJ@Z");

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
	if (channel >= 0x20)
	{
		return false;
	}

	return true;
}

EForgeDeviceType CForgeDeviceManager::GetDeviceType(long objectIndex) // 0x10860DD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetDeviceType@CForgeDeviceManager@@QAE?AW4EForgeDeviceType@@J@Z");

	s_device_data *device = (s_device_data *)object_get(objectIndex);
	if (device)
	{
		if (device->object_identifier.type == (e_object_type)9)
			return Control;
		else if (device->object_identifier.type == (e_object_type)8)
		{
			s_machine_definition *machineDef = (s_machine_definition *)tag_get('mach', device->definition_index);
			switch ((short)machineDef->machine_type)
			{
			case _machine_type_door:
				return Door;
			case _machine_type_gear:
				return Gear;
			case _machine_type_platform:
				return Generic;
			}
		}
	}
	return Invalid;
}

/* ---------- private code */

void UpdateDevice(unsigned long objectIndex) // 0x10861320
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateDevice@@YAXK@Z");

	void (*const simulation_action_object_update)(long, unsigned long long *) = reinterpret_cast<void (*)(long, unsigned long long *)>(0x4B3010);
	s_device_data *device = (s_device_data *)object_get(objectIndex);
	if (!device)
		return;
	s_multiplayer_object_properties *multiplayerProperties = object_get_multiplayer(objectIndex);
	if (!multiplayerProperties)
		return;
	unsigned char channelIndex = multiplayerProperties->teleporter_channel;
	if (channelIndex >= 32)
		return;
	SDeviceChannel *channel = &channels[channelIndex];
	if (shouldReset)
	{
		device->power_group_index = -1;
		device->position_group_index = -1;
	}
	if (device->power_group_index == -1 && device->position_group_index == -1)
	{
		s_device_group_datum *powerGroup = device_groups_get()->try_and_get(channel->powerGroupIndex);
		s_device_group_datum *positionGroup = device_groups_get()->try_and_get(channel->positionGroupIndex);
		device->power_group_index = -1;
		device->position_group_index = -1;
		device->power = powerGroup->value;
		device->position = positionGroup->value;
		device->device_flags = 0x100;
		((void (*)(unsigned long, long))0xB943C0)(objectIndex, 0x86);
		((void (*)(unsigned long, long))0xB94460)(objectIndex, 0x87);
	}
	if (device->object_identifier.type == (e_object_type)8)
	{
		unsigned long *machine_flags = (unsigned long *)offset_pointer(device, 0x250);
		CForgeDeviceObjectProperties *deviceProperties = (CForgeDeviceObjectProperties *)&multiplayerProperties->boundry_width;
		if (deviceProperties->door.open_time > 0)
			*machine_flags &= ~2;
		else
			*machine_flags |= 2;
		if (deviceProperties->trigger_radius > 0)
			*machine_flags &= ~1;
		else
			*machine_flags |= 1;
	}
	if (channel->positionGroupIndex != device->position_group_index)
	{
		device->position_group_index = channel->positionGroupIndex;
		unsigned long long component_mask = 0x8000;
		simulation_action_object_update(objectIndex, &component_mask);
	}
	if (channel->powerGroupIndex != device->power_group_index)
	{
		device->power_group_index = channel->powerGroupIndex;
		unsigned long long component_mask = 0x20000;
		simulation_action_object_update(objectIndex, &component_mask);
	}
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_enum<enum e_machine_type,short>::operator short() const;
template s_device_group_datum * c_data_array<s_device_group_datum>::try_and_get(unsigned long);

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { std::array<SDeviceChannel,32> channels; }
namespace hades_file_local { bool shouldReset; }
