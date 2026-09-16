/* ---------- headers */

#include "Server/Connect/ServerConnectStateHandler_AcquireMods.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Threading/SimpleMessageQueue.hpp"
#include "Console/Console.hpp"
#include "Download/DownloadStatCounter.hpp"
#include "Download/HttpFileDownload.hpp"
#include "Download/IDownload.hpp"
#include "Job/JobDefinitions.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patches/CustomPackets.hpp"
#include "Server/Connect/ServerConnectDefintiions.hpp"
#include "Server/Connect/ServerConnectModDownloadUI.hpp"
#include "Server/Connect/ServerConnectStateHandler.hpp"
#include "Server/Connect/ServerConnectStateManager.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
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
#include <variant>
#include <vector>
#include "mods/mod_system.hpp"

/* ---------- forward declarations */

class CServerConnectStateHandler;
class CServerConnectStateHandler_AcquireMods;
class IServerConnectModDownloadUI;
class SignatureVerificationJob;
class c_mod_package;
class c_mod_package_manager;
struct SServerConnectState;
struct SSignatureVerificationResult;
struct begin;
struct end;
struct lambda_1;
struct lambda_2;
struct lambda_3;
struct lambda_4;
struct s_mod_origin_info;
struct s_mod_package_id;
namespace Download
{
	class CHttpFileDownload;
}

namespace Utils {}
using namespace ::Utils;
namespace Download {}
using namespace ::Download;
namespace Console {}
using namespace ::Console;
namespace Http {}
using namespace ::Http;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

// SignatureVerificationJob is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

//class CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_1>
//{
//public:
//	void operator()() const;
//	<lambda_1>(CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_1> &);
//	<lambda_1>(CServerConnectStateHandler_AcquireMods *);
//private:
//	CServerConnectStateHandler_AcquireMods *__this; // 0x0
//public:
//	CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_1> &operator=(CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_1>) == 4, "Invalid CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_1> size");

//class CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_2>
//{
//public:
//	void operator()() const;
//	<lambda_2>(CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_2> &);
//	<lambda_2>(CServerConnectStateHandler_AcquireMods *);
//private:
//	CServerConnectStateHandler_AcquireMods *__this; // 0x0
//public:
//	CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_2> &operator=(CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_2> const &);
//};
//static_assert(sizeof(CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_2>) == 4, "Invalid CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_2> size");

//class CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_3>
//{
//public:
//	void operator()() const;
//	<lambda_3>(CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_3> &);
//	<lambda_3>(CServerConnectStateHandler_AcquireMods *);
//private:
//	CServerConnectStateHandler_AcquireMods *__this; // 0x0
//public:
//	CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_3> &operator=(CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_3> const &);
//};
//static_assert(sizeof(CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_3>) == 4, "Invalid CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_3> size");

//class CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_4>
//{
//public:
//	void operator()() const;
//	<lambda_4>(CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_4> &);
//	<lambda_4>(CServerConnectStateHandler_AcquireMods *);
//private:
//	CServerConnectStateHandler_AcquireMods *__this; // 0x0
//public:
//	CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_4> &operator=(CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_4> const &);
//};
//static_assert(sizeof(CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_4>) == 4, "Invalid CServerConnectStateHandler_AcquireMods::SetUI::__l2::<lambda_4> size");

//class CServerConnectStateHandler_AcquireMods::OnExit::__l8::<lambda_1>
//{
//public:
//	<lambda_1>(CServerConnectStateHandler_AcquireMods::OnExit::__l8::<lambda_1> &);
//	<lambda_1>(CServerConnectStateHandler_AcquireMods *);
//private:
//	CServerConnectStateHandler_AcquireMods *__this; // 0x0
//public:
//	CServerConnectStateHandler_AcquireMods::OnExit::__l8::<lambda_1> &operator=(CServerConnectStateHandler_AcquireMods::OnExit::__l8::<lambda_1> const &);
//};
//static_assert(sizeof(CServerConnectStateHandler_AcquireMods::OnExit::__l8::<lambda_1>) == 4, "Invalid CServerConnectStateHandler_AcquireMods::OnExit::__l8::<lambda_1> size");

//class CServerConnectStateHandler_AcquireMods::OnUpdate::__l2::<lambda_1>
//{
//public:
//	<lambda_1>(CServerConnectStateHandler_AcquireMods::OnUpdate::__l2::<lambda_1> &);
//	<lambda_1>(CServerConnectStateHandler_AcquireMods *);
//private:
//	CServerConnectStateHandler_AcquireMods *__this; // 0x0
//public:
//	CServerConnectStateHandler_AcquireMods::OnUpdate::__l2::<lambda_1> &operator=(CServerConnectStateHandler_AcquireMods::OnUpdate::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(CServerConnectStateHandler_AcquireMods::OnUpdate::__l2::<lambda_1>) == 4, "Invalid CServerConnectStateHandler_AcquireMods::OnUpdate::__l2::<lambda_1> size");

//class CServerConnectStateHandler_AcquireMods::KickSignatureVerificationJob::__l2::<lambda_1>
//{
//public:
//	EJobResult operator()() const;
//	<lambda_1>(CServerConnectStateHandler_AcquireMods::KickSignatureVerificationJob::__l2::<lambda_1> &);
//	<lambda_1>(CServerConnectStateHandler_AcquireMods *, SignatureVerificationJob *const &);
//private:
//	CServerConnectStateHandler_AcquireMods *__this; // 0x0
//	SignatureVerificationJob *job; // 0x4
//public:
//	CServerConnectStateHandler_AcquireMods::KickSignatureVerificationJob::__l2::<lambda_1> &operator=(CServerConnectStateHandler_AcquireMods::KickSignatureVerificationJob::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(CServerConnectStateHandler_AcquireMods::KickSignatureVerificationJob::__l2::<lambda_1>) == 8, "Invalid CServerConnectStateHandler_AcquireMods::KickSignatureVerificationJob::__l2::<lambda_1> size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

CServerConnectStateHandler_AcquireMods::CServerConnectStateHandler_AcquireMods() : m_state(EState::None), m_queueIndex(-1), m_downloadStarted(false), m_cancelled(false), m_hasEnumerated(false), m_pendingVerificationJobs(0), m_ui(nullptr) /* hades-mem-init:  */ // 0x10906B70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0CServerConnectStateHandler_AcquireMods@@QAE@XZ");
	// CServerConnectStateHandler_AcquireMods *const this;
}

CServerConnectStateHandler_AcquireMods::~CServerConnectStateHandler_AcquireMods() // 0x10906E60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1CServerConnectStateHandler_AcquireMods@@QAE@XZ");
	// CServerConnectStateHandler_AcquireMods *const this;
}

_extern void _sub_10908E40(CServerConnectStateHandler_AcquireMods *const, std::shared_ptr<IServerConnectModDownloadUI> const &);
void CServerConnectStateHandler_AcquireMods::SetUI(std::shared_ptr<IServerConnectModDownloadUI> const &ui) // 0x10908E40
{
	mangled_x86(MANGLED_TODO, "?SetUI@CServerConnectStateHandler_AcquireMods@@QAEXABV?$shared_ptr@VIServerConnectModDownloadUI@@@std@@@Z");
	// std::shared_ptr<IServerConnectModDownloadUI> const &ui;
	// function call : void (std::function<void __cdecl(void)>)
	// function call : void (std::function<void __cdecl(void)>)
	// function call : void (std::function<void __cdecl(void)>)
	// function call : void (std::function<void __cdecl(void)>)
	todo("implement");
	_sub_10908E40(this, ui);
}

_extern void _sub_109084C0(CServerConnectStateHandler_AcquireMods *const);
void CServerConnectStateHandler_AcquireMods::OnEnter() // 0x109084C0
{
	mangled_x86(MANGLED_TODO, "?OnEnter@CServerConnectStateHandler_AcquireMods@@EAEXXZ");
	// CServerConnectStateHandler_AcquireMods *const this;
	// SServerConnectState &state;
	{
		// std::vector<SServerConnectState::SRequiredMod> &<range>$L0;
		// SServerConnectState::SRequiredMod *<begin>$L0;
		// SServerConnectState::SRequiredMod *<end>$L0;
		{
			// SServerConnectState::SRequiredMod &mod;
		}
	}
	// function call : void (std::vector<SServerConnectState::SRequiredMod *> const &)
	todo("implement");
	_sub_109084C0(this);
}

_extern void _sub_10908780(CServerConnectStateHandler_AcquireMods *const);
void CServerConnectStateHandler_AcquireMods::OnExit() // 0x10908780
{
	mangled_x86(MANGLED_TODO, "?OnExit@CServerConnectStateHandler_AcquireMods@@EAEXXZ");
	// static ...; // 0x10908A07
	// static ...; // 0x10908A04
	// static ...; // 0x109089EC
	// static ...; // 0x109089E4
	// CServerConnectStateHandler_AcquireMods *const this;
	{
	}
	{
		// unsigned __int32 i;
		{
			// std::filesystem::path tempPath;
			{
				// std::error_code ec;
			}
		}
	}
	// function call : void ()
	// function call : bool () const
	// function call : void ()
	todo("implement");
	_sub_10908780(this);
}

_extern void _sub_10908CF0(CServerConnectStateHandler_AcquireMods *const);
void CServerConnectStateHandler_AcquireMods::OnUpdate() // 0x10908CF0
{
	mangled_x86(MANGLED_TODO, "?OnUpdate@CServerConnectStateHandler_AcquireMods@@EAEXXZ");
	// static ...; // 0x10908DB0
// $LN8:
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// CServerConnectStateHandler_AcquireMods *const this;
	todo("implement");
	_sub_10908CF0(this);
}

void CServerConnectStateHandler_AcquireMods::UpdateConfirmation() // 0x109098B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateConfirmation@CServerConnectStateHandler_AcquireMods@@AAEXXZ");
	// CServerConnectStateHandler_AcquireMods *const this;
}

_extern void _sub_109098D0(CServerConnectStateHandler_AcquireMods *const);
void CServerConnectStateHandler_AcquireMods::UpdateDownloading() // 0x109098D0
{
	mangled_x86(MANGLED_TODO, "?UpdateDownloading@CServerConnectStateHandler_AcquireMods@@AAEXXZ");
	// CServerConnectStateHandler_AcquireMods *const this;
	{
		// long long position;
		// long long length;
		// __int32 downloadSpeed;
		{
			// SServerConnectState::SRequiredMod *currentPackage;
		}
	}
	// function call : bool () const
	// function call : long long () const
	// function call : long long () const
	// function call : __int32 () const
	// function call : void (SServerConnectState::SRequiredMod const &, __int32, long long, long long, __int32)
	todo("implement");
	_sub_109098D0(this);
}

// mangled_x86(MANGLED_DEFAULT, "??0CServerConnectStateHandler@@QAE@XZ"); no body to assert in
_inline CServerConnectStateHandler::CServerConnectStateHandler() = default; // 0x10906B40

_extern void _sub_10909760(CServerConnectStateHandler_AcquireMods *const);
void CServerConnectStateHandler_AcquireMods::UpdateCancelling() // 0x10909760
{
	mangled_x86(MANGLED_TODO, "?UpdateCancelling@CServerConnectStateHandler_AcquireMods@@AAEXXZ");
	// CServerConnectStateHandler_AcquireMods *const this;
	// c_mod_package_manager &packageManager;
	// function call : bool () const
	todo("implement");
	_sub_10909760(this);
}

_extern void _sub_10909B90(CServerConnectStateHandler_AcquireMods *const);
void CServerConnectStateHandler_AcquireMods::UpdateFinalizing() // 0x10909B90
{
	mangled_x86(MANGLED_TODO, "?UpdateFinalizing@CServerConnectStateHandler_AcquireMods@@AAEXXZ");
	// CServerConnectStateHandler_AcquireMods *const this;
	// c_mod_package_manager &packageManager;
	{
		// unsigned __int32 i;
	}
	{
		// SServerConnectState const &state;
	}
	// function call : void (SServerConnectState const &)
	todo("implement");
	_sub_10909B90(this);
}

void CServerConnectStateHandler_AcquireMods::UpdateFinished() // 0x10909D60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateFinished@CServerConnectStateHandler_AcquireMods@@AAEXXZ");
	// CServerConnectStateHandler_AcquireMods *const this;

	RequestStateChange(Connect);
}

void CServerConnectStateHandler_AcquireMods::EnterFinalizationState() // 0x109074A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?EnterFinalizationState@CServerConnectStateHandler_AcquireMods@@AAEXXZ");
	// CServerConnectStateHandler_AcquireMods *const this;
	// c_mod_package_manager &packageManager;
	// function call : void ()

	c_mod_package_manager &package_manager = c_mod_system::get_package_manager();

	SetLocalState((EState)5);
	m_ui->OnDownloadFinalizing();
}

_extern void _sub_10907340(CServerConnectStateHandler_AcquireMods *const, Download::EDownloadError);
void CServerConnectStateHandler_AcquireMods::EnterFailedState(Download::EDownloadError error) // 0x10907340
{
	mangled_x86(MANGLED_TODO, "?EnterFailedState@CServerConnectStateHandler_AcquireMods@@AAEXW4EDownloadError@Download@@@Z");
	// Download::EDownloadError error;
	// function call : void (std::string const &)
	todo("implement");
	_sub_10907340(this, error);
}

void CServerConnectStateHandler_AcquireMods::SetLocalState(CServerConnectStateHandler_AcquireMods::EState state) // 0x10908E10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetLocalState@CServerConnectStateHandler_AcquireMods@@AAEXW4EState@1@@Z");
	// CServerConnectStateHandler_AcquireMods::EState state;

	m_state = state;
}

_extern void _sub_109092A0(CServerConnectStateHandler_AcquireMods *const);
void CServerConnectStateHandler_AcquireMods::StartNextDownload() // 0x109092A0
{
	mangled_x86(MANGLED_TODO, "?StartNextDownload@CServerConnectStateHandler_AcquireMods@@AAEXXZ");
	// static ...; // 0x10909665
	// static ...; // 0x1090965C
	// static ...; // 0x10909644
	// static ...; // 0x1090963C
	// CServerConnectStateHandler_AcquireMods *const this;
	// std::shared_ptr<Download::CHttpFileDownload> download;
	// std::filesystem::path p;
	// SServerConnectState::SRequiredMod *next;
	{
		// SServerConnectState::SRequiredMod *currentPackage;
	}
	// function call : void ()
	// function call : void ()
	// function call : void (SServerConnectState::SRequiredMod const &, __int32, long long, long long, __int32)
	todo("implement");
	_sub_109092A0(this);
}

_extern void _sub_109079A0(CServerConnectStateHandler_AcquireMods *const, SSignatureVerificationResult const &);
void CServerConnectStateHandler_AcquireMods::HandleSignatureVerificationResult(SSignatureVerificationResult const &result) // 0x109079A0
{
	mangled_x86(MANGLED_TODO, "?HandleSignatureVerificationResult@CServerConnectStateHandler_AcquireMods@@AAEXABUSSignatureVerificationResult@@@Z");
	// static ...; // 0x1090808D
	// static ...; // 0x10908085
	// static ...; // 0x10908083
	// static ...; // 0x1090807F
	// static ...; // 0x10908078
	// static ...; // 0x10908030
	// static ...; // 0x10908028
	// CServerConnectStateHandler_AcquireMods *const this;
	// SSignatureVerificationResult const &result;
	// std::error_code err;
	// SServerConnectState::SRequiredMod *package;
	// std::filesystem::path p;
	// SServerConnectState const &state;
	// std::filesystem::path newPath;
	// s_mod_package_id hash;
	// s_mod_origin_info origin;
	{
		// std::string const &identifier;
		// std::error_code err;
	}
	todo("implement");
	_sub_109079A0(this, result);
}

_extern void _sub_10908260(CServerConnectStateHandler_AcquireMods *const, __int32);
void CServerConnectStateHandler_AcquireMods::KickSignatureVerificationJob(__int32 queueIndex) // 0x10908260
{
	mangled_x86(MANGLED_TODO, "?KickSignatureVerificationJob@CServerConnectStateHandler_AcquireMods@@AAEXH@Z");
	// static ...; // 0x10908434
	// static ...; // 0x1090842C
	// CServerConnectStateHandler_AcquireMods *const this;
	// __int32 queueIndex;
	// SignatureVerificationJob *job;
	todo("implement");
	_sub_10908260(this, queueIndex);
}

_extern void _sub_109075C0(CServerConnectStateHandler_AcquireMods *const);
void CServerConnectStateHandler_AcquireMods::HandleDownloadStopped() // 0x109075C0
{
	mangled_x86(MANGLED_TODO, "?HandleDownloadStopped@CServerConnectStateHandler_AcquireMods@@AAEXXZ");
	// static ...; // 0x109078D0
	// static ...; // 0x109078CC
	// static ...; // 0x109078B4
	// static ...; // 0x109078AC
	// CServerConnectStateHandler_AcquireMods *const this;
	// Download::EDownloadStatus error;
	{
		// std::error_code err;
		// std::filesystem::path p;
	}
	// function call : Download::EDownloadStatus () const
	// function call : Download::EDownloadError () const
	// function call : Download::EDownloadError () const
	todo("implement");
	_sub_109075C0(this);
}

_extern bool _sub_10909050(CServerConnectStateHandler_AcquireMods *const, SServerConnectState::SRequiredMod const &);
bool CServerConnectStateHandler_AcquireMods::ShouldDownloadPackage(SServerConnectState::SRequiredMod const &package) // 0x10909050
{
	mangled_x86(MANGLED_TODO, "?ShouldDownloadPackage@CServerConnectStateHandler_AcquireMods@@AAE_NABUSRequiredMod@SServerConnectState@@@Z");
	// static ...; // 0x1090920A
	// static ...; // 0x10909204
	// static ...; // 0x109091E0
	// static ...; // 0x109091D8
	// CServerConnectStateHandler_AcquireMods *const this;
	// SServerConnectState::SRequiredMod const &package;
	// c_mod_package_manager::s_entry package_entry;
	// unsigned char remote_hash[20];
	// c_mod_package cache;
	// c_mod_package_manager &package_manager;
	todo("implement");
	bool __result = _sub_10909050(this, package);
	return __result;
}

_extern void _sub_10908B80(CServerConnectStateHandler_AcquireMods *const);
void CServerConnectStateHandler_AcquireMods::OnUIActionConfirm() // 0x10908B80
{
	mangled_x86(MANGLED_TODO, "?OnUIActionConfirm@CServerConnectStateHandler_AcquireMods@@AAEXXZ");
	// CServerConnectStateHandler_AcquireMods *const this;
	todo("implement");
	_sub_10908B80(this);
}

void CServerConnectStateHandler_AcquireMods::OnUIActionCancel() // 0x10908AC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnUIActionCancel@CServerConnectStateHandler_AcquireMods@@AAEXXZ");
	// CServerConnectStateHandler_AcquireMods *const this;
	// c_mod_package_manager &package_manager;
	// function call : void ()

	c_mod_package_manager &package_manager = c_mod_system::get_package_manager();
	package_manager.begin_enumerate();
	m_cancelled = true;
	if (m_activeDownload)
		m_activeDownload->Cancel();
	SetLocalState(EState::Cancelled);
}

void CServerConnectStateHandler_AcquireMods::OnUIActionRetry() // 0x10908C80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnUIActionRetry@CServerConnectStateHandler_AcquireMods@@AAEXXZ");
	// CServerConnectStateHandler_AcquireMods *const this;

	if (GetLocalState() == EState::DownloadFailed)
	{
		m_downloadStarted = false;
		SetLocalState(EState::Downloading);
	}
}

void CServerConnectStateHandler_AcquireMods::OnUIActionJoinServer() // 0x10908C20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnUIActionJoinServer@CServerConnectStateHandler_AcquireMods@@AAEXXZ");
	// CServerConnectStateHandler_AcquireMods *const this;

	if (GetLocalState() == WaitingOnUser)
		SetLocalState(finished);
}

/* ---------- private code */
