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
	extern DewritoReader* _sub_10C56FE0(Utils::DewritoReader *const);
	DewritoReader::DewritoReader() // 0x10C56FE0
	{
		mangled_x86(MANGLED_TODO, "??0DewritoReader@Utils@@QAE@XZ");
		// static ...; // 0x10C57140
		// static ...; // 0x10C57134
		// static ...; // 0x10C5712C
		// Utils::DewritoReader *const this;
		// std::error_code ec;
		todo("implement");
		_sub_10C56FE0(this);
	}
}

extern rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> _sub_10C572B0(Utils::DewritoReader *const);
namespace Utils
{
	rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> DewritoReader::GetDewritoJson() // 0x10C572B0
	{
		mangled_x86(MANGLED_TODO, "?GetDewritoJson@DewritoReader@Utils@@QAE?AV?$GenericDocument@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@VCrtAllocator@2@@rapidjson@@XZ");
		// static ...; // 0x10C573AC
		// static ...; // 0x10C573A0
		// static ...; // 0x10C57398
		// Utils::DewritoReader *const this;
		// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> copy;
		todo("implement");
		rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> __result = _sub_10C572B0(this);
		return __result;
	}

	_extern bool _sub_10C57620(Utils::DewritoReader *const, char const *);
	bool DewritoReader::ReadFile(char const *path) // 0x10C57620
	{
		mangled_x86(MANGLED_TODO, "?ReadFile@DewritoReader@Utils@@AAE_NPBD@Z");
		// static ...; // 0x10C57941
		// static ...; // 0x10C5793C
		// static ...; // 0x10C57918
		// static ...; // 0x10C57910
		// Utils::DewritoReader *const this;
		// char const *path;
		// std::basic_ifstream<char,std::char_traits<char> > in;
		// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
		// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
		{
			// char const *error;
		}
		// function call : unsigned long ()
		todo("implement");
		bool __result = _sub_10C57620(this, path);
		return __result;
	}
}

/* ---------- private code */

_extern void _sub_10C57400(rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> &, rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> &, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &);
void MergeDocuments(rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> &dest, rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> &src, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) // 0x10C57400
{
	// `anonymous-namespace'::MergeDocuments
	// static ...; // 0x10C5759C
	// static ...; // 0x10C57578
	// static ...; // 0x10C57570
	// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> &dest;
	// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> &src;
	// rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator;
	{
		// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > itr;
		{
			// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > key;
			// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > value;
		}
	}
	todo("implement");
	_sub_10C57400(dest, src, allocator);
}
