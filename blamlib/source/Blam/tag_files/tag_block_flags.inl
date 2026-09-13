#ifndef __BLAM_TAG_FILES_TAG_BLOCK_FLAGS_INL__
#define __BLAM_TAG_FILES_TAG_BLOCK_FLAGS_INL__
#pragma once

/* ---------- headers */

#include "hades/hades.h"
struct s_scenario_structure_bsp_reference;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline c_tag_block_flags<s_scenario_structure_bsp_reference,long>::operator long() const // 0x10AC3F30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$c_tag_block_flags@Us_scenario_structure_bsp_reference@@J@@QBEJXZ");

	return m_flags;
}

/* ---------- private code */

#endif // __BLAM_TAG_FILES_TAG_BLOCK_FLAGS_INL__
