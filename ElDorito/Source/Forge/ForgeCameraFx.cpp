/* ---------- headers */

#include "Forge/ForgeCameraFx.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/render/camera_fx_settings.hpp"
#include "Blam/render/views/render_player_view.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
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

struct c_player_view;
namespace Forge
{
	class CForgeCameraFx;
	struct ForgeMapModifierProperties;
}
namespace
{
	struct ForgeCameraFxState;
}

namespace Forge {}
using namespace ::Forge;

/* ---------- constants */

/* ---------- definitions */

namespace
{
	struct ForgeCameraFxState
	{
		bool Enabled; // 0x0
		unsigned char __pad0[3]; // 0x1
		float Exposure; // 0x4
		float LightIntensity; // 0x8
		float BloomIntensity; // 0xC
		float LightBloomIntensity; // 0x10
		ForgeCameraFxState(); /* compiler_generated() */
	};
	static_assert(sizeof(ForgeCameraFxState) == 20, "Invalid ForgeCameraFxState size");
}
typedef unsigned short IRQ_DEVICE_POLICY;
typedef unsigned long ERESOURCE_THREAD;
typedef unsigned char SECURITY_CONTEXT_TRACKING_MODE;
typedef void *NDIS_HANDLE;
typedef unsigned __int32 NET_IF_COMPARTMENT_ID;
typedef unsigned long long POOL_FLAGS;
typedef unsigned long FWPS_IPSEC_FLAGS;
typedef unsigned __int32 NET_IF_COMPARTMENT_SCOPE;
typedef char KPROCESSOR_MODE;
typedef wchar_t *PWCHAR;
typedef __int32 NDIS_STATUS;
typedef unsigned long POOL_NODE_REQUIREMENT;

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Forge
{
	_extern void _sub_1067BBC0();
	void CForgeCameraFx::InitializeForNewMap() // 0x1067BBC0
	{
		mangled_x86(MANGLED_TODO, "?InitializeForNewMap@CForgeCameraFx@Forge@@SAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_1067BBC0();
	}

	_extern void _sub_1067BE20(long, Forge::ForgeMapModifierProperties &);
	void CForgeCameraFx::Update(long mapModifierIndex, Forge::ForgeMapModifierProperties &mapModifierProperties) // 0x1067BE20
	{
		mangled_x86(MANGLED_TODO, "?Update@CForgeCameraFx@Forge@@SAXJAAUForgeMapModifierProperties@2@@Z");
		// Forge::ForgeMapModifierProperties &mapModifierProperties;
		// float expScale;
		todo("implement");
		_sub_1067BE20(mapModifierIndex, mapModifierProperties);
	}

	_extern void _sub_1067BBA0();
	void CForgeCameraFx::HandleMapModifierDeleted() // 0x1067BBA0
	{
		mangled_x86(MANGLED_TODO, "?HandleMapModifierDeleted@CForgeCameraFx@Forge@@SAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_1067BBA0();
	}

	_extern void _sub_1067BC80(c_player_view *, float);
	void CForgeCameraFx::OverrideCameraFxSettings(c_player_view *player_view, float exposure_boost) // 0x1067BC80
	{
		mangled_x86(MANGLED_TODO, "?OverrideCameraFxSettings@CForgeCameraFx@Forge@@SAXPAUc_player_view@@M@Z");
		// float exposure_boost;
		todo("implement");
		_sub_1067BC80(player_view, exposure_boost);
	}

	_extern bool _sub_1067BC60();
	bool CForgeCameraFx::IsActive() // 0x1067BC60
	{
		mangled_x86(MANGLED_TODO, "?IsActive@CForgeCameraFx@Forge@@SA_NXZ");
		// procedure flags: nofpo
		todo("implement");
		bool __result = _sub_1067BC60();
		return __result;
	}

	_extern float _sub_1067BB80();
	float CForgeCameraFx::GetBloomIntensity() // 0x1067BB80
	{
		mangled_x86(MANGLED_TODO, "?GetBloomIntensity@CForgeCameraFx@Forge@@SAMXZ");
		// procedure flags: nofpo
		todo("implement");
		float __result = _sub_1067BB80();
		return __result;
	}
}

/* ---------- private code */
