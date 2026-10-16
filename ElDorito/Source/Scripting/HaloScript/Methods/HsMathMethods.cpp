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
				void RegisterMethods(Scripting::HS::ScriptMethodMap &methods) // 0x106807C0
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterMethods@Math@Methods@HS@Scripting@@YAXAAVScriptMethodMap@34@@Z");

					methods.AddMethod("math_sine", "Math operation for Sine", NetworkSafe, hs_math_sine_evaluate, _hs_type_real, { { _hs_type_real, "input", "input" } });
					methods.AddMethod("math_cosine", "Math operation for cosine", NetworkSafe, hs_math_cosine_evaluate, _hs_type_real, { { _hs_type_real, "input", "input" } });
					methods.AddMethod("math_tangent", "Math operation for tangent", NetworkSafe, hs_math_tangent_evaluate, _hs_type_real, { { _hs_type_real, "input", "input" } });
					methods.AddMethod("math_square_root", "Math operation for square root", NetworkSafe, hs_math_square_root_evaluate, _hs_type_real, { { _hs_type_real, "input", "input" } });
					methods.AddMethod("math_absolute", "Math operation for absolute", NetworkSafe, hs_math_absolute_evaluate, _hs_type_long, { { _hs_type_long, "input", "input" } });
					methods.AddMethod("math_floating_absolute", "Math operation for a floating absolute", NetworkSafe, hs_math_floating_absolute_evaluate, _hs_type_real, { { _hs_type_real, "input", "input" } });
					methods.AddMethod("math_ceiling", "Math operation for ceiling", NetworkSafe, hs_math_ceiling_evaluate, _hs_type_real, { { _hs_type_real, "input", "input" } });
					methods.AddMethod("math_floor", "Math operation for floor", NetworkSafe, hs_math_floor_evaluate, _hs_type_real, { { _hs_type_real, "input", "input" } });
					methods.AddMethod("math_modulus", "Math operation for modulus", NetworkSafe, hs_math_modulus_evaluate, _hs_type_long, { { _hs_type_long, "numerator", "input" }, { _hs_type_long, "denominator", "input" } });
					methods.AddMethod("math_floating_modulus", "Math operation for a floating modulus", NetworkSafe, hs_math_floating_modulus_evaluate, _hs_type_real, { { _hs_type_real, "numerator", "input" }, { _hs_type_real, "denominator", "input" } });
				}
			}
		}
	}
}

/* ---------- private code */

void hs_math_sine_evaluate(short op, long thread_index, bool initial) // 0x106819D0
{

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

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		auto input = args[0].real_value;
		auto result = floor(input);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(result));
	}
}

void hs_math_modulus_evaluate(short op, long thread_index, bool initial) // 0x106818A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_math_modulus_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		long input1 = args[0].long_value;
		long input2 = args[1].long_value;
		if (input2 == 0)
		{
			((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_long(0));
		}
		else
		{
			long result = input1 % input2;
			((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_long(result));
		}
	}
}

void hs_math_floating_modulus_evaluate(short op, long thread_index, bool initial) // 0x10681630
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_math_floating_modulus_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		float input1 = args[0].real_value;
		float input2 = args[1].real_value;
		if (input2 == 0.0f)
		{
			((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(0.0f));
			return;
		}
		float result = fmod(input1, input2);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(result));
	}
}
