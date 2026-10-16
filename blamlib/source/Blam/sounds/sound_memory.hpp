#ifndef __BLAM_SOUNDS_SOUND_MEMORY_HPP__
#define __BLAM_SOUNDS_SOUND_MEMORY_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/async/async.hpp"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/math/sound_math.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/sounds/platform_sound.hpp"
#include "Blam/sounds/sound_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Forge/ForgeUndo.hpp"

/* ---------- forward declarations */

struct c_async_completion_flag;
struct looping_sound_datum;
struct looping_sound_track_datum;
struct real_decibel;
struct real_matrix4x3;
struct real_quaternion;
struct real_vector3d;
struct s_cluster_reference;
struct s_datum;
struct s_game_looping_sound_datum;
struct s_looping_sound_component_track_data;
struct s_platform_sound_status;
struct s_sound_definition;
struct s_sound_listener;
struct s_sound_location;
struct s_sound_manager_environment;
struct s_sound_manager_globals;
struct s_sound_manager_reverb;
struct s_sound_permutation;
struct s_sound_permutation_chunk;
struct s_sound_pitch_range;
struct s_sound_source;
struct s_sound_source_datum;
struct s_sound_tag_data;
struct s_sound_tracker;
struct s_xbox_sound_datum;
struct s_xbox_sound_datum_ex;
struct sound_channel_datum;

/* ---------- constants */

enum e_sound_channel_flag_bits
{
	_sound_channel_paused_bit = 0,
};

/* ---------- definitions */

struct s_xbox_sound_datum :
	public s_datum
{
	unsigned char software_reference_count; // 0x2
	unsigned char hardware_reference_count; // 0x3
	long sound_tag_index; // 0x4
	s_sound_permutation_chunk *chunk; // 0x8
};
static_assert(sizeof(s_xbox_sound_datum) == 12, "Invalid s_xbox_sound_datum size");

struct s_xbox_sound_datum_ex :
	public s_xbox_sound_datum
{
	c_async_completion_flag io_completion; // 0xC
	bool is_loading; // 0x14
	void *buffer; // 0x18
	unsigned long size; // 0x1C
	_inline bool io_pending() const;
	s_xbox_sound_datum_ex(); /* compiler_generated() */
	s_xbox_sound_datum_ex &operator=(s_xbox_sound_datum_ex &); /* compiler_generated() */
	s_xbox_sound_datum_ex &operator=(s_xbox_sound_datum_ex const &); /* compiler_generated() */
};
static_assert(sizeof(s_xbox_sound_datum_ex) == 32, "Invalid s_xbox_sound_datum_ex size");
static_assert(offsetof(s_xbox_sound_datum_ex, size) == 0x1C, "s_xbox_sound_datum_ex::size moved when its reconstructed padding was removed");

#pragma pack(push, 4)
struct s_sound_location
{
	real_point3d position; // 0x0
	real_quaternion rotation; // 0xC
	real_vector3d velocity; // 0x1C
	s_cluster_reference cluster; // 0x28
};
#pragma pack(pop)
static_assert(sizeof(s_sound_location) == 44, "Invalid s_sound_location size");

#pragma pack(push, 4)
struct looping_sound_track_datum
{
	unsigned long sound_index; // 0x0
	long range_permutation_flags; // 0x4
	unsigned long random_seed; // 0x8
	char playback_state; // 0xC
	char queued_playback_state; // 0xD
	char field_E; // 0xE
	char field_F; // 0xF
	float pitch_bend; // 0x10
	float speaker_gains[4]; // 0x14
};
#pragma pack(pop)
static_assert(sizeof(looping_sound_track_datum) == 36, "Invalid looping_sound_track_datum size");

struct s_sound_source
{
	c_flags<enum e_sound_source_flag_bits,unsigned short> flags; // 0x0
	char volume_type; // 0x2
	unsigned char spatialization_flags : 4; // 0x3
	char spatialization_mode : 4; // 0x3
	float gain_scale; // 0x4
	real_decibel additional_gain_db; // 0x8
	s_sound_location sound_location; // 0xC
	float cone_height; // 0x38
	float min_distance; // 0x3C
	float max_distance; // 0x40
	short inner_cone_angle; // 0x44
	short outer_cone_angle; // 0x46
	real_decibel unknown_db; // 0x48
	s_sound_source(s_sound_source &); /* compiler_generated() */
	s_sound_source(s_sound_source const &); /* compiler_generated() */
	s_sound_source(); /* compiler_generated() */
	s_sound_source &operator=(s_sound_source &); /* compiler_generated() */
	s_sound_source &operator=(s_sound_source const &); /* compiler_generated() */
};
// static_assert(sizeof(s_sound_source) == 76, "Invalid s_sound_source size");
// The layout above is the PDB's member list without its padding, so the
// size assertion is withheld: it would fail on alignment alone.

struct s_looping_sound_component_track_data
{
	unsigned long playback_controller_index; // 0x0
	char track_index; // 0x4
	char flags; // 0x5
	char syncrhonized_sound_ready; // 0x6
	unsigned long random_seed; // 0x8
	long range_permutation_flags; // 0xC
	long prev_track_sound_index; // 0x10
};
static_assert(sizeof(s_looping_sound_component_track_data) == 20, "Invalid s_looping_sound_component_track_data size");
static_assert(offsetof(s_looping_sound_component_track_data, random_seed) == 0x8, "s_looping_sound_component_track_data::random_seed moved when its reconstructed padding was removed");

struct s_sound_source_datum :
	public s_datum
{
	char type; // 0x2
	char ready_count; // 0x3
	long flags; // 0x4
	short source_flags; // 0x8
	short field_A; // 0xA
	long user_index; // 0xC
	long sound_tag_index; // 0x10
	unsigned long looping_sound; // 0x14
	s_sound_tracker *tracker; // 0x18
	s_sound_source source; // 0x1C
	s_looping_sound_component_track_data track_data; // 0x68
	long next_sound_index; // 0x7C
	unsigned char __pad0[20]; // 0x80
	s_sound_tracker *sound_effect_tracker; // 0x94
	long sound_tracker_datum_index; // 0x98
	long fade_start_time; // 0x9C
	float pitch; // 0xA0
	real_decibel gain_db; // 0xA4
	unsigned long random_seed; // 0xA8
	char pitch_range_index; // 0xAC
	char permutation_index; // 0xAD
	short permutation_chunk_index; // 0xAE
	char priority; // 0xB0
	char best_audible_user_index; // 0xB1
	char voice_index; // 0xB2
	unsigned long playback_controller_index; // 0xB4
	short channel_index; // 0xB8
	char fade_mode; // 0xBA
	char sound_event_stop_reason; // 0xBB
	real_decibel fade_db; // 0xBC
	long fade_out_time; // 0xC0
	long fade_in_time; // 0xC4
	s_sound_source_datum(s_sound_source_datum &); /* compiler_generated() */
	s_sound_source_datum(s_sound_source_datum const &); /* compiler_generated() */
	s_sound_source_datum(); /* compiler_generated() */
	s_sound_source_datum &operator=(s_sound_source_datum &); /* compiler_generated() */
	s_sound_source_datum &operator=(s_sound_source_datum const &); /* compiler_generated() */
};
static_assert(sizeof(s_sound_source_datum) == 200, "Invalid s_sound_source_datum size");
static_assert(offsetof(s_sound_source_datum, playback_controller_index) == 0xB4, "s_sound_source_datum::playback_controller_index moved when its reconstructed padding was removed");

struct looping_sound_datum :
	public s_datum
{
	char field_2; // 0x2
	char type; // 0x3
	long flags; // 0x4
	long looping_sound_tag_index; // 0x8
	long sound_identifier; // 0xC
	long output_user_index; // 0x10
	s_sound_source source; // 0x14
	c_flags<enum e_looping_sound_datum_flags,char> looping_sound_flags; // 0x60
	char component_sound_count; // 0x61
	char refresh_state; // 0x62
	bool flip_flop; // 0x63
	unsigned long playback_controller; // 0x64
	float layers[8]; // 0x68
	long timing[4]; // 0x88
	looping_sound_track_datum tracks[4]; // 0x98
	looping_sound_datum(looping_sound_datum &); /* compiler_generated() */
	looping_sound_datum(looping_sound_datum const &); /* compiler_generated() */
	looping_sound_datum(); /* compiler_generated() */
	looping_sound_datum &operator=(looping_sound_datum &); /* compiler_generated() */
	looping_sound_datum &operator=(looping_sound_datum const &); /* compiler_generated() */
};
static_assert(sizeof(looping_sound_datum) == 296, "Invalid looping_sound_datum size");

struct s_game_looping_sound_datum :
	public s_datum
{
	char state; // 0x2
	c_enum<enum e_game_looping_sound_type,char> type; // 0x3
	c_flags<enum e_game_looping_sound_flag,unsigned short> flags; // 0x4
	short object_attachment_index; // 0x6
	float scale; // 0x8
	long definition_index; // 0xC
	long platform_playback_identifier; // 0x10
	unsigned long random_seed; // 0x14
	union
	{
		struct
		{
			long object_index; // 0x0
			unsigned long function_name; // 0x4
		} object; // 0x18
		struct
		{
			float additional_gain_db; // 0x0
			s_cluster_reference cluster; // 0x4
			char background_sound_index; // 0x6
		} unattached; // 0x18
		struct
		{
			long stop_tick; // 0x0
			long identifier; // 0x4
		} music; // 0x18
	};
	s_game_looping_sound_datum(s_game_looping_sound_datum &); /* compiler_generated() */
	s_game_looping_sound_datum(s_game_looping_sound_datum const &); /* compiler_generated() */
	s_game_looping_sound_datum(); /* compiler_generated() */
	s_game_looping_sound_datum &operator=(s_game_looping_sound_datum &); /* compiler_generated() */
	s_game_looping_sound_datum &operator=(s_game_looping_sound_datum const &); /* compiler_generated() */
};
static_assert(sizeof(s_game_looping_sound_datum) == 32, "Invalid s_game_looping_sound_datum size");

struct s_sound_tag_data
{
	long sound_tag_index; // 0x0
	s_sound_definition *sound_definition; // 0x4
	unsigned long sound_source; // 0x8
	s_sound_pitch_range *pitch_range; // 0xC
	s_sound_permutation *permutation; // 0x10
};
static_assert(sizeof(s_sound_tag_data) == 20, "Invalid s_sound_tag_data size");

struct sound_channel_datum
{
	unsigned long sound_index; // 0x0
	long voice_index; // 0x4
	unsigned char __pad0[4]; // 0x8
	long refresh_counter; // 0xC
	char type_index; // 0x10
	char flags; // 0x11
	char spatial_flags; // 0x12
	char prev_spatial_flags; // 0x13
	short hardware_source_index; // 0x14
	short hardware_voice_index; // 0x16
	float cinematic_fade_timer; // 0x18
	float playing_time_seconds; // 0x1C
	long spatialization_unknown_time; // 0x20
	long playing_sound_definition_index; // 0x24
	long queued_sound_definition_index; // 0x28
	short playing_chunk_index; // 0x2C
	short queued_chunk_index; // 0x2E
	s_sound_permutation *playing_permutation; // 0x30
	s_sound_permutation *queued_permutation; // 0x34
};
static_assert(sizeof(sound_channel_datum) == 56, "Invalid sound_channel_datum size");

struct s_sound_listener
{
	long header_signatre; // 0x0
	s_cluster_reference cluster_reference; // 0x4
	short global_material_type; // 0x6
	char valid; // 0x8
	bool underwater; // 0x9
	real_matrix4x3 transform; // 0xC
	real_vector3d velocity; // 0x40
	long footer_signature; // 0x4C
};
static_assert(sizeof(s_sound_listener) == 80, "Invalid s_sound_listener size");
static_assert(offsetof(s_sound_listener, transform) == 0xC, "s_sound_listener::transform moved when its reconstructed padding was removed");

struct s_sound_manager_reverb
{
	float weight; // 0x0
	long sound_environemnt_tag_index; // 0x4
	float unknown1; // 0x8
	float unknown2; // 0xC
	float unknown3; // 0x10
	float unknown4; // 0x14
	unsigned char __pad0[4]; // 0x18
};
static_assert(sizeof(s_sound_manager_reverb) == 28, "Invalid s_sound_manager_reverb size");

struct s_sound_manager_environment
{
	public:
	struct s_propagations
	{
		float unknown1; // 0x0
		float unknown2; // 0x4
		long environment_tag_index; // 0x8
		unsigned char __pad0[16]; // 0xC  // hades: unknown tail; refresh_channel (0x10A34780) reads globals+0x26C
	};
	// Withheld: the type inventory does not describe this type, so its
	// padding could not be reconstructed.
	public:
	long environment_type; // 0x0
	s_propagations propagations[2]; // 0x4
	long propagation_count; // 0x3C
};
// static_assert(sizeof(s_sound_manager_environment) == 64, "Invalid s_sound_manager_environment size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

struct s_sound_manager_globals
{
	s_platform_sound_status platform_status; // 0x0
	unsigned long allocated_hardware_source_bit_vector[7]; // 0x60
	unsigned long alocated_hardware_voice_bit_vector[7]; // 0x7C
	bool initialized; // 0x98
	bool active2; // 0x99
	bool active3; // 0x9A
	bool paused; // 0x9B
	bool idling; // 0x9C
	bool rendering; // 0x9D
	bool frame_dirty; // 0x9E
	char field_9F; // 0x9F
	char flip_flop; // 0xA0
	unsigned char __pad0[3]; // 0xA1
	__int32 last_render_time_milliseconds; // 0xA4
	__int32 layer_fade_start_milliseconds; // 0xA8
	s_sound_listener listeners[4]; // 0xAC
	s_sound_manager_environment environment; // 0x1EC
	long previous_environemnt_type; // 0x22C
	float reverb_multiplier; // 0x230
	s_sound_manager_reverb reverbs[2]; // 0x234
	float frame_delta_time_seconds; // 0x26C
	char at_least_one_tick_has_passed; // 0x270
	unsigned char __pad1[3]; // 0x271
	float volume; // 0x274
	float cinematic_volume; // 0x278
	float cinematic_volume2; // 0x27C
	__int32 unknown_milliseconds; // 0x280
	float pause_gain; // 0x284
	float pause_fade_timer; // 0x288
	unsigned char __pad2[4]; // 0x28C
	__int32 solo_player_fade_out_delay_timer_seconds; // 0x290
	float solo_player_fade_out_delay_timer; // 0x294
	float solo_player_fade_out_time; // 0x298
	float solo_player_fade_in_time; // 0x29C
	long first_ducker; // 0x2A0
	float first_ducker_time; // 0x2A4
	long second_ducker : 32; // 0x2A8
	float second_ducker_time; // 0x2AC
	short channel_count; // 0x2B0
	short max_channels; // 0x2B2
	float cortana_effect_unknown; // 0x2B4
};
// static_assert(sizeof(s_sound_manager_globals) == 696, "Invalid s_sound_manager_globals size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

inline bool s_xbox_sound_datum_ex::io_pending() const // 0x10A342E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?io_pending@s_xbox_sound_datum_ex@@QBE_NXZ");

	return !io_completion.is_done() && is_loading;
}

/* ---------- private code */

#endif // __BLAM_SOUNDS_SOUND_MEMORY_HPP__
