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

unsigned __int32 GetMainThreadId() // 0x10AF8CE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetMainThreadId@@YAIXZ");
	// procedure flags: nofpo
	// static ...; // 0x10AF8E33
	// static ...; // 0x10AF8E2C
	// static ...; // 0x10AF8E14
	// static ...; // 0x10AF8E0C
	// tagTHREADENTRY32 tEntry;
	// unsigned long currentPID;
	// unsigned long result;
	// std::shared_ptr<void> hThreadSnapshot;
		// __int32 success;
	// function call : unsigned long ()
	// function call : unsigned long ()

	const std::shared_ptr<void> hThreadSnapshot(CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0), CloseHandle);
	if( hThreadSnapshot.get() == INVALID_HANDLE_VALUE )
		return 0;

	THREADENTRY32 tEntry;
	tEntry.dwSize = sizeof(THREADENTRY32);
	DWORD result = 0;
	DWORD currentPID = GetCurrentProcessId();
	for( BOOL success = Thread32First(hThreadSnapshot.get(), &tEntry);
		!result && success && GetLastError() != ERROR_NO_MORE_FILES;
		success = Thread32Next(hThreadSnapshot.get(), &tEntry) )
	{
		if( tEntry.th32OwnerProcessID == currentPID )
			result = tEntry.th32ThreadID;
	}
	return result;
}

unsigned __int32 GetMainThreadId(unsigned __int32 ProcessId) // 0x10AF8BB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetMainThreadId@@YAII@Z");
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

	LPVOID lpTid;

	_asm
	{
		mov eax, fs:[18h]
			add eax, 36
			mov[lpTid], eax
	}

	HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, ProcessId);
	if( hProcess == NULL )
		return NULL;

	DWORD dwTid;
	if( ReadProcessMemory(hProcess, lpTid, &dwTid, sizeof(dwTid), NULL) == FALSE )
	{
		CloseHandle(hProcess);
		return NULL;
	}

	CloseHandle(hProcess);

	return dwTid;
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

void SetPageAccess(unsigned __int32 Offset, unsigned __int32 Size, unsigned __int32 AccessFlags) // 0x10AF9170
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetPageAccess@@YAXIII@Z");
	// static ...; // 0x10AF91D0
	// unsigned __int32 Offset;
	// unsigned __int32 Size;
	// unsigned __int32 AccessFlags;
	// unsigned long temp;
	// function call : __int32 (void *, unsigned long, unsigned long, unsigned long *)

	DWORD temp;

	VirtualProtect((void *)Offset, Size, AccessFlags, &temp);
}

/* ---------- private code */
