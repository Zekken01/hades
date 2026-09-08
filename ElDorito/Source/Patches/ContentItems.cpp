/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "ElDorito.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "ThirdParty/dirent.h"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "Utils/Macros.hpp"
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"

#include <Windows.h>
#include <commctrl.h>
#include <dpa_dsa.h>
#include <propkeydef.h>
#include <propsys.h>
#include <shlobj_core.h>
#include <shobjidl.h>
#include <shobjidl_core.h>
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
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct DIR;
struct begin;
struct dirent;
struct end;
struct s_ContentItemRenameState;
struct s_datum;
namespace hades_file_local
{
	struct c_content_item;
	struct c_content_catalog;
	struct c_content_item_overlapped_task;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Ui {}
	using namespace Web::Ui;
}

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer {}
		using namespace Web::Ui::ScreenLayer;
	}
}

namespace Web
{
	namespace Browser {}
	using namespace Web::Browser;
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge {}
		using namespace Web::Browser::Bridge;
	}
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace ContentItems {}
	using namespace Patches::ContentItems;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct c_content_item :
		public s_datum
	{
		unsigned short Unknown02; // 0x2
		unsigned __int32 Unknown04; // 0x4
		__int32 ContentType; // 0x8
		c_content_catalog *Catalog; // 0xC
		unsigned char ContentHeader[248]; // 0x10
		__int32 Unknown108; // 0x108
		__int32 Unknown10C; // 0x10C
		wchar_t RelativeFilePath[128]; // 0x110
	};
	static_assert(sizeof(c_content_item) == 528, "Invalid c_content_item size");

	struct c_content_catalog
	{
		__int32 LocalProfileIndex; // 0x0
		c_data_array<c_content_item> *Items; // 0x4
		unsigned char Unknown08[680]; // 0x8
	};
	static_assert(sizeof(c_content_catalog) == 688, "Invalid c_content_catalog size");

	//@@anonymous-namespace@@
	struct c_content_item_overlapped_task
	{
		__int32 LocalProfileIndex; // 0x0
		unsigned __int32 ContentItemDatumIndex; // 0x4
		wchar_t *NewContentName; // 0x8
		wchar_t *NewContentDescription; // 0xC
		long *CompletionState; // 0x10
		long *CompletionStatus; // 0x14
	};
	static_assert(sizeof(c_content_item_overlapped_task) == 24, "Invalid c_content_item_overlapped_task size");
}
using namespace hades_file_local;
struct s_ContentItemRenameState
{
	bool IsValid; // 0x0
	wchar_t NewPath[128]; // 0x2
};
// static_assert(sizeof(s_ContentItemRenameState) == 258, "Invalid s_ContentItemRenameState size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

/* ---------- prototypes */

namespace Patches
{
	namespace ContentItems
	{
		extern void ApplyAll();
	}
}

bool AddContentItem(wchar_t *itemPath);
bool AddContentItem(std::basic_string<char,std::char_traits<char>,std::allocator<char> > itemPath);
void GetFilePathForItem(wchar_t *dest, unsigned __int32 MaxCount, wchar_t *variantName, __int32 variantType);
void AddAllBLFContentItems(std::basic_string<char,std::char_traits<char>,std::allocator<char> > path);
char CallsXEnumerateHook();
char FS_GetFiloForContentItemHook(c_content_item *contentItem, void *unused, void *filo);
wchar_t *FS_GetFilePathForContentItemHook(c_content_item *contentItem, void *unused, wchar_t *dest, unsigned __int32 MaxCount);
bool ContainsForbiddenCharacters(wchar_t *namePtr);
bool SaveFileGetNameHook(unsigned char *blfStart, void *unused, __int32 a2, wchar_t *Src, unsigned __int32 MaxCount);
bool c_content_item__init_hook(c_content_item *thisptr, void *unused, __int32 contentType, c_content_catalog *catalog, wchar_t *name, wchar_t *dashMetadata, __int32 a5, __int32 a6, __int32 a7);
char PackageMountHook(__int32 a1, __int32 a2, __int32 a3, __int32 a4);
unsigned __int32 PackageMountHook2(__int32 localProfileIndex, wchar_t *name, __int32 contentType, long volatile *pStatus, long volatile *pState, long volatile *pContentItemDatumIndex);
char *AllocateGameGlobalMemory2Hook(char *Src, __int32 a2, __int32 a3, char a4, void *a5);
bool IsProfileAvailable();
wchar_t *GetDirectoryPathW(wchar_t *path, wchar_t *buff, __int32 bufflen);
__int32 content_item_overlapped_task_execute_hook(c_content_item_overlapped_task *task);
void c_content_item_delete_hook(c_content_item *thisptr, void *unused, __int32 a1);
void c_gui_screen_pregame_selection__overlapped_task_update_hook(unsigned char *thisptr, void *unused);
bool c_gui_map_selected_item__get_file_path_hook(void *thisptr, void *unused, char *buff, __int32 bufflen);
bool c_gui_game_variant_selected_item__get_file_path_hook(void *thisptr, void *unused, char *buff, __int32 bufflen);
__int32 file_write_overlapped_task_execute_hook(unsigned char *task);
bool game_variant_description_override_hook(__int32 chud_handle, __int32 a2, __int32 stringid, __int32 *a4, __int32 length);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern bool saving_new_gametype; // 0x12458148
	extern unsigned char *contentItemsGlobal; // 0x12458254
	extern bool enumerated; // 0x12458149
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace ContentItems
	{
		_extern void _sub_10A3ACF0();
		void ApplyAll() // 0x10A3ACF0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@ContentItems@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A3ACF0();
		}
	}
}

/* ---------- private code */

_extern bool _sub_10A3A620(wchar_t *);
bool AddContentItem(wchar_t *itemPath) // 0x10A3A620
{
	// `anonymous-namespace'::AddContentItem
	// static ...; // 0x10A3A9E5
	// static ...; // 0x10A3A9E0
	// static ...; // 0x10A3A9DA
	// static ...; // 0x10A3A9D5
	// static ...; // 0x10A3A9C8
	// static ...; // 0x10A3A98C
	// static ...; // 0x10A3A984
	// wchar_t *itemPath;
	// __int32 dataIdx;
	// __int32 (*globalsArrayPush)(void *);
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > path;
	// unsigned char *dataBasePtr;
	// long fileSize;
	// _iobuf *file;
	// unsigned __int32 magic;
	// std::filesystem::path relativePath;
	// c_content_item *contentItem;
	// c_content_catalog *contentCatalog;
	// unsigned char fileData[248];
	// c_content_catalog *(*const content_catalog_get)(__int32);
	// __int32 contentType;
	// __int32 (*const sub_525330)(__int32);
	// function call : __int32 (*)(void *)
	// function call : c_content_catalog *(*const)(__int32)
	// function call : __int32 (*const)(__int32)
	todo("implement");
	bool __result = _sub_10A3A620(itemPath);
	return __result;
}

_extern bool _sub_10A3AAF0(std::string);
bool AddContentItem(std::basic_string<char,std::char_traits<char>,std::allocator<char> > itemPath) // 0x10A3AAF0
{
	// `anonymous-namespace'::AddContentItem
	// static ...; // 0x10A3ABE0
	// static ...; // 0x10A3ABD4
	// static ...; // 0x10A3ABCC
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > itemPath;
	// std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > unicode;
	todo("implement");
	bool __result = _sub_10A3AAF0(itemPath);
	return __result;
}

_extern void _sub_10A3D300(wchar_t *, unsigned __int32, wchar_t *, __int32);
void GetFilePathForItem(wchar_t *dest, unsigned __int32 MaxCount, wchar_t *variantName, __int32 variantType) // 0x10A3D300
{
	// `anonymous-namespace'::GetFilePathForItem
	// wchar_t *dest;
	// unsigned __int32 MaxCount;
	// wchar_t *variantName;
	// __int32 variantType;
	// wchar_t currentDir[128];
	{
		// wchar_t *fileName;
		// wchar_t *(*FS_GetFileNameForItemType)(unsigned __int32);
	}
	// function call : unsigned long (unsigned long, wchar_t *)
	// function call : wchar_t *(*)(unsigned __int32)
	todo("implement");
	_sub_10A3D300(dest, MaxCount, variantName, variantType);
}

_extern void _sub_10A3A2F0(std::string);
void AddAllBLFContentItems(std::basic_string<char,std::char_traits<char>,std::allocator<char> > path) // 0x10A3A2F0
{
	// `anonymous-namespace'::AddAllBLFContentItems
	// static ...; // 0x10A3A56C
	// static ...; // 0x10A3A560
	// static ...; // 0x10A3A558
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > path;
	// dirent *entry;
	// DIR *dp;
	{
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > filePath;
	}
	todo("implement");
	_sub_10A3A2F0(path);
}

_extern char _sub_10A3C6B0();
char CallsXEnumerateHook() // 0x10A3C6B0
{
	// `anonymous-namespace'::CallsXEnumerateHook
	// procedure flags: nofpo
	// static ...; // 0x10A3C979
	// static ...; // 0x10A3C96D
	// static ...; // 0x10A3C964
	// static ...; // 0x10A3C940
	// static ...; // 0x10A3C938
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > mapsPath;
	// char currentDir[128];
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > variantPath;
	// function call : unsigned long (unsigned long, char *)
	todo("implement");
	char __result = _sub_10A3C6B0();
	return __result;
}

_extern char _sub_10A3D0A0(c_content_item *, void *, void *);
char FS_GetFiloForContentItemHook(c_content_item *contentItem, void *unused, void *filo) // 0x10A3D0A0
{
	// `anonymous-namespace'::FS_GetFiloForContentItemHook
	// static ...; // 0x10A3D1E8
	// static ...; // 0x10A3D1E0
	// c_content_item *contentItem;
	// void *unused;
	// void *filo;
	// std::filesystem::path path;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > relativePath;
	// void *(*fsCallsSetupFiloStruct2)(void *, wchar_t const *, char);
	// function call : void *(*)(void *, wchar_t const *, char)
	todo("implement");
	char __result = _sub_10A3D0A0(contentItem, unused, filo);
	return __result;
}

_extern wchar_t *_sub_10A3CEF0(c_content_item *, void *, wchar_t *, unsigned __int32);
wchar_t *FS_GetFilePathForContentItemHook(c_content_item *contentItem, void *unused, wchar_t *dest, unsigned __int32 MaxCount) // 0x10A3CEF0
{
	// `anonymous-namespace'::FS_GetFilePathForContentItemHook
	// static ...; // 0x10A3D018
	// c_content_item *contentItem;
	// void *unused;
	// wchar_t *dest;
	// unsigned __int32 MaxCount;
	// std::filesystem::path path;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > relativePath;
	todo("implement");
	wchar_t * __result = _sub_10A3CEF0(contentItem, unused, dest, MaxCount);
	return __result;
}

_extern bool _sub_10A3CA40(wchar_t *);
bool ContainsForbiddenCharacters(wchar_t *namePtr) // 0x10A3CA40
{
	// `anonymous-namespace'::ContainsForbiddenCharacters
	// static ...; // 0x10A3CDF1
	// static ...; // 0x10A3CDED
	// static ...; // 0x10A3CDE8
	// static ...; // 0x10A3CDE3
	// static ...; // 0x10A3CDD1
	// static ...; // 0x10A3CDC0
	// static ...; // 0x10A3CD78
	// static ...; // 0x10A3CD70
	// wchar_t *namePtr;
	// std::initializer_list<char> illegalChars;
	// std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > temp;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > current_directory;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > name;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > parent_directory;
	{
		// std::initializer_list<char> &<range>$L0;
		// char const *<begin>$L0;
		// char const *<end>$L0;
		{
			// char c;
		}
	}
	todo("implement");
	bool __result = _sub_10A3CA40(namePtr);
	return __result;
}

_extern bool _sub_10A3D630(unsigned char *, void *, __int32, wchar_t *, unsigned __int32);
bool SaveFileGetNameHook(unsigned char *blfStart, void *unused, __int32 a2, wchar_t *Src, unsigned __int32 MaxCount) // 0x10A3D630
{
	// `anonymous-namespace'::SaveFileGetNameHook
	// unsigned __int32 MaxCount;
	// __int32 variantType;
	// wchar_t *variantName;
	todo("implement");
	bool __result = _sub_10A3D630(blfStart, unused, a2, Src, MaxCount);
	return __result;
}

_extern bool _sub_10A3E990(c_content_item *, void *, __int32, c_content_catalog *, wchar_t *, wchar_t *, __int32, __int32, __int32);
bool c_content_item__init_hook(c_content_item *thisptr, void *unused, __int32 contentType, c_content_catalog *catalog, wchar_t *name, wchar_t *dashMetadata, __int32 a5, __int32 a6, __int32 a7) // 0x10A3E990
{
	// `anonymous-namespace'::c_content_item__init_hook
	// c_content_catalog *catalog;
	// wchar_t *name;
	// wchar_t *dashMetadata;
	// __int32 a5;
	// __int32 a6;
	// __int32 a7;
	// __int32 (*const sub_5244C0)(__int32);
	// wchar_t buff[128];
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > itemPath;
	// std::filesystem::path relativePath;
	// function call : __int32 (*const)(__int32)
	todo("implement");
	bool __result = _sub_10A3E990(thisptr, unused, contentType, catalog, name, dashMetadata, a5, a6, a7);
	return __result;
}

_extern char _sub_10A3D610(__int32, __int32, __int32, __int32);
char PackageMountHook(__int32 a1, __int32 a2, __int32 a3, __int32 a4) // 0x10A3D610
{
	// `anonymous-namespace'::PackageMountHook
	// __int32 a4;
	todo("implement");
	char __result = _sub_10A3D610(a1, a2, a3, a4);
	return __result;
}

_extern unsigned __int32 _sub_10A3D4F0(__int32, wchar_t *, __int32, long volatile *, long volatile *, long volatile *);
unsigned __int32 PackageMountHook2(__int32 localProfileIndex, wchar_t *name, __int32 contentType, long volatile *pStatus, long volatile *pState, long volatile *pContentItemDatumIndex) // 0x10A3D4F0
{
	// `anonymous-namespace'::PackageMountHook2
	// long volatile *pContentItemDatumIndex;
	// unsigned __int32 contentItemIndex;
	// __int32 (*const c_content_catalog__get_or_create_content_item)(c_content_catalog *, wchar_t const *, wchar_t const *, __int32, char, __int32, __int32);
	// c_content_catalog *(*const content_catalog_get)(__int32);
	// __int32 status;
	// __int32 (*const sub_525330)(__int32);
	{
		// c_content_catalog *catalog;
	}
	// function call : __int32 (*const)(__int32)
	// function call : c_content_catalog *(*const)(__int32)
	// function call : __int32 (*const)(c_content_catalog *, wchar_t const *, wchar_t const *, __int32, char, __int32, __int32)
	todo("implement");
	unsigned __int32 __result = _sub_10A3D4F0(localProfileIndex, name, contentType, pStatus, pState, pContentItemDatumIndex);
	return __result;
}

_extern char *_sub_10A3AC30(char *, __int32, __int32, char, void *);
char *AllocateGameGlobalMemory2Hook(char *Src, __int32 a2, __int32 a3, char a4, void *a5) // 0x10A3AC30
{
	// `anonymous-namespace'::AllocateGameGlobalMemory2Hook
	// void *a5;
	// char *(*allocateGlobal)(char *, __int32, __int32, char, void *);
	// char *retData;
	// function call : char *(*)(char *, __int32, __int32, char, void *)
	todo("implement");
	char * __result = _sub_10A3AC30(Src, a2, a3, a4, a5);
	return __result;
}

bool IsProfileAvailable() // 0x10A3D4D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?IsProfileAvailable@@YA_NXZ");
	// `anonymous-namespace'::IsProfileAvailable
	// procedure flags: nofpo

	return true;
}

_extern wchar_t *_sub_10A3D270(wchar_t *, wchar_t *, __int32);
wchar_t *GetDirectoryPathW(wchar_t *path, wchar_t *buff, __int32 bufflen) // 0x10A3D270
{
	// `anonymous-namespace'::GetDirectoryPathW
	// __int32 bufflen;
	// wchar_t *filePart;
	todo("implement");
	wchar_t * __result = _sub_10A3D270(path, buff, bufflen);
	return __result;
}

_extern __int32 _sub_10A3F470(c_content_item_overlapped_task *);
__int32 content_item_overlapped_task_execute_hook(c_content_item_overlapped_task *task) // 0x10A3F470
{
	// `anonymous-namespace'::content_item_overlapped_task_execute_hook
	// static ...; // 0x10A3F9F6
	// static ...; // 0x10A3F9ED
	// static ...; // 0x10A3F9DB
	// static ...; // 0x10A3F9D3
	// static ...; // 0x10A3F9C6
	// static ...; // 0x10A3F9BE
	// static ...; // 0x10A3F9B2
	// static ...; // 0x10A3F9A8
	// static ...; // 0x10A3F948
	// static ...; // 0x10A3F940
	// c_content_item_overlapped_task *task;
	// c_content_catalog *(*const local_profile_get_content_catalog)(__int32);
	// bool (*const c_content_catalog__get_item_filo)(c_content_catalog *, unsigned __int32, void *);
	// unsigned __int32 (*const c_content_catalog__get_availability)(c_content_catalog *);
	// void (*const string_unicode_to_ascii)(wchar_t *, char *, __int32, void *);
	// bool (*const EditContentHeaderOverlappedTaskFunc)(c_content_item_overlapped_task *);
	{
		// c_content_catalog *catalog;
		{
			// c_content_item *item;
			{
				// unsigned char filo[520];
				// wchar_t newFilePathBuffer[128];
				// std::filesystem::path relativePath;
				// std::filesystem::path newPath;
				// bool v2;
				// char *filePath;
				{
					// __int32 n;
				}
				{
					// std::filesystem::path parent_path;
					// std::filesystem::path oldPath;
					// std::filesystem::path data_path;
				}
			}
		}
	}
	// function call : c_content_catalog *(*const)(__int32)
	// function call : unsigned __int32 (*const)(c_content_catalog *)
	// function call : bool (*const)(c_content_catalog *, unsigned __int32, void *)
	// function call : bool (*const)(c_content_item_overlapped_task *)
	// function call : bool (*const)(c_content_item_overlapped_task *)
	// function call : bool (*const)(c_content_item_overlapped_task *)
	todo("implement");
	__int32 __result = _sub_10A3F470(task);
	return __result;
}

_extern void _sub_10A3EC60(c_content_item *, void *, __int32);
void c_content_item_delete_hook(c_content_item *thisptr, void *unused, __int32 a1) // 0x10A3EC60
{
	// `anonymous-namespace'::c_content_item_delete_hook
	// static ...; // 0x10A3EE84
	// static ...; // 0x10A3EE60
	// static ...; // 0x10A3EE58
	// c_content_item *thisptr;
	// void *unused;
	// __int32 a1;
	// std::filesystem::path parent_path;
	// std::filesystem::path path;
	// std::filesystem::path data_path;
	todo("implement");
	_sub_10A3EC60(thisptr, unused, a1);
}

_extern void _sub_10A3F010(unsigned char *, void *);
void c_gui_screen_pregame_selection__overlapped_task_update_hook(unsigned char *thisptr, void *unused) // 0x10A3F010
{
	// `anonymous-namespace'::c_gui_screen_pregame_selection__overlapped_task_update_hook
	// static ...; // 0x10A3F294
	// static ...; // 0x10A3F28C
	// unsigned char *thisptr;
	// void *unused;
	// __int32 (*const c_gui_screen_widget__get_local_profile_index)(void *);
	// void *(*const c_gui_widget__find_named_child)(void *, unsigned __int32);
	// __int32 (*const c_gui_list_widget__get_selected_item_index)(void *);
	// void (*const c_gui_screen_pregame_selection__overlapped_task_update)(unsigned char *);
	// __int32 (*const c_filo__set_path)(void *, char *);
	// void *(*const c_gui_list_widget__get_ordered_data_source)(void *);
	{
		// void *subitem;
		{
			// __int32 selectedIndex;
			// void *datasource;
			{
				// void *item;
				// void *(*const c_ordered_datasource__get_item_at)(void *, __int32);
				{
					// std::filesystem::path bs;
				}
			}
		}
	}
	// function call : void *(*const)(void *, unsigned __int32)
	// function call : void *(*const)(void *)
	// function call : __int32 (*const)(void *)
	// function call : void *(*const)(void *, __int32)
	// function call : __int32 (*const)(void *, char *)
	// function call : void (*const)(unsigned char *)
	todo("implement");
	_sub_10A3F010(thisptr, unused);
}

_extern bool _sub_10A3EFA0(void *, void *, char *, __int32);
bool c_gui_map_selected_item__get_file_path_hook(void *thisptr, void *unused, char *buff, __int32 bufflen) // 0x10A3EFA0
{
	// `anonymous-namespace'::c_gui_map_selected_item__get_file_path_hook
	// __int32 bufflen;
	todo("implement");
	bool __result = _sub_10A3EFA0(thisptr, unused, buff, bufflen);
	return __result;
}

_extern bool _sub_10A3EF30(void *, void *, char *, __int32);
bool c_gui_game_variant_selected_item__get_file_path_hook(void *thisptr, void *unused, char *buff, __int32 bufflen) // 0x10A3EF30
{
	// `anonymous-namespace'::c_gui_game_variant_selected_item__get_file_path_hook
	// __int32 bufflen;
	todo("implement");
	bool __result = _sub_10A3EF30(thisptr, unused, buff, bufflen);
	return __result;
}

_extern __int32 _sub_10A3FE10(unsigned char *);
__int32 file_write_overlapped_task_execute_hook(unsigned char *task) // 0x10A3FE10
{
	// `anonymous-namespace'::file_write_overlapped_task_execute_hook
	// static ...; // 0x10A3FED0
	// static ...; // 0x10A3FEC4
	// static ...; // 0x10A3FEBC
	// unsigned char *task;
	// wchar_t directoryPath[128];
	// __int32 (*const file_write_overlapped_task_execute)(unsigned char *);
	// function call : __int32 (HWND__ *, wchar_t const *, _SECURITY_ATTRIBUTES const *)
	// function call : __int32 (*const)(unsigned char *)
	todo("implement");
	__int32 __result = _sub_10A3FE10(task);
	return __result;
}

_extern bool _sub_10A3FF20(__int32, __int32, __int32, __int32 *, __int32);
bool game_variant_description_override_hook(__int32 chud_handle, __int32 a2, __int32 stringid, __int32 *a4, __int32 length) // 0x10A3FF20
{
	// `anonymous-namespace'::game_variant_description_override_hook
	// __int32 length;
	// bool (*const sub_AA59B0)(__int32, __int32, __int32, void *, __int32);
	// function call : bool (*const)(__int32, __int32, __int32, void *, __int32)
	todo("implement");
	bool __result = _sub_10A3FF20(chud_handle, a2, stringid, a4, length);
	return __result;
}
