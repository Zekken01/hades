/* ---------- headers */

#include "mods/blf_writer.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"

/* ---------- forward declarations */

class c_blf_writer;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void *_sub_1086D800(c_blf_writer *const, unsigned long);
void *c_blf_writer::allocate_chunk(unsigned long size) // 0x1086D800
{
	mangled_x86(MANGLED_TODO, "?allocate_chunk@c_blf_writer@@QAEPAXK@Z");
	// unsigned long size;
	// unsigned char *head;
	todo("implement");
	void * __result = _sub_1086D800(this, size);
	return __result;
}

/* ---------- private code */
