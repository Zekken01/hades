/* ---------- headers */

#include "Blam/saved_games/blf.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/tag_files/tag_groups.hpp"

#include <Windows.h>

/* ---------- forward declarations */

struct s_blf_chunk_end_of_file;
struct s_blf_chunk_header;
struct s_blf_chunk_start_of_file;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_10F0D870(s_blf_chunk_header *const, unsigned long, unsigned long, short, short);
void s_blf_chunk_header::setup(unsigned long signature, unsigned long size, short version_major, short version_minor) // 0x10F0D870
{
	mangled_x86(MANGLED_TODO, "?setup@s_blf_chunk_header@@QAEXKKFF@Z");
	// short version_minor;
	todo("implement");
	_sub_10F0D870(this, signature, size, version_major, version_minor);
}

extern s_blf_chunk_start_of_file* _sub_10F0D780(s_blf_chunk_start_of_file *const);
s_blf_chunk_start_of_file::s_blf_chunk_start_of_file() // 0x10F0D780
{
	mangled_x86(MANGLED_TODO, "??0s_blf_chunk_start_of_file@@QAE@XZ");
	// s_blf_chunk_start_of_file *const this;
	todo("implement");
	_sub_10F0D780(this);
}

extern s_blf_chunk_end_of_file* _sub_10F0D6D0(s_blf_chunk_end_of_file *const);
s_blf_chunk_end_of_file::s_blf_chunk_end_of_file() // 0x10F0D6D0
{
	mangled_x86(MANGLED_TODO, "??0s_blf_chunk_end_of_file@@QAE@XZ");
	// s_blf_chunk_end_of_file *const this;
	todo("implement");
	_sub_10F0D6D0(this);
}

/* ---------- private code */
