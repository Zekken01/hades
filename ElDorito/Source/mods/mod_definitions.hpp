#ifndef __MODS_MOD_DEFINITIONS_HPP__
#define __MODS_MOD_DEFINITIONS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include <memory>
#include <string>

/* ---------- forward declarations */

struct s_mod_origin_info;

/* ---------- constants */

/* ---------- definitions */

struct s_mod_origin_info
{
	std::string server_ip; // 0x0
	std::string server_host; // 0x1C
	std::string server_name; // 0x38
	std::string url; // 0x54
	_inline s_mod_origin_info(s_mod_origin_info &&__that); /* compiler_generated() */
	_inline s_mod_origin_info(s_mod_origin_info const &__that); /* compiler_generated() */
	_inline s_mod_origin_info(); /* compiler_generated() */
	_inline ~s_mod_origin_info(); /* compiler_generated() */
	s_mod_origin_info &operator=(s_mod_origin_info &); /* compiler_generated() */
	_inline s_mod_origin_info &operator=(s_mod_origin_info const &__that); /* compiler_generated() */
};
static_assert(sizeof(s_mod_origin_info) == 112, "Invalid s_mod_origin_info size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODS_MOD_DEFINITIONS_HPP__
