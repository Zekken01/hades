#ifndef __SERVER_VOTING_VOTINGPACKETS_HPP__
#define __SERVER_VOTING_VOTINGPACKETS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Patches/CustomPackets.hpp"
#include "ThirdParty/rapidjson/rapidjson.h"

#include <memory>

/* ---------- forward declarations */

namespace Server
{
	namespace Voting
	{
		class VotingMessageHandler;
		struct VotingMessage;
		struct VotingOption;
	}
}

/* ---------- constants */

namespace Server
{
	namespace Voting
	{
		enum VotingMessageType : unsigned __int32
		{
			VetoVote = 0,
			VetoOption,
			Vote,
			VotingOptions,
			VoteTally,
			Winner,
			VoteTimerUpdated,
			VoteEnded,
			Count,
		};
	}
}

/* ---------- definitions */

#pragma pack(push, 1)
namespace Server
{
	namespace Voting
	{
		struct VotingOption
		{
			char scnrName[32]; // 0x0
			char mapName[17]; // 0x20
			char modName[17]; // 0x31
			char modHash[41]; // 0x42
			char typeName[17]; // 0x6B
			char imageUri[512]; // 0x7C
			bool canVeto; // 0x27C
		};
	}
}

#pragma pack(pop)
static_assert(sizeof(Server::Voting::VotingOption) == 637, "Invalid Server::Voting::VotingOption size");

namespace Server
{
	namespace Voting
	{
		struct VotingMessage
		{
			Server::Voting::VotingMessageType Type; // 0x0
			Server::Voting::VotingOption votingOptions[6]; // 0x4
			unsigned char voteTime; // 0xEF2
			unsigned char votes[6]; // 0xEF3
			unsigned char Vote; // 0xEF9
			unsigned char winner; // 0xEFA
			bool voteEnded; // 0xEFB
			bool shouldUpdateTimer; // 0xEFC
			unsigned char votesNeededToPass; // 0xEFD
			public:
			// Declaring the VotingMessageType constructor suppressed the implicit
			// default one, so a class holding a VotingMessage could not leave it
			// default-initialised - C2512. The original never touches this member
			// in those constructors, and every VotingOption is POD, so the
			// defaulted constructor is trivial and emits nothing.
			VotingMessage() = default;  // hades: added for 0x10739F90, 0x1073A8D0
			VotingMessage(Server::Voting::VotingMessageType type);
		};
		static_assert(sizeof(Server::Voting::VotingMessage) == 3840, "Invalid Server::Voting::VotingMessage size");

		class VotingMessageHandler
		{
		public:
			virtual _inline ~VotingMessageHandler();
			virtual void MessageReceived(Server::Voting::VotingMessage const &) = 0;
			VotingMessageHandler(Server::Voting::VotingMessageHandler const &); /* compiler_generated() */
			_inline VotingMessageHandler() = default; /* compiler_generated() */
			Server::Voting::VotingMessageHandler &operator=(Server::Voting::VotingMessageHandler const &); /* compiler_generated() */
		};
		static_assert(sizeof(Server::Voting::VotingMessageHandler) == 4, "Invalid Server::Voting::VotingMessageHandler size");
	}
}

/* ---------- prototypes */

namespace Server
{
	namespace Voting
	{
		extern void AddMessageHandler(std::shared_ptr<Server::Voting::VotingMessageHandler> handler);
		extern void InitializePackets();
		extern bool BroadcastVotingMessage(Server::Voting::VotingMessage &message);
		extern bool SendVotingMessageToPeer(Server::Voting::VotingMessage &message, __int32 peer);
		extern bool SendVoteToHost(__int32 const vote);
	}
}

/* ---------- globals */

/* ---------- public code */

namespace Server
{
	namespace Voting
	{
		inline VotingMessageHandler::~VotingMessageHandler() // 0x10C9A7C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1VotingMessageHandler@Voting@Server@@UAE@XZ");
		}
	}
}

/* ---------- private code */

#endif // __SERVER_VOTING_VOTINGPACKETS_HPP__
