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
	_extern void _sub_1086D2A0(SJobCounter const *);
	void WaitForCounter(SJobCounter const *counter) // 0x1086D2A0
	{
		mangled_x86(MANGLED_TODO, "?WaitForCounter@Job@@YAXPBUSJobCounter@@@Z");
		// SJobCounter const *counter;
		todo("implement");
		_sub_1086D2A0(counter);
	}
}

/* ---------- private code */
