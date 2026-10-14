/* ---------- headers */

#include "Debug/DebugTrace.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/physics/havok_types.hpp"
#include "CommandMap.hpp"
#include "Common/Threading/SimpleMessageQueue.hpp"
#include "Debug/DebugDraw.hpp"
#include "Download/HttpFileDownload.hpp"
#include "Forge/Magnets.hpp"
#include "Server/Connect/ServerConnectStateHandler_AcquireMods.hpp"
#include "Utils/Singleton.hpp"

#include "Modules/ModuleDebug.hpp"  // hades: added for 0x1081E010

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <limits>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class CDebugTrace;
class _Closure_wrapper_78020310_1;
struct lambda_1;
struct lambda_typedef_cdecl;
struct lambda_typedef_fastcall;
struct lambda_typedef_stdcall;
struct lambda_typedef_vectorcall;
struct real_point2d;
namespace Modules
{
	struct Command;
}
namespace hades_file_local
{
	struct STraceLine;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	#pragma pack(push, 4)
	struct STraceLine
	{
		__int32 color; // 0x0
		char text[2048]; // 0x4
	};
	#pragma pack(pop)
	static_assert(sizeof(STraceLine) == 2052, "Invalid STraceLine size");

	struct s_buff
	{
		STraceLine elements[40]; // 0x0
		__int32 count = 0; // 0x140A0
		__int32 head = 0; // 0x140A4
		__int32 tail = 0; // 0x140A8
		void Add(STraceLine *);
		void Clear();
		s_buff(); /* compiler_generated() */
	};
}
using namespace hades_file_local;
// static_assert(sizeof(s_buff) == 82092, "Invalid s_buff size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

//class InitializeIfNeeded::__l2::<lambda_1>
//{
//public:
//	void operator()(Modules::Command const *) const;
//};
//static_assert(sizeof(InitializeIfNeeded::__l2::<lambda_1>) == 1, "Invalid InitializeIfNeeded::__l2::<lambda_1> size");

//class _Closure_wrapper_78020310_1 :
//	public CDebugTrace::Render::__l2::<lambda_1>
//{
//private:
//	typedef void (*<lambda_typedef_cdecl>)(STraceLine *);
//public:
//	void (*operator void (__cdecl *)(struct STraceLine *)() const)(STraceLine *);
//private:
//	typedef void (*<lambda_typedef_stdcall>)(STraceLine *);
//public:
//	void (*operator void (__stdcall *)(struct STraceLine *)() const)(STraceLine *);
//private:
//	typedef void (*<lambda_typedef_fastcall>)(STraceLine *);
//public:
//	void (*operator void (__fastcall *)(struct STraceLine *)() const)(STraceLine *);
//private:
//	typedef void (*<lambda_typedef_vectorcall>)(STraceLine *);
//public:
//	void (*operator void (__vectorcall *)(struct STraceLine *)() const)(STraceLine *);
//};
//static_assert(sizeof(_Closure_wrapper_78020310_1) == 1, "Invalid _Closure_wrapper_78020310_1 size");

//class CDebugTrace::Render::__l2::<lambda_1>
//{
//public:
//	void operator()(STraceLine *) const;
//};
//static_assert(sizeof(CDebugTrace::Render::__l2::<lambda_1>) == 1, "Invalid CDebugTrace::Render::__l2::<lambda_1> size");

/* ---------- prototypes */

void InitializeIfNeeded();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	s_buff buff; // 0x1168F568
	extern std::atomic<bool> initialized; // 0x116A3614
	extern std::atomic<bool> clearRequested; // 0x116A3615
	CSimpleMessageQueue<STraceLine,128> queue; // 0x116A3618
}
using namespace hades_file_local;
/* ---------- public code */

void CDebugTrace::Trace(__int32 color, char const *format, ...) // 0x1081E310
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Trace@CDebugTrace@@SAXHPBDZZ");
	// char *va;
	// STraceLine *line;

	InitializeIfNeeded();
	STraceLine *line = queue.TryToAllocate();
	#line 153 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Debug\\DebugTrace.cpp"
		assert(line || !"increase the queue size");
		#line 159 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Debug\\DebugTrace.cpp"

	va_list va;
	va_start(va, format);
	vsprintf_s(line->text, format, va);
	va_end(va);

	line->color = color;
	queue.Add(line);
}

void CDebugTrace::Render() // 0x1081E0F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Render@CDebugTrace@@SAXXZ");
	// procedure flags: nofpo
	// static ...; // 0x1081E23B
	// static ...; // 0x1081E234
	// static ...; // 0x1081E21C
	// static ...; // 0x1081E214
	// real_point2d offset;
		// bool exp;
		// __int32 i;
			// STraceLine *line;

	if (!initialized.load())
		return;
	{
		bool exp = true;
		if (clearRequested.compare_exchange_strong(exp, false))
			buff.Clear();
	}
	queue.ConsumeAll([](STraceLine *line)
	{
		std::string const &filter = Modules::ModuleDebug::Instance().VarTraceFilter->ValueString;
		if (!filter.empty() && !strstr(line->text, filter.c_str()))
			return;
		buff.Add(line);
	});
	real_point2d offset = { 50.0f, 50.0f };
	for (__int32 i = 0; i < buff.count; i++)
	{
		STraceLine *line = &buff.elements[(i + buff.tail) % buff.count];
		CDebugDrawBackend::DrawString2d(offset, line->color, 0, 1.0f, line->text);
		offset.y += 16.0f;
	}
}

/* ---------- private code */

_inline void s_buff::Add(STraceLine *line) // 0x1081DD80
{
	// `anonymous-namespace'::<unnamed-type-buff>::Add
	// STraceLine *line;

	elements[head] = *line;
	head = (head + 1) % 40;
	if (count == 40)
	{
		tail = (tail + 1) % 40;
	}
	else
	{
		count++;
	}
}

_inline void s_buff::Clear() // 0x1081DE40
{
	// `anonymous-namespace'::<unnamed-type-buff>::Clear
	// s_buff *const this;

	head = 0, tail = 0, count = 0;
}

void InitializeIfNeeded() // 0x1081E010
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?InitializeIfNeeded@@YAXXZ");
	// `anonymous-namespace'::InitializeIfNeeded
	// procedure flags: nofpo
	// static ...; // 0x1081E0BC
	// static ...; // 0x1081E0B0
	// static ...; // 0x1081E0A8
		// bool exp;

	{
		bool exp = false;
		if (!initialized.compare_exchange_strong(exp, true))
			return;
	}
	queue.Initialize();
	Utils::Singleton<Modules::CommandMap>::Instance().OnVariableUpdate([](Modules::Command const *command)
	{
		if (command == Utils::Singleton<Modules::ModuleDebug>::Instance().VarTraceFilter)
			clearRequested.store(true);
	});
}

_inline s_buff::s_buff() = default; // 0x1081DA60

/* ---------- explicit instantiations */
template _SINGLE_LIST_ENTRY * CSimpleMessageQueue<STraceLine,128>::Reversed(_SINGLE_LIST_ENTRY *);
template CSimpleMessageQueue<STraceLine,128>::CSimpleMessageQueue(); // 0x1081DAB0
template CSimpleMessageQueue<STraceLine,128>::~CSimpleMessageQueue(); // 0x1081DB80
template void CSimpleMessageQueue<STraceLine,128>::FreeElement(CSimpleMessageQueue<STraceLine,128>::SQueueEntry *); // 0x1081DE90
