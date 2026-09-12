#ifndef __WEB_UI_SCREENLAYER_HPP__
#define __WEB_UI_SCREENLAYER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Audio/AudioDeviceManager.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Download/HttpFileDownload.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/Ui.hpp"

#include <functional>
#include <memory>
#include <string>

/* ---------- forward declarations */

namespace Web
{
	namespace Ui
	{
		class WebScreen;
	}
}
namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer
		{
			struct SDialogShowParams;
		}
	}
}

/* ---------- constants */

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer
		{
			enum ScreenId
			{
				Alert = 0,
				Browser,
				Chat,
				Console,
				ForgeObjectCreation,
				ForgeObjectProperties,
				Loading,
				ModDownload,
				ProfileSettings,
				Scoreboard,
				ServerSettings,
				Settings,
				Title,
				Voting,
				MainMenu,
				Podium,
			};

			enum EScreenState
			{
				Hidden = 0,
				Waiting,
				Visbile,
			};
		}
	}
}

/* ---------- definitions */

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer
		{
			struct SDialogShowParams
			{
				std::string templateName; // 0x0
				std::function<void __cdecl(std::string const &)> callback; // 0x20
				std::string customBody; // 0x48
				std::string customTitle; // 0x64
				std::string initialValue; // 0x80
				short maxLength; // 0x9C
				short numRows; // 0x9E
				float dialogHeight; // 0xA0
				SDialogShowParams(Web::Ui::ScreenLayer::SDialogShowParams &); /* compiler_generated() */
				SDialogShowParams(Web::Ui::ScreenLayer::SDialogShowParams const &); /* compiler_generated() */
				_inline SDialogShowParams(); /* compiler_generated() */
				_inline ~SDialogShowParams(); /* compiler_generated() */
				Web::Ui::ScreenLayer::SDialogShowParams &operator=(Web::Ui::ScreenLayer::SDialogShowParams &); /* compiler_generated() */
				Web::Ui::ScreenLayer::SDialogShowParams &operator=(Web::Ui::ScreenLayer::SDialogShowParams const &); /* compiler_generated() */
			};
			static_assert(sizeof(Web::Ui::ScreenLayer::SDialogShowParams) == 168, "Invalid Web::Ui::ScreenLayer::SDialogShowParams size");
			static_assert(offsetof(Web::Ui::ScreenLayer::SDialogShowParams, customBody) == 0x48, "Web::Ui::ScreenLayer::SDialogShowParams::customBody moved when its reconstructed padding was removed");
		}
	}
}

/* ---------- prototypes */

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer
		{
			extern void Init();
			extern void Tick();
			extern void Resize();
			extern void Show(bool show);
			extern void Show(Web::Ui::ScreenLayer::ScreenId screenId, std::string const &data);
			extern void Show(std::string const &screenId, std::string const &data);
			extern void Hide(Web::Ui::ScreenLayer::ScreenId screenId);
			extern void Hide(std::string const &screenId);
			extern void Notify(std::string const &event, std::string const &data, bool broadcast);
			extern void NotifyScreen(Web::Ui::ScreenLayer::ScreenId screenId, std::string const &event, std::string const &data);
			extern void NotifyScreen(std::string const &screenId, std::string const &event, std::string const &data);
			extern void NotifyScreenStateChanged(std::string const &screenId, Web::Ui::ScreenLayer::EScreenState state);
			extern void CaptureInput(bool capture, bool pointerCapture);
			extern void ShowAlert(std::string const &title, std::string body, Web::Ui::ScreenLayer::AlertIcon icon, float height);
			extern void RegisterScreen(std::string const &screenId, std::shared_ptr<Web::Ui::WebScreen> const &screen);
			extern void RegisterScreen(Web::Ui::ScreenLayer::ScreenId id, std::shared_ptr<Web::Ui::WebScreen> const &screen);
			extern std::shared_ptr<Web::Ui::WebScreen> GetScreen(std::string const &stringId);
			extern void SetDialogHandler(std::function<void __cdecl(Web::Ui::ScreenLayer::SDialogShowParams const &)> const &handler);
			extern void ShowDialog(Web::Ui::ScreenLayer::SDialogShowParams const &params);
			extern void ShowDialog(std::string const &templateName, std::function<void __cdecl(std::string const &)> callback);
			extern void CreateScreens();
		}
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __WEB_UI_SCREENLAYER_HPP__
