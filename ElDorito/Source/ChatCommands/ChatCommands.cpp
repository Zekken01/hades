/* ---------- headers */

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
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
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
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Modules/ModuleServer.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
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
struct lambda_1;
struct s_damage_data;
struct s_damage_reporting_info;
struct s_file_reference;
struct s_mod_origin_info;
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

/* ---------- globals */

namespace Utils
{
	Modules::ModuleServer *Utils::Singleton<Modules::ModuleServer>::m_instance; // 0x11387E7C
}

/* ---------- private variables */

namespace Server
{
	namespace
	{
		extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > DefaultBanListPath; // 0x11387E58
	}
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

extern c_mod_package_manager::mod_type* _sub_106CD920(c_mod_package_manager::mod_type *const);
_inline c_mod_package_manager::mod_type::mod_type() // 0x106CD920
{
	mangled_x86(MANGLED_TODO, "??0mod_type@c_mod_package_manager@@QAE@XZ");
	// c_mod_package_manager::mod_type *const this;
	compiler_generated();
	todo("implement");
	_sub_106CD920(this);
}

extern s_damage_data* _sub_106CD990(s_damage_data *const);
_inline s_damage_data::s_damage_data() // 0x106CD990
{
	mangled_x86(MANGLED_TODO, "??0s_damage_data@@QAE@XZ");
	// s_damage_data *const this;
	compiler_generated();
	todo("implement");
	_sub_106CD990(this);
}

extern s_damage_reporting_info* _sub_106CD9F0(s_damage_reporting_info *const);
_inline s_damage_reporting_info::s_damage_reporting_info() // 0x106CD9F0
{
	mangled_x86(MANGLED_TODO, "??0s_damage_reporting_info@@QAE@XZ");
	// s_damage_reporting_info *const this;
	compiler_generated();
	todo("implement");
	_sub_106CD9F0(this);
}

extern c_mod_package_manager::s_entry* _sub_106CDA40(c_mod_package_manager::s_entry *const);
_inline c_mod_package_manager::s_entry::s_entry() // 0x106CDA40
{
	mangled_x86(MANGLED_TODO, "??0s_entry@c_mod_package_manager@@QAE@XZ");
	// c_mod_package_manager::s_entry *const this;
	compiler_generated();
	todo("implement");
	_sub_106CDA40(this);
}

extern s_file_reference* _sub_106CDAC0(s_file_reference *const);
_inline s_file_reference::s_file_reference() // 0x106CDAC0
{
	mangled_x86(MANGLED_TODO, "??0s_file_reference@@QAE@XZ");
	// s_file_reference *const this;
	compiler_generated();
	todo("implement");
	_sub_106CDAC0(this);
}

extern s_mod_origin_info* _sub_106CDB20(s_mod_origin_info *const);
_inline s_mod_origin_info::s_mod_origin_info() // 0x106CDB20
{
	mangled_x86(MANGLED_TODO, "??0s_mod_origin_info@@QAE@XZ");
	// s_mod_origin_info *const this;
	compiler_generated();
	todo("implement");
	_sub_106CDB20(this);
}

_extern void _sub_106CDE70(c_mod_package_manager::s_entry *const);
_inline c_mod_package_manager::s_entry::~s_entry() // 0x106CDE70
{
	mangled_x86(MANGLED_TODO, "??1s_entry@c_mod_package_manager@@QAE@XZ");
	// c_mod_package_manager::s_entry *const this;
	compiler_generated();
	todo("implement");
	_sub_106CDE70(this);
}

_extern void _sub_106CDED0(s_mod_origin_info *const);
_inline s_mod_origin_info::~s_mod_origin_info() // 0x106CDED0
{
	mangled_x86(MANGLED_TODO, "??1s_mod_origin_info@@QAE@XZ");
	// s_mod_origin_info *const this;
	compiler_generated();
	todo("implement");
	_sub_106CDED0(this);
}

/* ---------- private code */
