#ifndef __SERVER_VOTING_VETOSYSTEM_HPP__
#define __SERVER_VOTING_VETOSYSTEM_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Server/Voting/AbstractVotingSystem.hpp"
#include "Server/Voting/VotingPackets.hpp"
#include "Server/Voting/VotingTypes.hpp"

#include <memory>
#include <string>
#include <vector>

/* ---------- forward declarations */

namespace Server
{
	namespace Voting
	{
		class AbstractVotingSystem;
		class VetoSystem;
		struct MapAndType;
		struct VotingMessage;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Server
{
	namespace Voting
	{
		class VetoSystem :
			public Server::Voting::AbstractVotingSystem
		{
		public:
			VetoSystem(Server::Voting::VetoSystem &); /* compiler_generated() */
			VetoSystem(Server::Voting::VetoSystem const &); /* compiler_generated() */
			VetoSystem();
			virtual void Init();
			virtual void NewVote();
			virtual void EndVote();
			virtual void Tick();
			virtual void SendVoteCountsToEveryone();
			virtual void Reset();
			virtual void onExit();
			virtual void StartVoting();
			virtual Server::Voting::VotingMessage GenerateVotingOptionsMessage(bool updateTime);
			virtual bool isEnabled();
			virtual void LogVote(Server::Voting::VotingMessage const &message, std::string name);
		private:
			virtual bool LoadJson(std::string filename);
			virtual Server::Voting::MapAndType GenerateVotingOption();
			void SetGameAndMap();
			void SetStartTimer();
			void SetVoteStartedTime();
			void countVotes();
			void FindWinner();
			virtual void loadDefaultMapsAndTypes();
			long long startime; // 0xF58
			bool willSetMap; // 0xF60
			unsigned char __pad0[3]; // 0xF61
			std::vector<Server::Voting::MapAndType> currentPlaylist; // 0xF64
			std::vector<Server::Voting::MapAndType> entirePlaylist; // 0xF74
			Server::Voting::MapAndType currentVetoOption; // 0xF84
			__int32 numberOfVetosUsed; // 0x10E8
			__int32 currentNumberOfVotes; // 0x10EC
			bool shouldRunPreviousCommands; // 0x10F0
			unsigned char __pad1[3]; // 0x10F1
			Server::Voting::MapAndType previousWinner; // 0x10F4
		public:
			virtual _inline ~VetoSystem() = default; /* compiler_generated() */ // 0x1073B7F0
			Server::Voting::VetoSystem &operator=(Server::Voting::VetoSystem &); /* compiler_generated() */
			Server::Voting::VetoSystem &operator=(Server::Voting::VetoSystem const &); /* compiler_generated() */
		};
		static_assert(sizeof(Server::Voting::VetoSystem) == 4696, "Invalid Server::Voting::VetoSystem size");
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __SERVER_VOTING_VETOSYSTEM_HPP__
