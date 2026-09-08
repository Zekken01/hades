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
#include "mods/datatypes/sliding_buffer.hpp"
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
struct s_cache_tag_instance;
namespace Blam
{
	class BitStream;
}
namespace Blam
{
	namespace Network
	{
		struct PacketTable;
		struct RegisteredPacket;
	}
}
namespace Debug
{
	namespace CrashReporting
	{
		struct s_crash_info;
	}
}
namespace hades_file_local
{
	struct s_tag_history_entry;
	struct s_extra_exception_info;
	struct s_per_thread_exception_info;
	struct ModuleInfo;
	struct s_exception_information;
}
using namespace hades_file_local;

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

namespace hades_file_local
{
	enum e_tag_get_failed_reason
	{
		_tag_get_failed_invalid_tag = 0,
		_tag_get_failed_not_loaded,
		_tag_get_failed_unexpected_group,
	};
}
using namespace hades_file_local;
/* ---------- definitions */

namespace hades_file_local
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
using namespace hades_file_local;
namespace Blam
{
	namespace Network
	{
		typedef bool (*DeserializePacketFn)(Blam::BitStream *, __int32, void *);
		typedef void (*SerializePacketFn)(Blam::BitStream *, __int32, void const *);
	}
}

namespace hades_file_local
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
using namespace hades_file_local;
/* ---------- prototypes */

namespace Patches
{
	namespace Logging
	{
		extern void ApplyAll();
	}
}

void dbglog(char const *module, char const *format, ...);
void debuglog_string(char *name, char *value);
void debuglog_int(char *name, __int32 value);
void debuglog_float(char *name, float value);
void networkLogHook(char *format, ...);
void sslLogHook(char a1, __int32 a2, void *a3, void *a4, char a5);
void uiLogHook(char a1, __int32 a2, void *a3, void *a4, char a5);
bool packetRecvHook(void *thisPtr, __int32 unused, Blam::BitStream *stream, __int32 *packetIdOut, __int32 *packetSizeOut, void *packetBuffer);
void packetSendHook(void *thisPtr, __int32 unused, Blam::BitStream *stream, __int32 packetId, __int32 packetSize, void *packetBuffer);
void build_tag_history_for_crash_report(::Debug::CrashReporting::s_crash_info &crash_info);
void ExceptionHook(char *msg);
void *virtualAllocHook(void *address, unsigned __int32 size, unsigned __int32 allocationType, unsigned __int32 protect);
void notify_tag_get_failed(long cause_group, long cause_tag_index, e_tag_get_failed_reason reason);
void *tag_get_hook(unsigned long group, long index);
void system_build_exception_information_hook(_EXCEPTION_POINTERS const *exception_pointers, s_exception_information *out_info);

/* ---------- globals */

extern std::atomic_flag g_gameIsCrashed; // 0x12458D5C

/* ---------- private variables */

namespace hades_file_local
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
using namespace hades_file_local;
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

_extern void _sub_10A85ED0(char const *, char const *, ...);
void dbglog(char const *module, char const *format, ...) // 0x10A85ED0
{
	// `anonymous-namespace'::dbglog
	// static ...; // 0x10A85FC8
	// char const *module;
	// char const *format;
	// char *ap;
	// char buff[4096];
	// char const *backupFormat;
	todo("implement");
	_sub_10A85ED0(module, format);
}

_extern void _sub_10A86160(char *, char *);
void debuglog_string(char *name, char *value) // 0x10A86160
{
	// `anonymous-namespace'::debuglog_string
	// char *value;
	todo("implement");
	_sub_10A86160(name, value);
}

_extern void _sub_10A860D0(char *, __int32);
void debuglog_int(char *name, __int32 value) // 0x10A860D0
{
	// `anonymous-namespace'::debuglog_int
	// __int32 value;
	todo("implement");
	_sub_10A860D0(name, value);
}

_extern void _sub_10A86030(char *, float);
void debuglog_float(char *name, float value) // 0x10A86030
{
	// `anonymous-namespace'::debuglog_float
	// float value;
	todo("implement");
	_sub_10A86030(name, value);
}

_extern void _sub_10A86440(char *, ...);
void networkLogHook(char *format, ...) // 0x10A86440
{
	// `anonymous-namespace'::networkLogHook
	// static ...; // 0x10A8671C
	// static ...; // 0x10A86704
	// static ...; // 0x10A866FC
	// char *format;
	// char *args;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > formatStr;
	// char dstBuf[4096];
	todo("implement");
	_sub_10A86440(format);
}

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
	}
}

_extern void _sub_10A86ED0(char, __int32, void *, void *, char);
void sslLogHook(char a1, __int32 a2, void *a3, void *a4, char a5) // 0x10A86ED0
{
	// `anonymous-namespace'::sslLogHook
	// char a5;
	// char const *logData2;
	// char const *logData1;
	todo("implement");
	_sub_10A86ED0(a1, a2, a3, a4, a5);
}

_inline s_per_thread_exception_info::s_per_thread_exception_info() // 0x10A84A40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_per_thread_exception_info@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::s_per_thread_exception_info::s_per_thread_exception_info
	// s_per_thread_exception_info *const this;

	compiler_generated();
}

namespace Debug
{
	namespace CrashReporting
	{
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

_extern void _sub_10A87380(char, __int32, void *, void *, char);
void uiLogHook(char a1, __int32 a2, void *a3, void *a4, char a5) // 0x10A87380
{
	// `anonymous-namespace'::uiLogHook
	// char a5;
	// char const *logData1;
	todo("implement");
	_sub_10A87380(a1, a2, a3, a4, a5);
}

_extern bool _sub_10A86C90(void *, __int32, Blam::BitStream *, __int32 *, __int32 *, void *);
bool packetRecvHook(void *thisPtr, __int32 unused, Blam::BitStream *stream, __int32 *packetIdOut, __int32 *packetSizeOut, void *packetBuffer) // 0x10A86C90
{
	// `anonymous-namespace'::packetRecvHook
	// void *packetBuffer;
	// Blam::Network::PacketTable *packetTable;
	// bool (*DeserializePacketInfo)(void *, Blam::BitStream *, __int32 *, __int32 *, void *);
	// Blam::Network::RegisteredPacket *packet;
	// function call : bool (*)(void *, Blam::BitStream *, __int32 *, __int32 *, void *)
	todo("implement");
	bool __result = _sub_10A86C90(thisPtr, unused, stream, packetIdOut, packetSizeOut, packetBuffer);
	return __result;
}

_extern void _sub_10A86DC0(void *, __int32, Blam::BitStream *, __int32, __int32, void *);
void packetSendHook(void *thisPtr, __int32 unused, Blam::BitStream *stream, __int32 packetId, __int32 packetSize, void *packetBuffer) // 0x10A86DC0
{
	// `anonymous-namespace'::packetSendHook
	// void *packetBuffer;
	// bool (*SerializePacketInfo)(void *, Blam::BitStream *, __int32, __int32, void *);
	// Blam::Network::PacketTable *packetTable;
	// Blam::Network::RegisteredPacket *packet;
	// function call : bool (*)(void *, Blam::BitStream *, __int32, __int32, void *)
	todo("implement");
	_sub_10A86DC0(thisPtr, unused, stream, packetId, packetSize, packetBuffer);
}

_extern void _sub_10A85C70(::Debug::CrashReporting::s_crash_info &);
void build_tag_history_for_crash_report(::Debug::CrashReporting::s_crash_info &crash_info) // 0x10A85C70
{
	// `anonymous-namespace'::build_tag_history_for_crash_report
	// static ...; // 0x10A85E3E
	// static ...; // 0x10A85E32
	// static ...; // 0x10A85E28
	// static ...; // 0x10A85E04
	// static ...; // 0x10A85DFC
	// Debug::CrashReporting::s_crash_info &crash_info;
	{
		// long i;
		{
			// s_tag_history_entry history_entry;
			// char group_ascii[5];
			// s_static_string<256> name_buff;
			// char const *name;
		}
	}
	todo("implement");
	_sub_10A85C70(crash_info);
}

_extern void _sub_10A85990(char *);
void ExceptionHook(char *msg) // 0x10A85990
{
	// `anonymous-namespace'::ExceptionHook
	// static ...; // 0x10A85BD0
	// static ...; // 0x10A85BCB
	// static ...; // 0x10A85BC0
	// static ...; // 0x10A85B9C
	// static ...; // 0x10A85B94
	// char *msg;
	// HINSTANCE__ *hMod;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > moduleName;
	// s_exception_information *except;
	// char info[1024];
	// Debug::CrashReporting::s_crash_info crash_info;
	todo("implement");
	_sub_10A85990(msg);
}

_extern void *_sub_10A87430(void *, unsigned __int32, unsigned __int32, unsigned __int32);
void *virtualAllocHook(void *address, unsigned __int32 size, unsigned __int32 allocationType, unsigned __int32 protect) // 0x10A87430
{
	// `anonymous-namespace'::virtualAllocHook
	// unsigned __int32 protect;
	// void *addr;
	// function call : void *(*)(void *, unsigned __int32, unsigned __int32, unsigned __int32)
	todo("implement");
	void * __result = _sub_10A87430(address, size, allocationType, protect);
	return __result;
}

_extern void _sub_10A867F0(long, long, e_tag_get_failed_reason);
void notify_tag_get_failed(long cause_group, long cause_tag_index, e_tag_get_failed_reason reason) // 0x10A867F0
{
	// `anonymous-namespace'::notify_tag_get_failed
	// static ...; // 0x10A86B72
	// static ...; // 0x10A86B64
	// static ...; // 0x10A86B58
	// static ...; // 0x10A86B1C
	// static ...; // 0x10A86B14
	// long cause_group;
	// long cause_tag_index;
	// e_tag_get_failed_reason reason;
	// char const *cause_tag_name;
	// char const *cause_group_name;
	// char cause_group_ascii[5];
	// __int32 decision;
	// unsigned long assertLevel;
	// s_static_string<8192> msg;
	{
		// char actual_group_ascii[5];
		// unsigned long actual_group;
	}
	{
		// long i;
		{
			// s_tag_history_entry history_entry;
			// char group_ascii[5];
			// unsigned long group;
			// char const *name;
		}
	}
	// function call : __int32 (HWND__ *, char const *, char const *, unsigned __int32)
	todo("implement");
	_sub_10A867F0(cause_group, cause_tag_index, reason);
}

_extern void *_sub_10A87100(unsigned long, long);
void *tag_get_hook(unsigned long group, long index) // 0x10A87100
{
	// `anonymous-namespace'::tag_get_hook
	// long index;
	// s_cache_tag_instance *instance;
	// long absolute_index;
	todo("implement");
	void * __result = _sub_10A87100(group, index);
	return __result;
}

_extern void _sub_10A86FB0(_EXCEPTION_POINTERS const *, s_exception_information *);
void system_build_exception_information_hook(_EXCEPTION_POINTERS const *exception_pointers, s_exception_information *out_info) // 0x10A86FB0
{
	// `anonymous-namespace'::system_build_exception_information_hook
	// s_exception_information *out_info;
	// long count;
	// c_static_sliding_buffer<s_tag_history_entry,4> &tag_history;
	// s_extra_exception_info &extra_info;
	{
		// long i;
	}
	// function call : void (*)(_EXCEPTION_POINTERS const *, s_exception_information *)
	todo("implement");
	_sub_10A86FB0(exception_pointers, out_info);
}
