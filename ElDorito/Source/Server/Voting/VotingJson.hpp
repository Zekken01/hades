#ifndef __SERVER_VOTING_VOTINGJSON_HPP__
#define __SERVER_VOTING_VOTINGJSON_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Server/Voting/VotingTypes.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/stream.h"

#include <memory>
#include <string>
#include <vector>

/* ---------- forward declarations */

namespace Server
{
	namespace Voting
	{
		struct HaloMap;
		struct HaloType;
		struct PlaylistItem;
		struct VotingJson;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Server
{
	namespace Voting
	{
		struct VotingJson
		{
			std::vector<Server::Voting::HaloType> types; // 0x0
			std::vector<Server::Voting::HaloMap> maps; // 0x10
			std::vector<Server::Voting::PlaylistItem> vetoPlaylist; // 0x20
			VotingJson(Server::Voting::VotingJson &); /* compiler_generated() */
			VotingJson(Server::Voting::VotingJson const &); /* compiler_generated() */
			_inline VotingJson() = default; /* compiler_generated() */
			_inline ~VotingJson(); /* compiler_generated() */
			Server::Voting::VotingJson &operator=(Server::Voting::VotingJson &); /* compiler_generated() */
			Server::Voting::VotingJson &operator=(Server::Voting::VotingJson const &); /* compiler_generated() */
		};
		static_assert(sizeof(Server::Voting::VotingJson) == 48, "Invalid Server::Voting::VotingJson size");
	}
}

/* ---------- prototypes */

namespace Server
{
	namespace Voting
	{
		extern bool LoadVotingJson(std::string const &filename, Server::Voting::VotingJson &voting);
		extern bool LoadPlaylistItem(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &c, Server::Voting::PlaylistItem &item, std::vector<Server::Voting::HaloType> const &types);
		extern bool LoadHaloMap(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &mapObject, std::string const &modPack, Server::Voting::HaloMap &map);
		extern bool LoadHaloType(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &c, Server::Voting::HaloType &ht);
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __SERVER_VOTING_VOTINGJSON_HPP__
