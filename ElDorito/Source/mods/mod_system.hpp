#ifndef __MODS_MOD_SYSTEM_HPP__
#define __MODS_MOD_SYSTEM_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

/* ---------- forward declarations */

class CModPackageFileSystemView;
class IModManager;
class c_mod_package_manager;
struct c_mod_system;
struct s_mod_server_package_entry;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_mod_server_package_entry
{
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > package_url; // 0x0
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > local_name; // 0x1C
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > hash; // 0x38
	_inline s_mod_server_package_entry(s_mod_server_package_entry &&__that); /* compiler_generated() */
	_inline s_mod_server_package_entry(s_mod_server_package_entry const &__that); /* compiler_generated() */
	_inline s_mod_server_package_entry(); /* compiler_generated() */
	_inline ~s_mod_server_package_entry(); /* compiler_generated() */
	s_mod_server_package_entry &operator=(s_mod_server_package_entry &); /* compiler_generated() */
	_inline s_mod_server_package_entry &operator=(s_mod_server_package_entry const &__that); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_mod_server_package_entry) == 84, "Invalid s_mod_server_package_entry size");

struct c_mod_system
{
	static IModManager &GetModManager();
	static void initialize(bool is_dedicated_server);
	static void update();
	static c_mod_package_manager &get_package_manager();
	static char const *get_package_directory();
	static std::basic_string<char,std::char_traits<char>,std::allocator<char> > get_current_package_hash();
	static std::basic_string<char,std::char_traits<char>,std::allocator<char> > get_current_mainmenu_package_hash();
	static std::basic_string<char,std::char_traits<char>,std::allocator<char> > get_current_package_filename(EModIndex package_type);
	static std::basic_string<char,std::char_traits<char>,std::allocator<char> > get_mod_hash_by_identifier(char const *identifier);
	static bool get_mod_info_by_hash(char const *hash_str, c_mod_package_manager::s_entry *package_entry);
	static bool get_mod_info_by_identifier(char const *identifier, c_mod_package_manager::s_entry *package_entry);
	static bool unload_current_package();
	static bool load_package_by_identifier(char const *identifier);
	static bool find_server_package_by_hash(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &hash, s_mod_server_package_entry *entry);
	static bool find_server_package_by_name(char const *name, s_mod_server_package_entry *entry);
	static bool has_server_package_list();
	static std::unordered_map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,CModPackageFileSystemView::SFileEntry,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,CModPackageFileSystemView::SFileEntry> > > get_package_file_list(std::basic_string<char,std::char_traits<char>,std::allocator<char> > hash);
	static std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetNewPackageFilename(std::basic_string<char,std::char_traits<char>,std::allocator<char> > name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > hash, std::basic_string<char,std::char_traits<char>,std::allocator<char> > version);
};
static_assert(sizeof(c_mod_system) == 1, "Invalid c_mod_system size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODS_MOD_SYSTEM_HPP__
