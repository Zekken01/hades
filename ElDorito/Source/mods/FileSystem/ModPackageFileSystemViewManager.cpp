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

extern std::shared_ptr<CModPackageFileSystemView> _sub_10886210(CModPackageFileSystemViewManager *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
std::shared_ptr<CModPackageFileSystemView> CModPackageFileSystemViewManager::GetView(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &identifier) // 0x10886210
{
	mangled_x86(MANGLED_TODO, "?GetView@CModPackageFileSystemViewManager@@QAE?AV?$shared_ptr@VCModPackageFileSystemView@@@std@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@3@@Z");
	// static ...; // 0x1088652A
	// static ...; // 0x1088651D
	// static ...; // 0x10886518
	// static ...; // 0x108864E8
	// static ...; // 0x108864E0
	// CModPackageFileSystemViewManager *const this;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &identifier;
	// std::scoped_lock<std::mutex> lock;
	// c_mod_package_manager::s_entry packageEntry;
	// c_mod_package_manager const &manager;
	{
		// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::shared_ptr<CModPackageFileSystemView> > > > > it;
	}
	{
		// unsigned char hash[20];
	}
	todo("implement");
	std::shared_ptr<CModPackageFileSystemView> __result = _sub_10886210(this, identifier);
	return __result;
}

_extern bool _sub_10886600(CModPackageFileSystemViewManager *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
bool CModPackageFileSystemViewManager::ViewExists(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &identifier) // 0x10886600
{
	mangled_x86(MANGLED_TODO, "?ViewExists@CModPackageFileSystemViewManager@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// static ...; // 0x10886866
	// static ...; // 0x10886859
	// static ...; // 0x10886854
	// static ...; // 0x10886824
	// static ...; // 0x1088681C
	// CModPackageFileSystemViewManager *const this;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &identifier;
	// std::scoped_lock<std::mutex> lock;
	// c_mod_package_manager::s_entry packageEntry;
	// c_mod_package_manager const &manager;
	{
		// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::shared_ptr<CModPackageFileSystemView> > > > > it;
	}
	{
		// unsigned char hash[20];
	}
	todo("implement");
	bool __result = _sub_10886600(this, identifier);
	return __result;
}

_inline CModPackageFileSystemView::~CModPackageFileSystemView() // 0x108859F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1CModPackageFileSystemView@@QAE@XZ");
	// CModPackageFileSystemView *const this;

	compiler_generated();
}

_extern void _sub_10886170(CModPackageFileSystemViewManager *const);
void CModPackageFileSystemViewManager::Flush() // 0x10886170
{
	mangled_x86(MANGLED_TODO, "?Flush@CModPackageFileSystemViewManager@@QAEXXZ");
	// static ...; // 0x108861E8
	// static ...; // 0x108861DC
	// static ...; // 0x108861D4
	// CModPackageFileSystemViewManager *const this;
	// std::scoped_lock<std::mutex> lock;
	todo("implement");
	_sub_10886170(this);
}

/* ---------- private code */
