/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Geoemetry.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "Utils/Singleton.hpp"


#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Forge {}
using namespace ::Forge;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace MapBarriers {}
	using namespace Patches::MapBarriers;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

#include "Modules/ModuleDebug.hpp"  // hades: added for 0x107BA250
namespace Forge { class CForgeMapBarriers { public: static bool KillBarrierDisabled(); static bool PushBarrierDisabled(); }; }  // hades: added for 0x107BA250

namespace Patches
{
	namespace MapBarriers
	{
		extern bool CheckKillTriggersHook(__int32 a0, void *a1);
		extern bool ObjectSafeZoneHook(void *a0);
		extern void *PushBarriersGetStructureDesignHook(__int32 index);
		extern void ApplyAll();
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace MapBarriers
	{
		bool CheckKillTriggersHook(__int32 a0, void *a1) // 0x107BA250
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?CheckKillTriggersHook@MapBarriers@Patches@@YA_NHPAX@Z");

			if (Utils::Singleton<Modules::ModuleDebug>::Instance().VarMapBarriersDisabledClient->ValueInt)
			{
				return false;
			}

			if (Forge::CForgeMapBarriers::KillBarrierDisabled())
			{
				return false;
			}

			bool (*CheckKillTriggers)(__int32, void *) = reinterpret_cast<bool (*)(__int32, void *)>(0x68C410);
			return CheckKillTriggers(a0, a1);
		}

		bool ObjectSafeZoneHook(void *a0) // 0x107BA2F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ObjectSafeZoneHook@MapBarriers@Patches@@YA_NPAX@Z");

			if (Utils::Singleton<Modules::ModuleDebug>::Instance().VarMapBarriersDisabledClient->ValueInt)
			{
				return true;
			}

			if (Forge::CForgeMapBarriers::KillBarrierDisabled())
			{
				return true;
			}

			bool (*CheckSafeZones)(void *) = reinterpret_cast<bool (*)(void *)>(0x4EB130);
			return CheckSafeZones(a0);
		}

		void *PushBarriersGetStructureDesignHook(__int32 index) // 0x107BA390
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PushBarriersGetStructureDesignHook@MapBarriers@Patches@@YAPAXH@Z");

			if (Utils::Singleton<Modules::ModuleDebug>::Instance().VarMapBarriersDisabledClient->ValueInt)
			{
				return nullptr;
			}

			if (Forge::CForgeMapBarriers::PushBarrierDisabled())
			{
				return nullptr;
			}

			void * (*GetStructureDesign)(__int32) = reinterpret_cast<void * (*)(__int32)>(0x4E97D0);
			return GetStructureDesign(index);
		}

		void ApplyAll() // 0x107B98E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@MapBarriers@Patches@@YAXXZ");

			Hook(0x771C7D, CheckKillTriggersHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7B4C32, CheckKillTriggersHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x19EBA1, ObjectSafeZoneHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x19FDBE, ObjectSafeZoneHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x19FEEC, ObjectSafeZoneHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x32663D, ObjectSafeZoneHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x2749D1, PushBarriersGetStructureDesignHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x274DBA, PushBarriersGetStructureDesignHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x2750F8, PushBarriersGetStructureDesignHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x275655, PushBarriersGetStructureDesignHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
		}
	}
}

/* ---------- private code */
