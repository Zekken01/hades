#ifndef __INTERFACE_CUSTOMBITMAPMANAGER_HPP__
#define __INTERFACE_CUSTOMBITMAPMANAGER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Player/PlayerEmblemGenerator.hpp"
#include "Web/WebRenderHandlerGpu.hpp"

#include <array>
#include <chrono>
#include <memory>
#include <shared_mutex>
#include <string>
#include <vector>

/* ---------- forward declarations */

class CustomBitmapManager;

/* ---------- constants */

/* ---------- definitions */

class CustomBitmapManager
{
public:
	public:
	enum class ELoadState : unsigned short // hades: scoped (the original compares it at word width)
	{
		kNone = 0,
		kLoading,
		kLoaded,
		kFailed,
	};
	struct StorageItem
	{
		unsigned short salt; // 0x0
		unsigned short refCount; // 0x2
		ELoadState loadState; // 0x4
		unsigned short loadTaskId; // 0x6
		std::string path; // 0x8
		std::string fallbackPath; // 0x24
		std::vector<unsigned char> buffer; // 0x40
		std::shared_mutex bufferLock; // 0x50
		Microsoft::WRL::ComPtr<IDirect3DTexture9> texture; // 0x54
		bool createTextureFailed; // 0x58
		unsigned __int32 keepAliveTimerMS; // 0x5C
		_inline bool InUse() const;
		_inline StorageItem() = default; /* compiler_generated() */
		_inline ~StorageItem(); /* compiler_generated() */
	};
	static_assert(sizeof(StorageItem) == 96, "Invalid StorageItem size");
	static_assert(offsetof(StorageItem, keepAliveTimerMS) == 0x5C, "StorageItem::keepAliveTimerMS moved when its reconstructed padding was removed");
	public:
	static __int32 const kInvalidHandle;
	static __int32 const kMaxStorageItems;
	static CustomBitmapManager *Get();
	__int32 FindOrAllocateBitmap(std::string const &path);
	void BitmapAddRef(__int32 handle);
	void BitmapRelease(__int32 handle);
	void BitmapLoadFromFileAsync(__int32 handle, std::string path, std::string fallbackPath);
	IDirect3DTexture9 *BitmapGetTexture(__int32 handle);
	void UpdateRender();
private:
	__int32 MakeHandle(unsigned short salt, unsigned short index);
	unsigned short NextSalt();
	__int32 GetFreeStorageItem();
	StorageItem *GetStorageItem(__int32 handle);
	void DeleteStorageItem(__int32 index);
	bool LoadFileIntoBufferBlocking(std::string const &url, std::vector<unsigned char> &buffer);
	__int32 FindStorageItemWithPath(std::string const &path);
	std::shared_mutex m_lock; // 0x0
	std::array<StorageItem,32> m_storageItems; // 0x4
	unsigned short m_nextSalt = 0; // 0xC04
	unsigned char __pad0[2]; // 0xC06
	std::string m_currentModHash; // 0xC08
	unsigned char __pad1[4]; // 0xC24
	std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000> > > m_lastUpdateRenderTime; // 0xC28
public:
	_inline CustomBitmapManager() = default; /* compiler_generated() */
	_inline ~CustomBitmapManager(); /* compiler_generated() */
};
static_assert(sizeof(CustomBitmapManager) == 3120, "Invalid CustomBitmapManager size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

inline bool CustomBitmapManager::StorageItem::InUse() const // 0x10784EB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?InUse@StorageItem@CustomBitmapManager@@QBE_NXZ");
	// CustomBitmapManager::StorageItem const *const this;

	return salt != 0;
}

/* ---------- private code */

#endif // __INTERFACE_CUSTOMBITMAPMANAGER_HPP__
