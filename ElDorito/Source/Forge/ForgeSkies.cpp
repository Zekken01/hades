/* ---------- headers */

#include "Forge/ForgeSkies.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/fmod/fmod_functions.inl"
#include "Blam/forge/forge_globals.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/math/sound_math.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/sounds/sound_memory.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeObjectProperties.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/Reforge.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <limits>
#include <type_traits>

/* ---------- forward declarations */

struct c_object_identifier;
struct real_point3d;
struct real_rectangle2d;
struct real_vector3d;
struct s_forge_globals_definition;
struct s_forge_sky_definition;
struct s_multiplayer_object_properties_definition;
struct s_object_data;
struct s_object_placement_data;
struct s_scenario;
struct s_scenario_location;
struct s_tag_reference;
namespace Forge
{
	class CForgeSkies;
	struct ForgeMapModifierProperties;
}
namespace
{
	struct ForgeSkyState;
}

namespace Forge {}
using namespace ::Forge;

/* ---------- constants */

/* ---------- definitions */

namespace
{
	struct ForgeSkyState
	{
		bool useMapModifierTransform; // 0x0
		unsigned char __pad0[3]; // 0x1
		long SkyIndex; // 0x4
		long SceneryObjectIndex; // 0x8
		long BackgroundSoundDatumIndex; // 0xC
		long ScreenEffectDatumIndex; // 0x10
		ForgeSkyState(); /* compiler_generated() */
	};
	static_assert(sizeof(ForgeSkyState) == 20, "Invalid ForgeSkyState size");
}
/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern real_rectangle2d global_null_rectangle2d; // 0x11172F9C
	extern s_forge_sky_definition mapDefaultSky; // 0x11371850
}
/* ---------- public code */

extern c_object_identifier* _sub_1067D1D0(c_object_identifier *const);
_inline c_object_identifier::c_object_identifier() // 0x1067D1D0
{
	mangled_x86(MANGLED_TODO, "??0c_object_identifier@@QAE@XZ");
	// c_object_identifier *const this;
	compiler_generated();
	todo("implement");
	_sub_1067D1D0(this);
}

extern s_multiplayer_object_properties_definition* _sub_1067D240(s_multiplayer_object_properties_definition *const);
_inline s_multiplayer_object_properties_definition::s_multiplayer_object_properties_definition() // 0x1067D240
{
	mangled_x86(MANGLED_TODO, "??0s_multiplayer_object_properties_definition@@QAE@XZ");
	// s_multiplayer_object_properties_definition *const this;
	compiler_generated();
	todo("implement");
	_sub_1067D240(this);
}

extern s_object_placement_data* _sub_1067D2F0(s_object_placement_data *const);
_inline s_object_placement_data::s_object_placement_data() // 0x1067D2F0
{
	mangled_x86(MANGLED_TODO, "??0s_object_placement_data@@QAE@XZ");
	// s_object_placement_data *const this;
	compiler_generated();
	todo("implement");
	_sub_1067D2F0(this);
}

namespace Forge
{
	_extern void _sub_1067DE20();
	void CForgeSkies::InitializeForNewMap() // 0x1067DE20
	{
		mangled_x86(MANGLED_TODO, "?InitializeForNewMap@CForgeSkies@Forge@@SAXXZ");
		// procedure flags: nofpo
		// static ...; // 0x1067E0F4
		// static ...; // 0x1067E0E8
		// static ...; // 0x1067E0E0
		// s_tag_reference null_tag_reference;
		// s_scenario *scenario;
		todo("implement");
		_sub_1067DE20();
	}

	_extern void _sub_1067EB10(long, Forge::ForgeMapModifierProperties &);
	void CForgeSkies::Update(long modifierObjectIndex, Forge::ForgeMapModifierProperties &mapModifierProperties) // 0x1067EB10
	{
		mangled_x86(MANGLED_TODO, "?Update@CForgeSkies@Forge@@SAXJAAUForgeMapModifierProperties@2@@Z");
		// static ...; // 0x1067EDF7
		// static ...; // 0x1067EDF4
		// static ...; // 0x1067EDD0
		// static ...; // 0x1067EDC8
		// long modifierObjectIndex;
		// Forge::ForgeMapModifierProperties &mapModifierProperties;
		// s_forge_globals_definition *forge_globals;
		// long desiredSkyIndex;
		{
			// s_forge_sky_definition *desiredSky;
			// s_forge_globals_definition *forge_globals;
		}
		{
			// s_object_data *mapModifierObject;
			{
				// real_point3d position;
				// float zOffset;
			}
		}
		{
			// real_vector3d forward;
			// s_forge_sky_definition *forgeSky;
			// real_vector3d up;
		}
		// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
		// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
		// function call : void (*const)(unsigned long, real_point3d *, real_vector3d *, real_vector3d *, s_scenario_location *)
		// function call : void (*const)(unsigned long, real_point3d *, real_vector3d *, real_vector3d *, s_scenario_location *)
		todo("implement");
		_sub_1067EB10(modifierObjectIndex, mapModifierProperties);
	}

	_extern void _sub_1067DBE0();
	void CForgeSkies::HandleMapModifierDeleted() // 0x1067DBE0
	{
		mangled_x86(MANGLED_TODO, "?HandleMapModifierDeleted@CForgeSkies@Forge@@SAXXZ");
		// procedure flags: nofpo
		// s_scenario *scenario;
		// function call : void (*const)(unsigned long)
		todo("implement");
		_sub_1067DBE0();
	}

	_extern bool _sub_1067E1C0();
	bool CForgeSkies::IsActive() // 0x1067E1C0
	{
		mangled_x86(MANGLED_TODO, "?IsActive@CForgeSkies@Forge@@SA_NXZ");
		// procedure flags: nofpo
		todo("implement");
		bool __result = _sub_1067E1C0();
		return __result;
	}
}

/* ---------- private code */
