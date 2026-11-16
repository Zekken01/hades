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
	void CForgeMapBarriers::InitializeForNewMap() // 0x1067C130
	{
		Reset();
	}

	void CForgeMapBarriers::Update(long mapModifierIndex, Forge::ForgeMapModifierProperties &mapModifierProperties) // 0x1067C1E0
	{
		killBarrierDisabled = (mapModifierProperties.Flags & 2) != 0;
		pushBarrierDisabled = (mapModifierProperties.Flags & 1) != 0;
	}

	void CForgeMapBarriers::HandleMapModifierDeleted() // 0x1067C0F0
	{
		Reset();
	}

	bool CForgeMapBarriers::KillBarrierDisabled() // 0x1067C170
	{
		return killBarrierDisabled;
	}

	bool CForgeMapBarriers::PushBarrierDisabled() // 0x1067C190
	{
		return pushBarrierDisabled;
	}
}

/* ---------- private code */

void Reset() // 0x1067C1B0
{
	killBarrierDisabled = false;
	pushBarrierDisabled = false;
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { bool killBarrierDisabled; }
namespace hades_file_local { bool pushBarrierDisabled; }
