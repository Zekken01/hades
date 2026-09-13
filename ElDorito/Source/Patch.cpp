/* ---------- headers */

#include "Patch.hpp"
#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Pointer.hpp"

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
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class Hook;
class Patch;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern Patch* _sub_10A28ED0(Patch *const, unsigned __int32, std::initializer_list<unsigned char> const &, std::initializer_list<unsigned char> const &);
Patch::Patch(unsigned __int32 Offset, std::initializer_list<unsigned char> const &Data, std::initializer_list<unsigned char> const &Reset) // 0x10A28ED0
{
	mangled_x86(MANGLED_TODO, "??0Patch@@QAE@IABV?$initializer_list@E@std@@0@Z");
	// std::initializer_list<unsigned char> const &Reset;
	todo("implement");
	_sub_10A28ED0(this, Offset, Data, Reset);
}

Patch::Patch() // 0x10A29470
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0Patch@@QAE@XZ");
	// Patch *const this;

	Offset = 0;
}

extern Patch* _sub_10A29040(Patch *const, unsigned __int32, std::initializer_list<unsigned char> const &, Pointer);
Patch::Patch(unsigned __int32 Offset, std::initializer_list<unsigned char> const &Data, Pointer base) // 0x10A29040
{
	mangled_x86(MANGLED_TODO, "??0Patch@@QAE@IABV?$initializer_list@E@std@@VPointer@@@Z");
	// Pointer base;
	todo("implement");
	_sub_10A29040(this, Offset, Data, base);
}

extern Patch* _sub_10A29240(Patch *const, unsigned __int32, unsigned __int32, unsigned __int32, Pointer);
Patch::Patch(unsigned __int32 Offset, unsigned __int32 byteValue, unsigned __int32 numBytes, Pointer base) // 0x10A29240
{
	mangled_x86(MANGLED_TODO, "??0Patch@@QAE@IIIVPointer@@@Z");
	// Pointer base;
	todo("implement");
	_sub_10A29240(this, Offset, byteValue, numBytes, base);
}

Hook::Hook() : Offset(0), Flags(0) /* hades-mem-init: : Flags(todo_result<__int32>()) */ // 0x10A28D50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0Hook@@QAE@XZ");
	// Hook *const this;

	Orig.resize(5);
	Pointer::Base(Offset).Read(Orig.data(), Orig.size());
}

extern Hook* _sub_10A28B60(Hook *const, unsigned __int32, void *, __int32, std::initializer_list<unsigned char>);
Hook::Hook(unsigned __int32 Offset, void *destFunc, __int32 flags, std::initializer_list<unsigned char> Reset) : Flags(flags) // 0x10A28B60
{
	mangled_x86(MANGLED_TODO, "??0Hook@@QAE@IPAXHV?$initializer_list@E@std@@@Z");
	// std::initializer_list<unsigned char> Reset;
	todo("implement");
	_sub_10A28B60(this, Offset, destFunc, flags, Reset);
}

/* ---------- private code */
