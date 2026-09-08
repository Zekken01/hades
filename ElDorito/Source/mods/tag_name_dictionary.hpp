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
	_inline c_tag_name_dictionary(c_tag_name_dictionary &&__that);
	c_tag_name_dictionary(c_tag_name_dictionary const &);
	_inline c_tag_name_dictionary(std::unordered_map<int,std::string,std::hash<int>,std::equal_to<int>,std::allocator<std::pair<int const ,std::string> > > &&names);
	_inline c_tag_name_dictionary();
private:
	c_tag_name_dictionary(std::unordered_map<int,std::string,std::hash<int>,std::equal_to<int>,std::allocator<std::pair<int const ,std::string> > > const &);
public:
	_inline ~c_tag_name_dictionary();
	c_tag_name_dictionary &operator=(c_tag_name_dictionary &);
	c_tag_name_dictionary &operator=(c_tag_name_dictionary const &);
	void clear();
	_inline void add(long index, char const *name);
	_inline char const *get_name(long index) const;
	bool contains(long) const;
	c_tag_name_dictionary clone();
	std::unordered_map<int,std::string,std::hash<int>,std::equal_to<int>,std::allocator<std::pair<int const ,std::string> > > m_index_to_name; // 0x0
};
static_assert(sizeof(c_tag_name_dictionary) == 40, "Invalid c_tag_name_dictionary size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

extern c_tag_name_dictionary* _sub_10877860(c_tag_name_dictionary *const);
_inline c_tag_name_dictionary::c_tag_name_dictionary() // 0x10877860
{
	mangled_x86(MANGLED_TODO, "??0c_tag_name_dictionary@@QAE@XZ");
	// c_tag_name_dictionary *const this;
	todo("implement");
	_sub_10877860(this);
}

extern c_tag_name_dictionary* _sub_1089D060(c_tag_name_dictionary *const, std::unordered_map<int,std::string,std::hash<int>,std::equal_to<int>,std::allocator<std::pair<int const ,std::string> > > &);
_inline c_tag_name_dictionary::c_tag_name_dictionary(std::unordered_map<int,std::string,std::hash<int>,std::equal_to<int>,std::allocator<std::pair<int const ,std::string> > > &&names) // 0x1089D060
{
	mangled_x86(MANGLED_TODO, "??0c_tag_name_dictionary@@QAE@$$QAV?$unordered_map@HV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$hash@H@2@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBHV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@@2@@std@@@Z");
	// std::unordered_map<int,std::string,std::hash<int>,std::equal_to<int>,std::allocator<std::pair<int const ,std::string> > > &names;
	todo("implement");
	_sub_1089D060(this, names);
}

extern c_tag_name_dictionary* _sub_10871760(c_tag_name_dictionary *const, c_tag_name_dictionary &);
_inline c_tag_name_dictionary::c_tag_name_dictionary(c_tag_name_dictionary &&__that) // 0x10871760
{
	mangled_x86(MANGLED_TODO, "??0c_tag_name_dictionary@@QAE@$$QAV0@@Z");
	// c_tag_name_dictionary &__that;
	todo("implement");
	_sub_10871760(this, __that);
}

_extern void _sub_10877F60(c_tag_name_dictionary *const);
_inline c_tag_name_dictionary::~c_tag_name_dictionary() // 0x10877F60
{
	mangled_x86(MANGLED_TODO, "??1c_tag_name_dictionary@@QAE@XZ");
	// c_tag_name_dictionary *const this;
	todo("implement");
	_sub_10877F60(this);
}

_extern void _sub_10879940(c_tag_name_dictionary *const, long, char const *);
_inline void c_tag_name_dictionary::add(long index, char const *name) // 0x10879940
{
	mangled_x86(MANGLED_TODO, "?add@c_tag_name_dictionary@@QAEXJPBD@Z");
	// char const *name;
	todo("implement");
	_sub_10879940(this, index, name);
}

extern char const *_sub_10874230(c_tag_name_dictionary const *const, long);
_inline char const *c_tag_name_dictionary::get_name(long index) const // 0x10874230
{
	mangled_x86(MANGLED_TODO, "?get_name@c_tag_name_dictionary@@QBEPBDJ@Z");
	// static ...; // 0x10874380
	// static ...; // 0x10874378
	// c_tag_name_dictionary const *const this;
	// long index;
	{
		// std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<int const ,std::string> > > > it;
	}
	todo("implement");
	char const * __result = _sub_10874230((c_tag_name_dictionary const *)this, index);
	return __result;
}

/* ---------- private code */

#endif // __MODS_TAG_NAME_DICTIONARY_HPP__
