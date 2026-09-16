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
		_extern bool _sub_107BA250(__int32, void *);
		bool CheckKillTriggersHook(__int32 a0, void *a1) // 0x107BA250
		{
			mangled_x86(MANGLED_TODO, "?CheckKillTriggersHook@MapBarriers@Patches@@YA_NHPAX@Z");
			// void *a1;
			// bool (*CheckKillTriggers)(__int32, void *);
			// function call : bool (*)(__int32, void *)
			todo("implement");
			bool __result = _sub_107BA250(a0, a1);
			return __result;
		}

		_extern bool _sub_107BA2F0(void *);
		bool ObjectSafeZoneHook(void *a0) // 0x107BA2F0
		{
			mangled_x86(MANGLED_TODO, "?ObjectSafeZoneHook@MapBarriers@Patches@@YA_NPAX@Z");
			// void *a0;
			// bool (*CheckSafeZones)(void *);
			// function call : bool (*)(void *)
			todo("implement");
			bool __result = _sub_107BA2F0(a0);
			return __result;
		}

		_extern void *_sub_107BA390(__int32);
		void *PushBarriersGetStructureDesignHook(__int32 index) // 0x107BA390
		{
			mangled_x86(MANGLED_TODO, "?PushBarriersGetStructureDesignHook@MapBarriers@Patches@@YAPAXH@Z");
			// __int32 index;
			// void *(*GetStructureDesign)(__int32);
			// function call : void *(*)(__int32)
			todo("implement");
			void * __result = _sub_107BA390(index);
			return __result;
		}

		_extern void _sub_107B98E0();
		void ApplyAll() // 0x107B98E0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@MapBarriers@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_107B98E0();
		}
	}
}

/* ---------- private code */
