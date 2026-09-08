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
	static _inline Pointer const Base(unsigned __int32 Offset, unsigned __int32 Stride);
	static Pointer const Rebase(std::string const &, unsigned __int32);
	static Pointer const Rebase(unsigned __int32);
private:
	void *_Pointer; // 0x0
public:
	template<typename t_arg0>
	t_arg0 Read() const;
	template<typename t_arg0>
	void Write(t_arg0 const value) const;
	template<typename t_arg0>
	void WriteFast(t_arg0 const value) const;
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

_extern void *_sub_10968590();
_inline void *GetBasePointer() // 0x10968590
{
	mangled_x86(MANGLED_TODO, "?GetBasePointer@@YAPAXXZ");
	// procedure flags: nofpo
	todo("implement");
	void * __result = _sub_10968590();
	return __result;
}

extern Pointer* _sub_10698D80(Pointer *const, void *);
_inline Pointer::Pointer(void *Pointer) // 0x10698D80
{
	mangled_x86(MANGLED_TODO, "??0Pointer@@QAE@PAX@Z");
	// void *Pointer;
	todo("implement");
	_sub_10698D80(this, Pointer);
}

extern Pointer* _sub_10698D50(Pointer *const, unsigned __int32);
_inline Pointer::Pointer(unsigned __int32 Offset) // 0x10698D50
{
	mangled_x86(MANGLED_TODO, "??0Pointer@@QAE@I@Z");
	// unsigned __int32 Offset;
	todo("implement");
	_sub_10698D50(this, Offset);
}

_inline Pointer::~Pointer() // 0x10699000
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1Pointer@@QAE@XZ");
	// Pointer *const this;
}

extern Pointer _sub_10992670(Pointer const *const, __int32 const);
_inline Pointer Pointer::operator[](__int32 const Offset) const // 0x10992670
{
	mangled_x86(MANGLED_TODO, "??APointer@@QBE?AV0@H@Z");
	// __int32 const Offset;
	todo("implement");
	Pointer __result = _sub_10992670((Pointer const *)this, Offset);
	return __result;
}

extern Pointer _sub_10699490(Pointer const *const, unsigned __int32, unsigned __int32);
_inline Pointer Pointer::operator()(unsigned __int32 Offset, unsigned __int32 Stride) const // 0x10699490
{
	mangled_x86(MANGLED_TODO, "??RPointer@@QBE?AV0@II@Z");
	// unsigned __int32 Stride;
	todo("implement");
	Pointer __result = _sub_10699490((Pointer const *)this, Offset, Stride);
	return __result;
}

_extern void _sub_10A90100(Pointer *const, Pointer);
_inline void Pointer::operator=(Pointer Pointer) // 0x10A90100
{
	mangled_x86(MANGLED_TODO, "??4Pointer@@QAEXV0@@Z");
	// Pointer Pointer;
	todo("implement");
	_sub_10A90100(this, Pointer);
}

_inline Pointer::operator void *() const // 0x108E4020
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??BPointer@@QBEPAXXZ");
	// Pointer const *const this;

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

_extern void _sub_10699F40(Pointer const *const, void const *, unsigned __int32);
_inline void Pointer::Write(void const *data, unsigned __int32 size) const // 0x10699F40
{
	mangled_x86(MANGLED_TODO, "?Write@Pointer@@QBEXPBXI@Z");
	// static ...; // 0x1069A100
	// static ...; // 0x1069A0DC
	// static ...; // 0x1069A0D4
	// Pointer const *const this;
	// void const *data;
	// unsigned __int32 size;
	// unsigned long temp;
	// unsigned long temp2;
	{
		// std::stringstream ss;
	}
	// function call : __int32 (void *, unsigned long, unsigned long, unsigned long *)
	// function call : void (char const *)
	// function call : __int32 (void *, unsigned long, unsigned long, unsigned long *)
	todo("implement");
	_sub_10699F40((Pointer const *)this, data, size);
}

_extern void _sub_1069A190(Pointer const *const, void *, bool);
_inline void Pointer::WriteCall(void *newFunction, bool isIndirect) const // 0x1069A190
{
	mangled_x86(MANGLED_TODO, "?WriteCall@Pointer@@QBEXPAX_N@Z");
	// static ...; // 0x1069A3D7
	// static ...; // 0x1069A3CF
	// static ...; // 0x1069A3CC
	// static ...; // 0x1069A390
	// static ...; // 0x1069A388
	// Pointer const *const this;
	// void *newFunction;
	// bool isIndirect;
	// unsigned __int32 JMPSize;
	// unsigned long temp;
	// __int32 patchSize;
	// unsigned long temp2;
	// unsigned char tempJMP[6];
	{
		// std::stringstream ss;
	}
	// function call : __int32 (void *, unsigned long, unsigned long, unsigned long *)
	// function call : void (char const *)
	// function call : __int32 (void *, unsigned long, unsigned long, unsigned long *)
	todo("implement");
	_sub_1069A190((Pointer const *)this, newFunction, isIndirect);
}

_extern void _sub_1069A480(Pointer const *const, void *, __int32);
_inline void Pointer::WriteJump(void *newFunction, __int32 jmpFlags) const // 0x1069A480
{
	mangled_x86(MANGLED_TODO, "?WriteJump@Pointer@@QBEXPAXH@Z");
	// static ...; // 0x1069A72A
	// static ...; // 0x1069A723
	// static ...; // 0x1069A71B
	// static ...; // 0x1069A718
	// static ...; // 0x1069A6D0
	// static ...; // 0x1069A6C8
	// Pointer const *const this;
	// void *newFunction;
	// __int32 jmpFlags;
	// unsigned __int32 JMPSize;
	// unsigned long temp;
	// unsigned __int32 patchSize;
	// unsigned char tempJE[6];
	// unsigned long temp2;
	// unsigned char tempJMP[5];
	{
		// std::stringstream ss;
	}
	// function call : __int32 (void *, unsigned long, unsigned long, unsigned long *)
	// function call : void (char const *)
	// function call : __int32 (void *, unsigned long, unsigned long, unsigned long *)
	todo("implement");
	_sub_1069A480((Pointer const *)this, newFunction, jmpFlags);
}

_extern void _sub_10A29540(Pointer const *const, void *, unsigned __int32);
_inline void Pointer::Read(void *Dest, unsigned __int32 size) const // 0x10A29540
{
	mangled_x86(MANGLED_TODO, "?Read@Pointer@@QBEXPAXI@Z");
	// unsigned __int32 size;
	todo("implement");
	_sub_10A29540((Pointer const *)this, Dest, size);
}

extern Pointer const _sub_10699CA0(unsigned __int32, unsigned __int32);
_inline Pointer const Pointer::Base(unsigned __int32 Offset, unsigned __int32 Stride) // 0x10699CA0
{
	mangled_x86(MANGLED_TODO, "?Base@Pointer@@SA?BV1@II@Z");
	// unsigned __int32 Stride;
	// static Pointer ModuleBase; // 0x11372CCC
	// static __int32 $TSS0; // 0x11372CD0
	todo("implement");
	Pointer const __result = _sub_10699CA0(Offset, Stride);
	return __result;
}

/* ---------- private code */

#endif // __POINTER_HPP__
