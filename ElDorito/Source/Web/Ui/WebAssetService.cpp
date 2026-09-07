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

/* ---------- globals */

namespace Utils
{
	CModPackageFileSystemViewManager *Utils::Singleton<CModPackageFileSystemViewManager>::m_instance; // 0x1138CEB4
}

/* ---------- private variables */

/* ---------- public code */

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_1077E320(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::vector<std::basic_string_view<char,std::char_traits<char> >,std::allocator<std::basic_string_view<char,std::char_traits<char> > > > const &);
namespace Web
{
	namespace Ui
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > AssetService::FindAssetInModVfs(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &modIdentifier, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path, std::vector<std::basic_string_view<char,std::char_traits<char> >,std::allocator<std::basic_string_view<char,std::char_traits<char> > > > const &fileTypes) // 0x1077E320
		{
			mangled_x86(MANGLED_TODO, "?FindAssetInModVfs@AssetService@Ui@Web@@SA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV45@0ABV?$vector@V?$basic_string_view@DU?$char_traits@D@std@@@std@@V?$allocator@V?$basic_string_view@DU?$char_traits@D@std@@@std@@@2@@5@@Z");
			// static ...; // 0x1077E815
			// static ...; // 0x1077E80F
			// static ...; // 0x1077E804
			// static ...; // 0x1077E7C8
			// static ...; // 0x1077E7C0
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &modIdentifier;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path;
			// std::vector<std::basic_string_view<char,std::char_traits<char> >,std::allocator<std::basic_string_view<char,std::char_traits<char> > > > const &fileTypes;
			// std::vector<std::basic_string_view<char,std::char_traits<char> >,std::allocator<std::basic_string_view<char,std::char_traits<char> > > > const &actualFileTypes;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > vfsId;
			// std::shared_ptr<CModPackageFileSystemView> vfs;
			{
				// CModPackageFileSystemView::SFileEntry entry;
				{
					// std::vector<std::basic_string_view<char,std::char_traits<char> >,std::allocator<std::basic_string_view<char,std::char_traits<char> > > > const &<range>$L0;
					// std::basic_string_view<char,std::char_traits<char> > const *<begin>$L0;
					// std::basic_string_view<char,std::char_traits<char> > const *<end>$L0;
					{
						// std::basic_string_view<char,std::char_traits<char> > const &ext;
						{
							// std::basic_string<char,std::char_traits<char>,std::allocator<char> > actualPath;
						}
					}
				}
			}
			todo("implement");
			std::string __result = _sub_1077E320(modIdentifier, path, fileTypes);
			return __result;
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_1077DCA0(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::vector<std::basic_string_view<char,std::char_traits<char> >,std::allocator<std::basic_string_view<char,std::char_traits<char> > > > const &);
namespace Web
{
	namespace Ui
	{
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > AssetService::FindAssetInBaseDir(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path, std::vector<std::basic_string_view<char,std::char_traits<char> >,std::allocator<std::basic_string_view<char,std::char_traits<char> > > > const &fileTypes) // 0x1077DCA0
		{
			mangled_x86(MANGLED_TODO, "?FindAssetInBaseDir@AssetService@Ui@Web@@SA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV45@ABV?$vector@V?$basic_string_view@DU?$char_traits@D@std@@@std@@V?$allocator@V?$basic_string_view@DU?$char_traits@D@std@@@std@@@2@@5@@Z");
			// static ...; // 0x1077E1C3
			// static ...; // 0x1077E1B8
			// static ...; // 0x1077E194
			// static ...; // 0x1077E18C
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path;
			// std::vector<std::basic_string_view<char,std::char_traits<char> >,std::allocator<std::basic_string_view<char,std::char_traits<char> > > > const &fileTypes;
			// std::vector<std::basic_string_view<char,std::char_traits<char> >,std::allocator<std::basic_string_view<char,std::char_traits<char> > > > const &actualFileTypes;
			// std::filesystem::path baseDir;
			{
				// std::vector<std::basic_string_view<char,std::char_traits<char> >,std::allocator<std::basic_string_view<char,std::char_traits<char> > > > const &<range>$L0;
				// std::basic_string_view<char,std::char_traits<char> > const *<begin>$L0;
				// std::basic_string_view<char,std::char_traits<char> > const *<end>$L0;
				{
					// std::basic_string_view<char,std::char_traits<char> > const &ext;
					{
						// std::basic_string<char,std::char_traits<char>,std::allocator<char> > actualPath;
					}
				}
			}
			todo("implement");
			std::string __result = _sub_1077DCA0(path, fileTypes);
			return __result;
		}
	}
}

extern CModPackageFileSystemViewManager* _sub_1077C870(CModPackageFileSystemViewManager *const);
_inline CModPackageFileSystemViewManager::CModPackageFileSystemViewManager() // 0x1077C870
{
	mangled_x86(MANGLED_TODO, "??0CModPackageFileSystemViewManager@@QAE@XZ");
	// CModPackageFileSystemViewManager *const this;
	compiler_generated();
	todo("implement");
	_sub_1077C870(this);
}

/* ---------- private code */
