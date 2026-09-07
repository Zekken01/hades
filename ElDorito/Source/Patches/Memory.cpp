/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/math/sound_math.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/sounds/sound_memory.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Modules/ModuleGame.hpp"
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

/* ---------- forward declarations */

namespace Modules
{
	class ModuleGame;
}
namespace
{
	struct c_debug_game_state_allocation;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Memory {}
	using namespace Patches::Memory;
	namespace Core {}
	using namespace Patches::Core;
}

/* ---------- constants */

/* ---------- definitions */

namespace
{
	struct c_debug_game_state_allocation
	{
		static _iobuf *m_fp;
		static bool m_enabled;
		static void record_allocation(long, char const *, char const *, unsigned long);
		static void begin(unsigned long);
		static void end();
	};
	static_assert(sizeof(c_debug_game_state_allocation) == 1, "Invalid c_debug_game_state_allocation size");
}
/* ---------- prototypes */

namespace Patches
{
	namespace Memory
	{
		extern __int32 ExpandRuntimeStateGlobals();
		extern __int32 ExpandGameStateGlobals();
		extern void ExpandRenderGlobals();
		extern void ExpandMainGlobalMemoryMap();
		extern void OnMapLoadCallback(char const *mapName);
		extern void ApplyAll();
		extern void ApplyAfterInit();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern unsigned __int32 newDataSize; // 0x124645F4
	extern unsigned __int32 newCacheSize; // 0x124645F8
	extern unsigned __int32 physicalMemorySize; // 0x124645FC
}
_iobuf *c_debug_game_state_allocation::m_fp; // 0x12464600
bool c_debug_game_state_allocation::m_enabled; // 0x12464604

/* ---------- public code */

namespace Patches
{
	namespace Memory
	{
		_extern __int32 _sub_10A8AF90();
		__int32 ExpandRuntimeStateGlobals() // 0x10A8AF90
		{
			mangled_x86(MANGLED_TODO, "?ExpandRuntimeStateGlobals@Memory@Patches@@YAHXZ");
			// procedure flags: nofpo
			// unsigned __int32 xboxSoundSize;
			// unsigned __int32 const origRuntimeGlobalsSize;
			// unsigned __int32 newGameStateCompressionScratchSize;
			// unsigned __int32 origGameStateCompressionScratchSize;
			// unsigned __int32 extraSize;
			// unsigned __int32 oldXboxSoundCount;
			// unsigned __int32 newXboxSoundSize;
			// unsigned __int32 newRuntimeGlobalsSize;
			// unsigned __int32 newXboxSoundCount;
			// function call : unsigned long (*const)(long, unsigned long, long)
			// function call : unsigned long (*const)(long, unsigned long, long)
			// function call : unsigned long (*const)(long)
			todo("implement");
			__int32 __result = _sub_10A8AF90();
			return __result;
		}

		_extern __int32 _sub_10A8AB70();
		__int32 ExpandGameStateGlobals() // 0x10A8AB70
		{
			mangled_x86(MANGLED_TODO, "?ExpandGameStateGlobals@Memory@Patches@@YAHXZ");
			// procedure flags: nofpo
			// unsigned __int32 const origGameStateGlobalsPersistSize;
			// unsigned __int32 newCachedObjectRenderStatesCount;
			// unsigned __int32 origUnknownSubAllocation3Size;
			// unsigned __int32 origUnknownSubAllocation2Size;
			// unsigned __int32 const origGameStateGlobalsSize;
			// unsigned __int32 subAllocation4ExtraSize;
			// unsigned __int32 oldCachedObjectRenderStatesCount;
			// unsigned __int32 origUnknownSubAllocation4Size;
			// unsigned __int32 const newGameGlobalsPersistSize;
			// unsigned __int32 cachedObjectRenderStatesSize;
			// unsigned __int32 newUnknownSubAllocation3Size;
			// unsigned __int32 newUnknownSubAllocation4Size;
			// unsigned __int32 newUnknownSubAllocation2Size;
			// unsigned __int32 newUnknownSubAllocation5Size;
			// unsigned __int32 const newGameStateGlobalsSize;
			// __int32 extraGlobalsSize;
			// unsigned __int32 origUnknownSubAllocation5Size;
			// function call : unsigned long (*const)(long, unsigned long, long)
			// function call : unsigned long (*const)(long, unsigned long, long)
			todo("implement");
			__int32 __result = _sub_10A8AB70();
			return __result;
		}

		_extern void _sub_10A8AF70();
		void ExpandRenderGlobals() // 0x10A8AF70
		{
			mangled_x86(MANGLED_TODO, "?ExpandRenderGlobals@Memory@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A8AF70();
		}

		_extern void _sub_10A8AEC0();
		void ExpandMainGlobalMemoryMap() // 0x10A8AEC0
		{
			mangled_x86(MANGLED_TODO, "?ExpandMainGlobalMemoryMap@Memory@Patches@@YAXXZ");
			// procedure flags: nofpo
			// unsigned __int32 dataSizeIncrease;
			// Modules::ModuleGame &moduleGame;
			todo("implement");
			_sub_10A8AEC0();
		}

		_extern void _sub_10A8B140(char const *);
		void OnMapLoadCallback(char const *mapName) // 0x10A8B140
		{
			mangled_x86(MANGLED_TODO, "?OnMapLoadCallback@Memory@Patches@@YAXPBD@Z");
			// char const *mapName;
			todo("implement");
			_sub_10A8B140(mapName);
		}

		_extern void _sub_10A8A510();
		void ApplyAll() // 0x10A8A510
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Memory@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A8A510();
		}

		_extern void _sub_10A8A4D0();
		void ApplyAfterInit() // 0x10A8A4D0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAfterInit@Memory@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A8A4D0();
		}
	}
}

/* ---------- private code */
