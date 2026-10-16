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

extern "C" inline FMOD_RESULT __stdcall FMOD_System_CreateCodec(FMOD_SYSTEM *system, FMOD_CODEC_DESCRIPTION *description, unsigned int priority) // 0x106CBEA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_CreateCodec@12");

	FMOD_RESULT (__stdcall *const _FMOD_System_CreateCodec)(FMOD_SYSTEM *, FMOD_CODEC_DESCRIPTION *, unsigned __int32) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, FMOD_CODEC_DESCRIPTION *, unsigned __int32))0x138798F;
	return _FMOD_System_CreateCodec(system, description, priority);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_CreateSound(FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound) // 0x106CBF10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_CreateSound@20");

	FMOD_RESULT (__stdcall *const _FMOD_System_CreateSound)(FMOD_SYSTEM *, char const *, unsigned __int32, FMOD_CREATESOUNDEXINFO *, FMOD_SOUND **) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, char const *, unsigned __int32, FMOD_CREATESOUNDEXINFO *, FMOD_SOUND **))0x1387A7F;
	return _FMOD_System_CreateSound(system, name_or_data, mode, exinfo, sound);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_CreateStream(FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound) // 0x10A36FC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_CreateStream@20");

	FMOD_RESULT (__stdcall *const _FMOD_System_CreateStream)(FMOD_SYSTEM *, char const *, unsigned __int32, FMOD_CREATESOUNDEXINFO *, FMOD_SOUND **) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, char const *, unsigned __int32, FMOD_CREATESOUNDEXINFO *, FMOD_SOUND **))0x1387AD5;
	return _FMOD_System_CreateStream(system, name_or_data, mode, exinfo, sound);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_Get3DNumListeners(FMOD_SYSTEM *system, int *numlisteners) // 0x10A37040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_Get3DNumListeners@8");

	FMOD_RESULT (__stdcall *const _FMOD_System_Get3DNumListeners)(FMOD_SYSTEM *, __int32 *) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, __int32 *))0x1387B34;
	return _FMOD_System_Get3DNumListeners(system, numlisteners);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_GetAdvancedSettings(FMOD_SYSTEM *system, FMOD_ADVANCEDSETTINGS *settings) // 0x10A370B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_GetAdvancedSettings@8");

	FMOD_RESULT (__stdcall *const _FMOD_System_GetAdvancedSettings)(FMOD_SYSTEM *, FMOD_ADVANCEDSETTINGS *) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, FMOD_ADVANCEDSETTINGS *))0x1387BB2;
	return _FMOD_System_GetAdvancedSettings(system, settings);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_GetCPUUsage(FMOD_SYSTEM *system, float *dsp, float *stream, float *geometry, float *update, float *total) // 0x10A37120
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_GetCPUUsage@24");

	FMOD_RESULT (__stdcall *const _FMOD_System_GetCPUUsage)(FMOD_SYSTEM *, float *, float *, float *, float *, float *) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, float *, float *, float *, float *, float *))0x1387C8A;
	return _FMOD_System_GetCPUUsage(system, dsp, stream, geometry, update, total);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_GetChannelsPlaying(FMOD_SYSTEM *system, int *channels) // 0x10A371A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_GetChannelsPlaying@8");

	FMOD_RESULT (__stdcall *const _FMOD_System_GetChannelsPlaying)(FMOD_SYSTEM *, __int32 *) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, __int32 *))0x1387CE3;
	return _FMOD_System_GetChannelsPlaying(system, channels);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_GetDSPClock(FMOD_SYSTEM *system, unsigned int *hi, unsigned int *lo) // 0x10A37210
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_GetDSPClock@12");

	FMOD_RESULT (__stdcall *const _FMOD_System_GetDSPClock)(FMOD_SYSTEM *, unsigned __int32 *, unsigned __int32 *) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, unsigned __int32 *, unsigned __int32 *))0x1387D30;
	return _FMOD_System_GetDSPClock(system, hi, lo);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_GetDriverCaps(FMOD_SYSTEM *system, int id, FMOD_CAPS *caps, int *minfrequency, int *maxfrequency, FMOD_SPEAKERMODE *controlpanelspeakermode) // 0x10A37280
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_GetDriverCaps@24");

	FMOD_RESULT (__stdcall *const _FMOD_System_GetDriverCaps)(FMOD_SYSTEM *, __int32, unsigned __int32 *, __int32 *, __int32 *, FMOD_SPEAKERMODE *) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, __int32, unsigned __int32 *, __int32 *, __int32 *, FMOD_SPEAKERMODE *))0x1387DA2;
	return _FMOD_System_GetDriverCaps(system, id, caps, minfrequency, maxfrequency, controlpanelspeakermode);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_GetDriverInfo(FMOD_SYSTEM *system, int id, char *name, int namelen, FMOD_GUID *guid) // 0x10A37300
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_GetDriverInfo@20");

	FMOD_RESULT (__stdcall *const _FMOD_System_GetDriverInfo)(FMOD_SYSTEM *, __int32, char *, __int32, FMOD_GUID *) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, __int32, char *, __int32, FMOD_GUID *))0x1387DD3;
	return _FMOD_System_GetDriverInfo(system, id, name, namelen, guid);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_GetMemoryInfo(FMOD_SYSTEM *system, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, unsigned int *memoryused_array) // 0x10A37380
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_GetMemoryInfo@20");

	FMOD_RESULT (__stdcall *const _FMOD_System_GetMemoryInfo)(FMOD_SYSTEM *, unsigned __int32, unsigned __int32, unsigned __int32 *, unsigned __int32 *) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, unsigned __int32, unsigned __int32, unsigned __int32 *, unsigned __int32 *))0x1387EC9;
	return _FMOD_System_GetMemoryInfo(system, memorybits, event_memorybits, memoryused, memoryused_array);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_GetNumDrivers(FMOD_SYSTEM *system, int *numdrivers) // 0x10A37400
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_GetNumDrivers@8");

	FMOD_RESULT (__stdcall *const _FMOD_System_GetNumDrivers)(FMOD_SYSTEM *, __int32 *) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, __int32 *))0x1387F69;
	return _FMOD_System_GetNumDrivers(system, numdrivers);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_GetOutput(FMOD_SYSTEM *system, FMOD_OUTPUTTYPE *output) // 0x10A37470
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_GetOutput@8");

	FMOD_RESULT (__stdcall *const _FMOD_System_GetOutput)(FMOD_SYSTEM *, FMOD_OUTPUTTYPE *) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, FMOD_OUTPUTTYPE *))0x1387FB6;
	return _FMOD_System_GetOutput(system, output);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_GetSoftwareChannels(FMOD_SYSTEM *system, int *numsoftwarechannels) // 0x10A374E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_GetSoftwareChannels@8");

	FMOD_RESULT (__stdcall *const _FMOD_System_GetSoftwareChannels)(FMOD_SYSTEM *, __int32 *) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, __int32 *))0x1388174;
	return _FMOD_System_GetSoftwareChannels(system, numsoftwarechannels);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_GetVersion(FMOD_SYSTEM *system, unsigned int *version) // 0x10A37550
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_GetVersion@8");

	FMOD_RESULT (__stdcall *const _FMOD_System_GetVersion)(FMOD_SYSTEM *, unsigned __int32 *) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, unsigned __int32 *))0x1388371;
	return _FMOD_System_GetVersion(system, version);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_LockDSP(FMOD_SYSTEM *system) // 0x10A375C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_LockDSP@4");

	FMOD_RESULT (__stdcall *const _FMOD_System_LockDSP)(FMOD_SYSTEM *) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *))0x138846A;
	return _FMOD_System_LockDSP(system);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_PlaySound(FMOD_SYSTEM *system, FMOD_CHANNELINDEX channelid, FMOD_SOUND *sound, FMOD_BOOL paused, FMOD_CHANNEL **channel) // 0x10A37620
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_PlaySound@20");

	FMOD_RESULT (__stdcall *const _FMOD_System_PlaySound)(FMOD_SYSTEM *, FMOD_CHANNELINDEX, FMOD_SOUND *, bool, FMOD_CHANNEL **) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, FMOD_CHANNELINDEX, FMOD_SOUND *, bool, FMOD_CHANNEL **))0x13884BA;
	return _FMOD_System_PlaySound(system, channelid, sound, *(bool *)&paused, channel);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_SetAdvancedSettings(FMOD_SYSTEM *system, FMOD_ADVANCEDSETTINGS *settings) // 0x10A376A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_SetAdvancedSettings@8");

	FMOD_RESULT (__stdcall *const _FMOD_System_SetAdvancedSettings)(FMOD_SYSTEM *, FMOD_ADVANCEDSETTINGS *) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, FMOD_ADVANCEDSETTINGS *))0x1388659;
	return _FMOD_System_SetAdvancedSettings(system, settings);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_SetDSPBufferSize(FMOD_SYSTEM *system, unsigned int bufferlength, int numbuffers) // 0x10A37710
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_SetDSPBufferSize@12");

	FMOD_RESULT (__stdcall *const _FMOD_System_SetDSPBufferSize)(FMOD_SYSTEM *, unsigned __int32, __int32) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, unsigned __int32, __int32))0x13886A3;
	return _FMOD_System_SetDSPBufferSize(system, bufferlength, numbuffers);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_SetDriver(FMOD_SYSTEM *system, int driver) // 0x10A37780
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_SetDriver@8");

	FMOD_RESULT (__stdcall *const _FMOD_System_SetDriver)(FMOD_SYSTEM *, __int32) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, __int32))0x13886CB;
	return _FMOD_System_SetDriver(system, driver);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_SetHardwareChannels(FMOD_SYSTEM *system, int min2d, int max2d, int min3d, int max3d) // 0x10A377F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_SetHardwareChannels@20");

	FMOD_RESULT (__stdcall *const _FMOD_System_SetHardwareChannels)(FMOD_SYSTEM *, __int32, __int32, __int32, __int32) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, __int32, __int32, __int32, __int32))0x138874E;
	return _FMOD_System_SetHardwareChannels(system, min2d, max2d, min3d, max3d);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_SetOutput(FMOD_SYSTEM *system, FMOD_OUTPUTTYPE output) // 0x10A37870
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_SetOutput@8");

	FMOD_RESULT (__stdcall *const _FMOD_System_SetOutput)(FMOD_SYSTEM *, FMOD_OUTPUTTYPE) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, FMOD_OUTPUTTYPE))0x13887C6;
	return _FMOD_System_SetOutput(system, output);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_SetSoftwareChannels(FMOD_SYSTEM *system, int numsoftwarechannels) // 0x10A378E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_SetSoftwareChannels@8");

	FMOD_RESULT (__stdcall *const _FMOD_System_SetSoftwareChannels)(FMOD_SYSTEM *, __int32) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, __int32))0x1388880;
	return _FMOD_System_SetSoftwareChannels(system, numsoftwarechannels);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_SetSpeakerMode(FMOD_SYSTEM *system, FMOD_SPEAKERMODE speakermode) // 0x10A37950
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_SetSpeakerMode@8");

	FMOD_RESULT (__stdcall *const _FMOD_System_SetSpeakerMode)(FMOD_SYSTEM *, FMOD_SPEAKERMODE) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *, FMOD_SPEAKERMODE))0x13888D6;
	return _FMOD_System_SetSpeakerMode(system, speakermode);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_System_UnlockDSP(FMOD_SYSTEM *system) // 0x10A379C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_System_UnlockDSP@4");

	FMOD_RESULT (__stdcall *const _FMOD_System_UnlockDSP)(FMOD_SYSTEM *) = (FMOD_RESULT (__stdcall *)(FMOD_SYSTEM *))0x138896D;
	return _FMOD_System_UnlockDSP(system);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Sound_GetDefaults(FMOD_SOUND *sound, float *frequency, float *volume, float *pan, int *priority) // 0x10A36DE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Sound_GetDefaults@20");

	FMOD_RESULT (__stdcall *const _FMOD_Sound_GetDefaults)(FMOD_SOUND *, float *, float *, float *, __int32 *) = (FMOD_RESULT (__stdcall *)(FMOD_SOUND *, float *, float *, float *, __int32 *))0x1388AED;
	return _FMOD_Sound_GetDefaults(sound, frequency, volume, pan, priority);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Sound_GetFormat(FMOD_SOUND *sound, FMOD_SOUND_TYPE *type, FMOD_SOUND_FORMAT *format, int *channels, int *bits) // 0x10A36E60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Sound_GetFormat@20");

	FMOD_RESULT (__stdcall *const _FMOD_Sound_GetFormat)(FMOD_SOUND *, FMOD_SOUND_TYPE *, FMOD_SOUND_FORMAT *, __int32 *, __int32 *) = (FMOD_RESULT (__stdcall *)(FMOD_SOUND *, FMOD_SOUND_TYPE *, FMOD_SOUND_FORMAT *, __int32 *, __int32 *))0x1388B2F;
	return _FMOD_Sound_GetFormat(sound, type, format, channels, bits);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Sound_GetLength(FMOD_SOUND *sound, unsigned int *length, FMOD_TIMEUNIT lengthtype) // 0x10A36EE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Sound_GetLength@12");

	FMOD_RESULT (__stdcall *const _FMOD_Sound_GetLength)(FMOD_SOUND *, unsigned __int32 *, unsigned __int32) = (FMOD_RESULT (__stdcall *)(FMOD_SOUND *, unsigned __int32 *, unsigned __int32))0x1388B71;
	return _FMOD_Sound_GetLength(sound, length, lengthtype);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Sound_GetUserData(FMOD_SOUND *sound, void **userdata) // 0x10A36F50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Sound_GetUserData@8");

	FMOD_RESULT (__stdcall *const _FMOD_Sound_GetUserData)(FMOD_SOUND *, void **) = (FMOD_RESULT (__stdcall *)(FMOD_SOUND *, void **))0x1388FA5;
	return _FMOD_Sound_GetUserData(sound, userdata);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_Get3DMinMaxDistance(FMOD_CHANNEL *channel, float *mindistance, float *maxdistance) // 0x10A36330
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_Get3DMinMaxDistance@12");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_Get3DMinMaxDistance)(FMOD_CHANNEL *, float *, float *) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, float *, float *))0x1389655;
	return _FMOD_Channel_Get3DMinMaxDistance(channel, mindistance, maxdistance);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_GetCurrentSound(FMOD_CHANNEL *channel, FMOD_SOUND **sound) // 0x10A363A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_GetCurrentSound@8");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_GetCurrentSound)(FMOD_CHANNEL *, FMOD_SOUND **) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, FMOD_SOUND **))0x1389791;
	return _FMOD_Channel_GetCurrentSound(channel, sound);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_GetDelay(FMOD_CHANNEL *channel, FMOD_DELAYTYPE delaytype, unsigned int *delayhi, unsigned int *delaylo) // 0x10A36410
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_GetDelay@16");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_GetDelay)(FMOD_CHANNEL *, FMOD_DELAYTYPE, unsigned __int32 *, unsigned __int32 *) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, FMOD_DELAYTYPE, unsigned __int32 *, unsigned __int32 *))0x13897EF;
	return _FMOD_Channel_GetDelay(channel, delaytype, delayhi, delaylo);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_GetFrequency(FMOD_CHANNEL *channel, float *frequency) // 0x10A36480
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_GetFrequency@8");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_GetFrequency)(FMOD_CHANNEL *, float *) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, float *))0x1389832;
	return _FMOD_Channel_GetFrequency(channel, frequency);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_GetPosition(FMOD_CHANNEL *channel, unsigned int *position, FMOD_TIMEUNIT postype) // 0x10A364F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_GetPosition@12");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_GetPosition)(FMOD_CHANNEL *, unsigned __int32 *, unsigned __int32) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, unsigned __int32 *, unsigned __int32))0x1389A68;
	return _FMOD_Channel_GetPosition(channel, position, postype);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_IsPlaying(FMOD_CHANNEL *channel, FMOD_BOOL *isplaying) // 0x10A36560
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_IsPlaying@8");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_IsPlaying)(FMOD_CHANNEL *, bool *) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, bool *))0x1389CA9;
	return _FMOD_Channel_IsPlaying(channel, (bool *)isplaying);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_Set3DAttributes(FMOD_CHANNEL *channel, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel) // 0x10A365D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_Set3DAttributes@12");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_Set3DAttributes)(FMOD_CHANNEL *, FMOD_VECTOR const *, FMOD_VECTOR const *) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, FMOD_VECTOR const *, FMOD_VECTOR const *))0x1389D07;
	return _FMOD_Channel_Set3DAttributes(channel, pos, vel);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_Set3DConeOrientation(FMOD_CHANNEL *channel, FMOD_VECTOR *orientation) // 0x10A36640
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_Set3DConeOrientation@8");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_Set3DConeOrientation)(FMOD_CHANNEL *, FMOD_VECTOR *) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, FMOD_VECTOR *))0x1389D2D;
	return _FMOD_Channel_Set3DConeOrientation(channel, orientation);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_Set3DConeSettings(FMOD_CHANNEL *channel, float insideconeangle, float outsideconeangle, float outsidevolume) // 0x10A366B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_Set3DConeSettings@16");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_Set3DConeSettings)(FMOD_CHANNEL *, float, float, float) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, float, float, float))0x1389D50;
	return _FMOD_Channel_Set3DConeSettings(channel, insideconeangle, outsideconeangle, outsidevolume);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_Set3DDopplerLevel(FMOD_CHANNEL *channel, float level) // 0x10A36740
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_Set3DDopplerLevel@8");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_Set3DDopplerLevel)(FMOD_CHANNEL *, float) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, float))0x1389DB9;
	return _FMOD_Channel_Set3DDopplerLevel(channel, level);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_Set3DMinMaxDistance(FMOD_CHANNEL *channel, float mindistance, float maxdistance) // 0x10A367B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_Set3DMinMaxDistance@12");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_Set3DMinMaxDistance)(FMOD_CHANNEL *, float, float) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, float, float))0x1389DE4;
	return _FMOD_Channel_Set3DMinMaxDistance(channel, mindistance, maxdistance);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_Set3DOcclusion(FMOD_CHANNEL *channel, float directocclusion, float reverbocclusion) // 0x10A36830
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_Set3DOcclusion@12");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_Set3DOcclusion)(FMOD_CHANNEL *, float, float) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, float, float))0x1389E1B;
	return _FMOD_Channel_Set3DOcclusion(channel, directocclusion, reverbocclusion);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_Set3DSpread(FMOD_CHANNEL *channel, float angle) // 0x10A368B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_Set3DSpread@8");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_Set3DSpread)(FMOD_CHANNEL *, float) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, float))0x1389E7D;
	return _FMOD_Channel_Set3DSpread(channel, angle);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_SetChannelGroup(FMOD_CHANNEL *channel, FMOD_CHANNELGROUP *channelgroup) // 0x10A36920
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_SetChannelGroup@8");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_SetChannelGroup)(FMOD_CHANNEL *, FMOD_CHANNELGROUP *) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, FMOD_CHANNELGROUP *))0x1389ECB;
	return _FMOD_Channel_SetChannelGroup(channel, channelgroup);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_SetDelay(FMOD_CHANNEL *channel, FMOD_DELAYTYPE delaytype, unsigned int delayhi, unsigned int delaylo) // 0x10A36990
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_SetDelay@16");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_SetDelay)(FMOD_CHANNEL *, FMOD_DELAYTYPE, unsigned __int32, unsigned __int32) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, FMOD_DELAYTYPE, unsigned __int32, unsigned __int32))0x1389EEE;
	return _FMOD_Channel_SetDelay(channel, delaytype, delayhi, delaylo);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_SetFrequency(FMOD_CHANNEL *channel, float frequency) // 0x10A36A00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_SetFrequency@8");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_SetFrequency)(FMOD_CHANNEL *, float) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, float))0x1389F17;
	return _FMOD_Channel_SetFrequency(channel, frequency);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_SetMode(FMOD_CHANNEL *channel, FMOD_MODE mode) // 0x10A36A70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_SetMode@8");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_SetMode)(FMOD_CHANNEL *, unsigned __int32) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, unsigned __int32))0x1389FE2;
	return _FMOD_Channel_SetMode(channel, mode);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_SetPaused(FMOD_CHANNEL *channel, FMOD_BOOL paused) // 0x10A36AE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_SetPaused@8");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_SetPaused)(FMOD_CHANNEL *, bool) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, bool))0x138A055;
	return _FMOD_Channel_SetPaused(channel, *(bool *)&paused);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_SetPosition(FMOD_CHANNEL *channel, unsigned int position, FMOD_TIMEUNIT postype) // 0x10A36B50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_SetPosition@12");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_SetPosition)(FMOD_CHANNEL *, unsigned __int32, unsigned __int32) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, unsigned __int32, unsigned __int32))0x138A078;
	return _FMOD_Channel_SetPosition(channel, position, postype);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_SetReverbProperties(FMOD_CHANNEL *channel, const FMOD_REVERB_CHANNELPROPERTIES *prop) // 0x10A36BC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_SetReverbProperties@8");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_SetReverbProperties)(FMOD_CHANNEL *, FMOD_REVERB_CHANNELPROPERTIES const *) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, FMOD_REVERB_CHANNELPROPERTIES const *))0x138A0C1;
	return _FMOD_Channel_SetReverbProperties(channel, prop);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_SetSpeakerLevels(FMOD_CHANNEL *channel, FMOD_SPEAKER speaker, float *levels, int numlevels) // 0x10A36C30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_SetSpeakerLevels@16");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_SetSpeakerLevels)(FMOD_CHANNEL *, FMOD_SPEAKER, float *, __int32) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, FMOD_SPEAKER, float *, __int32))0x138A0E4;
	return _FMOD_Channel_SetSpeakerLevels(channel, speaker, levels, numlevels);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_SetSpeakerMix(FMOD_CHANNEL *channel, float frontleft, float frontright, float center, float lfe, float backleft, float backright, float sideleft, float sideright) // 0x10A36CA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_SetSpeakerMix@36");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_SetSpeakerMix)(FMOD_CHANNEL *, float, float, float, float, float, float, float, float) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, float, float, float, float, float, float, float, float))0x138A10F;
	return _FMOD_Channel_SetSpeakerMix(channel, frontleft, frontright, center, lfe, backleft, backright, sideleft, sideright);
}

extern "C" inline FMOD_RESULT __stdcall FMOD_Channel_SetVolume(FMOD_CHANNEL *channel, float volume) // 0x10A36D70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FMOD_Channel_SetVolume@8");

	FMOD_RESULT (__stdcall *const _FMOD_Channel_SetVolume)(FMOD_CHANNEL *, float) = (FMOD_RESULT (__stdcall *)(FMOD_CHANNEL *, float))0x138A1AE;
	return _FMOD_Channel_SetVolume(channel, volume);
}

/* ---------- private code */

#endif // __BLAM_FMOD_FMOD_FUNCTIONS_INL__
