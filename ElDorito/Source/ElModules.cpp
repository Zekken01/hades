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
	extern ElModules* _sub_108BE780(Modules::ElModules *const);
	ElModules::ElModules() : ModuleBase(todo_result<std::string>()) // 0x108BE780
	{
		mangled_x86(MANGLED_TODO, "??0ElModules@Modules@@QAE@XZ");
		// Modules::ElModules *const this;
		todo("implement");
		_sub_108BE780(this);
	}
}

/* ---------- private code */

_extern bool _sub_108BF6A0(std::vector<std::string> const &, std::string &);
bool CommandHelp(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x108BF6A0
{
	// `anonymous-namespace'::CommandHelp
	// static ...; // 0x108BF9B4
	// static ...; // 0x108BF99C
	// static ...; // 0x108BF994
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// Modules::CommandMap &commandMap;
	{
		// std::string cmdName;
		// Modules::Command *cmd;
		{
			// bool isModule;
			{
				// std::_Deque_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > it;
			}
		}
	}
	todo("implement");
	bool __result = _sub_108BF6A0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_108BF290(std::vector<std::string> const &, std::string &);
bool CommandExecute(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x108BF290
{
	// `anonymous-namespace'::CommandExecute
	// static ...; // 0x108BF5C0
	// static ...; // 0x108BF5A8
	// static ...; // 0x108BF5A0
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::ifstream in;
	{
		// bool stopOnFirstError;
		// std::string contents;
	}
	todo("implement");
	bool __result = _sub_108BF290(Arguments, returnInfo);
	return __result;
}

bool CommandWriteConfig(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x108BFA90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandWriteConfig@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandWriteConfig
	// static ...; // 0x108C045F
	// static ...; // 0x108C0454
	// static ...; // 0x108C044C
	// static ...; // 0x108C0442
	// static ...; // 0x108C043F
	// static ...; // 0x108C0435
	// static ...; // 0x108C0432
	// static ...; // 0x108C0428
	// static ...; // 0x108C0420
	// static ...; // 0x108C0418
	// static ...; // 0x108C0394
	// static ...; // 0x108C038C
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::wstring wide_ed_appdata;
	// std::ofstream outKeys;
	// std::string prefsFile;
	// std::string prefsName;
	// wchar_t *localAppdata;
	// std::ofstream outFile;
	// std::string ed_appdata;
	// std::string keyFile;
		// std::stringstream ss;
		// std::stringstream keystream;

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
		prefsFile = "data/" + prefsName;

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
