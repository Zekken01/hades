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
namespace hades_file_local
{
	struct ForgeCameraFxState;
}
using namespace hades_file_local;

namespace Forge {}
using namespace ::Forge;

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct ForgeCameraFxState
	{
		bool Enabled = false; // 0x0
		float Exposure = 0.0f; // 0x4
		float LightIntensity = 0.0f; // 0x8
		float BloomIntensity = 0.0f; // 0xC
		float LightBloomIntensity = 0.0f; // 0x10
	};
	static_assert(sizeof(ForgeCameraFxState) == 20, "Invalid ForgeCameraFxState size");
}
using namespace hades_file_local;
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

namespace hades_file_local
{
	extern ForgeCameraFxState state; // 0x11371830
}
using namespace hades_file_local;
/* ---------- public code */

namespace Forge
{
	void CForgeCameraFx::InitializeForNewMap() // 0x1067BBC0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?InitializeForNewMap@CForgeCameraFx@Forge@@SAXXZ");

		state = {};
	}

	void CForgeCameraFx::Update(long mapModifierIndex, Forge::ForgeMapModifierProperties &mapModifierProperties) // 0x1067BE20
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Update@CForgeCameraFx@Forge@@SAXJAAUForgeMapModifierProperties@2@@Z");

		state.Enabled = true;
		state.Exposure = pow(mapModifierProperties.CameraFxExposure * 0.05f, 2.2f) * 0.01f;
		float expScale = state.Exposure;
		if (abs(state.Exposure) < 0.0001f)
			expScale = 1.0f;

		state.LightIntensity = mapModifierProperties.CameraFxLightIntensity / expScale * 0.07f;
		if (state.LightIntensity > 20000.0f)
			state.LightIntensity = 20000.0f;
		state.BloomIntensity = mapModifierProperties.CameraFxBloom / expScale * 0.07f;
		state.LightBloomIntensity = pow(mapModifierProperties.CameraFxLightBloom / 255.0f * 2.0f, 2.2f);
		if (state.BloomIntensity > 20000.0f)
			state.BloomIntensity = 20000.0f;
	}

	void CForgeCameraFx::HandleMapModifierDeleted() // 0x1067BBA0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?HandleMapModifierDeleted@CForgeCameraFx@Forge@@SAXXZ");

		state.Enabled = false;
	}

	void CForgeCameraFx::OverrideCameraFxSettings(c_player_view *player_view, float exposure_boost) // 0x1067BC80
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?OverrideCameraFxSettings@CForgeCameraFx@Forge@@SAXPAUc_player_view@@M@Z");

		if (!state.Enabled)
			return;

		if (abs(state.Exposure) >= 0.00001f)
			*(float *)((char *)player_view + 0x29C) = state.Exposure;
		if (abs(state.LightIntensity) >= 0.00001f)
			*(float *)((char *)player_view + 0x1E48) = state.LightIntensity;
		if (abs(state.BloomIntensity) >= 0.00001f)
			*(float *)((char *)player_view + 0x2A0) = state.BloomIntensity;
		if (abs(state.LightBloomIntensity) >= 0.00001f)
			*(float *)(*(char **)((char *)player_view + 0x298) + 0x290) = state.LightBloomIntensity;
	}

	bool CForgeCameraFx::IsActive() // 0x1067BC60
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?IsActive@CForgeCameraFx@Forge@@SA_NXZ");

		return state.Enabled;
	}

	float CForgeCameraFx::GetBloomIntensity() // 0x1067BB80
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetBloomIntensity@CForgeCameraFx@Forge@@SAMXZ");

		return state.BloomIntensity;
	}
}

/* ---------- private code */

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { ForgeCameraFxState state; }
