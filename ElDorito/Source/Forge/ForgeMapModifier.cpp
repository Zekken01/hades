/* ---------- headers */

#include "Forge/ForgeMapModifier.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/forge/forge_globals.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/engine/game_engine_sandbox.hpp"
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
#include "Blam/saved_games/scenario_map_variant.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeObjectProperties.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/Reforge.hpp"
#include "mods/map_variant_loader.hpp"

/* ---------- forward declarations */

struct real_point3d;
struct real_vector3d;
struct s_forge_globals_definition;
struct s_map_variant;
struct s_map_variant_placement_properties;
struct s_multiplayer_object_properties;
struct s_object_data;
struct s_object_header;
struct s_variant_datum;
namespace Forge
{
	class CForgeMapModifier;
	struct ForgeMapModifierProperties;
}
namespace hades_file_local
{
	struct ForgeMapModifierState;
}
using namespace hades_file_local;

namespace Forge {}
using namespace ::Forge;

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct ForgeMapModifierState
	{
		bool IsActive = false; // 0x0
		bool WaitingForNewRound = false; // 0x1
		long ObjectIndex = -1; // 0x4
	};
	static_assert(sizeof(ForgeMapModifierState) == 8, "Invalid ForgeMapModifierState size");
}
using namespace hades_file_local;
/* ---------- prototypes */

extern s_map_variant *(*const game_engine_get_runtime_map_variant)();  // hades: added for 0x1067C5A0

#include "Forge/ForgeWeather.hpp"  // hades: added for 0x1067C9B0
#include "Forge/ForgeSkies.hpp"  // hades: added for 0x1067C9B0
#include "Forge/ForgeAtmosphere.hpp"  // hades: added for 0x1067C9B0
#include "Forge/ForgeCameraFx.hpp"  // hades: added for 0x1067C9B0
#include "Forge/ForgeMapBarriers.hpp"  // hades: added for 0x1067C9B0
extern s_multiplayer_object_properties *(*const object_get_multiplayer)(unsigned long);  // hades: added for 0x1067C9B0

long FindMapModifierObject();
long CreateMapmodifierObject();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern ForgeMapModifierState state; // 0x1134D0C4
}
using namespace hades_file_local;
/* ---------- public code */

namespace Forge
{
	void CForgeMapModifier::InitializeForNewMap() // 0x1067C930
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?InitializeForNewMap@CForgeMapModifier@Forge@@SAXXZ");

		state = {};
	}

	void CForgeMapModifier::Update() // 0x1067C9B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Update@CForgeMapModifier@Forge@@SAXXZ");

		long mapModifierObjectIndex = FindMapModifierObject();
		state.ObjectIndex = mapModifierObjectIndex;
		bool roundInProgress = ((bool (__cdecl *)())0x550F90)();
		if ((mapModifierObjectIndex == -1 || state.WaitingForNewRound && roundInProgress) && state.IsActive)
		{
			state.IsActive = false;
			CForgeWeather::HandleMapModifierDeleted();
			CForgeSkies::HandleMapModifierDeleted();
			CForgeAtmosphere::HandleMapModifierDeleted();
			CForgeCameraFx::HandleMapModifierDeleted();
			CForgeMapBarriers::HandleMapModifierDeleted();
			((float (__cdecl *)(float))0x6818A0)(1.0f);
		}

		state.WaitingForNewRound = !roundInProgress;
		if (!roundInProgress)
			return;

		s_object_data *mapModifierObject = object_get(mapModifierObjectIndex);
		if (!mapModifierObject)
			return;
		s_multiplayer_object_properties *mpProperties = object_get_multiplayer(mapModifierObjectIndex);
		if (!mpProperties)
			return;

		state.IsActive = true;
		Forge::ForgeMapModifierProperties *mapModifierProperties = (Forge::ForgeMapModifierProperties *)((char *)mpProperties + 0x14);
		CForgeSkies::Update(mapModifierObjectIndex, *mapModifierProperties);
		CForgeWeather::Update(mapModifierObjectIndex, *mapModifierProperties);
		CForgeAtmosphere::Update(mapModifierObjectIndex, *mapModifierProperties);
		CForgeCameraFx::Update(mapModifierObjectIndex, *mapModifierProperties);
		CForgeMapBarriers::Update(mapModifierObjectIndex, *mapModifierProperties);
		((float (__cdecl *)(float))0x6818A0)(1.0f - mapModifierProperties->PhysicsGravity / 255.0f);
	}

	long CForgeMapModifier::GetOrCreateMapModifierObject() // 0x1067C8D0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetOrCreateMapModifierObject@CForgeMapModifier@Forge@@SAJXZ");

		long object_index = FindMapModifierObject();

		if (object_index == -1)
			object_index = CreateMapmodifierObject();

		return object_index;
	}

	void CForgeMapModifier::OnUndoRedoCompleted() // 0x1067C990
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?OnUndoRedoCompleted@CForgeMapModifier@Forge@@SAXXZ");

		state.WaitingForNewRound = true;
	}
}

/* ---------- private code */

long FindMapModifierObject() // 0x1067C780
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FindMapModifierObject@@YAJXZ");

	s_forge_globals_definition *forge_globals = forge_globals_get_definition();
	if (!forge_globals)
		return -1;
	c_data_array<s_object_header> *object_headers = object_headers_get();
	for (c_data_iterator<s_object_header> it = object_headers->begin(); it != object_headers->end(); ++it)
	{
		if (it->type != (e_object_type)7)
			continue;
		long definition_index = it->data->definition_index;
		if (definition_index == forge_globals->map_modifier_object.index)
			return it.current_datum_index;
	}
	return -1;
}

long CreateMapmodifierObject() // 0x1067C5A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CreateMapmodifierObject@@YAJXZ");

	s_forge_globals_definition *forge_globals = forge_globals_get_definition();
	if (!forge_globals)
		return -1;
	s_map_variant *map_variant = game_engine_get_runtime_map_variant();
	if (!map_variant)
		return -1;
	long object_index = ((long (__thiscall *)(s_map_variant *, long, long, long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, e_object_type, s_map_variant_placement_properties *, unsigned short))0x582110)(map_variant, forge_globals->map_modifier_object.index, -1, -1, &get_sandbox_globals()->player_cursor_position[0], &global_forward3d, &global_up3d, -1, (e_object_type)-1, nullptr, 0);
	if (object_index == -1)
		return -1;
	s_object_data *mapModifierObject = object_get(object_index);
	long playerIndex = ((long (*)(long))0x589C30)(0);
	s_variant_datum &placement = map_variant->objects[mapModifierObject->map_variant_index];
	placement.properties.boundry_shape = (char)4;
	((void (*)(long, long, s_map_variant_placement_properties *))0x59B720)(playerIndex, mapModifierObject->map_variant_index, &placement.properties);
	((void (*)(long, long))0x59B080)(playerIndex, mapModifierObject->map_variant_index);
	return object_index;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_data_iterator<s_object_header>::operator!=(c_data_iterator<s_object_header> const &) const;
template bool c_data_iterator<s_object_header>::operator==(c_data_iterator<s_object_header> const &) const;
template bool c_enum<enum e_object_type,char>::operator!=(e_object_type const &) const;
template bool c_enum<enum e_object_type,char>::operator==(e_object_type const &) const;
template c_data_iterator<s_object_header> & c_data_iterator<s_object_header>::operator++();
template c_data_iterator<s_object_header> c_data_array<s_object_header>::begin();
template c_data_iterator<s_object_header> c_data_array<s_object_header>::end();
template c_data_iterator<s_object_header>::c_data_iterator(s_data_array *);
template c_enum<enum e_multiplayer_object_boundary_shape,char> & c_enum<enum e_multiplayer_object_boundary_shape,char>::operator=(char const &);
template s_object_header & c_data_iterator<s_object_header>::next();
template s_object_header * c_data_iterator<s_object_header>::operator->();

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { ForgeMapModifierState state; }
