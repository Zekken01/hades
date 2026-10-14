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

#include "Utils/Logger.hpp"  // hades: added for 0x108BB170

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

// hades: moved from hades/recovered_types.h, where its member types were not visible
struct s_mod_system_globals
{
	bool initialized; // 0x0
	bool packages_updated; // 0x1
	bool dedicated; // 0x2
	unsigned char __pad0[1]; // 0x3
	c_mod_package_manager package_manager; // 0x4
	std::unordered_map<std::string,s_mod_server_package_entry> server_package_map; // 0x84
public:
	s_mod_system_globals();
	~s_mod_system_globals();
};
static_assert32(sizeof(s_mod_system_globals) == 172, "Invalid s_mod_system_globals size");

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

extern s_session_mod_options const *network_squad_session_get_mod();  // hades: added for 0x108BBEC0  // hades: added for 0x108BBEC0

bool update_packages();
bool create_package_directory();
bool load_package_file_internal(char const *file_path);
bool load_package_by_string_hash(char const *hash_str);
bool mod_system_load_named_package(char const *name);
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

void c_mod_system::initialize(bool is_dedicated_server) // 0x108BC8E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize@c_mod_system@@SAX_N@Z");
	// bool is_dedicated_server;

	create_package_directory();
	g_mod_system_globals.dedicated = is_dedicated_server;
	(&g_mod_system_globals.package_manager)->initialize(c_mod_system::get_package_directory());
	if (!is_dedicated_server)
	{
		(&g_mod_system_globals.package_manager)->begin_enumerate();
	}

	g_mod_system_globals.initialized = true;
}

void c_mod_system::update() // 0x108BD580
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update@c_mod_system@@SAXXZ");
	// procedure flags: nofpo
	// function call : void ()

	if (!g_mod_system_globals.packages_updated)
	{
		g_mod_system_globals.packages_updated = true;
		update_packages();
	}

	(&g_mod_system_globals.package_manager)->update();
	static_cast<ModManager &>(c_mod_system::GetModManager()).SetMainThread();
	c_mod_system::GetModManager().Tick();
}

char const *c_mod_system::get_package_directory() // 0x108BC5E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_package_directory@c_mod_system@@SAPBDXZ");
	// procedure flags: nofpo

	return k_package_directory;
}

bool c_mod_system::unload_current_package() // 0x108BD4F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unload_current_package@c_mod_system@@SA_NXZ");
	// procedure flags: nofpo
	// function call : EModResult (EModIndex, char const *, bool)

	c_mod_system::GetModManager().SetMod(kGame, nullptr, true);
	return true;
}

std::string c_mod_system::get_mod_hash_by_identifier(char const *identifier) // 0x108BC040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_mod_hash_by_identifier@c_mod_system@@SA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PBD@Z");
	// static ...; // 0x108BC2B9
	// static ...; // 0x108BC2AC
	// static ...; // 0x108BC2A4
	// static ...; // 0x108BC280
	// static ...; // 0x108BC278
	// char const *identifier;
	// s_mod_server_package_entry server_package;
		// c_mod_package_manager::s_entry packageEntry;
		// c_mod_package_manager const &manager;
			// std::string hashstr;

	s_mod_server_package_entry server_package;
	if (find_server_package_by_name(identifier, &server_package))
	{
		return server_package.hash;
	}
	else if (strstr(identifier, ".pak"))
	{
		c_mod_package_manager const &manager = get_package_manager();
		c_mod_package_manager::s_entry packageEntry;
		if (manager.find_package_by_filename(identifier, &packageEntry))
		{
			std::string hashstr;
			Utils::String::BytesToHexString(packageEntry.hash, sizeof(packageEntry.hash), hashstr);
			return hashstr;
		}
		else
		{
			return "";
		}
	}
	else
	{
		return identifier;
	}
}

bool c_mod_system::get_mod_info_by_hash(char const *hash_str, c_mod_package_manager::s_entry *package_entry) // 0x108BC370
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_mod_info_by_hash@c_mod_system@@SA_NPBDPAUs_entry@c_mod_package_manager@@@Z");
	// static ...; // 0x108BC444
	// static ...; // 0x108BC43C
	// char const *hash_str;
	// c_mod_package_manager::s_entry *package_entry;
	// unsigned char hash[20];
	// c_mod_package_manager &package_manager;

	unsigned char hash[20];

	Utils::String::HexStringToBytes(hash_str, hash, 20);

	c_mod_package_manager &package_manager = c_mod_system::get_package_manager();
	return package_manager.find_package_by_hash(hash, package_entry);
}

bool c_mod_system::get_mod_info_by_identifier(char const *identifier, c_mod_package_manager::s_entry *package_entry) // 0x108BC490
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_mod_info_by_identifier@c_mod_system@@SA_NPBDPAUs_entry@c_mod_package_manager@@@Z");
	// static ...; // 0x108BC584
	// static ...; // 0x108BC57C
	// char const *identifier;
	// c_mod_package_manager::s_entry *package_entry;
	// std::string hash_str;

	std::string hash_str = get_mod_hash_by_identifier(identifier);
	if (hash_str.empty())
		return false;

	return get_mod_info_by_hash(hash_str.c_str(), package_entry);
}

bool c_mod_system::load_package_by_identifier(char const *identifier) // 0x108BC960
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?load_package_by_identifier@c_mod_system@@SA_NPBD@Z");
	// static ...; // 0x108BCB64
	// static ...; // 0x108BCB58
	// static ...; // 0x108BCB50
	// char const *identifier;
		// std::filesystem::path path;
		// c_mod_package_manager &package_manager;

	if (mod_system_load_named_package(identifier))
		return true;
	if (strstr(identifier, ".pak"))
	{
		c_mod_package_manager &package_manager = c_mod_system::get_package_manager();
		std::filesystem::path path = std::filesystem::path(c_mod_system::get_package_directory()) / std::string(identifier);
		return load_package_file_internal(path.string().c_str());
	}
	if (load_package_by_string_hash(identifier))
		return true;
	return false;
}

std::string c_mod_system::get_current_package_hash() // 0x108BBEC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_current_package_hash@c_mod_system@@SA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// procedure flags: nofpo
	// static ...; // 0x108BBFE0
	// static ...; // 0x108BBFD4
	// static ...; // 0x108BBFCC
	// std::string hashstr;
	// s_session_mod_options const *mod_options;

	s_session_mod_options const *mod_options = network_squad_session_get_mod();
	if (!mod_options || !mod_options->valid)
		return "";
	std::string hashstr;
	Utils::String::BytesToHexString(mod_options->hash, sizeof(mod_options->hash), hashstr);
	return hashstr;
}

std::string c_mod_system::get_current_mainmenu_package_hash() // 0x108BB9A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_current_mainmenu_package_hash@c_mod_system@@SA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// procedure flags: nofpo
	// static ...; // 0x108BBB38
	// static ...; // 0x108BBB2C
	// static ...; // 0x108BBB24
	// IMod *mod;
		// c_mod_package *package;
		// std::string hash_str;
	// function call : IMod *(EModIndex) const
	// function call : c_mod_package *(bool) const

	IMod *mod = GetModManager().GetMod(kMainMenu);
	if (mod)
	{
		c_mod_package *package = mod->GetPak(true);
		if (!package)
			return "";
		std::string hash_str;
		Utils::String::BytesToHexString(package->get_header()->sha1, sizeof(package->get_header()->sha1), hash_str);
		return hash_str;
	}
	return "";
}

std::string c_mod_system::get_current_package_filename(EModIndex package_type) // 0x108BBBB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_current_package_filename@c_mod_system@@SA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@W4EModIndex@@@Z");
	// static ...; // 0x108BBE1C
	// static ...; // 0x108BBE10
	// static ...; // 0x108BBE08
	// EModIndex package_type;
	// IMod *mod;
		// c_mod_package *package;
		// c_mod_package_manager::s_entry entry;
	// function call : IMod *(EModIndex) const
	// function call : c_mod_package *(bool) const

	IMod *mod = GetModManager().GetMod(package_type);
	if (mod)
	{
		c_mod_package *package = mod->GetPak(true);
		if (!package)
			return "";
		c_mod_package_manager::s_entry entry;
		if (get_package_manager().find_package_by_hash(package->get_header()->sha1, &entry))
			return std::filesystem::path(entry.file.filename).filename().string();
	}
	return "";
}

c_mod_package_manager &c_mod_system::get_package_manager() // 0x108BC850
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_package_manager@c_mod_system@@SAAAVc_mod_package_manager@@XZ");
	// procedure flags: nofpo

	return g_mod_system_globals.package_manager;
}

bool c_mod_system::find_server_package_by_hash(std::string const &hash, s_mod_server_package_entry *entry) // 0x108BB5C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?find_server_package_by_hash@c_mod_system@@SA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAUs_mod_server_package_entry@@@Z");
	// static ...; // 0x108BB6F8
	// static ...; // 0x108BB6F0
	// std::string const &hash;
	// s_mod_server_package_entry *entry;
		// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<std::string const ,s_mod_server_package_entry> > > > it;

	if (auto it = g_mod_system_globals.server_package_map.find(hash); it != std::end(g_mod_system_globals.server_package_map))
	{
		*entry = it->second;
		return true;
	}
	return false;
}

bool c_mod_system::find_server_package_by_name(char const *name, s_mod_server_package_entry *entry) // 0x108BB760
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?find_server_package_by_name@c_mod_system@@SA_NPBDPAUs_mod_server_package_entry@@@Z");
	// static ...; // 0x108BB914
	// static ...; // 0x108BB90C
	// char const *name;
	// s_mod_server_package_entry *entry;
	// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<std::string const ,s_mod_server_package_entry> > > > it;

	auto it = std::find_if(std::begin(g_mod_system_globals.server_package_map), std::end(g_mod_system_globals.server_package_map), [name](auto const &pair) { return pair.second.local_name == name; });
	if (it != std::end(g_mod_system_globals.server_package_map))
	{
		*entry = it->second;
		return true;
	}
	return false;
}

bool c_mod_system::has_server_package_list() // 0x108BC870
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?has_server_package_list@c_mod_system@@SA_NXZ");
	// procedure flags: nofpo

	return g_mod_system_globals.server_package_map.size() ? true : false;
}

std::unordered_map<std::string,CModPackageFileSystemView::SFileEntry> c_mod_system::get_package_file_list(std::string hash) // 0x108BC600
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_package_file_list@c_mod_system@@SA?AV?$unordered_map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@USFileEntry@CModPackageFileSystemView@@U?$hash@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@U?$equal_to@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@USFileEntry@CModPackageFileSystemView@@@std@@@2@@std@@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@3@@Z");
	// static ...; // 0x108BC7A5
	// static ...; // 0x108BC7A0
	// static ...; // 0x108BC788
	// static ...; // 0x108BC780
	// std::string hash;
	// std::unordered_map<std::string,CModPackageFileSystemView::SFileEntry> fileList;
		// std::shared_ptr<CModPackageFileSystemView> view;

	std::unordered_map<std::string,CModPackageFileSystemView::SFileEntry> fileList;
	if (hash != "" && Utils::Singleton<CModPackageFileSystemViewManager>::Instance().ViewExists(hash))
	{
		std::shared_ptr<CModPackageFileSystemView> view = Utils::Singleton<CModPackageFileSystemViewManager>::Instance().GetView(hash);
		if (view)
			fileList = view->GetFileList();
	}
	return fileList;
}

std::string c_mod_system::GetNewPackageFilename(std::string name, std::string hash, std::string version) // 0x108B82B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetNewPackageFilename@c_mod_system@@SA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V23@00@Z");
	// static ...; // 0x108B859C
	// std::string name;
	// std::string hash;
	// std::string version;
	// char buff[32];

	char buff[32];
	buff[0] = '\0';
	strncpy_s(buff, name.c_str(), std::size(buff) - 1);
	FormatFilename(buff, strlen(buff));
	std::replace(version.begin(), version.end(), '.', '_');
	return std::string(buff) + "_" + hash.substr(0, 8) + "_v" + version;
}

IModManager &c_mod_system::GetModManager() // 0x108B81C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetModManager@c_mod_system@@SAAAVIModManager@@XZ");
	// procedure flags: nofpo
	// static ModManager manager; // 0x12407F70
	// static __int32 $TSS0; // 0x12407F6C

	static ModManager manager;
	return manager;
}

// mangled_x86(MANGLED_DEFAULT, "??0c_mod_package_updater_blocking@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0s_mod_server_package_entry@@QAE@$$QAU0@@Z"); no body to assert in
// _inline s_mod_server_package_entry::s_mod_server_package_entry(s_mod_server_package_entry &&__that) = default; // 0x108B6B90  // hades: implicit

// mangled_x86(MANGLED_DEFAULT, "??0s_mod_server_package_entry@@QAE@ABU0@@Z"); no body to assert in
// _inline s_mod_server_package_entry::s_mod_server_package_entry(s_mod_server_package_entry const &__that) = default; // 0x108B6C40  // hades: implicit

// mangled_x86(MANGLED_DEFAULT, "??0s_mod_server_package_entry@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0s_mod_system_globals@@QAE@XZ"); no body to assert in
_inline s_mod_system_globals::s_mod_system_globals() = default; // 0x108B6DB0

// mangled_x86(MANGLED_DEFAULT, "??1c_mod_package_updater_blocking@@QAE@XZ"); no body to assert in
_inline c_mod_package_updater_blocking::~c_mod_package_updater_blocking() = default; // 0x108B7790

// mangled_x86(MANGLED_DEFAULT, "??1s_mod_server_package_entry@@QAE@XZ"); no body to assert in
// _inline s_mod_server_package_entry::~s_mod_server_package_entry() = default; // 0x108B77F0  // hades: implicit

// mangled_x86(MANGLED_DEFAULT, "??1s_mod_system_globals@@QAE@XZ"); no body to assert in
_inline s_mod_system_globals::~s_mod_system_globals() = default; // 0x108B7860

// mangled_x86(MANGLED_DEFAULT, "??4s_mod_server_package_entry@@QAEAAU0@ABU0@@Z"); no body to assert in
// _inline s_mod_server_package_entry &s_mod_server_package_entry::operator=(s_mod_server_package_entry const &__that) = default; // 0x108B79E0  // hades: implicit

/* ---------- private code */

bool update_packages() // 0x108BD630
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_update_packages");
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
		// std::vector<c_mod_package_updater_blocking::s_mod_package_description> const &<range>$L0;
		// c_mod_package_updater_blocking::s_mod_package_description const *<begin>$L0;
		// c_mod_package_updater_blocking::s_mod_package_description const *<end>$L0;
			// c_mod_package_updater_blocking::s_mod_package_description const &package;
				// s_mod_server_package_entry entry;

	std::string package_list_filename = Utils::Singleton<Modules::ModuleServer>::Instance().VarModsJsonFile->ValueString;
	c_file_reference package_list(package_list_filename.c_str());
	if (!package_list.exists())
		return true;
	c_mod_package_updater_blocking updater;
	updater.initialize(g_mod_system_globals.dedicated, package_list_filename.c_str(), k_package_directory);
	updater.update_packages_blocking();
	for (c_mod_package_updater_blocking::s_mod_package_description const &package : updater.get_package_list())
	{
		s_mod_server_package_entry entry;
		entry.hash = package.hash;
		entry.local_name = package.local_name;
		entry.package_url = package.package_url;
		g_mod_system_globals.server_package_map.insert(std::make_pair(entry.hash, entry));
	}
	return true;
}

bool create_package_directory() // 0x108BB170
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_create_package_directory");
	// create_package_directory
	// procedure flags: nofpo
	// static ...; // 0x108BB318
	// static ...; // 0x108BB30C
	// static ...; // 0x108BB304
	// std::error_code ec;

	std::error_code ec;
	if (!std::filesystem::create_directories(k_package_directory, ec) && ec)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, "failed to create mod package directory '%s'", k_package_directory);
		throw std::runtime_error(nullptr);
	}
	return true;
}

bool load_package_file_internal(char const *file_path) // 0x108BCDC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_load_package_file_internal");
	// load_package_file_internal
	// char const *file_path;
	// EModResult error;
	// function call : EModResult (EModIndex, char const *, bool)

	EModResult result = c_mod_system::GetModManager().SetMod(EModIndex(0), file_path, true);
	if (result != kSuccess && result != kPending)
		return false;
	return true;
}

bool load_package_by_string_hash(char const *hash_str) // 0x108BCBF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_load_package_by_string_hash");
	// load_package_by_string_hash
	// static ...; // 0x108BCD5A
	// static ...; // 0x108BCD4C
	// static ...; // 0x108BCD34
	// static ...; // 0x108BCD2C
	// char const *hash_str;
	// c_mod_package_manager::s_entry package_entry;
	// unsigned char hash[20];
	// c_mod_package_manager &package_manager;

	unsigned char hash[20];
	Utils::String::HexStringToBytes(hash_str, hash, 20);
	c_mod_package_manager &package_manager = c_mod_system::get_package_manager();
	c_mod_package_manager::s_entry package_entry;
	if (!package_manager.find_package_by_hash(hash, &package_entry))
		return false;
	return load_package_file_internal(package_entry.file.filename);
}

bool mod_system_load_named_package(char const *name) // 0x108BD010
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_mod_system_load_named_package");
	// mod_system_load_named_package
	// static ...; // 0x108BD110
	// static ...; // 0x108BD104
	// static ...; // 0x108BD0FC
	// char const *name;
	// s_mod_server_package_entry server_package;

	s_mod_server_package_entry server_package;
	if (!c_mod_system::find_server_package_by_name(name, &server_package))
	{
		return false;
	}

	return load_package_by_string_hash(server_package.hash.c_str());
}

extern "C" __int32 FormatFilename(char *str, __int32 length) // 0x108B7FB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_FormatFilename");
	// FormatFilename
	// __int32 length;
		// char *c;
		// __int32 i;
			// __int32 j;

	for (char *c = &str[length - 1]; isspace(*c); c--, length--)
		*c = 0;
	for (__int32 i = 0; i < length; )
	{
		if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z') || str[i] == '_' || str[i] == '-')
		{
			i++;
		}
		else if (str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] = tolower(str[i]);
			i++;
		}
		else if (str[i] == ' ' && i > 0)
		{
			str[i++] = '_';
		}
		else
		{
			for (__int32 j = i + 1; j < length; j++)
				std::swap(str[j], str[j - 1]);
			length--;
		}
	}
	str[length] = 0;
	return length;
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { s_mod_system_globals g_mod_system_globals; }
