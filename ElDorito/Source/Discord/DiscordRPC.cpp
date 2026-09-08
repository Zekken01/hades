/* ---------- headers */

#include "Discord/DiscordRPC.h"
#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "Forge/Magnets.hpp"
#include "mods/map_variant_loader.hpp"
#include "Patches/Core.hpp"
#include "Pointer.hpp"
#include "ThirdParty/HttpRequest.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <memory>
#include <mutex>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class HttpRequest;
struct c_game_variant;
struct s_map_variant;
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}
namespace Discord
{
	class DiscordRPC;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Core {}
	using namespace Patches::Core;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void handleDiscordDisconnected(__int32 errorCode, char const *message);
void handleDiscordError(__int32 errorCode, char const *message);
void handleDiscordJoin(char const *joinSecret);
void handleDiscordSpectate(char const *spectateSecret);
void handleDiscordJoinRequest(DiscordJoinRequest const *joinRequest);
void UpdateRichPresence();
void handleDiscordReady();
unsigned long DiscordRetrieveExternalIP_Thread(void *lpParam);
void OnShutdown();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern char const *APPLICATION_ID; // 0x11353AE0
	extern std::pair<std::wstring,bool> const ipGetter[3]; // 0x1240DA40
}
using namespace hades_file_local;
/* ---------- public code */

namespace Discord
{
	_extern void _sub_10953000(Discord::DiscordRPC *const, std::string);
	void DiscordRPC::SetJoinString(std::string join) // 0x10953000
	{
		mangled_x86(MANGLED_TODO, "?SetJoinString@DiscordRPC@Discord@@QAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string join;
		todo("implement");
		_sub_10953000(this, join);
	}

	_extern void _sub_10953270(Discord::DiscordRPC *const);
	void DiscordRPC::UpdatePresence() // 0x10953270
	{
		mangled_x86(MANGLED_TODO, "?UpdatePresence@DiscordRPC@Discord@@QAEXXZ");
		// static ...; // 0x10953370
		// static ...; // 0x10953364
		// static ...; // 0x1095335C
		// Discord::DiscordRPC *const this;
		// long long curTime;
		todo("implement");
		_sub_10953270(this);
	}

	_extern void _sub_10953190(Discord::DiscordRPC *const, __int32);
	void DiscordRPC::UpdatePresence(__int32 networkMode) // 0x10953190
	{
		mangled_x86(MANGLED_TODO, "?UpdatePresence@DiscordRPC@Discord@@QAEXH@Z");
		// __int32 networkMode;
		// Blam::Network::Session *session;
		{
			// void *thread;
		}
		// function call : void *(_SECURITY_ATTRIBUTES *, unsigned long, unsigned long (*)(void *), void *, unsigned long, unsigned long *)
		todo("implement");
		_sub_10953190(this, networkMode);
	}

	extern DiscordRPC* _sub_109520A0(Discord::DiscordRPC *const);
	DiscordRPC::DiscordRPC() : discordUpdateTime(todo_result<long long>()) // 0x109520A0
	{
		mangled_x86(MANGLED_TODO, "??0DiscordRPC@Discord@@QAE@XZ");
		// static ...; // 0x10952325
		// static ...; // 0x1095231C
		// static ...; // 0x10952304
		// static ...; // 0x109522FC
		// Discord::DiscordRPC *const this;
		// DiscordEventHandlers handlers;
		// HINSTANCE__ *hModule;
		// wchar_t appPath[260];
		// function call : HINSTANCE__ *(wchar_t const *)
		// function call : unsigned long (HINSTANCE__ *, wchar_t *, unsigned long)
		todo("implement");
		_sub_109520A0(this);
	}

	_extern void _sub_10952FA0(Discord::DiscordRPC *const, char const *, __int32);
	void DiscordRPC::ReplyToJoinRequest(char const *userId, __int32 reply) // 0x10952FA0
	{
		mangled_x86(MANGLED_TODO, "?ReplyToJoinRequest@DiscordRPC@Discord@@QAEXPBDH@Z");
		// __int32 reply;
		todo("implement");
		_sub_10952FA0(this, userId, reply);
	}

	_extern void _sub_109530E0(Discord::DiscordRPC *const);
	void DiscordRPC::Shutdown() // 0x109530E0
	{
		mangled_x86(MANGLED_TODO, "?Shutdown@DiscordRPC@Discord@@QAEXXZ");
		// Discord::DiscordRPC *const this;
		todo("implement");
		_sub_109530E0(this);
	}

	_extern void _sub_10953130(Discord::DiscordRPC *const);
	void DiscordRPC::Update() // 0x10953130
	{
		mangled_x86(MANGLED_TODO, "?Update@DiscordRPC@Discord@@QAEXXZ");
		// Discord::DiscordRPC *const this;
		todo("implement");
		_sub_10953130(this);
	}
}

/* ---------- private code */

void handleDiscordDisconnected(__int32 errorCode, char const *message) // 0x10954210
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?handleDiscordDisconnected@@YAXHPBD@Z");
	// the original is empty
	// `anonymous-namespace'::handleDiscordDisconnected
	// char const *message;
}

void handleDiscordError(__int32 errorCode, char const *message) // 0x10954230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?handleDiscordError@@YAXHPBD@Z");
	// the original is empty
	// `anonymous-namespace'::handleDiscordError
	// char const *message;
}

_extern void _sub_10954250(char const *);
void handleDiscordJoin(char const *joinSecret) // 0x10954250
{
	// `anonymous-namespace'::handleDiscordJoin
	// char const *joinSecret;
	todo("implement");
	_sub_10954250(joinSecret);
}

void handleDiscordSpectate(char const *spectateSecret) // 0x10954430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?handleDiscordSpectate@@YAXPBD@Z");
	// the original is empty
	// `anonymous-namespace'::handleDiscordSpectate
	// char const *spectateSecret;
}

_extern void _sub_10954380(DiscordJoinRequest const *);
void handleDiscordJoinRequest(DiscordJoinRequest const *joinRequest) // 0x10954380
{
	// `anonymous-namespace'::handleDiscordJoinRequest
	// DiscordJoinRequest const *joinRequest;
	todo("implement");
	_sub_10954380(joinRequest);
}

_extern void _sub_109533C0();
void UpdateRichPresence() // 0x109533C0
{
	// `anonymous-namespace'::UpdateRichPresence
	// procedure flags: nofpo
	// static ...; // 0x10953C14
	// static ...; // 0x10953C08
	// static ...; // 0x10953C00
	// Blam::Network::Session *session;
	{
		// c_game_variant *game;
		// __int32 plyIndex;
		// __int32 players;
		// s_map_variant *map;
		{
			// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
		}
	}
	todo("implement");
	_sub_109533C0();
}

_extern void _sub_109543E0();
void handleDiscordReady() // 0x109543E0
{
	// `anonymous-namespace'::handleDiscordReady
	// procedure flags: nofpo
	todo("implement");
	_sub_109543E0();
}

_extern unsigned long _sub_10952610(void *);
unsigned long DiscordRetrieveExternalIP_Thread(void *lpParam) // 0x10952610
{
	// `anonymous-namespace'::DiscordRetrieveExternalIP_Thread
	// static ...; // 0x10952D73
	// static ...; // 0x10952D6A
	// static ...; // 0x10952D62
	// static ...; // 0x10952D5C
	// static ...; // 0x10952D2C
	// static ...; // 0x10952D24
	// void *lpParam;
	// HttpRequest req;
	{
		// __int32 i;
		{
			// std::wstring respHdr;
			// std::string extIp;
			// std::wstring expected;
		}
	}
	todo("implement");
	unsigned long __result = _sub_10952610(lpParam);
	return __result;
}

_extern void _sub_10952F50();
void OnShutdown() // 0x10952F50
{
	// `anonymous-namespace'::OnShutdown
	// procedure flags: nofpo
	todo("implement");
	_sub_10952F50();
}
