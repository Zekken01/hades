#ifndef __SERVER_CONNECT_SERVERCONNECTSTATEHANDLER_ACQUIREMODS_HPP__
#define __SERVER_CONNECT_SERVERCONNECTSTATEHANDLER_ACQUIREMODS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Download/IDownload.hpp"
#include "Patches/CustomPackets.hpp"
#include "Server/Connect/ServerConnectDefintiions.hpp"
#include "Server/Connect/ServerConnectModDownloadUI.hpp"
#include "Server/Connect/ServerConnectStateHandler.hpp"

#include <memory>
#include <string>
#include <vector>

/* ---------- forward declarations */

class CServerConnectStateHandler;
class CServerConnectStateHandler_AcquireMods;
class IServerConnectModDownloadUI;
struct SServerConnectState;
struct SSignatureVerificationResult;
namespace Download
{
	class IDownload;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct SSignatureVerificationResult
{
	public:
	enum EError
	{
		None = 0,
		PackageInitFailed,
	};
	public:
	EError error; // 0x0
	__int32 queueIndex; // 0x4
	bool verified; // 0x8
	unsigned char __pad0[3]; // 0x9
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > tempFilePath; // 0xC
	unsigned char computedHash[20]; // 0x28
	SSignatureVerificationResult(SSignatureVerificationResult &); /* compiler_generated() */
	SSignatureVerificationResult(SSignatureVerificationResult const &); /* compiler_generated() */
	_inline SSignatureVerificationResult(); /* compiler_generated() */
	_inline ~SSignatureVerificationResult(); /* compiler_generated() */
	SSignatureVerificationResult &operator=(SSignatureVerificationResult &); /* compiler_generated() */
	_inline SSignatureVerificationResult &operator=(SSignatureVerificationResult const &__that); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(SSignatureVerificationResult) == 60, "Invalid SSignatureVerificationResult size");

class CServerConnectStateHandler_AcquireMods :
	public CServerConnectStateHandler
{
public:
	public:
	enum EState
	{
		None = 0,
		Confirmation,
		Downloading,
		DownloadFailed,
		Cancelled,
		Finalizing,
		WaitingOnUser,
		finished,
	};
	public:
	CServerConnectStateHandler_AcquireMods();
	~CServerConnectStateHandler_AcquireMods();
	void SetUI(std::shared_ptr<IServerConnectModDownloadUI> const &ui);
	_inline EState GetLocalState();
private:
	virtual void OnEnter();
	virtual void OnExit();
	virtual void OnUpdate();
	void UpdateConfirmation();
	void UpdateDownloading();
	void UpdateCancelling();
	void UpdateFinalizing();
	void UpdateFinished();
	void StartNextDownload();
	void HandleDownloadStopped();
	void HandleSignatureVerificationResult(SSignatureVerificationResult const &result);
	void EnterFinalizationState();
	void EnterFailedState(Download::EDownloadError error);
	void SetLocalState(EState state);
	bool ShouldDownloadPackage(SServerConnectState::SRequiredMod const &package);
	void KickSignatureVerificationJob(__int32 queueIndex);
	void OnUIActionConfirm();
	void OnUIActionCancel();
	void OnUIActionRetry();
	void OnUIActionJoinServer();
	EState m_state; // 0x8
	std::vector<SServerConnectState::SRequiredMod *,std::allocator<SServerConnectState::SRequiredMod *> > m_downloadQueue; // 0xC
	std::vector<SSignatureVerificationResult,std::allocator<SSignatureVerificationResult> > m_verificationResults; // 0x1C
	__int32 m_queueIndex; // 0x2C
	bool m_downloadStarted; // 0x30
	bool m_cancelled; // 0x31
	bool m_hasEnumerated; // 0x32
	unsigned char __pad0[1]; // 0x33
	__int32 m_pendingVerificationJobs; // 0x34
	std::shared_ptr<IServerConnectModDownloadUI> m_ui; // 0x38
	std::shared_ptr<Download::IDownload> m_activeDownload; // 0x40
	CSimpleMessageQueue<SSignatureVerificationResult,4> m_verificationQueue; // 0x48
};
static_assert(sizeof(CServerConnectStateHandler_AcquireMods) == 352, "Invalid CServerConnectStateHandler_AcquireMods size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline CServerConnectStateHandler_AcquireMods::EState CServerConnectStateHandler_AcquireMods::GetLocalState() // 0x10907530
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetLocalState@CServerConnectStateHandler_AcquireMods@@QAE?AW4EState@1@XZ");
	// CServerConnectStateHandler_AcquireMods *const this;

	return m_state;
}

/* ---------- private code */

#endif // __SERVER_CONNECT_SERVERCONNECTSTATEHANDLER_ACQUIREMODS_HPP__
