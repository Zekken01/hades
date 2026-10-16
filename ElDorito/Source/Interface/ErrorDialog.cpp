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
		DialogInitParams() = default; /* compiler_generated() */  // hades: not user-provided, so make_shared value-initializes
		~DialogInitParams(); /* compiler_generated() */
		DialogInitParams &operator=(DialogInitParams &); /* compiler_generated() */
		DialogInitParams &operator=(DialogInitParams const &); /* compiler_generated() */
	};
	static_assert(sizeof(DialogInitParams) == 56, "Invalid DialogInitParams size");

}
using namespace hades_file_local;
/* ---------- prototypes */

__int32 __stdcall DialogProc(HWND__ *hWnd, unsigned __int32 msg, unsigned __int32 wParam, long lParam);
std::string NormalizeLineEndings(std::string input);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

void ErrorDialog::Show(std::string const &title, std::string const &message) // 0x10787170
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Show@ErrorDialog@@SAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");

	HINSTANCE__ *hModule = GetModuleHandleA("mtndew.dll");
	std::unique_ptr<DialogInitParams> initParams = std::make_unique<DialogInitParams>();
	initParams->message = NormalizeLineEndings(message);
	initParams->title = title;
	DialogBoxParamA(hModule, MAKEINTRESOURCEA(101), *(HWND__ **)0x199C014, DialogProc, (long)initParams.release());
}

/* ---------- private code */

__int32 __stdcall DialogProc(HWND__ *hWnd, unsigned __int32 msg, unsigned __int32 wParam, long lParam) // 0x10786D50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DialogProc@@YGHPAUHWND__@@IIJ@Z");

	if (msg == WM_INITDIALOG)
	{
		MessageBeep(MB_ICONERROR);
		std::unique_ptr<DialogInitParams> initParams(reinterpret_cast<DialogInitParams *>(lParam));
		SetWindowTextA(hWnd, initParams->title.c_str());
		SetDlgItemTextA(hWnd, 1001, initParams->message.c_str());
		HICON hIcon;
		HRESULT hr = LoadIconWithScaleDown(nullptr, MAKEINTRESOURCEW(32513), 32, 32, &hIcon);
		SendMessageA(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
		SendDlgItemMessageA(hWnd, 1002, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
		__int32 const margin = 2;
		RECT ec = {};
		SendDlgItemMessageA(hWnd, 1001, EM_GETRECT, 0, (LPARAM)&ec);
		InflateRect(&ec, -margin, -margin);
		SendDlgItemMessageA(hWnd, 1001, EM_SETRECT, 0, (LPARAM)&ec);
		return TRUE;
	}
	else if (msg == WM_COMMAND)
	{
		if (wParam == IDOK)
		{
			EndDialog(hWnd, 0);
			return TRUE;
		}
	}
	else if (msg == WM_CLOSE)
	{
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}

// mangled_x86(MANGLED_DEFAULT, "??0DialogInitParams@hades_file_local@@QAE@XZ"); no body to assert in
// _inline DialogInitParams::DialogInitParams() = default; // 0x10786AF0  // hades: defaulted on its declaration

// mangled_x86(MANGLED_DEFAULT, "??1DialogInitParams@hades_file_local@@QAE@XZ"); no body to assert in
_inline DialogInitParams::~DialogInitParams() = default; // 0x10786BD0

std::string NormalizeLineEndings(std::string input) // 0x10787040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?NormalizeLineEndings@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V12@@Z");

	size_t pos = 0;
	while ((pos = input.find("\n", pos)) != std::string::npos)
	{
		if (pos == 0 || input[pos - 1] != '\r')
		{
			input.insert(pos, "\r");
		}
		else
		{
			pos++;
		}
	}

	return input;
}
