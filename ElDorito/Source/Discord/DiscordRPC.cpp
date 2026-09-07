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
#include "Common/Http/HttpRequest.hpp"
#include "Forge/Magnets.hpp"
#include "Pointer.hpp"
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

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern char const *APPLICATION_ID; // 0x11353AE0
	extern std::pair<std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> >,bool> const ipGetter[3]; // 0x1240DA40
}
/* ---------- public code */

namespace Discord
{
	_extern void _sub_10953000(Discord::DiscordRPC *const, std::string);
	void DiscordRPC::SetJoinString(std::basic_string<char,std::char_traits<char>,std::allocator<char> > join) // 0x10953000
	{
		mangled_x86(MANGLED_TODO, "?SetJoinString@DiscordRPC@Discord@@QAEXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > join;
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
