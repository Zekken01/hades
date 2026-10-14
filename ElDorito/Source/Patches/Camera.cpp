/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/camera/camera.hpp"
#include "Blam/camera/director.hpp"
#include "Blam/camera/observer.hpp"
#include "Blam/camera/scripted_camera.hpp"
#include "Blam/input/input.hpp"  // hades: added for 0x109594F0
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

extern void matrix3x3_from_axis_and_angle(real_matrix3x3 *matrix, real_vector3d const *axis, float sin_theta, float cos_theta);  // hades: added for 0x1095C610
extern real_vector3d *matrix3x3_transform_vector(real_matrix3x3 const *matrix, real_vector3d const *vector, real_vector3d *result);  // hades: added for 0x1095C610
real_vector3d *cross_product3d(real_vector3d const *a, real_vector3d const *b, real_vector3d *result);  // hades: added for 0x1095C610
namespace Patches { namespace RawInput { void UpdateCameraYawPitch(float deltaX, float deltaY, float &yaw, float &pitch); } }  // hades: added for 0x109594F0
extern s_input_globals &input_globals;  // hades: added for 0x109594F0
float screen_effect_apply_field_of_view_scale(long output_user_index, real_point3d *position, real_vector3d *forward, float fov);  // hades: added for 0x1095B7E0
real_point3d *matrix4x3_transform_point(real_matrix4x3 const *matrix, real_point3d const *point, real_point3d *result);  // hades: added for 0x1095B7E0
real_vector3d *matrix4x3_transform_vector(real_matrix4x3 const *matrix, real_vector3d const *vector, real_vector3d *result);  // hades: added for 0x1095B7E0
real_vector3d *vector3d_from_euler_angles2d(real_vector3d *forward, real_euler_angles2d const *angles);  // hades: added for 0x109594F0
real_vector3d *generate_up_vector3d(real_vector3d const *forward, real_vector3d *up);  // hades: added for 0x109594F0
float normalize3d(real_vector3d *v);  // hades: added for 0x109594F0
float dot_product3d(real_vector3d const *a, real_vector3d const *b);  // hades: added for 0x1095C610

extern real_euler_angles3d *euler_angles3d_from_vectors3d(real_euler_angles3d *angles, real_vector3d const *forward, real_vector3d const *up);  // hades: added for 0x1095ACD0

void matrix3x3_from_angles(real_matrix3x3 *matrix, float yaw, float pitch, float roll);  // hades: added for 0x1095C2E0

namespace Patches
{
	namespace Camera
	{
		extern void ApplyAll();
		extern void ApplyAfterTagsLoaded();
		extern bool SetForcedCameraMode(std::string const mode);
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
static void OnMapLoaded(char const *mapPath);
float GetScriptedCameraFovHook();
void __fastcall c_following_camera__update_hook(void *thisptr, void *unused, __int32 localPlayerIndex, __int32 a4, unsigned char *state);
__int32 unit_use_third_person_camera(unsigned long object_index, __int32 *a2);
bool director_scripting_get_hook();
bool __fastcall c_director__set_camera_mode_internal_hook(void *thisPtr, void *unused, __int32 camera_mode, float camera_speed, bool a4);
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
void __fastcall c_flying_camera__update_hook(c_flying_camera *thisptr, void *__formal, long user_index, float dt, s_observer_command *result);
void player_effect_apply_camera_effect_matrix_hook(long output_user_index, real_matrix4x3 *camera_matrix);
void observer_compute_result_hook(long output_user_index, s_focus_and_distance *focus_and_distance);
void observer_compute_view_offset_matrix_hook(long output_user_index, real_matrix4x3 *view_matrix);
void observer_result_compute_parameters_hook(s_observer_result *result);

/* ---------- globals */

extern void screen_effect_get_camera_shake(long output_user_index, float *translational, float *rotational);  // hades: added for 0x1095D0D0
extern void matrix4x3_multiply(real_matrix4x3 const *m1, real_matrix4x3 const *m2, real_matrix4x3 *result);  // hades: added for 0x1095D0D0
extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>); // 0x11248848
extern float (*const game_seconds_to_ticks_real)(float);  // hades: added for 0x1095D3B0
extern long (*const game_tick_rate)();  // hades: added for 0x1095D3B0
extern bool (*const game_time_get_paused)();  // hades: added for 0x1095D3B0

/* ---------- private variables */

namespace hades_file_local
{
	extern "C" e_camera_mode cameraMode; // 0x11353BB0
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
		void ApplyAll() // 0x10956FE0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Camera@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x687B3C, director_perspective_for_sprint_meter_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x32161E, director_game_desired_perspective_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x321B62, director_game_desired_perspective_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x32651B, director_game_desired_perspective_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x327110, director_game_desired_perspective_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x191BE0, director_inhibited_facing_hook).Apply();
			Hook(0x32E18C, GetScriptedCameraFovHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0x16724DC).Write<unsigned int>(reinterpret_cast<unsigned int>(c_following_camera__update_hook));
			Hook(0x1917E0, unit_use_third_person_camera).Apply();
			Hook(0x3219DC, director_scripting_get_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x193203, c_director__set_camera_mode_internal_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x191980, director_game_tick_hook).Apply();
			Hook(0x32C7F6, scripted_camera__player_mapping_get_input_controller_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x32F15A, scripted_camera_update_call_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x65F2D3, { 0xF4, 0xFE }).Apply();
			Patch(0x65E5AC, { 0xF8, 0xFE }).Apply();
			Hook(0x2047A8, director_render_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x743764, unit_camera_override_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x749F7E, unit_update_aiming_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0x16726D8).Write(c_flying_camera__update_hook);
			Hook(0x210A99, player_effect_apply_camera_effect_matrix_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x213ADB, observer_compute_result_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x212460, observer_compute_view_offset_matrix_hook).Apply();
			Hook(0x2131E0, observer_result_compute_parameters_hook).Apply();
			Hook(0x1D5070, equipped_weap_allows_3p_zoom, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x191D04, camera_globals_initialize_from_tags_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patches::Core::OnMapLoaded(::OnMapLoaded);
		}

		void ApplyAfterTagsLoaded() // 0x10956FC0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAfterTagsLoaded@Camera@Patches@@YAXXZ");
			// procedure flags: nofpo
		}

		bool SetForcedCameraMode(std::string const mode) // 0x10958AF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetForcedCameraMode@Camera@Patches@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// std::string mode;
			// constexpr bool (*const `Patches::Camera::SetForcedCameraMode'::`2'::player_terminal_chud_set)(bool); // constant == 11050832
				// e_camera_mode currentMode;
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

			static bool (*const player_terminal_chud_set)(bool) = (bool (*)(bool))0xA89F50;
			cameraMode = _camera_mode_none;
			if (!mode.compare("flying"))
			{
				((bool (__cdecl *)(long, long))0x592480)(0, 3);
				((void (__cdecl *)(long, long))0x5923C0)(0, 2);
				e_camera_mode currentMode = ((c_director *(__cdecl *)(long))0x591990)(0)->get_camera()->get_type();
				cameraMode = currentMode == _camera_mode_flying ? _camera_mode_flying : cameraMode;
			}
			else if (!mode.compare("static"))
			{
				((bool (__cdecl *)(long, long))0x592480)(0, 0);
				((void (__cdecl *)(long, long))0x5923C0)(0, 5);
				e_camera_mode currentMode = ((c_director *(__cdecl *)(long))0x591990)(0)->get_camera()->get_type();
				cameraMode = currentMode == _camera_mode_static ? _camera_mode_static : cameraMode;
			}
			else if (!mode.compare("scripted"))
			{
				((bool (__cdecl *)(long, long))0x592480)(0, 0);
				((void (__cdecl *)(long, long))0x5923C0)(0, 6);
				e_camera_mode currentMode = ((c_director *(__cdecl *)(long))0x591990)(0)->get_camera()->get_type();
				cameraMode = currentMode == _camera_mode_scripted ? _camera_mode_scripted : cameraMode;
			}
			else if (!mode.compare("first"))
			{
				((bool (__cdecl *)(long, long))0x592480)(0, 0);
				((void (__cdecl *)(long, long))0x5923C0)(0, 3);
				e_camera_mode currentMode = ((c_director *(__cdecl *)(long))0x591990)(0)->get_camera()->get_type();
				cameraMode = currentMode == _camera_mode_first_person ? _camera_mode_first_person : cameraMode;
			}
			else if (!mode.compare("third"))
			{
				((bool (__cdecl *)(long, long))0x592480)(0, 0);
				((void (__cdecl *)(long, long))0x5923C0)(0, 0);
				e_camera_mode currentMode = ((c_director *(__cdecl *)(long))0x591990)(0)->get_camera()->get_type();
				cameraMode = currentMode == _camera_mode_following ? _camera_mode_following : cameraMode;
			}
			else if (!mode.compare("default"))
			{
				((bool (__cdecl *)(long, long))0x592480)(0, 0);
				((void (__cdecl *)(long, long))0x5923C0)(0, 3);
				e_camera_mode currentMode = ((c_director *(__cdecl *)(long))0x591990)(0)->get_camera()->get_type();
				cameraMode = currentMode == _camera_mode_first_person ? _camera_mode_none : cameraMode;
			}
			else
				return false;
			player_terminal_chud_set(mode != "flying" && mode != "static");
			return true;
		}
	}
}


namespace Patches
{
	namespace Camera
	{
		e_camera_mode GetForcedCameraMode() // 0x109589A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetForcedCameraMode@Camera@Patches@@YA?AW4e_camera_mode@@XZ");
			// procedure flags: nofpo

			return cameraMode;
		}
	}
}

/* ---------- private code */

long director_game_desired_perspective_hook(long unit_index, long *out_seat_state) // 0x1095A750
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?director_game_desired_perspective_hook@@YAJJPAJ@Z");
	// `anonymous-namespace'::director_game_desired_perspective_hook
	// long *out_seat_state;
	// s_player_datum *player;
	// long player_index;
	// function call : long (*)(long, long *)

	long player_index = unit_get_current_or_last_weak_player_index(unit_index);
	s_player_datum *player = player_get(player_index);

	if (player && player->traits.extended.use_third_person_camera == c_player_trait_extended::_third_person_camera_enabled)
	{
		*out_seat_state = 4;

		return 1;
	}

	return ((long (*)(long, long *))0x5917E0)(unit_index, out_seat_state);
}

bool weapon_prevents_sprinting(long weapon_index) // 0x1095F230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?weapon_prevents_sprinting@@YA_NJ@Z");
	// `anonymous-namespace'::weapon_prevents_sprinting
	// long weapon_index;
	// void *weapon_definition;
	// s_object_data *weapon;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void *(*const)(unsigned long, long)

	s_object_data *weapon = object_try_and_get_and_verify_type(weapon_index, 4);

	if (!weapon)
		return false;

	void *weapon_definition = tag_get(0x77656170, weapon->definition_index);

	return weapon_definition && (*(long *)((unsigned char *)weapon_definition + 0x1d4) & 0x40000) != 0;
}

long director_perspective_for_sprint_meter_hook(long output_user_index) // 0x1095AB10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?director_perspective_for_sprint_meter_hook@@YAJJ@Z");
	// `anonymous-namespace'::director_perspective_for_sprint_meter_hook
	// long output_user_index;
	// long perspective;
		// s_player_datum *player;
		// long player_index;
			// s_unit_data *unit;
			// long unit_index;
				// long weapon_index;
				// long weapon_inventory_index;
	// function call : e_director_perspective (*const)(long)
	// function call : unsigned long (*const)(long)
	// function call : unsigned long (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)

	long perspective = ((long (*)(long))0x591A40)(output_user_index);
	if (perspective == 1)
	{
		long player_index = ((long (*)(long))0x589C60)(output_user_index);
		s_player_datum *player = player_get(player_index);
		if (player && player->traits.extended.use_third_person_camera == c_player_trait_extended::_third_person_camera_enabled)
		{
			long unit_index = ((long (*)(long))0x589CC0)(output_user_index);
			s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003);
			if (unit)
			{
				long weapon_inventory_index = unit->current_weapon_set.indices[0];
				long weapon_index = unit->weapon_object_indices[weapon_inventory_index];
				if (weapon_index != -1 && weapon_prevents_sprinting(weapon_index))
					return perspective;
			}
			perspective = 0;
		}
	}
	return perspective;
}

bool director_inhibited_facing_hook(long output_user_index) // 0x1095AA40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?director_inhibited_facing_hook@@YA_NJ@Z");
	// `anonymous-namespace'::director_inhibited_facing_hook
	// long output_user_index;
	// unsigned long unit_index;
	// function call : unsigned long (*const)(long)
	// function call : c_director *(*const)(long)
	// function call : bool () const

	unsigned long unit_index = ((unsigned long (*)(long))0x589CC0)(output_user_index);

	if (unit_index != NONE && Player::CPlayerEmotes::UnitCameraMovementInhibited(unit_index))
	{
		return true;
	}

	return ((c_director *(*)(long))0x591990)(output_user_index)->inhibits_facing();
}

bool unit_camera_override_hook(long unit_index, s_unit_camera_definition **camera) // 0x1095ED00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_camera_override_hook@@YA_NJPAPAUs_unit_camera_definition@@@Z");
	// `anonymous-namespace'::unit_camera_override_hook
	// s_unit_camera_definition **camera;
	// bool (*const equipment_get_unit_camera)(long, s_unit_camera_definition **);
	// function call : bool (*const)(long, s_unit_camera_definition **)

	const auto equipment_get_unit_camera = (bool(*)(long, s_unit_camera_definition **))0xB40BF0;

	if (equipment_get_unit_camera(unit_index, camera))
	{
		return true;
	}

	if (Player::CPlayerEmotes::GetUnitCamera(unit_index, camera))
	{
		return true;
	}

	return false;
}

void unit_update_aiming_hook(long unit_index) // 0x1095EDA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_update_aiming_hook@@YAXJ@Z");
	// `anonymous-namespace'::unit_update_aiming_hook
	// long unit_index;
	// void (*const unit_update_aiming)(long);
	// function call : void (*const)(long)

	if (Player::CPlayerEmotes::UnitMovementInhibited(unit_index))
	{
		return;
	}

	void (*const unit_update_aiming)(long) = reinterpret_cast<void (*)(long)>(0xB4A2C0);
	unit_update_aiming(unit_index);
}

__int32 equipped_weap_allows_3p_zoom() // 0x1095B110
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?equipped_weap_allows_3p_zoom@@YAHXZ");
	// `anonymous-namespace'::equipped_weap_allows_3p_zoom
	// procedure flags: nofpo
	// long perspective;
	// unsigned long unit_index;
		// s_unit_data *unit;
			// char inventoryIndex;
				// long weaponIndex;
	// function call : e_director_perspective (*const)(long)
	// function call : unsigned long (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : bool (*const)(long)

	static e_director_perspective (*const director_get_perspective)(long) = reinterpret_cast<e_director_perspective (*)(long)>(0x591A40);
	static unsigned long (*const player_get_unit_index)(long) = reinterpret_cast<unsigned long (*)(long)>(0x589CC0);
	static bool (*const weapon_has_zoom)(long) = reinterpret_cast<bool (*)(long)>(0xB64300);
	long perspective = director_get_perspective(0);
	if (perspective != _perspective_orbiting)
		return perspective;
	unsigned long unit_index = player_get_unit_index(0);
	if (unit_index != -1)
	{
		s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 1);
		if (unit)
		{
			char inventoryIndex = unit->current_weapon_set.indices[0];
			if (inventoryIndex != -1)
			{
				long weaponIndex = unit->weapon_object_indices[inventoryIndex];
				if (weapon_has_zoom(weaponIndex))
					return 0;
			}
		}
	}
	return 1;
}

void camera_globals_initialize_from_tags_hook() // 0x10959F90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?camera_globals_initialize_from_tags_hook@@YAXXZ");
	// `anonymous-namespace'::camera_globals_initialize_from_tags_hook
	// procedure flags: nofpo
	// s_camera_globals *g_old_camera_globals;
	// s_camera_globals *g_camera_globals;
	// s_camera_globals *camera_globals_definition;

	s_camera_globals *camera_globals_definition = &game_globals_get()->Camera->global_defaults;
	s_camera_globals *g_camera_globals = (s_camera_globals *)0x18ECE00;
	s_camera_globals *g_old_camera_globals = (s_camera_globals *)0x471AF40;
	if (!(*(unsigned long *)0x471AFD4 & 1))
	{
		*(unsigned long *)0x471AFD4 |= 1;
		memcpy(g_old_camera_globals, g_camera_globals, sizeof(s_camera_globals));
	}
	if (g_camera_globals->yaw_scale == g_old_camera_globals->yaw_scale)
		g_camera_globals->yaw_scale = camera_globals_definition->yaw_scale;
	if (g_camera_globals->pitch_scale == g_old_camera_globals->pitch_scale)
		g_camera_globals->pitch_scale = camera_globals_definition->pitch_scale;
	if (g_camera_globals->forward_scale == g_old_camera_globals->forward_scale)
		g_camera_globals->forward_scale = camera_globals_definition->forward_scale;
	if (g_camera_globals->side_scale == g_old_camera_globals->side_scale)
		g_camera_globals->side_scale = camera_globals_definition->side_scale;
	if (g_camera_globals->up_scale == g_old_camera_globals->up_scale)
		g_camera_globals->up_scale = camera_globals_definition->up_scale;
	if (g_camera_globals->transition_time == g_old_camera_globals->transition_time)
		g_camera_globals->transition_time = camera_globals_definition->transition_time;
	if (g_camera_globals->falling_death_transition_time == g_old_camera_globals->falling_death_transition_time)
		g_camera_globals->falling_death_transition_time = camera_globals_definition->falling_death_transition_time;
	if (g_camera_globals->initial_distance == g_old_camera_globals->initial_distance)
		g_camera_globals->initial_distance = camera_globals_definition->initial_distance;
	if (g_camera_globals->final_distance == g_old_camera_globals->final_distance)
		g_camera_globals->final_distance = camera_globals_definition->final_distance;
	if (g_camera_globals->dead_cam_z_offset == g_old_camera_globals->dead_cam_z_offset)
		g_camera_globals->dead_cam_z_offset = camera_globals_definition->dead_cam_z_offset;
	if (g_camera_globals->dead_cam_maximum_elevation == g_old_camera_globals->dead_cam_maximum_elevation)
		g_camera_globals->dead_cam_maximum_elevation = camera_globals_definition->dead_cam_maximum_elevation;
	if (g_camera_globals->dead_cam_movement_delay == g_old_camera_globals->dead_cam_movement_delay)
		g_camera_globals->dead_cam_movement_delay = camera_globals_definition->dead_cam_movement_delay;
	if (g_camera_globals->time_to_auto_switch_to_orbiting == g_old_camera_globals->time_to_auto_switch_to_orbiting)
		g_camera_globals->time_to_auto_switch_to_orbiting = camera_globals_definition->time_to_auto_switch_to_orbiting;
	if (g_camera_globals->dead_camera_minimum_falling_velocity == g_old_camera_globals->dead_camera_minimum_falling_velocity)
		g_camera_globals->dead_camera_minimum_falling_velocity = camera_globals_definition->dead_camera_minimum_falling_velocity;
	if (g_camera_globals->maximum_boost_speed == g_old_camera_globals->maximum_boost_speed)
		g_camera_globals->maximum_boost_speed = camera_globals_definition->maximum_boost_speed;
	if (g_camera_globals->time_to_maximum_boost == g_old_camera_globals->time_to_maximum_boost)
		g_camera_globals->time_to_maximum_boost = camera_globals_definition->time_to_maximum_boost;
	if (g_camera_globals->boost_function == g_old_camera_globals->boost_function)
		g_camera_globals->boost_function = camera_globals_definition->boost_function;
	if (g_camera_globals->zoomed_field_of_view == g_old_camera_globals->zoomed_field_of_view)
		g_camera_globals->zoomed_field_of_view = camera_globals_definition->zoomed_field_of_view;
	if (g_camera_globals->zoomed_look_speed == g_old_camera_globals->zoomed_look_speed)
		g_camera_globals->zoomed_look_speed = camera_globals_definition->zoomed_look_speed;
	if (g_camera_globals->bounding_sphere_radius == g_old_camera_globals->bounding_sphere_radius)
		g_camera_globals->bounding_sphere_radius = camera_globals_definition->bounding_sphere_radius;
	if (g_camera_globals->flying_cam_movement_delay == g_old_camera_globals->flying_cam_movement_delay)
		g_camera_globals->flying_cam_movement_delay = camera_globals_definition->flying_cam_movement_delay;
	if (g_camera_globals->zoom_transition_time == g_old_camera_globals->zoom_transition_time)
		g_camera_globals->zoom_transition_time = camera_globals_definition->zoom_transition_time;
	if (g_camera_globals->vertical_movement_time_to_max_speed == g_old_camera_globals->vertical_movement_time_to_max_speed)
		g_camera_globals->vertical_movement_time_to_max_speed = camera_globals_definition->vertical_movement_time_to_max_speed;
	if (g_camera_globals->vertical_movement_function == g_old_camera_globals->vertical_movement_function)
		g_camera_globals->vertical_movement_function = camera_globals_definition->vertical_movement_function;
	if (g_camera_globals->survival_switch_time == g_old_camera_globals->survival_switch_time)
		g_camera_globals->survival_switch_time = camera_globals_definition->survival_switch_time;
	if (g_camera_globals->minimum_distance == g_old_camera_globals->minimum_distance)
		g_camera_globals->minimum_distance = camera_globals_definition->minimum_distance;
	if (g_camera_globals->maximum_distance == g_old_camera_globals->maximum_distance)
		g_camera_globals->maximum_distance = camera_globals_definition->maximum_distance;
	if (g_camera_globals->orbit_cam_movement_delay == g_old_camera_globals->orbit_cam_movement_delay)
		g_camera_globals->orbit_cam_movement_delay = camera_globals_definition->orbit_cam_movement_delay;
	if (g_camera_globals->orbit_cam_z_offset == g_old_camera_globals->orbit_cam_z_offset)
		g_camera_globals->orbit_cam_z_offset = camera_globals_definition->orbit_cam_z_offset;
	if (g_camera_globals->orbit_cam_minimum_elevation == g_old_camera_globals->orbit_cam_minimum_elevation)
		g_camera_globals->orbit_cam_minimum_elevation = camera_globals_definition->orbit_cam_minimum_elevation;
	if (g_camera_globals->orbit_cam_maximum_elevation == g_old_camera_globals->orbit_cam_maximum_elevation)
		g_camera_globals->orbit_cam_maximum_elevation = camera_globals_definition->orbit_cam_maximum_elevation;
	if (g_camera_globals->max_playback_speed == g_old_camera_globals->max_playback_speed)
		g_camera_globals->max_playback_speed = camera_globals_definition->max_playback_speed;
	if (g_camera_globals->fade_out_time == g_old_camera_globals->fade_out_time)
		g_camera_globals->fade_out_time = camera_globals_definition->fade_out_time;
	if (g_camera_globals->fade_in_time == g_old_camera_globals->fade_in_time)
		g_camera_globals->fade_in_time = camera_globals_definition->fade_in_time;
	if (g_camera_globals->enter_vehicle_transition_time == g_old_camera_globals->enter_vehicle_transition_time)
		g_camera_globals->enter_vehicle_transition_time = camera_globals_definition->enter_vehicle_transition_time;
	if (g_camera_globals->exit_vehicle_transition_time == g_old_camera_globals->exit_vehicle_transition_time)
		g_camera_globals->exit_vehicle_transition_time = camera_globals_definition->exit_vehicle_transition_time;
	memcpy(g_old_camera_globals, camera_globals_definition, sizeof(s_camera_globals));
}

void CameraModeReset() // 0x10958800
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CameraModeReset@@YAXXZ");
	// `anonymous-namespace'::CameraModeReset
	// procedure flags: nofpo
	// constexpr bool (*const `CameraModeReset'::`2'::player_terminal_chud_set)(bool); // constant == 11050832
	// e_camera_mode currentMode;
	// function call : void (*const)(long, e_director_mode)
	// function call : bool (*const)(long, long)
	// function call : c_director *(*const)(long)
	// function call : e_camera_mode ()
	// function call : bool (*const)(bool)

	static bool (*const player_terminal_chud_set)(bool) = (bool (*)(bool))0xA89F50;

	Modules::ModuleCamera::Instance().VarCameraFocusDistance->ValueInt = 0;
	Modules::ModuleCamera::Instance().VarCameraFocusDistance->ValueString = '0';
	if (Modules::ModuleCamera::Instance().VarCameraMode->ValueString == "default")
		return;

	Modules::ModuleCamera::Instance().VarCameraMode->ValueString = "default";
	cameraMode = _camera_mode_none;
	((bool (__cdecl *)(long, long))0x592480)(0, 0);
	((void (__cdecl *)(long, long))0x5923C0)(0, 3);
	e_camera_mode currentMode = ((c_director *(__cdecl *)(long))0x591990)(0)->get_camera()->get_type();
	cameraMode = currentMode == _camera_mode_first_person ? _camera_mode_none : cameraMode;
	player_terminal_chud_set(true);
}

static void OnMapLoaded(char const *mapPath) // 0x10958AB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnMapLoaded@@YAXPBD@Z");
	// `anonymous-namespace'::OnMapLoaded
	// char const *mapPath;

	CameraModeReset();
}

float GetScriptedCameraFovHook() // 0x109589C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetScriptedCameraFovHook@@YAMXZ");
	// `anonymous-namespace'::GetScriptedCameraFovHook
	// procedure flags: nofpo
	// bool (*const game_is_mainmenu)();
	// float fov;
		// float scriptedCameraFov;
	// function call : bool (*const)()

	const auto game_is_mainmenu = (bool(*)())(0x00531E90);

	auto fov = 0.0f;

	if (game_is_mainmenu())
	{
		fov = 70.0f;
	}
	else
	{
		auto scriptedCameraFov = *(float*)0x018ECE00;
		if (scriptedCameraFov == 0.0f)
			fov = *(float*)0x18BB1C8;
		else
			fov = scriptedCameraFov;
	}

	return fov * 0.017453292f;
}

void __fastcall c_following_camera__update_hook(void *thisptr, void *unused, __int32 localPlayerIndex, __int32 a4, unsigned char *state) // 0x10959C60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_following_camera__update_hook@@YIXPAX0HHPAE@Z");
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
		// s_unit_data *unit;
			// unsigned long weapon_index;
	// function call : unsigned long (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : bool (*const)(long)
	// function call : long (*const)(long, short)
	// function call : float (*const)(long)
	// function call : void (*const)(void *, __int32, __int32, unsigned char *)

	struct s_camera_definition
	{
		real_point3d Position;
		real_vector3d PositionShift;
		float LookShift[2];
		float Depth;
		float FieldOfView;
		real_vector3d Forward;
		real_vector3d Up;
	};
	bool (*const unit_in_vehicle)(long) = reinterpret_cast<bool (*)(long)>(0xBB29C0);
	void (__thiscall *const c_following_camera__update)(void *, __int32, __int32, unsigned char *) = reinterpret_cast<void (__thiscall *)(void *, __int32, __int32, unsigned char *)>(0x729730);
	Modules::ModuleCamera const &moduleCamera = Utils::Singleton<Modules::ModuleCamera>::Instance();
	s_observer_command *observer_cmd = (s_observer_command *)state;
	unsigned long unit_index = ((unsigned long (*)(long))0x589CC0)(0);
	bool in_vehicle = false;
	if (unit_index != -1)
	{
		s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 1);
		if (unit)
		{
			if (unit_in_vehicle(unit_index))
				in_vehicle = true;
			unsigned long weapon_index = ((unsigned long (*)(long, short))0xB454D0)(unit_index, unit->current_weapon_set.indices[0]);
			observer_cmd->zoom_change_time = ((float (*)(unsigned long))0xB62B80)(weapon_index);
			observer_cmd->zoom_flags = 1;
		}
	}
	c_following_camera__update(thisptr, localPlayerIndex, a4, state);
	s_camera_definition &definition = *(s_camera_definition *)(state + 4);
	Modules::Command *camera_type = moduleCamera.VarCameraFov;
	if (in_vehicle)
		camera_type = moduleCamera.VarVehicleCameraFov;
	definition.FieldOfView = definition.FieldOfView / camera_type->DefaultValueFloat * camera_type->ValueFloat;
	unsigned __int32 targetObjectIndex = *(unsigned long *)((char *)thisptr + 4);
	if (targetObjectIndex == -1)
		return;
	s_object_data *targetObject = object_get(targetObjectIndex);
	if (!targetObject)
		return;
	float s = pow(targetObject->scale, 1.0f);
	definition.Depth *= s;
	definition.PositionShift *= s;
	if (moduleCamera.VarCameraFocusDistance->ValueFloat != 0.0f)
		definition.Depth = moduleCamera.VarCameraFocusDistance->ValueFloat;
}

__int32 unit_use_third_person_camera(unsigned long object_index, __int32 *a2) // 0x1095EE20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_use_third_person_camera@@YAHKPAH@Z");
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
		// __int32 v16;
		// s_unit_data *parent;
			// s_unit_definition *unit_definition;
			// c_flags<enum e_unit_seat_flags,long> seat_flags;
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

	static __int32 (*const weapon_uses_third_person_camera)(short) = (__int32 (*)(short))0xB69A20;
	static __int32 (*const sub_B444F0)(unsigned long) = (__int32 (*)(unsigned long))0xB444F0;
	static bool (*const secondary_skull_is_active)(unsigned long) = (bool (*)(unsigned long))0x60AE50;
	static bool (*const sub_B40B80)(short) = (bool (*)(short))0xB40B80;
	static __int32 (*const sub_B8F910)(short) = (__int32 (*)(short))0xB8F910;
	static bool (*const sub_BA67F0)(short) = (bool (*)(short))0xBA67F0;
	*a2 = 0;
	__int32 result = 0;
	if (object_index == -1)
		return 0;
	s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(object_index, 0x2003);
	if (unit->parent_object_index != -1)
	{
		s_unit_data *parent = (s_unit_data *)object_try_and_get_and_verify_type(unit->parent_object_index, 0x2003);
		__int32 v16 = sub_B8F910((short)object_index);
		*a2 = 2;
		if (unit->seat_index != -1)
		{
			s_unit_definition *unit_definition = (s_unit_definition *)tag_get('unit', parent->definition_index);
			c_flags<enum e_unit_seat_flags,long> seat_flags = unit_definition->seats[unit->seat_index].flags;
			if (seat_flags & 0x10)
				result = 1;
			if (seat_flags & 0x40)
			{
				if (sub_BA67F0((short)object_index))
					*a2 = 1;
				else if (v16 == 0x55 || v16 == 0x4BE)
					*a2 = 3;
			}
		}
	}
	else
	{
		if (sub_B444F0(object_index))
			result = 1;
	}
	unsigned long weapon_index = ((unsigned long (*)(unsigned long, short))0xB454D0)(object_index, unit->current_weapon_set.indices[0]);
	if (weapon_index != -1 && (weapon_uses_third_person_camera((short)weapon_index) || secondary_skull_is_active(5)))
		*a2 = 4;
	if (Player::CPlayerEmotes::UnitRequiresThirdPersonCamera(object_index))
		*a2 = 4;
	if (sub_B40B80((short)object_index) || *a2 == 1 || *a2 == 3 || *a2 == 4)
		result = 1;
	if (Patches::Camera::GetForcedCameraMode() == _camera_mode_first_person)
		return 0;
	else if (Patches::Camera::GetForcedCameraMode() == 0)
		return 1;
	return result;
}

bool director_scripting_get_hook() // 0x1095B0B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?director_scripting_get_hook@@YA_NXZ");
	// `anonymous-namespace'::director_scripting_get_hook
	// procedure flags: nofpo
	// constexpr bool (*const `director_scripting_get_hook'::`2'::director_scripting_get)(); // constant == 5839744
	// function call : bool (*const)()

	if (Patches::Camera::GetForcedCameraMode() == _camera_mode_flying)
		return true;
	return ((bool(__cdecl *)())0x591b80)();
}

bool __fastcall c_director__set_camera_mode_internal_hook(void *thisPtr, void *unused, __int32 camera_mode, float camera_speed, bool a4) // 0x10959450
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_director__set_camera_mode_internal_hook@@YI_NPAX0HM_N@Z");
	// `anonymous-namespace'::c_director__set_camera_mode_internal_hook
	// bool a4;
	// constexpr bool (*const `c_director__set_camera_mode_internal_hook'::`2'::c_director__set_camera_mode_internal)(void *, __int32, float, bool); // constant == 5845520
	// function call : bool (*const)(void *, __int32, float, bool)

	if (Patches::Camera::GetForcedCameraMode() == _camera_mode_flying || Patches::Camera::GetForcedCameraMode() == _camera_mode_static)
		return false;
	return ((bool(__thiscall *const)(void *, __int32, float, bool))0x593210)(thisPtr, camera_mode, camera_speed, a4);
}

__int32 scripted_camera__player_mapping_get_input_controller_hook(short a1) // 0x1095D2A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?scripted_camera__player_mapping_get_input_controller_hook@@YAHF@Z");
	// `anonymous-namespace'::scripted_camera__player_mapping_get_input_controller_hook
	// short a1;
	// constexpr __int32 (*const `scripted_camera__player_mapping_get_input_controller_hook'::`2'::player_mapping_get_input_controller)(short); // constant == 5806800
	// bool controllerEnabled;
	// function call : __int32 (*const)(short)

	bool controllerEnabled = Pointer::Base(0x204DE98).Read<bool>();

	if (!controllerEnabled)
		return -1;

	return ((__int32 (*)(short))0x589ad0)(a1);
}

void debug_teleport_to_camera() // 0x1095A660
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?debug_teleport_to_camera@@YAXXZ");
	// `anonymous-namespace'::debug_teleport_to_camera
	// procedure flags: nofpo
	// Modules::ModuleDebug &debugModule;
		// unsigned long unit_index;
		// s_observer_result *camera;
			// void (*const hs_object_orient)(long, real_point3d const *, real_vector3d const *, real_vector3d const *, bool, bool);
	// function call : s_observer_result *(*const)(long)
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, real_point3d const *, real_vector3d const *, real_vector3d const *, bool, bool)

	auto &debugModule = Utils::Singleton<Modules::ModuleDebug>::Instance();

	if (debugModule.teleportToCamera)
	{
		debugModule.teleportToCamera = false;

		s_observer_result *camera = ((s_observer_result *(*)(long))0x613960)(0);
		unsigned long unit_index = ((unsigned long (*)(long))0x589CC0)(0);

		if (camera && unit_index != NONE)
		{
			const auto hs_object_orient = (void(*)(long, real_point3d const *, real_vector3d const *, real_vector3d const *, bool, bool))0x96E320;

			hs_object_orient(unit_index, &camera->position, &camera->forward, &camera->up, true, true);
		}
	}
}

void director_game_tick_hook() // 0x1095A810
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?director_game_tick_hook@@YAXXZ");
	// `anonymous-namespace'::director_game_tick_hook
	// procedure flags: nofpo
	// static float `director_game_tick_hook'::`2'::previousVert; // 0x1240F668
	// static float `director_game_tick_hook'::`2'::previousHoriz; // 0x1240F664
	// constexpr void (*const `director_game_tick_hook'::`2'::scripted_camera_game_tick)(); // constant == 7521840
	// bool controllerEnabled;
		// float scripted_camera_horiz;
		// s_scripted_camera_globals *scripted_camera_globals;
		// float scripted_camera_vert;
		// float current_vert;
		// s_player_control_input_state *player_control;
		// float current_horiz;
	// function call : void (*const)()

	static float previousVert;
	static float previousHoriz;
	bool controllerEnabled = Pointer::Base(0x204DE98, 1).Read<bool>();
	if (!controllerEnabled)
	{
		s_scripted_camera_globals *scripted_camera_globals = tls_getd().scripted_camera_globals;
		s_player_control_input_state *player_control = player_control_input_get(0);
		float current_horiz = player_control->state.desired_angles.yaw;
		float current_vert = player_control->state.desired_angles.pitch;
		float scripted_camera_horiz = scripted_camera_globals->horizontal_view_offset;
		float scripted_camera_vert = scripted_camera_globals->vertical_view_offset;
		scripted_camera_horiz += current_horiz - previousHoriz;
		scripted_camera_vert += current_vert - previousVert;
		if (scripted_camera_horiz <= 1.0f && scripted_camera_horiz >= -1.0f)
			scripted_camera_globals->horizontal_view_offset = scripted_camera_horiz;
		if (scripted_camera_vert <= 1.0f && scripted_camera_vert >= -1.0f)
			scripted_camera_globals->vertical_view_offset = scripted_camera_vert;
		previousHoriz = current_horiz;
		previousVert = current_vert;
	}
	((void (*)())0x72C630)();
	debug_teleport_to_camera();
}

void director_render_hook() // 0x1095ACD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?director_render_hook@@YAXXZ");
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

	static void (*const interface_get_current_display_settings)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *) = reinterpret_cast<void (*)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *)>(0xA9FAA0);
	if (!Utils::Singleton<Modules::ModuleCamera>::Instance().VarCameraShowCoordinates->ValueInt)
		return;
	long output_user_index = ((long (*)())0x589A30)();
	s_observer_result *camera = ((s_observer_result *(*)(long))0x613960)(output_user_index);
	if (!camera)
		return;
	real_euler_angles3d angles;
	euler_angles3d_from_vectors3d(&angles, &camera->forward, &camera->up);
	float const k_to_degrees = 57.295776f;
	float const pitch_deg = angles.pitch * k_to_degrees;
	float const yaw_deg = angles.yaw * k_to_degrees;
	float const roll_deg = angles.roll * k_to_degrees;
	char buff[4096];
	sprintf_s(buff, "%.4f %.4f %.4f / %.4f %.4f %.4f", camera->position.x, camera->position.y, camera->position.z, yaw_deg, pitch_deg, roll_deg);
	short_rectangle2d bounds;
	interface_get_current_display_settings(nullptr, nullptr, nullptr, &bounds);
	c_font_cache_mt_safe font_cache;
	c_rasterizer_draw_string drawstr;
	drawstr.set_font(4);
	drawstr.set_style(-1);
	drawstr.set_justification(0);
	drawstr.set_bounds(bounds);
	bounds.y0 += 80;
	drawstr.set_color({ 1.0f, 1.0f, 1.0f, 1.0f });
	drawstr.draw(&font_cache, buff);
}

void offset_and_scale_position_easing_type_one(real_point3d *position, real_vector3d *offset, float scale) // 0x1095CCF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?offset_and_scale_position_easing_type_one@@YAXPAUreal_point3d@@PAUreal_vector3d@@M@Z");
	// `anonymous-namespace'::offset_and_scale_position_easing_type_one
	// float scale;

	position->x = (position->x - offset->i) * scale + offset->i;
	position->y = (position->y - offset->j) * scale + offset->j;
	position->z = (position->z - offset->k) * scale + offset->k;
}

void offset_and_scale_position_easing_type_two(real_point3d *position, real_vector3d *offset, real_vector3d *offset_2, float scale) // 0x1095CD90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?offset_and_scale_position_easing_type_two@@YAXPAUreal_point3d@@PAUreal_vector3d@@1M@Z");
	// `anonymous-namespace'::offset_and_scale_position_easing_type_two
	// float scale;
	// float offset_d;
	// float stored_pos;

	float stored_pos;
	float offset_d;
	stored_pos = position->x;
	offset_d = offset->i - offset_2->i;
	position->x = (stored_pos - offset_d * 2.0) * scale * scale;
	position->x = position->x * scale + (offset_d * 3.0 - stored_pos * 2.0) * scale * scale;
	position->x += stored_pos * scale;
	position->x += offset_2->i;
	stored_pos = position->y;
	offset_d = offset->j - offset_2->j;
	position->y = (stored_pos - offset_d * 2.0) * scale * scale;
	position->y = position->y * scale + (offset_d * 3.0 - stored_pos * 2.0) * scale * scale;
	position->y += stored_pos * scale;
	position->y += offset_2->j;
	stored_pos = position->z;
	offset_d = offset->k - offset_2->k;
	position->z = (stored_pos - offset_d * 2.0) * scale * scale;
	position->z = position->z * scale + (offset_d * 3.0 - stored_pos * 2.0) * scale * scale;
	position->z += stored_pos * scale;
	position->z += offset_2->k;
}

void lerp_vector(real_vector3d *out_vec, real_vector3d *vec1, real_vector3d *vec2, float s) // 0x1095B720
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?lerp_vector@@YAXPAUreal_vector3d@@00M@Z");
	// `anonymous-namespace'::lerp_vector
	// float s;

	out_vec->i = s * vec2->i + (1.0f - s) * vec1->i;
	out_vec->j = s * vec2->j + (1.0f - s) * vec1->j;
	out_vec->k = s * vec2->k + (1.0f - s) * vec1->k;
}

void lerp_real(float *out_val, float a, float b, float s) // 0x1095B6D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?lerp_real@@YAXPAMMMM@Z");
	// `anonymous-namespace'::lerp_real
	// float s;

	*out_val = s * b + (1.0f - s) * a;
}

void slerp_rotational_vectors(real_vector3d *out_f, real_vector3d *out_up, real_vector3d *a, real_vector3d *a_up, real_vector3d *b, real_vector3d *b_up, float s) // 0x1095E7D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?slerp_rotational_vectors@@YAXPAUreal_vector3d@@00000M@Z");
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

	void (*const matrix4x3_from_point_and_vectors)(real_matrix4x3 *, real_point3d const *, real_vector3d *, real_vector3d *) = reinterpret_cast<void (*)(real_matrix4x3 *, real_point3d const *, real_vector3d *, real_vector3d *)>(0x5B20C0);
	void (*const matrix4x3_rotation_to_quaternion)(real_matrix4x3 *, real_quaternion *) = reinterpret_cast<void (*)(real_matrix4x3 *, real_quaternion *)>(0x5B37D0);
	void (*const quaternions_slerp_interpolate_and_normalize)(real_quaternion *, real_quaternion *, float, real_quaternion *) = reinterpret_cast<void (*)(real_quaternion *, real_quaternion *, float, real_quaternion *)>(0x4FB430);
	void (*const matrix4x3_from_point_and_quaternion)(real_matrix4x3 *, real_point3d const *, real_quaternion *) = reinterpret_cast<void (*)(real_matrix4x3 *, real_point3d const *, real_quaternion *)>(0x5B1F30);
	void (*const matrix4x3_to_point_and_vectors)(real_matrix4x3 *, real_vector3d *, real_vector3d *, real_vector3d *) = reinterpret_cast<void (*)(real_matrix4x3 *, real_vector3d *, real_vector3d *, real_vector3d *)>(0x5B3890);
	real_matrix4x3 rotation_matrix;
	matrix4x3_from_point_and_vectors(&rotation_matrix, &global_origin3d, a, a_up);
	real_quaternion rotation_quat;
	matrix4x3_rotation_to_quaternion(&rotation_matrix, &rotation_quat);
	real_matrix4x3 next_rotation_matrix;
	matrix4x3_from_point_and_vectors(&next_rotation_matrix, &global_origin3d, b, b_up);
	real_quaternion next_rotation_quat;
	matrix4x3_rotation_to_quaternion(&next_rotation_matrix, &next_rotation_quat);
	real_quaternion new_rotation;
	quaternions_slerp_interpolate_and_normalize(&rotation_quat, &next_rotation_quat, s, &new_rotation);
	real_matrix4x3 new_rotation_matrix;
	matrix4x3_from_point_and_quaternion(&new_rotation_matrix, &global_origin3d, &new_rotation);
	real_vector3d out_pos;
	matrix4x3_to_point_and_vectors(&new_rotation_matrix, &out_pos, out_f, out_up);
}

void build_interpolated_camera_frame(s_camera_frame *out_frame, s_camera_frame *a, s_camera_frame *b, float s) // 0x10959160
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?build_interpolated_camera_frame@@YAXPAUs_camera_frame@@00M@Z");
	// `anonymous-namespace'::build_interpolated_camera_frame
	// float s;

	lerp_vector((real_vector3d *)&out_frame->position, (real_vector3d *)&a->position, (real_vector3d *)&b->position, s);
	slerp_rotational_vectors(&out_frame->forward, &out_frame->up, &a->forward, &a->up, &b->forward, &b->up, s);
	lerp_real(&out_frame->unknown_00, a->unknown_00, b->unknown_00, s);
	lerp_real(&out_frame->unknown_01, a->unknown_01, b->unknown_01, s);
	lerp_real(&out_frame->field_of_view, a->field_of_view, b->field_of_view, s);
	lerp_real(&out_frame->near_focal_plane_distance, -a->near_focal_plane_distance, -b->near_focal_plane_distance, s);
	lerp_real(&out_frame->far_focal_plane_distance, -a->far_focal_plane_distance, -b->far_focal_plane_distance, s);
	lerp_real(&out_frame->focal_depth, a->focal_depth, b->focal_depth, s);
	lerp_real(&out_frame->blur_amount, a->blur_amount, b->blur_amount, s);
	out_frame->depth_of_field = s < 0.5f ? a->depth_of_field : b->depth_of_field;
}

void observer_set_camera_frame(s_observer_command *observer_command, real_matrix4x3 *camera_matrix, s_camera_frame *frame) // 0x1095CB60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?observer_set_camera_frame@@YAXPAUs_observer_command@@PAUreal_matrix4x3@@PAUs_camera_frame@@@Z");
	// `anonymous-namespace'::observer_set_camera_frame
	// s_camera_frame *frame;
	// float (*const calculate_field_of_view)(float);
	// function call : float (*const)(float)

	float (*const calculate_field_of_view)(float) = (float (*const)(float))0x72bfe0;

	observer_command->camera.forward = camera_matrix->forward;
	observer_command->camera.up = camera_matrix->up;
	observer_command->camera.position = camera_matrix->position;
	observer_command->smoothing_factor = 0.0f;
	observer_command->camera.focus_distance = 0.0f;
	observer_command->camera.horizontal_field_of_view = calculate_field_of_view(frame->field_of_view);

	if (frame->depth_of_field)
		observer_command->depth_of_field.flags |= 1;
	else
		observer_command->depth_of_field.flags &= ~1;

	observer_command->depth_of_field.focus_distance = frame->near_focal_plane_distance;
	observer_command->depth_of_field.focus_half_width = frame->far_focal_plane_distance;
	observer_command->depth_of_field.near_plane = frame->focal_depth;
	observer_command->depth_of_field.far_plane = frame->blur_amount;
}

void scripted_camera_update_call_hook(void *a1, void *camera_control, s_observer_command *observer_command) // 0x1095D3B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?scripted_camera_update_call_hook@@YAXPAX0PAUs_observer_command@@@Z");
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
		// float fov_time_scale;
		// s_cinematic_scene_definition *const cisc;
			// long scene_shot_index;
			// s_cinematic_scene_shot *const shot;
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
					// float s;
					// s_camera_frame *const next_frame;
					// long ticks_elapsed;
					// float current_frame_time;
						// float unknown_scale;
						// float scaled_frame_time;
						// real_quaternion rotation_quat;
						// real_vector3d out_pos;
						// real_matrix4x3 rotation_matrix;
				// __int32 i;
					// s_cinematic_shot_extra_camera *const extra_camera;
						// long shot_index;
						// s_cinematic_extra_camera_shot *const extra_shot;
							// s_cinematic_extra_camera_frame *const extra_frame;
							// long frame_index;
								// real_matrix4x3 camera_matrix;
								// s_camera_frame *const camera_frame;
		// long output_user_index;
			// real_point3d *observer_position;
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

	void (*const scripted_camera_update)(void *, void *, s_observer_command *) = reinterpret_cast<void (*)(void *, void *, s_observer_command *)>(0x72E170);
	float (*const observer_suggested_field_of_view)() = reinterpret_cast<float (*)()>(0x613730);
	void (*const scripted_camera_get_deterministic_cinematic_camera_matrix)(s_camera_frame const *, real_matrix4x3 *) = reinterpret_cast<void (*)(s_camera_frame const *, real_matrix4x3 *)>(0x72CE60);
	void (*const matrix4x3_rotation_from_axis_and_angle)(real_matrix4x3 *, real_vector3d *, float, float) = reinterpret_cast<void (*)(real_matrix4x3 *, real_vector3d *, float, float)>(0x5B3270);
	void (*const matrix3x3_multiply)(real_matrix3x3 *, real_matrix3x3 *, real_matrix3x3 *) = reinterpret_cast<void (*)(real_matrix3x3 *, real_matrix3x3 *, real_matrix3x3 *)>(0x5B09B0);
	float (*const calculate_field_of_view)(float) = reinterpret_cast<float (*)(float)>(0x72BFE0);
	void (*const matrix4x3_from_point_and_vectors)(real_matrix4x3 *, real_point3d const *, real_vector3d *, real_vector3d *) = reinterpret_cast<void (*)(real_matrix4x3 *, real_point3d const *, real_vector3d *, real_vector3d *)>(0x5B20C0);
	void (*const matrix4x3_rotation_to_quaternion)(real_matrix4x3 *, real_quaternion *) = reinterpret_cast<void (*)(real_matrix4x3 *, real_quaternion *)>(0x5B37D0);
	void (*const quaternions_slerp_interpolate_and_normalize)(real_quaternion *, real_quaternion *, float, real_quaternion *) = reinterpret_cast<void (*)(real_quaternion *, real_quaternion *, float, real_quaternion *)>(0x4FB430);
	void (*const matrix4x3_from_point_and_quaternion)(real_matrix4x3 *, real_point3d const *, real_quaternion *) = reinterpret_cast<void (*)(real_matrix4x3 *, real_point3d const *, real_quaternion *)>(0x5B1F30);
	void (*const matrix4x3_to_point_and_vectors)(real_matrix4x3 *, real_vector3d *, real_vector3d *, real_vector3d *) = reinterpret_cast<void (*)(real_matrix4x3 *, real_vector3d *, real_vector3d *, real_vector3d *)>(0x5B3890);
	void (*const cinematic_camera_update_texture_camera)(s_camera_frame *) = reinterpret_cast<void (*)(s_camera_frame *)>(0x72C260);
	void (*const transform_into_flag_space)(real_matrix4x3 *, long) = reinterpret_cast<void (*)(real_matrix4x3 *, long)>(0x72F0E0);
	long (*const players_first_active_user)() = reinterpret_cast<long (*)()>(0x589A30);
	real_point3d *(*const observer_get_position)(long) = reinterpret_cast<real_point3d *(*)(long)>(0x6127C0);
	void (*const render_texture_camera_off)() = reinterpret_cast<void (*)()>(0xA3AE50);
	void (*const render_texture_camera_on)() = reinterpret_cast<void (*)()>(0xA3AE70);
	void (*const observer_validate_camera_command)(s_observer_command *) = reinterpret_cast<void (*)(s_observer_command *)>(0x614D60);
	s_scripted_camera_globals *scripted_camera_globals = tls_getd().scripted_camera_globals;
	if (scripted_camera_globals->mode != _scripted_camera_cinematic_flying)
	{
		scripted_camera_update(a1, camera_control, observer_command);
		return;
	}
	observer_command->flags = 0;
	float field_of_view = observer_suggested_field_of_view();
	if (((bool (*const)())0x67D270)() && scripted_camera_globals->destination_field_of_view != 0.0f && scripted_camera_globals->field_of_view_change_duration > scripted_camera_globals->seconds_elapsed)
	{
		float fov_time_scale = scripted_camera_globals->seconds_elapsed / scripted_camera_globals->field_of_view_change_duration;
		if (fov_time_scale <= 0.0f)
			fov_time_scale = 0.0f;
		if (fov_time_scale >= 1.0f)
			fov_time_scale = 1.0f;
		field_of_view = (scripted_camera_globals->destination_field_of_view - scripted_camera_globals->field_of_view) * fov_time_scale;
		field_of_view = field_of_view + scripted_camera_globals->field_of_view;
	}
	observer_command->flags |= 8;
	observer_command->camera.horizontal_field_of_view = field_of_view;
	if (game_time_get_paused())
		observer_command->flags |= 0x80;
	else
		observer_command->flags &= ~0x80;
	bool render_texture_camera_active = false;
	if (scripted_camera_globals->cinematic_scene_tag_index != -1)
	{
		s_cinematic_scene_definition *const cisc = (s_cinematic_scene_definition *)tag_get('cisc', scripted_camera_globals->cinematic_scene_tag_index);
		if (cisc->shots.count > 0)
		{
			{
				long scene_shot_index = cisc->shots.count - 1;
				if (scripted_camera_globals->scene_shot_index < scene_shot_index)
					scene_shot_index = scripted_camera_globals->scene_shot_index;
				s_cinematic_scene_shot *const shot = &cisc->shots[scene_shot_index];
				if (shot->camera_frames.count > 0)
				{
					long scene_frame_index = shot->camera_frames.count - 1;
					if (scripted_camera_globals->scene_frame_index < 0)
						scene_frame_index = 0;
					else if (scripted_camera_globals->scene_frame_index < scene_frame_index)
						scene_frame_index = scripted_camera_globals->scene_frame_index;
					s_camera_frame *const camera_frame = &shot->camera_frames[scene_frame_index];
					real_matrix4x3 camera_matrix;
					long next_frame_index = shot->camera_frames.count - 1;
					if (scene_frame_index + 1 < shot->camera_frames.count)
						next_frame_index = scene_frame_index + 1;
					float tick_scale = game_tick_rate() / 30.0f;
					long interpolated_frames = tick_scale - 1.0f;
					bool interpolate_frame = interpolated_frames > 0 && next_frame_index != -1;
					s_camera_frame interpolated_frame;
					if (interpolate_frame)
					{
						s_camera_frame *const next_frame = &shot->camera_frames[next_frame_index];
						long ticks_elapsed = scripted_camera_globals->pan_navigator.ticks_elapsed;
						float s = (float)(ticks_elapsed % (long)tick_scale) / tick_scale;
						build_interpolated_camera_frame(&interpolated_frame, camera_frame, next_frame, s);
						scripted_camera_get_deterministic_cinematic_camera_matrix(&interpolated_frame, &camera_matrix);
					}
					else
					{
						scripted_camera_get_deterministic_cinematic_camera_matrix(camera_frame, &camera_matrix);
					}
					float horizontal_axis = sin(scripted_camera_globals->horizontal_view_offset);
					float horizontal_angle = cos(scripted_camera_globals->horizontal_view_offset);
					real_matrix4x3 rotation;
					matrix4x3_rotation_from_axis_and_angle(&rotation, &camera_matrix.up, horizontal_axis, horizontal_angle);
					matrix3x3_multiply((real_matrix3x3 *)&rotation.forward, (real_matrix3x3 *)&camera_matrix.forward, (real_matrix3x3 *)&camera_matrix.forward);
					float vertical_axis = sin(-scripted_camera_globals->vertical_view_offset);
					float vertical_angle = cos(-scripted_camera_globals->vertical_view_offset);
					matrix4x3_rotation_from_axis_and_angle(&rotation, &camera_matrix.left, vertical_axis, vertical_angle);
					matrix3x3_multiply((real_matrix3x3 *)&rotation.forward, (real_matrix3x3 *)&camera_matrix.forward, (real_matrix3x3 *)&camera_matrix.forward);
					observer_set_camera_frame(observer_command, &camera_matrix, interpolate_frame ? &interpolated_frame : camera_frame);
					if (scripted_camera_globals->pan_navigator.easing_type == 1)
					{
						float current_frame_time = game_seconds_to_ticks_real((float)scripted_camera_globals->frame_index_rounded / 30.0f);
						if (scripted_camera_globals->pan_navigator.end_time > current_frame_time)
						{
							float scaled_frame_time = current_frame_time / scripted_camera_globals->pan_navigator.end_time;
							float unknown_scale = (scripted_camera_globals->field_A8 - 2.0) * scaled_frame_time * scaled_frame_time * scaled_frame_time + (3.0 - scripted_camera_globals->field_A8) * scaled_frame_time * scaled_frame_time;
							offset_and_scale_position_easing_type_one(&observer_command->camera.position, &scripted_camera_globals->position_offset, unknown_scale);
							real_matrix4x3 rotation_matrix;
							matrix4x3_from_point_and_vectors(&rotation_matrix, &global_origin3d, &observer_command->camera.forward, &observer_command->camera.up);
							real_quaternion rotation_quat;
							matrix4x3_rotation_to_quaternion(&rotation_matrix, &rotation_quat);
							quaternions_slerp_interpolate_and_normalize(&scripted_camera_globals->pan_navigator.rotation, &scripted_camera_globals->unknown_rotation, unknown_scale, &rotation_quat);
							matrix4x3_from_point_and_quaternion(&rotation_matrix, &global_origin3d, &rotation_quat);
							real_vector3d out_pos;
							matrix4x3_to_point_and_vectors(&rotation_matrix, &out_pos, &observer_command->camera.forward, &observer_command->camera.up);
						}
					}
					if (scripted_camera_globals->pan_navigator.easing_type == 2)
					{
						float current_frame_time = game_seconds_to_ticks_real((float)scripted_camera_globals->frame_index_rounded / 30.0f);
						if (scripted_camera_globals->pan_navigator.end_time > current_frame_time)
						{
							float scaled_frame_time = current_frame_time / scripted_camera_globals->pan_navigator.end_time;
							offset_and_scale_position_easing_type_two(&observer_command->camera.position, &scripted_camera_globals->position_offset, &scripted_camera_globals->unknown_offset, scaled_frame_time);
							real_quaternion rotation_quat;
							quaternions_slerp_interpolate_and_normalize(&scripted_camera_globals->unknown_rotation, &scripted_camera_globals->pan_navigator.rotation, scaled_frame_time, &rotation_quat);
							real_matrix4x3 rotation_matrix;
							matrix4x3_from_point_and_quaternion(&rotation_matrix, &global_origin3d, &rotation_quat);
							real_vector3d out_pos;
							matrix4x3_to_point_and_vectors(&rotation_matrix, &out_pos, &observer_command->camera.forward, &observer_command->camera.up);
						}
					}
				}
			}
			observer_command->flags |= 0x19;
			observer_command->relative_to_object_index = -1;
			if (cisc->extra_camera_frame_data.count > 0)
			{
				for (__int32 i = 0; i < cisc->extra_camera_frame_data.count; i++)
				{
					s_cinematic_shot_extra_camera *const extra_camera = &cisc->extra_camera_frame_data[i];
					if (extra_camera->shots.count > 0)
					{
						long shot_index = extra_camera->shots.count - 1;
						if (scripted_camera_globals->scene_shot_index < shot_index)
							shot_index = scripted_camera_globals->scene_shot_index;
						s_cinematic_extra_camera_shot *const extra_shot = &extra_camera->shots[shot_index];
						if (extra_shot->camera_frames.count > 0)
						{
							long frame_index = extra_shot->camera_frames.count - 1;
							if (scripted_camera_globals->scene_frame_index < 0)
								frame_index = 0;
							else if (scripted_camera_globals->scene_frame_index < frame_index)
								frame_index = scripted_camera_globals->scene_frame_index;
							s_cinematic_extra_camera_frame *const extra_frame = &extra_shot->camera_frames[frame_index];
							if (extra_camera->type == 990 && extra_frame->flags)
							{
								cinematic_camera_update_texture_camera(&extra_frame->frame_data);
								if (render_texture_camera_active || extra_frame->flags & 1)
									render_texture_camera_active = true;
							}
							if (scripted_camera_globals->extra_camera_shot_name == extra_camera->name)
							{
								s_camera_frame *const camera_frame = &extra_frame->frame_data;
								real_matrix4x3 camera_matrix;
								matrix4x3_from_point_and_vectors(&camera_matrix, &camera_frame->position, &camera_frame->forward, &camera_frame->up);
								transform_into_flag_space(&camera_matrix, scripted_camera_globals->cutscene_flag_index);
								observer_set_camera_frame(observer_command, &camera_matrix, camera_frame);
							}
						}
					}
				}
			}
		}
	}
	if (scripted_camera_globals->pan_navigator.easing_type != 2)
	{
		long output_user_index = players_first_active_user();
		if (output_user_index == -1)
		{
			scripted_camera_globals->field_AC.i = global_up3d.i;
			scripted_camera_globals->field_AC.j = global_up3d.j;
			scripted_camera_globals->field_AC.k = global_up3d.k;
		}
		else
		{
			real_point3d *observer_position = observer_get_position(output_user_index);
			scripted_camera_globals->field_AC.i = observer_position->x - observer_command->camera.position.x;
			scripted_camera_globals->field_AC.j = observer_position->y - observer_command->camera.position.y;
			scripted_camera_globals->field_AC.k = observer_position->z - observer_command->camera.position.z;
			scripted_camera_globals->field_AC.i *= 30.0;
			scripted_camera_globals->field_AC.j *= 30.0;
			scripted_camera_globals->field_AC.k *= 30.0;
		}
	}
	if (render_texture_camera_active != scripted_camera_globals->render_texture_camera_active)
	{
		if (render_texture_camera_active)
			render_texture_camera_on();
		else
			render_texture_camera_off();
	}
	scripted_camera_globals->update = false;
	observer_command->flags |= 0x800;
	observer_command->zoom_flags = 3;
	observer_command->zoom_change_time = 0.0f;
	observer_validate_camera_command(observer_command);
}

void __fastcall c_flying_camera__update_hook(c_flying_camera *thisptr, void *__formal, long user_index, float dt, s_observer_command *result) // 0x109594F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_flying_camera__update_hook@@YIXPAUc_flying_camera@@PAXJMPAUs_observer_command@@@Z");
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
		// real_euler_angles2d vel;
	// function call : unsigned long (*const)(long)

	float k_camera_pitch_threshold = 1.4922565f;
	long player_index = ((unsigned long (*const)(long))0x589C60)(0);
	if (player_index == -1)
		return;
	long controller_index = player_get(player_index)->machine_controller_index;
	if (controller_index < 0 || controller_index > 3)
		return;
	Blam::Input::PlayerInputState *state = Blam::Input::GetPlayerInputState(controller_index);
	float lb = state->Actions[Blam::Input::eGameActionUiLeftBumper].Pressure;
	float rb = state->Actions[Blam::Input::eGameActionUiRightBumper].Pressure;
	float boost = state->Actions[Blam::Input::eGameActionVehicleBoost].Pressure;
	float vertSpeed = Modules::ModuleCamera::Instance().VarCameraVertSpeed->ValueFloat;
	float moveSpeed = Modules::ModuleCamera::Instance().VarCameraSpeed->ValueFloat;
	float boostPow = powf(2.5f, boost);
	moveSpeed *= boostPow;
	vertSpeed *= boostPow;
	bool controllerEnabled = Pointer::Base(0x204DE98).Read<bool>();
	if (controllerEnabled)
	{
		real_euler_angles2d vel;
		Modules::ModuleCamera::Instance().GetInputAngularVelocity(&vel);
		thisptr->angles.yaw += vel.yaw;
		thisptr->angles.pitch += vel.pitch;
	}
	else
	{
		Patches::RawInput::UpdateCameraYawPitch((float)input_globals.mouse.raw_x, (float)input_globals.mouse.raw_y, thisptr->angles.yaw, thisptr->angles.pitch);
	}
	if (thisptr->angles.pitch < -k_camera_pitch_threshold)
		thisptr->angles.pitch = -k_camera_pitch_threshold;
	if (thisptr->angles.pitch > k_camera_pitch_threshold)
		thisptr->angles.pitch = k_camera_pitch_threshold;
	real_vector3d forward;
	real_vector3d left;
	real_vector3d up;
	vector3d_from_euler_angles2d(&forward, &thisptr->angles);
	generate_up_vector3d(&forward, &up);
	cross_product3d(&up, &forward, &left);
	normalize3d(&left);
	thisptr->position = thisptr->position + moveSpeed * dt * (state->Forward * forward + state->Strafe * left);
	thisptr->position.z += (rb - lb) * up.k * vertSpeed * dt;
	result->smoothing_factor = Modules::ModuleCamera::Instance().VarCameraSmoothing->ValueFloat;
	result->camera.position = thisptr->position;
	result->camera.forward = forward;
	result->camera.up = up;
	result->camera.position_shift = { 0.0f, 0.0f, 0.0f };
	result->camera.focus_distance = 0.0f;
	result->camera.horizontal_field_of_view = *((float *)0x18ECE00 + 0) / 180.0f * 3.1415927f;
	result->flags = 1;
}

void player_effect_apply_camera_effect_matrix_hook(long output_user_index, real_matrix4x3 *camera_matrix) // 0x1095D0D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_effect_apply_camera_effect_matrix_hook@@YAXJPAUreal_matrix4x3@@@Z");
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
		// real_matrix4x3 shake_matrix;
	// function call : void (*const)(long, real_matrix4x3 *)
	// function call : void (*const)(float, float, real_matrix4x3 *)

	void (*const player_effect_apply_camera_effect_matrix)(long, real_matrix4x3 *) = (void (*const)(long, real_matrix4x3 *))0x683b30;
	void (*const get_shake_matrix)(float, float, real_matrix4x3 *) = (void (*const)(float, float, real_matrix4x3 *))0x683a30;

	player_effect_apply_camera_effect_matrix(output_user_index, camera_matrix);

	float shake_translation = 0.0f;
	float shake_rotation = 0.0f;
	screen_effect_get_camera_shake(output_user_index, &shake_translation, &shake_rotation);

	if (shake_translation > 0.0f || shake_rotation > 0.0f)
	{
		real_matrix4x3 shake_matrix = global_identity4x3;
		get_shake_matrix(shake_translation, shake_rotation, &shake_matrix);
		matrix4x3_multiply(camera_matrix, &shake_matrix, camera_matrix);
	}
}

void observer_compute_result_hook(long output_user_index, s_focus_and_distance *focus_and_distance) // 0x1095B7E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?observer_compute_result_hook@@YAXJPAUs_focus_and_distance@@@Z");
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
		// real_vector3d left;
		// float i;
		// float j;
		// float magnitude;
		// float fov_degrees;
		// float hfov;
	// function call : bool (*const)(real_vector3d const *, real_vector3d const *)
	// function call : void (*const)(s_observer_result *)
	// function call : void (*const)(long, real_point3d const *, float, real_vector3d *)

	void (*const observer_result_compute_parameters)(s_observer_result *) = (void (*)(s_observer_result *))0x6131E0;
	void (*const observer_result_set_position)(long, real_point3d const *, float, real_vector3d *) = (void (*)(long, real_point3d const *, float, real_vector3d *))0x613460;
	bool (*const valid_real_vector3d_axes2)(real_vector3d const *, real_vector3d const *) = (bool (*)(real_vector3d const *, real_vector3d const *))0x4AB450;
	float const g_camera_focus_distance_max = *(float *)0x18BB1F0;
	s_camera_globals const &g_camera_globals = *(s_camera_globals *)0x18ECE00;
	s_observer *observer = observer_get(output_user_index);
	real_vector3d *forward = &observer->values.forward;
	real_vector3d *up = &observer->values.up;
	if (!valid_real_vector3d_axes2(forward, up))
	{
		*forward = global_forward3d;
		*up = global_up3d;
	}
	observer->values.horizontal_field_of_view = fminf(fmaxf(observer->values.horizontal_field_of_view, k_camera_field_of_view_min), k_camera_field_of_view_max);
	float focus_distance = fminf(fmaxf(observer->values.focus_distance, 0.0f), g_camera_focus_distance_max);
	real_point3d focus_position = observer->values.position;
	focus_position.x = fminf(fmaxf(focus_position.x, -50000.0f), 50000.0f);
	focus_position.y = fminf(fmaxf(focus_position.y, -50000.0f), 50000.0f);
	focus_position.z = fminf(fmaxf(focus_position.z, -50000.0f), 50000.0f);
	if (observer->field_F7)
	{
		real_vector3d left;
		cross_product3d(up, forward, &left);
		normalize3d(&left);
		focus_position.x += observer->values.position_shift.i * forward->i;
		focus_position.y += observer->values.position_shift.i * forward->j;
		focus_position.z += observer->values.position_shift.i * forward->k;
		focus_position.x += observer->values.position_shift.j * left.j;
		focus_position.y += observer->values.position_shift.j * left.i;
		focus_position.z += observer->values.position_shift.j * left.k;
		focus_position.x += observer->values.position_shift.k * up->i;
		focus_position.y += observer->values.position_shift.k * up->j;
		focus_position.z += observer->values.position_shift.k * up->k;
	}
	else
	{
		float i;
		float j;
		float magnitude = sqrtf(forward->i * forward->i + forward->j * forward->j);
		if (fabsf(magnitude - 0.0f) < 0.0001f)
		{
			i = forward->i;
			j = forward->j;
		}
		else
		{
			i = forward->i / magnitude;
			j = forward->j / magnitude;
		}
		focus_position.x += observer->values.position_shift.j * j + observer->values.position_shift.i * i;
		focus_position.y += observer->values.position_shift.i * j - observer->values.position_shift.j * i;
		focus_position.z += observer->values.position_shift.k;
	}
	observer->result.forward = *forward;
	observer->result.up = *up;
	observer->result.translational_velocity = -observer->translational_velocity;
	observer->result.angular_velocity = observer->angular_velocity;
	if (!(observer->pending_command->flags & 0x800))
	{
		float fov_degrees = Modules::ModuleCamera::Instance().VarCameraFov->ValueFloat;
		float hfov = fminf(fmaxf(fov_degrees / 180.0f * 3.1415927f, k_camera_field_of_view_min), k_camera_field_of_view_max);
		observer->values.horizontal_field_of_view = hfov;
		observer->result.horizontal_field_of_view = hfov;
		observer->pending_command->camera.horizontal_field_of_view = hfov;
		observer->pending_command->zoom_flags = 0;
	}
	observer->result.horizontal_field_of_view = screen_effect_apply_field_of_view_scale(output_user_index, &focus_position, forward, observer->values.horizontal_field_of_view);
	observer->result.focus_offset = observer->values.focus_offset;
	observer->result.aspect_ratio = 4.0f / 3.0f;
	observer->result.depth_of_field = observer->pending_command->depth_of_field;
	observer_result_compute_parameters(&observer->result);
	if (observer->use_focus_space)
	{
		matrix4x3_transform_point(&observer->focus_space, &focus_position, &focus_position);
		matrix4x3_transform_vector(&observer->focus_space, &observer->result.translational_velocity, &observer->result.translational_velocity);
		matrix4x3_transform_vector(&observer->focus_space, &observer->result.angular_velocity, &observer->result.angular_velocity);
		matrix4x3_transform_vector(&observer->focus_space, forward, forward);
		matrix4x3_transform_vector(&observer->focus_space, up, up);
		observer->result.translational_velocity.i += observer->current_command.velocity.i;
		observer->result.translational_velocity.j += observer->current_command.velocity.j;
		observer->result.translational_velocity.k += observer->current_command.velocity.k;
	}
	focus_and_distance->position = focus_position;
	focus_and_distance->distance = focus_distance;
	observer_result_set_position(output_user_index, &focus_position, focus_distance, &observer->result.forward);
	observer->result_valid = true;
}

void observer_compute_view_offset_matrix_hook(long output_user_index, real_matrix4x3 *view_matrix) // 0x1095C2E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?observer_compute_view_offset_matrix_hook@@YAXJPAUreal_matrix4x3@@@Z");
	// `anonymous-namespace'::observer_compute_view_offset_matrix_hook
	// real_matrix4x3 *view_matrix;
	// float view_offset_scale;
		// float yaw;
		// float half_vfov;
		// s_observer *observer;
		// float aspect;
		// float pitch;

	float view_offset_scale = !Utils::Singleton<Modules::ModuleCamera>::Instance().VarOldViewOffsetScale->ValueInt ? 0.785f : 1.0f;
	if (!Utils::Singleton<Modules::ModuleCamera>::Instance().VarOldViewOffsetScale->ValueInt)
	{
		s_observer *observer = observer_get(output_user_index);
		float aspect = 1.33333337f;
		float half_vfov = atan2f(tanf(0.5f * k_camera_field_of_view_default / aspect), 1.0f);
		float pitch = atanf(tanf(half_vfov * 0.785f) * observer->values.focus_offset.j) / -0.785f;
		float yaw = atanf(0.0f);
		matrix3x3_from_angles((real_matrix3x3 *)&view_matrix->forward, -yaw, pitch, 0.0f);
		view_matrix->position = global_origin3d;
		view_matrix->scale = 1.0f;
	}
	else
	{
		s_observer *observer = observer_get(output_user_index);
		float pitch = atanf(tanf(observer->result.vertical_field_of_view * 0.5f) * observer->values.focus_offset.j);
		float yaw = atanf(0.0f);
		matrix3x3_from_angles((real_matrix3x3 *)&view_matrix->forward, -yaw, -pitch, 0.0f);
		view_matrix->position = global_origin3d;
		view_matrix->scale = 1.0f;
	}
}

void observer_result_compute_parameters_hook(s_observer_result *result) // 0x1095C610
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?observer_result_compute_parameters_hook@@YAXPAUs_observer_result@@@Z");
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

	float view_offset_scale = !Utils::Singleton<Modules::ModuleCamera>::Instance().VarOldViewOffsetScale->ValueInt ? 0.785f : 1.0f;
	float hfov = result->horizontal_field_of_view;
	float vfov = atan2f(tanf(hfov * 0.5f) / result->aspect_ratio, 1.0f) * 2.0f;
	real_vector3d old_forward = result->forward;
	real_matrix3x3 matrix;
	float atan0 = atanf(0.0f);
	matrix3x3_from_axis_and_angle(&matrix, &global_up3d, sinf(atan0), cosf(atan0));
	matrix3x3_transform_vector(&matrix, &result->forward, &result->forward);
	matrix3x3_transform_vector(&matrix, &result->up, &result->up);
	float pitch = atanf(tanf(vfov * 0.5 * view_offset_scale) * result->focus_offset.j) / view_offset_scale;
	real_vector3d right;
	cross_product3d(&result->forward, &result->up, &right);
	matrix3x3_from_axis_and_angle(&matrix, &right, sinf(pitch), cosf(pitch));
	matrix3x3_transform_vector(&matrix, &result->forward, &result->forward);
	matrix3x3_transform_vector(&matrix, &result->up, &result->up);
	float dot_inv = 1.0f / fmaxf(dot_product3d(&result->forward, &old_forward), 0.0001f);
	result->focus_distance = sqrtf((old_forward.j * dot_inv - result->forward.j) * (old_forward.j * dot_inv - result->forward.j) + (old_forward.i * dot_inv - result->forward.i) * (old_forward.i * dot_inv - result->forward.i) + (old_forward.k * dot_inv - result->forward.k) * (old_forward.k * dot_inv - result->forward.k));
	result->vertical_field_of_view = vfov;
	result->fov_scale = result->horizontal_field_of_view / k_camera_field_of_view_default;
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

/* ---------- explicit instantiations */
template bool & Pointer::Read<bool>() const;
