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
		bool Enabled; // 0x0
		unsigned char __pad0[3]; // 0x1
		real_rgb_color FogColor; // 0x4
		float FogDensity; // 0x10
		float FogVisibility; // 0x14
		float Brightness; // 0x18
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
	_extern void _sub_1067F930();
	void CForgeAtmosphere::InitializeForNewMap() // 0x1067F930
	{
		mangled_x86(MANGLED_TODO, "?InitializeForNewMap@CForgeAtmosphere@Forge@@SAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_1067F930();
	}

	_extern void _sub_1067FEA0(long, Forge::ForgeMapModifierProperties &);
	void CForgeAtmosphere::Update(long mapModifierIndex, Forge::ForgeMapModifierProperties &mapModifierProperties) // 0x1067FEA0
	{
		mangled_x86(MANGLED_TODO, "?Update@CForgeAtmosphere@Forge@@SAXJAAUForgeMapModifierProperties@2@@Z");
		// Forge::ForgeMapModifierProperties &mapModifierProperties;
		todo("implement");
		_sub_1067FEA0(mapModifierIndex, mapModifierProperties);
	}

	void CForgeAtmosphere::HandleMapModifierDeleted() // 0x1067F910
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?HandleMapModifierDeleted@CForgeAtmosphere@Forge@@SAXXZ");
		// procedure flags: nofpo

		state.Enabled = false;
	}

	_extern bool _sub_1067F9D0(s_cluster_reference, s_weighted_atmosphere_parameters *);
	bool CForgeAtmosphere::OverrideSkyAtmosphereSettings(s_cluster_reference cluster_reference, s_weighted_atmosphere_parameters *parameters) // 0x1067F9D0
	{
		mangled_x86(MANGLED_TODO, "?OverrideSkyAtmosphereSettings@CForgeAtmosphere@Forge@@SA_NUs_cluster_reference@@PAUs_weighted_atmosphere_parameters@@@Z");
		// static ...; // 0x1067FD88
		// static ...; // 0x1067FD80
		// s_cluster_reference cluster_reference;
		// s_weighted_atmosphere_parameters *parameters;
		// c_sky_atm_parameters *skya;
		// c_atmosphere_setting const &template_setting;
		// c_atmosphere_setting temp_setting;
		// function call : void *(*const)(unsigned long, long)
		// function call : void (*const)(s_cluster_reference, c_atmosphere_setting *, s_weighted_atmosphere_parameters *, float)
		todo("implement");
		bool __result = _sub_1067F9D0(cluster_reference, parameters);
		return __result;
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
