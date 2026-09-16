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

extern s_multiplayer_object_properties *(*const object_get_multiplayer)(unsigned long);  // hades: added for 0x1083CC40

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
}

// mangled_x86(MANGLED_DEFAULT, "??0s_map_variant_placement_properties@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0s_simulation_queue_sandbox_event_data@@QAE@XZ"); no body to assert in

namespace Forge
{
	::Forge::SPropertyValue CDefaultPropertyAccessor::GetPropertyValue(::Forge::EObjectProperty property) // 0x1083DE60
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetPropertyValue@CDefaultPropertyAccessor@Forge@@UAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
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

		switch (property)
		{
		case General_OnMapAtStart:
		case General_Symmetry:
		case General_RespawnRate:
		case General_SpareClips:
		case General_SpawnOrder:
		case General_Team:
		case General_TeleporterChannel:
		case General_ShapeType:
		case General_ShapeRadius:
		case General_ShapeWidth:
		case General_ShapeTop:
		case General_ShapeBottom:
		case General_ShapeDepth:
		case General_Physics:
		case General_EngineFlags:
			return GetGeneralPropertyValue(property);
		case Reforge_Material:
		case Reforge_Material_ColorR:
		case Reforge_Material_ColorG:
		case Reforge_Material_ColorB:
		case Reforge_Material_TextureOverride:
		case Reforge_Material_TextureScale:
		case Reforge_Material_TextureOffsetX:
		case Reforge_Material_TextureOffsetY:
		case Reforge_Material_AllowsProjectiles:
		case Reforge_Material_Type:
		case Reforge_TeamBarrier:
		case Reforge_Material_Climbable:
			return GetReforgePropertyValue(property);
		case Light_Type:
		case Light_ColorR:
		case Light_ColorG:
		case Light_ColorB:
		case Light_Intensity:
		case Light_Radius:
		case Light_FieldOfView:
		case Light_NearWidth:
		case Light_IlluminationType:
		case Light_IlluminationBase:
		case Light_IlluminationFreq:
			return GetForgeLightPropertyValue(property);
		case Fx_Range:
		case Fx_LightIntensity:
		case Fx_Hue:
		case Fx_Saturation:
		case Fx_Desaturation:
		case Fx_GammaIncrease:
		case Fx_GammaDecrease:
		case Fx_ColorFilterR:
		case Fx_ColorFilterG:
		case Fx_ColorFilterB:
		case Fx_ColorFloorR:
		case Fx_ColorFloorG:
		case Fx_ColorFloorB:
		case Fx_Tracing:
			return GetForgeFxPropertyValue(property);
		case GarbageVolume_CollectDeadBiped:
		case GarbageVolume_CollectWeapons:
		case GarbageVolume_CollectObjectives:
		case GarbageVolume_CollectGrenades:
		case GarbageVolume_CollectEquipment:
		case GarbageVolume_CollectVehicles:
		case GarbageVolume_Interval:
			return GetGarbageVolumePropertyValue(property);
		case KillVolume_AlwaysVisible:
		case KillVolume_DestroyVehicles:
		case KillVolume_DamageCause:
			return GetKillVolumePropertyValue(property);
		case Map_DisablePushBarrier:
		case Map_DisableDeathBarrier:
		case Map_PhysicsGravity:
		case CameraFx_Exposure:
		case CameraFx_LightIntensity:
		case CameraFx_Bloom:
		case CameraFx_LightBloom:
		case AtmosphereProperties_Enabled:
		case AtmosphereProperties_Weather:
		case AtmosphereProperties_Brightness:
		case AtmosphereProperties_FogDensity:
		case AtmosphereProperties_FogVisibility:
		case AtmosphereProperties_FogColorR:
		case AtmosphereProperties_FogColorG:
		case AtmosphereProperties_FogColorB:
		case AtmosphereProperties_Skybox:
		case AtmosphereProperties_SkyboxOffsetZ:
		case AtmosphereProperties_SkyboxOverrideTransform:
			return GetMapModifierPropertyValue(property);
		case Budget_Minimum:
		case Budget_Maximum:
			return GetBudgetPropertyValue(property);
		case Device_TurnRate:
		case Device_DoorOpenTime:
		case Device_TriggerRadius:
		case Device_DelayTime:
			return GetForgeDevicePropertyValue(property);
		case Scale:
			return GetForgeSceneryPropertyValue(property);
		case PrimaryChangeColorR:
		case PrimaryChangeColorG:
		case PrimaryChangeColorB:
			return GetForgeChangeColorsPropertyValue(property);
		default:
			throw std::runtime_error("not implemented");
		}
	}

	void CDefaultPropertyAccessor::SetPropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x108407C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetPropertyValue@CDefaultPropertyAccessor@Forge@@UAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
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

		switch (property)
		{
		case General_OnMapAtStart:
		case General_Symmetry:
		case General_RespawnRate:
		case General_SpareClips:
		case General_SpawnOrder:
		case General_Team:
		case General_TeleporterChannel:
		case General_ShapeType:
		case General_ShapeRadius:
		case General_ShapeWidth:
		case General_ShapeTop:
		case General_ShapeBottom:
		case General_ShapeDepth:
		case General_Physics:
		case General_EngineFlags:
			SetGeneralPropertyValue(property, value);
			break;
		case Reforge_Material:
		case Reforge_Material_ColorR:
		case Reforge_Material_ColorG:
		case Reforge_Material_ColorB:
		case Reforge_Material_TextureOverride:
		case Reforge_Material_TextureScale:
		case Reforge_Material_TextureOffsetX:
		case Reforge_Material_TextureOffsetY:
		case Reforge_Material_AllowsProjectiles:
		case Reforge_Material_Type:
		case Reforge_TeamBarrier:
		case Reforge_Material_Climbable:
			SetReforgePropertyValue(property, value);
			break;
		case Light_Type:
		case Light_ColorR:
		case Light_ColorG:
		case Light_ColorB:
		case Light_Intensity:
		case Light_Radius:
		case Light_FieldOfView:
		case Light_NearWidth:
		case Light_IlluminationType:
		case Light_IlluminationBase:
		case Light_IlluminationFreq:
			SetForgeLightPropertyValue(property, value);
			break;
		case Fx_Range:
		case Fx_LightIntensity:
		case Fx_Hue:
		case Fx_Saturation:
		case Fx_Desaturation:
		case Fx_GammaIncrease:
		case Fx_GammaDecrease:
		case Fx_ColorFilterR:
		case Fx_ColorFilterG:
		case Fx_ColorFilterB:
		case Fx_ColorFloorR:
		case Fx_ColorFloorG:
		case Fx_ColorFloorB:
		case Fx_Tracing:
			SetForgeFxPropertyValue(property, value);
			break;
		case GarbageVolume_CollectDeadBiped:
		case GarbageVolume_CollectWeapons:
		case GarbageVolume_CollectObjectives:
		case GarbageVolume_CollectGrenades:
		case GarbageVolume_CollectEquipment:
		case GarbageVolume_CollectVehicles:
		case GarbageVolume_Interval:
			SetGarbageVolumePropertyValue(property, value);
			break;
		case KillVolume_AlwaysVisible:
		case KillVolume_DestroyVehicles:
		case KillVolume_DamageCause:
			SetKillVolumePropertyValue(property, value);
			break;
		case Map_DisablePushBarrier:
		case Map_DisableDeathBarrier:
		case Map_PhysicsGravity:
		case CameraFx_Exposure:
		case CameraFx_LightIntensity:
		case CameraFx_Bloom:
		case CameraFx_LightBloom:
		case AtmosphereProperties_Enabled:
		case AtmosphereProperties_Weather:
		case AtmosphereProperties_Brightness:
		case AtmosphereProperties_FogDensity:
		case AtmosphereProperties_FogVisibility:
		case AtmosphereProperties_FogColorR:
		case AtmosphereProperties_FogColorG:
		case AtmosphereProperties_FogColorB:
		case AtmosphereProperties_Skybox:
		case AtmosphereProperties_SkyboxOffsetZ:
		case AtmosphereProperties_SkyboxOverrideTransform:
			SetMapModifierPropertyValue(property, value);
			break;
		case Budget_Minimum:
		case Budget_Maximum:
			SetBudgetPropertyValue(property, value);
			break;
		case Device_TurnRate:
		case Device_DoorOpenTime:
		case Device_TriggerRadius:
		case Device_DelayTime:
			SetForgeDevicePropertyValue(property, value);
			break;
		case Scale:
			SetForgeSceneryPropertyValue(property, value);
			break;
		case PrimaryChangeColorR:
		case PrimaryChangeColorG:
		case PrimaryChangeColorB:
			SetForgeChangeColorsPropertyValue(property, value);
			break;
		default:
			throw std::runtime_error("not implemented");
		}
	}

	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetGeneralPropertyValue(::Forge::EObjectProperty property) // 0x1083D110
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetGeneralPropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
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

		s_multiplayer_object_properties *properties = object_get_multiplayer(m_objectIndex);

		if (!properties)
		{
			throw std::runtime_error("not a multiplayer object");
		}

		switch (property)
		{
		case General_OnMapAtStart:
			return Forge::SPropertyValue::Integer((((unsigned char)properties->definition_flags >> 7) & 1) == 0);
		case General_Symmetry:
			return Forge::SPropertyValue::Integer((char)properties->symmetry);
		case General_RespawnRate:
			return Forge::SPropertyValue::Integer(properties->spawn_time);
		case General_SpawnOrder:
			return Forge::SPropertyValue::Integer((unsigned char)properties->teleporter_channel);
		case General_SpareClips:
			return Forge::SPropertyValue::Integer(properties->spare_clips);
		case General_Team:
			return Forge::SPropertyValue::Integer((short)properties->team_designator);
		case General_EngineFlags:
			return Forge::SPropertyValue::Integer((unsigned short)properties->engine_flags);
		case General_TeleporterChannel:
			return Forge::SPropertyValue::Integer((unsigned char)properties->teleporter_channel);
		case General_ShapeType:
			return Forge::SPropertyValue::Integer((char)properties->boundary_shape);
		case General_ShapeRadius:
			return Forge::SPropertyValue::Real(properties->boundry_width);
		case General_ShapeTop:
			return Forge::SPropertyValue::Real(properties->boundry_top);
		case General_ShapeBottom:
			return Forge::SPropertyValue::Real(properties->boundry_bottom);
		case General_ShapeWidth:
			return Forge::SPropertyValue::Real(properties->boundry_width);
		case General_ShapeDepth:
			return Forge::SPropertyValue::Real(properties->boundry_length);
		case General_Physics:
			return Forge::SPropertyValue::Integer((char)properties->boundary_shape == 4);
		default:
			throw std::runtime_error("not implemented");
		}
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

	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetReforgePropertyValue(::Forge::EObjectProperty property) // 0x1083E370
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetReforgePropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
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

		s_multiplayer_object_properties *properties = object_get_multiplayer(m_objectIndex);

		if (!properties)
		{
			throw std::runtime_error("not a multiplayer object");
		}

		Forge::ReforgeObjectProperties *reforgeProperties = (Forge::ReforgeObjectProperties *)&properties->boundry_width;

		switch (property)
		{
		case Reforge_Material:
			return Forge::SPropertyValue::Integer((unsigned char)properties->teleporter_channel);
		case Reforge_Material_ColorR:
			return Forge::SPropertyValue::Real((float)reforgeProperties->ColorR / 255.0f);
		case Reforge_Material_ColorG:
			return Forge::SPropertyValue::Real((float)reforgeProperties->ColorG / 255.0f);
		case Reforge_Material_ColorB:
			return Forge::SPropertyValue::Real((float)reforgeProperties->ColorB / 255.0f);
		case Reforge_Material_TextureOverride:
			return Forge::SPropertyValue::Integer((reforgeProperties->Flags & Forge::ReforgeObjectProperties::MaterialOverrideTextureCoords) != 0);
		case Reforge_Material_TextureScale:
			return Forge::SPropertyValue::Real((float)reforgeProperties->TextureData.Scale / 255.0f * 4.0f);
		case Reforge_Material_TextureOffsetX:
			return Forge::SPropertyValue::Real((float)reforgeProperties->TextureData.OffsetX / 255.0f);
		case Reforge_Material_TextureOffsetY:
			return Forge::SPropertyValue::Real((float)reforgeProperties->TextureData.OffsetY / 255.0f);
		case Reforge_Material_AllowsProjectiles:
			return Forge::SPropertyValue::Integer((reforgeProperties->Flags & Forge::ReforgeObjectProperties::MaterialAllowsProjectiles) != 0);
		case Reforge_Material_Type:
			return Forge::SPropertyValue::Integer(reforgeProperties->MaterialType);
		case Reforge_TeamBarrier:
			return Forge::SPropertyValue::Integer(reforgeProperties->TeamBarrier);
		case Reforge_Material_Climbable:
			return Forge::SPropertyValue::Integer((reforgeProperties->Flags & Forge::ReforgeObjectProperties::MaterialIsClimbable) != 0);
		default:
			throw std::runtime_error("not implemented");
		}
	}

	_inline void CDefaultPropertyAccessor::SetReforgePropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x10840BF0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetReforgePropertyValue@CDefaultPropertyAccessor@Forge@@AAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
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

		s_map_variant_placement_properties properties;

		GetMapVariantObjectProperties(m_objectIndex, &properties);

		Forge::ReforgeObjectProperties *reforgeProperties = (Forge::ReforgeObjectProperties *)&properties.boundry_width;

		switch (property)
		{
		case Reforge_Material:
			properties.shared_storage = (unsigned char)value.intValue;
			break;
		case Reforge_Material_ColorR:
			reforgeProperties->ColorR = (int)(value.realValue * 255.0f);
			break;
		case Reforge_Material_ColorG:
			reforgeProperties->ColorG = (int)(value.realValue * 255.0f);
			break;
		case Reforge_Material_ColorB:
			reforgeProperties->ColorB = (int)(value.realValue * 255.0f);
			break;
		case Reforge_Material_TextureOverride:
			if (value.intValue)
			{
				reforgeProperties->Flags |= Forge::ReforgeObjectProperties::MaterialOverrideTextureCoords;
			}
			else
			{
				reforgeProperties->Flags &= ~Forge::ReforgeObjectProperties::MaterialOverrideTextureCoords;
			}

			break;
		case Reforge_Material_AllowsProjectiles:
			if (value.intValue)
			{
				reforgeProperties->Flags |= Forge::ReforgeObjectProperties::MaterialAllowsProjectiles;
			}
			else
			{
				reforgeProperties->Flags &= ~Forge::ReforgeObjectProperties::MaterialAllowsProjectiles;
			}

			break;
		case Reforge_Material_TextureScale:
			reforgeProperties->TextureData.Scale = (int)(value.realValue / 4.0f * 255.0f);
			break;
		case Reforge_Material_TextureOffsetX:
			reforgeProperties->TextureData.OffsetX = (int)(value.realValue * 255.0f);
			break;
		case Reforge_Material_TextureOffsetY:
			reforgeProperties->TextureData.OffsetY = (int)(value.realValue * 255.0f);
			break;
		case Reforge_Material_Type:
			reforgeProperties->MaterialType = (unsigned char)value.intValue;
			break;
		case Reforge_TeamBarrier:
			reforgeProperties->TeamBarrier = (unsigned char)value.intValue;
			break;
		case Reforge_Material_Climbable:
			if (value.intValue)
			{
				reforgeProperties->Flags |= Forge::ReforgeObjectProperties::MaterialIsClimbable;
			}
			else
			{
				reforgeProperties->Flags &= ~Forge::ReforgeObjectProperties::MaterialIsClimbable;
			}

			break;
		default:
			throw std::runtime_error("not implemented");
		}

		SetMapVariantObjectProperties(m_playerIndex, m_objectIndex, properties);
	}

	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetForgeLightPropertyValue(::Forge::EObjectProperty property) // 0x1083C880
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetForgeLightPropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
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

		s_multiplayer_object_properties *properties = object_get_multiplayer(m_objectIndex);

		if (!properties)
		{
			throw std::runtime_error("not a multiplayer object");
		}

		Forge::ForgeLightProperties *lightProperties = (Forge::ForgeLightProperties *)&properties->boundry_width;

		switch (property)
		{
		case Light_Type:
			return Forge::SPropertyValue::Integer(lightProperties->Type);
		case Light_ColorR:
			return Forge::SPropertyValue::Real((float)lightProperties->ColorR / 255.0f);
		case Light_ColorG:
			return Forge::SPropertyValue::Real((float)lightProperties->ColorG / 255.0f);
		case Light_ColorB:
			return Forge::SPropertyValue::Real((float)lightProperties->ColorB / 255.0f);
		case Light_Intensity:
			return Forge::SPropertyValue::Real((float)lightProperties->Intensity / 255.0f * 2.0f);
		case Light_Radius:
			return Forge::SPropertyValue::Real((float)lightProperties->Range / 65535.0f * 50.0f);
		case Light_FieldOfView:
			return Forge::SPropertyValue::Real((float)lightProperties->FieldOfView / 255.0f * 180.0f);
		case Light_NearWidth:
			return Forge::SPropertyValue::Real((float)lightProperties->FieldOfView / 255.0f);
		case Light_IlluminationType:
			return Forge::SPropertyValue::Integer(lightProperties->Function.Type);
		case Light_IlluminationBase:
			return Forge::SPropertyValue::Real((float)lightProperties->Function.Base / 255.0f);
		case Light_IlluminationFreq:
			return Forge::SPropertyValue::Real((float)lightProperties->Function.Freq / 255.0f * 2.0f);
		default:
			throw std::runtime_error("not implemented");
		}
	}

	_inline void CDefaultPropertyAccessor::SetForgeLightPropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x1083F1D0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetForgeLightPropertyValue@CDefaultPropertyAccessor@Forge@@AAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
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

		s_map_variant_placement_properties properties;

		GetMapVariantObjectProperties(m_objectIndex, &properties);

		Forge::ForgeLightProperties *lightProperties = (Forge::ForgeLightProperties *)&properties.boundry_width;

		switch (property)
		{
		case Light_Type:
			lightProperties->Type = (unsigned char)value.intValue;
			break;
		case Light_ColorR:
			lightProperties->ColorR = (int)(value.realValue * 255.0f);
			break;
		case Light_ColorG:
			lightProperties->ColorG = (int)(value.realValue * 255.0f);
			break;
		case Light_ColorB:
			lightProperties->ColorB = (int)(value.realValue * 255.0f);
			break;
		case Light_Intensity:
			lightProperties->Intensity = (int)(value.realValue / 2.0f * 255.0f);
			break;
		case Light_Radius:
			lightProperties->Range = (int)(value.realValue / 50.0f * 65535.0f);
			break;
		case Light_FieldOfView:
			lightProperties->FieldOfView = (int)(value.realValue / 180.0f * 255.0f);
			break;
		case Light_NearWidth:
			lightProperties->NearWidth = (int)(value.realValue * 255.0f);
			break;
		case Light_IlluminationType:
			lightProperties->Function.Type = (unsigned char)value.intValue;
			break;
		case Light_IlluminationBase:
			lightProperties->Function.Base = (int)(value.realValue * 255.0f);
			break;
		case Light_IlluminationFreq:
			lightProperties->Function.Freq = (int)(value.realValue / 2.0f * 255.0f);
			break;
		default:
			throw std::runtime_error("not implemented");
		}

		SetMapVariantObjectProperties(m_playerIndex, m_objectIndex, properties);
	}

	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetForgeFxPropertyValue(::Forge::EObjectProperty property) // 0x1083C420
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetForgeFxPropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
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

		s_multiplayer_object_properties *properties = object_get_multiplayer(m_objectIndex);

		if (!properties)
		{
			throw std::runtime_error("not a multiplayer object");
		}

		Forge::ForgeScreenFxProperties *screenFxProperties = (Forge::ForgeScreenFxProperties *)&properties->boundry_width;

		switch (property)
		{
		case Fx_Range:
			return Forge::SPropertyValue::Integer(screenFxProperties->MaximumDistance);
		case Fx_LightIntensity:
			return Forge::SPropertyValue::Real((float)screenFxProperties->LightIntensity / 255.0f);
		case Fx_Hue:
			return Forge::SPropertyValue::Real((float)screenFxProperties->Hue / 255.0f);
		case Fx_Saturation:
			return Forge::SPropertyValue::Real((float)screenFxProperties->Saturation / 255.0f);
		case Fx_Desaturation:
			return Forge::SPropertyValue::Real((float)screenFxProperties->Desaturation / 255.0f);
		case Fx_GammaIncrease:
			return Forge::SPropertyValue::Real((float)screenFxProperties->GammaIncrease / 255.0f);
		case Fx_GammaDecrease:
			return Forge::SPropertyValue::Real((float)screenFxProperties->GammaDecrease / 255.0f);
		case Fx_ColorFilterR:
			return Forge::SPropertyValue::Real((float)screenFxProperties->ColorFilterR / 255.0f);
		case Fx_ColorFilterG:
			return Forge::SPropertyValue::Real((float)screenFxProperties->ColorFilterG / 255.0f);
		case Fx_ColorFilterB:
			return Forge::SPropertyValue::Real((float)screenFxProperties->ColorFilterB / 255.0f);
		case Fx_ColorFloorR:
			return Forge::SPropertyValue::Real((float)screenFxProperties->ColorFloorR / 255.0f);
		case Fx_ColorFloorG:
			return Forge::SPropertyValue::Real((float)screenFxProperties->ColorFloorG / 255.0f);
		case Fx_ColorFloorB:
			return Forge::SPropertyValue::Real((float)screenFxProperties->ColorFloorB / 255.0f);
		case Fx_Tracing:
			return Forge::SPropertyValue::Real((float)screenFxProperties->Tracing / 255.0f);
		default:
			throw std::runtime_error("not implemented");
		}
	}

	_inline void CDefaultPropertyAccessor::SetForgeFxPropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x1083EE90
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetForgeFxPropertyValue@CDefaultPropertyAccessor@Forge@@AAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
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

		s_map_variant_placement_properties properties;

		GetMapVariantObjectProperties(m_objectIndex, &properties);

		Forge::ForgeScreenFxProperties *screenFxProperties = (Forge::ForgeScreenFxProperties *)&properties.boundry_width;

		switch (property)
		{
		case Fx_ColorFilterR:
			screenFxProperties->ColorFilterR = (int)(value.realValue * 255.0f);
			break;
		case Fx_ColorFilterG:
			screenFxProperties->ColorFilterG = (int)(value.realValue * 255.0f);
			break;
		case Fx_ColorFilterB:
			screenFxProperties->ColorFilterB = (int)(value.realValue * 255.0f);
			break;
		case Fx_ColorFloorR:
			screenFxProperties->ColorFloorR = (int)(value.realValue * 255.0f);
			break;
		case Fx_ColorFloorG:
			screenFxProperties->ColorFloorG = (int)(value.realValue * 255.0f);
			break;
		case Fx_ColorFloorB:
			screenFxProperties->ColorFloorB = (int)(value.realValue * 255.0f);
			break;
		case Fx_Hue:
			screenFxProperties->Hue = (int)(value.realValue * 255.0f);
			break;
		case Fx_LightIntensity:
			screenFxProperties->LightIntensity = (int)(value.realValue * 255.0f);
			break;
		case Fx_Saturation:
			screenFxProperties->Saturation = (int)(value.realValue * 255.0f);
			break;
		case Fx_Desaturation:
			screenFxProperties->Desaturation = (int)(value.realValue * 255.0f);
			break;
		case Fx_Range:
			screenFxProperties->MaximumDistance = (unsigned char)value.intValue;
			break;
		case Fx_Tracing:
			screenFxProperties->Tracing = (int)(value.realValue * 255.0f);
			break;
		case Fx_GammaIncrease:
			screenFxProperties->GammaIncrease = (int)(value.realValue * 255.0f);
			break;
		case Fx_GammaDecrease:
			screenFxProperties->GammaDecrease = (int)(value.realValue * 255.0f);
			break;
		default:
			throw std::runtime_error("not implemented");
		}

		SetMapVariantObjectProperties(m_playerIndex, m_objectIndex, properties);
	}

	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetKillVolumePropertyValue(::Forge::EObjectProperty property) // 0x1083D520
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetKillVolumePropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
		// Forge::EObjectProperty property;
		// Forge::ForgeKillVolumeProperties *killVolumeProperties;
		// s_multiplayer_object_properties *properties;
		// function call : s_multiplayer_object_properties *(*const)(unsigned long)

		s_multiplayer_object_properties *properties = object_get_multiplayer(m_objectIndex);

		if (!properties)
		{
			throw std::runtime_error("not a multiplayer object");
		}

		Forge::ForgeKillVolumeProperties *killVolumeProperties = (Forge::ForgeKillVolumeProperties *)&properties->teleporter_channel;

		switch (property)
		{
		case KillVolume_AlwaysVisible:
			return Forge::SPropertyValue::Integer((killVolumeProperties->Flags & Forge::ForgeKillVolumeProperties::eKillVolumeFlags_AlwaysVisible) != 0);
		case KillVolume_DestroyVehicles:
			return Forge::SPropertyValue::Integer((killVolumeProperties->Flags & Forge::ForgeKillVolumeProperties::eKillVolumeFlags_DestroyVehicles) != 0);
		case KillVolume_DamageCause:
			return Forge::SPropertyValue::Integer(killVolumeProperties->DamageCause);
		default:
			throw std::runtime_error("not implemented");
		}
	}

	_inline void CDefaultPropertyAccessor::SetKillVolumePropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x1083FE10
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetKillVolumePropertyValue@CDefaultPropertyAccessor@Forge@@AAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
		// static ...; // 0x1083FF8C
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// Forge::SPropertyValue value;
		// Forge::ForgeKillVolumeProperties *killVolumeProperties;
		// s_map_variant_placement_properties properties;

		s_map_variant_placement_properties properties;

		GetMapVariantObjectProperties(m_objectIndex, &properties);

		Forge::ForgeKillVolumeProperties *killVolumeProperties = (Forge::ForgeKillVolumeProperties *)&properties.shared_storage;

		switch (property)
		{
		case KillVolume_AlwaysVisible:
			killVolumeProperties->Flags &= ~Forge::ForgeKillVolumeProperties::eKillVolumeFlags_AlwaysVisible;
			if (value.intValue)
			{
				killVolumeProperties->Flags |= Forge::ForgeKillVolumeProperties::eKillVolumeFlags_AlwaysVisible;
			}

			break;
		case KillVolume_DestroyVehicles:
			killVolumeProperties->Flags &= ~Forge::ForgeKillVolumeProperties::eKillVolumeFlags_DestroyVehicles;
			if (value.intValue)
			{
				killVolumeProperties->Flags |= Forge::ForgeKillVolumeProperties::eKillVolumeFlags_DestroyVehicles;
			}

			break;
		case KillVolume_DamageCause:
			killVolumeProperties->DamageCause = (unsigned char)value.realValue;
			break;
		default:
			throw std::runtime_error("not implemented");
		}

		SetMapVariantObjectProperties(m_playerIndex, m_objectIndex, properties);
	}

	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetGarbageVolumePropertyValue(::Forge::EObjectProperty property) // 0x1083CD70
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetGarbageVolumePropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
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

		s_multiplayer_object_properties *properties = object_get_multiplayer(m_objectIndex);

		if (!properties)
		{
			throw std::runtime_error("not a multiplayer object");
		}

		Forge::ForgeGarbageVolumeProperties *garbageVolumeProperties = (Forge::ForgeGarbageVolumeProperties *)&properties->teleporter_channel;

		switch (property)
		{
		case GarbageVolume_CollectDeadBiped:
			return Forge::SPropertyValue::Integer((garbageVolumeProperties->Flags & Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectDeadBipeds) != 0);
		case GarbageVolume_CollectWeapons:
			return Forge::SPropertyValue::Integer((garbageVolumeProperties->Flags & Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectWeapons) != 0);
		case GarbageVolume_CollectObjectives:
			return Forge::SPropertyValue::Integer((garbageVolumeProperties->Flags & Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectObjectives) != 0);
		case GarbageVolume_CollectGrenades:
			return Forge::SPropertyValue::Integer((garbageVolumeProperties->Flags & Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectGrenades) != 0);
		case GarbageVolume_CollectEquipment:
			return Forge::SPropertyValue::Integer((garbageVolumeProperties->Flags & Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectEquipment) != 0);
		case GarbageVolume_CollectVehicles:
			return Forge::SPropertyValue::Integer((garbageVolumeProperties->Flags & Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectVehicles) != 0);
		case GarbageVolume_Interval:
			return Forge::SPropertyValue::Integer(garbageVolumeProperties->Interval);
		default:
			throw std::runtime_error("not implemented");
		}
	}

	_inline void CDefaultPropertyAccessor::SetGarbageVolumePropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x1083F600
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetGarbageVolumePropertyValue@CDefaultPropertyAccessor@Forge@@AAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
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

		s_map_variant_placement_properties properties;

		GetMapVariantObjectProperties(m_objectIndex, &properties);

		Forge::ForgeGarbageVolumeProperties *garbageVolumeProperties = (Forge::ForgeGarbageVolumeProperties *)&properties.shared_storage;

		switch (property)
		{
		case GarbageVolume_CollectDeadBiped:
			garbageVolumeProperties->Flags &= ~Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectDeadBipeds;
			if (value.intValue)
			{
				garbageVolumeProperties->Flags |= Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectDeadBipeds;
			}

			break;
		case GarbageVolume_CollectWeapons:
			garbageVolumeProperties->Flags &= ~Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectWeapons;
			if (value.intValue)
			{
				garbageVolumeProperties->Flags |= Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectWeapons;
			}

			break;
		case GarbageVolume_CollectObjectives:
			garbageVolumeProperties->Flags &= ~Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectObjectives;
			if (value.intValue)
			{
				garbageVolumeProperties->Flags |= Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectObjectives;
			}

			break;
		case GarbageVolume_CollectGrenades:
			garbageVolumeProperties->Flags &= ~Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectGrenades;
			if (value.intValue)
			{
				garbageVolumeProperties->Flags |= Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectGrenades;
			}

			break;
		case GarbageVolume_CollectEquipment:
			garbageVolumeProperties->Flags &= ~Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectEquipment;
			if (value.intValue)
			{
				garbageVolumeProperties->Flags |= Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectEquipment;
			}

			break;
		case GarbageVolume_CollectVehicles:
			garbageVolumeProperties->Flags &= ~Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectVehicles;
			if (value.intValue)
			{
				garbageVolumeProperties->Flags |= Forge::ForgeGarbageVolumeProperties::eGarbageVolumeFlags_CollectVehicles;
			}

			break;
		case GarbageVolume_Interval:
			garbageVolumeProperties->Interval = (unsigned char)value.realValue;
			break;
		default:
			throw std::runtime_error("not implemented");
		}

		SetMapVariantObjectProperties(m_playerIndex, m_objectIndex, properties);
	}

	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetMapModifierPropertyValue(::Forge::EObjectProperty property) // 0x1083D700
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetMapModifierPropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
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

		s_multiplayer_object_properties *properties = object_get_multiplayer(m_objectIndex);

		if (!properties)
		{
			throw std::runtime_error("not a multiplayer object");
		}

		Forge::ForgeMapModifierProperties *mapModifierProperties = (Forge::ForgeMapModifierProperties *)&properties->boundry_width;

		switch (property)
		{
		case Map_DisablePushBarrier:
			return Forge::SPropertyValue::Integer((mapModifierProperties->Flags & Forge::ForgeMapModifierProperties::eMapModifierFlags_DisablePushBarrier) != 0);
		case Map_DisableDeathBarrier:
			return Forge::SPropertyValue::Integer((mapModifierProperties->Flags & Forge::ForgeMapModifierProperties::eMapModifierFlags_DisableDeathBarrier) != 0);
		case Map_PhysicsGravity:
			return Forge::SPropertyValue::Real((float)mapModifierProperties->PhysicsGravity / 255.0f);
		case CameraFx_Exposure:
			return Forge::SPropertyValue::Real((float)mapModifierProperties->CameraFxExposure / 255.0f);
		case CameraFx_LightIntensity:
			return Forge::SPropertyValue::Real((float)mapModifierProperties->CameraFxLightIntensity / 255.0f);
		case CameraFx_Bloom:
			return Forge::SPropertyValue::Real((float)mapModifierProperties->CameraFxBloom / 255.0f);
		case CameraFx_LightBloom:
			return Forge::SPropertyValue::Real((float)mapModifierProperties->CameraFxLightBloom / 255.0f * 2.0f);
		case AtmosphereProperties_Enabled:
			return Forge::SPropertyValue::Integer(mapModifierProperties->AtmosphereProperties.Flags & 1);
		case AtmosphereProperties_Weather:
			return Forge::SPropertyValue::Integer(mapModifierProperties->AtmosphereProperties.Weather);
		case AtmosphereProperties_Brightness:
			return Forge::SPropertyValue::Real((float)mapModifierProperties->AtmosphereProperties.Brightness / 255.0f);
		case AtmosphereProperties_FogDensity:
			return Forge::SPropertyValue::Real((float)mapModifierProperties->AtmosphereProperties.FogDensity / 255.0f);
		case AtmosphereProperties_FogVisibility:
			return Forge::SPropertyValue::Real((float)mapModifierProperties->AtmosphereProperties.FogVisibility / 255.0f);
		case AtmosphereProperties_FogColorR:
			return Forge::SPropertyValue::Real((float)mapModifierProperties->AtmosphereProperties.FogColorR / 255.0f);
		case AtmosphereProperties_FogColorG:
			return Forge::SPropertyValue::Real((float)mapModifierProperties->AtmosphereProperties.FogColorG / 255.0f);
		case AtmosphereProperties_FogColorB:
			return Forge::SPropertyValue::Real((float)mapModifierProperties->AtmosphereProperties.FogColorB / 255.0f);
		case AtmosphereProperties_Skybox:
			return Forge::SPropertyValue::Integer(mapModifierProperties->AtmosphereProperties.Skybox);
		case AtmosphereProperties_SkyboxOffsetZ:
			return Forge::SPropertyValue::Real((float)mapModifierProperties->AtmosphereProperties.SkyboxZOffset / 255.0f * 2.0f - 1.0f);
		case AtmosphereProperties_SkyboxOverrideTransform:
			return Forge::SPropertyValue::Integer((mapModifierProperties->AtmosphereProperties.Flags & 2) != 0);
		default:
			throw std::runtime_error("not implemented");
		}
	}

	_inline void CDefaultPropertyAccessor::SetMapModifierPropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x10840020
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetMapModifierPropertyValue@CDefaultPropertyAccessor@Forge@@AAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
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
			// unsigned short &flags;

		s_map_variant_placement_properties properties;

		GetMapVariantObjectProperties(m_objectIndex, &properties);

		Forge::ForgeMapModifierProperties *mapModifierProperties = (Forge::ForgeMapModifierProperties *)&properties.boundry_width;

		switch (property)
		{
		case Map_DisableDeathBarrier:
			mapModifierProperties->Flags &= ~Forge::ForgeMapModifierProperties::eMapModifierFlags_DisableDeathBarrier;
			if (value.intValue)
			{
				mapModifierProperties->Flags |= Forge::ForgeMapModifierProperties::eMapModifierFlags_DisableDeathBarrier;
			}

			break;
		case Map_DisablePushBarrier:
			mapModifierProperties->Flags &= ~Forge::ForgeMapModifierProperties::eMapModifierFlags_DisablePushBarrier;
			if (value.intValue)
			{
				mapModifierProperties->Flags |= Forge::ForgeMapModifierProperties::eMapModifierFlags_DisablePushBarrier;
			}

			break;
		case Map_PhysicsGravity:
			mapModifierProperties->PhysicsGravity = (int)(value.realValue * 255.0f);
			break;
		case CameraFx_Exposure:
			mapModifierProperties->CameraFxExposure = (int)(value.realValue * 255.0f);
			break;
		case CameraFx_LightIntensity:
			mapModifierProperties->CameraFxLightIntensity = (int)(value.realValue * 255.0f);
			break;
		case CameraFx_Bloom:
			mapModifierProperties->CameraFxBloom = (int)(value.realValue * 255.0f);
			break;
		case CameraFx_LightBloom:
			mapModifierProperties->CameraFxLightBloom = (int)(value.realValue / 2.0f * 255.0f);
			break;
		case AtmosphereProperties_Enabled:
			mapModifierProperties->AtmosphereProperties.Flags &= ~1;
			if (value.intValue)
			{
				mapModifierProperties->AtmosphereProperties.Flags |= 1;
			}

			break;
		case AtmosphereProperties_Weather:
			mapModifierProperties->AtmosphereProperties.Weather = (unsigned char)value.intValue;
			break;
		case AtmosphereProperties_Brightness:
			mapModifierProperties->AtmosphereProperties.Brightness = (int)(value.realValue * 255.0f);
			break;
		case AtmosphereProperties_FogDensity:
			mapModifierProperties->AtmosphereProperties.FogDensity = (int)(value.realValue * 255.0f);
			break;
		case AtmosphereProperties_FogVisibility:
			mapModifierProperties->AtmosphereProperties.FogVisibility = (int)(value.realValue * 255.0f);
			break;
		case AtmosphereProperties_FogColorR:
			mapModifierProperties->AtmosphereProperties.FogColorR = (int)(value.realValue * 255.0f);
			break;
		case AtmosphereProperties_FogColorG:
			mapModifierProperties->AtmosphereProperties.FogColorG = (int)(value.realValue * 255.0f);
			break;
		case AtmosphereProperties_FogColorB:
			mapModifierProperties->AtmosphereProperties.FogColorB = (int)(value.realValue * 255.0f);
			break;
		case AtmosphereProperties_Skybox:
			mapModifierProperties->AtmosphereProperties.Skybox = (unsigned char)value.intValue;
			break;
		case AtmosphereProperties_SkyboxOffsetZ:
			mapModifierProperties->AtmosphereProperties.SkyboxZOffset = (int)((value.realValue / 2.0f + 0.5f) * 255.0f);
			break;
		case AtmosphereProperties_SkyboxOverrideTransform:
			mapModifierProperties->AtmosphereProperties.Flags &= ~2;
			if (value.intValue)
			{
				mapModifierProperties->AtmosphereProperties.Flags |= 2;
			}

			break;
		default:
			throw std::runtime_error("not implemented");
		}

		SetMapVariantObjectProperties(m_playerIndex, m_objectIndex, properties);
	}

	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetBudgetPropertyValue(::Forge::EObjectProperty property) // 0x1083BEB0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetBudgetPropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
		// static ...; // 0x1083BF90
		// static ...; // 0x1083BF88
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// s_variant_quota entry;

		s_variant_quota entry;

		GetMapVariantBudgetForObject(m_objectIndex, &entry);
		switch (property)
		{
		case Budget_Minimum:
			return Forge::SPropertyValue::Integer(entry.minimum_count);
		case Budget_Maximum:
			return Forge::SPropertyValue::Integer(entry.maximum_count);
		default:
			throw std::runtime_error("not implemented");
		}
	}

	_inline void CDefaultPropertyAccessor::SetBudgetPropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x1083E930
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetBudgetPropertyValue@CDefaultPropertyAccessor@Forge@@AAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
		// static ...; // 0x1083EA08
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// Forge::SPropertyValue value;
		// s_variant_quota entry;

		s_variant_quota entry;

		GetMapVariantBudgetForObject(m_objectIndex, &entry);
		switch (property)
		{
		case Budget_Minimum:
			entry.minimum_count = (unsigned char)value.realValue;
			break;
		case Budget_Maximum:
			entry.maximum_count = (unsigned char)value.realValue;
			break;
		default:
			throw std::runtime_error("not implemented");
		}

		SetMapVariantBudgetForObject(m_playerIndex, m_objectIndex, entry);
	}

	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetForgeDevicePropertyValue(::Forge::EObjectProperty property) // 0x1083C260
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetForgeDevicePropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
	// $LN8:
	// $LN7:
	// $LN6:
	// $LN5:
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// s_multiplayer_object_properties *properties;
		// CForgeDeviceObjectProperties *deviceProperties;
		// function call : s_multiplayer_object_properties *(*const)(unsigned long)

		s_multiplayer_object_properties *properties = object_get_multiplayer(m_objectIndex);

		if (!properties)
		{
			throw std::runtime_error("not a multiplayer object");
		}

		CForgeDeviceObjectProperties *deviceProperties = (CForgeDeviceObjectProperties *)&properties->boundry_width;

		switch (property)
		{
		case Device_TurnRate:
			return Forge::SPropertyValue::Real(deviceProperties->GetGearTurnRate());
		case Device_DoorOpenTime:
			return Forge::SPropertyValue::Real(deviceProperties->GetDoorOpenTime());
		case Device_TriggerRadius:
			return Forge::SPropertyValue::Real(deviceProperties->GetTriggerRadius());
		case Device_DelayTime:
			return Forge::SPropertyValue::Real(deviceProperties->GetDelayTime());
		default:
			throw std::runtime_error("not implemented");
		}
	}

	_inline void CDefaultPropertyAccessor::SetForgeDevicePropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x1083ECE0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetForgeDevicePropertyValue@CDefaultPropertyAccessor@Forge@@AAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
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

		s_map_variant_placement_properties properties;

		GetMapVariantObjectProperties(m_objectIndex, &properties);

		CForgeDeviceObjectProperties *deviceProperties = (CForgeDeviceObjectProperties *)&properties.boundry_width;

		switch (property)
		{
		case Device_TurnRate:
			deviceProperties->SetGearTurnRate(value.realValue);
			break;
		case Device_DoorOpenTime:
			deviceProperties->SetDoorOpenTime(value.realValue);
			break;
		case Device_TriggerRadius:
			deviceProperties->SetTriggerRadius(value.realValue);
			break;
		case Device_DelayTime:
			deviceProperties->SetDelayTime(value.realValue);
			break;
		default:
			throw std::runtime_error("not implemented");
		}

		SetMapVariantObjectProperties(m_playerIndex, m_objectIndex, properties);
	}

	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetForgeSceneryPropertyValue(::Forge::EObjectProperty property) // 0x1083CC40
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetForgeSceneryPropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
		// Forge::EObjectProperty property;
		// s_multiplayer_object_properties *properties;
			// s_object_data *object;
		// function call : s_multiplayer_object_properties *(*const)(unsigned long)

		s_multiplayer_object_properties *multiplayerProperties = object_get_multiplayer(m_objectIndex);

		if (!multiplayerProperties)
		{
			throw std::runtime_error("not a multiplayer object");
		}

		switch (property)
		{
		case Scale:
		{
			s_object_data *object = object_get(m_objectIndex);

			return Forge::SPropertyValue::Real(object->scale);
		}
		default:
			throw std::runtime_error("not implemented");
		}
	}

	void CDefaultPropertyAccessor::SetForgeSceneryPropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x1083F4E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetForgeSceneryPropertyValue@CDefaultPropertyAccessor@Forge@@AAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
		// static ...; // 0x1083F5A0
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// Forge::SPropertyValue value;
		// s_map_variant_placement_properties properties;

		s_map_variant_placement_properties properties;

		GetMapVariantObjectProperties(m_objectIndex, &properties);
		switch (property)
		{
		case Scale:
			properties.boundry_width = value.realValue;
			break;
		default:
			throw std::runtime_error("not implemented");
		}

		SetMapVariantObjectProperties(m_playerIndex, m_objectIndex, properties);
	}

	_inline ::Forge::SPropertyValue CDefaultPropertyAccessor::GetForgeChangeColorsPropertyValue(::Forge::EObjectProperty property) // 0x1083C080
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetForgeChangeColorsPropertyValue@CDefaultPropertyAccessor@Forge@@AAE?AUSPropertyValue@2@W4EObjectProperty@2@@Z");
		// static ...; // 0x1083C1EC
		// static ...; // 0x1083C1E4
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// SPixel24 color;
		// s_multiplayer_object_properties *properties;
		// function call : s_multiplayer_object_properties *(*const)(unsigned long)

		s_multiplayer_object_properties *properties = object_get_multiplayer(m_objectIndex);

		if (!properties)
		{
			throw std::runtime_error("not a multiplayer object");
		}

		SPixel24 color = *(SPixel24 *)&properties->boundry_width;

		switch (property)
		{
		case PrimaryChangeColorR:
			return Forge::SPropertyValue::Real((float)color.R / 255.0f);
		case PrimaryChangeColorG:
			return Forge::SPropertyValue::Real((float)color.G / 255.0f);
		case PrimaryChangeColorB:
			return Forge::SPropertyValue::Real((float)color.B / 255.0f);
		default:
			throw std::runtime_error("not implemented");
		}
	}

	_inline void CDefaultPropertyAccessor::SetForgeChangeColorsPropertyValue(::Forge::EObjectProperty property, ::Forge::SPropertyValue value) // 0x1083EB60
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetForgeChangeColorsPropertyValue@CDefaultPropertyAccessor@Forge@@AAEXW4EObjectProperty@2@USPropertyValue@2@@Z");
		// static ...; // 0x1083EC74
		// Forge::CDefaultPropertyAccessor *const this;
		// Forge::EObjectProperty property;
		// Forge::SPropertyValue value;
		// SPixel24 &color;
		// s_map_variant_placement_properties properties;

		s_map_variant_placement_properties properties;

		GetMapVariantObjectProperties(m_objectIndex, &properties);

		SPixel24 *color = (SPixel24 *)&properties.boundry_width;

		switch (property)
		{
		case PrimaryChangeColorR:
			color->R = (int)(value.realValue * 255.0f);
			break;
		case PrimaryChangeColorG:
			color->G = (int)(value.realValue * 255.0f);
			break;
		case PrimaryChangeColorB:
			color->B = (int)(value.realValue * 255.0f);
			break;
		default:
			throw std::runtime_error("not implemented");
		}

		SetMapVariantObjectProperties(m_playerIndex, m_objectIndex, properties);
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

_inline bool GetMapVariantObjectProperties(long objectIndex, s_map_variant_placement_properties *outProperties) // 0x1083DD90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetMapVariantObjectProperties@@YA_NJPAUs_map_variant_placement_properties@@@Z");
	// `anonymous-namespace'::GetMapVariantObjectProperties
	// s_map_variant_placement_properties *outProperties;
	// s_object_data *object;
	// s_map_variant_placement_properties *properties;

	s_variant_datum *objects;
	s_object_data *object;

	object = object_get(objectIndex);
	if (!object)
	{
		return false;
	}

	if (object->map_variant_index == -1)
	{
		return false;
	}

	objects = Forge::GetMapVariant()->objects;
	memcpy(outProperties, &objects[object->map_variant_index].properties, sizeof(s_map_variant_placement_properties));
	return true;
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

_inline bool GetMapVariantBudgetForObject(long objectIndex, s_variant_quota *outEntry) // 0x1083DCA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetMapVariantBudgetForObject@@YA_NJPAUs_variant_quota@@@Z");
	// `anonymous-namespace'::GetMapVariantBudgetForObject
	// s_variant_quota *outEntry;
	// s_variant_datum &placement;
	// s_object_data *object;
	// s_map_variant *mapVariant;

	s_map_variant *mapVariant;
	s_object_data *object;

	object = object_get(objectIndex);
	if (!object)
	{
		return false;
	}

	if (object->map_variant_index == -1)
	{
		return false;
	}

	mapVariant = Forge::GetMapVariant();
	if (mapVariant->objects[object->map_variant_index].quota_index >= 0x100)
	{
		return false;
	}

	*outEntry = mapVariant->object_quotas[mapVariant->objects[object->map_variant_index].quota_index];
	return true;
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
