#ifndef __COMMON_HTTP_HTTPHEADERS_HPP__
#define __COMMON_HTTP_HTTPHEADERS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Utils/NameValueTable.hpp"

#include <initializer_list>
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Http
{
	class CHttpHeaders;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Http
{
	class CHttpHeaders
	{
	public:
		public:
		struct SHeaderKeyComparator
		{
			bool operator()(std::string const &, std::string const &) const;
		};
		static_assert(sizeof(SHeaderKeyComparator) == 1, "Invalid SHeaderKeyComparator size");
		enum ECollisionOp
		{
			Reject = 0,
			Replace,
			Coalesce,
		};
		public:
		typedef std::map<std::string,std::string,SHeaderKeyComparator> TMap;
		typedef std::pair<std::string,std::string> THeaderPair;
		_inline std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::string> > > > begin() const;
		_inline std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::string> > > > end() const;
		_inline CHttpHeaders(Http::CHttpHeaders &&__that); /* compiler_generated() */
		_inline CHttpHeaders(Http::CHttpHeaders const &__that); /* compiler_generated() */
		CHttpHeaders(std::initializer_list<std::pair<std::string,std::string> > const &values);
		_inline CHttpHeaders();
		std::string const Get(std::string const &headerKey) const;
		bool GetInt(std::string const &headerKey, long long &value) const;
		__int32 GetCount() const;
		bool Contains(std::string const &headerKey) const;
		bool Add(std::string const &headerKey, std::string const &headerValue, ECollisionOp collisionOp);
		bool Remove(std::string const &headerKey);
		static void Parse(std::string const &str, Http::CHttpHeaders &headers);
		std::string ToString() const;
		std::vector<std::tuple<std::string,std::string> > GetHeaders();
		_inline std::string operator[](std::string const &headerKey) const;
		std::string &operator[](std::string const &);
	private:
		std::map<std::string,std::string,SHeaderKeyComparator> m_map; // 0x0
	public:
		_inline ~CHttpHeaders(); /* compiler_generated() */

		_inline Http::CHttpHeaders &operator=(Http::CHttpHeaders const &__that); /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Http::CHttpHeaders) == 12, "Invalid Http::CHttpHeaders size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Http
{
	inline bool CHttpHeaders::SHeaderKeyComparator::operator()(std::string const &s1, std::string const &s2) const // 0x107FB130
	{
		return std::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), [](char c1, char c2) { return tolower(c1) < tolower(c2); });
	}
}


namespace Http
{
	inline std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::string> > > > CHttpHeaders::begin() const // 0x107FD840
	{
		return m_map.begin();
	}
}


namespace Http
{
	inline std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::string> > > > CHttpHeaders::end() const // 0x107FDB00
	{
		return m_map.end();
	}

	inline CHttpHeaders::CHttpHeaders() // 0x10806D90
	{
	}
}


namespace Http
{
	inline std::string CHttpHeaders::operator[](std::string const &headerKey) const // 0x1082D190
	{
		if (auto it = m_map.find(headerKey); it != end())
		{
			return it->second;
		}
		else
		{
			return "";
		}
	}
}

/* ---------- private code */

#endif // __COMMON_HTTP_HTTPHEADERS_HPP__
