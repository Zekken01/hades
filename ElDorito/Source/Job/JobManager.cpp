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

void CJobManager::Initialize() // 0x1086A130
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Initialize@CJobManager@@QAEXXZ");

	__int32 const kNumberOfWorkerThreads = 4;
	for (__int32 i = 0; i < kNumberOfWorkerThreads; i++)
	{
		m_workerThreads.push_back(std::thread([this]() { WorkerThreadProc(); }));
	}
}

void CJobManager::Dispose() // 0x10869F80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Dispose@CJobManager@@QAEXXZ");

	std::unique_lock<std::mutex> lock(m_mutex);
	m_disposing = true;
	m_emptyCondition.notify_all();
	lock.unlock();
	for (std::thread &t : m_workerThreads)
		t.join();
}

void CJobManager::AddNewJob(std::function<enum EJobResult __cdecl(void)> function, __int32 priority, SJobCounter *counter) // 0x10869D00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?AddNewJob@CJobManager@@QAEXV?$function@$$A6A?AW4EJobResult@@XZ@std@@HPAUSJobCounter@@@Z");

	SJob job;
	job.callback = function;
	job.priority = priority;
	job.counter = counter;
	std::unique_lock<std::mutex> lock(m_mutex);
	if (m_disposing)
		return;
	job.id = m_jobId++;
	m_jobs.push(job);
	if (job.counter)
		job.counter->Increment();
	m_jobCounter.Increment();
	lock.unlock();
	m_emptyCondition.notify_all();
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

bool CJobManager::RunJobs() // 0x1086A250
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RunJobs@CJobManager@@QAE_NXZ");

	std::unique_lock<std::mutex> lock(m_mutex);
	m_emptyCondition.wait(lock, [this] { return !m_jobs.empty() || m_disposing; });
	if (m_disposing)
		return false;

	CJobManager::SJob job = m_jobs.top();
	m_jobs.pop();
	lock.unlock();

	EJobResult result = job.callback();
	if (result >= Done)
	{
		if (job.counter)
			job.counter->Decrement();
		m_jobCounter.Decrement();
	}
	else
	{
		lock.lock();
		m_jobs.push(job);
		lock.unlock();
	}
	return true;
}

void CJobManager::WorkerThreadProc() // 0x1086A490
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?WorkerThreadProc@CJobManager@@AAEXXZ");

	while (RunJobs())
	{
		std::this_thread::yield();
	}
}

/* ---------- private code */
