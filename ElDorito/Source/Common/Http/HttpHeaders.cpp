/* ---------- headers */

#include "Common/Http/HttpHeaders.hpp"
#include "hades/hades.h"

#include "Utils/NameValueTable.hpp"
#include "Utils/String.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <limits>
#include <map>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
namespace Http
{
	class CHttpHeaders;
}

namespace Utils {}
using namespace ::Utils;
namespace Http {}
using namespace ::Http;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Http
{
	CHttpHeaders::CHttpHeaders(std::initializer_list<std::pair<std::string,std::string> > const &values) // 0x107FA7A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0CHttpHeaders@Http@@QAE@ABV?$initializer_list@U?$pair@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@std@@@std@@@Z");
		// std::initializer_list<std::pair<std::string,std::string> > const &values;
			// std::initializer_list<std::pair<std::string,std::string> > const &<range>$L0;
			// std::pair<std::string,std::string> const *<begin>$L0;
			// std::pair<std::string,std::string> const *<end>$L0;
				// std::string const &k;
				// std::string const &v;

		for (auto const &[key, value] : values)
			Add(key, value, Coalesce);
	}
}


namespace Http
{
	std::string const CHttpHeaders::Get(std::string const &headerKey) const // 0x107FB750
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Get@CHttpHeaders@Http@@QBE?BV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV34@@Z");
		// static ...; // 0x107FB8C8
		// static ...; // 0x107FB8C0
		// Http::CHttpHeaders const *const this;
		// std::string const &headerKey;
			// std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::string> > > > it;

		if (auto it = m_map.find(headerKey); it != m_map.end())
			return it->second;
		return {};
	}

	bool CHttpHeaders::GetInt(std::string const &headerKey, long long &value) const // 0x107FBB20
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetInt@CHttpHeaders@Http@@QBE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AA_J@Z");
		// static ...; // 0x107FBC54
		// static ...; // 0x107FBC4C
		// Http::CHttpHeaders const *const this;
		// std::string const &headerKey;
		// long long &value;
		// std::errc ec;
		// std::string str;
		// std::from_chars_result $S2;
		// char const *p;

		std::string const str = Get(headerKey);
		if (str.empty())
			return false;
		auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value, 10);
		return ec == std::errc();
	}

	bool CHttpHeaders::Contains(std::string const &headerKey) const // 0x107FB620
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Contains@CHttpHeaders@Http@@QBE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string const &headerKey;

		return m_map.find(headerKey) != m_map.end();
	}

	bool CHttpHeaders::Add(std::string const &headerKey, std::string const &headerValue, Http::CHttpHeaders::ECollisionOp collisionOp) // 0x107FB2B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Add@CHttpHeaders@Http@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0W4ECollisionOp@12@@Z");
		// Http::CHttpHeaders *const this;
		// std::string const &headerKey;
		// std::string const &headerValue;
		// Http::CHttpHeaders::ECollisionOp collisionOp;
			// std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::string> > > > it;

		auto it = m_map.find(headerKey);
		if (it != m_map.end())
		{
			switch (collisionOp)
			{
			case Coalesce:
				if (it->second.empty())
					it->second = headerValue;
				else
					it->second += "," + headerValue;
				return true;
			case Replace:
				it->second = headerValue;
				return true;
			default:
				return false;
			}
		}
		else
		{
			m_map.emplace(headerKey, headerValue);
			return true;
		}
	}

	bool CHttpHeaders::Remove(std::string const &headerKey) // 0x107FBF10
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Remove@CHttpHeaders@Http@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x107FC04C
		// static ...; // 0x107FC044
		// Http::CHttpHeaders *const this;
		// std::string const &headerKey;
			// std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::string> > > > it;

		if (auto it = m_map.find(headerKey); it != m_map.end())
		{
			m_map.erase(it);
			return true;
		}
		return false;
	}

	void CHttpHeaders::Parse(std::string const &str, Http::CHttpHeaders &headers) // 0x107FBCD0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Parse@CHttpHeaders@Http@@SAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV12@@Z");
		// static ...; // 0x107FBE82
		// static ...; // 0x107FBE7C
		// static ...; // 0x107FBE58
		// static ...; // 0x107FBE50
		// std::string const &str;
		// Http::CHttpHeaders &headers;
		// unsigned __int32 pos;
			// std::string key;
			// std::string headerLine;
			// unsigned __int32 sp;
			// unsigned __int32 eol;
			// std::string value;

		unsigned __int32 start = 0;
		for (;;)
		{
			unsigned __int32 end = str.find("\r\n", start);
			if (end == std::string::npos)
				break;
			std::string headerLine = str.substr(start, end - start);
			start = end + 2;
			unsigned __int32 colon = headerLine.find(':');
			if (colon == std::string::npos)
				continue;
			std::string key = headerLine.substr(0, colon);
			std::string value = headerLine.substr(colon + 1);
			Utils::String::TrimInline(key);
			Utils::String::TrimInline(value);
			headers.Add(key, value, Coalesce);
		}
	}
}


namespace Http
{
	std::string CHttpHeaders::ToString() const // 0x107FC0B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ToString@CHttpHeaders@Http@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// static ...; // 0x107FC330
		// static ...; // 0x107FC325
		// static ...; // 0x107FC31C
		// static ...; // 0x107FC2F8
		// static ...; // 0x107FC2F0
		// Http::CHttpHeaders const *const this;
		// std::stringstream ss;
			// std::string const &last;
				// Http::CHttpHeaders const &<range>$L0;
				// std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::string> > > > <begin>$L0;
				// std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::string> > > > <end>$L0;
					// std::string const &k;
					// std::string const &v;

		std::stringstream ss;
		if (!m_map.empty())
		{
			std::string const &lastKey = (--m_map.end())->first;
			for (auto const &[key, value] : *this)
			{
				ss << key << ": " << value;
				if (lastKey != key)
					ss << "\r\n";
			}
		}
		return ss.str();
	}
}


namespace Http
{
	std::vector<std::tuple<std::string,std::string> > CHttpHeaders::GetHeaders() // 0x107FB940
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetHeaders@CHttpHeaders@Http@@QAE?AV?$vector@V?$tuple@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@std@@V?$allocator@V?$tuple@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@std@@@2@@std@@XZ");
		// static ...; // 0x107FBAB4
		// static ...; // 0x107FBAA9
		// static ...; // 0x107FBAA0
		// static ...; // 0x107FBA7C
		// static ...; // 0x107FBA74
		// Http::CHttpHeaders *const this;
		// std::vector<std::tuple<std::string,std::string> > headers;
			// std::map<std::string,std::string,Http::CHttpHeaders::SHeaderKeyComparator> &<range>$L0;
			// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::string> > > > <begin>$L0;
			// std::_Default_sentinel <end>$L0;
				// std::string const &k;
				// std::string const &v;

		std::vector<std::tuple<std::string,std::string> > headers;
		for (auto const &[k, v] : m_map)
			headers.emplace_back(k, v);
		return headers;
	}
}

/* ---------- private code */
