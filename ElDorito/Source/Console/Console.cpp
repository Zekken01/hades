/* ---------- headers */

#include "Console/Console.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Patches/CustomPackets.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

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
		LogConsoleOutputHandler(); /* compiler_generated() */
		virtual ~LogConsoleOutputHandler(); /* compiler_generated() */
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
	_extern void _sub_10950840();
	void Init() // 0x10950840
	{
		mangled_x86(MANGLED_TODO, "?Init@Console@@YAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_10950840();
	}

	_extern void _sub_109509D0(std::string const &);
	void WriteLine(std::string const &line) // 0x109509D0
	{
		mangled_x86(MANGLED_TODO, "?WriteLine@Console@@YAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x10950B24
		// static ...; // 0x10950B18
		// static ...; // 0x10950B10
		// std::string const &line;
		// std::vector<std::string> lines;
		{
			// std::vector<std::string> &<range>$L0;
			// std::string *<begin>$L0;
			// std::string *<end>$L0;
			{
				// std::string &lineToPrint;
				{
					// std::shared_ptr<Console::ConsoleOutputHandler> *<end>$L1;
					// std::shared_ptr<Console::ConsoleOutputHandler> *<begin>$L1;
					// std::vector<std::shared_ptr<Console::ConsoleOutputHandler> > &<range>$L1;
					{
						// std::shared_ptr<Console::ConsoleOutputHandler> &handler;
					}
				}
			}
		}
		// function call : void (std::string const &)
		todo("implement");
		_sub_109509D0(line);
	}

	_extern void _sub_10950930(std::shared_ptr<Console::ConsoleOutputHandler>);
	void RegisterHandler(std::shared_ptr<Console::ConsoleOutputHandler> handler) // 0x10950930
	{
		mangled_x86(MANGLED_TODO, "?RegisterHandler@Console@@YAXV?$shared_ptr@VConsoleOutputHandler@Console@@@std@@@Z");
		// std::shared_ptr<Console::ConsoleOutputHandler> handler;
		todo("implement");
		_sub_10950930(handler);
	}

	_inline ConsoleOutputHandler::ConsoleOutputHandler() // 0x10950320
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ConsoleOutputHandler@Console@@QAE@XZ");
		// Console::ConsoleOutputHandler *const this;

		compiler_generated();
	}
}

/* ---------- private code */

_extern void _sub_10950B80(LogConsoleOutputHandler *const, std::string const &);
void LogConsoleOutputHandler::WriteLine(std::string const &line) // 0x10950B80
{
	// `anonymous-namespace'::LogConsoleOutputHandler::WriteLine
	// std::string const &line;
	todo("implement");
	_sub_10950B80(this, line);
}

_inline LogConsoleOutputHandler::LogConsoleOutputHandler() // 0x10950350
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0LogConsoleOutputHandler@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::LogConsoleOutputHandler::LogConsoleOutputHandler
	// LogConsoleOutputHandler *const this;

	compiler_generated();
}

_inline LogConsoleOutputHandler::~LogConsoleOutputHandler() // 0x10950630
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1LogConsoleOutputHandler@hades_file_local@@UAE@XZ");
	// `anonymous-namespace'::LogConsoleOutputHandler::~LogConsoleOutputHandler
	// LogConsoleOutputHandler *const this;

	compiler_generated();
}
