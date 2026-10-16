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

#include "Blam/cseries/language.hpp"  // hades: added for 0x108602A0, 0x10860170  // hades: added for 0x108602A0

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

CMapFile::CMapFile(std::string const &filePath) : m_data(nullptr), m_dataSize(0), m_mapInfo(nullptr), m_cacheFileHeader(nullptr), m_mapVariant(nullptr) /* hades-mem-init:  */ // 0x1085FEF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0CMapFile@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

	std::ifstream stream(filePath, std::ios::binary);
	if (!stream.is_open())
		return;
	LoadFromFile(stream);
}

CMapFile::CMapFile(void const *data, unsigned __int32 size) : m_data(nullptr), m_dataSize(0), m_mapInfo(nullptr), m_cacheFileHeader(nullptr), m_mapVariant(nullptr) /* hades-mem-init:  */ // 0x10860080
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0CMapFile@@QAE@PBXI@Z");

	LoadFromBuffer((unsigned char const *)data, size);
}

bool CMapFile::IsValid() const // 0x10860890
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?IsValid@CMapFile@@QBE_NXZ");

	return m_buffer.size() > 0;
}

bool CMapFile::HasMapInfo() const // 0x108607F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HasMapInfo@CMapFile@@QBE_NXZ");

	return m_mapInfo != nullptr;
}

bool CMapFile::HasMapVariant() const // 0x10860840
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HasMapVariant@CMapFile@@QBE_NXZ");

	return m_mapVariant != nullptr;
}

#line 125
s_map_variant const *CMapFile::GetMapVariant() const // 0x10860460
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetMapVariant@CMapFile@@QBEPBUs_map_variant@@XZ");
#line 129

	#line 127 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Common\\MapFile.cpp"
		assert(HasMapVariant());
		#line 133 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Common\\MapFile.cpp"
	return m_mapVariant;
}

std::string const CMapFile::GetScenarioPath() const // 0x10860690
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetScenarioPath@CMapFile@@QBE?BV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
#line 140

	#line 138 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Common\\MapFile.cpp"
		assert(IsValid());
		#line 144 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Common\\MapFile.cpp"
	return std::filesystem::path(m_cacheFileHeader->scenario_path).string();
}

std::string const CMapFile::GetScenarioName() const // 0x108604E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetScenarioName@CMapFile@@QBE?BV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
#line 151

	#line 149 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Common\\MapFile.cpp"
		assert(IsValid());
		#line 155 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Common\\MapFile.cpp"
	return std::filesystem::path(m_cacheFileHeader->scenario_path).filename().string();
}

std::wstring const CMapFile::GetDisplayName(__int32 language) const // 0x108602A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetDisplayName@CMapFile@@QBE?BV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@H@Z");
#line 162

	#line 160 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Common\\MapFile.cpp"
		assert(IsValid());
		#line 166 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Common\\MapFile.cpp"
	#line 161 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Common\\MapFile.cpp"
		assert(language >= 0 && language < k_number_of_languages);
		#line 169 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Common\\MapFile.cpp"
	if (!HasMapInfo())
		return L"";
	return m_mapInfo->map_names[language];
}

std::wstring const CMapFile::GetDescription(__int32 language) const // 0x10860170
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetDescription@CMapFile@@QBE?BV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@H@Z");
#line 178

	#line 176 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Common\\MapFile.cpp"
		assert(IsValid());
		#line 182 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Common\\MapFile.cpp"
	#line 177 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Common\\MapFile.cpp"
		assert(language >= 0 && language < k_number_of_languages);
		#line 185 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Common\\MapFile.cpp"
	if (!HasMapInfo())
		return L"";
	return m_mapInfo->map_descriptions[language];
}

__int32 CMapFile::GetMapId() const // 0x108603D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetMapId@CMapFile@@QBEHXZ");
#line 194

	#line 192 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Common\\MapFile.cpp"
		assert(IsValid());
		#line 198 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Common\\MapFile.cpp"
	return m_cacheFileHeader->map_id;
}

void CMapFile::LoadFromFile(std::ifstream &stream) // 0x10860B10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LoadFromFile@CMapFile@@AAEXAAV?$basic_ifstream@DU?$char_traits@D@std@@@std@@@Z");

	stream.seekg(0, std::ios::end);
	m_buffer.resize(stream.tellg());
	stream.seekg(0, std::ios::beg);
	stream.read(m_buffer.data(), m_buffer.size());
	if (stream.bad())
		return;
	m_data = (unsigned char const *)m_buffer.data();
	m_dataSize = m_buffer.size();
	LoadFromBuffer(m_data, m_dataSize);
}

void CMapFile::LoadFromBuffer(unsigned char const *data, unsigned __int32 size) // 0x10860910
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LoadFromBuffer@CMapFile@@AAEXPBEI@Z");

	if (size < 0x3390)
		return;
	m_cacheFileHeader = (s_cache_file_header const *)&m_data[0];
	if (size == 0x3390)
		return;

	unsigned char const *dataEnd = m_data + size;
	unsigned char const *blfData = &m_data[0x3390];
	s_blf_chunk_header blfChunkHeader;
	unsigned char const *blfChunkData;
	unsigned long blfChunkSize;
	bool chunkFound = blf_find_chunk_in_buffer(blfData, std::distance(blfData, dataEnd), 0x6C65766C, &blfChunkHeader, &blfChunkData, &blfChunkSize);
	if (chunkFound)
		m_mapInfo = (s_blf_map_information const *)&blfChunkData[-12];
	chunkFound = blf_find_chunk_in_buffer(blfData, std::distance(blfData, dataEnd), 0x6D617076, &blfChunkHeader, &blfChunkData, &blfChunkSize);
	if (chunkFound)
		m_mapVariant = (s_map_variant const *)&blfChunkData[4];
}

/* ---------- private code */
