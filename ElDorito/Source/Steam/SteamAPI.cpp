/* ---------- headers */

#include "Steam/SteamAPI.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"

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
	extern SteamAPI* _sub_10C51C30(Steam::SteamAPI *const);
	SteamAPI::SteamAPI() // 0x10C51C30
	{
		mangled_x86(MANGLED_TODO, "??0SteamAPI@Steam@@QAE@XZ");
		// static ...; // 0x10C51D68
		// static ...; // 0x10C51D5C
		// static ...; // 0x10C51D54
		// Steam::SteamAPI *const this;
		// _iobuf *file;
		// ISteamFriends *steamInterface;
		// function call : __int32 (char const *, char const *)
		// function call : bool (char const *, char const *)
		todo("implement");
		_sub_10C51C30(this);
	}

	_extern bool _sub_10C51F20(Steam::SteamAPI *const);
	bool SteamAPI::InitPublicAPI() // 0x10C51F20
	{
		mangled_x86(MANGLED_TODO, "?InitPublicAPI@SteamAPI@Steam@@AAE_NXZ");
		// static ...; // 0x10C52038
		// static ...; // 0x10C5202C
		// static ...; // 0x10C52024
		// Steam::SteamAPI *const this;
		// void *(*createInterface)(char const *, __int32 *);
		// ISteamClient *clientEngine;
		// __int32 returnCode;
		{
			// __int32 steamPipe;
			// __int32 steamUser;
		}
		// function call : void *(*)(char const *, __int32 *)
		// function call : __int32 ()
		// function call : __int32 (__int32)
		todo("implement");
		bool __result = _sub_10C51F20(this);
		return __result;
	}
}

extern ISteamFriends *_sub_10C51DC0(Steam::SteamAPI *const);
namespace Steam
{
	ISteamFriends *SteamAPI::GetIFriendsInterface() // 0x10C51DC0
	{
		mangled_x86(MANGLED_TODO, "?GetIFriendsInterface@SteamAPI@Steam@@QAEPAVISteamFriends@@XZ");
		// Steam::SteamAPI *const this;
		// function call : ISteamFriends *(__int32, __int32, char const *)
		todo("implement");
		ISteamFriends * __result = _sub_10C51DC0(this);
		return __result;
	}
}

extern ISteamUser *_sub_10C51E70(Steam::SteamAPI *const);
namespace Steam
{
	ISteamUser *SteamAPI::GetISteamUserInterface() // 0x10C51E70
	{
		mangled_x86(MANGLED_TODO, "?GetISteamUserInterface@SteamAPI@Steam@@QAEPAVISteamUser@@XZ");
		// Steam::SteamAPI *const this;
		// function call : ISteamUser *(__int32, __int32, char const *)
		todo("implement");
		ISteamUser * __result = _sub_10C51E70(this);
		return __result;
	}
}

/* ---------- private code */
