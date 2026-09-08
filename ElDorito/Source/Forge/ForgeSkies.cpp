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
#include "Blam/items/equipment_definitions.hpp"
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

struct begin;
struct c_object_identifier;
struct end;
struct real_point3d;
struct real_rectangle2d;
struct real_vector3d;
struct s_damage_owner;
struct s_forge_globals_definition;
struct s_forge_sky_definition;
struct s_game_looping_sound_datum;
struct s_multiplayer_object_properties_definition;
struct s_object_data;
struct s_object_header;
struct s_object_placement_data;
struct s_scenario;
struct s_scenario_location;
struct s_scenario_scenery;
struct s_scenario_sky_reference;
struct s_screen_effect_datum;
struct s_tag_reference;
namespace Forge
{
	class CForgeSkies;
	struct ForgeMapModifierProperties;
}
namespace hades_file_local
{
	struct ForgeSkyState;
}
using namespace hades_file_local;

namespace Forge {}
using namespace ::Forge;

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
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
using namespace hades_file_local;
/* ---------- prototypes */

unsigned long FindObjectByName(e_object_type type, short name);
s_forge_sky_definition *GetForgeSky();
void ReplaceForgeSkyScenery(long newSceneryTagIndex);
void ReplaceForgeSky(s_forge_sky_definition *desiredSky);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern real_rectangle2d global_null_rectangle2d; // 0x11172F9C
	extern s_forge_sky_definition mapDefaultSky; // 0x11371850
}
using namespace hades_file_local;
/* ---------- public code */

_inline c_object_identifier::c_object_identifier() // 0x1067D1D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_object_identifier@@QAE@XZ");
	// c_object_identifier *const this;

	compiler_generated();
}

_inline s_multiplayer_object_properties_definition::s_multiplayer_object_properties_definition() // 0x1067D240
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_multiplayer_object_properties_definition@@QAE@XZ");
	// s_multiplayer_object_properties_definition *const this;

	compiler_generated();
}

_inline s_object_placement_data::s_object_placement_data() // 0x1067D2F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_object_placement_data@@QAE@XZ");
	// s_object_placement_data *const this;

	compiler_generated();
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

_extern unsigned long _sub_1067DA10(e_object_type, short);
unsigned long FindObjectByName(e_object_type type, short name) // 0x1067DA10
{
	// `anonymous-namespace'::FindObjectByName
	// static ...; // 0x1067DAF4
	// static ...; // 0x1067DAEC
	// e_object_type type;
	// short name;
	// c_data_array<s_object_header> *object_headers;
	{
		// c_data_iterator<s_object_header> it;
	}
	todo("implement");
	unsigned long __result = _sub_1067DA10(type, name);
	return __result;
}

extern s_forge_sky_definition *_sub_1067DB40();
s_forge_sky_definition *GetForgeSky() // 0x1067DB40
{
	// `anonymous-namespace'::GetForgeSky
	// procedure flags: nofpo
	// s_forge_globals_definition *forge_globals;
	todo("implement");
	s_forge_sky_definition * __result = _sub_1067DB40();
	return __result;
}

_extern void _sub_1067E7D0(long);
void ReplaceForgeSkyScenery(long newSceneryTagIndex) // 0x1067E7D0
{
	// `anonymous-namespace'::ReplaceForgeSkyScenery
	// static ...; // 0x1067EA54
	// static ...; // 0x1067EA48
	// static ...; // 0x1067EA40
	// long newSceneryTagIndex;
	// long skySceneryIndex;
	// s_scenario *scenario;
	// s_object_placement_data objectPlacementData;
	{
		// c_tag_block<s_scenario_sky_reference> &<range>$L0;
		// s_scenario_sky_reference *<begin>$L0;
		// s_scenario_sky_reference *<end>$L0;
		{
			// s_scenario_sky_reference &skyRef;
			{
				// s_scenario_scenery *<end>$L1;
				// s_scenario_scenery *<begin>$L1;
				// c_tag_block<s_scenario_scenery> &<range>$L1;
				{
					// s_scenario_scenery &scenery;
					{
						// unsigned long objectIndex;
					}
				}
			}
		}
	}
	{
		// s_object_data *skyObject;
	}
	// function call : void (*const)(long)
	// function call : void (*const)(long)
	// function call : void (*const)(s_object_placement_data *, long, unsigned long, s_damage_owner *)
	// function call : long (*const)(s_object_placement_data *)
	todo("implement");
	_sub_1067E7D0(newSceneryTagIndex);
}

_extern void _sub_1067E230(s_forge_sky_definition *);
void ReplaceForgeSky(s_forge_sky_definition *desiredSky) // 0x1067E230
{
	// `anonymous-namespace'::ReplaceForgeSky
	// static ...; // 0x1067E6A1
	// static ...; // 0x1067E69E
	// static ...; // 0x1067E69B
	// static ...; // 0x1067E698
	// static ...; // 0x1067E668
	// static ...; // 0x1067E660
	// s_forge_sky_definition *desiredSky;
	// c_data_array<s_screen_effect_datum> *screenEffects;
	// s_scenario *scenario;
	// c_data_array<s_game_looping_sound_datum> *loopingSounds;
	{
		// c_data_iterator<s_screen_effect_datum> it;
	}
	{
		// unsigned long unit_index;
		{
			// c_data_iterator<s_screen_effect_datum> it;
		}
	}
	{
		// c_data_array<s_object_header> *object_headers;
		// long skyObjectTagIndex;
		{
			// c_data_iterator<s_object_header> it;
		}
	}
	{
		// c_data_iterator<s_game_looping_sound_datum> it;
	}
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(unsigned long)
	// function call : void (*const)(unsigned long)
	// function call : long (*const)(long, long, float)
	todo("implement");
	_sub_1067E230(desiredSky);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_data_iterator<s_game_looping_sound_datum>::operator!=(c_data_iterator<s_game_looping_sound_datum> const &) const;
template bool c_data_iterator<s_game_looping_sound_datum>::operator==(c_data_iterator<s_game_looping_sound_datum> const &) const;
template bool c_data_iterator<s_screen_effect_datum>::operator!=(c_data_iterator<s_screen_effect_datum> const &) const;
template bool c_data_iterator<s_screen_effect_datum>::operator==(c_data_iterator<s_screen_effect_datum> const &) const;
template bool c_tag_block<s_forge_sky_definition>::try_get_element(__int32, s_forge_sky_definition **) const;
template bool c_tag_block<s_scenario_acoustics_palette_entry>::try_get_element(__int32, s_scenario_acoustics_palette_entry **) const;
template bool c_tag_block<s_scenario_sky_reference>::try_get_element(__int32, s_scenario_sky_reference **) const;
template bool c_tag_block<s_scenario_structure_bsp_reference>::try_get_element(__int32, s_scenario_structure_bsp_reference **) const;
template bool c_tag_block_index<s_scenario_object_name,short>::operator==(short) const;
template c_data_iterator<s_game_looping_sound_datum> & c_data_iterator<s_game_looping_sound_datum>::operator++();
template c_data_iterator<s_game_looping_sound_datum> c_data_array<s_game_looping_sound_datum>::begin();
template c_data_iterator<s_game_looping_sound_datum> c_data_array<s_game_looping_sound_datum>::end();
template c_data_iterator<s_game_looping_sound_datum>::c_data_iterator(s_data_array *);
template c_data_iterator<s_screen_effect_datum> & c_data_iterator<s_screen_effect_datum>::operator++();
template c_data_iterator<s_screen_effect_datum> c_data_array<s_screen_effect_datum>::begin();
template c_data_iterator<s_screen_effect_datum> c_data_array<s_screen_effect_datum>::end();
template c_data_iterator<s_screen_effect_datum>::c_data_iterator(s_data_array *);
template c_enum<enum e_game_engine_symmetric_placement,long>::c_enum();
template c_enum<enum e_multiplayer_object_boundary_shape,char>::c_enum();
template c_enum<enum e_multiplayer_object_placement_spawn_flags,unsigned char>::c_enum();
template c_enum<enum e_multiplayer_team_designator,short>::c_enum();
template c_enum<enum e_multiplayer_teleporter_channel,char>::c_enum();
template c_enum<enum e_object_type,char>::c_enum();
template c_enum<enum e_object_type,char>::operator enum e_object_type() const;
template c_enum<enum e_object_type,long>::c_enum(long const &);
template c_enum<enum e_scenario_object_source,char>::c_enum();
template c_flags<enum e_game_engine_flags,unsigned short>::c_flags();
template c_flags<enum e_game_looping_sound_flag,unsigned short> c_flags<enum e_game_looping_sound_flag,unsigned short>::operator&(__int32 const) const;
template c_flags<enum e_game_looping_sound_flag,unsigned short>::c_flags(unsigned short const &);
template c_flags<enum e_game_looping_sound_flag,unsigned short>::operator bool() const;
template c_flags<enum e_multiplayer_object_teleporter_flags,unsigned char>::c_flags();
template c_tag_block_index<s_scenario_object_name,short>::operator short() const;
template c_tag_block_index<s_scenario_structure_bsp_reference,short>::c_tag_block_index();
template c_tag_block_index<s_scenario_structure_bsp_reference,short>::c_tag_block_index(short);
template s_forge_sky_definition & c_tag_block<s_forge_sky_definition>::operator[](__int32);
template s_forge_sky_definition * c_tag_block<s_forge_sky_definition>::get_element(__int32) const;
template s_game_looping_sound_datum & c_data_iterator<s_game_looping_sound_datum>::next();
template s_game_looping_sound_datum * c_data_iterator<s_game_looping_sound_datum>::operator->();
template s_scenario_acoustics_palette_entry & c_tag_block<s_scenario_acoustics_palette_entry>::operator[](__int32);
template s_scenario_acoustics_palette_entry * c_tag_block<s_scenario_acoustics_palette_entry>::get_element(__int32) const;
template s_scenario_scenery * c_tag_block<s_scenario_scenery>::begin();
template s_scenario_scenery * c_tag_block<s_scenario_scenery>::end();
template s_scenario_sky_reference & c_tag_block<s_scenario_sky_reference>::operator[](__int32);
template s_scenario_sky_reference * c_tag_block<s_scenario_sky_reference>::begin();
template s_scenario_sky_reference * c_tag_block<s_scenario_sky_reference>::end();
template s_scenario_sky_reference * c_tag_block<s_scenario_sky_reference>::get_element(__int32) const;
template s_scenario_structure_bsp_reference & c_tag_block<s_scenario_structure_bsp_reference>::operator[](__int32);
template s_scenario_structure_bsp_reference * c_tag_block<s_scenario_structure_bsp_reference>::get_element(__int32) const;
template s_screen_effect_datum & c_data_iterator<s_screen_effect_datum>::next();
template s_screen_effect_datum * c_data_iterator<s_screen_effect_datum>::operator->();
template unsigned long c_data_array<s_screen_effect_datum>::delete_datum(unsigned long);
