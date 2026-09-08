#ifndef __MODULES_MODULEGAME_HPP__
#define __MODULES_MODULEGAME_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"

#include <memory>
#include <string>
#include <vector>

/* ---------- forward declarations */

namespace Modules
{
	class ModuleBase;
	class ModuleGame;
	struct Command;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Modules
{
	class ModuleGame :
		public Utils::Singleton<Modules::ModuleGame>,
		public Modules::ModuleBase
	{
	public:
		Modules::Command *VarLanguage; // 0x1C
		Modules::Command *VarSkipTitleSplash; // 0x20
		Modules::Command *VarSkipIntroVideos; // 0x24
		Modules::Command *VarLogName; // 0x28
		Modules::Command *VarMenuURL; // 0x2C
		Modules::Command *VarConsoleURL; // 0x30
		Modules::Command *VarChatURL; // 0x34
		Modules::Command *VarLoadingURL; // 0x38
		Modules::Command *VarVotingURL; // 0x3C
		Modules::Command *VarTitleURL; // 0x40
		Modules::Command *VarScoreboardURL; // 0x44
		Modules::Command *VarDialogURL; // 0x48
		Modules::Command *VarSettingsURL; // 0x4C
		Modules::Command *VarProfileSettingsURL; // 0x50
		Modules::Command *VarServerSettingsURL; // 0x54
		Modules::Command *VarForgeObjectPropertiesURL; // 0x58
		Modules::Command *VarForgeObjectCreationURL; // 0x5C
		Modules::Command *VarVoipURL; // 0x60
		Modules::Command *VarWeaponOffsetURL; // 0x64
		Modules::Command *VarScreenshotNoticeURL; // 0x68
		Modules::Command *VarDiscordURL; // 0x6C
		Modules::Command *VarPlayerReportURL; // 0x70
		Modules::Command *VarInGameVotingURL; // 0x74
		Modules::Command *VarEmoteScreenURL; // 0x78
		Modules::Command *VarCEFGpuEnable; // 0x7C
		Modules::Command *VarCEFAtlasRendererEnable; // 0x80
		Modules::Command *VarRconPort; // 0x84
		Modules::Command *VarFirstRun; // 0x88
		Modules::Command *VarExpandedScoreboard; // 0x8C
		Modules::Command *VarHideChat; // 0x90
		Modules::Command *VarChatMessageLimit; // 0x94
		Modules::Command *VarHideH3UI; // 0x98
		Modules::Command *VarFullscreenBlur; // 0x9C
		Modules::Command *VarFullscreenBlurTime; // 0xA0
		Modules::Command *VarScreenshotsFolder; // 0xA4
		Modules::Command *VarScreenshotNoticeDisabled; // 0xA8
		Modules::Command *VarDiscordEnable; // 0xAC
		Modules::Command *VarDiscordAutoAccept; // 0xB0
		Modules::Command *VarMainMenuMod; // 0xB4
		Modules::Command *VarCampaignMod; // 0xB8
		Modules::Command *VarFirefightMod; // 0xBC
		Modules::Command *VarMultiplayerMod; // 0xC0
		Modules::Command *VarTickRate; // 0xC4
		Modules::Command *VarTickRateClient; // 0xC8
		std::vector<std::string> FiltersExclude; // 0xCC
		std::vector<std::string> FiltersInclude; // 0xDC
		ModuleGame();
		~ModuleGame(); /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Modules::ModuleGame) == 236, "Invalid Modules::ModuleGame size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODULES_MODULEGAME_HPP__
