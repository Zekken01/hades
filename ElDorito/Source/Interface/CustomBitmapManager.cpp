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

#include <d3dx9tex.h>  // hades: added for 0x10785BD0

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

#include "mods/mod_system.hpp"  // hades: added for 0x10784400
namespace Job { extern void RunJob(std::function<EJobResult __cdecl(void)> function, SJobCounter *counter, __int32 priority); }  // hades: added for 0x10784400  // hades: added for 0x10784400

/* ---------- globals */

extern Microsoft::WRL::Details::CreatorMap const *__pobjectentryfirst; // 0x1134A91C
extern Microsoft::WRL::Details::CreatorMap const *__pobjectentrymid; // 0x1134AA20
extern Microsoft::WRL::Details::CreatorMap const *__pobjectentrylast; // 0x1134AB24

/* ---------- private variables */

namespace hades_file_local
{
	extern char const *kBasePath; // 0x1134DA8C
	CustomBitmapManager g_customBitmapManager; // 0x1138CEB8  // hades: defined, so its dynamic initializer emits the constructor
}
using namespace hades_file_local;
/* ---------- public code */

CustomBitmapManager *CustomBitmapManager::Get() // 0x10784CB0
{
	return &g_customBitmapManager;
}

#line 182
__int32 CustomBitmapManager::FindOrAllocateBitmap(std::string const &path) // 0x10784900
{
#line 193

	std::scoped_lock<std::shared_mutex> lock(m_lock);
	__int32 itemIndex = FindStorageItemWithPath(path);
	if (itemIndex != -1)
	{
		StorageItem *item = &m_storageItems[itemIndex];
		item->refCount++;
		return MakeHandle(item->salt, itemIndex);
	}
	itemIndex = GetFreeStorageItem();
	if (itemIndex == -1)
		return -1;
	StorageItem *item = &m_storageItems[itemIndex];
	#line 199 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Interface\\CustomBitmapManager.cpp"
		assert(!item->texture);
		#line 209 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Interface\\CustomBitmapManager.cpp"
	item->loadState = ELoadState::kNone;
	item->salt = NextSalt();
	item->refCount = 1;
	item->texture = nullptr;
	item->loadTaskId = 0;
	item->createTextureFailed = false;
	item->keepAliveTimerMS = -1;
	return MakeHandle(item->salt, itemIndex);
}

void CustomBitmapManager::BitmapAddRef(__int32 handle) // 0x107841B0
{
	std::scoped_lock<std::shared_mutex> lock(m_lock);
	StorageItem *item = GetStorageItem(handle);
	if (item)
		++item->refCount;
}

void CustomBitmapManager::BitmapRelease(__int32 handle) // 0x10784720
{
	std::scoped_lock<std::shared_mutex> lock(m_lock);
	StorageItem *item = GetStorageItem(handle);
	if (item && item->refCount > 0)
	{
		item->refCount--;
	}
}

void CustomBitmapManager::BitmapLoadFromFileAsync(__int32 handle, std::string path, std::string fallbackPath) // 0x10784400
{
	std::scoped_lock<std::shared_mutex> lock(m_lock);
	std::string currentModHash = c_mod_system::get_current_package_hash();
	StorageItem *item = GetStorageItem(handle);
	if (!item)
		return;
	if (item->loadState != ELoadState::kNone && item->path == path && currentModHash == m_currentModHash)
		return;
	item->loadState = ELoadState::kLoading;
	item->loadTaskId++;
	item->path = path;
	item->fallbackPath = fallbackPath;
	m_currentModHash = std::move(currentModHash);
	Job::RunJob([this, handle, taskId = item->loadTaskId]()
	{
		std::unique_lock<std::shared_mutex> lock(m_lock);
		StorageItem *item = GetStorageItem(handle);
		if (!item || item->loadTaskId != taskId)
			return Done;
		std::string modHash = m_currentModHash;
		lock.unlock();
		bool success = false;
		std::scoped_lock<std::shared_mutex> bufferLock(item->bufferLock);
		if ((!modHash.empty() && LoadFileIntoBufferBlocking(std::format("pak://{}/{}", modHash, item->path), item->buffer)) || LoadFileIntoBufferBlocking(item->path, item->buffer) || (!item->fallbackPath.empty() && LoadFileIntoBufferBlocking(item->fallbackPath, item->buffer)))
			success = true;
		lock.lock();
		item = GetStorageItem(handle);
		if (!item || item->loadTaskId != taskId)
			return Done;
		item->loadState = success ? ELoadState::kLoaded : ELoadState::kFailed;
		return Done;
	}, nullptr, 0);
}

IDirect3DTexture9 *CustomBitmapManager::BitmapGetTexture(__int32 handle) // 0x107842C0
{
	std::shared_lock<std::shared_mutex> lock(m_lock);
	StorageItem *item = GetStorageItem(handle);
	if (!item)
		return nullptr;

	return item->texture.Get();
}

void CustomBitmapManager::UpdateRender() // 0x10785BD0
{
	auto currentTime = std::chrono::steady_clock::now();
	unsigned __int32 updateDeltaMS = (unsigned __int32)std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - m_lastUpdateRenderTime).count();
	m_lastUpdateRenderTime = currentTime;
	std::scoped_lock<std::shared_mutex> lock(m_lock);
	for (unsigned __int32 i = 0; i < m_storageItems.size(); i++)
	{
		StorageItem *item = &m_storageItems[i];
		if (!item->InUse())
			continue;
		if (item->refCount == 0)
		{
			if (item->loadState != ELoadState::kLoading)
			{
				if (item->keepAliveTimerMS == -1)
					item->keepAliveTimerMS = 0;
				item->keepAliveTimerMS += updateDeltaMS;
				if (item->keepAliveTimerMS >= 5000)
					DeleteStorageItem(i);
			}
			continue;
		}
		if (item->loadState == ELoadState::kLoaded && !item->createTextureFailed && item->texture == nullptr)
		{
			std::scoped_lock<std::shared_mutex> bufferLock(item->bufferLock);
			HRESULT hr = D3DXCreateTextureFromFileInMemory(c_rasterizer::get_device(), item->buffer.data(), item->buffer.size(), &item->texture);
			if (FAILED(hr))
			{
				item->texture = nullptr;
				item->createTextureFailed = true;
			}
		}
	}
}

namespace Utils
{
	namespace Uri
	{
	}
}

_inline CustomBitmapManager::~CustomBitmapManager() = default; // 0x10783710

_inline CustomBitmapManager::StorageItem::~StorageItem() = default; // 0x10783780

__int32 CustomBitmapManager::MakeHandle(unsigned short salt, unsigned short index) // 0x10785AA0
{
	return (salt << 16) | index;
}

unsigned short CustomBitmapManager::NextSalt() // 0x10785AD0
{
	if (m_nextSalt++ == 0xFFFF)
		m_nextSalt = 1;
	return m_nextSalt;
}

__int32 CustomBitmapManager::FindStorageItemWithPath(std::string const &path) // 0x10784B90
{
	for (unsigned __int32 i = 0; i < m_storageItems.size(); i++)
	{
		if (m_storageItems[i].InUse() && m_storageItems[i].path == path)
			return i;
	}
	return -1;
}

__int32 CustomBitmapManager::GetFreeStorageItem() // 0x10784D30
{
	for (unsigned __int32 i = 0; i < m_storageItems.size(); i++)
	{
		if (!m_storageItems[i].InUse())
			return i;
	}

	return -1;
}

CustomBitmapManager::StorageItem *CustomBitmapManager::GetStorageItem(__int32 handle) // 0x10784DE0
{
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

bool CustomBitmapManager::LoadFileIntoBufferBlocking(std::string const &url, std::vector<unsigned char> &buffer) // 0x107850A0
{
	long long fileOffset = 0;
	long long fileSize = 0;
	std::filesystem::path fpath;
	if (url.starts_with("pak://"))
	{
		Utils::Uri::UriComponents uric;
		if (!Utils::Uri::ParseUriComponents(url, uric))
			return false;
		std::shared_ptr<CModPackageFileSystemView> fsView = Utils::Singleton<CModPackageFileSystemViewManager>::Instance().GetView(std::string(uric.authority));
		if (!fsView)
			return false;
		CModPackageFileSystemView::SFileEntry fsEntry;
		std::string path = std::string(uric.path.substr(1)).c_str();
		if (!fsView->GetFileEntry(path + ".jpg", &fsEntry) && !fsView->GetFileEntry(path + ".png", &fsEntry))
			return false;
		fpath = fsView->GetFilePath();
		fileOffset = fsView->GetBaseOffset() + fsEntry.offset;
		fileSize = fsEntry.size;
	}
	else
	{
		fpath = std::filesystem::path(kBasePath) / std::filesystem::path(url).lexically_normal();
		fpath.replace_extension("jpg");
		if (!std::filesystem::exists(fpath))
		{
			fpath.replace_extension("png");
			if (!std::filesystem::exists(fpath))
				return false;
		}
		fileOffset = 0;
		fileSize = 0;
	}
	std::ifstream ifs(fpath, std::ios::binary);
	if (!fileSize)
	{
		ifs.seekg(0, std::ios::end);
		fileSize = ifs.tellg() - fileOffset;
	}
	buffer.resize(fileSize);
	ifs.seekg(fileOffset, std::ios::beg);
	if (!ifs.read((char *)buffer.data(), buffer.size()))
		return false;
	return true;
}

void CustomBitmapManager::DeleteStorageItem(__int32 index) // 0x10784840
{
	StorageItem *item = &m_storageItems[index];
	item->loadState = ELoadState::kNone;
	item->refCount = 0;
	item->texture = nullptr;
	item->buffer.clear();
	item->salt = 0;
	item->createTextureFailed = false;
	item->keepAliveTimerMS = -1;
}

/* ---------- private code */

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { char const *kBasePath = "ui"; }
