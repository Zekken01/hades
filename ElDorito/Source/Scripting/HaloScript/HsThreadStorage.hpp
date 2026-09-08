#ifndef __SCRIPTING_HALOSCRIPT_HSTHREADSTORAGE_HPP__
#define __SCRIPTING_HALOSCRIPT_HSTHREADSTORAGE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/ForgeUndo.hpp"
#include "Forge/Magnets.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

/* ---------- forward declarations */

namespace Scripting
{
	namespace HS
	{
		class HsThreadStorage;
		class HsThreadStorageManager;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Scripting
{
	namespace HS
	{
		class HsThreadStorage
		{
		public:
		private:
			public:
			struct MemBlock
			{
				MemBlock *next; // 0x0
				MemBlock *previous; // 0x4
				unsigned __int32 size; // 0x8
			};
			static_assert(sizeof(MemBlock) == 12, "Invalid MemBlock size");
			public:
			MemBlock *m_blockList; // 0x0
			unsigned __int32 m_allocatedSize; // 0x4
		public:
			HsThreadStorage(Scripting::HS::HsThreadStorage &);
			HsThreadStorage(Scripting::HS::HsThreadStorage const &);
			_inline HsThreadStorage();
			_inline ~HsThreadStorage();
			void *Allocate(unsigned __int32 size);
			void Free(void *ptr);
			void FreeAll();
		private:
			MemBlock *AllocateBlock(unsigned __int32 size);
			void FreeBlock(MemBlock *block);
			void InsertMemBlock(MemBlock **list, MemBlock *block);
			void RemoveMemBlock(MemBlock **list, MemBlock *block);
				char data[0]; // 0xC
		};
		static_assert(sizeof(Scripting::HS::HsThreadStorage) == 8, "Invalid Scripting::HS::HsThreadStorage size");
	}
}

#pragma pack(push, 4)
namespace Scripting
{
	namespace HS
	{
		class HsThreadStorageManager
		{
		private:
			std::unordered_map<int,Scripting::HS::HsThreadStorage,std::hash<int>,std::equal_to<int>,std::allocator<std::pair<int const ,Scripting::HS::HsThreadStorage> > > m_threadStorage; // 0x0
			unsigned __int32 m_lastCollectionTime; // 0x28
		public:
			HsThreadStorageManager(Scripting::HS::HsThreadStorageManager &);
			HsThreadStorageManager(Scripting::HS::HsThreadStorageManager const &);
		private:
			_inline HsThreadStorageManager();
		public:
			_inline ~HsThreadStorageManager();
			static Scripting::HS::HsThreadStorageManager *Get();
			Scripting::HS::HsThreadStorage *GetStorage(__int32 threadIndex);
			void Reset();
			void DeleteStorage(__int32 threadIndex);
			void *MemAlloc(__int32 threadIndex, unsigned __int32 size);
			void MemFree(__int32 threadIndex, void *ptr);
			void Update(unsigned __int32 time);
		private:
			void CollectGarbage(unsigned __int32 time);
		};
	}
}

#pragma pack(pop)
static_assert(sizeof(Scripting::HS::HsThreadStorageManager) == 44, "Invalid Scripting::HS::HsThreadStorageManager size");

/* ---------- prototypes */

namespace Scripting
{
	namespace HS
	{
		extern bool HsThreadIsDead(__int32 threadIndex);

		extern _inline char const *HsThreadString(long thread_index, std::string_view str);
	}
}

/* ---------- globals */

/* ---------- public code */

namespace Scripting
{
	namespace HS
	{
		extern HsThreadStorage* _sub_106F25A0(Scripting::HS::HsThreadStorage *const);
		_inline HsThreadStorage::HsThreadStorage() // 0x106F25A0
		{
			mangled_x86(MANGLED_TODO, "??0HsThreadStorage@HS@Scripting@@QAE@XZ");
			// Scripting::HS::HsThreadStorage *const this;
			todo("implement");
			_sub_106F25A0(this);
		}

		_extern void _sub_106F2C40(Scripting::HS::HsThreadStorage *const);
		_inline HsThreadStorage::~HsThreadStorage() // 0x106F2C40
		{
			mangled_x86(MANGLED_TODO, "??1HsThreadStorage@HS@Scripting@@QAE@XZ");
			// Scripting::HS::HsThreadStorage *const this;
			todo("implement");
			_sub_106F2C40(this);
		}

		extern HsThreadStorageManager* _sub_106F25E0(Scripting::HS::HsThreadStorageManager *const);
		_inline HsThreadStorageManager::HsThreadStorageManager() // 0x106F25E0
		{
			mangled_x86(MANGLED_TODO, "??0HsThreadStorageManager@HS@Scripting@@AAE@XZ");
			// Scripting::HS::HsThreadStorageManager *const this;
			todo("implement");
			_sub_106F25E0(this);
		}

		_extern void _sub_106F2CD0(Scripting::HS::HsThreadStorageManager *const);
		_inline HsThreadStorageManager::~HsThreadStorageManager() // 0x106F2CD0
		{
			mangled_x86(MANGLED_TODO, "??1HsThreadStorageManager@HS@Scripting@@QAE@XZ");
			// Scripting::HS::HsThreadStorageManager *const this;
			todo("implement");
			_sub_106F2CD0(this);
		}
	}
}

extern char const *_sub_106FAAF0(long, std::string_view);
namespace Scripting
{
	namespace HS
	{
		_inline char const *HsThreadString(long thread_index, std::string_view str) // 0x106FAAF0
		{
			mangled_x86(MANGLED_TODO, "?HsThreadString@HS@Scripting@@YAPBDJV?$basic_string_view@DU?$char_traits@D@std@@@std@@@Z");
			// std::string_view str;
			// char *mem;
			todo("implement");
			char const * __result = _sub_106FAAF0(thread_index, str);
			return __result;
		}
	}
}

/* ---------- private code */

#endif // __SCRIPTING_HALOSCRIPT_HSTHREADSTORAGE_HPP__
