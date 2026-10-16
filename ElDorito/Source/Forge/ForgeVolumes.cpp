/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/forge/forge_globals.hpp"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/game/engine/game_engine_ctf.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_engine_candy_monitor.hpp"
#include "Blam/game/game_engine_globals.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "ElDorito.hpp"
#include "Forge/ForgeObjectProperties.hpp"
#include "Forge/ForgeUndo.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/Magnets.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/rapidjson.h"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include "Modules/ModuleForge.hpp"  // hades: added for 0x10954E30

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

/* ---------- forward declarations */

struct begin;
struct c_game_engine;
struct end;
struct real_argb_color;
struct real_point3d;
struct real_vector3d;
struct s_cluster_reference;
struct s_ctf_engine_globals;
struct s_forge_globals_definition;
struct s_game_engine_globals;
struct s_game_globals;
struct s_multiplayer_object_boundary_geometry_data;
struct s_multiplayer_object_properties;
struct s_multiplayer_weapon_tracker;
struct s_object_data;
struct s_object_header;
struct s_player_datum;
struct s_state;
struct s_unit_data;
namespace Forge
{
	struct ForgeGarbageVolumeProperties;
	struct ForgeKillVolumeProperties;
}
namespace hades_file_local
{
	struct ForgeVolume;
	struct DamageData;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace Forge {}
using namespace ::Forge;
namespace Forge
{
	namespace Volumes {}
	using namespace Forge::Volumes;
}

/* ---------- constants */

namespace hades_file_local
{
	enum VolumeType : unsigned char
	{
		eVolumeType_Disabled = 0,
		eVolumeType_Kill,
		eVolumeType_GarbageCollection,
	};

	enum VolumeFlags : unsigned short
	{
		eVolumeFlags_AlwaysVisible = 1, // 0x0001
	};
}
using namespace hades_file_local;
/* ---------- definitions */

namespace hades_file_local
{
	struct ForgeVolume
	{
			public:
			struct s_GarbageVolume
		{
			unsigned short CollectionTicks; // 0x0
		};
		// static_assert(sizeof(s_GarbageVolume) == 2, "Invalid s_GarbageVolume size");
		// Withheld: the type inventory does not describe this type, so its
		// padding could not be reconstructed.
		union s_Data
		{
			public:
			struct s_GarbageVolume
			{
				unsigned short CollectionTicks; // 0x0
			};
			// static_assert(sizeof(s_GarbageVolume) == 2, "Invalid s_GarbageVolume size");
			// Withheld: the type inventory does not describe this type, so its
			// padding could not be reconstructed.
			public:
			struct
		{
			unsigned short CollectionTicks; // 0x0
		} GarbageVolume; // 0x0
		};
		// static_assert(sizeof(s_Data) == 2, "Invalid s_Data size");
		// Withheld: the type inventory does not describe this type, so its
		// padding could not be reconstructed.
			public:
		VolumeType Type; // 0x0
		char TeamIndex; // 0x1
		unsigned short Flags; // 0x2
		__int32 ObjectIndex; // 0x4
		s_multiplayer_object_boundary_geometry_data Zone; // 0x8
		union
		{
			struct
		{
			unsigned short CollectionTicks; // 0x0
		} GarbageVolume; // 0x0
		} Data; // 0x58
	};
}
using namespace hades_file_local;
// static_assert(sizeof(ForgeVolume) == 92, "Invalid ForgeVolume size");
// The layout above is the PDB's member list without its padding, so the
// size assertion is withheld: it would fail on alignment alone.

namespace hades_file_local
{
	struct DamageData
	{
		__int32 DamageEffect; // 0x0
		__int32 Flags; // 0x4
		__int32 PlayerIndex; // 0x8
		__int32 ObjectIndex; // 0xC
		__int32 field_10; // 0x10
		__int32 field_14; // 0x14
		__int32 field_18; // 0x18
		__int32 field_1C; // 0x1C
		short ClusterIndex; // 0x20
		short field_22; // 0x22
		real_point3d ObjectPosition; // 0x24
		real_vector3d EpicenterDirection; // 0x30
		real_vector3d Direction; // 0x3C
		__int32 Direction2; // 0x48
		__int32 field_4C; // 0x4C
		__int32 field_50; // 0x50
		__int32 field_54; // 0x54
		float field_58; // 0x58
		float field_5C; // 0x5C
		float field_60; // 0x60
		float field_64; // 0x64
		float field_68; // 0x68
		__int32 field_6C; // 0x6C
		__int32 field_70; // 0x70
		__int32 field_74; // 0x74
		__int32 field_78; // 0x78
		__int32 field_7C; // 0x7C
		__int32 field_80; // 0x80
		short MaterialIndex; // 0x84
		short field_86; // 0x86
		__int32 field_88; // 0x88
		__int32 field_8C; // 0x8C
		__int32 field_90; // 0x90
		__int32 field_94; // 0x94
	};
	static_assert(sizeof(DamageData) == 152, "Invalid DamageData size");
}
using namespace hades_file_local;
struct s_state
{
	bool IsValid; // 0x0
	long killVolumeDamageEffect; // 0x4
	unsigned __int32 TicksSinceLastScan; // 0x8
	ForgeVolume Volumes[64]; // 0xC
};
// static_assert(sizeof(s_state) == 5900, "Invalid s_state size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

/* ---------- prototypes */

template<typename t_arg0> static t_arg0 *object_get(unsigned long object_index) { return (t_arg0 *)object_get(object_index); }  // hades: a file-local template in the original (undecorated `object_get<T>`), defined so it is emitted;  // hades: added for 0x10955CA0

extern float (*const game_ticks_to_seconds)(float);  // hades: added for 0x10955820
extern long (*const game_time_get)();  // hades: added for 0x10955820

struct s_hades_game_engine_vtable { void *slots[84]; void (__thiscall *flag_reset_slot)(void *, short); void *slot85; void (__thiscall *flag_returned)(void *, short, bool); };  // hades: added for 0x109550B0

extern s_multiplayer_object_properties *(*const object_get_multiplayer)(unsigned long);  // hades: added for 0x109549C0

s_forge_globals_definition *forge_globals_get_definition();  // hades: added for 0X10954DA0

namespace Forge
{
	namespace Volumes
	{
		extern void InitializeForNewRound();
		extern void DisposeFromOldRound();
		extern void Update();
	}
}

void ApplyUnitDamage(ForgeVolume &killVolume, unsigned __int32 unitObjectIndex);
void ResetVolume(__int32 index);
void UpdateKillVolume(ForgeVolume &volume);
bool ShouldGarbageCollectObject(unsigned __int32 objectIndex, ForgeVolume &volume);
s_multiplayer_weapon_tracker *FindEngineObject(unsigned __int32 objectIndex);
void ResetCtfObject(long objectIndex);
void CollectObject(unsigned __int32 objectIndex);
void UpdateGarbageCollectionVolume(ForgeVolume &volume);
__int32 GetNextVolumeIndex(unsigned __int32 objectIndex);
void FindVolumes();
bool ObjectIsVolume(__int32 tagIndex);
void UpdateVolumes();
void RenderVolumes();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern float const kGarbageCollectionIntervals[4]; // 0x11199D78
	namespace hades_file_local_ForgeVolumes { extern s_state state; } using namespace hades_file_local_ForgeVolumes; // 0x1240DAB8
}
using namespace hades_file_local;
/* ---------- public code */

namespace Forge
{
	namespace Volumes
	{
		void InitializeForNewRound() // 0x10954D00
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?InitializeForNewRound@Volumes@Forge@@YAXXZ");

			memset(&state, 0, sizeof(state));

			for (__int32 i = 0; i < 64; i++)
			{
				ForgeVolume *volume = &state.Volumes[i];
				volume->Type = eVolumeType_Disabled;
				volume->ObjectIndex = -1;
			}

			state.IsValid = true;
		}

		void DisposeFromOldRound() // 0x109548F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?DisposeFromOldRound@Volumes@Forge@@YAXXZ");

			state.IsValid = false;
		}

		void Update() // 0x109556B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Update@Volumes@Forge@@YAXXZ");

			bool (*const game_engine_round_in_progress)() = (bool (*)())0x550F90;
			if (game_engine_round_in_progress())
			{
				if (!state.IsValid)
					InitializeForNewRound();
				if (state.IsValid)
				{
					if (game_ticks_to_seconds((float)state.TicksSinceLastScan++) > 1.0f)
					{
						state.TicksSinceLastScan = 0;
						FindVolumes();
					}
					UpdateVolumes();
					RenderVolumes();
				}
			}
			else
			{
				DisposeFromOldRound();
			}
		}
	}
}

/* ---------- private code */

void ApplyUnitDamage(ForgeVolume &killVolume, unsigned __int32 unitObjectIndex) // 0x10954590
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyUnitDamage@@YAXAAUForgeVolume@hades_file_local@@I@Z");

	__int32 (*const damage_data_new)(DamageData *, __int32) = reinterpret_cast<__int32 (*)(DamageData *, __int32)>(0xB50330);
	void (*const unit_cause_damage)(DamageData *, __int32, __int32) = reinterpret_cast<void (*)(DamageData *, __int32, __int32)>(0xB542A0);
	void (*const damage_determine_cause)(unsigned __int32, void *) = reinterpret_cast<void (*)(unsigned __int32, void *)>(0xB770E0);
	if (unitObjectIndex == -1)
		return;
	s_object_data *volumeObject = object_get(killVolume.ObjectIndex);
	if (!volumeObject)
		return;
	s_multiplayer_object_properties *mpProperties = object_get_multiplayer(killVolume.ObjectIndex);
	if (!mpProperties)
		return;
	s_game_globals *matg = *(s_game_globals **)0x22AAEB8;
	__int32 damageEffectTagIndex = -1;
	if (matg->PlayerFallingDamage.count > 0)
		damageEffectTagIndex = matg->PlayerFallingDamage->DistanceDamage.index;
	__int32 damageCauseType = 0;
	Forge::ForgeKillVolumeProperties *killVolumeProperties = (Forge::ForgeKillVolumeProperties *)&mpProperties->teleporter_channel;
	switch (killVolumeProperties->DamageCause)
	{
	case 1:
		damageCauseType = 1;
		break;
	case 2:
		damageCauseType = 2;
		break;
	}
	if (damageEffectTagIndex != -1)
	{
		DamageData damage;
		damage_data_new(&damage, damageEffectTagIndex);
		if (damageCauseType != 1)
			damage_determine_cause(unitObjectIndex, &damage.PlayerIndex);
		damage.field_8C = damageCauseType;
		damage.Flags |= 4;
		unit_cause_damage(&damage, unitObjectIndex, 5);
	}
}

void ResetVolume(__int32 index) // 0x10955210
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ResetVolume@@YAXH@Z");

	ForgeVolume &volume = state.Volumes[index];
	memset(&volume, 0, sizeof(volume));
	volume.Type = eVolumeType_Disabled;
	volume.ObjectIndex = -1;
}

void UpdateKillVolume(ForgeVolume &volume) // 0x10955CA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateKillVolume@@YAXAAUForgeVolume@hades_file_local@@@Z");

	bool (__thiscall *const ZoneShape__ContainsPlayer)(void *, __int32) = reinterpret_cast<bool (__thiscall *)(void *, __int32)>(0x765C80);
	c_data_array<s_player_datum> *players = players_get();
	s_object_data *volumeObject = object_get(volume.ObjectIndex);
	if (!volumeObject)
		return;
	s_multiplayer_object_properties *mpProperties = object_get_multiplayer(volume.ObjectIndex);
	if (!mpProperties)
		return;
	::Forge::ForgeKillVolumeProperties *properties = (::Forge::ForgeKillVolumeProperties *)&mpProperties->teleporter_channel;
	__int32 objectTypeMask = 1;
	if (properties->Flags & ::Forge::ForgeKillVolumeProperties::eKillVolumeFlags_DestroyVehicles)
		objectTypeMask |= 2;
	long clusterObjects[128];
	short clusterObjectCount = ((short (*)(long, long, s_scenario_location *, real_point3d *, float, long *, long))0xB35B60)(0, objectTypeMask, &volumeObject->location, &volumeObject->bounding_sphere_center, abs(volume.Zone.bounding_radius), clusterObjects, 128);
	for (__int32 i = 0; i < clusterObjectCount; i++)
	{
		s_object_data *clusterObject = object_get(clusterObjects[i]);
		if (!clusterObject)
			break;
		unsigned char objectType = *(unsigned char *)&clusterObject->object_identifier.type;
		if (objectType == 0)
		{
			unsigned __int32 playerIndex = ((s_unit_data *)clusterObject)->player_index;
			s_player_datum *player;
			if (playerIndex != -1 && (player = players_get()->try_and_get(playerIndex)) != nullptr && player->unit_index != -1 && ZoneShape__ContainsPlayer(&volume.Zone, playerIndex) && (volume.TeamIndex == player->configuration.host.team || volume.TeamIndex == 8))
				ApplyUnitDamage(volume, player->unit_index);
		}
		else if (objectType == 1)
		{
			real_point3d position;
			((void (*)(long, real_point3d *))0xB2E5A0)(clusterObjects[i], &position);
			if (!((bool (*)(real_point3d *, s_multiplayer_object_boundary_geometry_data *))0xBA11F0)(&position, &volume.Zone))
				continue;
			unsigned __int32 driverUnitObjectIndex = ((s_unit_data *)clusterObject)->motion_control_unit_index;
			s_unit_data *driverUnitObject;
			if (driverUnitObjectIndex != -1 && (driverUnitObject = object_get<s_unit_data>(driverUnitObjectIndex)) != nullptr)
			{
				unsigned __int32 playerIndex = driverUnitObject->player_index;
				s_player_datum *player;
				if (playerIndex != -1 && (player = players->try_and_get(playerIndex)) != nullptr && player->unit_index != -1 && volume.TeamIndex != player->configuration.host.team && volume.TeamIndex != 8)
					continue;
			}
			ApplyUnitDamage(volume, clusterObjects[i]);
		}
	}
}

bool ShouldGarbageCollectObject(unsigned __int32 objectIndex, ForgeVolume &volume) // 0x10955290
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ShouldGarbageCollectObject@@YA_NIAAUForgeVolume@hades_file_local@@@Z");

	s_object_data *volumeObject = object_get(volume.ObjectIndex);
	if (!volumeObject)
		return false;
	::Forge::ForgeGarbageVolumeProperties *garbageVolumeProperties = (::Forge::ForgeGarbageVolumeProperties *)&object_get_multiplayer(volume.ObjectIndex)->teleporter_channel;
	s_object_data *object = object_get(objectIndex);
	e_object_type objectType = object->object_identifier.type;
	if (objectType == _object_type_vehicle)
	{
		if (!(garbageVolumeProperties->Flags & ::Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectVehicles))
			return false;
		unsigned __int32 driverObjectIndex = *(unsigned __int32 *)((char *)object + 0x32C);
		return driverObjectIndex == -1;
	}
	if (objectType == _object_type_weapon)
	{
		short mpWeaponType = ((short (*)(unsigned __int32))0xB62DB0)(objectIndex);
		unsigned __int32 ownerUnitObjectIndex = *(unsigned __int32 *)((char *)object + 0x184);
		if (ownerUnitObjectIndex != -1)
			return false;
		if (mpWeaponType > 0)
			return garbageVolumeProperties->Flags & ::Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectObjectives;
		else
			return garbageVolumeProperties->Flags & ::Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectWeapons;
	}
	else if (objectType == _object_type_biped)
	{
		if (!(garbageVolumeProperties->Flags & ::Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectDeadBipeds))
			return false;
		if (object->definition_index == 0xC13)
			return false;
		for (s_player_datum const &player : *players_get())
		{
			if (player.unit_index == objectIndex)
				return false;
		}
		return true;
	}
	else if (objectType == _object_type_equipment)
	{
		bool isGrenade = ((long (*)(long))0x52D1A0)(object->definition_index) != -1;
		if (isGrenade)
		{
			if (!(garbageVolumeProperties->Flags & ::Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectGrenades))
				return false;
			if (!*((unsigned char *)object + 0x179))
				return true;
		}
		else
		{
			if (!(garbageVolumeProperties->Flags & ::Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectEquipment))
				return false;
			unsigned __int32 ownerUnitObjectIndex = *(unsigned __int32 *)((char *)object + 0x184);
			return ownerUnitObjectIndex == -1;
		}
	}
	return false;
}

s_multiplayer_weapon_tracker *FindEngineObject(unsigned __int32 objectIndex) // 0x10954910
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FindEngineObject@@YAPAUs_multiplayer_weapon_tracker@@I@Z");

	s_game_engine_globals *game_engine_globals = tls_getd().game_engine_globals;

	for (long i = 0; i < game_engine_globals->multiplayer_weapon_count; i++)
	{
		if (game_engine_globals->multiplayer_weapon[i].weapon_index == objectIndex)
			return &game_engine_globals->multiplayer_weapon[i];
	}

	return nullptr;
}

void ResetCtfObject(long objectIndex) // 0x109550B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ResetCtfObject@@YAXJ@Z");

	void (*const flag_reset)(long) = reinterpret_cast<void (*)(long)>(0x97DD00);
	c_game_engine *engine = ((c_game_engine *(__cdecl *)())0x5CE150)();
	if (!engine)
		return;
	s_multiplayer_weapon_tracker *engineObject = FindEngineObject(objectIndex);
	if (!engineObject)
		return;
	s_ctf_engine_globals *ctf_globals = get_ctf_globals();
	if (ctf_globals->field_1638)
		ctf_globals->field_1638 = false;
	else
	{
		(*(s_hades_game_engine_vtable **)engine)->flag_returned(engine, engineObject->multiplayer_weapon_identifier, ctf_globals->field_1639);
		ctf_globals->field_1639 = false;
	}
	flag_reset(engineObject->weapon_index);
	(*(s_hades_game_engine_vtable **)engine)->flag_reset_slot(engine, engineObject->multiplayer_weapon_identifier);
}

void CollectObject(unsigned __int32 objectIndex) // 0x109547E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CollectObject@@YAXI@Z");

	void (*const objects_dispose)(unsigned __int32) = reinterpret_cast<void (*)(unsigned __int32)>(0xB2CD10);
	s_object_data *object = object_get(objectIndex);
	if (!object)
		return;
	if (object->object_identifier.type == (e_object_type)2)
	{
		short mpWeaponType = ((short(__cdecl *)(unsigned __int32))0xB62DB0)(objectIndex);
		switch (mpWeaponType)
		{
		case 1:
			ResetCtfObject(objectIndex);
			return;
		}
	}
	objects_dispose(objectIndex);
}

void UpdateGarbageCollectionVolume(ForgeVolume &volume) // 0x10955820
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateGarbageCollectionVolume@@YAXAAUForgeVolume@hades_file_local@@@Z");

	if (game_ticks_to_seconds(volume.Data.GarbageVolume.CollectionTicks++) < 0.25f)
		return;
	volume.Data.GarbageVolume.CollectionTicks = 0;
	s_object_data *volumeObject = object_get(volume.ObjectIndex);
	if (!volumeObject)
		return;
	::Forge::ForgeGarbageVolumeProperties *garbageVolumeProperties = (::Forge::ForgeGarbageVolumeProperties *)&object_get_multiplayer(volume.ObjectIndex)->teleporter_channel;
	__int32 intervalIndex = garbageVolumeProperties->Interval;
	if (intervalIndex < 0 || intervalIndex >= sizeof(kGarbageCollectionIntervals) / sizeof(kGarbageCollectionIntervals[0]))
		return;
	float interval = kGarbageCollectionIntervals[intervalIndex];
	__int32 const collectionMask = 0xF;
	long clusterObjects[128];
	short clusterObjectCount = ((short (*)(long, long, s_scenario_location const *, real_point3d const *, float, long *, long))0xB35B60)(0, collectionMask, &volumeObject->location, &volumeObject->bounding_sphere_center, abs(volume.Zone.bounding_radius), clusterObjects, 128);
	long currentTime = game_time_get();
	for (__int32 i = 0; i < clusterObjectCount; i++)
	{
		long clusterObjectIndex = clusterObjects[i];
		s_object_data *clusterObject = object_get(clusterObjectIndex);
		if (!clusterObject)
			continue;
		unsigned __int32 lastActiveTicks = 0;
		switch ((e_object_type)clusterObject->object_identifier.type)
		{
		case _object_type_biped:
		case _object_type_vehicle:
			lastActiveTicks = *(unsigned __int32 *)((char *)clusterObject + 0x4A8);
			break;
		case _object_type_weapon:
			lastActiveTicks = *(unsigned __int32 *)((char *)clusterObject + 0x180);
			break;
		case _object_type_equipment:
			lastActiveTicks = *(unsigned __int32 *)((char *)clusterObject + 0x12C);
			break;
		}
		if (lastActiveTicks != -1)
		{
			if (game_ticks_to_seconds(currentTime - lastActiveTicks) > interval)
			{
				if (!((bool (*)(real_point3d *, s_multiplayer_object_boundary_geometry_data *))0xBA11F0)(&clusterObject->bounding_sphere_center, &volume.Zone))
					continue;
				if (ShouldGarbageCollectObject(clusterObjectIndex, volume))
					CollectObject(clusterObjectIndex);
			}
		}
	}
}

__int32 GetNextVolumeIndex(unsigned __int32 objectIndex) // 0x10954C80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetNextVolumeIndex@@YAHI@Z");

	for (int i = 0; i < 64; i++)
	{
		auto volume = &state.Volumes[i];
		if (volume->ObjectIndex == objectIndex)
			return -1;
		if (volume->Type == eVolumeType_Disabled)
			return i;
	}
	return -1;
}

void FindVolumes() // 0x109549C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FindVolumes@@YAXXZ");

	s_forge_globals_definition *forge_globals = forge_globals_get_definition();
	c_data_array<s_object_header> *object_headers = object_headers_get();
	for (c_data_iterator<s_object_header> it = object_headers->begin(); it != object_headers->end(); ++it)
	{
		if (it->type != (e_object_type)11 || !it->data)
			continue;
		s_multiplayer_object_properties *mpProperties = object_get_multiplayer(it.current_datum_index);
		if (!mpProperties)
			continue;
		if (it->data->definition_index != forge_globals->kill_volume_object.index && it->data->definition_index != forge_globals->garbage_volume_object.index)
			continue;
		__int32 volumeIndex = GetNextVolumeIndex(it.current_datum_index);
		if (volumeIndex == -1)
			continue;
		ForgeVolume &volume = state.Volumes[volumeIndex];
		((void(__cdecl *)(long, s_multiplayer_object_boundary_geometry_data *, long))0xBA0AD0)(it.current_datum_index, &volume.Zone, -1);
		volume.ObjectIndex = it.current_datum_index;
		volume.TeamIndex = (short)mpProperties->team_designator & 0xFF;
		volume.Flags = 0;
		if (it->data->definition_index == forge_globals->kill_volume_object.index)
		{
			volume.Type = eVolumeType_Kill;
			Forge::ForgeKillVolumeProperties *killVolumeProperties = (Forge::ForgeKillVolumeProperties *)&mpProperties->teleporter_channel;
			if (killVolumeProperties->Flags & Forge::ForgeKillVolumeProperties::eKillVolumeFlags_AlwaysVisible)
				volume.Flags |= 1;
		}
		else if (it->data->definition_index == forge_globals->garbage_volume_object.index)
		{
			volume.Type = eVolumeType_GarbageCollection;
			volume.Data.GarbageVolume.CollectionTicks = 0;
		}
	}
}

bool ObjectIsVolume(__int32 tagIndex) // 0x10954DA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ObjectIsVolume@@YA_NH@Z");

	s_forge_globals_definition *forge_globals = forge_globals_get_definition();
	return tagIndex == forge_globals->kill_volume_object.index || tagIndex == forge_globals->garbage_volume_object.index;
}

void UpdateVolumes() // 0x10956160
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateVolumes@@YAXXZ");

	for (__int32 i = 0; i < 64; i++)
	{
		ForgeVolume &volume = state.Volumes[i];
		if (!volume.Type || volume.ObjectIndex == -1)
			continue;
		s_object_data *volumeObject = object_get(volume.ObjectIndex);
		if (!volumeObject || !ObjectIsVolume(volumeObject->definition_index))
		{
			ResetVolume(i);
			continue;
		}
		((void(__cdecl *)(long, s_multiplayer_object_boundary_geometry_data *, long))0xBA0AD0)(volume.ObjectIndex, &volume.Zone, -1);
		switch (volume.Type)
		{
		case eVolumeType_Kill:
			UpdateKillVolume(volume);
			break;
		case eVolumeType_GarbageCollection:
			UpdateGarbageCollectionVolume(volume);
			break;
		}
	}
}

void RenderVolumes() // 0x10954E30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RenderVolumes@@YAXXZ");

	for (__int32 i = 0; i < 64; i++)
	{
		ForgeVolume const &volume = state.Volumes[i];
		if (!volume.Type)
			continue;
		s_object_data *volumeObject;
		if (volume.ObjectIndex == -1 || !(volumeObject = object_get(volume.ObjectIndex)))
			return;
		if (!((bool(__cdecl *)(long, long *, long *))0x59A6F0)(((unsigned long(__cdecl *)(long))0x589C30)(0), nullptr, nullptr) && !(volume.Flags & 1) && !Modules::ModuleForge::Instance().VarShowInvisiblesClient->ValueInt)
			continue;
		switch (volume.Type)
		{
		case eVolumeType_GarbageCollection:
		{
			real_argb_color color = { 0.1f, 0.0f, 0.5f, 0.0f };
			((void(__cdecl *)(s_multiplayer_object_boundary_geometry_data const *, real_argb_color const *, long))0xBA0FC0)(&volume.Zone, &color, volume.ObjectIndex);
			break;
		}
		case eVolumeType_Kill:
		{
			real_argb_color color = { 0.1f, 0.5f, 0.0f, 0.0f };
			((void(__cdecl *)(s_multiplayer_object_boundary_geometry_data const *, real_argb_color const *, long))0xBA0FC0)(&volume.Zone, &color, volume.ObjectIndex);
			break;
		}
		}
	}
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { float const kGarbageCollectionIntervals[4] = { 0.0f, 3.0f, 5.0f, 10.0f }; }
namespace hades_file_local { namespace hades_file_local_ForgeVolumes { s_state state; } }
