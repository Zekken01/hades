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

unsigned long tag_try_and_get_group_tag(long tag_index) // 0x10EFC5C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?tag_try_and_get_group_tag@@YAKJ@Z");

	auto instance = try_and_get_instance_internal(tag_index);
	if (!instance)
		return NONE;
	return instance->group.tags[0];
}

unsigned long tag_get_group_tag(long tag_index) // 0x10EFC390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?tag_get_group_tag@@YAKJ@Z");

	return g_cache_file_tag_globals->instances[g_cache_file_tag_globals->index_to_absolute_index_map[tag_index]]->group.tags[0];
}

bool tag_loaded(long tag_index) // 0x10EFC410
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?tag_loaded@@YA_NJ@Z");

	if (!g_cache_file_tag_globals->initialized)
	{
		return false;
	}

	if (tag_index < 0 || tag_index >= 0xFFFF)
	{
		return false;
	}

	long absolute_index = g_cache_file_tag_globals->index_to_absolute_index_map[tag_index];
	if (absolute_index < 0 || absolute_index >= g_cache_file_tag_globals->loaded_instance_count)
	{
		return false;
	}

	return g_cache_file_tag_globals->instances[absolute_index] != nullptr;
}

bool tags_loaded() // 0x10EFC640
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?tags_loaded@@YA_NXZ");

	return g_cache_file_tag_globals->initialized;
}

/* ---------- private code */

extern "C" s_cache_tag_instance *try_and_get_instance_internal(long tag_index) // 0x10EFC690
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_try_and_get_instance_internal");

	if (tag_index < 0 || tag_index >= 0xFFFF)
	{
		return nullptr;
	}

	long absolute_index = g_cache_file_tag_globals->index_to_absolute_index_map[tag_index];
	if (absolute_index < 0 || absolute_index >= 0xFFFF)
	{
		return nullptr;
	}

	s_cache_tag_instance *instance = g_cache_file_tag_globals->instances[absolute_index];
	return instance;
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
void *(*const tag_get)(unsigned long, long) = reinterpret_cast<decltype(tag_get)>(0x503370);
long (*const tag_get_first_in_group)(unsigned long) = reinterpret_cast<decltype(tag_get_first_in_group)>(0x5017E0);
s_tag_padding_definition *g_pad16_definition = &pad16;
s_tag_padding_definition pad16 = { "pad16", 2 };
