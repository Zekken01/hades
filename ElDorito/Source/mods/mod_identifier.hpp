#ifndef __MODS_MOD_IDENTIFIER_HPP__
#define __MODS_MOD_IDENTIFIER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Utils/StlUtil.hpp"

#include <functional>
#include <memory>
#include <string>

/* ---------- forward declarations */

struct begin;
struct end;
struct s_mod_package_id;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_mod_package_id
{
	unsigned char hash[20]; // 0x0
	s_mod_package_id(unsigned char const (&hash)[20]);
	_inline s_mod_package_id();
	std::string const to_string() const;
	static s_mod_package_id from_string(std::string const &str);
	bool operator==(s_mod_package_id const &rhs) const;
};
#pragma pack(pop)
static_assert(sizeof(s_mod_package_id) == 20, "Invalid s_mod_package_id size");

template<> struct std::hash<s_mod_package_id>
{
	unsigned __int32 operator()(s_mod_package_id const &) const;
};
static_assert(sizeof(std::hash<s_mod_package_id>) == 1, "Invalid std::hash<s_mod_package_id> size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

extern s_mod_package_id* _sub_10853A40(s_mod_package_id *const);
_inline s_mod_package_id::s_mod_package_id() // 0x10853A40
{
	mangled_x86(MANGLED_TODO, "??0s_mod_package_id@@QAE@XZ");
	// s_mod_package_id *const this;
	todo("implement");
	_sub_10853A40(this);
}

_extern unsigned __int32 _sub_1084E890(std::hash<s_mod_package_id> const *const, s_mod_package_id const &);
_inline unsigned __int32 std::hash<s_mod_package_id>::operator()(s_mod_package_id const &k) const // 0x1084E890
{
	mangled_x86(MANGLED_TODO, "??R?$hash@Us_mod_package_id@@@std@@QBEIABUs_mod_package_id@@@Z");
	// s_mod_package_id const &k;
	// unsigned __int32 result;
	{
		// unsigned char const &<range>$L0[20];
		// unsigned char const *<begin>$L0;
		// unsigned char const *<end>$L0;
		{
			// unsigned char b;
		}
	}
	todo("implement");
	unsigned __int32 __result = _sub_1084E890((std::hash<s_mod_package_id> const *)this, k);
	return __result;
}

/* ---------- private code */

#endif // __MODS_MOD_IDENTIFIER_HPP__
