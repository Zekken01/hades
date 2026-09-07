/* ---------- headers */

#include "Forge/ForgeMapModifier.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
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
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeObjectProperties.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/Reforge.hpp"

/* ---------- forward declarations */

struct s_multiplayer_object_properties;
struct s_object_data;
namespace Forge
{
	class CForgeMapModifier;
	struct ForgeMapModifierProperties;
}
namespace
{
	struct ForgeMapModifierState;
}

namespace Forge {}
using namespace ::Forge;

/* ---------- constants */

/* ---------- definitions */

namespace
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
/* ---------- prototypes */

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
