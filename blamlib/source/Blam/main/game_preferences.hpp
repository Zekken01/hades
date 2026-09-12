#ifndef __BLAM_MAIN_GAME_PREFERENCES_HPP__
#define __BLAM_MAIN_GAME_PREFERENCES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/async/async.hpp"

/* ---------- forward declarations */

struct c_async_completion_flag;
struct s_global_preferences;
struct s_global_preferences_data;
struct s_global_preferences_settings;

/* ---------- constants */

/* ---------- definitions */

struct s_global_preferences_settings
{
	public:
	enum e_level
	{
		_low = 0,
		_medium,
		_high,
	};
	enum e_input_type
	{
		_input_type_keyboard = 0,
		_input_type_gamepad,
	};
	enum e_display_type
	{
		_display_mode_default = 0,
		_display_type_standard,
		_display_type_wide,
	};
	enum e_display_subtitles
	{
		_display_subtitles_auto = 0,
		_display_subtitles_on,
		_display_subtitles_off,
	};
	struct s_video_settings_new
	{
		long field_0; // 0x0
		long resolution_width_wide; // 0x4
		long resolution_height_wide; // 0x8
		long resolution_width; // 0xC
		long resolution_height; // 0x10
		e_level texture_resolution; // 0x14
		e_level shadow_quality; // 0x18
		e_level texture_filtering_quality; // 0x1C
		e_level lighting_quality; // 0x20
		e_level effects_quality; // 0x24
		e_level details_quality; // 0x28
		e_level postprocessing_quality; // 0x2C
		bool motion_blur; // 0x30
		bool vsync; // 0x31
		bool anti_aliasing; // 0x32
	};
	static_assert(sizeof(s_video_settings_new) == 52, "Invalid s_video_settings_new size");
#pragma pack(push, 4)
	struct s_input_settings
	{
		e_input_type type; // 0x0
		long mouse_sensitivity_vertical; // 0x4
		long mouse_sensitivity_horizontal; // 0x8
		long mouse_sensitivity_vehicle_vertical; // 0xC
		long mouse_sensitivity_vehicle_horizontal; // 0x10
		long mouse_acceleration; // 0x14
		bool mouse_filter; // 0x18
		bool invert_mouse; // 0x19
		unsigned char __pad0[2]; // 0x1A
		long button_layout; // 0x1C
		unsigned char bindings[380]; // 0x20
	};
#pragma pack(pop)
	static_assert(sizeof(s_input_settings) == 412, "Invalid s_input_settings size");
	public:
	long version; // 0x0
	long lanquage; // 0x4
	long last_font_lanquage; // 0x8
	unsigned long last_font_modification_date[2]; // 0xC
	unsigned long build_number; // 0x14
	long betrayal_penalty; // 0x18
	long eviction_count; // 0x1C
	unsigned long last_main_menu_item; // 0x20
	long field_24; // 0x24
	unsigned char last_game_setup[269176]; // 0x28
	long privacy_mode; // 0x41BA0
	unsigned long hardware_checksum; // 0x41BA4
	long display_adapter; // 0x41BA8
	bool display_fullscreen; // 0x41BAC
	e_display_type display_type; // 0x41BB0
	long display_contrast; // 0x41BB4
	long display_brightness; // 0x41BB8
	s_video_settings_new video_settings; // 0x41BBC
	bool hide_watermark; // 0x41BF0
	e_display_subtitles display_subtitles; // 0x41BF4
	long content_item_unique_name_number_seeds[14]; // 0x41BF8
	long master_volume; // 0x41C30
	long sfx_volume; // 0x41C34
	long music_volume; // 0x41C38
	long voice_volume; // 0x41C3C
	long voice_chat_control; // 0x41C40
	long voice_chat_volume; // 0x41C44
	bool toggle_crouch; // 0x41C48
	bool hud_shake; // 0x41C49
	char field_41C4A; // 0x41C4A
	long team_markers; // 0x41C4C
	float camera_fov; // 0x41C50
	s_input_settings input_settings; // 0x41C54
};
static_assert(sizeof(s_global_preferences_settings) == 269808, "Invalid s_global_preferences_settings size");
static_assert(offsetof(s_global_preferences_settings, display_type) == 0x41BB0, "s_global_preferences_settings::display_type moved when its reconstructed padding was removed");
static_assert(offsetof(s_global_preferences_settings, display_subtitles) == 0x41BF4, "s_global_preferences_settings::display_subtitles moved when its reconstructed padding was removed");
static_assert(offsetof(s_global_preferences_settings, team_markers) == 0x41C4C, "s_global_preferences_settings::team_markers moved when its reconstructed padding was removed");

struct s_global_preferences_data
{
	unsigned char sha1_hash[20]; // 0x0
	__int32 field_14; // 0x14
	s_global_preferences_settings settings; // 0x18
	unsigned char campaign_state[504]; // 0x41E08
};
static_assert(sizeof(s_global_preferences_data) == 270336, "Invalid s_global_preferences_data size");

#pragma pack(push, 4)
struct s_global_preferences
{
	bool initialized; // 0x0
	bool dirty; // 0x1
	unsigned char __pad0[2]; // 0x2
	void *file_handle; // 0x4
	s_global_preferences_data current; // 0x8
	unsigned char async_buffer[270336]; // 0x42008
	long async_task_id; // 0x84008
	c_async_completion_flag ready_to_write; // 0x8400C
	s_global_preferences(); /* compiler_generated() */
	s_global_preferences &operator=(s_global_preferences &); /* compiler_generated() */
	s_global_preferences &operator=(s_global_preferences const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_global_preferences) == 540692, "Invalid s_global_preferences size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_MAIN_GAME_PREFERENCES_HPP__
