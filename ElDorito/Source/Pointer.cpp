/* ---------- headers */

#include "Pointer.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Patches/CustomPackets.hpp"

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

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern unsigned __int32 GetMainThreadId();
extern unsigned __int32 GetMainThreadId(unsigned __int32 ProcessId);
extern void *GetModuleBase();
extern void *GetModuleBase(std::string const &ModuleName);
extern void SetPageAccess(unsigned __int32 Offset, unsigned __int32 Size, unsigned __int32 AccessFlags);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern unsigned __int32 _sub_10AF8CE0();
unsigned __int32 GetMainThreadId() // 0x10AF8CE0
{
	mangled_x86(MANGLED_TODO, "?GetMainThreadId@@YAIXZ");
	// procedure flags: nofpo
	// static ...; // 0x10AF8E33
	// static ...; // 0x10AF8E2C
	// static ...; // 0x10AF8E14
	// static ...; // 0x10AF8E0C
	// tagTHREADENTRY32 tEntry;
	// unsigned long currentPID;
	// unsigned long result;
	// std::shared_ptr<void> hThreadSnapshot;
	{
		// __int32 success;
	}
	// function call : unsigned long ()
	// function call : unsigned long ()
	todo("implement");
	unsigned __int32 __result = _sub_10AF8CE0();
	return __result;
}

_extern unsigned __int32 _sub_10AF8BB0(unsigned __int32);
unsigned __int32 GetMainThreadId(unsigned __int32 ProcessId) // 0x10AF8BB0
{
	mangled_x86(MANGLED_TODO, "?GetMainThreadId@@YAII@Z");
	// static ...; // 0x10AF8C96
	// static ...; // 0x10AF8C90
	// static ...; // 0x10AF8C78
	// static ...; // 0x10AF8C70
	// unsigned __int32 ProcessId;
	// unsigned long dwTid;
	// void *hProcess;
	// void *lpTid;
	// function call : void *(unsigned long, __int32, unsigned long)
	// function call : __int32 (void *, void const *, void *, unsigned long, unsigned long *)
	// function call : __int32 (void *)
	// function call : __int32 (void *)
	todo("implement");
	unsigned __int32 __result = _sub_10AF8BB0(ProcessId);
	return __result;
}

_extern void *_sub_10AF9010();
void *GetModuleBase() // 0x10AF9010
{
	mangled_x86(MANGLED_TODO, "?GetModuleBase@@YAPAXXZ");
	// procedure flags: nofpo
	// static ...; // 0x10AF9114
	// static ...; // 0x10AF9108
	// static ...; // 0x10AF9100
	// static void *Base; // 0x12467578
	{
		// void *hSnapShot;
		// __int32 bRet;
		// tagMODULEENTRY32 lpModuleEntry;
	}
	// function call : unsigned long ()
	// function call : __int32 (void *)
	todo("implement");
	void * __result = _sub_10AF9010();
	return __result;
}

_extern void *_sub_10AF8EA0(std::string const &);
void *GetModuleBase(std::string const &ModuleName) // 0x10AF8EA0
{
	mangled_x86(MANGLED_TODO, "?GetModuleBase@@YAPAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// static ...; // 0x10AF8FB8
	// static ...; // 0x10AF8FAC
	// static ...; // 0x10AF8FA4
	// std::string const &ModuleName;
	// void *hSnapShot;
	// __int32 bModule;
	// tagMODULEENTRY32 lpModuleEntry;
	// function call : unsigned long ()
	// function call : __int32 (void *)
	// function call : __int32 (void *)
	todo("implement");
	void * __result = _sub_10AF8EA0(ModuleName);
	return __result;
}

_extern void _sub_10AF9170(unsigned __int32, unsigned __int32, unsigned __int32);
void SetPageAccess(unsigned __int32 Offset, unsigned __int32 Size, unsigned __int32 AccessFlags) // 0x10AF9170
{
	mangled_x86(MANGLED_TODO, "?SetPageAccess@@YAXIII@Z");
	// static ...; // 0x10AF91D0
	// unsigned __int32 Offset;
	// unsigned __int32 Size;
	// unsigned __int32 AccessFlags;
	// unsigned long temp;
	// function call : __int32 (void *, unsigned long, unsigned long, unsigned long *)
	todo("implement");
	_sub_10AF9170(Offset, Size, AccessFlags);
}

/* ---------- private code */
