/* ---------- headers */

#include "Scripting/HaloScript/HsThreadStorage.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Forge/ForgeUndo.hpp"
#include "Forge/Magnets.hpp"
#include "Utils/NameValueTable.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <list>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Scripting
{
	namespace HS
	{
		class HsThreadStorage;
		class HsThreadStorageManager;
	}
}

namespace Scripting {}
using namespace ::Scripting;
namespace Scripting
{
	namespace HS {}
	using namespace Scripting::HS;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

struct s_hs_thread *hs_thread_get(unsigned long thread_index);  // hades: added for 0X106F3D40

namespace Scripting
{
	namespace HS
	{
		extern bool HsThreadIsDead(__int32 threadIndex);
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Scripting
{
	namespace HS
	{
		bool HsThreadIsDead(__int32 threadIndex) // 0x106F3D40
		{
			return hs_thread_get(threadIndex) == nullptr;
		}

		void *HsThreadStorage::Allocate(unsigned __int32 size) // 0x106F36B0
		{
			Scripting::HS::HsThreadStorage::MemBlock *block = AllocateBlock(size);

			InsertMemBlock(&m_blockList, block);
			return block + 1;
		}

		void HsThreadStorage::Free(void *ptr) // 0x106F3A60
		{
			if (ptr == nullptr)
			{
				return;
			}

			MemBlock *block = &((MemBlock *)ptr)[-1];
			RemoveMemBlock(&m_blockList, block);
			FreeBlock(block);
		}

		void HsThreadStorage::FreeAll() // 0x106F3AF0
		{
			MemBlock *block = m_blockList;
			while (block)
			{
				MemBlock *next = block->next;
				FreeBlock(block);
				block = next;
			}

			m_blockList = nullptr;
		}

		Scripting::HS::HsThreadStorage::MemBlock *HsThreadStorage::AllocateBlock(unsigned __int32 size) // 0x106F3730
		{
			unsigned __int32 blockSize = size + 12;
			MemBlock *block = (MemBlock *)operator new(blockSize);
			*(unsigned __int32 *)((unsigned char *)block + 8) = size;
			m_allocatedSize += blockSize;

			return block;
		}

		void HsThreadStorage::FreeBlock(Scripting::HS::HsThreadStorage::MemBlock *block) // 0x106F3B70
		{
			m_allocatedSize -= block->size + 12;
			::operator delete(block);
		}

		void HsThreadStorage::InsertMemBlock(Scripting::HS::HsThreadStorage::MemBlock **list, Scripting::HS::HsThreadStorage::MemBlock *block) // 0x106F3DC0
		{
			block->previous = nullptr;
			block->next = *list;
			if (block->next)
			{
				block->next->previous = block;
			}
			*list = block;
		}

		void HsThreadStorage::RemoveMemBlock(Scripting::HS::HsThreadStorage::MemBlock **list, Scripting::HS::HsThreadStorage::MemBlock *block) // 0x106F3F00
		{
			if (*list == block)
			{
				*list = block->next;
				if (block->next)
					block->previous = nullptr;
			}
			else
			{
				if (block->previous)
					block->previous->next = block->next;
				if (block->next)
					block->next->previous = block->previous;
			}
			block->next = nullptr;
			block->previous = nullptr;
		}

		Scripting::HS::HsThreadStorageManager *HsThreadStorageManager::Get() // 0x106F3BE0
		{
			static Scripting::HS::HsThreadStorageManager instance;
			return &instance;
		}

		void *HsThreadStorageManager::MemAlloc(__int32 threadIndex, unsigned __int32 size) // 0x106F3E20
		{
			return GetStorage(threadIndex)->Allocate(size);
		}

		void HsThreadStorageManager::MemFree(__int32 threadIndex, void *ptr) // 0x106F3E90
		{
			GetStorage(threadIndex)->Free(ptr);
		}

		Scripting::HS::HsThreadStorage *HsThreadStorageManager::GetStorage(__int32 threadIndex) // 0x106F3CD0
		{
			return &m_threadStorage[threadIndex];
		}

		void HsThreadStorageManager::Reset() // 0x106F3FA0
		{
			m_threadStorage.clear();
			m_lastCollectionTime = 0;
		}

		void HsThreadStorageManager::DeleteStorage(__int32 threadIndex) // 0x106F39F0
		{
			m_threadStorage.erase(threadIndex);
		}

		void HsThreadStorageManager::Update(unsigned __int32 time) // 0x106F4000
		{
			if (time - m_lastCollectionTime >= 100)
				CollectGarbage(time);
		}

		void HsThreadStorageManager::CollectGarbage(unsigned __int32 time) // 0x106F37C0
		{
			m_lastCollectionTime = time;
			for (auto it = m_threadStorage.begin(); it != m_threadStorage.end();)
			{
				if (HsThreadIsDead(it->first))
					it = m_threadStorage.erase(it);
				else
					++it;
			}
		}
	}
}

/* ---------- private code */
