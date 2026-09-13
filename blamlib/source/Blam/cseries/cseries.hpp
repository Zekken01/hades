#ifndef __BLAM_CSERIES_CSERIES_HPP__
#define __BLAM_CSERIES_CSERIES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct utf8;
union long_string;
union tag_string;

/* ---------- constants */

enum
{
	NONE = -1, // 0xFF
	k_maximum_tag_string_length = 32, // 0x0020 ' '
	k_maximum_long_string_length = 256, // 0x0100
};

/* ---------- definitions */

union tag_string
{
	char ascii[32]; // 0x0
	wchar_t unicode[16]; // 0x0
};
static_assert(sizeof(tag_string) == 32, "Invalid tag_string size");

union long_string
{
	char ascii[256]; // 0x0
	wchar_t unicode[128]; // 0x0
};
static_assert(sizeof(long_string) == 256, "Invalid long_string size");

struct utf8
{
	unsigned char octets[1]; // 0x0
};
static_assert(sizeof(utf8) == 1, "Invalid utf8 size");

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

extern _inline long count_bits(unsigned long x);

/* ---------- globals */

/* ---------- public code */

_inline long count_bits(unsigned long x) // 0x10EFC220
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?count_bits@@YAJK@Z");
	// unsigned long x;

	x = (x & 0x55555555) + ((x >> 1) & 0x55555555);
	x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
	x = (x & 0xF0F0F0F) + ((x >> 4) & 0xF0F0F0F);
	x = (x & 0xFF00FF) + ((x >> 8) & 0xFF00FF);
	x = (x & 0xFFFF) + ((x >> 16) & 0xFFFF);
	return x;
}

/* ---------- private code */

#endif // __BLAM_CSERIES_CSERIES_HPP__
