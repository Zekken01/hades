/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/camera/camera.hpp"
#include "Blam/camera/director.hpp"
#include "Blam/camera/observer.hpp"
#include "Blam/camera/scripted_camera.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/cutscene/cinematic_definitions.hpp"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/player_control.hpp"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/draw_string.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/unit_definitions.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Debug/DebugDraw.hpp"
#include "ElDorito.hpp"
#include "Modules/ModuleCamera.hpp"
#include "Modules/ModuleDebug.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/Core.hpp"
#include "Patches/Ui.hpp"
#include "Player/PlayerEmotes.hpp"
#include "Pointer.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

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
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_director;
struct c_flying_camera;
struct c_font_cache_mt_safe;
struct c_rasterizer_draw_string;
struct real_euler_angles2d;
struct real_euler_angles3d;
struct real_matrix3x3;
struct real_matrix4x3;
struct real_point3d;
struct real_quaternion;
struct real_vector3d;
struct s_camera_definition;
struct s_camera_frame;
struct s_camera_globals;
struct s_cinematic_extra_camera_frame;
struct s_cinematic_extra_camera_shot;
struct s_cinematic_scene_definition;
struct s_cinematic_scene_shot;
struct s_cinematic_shot_extra_camera;
struct s_focus_and_distance;
struct s_object_data;
struct s_observer;
struct s_observer_command;
struct s_observer_result;
struct s_player_control_input_state;
struct s_player_datum;
struct s_scripted_camera_globals;
struct s_unit_camera_definition;
struct s_unit_data;
struct s_unit_definition;
struct short_rectangle2d;
namespace Blam
{
	namespace Input
	{
		struct PlayerInputState;
	}
}
namespace Modules
{
	class ModuleCamera;
	class ModuleDebug;
	struct Command;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace RawInput {}
	using namespace Patches::RawInput;
	namespace Camera {}
	using namespace Patches::Camera;
	namespace Core {}
	using namespace Patches::Core;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Input {}
	using namespace Blam::Input;
}

/* ---------- constants */

/* ---------- definitions */

//struct c_following_camera__update_hook::__l2::s_camera_definition
//{
//	real_point3d Position; // 0x0
//	real_vector3d PositionShift; // 0xC
//	float LookShift[2]; // 0x18
//	float Depth; // 0x20
//	float FieldOfView; // 0x24
//	real_vector3d Forward; // 0x28
//	real_vector3d Up; // 0x34
//};
//static_assert(sizeof(c_following_camera__update_hook::__l2::s_camera_definition) == 64, "Invalid c_following_camera__update_hook::__l2::s_camera_definition size");

/* ---------- prototypes */

namespace Patches
{
	namespace Camera
	{
		extern void ApplyAll();
		extern void ApplyAfterTagsLoaded();
		extern bool SetForcedCameraMode(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const mode);
		extern e_camera_mode GetForcedCameraMode();
	}
}

long director_game_desired_perspective_hook(long unit_index, long *out_seat_state);
bool weapon_prevents_sprinting(long weapon_index);
long director_perspective_for_sprint_meter_hook(long output_user_index);
bool director_inhibited_facing_hook(long output_user_index);
bool unit_camera_override_hook(long unit_index, s_unit_camera_definition **camera);
void unit_update_aiming_hook(long unit_index);
__int32 equipped_weap_allows_3p_zoom();
void camera_globals_initialize_from_tags_hook();
void CameraModeReset();
void OnMapLoaded(char const *mapPath);
float GetScriptedCameraFovHook();
void c_following_camera__update_hook(void *thisptr, void *unused, __int32 localPlayerIndex, __int32 a4, unsigned char *state);
__int32 unit_use_third_person_camera(unsigned long object_index, __int32 *a2);
bool director_scripting_get_hook();
bool c_director__set_camera_mode_internal_hook(void *thisPtr, void *unused, __int32 camera_mode, float camera_speed, bool a4);
__int32 scripted_camera__player_mapping_get_input_controller_hook(short a1);
void debug_teleport_to_camera();
void director_game_tick_hook();
void director_render_hook();
void offset_and_scale_position_easing_type_one(real_point3d *position, real_vector3d *offset, float scale);
void offset_and_scale_position_easing_type_two(real_point3d *position, real_vector3d *offset, real_vector3d *offset_2, float scale);
void lerp_vector(real_vector3d *out_vec, real_vector3d *vec1, real_vector3d *vec2, float s);
void lerp_real(float *out_val, float a, float b, float s);
void slerp_rotational_vectors(real_vector3d *out_f, real_vector3d *out_up, real_vector3d *a, real_vector3d *a_up, real_vector3d *b, real_vector3d *b_up, float s);
void build_interpolated_camera_frame(s_camera_frame *out_frame, s_camera_frame *a, s_camera_frame *b, float s);
void observer_set_camera_frame(s_observer_command *observer_command, real_matrix4x3 *camera_matrix, s_camera_frame *frame);
void scripted_camera_update_call_hook(void *a1, void *camera_control, s_observer_command *observer_command);
void c_flying_camera__update_hook(c_flying_camera *thisptr, void *__formal, long user_index, float dt, s_observer_command *result);
void player_effect_apply_camera_effect_matrix_hook(long output_user_index, real_matrix4x3 *camera_matrix);
void observer_compute_result_hook(long output_user_index, s_focus_and_distance *focus_and_distance);
void observer_compute_view_offset_matrix_hook(long output_user_index, real_matrix4x3 *view_matrix);
void observer_result_compute_parameters_hook(s_observer_result *result);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern e_camera_mode cameraMode; // 0x11353BB0
	extern float &k_camera_field_of_view_default; // 0x11353BA4
	extern float &k_camera_field_of_view_min; // 0x11353BA8
	extern float &k_camera_field_of_view_max; // 0x11353BAC
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Camera
	{
		_extern void _sub_10956FE0();
		void ApplyAll() // 0x10956FE0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Camera@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10956FE0();
		}

		_extern void _sub_10956FC0();
		void ApplyAfterTagsLoaded() // 0x10956FC0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAfterTagsLoaded@Camera@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10956FC0();
		}

		_extern bool _sub_10958AF0(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const);
		bool SetForcedCameraMode(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const mode) // 0x10958AF0
		{
			mangled_x86(MANGLED_TODO, "?SetForcedCameraMode@Camera@Patches@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > mode;
			// constexpr bool (*const `Patches::Camera::SetForcedCameraMode'::`2'::player_terminal_chud_set)(bool); // constant == 11050832
			{
				// e_camera_mode currentMode;
			}
			{
			}
			{
			}
			{
			}
			{
			}
			{
			}
			// function call : void (*const)(long, e_director_mode)
			// function call : bool (*const)(long, long)
			// function call : c_director *(*const)(long)
			// function call : e_camera_mode ()
			// function call : void (*const)(long, e_director_mode)
			// function call : bool (*const)(long, long)
			// function call : c_director *(*const)(long)
			// function call : e_camera_mode ()
			// function call : void (*const)(long, e_director_mode)
			// function call : bool (*const)(long, long)
			// function call : c_director *(*const)(long)
			// function call : e_camera_mode ()
			// function call : void (*const)(long, e_director_mode)
			// function call : bool (*const)(long, long)
			// function call : c_director *(*const)(long)
			// function call : e_camera_mode ()
			// function call : void (*const)(long, e_director_mode)
			// function call : bool (*const)(long, long)
			// function call : c_director *(*const)(long)
			// function call : e_camera_mode ()
			// function call : void (*const)(long, e_director_mode)
			// function call : bool (*const)(long, long)
			// function call : c_director *(*const)(long)
			// function call : e_camera_mode ()
			// function call : bool (*const)(bool)
			todo("implement");
			bool __result = _sub_10958AF0(mode);
			return __result;
		}
	}
}

extern e_camera_mode _sub_109589A0();
namespace Patches
{
	namespace Camera
	{
		e_camera_mode GetForcedCameraMode() // 0x109589A0
		{
			mangled_x86(MANGLED_TODO, "?GetForcedCameraMode@Camera@Patches@@YA?AW4e_camera_mode@@XZ");
			// procedure flags: nofpo
			todo("implement");
			e_camera_mode __result = _sub_109589A0();
			return __result;
		}
	}
}

/* ---------- private code */

_extern long _sub_1095A750(long, long *);
long director_game_desired_perspective_hook(long unit_index, long *out_seat_state) // 0x1095A750
{
	// `anonymous-namespace'::director_game_desired_perspective_hook
	// long *out_seat_state;
	// s_player_datum *player;
	// long player_index;
	// function call : long (*)(long, long *)
	todo("implement");
	long __result = _sub_1095A750(unit_index, out_seat_state);
	return __result;
}

_extern bool _sub_1095F230(long);
bool weapon_prevents_sprinting(long weapon_index) // 0x1095F230
{
	// `anonymous-namespace'::weapon_prevents_sprinting
	// long weapon_index;
	// void *weapon_definition;
	// s_object_data *weapon;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	bool __result = _sub_1095F230(weapon_index);
	return __result;
}

_extern long _sub_1095AB10(long);
long director_perspective_for_sprint_meter_hook(long output_user_index) // 0x1095AB10
{
	// `anonymous-namespace'::director_perspective_for_sprint_meter_hook
	// long output_user_index;
	// long perspective;
	{
		// s_player_datum *player;
		// long player_index;
		{
			// s_unit_data *unit;
			// long unit_index;
			{
				// long weapon_index;
				// long weapon_inventory_index;
			}
		}
	}
	// function call : e_director_perspective (*const)(long)
	// function call : unsigned long (*const)(long)
	// function call : unsigned long (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	long __result = _sub_1095AB10(output_user_index);
	return __result;
}

_extern bool _sub_1095AA40(long);
bool director_inhibited_facing_hook(long output_user_index) // 0x1095AA40
{
	// `anonymous-namespace'::director_inhibited_facing_hook
	// long output_user_index;
	// unsigned long unit_index;
	// function call : unsigned long (*const)(long)
	// function call : c_director *(*const)(long)
	// function call : bool () const
	todo("implement");
	bool __result = _sub_1095AA40(output_user_index);
	return __result;
}

_extern bool _sub_1095ED00(long, s_unit_camera_definition **);
bool unit_camera_override_hook(long unit_index, s_unit_camera_definition **camera) // 0x1095ED00
{
	// `anonymous-namespace'::unit_camera_override_hook
	// s_unit_camera_definition **camera;
	// bool (*const equipment_get_unit_camera)(long, s_unit_camera_definition **);
	// function call : bool (*const)(long, s_unit_camera_definition **)
	todo("implement");
	bool __result = _sub_1095ED00(unit_index, camera);
	return __result;
}

_extern void _sub_1095EDA0(long);
void unit_update_aiming_hook(long unit_index) // 0x1095EDA0
{
	// `anonymous-namespace'::unit_update_aiming_hook
	// long unit_index;
	// void (*const unit_update_aiming)(long);
	// function call : void (*const)(long)
	todo("implement");
	_sub_1095EDA0(unit_index);
}

_extern __int32 _sub_1095B110();
__int32 equipped_weap_allows_3p_zoom() // 0x1095B110
{
	// `anonymous-namespace'::equipped_weap_allows_3p_zoom
	// procedure flags: nofpo
	// long perspective;
	// unsigned long unit_index;
	{
		// s_unit_data *unit;
		{
			// char inventoryIndex;
			{
				// long weaponIndex;
			}
		}
	}
	// function call : e_director_perspective (*const)(long)
	// function call : unsigned long (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : bool (*const)(long)
	todo("implement");
	__int32 __result = _sub_1095B110();
	return __result;
}

_extern void _sub_10959F90();
void camera_globals_initialize_from_tags_hook() // 0x10959F90
{
	// `anonymous-namespace'::camera_globals_initialize_from_tags_hook
	// procedure flags: nofpo
	// s_camera_globals *g_old_camera_globals;
	// s_camera_globals *g_camera_globals;
	// s_camera_globals *camera_globals_definition;
	todo("implement");
	_sub_10959F90();
}

_extern void _sub_10958800();
void CameraModeReset() // 0x10958800
{
	// `anonymous-namespace'::CameraModeReset
	// procedure flags: nofpo
	// constexpr bool (*const `CameraModeReset'::`2'::player_terminal_chud_set)(bool); // constant == 11050832
	// e_camera_mode currentMode;
	// function call : void (*const)(long, e_director_mode)
	// function call : bool (*const)(long, long)
	// function call : c_director *(*const)(long)
	// function call : e_camera_mode ()
	// function call : bool (*const)(bool)
	todo("implement");
	_sub_10958800();
}

_extern void _sub_10958AB0(char const *);
void OnMapLoaded(char const *mapPath) // 0x10958AB0
{
	// `anonymous-namespace'::OnMapLoaded
	// char const *mapPath;
	todo("implement");
	_sub_10958AB0(mapPath);
}

_extern float _sub_109589C0();
float GetScriptedCameraFovHook() // 0x109589C0
{
	// `anonymous-namespace'::GetScriptedCameraFovHook
	// procedure flags: nofpo
	// bool (*const game_is_mainmenu)();
	// float fov;
	{
		// float scriptedCameraFov;
	}
	// function call : bool (*const)()
	todo("implement");
	float __result = _sub_109589C0();
	return __result;
}

_extern void _sub_10959C60(void *, void *, __int32, __int32, unsigned char *);
void c_following_camera__update_hook(void *thisptr, void *unused, __int32 localPlayerIndex, __int32 a4, unsigned char *state) // 0x10959C60
{
	// `anonymous-namespace'::c_following_camera__update_hook
	// unsigned char *state;
	// unsigned long unit_index;
	// float s;
	// s_object_data *targetObject;
	// unsigned __int32 targetObjectIndex;
	// s_observer_command *observer_cmd;
	// bool (*const unit_in_vehicle)(long);
	// Modules::Command *camera_type;
	// Modules::ModuleCamera const &moduleCamera;
	// bool in_vehicle;
	// c_following_camera__update_hook::__l2::s_camera_definition &definition;
	// void (*const c_following_camera__update)(void *, __int32, __int32, unsigned char *);
	{
		// s_unit_data *unit;
		{
			// unsigned long weapon_index;
		}
	}
	// function call : unsigned long (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : bool (*const)(long)
	// function call : long (*const)(long, short)
	// function call : float (*const)(long)
	// function call : void (*const)(void *, __int32, __int32, unsigned char *)
	todo("implement");
	_sub_10959C60(thisptr, unused, localPlayerIndex, a4, state);
}

_extern __int32 _sub_1095EE20(unsigned long, __int32 *);
__int32 unit_use_third_person_camera(unsigned long object_index, __int32 *a2) // 0x1095EE20
{
	// `anonymous-namespace'::unit_use_third_person_camera
	// static ...; // 0x1095F148
	// static ...; // 0x1095F140
	// unsigned long object_index;
	// __int32 *a2;
	// s_unit_data *unit;
	// unsigned long weapon_index;
	// constexpr __int32 (*const `unit_use_third_person_camera'::`2'::weapon_uses_third_person_camera)(short); // constant == 11967008
	// constexpr __int32 (*const `unit_use_third_person_camera'::`2'::sub_B444F0)(unsigned long); // constant == 11814128
	// constexpr bool (*const `unit_use_third_person_camera'::`2'::secondary_skull_is_active)(unsigned long); // constant == 6336080
	// constexpr bool (*const `unit_use_third_person_camera'::`2'::sub_B40B80)(short); // constant == 11799424
	// constexpr __int32 (*const `unit_use_third_person_camera'::`2'::sub_B8F910)(short); // constant == 12122384
	// constexpr bool (*const `unit_use_third_person_camera'::`2'::sub_BA67F0)(short); // constant == 12216304
	// __int32 result;
	{
		// __int32 v16;
		// s_unit_data *parent;
		{
			// s_unit_definition *unit_definition;
			// c_flags<enum e_unit_seat_flags,long> seat_flags;
		}
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : __int32 (*const)(short)
	// function call : void *(*const)(unsigned long, long)
	// function call : bool (*const)(short)
	// function call : __int32 (*const)(unsigned long)
	// function call : long (*const)(long, short)
	// function call : __int32 (*const)(short)
	// function call : bool (*const)(unsigned long)
	// function call : bool (*const)(short)
	todo("implement");
	__int32 __result = _sub_1095EE20(object_index, a2);
	return __result;
}

_extern bool _sub_1095B0B0();
bool director_scripting_get_hook() // 0x1095B0B0
{
	// `anonymous-namespace'::director_scripting_get_hook
	// procedure flags: nofpo
	// constexpr bool (*const `director_scripting_get_hook'::`2'::director_scripting_get)(); // constant == 5839744
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_1095B0B0();
	return __result;
}

_extern bool _sub_10959450(void *, void *, __int32, float, bool);
bool c_director__set_camera_mode_internal_hook(void *thisPtr, void *unused, __int32 camera_mode, float camera_speed, bool a4) // 0x10959450
{
	// `anonymous-namespace'::c_director__set_camera_mode_internal_hook
	// bool a4;
	// constexpr bool (*const `c_director__set_camera_mode_internal_hook'::`2'::c_director__set_camera_mode_internal)(void *, __int32, float, bool); // constant == 5845520
	// function call : bool (*const)(void *, __int32, float, bool)
	todo("implement");
	bool __result = _sub_10959450(thisPtr, unused, camera_mode, camera_speed, a4);
	return __result;
}

_extern __int32 _sub_1095D2A0(short);
__int32 scripted_camera__player_mapping_get_input_controller_hook(short a1) // 0x1095D2A0
{
	// `anonymous-namespace'::scripted_camera__player_mapping_get_input_controller_hook
	// short a1;
	// constexpr __int32 (*const `scripted_camera__player_mapping_get_input_controller_hook'::`2'::player_mapping_get_input_controller)(short); // constant == 5806800
	// bool controllerEnabled;
	// function call : __int32 (*const)(short)
	todo("implement");
	__int32 __result = _sub_1095D2A0(a1);
	return __result;
}

_extern void _sub_1095A660();
void debug_teleport_to_camera() // 0x1095A660
{
	// `anonymous-namespace'::debug_teleport_to_camera
	// procedure flags: nofpo
	// Modules::ModuleDebug &debugModule;
	{
		// unsigned long unit_index;
		// s_observer_result *camera;
		{
			// void (*const hs_object_orient)(long, real_point3d const *, real_vector3d const *, real_vector3d const *, bool, bool);
		}
	}
	// function call : s_observer_result *(*const)(long)
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, real_point3d const *, real_vector3d const *, real_vector3d const *, bool, bool)
	todo("implement");
	_sub_1095A660();
}

_extern void _sub_1095A810();
void director_game_tick_hook() // 0x1095A810
{
	// `anonymous-namespace'::director_game_tick_hook
	// procedure flags: nofpo
	// static float `director_game_tick_hook'::`2'::previousVert; // 0x1240F668
	// static float `director_game_tick_hook'::`2'::previousHoriz; // 0x1240F664
	// constexpr void (*const `director_game_tick_hook'::`2'::scripted_camera_game_tick)(); // constant == 7521840
	// bool controllerEnabled;
	{
		// float scripted_camera_horiz;
		// s_scripted_camera_globals *scripted_camera_globals;
		// float scripted_camera_vert;
		// float current_vert;
		// s_player_control_input_state *player_control;
		// float current_horiz;
	}
	// function call : void (*const)()
	todo("implement");
	_sub_1095A810();
}

_extern void _sub_1095ACD0();
void director_render_hook() // 0x1095ACD0
{
	// `anonymous-namespace'::director_render_hook
	// procedure flags: nofpo
	// static ...; // 0x1095AFDB
	// static ...; // 0x1095AFD6
	// static ...; // 0x1095AFCF
	// static ...; // 0x1095AFC4
	// static ...; // 0x1095AFBC
	// static ...; // 0x1095AF80
	// static ...; // 0x1095AF78
	// real_euler_angles3d angles;
	// float const pitch_deg;
	// long output_user_index;
	// float const yaw_deg;
	// char buff[4096];
	// short_rectangle2d bounds;
	// float const roll_deg;
	// s_observer_result *camera;
	// c_rasterizer_draw_string drawstr;
	// float const k_to_degrees;
	// c_font_cache_mt_safe font_cache;
	// function call : long (*const)()
	// function call : s_observer_result *(*const)(long)
	// function call : void (*const)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *)
	todo("implement");
	_sub_1095ACD0();
}

_extern void _sub_1095CCF0(real_point3d *, real_vector3d *, float);
void offset_and_scale_position_easing_type_one(real_point3d *position, real_vector3d *offset, float scale) // 0x1095CCF0
{
	// `anonymous-namespace'::offset_and_scale_position_easing_type_one
	// float scale;
	todo("implement");
	_sub_1095CCF0(position, offset, scale);
}

_extern void _sub_1095CD90(real_point3d *, real_vector3d *, real_vector3d *, float);
void offset_and_scale_position_easing_type_two(real_point3d *position, real_vector3d *offset, real_vector3d *offset_2, float scale) // 0x1095CD90
{
	// `anonymous-namespace'::offset_and_scale_position_easing_type_two
	// float scale;
	// float offset_d;
	// float stored_pos;
	todo("implement");
	_sub_1095CD90(position, offset, offset_2, scale);
}

_extern void _sub_1095B720(real_vector3d *, real_vector3d *, real_vector3d *, float);
void lerp_vector(real_vector3d *out_vec, real_vector3d *vec1, real_vector3d *vec2, float s) // 0x1095B720
{
	// `anonymous-namespace'::lerp_vector
	// float s;
	todo("implement");
	_sub_1095B720(out_vec, vec1, vec2, s);
}

_extern void _sub_1095B6D0(float *, float, float, float);
void lerp_real(float *out_val, float a, float b, float s) // 0x1095B6D0
{
	// `anonymous-namespace'::lerp_real
	// float s;
	todo("implement");
	_sub_1095B6D0(out_val, a, b, s);
}

_extern void _sub_1095E7D0(real_vector3d *, real_vector3d *, real_vector3d *, real_vector3d *, real_vector3d *, real_vector3d *, float);
void slerp_rotational_vectors(real_vector3d *out_f, real_vector3d *out_up, real_vector3d *a, real_vector3d *a_up, real_vector3d *b, real_vector3d *b_up, float s) // 0x1095E7D0
{
	// `anonymous-namespace'::slerp_rotational_vectors
	// static ...; // 0x1095E9B4
	// static ...; // 0x1095E960
	// static ...; // 0x1095E958
	// real_vector3d *out_f;
	// real_vector3d *out_up;
	// real_vector3d *a;
	// real_vector3d *a_up;
	// real_vector3d *b;
	// real_vector3d *b_up;
	// float s;
	// real_matrix4x3 next_rotation_matrix;
	// real_quaternion next_rotation_quat;
	// void (*const matrix4x3_from_point_and_vectors)(real_matrix4x3 *, real_point3d const *, real_vector3d *, real_vector3d *);
	// void (*const quaternions_slerp_interpolate_and_normalize)(real_quaternion *, real_quaternion *, float, real_quaternion *);
	// void (*const matrix4x3_from_point_and_quaternion)(real_matrix4x3 *, real_point3d const *, real_quaternion *);
	// real_matrix4x3 new_rotation_matrix;
	// void (*const matrix4x3_to_point_and_vectors)(real_matrix4x3 *, real_vector3d *, real_vector3d *, real_vector3d *);
	// real_quaternion rotation_quat;
	// real_quaternion new_rotation;
	// real_vector3d out_pos;
	// void (*const matrix4x3_rotation_to_quaternion)(real_matrix4x3 *, real_quaternion *);
	// real_matrix4x3 rotation_matrix;
	// function call : void (*const)(real_matrix4x3 *, real_point3d const *, real_vector3d *, real_vector3d *)
	// function call : void (*const)(real_matrix4x3 *, real_quaternion *)
	// function call : void (*const)(real_matrix4x3 *, real_point3d const *, real_vector3d *, real_vector3d *)
	// function call : void (*const)(real_matrix4x3 *, real_quaternion *)
	// function call : void (*const)(real_quaternion *, real_quaternion *, float, real_quaternion *)
	// function call : void (*const)(real_matrix4x3 *, real_point3d const *, real_quaternion *)
	// function call : void (*const)(real_matrix4x3 *, real_vector3d *, real_vector3d *, real_vector3d *)
	todo("implement");
	_sub_1095E7D0(out_f, out_up, a, a_up, b, b_up, s);
}

_extern void _sub_10959160(s_camera_frame *, s_camera_frame *, s_camera_frame *, float);
void build_interpolated_camera_frame(s_camera_frame *out_frame, s_camera_frame *a, s_camera_frame *b, float s) // 0x10959160
{
	// `anonymous-namespace'::build_interpolated_camera_frame
	// float s;
	todo("implement");
	_sub_10959160(out_frame, a, b, s);
}

_extern void _sub_1095CB60(s_observer_command *, real_matrix4x3 *, s_camera_frame *);
void observer_set_camera_frame(s_observer_command *observer_command, real_matrix4x3 *camera_matrix, s_camera_frame *frame) // 0x1095CB60
{
	// `anonymous-namespace'::observer_set_camera_frame
	// s_camera_frame *frame;
	// float (*const calculate_field_of_view)(float);
	// function call : float (*const)(float)
	todo("implement");
	_sub_1095CB60(observer_command, camera_matrix, frame);
}

_extern void _sub_1095D3B0(void *, void *, s_observer_command *);
void scripted_camera_update_call_hook(void *a1, void *camera_control, s_observer_command *observer_command) // 0x1095D3B0
{
	// `anonymous-namespace'::scripted_camera_update_call_hook
	// static ...; // 0x1095E34A
	// static ...; // 0x1095E33A
	// static ...; // 0x1095E32C
	// static ...; // 0x1095E324
	// static ...; // 0x1095E316
	// static ...; // 0x1095E306
	// static ...; // 0x1095E2FE
	// static ...; // 0x1095E2F0
	// static ...; // 0x1095E278
	// static ...; // 0x1095E270
	// void *a1;
	// void *camera_control;
	// s_observer_command *observer_command;
	// void (*const render_texture_camera_off)();
	// s_scripted_camera_globals *scripted_camera_globals;
	// void (*const render_texture_camera_on)();
	// float (*const observer_suggested_field_of_view)();
	// void (*const matrix3x3_multiply)(real_matrix3x3 *, real_matrix3x3 *, real_matrix3x3 *);
	// void (*const cinematic_camera_update_texture_camera)(s_camera_frame *);
	// void (*const matrix4x3_from_point_and_vectors)(real_matrix4x3 *, real_point3d const *, real_vector3d *, real_vector3d *);
	// void (*const quaternions_slerp_interpolate_and_normalize)(real_quaternion *, real_quaternion *, float, real_quaternion *);
	// void (*const transform_into_flag_space)(real_matrix4x3 *, long);
	// void (*const scripted_camera_get_deterministic_cinematic_camera_matrix)(s_camera_frame const *, real_matrix4x3 *);
	// float field_of_view;
	// long (*const players_first_active_user)();
	// real_point3d *(*const observer_get_position)(long);
	// void (*const matrix4x3_from_point_and_quaternion)(real_matrix4x3 *, real_point3d const *, real_quaternion *);
	// void (*const scripted_camera_update)(void *, void *, s_observer_command *);
	// void (*const matrix4x3_to_point_and_vectors)(real_matrix4x3 *, real_vector3d *, real_vector3d *, real_vector3d *);
	// void (*const observer_validate_camera_command)(s_observer_command *);
	// bool render_texture_camera_active;
	// void (*const matrix4x3_rotation_from_axis_and_angle)(real_matrix4x3 *, real_vector3d *, float, float);
	// float (*const calculate_field_of_view)(float);
	// void (*const matrix4x3_rotation_to_quaternion)(real_matrix4x3 *, real_quaternion *);
	{
		// float fov_time_scale;
	}
	{
		// s_cinematic_scene_definition *const cisc;
		{
			// long scene_shot_index;
			// s_cinematic_scene_shot *const shot;
			{
				// real_matrix4x3 camera_matrix;
				// long interpolated_frames;
				// float vertical_angle;
				// s_camera_frame *const camera_frame;
				// real_matrix4x3 rotation;
				// bool interpolate_frame;
				// long scene_frame_index;
				// float horizontal_axis;
				// float vertical_axis;
				// s_camera_frame interpolated_frame;
				// long next_frame_index;
				// float tick_scale;
				// float horizontal_angle;
				{
					// float s;
					// s_camera_frame *const next_frame;
					// long ticks_elapsed;
				}
				{
					// float current_frame_time;
					{
						// float unknown_scale;
						// float scaled_frame_time;
						// real_quaternion rotation_quat;
						// real_vector3d out_pos;
						// real_matrix4x3 rotation_matrix;
					}
				}
				{
					{
					}
				}
			}
			{
				// __int32 i;
				{
					// s_cinematic_shot_extra_camera *const extra_camera;
					{
						// long shot_index;
						// s_cinematic_extra_camera_shot *const extra_shot;
						{
							// s_cinematic_extra_camera_frame *const extra_frame;
							// long frame_index;
							{
								// real_matrix4x3 camera_matrix;
								// s_camera_frame *const camera_frame;
							}
						}
					}
				}
			}
		}
	}
	{
		// long output_user_index;
		{
			// real_point3d *observer_position;
		}
	}
	// function call : void (*const)(void *, void *, s_observer_command *)
	// function call : float (*const)()
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : void *(*const)(unsigned long, long)
	// function call : long (*const)()
	// function call : void (*const)(s_camera_frame const *, real_matrix4x3 *)
	// function call : void (*const)(s_camera_frame const *, real_matrix4x3 *)
	// function call : void (*const)(real_matrix4x3 *, real_vector3d *, float, float)
	// function call : void (*const)(real_matrix3x3 *, real_matrix3x3 *, real_matrix3x3 *)
	// function call : void (*const)(real_matrix4x3 *, real_vector3d *, float, float)
	// function call : void (*const)(real_matrix3x3 *, real_matrix3x3 *, real_matrix3x3 *)
	// function call : float (*const)(float)
	// function call : void (*const)(real_matrix4x3 *, real_point3d const *, real_vector3d *, real_vector3d *)
	// function call : void (*const)(real_matrix4x3 *, real_quaternion *)
	// function call : void (*const)(real_quaternion *, real_quaternion *, float, real_quaternion *)
	// function call : void (*const)(real_matrix4x3 *, real_point3d const *, real_quaternion *)
	// function call : void (*const)(real_matrix4x3 *, real_vector3d *, real_vector3d *, real_vector3d *)
	// function call : float (*const)(float)
	// function call : void (*const)(real_quaternion *, real_quaternion *, float, real_quaternion *)
	// function call : void (*const)(real_matrix4x3 *, real_point3d const *, real_quaternion *)
	// function call : void (*const)(real_matrix4x3 *, real_vector3d *, real_vector3d *, real_vector3d *)
	// function call : void (*const)(s_camera_frame *)
	// function call : void (*const)(real_matrix4x3 *, real_point3d const *, real_vector3d *, real_vector3d *)
	// function call : void (*const)(real_matrix4x3 *, long)
	// function call : long (*const)()
	// function call : real_point3d *(*const)(long)
	// function call : void (*const)()
	// function call : void (*const)()
	// function call : void (*const)(s_observer_command *)
	todo("implement");
	_sub_1095D3B0(a1, camera_control, observer_command);
}

_extern void _sub_109594F0(c_flying_camera *, void *, long, float, s_observer_command *);
void c_flying_camera__update_hook(c_flying_camera *thisptr, void *__formal, long user_index, float dt, s_observer_command *result) // 0x109594F0
{
	// `anonymous-namespace'::c_flying_camera__update_hook
	// static ...; // 0x10959A9C
	// static ...; // 0x10959A94
	// c_flying_camera *thisptr;
	// void *__formal;
	// long user_index;
	// float dt;
	// s_observer_command *result;
	// long player_index;
	// real_vector3d forward;
	// long controller_index;
	// float rb;
	// float moveSpeed;
	// float vertSpeed;
	// float boostPow;
	// bool controllerEnabled;
	// Blam::Input::PlayerInputState *state;
	// float lb;
	// float boost;
	// float k_camera_pitch_threshold;
	// real_vector3d left;
	// real_vector3d up;
	{
		// real_euler_angles2d vel;
	}
	// function call : unsigned long (*const)(long)
	todo("implement");
	_sub_109594F0(thisptr, __formal, user_index, dt, result);
}

_extern void _sub_1095D0D0(long, real_matrix4x3 *);
void player_effect_apply_camera_effect_matrix_hook(long output_user_index, real_matrix4x3 *camera_matrix) // 0x1095D0D0
{
	// `anonymous-namespace'::player_effect_apply_camera_effect_matrix_hook
	// static ...; // 0x1095D219
	// static ...; // 0x1095D20C
	// static ...; // 0x1095D1E8
	// static ...; // 0x1095D1E0
	// long output_user_index;
	// real_matrix4x3 *camera_matrix;
	// void (*const player_effect_apply_camera_effect_matrix)(long, real_matrix4x3 *);
	// void (*const get_shake_matrix)(float, float, real_matrix4x3 *);
	// float shake_translation;
	// float shake_rotation;
	{
		// real_matrix4x3 shake_matrix;
	}
	// function call : void (*const)(long, real_matrix4x3 *)
	// function call : void (*const)(float, float, real_matrix4x3 *)
	todo("implement");
	_sub_1095D0D0(output_user_index, camera_matrix);
}

_extern void _sub_1095B7E0(long, s_focus_and_distance *);
void observer_compute_result_hook(long output_user_index, s_focus_and_distance *focus_and_distance) // 0x1095B7E0
{
	// `anonymous-namespace'::observer_compute_result_hook
	// static ...; // 0x1095C094
	// static ...; // 0x1095C07C
	// static ...; // 0x1095C074
	// long output_user_index;
	// s_focus_and_distance *focus_and_distance;
	// real_vector3d *forward;
	// void (*const observer_result_compute_parameters)(s_observer_result *);
	// bool (*const valid_real_vector3d_axes2)(real_vector3d const *, real_vector3d const *);
	// float const g_camera_focus_distance_max;
	// s_camera_globals const &g_camera_globals;
	// s_observer *observer;
	// float focus_distance;
	// void (*const observer_result_set_position)(long, real_point3d const *, float, real_vector3d *);
	// real_vector3d *up;
	// real_point3d focus_position;
	{
		// real_vector3d left;
	}
	{
		// float i;
		// float j;
		// float magnitude;
	}
	{
		// float fov_degrees;
		// float hfov;
	}
	// function call : bool (*const)(real_vector3d const *, real_vector3d const *)
	// function call : void (*const)(s_observer_result *)
	// function call : void (*const)(long, real_point3d const *, float, real_vector3d *)
	todo("implement");
	_sub_1095B7E0(output_user_index, focus_and_distance);
}

_extern void _sub_1095C2E0(long, real_matrix4x3 *);
void observer_compute_view_offset_matrix_hook(long output_user_index, real_matrix4x3 *view_matrix) // 0x1095C2E0
{
	// `anonymous-namespace'::observer_compute_view_offset_matrix_hook
	// real_matrix4x3 *view_matrix;
	// float view_offset_scale;
	{
		// float yaw;
		// float half_vfov;
		// s_observer *observer;
		// float aspect;
		// float pitch;
	}
	{
	}
	todo("implement");
	_sub_1095C2E0(output_user_index, view_matrix);
}

_extern void _sub_1095C610(s_observer_result *);
void observer_result_compute_parameters_hook(s_observer_result *result) // 0x1095C610
{
	// `anonymous-namespace'::observer_result_compute_parameters_hook
	// static ...; // 0x1095CA3D
	// static ...; // 0x1095CA36
	// static ...; // 0x1095CA30
	// static ...; // 0x1095CA0C
	// static ...; // 0x1095CA04
	// s_observer_result *result;
	// float vfov;
	// real_vector3d old_forward;
	// real_vector3d right;
	// float hfov;
	// float dot_inv;
	// real_matrix3x3 matrix;
	// float view_offset_scale;
	// float atan0;
	// float pitch;
	todo("implement");
	_sub_1095C610(result);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_enum<enum e_scripted_camera_mode,short>::operator!=(e_scripted_camera_mode const &) const;
template bool c_enum<enum e_scripted_camera_mode,short>::operator==(e_scripted_camera_mode const &) const;
template bool c_tag_block<s_camera_frame>::try_get_element(__int32, s_camera_frame **) const;
template bool c_tag_block<s_cinematic_extra_camera_frame>::try_get_element(__int32, s_cinematic_extra_camera_frame **) const;
template bool c_tag_block<s_cinematic_extra_camera_shot>::try_get_element(__int32, s_cinematic_extra_camera_shot **) const;
template bool c_tag_block<s_cinematic_shot_extra_camera>::try_get_element(__int32, s_cinematic_shot_extra_camera **) const;
template bool c_tag_block<s_game_globals_camera>::try_get_element(__int32, s_game_globals_camera **) const;
template bool c_tag_block<s_unit_seat_definition>::try_get_element(__int32, s_unit_seat_definition **) const;
template c_flags<enum e_unit_seat_flags,long> c_flags<enum e_unit_seat_flags,long>::operator&(__int32 const) const;
template c_flags<enum e_unit_seat_flags,long>::c_flags(c_flags<enum e_unit_seat_flags,long> const &);
template c_flags<enum e_unit_seat_flags,long>::c_flags(long const &);
template c_flags<enum e_unit_seat_flags,long>::operator bool() const;
template s_camera_frame & c_tag_block<s_camera_frame>::operator[](__int32);
template s_camera_frame * c_tag_block<s_camera_frame>::get_element(__int32) const;
template s_cinematic_extra_camera_frame & c_tag_block<s_cinematic_extra_camera_frame>::operator[](__int32);
template s_cinematic_extra_camera_frame * c_tag_block<s_cinematic_extra_camera_frame>::get_element(__int32) const;
template s_cinematic_extra_camera_shot & c_tag_block<s_cinematic_extra_camera_shot>::operator[](__int32);
template s_cinematic_extra_camera_shot * c_tag_block<s_cinematic_extra_camera_shot>::get_element(__int32) const;
template s_cinematic_shot_extra_camera & c_tag_block<s_cinematic_shot_extra_camera>::operator[](__int32);
template s_cinematic_shot_extra_camera * c_tag_block<s_cinematic_shot_extra_camera>::get_element(__int32) const;
template s_game_globals_camera * c_tag_block<s_game_globals_camera>::get_element(__int32) const;
template s_game_globals_camera * c_tag_block<s_game_globals_camera>::operator->();
template s_unit_seat_definition & c_tag_block<s_unit_seat_definition>::operator[](__int32);
template s_unit_seat_definition * c_tag_block<s_unit_seat_definition>::get_element(__int32) const;
