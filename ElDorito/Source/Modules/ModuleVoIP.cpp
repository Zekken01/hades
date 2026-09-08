/* ---------- headers */

#include "Modules/ModuleVoIP.hpp"
#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/input/input.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Modules/ModuleBase.hpp"
#include "Modules/ModuleInput.hpp"
#include "Patch.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
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
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Singleton.hpp"
#include "Web/Ui/Screen.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
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

namespace Blam
{
	namespace Input
	{
		enum KeyCode : unsigned short;
		struct BindingsTable;
	}
}
namespace Modules
{
	class ModuleBase;
	class ModuleVoIP;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Ui {}
	using namespace Web::Ui;
}

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer {}
		using namespace Web::Ui::ScreenLayer;
		namespace WebChat {}
		using namespace Web::Ui::WebChat;
	}
}

namespace Web
{
	namespace Browser {}
	using namespace Web::Browser;
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge {}
		using namespace Web::Browser::Bridge;
	}
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Core {}
	using namespace Patches::Core;
}

namespace Blam
{
	namespace Input {}
	using namespace Blam::Input;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

bool UpdateVoip(std::vector<std::string> const &Arguments, std::string &returnInfo);
void RendererStarted(char const *map);
bool VariableListenToMicrophone(std::vector<std::string> const &arguments, std::string &returnInfo);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern bool ready; // 0x124578D0
	extern bool isMainMenu; // 0x124578D1
	extern bool isChatting; // 0x124578D2
}
using namespace hades_file_local;
/* ---------- public code */

namespace Modules
{
	_extern void _sub_10A24EC0(Modules::ModuleVoIP *const);
	void ModuleVoIP::Tick() // 0x10A24EC0
	{
		mangled_x86(MANGLED_TODO, "?Tick@ModuleVoIP@Modules@@QAEXXZ");
		// static ...; // 0x10A253D0
		// static ...; // 0x10A253C4
		// static ...; // 0x10A253BC
		// Modules::ModuleVoIP *const this;
		// bool isUsingController;
		// Blam::Input::BindingsTable bindings;
		{
			// short kbmKeySecondary;
			// unsigned char *mouseButtons;
			// Blam::Input::KeyCode secondaryBind;
			// bool mousePrimary;
			// bool infocus;
			// bool mouseSeconday;
			// HWND__ *hWnd;
			// Blam::Input::KeyCode primaryBind;
			// short kbmKeyPrimary;
		}
		// function call : HWND__ *()
		// function call : short (__int32)
		// function call : short (__int32)
		todo("implement");
		_sub_10A24EC0(this);
	}

	extern ModuleVoIP* _sub_10A24050(Modules::ModuleVoIP *const);
	ModuleVoIP::ModuleVoIP() : ModuleBase(todo_result<std::string>()) // 0x10A24050
	{
		mangled_x86(MANGLED_TODO, "??0ModuleVoIP@Modules@@QAE@XZ");
		// Modules::ModuleVoIP *const this;
		todo("implement");
		_sub_10A24050(this);
	}

	_extern bool _sub_10A24D90(Modules::ModuleVoIP *const);
	bool ModuleVoIP::IsChatting() // 0x10A24D90
	{
		mangled_x86(MANGLED_TODO, "?IsChatting@ModuleVoIP@Modules@@QAE_NXZ");
		// Modules::ModuleVoIP *const this;
		todo("implement");
		bool __result = _sub_10A24D90(this);
		return __result;
	}
}

/* ---------- private code */

_extern bool _sub_10A25520(std::vector<std::string> const &, std::string &);
bool UpdateVoip(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10A25520
{
	// `anonymous-namespace'::UpdateVoip
	// static ...; // 0x10A257F8
	// static ...; // 0x10A257E0
	// static ...; // 0x10A257D8
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	todo("implement");
	bool __result = _sub_10A25520(Arguments, returnInfo);
	return __result;
}

_extern void _sub_10A24DC0(char const *);
void RendererStarted(char const *map) // 0x10A24DC0
{
	// `anonymous-namespace'::RendererStarted
	// char const *map;
	todo("implement");
	_sub_10A24DC0(map);
}

_extern bool _sub_10A258C0(std::vector<std::string> const &, std::string &);
bool VariableListenToMicrophone(std::vector<std::string> const &arguments, std::string &returnInfo) // 0x10A258C0
{
	// `anonymous-namespace'::VariableListenToMicrophone
	// static ...; // 0x10A25A5C
	// static ...; // 0x10A25A44
	// static ...; // 0x10A25A3C
	// std::vector<std::string> const &arguments;
	// std::string &returnInfo;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	todo("implement");
	bool __result = _sub_10A258C0(arguments, returnInfo);
	return __result;
}
