/* ---------- headers */

#include "Interface/CustomBitmapManager.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Job/JobDefinitions.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/FileSystem/ModPackageFileSystemViewManager.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Patches/CustomPackets.hpp"
#include "Player/PlayerEmblemGenerator.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/Uri.hpp"

#include <d3dx9core.h>
#include <d3dx9math.h>
#include <d3dx9math.inl>

#include <Windows.h>
#include <intsafe.h>
#include <roapi.h>
#include <roerrorapi.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <weakreference.h>
#include <wrl/client.h>
#include <wrl/event.h>
#include <wrl/implements.h>
#include <wrl/internal.h>
#include <wrl/module.h>
#include <wrl/wrappers/corewrappers.h>
#include <algorithm>
#include <array>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <fstream>
#include <functional>
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
class CustomBitmapManager;
struct lambda_1;
namespace Utils
{
	namespace Uri
	{
		struct UriComponents;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace Uri {}
	using namespace Utils::Uri;
}

namespace Windows {}
using namespace ::Windows;
namespace Windows
{
	namespace Foundation {}
	using namespace Windows::Foundation;
}

namespace Windows
{
	namespace Foundation
	{
		namespace Diagnostics {}
		using namespace Windows::Foundation::Diagnostics;
	}
}

namespace ABI {}
using namespace ::ABI;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

//class CustomBitmapManager::BitmapLoadFromFileAsync::__l2::<lambda_1>
//{
//public:
//	EJobResult operator()() const;
//	<lambda_1>(CustomBitmapManager::BitmapLoadFromFileAsync::__l2::<lambda_1> &);
//	<lambda_1>(CustomBitmapManager *, __int32 const &, unsigned short);
//private:
//	CustomBitmapManager *__this; // 0x0
//	__int32 handle; // 0x4
//	unsigned short loadTaskId; // 0x8
//public:
//	CustomBitmapManager::BitmapLoadFromFileAsync::__l2::<lambda_1> &operator=(CustomBitmapManager::BitmapLoadFromFileAsync::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(CustomBitmapManager::BitmapLoadFromFileAsync::__l2::<lambda_1>) == 12, "Invalid CustomBitmapManager::BitmapLoadFromFileAsync::__l2::<lambda_1> size");

/* ---------- prototypes */

/* ---------- globals */

extern Microsoft::WRL::Details::CreatorMap const *__pobjectentryfirst; // 0x1134A91C
extern Microsoft::WRL::Details::CreatorMap const *__pobjectentrymid; // 0x1134AA20
extern Microsoft::WRL::Details::CreatorMap const *__pobjectentrylast; // 0x1134AB24

/* ---------- private variables */

namespace hades_file_local
{
	extern char const *kBasePath; // 0x1134DA8C
	extern CustomBitmapManager g_customBitmapManager; // 0x1138CEB8
}
using namespace hades_file_local;
/* ---------- public code */

CustomBitmapManager *CustomBitmapManager::Get() // 0x10784CB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Get@CustomBitmapManager@@SAPAV1@XZ");
	// procedure flags: nofpo

	return &g_customBitmapManager;
}

_extern __int32 _sub_10784900(CustomBitmapManager *const, std::string const &);
__int32 CustomBitmapManager::FindOrAllocateBitmap(std::string const &path) // 0x10784900
{
	mangled_x86(MANGLED_TODO, "?FindOrAllocateBitmap@CustomBitmapManager@@QAEHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// static ...; // 0x10784AFC
	// static ...; // 0x10784AF4
	// CustomBitmapManager *const this;
	// std::string const &path;
	// std::scoped_lock<std::shared_mutex> lock;
	// CustomBitmapManager::StorageItem *item;
	// __int32 itemIndex;
	{
		// CustomBitmapManager::StorageItem *item;
	}
	todo("implement");
	__int32 __result = _sub_10784900(this, path);
	return __result;
}

void CustomBitmapManager::BitmapAddRef(__int32 handle) // 0x107841B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BitmapAddRef@CustomBitmapManager@@QAEXH@Z");
	// static ...; // 0x10784274
	// static ...; // 0x1078426C
	// CustomBitmapManager *const this;
	// __int32 handle;
	// std::scoped_lock<std::shared_mutex> lock;
	// CustomBitmapManager::StorageItem *item;

	std::scoped_lock<std::shared_mutex> lock(m_lock);

	StorageItem *item = GetStorageItem(handle);
	if (item)
		++item->refCount;
}

void CustomBitmapManager::BitmapRelease(__int32 handle) // 0x10784720
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?BitmapRelease@CustomBitmapManager@@QAEXH@Z");
	// static ...; // 0x107847F0
	// static ...; // 0x107847E8
	// CustomBitmapManager *const this;
	// __int32 handle;
	// std::scoped_lock<std::shared_mutex> lock;
	// CustomBitmapManager::StorageItem *item;

	std::scoped_lock<std::shared_mutex> lock(m_lock);
	StorageItem *item = GetStorageItem(handle);
	if (item && item->refCount > 0)
	{
		item->refCount--;
	}
}

_extern void _sub_10784400(CustomBitmapManager *const, __int32, std::string, std::string);
void CustomBitmapManager::BitmapLoadFromFileAsync(__int32 handle, std::string path, std::string fallbackPath) // 0x10784400
{
	mangled_x86(MANGLED_TODO, "?BitmapLoadFromFileAsync@CustomBitmapManager@@QAEXHV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
	// static ...; // 0x10784644
	// CustomBitmapManager *const this;
	// __int32 handle;
	// std::string path;
	// std::string fallbackPath;
	// std::scoped_lock<std::shared_mutex> lock;
	// std::string currentModHash;
	// CustomBitmapManager::StorageItem *item;
	todo("implement");
	_sub_10784400(this, handle, path, fallbackPath);
}

extern IDirect3DTexture9 *_sub_107842C0(CustomBitmapManager *const, __int32);
IDirect3DTexture9 *CustomBitmapManager::BitmapGetTexture(__int32 handle) // 0x107842C0
{
	mangled_x86(MANGLED_TODO, "?BitmapGetTexture@CustomBitmapManager@@QAEPAUIDirect3DTexture9@@H@Z");
	// static ...; // 0x107843A8
	// static ...; // 0x107843A0
	// CustomBitmapManager *const this;
	// __int32 handle;
	// std::shared_lock<std::shared_mutex> lock;
	// CustomBitmapManager::StorageItem *item;
	todo("implement");
	IDirect3DTexture9 * __result = _sub_107842C0(this, handle);
	return __result;
}

_extern void _sub_10785BD0(CustomBitmapManager *const);
void CustomBitmapManager::UpdateRender() // 0x10785BD0
{
	mangled_x86(MANGLED_TODO, "?UpdateRender@CustomBitmapManager@@QAEXXZ");
	// static ...; // 0x10785E94
	// static ...; // 0x10785E8F
	// static ...; // 0x10785E84
	// static ...; // 0x10785E60
	// static ...; // 0x10785E58
	// CustomBitmapManager *const this;
	// std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000> > > currentTime;
	// std::scoped_lock<std::shared_mutex> lock;
	// unsigned __int32 updateDeltaMS;
	{
		// unsigned __int32 i;
		{
			// CustomBitmapManager::StorageItem *item;
			{
				// HRESULT hr;
				// std::scoped_lock<std::shared_mutex> bufferLock;
			}
		}
	}
	todo("implement");
	_sub_10785BD0(this);
}

// mangled_x86(MANGLED_DEFAULT, "??0CustomBitmapManager@@QAE@XZ"); no body to assert in
_inline CustomBitmapManager::CustomBitmapManager() = default; // 0x10783290

// mangled_x86(MANGLED_DEFAULT, "??0StorageItem@CustomBitmapManager@@QAE@XZ"); no body to assert in
_inline CustomBitmapManager::StorageItem::StorageItem() = default; // 0x10783370

namespace Utils
{
	namespace Uri
	{
		// mangled_x86(MANGLED_DEFAULT, "??0UriComponents@Uri@Utils@@QAE@XZ"); no body to assert in
		_inline UriComponents::UriComponents() = default; // 0x10783400
	}
}

// mangled_x86(MANGLED_DEFAULT, "??1CustomBitmapManager@@QAE@XZ"); no body to assert in
_inline CustomBitmapManager::~CustomBitmapManager() = default; // 0x10783710

// mangled_x86(MANGLED_DEFAULT, "??1StorageItem@CustomBitmapManager@@QAE@XZ"); no body to assert in
_inline CustomBitmapManager::StorageItem::~StorageItem() = default; // 0x10783780

__int32 CustomBitmapManager::MakeHandle(unsigned short salt, unsigned short index) // 0x10785AA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?MakeHandle@CustomBitmapManager@@AAEHGG@Z");
	// unsigned short index;

	return (salt << 16) | index;
}

unsigned short CustomBitmapManager::NextSalt() // 0x10785AD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?NextSalt@CustomBitmapManager@@AAEGXZ");
	// CustomBitmapManager *const this;

	if (m_nextSalt++ == 0xFFFF)
		m_nextSalt = 1;
	return m_nextSalt;
}

_extern __int32 _sub_10784B90(CustomBitmapManager *const, std::string const &);
__int32 CustomBitmapManager::FindStorageItemWithPath(std::string const &path) // 0x10784B90
{
	mangled_x86(MANGLED_TODO, "?FindStorageItemWithPath@CustomBitmapManager@@AAEHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// std::string const &path;
	{
		// unsigned __int32 i;
	}
	todo("implement");
	__int32 __result = _sub_10784B90(this, path);
	return __result;
}

_extern __int32 _sub_10784D30(CustomBitmapManager *const);
__int32 CustomBitmapManager::GetFreeStorageItem() // 0x10784D30
{
	mangled_x86(MANGLED_TODO, "?GetFreeStorageItem@CustomBitmapManager@@AAEHXZ");
	// CustomBitmapManager *const this;
	{
		// unsigned __int32 i;
	}
	todo("implement");
	__int32 __result = _sub_10784D30(this);
	return __result;
}

CustomBitmapManager::StorageItem *CustomBitmapManager::GetStorageItem(__int32 handle) // 0x10784DE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetStorageItem@CustomBitmapManager@@AAEPAUStorageItem@1@H@Z");
	// __int32 handle;
	// CustomBitmapManager::StorageItem *item;
	// unsigned short index;
	// unsigned short salt;

	if (handle == -1)
		return nullptr;

	unsigned short salt = handle >> 16;
	unsigned short index = (unsigned short)handle;
	if (!salt || index > m_storageItems.size())
		return nullptr;

	StorageItem *item = &m_storageItems[index];
	if (item->salt != salt)
		return nullptr;

	return item;
}

_extern bool _sub_107850A0(CustomBitmapManager *const, std::string const &, std::vector<unsigned char> &);
bool CustomBitmapManager::LoadFileIntoBufferBlocking(std::string const &url, std::vector<unsigned char> &buffer) // 0x107850A0
{
	mangled_x86(MANGLED_TODO, "?LoadFileIntoBufferBlocking@CustomBitmapManager@@AAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV?$vector@EV?$allocator@E@std@@@3@@Z");
	// static ...; // 0x10785889
	// static ...; // 0x10785881
	// static ...; // 0x1078587C
	// static ...; // 0x10785878
	// static ...; // 0x10785830
	// static ...; // 0x10785828
	// CustomBitmapManager *const this;
	// std::string const &url;
	// std::vector<unsigned char> &buffer;
	// std::filesystem::path fpath;
	// long long fileSize;
	// long long fileOffset;
	// std::ifstream ifs;
	{
		// Utils::Uri::UriComponents uric;
		// std::shared_ptr<CModPackageFileSystemView> fsView;
		// std::string path;
		// CModPackageFileSystemView::SFileEntry fsEntry;
	}
	todo("implement");
	bool __result = _sub_107850A0(this, url, buffer);
	return __result;
}

void CustomBitmapManager::DeleteStorageItem(__int32 index) // 0x10784840
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DeleteStorageItem@CustomBitmapManager@@AAEXH@Z");
	// __int32 index;
	// CustomBitmapManager::StorageItem *item;

	StorageItem *item = &m_storageItems[index];
	item->loadState = kNone;
	item->refCount = 0;
	item->texture = nullptr;
	item->buffer.clear();
	item->salt = 0;
	item->createTextureFailed = false;
	item->keepAliveTimerMS = -1;
}

/* ---------- private code */
