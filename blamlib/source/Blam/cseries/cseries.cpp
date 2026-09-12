/* ---------- headers */

#include "Blam/cseries/cseries.hpp"
#include "hades/hades.h"

#include "Blam/cseries/enums.inl"
#include "ChatCommands/ChatCommandMap.hpp"

#include <Windows.h>
#include <stdio.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void assert_handle(char const *info, char const *filepath, long line);
extern void trace_handle(char const *format, ...);
extern void display_assert(char const *reason, char const *file, __int32 line, bool halt);
extern void system_exit(__int32 code);
extern unsigned long system_milliseconds();
extern char *csstrnlwr(char *string, unsigned long size);
extern char *csstrnzcpy(char *to, char const *from, unsigned long size);
extern wchar_t *csstrtowcs(char const *in, wchar_t *out, __int32 const length);
extern char *cswcstostr(wchar_t const *in, char *out, __int32 const length);
extern void *csmemset(void *buffer, unsigned char value, unsigned long size);
extern void *csmemcpy(void *destination, void const *source, unsigned long size);
extern void *csmemmove(void *destination, void const *source, unsigned long size);

/* ---------- globals */

extern unsigned long (*const crc_new)(); // 0x112484A0
extern unsigned long (*const crc_checksum_buffer)(unsigned long, void const *, long); // 0x112484A4

/* ---------- private variables */

/* ---------- public code */

void assert_handle(char const *info, char const *filepath, long line) // 0x10EF6F30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?assert_handle@@YAXPBD0J@Z");
	// long line;

	fprintf(stderr, "assert failed: (%s) %s:%d\n", info, filepath, line);
}

void trace_handle(char const *format, ...) // 0x10EF75A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?trace_handle@@YAXPBDZZ");
	// char *va;

	va_list va;
	va_start(va, format);
	vprintf(format, va);
	va_end(va);
}

_extern void _sub_10EF7410(char const *, char const *, __int32, bool);
void display_assert(char const *reason, char const *file, __int32 line, bool halt) // 0x10EF7410
{
	mangled_x86(MANGLED_TODO, "?display_assert@@YAXPBD0H_N@Z");
	// bool halt;
	// char const *reason_message;
	// char const *halt_message;
	todo("implement");
	_sub_10EF7410(reason, file, line, halt);
}

_extern void _sub_10EF7500(__int32);
void system_exit(__int32 code) // 0x10EF7500
{
	mangled_x86(MANGLED_TODO, "?system_exit@@YAXH@Z");
	// __int32 code;
	todo("implement");
	_sub_10EF7500(code);
}

unsigned long system_milliseconds() // 0x10EF7540
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?system_milliseconds@@YAKXZ");
	// procedure flags: nofpo
	// function call : unsigned long (*)()

	return ((unsigned long(__cdecl *const)())0x4ec110)();
}

_extern char *_sub_10EF70C0(char *, unsigned long);
char *csstrnlwr(char *string, unsigned long size) // 0x10EF70C0
{
	mangled_x86(MANGLED_TODO, "?csstrnlwr@@YAPADPADK@Z");
	// unsigned long size;
	// unsigned long remaining;
	{
		// char *i;
	}
	todo("implement");
	char * __result = _sub_10EF70C0(string, size);
	return __result;
}

char *csstrnzcpy(char *to, char const *from, unsigned long size) // 0x10EF7170
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?csstrnzcpy@@YAPADPADPBDK@Z");
	// unsigned long size;
	// unsigned __int32 copied;

	unsigned long copied = strnlen(from, size);

	strncpy_s(to, size, from, 0xFFFFFFFF);
	if (copied >= size)
	{
		to[size - 1] = 0;
	}
	else
	{
		memset(&to[copied], 0, size - copied);
	}

	return to;
}

_extern wchar_t *_sub_10EF7230(char const *, wchar_t *, __int32 const);
wchar_t *csstrtowcs(char const *in, wchar_t *out, __int32 const length) // 0x10EF7230
{
	mangled_x86(MANGLED_TODO, "?csstrtowcs@@YAPA_WPBDPA_WH@Z");
	// __int32 const length;
	{
		// __int32 i;
	}
	todo("implement");
	wchar_t * __result = _sub_10EF7230(in, out, length);
	return __result;
}

_extern char *_sub_10EF7320(wchar_t const *, char *, __int32 const);
char *cswcstostr(wchar_t const *in, char *out, __int32 const length) // 0x10EF7320
{
	mangled_x86(MANGLED_TODO, "?cswcstostr@@YAPADPB_WPADH@Z");
	// __int32 const length;
	{
		// __int32 i;
	}
	todo("implement");
	char * __result = _sub_10EF7320(in, out, length);
	return __result;
}

void *csmemset(void *buffer, unsigned char value, unsigned long size) // 0x10EF7060
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?csmemset@@YAPAXPAXEK@Z");
	// unsigned long size;

	return memset(buffer, value, size);
}

void *csmemcpy(void *destination, void const *source, unsigned long size) // 0x10EF6FA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?csmemcpy@@YAPAXPAXPBXK@Z");
	// unsigned long size;

	return memcpy(destination, source, size);
}

void *csmemmove(void *destination, void const *source, unsigned long size) // 0x10EF7000
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?csmemmove@@YAPAXPAXPBXK@Z");
	// unsigned long size;

	return memmove(destination, source, size);
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_enum<enum e_error_message_priority,int>::c_enum(__int32 const &);
template c_enum<enum e_error_message_priority,int>::c_enum(e_error_message_priority const &);
