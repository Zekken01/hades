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

namespace Download { extern std::shared_ptr<Download::CHttpFileDownload> CreateHttpFileDownload(); }  // hades: added for 0x109092A0

#include "Utils/Logger.hpp"  // hades: added for 0x10908260
struct SJobCounter;  // hades: added for 0x10908260
namespace Job { extern void RunJob(std::function<EJobResult __cdecl(void)> function, SJobCounter *counter, __int32 priority); }  // hades: added for 0x10908260

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

void CServerConnectStateHandler_AcquireMods::SetUI(std::shared_ptr<IServerConnectModDownloadUI> const &ui) // 0x10908E40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetUI@CServerConnectStateHandler_AcquireMods@@QAEXABV?$shared_ptr@VIServerConnectModDownloadUI@@@std@@@Z");
	// std::shared_ptr<IServerConnectModDownloadUI> const &ui;
	// function call : void (std::function<void __cdecl(void)>)
	// function call : void (std::function<void __cdecl(void)>)
	// function call : void (std::function<void __cdecl(void)>)
	// function call : void (std::function<void __cdecl(void)>)

	m_ui = ui;
	if (!m_ui)
		return;
	m_ui->SetConfirmCallback([this]() { OnUIActionConfirm(); });
	m_ui->SetRetryCallback([this]() { OnUIActionRetry(); });
	m_ui->SetCancelCallback([this]() { OnUIActionCancel(); });
	m_ui->SetJoinServerCallback([this]() { OnUIActionJoinServer(); });
}

void CServerConnectStateHandler_AcquireMods::OnEnter() // 0x109084C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnEnter@CServerConnectStateHandler_AcquireMods@@EAEXXZ");
	// CServerConnectStateHandler_AcquireMods *const this;
	// SServerConnectState &state;
		// std::vector<SServerConnectState::SRequiredMod> &<range>$L0;
		// SServerConnectState::SRequiredMod *<begin>$L0;
		// SServerConnectState::SRequiredMod *<end>$L0;
			// SServerConnectState::SRequiredMod &mod;
	// function call : void (std::vector<SServerConnectState::SRequiredMod *> const &)

	Console::WriteLine("Server Connect :: Acquiring mods...");
	SetLocalState(Confirmation);
	SServerConnectState &state = GetManager()->GetStateMutable();
	SetLocalState(None);
	m_downloadQueue.clear();
	m_queueIndex = -1;
	m_downloadStarted = false;
	m_cancelled = false;
	m_hasEnumerated = false;
	m_pendingVerificationJobs = 0;
	for (auto &mod : state.requiredMods)
	{
		if (ShouldDownloadPackage(mod))
			m_downloadQueue.push_back(&mod);
	}
	if (m_downloadQueue.empty())
		RequestStateChange(Connect);
	else
	{
		SetLocalState(Confirmation);
		m_queueIndex = 0;
		if (m_ui)
		{
			m_ui->ShowConfirmation(m_downloadQueue);
			if (GetManager()->GetState().modDownloadConfirmed)
				OnUIActionConfirm();
		}
		else
			OnUIActionConfirm();
	}
}

void CServerConnectStateHandler_AcquireMods::OnExit() // 0x10908780
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnExit@CServerConnectStateHandler_AcquireMods@@EAEXXZ");
	// static ...; // 0x10908A07
	// static ...; // 0x10908A04
	// static ...; // 0x109089EC
	// static ...; // 0x109089E4
	// CServerConnectStateHandler_AcquireMods *const this;
		// unsigned __int32 i;
			// std::filesystem::path tempPath;
				// std::error_code ec;
	// function call : void ()
	// function call : bool () const
	// function call : void ()

	if (m_activeDownload)
	{
		m_activeDownload->Cancel();
		while (!m_activeDownload->IsComplete())
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		m_activeDownload = nullptr;
	}
	while (m_pendingVerificationJobs > 0)
	{
		m_verificationQueue.ConsumeAll([this](auto *result) { HandleSignatureVerificationResult(*result); });
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	m_ui->Hide();
	for (unsigned __int32 i = 0; i < m_downloadQueue.size(); i++)
	{
		std::filesystem::path tempPath = m_downloadQueue[i]->downloadPath;
		if (std::filesystem::exists(tempPath))
		{
			std::error_code ec;
			std::filesystem::remove(tempPath, ec);
		}
	}
}

void CServerConnectStateHandler_AcquireMods::OnUpdate() // 0x10908CF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnUpdate@CServerConnectStateHandler_AcquireMods@@EAEXXZ");
	// static ...; // 0x10908DB0
// $LN8:
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// CServerConnectStateHandler_AcquireMods *const this;

	m_verificationQueue.ConsumeAll([this](auto *result) { HandleSignatureVerificationResult(*result); });
	switch (GetLocalState())
	{
	case Confirmation:
		UpdateConfirmation();
		break;
	case Downloading:
		UpdateDownloading();
		break;
	case Cancelled:
		UpdateCancelling();
		break;
	case Finalizing:
		UpdateFinalizing();
		break;
	case finished:
		UpdateFinished();
		break;
	}
}

void CServerConnectStateHandler_AcquireMods::UpdateConfirmation() // 0x109098B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateConfirmation@CServerConnectStateHandler_AcquireMods@@AAEXXZ");
	// CServerConnectStateHandler_AcquireMods *const this;
}

void CServerConnectStateHandler_AcquireMods::UpdateDownloading() // 0x109098D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateDownloading@CServerConnectStateHandler_AcquireMods@@AAEXXZ");
	// CServerConnectStateHandler_AcquireMods *const this;
		// long long position;
		// long long length;
		// __int32 downloadSpeed;
			// SServerConnectState::SRequiredMod *currentPackage;
	// function call : bool () const
	// function call : long long () const
	// function call : long long () const
	// function call : __int32 () const
	// function call : void (SServerConnectState::SRequiredMod const &, __int32, long long, long long, __int32)

	if (!m_downloadStarted)
		StartNextDownload();
	else if (m_activeDownload->IsComplete())
		HandleDownloadStopped();
	if (m_queueIndex == m_downloadQueue.size())
	{
		EnterFinalizationState();
	}
	else if (m_downloadStarted)
	{
		long long position = m_activeDownload->GetDownloadedBytes();
		long long length = m_activeDownload->GetTotalBytes();
		if (!length)
			length = m_downloadQueue[m_queueIndex]->fileSize;
		__int32 downloadSpeed = m_activeDownload->GetDownloadSpeed();
		if (length > 0)
		{
			SServerConnectState::SRequiredMod *currentPackage = m_downloadQueue[m_queueIndex];
			if (m_ui)
				m_ui->OnDownloadProgress(*currentPackage, m_queueIndex, position, length, downloadSpeed);
		}
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0CServerConnectStateHandler@@QAE@XZ"); no body to assert in
// _inline CServerConnectStateHandler::CServerConnectStateHandler() = default; // 0x10906B40  // hades: defaulted on its declaration

void CServerConnectStateHandler_AcquireMods::UpdateCancelling() // 0x10909760
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateCancelling@CServerConnectStateHandler_AcquireMods@@AAEXXZ");
	// CServerConnectStateHandler_AcquireMods *const this;
	// c_mod_package_manager &packageManager;
	// function call : bool () const

	if (m_activeDownload && !m_activeDownload->IsComplete())
	{
		return;
	}

	if (m_pendingVerificationJobs > 0)
	{
		return;
	}

	c_mod_package_manager &package_manager = c_mod_system::get_package_manager();
	if (!m_hasEnumerated)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Trace, "ServerConnect: refreshing mods..");
		m_hasEnumerated = true;
		package_manager.begin_enumerate();
	}

	if (!package_manager.enumeration_in_progress())
	{
		GetManager()->Abort(static_cast<EServerConnectAbortReason>(8));
	}
}

void CServerConnectStateHandler_AcquireMods::UpdateFinalizing() // 0x10909B90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateFinalizing@CServerConnectStateHandler_AcquireMods@@AAEXXZ");
	// CServerConnectStateHandler_AcquireMods *const this;
	// c_mod_package_manager &packageManager;
		// unsigned __int32 i;
		// SServerConnectState const &state;
	// function call : void (SServerConnectState const &)

	if (m_pendingVerificationJobs > 0)
		return;
	c_mod_package_manager &packageManager = c_mod_system::get_package_manager();
	if (!m_hasEnumerated)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Trace, "ServerConnect: refreshing mods..");
		m_hasEnumerated = true;
		packageManager.begin_enumerate();
	}
	if (!packageManager.enumeration_requested_or_in_progress())
	{
		for (unsigned __int32 i = 0; i < m_downloadQueue.size(); i++)
		{
			if (m_downloadQueue[i]->verificationFailed)
			{
				Abort((EServerConnectAbortReason)6);
				return;
			}
		}
		if (m_ui)
		{
			SServerConnectState const &state = GetManager()->GetState();
			m_ui->OnDownloadFinished(state);
			SetLocalState((EState)6);
		}
	}
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

void CServerConnectStateHandler_AcquireMods::EnterFailedState(Download::EDownloadError error) // 0x10907340
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?EnterFailedState@CServerConnectStateHandler_AcquireMods@@AAEXW4EDownloadError@Download@@@Z");
	// Download::EDownloadError error;
	// function call : void (std::string const &)

	if (m_cancelled)
	{
		return;
	}

	if (GetLocalState() == DownloadFailed)
	{
		return;
	}

	if (m_ui)
	{
		m_ui->OnDownloadFailed(Download::DownloadErrorToString(error));
	}

	SetLocalState(DownloadFailed);
}

void CServerConnectStateHandler_AcquireMods::SetLocalState(CServerConnectStateHandler_AcquireMods::EState state) // 0x10908E10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetLocalState@CServerConnectStateHandler_AcquireMods@@AAEXW4EState@1@@Z");
	// CServerConnectStateHandler_AcquireMods::EState state;

	m_state = state;
}

void CServerConnectStateHandler_AcquireMods::StartNextDownload() // 0x109092A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?StartNextDownload@CServerConnectStateHandler_AcquireMods@@AAEXXZ");
	// static ...; // 0x10909665
	// static ...; // 0x1090965C
	// static ...; // 0x10909644
	// static ...; // 0x1090963C
	// CServerConnectStateHandler_AcquireMods *const this;
	// std::shared_ptr<Download::CHttpFileDownload> download;
	// std::filesystem::path p;
	// SServerConnectState::SRequiredMod *next;
		// SServerConnectState::SRequiredMod *currentPackage;
	// function call : void ()
	// function call : void ()
	// function call : void (SServerConnectState::SRequiredMod const &, __int32, long long, long long, __int32)

	if (m_queueIndex >= m_downloadQueue.size())
		return;
	SServerConnectState::SRequiredMod *next = m_downloadQueue[m_queueIndex];
	std::filesystem::path p = std::filesystem::path(c_mod_system::get_package_directory()) / next->hash;
	p.replace_extension(".tmp");
	next->downloadPath = p.string();
	std::shared_ptr<Download::CHttpFileDownload> download = Download::CreateHttpFileDownload();
	download->SetUrl(next->packageUrl);
	download->SetDestinationFile(next->downloadPath);
	download->Start();
	m_activeDownload = download;
	Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Trace, "ServerConnect: Downloading mod package '%s'", next->packageUrl.c_str());
	m_downloadStarted = true;
	if (m_ui)
	{
		m_ui->OnDownloadStart();
		SServerConnectState::SRequiredMod *currentPackage = m_downloadQueue[m_queueIndex];
		if (m_ui)
			m_ui->OnDownloadProgress(*currentPackage, m_queueIndex, 0, currentPackage->fileSize, 0);
	}
}

void CServerConnectStateHandler_AcquireMods::HandleSignatureVerificationResult(SSignatureVerificationResult const &result) // 0x109079A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleSignatureVerificationResult@CServerConnectStateHandler_AcquireMods@@AAEXABUSSignatureVerificationResult@@@Z");
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
	// std::filesystem::path newPath;
	// SServerConnectState const &state;
	// std::filesystem::path p;
	// s_mod_package_id hash;
	// s_mod_origin_info origin;
		// std::string const &identifier;
		// std::error_code err;

	if (result.queueIndex < 0 || result.queueIndex >= (__int32)m_downloadQueue.size())
	{
	#line 604 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Server\\Connect\\ServerConnectStateHandler_AcquireMods.cpp"
		assert(!"HandleSignatureVerificationResult invalid queue index");
	#line 626 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Server\\Connect\\ServerConnectStateHandler_AcquireMods.cpp"
		return;
	}
	SServerConnectState::SRequiredMod *package = m_downloadQueue[result.queueIndex];
	#line 611 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Server\\Connect\\ServerConnectStateHandler_AcquireMods.cpp"
	assert(package->downloadPath == result.tempFilePath);
	#line 632 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Server\\Connect\\ServerConnectStateHandler_AcquireMods.cpp"
	m_pendingVerificationJobs--;
	if (result.error != SSignatureVerificationResult::None || !result.verified)
	{
		package->verificationFailed = true;
		std::string const &identifier = m_downloadQueue[result.queueIndex]->localName;
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "ServerConnect: Failed to verify mod package signature '%s'", identifier.c_str());
		std::error_code err;
		std::filesystem::remove(result.tempFilePath, err);
		return;
	}
	s_mod_package_id hash(result.computedHash);
	std::filesystem::path newPath = std::filesystem::path(c_mod_system::get_package_directory()) / c_mod_system::GetNewPackageFilename(package->name, hash.to_string(), package->version);
	newPath.replace_extension(".pak");
	std::filesystem::path p = result.tempFilePath;
	std::error_code err;
	std::filesystem::rename(result.tempFilePath, newPath, err);
	if (err)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "ServerConnect: Failed to move downloaded mod package '%s' Error=%s", package->localName.c_str(), err.message());
		EnterFailedState((Download::EDownloadError)5);
		return;
	}
	s_mod_origin_info origin;
	SServerConnectState const &state = GetManager()->GetState();
	origin.server_ip = state.hostname + ":" + std::to_string(state.port);
	origin.server_host = state.serverHost;
	origin.server_name = state.serverName;
	origin.url = package->packageUrl;
	c_mod_system::get_package_manager().set_package_origin(hash, origin);
	c_mod_system::get_package_manager().set_package_signature_verified(hash, true);
}

void CServerConnectStateHandler_AcquireMods::KickSignatureVerificationJob(__int32 queueIndex) // 0x10908260
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?KickSignatureVerificationJob@CServerConnectStateHandler_AcquireMods@@AAEXH@Z");
	// static ...; // 0x10908434
	// static ...; // 0x1090842C
	// CServerConnectStateHandler_AcquireMods *const this;
	// __int32 queueIndex;
	// SignatureVerificationJob *job;

	Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Trace, "ServerConnect: Started mod package signature verification job '%s'", m_downloadQueue[queueIndex]->localName.c_str());
	m_pendingVerificationJobs++;
	m_downloadQueue[queueIndex]->verificationFailed = false;
	SignatureVerificationJob *job = new SignatureVerificationJob(queueIndex, m_downloadQueue[queueIndex]->downloadPath);
	Job::RunJob([this, job]() -> EJobResult
	{
		if (job->Update())
		{
			auto result = m_verificationQueue.TryToAllocate();
			if (result) { *result = job->GetResult(); delete job; m_verificationQueue.Add(result); return Done; }
		}

		return NotDone;
	}, nullptr, 0);
}

void CServerConnectStateHandler_AcquireMods::HandleDownloadStopped() // 0x109075C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleDownloadStopped@CServerConnectStateHandler_AcquireMods@@AAEXXZ");
	// static ...; // 0x109078D0
	// static ...; // 0x109078CC
	// static ...; // 0x109078B4
	// static ...; // 0x109078AC
	// CServerConnectStateHandler_AcquireMods *const this;
	// Download::EDownloadStatus error;
		// std::error_code err;
		// std::filesystem::path p;
	// function call : Download::EDownloadStatus () const
	// function call : Download::EDownloadError () const
	// function call : Download::EDownloadError () const

	Download::EDownloadStatus error = m_activeDownload->GetStatus();
	if (error == Download::Success)
	{
		KickSignatureVerificationJob(m_queueIndex);
		m_downloadStarted = false;
		m_queueIndex++;
	}
	else
	{
		std::filesystem::path p(m_downloadQueue[m_queueIndex]->downloadPath);
		std::error_code err;
		std::filesystem::remove(p, err);
		if (err)
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "ServerConnect: Failed to delete temp file '%S'. %s", p.c_str(), err.message().c_str());
		if (error != Download::Cancelled && !m_cancelled)
		{
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "ServerConnect: Mod download failed '%s'. %s", m_downloadQueue[m_queueIndex]->localName.c_str(), Download::DownloadErrorToString(m_activeDownload->GetError()));
			EnterFailedState(m_activeDownload->GetError());
			return;
		}
	}
}

bool CServerConnectStateHandler_AcquireMods::ShouldDownloadPackage(SServerConnectState::SRequiredMod const &package) // 0x10909050
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ShouldDownloadPackage@CServerConnectStateHandler_AcquireMods@@AAE_NABUSRequiredMod@SServerConnectState@@@Z");
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

	unsigned char remote_hash[20];
	Utils::String::HexStringToBytes(package.hash, remote_hash, sizeof(remote_hash));
	c_mod_package_manager &package_manager = c_mod_system::get_package_manager();
	c_mod_package_manager::s_entry package_entry;
	if (!package_manager.find_package_by_hash(remote_hash, &package_entry))
	{
		return true;
	}

	c_mod_package cache(package_entry.file.filename);
	if (!cache.initialize(nullptr))
	{
		return true;
	}

	cache.dispose();
	return false;
}

void CServerConnectStateHandler_AcquireMods::OnUIActionConfirm() // 0x10908B80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnUIActionConfirm@CServerConnectStateHandler_AcquireMods@@AAEXXZ");
	// CServerConnectStateHandler_AcquireMods *const this;

	#line 762 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Server\\Connect\\ServerConnectStateHandler_AcquireMods.cpp"
		assert(GetLocalState() == EState::Confirmation);
		#line 768 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Server\\Connect\\ServerConnectStateHandler_AcquireMods.cpp"
	GetManager()->GetStateMutable().modDownloadConfirmed = true;
	SetLocalState(EState::Downloading);
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
