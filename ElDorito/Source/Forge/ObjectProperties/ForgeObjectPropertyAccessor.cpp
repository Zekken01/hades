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
#include "mods/map_variant_loader.hpp"
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
struct s_map_variant;
struct s_map_variant_placement_properties;
struct s_multiplayer_object_properties;
struct s_object_data;
struct s_simulation_queue_sandbox_event_data;
struct s_variant_datum;
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
namespace hades_file_local
{
	struct SPixel24;
}
using namespace hades_file_local;

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

namespace hades_file_local
{
	struct SPixel24
	{
		unsigned char R; // 0x0
		unsigned char G; // 0x1
		unsigned char B; // 0x2
	};
	static_assert(sizeof(SPixel24) == 3, "Invalid SPixel24 size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Forge { s_map_variant *GetMapVariant(); }  // hades: added for 0X108406A0

_inline bool GetMapVariantObjectProperties(long objectIndex, s_map_variant_placement_properties *outProperties);
_inline bool SetMapVariantObjectProperties(long playerIndex, long objectIndex, s_map_variant_placement_properties &properties);
_inline bool GetMapVariantBudgetForObject(long objectIndex, s_variant_quota *outEntry);
_inline bool SetMapVariantBudgetForObject(long playerIndex, long objectIndex, s_variant_quota &entry);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Forge
{
	CDefaultPropertyAccessor::CDefaultPropertyAccessor(long playerIndex, long objectIndex) // 0x1083AD10
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0CDefaultPropertyAccessor@Forge@@QAE@JJ@Z");
		// long objectIndex;

		m_objectIndex = objectIndex;
		m_playerIndex = playerIndex;
	}

	// mangled_x86(MANGLED_DEFAULT, "??0CObjectPropertyAccessor@Forge@@QAE@XZ"); no body to assert in
	_inline CObjectPropertyAccessor::CObjectPropertyAccessor() = default; // 0x1083AD90
}

// mangled_x86(MANGLED_DEFAULT, "??0s_map_variant_placement_properties@@QAE@XZ"); no body to assert in
_inline s_map_variant_placement_properties::s_map_variant_placement_properties() = default; // 0x1083AEF0

// mangled_x86(MANGLED_DEFAULT, "??0s_simulation_queue_sandbox_event_data@@QAE@XZ"); no body to assert in
_inline s_simulation_queue_sandbox_event_data::s_simulation_queue_sandbox_event_data() = default; // 0x1083AF60

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

	void CDeferredPropertySetter::SetPropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x10840B70
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetPropertyValue@CDeferredPropertySetter@Forge@@UAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
		// Forge::SPropertyValue value;

		m_values[property] = value;
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

	void CDeferredPropertySetter::Reset() // 0x1083E8E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Reset@CDeferredPropertySetter@Forge@@QAEXXZ");
		// Forge::CDeferredPropertySetter *const this;

		m_values.clear();
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
			// std::unordered_map<enum Forge::EObjectProperty,Forge::SPropertyValue> &<range>$L0;
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

_extern bool _sub_1083DD90(long, s_map_variant_placement_properties *);
_inline bool GetMapVariantObjectProperties(long objectIndex, s_map_variant_placement_properties *outProperties) // 0x1083DD90
{
	// `anonymous-namespace'::GetMapVariantObjectProperties
	// s_map_variant_placement_properties *outProperties;
	// s_object_data *object;
	// s_map_variant_placement_properties *properties;
	todo("implement");
	bool __result = _sub_1083DD90(objectIndex, outProperties);
	return __result;
}

_inline bool SetMapVariantObjectProperties(long playerIndex, long objectIndex, s_map_variant_placement_properties &properties) // 0x108406A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetMapVariantObjectProperties@@YA_NJJAAUs_map_variant_placement_properties@@@Z");
	// `anonymous-namespace'::SetMapVariantObjectProperties
	// s_map_variant_placement_properties &properties;
	// s_object_data *object;
	// void (*const Forge_SetPlacementVariantProperties)(unsigned __int32, __int32, s_map_variant_placement_properties *);
	// function call : bool (*const)()
	// function call : void (*const)(unsigned __int32, __int32, s_map_variant_placement_properties *)

	void (__cdecl *const SetMapVariantObjectPropertiesInternal)(long, long, s_map_variant_placement_properties *) = (void(__cdecl *const)(long, long, s_map_variant_placement_properties *))0x59b720;

	s_object_data *object = object_get(objectIndex);
	if (!object)
		return false;
	if (object->map_variant_index == -1)
		return false;
	if (((bool(__cdecl *const)())0x5319c0)())
		memcpy(&Forge::GetMapVariant()->objects[object->map_variant_index].properties, &properties, sizeof(properties));
	SetMapVariantObjectPropertiesInternal(playerIndex, object->map_variant_index, &properties);
	return true;
}

_extern bool _sub_1083DCA0(long, s_variant_quota *);
_inline bool GetMapVariantBudgetForObject(long objectIndex, s_variant_quota *outEntry) // 0x1083DCA0
{
	// `anonymous-namespace'::GetMapVariantBudgetForObject
	// s_variant_quota *outEntry;
	// s_variant_datum &placement;
	// s_object_data *object;
	// s_map_variant *mapVariant;
	todo("implement");
	bool __result = _sub_1083DCA0(objectIndex, outEntry);
	return __result;
}

_extern bool _sub_10840500(long, long, s_variant_quota &);
_inline bool SetMapVariantBudgetForObject(long playerIndex, long objectIndex, s_variant_quota &entry) // 0x10840500
{
	// `anonymous-namespace'::SetMapVariantBudgetForObject
	// static ...; // 0x10840628
	// long playerIndex;
	// long objectIndex;
	// s_variant_quota &entry;
	// s_variant_datum &placement;
	// s_object_data *object;
	// s_simulation_queue_sandbox_event_data event_data;
	// s_map_variant *mapVariant;
	// function call : void (*const)(s_simulation_queue_sandbox_event_data *)
	todo("implement");
	bool __result = _sub_10840500(playerIndex, objectIndex, entry);
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_enum<enum e_game_engine_symmetric_placement,char>::operator char() const;
template c_enum<enum e_multiplayer_object_boundary_shape,char>::operator char() const;
template c_enum<enum e_multiplayer_teleporter_channel,unsigned char>::operator unsigned char() const;
template c_flags<enum e_game_engine_flags,unsigned short>::operator unsigned short() const;
template c_flags<enum e_game_engine_type,unsigned short> & c_flags<enum e_game_engine_type,unsigned short>::operator=(unsigned short const &);
template c_flags<enum e_game_engine_type,unsigned short>::c_flags();
template c_flags<enum e_multiplayer_object_flags,unsigned char>::operator unsigned char() const;
template c_flags<enum e_variant_placement_flags,unsigned char> & c_flags<enum e_variant_placement_flags,unsigned char>::operator&=(__int32 const);
template c_flags<enum e_variant_placement_flags,unsigned char> & c_flags<enum e_variant_placement_flags,unsigned char>::operator=(c_flags<enum e_variant_placement_flags,unsigned char> const &);
template c_flags<enum e_variant_placement_flags,unsigned char> & c_flags<enum e_variant_placement_flags,unsigned char>::operator|=(__int32 const);
template c_flags<enum e_variant_placement_flags,unsigned char> c_flags<enum e_variant_placement_flags,unsigned char>::operator&(__int32 const) const;
template c_flags<enum e_variant_placement_flags,unsigned char> c_flags<enum e_variant_placement_flags,unsigned char>::operator|(__int32 const) const;
template c_flags<enum e_variant_placement_flags,unsigned char>::c_flags();
template c_flags<enum e_variant_placement_flags,unsigned char>::c_flags(unsigned char const &);
