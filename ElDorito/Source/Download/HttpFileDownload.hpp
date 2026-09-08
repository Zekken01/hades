#ifndef __DOWNLOAD_HTTPFILEDOWNLOAD_HPP__
#define __DOWNLOAD_HTTPFILEDOWNLOAD_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "Download/DownloadStatCounter.hpp"
#include "Download/IDownload.hpp"
#include "Forge/Magnets.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"

#include <atomic>
#include <chrono>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
namespace Download
{
	class CHttpFileDownload;
	class CHttpFileDownloadManager;
	class IDownload;
	struct CDownloadStatCounter;
}
namespace Http
{
	class CHttpHeaders;
	class IHttpRequest;
}

/* ---------- constants */

/* ---------- definitions */

namespace Download
{
	class CHttpFileDownload :
		public Download::IDownload,
		public std::enable_shared_from_this<Download::CHttpFileDownload>
	{
	public:
		public:
		enum EAbortReason
		{
			None = 0,
			Cancelled,
			NotEnoughDiskSpace,
			BadResponse,
			RequestError,
			FileError,
			NetworkError,
		};
		struct SSegment
		{
			bool started : 1; // 0x0
			bool finished : 1; // 0x0
			bool retrying : 1; // 0x0
			unsigned char __pad0[3]; // 0x1
			std::mutex lock; // 0x4
			unsigned char __pad1[4]; // 0x34
			long long const offset; // 0x38
			long long length; // 0x40
			long long downloaded; // 0x48
			Download::CDownloadStatCounter downloadRate; // 0x50
			std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000> > > startTime; // 0x60
			std::shared_ptr<Http::IHttpRequest> request; // 0x68
			__int32 retryCount; // 0x70
			unsigned char __pad2[4]; // 0x74
			std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000> > > retryAt; // 0x78
			_inline long long GetRemaining() const;
			_inline SSegment *Split();
			_inline SSegment(long long offset, long long length);
			_inline ~SSegment();
		};
		static_assert(sizeof(SSegment) == 128, "Invalid SSegment size");
		class ISegmentStore
		{
		public:
			virtual _inline ~ISegmentStore();
			virtual bool CheckAvailableSpace(long long) = 0;
			virtual bool AdviseFileSize(long long) = 0;
			virtual bool WriteData(SSegment *, char const *, unsigned __int32) = 0;
			virtual void Complete(SSegment *) = 0;
			virtual _inline void BeforeStartSegment(SSegment *segment);
			ISegmentStore(ISegmentStore const &); /* compiler_generated() */
			_inline ISegmentStore(); /* compiler_generated() */
			ISegmentStore &operator=(ISegmentStore const &); /* compiler_generated() */
		};
		static_assert(sizeof(ISegmentStore) == 4, "Invalid ISegmentStore size");
		public:
		CHttpFileDownload();
		virtual ~CHttpFileDownload();
		virtual _inline bool IsComplete() const;
		virtual _inline long long GetDownloadedBytes() const;
		virtual _inline long long GetTotalBytes() const;
		virtual _inline __int32 GetDownloadSpeed() const;
		virtual Download::EDownloadStatus GetStatus() const;
		virtual Download::EDownloadError GetError() const;
		virtual std::string GetFilePath() const;
		virtual float GetProgress() const;
		virtual void Start();
		virtual void Cancel();
		void SetUrl(std::string const &url);
		void SetDestinationFile(std::string const &filepath);
		void SetMaxConnections(__int32 num);
		void SetReceiveBufferSize(__int32 size);
		void SetMaxRetries(__int32 count);
		void Tick();
		__int32 GetElapsedSeconds() const;
		_inline __int32 GetTotalRequests() const;
	private:
		std::shared_ptr<Http::IHttpRequest> CreateSegmentRequest(SSegment *segment);
		void Abort(EAbortReason reason);
		void FinishDownload(bool success);
		void PrintDebugStats();
		void UpdateStats();
		__int32 UpdateSegments();
		void HandleFailedSegments();
		void HandleCompletedSegments();
		void CheckAndHandleSegments();
		void CheckAndStartSegment(SSegment *segment);
		void CancelAllSegmentRequests();
		void SetSupportsSegmentation(bool support);
		bool GetSupportsSegmentation();
		long long ExtractContentLengthFromResponse(__int32 statusCode, Http::CHttpHeaders const &headers);
		void OnHttpResponse(SSegment *segment, std::shared_ptr<Http::IHttpRequest> request);
		void OnHttpRequestComplete(SSegment *segment, std::shared_ptr<Http::IHttpRequest> request, bool success);
		bool OnHttpReadData(SSegment *segment, std::shared_ptr<Http::IHttpRequest> request, char const *buffer, unsigned __int32 length);
		std::string m_destinationFilePath; // 0x20
		std::string m_url; // 0x3C
		__int32 m_maxConnections; // 0x58
		__int32 m_minSegmentSize; // 0x5C
		__int32 m_maxSegmentRetryCount; // 0x60
		unsigned __int32 m_receiveBufferSize; // 0x64
		std::mutex m_mutex; // 0x68
		bool m_bStarted; // 0x98
		bool m_bFinished; // 0x99
		unsigned char __pad0[2]; // 0x9A
		std::atomic<enum EAbortReason> m_abortReason; // 0x9C
		ISegmentStore *m_segmentStore; // 0xA0
		std::vector<SSegment *,std::allocator<SSegment *> > m_segments; // 0xA4
		std::vector<SSegment *,std::allocator<SSegment *> > m_completedSegments; // 0xB4
		std::vector<SSegment *,std::allocator<SSegment *> > m_failedSegments; // 0xC4
		unsigned char __pad1[4]; // 0xD4
		std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000> > > m_lastUpdateTime; // 0xD8
		std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000> > > m_startTime; // 0xE0
		std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000> > > m_lastStatsUpdateTime; // 0xE8
		__int32 m_remainingSegmentCount; // 0xF0
		__int32 m_downloadSpeed; // 0xF4
		__int32 m_totalRequestsMade; // 0xF8
		unsigned char __pad2[4]; // 0xFC
		long long m_downloadedBytes; // 0x100
		long long m_totalBytes; // 0x108
		std::string m_etag; // 0x110
		std::string m_lastModified; // 0x12C
		std::atomic<bool> m_supportsSegmentation; // 0x148
	unsigned char __pad3[7]; // 0x149
	};
	static_assert(sizeof(Download::CHttpFileDownload) == 336, "Invalid Download::CHttpFileDownload size");

	class CHttpFileDownloadManager :
		public Utils::Singleton<Download::CHttpFileDownloadManager>
	{
	public:
		_inline void Init();
		_inline void Shutdown();
		_inline void Tick();
		_inline void AddDownload(std::shared_ptr<Download::CHttpFileDownload> download);
		_inline void RemoveDownload(std::shared_ptr<Download::CHttpFileDownload> download);
	private:
		std::vector<std::shared_ptr<Download::CHttpFileDownload>,std::allocator<std::shared_ptr<Download::CHttpFileDownload> > > m_downloads; // 0x0
	public:
		_inline CHttpFileDownloadManager(); /* compiler_generated() */
		~CHttpFileDownloadManager(); /* compiler_generated() */
	};
	static_assert(sizeof(Download::CHttpFileDownloadManager) == 16, "Invalid Download::CHttpFileDownloadManager size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Download
{
	_inline bool CHttpFileDownload::IsComplete() const // 0x108308B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?IsComplete@CHttpFileDownload@Download@@UBE_NXZ");
		// Download::CHttpFileDownload const *const this;

		return m_bFinished;
	}

	_extern long long _sub_1082FB60(Download::CHttpFileDownload const *const);
	_inline long long CHttpFileDownload::GetDownloadedBytes() const // 0x1082FB60
	{
		mangled_x86(MANGLED_TODO, "?GetDownloadedBytes@CHttpFileDownload@Download@@UBE_JXZ");
		// Download::CHttpFileDownload const *const this;
		todo("implement");
		long long __result = _sub_1082FB60((Download::CHttpFileDownload const *)this);
		return __result;
	}

	_extern long long _sub_10830370(Download::CHttpFileDownload const *const);
	_inline long long CHttpFileDownload::GetTotalBytes() const // 0x10830370
	{
		mangled_x86(MANGLED_TODO, "?GetTotalBytes@CHttpFileDownload@Download@@UBE_JXZ");
		// Download::CHttpFileDownload const *const this;
		todo("implement");
		long long __result = _sub_10830370((Download::CHttpFileDownload const *)this);
		return __result;
	}

	_inline __int32 CHttpFileDownload::GetDownloadSpeed() const // 0x1082FB30
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetDownloadSpeed@CHttpFileDownload@Download@@UBEHXZ");
		// Download::CHttpFileDownload const *const this;

		return m_downloadSpeed;
	}

	_inline __int32 CHttpFileDownload::GetTotalRequests() const // 0x10857280
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetTotalRequests@CHttpFileDownload@Download@@QBEHXZ");
		// Download::CHttpFileDownload const *const this;

		return m_totalRequestsMade;
	}

	_inline void CHttpFileDownloadManager::Init() // 0x10820420
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Init@CHttpFileDownloadManager@Download@@QAEXXZ");
		// Download::CHttpFileDownloadManager *const this;
	}

	_extern void _sub_10820580(Download::CHttpFileDownloadManager *const);
	_inline void CHttpFileDownloadManager::Shutdown() // 0x10820580
	{
		mangled_x86(MANGLED_TODO, "?Shutdown@CHttpFileDownloadManager@Download@@QAEXXZ");
		// Download::CHttpFileDownloadManager *const this;
		{
			// std::vector<std::shared_ptr<Download::CHttpFileDownload>,std::allocator<std::shared_ptr<Download::CHttpFileDownload> > > &<range>$L0;
			// std::shared_ptr<Download::CHttpFileDownload> *<begin>$L0;
			// std::shared_ptr<Download::CHttpFileDownload> *<end>$L0;
			{
				// std::shared_ptr<Download::CHttpFileDownload> &download;
			}
		}
		// function call : void ()
		todo("implement");
		_sub_10820580(this);
	}

	_extern void _sub_10820690(Download::CHttpFileDownloadManager *const);
	_inline void CHttpFileDownloadManager::Tick() // 0x10820690
	{
		mangled_x86(MANGLED_TODO, "?Tick@CHttpFileDownloadManager@Download@@QAEXXZ");
		// static ...; // 0x1082077C
		// static ...; // 0x10820770
		// static ...; // 0x10820768
		// Download::CHttpFileDownloadManager *const this;
		// std::vector<std::shared_ptr<Download::CHttpFileDownload>,std::allocator<std::shared_ptr<Download::CHttpFileDownload> > > downloads;
		{
			// std::vector<std::shared_ptr<Download::CHttpFileDownload>,std::allocator<std::shared_ptr<Download::CHttpFileDownload> > > &<range>$L0;
			// std::shared_ptr<Download::CHttpFileDownload> *<begin>$L0;
			// std::shared_ptr<Download::CHttpFileDownload> *<end>$L0;
			{
				// std::shared_ptr<Download::CHttpFileDownload> &download;
			}
		}
		todo("implement");
		_sub_10820690(this);
	}

	_extern void _sub_1082DFD0(Download::CHttpFileDownloadManager *const, std::shared_ptr<Download::CHttpFileDownload>);
	_inline void CHttpFileDownloadManager::AddDownload(std::shared_ptr<Download::CHttpFileDownload> download) // 0x1082DFD0
	{
		mangled_x86(MANGLED_TODO, "?AddDownload@CHttpFileDownloadManager@Download@@QAEXV?$shared_ptr@VCHttpFileDownload@Download@@@std@@@Z");
		// std::shared_ptr<Download::CHttpFileDownload> download;
		todo("implement");
		_sub_1082DFD0(this, download);
	}

	_extern void _sub_10831950(Download::CHttpFileDownloadManager *const, std::shared_ptr<Download::CHttpFileDownload>);
	_inline void CHttpFileDownloadManager::RemoveDownload(std::shared_ptr<Download::CHttpFileDownload> download) // 0x10831950
	{
		mangled_x86(MANGLED_TODO, "?RemoveDownload@CHttpFileDownloadManager@Download@@QAEXV?$shared_ptr@VCHttpFileDownload@Download@@@std@@@Z");
		// static ...; // 0x10831AF0
		// static ...; // 0x10831AE8
		// Download::CHttpFileDownloadManager *const this;
		// std::shared_ptr<Download::CHttpFileDownload> download;
		{
			// std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::shared_ptr<Download::CHttpFileDownload> > > > it;
		}
		todo("implement");
		_sub_10831950(this, download);
	}
}

/* ---------- private code */

#endif // __DOWNLOAD_HTTPFILEDOWNLOAD_HPP__
