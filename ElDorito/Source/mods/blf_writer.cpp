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

void *c_blf_writer::allocate_chunk(unsigned long size) // 0x1086D800
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?allocate_chunk@c_blf_writer@@QAEPAXK@Z");

	unsigned char *head = m_buffer + m_position;
	if (head + size > m_buffer + m_buffer_size)
	{
		return nullptr;
	}
	m_position += size;
	return head;
}

/* ---------- private code */
