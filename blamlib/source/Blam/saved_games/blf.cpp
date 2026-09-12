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

void s_blf_chunk_header::setup(unsigned long signature, unsigned long size, short version_major, short version_minor) // 0x10F0D870
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?setup@s_blf_chunk_header@@QAEXKKFF@Z");
	// short version_minor;

	this->signature = signature;
	this->size = size;
	this->version_major = version_major;
	this->version_minor = version_minor;
}

s_blf_chunk_start_of_file::s_blf_chunk_start_of_file() // 0x10F0D780
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_blf_chunk_start_of_file@@QAE@XZ");
	// s_blf_chunk_start_of_file *const this;

	setup(0x5F626C66, 48, 1, 2);
	byte_order_marker = -2;
	memset(&internal_name, 0, sizeof(internal_name));
}

s_blf_chunk_end_of_file::s_blf_chunk_end_of_file() // 0x10F0D6D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_blf_chunk_end_of_file@@QAE@XZ");
	// s_blf_chunk_end_of_file *const this;

	setup(0x5F656F66, 17, 1, 1);
	authentication_data_size = 0;
	authentication_type = 0;
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_enum<enum e_blf_authentication_type,char> & c_enum<enum e_blf_authentication_type,char>::operator=(char const &);
template c_enum<enum e_blf_authentication_type,char>::c_enum();
