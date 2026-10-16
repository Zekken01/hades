/* ---------- headers */

#include "Server/ModBrowser/ModBrowserStateHandler_AcquireMod.hpp"
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
#include "Forge/Magnets.hpp"
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
#include "Server/Connect/ServerConnectStateHandler_AcquireMods.hpp"
#include "Server/ModBrowser/ModBrowserDefinitions.hpp"
#include "Server/ModBrowser/ModBrowserModDownloadUI.hpp"
#include "Server/ModBrowser/ModBrowserStateHandler.hpp"
#include "Server/ModBrowser/ModBrowserStateManager.hpp"
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

class CModBrowserStateHandler;
class CModBrowserStateHandler_AcquireMod;
class IModBrowserModDownloadUI;
class SignatureVerificationJob;
class c_mod_package;
class c_mod_package_manager;
struct SModBrowserState;
struct SSignatureVerificationResult;
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

//class CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_1>
//{
//public:
//	void operator()() const;
//	<lambda_1>(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_1> &);
//	<lambda_1>(CModBrowserStateHandler_AcquireMod *);
//private:
//	CModBrowserStateHandler_AcquireMod *__this; // 0x0
//public:
//	CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_1> &operator=(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_1>) == 4, "Invalid CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_1> size");

//class CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_2>
//{
//public:
//	void operator()() const;
//	<lambda_2>(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_2> &);
//	<lambda_2>(CModBrowserStateHandler_AcquireMod *);
//private:
//	CModBrowserStateHandler_AcquireMod *__this; // 0x0
//public:
//	CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_2> &operator=(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_2> const &);
//};
//static_assert(sizeof(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_2>) == 4, "Invalid CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_2> size");

//class CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_3>
//{
//public:
//	void operator()() const;
//	<lambda_3>(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_3> &);
//	<lambda_3>(CModBrowserStateHandler_AcquireMod *);
//private:
//	CModBrowserStateHandler_AcquireMod *__this; // 0x0
//public:
//	CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_3> &operator=(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_3> const &);
//};
//static_assert(sizeof(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_3>) == 4, "Invalid CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_3> size");

//class CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_4>
//{
//public:
//	void operator()() const;
//	<lambda_4>(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_4> &);
//	<lambda_4>(CModBrowserStateHandler_AcquireMod *);
//private:
//	CModBrowserStateHandler_AcquireMod *__this; // 0x0
//public:
//	CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_4> &operator=(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_4> const &);
//};
//static_assert(sizeof(CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_4>) == 4, "Invalid CModBrowserStateHandler_AcquireMod::SetUI::__l2::<lambda_4> size");

//class CModBrowserStateHandler_AcquireMod::OnExit::__l8::<lambda_1>
//{
//public:
//	<lambda_1>(CModBrowserStateHandler_AcquireMod::OnExit::__l8::<lambda_1> &);
//	<lambda_1>(CModBrowserStateHandler_AcquireMod *);
//private:
//	CModBrowserStateHandler_AcquireMod *__this; // 0x0
//public:
//	CModBrowserStateHandler_AcquireMod::OnExit::__l8::<lambda_1> &operator=(CModBrowserStateHandler_AcquireMod::OnExit::__l8::<lambda_1> const &);
//};
//static_assert(sizeof(CModBrowserStateHandler_AcquireMod::OnExit::__l8::<lambda_1>) == 4, "Invalid CModBrowserStateHandler_AcquireMod::OnExit::__l8::<lambda_1> size");

//class CModBrowserStateHandler_AcquireMod::OnUpdate::__l2::<lambda_1>
//{
//public:
//	<lambda_1>(CModBrowserStateHandler_AcquireMod::OnUpdate::__l2::<lambda_1> &);
//	<lambda_1>(CModBrowserStateHandler_AcquireMod *);
//private:
//	CModBrowserStateHandler_AcquireMod *__this; // 0x0
//public:
//	CModBrowserStateHandler_AcquireMod::OnUpdate::__l2::<lambda_1> &operator=(CModBrowserStateHandler_AcquireMod::OnUpdate::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(CModBrowserStateHandler_AcquireMod::OnUpdate::__l2::<lambda_1>) == 4, "Invalid CModBrowserStateHandler_AcquireMod::OnUpdate::__l2::<lambda_1> size");

//class CModBrowserStateHandler_AcquireMod::KickSignatureVerificationJob::__l2::<lambda_1>
//{
//public:
//	EJobResult operator()() const;
//	<lambda_1>(CModBrowserStateHandler_AcquireMod::KickSignatureVerificationJob::__l2::<lambda_1> &);
//	<lambda_1>(CModBrowserStateHandler_AcquireMod *, SignatureVerificationJob *const &);
//private:
//	CModBrowserStateHandler_AcquireMod *__this; // 0x0
//	SignatureVerificationJob *job; // 0x4
//public:
//	CModBrowserStateHandler_AcquireMod::KickSignatureVerificationJob::__l2::<lambda_1> &operator=(CModBrowserStateHandler_AcquireMod::KickSignatureVerificationJob::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(CModBrowserStateHandler_AcquireMod::KickSignatureVerificationJob::__l2::<lambda_1>) == 8, "Invalid CModBrowserStateHandler_AcquireMod::KickSignatureVerificationJob::__l2::<lambda_1> size");

/* ---------- prototypes */

namespace Download { extern std::shared_ptr<Download::CHttpFileDownload> CreateHttpFileDownload(); }  // hades: added for 0x107191A0

#include "Utils/Logger.hpp"  // hades: added for 0x10718130
struct SJobCounter;  // hades: added for 0x10718130
namespace Job { extern void RunJob(std::function<EJobResult __cdecl(void)> function, SJobCounter *counter, __int32 priority); }  // hades: added for 0x10718130

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_inline SignatureVerificationJob::SignatureVerificationJob(__int32 queueIndex, std::string const &path) : m_finished(false) /* hades-mem-init:  */ // 0x107156E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SignatureVerificationJob@@QAE@HABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

	m_result.verified = false;
	m_result.queueIndex = queueIndex;
	m_result.error = SSignatureVerificationResult::None;
	m_packagePath = path;
}

_inline SSignatureVerificationResult const &SignatureVerificationJob::GetResult() // 0x10717310
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetResult@SignatureVerificationJob@@QAEABUSSignatureVerificationResult@@XZ");

	(void)((!!(m_finished)) || (_wassert(L"m_finished", L"C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Server\\ModBrowser\\ModBrowserStateHandler_AcquireMod.cpp", 32), 0));
	return m_result;
}

_inline void SignatureVerificationJob::Abort(SSignatureVerificationResult::EError error) // 0x10716EC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Abort@SignatureVerificationJob@@QAEXW4EError@SSignatureVerificationResult@@@Z");

	if (!m_result.verified)
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Warning, "SignatureVerificationJob: Signature verification failed for package '%s'", m_packagePath.c_str());
	m_result.error = error;
	m_finished = true;
}

_inline bool SignatureVerificationJob::Update() // 0x107196F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Update@SignatureVerificationJob@@QAE_NXZ");

	c_mod_package package(m_packagePath.c_str());
	c_mod_package::e_error err;
	if (!package.initialize(&err))
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, "SignatureVerificationJob: Failed to open mod package '%s'. Error: %s", m_packagePath.c_str(), c_mod_package::get_error_string(err));
		Abort(SSignatureVerificationResult::PackageInitFailed);
	}
	else
	{
		m_result.verified = package.verify_signature();
		m_result.tempFilePath = m_packagePath;
		memcpy(m_result.computedHash, package.get_header()->sha1, sizeof(m_result.computedHash));
		Complete();
	}
	return true;
}

_inline void SignatureVerificationJob::Complete() // 0x10716F80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Complete@SignatureVerificationJob@@QAEXXZ");

	m_finished = true;
}

CModBrowserStateHandler_AcquireMod::CModBrowserStateHandler_AcquireMod() : m_state(EState::None), m_queueIndex(-1), m_downloadStarted(false), m_cancelled(false), m_hasEnumerated(false), m_pendingVerificationJobs(0), m_ui(nullptr) /* hades-mem-init:  */ // 0x107154D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0CModBrowserStateHandler_AcquireMod@@QAE@XZ");
}

// mangled_x86(MANGLED_DEFAULT, "??0SSignatureVerificationResult@@QAE@XZ"); no body to assert in

CModBrowserStateHandler_AcquireMod::~CModBrowserStateHandler_AcquireMod() // 0x10715C90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1CModBrowserStateHandler_AcquireMod@@QAE@XZ");
}

// mangled_x86(MANGLED_DEFAULT, "??1SSignatureVerificationResult@@QAE@XZ"); no body to assert in
_inline SSignatureVerificationResult::~SSignatureVerificationResult() = default; // 0x10715D80

// mangled_x86(MANGLED_DEFAULT, "??1SignatureVerificationJob@@QAE@XZ"); no body to assert in
_inline SignatureVerificationJob::~SignatureVerificationJob() // 0x10715DD0
{
	// hades: m_result is a typed member now, so its destructor runs implicitly after this body.

}

// mangled_x86(MANGLED_DEFAULT, "??4SSignatureVerificationResult@@QAEAAU0@ABU0@@Z"); no body to assert in
_inline SSignatureVerificationResult &SSignatureVerificationResult::operator=(SSignatureVerificationResult const &__that) = default; // 0x10715F50

void CModBrowserStateHandler_AcquireMod::SetUI(std::shared_ptr<IModBrowserModDownloadUI> const &ui) // 0x10718D40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetUI@CModBrowserStateHandler_AcquireMod@@QAEXABV?$shared_ptr@VIModBrowserModDownloadUI@@@std@@@Z");

	m_ui = ui;
	if (!m_ui)
		return;
	m_ui->SetConfirmCallback([this]() { OnUIActionConfirm(); });
	m_ui->SetRetryCallback([this]() { OnUIActionRetry(); });
	m_ui->SetCancelCallback([this]() { OnUIActionCancel(); });
	m_ui->SetDownloadSingleFinishedCallback([this]() { OnDownloadSingleFinished(); });
}

void CModBrowserStateHandler_AcquireMod::OnEnter() // 0x10718400
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnEnter@CModBrowserStateHandler_AcquireMod@@EAEXXZ");

	Console::WriteLine("Server Mod Browser :: Acquiring mod...");
	SetLocalState(Confirmation);
	SModBrowserState &state = GetManager()->GetStateMutable();
	SetLocalState(None);
	m_downloadQueue.clear();
	m_queueIndex = -1;
	m_downloadStarted = false;
	m_cancelled = false;
	m_hasEnumerated = false;
	m_pendingVerificationJobs = 0;
	SModBrowserState::SRequestedMod &mod = state.requestedMod;
	if (ShouldDownloadPackage(mod))
		m_downloadQueue.push_back(&mod);
	if (m_downloadQueue.empty())
		Complete();
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

void CModBrowserStateHandler_AcquireMod::OnExit() // 0x10718670
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnExit@CModBrowserStateHandler_AcquireMod@@EAEXXZ");

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

void CModBrowserStateHandler_AcquireMod::OnUpdate() // 0x10718B80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnUpdate@CModBrowserStateHandler_AcquireMod@@EAEXXZ");

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

void CModBrowserStateHandler_AcquireMod::UpdateConfirmation() // 0x10719A70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateConfirmation@CModBrowserStateHandler_AcquireMod@@AAEXXZ");
}

void CModBrowserStateHandler_AcquireMod::UpdateDownloading() // 0x10719A90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateDownloading@CModBrowserStateHandler_AcquireMod@@AAEXXZ");

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
			SModBrowserState::SRequestedMod *currentPackage = m_downloadQueue[m_queueIndex];
			if (m_ui)
				m_ui->OnDownloadProgress(*currentPackage, m_queueIndex, position, length, downloadSpeed);
		}
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0CModBrowserStateHandler@@QAE@XZ"); no body to assert in

void CModBrowserStateHandler_AcquireMod::UpdateCancelling() // 0x10719920
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateCancelling@CModBrowserStateHandler_AcquireMod@@AAEXXZ");

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
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Trace, "Server Mod Browser: refreshing mods..");
		m_hasEnumerated = true;
		package_manager.begin_enumerate();
	}

	if (!package_manager.enumeration_in_progress())
	{
		GetManager()->Abort(static_cast<EModBrowserAbortReason>(3));
	}
}

void CModBrowserStateHandler_AcquireMod::UpdateFinalizing() // 0x10719D50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateFinalizing@CModBrowserStateHandler_AcquireMod@@AAEXXZ");

	if (m_pendingVerificationJobs > 0)
		return;
	c_mod_package_manager &packageManager = c_mod_system::get_package_manager();
	if (!m_hasEnumerated)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Trace, "Server Mod Browser: refreshing mods..");
		m_hasEnumerated = true;
		packageManager.begin_enumerate();
	}
	if (!packageManager.enumeration_requested_or_in_progress())
	{
		for (unsigned __int32 i = 0; i < m_downloadQueue.size(); i++)
		{
			if (m_downloadQueue[i]->verificationFailed)
			{
				Abort((EModBrowserAbortReason)2);
				return;
			}
		}
		if (m_ui)
		{
			SModBrowserState const &state = GetManager()->GetState();
			m_ui->OnDownloadFinished(state);
			SetLocalState((EState)6);
		}
	}
}

void CModBrowserStateHandler_AcquireMod::UpdateFinished() // 0x10719F20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateFinished@CModBrowserStateHandler_AcquireMod@@AAEXXZ");

	Complete();
}

void CModBrowserStateHandler_AcquireMod::EnterFinalizationState() // 0x107171C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?EnterFinalizationState@CModBrowserStateHandler_AcquireMod@@AAEXXZ");

	c_mod_package_manager &packageManager = c_mod_system::get_package_manager();
	SetLocalState(EState::Finalizing);
	m_ui->OnDownloadFinalizing();
}

void CModBrowserStateHandler_AcquireMod::EnterFailedState(Download::EDownloadError error) // 0x10717060
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?EnterFailedState@CModBrowserStateHandler_AcquireMod@@AAEXW4EDownloadError@Download@@@Z");

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

void CModBrowserStateHandler_AcquireMod::SetLocalState(CModBrowserStateHandler_AcquireMod::EState state) // 0x10718D10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetLocalState@CModBrowserStateHandler_AcquireMod@@AAEXW4EState@1@@Z");

	m_state = state;
}

void CModBrowserStateHandler_AcquireMod::StartNextDownload() // 0x107191A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?StartNextDownload@CModBrowserStateHandler_AcquireMod@@AAEXXZ");

	if (m_queueIndex >= m_downloadQueue.size())
		return;
	SModBrowserState::SRequestedMod *next = m_downloadQueue[m_queueIndex];
	std::filesystem::path p = std::filesystem::path(c_mod_system::get_package_directory()) / next->hash;
	p.replace_extension(".tmp");
	next->downloadPath = p.string();
	std::shared_ptr<Download::CHttpFileDownload> download = Download::CreateHttpFileDownload();
	download->SetUrl(next->packageUrl);
	download->SetDestinationFile(next->downloadPath);
	download->Start();
	m_activeDownload = download;
	Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Trace, "Server Mod Browser: Downloading mod package '%s'", next->packageUrl.c_str());
	m_downloadStarted = true;
	if (m_ui)
	{
		m_ui->OnDownloadStart();
		SModBrowserState::SRequestedMod *currentPackage = m_downloadQueue[m_queueIndex];
		if (m_ui)
			m_ui->OnDownloadProgress(*currentPackage, m_queueIndex, 0, currentPackage->fileSize, 0);
	}
}

#line 672
void CModBrowserStateHandler_AcquireMod::HandleSignatureVerificationResult(SSignatureVerificationResult const &result) // 0x10717790
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleSignatureVerificationResult@CModBrowserStateHandler_AcquireMod@@AAEXABUSSignatureVerificationResult@@@Z");
	// static ...; // 0x10717E7D
	// static ...; // 0x10717E75
	// static ...; // 0x10717E73
	// static ...; // 0x10717E6F
	// static ...; // 0x10717E68
	// static ...; // 0x10717E20
	// static ...; // 0x10717E18
	// CModBrowserStateHandler_AcquireMod *const this;
	// SSignatureVerificationResult const &result;
	// std::error_code err;
	// SModBrowserState::SRequestedMod *package;
	// std::filesystem::path newPath;
	// SModBrowserState const &state;
	// std::filesystem::path p;
	// s_mod_package_id hash;
	// s_mod_origin_info origin;
		// std::string const &identifier;
		// std::error_code err;

	if (result.queueIndex < 0 || result.queueIndex >= (__int32)m_downloadQueue.size())
	{
	#line 677 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Server\\ModBrowser\\ModBrowserStateHandler_AcquireMod.cpp"
		assert(!"HandleSignatureVerificationResult invalid queue index");
	#line 699 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Server\\ModBrowser\\ModBrowserStateHandler_AcquireMod.cpp"
		return;
	}
	SModBrowserState::SRequestedMod *package = m_downloadQueue[result.queueIndex];
	#line 684 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Server\\ModBrowser\\ModBrowserStateHandler_AcquireMod.cpp"
	assert(package->downloadPath == result.tempFilePath);
	#line 705 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Server\\ModBrowser\\ModBrowserStateHandler_AcquireMod.cpp"
	m_pendingVerificationJobs--;
	if (result.error != SSignatureVerificationResult::None || !result.verified)
	{
		package->verificationFailed = true;
		std::string const &identifier = m_downloadQueue[result.queueIndex]->localName;
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "Server Mod Browser: Failed to verify mod package signature '%s'", identifier.c_str());
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
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "Server Mod Browser: Failed to move downloaded mod package '%s' Error=%s", package->localName.c_str(), err.message());
		EnterFailedState((Download::EDownloadError)5);
		return;
	}
	s_mod_origin_info origin;
	SModBrowserState const &state = GetManager()->GetState();
	origin.server_ip = state.hostname + ":" + std::to_string(state.port);
	origin.server_host = state.serverHost;
	origin.server_name = state.serverName;
	origin.url = package->packageUrl;
	c_mod_system::get_package_manager().set_package_origin(hash, origin);
	c_mod_system::get_package_manager().set_package_signature_verified(hash, true);
}

void CModBrowserStateHandler_AcquireMod::KickSignatureVerificationJob(__int32 queueIndex) // 0x10718130
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?KickSignatureVerificationJob@CModBrowserStateHandler_AcquireMod@@AAEXH@Z");

	Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Trace, "Server Mod Browser: Started mod package signature verification job '%s'", m_downloadQueue[queueIndex]->localName.c_str());
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

void CModBrowserStateHandler_AcquireMod::HandleDownloadStopped() // 0x107173B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleDownloadStopped@CModBrowserStateHandler_AcquireMod@@AAEXXZ");

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
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "Server Mod Browser: Failed to delete temp file '%S'. %s", p.c_str(), err.message().c_str());
		if (error != Download::Cancelled && !m_cancelled)
		{
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Error, "Server Mod Browser: Mod download failed '%s'. %s", m_downloadQueue[m_queueIndex]->localName.c_str(), Download::DownloadErrorToString(m_activeDownload->GetError()));
			EnterFailedState(m_activeDownload->GetError());
			return;
		}
	}
}

bool CModBrowserStateHandler_AcquireMod::ShouldDownloadPackage(SModBrowserState::SRequestedMod const &package) // 0x10718F50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ShouldDownloadPackage@CModBrowserStateHandler_AcquireMod@@AAE_NABUSRequestedMod@SModBrowserState@@@Z");

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

#line 833
void CModBrowserStateHandler_AcquireMod::OnUIActionConfirm() // 0x10718A70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnUIActionConfirm@CModBrowserStateHandler_AcquireMod@@AAEXXZ");
	// CModBrowserStateHandler_AcquireMod *const this;

	#line 835 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Server\\ModBrowser\\ModBrowserStateHandler_AcquireMod.cpp"
		assert(GetLocalState() == EState::Confirmation);
		#line 841 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Server\\ModBrowser\\ModBrowserStateHandler_AcquireMod.cpp"
	GetManager()->GetStateMutable().modDownloadConfirmed = true;
	SetLocalState(EState::Downloading);
}

void CModBrowserStateHandler_AcquireMod::OnUIActionCancel() // 0x107189B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnUIActionCancel@CModBrowserStateHandler_AcquireMod@@AAEXXZ");

	c_mod_package_manager &package_manager = c_mod_system::get_package_manager();
	package_manager.begin_enumerate();
	m_cancelled = true;
	if (m_activeDownload)
		m_activeDownload->Cancel();
	SetLocalState(EState::Cancelled);
}

void CModBrowserStateHandler_AcquireMod::OnUIActionRetry() // 0x10718B10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnUIActionRetry@CModBrowserStateHandler_AcquireMod@@AAEXXZ");

	if (GetLocalState() == EState::DownloadFailed)
	{
		m_downloadStarted = false;
		SetLocalState(EState::Downloading);
	}
}

void CModBrowserStateHandler_AcquireMod::OnDownloadSingleFinished() // 0x10718390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnDownloadSingleFinished@CModBrowserStateHandler_AcquireMod@@AAEXXZ");

	EState state = GetLocalState();
	if (state == WaitingOnUser)
		SetLocalState(finished);
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template CSimpleMessageQueue<SSignatureVerificationResult,4>::CSimpleMessageQueue();
template CSimpleMessageQueue<SSignatureVerificationResult,4>::~CSimpleMessageQueue();
template SSignatureVerificationResult * CSimpleMessageQueue<SSignatureVerificationResult,4>::TryToAllocate();
template _SINGLE_LIST_ENTRY * CSimpleMessageQueue<SSignatureVerificationResult,4>::Reversed(_SINGLE_LIST_ENTRY *);
template void CSimpleMessageQueue<SSignatureVerificationResult,4>::FreeElement(CSimpleMessageQueue<SSignatureVerificationResult,4>::SQueueEntry *);
template void CSimpleMessageQueue<SSignatureVerificationResult,4>::Initialize();
template void CSimpleMessageQueue<SSignatureVerificationResult,4>::Add<SSignatureVerificationResult>(SSignatureVerificationResult *); // 0x10711120
