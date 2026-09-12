/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine.hpp"
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
#include "mods/font_package.hpp"
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

class c_mod_package_manager;
struct s_game_options;
struct s_game_results_player_statistics;
struct s_mod_server_package_entry;
struct s_player_emblem_configuration;
namespace Blam
{
	namespace Network
	{
		struct PlayerSession;
		struct Session;
	}
}
namespace hades_file_local
{
	struct HttpRequestLine;
}
using namespace hades_file_local;

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
	namespace Network {}
	using namespace Blam::Network;
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

namespace hades_file_local
{
	#pragma pack(push, 4)
	struct HttpRequestLine
	{
		std::string method; // 0x0
		std::string requestUri; // 0x1C
		std::string protocolVersion; // 0x38
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
using namespace hades_file_local;
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

std::string BuildInfoServerPayload(std::string const &inDataBuffer);
std::string GenerateModList();
bool ParseHttpRequestLine(std::string const &rawline, HttpRequestLine *outRequestLine);
std::string BuildHttpResponse(std::string const &status, std::string const &contentType, std::string const &content, std::string const &additionalHeaders);
std::string BuildInfoServerResponse(std::string const &rawRequest);
std::string BuildModsServerResponse(std::string const &rawRequest);
std::string BuildNotFoundResponse(std::string const &rawRequest);
std::string BuildBadRequestResponse(std::string const &rawRequest);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern unsigned __int32 infoSocket; // 0x124678D8
	extern bool infoSocketOpen; // 0x124678DC
	extern long long lastAnnounce; // 0x124678E0
	extern std::string httpServerCache; // 0x124678A0
	extern std::string modListJson; // 0x124678BC
	extern long long timeSinceLastPoll; // 0x124678E8
	extern __int32 modCount; // 0x124678F0
}
using namespace hades_file_local;
namespace Server
{
	namespace Voting
	{
		namespace hades_file_local_Server_Voting
		{
			extern std::string const DefaultTypes[8]; // 0x124676E0
			extern std::string const DefaultTypeNames[8]; // 0x124677C0
		}
		using namespace hades_file_local_Server_Voting;
	}
}
/* ---------- public code */

namespace Server
{
	namespace InfoServer
	{
		bool IsInfoSocketOpen() // 0x10B1E450
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?IsInfoSocketOpen@InfoServer@Server@@YA_NXZ");
			// procedure flags: nofpo

			return infoSocketOpen;
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
				// std::string rawRequest;
				// std::string reply;
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

extern std::string _sub_10B1B3F0(std::string const &);
std::string BuildInfoServerPayload(std::string const &inDataBuffer) // 0x10B1B3F0
{
	// `anonymous-namespace'::BuildInfoServerPayload
	// static ...; // 0x10B1CC2F
	// static ...; // 0x10B1CC20
	// static ...; // 0x10B1CC14
	// static ...; // 0x10B1CC0E
	// static ...; // 0x10B1CC07
	// static ...; // 0x10B1CBFB
	// static ...; // 0x10B1CBF4
	// static ...; // 0x10B1CBF2
	// static ...; // 0x10B1CBEB
	// static ...; // 0x10B1CBE0
	// static ...; // 0x10B1CBD3
	// static ...; // 0x10B1CBCB
	// static ...; // 0x10B1CBC6
	// static ...; // 0x10B1CBBF
	// static ...; // 0x10B1CBB8
	// static ...; // 0x10B1CBB4
	// static ...; // 0x10B1CBAE
	// static ...; // 0x10B1CB9D
	// static ...; // 0x10B1CB94
	// static ...; // 0x10B1CAB0
	// static ...; // 0x10B1CAA8
	// std::string const &inDataBuffer;
	// std::string xnkid;
	// bool authenticated;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> s;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// std::string eldewritoVersion;
	// std::string mapName;
	// e_game_engine_type variantType;
	// std::string xnaddr;
	// std::string gameVersion;
	// Blam::Network::Session *session;
	// std::string response;
	// std::wstring mapVariantName;
	// std::wstring variantName;
	// std::string status;
	// e_game_mode gameMode;
	{
		// std::string authString;
	}
	{
		// std::string modHash;
		// unsigned __int32 playerInfoBase;
		// c_mod_package_manager::s_entry packageEntry;
		// unsigned __int32 playerStatusBase;
		// __int32 peerIdx;
		{
			// unsigned __int32 *scores;
			{
				// __int32 t;
			}
		}
		{
			// __int32 playerIdx;
			{
				// Blam::Network::PlayerSession *player;
				// s_player_emblem_configuration config;
				// std::string emblem;
				// std::stringstream color;
				// unsigned char alive;
				// char uid[17];
				// s_game_results_player_statistics *player_stats;
				// std::string name;
				// unsigned short team;
			}
		}
	}
	// function call : s_game_options *(*)()
	todo("implement");
	std::string __result = _sub_10B1B3F0(inDataBuffer);
	return __result;
}

extern std::string _sub_10B1DAF0();
std::string GenerateModList() // 0x10B1DAF0
{
	// `anonymous-namespace'::GenerateModList
	// procedure flags: nofpo
	// static ...; // 0x10B1E264
	// static ...; // 0x10B1E25D
	// static ...; // 0x10B1E256
	// static ...; // 0x10B1E249
	// static ...; // 0x10B1E245
	// static ...; // 0x10B1E239
	// static ...; // 0x10B1E22A
	// static ...; // 0x10B1E225
	// static ...; // 0x10B1E21C
	// static ...; // 0x10B1E1B0
	// static ...; // 0x10B1E1A8
	// c_mod_package_manager::c_threadsafe_iterator it;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// bool has_server_package_list;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// c_mod_package_manager &package_manager;
	// bool file_server_enabled;
	{
		// std::string key;
		// std::string hash_encoded;
		// std::string package_url;
		// s_mod_server_package_entry server_package;
		{
			// std::filesystem::path path;
			// std::string filename;
		}
	}
	todo("implement");
	std::string __result = _sub_10B1DAF0();
	return __result;
}

_extern bool _sub_10B1E470(std::string const &, HttpRequestLine *);
bool ParseHttpRequestLine(std::string const &rawline, HttpRequestLine *outRequestLine) // 0x10B1E470
{
	// `anonymous-namespace'::ParseHttpRequestLine
	// static ...; // 0x10B1E778
	// static ...; // 0x10B1E770
	// std::string const &rawline;
	// HttpRequestLine *outRequestLine;
	// constexpr ParseHttpRequestLine::__l2::s_state STATE_PROTOCOL_VERSION; // constant == 2
	// constexpr ParseHttpRequestLine::__l2::s_state STATE_END; // constant == 3
	// std::stringstream buff;
	// ParseHttpRequestLine::__l2::s_state state;
	// constexpr ParseHttpRequestLine::__l2::s_state STATE_METHOD_TOKEN; // constant == 0
	// constexpr ParseHttpRequestLine::__l2::s_state STATE_REQUEST_URI; // constant == 1
	{
		// __int32 i;
		{
			// char c;
		}
	}
	todo("implement");
	bool __result = _sub_10B1E470(rawline, outRequestLine);
	return __result;
}

extern std::string _sub_10B1AF30(std::string const &, std::string const &, std::string const &, std::string const &);
std::string BuildHttpResponse(std::string const &status, std::string const &contentType, std::string const &content, std::string const &additionalHeaders) // 0x10B1AF30
{
	// `anonymous-namespace'::BuildHttpResponse
	// std::string const &additionalHeaders;
	todo("implement");
	std::string __result = _sub_10B1AF30(status, contentType, content, additionalHeaders);
	return __result;
}

extern std::string _sub_10B1D250(std::string const &);
std::string BuildInfoServerResponse(std::string const &rawRequest) // 0x10B1D250
{
	// `anonymous-namespace'::BuildInfoServerResponse
	// static ...; // 0x10B1D45C
	// static ...; // 0x10B1D450
	// static ...; // 0x10B1D448
	// std::string const &rawRequest;
	// long long curTime;
	// std::string const &replyData;
	todo("implement");
	std::string __result = _sub_10B1D250(rawRequest);
	return __result;
}

// mangled_x86(MANGLED_DEFAULT, "??0HttpRequestLine@hades_file_local@@QAE@XZ"); no body to assert in
_inline HttpRequestLine::HttpRequestLine() = default; // 0x10B1ACC0

// mangled_x86(MANGLED_DEFAULT, "??1HttpRequestLine@hades_file_local@@QAE@XZ"); no body to assert in
_inline HttpRequestLine::~HttpRequestLine() = default; // 0x10B1AD30

extern std::string _sub_10B1D4F0(std::string const &);
std::string BuildModsServerResponse(std::string const &rawRequest) // 0x10B1D4F0
{
	// `anonymous-namespace'::BuildModsServerResponse
	// static ...; // 0x10B1D870
	// static ...; // 0x10B1D864
	// static ...; // 0x10B1D85C
	// std::string const &rawRequest;
	// bool authenticated;
	{
		// std::string authString;
	}
	todo("implement");
	std::string __result = _sub_10B1D4F0(rawRequest);
	return __result;
}

extern std::string _sub_10B1D960(std::string const &);
std::string BuildNotFoundResponse(std::string const &rawRequest) // 0x10B1D960
{
	// `anonymous-namespace'::BuildNotFoundResponse
	// std::string const &rawRequest;
	todo("implement");
	std::string __result = _sub_10B1D960(rawRequest);
	return __result;
}

extern std::string _sub_10B1ADA0(std::string const &);
std::string BuildBadRequestResponse(std::string const &rawRequest) // 0x10B1ADA0
{
	// `anonymous-namespace'::BuildBadRequestResponse
	// std::string const &rawRequest;
	todo("implement");
	std::string __result = _sub_10B1ADA0(rawRequest);
	return __result;
}
