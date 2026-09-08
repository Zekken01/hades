#ifndef __SERVER_MODBROWSER_MODBROWSERMODDOWNLOADUI_HPP__
#define __SERVER_MODBROWSER_MODBROWSERMODDOWNLOADUI_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Server/ModBrowser/ModBrowserDefinitions.hpp"
#include "Web/Ui/ScreenLayer.hpp"

#include <functional>
#include <memory>
#include <string>
#include <vector>

/* ---------- forward declarations */

class IModBrowserModDownloadUI;
struct SModBrowserState;

/* ---------- constants */

/* ---------- definitions */

class IModBrowserModDownloadUI
{
public:
	virtual _inline ~IModBrowserModDownloadUI();
	virtual void SetConfirmCallback(std::function<void __cdecl(void)>) = 0;
	virtual void SetRetryCallback(std::function<void __cdecl(void)>) = 0;
	virtual void SetCancelCallback(std::function<void __cdecl(void)>) = 0;
	virtual void SetDownloadSingleFinishedCallback(std::function<void __cdecl(void)>) = 0;
	virtual void OnDownloadStart() = 0;
	virtual void OnDownloadFailed(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &) = 0;
	virtual void OnDownloadFinished(SModBrowserState const &) = 0;
	virtual void OnDownloadFinalizing() = 0;
	virtual void OnDownloadProgress(SModBrowserState::SRequestedMod const &, __int32, long long, long long, __int32) = 0;
	virtual void ShowConfirmation(std::vector<SModBrowserState::SRequestedMod *,std::allocator<SModBrowserState::SRequestedMod *> > const &) = 0;
	virtual void Hide() = 0;
	IModBrowserModDownloadUI(IModBrowserModDownloadUI const &); /* compiler_generated() */
	_inline IModBrowserModDownloadUI(); /* compiler_generated() */
	IModBrowserModDownloadUI &operator=(IModBrowserModDownloadUI const &); /* compiler_generated() */
};
static_assert(sizeof(IModBrowserModDownloadUI) == 4, "Invalid IModBrowserModDownloadUI size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline IModBrowserModDownloadUI::~IModBrowserModDownloadUI() // 0x10C7B980
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1IModBrowserModDownloadUI@@UAE@XZ");
	// IModBrowserModDownloadUI *const this;
}

/* ---------- private code */

#endif // __SERVER_MODBROWSER_MODBROWSERMODDOWNLOADUI_HPP__
