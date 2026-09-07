#ifndef __MODULES_MODULESERVER_HPP__
#define __MODULES_MODULESERVER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "CommandMap.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Utils/StlUtil.hpp"

#include <functional>
#include <memory>
#include <string>
#include <unordered_set>

/* ---------- forward declarations */

namespace Modules
{
	class ModuleBase;
	class ModuleServer;
	struct Command;
}

/* ---------- constants */

/* ---------- definitions */

namespace Modules
{
	class ModuleServer :
		public Utils::Singleton<Modules::ModuleServer>,
		public Modules::ModuleBase
	{
	public:
		Modules::Command *VarHitMarkersEnabled; // 0x1C
		Modules::Command *VarHitMarkersEnabledClient; // 0x20
		Modules::Command *VarServerName; // 0x24
		Modules::Command *VarServerNameClient; // 0x28
		Modules::Command *VarServerHost; // 0x2C
		Modules::Command *VarServerHostClient; // 0x30
		Modules::Command *VarServerMessage; // 0x34
		Modules::Command *VarServerMessageClient; // 0x38
		Modules::Command *VarServerPassword; // 0x3C
		Modules::Command *VarShouldSubmitStats; // 0x40
		Modules::Command *VarServerCountdown; // 0x44
		Modules::Command *VarServerCountdownClient; // 0x48
		Modules::Command *VarShowDisconnectedPlayers; // 0x4C
		Modules::Command *VarShowDisconnectedPlayersClient; // 0x50
		Modules::Command *VarServerCountdownLobby; // 0x54
		Modules::Command *VarServerMaxPlayers; // 0x58
		Modules::Command *VarServerPort; // 0x5C
		Modules::Command *VarServerGamePort; // 0x60
		Modules::Command *VarFileServerPort; // 0x64
		Modules::Command *VarFileServerEnabled; // 0x68
		Modules::Command *VarServerShouldAnnounce; // 0x6C
		Modules::Command *VarServerSprintState; // 0x70
		Modules::Command *VarServerSprintStateClient; // 0x74
		Modules::Command *VarServerBottomlessClipEnabled; // 0x78
		Modules::Command *VarServerBottomlessClipEnabledClient; // 0x7C
		Modules::Command *VarServerSprintUnlimited; // 0x80
		Modules::Command *VarServerSprintUnlimitedClient; // 0x84
		Modules::Command *VarServerMuteSoundsDuringPostGame; // 0x88
		Modules::Command *VarServerMuteSoundsDuringPostGameClient; // 0x8C
		Modules::Command *VarServerDualWieldEnabled; // 0x90
		Modules::Command *VarServerDualWieldEnabledClient; // 0x94
		Modules::Command *VarServerFallDamageMPEnabled; // 0x98
		Modules::Command *VarServerFallDamageMPEnabledClient; // 0x9C
		Modules::Command *VarServerDedicated; // 0xA0
		Modules::Command *VarServerDedicatedClient; // 0xA4
		Modules::Command *VarServerAssassinationEnabled; // 0xA8
		Modules::Command *VarServerAssassinationEnabledClient; // 0xAC
		Modules::Command *VarFloodFilterEnabled; // 0xB0
		Modules::Command *VarFloodMessageScoreShort; // 0xB4
		Modules::Command *VarFloodMessageScoreLong; // 0xB8
		Modules::Command *VarFloodTimeoutScore; // 0xBC
		Modules::Command *VarFloodTimeoutSeconds; // 0xC0
		Modules::Command *VarFloodTimeoutResetSeconds; // 0xC4
		Modules::Command *VarChatLogEnabled; // 0xC8
		Modules::Command *VarListPlayersLogEnabled; // 0xCC
		Modules::Command *VarListPlayersLogFile; // 0xD0
		Modules::Command *VarChatLogFile; // 0xD4
		Modules::Command *VarModsJsonFile; // 0xD8
		Modules::Command *VarHUDWaypointStyle; // 0xDC
		Modules::Command *VarHUDWaypointStyleClient; // 0xE0
		Modules::Command *VarServerKillCommandEnabled; // 0xE4
		Modules::Command *VarKillCommandMessage; // 0xE8
		Modules::Command *VarServerEmotesEnabled; // 0xEC
		Modules::Command *VarServerEmotesEnabledClient; // 0xF0
		Modules::Command *VarServerEmotesDuringPodiumEnabled; // 0xF4
		Modules::Command *VarServerEmotesDuringPodiumEnabledClient; // 0xF8
		Modules::Command *VarServerPostMatchMusicEnabled; // 0xFC
		Modules::Command *VarServerPostMatchMusicEnabledClient; // 0x100
		Modules::Command *VarServerNearVictoryMusicEnabled; // 0x104
		Modules::Command *VarServerNearVictoryMusicEnabledClient; // 0x108
		Modules::Command *VarServerNearVictoryMusicPercent; // 0x10C
		Modules::Command *VarServerNearVictoryMusicPercentClient; // 0x110
		Modules::Command *VarRconPassword; // 0x114
		Modules::Command *VarRconLogFile; // 0x118
		Modules::Command *VarRconLogEnabled; // 0x11C
		Modules::Command *VarRconConsoleOutputEnabled; // 0x120
		Modules::Command *VarServerTeamShuffleEnabled; // 0x124
		Modules::Command *VarServerVotePassPercentage; // 0x128
		Modules::Command *VarTempBanDuration; // 0x12C
		Modules::Command *VarChatCommandKickPlayerEnabled; // 0x130
		Modules::Command *VarChatCommandEndGameEnabled; // 0x134
		Modules::Command *VarChatCommandEndRoundEnabled; // 0x138
		Modules::Command *VarChatCommandVoteTime; // 0x13C
		Modules::Command *VarChatCommandShuffleTeamsEnabled; // 0x140
		Modules::Command *VarChatFilterEnabled; // 0x144
		Modules::Command *VarReturnToLobbyTimeoutSeconds; // 0x148
		Modules::Command *VarBanListSyncIntervalSeconds; // 0x14C
		Modules::Command *VarPostGameTimeSeconds; // 0x150
		Modules::Command *VarPostGameFadeStartDelay; // 0x154
		Modules::Command *VarChatVoteAction; // 0x158
		Modules::Command *VarChatVoteActionClient; // 0x15C
		Modules::Command *VarChatVoteStarted; // 0x160
		Modules::Command *VarChatVoteStartedClient; // 0x164
		Modules::Command *VarChatVotesNeeded; // 0x168
		Modules::Command *VarChatVotesNeededClient; // 0x16C
		Modules::Command *VarChatVoteStartedByUid; // 0x170
		Modules::Command *VarChatVoteStartedByUidClient; // 0x174
		Modules::Command *VarPlayersInfo; // 0x178
		Modules::Command *VarPlayersInfoClient; // 0x17C
		Modules::Command *VarPlayersPingInfo; // 0x180
		Modules::Command *VarPlayersPingInfoClient; // 0x184
		Modules::Command *VarServerShowPlayerPing; // 0x188
		Modules::Command *VarNumTeams; // 0x18C
		Modules::Command *VarMinTeamSize; // 0x190
		Modules::Command *VarSignalServerPort; // 0x194
		Modules::Command *VarSendChatToRconClients; // 0x198
		Modules::Command *VarHttpServerCacheTime; // 0x19C
		Modules::Command *VarServerPodiumEnabled; // 0x1A0
		Modules::Command *VarServerKillCommandDuringPodiumEnabled; // 0x1A4
		Modules::Command *VarServerPodiumEnabledClient; // 0x1A8
		Modules::Command *VarServerPodiumForgeEnabled; // 0x1AC
		Modules::Command *VarServerPodiumForgeEnabledClient; // 0x1B0
		Modules::Command *VarCameraAllowedOnClients; // 0x1B4
		Modules::Command *VarCameraAllowedOnClientsClient; // 0x1B8
		Modules::Command *VarDebugAllowedOnClients; // 0x1BC
		Modules::Command *VarDebugAllowedOnClientsClient; // 0x1C0
		std::unordered_set<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > NonAllowedNames; // 0x1C4
		std::unordered_set<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > FilteredWords; // 0x1EC
		std::unordered_set<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > FilteredPatterns; // 0x214
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > FilterReplacementWord; // 0x23C
		void refreshServerFilters();
		std::unordered_set<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > GetFilteredWordsList();
		std::unordered_set<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > GetFilteredPatternsList();
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetFilterReplacementWord();
		ModuleServer();
		~ModuleServer(); /* compiler_generated() */
	};
	static_assert(sizeof(Modules::ModuleServer) == 600, "Invalid Modules::ModuleServer size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODULES_MODULESERVER_HPP__
