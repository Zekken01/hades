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

bool parse_tag_file_name(char const *path, char *out_tag_name, unsigned long *out_group_tag) // 0x108C1F00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?parse_tag_file_name@@YA_NPBDPADPAK@Z");

	char const *ext_part = strrchr(path, '.');
	if (!ext_part)
		return false;
	unsigned __int32 name_legnth = ext_part - path;
	if (name_legnth >= 256)
		return false;
	strncpy_s(out_tag_name, 256, path, name_legnth);
	out_tag_name[name_legnth] = 0;
	unsigned __int32 len = strlen(ext_part);
	unsigned long tmp = 0;
	for (unsigned __int32 i = 1; i < len; i++)
	{
		tmp |= ext_part[i];
		if (i < len - 1)
			tmp <<= 8;
	}
	*out_group_tag = tmp;
	return true;
}

char const *tag_to_string(unsigned long tag, char *dest, long dest_length) // 0x108C2020
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?tag_to_string@@YAPBDKPADJ@Z");

	if (dest_length < 5)
	{
		return nullptr;
	}

	dest[0] = (tag >> 24) & 0xFF;
	dest[1] = (tag >> 16) & 0xFF;
	dest[2] = (tag >> 8) & 0xFF;
	dest[3] = tag & 0xFF;
	dest[4] = 0;
	return dest;
}

/* ---------- private code */
