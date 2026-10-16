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

namespace Player { namespace Emblems { template <typename T> bool ParseInt(std::string_view const &str, T &value, __int32 min, __int32 max) { if (str.size() == 6) return false; T val = value; if (std::from_chars(str.data(), str.data() + str.size(), val).ec != std::errc()) return false; if (val < min || val > max) return false; value = val; return true; } } }  // hades: restored (orphaned instantiations 0x107DB9E0 char, 0x107DBB20 short, 0x107DBC60 unsigned)  // hades: added for 0x107DF190

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
		bool ParseQueryParameter(std::string_view const &str, std::string_view &name, std::string_view &value) // 0x107DF560
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ParseQueryParameter@Emblems@Player@@YA_NABV?$basic_string_view@DU?$char_traits@D@std@@@std@@AAV34@1@Z");

			__int32 separatorPos = str.find('=');
			if (separatorPos == -1)
				return false;
			name = str.substr(0, separatorPos);
			value = str.substr(separatorPos + 1);
			return true;
		}

		bool ParseQuery(std::string_view const &query, std::vector<std::pair<std::string_view,std::string_view> > &parameters) // 0x107DF3D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ParseQuery@Emblems@Player@@YA_NABV?$basic_string_view@DU?$char_traits@D@std@@@std@@AAV?$vector@U?$pair@V?$basic_string_view@DU?$char_traits@D@std@@@std@@V12@@std@@V?$allocator@U?$pair@V?$basic_string_view@DU?$char_traits@D@std@@@std@@V12@@std@@@2@@4@@Z");

			__int32 pos = 0;
			__int32 len = query.length();
			while (pos < len)
			{
				__int32 nextPos = query.find('&', pos);
				if (nextPos == -1)
					nextPos = len;
				std::string_view parameter(&query[pos], nextPos - pos);
				pos = nextPos + 1;
				std::string_view name;
				std::string_view value;
				if (ParseQueryParameter(parameter, name, value))
					parameters.push_back(std::make_pair(name, value));
			}
			return true;
		}

		bool ParseHex(std::string_view const &str, unsigned __int32 &value) // 0x107DF260
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ParseHex@Emblems@Player@@YA_NABV?$basic_string_view@DU?$char_traits@D@std@@@std@@AAI@Z");

			std::stringstream ss;
			ss << std::hex << str;
			ss >> value;
			return true;
		}

		bool ParseBool(std::string_view const &str, bool &value) // 0x107DF190
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ParseBool@Emblems@Player@@YA_NABV?$basic_string_view@DU?$char_traits@D@std@@@std@@AA_N@Z");

			char val;
			if (!ParseInt(str, val, 0, 1))
				return false;
			value = val;
			return true;
		}

		bool ParseURL(std::string const &url, s_player_emblem_configuration &config) // 0x107DF620
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ParseURL@Emblems@Player@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAUs_player_emblem_configuration@@@Z");

			Utils::Uri::UriComponents uric;
			if (!Utils::Uri::ParseUriComponents(url, uric))
				return false;
			std::vector<std::pair<std::string_view,std::string_view> > params;
			params.reserve(6);
			if (!ParseQuery(uric.query, params))
				return false;
			config = {};
			for (auto const &[name, value] : params)
			{
				if (name == "1" && !ParseInt(value, config.backgroundColor, 0, 0xFFFFFFFF))
					config.backgroundHex = ParseHex(value, config.backgroundColor);
				if (name == "2" && !ParseInt(value, config.secondaryColor, 0, 0xFFFFFFFF))
					config.secondaryHex = ParseHex(value, config.secondaryColor);
				if (name == "3" && !ParseInt(value, config.primaryColor, 0, 0xFFFFFFFF))
					config.primaryHex = ParseHex(value, config.primaryColor);
				if (name == "fi")
					ParseInt(value, config.foregroundIndex, 0, 0x7FFF);
				if (name == "bi")
					ParseInt(value, config.backgroundIndex, 0, 0x7FFF);
				if (name == "fl")
					ParseBool(value, config.iconEnabled);
			}
			return true;
		}
	}
}


namespace Player
{
	namespace Emblems
	{
		std::string HexToStrHex(__int32 hexValue) // 0x107DEE70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HexToStrHex@Emblems@Player@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z");

			__int32 red = (hexValue >> 16) & 0xFF;
			__int32 green = (hexValue >> 8) & 0xFF;
			__int32 blue = hexValue & 0xFF;
			std::stringstream hex;
			hex << std::setfill('0') << std::setw(2) << std::hex << red;
			hex << std::setfill('0') << std::setw(2) << std::hex << green;
			hex << std::setfill('0') << std::setw(2) << std::hex << blue;
			return hex.str();
		}
	}
}


namespace Player
{
	namespace Emblems
	{
		std::string BuildUrl(s_player_emblem_configuration config) // 0x107DE4E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?BuildUrl@Emblems@Player@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@Us_player_emblem_configuration@@@Z");

			std::string emblem = "emblems://emblem";
			emblem += "?1=" + (config.backgroundHex ? HexToStrHex(config.backgroundColor) : std::to_string(config.backgroundColor)) + "&2=" + (config.secondaryHex ? HexToStrHex(config.secondaryColor) : std::to_string(config.secondaryColor)) + "&3=" + (config.primaryHex ? HexToStrHex(config.primaryColor) : std::to_string(config.primaryColor)) + "&fi=" + std::to_string(config.foregroundIndex) + "&bi=" + std::to_string(config.backgroundIndex) + "&fl=" + std::to_string(config.iconEnabled);
			return emblem;
		}
	}
}

/* ---------- private code */
