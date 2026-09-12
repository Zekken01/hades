#ifndef __MODS_MAP_LOAD_ERROR_HELPER_HPP__
#define __MODS_MAP_LOAD_ERROR_HELPER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/tag_files/file_reference.inl"

#include <memory>
#include <string>

/* ---------- forward declarations */

class c_file_reference;
struct c_map_load_error_helper;
struct s_cache_tag_instance;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct c_map_load_error_helper
{
	_inline void invalid_tag_index();
	_inline void failed_to_find_mod_tag_in_base(c_file_reference const *mod_file, s_cache_tag_instance const *tag_header, char const *tag_name);
	_inline void failed_to_find_tag(c_file_reference const *cache_file, long cache_tag_index);
	_inline void missing_tag_name(c_file_reference const *cache_file, long cache_tag_index);
	_inline void invalid_tag_size(c_file_reference const *cache_file, char const *tag_name);
	_inline void failed_to_allocate_memory_for_tag(c_file_reference const *cache_file, char const *tag_name);
	_inline void failed_to_read_tag_data(c_file_reference const *cache_file, char const *tag_name);
	_inline void failed_to_allocate_tag_resource_memory();
	_inline void failed_to_initialize_font_cache();
	_inline void failed_to_open_mod_package_map_file(char const *mod_file, char const *map_path);
	_inline std::string const &get_last_error() const;
	_inline void set_last_error(std::string const &message);
	_inline void reset();
private:
	_inline char const *tag_filename(char *buff, unsigned long group, char const *name);
	std::string m_last_error; // 0x0
public:
	c_map_load_error_helper(c_map_load_error_helper &); /* compiler_generated() */
	c_map_load_error_helper(c_map_load_error_helper const &); /* compiler_generated() */
	_inline c_map_load_error_helper(); /* compiler_generated() */
	_inline ~c_map_load_error_helper(); /* compiler_generated() */
	c_map_load_error_helper &operator=(c_map_load_error_helper &); /* compiler_generated() */
	c_map_load_error_helper &operator=(c_map_load_error_helper const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(c_map_load_error_helper) == 28, "Invalid c_map_load_error_helper size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline void c_map_load_error_helper::invalid_tag_index() // 0x10927C10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?invalid_tag_index@c_map_load_error_helper@@QAEXXZ");
	// c_map_load_error_helper *const this;

	set_last_error(std::format("Tried to load tag dependency with an invalid tag index"));
}

_extern void _sub_109272A0(c_map_load_error_helper *const, c_file_reference const *, s_cache_tag_instance const *, char const *);
_inline void c_map_load_error_helper::failed_to_find_mod_tag_in_base(c_file_reference const *mod_file, s_cache_tag_instance const *tag_header, char const *tag_name) // 0x109272A0
{
	mangled_x86(MANGLED_TODO, "?failed_to_find_mod_tag_in_base@c_map_load_error_helper@@QAEXPBVc_file_reference@@PBUs_cache_tag_instance@@PBD@Z");
	// c_map_load_error_helper *const this;
	// c_file_reference const *mod_file;
	// s_cache_tag_instance const *tag_header;
	// char const *tag_name;
	// char tag_filename_buff[256];
	todo("implement");
	_sub_109272A0(this, mod_file, tag_header, tag_name);
}

_inline void c_map_load_error_helper::failed_to_find_tag(c_file_reference const *cache_file, long cache_tag_index) // 0x10927440
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?failed_to_find_tag@c_map_load_error_helper@@QAEXPBVc_file_reference@@J@Z");
	// long cache_tag_index;

	set_last_error(std::format("Failed to find tag in cache.\n\nCache: {}\nTagIndex: 0x{:04X}", cache_file->filename, cache_tag_index));
}

_inline void c_map_load_error_helper::missing_tag_name(c_file_reference const *cache_file, long cache_tag_index) // 0x10928F70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?missing_tag_name@c_map_load_error_helper@@QAEXPBVc_file_reference@@J@Z");
	// long cache_tag_index;

	set_last_error(std::format("Tried to load unnamed tag. Tags must be named!\n\nCache: {}\nTagIndex: 0x{:04X}", cache_file->filename, cache_tag_index));
}

_inline void c_map_load_error_helper::invalid_tag_size(c_file_reference const *cache_file, char const *tag_name) // 0x10927D20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?invalid_tag_size@c_map_load_error_helper@@QAEXPBVc_file_reference@@PBD@Z");
	// char const *tag_name;

	set_last_error(std::format("Tag had an invalid size.\n\nCache: {}\nTag: {}", cache_file->filename, tag_name));
}

_inline void c_map_load_error_helper::failed_to_allocate_memory_for_tag(c_file_reference const *cache_file, char const *tag_name) // 0x10927070
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?failed_to_allocate_memory_for_tag@c_map_load_error_helper@@QAEXPBVc_file_reference@@PBD@Z");
	// char const *tag_name;

	set_last_error(std::format("Failed to allocate memory for tag.\n\nCache: {}\nTag: {}", cache_file->filename, tag_name));
}

_inline void c_map_load_error_helper::failed_to_read_tag_data(c_file_reference const *cache_file, char const *tag_name) // 0x10927790
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?failed_to_read_tag_data@c_map_load_error_helper@@QAEXPBVc_file_reference@@PBD@Z");
	// char const *tag_name;

	set_last_error(std::format("Failed to allocate memory for tag.\n\nCache: {}\nTag: {}", cache_file->filename, tag_name));
}

_inline void c_map_load_error_helper::failed_to_allocate_tag_resource_memory() // 0x10927190
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?failed_to_allocate_tag_resource_memory@c_map_load_error_helper@@QAEXXZ");
	// c_map_load_error_helper *const this;

	set_last_error(std::format("Failed to allocate memory for tag resources"));
}

_inline void c_map_load_error_helper::failed_to_initialize_font_cache() // 0x10927560
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?failed_to_initialize_font_cache@c_map_load_error_helper@@QAEXXZ");
	// c_map_load_error_helper *const this;

	set_last_error(std::format("Failed to initialize font cache"));
}

_inline void c_map_load_error_helper::failed_to_open_mod_package_map_file(char const *mod_file, char const *map_path) // 0x10927670
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?failed_to_open_mod_package_map_file@c_map_load_error_helper@@QAEXPBD0@Z");
	// char const *map_path;

	set_last_error(std::format("Failed to open mod package map file\n\nMod: {}\nMap: {}", mod_file, map_path));
}

extern std::string const &_sub_10927BF0(c_map_load_error_helper const *const);
_inline std::string const &c_map_load_error_helper::get_last_error() const // 0x10927BF0
{
	mangled_x86(MANGLED_TODO, "?get_last_error@c_map_load_error_helper@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// c_map_load_error_helper const *const this;
	todo("implement");
	std::string const & __result = _sub_10927BF0((c_map_load_error_helper const *)this);
	return __result;
}

_extern void _sub_10929A90(c_map_load_error_helper *const, std::string const &);
_inline void c_map_load_error_helper::set_last_error(std::string const &message) // 0x10929A90
{
	mangled_x86(MANGLED_TODO, "?set_last_error@c_map_load_error_helper@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	// std::string const &message;
	todo("implement");
	_sub_10929A90(this, message);
}

_inline void c_map_load_error_helper::reset() // 0x10929590
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?reset@c_map_load_error_helper@@QAEXXZ");
	// c_map_load_error_helper *const this;

	set_last_error("An unknown error has occured.");
}

extern char const *_sub_10929B40(c_map_load_error_helper *const, char *, unsigned long, char const *);
_inline char const *c_map_load_error_helper::tag_filename(char *buff, unsigned long group, char const *name) // 0x10929B40
{
	mangled_x86(MANGLED_TODO, "?tag_filename@c_map_load_error_helper@@AAEPBDPADKPBD@Z");
	// c_map_load_error_helper *const this;
	// char *buff;
	// unsigned long group;
	// char const *name;
	// char ext[5];
	todo("implement");
	char const * __result = _sub_10929B40(this, buff, group, name);
	return __result;
}

/* ---------- private code */

#endif // __MODS_MAP_LOAD_ERROR_HELPER_HPP__
