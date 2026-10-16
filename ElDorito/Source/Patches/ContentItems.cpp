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
bool AddContentItem(std::string itemPath);
void GetFilePathForItem(wchar_t *dest, unsigned __int32 MaxCount, wchar_t *variantName, __int32 variantType);
void AddAllBLFContentItems(std::string path);
char CallsXEnumerateHook();
char __fastcall FS_GetFiloForContentItemHook(c_content_item *contentItem, void *unused, void *filo);
wchar_t *__fastcall FS_GetFilePathForContentItemHook(c_content_item *contentItem, void *unused, wchar_t *dest, unsigned __int32 MaxCount);
bool __fastcall ContainsForbiddenCharacters(wchar_t *namePtr);
bool __fastcall SaveFileGetNameHook(unsigned char *blfStart, void *unused, __int32 a2, wchar_t *Src, unsigned __int32 MaxCount);
bool __fastcall c_content_item__init_hook(c_content_item *thisptr, void *unused, __int32 contentType, c_content_catalog *catalog, wchar_t *name, wchar_t *dashMetadata, __int32 a5, __int32 a6, __int32 a7);
char __stdcall PackageMountHook(__int32 a1, __int32 a2, __int32 a3, __int32 a4);
unsigned __int32 PackageMountHook2(__int32 localProfileIndex, wchar_t *name, __int32 contentType, long volatile *pStatus, long volatile *pState, long volatile *pContentItemDatumIndex);
char *AllocateGameGlobalMemory2Hook(char *Src, __int32 a2, __int32 a3, char a4, void *a5);
bool IsProfileAvailable();
wchar_t *GetDirectoryPathW(wchar_t *path, wchar_t *buff, __int32 bufflen);
__int32 content_item_overlapped_task_execute_hook(c_content_item_overlapped_task *task);
void __fastcall c_content_item_delete_hook(c_content_item *thisptr, void *unused, __int32 a1);
void __fastcall c_gui_screen_pregame_selection__overlapped_task_update_hook(unsigned char *thisptr, void *unused);
bool __fastcall c_gui_map_selected_item__get_file_path_hook(void *thisptr, void *unused, char *buff, __int32 bufflen);
bool __fastcall c_gui_game_variant_selected_item__get_file_path_hook(void *thisptr, void *unused, char *buff, __int32 bufflen);
__int32 file_write_overlapped_task_execute_hook(unsigned char *task);
bool game_variant_description_override_hook(__int32 chud_handle, __int32 a2, __int32 stringid, __int32 *a4, __int32 length);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern bool saving_new_gametype; // 0x12458148
	extern bool enumerated; // 0x12458149
	extern s_ContentItemRenameState s_ContentItemRenameState; // 0x12458150
	extern "C" unsigned char *contentItemsGlobal; // 0x12458254
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace ContentItems
	{
		void ApplyAll() // 0x10A3ACF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@ContentItems@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x67DCA0, IsProfileAvailable).Apply();
			Patch(0x1A7A80, { 0x31, 0xC0, 0xC3 }).Apply();
			Patch(0x34D570, { 0x31, 0xC0, 0xC3 }).Apply();
			Hook(0x15B010, AllocateGameGlobalMemory2Hook).Apply();
			Hook(0x34CBE0, c_content_item__init_hook).Apply();
			Hook(0x34D010, PackageMountHook).Apply();
			Hook(0x1256D0, PackageMountHook2).Apply();
			Patch(0x12708E, { 0x8B, 0x4D, 0x14 }).Apply();
			Hook(0x127091, SaveFileGetNameHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x127096, 0x90, 3).Apply();
			Patch(0x6DC0EA, 0x90, 6).Apply();
			Patch(0x6DA59A, 0x90, 6).Apply();
			Pointer::Base(0x1A7E44).Write<unsigned int>(0x400);
			Hook(0x1A9050, CallsXEnumerateHook).Apply();
			Hook(0x34CE00, FS_GetFiloForContentItemHook).Apply();
			Hook(0x34CCF0, FS_GetFiloForContentItemHook).Apply();
			Hook(0x34CE70, FS_GetFilePathForContentItemHook).Apply();
			Hook(0x705388, c_gui_screen_pregame_selection__overlapped_task_update_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0x169E4E4).Write<unsigned int>(reinterpret_cast<unsigned int>(c_gui_game_variant_selected_item__get_file_path_hook));
			Pointer(0x169E244).Write<unsigned int>(reinterpret_cast<unsigned int>(c_gui_map_selected_item__get_file_path_hook));
			Pointer(0x526E50).Write<unsigned int>(reinterpret_cast<unsigned int>(content_item_overlapped_task_execute_hook));
			Hook(0x1A60E6, c_content_item_delete_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0x5AE016).Write<unsigned int>(reinterpret_cast<unsigned int>(file_write_overlapped_task_execute_hook));
			Hook(0x127617, malloc, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1276C5, free, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x127500, malloc, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1275E0, free, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1260CC, game_variant_description_override_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
		}
	}
}

/* ---------- private code */

bool AddContentItem(wchar_t *itemPath) // 0x10A3A620
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?AddContentItem@@YA_NPA_W@Z");
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
	// std::string path;
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

	unsigned char fileData[0xF8];
	FILE *file;
	if (_wfopen_s(&file, itemPath, L"rb") != 0 || !file)
		return false;
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	if (fileSize < 0x40)
	{
		fclose(file);
		return false;
	}
	unsigned __int32 magic;
	fread(&magic, 4, 1, file);
	if (magic != 0x5F626C66)
	{
		fclose(file);
		return false;
	}
	fseek(file, 0x40, SEEK_SET);
	fread(fileData, 1, 0xF8, file);
	fclose(file);
	__int32 (*const content_type_from_header)(__int32) = reinterpret_cast<__int32 (*)(__int32)>(0x525330);
	__int32 (*globalsArrayPush)(void *) = reinterpret_cast<__int32 (*)(void *)>(0x55B410);
	__int32 dataIdx = globalsArrayPush(contentItemsGlobal);
	unsigned char *dataBasePtr = *reinterpret_cast<unsigned char **>(contentItemsGlobal + 0x44);
	c_content_item *contentItem = reinterpret_cast<c_content_item *>(dataBasePtr + (unsigned short)dataIdx * 0x240);
	c_content_catalog *(*const content_catalog_get)(__int32) = reinterpret_cast<c_content_catalog *(*)(__int32)>(0x5A5600);
	c_content_catalog *contentCatalog = content_catalog_get(0);
	__int32 contentType = content_type_from_header(*reinterpret_cast<__int32 *>(fileData + 0xB8));
	contentItem->Unknown04 = 0x11;
	contentItem->ContentType = contentType;
	contentItem->Catalog = contentCatalog;
	memcpy(contentItem->ContentHeader, fileData, sizeof(contentItem->ContentHeader));
	std::string path = Utils::String::ThinString(itemPath);
	std::filesystem::path relativePath = std::filesystem::relative(path, std::filesystem::current_path());
	wcscpy_s(contentItem->RelativeFilePath, relativePath.c_str());
	return true;
}

bool AddContentItem(std::string itemPath) // 0x10A3AAF0
{
	// `anonymous-namespace'::AddContentItem
	// static ...; // 0x10A3ABE0
	// static ...; // 0x10A3ABD4
	// static ...; // 0x10A3ABCC
	// std::string itemPath;
	// std::wstring unicode;

	std::wstring unicode = Utils::String::WidenString(itemPath);
	return AddContentItem((wchar_t *)unicode.c_str());
}

void GetFilePathForItem(wchar_t *dest, unsigned __int32 MaxCount, wchar_t *variantName, __int32 variantType) // 0x10A3D300
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetFilePathForItem@@YAXPA_WI0H@Z");
	// `anonymous-namespace'::GetFilePathForItem
	// wchar_t *dest;
	// unsigned __int32 MaxCount;
	// wchar_t *variantName;
	// __int32 variantType;
	// wchar_t currentDir[128];
		// wchar_t *fileName;
		// wchar_t *(*FS_GetFileNameForItemType)(unsigned __int32);
	// function call : unsigned long (unsigned long, wchar_t *)
	// function call : wchar_t *(*)(unsigned __int32)

	wchar_t currentDir[128];
	memset(currentDir, 0, sizeof(currentDir));
	GetCurrentDirectoryW(128, currentDir);
	if (variantType == 10)
		swprintf_s(dest, MaxCount, L"%ls\\data\\map_variants\\%ls\\", currentDir, variantName);
	else
		swprintf_s(dest, MaxCount, L"%ls\\data\\game_variants\\%ls\\", currentDir, variantName);
	if (variantType == 10)
	{
		swprintf_s(dest, MaxCount, L"%ls\\data\\map_variants\\%ls\\sandbox.map", currentDir, variantName);
	}
	else
	{
		wchar_t *(*FS_GetFileNameForItemType)(unsigned __int32) = (wchar_t *(*)(unsigned __int32))0x526550;
		wchar_t *fileName = FS_GetFileNameForItemType(variantType);
		swprintf_s(dest, MaxCount, L"%ls\\data\\game_variants\\%ls\\%ls", currentDir, variantName, fileName);
	}
}

void AddAllBLFContentItems(std::string path) // 0x10A3A2F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?AddAllBLFContentItems@@YAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// `anonymous-namespace'::AddAllBLFContentItems
	// static ...; // 0x10A3A56C
	// static ...; // 0x10A3A560
	// static ...; // 0x10A3A558
	// std::string path;
	// dirent *entry;
	// DIR *dp;
		// std::string filePath;

	dirent *entry;
	DIR *dp;
	if ((dp = opendir(path.c_str())) == nullptr)
		return;
	while ((entry = readdir(dp)) != nullptr)
	{
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;
		std::string filePath = path + std::string("\\") + std::string(entry->d_name);
		if ((entry->d_type & S_IFMT) == S_IFDIR)
			AddAllBLFContentItems(filePath);
		else if ((entry->d_type & S_IFMT) == S_IFREG)
			AddContentItem(filePath);
	}
	closedir(dp);
}

char CallsXEnumerateHook() // 0x10A3C6B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CallsXEnumerateHook@@YADXZ");
	// `anonymous-namespace'::CallsXEnumerateHook
	// procedure flags: nofpo
	// static ...; // 0x10A3C979
	// static ...; // 0x10A3C96D
	// static ...; // 0x10A3C964
	// static ...; // 0x10A3C940
	// static ...; // 0x10A3C938
	// std::string mapsPath;
	// char currentDir[128];
	// std::string variantPath;
	// function call : unsigned long (unsigned long, char *)

	if (!contentItemsGlobal)
		return false;
	if (enumerated)
		return true;
	char currentDir[128];
	memset(currentDir, 0, sizeof(currentDir));
	GetCurrentDirectoryA(sizeof(currentDir), currentDir);
	std::string variantPath = std::string(currentDir) + std::string("\\data\\game_variants");
	std::string mapsPath = std::string(currentDir) + std::string("\\data\\map_variants");
	AddAllBLFContentItems(variantPath);
	AddAllBLFContentItems(mapsPath);
	enumerated = true;
	return true;
}

char __fastcall FS_GetFiloForContentItemHook(c_content_item *contentItem, void *unused, void *filo) // 0x10A3D0A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FS_GetFiloForContentItemHook@@YIDPAUc_content_item@hades_file_local@@PAX1@Z");
	// `anonymous-namespace'::FS_GetFiloForContentItemHook
	// static ...; // 0x10A3D1E8
	// static ...; // 0x10A3D1E0
	// c_content_item *contentItem;
	// void *unused;
	// void *filo;
	// std::filesystem::path path;
	// std::string relativePath;
	// void *(*fsCallsSetupFiloStruct2)(void *, wchar_t const *, char);
	// function call : void *(*)(void *, wchar_t const *, char)

	void *(*fsCallsSetupFiloStruct2)(void *, wchar_t const *, char) = reinterpret_cast<void *(*)(void *, wchar_t const *, char)>(0x5285B0);
	std::string relativePath = Utils::String::ThinString(contentItem->RelativeFilePath);
	std::filesystem::path path = std::filesystem::absolute(relativePath);
	fsCallsSetupFiloStruct2(filo, path.c_str(), false);
	return true;
}

wchar_t *__fastcall FS_GetFilePathForContentItemHook(c_content_item *contentItem, void *unused, wchar_t *dest, unsigned __int32 MaxCount) // 0x10A3CEF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FS_GetFilePathForContentItemHook@@YIPA_WPAUc_content_item@hades_file_local@@PAXPA_WI@Z");
	// `anonymous-namespace'::FS_GetFilePathForContentItemHook
	// static ...; // 0x10A3D018
	// c_content_item *contentItem;
	// void *unused;
	// wchar_t *dest;
	// unsigned __int32 MaxCount;
	// std::filesystem::path path;
	// std::string relativePath;

	std::string relativePath = Utils::String::ThinString(contentItem->RelativeFilePath);
	std::filesystem::path path = std::filesystem::absolute(relativePath);
	wcscpy_s(dest, MaxCount, path.c_str());
	return dest;
}

bool __fastcall ContainsForbiddenCharacters(wchar_t *namePtr) // 0x10A3CA40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ContainsForbiddenCharacters@@YI_NPA_W@Z");
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
	// std::wstring temp;
	// std::string current_directory;
	// std::string name;
	// std::string parent_directory;
		// std::initializer_list<char> &<range>$L0;
		// char const *<begin>$L0;
		// char const *<end>$L0;
			// char c;

	std::initializer_list<char> illegalChars = { '*' };
	std::wstring temp(namePtr);
	std::string name(temp.begin(), temp.end());
	for (char c : illegalChars)
	{
		if (name.find(c) != std::string::npos)
		{
			Web::Ui::ScreenLayer::ShowAlert("Error", "String contains one or more forbidden characters.", (Web::Ui::ScreenLayer::AlertIcon)0, 0.0f);
			return true;
		}
	}
	std::string current_directory = ".";
	std::string parent_directory = "..";
	if (name == current_directory || name == parent_directory)
	{
		Web::Ui::ScreenLayer::ShowAlert("Error", "A directory with this name cannot be created.", (Web::Ui::ScreenLayer::AlertIcon)0, 0.0f);
		return true;
	}
	return false;
}

bool __fastcall SaveFileGetNameHook(unsigned char *blfStart, void *unused, __int32 a2, wchar_t *Src, unsigned __int32 MaxCount) // 0x10A3D630
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SaveFileGetNameHook@@YI_NPAEPAXHPA_WI@Z");
	// `anonymous-namespace'::SaveFileGetNameHook
	// unsigned __int32 MaxCount;
	// __int32 variantType;
	// wchar_t *variantName;

	wchar_t *name = (wchar_t *)(blfStart + 0x48);
	unsigned __int32 uid = *(unsigned __int32 *)(blfStart + 0xF8);

	GetFilePathForItem(Src, MaxCount, name, uid);
	return true;
}

bool __fastcall c_content_item__init_hook(c_content_item *thisptr, void *unused, __int32 contentType, c_content_catalog *catalog, wchar_t *name, wchar_t *dashMetadata, __int32 a5, __int32 a6, __int32 a7) // 0x10A3E990
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_content_item__init_hook@@YI_NPAUc_content_item@hades_file_local@@PAXHPAUc_content_catalog@2@PA_W3HHH@Z");
	// `anonymous-namespace'::c_content_item__init_hook
	// c_content_catalog *catalog;
	// wchar_t *name;
	// wchar_t *dashMetadata;
	// __int32 a5;
	// __int32 a6;
	// __int32 a7;
	// __int32 (*const sub_5244C0)(__int32);
	// wchar_t buff[128];
	// std::string itemPath;
	// std::filesystem::path relativePath;
	// function call : __int32 (*const)(__int32)

	__int32 (*const sub_5244C0)(__int32) = reinterpret_cast<__int32 (*)(__int32)>(0x5244C0);
	if (ContainsForbiddenCharacters(name))
		return false;
	thisptr->Unknown04 = 17;
	thisptr->ContentType = contentType;
	thisptr->Catalog = catalog;
	if (contentType != 1)
		saving_new_gametype = true;
	wchar_t buff[128];
	GetFilePathForItem(buff, 128, name, sub_5244C0(contentType));
	std::string itemPath = Utils::String::ThinString(buff);
	std::filesystem::path relativePath = std::filesystem::relative(itemPath, std::filesystem::current_path());
	wcscpy_s(thisptr->RelativeFilePath, relativePath.c_str());
	return true;
}

char __stdcall PackageMountHook(__int32 a1, __int32 a2, __int32 a3, __int32 a4) // 0x10A3D610
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PackageMountHook@@YGDHHHH@Z");
	// `anonymous-namespace'::PackageMountHook
	// __int32 a4;

	return 1;
}

unsigned __int32 PackageMountHook2(__int32 localProfileIndex, wchar_t *name, __int32 contentType, long volatile *pStatus, long volatile *pState, long volatile *pContentItemDatumIndex) // 0x10A3D4F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PackageMountHook2@@YAIHPA_WHPCJ11@Z");
	// `anonymous-namespace'::PackageMountHook2
	// long volatile *pContentItemDatumIndex;
	// unsigned __int32 contentItemIndex;
	// __int32 (*const c_content_catalog__get_or_create_content_item)(c_content_catalog *, wchar_t const *, wchar_t const *, __int32, char, __int32, __int32);
	// c_content_catalog *(*const content_catalog_get)(__int32);
	// __int32 status;
	// __int32 (*const sub_525330)(__int32);
		// c_content_catalog *catalog;
	// function call : __int32 (*const)(__int32)
	// function call : c_content_catalog *(*const)(__int32)
	// function call : __int32 (*const)(c_content_catalog *, wchar_t const *, wchar_t const *, __int32, char, __int32, __int32)

	__int32 (*const sub_525330)(__int32) = reinterpret_cast<__int32 (*)(__int32)>(0x525330);
	c_content_catalog *(*const content_catalog_get)(__int32) = reinterpret_cast<c_content_catalog *(*)(__int32)>(0x5A5600);
	__int32 (__thiscall *const c_content_catalog__get_or_create_content_item)(c_content_catalog *, wchar_t const *, wchar_t const *, __int32, char, __int32, __int32) = reinterpret_cast<__int32 (__thiscall *)(c_content_catalog *, wchar_t const *, wchar_t const *, __int32, char, __int32, __int32)>(0x5A5E70);
	__int32 status = 0;
	unsigned __int32 contentItemIndex = -1;
	contentType = sub_525330(contentType);
	if (contentType != -1)
	{
		c_content_catalog *catalog = content_catalog_get(localProfileIndex);
		if (catalog)
		{
			contentItemIndex = c_content_catalog__get_or_create_content_item(catalog, name, L"", contentType, 0, 0, 0);
			if (contentItemIndex != -1)
				status = 1;
		}
	}
	InterlockedExchange(pState, 1);
	InterlockedExchange(pStatus, status);
	InterlockedExchange(pContentItemDatumIndex, contentItemIndex);
	return 0;
}

char *AllocateGameGlobalMemory2Hook(char *Src, __int32 a2, __int32 a3, char a4, void *a5) // 0x10A3AC30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?AllocateGameGlobalMemory2Hook@@YAPADPADHHDPAX@Z");
	// `anonymous-namespace'::AllocateGameGlobalMemory2Hook
	// void *a5;
	// char *(*allocateGlobal)(char *, __int32, __int32, char, void *);
	// char *retData;
	// function call : char *(*)(char *, __int32, __int32, char, void *)

	char *(__cdecl *AllocateGameGlobalMemory2)(char *, __int32, __int32, char, void *) = (char *(__cdecl *)(char *, __int32, __int32, char, void *))0x55afa0;
	char *retData = AllocateGameGlobalMemory2(Src, a2, a3, a4, a5);

	*(unsigned short *)(retData + 42) = 3;
	if (Src == (char *)0x165B170)
	{
		*(retData + 41) = 1;
		*(__int32 *)(retData + 64) = 1;
		contentItemsGlobal = (unsigned char *)retData;
	}
	return retData;
}

bool IsProfileAvailable() // 0x10A3D4D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?IsProfileAvailable@@YA_NXZ");
	// `anonymous-namespace'::IsProfileAvailable
	// procedure flags: nofpo

	return true;
}

wchar_t *GetDirectoryPathW(wchar_t *path, wchar_t *buff, __int32 bufflen) // 0x10A3D270
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetDirectoryPathW@@YAPA_WPA_W0H@Z");
	// `anonymous-namespace'::GetDirectoryPathW
	// __int32 bufflen;
	// wchar_t *filePart;

	wcscpy_s(buff, bufflen, path);
	wchar_t *filePart = wcsrchr(buff, L'\\');
	if (filePart != nullptr)
	{
		*filePart = 0;
		return buff;
	}
	return nullptr;
}

__int32 content_item_overlapped_task_execute_hook(c_content_item_overlapped_task *task) // 0x10A3F470
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?content_item_overlapped_task_execute_hook@@YAHPAUc_content_item_overlapped_task@hades_file_local@@@Z");
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
		// c_content_catalog *catalog;
			// c_content_item *item;
				// unsigned char filo[520];
				// wchar_t newFilePathBuffer[128];
				// std::filesystem::path relativePath;
				// std::filesystem::path newPath;
				// bool v2;
				// char *filePath;
					// __int32 n;
					// std::filesystem::path parent_path;
					// std::filesystem::path oldPath;
					// std::filesystem::path data_path;
	// function call : c_content_catalog *(*const)(__int32)
	// function call : unsigned __int32 (*const)(c_content_catalog *)
	// function call : bool (*const)(c_content_catalog *, unsigned __int32, void *)
	// function call : bool (*const)(c_content_item_overlapped_task *)
	// function call : bool (*const)(c_content_item_overlapped_task *)
	// function call : bool (*const)(c_content_item_overlapped_task *)

	bool (*const EditContentHeaderOverlappedTaskFunc)(c_content_item_overlapped_task *) = (bool (*)(c_content_item_overlapped_task *))0x526E90;
	c_content_catalog *(*const local_profile_get_content_catalog)(__int32) = (c_content_catalog *(*)(__int32))0x5A5600;
	unsigned __int32 (__thiscall *const c_content_catalog__get_availability)(c_content_catalog *) = (unsigned __int32 (__thiscall *)(c_content_catalog *))0x5A7A80;
	bool (__thiscall *const c_content_catalog__get_item_filo)(c_content_catalog *, unsigned __int32, void *) = (bool (__thiscall *)(c_content_catalog *, unsigned __int32, void *))0x5A6780;
	void (*const string_unicode_to_ascii)(wchar_t *, char *, __int32, void *) = (void (*)(wchar_t *, char *, __int32, void *))0x4EDEA0;
	hades_file_local::s_ContentItemRenameState.IsValid = false;
	if (task->NewContentName)
	{
		c_content_catalog *catalog = local_profile_get_content_catalog(task->LocalProfileIndex);
		if (c_content_catalog__get_availability(catalog) != 0xCACACACA)
		{
			c_content_item *item = catalog->Items->try_and_get(task->ContentItemDatumIndex);
			if (item)
			{
				unsigned char filo[520];
				c_content_catalog__get_item_filo(catalog, task->ContentItemDatumIndex, filo);
				char *filePath = (char *)(filo + 8);
				if (ContainsForbiddenCharacters(task->NewContentName))
				{
					*task->CompletionState = 1;
					*task->CompletionStatus = 1;
					task->NewContentName = (wchar_t *)(item->ContentHeader + 8);
					return EditContentHeaderOverlappedTaskFunc(task);
				}
				wchar_t newFilePathBuffer[128];
				GetFilePathForItem(newFilePathBuffer, 128, task->NewContentName, *(__int32 *)(item->ContentHeader + 0xB8));
				std::filesystem::path newPath(newFilePathBuffer);
				if (!std::filesystem::create_directories(newPath.parent_path()))
				{
					__int32 n = 5;
				}
				bool v2 = EditContentHeaderOverlappedTaskFunc(task);
				std::filesystem::path relativePath = std::filesystem::relative(newPath, std::filesystem::current_path());
				if (*task->CompletionStatus == 1)
				{
					wcscpy_s(item->RelativeFilePath, newPath.c_str());
					wcscpy_s(hades_file_local::s_ContentItemRenameState.NewPath, relativePath.c_str());
					hades_file_local::s_ContentItemRenameState.IsValid = true;
					std::filesystem::path oldPath(filePath);
					std::filesystem::path parent_path = oldPath.parent_path();
					std::filesystem::rename(oldPath, newPath);
					std::filesystem::path data_path = std::filesystem::absolute("data");
					if (std::filesystem::is_empty(parent_path) && parent_path.parent_path() != data_path)
						std::filesystem::remove(parent_path);
				}
				return v2;
			}
		}
	}
	return EditContentHeaderOverlappedTaskFunc(task);
}

void __fastcall c_content_item_delete_hook(c_content_item *thisptr, void *unused, __int32 a1) // 0x10A3EC60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_content_item_delete_hook@@YIXPAUc_content_item@hades_file_local@@PAXH@Z");
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

	std::filesystem::path path = std::filesystem::absolute(thisptr->RelativeFilePath);
	std::filesystem::path parent_path = path.parent_path();
	std::filesystem::remove(path);
	std::filesystem::path data_path = std::filesystem::absolute("data");
	if (std::filesystem::is_empty(parent_path) && parent_path.parent_path() != data_path)
		std::filesystem::remove_all(parent_path);
}

void __fastcall c_gui_screen_pregame_selection__overlapped_task_update_hook(unsigned char *thisptr, void *unused) // 0x10A3F010
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_screen_pregame_selection__overlapped_task_update_hook@@YIXPAEPAX@Z");
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
		// void *subitem;
			// __int32 selectedIndex;
			// void *datasource;
				// void *item;
				// void *(*const c_ordered_datasource__get_item_at)(void *, __int32);
					// std::filesystem::path bs;
	// function call : void *(*const)(void *, unsigned __int32)
	// function call : void *(*const)(void *)
	// function call : __int32 (*const)(void *)
	// function call : void *(*const)(void *, __int32)
	// function call : __int32 (*const)(void *, char *)
	// function call : void (*const)(unsigned char *)

	void (__thiscall *const c_gui_screen_pregame_selection__overlapped_task_update)(unsigned char *) = reinterpret_cast<void (__thiscall *)(unsigned char *)>(0xB053D0);
	void *(__thiscall *const c_gui_widget__find_named_child)(void *, unsigned __int32) = reinterpret_cast<void *(__thiscall *)(void *, unsigned __int32)>(0xAB8AA0);
	void *(__thiscall *const c_gui_list_widget__get_ordered_data_source)(void *) = reinterpret_cast<void *(__thiscall *)(void *)>(0xB14FE0);
	__int32 (__thiscall *const c_gui_list_widget__get_selected_item_index)(void *) = reinterpret_cast<__int32 (__thiscall *)(void *)>(0xB150E0);
	__int32 (*const c_filo__set_path)(void *, char *) = reinterpret_cast<__int32 (*)(void *, char *)>(0x528880);
	__int32 (__thiscall *const c_gui_screen_widget__get_local_profile_index)(void *) = reinterpret_cast<__int32 (__thiscall *)(void *)>(0xAB96C0);
	if (*(long *)(thisptr + 0x1AB0) == -1 && *(long *)(thisptr + 0x1AB4) != -1 && *(long *)(thisptr + 0x1AC0) == 1 && hades_file_local::s_ContentItemRenameState.IsValid)
	{
		hades_file_local::s_ContentItemRenameState.IsValid = false;
		void *subitem = c_gui_widget__find_named_child(thisptr, 0x102E6);
		if (subitem)
		{
			void *datasource = c_gui_list_widget__get_ordered_data_source(subitem);
			__int32 selectedIndex = c_gui_list_widget__get_selected_item_index(subitem);
			if (selectedIndex != -1)
			{
				void *(__thiscall *const c_ordered_datasource__get_item_at)(void *, __int32) = *(*reinterpret_cast<void *(__thiscall ***)(void *, __int32)>(datasource) + 17);
				void *item = c_ordered_datasource__get_item_at(datasource, selectedIndex);
				if (item)
				{
					std::filesystem::path bs = std::filesystem::absolute(Utils::String::ThinString(hades_file_local::s_ContentItemRenameState.NewPath));
					c_filo__set_path((char *)item + 404, (char *)bs.c_str());
				}
			}
		}
	}
	c_gui_screen_pregame_selection__overlapped_task_update(thisptr);
}

bool __fastcall c_gui_map_selected_item__get_file_path_hook(void *thisptr, void *unused, char *buff, __int32 bufflen) // 0x10A3EFA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_map_selected_item__get_file_path_hook@@YI_NPAX0PADH@Z");
	// `anonymous-namespace'::c_gui_map_selected_item__get_file_path_hook
	// __int32 bufflen;

	strcpy_s(buff, bufflen, (char *)thisptr + 412);
	return true;
}

bool __fastcall c_gui_game_variant_selected_item__get_file_path_hook(void *thisptr, void *unused, char *buff, __int32 bufflen) // 0x10A3EF30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_game_variant_selected_item__get_file_path_hook@@YI_NPAX0PADH@Z");
	// `anonymous-namespace'::c_gui_game_variant_selected_item__get_file_path_hook
	// __int32 bufflen;

	strcpy_s(buff, bufflen, (char *)thisptr + 416);
	return true;
}

__int32 file_write_overlapped_task_execute_hook(unsigned char *task) // 0x10A3FE10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?file_write_overlapped_task_execute_hook@@YAHPAE@Z");
	// `anonymous-namespace'::file_write_overlapped_task_execute_hook
	// static ...; // 0x10A3FED0
	// static ...; // 0x10A3FEC4
	// static ...; // 0x10A3FEBC
	// unsigned char *task;
	// wchar_t directoryPath[128];
	// __int32 (*const file_write_overlapped_task_execute)(unsigned char *);
	// function call : __int32 (HWND__ *, wchar_t const *, _SECURITY_ATTRIBUTES const *)
	// function call : __int32 (*const)(unsigned char *)

	__int32 (__cdecl *const file_write_overlapped_task_execute)(unsigned char *) = (__int32 (__cdecl *)(unsigned char *))0x5AF410;
	wchar_t directoryPath[128];

	if (GetDirectoryPathW((wchar_t *)task, directoryPath, 128))
		SHCreateDirectoryExW(nullptr, directoryPath, nullptr);

	return file_write_overlapped_task_execute(task);
}

bool game_variant_description_override_hook(__int32 chud_handle, __int32 a2, __int32 stringid, __int32 *a4, __int32 length) // 0x10A3FF20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_variant_description_override_hook@@YA_NHHHPAHH@Z");
	// `anonymous-namespace'::game_variant_description_override_hook
	// __int32 length;
	// bool (*const sub_AA59B0)(__int32, __int32, __int32, void *, __int32);
	// function call : bool (*const)(__int32, __int32, __int32, void *, __int32)

	bool (__cdecl *const chud_get_string)(__int32, __int32, __int32, __int32 *, __int32) = (bool(__cdecl *const)(__int32, __int32, __int32, __int32 *, __int32))0xaa59b0;

	if (saving_new_gametype)
	{
		saving_new_gametype = false;
		return chud_get_string(chud_handle, a2, stringid, a4, length);
	}
	else
	{
		return false;
	}
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { bool saving_new_gametype; }
namespace hades_file_local { bool enumerated; }
namespace hades_file_local { struct s_ContentItemRenameState s_ContentItemRenameState; }

namespace hades_file_local { extern "C" { unsigned char *contentItemsGlobal; } }
