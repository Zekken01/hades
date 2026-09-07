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
		bool StartTrace(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
		bool StopTrace();
		void InitializeForNewMap(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
		void RecordSimulationUpdate(s_simulation_update const &);
		void RecordRandomSeed(unsigned __int32);
	private:
		void LogEvent(SRandomEvent const &);
		void LogThreadProc();
		bool m_active; // 0x0
		unsigned char __pad0[3]; // 0x1
		__int32 m_outOfSync; // 0x4
		unsigned __int32 m_currentUpdateNumber; // 0x8
		__int32 m_callCounter; // 0xC
		std::basic_ofstream<char,std::char_traits<char> > m_file; // 0x10
		std::mutex m_mutex; // 0xC0
		std::condition_variable m_logThreadWakeEvent; // 0xF0
		std::vector<SRandomEvent,std::allocator<SRandomEvent> > m_queue; // 0x118
		std::unordered_map<HINSTANCE__ *,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::hash<HINSTANCE__ *>,std::equal_to<HINSTANCE__ *>,std::allocator<std::pair<HINSTANCE__ * const,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > m_moduleNames; // 0x128
		std::thread m_thread; // 0x150
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > m_currentMapName; // 0x158
		char m_logLineBuffer[16384]; // 0x174
	public:
		CDebugRandomTraceManager(); /* compiler_generated() */
		~CDebugRandomTraceManager(); /* compiler_generated() */
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

namespace Patches
{
	namespace DeterminismDebug
	{
		extern void ApplyAll();
		extern bool StartRandomTrace(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &filePath);
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
		_extern void _sub_107A32D0();
		void ApplyAll() // 0x107A32D0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@DeterminismDebug@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_107A32D0();
		}

		_extern bool _sub_107A4390(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
		bool StartRandomTrace(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &filePath) // 0x107A4390
		{
			mangled_x86(MANGLED_TODO, "?StartRandomTrace@DeterminismDebug@Patches@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &filePath;
			todo("implement");
			bool __result = _sub_107A4390(filePath);
			return __result;
		}

		_extern bool _sub_107A4590();
		bool StopRandomTrace() // 0x107A4590
		{
			mangled_x86(MANGLED_TODO, "?StopRandomTrace@DeterminismDebug@Patches@@YA_NXZ");
			// procedure flags: nofpo
			todo("implement");
			bool __result = _sub_107A4590();
			return __result;
		}
	}
}

/* ---------- private code */

_extern bool _sub_107A43F0(CDebugRandomTraceManager *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
_inline bool CDebugRandomTraceManager::StartTrace(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &filePath) // 0x107A43F0
{
	// `anonymous-namespace'::CDebugRandomTraceManager::StartTrace
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &filePath;
	todo("implement");
	bool __result = _sub_107A43F0(this, filePath);
	return __result;
}

_extern bool _sub_107A45E0(CDebugRandomTraceManager *const);
_inline bool CDebugRandomTraceManager::StopTrace() // 0x107A45E0
{
	// `anonymous-namespace'::CDebugRandomTraceManager::StopTrace
	// static ...; // 0x107A4738
	// static ...; // 0x107A472C
	// static ...; // 0x107A4724
	// CDebugRandomTraceManager *const this;
	// std::unique_lock<std::mutex> lock;
	todo("implement");
	bool __result = _sub_107A45E0(this);
	return __result;
}

_extern void _sub_107A3560(CDebugRandomTraceManager *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
_inline void CDebugRandomTraceManager::InitializeForNewMap(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &mapPath) // 0x107A3560
{
	// `anonymous-namespace'::CDebugRandomTraceManager::InitializeForNewMap
	// static ...; // 0x107A3694
	// static ...; // 0x107A368C
	// CDebugRandomTraceManager *const this;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &mapPath;
	// __int32 lastPathSeparator;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > name;
	todo("implement");
	_sub_107A3560(this, mapPath);
}

_extern void _sub_107A4280(CDebugRandomTraceManager *const, s_simulation_update const &);
_inline void CDebugRandomTraceManager::RecordSimulationUpdate(s_simulation_update const &update) // 0x107A4280
{
	// `anonymous-namespace'::CDebugRandomTraceManager::RecordSimulationUpdate
	// s_simulation_update const &update;
	// unsigned long verifySeed;
	// unsigned long time;
	// unsigned long verifyTime;
	// unsigned long seed;
	// function call : long (*const)()
	todo("implement");
	_sub_107A4280(this, update);
}

_extern void _sub_107A4040(CDebugRandomTraceManager *const, unsigned __int32);
_inline void CDebugRandomTraceManager::RecordRandomSeed(unsigned __int32 seed) // 0x107A4040
{
	// `anonymous-namespace'::CDebugRandomTraceManager::RecordRandomSeed
	// static ...; // 0x107A41F8
	// static ...; // 0x107A41E0
	// static ...; // 0x107A41D8
	// CDebugRandomTraceManager *const this;
	// unsigned __int32 seed;
	// CDebugRandomTraceManager::SRandomEvent event;
	{
		// std::scoped_lock<std::mutex> lock;
	}
	// function call : unsigned short (unsigned long, unsigned long, void **, unsigned long *)
	// function call : long (*const)()
	todo("implement");
	_sub_107A4040(this, seed);
}

_extern void _sub_107A3850(CDebugRandomTraceManager *const, CDebugRandomTraceManager::SRandomEvent const &);
_inline void CDebugRandomTraceManager::LogEvent(CDebugRandomTraceManager::SRandomEvent const &e) // 0x107A3850
{
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
	{
		// __int32 i;
		{
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > moduleName;
			{
				// HINSTANCE__ *hModule;
				{
					// unsigned __int32 relativeAddress;
					{
						// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<HINSTANCE__ * const,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > > it;
						{
							// std::basic_string<char,std::char_traits<char>,std::allocator<char> > name;
						}
					}
				}
			}
		}
	}
	// function call : __int32 (unsigned long, char const *, HINSTANCE__ **)
	// function call : unsigned long (HINSTANCE__ *, char *, unsigned long)
	todo("implement");
	_sub_107A3850(this, e);
}

_extern void _sub_107A3E20(CDebugRandomTraceManager *const);
_inline void CDebugRandomTraceManager::LogThreadProc() // 0x107A3E20
{
	// `anonymous-namespace'::CDebugRandomTraceManager::LogThreadProc
	// static ...; // 0x107A3FC6
	// static ...; // 0x107A3FC0
	// static ...; // 0x107A3FA8
	// static ...; // 0x107A3FA0
	// CDebugRandomTraceManager *const this;
	{
		// std::unique_lock<std::mutex> lock;
		// std::vector<CDebugRandomTraceManager::SRandomEvent,std::allocator<CDebugRandomTraceManager::SRandomEvent> > queue;
		{
			// std::vector<CDebugRandomTraceManager::SRandomEvent,std::allocator<CDebugRandomTraceManager::SRandomEvent> > &<range>$L0;
			// CDebugRandomTraceManager::SRandomEvent *<begin>$L0;
			// CDebugRandomTraceManager::SRandomEvent *<end>$L0;
			{
				// CDebugRandomTraceManager::SRandomEvent const &e;
			}
		}
	}
	todo("implement");
	_sub_107A3E20(this);
}

_extern void _sub_107A7F10(s_simulation_update *);
void simulation_record_update_hook(s_simulation_update *update) // 0x107A7F10
{
	// `anonymous-namespace'::simulation_record_update_hook
	// s_simulation_update *update;
	todo("implement");
	_sub_107A7F10(update);
}

_extern unsigned long *_sub_107A7850();
unsigned long *get_random_seed_address_hook() // 0x107A7850
{
	// `anonymous-namespace'::get_random_seed_address_hook
	// procedure flags: nofpo
	// unsigned long *seed_address;
	todo("implement");
	unsigned long * __result = _sub_107A7850();
	return __result;
}

extern CDebugRandomTraceManager* _sub_107A1F50(CDebugRandomTraceManager *const);
_inline CDebugRandomTraceManager::CDebugRandomTraceManager() // 0x107A1F50
{
	// `anonymous-namespace'::CDebugRandomTraceManager::CDebugRandomTraceManager
	// CDebugRandomTraceManager *const this;
	compiler_generated();
	todo("implement");
	_sub_107A1F50(this);
}

extern CDebugRandomTraceManager::SRandomEvent* _sub_107A20A0(CDebugRandomTraceManager::SRandomEvent *const);
_inline CDebugRandomTraceManager::SRandomEvent::SRandomEvent() // 0x107A20A0
{
	// `anonymous-namespace'::CDebugRandomTraceManager::SRandomEvent::SRandomEvent
	// CDebugRandomTraceManager::SRandomEvent *const this;
	compiler_generated();
	todo("implement");
	_sub_107A20A0(this);
}
