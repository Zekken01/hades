/* ---------- headers */

#include "ElModules.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Console/Console.hpp"
#include "Download/DownloadStatCounter.hpp"
#include "Download/HttpFileDownload.hpp"
#include "Download/IDownload.hpp"
#include "ElDorito.hpp"
#include "Modules/ModuleBase.hpp"
#include "Modules/ModuleCamera.hpp"
#include "Modules/ModuleCheat.hpp"
#include "Modules/ModuleInput.hpp"
#include "Modules/ModuleScript.hpp"
#include "Modules/ModuleTime.hpp"
#include "Modules/ModuleUPnP.hpp"
#include "Modules/ModuleWeapon.hpp"
#include "Patch.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Pointer.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Utils/UPnP.hpp"

#include "Modules/ModuleGame.hpp"  // hades: added for 0x108BE780
#include "Modules/ModulePlayer.hpp"  // hades: added for 0x108BE780
#include "Modules/ModuleServer.hpp"  // hades: added for 0x108BE780
#include "Modules/ModuleSettings.hpp"  // hades: added for 0x108BE780
#include "Modules/ModuleGraphics.hpp"  // hades: added for 0x108BE780
#include "Modules/ModuleDebug.hpp"  // hades: added for 0x108BE780
#include "Modules/ModuleForge.hpp"  // hades: added for 0x108BE780
#include "Modules/ModuleVoIP.hpp"  // hades: added for 0x108BE780
#include "Modules/ModuleTweaks.hpp"  // hades: added for 0x108BE780
#include "Modules/ModuleCampaign.hpp"  // hades: added for 0x108BE780
#include "Modules/ModuleDownload.hpp"  // hades: added for 0x108BE780
#include "Modules/ModuleVoting.hpp"  // hades: added for 0x108BE780

#include <Windows.h>
#include <commctrl.h>
#include <dpa_dsa.h>
#include <propkeydef.h>
#include <propsys.h>
#include <shlobj_core.h>
#include <shobjidl.h>
#include <shobjidl_core.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
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
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Modules
{
	class CommandMap;
	class ElModules;
	class ModuleBase;
	class ModuleCamera;
	class ModuleCheat;
	class ModuleInput;
	class ModuleScript;
	class ModuleTime;
	class ModuleUPnP;
	class ModuleWeapon;
	struct Command;
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
namespace Download {}
using namespace ::Download;
namespace Console {}
using namespace ::Console;
namespace Http {}
using namespace ::Http;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Input {}
	using namespace Blam::Input;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

bool CommandHelp(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandExecute(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandWriteConfig(std::vector<std::string> const &Arguments, std::string &returnInfo);

/* ---------- globals */

namespace Utils
{
	Modules::ModuleWeapon *Utils::Singleton<Modules::ModuleWeapon>::m_instance; // 0x12408044
	Modules::ModuleCheat *Utils::Singleton<Modules::ModuleCheat>::m_instance; // 0x12408058
	Modules::ModuleScript *Utils::Singleton<Modules::ModuleScript>::m_instance; // 0x1240805C
	Modules::ModuleCamera *Utils::Singleton<Modules::ModuleCamera>::m_instance; // 0x12408048
	Modules::ModuleInput *Utils::Singleton<Modules::ModuleInput>::m_instance; // 0x1240804C
	Modules::ModuleTime *Utils::Singleton<Modules::ModuleTime>::m_instance; // 0x12408050
	Modules::ModuleUPnP *Utils::Singleton<Modules::ModuleUPnP>::m_instance; // 0x12408054
}

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	ElModules::ElModules() : ModuleBase("") /* hades-mem-init: : ModuleBase(todo_result<std::string>()) */ // 0x108BE780
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ElModules@Modules@@QAE@XZ");

		ModuleGame::Instance();
		ModulePlayer::Instance();
		ModuleWeapon::Instance();
		ModuleServer::Instance();
		ModuleSettings::Instance();
		ModuleCamera::Instance();
		ModuleInput::Instance();
		ModuleTime::Instance();
		ModuleGraphics::Instance();
		ModuleUPnP::Instance();
		ModuleDebug::Instance();
		ModuleForge::Instance();
		ModuleVoIP::Instance();
		ModuleTweaks::Instance();
		ModuleCampaign::Instance();
		ModuleDownload::Instance();
		ModuleCheat::Instance();
		ModuleVoting::Instance();
		ModuleScript::Instance();
		AddCommand("Help", "help", "Displays this help text", eCommandFlagsNone, CommandHelp);
		AddCommand("Execute", "exec", "Executes a list of commands", eCommandFlagsNone, CommandExecute, { "filename(string) The list of commands to execute" });
		AddCommand("WriteConfig", "config_write", "Writes the ElDewrito config file", eCommandFlagsNone, CommandWriteConfig, { "filename(string) Optional, the filename to write the config to" });
		CommandMap::Instance().FinishAddCommands();
	}
}

/* ---------- private code */

bool CommandHelp(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x108BF6A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandHelp@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	Modules::CommandMap &commandMap = Modules::CommandMap::Instance();
	if (Arguments.size() > 0)
	{
		std::string cmdName = Arguments[0];
		Modules::Command *cmd = commandMap.FindCommand(cmdName);
		if (!cmd)
		{
			bool isModule = false;
			for (auto it = commandMap.Commands.begin(); it < commandMap.Commands.end(); it++)
			{
				if (it->ModuleName.length() > 0 && !_stricmp(it->ModuleName.c_str(), cmdName.c_str()))
				{
					isModule = true;
					break;
				}
			}
			if (isModule)
				returnInfo = commandMap.GenerateHelpText(cmdName);
			else
				returnInfo = "Command/Variable not found";
			return isModule;
		}
		returnInfo = cmd->GenerateHelpText();
		return true;
	}
	returnInfo = commandMap.GenerateHelpText("");
	return true;
}

bool CommandExecute(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x108BF290
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandExecute@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (Arguments.size() <= 0)
	{
		returnInfo = "Usage: Execute <filename>";
		return false;
	}
	std::ifstream in(Arguments[0], std::ios::in | std::ios::binary);
	if (in && in.is_open())
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		bool stopOnFirstError = !(Arguments.size() >= 2 && Arguments[1] == "1");
		returnInfo = Modules::CommandMap::Instance().ExecuteCommands(contents, true, stopOnFirstError);
		return true;
	}
	returnInfo = "Unable to open file " + Arguments[0] + " for reading.";
	return false;
}

bool CommandWriteConfig(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x108BFA90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandWriteConfig@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	PWSTR localAppdata;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, NULL, NULL, &localAppdata);
	auto wide_ed_appdata = std::wstring(localAppdata);
	auto ed_appdata = Utils::String::ThinString(wide_ed_appdata);
	ed_appdata += "\\ElDewrito";

	std::string keyFile;
	std::string prefsName = "dewrito_prefs.cfg";
	if (ElDorito::Instance().GetInstanceName() != "")
	{
		std::stringstream ss;
		ss << "dewrito_prefs_" << ElDorito::Instance().GetInstanceName() << ".cfg";
		prefsName = ss.str();
		std::stringstream keystream;
		keystream << ed_appdata << "\\keys_" << ElDorito::Instance().GetInstanceName() << ".cfg";
		keyFile = keystream.str();
	}
	else
	{
		std::stringstream ss;
		ss << ed_appdata << "\\keys.cfg";
		keyFile = ss.str();
	}
	std::string prefsFile;
	if (Arguments.size() > 0)
		prefsFile = Arguments[0];
	else
		prefsFile = "data\\" + prefsName;

	std::ofstream outFile(prefsFile, std::ios::trunc);
	if (outFile.fail())
	{
		returnInfo = "Failed to write config to " + prefsFile + "!";
		return false;
	}
	outFile << Modules::CommandMap::Instance().SaveVariables();
	outFile << "\n" << Modules::ModuleInput::Instance().ExportBindings();

	std::ofstream outKeys(keyFile, std::ios::trunc);
	if (outKeys.fail())
	{
		returnInfo += "\nFailed to write keys to " + keyFile;
		return false;
	}
	outKeys << Modules::CommandMap::Instance().SaveKeys();


	returnInfo = "Wrote config to " + prefsName + "\n" + "Wrote Key File to " + keyFile;
	return true;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Modules::ModuleCamera & Utils::Singleton<Modules::ModuleCamera>::Instance();
template Modules::ModuleCheat & Utils::Singleton<Modules::ModuleCheat>::Instance();
template Modules::ModuleInput & Utils::Singleton<Modules::ModuleInput>::Instance();
template Modules::ModuleScript & Utils::Singleton<Modules::ModuleScript>::Instance();
template Modules::ModuleTime & Utils::Singleton<Modules::ModuleTime>::Instance();
template Modules::ModuleUPnP & Utils::Singleton<Modules::ModuleUPnP>::Instance();
template Modules::ModuleWeapon & Utils::Singleton<Modules::ModuleWeapon>::Instance();
