/* ---------- headers */

#include "Forge/ObjectProperties/ForgeObjectPropertyAccessor.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/saved_games/scenario_map_variant.hpp"
#include "Blam/simulation/simulation_queue_global_events.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeDevice.hpp"
#include "Forge/ForgeObjectProperties.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/ObjectProperties/ForgePropertyValue.hpp"
#include "Patches/GamePatches.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <limits>
#include <list>
#include <memory>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>

/* ---------- forward declarations */

struct CForgeDeviceObjectProperties;
struct begin;
struct end;
struct s_map_variant_placement_properties;
struct s_multiplayer_object_properties;
struct s_object_data;
struct s_simulation_queue_sandbox_event_data;
struct s_variant_quota;
namespace Forge
{
	class CDefaultPropertyAccessor;
	class CDeferredPropertySetter;
	class CObjectPropertyAccessor;
	struct ForgeGarbageVolumeProperties;
	struct ForgeKillVolumeProperties;
	struct ForgeLightProperties;
	struct ForgeMapModifierProperties;
	struct ForgeScreenFxProperties;
	struct ReforgeObjectProperties;
	struct SPropertyValue;
}
namespace
{
	struct SPixel24;
}

namespace Utils {}
using namespace ::Utils;
namespace Forge {}
using namespace ::Forge;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Game {}
	using namespace Patches::Game;
}

/* ---------- constants */

/* ---------- definitions */

namespace
{
	struct SPixel24
	{
		unsigned char R; // 0x0
		unsigned char G; // 0x1
		unsigned char B; // 0x2
	};
	static_assert(sizeof(SPixel24) == 3, "Invalid SPixel24 size");
}
/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Forge
{
	extern CDefaultPropertyAccessor* _sub_1083AD10(::Forge::CDefaultPropertyAccessor *const, long, long);
	CDefaultPropertyAccessor::CDefaultPropertyAccessor(long playerIndex, long objectIndex) // 0x1083AD10
	{
		mangled_x86(MANGLED_TODO, "??0CDefaultPropertyAccessor@Forge@@QAE@JJ@Z");
		// long objectIndex;
		todo("implement");
		_sub_1083AD10(this, playerIndex, objectIndex);
	}

	extern CObjectPropertyAccessor* _sub_1083AD90(::Forge::CObjectPropertyAccessor *const);
	_inline CObjectPropertyAccessor::CObjectPropertyAccessor() // 0x1083AD90
	{
		mangled_x86(MANGLED_TODO, "??0CObjectPropertyAccessor@Forge@@QAE@XZ");
		// Forge::CObjectPropertyAccessor *const this;
		compiler_generated();
		todo("implement");
		_sub_1083AD90(this);
	}
}

extern s_map_variant_placement_properties* _sub_1083AEF0(s_map_variant_placement_properties *const);
_inline s_map_variant_placement_properties::s_map_variant_placement_properties() // 0x1083AEF0
{
	mangled_x86(MANGLED_TODO, "??0s_map_variant_placement_properties@@QAE@XZ");
	// s_map_variant_placement_properties *const this;
	compiler_generated();
	todo("implement");
	_sub_1083AEF0(this);
}

extern s_simulation_queue_sandbox_event_data* _sub_1083AF60(s_simulation_queue_sandbox_event_data *const);
_inline s_simulation_queue_sandbox_event_data::s_simulation_queue_sandbox_event_data() // 0x1083AF60
{
	mangled_x86(MANGLED_TODO, "??0s_simulation_queue_sandbox_event_data@@QAE@XZ");
	// s_simulation_queue_sandbox_event_data *const this;
	compiler_generated();
	todo("implement");
	_sub_1083AF60(this);
}

namespace Forge
{
	extern SPropertyValue _sub_1083DE60(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty);
	::Forge::SPropertyValue CDefaultPropertyAccessor::GetPropertyValue(::Forge::EObjectProperty property) // 0x1083DE60
	{
		mangled_x86(MANGLED_TODO, "?GetPropertyValue@CDefaultPropertyAccessor@Forge@@UAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
	// $LN93:
	// $LN90:
	// $LN89:
	// $LN85:
	// $LN83:
	// $LN65:
	// $LN62:
	// $LN55:
	// $LN41:
	// $LN30:
	// $LN18:
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		todo("implement");
		::Forge::SPropertyValue __result = _sub_1083DE60(this, property);
		return __result;
	}

	_extern void _sub_1083B2A0(::Forge::CDefaultPropertyAccessor *const);
	_inline CDefaultPropertyAccessor::~CDefaultPropertyAccessor() // 0x1083B2A0
	{
		mangled_x86(MANGLED_TODO, "??1CDefaultPropertyAccessor@Forge@@UAE@XZ");
		// Forge::CDefaultPropertyAccessor *const this;
		compiler_generated();
		todo("implement");
		_sub_1083B2A0(this);
	}

	_extern void _sub_108407C0(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty, ::Forge::SPropertyValue);
	void CDefaultPropertyAccessor::SetPropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x108407C0
	{
		mangled_x86(MANGLED_TODO, "?SetPropertyValue@CDefaultPropertyAccessor@Forge@@UAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
	// $LN90:
	// $LN89:
	// $LN85:
	// $LN83:
	// $LN65:
	// $LN62:
	// $LN55:
	// $LN41:
	// $LN30:
	// $LN18:
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// Forge::SPropertyValue value;
		todo("implement");
		_sub_108407C0(this, property, value);
	}

	extern SPropertyValue _sub_1083D110(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty);
	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetGeneralPropertyValue(::Forge::EObjectProperty property) // 0x1083D110
	{
		mangled_x86(MANGLED_TODO, "?GetGeneralPropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
	// $LN19:
	// $LN18:
	// $LN17:
	// $LN16:
	// $LN15:
	// $LN14:
	// $LN13:
	// $LN12:
	// $LN11:
	// $LN10:
	// $LN9:
	// $LN8:
	// $LN7:
	// $LN6:
	// $LN5:
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// s_multiplayer_object_properties *properties;
		// function call : s_multiplayer_object_properties *(*const)(unsigned long)
		todo("implement");
		::Forge::SPropertyValue __result = _sub_1083D110(this, property);
		return __result;
	}

	_extern void _sub_1083FA30(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty, ::Forge::SPropertyValue);
	_inline void CDefaultPropertyAccessor::SetGeneralPropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x1083FA30
	{
		mangled_x86(MANGLED_TODO, "?SetGeneralPropertyValue@CDefaultPropertyAccessor@Forge@@AAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
		// static ...; // 0x1083FCF0
		// static ...; // 0x1083FCE8
	// $LN28:
	// $LN27:
	// $LN26:
	// $LN25:
	// $LN24:
	// $LN23:
	// $LN22:
	// $LN21:
	// $LN20:
	// $LN19:
	// $LN18:
	// $LN17:
	// $LN16:
	// $LN12:
	// $LN9:
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// Forge::SPropertyValue value;
		// s_map_variant_placement_properties properties;
		todo("implement");
		_sub_1083FA30(this, property, value);
	}

	extern SPropertyValue _sub_1083E370(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty);
	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetReforgePropertyValue(::Forge::EObjectProperty property) // 0x1083E370
	{
		mangled_x86(MANGLED_TODO, "?GetReforgePropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
		// static ...; // 0x1083E67C
	// $LN17:
	// $LN16:
	// $LN15:
	// $LN14:
	// $LN13:
	// $LN12:
	// $LN11:
	// $LN10:
	// $LN9:
	// $LN8:
	// $LN7:
	// $LN6:
	// $LN5:
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// Forge::ReforgeObjectProperties *reforgeProperties;
		// s_multiplayer_object_properties *properties;
		// function call : s_multiplayer_object_properties *(*const)(unsigned long)
		todo("implement");
		::Forge::SPropertyValue __result = _sub_1083E370(this, property);
		return __result;
	}

	_extern void _sub_10840BF0(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty, ::Forge::SPropertyValue);
	_inline void CDefaultPropertyAccessor::SetReforgePropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x10840BF0
	{
		mangled_x86(MANGLED_TODO, "?SetReforgePropertyValue@CDefaultPropertyAccessor@Forge@@AAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
		// static ...; // 0x10840E4C
		// static ...; // 0x10840E40
		// static ...; // 0x10840E38
	// $LN22:
	// $LN19:
	// $LN18:
	// $LN17:
	// $LN16:
	// $LN15:
	// $LN14:
	// $LN11:
	// $LN8:
	// $LN7:
	// $LN6:
	// $LN5:
	// $LN4:
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// Forge::SPropertyValue value;
		// Forge::ReforgeObjectProperties *reforgeProperties;
		// s_map_variant_placement_properties properties;
		todo("implement");
		_sub_10840BF0(this, property, value);
	}

	extern SPropertyValue _sub_1083C880(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty);
	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetForgeLightPropertyValue(::Forge::EObjectProperty property) // 0x1083C880
	{
		mangled_x86(MANGLED_TODO, "?GetForgeLightPropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
	// $LN15:
	// $LN14:
	// $LN13:
	// $LN12:
	// $LN11:
	// $LN10:
	// $LN9:
	// $LN8:
	// $LN7:
	// $LN6:
	// $LN5:
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// s_multiplayer_object_properties *properties;
		// Forge::ForgeLightProperties *lightProperties;
		// function call : s_multiplayer_object_properties *(*const)(unsigned long)
		todo("implement");
		::Forge::SPropertyValue __result = _sub_1083C880(this, property);
		return __result;
	}

	_extern void _sub_1083F1D0(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty, ::Forge::SPropertyValue);
	_inline void CDefaultPropertyAccessor::SetForgeLightPropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x1083F1D0
	{
		mangled_x86(MANGLED_TODO, "?SetForgeLightPropertyValue@CDefaultPropertyAccessor@Forge@@AAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
		// static ...; // 0x1083F3F4
		// static ...; // 0x1083F3EC
	// $LN14:
	// $LN13:
	// $LN12:
	// $LN11:
	// $LN10:
	// $LN9:
	// $LN8:
	// $LN7:
	// $LN6:
	// $LN5:
	// $LN4:
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// Forge::SPropertyValue value;
		// s_map_variant_placement_properties properties;
		// Forge::ForgeLightProperties *lightProperties;
		todo("implement");
		_sub_1083F1D0(this, property, value);
	}

	extern SPropertyValue _sub_1083C420(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty);
	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetForgeFxPropertyValue(::Forge::EObjectProperty property) // 0x1083C420
	{
		mangled_x86(MANGLED_TODO, "?GetForgeFxPropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
	// $LN18:
	// $LN17:
	// $LN16:
	// $LN15:
	// $LN14:
	// $LN13:
	// $LN12:
	// $LN11:
	// $LN10:
	// $LN9:
	// $LN8:
	// $LN7:
	// $LN6:
	// $LN5:
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// Forge::ForgeScreenFxProperties *screenFxProperties;
		// s_multiplayer_object_properties *properties;
		// function call : s_multiplayer_object_properties *(*const)(unsigned long)
		todo("implement");
		::Forge::SPropertyValue __result = _sub_1083C420(this, property);
		return __result;
	}

	_extern void _sub_1083EE90(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty, ::Forge::SPropertyValue);
	_inline void CDefaultPropertyAccessor::SetForgeFxPropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x1083EE90
	{
		mangled_x86(MANGLED_TODO, "?SetForgeFxPropertyValue@CDefaultPropertyAccessor@Forge@@AAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
		// static ...; // 0x1083F0D8
		// static ...; // 0x1083F0D0
	// $LN17:
	// $LN16:
	// $LN15:
	// $LN14:
	// $LN13:
	// $LN12:
	// $LN11:
	// $LN10:
	// $LN9:
	// $LN8:
	// $LN7:
	// $LN6:
	// $LN5:
	// $LN4:
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// Forge::SPropertyValue value;
		// Forge::ForgeScreenFxProperties *screenFxProperties;
		// s_map_variant_placement_properties properties;
		todo("implement");
		_sub_1083EE90(this, property, value);
	}

	extern SPropertyValue _sub_1083D520(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty);
	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetKillVolumePropertyValue(::Forge::EObjectProperty property) // 0x1083D520
	{
		mangled_x86(MANGLED_TODO, "?GetKillVolumePropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
		// Forge::EObjectProperty property;
		// Forge::ForgeKillVolumeProperties *killVolumeProperties;
		// s_multiplayer_object_properties *properties;
		// function call : s_multiplayer_object_properties *(*const)(unsigned long)
		todo("implement");
		::Forge::SPropertyValue __result = _sub_1083D520(this, property);
		return __result;
	}

	_extern void _sub_1083FE10(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty, ::Forge::SPropertyValue);
	_inline void CDefaultPropertyAccessor::SetKillVolumePropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x1083FE10
	{
		mangled_x86(MANGLED_TODO, "?SetKillVolumePropertyValue@CDefaultPropertyAccessor@Forge@@AAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
		// static ...; // 0x1083FF8C
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// Forge::SPropertyValue value;
		// Forge::ForgeKillVolumeProperties *killVolumeProperties;
		// s_map_variant_placement_properties properties;
		todo("implement");
		_sub_1083FE10(this, property, value);
	}

	extern SPropertyValue _sub_1083CD70(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty);
	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetGarbageVolumePropertyValue(::Forge::EObjectProperty property) // 0x1083CD70
	{
		mangled_x86(MANGLED_TODO, "?GetGarbageVolumePropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
	// $LN11:
	// $LN10:
	// $LN9:
	// $LN8:
	// $LN7:
	// $LN6:
	// $LN5:
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// s_multiplayer_object_properties *properties;
		// Forge::ForgeGarbageVolumeProperties *garbageVolumeProperties;
		// function call : s_multiplayer_object_properties *(*const)(unsigned long)
		todo("implement");
		::Forge::SPropertyValue __result = _sub_1083CD70(this, property);
		return __result;
	}

	_extern void _sub_1083F600(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty, ::Forge::SPropertyValue);
	_inline void CDefaultPropertyAccessor::SetGarbageVolumePropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x1083F600
	{
		mangled_x86(MANGLED_TODO, "?SetGarbageVolumePropertyValue@CDefaultPropertyAccessor@Forge@@AAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
		// static ...; // 0x1083F8B8
		// static ...; // 0x1083F8B0
	// $LN16:
	// $LN14:
	// $LN12:
	// $LN10:
	// $LN8:
	// $LN6:
	// $LN4:
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// Forge::SPropertyValue value;
		// s_map_variant_placement_properties properties;
		// Forge::ForgeGarbageVolumeProperties *garbageVolumeProperties;
		todo("implement");
		_sub_1083F600(this, property, value);
	}

	extern SPropertyValue _sub_1083D700(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty);
	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetMapModifierPropertyValue(::Forge::EObjectProperty property) // 0x1083D700
	{
		mangled_x86(MANGLED_TODO, "?GetMapModifierPropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
	// $LN22:
	// $LN21:
	// $LN20:
	// $LN19:
	// $LN18:
	// $LN17:
	// $LN16:
	// $LN15:
	// $LN14:
	// $LN13:
	// $LN12:
	// $LN11:
	// $LN10:
	// $LN9:
	// $LN8:
	// $LN7:
	// $LN6:
	// $LN5:
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// s_multiplayer_object_properties *properties;
		// Forge::ForgeMapModifierProperties *mapModifierProperties;
		// function call : s_multiplayer_object_properties *(*const)(unsigned long)
		todo("implement");
		::Forge::SPropertyValue __result = _sub_1083D700(this, property);
		return __result;
	}

	_extern void _sub_10840020(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty, ::Forge::SPropertyValue);
	_inline void CDefaultPropertyAccessor::SetMapModifierPropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x10840020
	{
		mangled_x86(MANGLED_TODO, "?SetMapModifierPropertyValue@CDefaultPropertyAccessor@Forge@@AAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
		// static ...; // 0x1084039C
		// static ...; // 0x10840394
	// $LN25:
	// $LN24:
	// $LN23:
	// $LN22:
	// $LN21:
	// $LN20:
	// $LN19:
	// $LN18:
	// $LN17:
	// $LN16:
	// $LN13:
	// $LN12:
	// $LN11:
	// $LN10:
	// $LN9:
	// $LN8:
	// $LN6:
	// $LN4:
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// Forge::SPropertyValue value;
		// s_map_variant_placement_properties properties;
		// Forge::ForgeMapModifierProperties *mapModifierProperties;
		{
			// unsigned short &flags;
		}
		{
		}
		todo("implement");
		_sub_10840020(this, property, value);
	}

	extern SPropertyValue _sub_1083BEB0(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty);
	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetBudgetPropertyValue(::Forge::EObjectProperty property) // 0x1083BEB0
	{
		mangled_x86(MANGLED_TODO, "?GetBudgetPropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
		// static ...; // 0x1083BF90
		// static ...; // 0x1083BF88
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// s_variant_quota entry;
		todo("implement");
		::Forge::SPropertyValue __result = _sub_1083BEB0(this, property);
		return __result;
	}

	_extern void _sub_1083E930(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty, ::Forge::SPropertyValue);
	_inline void CDefaultPropertyAccessor::SetBudgetPropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x1083E930
	{
		mangled_x86(MANGLED_TODO, "?SetBudgetPropertyValue@CDefaultPropertyAccessor@Forge@@AAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
		// static ...; // 0x1083EA08
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// Forge::SPropertyValue value;
		// s_variant_quota entry;
		todo("implement");
		_sub_1083E930(this, property, value);
	}

	extern SPropertyValue _sub_1083C260(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty);
	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetForgeDevicePropertyValue(::Forge::EObjectProperty property) // 0x1083C260
	{
		mangled_x86(MANGLED_TODO, "?GetForgeDevicePropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
	// $LN8:
	// $LN7:
	// $LN6:
	// $LN5:
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// s_multiplayer_object_properties *properties;
		// CForgeDeviceObjectProperties *deviceProperties;
		// function call : s_multiplayer_object_properties *(*const)(unsigned long)
		todo("implement");
		::Forge::SPropertyValue __result = _sub_1083C260(this, property);
		return __result;
	}

	_extern void _sub_1083ECE0(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty, ::Forge::SPropertyValue);
	_inline void CDefaultPropertyAccessor::SetForgeDevicePropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x1083ECE0
	{
		mangled_x86(MANGLED_TODO, "?SetForgeDevicePropertyValue@CDefaultPropertyAccessor@Forge@@AAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
		// static ...; // 0x1083EE10
		// static ...; // 0x1083EE08
	// $LN7:
	// $LN6:
	// $LN5:
	// $LN4:
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// Forge::SPropertyValue value;
		// s_map_variant_placement_properties properties;
		// CForgeDeviceObjectProperties *deviceProperties;
		todo("implement");
		_sub_1083ECE0(this, property, value);
	}

	extern SPropertyValue _sub_1083CC40(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty);
	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetForgeSceneryPropertyValue(::Forge::EObjectProperty property) // 0x1083CC40
	{
		mangled_x86(MANGLED_TODO, "?GetForgeSceneryPropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
		// Forge::EObjectProperty property;
		// s_multiplayer_object_properties *properties;
		{
			// s_object_data *object;
		}
		// function call : s_multiplayer_object_properties *(*const)(unsigned long)
		todo("implement");
		::Forge::SPropertyValue __result = _sub_1083CC40(this, property);
		return __result;
	}

	_extern void _sub_1083F4E0(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty, ::Forge::SPropertyValue);
	void CDefaultPropertyAccessor::SetForgeSceneryPropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x1083F4E0
	{
		mangled_x86(MANGLED_TODO, "?SetForgeSceneryPropertyValue@CDefaultPropertyAccessor@Forge@@AAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
		// static ...; // 0x1083F5A0
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// Forge::SPropertyValue value;
		// s_map_variant_placement_properties properties;
		todo("implement");
		_sub_1083F4E0(this, property, value);
	}

	extern SPropertyValue _sub_1083C080(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty);
	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetForgeChangeColorsPropertyValue(::Forge::EObjectProperty property) // 0x1083C080
	{
		mangled_x86(MANGLED_TODO, "?GetForgeChangeColorsPropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
		// static ...; // 0x1083C1EC
		// static ...; // 0x1083C1E4
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// SPixel24 color;
		// s_multiplayer_object_properties *properties;
		// function call : s_multiplayer_object_properties *(*const)(unsigned long)
		todo("implement");
		::Forge::SPropertyValue __result = _sub_1083C080(this, property);
		return __result;
	}

	_extern void _sub_1083EB60(::Forge::CDefaultPropertyAccessor *const, ::Forge::EObjectProperty, ::Forge::SPropertyValue);
	_inline void CDefaultPropertyAccessor::SetForgeChangeColorsPropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x1083EB60
	{
		mangled_x86(MANGLED_TODO, "?SetForgeChangeColorsPropertyValue@CDefaultPropertyAccessor@Forge@@AAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
		// static ...; // 0x1083EC74
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// Forge::SPropertyValue value;
		// SPixel24 &color;
		// s_map_variant_placement_properties properties;
		todo("implement");
		_sub_1083EB60(this, property, value);
	}

	_extern void _sub_10840B70(::Forge::CDeferredPropertySetter *const, ::Forge::EObjectProperty, ::Forge::SPropertyValue);
	void CDeferredPropertySetter::SetPropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x10840B70
	{
		mangled_x86(MANGLED_TODO, "?SetPropertyValue@CDeferredPropertySetter@Forge@@UAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
		// Forge::SPropertyValue value;
		todo("implement");
		_sub_10840B70(this, property, value);
	}

	extern SPropertyValue _sub_1083E200(::Forge::CDeferredPropertySetter *const, ::Forge::EObjectProperty);
	::Forge::SPropertyValue CDeferredPropertySetter::GetPropertyValue(::Forge::EObjectProperty property) // 0x1083E200
	{
		mangled_x86(MANGLED_TODO, "?GetPropertyValue@CDeferredPropertySetter@Forge@@UAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
		// static ...; // 0x1083E318
		// static ...; // 0x1083E310
		// Forge::CDeferredPropertySetter *const this;
		// Forge::EObjectProperty property;
		{
			// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<enum Forge::EObjectProperty const ,Forge::SPropertyValue> > > > it;
		}
		todo("implement");
		::Forge::SPropertyValue __result = _sub_1083E200(this, property);
		return __result;
	}

	_extern void _sub_1083E8E0(::Forge::CDeferredPropertySetter *const);
	void CDeferredPropertySetter::Reset() // 0x1083E8E0
	{
		mangled_x86(MANGLED_TODO, "?Reset@CDeferredPropertySetter@Forge@@QAEXXZ");
		// Forge::CDeferredPropertySetter *const this;
		todo("implement");
		_sub_1083E8E0(this);
	}

	_extern void _sub_1083BD00(::Forge::CDeferredPropertySetter *const, long, long);
	void CDeferredPropertySetter::Apply(long playerIndex, long objectIndex) // 0x1083BD00
	{
		mangled_x86(MANGLED_TODO, "?Apply@CDeferredPropertySetter@Forge@@QAEXJJ@Z");
		// static ...; // 0x1083BE34
		// static ...; // 0x1083BE10
		// static ...; // 0x1083BE08
		// Forge::CDeferredPropertySetter *const this;
		// long playerIndex;
		// long objectIndex;
		// Forge::CDefaultPropertyAccessor accessor;
		{
			// std::unordered_map<enum Forge::EObjectProperty,Forge::SPropertyValue,std::hash<enum Forge::EObjectProperty>,std::equal_to<enum Forge::EObjectProperty>,std::allocator<std::pair<enum Forge::EObjectProperty const ,Forge::SPropertyValue> > > &<range>$L0;
			// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<enum Forge::EObjectProperty const ,Forge::SPropertyValue> > > > <begin>$L0;
			// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<enum Forge::EObjectProperty const ,Forge::SPropertyValue> > > > <end>$L0;
			{
				// std::pair<enum Forge::EObjectProperty const ,Forge::SPropertyValue> &value;
			}
		}
		todo("implement");
		_sub_1083BD00(this, playerIndex, objectIndex);
	}
}

/* ---------- private code */
