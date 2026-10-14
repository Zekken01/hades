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

char const *tag_name_strip_path(char const *name) // 0x10F18F00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?tag_name_strip_path@@YAPBDPBD@Z");
	// char const *name;
	// char const *result;

	#line 29 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\tag_files\\tag_files.cpp"
		if (!(name)) { display_assert("name", __FILE__, __LINE__, true); system_exit(-1); }
		#line 36 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\tag_files\\tag_files.cpp"
	char const *result = strrchr(name, '\\');
	if (result)
	{
		result++;
	}
	else
	{
		result = name;
	}

	return result;
}

char const *tag_name_get_directory(char const *tag_name) // 0x10F18C90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?tag_name_get_directory@@YAPBDPBD@Z");
	// char const *tag_name;
	// thread_local char buffer[256]; // 0x12579668
	// unsigned long position;
	// long length;

	thread_local char buffer[256];
	buffer[0] = 0;
	long length = 0;
	char const *position = strrchr(tag_name, '\\');
	if (position + 1 - tag_name < 256)
		length = position + 1 - tag_name;
	if (length > 0)
		csstrnzcpy(buffer, tag_name, length);
	return buffer;
}

char const *tag_name_get_filename_without_extension(char const *tag_name) // 0x10F18DC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?tag_name_get_filename_without_extension@@YAPBDPBD@Z");
	// char const *tag_name;
	// thread_local char buffer[256]; // 0x12579568
	// unsigned long position;
	// long length;
	// char const *filename;

	thread_local char buffer[256];
	buffer[0] = 0;
	char const *filename = tag_name_strip_path(tag_name);
	char const *position = filename + strcspn(filename, ".");
	long length = 0;
	if (position + 1 - filename < 256)
		length = position + 1 - filename;
	if (length > 0)
		csstrnzcpy(buffer, filename, length);
	return buffer;
}

/* ---------- private code */
