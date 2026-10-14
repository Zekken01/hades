/* ---------- headers */

#include "Blam/saved_games/content_blf.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

struct s_blf_chunk_content_header;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

s_blf_chunk_content_header::s_blf_chunk_content_header() // 0x10F1C3A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_blf_chunk_content_header@@QAE@XZ");
	// s_blf_chunk_content_header *const this;
	// function call : long (*const)()
	// function call : long (*const)()

	setup('chdr', sizeof(s_blf_chunk_content_header), 9, 3);
	build_version_major = (short)reinterpret_cast<long (*)()>(0x501420)();
	build_version_minor = (short)reinterpret_cast<long (*)()>(0x52D360)();
	metadata.name[0] = 0;
	metadata.description[0] = 0;
	metadata.author[0] = 0;
	metadata.content_type = -1;
	metadata.timestamp = 0;
	metadata.unknown = 0;
	metadata.map_id = -1;
	metadata.game_engine_type = 0;
}

/* ---------- private code */
