#ifndef __JOB_JOBMANAGER_HPP__
#define __JOB_JOBMANAGER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/SelectionRenderer.hpp"
#include "Job/JobDefinitions.hpp"

#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

/* ---------- forward declarations */

class CJobManager;
struct SJobCounter;

/* ---------- constants */

/* ---------- definitions */

class CJobManager
{
public:
	public:
	struct SJob
	{
		__int32 id; // 0x0
		__int32 priority; // 0x4
		std::function<enum EJobResult __cdecl(void)> callback; // 0x8
		SJobCounter *counter; // 0x30
		_inline SJob(SJob &&__that); /* compiler_generated() */
		_inline SJob(SJob const &__that); /* compiler_generated() */
		_inline SJob() = default; /* compiler_generated() */
		_inline ~SJob(); /* compiler_generated() */
		_inline SJob &operator=(SJob &&__that); /* compiler_generated() */
		SJob &operator=(SJob const &); /* compiler_generated() */
	};
	static_assert(sizeof(SJob) == 56, "Invalid SJob size");
	public:
	void Initialize();
	void Dispose();
	void AddNewJob(std::function<enum EJobResult __cdecl(void)> function, __int32 priority, SJobCounter *counter);
	bool RunJobs();
private:
	void WorkerThreadProc();
	__int32 m_jobId = 1; // 0x0
	std::priority_queue<SJob> m_jobs; // 0x4
	std::mutex m_mutex; // 0x18
	std::condition_variable m_emptyCondition; // 0x48
	SJobCounter m_jobCounter; // 0x70
	bool m_disposing = false; // 0x74
	unsigned char __pad0[3]; // 0x75
	std::vector<std::thread> m_workerThreads; // 0x78
public:
	_inline CJobManager() = default; /* compiler_generated() */
	_inline ~CJobManager(); /* compiler_generated() */
};
static_assert(sizeof(CJobManager) == 136, "Invalid CJobManager size");

/* ---------- prototypes */

extern _inline bool operator<(CJobManager::SJob const &a, CJobManager::SJob const &b);

/* ---------- globals */

/* ---------- public code */

inline bool operator<(CJobManager::SJob const &a, CJobManager::SJob const &b) // 0x10869990
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??M@YA_NABUSJob@CJobManager@@0@Z");
	// CJobManager::SJob const &b;

	return a.priority < b.priority;
}

/* ---------- private code */

#endif // __JOB_JOBMANAGER_HPP__
