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
	extern CHttpHeaders* _sub_107FA7A0(Http::CHttpHeaders *const, std::initializer_list<std::pair<std::string,std::string> > const &);
	CHttpHeaders::CHttpHeaders(std::initializer_list<std::pair<std::string,std::string> > const &values) // 0x107FA7A0
	{
		mangled_x86(MANGLED_TODO, "??0CHttpHeaders@Http@@QAE@ABV?$initializer_list@U?$pair@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@std@@@std@@@Z");
		// std::initializer_list<std::pair<std::string,std::string> > const &values;
		{
			// std::initializer_list<std::pair<std::string,std::string> > const &<range>$L0;
			// std::pair<std::string,std::string> const *<begin>$L0;
			// std::pair<std::string,std::string> const *<end>$L0;
			{
				// std::string const &k;
				// std::string const &v;
			}
		}
		todo("implement");
		_sub_107FA7A0(this, values);
	}
}

extern std::string const _sub_107FB750(Http::CHttpHeaders const *const, std::string const &);
namespace Http
{
	std::string const CHttpHeaders::Get(std::string const &headerKey) const // 0x107FB750
	{
		mangled_x86(MANGLED_TODO, "?Get@CHttpHeaders@Http@@QBE?BV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV34@@Z");
		// static ...; // 0x107FB8C8
		// static ...; // 0x107FB8C0
		// Http::CHttpHeaders const *const this;
		// std::string const &headerKey;
		{
			// std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::string> > > > it;
		}
		todo("implement");
		std::string const __result = _sub_107FB750((Http::CHttpHeaders const *)this, headerKey);
		return __result;
	}

	_extern bool _sub_107FBB20(Http::CHttpHeaders const *const, std::string const &, long long &);
	bool CHttpHeaders::GetInt(std::string const &headerKey, long long &value) const // 0x107FBB20
	{
		mangled_x86(MANGLED_TODO, "?GetInt@CHttpHeaders@Http@@QBE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AA_J@Z");
		// static ...; // 0x107FBC54
		// static ...; // 0x107FBC4C
		// Http::CHttpHeaders const *const this;
		// std::string const &headerKey;
		// long long &value;
		// std::errc ec;
		// std::string str;
		// std::from_chars_result $S2;
		// char const *p;
		todo("implement");
		bool __result = _sub_107FBB20((Http::CHttpHeaders const *)this, headerKey, value);
		return __result;
	}

	_extern bool _sub_107FB620(Http::CHttpHeaders const *const, std::string const &);
	bool CHttpHeaders::Contains(std::string const &headerKey) const // 0x107FB620
	{
		mangled_x86(MANGLED_TODO, "?Contains@CHttpHeaders@Http@@QBE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string const &headerKey;
		todo("implement");
		bool __result = _sub_107FB620((Http::CHttpHeaders const *)this, headerKey);
		return __result;
	}

	_extern bool _sub_107FB2B0(Http::CHttpHeaders *const, std::string const &, std::string const &, Http::CHttpHeaders::ECollisionOp);
	bool CHttpHeaders::Add(std::string const &headerKey, std::string const &headerValue, Http::CHttpHeaders::ECollisionOp collisionOp) // 0x107FB2B0
	{
		mangled_x86(MANGLED_TODO, "?Add@CHttpHeaders@Http@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0W4ECollisionOp@12@@Z");
		// Http::CHttpHeaders *const this;
		// std::string const &headerKey;
		// std::string const &headerValue;
		// Http::CHttpHeaders::ECollisionOp collisionOp;
		{
			// std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::string> > > > it;
		}
		todo("implement");
		bool __result = _sub_107FB2B0(this, headerKey, headerValue, collisionOp);
		return __result;
	}

	_extern bool _sub_107FBF10(Http::CHttpHeaders *const, std::string const &);
	bool CHttpHeaders::Remove(std::string const &headerKey) // 0x107FBF10
	{
		mangled_x86(MANGLED_TODO, "?Remove@CHttpHeaders@Http@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x107FC04C
		// static ...; // 0x107FC044
		// Http::CHttpHeaders *const this;
		// std::string const &headerKey;
		{
			// std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::string> > > > it;
		}
		todo("implement");
		bool __result = _sub_107FBF10(this, headerKey);
		return __result;
	}

	_extern void _sub_107FBCD0(std::string const &, Http::CHttpHeaders &);
	void CHttpHeaders::Parse(std::string const &str, Http::CHttpHeaders &headers) // 0x107FBCD0
	{
		mangled_x86(MANGLED_TODO, "?Parse@CHttpHeaders@Http@@SAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV12@@Z");
		// static ...; // 0x107FBE82
		// static ...; // 0x107FBE7C
		// static ...; // 0x107FBE58
		// static ...; // 0x107FBE50
		// std::string const &str;
		// Http::CHttpHeaders &headers;
		// unsigned __int32 pos;
		{
			// std::string key;
			// std::string headerLine;
			// unsigned __int32 sp;
			// unsigned __int32 eol;
			// std::string value;
		}
		todo("implement");
		_sub_107FBCD0(str, headers);
	}
}

extern std::string _sub_107FC0B0(Http::CHttpHeaders const *const);
namespace Http
{
	std::string CHttpHeaders::ToString() const // 0x107FC0B0
	{
		mangled_x86(MANGLED_TODO, "?ToString@CHttpHeaders@Http@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// static ...; // 0x107FC330
		// static ...; // 0x107FC325
		// static ...; // 0x107FC31C
		// static ...; // 0x107FC2F8
		// static ...; // 0x107FC2F0
		// Http::CHttpHeaders const *const this;
		// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
		{
			// std::string const &last;
			{
				// Http::CHttpHeaders const &<range>$L0;
				// std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::string> > > > <begin>$L0;
				// std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::string> > > > <end>$L0;
				{
					// std::string const &k;
					// std::string const &v;
				}
			}
		}
		todo("implement");
		std::string __result = _sub_107FC0B0((Http::CHttpHeaders const *)this);
		return __result;
	}
}

extern std::vector<std::tuple<std::string,std::string>,std::allocator<std::tuple<std::string,std::string> > > _sub_107FB940(Http::CHttpHeaders *const);
namespace Http
{
	std::vector<std::tuple<std::string,std::string>,std::allocator<std::tuple<std::string,std::string> > > CHttpHeaders::GetHeaders() // 0x107FB940
	{
		mangled_x86(MANGLED_TODO, "?GetHeaders@CHttpHeaders@Http@@QAE?AV?$vector@V?$tuple@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@std@@V?$allocator@V?$tuple@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@std@@@2@@std@@XZ");
		// static ...; // 0x107FBAB4
		// static ...; // 0x107FBAA9
		// static ...; // 0x107FBAA0
		// static ...; // 0x107FBA7C
		// static ...; // 0x107FBA74
		// Http::CHttpHeaders *const this;
		// std::vector<std::tuple<std::string,std::string>,std::allocator<std::tuple<std::string,std::string> > > headers;
		{
			// std::map<std::string,std::string,Http::CHttpHeaders::SHeaderKeyComparator,std::allocator<std::pair<std::string const ,std::string> > > &<range>$L0;
			// std::_Tree_unchecked_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<std::string const ,std::string> > > > <begin>$L0;
			// std::_Default_sentinel <end>$L0;
			{
				// std::string const &k;
				// std::string const &v;
			}
		}
		todo("implement");
		std::vector<std::tuple<std::string,std::string>,std::allocator<std::tuple<std::string,std::string> > > __result = _sub_107FB940(this);
		return __result;
	}
}

/* ---------- private code */
