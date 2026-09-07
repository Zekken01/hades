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
	enum ELoadState : unsigned short
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
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > path; // 0x8
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > fallbackPath; // 0x24
		std::vector<unsigned char,std::allocator<unsigned char> > buffer; // 0x40
		std::shared_mutex bufferLock; // 0x50
		Microsoft::WRL::ComPtr<IDirect3DTexture9> texture; // 0x54
		bool createTextureFailed; // 0x58
		unsigned char __pad0[3]; // 0x59
		unsigned __int32 keepAliveTimerMS; // 0x5C
		_inline bool InUse() const;
		_inline StorageItem(); /* compiler_generated() */
		_inline ~StorageItem(); /* compiler_generated() */
	};
	static_assert(sizeof(StorageItem) == 96, "Invalid StorageItem size");
	public:
	static __int32 const kInvalidHandle;
	static __int32 const kMaxStorageItems;
	static CustomBitmapManager *Get();
	__int32 FindOrAllocateBitmap(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path);
	void BitmapAddRef(__int32 handle);
	void BitmapRelease(__int32 handle);
	void BitmapLoadFromFileAsync(__int32 handle, std::basic_string<char,std::char_traits<char>,std::allocator<char> > path, std::basic_string<char,std::char_traits<char>,std::allocator<char> > fallbackPath);
	IDirect3DTexture9 *BitmapGetTexture(__int32 handle);
	void UpdateRender();
private:
	__int32 MakeHandle(unsigned short salt, unsigned short index);
	unsigned short NextSalt();
	__int32 GetFreeStorageItem();
	StorageItem *GetStorageItem(__int32 handle);
	void DeleteStorageItem(__int32 index);
	bool LoadFileIntoBufferBlocking(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &url, std::vector<unsigned char,std::allocator<unsigned char> > &buffer);
	__int32 FindStorageItemWithPath(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &path);
	std::shared_mutex m_lock; // 0x0
	std::array<StorageItem,32> m_storageItems; // 0x4
	unsigned short m_nextSalt; // 0xC04
	unsigned char __pad0[2]; // 0xC06
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > m_currentModHash; // 0xC08
	unsigned char __pad1[4]; // 0xC24
	std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000> > > m_lastUpdateRenderTime; // 0xC28
public:
	_inline CustomBitmapManager(); /* compiler_generated() */
	_inline ~CustomBitmapManager(); /* compiler_generated() */
};
static_assert(sizeof(CustomBitmapManager) == 3120, "Invalid CustomBitmapManager size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_extern bool _sub_10784EB0(CustomBitmapManager::StorageItem const *const);
_inline bool CustomBitmapManager::StorageItem::InUse() const // 0x10784EB0
{
	mangled_x86(MANGLED_TODO, "?InUse@StorageItem@CustomBitmapManager@@QBE_NXZ");
	// CustomBitmapManager::StorageItem const *const this;
	todo("implement");
	bool __result = _sub_10784EB0((CustomBitmapManager::StorageItem const *)this);
	return __result;
}

/* ---------- private code */

#endif // __INTERFACE_CUSTOMBITMAPMANAGER_HPP__
