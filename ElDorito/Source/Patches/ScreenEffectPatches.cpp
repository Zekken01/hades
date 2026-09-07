/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/camera/director.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
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
#include "Forge/Geoemetry.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
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

struct real_matrix4x3;
struct real_point3d;
struct real_rectangle2d;
struct real_vector3d;
struct s_area_screen_effect_definition;
struct s_data_array;
struct s_object_data;
struct s_scenario;
struct s_screen_effect_camera_settings;
struct s_screen_effect_datum;
struct s_screen_effect_settings;
struct s_screen_effect_shader_sample_result;
struct s_single_screen_effect_definition;
struct s_tag_reference;

namespace Forge {}
using namespace ::Forge;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace ScreenEffects {}
	using namespace Patches::ScreenEffects;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void screen_effect_sample(real_point3d const *camera_position, real_vector3d const *camera_forward, s_screen_effect_settings *settings, s_screen_effect_shader_sample_result *sample_result, long output_user_index);
extern void screen_effect_sample_camera(long output_user_index, real_point3d const *camera_position, real_vector3d const *camera_forward, s_screen_effect_camera_settings *settings);
extern long screen_effect_new(long definition_index, long attach_object_index, short attach_node_index, real_point3d const *position, real_rectangle2d const *bounds);
extern long screen_effect_new2(long definition_index, long attach_object_index, short attach_node_index, real_point3d const *attach_offset, real_rectangle2d const *bounds, bool unknown1, bool cannot_die);
extern void screen_effect_update(float dt);
extern float screen_effect_apply_field_of_view_scale(long output_user_index, real_point3d *position, real_vector3d *forward, float fov);
extern float screen_effect_get_hud_alpha_scale();
extern void screen_effect_set_hud_alpha_scale(float scale);
extern void screen_effect_get_camera_shake(long output_user_index, float *translational, float *rotational);
namespace Patches
{
	namespace ScreenEffects
	{
		extern void ApplyAll();
	}
}

extern "C" bool render_object_is_third_person(long user_index, long object_index);

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern real_vector3d global_zero3d; // 0x1118E940
	extern real_rectangle2d global_null_rectangle2d; // 0x1118E970
	extern float g_screen_effect_user_camera_shake[4]; // 0x1138E3B4
	extern float &g_screen_effect_hud_alpha_scale; // 0x113523E0
}
/* ---------- public code */

_extern bool _sub_107C1E60(s_single_screen_effect_definition *const, float, long, long);
bool s_single_screen_effect_definition::is_visible(float time_alive_seconds, long attach_object_index, long output_user_index) // 0x107C1E60
{
	mangled_x86(MANGLED_TODO, "?is_visible@s_single_screen_effect_definition@@QAE_NMJJ@Z");
	// long output_user_index;
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long)
	todo("implement");
	bool __result = _sub_107C1E60(this, time_alive_seconds, attach_object_index, output_user_index);
	return __result;
}

_extern float _sub_107C1920(s_single_screen_effect_definition *const, float, float, float, long, long, float *);
float s_single_screen_effect_definition::evaluate_falloff(float distance, float angle, float time_alive, long attach_object_index, long output_user_index, float *out_t) // 0x107C1920
{
	mangled_x86(MANGLED_TODO, "?evaluate_falloff@s_single_screen_effect_definition@@QAEMMMMJJPAM@Z");
	// float *out_t;
	// float t;
	// float falloff;
	{
		// float range;
		// float input;
	}
	// function call : float (*const)(long, unsigned long, long)
	// function call : float (*const)(long, unsigned long, long)
	todo("implement");
	float __result = _sub_107C1920(this, distance, angle, time_alive, attach_object_index, output_user_index, out_t);
	return __result;
}

_extern void _sub_107C3A70(s_screen_effect_settings *const);
void s_screen_effect_settings::set_defaults() // 0x107C3A70
{
	mangled_x86(MANGLED_TODO, "?set_defaults@s_screen_effect_settings@@QAEXXZ");
	// s_screen_effect_settings *const this;
	todo("implement");
	_sub_107C3A70(this);
}

_extern void _sub_107C10F0(s_screen_effect_settings *const, s_screen_effect_settings const *, real_vector3d const *, float);
void s_screen_effect_settings::accumulate_settings(s_screen_effect_settings const *settings, real_vector3d const *camera_to_effect, float falloff) // 0x107C10F0
{
	mangled_x86(MANGLED_TODO, "?accumulate_settings@s_screen_effect_settings@@QAEXPBU1@PBUreal_vector3d@@M@Z");
	// s_screen_effect_settings *const this;
	// s_screen_effect_settings const *settings;
	// real_vector3d const *camera_to_effect;
	// float falloff;
	// real_vector3d normalized_camera_to_effect;
	// float const suck;
	todo("implement");
	_sub_107C10F0(this, settings, camera_to_effect, falloff);
}

_extern bool _sub_107C3E00(s_screen_effect_datum *const);
bool s_screen_effect_datum::update_position() // 0x107C3E00
{
	mangled_x86(MANGLED_TODO, "?update_position@s_screen_effect_datum@@QAE_NXZ");
	// s_screen_effect_datum *const this;
	// s_object_data const *attach_object;
	// real_matrix4x3 const *matrix;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : real_matrix4x3 *(*const)(long, short)
	todo("implement");
	bool __result = _sub_107C3E00(this);
	return __result;
}

_extern void _sub_107C1890(s_screen_effect_shader_sample_result *const, s_tag_reference const *, float, float, long, real_rectangle2d const *);
void s_screen_effect_shader_sample_result::accumulate_settings(s_tag_reference const *shader, float falloff, float t, long attach_object_index, real_rectangle2d const *bounds) // 0x107C1890
{
	mangled_x86(MANGLED_TODO, "?accumulate_settings@s_screen_effect_shader_sample_result@@QAEXPBUs_tag_reference@@MMJPBUreal_rectangle2d@@@Z");
	// real_rectangle2d const *bounds;
	// void (*const accumulate_settings)(s_screen_effect_shader_sample_result *, s_tag_reference const *, float, float, long, real_rectangle2d const *);
	// function call : void (*const)(s_screen_effect_shader_sample_result *, s_tag_reference const *, float, float, long, real_rectangle2d const *)
	todo("implement");
	_sub_107C1890(this, shader, falloff, t, attach_object_index, bounds);
}

_extern void _sub_107C2A80(real_point3d const *, real_vector3d const *, s_screen_effect_settings *, s_screen_effect_shader_sample_result *, long);
void screen_effect_sample(real_point3d const *camera_position, real_vector3d const *camera_forward, s_screen_effect_settings *settings, s_screen_effect_shader_sample_result *sample_result, long output_user_index) // 0x107C2A80
{
	mangled_x86(MANGLED_TODO, "?screen_effect_sample@@YAXPBUreal_point3d@@PBUreal_vector3d@@PAUs_screen_effect_settings@@PAUs_screen_effect_shader_sample_result@@J@Z");
	// static ...; // 0x107C2F6C
	// real_point3d const *camera_position;
	// real_vector3d const *camera_forward;
	// s_screen_effect_settings *settings;
	// s_screen_effect_shader_sample_result *sample_result;
	// long output_user_index;
	// c_data_array<s_screen_effect_datum> *const screen_effects;
	// s_scenario const *scenario;
	{
		// s_area_screen_effect_definition *const definition;
		{
			// long i;
			{
				// s_single_screen_effect_definition *screen_effect;
			}
		}
	}
	{
		// c_data_iterator<s_screen_effect_datum> it;
		{
			// s_screen_effect_datum const *datum;
			// real_vector3d camera_to_effect;
			// long attach_object_index;
			// float const angle;
			// float const distance;
			// s_area_screen_effect_definition *sefc;
			{
				// long i;
				{
					// s_single_screen_effect_definition *screen_effect;
					{
						// float t;
						// float falloff;
					}
				}
			}
		}
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : bool (*const)()
	todo("implement");
	_sub_107C2A80(camera_position, camera_forward, settings, sample_result, output_user_index);
}

_extern void _sub_107C3100(long, real_point3d const *, real_vector3d const *, s_screen_effect_camera_settings *);
void screen_effect_sample_camera(long output_user_index, real_point3d const *camera_position, real_vector3d const *camera_forward, s_screen_effect_camera_settings *settings) // 0x107C3100
{
	mangled_x86(MANGLED_TODO, "?screen_effect_sample_camera@@YAXJPBUreal_point3d@@PBUreal_vector3d@@PAUs_screen_effect_camera_settings@@@Z");
	// static ...; // 0x107C3664
	// static ...; // 0x107C365C
	// long output_user_index;
	// real_point3d const *camera_position;
	// real_vector3d const *camera_forward;
	// s_screen_effect_camera_settings *settings;
	// c_data_array<s_screen_effect_datum> *const screen_effects;
	// s_scenario const *scenario;
	{
		// s_area_screen_effect_definition *const definition;
		{
			// long i;
			{
				// s_single_screen_effect_definition *screen_effect;
			}
		}
	}
	{
		// c_data_iterator<s_screen_effect_datum> it;
		{
			// s_screen_effect_datum const *datum;
			// real_vector3d camera_to_effect;
			// long attach_object_index;
			// float const angle;
			// float const distance;
			// s_area_screen_effect_definition *sefc;
			{
				// long i;
				{
					// s_single_screen_effect_definition *screen_effect;
					{
						// float t;
						// float falloff;
					}
				}
			}
		}
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : bool (*const)()
	todo("implement");
	_sub_107C3100(output_user_index, camera_position, camera_forward, settings);
}

_extern long _sub_107C26B0(long, long, short, real_point3d const *, real_rectangle2d const *);
long screen_effect_new(long definition_index, long attach_object_index, short attach_node_index, real_point3d const *position, real_rectangle2d const *bounds) // 0x107C26B0
{
	mangled_x86(MANGLED_TODO, "?screen_effect_new@@YAJJJFPBUreal_point3d@@PBUreal_rectangle2d@@@Z");
	// long attach_object_index;
	// short attach_node_index;
	// real_point3d const *position;
	// real_rectangle2d const *bounds;
	// s_screen_effect_datum *datum;
	// long datum_index;
	// s_area_screen_effect_definition *const definition;
	{
		// c_data_array<s_screen_effect_datum> *screen_effects;
		{
			// c_data_iterator<s_screen_effect_datum> it;
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : unsigned long (*const)(s_data_array *)
	todo("implement");
	long __result = _sub_107C26B0(definition_index, attach_object_index, attach_node_index, position, bounds);
	return __result;
}

_extern long _sub_107C25B0(long, long, short, real_point3d const *, real_rectangle2d const *, bool, bool);
long screen_effect_new2(long definition_index, long attach_object_index, short attach_node_index, real_point3d const *attach_offset, real_rectangle2d const *bounds, bool unknown1, bool cannot_die) // 0x107C25B0
{
	mangled_x86(MANGLED_TODO, "?screen_effect_new2@@YAJJJFPBUreal_point3d@@PBUreal_rectangle2d@@_N2@Z");
	// bool cannot_die;
	// s_screen_effect_datum *datum;
	// long datum_index;
	todo("implement");
	long __result = _sub_107C25B0(definition_index, attach_object_index, attach_node_index, attach_offset, bounds, unknown1, cannot_die);
	return __result;
}

_extern void _sub_107C3840(float);
void screen_effect_update(float dt) // 0x107C3840
{
	mangled_x86(MANGLED_TODO, "?screen_effect_update@@YAXM@Z");
	// static ...; // 0x107C39F4
	// static ...; // 0x107C39E8
	// static ...; // 0x107C39E0
	// float dt;
	// c_data_array<s_screen_effect_datum> *screen_effects;
	{
		// c_data_iterator<s_screen_effect_datum> it;
		{
			// s_screen_effect_datum *datum;
			// bool is_alive;
			// s_area_screen_effect_definition *sefc;
			{
				// long j;
				{
					// s_single_screen_effect_definition *effect;
				}
			}
		}
	}
	// function call : void (*const)(long)
	todo("implement");
	_sub_107C3840(dt);
}

_extern float _sub_107C2200(long, real_point3d *, real_vector3d *, float);
float screen_effect_apply_field_of_view_scale(long output_user_index, real_point3d *position, real_vector3d *forward, float fov) // 0x107C2200
{
	mangled_x86(MANGLED_TODO, "?screen_effect_apply_field_of_view_scale@@YAMJPAUreal_point3d@@PAUreal_vector3d@@M@Z");
	// long output_user_index;
	// real_point3d *position;
	// real_vector3d *forward;
	// float fov;
	// float const k_max_fov;
	// s_screen_effect_camera_settings camera_settings;
	// float const length;
	// float const k_min_fov;
	{
		// float hfov;
	}
	todo("implement");
	float __result = _sub_107C2200(output_user_index, position, forward, fov);
	return __result;
}

_extern float _sub_107C2590();
float screen_effect_get_hud_alpha_scale() // 0x107C2590
{
	mangled_x86(MANGLED_TODO, "?screen_effect_get_hud_alpha_scale@@YAMXZ");
	// procedure flags: nofpo
	todo("implement");
	float __result = _sub_107C2590();
	return __result;
}

_extern void _sub_107C3810(float);
void screen_effect_set_hud_alpha_scale(float scale) // 0x107C3810
{
	mangled_x86(MANGLED_TODO, "?screen_effect_set_hud_alpha_scale@@YAXM@Z");
	// float scale;
	todo("implement");
	_sub_107C3810(scale);
}

_extern void _sub_107C2520(long, float *, float *);
void screen_effect_get_camera_shake(long output_user_index, float *translational, float *rotational) // 0x107C2520
{
	mangled_x86(MANGLED_TODO, "?screen_effect_get_camera_shake@@YAXJPAM0@Z");
	// float *rotational;
	todo("implement");
	_sub_107C2520(output_user_index, translational, rotational);
}

namespace Patches
{
	namespace ScreenEffects
	{
		_extern void _sub_107C0EB0();
		void ApplyAll() // 0x107C0EB0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@ScreenEffects@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_107C0EB0();
		}
	}
}

/* ---------- private code */

_extern bool _sub_107C20E0(long, long);
extern "C" bool render_object_is_third_person(long user_index, long object_index) // 0x107C20E0
{
	// render_object_is_third_person
	// long object_index;
	{
		// s_object_data const *object;
	}
	// function call : e_director_perspective (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : unsigned long (*const)(long)
	todo("implement");
	bool __result = _sub_107C20E0(user_index, object_index);
	return __result;
}
