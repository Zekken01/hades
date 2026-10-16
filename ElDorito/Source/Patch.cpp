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

Patch::Patch(unsigned __int32 Offset, std::initializer_list<unsigned char> const &Data, std::initializer_list<unsigned char> const &Reset) : Offset(Offset), Data(Data), Orig(Reset) /* hades-mem-init:  */ // 0x10A28ED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0Patch@@QAE@IABV?$initializer_list@E@std@@0@Z");
}

Patch::Patch() : // 0x10A29470
	Offset(0)
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0Patch@@QAE@XZ");
	// Patch *const this;
}

Patch::Patch(unsigned __int32 Offset, std::initializer_list<unsigned char> const &Data, Pointer base) : Offset(Offset), Data(Data) /* hades-mem-init:  */ // 0x10A29040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0Patch@@QAE@IABV?$initializer_list@E@std@@VPointer@@@Z");

	Orig.resize(Data.size());
	base(Offset, 1).Read(Orig.data(), Orig.size());
}

Patch::Patch(unsigned __int32 Offset, unsigned __int32 byteValue, unsigned __int32 numBytes, Pointer base) : Offset(Offset) /* hades-mem-init:  */ // 0x10A29240
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0Patch@@QAE@IIIVPointer@@@Z");

	Data.resize(numBytes);
	std::fill(Data.begin(), Data.end(), (unsigned char)byteValue);
	Orig.resize(Data.size());
	base(Offset, 1).Read(Orig.data(), Orig.size());
}

Hook::Hook() : Offset(0), Flags(0) /* hades-mem-init: : Flags(todo_result<__int32>()) */ // 0x10A28D50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0Hook@@QAE@XZ");

	Orig.resize(5);
	Pointer::Base(Offset).Read(Orig.data(), Orig.size());
}

Hook::Hook(unsigned __int32 Offset, void *destFunc, __int32 flags, std::initializer_list<unsigned char> Reset) : Offset(Offset), DestFunc(destFunc), Flags(flags), Orig(Reset) /* hades-mem-init: : Flags(flags) */ // 0x10A28B60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0Hook@@QAE@IPAXHV?$initializer_list@E@std@@@Z");

	if (Orig.size() <= 0)
	{
		Orig.resize((Flags & 4) ? 6 : 5);
		Pointer::Base(Offset).Read(Orig.data(), Orig.size());
	}
}

/* ---------- private code */
