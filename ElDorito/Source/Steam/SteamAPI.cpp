/* ---------- headers */

#include "Steam/SteamAPI.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"

#include <isteamfriends.h>  // hades: added for 0x10C51C30
#include "Steam/SteamLoader.h"  // hades: added for 0x10C51C30

#include <isteamclient.h>  // hades: added for 0x10C51DC0

#include <steamclientpublic.h>

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <limits>
#include <tuple>
#include <type_traits>
#include <utility>

/* ---------- forward declarations */

class ISteamFriends;
class ISteamUser;
namespace Steam
{
	class SteamAPI;
}

namespace Utils {}
using namespace ::Utils;

/* ---------- constants */

/* ---------- definitions */

typedef std::function<enum EJobResult __cdecl(void)> TJobFunction;

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Steam
{
	SteamAPI::SteamAPI() // 0x10C51C30
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0SteamAPI@Steam@@QAE@XZ");
		// static ...; // 0x10C51D68
		// static ...; // 0x10C51D5C
		// static ...; // 0x10C51D54
		// Steam::SteamAPI *const this;
		// _iobuf *file;
		// ISteamFriends *steamInterface;
		// function call : __int32 (char const *, char const *)
		// function call : bool (char const *, char const *)

		m_Client = nullptr;
		m_SteamUser = 0;
		m_SteamPipe = 0;
		SetEnvironmentVariableA("SteamAppId", "218");
		_unlink("steam_appid.txt");

		_iobuf *file;
		if (!fopen_s(&file, "steam_appid.txt", "w"))
		{
			fprintf_s(file, "%d", 218);
			fclose(file);
		}

		m_SteamLoader = SteamLoader();
		m_SteamLoader.Initialize();
		InitPublicAPI();

		ISteamFriends *steamInterface = GetIFriendsInterface();
		steamInterface->SetRichPresence("status", "In the menus");
	}

	bool SteamAPI::InitPublicAPI() // 0x10C51F20
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?InitPublicAPI@SteamAPI@Steam@@AAE_NXZ");
		// static ...; // 0x10C52038
		// static ...; // 0x10C5202C
		// static ...; // 0x10C52024
		// Steam::SteamAPI *const this;
		// void *(*createInterface)(char const *, __int32 *);
		// ISteamClient *clientEngine;
		// __int32 returnCode;
			// __int32 steamPipe;
			// __int32 steamUser;
		// function call : void *(*)(char const *, __int32 *)
		// function call : __int32 ()
		// function call : __int32 (__int32)

		if (!m_SteamLoader.IsSteamRunning(true))
			return false;
		auto createInterface = m_SteamLoader.GetCreateInterfaceFunc();
		int returnCode;
		ISteamClient *clientEngine = (ISteamClient *)createInterface("SteamClient017", &returnCode);
		if (clientEngine)
		{
			auto steamPipe = clientEngine->CreateSteamPipe();
			auto steamUser = clientEngine->ConnectToGlobalUser(steamPipe);
			m_Client = clientEngine;
			m_SteamPipe = steamPipe;
			m_SteamUser = steamUser;
			return true;
		}
		return false;
	}
}


namespace Steam
{
	ISteamFriends *SteamAPI::GetIFriendsInterface() // 0x10C51DC0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetIFriendsInterface@SteamAPI@Steam@@QAEPAVISteamFriends@@XZ");
		// Steam::SteamAPI *const this;
		// function call : ISteamFriends *(__int32, __int32, char const *)

		if (m_Client)
		{
			return m_Client->GetISteamFriends(m_SteamUser, m_SteamPipe, "SteamFriends015");
		}
		else
		{
			return nullptr;
		}
	}
}


namespace Steam
{
	ISteamUser *SteamAPI::GetISteamUserInterface() // 0x10C51E70
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetISteamUserInterface@SteamAPI@Steam@@QAEPAVISteamUser@@XZ");
		// Steam::SteamAPI *const this;
		// function call : ISteamUser *(__int32, __int32, char const *)

		if (m_Client)
		{
			return m_Client->GetISteamUser(m_SteamUser, m_SteamPipe, "SteamUser019");
		}
		else
		{
			return nullptr;
		}
	}
}

/* ---------- private code */
