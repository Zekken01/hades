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

// Download::CSparseFileSegmentStore is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

/* ---------- globals */

namespace Utils
{
	Modules::ModuleDownload *Utils::Singleton<Modules::ModuleDownload>::m_instance; // 0x116F47F8
}

/* ---------- private variables */

/* ---------- public code */

namespace Download
{
	_inline CDownloadStatCounter::CDownloadStatCounter() // 0x1082B520
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0CDownloadStatCounter@Download@@QAE@XZ");
		// Download::CDownloadStatCounter *const this;

		compiler_generated();
	}

	_extern long long _sub_10830210(Download::CHttpFileDownload::SSegment const *const);
	_inline long long CHttpFileDownload::SSegment::GetRemaining() const // 0x10830210
	{
		mangled_x86(MANGLED_TODO, "?GetRemaining@SSegment@CHttpFileDownload@Download@@QBE_JXZ");
		// Download::CHttpFileDownload::SSegment const *const this;
		todo("implement");
		long long __result = _sub_10830210((Download::CHttpFileDownload::SSegment const *)this);
		return __result;
	}

	extern CHttpFileDownload::SSegment *_sub_10831F40(Download::CHttpFileDownload::SSegment *const);
	_inline Download::CHttpFileDownload::SSegment *CHttpFileDownload::SSegment::Split() // 0x10831F40
	{
		mangled_x86(MANGLED_TODO, "?Split@SSegment@CHttpFileDownload@Download@@QAEPAU123@XZ");
		// Download::CHttpFileDownload::SSegment *const this;
		// long long s2Length;
		// long long s2Offset;
		// long long remaining;
		todo("implement");
		Download::CHttpFileDownload::SSegment * __result = _sub_10831F40(this);
		return __result;
	}

	extern CHttpFileDownload::SSegment* _sub_1082BB40(Download::CHttpFileDownload::SSegment *const, long long, long long);
	_inline CHttpFileDownload::SSegment::SSegment(long long offset, long long length) : offset(offset) // 0x1082BB40
	{
		mangled_x86(MANGLED_TODO, "??0SSegment@CHttpFileDownload@Download@@QAE@_J0@Z");
		// long long length;
		todo("implement");
		_sub_1082BB40(this, offset, length);
	}

	_extern void _sub_1082CDA0(Download::CHttpFileDownload::SSegment *const);
	_inline CHttpFileDownload::SSegment::~SSegment() // 0x1082CDA0
	{
		mangled_x86(MANGLED_TODO, "??1SSegment@CHttpFileDownload@Download@@QAE@XZ");
		// Download::CHttpFileDownload::SSegment *const this;
		todo("implement");
		_sub_1082CDA0(this);
	}

	_inline CHttpFileDownload::ISegmentStore::~ISegmentStore() // 0x1082CCE0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??1ISegmentStore@CHttpFileDownload@Download@@UAE@XZ");
		// Download::CHttpFileDownload::ISegmentStore *const this;
	}
}

_inline CEventSink<>::SCallbackEntry::~SCallbackEntry() // 0x1082CD00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1SCallbackEntry@?$CEventSink@$$V@@QAE@XZ");
	// CEventSink<>::SCallbackEntry *const this;

	compiler_generated();
}

namespace Http
{
	_inline SContentRangeHeader::~SContentRangeHeader() // 0x1082CD50
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??1SContentRangeHeader@Http@@QAE@XZ");
		// Http::SContentRangeHeader *const this;

		compiler_generated();
	}
}

namespace Download
{
	_inline void CHttpFileDownload::ISegmentStore::BeforeStartSegment(Download::CHttpFileDownload::SSegment *segment) // 0x1082E2B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?BeforeStartSegment@ISegmentStore@CHttpFileDownload@Download@@UAEXPAUSSegment@23@@Z");
		// Download::CHttpFileDownload::SSegment *segment;
	}

	extern CSparseFileSegmentStore* _sub_1082B8C0(Download::CSparseFileSegmentStore *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
	_inline CSparseFileSegmentStore::CSparseFileSegmentStore(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &filename) // 0x1082B8C0
	{
		mangled_x86(MANGLED_TODO, "??0CSparseFileSegmentStore@Download@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &filename;
		// void *hFile;
		// function call : __int32 (void *)
		todo("implement");
		_sub_1082B8C0(this, filename);
	}

	_inline IDownload::IDownload() // 0x1082BA60
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0IDownload@Download@@QAE@XZ");
		// Download::IDownload *const this;

		compiler_generated();
	}

	_inline CHttpFileDownload::ISegmentStore::ISegmentStore() // 0x1082BAC0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ISegmentStore@CHttpFileDownload@Download@@QAE@XZ");
		// Download::CHttpFileDownload::ISegmentStore *const this;

		compiler_generated();
	}
}

namespace Http
{
	_inline SContentRangeHeader::SContentRangeHeader() // 0x1082BAF0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0SContentRangeHeader@Http@@QAE@XZ");
		// Http::SContentRangeHeader *const this;

		compiler_generated();
	}
}

namespace Download
{
	_extern void _sub_1082CA90(Download::CSparseFileSegmentStore *const);
	_inline CSparseFileSegmentStore::~CSparseFileSegmentStore() // 0x1082CA90
	{
		mangled_x86(MANGLED_TODO, "??1CSparseFileSegmentStore@Download@@UAE@XZ");
		// static ...; // 0x1082CC1F
		// static ...; // 0x1082CC1C
		// static ...; // 0x1082CC04
		// static ...; // 0x1082CBFC
		// Download::CSparseFileSegmentStore *const this;
		// std::scoped_lock<std::mutex> lock;
		{
			// std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::pair<Download::CHttpFileDownload::SSegment * const,void *> > > > it;
		}
		// function call : __int32 (void *)
		todo("implement");
		_sub_1082CA90(this);
	}

	_extern bool _sub_1082E880(Download::CSparseFileSegmentStore *const, long long);
	_inline bool CSparseFileSegmentStore::CheckAvailableSpace(long long size) // 0x1082E880
	{
		mangled_x86(MANGLED_TODO, "?CheckAvailableSpace@CSparseFileSegmentStore@Download@@UAE_N_J@Z");
		// static ...; // 0x1082EA78
		// static ...; // 0x1082EA60
		// static ...; // 0x1082EA58
		// Download::CSparseFileSegmentStore *const this;
		// long long size;
		// std::filesystem::space_info si;
		// std::filesystem::path directory;
		todo("implement");
		bool __result = _sub_1082E880(this, size);
		return __result;
	}

	_extern bool _sub_1082E090(Download::CSparseFileSegmentStore *const, long long);
	_inline bool CSparseFileSegmentStore::AdviseFileSize(long long size) // 0x1082E090
	{
		mangled_x86(MANGLED_TODO, "?AdviseFileSize@CSparseFileSegmentStore@Download@@UAE_N_J@Z");
		// static ...; // 0x1082E154
		// static ...; // 0x1082E14C
		// Download::CSparseFileSegmentStore *const this;
		// long long size;
		// unsigned long dw;
		// void *hFile;
		// function call : __int32 (void *, unsigned long, void *, unsigned long, void *, unsigned long, unsigned long *, _OVERLAPPED *)
		// function call : __int32 (void *)
		// function call : __int32 (void *)
		todo("implement");
		bool __result = _sub_1082E090(this, size);
		return __result;
	}

	_extern void *_sub_10831540(Download::CSparseFileSegmentStore *const, bool);
	_inline void *CSparseFileSegmentStore::OpenFile(bool overwrite) // 0x10831540
	{
		mangled_x86(MANGLED_TODO, "?OpenFile@CSparseFileSegmentStore@Download@@AAEPAX_N@Z");
		// bool overwrite;
		// function call : void *(char const *, unsigned long, unsigned long, _SECURITY_ATTRIBUTES *, unsigned long, unsigned long, void *)
		todo("implement");
		void * __result = _sub_10831540(this, overwrite);
		return __result;
	}

	_extern void _sub_10831CC0(Download::CSparseFileSegmentStore *const, void *, long long);
	_inline void CSparseFileSegmentStore::SeekFile(void *handle, long long offset) // 0x10831CC0
	{
		mangled_x86(MANGLED_TODO, "?SeekFile@CSparseFileSegmentStore@Download@@AAEXPAX_J@Z");
		// static ...; // 0x10831D3C
		// Download::CSparseFileSegmentStore *const this;
		// void *handle;
		// long long offset;
		// long hi;
		// long lo;
		// function call : unsigned long (void *, long, long *, unsigned long)
		todo("implement");
		_sub_10831CC0(this, handle, offset);
	}

	extern CHttpFileDownload* _sub_1082B570(Download::CHttpFileDownload *const);
	CHttpFileDownload::CHttpFileDownload() // 0x1082B570
	{
		mangled_x86(MANGLED_TODO, "??0CHttpFileDownload@Download@@QAE@XZ");
		// Download::CHttpFileDownload *const this;
		// Modules::ModuleDownload &moduleDownload;
		todo("implement");
		_sub_1082B570(this);
	}
}

namespace Http
{
	_inline CHttpHeaders::CHttpHeaders(Http::CHttpHeaders &&__that) // 0x1082B850
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0CHttpHeaders@Http@@QAE@$$QAV01@@Z");
		// Http::CHttpHeaders &__that;

		compiler_generated();
	}
}

namespace Download
{
	_extern void _sub_1082C910(Download::CHttpFileDownload *const);
	CHttpFileDownload::~CHttpFileDownload() // 0x1082C910
	{
		mangled_x86(MANGLED_TODO, "??1CHttpFileDownload@Download@@UAE@XZ");
		// Download::CHttpFileDownload *const this;
		// function call : void *(unsigned __int32)
		todo("implement");
		_sub_1082C910(this);
	}

	_extern void _sub_10831EE0(Download::CHttpFileDownload *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
	void CHttpFileDownload::SetUrl(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &url) // 0x10831EE0
	{
		mangled_x86(MANGLED_TODO, "?SetUrl@CHttpFileDownload@Download@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &url;
		todo("implement");
		_sub_10831EE0(this, url);
	}

	_extern void _sub_10831D80(Download::CHttpFileDownload *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
	void CHttpFileDownload::SetDestinationFile(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &filepath) // 0x10831D80
	{
		mangled_x86(MANGLED_TODO, "?SetDestinationFile@CHttpFileDownload@Download@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &filepath;
		todo("implement");
		_sub_10831D80(this, filepath);
	}

	_extern void _sub_10831DE0(Download::CHttpFileDownload *const, __int32);
	void CHttpFileDownload::SetMaxConnections(__int32 num) // 0x10831DE0
	{
		mangled_x86(MANGLED_TODO, "?SetMaxConnections@CHttpFileDownload@Download@@QAEXH@Z");
		// __int32 num;
		todo("implement");
		_sub_10831DE0(this, num);
	}

	_extern void _sub_10831E10(Download::CHttpFileDownload *const, __int32);
	void CHttpFileDownload::SetMaxRetries(__int32 count) // 0x10831E10
	{
		mangled_x86(MANGLED_TODO, "?SetMaxRetries@CHttpFileDownload@Download@@QAEXH@Z");
		// __int32 count;
		todo("implement");
		_sub_10831E10(this, count);
	}

	_extern void _sub_10831E40(Download::CHttpFileDownload *const, __int32);
	void CHttpFileDownload::SetReceiveBufferSize(__int32 size) // 0x10831E40
	{
		mangled_x86(MANGLED_TODO, "?SetReceiveBufferSize@CHttpFileDownload@Download@@QAEXH@Z");
		// __int32 size;
		todo("implement");
		_sub_10831E40(this, size);
	}

	_extern void _sub_108320C0(Download::CHttpFileDownload *const);
	void CHttpFileDownload::Start() // 0x108320C0
	{
		mangled_x86(MANGLED_TODO, "?Start@CHttpFileDownload@Download@@UAEXXZ");
		// static ...; // 0x10832250
		// static ...; // 0x10832244
		// static ...; // 0x1083223C
		// Download::CHttpFileDownload *const this;
		// std::shared_ptr<Download::CHttpFileDownload> self;
		todo("implement");
		_sub_108320C0(this);
	}

	_extern __int32 _sub_1082FB90(Download::CHttpFileDownload const *const);
	__int32 CHttpFileDownload::GetElapsedSeconds() const // 0x1082FB90
	{
		mangled_x86(MANGLED_TODO, "?GetElapsedSeconds@CHttpFileDownload@Download@@QBEHXZ");
		// Download::CHttpFileDownload const *const this;
		todo("implement");
		__int32 __result = _sub_1082FB90((Download::CHttpFileDownload const *)this);
		return __result;
	}

	extern EDownloadError _sub_1082FC20(Download::CHttpFileDownload const *const);
	Download::EDownloadError CHttpFileDownload::GetError() const // 0x1082FC20
	{
		mangled_x86(MANGLED_TODO, "?GetError@CHttpFileDownload@Download@@UBE?AW4EDownloadError@2@XZ");
		// static ...; // 0x1082FCB4
	// $LN10:
	// $LN9:
	// $LN8:
	// $LN7:
	// $LN6:
	// $LN5:
	// $LN4:
		// Download::CHttpFileDownload const *const this;
		todo("implement");
		Download::EDownloadError __result = _sub_1082FC20((Download::CHttpFileDownload const *)this);
		return __result;
	}

	extern EDownloadStatus _sub_10830250(Download::CHttpFileDownload const *const);
	Download::EDownloadStatus CHttpFileDownload::GetStatus() const // 0x10830250
	{
		mangled_x86(MANGLED_TODO, "?GetStatus@CHttpFileDownload@Download@@UBE?AW4EDownloadStatus@2@XZ");
		// Download::CHttpFileDownload const *const this;
		todo("implement");
		Download::EDownloadStatus __result = _sub_10830250((Download::CHttpFileDownload const *)this);
		return __result;
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_1082FD00(Download::CHttpFileDownload const *const);
namespace Download
{
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > CHttpFileDownload::GetFilePath() const // 0x1082FD00
	{
		mangled_x86(MANGLED_TODO, "?GetFilePath@CHttpFileDownload@Download@@UBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// Download::CHttpFileDownload const *const this;
		todo("implement");
		std::string __result = _sub_1082FD00((Download::CHttpFileDownload const *)this);
		return __result;
	}

	_extern float _sub_108300D0(Download::CHttpFileDownload const *const);
	float CHttpFileDownload::GetProgress() const // 0x108300D0
	{
		mangled_x86(MANGLED_TODO, "?GetProgress@CHttpFileDownload@Download@@UBEMXZ");
		// Download::CHttpFileDownload const *const this;
		todo("implement");
		float __result = _sub_108300D0((Download::CHttpFileDownload const *)this);
		return __result;
	}

	_extern void _sub_1082E2D0(Download::CHttpFileDownload *const);
	void CHttpFileDownload::Cancel() // 0x1082E2D0
	{
		mangled_x86(MANGLED_TODO, "?Cancel@CHttpFileDownload@Download@@UAEXXZ");
		// Download::CHttpFileDownload *const this;
		todo("implement");
		_sub_1082E2D0(this);
	}

	_extern void _sub_10830E90(Download::CHttpFileDownload *const, Download::CHttpFileDownload::SSegment *, std::shared_ptr<Http::IHttpRequest>);
	void CHttpFileDownload::OnHttpResponse(Download::CHttpFileDownload::SSegment *segment, std::shared_ptr<Http::IHttpRequest> request) // 0x10830E90
	{
		mangled_x86(MANGLED_TODO, "?OnHttpResponse@CHttpFileDownload@Download@@AAEXPAUSSegment@12@V?$shared_ptr@VIHttpRequest@Http@@@std@@@Z");
		// static ...; // 0x108313C8
		// static ...; // 0x108313A4
		// static ...; // 0x1083139C
		// Download::CHttpFileDownload *const this;
		// Download::CHttpFileDownload::SSegment *segment;
		// std::shared_ptr<Http::IHttpRequest> request;
		// __int32 responseCode;
		// std::shared_ptr<Http::IHttpResponse> response;
		// __int32 category;
		{
			// Http::CHttpHeaders const &headers;
			{
				// std::scoped_lock<std::mutex> lock;
			}
		}
		// function call : std::shared_ptr<Http::IHttpResponse> ()
		// function call : __int32 () const
		// function call : Http::CHttpHeaders const &() const
		// function call : bool (long long)
		// function call : bool (long long)
		// function call : void ()
		todo("implement");
		_sub_10830E90(this, segment, request);
	}

	_extern void _sub_10830C70(Download::CHttpFileDownload *const, Download::CHttpFileDownload::SSegment *, std::shared_ptr<Http::IHttpRequest>, bool);
	void CHttpFileDownload::OnHttpRequestComplete(Download::CHttpFileDownload::SSegment *segment, std::shared_ptr<Http::IHttpRequest> request, bool success) // 0x10830C70
	{
		mangled_x86(MANGLED_TODO, "?OnHttpRequestComplete@CHttpFileDownload@Download@@AAEXPAUSSegment@12@V?$shared_ptr@VIHttpRequest@Http@@@std@@_N@Z");
		// Download::CHttpFileDownload *const this;
		// Download::CHttpFileDownload::SSegment *segment;
		// std::shared_ptr<Http::IHttpRequest> request;
		// bool success;
		// std::scoped_lock<std::mutex> lock;
		// bool failed;
		// function call : void (Download::CHttpFileDownload::SSegment *)
		todo("implement");
		_sub_10830C70(this, segment, request, success);
	}

	_extern bool _sub_108308E0(Download::CHttpFileDownload *const, Download::CHttpFileDownload::SSegment *, std::shared_ptr<Http::IHttpRequest>, char const *, unsigned __int32);
	bool CHttpFileDownload::OnHttpReadData(Download::CHttpFileDownload::SSegment *segment, std::shared_ptr<Http::IHttpRequest> request, char const *buffer, unsigned __int32 length) // 0x108308E0
	{
		mangled_x86(MANGLED_TODO, "?OnHttpReadData@CHttpFileDownload@Download@@AAE_NPAUSSegment@12@V?$shared_ptr@VIHttpRequest@Http@@@std@@PBDI@Z");
		// Download::CHttpFileDownload::SSegment *segment;
		// std::shared_ptr<Http::IHttpRequest> request;
		// char const *buffer;
		// unsigned __int32 length;
		// std::unique_lock<std::mutex> segmentLock;
		{
			// unsigned __int32 overflow;
		}
		// function call : bool (Download::CHttpFileDownload::SSegment *, char const *, unsigned __int32)
		todo("implement");
		bool __result = _sub_108308E0(this, segment, request, buffer, length);
		return __result;
	}
}

extern std::shared_ptr<Http::IHttpRequest> _sub_1082EC80(Download::CHttpFileDownload *const, Download::CHttpFileDownload::SSegment *);
namespace Download
{
	std::shared_ptr<Http::IHttpRequest> CHttpFileDownload::CreateSegmentRequest(Download::CHttpFileDownload::SSegment *segment) // 0x1082EC80
	{
		mangled_x86(MANGLED_TODO, "?CreateSegmentRequest@CHttpFileDownload@Download@@AAE?AV?$shared_ptr@VIHttpRequest@Http@@@std@@PAUSSegment@12@@Z");
		// static ...; // 0x1082F2F8
		// static ...; // 0x1082F2F0
		// static ...; // 0x1082F2CC
		// static ...; // 0x1082F2C4
		// Download::CHttpFileDownload *const this;
		// Download::CHttpFileDownload::SSegment *segment;
		// Http::CHttpHeaders headers;
		// char buff[256];
		// std::shared_ptr<Http::IHttpRequest> request;
		// function call : void (Http::CHttpHeaders)
		// function call : void (unsigned __int32)
		// function call : void (std::function<void __cdecl(std::shared_ptr<Http::IHttpRequest>)> &)
		// function call : void (std::function<void __cdecl(std::shared_ptr<Http::IHttpRequest>,bool)> &)
		// function call : void (std::function<bool __cdecl(char const *,unsigned int)> &)
		// function call : void (std::string)
		todo("implement");
		std::shared_ptr<Http::IHttpRequest> __result = _sub_1082EC80(this, segment);
		return __result;
	}

	_extern long long _sub_1082F4B0(Download::CHttpFileDownload *const, __int32, Http::CHttpHeaders const &);
	long long CHttpFileDownload::ExtractContentLengthFromResponse(__int32 statusCode, Http::CHttpHeaders const &headers) // 0x1082F4B0
	{
		mangled_x86(MANGLED_TODO, "?ExtractContentLengthFromResponse@CHttpFileDownload@Download@@AAE_JHABVCHttpHeaders@Http@@@Z");
		// static ...; // 0x1082F784
		// static ...; // 0x1082F77C
		// Download::CHttpFileDownload *const this;
		// __int32 statusCode;
		// Http::CHttpHeaders const &headers;
		// long long contentLength;
		// Http::SContentRangeHeader contentRange;
		todo("implement");
		long long __result = _sub_1082F4B0(this, statusCode, headers);
		return __result;
	}

	_extern void _sub_10831E70(Download::CHttpFileDownload *const, bool);
	void CHttpFileDownload::SetSupportsSegmentation(bool support) // 0x10831E70
	{
		mangled_x86(MANGLED_TODO, "?SetSupportsSegmentation@CHttpFileDownload@Download@@AAEX_N@Z");
		// bool support;
		todo("implement");
		_sub_10831E70(this, support);
	}

	_extern bool _sub_10830310(Download::CHttpFileDownload *const);
	bool CHttpFileDownload::GetSupportsSegmentation() // 0x10830310
	{
		mangled_x86(MANGLED_TODO, "?GetSupportsSegmentation@CHttpFileDownload@Download@@AAE_NXZ");
		// Download::CHttpFileDownload *const this;
		todo("implement");
		bool __result = _sub_10830310(this);
		return __result;
	}

	_extern void _sub_1082DDF0(Download::CHttpFileDownload *const, Download::CHttpFileDownload::EAbortReason);
	void CHttpFileDownload::Abort(Download::CHttpFileDownload::EAbortReason reason) // 0x1082DDF0
	{
		mangled_x86(MANGLED_TODO, "?Abort@CHttpFileDownload@Download@@AAEXW4EAbortReason@12@@Z");
		// static ...; // 0x1082DE84
		// static ...; // 0x1082DE7C
		// Download::CHttpFileDownload *const this;
		// Download::CHttpFileDownload::EAbortReason reason;
		// Download::CHttpFileDownload::EAbortReason exp;
		todo("implement");
		_sub_1082DDF0(this, reason);
	}

	_extern void _sub_1082E320(Download::CHttpFileDownload *const);
	void CHttpFileDownload::CancelAllSegmentRequests() // 0x1082E320
	{
		mangled_x86(MANGLED_TODO, "?CancelAllSegmentRequests@CHttpFileDownload@Download@@AAEXXZ");
		// Download::CHttpFileDownload *const this;
		{
			// std::vector<Download::CHttpFileDownload::SSegment *,std::allocator<Download::CHttpFileDownload::SSegment *> > &<range>$L0;
			// Download::CHttpFileDownload::SSegment **<begin>$L0;
			// Download::CHttpFileDownload::SSegment **<end>$L0;
			{
				// Download::CHttpFileDownload::SSegment *segment;
			}
		}
		// function call : void ()
		todo("implement");
		_sub_1082E320(this);
	}

	_extern void _sub_1082F880(Download::CHttpFileDownload *const, bool);
	void CHttpFileDownload::FinishDownload(bool success) // 0x1082F880
	{
		mangled_x86(MANGLED_TODO, "?FinishDownload@CHttpFileDownload@Download@@AAEX_N@Z");
		// static ...; // 0x1082FA8C
		// static ...; // 0x1082FA84
		// Download::CHttpFileDownload *const this;
		// bool success;
		// std::vector<Download::CHttpFileDownload::SSegment *,std::allocator<Download::CHttpFileDownload::SSegment *> > segments;
		{
			// std::vector<Download::CHttpFileDownload::SSegment *,std::allocator<Download::CHttpFileDownload::SSegment *> > &<range>$L0;
			// Download::CHttpFileDownload::SSegment **<begin>$L0;
			// Download::CHttpFileDownload::SSegment **<end>$L0;
			{
				// Download::CHttpFileDownload::SSegment *segment;
			}
		}
		// function call : void *(unsigned __int32)
		todo("implement");
		_sub_1082F880(this, success);
	}

	_extern void _sub_108304F0(Download::CHttpFileDownload *const);
	void CHttpFileDownload::HandleFailedSegments() // 0x108304F0
	{
		mangled_x86(MANGLED_TODO, "?HandleFailedSegments@CHttpFileDownload@Download@@AAEXXZ");
		// static ...; // 0x108306EC
		// static ...; // 0x108306E0
		// static ...; // 0x108306C8
		// static ...; // 0x108306C0
		// Download::CHttpFileDownload *const this;
		// std::vector<Download::CHttpFileDownload::SSegment *,std::allocator<Download::CHttpFileDownload::SSegment *> > failed;
		{
			// std::vector<Download::CHttpFileDownload::SSegment *,std::allocator<Download::CHttpFileDownload::SSegment *> > &<range>$L0;
			// Download::CHttpFileDownload::SSegment **<begin>$L0;
			// Download::CHttpFileDownload::SSegment **<end>$L0;
			{
				// Download::CHttpFileDownload::SSegment *segment;
				{
					// std::scoped_lock<std::mutex> segmentLock;
				}
			}
		}
		todo("implement");
		_sub_108304F0(this);
	}

	_extern void _sub_108303A0(Download::CHttpFileDownload *const);
	void CHttpFileDownload::HandleCompletedSegments() // 0x108303A0
	{
		mangled_x86(MANGLED_TODO, "?HandleCompletedSegments@CHttpFileDownload@Download@@AAEXXZ");
		// static ...; // 0x108304A0
		// static ...; // 0x10830494
		// static ...; // 0x1083048C
		// Download::CHttpFileDownload *const this;
		// std::vector<Download::CHttpFileDownload::SSegment *,std::allocator<Download::CHttpFileDownload::SSegment *> > completed;
		{
			// std::vector<Download::CHttpFileDownload::SSegment *,std::allocator<Download::CHttpFileDownload::SSegment *> > &<range>$L0;
			// Download::CHttpFileDownload::SSegment **<begin>$L0;
			// Download::CHttpFileDownload::SSegment **<end>$L0;
			{
				// Download::CHttpFileDownload::SSegment *segment;
			}
		}
		todo("implement");
		_sub_108303A0(this);
	}

	_extern void _sub_1082E440(Download::CHttpFileDownload *const);
	void CHttpFileDownload::CheckAndHandleSegments() // 0x1082E440
	{
		mangled_x86(MANGLED_TODO, "?CheckAndHandleSegments@CHttpFileDownload@Download@@AAEXXZ");
		// static ...; // 0x1082E4F8
		// static ...; // 0x1082E4EC
		// static ...; // 0x1082E4E4
		// Download::CHttpFileDownload *const this;
		// std::scoped_lock<std::mutex> lock;
		todo("implement");
		_sub_1082E440(this);
	}

	_extern void _sub_1082E530(Download::CHttpFileDownload *const, Download::CHttpFileDownload::SSegment *);
	void CHttpFileDownload::CheckAndStartSegment(Download::CHttpFileDownload::SSegment *segment) // 0x1082E530
	{
		mangled_x86(MANGLED_TODO, "?CheckAndStartSegment@CHttpFileDownload@Download@@AAEXPAUSSegment@12@@Z");
		// static ...; // 0x1082E7BC
		// static ...; // 0x1082E7B4
		// Download::CHttpFileDownload *const this;
		// Download::CHttpFileDownload::SSegment *segment;
		// bool retrying;
		{
			// std::scoped_lock<std::mutex> segmentLock;
		}
		// function call : void (Download::CHttpFileDownload::SSegment *)
		// function call : bool ()
		todo("implement");
		_sub_1082E530(this, segment);
	}

	_extern __int32 _sub_10832560(Download::CHttpFileDownload *const);
	__int32 CHttpFileDownload::UpdateSegments() // 0x10832560
	{
		mangled_x86(MANGLED_TODO, "?UpdateSegments@CHttpFileDownload@Download@@AAEHXZ");
		// static ...; // 0x1083280F
		// static ...; // 0x1083280C
		// static ...; // 0x108327F4
		// static ...; // 0x108327EC
		// Download::CHttpFileDownload *const this;
		// long long totalDownloaded;
		// Download::CHttpFileDownload::SSegment *maxSegment;
		// __int32 finished;
		// long long maxSegmentRemaining;
		// __int32 started;
		{
			// std::vector<Download::CHttpFileDownload::SSegment *,std::allocator<Download::CHttpFileDownload::SSegment *> > &<range>$L0;
			// Download::CHttpFileDownload::SSegment **<begin>$L0;
			// Download::CHttpFileDownload::SSegment **<end>$L0;
			{
				// Download::CHttpFileDownload::SSegment *segment;
				{
					// long long remaining;
				}
			}
		}
		{
			// std::scoped_lock<std::mutex> lock;
			{
				// Download::CHttpFileDownload::SSegment *s2;
			}
		}
		todo("implement");
		__int32 __result = _sub_10832560(this);
		return __result;
	}

	_extern void _sub_10831690(Download::CHttpFileDownload *const);
	void CHttpFileDownload::PrintDebugStats() // 0x10831690
	{
		mangled_x86(MANGLED_TODO, "?PrintDebugStats@CHttpFileDownload@Download@@AAEXXZ");
		// static ...; // 0x108318B1
		// static ...; // 0x108318AB
		// static ...; // 0x108318A1
		// static ...; // 0x10831894
		// static ...; // 0x10831890
		// static ...; // 0x10831854
		// static ...; // 0x1083184C
		// Download::CHttpFileDownload *const this;
		// __int32 speed;
		// char const *speedUnit;
		// long long downloaded;
		// float progress;
		// float displaySpeed;
		// long long total;
		// __int32 eta;
		// function call : long long () const
		// function call : long long () const
		// function call : __int32 () const
		todo("implement");
		_sub_10831690(this);
	}

	_extern void _sub_108328D0(Download::CHttpFileDownload *const);
	void CHttpFileDownload::UpdateStats() // 0x108328D0
	{
		mangled_x86(MANGLED_TODO, "?UpdateStats@CHttpFileDownload@Download@@AAEXXZ");
		// static ...; // 0x10832B51
		// static ...; // 0x10832B4C
		// static ...; // 0x10832B34
		// static ...; // 0x10832B2C
		// Download::CHttpFileDownload *const this;
		// __int32 dt;
		// __int32 totalRate;
		// long long total;
		// std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000> > > now;
		{
			// std::vector<Download::CHttpFileDownload::SSegment *,std::allocator<Download::CHttpFileDownload::SSegment *> > &<range>$L0;
			// Download::CHttpFileDownload::SSegment **<begin>$L0;
			// Download::CHttpFileDownload::SSegment **<end>$L0;
			{
				// Download::CHttpFileDownload::SSegment *segment;
				{
					// std::scoped_lock<std::mutex> lock;
				}
			}
		}
		todo("implement");
		_sub_108328D0(this);
	}

	_extern void _sub_108322C0(Download::CHttpFileDownload *const);
	void CHttpFileDownload::Tick() // 0x108322C0
	{
		mangled_x86(MANGLED_TODO, "?Tick@CHttpFileDownload@Download@@QAEXXZ");
		// static ...; // 0x108324CC
		// static ...; // 0x108324C0
		// static ...; // 0x108324B8
		// Download::CHttpFileDownload *const this;
		// __int32 remaining;
		// std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<__int64,std::ratio<1,1000000000> > > now;
		todo("implement");
		_sub_108322C0(this);
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
