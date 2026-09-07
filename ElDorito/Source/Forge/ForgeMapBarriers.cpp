/* ---------- headers */

#include "Forge/ForgeMapBarriers.hpp"
#include "hades/hades.h"

#include "Forge/ForgeObjectProperties.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/Reforge.hpp"

/* ---------- forward declarations */

namespace Forge
{
	class CForgeMapBarriers;
	struct ForgeMapModifierProperties;
}
namespace Forge {}
using namespace ::Forge;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void Reset();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern bool killBarrierDisabled; // 0x11371848
	extern bool pushBarrierDisabled; // 0x11371849
}
using namespace hades_file_local;
/* ---------- public code */

namespace Forge
{
	_extern void _sub_1067C130();
	void CForgeMapBarriers::InitializeForNewMap() // 0x1067C130
	{
		mangled_x86(MANGLED_TODO, "?InitializeForNewMap@CForgeMapBarriers@Forge@@SAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_1067C130();
	}

	_extern void _sub_1067C1E0(long, Forge::ForgeMapModifierProperties &);
	void CForgeMapBarriers::Update(long mapModifierIndex, Forge::ForgeMapModifierProperties &mapModifierProperties) // 0x1067C1E0
	{
		mangled_x86(MANGLED_TODO, "?Update@CForgeMapBarriers@Forge@@SAXJAAUForgeMapModifierProperties@2@@Z");
		// Forge::ForgeMapModifierProperties &mapModifierProperties;
		todo("implement");
		_sub_1067C1E0(mapModifierIndex, mapModifierProperties);
	}

	_extern void _sub_1067C0F0();
	void CForgeMapBarriers::HandleMapModifierDeleted() // 0x1067C0F0
	{
		mangled_x86(MANGLED_TODO, "?HandleMapModifierDeleted@CForgeMapBarriers@Forge@@SAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_1067C0F0();
	}

	_extern bool _sub_1067C170();
	bool CForgeMapBarriers::KillBarrierDisabled() // 0x1067C170
	{
		mangled_x86(MANGLED_TODO, "?KillBarrierDisabled@CForgeMapBarriers@Forge@@SA_NXZ");
		// procedure flags: nofpo
		todo("implement");
		bool __result = _sub_1067C170();
		return __result;
	}

	_extern bool _sub_1067C190();
	bool CForgeMapBarriers::PushBarrierDisabled() // 0x1067C190
	{
		mangled_x86(MANGLED_TODO, "?PushBarrierDisabled@CForgeMapBarriers@Forge@@SA_NXZ");
		// procedure flags: nofpo
		todo("implement");
		bool __result = _sub_1067C190();
		return __result;
	}
}

/* ---------- private code */

_extern void _sub_1067C1B0();
void Reset() // 0x1067C1B0
{
	// `anonymous-namespace'::Reset
	// procedure flags: nofpo
	todo("implement");
	_sub_1067C1B0();
}
