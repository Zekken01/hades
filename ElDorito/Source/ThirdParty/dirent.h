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

_WDIR *_wopendir(wchar_t const *dirname) // 0x10A41FD0
{
	// _wopendir
	// wchar_t const *dirname;
	// _WDIR *dirp;
	// __int32 error;
		// unsigned long n;
			// wchar_t *p;
	// function call : unsigned long (wchar_t const *, unsigned long, wchar_t *, wchar_t **)
	// function call : unsigned long (wchar_t const *, unsigned long, wchar_t *, wchar_t **)

	_WDIR *dirp = NULL;
	__int32 error;
	if (dirname == NULL || dirname[0] == '\0')
	{
		dirent_set_errno(ENOENT);
		return NULL;
	}
	dirp = (_WDIR *)malloc(sizeof(struct _WDIR));
	if (dirp != NULL)
	{
		unsigned long n;
		dirp->handle = INVALID_HANDLE_VALUE;
		dirp->patt = NULL;
		dirp->cached = 0;
		n = GetFullPathNameW(dirname, 0, NULL, NULL);
		dirp->patt = (wchar_t *)malloc(sizeof(wchar_t) * n + 16);
		if (dirp->patt)
		{
			n = GetFullPathNameW(dirname, n, dirp->patt, NULL);
			if (n > 0)
			{
				wchar_t *p;
				p = dirp->patt + n;
				if (dirp->patt < p)
				{
					switch (p[-1])
					{
					case '\\':
					case '/':
					case ':':
						break;
					default:
						*p++ = '\\';
					}
				}
				*p++ = '*';
				*p = '\0';
				if (dirent_first(dirp))
					error = 0;
				else
				{
					error = 1;
					dirent_set_errno(ENOENT);
				}
			}
			else
			{
				dirent_set_errno(ENOENT);
				error = 1;
			}
		}
		else
			error = 1;
	}
	else
		error = 1;
	if (error && dirp)
	{
		_wclosedir(dirp);
		dirp = NULL;
	}
	return dirp;
}

__int32 _wclosedir(_WDIR *dirp) // 0x10A41EE0
{
	// _wclosedir
	// _WDIR *dirp;
	// __int32 ok;
	// function call : __int32 (void *)

	__int32 ok;
	if (dirp)
	{
		if (dirp->handle != INVALID_HANDLE_VALUE)
		{
			FindClose(dirp->handle);
			dirp->handle = INVALID_HANDLE_VALUE;
		}
		if (dirp->patt)
		{
			free(dirp->patt);
			dirp->patt = NULL;
		}
		free(dirp);
		ok = 0;
	}
	else
	{
		dirent_set_errno(EBADF);
		ok = -1;
	}
	return ok;
}

extern "C" _WIN32_FIND_DATAW *dirent_first(_WDIR *dirp) // 0x10A42300
{
	// dirent_first
	// _WDIR *dirp;
	// _WIN32_FIND_DATAW *datap;
	// function call : void *(wchar_t const *, _WIN32_FIND_DATAW *)

	_WIN32_FIND_DATAW *datap;
	dirp->handle = FindFirstFileW(dirp->patt, &dirp->data);
	if (dirp->handle != INVALID_HANDLE_VALUE)
	{
		datap = &dirp->data;
		dirp->cached = 1;
	}
	else
	{
		dirp->cached = 0;
		datap = NULL;
	}
	return datap;
}

extern "C" _WIN32_FIND_DATAW *dirent_next(_WDIR *dirp) // 0x10A42430
{
	// dirent_next
	// _WDIR *dirp;
	// _WIN32_FIND_DATAW *p;
	// function call : __int32 (void *, _WIN32_FIND_DATAW *)
	// function call : __int32 (void *)

	_WIN32_FIND_DATAW *p;
	if (dirp->cached != 0)
	{
		p = &dirp->data;
		dirp->cached = 0;
	}
	else if (dirp->handle != INVALID_HANDLE_VALUE)
	{
		if (FindNextFileW(dirp->handle, &dirp->data) != FALSE)
			p = &dirp->data;
		else
		{
			FindClose(dirp->handle);
			dirp->handle = INVALID_HANDLE_VALUE;
			p = NULL;
		}
	}
	else
	{
		p = NULL;
	}
	return p;
}

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
		// unsigned __int32 n;
		// wchar_t wname[260];

	struct DIR *dirp;
	__int32 error;
	if (dirname == NULL || dirname[0] == '\0')
	{
		dirent_set_errno(ENOENT);
		return NULL;
	}
	dirp = (DIR *)malloc(sizeof(struct DIR));
	if (dirp)
	{
		wchar_t wname[260];
		unsigned __int32 n;
		error = dirent_mbstowcs_s(&n, wname, 260, dirname, 260);
		if (!error)
		{
			dirp->wdirp = _wopendir(wname);
			if (dirp->wdirp)
				error = 0;
			else
				error = 1;
		}
		else
		{
			error = 1;
		}
	}
	else
	{
		error = 1;
	}
	if (error && dirp)
	{
		free(dirp);
		dirp = NULL;
	}
	return dirp;
}

extern "C" dirent *readdir(DIR *dirp) // 0x10A427A0
{
	// readdir
	// static ...; // 0x10A42944
	// static ...; // 0x10A42938
	// static ...; // 0x10A42930
	// DIR *dirp;
	// dirent *entp;
	// _WIN32_FIND_DATAW *datap;
		// unsigned __int32 n;
		// __int32 error;
			// unsigned long attr;

	_WIN32_FIND_DATAW *datap;
	struct dirent *entp;
	datap = dirent_next(dirp->wdirp);
	if (datap)
	{
		unsigned __int32 n;
		__int32 error;
		error = dirent_wcstombs_s(&n, dirp->ent.d_name, 260, datap->cFileName, 260);
		if (error && datap->cAlternateFileName[0] != '\0')
			error = dirent_wcstombs_s(&n, dirp->ent.d_name, 260, datap->cAlternateFileName, 260);
		if (!error)
		{
			unsigned long attr;
			entp = &dirp->ent;
			entp->d_namlen = n - 1;
			attr = datap->dwFileAttributes;
			if ((attr & FILE_ATTRIBUTE_DEVICE) != 0)
				entp->d_type = _S_IFCHR;
			else if ((attr & FILE_ATTRIBUTE_DIRECTORY) != 0)
				entp->d_type = _S_IFDIR;
			else
				entp->d_type = _S_IFREG;
			entp->d_ino = 0;
			entp->d_reclen = sizeof(struct dirent);
		}
		else
		{
			entp = &dirp->ent;
			entp->d_name[0] = '?';
			entp->d_name[1] = '\0';
			entp->d_namlen = 1;
			entp->d_type = 0;
			entp->d_ino = 0;
			entp->d_reclen = 0;
		}
	}
	else
	{
		entp = NULL;
	}
	return entp;
}

extern "C" __int32 closedir(DIR *dirp) // 0x10A42260
{
	// closedir
	// DIR *dirp;
	// __int32 ok;

	__int32 ok;
	if (dirp)
	{
		ok = _wclosedir(dirp->wdirp);
		dirp->wdirp = NULL;
		free(dirp);
	}
	else
	{
		dirent_set_errno(EBADF);
		ok = -1;
	}
	return ok;
}

extern "C" __int32 dirent_mbstowcs_s(unsigned __int32 *pReturnValue, wchar_t *wcstr, unsigned __int32 sizeInWords, char const *mbstr, unsigned __int32 count) // 0x10A423C0
{
	// dirent_mbstowcs_s
	// unsigned __int32 count;
	// __int32 error;

	__int32 error;
	error = mbstowcs_s(pReturnValue, wcstr, sizeInWords, mbstr, count);
	return error;
}

extern "C" __int32 dirent_wcstombs_s(unsigned __int32 *pReturnValue, char *mbstr, unsigned __int32 sizeInBytes, wchar_t const *wcstr, unsigned __int32 count) // 0x10A42580
{
	// dirent_wcstombs_s
	// unsigned __int32 count;
	// __int32 error;

	__int32 error;
	error = wcstombs_s(pReturnValue, mbstr, sizeInBytes, wcstr, count);
	return error;
}

extern "C" void dirent_set_errno(__int32 error) // 0x10A42530
{
	// dirent_set_errno
	// __int32 error;

	_set_errno(error);
}

#endif // __THIRDPARTY_DIRENT_H__
