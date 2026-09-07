#ifndef __WEB_UI_WEBMODS_HPP__
#define __WEB_UI_WEBMODS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Patches/CustomPackets.hpp"
#include "Server/Connect/ServerConnectModDownloadUI.hpp"

#include <memory>

/* ---------- forward declarations */

class IServerConnectModDownloadUI;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Web
{
	namespace Ui
	{
		namespace WebMods
		{
			extern std::shared_ptr<IServerConnectModDownloadUI> GetDownloadUI();
			extern void OnGameInputUpdated();
			extern void Init();
		}
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __WEB_UI_WEBMODS_HPP__
