/* ---------- headers */

#include "mods/mod_system.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/networking/session/network_session_parameter_mod.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/networking/session/network_session_parameters_custom.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/FileSystem/ModPackageFileSystemViewManager.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/mod_package_updater.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/new/ModListenerSet.hpp"
#include "mods/new/ModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patches/CustomPackets.hpp"
#include "Utils/EventSink.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

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
#include <charconv>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <functional>
#include <ios>
#include <iosfwd>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <optional>
#include <ostream>
#include <queue>
#include <ratio>
#include <shared_mutex>
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
#include <utility>
#include <vector>

/* ---------- forward declarations */

class CModPackageFileSystemView;
class IMod;
class IModManager;
class ModManager;
class c_file_reference;
class c_mod_package;
class c_mod_package_manager;
class c_mod_package_updater_blocking;
struct begin;
struct c_mod_system;
struct end;
struct lambda_1;
struct s_mod_server_package_entry;
struct s_mod_system_globals;
struct s_session_mod_options;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

// s_mod_system_globals is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

//class c_mod_system::find_server_package_by_name::__l2::<lambda_1>
//{
//public:
//	<lambda_1>(c_mod_system::find_server_package_by_name::__l2::<lambda_1> &);
//	<lambda_1>(char const *const &);
//private:
//	char const *name; // 0x0
//public:
//	c_mod_system::find_server_package_by_name::__l2::<lambda_1> &operator=(c_mod_system::find_server_package_by_name::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(c_mod_system::find_server_package_by_name::__l2::<lambda_1>) == 4, "Invalid c_mod_system::find_server_package_by_name::__l2::<lambda_1> size");

namespace Download
{

}

/* ---------- prototypes */

extern "C" bool update_packages();
extern "C" bool create_package_directory();
extern "C" bool load_package_file_internal(char const *file_path);
extern "C" bool load_package_by_string_hash(char const *hash_str);
extern "C" bool mod_system_load_named_package(char const *name);
extern "C" __int32 FormatFilename(char *str, __int32 length);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern s_mod_system_globals g_mod_system_globals; // 0x12407EC0
	extern char const *k_package_directory; // 0x11352BB4
}
using namespace hades_file_local;
/* ---------- public code */

_extern void _sub_108BC8E0(bool);
void c_mod_system::initialize(bool is_dedicated_server) // 0x108BC8E0
{
	mangled_x86(MANGLED_TODO, "?initialize@c_mod_system@@SAX_N@Z");
	// bool is_dedicated_server;
	todo("implement");
	_sub_108BC8E0(is_dedicated_server);
}

_extern void _sub_108BD580();
void c_mod_system::update() // 0x108BD580
{
	mangled_x86(MANGLED_TODO, "?update@c_mod_system@@SAXXZ");
	// procedure flags: nofpo
	// function call : void ()
	todo("implement");
	_sub_108BD580();
}

extern char const *_sub_108BC5E0();
char const *c_mod_system::get_package_directory() // 0x108BC5E0
{
	mangled_x86(MANGLED_TODO, "?get_package_directory@c_mod_system@@SAPBDXZ");
	// procedure flags: nofpo
	todo("implement");
	char const * __result = _sub_108BC5E0();
	return __result;
}

_extern bool _sub_108BD4F0();
bool c_mod_system::unload_current_package() // 0x108BD4F0
{
	mangled_x86(MANGLED_TODO, "?unload_current_package@c_mod_system@@SA_NXZ");
	// procedure flags: nofpo
	// function call : EModResult (EModIndex, char const *, bool)
	todo("implement");
	bool __result = _sub_108BD4F0();
	return __result;
}

extern std::string _sub_108BC040(char const *);
std::string c_mod_system::get_mod_hash_by_identifier(char const *identifier) // 0x108BC040
{
	mangled_x86(MANGLED_TODO, "?get_mod_hash_by_identifier@c_mod_system@@SA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PBD@Z");
	// static ...; // 0x108BC2B9
	// static ...; // 0x108BC2AC
	// static ...; // 0x108BC2A4
	// static ...; // 0x108BC280
	// static ...; // 0x108BC278
	// char const *identifier;
	// s_mod_server_package_entry server_package;
	{
		// c_mod_package_manager::s_entry packageEntry;
		// c_mod_package_manager const &manager;
		{
			// std::string hashstr;
		}
	}
	todo("implement");
	std::string __result = _sub_108BC040(identifier);
	return __result;
}

_extern bool _sub_108BC370(char const *, c_mod_package_manager::s_entry *);
bool c_mod_system::get_mod_info_by_hash(char const *hash_str, c_mod_package_manager::s_entry *package_entry) // 0x108BC370
{
	mangled_x86(MANGLED_TODO, "?get_mod_info_by_hash@c_mod_system@@SA_NPBDPAUs_entry@c_mod_package_manager@@@Z");
	// static ...; // 0x108BC444
	// static ...; // 0x108BC43C
	// char const *hash_str;
	// c_mod_package_manager::s_entry *package_entry;
	// unsigned char hash[20];
	// c_mod_package_manager &package_manager;
	todo("implement");
	bool __result = _sub_108BC370(hash_str, package_entry);
	return __result;
}

_extern bool _sub_108BC490(char const *, c_mod_package_manager::s_entry *);
bool c_mod_system::get_mod_info_by_identifier(char const *identifier, c_mod_package_manager::s_entry *package_entry) // 0x108BC490
{
	mangled_x86(MANGLED_TODO, "?get_mod_info_by_identifier@c_mod_system@@SA_NPBDPAUs_entry@c_mod_package_manager@@@Z");
	// static ...; // 0x108BC584
	// static ...; // 0x108BC57C
	// char const *identifier;
	// c_mod_package_manager::s_entry *package_entry;
	// std::string hash_str;
	todo("implement");
	bool __result = _sub_108BC490(identifier, package_entry);
	return __result;
}

_extern bool _sub_108BC960(char const *);
bool c_mod_system::load_package_by_identifier(char const *identifier) // 0x108BC960
{
	mangled_x86(MANGLED_TODO, "?load_package_by_identifier@c_mod_system@@SA_NPBD@Z");
	// static ...; // 0x108BCB64
	// static ...; // 0x108BCB58
	// static ...; // 0x108BCB50
	// char const *identifier;
	{
		// std::filesystem::path path;
		// c_mod_package_manager &package_manager;
	}
	todo("implement");
	bool __result = _sub_108BC960(identifier);
	return __result;
}

extern std::string _sub_108BBEC0();
std::string c_mod_system::get_current_package_hash() // 0x108BBEC0
{
	mangled_x86(MANGLED_TODO, "?get_current_package_hash@c_mod_system@@SA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// procedure flags: nofpo
	// static ...; // 0x108BBFE0
	// static ...; // 0x108BBFD4
	// static ...; // 0x108BBFCC
	// std::string hashstr;
	// s_session_mod_options const *mod_options;
	todo("implement");
	std::string __result = _sub_108BBEC0();
	return __result;
}

extern std::string _sub_108BB9A0();
std::string c_mod_system::get_current_mainmenu_package_hash() // 0x108BB9A0
{
	mangled_x86(MANGLED_TODO, "?get_current_mainmenu_package_hash@c_mod_system@@SA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// procedure flags: nofpo
	// static ...; // 0x108BBB38
	// static ...; // 0x108BBB2C
	// static ...; // 0x108BBB24
	// IMod *mod;
	{
		// c_mod_package *package;
		// std::string hash_str;
	}
	// function call : IMod *(EModIndex) const
	// function call : c_mod_package *(bool) const
	todo("implement");
	std::string __result = _sub_108BB9A0();
	return __result;
}

extern std::string _sub_108BBBB0(EModIndex);
std::string c_mod_system::get_current_package_filename(EModIndex package_type) // 0x108BBBB0
{
	mangled_x86(MANGLED_TODO, "?get_current_package_filename@c_mod_system@@SA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@W4EModIndex@@@Z");
	// static ...; // 0x108BBE1C
	// static ...; // 0x108BBE10
	// static ...; // 0x108BBE08
	// EModIndex package_type;
	// IMod *mod;
	{
		// c_mod_package *package;
		// c_mod_package_manager::s_entry entry;
	}
	// function call : IMod *(EModIndex) const
	// function call : c_mod_package *(bool) const
	todo("implement");
	std::string __result = _sub_108BBBB0(package_type);
	return __result;
}

extern c_mod_package_manager &_sub_108BC850();
c_mod_package_manager &c_mod_system::get_package_manager() // 0x108BC850
{
	mangled_x86(MANGLED_TODO, "?get_package_manager@c_mod_system@@SAAAVc_mod_package_manager@@XZ");
	// procedure flags: nofpo
	todo("implement");
	c_mod_package_manager & __result = _sub_108BC850();
	return __result;
}

_extern bool _sub_108BB5C0(std::string const &, s_mod_server_package_entry *);
bool c_mod_system::find_server_package_by_hash(std::string const &hash, s_mod_server_package_entry *entry) // 0x108BB5C0
{
	mangled_x86(MANGLED_TODO, "?find_server_package_by_hash@c_mod_system@@SA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAUs_mod_server_package_entry@@@Z");
	// static ...; // 0x108BB6F8
	// static ...; // 0x108BB6F0
	// std::string const &hash;
	// s_mod_server_package_entry *entry;
	{
		// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<std::string const ,s_mod_server_package_entry> > > > it;
	}
	todo("implement");
	bool __result = _sub_108BB5C0(hash, entry);
	return __result;
}

_extern bool _sub_108BB760(char const *, s_mod_server_package_entry *);
bool c_mod_system::find_server_package_by_name(char const *name, s_mod_server_package_entry *entry) // 0x108BB760
{
	mangled_x86(MANGLED_TODO, "?find_server_package_by_name@c_mod_system@@SA_NPBDPAUs_mod_server_package_entry@@@Z");
	// static ...; // 0x108BB914
	// static ...; // 0x108BB90C
	// char const *name;
	// s_mod_server_package_entry *entry;
	// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<std::string const ,s_mod_server_package_entry> > > > it;
	todo("implement");
	bool __result = _sub_108BB760(name, entry);
	return __result;
}

_extern bool _sub_108BC870();
bool c_mod_system::has_server_package_list() // 0x108BC870
{
	mangled_x86(MANGLED_TODO, "?has_server_package_list@c_mod_system@@SA_NXZ");
	// procedure flags: nofpo
	todo("implement");
	bool __result = _sub_108BC870();
	return __result;
}

extern std::unordered_map<std::string,CModPackageFileSystemView::SFileEntry,std::hash<std::string>,std::equal_to<std::string>,std::allocator<std::pair<std::string const ,CModPackageFileSystemView::SFileEntry> > > _sub_108BC600(std::string);
std::unordered_map<std::string,CModPackageFileSystemView::SFileEntry,std::hash<std::string>,std::equal_to<std::string>,std::allocator<std::pair<std::string const ,CModPackageFileSystemView::SFileEntry> > > c_mod_system::get_package_file_list(std::string hash) // 0x108BC600
{
	mangled_x86(MANGLED_TODO, "?get_package_file_list@c_mod_system@@SA?AV?$unordered_map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@USFileEntry@CModPackageFileSystemView@@U?$hash@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@U?$equal_to@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@USFileEntry@CModPackageFileSystemView@@@std@@@2@@std@@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@3@@Z");
	// static ...; // 0x108BC7A5
	// static ...; // 0x108BC7A0
	// static ...; // 0x108BC788
	// static ...; // 0x108BC780
	// std::string hash;
	// std::unordered_map<std::string,CModPackageFileSystemView::SFileEntry,std::hash<std::string>,std::equal_to<std::string>,std::allocator<std::pair<std::string const ,CModPackageFileSystemView::SFileEntry> > > fileList;
	{
		// std::shared_ptr<CModPackageFileSystemView> view;
	}
	todo("implement");
	std::unordered_map<std::string,CModPackageFileSystemView::SFileEntry,std::hash<std::string>,std::equal_to<std::string>,std::allocator<std::pair<std::string const ,CModPackageFileSystemView::SFileEntry> > > __result = _sub_108BC600(hash);
	return __result;
}

extern std::string _sub_108B82B0(std::string, std::string, std::string);
std::string c_mod_system::GetNewPackageFilename(std::string name, std::string hash, std::string version) // 0x108B82B0
{
	mangled_x86(MANGLED_TODO, "?GetNewPackageFilename@c_mod_system@@SA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V23@00@Z");
	// static ...; // 0x108B859C
	// std::string name;
	// std::string hash;
	// std::string version;
	// char buff[32];
	todo("implement");
	std::string __result = _sub_108B82B0(name, hash, version);
	return __result;
}

extern IModManager &_sub_108B81C0();
IModManager &c_mod_system::GetModManager() // 0x108B81C0
{
	mangled_x86(MANGLED_TODO, "?GetModManager@c_mod_system@@SAAAVIModManager@@XZ");
	// procedure flags: nofpo
	// static ModManager manager; // 0x12407F70
	// static __int32 $TSS0; // 0x12407F6C
	todo("implement");
	IModManager & __result = _sub_108B81C0();
	return __result;
}

_inline c_mod_package_updater_blocking::c_mod_package_updater_blocking() // 0x108B6B30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_mod_package_updater_blocking@@QAE@XZ");
	// c_mod_package_updater_blocking *const this;

	compiler_generated();
}

_inline s_mod_server_package_entry::s_mod_server_package_entry(s_mod_server_package_entry &&__that) // 0x108B6B90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_mod_server_package_entry@@QAE@$$QAU0@@Z");
	// s_mod_server_package_entry &__that;

	compiler_generated();
}

_inline s_mod_server_package_entry::s_mod_server_package_entry(s_mod_server_package_entry const &__that) // 0x108B6C40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_mod_server_package_entry@@QAE@ABU0@@Z");
	// s_mod_server_package_entry const &__that;

	compiler_generated();
}

_inline s_mod_server_package_entry::s_mod_server_package_entry() // 0x108B6D40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_mod_server_package_entry@@QAE@XZ");
	// s_mod_server_package_entry *const this;

	compiler_generated();
}

_inline s_mod_system_globals::s_mod_system_globals() // 0x108B6DB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_mod_system_globals@@QAE@XZ");
	// s_mod_system_globals *const this;

	compiler_generated();
}

_inline c_mod_package_updater_blocking::~c_mod_package_updater_blocking() // 0x108B7790
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1c_mod_package_updater_blocking@@QAE@XZ");
	// c_mod_package_updater_blocking *const this;

	compiler_generated();
}

_inline s_mod_server_package_entry::~s_mod_server_package_entry() // 0x108B77F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1s_mod_server_package_entry@@QAE@XZ");
	// s_mod_server_package_entry *const this;

	compiler_generated();
}

_inline s_mod_system_globals::~s_mod_system_globals() // 0x108B7860
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1s_mod_system_globals@@QAE@XZ");
	// s_mod_system_globals *const this;

	compiler_generated();
}

extern s_mod_server_package_entry &_sub_108B79E0(s_mod_server_package_entry *const, s_mod_server_package_entry const &);
_inline s_mod_server_package_entry &s_mod_server_package_entry::operator=(s_mod_server_package_entry const &__that) // 0x108B79E0
{
	mangled_x86(MANGLED_TODO, "??4s_mod_server_package_entry@@QAEAAU0@ABU0@@Z");
	// s_mod_server_package_entry const &__that;
	compiler_generated();
	todo("implement");
	s_mod_server_package_entry & __result = _sub_108B79E0(this, __that);
	return __result;
}

/* ---------- private code */

_extern bool _sub_108BD630();
extern "C" bool update_packages() // 0x108BD630
{
	// update_packages
	// procedure flags: nofpo
	// static ...; // 0x108BD93B
	// static ...; // 0x108BD92E
	// static ...; // 0x108BD926
	// static ...; // 0x108BD920
	// static ...; // 0x108BD8F0
	// static ...; // 0x108BD8E8
	// c_file_reference package_list;
	// c_mod_package_updater_blocking updater;
	// std::string package_list_filename;
	{
		// std::vector<c_mod_package_updater_blocking::s_mod_package_description,std::allocator<c_mod_package_updater_blocking::s_mod_package_description> > const &<range>$L0;
		// c_mod_package_updater_blocking::s_mod_package_description const *<begin>$L0;
		// c_mod_package_updater_blocking::s_mod_package_description const *<end>$L0;
		{
			// c_mod_package_updater_blocking::s_mod_package_description const &package;
			{
				// s_mod_server_package_entry entry;
			}
		}
	}
	todo("implement");
	bool __result = _sub_108BD630();
	return __result;
}

_extern bool _sub_108BB170();
extern "C" bool create_package_directory() // 0x108BB170
{
	// create_package_directory
	// procedure flags: nofpo
	// static ...; // 0x108BB318
	// static ...; // 0x108BB30C
	// static ...; // 0x108BB304
	// std::error_code ec;
	todo("implement");
	bool __result = _sub_108BB170();
	return __result;
}

_extern bool _sub_108BCDC0(char const *);
extern "C" bool load_package_file_internal(char const *file_path) // 0x108BCDC0
{
	// load_package_file_internal
	// char const *file_path;
	// EModResult error;
	// function call : EModResult (EModIndex, char const *, bool)
	todo("implement");
	bool __result = _sub_108BCDC0(file_path);
	return __result;
}

_extern bool _sub_108BCBF0(char const *);
extern "C" bool load_package_by_string_hash(char const *hash_str) // 0x108BCBF0
{
	// load_package_by_string_hash
	// static ...; // 0x108BCD5A
	// static ...; // 0x108BCD4C
	// static ...; // 0x108BCD34
	// static ...; // 0x108BCD2C
	// char const *hash_str;
	// c_mod_package_manager::s_entry package_entry;
	// unsigned char hash[20];
	// c_mod_package_manager &package_manager;
	todo("implement");
	bool __result = _sub_108BCBF0(hash_str);
	return __result;
}

_extern bool _sub_108BD010(char const *);
extern "C" bool mod_system_load_named_package(char const *name) // 0x108BD010
{
	// mod_system_load_named_package
	// static ...; // 0x108BD110
	// static ...; // 0x108BD104
	// static ...; // 0x108BD0FC
	// char const *name;
	// s_mod_server_package_entry server_package;
	todo("implement");
	bool __result = _sub_108BD010(name);
	return __result;
}

_extern __int32 _sub_108B7FB0(char *, __int32);
extern "C" __int32 FormatFilename(char *str, __int32 length) // 0x108B7FB0
{
	// FormatFilename
	// __int32 length;
	{
		// char *c;
	}
	{
		// __int32 i;
		{
			// __int32 j;
		}
	}
	todo("implement");
	__int32 __result = _sub_108B7FB0(str, length);
	return __result;
}
