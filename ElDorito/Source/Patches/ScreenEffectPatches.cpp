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
#include "Forge/ForgeScreenEffects.hpp"  // hades: added for 0x107C2A80
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

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const game_is_playback = reinterpret_cast<bool (*)()>(0x531D10);
}

extern float normalize3d(real_vector3d *v);  // hades: added for 0x107C10F0
float magnitude3d(real_vector3d const *v);  // hades: added for 0x107C2A80
float angle_between_vectors3d(real_vector3d const *a, real_vector3d const *b);  // hades: added for 0x107C2A80

extern unsigned long (*const datum_new)(s_data_array *);  // hades: added for 0x107C26B0

real_point3d *matrix4x3_transform_point(real_matrix4x3 const *matrix, real_point3d const *point, real_point3d *out_point);  // hades: added for 0x107C3E00

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0x107C20E0

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

namespace hades_file_local
{
	namespace hades_file_local_ScreenEffectPatches { extern real_vector3d global_zero3d; } using namespace hades_file_local_ScreenEffectPatches; // 0x1118E940
	namespace hades_file_local_ScreenEffectPatches { extern real_rectangle2d global_null_rectangle2d; } using namespace hades_file_local_ScreenEffectPatches; // 0x1118E970
	extern float g_screen_effect_user_camera_shake[4]; // 0x1138E3B4
	extern float &g_screen_effect_hud_alpha_scale; // 0x113523E0
}
using namespace hades_file_local;
/* ---------- public code */

bool s_single_screen_effect_definition::is_visible(float time_alive_seconds, long attach_object_index, long output_user_index) // 0x107C1E60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?is_visible@s_single_screen_effect_definition@@QAE_NMJJ@Z");

	if (flags.test(_debug_disable_bit))
		return false;
	if (lifetime > 0.0f && (delay >= time_alive_seconds || time_alive_seconds > delay + lifetime))
		return false;
	if (output_user_index != -1 && (static_cast<unsigned short>(flags) & 0x1C))
	{
		if (attach_object_index == -1 || ((long (*)(long))0x589CC0)(output_user_index) != attach_object_index && flags.test(_only_affects_attached_object_bit))
			return flags.test(_unattached_bit);
		else if (((bool (*)(long, long))0xA45060)(output_user_index, attach_object_index))
			return flags.test(_first_person_only_bit);
		else if (render_object_is_third_person(output_user_index, attach_object_index))
			return flags.test(_third_person_only_bit);
		return flags.test(_unattached_bit);
	}
	return true;
}

float s_single_screen_effect_definition::evaluate_falloff(float distance, float angle, float time_alive, long attach_object_index, long output_user_index, float *out_t) // 0x107C1920
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?evaluate_falloff@s_single_screen_effect_definition@@QAEMMMMJJPAM@Z");

	if (!((unsigned short)flags & 0x21) && distance > maximum_distance)
		return 0.0f;
	float t = time_alive;
	if (lifetime > 0.0001f)
		t = fminf(fmaxf((time_alive - delay) / lifetime, 0.0f), 1.0f);
	*out_t = t;
	float falloff = time_evoluation_function.evaluate_scalar(t, 0.5f);
	if (!flags.test(_disable_cinematic_camera_falloffs_bit))
	{
		falloff *= distance_falloff_function.evaluate_scalar(fminf(fmaxf(distance / maximum_distance, 0.0f), 1.0f), 0.5f);
		falloff *= angle_falloff_function.evaluate_scalar(fminf(fmaxf(angle / 3.1415927f, 0.0f), 1.0f), 0.5f);
	}
	if (attach_object_index != -1)
	{
		float input = t;
		if (object_falloff.input_variable)
			input = ((float (*)(long, unsigned long, long))0xB2E1A0)(attach_object_index, object_falloff.input_variable, -1);
		float range = 1.0f;
		if (object_falloff.range_variable)
			range = ((float (*)(long, unsigned long, long))0xB2E1A0)(attach_object_index, object_falloff.range_variable, -1);
		falloff *= object_falloff.function.evaluate_scalar(fminf(fmaxf(input, 0.0f), 1.0f), range);
	}
	return falloff;
}

void s_screen_effect_settings::set_defaults() // 0x107C3A70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_defaults@s_screen_effect_settings@@QAEXXZ");

	exposure_boost = 0.0f;
	exposure_deboost = 0.0f;
	hue_left = 0.0f;
	hue_right = 0.0f;
	saturation = 0.0f;
	desaturation = 0.0f;
	contrast_enhance = 0.0f;
	gamma_enhance = 0.0f;
	gamma_reduce = 0.0f;
	bright_noise = 0.0f;
	dark_noise = 0.0f;
	color_filter = { 1.0f, 1.0f, 1.0f };
	color_floor = { 0.0f, 0.0f, 0.0f };
	tron = 0.0f;
	motion_suck = 0.0f;
	motion_suck_direction = { 0.0f, 0.0f, 0.0f };
	horizontal_blur = 0.0f;
	vertical_blur = 0.0f;
	vision_mode = 0.0f;
	vision_noise = 0.0f;
	hud_fade = 0.0f;
}

void s_screen_effect_settings::accumulate_settings(s_screen_effect_settings const *settings, real_vector3d const *camera_to_effect, float falloff) // 0x107C10F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?accumulate_settings@s_screen_effect_settings@@QAEXPBU1@PBUreal_vector3d@@M@Z");

	falloff = fminf(fmaxf(falloff, 0.0f), 1.0f);
	exposure_boost = fmaxf(exposure_boost, falloff * settings->exposure_boost);
	exposure_deboost = fmaxf(exposure_deboost, falloff * settings->exposure_deboost);
	hue_left = fmaxf(hue_left, falloff * settings->hue_left);
	hue_right = fmaxf(hue_right, falloff * settings->hue_right);
	saturation = fmaxf(saturation, falloff * settings->saturation);
	desaturation = fmaxf(desaturation, falloff * settings->desaturation);
	contrast_enhance = fmaxf(contrast_enhance, falloff * settings->contrast_enhance);
	gamma_enhance = fmaxf(gamma_enhance, falloff * settings->gamma_enhance);
	gamma_reduce = fmaxf(gamma_reduce, falloff * settings->gamma_reduce);
	bright_noise = fmaxf(bright_noise, falloff * settings->bright_noise);
	dark_noise = fmaxf(dark_noise, falloff * settings->dark_noise);
	color_filter.red = fminf(falloff * settings->color_filter.red + (1.0f - falloff), color_filter.red);
	color_filter.green = fminf(falloff * settings->color_filter.green + (1.0f - falloff), color_filter.green);
	color_filter.blue = fminf(falloff * settings->color_filter.blue + (1.0f - falloff), color_filter.blue);
	color_floor.red = fmaxf(color_floor.red, falloff * settings->color_floor.red);
	color_floor.green = fmaxf(color_floor.green, falloff * settings->color_floor.green);
	color_floor.blue = fmaxf(color_floor.blue, falloff * settings->color_floor.blue);
	tron = fmaxf(tron, falloff * settings->tron);
	horizontal_blur = fmaxf(horizontal_blur, falloff * settings->horizontal_blur);
	vertical_blur = fmaxf(vertical_blur, falloff * settings->vertical_blur);
	vision_mode = fmaxf(vision_mode, falloff * settings->vision_mode);
	vision_noise = fmaxf(vision_noise, falloff * settings->vision_noise);
	hud_fade = fmaxf(hud_fade, falloff * settings->hud_fade);
	real_vector3d normalized_camera_to_effect = *camera_to_effect;
	normalize3d(&normalized_camera_to_effect);
	float const suck = falloff * settings->motion_suck;
	motion_suck_direction = motion_suck_direction + suck * normalized_camera_to_effect;
	motion_suck = fmaxf(motion_suck, suck);
}

bool s_screen_effect_datum::update_position() // 0x107C3E00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update_position@s_screen_effect_datum@@QAE_NXZ");

	if (type != _type_attached)
		return true;
	s_object_data const *attach_object = object_try_and_get_and_verify_type(attach_object_index, -1);
	if (!attach_object)
		return false;
	real_matrix4x3 const *matrix = ((real_matrix4x3 *(*)(long, short))0xB2E450)(attach_object_index, attach_node_index);
	matrix4x3_transform_point(matrix, &attach_relative_position, &position);
	if (!flags.test(_destroyed_with_object_bit) && (attach_object->damage_flags & 4))
		return false;
	return true;
}

void s_screen_effect_shader_sample_result::accumulate_settings(s_tag_reference const *shader, float falloff, float t, long attach_object_index, real_rectangle2d const *bounds) // 0x107C1890
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?accumulate_settings@s_screen_effect_shader_sample_result@@QAEXPBUs_tag_reference@@MMJPBUreal_rectangle2d@@@Z");

	void (__thiscall *const func)(s_screen_effect_shader_sample_result *, s_tag_reference const *, float, float, long, real_rectangle2d const *) = (void(__thiscall *const)(s_screen_effect_shader_sample_result *, s_tag_reference const *, float, float, long, real_rectangle2d const *))0x682a90;

	func(this, shader, falloff, t, attach_object_index, bounds);
}

void screen_effect_sample(real_point3d const *camera_position, real_vector3d const *camera_forward, s_screen_effect_settings *settings, s_screen_effect_shader_sample_result *sample_result, long output_user_index) // 0x107C2A80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?screen_effect_sample@@YAXPBUreal_point3d@@PBUreal_vector3d@@PAUs_screen_effect_settings@@PAUs_screen_effect_shader_sample_result@@J@Z");

	settings->set_defaults();
	sample_result->sample_count = 0;
	s_scenario const *scenario = global_scenario_get();
	if (scenario->default_screen_fx.index != -1)
	{
		s_area_screen_effect_definition *const definition = s_area_screen_effect_definition::get(scenario->default_screen_fx.index);
		if (definition->global_hidden_flags.test(s_area_screen_effect_definition::_hidden_flags_render_thread_bit))
		{
			for (long i = 0; i < definition->screen_effects.count; i++)
			{
				s_single_screen_effect_definition *screen_effect = &definition->screen_effects[i];
				if (screen_effect->flags.test(s_single_screen_effect_definition::_debug_disable_bit))
					continue;
				if (screen_effect->hidden_flags.test(s_single_screen_effect_definition::_render_thread_bit))
				{
					settings->accumulate_settings(&screen_effect->settings, &global_zero3d, 1.0f);
					sample_result->accumulate_settings(&screen_effect->screen_shader, 1.0f, 0.0f, -1, &global_null_rectangle2d);
				}
			}
		}
	}
	c_data_array<s_screen_effect_datum> *const screen_effects = tls_getd().screen_effects;
	for (c_data_iterator<s_screen_effect_datum> it = screen_effects->begin(); it != screen_effects->end(); ++it)
	{
		s_screen_effect_datum const *datum = &*it;
		s_area_screen_effect_definition *sefc = s_area_screen_effect_definition::get(datum->definition_index);
		if (!sefc->global_hidden_flags.test(s_area_screen_effect_definition::_hidden_flags_render_thread_bit))
			continue;
		real_vector3d camera_to_effect = datum->position - *camera_position;
		float const distance = magnitude3d(&camera_to_effect);
		float const angle = angle_between_vectors3d(&camera_to_effect, camera_forward);
		long attach_object_index = -1;
		if (datum->type == s_screen_effect_datum::_type_attached && object_try_and_get_and_verify_type(datum->attach_object_index, -1))
			attach_object_index = datum->attach_object_index;
		for (long i = 0; i < sefc->screen_effects.count; i++)
		{
			s_single_screen_effect_definition *screen_effect = &sefc->screen_effects[i];
			if (screen_effect->hidden_flags.test(s_single_screen_effect_definition::_render_thread_bit) && screen_effect->is_visible(datum->alive_time_in_seconds, attach_object_index, output_user_index) && (!datum->flags.test(s_screen_effect_datum::_unknown1_bit) || !eldorado::game_is_playback()))
			{
				Forge::CForgeScreenEffects::ApplyScreenEffectOverride(output_user_index, it.current_datum_index, screen_effect);
				float t = 0.0f;
				float falloff = screen_effect->evaluate_falloff(distance, angle, datum->alive_time_in_seconds, attach_object_index, output_user_index, &t);
				if (falloff > 0.0f)
				{
					settings->accumulate_settings(&screen_effect->settings, &camera_to_effect, falloff);
					sample_result->accumulate_settings(&screen_effect->screen_shader, falloff, t, attach_object_index, &datum->bounds);
				}
			}
		}
	}
}

void screen_effect_sample_camera(long output_user_index, real_point3d const *camera_position, real_vector3d const *camera_forward, s_screen_effect_camera_settings *settings) // 0x107C3100
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?screen_effect_sample_camera@@YAXJPBUreal_point3d@@PBUreal_vector3d@@PAUs_screen_effect_camera_settings@@@Z");

	settings->fov_in = 0.0f;
	settings->fov_out = 0.0f;
	settings->screen_shake = 0.0f;
	s_scenario const *scenario = global_scenario_get();
	if (scenario->default_screen_fx.index != -1)
	{
		s_area_screen_effect_definition *const definition = s_area_screen_effect_definition::get(scenario->default_screen_fx.index);
		if (definition->global_hidden_flags.test(s_area_screen_effect_definition::_hidden_flags_update_thread_bit))
		{
			for (long i = 0; i < definition->screen_effects.count; i++)
			{
				s_single_screen_effect_definition *screen_effect = &definition->screen_effects[i];
				if (screen_effect->flags.test(s_single_screen_effect_definition::_debug_disable_bit))
					continue;
				if (screen_effect->hidden_flags.test(s_single_screen_effect_definition::_update_thread_bit))
				{
					settings->fov_in = fmaxf(settings->fov_in, screen_effect->fov_in);
					settings->fov_out = fmaxf(settings->fov_out, screen_effect->fov_out);
					settings->screen_shake = fmaxf(settings->screen_shake, screen_effect->screen_shake);
				}
			}
		}
	}
	c_data_array<s_screen_effect_datum> *const screen_effects = tls_getd().screen_effects;
	for (c_data_iterator<s_screen_effect_datum> it = screen_effects->begin(); it != screen_effects->end(); ++it)
	{
		s_screen_effect_datum const *datum = &*it;
		s_area_screen_effect_definition *sefc = s_area_screen_effect_definition::get(datum->definition_index);
		if (!sefc->global_hidden_flags.test(s_area_screen_effect_definition::_hidden_flags_render_thread_bit))
			continue;
		real_vector3d camera_to_effect = datum->position - *camera_position;
		float const distance = magnitude3d(&camera_to_effect);
		float const angle = angle_between_vectors3d(&camera_to_effect, camera_forward);
		long attach_object_index = -1;
		if (datum->type == s_screen_effect_datum::_type_attached && object_try_and_get_and_verify_type(datum->attach_object_index, -1))
			attach_object_index = datum->attach_object_index;
		for (long i = 0; i < sefc->screen_effects.count; i++)
		{
			s_single_screen_effect_definition *screen_effect = &sefc->screen_effects[i];
			if (screen_effect->hidden_flags.test(s_single_screen_effect_definition::_update_thread_bit) && screen_effect->is_visible(datum->alive_time_in_seconds, attach_object_index, output_user_index) && (!datum->flags.test(s_screen_effect_datum::_unknown1_bit) || !eldorado::game_is_playback()))
			{
				float t = 0.0f;
				float falloff = screen_effect->evaluate_falloff(distance, angle, datum->alive_time_in_seconds, attach_object_index, output_user_index, &t);
				if (falloff > 0.0f)
				{
					settings->fov_in = fmaxf(settings->fov_in, falloff * screen_effect->fov_in);
					settings->fov_out = fmaxf(settings->fov_out, falloff * screen_effect->fov_out);
					settings->screen_shake = fmaxf(settings->screen_shake, falloff * screen_effect->screen_shake);
				}
			}
		}
	}
}

long screen_effect_new(long definition_index, long attach_object_index, short attach_node_index, real_point3d const *position, real_rectangle2d const *bounds) // 0x107C26B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?screen_effect_new@@YAJJJFPBUreal_point3d@@PBUreal_rectangle2d@@@Z");

	s_area_screen_effect_definition *const definition = (s_area_screen_effect_definition *)tag_get('sefc', definition_index);
	if (definition->global_flags.test(s_area_screen_effect_definition::_force_max_one_per_object_bit) && attach_object_index != -1)
	{
		c_data_array<s_screen_effect_datum> *screen_effects = tls_getd().screen_effects;
		for (c_data_iterator<s_screen_effect_datum> it = screen_effects->begin(); it != screen_effects->end(); ++it)
		{
			if (it->attach_object_index == attach_object_index && it->type == s_screen_effect_datum::_type_attached && object_try_and_get_and_verify_type(it->attach_object_index, -1))
				return -1;
		}
	}
	long datum_index = datum_new(tls_getd().screen_effects);
	if (datum_index == -1)
		return datum_index;
	s_screen_effect_datum *datum = tls_getd().screen_effects->try_and_get(datum_index);
	datum->definition_index = definition_index;
	if (attach_object_index == -1)
	{
		datum->type = s_screen_effect_datum::_type_unattached;
		datum->position = *position;
	}
	else
	{
		datum->type = s_screen_effect_datum::_type_attached;
		datum->attach_object_index = attach_object_index;
		datum->attach_node_index = attach_node_index;
		datum->attach_relative_position = *position;
		datum->flags = (unsigned char)0;
		if (definition->global_flags.test(s_area_screen_effect_definition::_force_delete_when_attached_to_dead_object_bit))
			datum->flags |= 4;
		datum->update_position();
	}
	datum->alive_time_in_seconds = 0.0f;
	datum->bounds = *bounds;
	return datum_index;
}

long screen_effect_new2(long definition_index, long attach_object_index, short attach_node_index, real_point3d const *attach_offset, real_rectangle2d const *bounds, bool unknown1, bool cannot_die) // 0x107C25B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?screen_effect_new2@@YAJJJFPBUreal_point3d@@PBUreal_rectangle2d@@_N2@Z");

	long datum_index = screen_effect_new(definition_index, attach_object_index, attach_node_index, attach_offset, bounds);
	s_screen_effect_datum *datum = tls_getd().screen_effects->try_and_get(datum_index);
	if (!datum)
		return -1;

	if (unknown1)
		datum->flags |= 2;
	else
		datum->flags &= ~2;

	if (cannot_die)
		datum->flags |= 1;
	else
		datum->flags &= ~1;

	return datum_index;
}

void screen_effect_update(float dt) // 0x107C3840
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?screen_effect_update@@YAXM@Z");

	c_data_array<s_screen_effect_datum> *screen_effects = tls_getd().screen_effects;
	for (c_data_iterator<s_screen_effect_datum> it = screen_effects->begin(); it != screen_effects->end(); ++it)
	{
		s_screen_effect_datum *datum = &*it;
		datum->alive_time_in_seconds += dt;
		bool is_alive = false;
		s_area_screen_effect_definition *sefc = s_area_screen_effect_definition::get(datum->definition_index);
		for (long j = 0; j < sefc->screen_effects.count; j++)
		{
			s_single_screen_effect_definition *effect = &sefc->screen_effects[j];
			if (effect->lifetime <= 0.0f || effect->lifetime + effect->delay >= datum->alive_time_in_seconds)
			{
				is_alive = true;
				break;
			}
		}
		is_alive = is_alive && datum->update_position();
		if (!is_alive && !datum->flags.test(s_screen_effect_datum::_cannot_die_bit))
			((void (*)(long))0x682EC0)(it.current_datum_index);
	}
}

float screen_effect_apply_field_of_view_scale(long output_user_index, real_point3d *position, real_vector3d *forward, float fov) // 0x107C2200
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?screen_effect_apply_field_of_view_scale@@YAMJPAUreal_point3d@@PAUreal_vector3d@@M@Z");

	s_screen_effect_camera_settings camera_settings;
	screen_effect_sample_camera(output_user_index, position, forward, &camera_settings);
	if (output_user_index < 4)
		g_screen_effect_user_camera_shake[output_user_index] = camera_settings.screen_shake;
	float const length = camera_settings.fov_out - camera_settings.fov_in;
	if (fabs(camera_settings.fov_out - camera_settings.fov_in) <= 0.0001f)
		return fov;
	float const k_min_fov = 0.017453292f;
	float const k_max_fov = 2.6179938f;
	if (fov < 1.5707964f)
	{
		return fminf(fmaxf(atanf(powf(2.0f, length) * tanf(fov)), k_min_fov), k_max_fov);
	}
	else
	{
		float hfov = atanf(powf(2.0f, length) * tanf(fov * 0.5f));
		return fminf(fmaxf(hfov + hfov, k_min_fov), k_max_fov);
	}
}

float screen_effect_get_hud_alpha_scale() // 0x107C2590
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?screen_effect_get_hud_alpha_scale@@YAMXZ");

	return g_screen_effect_hud_alpha_scale;
}

void screen_effect_set_hud_alpha_scale(float scale) // 0x107C3810
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?screen_effect_set_hud_alpha_scale@@YAXM@Z");

	g_screen_effect_hud_alpha_scale = scale;
}

void screen_effect_get_camera_shake(long output_user_index, float *translational, float *rotational) // 0x107C2520
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?screen_effect_get_camera_shake@@YAXJPAM0@Z");

	if (output_user_index < 0 || output_user_index >= 4)
	{
		*translational = 0.0f;
		*rotational = 0.0f;
	}
	else
	{
		*translational = g_screen_effect_user_camera_shake[output_user_index];
		*rotational = g_screen_effect_user_camera_shake[output_user_index];
	}
}

namespace Patches
{
	namespace ScreenEffects
	{
		void ApplyAll() // 0x107C0EB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@ScreenEffects@Patches@@YAXXZ");

			Hook(0x2836A0, screen_effect_update).Apply();
			Hook(0x283060, screen_effect_new).Apply();
		}
	}
}

/* ---------- private code */

extern "C" bool render_object_is_third_person(long user_index, long object_index) // 0x107C20E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_render_object_is_third_person");

	static e_director_perspective (*const director_get_perspective)(long) = reinterpret_cast<e_director_perspective (*)(long)>(0x591A40);
	static unsigned long (*const player_get_unit_index)(long) = reinterpret_cast<unsigned long (*)(long)>(0x589CC0);
	if (object_index == -1 || user_index == -1)
		return false;
	if (director_get_perspective(user_index) != _perspective_following)
		return false;
	{
		s_object_data const *object = object_try_and_get_and_verify_type(object_index, 2);
		if (object)
			object_index = object->parent_object_index;
	}
	if (object_index == -1 || object_index != player_get_unit_index(user_index) || object_get_type(object_index) != _object_type_biped)
		return false;
	return true;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_enum<enum s_screen_effect_datum::e_type,char>::operator!=(s_screen_effect_datum::e_type const &) const;
template bool c_enum<enum s_screen_effect_datum::e_type,char>::operator==(s_screen_effect_datum::e_type const &) const;
template bool c_flags<enum s_area_screen_effect_definition::e_global_flags,unsigned short>::test(s_area_screen_effect_definition::e_global_flags) const;
template bool c_flags<enum s_area_screen_effect_definition::e_global_hidden_flags,unsigned short>::test(s_area_screen_effect_definition::e_global_hidden_flags) const;
template bool c_flags<enum s_screen_effect_datum::e_flags,unsigned char>::test(s_screen_effect_datum::e_flags) const;
template bool c_flags<enum s_single_screen_effect_definition::e_flags,unsigned short>::test(s_single_screen_effect_definition::e_flags) const;
template bool c_flags<enum s_single_screen_effect_definition::e_hidden_flags,unsigned short>::test(s_single_screen_effect_definition::e_hidden_flags) const;
template bool c_tag_block<s_single_screen_effect_definition>::try_get_element(__int32, s_single_screen_effect_definition **) const;
template c_enum<enum s_screen_effect_datum::e_type,char> & c_enum<enum s_screen_effect_datum::e_type,char>::operator=(s_screen_effect_datum::e_type const &);
template c_flags<enum s_screen_effect_datum::e_flags,unsigned char> & c_flags<enum s_screen_effect_datum::e_flags,unsigned char>::operator&=(__int32 const);
template c_flags<enum s_screen_effect_datum::e_flags,unsigned char> & c_flags<enum s_screen_effect_datum::e_flags,unsigned char>::operator=(unsigned char const &);
template c_flags<enum s_screen_effect_datum::e_flags,unsigned char> & c_flags<enum s_screen_effect_datum::e_flags,unsigned char>::operator|=(__int32 const);
template c_flags<enum s_single_screen_effect_definition::e_flags,unsigned short>::operator unsigned short() const;
template s_screen_effect_datum & c_data_iterator<s_screen_effect_datum>::operator*();
template s_single_screen_effect_definition & c_tag_block<s_single_screen_effect_definition>::operator[](__int32);
template s_single_screen_effect_definition * c_tag_block<s_single_screen_effect_definition>::get_element(__int32) const;

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { float g_screen_effect_user_camera_shake[4]; }
namespace hades_file_local { float &g_screen_effect_hud_alpha_scale = *reinterpret_cast<float *>(0x18BF528); }
namespace hades_file_local { namespace hades_file_local_ScreenEffectPatches { real_vector3d global_zero3d; } }
namespace hades_file_local { namespace hades_file_local_ScreenEffectPatches { real_rectangle2d global_null_rectangle2d; } }
