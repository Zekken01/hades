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
		bool useMapModifierTransform = false; // 0x0
		// hades: no padding member (0x1), `state = {}` never writes it
		long SkyIndex = -1; // 0x4
		long SceneryObjectIndex = -1; // 0x8
		long BackgroundSoundDatumIndex = -1; // 0xC
		long ScreenEffectDatumIndex = -1; // 0x10
		// ForgeSkyState(); /* compiler_generated() */ - the implicit one
	};
	static_assert(sizeof(ForgeSkyState) == 20, "Invalid ForgeSkyState size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named from the game's own symbols.
	static auto const unattached_looping_sound_start = reinterpret_cast<long (*)(long, long, float)>(0x5DE1F0);
	static auto const unattached_looping_sound_stop = reinterpret_cast<void (*)(unsigned long)>(0x5DE2D0);
}

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const player_mapping_get_unit_by_output_user = reinterpret_cast<unsigned long (*)(long)>(0x589CC0);
}

extern void (*const object_set_position)(unsigned long, real_point3d *, real_vector3d *, real_vector3d *, s_scenario_location *);  // hades: added for 0x1067EB10
extern void vectors3d_from_euler_angles3d(real_vector3d *forward, real_vector3d *up, real_euler_angles3d const *angles);  // hades: added for 0x1067EB10
extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0x1067EB10

extern void (*const object_placement_data_new)(s_object_placement_data *, long, unsigned long, s_damage_owner *);  // hades: added for 0x1067E7D0

unsigned long FindObjectByName(e_object_type type, short name);
s_forge_sky_definition *GetForgeSky();
void ReplaceForgeSkyScenery(long newSceneryTagIndex);
void ReplaceForgeSky(s_forge_sky_definition *desiredSky);
extern long screen_effect_new(long definition_index, long attach_object_index, short attach_node_index, real_point3d const *position, real_rectangle2d const *bounds);  // hades: added for 0x1067E230

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	namespace hades_file_local_ForgeSkies { extern real_rectangle2d global_null_rectangle2d; } using namespace hades_file_local_ForgeSkies; // 0x11172F9C
	extern ForgeSkyState state; // 0x1134D10C
	extern s_forge_sky_definition mapDefaultSky; // 0x11371850
}
using namespace hades_file_local;
/* ---------- public code */

// mangled_x86(MANGLED_DEFAULT, "??0c_object_identifier@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0s_multiplayer_object_properties_definition@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0s_object_placement_data@@QAE@XZ"); no body to assert in

namespace Forge
{
	void CForgeSkies::InitializeForNewMap() // 0x1067DE20
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?InitializeForNewMap@CForgeSkies@Forge@@SAXXZ");

		state = {};
		if (!forge_globals_get_definition())
			return;
		s_tag_reference null_tag_reference = { 0xFFFFFFFF, nullptr, 0, 0xFFFFFFFF };
		s_scenario *scenario = global_scenario_get();
		if (scenario->skies.count && scenario->skies[0].sky_object.index != 0xFFFFFFFF)
			mapDefaultSky.object = scenario->skies[0].sky_object;
		else
			mapDefaultSky.object = null_tag_reference;
		mapDefaultSky.global_lighting = scenario->global_lighting;
		mapDefaultSky.parameters = scenario->sky_parameters;
		mapDefaultSky.screen_fx = scenario->default_screen_fx;
		mapDefaultSky.camera_fx = scenario->default_camera_fx;
		mapDefaultSky.wind = *(s_tag_reference *)scenario->structure_bsps[0].wind;
		if (scenario->background_sound_environment_palette.count > 0)
			mapDefaultSky.background_sound = scenario->background_sound_environment_palette[0].ambience.background_sound;
		else
			mapDefaultSky.background_sound = null_tag_reference;
	}

	void CForgeSkies::Update(long modifierObjectIndex, Forge::ForgeMapModifierProperties &mapModifierProperties) // 0x1067EB10
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Update@CForgeSkies@Forge@@SAXJAAUForgeMapModifierProperties@2@@Z");

		s_forge_globals_definition *forge_globals = forge_globals_get_definition();
		if (!forge_globals->skies.count)
			return;
		long desiredSkyIndex = mapModifierProperties.AtmosphereProperties.Skybox - 1;
		if (desiredSkyIndex != state.SkyIndex)
		{
			s_forge_globals_definition *forge_globals = forge_globals_get_definition();
			s_forge_sky_definition *desiredSky;
			if (desiredSkyIndex < 0 || desiredSkyIndex >= forge_globals->skies.count)
				desiredSky = &mapDefaultSky;
			else
				desiredSky = &forge_globals->skies[desiredSkyIndex];
			ReplaceForgeSky(desiredSky);
			state.SkyIndex = desiredSkyIndex;
		}
		if (state.SkyIndex != -1 && state.SceneryObjectIndex != -1)
		{
			state.useMapModifierTransform = (mapModifierProperties.AtmosphereProperties.Flags & 2) != 0;
			if (object_try_and_get_and_verify_type(state.SceneryObjectIndex, -1))
			{
				if (state.useMapModifierTransform)
				{
					s_object_data *mapModifierObject = object_try_and_get_and_verify_type(modifierObjectIndex, -1);
					if (mapModifierObject)
					{
						float zOffset = (mapModifierProperties.AtmosphereProperties.SkyboxZOffset / 255.0f * 2.0f - 1.0f) * 500.0f;
						real_point3d position = mapModifierObject->relative_position;
						position.z += zOffset;
						object_set_position(state.SceneryObjectIndex, &position, &mapModifierObject->forward, &mapModifierObject->up, nullptr);
					}
				}
				else
				{
					s_forge_sky_definition *forgeSky = GetForgeSky();
					real_vector3d forward;
					real_vector3d up;
					if (!forgeSky)
						return;
					vectors3d_from_euler_angles3d(&forward, &up, &forgeSky->orientation);
					object_set_position(state.SceneryObjectIndex, &forgeSky->translation, &forward, &up, nullptr);
				}
			}
		}
	}

	void CForgeSkies::HandleMapModifierDeleted() // 0x1067DBE0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?HandleMapModifierDeleted@CForgeSkies@Forge@@SAXXZ");

		if (!IsActive())
			return;
		s_scenario *scenario = global_scenario_get();
		ReplaceForgeSkyScenery(mapDefaultSky.object.index);
		if (state.BackgroundSoundDatumIndex != -1)
		{
			eldorado::unattached_looping_sound_stop(state.BackgroundSoundDatumIndex);
			state.BackgroundSoundDatumIndex = -1;
		}
		if (state.ScreenEffectDatumIndex != -1)
		{
			tls_getd().screen_effects->delete_datum(state.ScreenEffectDatumIndex);
			state.ScreenEffectDatumIndex = -1;
		}
		scenario->sky_parameters = mapDefaultSky.parameters;
		scenario->global_lighting = mapDefaultSky.global_lighting;
		scenario->default_camera_fx = mapDefaultSky.camera_fx;
		*(s_tag_reference *)scenario->structure_bsps[0].wind = mapDefaultSky.wind;
		state.SkyIndex = -1;
	}

	bool CForgeSkies::IsActive() // 0x1067E1C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?IsActive@CForgeSkies@Forge@@SA_NXZ");

		return GetForgeSky() != nullptr;
	}
}

/* ---------- private code */

unsigned long FindObjectByName(e_object_type type, short name) // 0x1067DA10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FindObjectByName@@YAKW4e_object_type@@F@Z");

	if (name == -1)
		return -1;
	c_data_array<s_object_header> *object_headers = object_headers_get();
	for (c_data_iterator<s_object_header> it = object_headers->begin(); it != object_headers->end(); ++it)
	{
		if (it->type == type && it->data->name_index == name)
			return it.current_datum_index;
	}
	return -1;
}

s_forge_sky_definition *GetForgeSky() // 0x1067DB40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetForgeSky@@YAPAUs_forge_sky_definition@@XZ");

	s_forge_globals_definition *forge_globals = forge_globals_get_definition();
	if (state.SkyIndex < 0 || state.SkyIndex >= forge_globals->skies.count)
	{
		return nullptr;
	}

	return &forge_globals->skies[state.SkyIndex];
}

void ReplaceForgeSkyScenery(long newSceneryTagIndex) // 0x1067E7D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ReplaceForgeSkyScenery@@YAXJ@Z");

	s_scenario *scenario = global_scenario_get();
	for (s_scenario_sky_reference &skyRef : scenario->skies)
	{
		for (s_scenario_scenery &scenery : scenario->scenery)
		{
			if ((short)scenery.parent_id.parent_object_name != -1 && skyRef.name == (short)scenery.parent_id.parent_object_name)
			{
				unsigned long objectIndex = FindObjectByName(scenery.object_id.type, scenery.name);
				if (objectIndex != -1 && object_get(objectIndex))
					((void (*)(unsigned long))0xB2CD10)(objectIndex);
			}
		}
	}
	if (state.SceneryObjectIndex != -1)
	{
		if (object_get(state.SceneryObjectIndex))
			((void (*)(unsigned long))0xB2CD10)(state.SceneryObjectIndex);
		state.SceneryObjectIndex = -1;
	}
	if (newSceneryTagIndex == -1)
		return;
	s_object_placement_data objectPlacementData;
	object_placement_data_new(&objectPlacementData, newSceneryTagIndex, -1, nullptr);
	objectPlacementData.placement_flags = 0x40;
	long skySceneryIndex = ((long (*)(s_object_placement_data *))0xB30440)(&objectPlacementData);
	if (skySceneryIndex != -1)
	{
		s_object_data *skyObject = object_get(skySceneryIndex);
		if (skyObject)
			state.SceneryObjectIndex = skySceneryIndex;
	}
}

void ReplaceForgeSky(s_forge_sky_definition *desiredSky) // 0x1067E230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ReplaceForgeSky@@YAXPAUs_forge_sky_definition@@@Z");

	s_scenario *scenario = global_scenario_get();
	c_data_array<s_screen_effect_datum> *screenEffects = tls_getd().screen_effects;
	if (scenario->default_screen_fx.index != -1)
	{
		for (c_data_iterator<s_screen_effect_datum> it = screenEffects->begin(); it != screenEffects->end(); ++it)
		{
			if (it->definition_index == scenario->default_screen_fx.index)
				screenEffects->delete_datum(it.current_datum_index);
		}
	}
	if (state.ScreenEffectDatumIndex != -1)
	{
		screenEffects->delete_datum(state.ScreenEffectDatumIndex);
		state.ScreenEffectDatumIndex = -1;
	}
	if (desiredSky->screen_fx.index != -1)
	{
		unsigned long unit_index = eldorado::player_mapping_get_unit_by_output_user(0);
		screen_effect_new(desiredSky->screen_fx.index, unit_index, 0, &global_origin3d, &global_null_rectangle2d);
		for (c_data_iterator<s_screen_effect_datum> it = screenEffects->begin(); it != screenEffects->end(); ++it)
		{
			if (it->definition_index == desiredSky->screen_fx.index)
				state.ScreenEffectDatumIndex = it.current_datum_index;
		}
	}
	if (state.SceneryObjectIndex == -1 && scenario->skies.count > 0)
	{
		long skyObjectTagIndex = scenario->skies[0].sky_object.index;
		c_data_array<s_object_header> *object_headers = object_headers_get();
		for (c_data_iterator<s_object_header> it = object_headers->begin(); it != object_headers->end(); ++it)
		{
			if (it->type == _object_type_scenery && skyObjectTagIndex == it->data->definition_index)
				state.SceneryObjectIndex = it.current_datum_index;
		}
	}
	c_data_array<s_game_looping_sound_datum> *loopingSounds = tls_getd().object_looping_sounds;
	for (c_data_iterator<s_game_looping_sound_datum> it = loopingSounds->begin(); it != loopingSounds->end(); ++it)
	{
		if (it->flags & 3)
			eldorado::unattached_looping_sound_stop(it.current_datum_index);
	}
	if (state.BackgroundSoundDatumIndex != -1)
	{
		eldorado::unattached_looping_sound_stop(state.BackgroundSoundDatumIndex);
		state.BackgroundSoundDatumIndex = -1;
	}
	state.BackgroundSoundDatumIndex = eldorado::unattached_looping_sound_start(desiredSky->background_sound.index, -1, 1.0f);
	ReplaceForgeSkyScenery(desiredSky->object.index);
	scenario->sky_parameters = desiredSky->parameters;
	scenario->global_lighting = desiredSky->global_lighting;
	scenario->default_camera_fx = desiredSky->camera_fx;
	*(s_tag_reference *)scenario->structure_bsps[0].wind = desiredSky->wind;
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

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { s_forge_sky_definition mapDefaultSky; }
namespace hades_file_local { namespace hades_file_local_ForgeSkies { real_rectangle2d global_null_rectangle2d; } }
namespace hades_file_local { ForgeSkyState state; }
