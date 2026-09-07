/* ---------- headers */

#include "Scripting/HaloScript/HsMethodMap.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

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
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <string_view>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
namespace Scripting
{
	namespace HS
	{
		class ScriptMethodMap;
		struct ScriptMethod;
		struct ScriptParameter;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Scripting {}
using namespace ::Scripting;
namespace Scripting
{
	namespace HS {}
	using namespace Scripting::HS;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Scripting
{
	namespace HS
	{
		extern bool ValidIdentifier(std::basic_string_view<char,std::char_traits<char> > name);
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Scripting
{
	namespace HS
	{
		_extern bool _sub_10702520(std::basic_string_view<char,std::char_traits<char> >);
		bool ValidIdentifier(std::basic_string_view<char,std::char_traits<char> > name) // 0x10702520
		{
			mangled_x86(MANGLED_TODO, "?ValidIdentifier@HS@Scripting@@YA_NV?$basic_string_view@DU?$char_traits@D@std@@@std@@@Z");
			// std::basic_string_view<char,std::char_traits<char> > name;
			{
				// unsigned __int32 i;
			}
			todo("implement");
			bool __result = _sub_10702520(name);
			return __result;
		}

		_extern void _sub_10701260(Scripting::HS::ScriptMethodMap *const, Scripting::HS::ScriptMethod &);
		void ScriptMethodMap::AddMethod(Scripting::HS::ScriptMethod &&method) // 0x10701260
		{
			mangled_x86(MANGLED_TODO, "?AddMethod@ScriptMethodMap@HS@Scripting@@AAEX$$QAUScriptMethod@23@@Z");
			// Scripting::HS::ScriptMethod &method;
			{
				// std::vector<Scripting::HS::ScriptParameter,std::allocator<Scripting::HS::ScriptParameter> > &<range>$L0;
				// Scripting::HS::ScriptParameter *<begin>$L0;
				// Scripting::HS::ScriptParameter *<end>$L0;
				{
					// Scripting::HS::ScriptParameter const &parameter;
				}
			}
			todo("implement");
			_sub_10701260(this, method);
		}

		extern ScriptMethod* _sub_10700770(Scripting::HS::ScriptMethod *const, Scripting::HS::ScriptMethod const &);
		_inline ScriptMethod::ScriptMethod(Scripting::HS::ScriptMethod const &__that) // 0x10700770
		{
			mangled_x86(MANGLED_TODO, "??0ScriptMethod@HS@Scripting@@QAE@ABU012@@Z");
			// Scripting::HS::ScriptMethod const &__that;
			compiler_generated();
			todo("implement");
			_sub_10700770(this, __that);
		}

		_extern void _sub_10701690(Scripting::HS::ScriptMethodMap *const, std::basic_string_view<char,std::char_traits<char> >, std::basic_string_view<char,std::char_traits<char> >, Scripting::HS::ScriptMethodFlags, void (*)(short, long, bool), e_hs_type, std::initializer_list<Scripting::HS::ScriptParameter>);
		void ScriptMethodMap::AddMethod(std::basic_string_view<char,std::char_traits<char> > name, std::basic_string_view<char,std::char_traits<char> > description, Scripting::HS::ScriptMethodFlags flags, void (*evaluate)(short, long, bool), e_hs_type returnType, std::initializer_list<Scripting::HS::ScriptParameter> parameters) // 0x10701690
		{
			mangled_x86(MANGLED_TODO, "?AddMethod@ScriptMethodMap@HS@Scripting@@QAEXV?$basic_string_view@DU?$char_traits@D@std@@@std@@0W4ScriptMethodFlags@23@P6AXFJ_N@ZW4e_hs_type@@V?$initializer_list@UScriptParameter@HS@Scripting@@@5@@Z");
			// Scripting::HS::ScriptMethodFlags flags;
			// void (*evaluate)(short, long, bool);
			// e_hs_type returnType;
			// std::initializer_list<Scripting::HS::ScriptParameter> parameters;
			// Scripting::HS::ScriptMethod method;
			todo("implement");
			_sub_10701690(this, name, description, flags, evaluate, returnType, parameters);
		}

		extern ScriptMethod const *_sub_10701880(Scripting::HS::ScriptMethodMap const *const, std::basic_string_view<char,std::char_traits<char> >);
		Scripting::HS::ScriptMethod const *ScriptMethodMap::FindMethod(std::basic_string_view<char,std::char_traits<char> > name) const // 0x10701880
		{
			mangled_x86(MANGLED_TODO, "?FindMethod@ScriptMethodMap@HS@Scripting@@QBEPBUScriptMethod@23@V?$basic_string_view@DU?$char_traits@D@std@@@std@@@Z");
			// static ...; // 0x107019BC
			// static ...; // 0x107019B4
			// Scripting::HS::ScriptMethodMap const *const this;
			// std::basic_string_view<char,std::char_traits<char> > name;
			{
				// std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<std::basic_string_view<char,std::char_traits<char> > const ,Scripting::HS::ScriptMethod> > > > it;
			}
			todo("implement");
			Scripting::HS::ScriptMethod const * __result = _sub_10701880((Scripting::HS::ScriptMethodMap const *)this, name);
			return __result;
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10701E00(Scripting::HS::ScriptMethodMap *const, Scripting::HS::ScriptMethod const *);
namespace Scripting
{
	namespace HS
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > ScriptMethodMap::GenerateHelp(Scripting::HS::ScriptMethod const *method) // 0x10701E00
		{
			mangled_x86(MANGLED_TODO, "?GenerateHelp@ScriptMethodMap@HS@Scripting@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PBUScriptMethod@23@@Z");
			// Scripting::HS::ScriptMethod const *method;
			todo("implement");
			std::string __result = _sub_10701E00(this, method);
			return __result;
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10701E90(Scripting::HS::ScriptMethodMap *const, Scripting::HS::ScriptMethod const *);
namespace Scripting
{
	namespace HS
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > ScriptMethodMap::GenerateMethodDeclaration(Scripting::HS::ScriptMethod const *method) // 0x10701E90
		{
			mangled_x86(MANGLED_TODO, "?GenerateMethodDeclaration@ScriptMethodMap@HS@Scripting@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PBUScriptMethod@23@@Z");
			// static ...; // 0x107023BC
			// static ...; // 0x107023B7
			// static ...; // 0x107023AF
			// static ...; // 0x107023A4
			// static ...; // 0x10702368
			// static ...; // 0x10702360
			// Scripting::HS::ScriptMethodMap *const this;
			// Scripting::HS::ScriptMethod const *method;
			// std::basic_string_view<char,std::char_traits<char> > returnType;
			{
				// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > parameters;
				{
					// unsigned __int32 i;
					{
						// std::basic_string<char,std::char_traits<char>,std::allocator<char> > typeStr;
						// std::basic_string_view<char,std::char_traits<char> > type;
					}
				}
			}
			todo("implement");
			std::string __result = _sub_10701E90(this, method);
			return __result;
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10701A20(Scripting::HS::ScriptMethodMap const *const);
namespace Scripting
{
	namespace HS
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > ScriptMethodMap::GenerateDocs() const // 0x10701A20
		{
			mangled_x86(MANGLED_TODO, "?GenerateDocs@ScriptMethodMap@HS@Scripting@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
			// static ...; // 0x10701D30
			// static ...; // 0x10701D25
			// static ...; // 0x10701D1C
			// static ...; // 0x10701CF8
			// static ...; // 0x10701CF0
			// Scripting::HS::ScriptMethodMap const *const this;
			// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > docs;
			// Scripting::HS::ScriptMethodMap &methods;
			{
				// std::unordered_map<std::basic_string_view<char,std::char_traits<char> >,Scripting::HS::ScriptMethod,std::hash<std::basic_string_view<char,std::char_traits<char> > >,std::equal_to<std::basic_string_view<char,std::char_traits<char> > >,std::allocator<std::pair<std::basic_string_view<char,std::char_traits<char> > const ,Scripting::HS::ScriptMethod> > > &<range>$L0;
				// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<std::basic_string_view<char,std::char_traits<char> > const ,Scripting::HS::ScriptMethod> > > > <begin>$L0;
				// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<std::basic_string_view<char,std::char_traits<char> > const ,Scripting::HS::ScriptMethod> > > > <end>$L0;
				{
					// Scripting::HS::ScriptMethod const &method;
					// std::basic_string_view<char,std::char_traits<char> > const &name;
				}
			}
			todo("implement");
			std::string __result = _sub_10701A20((Scripting::HS::ScriptMethodMap const *)this);
			return __result;
		}

		_extern void _sub_107017F0(Scripting::HS::ScriptMethodMap *const);
		void ScriptMethodMap::Finalize() // 0x107017F0
		{
			mangled_x86(MANGLED_TODO, "?Finalize@ScriptMethodMap@HS@Scripting@@QAEXXZ");
			// Scripting::HS::ScriptMethodMap *const this;
			todo("implement");
			_sub_107017F0(this);
		}
	}
}

/* ---------- private code */
