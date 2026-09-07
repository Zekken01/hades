#ifndef __BLAM_FMOD_FMOD_FUNCTIONS_INL__
#define __BLAM_FMOD_FMOD_FUNCTIONS_INL__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

struct FMOD_CODEC_DESCRIPTION;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern "C" _inline FMOD_RESULT __stdcall FMOD_System_CreateCodec(FMOD_SYSTEM *system, FMOD_CODEC_DESCRIPTION *description, unsigned int priority);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_CreateSound(FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_CreateStream(FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_Get3DNumListeners(FMOD_SYSTEM *system, int *numlisteners);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetAdvancedSettings(FMOD_SYSTEM *system, FMOD_ADVANCEDSETTINGS *settings);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetCPUUsage(FMOD_SYSTEM *system, float *dsp, float *stream, float *geometry, float *update, float *total);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetChannelsPlaying(FMOD_SYSTEM *system, int *channels);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetDSPClock(FMOD_SYSTEM *system, unsigned int *hi, unsigned int *lo);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetDriverCaps(FMOD_SYSTEM *system, int id, FMOD_CAPS *caps, int *minfrequency, int *maxfrequency, FMOD_SPEAKERMODE *controlpanelspeakermode);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetDriverInfo(FMOD_SYSTEM *system, int id, char *name, int namelen, FMOD_GUID *guid);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetMemoryInfo(FMOD_SYSTEM *system, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, unsigned int *memoryused_array);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetNumDrivers(FMOD_SYSTEM *system, int *numdrivers);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetOutput(FMOD_SYSTEM *system, FMOD_OUTPUTTYPE *output);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetSoftwareChannels(FMOD_SYSTEM *system, int *numsoftwarechannels);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetVersion(FMOD_SYSTEM *system, unsigned int *version);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_LockDSP(FMOD_SYSTEM *system);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_PlaySound(FMOD_SYSTEM *system, FMOD_CHANNELINDEX channelid, FMOD_SOUND *sound, FMOD_BOOL paused, FMOD_CHANNEL **channel);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_SetAdvancedSettings(FMOD_SYSTEM *system, FMOD_ADVANCEDSETTINGS *settings);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_SetDSPBufferSize(FMOD_SYSTEM *system, unsigned int bufferlength, int numbuffers);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_SetDriver(FMOD_SYSTEM *system, int driver);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_SetHardwareChannels(FMOD_SYSTEM *system, int min2d, int max2d, int min3d, int max3d);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_SetOutput(FMOD_SYSTEM *system, FMOD_OUTPUTTYPE output);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_SetSoftwareChannels(FMOD_SYSTEM *system, int numsoftwarechannels);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_SetSpeakerMode(FMOD_SYSTEM *system, FMOD_SPEAKERMODE speakermode);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_UnlockDSP(FMOD_SYSTEM *system);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Sound_GetDefaults(FMOD_SOUND *sound, float *frequency, float *volume, float *pan, int *priority);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Sound_GetFormat(FMOD_SOUND *sound, FMOD_SOUND_TYPE *type, FMOD_SOUND_FORMAT *format, int *channels, int *bits);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Sound_GetLength(FMOD_SOUND *sound, unsigned int *length, FMOD_TIMEUNIT lengthtype);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Sound_GetUserData(FMOD_SOUND *sound, void **userdata);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_Get3DMinMaxDistance(FMOD_CHANNEL *channel, float *mindistance, float *maxdistance);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_GetCurrentSound(FMOD_CHANNEL *channel, FMOD_SOUND **sound);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_GetDelay(FMOD_CHANNEL *channel, FMOD_DELAYTYPE delaytype, unsigned int *delayhi, unsigned int *delaylo);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_GetFrequency(FMOD_CHANNEL *channel, float *frequency);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_GetPosition(FMOD_CHANNEL *channel, unsigned int *position, FMOD_TIMEUNIT postype);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_IsPlaying(FMOD_CHANNEL *channel, FMOD_BOOL *isplaying);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_Set3DAttributes(FMOD_CHANNEL *channel, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_Set3DConeOrientation(FMOD_CHANNEL *channel, FMOD_VECTOR *orientation);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_Set3DConeSettings(FMOD_CHANNEL *channel, float insideconeangle, float outsideconeangle, float outsidevolume);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_Set3DDopplerLevel(FMOD_CHANNEL *channel, float level);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_Set3DMinMaxDistance(FMOD_CHANNEL *channel, float mindistance, float maxdistance);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_Set3DOcclusion(FMOD_CHANNEL *channel, float directocclusion, float reverbocclusion);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_Set3DSpread(FMOD_CHANNEL *channel, float angle);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_SetChannelGroup(FMOD_CHANNEL *channel, FMOD_CHANNELGROUP *channelgroup);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_SetDelay(FMOD_CHANNEL *channel, FMOD_DELAYTYPE delaytype, unsigned int delayhi, unsigned int delaylo);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_SetFrequency(FMOD_CHANNEL *channel, float frequency);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_SetMode(FMOD_CHANNEL *channel, FMOD_MODE mode);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_SetPaused(FMOD_CHANNEL *channel, FMOD_BOOL paused);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_SetPosition(FMOD_CHANNEL *channel, unsigned int position, FMOD_TIMEUNIT postype);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_SetReverbProperties(FMOD_CHANNEL *channel, const FMOD_REVERB_CHANNELPROPERTIES *prop);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_SetSpeakerLevels(FMOD_CHANNEL *channel, FMOD_SPEAKER speaker, float *levels, int numlevels);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_SetSpeakerMix(FMOD_CHANNEL *channel, float frontleft, float frontright, float center, float lfe, float backleft, float backright, float sideleft, float sideright);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_SetVolume(FMOD_CHANNEL *channel, float volume);

/* ---------- globals */

/* ---------- public code */

extern FMOD_RESULT _sub_106CBEA0(FMOD_SYSTEM *, FMOD_CODEC_DESCRIPTION *, unsigned int);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_CreateCodec(FMOD_SYSTEM *system, FMOD_CODEC_DESCRIPTION *description, unsigned int priority) // 0x106CBEA0
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_CreateCodec@12");
	// unsigned __int32 priority;
	// FMOD_RESULT (*const _FMOD_System_CreateCodec)(FMOD_SYSTEM *, FMOD_CODEC_DESCRIPTION *, unsigned __int32);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, FMOD_CODEC_DESCRIPTION *, unsigned __int32)
	todo("implement");
	FMOD_RESULT __result = _sub_106CBEA0(system, description, priority);
	return __result;
}

extern FMOD_RESULT _sub_106CBF10(FMOD_SYSTEM *, const char *, FMOD_MODE, FMOD_CREATESOUNDEXINFO *, FMOD_SOUND **);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_CreateSound(FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound) // 0x106CBF10
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_CreateSound@20");
	// FMOD_SOUND **sound;
	// FMOD_RESULT (*const _FMOD_System_CreateSound)(FMOD_SYSTEM *, char const *, unsigned __int32, FMOD_CREATESOUNDEXINFO *, FMOD_SOUND **);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, char const *, unsigned __int32, FMOD_CREATESOUNDEXINFO *, FMOD_SOUND **)
	todo("implement");
	FMOD_RESULT __result = _sub_106CBF10(system, name_or_data, mode, exinfo, sound);
	return __result;
}

extern FMOD_RESULT _sub_10A36FC0(FMOD_SYSTEM *, const char *, FMOD_MODE, FMOD_CREATESOUNDEXINFO *, FMOD_SOUND **);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_CreateStream(FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound) // 0x10A36FC0
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_CreateStream@20");
	// FMOD_SOUND **sound;
	// FMOD_RESULT (*const _FMOD_System_CreateStream)(FMOD_SYSTEM *, char const *, unsigned __int32, FMOD_CREATESOUNDEXINFO *, FMOD_SOUND **);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, char const *, unsigned __int32, FMOD_CREATESOUNDEXINFO *, FMOD_SOUND **)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36FC0(system, name_or_data, mode, exinfo, sound);
	return __result;
}

extern FMOD_RESULT _sub_10A37040(FMOD_SYSTEM *, int *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_Get3DNumListeners(FMOD_SYSTEM *system, int *numlisteners) // 0x10A37040
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_Get3DNumListeners@8");
	// __int32 *numlisteners;
	// FMOD_RESULT (*const _FMOD_System_Get3DNumListeners)(FMOD_SYSTEM *, __int32 *);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, __int32 *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A37040(system, numlisteners);
	return __result;
}

extern FMOD_RESULT _sub_10A370B0(FMOD_SYSTEM *, FMOD_ADVANCEDSETTINGS *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetAdvancedSettings(FMOD_SYSTEM *system, FMOD_ADVANCEDSETTINGS *settings) // 0x10A370B0
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_GetAdvancedSettings@8");
	// FMOD_ADVANCEDSETTINGS *settings;
	// FMOD_RESULT (*const _FMOD_System_GetAdvancedSettings)(FMOD_SYSTEM *, FMOD_ADVANCEDSETTINGS *);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, FMOD_ADVANCEDSETTINGS *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A370B0(system, settings);
	return __result;
}

extern FMOD_RESULT _sub_10A37120(FMOD_SYSTEM *, float *, float *, float *, float *, float *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetCPUUsage(FMOD_SYSTEM *system, float *dsp, float *stream, float *geometry, float *update, float *total) // 0x10A37120
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_GetCPUUsage@24");
	// float *total;
	// FMOD_RESULT (*const _FMOD_System_GetCPUUsage)(FMOD_SYSTEM *, float *, float *, float *, float *, float *);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, float *, float *, float *, float *, float *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A37120(system, dsp, stream, geometry, update, total);
	return __result;
}

extern FMOD_RESULT _sub_10A371A0(FMOD_SYSTEM *, int *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetChannelsPlaying(FMOD_SYSTEM *system, int *channels) // 0x10A371A0
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_GetChannelsPlaying@8");
	// __int32 *channels;
	// FMOD_RESULT (*const _FMOD_System_GetChannelsPlaying)(FMOD_SYSTEM *, __int32 *);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, __int32 *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A371A0(system, channels);
	return __result;
}

extern FMOD_RESULT _sub_10A37210(FMOD_SYSTEM *, unsigned int *, unsigned int *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetDSPClock(FMOD_SYSTEM *system, unsigned int *hi, unsigned int *lo) // 0x10A37210
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_GetDSPClock@12");
	// unsigned __int32 *lo;
	// FMOD_RESULT (*const _FMOD_System_GetDSPClock)(FMOD_SYSTEM *, unsigned __int32 *, unsigned __int32 *);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, unsigned __int32 *, unsigned __int32 *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A37210(system, hi, lo);
	return __result;
}

extern FMOD_RESULT _sub_10A37280(FMOD_SYSTEM *, int, FMOD_CAPS *, int *, int *, FMOD_SPEAKERMODE *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetDriverCaps(FMOD_SYSTEM *system, int id, FMOD_CAPS *caps, int *minfrequency, int *maxfrequency, FMOD_SPEAKERMODE *controlpanelspeakermode) // 0x10A37280
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_GetDriverCaps@24");
	// FMOD_SPEAKERMODE *controlpanelspeakermode;
	// FMOD_RESULT (*const _FMOD_System_GetDriverCaps)(FMOD_SYSTEM *, __int32, unsigned __int32 *, __int32 *, __int32 *, FMOD_SPEAKERMODE *);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, __int32, unsigned __int32 *, __int32 *, __int32 *, FMOD_SPEAKERMODE *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A37280(system, id, caps, minfrequency, maxfrequency, controlpanelspeakermode);
	return __result;
}

extern FMOD_RESULT _sub_10A37300(FMOD_SYSTEM *, int, char *, int, FMOD_GUID *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetDriverInfo(FMOD_SYSTEM *system, int id, char *name, int namelen, FMOD_GUID *guid) // 0x10A37300
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_GetDriverInfo@20");
	// FMOD_GUID *guid;
	// FMOD_RESULT (*const _FMOD_System_GetDriverInfo)(FMOD_SYSTEM *, __int32, char *, __int32, FMOD_GUID *);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, __int32, char *, __int32, FMOD_GUID *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A37300(system, id, name, namelen, guid);
	return __result;
}

extern FMOD_RESULT _sub_10A37380(FMOD_SYSTEM *, unsigned int, unsigned int, unsigned int *, unsigned int *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetMemoryInfo(FMOD_SYSTEM *system, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, unsigned int *memoryused_array) // 0x10A37380
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_GetMemoryInfo@20");
	// unsigned __int32 *memoryused_array;
	// FMOD_RESULT (*const _FMOD_System_GetMemoryInfo)(FMOD_SYSTEM *, unsigned __int32, unsigned __int32, unsigned __int32 *, unsigned __int32 *);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, unsigned __int32, unsigned __int32, unsigned __int32 *, unsigned __int32 *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A37380(system, memorybits, event_memorybits, memoryused, memoryused_array);
	return __result;
}

extern FMOD_RESULT _sub_10A37400(FMOD_SYSTEM *, int *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetNumDrivers(FMOD_SYSTEM *system, int *numdrivers) // 0x10A37400
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_GetNumDrivers@8");
	// __int32 *numdrivers;
	// FMOD_RESULT (*const _FMOD_System_GetNumDrivers)(FMOD_SYSTEM *, __int32 *);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, __int32 *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A37400(system, numdrivers);
	return __result;
}

extern FMOD_RESULT _sub_10A37470(FMOD_SYSTEM *, FMOD_OUTPUTTYPE *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetOutput(FMOD_SYSTEM *system, FMOD_OUTPUTTYPE *output) // 0x10A37470
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_GetOutput@8");
	// FMOD_OUTPUTTYPE *output;
	// FMOD_RESULT (*const _FMOD_System_GetOutput)(FMOD_SYSTEM *, FMOD_OUTPUTTYPE *);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, FMOD_OUTPUTTYPE *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A37470(system, output);
	return __result;
}

extern FMOD_RESULT _sub_10A374E0(FMOD_SYSTEM *, int *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetSoftwareChannels(FMOD_SYSTEM *system, int *numsoftwarechannels) // 0x10A374E0
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_GetSoftwareChannels@8");
	// __int32 *numsoftwarechannels;
	// FMOD_RESULT (*const _FMOD_System_GetSoftwareChannels)(FMOD_SYSTEM *, __int32 *);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, __int32 *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A374E0(system, numsoftwarechannels);
	return __result;
}

extern FMOD_RESULT _sub_10A37550(FMOD_SYSTEM *, unsigned int *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_GetVersion(FMOD_SYSTEM *system, unsigned int *version) // 0x10A37550
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_GetVersion@8");
	// unsigned __int32 *version;
	// FMOD_RESULT (*const _FMOD_System_GetVersion)(FMOD_SYSTEM *, unsigned __int32 *);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, unsigned __int32 *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A37550(system, version);
	return __result;
}

extern FMOD_RESULT _sub_10A375C0(FMOD_SYSTEM *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_LockDSP(FMOD_SYSTEM *system) // 0x10A375C0
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_LockDSP@4");
	// FMOD_SYSTEM *system;
	// FMOD_RESULT (*const _FMOD_System_LockDSP)(FMOD_SYSTEM *);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A375C0(system);
	return __result;
}

extern FMOD_RESULT _sub_10A37620(FMOD_SYSTEM *, FMOD_CHANNELINDEX, FMOD_SOUND *, FMOD_BOOL, FMOD_CHANNEL **);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_PlaySound(FMOD_SYSTEM *system, FMOD_CHANNELINDEX channelid, FMOD_SOUND *sound, FMOD_BOOL paused, FMOD_CHANNEL **channel) // 0x10A37620
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_PlaySound@20");
	// FMOD_CHANNEL **channel;
	// FMOD_RESULT (*const _FMOD_System_PlaySound)(FMOD_SYSTEM *, FMOD_CHANNELINDEX, FMOD_SOUND *, bool, FMOD_CHANNEL **);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, FMOD_CHANNELINDEX, FMOD_SOUND *, bool, FMOD_CHANNEL **)
	todo("implement");
	FMOD_RESULT __result = _sub_10A37620(system, channelid, sound, paused, channel);
	return __result;
}

extern FMOD_RESULT _sub_10A376A0(FMOD_SYSTEM *, FMOD_ADVANCEDSETTINGS *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_SetAdvancedSettings(FMOD_SYSTEM *system, FMOD_ADVANCEDSETTINGS *settings) // 0x10A376A0
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_SetAdvancedSettings@8");
	// FMOD_ADVANCEDSETTINGS *settings;
	// FMOD_RESULT (*const _FMOD_System_SetAdvancedSettings)(FMOD_SYSTEM *, FMOD_ADVANCEDSETTINGS *);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, FMOD_ADVANCEDSETTINGS *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A376A0(system, settings);
	return __result;
}

extern FMOD_RESULT _sub_10A37710(FMOD_SYSTEM *, unsigned int, int);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_SetDSPBufferSize(FMOD_SYSTEM *system, unsigned int bufferlength, int numbuffers) // 0x10A37710
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_SetDSPBufferSize@12");
	// __int32 numbuffers;
	// FMOD_RESULT (*const _FMOD_System_SetDSPBufferSize)(FMOD_SYSTEM *, unsigned __int32, __int32);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, unsigned __int32, __int32)
	todo("implement");
	FMOD_RESULT __result = _sub_10A37710(system, bufferlength, numbuffers);
	return __result;
}

extern FMOD_RESULT _sub_10A37780(FMOD_SYSTEM *, int);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_SetDriver(FMOD_SYSTEM *system, int driver) // 0x10A37780
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_SetDriver@8");
	// __int32 driver;
	// FMOD_RESULT (*const _FMOD_System_SetDriver)(FMOD_SYSTEM *, __int32);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, __int32)
	todo("implement");
	FMOD_RESULT __result = _sub_10A37780(system, driver);
	return __result;
}

extern FMOD_RESULT _sub_10A377F0(FMOD_SYSTEM *, int, int, int, int);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_SetHardwareChannels(FMOD_SYSTEM *system, int min2d, int max2d, int min3d, int max3d) // 0x10A377F0
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_SetHardwareChannels@20");
	// __int32 max3d;
	// FMOD_RESULT (*const _FMOD_System_SetHardwareChannels)(FMOD_SYSTEM *, __int32, __int32, __int32, __int32);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, __int32, __int32, __int32, __int32)
	todo("implement");
	FMOD_RESULT __result = _sub_10A377F0(system, min2d, max2d, min3d, max3d);
	return __result;
}

extern FMOD_RESULT _sub_10A37870(FMOD_SYSTEM *, FMOD_OUTPUTTYPE);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_SetOutput(FMOD_SYSTEM *system, FMOD_OUTPUTTYPE output) // 0x10A37870
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_SetOutput@8");
	// FMOD_OUTPUTTYPE output;
	// FMOD_RESULT (*const _FMOD_System_SetOutput)(FMOD_SYSTEM *, FMOD_OUTPUTTYPE);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, FMOD_OUTPUTTYPE)
	todo("implement");
	FMOD_RESULT __result = _sub_10A37870(system, output);
	return __result;
}

extern FMOD_RESULT _sub_10A378E0(FMOD_SYSTEM *, int);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_SetSoftwareChannels(FMOD_SYSTEM *system, int numsoftwarechannels) // 0x10A378E0
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_SetSoftwareChannels@8");
	// __int32 numsoftwarechannels;
	// FMOD_RESULT (*const _FMOD_System_SetSoftwareChannels)(FMOD_SYSTEM *, __int32);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, __int32)
	todo("implement");
	FMOD_RESULT __result = _sub_10A378E0(system, numsoftwarechannels);
	return __result;
}

extern FMOD_RESULT _sub_10A37950(FMOD_SYSTEM *, FMOD_SPEAKERMODE);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_SetSpeakerMode(FMOD_SYSTEM *system, FMOD_SPEAKERMODE speakermode) // 0x10A37950
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_SetSpeakerMode@8");
	// FMOD_SPEAKERMODE speakermode;
	// FMOD_RESULT (*const _FMOD_System_SetSpeakerMode)(FMOD_SYSTEM *, FMOD_SPEAKERMODE);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *, FMOD_SPEAKERMODE)
	todo("implement");
	FMOD_RESULT __result = _sub_10A37950(system, speakermode);
	return __result;
}

extern FMOD_RESULT _sub_10A379C0(FMOD_SYSTEM *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_System_UnlockDSP(FMOD_SYSTEM *system) // 0x10A379C0
{
	mangled_x86(MANGLED_TODO, "_FMOD_System_UnlockDSP@4");
	// FMOD_SYSTEM *system;
	// FMOD_RESULT (*const _FMOD_System_UnlockDSP)(FMOD_SYSTEM *);
	// function call : FMOD_RESULT (*const)(FMOD_SYSTEM *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A379C0(system);
	return __result;
}

extern FMOD_RESULT _sub_10A36DE0(FMOD_SOUND *, float *, float *, float *, int *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Sound_GetDefaults(FMOD_SOUND *sound, float *frequency, float *volume, float *pan, int *priority) // 0x10A36DE0
{
	mangled_x86(MANGLED_TODO, "_FMOD_Sound_GetDefaults@20");
	// __int32 *priority;
	// FMOD_RESULT (*const _FMOD_Sound_GetDefaults)(FMOD_SOUND *, float *, float *, float *, __int32 *);
	// function call : FMOD_RESULT (*const)(FMOD_SOUND *, float *, float *, float *, __int32 *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36DE0(sound, frequency, volume, pan, priority);
	return __result;
}

extern FMOD_RESULT _sub_10A36E60(FMOD_SOUND *, FMOD_SOUND_TYPE *, FMOD_SOUND_FORMAT *, int *, int *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Sound_GetFormat(FMOD_SOUND *sound, FMOD_SOUND_TYPE *type, FMOD_SOUND_FORMAT *format, int *channels, int *bits) // 0x10A36E60
{
	mangled_x86(MANGLED_TODO, "_FMOD_Sound_GetFormat@20");
	// __int32 *bits;
	// FMOD_RESULT (*const _FMOD_Sound_GetFormat)(FMOD_SOUND *, FMOD_SOUND_TYPE *, FMOD_SOUND_FORMAT *, __int32 *, __int32 *);
	// function call : FMOD_RESULT (*const)(FMOD_SOUND *, FMOD_SOUND_TYPE *, FMOD_SOUND_FORMAT *, __int32 *, __int32 *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36E60(sound, type, format, channels, bits);
	return __result;
}

extern FMOD_RESULT _sub_10A36EE0(FMOD_SOUND *, unsigned int *, FMOD_TIMEUNIT);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Sound_GetLength(FMOD_SOUND *sound, unsigned int *length, FMOD_TIMEUNIT lengthtype) // 0x10A36EE0
{
	mangled_x86(MANGLED_TODO, "_FMOD_Sound_GetLength@12");
	// unsigned __int32 lengthtype;
	// FMOD_RESULT (*const _FMOD_Sound_GetLength)(FMOD_SOUND *, unsigned __int32 *, unsigned __int32);
	// function call : FMOD_RESULT (*const)(FMOD_SOUND *, unsigned __int32 *, unsigned __int32)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36EE0(sound, length, lengthtype);
	return __result;
}

extern FMOD_RESULT _sub_10A36F50(FMOD_SOUND *, void **);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Sound_GetUserData(FMOD_SOUND *sound, void **userdata) // 0x10A36F50
{
	mangled_x86(MANGLED_TODO, "_FMOD_Sound_GetUserData@8");
	// void **userdata;
	// FMOD_RESULT (*const _FMOD_Sound_GetUserData)(FMOD_SOUND *, void **);
	// function call : FMOD_RESULT (*const)(FMOD_SOUND *, void **)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36F50(sound, userdata);
	return __result;
}

extern FMOD_RESULT _sub_10A36330(FMOD_CHANNEL *, float *, float *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_Get3DMinMaxDistance(FMOD_CHANNEL *channel, float *mindistance, float *maxdistance) // 0x10A36330
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_Get3DMinMaxDistance@12");
	// float *maxdistance;
	// FMOD_RESULT (*const _FMOD_Channel_Get3DMinMaxDistance)(FMOD_CHANNEL *, float *, float *);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, float *, float *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36330(channel, mindistance, maxdistance);
	return __result;
}

extern FMOD_RESULT _sub_10A363A0(FMOD_CHANNEL *, FMOD_SOUND **);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_GetCurrentSound(FMOD_CHANNEL *channel, FMOD_SOUND **sound) // 0x10A363A0
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_GetCurrentSound@8");
	// FMOD_SOUND **sound;
	// FMOD_RESULT (*const _FMOD_Channel_GetCurrentSound)(FMOD_CHANNEL *, FMOD_SOUND **);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, FMOD_SOUND **)
	todo("implement");
	FMOD_RESULT __result = _sub_10A363A0(channel, sound);
	return __result;
}

extern FMOD_RESULT _sub_10A36410(FMOD_CHANNEL *, FMOD_DELAYTYPE, unsigned int *, unsigned int *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_GetDelay(FMOD_CHANNEL *channel, FMOD_DELAYTYPE delaytype, unsigned int *delayhi, unsigned int *delaylo) // 0x10A36410
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_GetDelay@16");
	// unsigned __int32 *delaylo;
	// FMOD_RESULT (*const _FMOD_Channel_GetDelay)(FMOD_CHANNEL *, FMOD_DELAYTYPE, unsigned __int32 *, unsigned __int32 *);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, FMOD_DELAYTYPE, unsigned __int32 *, unsigned __int32 *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36410(channel, delaytype, delayhi, delaylo);
	return __result;
}

extern FMOD_RESULT _sub_10A36480(FMOD_CHANNEL *, float *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_GetFrequency(FMOD_CHANNEL *channel, float *frequency) // 0x10A36480
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_GetFrequency@8");
	// float *frequency;
	// FMOD_RESULT (*const _FMOD_Channel_GetFrequency)(FMOD_CHANNEL *, float *);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, float *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36480(channel, frequency);
	return __result;
}

extern FMOD_RESULT _sub_10A364F0(FMOD_CHANNEL *, unsigned int *, FMOD_TIMEUNIT);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_GetPosition(FMOD_CHANNEL *channel, unsigned int *position, FMOD_TIMEUNIT postype) // 0x10A364F0
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_GetPosition@12");
	// unsigned __int32 postype;
	// FMOD_RESULT (*const _FMOD_Channel_GetPosition)(FMOD_CHANNEL *, unsigned __int32 *, unsigned __int32);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, unsigned __int32 *, unsigned __int32)
	todo("implement");
	FMOD_RESULT __result = _sub_10A364F0(channel, position, postype);
	return __result;
}

extern FMOD_RESULT _sub_10A36560(FMOD_CHANNEL *, FMOD_BOOL *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_IsPlaying(FMOD_CHANNEL *channel, FMOD_BOOL *isplaying) // 0x10A36560
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_IsPlaying@8");
	// bool *isplaying;
	// FMOD_RESULT (*const _FMOD_Channel_IsPlaying)(FMOD_CHANNEL *, bool *);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, bool *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36560(channel, isplaying);
	return __result;
}

extern FMOD_RESULT _sub_10A365D0(FMOD_CHANNEL *, const FMOD_VECTOR *, const FMOD_VECTOR *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_Set3DAttributes(FMOD_CHANNEL *channel, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel) // 0x10A365D0
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_Set3DAttributes@12");
	// FMOD_VECTOR const *vel;
	// FMOD_RESULT (*const _FMOD_Channel_Set3DAttributes)(FMOD_CHANNEL *, FMOD_VECTOR const *, FMOD_VECTOR const *);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, FMOD_VECTOR const *, FMOD_VECTOR const *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A365D0(channel, pos, vel);
	return __result;
}

extern FMOD_RESULT _sub_10A36640(FMOD_CHANNEL *, FMOD_VECTOR *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_Set3DConeOrientation(FMOD_CHANNEL *channel, FMOD_VECTOR *orientation) // 0x10A36640
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_Set3DConeOrientation@8");
	// FMOD_VECTOR *orientation;
	// FMOD_RESULT (*const _FMOD_Channel_Set3DConeOrientation)(FMOD_CHANNEL *, FMOD_VECTOR *);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, FMOD_VECTOR *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36640(channel, orientation);
	return __result;
}

extern FMOD_RESULT _sub_10A366B0(FMOD_CHANNEL *, float, float, float);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_Set3DConeSettings(FMOD_CHANNEL *channel, float insideconeangle, float outsideconeangle, float outsidevolume) // 0x10A366B0
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_Set3DConeSettings@16");
	// float outsidevolume;
	// FMOD_RESULT (*const _FMOD_Channel_Set3DConeSettings)(FMOD_CHANNEL *, float, float, float);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, float, float, float)
	todo("implement");
	FMOD_RESULT __result = _sub_10A366B0(channel, insideconeangle, outsideconeangle, outsidevolume);
	return __result;
}

extern FMOD_RESULT _sub_10A36740(FMOD_CHANNEL *, float);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_Set3DDopplerLevel(FMOD_CHANNEL *channel, float level) // 0x10A36740
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_Set3DDopplerLevel@8");
	// float level;
	// FMOD_RESULT (*const _FMOD_Channel_Set3DDopplerLevel)(FMOD_CHANNEL *, float);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, float)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36740(channel, level);
	return __result;
}

extern FMOD_RESULT _sub_10A367B0(FMOD_CHANNEL *, float, float);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_Set3DMinMaxDistance(FMOD_CHANNEL *channel, float mindistance, float maxdistance) // 0x10A367B0
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_Set3DMinMaxDistance@12");
	// float maxdistance;
	// FMOD_RESULT (*const _FMOD_Channel_Set3DMinMaxDistance)(FMOD_CHANNEL *, float, float);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, float, float)
	todo("implement");
	FMOD_RESULT __result = _sub_10A367B0(channel, mindistance, maxdistance);
	return __result;
}

extern FMOD_RESULT _sub_10A36830(FMOD_CHANNEL *, float, float);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_Set3DOcclusion(FMOD_CHANNEL *channel, float directocclusion, float reverbocclusion) // 0x10A36830
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_Set3DOcclusion@12");
	// float reverbocclusion;
	// FMOD_RESULT (*const _FMOD_Channel_Set3DOcclusion)(FMOD_CHANNEL *, float, float);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, float, float)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36830(channel, directocclusion, reverbocclusion);
	return __result;
}

extern FMOD_RESULT _sub_10A368B0(FMOD_CHANNEL *, float);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_Set3DSpread(FMOD_CHANNEL *channel, float angle) // 0x10A368B0
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_Set3DSpread@8");
	// float angle;
	// FMOD_RESULT (*const _FMOD_Channel_Set3DSpread)(FMOD_CHANNEL *, float);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, float)
	todo("implement");
	FMOD_RESULT __result = _sub_10A368B0(channel, angle);
	return __result;
}

extern FMOD_RESULT _sub_10A36920(FMOD_CHANNEL *, FMOD_CHANNELGROUP *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_SetChannelGroup(FMOD_CHANNEL *channel, FMOD_CHANNELGROUP *channelgroup) // 0x10A36920
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_SetChannelGroup@8");
	// FMOD_CHANNELGROUP *channelgroup;
	// FMOD_RESULT (*const _FMOD_Channel_SetChannelGroup)(FMOD_CHANNEL *, FMOD_CHANNELGROUP *);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, FMOD_CHANNELGROUP *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36920(channel, channelgroup);
	return __result;
}

extern FMOD_RESULT _sub_10A36990(FMOD_CHANNEL *, FMOD_DELAYTYPE, unsigned int, unsigned int);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_SetDelay(FMOD_CHANNEL *channel, FMOD_DELAYTYPE delaytype, unsigned int delayhi, unsigned int delaylo) // 0x10A36990
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_SetDelay@16");
	// unsigned __int32 delaylo;
	// FMOD_RESULT (*const _FMOD_Channel_SetDelay)(FMOD_CHANNEL *, FMOD_DELAYTYPE, unsigned __int32, unsigned __int32);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, FMOD_DELAYTYPE, unsigned __int32, unsigned __int32)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36990(channel, delaytype, delayhi, delaylo);
	return __result;
}

extern FMOD_RESULT _sub_10A36A00(FMOD_CHANNEL *, float);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_SetFrequency(FMOD_CHANNEL *channel, float frequency) // 0x10A36A00
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_SetFrequency@8");
	// float frequency;
	// FMOD_RESULT (*const _FMOD_Channel_SetFrequency)(FMOD_CHANNEL *, float);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, float)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36A00(channel, frequency);
	return __result;
}

extern FMOD_RESULT _sub_10A36A70(FMOD_CHANNEL *, FMOD_MODE);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_SetMode(FMOD_CHANNEL *channel, FMOD_MODE mode) // 0x10A36A70
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_SetMode@8");
	// unsigned __int32 mode;
	// FMOD_RESULT (*const _FMOD_Channel_SetMode)(FMOD_CHANNEL *, unsigned __int32);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, unsigned __int32)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36A70(channel, mode);
	return __result;
}

extern FMOD_RESULT _sub_10A36AE0(FMOD_CHANNEL *, FMOD_BOOL);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_SetPaused(FMOD_CHANNEL *channel, FMOD_BOOL paused) // 0x10A36AE0
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_SetPaused@8");
	// bool paused;
	// FMOD_RESULT (*const _FMOD_Channel_SetPaused)(FMOD_CHANNEL *, bool);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, bool)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36AE0(channel, paused);
	return __result;
}

extern FMOD_RESULT _sub_10A36B50(FMOD_CHANNEL *, unsigned int, FMOD_TIMEUNIT);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_SetPosition(FMOD_CHANNEL *channel, unsigned int position, FMOD_TIMEUNIT postype) // 0x10A36B50
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_SetPosition@12");
	// unsigned __int32 postype;
	// FMOD_RESULT (*const _FMOD_Channel_SetPosition)(FMOD_CHANNEL *, unsigned __int32, unsigned __int32);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, unsigned __int32, unsigned __int32)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36B50(channel, position, postype);
	return __result;
}

extern FMOD_RESULT _sub_10A36BC0(FMOD_CHANNEL *, const FMOD_REVERB_CHANNELPROPERTIES *);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_SetReverbProperties(FMOD_CHANNEL *channel, const FMOD_REVERB_CHANNELPROPERTIES *prop) // 0x10A36BC0
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_SetReverbProperties@8");
	// FMOD_REVERB_CHANNELPROPERTIES const *prop;
	// FMOD_RESULT (*const _FMOD_Channel_SetReverbProperties)(FMOD_CHANNEL *, FMOD_REVERB_CHANNELPROPERTIES const *);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, FMOD_REVERB_CHANNELPROPERTIES const *)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36BC0(channel, prop);
	return __result;
}

extern FMOD_RESULT _sub_10A36C30(FMOD_CHANNEL *, FMOD_SPEAKER, float *, int);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_SetSpeakerLevels(FMOD_CHANNEL *channel, FMOD_SPEAKER speaker, float *levels, int numlevels) // 0x10A36C30
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_SetSpeakerLevels@16");
	// __int32 numlevels;
	// FMOD_RESULT (*const _FMOD_Channel_SetSpeakerLevels)(FMOD_CHANNEL *, FMOD_SPEAKER, float *, __int32);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, FMOD_SPEAKER, float *, __int32)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36C30(channel, speaker, levels, numlevels);
	return __result;
}

extern FMOD_RESULT _sub_10A36CA0(FMOD_CHANNEL *, float, float, float, float, float, float, float, float);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_SetSpeakerMix(FMOD_CHANNEL *channel, float frontleft, float frontright, float center, float lfe, float backleft, float backright, float sideleft, float sideright) // 0x10A36CA0
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_SetSpeakerMix@36");
	// float sideright;
	// FMOD_RESULT (*const _FMOD_Channel_SetSpeakerMix)(FMOD_CHANNEL *, float, float, float, float, float, float, float, float);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, float, float, float, float, float, float, float, float)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36CA0(channel, frontleft, frontright, center, lfe, backleft, backright, sideleft, sideright);
	return __result;
}

extern FMOD_RESULT _sub_10A36D70(FMOD_CHANNEL *, float);
extern "C" _inline FMOD_RESULT __stdcall FMOD_Channel_SetVolume(FMOD_CHANNEL *channel, float volume) // 0x10A36D70
{
	mangled_x86(MANGLED_TODO, "_FMOD_Channel_SetVolume@8");
	// float volume;
	// FMOD_RESULT (*const _FMOD_Channel_SetVolume)(FMOD_CHANNEL *, float);
	// function call : FMOD_RESULT (*const)(FMOD_CHANNEL *, float)
	todo("implement");
	FMOD_RESULT __result = _sub_10A36D70(channel, volume);
	return __result;
}

/* ---------- private code */

#endif // __BLAM_FMOD_FMOD_FUNCTIONS_INL__
