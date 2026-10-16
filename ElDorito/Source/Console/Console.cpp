/* ---------- headers */

#include "Console/Console.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Patches/CustomPackets.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include "Utils/Logger.hpp"  // hades: added for 0x10950B80

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
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <ios>
#include <iosfwd>
#include <limits>
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
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
namespace Console
{
	class ConsoleOutputHandler;
}
namespace hades_file_local
{
	class LogConsoleOutputHandler;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Console {}
using namespace ::Console;

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	class LogConsoleOutputHandler :
		public Console::ConsoleOutputHandler
	{
	public:
		virtual void WriteLine(std::string const &);
		LogConsoleOutputHandler(LogConsoleOutputHandler &); /* compiler_generated() */
		LogConsoleOutputHandler(LogConsoleOutputHandler const &); /* compiler_generated() */
		LogConsoleOutputHandler() = default; /* compiler_generated() */  // hades: not user-provided, so make_shared value-initializes
		virtual ~LogConsoleOutputHandler() = default; /* compiler_generated() */
		LogConsoleOutputHandler &operator=(LogConsoleOutputHandler &); /* compiler_generated() */
		LogConsoleOutputHandler &operator=(LogConsoleOutputHandler const &); /* compiler_generated() */
	};
	static_assert(sizeof(LogConsoleOutputHandler) == 4, "Invalid LogConsoleOutputHandler size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Console
{
	extern void Init();
	extern void WriteLine(std::string const &line);
	extern void RegisterHandler(std::shared_ptr<Console::ConsoleOutputHandler> handler);
}

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern std::vector<std::shared_ptr<Console::ConsoleOutputHandler> > Handlers; // 0x1240DA2C
}
using namespace hades_file_local;
/* ---------- public code */

namespace Console
{
	void Init() // 0x10950840
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Init@Console@@YAXXZ");

		RegisterHandler(std::make_shared<LogConsoleOutputHandler>());
	}

	void WriteLine(std::string const &line) // 0x109509D0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?WriteLine@Console@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

		std::vector<std::string> lines = Utils::String::SplitString(line, '\n');
		for (std::string &lineToPrint : lines)
		{
			for (std::shared_ptr<Console::ConsoleOutputHandler> &handler : Handlers)
				handler->WriteLine(lineToPrint);
		}
	}

	void RegisterHandler(std::shared_ptr<Console::ConsoleOutputHandler> handler) // 0x10950930
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterHandler@Console@@YAXV?$shared_ptr@VConsoleOutputHandler@Console@@@std@@@Z");

		Handlers.push_back(handler);
	}

	// mangled_x86(MANGLED_DEFAULT, "??0ConsoleOutputHandler@Console@@QAE@XZ"); no body to assert in
}

/* ---------- private code */

void LogConsoleOutputHandler::WriteLine(std::string const &line) // 0x10950B80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?WriteLine@LogConsoleOutputHandler@hades_file_local@@UAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

	Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Debug, Utils::LogLevel::Info, "%s", line.c_str());
}

// mangled_x86(MANGLED_DEFAULT, "??0LogConsoleOutputHandler@hades_file_local@@QAE@XZ"); no body to assert in
// _inline LogConsoleOutputHandler::LogConsoleOutputHandler() = default; // 0x10950350  // hades: defaulted on its declaration

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { std::vector<std::shared_ptr<Console::ConsoleOutputHandler> > Handlers; }
