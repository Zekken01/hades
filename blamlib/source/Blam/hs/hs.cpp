/* ---------- headers */

#include "Blam/hs/hs.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <limits>
#include <type_traits>

/* ---------- forward declarations */

struct hs_stack_frame;
struct hs_value;
struct s_data_array;
struct s_hs_global;
struct s_hs_global_external;
struct s_hs_global_runtime;
struct s_hs_thread;
struct s_scenario;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

s_hs_thread *hs_thread_get(unsigned long thread_index);  // hades: added for 0X10F03460

extern void *hs_get_node_data(unsigned long script_index);
extern s_hs_thread *hs_thread_get(unsigned long index);
extern void hs_find_dormant_script(char const *script_name, long *out_script_index);
extern hs_stack_frame *hs_thread_stack(long thread_index);
extern s_hs_global_external *hs_global_external_get(short index);
extern e_hs_type hs_global_get_type(short global_index);
extern char const *hs_global_get_name(short global_index);
extern short hs_global_get_runtime_index(short global_index);
extern s_hs_global_runtime *hs_global_runtime_get(short global_index);
extern hs_value const *hs_evaluate_arguments2(short op, long thread_index, bool initial);
extern void hs_return2(long thread_index, hs_value value);
extern char const *hs_get_type_name(e_hs_type type);

/* ---------- globals */

extern s_data_array **g_script_node_runtime_state_allocation; // 0x11359AB4

/* ---------- private variables */

namespace hades_file_local
{
	extern s_hs_global_external **const g_hs_global_externals; // 0x112497A8
}
using namespace hades_file_local;
/* ---------- public code */

_extern void *_sub_10F02FA0(unsigned long);
void *hs_get_node_data(unsigned long script_index) // 0x10F02FA0
{
	mangled_x86(MANGLED_TODO, "?hs_get_node_data@@YAPAXK@Z");
	// unsigned long script_index;
	// char *allocation_data;
	// char *deterministic_datum;
	// __int32 allocation_index;
	// __int32 allocation_offset;
	todo("implement");
	void * __result = _sub_10F02FA0(script_index);
	return __result;
}

s_hs_thread *hs_thread_get(unsigned long index) // 0x10F033F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_thread_get@@YAPAUs_hs_thread@@K@Z");
	// unsigned long index;

	return tls_getd().hs_thread_deterministic_data->try_and_get(index);
}

void hs_find_dormant_script(char const *script_name, long *out_script_index) // 0x10F02E90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_find_dormant_script@@YAXPBDPAJ@Z");
	// long *out_script_index;
	// long thread_index;
		// s_scenario *scenario;
		// s_hs_thread *thread;
	// function call : long (*const)(char const *)

	*out_script_index = -1;
	long thread_index = ((long (*const)(char const *))0x596070)(script_name);
	if (thread_index != -1)
	{
		s_hs_thread *thread = hs_thread_get(thread_index);
		s_scenario *scenario = global_scenario_get();
		if (scenario->scripts[thread->script_index].type == _hs_script_type_dormant)
		{
			*out_script_index = thread->script_index;
		}
	}
}

hs_stack_frame *hs_thread_stack(long thread_index) // 0x10F03460
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_thread_stack@@YAPAUhs_stack_frame@@J@Z");
	// long thread_index;
	// s_hs_thread *thread;

	s_hs_thread *thread = hs_thread_get(thread_index);
	if (thread == nullptr)
	{
		return nullptr;
	}
	return (hs_stack_frame *)&thread->stack[thread->stack_offset];
}

s_hs_global_external *hs_global_external_get(short index) // 0x10F030A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_global_external_get@@YAPAUs_hs_global_external@@F@Z");
	// short index;

	return g_hs_global_externals[index];
}

extern e_hs_type _sub_10F03220(short);
e_hs_type hs_global_get_type(short global_index) // 0x10F03220
{
	mangled_x86(MANGLED_TODO, "?hs_global_get_type@@YA?AW4e_hs_type@@F@Z");
	// short global_index;
	// short absolute_index;
	{
		// s_scenario *scnr;
		{
			// s_hs_global *global;
		}
	}
	todo("implement");
	e_hs_type __result = _sub_10F03220(global_index);
	return __result;
}

char const *hs_global_get_name(short global_index) // 0x10F03100
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_global_get_name@@YAPBDF@Z");
	// short global_index;
	// short absolute_index;

	short masked_index = global_index & 0x7FFF;
	if (global_index & 0x8000)
	{
		return "<unknown>";
	}
	else
	{
		return (char const *)&global_scenario_get()->script_globals[masked_index];
	}
}

short hs_global_get_runtime_index(short global_index) // 0x10F031A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_global_get_runtime_index@@YAFF@Z");
	// short global_index;
	// short runtime_index;

	short runtime_index = global_index & 0x7FFF;
	if ((global_index & 0x8000) == 0)
	{
		runtime_index += 1315;
	}
	return runtime_index;
}

s_hs_global_runtime *hs_global_runtime_get(short global_index) // 0x10F032F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_global_runtime_get@@YAPAUs_hs_global_runtime@@F@Z");
	// short global_index;

	return tls_getd().hs_global_data->try_and_get_absolute(hs_global_get_runtime_index(global_index));
}

hs_value const *hs_evaluate_arguments2(short op, long thread_index, bool initial) // 0x10F02E20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_evaluate_arguments2@@YAPBUhs_value@@FJ_N@Z");
	// bool initial;
	// function call : hs_value *(*const)(short, long, bool)

	return ((hs_value const *(__cdecl *)(unsigned short, long, bool))0x5972f0)(op, thread_index, initial);
}

void hs_return2(long thread_index, hs_value value) // 0x10F03380
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_return2@@YAXJUhs_value@@@Z");
	// hs_value value;
	// function call : void (*const)(long, hs_value)

	((void(__cdecl *const)(long, hs_value))0x5974e0)(thread_index, value);
}

char const *hs_get_type_name(e_hs_type type) // 0x10F03050
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_get_type_name@@YAPBDW4e_hs_type@@@Z");
	// e_hs_type type;

	return ((char const **)0x18BEC98)[(short)type];
}

extern hs_value _sub_10F02A90(e_hs_type);
hs_value hs_value::get_default(e_hs_type type) // 0x10F02A90
{
	mangled_x86(MANGLED_TODO, "?get_default@hs_value@@SA?AU1@W4e_hs_type@@@Z");
	// static ...; // 0x10F02C14
// $LN16:
// $LN15:
// $LN14:
// $LN13:
// $LN12:
// $LN11:
// $LN10:
// $LN7:
// $LN6:
// $LN4:
	// e_hs_type type;
	todo("implement");
	hs_value __result = _sub_10F02A90(type);
	return __result;
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_enum<unsigned short,enum e_hs_type>::operator enum e_hs_type() const;
template s_hs_global_runtime * c_data_array<s_hs_global_runtime>::try_and_get_absolute(long);
