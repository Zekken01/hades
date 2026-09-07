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
		_inline SJob(); /* compiler_generated() */
		_inline ~SJob(); /* compiler_generated() */
		_inline SJob &operator=(SJob &&__that); /* compiler_generated() */
		SJob &operator=(SJob const &); /* compiler_generated() */
		unsigned char __pad0[4]; // 0x34
	};
	static_assert(sizeof(SJob) == 56, "Invalid SJob size");
	public:
	void Initialize();
	void Dispose();
	void AddNewJob(std::function<enum EJobResult __cdecl(void)> function, __int32 priority, SJobCounter *counter);
	bool RunJobs();
private:
	void WorkerThreadProc();
	__int32 m_jobId; // 0x0
	std::priority_queue<SJob,std::vector<SJob,std::allocator<SJob> >,std::less<SJob> > m_jobs; // 0x4
	std::mutex m_mutex; // 0x18
	std::condition_variable m_emptyCondition; // 0x48
	SJobCounter m_jobCounter; // 0x70
	bool m_disposing; // 0x74
	unsigned char __pad0[3]; // 0x75
	std::vector<std::thread,std::allocator<std::thread> > m_workerThreads; // 0x78
public:
	_inline CJobManager(); /* compiler_generated() */
	_inline ~CJobManager(); /* compiler_generated() */
};
static_assert(sizeof(CJobManager) == 136, "Invalid CJobManager size");

/* ---------- prototypes */

extern _inline bool operator<(CJobManager::SJob const &a, CJobManager::SJob const &b);

/* ---------- globals */

/* ---------- public code */

_extern bool _sub_10869990(CJobManager::SJob const &, CJobManager::SJob const &);
_inline bool operator<(CJobManager::SJob const &a, CJobManager::SJob const &b) // 0x10869990
{
	mangled_x86(MANGLED_TODO, "??M@YA_NABUSJob@CJobManager@@0@Z");
	// CJobManager::SJob const &b;
	todo("implement");
	bool __result = _sub_10869990(a, b);
	return __result;
}

/* ---------- private code */

#endif // __JOB_JOBMANAGER_HPP__
