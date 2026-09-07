#ifndef __BLAM_CACHE_TAG_ITERATOR_HPP__
#define __BLAM_CACHE_TAG_ITERATOR_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct s_tag_iterator;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_tag_iterator
{
	unsigned char __pad0[8]; // 0x0
	long tag_index; // 0x8
	long absolute_index; // 0xC
	long group_tag; // 0x10
};
#pragma pack(pop)
static_assert(sizeof(s_tag_iterator) == 20, "Invalid s_tag_iterator size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_CACHE_TAG_ITERATOR_HPP__
