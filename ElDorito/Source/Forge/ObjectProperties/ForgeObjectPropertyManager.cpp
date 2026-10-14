/* ---------- headers */

#include "Forge/ObjectProperties/ForgeObjectPropertyManager.hpp"
#include "hades/hades.h"

#include "Forge/Geoemetry.hpp"
#include "Forge/ObjectProperties/ForgeObjectPropertyDefinitions.hpp"
#include "Interface/CustomBitmapManager.hpp"
#include "Utils/NameValueTable.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <list>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Forge
{
	class CObjectPropertyManager;
	struct SPropertyDefinition;
}

namespace Utils {}
using namespace ::Utils;
namespace Forge {}
using namespace ::Forge;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Forge
{
	CObjectPropertyManager::CObjectPropertyManager() // 0x108453B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0CObjectPropertyManager@Forge@@QAE@XZ");
		// Forge::CObjectPropertyManager *const this;

		Register(Integer, "on_map_at_start", General_OnMapAtStart);
		Register(Integer, "symmetry", General_Symmetry);
		Register(Integer, "respawn_rate", General_RespawnRate);
		Register(Integer, "spare_clips", General_SpareClips);
		Register(Integer, "spawn_order", General_SpawnOrder);
		Register(Integer, "team_affiliation", General_Team);
		Register(Integer, "engine_flags", General_EngineFlags);
		Register(Integer, "physics", General_Physics);
		Register(Integer, "reforge_material", Reforge_Material);
		Register(Real, "reforge_material_color_r", Reforge_Material_ColorR);
		Register(Real, "reforge_material_color_g", Reforge_Material_ColorG);
		Register(Real, "reforge_material_color_b", Reforge_Material_ColorB);
		Register(Real, "reforge_material_tex_scale", Reforge_Material_TextureScale);
		Register(Real, "reforge_material_tex_offset_x", Reforge_Material_TextureOffsetX);
		Register(Real, "reforge_material_tex_offset_y", Reforge_Material_TextureOffsetY);
		Register(Integer, "reforge_material_tex_override", Reforge_Material_TextureOverride);
		Register(Integer, "reforge_material_allows_projectiles", Reforge_Material_AllowsProjectiles);
		Register(Integer, "reforge_material_type", Reforge_Material_Type);
		Register(Integer, "reforge_material_team_barrier", Reforge_TeamBarrier);
		Register(Integer, "reforge_material_climbable", Reforge_Material_Climbable);
		Register(Real, "scale", Scale);
		Register(Integer, "teleporter_channel", General_TeleporterChannel);
		Register(Integer, "shape_type", General_ShapeType);
		Register(Real, "shape_radius", General_ShapeRadius);
		Register(Real, "shape_width", General_ShapeWidth);
		Register(Real, "shape_top", General_ShapeTop);
		Register(Real, "shape_bottom", General_ShapeBottom);
		Register(Real, "shape_depth", General_ShapeDepth);
		Register(Integer, "light_type", Light_Type);
		Register(Real, "light_field_of_view", Light_FieldOfView);
		Register(Real, "light_near_width", Light_NearWidth);
		Register(Real, "light_color_r", Light_ColorR);
		Register(Real, "light_color_g", Light_ColorG);
		Register(Real, "light_color_b", Light_ColorB);
		Register(Real, "light_intensity", Light_Intensity);
		Register(Real, "light_radius", Light_Radius);
		Register(Integer, "light_illumination_function_type", Light_IlluminationType);
		Register(Real, "light_illumination_function_base", Light_IlluminationBase);
		Register(Real, "light_illumination_function_freq", Light_IlluminationFreq);
		Register(Integer, "fx_range", Fx_Range);
		Register(Real, "fx_hue", Fx_Hue);
		Register(Real, "fx_light_intensity", Fx_LightIntensity);
		Register(Real, "fx_saturation", Fx_Saturation);
		Register(Real, "fx_desaturation", Fx_Desaturation);
		Register(Real, "fx_color_filter_r", Fx_ColorFilterR);
		Register(Real, "fx_color_filter_g", Fx_ColorFilterG);
		Register(Real, "fx_color_filter_b", Fx_ColorFilterB);
		Register(Real, "fx_color_floor_r", Fx_ColorFloorR);
		Register(Real, "fx_color_floor_g", Fx_ColorFloorG);
		Register(Real, "fx_color_floor_b", Fx_ColorFloorB);
		Register(Real, "fx_gamma_increase", Fx_GammaIncrease);
		Register(Real, "fx_gamma_decrease", Fx_GammaDecrease);
		Register(Real, "fx_tracing", Fx_Tracing);
		Register(Integer, "garbage_volume_collect_dead_biped", GarbageVolume_CollectDeadBiped);
		Register(Integer, "garbage_volume_collect_weapons", GarbageVolume_CollectWeapons);
		Register(Integer, "garbage_volume_collect_objectives", GarbageVolume_CollectObjectives);
		Register(Integer, "garbage_volume_collect_grenades", GarbageVolume_CollectGrenades);
		Register(Integer, "garbage_volume_collect_equipment", GarbageVolume_CollectEquipment);
		Register(Integer, "garbage_volume_collect_vehicles", GarbageVolume_CollectVehicles);
		Register(Integer, "garbage_volume_interval", GarbageVolume_Interval);
		Register(Integer, "kill_volume_always_visible", KillVolume_AlwaysVisible);
		Register(Integer, "kill_volume_destroy_vehicles", KillVolume_DestroyVehicles);
		Register(Integer, "kill_volume_damage_cause", KillVolume_DamageCause);
		Register(Integer, "map_disable_push_barrier", Map_DisablePushBarrier);
		Register(Integer, "map_disable_death_barrier", Map_DisableDeathBarrier);
		Register(Real, "map_physics_gravity", Map_PhysicsGravity);
		Register(Real, "camera_fx_exposure", CameraFx_Exposure);
		Register(Real, "camera_fx_light_intensity", CameraFx_LightIntensity);
		Register(Real, "camera_fx_bloom", CameraFx_Bloom);
		Register(Real, "camera_fx_light_bloom", CameraFx_LightBloom);
		Register(Integer, "atmosphere_properties_enabled", AtmosphereProperties_Enabled);
		Register(Integer, "atmosphere_properties_weather", AtmosphereProperties_Weather);
		Register(Real, "atmosphere_properties_brightness", AtmosphereProperties_Brightness);
		Register(Real, "atmosphere_properties_fog_density", AtmosphereProperties_FogDensity);
		Register(Real, "atmosphere_properties_fog_visibility", AtmosphereProperties_FogVisibility);
		Register(Real, "atmosphere_properties_fog_color_r", AtmosphereProperties_FogColorR);
		Register(Real, "atmosphere_properties_fog_color_g", AtmosphereProperties_FogColorG);
		Register(Real, "atmosphere_properties_fog_color_b", AtmosphereProperties_FogColorB);
		Register(Integer, "atmosphere_properties_skybox", AtmosphereProperties_Skybox);
		Register(Real, "atmosphere_properties_skybox_offset_z", AtmosphereProperties_SkyboxOffsetZ);
		Register(Integer, "atmosphere_properties_skybox_override_transform", AtmosphereProperties_SkyboxOverrideTransform);
		Register(Real, "device_turn_rate", Device_TurnRate);
		Register(Real, "device_door_open_time", Device_DoorOpenTime);
		Register(Real, "device_trigger_radius", Device_TriggerRadius);
		Register(Real, "device_delay_time", Device_DelayTime);
		Register(Real, "primary_change_color_r", PrimaryChangeColorR);
		Register(Real, "primary_change_color_g", PrimaryChangeColorG);
		Register(Real, "primary_change_color_b", PrimaryChangeColorB);
		Register(Integer, "summary_runtime_minimum", Budget_Minimum);
		Register(Integer, "summary_runtime_maximum", Budget_Maximum);
	}

	void CObjectPropertyManager::Register(Forge::EPropertyValueType valueType, char const *name, Forge::EObjectProperty property) // 0x10846D70
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Register@CObjectPropertyManager@Forge@@AAEXW4EPropertyValueType@2@PBDW4EObjectProperty@2@@Z");
		// Forge::EObjectProperty property;

		m_registeredProperties[property] = { name, property, valueType };
		m_nameLookup[name] = property;
	}
}


namespace Forge
{
	std::array<Forge::SPropertyDefinition,90> const CObjectPropertyManager::GetProperties() const // 0x10846C50
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetProperties@CObjectPropertyManager@Forge@@QBE?BV?$array@USPropertyDefinition@Forge@@$0FK@@std@@XZ");
		// Forge::CObjectPropertyManager const *const this;

		return m_registeredProperties;
	}

	Forge::EObjectProperty CObjectPropertyManager::FindPropertyByName(char const *name) // 0x10846A60
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?FindPropertyByName@CObjectPropertyManager@Forge@@QAE?AW4EObjectProperty@2@PBD@Z");
		// static ...; // 0x10846BD8
		// static ...; // 0x10846BD0
		// Forge::CObjectPropertyManager *const this;
		// char const *name;
			// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<std::string const ,enum Forge::EObjectProperty> > > > it;

		if (auto it = m_nameLookup.find(name); it != m_nameLookup.end())
			return it->second;
		return (Forge::EObjectProperty)-1;
	}

	Forge::SPropertyDefinition const *CObjectPropertyManager::GetProperty(Forge::EObjectProperty property) const // 0x10846C90
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetProperty@CObjectPropertyManager@Forge@@QBEPBUSPropertyDefinition@2@W4EObjectProperty@2@@Z");
		// Forge::EObjectProperty property;

		return &m_registeredProperties[property];
	}
}


namespace Forge
{
	char const *CObjectPropertyManager::GetPropertyName(Forge::EObjectProperty property) // 0x10846D00
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetPropertyName@CObjectPropertyManager@Forge@@QAEPBDW4EObjectProperty@2@@Z");
		// Forge::EObjectProperty property;

		return m_registeredProperties[property].name;
	}
}

/* ---------- private code */
