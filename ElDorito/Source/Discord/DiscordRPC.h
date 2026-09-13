#ifndef __DISCORD_DISCORDRPC_H__
#define __DISCORD_DISCORDRPC_H__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/Magnets.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"

#include <memory>
#include <mutex>
#include <string>

/* ---------- forward declarations */

namespace Discord
{
	class DiscordRPC;
}

/* ---------- constants */

/* ---------- definitions */

namespace Discord
{
	class DiscordRPC :
		public Utils::Singleton<Discord::DiscordRPC>
	{
	public:
		DiscordRichPresence discordPresence; // 0x0
		std::string detailString; // 0x48
		std::string mapString; // 0x64
		std::string gameTypeString; // 0x80
		std::string matchSecret; // 0x9C
		std::mutex joinMtx; // 0xB8
		std::string joinString; // 0xE8
	private:
		long long lastUpdate; // 0x108
		long long const discordUpdateTime; // 0x110
	public:
		void SetJoinString(std::string join);
		void Update();
		void UpdatePresence(__int32 networkMode);
		void UpdatePresence();
		void ReplyToJoinRequest(char const *userId, __int32 reply);
		void Shutdown();
		DiscordRPC();
		~DiscordRPC() = default; /* compiler_generated() */
	};
}

// static_assert(sizeof(Discord::DiscordRPC) == 280, "Invalid Discord::DiscordRPC size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __DISCORD_DISCORDRPC_H__
