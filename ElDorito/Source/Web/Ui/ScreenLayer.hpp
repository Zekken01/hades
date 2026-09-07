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
				std::basic_string<char,std::char_traits<char>,std::allocator<char> > templateName; // 0x0
				unsigned char __pad0[4]; // 0x1C
				std::function<void __cdecl(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &)> callback; // 0x20
				std::basic_string<char,std::char_traits<char>,std::allocator<char> > customBody; // 0x48
				std::basic_string<char,std::char_traits<char>,std::allocator<char> > customTitle; // 0x64
				std::basic_string<char,std::char_traits<char>,std::allocator<char> > initialValue; // 0x80
				short maxLength; // 0x9C
				short numRows; // 0x9E
				float dialogHeight; // 0xA0
				SDialogShowParams(Web::Ui::ScreenLayer::SDialogShowParams &); /* compiler_generated() */
				SDialogShowParams(Web::Ui::ScreenLayer::SDialogShowParams const &); /* compiler_generated() */
				_inline SDialogShowParams(); /* compiler_generated() */
				_inline ~SDialogShowParams(); /* compiler_generated() */
				Web::Ui::ScreenLayer::SDialogShowParams &operator=(Web::Ui::ScreenLayer::SDialogShowParams &); /* compiler_generated() */
				Web::Ui::ScreenLayer::SDialogShowParams &operator=(Web::Ui::ScreenLayer::SDialogShowParams const &); /* compiler_generated() */
				unsigned char __pad1[4]; // 0xA4
			};
			static_assert(sizeof(Web::Ui::ScreenLayer::SDialogShowParams) == 168, "Invalid Web::Ui::ScreenLayer::SDialogShowParams size");
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
			extern void Show(Web::Ui::ScreenLayer::ScreenId screenId, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &data);
			extern void Show(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &screenId, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &data);
			extern void Hide(Web::Ui::ScreenLayer::ScreenId screenId);
			extern void Hide(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &screenId);
			extern void Notify(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &event, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &data, bool broadcast);
			extern void NotifyScreen(Web::Ui::ScreenLayer::ScreenId screenId, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &event, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &data);
			extern void NotifyScreen(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &screenId, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &event, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &data);
			extern void NotifyScreenStateChanged(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &screenId, Web::Ui::ScreenLayer::EScreenState state);
			extern void CaptureInput(bool capture, bool pointerCapture);
			extern void ShowAlert(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &title, std::basic_string<char,std::char_traits<char>,std::allocator<char> > body, Web::Ui::ScreenLayer::AlertIcon icon, float height);
			extern void RegisterScreen(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &screenId, std::shared_ptr<Web::Ui::WebScreen> const &screen);
			extern void RegisterScreen(Web::Ui::ScreenLayer::ScreenId id, std::shared_ptr<Web::Ui::WebScreen> const &screen);
			extern std::shared_ptr<Web::Ui::WebScreen> GetScreen(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &stringId);
			extern void SetDialogHandler(std::function<void __cdecl(Web::Ui::ScreenLayer::SDialogShowParams const &)> const &handler);
			extern void ShowDialog(Web::Ui::ScreenLayer::SDialogShowParams const &params);
			extern void ShowDialog(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &templateName, std::function<void __cdecl(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &)> callback);
			extern void CreateScreens();
		}
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __WEB_UI_SCREENLAYER_HPP__
