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
			bool operator()(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &) const;
		};
		static_assert(sizeof(SHeaderKeyComparator) == 1, "Invalid SHeaderKeyComparator size");
		enum ECollisionOp
		{
			Reject = 0,
			Replace,
			Coalesce,
		};
		public:
		typedef std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,SHeaderKeyComparator,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > TMap;
		typedef std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > THeaderPair;
		_inline std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > > begin() const;
		_inline std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > > end() const;
		_inline CHttpHeaders(Http::CHttpHeaders &&__that); /* compiler_generated() */
		_inline CHttpHeaders(Http::CHttpHeaders const &__that); /* compiler_generated() */
		CHttpHeaders(std::initializer_list<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &values);
		_inline CHttpHeaders();
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > const Get(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &headerKey) const;
		bool GetInt(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &headerKey, long long &value) const;
		__int32 GetCount() const;
		bool Contains(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &headerKey) const;
		bool Add(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &headerKey, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &headerValue, ECollisionOp collisionOp);
		bool Remove(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &headerKey);
		static void Parse(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str, Http::CHttpHeaders &headers);
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > ToString() const;
		std::vector<std::tuple<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::tuple<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > GetHeaders();
		_inline std::basic_string<char,std::char_traits<char>,std::allocator<char> > operator[](std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &headerKey) const;
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > &operator[](std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
	private:
		std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,SHeaderKeyComparator,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > m_map; // 0x0
	public:
		_inline ~CHttpHeaders(); /* compiler_generated() */
		Http::CHttpHeaders &operator=(Http::CHttpHeaders &); /* compiler_generated() */
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
	_extern bool _sub_107FB130(Http::CHttpHeaders::SHeaderKeyComparator const *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
	_inline bool CHttpHeaders::SHeaderKeyComparator::operator()(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &s1, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &s2) const // 0x107FB130
	{
		mangled_x86(MANGLED_TODO, "??RSHeaderKeyComparator@CHttpHeaders@Http@@QBE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &s2;
		todo("implement");
		bool __result = _sub_107FB130((Http::CHttpHeaders::SHeaderKeyComparator const *)this, s1, s2);
		return __result;
	}
}

extern std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > > _sub_107FD840(Http::CHttpHeaders const *const);
namespace Http
{
	_inline std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > > CHttpHeaders::begin() const // 0x107FD840
	{
		mangled_x86(MANGLED_TODO, "?begin@CHttpHeaders@Http@@QBE?AV?$_Tree_const_iterator@V?$_Tree_val@U?$_Tree_simple_types@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@std@@@std@@@std@@@std@@XZ");
		// Http::CHttpHeaders const *const this;
		todo("implement");
		std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > > __result = _sub_107FD840((Http::CHttpHeaders const *)this);
		return __result;
	}
}

extern std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > > _sub_107FDB00(Http::CHttpHeaders const *const);
namespace Http
{
	_inline std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > > CHttpHeaders::end() const // 0x107FDB00
	{
		mangled_x86(MANGLED_TODO, "?end@CHttpHeaders@Http@@QBE?AV?$_Tree_const_iterator@V?$_Tree_val@U?$_Tree_simple_types@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@std@@@std@@@std@@@std@@XZ");
		// Http::CHttpHeaders const *const this;
		todo("implement");
		std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > > __result = _sub_107FDB00((Http::CHttpHeaders const *)this);
		return __result;
	}

	extern CHttpHeaders* _sub_10806D90(Http::CHttpHeaders *const);
	_inline CHttpHeaders::CHttpHeaders() // 0x10806D90
	{
		mangled_x86(MANGLED_TODO, "??0CHttpHeaders@Http@@QAE@XZ");
		// Http::CHttpHeaders *const this;
		todo("implement");
		_sub_10806D90(this);
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_1082D190(Http::CHttpHeaders const *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
namespace Http
{
	_inline std::basic_string<char,std::char_traits<char>,std::allocator<char> > CHttpHeaders::operator[](std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &headerKey) const // 0x1082D190
	{
		mangled_x86(MANGLED_TODO, "??ACHttpHeaders@Http@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV23@@Z");
		// static ...; // 0x1082D314
		// static ...; // 0x1082D30C
		// Http::CHttpHeaders const *const this;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &headerKey;
		{
			// std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > > it;
		}
		todo("implement");
		std::string __result = _sub_1082D190((Http::CHttpHeaders const *)this, headerKey);
		return __result;
	}
}

/* ---------- private code */

#endif // __COMMON_HTTP_HTTPHEADERS_HPP__
