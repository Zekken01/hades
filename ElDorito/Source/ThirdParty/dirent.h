#ifndef __THIRDPARTY_DIRENT_H__
#define __THIRDPARTY_DIRENT_H__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

struct DIR;
struct _WDIR;
struct _wdirent;
struct dirent;

/* ---------- constants */

/* ---------- definitions */

struct _wdirent
{
	long d_ino; // 0x0
	unsigned short d_reclen; // 0x4
	unsigned __int32 d_namlen; // 0x8
	__int32 d_type; // 0xC
	wchar_t d_name[260]; // 0x10
};
static_assert(sizeof(_wdirent) == 536, "Invalid _wdirent size");
static_assert(offsetof(_wdirent, d_namlen) == 0x8, "_wdirent::d_namlen moved when its reconstructed padding was removed");

#pragma pack(push, 4)
struct _WDIR
{
	_wdirent ent; // 0x0
	_WIN32_FIND_DATAW data; // 0x218
	__int32 cached; // 0x468
	void *handle; // 0x46C
	wchar_t *patt; // 0x470
};
#pragma pack(pop)
static_assert(sizeof(_WDIR) == 1140, "Invalid _WDIR size");

#pragma pack(push, 4)
struct dirent
{
	long d_ino; // 0x0
	unsigned short d_reclen; // 0x4
	unsigned char __pad0[2]; // 0x6
	unsigned __int32 d_namlen; // 0x8
	__int32 d_type; // 0xC
	char d_name[260]; // 0x10
};
#pragma pack(pop)
static_assert(sizeof(dirent) == 276, "Invalid dirent size");

struct DIR
{
	dirent ent; // 0x0
	_WDIR *wdirp; // 0x114
};
static_assert(sizeof(DIR) == 280, "Invalid DIR size");

/* ---------- prototypes */

_WDIR *_wopendir(wchar_t const *dirname);
__int32 _wclosedir(_WDIR *dirp);
extern "C" _WIN32_FIND_DATAW *dirent_first(_WDIR *dirp);
extern "C" _WIN32_FIND_DATAW *dirent_next(_WDIR *dirp);
extern "C" DIR *opendir(char const *dirname);
extern "C" dirent *readdir(DIR *dirp);
extern "C" __int32 closedir(DIR *dirp);
extern "C" __int32 dirent_mbstowcs_s(unsigned __int32 *pReturnValue, wchar_t *wcstr, unsigned __int32 sizeInWords, char const *mbstr, unsigned __int32 count);
extern "C" __int32 dirent_wcstombs_s(unsigned __int32 *pReturnValue, char *mbstr, unsigned __int32 sizeInBytes, wchar_t const *wcstr, unsigned __int32 count);
extern "C" void dirent_set_errno(__int32 error);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

extern _WDIR *_sub_10A41FD0(wchar_t const *);
_WDIR *_wopendir(wchar_t const *dirname) // 0x10A41FD0
{
	// _wopendir
	// wchar_t const *dirname;
	// _WDIR *dirp;
	// __int32 error;
	{
		// unsigned long n;
		{
			// wchar_t *p;
		}
	}
	// function call : unsigned long (wchar_t const *, unsigned long, wchar_t *, wchar_t **)
	// function call : unsigned long (wchar_t const *, unsigned long, wchar_t *, wchar_t **)
	todo("implement");
	_WDIR * __result = _sub_10A41FD0(dirname);
	return __result;
}

_extern __int32 _sub_10A41EE0(_WDIR *);
__int32 _wclosedir(_WDIR *dirp) // 0x10A41EE0
{
	// _wclosedir
	// _WDIR *dirp;
	// __int32 ok;
	// function call : __int32 (void *)
	todo("implement");
	__int32 __result = _sub_10A41EE0(dirp);
	return __result;
}

extern _WIN32_FIND_DATAW *_sub_10A42300(_WDIR *);
extern "C" _WIN32_FIND_DATAW *dirent_first(_WDIR *dirp) // 0x10A42300
{
	// dirent_first
	// _WDIR *dirp;
	// _WIN32_FIND_DATAW *datap;
	// function call : void *(wchar_t const *, _WIN32_FIND_DATAW *)
	todo("implement");
	_WIN32_FIND_DATAW * __result = _sub_10A42300(dirp);
	return __result;
}

extern _WIN32_FIND_DATAW *_sub_10A42430(_WDIR *);
extern "C" _WIN32_FIND_DATAW *dirent_next(_WDIR *dirp) // 0x10A42430
{
	// dirent_next
	// _WDIR *dirp;
	// _WIN32_FIND_DATAW *p;
	// function call : __int32 (void *, _WIN32_FIND_DATAW *)
	// function call : __int32 (void *)
	todo("implement");
	_WIN32_FIND_DATAW * __result = _sub_10A42430(dirp);
	return __result;
}

extern DIR *_sub_10A425F0(char const *);
extern "C" DIR *opendir(char const *dirname) // 0x10A425F0
{
	// opendir
	// static ...; // 0x10A4273E
	// static ...; // 0x10A4273C
	// static ...; // 0x10A42724
	// static ...; // 0x10A4271C
	// char const *dirname;
	// DIR *dirp;
	// __int32 error;
	{
		// unsigned __int32 n;
		// wchar_t wname[260];
	}
	todo("implement");
	DIR * __result = _sub_10A425F0(dirname);
	return __result;
}

extern dirent *_sub_10A427A0(DIR *);
extern "C" dirent *readdir(DIR *dirp) // 0x10A427A0
{
	// readdir
	// static ...; // 0x10A42944
	// static ...; // 0x10A42938
	// static ...; // 0x10A42930
	// DIR *dirp;
	// dirent *entp;
	// _WIN32_FIND_DATAW *datap;
	{
		// unsigned __int32 n;
		// __int32 error;
		{
			// unsigned long attr;
		}
	}
	todo("implement");
	dirent * __result = _sub_10A427A0(dirp);
	return __result;
}

_extern __int32 _sub_10A42260(DIR *);
extern "C" __int32 closedir(DIR *dirp) // 0x10A42260
{
	// closedir
	// DIR *dirp;
	// __int32 ok;
	todo("implement");
	__int32 __result = _sub_10A42260(dirp);
	return __result;
}

_extern __int32 _sub_10A423C0(unsigned __int32 *, wchar_t *, unsigned __int32, char const *, unsigned __int32);
extern "C" __int32 dirent_mbstowcs_s(unsigned __int32 *pReturnValue, wchar_t *wcstr, unsigned __int32 sizeInWords, char const *mbstr, unsigned __int32 count) // 0x10A423C0
{
	// dirent_mbstowcs_s
	// unsigned __int32 count;
	// __int32 error;
	todo("implement");
	__int32 __result = _sub_10A423C0(pReturnValue, wcstr, sizeInWords, mbstr, count);
	return __result;
}

_extern __int32 _sub_10A42580(unsigned __int32 *, char *, unsigned __int32, wchar_t const *, unsigned __int32);
extern "C" __int32 dirent_wcstombs_s(unsigned __int32 *pReturnValue, char *mbstr, unsigned __int32 sizeInBytes, wchar_t const *wcstr, unsigned __int32 count) // 0x10A42580
{
	// dirent_wcstombs_s
	// unsigned __int32 count;
	// __int32 error;
	todo("implement");
	__int32 __result = _sub_10A42580(pReturnValue, mbstr, sizeInBytes, wcstr, count);
	return __result;
}

_extern void _sub_10A42530(__int32);
extern "C" void dirent_set_errno(__int32 error) // 0x10A42530
{
	// dirent_set_errno
	// __int32 error;
	todo("implement");
	_sub_10A42530(error);
}

#endif // __THIRDPARTY_DIRENT_H__
