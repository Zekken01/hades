/* ---------- headers */

#include "Web/Ui/WebAssetService.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/RefCounting.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/FileSystem/ModPackageFileSystemViewManager.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Web/WebFileReadHandler.hpp"

#include "mods/mod_system.hpp"  // hades: added for 0x1077E970

#include <base/cef_atomic_ref_count.h>
#include <base/cef_lock.h>
#include <base/cef_logging.h>
#include <base/cef_platform_thread.h>
#include <base/cef_ref_counted.h>
#include <base/cef_scoped_refptr.h>
#include <base/cef_thread_checker.h>
#include <base/internal/cef_lock_impl.h>
#include <cef_base.h>
#include <cef_devtools_message_observer.h>
#include <cef_extension_handler.h>
#include <cef_resource_handler.h>
#include <internal/cef_string_wrappers.h>
#include <internal/cef_types_wrappers.h>
#include <internal/cef_win.h>
#include <wrapper/cef_stream_resource_handler.h>

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
#include <exception>
#include <filesystem>
#include <forward_list>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
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
#include <string_view>
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
class CModPackageFileSystemViewManager;
class IMod;
class c_mod_package;
struct begin;
struct end;
namespace Web
{
	namespace Ui
	{
		struct AssetService;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace base {}
using namespace ::base;
namespace base
{
	namespace cef_subtle {}
	using namespace base::cef_subtle;
	namespace cef_internal {}
	using namespace base::cef_internal;
	namespace internal {}
	using namespace base::internal;
}

namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Ui {}
	using namespace Web::Ui;
	namespace Browser {}
	using namespace Web::Browser;
}

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

std::shared_ptr<CModPackageFileSystemView> GetModVFS(std::string const &identifier, std::string &vfsId);

/* ---------- globals */

namespace Utils
{
	CModPackageFileSystemViewManager *Utils::Singleton<CModPackageFileSystemViewManager>::m_instance; // 0x1138CEB4
}

/* ---------- private variables */

/* ---------- public code */


namespace Web
{
	namespace Ui
	{
		std::string AssetService::FindAssetInModVfs(std::string const &modIdentifier, std::string const &path, std::vector<std::string_view> const &fileTypes) // 0x1077E320
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?FindAssetInModVfs@AssetService@Ui@Web@@SA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV45@0ABV?$vector@V?$basic_string_view@DU?$char_traits@D@std@@@std@@V?$allocator@V?$basic_string_view@DU?$char_traits@D@std@@@std@@@2@@5@@Z");

			std::vector<std::string_view> const &actualFileTypes = !fileTypes.empty() ? fileTypes : std::vector<std::string_view>{ "" };
			std::string vfsId;
			std::shared_ptr<CModPackageFileSystemView> vfs = GetModVFS(modIdentifier, vfsId);
			if (vfs)
			{
				CModPackageFileSystemView::SFileEntry entry;
				for (std::string_view const &ext : actualFileTypes)
				{
					std::string const actualPath = ext.empty() ? std::string(path) : std::format("{}.{}", path, ext);
					if (vfs->GetFileEntry(actualPath, &entry))
						return std::format("pak://{}/{}", vfsId, actualPath);
				}
			}
			return "";
		}
	}
}


namespace Web
{
	namespace Ui
	{
		std::string AssetService::FindAssetInBaseDir(std::string const &path, std::vector<std::string_view> const &fileTypes) // 0x1077DCA0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?FindAssetInBaseDir@AssetService@Ui@Web@@SA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV45@ABV?$vector@V?$basic_string_view@DU?$char_traits@D@std@@@std@@V?$allocator@V?$basic_string_view@DU?$char_traits@D@std@@@std@@@2@@5@@Z");

			std::vector<std::string_view> const &actualFileTypes = !fileTypes.empty() ? fileTypes : std::vector<std::string_view>{ "" };
			std::filesystem::path baseDir("ui\\");
			for (std::string_view const &ext : actualFileTypes)
			{
				std::string const actualPath = ext.empty() ? std::string(path) : std::format("{}.{}", path, ext);
				if (std::filesystem::exists(baseDir / std::filesystem::path(actualPath).lexically_normal()))
					return std::format("dew://{}", actualPath);
			}
			return "";
		}
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0CModPackageFileSystemViewManager@@QAE@XZ"); no body to assert in

/* ---------- private code */

std::shared_ptr<CModPackageFileSystemView> GetModVFS(std::string const &identifier, std::string &vfsId) // 0x1077E970
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetModVFS@@YA?AV?$shared_ptr@VCModPackageFileSystemView@@@std@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@AAV32@@Z");

	EModIndex modIndex = kInvalid;
	if (identifier == "game")
		modIndex = kGame;
	else if (identifier == "mainmenu")
		modIndex = kMainMenu;
	if (modIndex != kInvalid)
	{
		Ref<IMod> mod = c_mod_system::GetModManager().GetModShared(modIndex);
		if (mod)
		{
			c_mod_package const *pak = mod->GetPak(true);
			if (!pak)
				return nullptr;
			std::string hashStr;
			Utils::String::BytesToHexString(pak->get_header()->sha1, 20, hashStr);
			vfsId = hashStr;
			return Utils::Singleton<CModPackageFileSystemViewManager>::Instance().GetView(hashStr);
		}
	}
	else
	{
		vfsId = identifier;
		return Utils::Singleton<CModPackageFileSystemViewManager>::Instance().GetView(identifier);
	}
	return nullptr;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template CModPackageFileSystemViewManager & Utils::Singleton<CModPackageFileSystemViewManager>::Instance();
