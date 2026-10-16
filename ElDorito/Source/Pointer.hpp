#ifndef __POINTER_HPP__
#define __POINTER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Modules/ModuleBase.hpp"

#include <memory>
#include <sstream>
#include <string>

/* ---------- forward declarations */

class Pointer;
namespace Modules
{
	class ModuleBase;
}

/* ---------- constants */

enum class HookFlags
{
	None = 0, // 0x0000
	IsCall = 1, // 0x0001
	IsIndirectCall = 2, // 0x0002
	IsJmpIfEqual = 4, // 0x0004
	IsJmpIfNotEqual = 8, // 0x0008
};

/* ---------- definitions */

class Pointer
{
public:
	_inline Pointer(unsigned __int32 Offset);
	_inline Pointer(void *Pointer);
	Pointer();
	_inline ~Pointer();
	_inline Pointer operator[](__int32 const Offset) const;
	Pointer operator()(unsigned __int32, unsigned __int32) const;
	Pointer &operator+(unsigned __int32);
	_inline void operator=(Pointer Pointer);
	_inline operator void *() const;
	operator bool() const;
	_inline void Write(void const *data, unsigned __int32 size) const;
	_inline void WriteCall(void *newFunction, bool isIndirect) const;
	_inline void WriteJump(void *newFunction, __int32 jmpFlags) const;
	_inline void Read(void *Dest, unsigned __int32 size) const;
	static Pointer const Base(std::string const &, unsigned __int32, unsigned __int32);
	static _inline Pointer const Base(unsigned __int32 Offset = 0, unsigned __int32 Stride = 1);  /* hades: default from 0.6.1 */
	static Pointer const Rebase(std::string const &, unsigned __int32);
	static Pointer const Rebase(unsigned __int32);
private:
	void *_Pointer; // 0x0
public:
	template<typename t_arg0>
	t_arg0 &Read() const;
	template<typename t_arg0>
	void Write(t_arg0 const value) const;
	template<typename t_arg0>
	void WriteFast(t_arg0 const value) const;
	template<typename t_arg0>
	operator t_arg0 *() const;
};
static_assert(sizeof(Pointer) == 4, "Invalid Pointer size");

/* ---------- prototypes */

extern unsigned __int32 GetMainThreadId();
extern unsigned __int32 GetMainThreadId(unsigned __int32 ProcessId);
extern void *GetModuleBase();
extern void *GetModuleBase(std::string const &ModuleName);
extern void SetPageAccess(unsigned __int32 Offset, unsigned __int32 Size, unsigned __int32 AccessFlags);

extern _inline void *GetBasePointer();

/* ---------- globals */

/* ---------- public code */

template<typename t_arg0>
_inline t_arg0 &Pointer::Read() const
{
	mangled_prefix_assert("??$Read@");

	return *(t_arg0 *)_Pointer;
}

template<typename t_arg0>
_inline void Pointer::WriteFast(t_arg0 const value) const
{
	mangled_prefix_assert("??$WriteFast@");

	*(t_arg0 *)_Pointer = value;
}

template<typename t_arg0>
_inline Pointer::operator t_arg0 *() const
{
	mangled_prefix_assert("??$?B");

	return (t_arg0 *)_Pointer;
}

inline void *GetBasePointer() // 0x10968590
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetBasePointer@@YAPAXXZ");

	return GetModuleBase();
}

inline Pointer::Pointer(void *Pointer) // 0x10698D80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0Pointer@@QAE@PAX@Z");

	_Pointer = Pointer;
}

inline Pointer::Pointer(unsigned __int32 Offset) // 0x10698D50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0Pointer@@QAE@I@Z");

	_Pointer = (void *)Offset;
}

inline Pointer::~Pointer() // 0x10699000
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1Pointer@@QAE@XZ");
}

inline Pointer Pointer::operator[](__int32 const Offset) const // 0x10992670
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??APointer@@QBE?AV0@H@Z");

	if (_Pointer != nullptr && (char *)_Pointer + Offset != nullptr)
	{
		return Pointer(*(unsigned int *)((char *)_Pointer + Offset));
	}
	return Pointer(nullptr);
}

inline Pointer Pointer::operator()(unsigned __int32 Offset, unsigned __int32 Stride) const // 0x10699490
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??RPointer@@QBE?AV0@II@Z");

	return Pointer((void *)((char *)_Pointer + Offset * Stride));
}

inline void Pointer::operator=(Pointer Pointer) // 0x10A90100
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??4Pointer@@QAEXV0@@Z");

	_Pointer = Pointer._Pointer;
}

inline Pointer::operator void *() const // 0x108E4020
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??BPointer@@QBEPAXXZ");

	return _Pointer;
}

template<typename t_arg0>
_inline void Pointer::Write(t_arg0 const value) const
{
	mangled_prefix_assert("??$Write@");

	DWORD temp;
	DWORD temp2;
	if (!VirtualProtect(_Pointer, sizeof(t_arg0), PAGE_READWRITE, &temp))
	{
		std::stringstream ss;
		ss << "Failed to set protection on memory address " << std::hex << _Pointer;
		OutputDebugString(ss.str().c_str());
		return;
	}
	*((t_arg0 *)_Pointer) = value;
	VirtualProtect(_Pointer, sizeof(t_arg0), temp, &temp2);
}

inline void Pointer::Write(void const *data, unsigned __int32 size) const // 0x10699F40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Write@Pointer@@QBEXPBXI@Z");

	unsigned long temp;
	unsigned long temp2;
	if (!VirtualProtect(_Pointer, size, PAGE_READWRITE, &temp))
	{
		std::stringstream ss;
		ss << "Failed to set protection on memory address " << std::hex << _Pointer;
		OutputDebugStringA(ss.str().c_str());
		return;
	}
	memcpy(_Pointer, data, size);
	VirtualProtect(_Pointer, size, temp, &temp2);
}

inline void Pointer::WriteCall(void *newFunction, bool isIndirect) const // 0x1069A190
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?WriteCall@Pointer@@QBEXPAX_N@Z");

	unsigned long temp;
	unsigned long temp2;
	unsigned char tempJMP[6] = { 0xE8, 0x90, 0x90, 0x90, 0x90, 0x90 };
	__int32 patchSize = isIndirect ? 6 : 5;
	unsigned __int32 JMPSize = (unsigned __int32)newFunction - (unsigned __int32)_Pointer - 5;
	if (!VirtualProtect(_Pointer, 5, PAGE_READWRITE, &temp))
	{
		std::stringstream ss;
		ss << "Failed to set protection on memory address " << std::hex << _Pointer;
		OutputDebugStringA(ss.str().c_str());
		return;
	}
	memcpy(&tempJMP[1], &JMPSize, 4);
	memcpy(_Pointer, tempJMP, patchSize);
	VirtualProtect(_Pointer, patchSize, temp, &temp2);
}

inline void Pointer::WriteJump(void *newFunction, __int32 jmpFlags) const // 0x1069A480
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?WriteJump@Pointer@@QBEXPAXH@Z");

	unsigned long temp;
	unsigned long temp2;
	unsigned char tempJMP[5] = { 0xE9, 0x90, 0x90, 0x90, 0x90 };
	unsigned char tempJE[6] = { 0x0F, 0x84, 0x90, 0x90, 0x90, 0x90 };
	unsigned __int32 patchSize = (jmpFlags & 4) ? 6 : 5;
	unsigned __int32 JMPSize = (unsigned __int32)newFunction - (unsigned __int32)_Pointer - patchSize;
	if (!VirtualProtect(_Pointer, patchSize, PAGE_READWRITE, &temp))
	{
		std::stringstream ss;
		ss << "Failed to set protection on memory address " << std::hex << _Pointer;
		OutputDebugStringA(ss.str().c_str());
		return;
	}
	if (jmpFlags & 4)
	{
		memcpy(&tempJE[2], &JMPSize, 4);
		memcpy(_Pointer, tempJE, 6);
	}
	else
	{
		memcpy(&tempJMP[1], &JMPSize, 4);
		memcpy(_Pointer, tempJMP, 5);
	}
	VirtualProtect(_Pointer, patchSize, temp, &temp2);
}

inline void Pointer::Read(void *Dest, unsigned __int32 size) const // 0x10A29540
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Read@Pointer@@QBEXPAXI@Z");

	memcpy(Dest, _Pointer, size);
}

inline Pointer const Pointer::Base(unsigned __int32 Offset, unsigned __int32 Stride) // 0x10699CA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Base@Pointer@@SA?BV1@II@Z");

	static Pointer const ModuleBase(GetModuleBase());
	return ModuleBase(Offset, Stride);
}

/* ---------- private code */

#endif // __POINTER_HPP__
