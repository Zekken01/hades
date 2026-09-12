#ifndef __MODS_BLF_WRITER_HPP__
#define __MODS_BLF_WRITER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

class c_blf_writer;
struct t_arg0;

/* ---------- constants */

/* ---------- definitions */

class c_blf_writer
{
public:
	_inline c_blf_writer(unsigned long buffer_size, void *buffer);
	void *allocate_chunk(unsigned long size);
private:
	unsigned long m_position; // 0x0
	unsigned long m_buffer_size; // 0x4
	unsigned char *m_buffer; // 0x8
public:
	template<typename t_arg0>
	t_arg0 add_chunk();
};
static_assert(sizeof(c_blf_writer) == 12, "Invalid c_blf_writer size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline c_blf_writer::c_blf_writer(unsigned long buffer_size, void *buffer) // 0x10AC8590
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_blf_writer@@QAE@KPAX@Z");
	// void *buffer;

	m_position = 0;
	m_buffer_size = buffer_size;
	m_buffer = (unsigned char *)buffer;
}

template<typename t_arg0>
_inline t_arg0 c_blf_writer::add_chunk()
{
	mangled_prefix_assert("??$add_chunk@");
	todo("implement");
	return todo_result<t_arg0>();
}

/* ---------- private code */

#endif // __MODS_BLF_WRITER_HPP__
