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

s_hs_global_external *hs_global_external_get(short global_index);  // hades: added for 0X10F03220

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

void *hs_get_node_data(unsigned long script_index) // 0x10F02FA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_get_node_data@@YAPAXK@Z");
	// unsigned long script_index;
	// char *allocation_data;
	// char *deterministic_datum;
	// __int32 allocation_index;
	// __int32 allocation_offset;

	char *deterministic_datum = (char *)tls_get(0x68);
	__int32 allocation_index = *(unsigned short *)(deterministic_datum + *(short *)(deterministic_datum + 0x10) + 0x24) + 0x10;
	char *allocation_data = (char *)(*g_script_node_runtime_state_allocation)->address;
	__int32 allocation_offset = *(unsigned short *)(allocation_data + *(unsigned short *)(allocation_data + allocation_index * 0x18) * 0x18 + 8) * 0x18;
	return allocation_data + allocation_offset;
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

e_hs_type hs_global_get_type(short global_index) // 0x10F03220
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_global_get_type@@YA?AW4e_hs_type@@F@Z");
	// short global_index;
	// short absolute_index;
		// s_scenario *scnr;
			// s_hs_global *global;

	short absolute_index = global_index & 0x7FFF;
	if (global_index & 0x8000)
	{
		return hs_global_external_get(absolute_index)->type;
	}
	else
	{
		s_scenario *scenario = global_scenario_get();
		s_hs_global *global = scenario->script_globals.get_element(absolute_index);
		if (global)
			return global->type;
	}
	return _hs_type_unparsed;
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

hs_value hs_value::get_default(e_hs_type type) // 0x10F02A90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_default@hs_value@@SA?AU1@W4e_hs_type@@@Z");
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

	switch (type)
	{
	case _hs_type_unparsed:
	case _hs_type_special_form:
		return hs_value::from_long(0);
	case _hs_type_function_name:
		return hs_value::from_string("");
	case _hs_type_passthrough:
	case _hs_type_void:
	case _hs_type_boolean:
		return hs_value::from_long(0);
	case _hs_type_real:
		return hs_value::from_real(0.0f);
	case _hs_type_short:
		return hs_value::from_short(0);
	case _hs_type_long:
		return hs_value::from_long(0);
	case _hs_type_string:
		return hs_value::from_string("");
	case _hs_type_script:
		return hs_value::from_long(-1);
	case _hs_type_string_id:
		return hs_value::from_long(0);
	case _hs_type_unit_seat_mapping:
	case _hs_type_trigger_volume:
	case _hs_type_cutscene_flag:
	case _hs_type_cutscene_camera_point:
	case _hs_type_cutscene_title:
	case _hs_type_cutscene_recording:
	case _hs_type_device_group:
	case _hs_type_ai:
	case _hs_type_ai_command_list:
	case _hs_type_ai_command_script:
	case _hs_type_ai_behavior:
	case _hs_type_ai_orders:
	case _hs_type_ai_line:
	case _hs_type_starting_profile:
	case _hs_type_conversation:
	case _hs_type_zone_set:
	case _hs_type_designer_zone:
	case _hs_type_point_reference:
	case _hs_type_style:
	case _hs_type_object_list:
	case _hs_type_folder:
	case _hs_type_sound:
	case _hs_type_effect:
	case _hs_type_damage:
	case _hs_type_looping_sound:
	case _hs_type_animation_graph:
	case _hs_type_damage_effect:
	case _hs_type_object_definition:
	case _hs_type_bitmap:
	case _hs_type_shader:
	case _hs_type_render_model:
	case _hs_type_structure_definition:
	case _hs_type_lightmap_definition:
	case _hs_type_cinematic_definition:
	case _hs_type_cinematic_scene_definition:
	case _hs_type_bink_definition:
	case _hs_type_any_tag:
	case _hs_type_any_tag_not_resolving:
	case _hs_type_game_difficulty:
	case _hs_type_team:
	case _hs_type_mp_team:
	case _hs_type_controller:
	case _hs_type_button_preset:
	case _hs_type_joystick_preset:
	case _hs_type_unknown_56:
	case _hs_type_player_color:
	case _hs_type_player_character_type:
	case _hs_type_voice_output_setting:
	case _hs_type_voice_mask:
	case _hs_type_subtitle_setting:
	case _hs_type_actor_type:
	case _hs_type_model_state:
	case _hs_type_event:
	case _hs_type_character_physics:
	case _hs_type_object:
	case _hs_type_unit:
	case _hs_type_vehicle:
	case _hs_type_weapon:
	case _hs_type_device:
	case _hs_type_scenery:
	case _hs_type_effect_scenery:
	case _hs_type_object_name:
	case _hs_type_unit_name:
	case _hs_type_vehicle_name:
	case _hs_type_weapon_name:
	case _hs_type_device_name:
	case _hs_type_scenery_name:
	case _hs_type_effect_scenery_name:
	case _hs_type_cinematic_lightprobe:
	case _hs_type_animation_budget_reference:
	case _hs_type_looping_sound_budget_reference:
	case _hs_type_sound_budget_reference:
		return hs_value::from_long(-1);
	default:
		return hs_value::from_long(0);
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_enum<unsigned short,enum e_hs_type>::operator enum e_hs_type() const;
template s_hs_global_runtime * c_data_array<s_hs_global_runtime>::try_and_get_absolute(long);

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
s_data_array **g_script_node_runtime_state_allocation = reinterpret_cast<s_data_array **>(0x24B06D4);
namespace hades_file_local { s_hs_global_external **const g_hs_global_externals = reinterpret_cast<s_hs_global_external **>(0x18EF450); }
