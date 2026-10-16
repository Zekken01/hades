/* ---------- headers */

#include "Forge/ForgeAtmosphere.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/sky_atm/atmosphere.hpp"
#include "Blam/sky_atm/sky_atm_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
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

struct c_atmosphere_setting;
struct c_sky_atm_parameters;
struct real_rgb_color;
struct s_cluster_reference;
struct s_weighted_atmosphere_parameters;
namespace Forge
{
	class CForgeAtmosphere;
	struct ForgeMapModifierProperties;
}
namespace hades_file_local
{
	struct ForgeAtmosphereState;
}
using namespace hades_file_local;

namespace Forge {}
using namespace ::Forge;

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	#pragma pack(push, 4)
	struct ForgeAtmosphereState
	{
		bool Enabled = false; // 0x0
		real_rgb_color FogColor = {}; // 0x4
		float FogDensity = 0.0f; // 0x10
		float FogVisibility = 0.0f; // 0x14
		float Brightness = 0.0f; // 0x18
		// hades: the generator declared `ForgeAtmosphereState();` here. Nothing
		// defines it, the inventory has no address for it, and declaring a
		// constructor is what stops this being an aggregate - so `state = {}`
		// emitted a call to ??0ForgeAtmosphereState where the original zeroes
		// the temporary inline, member by member. Removed for 0x1067F930 and
		// 0x1067BBC0. Same family as the hades-declared-only-members memory.
	};
	#pragma pack(pop)
	static_assert(sizeof(ForgeAtmosphereState) == 28, "Invalid ForgeAtmosphereState size");
}
using namespace hades_file_local;
/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern ForgeAtmosphereState state; // 0x11371920
}
using namespace hades_file_local;
/* ---------- public code */

namespace Forge
{
	void CForgeAtmosphere::InitializeForNewMap() // 0x1067F930
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?InitializeForNewMap@CForgeAtmosphere@Forge@@SAXXZ");

		state = {};
	}

	void CForgeAtmosphere::Update(long mapModifierIndex, Forge::ForgeMapModifierProperties &mapModifierProperties) // 0x1067FEA0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Update@CForgeAtmosphere@Forge@@SAXJAAUForgeMapModifierProperties@2@@Z");

		state.Enabled = false;
		if (mapModifierProperties.AtmosphereProperties.Flags & 1)
		{
			state.Enabled = true;
			state.FogColor.red = mapModifierProperties.AtmosphereProperties.FogColorR / 255.0f;
			state.FogColor.green = mapModifierProperties.AtmosphereProperties.FogColorG / 255.0f;
			state.FogColor.blue = mapModifierProperties.AtmosphereProperties.FogColorB / 255.0f;
			state.FogDensity = mapModifierProperties.AtmosphereProperties.FogDensity / 255.0f * 200.0f;
			state.FogVisibility = mapModifierProperties.AtmosphereProperties.FogVisibility / 255.0f * 200.0f;
			state.Brightness = mapModifierProperties.AtmosphereProperties.Brightness / 255.0f * 4.0f;
		}
	}

	void CForgeAtmosphere::HandleMapModifierDeleted() // 0x1067F910
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?HandleMapModifierDeleted@CForgeAtmosphere@Forge@@SAXXZ");

		state.Enabled = false;
	}

	bool CForgeAtmosphere::OverrideSkyAtmosphereSettings(s_cluster_reference cluster_reference, s_weighted_atmosphere_parameters *parameters) // 0x1067F9D0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?OverrideSkyAtmosphereSettings@CForgeAtmosphere@Forge@@SA_NUs_cluster_reference@@PAUs_weighted_atmosphere_parameters@@@Z");

		if (!state.Enabled)
			return false;
		c_sky_atm_parameters *skya = (c_sky_atm_parameters *)tag_get('skya', global_scenario_get()->sky_parameters.index);
		if (!skya)
			return false;
		if (!skya->atmosphere_settings.count)
			return false;
		c_atmosphere_setting const &template_setting = skya->atmosphere_settings[0];
		c_atmosphere_setting temp_setting = {};
		temp_setting.flags = 7;
		temp_setting.pitch = template_setting.pitch;
		temp_setting.heading = template_setting.heading;
		temp_setting.color = state.FogColor;
		temp_setting.intensity = state.Brightness;
		temp_setting.sea_level = -100.0f + state.FogVisibility;
		temp_setting.rayleign_height_scale = 100.0f;
		temp_setting.mie_height_scale = 25.0f;
		temp_setting.rayleigh_multiplier = 0.08f;
		temp_setting.mie_multiplier = 2.5f;
		temp_setting.sun_phase_function = template_setting.sun_phase_function;
		temp_setting.de_saturation = 1.0f;
		temp_setting.distance_bias = -100.0f + state.FogDensity;
		temp_setting.max_fog_thickness = 65535.0f;
		temp_setting.beta_m = { 0.0009897007f, 0.0009897007f, 0.0009897007f };
		temp_setting.beta_p = { 0.1970554f, 0.1970554f, 0.1970554f };
		temp_setting.beta_m_theta_prefix = { 6.008439e-05f, 6.008439e-05f, 6.008439e-05f };
		temp_setting.beta_p_theta_prefix = { 0.04638588f, 0.04638588f, 0.04638588f };
		temp_setting.sheet_density = template_setting.sheet_density;
		temp_setting.full_intensity_height = template_setting.full_intensity_height;
		temp_setting.half_intensity_height = template_setting.half_intensity_height;
		temp_setting.wind_direction = template_setting.wind_direction;
		((void (*const)(s_cluster_reference, c_atmosphere_setting *, s_weighted_atmosphere_parameters *, float))0x671D90)(cluster_reference, &temp_setting, parameters, 1.0f);
		return true;
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<c_atmosphere_setting>::try_get_element(__int32, c_atmosphere_setting **) const;
template c_atmosphere_setting & c_tag_block<c_atmosphere_setting>::operator[](__int32);
template c_atmosphere_setting * c_tag_block<c_atmosphere_setting>::get_element(__int32) const;
template c_flags<enum e_atmosphere_flags,unsigned short> & c_flags<enum e_atmosphere_flags,unsigned short>::operator=(unsigned short const &);
template c_flags<enum e_atmosphere_flags,unsigned short>::c_flags();

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { ForgeAtmosphereState state; }
