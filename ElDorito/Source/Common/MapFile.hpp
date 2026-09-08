#ifndef __COMMON_MAPFILE_HPP__
#define __COMMON_MAPFILE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/saved_games/blf.hpp"
#include "Forge/ForgeUtil.hpp"
#include "mods/map_variant_loader.hpp"

#include <fstream>
#include <memory>
#include <string>

/* ---------- forward declarations */

class CMapFile;
struct s_blf_map_information;
struct s_cache_file_header;
struct s_map_variant;

/* ---------- constants */

/* ---------- definitions */

class CMapFile
{
public:
	CMapFile(CMapFile &); /* compiler_generated() */
	CMapFile(CMapFile const &); /* compiler_generated() */
	CMapFile(void const *data, unsigned __int32 size);
	CMapFile(std::string const &filePath);
	bool IsValid() const;
	bool HasMapInfo() const;
	bool HasMapVariant() const;
	__int32 GetMapId() const;
	std::string const GetScenarioPath() const;
	std::string const GetScenarioName() const;
	std::wstring const GetDisplayName(__int32 language) const;
	std::wstring const GetDescription(__int32 language) const;
	s_map_variant const *GetMapVariant() const;
private:
	void LoadFromFile(std::basic_ifstream<char,std::char_traits<char> > &stream);
	void LoadFromBuffer(unsigned char const *data, unsigned __int32 size);
	unsigned char const *m_data; // 0x0
	unsigned __int32 m_dataSize; // 0x4
	s_blf_map_information const *m_mapInfo; // 0x8
	s_cache_file_header const *m_cacheFileHeader; // 0xC
	s_map_variant const *m_mapVariant; // 0x10
	std::string m_buffer; // 0x14
public:
	_inline ~CMapFile(); /* compiler_generated() */
	CMapFile &operator=(CMapFile &); /* compiler_generated() */
	CMapFile &operator=(CMapFile const &); /* compiler_generated() */
};
static_assert(sizeof(CMapFile) == 48, "Invalid CMapFile size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __COMMON_MAPFILE_HPP__
