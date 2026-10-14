/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/SelectionRenderer.hpp"
#include "Job/JobDefinitions.hpp"
#include "Job/JobManager.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <condition_variable>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <limits>
#include <mutex>
#include <queue>
#include <ratio>
#include <stdexcept>
#include <stop_token>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class CJobManager;
struct SJobCounter;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Job
{
	extern void RunJob(std::function<enum EJobResult __cdecl(void)> function, SJobCounter *counter, __int32 priority);
	extern void Initialize();
	extern void Dispose();
}

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	CJobManager jobManager; // 0x123AEE68  // hades: defined, so its dynamic initializer emits the constructor
	extern bool initialized; // 0x123AEEF0
}
using namespace hades_file_local;
/* ---------- public code */

namespace Job
{
	void RunJob(std::function<enum EJobResult __cdecl(void)> function, SJobCounter *counter, __int32 priority) // 0x1086CEA0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?RunJob@Job@@YAXV?$function@$$A6A?AW4EJobResult@@XZ@std@@PAUSJobCounter@@H@Z");
		// __int32 priority;

		#line 72 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Job\\JobSystem.cpp"
		assert(initialized);
		#line 78 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Job\\JobSystem.cpp"
		jobManager.AddNewJob(function, priority, counter);
	}

	void Initialize() // 0x1086CE50
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Initialize@Job@@YAXXZ");
		// procedure flags: nofpo

		initialized = true;
		jobManager.Initialize();
	}

	void Dispose() // 0x1086CE00
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Dispose@Job@@YAXXZ");
		// procedure flags: nofpo

			jobManager.Dispose();
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0CJobManager@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0SJobCounter@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??1CJobManager@@QAE@XZ"); no body to assert in
_inline CJobManager::~CJobManager() = default; // 0x1086CD80

/* ---------- private code */
