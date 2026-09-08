#ifndef __MODS_FILESYSTEM_MODPACKAGEFILESYSTEMVIEW_HPP__
#define __MODS_FILESYSTEM_MODPACKAGEFILESYSTEMVIEW_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/Magnets.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <functional>
#include <istream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

/* ---------- forward declarations */

class CModPackageFileSystemView;

/* ---------- constants */

/* ---------- definitions */

class CModPackageFileSystemView
{
public:
	public:
	struct SFileEntry
	{
		unsigned __int32 size; // 0x0
		unsigned __int32 offset; // 0x4
	};
	static_assert(sizeof(SFileEntry) == 8, "Invalid SFileEntry size");
	public:
	CModPackageFileSystemView(CModPackageFileSystemView &); /* compiler_generated() */
	CModPackageFileSystemView(CModPackageFileSystemView const &); /* compiler_generated() */
	CModPackageFileSystemView(std::string const &filePath);
	bool GetFileEntry(std::string const &virtualPath, SFileEntry *outEntry);
	std::unordered_map<std::string,SFileEntry> GetFileList();
	_inline std::string const &GetFilePath() const;
	_inline long long GetBaseOffset() const;
private:
	void Initialize();
	bool ReadFileTable(std::istream &stream);
	long long m_baseOffset; // 0x0
	std::string m_filePath; // 0x8
	std::unordered_map<std::string,SFileEntry> m_files; // 0x24
public:
	_inline ~CModPackageFileSystemView(); /* compiler_generated() */
	CModPackageFileSystemView &operator=(CModPackageFileSystemView &); /* compiler_generated() */
	CModPackageFileSystemView &operator=(CModPackageFileSystemView const &); /* compiler_generated() */
unsigned char __pad0[4]; // 0x4C
};
static_assert(sizeof(CModPackageFileSystemView) == 80, "Invalid CModPackageFileSystemView size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

extern std::string const &_sub_10784D00(CModPackageFileSystemView const *const);
_inline std::string const &CModPackageFileSystemView::GetFilePath() const // 0x10784D00
{
	mangled_x86(MANGLED_TODO, "?GetFilePath@CModPackageFileSystemView@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// CModPackageFileSystemView const *const this;
	todo("implement");
	std::string const & __result = _sub_10784D00((CModPackageFileSystemView const *)this);
	return __result;
}

_extern long long _sub_10784CD0(CModPackageFileSystemView const *const);
_inline long long CModPackageFileSystemView::GetBaseOffset() const // 0x10784CD0
{
	mangled_x86(MANGLED_TODO, "?GetBaseOffset@CModPackageFileSystemView@@QBE_JXZ");
	// CModPackageFileSystemView const *const this;
	todo("implement");
	long long __result = _sub_10784CD0((CModPackageFileSystemView const *)this);
	return __result;
}

/* ---------- private code */

#endif // __MODS_FILESYSTEM_MODPACKAGEFILESYSTEMVIEW_HPP__
