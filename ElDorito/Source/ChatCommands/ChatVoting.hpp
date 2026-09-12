#ifndef __CHATCOMMANDS_CHATVOTING_HPP__
#define __CHATCOMMANDS_CHATVOTING_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"

#include <memory>
#include <string>
#include <vector>

/* ---------- forward declarations */

namespace ChatCommands
{
	class EndGameCommand;
	class EndRoundCommand;
	class KickIndexCommand;
	class KickPlayerCommand;
	class ShuffleTeamsCommand;
	class VotingChatCommand;
}

/* ---------- constants */

/* ---------- definitions */

namespace ChatCommands
{
	class VotingChatCommand
	{
	public:
		virtual void doOnVotePass(std::string) = 0;
		virtual void doOnVoteStart(std::string) = 0;
		virtual bool isValidArgument(std::string, std::string &) = 0;
		virtual void doOnVoteFail() = 0;
		virtual bool isEnabled() = 0;
		void processMessage(unsigned char sender, std::string argument);
		void StartVote();
		void enable();
		void disable();
		void tick();
		void endVoting();
		bool isCurrentlyVoting();
		std::string getName();
		std::string getDescription();
		VotingChatCommand(ChatCommands::VotingChatCommand &); /* compiler_generated() */
		VotingChatCommand(ChatCommands::VotingChatCommand const &); /* compiler_generated() */
		VotingChatCommand(std::string n, std::string d);
		void processVote(unsigned char sender, std::string message);
	protected:
		__int32 starterIndex; // 0x8
		unsigned __int32 votesNeeded; // 0xC
	private:
		std::string name; // 0x10
		std::string description; // 0x2C
		bool currentlyVoting; // 0x48
		unsigned char __pad0[7]; // 0x49
		long long voteTimeStarted; // 0x50
		std::vector<unsigned __int64> yesVoters; // 0x58
	public:
		_inline ~VotingChatCommand(); /* compiler_generated() */
		ChatCommands::VotingChatCommand &operator=(ChatCommands::VotingChatCommand &); /* compiler_generated() */
		ChatCommands::VotingChatCommand &operator=(ChatCommands::VotingChatCommand const &); /* compiler_generated() */
	};
	static_assert(sizeof(ChatCommands::VotingChatCommand) == 104, "Invalid ChatCommands::VotingChatCommand size");

	class EndGameCommand :
		public ChatCommands::VotingChatCommand
	{
	public:
		virtual void doOnVoteStart(std::string starterName);
		virtual void doOnVotePass(std::string name);
		virtual void doOnVoteFail();
		virtual bool isValidArgument(std::string s, std::string &returnInfo);
		virtual bool isEnabled();
		EndGameCommand(ChatCommands::EndGameCommand &); /* compiler_generated() */
		EndGameCommand(ChatCommands::EndGameCommand const &); /* compiler_generated() */
		EndGameCommand();
		_inline ~EndGameCommand(); /* compiler_generated() */
		ChatCommands::EndGameCommand &operator=(ChatCommands::EndGameCommand &); /* compiler_generated() */
		ChatCommands::EndGameCommand &operator=(ChatCommands::EndGameCommand const &); /* compiler_generated() */
	};
	static_assert(sizeof(ChatCommands::EndGameCommand) == 104, "Invalid ChatCommands::EndGameCommand size");

	class EndRoundCommand :
		public ChatCommands::VotingChatCommand
	{
	public:
		virtual void doOnVoteStart(std::string starterName);
		virtual void doOnVotePass(std::string name);
		virtual void doOnVoteFail();
		virtual bool isValidArgument(std::string s, std::string &returnInfo);
		virtual bool isEnabled();
		EndRoundCommand(ChatCommands::EndRoundCommand &); /* compiler_generated() */
		EndRoundCommand(ChatCommands::EndRoundCommand const &); /* compiler_generated() */
		EndRoundCommand();
		_inline ~EndRoundCommand(); /* compiler_generated() */
		ChatCommands::EndRoundCommand &operator=(ChatCommands::EndRoundCommand &); /* compiler_generated() */
		ChatCommands::EndRoundCommand &operator=(ChatCommands::EndRoundCommand const &); /* compiler_generated() */
	};
	static_assert(sizeof(ChatCommands::EndRoundCommand) == 104, "Invalid ChatCommands::EndRoundCommand size");

	class ShuffleTeamsCommand :
		public ChatCommands::VotingChatCommand
	{
	public:
		virtual void doOnVoteStart(std::string starterName);
		virtual void doOnVotePass(std::string name);
		virtual void doOnVoteFail();
		virtual bool isValidArgument(std::string s, std::string &returnInfo);
		virtual bool isEnabled();
		ShuffleTeamsCommand(ChatCommands::ShuffleTeamsCommand &); /* compiler_generated() */
		ShuffleTeamsCommand(ChatCommands::ShuffleTeamsCommand const &); /* compiler_generated() */
		ShuffleTeamsCommand();
		_inline ~ShuffleTeamsCommand(); /* compiler_generated() */
		ChatCommands::ShuffleTeamsCommand &operator=(ChatCommands::ShuffleTeamsCommand &); /* compiler_generated() */
		ChatCommands::ShuffleTeamsCommand &operator=(ChatCommands::ShuffleTeamsCommand const &); /* compiler_generated() */
	};
	static_assert(sizeof(ChatCommands::ShuffleTeamsCommand) == 104, "Invalid ChatCommands::ShuffleTeamsCommand size");

	class KickPlayerCommand :
		public ChatCommands::VotingChatCommand
	{
	public:
		virtual void doOnVoteStart(std::string starterName);
		virtual void doOnVotePass(std::string name);
		virtual void doOnVoteFail();
		virtual bool isEnabled();
		virtual bool isValidArgument(std::string s, std::string &returnInfo);
		KickPlayerCommand(ChatCommands::KickPlayerCommand &); /* compiler_generated() */
		KickPlayerCommand(ChatCommands::KickPlayerCommand const &); /* compiler_generated() */
		KickPlayerCommand();
	private:
		std::string playerName; // 0x68
	public:
		_inline ~KickPlayerCommand(); /* compiler_generated() */
		ChatCommands::KickPlayerCommand &operator=(ChatCommands::KickPlayerCommand &); /* compiler_generated() */
		ChatCommands::KickPlayerCommand &operator=(ChatCommands::KickPlayerCommand const &); /* compiler_generated() */
	};
	static_assert(sizeof(ChatCommands::KickPlayerCommand) == 136, "Invalid ChatCommands::KickPlayerCommand size");

	class KickIndexCommand :
		public ChatCommands::VotingChatCommand
	{
	public:
		virtual void doOnVoteStart(std::string starterName);
		virtual void doOnVotePass(std::string name);
		virtual void doOnVoteFail();
		virtual bool isEnabled();
		virtual bool isValidArgument(std::string s, std::string &returnInfo);
		KickIndexCommand(ChatCommands::KickIndexCommand &); /* compiler_generated() */
		KickIndexCommand(ChatCommands::KickIndexCommand const &); /* compiler_generated() */
		KickIndexCommand();
	private:
		std::string playerName; // 0x68
	public:
		_inline ~KickIndexCommand(); /* compiler_generated() */
		ChatCommands::KickIndexCommand &operator=(ChatCommands::KickIndexCommand &); /* compiler_generated() */
		ChatCommands::KickIndexCommand &operator=(ChatCommands::KickIndexCommand const &); /* compiler_generated() */
	};
	static_assert(sizeof(ChatCommands::KickIndexCommand) == 136, "Invalid ChatCommands::KickIndexCommand size");
}

/* ---------- prototypes */

namespace ChatCommands
{
	extern __int32 findNumberOfPlayersInGame();
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __CHATCOMMANDS_CHATVOTING_HPP__
