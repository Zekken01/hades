#ifndef __BLAM_MEMORY_DATA_HPP__
#define __BLAM_MEMORY_DATA_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/objects/damage_definitions.hpp"

/* ---------- forward declarations */

struct s_datum;

/* ---------- constants */

/* ---------- definitions */

struct s_datum
{
	unsigned short salt; // 0x0
};
static_assert(sizeof(s_datum) == 2, "Invalid s_datum size");

// s_data_array is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// s_data_iterator is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

extern void *datum_get_absolute(s_data_array const *data, long absolute_index);
extern long datum_absolute_index_to_index(s_data_array const *data, long absolute_index);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_MEMORY_DATA_HPP__
