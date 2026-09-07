/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern char const *tag_name_strip_path(char const *name);
extern char const *tag_name_get_directory(char const *tag_name);
extern char const *tag_name_get_filename_without_extension(char const *tag_name);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern char const *_sub_10F18F00(char const *);
char const *tag_name_strip_path(char const *name) // 0x10F18F00
{
	mangled_x86(MANGLED_TODO, "?tag_name_strip_path@@YAPBDPBD@Z");
	// char const *name;
	// char const *result;
	todo("implement");
	char const * __result = _sub_10F18F00(name);
	return __result;
}

extern char const *_sub_10F18C90(char const *);
char const *tag_name_get_directory(char const *tag_name) // 0x10F18C90
{
	mangled_x86(MANGLED_TODO, "?tag_name_get_directory@@YAPBDPBD@Z");
	// char const *tag_name;
	// thread_local char buffer[256]; // 0x12579668
	// unsigned long position;
	// long length;
	todo("implement");
	char const * __result = _sub_10F18C90(tag_name);
	return __result;
}

extern char const *_sub_10F18DC0(char const *);
char const *tag_name_get_filename_without_extension(char const *tag_name) // 0x10F18DC0
{
	mangled_x86(MANGLED_TODO, "?tag_name_get_filename_without_extension@@YAPBDPBD@Z");
	// char const *tag_name;
	// thread_local char buffer[256]; // 0x12579568
	// unsigned long position;
	// long length;
	// char const *filename;
	todo("implement");
	char const * __result = _sub_10F18DC0(tag_name);
	return __result;
}

/* ---------- private code */
