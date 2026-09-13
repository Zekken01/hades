/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Scripting/HaloScript/HsMethodMap.hpp"
#include "Scripting/HaloScript/HsThreadStorage.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <initializer_list>
#include <limits>
#include <tuple>
#include <type_traits>
#include <utility>

/* ---------- forward declarations */

struct hs_value;
namespace Scripting
{
	namespace HS
	{
		class ScriptMethodMap;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Scripting {}
using namespace ::Scripting;
namespace Scripting
{
	namespace HS {}
	using namespace Scripting::HS;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Scripting
{
	namespace HS
	{
		namespace Methods
		{
			namespace Math
			{
				extern void RegisterMethods(Scripting::HS::ScriptMethodMap &methods);
			}
		}
	}
}

void hs_math_sine_evaluate(short op, long thread_index, bool initial);
void hs_math_cosine_evaluate(short op, long thread_index, bool initial);
void hs_math_tangent_evaluate(short op, long thread_index, bool initial);
void hs_math_square_root_evaluate(short op, long thread_index, bool initial);
void hs_math_absolute_evaluate(short op, long thread_index, bool initial);
void hs_math_floating_absolute_evaluate(short op, long thread_index, bool initial);
void hs_math_ceiling_evaluate(short op, long thread_index, bool initial);
void hs_math_floor_evaluate(short op, long thread_index, bool initial);
void hs_math_modulus_evaluate(short op, long thread_index, bool initial);
void hs_math_floating_modulus_evaluate(short op, long thread_index, bool initial);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Scripting
{
	namespace HS
	{
		namespace Methods
		{
			namespace Math
			{
				_extern void _sub_106807C0(Scripting::HS::ScriptMethodMap &);
				void RegisterMethods(Scripting::HS::ScriptMethodMap &methods) // 0x106807C0
				{
					mangled_x86(MANGLED_TODO, "?RegisterMethods@Math@Methods@HS@Scripting@@YAXAAVScriptMethodMap@34@@Z");
					// Scripting::HS::ScriptMethodMap &methods;
					todo("implement");
					_sub_106807C0(methods);
				}
			}
		}
	}
}

/* ---------- private code */

void hs_math_sine_evaluate(short op, long thread_index, bool initial) // 0x106819D0
{
	// `anonymous-namespace'::hs_math_sine_evaluate
	// bool initial;

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		auto input = args[0].real_value;
		auto result = sin(input);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(result));
	}
}

void hs_math_cosine_evaluate(short op, long thread_index, bool initial) // 0x10681450
{
	// `anonymous-namespace'::hs_math_cosine_evaluate
	// bool initial;

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		auto input = args[0].real_value;
		auto result = cos(input);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(result));
	}
}

void hs_math_tangent_evaluate(short op, long thread_index, bool initial) // 0x10681BB0
{
	// `anonymous-namespace'::hs_math_tangent_evaluate
	// bool initial;

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		auto input = args[0].real_value;
		auto result = tan(input);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(result));
	}
}

void hs_math_square_root_evaluate(short op, long thread_index, bool initial) // 0x10681AC0
{
	// `anonymous-namespace'::hs_math_square_root_evaluate
	// bool initial;

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		auto input = args[0].real_value;
		auto result = sqrt(input);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(result));
	}
}

void hs_math_absolute_evaluate(short op, long thread_index, bool initial) // 0x10681280
{
	// `anonymous-namespace'::hs_math_absolute_evaluate
	// bool initial;

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		auto input = args[0].long_value;
		auto result = labs(input);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_long(result));
	}
}

void hs_math_floating_absolute_evaluate(short op, long thread_index, bool initial) // 0x10681540
{
	// `anonymous-namespace'::hs_math_floating_absolute_evaluate
	// bool initial;

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		auto input = args[0].real_value;
		auto result = abs(input);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(result));
	}
}

void hs_math_ceiling_evaluate(short op, long thread_index, bool initial) // 0x10681360
{
	// `anonymous-namespace'::hs_math_ceiling_evaluate
	// bool initial;

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		auto input = args[0].real_value;
		auto result = ceil(input);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(result));
	}
}

void hs_math_floor_evaluate(short op, long thread_index, bool initial) // 0x106817B0
{
	// `anonymous-namespace'::hs_math_floor_evaluate
	// bool initial;

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		auto input = args[0].real_value;
		auto result = floor(input);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(result));
	}
}

_extern void _sub_106818A0(short, long, bool);
void hs_math_modulus_evaluate(short op, long thread_index, bool initial) // 0x106818A0
{
	// `anonymous-namespace'::hs_math_modulus_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// long input1;
			// long input2;
			// long result;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106818A0(op, thread_index, initial);
}

_extern void _sub_10681630(short, long, bool);
void hs_math_floating_modulus_evaluate(short op, long thread_index, bool initial) // 0x10681630
{
	// `anonymous-namespace'::hs_math_floating_modulus_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// float input1;
			// float input2;
			// float result;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_10681630(op, thread_index, initial);
}
