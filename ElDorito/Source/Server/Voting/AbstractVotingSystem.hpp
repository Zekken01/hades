#ifndef __SERVER_VOTING_ABSTRACTVOTINGSYSTEM_HPP__
#define __SERVER_VOTING_ABSTRACTVOTINGSYSTEM_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Server/Voting/VotingPackets.hpp"
#include "Server/Voting/VotingTypes.hpp"
#include "Utils/NameValueTable.hpp"

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <utility>

/* ---------- forward declarations */

namespace Server
{
	namespace Voting
	{
		class AbstractVotingSystem;
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
		class AbstractVotingSystem
		{
		public:
			virtual _inline ~AbstractVotingSystem() = default;
			virtual void Init() = 0;
			virtual void NewVote() = 0;
			virtual void EndVote() = 0;
			virtual void Tick() = 0;
			virtual void Reset() = 0;
			virtual void StartVoting() = 0;
			virtual bool isEnabled() = 0;
			virtual void SendVoteCountsToEveryone() = 0;
			virtual void onExit() = 0;
			virtual bool ShouldSendVotingOptions();
			void GenerateVotingOptionsMessage(__int32 peer);
			virtual Server::Voting::VotingMessage GenerateVotingOptionsMessage(bool) = 0;
			virtual void LogVote(Server::Voting::VotingMessage const &, std::string) = 0;
			virtual __int32 getVoteNeededToPass();
			bool ReloadVotingJson(std::string fileName, bool loadFileFromDisc);
			bool AllowShuffle = true; // 0x8
			unsigned char __pad0[7]; // 0x9
			std::function<void __cdecl(Server::Voting::MapAndType)> votePassedCallback; // 0x10
		protected:
			std::map<std::string,int> mapVotes; // 0x38
			unsigned char __pad1[4]; // 0x44
			long long voteStartedTime = 0; // 0x48
			Server::Voting::VotingMessage finalTally; // 0x50
			bool winnerChosen = false; // 0xF50
			bool revoteFlag = false; // 0xF51
			bool idle = false; // 0xF52
			bool jsonLoaded = false; // 0xF53
		public:
			void CheckAndLoadJson();
		protected:
			void NotifyVotePassed(Server::Voting::MapAndType const &winner);
		private:
			virtual bool LoadJson(std::string) = 0;
			virtual Server::Voting::MapAndType GenerateVotingOption() = 0;
			virtual void loadDefaultMapsAndTypes() = 0;
		public:
			AbstractVotingSystem(Server::Voting::AbstractVotingSystem const &); /* compiler_generated() */
			AbstractVotingSystem() = default; /* compiler_generated() */ // 0x10739F90
			Server::Voting::AbstractVotingSystem &operator=(Server::Voting::AbstractVotingSystem const &); /* compiler_generated() */
		};
		static_assert(sizeof(Server::Voting::AbstractVotingSystem) == 3928, "Invalid Server::Voting::AbstractVotingSystem size");
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Server
{
	namespace Voting
	{

	}
}

/* ---------- private code */

#endif // __SERVER_VOTING_ABSTRACTVOTINGSYSTEM_HPP__
