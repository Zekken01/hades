/* ---------- headers */

#include "mods/blf_reader.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/saved_games/blf.hpp"
#include "Blam/tag_files/tag_groups.hpp"

#include <Windows.h>

/* ---------- forward declarations */

class c_blf_reader;
struct s_blf_chunk_header;
struct s_blf_chunk_start_of_file;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern bool blf_find_chunk_in_buffer(unsigned char const *buffer, unsigned long buffer_size, unsigned long signature, s_blf_chunk_header *out_header, unsigned char const **out_data, unsigned long *out_data_size);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

c_blf_reader::c_blf_reader(unsigned char const *buffer, unsigned long size) // 0x1086D360
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_blf_reader@@QAE@PBEK@Z");

	m_should_byte_swap = false;
	m_buffer = buffer;
	m_size = size;
	m_position = 0;
}

bool c_blf_reader::read_next_chunk_internal(s_blf_chunk_header *out_header, unsigned char const **out_data, unsigned long *out_data_size) // 0x1086D640
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?read_next_chunk_internal@c_blf_reader@@AAE_NPAUs_blf_chunk_header@@PAPBEPAK@Z");

	if (&m_buffer[m_position + sizeof(s_blf_chunk_header)] > m_buffer + m_size)
		return false;

	s_blf_chunk_header &header = *out_header = *(s_blf_chunk_header const *)(m_buffer + m_position);
	if (m_should_byte_swap)
	{
		header.signature = _byteswap_ulong(header.signature);
		header.size = _byteswap_ulong(header.size);
		header.version_major = _byteswap_ushort(header.version_major);
		header.version_minor = _byteswap_ushort(header.version_minor);
	}

	if (header.size < sizeof(s_blf_chunk_header) || &m_buffer[m_position + header.size] > m_buffer + m_size)
		return false;

	*out_header = header;
	*out_data = &m_buffer[m_position + sizeof(s_blf_chunk_header)];
	*out_data_size = header.size - sizeof(s_blf_chunk_header);
	m_position += header.size;
	return true;
}

bool c_blf_reader::begin() // 0x1086D3B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?begin@c_blf_reader@@QAE_NXZ");

	m_should_byte_swap = false;
	s_blf_chunk_header chunk_header;
	unsigned char const *data = nullptr;
	unsigned long data_size;
	s_blf_chunk_start_of_file *start_of_file = (s_blf_chunk_start_of_file *)m_buffer;
	if (!read_next_chunk_internal(&chunk_header, &data, &data_size))
		return false;
	if (chunk_header.signature != '_blf' || start_of_file->version_major != 1)
		return false;
	if (chunk_header.size < 0x30)
		return false;
	return true;
}

bool blf_find_chunk_in_buffer(unsigned char const *buffer, unsigned long buffer_size, unsigned long signature, s_blf_chunk_header *out_header, unsigned char const **out_data, unsigned long *out_data_size) // 0x1086D4F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?blf_find_chunk_in_buffer@@YA_NPBEKKPAUs_blf_chunk_header@@PAPBEPAK@Z");

	c_blf_reader blf_reader(buffer, buffer_size);
	if (!blf_reader.begin())
	{
		return false;
	}

	while (blf_reader.read_next_chunk(out_header, out_data, out_data_size))
	{
		if (out_header->signature == signature)
		{
			return true;
		}

		if (out_header->signature == '_eof')
		{
			break;
		}
	}

	return false;
}

/* ---------- private code */
