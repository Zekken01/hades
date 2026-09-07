/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern bool parse_tag_file_name(char const *path, char *out_tag_name, unsigned long *out_group_tag);
extern char const *tag_to_string(unsigned long tag, char *dest, long dest_length);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern bool _sub_108C1F00(char const *, char *, unsigned long *);
bool parse_tag_file_name(char const *path, char *out_tag_name, unsigned long *out_group_tag) // 0x108C1F00
{
	mangled_x86(MANGLED_TODO, "?parse_tag_file_name@@YA_NPBDPADPAK@Z");
	// unsigned long *out_group_tag;
	// unsigned __int32 name_legnth;
	// unsigned long tmp;
	// char const *ext_part;
	// unsigned __int32 len;
	{
		// unsigned __int32 i;
	}
	todo("implement");
	bool __result = _sub_108C1F00(path, out_tag_name, out_group_tag);
	return __result;
}

extern char const *_sub_108C2020(unsigned long, char *, long);
char const *tag_to_string(unsigned long tag, char *dest, long dest_length) // 0x108C2020
{
	mangled_x86(MANGLED_TODO, "?tag_to_string@@YAPBDKPADJ@Z");
	// long dest_length;
	todo("implement");
	char const * __result = _sub_108C2020(tag, dest, dest_length);
	return __result;
}

/* ---------- private code */
