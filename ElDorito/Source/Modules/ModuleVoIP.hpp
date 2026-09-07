#ifndef __MODULES_MODULEVOIP_HPP__
#define __MODULES_MODULEVOIP_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"

/* ---------- forward declarations */

namespace Modules
{
	class ModuleBase;
	class ModuleVoIP;
	struct Command;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Modules
{
	class ModuleVoIP :
		public Utils::Singleton<Modules::ModuleVoIP>,
		public Modules::ModuleBase
	{
	public:
		Modules::Command *VarVoipEnabled; // 0x1C
		Modules::Command *VarPTTEnabled; // 0x20
		Modules::Command *VarPTT; // 0x24
		Modules::Command *VarMicrophone; // 0x28
		Modules::Command *VarEchoCancellation; // 0x2C
		Modules::Command *VarAGC; // 0x30
		Modules::Command *VarNoiseSupress; // 0x34
		Modules::Command *VarPTTSoundEnabled; // 0x38
		Modules::Command *VarSpeakingPlayerOnHUD; // 0x3C
		Modules::Command *VarIncomingVolume; // 0x40
		Modules::Command *VarStatsEnabled; // 0x44
		Modules::Command *VarOutgoingVolume; // 0x48
		Modules::Command *VarListenToMicrophone; // 0x4C
		Modules::Command *VarMaximumBitrate; // 0x50
		bool voipConnected; // 0x54
		bool voiceDetected; // 0x55
		unsigned short playersSpeaking; // 0x56
		unsigned short playersSpoke; // 0x58
		unsigned short playersMuted; // 0x5A
		ModuleVoIP();
		bool IsChatting();
		void Tick();
		~ModuleVoIP(); /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Modules::ModuleVoIP) == 92, "Invalid Modules::ModuleVoIP size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODULES_MODULEVOIP_HPP__
