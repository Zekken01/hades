#ifndef __WEB_UI_WEBSERVERMODBROWSER_HPP__
#define __WEB_UI_WEBSERVERMODBROWSER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Patches/CustomPackets.hpp"
#include "Server/ModBrowser/ModBrowserModDownloadUI.hpp"

#include <memory>

/* ---------- forward declarations */

class IModBrowserModDownloadUI;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Web
{
	namespace Ui
	{
		namespace WebServerModBrowser
		{
			extern std::shared_ptr<IModBrowserModDownloadUI> GetDownloadUISingle();
			extern void Init();
		}
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __WEB_UI_WEBSERVERMODBROWSER_HPP__
