/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block_index.inl"
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
struct real_euler_angles3d;
struct real_matrix3x3;
struct real_point3d;
struct real_vector3d;
struct s_damage_owner;
struct s_object_data;
struct s_object_placement_data;
struct s_scenario_location;
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
			namespace Object
			{
				extern void RegisterMethods(Scripting::HS::ScriptMethodMap &methods);
			}
		}
	}
}

void hs_object_get_x_position_evaluate(short op, long thread_index, bool initial);
void hs_object_get_z_position_evaluate(short op, long thread_index, bool initial);
void hs_object_get_yaw_evaluate(short op, long thread_index, bool initial);
void hs_object_get_pitch_evaluate(short op, long thread_index, bool initial);
void hs_object_get_roll_evaluate(short op, long thread_index, bool initial);
void hs_object_set_position_evaluate(short op, long thread_index, bool initial);
void hs_object_set_rotation_evaluate(short op, long thread_index, bool initial);
void hs_object_create_at_position_evaluate(short op, long thread_index, bool initial);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Scripting
{
	namespace HS
	{
		namespace Methods
		{
			namespace Object
			{
				_extern void _sub_10681FD0(Scripting::HS::ScriptMethodMap &);
				void RegisterMethods(Scripting::HS::ScriptMethodMap &methods) // 0x10681FD0
				{
					mangled_x86(MANGLED_TODO, "?RegisterMethods@Object@Methods@HS@Scripting@@YAXAAVScriptMethodMap@34@@Z");
					// Scripting::HS::ScriptMethodMap &methods;
					todo("implement");
					_sub_10681FD0(methods);
				}
			}
		}
	}
}

/* ---------- private code */

_extern void _sub_10683190(short, long, bool);
void hs_object_get_x_position_evaluate(short op, long thread_index, bool initial) // 0x10683190
{
	// `anonymous-namespace'::hs_object_get_x_position_evaluate
	// static ...; // 0x1068330C
	// short op;
	// long thread_index;
	// bool initial;
	{
		// hs_value *args;
		{
			// long object_index;
			{
				// s_object_data *object;
				{
					// real_point3d position;
				}
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(unsigned long, real_point3d *)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_10683190(op, thread_index, initial);
}

_extern void _sub_106835F0(short, long, bool);
void hs_object_get_z_position_evaluate(short op, long thread_index, bool initial) // 0x106835F0
{
	// `anonymous-namespace'::hs_object_get_z_position_evaluate
	// static ...; // 0x1068376C
	// short op;
	// long thread_index;
	// bool initial;
	{
		// hs_value *args;
		{
			// long object_index;
			{
				// s_object_data *object;
				{
					// real_point3d position;
				}
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(unsigned long, real_point3d *)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106835F0(op, thread_index, initial);
}

_extern void _sub_10683390(short, long, bool);
void hs_object_get_yaw_evaluate(short op, long thread_index, bool initial) // 0x10683390
{
	// `anonymous-namespace'::hs_object_get_yaw_evaluate
	// static ...; // 0x10683548
	// static ...; // 0x10683524
	// static ...; // 0x1068351C
	// short op;
	// long thread_index;
	// bool initial;
	{
		// hs_value *args;
		{
			// long object_index;
			{
				// s_object_data *object;
				{
					// real_euler_angles3d object_angles;
					// real_vector3d object_forward;
					// real_vector3d object_up;
				}
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, real_vector3d *, real_vector3d *)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_10683390(op, thread_index, initial);
}

_extern void _sub_10682CD0(short, long, bool);
void hs_object_get_pitch_evaluate(short op, long thread_index, bool initial) // 0x10682CD0
{
	// `anonymous-namespace'::hs_object_get_pitch_evaluate
	// static ...; // 0x10682E88
	// static ...; // 0x10682E64
	// static ...; // 0x10682E5C
	// short op;
	// long thread_index;
	// bool initial;
	{
		// hs_value *args;
		{
			// long object_index;
			{
				// s_object_data *object;
				{
					// real_euler_angles3d object_angles;
					// real_vector3d object_forward;
					// real_vector3d object_up;
				}
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, real_vector3d *, real_vector3d *)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_10682CD0(op, thread_index, initial);
}

_extern void _sub_10682F30(short, long, bool);
void hs_object_get_roll_evaluate(short op, long thread_index, bool initial) // 0x10682F30
{
	// `anonymous-namespace'::hs_object_get_roll_evaluate
	// static ...; // 0x106830E8
	// static ...; // 0x106830C4
	// static ...; // 0x106830BC
	// short op;
	// long thread_index;
	// bool initial;
	{
		// hs_value *args;
		{
			// long object_index;
			{
				// s_object_data *object;
				{
					// real_euler_angles3d object_angles;
					// real_vector3d object_forward;
					// real_vector3d object_up;
				}
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, real_vector3d *, real_vector3d *)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_10682F30(op, thread_index, initial);
}

_extern void _sub_106837F0(short, long, bool);
void hs_object_set_position_evaluate(short op, long thread_index, bool initial) // 0x106837F0
{
	// `anonymous-namespace'::hs_object_set_position_evaluate
	// static ...; // 0x10683A10
	// static ...; // 0x106839EC
	// static ...; // 0x106839E4
	// short op;
	// long thread_index;
	// bool initial;
	{
		// hs_value *args;
		{
			// long object_index;
			// long pos_z;
			// long pos_x;
			// long pos_y;
			{
				// s_object_data *object;
				{
					// real_point3d position;
					// real_vector3d object_forward;
					// real_vector3d object_up;
				}
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, real_vector3d *, real_vector3d *)
	// function call : void (*const)(unsigned long, real_point3d *, real_vector3d *, real_vector3d *, s_scenario_location *)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106837F0(op, thread_index, initial);
}

_extern void _sub_10683AD0(short, long, bool);
void hs_object_set_rotation_evaluate(short op, long thread_index, bool initial) // 0x10683AD0
{
	// `anonymous-namespace'::hs_object_set_rotation_evaluate
	// static ...; // 0x10683D40
	// static ...; // 0x10683D1C
	// static ...; // 0x10683D14
	// short op;
	// long thread_index;
	// bool initial;
	{
		// hs_value *args;
		{
			// long object_index;
			// long yaw;
			// long pitch;
			// long roll;
			{
				// s_object_data *object;
				{
					// real_vector3d object_forward;
					// float roll_rad;
					// real_vector3d object_up;
					// float yaw_rad;
					// real_matrix3x3 matrix;
					// float pitch_rad;
				}
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, real_vector3d *, real_vector3d *)
	// function call : void (*const)(unsigned long, real_point3d *, real_vector3d *, real_vector3d *, s_scenario_location *)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_10683AD0(op, thread_index, initial);
}

_extern void _sub_10682980(short, long, bool);
void hs_object_create_at_position_evaluate(short op, long thread_index, bool initial) // 0x10682980
{
	// `anonymous-namespace'::hs_object_create_at_position_evaluate
	// static ...; // 0x10682C04
	// short op;
	// long thread_index;
	// bool initial;
	{
		// hs_value *args;
		{
			// long tag_index;
			// long pos_z;
			// long pos_x;
			// long pos_y;
			{
				// s_object_placement_data placement;
				// long object_index;
				// void (*const simulation_action_object_create)(long);
				// void (*const game_engine_register_object)(long);
				{
					// s_object_data *object;
				}
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : void (*const)(s_object_placement_data *, long, unsigned long, s_damage_owner *)
	// function call : long (*const)(s_object_placement_data *)
	// function call : void (*const)(long)
	// function call : void (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_10682980(op, thread_index, initial);
}
