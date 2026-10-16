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

void *GetModuleBase() // 0x10AF9010
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetModuleBase@@YAPAXXZ");

	static void *Base = nullptr;
	if (!Base)
	{
		void *hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
		if (hSnapShot == INVALID_HANDLE_VALUE)
			return nullptr;
		tagMODULEENTRY32 lpModuleEntry;
		lpModuleEntry.dwSize = sizeof(tagMODULEENTRY32);
		__int32 bRet = Module32First(hSnapShot, &lpModuleEntry);
		CloseHandle(hSnapShot);
		Base = bRet ? lpModuleEntry.modBaseAddr : nullptr;
	}
	return Base;
}

void *GetModuleBase(std::string const &ModuleName) // 0x10AF8EA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetModuleBase@@YAPAXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

	void *hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
	if (hSnapShot == INVALID_HANDLE_VALUE)
		return nullptr;
	tagMODULEENTRY32 lpModuleEntry;
	lpModuleEntry.dwSize = sizeof(tagMODULEENTRY32);
	__int32 bModule = Module32First(hSnapShot, &lpModuleEntry);
	while (bModule)
	{
		if (ModuleName.compare(lpModuleEntry.szModule) == 0)
		{
			CloseHandle(hSnapShot);
			return lpModuleEntry.modBaseAddr;
		}
		bModule = Module32Next(hSnapShot, &lpModuleEntry);
	}
	CloseHandle(hSnapShot);
	return nullptr;
}

void SetPageAccess(unsigned __int32 Offset, unsigned __int32 Size, unsigned __int32 AccessFlags) // 0x10AF9170
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetPageAccess@@YAXIII@Z");

	DWORD temp;

	VirtualProtect((void *)Offset, Size, AccessFlags, &temp);
}

/* ---------- private code */
