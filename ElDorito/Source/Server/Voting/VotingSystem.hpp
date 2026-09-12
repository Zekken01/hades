#ifndef __SERVER_VOTING_VOTINGSYSTEM_HPP__
#define __SERVER_VOTING_VOTINGSYSTEM_HPP__
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
		class VotingSystem;
		struct HaloMap;
		struct HaloType;
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
		class VotingSystem :
			public Server::Voting::AbstractVotingSystem
		{
		public:
			VotingSystem(Server::Voting::VotingSystem &); /* compiler_generated() */
			VotingSystem(Server::Voting::VotingSystem const &); /* compiler_generated() */
			VotingSystem();
			virtual void Init();
			virtual void NewVote();
			virtual void EndVote();
			virtual void Tick();
			virtual void Reset();
			virtual void StartVoting();
			virtual Server::Voting::VotingMessage GenerateVotingOptionsMessage(bool updateTime);
			virtual bool isEnabled();
			virtual void onExit();
			virtual void SendVoteCountsToEveryone();
			virtual void LogVote(Server::Voting::VotingMessage const &message, std::string name);
		private:
			virtual bool LoadJson(std::string filename);
			virtual void loadDefaultMapsAndTypes();
			virtual Server::Voting::MapAndType GenerateVotingOption();
			std::vector<Server::Voting::MapAndType> countQuickVotes();
			void countVotes();
			void FindWinner();
			long long winnerChosenTime; // 0xF58
			long long mapSetTime; // 0xF60
			long long enumerationTime; // 0xF68
			unsigned __int32 numberOfRevotesUsed; // 0xF70
			unsigned __int32 numberOfRematchesUsed; // 0xF74
			bool isFirstVote; // 0xF78
			bool shouldRunPreviousCommands; // 0xF79
			unsigned char __pad0[2]; // 0xF7A
			Server::Voting::MapAndType previousWinner; // 0xF7C
			Server::Voting::MapAndType winningVotingOption; // 0x10E0
			std::vector<Server::Voting::MapAndType> currentVotingOptions; // 0x1244
			std::vector<Server::Voting::HaloType> gameTypes; // 0x1254
			std::vector<Server::Voting::HaloMap> haloMaps; // 0x1264
		public:
			virtual _inline ~VotingSystem(); /* compiler_generated() */
			Server::Voting::VotingSystem &operator=(Server::Voting::VotingSystem &); /* compiler_generated() */
			Server::Voting::VotingSystem &operator=(Server::Voting::VotingSystem const &); /* compiler_generated() */
		};
		static_assert(sizeof(Server::Voting::VotingSystem) == 4728, "Invalid Server::Voting::VotingSystem size");
	}
}

/* ---------- prototypes */

namespace Server
{
	namespace Voting
	{
		extern double getRandom(double fMin, double fMax);
		extern __int32 getVotesNeededToInstantSkip();
	}
}

/* ---------- globals */

/* ---------- public code */

namespace Server
{
	namespace Voting
	{
		// mangled_x86(MANGLED_DEFAULT, "??1VotingSystem@Voting@Server@@UAE@XZ"); no body to assert in
		_inline VotingSystem::~VotingSystem() = default; // 0x10C43260
	}
}

/* ---------- private code */

#endif // __SERVER_VOTING_VOTINGSYSTEM_HPP__
