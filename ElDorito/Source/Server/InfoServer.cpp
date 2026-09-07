/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_results.hpp"
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
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "ElDorito.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/mod_system.hpp"
#include "mods/new/IModManager.hpp"
#include "Pointer.hpp"
#include "Server/Voting/VotingPackets.hpp"
#include "Server/Voting/VotingTypes.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Utils/UPnP.hpp"

#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
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

namespace
{
	struct HttpRequestLine;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace InfoServer {}
	using namespace Server::InfoServer;
	namespace Voting {}
	using namespace Server::Voting;
}

namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace Emblems {}
	using namespace Player::Emblems;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

//enum ParseHttpRequestLine::__l2::s_state
//{
//	STATE_METHOD_TOKEN = 0,
//	STATE_REQUEST_URI,
//	STATE_PROTOCOL_VERSION,
//	STATE_END,
//};

/* ---------- definitions */

namespace
{
	#pragma pack(push, 4)
	struct HttpRequestLine
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > method; // 0x0
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > requestUri; // 0x1C
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > protocolVersion; // 0x38
		HttpRequestLine(HttpRequestLine &); /* compiler_generated() */
		HttpRequestLine(HttpRequestLine const &); /* compiler_generated() */
		HttpRequestLine(); /* compiler_generated() */
		~HttpRequestLine(); /* compiler_generated() */
		HttpRequestLine &operator=(HttpRequestLine &); /* compiler_generated() */
		HttpRequestLine &operator=(HttpRequestLine const &); /* compiler_generated() */
	};
	#pragma pack(pop)
	static_assert(sizeof(HttpRequestLine) == 84, "Invalid HttpRequestLine size");
}
/* ---------- prototypes */

namespace Server
{
	namespace InfoServer
	{
		extern bool IsInfoSocketOpen();
		extern bool StartInfoServer();
		extern bool StopInfoServer();
		extern __int32 __stdcall networkWndProc(HWND__ *hWnd, unsigned __int32 msg, unsigned __int32 wParam, long lParam, bool *outHandled);
		extern void Tick();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern unsigned __int32 infoSocket; // 0x124678D8
	extern bool infoSocketOpen; // 0x124678DC
	extern long long lastAnnounce; // 0x124678E0
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > httpServerCache; // 0x124678A0
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > modListJson; // 0x124678BC
	extern long long timeSinceLastPoll; // 0x124678E8
	extern __int32 modCount; // 0x124678F0
}
namespace Server
{
	namespace Voting
	{
		namespace
		{
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const DefaultTypes[8]; // 0x124676E0
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const DefaultTypeNames[8]; // 0x124677C0
		}
	}
}
/* ---------- public code */

namespace Server
{
	namespace InfoServer
	{
		_extern bool _sub_10B1E450();
		bool IsInfoSocketOpen() // 0x10B1E450
		{
			mangled_x86(MANGLED_TODO, "?IsInfoSocketOpen@InfoServer@Server@@YA_NXZ");
			// procedure flags: nofpo
			todo("implement");
			bool __result = _sub_10B1E450();
			return __result;
		}

		_extern bool _sub_10B1E850();
		bool StartInfoServer() // 0x10B1E850
		{
			mangled_x86(MANGLED_TODO, "?StartInfoServer@InfoServer@Server@@YA_NXZ");
			// procedure flags: nofpo
			// static ...; // 0x10B1ED80
			// static ...; // 0x10B1ED74
			// static ...; // 0x10B1ED6C
			// HWND__ *hwnd;
			// sockaddr_in bindAddr;
			// unsigned long port;
			// function call : unsigned __int32 (__int32, __int32, __int32)
			// function call : unsigned long (unsigned long)
			// function call : unsigned short (unsigned short)
			// function call : __int32 (unsigned __int32, sockaddr const *, __int32)
			// function call : unsigned short (unsigned short)
			// function call : __int32 (unsigned __int32, HWND__ *, unsigned __int32, long)
			// function call : __int32 (unsigned __int32, __int32)
			todo("implement");
			bool __result = _sub_10B1E850();
			return __result;
		}

		_extern bool _sub_10B1EEE0();
		bool StopInfoServer() // 0x10B1EEE0
		{
			mangled_x86(MANGLED_TODO, "?StopInfoServer@InfoServer@Server@@YA_NXZ");
			// procedure flags: nofpo
			// static ...; // 0x10B1EFF4
			// static ...; // 0x10B1EFE8
			// static ...; // 0x10B1EFE0
			// __int32 istrue;
			// function call : __int32 (unsigned __int32)
			// function call : __int32 (unsigned __int32, __int32, __int32, char const *, __int32)
			todo("implement");
			bool __result = _sub_10B1EEE0();
			return __result;
		}

		_extern __int32 _sub_10B1F560(HWND__ *, unsigned __int32, unsigned __int32, long, bool *);
		__int32 __stdcall networkWndProc(HWND__ *hWnd, unsigned __int32 msg, unsigned __int32 wParam, long lParam, bool *outHandled) // 0x10B1F560
		{
			mangled_x86(MANGLED_TODO, "?networkWndProc@InfoServer@Server@@YGHPAUHWND__@@IIJPA_N@Z");
			// static ...; // 0x10B1F908
			// static ...; // 0x10B1F900
			// HWND__ *hWnd;
			// unsigned __int32 msg;
			// unsigned __int32 wParam;
			// long lParam;
			// bool *outHandled;
			// __int32 inDataLength;
			// char inDataBuffer[4096];
			// unsigned __int32 clientSocket;
			{
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > rawRequest;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > reply;
				// HttpRequestLine requestLine;
			}
			// function call : __int32 (unsigned __int32)
			// function call : unsigned __int32 (unsigned __int32, sockaddr *, __int32 *)
			// function call : __int32 (unsigned __int32, HWND__ *, unsigned __int32, long)
			// function call : __int32 (unsigned __int32, char *, __int32, __int32)
			// function call : __int32 (unsigned __int32, char const *, __int32, __int32)
			// function call : __int32 (unsigned __int32)
			todo("implement");
			__int32 __result = _sub_10B1F560(hWnd, msg, wParam, lParam, outHandled);
			return __result;
		}

		_extern void _sub_10B1F050();
		void Tick() // 0x10B1F050
		{
			mangled_x86(MANGLED_TODO, "?Tick@InfoServer@Server@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10B1F170
			// static ...; // 0x10B1F164
			// static ...; // 0x10B1F15C
			// long long curTime;
			todo("implement");
			_sub_10B1F050();
		}
	}
}

/* ---------- private code */
