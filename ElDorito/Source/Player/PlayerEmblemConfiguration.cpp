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
		extern bool ParseQueryParameter(std::string_view const &str, std::string_view &name, std::string_view &value);
		extern bool ParseQuery(std::string_view const &query, std::vector<std::pair<std::string_view,std::string_view> > &parameters);
		extern bool ParseHex(std::string_view const &str, unsigned __int32 &value);
		extern bool ParseBool(std::string_view const &str, bool &value);
		extern bool ParseURL(std::string const &url, s_player_emblem_configuration &config);
		extern std::string HexToStrHex(__int32 hexValue);
		extern std::string BuildUrl(s_player_emblem_configuration config);
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Player
{
	namespace Emblems
	{
		_extern bool _sub_107DF560(std::string_view const &, std::string_view &, std::string_view &);
		bool ParseQueryParameter(std::string_view const &str, std::string_view &name, std::string_view &value) // 0x107DF560
		{
			mangled_x86(MANGLED_TODO, "?ParseQueryParameter@Emblems@Player@@YA_NABV?$basic_string_view@DU?$char_traits@D@std@@@std@@AAV34@1@Z");
			// std::string_view &value;
			// __int32 separatorPos;
			todo("implement");
			bool __result = _sub_107DF560(str, name, value);
			return __result;
		}

		_extern bool _sub_107DF3D0(std::string_view const &, std::vector<std::pair<std::string_view,std::string_view> > &);
		bool ParseQuery(std::string_view const &query, std::vector<std::pair<std::string_view,std::string_view> > &parameters) // 0x107DF3D0
		{
			mangled_x86(MANGLED_TODO, "?ParseQuery@Emblems@Player@@YA_NABV?$basic_string_view@DU?$char_traits@D@std@@@std@@AAV?$vector@U?$pair@V?$basic_string_view@DU?$char_traits@D@std@@@std@@V12@@std@@V?$allocator@U?$pair@V?$basic_string_view@DU?$char_traits@D@std@@@std@@V12@@std@@@2@@4@@Z");
			// static ...; // 0x107DF4F6
			// static ...; // 0x107DF4F0
			// static ...; // 0x107DF4CC
			// static ...; // 0x107DF4C4
			// std::string_view const &query;
			// std::vector<std::pair<std::string_view,std::string_view> > &parameters;
			// __int32 pos;
			// __int32 len;
			{
				// std::string_view parameter;
				// __int32 nextPos;
				// std::string_view name;
				// std::string_view value;
			}
			todo("implement");
			bool __result = _sub_107DF3D0(query, parameters);
			return __result;
		}

		_extern bool _sub_107DF260(std::string_view const &, unsigned __int32 &);
		bool ParseHex(std::string_view const &str, unsigned __int32 &value) // 0x107DF260
		{
			mangled_x86(MANGLED_TODO, "?ParseHex@Emblems@Player@@YA_NABV?$basic_string_view@DU?$char_traits@D@std@@@std@@AAI@Z");
			// static ...; // 0x107DF374
			// static ...; // 0x107DF36C
			// std::string_view const &str;
			// unsigned __int32 &value;
			// std::stringstream ss;
			todo("implement");
			bool __result = _sub_107DF260(str, value);
			return __result;
		}

		_extern bool _sub_107DF190(std::string_view const &, bool &);
		bool ParseBool(std::string_view const &str, bool &value) // 0x107DF190
		{
			mangled_x86(MANGLED_TODO, "?ParseBool@Emblems@Player@@YA_NABV?$basic_string_view@DU?$char_traits@D@std@@@std@@AA_N@Z");
			// static ...; // 0x107DF21C
			// static ...; // 0x107DF214
			// std::string_view const &str;
			// bool &value;
			// char val;
			todo("implement");
			bool __result = _sub_107DF190(str, value);
			return __result;
		}

		_extern bool _sub_107DF620(std::string const &, s_player_emblem_configuration &);
		bool ParseURL(std::string const &url, s_player_emblem_configuration &config) // 0x107DF620
		{
			mangled_x86(MANGLED_TODO, "?ParseURL@Emblems@Player@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAUs_player_emblem_configuration@@@Z");
			// static ...; // 0x107DFAFC
			// static ...; // 0x107DFAE4
			// static ...; // 0x107DFADC
			// std::string const &url;
			// s_player_emblem_configuration &config;
			// Utils::Uri::UriComponents uric;
			// std::vector<std::pair<std::string_view,std::string_view> > params;
			{
				// std::vector<std::pair<std::string_view,std::string_view> > &<range>$L0;
				// std::pair<std::string_view,std::string_view> *<begin>$L0;
				// std::pair<std::string_view,std::string_view> *<end>$L0;
				{
					// std::string_view const &name;
					// std::string_view const &value;
				}
			}
			todo("implement");
			bool __result = _sub_107DF620(url, config);
			return __result;
		}
	}
}

extern std::string _sub_107DEE70(__int32);
namespace Player
{
	namespace Emblems
	{
		std::string HexToStrHex(__int32 hexValue) // 0x107DEE70
		{
			mangled_x86(MANGLED_TODO, "?HexToStrHex@Emblems@Player@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z");
			// static ...; // 0x107DF0EC
			// static ...; // 0x107DF0E0
			// static ...; // 0x107DF0D8
			// __int32 hexValue;
			// __int32 green;
			// std::stringstream hex;
			// __int32 blue;
			// __int32 red;
			todo("implement");
			std::string __result = _sub_107DEE70(hexValue);
			return __result;
		}
	}
}

extern std::string _sub_107DE4E0(s_player_emblem_configuration);
namespace Player
{
	namespace Emblems
	{
		std::string BuildUrl(s_player_emblem_configuration config) // 0x107DE4E0
		{
			mangled_x86(MANGLED_TODO, "?BuildUrl@Emblems@Player@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@Us_player_emblem_configuration@@@Z");
			// static ...; // 0x107DEC7C
			// static ...; // 0x107DEC70
			// static ...; // 0x107DEC68
			// s_player_emblem_configuration config;
			// std::string emblem;
			todo("implement");
			std::string __result = _sub_107DE4E0(config);
			return __result;
		}
	}
}

/* ---------- private code */
