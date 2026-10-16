/* ---------- headers */

#include "mods/FileSystem/ModPackageFileSystemViewManager.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Patches/CustomPackets.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"

#include "mods/mod_system.hpp"  // hades: added for 0x10886600  // hades: added for 0x10886600

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
#include <unordered_map>
#include <utility>

/* ---------- forward declarations */

class CModPackageFileSystemView;
class CModPackageFileSystemViewManager;
class c_mod_package_manager;

namespace Utils {}
using namespace ::Utils;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

std::shared_ptr<CModPackageFileSystemView> CModPackageFileSystemViewManager::GetView(std::string const &identifier) // 0x10886210
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetView@CModPackageFileSystemViewManager@@QAE?AV?$shared_ptr@VCModPackageFileSystemView@@@std@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@3@@Z");

	std::scoped_lock<std::mutex> lock(m_mutex);
	if (auto it = m_views.find(identifier); it != std::end(m_views))
		return it->second;
	c_mod_package_manager const &manager = c_mod_system::get_package_manager();
	c_mod_package_manager::s_entry packageEntry;
	if (!manager.find_package_by_filename(identifier.c_str(), &packageEntry))
	{
		unsigned char hash[20];
		Utils::String::HexStringToBytes(identifier, hash, sizeof(hash));
		if (!manager.find_package_by_hash(hash, &packageEntry))
			return nullptr;
	}
	return m_views[identifier] = std::make_shared<CModPackageFileSystemView>(packageEntry.file.filename);
}

bool CModPackageFileSystemViewManager::ViewExists(std::string const &identifier) // 0x10886600
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ViewExists@CModPackageFileSystemViewManager@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

	std::scoped_lock<std::mutex> lock(m_mutex);
	if (auto it = m_views.find(identifier); it != std::end(m_views))
		return true;
	c_mod_package_manager const &manager = c_mod_system::get_package_manager();
	c_mod_package_manager::s_entry packageEntry;
	if (!manager.find_package_by_filename(identifier.c_str(), &packageEntry))
	{
		unsigned char hash[20];
		Utils::String::HexStringToBytes(identifier, hash, sizeof(hash));
		if (!manager.find_package_by_hash(hash, &packageEntry))
			return false;
	}
	return true;
}

// mangled_x86(MANGLED_DEFAULT, "??1CModPackageFileSystemView@@QAE@XZ"); no body to assert in
_inline CModPackageFileSystemView::~CModPackageFileSystemView() = default; // 0x108859F0

void CModPackageFileSystemViewManager::Flush() // 0x10886170
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Flush@CModPackageFileSystemViewManager@@QAEXXZ");

	std::scoped_lock<std::mutex> lock(m_mutex);
	m_views.clear();
}

/* ---------- private code */
