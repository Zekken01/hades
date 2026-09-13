/* ---------- headers */

#include "Blam/tag_files/tag_groups.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"

/* ---------- forward declarations */

struct s_cache_tag_instance;
struct s_tag_padding_definition;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern s_cache_file_tag_globals *g_cache_file_tag_globals;  // hades: added for 0x10EFC640

extern void *tag_try_and_get_and_verify_group(unsigned long group_tag, long tag_index);
extern unsigned long tag_try_and_get_group_tag(long tag_index);
extern unsigned long tag_get_group_tag(long tag_index);
extern bool tag_loaded(long tag_index);
extern bool tags_loaded();

extern "C" s_cache_tag_instance *try_and_get_instance_internal(long tag_index);

/* ---------- globals */

extern void *(*const tag_get)(unsigned long, long); // 0x11248AE4
extern long (*const tag_get_first_in_group)(unsigned long); // 0x11248AE8
extern s_tag_padding_definition *g_pad8_definition; // 0x113595A8
extern s_tag_padding_definition *g_pad16_definition; // 0x113595AC
extern s_tag_padding_definition *g_pad32_definition; // 0x113595B0
extern s_tag_padding_definition *g_pad64_definition; // 0x113595B4
extern s_tag_padding_definition pad8; // 0x113595B8
extern s_tag_padding_definition pad16; // 0x113595C0
extern s_tag_padding_definition pad32; // 0x113595C8
extern s_tag_padding_definition pad64; // 0x113595D0

/* ---------- private variables */

/* ---------- public code */

void *tag_try_and_get_and_verify_group(unsigned long group_tag, long tag_index) // 0x10EFC4F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?tag_try_and_get_and_verify_group@@YAPAXKJ@Z");
	// long tag_index;
	// s_cache_tag_instance *instance;

	s_cache_tag_instance *instance = try_and_get_instance_internal(tag_index);
	if (!instance)
		return nullptr;
	if (!(instance->group.tags[0] == group_tag
		|| instance->group.tags[1] == group_tag
		|| instance->group.tags[2] == group_tag))
	{
		return nullptr;
	}
	return (char *)instance + instance->definition_offset;
}

_extern unsigned long _sub_10EFC5C0(long);
unsigned long tag_try_and_get_group_tag(long tag_index) // 0x10EFC5C0
{
	mangled_x86(MANGLED_TODO, "?tag_try_and_get_group_tag@@YAKJ@Z");
	// long tag_index;
	// s_cache_tag_instance *instance;
	todo("implement");
	unsigned long __result = _sub_10EFC5C0(tag_index);
	return __result;
}

unsigned long tag_get_group_tag(long tag_index) // 0x10EFC390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?tag_get_group_tag@@YAKJ@Z");
	// long tag_index;

	return g_cache_file_tag_globals->instances[g_cache_file_tag_globals->index_to_absolute_index_map[tag_index]]->group.tags[0];
}

_extern bool _sub_10EFC410(long);
bool tag_loaded(long tag_index) // 0x10EFC410
{
	mangled_x86(MANGLED_TODO, "?tag_loaded@@YA_NJ@Z");
	// long tag_index;
	// long absolute_index;
	todo("implement");
	bool __result = _sub_10EFC410(tag_index);
	return __result;
}

bool tags_loaded() // 0x10EFC640
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?tags_loaded@@YA_NXZ");
	// procedure flags: nofpo

	return g_cache_file_tag_globals->initialized;
}

/* ---------- private code */

extern s_cache_tag_instance *_sub_10EFC690(long);
extern "C" s_cache_tag_instance *try_and_get_instance_internal(long tag_index) // 0x10EFC690
{
	// try_and_get_instance_internal
	// long tag_index;
	// s_cache_tag_instance *instance;
	// long absolute_index;
	todo("implement");
	s_cache_tag_instance * __result = _sub_10EFC690(tag_index);
	return __result;
}
