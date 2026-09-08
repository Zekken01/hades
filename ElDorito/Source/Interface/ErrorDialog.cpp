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
namespace hades_file_local
{
	struct DialogInitParams;
}
using namespace hades_file_local;

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct DialogInitParams
	{
		std::string message; // 0x0
		std::string title; // 0x1C
		DialogInitParams(DialogInitParams &); /* compiler_generated() */
		DialogInitParams(DialogInitParams const &); /* compiler_generated() */
		DialogInitParams(); /* compiler_generated() */
		~DialogInitParams(); /* compiler_generated() */
		DialogInitParams &operator=(DialogInitParams &); /* compiler_generated() */
		DialogInitParams &operator=(DialogInitParams const &); /* compiler_generated() */
	};
	static_assert(sizeof(DialogInitParams) == 56, "Invalid DialogInitParams size");

}
using namespace hades_file_local;
/* ---------- prototypes */

__int32 DialogProc(HWND__ *hWnd, unsigned __int32 msg, unsigned __int32 wParam, long lParam);
std::string NormalizeLineEndings(std::string input);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_10787170(std::string const &, std::string const &);
void ErrorDialog::Show(std::string const &title, std::string const &message) // 0x10787170
{
	mangled_x86(MANGLED_TODO, "?Show@ErrorDialog@@SAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
	// static ...; // 0x107872E4
	// static ...; // 0x107872DC
	// std::string const &title;
	// std::string const &message;
	// std::unique_ptr<DialogInitParams> initParams;
	// HINSTANCE__ *hModule;
	// function call : HINSTANCE__ *(char const *)
	// function call : __int32 (HINSTANCE__ *, char const *, HWND__ *, __int32 (*)(HWND__ *, unsigned __int32, unsigned __int32, long), long)
	todo("implement");
	_sub_10787170(title, message);
}

/* ---------- private code */

_extern __int32 _sub_10786D50(HWND__ *, unsigned __int32, unsigned __int32, long);
__int32 DialogProc(HWND__ *hWnd, unsigned __int32 msg, unsigned __int32 wParam, long lParam) // 0x10786D50
{
	// `anonymous-namespace'::DialogProc
	// static ...; // 0x10786F68
	// static ...; // 0x10786F60
	// HWND__ *hWnd;
	// unsigned __int32 msg;
	// unsigned __int32 wParam;
	// long lParam;
	{
		// tagRECT ec;
		// std::unique_ptr<DialogInitParams> initParams;
		// HRESULT hr;
		// __int32 const margin;
		// HICON__ *hIcon;
	}
	// function call : __int32 (unsigned __int32)
	// function call : __int32 (HWND__ *, char const *)
	// function call : __int32 (HWND__ *, __int32, char const *)
	// function call : HRESULT (HINSTANCE__ *, wchar_t const *, __int32, __int32, HICON__ **)
	// function call : long (HWND__ *, unsigned __int32, unsigned __int32, long)
	// function call : long (HWND__ *, __int32, unsigned __int32, unsigned __int32, long)
	// function call : long (HWND__ *, __int32, unsigned __int32, unsigned __int32, long)
	// function call : __int32 (tagRECT *, __int32, __int32)
	// function call : long (HWND__ *, __int32, unsigned __int32, unsigned __int32, long)
	// function call : __int32 (HWND__ *, __int32)
	// function call : __int32 (HWND__ *, __int32)
	todo("implement");
	__int32 __result = _sub_10786D50(hWnd, msg, wParam, lParam);
	return __result;
}

_inline DialogInitParams::DialogInitParams() // 0x10786AF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0DialogInitParams@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::DialogInitParams::DialogInitParams
	// DialogInitParams *const this;

	compiler_generated();
}

_inline DialogInitParams::~DialogInitParams() // 0x10786BD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1DialogInitParams@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::DialogInitParams::~DialogInitParams
	// DialogInitParams *const this;

	compiler_generated();
}

extern std::string _sub_10787040(std::string);
std::string NormalizeLineEndings(std::string input) // 0x10787040
{
	// `anonymous-namespace'::NormalizeLineEndings
	// std::string input;
	// unsigned __int32 pos;
	todo("implement");
	std::string __result = _sub_10787040(input);
	return __result;
}
