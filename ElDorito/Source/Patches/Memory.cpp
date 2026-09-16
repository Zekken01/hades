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
#include "Blam/cache/physical_memory_map.hpp"
#include "mods/memory/physical_memory_manager.hpp"

/* ---------- forward declarations */

struct c_restricted_memory;
namespace Modules
{
	class ModuleGame;
}
namespace hades_file_local
{
	struct c_debug_game_state_allocation;
}
using namespace hades_file_local;

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

namespace hades_file_local
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
using namespace hades_file_local;
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

void physical_memory_initialize_hook();
long __fastcall c_restricted_memory__add_member_hook(c_restricted_memory *thisptr, void *unused, char const *name, char const *type, unsigned long size_in_bytes, unsigned char alignment_bits, void *allocate_function, void *update_function, void *free_function);

/* ---------- globals */

extern unsigned long (*const data_allocation_size)(long, unsigned long, long); // 0x11248880
extern long const k_number_of_xbox_sound_datums; // 0x111ABBB4

/* ---------- private variables */

namespace hades_file_local
{
	extern unsigned __int32 newDataSize; // 0x124645F4
	extern unsigned __int32 newCacheSize; // 0x124645F8
	extern unsigned __int32 physicalMemorySize; // 0x124645FC
}
using namespace hades_file_local;
_iobuf *c_debug_game_state_allocation::m_fp; // 0x12464600
bool c_debug_game_state_allocation::m_enabled; // 0x12464604

/* ---------- public code */

namespace Patches
{
	namespace Memory
	{
		__int32 ExpandRuntimeStateGlobals() // 0x10A8AF90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ExpandRuntimeStateGlobals@Memory@Patches@@YAHXZ");
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

			const unsigned __int32 origRuntimeGlobalsSize = 0x380000;
			unsigned __int32 extraSize = 0;

			unsigned __int32 origGameStateCompressionScratchSize = 0x4B000;
			unsigned __int32 newGameStateCompressionScratchSize = origGameStateCompressionScratchSize;
			*(unsigned __int32 *)0x510A6E = newGameStateCompressionScratchSize;
			*(unsigned __int32 *)0x510A86 = newGameStateCompressionScratchSize;
			extraSize += newGameStateCompressionScratchSize - origGameStateCompressionScratchSize;

			unsigned __int32 oldXboxSoundCount = 8192;
			unsigned __int32 newXboxSoundCount = k_number_of_xbox_sound_datums;
			unsigned __int32 xboxSoundSize = 12;
			unsigned __int32 newXboxSoundSize = 32;
			*(unsigned __int32 *)0x66009B = newXboxSoundCount;
			extraSize += data_allocation_size(newXboxSoundCount, newXboxSoundSize, 0) - data_allocation_size(oldXboxSoundCount, xboxSoundSize, 0);
			extraSize += ((unsigned long (*)(long))0x9668D0)(k_number_of_xbox_sound_datums);
			extraSize += 0xA8C0;

			unsigned __int32 newRuntimeGlobalsSize = (origRuntimeGlobalsSize + extraSize + 0xFFFF) & 0xFFFF0000;
			*(unsigned __int32 *)0x509F31 = newRuntimeGlobalsSize;
			*(unsigned __int32 *)0x509CD7 = newRuntimeGlobalsSize;
			*(unsigned __int32 *)0x509D6A = newRuntimeGlobalsSize;
			*(unsigned __int32 *)0x509E63 = newRuntimeGlobalsSize;
			*(unsigned __int32 *)0x509EC7 = newRuntimeGlobalsSize;

			return newRuntimeGlobalsSize - origRuntimeGlobalsSize;
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

		void ExpandRenderGlobals() // 0x10A8AF70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ExpandRenderGlobals@Memory@Patches@@YAXXZ");
			// procedure flags: nofpo
		}

		void ExpandMainGlobalMemoryMap() // 0x10A8AEC0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ExpandMainGlobalMemoryMap@Memory@Patches@@YAXXZ");
			// procedure flags: nofpo
			// unsigned __int32 dataSizeIncrease;
			// Modules::ModuleGame &moduleGame;

			auto &gameModule = Modules::ModuleGame::Instance();

			__int32 size = ExpandGameStateGlobals() + ExpandRuntimeStateGlobals();
			newDataSize = (size + 0x4D00000 + 0xFFF) & 0xFFFFF000;

			physicalMemorySize = 0x45000000;
			if (physicalMemorySize < newDataSize)
				physicalMemorySize = newDataSize;

			newCacheSize = physicalMemorySize - newDataSize;
		}

		void OnMapLoadCallback(char const *mapName) // 0x10A8B140
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnMapLoadCallback@Memory@Patches@@YAXPBD@Z");
			// char const *mapName;

			c_debug_game_state_allocation::end();
		}

		_extern void _sub_10A8A510();
		void ApplyAll() // 0x10A8A510
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Memory@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A8A510();
		}

		void ApplyAfterInit() // 0x10A8A4D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAfterInit@Memory@Patches@@YAXXZ");
			// procedure flags: nofpo

			Patches::Memory::ExpandMainGlobalMemoryMap();
		}
	}
}

/* ---------- private code */

_inline void c_debug_game_state_allocation::record_allocation(long allocation_type, char const *name, char const *type, unsigned long size) // 0x10A8B7F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?record_allocation@c_debug_game_state_allocation@hades_file_local@@SAXJPBD0K@Z");
	// `anonymous-namespace'::c_debug_game_state_allocation::record_allocation
	// unsigned long size;
		// long i;
			// unsigned long size;

	if (!m_enabled || !m_fp)
		return;

	fprintf(m_fp, "% 44s,% 24s", name, type);

	for (long i = 0; i < 5; i++)
	{
		long value = 0;
		if (allocation_type == i)
			value = value;

		fprintf(m_fp, ",% 40d", value);
	}

	fprintf(m_fp, "\n");
}

_inline void c_debug_game_state_allocation::begin(unsigned long memory_total) // 0x10A8B180
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?begin@c_debug_game_state_allocation@hades_file_local@@SAXK@Z");
	// `anonymous-namespace'::c_debug_game_state_allocation::begin
	// unsigned long memory_total;
	// char const *(*const version_get_full_string)();
		// long i;
	// function call : char const *(*const)()

	if (!m_enabled || fopen_s(&m_fp, "gamestate.txt", "w"))
		return;

	char const *(*const version_get_full_string)() = (char const *(*)())0x5013A0;

	fprintf(m_fp, "game state allocations from: %s\n", version_get_full_string());
	fprintf(m_fp, "memory total, %u\n", memory_total);
	fprintf(m_fp, "memory available, %u\n", 0);
	fprintf(m_fp, "% 44s,% 24s", "name", "type");
	for (long i = 0; i < 5; i++)
		fprintf(m_fp, ",% 40s", ((char const **)0x18A15FC)[i]);
	fprintf(m_fp, "\n");
}

_extern void _sub_10A8B460();
_inline void c_debug_game_state_allocation::end() // 0x10A8B460
{
	// `anonymous-namespace'::c_debug_game_state_allocation::end
	// procedure flags: nofpo
	{
		// long i;
		{
			// long flags;
			// unsigned long size;
			// char *region;
		}
	}
	{
		{
		}
	}
	todo("implement");
	_sub_10A8B460();
}

void physical_memory_initialize_hook() // 0x10A8B650
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?physical_memory_initialize_hook@@YAXXZ");
	// `anonymous-namespace'::physical_memory_initialize_hook
	// procedure flags: nofpo
	// void *physical_memory_base_address;

	c_physical_memory_manager::initialize(physicalMemorySize);

	void *physical_memory_base_address = c_physical_memory_manager::get_base_address();

	c_physical_memory_manager::push(_physical_memory_stage_shared);
	c_physical_memory_manager::allocate(_physical_memory_stage_shared, "shared-data", newDataSize, 2, nullptr);

	memset((void *)0x238EC50, 0, sizeof(s_physical_memory_globals));

	((s_physical_memory_globals *)0x238EC50)->start_address = physical_memory_base_address;
	((s_physical_memory_globals *)0x238EC50)->current_address = c_physical_memory_manager::get_current_address();
	((s_physical_memory_globals *)0x238EC50)->field_10 = 1;
	((s_physical_memory_globals *)0x238EC50)->current_stage = 0;
	((s_physical_memory_globals *)0x238EC50)->stages[0].field_10 = 0;
	((s_physical_memory_globals *)0x238EC50)->stages[0].start_address = physical_memory_base_address;
	((s_physical_memory_globals *)0x238EC50)->stages[0].end_address = c_physical_memory_manager::get_current_address();
	((s_physical_memory_globals *)0x238EC50)->stages[0].field_10 = 1;
	((s_physical_memory_globals *)0x238EC50)->stages[0].num_allocations = 0;
	*(void **)0x238ED08 = physical_memory_base_address;
	*(void **)0x238ED0C = physical_memory_base_address;
}

_extern long _sub_10A8B310(c_restricted_memory *, void *, char const *, char const *, unsigned long, unsigned char, void *, void *, void *);
long __fastcall c_restricted_memory__add_member_hook(c_restricted_memory *thisptr, void *unused, char const *name, char const *type, unsigned long size_in_bytes, unsigned char alignment_bits, void *allocate_function, void *update_function, void *free_function) // 0x10A8B310
{
	// `anonymous-namespace'::c_restricted_memory__add_member_hook
	// void *free_function;
	// long allocation_type;
	// unsigned long original_used_size;
	// unsigned long new_region_used_size;
	// unsigned long region_total_size;
	// long (*const add_member_impl)(c_restricted_memory *, char const *, char const *, unsigned long, unsigned char, void *, void *, void *);
	// unsigned long *region_used_size_ptr;
	// long member_index;
	// unsigned long allocated_size;
	// function call : long (*const)(c_restricted_memory *, char const *, char const *, unsigned long, unsigned char, void *, void *, void *)
	todo("implement");
	long __result = _sub_10A8B310(thisptr, unused, name, type, size_in_bytes, alignment_bits, allocate_function, update_function, free_function);
	return __result;
}
