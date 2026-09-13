/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/input/input.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Console/Console.hpp"
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
#include "Web/Ui/Screen.hpp"
#include "Web/Ui/ScreenLayer.hpp"
#include "Web/Ui/WebMods.hpp"

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
#include <limits>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

namespace Console
{
	class ConsoleOutputHandler;
}
namespace hades_file_local
{
	class WebConsoleOutputHandler;
}
using namespace hades_file_local;

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
		namespace WebConsole {}
		using namespace Web::Ui::WebConsole;
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
	namespace Input {}
	using namespace Patches::Input;
}

namespace Console {}
using namespace ::Console;
namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	class WebConsoleOutputHandler :
		public Console::ConsoleOutputHandler
	{
	public:
		virtual void WriteLine(std::string const &);
		WebConsoleOutputHandler(WebConsoleOutputHandler &); /* compiler_generated() */
		WebConsoleOutputHandler(WebConsoleOutputHandler const &); /* compiler_generated() */
		WebConsoleOutputHandler(); /* compiler_generated() */
		virtual ~WebConsoleOutputHandler() = default; /* compiler_generated() */
		WebConsoleOutputHandler &operator=(WebConsoleOutputHandler &); /* compiler_generated() */
		WebConsoleOutputHandler &operator=(WebConsoleOutputHandler const &); /* compiler_generated() */
	};
	static_assert(sizeof(WebConsoleOutputHandler) == 4, "Invalid WebConsoleOutputHandler size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Web
{
	namespace Ui
	{
		namespace WebConsole
		{
			extern void Init();
			extern void Show();
			extern void Hide();
		}
	}
}

void OnGameInputUpdated();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Web
{
	namespace Ui
	{
		namespace WebConsole
		{
			_extern void _sub_10C9DCE0();
			void Init() // 0x10C9DCE0
			{
				mangled_x86(MANGLED_TODO, "?Init@WebConsole@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				todo("implement");
				_sub_10C9DCE0();
			}

			void Show() // 0x10C9DE50
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Show@WebConsole@Ui@Web@@YAXXZ");
				// procedure flags: nofpo

				ScreenLayer::Show(ScreenLayer::Console, "{}");
			}

			void Hide() // 0x10C9DC90
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Hide@WebConsole@Ui@Web@@YAXXZ");
				// procedure flags: nofpo

				ScreenLayer::Hide(ScreenLayer::Console);
			}
		}
	}
}

/* ---------- private code */

void WebConsoleOutputHandler::WriteLine(std::string const &line) // 0x10C9DF20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?WriteLine@WebConsoleOutputHandler@hades_file_local@@UAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::WebConsoleOutputHandler::WriteLine
	// static ...; // 0x10C9E098
	// static ...; // 0x10C9E080
	// static ...; // 0x10C9E078
	// WebConsoleOutputHandler *const this;
	// std::string const &line;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;

	// Create a JSON object with the line
	rapidjson::StringBuffer jsonBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
	jsonWriter.StartObject();
	jsonWriter.Key("line");
	jsonWriter.String(line.c_str());
	jsonWriter.EndObject();

	// Broadcast a "console" event to all screens
	Web::Ui::ScreenLayer::Notify("console", jsonBuffer.GetString(), true);
}

_extern void _sub_10C9DDE0();
void OnGameInputUpdated() // 0x10C9DDE0
{
	// `anonymous-namespace'::OnGameInputUpdated
	// procedure flags: nofpo
	todo("implement");
	_sub_10C9DDE0();
}

// mangled_x86(MANGLED_DEFAULT, "??0WebConsoleOutputHandler@hades_file_local@@QAE@XZ"); no body to assert in
_inline WebConsoleOutputHandler::WebConsoleOutputHandler() = default; // 0x10C9DA50

