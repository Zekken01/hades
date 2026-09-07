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
	class ElModules;
	class ModuleBase;
	class ModuleCamera;
	class ModuleCheat;
	class ModuleInput;
	class ModuleScript;
	class ModuleTime;
	class ModuleUPnP;
	class ModuleWeapon;
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
	ElModules::ElModules() : ModuleBase(todo_result<std::basic_string<char,std::char_traits<char>,std::allocator<char> >>()) // 0x108BE780
	{
		mangled_x86(MANGLED_TODO, "??0ElModules@Modules@@QAE@XZ");
		// Modules::ElModules *const this;
		todo("implement");
		_sub_108BE780(this);
	}
}

/* ---------- private code */
