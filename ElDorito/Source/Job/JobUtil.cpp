/* ---------- headers */

#include "hades/hades.h"

#include "Job/JobDefinitions.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <limits>
#include <ratio>
#include <stop_token>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

struct SJobCounter;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Job
{
	extern void WaitForCounter(SJobCounter const *counter);
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Job
{
	void WaitForCounter(SJobCounter const *counter) // 0x1086D2A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?WaitForCounter@Job@@YAXPBUSJobCounter@@@Z");

		while (counter->GetValue())
		{
			std::this_thread::yield();
		}
	}
}

/* ---------- private code */
