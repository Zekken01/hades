#ifndef __MODS_FILESYSTEM_MODPACKAGEFILESYSTEMVIEWMANAGER_HPP__
#define __MODS_FILESYSTEM_MODPACKAGEFILESYSTEMVIEWMANAGER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <utility>

/* ---------- forward declarations */

class CModPackageFileSystemView;
class CModPackageFileSystemViewManager;

/* ---------- constants */

/* ---------- definitions */

class CModPackageFileSystemViewManager :
	public Utils::Singleton<CModPackageFileSystemViewManager>
{
public:
	std::shared_ptr<CModPackageFileSystemView> GetView(std::string const &identifier);
	bool ViewExists(std::string const &identifier);
	void Flush();
private:
	std::mutex m_mutex; // 0x0
	std::unordered_map<std::string,std::shared_ptr<CModPackageFileSystemView> > m_views; // 0x30
public:
	_inline CModPackageFileSystemViewManager(); /* compiler_generated() */
	~CModPackageFileSystemViewManager(); /* compiler_generated() */
};
static_assert(sizeof(CModPackageFileSystemViewManager) == 88, "Invalid CModPackageFileSystemViewManager size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODS_FILESYSTEM_MODPACKAGEFILESYSTEMVIEWMANAGER_HPP__
