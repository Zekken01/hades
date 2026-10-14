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
#include "Modules/ModuleDebug.hpp"  // hades: added for 0x10A867F0
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
#include "Utils/Logger.hpp"

#include "Patches/Core.hpp"  // hades: added for 0x10A85990

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
		std::string Path; // 0x0
		unsigned __int32 Address; // 0x1C
		unsigned __int32 Size; // 0x20
		unsigned __int32 EntryPoint; // 0x24
		ModuleInfo(ModuleInfo &); /* compiler_generated() */
		ModuleInfo(ModuleInfo const &); /* compiler_generated() */
		ModuleInfo(); /* compiler_generated() */
		~ModuleInfo() = default; /* compiler_generated() */
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

namespace Utils { extern std::string GetStackTraceString(__int32 framesToSkip, __int32 framesToCapture); }  // hades: added for 0x10A87430

extern s_cache_file_tag_globals *g_cache_file_tag_globals;  // hades: added for 0x10A85C70
char const *tag_get_name(long tag_index);  // hades: added for 0x10A85C70
char const *tag_to_string(unsigned long group_tag, char *buffer, long length);  // hades: added for 0x10A85C70

namespace Blam { namespace Network { PacketTable *GetPacketTable(); } }  // hades: added for 0X10A86DC0

namespace Patches
{
	namespace Logging
	{
		extern void ApplyAll();
	}
}

void dbglog(char const *module, char const *format, ...);
void __stdcall debuglog_string(char *name, char *value);
void __stdcall debuglog_int(char *name, __int32 value);
void __stdcall debuglog_float(char *name, float value);
void networkLogHook(char *format, ...);
void sslLogHook(char a1, __int32 a2, void *a3, void *a4, char a5);
void uiLogHook(char a1, __int32 a2, void *a3, void *a4, char a5);
bool __fastcall packetRecvHook(void *thisPtr, __int32 unused, Blam::BitStream *stream, __int32 *packetIdOut, __int32 *packetSizeOut, void *packetBuffer);
void __fastcall packetSendHook(void *thisPtr, __int32 unused, Blam::BitStream *stream, __int32 packetId, __int32 packetSize, void *packetBuffer);
void build_tag_history_for_crash_report(::Debug::CrashReporting::s_crash_info &crash_info);
void ExceptionHook(char *msg);
void *__stdcall virtualAllocHook(void *address, unsigned __int32 size, unsigned __int32 allocationType, unsigned __int32 protect);
void notify_tag_get_failed(long cause_group, long cause_tag_index, e_tag_get_failed_reason reason);
void *tag_get_hook(unsigned long group, long index);
void system_build_exception_information_hook(_EXCEPTION_POINTERS const *exception_pointers, s_exception_information *out_info);

/* ---------- globals */

extern std::atomic_flag g_gameIsCrashed; // 0x12458D5C

/* ---------- private variables */

namespace hades_file_local
{
	Hook DebugLogStringHook = Hook(0x218A30, (void *)debuglog_string); // 0x12458D60
	Hook DebugLogIntHook = Hook(0x218A10, (void *)debuglog_int); // 0x12458D7C
	Hook DebugLogFloatHook = Hook(0x2189F0, (void *)debuglog_float); // 0x12458D98
	Hook Game1Hook = Hook(0x106FB0, (void *)dbglog); // 0x12458DB4
	Hook SSLHook = Hook(0xA7FE10, (void *)sslLogHook); // 0x12458DD0
	Hook UIHook = Hook(0xAED600, (void *)uiLogHook); // 0x12458DEC
	Hook NetworkLogHook = Hook(0x9858D0, (void *)networkLogHook); // 0x12458E08
	extern unsigned __int32 origVirtualAllocAddress; // 0x12458E24
	extern s_extra_exception_info g_extra_exception_info; // 0x12458E28
	// hades: the per-thread tag history every hook here reads. The name is ours;
	// the original reaches it only through its TLS offset.
	thread_local s_per_thread_exception_info perThreadExceptionInfo;
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Logging
	{
		void ApplyAll() // 0x10A84AE0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Logging@Patches@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10A85690
			// static ...; // 0x10A85684
			// static ...; // 0x10A8567C
			// unsigned long temp;
			// function call : __int32 (void *, unsigned long, unsigned long, unsigned long *)

			*(unsigned __int32 *)0x9053C7 = 0x7FF;
			Patch(0x11C158, { 0x8D, 0x85, 0x00, 0xFC, 0xFF, 0xFF, 0x50 }).Apply();
			Patch(0x11C165, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }).Apply();
			Hook(0x11C15F, ExceptionHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x11BCF0, system_build_exception_information_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0x243FB38).Write<bool>(1);
			NetworkLogHook.Apply();
			SSLHook.Apply();
			UIHook.Apply();
			Game1Hook.Apply();
			DebugLogFloatHook.Apply();
			DebugLogIntHook.Apply();
			DebugLogStringHook.Apply();
			Hook(0x7D518, packetRecvHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x83EEA, packetRecvHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7D618, packetSendHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7D81D, packetSendHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x841F5, packetSendHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			unsigned long temp;
			VirtualProtect((LPVOID)0x1600194, 4, PAGE_READWRITE, &temp);
			origVirtualAllocAddress = *(unsigned __int32 *)0x1600194;
			*(unsigned __int32 *)0x1600194 = (unsigned __int32)&virtualAllocHook;
			Hook(0x103370, tag_get_hook).Apply();
		}
	}
}

/* ---------- private code */

void dbglog(char const *module, char const *format, ...) // 0x10A85ED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?dbglog@@YAXPBD0ZZ");
	// `anonymous-namespace'::dbglog
	// static ...; // 0x10A85FC8
	// char const *module;
	// char const *format;
	// char *ap;
	// char buff[4096];
	// char const *backupFormat;

	char const *backupFormat = "";
	if (!format)
		format = backupFormat;
	if (module && !strcmp(module, "game_tick"))
		return;
	char *ap;
	char buff[4096];
	va_start(ap, format);
	vsprintf_s(buff, sizeof(buff), format, ap);
	va_end(ap);
	Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Debug, Utils::LogLevel::Info, "%s: %s", module, buff);
}

void __stdcall debuglog_string(char *name, char *value) // 0x10A86160
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?debuglog_string@@YGXPAD0@Z");
	// `anonymous-namespace'::debuglog_string
	// char *value;

	Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Debug, Utils::LogLevel::Info, "%s: %s", name, value);
}

void __stdcall debuglog_int(char *name, __int32 value) // 0x10A860D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?debuglog_int@@YGXPADH@Z");
	// `anonymous-namespace'::debuglog_int
	// __int32 value;

	Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Debug, Utils::LogLevel::Info, "%s: %d", name, value);
}

void __stdcall debuglog_float(char *name, float value) // 0x10A86030
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?debuglog_float@@YGXPADM@Z");
	// `anonymous-namespace'::debuglog_float
	// float value;

	Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Debug, Utils::LogLevel::Info, "%s: %f", name, value);
}

void networkLogHook(char *format, ...) // 0x10A86440
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?networkLogHook@@YAXPADZZ");
	// `anonymous-namespace'::networkLogHook
	// static ...; // 0x10A8671C
	// static ...; // 0x10A86704
	// static ...; // 0x10A866FC
	// char *format;
	// char *args;
	// std::string formatStr;
	// char dstBuf[4096];

	if (!Utils::Singleton<Utils::Logger>::Instance().TestLevel(Utils::LogTypes::Network, Utils::LogLevel::Info))
		return;
	std::string formatStr = format;
	Utils::String::ReplaceString(formatStr, "%LX", "%llX");
	Utils::String::ReplaceString(formatStr, "%Lx", "%llx");
	Utils::String::ReplaceString(formatStr, "%8X", "%08X");
	Utils::String::ReplaceString(formatStr, "%8x", "%08x");
	char dstBuf[4096];
	char *args;
	va_start(args, format);
	vsnprintf_s(dstBuf, 4096, 4095, formatStr.c_str(), args);
	va_end(args);
	Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "%s", dstBuf);
}

namespace Debug
{
	namespace CrashReporting
	{
	}
}

void sslLogHook(char a1, __int32 a2, void *a3, void *a4, char a5) // 0x10A86ED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sslLogHook@@YAXDHPAX0D@Z");
	// `anonymous-namespace'::sslLogHook
	// char a5;
	// char const *logData2;
	// char const *logData1;

	char const *str1 = *(char const **)a3;
	char const *str2 = *(char const **)((unsigned char *)a3 + 8);
	if (!str1)
		str1 = "";
	else
		str1 += 12;
	if (!str2)
		str2 = "";
	else
		str2 += 12;
	Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "%s - %s", str1, str2);
}

// mangled_x86(MANGLED_DEFAULT, "??0s_per_thread_exception_info@hades_file_local@@QAE@XZ"); no body to assert in
_inline s_per_thread_exception_info::s_per_thread_exception_info() = default; // 0x10A84A40

namespace Debug
{
	namespace CrashReporting
	{
	}
}

void uiLogHook(char a1, __int32 a2, void *a3, void *a4, char a5) // 0x10A87380
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?uiLogHook@@YAXDHPAX0D@Z");
	// `anonymous-namespace'::uiLogHook
	// char a5;
	// char const *logData1;

	char const *logData1 = *(char **)a3;
	if (logData1 == 0)
		logData1 = "";
	else
		logData1 += 0xC;

	Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, logData1);
}

bool __fastcall packetRecvHook(void *thisPtr, __int32 unused, Blam::BitStream *stream, __int32 *packetIdOut, __int32 *packetSizeOut, void *packetBuffer) // 0x10A86C90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?packetRecvHook@@YI_NPAXHPAVBitStream@Blam@@PAH20@Z");
	// `anonymous-namespace'::packetRecvHook
	// void *packetBuffer;
	// Blam::Network::PacketTable *packetTable;
	// bool (*DeserializePacketInfo)(void *, Blam::BitStream *, __int32 *, __int32 *, void *);
	// Blam::Network::RegisteredPacket *packet;
	// function call : bool (*)(void *, Blam::BitStream *, __int32 *, __int32 *, void *)

	bool (__thiscall *packetRecv)(void *, Blam::BitStream *, __int32 *, __int32 *, void *) = (bool (__thiscall *)(void *, Blam::BitStream *, __int32 *, __int32 *, void *))0x47FF70;

	if (!packetRecv(thisPtr, stream, packetIdOut, packetSizeOut, packetBuffer))
	{
		return false;
	}

	Blam::Network::PacketTable *packetTable = Blam::Network::GetPacketTable();
	if (!packetTable)
	{
		return true;
	}

	Blam::Network::RegisteredPacket *packet = &packetTable->Packets[*packetIdOut];
	Utils::Singleton<Utils::Logger>::Instance().Log((Utils::LogTypes)2, (Utils::LogLevel)2, "RECV %s (size=0x%X)", packet->Name, *packetSizeOut);
	return true;
}

void __fastcall packetSendHook(void *thisPtr, __int32 unused, Blam::BitStream *stream, __int32 packetId, __int32 packetSize, void *packetBuffer) // 0x10A86DC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?packetSendHook@@YIXPAXHPAVBitStream@Blam@@HH0@Z");
	// `anonymous-namespace'::packetSendHook
	// void *packetBuffer;
	// bool (*SerializePacketInfo)(void *, Blam::BitStream *, __int32, __int32, void *);
	// Blam::Network::PacketTable *packetTable;
	// Blam::Network::RegisteredPacket *packet;
	// function call : bool (*)(void *, Blam::BitStream *, __int32, __int32, void *)

	void (__thiscall *sendPacket)(void *, Blam::BitStream *, __int32, __int32, void *) = (void (__thiscall *)(void *, Blam::BitStream *, __int32, __int32, void *))0x480090;
	sendPacket(thisPtr, stream, packetId, packetSize, packetBuffer);

	Blam::Network::PacketTable *packetTable = Blam::Network::GetPacketTable();
	if (!packetTable)
		return;

	Blam::Network::RegisteredPacket *packet = &packetTable->Packets[packetId];
	Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "SEND %s (size=0x%X)", packet->Name, packetSize);
}

void build_tag_history_for_crash_report(::Debug::CrashReporting::s_crash_info &crash_info) // 0x10A85C70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?build_tag_history_for_crash_report@@YAXAAUs_crash_info@CrashReporting@Debug@@@Z");
	// `anonymous-namespace'::build_tag_history_for_crash_report
	// static ...; // 0x10A85E3E
	// static ...; // 0x10A85E32
	// static ...; // 0x10A85E28
	// static ...; // 0x10A85E04
	// static ...; // 0x10A85DFC
	// Debug::CrashReporting::s_crash_info &crash_info;
		// long i;
			// s_tag_history_entry history_entry;
			// char group_ascii[5];
			// s_static_string<256> name_buff;
			// char const *name;

	if (g_cache_file_tag_globals->initialized)
	{
		for (long i = 0; i < g_extra_exception_info.tag_history_count; i++)
		{
			s_tag_history_entry history_entry = g_extra_exception_info.tag_history[i];
			if (history_entry.tag_load_sequence_number != g_cache_file_tag_globals->tag_load_sequence_number)
				continue;
			char const *name = tag_get_name(history_entry.index);
			char group_ascii[5];
			tag_to_string(history_entry.group_tag, group_ascii, 5);
			if (name)
			{
				s_static_string<256> name_buff;
				name_buff.print("%s.%s", name, history_entry.group_tag == -1 ? "unknown" : group_ascii);
				crash_info.tag_history.push_back(name_buff.get_string());
			}
		}
	}
}

void ExceptionHook(char *msg) // 0x10A85990
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ExceptionHook@@YAXPAD@Z");
	// `anonymous-namespace'::ExceptionHook
	// static ...; // 0x10A85BD0
	// static ...; // 0x10A85BCB
	// static ...; // 0x10A85BC0
	// static ...; // 0x10A85B9C
	// static ...; // 0x10A85B94
	// char *msg;
	// HINSTANCE__ *hMod;
	// std::string moduleName;
	// s_exception_information *except;
	// char info[1024];
	// Debug::CrashReporting::s_crash_info crash_info;

	g_gameIsCrashed.test_and_set();
	s_exception_information *except = reinterpret_cast<s_exception_information *>(0x238E888);
	HINSTANCE__ *hMod = Utils::ProcessUtils::GetModuleFromAddress((void *)except->exception_address);
	std::string moduleName = Utils::ProcessUtils::GetModuleNameForDisplay(hMod);
	char info[1024];
	sprintf_s(info, "%s - %s+%0X", msg, moduleName.c_str(), except->exception_address - (unsigned __int32)hMod);
	Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Debug, Utils::LogLevel::Error, info);
	Debug::CrashReporting::s_crash_info crash_info;
	crash_info.ctx = &except->context;
	crash_info.info = info;
	crash_info.exception.address = except->exception_address;
	crash_info.exception.code = except->_exception_code;
	crash_info.exception.flags = except->exception_flags;
	crash_info.exception.msg = msg;
	crash_info.exception.num_parameters = except->exception_number_of_parameters;
	build_tag_history_for_crash_report(crash_info);
	Debug::CrashReporting::ReportCrash(crash_info);
	Utils::Singleton<Utils::Logger>::Instance().Flush();
	Patches::Core::ExecuteShutdownCallbacks();
	exit(0);
}

void *__stdcall virtualAllocHook(void *address, unsigned __int32 size, unsigned __int32 allocationType, unsigned __int32 protect) // 0x10A87430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?virtualAllocHook@@YGPAXPAXIII@Z");
	// `anonymous-namespace'::virtualAllocHook
	// unsigned __int32 protect;
	// void *addr;
	// function call : void *(*)(void *, unsigned __int32, unsigned __int32, unsigned __int32)

	void *addr = reinterpret_cast<void *(__stdcall *)(void *, unsigned __int32, unsigned __int32, unsigned __int32)>(origVirtualAllocAddress)(address, size, allocationType, protect);
	Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Memory, Utils::LogLevel::Trace, "VirtualAlloc - Address: 0x%08X, Size: 0x%08X, Type: 0x%08X, Protect: 0x%08X, CallStack: %s", addr, size, allocationType, protect, Utils::GetStackTraceString(1, 5).c_str());
	return addr;
}

void notify_tag_get_failed(long cause_group, long cause_tag_index, e_tag_get_failed_reason reason) // 0x10A867F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?notify_tag_get_failed@@YAXJJW4e_tag_get_failed_reason@hades_file_local@@@Z");
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
		// char actual_group_ascii[5];
		// unsigned long actual_group;
		// long i;
			// s_tag_history_entry history_entry;
			// char group_ascii[5];
			// unsigned long group;
			// char const *name;
	// function call : __int32 (HWND__ *, char const *, char const *, unsigned __int32)

	unsigned long assertLevel = Modules::ModuleDebug::Instance().VarAssertLevel->ValueInt;
	if (!assertLevel)
		return;
	if (reason == _tag_get_failed_unexpected_group && assertLevel < 2)
		return;
	char const *cause_tag_name = tag_get_name(cause_tag_index);
	char cause_group_ascii[5];
	tag_to_string(cause_group, cause_group_ascii, 5);
	char const *cause_group_name = cause_group != -1 ? cause_group_ascii : "unknown";
	s_static_string<8192> msg;
	if (reason == _tag_get_failed_invalid_tag)
		msg.print("Invalid Tag [0x%04X]\nExpected Group: '%s'", cause_tag_index, cause_group_name);
	else if (reason == _tag_get_failed_not_loaded)
		msg.print("Tag not loaded!\n[0x%04X] '%s'\nExpected Group: '%s'", cause_tag_index, cause_tag_name, cause_group_name);
	else if (reason == _tag_get_failed_unexpected_group)
	{
		unsigned long actual_group = tag_get_group_tag(cause_tag_index);
		char actual_group_ascii[5];
		tag_to_string(actual_group, actual_group_ascii, 5);
		msg.print("Tag not in expected group!\n[0x%04X] '%s.%s'\nExpected Group '%s'", cause_tag_index, cause_tag_name, actual_group_ascii, cause_group_name);
	}
	msg.append("\n\nTag History:\n");
	for (long i = perThreadExceptionInfo.tag_history.get_first_index(); i != perThreadExceptionInfo.tag_history.get_last_index(); i++)
	{
		s_tag_history_entry history_entry = perThreadExceptionInfo.tag_history.get_element(i);
		unsigned long group = history_entry.group_tag;
		char const *name = tag_get_name(history_entry.index);
		char group_ascii[5];
		tag_to_string(group, group_ascii, 5);
		msg.append_print("[0x%04X] %s.%s\n", history_entry.index, name, group == -1 ? "unknown" : group_ascii);
	}
	__int32 decision = MessageBoxA(nullptr, msg.get_string(), "tag_get() failed.  Break into the debugger?", MB_YESNO);
	if (decision == IDYES)
		__debugbreak();
}

void *tag_get_hook(unsigned long group, long index) // 0x10A87100
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?tag_get_hook@@YAPAXKJ@Z");
	// `anonymous-namespace'::tag_get_hook
	// long index;
	// s_cache_tag_instance *instance;
	// long absolute_index;

	if (index == -1)
		return nullptr;
	if (index < 0 || index >= 0xFFFF)
	{
		notify_tag_get_failed(group, index, _tag_get_failed_invalid_tag);
		return nullptr;
	}
	long absolute_index = g_cache_file_tag_globals->index_to_absolute_index_map[index];
	if (absolute_index == -1)
	{
		notify_tag_get_failed(group, index, _tag_get_failed_not_loaded);
		return nullptr;
	}
	s_cache_tag_instance *instance = g_cache_file_tag_globals->instances[absolute_index];
	if (instance->group.tags[0] != group && instance->group.tags[1] != group && instance->group.tags[2] != group)
		notify_tag_get_failed(group, index, _tag_get_failed_unexpected_group);
	perThreadExceptionInfo.tag_history.insert(s_tag_history_entry{ g_cache_file_tag_globals->tag_load_sequence_number, instance->group.tags[0], index });
	return (char *)instance + instance->definition_offset;
}

void system_build_exception_information_hook(_EXCEPTION_POINTERS const *exception_pointers, s_exception_information *out_info) // 0x10A86FB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?system_build_exception_information_hook@@YAXPBU_EXCEPTION_POINTERS@@PAUs_exception_information@hades_file_local@@@Z");
	// `anonymous-namespace'::system_build_exception_information_hook
	// s_exception_information *out_info;
	// long count;
	// c_static_sliding_buffer<s_tag_history_entry,4> &tag_history;
	// s_extra_exception_info &extra_info;
		// long i;
	// function call : void (*)(_EXCEPTION_POINTERS const *, s_exception_information *)

	long count = 0;
	c_static_sliding_buffer<s_tag_history_entry,4> &tag_history = perThreadExceptionInfo.tag_history;
	s_extra_exception_info &extra_info = g_extra_exception_info;
	for (long i = tag_history.get_first_index(); i != tag_history.get_last_index(); i++)
	{
		extra_info.tag_history[count++] = tag_history.get_element(i);
	}
	_InterlockedExchange(&g_extra_exception_info.tag_history_count, count);
	((void(*)(_EXCEPTION_POINTERS const *, s_exception_information *))0x51BC10)(exception_pointers, out_info);
}

/* ---------- explicit instantiations */
template long c_static_sliding_buffer<s_tag_history_entry,4>::get_last_index() const;
template s_tag_history_entry c_static_sliding_buffer<s_tag_history_entry,4>::get_element(long) const;
template c_static_sliding_buffer<s_tag_history_entry,4>::c_static_sliding_buffer();
template long c_static_sliding_buffer<s_tag_history_entry,4>::get_count() const;
template long c_static_sliding_buffer<s_tag_history_entry,4>::get_first_index() const;

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
std::atomic_flag g_gameIsCrashed;
namespace hades_file_local { unsigned __int32 origVirtualAllocAddress; }
namespace hades_file_local { s_extra_exception_info g_extra_exception_info; }
