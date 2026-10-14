#ifndef __SERVER_MODBROWSER_MODBROWSERSTATEHANDLER_ACQUIREMOD_HPP__
#define __SERVER_MODBROWSER_MODBROWSERSTATEHANDLER_ACQUIREMOD_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Download/IDownload.hpp"
#include "Patches/CustomPackets.hpp"
#include "Server/Connect/ServerConnectStateHandler_AcquireMods.hpp"
#include "Server/ModBrowser/ModBrowserDefinitions.hpp"
#include "Server/ModBrowser/ModBrowserModDownloadUI.hpp"
#include "Server/ModBrowser/ModBrowserStateHandler.hpp"

#include <memory>
#include <vector>

/* ---------- forward declarations */

class CModBrowserStateHandler;
class CModBrowserStateHandler_AcquireMod;
class IModBrowserModDownloadUI;
struct SModBrowserState;
struct SSignatureVerificationResult;
namespace Download
{
	class IDownload;
}

/* ---------- constants */

/* ---------- definitions */

class CModBrowserStateHandler_AcquireMod :
	public CModBrowserStateHandler
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
	CModBrowserStateHandler_AcquireMod();
	~CModBrowserStateHandler_AcquireMod();
	void SetUI(std::shared_ptr<IModBrowserModDownloadUI> const &ui);
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
	bool ShouldDownloadPackage(SModBrowserState::SRequestedMod const &package);
	void KickSignatureVerificationJob(__int32 queueIndex);
	void OnUIActionConfirm();
	void OnUIActionCancel();
	void OnUIActionRetry();
	void OnDownloadSingleFinished();
	EState m_state; // 0x8
	std::vector<SModBrowserState::SRequestedMod *> m_downloadQueue; // 0xC
	std::vector<SSignatureVerificationResult> m_verificationResults; // 0x1C
	__int32 m_queueIndex; // 0x2C
	bool m_downloadStarted; // 0x30
	bool m_cancelled; // 0x31
	bool m_hasEnumerated; // 0x32
	unsigned char __pad0[1]; // 0x33
	__int32 m_pendingVerificationJobs; // 0x34
	std::shared_ptr<IModBrowserModDownloadUI> m_ui; // 0x38
	std::shared_ptr<Download::IDownload> m_activeDownload; // 0x40
	CSimpleMessageQueue<SSignatureVerificationResult,4> m_verificationQueue; // 0x48
};
static_assert(sizeof(CModBrowserStateHandler_AcquireMod) == 352, "Invalid CModBrowserStateHandler_AcquireMod size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

inline CModBrowserStateHandler_AcquireMod::EState CModBrowserStateHandler_AcquireMod::GetLocalState() // 0x107172E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetLocalState@CModBrowserStateHandler_AcquireMod@@QAE?AW4EState@1@XZ");
	// CModBrowserStateHandler_AcquireMod *const this;

	return m_state;
}

/* ---------- private code */

#endif // __SERVER_MODBROWSER_MODBROWSERSTATEHANDLER_ACQUIREMOD_HPP__
