#ifndef __MODS_BLF_READER_HPP__
#define __MODS_BLF_READER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/saved_games/blf.hpp"

/* ---------- forward declarations */

class c_blf_reader;
struct s_blf_chunk_header;

/* ---------- constants */

/* ---------- definitions */

class c_blf_reader
{
public:
	c_blf_reader(unsigned char const *buffer, unsigned long size);
	bool begin();
	_inline bool read_next_chunk(s_blf_chunk_header *out_header, unsigned char const **out_data, unsigned long *out_data_size);
private:
	bool m_should_byte_swap; // 0x0
	// 0x1: 3 bytes of implicit padding (hades: no array member, it would add a /GS cookie to every c_blf_reader local)
	unsigned char const *m_buffer; // 0x4
	unsigned long m_size; // 0x8
	unsigned long m_position; // 0xC
	bool read_next_chunk_internal(s_blf_chunk_header *out_header, unsigned char const **out_data, unsigned long *out_data_size);
};
static_assert(sizeof(c_blf_reader) == 16, "Invalid c_blf_reader size");

/* ---------- prototypes */

extern bool blf_find_chunk_in_buffer(unsigned char const *buffer, unsigned long buffer_size, unsigned long signature, s_blf_chunk_header *out_header, unsigned char const **out_data, unsigned long *out_data_size);

/* ---------- globals */

/* ---------- public code */

inline bool c_blf_reader::read_next_chunk(s_blf_chunk_header *out_header, unsigned char const **out_data, unsigned long *out_data_size) // 0x1086D5E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_next_chunk@c_blf_reader@@QAE_NPAUs_blf_chunk_header@@PAPBEPAK@Z");

	return read_next_chunk_internal(out_header, out_data, out_data_size);
}

/* ---------- private code */

#endif // __MODS_BLF_READER_HPP__
