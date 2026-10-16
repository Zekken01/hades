/* ---------- headers */

#include "Blam/devices/devices.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

struct s_data_array;
struct s_device_group_datum;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern unsigned long (*const datum_new)(s_data_array *);  // hades: added for 0x10F0C4E0

extern c_data_array<s_device_group_datum> *device_groups_get();
extern long device_group_new(long device_index, float initial_value, unsigned long flags);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

c_data_array<s_device_group_datum> *device_groups_get() // 0x10F0C5C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?device_groups_get@@YAPAV?$c_data_array@Us_device_group_datum@@@@XZ");

	return tls_getd().device_groups;
}

long device_group_new(long device_index, float initial_value, unsigned long flags) // 0x10F0C4E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?device_group_new@@YAJJMK@Z");

	c_data_array<s_device_group_datum> *device_groups = device_groups_get();
	unsigned long datum_index = datum_new(device_groups);
	s_device_group_datum *datum = device_groups->try_and_get(datum_index);
	if (datum)
	{
		datum->object_index = device_index;
		datum->value = initial_value;
		datum->initial_value = initial_value;
		datum->flags = (unsigned short)flags;
	}

	return datum_index;
}

/* ---------- private code */
