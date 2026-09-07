#ifndef __SERVER_VOTING_VOTINGUTIL_HPP__
#define __SERVER_VOTING_VOTINGUTIL_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Server/Voting/VotingTypes.hpp"

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
		struct MapAndType;
		struct SMapListItem;
	}
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Server
{
	namespace Voting
	{
		extern __int32 getCustomMapID(std::basic_string<char,std::char_traits<char>,std::allocator<char> > mapName);
		extern bool findMapInfoInModPackage(__int32 mapId, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &mapName, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &identifier, Server::Voting::SMapListItem *info);
		extern bool getMapInfo(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &mapName, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &modpack, Server::Voting::SMapListItem *info);
		extern unsigned __int32 FindMapByName(std::vector<Server::Voting::HaloMap,std::allocator<Server::Voting::HaloMap> > const &maps, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name);
		extern unsigned __int32 FindTypeByName(std::vector<Server::Voting::HaloType,std::allocator<Server::Voting::HaloType> > const &types, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name);
		extern void BuildRandomPlaylist(std::vector<Server::Voting::MapAndType,std::allocator<Server::Voting::MapAndType> > &playlist, unsigned __int32 size, std::vector<Server::Voting::HaloType,std::allocator<Server::Voting::HaloType> > const &types, std::vector<Server::Voting::HaloMap,std::allocator<Server::Voting::HaloMap> > const &maps);
		extern std::vector<Server::Voting::SMapListItem,std::allocator<Server::Voting::SMapListItem> > const &GetDefaultMapList();
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __SERVER_VOTING_VOTINGUTIL_HPP__
