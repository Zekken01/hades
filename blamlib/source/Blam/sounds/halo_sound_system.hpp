#ifndef __BLAM_SOUNDS_HALO_SOUND_SYSTEM_HPP__
#define __BLAM_SOUNDS_HALO_SOUND_SYSTEM_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/sounds/sound_memory.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/mod_package_updater.hpp"

/* ---------- forward declarations */

struct FMOD_EventSystem;
struct HALO_CHANNEL;
struct HALO_CHANNEL_PROPERTIES;
struct HALO_LOOPSOUND_TRIM_DSP;
struct HALO_PERM_SOUND;
struct HALO_SOUND_LIST;
struct HALO_SOUND_SYSTEM;
struct SYSTEM_FMOD;
struct s_mixer_state;
struct s_sound_tag_data;
struct s_unknown_properties;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct HALO_CHANNEL_PROPERTIES
{
	float gain; // 0x0
	float playback_rate_scale; // 0x4
	char field_8; // 0x8
	bool is_3d; // 0x9
	unsigned char __pad0[2]; // 0xA
	float d1; // 0xC
	float d2; // 0x10
	float d3; // 0x14
	float d4; // 0x18
	float min_listener_distance; // 0x1C
	float insideconeangle; // 0x20
	float outsideconeangle; // 0x24
	float outsidevolume; // 0x28
	__int32 field_2C; // 0x2C
	FMOD_VECTOR position; // 0x30
	FMOD_VECTOR forward; // 0x3C
	FMOD_VECTOR velocity; // 0x48
	float direct_occlusion; // 0x54
	float reverb_occlusion; // 0x58
	float reverb_room_factor; // 0x5C
	long playback_controller_index; // 0x60
	unsigned char __pad1[4]; // 0x64
	float unknown_gain_factor; // 0x68
};
#pragma pack(pop)
static_assert(sizeof(HALO_CHANNEL_PROPERTIES) == 108, "Invalid HALO_CHANNEL_PROPERTIES size");

struct HALO_LOOPSOUND_TRIM_DSP
{
	unsigned __int32 start_time_lo; // 0x0
	unsigned __int32 start_time_hi; // 0x4
	unsigned __int32 end_time_lo; // 0x8
	unsigned __int32 end_time_hi; // 0xC
	FMOD_DSP *fmod_dsp; // 0x10
	static HALO_LOOPSOUND_TRIM_DSP *(*OpNewConstruct)(HALO_LOOPSOUND_TRIM_DSP *);
	unsigned char __pad0[4]; // 0x14
};
static_assert(sizeof(HALO_LOOPSOUND_TRIM_DSP) == 24, "Invalid HALO_LOOPSOUND_TRIM_DSP size");

struct FMOD_EventSystem
{
	void **vftable; // 0x0
};
// static_assert(sizeof(FMOD_EventSystem) == 4, "Invalid FMOD_EventSystem size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

struct SYSTEM_FMOD
{
	void **vftable; // 0x0
	unsigned __int32 flags; // 0x4
	__int32 listener_count; // 0x2C
	FMOD_EventSystem *event_system; // 0x30
	FMOD_SPEAKERMODE speaker_mode; // 0x40
	FMOD_VECTOR listener_positions[4]; // 0x50
	char unknown[472]; // 0x80
	FMOD_REVERB_PROPERTIES desired_reverb_properties; // 0x258
	FMOD_REVERB_PROPERTIES current_reverb_properties; // 0x2D4
};
// static_assert(sizeof(SYSTEM_FMOD) == 848, "Invalid SYSTEM_FMOD size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

struct HALO_PERM_SOUND
{
	public:
	struct s_unknown_properties
	{
		__int32 field_0; // 0x0
		unsigned __int32 flags; // 0x4
		float low_pass_reverb_scale; // 0x8
		float low_pass_gain_scale; // 0xC
		float low_pass_gain_attenuation_scale; // 0x10
		__int32 field_14; // 0x14
		__int32 field_18; // 0x18
		float low_pass_gain_max; // 0x1C
		float low_pass_gain_min; // 0x20
	};
	// static_assert(sizeof(s_unknown_properties) == 36, "Invalid s_unknown_properties size");
	// Withheld: the type inventory does not describe this type, so its
	// padding could not be reconstructed.
	struct s_mixer_state
	{
		long sound_definition_index; // 0x0
		long reference_count; // 0x4
		unsigned long flags; // 0x8
	};
	// static_assert(sizeof(s_mixer_state) == 12, "Invalid s_mixer_state size");
	// Withheld: the type inventory does not describe this type, so its
	// padding could not be reconstructed.
	public:
	FMOD_SOUND *fmod_sound; // 0x0
	FMOD_CHANNEL *fmod_channel; // 0x4
	HALO_PERM_SOUND *previous_perm; // 0x8
	unsigned long init_time; // 0xC
	unsigned long played_time; // 0x10
	HALO_LOOPSOUND_TRIM_DSP *loopsound_trim; // 0x14
	s_unknown_properties *unknown_properties; // 0x18
	s_mixer_state *mixer_state; // 0x1C
	__int32 sound_definition_index; // 0x20
	__int32 permutation_name_string_id; // 0x24
	bool loop_hack; // 0x28
	unsigned char __pad0[3]; // 0x29
	__int32 sample_count; // 0x2C
	bool sequenced_flag; // 0x30
	unsigned char __pad1[3]; // 0x31
	__int32 first_sample; // 0x34
	static bool (*isPlaying)(HALO_PERM_SOUND *);
	static void (*Play)(HALO_PERM_SOUND *, HALO_CHANNEL_PROPERTIES *);
	static bool (*Init)(HALO_PERM_SOUND *, s_sound_tag_data *, HALO_CHANNEL_PROPERTIES *, HALO_CHANNEL *);
	static HALO_PERM_SOUND *(*Free)(HALO_PERM_SOUND *);
	static HALO_PERM_SOUND *(*Reset)(HALO_PERM_SOUND *);
	static __int32 (*UpdateChannelProperties)(HALO_PERM_SOUND *, HALO_CHANNEL_PROPERTIES *);
	static __int32 (*InitChannelProperties)(HALO_PERM_SOUND *, HALO_CHANNEL_PROPERTIES *);
	static void (*Delay)(HALO_PERM_SOUND *, bool);
	static void (*DelayDSP)(HALO_PERM_SOUND *);
};
// static_assert(sizeof(HALO_PERM_SOUND) == 56, "Invalid HALO_PERM_SOUND size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

#pragma pack(push, 4)
struct HALO_CHANNEL
{
	public:
	enum STATE
	{
		_STATE_IDLE = 0,
		_STATE_STOPPING,
		_STATE_PLAYING,
		_STATE_FULL,
	};
	public:
	long state; // 0x0
	long id; // 0x4
	HALO_PERM_SOUND queue[2]; // 0x8
	HALO_CHANNEL_PROPERTIES properties; // 0x78
	static char const *STATE_NAMES[0];
};
#pragma pack(pop)
// static_assert(sizeof(HALO_CHANNEL) == 228, "Invalid HALO_CHANNEL size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

struct HALO_SOUND_SYSTEM
{
	public:
	enum FLAG_BITS
	{
		_PAUSED_BIT = 1, // 0x0001
	};
	public:
	void *vftable; // 0x0
	FMOD_SYSTEM *fmod_system; // 0x4
	unsigned __int32 dsp_buffer_size; // 0x8
	__int32 output_sample_rate; // 0xC
	FMOD_CHANNELGROUP *sfx_channel_group; // 0x10
	float sfx_volume; // 0x14
	FMOD_CHANNELGROUP *voice_channel_group; // 0x18
	float voice_volume; // 0x1C
	FMOD_CHANNELGROUP *music_channel_group; // 0x20
	float music_volume; // 0x24
	FMOD_CHANNELGROUP *master_channel_group; // 0x28
	float master_volume; // 0x2C
	unsigned long flags; // 0x30
	unsigned __int32 paused_time_hi; // 0x34
	unsigned __int32 paused_time_lo; // 0x38
	unsigned char __pad0[32]; // 0x3C
	HALO_LIST<HALO_SOUND_LIST> unknown_list1; // 0x5C
	HALO_LIST<void> unknown_list2; // 0x68
	HALO_LIST<HALO_CHANNEL> channels; // 0x74
	HALO_LIST<void> unknown_list3; // 0x80
	long field_8C; // 0x8C
	long field_90; // 0x90
	long field_94; // 0x94
	long field_98; // 0x98
	long field_9C; // 0x9C
	long field_A0; // 0xA0
	long field_A4; // 0xA4
	long field_A8; // 0xA8
	long field_AC; // 0xAC
	HALO_LIST<HALO_CHANNEL> unknown_channels; // 0xB0
	HALO_LIST<void> mixer_states; // 0xBC
	HALO_LIST<void> unknown_list4; // 0xC8
	unsigned char __pad1[60]; // 0xD4
	float matrix[16]; // 0x110
	float inverse_matrix[16]; // 0x150
	_inline HALO_CHANNEL *FindChannel(__int32 id);
	static _inline HALO_SOUND_SYSTEM *Get();
};
// static_assert(sizeof(HALO_SOUND_SYSTEM) == 480, "Invalid HALO_SOUND_SYSTEM size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

extern HALO_CHANNEL *_sub_10A2F840(HALO_SOUND_SYSTEM *const, __int32);
_inline HALO_CHANNEL *HALO_SOUND_SYSTEM::FindChannel(__int32 id) // 0x10A2F840
{
	mangled_x86(MANGLED_TODO, "?FindChannel@HALO_SOUND_SYSTEM@@QAEPAUHALO_CHANNEL@@H@Z");
	// __int32 id;
	{
		// __int32 i;
	}
	todo("implement");
	HALO_CHANNEL * __result = _sub_10A2F840(this, id);
	return __result;
}

_inline HALO_SOUND_SYSTEM *HALO_SOUND_SYSTEM::Get() // 0x10A2F8F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Get@HALO_SOUND_SYSTEM@@SAPAU1@XZ");
	// procedure flags: nofpo

	return *(HALO_SOUND_SYSTEM * *)0x18bc9c8;
}

/* ---------- private code */

#endif // __BLAM_SOUNDS_HALO_SOUND_SYSTEM_HPP__
