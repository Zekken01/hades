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
		for (auto const &[key, value] : values)
			Add(key, value, Coalesce);
	}
}


namespace Http
{
	std::string const CHttpHeaders::Get(std::string const &headerKey) const // 0x107FB750
	{
		if (auto it = m_map.find(headerKey); it != m_map.end())
			return it->second;
		return {};
	}

	bool CHttpHeaders::GetInt(std::string const &headerKey, long long &value) const // 0x107FBB20
	{
		std::string const str = Get(headerKey);
		if (str.empty())
			return false;
		auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value, 10);
		return ec == std::errc();
	}

	bool CHttpHeaders::Contains(std::string const &headerKey) const // 0x107FB620
	{
		return m_map.find(headerKey) != m_map.end();
	}

	bool CHttpHeaders::Add(std::string const &headerKey, std::string const &headerValue, Http::CHttpHeaders::ECollisionOp collisionOp) // 0x107FB2B0
	{
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
		if (auto it = m_map.find(headerKey); it != m_map.end())
		{
			m_map.erase(it);
			return true;
		}
		return false;
	}

	void CHttpHeaders::Parse(std::string const &str, Http::CHttpHeaders &headers) // 0x107FBCD0
	{
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
		std::vector<std::tuple<std::string,std::string> > headers;
		for (auto const &[k, v] : m_map)
			headers.emplace_back(k, v);
		return headers;
	}
}

/* ---------- private code */
