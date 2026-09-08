#ifndef __DOWNLOAD_IDOWNLOAD_HPP__
#define __DOWNLOAD_IDOWNLOAD_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Audio/AudioDeviceManager.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

namespace Download
{
	class IDownload;
}

/* ---------- constants */

namespace Download
{
	enum EDownloadStatus
	{
		NotStarted = 0,
		Downloading,
		Cancelled,
		Success,
		Failed,
	};
}

/* ---------- definitions */

namespace Download
{
	class IDownload
	{
	public:
		CEventSink<> Completed; // 0x4
		virtual _inline ~IDownload();
		virtual bool IsComplete() const = 0;
		virtual Download::EDownloadStatus GetStatus() const = 0;
		virtual Download::EDownloadError GetError() const = 0;
		virtual std::string GetFilePath() const = 0;
		virtual long long GetDownloadedBytes() const = 0;
		virtual long long GetTotalBytes() const = 0;
		virtual __int32 GetDownloadSpeed() const = 0;
		virtual float GetProgress() const = 0;
		virtual void Start() = 0;
		virtual void Cancel() = 0;
		_inline IDownload(); /* compiler_generated() */
	};
	static_assert(sizeof(Download::IDownload) == 24, "Invalid Download::IDownload size");
}

/* ---------- prototypes */

namespace Download
{
	extern _inline char const *DownloadStatusToString(Download::EDownloadStatus status);
	extern _inline char const *DownloadErrorToString(Download::EDownloadError error);
}

/* ---------- globals */

/* ---------- public code */

namespace Download
{
	_extern void _sub_1082CC90(Download::IDownload *const);
	_inline IDownload::~IDownload() // 0x1082CC90
	{
		mangled_x86(MANGLED_TODO, "??1IDownload@Download@@UAE@XZ");
		// Download::IDownload *const this;
		todo("implement");
		_sub_1082CC90(this);
	}
}

extern char const *_sub_108571F0(Download::EDownloadStatus);
namespace Download
{
	_inline char const *DownloadStatusToString(Download::EDownloadStatus status) // 0x108571F0
	{
		mangled_x86(MANGLED_TODO, "?DownloadStatusToString@Download@@YAPBDW4EDownloadStatus@1@@Z");
		// static ...; // 0x1085724C
	// $LN8:
	// $LN7:
	// $LN6:
	// $LN5:
	// $LN4:
		// Download::EDownloadStatus status;
		todo("implement");
		char const * __result = _sub_108571F0(status);
		return __result;
	}
}

extern char const *_sub_10716FB0(Download::EDownloadError);
namespace Download
{
	_inline char const *DownloadErrorToString(Download::EDownloadError error) // 0x10716FB0
	{
		mangled_x86(MANGLED_TODO, "?DownloadErrorToString@Download@@YAPBDW4EDownloadError@1@@Z");
		// static ...; // 0x10717018
	// $LN10:
	// $LN9:
	// $LN8:
	// $LN7:
	// $LN6:
	// $LN5:
	// $LN4:
		// Download::EDownloadError error;
		todo("implement");
		char const * __result = _sub_10716FB0(error);
		return __result;
	}
}

/* ---------- private code */

#endif // __DOWNLOAD_IDOWNLOAD_HPP__
