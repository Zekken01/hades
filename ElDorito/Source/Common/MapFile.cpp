/* ---------- headers */

#include "Common/MapFile.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/saved_games/blf.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Forge/ForgeUtil.hpp"
#include "mods/blf_reader.hpp"
#include "mods/map_variant_loader.hpp"

#include <Windows.h>
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
#include <fstream>
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

class CMapFile;
struct s_blf_chunk_header;
struct s_map_variant;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern CMapFile* _sub_1085FEF0(CMapFile *const, std::string const &);
CMapFile::CMapFile(std::string const &filePath) // 0x1085FEF0
{
	mangled_x86(MANGLED_TODO, "??0CMapFile@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// static ...; // 0x10860014
	// static ...; // 0x1086000C
	// CMapFile *const this;
	// std::string const &filePath;
	// std::ifstream stream;
	todo("implement");
	_sub_1085FEF0(this, filePath);
}

extern CMapFile* _sub_10860080(CMapFile *const, void const *, unsigned __int32);
CMapFile::CMapFile(void const *data, unsigned __int32 size) // 0x10860080
{
	mangled_x86(MANGLED_TODO, "??0CMapFile@@QAE@PBXI@Z");
	// unsigned __int32 size;
	todo("implement");
	_sub_10860080(this, data, size);
}

_extern bool _sub_10860890(CMapFile const *const);
bool CMapFile::IsValid() const // 0x10860890
{
	mangled_x86(MANGLED_TODO, "?IsValid@CMapFile@@QBE_NXZ");
	// CMapFile const *const this;
	todo("implement");
	bool __result = _sub_10860890((CMapFile const *)this);
	return __result;
}

_extern bool _sub_108607F0(CMapFile const *const);
bool CMapFile::HasMapInfo() const // 0x108607F0
{
	mangled_x86(MANGLED_TODO, "?HasMapInfo@CMapFile@@QBE_NXZ");
	// CMapFile const *const this;
	todo("implement");
	bool __result = _sub_108607F0((CMapFile const *)this);
	return __result;
}

_extern bool _sub_10860840(CMapFile const *const);
bool CMapFile::HasMapVariant() const // 0x10860840
{
	mangled_x86(MANGLED_TODO, "?HasMapVariant@CMapFile@@QBE_NXZ");
	// CMapFile const *const this;
	todo("implement");
	bool __result = _sub_10860840((CMapFile const *)this);
	return __result;
}

extern s_map_variant const *_sub_10860460(CMapFile const *const);
s_map_variant const *CMapFile::GetMapVariant() const // 0x10860460
{
	mangled_x86(MANGLED_TODO, "?GetMapVariant@CMapFile@@QBEPBUs_map_variant@@XZ");
	// CMapFile const *const this;
	todo("implement");
	s_map_variant const * __result = _sub_10860460((CMapFile const *)this);
	return __result;
}

extern std::string const _sub_10860690(CMapFile const *const);
std::string const CMapFile::GetScenarioPath() const // 0x10860690
{
	mangled_x86(MANGLED_TODO, "?GetScenarioPath@CMapFile@@QBE?BV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// CMapFile const *const this;
	todo("implement");
	std::string const __result = _sub_10860690((CMapFile const *)this);
	return __result;
}

extern std::string const _sub_108604E0(CMapFile const *const);
std::string const CMapFile::GetScenarioName() const // 0x108604E0
{
	mangled_x86(MANGLED_TODO, "?GetScenarioName@CMapFile@@QBE?BV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// CMapFile const *const this;
	todo("implement");
	std::string const __result = _sub_108604E0((CMapFile const *)this);
	return __result;
}

extern std::wstring const _sub_108602A0(CMapFile const *const, __int32);
std::wstring const CMapFile::GetDisplayName(__int32 language) const // 0x108602A0
{
	mangled_x86(MANGLED_TODO, "?GetDisplayName@CMapFile@@QBE?BV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@H@Z");
	// __int32 language;
	todo("implement");
	std::wstring const __result = _sub_108602A0((CMapFile const *)this, language);
	return __result;
}

extern std::wstring const _sub_10860170(CMapFile const *const, __int32);
std::wstring const CMapFile::GetDescription(__int32 language) const // 0x10860170
{
	mangled_x86(MANGLED_TODO, "?GetDescription@CMapFile@@QBE?BV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@H@Z");
	// __int32 language;
	todo("implement");
	std::wstring const __result = _sub_10860170((CMapFile const *)this, language);
	return __result;
}

_extern __int32 _sub_108603D0(CMapFile const *const);
__int32 CMapFile::GetMapId() const // 0x108603D0
{
	mangled_x86(MANGLED_TODO, "?GetMapId@CMapFile@@QBEHXZ");
	// CMapFile const *const this;
	todo("implement");
	__int32 __result = _sub_108603D0((CMapFile const *)this);
	return __result;
}

_extern void _sub_10860B10(CMapFile *const, std::ifstream &);
void CMapFile::LoadFromFile(std::ifstream &stream) // 0x10860B10
{
	mangled_x86(MANGLED_TODO, "?LoadFromFile@CMapFile@@AAEXAAV?$basic_ifstream@DU?$char_traits@D@std@@@std@@@Z");
	// std::ifstream &stream;
	todo("implement");
	_sub_10860B10(this, stream);
}

_extern void _sub_10860910(CMapFile *const, unsigned char const *, unsigned __int32);
void CMapFile::LoadFromBuffer(unsigned char const *data, unsigned __int32 size) // 0x10860910
{
	mangled_x86(MANGLED_TODO, "?LoadFromBuffer@CMapFile@@AAEXPBEI@Z");
	// static ...; // 0x10860A78
	// static ...; // 0x10860A54
	// static ...; // 0x10860A4C
	// CMapFile *const this;
	// unsigned char const *data;
	// unsigned __int32 size;
	// unsigned char const *dataEnd;
	// unsigned char const *blfData;
	// unsigned char const *blfChunkData;
	// unsigned long blfChunkSize;
	// s_blf_chunk_header blfChunkHeader;
	// bool chunkFound;
	todo("implement");
	_sub_10860910(this, data, size);
}

/* ---------- private code */
