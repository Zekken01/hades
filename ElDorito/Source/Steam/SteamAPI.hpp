#ifndef __STEAM_STEAMAPI_HPP__
#define __STEAM_STEAMAPI_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Patches/PlayerPropertiesExtension.hpp"
#include "Steam/SteamLoader.h"

/* ---------- forward declarations */

struct ISteamClient;
class ISteamFriends;
class ISteamUser;
namespace Steam
{
	class SteamAPI;
	class SteamLoader;
}

/* ---------- constants */

/* ---------- definitions */

namespace Steam
{
	class SteamAPI :
		public Utils::Singleton<Steam::SteamAPI>
	{
	public:
		SteamAPI();
		ISteamFriends *GetIFriendsInterface();
		ISteamUser *GetISteamUserInterface();
	private:
		bool InitPublicAPI();
		Steam::SteamLoader m_SteamLoader; // 0x0
		ISteamClient *m_Client; // 0x4
		__int32 m_SteamPipe; // 0x8
		__int32 m_SteamUser; // 0xC
	};
}

// static_assert(sizeof(Steam::SteamAPI) == 16, "Invalid Steam::SteamAPI size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __STEAM_STEAMAPI_HPP__
