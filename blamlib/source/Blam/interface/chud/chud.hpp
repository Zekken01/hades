#ifndef __BLAM_INTERFACE_CHUD_CHUD_HPP__
#define __BLAM_INTERFACE_CHUD_CHUD_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/aim_target.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct c_aim_target_object;
struct c_chud_global_scripting;
struct c_chud_navpoint_manager;
struct c_chud_persistent_global_data;
struct c_chud_point_tracker;
struct c_chud_update_user_data;
struct c_curved_hud_test;
struct real_argb_color;
struct real_point2d;
struct real_rectangle2d;
struct real_vector3d;
struct real_vector4d;
struct s_chud_animation_function;
struct s_chud_bitmap_info;
struct s_chud_bitmap_widget;
struct s_chud_definition;
struct s_chud_draw_widget_data;
struct s_chud_managed_navpoint;
struct s_chud_navpoint;
struct s_chud_render_data;
struct s_chud_shared_persistent_user_data;
struct s_chud_text_widget;
struct s_chud_widget;
struct s_chud_widget_animation;
struct s_chud_widget_collection;
struct s_chud_widget_placement;
struct s_chud_widget_render_parameters;
struct s_tag_block;
struct s_tag_reference;
struct s_widget_geometry_quad_simple;
struct short_rectangle2d;

/* ---------- constants */

enum e_chud_widget_type
{
	_chud_widget_type_unspecial = 0,
	_chud_widget_type_ammo,
	_chud_widget_type_crosshairandScope,
	_chud_widget_type_unit_shield_meter,
	_chud_widget_type_grenades,
	_chud_widget_type_gametype,
	_chud_widget_type_motion_sensor,
	_chud_widget_type_spike_grenade,
	_chud_widget_type_firebomb_grenade,
	_chud_widget_type_compass,
	_chud_widget_type_stamina,
	_chud_widget_type_energy_meter,
	_chud_widget_type_consumable,
	k_chud_widget_type_count,
};

/* ---------- definitions */

#pragma pack(push, 4)
struct s_chud_widget_placement
{
	c_enum<enum e_chud_widget_anchor_type,unsigned short> anchor; // 0x0
	unsigned char __pad0[2]; // 0x2
	real_point2d mirror_offset; // 0x4
	real_point2d offset; // 0xC
	float scale_x; // 0x14
	float scale_y; // 0x18
	s_chud_widget_placement(s_chud_widget_placement &); /* compiler_generated() */
	s_chud_widget_placement(s_chud_widget_placement const &); /* compiler_generated() */
	s_chud_widget_placement(); /* compiler_generated() */
	s_chud_widget_placement &operator=(s_chud_widget_placement &); /* compiler_generated() */
	s_chud_widget_placement &operator=(s_chud_widget_placement const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_chud_widget_placement) == 28, "Invalid s_chud_widget_placement size");

struct s_chud_animation_function
{
	c_flags<enum e_chud_animation_flags,unsigned char> flags; // 0x0
	c_enum<enum e_chud_animation_input_type,unsigned char> input_type; // 0x1
	unsigned char __pad0[2]; // 0x2
	s_tag_reference definition; // 0x4
	s_chud_animation_function(s_chud_animation_function &); /* compiler_generated() */
	s_chud_animation_function(s_chud_animation_function const &); /* compiler_generated() */
	s_chud_animation_function(); /* compiler_generated() */
	s_chud_animation_function &operator=(s_chud_animation_function &); /* compiler_generated() */
	s_chud_animation_function &operator=(s_chud_animation_function const &); /* compiler_generated() */
	unsigned char __pad1[4]; // 0x14
};
static_assert(sizeof(s_chud_animation_function) == 24, "Invalid s_chud_animation_function size");

struct s_chud_widget_animation
{
	s_chud_animation_function initialize; // 0x0
	s_chud_animation_function idle; // 0x18
	s_chud_animation_function special_state; // 0x30
	s_chud_animation_function transition_in; // 0x48
	s_chud_animation_function transition_out; // 0x60
	s_chud_animation_function brief_state; // 0x78
	s_chud_widget_animation(s_chud_widget_animation &); /* compiler_generated() */
	s_chud_widget_animation(s_chud_widget_animation const &); /* compiler_generated() */
	s_chud_widget_animation(); /* compiler_generated() */
	s_chud_widget_animation &operator=(s_chud_widget_animation &); /* compiler_generated() */
	s_chud_widget_animation &operator=(s_chud_widget_animation const &); /* compiler_generated() */
};
static_assert(sizeof(s_chud_widget_animation) == 144, "Invalid s_chud_widget_animation size");

struct s_chud_widget_render_parameters
{
	c_enum<enum e_chud_render_output_type,unsigned short> output_type; // 0x0
	unsigned char __pad0[2]; // 0x2
	c_enum<enum e_chud_render_output_type,unsigned short> input; // 0x4
	c_enum<enum e_chud_render_output_type,unsigned short> range_input; // 0x6
	unsigned long local_colors[4]; // 0x8
	float local_scalars[4]; // 0x18
	c_enum<enum e_chud_render_output_color_value,unsigned short> output_colors[6]; // 0x28
	c_enum<enum e_chud_render_output_scalar_value,unsigned short> output_scalars[6]; // 0x34
	s_chud_widget_render_parameters(s_chud_widget_render_parameters &); /* compiler_generated() */
	s_chud_widget_render_parameters(s_chud_widget_render_parameters const &); /* compiler_generated() */
	s_chud_widget_render_parameters(); /* compiler_generated() */
	s_chud_widget_render_parameters &operator=(s_chud_widget_render_parameters &); /* compiler_generated() */
	s_chud_widget_render_parameters &operator=(s_chud_widget_render_parameters const &); /* compiler_generated() */
	unsigned char __pad1[8]; // 0x40
};
static_assert(sizeof(s_chud_widget_render_parameters) == 72, "Invalid s_chud_widget_render_parameters size");

struct s_chud_widget
{
	unsigned long name; // 0x0
	c_enum<enum e_chud_widget_type,unsigned short> special_hud_type; // 0x4
	unsigned char __pad0[2]; // 0x6
	s_tag_block state_flags; // 0x8
	c_tag_block<s_chud_widget_placement> placement; // 0x14
	c_tag_block<s_chud_widget_animation> animations; // 0x20
	c_tag_block<s_chud_widget_render_parameters> render_parameters; // 0x2C
	s_chud_widget(s_chud_widget &); /* compiler_generated() */
	s_chud_widget(s_chud_widget const &); /* compiler_generated() */
	s_chud_widget(); /* compiler_generated() */
	s_chud_widget &operator=(s_chud_widget &); /* compiler_generated() */
	s_chud_widget &operator=(s_chud_widget const &); /* compiler_generated() */
};
static_assert(sizeof(s_chud_widget) == 56, "Invalid s_chud_widget size");

#pragma pack(push, 4)
struct s_chud_bitmap_widget :
	public s_chud_widget
{
	long widget_index; // 0x38
	c_flags<enum e_chud_widget_bitmap_flags,unsigned long> flags; // 0x3C
	s_tag_reference bitmap; // 0x40
	unsigned char sprite_index; // 0x50
	s_chud_bitmap_widget(s_chud_bitmap_widget &); /* compiler_generated() */
	s_chud_bitmap_widget(s_chud_bitmap_widget const &); /* compiler_generated() */
	s_chud_bitmap_widget(); /* compiler_generated() */
	s_chud_bitmap_widget &operator=(s_chud_bitmap_widget &); /* compiler_generated() */
	s_chud_bitmap_widget &operator=(s_chud_bitmap_widget const &); /* compiler_generated() */
	unsigned char __pad0[3]; // 0x51
};
#pragma pack(pop)
static_assert(sizeof(s_chud_bitmap_widget) == 84, "Invalid s_chud_bitmap_widget size");

struct s_chud_text_widget :
	public s_chud_widget
{
	long widget_index; // 0x38
	unsigned long flags; // 0x3C
	unsigned short font_type; // 0x40
	unsigned char __pad0[2]; // 0x42
	unsigned long value; // 0x44
	s_chud_text_widget(s_chud_text_widget &); /* compiler_generated() */
	s_chud_text_widget(s_chud_text_widget const &); /* compiler_generated() */
	s_chud_text_widget(); /* compiler_generated() */
	s_chud_text_widget &operator=(s_chud_text_widget &); /* compiler_generated() */
	s_chud_text_widget &operator=(s_chud_text_widget const &); /* compiler_generated() */
};
static_assert(sizeof(s_chud_text_widget) == 72, "Invalid s_chud_text_widget size");

struct s_chud_widget_collection :
	public s_chud_widget
{
	s_tag_reference parallax_data; // 0x38
	c_tag_block<s_chud_bitmap_widget> bitmap_widgets; // 0x48
	c_tag_block<s_chud_text_widget> text_widgets; // 0x54
	s_chud_widget_collection(s_chud_widget_collection &); /* compiler_generated() */
	s_chud_widget_collection(s_chud_widget_collection const &); /* compiler_generated() */
	s_chud_widget_collection(); /* compiler_generated() */
	s_chud_widget_collection &operator=(s_chud_widget_collection &); /* compiler_generated() */
	s_chud_widget_collection &operator=(s_chud_widget_collection const &); /* compiler_generated() */
};
static_assert(sizeof(s_chud_widget_collection) == 96, "Invalid s_chud_widget_collection size");

struct s_chud_definition
{
	c_tag_block<s_chud_widget_collection> widgets; // 0x0
	long low_clip_cutoff; // 0xC
	long low_ammo_cutoff; // 0x10
	long age_cutoff; // 0x14
};
static_assert(sizeof(s_chud_definition) == 24, "Invalid s_chud_definition size");

struct c_curved_hud_test
{
	real_vector3d basis0; // 0x0
	__int32 field_C; // 0xC
	real_vector3d basis1; // 0x10
	__int32 field_1C; // 0x1C
	real_vector3d basis2; // 0x20
	__int32 field_2C; // 0x2C
	real_vector3d basis3; // 0x30
	__int32 field_3C; // 0x3C
	__int32 field_40; // 0x40
	__int32 field_44; // 0x44
	__int32 screen_offset_x; // 0x48
	__int32 screen_offset_y; // 0x4C
	__int32 screen_half_scale_x; // 0x50
	__int32 screen_half_scale_y; // 0x54
	__int32 fov_y; // 0x58
	__int32 aspect; // 0x5C
	float offset_z; // 0x60
	float z_value_scale; // 0x64
	float x_scale; // 0x68
	float y_scale; // 0x6C
	static void (*const construct)(c_curved_hud_test *);
	static void (*const transform)(c_curved_hud_test *, float, float, real_point2d *);
	static void (*const inverse_transform)(c_curved_hud_test *, real_point2d const *, float *, float *);
	static void (*const set_constants)(c_curved_hud_test *, long);
};
static_assert(sizeof(c_curved_hud_test) == 112, "Invalid c_curved_hud_test size");

#pragma pack(push, 4)
struct c_chud_point_tracker
{
	bool valid; // 0x0
	unsigned char __pad0[3]; // 0x1
	real_point3d world_point; // 0x4
	real_point2d screen_point; // 0x10
	real_point2d unknown_screen_point; // 0x18
	float offscreen_amount; // 0x20
	__int32 field_24; // 0x24
	__int32 field_28; // 0x28
	static void (*const prepare_for_draw)(c_chud_point_tracker *, float);
};
#pragma pack(pop)
static_assert(sizeof(c_chud_point_tracker) == 44, "Invalid c_chud_point_tracker size");

struct s_chud_shared_persistent_user_data
{
	char unknown0[3348]; // 0x0
	float warp_modifier; // 0xD14
	char gapD18; // 0xD18
	char use_pointer_tracker1; // 0xD19
	unsigned char __pad0[2]; // 0xD1A
	real_point3d unknown_pooint1; // 0xD1C
	c_chud_point_tracker point_tracker; // 0xD28
	char gapD54[708]; // 0xD54
	char use_pointer_tracker2; // 0x1018
	unsigned char __pad1[3]; // 0x1019
	real_point3d unknown_point2; // 0x101C
	c_chud_point_tracker pointer_tracker2; // 0x1028
	char gap1054[80]; // 0x1054
	real_vector4d local_to_world0; // 0x10A4
	real_vector4d local_to_world1; // 0x10B4
	real_vector4d local_to_world2; // 0x10C4
	real_vector4d local_to_world3; // 0x10D4
	long resolution_setting; // 0x10E4
};
static_assert(sizeof(s_chud_shared_persistent_user_data) == 4328, "Invalid s_chud_shared_persistent_user_data size");

struct s_chud_bitmap_info
{
	long group_definition_index; // 0x0
	long bitmap_index; // 0x4
	long width; // 0x8
	long height; // 0xC
	real_rectangle2d bounds; // 0x10
	float unknown_width; // 0x20
	float unknown_height; // 0x24
};
static_assert(sizeof(s_chud_bitmap_info) == 40, "Invalid s_chud_bitmap_info size");

struct s_chud_draw_widget_data
{
	__int32 output_user_index; // 0x0
	void *runtime_data; // 0x4
	s_chud_definition *definition; // 0x8
	void *group_widget; // 0xC
	void *widget; // 0x10
	void *child_widget; // 0x14
};
static_assert(sizeof(s_chud_draw_widget_data) == 24, "Invalid s_chud_draw_widget_data size");

// s_widget_geometry_properties is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

struct s_widget_geometry_quad_simple
{
	real_vector4d position0; // 0x0
	real_vector4d position1; // 0x10
	real_vector4d position2; // 0x20
	real_vector4d position3; // 0x30
};
static_assert(sizeof(s_widget_geometry_quad_simple) == 64, "Invalid s_widget_geometry_quad_simple size");

struct s_chud_navpoint
{
	long player_index; // 0x0
	long arrow_icon; // 0x4
	long objective_icon; // 0x8
	unsigned long marker_color; // 0xC
	unsigned long flags; // 0x10
	float opacity; // 0x14
	wchar_t service_tag[5]; // 0x18
	unsigned char __pad0[2]; // 0x22
	real_point3d position; // 0x24
};
static_assert(sizeof(s_chud_navpoint) == 48, "Invalid s_chud_navpoint size");

#pragma pack(push, 4)
struct s_chud_managed_navpoint
{
	s_chud_navpoint navpoint; // 0x0
	bool visible; // 0x30
	unsigned char __pad0[3]; // 0x31
	long submit_time; // 0x34
	float scale; // 0x38
	c_chud_point_tracker point_tracker; // 0x3C
	long state; // 0x68
	long field_6C; // 0x6C
	float opacity; // 0x70
};
#pragma pack(pop)
static_assert(sizeof(s_chud_managed_navpoint) == 116, "Invalid s_chud_managed_navpoint size");

struct c_chud_navpoint_manager
{
	s_chud_managed_navpoint m_navpoints[20]; // 0x0
	long m_reveal_player_index; // 0x910
	wchar_t m_player_name[17]; // 0x914
	unsigned char __pad0[2]; // 0x936
	float m_name_reveal; // 0x938
	float m_name_reveal_width; // 0x93C
	long m_name_navpoint_index; // 0x940
	float m_distance_reveal; // 0x944
	wchar_t m_distance_text[10]; // 0x948
	float m_distance_reveal_width; // 0x95C
	float m_distance_navpoint_index; // 0x960
	short field_964[4]; // 0x964
	__int32 unknown_index1; // 0x96C
	__int32 unknown_index2; // 0x970
	float field_974; // 0x974
	__int32 field_978; // 0x978
	__int32 field_97C; // 0x97C
	__int32 field_980; // 0x980
	__int32 field_984; // 0x984
	__int32 field_988; // 0x988
	__int32 field_98C; // 0x98C
	__int32 field_990; // 0x990
	__int32 field_994; // 0x994
	static unsigned long (*const get_managed_navpoint_arrow_color)(s_chud_managed_navpoint *);
	static unsigned long (*const get_managed_navpoint_base_color)(s_chud_managed_navpoint *);
	static unsigned long (*const get_managed_navpoint_text_color)(s_chud_managed_navpoint *);
};
static_assert(sizeof(c_chud_navpoint_manager) == 2456, "Invalid c_chud_navpoint_manager size");

#pragma pack(push, 4)
struct s_chud_render_data
{
	long vertex_shader_definition_index; // 0x0
	long pixel_shader_definition_index; // 0x4
	short blend_mode; // 0x8
	unsigned char __pad0[2]; // 0xA
	real_argb_color colors[6]; // 0xC
	float field_6C[6]; // 0x6C
	__int32 field_84; // 0x84
	float opacity; // 0x88
	float field_8C[4]; // 0x8C
	short_rectangle2d bounds; // 0x9C
};
#pragma pack(pop)
static_assert(sizeof(s_chud_render_data) == 164, "Invalid s_chud_render_data size");

struct c_chud_update_user_data
{
	public:
	enum e_interface_type
	{
		_interface_type_primary_weapon = 0,
		_interface_type_secondary_weapon,
		_interface_type_backpack_weapon,
		_interface_type_support_weapon,
		_interface_type_equipment,
		_interface_type_parent,
		_interface_type_unit,
		_interface_type_vehicle,
		_interface_type_hologram,
		_interface_type_scoreboard,
		_interface_type_sandbox,
		_interface_type_saved_film,
		_interface_type_unknown13,
		_interface_type_tank_mode,
		k_interface_type_count,
	};
#pragma pack(push, 4)
	struct s_interface_state
	{
		long object_index; // 0x0
		long chud_definition_index; // 0x4
		long special_hud_icon; // 0x8
		unsigned short field_C; // 0xC
		unsigned short field_E; // 0xE
		unsigned short weapon_target_flags; // 0x10
		unsigned short tracking_flags; // 0x12
		unsigned short flags; // 0x14
		unsigned short field_16; // 0x16
		float overheat; // 0x18
		__int32 field_1C; // 0x1C
		float battery; // 0x20
		float barrel_spin; // 0x24
		float field_28; // 0x28
		float charged_fraction; // 0x2C
		__int32 projectile_error; // 0x30
		float ammo_loaded; // 0x34
		__int32 field_38; // 0x38
		float ammo_reserve; // 0x3C
		__int32 rounds_inventory_maximum; // 0x40
		char is_reloaading; // 0x44
		char field_45; // 0x45
		char tracking_unknown1; // 0x46
		char tracking_unknown2; // 0x47
		char tracking; // 0x48
		char target_locked; // 0x49
		char field_4A; // 0x4A
		char field_4B; // 0x4B
		float tracking_locking_delta; // 0x4C
		real_point3d target_tracking_reticle_position; // 0x50
	};
#pragma pack(pop)
	static_assert(sizeof(s_interface_state) == 92, "Invalid s_interface_state size");
	struct s_consumable_state
	{
		float time_remaining; // 0x0
		float remaining_fraction; // 0x4
	};
	static_assert(sizeof(s_consumable_state) == 8, "Invalid s_consumable_state size");
	public:
	long output_user_index; // 0x0
	long player_index; // 0x4
	long unit_index; // 0x8
	long field_C; // 0xC
	bool field_10; // 0x10
	unsigned char __pad0[3]; // 0x11
	s_interface_state interfaces[15]; // 0x14
	unsigned short game_engine_flags; // 0x578
	unsigned short player_type_flags; // 0x57A
	unsigned short multiplayer_flags; // 0x57C
	unsigned short resolution_flags; // 0x57E
	unsigned long multiplayer_events_flags; // 0x580
	unsigned long field_584; // 0x584
	unsigned short field_588; // 0x588
	unsigned short campaign_flags; // 0x58A
	unsigned short skull_flags; // 0x58C
	unsigned short surival_mode_round_flags; // 0x58E
	unsigned short survival_mode_wave_flags; // 0x590
	unsigned short survival_mode_lives_flags; // 0x592
	unsigned short game_difficulty_mask; // 0x594
	short field_596; // 0x596
	short field_598; // 0x598
	unsigned short field_59A; // 0x59A
	unsigned short field_59C; // 0x59C
	unsigned char __pad1[2]; // 0x59E
	unsigned long unit_general_flags; // 0x5A0
	unsigned long shield_flags; // 0x5A4
	unsigned short unknown_flags; // 0x5A8
	unsigned char __pad2[2]; // 0x5AA
	unsigned long consumable_flags; // 0x5AC
	unsigned long consumable_energy_flags; // 0x5B0
	bool field_5B4; // 0x5B4
	unsigned char __pad3[3]; // 0x5B5
	float primary_auto_aim; // 0x5B8
	float secondary_auto_aim; // 0x5BC
	float body_vitality; // 0x5C0
	float shield_vitality; // 0x5C4
	float max_shield_vitality; // 0x5C8
	unsigned char shield_damage_decay_timer; // 0x5CC
	unsigned char __pad4[3]; // 0x5CD
	long selected_grenade; // 0x5D0
	long grenade_counts[4]; // 0x5D4
	short field_5E4; // 0x5E4
	unsigned char __pad5[2]; // 0x5E6
	long zoom_level; // 0x5E8
	bool field_5EC; // 0x5EC
	unsigned char __pad6[3]; // 0x5ED
	long frag_grenade_count; // 0x5F0
	long plasma_grenade_count; // 0x5F4
	unsigned long damage_flags; // 0x5F8
	bool field_5FC; // 0x5FC
	bool should_draw_motion_sensor; // 0x5FD
	unsigned char __pad7[2]; // 0x5FE
	float motion_sensor_range; // 0x600
	bool field_604; // 0x604
	bool has_shield; // 0x605
	unsigned char autoaim_flags; // 0x606
	char unknown_tracking2; // 0x607
	bool being_tracked; // 0x608
	bool hologram_target_available; // 0x609
	unsigned char __pad8[2]; // 0x60A
	real_point3d hologram_target_point; // 0x60C
	char tank_mode_active; // 0x618
	unsigned char __pad9[3]; // 0x619
	long field_d61C; // 0x61C
	c_aim_target_object aim_target_object; // 0x620
	bool carrying_objective; // 0x62C
	unsigned char __pad10[1]; // 0x62D
	short consumable_icons[4]; // 0x62E
	short consumable_cooldown_text; // 0x636
	float comsumable_cooldown_meter; // 0x638
	__int32 consumable_slot_index; // 0x63C
	bool consumable_meter_visible; // 0x640
	unsigned char __pad11[3]; // 0x641
	float consumable_remaining_time; // 0x644
	float consumable_remaining_fraction; // 0x648
	s_consumable_state consumables[4]; // 0x64C
	float consumable_costs[4]; // 0x66C
	float energy_meters[16]; // 0x67C
	float stamina_recovery_time; // 0x6BC
	bool field_6C0; // 0x6C0
	bool field_6C1; // 0x6C1
	char pad[2]; // 0x6C2
	char game_engine[440]; // 0x6C4
	char metagame[64]; // 0x87C
	char saved_film[68]; // 0x8BC
	char netdebug[16]; // 0x900
};
static_assert(sizeof(c_chud_update_user_data) == 2320, "Invalid c_chud_update_user_data size");

struct c_chud_global_scripting
{
	bool show; // 0x0
	bool field_149[4]; // 0x1
	bool widget_show[4][13]; // 0x5
	unsigned char __pad0[3]; // 0x39
	float widget_alpha[4][13]; // 0x3C
	float widget_unknown1[4][13]; // 0x10C
	long widget_unknown2[4][13]; // 0x1DC
	bool bonus_round_show_timer; // 0x2AC
	bool bonus_round_start_timer; // 0x2AD
	unsigned char __pad1[2]; // 0x2AE
	long bonus_round_set_timer; // 0x2B0
	long bonus_round_target_score; // 0x2B4
};
static_assert(sizeof(c_chud_global_scripting) == 696, "Invalid c_chud_global_scripting size");

struct c_chud_persistent_global_data
{
	char field_0[8][40]; // 0x0
	long field_140; // 0x140
	char field_144; // 0x144
	unsigned char __pad0[3]; // 0x145
	c_chud_global_scripting m_scripting; // 0x148
	char player_data[16][28]; // 0x400
};
static_assert(sizeof(c_chud_persistent_global_data) == 1472, "Invalid c_chud_persistent_global_data size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_INTERFACE_CHUD_CHUD_HPP__
