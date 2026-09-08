/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Modules/ModuleServer.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Player/PlayerCustomization.hpp"
#include "Server/BanList.hpp"
#include "Server/ServerChat.hpp"
#include "Server/StatsServerBanList.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <ios>
#include <iosfwd>
#include <limits>
#include <list>
#include <map>
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
#include <unordered_set>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_mod_package_manager;
class c_network_session;
class c_network_session_membership;
struct begin;
struct c_game_engine;
struct end;
struct lambda_1;
struct s_damage_data;
struct s_damage_reporting_info;
struct s_file_reference;
struct s_mod_origin_info;
struct s_network_session_player;
struct s_player_datum;
struct s_player_identifier;
namespace Blam
{
	namespace Network
	{
		struct PlayerSession;
		struct Session;
	}
}
namespace Modules
{
	class ModuleServer;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace ChatCommands {}
using namespace ::ChatCommands;
namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace ReportHandler {}
	using namespace Server::ReportHandler;
	namespace Chat {}
	using namespace Server::Chat;
}

namespace Modules {}
using namespace ::Modules;
namespace Objects {}
using namespace ::Objects;
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

/* ---------- definitions */

//class CommandKill::__l2::<lambda_1>
//{
//public:
//	void operator()() const;
//	<lambda_1>(CommandKill::__l2::<lambda_1> &);
//	<lambda_1>(unsigned long, __int32 const &);
//private:
//	unsigned long unitIndex; // 0x0
//	__int32 peer; // 0x4
//public:
//	CommandKill::__l2::<lambda_1> &operator=(CommandKill::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(CommandKill::__l2::<lambda_1>) == 8, "Invalid CommandKill::__l2::<lambda_1> size");

/* ---------- prototypes */

namespace ChatCommands
{
	extern void RegisterCommands();
}

__int32 FindPlayerInGameWithIdentifier(s_player_identifier const &identifier);
__int32 FindNetworkPlayerInGame(char networkPlayerIndex);
bool CommandHelp(__int32 peer, std::vector<std::string,std::allocator<std::string> > const &args, std::string &returnValue);
bool ComamndListPlayers(__int32 peer, std::vector<std::string,std::allocator<std::string> > const &args, std::string &returnValue);
bool CommandReportPlayer(__int32 peer, std::vector<std::string,std::allocator<std::string> > const &args, std::string &returnValue);
bool CommandKill(__int32 peer, std::vector<std::string,std::allocator<std::string> > const &args, std::string &returnValue);
bool ComamndModInfo(__int32 peer, std::vector<std::string,std::allocator<std::string> > const &args, std::string &returnValue);

/* ---------- globals */

namespace Utils
{
	Modules::ModuleServer *Utils::Singleton<Modules::ModuleServer>::m_instance; // 0x11387E7C
}

/* ---------- private variables */

namespace Server
{
	namespace hades_file_local_Server
	{
		extern std::string DefaultBanListPath; // 0x11387E58
	}
	using namespace hades_file_local_Server;
}
/* ---------- public code */

namespace ChatCommands
{
	_extern void _sub_106CFAB0();
	void RegisterCommands() // 0x106CFAB0
	{
		mangled_x86(MANGLED_TODO, "?RegisterCommands@ChatCommands@@YAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_106CFAB0();
	}
}

_inline c_mod_package_manager::mod_type::mod_type() // 0x106CD920
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0mod_type@c_mod_package_manager@@QAE@XZ");
	// c_mod_package_manager::mod_type *const this;

	compiler_generated();
}

_inline s_damage_data::s_damage_data() // 0x106CD990
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_damage_data@@QAE@XZ");
	// s_damage_data *const this;

	compiler_generated();
}

_inline s_damage_reporting_info::s_damage_reporting_info() // 0x106CD9F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_damage_reporting_info@@QAE@XZ");
	// s_damage_reporting_info *const this;

	compiler_generated();
}

_inline c_mod_package_manager::s_entry::s_entry() // 0x106CDA40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_entry@c_mod_package_manager@@QAE@XZ");
	// c_mod_package_manager::s_entry *const this;

	compiler_generated();
}

_inline s_file_reference::s_file_reference() // 0x106CDAC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_file_reference@@QAE@XZ");
	// s_file_reference *const this;

	compiler_generated();
}

_inline s_mod_origin_info::s_mod_origin_info() // 0x106CDB20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_mod_origin_info@@QAE@XZ");
	// s_mod_origin_info *const this;

	compiler_generated();
}

_inline c_mod_package_manager::s_entry::~s_entry() // 0x106CDE70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1s_entry@c_mod_package_manager@@QAE@XZ");
	// c_mod_package_manager::s_entry *const this;

	compiler_generated();
}

_inline s_mod_origin_info::~s_mod_origin_info() // 0x106CDED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1s_mod_origin_info@@QAE@XZ");
	// s_mod_origin_info *const this;

	compiler_generated();
}

/* ---------- private code */

_extern __int32 _sub_106CF7B0(s_player_identifier const &);
__int32 FindPlayerInGameWithIdentifier(s_player_identifier const &identifier) // 0x106CF7B0
{
	// `anonymous-namespace'::FindPlayerInGameWithIdentifier
	// static ...; // 0x106CF888
	// static ...; // 0x106CF87C
	// static ...; // 0x106CF874
	// s_player_identifier const &identifier;
	// c_data_array<s_player_datum> *players;
	{
		// c_data_iterator<s_player_datum> it;
	}
	// function call : bool (*const)()
	todo("implement");
	__int32 __result = _sub_106CF7B0(identifier);
	return __result;
}

_extern __int32 _sub_106CF690(char);
__int32 FindNetworkPlayerInGame(char networkPlayerIndex) // 0x106CF690
{
	// `anonymous-namespace'::FindNetworkPlayerInGame
	// static ...; // 0x106CF764
	// static ...; // 0x106CF758
	// static ...; // 0x106CF750
	// char networkPlayerIndex;
	// c_network_session_membership *membership;
	// s_network_session_player *networkPlayer;
	// c_network_session *session;
	// function call : bool (*const)(c_network_session **)
	todo("implement");
	__int32 __result = _sub_106CF690(networkPlayerIndex);
	return __result;
}

_extern bool _sub_106CF180(__int32, std::vector<std::string,std::allocator<std::string> > const &, std::string &);
bool CommandHelp(__int32 peer, std::vector<std::string,std::allocator<std::string> > const &args, std::string &returnValue) // 0x106CF180
{
	// `anonymous-namespace'::CommandHelp
	// static ...; // 0x106CF280
	// static ...; // 0x106CF278
	// __int32 peer;
	// std::vector<std::string,std::allocator<std::string> > const &args;
	// std::string &returnValue;
	{
		// std::vector<std::string,std::allocator<std::string> > &<range>$L0;
		// std::string *<begin>$L0;
		// std::string *<end>$L0;
		{
			// std::string i;
		}
	}
	todo("implement");
	bool __result = _sub_106CF180(peer, args, returnValue);
	return __result;
}

_extern bool _sub_106CE6E0(__int32, std::vector<std::string,std::allocator<std::string> > const &, std::string &);
bool ComamndListPlayers(__int32 peer, std::vector<std::string,std::allocator<std::string> > const &args, std::string &returnValue) // 0x106CE6E0
{
	// `anonymous-namespace'::ComamndListPlayers
	// std::string &returnValue;
	// Blam::Network::Session *session;
	// __int32 peerIdx;
	{
		// __int32 playerIdx;
		{
			// Blam::Network::PlayerSession *player;
		}
	}
	todo("implement");
	bool __result = _sub_106CE6E0(peer, args, returnValue);
	return __result;
}

_extern bool _sub_106CF550(__int32, std::vector<std::string,std::allocator<std::string> > const &, std::string &);
bool CommandReportPlayer(__int32 peer, std::vector<std::string,std::allocator<std::string> > const &args, std::string &returnValue) // 0x106CF550
{
	// `anonymous-namespace'::CommandReportPlayer
	// std::string &returnValue;
	todo("implement");
	bool __result = _sub_106CF550(peer, args, returnValue);
	return __result;
}

_extern bool _sub_106CF2F0(__int32, std::vector<std::string,std::allocator<std::string> > const &, std::string &);
bool CommandKill(__int32 peer, std::vector<std::string,std::allocator<std::string> > const &args, std::string &returnValue) // 0x106CF2F0
{
	// `anonymous-namespace'::CommandKill
	// std::string &returnValue;
	// s_player_datum *player;
	// __int32 playerIndex;
	// __int32 networkPlayerIndex;
	// Blam::Network::Session *session;
	// function call : bool (*const)()
	// function call : c_game_engine *(*const)()
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_106CF2F0(peer, args, returnValue);
	return __result;
}

_extern bool _sub_106CEA80(__int32, std::vector<std::string,std::allocator<std::string> > const &, std::string &);
bool ComamndModInfo(__int32 peer, std::vector<std::string,std::allocator<std::string> > const &args, std::string &returnValue) // 0x106CEA80
{
	// `anonymous-namespace'::ComamndModInfo
	// static ...; // 0x106CEFF9
	// static ...; // 0x106CEFF4
	// static ...; // 0x106CEFEC
	// static ...; // 0x106CEFB0
	// static ...; // 0x106CEFA8
	// __int32 peer;
	// std::vector<std::string,std::allocator<std::string> > const &args;
	// std::string &returnValue;
	// char buffer[32];
	// std::string desc;
	// bool hasModSet;
	// std::string modhash;
	// c_mod_package_manager::s_entry mod_package;
	// std::string message;
	// tm *convertedLocal;
	todo("implement");
	bool __result = _sub_106CEA80(peer, args, returnValue);
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Modules::ModuleServer & Utils::Singleton<Modules::ModuleServer>::Instance();
template bool c_data_iterator<s_player_datum>::operator!=(c_data_iterator<s_player_datum> const &) const;
template bool c_data_iterator<s_player_datum>::operator==(c_data_iterator<s_player_datum> const &) const;
template bool c_tag_block<s_game_globals_falling_damage>::try_get_element(__int32, s_game_globals_falling_damage **) const;
template c_data_iterator<s_player_datum> & c_data_iterator<s_player_datum>::operator++();
template c_data_iterator<s_player_datum> c_data_array<s_player_datum>::begin();
template c_data_iterator<s_player_datum> c_data_array<s_player_datum>::end();
template c_data_iterator<s_player_datum>::c_data_iterator(s_data_array *);
template c_enum<enum e_damage_reporting_type,short> & c_enum<enum e_damage_reporting_type,short>::operator=(e_damage_reporting_type const &);
template c_enum<enum e_damage_reporting_type,short>::c_enum();
template c_enum<enum e_file_reference_location,short>::c_enum();
template c_enum<enum e_file_reference_location,short>::c_enum(c_enum<enum e_file_reference_location,short> const &);
template c_enum<enum e_file_reference_location,short>::c_enum(e_file_reference_location const &);
template c_enum<enum e_file_reference_location,short>::c_enum(short const &);
template c_flags<enum e_file_reference_flags,unsigned short>::c_flags();
template s_game_globals_falling_damage * c_tag_block<s_game_globals_falling_damage>::get_element(__int32) const;
template s_game_globals_falling_damage * c_tag_block<s_game_globals_falling_damage>::operator->();
template s_player_datum & c_data_iterator<s_player_datum>::next();
template s_player_datum * c_data_iterator<s_player_datum>::operator->();
