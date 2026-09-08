#ifndef __SERVER_VOTING_HALOTYPEINHERITANCE_HPP__
#define __SERVER_VOTING_HALOTYPEINHERITANCE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Server/Voting/VotingTypes.hpp"

#include <memory>
#include <vector>

/* ---------- forward declarations */

namespace Server
{
	namespace Voting
	{
		struct HaloMap;
		struct HaloType;
		struct HaloTypeInheritance;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Server
{
	namespace Voting
	{
		struct HaloTypeInheritance
		{
			static void MergeMaps(std::vector<Server::Voting::HaloMap> &maps, std::vector<Server::Voting::HaloMap> const &newMaps);
			static bool BuildHaloType(Server::Voting::HaloType &newType, Server::Voting::HaloType const &currentType, std::vector<Server::Voting::HaloType> const &types);
			static void BuildHaloTypes(std::vector<Server::Voting::HaloType> &newTypes, std::vector<Server::Voting::HaloType> const &allTypes);
		};
		static_assert(sizeof(Server::Voting::HaloTypeInheritance) == 1, "Invalid Server::Voting::HaloTypeInheritance size");
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __SERVER_VOTING_HALOTYPEINHERITANCE_HPP__
