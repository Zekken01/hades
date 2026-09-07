#ifndef __BLAM_EFFECTS_PARTICLE_EMITTER_DEFINITIONS_HPP__
#define __BLAM_EFFECTS_PARTICLE_EMITTER_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/particle_states.hpp"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class c_particle_state_list;
struct c_editable_property;
struct real_euler_angles3d;
struct real_point3d;
struct real_vector3d;
struct s_particle_emitter_custom_points;
struct s_particle_emitter_movement_data;
struct s_particle_emitter_movement_data_movement;
struct s_particle_emitter_particle_movement_data_movement_parameter;
struct s_particle_emitter_relative_direction_property;
struct s_particle_emitter_runtime_m_gpu_data;
struct s_particle_emitter_runtime_m_gpu_data_color;
struct s_particle_emitter_runtime_m_gpu_data_function;
struct s_particle_emitter_runtime_m_gpu_data_property;
struct s_particle_emitter_self_acceleration_property;
struct s_particle_emitter_translational_offset_property;
struct s_particle_system_emitter;
struct s_tag_data;
struct s_tag_reference;

/* ---------- constants */

enum e_particle_emitter_emission_shape
{
	_emission_shape_sprayer = 0,
	_emission_shape_disc,
	_emission_shape_globe,
	_emission_shape_implode,
	_emission_shape_tube,
	_emission_shape_halo,
	_emission_shape_impact_contour,
	_emission_shape_impact_area,
	_emission_shape_debris,
	_emission_shape_line,
	_emission_shape_breakable_surface,
	_emission_shape_custom_points,
	_emission_shape_boat_hull_surface,
	_emission_shape_cube,
	_emission_shape_cylinder,
	_emission_shape_unweighted_line,
	_emission_shape_plane,
	_emission_shape_jetwash,
	_emission_shape_planar_orbit,
	_emission_shape_sphere_orbit,
};

enum e_particle_emitter_model_axis
{
	_particle_emitter_model_constant = 0,
	_particle_emitter_model_cone,
	_particle_emitter_model_disc,
	_particle_emitter_model_globe,
};

enum e_particle_emitter_reference_axis
{
	_particle_emitter_reference_axis_x = 0,
	_particle_emitter_reference_axis_y,
	_particle_emitter_reference_axis_z,
};

/* ---------- definitions */

struct c_editable_property
{
	public:
	enum e_output_modifier
	{
		_output_modifier_none = 0,
		_output_modifier_plus,
		_output_modifier_times,
	};
	public:
	c_enum<enum e_particle_states,char> input_variable; // 0x0
	c_enum<enum e_particle_states,char> range_variable; // 0x1
	c_enum<enum e_output_modifier,char> output_modifier; // 0x2
	c_enum<enum e_particle_states,char> output_modifier_input; // 0x3
	s_tag_data function; // 0x4
	float m_constant_value; // 0x18
	char m_flags; // 0x1C
	static float (*state_list_evaluate)(c_editable_property *, c_particle_state_list *);
	c_editable_property(c_editable_property &); /* compiler_generated() */
	c_editable_property(c_editable_property const &); /* compiler_generated() */
	c_editable_property(); /* compiler_generated() */
	c_editable_property &operator=(c_editable_property &); /* compiler_generated() */
	c_editable_property &operator=(c_editable_property const &); /* compiler_generated() */
	unsigned char __pad0[3]; // 0x1D
};
static_assert(sizeof(c_editable_property) == 32, "Invalid c_editable_property size");

struct s_particle_emitter_translational_offset_property :
	public c_editable_property
{
	real_point3d starting_interpolant; // 0x20
	real_point3d ending_interpolant; // 0x2C
	s_particle_emitter_translational_offset_property(s_particle_emitter_translational_offset_property &); /* compiler_generated() */
	s_particle_emitter_translational_offset_property(s_particle_emitter_translational_offset_property const &); /* compiler_generated() */
	s_particle_emitter_translational_offset_property(); /* compiler_generated() */
	s_particle_emitter_translational_offset_property &operator=(s_particle_emitter_translational_offset_property &); /* compiler_generated() */
	s_particle_emitter_translational_offset_property &operator=(s_particle_emitter_translational_offset_property const &); /* compiler_generated() */
};
static_assert(sizeof(s_particle_emitter_translational_offset_property) == 56, "Invalid s_particle_emitter_translational_offset_property size");

struct s_particle_emitter_relative_direction_property :
	public c_editable_property
{
	real_euler_angles3d direction_at0; // 0x20
	real_euler_angles3d direction_at1; // 0x2C
	s_particle_emitter_relative_direction_property(s_particle_emitter_relative_direction_property &); /* compiler_generated() */
	s_particle_emitter_relative_direction_property(s_particle_emitter_relative_direction_property const &); /* compiler_generated() */
	s_particle_emitter_relative_direction_property(); /* compiler_generated() */
	s_particle_emitter_relative_direction_property &operator=(s_particle_emitter_relative_direction_property &); /* compiler_generated() */
	s_particle_emitter_relative_direction_property &operator=(s_particle_emitter_relative_direction_property const &); /* compiler_generated() */
};
static_assert(sizeof(s_particle_emitter_relative_direction_property) == 56, "Invalid s_particle_emitter_relative_direction_property size");

#pragma pack(push, 4)
struct s_particle_emitter_particle_movement_data_movement_parameter
{
	long parameter_id; // 0x0
	c_editable_property property; // 0x4
	s_particle_emitter_particle_movement_data_movement_parameter(s_particle_emitter_particle_movement_data_movement_parameter &); /* compiler_generated() */
	s_particle_emitter_particle_movement_data_movement_parameter(s_particle_emitter_particle_movement_data_movement_parameter const &); /* compiler_generated() */
	s_particle_emitter_particle_movement_data_movement_parameter(); /* compiler_generated() */
	s_particle_emitter_particle_movement_data_movement_parameter &operator=(s_particle_emitter_particle_movement_data_movement_parameter &); /* compiler_generated() */
	s_particle_emitter_particle_movement_data_movement_parameter &operator=(s_particle_emitter_particle_movement_data_movement_parameter const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_particle_emitter_particle_movement_data_movement_parameter) == 36, "Invalid s_particle_emitter_particle_movement_data_movement_parameter size");

struct s_particle_emitter_movement_data_movement
{
	c_enum<enum e_particle_emitter_movement_data_movement_type,short> type; // 0x0
	c_flags<enum e_particle_emitter_movement_data_movement_flags,char> flags; // 0x2
	unsigned char __pad0[1]; // 0x3
	c_tag_block<s_particle_emitter_particle_movement_data_movement_parameter> parameters; // 0x4
	long runtime_m_constant_parameters; // 0x10
	long runtime_m_used_particle_states; // 0x14
	s_particle_emitter_movement_data_movement(s_particle_emitter_movement_data_movement &); /* compiler_generated() */
	s_particle_emitter_movement_data_movement(s_particle_emitter_movement_data_movement const &); /* compiler_generated() */
	s_particle_emitter_movement_data_movement(); /* compiler_generated() */
	s_particle_emitter_movement_data_movement &operator=(s_particle_emitter_movement_data_movement &); /* compiler_generated() */
	s_particle_emitter_movement_data_movement &operator=(s_particle_emitter_movement_data_movement const &); /* compiler_generated() */
};
static_assert(sizeof(s_particle_emitter_movement_data_movement) == 24, "Invalid s_particle_emitter_movement_data_movement size");

struct s_particle_emitter_movement_data
{
	s_tag_reference physics_template; // 0x0
	c_flags<enum e_particle_emitter_movement_data_flags,long> flags; // 0x10
	c_tag_block<s_particle_emitter_movement_data_movement> movements; // 0x14
	s_particle_emitter_movement_data(s_particle_emitter_movement_data &); /* compiler_generated() */
	s_particle_emitter_movement_data(s_particle_emitter_movement_data const &); /* compiler_generated() */
	s_particle_emitter_movement_data(); /* compiler_generated() */
	s_particle_emitter_movement_data &operator=(s_particle_emitter_movement_data &); /* compiler_generated() */
	s_particle_emitter_movement_data &operator=(s_particle_emitter_movement_data const &); /* compiler_generated() */
};
static_assert(sizeof(s_particle_emitter_movement_data) == 32, "Invalid s_particle_emitter_movement_data size");

struct s_particle_emitter_self_acceleration_property :
	public c_editable_property
{
	real_vector3d starting_interpolant; // 0x20
	real_vector3d ending_interpolant; // 0x2C
	s_particle_emitter_self_acceleration_property(s_particle_emitter_self_acceleration_property &); /* compiler_generated() */
	s_particle_emitter_self_acceleration_property(s_particle_emitter_self_acceleration_property const &); /* compiler_generated() */
	s_particle_emitter_self_acceleration_property(); /* compiler_generated() */
	s_particle_emitter_self_acceleration_property &operator=(s_particle_emitter_self_acceleration_property &); /* compiler_generated() */
	s_particle_emitter_self_acceleration_property &operator=(s_particle_emitter_self_acceleration_property const &); /* compiler_generated() */
};
static_assert(sizeof(s_particle_emitter_self_acceleration_property) == 56, "Invalid s_particle_emitter_self_acceleration_property size");

struct s_particle_emitter_runtime_m_gpu_data_property
{
	float data[4]; // 0x0
};
static_assert(sizeof(s_particle_emitter_runtime_m_gpu_data_property) == 16, "Invalid s_particle_emitter_runtime_m_gpu_data_property size");

struct s_particle_emitter_runtime_m_gpu_data_function
{
	float data[16]; // 0x0
};
static_assert(sizeof(s_particle_emitter_runtime_m_gpu_data_function) == 64, "Invalid s_particle_emitter_runtime_m_gpu_data_function size");

struct s_particle_emitter_runtime_m_gpu_data
{
	long constant_per_particle_properties; // 0x0
	long constant_over_time_properties; // 0x4
	long used_particle_states; // 0x8
	c_tag_block<s_particle_emitter_runtime_m_gpu_data_property> properties; // 0xC
	c_tag_block<s_particle_emitter_runtime_m_gpu_data_function> functions; // 0x18
	c_tag_block<s_particle_emitter_runtime_m_gpu_data_color> colors; // 0x24
};
static_assert(sizeof(s_particle_emitter_runtime_m_gpu_data) == 48, "Invalid s_particle_emitter_runtime_m_gpu_data size");

struct s_particle_system_emitter
{
	unsigned long name; // 0x0
	c_enum<enum e_particle_emitter_emission_shape,char> emission_shape; // 0x4
	c_flags<enum e_particle_emitter_flags,char> emitter_flags; // 0x5
	c_enum<enum e_particle_emitter_model_axis,char> model_axis; // 0x6
	c_enum<enum e_particle_emitter_reference_axis,char> reference_axis; // 0x7
	s_tag_reference custom_shape; // 0x8
	float bounding_radius_estimate; // 0x18
	float bound_radius_override; // 0x1C
	float uv_scroll_rate[2]; // 0x20
	s_particle_emitter_translational_offset_property translational_offset; // 0x28
	s_particle_emitter_relative_direction_property relative_direction; // 0x60
	c_editable_property emission_radius; // 0x98
	c_editable_property emission_angle; // 0xB8
	c_editable_property particle_starting_count; // 0xD8
	c_editable_property particle_max_count; // 0xF8
	c_editable_property particle_emission_rate; // 0x118
	c_editable_property particle_emission_per_distance; // 0x138
	c_editable_property particle_lifespan; // 0x158
	s_particle_emitter_movement_data particle_movement; // 0x178
	s_particle_emitter_self_acceleration_property particle_self_acceleration; // 0x198
	c_editable_property particle_velocity; // 0x1D0
	c_editable_property particle_angular_velocity; // 0x1F0
	c_editable_property particle_mass; // 0x210
	c_editable_property particle_drag_coefficient; // 0x230
	c_editable_property particle_size; // 0x250
	c_editable_property particle_tint; // 0x270
	c_editable_property particle_alpha; // 0x290
	c_editable_property particle_alpha_black_point; // 0x2B0
	s_particle_emitter_runtime_m_gpu_data runtime_m_gpu; // 0x2D0
	s_particle_system_emitter(s_particle_system_emitter &); /* compiler_generated() */
	s_particle_system_emitter(s_particle_system_emitter const &); /* compiler_generated() */
	s_particle_system_emitter(); /* compiler_generated() */
	s_particle_system_emitter &operator=(s_particle_system_emitter &); /* compiler_generated() */
	s_particle_system_emitter &operator=(s_particle_system_emitter const &); /* compiler_generated() */
};
static_assert(sizeof(s_particle_system_emitter) == 768, "Invalid s_particle_system_emitter size");

// s_particle_system_definition is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

#pragma pack(push, 4)
struct s_particle_emitter_custom_points
{
	public:
	struct s_point
	{
		short position_x; // 0x0
		short position_y; // 0x2
		short position_z; // 0x4
		char normal_x; // 0x6
		char normal_y; // 0x7
		char normal_z; // 0x8
		char correlation; // 0x9
	};
	static_assert(sizeof(s_point) == 10, "Invalid s_point size");
	public:
	s_tag_reference particle_model; // 0x0
	real_vector3d compression_scale; // 0x10
	real_vector3d compression_offset; // 0x1C
	c_tag_block<s_point> points; // 0x28
	static s_particle_emitter_custom_points *get(long);
	s_point *get_point(long);
	void decompress_point(long, real_point3d &, real_vector3d &);
};
#pragma pack(pop)
static_assert(sizeof(s_particle_emitter_custom_points) == 52, "Invalid s_particle_emitter_custom_points size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_EFFECTS_PARTICLE_EMITTER_DEFINITIONS_HPP__
