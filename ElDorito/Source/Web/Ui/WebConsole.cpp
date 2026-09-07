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
namespace
{
	class WebConsoleOutputHandler;
}

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

namespace
{
	class WebConsoleOutputHandler :
		public Console::ConsoleOutputHandler
	{
	public:
		virtual void WriteLine(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
		WebConsoleOutputHandler(WebConsoleOutputHandler &); /* compiler_generated() */
		WebConsoleOutputHandler(WebConsoleOutputHandler const &); /* compiler_generated() */
		WebConsoleOutputHandler(); /* compiler_generated() */
		virtual ~WebConsoleOutputHandler(); /* compiler_generated() */
		WebConsoleOutputHandler &operator=(WebConsoleOutputHandler &); /* compiler_generated() */
		WebConsoleOutputHandler &operator=(WebConsoleOutputHandler const &); /* compiler_generated() */
	};
	static_assert(sizeof(WebConsoleOutputHandler) == 4, "Invalid WebConsoleOutputHandler size");
}
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

			_extern void _sub_10C9DE50();
			void Show() // 0x10C9DE50
			{
				mangled_x86(MANGLED_TODO, "?Show@WebConsole@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				todo("implement");
				_sub_10C9DE50();
			}

			_extern void _sub_10C9DC90();
			void Hide() // 0x10C9DC90
			{
				mangled_x86(MANGLED_TODO, "?Hide@WebConsole@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				todo("implement");
				_sub_10C9DC90();
			}
		}
	}
}

/* ---------- private code */
