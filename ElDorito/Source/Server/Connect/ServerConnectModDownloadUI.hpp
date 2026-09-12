#ifndef __SERVER_CONNECT_SERVERCONNECTMODDOWNLOADUI_HPP__
#define __SERVER_CONNECT_SERVERCONNECTMODDOWNLOADUI_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Server/Connect/ServerConnectDefintiions.hpp"
#include "Web/Ui/ScreenLayer.hpp"

#include <functional>
#include <memory>
#include <string>
#include <vector>

/* ---------- forward declarations */

class IServerConnectModDownloadUI;
struct SServerConnectState;

/* ---------- constants */

/* ---------- definitions */

class IServerConnectModDownloadUI
{
public:
	virtual _inline ~IServerConnectModDownloadUI() = default; // 0x10CACB30
	virtual void SetConfirmCallback(std::function<void __cdecl(void)>) = 0;
	virtual void SetRetryCallback(std::function<void __cdecl(void)>) = 0;
	virtual void SetCancelCallback(std::function<void __cdecl(void)>) = 0;
	virtual void SetJoinServerCallback(std::function<void __cdecl(void)>) = 0;
	virtual void OnDownloadStart() = 0;
	virtual void OnDownloadFailed(std::string const &) = 0;
	virtual void OnDownloadFinished(SServerConnectState const &) = 0;
	virtual void OnDownloadFinalizing() = 0;
	virtual void OnDownloadProgress(SServerConnectState::SRequiredMod const &, __int32, long long, long long, __int32) = 0;
	virtual void ShowConfirmation(std::vector<SServerConnectState::SRequiredMod *> const &) = 0;
	virtual void Hide() = 0;
	IServerConnectModDownloadUI(IServerConnectModDownloadUI const &); /* compiler_generated() */
	_inline IServerConnectModDownloadUI(); /* compiler_generated() */
	IServerConnectModDownloadUI &operator=(IServerConnectModDownloadUI const &); /* compiler_generated() */
};
static_assert(sizeof(IServerConnectModDownloadUI) == 4, "Invalid IServerConnectModDownloadUI size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __SERVER_CONNECT_SERVERCONNECTMODDOWNLOADUI_HPP__
