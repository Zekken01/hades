#ifndef __MODS_MOD_PACKAGE_UPDATER_HPP__
#define __MODS_MOD_PACKAGE_UPDATER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/new/IModManager.hpp"
#include "Utils/StlUtil.hpp"

#include <deque>
#include <memory>
#include <queue>
#include <string>
#include <vector>

/* ---------- forward declarations */

class c_mod_package;
class c_mod_package_updater_blocking;
struct s_mod_package_header;

/* ---------- constants */

/* ---------- definitions */

class c_mod_package_updater_blocking
{
public:
	public:
	struct s_mod_package_description
	{
		std::string local_name; // 0x0
		std::string hash; // 0x1C
		std::string package_url; // 0x38
		unsigned char __pad0[4]; // 0x54
		unsigned long long package_size; // 0x58
		std::string mod_name; // 0x60
		std::string mod_author; // 0x7C
		std::string mod_description; // 0x98
		_inline s_mod_package_description(s_mod_package_description &&__that); /* compiler_generated() */
		_inline s_mod_package_description(s_mod_package_description const &__that); /* compiler_generated() */
		_inline s_mod_package_description(); /* compiler_generated() */
		_inline ~s_mod_package_description(); /* compiler_generated() */
		s_mod_package_description &operator=(s_mod_package_description &); /* compiler_generated() */
		s_mod_package_description &operator=(s_mod_package_description const &); /* compiler_generated() */
		unsigned char __pad1[4]; // 0xB4
	};
	static_assert(sizeof(s_mod_package_description) == 184, "Invalid s_mod_package_description size");
	public:
	void initialize(bool dedicated, char const *package_list_filename, char const *package_directory);
	bool update_packages_blocking();
	_inline std::vector<s_mod_package_description> const &get_package_list() const;
private:
	bool m_dedicated; // 0x0
	unsigned char __pad0[3]; // 0x1
	std::queue<s_mod_package_description> m_download_queue; // 0x4
	std::vector<s_mod_package_description> m_packages; // 0x18
	s_static_string<256> m_package_directory; // 0x28
	s_static_string<256> m_package_list_filename; // 0x128
	bool process_queue();
	bool locate_packages();
	bool update_package(s_mod_package_description *description);
	bool download_package(char const *package_url, char const *filename);
	void build_mod_package_description(c_mod_package &package, s_mod_package_description *description);
public:
	c_mod_package_updater_blocking(c_mod_package_updater_blocking &); /* compiler_generated() */
	c_mod_package_updater_blocking(c_mod_package_updater_blocking const &); /* compiler_generated() */
	_inline c_mod_package_updater_blocking(); /* compiler_generated() */
	_inline ~c_mod_package_updater_blocking(); /* compiler_generated() */
	c_mod_package_updater_blocking &operator=(c_mod_package_updater_blocking &); /* compiler_generated() */
	c_mod_package_updater_blocking &operator=(c_mod_package_updater_blocking const &); /* compiler_generated() */
};
static_assert(sizeof(c_mod_package_updater_blocking) == 552, "Invalid c_mod_package_updater_blocking size");

/* ---------- prototypes */

extern bool download_mod_package_header(char const *url, s_mod_package_header *out_header, bool use_range);

/* ---------- globals */

/* ---------- public code */

extern std::vector<c_mod_package_updater_blocking::s_mod_package_description> const &_sub_108BC820(c_mod_package_updater_blocking const *const);
_inline std::vector<c_mod_package_updater_blocking::s_mod_package_description> const &c_mod_package_updater_blocking::get_package_list() const // 0x108BC820
{
	mangled_x86(MANGLED_TODO, "?get_package_list@c_mod_package_updater_blocking@@QBEABV?$vector@Us_mod_package_description@c_mod_package_updater_blocking@@V?$allocator@Us_mod_package_description@c_mod_package_updater_blocking@@@std@@@std@@XZ");
	// c_mod_package_updater_blocking const *const this;
	todo("implement");
	std::vector<c_mod_package_updater_blocking::s_mod_package_description> const & __result = _sub_108BC820((c_mod_package_updater_blocking const *)this);
	return __result;
}

/* ---------- private code */

#endif // __MODS_MOD_PACKAGE_UPDATER_HPP__
