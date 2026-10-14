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
			mangled_x86(MANGLED_KNOWN_GOOD, "?HsThreadIsDead@HS@Scripting@@YA_NH@Z");
			// __int32 threadIndex;

			return hs_thread_get(threadIndex) == nullptr;
		}

		void *HsThreadStorage::Allocate(unsigned __int32 size) // 0x106F36B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Allocate@HsThreadStorage@HS@Scripting@@QAEPAXI@Z");
			// unsigned __int32 size;
			// Scripting::HS::HsThreadStorage::MemBlock *block;

			Scripting::HS::HsThreadStorage::MemBlock *block = AllocateBlock(size);

			InsertMemBlock(&m_blockList, block);
			return block + 1;
		}

		void HsThreadStorage::Free(void *ptr) // 0x106F3A60
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Free@HsThreadStorage@HS@Scripting@@QAEXPAX@Z");
			// void *ptr;
			// Scripting::HS::HsThreadStorage::MemBlock *block;

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
			mangled_x86(MANGLED_KNOWN_GOOD, "?FreeAll@HsThreadStorage@HS@Scripting@@QAEXXZ");
			// Scripting::HS::HsThreadStorage *const this;
			// Scripting::HS::HsThreadStorage::MemBlock *block;
				// Scripting::HS::HsThreadStorage::MemBlock *next;

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
			mangled_x86(MANGLED_KNOWN_GOOD, "?AllocateBlock@HsThreadStorage@HS@Scripting@@AAEPAUMemBlock@123@I@Z");
			// unsigned __int32 size;
			// Scripting::HS::HsThreadStorage::MemBlock *block;
			// unsigned __int32 allocationSize;

			unsigned __int32 blockSize = size + 12;
			MemBlock *block = (MemBlock *)operator new(blockSize);
			*(unsigned __int32 *)((unsigned char *)block + 8) = size;
			m_allocatedSize += blockSize;

			return block;
		}

		void HsThreadStorage::FreeBlock(Scripting::HS::HsThreadStorage::MemBlock *block) // 0x106F3B70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?FreeBlock@HsThreadStorage@HS@Scripting@@AAEXPAUMemBlock@123@@Z");
			// Scripting::HS::HsThreadStorage::MemBlock *block;

			m_allocatedSize -= block->size + 12;
			::operator delete(block);
		}

		void HsThreadStorage::InsertMemBlock(Scripting::HS::HsThreadStorage::MemBlock **list, Scripting::HS::HsThreadStorage::MemBlock *block) // 0x106F3DC0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?InsertMemBlock@HsThreadStorage@HS@Scripting@@AAEXPAPAUMemBlock@123@PAU4123@@Z");
			// Scripting::HS::HsThreadStorage::MemBlock *block;

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
			mangled_x86(MANGLED_KNOWN_GOOD, "?RemoveMemBlock@HsThreadStorage@HS@Scripting@@AAEXPAPAUMemBlock@123@PAU4123@@Z");
			// Scripting::HS::HsThreadStorage::MemBlock *block;

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
			mangled_x86(MANGLED_KNOWN_GOOD, "?Get@HsThreadStorageManager@HS@Scripting@@SAPAV123@XZ");
			// procedure flags: nofpo
			// static Scripting::HS::HsThreadStorageManager instance; // 0x113882AC
			// static __int32 $TSS0; // 0x113882D8

			static Scripting::HS::HsThreadStorageManager instance;
			return &instance;
		}

		void *HsThreadStorageManager::MemAlloc(__int32 threadIndex, unsigned __int32 size) // 0x106F3E20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?MemAlloc@HsThreadStorageManager@HS@Scripting@@QAEPAXHI@Z");
			// unsigned __int32 size;

			return GetStorage(threadIndex)->Allocate(size);
		}

		void HsThreadStorageManager::MemFree(__int32 threadIndex, void *ptr) // 0x106F3E90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?MemFree@HsThreadStorageManager@HS@Scripting@@QAEXHPAX@Z");
			// void *ptr;

			GetStorage(threadIndex)->Free(ptr);
		}

		Scripting::HS::HsThreadStorage *HsThreadStorageManager::GetStorage(__int32 threadIndex) // 0x106F3CD0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetStorage@HsThreadStorageManager@HS@Scripting@@QAEPAVHsThreadStorage@23@H@Z");
			// __int32 threadIndex;

			return &m_threadStorage[threadIndex];
		}

		void HsThreadStorageManager::Reset() // 0x106F3FA0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Reset@HsThreadStorageManager@HS@Scripting@@QAEXXZ");
			// Scripting::HS::HsThreadStorageManager *const this;

			m_threadStorage.clear();
			m_lastCollectionTime = 0;
		}

		void HsThreadStorageManager::DeleteStorage(__int32 threadIndex) // 0x106F39F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?DeleteStorage@HsThreadStorageManager@HS@Scripting@@QAEXH@Z");
			// __int32 threadIndex;

			m_threadStorage.erase(threadIndex);
		}

		void HsThreadStorageManager::Update(unsigned __int32 time) // 0x106F4000
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Update@HsThreadStorageManager@HS@Scripting@@QAEXI@Z");
			// unsigned __int32 time;

			if (time - m_lastCollectionTime >= 100)
				CollectGarbage(time);
		}

		void HsThreadStorageManager::CollectGarbage(unsigned __int32 time) // 0x106F37C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?CollectGarbage@HsThreadStorageManager@HS@Scripting@@AAEXI@Z");
			// static ...; // 0x106F3968
			// static ...; // 0x106F3960
			// Scripting::HS::HsThreadStorageManager *const this;
			// unsigned __int32 time;
				// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<int const ,Scripting::HS::HsThreadStorage> > > > it;

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
