/* ---------- headers */

#include "Utils/DewritoReader.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/error/en.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "Utils/Singleton.hpp"

#include "Utils/Logger.hpp"  // hades: added for 0x10C57620

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

namespace Utils
{
	class DewritoReader;
}

namespace Utils {}
using namespace ::Utils;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void MergeDocuments(rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> &dest, rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> &src, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Utils
{
	DewritoReader::DewritoReader() : dewrito_json_filepath("data\\dewrito.json"), dewrito_json_user_filepath("data\\dewrito.user.json") /* hades-mem-init:  */ // 0x10C56FE0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0DewritoReader@Utils@@QAE@XZ");

		m_dewrito_json.SetObject();
		m_isValid = ReadFile(dewrito_json_filepath);
		std::error_code ec;
		if (std::filesystem::exists(dewrito_json_user_filepath, ec))
			ReadFile(dewrito_json_user_filepath);
	}
}


namespace Utils
{
	rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> DewritoReader::GetDewritoJson() // 0x10C572B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetDewritoJson@DewritoReader@Utils@@QAE?AV?$GenericDocument@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@VCrtAllocator@2@@rapidjson@@XZ");

		rapidjson::Document copy;
		copy.CopyFrom(m_dewrito_json, copy.GetAllocator());
		return copy;
	}

	bool DewritoReader::ReadFile(char const *path) // 0x10C57620
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ReadFile@DewritoReader@Utils@@AAE_NPBD@Z");

		std::ifstream in(path, std::ios::in | std::ios::binary);
		if (!in || !in.is_open())
		{
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "Utils::DewritoReader::ReadFile(): Failed to open \"%s\". LastError: %d", path, GetLastError());
			return false;
		}
		std::stringstream ss;
		ss << in.rdbuf();
		rapidjson::Document json;
		if (json.Parse<0>(ss.str().c_str()).HasParseError())
		{
			char const *error = rapidjson::GetParseError_En(json.GetParseError());
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "Utils::DewritoReader::ReadFile(): Failed to parse \"%s\": %s", path, error);
			return false;
		}
		MergeDocuments(m_dewrito_json, json, m_dewrito_json.GetAllocator());
		return true;
	}
}

/* ---------- private code */

void MergeDocuments(rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> &dest, rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> &src, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) // 0x10C57400
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?MergeDocuments@@YAXAAV?$GenericDocument@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@VCrtAllocator@2@@rapidjson@@0AAV?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@Z");

	if (!src.IsObject() || !dest.IsObject())
		return;
	for (rapidjson::Value::ConstMemberIterator itr = src.MemberBegin(); itr != src.MemberEnd(); ++itr)
	{
		rapidjson::Value key(itr->name, allocator);
		rapidjson::Value value(itr->value, allocator);
		dest.RemoveMember(itr->name);
		dest.AddMember(key, value, allocator);
	}
}
