/* ---------- headers */

#include "Blam/memory/data.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"

/* ---------- forward declarations */

struct s_data_array;
struct s_data_iterator;
struct s_datum;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void *datum_get_absolute(s_data_array const *data, long index);  // hades: added for 0X10EF9120

extern void *datum_get_absolute(s_data_array const *data, long absolute_index);
extern long datum_absolute_index_to_index(s_data_array const *data, long absolute_index);

/* ---------- globals */

extern void *(*const datum_try_and_get_absolute)(s_data_array const *, unsigned long); // 0x11248898
extern void *(*const datum_try_and_get)(s_data_array const *, unsigned long); // 0x11248894
extern s_datum *(*const data_iterator_next)(s_data_iterator *); // 0x11248888
extern unsigned long (*const data_allocation_size)(long, unsigned long, long); // 0x11248880
extern void (*const datum_delete)(s_data_array *, long); // 0x11248890
extern void (*const data_iterator_new)(s_data_iterator *, s_data_array const *); // 0x11248884
extern unsigned long (*const datum_new)(s_data_array *); // 0x1124888C
extern void *(*const data_new)(char const *, long, unsigned long, long, void *); // 0x11248868
extern void (*const data_initialize)(s_data_array *, char const *, long, unsigned long, long, void *); // 0x1124886C
extern void (*const data_dispose)(s_data_array *); // 0x11248870
extern void (*const data_delete_all)(s_data_array *); // 0x11248874
extern void (*const data_make_valid)(s_data_array *); // 0x11248878
extern void (*const data_make_invalid)(s_data_array *); // 0x1124887C

/* ---------- private variables */

/* ---------- public code */

void *datum_get_absolute(s_data_array const *data, long absolute_index) // 0x10EF9190
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?datum_get_absolute@@YAPAXPBUs_data_array@@J@Z");
	// long absolute_index;

	return offset_pointer(data->address, absolute_index * data->datum_size);
}

long datum_absolute_index_to_index(s_data_array const *data, long absolute_index) // 0x10EF9120
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?datum_absolute_index_to_index@@YAJPBUs_data_array@@J@Z");
	// long absolute_index;

	if (absolute_index == -1)
	{
		return -1;
	}

	return absolute_index | (*(unsigned short *)datum_get_absolute(data, absolute_index) << 16);
}

/* ---------- private code */
