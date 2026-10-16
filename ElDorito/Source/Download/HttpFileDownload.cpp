/* ---------- headers */

#include "Download/HttpFileDownload.hpp"
#include "hades/hades.h"

#include "Audio/AudioDeviceManager.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "Common/Http/HttpUtil.hpp"
#include "Console/Console.hpp"
#include "Download/DownloadStatCounter.hpp"
#include "Download/IDownload.hpp"
#include "Modules/ModuleDownload.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Utils/EventSink.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <functional>
#include <ios>
#include <iosfwd>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
namespace Download
{
	class CHttpFileDownload;
	class CSparseFileSegmentStore;
	class IDownload;
	struct CDownloadStatCounter;
}
namespace Http
{
	class CHttpHeaders;
	class IHttpRequest;
	class IHttpResponse;
	struct SContentRangeHeader;
}
namespace Modules
{
	class ModuleDownload;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Download {}
using namespace ::Download;
namespace Console {}
using namespace ::Console;
namespace Http {}
using namespace ::Http;

/* ---------- constants */

/* ---------- definitions */

namespace Download
{
	// hades: moved from hades/recovered_types.h onto its real base (was hades::polymorphic_bytes)
	struct CSparseFileSegmentStore :
		public Download::CHttpFileDownload::ISegmentStore
	{
		virtual ~CSparseFileSegmentStore();
		virtual bool CheckAvailableSpace(long long);
		virtual bool AdviseFileSize(long long);
		virtual bool WriteData(Download::CHttpFileDownload::SSegment *, char const *, unsigned __int32);
		virtual void Complete(Download::CHttpFileDownload::SSegment *);
		virtual void BeforeStartSegment(Download::CHttpFileDownload::SSegment *);
		std::string m_filename; // 0x4
		std::mutex m_mutex; // 0x20
		std::unordered_map<Download::CHttpFileDownload::SSegment *,void *> m_streams; // 0x50
	public:
		CSparseFileSegmentStore(std::string const &);
		void *GetOrCreateSegmentStream(Download::CHttpFileDownload::SSegment *, bool);
	private:
		void * OpenFile(bool);
		void SeekFile(void *, __int64);
	public:
		CSparseFileSegmentStore();
	};
	static_assert32(sizeof(CSparseFileSegmentStore) == 120, "Invalid CSparseFileSegmentStore size");
}

// Download::CSparseFileSegmentStore is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

namespace Http { extern std::shared_ptr<Http::IHttpRequest> CreateRequest(); }  // hades: added for 0x1082EC80  // hades: added for 0x1082EC80

/* ---------- globals */

namespace Download
{
	// hades: a `static` template in the original (`Download::DebugTrace<...>` carries
	// no decoration in the PDB); one body, one instantiation per argument pack.
	template <typename ...Args>
	static void DebugTrace(char const *format, Args &&...args)
	{
		if (!Modules::ModuleDownload::Instance().VarDebugTrace->ValueInt)
			return;

		char buffer[8192];
		int len = sprintf_s(buffer, "HttpFileDownload :: ");
		sprintf_s(buffer + len, sizeof(buffer) - len, format, std::forward<Args>(args)...);

		static std::mutex mutex;
		std::scoped_lock lock(mutex);
		Console::WriteLine(buffer);
	}
}

namespace Utils
{
	Modules::ModuleDownload *Utils::Singleton<Modules::ModuleDownload>::m_instance; // 0x116F47F8
}

/* ---------- private variables */

/* ---------- public code */

namespace Download
{
	// mangled_x86(MANGLED_DEFAULT, "??0CDownloadStatCounter@Download@@QAE@XZ"); no body to assert in
	_inline CDownloadStatCounter::CDownloadStatCounter() noexcept // 0x1082B520
	{
		m_totalCounter = 0;
		m_counter = 0;
		m_average = 0;
	}

	_inline long long CHttpFileDownload::SSegment::GetRemaining() const // 0x10830210
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetRemaining@SSegment@CHttpFileDownload@Download@@QBE_JXZ");

		return length - downloaded;
	}

	_inline Download::CHttpFileDownload::SSegment *CHttpFileDownload::SSegment::Split() // 0x10831F40
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Split@SSegment@CHttpFileDownload@Download@@QAEPAU123@XZ");

		long long remaining = GetRemaining();
		long long s2Offset = offset + length - remaining / 2;
		long long s2Length = remaining / 2;
		length -= s2Length;
		return new SSegment(s2Offset, s2Length);
	}

	_inline CHttpFileDownload::SSegment::SSegment(long long offset, long long length) : offset(offset), length(length) /* hades-mem-init: : offset(offset) */ // 0x1082BB40
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0SSegment@CHttpFileDownload@Download@@QAE@_J0@Z");
	}

	_inline CHttpFileDownload::SSegment::~SSegment() // 0x1082CDA0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??1SSegment@CHttpFileDownload@Download@@QAE@XZ");
	}

}

// mangled_x86(MANGLED_DEFAULT, "??1SCallbackEntry@?$CEventSink@$$V@@QAE@XZ"); no body to assert in
// _inline CEventSink<>::SCallbackEntry::~SCallbackEntry() = default; // 0x1082CD00  // hades: implicit (SCallbackEntry is an aggregate)

namespace Http
{
	// mangled_x86(MANGLED_DEFAULT, "??1SContentRangeHeader@Http@@QAE@XZ"); no body to assert in
	_inline SContentRangeHeader::~SContentRangeHeader() = default; // 0x1082CD50
}

namespace Download
{
	_inline void CHttpFileDownload::ISegmentStore::BeforeStartSegment(Download::CHttpFileDownload::SSegment *segment) // 0x1082E2B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?BeforeStartSegment@ISegmentStore@CHttpFileDownload@Download@@UAEXPAUSSegment@23@@Z");
	}

	_inline CSparseFileSegmentStore::CSparseFileSegmentStore(std::string const &filename) : m_filename(std::filesystem::absolute(filename).string()) /* hades-mem-init:  */ // 0x1082B8C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0CSparseFileSegmentStore@Download@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

		void *hFile = OpenFile(true);
		CloseHandle(hFile);
	}

	// mangled_x86(MANGLED_DEFAULT, "??0IDownload@Download@@QAE@XZ"); no body to assert in

	// mangled_x86(MANGLED_DEFAULT, "??0ISegmentStore@CHttpFileDownload@Download@@QAE@XZ"); no body to assert in
}

namespace Http
{
	// mangled_x86(MANGLED_DEFAULT, "??0SContentRangeHeader@Http@@QAE@XZ"); no body to assert in
}

namespace Download
{
	_inline CSparseFileSegmentStore::~CSparseFileSegmentStore() // 0x1082CA90
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??1CSparseFileSegmentStore@Download@@UAE@XZ");

		std::scoped_lock<std::mutex> lock(m_mutex);
		for (auto it = m_streams.cbegin(); it != m_streams.cend(); ++it)
			CloseHandle(it->second);
	}

#line 269
	_inline bool CSparseFileSegmentStore::CheckAvailableSpace(long long size) // 0x1082E880
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?CheckAvailableSpace@CSparseFileSegmentStore@Download@@UAE_N_J@Z");
		// static ...; // 0x1082EA78
		// static ...; // 0x1082EA60
		// static ...; // 0x1082EA58
		// Download::CSparseFileSegmentStore *const this;
		// long long size;
		// std::filesystem::space_info si;
		// std::filesystem::path directory;

		(void)((!!(size >= 0)) || (_wassert(L"size >= 0", L"C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Download\\HttpFileDownload.cpp", 105), 0));  // hades: the original pushes the line as a constant, not through __LINE__Var
		if (size < 0)
			return false;
		std::filesystem::path directory = std::filesystem::path(m_filename).parent_path();
		std::filesystem::space_info si = std::filesystem::space(directory);
		return static_cast<long long>(si.available) >= size;
	}

	_inline bool CSparseFileSegmentStore::AdviseFileSize(long long size) // 0x1082E090
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?AdviseFileSize@CSparseFileSegmentStore@Download@@UAE_N_J@Z");

		void *hFile = OpenFile(false);
		DWORD dw;
		if (hFile != INVALID_HANDLE_VALUE)
		{
			DeviceIoControl(hFile, 0x900C4, nullptr, 0, nullptr, 0, &dw, nullptr);
			SeekFile(hFile, size);
			SetEndOfFile(hFile);
			CloseHandle(hFile);
		}
		return true;
	}

	_inline void *CSparseFileSegmentStore::OpenFile(bool overwrite) // 0x10831540
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?OpenFile@CSparseFileSegmentStore@Download@@AAEPAX_N@Z");

		return CreateFileA(m_filename.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, overwrite ? CREATE_ALWAYS : OPEN_ALWAYS, 0, nullptr);
	}

	_inline void CSparseFileSegmentStore::SeekFile(void *handle, long long offset) // 0x10831CC0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SeekFile@CSparseFileSegmentStore@Download@@AAEXPAX_J@Z");

		long lo = (long)offset;
		long hi = (long)((unsigned long long)offset >> 32);
		SetFilePointer(handle, lo, &hi, FILE_BEGIN);
	}

#line 338
	CHttpFileDownload::~CHttpFileDownload() // 0x1082C910
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??1CHttpFileDownload@Download@@UAE@XZ");

		#line 340 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Download\\HttpFileDownload.cpp"
			assert(m_bFinished);
			#line 345 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Download\\HttpFileDownload.cpp"
		delete m_segmentStore;
	}

	CHttpFileDownload::CHttpFileDownload() : m_maxConnections(1), m_minSegmentSize(2 * 1024 * 1024), m_maxSegmentRetryCount(5), m_receiveBufferSize(16 * 1024), m_bStarted(false), m_bFinished(false), m_abortReason(EAbortReason::None), m_segmentStore(nullptr), m_remainingSegmentCount(0), m_downloadSpeed(0), m_totalRequestsMade(0), m_downloadedBytes(0), m_totalBytes(0), m_supportsSegmentation(true) /* hades-mem-init:  */ // 0x1082B570
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0CHttpFileDownload@Download@@QAE@XZ");

		Modules::ModuleDownload &moduleDownload = Modules::ModuleDownload::Instance();
		m_maxConnections = moduleDownload.VarMaxHttpConnections->ValueInt;
		m_minSegmentSize = moduleDownload.VarMinHttpSegmentSize->ValueInt;
		m_maxSegmentRetryCount = moduleDownload.VarMaxHttpSegmentRetry->ValueInt;
	}
}

namespace Http
{
	// mangled_x86(MANGLED_DEFAULT, "??0CHttpHeaders@Http@@QAE@$$QAV01@@Z"); no body to assert in
	_inline CHttpHeaders::CHttpHeaders(Http::CHttpHeaders &&__that) = default; // 0x1082B850
}

namespace Download
{


	void CHttpFileDownload::SetUrl(std::string const &url) // 0x10831EE0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetUrl@CHttpFileDownload@Download@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

		m_url = url;
	}

	void CHttpFileDownload::SetDestinationFile(std::string const &filepath) // 0x10831D80
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetDestinationFile@CHttpFileDownload@Download@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

		m_destinationFilePath = filepath;
	}

	void CHttpFileDownload::SetMaxConnections(__int32 num) // 0x10831DE0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetMaxConnections@CHttpFileDownload@Download@@QAEXH@Z");

		m_maxConnections = num;
	}

	void CHttpFileDownload::SetMaxRetries(__int32 count) // 0x10831E10
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetMaxRetries@CHttpFileDownload@Download@@QAEXH@Z");

		m_maxSegmentRetryCount = count;
	}

	void CHttpFileDownload::SetReceiveBufferSize(__int32 size) // 0x10831E40
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetReceiveBufferSize@CHttpFileDownload@Download@@QAEXH@Z");

		m_receiveBufferSize = size;
	}

	void CHttpFileDownload::Start() // 0x108320C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Start@CHttpFileDownload@Download@@UAEXXZ");

		std::shared_ptr<CHttpFileDownload> self = shared_from_this();
		DebugTrace("Download started for url '%s'", m_url.c_str());
		m_bStarted = true;
		m_startTime = std::chrono::steady_clock::now();
		m_segmentStore = new CSparseFileSegmentStore(m_destinationFilePath);
		CHttpFileDownloadManager::Instance().AddDownload(self);
	}

	__int32 CHttpFileDownload::GetElapsedSeconds() const // 0x1082FB90
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetElapsedSeconds@CHttpFileDownload@Download@@QBEHXZ");

		return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - m_startTime).count();
	}

	Download::EDownloadError CHttpFileDownload::GetError() const // 0x1082FC20
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetError@CHttpFileDownload@Download@@UBE?AW4EDownloadError@2@XZ");

		switch (m_abortReason)
		{
		case None:
			return (EDownloadError)0;
		case Cancelled:
			return (EDownloadError)1;
		case NotEnoughDiskSpace:
			return (EDownloadError)2;
		case BadResponse:
			return (EDownloadError)3;
		case RequestError:
			return (EDownloadError)4;
		case FileError:
			return (EDownloadError)5;
		case NetworkError:
			return (EDownloadError)6;
		default:
			return (EDownloadError)7;
		}
	}

	Download::EDownloadStatus CHttpFileDownload::GetStatus() const // 0x10830250
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetStatus@CHttpFileDownload@Download@@UBE?AW4EDownloadStatus@2@XZ");

		if (m_abortReason == EAbortReason::Cancelled)
			return EDownloadStatus::Cancelled;
		else if (m_bFinished)
		{
			if (m_abortReason != EAbortReason::None)
				return EDownloadStatus::Failed;
			else
				return EDownloadStatus::Success;
		}
		else if (m_bStarted)
			return EDownloadStatus::Downloading;

		return EDownloadStatus::NotStarted;
	}
}


namespace Download
{
	std::string CHttpFileDownload::GetFilePath() const // 0x1082FD00
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetFilePath@CHttpFileDownload@Download@@UBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");

		return m_destinationFilePath;
	}

	float CHttpFileDownload::GetProgress() const // 0x108300D0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetProgress@CHttpFileDownload@Download@@UBEMXZ");

		return (float)(m_totalBytes <= 0 ? 0.0 : m_downloadedBytes * 1.0 / m_totalBytes);
	}

	void CHttpFileDownload::Cancel() // 0x1082E2D0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Cancel@CHttpFileDownload@Download@@UAEXXZ");

		Abort(Cancelled);
	}

	void CHttpFileDownload::OnHttpResponse(Download::CHttpFileDownload::SSegment *segment, std::shared_ptr<Http::IHttpRequest> request) // 0x10830E90
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?OnHttpResponse@CHttpFileDownload@Download@@AAEXPAUSSegment@12@V?$shared_ptr@VIHttpRequest@Http@@@std@@@Z");

		if (m_abortReason)
			return;
		std::shared_ptr<Http::IHttpResponse> response = request->GetResponse();
		__int32 responseCode = response->GetResponseCode();
		DebugTrace("Server returned status code: %d", responseCode);
		__int32 category = responseCode / 100;
		if (category == 2)
		{
			Http::CHttpHeaders const &headers = response->GetHeaders();
			if (responseCode == 206)
				DebugTrace("Content-Range: %s", headers.Get("Content-Range").c_str());
			if (segment->offset == 0 && segment->length == -1)
			{
				m_etag = headers["ETag"];
				m_lastModified = headers["Last-Modified"];
				m_totalBytes = ExtractContentLengthFromResponse(responseCode, headers);
				{
					std::scoped_lock<std::mutex> lock(segment->lock);
					segment->length = m_totalBytes;
				}
				if (m_totalBytes > 0)
				{
					if (!m_segmentStore->CheckAvailableSpace(segment->length))
					{
						Abort(NotEnoughDiskSpace);
						return;
					}
					if (!m_segmentStore->AdviseFileSize(segment->length))
					{
						Abort(FileError);
						return;
					}
				}
				SetSupportsSegmentation(responseCode == 206 && m_totalBytes > 0);
			}
		}
		else
		{
			DebugTrace("Server returned bad response code");
			request->Cancel();
		}
	}

	void CHttpFileDownload::OnHttpRequestComplete(Download::CHttpFileDownload::SSegment *segment, std::shared_ptr<Http::IHttpRequest> request, bool success) // 0x10830C70
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?OnHttpRequestComplete@CHttpFileDownload@Download@@AAEXPAUSSegment@12@V?$shared_ptr@VIHttpRequest@Http@@@std@@_N@Z");

		if (m_abortReason)
			return;
		m_segmentStore->Complete(segment);
		bool failed = false;
		if (!success && !segment->finished)
			failed = true;
		else
		{
			segment->finished = true;
			DebugTrace("Finished segment offset: %lld...", segment->offset);
		}
		std::scoped_lock<std::mutex> lock(m_mutex);
		if (failed)
			m_failedSegments.push_back(segment);
		else
			m_completedSegments.push_back(segment);
	}

	bool CHttpFileDownload::OnHttpReadData(Download::CHttpFileDownload::SSegment *segment, std::shared_ptr<Http::IHttpRequest> request, char const *buffer, unsigned __int32 length) // 0x108308E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?OnHttpReadData@CHttpFileDownload@Download@@AAE_NPAUSSegment@12@V?$shared_ptr@VIHttpRequest@Http@@@std@@PBDI@Z");

		if (m_abortReason)
			return false;
		std::unique_lock<std::mutex> segmentLock(segment->lock);
		segment->downloadRate.Add(length);
		segment->downloaded += length;
		if (length > 0)
			segment->retryCount = 0;
		if (segment->length != -1 && segment->downloaded > segment->length)
		{
			unsigned __int32 overflow = segment->downloaded - segment->length;
			if (overflow > m_receiveBufferSize)
				throw std::overflow_error("segment length overflow");
			segment->downloaded = segment->length;
			length -= overflow;
			segment->finished = true;
		}
		segmentLock.unlock();
		if (!m_segmentStore->WriteData(segment, buffer, length) && !segment->finished)
		{
			Abort(FileError);
			return false;
		}
		return !segment->finished;
	}
}


namespace Download
{
	std::shared_ptr<Http::IHttpRequest> CHttpFileDownload::CreateSegmentRequest(Download::CHttpFileDownload::SSegment *segment) // 0x1082EC80
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?CreateSegmentRequest@CHttpFileDownload@Download@@AAE?AV?$shared_ptr@VIHttpRequest@Http@@@std@@PAUSSegment@12@@Z");

		char buff[256];
		if (segment->length > 0)
			sprintf_s(buff, "bytes=%lld-%lld", segment->offset + segment->downloaded, segment->offset + segment->length - 1);
		else
			sprintf_s(buff, "bytes=%lld-", segment->offset + segment->downloaded);
		DebugTrace("Requesting range: %s", buff);
		Http::CHttpHeaders headers;
		headers.Add("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/97.0.4692.99 Safari/537.36", Http::CHttpHeaders::Coalesce);
		headers.Add("Accept", "*/*", Http::CHttpHeaders::Coalesce);
		headers.Add("Range", buff, Http::CHttpHeaders::Coalesce);
		if (segment->offset > 0 && !m_lastModified.empty())
			headers.Add("If-Unmodified-Since", m_lastModified, Http::CHttpHeaders::Coalesce);
		std::shared_ptr<Http::IHttpRequest> request = Http::CreateRequest();
		request->SetHeaders(std::move(headers));
		request->SetReceiveBufferSize(m_receiveBufferSize);
		request->SetOnResponse(std::bind_front(&CHttpFileDownload::OnHttpResponse, this, segment));
		request->SetOnCompleted(std::bind_front(&CHttpFileDownload::OnHttpRequestComplete, this, segment));
		request->SetReceiver(std::bind_front(&CHttpFileDownload::OnHttpReadData, this, segment, request));
		request->SetUrl(m_url);
		return request;
	}

	long long CHttpFileDownload::ExtractContentLengthFromResponse(__int32 statusCode, Http::CHttpHeaders const &headers) // 0x1082F4B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ExtractContentLengthFromResponse@CHttpFileDownload@Download@@AAE_JHABVCHttpHeaders@Http@@@Z");

		long long contentLength;
		if (!headers.GetInt("Content-Length", contentLength))
			contentLength = -1;
		Http::SContentRangeHeader contentRange;
		if (statusCode == 206 && Http::ParseContentRangeHeader(headers["Content-Range"], contentRange))
		{
			if (contentRange.totalSize > 0 && contentLength > 0 && contentRange.totalSize != contentLength)
				DebugTrace("Content-Range size did not match the Content-Length %lld/%lld", contentRange.totalSize, contentLength);
			if (contentRange.totalSize != -1 && contentRange.totalSize > contentLength)
				contentLength = contentRange.totalSize;
		}
		return contentLength;
	}

	void CHttpFileDownload::SetSupportsSegmentation(bool support) // 0x10831E70
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetSupportsSegmentation@CHttpFileDownload@Download@@AAEX_N@Z");

		m_supportsSegmentation.store(support);
	}

	bool CHttpFileDownload::GetSupportsSegmentation() // 0x10830310
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetSupportsSegmentation@CHttpFileDownload@Download@@AAE_NXZ");

		return m_supportsSegmentation.load();
	}

	void CHttpFileDownload::Abort(Download::CHttpFileDownload::EAbortReason reason) // 0x1082DDF0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Abort@CHttpFileDownload@Download@@AAEXW4EAbortReason@12@@Z");

		EAbortReason exp = None;
		if (m_abortReason.compare_exchange_strong(exp, reason))
		{
			DebugTrace("Aborting... code: %d", reason);
		}
	}

	void CHttpFileDownload::CancelAllSegmentRequests() // 0x1082E320
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?CancelAllSegmentRequests@CHttpFileDownload@Download@@AAEXXZ");

		for (auto segment : m_segments)
		{
			if (segment->request)
			{
				segment->request->Cancel();
				segment->request = nullptr;
			}
		}
	}

	void CHttpFileDownload::FinishDownload(bool success) // 0x1082F880
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?FinishDownload@CHttpFileDownload@Download@@AAEX_N@Z");

		DebugTrace("Finishing download...");
		if (!success)
		{
			DebugTrace("Cancelling pending requests...");
			CancelAllSegmentRequests();
		}
		UpdateStats();
		std::vector<SSegment *> segments = std::move(m_segments);
		for (auto segment : segments)
			delete segment;
		delete m_segmentStore;
		m_segmentStore = nullptr;
		CHttpFileDownloadManager::Instance().RemoveDownload(shared_from_this());
		m_bFinished = true;
		DebugTrace("Finished.");
		Completed.PostEvent();
		Completed.Reset();
	}

	void CHttpFileDownload::HandleFailedSegments() // 0x108304F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?HandleFailedSegments@CHttpFileDownload@Download@@AAEXXZ");

		using namespace std::chrono_literals;
		std::vector<SSegment *> failed = std::move(m_failedSegments);
		for (auto segment : failed)
		{
			if (segment->retryCount < m_maxSegmentRetryCount)
			{
				std::scoped_lock<std::mutex> segmentLock(segment->lock);
				segment->retrying = true;
				segment->retryAt = std::chrono::steady_clock::now() + (1 << segment->retryCount) * 1s;
				segment->retryCount++;
			}
			else
			{
				segment->retrying = false;
				Abort(RequestError);
			}
		}
	}

	void CHttpFileDownload::HandleCompletedSegments() // 0x108303A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?HandleCompletedSegments@CHttpFileDownload@Download@@AAEXXZ");

		std::vector<Download::CHttpFileDownload::SSegment *> completed = std::move(m_completedSegments);
		for (auto segment : completed)
		{
			segment->request = nullptr;
			segment->finished = true;
			m_remainingSegmentCount--;
		}
	}

	void CHttpFileDownload::CheckAndHandleSegments() // 0x1082E440
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?CheckAndHandleSegments@CHttpFileDownload@Download@@AAEXXZ");

		std::scoped_lock<std::mutex> lock(m_mutex);

		HandleFailedSegments();
		HandleCompletedSegments();
	}

	void CHttpFileDownload::CheckAndStartSegment(Download::CHttpFileDownload::SSegment *segment) // 0x1082E530
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?CheckAndStartSegment@CHttpFileDownload@Download@@AAEXPAUSSegment@12@@Z");

		bool retrying = segment->retrying;
		if (!segment->started || segment->retrying && std::chrono::steady_clock::now() >= segment->retryAt)
		{
			if (retrying)
				DebugTrace("Retrying failed segment offset: %lld, attempt (%d/%d)", segment->offset, segment->retryCount, m_maxSegmentRetryCount);
			{
				std::scoped_lock<std::mutex> segmentLock(segment->lock);
				segment->retrying = false;
				segment->started = true;
				segment->startTime = std::chrono::steady_clock::now();
				segment->downloadRate.Clear();
			}
			m_segmentStore->BeforeStartSegment(segment);
			segment->request = CreateSegmentRequest(segment);
			if (!segment->request->Send())
			{
				DebugTrace("Failed to send request for segment offset: %lld...", segment->offset);
				Abort(RequestError);
			}
			else
			{
				if (!retrying)
					m_remainingSegmentCount++;
				m_totalRequestsMade++;
				DebugTrace("Started segment offset: %lld...", segment->offset);
			}
		}
	}

	__int32 CHttpFileDownload::UpdateSegments() // 0x10832560
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateSegments@CHttpFileDownload@Download@@AAEHXZ");

		SSegment *maxSegment = nullptr;
		long long maxSegmentRemaining = 0;
		long long totalDownloaded = 0;
		CheckAndHandleSegments();
		__int32 started = 0;
		__int32 finished = 0;
		for (auto segment : m_segments)
		{
			CheckAndStartSegment(segment);
			if (segment->started)
				started++;
			if (segment->finished)
				finished++;
			totalDownloaded += segment->downloaded;
			long long remaining = segment->GetRemaining();
			if (remaining > maxSegmentRemaining)
			{
				maxSegmentRemaining = remaining;
				maxSegment = segment;
			}
		}
		m_downloadedBytes = totalDownloaded;
		if (GetSupportsSegmentation() && maxSegment && started - finished < m_maxConnections)
		{
			std::scoped_lock<std::mutex> lock(maxSegment->lock);
			if (maxSegment->GetRemaining() / 2 > m_minSegmentSize)
			{
				SSegment *s2 = maxSegment->Split();
				m_segments.push_back(s2);
			}
		}
		return m_remainingSegmentCount;
	}

	void CHttpFileDownload::PrintDebugStats() // 0x10831690
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?PrintDebugStats@CHttpFileDownload@Download@@AAEXXZ");

		long long downloaded = GetDownloadedBytes();
		long long total = GetTotalBytes();
		__int32 speed = GetDownloadSpeed();
		char const *speedUnit = "KiB/s";
		float displaySpeed = speed / 1024.0f;
		if (speed >= 1024 * 1024)
		{
			speedUnit = "MiB/s";
			displaySpeed /= 1024.0f;
		}
		__int32 eta = total > 0 && speed > 0 ? (__int32)((total - downloaded) / speed) : 0;
		float progress = total <= 0 ? 0.0 : downloaded * 1.0 / total;
		DebugTrace("Downloaded %lld/%lld (%.1f%%), dl speed: %.1f %s, eta: %d (sec)", downloaded, total, progress * 100.0f, displaySpeed, speedUnit, eta);
	}

	void CHttpFileDownload::UpdateStats() // 0x108328D0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateStats@CHttpFileDownload@Download@@AAEXXZ");

		using namespace std::chrono_literals;
		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
		if (now - m_lastStatsUpdateTime < 1s)
			return;
		__int32 dt = (__int32)std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastStatsUpdateTime).count();
		m_lastStatsUpdateTime = now;
		__int32 totalRate = 0;
		long long total = 0;
		for (auto segment : m_segments)
		{
			std::scoped_lock<std::mutex> lock(segment->lock);
			segment->downloadRate.SecondTick(dt);
			if (segment->started && !segment->finished && !segment->retrying)
				totalRate += segment->downloadRate.GetRate();
			total += segment->downloaded;
		}
		m_downloadSpeed = totalRate;
		m_downloadedBytes = total;
		PrintDebugStats();
	}

	void CHttpFileDownload::Tick() // 0x108322C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@CHttpFileDownload@Download@@QAEXXZ");

		using namespace std::chrono_literals;
		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
		if (now - m_lastUpdateTime < 100ms)
			return;
		m_lastUpdateTime = now;
		if (!m_segments.size())
			m_segments.emplace_back(new SSegment(0, -1));
		__int32 remaining = UpdateSegments();
		UpdateStats();
		if (m_abortReason)
			FinishDownload(false);
		else if (!m_bFinished && !remaining)
			FinishDownload(true);
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Modules::ModuleDownload & Utils::Singleton<Modules::ModuleDownload>::Instance();
template void CEventSink<>::PostEvent();
template void CEventSink<>::Reset();

namespace Download
{
	bool CSparseFileSegmentStore::WriteData(Download::CHttpFileDownload::SSegment *segment, char const *data, unsigned __int32 length) // 0x10832C00
	{

			if (!length)
				return true;
			void *handle = GetOrCreateSegmentStream(segment, true);
			if (handle == INVALID_HANDLE_VALUE)
				return false;
			DWORD written;
			return WriteFile(handle, data, length, &written, nullptr) && written == length;
	}

	void CSparseFileSegmentStore::Complete(Download::CHttpFileDownload::SSegment *segment) // 0x1082EB60
	{

			void *handle = GetOrCreateSegmentStream(segment, false);
			if (handle == INVALID_HANDLE_VALUE)
				return;
			DebugTrace("Flushing segment stream. offset: %lld", segment->offset);
			FlushFileBuffers(handle);
			{
				std::scoped_lock<std::mutex> lock(m_mutex);
				m_streams.erase(segment);
			}
			CloseHandle(handle);
	}

	void CSparseFileSegmentStore::BeforeStartSegment(Download::CHttpFileDownload::SSegment *segment) // 0x1082E1A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?BeforeStartSegment@CSparseFileSegmentStore@Download@@UAEXPAUSSegment@CHttpFileDownload@2@@Z");

				if (segment->downloaded > 0)
				{
					void *handle = GetOrCreateSegmentStream(segment, true);
					if (handle != INVALID_HANDLE_VALUE)
					{
						DebugTrace("Seek segment %lld + %lld -> %lld\n", segment->offset, segment->downloaded, segment->offset + segment->downloaded);
						SeekFile(handle, segment->offset + segment->downloaded);
					}
				}
	}

	void *CSparseFileSegmentStore::GetOrCreateSegmentStream(Download::CHttpFileDownload::SSegment *segment, bool create) // 0x1082FD80
	{

			std::scoped_lock<std::mutex> lock(m_mutex);
			auto it = m_streams.find(segment);
			if (it == m_streams.end())
			{
				if (!create)
					return INVALID_HANDLE_VALUE;
				DebugTrace("Opened segment stream. offset: %lld", segment->offset);
				void *stream = OpenFile(false);
				if (stream == INVALID_HANDLE_VALUE)
					return stream;
				SeekFile(stream, segment->offset);
				m_streams.insert({ segment, stream });
				return stream;
			}
			else
			{
				return it->second;
			}
	}
}

// hades: the instantiations OnHttpResponse and CreateSegmentRequest use (neither is reconstructed yet).
template void Download::DebugTrace<int &>(char const *format, int &);
template void Download::DebugTrace<char (&)[256]>(char const *format, char (&)[256]);

// hades: the original's CreateSegmentRequest passes a char[256] to DebugTrace; that
// body is not written yet, so the instantiation is requested explicitly. It sits at
// the end of the file so the functions above keep their line numbers.
template void Download::DebugTrace<char (&)[256]>(char const *format, char (&args)[256]); // 0x10823C00
