/* ---------- headers */

#include "Modules/ModuleServer.hpp"
#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/cseries/static_string.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "Console/Console.hpp"
#include "ElDorito.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patches/Network.hpp"
#include "Pointer.hpp"
#include "Server/BanList.hpp"
#include "Server/Connect/ServerConnect.hpp"
#include "Server/Connect/ServerConnectDefintiions.hpp"
#include "Server/ServerChat.hpp"
#include "Server/StatsServerBanList.hpp"
#include "Server/Voting/VotingPackets.hpp"
#include "Server/Voting/VotingTypes.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/DewritoReader.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <WinSock2.h>
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
#include <bitset>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <functional>
#include <initializer_list>
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
#include <random>
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
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_mod_package_manager;
struct SServerConnectOptions;
namespace Modules
{
	class ModuleBase;
	class ModuleServer;
	struct Command;
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
	namespace VariableSynchronization {}
	using namespace Server::VariableSynchronization;
	namespace Signaling {}
	using namespace Server::Signaling;
	namespace InfoServer {}
	using namespace Server::InfoServer;
	namespace Stats {}
	using namespace Server::Stats;
	namespace Chat {}
	using namespace Server::Chat;
	namespace Voting {}
	using namespace Server::Voting;
}

namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Ui {}
	using namespace Web::Ui;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Sprint {}
	using namespace Patches::Sprint;
	namespace Weapon {}
	using namespace Patches::Weapon;
	namespace PlayerUid {}
	using namespace Patches::PlayerUid;
	namespace Assassination {}
	using namespace Patches::Assassination;
	namespace Tweaks {}
	using namespace Patches::Tweaks;
}

namespace Console {}
using namespace ::Console;
namespace PersistentMemory {}
using namespace ::PersistentMemory;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

namespace
{
	enum KickType
	{
		Kick = 0,
		Ban,
		TempBan,
	};
}
/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

namespace Server
{
	namespace
	{
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > DefaultBanListPath; // 0x12456040
	}
}
namespace Server
{
	namespace Voting
	{
		namespace
		{
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const DefaultTypes[8]; // 0x12455E80
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const DefaultTypeNames[8]; // 0x12455F60
		}
	}
}
namespace
{
	extern unsigned short PingId; // 0x1245605C
}
/* ---------- public code */

namespace Modules
{
	extern ModuleServer* _sub_109FE0E0(Modules::ModuleServer *const);
	ModuleServer::ModuleServer() : ModuleBase(todo_result<std::basic_string<char,std::char_traits<char>,std::allocator<char> >>()) // 0x109FE0E0
	{
		mangled_x86(MANGLED_TODO, "??0ModuleServer@Modules@@QAE@XZ");
		// Modules::ModuleServer *const this;
		// Modules::Command *syncTestServer;
		// Modules::Command *syncTestClient;
		todo("implement");
		_sub_109FE0E0(this);
	}
}

extern SServerConnectOptions* _sub_10A06DC0(SServerConnectOptions *const);
_inline SServerConnectOptions::SServerConnectOptions() // 0x10A06DC0
{
	mangled_x86(MANGLED_TODO, "??0SServerConnectOptions@@QAE@XZ");
	// SServerConnectOptions *const this;
	compiler_generated();
	todo("implement");
	_sub_10A06DC0(this);
}

_extern void _sub_10A07290(SServerConnectOptions *const);
_inline SServerConnectOptions::~SServerConnectOptions() // 0x10A07290
{
	mangled_x86(MANGLED_TODO, "??1SServerConnectOptions@@QAE@XZ");
	// SServerConnectOptions *const this;
	compiler_generated();
	todo("implement");
	_sub_10A07290(this);
}

_extern void _sub_10A073C0(c_mod_package_manager::c_threadsafe_iterator *const);
_inline c_mod_package_manager::c_threadsafe_iterator::~c_threadsafe_iterator() // 0x10A073C0
{
	mangled_x86(MANGLED_TODO, "??1c_threadsafe_iterator@c_mod_package_manager@@QAE@XZ");
	// c_mod_package_manager::c_threadsafe_iterator *const this;
	compiler_generated();
	todo("implement");
	_sub_10A073C0(this);
}

namespace Modules
{
	_extern void _sub_10A186A0(Modules::ModuleServer *const);
	void ModuleServer::refreshServerFilters() // 0x10A186A0
	{
		mangled_x86(MANGLED_TODO, "?refreshServerFilters@ModuleServer@Modules@@QAEXXZ");
		// static ...; // 0x10A18ED5
		// static ...; // 0x10A18ECC
		// static ...; // 0x10A18EC7
		// static ...; // 0x10A18EC2
		// static ...; // 0x10A18EBD
		// static ...; // 0x10A18EB5
		// static ...; // 0x10A18EAD
		// static ...; // 0x10A18EAB
		// static ...; // 0x10A18EA4
		// static ...; // 0x10A18E38
		// static ...; // 0x10A18E30
		// Modules::ModuleServer *const this;
		// std::basic_ifstream<char,std::char_traits<char> > in;
		{
			// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> json;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > contents;
			{
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &namesArray;
				{
					// unsigned __int32 i;
					{
						// std::basic_string<char,std::char_traits<char>,std::allocator<char> > name;
					}
				}
			}
			{
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &wordsArray;
				{
					{
						// std::basic_string<char,std::char_traits<char>,std::allocator<char> > word;
					}
				}
			}
			{
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &patternArray;
				{
					{
						// std::basic_string<char,std::char_traits<char>,std::allocator<char> > pattern;
					}
				}
			}
			{
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > &replacementWord;
			}
		}
		{
			// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> s;
			// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
			// std::basic_ofstream<char,std::char_traits<char> > outFile;
		}
		todo("implement");
		_sub_10A186A0(this);
	}
}

extern std::unordered_set<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > _sub_10A139E0(Modules::ModuleServer *const);
namespace Modules
{
	std::unordered_set<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > ModuleServer::GetFilteredWordsList() // 0x10A139E0
	{
		mangled_x86(MANGLED_TODO, "?GetFilteredWordsList@ModuleServer@Modules@@QAE?AV?$unordered_set@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$hash@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@U?$equal_to@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@XZ");
		// Modules::ModuleServer *const this;
		todo("implement");
		std::unordered_set<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > __result = _sub_10A139E0(this);
		return __result;
	}
}

extern std::unordered_set<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > _sub_10A13960(Modules::ModuleServer *const);
namespace Modules
{
	std::unordered_set<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > ModuleServer::GetFilteredPatternsList() // 0x10A13960
	{
		mangled_x86(MANGLED_TODO, "?GetFilteredPatternsList@ModuleServer@Modules@@QAE?AV?$unordered_set@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$hash@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@U?$equal_to@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@XZ");
		// Modules::ModuleServer *const this;
		todo("implement");
		std::unordered_set<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > __result = _sub_10A13960(this);
		return __result;
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10A138E0(Modules::ModuleServer *const);
namespace Modules
{
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > ModuleServer::GetFilterReplacementWord() // 0x10A138E0
	{
		mangled_x86(MANGLED_TODO, "?GetFilterReplacementWord@ModuleServer@Modules@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// Modules::ModuleServer *const this;
		todo("implement");
		std::string __result = _sub_10A138E0(this);
		return __result;
	}
}

/* ---------- private code */
