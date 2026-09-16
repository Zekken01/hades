/* ---------- headers */

#include "Utils/Logger.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Modules/ModuleGame.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/WebSocket.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <optional>
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
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
namespace Modules
{
	class ModuleGame;
}
namespace Utils
{
	struct LogEntry;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Utils
{
	extern std::string LogLevelToString(Utils::LogLevel level);
	extern std::string LogTypesToString(Utils::LogTypes types);
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern std::string _sub_10C5A850(Utils::LogLevel);
namespace Utils
{
	std::string LogLevelToString(Utils::LogLevel level) // 0x10C5A850
	{
		mangled_x86(MANGLED_TODO, "?LogLevelToString@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@W4LogLevel@1@@Z");
		// static ...; // 0x10C5A978
	// $LN8:
	// $LN7:
	// $LN6:
	// $LN5:
	// $LN4:
		// Utils::LogLevel level;
		todo("implement");
		std::string __result = _sub_10C5A850(level);
		return __result;
	}
}

extern std::string _sub_10C5A9E0(Utils::LogTypes);
namespace Utils
{
	std::string LogTypesToString(Utils::LogTypes types) // 0x10C5A9E0
	{
		mangled_x86(MANGLED_TODO, "?LogTypesToString@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@W4LogTypes@1@@Z");
		// static ...; // 0x10C5AEE7
		// static ...; // 0x10C5AEE4
		// static ...; // 0x10C5AECC
		// static ...; // 0x10C5AEC4
		// Utils::LogTypes types;
		{
			// std::stringstream ss;
			// std::vector<std::string> bits;
			{
				// __int32 bit;
			}
			{
				// unsigned __int32 i;
			}
		}
		todo("implement");
		std::string __result = _sub_10C5A9E0(types);
		return __result;
	}

	// mangled_x86(MANGLED_DEFAULT, "??0LogEntry@Utils@@QAE@XZ"); no body to assert in

	_extern unsigned long _sub_10C5A5E0(void *);
	unsigned long __stdcall Logger::Flusher(void *lpParam) // 0x10C5A5E0
	{
		mangled_x86(MANGLED_TODO, "?Flusher@Logger@Utils@@CGKPAX@Z");
		// void *lpParam;
		todo("implement");
		unsigned long __result = _sub_10C5A5E0(lpParam);
		return __result;
	}

	extern Logger* _sub_10C59920(Utils::Logger *const);
	Logger::Logger() // 0x10C59920
	{
		mangled_x86(MANGLED_TODO, "??0Logger@Utils@@QAE@XZ");
		// Utils::Logger *const this;
		// function call : void *(_SECURITY_ATTRIBUTES *, unsigned long, unsigned long (*)(void *), void *, unsigned long, unsigned long *)
		todo("implement");
		_sub_10C59920(this);
	}

	_extern void _sub_10C59E20(Utils::Logger *const);
	void Logger::Flush() // 0x10C59E20
	{
		mangled_x86(MANGLED_TODO, "?Flush@Logger@Utils@@QAEXXZ");
		// static ...; // 0x10C5A44B
		// static ...; // 0x10C5A43F
		// static ...; // 0x10C5A42F
		// static ...; // 0x10C5A427
		// static ...; // 0x10C5A421
		// static ...; // 0x10C5A419
		// static ...; // 0x10C5A412
		// static ...; // 0x10C5A40B
		// static ...; // 0x10C5A409
		// static ...; // 0x10C5A3FC
		// static ...; // 0x10C5A384
		// static ...; // 0x10C5A37C
	// closefile:
		// Utils::Logger *const this;
		// std::filesystem::path parentDirectory;
		// std::lock_guard<std::mutex> lock;
		// Modules::ModuleGame &gameModule;
		// std::ofstream outfile;
		// std::filesystem::path logFilePath;
		// Utils::LogEntry entry;
		{
			// long long t;
			// tm ourLocalTime;
			// std::string message;
			{
				// std::vector<std::string> &<range>$L0;
				// std::string *<begin>$L0;
				// std::string *<end>$L0;
				{
					// std::string filter;
				}
			}
			{
				// std::string *<end>$L1;
				// std::string *<begin>$L1;
				// std::vector<std::string> &<range>$L1;
				{
				}
			}
		}
		todo("implement");
		_sub_10C59E20(this);
	}
}

/* ---------- private code */
