/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/tls.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Reforge.hpp"
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

struct lambda_1;
struct lambda_2;
struct s_simulation_update;
namespace
{
	class CDebugRandomTraceManager;
}

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

namespace
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
