#ifndef __MODS_MOD_DATABASE_HPP__
#define __MODS_MOD_DATABASE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "Modules/ModuleServer.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

/* ---------- forward declarations */

class c_mod_database;
struct s_mod_origin_info;
struct s_mod_package_id;

/* ---------- constants */

/* ---------- definitions */

class c_mod_database
{
public:
	public:
	struct s_record
	{
		long long date_added; // 0x0
		long long date_last_used; // 0x8
		std::string mod_name; // 0x10
		s_mod_origin_info origin; // 0x2C
		bool signature_verified; // 0x9C
		_inline s_record(s_record &&__that); /* compiler_generated() */
		_inline s_record(s_record const &__that); /* compiler_generated() */
		_inline s_record(); /* compiler_generated() */
		_inline ~s_record(); /* compiler_generated() */
		s_record &operator=(s_record &); /* compiler_generated() */
		_inline s_record &operator=(s_record const &__that); /* compiler_generated() */
	};
	static_assert(sizeof(s_record) == 160, "Invalid s_record size");
	public:
	c_mod_database(c_mod_database &);
	c_mod_database(c_mod_database const &);
	_inline c_mod_database();
	~c_mod_database();
	c_mod_database &operator=(c_mod_database &);
	c_mod_database &operator=(c_mod_database const &);
	bool create(std::string const &filename);
	bool load(std::string const &filename);
	bool load_or_create(std::string const &filename);
	bool save();
	bool try_get_record(s_mod_package_id const &id, s_record **record);
	bool get_or_create_record(s_mod_package_id const &id, s_record **record);
	bool create_record(s_mod_package_id const &id, s_record **record);
	bool update_record(s_mod_package_id const &id, s_record const &record);
	bool delete_record(s_mod_package_id const &id);
	void notify_record_changed(s_mod_package_id const &id);
	_inline bool is_dirty() const;
	void purge_all_not_in_set(std::unordered_set<s_mod_package_id> set);
	void purge_any(std::function<bool __cdecl(s_mod_package_id const &,s_record const &)> predicate);
private:
	bool m_dirty; // 0x0
	unsigned char __pad0[3]; // 0x1
	std::string m_filename; // 0x4
	std::unordered_map<s_mod_package_id,s_record> m_records; // 0x20
};
static_assert(sizeof(c_mod_database) == 72, "Invalid c_mod_database size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

extern c_mod_database* _sub_108A4B70(c_mod_database *const);
_inline c_mod_database::c_mod_database() // 0x108A4B70
{
	mangled_x86(MANGLED_TODO, "??0c_mod_database@@QAE@XZ");
	// c_mod_database *const this;
	todo("implement");
	_sub_108A4B70(this);
}

_inline bool c_mod_database::is_dirty() const // 0x108AA470
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?is_dirty@c_mod_database@@QBE_NXZ");
	// c_mod_database const *const this;

	return m_dirty;
}

/* ---------- private code */

#endif // __MODS_MOD_DATABASE_HPP__
