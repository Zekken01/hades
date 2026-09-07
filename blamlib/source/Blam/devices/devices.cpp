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

extern c_data_array<s_device_group_datum> *device_groups_get();
extern long device_group_new(long device_index, float initial_value, unsigned long flags);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern c_data_array<s_device_group_datum> *_sub_10F0C5C0();
c_data_array<s_device_group_datum> *device_groups_get() // 0x10F0C5C0
{
	mangled_x86(MANGLED_TODO, "?device_groups_get@@YAPAV?$c_data_array@Us_device_group_datum@@@@XZ");
	// procedure flags: nofpo
	todo("implement");
	c_data_array<s_device_group_datum> * __result = _sub_10F0C5C0();
	return __result;
}

_extern long _sub_10F0C4E0(long, float, unsigned long);
long device_group_new(long device_index, float initial_value, unsigned long flags) // 0x10F0C4E0
{
	mangled_x86(MANGLED_TODO, "?device_group_new@@YAJJMK@Z");
	// unsigned long flags;
	// s_device_group_datum *datum;
	// unsigned long datum_index;
	// c_data_array<s_device_group_datum> *device_groups;
	// function call : unsigned long (*const)(s_data_array *)
	todo("implement");
	long __result = _sub_10F0C4E0(device_index, initial_value, flags);
	return __result;
}

/* ---------- private code */
