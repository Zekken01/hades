/* ---------- headers */

#include "Interface/ErrorDialog.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Web/Ui/ScreenLayer.hpp"
#include "Web/WebRenderHandlerGpu.hpp"

#include <Windows.h>
#include <commctrl.h>
#include <dpa_dsa.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

class ErrorDialog;
namespace
{
	struct DialogInitParams;
}

/* ---------- constants */

/* ---------- definitions */

namespace
{
	struct DialogInitParams
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > message; // 0x0
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > title; // 0x1C
		DialogInitParams(DialogInitParams &); /* compiler_generated() */
		DialogInitParams(DialogInitParams const &); /* compiler_generated() */
		DialogInitParams(); /* compiler_generated() */
		~DialogInitParams(); /* compiler_generated() */
		DialogInitParams &operator=(DialogInitParams &); /* compiler_generated() */
		DialogInitParams &operator=(DialogInitParams const &); /* compiler_generated() */
	};
	static_assert(sizeof(DialogInitParams) == 56, "Invalid DialogInitParams size");

}
/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_10787170(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
void ErrorDialog::Show(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &title, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &message) // 0x10787170
{
	mangled_x86(MANGLED_TODO, "?Show@ErrorDialog@@SAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
	// static ...; // 0x107872E4
	// static ...; // 0x107872DC
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &title;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &message;
	// std::unique_ptr<DialogInitParams,std::default_delete<DialogInitParams> > initParams;
	// HINSTANCE__ *hModule;
	// function call : HINSTANCE__ *(char const *)
	// function call : __int32 (HINSTANCE__ *, char const *, HWND__ *, __int32 (*)(HWND__ *, unsigned __int32, unsigned __int32, long), long)
	todo("implement");
	_sub_10787170(title, message);
}

/* ---------- private code */
