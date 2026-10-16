/* ---------- headers */

#include "Modules/ModuleWeapon.hpp"
#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "ElDorito.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patches/Weapon.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
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
#include <locale>
#include <memory>
#include <ostream>
#include <regex>
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
struct real_vector3d;
namespace Modules
{
	class ModuleBase;
	class ModuleWeapon;
}
namespace Patches
{
	namespace Weapon
	{
		struct WeaponInfo;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Weapon {}
	using namespace Patches::Weapon;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

bool CommandWeaponOffset(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandWeaponOffsetReset(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandLoadWeaponsJSON(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandSaveWeaponsJSON(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandNewWeaponsJSON(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandDeleteWeaponsJSON(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandGetEquippedWeaponInfo(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandListWeaponConfigsJSON(std::vector<std::string> const &arguments, std::string &returnInfo);
real_vector3d ToOffset(std::string I, std::string J, std::string K);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	namespace hades_file_local_ModuleWeapon { extern bool (*IsMainMenu)(); } using namespace hades_file_local_ModuleWeapon; // 0x1135416C
}
using namespace hades_file_local;
/* ---------- public code */

namespace Modules
{
	ModuleWeapon::ModuleWeapon() : ModuleBase("Weapon") /* hades-mem-init: : ModuleBase(todo_result<std::string>()) */ // 0x10A25BA0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ModuleWeapon@Modules@@QAE@XZ");

		AddCommand("Offset", "weap_off", "This changes weapon offset.", eCommandFlagsNone, CommandWeaponOffset, { "Weapon Name", "I Offset", "J Offset", "K Offset" });
		AddCommand("Offset.Reset", "weap_off_res", "This resets weapon offset to default.", eCommandFlagsNone, CommandWeaponOffsetReset, { "Weapon Name" });
		VarWeaponJSON = AddVariableString("JSON.File", "weap_json_file", "The file weapon changes are saved to.", eCommandFlagsArchived, "default");
		AddCommand("JSON.Load", "weap_json_load", "This loads weapon offset.", eCommandFlagsNone, CommandLoadWeaponsJSON);
		AddCommand("JSON.Save", "weap_json_save", "This saves weapon offset.", eCommandFlagsNone, CommandSaveWeaponsJSON);
		AddCommand("JSON.New", "weap_json_new", "This creates a new weapon offset config.", eCommandFlagsNone, CommandNewWeaponsJSON);
		AddCommand("JSON.Delete", "weap_json_delete", "This delete a new weapon offset config.", eCommandFlagsNone, CommandDeleteWeaponsJSON);
		AddCommand("JSON.List", "weap_json_list", "This lists all available weapon offset configs.", CommandFlags(eCommandFlagsOmitValueInList | eCommandFlagsHidden), CommandListWeaponConfigsJSON);
		AddCommand("Equipped", "weap_equipped", "Gives info on the currently equipped weapon.", eCommandFlagsHidden, CommandGetEquippedWeaponInfo);
	}
}

namespace Patches
{
	namespace Weapon
	{
		// mangled_x86(MANGLED_DEFAULT, "??0WeaponInfo@Weapon@Patches@@QAE@XZ"); no body to assert in

		// mangled_x86(MANGLED_DEFAULT, "??1WeaponInfo@Weapon@Patches@@QAE@XZ"); no body to assert in
		// implicit: WeaponInfo::~WeaponInfo() = default; // 0x10A26580

		// mangled_x86(MANGLED_DEFAULT, "??4WeaponInfo@Weapon@Patches@@QAEAAU012@$$QAU012@@Z"); no body to assert in
		// WeaponInfo::operator=(WeaponInfo &&) is defaulted in its class (H8).
	}
}

/* ---------- private code */

bool CommandWeaponOffset(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A27430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandWeaponOffset@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (Arguments.size() < 1)
	{
		returnInfo = "Invalid argument";
		return false;
	}
	Patches::Weapon::WeaponInfo weapon;
	if (Utils::String::ToLower(Arguments[0]) == "equipped")
		weapon = Patches::Weapon::GetEquippedWeapon();
	else
	{
		std::string type = Arguments[0];
		weapon = Patches::Weapon::GetWeaponByType(type);
	}
	if (Arguments.size() != 4)
	{
		rapidjson::StringBuffer jsonBuffer;
		rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
		jsonWriter.StartObject();
		jsonWriter.Key("Type");
		jsonWriter.String(weapon.weapon_type.c_str());
		jsonWriter.Key("FirstPersonWeaponOffset");
		jsonWriter.StartArray();
		jsonWriter.String(std::to_string(weapon.offset.i).c_str());
		jsonWriter.String(std::to_string(weapon.offset.j).c_str());
		jsonWriter.String(std::to_string(weapon.offset.k).c_str());
		jsonWriter.EndArray();
		jsonWriter.EndObject();
		returnInfo = jsonBuffer.GetString();
		return true;
	}
	real_vector3d offset = ToOffset(Arguments[1], Arguments[2], Arguments[3]);
	Patches::Weapon::SetTypeOffset(weapon.weapon_type, offset);
	std::stringstream ss;
	ss << "Weapon: " << weapon.weapon_type << ", I: " << weapon.offset.i << ", J: " << weapon.offset.j << ", K: " << weapon.offset.k;
	returnInfo = ss.str();
	return true;
}

bool CommandWeaponOffsetReset(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A27BA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandWeaponOffsetReset@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (IsMainMenu())
	{
		returnInfo = "This command is unavailable at the moment, please try again when not on the mainmenu.";
		return false;
	}
	if (Arguments.size() < 1)
	{
		returnInfo = "Invalid argument";
		return false;
	}
	Patches::Weapon::WeaponInfo weapon;
	if (Utils::String::ToLower(Arguments[0]) == "equipped")
		weapon = Patches::Weapon::GetEquippedWeapon();
	else
	{
		std::string type = Arguments[0];
		weapon = Patches::Weapon::GetWeaponByType(type);
	}
	Patches::Weapon::SetTypeOffset(weapon.weapon_type, real_vector3d{ 0.0f, 0.0f, 0.0f });
	std::stringstream ss;
	ss << "Weapon: " << weapon.weapon_type << " offset reset to default.";
	returnInfo = ss.str();
	return true;
}

bool CommandLoadWeaponsJSON(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A26E70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandLoadWeaponsJSON@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	bool changeJson = false;
	if (Arguments.size() > 0)
	{
		for (auto &name : Modules::ModuleWeapon::Instance().WeaponsJSONList)
		{
			if (Arguments[0] == name)
				changeJson = true;
		}
	}
	if (changeJson)
		Modules::ModuleWeapon::Instance().VarWeaponJSON->ValueString = Arguments[0];
	std::string file = Modules::ModuleWeapon::Instance().VarWeaponJSON->ValueString;
	if (Utils::String::ToLower(file) == "default")
		Patches::Weapon::UseDefaultOffsets();
	else
		Patches::Weapon::Config::LoadJSON(file);
	returnInfo = "Weapons json loaded successfully.";
	return true;
}

bool CommandSaveWeaponsJSON(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A27390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandSaveWeaponsJSON@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (IsMainMenu())
	{
		returnInfo = "This command is unavailable at the moment, please try again when not on the mainmenu.";
		return false;
	}

	Patches::Weapon::Config::SaveJSON(Modules::ModuleWeapon::Instance().VarWeaponJSON->ValueString);

	returnInfo = "Weapons json saved successfully.";
	return true;
}

bool CommandNewWeaponsJSON(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A270E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandNewWeaponsJSON@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (IsMainMenu())
	{
		returnInfo = "This command is unavailable at the moment, please try again when not on the mainmenu.";
		return false;
	}
	if (Arguments.size() != 1)
	{
		returnInfo = "Invalid argument";
		return false;
	}
	std::string newConfigName = Arguments[0];
	if (Patches::Weapon::Config::ConfigExists(newConfigName))
	{
		returnInfo = "Config Already Exists";
		return true;
	}
	else
	{
		std::regex pattern("^[a-zA-Z0-9\\-_]+$");
		if (std::regex_match(newConfigName, pattern))
		{
			Patches::Weapon::UseDefaultOffsets();
			Patches::Weapon::Config::SaveJSON(newConfigName);
			returnInfo = "Weapons offset config saved successfully.";
			return true;
		}
		else
		{
			returnInfo = "Name must only contain letters or numbers or underscore or dash.";
			return false;
		}
	}
}

bool CommandDeleteWeaponsJSON(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A26650
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandDeleteWeaponsJSON@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (IsMainMenu())
	{
		returnInfo = "This command is unavailable at the moment, please try again when not on the mainmenu.";
		return false;
	}
	if (Arguments.size() != 1)
	{
		returnInfo = "Invalid argument";
		return false;
	}
	std::string newConfigName = Arguments[0];
	if (!Patches::Weapon::Config::ConfigExists(newConfigName))
	{
		returnInfo = "Config Doesnt Exists";
		return false;
	}
	else
	{
		std::regex pattern("^[a-zA-Z0-9\\-_]+$");
		if (std::regex_match(newConfigName, pattern))
		{
			Patches::Weapon::UseDefaultOffsets();
			if (Patches::Weapon::Config::DeleteJSON(newConfigName))
			{
				returnInfo = "Weapons offset deleted successfully.";
				return true;
			}
			else
			{
				returnInfo = "Failed to delete weapon offiset config file.";
				return true;
			}
		}
		else
		{
			returnInfo = "Name must only contain letters or numbers or underscore or dash.";
			return false;
		}
	}
}

bool CommandGetEquippedWeaponInfo(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A26960
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGetEquippedWeaponInfo@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (IsMainMenu())
	{
		returnInfo = "This command is unavailable at the moment, please try again when not on the mainmenu.";
		return false;
	}
	Patches::Weapon::WeaponInfo equippedWeapon = Patches::Weapon::GetEquippedWeapon();
	real_vector3d equippedWeaponOffset = equippedWeapon.offset;
	rapidjson::StringBuffer jsonBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
	jsonWriter.StartObject();
	jsonWriter.Key("Type");
	jsonWriter.String(equippedWeapon.weapon_type.c_str());
	jsonWriter.Key("DisplayName");
	jsonWriter.String(Patches::Weapon::GetTypeDisplayName(equippedWeapon.weapon_type).c_str());
	jsonWriter.Key("FirstPersonWeaponOffset");
	jsonWriter.StartArray();
	jsonWriter.String(std::to_string(equippedWeaponOffset.i).c_str());
	jsonWriter.String(std::to_string(equippedWeaponOffset.j).c_str());
	jsonWriter.String(std::to_string(equippedWeaponOffset.k).c_str());
	jsonWriter.EndArray();
	jsonWriter.EndObject();
	returnInfo = jsonBuffer.GetString();
	return true;
}

bool CommandListWeaponConfigsJSON(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x10A26DB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandListWeaponConfigsJSON@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	Patches::Weapon::Config::CreateList();

	for (auto &config : Modules::ModuleWeapon::Instance().WeaponsJSONList)
	{
		if (returnInfo.length() > 0)
		{
			returnInfo += ',';
		}

		returnInfo += config;
	}

	return true;
}

real_vector3d ToOffset(std::string I, std::string J, std::string K) // 0x10A27F20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ToOffset@@YA?AUreal_vector3d@@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00@Z");

	return { std::stof(I), std::stof(J), std::stof(K) };
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { namespace hades_file_local_ModuleWeapon { bool (*IsMainMenu)() = reinterpret_cast<decltype(IsMainMenu)>(0x531E90); } }
