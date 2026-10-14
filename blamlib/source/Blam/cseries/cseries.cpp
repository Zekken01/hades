/* ---------- headers */

#include "Blam/cseries/cseries.hpp"
#include "hades/hades.h"

#include "Blam/cseries/enums.inl"
#include "ChatCommands/ChatCommandMap.hpp"

#include "Blam/cseries/errors.hpp"  // hades: added for 0x10EF7410

#include <Windows.h>
#include <stdio.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void assert_handle(char const *info, char const *filepath, long line);
extern void trace_handle(char const *format, ...);
extern void display_assert(char const *reason, char const *file, __int32 line, bool halt);
extern __declspec(noreturn) void system_exit(__int32 code);
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

void display_assert(char const *reason, char const *file, __int32 line, bool halt) // 0x10EF7410
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?display_assert@@YAXPBD0H_N@Z");
	// bool halt;
	// char const *reason_message;
	// char const *halt_message;

	char const *reason_message = reason ? reason : "<no reason given>";
	char const *halt_message = halt ? "halt" : "warn";
	error(_error_message_priority_assert, "EXCEPTION %s in %s,#%d: %s", halt_message, file, line, reason_message);
}

__declspec(noreturn) void system_exit(__int32 code) // 0x10EF7500
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?system_exit@@YAXH@Z");
	// __int32 code;

	__asm int 3
}

unsigned long system_milliseconds() // 0x10EF7540
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?system_milliseconds@@YAKXZ");
	// procedure flags: nofpo
	// function call : unsigned long (*)()

	return ((unsigned long(__cdecl *const)())0x4ec110)();
}

char *csstrnlwr(char *string, unsigned long size) // 0x10EF70C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?csstrnlwr@@YAPADPADK@Z");
	// unsigned long size;
	// unsigned long remaining;
		// char *i;

	unsigned long count = size;
	char *s = string;

	for (; count != 0; count--)
	{
		if (!*s)
			break;

		*s = tolower(*s);
		s++;
	}

	return string;
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

wchar_t *csstrtowcs(char const *in, wchar_t *out, __int32 const length) // 0x10EF7230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?csstrtowcs@@YAPA_WPBDPA_WH@Z");
	// __int32 const length;
		// __int32 i;

	for (long i = 0; i < length; i++)
	{
		if (i == length - 1)
			out[i] = 0;
		else if (in[i] > 0x7F)
			out[i] = 0x25A1;
		else if (!(out[i] = in[i]))
			break;
	}

	return out;
}

char *cswcstostr(wchar_t const *in, char *out, __int32 const length) // 0x10EF7320
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?cswcstostr@@YAPADPB_WPADH@Z");
	// __int32 const length;
		// __int32 i;

	for (long i = 0; i < length; i++)
	{
		if (i == length - 1)
		{
			*(out + i) = 0;
		}
		else if (in[i] > 0x7F)
		{
			*(out + i) = '?';
		}
		else if (!(*(out + i) = (char)(in[i] & 0xFF)))
		{
			break;
		}
	}

	return out;
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
