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
		_extern bool _sub_106F3D40(__int32);
		bool HsThreadIsDead(__int32 threadIndex) // 0x106F3D40
		{
			mangled_x86(MANGLED_TODO, "?HsThreadIsDead@HS@Scripting@@YA_NH@Z");
			// __int32 threadIndex;
			todo("implement");
			bool __result = _sub_106F3D40(threadIndex);
			return __result;
		}

		_extern void *_sub_106F36B0(Scripting::HS::HsThreadStorage *const, unsigned __int32);
		void *HsThreadStorage::Allocate(unsigned __int32 size) // 0x106F36B0
		{
			mangled_x86(MANGLED_TODO, "?Allocate@HsThreadStorage@HS@Scripting@@QAEPAXI@Z");
			// unsigned __int32 size;
			// Scripting::HS::HsThreadStorage::MemBlock *block;
			todo("implement");
			void * __result = _sub_106F36B0(this, size);
			return __result;
		}

		_extern void _sub_106F3A60(Scripting::HS::HsThreadStorage *const, void *);
		void HsThreadStorage::Free(void *ptr) // 0x106F3A60
		{
			mangled_x86(MANGLED_TODO, "?Free@HsThreadStorage@HS@Scripting@@QAEXPAX@Z");
			// void *ptr;
			// Scripting::HS::HsThreadStorage::MemBlock *block;
			todo("implement");
			_sub_106F3A60(this, ptr);
		}

		_extern void _sub_106F3AF0(Scripting::HS::HsThreadStorage *const);
		void HsThreadStorage::FreeAll() // 0x106F3AF0
		{
			mangled_x86(MANGLED_TODO, "?FreeAll@HsThreadStorage@HS@Scripting@@QAEXXZ");
			// Scripting::HS::HsThreadStorage *const this;
			// Scripting::HS::HsThreadStorage::MemBlock *block;
			{
				// Scripting::HS::HsThreadStorage::MemBlock *next;
			}
			todo("implement");
			_sub_106F3AF0(this);
		}

		extern HsThreadStorage::MemBlock *_sub_106F3730(Scripting::HS::HsThreadStorage *const, unsigned __int32);
		Scripting::HS::HsThreadStorage::MemBlock *HsThreadStorage::AllocateBlock(unsigned __int32 size) // 0x106F3730
		{
			mangled_x86(MANGLED_TODO, "?AllocateBlock@HsThreadStorage@HS@Scripting@@AAEPAUMemBlock@123@I@Z");
			// unsigned __int32 size;
			// Scripting::HS::HsThreadStorage::MemBlock *block;
			// unsigned __int32 allocationSize;
			todo("implement");
			Scripting::HS::HsThreadStorage::MemBlock * __result = _sub_106F3730(this, size);
			return __result;
		}

		_extern void _sub_106F3B70(Scripting::HS::HsThreadStorage *const, Scripting::HS::HsThreadStorage::MemBlock *);
		void HsThreadStorage::FreeBlock(Scripting::HS::HsThreadStorage::MemBlock *block) // 0x106F3B70
		{
			mangled_x86(MANGLED_TODO, "?FreeBlock@HsThreadStorage@HS@Scripting@@AAEXPAUMemBlock@123@@Z");
			// Scripting::HS::HsThreadStorage::MemBlock *block;
			todo("implement");
			_sub_106F3B70(this, block);
		}

		_extern void _sub_106F3DC0(Scripting::HS::HsThreadStorage *const, Scripting::HS::HsThreadStorage::MemBlock **, Scripting::HS::HsThreadStorage::MemBlock *);
		void HsThreadStorage::InsertMemBlock(Scripting::HS::HsThreadStorage::MemBlock **list, Scripting::HS::HsThreadStorage::MemBlock *block) // 0x106F3DC0
		{
			mangled_x86(MANGLED_TODO, "?InsertMemBlock@HsThreadStorage@HS@Scripting@@AAEXPAPAUMemBlock@123@PAU4123@@Z");
			// Scripting::HS::HsThreadStorage::MemBlock *block;
			todo("implement");
			_sub_106F3DC0(this, list, block);
		}

		_extern void _sub_106F3F00(Scripting::HS::HsThreadStorage *const, Scripting::HS::HsThreadStorage::MemBlock **, Scripting::HS::HsThreadStorage::MemBlock *);
		void HsThreadStorage::RemoveMemBlock(Scripting::HS::HsThreadStorage::MemBlock **list, Scripting::HS::HsThreadStorage::MemBlock *block) // 0x106F3F00
		{
			mangled_x86(MANGLED_TODO, "?RemoveMemBlock@HsThreadStorage@HS@Scripting@@AAEXPAPAUMemBlock@123@PAU4123@@Z");
			// Scripting::HS::HsThreadStorage::MemBlock *block;
			todo("implement");
			_sub_106F3F00(this, list, block);
		}

		extern HsThreadStorageManager *_sub_106F3BE0();
		Scripting::HS::HsThreadStorageManager *HsThreadStorageManager::Get() // 0x106F3BE0
		{
			mangled_x86(MANGLED_TODO, "?Get@HsThreadStorageManager@HS@Scripting@@SAPAV123@XZ");
			// procedure flags: nofpo
			// static Scripting::HS::HsThreadStorageManager instance; // 0x113882AC
			// static __int32 $TSS0; // 0x113882D8
			todo("implement");
			Scripting::HS::HsThreadStorageManager * __result = _sub_106F3BE0();
			return __result;
		}

		_extern void *_sub_106F3E20(Scripting::HS::HsThreadStorageManager *const, __int32, unsigned __int32);
		void *HsThreadStorageManager::MemAlloc(__int32 threadIndex, unsigned __int32 size) // 0x106F3E20
		{
			mangled_x86(MANGLED_TODO, "?MemAlloc@HsThreadStorageManager@HS@Scripting@@QAEPAXHI@Z");
			// unsigned __int32 size;
			todo("implement");
			void * __result = _sub_106F3E20(this, threadIndex, size);
			return __result;
		}

		_extern void _sub_106F3E90(Scripting::HS::HsThreadStorageManager *const, __int32, void *);
		void HsThreadStorageManager::MemFree(__int32 threadIndex, void *ptr) // 0x106F3E90
		{
			mangled_x86(MANGLED_TODO, "?MemFree@HsThreadStorageManager@HS@Scripting@@QAEXHPAX@Z");
			// void *ptr;
			todo("implement");
			_sub_106F3E90(this, threadIndex, ptr);
		}

		extern HsThreadStorage *_sub_106F3CD0(Scripting::HS::HsThreadStorageManager *const, __int32);
		Scripting::HS::HsThreadStorage *HsThreadStorageManager::GetStorage(__int32 threadIndex) // 0x106F3CD0
		{
			mangled_x86(MANGLED_TODO, "?GetStorage@HsThreadStorageManager@HS@Scripting@@QAEPAVHsThreadStorage@23@H@Z");
			// __int32 threadIndex;
			todo("implement");
			Scripting::HS::HsThreadStorage * __result = _sub_106F3CD0(this, threadIndex);
			return __result;
		}

		_extern void _sub_106F3FA0(Scripting::HS::HsThreadStorageManager *const);
		void HsThreadStorageManager::Reset() // 0x106F3FA0
		{
			mangled_x86(MANGLED_TODO, "?Reset@HsThreadStorageManager@HS@Scripting@@QAEXXZ");
			// Scripting::HS::HsThreadStorageManager *const this;
			todo("implement");
			_sub_106F3FA0(this);
		}

		_extern void _sub_106F39F0(Scripting::HS::HsThreadStorageManager *const, __int32);
		void HsThreadStorageManager::DeleteStorage(__int32 threadIndex) // 0x106F39F0
		{
			mangled_x86(MANGLED_TODO, "?DeleteStorage@HsThreadStorageManager@HS@Scripting@@QAEXH@Z");
			// __int32 threadIndex;
			todo("implement");
			_sub_106F39F0(this, threadIndex);
		}

		_extern void _sub_106F4000(Scripting::HS::HsThreadStorageManager *const, unsigned __int32);
		void HsThreadStorageManager::Update(unsigned __int32 time) // 0x106F4000
		{
			mangled_x86(MANGLED_TODO, "?Update@HsThreadStorageManager@HS@Scripting@@QAEXI@Z");
			// unsigned __int32 time;
			todo("implement");
			_sub_106F4000(this, time);
		}

		_extern void _sub_106F37C0(Scripting::HS::HsThreadStorageManager *const, unsigned __int32);
		void HsThreadStorageManager::CollectGarbage(unsigned __int32 time) // 0x106F37C0
		{
			mangled_x86(MANGLED_TODO, "?CollectGarbage@HsThreadStorageManager@HS@Scripting@@AAEXI@Z");
			// static ...; // 0x106F3968
			// static ...; // 0x106F3960
			// Scripting::HS::HsThreadStorageManager *const this;
			// unsigned __int32 time;
			{
				// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<int const ,Scripting::HS::HsThreadStorage> > > > it;
			}
			todo("implement");
			_sub_106F37C0(this, time);
		}
	}
}

/* ---------- private code */
