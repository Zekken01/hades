#ifndef __MODS_TAG_NAME_DICTIONARY_HPP__
#define __MODS_TAG_NAME_DICTIONARY_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

/* ---------- forward declarations */

class c_tag_name_dictionary;

/* ---------- constants */

/* ---------- definitions */

class c_tag_name_dictionary
{
public:
	_inline c_tag_name_dictionary(c_tag_name_dictionary &&__that) noexcept; // hades: noexcept (original has a terminate frame and no std::move call)
	c_tag_name_dictionary(c_tag_name_dictionary const &);
	_inline c_tag_name_dictionary(std::unordered_map<int,std::string> &&names);
	_inline c_tag_name_dictionary();
private:
	c_tag_name_dictionary(std::unordered_map<int,std::string> const &);
public:
	_inline ~c_tag_name_dictionary();
	c_tag_name_dictionary &operator=(c_tag_name_dictionary &);
	c_tag_name_dictionary &operator=(c_tag_name_dictionary const &);
	void clear();
	_inline void add(long index, char const *name);
	_inline char const *get_name(long index) const;
	bool contains(long) const;
	c_tag_name_dictionary clone();
	std::unordered_map<int,std::string> m_index_to_name; // 0x0
};
static_assert(sizeof(c_tag_name_dictionary) == 40, "Invalid c_tag_name_dictionary size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline c_tag_name_dictionary::c_tag_name_dictionary() // 0x10877860
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_tag_name_dictionary@@QAE@XZ");
	// c_tag_name_dictionary *const this;
}

_inline c_tag_name_dictionary::c_tag_name_dictionary(std::unordered_map<int,std::string> &&names) : m_index_to_name(std::move(names)) /* hades-mem-init:  */ // 0x1089D060
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_tag_name_dictionary@@QAE@$$QAV?$unordered_map@HV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$hash@H@2@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBHV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@@2@@std@@@Z");
	// std::unordered_map<int,std::string> &names;
}

// mangled_x86(MANGLED_DEFAULT, "??0c_tag_name_dictionary@@QAE@$$QAV0@@Z"); no body to assert in
_inline c_tag_name_dictionary::c_tag_name_dictionary(c_tag_name_dictionary &&__that) noexcept = default; // 0x10871760

_inline c_tag_name_dictionary::~c_tag_name_dictionary() // 0x10877F60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1c_tag_name_dictionary@@QAE@XZ");
	// c_tag_name_dictionary *const this;
}

_inline void c_tag_name_dictionary::add(long index, char const *name) // 0x10879940
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?add@c_tag_name_dictionary@@QAEXJPBD@Z");
	// char const *name;

	m_index_to_name[index] = name;
}

_inline char const *c_tag_name_dictionary::get_name(long index) const // 0x10874230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_name@c_tag_name_dictionary@@QBEPBDJ@Z");
	// static ...; // 0x10874380
	// static ...; // 0x10874378
	// c_tag_name_dictionary const *const this;
	// long index;
		// std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<int const ,std::string> > > > it;

	if (auto it = m_index_to_name.find(index); it != std::end(m_index_to_name))
		return it->second.c_str();
	return nullptr;
}

/* ---------- private code */

#endif // __MODS_TAG_NAME_DICTIONARY_HPP__
