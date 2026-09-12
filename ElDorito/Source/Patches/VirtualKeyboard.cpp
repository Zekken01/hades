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
namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer
		{
			struct SDialogShowParams;
		}
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
//	void operator()(std::string const &) const;
//	<lambda_1>(WebVirtualKeyboardHandler::__l2::<lambda_1> &);
//	<lambda_1>(WebVirtualKeyboardHandler::__l2::<lambda_1> const &);
//	<lambda_1>(std::string const &);
//private:
//	std::string defaultValue; // 0x0
//public:
//	WebVirtualKeyboardHandler::__l2::<lambda_1> &operator=(WebVirtualKeyboardHandler::__l2::<lambda_1> const &);
//	~<lambda_1>(); /* compiler_generated() */
//};
//static_assert(sizeof(WebVirtualKeyboardHandler::__l2::<lambda_1>) == 28, "Invalid WebVirtualKeyboardHandler::__l2::<lambda_1> size");

/* ---------- prototypes */

Blam::Input::VirtualKeyboard *CreateVirtualKeyboard(char const *file, __int32 line, __int32 unk2, __int32 unk3, __int32 unk4, __int32 unk5, __int32 maxLength, __int32 unk7, __int32 unk8);

void __fastcall SetVirtualKeyboardDefaultValue(Blam::Input::VirtualKeyboard *keyboard, void *unused, wchar_t *newDefaultValue);
void __fastcall SetVirtualKeyboardTitle(Blam::Input::VirtualKeyboard *keyboard, void *unused, wchar_t *newTitle);
void __fastcall SetVirtualKeyboardDescription(Blam::Input::VirtualKeyboard *keyboard, void *unused, wchar_t *newDescription);
bool ShowVirtualKeyboard(Blam::Input::VirtualKeyboard *keyboard, char const *file, __int32 line);
void WebVirtualKeyboardHandler(Blam::Input::VirtualKeyboard *keyboard);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern std::function<void __cdecl(Blam::Input::VirtualKeyboard *)> KeyboardHandler; // 0x124674F8
	extern Blam::Input::VirtualKeyboard *CurrentKeyboard; // 0x12467520
}
using namespace hades_file_local;
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

		void ApplyAll() // 0x10AEB800
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@VirtualKeyboard@Patches@@YAXXZ");
			// procedure flags: nofpo

			// Implement virtual keyboard stubs
			Hook(0xE1840, CreateVirtualKeyboard).Apply();
			Hook(0xE19A0, SetVirtualKeyboardDefaultValue).Apply();
			Hook(0xE19D0, SetVirtualKeyboardTitle).Apply();
			Hook(0xE19B0, SetVirtualKeyboardDescription).Apply();
			Hook(0x1A8F40, ShowVirtualKeyboard).Apply();
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

//_extern void _sub_10AEB510(<lambda_1> const *const, Blam::Input::VirtualKeyboard *);
//_inline void <lambda_1>::operator()(Blam::Input::VirtualKeyboard *keyboard) const // 0x10AEB510
//{
//	// `anonymous-namespace'::<lambda_1>::operator()
//	// Blam::Input::VirtualKeyboard *keyboard;
//	// function call : void ()
//	todo("implement");
//	_sub_10AEB510(this, keyboard);
//}

extern Blam::Input::VirtualKeyboard *_sub_10AEBD00(char const *, __int32, __int32, __int32, __int32, __int32, __int32, __int32, __int32);
Blam::Input::VirtualKeyboard *CreateVirtualKeyboard(char const *file, __int32 line, __int32 unk2, __int32 unk3, __int32 unk4, __int32 unk5, __int32 maxLength, __int32 unk7, __int32 unk8) // 0x10AEBD00
{
	// `anonymous-namespace'::CreateVirtualKeyboard
	// __int32 unk8;
	todo("implement");
	Blam::Input::VirtualKeyboard * __result = _sub_10AEBD00(file, line, unk2, unk3, unk4, unk5, maxLength, unk7, unk8);
	return __result;
}

void __fastcall SetVirtualKeyboardDefaultValue(Blam::Input::VirtualKeyboard *keyboard, void *unused, wchar_t *newDefaultValue) // 0x10AEBF10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetVirtualKeyboardDefaultValue@@YIXPAVVirtualKeyboard@Input@Blam@@PAXPA_W@Z");
	// `anonymous-namespace'::SetVirtualKeyboardDefaultValue
	// wchar_t *newDefaultValue;

	keyboard->SetDefaultValue(newDefaultValue);
}

void __fastcall SetVirtualKeyboardTitle(Blam::Input::VirtualKeyboard *keyboard, void *unused, wchar_t *newTitle) // 0x10AEBFD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetVirtualKeyboardTitle@@YIXPAVVirtualKeyboard@Input@Blam@@PAXPA_W@Z");
	// `anonymous-namespace'::SetVirtualKeyboardTitle
	// wchar_t *newTitle;

	keyboard->SetTitle(newTitle);
}

void __fastcall SetVirtualKeyboardDescription(Blam::Input::VirtualKeyboard *keyboard, void *unused, wchar_t *newDescription) // 0x10AEBF70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetVirtualKeyboardDescription@@YIXPAVVirtualKeyboard@Input@Blam@@PAXPA_W@Z");
	// `anonymous-namespace'::SetVirtualKeyboardDescription
	// wchar_t *newDescription;

	keyboard->SetDescription(newDescription);
}

bool ShowVirtualKeyboard(Blam::Input::VirtualKeyboard *keyboard, char const *file, __int32 line) // 0x10AEC030
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ShowVirtualKeyboard@@YA_NPAVVirtualKeyboard@Input@Blam@@PBDH@Z");
	// `anonymous-namespace'::ShowVirtualKeyboard
	// __int32 line;

	KeyboardHandler(keyboard);
	return true;
}

_extern void _sub_10AEC080(Blam::Input::VirtualKeyboard *);
void WebVirtualKeyboardHandler(Blam::Input::VirtualKeyboard *keyboard) // 0x10AEC080
{
	// `anonymous-namespace'::WebVirtualKeyboardHandler
	// static ...; // 0x10AEC335
	// static ...; // 0x10AEC329
	// static ...; // 0x10AEC31C
	// static ...; // 0x10AEC30F
	// static ...; // 0x10AEC308
	// static ...; // 0x10AEC2CC
	// static ...; // 0x10AEC2C4
	// Blam::Input::VirtualKeyboard *keyboard;
	// Web::Ui::ScreenLayer::SDialogShowParams params;
	// std::string defaultValue;
	// std::string description;
	// std::string templateName;
	// std::string title;
	todo("implement");
	_sub_10AEC080(keyboard);
}
