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

inline c_tag_name_dictionary::c_tag_name_dictionary() // 0x10877860
{
}

inline c_tag_name_dictionary::c_tag_name_dictionary(std::unordered_map<int,std::string> &&names) : m_index_to_name(std::move(names)) /* hades-mem-init:  */ // 0x1089D060
{
}

inline c_tag_name_dictionary::c_tag_name_dictionary(c_tag_name_dictionary &&__that) noexcept = default; // 0x10871760

inline c_tag_name_dictionary::~c_tag_name_dictionary() // 0x10877F60
{
}

inline void c_tag_name_dictionary::add(long index, char const *name) // 0x10879940
{
	m_index_to_name[index] = name;
}

inline char const *c_tag_name_dictionary::get_name(long index) const // 0x10874230
{
	if (auto it = m_index_to_name.find(index); it != std::end(m_index_to_name))
		return it->second.c_str();
	return nullptr;
}

/* ---------- private code */

#endif // __MODS_TAG_NAME_DICTIONARY_HPP__
