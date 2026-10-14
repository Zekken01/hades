/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/tls.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Reforge.hpp"
#include "mods/mod_package_updater.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Pointer.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include "Patches/Core.hpp"  // hades: added for 0x107A32D0

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <condition_variable>
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
#include <list>
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
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
struct lambda_1;
struct lambda_2;
struct s_simulation_update;
namespace hades_file_local
{
	class CDebugRandomTraceManager;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace DeterminismDebug {}
	using namespace Patches::DeterminismDebug;
	namespace Core {}
	using namespace Patches::Core;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{

	//@@anonymous-namespace@@
	class CDebugRandomTraceManager :
		public Utils::Singleton<CDebugRandomTraceManager>
	{
	public:
		public:
		struct SRandomEvent
		{
			__int32 updateNumber; // 0x0
			unsigned __int32 randomSeed; // 0x4
			unsigned __int32 time; // 0x8
			__int32 callNum; // 0xC
			__int32 outOfSync; // 0x10
			void *stackFrames[6]; // 0x14
			__int32 numStackFrames; // 0x2C
			char mapName[64]; // 0x30
			SRandomEvent(); /* compiler_generated() */
		};
		static_assert(sizeof(SRandomEvent) == 112, "Invalid SRandomEvent size");
		public:
		bool StartTrace(std::string const &);
		bool StopTrace();
		void InitializeForNewMap(std::string const &);
		void RecordSimulationUpdate(s_simulation_update const &);
		void RecordRandomSeed(unsigned __int32);
	private:
		void LogEvent(SRandomEvent const &);
		void LogThreadProc();
		bool m_active = false; // 0x0
		unsigned char __pad0[3]; // 0x1
		__int32 m_outOfSync = 0; // 0x4
		unsigned __int32 m_currentUpdateNumber = 0xFFFFFFFF; // 0x8
		__int32 m_callCounter = -1; // 0xC
		std::ofstream m_file; // 0x10
		std::mutex m_mutex; // 0xC0
		std::condition_variable m_logThreadWakeEvent; // 0xF0
		std::vector<SRandomEvent> m_queue; // 0x118
		std::unordered_map<HINSTANCE__ *,std::string> m_moduleNames; // 0x128
		std::thread m_thread; // 0x150
		std::string m_currentMapName; // 0x158
		char m_logLineBuffer[16384]; // 0x174
	public:
		CDebugRandomTraceManager() = default; /* compiler_generated() */
		~CDebugRandomTraceManager() = default; /* compiler_generated() */
	unsigned char __pad1[4]; // 0x4174
	};
	static_assert(sizeof(CDebugRandomTraceManager) == 16760, "Invalid CDebugRandomTraceManager size");

}
using namespace hades_file_local;
//class Patches::DeterminismDebug::ApplyAll::__l2::<lambda_1>
//{
//public:
//	void operator()() const;
//};
//static_assert(sizeof(Patches::DeterminismDebug::ApplyAll::__l2::<lambda_1>) == 1, "Invalid Patches::DeterminismDebug::ApplyAll::__l2::<lambda_1> size");

//class Patches::DeterminismDebug::ApplyAll::__l2::<lambda_2>
//{
//public:
//	void operator()(char const *) const;
//};
//static_assert(sizeof(Patches::DeterminismDebug::ApplyAll::__l2::<lambda_2>) == 1, "Invalid Patches::DeterminismDebug::ApplyAll::__l2::<lambda_2> size");

/* ---------- prototypes */

extern long (*const game_time_get)(); // 0x11248DA8  // hades: added for 0X107A4280

namespace Patches
{
	namespace DeterminismDebug
	{
		extern void ApplyAll();
		extern bool StartRandomTrace(std::string const &filePath);
		extern bool StopRandomTrace();
	}
}

void simulation_record_update_hook(s_simulation_update *update);
unsigned long *get_random_seed_address_hook();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace DeterminismDebug
	{
		void ApplyAll() // 0x107A32D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@DeterminismDebug@Patches@@YAXXZ");
			// procedure flags: nofpo

			Patches::Core::OnShutdown([]()
			{
				CDebugRandomTraceManager::Instance().StopTrace();
			});
			Patches::Core::OnMapLoaded([](char const *mapPath)
			{
				CDebugRandomTraceManager::Instance().InitializeForNewMap(mapPath);
			});
			Hook(0x41F90, simulation_record_update_hook).Apply();
			Hook(0x11F000, get_random_seed_address_hook).Apply();
		}

		bool StartRandomTrace(std::string const &filePath) // 0x107A4390
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?StartRandomTrace@DeterminismDebug@Patches@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// std::string const &filePath;

			return Utils::Singleton<CDebugRandomTraceManager>::Instance().StartTrace(filePath);
		}

		bool StopRandomTrace() // 0x107A4590
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?StopRandomTrace@DeterminismDebug@Patches@@YA_NXZ");
			// procedure flags: nofpo

			return CDebugRandomTraceManager::Instance().StopTrace();
		}
	}
}

/* ---------- private code */

_inline bool CDebugRandomTraceManager::StartTrace(std::string const &filePath) // 0x107A43F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?StartTrace@CDebugRandomTraceManager@hades_file_local@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::CDebugRandomTraceManager::StartTrace
	// std::string const &filePath;

	StopTrace();
	m_file = std::ofstream(filePath);
	if (!m_file.is_open())
		return false;
	m_active = true;
	m_moduleNames.clear();
	m_thread = std::thread(std::bind_front(&CDebugRandomTraceManager::LogThreadProc, this));
	return true;
}

_inline bool CDebugRandomTraceManager::StopTrace() // 0x107A45E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?StopTrace@CDebugRandomTraceManager@hades_file_local@@QAE_NXZ");
	// `anonymous-namespace'::CDebugRandomTraceManager::StopTrace
	// static ...; // 0x107A4738
	// static ...; // 0x107A472C
	// static ...; // 0x107A4724
	// CDebugRandomTraceManager *const this;
	// std::unique_lock<std::mutex> lock;

	std::unique_lock<std::mutex> lock(m_mutex);
	if (!m_active)
		return true;

	m_active = false;
	lock.unlock();
	m_logThreadWakeEvent.notify_one();
	if (m_thread.joinable())
		m_thread.join();
	m_file = {};
	return true;
}

_inline void CDebugRandomTraceManager::InitializeForNewMap(std::string const &mapPath) // 0x107A3560
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?InitializeForNewMap@CDebugRandomTraceManager@hades_file_local@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::CDebugRandomTraceManager::InitializeForNewMap
	// static ...; // 0x107A3694
	// static ...; // 0x107A368C
	// CDebugRandomTraceManager *const this;
	// std::string const &mapPath;
	// __int32 lastPathSeparator;
	// std::string name;

	std::string name;
	__int32 lastPathSeparator = mapPath.find_last_of("\\");
	if (lastPathSeparator != -1)
		name = mapPath.substr(lastPathSeparator + 1);
	else
		name = mapPath;

	m_outOfSync = 0;
	m_currentUpdateNumber = -1;
	m_currentMapName = name;
	m_callCounter = 0;
}

_inline void CDebugRandomTraceManager::RecordSimulationUpdate(s_simulation_update const &update) // 0x107A4280
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RecordSimulationUpdate@CDebugRandomTraceManager@hades_file_local@@QAEXABUs_simulation_update@@@Z");
	// `anonymous-namespace'::CDebugRandomTraceManager::RecordSimulationUpdate
	// s_simulation_update const &update;
	// unsigned long verifySeed;
	// unsigned long time;
	// unsigned long verifyTime;
	// unsigned long seed;
	// function call : long (*const)()

	unsigned long seed = *(unsigned long *)tls_getd().random_math_globals;
	unsigned long time = game_time_get();
	unsigned long verifyTime = *(unsigned long *)offset_pointer(&update, 5616);
	unsigned long verifySeed = *(unsigned long *)offset_pointer(&update, 5620);
	m_callCounter = 0;
	m_outOfSync = 0;
	m_currentUpdateNumber = *(unsigned long *)&update;
	if (verifySeed != seed)
		m_outOfSync |= 1;
	if (verifyTime != time)
		m_outOfSync |= 2;
}

_inline void CDebugRandomTraceManager::RecordRandomSeed(unsigned __int32 seed) // 0x107A4040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RecordRandomSeed@CDebugRandomTraceManager@hades_file_local@@QAEXI@Z");
	// `anonymous-namespace'::CDebugRandomTraceManager::RecordRandomSeed
	// static ...; // 0x107A41F8
	// static ...; // 0x107A41E0
	// static ...; // 0x107A41D8
	// CDebugRandomTraceManager *const this;
	// unsigned __int32 seed;
	// CDebugRandomTraceManager::SRandomEvent event;
		// std::scoped_lock<std::mutex> lock;
	// function call : unsigned short (unsigned long, unsigned long, void **, unsigned long *)
	// function call : long (*const)()

	if (!m_active || m_currentUpdateNumber == -1)
		return;
	SRandomEvent event;
	event.updateNumber = m_currentUpdateNumber;
	event.randomSeed = seed;
	event.numStackFrames = RtlCaptureStackBackTrace(2, 6, event.stackFrames, nullptr);
	event.outOfSync = m_outOfSync;
	event.time = game_time_get();
	event.callNum = m_callCounter++;
	strncpy_s(event.mapName, m_currentMapName.c_str(), sizeof(event.mapName) - 1);
	{
		std::scoped_lock<std::mutex> lock(m_mutex);
		m_queue.push_back(event);
	}
	m_logThreadWakeEvent.notify_one();
}

_inline void CDebugRandomTraceManager::LogEvent(CDebugRandomTraceManager::SRandomEvent const &e) // 0x107A3850
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LogEvent@CDebugRandomTraceManager@hades_file_local@@AAEXABUSRandomEvent@12@@Z");
	// `anonymous-namespace'::CDebugRandomTraceManager::LogEvent
	// static ...; // 0x107A3CE0
	// static ...; // 0x107A3CD8
	// static ...; // 0x107A3CD5
	// static ...; // 0x107A3CD0
	// static ...; // 0x107A3C94
	// static ...; // 0x107A3C8C
	// CDebugRandomTraceManager *const this;
	// CDebugRandomTraceManager::SRandomEvent const &e;
	// char stackBuffer[8192];
	// __int32 stackLen;
	// __int32 len;
		// __int32 i;
			// std::string moduleName;
				// HINSTANCE__ *hModule;
					// unsigned __int32 relativeAddress;
						// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<HINSTANCE__ * const,std::string> > > > it;
							// std::string name;
	// function call : __int32 (unsigned long, char const *, HINSTANCE__ **)
	// function call : unsigned long (HINSTANCE__ *, char *, unsigned long)

	char stackBuffer[8192];
	__int32 stackLen = 0;
	for (__int32 i = 0; i < e.numStackFrames; i++)
	{
		std::string moduleName;
		HMODULE hModule;
		if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)e.stackFrames[i], &hModule) && hModule)
		{
			if (auto it = m_moduleNames.find(hModule); it == m_moduleNames.end())
			{
				std::string name;
				name.resize(MAX_PATH + 1);
				GetModuleFileNameA(hModule, name.data(), name.length() - 1);
				name = name.substr(name.find_last_of('\\') + 1);
				m_moduleNames.insert({ hModule, name });
				moduleName = name;
			}
			else
			{
				moduleName = it->second;
			}
			unsigned __int32 relativeAddress = (unsigned __int32)e.stackFrames[i] - (unsigned __int32)hModule;
			stackLen += sprintf(&stackBuffer[stackLen], "%s+%X%s", moduleName.empty() ? "unknown" : moduleName.c_str(), relativeAddress, i < e.numStackFrames - 1 ? " -> " : "");
		}
	}
	__int32 len = sprintf_s(m_logLineBuffer, "map: %s, time: %u, update: %u, desync: %d, call: %d, seed: %u, stack: %s\n", e.mapName, e.time, e.updateNumber, e.outOfSync, e.callNum, e.randomSeed, stackBuffer);
	m_file.write(m_logLineBuffer, len);
}

_inline void CDebugRandomTraceManager::LogThreadProc() // 0x107A3E20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LogThreadProc@CDebugRandomTraceManager@hades_file_local@@AAEXXZ");
	// `anonymous-namespace'::CDebugRandomTraceManager::LogThreadProc
	// static ...; // 0x107A3FC6
	// static ...; // 0x107A3FC0
	// static ...; // 0x107A3FA8
	// static ...; // 0x107A3FA0
	// CDebugRandomTraceManager *const this;
		// std::unique_lock<std::mutex> lock;
		// std::vector<CDebugRandomTraceManager::SRandomEvent> queue;
			// std::vector<CDebugRandomTraceManager::SRandomEvent> &<range>$L0;
			// CDebugRandomTraceManager::SRandomEvent *<begin>$L0;
			// CDebugRandomTraceManager::SRandomEvent *<end>$L0;
				// CDebugRandomTraceManager::SRandomEvent const &e;

	for (;;)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_logThreadWakeEvent.wait_for(lock, std::chrono::milliseconds(1000));
		std::vector<SRandomEvent> queue = std::move(m_queue);
		lock.unlock();
		for (auto const &e : queue)
			LogEvent(e);
		m_file.flush();
		if (!m_active)
			break;
	}
}

void simulation_record_update_hook(s_simulation_update *update) // 0x107A7F10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?simulation_record_update_hook@@YAXPAUs_simulation_update@@@Z");
	// `anonymous-namespace'::simulation_record_update_hook
	// s_simulation_update *update;

	Utils::Singleton<CDebugRandomTraceManager>::Instance().RecordSimulationUpdate(*update);
}

unsigned long *get_random_seed_address_hook() // 0x107A7850
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_random_seed_address_hook@@YAPAKXZ");
	// `anonymous-namespace'::get_random_seed_address_hook
	// procedure flags: nofpo
	// unsigned long *seed_address;

	unsigned long *seed_address = (unsigned long *)tls_getd().random_math_globals;
	CDebugRandomTraceManager::Instance().RecordRandomSeed(*seed_address);
	return seed_address;
}

// mangled_x86(MANGLED_DEFAULT, "??0CDebugRandomTraceManager@hades_file_local@@QAE@XZ"); no body to assert in
// hades: CDebugRandomTraceManager::CDebugRandomTraceManager() is defaulted in the class (implicit, so `new T()` zero-fills first) // 0x107A1F50

// mangled_x86(MANGLED_DEFAULT, "??0SRandomEvent@CDebugRandomTraceManager@hades_file_local@@QAE@XZ"); no body to assert in
_inline CDebugRandomTraceManager::SRandomEvent::SRandomEvent() // 0x107A20A0
{
	numStackFrames = 0;
}
