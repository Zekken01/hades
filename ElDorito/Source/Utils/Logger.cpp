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


namespace Utils
{
	std::string LogLevelToString(Utils::LogLevel level) // 0x10C5A850
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?LogLevelToString@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@W4LogLevel@1@@Z");

		switch (level)
		{
		case Utils::LogLevel::None:
			return "None";
		case Utils::LogLevel::Trace:
			return "Trace";
		case Utils::LogLevel::Info:
			return "Info";
		case Utils::LogLevel::Warning:
			return "Warning";
		case Utils::LogLevel::Error:
			return "Error";
		}
		return "Unknown";
	}
}


namespace Utils
{
	std::string LogTypesToString(Utils::LogTypes types) // 0x10C5A9E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?LogTypesToString@Utils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@W4LogTypes@1@@Z");

		switch (types)
		{
		case Utils::LogTypes::None:
			return "None";
		case Utils::LogTypes::All:
			return "All";
		default:
		{
			std::vector<std::string> bits;
			for (__int32 bit = 0; bit < 32; bit++)
			{
				if (!(((__int32)types >> bit) & 1))
					continue;
				switch ((Utils::LogTypes)(1 << bit))
				{
				case Utils::LogTypes::Game:
					bits.push_back("Game");
					break;
				case Utils::LogTypes::Network:
					bits.push_back("Network");
					break;
				case Utils::LogTypes::Graphics:
					bits.push_back("Graphics");
					break;
				case Utils::LogTypes::Memory:
					bits.push_back("Memory");
					break;
				case Utils::LogTypes::Sound:
					bits.push_back("Sound");
					break;
				case Utils::LogTypes::Input:
					bits.push_back("Input");
					break;
				case Utils::LogTypes::Debug:
					bits.push_back("Debug");
					break;
				default:
					bits.push_back(std::string("UnknownBit") + std::to_string(bit));
				}
			}
			std::stringstream ss;
			ss << bits[0];
			if (bits.size() > 1)
				for (unsigned __int32 i = 1; i < bits.size(); i++)
					ss << " | " << bits[i];
			return ss.str();
		}
		}
	}

	// mangled_x86(MANGLED_DEFAULT, "??0LogEntry@Utils@@QAE@XZ"); no body to assert in

	unsigned long __stdcall Logger::Flusher(void *lpParam) // 0x10C5A5E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Flusher@Logger@Utils@@CGKPAX@Z");

		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
			Utils::Singleton<Utils::Logger>::Instance().Flush();
		}
	}

	Logger::Logger() // 0x10C59920
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0Logger@Utils@@QAE@XZ");

		typedef boost::lockfree::queue<Utils::LogEntry, boost::lockfree::fixed_sized<false> > entry_queue;
		reinterpret_cast<entry_queue *>(Entries)->entry_queue::queue(0);
		Level = static_cast<Utils::LogLevel>(3);
		Types = static_cast<Utils::LogTypes>(-1);
		CreateThread(nullptr, 0, Flusher, nullptr, 0, nullptr);
	}

	void Logger::Flush() // 0x10C59E20
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Flush@Logger@Utils@@QAEXXZ");

		if (reinterpret_cast<boost::lockfree::queue<Utils::LogEntry, boost::lockfree::fixed_sized<false> > *>(Entries)->empty())
			return;
		std::lock_guard<std::mutex> lock(flushMutex);
		Modules::ModuleGame &gameModule = Modules::ModuleGame::Instance();
		std::filesystem::path logFilePath(gameModule.VarLogName->ValueString);
		std::filesystem::path parentDirectory = logFilePath.parent_path();
		if (parentDirectory != "")
			std::filesystem::create_directories(parentDirectory);
		std::ofstream outfile;
		outfile.open(logFilePath, std::ios_base::app);
		if (outfile.fail())
			return;
		Utils::LogEntry entry;
		while (reinterpret_cast<boost::lockfree::queue<Utils::LogEntry, boost::lockfree::fixed_sized<false> > *>(Entries)->pop(entry))
		{
			std::string message(entry.Message);
			delete[] entry.Message;
			for (auto filter : gameModule.FiltersExclude)
			{
				if (strstr(message.c_str(), filter.c_str()) != nullptr)
					goto closefile;
			}
			for (auto filter : gameModule.FiltersInclude)
			{
				if (strstr(message.c_str(), filter.c_str()) != nullptr)
					continue;
				goto closefile;
			}
			time_t t = std::chrono::system_clock::to_time_t(entry.Time);
			tm ourLocalTime;
			if (localtime_s(&ourLocalTime, &t) != 0)
				goto closefile;
			outfile << '[' << std::put_time(&ourLocalTime, "%m-%d-%Y %H:%M:%S") << "] " << LogTypesToString(entry.Type) << " - " << message << '\n';
		}
		closefile:
		outfile.close();
	}
}

/* ---------- private code */

namespace Utils
{
	bool Logger::TestLevel(Utils::LogTypes type, Utils::LogLevel level) const // 0x10C5B030
	{

			if (level != Utils::LogLevel::Error)
			{
				if (Level == Utils::LogLevel::None || level < Level)
					return false;
				if (!((__int32)Types & (__int32)type))
					return false;
			}
			return true;
	}
}

// hades: Log was dropped from the tree (an orphaned member); it sits at the end of the
// file so the functions above keep their line numbers.
namespace Utils
{
	void Logger::Log(Utils::LogTypes type, Utils::LogLevel level, std::string message, ...) // 0x10C5A670
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Log@Logger@Utils@@QAAXW4LogTypes@2@W4LogLevel@2@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ZZ");

		if (!TestLevel(type, level))
			return;

		// construct formatted message
		va_list ap;
		va_start(ap, message);
		int bufferSize = _vscprintf(message.c_str(), ap) + 1;
		char *buffer = new char[bufferSize];
		vsprintf_s(buffer, bufferSize, message.c_str(), ap);
		va_end(ap);

		// add it to the queue to be flushed to disk
		LogEntry entry = { };
		entry.Time = std::chrono::system_clock::now();
		entry.Type = type;
		entry.Message = buffer;
		reinterpret_cast<boost::lockfree::queue<Utils::LogEntry, boost::lockfree::fixed_sized<false> > *>(Entries)->push(entry);
	}
}
