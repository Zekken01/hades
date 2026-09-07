#ifndef __PATCHES_AUDIO_HPP__
#define __PATCHES_AUDIO_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

namespace Patches
{
	namespace Audio
	{
		struct SAudioDeviceInfo;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Patches
{
	namespace Audio
	{
		struct SAudioDeviceInfo
		{
			char name[512]; // 0x0
		};
		static_assert(sizeof(Patches::Audio::SAudioDeviceInfo) == 512, "Invalid Patches::Audio::SAudioDeviceInfo size");
	}
}

/* ---------- prototypes */

namespace Patches
{
	namespace Audio
	{
		extern void ApplyAll();
		extern void ApplyAfterInit();
		extern bool SetOutputDevice(__int32 deviceIndex);
		extern bool GetDeviceInfo(__int32 deviceIndex, Patches::Audio::SAudioDeviceInfo *outInfo);
		extern __int32 GetDeviceCount();
		extern void Tick();
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __PATCHES_AUDIO_HPP__
