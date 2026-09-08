/* ---------- headers */

#include "mods/mod_database.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "Modules/ModuleServer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/istreamwrapper.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/ostreamwrapper.h"
#include "ThirdParty/rapidjson/prettywriter.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <Windows.h>
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
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_mod_database;
struct begin;
struct end;
struct lambda_1;
struct s_mod_origin_info;
struct s_mod_package_id;

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

/* ---------- constants */

/* ---------- definitions */

//class c_mod_database::purge_all_not_in_set::__l2::<lambda_1>
//{
//public:
//	<lambda_1>(c_mod_database::purge_all_not_in_set::__l2::<lambda_1> &);
//	<lambda_1>(std::unordered_set<s_mod_package_id> &);
//private:
//	std::unordered_set<s_mod_package_id> &set; // 0x0
//public:
//	c_mod_database::purge_all_not_in_set::__l2::<lambda_1> &operator=(c_mod_database::purge_all_not_in_set::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(c_mod_database::purge_all_not_in_set::__l2::<lambda_1>) == 4, "Invalid c_mod_database::purge_all_not_in_set::__l2::<lambda_1> size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_1084DB20(c_mod_database *const);
c_mod_database::~c_mod_database() // 0x1084DB20
{
	mangled_x86(MANGLED_TODO, "??1c_mod_database@@QAE@XZ");
	// c_mod_database *const this;
	todo("implement");
	_sub_1084DB20(this);
}

// mangled_x86(MANGLED_DEFAULT, "??1s_record@c_mod_database@@QAE@XZ"); no body to assert in
_inline c_mod_database::s_record::~s_record() = default; // 0x1084DBD0

// mangled_x86(MANGLED_DEFAULT, "??4s_mod_origin_info@@QAEAAU0@ABU0@@Z"); no body to assert in
_inline s_mod_origin_info &s_mod_origin_info::operator=(s_mod_origin_info const &__that) = default; // 0x1084DE80

// mangled_x86(MANGLED_DEFAULT, "??4s_record@c_mod_database@@QAEAAU01@ABU01@@Z"); no body to assert in
_inline c_mod_database::s_record &c_mod_database::s_record::operator=(c_mod_database::s_record const &__that) = default; // 0x1084DF20

_extern bool _sub_10853630(c_mod_database *const, s_mod_package_id const &, c_mod_database::s_record **);
bool c_mod_database::try_get_record(s_mod_package_id const &id, c_mod_database::s_record **record) // 0x10853630
{
	mangled_x86(MANGLED_TODO, "?try_get_record@c_mod_database@@QAE_NABUs_mod_package_id@@PAPAUs_record@1@@Z");
	// static ...; // 0x1085373C
	// c_mod_database *const this;
	// s_mod_package_id const &id;
	// c_mod_database::s_record **record;
	{
		// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<s_mod_package_id const ,c_mod_database::s_record> > > > it;
	}
	todo("implement");
	bool __result = _sub_10853630(this, id, record);
	return __result;
}

_extern bool _sub_10852200(c_mod_database *const, s_mod_package_id const &, c_mod_database::s_record **);
bool c_mod_database::get_or_create_record(s_mod_package_id const &id, c_mod_database::s_record **record) // 0x10852200
{
	mangled_x86(MANGLED_TODO, "?get_or_create_record@c_mod_database@@QAE_NABUs_mod_package_id@@PAPAUs_record@1@@Z");
	// c_mod_database::s_record **record;
	todo("implement");
	bool __result = _sub_10852200(this, id, record);
	return __result;
}

_extern bool _sub_108517C0(c_mod_database *const, s_mod_package_id const &, c_mod_database::s_record **);
bool c_mod_database::create_record(s_mod_package_id const &id, c_mod_database::s_record **record) // 0x108517C0
{
	mangled_x86(MANGLED_TODO, "?create_record@c_mod_database@@QAE_NABUs_mod_package_id@@PAPAUs_record@1@@Z");
	// static ...; // 0x10851A34
	// static ...; // 0x10851A10
	// static ...; // 0x10851A08
	// c_mod_database *const this;
	// s_mod_package_id const &id;
	// c_mod_database::s_record **record;
	{
		// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<s_mod_package_id const ,c_mod_database::s_record> > > > it;
		{
			// c_mod_database::s_record new_record;
			// std::pair<std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<s_mod_package_id const ,c_mod_database::s_record> > > >,bool> result;
		}
	}
	todo("implement");
	bool __result = _sub_108517C0(this, id, record);
	return __result;
}

_extern bool _sub_10851D60(c_mod_database *const, s_mod_package_id const &);
bool c_mod_database::delete_record(s_mod_package_id const &id) // 0x10851D60
{
	mangled_x86(MANGLED_TODO, "?delete_record@c_mod_database@@QAE_NABUs_mod_package_id@@@Z");
	// static ...; // 0x10851EEC
	// static ...; // 0x10851EE4
	// c_mod_database *const this;
	// s_mod_package_id const &id;
	{
		// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<s_mod_package_id const ,c_mod_database::s_record> > > > it;
	}
	todo("implement");
	bool __result = _sub_10851D60(this, id);
	return __result;
}

_extern bool _sub_108537A0(c_mod_database *const, s_mod_package_id const &, c_mod_database::s_record const &);
bool c_mod_database::update_record(s_mod_package_id const &id, c_mod_database::s_record const &record) // 0x108537A0
{
	mangled_x86(MANGLED_TODO, "?update_record@c_mod_database@@QAE_NABUs_mod_package_id@@ABUs_record@1@@Z");
	// static ...; // 0x108538F4
	// c_mod_database *const this;
	// s_mod_package_id const &id;
	// c_mod_database::s_record const &record;
	{
		// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<s_mod_package_id const ,c_mod_database::s_record> > > > it;
	}
	todo("implement");
	bool __result = _sub_108537A0(this, id, record);
	return __result;
}

_extern bool _sub_108516B0(c_mod_database *const, std::string const &);
bool c_mod_database::create(std::string const &filename) // 0x108516B0
{
	mangled_x86(MANGLED_TODO, "?create@c_mod_database@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// std::string const &filename;
	todo("implement");
	bool __result = _sub_108516B0(this, filename);
	return __result;
}

_extern bool _sub_10852AD0(c_mod_database *const, std::string const &);
bool c_mod_database::load_or_create(std::string const &filename) // 0x10852AD0
{
	mangled_x86(MANGLED_TODO, "?load_or_create@c_mod_database@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// std::string const &filename;
	todo("implement");
	bool __result = _sub_10852AD0(this, filename);
	return __result;
}

_extern bool _sub_108522A0(c_mod_database *const, std::string const &);
bool c_mod_database::load(std::string const &filename) // 0x108522A0
{
	mangled_x86(MANGLED_TODO, "?load@c_mod_database@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// static ...; // 0x1085291A
	// static ...; // 0x10852918
	// static ...; // 0x10852909
	// static ...; // 0x10852905
	// static ...; // 0x10852901
	// static ...; // 0x108528F6
	// static ...; // 0x108528ED
	// static ...; // 0x108528E7
	// static ...; // 0x108528E0
	// static ...; // 0x10852868
	// static ...; // 0x10852860
	// c_mod_database *const this;
	// std::string const &filename;
	// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> d;
	// std::unordered_map<s_mod_package_id,c_mod_database::s_record> tmp;
	// rapidjson::GenericMemberIterator<0,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > records_member;
	// std::ifstream ifs;
	// rapidjson::BasicIStreamWrapper<std::istream > isw;
	{
		// rapidjson::GenericObject<0,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > &<range>$L0;
		// rapidjson::GenericMemberIterator<0,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > <begin>$L0;
		// rapidjson::GenericMemberIterator<0,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > <end>$L0;
		{
			// rapidjson::GenericMember<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &key;
			{
				// c_mod_database::s_record record;
				// char const *hash;
				// rapidjson::GenericObject<0,rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > value;
			}
		}
	}
	todo("implement");
	bool __result = _sub_108522A0(this, filename);
	return __result;
}

_extern bool _sub_108530E0(c_mod_database *const);
bool c_mod_database::save() // 0x108530E0
{
	mangled_x86(MANGLED_TODO, "?save@c_mod_database@@QAE_NXZ");
	// static ...; // 0x108534C7
	// static ...; // 0x108534C3
	// static ...; // 0x108534BC
	// static ...; // 0x108534B1
	// static ...; // 0x108534A8
	// static ...; // 0x108534A4
	// static ...; // 0x1085345C
	// static ...; // 0x10853454
	// c_mod_database *const this;
	// rapidjson::BasicOStreamWrapper<std::ostream > osw;
	// std::ofstream ofs;
	// rapidjson::PrettyWriter<rapidjson::BasicOStreamWrapper<std::ostream >,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	{
		// std::unordered_map<s_mod_package_id,c_mod_database::s_record> &<range>$L0;
		// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<s_mod_package_id const ,c_mod_database::s_record> > > > <begin>$L0;
		// std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<s_mod_package_id const ,c_mod_database::s_record> > > > <end>$L0;
		{
			// std::pair<s_mod_package_id const ,c_mod_database::s_record> &record;
			{
				// std::string key;
			}
		}
	}
	todo("implement");
	bool __result = _sub_108530E0(this);
	return __result;
}

_extern void _sub_10852D20(c_mod_database *const, s_mod_package_id const &);
void c_mod_database::notify_record_changed(s_mod_package_id const &id) // 0x10852D20
{
	mangled_x86(MANGLED_TODO, "?notify_record_changed@c_mod_database@@QAEXABUs_mod_package_id@@@Z");
	// s_mod_package_id const &id;
	todo("implement");
	_sub_10852D20(this, id);
}

_extern void _sub_10852E70(c_mod_database *const, std::function<bool __cdecl(s_mod_package_id const &,c_mod_database::s_record const &)>);
void c_mod_database::purge_any(std::function<bool __cdecl(s_mod_package_id const &,c_mod_database::s_record const &)> predicate) // 0x10852E70
{
	mangled_x86(MANGLED_TODO, "?purge_any@c_mod_database@@QAEXV?$function@$$A6A_NABUs_mod_package_id@@ABUs_record@c_mod_database@@@Z@std@@@Z");
	// static ...; // 0x1085304C
	// static ...; // 0x10853044
	// c_mod_database *const this;
	// std::function<bool __cdecl(s_mod_package_id const &,c_mod_database::s_record const &)> predicate;
	{
		// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<s_mod_package_id const ,c_mod_database::s_record> > > > it;
	}
	todo("implement");
	_sub_10852E70(this, predicate);
}

_extern void _sub_10852DA0(c_mod_database *const, std::unordered_set<s_mod_package_id>);
void c_mod_database::purge_all_not_in_set(std::unordered_set<s_mod_package_id> set) // 0x10852DA0
{
	mangled_x86(MANGLED_TODO, "?purge_all_not_in_set@c_mod_database@@QAEXV?$unordered_set@Us_mod_package_id@@U?$hash@Us_mod_package_id@@@std@@U?$equal_to@Us_mod_package_id@@@3@V?$allocator@Us_mod_package_id@@@3@@std@@@Z");
	// std::unordered_set<s_mod_package_id> set;
	todo("implement");
	_sub_10852DA0(this, set);
}

// mangled_x86(MANGLED_DEFAULT, "??0s_mod_origin_info@@QAE@$$QAU0@@Z"); no body to assert in
_inline s_mod_origin_info::s_mod_origin_info(s_mod_origin_info &&__that) = default; // 0x1084CC50

// mangled_x86(MANGLED_DEFAULT, "??0s_mod_origin_info@@QAE@ABU0@@Z"); no body to assert in
_inline s_mod_origin_info::s_mod_origin_info(s_mod_origin_info const &__that) = default; // 0x1084CD30

// mangled_x86(MANGLED_DEFAULT, "??0s_record@c_mod_database@@QAE@$$QAU01@@Z"); no body to assert in
_inline c_mod_database::s_record::s_record(c_mod_database::s_record &&__that) = default; // 0x1084CE60

// mangled_x86(MANGLED_DEFAULT, "??0s_record@c_mod_database@@QAE@ABU01@@Z"); no body to assert in
_inline c_mod_database::s_record::s_record(c_mod_database::s_record const &__that) = default; // 0x1084CF40

// mangled_x86(MANGLED_DEFAULT, "??0s_record@c_mod_database@@QAE@XZ"); no body to assert in
_inline c_mod_database::s_record::s_record() = default; // 0x1084D060

/* ---------- private code */
