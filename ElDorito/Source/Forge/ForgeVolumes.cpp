/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_ctf.hpp"
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
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "ElDorito.hpp"
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

struct real_vector3d;
struct s_multiplayer_object_boundary_geometry_data;
struct s_state;
namespace
{
	struct ForgeVolume;
	struct DamageData;
}

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

namespace
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
/* ---------- definitions */

namespace
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
// static_assert(sizeof(ForgeVolume) == 92, "Invalid ForgeVolume size");
// The layout above is the PDB's member list without its padding, so the
// size assertion is withheld: it would fail on alignment alone.

namespace
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

namespace Forge
{
	namespace Volumes
	{
		extern void InitializeForNewRound();
		extern void DisposeFromOldRound();
		extern void Update();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern float const kGarbageCollectionIntervals[4]; // 0x11199D78
}
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

		_extern void _sub_109548F0();
		void DisposeFromOldRound() // 0x109548F0
		{
			mangled_x86(MANGLED_TODO, "?DisposeFromOldRound@Volumes@Forge@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_109548F0();
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
