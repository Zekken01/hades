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
		bool IsActive; // 0x0
		bool WaitingForNewRound; // 0x1
		unsigned char __pad0[2]; // 0x2
		long ObjectIndex; // 0x4
		ForgeMapModifierState(); /* compiler_generated() */
	};
	static_assert(sizeof(ForgeMapModifierState) == 8, "Invalid ForgeMapModifierState size");
}
using namespace hades_file_local;
/* ---------- prototypes */

long FindMapModifierObject();
long CreateMapmodifierObject();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Forge
{
	_extern void _sub_1067C930();
	void CForgeMapModifier::InitializeForNewMap() // 0x1067C930
	{
		mangled_x86(MANGLED_TODO, "?InitializeForNewMap@CForgeMapModifier@Forge@@SAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_1067C930();
	}

	_extern void _sub_1067C9B0();
	void CForgeMapModifier::Update() // 0x1067C9B0
	{
		mangled_x86(MANGLED_TODO, "?Update@CForgeMapModifier@Forge@@SAXXZ");
		// procedure flags: nofpo
		// bool roundInProgress;
		// s_object_data *mapModifierObject;
		// long mapModifierObjectIndex;
		// s_multiplayer_object_properties *mpProperties;
		// Forge::ForgeMapModifierProperties *mapModifierProperties;
		// function call : bool (*const)()
		// function call : float (*const)(float)
		// function call : s_multiplayer_object_properties *(*const)(unsigned long)
		// function call : float (*const)(float)
		todo("implement");
		_sub_1067C9B0();
	}

	_extern long _sub_1067C8D0();
	long CForgeMapModifier::GetOrCreateMapModifierObject() // 0x1067C8D0
	{
		mangled_x86(MANGLED_TODO, "?GetOrCreateMapModifierObject@CForgeMapModifier@Forge@@SAJXZ");
		// procedure flags: nofpo
		// long object_index;
		todo("implement");
		long __result = _sub_1067C8D0();
		return __result;
	}

	_extern void _sub_1067C990();
	void CForgeMapModifier::OnUndoRedoCompleted() // 0x1067C990
	{
		mangled_x86(MANGLED_TODO, "?OnUndoRedoCompleted@CForgeMapModifier@Forge@@SAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_1067C990();
	}
}

/* ---------- private code */

_extern long _sub_1067C780();
long FindMapModifierObject() // 0x1067C780
{
	// `anonymous-namespace'::FindMapModifierObject
	// procedure flags: nofpo
	// static ...; // 0x1067C888
	// static ...; // 0x1067C87C
	// static ...; // 0x1067C874
	// c_data_array<s_object_header> *object_headers;
	// s_forge_globals_definition *forge_globals;
	{
		// c_data_iterator<s_object_header> it;
		{
			// long tagIndex;
		}
	}
	todo("implement");
	long __result = _sub_1067C780();
	return __result;
}

_extern long _sub_1067C5A0();
long CreateMapmodifierObject() // 0x1067C5A0
{
	// `anonymous-namespace'::CreateMapmodifierObject
	// procedure flags: nofpo
	// s_object_data *mapModifierObject;
	// s_variant_datum &placement;
	// long object_index;
	// long playerIndex;
	// s_map_variant *map_variant;
	// s_forge_globals_definition *forge_globals;
	// function call : s_map_variant *(*const)()
	// function call : long (*const)(s_map_variant *, long, long, long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, long, s_map_variant_placement_properties const *, short)
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, long, s_map_variant_placement_properties const *)
	// function call : void (*const)(long, long)
	todo("implement");
	long __result = _sub_1067C5A0();
	return __result;
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
