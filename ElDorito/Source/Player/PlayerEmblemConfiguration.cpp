/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/game/player_appearance.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Uri.hpp"

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
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <string_view>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
struct s_player_emblem_configuration;
namespace Utils
{
	namespace Uri
	{
		struct UriComponents;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace Uri {}
	using namespace Utils::Uri;
}

namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace Emblems {}
	using namespace Player::Emblems;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Player
{
	namespace Emblems
	{
		extern bool ParseQueryParameter(std::basic_string_view<char,std::char_traits<char> > const &str, std::basic_string_view<char,std::char_traits<char> > &name, std::basic_string_view<char,std::char_traits<char> > &value);
		extern bool ParseQuery(std::basic_string_view<char,std::char_traits<char> > const &query, std::vector<std::pair<std::basic_string_view<char,std::char_traits<char> >,std::basic_string_view<char,std::char_traits<char> > >,std::allocator<std::pair<std::basic_string_view<char,std::char_traits<char> >,std::basic_string_view<char,std::char_traits<char> > > > > &parameters);
		extern bool ParseHex(std::basic_string_view<char,std::char_traits<char> > const &str, unsigned __int32 &value);
		extern bool ParseBool(std::basic_string_view<char,std::char_traits<char> > const &str, bool &value);
		extern bool ParseURL(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &url, s_player_emblem_configuration &config);
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > HexToStrHex(__int32 hexValue);
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > BuildUrl(s_player_emblem_configuration config);
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Player
{
	namespace Emblems
	{
		_extern bool _sub_107DF560(std::basic_string_view<char,std::char_traits<char> > const &, std::basic_string_view<char,std::char_traits<char> > &, std::basic_string_view<char,std::char_traits<char> > &);
		bool ParseQueryParameter(std::basic_string_view<char,std::char_traits<char> > const &str, std::basic_string_view<char,std::char_traits<char> > &name, std::basic_string_view<char,std::char_traits<char> > &value) // 0x107DF560
		{
			mangled_x86(MANGLED_TODO, "?ParseQueryParameter@Emblems@Player@@YA_NABV?$basic_string_view@DU?$char_traits@D@std@@@std@@AAV34@1@Z");
			// std::basic_string_view<char,std::char_traits<char> > &value;
			// __int32 separatorPos;
			todo("implement");
			bool __result = _sub_107DF560(str, name, value);
			return __result;
		}

		_extern bool _sub_107DF3D0(std::basic_string_view<char,std::char_traits<char> > const &, std::vector<std::pair<std::basic_string_view<char,std::char_traits<char> >,std::basic_string_view<char,std::char_traits<char> > >,std::allocator<std::pair<std::basic_string_view<char,std::char_traits<char> >,std::basic_string_view<char,std::char_traits<char> > > > > &);
		bool ParseQuery(std::basic_string_view<char,std::char_traits<char> > const &query, std::vector<std::pair<std::basic_string_view<char,std::char_traits<char> >,std::basic_string_view<char,std::char_traits<char> > >,std::allocator<std::pair<std::basic_string_view<char,std::char_traits<char> >,std::basic_string_view<char,std::char_traits<char> > > > > &parameters) // 0x107DF3D0
		{
			mangled_x86(MANGLED_TODO, "?ParseQuery@Emblems@Player@@YA_NABV?$basic_string_view@DU?$char_traits@D@std@@@std@@AAV?$vector@U?$pair@V?$basic_string_view@DU?$char_traits@D@std@@@std@@V12@@std@@V?$allocator@U?$pair@V?$basic_string_view@DU?$char_traits@D@std@@@std@@V12@@std@@@2@@4@@Z");
			// static ...; // 0x107DF4F6
			// static ...; // 0x107DF4F0
			// static ...; // 0x107DF4CC
			// static ...; // 0x107DF4C4
			// std::basic_string_view<char,std::char_traits<char> > const &query;
			// std::vector<std::pair<std::basic_string_view<char,std::char_traits<char> >,std::basic_string_view<char,std::char_traits<char> > >,std::allocator<std::pair<std::basic_string_view<char,std::char_traits<char> >,std::basic_string_view<char,std::char_traits<char> > > > > &parameters;
			// __int32 pos;
			// __int32 len;
			{
				// std::basic_string_view<char,std::char_traits<char> > parameter;
				// __int32 nextPos;
				// std::basic_string_view<char,std::char_traits<char> > name;
				// std::basic_string_view<char,std::char_traits<char> > value;
			}
			todo("implement");
			bool __result = _sub_107DF3D0(query, parameters);
			return __result;
		}

		_extern bool _sub_107DF260(std::basic_string_view<char,std::char_traits<char> > const &, unsigned __int32 &);
		bool ParseHex(std::basic_string_view<char,std::char_traits<char> > const &str, unsigned __int32 &value) // 0x107DF260
		{
			mangled_x86(MANGLED_TODO, "?ParseHex@Emblems@Player@@YA_NABV?$basic_string_view@DU?$char_traits@D@std@@@std@@AAI@Z");
			// static ...; // 0x107DF374
			// static ...; // 0x107DF36C
			// std::basic_string_view<char,std::char_traits<char> > const &str;
			// unsigned __int32 &value;
			// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
			todo("implement");
			bool __result = _sub_107DF260(str, value);
			return __result;
		}

		_extern bool _sub_107DF190(std::basic_string_view<char,std::char_traits<char> > const &, bool &);
		bool ParseBool(std::basic_string_view<char,std::char_traits<char> > const &str, bool &value) // 0x107DF190
		{
			mangled_x86(MANGLED_TODO, "?ParseBool@Emblems@Player@@YA_NABV?$basic_string_view@DU?$char_traits@D@std@@@std@@AA_N@Z");
			// static ...; // 0x107DF21C
			// static ...; // 0x107DF214
			// std::basic_string_view<char,std::char_traits<char> > const &str;
			// bool &value;
			// char val;
			todo("implement");
			bool __result = _sub_107DF190(str, value);
			return __result;
		}

		_extern bool _sub_107DF620(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, s_player_emblem_configuration &);
		bool ParseURL(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &url, s_player_emblem_configuration &config) // 0x107DF620
		{
			mangled_x86(MANGLED_TODO, "?ParseURL@Emblems@Player@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAUs_player_emblem_configuration@@@Z");
			// static ...; // 0x107DFAFC
			// static ...; // 0x107DFAE4
			// static ...; // 0x107DFADC
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &url;
			// s_player_emblem_configuration &config;
			// Utils::Uri::UriComponents uric;
			// std::vector<std::pair<std::basic_string_view<char,std::char_traits<char> >,std::basic_string_view<char,std::char_traits<char> > >,std::allocator<std::pair<std::basic_string_view<char,std::char_traits<char> >,std::basic_string_view<char,std::char_traits<char> > > > > params;
			{
				// std::vector<std::pair<std::basic_string_view<char,std::char_traits<char> >,std::basic_string_view<char,std::char_traits<char> > >,std::allocator<std::pair<std::basic_string_view<char,std::char_traits<char> >,std::basic_string_view<char,std::char_traits<char> > > > > &<range>$L0;
				// std::pair<std::basic_string_view<char,std::char_traits<char> >,std::basic_string_view<char,std::char_traits<char> > > *<begin>$L0;
				// std::pair<std::basic_string_view<char,std::char_traits<char> >,std::basic_string_view<char,std::char_traits<char> > > *<end>$L0;
				{
					// std::basic_string_view<char,std::char_traits<char> > const &name;
					// std::basic_string_view<char,std::char_traits<char> > const &value;
				}
			}
			todo("implement");
			bool __result = _sub_107DF620(url, config);
			return __result;
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_107DEE70(__int32);
namespace Player
{
	namespace Emblems
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > HexToStrHex(__int32 hexValue) // 0x107DEE70
		{
			mangled_x86(MANGLED_TODO, "?HexToStrHex@Emblems@Player@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z");
			// static ...; // 0x107DF0EC
			// static ...; // 0x107DF0E0
			// static ...; // 0x107DF0D8
			// __int32 hexValue;
			// __int32 green;
			// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > hex;
			// __int32 blue;
			// __int32 red;
			todo("implement");
			std::string __result = _sub_107DEE70(hexValue);
			return __result;
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_107DE4E0(s_player_emblem_configuration);
namespace Player
{
	namespace Emblems
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > BuildUrl(s_player_emblem_configuration config) // 0x107DE4E0
		{
			mangled_x86(MANGLED_TODO, "?BuildUrl@Emblems@Player@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@Us_player_emblem_configuration@@@Z");
			// static ...; // 0x107DEC7C
			// static ...; // 0x107DEC70
			// static ...; // 0x107DEC68
			// s_player_emblem_configuration config;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > emblem;
			todo("implement");
			std::string __result = _sub_107DE4E0(config);
			return __result;
		}
	}
}

/* ---------- private code */
