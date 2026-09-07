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

extern c_blf_reader* _sub_1086D360(c_blf_reader *const, unsigned char const *, unsigned long);
c_blf_reader::c_blf_reader(unsigned char const *buffer, unsigned long size) // 0x1086D360
{
	mangled_x86(MANGLED_TODO, "??0c_blf_reader@@QAE@PBEK@Z");
	// unsigned long size;
	todo("implement");
	_sub_1086D360(this, buffer, size);
}

_extern bool _sub_1086D640(c_blf_reader *const, s_blf_chunk_header *, unsigned char const **, unsigned long *);
bool c_blf_reader::read_next_chunk_internal(s_blf_chunk_header *out_header, unsigned char const **out_data, unsigned long *out_data_size) // 0x1086D640
{
	mangled_x86(MANGLED_TODO, "?read_next_chunk_internal@c_blf_reader@@AAE_NPAUs_blf_chunk_header@@PAPBEPAK@Z");
	// unsigned long *out_data_size;
	// s_blf_chunk_header &header;
	todo("implement");
	bool __result = _sub_1086D640(this, out_header, out_data, out_data_size);
	return __result;
}

_extern bool _sub_1086D3B0(c_blf_reader *const);
bool c_blf_reader::begin() // 0x1086D3B0
{
	mangled_x86(MANGLED_TODO, "?begin@c_blf_reader@@QAE_NXZ");
	// static ...; // 0x1086D49F
	// static ...; // 0x1086D49A
	// static ...; // 0x1086D490
	// static ...; // 0x1086D46C
	// static ...; // 0x1086D464
	// c_blf_reader *const this;
	// s_blf_chunk_header chunk_header;
	// unsigned char const *data;
	// unsigned long data_size;
	// s_blf_chunk_start_of_file *start_of_file;
	todo("implement");
	bool __result = _sub_1086D3B0(this);
	return __result;
}

_extern bool _sub_1086D4F0(unsigned char const *, unsigned long, unsigned long, s_blf_chunk_header *, unsigned char const **, unsigned long *);
bool blf_find_chunk_in_buffer(unsigned char const *buffer, unsigned long buffer_size, unsigned long signature, s_blf_chunk_header *out_header, unsigned char const **out_data, unsigned long *out_data_size) // 0x1086D4F0
{
	mangled_x86(MANGLED_TODO, "?blf_find_chunk_in_buffer@@YA_NPBEKKPAUs_blf_chunk_header@@PAPBEPAK@Z");
	// unsigned long signature;
	// s_blf_chunk_header *out_header;
	// unsigned char const **out_data;
	// unsigned long *out_data_size;
	// c_blf_reader blf_reader;
	todo("implement");
	bool __result = _sub_1086D4F0(buffer, buffer_size, signature, out_header, out_data, out_data_size);
	return __result;
}

/* ---------- private code */
