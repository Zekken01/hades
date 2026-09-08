#ifndef __WEB_WEBRENDERER_HPP__
#define __WEB_WEBRENDERER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Download/HttpFileDownload.hpp"
#include "Forge/Magnets.hpp"
#include "mods/mod_package_updater.hpp"
#include "Patches/CustomPackets.hpp"
#include "Web/Ui/ScreenLayer.hpp"
#include "Web/WebRendererApp.hpp"
#include "Web/WebRendererHandler.hpp"
#include "Web/WebRendererRenderHandler.hpp"

#include <atomic>
#include <deque>
#include <filesystem>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <string>

/* ---------- forward declarations */

namespace Web
{
	namespace Browser
	{
		class WebRenderer;
		class WebRendererApp;
		class WebRendererHandler;
		class WebRendererRenderHandler;
	}
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Web
{
	namespace Browser
	{
		class WebRenderer
		{
		private:
			scoped_refptr<Web::Browser::WebRendererHandler> m_Handler; // 0x0
			scoped_refptr<Web::Browser::WebRendererRenderHandler> m_RenderHandler; // 0x4
			scoped_refptr<Web::Browser::WebRendererApp> m_App; // 0x8
			Web::Browser::RendererState m_State; // 0xC
			HWND__ *m_HostWindow; // 0x10
			std::queue<std::function<void __cdecl(void)> > m_DomTasks; // 0x14
			std::atomic<bool> m_MainFrameLoaded; // 0x28
			unsigned char __pad0[3]; // 0x29
			std::mutex m_mutex; // 0x2C
			bool m_useOSR; // 0x5C
			unsigned char __pad1[3]; // 0x5D
			std::filesystem::path m_cefPath; // 0x60
		public:
			WebRenderer();
			static std::shared_ptr<Web::Browser::WebRenderer> GetInstance();
			bool Init(std::string const &url, bool debugEnable);
			bool InitRenderer(IDirect3DDevice9 *device);
			bool Render(IDirect3DDevice9 *device);
			bool Update();
			bool Initialized();
			bool IsRendering();
			bool ShowRenderer(bool show, bool overlay);
			bool Resize(unsigned __int32 width, unsigned __int32 height);
			bool SendMouseMoveEvent(CefStructBase<CefMouseEventTraits> const &p_Event, bool p_MouseLeave);
			bool SendMouseClickEvent(CefStructBase<CefMouseEventTraits> const &event, cef_mouse_button_type_t button, bool mouseUp, __int32 clickCount);
			bool SendMouseWheelEvent(CefStructBase<CefMouseEventTraits> const &event, __int32 deltaX, __int32 deltaY);
			bool SendPlatformEvent(CefStructBase<CefPlatformEventTraits> const &event);
			bool SendKeyEvent(CefStructBase<CefKeyEventTraits> const &p_Event);
			bool OpenUrl(std::string const &p_Url);
			bool Reload(bool p_IgnoreCache);
			bool RegisterScheme(std::string const &p_Name, std::string const &p_Directory);
			bool ExecuteJavascript(std::string p_Code, bool deferIfNeeded);
			void EnqueueDOMTask(std::function<void __cdecl(void)> &&task);
			bool PreReset();
			bool PostReset();
			bool Shutdown();
			bool SetState(Web::Browser::RendererState p_State);
			Web::Browser::RendererState GetState();
			std::string GetUIDirectory();
			bool IsAccelerated() const;
			scoped_refptr<Web::Browser::WebRendererHandler> GetClientHandler() const;
			scoped_refptr<Web::Browser::WebRendererRenderHandler> GetRenderHandler() const;
			void OnFrameLoadStart(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame);
			void OnFrameLoadEnd(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame);
		private:
			void InitPakFileSystem();
			void PurgeDOMTasks();
			void ExecuteDOMTasks();
		public:
			_inline ~WebRenderer(); /* compiler_generated() */
		};
	}
}

#pragma pack(pop)
static_assert(sizeof(Web::Browser::WebRenderer) == 124, "Invalid Web::Browser::WebRenderer size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __WEB_WEBRENDERER_HPP__
