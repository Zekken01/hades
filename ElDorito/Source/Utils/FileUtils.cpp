/* ---------- headers */

#include "hades/hades.h"

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
#include <ios>
#include <limits>
#include <stdexcept>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

namespace Utils {}
using namespace ::Utils;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Utils
{
	namespace FileUtils
	{
		extern long long GetFileSize64(char const *filename);
		extern __int32 GetFileSize(char const *filename);
		extern char const *GetName(char const *filename);
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Utils
{
	namespace FileUtils
	{
		long long GetFileSize64(char const *filename) // 0x10C57CE0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetFileSize64@FileUtils@Utils@@YA_JPBD@Z");
			// static ...; // 0x10C57D94
			// static ...; // 0x10C57D88
			// static ...; // 0x10C57D80
			// char const *filename;
			// _stat64 stat_buf;
			// __int32 rc;

			struct _stat64 fileStat;
			int result = _stat64(filename, &fileStat);

			return result == 0 ? fileStat.st_size : -1;
		}

		__int32 GetFileSize(char const *filename) // 0x10C57DD0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetFileSize@FileUtils@Utils@@YAHPBD@Z");
			// static ...; // 0x10C57E6C
			// static ...; // 0x10C57E60
			// static ...; // 0x10C57E58
			// char const *filename;
			// _stat64i32 stat_buf;
			// __int32 rc;

			struct _stat64i32 stat_buf;
			__int32 rc = _stat64i32(filename, &stat_buf);

			return rc == 0 ? stat_buf.st_size : -1;
		}
	}
}

extern char const *_sub_10C57EA0(char const *);
namespace Utils
{
	namespace FileUtils
	{
		char const *GetName(char const *filename) // 0x10C57EA0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetName@FileUtils@Utils@@YAPBDPBD@Z");
			// char const *filename;
			// char const *name;

			char const *lastSlash = strrchr(filename, '\\');
			return lastSlash ? lastSlash + 1 : filename;
		}
	}
}

/* ---------- private code */
