/* ---------- headers */

#include "Blam/cache/cache_files.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

struct s_cache_file_header;
struct s_cache_file_tag_globals;
struct s_cache_tag_instance;
struct s_file_reference;
struct s_tag_reference;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void cache_file_tag_references_fixup();
extern void cache_file_tags_close();

/* ---------- globals */

extern s_cache_file_tag_globals *g_cache_file_tag_globals; // 0x1135A100
extern char const *(*const cache_files_map_directory)(); // 0x1124B93C
extern bool (*const cache_file_header_verify)(s_cache_file_header *, char const *, bool); // 0x1124B948
extern bool (*const cache_file_open_package)(char const *, s_cache_file_header *); // 0x1124B944
extern long (*const cache_file_globals_get_tag)(long); // 0x1124B94C
extern void (*const cache_files_tags_reset)(); // 0x1124B954
extern bool (*const cache_file_open_internal)(long, char const *); // 0x1124B940
extern void (*const cache_files_close)(); // 0x1124B950
extern long (*const cache_files_read_from_tag_cache_blocking)(long, long, void *); // 0x1124B958
extern bool (*const cache_file_tags_fixup)(); // 0x1124B95C
extern bool (*const cache_file_tags_open)(); // 0x1124B960
extern void (*const sub_502500)(void *, s_cache_file_header *); // 0x1124B964
extern void (*const sub_503470)(void *, void *, long); // 0x1124B968

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_10F18FC0();
void cache_file_tag_references_fixup() // 0x10F18FC0
{
	mangled_x86(MANGLED_TODO, "?cache_file_tag_references_fixup@@YAXXZ");
	// procedure flags: nofpo
	{
		// __int32 i;
		{
			// s_cache_tag_instance *instance;
			// unsigned long *tag_reference_fixups;
			{
				// __int32 j;
				{
					// s_tag_reference *reference;
				}
			}
		}
	}
	todo("implement");
	_sub_10F18FC0();
}

void cache_file_tags_close() // 0x10F190F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?cache_file_tags_close@@YAXXZ");
	// procedure flags: nofpo
	// function call : bool (*const)(s_file_reference *)

	file_close(&g_cache_file_tag_globals->cache_file_reference);
}

/* ---------- private code */
