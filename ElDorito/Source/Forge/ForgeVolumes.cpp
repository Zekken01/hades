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
	extern s_state state; // 0x1240DAB8
}
using namespace hades_file_local;
/* ---------- public code */

namespace Forge
{
	namespace Volumes
	{
		_extern void _sub_10954D00();
		void InitializeForNewRound() // 0x10954D00
		{
			mangled_x86(MANGLED_TODO, "?InitializeForNewRound@Volumes@Forge@@YAXXZ");
			// procedure flags: nofpo
			{
				// __int32 i;
				{
					// ForgeVolume *volume;
				}
			}
			todo("implement");
			_sub_10954D00();
		}

		void DisposeFromOldRound() // 0x109548F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?DisposeFromOldRound@Volumes@Forge@@YAXXZ");
			// procedure flags: nofpo

			state.IsValid = false;
		}

		_extern void _sub_109556B0();
		void Update() // 0x109556B0
		{
			mangled_x86(MANGLED_TODO, "?Update@Volumes@Forge@@YAXXZ");
			// procedure flags: nofpo
			// bool (*const game_engine_round_in_progress)();
			// function call : bool (*const)()
			// function call : float (*const)(float)
			todo("implement");
			_sub_109556B0();
		}
	}
}

/* ---------- private code */

_extern void _sub_10954590(ForgeVolume &, unsigned __int32);
void ApplyUnitDamage(ForgeVolume &killVolume, unsigned __int32 unitObjectIndex) // 0x10954590
{
	// `anonymous-namespace'::ApplyUnitDamage
	// static ...; // 0x10954750
	// static ...; // 0x10954748
	// ForgeVolume &killVolume;
	// unsigned __int32 unitObjectIndex;
	// void (*const damage_determine_cause)(unsigned __int32, void *);
	// s_game_globals *matg;
	// __int32 damageCauseType;
	// Forge::ForgeKillVolumeProperties *killVolumeProperties;
	// __int32 damageEffectTagIndex;
	// __int32 (*const damage_data_new)(DamageData *, __int32);
	// void (*const unit_cause_damage)(DamageData *, __int32, __int32);
	// s_object_data *volumeObject;
	// s_multiplayer_object_properties *mpProperties;
	{
		// DamageData damage;
	}
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : __int32 (*const)(DamageData *, __int32)
	// function call : void (*const)(unsigned __int32, void *)
	// function call : void (*const)(DamageData *, __int32, __int32)
	todo("implement");
	_sub_10954590(killVolume, unitObjectIndex);
}

_extern void _sub_10955210(__int32);
void ResetVolume(__int32 index) // 0x10955210
{
	// `anonymous-namespace'::ResetVolume
	// __int32 index;
	// ForgeVolume &volume;
	todo("implement");
	_sub_10955210(index);
}

_extern void _sub_10955CA0(ForgeVolume &);
void UpdateKillVolume(ForgeVolume &volume) // 0x10955CA0
{
	// `anonymous-namespace'::UpdateKillVolume
	// static ...; // 0x10956055
	// static ...; // 0x1095604C
	// static ...; // 0x10956034
	// static ...; // 0x1095602C
	// ForgeVolume &volume;
	// bool (*const ZoneShape__ContainsPlayer)(void *, __int32);
	// long clusterObjects[128];
	// short clusterObjectCount;
	// c_data_array<s_player_datum> *players;
	// __int32 objectTypeMask;
	// Forge::ForgeKillVolumeProperties *properties;
	// s_object_data *volumeObject;
	// s_multiplayer_object_properties *mpProperties;
	{
		// __int32 i;
		{
			// s_object_data *clusterObject;
			// unsigned char objectType;
			{
				// s_player_datum *player;
				// unsigned __int32 playerIndex;
			}
			{
				// s_unit_data *driverUnitObject;
				// unsigned __int32 driverUnitObjectIndex;
				// real_point3d position;
				{
					// s_player_datum *player;
					// long playerIndex;
				}
			}
		}
	}
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : short (*const)(long, long, s_cluster_reference const *, real_point3d const *, float, long *, short)
	// function call : bool (*const)(void *, __int32)
	// function call : void (*const)(long, real_point3d *)
	// function call : bool (*const)(real_point3d const *, s_multiplayer_object_boundary_geometry_data const *)
	todo("implement");
	_sub_10955CA0(volume);
}

_extern bool _sub_10955290(unsigned __int32, ForgeVolume &);
bool ShouldGarbageCollectObject(unsigned __int32 objectIndex, ForgeVolume &volume) // 0x10955290
{
	// `anonymous-namespace'::ShouldGarbageCollectObject
	// static ...; // 0x109555C0
	// static ...; // 0x109555A8
	// static ...; // 0x109555A0
	// unsigned __int32 objectIndex;
	// ForgeVolume &volume;
	// s_object_data *object;
	// e_object_type objectType;
	// s_object_data *volumeObject;
	// Forge::ForgeGarbageVolumeProperties *garbageVolumeProperties;
	{
		// unsigned __int32 driverObjectIndex;
	}
	{
		// unsigned __int32 ownerUnitObjectIndex;
		// short mpWeaponType;
	}
	{
		// c_data_array<s_player_datum> &<range>$L0;
		// c_data_iterator<s_player_datum> <begin>$L0;
		// c_data_iterator<s_player_datum> <end>$L0;
		{
			// s_player_datum const &player;
		}
	}
	{
		// bool isGrenade;
		{
			// unsigned __int32 ownerUnitObjectIndex;
		}
	}
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : short (*const)(unsigned __int32)
	// function call : __int32 (*const)(__int32)
	todo("implement");
	bool __result = _sub_10955290(objectIndex, volume);
	return __result;
}

extern s_multiplayer_weapon_tracker *_sub_10954910(unsigned __int32);
s_multiplayer_weapon_tracker *FindEngineObject(unsigned __int32 objectIndex) // 0x10954910
{
	// `anonymous-namespace'::FindEngineObject
	// unsigned __int32 objectIndex;
	// s_game_engine_globals *game_engine_globals;
	{
		// long i;
	}
	todo("implement");
	s_multiplayer_weapon_tracker * __result = _sub_10954910(objectIndex);
	return __result;
}

_extern void _sub_109550B0(long);
void ResetCtfObject(long objectIndex) // 0x109550B0
{
	// `anonymous-namespace'::ResetCtfObject
	// long objectIndex;
	// s_ctf_engine_globals *ctf_globals;
	// s_multiplayer_weapon_tracker *engineObject;
	// void (*const flag_reset)(long);
	// c_game_engine *engine;
	// function call : c_game_engine *(*const)()
	// function call : void (*)(void *, short, bool)
	// function call : void (*const)(long)
	// function call : void (*)(void *, short)
	todo("implement");
	_sub_109550B0(objectIndex);
}

_extern void _sub_109547E0(unsigned __int32);
void CollectObject(unsigned __int32 objectIndex) // 0x109547E0
{
	// `anonymous-namespace'::CollectObject
	// unsigned __int32 objectIndex;
	// s_object_data *object;
	// void (*const objects_dispose)(unsigned __int32);
	{
		// short mpWeaponType;
	}
	// function call : short (*const)(unsigned __int32)
	// function call : void (*const)(unsigned __int32)
	todo("implement");
	_sub_109547E0(objectIndex);
}

_extern void _sub_10955820(ForgeVolume &);
void UpdateGarbageCollectionVolume(ForgeVolume &volume) // 0x10955820
{
	// `anonymous-namespace'::UpdateGarbageCollectionVolume
	// static ...; // 0x10955BA4
	// static ...; // 0x10955B94
	// static ...; // 0x10955B88
	// static ...; // 0x10955B80
// $LN15:
// $LN14:
// $LN12:
	// ForgeVolume &volume;
	// long currentTime;
	// long clusterObjects[128];
	// __int32 const collectionMask;
	// float interval;
	// short clusterObjectCount;
	// __int32 intervalIndex;
	// s_object_data *volumeObject;
	// Forge::ForgeGarbageVolumeProperties *garbageVolumeProperties;
	{
		// __int32 i;
		{
			// long clusterObjectIndex;
			// s_object_data *clusterObject;
			// unsigned __int32 lastActiveTicks;
		}
	}
	// function call : float (*const)(float)
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : short (*const)(long, long, s_cluster_reference const *, real_point3d const *, float, long *, short)
	// function call : long (*const)()
	// function call : float (*const)(float)
	// function call : bool (*const)(real_point3d const *, s_multiplayer_object_boundary_geometry_data const *)
	todo("implement");
	_sub_10955820(volume);
}

_extern __int32 _sub_10954C80(unsigned __int32);
__int32 GetNextVolumeIndex(unsigned __int32 objectIndex) // 0x10954C80
{
	// `anonymous-namespace'::GetNextVolumeIndex
	// unsigned __int32 objectIndex;
	{
		// __int32 i;
		{
			// ForgeVolume &volume;
		}
	}
	todo("implement");
	__int32 __result = _sub_10954C80(objectIndex);
	return __result;
}

_extern void _sub_109549C0();
void FindVolumes() // 0x109549C0
{
	// `anonymous-namespace'::FindVolumes
	// procedure flags: nofpo
	// static ...; // 0x10954BEC
	// static ...; // 0x10954BE0
	// static ...; // 0x10954BD8
	// c_data_array<s_object_header> *object_headers;
	// s_forge_globals_definition *forge_globals;
	{
		// c_data_iterator<s_object_header> it;
		{
			// __int32 volumeIndex;
			// ForgeVolume &volume;
			// s_multiplayer_object_properties *mpProperties;
			{
				// Forge::ForgeKillVolumeProperties *killVolumeProperties;
			}
		}
	}
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : void (*const)(long, s_multiplayer_object_boundary_geometry_data *, long)
	todo("implement");
	_sub_109549C0();
}

bool ObjectIsVolume(__int32 tagIndex) // 0x10954DA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ObjectIsVolume@@YA_NH@Z");
	// `anonymous-namespace'::ObjectIsVolume
	// __int32 tagIndex;
	// s_forge_globals_definition *forge_globals;

	s_forge_globals_definition *forge_globals = forge_globals_get_definition();
	return tagIndex == forge_globals->kill_volume_object.index || tagIndex == forge_globals->garbage_volume_object.index;
}

_extern void _sub_10956160();
void UpdateVolumes() // 0x10956160
{
	// `anonymous-namespace'::UpdateVolumes
	// procedure flags: nofpo
	{
		// __int32 i;
		{
			// ForgeVolume &volume;
			// s_object_data *volumeObject;
		}
	}
	// function call : void (*const)(long, s_multiplayer_object_boundary_geometry_data *, long)
	todo("implement");
	_sub_10956160();
}

_extern void _sub_10954E30();
void RenderVolumes() // 0x10954E30
{
	// `anonymous-namespace'::RenderVolumes
	// procedure flags: nofpo
	// static ...; // 0x1095501E
	// static ...; // 0x10955018
	// static ...; // 0x10955000
	// static ...; // 0x10954FF8
	{
		// __int32 i;
		{
			// ForgeVolume const &volume;
			// s_object_data *volumeObject;
			{
				// real_argb_color color;
			}
			{
			}
		}
	}
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *, long *)
	// function call : void (*const)(s_multiplayer_object_boundary_geometry_data const *, real_argb_color const *, long)
	// function call : void (*const)(s_multiplayer_object_boundary_geometry_data const *, real_argb_color const *, long)
	todo("implement");
	_sub_10954E30();
}
