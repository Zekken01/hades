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

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<e_object_type, long>);  // hades: added for 0x10683190
extern void (*const object_get_world_position)(unsigned long, real_point3d *);  // hades: added for 0x10683190
extern real_euler_angles3d *euler_angles3d_from_vectors3d(real_euler_angles3d *angles, real_vector3d const *forward, real_vector3d const *up);  // hades: added for 0x10683190
extern void (*const object_set_position)(unsigned long, real_point3d *, real_vector3d *, real_vector3d *, s_scenario_location *);  // hades: added for 0x10683190
extern void matrix3x3_from_angles(real_matrix3x3 *matrix, float yaw, float pitch, float roll);  // hades: added for 0x10683190
extern void (*const object_placement_data_new)(s_object_placement_data *, long, unsigned long, s_damage_owner *);  // hades: added for 0x10683190

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
				void RegisterMethods(Scripting::HS::ScriptMethodMap &methods) // 0x10681FD0
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterMethods@Object@Methods@HS@Scripting@@YAXAAVScriptMethodMap@34@@Z");
					// Scripting::HS::ScriptMethodMap &methods;

					methods.AddMethod("object_get_x_position", "Gets an objects X position", NetworkSafe, hs_object_get_x_position_evaluate, _hs_type_real, { { _hs_type_object, "obj", "The object to retrieve the X position for" } });
					methods.AddMethod("object_get_y_position", "Gets an objects Y position", NetworkSafe, hs_object_get_x_position_evaluate, _hs_type_real, { { _hs_type_object, "obj", "The object to retrieve the Y position for" } });
					methods.AddMethod("object_get_z_position", "Gets an objects Z position", NetworkSafe, hs_object_get_z_position_evaluate, _hs_type_real, { { _hs_type_object, "obj", "The object to retrieve the Z position for" } });
					methods.AddMethod("object_get_yaw", "Gets an objects yaw", NetworkSafe, hs_object_get_yaw_evaluate, _hs_type_real, { { _hs_type_object, "obj", "The object to retrieve the yaw for" } });
					methods.AddMethod("object_get_pitch", "Gets an objects pitch", NetworkSafe, hs_object_get_pitch_evaluate, _hs_type_real, { { _hs_type_object, "obj", "The object to retrieve the pitch for" } });
					methods.AddMethod("object_get_roll", "Gets an objects roll", NetworkSafe, hs_object_get_roll_evaluate, _hs_type_real, { { _hs_type_object, "obj", "The object to retrieve the roll for" } });
					methods.AddMethod("object_set_position", "Sets an objects position", HostOnly, hs_object_set_position_evaluate, _hs_type_void, { { _hs_type_object, "obj", "The object to set the position for" }, { _hs_type_real, "pos_x", "The X position" }, { _hs_type_real, "pos_y", "The Y position" }, { _hs_type_real, "pos_z", "The Z position" } });
					methods.AddMethod("object_set_rotation", "Sets an objects rotation", HostOnly, hs_object_set_rotation_evaluate, _hs_type_void, { { _hs_type_object, "obj", "The object to set the rotation for" }, { _hs_type_real, "yaw", "The yaw value (0-360)" }, { _hs_type_real, "pitch", "The pitch value (0-360)" }, { _hs_type_real, "roll", "The roll value (0-360)" } });
					methods.AddMethod("object_create_at_position", "Creates an object at a position", HostOnly, hs_object_create_at_position_evaluate, _hs_type_object, { { _hs_type_any_tag, "tag", "The desired objects tag" }, { _hs_type_real, "pos_x", "The X position" }, { _hs_type_real, "pos_y", "The Y position" }, { _hs_type_real, "pos_z", "The Z position" } });
				}
			}
		}
	}
}

/* ---------- private code */

void hs_object_get_x_position_evaluate(short op, long thread_index, bool initial) // 0x10683190
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_object_get_x_position_evaluate@@YAXFJ_N@Z");
	// `anonymous-namespace'::hs_object_get_x_position_evaluate
	// static ...; // 0x1068330C
	// short op;
	// long thread_index;
	// bool initial;
		// hs_value *args;
			// long object_index;
				// s_object_data *object;
					// real_point3d position;
	// function call : hs_value *(*const)(short, long, bool)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(unsigned long, real_point3d *)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		long object_index = args[0].long_value;
		if (object_index != -1)
		{
			s_object_data *object = object_try_and_get_and_verify_type(object_index, -1);
			if (object)
			{
				real_point3d position = {};
				object_get_world_position(object_index, &position);
				((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(position.x));
				return;
			}
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(-1.0f));
	}
}

void hs_object_get_z_position_evaluate(short op, long thread_index, bool initial) // 0x106835F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_object_get_z_position_evaluate@@YAXFJ_N@Z");
	// `anonymous-namespace'::hs_object_get_z_position_evaluate
	// static ...; // 0x1068376C
	// short op;
	// long thread_index;
	// bool initial;
		// hs_value *args;
			// long object_index;
				// s_object_data *object;
					// real_point3d position;
	// function call : hs_value *(*const)(short, long, bool)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(unsigned long, real_point3d *)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		long object_index = args[0].long_value;
		if (object_index != -1)
		{
			s_object_data *object = object_try_and_get_and_verify_type(object_index, -1);
			if (object)
			{
				real_point3d position = {};
				object_get_world_position(object_index, &position);
				((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(position.z));
				return;
			}
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(-1.0f));
	}
}

void hs_object_get_yaw_evaluate(short op, long thread_index, bool initial) // 0x10683390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_object_get_yaw_evaluate@@YAXFJ_N@Z");
	// `anonymous-namespace'::hs_object_get_yaw_evaluate
	// static ...; // 0x10683548
	// static ...; // 0x10683524
	// static ...; // 0x1068351C
	// short op;
	// long thread_index;
	// bool initial;
		// hs_value *args;
			// long object_index;
				// s_object_data *object;
					// real_euler_angles3d object_angles;
					// real_vector3d object_forward;
					// real_vector3d object_up;
	// function call : hs_value *(*const)(short, long, bool)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, real_vector3d *, real_vector3d *)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		long object_index = args[0].long_value;
		if (object_index != -1)
		{
			s_object_data *object = object_try_and_get_and_verify_type(object_index, -1);
			if (object)
			{
				real_euler_angles3d object_angles = {};
				real_vector3d object_forward;
				real_vector3d object_up;
				((void(__cdecl *)(long, real_vector3d *, real_vector3d *))0xB2E490)(object_index, &object_forward, &object_up);
				euler_angles3d_from_vectors3d(&object_angles, &object_forward, &object_up);
				((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(object_angles.yaw));
				return;
			}
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(-1.0f));
	}
}

void hs_object_get_pitch_evaluate(short op, long thread_index, bool initial) // 0x10682CD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_object_get_pitch_evaluate@@YAXFJ_N@Z");
	// `anonymous-namespace'::hs_object_get_pitch_evaluate
	// static ...; // 0x10682E88
	// static ...; // 0x10682E64
	// static ...; // 0x10682E5C
	// short op;
	// long thread_index;
	// bool initial;
		// hs_value *args;
			// long object_index;
				// s_object_data *object;
					// real_euler_angles3d object_angles;
					// real_vector3d object_forward;
					// real_vector3d object_up;
	// function call : hs_value *(*const)(short, long, bool)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, real_vector3d *, real_vector3d *)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		long object_index = args[0].long_value;
		if (object_index != -1)
		{
			s_object_data *object = object_try_and_get_and_verify_type(object_index, -1);
			if (object)
			{
				real_euler_angles3d object_angles = {};
				real_vector3d object_forward;
				real_vector3d object_up;
				((void(__cdecl *)(long, real_vector3d *, real_vector3d *))0xB2E490)(object_index, &object_forward, &object_up);
				euler_angles3d_from_vectors3d(&object_angles, &object_forward, &object_up);
				((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(object_angles.pitch));
				return;
			}
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(-1.0f));
	}
}

void hs_object_get_roll_evaluate(short op, long thread_index, bool initial) // 0x10682F30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_object_get_roll_evaluate@@YAXFJ_N@Z");
	// `anonymous-namespace'::hs_object_get_roll_evaluate
	// static ...; // 0x106830E8
	// static ...; // 0x106830C4
	// static ...; // 0x106830BC
	// short op;
	// long thread_index;
	// bool initial;
		// hs_value *args;
			// long object_index;
				// s_object_data *object;
					// real_euler_angles3d object_angles;
					// real_vector3d object_forward;
					// real_vector3d object_up;
	// function call : hs_value *(*const)(short, long, bool)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, real_vector3d *, real_vector3d *)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		long object_index = args[0].long_value;
		if (object_index != -1)
		{
			s_object_data *object = object_try_and_get_and_verify_type(object_index, -1);
			if (object)
			{
				real_euler_angles3d object_angles = {};
				real_vector3d object_forward;
				real_vector3d object_up;
				((void(__cdecl *)(long, real_vector3d *, real_vector3d *))0xB2E490)(object_index, &object_forward, &object_up);
				euler_angles3d_from_vectors3d(&object_angles, &object_forward, &object_up);
				((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(object_angles.roll));
				return;
			}
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(-1.0f));
	}
}

void hs_object_set_position_evaluate(short op, long thread_index, bool initial) // 0x106837F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_object_set_position_evaluate@@YAXFJ_N@Z");
	// `anonymous-namespace'::hs_object_set_position_evaluate
	// static ...; // 0x10683A10
	// static ...; // 0x106839EC
	// static ...; // 0x106839E4
	// short op;
	// long thread_index;
	// bool initial;
		// hs_value *args;
			// long object_index;
			// long pos_z;
			// long pos_x;
			// long pos_y;
				// s_object_data *object;
					// real_point3d position;
					// real_vector3d object_forward;
					// real_vector3d object_up;
	// function call : hs_value *(*const)(short, long, bool)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, real_vector3d *, real_vector3d *)
	// function call : void (*const)(unsigned long, real_point3d *, real_vector3d *, real_vector3d *, s_scenario_location *)
	// function call : void (*const)(long, hs_value)

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		long object_index = args[0].long_value;
		long pos_x = (long)args[1].real_value;
		long pos_y = (long)args[2].real_value;
		long pos_z = (long)args[3].real_value;
		if (((bool(__cdecl *)())0x5319C0)() && ((bool(__cdecl *)())0x550F90)() && object_index != -1)
		{
			s_object_data *object = object_try_and_get_and_verify_type(object_index, -1);
			if (object)
			{
				real_vector3d object_forward;
				real_vector3d object_up;
				((void(__cdecl *)(long, real_vector3d *, real_vector3d *))0xB2E490)(object_index, &object_forward, &object_up);
				real_point3d position = {};
				position.x = (float)pos_x;
				position.y = (float)pos_y;
				position.z = (float)pos_z;
				object_set_position(object_index, &position, &object_forward, &object_up, nullptr);
			}
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value{});
	}
}

void hs_object_set_rotation_evaluate(short op, long thread_index, bool initial) // 0x10683AD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_object_set_rotation_evaluate@@YAXFJ_N@Z");
	// `anonymous-namespace'::hs_object_set_rotation_evaluate
	// static ...; // 0x10683D40
	// static ...; // 0x10683D1C
	// static ...; // 0x10683D14
	// short op;
	// long thread_index;
	// bool initial;
		// hs_value *args;
			// long object_index;
			// long yaw;
			// long pitch;
			// long roll;
				// s_object_data *object;
					// real_vector3d object_forward;
					// float roll_rad;
					// real_vector3d object_up;
					// float yaw_rad;
					// real_matrix3x3 matrix;
					// float pitch_rad;
	// function call : hs_value *(*const)(short, long, bool)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, real_vector3d *, real_vector3d *)
	// function call : void (*const)(unsigned long, real_point3d *, real_vector3d *, real_vector3d *, s_scenario_location *)
	// function call : void (*const)(long, hs_value)

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		long object_index = args[0].long_value;
		long yaw = (long)args[1].real_value;
		long pitch = (long)args[2].real_value;
		long roll = (long)args[3].real_value;
		if (((bool(__cdecl *)())0x5319C0)() && ((bool(__cdecl *)())0x550F90)() && object_index != -1)
		{
			s_object_data *object = object_try_and_get_and_verify_type(object_index, -1);
			if (object)
			{
				real_vector3d object_forward;
				real_vector3d object_up;
				((void(__cdecl *)(long, real_vector3d *, real_vector3d *))0xB2E490)(object_index, &object_forward, &object_up);
				real_matrix3x3 matrix;
				float yaw_rad = (float)yaw * 0.017453292f;
				float pitch_rad = (float)pitch * 0.017453292f;
				float roll_rad = (float)roll * 0.017453292f;
				matrix3x3_from_angles(&matrix, -yaw_rad, pitch_rad, roll_rad);
				object_set_position(object_index, nullptr, &matrix.forward, &matrix.up, nullptr);
			}
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value{});
	}
}

void hs_object_create_at_position_evaluate(short op, long thread_index, bool initial) // 0x10682980
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_object_create_at_position_evaluate@@YAXFJ_N@Z");
	// `anonymous-namespace'::hs_object_create_at_position_evaluate
	// static ...; // 0x10682C04
	// short op;
	// long thread_index;
	// bool initial;
		// hs_value *args;
			// long tag_index;
			// long pos_z;
			// long pos_x;
			// long pos_y;
				// s_object_placement_data placement;
				// long object_index;
				// void (*const simulation_action_object_create)(long);
				// void (*const game_engine_register_object)(long);
					// s_object_data *object;
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

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		long tag_index = args[0].long_value;
		long pos_x = (long)args[1].real_value;
		long pos_y = (long)args[2].real_value;
		long pos_z = (long)args[3].real_value;
		if (((bool(__cdecl *)())0x5319C0)() && ((bool(__cdecl *)())0x550F90)() && tag_index != -1)
		{
			void (*const simulation_action_object_create)(long) = reinterpret_cast<void (*)(long)>(0x58FFB0);
			void (*const game_engine_register_object)(long) = reinterpret_cast<void (*)(long)>(0x4B2CD0);
			s_object_placement_data placement;
			object_placement_data_new(&placement, tag_index, -1, nullptr);
			placement.relative_position.x = (float)pos_x;
			placement.relative_position.y = (float)pos_y;
			placement.relative_position.z = (float)pos_z;
			long object_index = ((long(__cdecl *)(s_object_placement_data *))0xB30440)(&placement);
			if (object_index != -1)
			{
				game_engine_register_object(object_index);
				simulation_action_object_create(object_index);
				s_object_data *object = object_try_and_get_and_verify_type(object_index, -1);
				if (object)
				{
					((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_long(object_index));
					return;
				}
			}
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_long(-1));
	}
}
