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
		virtual ~IDownload() = default;  // hades: implicit - the original stores no vftable in it
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
		_inline IDownload() = default; /* compiler_generated() */
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
	// hades: IDownload::~IDownload() is defaulted in the class (0x1082CC90)
}


namespace Download
{
	inline char const *DownloadStatusToString(Download::EDownloadStatus status) // 0x108571F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?DownloadStatusToString@Download@@YAPBDW4EDownloadStatus@1@@Z");

		switch (status)
		{
		case NotStarted:
			return "NotStarted";
		case Downloading:
			return "Downloading";
		case Cancelled:
			return "Cancelled";
		case Success:
			return "Success";
		case Failed:
			return "Failed";
		}

		return "Unknown";
	}
}


namespace Download
{
	inline char const *DownloadErrorToString(Download::EDownloadError error) // 0x10716FB0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?DownloadErrorToString@Download@@YAPBDW4EDownloadError@1@@Z");

		switch (error)
		{
		case 0:
			return "None";
		case 1:
			return "Cancelled";
		case 2:
			return "NotEnoughDiskSpace";
		case 3:
			return "BadResponse";
		case 4:
			return "RequestError";
		case 5:
			return "FileError";
		case 6:
			return "NetworkError";
		}

		return "Unknown";
	}
}

/* ---------- private code */

#endif // __DOWNLOAD_IDOWNLOAD_HPP__
