/* ---------- headers */

#include "Job/JobManager.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/SelectionRenderer.hpp"
#include "Job/JobDefinitions.hpp"

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
#include <memory>
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
struct begin;
struct end;
struct lambda_1;

/* ---------- constants */

/* ---------- definitions */

//class CJobManager::Initialize::__l4::<lambda_1>
//{
//public:
//	void operator()() const;
//	<lambda_1>(CJobManager::Initialize::__l4::<lambda_1> &);
//	<lambda_1>(CJobManager *);
//private:
//	CJobManager *__this; // 0x0
//public:
//	CJobManager::Initialize::__l4::<lambda_1> &operator=(CJobManager::Initialize::__l4::<lambda_1> const &);
//};
//static_assert(sizeof(CJobManager::Initialize::__l4::<lambda_1>) == 4, "Invalid CJobManager::Initialize::__l4::<lambda_1> size");

//class CJobManager::RunJobs::__l2::<lambda_1>
//{
//public:
//	bool operator()() const;
//	<lambda_1>(CJobManager::RunJobs::__l2::<lambda_1> &);
//	<lambda_1>(CJobManager *);
//private:
//	CJobManager *__this; // 0x0
//public:
//	CJobManager::RunJobs::__l2::<lambda_1> &operator=(CJobManager::RunJobs::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(CJobManager::RunJobs::__l2::<lambda_1>) == 4, "Invalid CJobManager::RunJobs::__l2::<lambda_1> size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_1086A130(CJobManager *const);
void CJobManager::Initialize() // 0x1086A130
{
	mangled_x86(MANGLED_TODO, "?Initialize@CJobManager@@QAEXXZ");
	// CJobManager *const this;
	// __int32 const kNumberOfWorkerThreads;
	{
		// __int32 i;
		{
		}
	}
	todo("implement");
	_sub_1086A130(this);
}

_extern void _sub_10869F80(CJobManager *const);
void CJobManager::Dispose() // 0x10869F80
{
	mangled_x86(MANGLED_TODO, "?Dispose@CJobManager@@QAEXXZ");
	// static ...; // 0x1086A084
	// static ...; // 0x1086A078
	// static ...; // 0x1086A070
	// CJobManager *const this;
	// std::unique_lock<std::mutex> lock;
	{
		// std::vector<std::thread> &<range>$L0;
		// std::thread *<begin>$L0;
		// std::thread *<end>$L0;
		{
			// std::thread &t;
		}
	}
	todo("implement");
	_sub_10869F80(this);
}

_extern void _sub_10869D00(CJobManager *const, std::function<enum EJobResult __cdecl(void)>, __int32, SJobCounter *);
void CJobManager::AddNewJob(std::function<enum EJobResult __cdecl(void)> function, __int32 priority, SJobCounter *counter) // 0x10869D00
{
	mangled_x86(MANGLED_TODO, "?AddNewJob@CJobManager@@QAEXV?$function@$$A6A?AW4EJobResult@@XZ@std@@HPAUSJobCounter@@@Z");
	// static ...; // 0x10869E84
	// CJobManager *const this;
	// std::function<enum EJobResult __cdecl(void)> function;
	// __int32 priority;
	// SJobCounter *counter;
	// CJobManager::SJob job;
	// std::unique_lock<std::mutex> lock;
	todo("implement");
	_sub_10869D00(this, function, priority, counter);
}

// mangled_x86(MANGLED_DEFAULT, "??0SJob@CJobManager@@QAE@$$QAU01@@Z"); no body to assert in
_inline CJobManager::SJob::SJob(CJobManager::SJob &&__that) = default; // 0x108692E0

// mangled_x86(MANGLED_DEFAULT, "??0SJob@CJobManager@@QAE@ABU01@@Z"); no body to assert in
_inline CJobManager::SJob::SJob(CJobManager::SJob const &__that) = default; // 0x10869380

// mangled_x86(MANGLED_DEFAULT, "??0SJob@CJobManager@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??1SJob@CJobManager@@QAE@XZ"); no body to assert in
_inline CJobManager::SJob::~SJob() = default; // 0x10869750

// mangled_x86(MANGLED_DEFAULT, "??4SJob@CJobManager@@QAEAAU01@$$QAU01@@Z"); no body to assert in
_inline CJobManager::SJob &CJobManager::SJob::operator=(CJobManager::SJob &&__that) = default; // 0x108698D0

_extern bool _sub_1086A250(CJobManager *const);
bool CJobManager::RunJobs() // 0x1086A250
{
	mangled_x86(MANGLED_TODO, "?RunJobs@CJobManager@@QAE_NXZ");
	// static ...; // 0x1086A40C
	// static ...; // 0x1086A408
	// static ...; // 0x1086A3F0
	// static ...; // 0x1086A3E8
	// CJobManager *const this;
	// std::unique_lock<std::mutex> lock;
	// CJobManager::SJob job;
	// EJobResult result;
	todo("implement");
	bool __result = _sub_1086A250(this);
	return __result;
}

void CJobManager::WorkerThreadProc() // 0x1086A490
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?WorkerThreadProc@CJobManager@@AAEXXZ");
	// CJobManager *const this;

	while (RunJobs())
	{
		std::this_thread::yield();
	}
}

/* ---------- private code */
