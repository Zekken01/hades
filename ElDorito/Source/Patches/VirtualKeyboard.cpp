/* ---------- headers */

#include "Patches/VirtualKeyboard.hpp"
#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "Utils/String.hpp"
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

struct lambda_1;
namespace Blam
{
	namespace Input
	{
		class VirtualKeyboard;
	}
}

namespace Utils {}
using namespace ::Utils;
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
	namespace VirtualKeyboard {}
	using namespace Patches::VirtualKeyboard;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Input {}
	using namespace Blam::Input;
}

/* ---------- constants */

/* ---------- definitions */

//class <lambda_1>
//{
//public:
//	void operator()(Blam::Input::VirtualKeyboard *) const;
//};
//static_assert(sizeof(<lambda_1>) == 1, "Invalid <lambda_1> size");

//class WebVirtualKeyboardHandler::__l2::<lambda_1>
//{
//public:
//	void operator()(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &) const;
//	<lambda_1>(WebVirtualKeyboardHandler::__l2::<lambda_1> &);
//	<lambda_1>(WebVirtualKeyboardHandler::__l2::<lambda_1> const &);
//	<lambda_1>(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
//private:
//	std::basic_string<char,std::char_traits<char>,std::allocator<char> > defaultValue; // 0x0
//public:
//	WebVirtualKeyboardHandler::__l2::<lambda_1> &operator=(WebVirtualKeyboardHandler::__l2::<lambda_1> const &);
//	~<lambda_1>(); /* compiler_generated() */
//};
//static_assert(sizeof(WebVirtualKeyboardHandler::__l2::<lambda_1>) == 28, "Invalid WebVirtualKeyboardHandler::__l2::<lambda_1> size");

/* ---------- prototypes */

namespace Patches
{
	namespace VirtualKeyboard
	{
		extern void Init();
		extern void ApplyAll();
		extern void SetKeyboardHandler(std::function<void __cdecl(Blam::Input::VirtualKeyboard *)> callback);
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern std::function<void __cdecl(Blam::Input::VirtualKeyboard *)> KeyboardHandler; // 0x124674F8
	extern Blam::Input::VirtualKeyboard *CurrentKeyboard; // 0x12467520
}
/* ---------- public code */

namespace Patches
{
	namespace VirtualKeyboard
	{
		_extern void _sub_10AEBE10();
		void Init() // 0x10AEBE10
		{
			mangled_x86(MANGLED_TODO, "?Init@VirtualKeyboard@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10AEBE10();
		}

		_extern void _sub_10AEB800();
		void ApplyAll() // 0x10AEB800
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@VirtualKeyboard@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10AEB800();
		}

		_extern void _sub_10AEBE70(std::function<void __cdecl(Blam::Input::VirtualKeyboard *)>);
		void SetKeyboardHandler(std::function<void __cdecl(Blam::Input::VirtualKeyboard *)> callback) // 0x10AEBE70
		{
			mangled_x86(MANGLED_TODO, "?SetKeyboardHandler@VirtualKeyboard@Patches@@YAXV?$function@$$A6AXPAVVirtualKeyboard@Input@Blam@@@Z@std@@@Z");
			// std::function<void __cdecl(Blam::Input::VirtualKeyboard *)> callback;
			todo("implement");
			_sub_10AEBE70(callback);
		}
	}
}

/* ---------- private code */
