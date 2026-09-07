/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BitStream.hpp"
#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/cseries/static_string.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Debug/CrashReporting/CrashReporter.hpp"
#include "ElDorito.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "Utils/Macros.hpp"
#include "Utils/ProcessUtils.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <memory>
#include <mutex>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class Hook;
namespace Blam
{
	class BitStream;
}
namespace Debug
{
	namespace CrashReporting
	{
		struct s_crash_info;
	}
}
namespace
{
	struct s_tag_history_entry;
	struct s_extra_exception_info;
	struct s_per_thread_exception_info;
	struct ModuleInfo;
	struct s_exception_information;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace Debug {}
using namespace ::Debug;
namespace Debug
{
	namespace CrashReporting {}
	using namespace Debug::CrashReporting;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Logging {}
	using namespace Patches::Logging;
	namespace Core {}
	using namespace Patches::Core;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

namespace
{
	enum e_tag_get_failed_reason
	{
		_tag_get_failed_invalid_tag = 0,
		_tag_get_failed_not_loaded,
		_tag_get_failed_unexpected_group,
	};
}
/* ---------- definitions */

namespace
{
	struct s_tag_history_entry
	{
		long tag_load_sequence_number; // 0x0
		unsigned long group_tag; // 0x4
		long index; // 0x8
	};
	static_assert(sizeof(s_tag_history_entry) == 12, "Invalid s_tag_history_entry size");

	#pragma pack(push, 4)
	struct s_extra_exception_info
	{
		s_tag_history_entry tag_history[4]; // 0x0
		long volatile tag_history_count; // 0x30
	};
	#pragma pack(pop)
	static_assert(sizeof(s_extra_exception_info) == 52, "Invalid s_extra_exception_info size");

	#pragma pack(push, 4)
	struct s_per_thread_exception_info
	{
		c_static_sliding_buffer<s_tag_history_entry,4> tag_history; // 0x0
		s_per_thread_exception_info(); /* compiler_generated() */
	};
	#pragma pack(pop)
	static_assert(sizeof(s_per_thread_exception_info) == 60, "Invalid s_per_thread_exception_info size");

}
namespace Blam
{
	namespace Network
	{
		typedef bool (*DeserializePacketFn)(Blam::BitStream *, __int32, void *);
		typedef void (*SerializePacketFn)(Blam::BitStream *, __int32, void const *);
	}
}

namespace
{
	struct ModuleInfo
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > Path; // 0x0
		unsigned __int32 Address; // 0x1C
		unsigned __int32 Size; // 0x20
		unsigned __int32 EntryPoint; // 0x24
		ModuleInfo(ModuleInfo &); /* compiler_generated() */
		ModuleInfo(ModuleInfo const &); /* compiler_generated() */
		ModuleInfo(); /* compiler_generated() */
		~ModuleInfo(); /* compiler_generated() */
		ModuleInfo &operator=(ModuleInfo &); /* compiler_generated() */
		ModuleInfo &operator=(ModuleInfo const &); /* compiler_generated() */
	};
	static_assert(sizeof(ModuleInfo) == 40, "Invalid ModuleInfo size");

	//@@anonymous-namespace@@
	#pragma pack(push, 4)
	struct s_exception_information
	{
		long volatile ready; // 0x0
		unsigned __int32 platform_thread_id; // 0x4
		_CONTEXT context; // 0x8
		unsigned long _exception_code; // 0x2D4
		unsigned long exception_flags; // 0x2D8
		unsigned __int32 exception_address; // 0x2DC
		unsigned long exception_number_of_parameters; // 0x2E0
		unsigned long exception_parameters[4]; // 0x2E4
	};
	#pragma pack(pop)
	static_assert(sizeof(s_exception_information) == 756, "Invalid s_exception_information size");
}
/* ---------- prototypes */

namespace Patches
{
	namespace Logging
	{
		extern void ApplyAll();
	}
}

/* ---------- globals */

extern std::atomic_flag g_gameIsCrashed; // 0x12458D5C

/* ---------- private variables */

namespace
{
	extern Hook NetworkLogHook; // 0x12458E08
	extern Hook SSLHook; // 0x12458DD0
	extern Hook UIHook; // 0x12458DEC
	extern Hook Game1Hook; // 0x12458DB4
	extern Hook DebugLogFloatHook; // 0x12458D98
	extern Hook DebugLogIntHook; // 0x12458D7C
	extern Hook DebugLogStringHook; // 0x12458D60
	extern unsigned __int32 origVirtualAllocAddress; // 0x12458E24
}
/* ---------- public code */

namespace Patches
{
	namespace Logging
	{
		_extern void _sub_10A84AE0();
		void ApplyAll() // 0x10A84AE0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Logging@Patches@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10A85690
			// static ...; // 0x10A85684
			// static ...; // 0x10A8567C
			// unsigned long temp;
			// function call : __int32 (void *, unsigned long, unsigned long, unsigned long *)
			todo("implement");
			_sub_10A84AE0();
		}
	}
}

/* ---------- private code */

namespace Debug
{
	namespace CrashReporting
	{
		extern s_crash_info::s_exception* _sub_10A849A0(::Debug::CrashReporting::s_crash_info::s_exception *const);
		_inline s_crash_info::s_exception::s_exception() // 0x10A849A0
		{
			// Debug::CrashReporting::s_crash_info::<unnamed-type-exception>::<unnamed-type-exception>
			// Debug::CrashReporting::s_crash_info::s_exception *const this;
			compiler_generated();
			todo("implement");
			_sub_10A849A0(this);
		}

		_extern void _sub_10A84A90(::Debug::CrashReporting::s_crash_info::s_exception *const);
		_inline s_crash_info::s_exception::~s_exception() // 0x10A84A90
		{
			// Debug::CrashReporting::s_crash_info::<unnamed-type-exception>::~<unnamed-type-exception>
			// Debug::CrashReporting::s_crash_info::s_exception *const this;
			compiler_generated();
			todo("implement");
			_sub_10A84A90(this);
		}
	}
}
