#ifndef __COMMON_HTTP_WINHTTP_WINHTTPCOMMON_HPP__
#define __COMMON_HTTP_WINHTTP_WINHTTPCOMMON_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

namespace Http
{
	struct WinHttpErrorCategory;
	struct WinHttpHandlerDeleter;
}

/* ---------- constants */

/* ---------- definitions */

namespace Http
{
	struct WinHttpErrorCategory :
		public std::error_category
	{
		static _inline Http::WinHttpErrorCategory &Get();
		virtual _inline char const *name() const noexcept;
		virtual _inline std::string message(__int32 error) const;
		_inline WinHttpErrorCategory(); /* compiler_generated() */
		virtual _inline ~WinHttpErrorCategory() = default; /* compiler_generated() */ // 0x10807760
	};
	static_assert(sizeof(Http::WinHttpErrorCategory) == 8, "Invalid Http::WinHttpErrorCategory size");

	struct WinHttpHandlerDeleter
	{
		void operator()(void *);
	};
	static_assert(sizeof(Http::WinHttpHandlerDeleter) == 1, "Invalid Http::WinHttpHandlerDeleter size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Http
{
	extern WinHttpErrorCategory &_sub_10808960();
	_inline Http::WinHttpErrorCategory &WinHttpErrorCategory::Get() // 0x10808960
	{
		mangled_x86(MANGLED_TODO, "?Get@WinHttpErrorCategory@Http@@SAAAU12@XZ");
		// procedure flags: nofpo
		// static Http::WinHttpErrorCategory instance; // 0x1138F43C
		// static __int32 $TSS0; // 0x1138F448
		todo("implement");
		Http::WinHttpErrorCategory & __result = _sub_10808960();
		return __result;
	}
}

extern char const *_sub_1080C0F0(Http::WinHttpErrorCategory const *const);
namespace Http
{
	_inline char const *WinHttpErrorCategory::name() const noexcept // 0x1080C0F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?name@WinHttpErrorCategory@Http@@UBEPBDXZ");
		// Http::WinHttpErrorCategory const *const this;

		return "WinHttp";
	}
}

extern std::string _sub_1080BE40(Http::WinHttpErrorCategory const *const, __int32);
namespace Http
{
	_inline std::string WinHttpErrorCategory::message(__int32 error) const // 0x1080BE40
	{
		mangled_x86(MANGLED_TODO, "?message@WinHttpErrorCategory@Http@@UBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z");
		// static ...; // 0x1080C054
		// static ...; // 0x1080C03C
		// static ...; // 0x1080C034
		// Http::WinHttpErrorCategory const *const this;
		// __int32 error;
		// char *buffer;
		// std::string result;
		// HINSTANCE__ *hInst;
		// unsigned long dwChars;
		// function call : HINSTANCE__ *(char const *)
		// function call : unsigned long (unsigned long, void const *, unsigned long, unsigned long, char *, unsigned long, char **)
		// function call : void *(void *)
		todo("implement");
		std::string __result = _sub_1080BE40((Http::WinHttpErrorCategory const *)this, error);
		return __result;
	}

	_inline void WinHttpHandlerDeleter::operator()(void *handle) // 0x107F71C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??RWinHttpHandlerDeleter@Http@@QAEXPAX@Z");
		// void *handle;
		// function call : __int32 (void *)

		WinHttpCloseHandle(handle);
	}
}

/* ---------- private code */

#endif // __COMMON_HTTP_WINHTTP_WINHTTPCOMMON_HPP__
